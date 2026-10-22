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

#اگر_تعریف_نشده AVUTIL_AARCH64_بررسی_چرخهای_H
#تعریف_کن AVUTIL_AARCH64_بررسی_چرخهای_H

#ضمن <stddef.h>
#ضمن <stdint.h>

#ضمن "config.h"

#ضمن "cpu.h"
#ضمن "libavutil/attributes_internal.h"
#ضمن "libavutil/avassert.h"
#ضمن "libavutil/cpu.h"
#ضمن "libavutil/crc.h"
#ضمن "libavutil/intreadwrite.h"

#إذا HAVE_ARM_بررسی_چرخهای
FF_VISIBILITY_افزودن_HIDDEN
uint32_t ff_بررسی_چرخهای_32_aarch64(ثابت AVCRC *ctx, uint32_t بررسی_چرخهای, ثابت uint8_t *میانگیر,
                          size_t درازی);
FF_VISIBILITY_برداشت_HIDDEN
#پایان_اگر

#إذا HAVE_PMULL && HAVE_EOR3
#ضمن "libavutil/crc_internal.h"

FF_VISIBILITY_افزودن_HIDDEN
uint32_t ff_بررسی_چرخهای_neon_pmull(ثابت AVCRC *ctx, uint32_t بررسی_چرخهای, ثابت uint8_t *میانگیر,
                           size_t درازی);
uint32_t ff_بررسی_چرخهای_le_neon_pmull(ثابت AVCRC *ctx, uint32_t بررسی_چرخهای, ثابت uint8_t *میانگیر,
                              size_t درازی);
FF_VISIBILITY_برداشت_HIDDEN

تعداد {
    بررسی_چرخهای_C    = 0,
    PMULL_BE,
    PMULL_LE,
    بررسی_چرخهای_32_PMULL_LE,
};

ساكن ثابت AVCRC بررسی_چرخهای_جدول_pmull[AV_بررسی_چرخهای_MAX][17] = {
    [AV_بررسی_چرخهای_8_ATM] = {
        PMULL_BE,
        0xbc000000, 0x0, 0x32000000, 0x0,
        0x94000000, 0x0, 0xc4000000, 0x0,
        0x62000000, 0x0, 0x79000000, 0x0,
        0x07156a16, 0x1, 0x07000000, 0x1,
    },
    [AV_بررسی_چرخهای_8_EBU] = {
        PMULL_BE,
        0xf3000000, 0x0, 0xb5000000, 0x0,
        0x0d000000, 0x0, 0xfc000000, 0x0,
        0x6a000000, 0x0, 0x65000000, 0x0,
        0x1c4b8192, 0x1, 0x1d000000, 0x1,
    },
    [AV_بررسی_چرخهای_16_ANSI] = {
        PMULL_BE,
        0x807d0000, 0x0, 0xf9e30000, 0x0,
        0xff830000, 0x0, 0xf9130000, 0x0,
        0x807b0000, 0x0, 0x86630000, 0x0,
        0xfffbffe7, 0x1, 0x80050000, 0x1,
    },
    [AV_بررسی_چرخهای_16_CCITT] = {
        PMULL_BE,
        0x59b00000, 0x0, 0x60190000, 0x0,
        0x45630000, 0x0, 0xd5f60000, 0x0,
        0xaa510000, 0x0, 0xeb230000, 0x0,
        0x11303471, 0x1, 0x10210000, 0x1,
    },
    [AV_بررسی_چرخهای_24_IEEE] = {
        PMULL_BE,
        0x467d2400, 0x0, 0x1f428700, 0x0,
        0x64e4d700, 0x0, 0x2c8c9d00, 0x0,
        0xd9fe8c00, 0x0, 0xfd7e0c00, 0x0,
        0xf845fe24, 0x1, 0x864cfb00, 0x1,
    },
    [AV_بررسی_چرخهای_32_IEEE] = {
        PMULL_BE,
        0xe6228b11, 0x0, 0x8833794c, 0x0,
        0xe8a45605, 0x0, 0xc5b9cd4c, 0x0,
        0x490d678d, 0x0, 0xf200aa66, 0x0,
        0x04d101df, 0x1, 0x04c11db7, 0x1,
    },
    [AV_بررسی_چرخهای_32_IEEE_LE] = {
        PMULL_LE,
        0x54442bd4, 0x1, 0xc6e41596, 0x1,
        0x751997d0, 0x1, 0xccaa009e, 0x0,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
    },
    [AV_بررسی_چرخهای_16_ANSI_LE] = {
        PMULL_LE,
        0x1b0c2, 0x0, 0x0000bffa, 0x0,
        0x1d0c2, 0x0, 0x00018cc2, 0x0,
        0x00018cc2, 0x0, 0x1bc02, 0x0,
        0xcfffbffe, 0x1, 0x14003, 0x0,
    },
};


ساكن مضمن فراغ بررسی_چرخهای_init_aarch64(AVCRC *ctx, صحيح le, صحيح بیتها, uint32_t poly, صحيح ctx_اندازه)
{
    uint64_t poly_;
    إذا (le) {
        // convert the reversed representation to regular form
        poly = معکوس(poly, بیتها) >> 1;
    }
    // convert to 32 degree polynomial
    poly_ = ((uint64_t)poly) << (32 - بیتها);

    uint64_t div;
    uint8_t *dst = (uint8_t*)(ctx + 1);
    إذا (le) {
        ctx[0] = PMULL_LE;
        AV_WN64(dst +  0, xnmodp(4 * 128 + 32, poly_, 32, &div, le));
        AV_WN64(dst +  8, xnmodp(4 * 128 - 32, poly_, 32, &div, le));
        uint64_t tmp = xnmodp(128 - 32, poly_, 32, &div, le);
        AV_WN64(dst + 16, xnmodp(128 + 32, poly_, 32, &div, le));
        AV_WN64(dst + 24, tmp);
        AV_WN64(dst + 32, tmp);
        AV_WN64(dst + 40, xnmodp(64, poly_, 32, &div, le));
        AV_WN64(dst + 48, div);
        AV_WN64(dst + 56, معکوس(poly_ | (1ULL << 32), 32));
    } وإلا {
        ctx[0] = PMULL_BE;
        AV_WN64(dst +  0, xnmodp(4 * 128, poly_, 32, &div, le));
        AV_WN64(dst +  8, xnmodp(4 * 128 + 64, poly_, 32, &div, le));
        AV_WN64(dst + 16, xnmodp(128, poly_, 32, &div, le));
        AV_WN64(dst + 24, xnmodp(128 + 64, poly_, 32, &div, le));
        AV_WN64(dst + 32, xnmodp(64, poly_, 32, &div, le));
        AV_WN64(dst + 48, div);
        AV_WN64(dst + 40, xnmodp(96, poly_, 32, &div, le));
        AV_WN64(dst + 56, poly_ | (1ULL << 32));
    }
}

#إذا HAVE_ARM_بررسی_چرخهای
FF_VISIBILITY_افزودن_HIDDEN
uint32_t ff_بررسی_چرخهای_32_pmull_eor3_aarch64(ثابت AVCRC *ctx, uint32_t بررسی_چرخهای, ثابت uint8_t *میانگیر,
                                     size_t درازی);
FF_VISIBILITY_برداشت_HIDDEN
ساكن ثابت AVCRC بررسی_چرخهای_جدول_بررسی_چرخهای_32_pmull[] = {
        بررسی_چرخهای_32_PMULL_LE,
        0x26b70c3d, 0x0, 0x3f41287a, 0x0,
        0xae689191, 0x0, 0xccaa009e, 0x0,
        0xf1da05aa, 0x0, 0x81256527, 0x0,
        0x8f352d95, 0x0, 0x1d9513d7, 0x0,
        0x54442bd4, 0x1, 0xc6e41596, 0x1,
        0x751997d0, 0x1, 0xccaa009e, 0x0,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
};
#پایان_اگر
#پایان_اگر

ساكن مضمن av_cold صحيح ff_بررسی_چرخهای_init_aarch64(AVCRC *ctx, صحيح le, صحيح بیتها, uint32_t poly, صحيح ctx_اندازه)
{
#إذا HAVE_PMULL && HAVE_EOR3
    صحيح cpu_flags = av_get_cpu_flags();

    إذا (have_pmull(cpu_flags) && have_eor3(cpu_flags)) {
        بررسی_چرخهای_init_aarch64(ctx, le, بیتها, poly, ctx_اندازه);
        أرجع 1;
    }
#پایان_اگر
    أرجع 0;
}

ساكن مضمن uint32_t ff_بررسی_چرخهای_aarch64(ثابت AVCRC *ctx, uint32_t بررسی_چرخهای,
                                      ثابت uint8_t *میانگیر, size_t درازی)
{
    بدل (ctx[0]) {
#إذا HAVE_PMULL && HAVE_EOR3
#إذا HAVE_ARM_بررسی_چرخهای
    حالة بررسی_چرخهای_32_PMULL_LE: أرجع ff_بررسی_چرخهای_32_pmull_eor3_aarch64(ctx, بررسی_چرخهای, میانگیر, درازی);
#پایان_اگر
    حالة PMULL_BE: أرجع ff_بررسی_چرخهای_neon_pmull(ctx, بررسی_چرخهای, میانگیر, درازی);
    حالة PMULL_LE: أرجع ff_بررسی_چرخهای_le_neon_pmull(ctx, بررسی_چرخهای, میانگیر, درازی);
#پایان_اگر
#إذا HAVE_ARM_بررسی_چرخهای
    حالة (AV_بررسی_چرخهای_32_IEEE_LE + 1): أرجع ff_بررسی_چرخهای_32_aarch64(ctx, بررسی_چرخهای, میانگیر, درازی);
#پایان_اگر
    افتراضي: av_unreachable("AARCH64 has PMULL_LE, PMULL_BE, CRC32_PMULL_LE, and AV_CRC_32_IEEE_LE arch-specific CRC code");
    }
    أرجع 0;
}

ساكن مضمن ثابت AVCRC *ff_بررسی_چرخهای_get_جدول_aarch64(AVCRCId بررسی_چرخهای_id)
{
    صحيح cpu_flags = av_get_cpu_flags();
#إذا HAVE_PMULL && HAVE_EOR3
    إذا (have_pmull(cpu_flags) && have_eor3(cpu_flags)) {
#إذا HAVE_ARM_بررسی_چرخهای
        إذا (بررسی_چرخهای_id == AV_بررسی_چرخهای_32_IEEE_LE && have_arm_بررسی_چرخهای(cpu_flags)) {
            أرجع بررسی_چرخهای_جدول_بررسی_چرخهای_32_pmull;
        }
#پایان_اگر
        أرجع بررسی_چرخهای_جدول_pmull[بررسی_چرخهای_id];
    }
#پایان_اگر
#إذا HAVE_ARM_بررسی_چرخهای
    ساكن ثابت AVCRC بررسی_چرخهای_32_ieee_le_ctx[] = {
        AV_بررسی_چرخهای_32_IEEE_LE + 1
    };

    إذا (بررسی_چرخهای_id != AV_بررسی_چرخهای_32_IEEE_LE)
        أرجع عدم;

    إذا (have_arm_بررسی_چرخهای(cpu_flags)) {
        أرجع بررسی_چرخهای_32_ieee_le_ctx;
    }
#پایان_اگر
    أرجع عدم;
}

#پایان_اگر /* AVUTIL_AARCH64_CRC_H */
