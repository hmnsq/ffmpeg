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

#अगर_अघोषित AVUTIL_BSWAP_H
#घोषणा AVUTIL_BSWAP_H

#समावेश <stdint.h>
#समावेश "libavutil/avconfig.h"
#समावेश "attributes.h"

#अगर_घोषित HAVE_AV_CONFIG_H

#समावेश "config.h"

#अगर ARCH_ARM
#   include "arm/bswap.h"
#या_अगर ARCH_RISCV
#   include "riscv/bswap.h"
#या_अगर ARCH_X86
#   include "x86/bswap.h"
#पूर्ण_अगर

#पूर्ण_अगर /* HAVE_AV_CONFIG_H */

#घोषणा AV_BSWAP16C(x) (((x) << 8 & 0xff00)  | ((x) >> 8 & 0x00ff))
#घोषणा AV_BSWAP32C(x) (AV_BSWAP16C(x) << 16 | AV_BSWAP16C((x) >> 16))
#घोषणा AV_BSWAP64C(x) (AV_BSWAP32C(x) << 32 | AV_BSWAP32C((x) >> 32))

#घोषणा AV_BSWAPC(s, x) AV_BSWAP##s##C(x)

#अगर_अघोषित av_bswap16
अटल av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    x= (x>>8) | (x<<8);
    वापस x;
}
#पूर्ण_अगर

#अगर_अघोषित av_bswap32
अटल av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    वापस AV_BSWAP32C(x);
}
#पूर्ण_अगर

#अगर_अघोषित av_bswap64
अटल अंतरभूत uint64_t av_const av_bswap64(uint64_t x)
{
    वापस (uint64_t)av_bswap32((uint32_t)x) << 32 | av_bswap32((uint32_t)(x >> 32));
}
#पूर्ण_अगर

// be2ne ... big-endian to native-endian
// le2ne ... little-endian to native-endian

#अगर AV_HAVE_BIGENDIAN
#घोषणा av_be2ne16(x) (x)
#घोषणा av_be2ne32(x) (x)
#घोषणा av_be2ne64(x) (x)
#घोषणा av_le2ne16(x) av_bswap16(x)
#घोषणा av_le2ne32(x) av_bswap32(x)
#घोषणा av_le2ne64(x) av_bswap64(x)
#घोषणा AV_BE2NEC(s, x) (x)
#घोषणा AV_LE2NEC(s, x) AV_BSWAPC(s, x)
#अन्यथा
#घोषणा av_be2ne16(x) av_bswap16(x)
#घोषणा av_be2ne32(x) av_bswap32(x)
#घोषणा av_be2ne64(x) av_bswap64(x)
#घोषणा av_le2ne16(x) (x)
#घोषणा av_le2ne32(x) (x)
#घोषणा av_le2ne64(x) (x)
#घोषणा AV_BE2NEC(s, x) AV_BSWAPC(s, x)
#घोषणा AV_LE2NEC(s, x) (x)
#पूर्ण_अगर

#घोषणा AV_BE2NE16C(x) AV_BE2NEC(16, x)
#घोषणा AV_BE2NE32C(x) AV_BE2NEC(32, x)
#घोषणा AV_BE2NE64C(x) AV_BE2NEC(64, x)
#घोषणा AV_LE2NE16C(x) AV_LE2NEC(16, x)
#घोषणा AV_LE2NE32C(x) AV_LE2NEC(32, x)
#घोषणा AV_LE2NE64C(x) AV_LE2NEC(64, x)

#पूर्ण_अगर /* AVUTIL_BSWAP_H */
