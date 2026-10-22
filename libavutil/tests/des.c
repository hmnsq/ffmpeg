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
    ಹಿಂತಿರುಗಿ r;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t test_ಕೀಲಿ[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ DECLARE_ALIGNED(8, uint8_t, plain)[] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ DECLARE_ALIGNED(8, uint8_t, crypt_ref)[] = { 0x4a, 0xb6, 0x5b, 0x3d, 0x4b, 0x06, 0x15, 0x18 };
ಸ್ಥಿರ DECLARE_ALIGNED(8, uint8_t, tmp)[8];
ಸ್ಥಿರ DECLARE_ALIGNED(8, uint8_t, large_ಬಫರ್)[10002][8];
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t cbc_ಕೀಲಿ[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01,
    0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23
};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಸತತ_test(ಪೂರ್ಣಾಂಕ cbc, ಪೂರ್ಣಾಂಕ decrypt)
{
    AVDES d;
    ಪೂರ್ಣಾಂಕ delay = cbc && !decrypt ? 2 : 1;
    uint64_t res;
    AV_WB64(large_ಬಫರ್[0], 0x4e6f772069732074ULL);
    AV_WB64(large_ಬಫರ್[1], 0x1234567890abcdefULL);
    AV_WB64(tmp,             0x1234567890abcdefULL);
    av_des_init(&d, cbc_ಕೀಲಿ, 192, decrypt);
    av_des_crypt(&d, large_ಬಫರ್[delay], large_ಬಫರ್[0], 10000, cbc ? tmp : ಖಾಲಿ, decrypt);
    res = AV_RB64(large_ಬಫರ್[9999 + delay]);
    ಆದರೆ (cbc) {
        ಆದರೆ (decrypt)
            ಹಿಂತಿರುಗಿ res == 0xc5cecf63ecec514cULL;
        ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ res == 0xcb191f85d1ed8439ULL;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (decrypt)
            ಹಿಂತಿರುಗಿ res == 0x8325397644091a0aULL;
        ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ res == 0xdd17e8b8b437d232ULL;
    }
}

ಒಕ್ಕೂಟ ಶಬ್ದ_byte {
    uint64_t ಶಬ್ದ_4;
    uint8_t byte[8];
};

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVDES d;
    ಪೂರ್ಣಾಂಕ i;
    ಒಕ್ಕೂಟ ಶಬ್ದ_byte ಕೀಲಿ[3], ದತ್ತಾಂಶ, ct;
    uint64_t roundkeys[16];
    srand(av_gettime());
    ಕೀಲಿ[0].ಶಬ್ದ_4 = AV_RB64(test_ಕೀಲಿ);
    ದತ್ತಾಂಶ.ಶಬ್ದ_4   = AV_RB64(plain);
    gen_roundkeys(roundkeys, ಕೀಲಿ[0].ಶಬ್ದ_4);
    ಆದರೆ (des_encdec(ದತ್ತಾಂಶ.ಶಬ್ದ_4, roundkeys, 0) != AV_RB64(crypt_ref)) {
        ಬರೆ("Test 1 failed\n");
        ಹಿಂತಿರುಗಿ 1;
    }
    av_des_init(&d, test_ಕೀಲಿ, 64, 0);
    av_des_crypt(&d, tmp, plain, 1, ಖಾಲಿ, 0);
    ಆದರೆ (memcmp(tmp, crypt_ref, ಗಾತ್ರ(crypt_ref))) {
        ಬರೆ("Public API decryption failed\n");
        ಹಿಂತಿರುಗಿ 1;
    }
    ಆದರೆ (!ಸತತ_test(0, 0) || !ಸತತ_test(0, 1) || !ಸತತ_test(1, 0) || !ಸತತ_test(1, 1)) {
        ಬರೆ("Partial Monte-Carlo test failed\n");
        ಹಿಂತಿರುಗಿ 1;
    }
    ಗಾಗಿ (i = 0; i < 1000; i++) {
        ಕೀಲಿ[0].ಶಬ್ದ_4 = rand64();
        ಕೀಲಿ[1].ಶಬ್ದ_4 = rand64();
        ಕೀಲಿ[2].ಶಬ್ದ_4 = rand64();
        ದತ್ತಾಂಶ.ಶಬ್ದ_4   = rand64();
        av_des_init(&d, ಕೀಲಿ[0].byte, 192, 0);
        av_des_crypt(&d, ct.byte, ದತ್ತಾಂಶ.byte, 1, ಖಾಲಿ, 0);
        av_des_init(&d, ಕೀಲಿ[0].byte, 192, 1);
        av_des_crypt(&d, ct.byte, ct.byte, 1, ಖಾಲಿ, 1);
        ಆದರೆ (ct.ಶಬ್ದ_4 != ದತ್ತಾಂಶ.ಶಬ್ದ_4) {
            ಬರೆ("Test 2 failed\n");
            ಹಿಂತಿರುಗಿ 1;
        }
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ GENTABLES
    ಬರೆ("static const uint32_t S_boxes_P_shuffle[8][64] = {\n");
    ಗಾಗಿ (i = 0; i < 8; i++) {
        ಪೂರ್ಣಾಂಕ j;
        ಬರೆ("    {");
        ಗಾಗಿ (j = 0; j < 64; j++) {
            uint32_t v = S_boxes[i][j >> 1];
            v   = j & 1 ? v >> 4 : v & 0xf;
            v <<= 28 - 4 * i;
            v   = shuffle(v, P_shuffle, ಗಾತ್ರ(P_shuffle));
            ಬರೆ((j & 7) == 0 ? "\n    " : " ");
            ಬರೆ("0x%08X,", v);
        }
        ಬರೆ("\n    },\n");
    }
    ಬರೆ("};\n");
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ 0;
}
