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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_BSWAP_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_BSWAP_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "libavutil/avconfig.h"
#ಅನ್ತರ್ಭಾವ "attributes.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ HAVE_AV_CONFIG_H

#ಅನ್ತರ್ಭಾವ "config.h"

#ಆದರೆ ARCH_ARM
#   include "arm/bswap.h"
#ಅಥವಾಆದರೆ ARCH_RISCV
#   include "riscv/bswap.h"
#ಅಥವಾಆದರೆ ARCH_X86
#   include "x86/bswap.h"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_AV_CONFIG_H */

#ವ್ಯಾಖ್ಯಾನಿಸು AV_BSWAP16C(x) (((x) << 8 & 0xff00)  | ((x) >> 8 & 0x00ff))
#ವ್ಯಾಖ್ಯಾನಿಸು AV_BSWAP32C(x) (AV_BSWAP16C(x) << 16 | AV_BSWAP16C((x) >> 16))
#ವ್ಯಾಖ್ಯಾನಿಸು AV_BSWAP64C(x) (AV_BSWAP32C(x) << 32 | AV_BSWAP32C((x) >> 32))

#ವ್ಯಾಖ್ಯಾನಿಸು AV_BSWAPC(s, x) AV_BSWAP##s##C(x)

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ av_bswap16
ಸ್ಥಿರ av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    x= (x>>8) | (x<<8);
    ಹಿಂತಿರುಗಿ x;
}
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ av_bswap32
ಸ್ಥಿರ av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    ಹಿಂತಿರುಗಿ AV_BSWAP32C(x);
}
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ av_bswap64
ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint64_t av_const av_bswap64(uint64_t x)
{
    ಹಿಂತಿರುಗಿ (uint64_t)av_bswap32((uint32_t)x) << 32 | av_bswap32((uint32_t)(x >> 32));
}
#ಆದರೆ_ಅಂತ್ಯ

// be2ne ... big-endian to native-endian
// le2ne ... little-endian to native-endian

#ಆದರೆ AV_HAVE_BIGENDIAN
#ವ್ಯಾಖ್ಯಾನಿಸು av_be2ne16(x) (x)
#ವ್ಯಾಖ್ಯಾನಿಸು av_be2ne32(x) (x)
#ವ್ಯಾಖ್ಯಾನಿಸು av_be2ne64(x) (x)
#ವ್ಯಾಖ್ಯಾನಿಸು av_le2ne16(x) av_bswap16(x)
#ವ್ಯಾಖ್ಯಾನಿಸು av_le2ne32(x) av_bswap32(x)
#ವ್ಯಾಖ್ಯಾನಿಸು av_le2ne64(x) av_bswap64(x)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_BE2NEC(s, x) (x)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LE2NEC(s, x) AV_BSWAPC(s, x)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು av_be2ne16(x) av_bswap16(x)
#ವ್ಯಾಖ್ಯಾನಿಸು av_be2ne32(x) av_bswap32(x)
#ವ್ಯಾಖ್ಯಾನಿಸು av_be2ne64(x) av_bswap64(x)
#ವ್ಯಾಖ್ಯಾನಿಸು av_le2ne16(x) (x)
#ವ್ಯಾಖ್ಯಾನಿಸು av_le2ne32(x) (x)
#ವ್ಯಾಖ್ಯಾನಿಸು av_le2ne64(x) (x)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_BE2NEC(s, x) AV_BSWAPC(s, x)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LE2NEC(s, x) (x)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು AV_BE2NE16C(x) AV_BE2NEC(16, x)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_BE2NE32C(x) AV_BE2NEC(32, x)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_BE2NE64C(x) AV_BE2NEC(64, x)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LE2NE16C(x) AV_LE2NEC(16, x)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LE2NE32C(x) AV_LE2NEC(32, x)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_LE2NE64C(x) AV_LE2NEC(64, x)

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_BSWAP_H */
