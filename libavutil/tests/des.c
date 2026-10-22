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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/timer.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/des.c"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/time.h"

ਸਥਿਰ uint64_t rand64(ਖਾਲੀ)
{
    uint64_t r = rand();
    r = (r << 32) | rand();
    ਵਾਪਸ r;
}

ਸਥਿਰ ਅਚਲ uint8_t test_ਕੁੰਜੀ[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
ਸਥਿਰ ਅਚਲ DECLARE_ALIGNED(8, uint8_t, plain)[] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
ਸਥਿਰ ਅਚਲ DECLARE_ALIGNED(8, uint8_t, crypt_ref)[] = { 0x4a, 0xb6, 0x5b, 0x3d, 0x4b, 0x06, 0x15, 0x18 };
ਸਥਿਰ DECLARE_ALIGNED(8, uint8_t, tmp)[8];
ਸਥਿਰ DECLARE_ALIGNED(8, uint8_t, large_ਬਫਰ)[10002][8];
ਸਥਿਰ ਅਚਲ uint8_t cbc_ਕੁੰਜੀ[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01,
    0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23
};

ਸਥਿਰ ਪੂਰਨ ਲੜੀਵਾਰ_test(ਪੂਰਨ cbc, ਪੂਰਨ decrypt)
{
    AVDES d;
    ਪੂਰਨ delay = cbc && !decrypt ? 2 : 1;
    uint64_t res;
    AV_WB64(large_ਬਫਰ[0], 0x4e6f772069732074ULL);
    AV_WB64(large_ਬਫਰ[1], 0x1234567890abcdefULL);
    AV_WB64(tmp,             0x1234567890abcdefULL);
    av_des_init(&d, cbc_ਕੁੰਜੀ, 192, decrypt);
    av_des_crypt(&d, large_ਬਫਰ[delay], large_ਬਫਰ[0], 10000, cbc ? tmp : ਨਿਰਾ, decrypt);
    res = AV_RB64(large_ਬਫਰ[9999 + delay]);
    ਜੇ (cbc) {
        ਜੇ (decrypt)
            ਵਾਪਸ res == 0xc5cecf63ecec514cULL;
        ਨਹੀਂਤਾਂ
            ਵਾਪਸ res == 0xcb191f85d1ed8439ULL;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (decrypt)
            ਵਾਪਸ res == 0x8325397644091a0aULL;
        ਨਹੀਂਤਾਂ
            ਵਾਪਸ res == 0xdd17e8b8b437d232ULL;
    }
}

ਸੰਘ ਸ਼ਬਦ_byte {
    uint64_t ਸ਼ਬਦ_4;
    uint8_t byte[8];
};

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVDES d;
    ਪੂਰਨ i;
    ਸੰਘ ਸ਼ਬਦ_byte ਕੁੰਜੀ[3], ਅੰਕੜੇ, ct;
    uint64_t roundkeys[16];
    srand(av_gettime());
    ਕੁੰਜੀ[0].ਸ਼ਬਦ_4 = AV_RB64(test_ਕੁੰਜੀ);
    ਅੰਕੜੇ.ਸ਼ਬਦ_4   = AV_RB64(plain);
    gen_roundkeys(roundkeys, ਕੁੰਜੀ[0].ਸ਼ਬਦ_4);
    ਜੇ (des_encdec(ਅੰਕੜੇ.ਸ਼ਬਦ_4, roundkeys, 0) != AV_RB64(crypt_ref)) {
        ਲਿਖੋ("Test 1 failed\n");
        ਵਾਪਸ 1;
    }
    av_des_init(&d, test_ਕੁੰਜੀ, 64, 0);
    av_des_crypt(&d, tmp, plain, 1, ਨਿਰਾ, 0);
    ਜੇ (memcmp(tmp, crypt_ref, ਆਕਾਰ(crypt_ref))) {
        ਲਿਖੋ("Public API decryption failed\n");
        ਵਾਪਸ 1;
    }
    ਜੇ (!ਲੜੀਵਾਰ_test(0, 0) || !ਲੜੀਵਾਰ_test(0, 1) || !ਲੜੀਵਾਰ_test(1, 0) || !ਲੜੀਵਾਰ_test(1, 1)) {
        ਲਿਖੋ("Partial Monte-Carlo test failed\n");
        ਵਾਪਸ 1;
    }
    ਲਈ (i = 0; i < 1000; i++) {
        ਕੁੰਜੀ[0].ਸ਼ਬਦ_4 = rand64();
        ਕੁੰਜੀ[1].ਸ਼ਬਦ_4 = rand64();
        ਕੁੰਜੀ[2].ਸ਼ਬਦ_4 = rand64();
        ਅੰਕੜੇ.ਸ਼ਬਦ_4   = rand64();
        av_des_init(&d, ਕੁੰਜੀ[0].byte, 192, 0);
        av_des_crypt(&d, ct.byte, ਅੰਕੜੇ.byte, 1, ਨਿਰਾ, 0);
        av_des_init(&d, ਕੁੰਜੀ[0].byte, 192, 1);
        av_des_crypt(&d, ct.byte, ct.byte, 1, ਨਿਰਾ, 1);
        ਜੇ (ct.ਸ਼ਬਦ_4 != ਅੰਕੜੇ.ਸ਼ਬਦ_4) {
            ਲਿਖੋ("Test 2 failed\n");
            ਵਾਪਸ 1;
        }
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ GENTABLES
    ਲਿਖੋ("static const uint32_t S_boxes_P_shuffle[8][64] = {\n");
    ਲਈ (i = 0; i < 8; i++) {
        ਪੂਰਨ j;
        ਲਿਖੋ("    {");
        ਲਈ (j = 0; j < 64; j++) {
            uint32_t v = S_boxes[i][j >> 1];
            v   = j & 1 ? v >> 4 : v & 0xf;
            v <<= 28 - 4 * i;
            v   = shuffle(v, P_shuffle, ਆਕਾਰ(P_shuffle));
            ਲਿਖੋ((j & 7) == 0 ? "\n    " : " ");
            ਲਿਖੋ("0x%08X,", v);
        }
        ਲਿਖੋ("\n    },\n");
    }
    ਲਿਖੋ("};\n");
#ਜੇ_ਅੰਤ
    ਵਾਪਸ 0;
}
