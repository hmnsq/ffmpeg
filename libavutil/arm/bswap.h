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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_ARM_BSWAP_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_ARM_BSWAP_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ARMCC_VERSION

#ಆದರೆ HAVE_ARMV6
#ವ್ಯಾಖ್ಯಾನಿಸು av_bswap32 av_bswap32
ಸ್ಥಿರ av_always_inline av_const uint32_t av_bswap32(uint32_t x)
{
    ಹಿಂತಿರುಗಿ __rev(x);
}
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_ARMV6 */

#ಅಥವಾಆದರೆ HAVE_INLINE_ASM

#ಆದರೆ HAVE_ARMV6_INLINE
#ವ್ಯಾಖ್ಯಾನಿಸು av_bswap16 av_bswap16
ಸ್ಥಿರ av_always_inline av_const ಚಿಹ್ನೆರಹಿತ av_bswap16(ಚಿಹ್ನೆರಹಿತ x)
{
    ಚಿಹ್ನೆರಹಿತ y;

    __asm__("rev16 %0, %1" : "=r"(y) : "r"(x));
    ಹಿಂತಿರುಗಿ y;
}
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /* __ARMCC_VERSION */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_ARM_BSWAP_H */
