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

#ifndef AVUTIL_COMMON_H
#define AVUTIL_COMMON_H

#எனில் defined(__cplusplus) && !defined(__STDC_CONSTANT_MACROS) && !defined(UINT64_C)
#error missing -D__STDC_CONSTANT_MACROS / #define __STDC_CONSTANT_MACROS
#endif

#அந்தர்பாவ <errno.h>
#அந்தர்பாவ <inttypes.h>
#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <math.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "attributes.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "version.h"

#ifdef HAVE_AV_CONFIG_H
#   include "config.h"
#   include "intmath.h"
#   include "internal.h"
#இல்லையெனில்
#   include "mem.h"
#endif /* HAVE_AV_CONFIG_H */

//rounded division & shift
#define RSHIFT(a,b) ((a) > 0 ? ((a) + ((1<<(b))>>1))>>(b) : ((a) + ((1<<(b))>>1)-1)>>(b))
/* assume b>0 */
#define ROUNDED_DIV(a,b) (((a)>=0 ? (a) + ((b)>>1) : (a) - ((b)>>1))/(b))
/* Fast a/(1<<b) rounded toward +inf. Assume a>=0 and b>=0 */
#define AV_CEIL_RSHIFT(a,b) (!av_builtin_constant_p(b) ? -((-(a)) >> (b)) \
                                                       : ((a) + (1<<(b)) - 1) >> (b))
/* Backwards compat. */
#define FF_CEIL_RSHIFT AV_CEIL_RSHIFT

#define FFUDIV(a,b) (((a)>0 ?(a):(a)-(b)+1) / (b))
#define FFUMOD(a,b) ((a)-(b)*FFUDIV(a,b))

/**
 * Absolute value, Note, INT_MIN / INT64_MIN result in undefined behavior as they
 * are not representable as absolute values of their type. This is the same
 * as with *abs()
 * @see FFNABS()
 */
#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))
#define FFSIGN(a) ((a) > 0 ? 1 : -1)

/**
 * Negative Absolute value.
 * this works for all integers of all types.
 * As with many macros, this evaluates its argument twice, it thus must not have
 * a sideeffect, that is FFNABS(x++) has undefined behavior.
 */
#define FFNABS(a) ((a) <= 0 ? (a) : (-(a)))

/**
 * Unsigned Absolute value.
 * This takes the absolute value of a signed int and returns it as a unsigned.
 * This also works with INT_MIN which would otherwise not be representable
 * As with many macros, this evaluates its argument twice.
 */
#define FFABSU(a) ((a) <= 0 ? -(unsigned)(a) : (unsigned)(a))
#define FFABS64U(a) ((a) <= 0 ? -(uint64_t)(a) : (uint64_t)(a))

/* misc math functions */

#ifndef av_ceil_log2
#   define av_ceil_log2     av_ceil_log2_c
#endif
#ifndef av_clip
#   define av_clip          av_clip_c
#endif
#ifndef av_clip64
#   define av_clip64        av_clip64_c
#endif
#ifndef av_clip_uint8
#   define av_clip_uint8    av_clip_uint8_c
#endif
#ifndef av_clip_int8
#   define av_clip_int8     av_clip_int8_c
#endif
#ifndef av_clip_uint16
#   define av_clip_uint16   av_clip_uint16_c
#endif
#ifndef av_clip_int16
#   define av_clip_int16    av_clip_int16_c
#endif
#ifndef av_clipl_int32
#   define av_clipl_int32   av_clipl_int32_c
#endif
#ifndef av_clip_intp2
#   define av_clip_intp2    av_clip_intp2_c
#endif
#ifndef av_clip_uintp2
#   define av_clip_uintp2   av_clip_uintp2_c
#endif
#ifndef av_sat_add32
#   define av_sat_add32     av_sat_add32_c
#endif
#ifndef av_sat_dadd32
#   define av_sat_dadd32    av_sat_dadd32_c
#endif
#ifndef av_sat_sub32
#   define av_sat_sub32     av_sat_sub32_c
#endif
#ifndef av_sat_dsub32
#   define av_sat_dsub32    av_sat_dsub32_c
#endif
#ifndef av_sat_add64
#   define av_sat_add64     av_sat_add64_c
#endif
#ifndef av_sat_sub64
#   define av_sat_sub64     av_sat_sub64_c
#endif
#ifndef av_clipf
#   define av_clipf         av_clipf_c
#endif
#ifndef av_clipd
#   define av_clipd         av_clipd_c
#endif
#ifndef av_zero_extend
#   define av_zero_extend   av_zero_extend_c
#endif
#ifndef av_popcount
#   define av_popcount      av_popcount_c
#endif
#ifndef av_popcount64
#   define av_popcount64    av_popcount64_c
#endif
#ifndef av_parity
#   define av_parity        av_parity_c
#endif

#ifndef av_log2
av_const முழு av_log2(unsigned v);
#endif

#ifndef av_log2_16bit
av_const முழு av_log2_16bit(unsigned v);
#endif

/**
 * Clip a signed integer value into the amin-amax range.
 * @param a value to clip
 * @param amin minimum value of the clip range
 * @param amax maximum value of the clip range
 * @return clipped value
 */
நிலையான av_always_inline av_const முழு av_clip_c(முழு a, முழு amin, முழு amax)
{
#எனில் defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    எனில் (amin > amax) abort();
#endif
    எனில்      (a < amin) திரும்பு amin;
    இல்லையெனில் எனில் (a > amax) திரும்பு amax;
    இல்லையெனில்               திரும்பு a;
}

/**
 * Clip a signed 64bit integer value into the amin-amax range.
 * @param a value to clip
 * @param amin minimum value of the clip range
 * @param amax maximum value of the clip range
 * @return clipped value
 */
நிலையான av_always_inline av_const int64_t av_clip64_c(int64_t a, int64_t amin, int64_t amax)
{
#எனில் defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    எனில் (amin > amax) abort();
#endif
    எனில்      (a < amin) திரும்பு amin;
    இல்லையெனில் எனில் (a > amax) திரும்பு amax;
    இல்லையெனில்               திரும்பு a;
}

/**
 * Clip a signed integer value into the 0-255 range.
 * @param a value to clip
 * @return clipped value
 */
நிலையான av_always_inline av_const uint8_t av_clip_uint8_c(முழு a)
{
    எனில் (a&(~0xFF)) திரும்பு (~a)>>31;
    இல்லையெனில்           திரும்பு a;
}

/**
 * Clip a signed integer value into the -128,127 range.
 * @param a value to clip
 * @return clipped value
 */
நிலையான av_always_inline av_const int8_t av_clip_int8_c(முழு a)
{
    எனில் ((a+0x80U) & ~0xFF) திரும்பு (a>>31) ^ 0x7F;
    இல்லையெனில்                  திரும்பு a;
}

/**
 * Clip a signed integer value into the 0-65535 range.
 * @param a value to clip
 * @return clipped value
 */
நிலையான av_always_inline av_const uint16_t av_clip_uint16_c(முழு a)
{
    எனில் (a&(~0xFFFF)) திரும்பு (~a)>>31;
    இல்லையெனில்             திரும்பு a;
}

/**
 * Clip a signed integer value into the -32768,32767 range.
 * @param a value to clip
 * @return clipped value
 */
நிலையான av_always_inline av_const int16_t av_clip_int16_c(முழு a)
{
    எனில் ((a+0x8000U) & ~0xFFFF) திரும்பு (a>>31) ^ 0x7FFF;
    இல்லையெனில்                      திரும்பு a;
}

/**
 * Clip a signed 64-bit integer value into the -2147483648,2147483647 range.
 * @param a value to clip
 * @return clipped value
 */
நிலையான av_always_inline av_const int32_t av_clipl_int32_c(int64_t a)
{
    எனில் ((a+UINT64_C(0x80000000)) & ~UINT64_C(0xFFFFFFFF)) திரும்பு (int32_t)((a>>63) ^ 0x7FFFFFFF);
    இல்லையெனில்                                                  திரும்பு (int32_t)a;
}

/**
 * Clip a signed integer into the -(2^p),(2^p-1) range.
 * @param  a value to clip
 * @param  p bit position to clip at
 * @return clipped value
 */
நிலையான av_always_inline av_const முழு av_clip_intp2_c(முழு a, முழு p)
{
    எனில் (((unsigned)a + (1U << p)) & ~((2U << p) - 1))
        திரும்பு (a >> 31) ^ ((1 << p) - 1);
    இல்லையெனில்
        திரும்பு a;
}

/**
 * Clip a signed integer to an unsigned power of two range.
 * @param  a value to clip
 * @param  p bit position to clip at
 * @return clipped value
 */
நிலையான av_always_inline av_const unsigned av_clip_uintp2_c(முழு a, முழு p)
{
    எனில் (a & ~((1U<<p) - 1)) திரும்பு (~a) >> 31 & ((1U<<p) - 1);
    இல்லையெனில்                    திரும்பு  a;
}

/**
 * Clear high bits from an unsigned integer starting with specific bit position
 * @param  a value to clip
 * @param  p bit position to clip at. Must be between 0 and 31.
 * @return clipped value
 */
நிலையான av_always_inline av_const unsigned av_zero_extend_c(unsigned a, unsigned p)
{
#எனில் defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    எனில் (p > 31) abort();
#endif
    திரும்பு a & ((1U << p) - 1);
}

/**
 * Add two signed 32-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return sum with signed saturation
 */
நிலையான av_always_inline முழு av_sat_add32_c(முழு a, முழு b)
{
    திரும்பு av_clipl_int32((int64_t)a + b);
}

/**
 * Add a doubled value to another value with saturation at both stages.
 *
 * @param  a first value
 * @param  b value doubled and added to a
 * @return sum sat(a + sat(2*b)) with signed saturation
 */
நிலையான av_always_inline முழு av_sat_dadd32_c(முழு a, முழு b)
{
    திரும்பு av_sat_add32(a, av_sat_add32(b, b));
}

/**
 * Subtract two signed 32-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return difference with signed saturation
 */
நிலையான av_always_inline முழு av_sat_sub32_c(முழு a, முழு b)
{
    திரும்பு av_clipl_int32((int64_t)a - b);
}

/**
 * Subtract a doubled value from another value with saturation at both stages.
 *
 * @param  a first value
 * @param  b value doubled and subtracted from a
 * @return difference sat(a - sat(2*b)) with signed saturation
 */
நிலையான av_always_inline முழு av_sat_dsub32_c(முழு a, முழு b)
{
    திரும்பு av_sat_sub32(a, av_sat_add32(b, b));
}

/**
 * Add two signed 64-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return sum with signed saturation
 */
நிலையான av_always_inline int64_t av_sat_add64_c(int64_t a, int64_t b) {
#எனில் (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_add_overflow)
    int64_t tmp;
    திரும்பு !__builtin_add_overflow(a, b, &tmp) ? tmp : (tmp < 0 ? INT64_MAX : INT64_MIN);
#இல்லையெனில்
    int64_t s = a+(uint64_t)b;
    எனில் ((int64_t)(a^b | ~s^b) >= 0)
        திரும்பு INT64_MAX ^ (b >> 63);
    திரும்பு s;
#endif
}

/**
 * Subtract two signed 64-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return difference with signed saturation
 */
நிலையான av_always_inline int64_t av_sat_sub64_c(int64_t a, int64_t b) {
#எனில் (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_sub_overflow)
    int64_t tmp;
    திரும்பு !__builtin_sub_overflow(a, b, &tmp) ? tmp : (tmp < 0 ? INT64_MAX : INT64_MIN);
#இல்லையெனில்
    எனில் (b <= 0 && a >= INT64_MAX + b)
        திரும்பு INT64_MAX;
    எனில் (b >= 0 && a <= INT64_MIN + b)
        திரும்பு INT64_MIN;
    திரும்பு a - b;
#endif
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
நிலையான av_always_inline av_const தசம av_clipf_c(தசம a, தசம amin, தசம amax)
{
#எனில் defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    எனில் (amin > amax) abort();
#endif
    திரும்பு FFMIN(FFMAX(a, amin), amax);
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
நிலையான av_always_inline av_const இரட்டை av_clipd_c(இரட்டை a, இரட்டை amin, இரட்டை amax)
{
#எனில் defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    எனில் (amin > amax) abort();
#endif
    திரும்பு FFMIN(FFMAX(a, amin), amax);
}

/** Compute ceil(log2(x)).
 * @param x value used to compute ceil(log2(x))
 * @return computed ceiling of log2(x)
 */
நிலையான av_always_inline av_const முழு av_ceil_log2_c(முழு x)
{
    திரும்பு av_log2((x - 1U) << 1);
}

/**
 * Count number of bits set to one in x
 * @param x value to count bits of
 * @return the number of bits set to one in x
 */
நிலையான av_always_inline av_const முழு av_popcount_c(uint32_t x)
{
    x -= (x >> 1) & 0x55555555;
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x += x >> 8;
    திரும்பு (x + (x >> 16)) & 0x3F;
}

/**
 * Count number of bits set to one in x
 * @param x value to count bits of
 * @return the number of bits set to one in x
 */
நிலையான av_always_inline av_const முழு av_popcount64_c(uint64_t x)
{
    திரும்பு av_popcount((uint32_t)x) + av_popcount((uint32_t)(x >> 32));
}

நிலையான av_always_inline av_const முழு av_parity_c(uint32_t v)
{
    திரும்பு av_popcount(v) & 1;
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
#define GET_UTF8(val, GET_BYTE, ERROR)\
    val= (uint8_t)(GET_BYTE);\
    {\
        uint32_t உச்சி = (val & 128) >> 1;\
        எனில் ((val & 0xc0) == 0x80 || val >= 0xFE)\
            {ERROR}\
        போது (val & உச்சி) {\
            unsigned முழு tmp = (uint8_t)(GET_BYTE) - 128;\
            எனில்(tmp>>6)\
                {ERROR}\
            val= (val<<6) + tmp;\
            உச்சி <<= 5;\
        }\
        val &= (உச்சி << 1) - 1;\
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
#define GET_UTF16(val, GET_16BIT, ERROR)\
    val = (uint16_t)(GET_16BIT);\
    {\
        unsigned முழு hi = val - 0xD800;\
        எனில் (hi < 0x800) {\
            val = (uint16_t)(GET_16BIT) - 0xDC00;\
            எனில் (val > 0x3FFU || hi > 0x3FFU)\
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
#define PUT_UTF8(val, tmp, PUT_BYTE)\
    {\
        முழு bytes, shift;\
        uint32_t in = val;\
        எனில் (in < 0x80) {\
            tmp = in;\
            PUT_BYTE\
        } இல்லையெனில் {\
            bytes = (av_log2(in) + 4) / 5;\
            shift = (bytes - 1) * 6;\
            tmp = (256 - (256 >> bytes)) | (in >> shift);\
            PUT_BYTE\
            போது (shift >= 6) {\
                shift -= 6;\
                tmp = 0x80 | ((in >> shift) & 0x3f);\
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
#define PUT_UTF16(val, tmp, PUT_16BIT)\
    {\
        uint32_t in = val;\
        எனில் (in < 0x10000) {\
            tmp = in;\
            PUT_16BIT\
        } இல்லையெனில் {\
            tmp = 0xD800 | ((in - 0x10000) >> 10);\
            PUT_16BIT\
            tmp = 0xDC00 | ((in - 0x10000) & 0x3FF);\
            PUT_16BIT\
        }\
    }\

#endif /* AVUTIL_COMMON_H */
