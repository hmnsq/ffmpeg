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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_AARCH64_ਚੱਕਰੀ_ਜਾਂਚ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_AARCH64_ਚੱਕਰੀ_ਜਾਂਚ_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/crc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/intreadwrite.h"

#ਜੇ HAVE_ARM_ਚੱਕਰੀ_ਜਾਂਚ
FF_VISIBILITY_ਧੱਕੋ_HIDDEN
uint32_t ff_ਚੱਕਰੀ_ਜਾਂਚ_32_aarch64(ਅਚਲ AVCRC *ctx, uint32_t ਚੱਕਰੀ_ਜਾਂਚ, ਅਚਲ uint8_t *ਬਫਰ,
                          size_t ਲੰਮਾਈ);
FF_VISIBILITY_ਕੱਢੋ_HIDDEN
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_PMULL && HAVE_EOR3
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/crc_internal.h"

FF_VISIBILITY_ਧੱਕੋ_HIDDEN
uint32_t ff_ਚੱਕਰੀ_ਜਾਂਚ_neon_pmull(ਅਚਲ AVCRC *ctx, uint32_t ਚੱਕਰੀ_ਜਾਂਚ, ਅਚਲ uint8_t *ਬਫਰ,
                           size_t ਲੰਮਾਈ);
uint32_t ff_ਚੱਕਰੀ_ਜਾਂਚ_le_neon_pmull(ਅਚਲ AVCRC *ctx, uint32_t ਚੱਕਰੀ_ਜਾਂਚ, ਅਚਲ uint8_t *ਬਫਰ,
                              size_t ਲੰਮਾਈ);
FF_VISIBILITY_ਕੱਢੋ_HIDDEN

ਗਿਣਤੀ {
    ਚੱਕਰੀ_ਜਾਂਚ_C    = 0,
    PMULL_BE,
    PMULL_LE,
    ਚੱਕਰੀ_ਜਾਂਚ_32_PMULL_LE,
};

ਸਥਿਰ ਅਚਲ AVCRC ਚੱਕਰੀ_ਜਾਂਚ_ਸਾਰਣੀ_pmull[AV_ਚੱਕਰੀ_ਜਾਂਚ_MAX][17] = {
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_8_ATM] = {
        PMULL_BE,
        0xbc000000, 0x0, 0x32000000, 0x0,
        0x94000000, 0x0, 0xc4000000, 0x0,
        0x62000000, 0x0, 0x79000000, 0x0,
        0x07156a16, 0x1, 0x07000000, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_8_EBU] = {
        PMULL_BE,
        0xf3000000, 0x0, 0xb5000000, 0x0,
        0x0d000000, 0x0, 0xfc000000, 0x0,
        0x6a000000, 0x0, 0x65000000, 0x0,
        0x1c4b8192, 0x1, 0x1d000000, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_16_ANSI] = {
        PMULL_BE,
        0x807d0000, 0x0, 0xf9e30000, 0x0,
        0xff830000, 0x0, 0xf9130000, 0x0,
        0x807b0000, 0x0, 0x86630000, 0x0,
        0xfffbffe7, 0x1, 0x80050000, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_16_CCITT] = {
        PMULL_BE,
        0x59b00000, 0x0, 0x60190000, 0x0,
        0x45630000, 0x0, 0xd5f60000, 0x0,
        0xaa510000, 0x0, 0xeb230000, 0x0,
        0x11303471, 0x1, 0x10210000, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_24_IEEE] = {
        PMULL_BE,
        0x467d2400, 0x0, 0x1f428700, 0x0,
        0x64e4d700, 0x0, 0x2c8c9d00, 0x0,
        0xd9fe8c00, 0x0, 0xfd7e0c00, 0x0,
        0xf845fe24, 0x1, 0x864cfb00, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE] = {
        PMULL_BE,
        0xe6228b11, 0x0, 0x8833794c, 0x0,
        0xe8a45605, 0x0, 0xc5b9cd4c, 0x0,
        0x490d678d, 0x0, 0xf200aa66, 0x0,
        0x04d101df, 0x1, 0x04c11db7, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE_LE] = {
        PMULL_LE,
        0x54442bd4, 0x1, 0xc6e41596, 0x1,
        0x751997d0, 0x1, 0xccaa009e, 0x0,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_16_ANSI_LE] = {
        PMULL_LE,
        0x1b0c2, 0x0, 0x0000bffa, 0x0,
        0x1d0c2, 0x0, 0x00018cc2, 0x0,
        0x00018cc2, 0x0, 0x1bc02, 0x0,
        0xcfffbffe, 0x1, 0x14003, 0x0,
    },
};


ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ ਚੱਕਰੀ_ਜਾਂਚ_init_aarch64(AVCRC *ctx, ਪੂਰਨ le, ਪੂਰਨ ਬਿੱਟ, uint32_t poly, ਪੂਰਨ ctx_ਮਾਪ)
{
    uint64_t poly_;
    ਜੇ (le) {
        // convert the reversed representation to regular form
        poly = ਉਲਟ(poly, ਬਿੱਟ) >> 1;
    }
    // convert to 32 degree polynomial
    poly_ = ((uint64_t)poly) << (32 - ਬਿੱਟ);

    uint64_t div;
    uint8_t *dst = (uint8_t*)(ctx + 1);
    ਜੇ (le) {
        ctx[0] = PMULL_LE;
        AV_WN64(dst +  0, xnmodp(4 * 128 + 32, poly_, 32, &div, le));
        AV_WN64(dst +  8, xnmodp(4 * 128 - 32, poly_, 32, &div, le));
        uint64_t tmp = xnmodp(128 - 32, poly_, 32, &div, le);
        AV_WN64(dst + 16, xnmodp(128 + 32, poly_, 32, &div, le));
        AV_WN64(dst + 24, tmp);
        AV_WN64(dst + 32, tmp);
        AV_WN64(dst + 40, xnmodp(64, poly_, 32, &div, le));
        AV_WN64(dst + 48, div);
        AV_WN64(dst + 56, ਉਲਟ(poly_ | (1ULL << 32), 32));
    } ਨਹੀਂਤਾਂ {
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

#ਜੇ HAVE_ARM_ਚੱਕਰੀ_ਜਾਂਚ
FF_VISIBILITY_ਧੱਕੋ_HIDDEN
uint32_t ff_ਚੱਕਰੀ_ਜਾਂਚ_32_pmull_eor3_aarch64(ਅਚਲ AVCRC *ctx, uint32_t ਚੱਕਰੀ_ਜਾਂਚ, ਅਚਲ uint8_t *ਬਫਰ,
                                     size_t ਲੰਮਾਈ);
FF_VISIBILITY_ਕੱਢੋ_HIDDEN
ਸਥਿਰ ਅਚਲ AVCRC ਚੱਕਰੀ_ਜਾਂਚ_ਸਾਰਣੀ_ਚੱਕਰੀ_ਜਾਂਚ_32_pmull[] = {
        ਚੱਕਰੀ_ਜਾਂਚ_32_PMULL_LE,
        0x26b70c3d, 0x0, 0x3f41287a, 0x0,
        0xae689191, 0x0, 0xccaa009e, 0x0,
        0xf1da05aa, 0x0, 0x81256527, 0x0,
        0x8f352d95, 0x0, 0x1d9513d7, 0x0,
        0x54442bd4, 0x1, 0xc6e41596, 0x1,
        0x751997d0, 0x1, 0xccaa009e, 0x0,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
};
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਸਤਰਅੰਦਰ av_cold ਪੂਰਨ ff_ਚੱਕਰੀ_ਜਾਂਚ_init_aarch64(AVCRC *ctx, ਪੂਰਨ le, ਪੂਰਨ ਬਿੱਟ, uint32_t poly, ਪੂਰਨ ctx_ਮਾਪ)
{
#ਜੇ HAVE_PMULL && HAVE_EOR3
    ਪੂਰਨ cpu_flags = av_get_cpu_flags();

    ਜੇ (have_pmull(cpu_flags) && have_eor3(cpu_flags)) {
        ਚੱਕਰੀ_ਜਾਂਚ_init_aarch64(ctx, le, ਬਿੱਟ, poly, ctx_ਮਾਪ);
        ਵਾਪਸ 1;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ uint32_t ff_ਚੱਕਰੀ_ਜਾਂਚ_aarch64(ਅਚਲ AVCRC *ctx, uint32_t ਚੱਕਰੀ_ਜਾਂਚ,
                                      ਅਚਲ uint8_t *ਬਫਰ, size_t ਲੰਮਾਈ)
{
    ਚੋਣ (ctx[0]) {
#ਜੇ HAVE_PMULL && HAVE_EOR3
#ਜੇ HAVE_ARM_ਚੱਕਰੀ_ਜਾਂਚ
    ਹਾਲਤ ਚੱਕਰੀ_ਜਾਂਚ_32_PMULL_LE: ਵਾਪਸ ff_ਚੱਕਰੀ_ਜਾਂਚ_32_pmull_eor3_aarch64(ctx, ਚੱਕਰੀ_ਜਾਂਚ, ਬਫਰ, ਲੰਮਾਈ);
#ਜੇ_ਅੰਤ
    ਹਾਲਤ PMULL_BE: ਵਾਪਸ ff_ਚੱਕਰੀ_ਜਾਂਚ_neon_pmull(ctx, ਚੱਕਰੀ_ਜਾਂਚ, ਬਫਰ, ਲੰਮਾਈ);
    ਹਾਲਤ PMULL_LE: ਵਾਪਸ ff_ਚੱਕਰੀ_ਜਾਂਚ_le_neon_pmull(ctx, ਚੱਕਰੀ_ਜਾਂਚ, ਬਫਰ, ਲੰਮਾਈ);
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_ARM_ਚੱਕਰੀ_ਜਾਂਚ
    ਹਾਲਤ (AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE_LE + 1): ਵਾਪਸ ff_ਚੱਕਰੀ_ਜਾਂਚ_32_aarch64(ctx, ਚੱਕਰੀ_ਜਾਂਚ, ਬਫਰ, ਲੰਮਾਈ);
#ਜੇ_ਅੰਤ
    ਮੂਲ: av_unreachable("AARCH64 has PMULL_LE, PMULL_BE, CRC32_PMULL_LE, and AV_CRC_32_IEEE_LE arch-specific CRC code");
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਅਚਲ AVCRC *ff_ਚੱਕਰੀ_ਜਾਂਚ_get_ਸਾਰਣੀ_aarch64(AVCRCId ਚੱਕਰੀ_ਜਾਂਚ_id)
{
    ਪੂਰਨ cpu_flags = av_get_cpu_flags();
#ਜੇ HAVE_PMULL && HAVE_EOR3
    ਜੇ (have_pmull(cpu_flags) && have_eor3(cpu_flags)) {
#ਜੇ HAVE_ARM_ਚੱਕਰੀ_ਜਾਂਚ
        ਜੇ (ਚੱਕਰੀ_ਜਾਂਚ_id == AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE_LE && have_arm_ਚੱਕਰੀ_ਜਾਂਚ(cpu_flags)) {
            ਵਾਪਸ ਚੱਕਰੀ_ਜਾਂਚ_ਸਾਰਣੀ_ਚੱਕਰੀ_ਜਾਂਚ_32_pmull;
        }
#ਜੇ_ਅੰਤ
        ਵਾਪਸ ਚੱਕਰੀ_ਜਾਂਚ_ਸਾਰਣੀ_pmull[ਚੱਕਰੀ_ਜਾਂਚ_id];
    }
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_ARM_ਚੱਕਰੀ_ਜਾਂਚ
    ਸਥਿਰ ਅਚਲ AVCRC ਚੱਕਰੀ_ਜਾਂਚ_32_ieee_le_ctx[] = {
        AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE_LE + 1
    };

    ਜੇ (ਚੱਕਰੀ_ਜਾਂਚ_id != AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE_LE)
        ਵਾਪਸ ਨਿਰਾ;

    ਜੇ (have_arm_ਚੱਕਰੀ_ਜਾਂਚ(cpu_flags)) {
        ਵਾਪਸ ਚੱਕਰੀ_ਜਾਂਚ_32_ieee_le_ctx;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ ਨਿਰਾ;
}

#ਜੇ_ਅੰਤ /* AVUTIL_AARCH64_CRC_H */
