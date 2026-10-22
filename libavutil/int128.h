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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_INT128_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_INT128_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "integer.h"

#ਜੇ HAVE_INT128
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_INT128_NATIVE 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ __int128 av_uint128;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ          __int128 av_int128;
#ਜਾਂਜੇ defined(BITINT_MAXWIDTH) && BITINT_MAXWIDTH >= 128
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_INT128_NATIVE 1
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਦੋਆਧਾਰੀ_ਅੰਕ_Int(128) av_uint128;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ          ਦੋਆਧਾਰੀ_ਅੰਕ_Int(128) av_int128;
#ਜਾਂਜੇ AV_INTEGER_ਮਾਪ >= 8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_INT128_NATIVE 0
ਕਿਸਮਪਰਿਭਾਸ਼ਾ AVInteger av_uint128;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ AVInteger av_int128;
#ਨਹੀਂਤਾਂ
#ਗਲਤੀ "128-bit integer type not available"
#ਜੇ_ਅੰਤ

#ਜੇ AV_INT128_NATIVE
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
#ਨਹੀਂਤਾਂ
#  define av_add128(a, b)   av_ਜੋੜੋ_i(a, b)
#  define av_sub128(a, b)   av_sub_i(a, b)
#  define av_mul128(a, b)   av_mul_i(a, b)
#  define av_div128(a, b)   av_div_i(a, b)
#  define av_cmp128(a, b)   av_cmp_i(a, b)
#  define av_min128(a, b)   (av_cmp_i(a, b) > 0 ? (b) : (a))
#  define av_max128(a, b)   (av_cmp_i(a, b) > 0 ? (a) : (b))
#  define av_eq128(a, b)    (av_cmp_i(a, b) == 0)
#  define av_mod128(a, b)   av_mod_i(ਨਿਰਾ, a, b)
#  define av_shr128(a, b)   av_shr_i(a, b)
#  define av_to128i(a)      av_int2i(a)
#  define av_from128i(a)    av_i2int(a)
#  define av_from128u(a)    ((uint64_t) av_i2int(a))
#  define av_test128(a)     (!av_eq128(a, av_to128u(0)))

ਸਥਿਰ av_always_inline av_uint128 av_to128u(uint64_t a)
{
    ਵਾਪਸ (AVInteger) {{ a, a >> 16, a >> 32, a >> 48 }};
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* AVUTIL_INT128_H */
