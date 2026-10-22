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

#నిర్వచితం_కాకపోతే AVUTIL_COMMON_H
#నిర్వచించు AVUTIL_COMMON_H

#ఒకవేళ defined(__cplusplus) && !defined(__STDC_CONSTANT_MACROS) && !defined(UINT64_C)
#దోషం missing -D__STDC_CONSTANT_MACROS / #నిర్వచించు __STDC_CONSTANT_MACROS
#అయితే_ముగింపు

#అన్తర్భావ <errno.h>
#అన్తర్భావ <inttypes.h>
#అన్తర్భావ <limits.h>
#అన్తర్భావ <math.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "attributes.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "version.h"

#నిర్వచితమైతే HAVE_AV_CONFIG_H
#   include "config.h"
#   include "intmath.h"
#   include "internal.h"
#లేకపోతే
#   include "mem.h"
#అయితే_ముగింపు /* HAVE_AV_CONFIG_H */

//rounded division & shift
#నిర్వచించు RSHIFT(a,b) ((a) > 0 ? ((a) + ((1<<(b))>>1))>>(b) : ((a) + ((1<<(b))>>1)-1)>>(b))
/* assume b>0 */
#నిర్వచించు ROUNDED_DIV(a,b) (((a)>=0 ? (a) + ((b)>>1) : (a) - ((b)>>1))/(b))
/* Fast a/(1<<b) rounded toward +inf. Assume a>=0 and b>=0 */
#నిర్వచించు AV_CEIL_RSHIFT(a,b) (!av_builtin_constant_p(b) ? -((-(a)) >> (b)) \
                                                       : ((a) + (1<<(b)) - 1) >> (b))
/* Backwards compat. */
#నిర్వచించు FF_CEIL_RSHIFT AV_CEIL_RSHIFT

#నిర్వచించు FFUDIV(a,b) (((a)>0 ?(a):(a)-(b)+1) / (b))
#నిర్వచించు FFUMOD(a,b) ((a)-(b)*FFUDIV(a,b))

/**
 * Absolute value, Note, INT_MIN / INT64_MIN result in undefined behavior as they
 * are not representable as absolute values of their type. This is the same
 * as with *abs()
 * @see FFNABS()
 */
#నిర్వచించు FFABS(a) ((a) >= 0 ? (a) : (-(a)))
#నిర్వచించు FFSIGN(a) ((a) > 0 ? 1 : -1)

/**
 * Negative Absolute value.
 * this works for all integers of all types.
 * As with many macros, this evaluates its argument twice, it thus must not have
 * a sideeffect, that is FFNABS(x++) has undefined behavior.
 */
#నిర్వచించు FFNABS(a) ((a) <= 0 ? (a) : (-(a)))

/**
 * Unsigned Absolute value.
 * This takes the absolute value of a signed int and returns it as a unsigned.
 * This also works with INT_MIN which would otherwise not be representable
 * As with many macros, this evaluates its argument twice.
 */
#నిర్వచించు FFABSU(a) ((a) <= 0 ? -(గుర్తులేని)(a) : (గుర్తులేని)(a))
#నిర్వచించు FFABS64U(a) ((a) <= 0 ? -(uint64_t)(a) : (uint64_t)(a))

/* misc math functions */

#నిర్వచితం_కాకపోతే av_ceil_log2
#   define av_ceil_log2     av_ceil_log2_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_clip
#   define av_clip          av_clip_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_clip64
#   define av_clip64        av_clip64_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_clip_uint8
#   define av_clip_uint8    av_clip_uint8_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_clip_int8
#   define av_clip_int8     av_clip_int8_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_clip_uint16
#   define av_clip_uint16   av_clip_uint16_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_clip_int16
#   define av_clip_int16    av_clip_int16_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_clipl_int32
#   define av_clipl_int32   av_clipl_int32_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_clip_intp2
#   define av_clip_intp2    av_clip_intp2_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_clip_uintp2
#   define av_clip_uintp2   av_clip_uintp2_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_sat_add32
#   define av_sat_add32     av_sat_add32_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_sat_dadd32
#   define av_sat_dadd32    av_sat_dadd32_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_sat_sub32
#   define av_sat_sub32     av_sat_sub32_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_sat_dsub32
#   define av_sat_dsub32    av_sat_dsub32_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_sat_add64
#   define av_sat_add64     av_sat_add64_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_sat_sub64
#   define av_sat_sub64     av_sat_sub64_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_clipf
#   define av_clipf         av_clipf_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_clipd
#   define av_clipd         av_clipd_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_zero_extend
#   define av_zero_extend   av_zero_extend_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_popcount
#   define av_popcount      av_popcount_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_popcount64
#   define av_popcount64    av_popcount64_c
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే av_parity
#   define av_parity        av_parity_c
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే av_log2
av_const పూర్ణాంకం av_log2(గుర్తులేని v);
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే av_log2_16bit
av_const పూర్ణాంకం av_log2_16bit(గుర్తులేని v);
#అయితే_ముగింపు

/**
 * Clip a signed integer value into the amin-amax range.
 * @param a value to clip
 * @param amin minimum value of the clip range
 * @param amax maximum value of the clip range
 * @return clipped value
 */
స్థిర av_always_inline av_const పూర్ణాంకం av_clip_c(పూర్ణాంకం a, పూర్ణాంకం amin, పూర్ణాంకం amax)
{
#ఒకవేళ defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ఒకవేళ (amin > amax) abort();
#అయితే_ముగింపు
    ఒకవేళ      (a < amin) తిరిగి amin;
    లేకపోతే ఒకవేళ (a > amax) తిరిగి amax;
    లేకపోతే               తిరిగి a;
}

/**
 * Clip a signed 64bit integer value into the amin-amax range.
 * @param a value to clip
 * @param amin minimum value of the clip range
 * @param amax maximum value of the clip range
 * @return clipped value
 */
స్థిర av_always_inline av_const int64_t av_clip64_c(int64_t a, int64_t amin, int64_t amax)
{
#ఒకవేళ defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ఒకవేళ (amin > amax) abort();
#అయితే_ముగింపు
    ఒకవేళ      (a < amin) తిరిగి amin;
    లేకపోతే ఒకవేళ (a > amax) తిరిగి amax;
    లేకపోతే               తిరిగి a;
}

/**
 * Clip a signed integer value into the 0-255 range.
 * @param a value to clip
 * @return clipped value
 */
స్థిర av_always_inline av_const uint8_t av_clip_uint8_c(పూర్ణాంకం a)
{
    ఒకవేళ (a&(~0xFF)) తిరిగి (~a)>>31;
    లేకపోతే           తిరిగి a;
}

/**
 * Clip a signed integer value into the -128,127 range.
 * @param a value to clip
 * @return clipped value
 */
స్థిర av_always_inline av_const int8_t av_clip_int8_c(పూర్ణాంకం a)
{
    ఒకవేళ ((a+0x80U) & ~0xFF) తిరిగి (a>>31) ^ 0x7F;
    లేకపోతే                  తిరిగి a;
}

/**
 * Clip a signed integer value into the 0-65535 range.
 * @param a value to clip
 * @return clipped value
 */
స్థిర av_always_inline av_const uint16_t av_clip_uint16_c(పూర్ణాంకం a)
{
    ఒకవేళ (a&(~0xFFFF)) తిరిగి (~a)>>31;
    లేకపోతే             తిరిగి a;
}

/**
 * Clip a signed integer value into the -32768,32767 range.
 * @param a value to clip
 * @return clipped value
 */
స్థిర av_always_inline av_const int16_t av_clip_int16_c(పూర్ణాంకం a)
{
    ఒకవేళ ((a+0x8000U) & ~0xFFFF) తిరిగి (a>>31) ^ 0x7FFF;
    లేకపోతే                      తిరిగి a;
}

/**
 * Clip a signed 64-bit integer value into the -2147483648,2147483647 range.
 * @param a value to clip
 * @return clipped value
 */
స్థిర av_always_inline av_const int32_t av_clipl_int32_c(int64_t a)
{
    ఒకవేళ ((a+UINT64_C(0x80000000)) & ~UINT64_C(0xFFFFFFFF)) తిరిగి (int32_t)((a>>63) ^ 0x7FFFFFFF);
    లేకపోతే                                                  తిరిగి (int32_t)a;
}

/**
 * Clip a signed integer into the -(2^p),(2^p-1) range.
 * @param  a value to clip
 * @param  p bit position to clip at
 * @return clipped value
 */
స్థిర av_always_inline av_const పూర్ణాంకం av_clip_intp2_c(పూర్ణాంకం a, పూర్ణాంకం p)
{
    ఒకవేళ (((గుర్తులేని)a + (1U << p)) & ~((2U << p) - 1))
        తిరిగి (a >> 31) ^ ((1 << p) - 1);
    లేకపోతే
        తిరిగి a;
}

/**
 * Clip a signed integer to an unsigned power of two range.
 * @param  a value to clip
 * @param  p bit position to clip at
 * @return clipped value
 */
స్థిర av_always_inline av_const గుర్తులేని av_clip_uintp2_c(పూర్ణాంకం a, పూర్ణాంకం p)
{
    ఒకవేళ (a & ~((1U<<p) - 1)) తిరిగి (~a) >> 31 & ((1U<<p) - 1);
    లేకపోతే                    తిరిగి  a;
}

/**
 * Clear high bits from an unsigned integer starting with specific bit position
 * @param  a value to clip
 * @param  p bit position to clip at. Must be between 0 and 31.
 * @return clipped value
 */
స్థిర av_always_inline av_const గుర్తులేని av_zero_extend_c(గుర్తులేని a, గుర్తులేని p)
{
#ఒకవేళ defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ఒకవేళ (p > 31) abort();
#అయితే_ముగింపు
    తిరిగి a & ((1U << p) - 1);
}

/**
 * Add two signed 32-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return sum with signed saturation
 */
స్థిర av_always_inline పూర్ణాంకం av_sat_add32_c(పూర్ణాంకం a, పూర్ణాంకం b)
{
    తిరిగి av_clipl_int32((int64_t)a + b);
}

/**
 * Add a doubled value to another value with saturation at both stages.
 *
 * @param  a first value
 * @param  b value doubled and added to a
 * @return sum sat(a + sat(2*b)) with signed saturation
 */
స్థిర av_always_inline పూర్ణాంకం av_sat_dadd32_c(పూర్ణాంకం a, పూర్ణాంకం b)
{
    తిరిగి av_sat_add32(a, av_sat_add32(b, b));
}

/**
 * Subtract two signed 32-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return difference with signed saturation
 */
స్థిర av_always_inline పూర్ణాంకం av_sat_sub32_c(పూర్ణాంకం a, పూర్ణాంకం b)
{
    తిరిగి av_clipl_int32((int64_t)a - b);
}

/**
 * Subtract a doubled value from another value with saturation at both stages.
 *
 * @param  a first value
 * @param  b value doubled and subtracted from a
 * @return difference sat(a - sat(2*b)) with signed saturation
 */
స్థిర av_always_inline పూర్ణాంకం av_sat_dsub32_c(పూర్ణాంకం a, పూర్ణాంకం b)
{
    తిరిగి av_sat_sub32(a, av_sat_add32(b, b));
}

/**
 * Add two signed 64-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return sum with signed saturation
 */
స్థిర av_always_inline int64_t av_sat_add64_c(int64_t a, int64_t b) {
#ఒకవేళ (!defined(__INTEL_COMPILER) && AV_GCC_సంస్కరణ_AT_కనిష్ఠ(5,1)) || AV_HAS_BUILTIN(__builtin_add_overflow)
    int64_t tmp;
    తిరిగి !__builtin_add_overflow(a, b, &tmp) ? tmp : (tmp < 0 ? INT64_MAX : INT64_MIN);
#లేకపోతే
    int64_t s = a+(uint64_t)b;
    ఒకవేళ ((int64_t)(a^b | ~s^b) >= 0)
        తిరిగి INT64_MAX ^ (b >> 63);
    తిరిగి s;
#అయితే_ముగింపు
}

/**
 * Subtract two signed 64-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return difference with signed saturation
 */
స్థిర av_always_inline int64_t av_sat_sub64_c(int64_t a, int64_t b) {
#ఒకవేళ (!defined(__INTEL_COMPILER) && AV_GCC_సంస్కరణ_AT_కనిష్ఠ(5,1)) || AV_HAS_BUILTIN(__builtin_sub_overflow)
    int64_t tmp;
    తిరిగి !__builtin_sub_overflow(a, b, &tmp) ? tmp : (tmp < 0 ? INT64_MAX : INT64_MIN);
#లేకపోతే
    ఒకవేళ (b <= 0 && a >= INT64_MAX + b)
        తిరిగి INT64_MAX;
    ఒకవేళ (b >= 0 && a <= INT64_MIN + b)
        తిరిగి INT64_MIN;
    తిరిగి a - b;
#అయితే_ముగింపు
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
స్థిర av_always_inline av_const దశాంశం av_clipf_c(దశాంశం a, దశాంశం amin, దశాంశం amax)
{
#ఒకవేళ defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ఒకవేళ (amin > amax) abort();
#అయితే_ముగింపు
    తిరిగి FFMIN(FFMAX(a, amin), amax);
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
స్థిర av_always_inline av_const ద్విగుణ av_clipd_c(ద్విగుణ a, ద్విగుణ amin, ద్విగుణ amax)
{
#ఒకవేళ defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    ఒకవేళ (amin > amax) abort();
#అయితే_ముగింపు
    తిరిగి FFMIN(FFMAX(a, amin), amax);
}

/** Compute ceil(log2(x)).
 * @param x value used to compute ceil(log2(x))
 * @return computed ceiling of log2(x)
 */
స్థిర av_always_inline av_const పూర్ణాంకం av_ceil_log2_c(పూర్ణాంకం x)
{
    తిరిగి av_log2((x - 1U) << 1);
}

/**
 * Count number of bits set to one in x
 * @param x value to count bits of
 * @return the number of bits set to one in x
 */
స్థిర av_always_inline av_const పూర్ణాంకం av_popcount_c(uint32_t x)
{
    x -= (x >> 1) & 0x55555555;
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x += x >> 8;
    తిరిగి (x + (x >> 16)) & 0x3F;
}

/**
 * Count number of bits set to one in x
 * @param x value to count bits of
 * @return the number of bits set to one in x
 */
స్థిర av_always_inline av_const పూర్ణాంకం av_popcount64_c(uint64_t x)
{
    తిరిగి av_popcount((uint32_t)x) + av_popcount((uint32_t)(x >> 32));
}

స్థిర av_always_inline av_const పూర్ణాంకం av_parity_c(uint32_t v)
{
    తిరిగి av_popcount(v) & 1;
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
#నిర్వచించు GET_UTF8(val, GET_BYTE, ERROR)\
    val= (uint8_t)(GET_BYTE);\
    {\
        uint32_t శిఖరం = (val & 128) >> 1;\
        ఒకవేళ ((val & 0xc0) == 0x80 || val >= 0xFE)\
            {ERROR}\
        అయితే (val & శిఖరం) {\
            గుర్తులేని పూర్ణాంకం tmp = (uint8_t)(GET_BYTE) - 128;\
            ఒకవేళ(tmp>>6)\
                {ERROR}\
            val= (val<<6) + tmp;\
            శిఖరం <<= 5;\
        }\
        val &= (శిఖరం << 1) - 1;\
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
#నిర్వచించు GET_UTF16(val, GET_16_బిట్టు, ERROR)\
    val = (uint16_t)(GET_16_బిట్టు);\
    {\
        గుర్తులేని పూర్ణాంకం hi = val - 0xD800;\
        ఒకవేళ (hi < 0x800) {\
            val = (uint16_t)(GET_16_బిట్టు) - 0xDC00;\
            ఒకవేళ (val > 0x3FFU || hi > 0x3FFU)\
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
#నిర్వచించు PUT_UTF8(val, tmp, PUT_BYTE)\
    {\
        పూర్ణాంకం బైట్లు, జరుపు;\
        uint32_t లోపల = val;\
        ఒకవేళ (లోపల < 0x80) {\
            tmp = లోపల;\
            PUT_BYTE\
        } లేకపోతే {\
            బైట్లు = (av_log2(లోపల) + 4) / 5;\
            జరుపు = (బైట్లు - 1) * 6;\
            tmp = (256 - (256 >> బైట్లు)) | (లోపల >> జరుపు);\
            PUT_BYTE\
            అయితే (జరుపు >= 6) {\
                జరుపు -= 6;\
                tmp = 0x80 | ((లోపల >> జరుపు) & 0x3f);\
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
#నిర్వచించు PUT_UTF16(val, tmp, PUT_16_బిట్టు)\
    {\
        uint32_t లోపల = val;\
        ఒకవేళ (లోపల < 0x10000) {\
            tmp = లోపల;\
            PUT_16_బిట్టు\
        } లేకపోతే {\
            tmp = 0xD800 | ((లోపల - 0x10000) >> 10);\
            PUT_16_బిట్టు\
            tmp = 0xDC00 | ((లోపల - 0x10000) & 0x3FF);\
            PUT_16_బిట్టు\
        }\
    }\

#అయితే_ముగింపు /* AVUTIL_COMMON_H */
