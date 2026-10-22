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

ساكن ثابت uint8_t test_کلید[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
ساكن ثابت DECLARE_ALIGNED(8, uint8_t, plain)[] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
ساكن ثابت DECLARE_ALIGNED(8, uint8_t, crypt_ref)[] = { 0x4a, 0xb6, 0x5b, 0x3d, 0x4b, 0x06, 0x15, 0x18 };
ساكن DECLARE_ALIGNED(8, uint8_t, tmp)[8];
ساكن DECLARE_ALIGNED(8, uint8_t, large_میانگیر)[10002][8];
ساكن ثابت uint8_t cbc_کلید[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01,
    0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23
};

ساكن صحيح پیاپی_test(صحيح cbc, صحيح decrypt)
{
    AVDES d;
    صحيح delay = cbc && !decrypt ? 2 : 1;
    uint64_t res;
    AV_WB64(large_میانگیر[0], 0x4e6f772069732074ULL);
    AV_WB64(large_میانگیر[1], 0x1234567890abcdefULL);
    AV_WB64(tmp,             0x1234567890abcdefULL);
    av_des_init(&d, cbc_کلید, 192, decrypt);
    av_des_crypt(&d, large_میانگیر[delay], large_میانگیر[0], 10000, cbc ? tmp : عدم, decrypt);
    res = AV_RB64(large_میانگیر[9999 + delay]);
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

اتحاد کلمه_byte {
    uint64_t کلمه_4;
    uint8_t byte[8];
};

صحيح اصلی(فراغ)
{
    AVDES d;
    صحيح i;
    اتحاد کلمه_byte کلید[3], داده, ct;
    uint64_t roundkeys[16];
    srand(av_gettime());
    کلید[0].کلمه_4 = AV_RB64(test_کلید);
    داده.کلمه_4   = AV_RB64(plain);
    gen_roundkeys(roundkeys, کلید[0].کلمه_4);
    إذا (des_encdec(داده.کلمه_4, roundkeys, 0) != AV_RB64(crypt_ref)) {
        چاپ_کن("Test 1 failed\n");
        أرجع 1;
    }
    av_des_init(&d, test_کلید, 64, 0);
    av_des_crypt(&d, tmp, plain, 1, عدم, 0);
    إذا (memcmp(tmp, crypt_ref, حجم(crypt_ref))) {
        چاپ_کن("Public API decryption failed\n");
        أرجع 1;
    }
    إذا (!پیاپی_test(0, 0) || !پیاپی_test(0, 1) || !پیاپی_test(1, 0) || !پیاپی_test(1, 1)) {
        چاپ_کن("Partial Monte-Carlo test failed\n");
        أرجع 1;
    }
    لكل (i = 0; i < 1000; i++) {
        کلید[0].کلمه_4 = rand64();
        کلید[1].کلمه_4 = rand64();
        کلید[2].کلمه_4 = rand64();
        داده.کلمه_4   = rand64();
        av_des_init(&d, کلید[0].byte, 192, 0);
        av_des_crypt(&d, ct.byte, داده.byte, 1, عدم, 0);
        av_des_init(&d, کلید[0].byte, 192, 1);
        av_des_crypt(&d, ct.byte, ct.byte, 1, عدم, 1);
        إذا (ct.کلمه_4 != داده.کلمه_4) {
            چاپ_کن("Test 2 failed\n");
            أرجع 1;
        }
    }
#اگر_تعریف_شده GENTABLES
    چاپ_کن("static const uint32_t S_boxes_P_shuffle[8][64] = {\n");
    لكل (i = 0; i < 8; i++) {
        صحيح j;
        چاپ_کن("    {");
        لكل (j = 0; j < 64; j++) {
            uint32_t v = S_boxes[i][j >> 1];
            v   = j & 1 ? v >> 4 : v & 0xf;
            v <<= 28 - 4 * i;
            v   = shuffle(v, P_shuffle, حجم(P_shuffle));
            چاپ_کن((j & 7) == 0 ? "\n    " : " ");
            چاپ_کن("0x%08X,", v);
        }
        چاپ_کن("\n    },\n");
    }
    چاپ_کن("};\n");
#پایان_اگر
    أرجع 0;
}
