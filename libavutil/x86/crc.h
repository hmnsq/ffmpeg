/*
 * Copyright (c) 2025 Shreesh Adiga <16567adigashreesh@gmail.com>
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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_X86_چڪري_جاچ_H
#وصف_ڪريو AVUTIL_X86_چڪري_جاچ_H

#ضمن "config.h"
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/attributes_internal.h"
#ضمن "libavutil/avassert.h"
#ضمن "libavutil/cpu.h"
#ضمن "libavutil/crc.h"
#ضمن "libavutil/intreadwrite.h"
#ضمن "libavutil/x86/cpu.h"

#إذا HAVE_CLMUL_EXTERNAL
#ضمن "libavutil/crc_internal.h"

FF_VISIBILITY_ڌڪو_HIDDEN
uint32_t ff_چڪري_جاچ_clmul(ثابت AVCRC *ctx, uint32_t چڪري_جاچ,
                      ثابت uint8_t *بفر, size_t ڊيگهائي);
uint32_t ff_چڪري_جاچ_le_clmul(ثابت AVCRC *ctx, uint32_t چڪري_جاچ,
                         ثابت uint8_t *بفر, size_t ڊيگهائي);
FF_VISIBILITY_ڪڍو_HIDDEN

تعداد {
    چڪري_جاچ_C    = 0,
    CLMUL_BE,
    CLMUL_LE,
};

ساكن ثابت AVCRC چڪري_جاچ_جدول_clmul[AV_چڪري_جاچ_MAX][17] = {
    [AV_چڪري_جاچ_8_ATM] = {
        CLMUL_BE,
        0x32000000, 0x0, 0xbc000000, 0x0,
        0xc4000000, 0x0, 0x94000000, 0x0,
        0x62000000, 0x0, 0x79000000, 0x0,
        0x07156a16, 0x1, 0x07000000, 0x1,
    },
    [AV_چڪري_جاچ_8_EBU] = {
        CLMUL_BE,
        0xb5000000, 0x0, 0xf3000000, 0x0,
        0xfc000000, 0x0, 0x0d000000, 0x0,
        0x6a000000, 0x0, 0x65000000, 0x0,
        0x1c4b8192, 0x1, 0x1d000000, 0x1,
    },
    [AV_چڪري_جاچ_16_ANSI] = {
        CLMUL_BE,
        0xf9e30000, 0x0, 0x807d0000, 0x0,
        0xf9130000, 0x0, 0xff830000, 0x0,
        0x807b0000, 0x0, 0x86630000, 0x0,
        0xfffbffe7, 0x1, 0x80050000, 0x1,
    },
    [AV_چڪري_جاچ_16_CCITT] = {
        CLMUL_BE,
        0x60190000, 0x0, 0x59b00000, 0x0,
        0xd5f60000, 0x0, 0x45630000, 0x0,
        0xaa510000, 0x0, 0xeb230000, 0x0,
        0x11303471, 0x1, 0x10210000, 0x1,
    },
    [AV_چڪري_جاچ_24_IEEE] = {
        CLMUL_BE,
        0x1f428700, 0x0, 0x467d2400, 0x0,
        0x2c8c9d00, 0x0, 0x64e4d700, 0x0,
        0xd9fe8c00, 0x0, 0xfd7e0c00, 0x0,
        0xf845fe24, 0x1, 0x864cfb00, 0x1,
    },
    [AV_چڪري_جاچ_32_IEEE] = {
        CLMUL_BE,
        0x8833794c, 0x0, 0xe6228b11, 0x0,
        0xc5b9cd4c, 0x0, 0xe8a45605, 0x0,
        0x490d678d, 0x0, 0xf200aa66, 0x0,
        0x04d101df, 0x1, 0x04c11db7, 0x1,
    },
    [AV_چڪري_جاچ_32_IEEE_LE] = {
        CLMUL_LE,
        0xc6e41596, 0x1, 0x54442bd4, 0x1,
        0xccaa009e, 0x0, 0x751997d0, 0x1,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
    },
    [AV_چڪري_جاچ_16_ANSI_LE] = {
        CLMUL_LE,
        0x0000bffa, 0x0, 0x1b0c2, 0x0,
        0x00018cc2, 0x0, 0x1d0c2, 0x0,
        0x00018cc2, 0x0, 0x1bc02, 0x0,
        0xcfffbffe, 0x1, 0x14003, 0x0,
    },
};

ساكن مضمن فراغ چڪري_جاچ_init_x86(AVCRC *ctx, صحيح le, صحيح بٽ, uint32_t poly, صحيح ctx_سائيز)
{
    uint64_t poly_;
    إذا (le) {
        // convert the reversed representation to regular form
        poly = ابتو(poly, بٽ) >> 1;
    }
    // convert to 32 degree polynomial
    poly_ = ((uint64_t)poly) << (32 - بٽ);

    uint64_t div;
    uint8_t *dst = (uint8_t*)(ctx + 1);
    إذا (le) {
        ctx[0] = CLMUL_LE;
        AV_WN64(dst,      xnmodp(4 * 128 - 32, poly_, 32, &div, le));
        AV_WN64(dst +  8, xnmodp(4 * 128 + 32, poly_, 32, &div, le));
        uint64_t tmp = xnmodp(128 - 32, poly_, 32, &div, le);
        AV_WN64(dst + 16, tmp);
        AV_WN64(dst + 24, xnmodp(128 + 32, poly_, 32, &div, le));
        AV_WN64(dst + 32, tmp);
        AV_WN64(dst + 40, xnmodp(64, poly_, 32, &div, le));
        AV_WN64(dst + 48, div);
        AV_WN64(dst + 56, ابتو(poly_ | (1ULL << 32), 32));
    } وإلا {
        ctx[0] = CLMUL_BE;
        AV_WN64(dst,      xnmodp(4 * 128 + 64, poly_, 32, &div, le));
        AV_WN64(dst +  8, xnmodp(4 * 128, poly_, 32, &div, le));
        AV_WN64(dst + 16, xnmodp(128 + 64, poly_, 32, &div, le));
        AV_WN64(dst + 24, xnmodp(128, poly_, 32, &div, le));
        AV_WN64(dst + 32, xnmodp(64, poly_, 32, &div, le));
        AV_WN64(dst + 48, div);
        AV_WN64(dst + 40, xnmodp(96, poly_, 32, &div, le));
        AV_WN64(dst + 56, poly_ | (1ULL << 32));
    }
}
#جيڪڏهن_پورو

ساكن مضمن ثابت AVCRC *ff_چڪري_جاچ_get_جدول_x86(AVCRCId چڪري_جاچ_id)
{
#إذا HAVE_CLMUL_EXTERNAL
    صحيح cpu_flags = av_get_cpu_flags();

    إذا (EXTERNAL_CLMUL(cpu_flags)) {
        أرجع چڪري_جاچ_جدول_clmul[چڪري_جاچ_id];
    }
#جيڪڏهن_پورو
    أرجع عدم;
}

ساكن مضمن av_cold صحيح ff_چڪري_جاچ_init_x86(AVCRC *ctx, صحيح le, صحيح بٽ, uint32_t poly, صحيح ctx_سائيز)
{
#إذا HAVE_CLMUL_EXTERNAL
    صحيح cpu_flags = av_get_cpu_flags();

    إذا (EXTERNAL_CLMUL(cpu_flags)) {
        چڪري_جاچ_init_x86(ctx, le, بٽ, poly, ctx_سائيز);
        أرجع 1;
    }
#جيڪڏهن_پورو
    أرجع 0;
}

ساكن مضمن uint32_t ff_چڪري_جاچ_x86(ثابت AVCRC *ctx, uint32_t چڪري_جاچ,
                                  ثابت uint8_t *بفر, size_t ڊيگهائي)
{
    بدل (ctx[0]) {
#إذا HAVE_CLMUL_EXTERNAL
    حالة CLMUL_BE: أرجع ff_چڪري_جاچ_clmul(ctx, چڪري_جاچ, بفر, ڊيگهائي);
    حالة CLMUL_LE: أرجع ff_چڪري_جاچ_le_clmul(ctx, چڪري_جاچ, بفر, ڊيگهائي);
#جيڪڏهن_پورو
    افتراضي: av_unreachable("x86 CRC only uses CLMUL_BE and CLMUL_LE");
    }
    أرجع 0;
}

#جيڪڏهن_پورو /* AVUTIL_X86_CRC_H */
