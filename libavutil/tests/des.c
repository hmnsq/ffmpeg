/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#अन्तर्भाव "libavutil/mem_internal.h"
#अन्तर्भाव "libavutil/timer.h"

#अन्तर्भाव "libavutil/des.c"

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/time.h"

स्थिर uint64_t rand64(शून्य)
{
    uint64_t r = अक्रम();
    r = (r << 32) | अक्रम();
    प्रत्यागम r;
}

स्थिर ध्रुव uint8_t test_कुंजी[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
स्थिर ध्रुव DECLARE_ALIGNED(8, uint8_t, plain)[] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
स्थिर ध्रुव DECLARE_ALIGNED(8, uint8_t, crypt_ref)[] = { 0x4a, 0xb6, 0x5b, 0x3d, 0x4b, 0x06, 0x15, 0x18 };
स्थिर DECLARE_ALIGNED(8, uint8_t, tmp)[8];
स्थिर DECLARE_ALIGNED(8, uint8_t, large_buffer)[10002][8];
स्थिर ध्रुव uint8_t cbc_कुंजी[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01,
    0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23
};

स्थिर पूर्णाङ्क run_test(पूर्णाङ्क cbc, पूर्णाङ्क decrypt)
{
    AVDES d;
    पूर्णाङ्क delay = cbc && !decrypt ? 2 : 1;
    uint64_t res;
    AV_WB64(large_buffer[0], 0x4e6f772069732074ULL);
    AV_WB64(large_buffer[1], 0x1234567890abcdefULL);
    AV_WB64(tmp,             0x1234567890abcdefULL);
    av_des_init(&d, cbc_कुंजी, 192, decrypt);
    av_des_crypt(&d, large_buffer[delay], large_buffer[0], 10000, cbc ? tmp : रिक्त, decrypt);
    res = AV_RB64(large_buffer[9999 + delay]);
    यदि (cbc) {
        यदि (decrypt)
            प्रत्यागम res == 0xc5cecf63ecec514cULL;
        अन्यथा
            प्रत्यागम res == 0xcb191f85d1ed8439ULL;
    } अन्यथा {
        यदि (decrypt)
            प्रत्यागम res == 0x8325397644091a0aULL;
        अन्यथा
            प्रत्यागम res == 0xdd17e8b8b437d232ULL;
    }
}

सङ्घ word_byte {
    uint64_t word;
    uint8_t byte[8];
};

पूर्णाङ्क main(शून्य)
{
    AVDES d;
    पूर्णाङ्क i;
    सङ्घ word_byte कुंजी[3], data, ct;
    uint64_t roundkeys[16];
    बेक्रम(av_gettime());
    कुंजी[0].word = AV_RB64(test_कुंजी);
    data.word   = AV_RB64(plain);
    gen_roundkeys(roundkeys, कुंजी[0].word);
    यदि (des_encdec(data.word, roundkeys, 0) != AV_RB64(crypt_ref)) {
        म_लिखो("Test 1 failed\n");
        प्रत्यागम 1;
    }
    av_des_init(&d, test_कुंजी, 64, 0);
    av_des_crypt(&d, tmp, plain, 1, रिक्त, 0);
    यदि (स_भेद(tmp, crypt_ref, परिमाण(crypt_ref))) {
        म_लिखो("Public API decryption failed\n");
        प्रत्यागम 1;
    }
    यदि (!run_test(0, 0) || !run_test(0, 1) || !run_test(1, 0) || !run_test(1, 1)) {
        म_लिखो("Partial Monte-Carlo test failed\n");
        प्रत्यागम 1;
    }
    प्रति (i = 0; i < 1000; i++) {
        कुंजी[0].word = rand64();
        कुंजी[1].word = rand64();
        कुंजी[2].word = rand64();
        data.word   = rand64();
        av_des_init(&d, कुंजी[0].byte, 192, 0);
        av_des_crypt(&d, ct.byte, data.byte, 1, रिक्त, 0);
        av_des_init(&d, कुंजी[0].byte, 192, 1);
        av_des_crypt(&d, ct.byte, ct.byte, 1, रिक्त, 1);
        यदि (ct.word != data.word) {
            म_लिखो("Test 2 failed\n");
            प्रत्यागम 1;
        }
    }
#ifdef GENTABLES
    म_लिखो("static const uint32_t S_boxes_P_shuffle[8][64] = {\n");
    प्रति (i = 0; i < 8; i++) {
        पूर्णाङ्क j;
        म_लिखो("    {");
        प्रति (j = 0; j < 64; j++) {
            uint32_t v = S_boxes[i][j >> 1];
            v   = j & 1 ? v >> 4 : v & 0xf;
            v <<= 28 - 4 * i;
            v   = shuffle(v, P_shuffle, परिमाण(P_shuffle));
            म_लिखो((j & 7) == 0 ? "\n    " : " ");
            म_लिखो("0x%08X,", v);
        }
        म_लिखो("\n    },\n");
    }
    म_लिखो("};\n");
#endif
    प्रत्यागम 0;
}
