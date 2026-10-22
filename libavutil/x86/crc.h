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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_X86_ਚੱਕਰੀ_ਜਾਂਚ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_X86_ਚੱਕਰੀ_ਜਾਂਚ_H

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/crc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/intreadwrite.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/x86/cpu.h"

#ਜੇ HAVE_CLMUL_EXTERNAL
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/crc_internal.h"

FF_VISIBILITY_ਧੱਕੋ_HIDDEN
uint32_t ff_ਚੱਕਰੀ_ਜਾਂਚ_clmul(ਅਚਲ AVCRC *ctx, uint32_t ਚੱਕਰੀ_ਜਾਂਚ,
                      ਅਚਲ uint8_t *ਬਫਰ, size_t ਲੰਮਾਈ);
uint32_t ff_ਚੱਕਰੀ_ਜਾਂਚ_le_clmul(ਅਚਲ AVCRC *ctx, uint32_t ਚੱਕਰੀ_ਜਾਂਚ,
                         ਅਚਲ uint8_t *ਬਫਰ, size_t ਲੰਮਾਈ);
FF_VISIBILITY_ਕੱਢੋ_HIDDEN

ਗਿਣਤੀ {
    ਚੱਕਰੀ_ਜਾਂਚ_C    = 0,
    CLMUL_BE,
    CLMUL_LE,
};

ਸਥਿਰ ਅਚਲ AVCRC ਚੱਕਰੀ_ਜਾਂਚ_ਸਾਰਣੀ_clmul[AV_ਚੱਕਰੀ_ਜਾਂਚ_MAX][17] = {
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_8_ATM] = {
        CLMUL_BE,
        0x32000000, 0x0, 0xbc000000, 0x0,
        0xc4000000, 0x0, 0x94000000, 0x0,
        0x62000000, 0x0, 0x79000000, 0x0,
        0x07156a16, 0x1, 0x07000000, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_8_EBU] = {
        CLMUL_BE,
        0xb5000000, 0x0, 0xf3000000, 0x0,
        0xfc000000, 0x0, 0x0d000000, 0x0,
        0x6a000000, 0x0, 0x65000000, 0x0,
        0x1c4b8192, 0x1, 0x1d000000, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_16_ANSI] = {
        CLMUL_BE,
        0xf9e30000, 0x0, 0x807d0000, 0x0,
        0xf9130000, 0x0, 0xff830000, 0x0,
        0x807b0000, 0x0, 0x86630000, 0x0,
        0xfffbffe7, 0x1, 0x80050000, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_16_CCITT] = {
        CLMUL_BE,
        0x60190000, 0x0, 0x59b00000, 0x0,
        0xd5f60000, 0x0, 0x45630000, 0x0,
        0xaa510000, 0x0, 0xeb230000, 0x0,
        0x11303471, 0x1, 0x10210000, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_24_IEEE] = {
        CLMUL_BE,
        0x1f428700, 0x0, 0x467d2400, 0x0,
        0x2c8c9d00, 0x0, 0x64e4d700, 0x0,
        0xd9fe8c00, 0x0, 0xfd7e0c00, 0x0,
        0xf845fe24, 0x1, 0x864cfb00, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE] = {
        CLMUL_BE,
        0x8833794c, 0x0, 0xe6228b11, 0x0,
        0xc5b9cd4c, 0x0, 0xe8a45605, 0x0,
        0x490d678d, 0x0, 0xf200aa66, 0x0,
        0x04d101df, 0x1, 0x04c11db7, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE_LE] = {
        CLMUL_LE,
        0xc6e41596, 0x1, 0x54442bd4, 0x1,
        0xccaa009e, 0x0, 0x751997d0, 0x1,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
    },
    [AV_ਚੱਕਰੀ_ਜਾਂਚ_16_ANSI_LE] = {
        CLMUL_LE,
        0x0000bffa, 0x0, 0x1b0c2, 0x0,
        0x00018cc2, 0x0, 0x1d0c2, 0x0,
        0x00018cc2, 0x0, 0x1bc02, 0x0,
        0xcfffbffe, 0x1, 0x14003, 0x0,
    },
};

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ ਚੱਕਰੀ_ਜਾਂਚ_init_x86(AVCRC *ctx, ਪੂਰਨ le, ਪੂਰਨ ਬਿੱਟ, uint32_t poly, ਪੂਰਨ ctx_ਮਾਪ)
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
        ctx[0] = CLMUL_LE;
        AV_WN64(dst,      xnmodp(4 * 128 - 32, poly_, 32, &div, le));
        AV_WN64(dst +  8, xnmodp(4 * 128 + 32, poly_, 32, &div, le));
        uint64_t tmp = xnmodp(128 - 32, poly_, 32, &div, le);
        AV_WN64(dst + 16, tmp);
        AV_WN64(dst + 24, xnmodp(128 + 32, poly_, 32, &div, le));
        AV_WN64(dst + 32, tmp);
        AV_WN64(dst + 40, xnmodp(64, poly_, 32, &div, le));
        AV_WN64(dst + 48, div);
        AV_WN64(dst + 56, ਉਲਟ(poly_ | (1ULL << 32), 32));
    } ਨਹੀਂਤਾਂ {
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
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਸਤਰਅੰਦਰ ਅਚਲ AVCRC *ff_ਚੱਕਰੀ_ਜਾਂਚ_get_ਸਾਰਣੀ_x86(AVCRCId ਚੱਕਰੀ_ਜਾਂਚ_id)
{
#ਜੇ HAVE_CLMUL_EXTERNAL
    ਪੂਰਨ cpu_flags = av_get_cpu_flags();

    ਜੇ (EXTERNAL_CLMUL(cpu_flags)) {
        ਵਾਪਸ ਚੱਕਰੀ_ਜਾਂਚ_ਸਾਰਣੀ_clmul[ਚੱਕਰੀ_ਜਾਂਚ_id];
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ av_cold ਪੂਰਨ ff_ਚੱਕਰੀ_ਜਾਂਚ_init_x86(AVCRC *ctx, ਪੂਰਨ le, ਪੂਰਨ ਬਿੱਟ, uint32_t poly, ਪੂਰਨ ctx_ਮਾਪ)
{
#ਜੇ HAVE_CLMUL_EXTERNAL
    ਪੂਰਨ cpu_flags = av_get_cpu_flags();

    ਜੇ (EXTERNAL_CLMUL(cpu_flags)) {
        ਚੱਕਰੀ_ਜਾਂਚ_init_x86(ctx, le, ਬਿੱਟ, poly, ctx_ਮਾਪ);
        ਵਾਪਸ 1;
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ uint32_t ff_ਚੱਕਰੀ_ਜਾਂਚ_x86(ਅਚਲ AVCRC *ctx, uint32_t ਚੱਕਰੀ_ਜਾਂਚ,
                                  ਅਚਲ uint8_t *ਬਫਰ, size_t ਲੰਮਾਈ)
{
    ਚੋਣ (ctx[0]) {
#ਜੇ HAVE_CLMUL_EXTERNAL
    ਹਾਲਤ CLMUL_BE: ਵਾਪਸ ff_ਚੱਕਰੀ_ਜਾਂਚ_clmul(ctx, ਚੱਕਰੀ_ਜਾਂਚ, ਬਫਰ, ਲੰਮਾਈ);
    ਹਾਲਤ CLMUL_LE: ਵਾਪਸ ff_ਚੱਕਰੀ_ਜਾਂਚ_le_clmul(ctx, ਚੱਕਰੀ_ਜਾਂਚ, ਬਫਰ, ਲੰਮਾਈ);
#ਜੇ_ਅੰਤ
    ਮੂਲ: av_unreachable("x86 CRC only uses CLMUL_BE and CLMUL_LE");
    }
    ਵਾਪਸ 0;
}

#ਜੇ_ਅੰਤ /* AVUTIL_X86_CRC_H */
