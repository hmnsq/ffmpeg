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

#അന്തര്ഭാവ "libavutil/mem_internal.h"
#അന്തര്ഭാവ "libavutil/timer.h"

#അന്തര്ഭാവ "libavutil/des.c"

#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "libavutil/time.h"

സ്ഥിതം uint64_t rand64(ശൂന്യം)
{
    uint64_t r = rand();
    r = (r << 32) | rand();
    തിരികെ r;
}

സ്ഥിതം സ്ഥിരം uint8_t test_താക്കോൽ[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
സ്ഥിതം സ്ഥിരം DECLARE_ALIGNED(8, uint8_t, plain)[] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
സ്ഥിതം സ്ഥിരം DECLARE_ALIGNED(8, uint8_t, crypt_ref)[] = { 0x4a, 0xb6, 0x5b, 0x3d, 0x4b, 0x06, 0x15, 0x18 };
സ്ഥിതം DECLARE_ALIGNED(8, uint8_t, tmp)[8];
സ്ഥിതം DECLARE_ALIGNED(8, uint8_t, large_buffer)[10002][8];
സ്ഥിതം സ്ഥിരം uint8_t cbc_താക്കോൽ[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01,
    0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23
};

സ്ഥിതം പൂർണ്ണസംഖ്യ run_test(പൂർണ്ണസംഖ്യ cbc, പൂർണ്ണസംഖ്യ decrypt)
{
    AVDES d;
    പൂർണ്ണസംഖ്യ delay = cbc && !decrypt ? 2 : 1;
    uint64_t res;
    AV_WB64(large_buffer[0], 0x4e6f772069732074ULL);
    AV_WB64(large_buffer[1], 0x1234567890abcdefULL);
    AV_WB64(tmp,             0x1234567890abcdefULL);
    av_des_init(&d, cbc_താക്കോൽ, 192, decrypt);
    av_des_crypt(&d, large_buffer[delay], large_buffer[0], 10000, cbc ? tmp : ശൂന്യ, decrypt);
    res = AV_RB64(large_buffer[9999 + delay]);
    എങ്കിൽ (cbc) {
        എങ്കിൽ (decrypt)
            തിരികെ res == 0xc5cecf63ecec514cULL;
        അല്ലെങ്കിൽ
            തിരികെ res == 0xcb191f85d1ed8439ULL;
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (decrypt)
            തിരികെ res == 0x8325397644091a0aULL;
        അല്ലെങ്കിൽ
            തിരികെ res == 0xdd17e8b8b437d232ULL;
    }
}

സംഘം word_byte {
    uint64_t word;
    uint8_t byte[8];
};

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    AVDES d;
    പൂർണ്ണസംഖ്യ i;
    സംഘം word_byte താക്കോൽ[3], data, ct;
    uint64_t roundkeys[16];
    srand(av_gettime());
    താക്കോൽ[0].word = AV_RB64(test_താക്കോൽ);
    data.word   = AV_RB64(plain);
    gen_roundkeys(roundkeys, താക്കോൽ[0].word);
    എങ്കിൽ (des_encdec(data.word, roundkeys, 0) != AV_RB64(crypt_ref)) {
        printf("Test 1 failed\n");
        തിരികെ 1;
    }
    av_des_init(&d, test_താക്കോൽ, 64, 0);
    av_des_crypt(&d, tmp, plain, 1, ശൂന്യ, 0);
    എങ്കിൽ (memcmp(tmp, crypt_ref, വലുപ്പം(crypt_ref))) {
        printf("Public API decryption failed\n");
        തിരികെ 1;
    }
    എങ്കിൽ (!run_test(0, 0) || !run_test(0, 1) || !run_test(1, 0) || !run_test(1, 1)) {
        printf("Partial Monte-Carlo test failed\n");
        തിരികെ 1;
    }
    വേണ്ടി (i = 0; i < 1000; i++) {
        താക്കോൽ[0].word = rand64();
        താക്കോൽ[1].word = rand64();
        താക്കോൽ[2].word = rand64();
        data.word   = rand64();
        av_des_init(&d, താക്കോൽ[0].byte, 192, 0);
        av_des_crypt(&d, ct.byte, data.byte, 1, ശൂന്യ, 0);
        av_des_init(&d, താക്കോൽ[0].byte, 192, 1);
        av_des_crypt(&d, ct.byte, ct.byte, 1, ശൂന്യ, 1);
        എങ്കിൽ (ct.word != data.word) {
            printf("Test 2 failed\n");
            തിരികെ 1;
        }
    }
#ifdef GENTABLES
    printf("static const uint32_t S_boxes_P_shuffle[8][64] = {\n");
    വേണ്ടി (i = 0; i < 8; i++) {
        പൂർണ്ണസംഖ്യ j;
        printf("    {");
        വേണ്ടി (j = 0; j < 64; j++) {
            uint32_t v = S_boxes[i][j >> 1];
            v   = j & 1 ? v >> 4 : v & 0xf;
            v <<= 28 - 4 * i;
            v   = shuffle(v, P_shuffle, വലുപ്പം(P_shuffle));
            printf((j & 7) == 0 ? "\n    " : " ");
            printf("0x%08X,", v);
        }
        printf("\n    },\n");
    }
    printf("};\n");
#endif
    തിരികെ 0;
}
