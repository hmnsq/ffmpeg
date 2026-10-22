/*
 * copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
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

/**
 * @file
 * byte swapping routines
 */

#నిర్వచితం_కాకపోతే AVUTIL_BSWAP_H
#నిర్వచించు AVUTIL_BSWAP_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "libavutil/avconfig.h"
#అన్తర్భావ "attributes.h"

#నిర్వచితమైతే HAVE_AV_CONFIG_H

#అన్తర్భావ "config.h"

#ఒకవేళ ARCH_ARM
#   include "arm/bswap.h"
#లేదావేళ ARCH_RISCV
#   include "riscv/bswap.h"
#లేదావేళ ARCH_X86
#   include "x86/bswap.h"
#అయితే_ముగింపు

#అయితే_ముగింపు /* HAVE_AV_CONFIG_H */

#నిర్వచించు AV_BSWAP16C(x) (((x) << 8 & 0xff00)  | ((x) >> 8 & 0x00ff))
#నిర్వచించు AV_BSWAP32C(x) (AV_BSWAP16C(x) << 16 | AV_BSWAP16C((x) >> 16))
#నిర్వచించు AV_BSWAP64C(x) (AV_BSWAP32C(x) << 32 | AV_BSWAP32C((x) >> 32))

#నిర్వచించు AV_BSWAPC(s, x) AV_BSWAP##s##C(x)

#నిర్వచితం_కాకపోతే av_bswap16
స్థిర av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    x= (x>>8) | (x<<8);
    తిరిగి x;
}
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే av_bswap32
స్థిర av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    తిరిగి AV_BSWAP32C(x);
}
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే av_bswap64
స్థిర అంతఃవరుస uint64_t av_const av_bswap64(uint64_t x)
{
    తిరిగి (uint64_t)av_bswap32((uint32_t)x) << 32 | av_bswap32((uint32_t)(x >> 32));
}
#అయితే_ముగింపు

// be2ne ... big-endian to native-endian
// le2ne ... little-endian to native-endian

#ఒకవేళ AV_HAVE_BIGENDIAN
#నిర్వచించు av_be2ne16(x) (x)
#నిర్వచించు av_be2ne32(x) (x)
#నిర్వచించు av_be2ne64(x) (x)
#నిర్వచించు av_le2ne16(x) av_bswap16(x)
#నిర్వచించు av_le2ne32(x) av_bswap32(x)
#నిర్వచించు av_le2ne64(x) av_bswap64(x)
#నిర్వచించు AV_BE2NEC(s, x) (x)
#నిర్వచించు AV_LE2NEC(s, x) AV_BSWAPC(s, x)
#లేకపోతే
#నిర్వచించు av_be2ne16(x) av_bswap16(x)
#నిర్వచించు av_be2ne32(x) av_bswap32(x)
#నిర్వచించు av_be2ne64(x) av_bswap64(x)
#నిర్వచించు av_le2ne16(x) (x)
#నిర్వచించు av_le2ne32(x) (x)
#నిర్వచించు av_le2ne64(x) (x)
#నిర్వచించు AV_BE2NEC(s, x) AV_BSWAPC(s, x)
#నిర్వచించు AV_LE2NEC(s, x) (x)
#అయితే_ముగింపు

#నిర్వచించు AV_BE2NE16C(x) AV_BE2NEC(16, x)
#నిర్వచించు AV_BE2NE32C(x) AV_BE2NEC(32, x)
#నిర్వచించు AV_BE2NE64C(x) AV_BE2NEC(64, x)
#నిర్వచించు AV_LE2NE16C(x) AV_LE2NEC(16, x)
#నిర్వచించు AV_LE2NE32C(x) AV_LE2NEC(32, x)
#నిర్వచించు AV_LE2NE64C(x) AV_LE2NEC(64, x)

#అయితే_ముగింపు /* AVUTIL_BSWAP_H */
