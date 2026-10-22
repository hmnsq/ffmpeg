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

#నిర్వచితం_కాకపోతే AVUTIL_X86_చక్రీయ_తనిఖీ_H
#నిర్వచించు AVUTIL_X86_చక్రీయ_తనిఖీ_H

#అన్తర్భావ "config.h"
#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/attributes_internal.h"
#అన్తర్భావ "libavutil/avassert.h"
#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/crc.h"
#అన్తర్భావ "libavutil/intreadwrite.h"
#అన్తర్భావ "libavutil/x86/cpu.h"

#ఒకవేళ HAVE_CLMUL_EXTERNAL
#అన్తర్భావ "libavutil/crc_internal.h"

FF_VISIBILITY_నెట్టు_HIDDEN
uint32_t ff_చక్రీయ_తనిఖీ_clmul(స్థిరరాశి AVCRC *ctx, uint32_t చక్రీయ_తనిఖీ,
                      స్థిరరాశి uint8_t *బఫరు, size_t నిడివి);
uint32_t ff_చక్రీయ_తనిఖీ_le_clmul(స్థిరరాశి AVCRC *ctx, uint32_t చక్రీయ_తనిఖీ,
                         స్థిరరాశి uint8_t *బఫరు, size_t నిడివి);
FF_VISIBILITY_తీయి_HIDDEN

గణన {
    చక్రీయ_తనిఖీ_C    = 0,
    CLMUL_BE,
    CLMUL_LE,
};

స్థిర స్థిరరాశి AVCRC చక్రీయ_తనిఖీ_పట్టిక_clmul[AV_చక్రీయ_తనిఖీ_MAX][17] = {
    [AV_చక్రీయ_తనిఖీ_8_ATM] = {
        CLMUL_BE,
        0x32000000, 0x0, 0xbc000000, 0x0,
        0xc4000000, 0x0, 0x94000000, 0x0,
        0x62000000, 0x0, 0x79000000, 0x0,
        0x07156a16, 0x1, 0x07000000, 0x1,
    },
    [AV_చక్రీయ_తనిఖీ_8_EBU] = {
        CLMUL_BE,
        0xb5000000, 0x0, 0xf3000000, 0x0,
        0xfc000000, 0x0, 0x0d000000, 0x0,
        0x6a000000, 0x0, 0x65000000, 0x0,
        0x1c4b8192, 0x1, 0x1d000000, 0x1,
    },
    [AV_చక్రీయ_తనిఖీ_16_ANSI] = {
        CLMUL_BE,
        0xf9e30000, 0x0, 0x807d0000, 0x0,
        0xf9130000, 0x0, 0xff830000, 0x0,
        0x807b0000, 0x0, 0x86630000, 0x0,
        0xfffbffe7, 0x1, 0x80050000, 0x1,
    },
    [AV_చక్రీయ_తనిఖీ_16_CCITT] = {
        CLMUL_BE,
        0x60190000, 0x0, 0x59b00000, 0x0,
        0xd5f60000, 0x0, 0x45630000, 0x0,
        0xaa510000, 0x0, 0xeb230000, 0x0,
        0x11303471, 0x1, 0x10210000, 0x1,
    },
    [AV_చక్రీయ_తనిఖీ_24_IEEE] = {
        CLMUL_BE,
        0x1f428700, 0x0, 0x467d2400, 0x0,
        0x2c8c9d00, 0x0, 0x64e4d700, 0x0,
        0xd9fe8c00, 0x0, 0xfd7e0c00, 0x0,
        0xf845fe24, 0x1, 0x864cfb00, 0x1,
    },
    [AV_చక్రీయ_తనిఖీ_32_IEEE] = {
        CLMUL_BE,
        0x8833794c, 0x0, 0xe6228b11, 0x0,
        0xc5b9cd4c, 0x0, 0xe8a45605, 0x0,
        0x490d678d, 0x0, 0xf200aa66, 0x0,
        0x04d101df, 0x1, 0x04c11db7, 0x1,
    },
    [AV_చక్రీయ_తనిఖీ_32_IEEE_LE] = {
        CLMUL_LE,
        0xc6e41596, 0x1, 0x54442bd4, 0x1,
        0xccaa009e, 0x0, 0x751997d0, 0x1,
        0xccaa009e, 0x0, 0x63cd6124, 0x1,
        0xf7011640, 0x1, 0xdb710641, 0x1,
    },
    [AV_చక్రీయ_తనిఖీ_16_ANSI_LE] = {
        CLMUL_LE,
        0x0000bffa, 0x0, 0x1b0c2, 0x0,
        0x00018cc2, 0x0, 0x1d0c2, 0x0,
        0x00018cc2, 0x0, 0x1bc02, 0x0,
        0xcfffbffe, 0x1, 0x14003, 0x0,
    },
};

స్థిర అంతఃవరుస శూన్య చక్రీయ_తనిఖీ_init_x86(AVCRC *ctx, పూర్ణాంకం le, పూర్ణాంకం బిట్లు, uint32_t poly, పూర్ణాంకం ctx_కొలత)
{
    uint64_t poly_;
    ఒకవేళ (le) {
        // convert the reversed representation to regular form
        poly = తిరగేయి(poly, బిట్లు) >> 1;
    }
    // convert to 32 degree polynomial
    poly_ = ((uint64_t)poly) << (32 - బిట్లు);

    uint64_t div;
    uint8_t *dst = (uint8_t*)(ctx + 1);
    ఒకవేళ (le) {
        ctx[0] = CLMUL_LE;
        AV_WN64(dst,      xnmodp(4 * 128 - 32, poly_, 32, &div, le));
        AV_WN64(dst +  8, xnmodp(4 * 128 + 32, poly_, 32, &div, le));
        uint64_t tmp = xnmodp(128 - 32, poly_, 32, &div, le);
        AV_WN64(dst + 16, tmp);
        AV_WN64(dst + 24, xnmodp(128 + 32, poly_, 32, &div, le));
        AV_WN64(dst + 32, tmp);
        AV_WN64(dst + 40, xnmodp(64, poly_, 32, &div, le));
        AV_WN64(dst + 48, div);
        AV_WN64(dst + 56, తిరగేయి(poly_ | (1ULL << 32), 32));
    } లేకపోతే {
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
#అయితే_ముగింపు

స్థిర అంతఃవరుస స్థిరరాశి AVCRC *ff_చక్రీయ_తనిఖీ_get_పట్టిక_x86(AVCRCId చక్రీయ_తనిఖీ_id)
{
#ఒకవేళ HAVE_CLMUL_EXTERNAL
    పూర్ణాంకం cpu_flags = av_get_cpu_flags();

    ఒకవేళ (EXTERNAL_CLMUL(cpu_flags)) {
        తిరిగి చక్రీయ_తనిఖీ_పట్టిక_clmul[చక్రీయ_తనిఖీ_id];
    }
#అయితే_ముగింపు
    తిరిగి ఖాళీ;
}

స్థిర అంతఃవరుస av_cold పూర్ణాంకం ff_చక్రీయ_తనిఖీ_init_x86(AVCRC *ctx, పూర్ణాంకం le, పూర్ణాంకం బిట్లు, uint32_t poly, పూర్ణాంకం ctx_కొలత)
{
#ఒకవేళ HAVE_CLMUL_EXTERNAL
    పూర్ణాంకం cpu_flags = av_get_cpu_flags();

    ఒకవేళ (EXTERNAL_CLMUL(cpu_flags)) {
        చక్రీయ_తనిఖీ_init_x86(ctx, le, బిట్లు, poly, ctx_కొలత);
        తిరిగి 1;
    }
#అయితే_ముగింపు
    తిరిగి 0;
}

స్థిర అంతఃవరుస uint32_t ff_చక్రీయ_తనిఖీ_x86(స్థిరరాశి AVCRC *ctx, uint32_t చక్రీయ_తనిఖీ,
                                  స్థిరరాశి uint8_t *బఫరు, size_t నిడివి)
{
    ఎంపిక (ctx[0]) {
#ఒకవేళ HAVE_CLMUL_EXTERNAL
    స్థితి CLMUL_BE: తిరిగి ff_చక్రీయ_తనిఖీ_clmul(ctx, చక్రీయ_తనిఖీ, బఫరు, నిడివి);
    స్థితి CLMUL_LE: తిరిగి ff_చక్రీయ_తనిఖీ_le_clmul(ctx, చక్రీయ_తనిఖీ, బఫరు, నిడివి);
#అయితే_ముగింపు
    అప్రమేయ: av_unreachable("x86 CRC only uses CLMUL_BE and CLMUL_LE");
    }
    తిరిగి 0;
}

#అయితే_ముగింపు /* AVUTIL_X86_CRC_H */
