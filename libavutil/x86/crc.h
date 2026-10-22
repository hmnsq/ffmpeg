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

#ifndef AVUTIL_X86_CRC_H
#define AVUTIL_X86_CRC_H

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes_internal.h"
#ಅನ್ತರ್ಭಾವ "libavutil/avassert.h"
#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/crc.h"
#ಅನ್ತರ್ಭಾವ "libavutil/intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "libavutil/x86/cpu.h"

#ಯದಿ HAVE_CLMUL_EXTERNAL
#ಅನ್ತರ್ಭಾವ "libavutil/crc_internal.h"

FF_VISIBILITY_ತಳ್ಳು_HIDDEN
uint32_t ff_crc_clmul(ಧ್ರುವ AVCRC *ctx, uint32_t crc,
                      ಧ್ರುವ uint8_t *buffer, size_t length);
uint32_t ff_crc_le_clmul(ಧ್ರುವ AVCRC *ctx, uint32_t crc,
                         ಧ್ರುವ uint8_t *buffer, size_t length);
FF_VISIBILITY_ತೆಗೆ_HIDDEN

ಗಣನಾ {
    CRC_C    = 0,
    CLMUL_BE,
    CLMUL_LE,
};

ಸ್ಥಿರ ಧ್ರುವ AVCRC crc_table_clmul[AV_CRC_MAX][17] = {
    [AV_CRC_8_ATM] = {
        CLMUL_BE,
        0x32000000, 0x0, 0xbc000000, 0x0,
        0xc4000000, 0x0, 0x94000000, 0x0,
        0x62000000, 0x0, 0x79000000, 0x0,
        0x07156a16, 0x1, 0x07000000, 0x1,
    },
    [AV_CRC_8_EBU] = {
        CLMUL_BE,
        0xb5000000, 0x0, 0xf3000000, 0x0,
        0xfc000000, 0x0, 0x0d000000, 0x0,
        0x6a000000, 0x0, 0x65000000, 0x0,
        0x1c4b8192, 0x1, 0x1d000000, 0x1,
    },
    [AV_CRC_16_ANSI] = {
        CLMUL_BE,
        0xf9e30000, 0x0, 0x807d0000, 0x0,
        0xf9130000, 0x0, 0xff830000, 0x0,
        0x807b0000, 0x0, 0x86630000, 0x0,
        0xfffbffe7, 0x1, 0x80050000, 0x1,
    },
    [AV_CRC_16_CCITT] = {
        CLMUL_BE,
        0x60190000, 0x0, 0x59b00000, 0x0,
        0xd5f60000, 0x0, 0x45630000, 0x0,
        0xaa510000, 0x0, 0xeb230000, 0x0,
        0x11303471, 0x1, 0x10210000, 0x1,
    },
    [AV_CRC_24_IEEE] = {
        CLMUL_BE,
        0x1f428700, 0x0, 0x467d2400, 0x0,
        0x2c8c9d00, 0x0, 0x64e4d700, 0x0,
        0xd9fe8c00, 0x0, 0xfd7e0c00, 0x0,
        0xf845fe24, 0x1, 0x864cfb00, 0x1,
    },
    [AV_CRC_32_IEEE] = {
        CLMUL_BE,
        0x8833794c, 0x0, 0xe6228b11, 0x0,
        0xc5b9cd4c, 0x0, 0xe8a45605, 0x0,
        0x490d678d, 0x0, 0xf200aa66, 0x0,
        0x04d101df, 0x1, 0x04c11db7, 0x1,
    },
    [AV_CRC_32_IEEE_LE] = {
        CLMUL_LE,
        0xc6e41596, 0x1, 0x54442bd4, 0x1,
        0xccaa009e, 0x0, 0x751997d0, 0x1,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
    },
    [AV_CRC_16_ANSI_LE] = {
        CLMUL_LE,
        0x0000bffa, 0x0, 0x1b0c2, 0x0,
        0x00018cc2, 0x0, 0x1d0c2, 0x0,
        0x00018cc2, 0x0, 0x1bc02, 0x0,
        0xcfffbffe, 0x1, 0x14003, 0x0,
    },
};

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ crc_init_x86(AVCRC *ctx, ಪೂರ್ಣಾಙ್ಕ le, ಪೂರ್ಣಾಙ್ಕ bits, uint32_t poly, ಪೂರ್ಣಾಙ್ಕ ctx_size)
{
    uint64_t poly_;
    ಯದಿ (le) {
        // convert the reversed representation to regular form
        poly = reverse(poly, bits) >> 1;
    }
    // convert to 32 degree polynomial
    poly_ = ((uint64_t)poly) << (32 - bits);

    uint64_t div;
    uint8_t *dst = (uint8_t*)(ctx + 1);
    ಯದಿ (le) {
        ctx[0] = CLMUL_LE;
        AV_WN64(dst,      xnmodp(4 * 128 - 32, poly_, 32, &div, le));
        AV_WN64(dst +  8, xnmodp(4 * 128 + 32, poly_, 32, &div, le));
        uint64_t tmp = xnmodp(128 - 32, poly_, 32, &div, le);
        AV_WN64(dst + 16, tmp);
        AV_WN64(dst + 24, xnmodp(128 + 32, poly_, 32, &div, le));
        AV_WN64(dst + 32, tmp);
        AV_WN64(dst + 40, xnmodp(64, poly_, 32, &div, le));
        AV_WN64(dst + 48, div);
        AV_WN64(dst + 56, reverse(poly_ | (1ULL << 32), 32));
    } ಅನ್ಯಥಾ {
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
#endif

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಧ್ರುವ AVCRC *ff_crc_get_table_x86(AVCRCId crc_id)
{
#ಯದಿ HAVE_CLMUL_EXTERNAL
    ಪೂರ್ಣಾಙ್ಕ cpu_flags = av_get_cpu_flags();

    ಯದಿ (EXTERNAL_CLMUL(cpu_flags)) {
        ಪ್ರತ್ಯಾಗಮ crc_table_clmul[crc_id];
    }
#endif
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ av_cold ಪೂರ್ಣಾಙ್ಕ ff_crc_init_x86(AVCRC *ctx, ಪೂರ್ಣಾಙ್ಕ le, ಪೂರ್ಣಾಙ್ಕ bits, uint32_t poly, ಪೂರ್ಣಾಙ್ಕ ctx_size)
{
#ಯದಿ HAVE_CLMUL_EXTERNAL
    ಪೂರ್ಣಾಙ್ಕ cpu_flags = av_get_cpu_flags();

    ಯದಿ (EXTERNAL_CLMUL(cpu_flags)) {
        crc_init_x86(ctx, le, bits, poly, ctx_size);
        ಪ್ರತ್ಯಾಗಮ 1;
    }
#endif
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ uint32_t ff_crc_x86(ಧ್ರುವ AVCRC *ctx, uint32_t crc,
                                  ಧ್ರುವ uint8_t *buffer, size_t length)
{
    ವಿಕಲ್ಪ (ctx[0]) {
#ಯದಿ HAVE_CLMUL_EXTERNAL
    ಪಕ್ಷ CLMUL_BE: ಪ್ರತ್ಯಾಗಮ ff_crc_clmul(ctx, crc, buffer, length);
    ಪಕ್ಷ CLMUL_LE: ಪ್ರತ್ಯಾಗಮ ff_crc_le_clmul(ctx, crc, buffer, length);
#endif
    ಸ್ವಭಾವ: av_unreachable("x86 CRC only uses CLMUL_BE and CLMUL_LE");
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

#endif /* AVUTIL_X86_CRC_H */
