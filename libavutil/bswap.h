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

#यदि_अपरिभाषितम् AVUTIL_BSWAP_H
#परिभाषय AVUTIL_BSWAP_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "libavutil/avconfig.h"
#अन्तर्भाव "attributes.h"

#यदि_परिभाषितम् HAVE_AV_CONFIG_H

#अन्तर्भाव "config.h"

#यदि ARCH_ARM
#   include "arm/bswap.h"
#नोचेद्यदि ARCH_RISCV
#   include "riscv/bswap.h"
#नोचेद्यदि ARCH_X86
#   include "x86/bswap.h"
#यदि_अन्तः

#यदि_अन्तः /* HAVE_AV_CONFIG_H */

#परिभाषय AV_BSWAP16C(x) (((x) << 8 & 0xff00)  | ((x) >> 8 & 0x00ff))
#परिभाषय AV_BSWAP32C(x) (AV_BSWAP16C(x) << 16 | AV_BSWAP16C((x) >> 16))
#परिभाषय AV_BSWAP64C(x) (AV_BSWAP32C(x) << 32 | AV_BSWAP32C((x) >> 32))

#परिभाषय AV_BSWAPC(s, x) AV_BSWAP##s##C(x)

#यदि_अपरिभाषितम् av_bswap16
स्थिर av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    x= (x>>8) | (x<<8);
    प्रत्यागम x;
}
#यदि_अन्तः

#यदि_अपरिभाषितम् av_bswap32
स्थिर av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    प्रत्यागम AV_BSWAP32C(x);
}
#यदि_अन्तः

#यदि_अपरिभाषितम् av_bswap64
स्थिर अन्तःस्थ uint64_t av_const av_bswap64(uint64_t x)
{
    प्रत्यागम (uint64_t)av_bswap32((uint32_t)x) << 32 | av_bswap32((uint32_t)(x >> 32));
}
#यदि_अन्तः

// be2ne ... big-endian to native-endian
// le2ne ... little-endian to native-endian

#यदि AV_HAVE_BIGENDIAN
#परिभाषय av_be2ne16(x) (x)
#परिभाषय av_be2ne32(x) (x)
#परिभाषय av_be2ne64(x) (x)
#परिभाषय av_le2ne16(x) av_bswap16(x)
#परिभाषय av_le2ne32(x) av_bswap32(x)
#परिभाषय av_le2ne64(x) av_bswap64(x)
#परिभाषय AV_BE2NEC(s, x) (x)
#परिभाषय AV_LE2NEC(s, x) AV_BSWAPC(s, x)
#अन्यथा
#परिभाषय av_be2ne16(x) av_bswap16(x)
#परिभाषय av_be2ne32(x) av_bswap32(x)
#परिभाषय av_be2ne64(x) av_bswap64(x)
#परिभाषय av_le2ne16(x) (x)
#परिभाषय av_le2ne32(x) (x)
#परिभाषय av_le2ne64(x) (x)
#परिभाषय AV_BE2NEC(s, x) AV_BSWAPC(s, x)
#परिभाषय AV_LE2NEC(s, x) (x)
#यदि_अन्तः

#परिभाषय AV_BE2NE16C(x) AV_BE2NEC(16, x)
#परिभाषय AV_BE2NE32C(x) AV_BE2NEC(32, x)
#परिभाषय AV_BE2NE64C(x) AV_BE2NEC(64, x)
#परिभाषय AV_LE2NE16C(x) AV_LE2NEC(16, x)
#परिभाषय AV_LE2NE32C(x) AV_LE2NEC(32, x)
#परिभाषय AV_LE2NE64C(x) AV_LE2NEC(64, x)

#यदि_अन्तः /* AVUTIL_BSWAP_H */
