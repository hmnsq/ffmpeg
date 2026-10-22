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

#నిర్వచితం_కాకపోతే AVUTIL_INT128_H
#నిర్వచించు AVUTIL_INT128_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stddef.h>
#అన్తర్భావ <limits.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "integer.h"

#ఒకవేళ HAVE_INT128
#నిర్వచించు AV_INT128_NATIVE 1
రకనిర్వచనం గుర్తులేని __int128 av_uint128;
రకనిర్వచనం          __int128 av_int128;
#లేదావేళ defined(BITINT_MAXWIDTH) && BITINT_MAXWIDTH >= 128
#నిర్వచించు AV_INT128_NATIVE 1
రకనిర్వచనం గుర్తులేని బిట్టు_Int(128) av_uint128;
రకనిర్వచనం          బిట్టు_Int(128) av_int128;
#లేదావేళ AV_INTEGER_కొలత >= 8
#నిర్వచించు AV_INT128_NATIVE 0
రకనిర్వచనం AVInteger av_uint128;
రకనిర్వచనం AVInteger av_int128;
#లేకపోతే
#దోషం "128-bit integer type not available"
#అయితే_ముగింపు

#ఒకవేళ AV_INT128_NATIVE
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
#లేకపోతే
#  define av_add128(a, b)   av_కూడు_i(a, b)
#  define av_sub128(a, b)   av_sub_i(a, b)
#  define av_mul128(a, b)   av_mul_i(a, b)
#  define av_div128(a, b)   av_div_i(a, b)
#  define av_cmp128(a, b)   av_cmp_i(a, b)
#  define av_min128(a, b)   (av_cmp_i(a, b) > 0 ? (b) : (a))
#  define av_max128(a, b)   (av_cmp_i(a, b) > 0 ? (a) : (b))
#  define av_eq128(a, b)    (av_cmp_i(a, b) == 0)
#  define av_mod128(a, b)   av_mod_i(ఖాళీ, a, b)
#  define av_shr128(a, b)   av_shr_i(a, b)
#  define av_to128i(a)      av_int2i(a)
#  define av_from128i(a)    av_i2int(a)
#  define av_from128u(a)    ((uint64_t) av_i2int(a))
#  define av_test128(a)     (!av_eq128(a, av_to128u(0)))

స్థిర av_always_inline av_uint128 av_to128u(uint64_t a)
{
    తిరిగి (AVInteger) {{ a, a >> 16, a >> 32, a >> 48 }};
}
#అయితే_ముగింపు

#అయితే_ముగింపు /* AVUTIL_INT128_H */
