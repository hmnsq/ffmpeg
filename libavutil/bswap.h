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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_BSWAP_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_BSWAP_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avconfig.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_AV_CONFIG_H

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ ARCH_ARM
#   include "arm/bswap.h"
#ਜਾਂਜੇ ARCH_RISCV
#   include "riscv/bswap.h"
#ਜਾਂਜੇ ARCH_X86
#   include "x86/bswap.h"
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* HAVE_AV_CONFIG_H */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_BSWAP16C(x) (((x) << 8 & 0xff00)  | ((x) >> 8 & 0x00ff))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_BSWAP32C(x) (AV_BSWAP16C(x) << 16 | AV_BSWAP16C((x) >> 16))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_BSWAP64C(x) (AV_BSWAP32C(x) << 32 | AV_BSWAP32C((x) >> 32))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_BSWAPC(s, x) AV_BSWAP##s##C(x)

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_bswap16
ਸਥਿਰ av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    x= (x>>8) | (x<<8);
    ਵਾਪਸ x;
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_bswap32
ਸਥਿਰ av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    ਵਾਪਸ AV_BSWAP32C(x);
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_bswap64
ਸਥਿਰ ਸਤਰਅੰਦਰ uint64_t av_const av_bswap64(uint64_t x)
{
    ਵਾਪਸ (uint64_t)av_bswap32((uint32_t)x) << 32 | av_bswap32((uint32_t)(x >> 32));
}
#ਜੇ_ਅੰਤ

// be2ne ... big-endian to native-endian
// le2ne ... little-endian to native-endian

#ਜੇ AV_HAVE_BIGENDIAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_be2ne16(x) (x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_be2ne32(x) (x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_be2ne64(x) (x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_le2ne16(x) av_bswap16(x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_le2ne32(x) av_bswap32(x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_le2ne64(x) av_bswap64(x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_BE2NEC(s, x) (x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LE2NEC(s, x) AV_BSWAPC(s, x)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_be2ne16(x) av_bswap16(x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_be2ne32(x) av_bswap32(x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_be2ne64(x) av_bswap64(x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_le2ne16(x) (x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_le2ne32(x) (x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_le2ne64(x) (x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_BE2NEC(s, x) AV_BSWAPC(s, x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LE2NEC(s, x) (x)
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_BE2NE16C(x) AV_BE2NEC(16, x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_BE2NE32C(x) AV_BE2NEC(32, x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_BE2NE64C(x) AV_BE2NEC(64, x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LE2NE16C(x) AV_LE2NEC(16, x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LE2NE32C(x) AV_LE2NEC(32, x)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_LE2NE64C(x) AV_LE2NEC(64, x)

#ਜੇ_ਅੰਤ /* AVUTIL_BSWAP_H */
