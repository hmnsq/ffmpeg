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

#ಅನ್ತರ್ಭಾವ "libavutil/mem_internal.h"
#ಅನ್ತರ್ಭಾವ "libavutil/timer.h"

#ಅನ್ತರ್ಭಾವ "libavutil/des.c"

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/time.h"

ಸ್ಥಿರ uint64_t rand64(ಶೂನ್ಯ)
{
    uint64_t r = rand();
    r = (r << 32) | rand();
    ಪ್ರತ್ಯಾಗಮ r;
}

ಸ್ಥಿರ ಧ್ರುವ uint8_t test_ಕೀಲಿ[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
ಸ್ಥಿರ ಧ್ರುವ DECLARE_ALIGNED(8, uint8_t, plain)[] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
ಸ್ಥಿರ ಧ್ರುವ DECLARE_ALIGNED(8, uint8_t, crypt_ref)[] = { 0x4a, 0xb6, 0x5b, 0x3d, 0x4b, 0x06, 0x15, 0x18 };
ಸ್ಥಿರ DECLARE_ALIGNED(8, uint8_t, tmp)[8];
ಸ್ಥಿರ DECLARE_ALIGNED(8, uint8_t, large_buffer)[10002][8];
ಸ್ಥಿರ ಧ್ರುವ uint8_t cbc_ಕೀಲಿ[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01,
    0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23
};

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ run_test(ಪೂರ್ಣಾಙ್ಕ cbc, ಪೂರ್ಣಾಙ್ಕ decrypt)
{
    AVDES d;
    ಪೂರ್ಣಾಙ್ಕ delay = cbc && !decrypt ? 2 : 1;
    uint64_t res;
    AV_WB64(large_buffer[0], 0x4e6f772069732074ULL);
    AV_WB64(large_buffer[1], 0x1234567890abcdefULL);
    AV_WB64(tmp,             0x1234567890abcdefULL);
    av_des_init(&d, cbc_ಕೀಲಿ, 192, decrypt);
    av_des_crypt(&d, large_buffer[delay], large_buffer[0], 10000, cbc ? tmp : ರಿಕ್ತ, decrypt);
    res = AV_RB64(large_buffer[9999 + delay]);
    ಯದಿ (cbc) {
        ಯದಿ (decrypt)
            ಪ್ರತ್ಯಾಗಮ res == 0xc5cecf63ecec514cULL;
        ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ res == 0xcb191f85d1ed8439ULL;
    } ಅನ್ಯಥಾ {
        ಯದಿ (decrypt)
            ಪ್ರತ್ಯಾಗಮ res == 0x8325397644091a0aULL;
        ಅನ್ಯಥಾ
            ಪ್ರತ್ಯಾಗಮ res == 0xdd17e8b8b437d232ULL;
    }
}

ಸಙ್ಘ word_byte {
    uint64_t word;
    uint8_t byte[8];
};

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    AVDES d;
    ಪೂರ್ಣಾಙ್ಕ i;
    ಸಙ್ಘ word_byte ಕೀಲಿ[3], data, ct;
    uint64_t roundkeys[16];
    srand(av_gettime());
    ಕೀಲಿ[0].word = AV_RB64(test_ಕೀಲಿ);
    data.word   = AV_RB64(plain);
    gen_roundkeys(roundkeys, ಕೀಲಿ[0].word);
    ಯದಿ (des_encdec(data.word, roundkeys, 0) != AV_RB64(crypt_ref)) {
        printf("Test 1 failed\n");
        ಪ್ರತ್ಯಾಗಮ 1;
    }
    av_des_init(&d, test_ಕೀಲಿ, 64, 0);
    av_des_crypt(&d, tmp, plain, 1, ರಿಕ್ತ, 0);
    ಯದಿ (memcmp(tmp, crypt_ref, ಪರಿಮಾಣ(crypt_ref))) {
        printf("Public API decryption failed\n");
        ಪ್ರತ್ಯಾಗಮ 1;
    }
    ಯದಿ (!run_test(0, 0) || !run_test(0, 1) || !run_test(1, 0) || !run_test(1, 1)) {
        printf("Partial Monte-Carlo test failed\n");
        ಪ್ರತ್ಯಾಗಮ 1;
    }
    ಪ್ರತಿ (i = 0; i < 1000; i++) {
        ಕೀಲಿ[0].word = rand64();
        ಕೀಲಿ[1].word = rand64();
        ಕೀಲಿ[2].word = rand64();
        data.word   = rand64();
        av_des_init(&d, ಕೀಲಿ[0].byte, 192, 0);
        av_des_crypt(&d, ct.byte, data.byte, 1, ರಿಕ್ತ, 0);
        av_des_init(&d, ಕೀಲಿ[0].byte, 192, 1);
        av_des_crypt(&d, ct.byte, ct.byte, 1, ರಿಕ್ತ, 1);
        ಯದಿ (ct.word != data.word) {
            printf("Test 2 failed\n");
            ಪ್ರತ್ಯಾಗಮ 1;
        }
    }
#ifdef GENTABLES
    printf("static const uint32_t S_boxes_P_shuffle[8][64] = {\n");
    ಪ್ರತಿ (i = 0; i < 8; i++) {
        ಪೂರ್ಣಾಙ್ಕ j;
        printf("    {");
        ಪ್ರತಿ (j = 0; j < 64; j++) {
            uint32_t v = S_boxes[i][j >> 1];
            v   = j & 1 ? v >> 4 : v & 0xf;
            v <<= 28 - 4 * i;
            v   = shuffle(v, P_shuffle, ಪರಿಮಾಣ(P_shuffle));
            printf((j & 7) == 0 ? "\n    " : " ");
            printf("0x%08X,", v);
        }
        printf("\n    },\n");
    }
    printf("};\n");
#endif
    ಪ್ರತ್ಯಾಗಮ 0;
}
