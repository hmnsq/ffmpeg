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
 * common internal and external API header
 */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_COMMON_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_COMMON_H

#ਜੇ defined(__cplusplus) && !defined(__STDC_CONSTANT_MACROS) && !defined(UINT64_C)
#ਗਲਤੀ missing -D__STDC_CONSTANT_MACROS / #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ __STDC_CONSTANT_MACROS
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <inttypes.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "version.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ HAVE_AV_CONFIG_H
#   include "config.h"
#   include "intmath.h"
#   include "internal.h"
#ਨਹੀਂਤਾਂ
#   include "mem.h"
#ਜੇ_ਅੰਤ /* HAVE_AV_CONFIG_H */

//rounded division & shift
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RSHIFT(a,b) ((a) > 0 ? ((a) + ((1<<(b))>>1))>>(b) : ((a) + ((1<<(b))>>1)-1)>>(b))
/* assume b>0 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROUNDED_DIV(a,b) (((a)>=0 ? (a) + ((b)>>1) : (a) - ((b)>>1))/(b))
/* Fast a/(1<<b) rounded toward +inf. Assume a>=0 and b>=0 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_CEIL_RSHIFT(a,b) (!av_builtin_constant_p(b) ? -((-(a)) >> (b)) \
                                                       : ((a) + (1<<(b)) - 1) >> (b))
/* Backwards compat. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_CEIL_RSHIFT AV_CEIL_RSHIFT

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFUDIV(a,b) (((a)>0 ?(a):(a)-(b)+1) / (b))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFUMOD(a,b) ((a)-(b)*FFUDIV(a,b))

/**
 * Absolute value, Note, INT_MIN / INT64_MIN result in undefined behavior as they
 * are not representable as absolute values of their type. This is the same
 * as with *abs()
 * @see FFNABS()
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFABS(a) ((a) >= 0 ? (a) : (-(a)))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFSIGN(a) ((a) > 0 ? 1 : -1)

/**
 * Negative Absolute value.
 * this works for all integers of all types.
 * As with many macros, this evaluates its argument twice, it thus must not have
 * a sideeffect, that is FFNABS(x++) has undefined behavior.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFNABS(a) ((a) <= 0 ? (a) : (-(a)))

/**
 * Unsigned Absolute value.
 * This takes the absolute value of a signed int and returns it as a unsigned.
 * This also works with INT_MIN which would otherwise not be representable
 * As with many macros, this evaluates its argument twice.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFABSU(a) ((a) <= 0 ? -(ਬਿਨਾਨਿਸ਼ਾਨੀ)(a) : (ਬਿਨਾਨਿਸ਼ਾਨੀ)(a))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFABS64U(a) ((a) <= 0 ? -(uint64_t)(a) : (uint64_t)(a))

/* misc math functions */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_ceil_log2
#   define av_ceil_log2     av_ceil_log2_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_clip
#   define av_clip          av_clip_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_clip64
#   define av_clip64        av_clip64_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_clip_uint8
#   define av_clip_uint8    av_clip_uint8_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_clip_int8
#   define av_clip_int8     av_clip_int8_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_clip_uint16
#   define av_clip_uint16   av_clip_uint16_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_clip_int16
#   define av_clip_int16    av_clip_int16_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_clipl_int32
#   define av_clipl_int32   av_clipl_int32_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_clip_intp2
#   define av_clip_intp2    av_clip_intp2_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_clip_uintp2
#   define av_clip_uintp2   av_clip_uintp2_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_sat_add32
#   define av_sat_add32     av_sat_add32_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_sat_dadd32
#   define av_sat_dadd32    av_sat_dadd32_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_sat_sub32
#   define av_sat_sub32     av_sat_sub32_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_sat_dsub32
#   define av_sat_dsub32    av_sat_dsub32_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_sat_add64
#   define av_sat_add64     av_sat_add64_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_sat_sub64
#   define av_sat_sub64     av_sat_sub64_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_clipf
#   define av_clipf         av_clipf_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_clipd
#   define av_clipd         av_clipd_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_zero_extend
#   define av_zero_extend   av_zero_extend_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_popcount
#   define av_popcount      av_popcount_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_popcount64
#   define av_popcount64    av_popcount64_c
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_parity
#   define av_parity        av_parity_c
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_log2
av_const ਪੂਰਨ av_log2(ਬਿਨਾਨਿਸ਼ਾਨੀ v);
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ av_log2_16bit
av_const ਪੂਰਨ av_log2_16bit(ਬਿਨਾਨਿਸ਼ਾਨੀ v);
#ਜੇ_ਅੰਤ

/**
 * Clip a signed integer value into the amin-amax range.
 * @param a value to clip
 * @param amin minimum value of the clip range
 * @param amax maximum value of the clip range
 * @return clipped value
 */
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ av_clip_c(ਪੂਰਨ a, ਪੂਰਨ amin, ਪੂਰਨ amax)
{
#ਜੇ defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ਜੇ (amin > amax) abort();
#ਜੇ_ਅੰਤ
    ਜੇ      (a < amin) ਵਾਪਸ amin;
    ਨਹੀਂਤਾਂ ਜੇ (a > amax) ਵਾਪਸ amax;
    ਨਹੀਂਤਾਂ               ਵਾਪਸ a;
}

/**
 * Clip a signed 64bit integer value into the amin-amax range.
 * @param a value to clip
 * @param amin minimum value of the clip range
 * @param amax maximum value of the clip range
 * @return clipped value
 */
ਸਥਿਰ av_always_inline av_const int64_t av_clip64_c(int64_t a, int64_t amin, int64_t amax)
{
#ਜੇ defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ਜੇ (amin > amax) abort();
#ਜੇ_ਅੰਤ
    ਜੇ      (a < amin) ਵਾਪਸ amin;
    ਨਹੀਂਤਾਂ ਜੇ (a > amax) ਵਾਪਸ amax;
    ਨਹੀਂਤਾਂ               ਵਾਪਸ a;
}

/**
 * Clip a signed integer value into the 0-255 range.
 * @param a value to clip
 * @return clipped value
 */
ਸਥਿਰ av_always_inline av_const uint8_t av_clip_uint8_c(ਪੂਰਨ a)
{
    ਜੇ (a&(~0xFF)) ਵਾਪਸ (~a)>>31;
    ਨਹੀਂਤਾਂ           ਵਾਪਸ a;
}

/**
 * Clip a signed integer value into the -128,127 range.
 * @param a value to clip
 * @return clipped value
 */
ਸਥਿਰ av_always_inline av_const int8_t av_clip_int8_c(ਪੂਰਨ a)
{
    ਜੇ ((a+0x80U) & ~0xFF) ਵਾਪਸ (a>>31) ^ 0x7F;
    ਨਹੀਂਤਾਂ                  ਵਾਪਸ a;
}

/**
 * Clip a signed integer value into the 0-65535 range.
 * @param a value to clip
 * @return clipped value
 */
ਸਥਿਰ av_always_inline av_const uint16_t av_clip_uint16_c(ਪੂਰਨ a)
{
    ਜੇ (a&(~0xFFFF)) ਵਾਪਸ (~a)>>31;
    ਨਹੀਂਤਾਂ             ਵਾਪਸ a;
}

/**
 * Clip a signed integer value into the -32768,32767 range.
 * @param a value to clip
 * @return clipped value
 */
ਸਥਿਰ av_always_inline av_const int16_t av_clip_int16_c(ਪੂਰਨ a)
{
    ਜੇ ((a+0x8000U) & ~0xFFFF) ਵਾਪਸ (a>>31) ^ 0x7FFF;
    ਨਹੀਂਤਾਂ                      ਵਾਪਸ a;
}

/**
 * Clip a signed 64-bit integer value into the -2147483648,2147483647 range.
 * @param a value to clip
 * @return clipped value
 */
ਸਥਿਰ av_always_inline av_const int32_t av_clipl_int32_c(int64_t a)
{
    ਜੇ ((a+UINT64_C(0x80000000)) & ~UINT64_C(0xFFFFFFFF)) ਵਾਪਸ (int32_t)((a>>63) ^ 0x7FFFFFFF);
    ਨਹੀਂਤਾਂ                                                  ਵਾਪਸ (int32_t)a;
}

/**
 * Clip a signed integer into the -(2^p),(2^p-1) range.
 * @param  a value to clip
 * @param  p bit position to clip at
 * @return clipped value
 */
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ av_clip_intp2_c(ਪੂਰਨ a, ਪੂਰਨ p)
{
    ਜੇ (((ਬਿਨਾਨਿਸ਼ਾਨੀ)a + (1U << p)) & ~((2U << p) - 1))
        ਵਾਪਸ (a >> 31) ^ ((1 << p) - 1);
    ਨਹੀਂਤਾਂ
        ਵਾਪਸ a;
}

/**
 * Clip a signed integer to an unsigned power of two range.
 * @param  a value to clip
 * @param  p bit position to clip at
 * @return clipped value
 */
ਸਥਿਰ av_always_inline av_const ਬਿਨਾਨਿਸ਼ਾਨੀ av_clip_uintp2_c(ਪੂਰਨ a, ਪੂਰਨ p)
{
    ਜੇ (a & ~((1U<<p) - 1)) ਵਾਪਸ (~a) >> 31 & ((1U<<p) - 1);
    ਨਹੀਂਤਾਂ                    ਵਾਪਸ  a;
}

/**
 * Clear high bits from an unsigned integer starting with specific bit position
 * @param  a value to clip
 * @param  p bit position to clip at. Must be between 0 and 31.
 * @return clipped value
 */
ਸਥਿਰ av_always_inline av_const ਬਿਨਾਨਿਸ਼ਾਨੀ av_zero_extend_c(ਬਿਨਾਨਿਸ਼ਾਨੀ a, ਬਿਨਾਨਿਸ਼ਾਨੀ p)
{
#ਜੇ defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ਜੇ (p > 31) abort();
#ਜੇ_ਅੰਤ
    ਵਾਪਸ a & ((1U << p) - 1);
}

/**
 * Add two signed 32-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return sum with signed saturation
 */
ਸਥਿਰ av_always_inline ਪੂਰਨ av_sat_add32_c(ਪੂਰਨ a, ਪੂਰਨ b)
{
    ਵਾਪਸ av_clipl_int32((int64_t)a + b);
}

/**
 * Add a doubled value to another value with saturation at both stages.
 *
 * @param  a first value
 * @param  b value doubled and added to a
 * @return sum sat(a + sat(2*b)) with signed saturation
 */
ਸਥਿਰ av_always_inline ਪੂਰਨ av_sat_dadd32_c(ਪੂਰਨ a, ਪੂਰਨ b)
{
    ਵਾਪਸ av_sat_add32(a, av_sat_add32(b, b));
}

/**
 * Subtract two signed 32-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return difference with signed saturation
 */
ਸਥਿਰ av_always_inline ਪੂਰਨ av_sat_sub32_c(ਪੂਰਨ a, ਪੂਰਨ b)
{
    ਵਾਪਸ av_clipl_int32((int64_t)a - b);
}

/**
 * Subtract a doubled value from another value with saturation at both stages.
 *
 * @param  a first value
 * @param  b value doubled and subtracted from a
 * @return difference sat(a - sat(2*b)) with signed saturation
 */
ਸਥਿਰ av_always_inline ਪੂਰਨ av_sat_dsub32_c(ਪੂਰਨ a, ਪੂਰਨ b)
{
    ਵਾਪਸ av_sat_sub32(a, av_sat_add32(b, b));
}

/**
 * Add two signed 64-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return sum with signed saturation
 */
ਸਥਿਰ av_always_inline int64_t av_sat_add64_c(int64_t a, int64_t b) {
#ਜੇ (!defined(__INTEL_COMPILER) && AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(5,1)) || AV_HAS_BUILTIN(__builtin_add_overflow)
    int64_t tmp;
    ਵਾਪਸ !__builtin_add_overflow(a, b, &tmp) ? tmp : (tmp < 0 ? INT64_MAX : INT64_MIN);
#ਨਹੀਂਤਾਂ
    int64_t s = a+(uint64_t)b;
    ਜੇ ((int64_t)(a^b | ~s^b) >= 0)
        ਵਾਪਸ INT64_MAX ^ (b >> 63);
    ਵਾਪਸ s;
#ਜੇ_ਅੰਤ
}

/**
 * Subtract two signed 64-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return difference with signed saturation
 */
ਸਥਿਰ av_always_inline int64_t av_sat_sub64_c(int64_t a, int64_t b) {
#ਜੇ (!defined(__INTEL_COMPILER) && AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(5,1)) || AV_HAS_BUILTIN(__builtin_sub_overflow)
    int64_t tmp;
    ਵਾਪਸ !__builtin_sub_overflow(a, b, &tmp) ? tmp : (tmp < 0 ? INT64_MAX : INT64_MIN);
#ਨਹੀਂਤਾਂ
    ਜੇ (b <= 0 && a >= INT64_MAX + b)
        ਵਾਪਸ INT64_MAX;
    ਜੇ (b >= 0 && a <= INT64_MIN + b)
        ਵਾਪਸ INT64_MIN;
    ਵਾਪਸ a - b;
#ਜੇ_ਅੰਤ
}

/**
 * Clip a float value into the amin-amax range.
 * If a is nan or -inf amin will be returned.
 * If a is +inf amax will be returned.
 * @param a value to clip
 * @param amin minimum value of the clip range
 * @param amax maximum value of the clip range
 * @return clipped value
 */
ਸਥਿਰ av_always_inline av_const ਦਸ਼ਮਲਵ av_clipf_c(ਦਸ਼ਮਲਵ a, ਦਸ਼ਮਲਵ amin, ਦਸ਼ਮਲਵ amax)
{
#ਜੇ defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ਜੇ (amin > amax) abort();
#ਜੇ_ਅੰਤ
    ਵਾਪਸ FFMIN(FFMAX(a, amin), amax);
}

/**
 * Clip a double value into the amin-amax range.
 * If a is nan or -inf amin will be returned.
 * If a is +inf amax will be returned.
 * @param a value to clip
 * @param amin minimum value of the clip range
 * @param amax maximum value of the clip range
 * @return clipped value
 */
ਸਥਿਰ av_always_inline av_const ਦੁੱਗਣਾ av_clipd_c(ਦੁੱਗਣਾ a, ਦੁੱਗਣਾ amin, ਦੁੱਗਣਾ amax)
{
#ਜੇ defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ਜੇ (amin > amax) abort();
#ਜੇ_ਅੰਤ
    ਵਾਪਸ FFMIN(FFMAX(a, amin), amax);
}

/** Compute ceil(log2(x)).
 * @param x value used to compute ceil(log2(x))
 * @return computed ceiling of log2(x)
 */
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ av_ceil_log2_c(ਪੂਰਨ x)
{
    ਵਾਪਸ av_log2((x - 1U) << 1);
}

/**
 * Count number of bits set to one in x
 * @param x value to count bits of
 * @return the number of bits set to one in x
 */
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ av_popcount_c(uint32_t x)
{
    x -= (x >> 1) & 0x55555555;
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x += x >> 8;
    ਵਾਪਸ (x + (x >> 16)) & 0x3F;
}

/**
 * Count number of bits set to one in x
 * @param x value to count bits of
 * @return the number of bits set to one in x
 */
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ av_popcount64_c(uint64_t x)
{
    ਵਾਪਸ av_popcount((uint32_t)x) + av_popcount((uint32_t)(x >> 32));
}

ਸਥਿਰ av_always_inline av_const ਪੂਰਨ av_parity_c(uint32_t v)
{
    ਵਾਪਸ av_popcount(v) & 1;
}

/**
 * Convert a UTF-8 character (up to 4 bytes) to its 32-bit UCS-4 encoded form.
 *
 * @param val      Output value, must be an lvalue of type uint32_t.
 * @param GET_BYTE Expression reading one byte from the input.
 *                 Evaluated up to 7 times (4 for the currently
 *                 assigned Unicode range).  With a memory buffer
 *                 input, this could be *ptr++, or if you want to make sure
 *                 that *ptr stops at the end of a NULL terminated string then
 *                 *ptr ? *ptr++ : 0
 * @param ERROR    Expression to be evaluated on invalid input,
 *                 typically a goto statement.
 *
 * @warning ERROR should not contain a loop control statement which
 * could interact with the internal while loop, and should force an
 * exit from the macro code (e.g. through a goto or a return) in order
 * to prevent undefined results.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET_UTF8(val, GET_BYTE, ERROR)\
    val= (uint8_t)(GET_BYTE);\
    {\
        uint32_t ਸਿਖਰ = (val & 128) >> 1;\
        ਜੇ ((val & 0xc0) == 0x80 || val >= 0xFE)\
            {ERROR}\
        ਜਦੋਂ (val & ਸਿਖਰ) {\
            ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ tmp = (uint8_t)(GET_BYTE) - 128;\
            ਜੇ(tmp>>6)\
                {ERROR}\
            val= (val<<6) + tmp;\
            ਸਿਖਰ <<= 5;\
        }\
        val &= (ਸਿਖਰ << 1) - 1;\
    }

/**
 * Convert a UTF-16 character (2 or 4 bytes) to its 32-bit UCS-4 encoded form.
 *
 * @param val       Output value, must be an lvalue of type uint32_t.
 * @param GET_16BIT Expression returning two bytes of UTF-16 data converted
 *                  to native byte order.  Evaluated one or two times.
 * @param ERROR     Expression to be evaluated on invalid input,
 *                  typically a goto statement.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET_UTF16(val, GET_16_ਦੋਆਧਾਰੀ_ਅੰਕ, ERROR)\
    val = (uint16_t)(GET_16_ਦੋਆਧਾਰੀ_ਅੰਕ);\
    {\
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ hi = val - 0xD800;\
        ਜੇ (hi < 0x800) {\
            val = (uint16_t)(GET_16_ਦੋਆਧਾਰੀ_ਅੰਕ) - 0xDC00;\
            ਜੇ (val > 0x3FFU || hi > 0x3FFU)\
                {ERROR}\
            val += (hi<<10) + 0x10000;\
        }\
    }\

/**
 * @def PUT_UTF8(val, tmp, PUT_BYTE)
 * Convert a 32-bit Unicode character to its UTF-8 encoded form (up to 4 bytes long).
 * @param val is an input-only argument and should be of type uint32_t. It holds
 * a UCS-4 encoded Unicode character that is to be converted to UTF-8. If
 * val is given as a function it is executed only once.
 * @param tmp is a temporary variable and should be of type uint8_t. It
 * represents an intermediate value during conversion that is to be
 * output by PUT_BYTE.
 * @param PUT_BYTE writes the converted UTF-8 bytes to any proper destination.
 * It could be a function or a statement, and uses tmp as the input byte.
 * For example, PUT_BYTE could be "*output++ = tmp;" PUT_BYTE will be
 * executed up to 4 times for values in the valid UTF-8 range and up to
 * 7 times in the general case, depending on the length of the converted
 * Unicode character.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PUT_UTF8(val, tmp, PUT_BYTE)\
    {\
        ਪੂਰਨ ਬਾਈਟਾਂ, ਖਿਸਕਾਓ;\
        uint32_t ਵਿੱਚ_2 = val;\
        ਜੇ (ਵਿੱਚ_2 < 0x80) {\
            tmp = ਵਿੱਚ_2;\
            PUT_BYTE\
        } ਨਹੀਂਤਾਂ {\
            ਬਾਈਟਾਂ = (av_log2(ਵਿੱਚ_2) + 4) / 5;\
            ਖਿਸਕਾਓ = (ਬਾਈਟਾਂ - 1) * 6;\
            tmp = (256 - (256 >> ਬਾਈਟਾਂ)) | (ਵਿੱਚ_2 >> ਖਿਸਕਾਓ);\
            PUT_BYTE\
            ਜਦੋਂ (ਖਿਸਕਾਓ >= 6) {\
                ਖਿਸਕਾਓ -= 6;\
                tmp = 0x80 | ((ਵਿੱਚ_2 >> ਖਿਸਕਾਓ) & 0x3f);\
                PUT_BYTE\
            }\
        }\
    }

/**
 * @def PUT_UTF16(val, tmp, PUT_16BIT)
 * Convert a 32-bit Unicode character to its UTF-16 encoded form (2 or 4 bytes).
 * @param val is an input-only argument and should be of type uint32_t. It holds
 * a UCS-4 encoded Unicode character that is to be converted to UTF-16. If
 * val is given as a function it is executed only once.
 * @param tmp is a temporary variable and should be of type uint16_t. It
 * represents an intermediate value during conversion that is to be
 * output by PUT_16BIT.
 * @param PUT_16BIT writes the converted UTF-16 data to any proper destination
 * in desired endianness. It could be a function or a statement, and uses tmp
 * as the input byte.  For example, PUT_BYTE could be "*output++ = tmp;"
 * PUT_BYTE will be executed 1 or 2 times depending on input character.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PUT_UTF16(val, tmp, PUT_16_ਦੋਆਧਾਰੀ_ਅੰਕ)\
    {\
        uint32_t ਵਿੱਚ_2 = val;\
        ਜੇ (ਵਿੱਚ_2 < 0x10000) {\
            tmp = ਵਿੱਚ_2;\
            PUT_16_ਦੋਆਧਾਰੀ_ਅੰਕ\
        } ਨਹੀਂਤਾਂ {\
            tmp = 0xD800 | ((ਵਿੱਚ_2 - 0x10000) >> 10);\
            PUT_16_ਦੋਆਧਾਰੀ_ਅੰਕ\
            tmp = 0xDC00 | ((ਵਿੱਚ_2 - 0x10000) & 0x3FF);\
            PUT_16_ਦੋਆਧਾਰੀ_ਅੰਕ\
        }\
    }\

#ਜੇ_ਅੰਤ /* AVUTIL_COMMON_H */
