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

#اگر_غیر_تعریف_شدہ AVUTIL_BSWAP_H
#تعریف_کرو AVUTIL_BSWAP_H

#شامل <stdint.h>
#شامل "libavutil/avconfig.h"
#شامل "attributes.h"

#اگر_تعریف_شدہ HAVE_AV_CONFIG_H

#شامل "config.h"

#اگر ARCH_ARM
#   include "arm/bswap.h"
#وگرنہ_اگر ARCH_RISCV
#   include "riscv/bswap.h"
#وگرنہ_اگر ARCH_X86
#   include "x86/bswap.h"
#اگر_ختم

#اگر_ختم /* HAVE_AV_CONFIG_H */

#تعریف_کرو AV_BSWAP16C(x) (((x) << 8 & 0xff00)  | ((x) >> 8 & 0x00ff))
#تعریف_کرو AV_BSWAP32C(x) (AV_BSWAP16C(x) << 16 | AV_BSWAP16C((x) >> 16))
#تعریف_کرو AV_BSWAP64C(x) (AV_BSWAP32C(x) << 32 | AV_BSWAP32C((x) >> 32))

#تعریف_کرو AV_BSWAPC(s, x) AV_BSWAP##s##C(x)

#اگر_غیر_تعریف_شدہ av_bswap16
ساکن av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    x= (x>>8) | (x<<8);
    واپس x;
}
#اگر_ختم

#اگر_غیر_تعریف_شدہ av_bswap32
ساکن av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    واپس AV_BSWAP32C(x);
}
#اگر_ختم

#اگر_غیر_تعریف_شدہ av_bswap64
ساکن اندرونی uint64_t av_const av_bswap64(uint64_t x)
{
    واپس (uint64_t)av_bswap32((uint32_t)x) << 32 | av_bswap32((uint32_t)(x >> 32));
}
#اگر_ختم

// be2ne ... big-endian to native-endian
// le2ne ... little-endian to native-endian

#اگر AV_HAVE_BIGENDIAN
#تعریف_کرو av_be2ne16(x) (x)
#تعریف_کرو av_be2ne32(x) (x)
#تعریف_کرو av_be2ne64(x) (x)
#تعریف_کرو av_le2ne16(x) av_bswap16(x)
#تعریف_کرو av_le2ne32(x) av_bswap32(x)
#تعریف_کرو av_le2ne64(x) av_bswap64(x)
#تعریف_کرو AV_BE2NEC(s, x) (x)
#تعریف_کرو AV_LE2NEC(s, x) AV_BSWAPC(s, x)
#ورنہ
#تعریف_کرو av_be2ne16(x) av_bswap16(x)
#تعریف_کرو av_be2ne32(x) av_bswap32(x)
#تعریف_کرو av_be2ne64(x) av_bswap64(x)
#تعریف_کرو av_le2ne16(x) (x)
#تعریف_کرو av_le2ne32(x) (x)
#تعریف_کرو av_le2ne64(x) (x)
#تعریف_کرو AV_BE2NEC(s, x) AV_BSWAPC(s, x)
#تعریف_کرو AV_LE2NEC(s, x) (x)
#اگر_ختم

#تعریف_کرو AV_BE2NE16C(x) AV_BE2NEC(16, x)
#تعریف_کرو AV_BE2NE32C(x) AV_BE2NEC(32, x)
#تعریف_کرو AV_BE2NE64C(x) AV_BE2NEC(64, x)
#تعریف_کرو AV_LE2NE16C(x) AV_LE2NEC(16, x)
#تعریف_کرو AV_LE2NE32C(x) AV_LE2NEC(32, x)
#تعریف_کرو AV_LE2NE64C(x) AV_LE2NEC(64, x)

#اگر_ختم /* AVUTIL_BSWAP_H */
