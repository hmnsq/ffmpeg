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

#جے_بنا_تعریف AVUTIL_AARCH64_چکری_جانچ_H
#تعریف_کرو AVUTIL_AARCH64_چکری_جانچ_H

#ضمن <stddef.h>
#ضمن <stdint.h>

#ضمن "config.h"

#ضمن "cpu.h"
#ضمن "libavutil/attributes_internal.h"
#ضمن "libavutil/avassert.h"
#ضمن "libavutil/cpu.h"
#ضمن "libavutil/crc.h"
#ضمن "libavutil/intreadwrite.h"

#إذا HAVE_ARM_چکری_جانچ
FF_VISIBILITY_ڈالو_HIDDEN
uint32_t ff_چکری_جانچ_32_aarch64(ثابت AVCRC *ctx, uint32_t چکری_جانچ, ثابت uint8_t *بفر,
                          size_t لمائی);
FF_VISIBILITY_نکالو_HIDDEN
#جے_انت

#إذا HAVE_PMULL && HAVE_EOR3
#ضمن "libavutil/crc_internal.h"

FF_VISIBILITY_ڈالو_HIDDEN
uint32_t ff_چکری_جانچ_neon_pmull(ثابت AVCRC *ctx, uint32_t چکری_جانچ, ثابت uint8_t *بفر,
                           size_t لمائی);
uint32_t ff_چکری_جانچ_le_neon_pmull(ثابت AVCRC *ctx, uint32_t چکری_جانچ, ثابت uint8_t *بفر,
                              size_t لمائی);
FF_VISIBILITY_نکالو_HIDDEN

تعداد {
    چکری_جانچ_C    = 0,
    PMULL_BE,
    PMULL_LE,
    چکری_جانچ_32_PMULL_LE,
};

ساكن ثابت AVCRC چکری_جانچ_جدول_pmull[AV_چکری_جانچ_MAX][17] = {
    [AV_چکری_جانچ_8_ATM] = {
        PMULL_BE,
        0xbc000000, 0x0, 0x32000000, 0x0,
        0x94000000, 0x0, 0xc4000000, 0x0,
        0x62000000, 0x0, 0x79000000, 0x0,
        0x07156a16, 0x1, 0x07000000, 0x1,
    },
    [AV_چکری_جانچ_8_EBU] = {
        PMULL_BE,
        0xf3000000, 0x0, 0xb5000000, 0x0,
        0x0d000000, 0x0, 0xfc000000, 0x0,
        0x6a000000, 0x0, 0x65000000, 0x0,
        0x1c4b8192, 0x1, 0x1d000000, 0x1,
    },
    [AV_چکری_جانچ_16_ANSI] = {
        PMULL_BE,
        0x807d0000, 0x0, 0xf9e30000, 0x0,
        0xff830000, 0x0, 0xf9130000, 0x0,
        0x807b0000, 0x0, 0x86630000, 0x0,
        0xfffbffe7, 0x1, 0x80050000, 0x1,
    },
    [AV_چکری_جانچ_16_CCITT] = {
        PMULL_BE,
        0x59b00000, 0x0, 0x60190000, 0x0,
        0x45630000, 0x0, 0xd5f60000, 0x0,
        0xaa510000, 0x0, 0xeb230000, 0x0,
        0x11303471, 0x1, 0x10210000, 0x1,
    },
    [AV_چکری_جانچ_24_IEEE] = {
        PMULL_BE,
        0x467d2400, 0x0, 0x1f428700, 0x0,
        0x64e4d700, 0x0, 0x2c8c9d00, 0x0,
        0xd9fe8c00, 0x0, 0xfd7e0c00, 0x0,
        0xf845fe24, 0x1, 0x864cfb00, 0x1,
    },
    [AV_چکری_جانچ_32_IEEE] = {
        PMULL_BE,
        0xe6228b11, 0x0, 0x8833794c, 0x0,
        0xe8a45605, 0x0, 0xc5b9cd4c, 0x0,
        0x490d678d, 0x0, 0xf200aa66, 0x0,
        0x04d101df, 0x1, 0x04c11db7, 0x1,
    },
    [AV_چکری_جانچ_32_IEEE_LE] = {
        PMULL_LE,
        0x54442bd4, 0x1, 0xc6e41596, 0x1,
        0x751997d0, 0x1, 0xccaa009e, 0x0,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
    },
    [AV_چکری_جانچ_16_ANSI_LE] = {
        PMULL_LE,
        0x1b0c2, 0x0, 0x0000bffa, 0x0,
        0x1d0c2, 0x0, 0x00018cc2, 0x0,
        0x00018cc2, 0x0, 0x1bc02, 0x0,
        0xcfffbffe, 0x1, 0x14003, 0x0,
    },
};


ساكن مضمن فراغ چکری_جانچ_init_aarch64(AVCRC *ctx, صحيح le, صحيح بٹ, uint32_t poly, صحيح ctx_ناپ)
{
    uint64_t poly_;
    إذا (le) {
        // convert the reversed representation to regular form
        poly = الٹ(poly, بٹ) >> 1;
    }
    // convert to 32 degree polynomial
    poly_ = ((uint64_t)poly) << (32 - بٹ);

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
        AV_WN64(dst + 56, الٹ(poly_ | (1ULL << 32), 32));
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

#إذا HAVE_ARM_چکری_جانچ
FF_VISIBILITY_ڈالو_HIDDEN
uint32_t ff_چکری_جانچ_32_pmull_eor3_aarch64(ثابت AVCRC *ctx, uint32_t چکری_جانچ, ثابت uint8_t *بفر,
                                     size_t لمائی);
FF_VISIBILITY_نکالو_HIDDEN
ساكن ثابت AVCRC چکری_جانچ_جدول_چکری_جانچ_32_pmull[] = {
        چکری_جانچ_32_PMULL_LE,
        0x26b70c3d, 0x0, 0x3f41287a, 0x0,
        0xae689191, 0x0, 0xccaa009e, 0x0,
        0xf1da05aa, 0x0, 0x81256527, 0x0,
        0x8f352d95, 0x0, 0x1d9513d7, 0x0,
        0x54442bd4, 0x1, 0xc6e41596, 0x1,
        0x751997d0, 0x1, 0xccaa009e, 0x0,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
};
#جے_انت
#جے_انت

ساكن مضمن av_cold صحيح ff_چکری_جانچ_init_aarch64(AVCRC *ctx, صحيح le, صحيح بٹ, uint32_t poly, صحيح ctx_ناپ)
{
#إذا HAVE_PMULL && HAVE_EOR3
    صحيح cpu_flags = av_get_cpu_flags();

    إذا (have_pmull(cpu_flags) && have_eor3(cpu_flags)) {
        چکری_جانچ_init_aarch64(ctx, le, بٹ, poly, ctx_ناپ);
        أرجع 1;
    }
#جے_انت
    أرجع 0;
}

ساكن مضمن uint32_t ff_چکری_جانچ_aarch64(ثابت AVCRC *ctx, uint32_t چکری_جانچ,
                                      ثابت uint8_t *بفر, size_t لمائی)
{
    بدل (ctx[0]) {
#إذا HAVE_PMULL && HAVE_EOR3
#إذا HAVE_ARM_چکری_جانچ
    حالة چکری_جانچ_32_PMULL_LE: أرجع ff_چکری_جانچ_32_pmull_eor3_aarch64(ctx, چکری_جانچ, بفر, لمائی);
#جے_انت
    حالة PMULL_BE: أرجع ff_چکری_جانچ_neon_pmull(ctx, چکری_جانچ, بفر, لمائی);
    حالة PMULL_LE: أرجع ff_چکری_جانچ_le_neon_pmull(ctx, چکری_جانچ, بفر, لمائی);
#جے_انت
#إذا HAVE_ARM_چکری_جانچ
    حالة (AV_چکری_جانچ_32_IEEE_LE + 1): أرجع ff_چکری_جانچ_32_aarch64(ctx, چکری_جانچ, بفر, لمائی);
#جے_انت
    افتراضي: av_unreachable("AARCH64 has PMULL_LE, PMULL_BE, CRC32_PMULL_LE, and AV_CRC_32_IEEE_LE arch-specific CRC code");
    }
    أرجع 0;
}

ساكن مضمن ثابت AVCRC *ff_چکری_جانچ_get_جدول_aarch64(AVCRCId چکری_جانچ_id)
{
    صحيح cpu_flags = av_get_cpu_flags();
#إذا HAVE_PMULL && HAVE_EOR3
    إذا (have_pmull(cpu_flags) && have_eor3(cpu_flags)) {
#إذا HAVE_ARM_چکری_جانچ
        إذا (چکری_جانچ_id == AV_چکری_جانچ_32_IEEE_LE && have_arm_چکری_جانچ(cpu_flags)) {
            أرجع چکری_جانچ_جدول_چکری_جانچ_32_pmull;
        }
#جے_انت
        أرجع چکری_جانچ_جدول_pmull[چکری_جانچ_id];
    }
#جے_انت
#إذا HAVE_ARM_چکری_جانچ
    ساكن ثابت AVCRC چکری_جانچ_32_ieee_le_ctx[] = {
        AV_چکری_جانچ_32_IEEE_LE + 1
    };

    إذا (چکری_جانچ_id != AV_چکری_جانچ_32_IEEE_LE)
        أرجع عدم;

    إذا (have_arm_چکری_جانچ(cpu_flags)) {
        أرجع چکری_جانچ_32_ieee_le_ctx;
    }
#جے_انت
    أرجع عدم;
}

#جے_انت /* AVUTIL_AARCH64_CRC_H */
