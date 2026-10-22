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

#समावेश "libavutil/mem_internal.h"
#समावेश "libavutil/timer.h"

#समावेश "libavutil/des.c"

#समावेश <stdint.h>
#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <string.h>

#समावेश "libavutil/time.h"

अटल uint64_t rand64(व्योम)
{
    uint64_t r = अक्रम();
    r = (r << 32) | अक्रम();
    वापस r;
}

अटल स्थिर uint8_t test_कुंजी[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
अटल स्थिर DECLARE_ALIGNED(8, uint8_t, plain)[] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
अटल स्थिर DECLARE_ALIGNED(8, uint8_t, crypt_ref)[] = { 0x4a, 0xb6, 0x5b, 0x3d, 0x4b, 0x06, 0x15, 0x18 };
अटल DECLARE_ALIGNED(8, uint8_t, tmp)[8];
अटल DECLARE_ALIGNED(8, uint8_t, large_बफर)[10002][8];
अटल स्थिर uint8_t cbc_कुंजी[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01,
    0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23
};

अटल पूर्णांक run_test(पूर्णांक cbc, पूर्णांक decrypt)
{
    AVDES d;
    पूर्णांक delay = cbc && !decrypt ? 2 : 1;
    uint64_t res;
    AV_WB64(large_बफर[0], 0x4e6f772069732074ULL);
    AV_WB64(large_बफर[1], 0x1234567890abcdefULL);
    AV_WB64(tmp,             0x1234567890abcdefULL);
    av_des_init(&d, cbc_कुंजी, 192, decrypt);
    av_des_crypt(&d, large_बफर[delay], large_बफर[0], 10000, cbc ? tmp : शून्य, decrypt);
    res = AV_RB64(large_बफर[9999 + delay]);
    अगर (cbc) {
        अगर (decrypt)
            वापस res == 0xc5cecf63ecec514cULL;
        अन्यथा
            वापस res == 0xcb191f85d1ed8439ULL;
    } अन्यथा {
        अगर (decrypt)
            वापस res == 0x8325397644091a0aULL;
        अन्यथा
            वापस res == 0xdd17e8b8b437d232ULL;
    }
}

जोड़ word_byte {
    uint64_t word;
    uint8_t byte[8];
};

पूर्णांक मुख्य(व्योम)
{
    AVDES d;
    पूर्णांक i;
    जोड़ word_byte कुंजी[3], तथ्य, ct;
    uint64_t roundkeys[16];
    बेक्रम(av_gettime());
    कुंजी[0].word = AV_RB64(test_कुंजी);
    तथ्य.word   = AV_RB64(plain);
    gen_roundkeys(roundkeys, कुंजी[0].word);
    अगर (des_encdec(तथ्य.word, roundkeys, 0) != AV_RB64(crypt_ref)) {
        म_लिखो("Test 1 failed\n");
        वापस 1;
    }
    av_des_init(&d, test_कुंजी, 64, 0);
    av_des_crypt(&d, tmp, plain, 1, शून्य, 0);
    अगर (स_भेद(tmp, crypt_ref, माप(crypt_ref))) {
        म_लिखो("Public API decryption failed\n");
        वापस 1;
    }
    अगर (!run_test(0, 0) || !run_test(0, 1) || !run_test(1, 0) || !run_test(1, 1)) {
        म_लिखो("Partial Monte-Carlo test failed\n");
        वापस 1;
    }
    क्रम (i = 0; i < 1000; i++) {
        कुंजी[0].word = rand64();
        कुंजी[1].word = rand64();
        कुंजी[2].word = rand64();
        तथ्य.word   = rand64();
        av_des_init(&d, कुंजी[0].byte, 192, 0);
        av_des_crypt(&d, ct.byte, तथ्य.byte, 1, शून्य, 0);
        av_des_init(&d, कुंजी[0].byte, 192, 1);
        av_des_crypt(&d, ct.byte, ct.byte, 1, शून्य, 1);
        अगर (ct.word != तथ्य.word) {
            म_लिखो("Test 2 failed\n");
            वापस 1;
        }
    }
#अगर_घोषित GENTABLES
    म_लिखो("static const uint32_t S_boxes_P_shuffle[8][64] = {\n");
    क्रम (i = 0; i < 8; i++) {
        पूर्णांक j;
        म_लिखो("    {");
        क्रम (j = 0; j < 64; j++) {
            uint32_t v = S_boxes[i][j >> 1];
            v   = j & 1 ? v >> 4 : v & 0xf;
            v <<= 28 - 4 * i;
            v   = shuffle(v, P_shuffle, माप(P_shuffle));
            म_लिखो((j & 7) == 0 ? "\n    " : " ");
            म_लिखो("0x%08X,", v);
        }
        म_लिखो("\n    },\n");
    }
    म_लिखो("};\n");
#पूर्ण_अगर
    वापस 0;
}
