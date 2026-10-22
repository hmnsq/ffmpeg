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

#ضمن "libavutil/mem_internal.h"
#ضمن "libavutil/timer.h"

#ضمن "libavutil/des.c"

#ضمن <stdint.h>
#ضمن <stdio.h>
#ضمن <stdlib.h>
#ضمن <string.h>

#ضمن "libavutil/time.h"

ساكن uint64_t rand64(فراغ)
{
    uint64_t r = rand();
    r = (r << 32) | rand();
    أرجع r;
}

ساكن ثابت uint8_t test_ڪنجي[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
ساكن ثابت DECLARE_ALIGNED(8, uint8_t, plain)[] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
ساكن ثابت DECLARE_ALIGNED(8, uint8_t, crypt_ref)[] = { 0x4a, 0xb6, 0x5b, 0x3d, 0x4b, 0x06, 0x15, 0x18 };
ساكن DECLARE_ALIGNED(8, uint8_t, tmp)[8];
ساكن DECLARE_ALIGNED(8, uint8_t, large_بفر)[10002][8];
ساكن ثابت uint8_t cbc_ڪنجي[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01,
    0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23
};

ساكن صحيح لاڳيتو_test(صحيح cbc, صحيح decrypt)
{
    AVDES d;
    صحيح delay = cbc && !decrypt ? 2 : 1;
    uint64_t res;
    AV_WB64(large_بفر[0], 0x4e6f772069732074ULL);
    AV_WB64(large_بفر[1], 0x1234567890abcdefULL);
    AV_WB64(tmp,             0x1234567890abcdefULL);
    av_des_init(&d, cbc_ڪنجي, 192, decrypt);
    av_des_crypt(&d, large_بفر[delay], large_بفر[0], 10000, cbc ? tmp : عدم, decrypt);
    res = AV_RB64(large_بفر[9999 + delay]);
    إذا (cbc) {
        إذا (decrypt)
            أرجع res == 0xc5cecf63ecec514cULL;
        وإلا
            أرجع res == 0xcb191f85d1ed8439ULL;
    } وإلا {
        إذا (decrypt)
            أرجع res == 0x8325397644091a0aULL;
        وإلا
            أرجع res == 0xdd17e8b8b437d232ULL;
    }
}

اتحاد لفظ_byte {
    uint64_t لفظ_4;
    uint8_t byte[8];
};

صحيح مکيه(فراغ)
{
    AVDES d;
    صحيح i;
    اتحاد لفظ_byte ڪنجي[3], معلومات, ct;
    uint64_t roundkeys[16];
    srand(av_gettime());
    ڪنجي[0].لفظ_4 = AV_RB64(test_ڪنجي);
    معلومات.لفظ_4   = AV_RB64(plain);
    gen_roundkeys(roundkeys, ڪنجي[0].لفظ_4);
    إذا (des_encdec(معلومات.لفظ_4, roundkeys, 0) != AV_RB64(crypt_ref)) {
        لکو("Test 1 failed\n");
        أرجع 1;
    }
    av_des_init(&d, test_ڪنجي, 64, 0);
    av_des_crypt(&d, tmp, plain, 1, عدم, 0);
    إذا (memcmp(tmp, crypt_ref, حجم(crypt_ref))) {
        لکو("Public API decryption failed\n");
        أرجع 1;
    }
    إذا (!لاڳيتو_test(0, 0) || !لاڳيتو_test(0, 1) || !لاڳيتو_test(1, 0) || !لاڳيتو_test(1, 1)) {
        لکو("Partial Monte-Carlo test failed\n");
        أرجع 1;
    }
    لكل (i = 0; i < 1000; i++) {
        ڪنجي[0].لفظ_4 = rand64();
        ڪنجي[1].لفظ_4 = rand64();
        ڪنجي[2].لفظ_4 = rand64();
        معلومات.لفظ_4   = rand64();
        av_des_init(&d, ڪنجي[0].byte, 192, 0);
        av_des_crypt(&d, ct.byte, معلومات.byte, 1, عدم, 0);
        av_des_init(&d, ڪنجي[0].byte, 192, 1);
        av_des_crypt(&d, ct.byte, ct.byte, 1, عدم, 1);
        إذا (ct.لفظ_4 != معلومات.لفظ_4) {
            لکو("Test 2 failed\n");
            أرجع 1;
        }
    }
#جيڪڏهن_وصف_ٿيل GENTABLES
    لکو("static const uint32_t S_boxes_P_shuffle[8][64] = {\n");
    لكل (i = 0; i < 8; i++) {
        صحيح j;
        لکو("    {");
        لكل (j = 0; j < 64; j++) {
            uint32_t v = S_boxes[i][j >> 1];
            v   = j & 1 ? v >> 4 : v & 0xf;
            v <<= 28 - 4 * i;
            v   = shuffle(v, P_shuffle, حجم(P_shuffle));
            لکو((j & 7) == 0 ? "\n    " : " ");
            لکو("0x%08X,", v);
        }
        لکو("\n    },\n");
    }
    لکو("};\n");
#جيڪڏهن_پورو
    أرجع 0;
}
