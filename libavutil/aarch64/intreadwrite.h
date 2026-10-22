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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_AARCH64_INTREADWRITE_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_AARCH64_INTREADWRITE_H

#ಆದರೆ HAVE_INTRINSICS_NEON

#ಅನ್ತರ್ಭಾವ <arm_neon.h>

#ವ್ಯಾಖ್ಯಾನಿಸು AV_COPY128 AV_COPY128
ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ AV_COPY128(ಶೂನ್ಯ *d, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *s)
{
    uint8x16_t tmp = vld1q_u8((ಸ್ಥಿರಾಂಕ uint8_t *)s);
    vst1q_u8((uint8_t *)d, tmp);
}

#ವ್ಯಾಖ್ಯಾನಿಸು AV_ZERO128 AV_ZERO128
ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ AV_ZERO128(ಶೂನ್ಯ *d)
{
    uint8x16_t zero = vdupq_n_u8(0);
    vst1q_u8((uint8_t *)d, zero);
}

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_INTRINSICS_NEON */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_AARCH64_INTREADWRITE_H */
