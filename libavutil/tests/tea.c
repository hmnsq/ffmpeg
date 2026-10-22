/*
 * A 32-bit implementation of the TEA algorithm
 * Copyright (c) 2015 Vesselin Bontchev
 *
 * Loosely based on the implementation of David Wheeler and Roger Needham,
 * https://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm#Reference_code
 *
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

#ضمن <stdio.h>

#ضمن "libavutil/common.h"
#ضمن "libavutil/mem.h"
#ضمن "libavutil/tea.h"

#وصف_ڪريو TEA_انگ_TESTS 4

// https://github.com/logandrews/TeaCrypt/blob/master/tea/tea_test.go
ساكن ثابت uint8_t tea_test_ڪنجي[TEA_انگ_TESTS][16] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    },
    { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
    },
    { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
    }
};

ساكن ثابت uint8_t tea_test_pt[TEA_انگ_TESTS][8] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 },
    { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 },
    { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF }
};

ساكن ثابت uint8_t tea_test_ct[TEA_انگ_TESTS][8] = {
    { 0x41, 0xEA, 0x3A, 0x0A, 0x94, 0xBA, 0xA9, 0x40 },
    { 0x6A, 0x2F, 0x9C, 0xF3, 0xFC, 0xCF, 0x3C, 0x55 },
    { 0xDE, 0xB1, 0xC0, 0xA2, 0x7E, 0x74, 0x5D, 0xB3 },
    { 0x12, 0x6C, 0x6B, 0x92, 0xC0, 0x65, 0x3A, 0x3E }
};

ساكن فراغ test_tea(بنية AVTEA *ctx, uint8_t *dst, ثابت uint8_t *src,
                     ثابت uint8_t *ref, صحيح len, uint8_t *iv, صحيح dir,
                     ثابت حرف *test)
{
    av_tea_crypt(ctx, dst, src, len, iv, dir);
    إذا (memcmp(dst, ref, 8*len)) {
        صحيح i;
        لکو("%s failed\ngot      ", test);
        لكل (i = 0; i < 8*len; i++)
            لکو("%02x ", dst[i]);
        لکو("\nexpected ");
        لكل (i = 0; i < 8*len; i++)
            لکو("%02x ", ref[i]);
        لکو("\n");
        ٻاهر_نڪرو(1);
    }
}

صحيح مکيه(فراغ)
{
    بنية AVTEA *ctx;
    uint8_t buf[8], iv[8];
    صحيح i;
    ساكن ثابت uint8_t src[32] = "HelloWorldHelloWorldHelloWorld";
    uint8_t ct[32];
    uint8_t pl[32];

    ctx = av_tea_alloc();
    إذا (!ctx)
        أرجع 1;

    لكل (i = 0; i < TEA_انگ_TESTS; i++) {
        av_tea_init(ctx, tea_test_ڪنجي[i], 64);

        test_tea(ctx, buf, tea_test_pt[i], tea_test_ct[i], 1, عدم, 0, "encryption");
        test_tea(ctx, buf, tea_test_ct[i], tea_test_pt[i], 1, عدم, 1, "decryption");

        /* encrypt */
        يادگيري_نقل(iv, "HALLO123", 8);
        av_tea_crypt(ctx, ct, src, 4, iv, 0);

        /* decrypt into pl */
        يادگيري_نقل(iv, "HALLO123", 8);
        test_tea(ctx, pl, ct, src, 4, iv, 1, "CBC decryption");

        يادگيري_نقل(iv, "HALLO123", 8);
        test_tea(ctx, ct, ct, src, 4, iv, 1, "CBC inplace decryption");
    }

    لکو("Test encryption/decryption success.\n");
    av_free(ctx);

    أرجع 0;
}
