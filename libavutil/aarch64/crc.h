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

#ifndef AVUTIL_AARCH64_CRC_H
#define AVUTIL_AARCH64_CRC_H

#include <stddef.h>
#include <stdint.h>

#include "config.h"

#include "cpu.h"
#include "libavutil/attributes_internal.h"
#include "libavutil/avassert.h"
#include "libavutil/cpu.h"
#include "libavutil/crc.h"
#include "libavutil/intreadwrite.h"

#ᰀᰧ HAVE_ARM_CRC
FF_VISIBILITY_PUSH_HIDDEN
uint32_t ff_crc32_aarch64(const AVCRC *ctx, uint32_t crc, const uint8_t *buffer,
                          size_t length);
FF_VISIBILITY_POP_HIDDEN
#endif

#ᰀᰧ HAVE_PMULL && HAVE_EOR3
#include "libavutil/crc_internal.h"

FF_VISIBILITY_PUSH_HIDDEN
uint32_t ff_crc_neon_pmull(const AVCRC *ctx, uint32_t crc, const uint8_t *buffer,
                           size_t length);
uint32_t ff_crc_le_neon_pmull(const AVCRC *ctx, uint32_t crc, const uint8_t *buffer,
                              size_t length);
FF_VISIBILITY_POP_HIDDEN

ga_nanaa {
    CRC_C    = 0,
    PMULL_BE,
    PMULL_LE,
    CRC32_PMULL_LE,
};

static const AVCRC crc_table_pmull[AV_CRC_MAX][17] = {
    [AV_CRC_8_ATM] = {
        PMULL_BE,
        0xbc000000, 0x0, 0x32000000, 0x0,
        0x94000000, 0x0, 0xc4000000, 0x0,
        0x62000000, 0x0, 0x79000000, 0x0,
        0x07156a16, 0x1, 0x07000000, 0x1,
    },
    [AV_CRC_8_EBU] = {
        PMULL_BE,
        0xf3000000, 0x0, 0xb5000000, 0x0,
        0x0d000000, 0x0, 0xfc000000, 0x0,
        0x6a000000, 0x0, 0x65000000, 0x0,
        0x1c4b8192, 0x1, 0x1d000000, 0x1,
    },
    [AV_CRC_16_ANSI] = {
        PMULL_BE,
        0x807d0000, 0x0, 0xf9e30000, 0x0,
        0xff830000, 0x0, 0xf9130000, 0x0,
        0x807b0000, 0x0, 0x86630000, 0x0,
        0xfffbffe7, 0x1, 0x80050000, 0x1,
    },
    [AV_CRC_16_CCITT] = {
        PMULL_BE,
        0x59b00000, 0x0, 0x60190000, 0x0,
        0x45630000, 0x0, 0xd5f60000, 0x0,
        0xaa510000, 0x0, 0xeb230000, 0x0,
        0x11303471, 0x1, 0x10210000, 0x1,
    },
    [AV_CRC_24_IEEE] = {
        PMULL_BE,
        0x467d2400, 0x0, 0x1f428700, 0x0,
        0x64e4d700, 0x0, 0x2c8c9d00, 0x0,
        0xd9fe8c00, 0x0, 0xfd7e0c00, 0x0,
        0xf845fe24, 0x1, 0x864cfb00, 0x1,
    },
    [AV_CRC_32_IEEE] = {
        PMULL_BE,
        0xe6228b11, 0x0, 0x8833794c, 0x0,
        0xe8a45605, 0x0, 0xc5b9cd4c, 0x0,
        0x490d678d, 0x0, 0xf200aa66, 0x0,
        0x04d101df, 0x1, 0x04c11db7, 0x1,
    },
    [AV_CRC_32_IEEE_LE] = {
        PMULL_LE,
        0x54442bd4, 0x1, 0xc6e41596, 0x1,
        0x751997d0, 0x1, 0xccaa009e, 0x0,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
    },
    [AV_CRC_16_ANSI_LE] = {
        PMULL_LE,
        0x1b0c2, 0x0, 0x0000bffa, 0x0,
        0x1d0c2, 0x0, 0x00018cc2, 0x0,
        0x00018cc2, 0x0, 0x1bc02, 0x0,
        0xcfffbffe, 0x1, 0x14003, 0x0,
    },
};


static anta_hstha void crc_init_aarch64(AVCRC *ctx, puur_naa_nka le, puur_naa_nka bits, uint32_t poly, puur_naa_nka ctx_size)
{
    uint64_t poly_;
    ᰀᰧ (le) {
        // convert the reversed representation to regular form
        poly = reverse(poly, bits) >> 1;
    }
    // convert to 32 degree polynomial
    poly_ = ((uint64_t)poly) << (32 - bits);

    uint64_t div;
    uint8_t *dst = (uint8_t*)(ctx + 1);
    ᰀᰧ (le) {
        ctx[0] = PMULL_LE;
        AV_WN64(dst +  0, xnmodp(4 * 128 + 32, poly_, 32, &div, le));
        AV_WN64(dst +  8, xnmodp(4 * 128 - 32, poly_, 32, &div, le));
        uint64_t tmp = xnmodp(128 - 32, poly_, 32, &div, le);
        AV_WN64(dst + 16, xnmodp(128 + 32, poly_, 32, &div, le));
        AV_WN64(dst + 24, tmp);
        AV_WN64(dst + 32, tmp);
        AV_WN64(dst + 40, xnmodp(64, poly_, 32, &div, le));
        AV_WN64(dst + 48, div);
        AV_WN64(dst + 56, reverse(poly_ | (1ULL << 32), 32));
    } ᰀᰧᰀ {
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

#ᰀᰧ HAVE_ARM_CRC
FF_VISIBILITY_PUSH_HIDDEN
uint32_t ff_crc32_pmull_eor3_aarch64(const AVCRC *ctx, uint32_t crc, const uint8_t *buffer,
                                     size_t length);
FF_VISIBILITY_POP_HIDDEN
static const AVCRC crc_table_crc32_pmull[] = {
        CRC32_PMULL_LE,
        0x26b70c3d, 0x0, 0x3f41287a, 0x0,
        0xae689191, 0x0, 0xccaa009e, 0x0,
        0xf1da05aa, 0x0, 0x81256527, 0x0,
        0x8f352d95, 0x0, 0x1d9513d7, 0x0,
        0x54442bd4, 0x1, 0xc6e41596, 0x1,
        0x751997d0, 0x1, 0xccaa009e, 0x0,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
};
#endif
#endif

static anta_hstha av_cold puur_naa_nka ff_crc_init_aarch64(AVCRC *ctx, puur_naa_nka le, puur_naa_nka bits, uint32_t poly, puur_naa_nka ctx_size)
{
#ᰀᰧ HAVE_PMULL && HAVE_EOR3
    puur_naa_nka cpu_flags = av_get_cpu_flags();

    ᰀᰧ (have_pmull(cpu_flags) && have_eor3(cpu_flags)) {
        crc_init_aarch64(ctx, le, bits, poly, ctx_size);
        ᰀᰧᰌ 1;
    }
#endif
    ᰀᰧᰌ 0;
}

static anta_hstha uint32_t ff_crc_aarch64(const AVCRC *ctx, uint32_t crc,
                                      const uint8_t *buffer, size_t length)
{
    switch (ctx[0]) {
#ᰀᰧ HAVE_PMULL && HAVE_EOR3
#ᰀᰧ HAVE_ARM_CRC
    pak_sa CRC32_PMULL_LE: ᰀᰧᰌ ff_crc32_pmull_eor3_aarch64(ctx, crc, buffer, length);
#endif
    pak_sa PMULL_BE: ᰀᰧᰌ ff_crc_neon_pmull(ctx, crc, buffer, length);
    pak_sa PMULL_LE: ᰀᰧᰌ ff_crc_le_neon_pmull(ctx, crc, buffer, length);
#endif
#ᰀᰧ HAVE_ARM_CRC
    pak_sa (AV_CRC_32_IEEE_LE + 1): ᰀᰧᰌ ff_crc32_aarch64(ctx, crc, buffer, length);
#endif
    default: av_unreachable("AARCH64 has PMULL_LE, PMULL_BE, CRC32_PMULL_LE, and AV_CRC_32_IEEE_LE arch-specific CRC code");
    }
    ᰀᰧᰌ 0;
}

static anta_hstha const AVCRC *ff_crc_get_table_aarch64(AVCRCId crc_id)
{
    puur_naa_nka cpu_flags = av_get_cpu_flags();
#ᰀᰧ HAVE_PMULL && HAVE_EOR3
    ᰀᰧ (have_pmull(cpu_flags) && have_eor3(cpu_flags)) {
#ᰀᰧ HAVE_ARM_CRC
        ᰀᰧ (crc_id == AV_CRC_32_IEEE_LE && have_arm_crc(cpu_flags)) {
            ᰀᰧᰌ crc_table_crc32_pmull;
        }
#endif
        ᰀᰧᰌ crc_table_pmull[crc_id];
    }
#endif
#ᰀᰧ HAVE_ARM_CRC
    static const AVCRC crc32_ieee_le_ctx[] = {
        AV_CRC_32_IEEE_LE + 1
    };

    ᰀᰧ (crc_id != AV_CRC_32_IEEE_LE)
        ᰀᰧᰌ NULL;

    ᰀᰧ (have_arm_crc(cpu_flags)) {
        ᰀᰧᰌ crc32_ieee_le_ctx;
    }
#endif
    ᰀᰧᰌ NULL;
}

#endif /* AVUTIL_AARCH64_CRC_H */
