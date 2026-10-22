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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_AARCH64_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_AARCH64_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_H

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ "cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes_internal.h"
#ಅನ್ತರ್ಭಾವ "libavutil/avassert.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/crc.h"
#ಅನ್ತರ್ಭಾವ "libavutil/intreadwrite.h"

#ಆದರೆ HAVE_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ
FF_VISIBILITY_ತಳ್ಳು_HIDDEN
uint32_t ff_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_aarch64(ಸ್ಥಿರಾಂಕ AVCRC *ctx, uint32_t ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, ಸ್ಥಿರಾಂಕ uint8_t *ಬಫರ್,
                          size_t ಉದ್ದಳತೆ);
FF_VISIBILITY_ತೆಗೆ_HIDDEN
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_PMULL && HAVE_EOR3
#ಅನ್ತರ್ಭಾವ "libavutil/crc_internal.h"

FF_VISIBILITY_ತಳ್ಳು_HIDDEN
uint32_t ff_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_neon_pmull(ಸ್ಥಿರಾಂಕ AVCRC *ctx, uint32_t ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, ಸ್ಥಿರಾಂಕ uint8_t *ಬಫರ್,
                           size_t ಉದ್ದಳತೆ);
uint32_t ff_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_le_neon_pmull(ಸ್ಥಿರಾಂಕ AVCRC *ctx, uint32_t ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, ಸ್ಥಿರಾಂಕ uint8_t *ಬಫರ್,
                              size_t ಉದ್ದಳತೆ);
FF_VISIBILITY_ತೆಗೆ_HIDDEN

ಎಣಿಕೆ {
    ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_C    = 0,
    PMULL_BE,
    PMULL_LE,
    ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_PMULL_LE,
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVCRC ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_ಕೋಷ್ಟಕ_pmull[AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_MAX][17] = {
    [AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_8_ATM] = {
        PMULL_BE,
        0xbc000000, 0x0, 0x32000000, 0x0,
        0x94000000, 0x0, 0xc4000000, 0x0,
        0x62000000, 0x0, 0x79000000, 0x0,
        0x07156a16, 0x1, 0x07000000, 0x1,
    },
    [AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_8_EBU] = {
        PMULL_BE,
        0xf3000000, 0x0, 0xb5000000, 0x0,
        0x0d000000, 0x0, 0xfc000000, 0x0,
        0x6a000000, 0x0, 0x65000000, 0x0,
        0x1c4b8192, 0x1, 0x1d000000, 0x1,
    },
    [AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_16_ANSI] = {
        PMULL_BE,
        0x807d0000, 0x0, 0xf9e30000, 0x0,
        0xff830000, 0x0, 0xf9130000, 0x0,
        0x807b0000, 0x0, 0x86630000, 0x0,
        0xfffbffe7, 0x1, 0x80050000, 0x1,
    },
    [AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_16_CCITT] = {
        PMULL_BE,
        0x59b00000, 0x0, 0x60190000, 0x0,
        0x45630000, 0x0, 0xd5f60000, 0x0,
        0xaa510000, 0x0, 0xeb230000, 0x0,
        0x11303471, 0x1, 0x10210000, 0x1,
    },
    [AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_24_IEEE] = {
        PMULL_BE,
        0x467d2400, 0x0, 0x1f428700, 0x0,
        0x64e4d700, 0x0, 0x2c8c9d00, 0x0,
        0xd9fe8c00, 0x0, 0xfd7e0c00, 0x0,
        0xf845fe24, 0x1, 0x864cfb00, 0x1,
    },
    [AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE] = {
        PMULL_BE,
        0xe6228b11, 0x0, 0x8833794c, 0x0,
        0xe8a45605, 0x0, 0xc5b9cd4c, 0x0,
        0x490d678d, 0x0, 0xf200aa66, 0x0,
        0x04d101df, 0x1, 0x04c11db7, 0x1,
    },
    [AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE_LE] = {
        PMULL_LE,
        0x54442bd4, 0x1, 0xc6e41596, 0x1,
        0x751997d0, 0x1, 0xccaa009e, 0x0,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
    },
    [AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_16_ANSI_LE] = {
        PMULL_LE,
        0x1b0c2, 0x0, 0x0000bffa, 0x0,
        0x1d0c2, 0x0, 0x00018cc2, 0x0,
        0x00018cc2, 0x0, 0x1bc02, 0x0,
        0xcfffbffe, 0x1, 0x14003, 0x0,
    },
};


ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_init_aarch64(AVCRC *ctx, ಪೂರ್ಣಾಂಕ le, ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು, uint32_t poly, ಪೂರ್ಣಾಂಕ ctx_ಗಾತ್ರ)
{
    uint64_t poly_;
    ಆದರೆ (le) {
        // convert the reversed representation to regular form
        poly = ಹಿಮ್ಮುಖ(poly, ಬಿಟ್ಟುಗಳು) >> 1;
    }
    // convert to 32 degree polynomial
    poly_ = ((uint64_t)poly) << (32 - ಬಿಟ್ಟುಗಳು);

    uint64_t div;
    uint8_t *dst = (uint8_t*)(ctx + 1);
    ಆದರೆ (le) {
        ctx[0] = PMULL_LE;
        AV_WN64(dst +  0, xnmodp(4 * 128 + 32, poly_, 32, &div, le));
        AV_WN64(dst +  8, xnmodp(4 * 128 - 32, poly_, 32, &div, le));
        uint64_t tmp = xnmodp(128 - 32, poly_, 32, &div, le);
        AV_WN64(dst + 16, xnmodp(128 + 32, poly_, 32, &div, le));
        AV_WN64(dst + 24, tmp);
        AV_WN64(dst + 32, tmp);
        AV_WN64(dst + 40, xnmodp(64, poly_, 32, &div, le));
        AV_WN64(dst + 48, div);
        AV_WN64(dst + 56, ಹಿಮ್ಮುಖ(poly_ | (1ULL << 32), 32));
    } ಇಲ್ಲದಿದ್ದರೆ {
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

#ಆದರೆ HAVE_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ
FF_VISIBILITY_ತಳ್ಳು_HIDDEN
uint32_t ff_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_pmull_eor3_aarch64(ಸ್ಥಿರಾಂಕ AVCRC *ctx, uint32_t ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, ಸ್ಥಿರಾಂಕ uint8_t *ಬಫರ್,
                                     size_t ಉದ್ದಳತೆ);
FF_VISIBILITY_ತೆಗೆ_HIDDEN
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVCRC ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_ಕೋಷ್ಟಕ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_pmull[] = {
        ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_PMULL_LE,
        0x26b70c3d, 0x0, 0x3f41287a, 0x0,
        0xae689191, 0x0, 0xccaa009e, 0x0,
        0xf1da05aa, 0x0, 0x81256527, 0x0,
        0x8f352d95, 0x0, 0x1d9513d7, 0x0,
        0x54442bd4, 0x1, 0xc6e41596, 0x1,
        0x751997d0, 0x1, 0xccaa009e, 0x0,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
};
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಸಾಲೊಳಗೆ av_cold ಪೂರ್ಣಾಂಕ ff_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_init_aarch64(AVCRC *ctx, ಪೂರ್ಣಾಂಕ le, ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು, uint32_t poly, ಪೂರ್ಣಾಂಕ ctx_ಗಾತ್ರ)
{
#ಆದರೆ HAVE_PMULL && HAVE_EOR3
    ಪೂರ್ಣಾಂಕ cpu_flags = av_get_cpu_flags();

    ಆದರೆ (have_pmull(cpu_flags) && have_eor3(cpu_flags)) {
        ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_init_aarch64(ctx, le, ಬಿಟ್ಟುಗಳು, poly, ctx_ಗಾತ್ರ);
        ಹಿಂತಿರುಗಿ 1;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint32_t ff_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_aarch64(ಸ್ಥಿರಾಂಕ AVCRC *ctx, uint32_t ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ,
                                      ಸ್ಥಿರಾಂಕ uint8_t *ಬಫರ್, size_t ಉದ್ದಳತೆ)
{
    ಆಯ್ಕೆ (ctx[0]) {
#ಆದರೆ HAVE_PMULL && HAVE_EOR3
#ಆದರೆ HAVE_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ
    ಸ್ಥಿತಿ ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_PMULL_LE: ಹಿಂತಿರುಗಿ ff_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_pmull_eor3_aarch64(ctx, ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, ಬಫರ್, ಉದ್ದಳತೆ);
#ಆದರೆ_ಅಂತ್ಯ
    ಸ್ಥಿತಿ PMULL_BE: ಹಿಂತಿರುಗಿ ff_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_neon_pmull(ctx, ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, ಬಫರ್, ಉದ್ದಳತೆ);
    ಸ್ಥಿತಿ PMULL_LE: ಹಿಂತಿರುಗಿ ff_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_le_neon_pmull(ctx, ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, ಬಫರ್, ಉದ್ದಳತೆ);
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ
    ಸ್ಥಿತಿ (AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE_LE + 1): ಹಿಂತಿರುಗಿ ff_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_aarch64(ctx, ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, ಬಫರ್, ಉದ್ದಳತೆ);
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ: av_unreachable("AARCH64 has PMULL_LE, PMULL_BE, CRC32_PMULL_LE, and AV_CRC_32_IEEE_LE arch-specific CRC code");
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಸ್ಥಿರಾಂಕ AVCRC *ff_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_get_ಕೋಷ್ಟಕ_aarch64(AVCRCId ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_id)
{
    ಪೂರ್ಣಾಂಕ cpu_flags = av_get_cpu_flags();
#ಆದರೆ HAVE_PMULL && HAVE_EOR3
    ಆದರೆ (have_pmull(cpu_flags) && have_eor3(cpu_flags)) {
#ಆದರೆ HAVE_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ
        ಆದರೆ (ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_id == AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE_LE && have_arm_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ(cpu_flags)) {
            ಹಿಂತಿರುಗಿ ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_ಕೋಷ್ಟಕ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_pmull;
        }
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_ಕೋಷ್ಟಕ_pmull[ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_id];
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVCRC ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_ieee_le_ctx[] = {
        AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE_LE + 1
    };

    ಆದರೆ (ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_id != AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE_LE)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಆದರೆ (have_arm_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ(cpu_flags)) {
        ಹಿಂತಿರುಗಿ ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_ieee_le_ctx;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_AARCH64_CRC_H */
