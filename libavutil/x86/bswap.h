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

/**
 * @file
 * byte swapping routines
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_X86_BSWAP_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_X86_BSWAP_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಆದರೆ defined(_MSC_VER)
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <intrin.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"

#ಆದರೆ defined(_MSC_VER)

#ವ್ಯಾಖ್ಯಾನಿಸು av_bswap16 av_bswap16
ಸ್ಥಿರ av_always_inline av_const uint16_t av_bswap16(uint16_t x)
{
    ಹಿಂತಿರುಗಿ _rotr16(x, 8);
}

#ವ್ಯಾಖ್ಯಾನಿಸು av_bswap32 av_bswap32
ಸ್ಥಿರ av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    ಹಿಂತಿರುಗಿ _byteswap_ulong(x);
}

#ಆದರೆ ARCH_X86_64
#ವ್ಯಾಖ್ಯಾನಿಸು av_bswap64 av_bswap64
ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint64_t av_const av_bswap64(uint64_t x)
{
    ಹಿಂತಿರುಗಿ _byteswap_uint64(x);
}
#ಆದರೆ_ಅಂತ್ಯ


#ಅಥವಾಆದರೆ HAVE_INLINE_ASM

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __INTEL_COMPILER
#ವ್ಯಾಖ್ಯಾನಿಸು av_bswap32 av_bswap32
ಸ್ಥಿರ av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    __asm__("bswap   %0" : "+r" (x));
    ಹಿಂತಿರುಗಿ x;
}

#ಆದರೆ ARCH_X86_64
#ವ್ಯಾಖ್ಯಾನಿಸು av_bswap64 av_bswap64
ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint64_t av_const av_bswap64(uint64_t x)
{
    __asm__("bswap  %0": "=r" (x) : "0" (x));
    ಹಿಂತಿರುಗಿ x;
}
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* __INTEL_COMPILER */

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_INLINE_ASM */
#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_X86_BSWAP_H */
