/*
 * 128-bit integers
 * Copyright (c) 2026 Niklas Haas
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
 * 128-bit integers, falling back to integer.h if necessary
 * @author Niklas Haas
 */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_INT128_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_INT128_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <limits.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "integer.h"

#ಆದರೆ HAVE_INT128
#ವ್ಯಾಖ್ಯಾನಿಸು AV_INT128_NATIVE 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ __int128 av_uint128;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ          __int128 av_int128;
#ಅಥವಾಆದರೆ defined(BITINT_MAXWIDTH) && BITINT_MAXWIDTH >= 128
#ವ್ಯಾಖ್ಯಾನಿಸು AV_INT128_NATIVE 1
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಬಿಟ್_Int(128) av_uint128;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ          ಬಿಟ್_Int(128) av_int128;
#ಅಥವಾಆದರೆ AV_INTEGER_ಗಾತ್ರ >= 8
#ವ್ಯಾಖ್ಯಾನಿಸು AV_INT128_NATIVE 0
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ AVInteger av_uint128;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ AVInteger av_int128;
#ಇಲ್ಲದಿದ್ದರೆ
#ದೋಷ "128-bit integer type not available"
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ AV_INT128_NATIVE
#  define av_add128(a, b)   ((a) + (b))
#  define av_sub128(a, b)   ((a) - (b))
#  define av_mul128(a, b)   ((a) * (b))
#  define av_div128(a, b)   ((a) / (b))
#  define av_cmp128(a, b)   ((a) < (b) ? -1 : (a) > (b) ? 1 : 0)
#  define av_min128(a, b)   ((a) > (b) ? (b) : (a))
#  define av_max128(a, b)   ((a) > (b) ? (a) : (b))
#  define av_eq128(a, b)    ((a) == (b))
#  define av_mod128(a, b)   ((a) % (b))
#  define av_shr128(a, b)   ((a) >> (b))
#  define av_to128u(a)      ((av_uint128) (a))
#  define av_to128i(a)      ((av_int128) (a))
#  define av_from128i(a)    ((int64_t) (a))
#  define av_from128u(a)    ((uint64_t) (a))
#  define av_test128(a)     (!!(a))
#ಇಲ್ಲದಿದ್ದರೆ
#  define av_add128(a, b)   av_ಕೂಡಿಸು_i(a, b)
#  define av_sub128(a, b)   av_sub_i(a, b)
#  define av_mul128(a, b)   av_mul_i(a, b)
#  define av_div128(a, b)   av_div_i(a, b)
#  define av_cmp128(a, b)   av_cmp_i(a, b)
#  define av_min128(a, b)   (av_cmp_i(a, b) > 0 ? (b) : (a))
#  define av_max128(a, b)   (av_cmp_i(a, b) > 0 ? (a) : (b))
#  define av_eq128(a, b)    (av_cmp_i(a, b) == 0)
#  define av_mod128(a, b)   av_mod_i(ಖಾಲಿ, a, b)
#  define av_shr128(a, b)   av_shr_i(a, b)
#  define av_to128i(a)      av_int2i(a)
#  define av_from128i(a)    av_i2int(a)
#  define av_from128u(a)    ((uint64_t) av_i2int(a))
#  define av_test128(a)     (!av_eq128(a, av_to128u(0)))

ಸ್ಥಿರ av_always_inline av_uint128 av_to128u(uint64_t a)
{
    ಹಿಂತಿರುಗಿ (AVInteger) {{ a, a >> 16, a >> 32, a >> 48 }};
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_INT128_H */
