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

#अगर_अघोषित AVUTIL_COMMON_H
#घोषणा AVUTIL_COMMON_H

#अगर defined(__cplusplus) && !defined(__STDC_CONSTANT_MACROS) && !defined(UINT64_C)
#त्रुटि missing -D__STDC_CONSTANT_MACROS / #घोषणा __STDC_CONSTANT_MACROS
#पूर्ण_अगर

#समावेश <errno.h>
#समावेश <inttypes.h>
#समावेश <limits.h>
#समावेश <math.h>
#समावेश <stdint.h>
#समावेश <stdio.h>
#समावेश <stdlib.h>
#समावेश <string.h>

#समावेश "attributes.h"
#समावेश "error.h"
#समावेश "macros.h"
#समावेश "version.h"

#अगर_घोषित HAVE_AV_CONFIG_H
#   include "config.h"
#   include "intmath.h"
#   include "internal.h"
#अन्यथा
#   include "mem.h"
#पूर्ण_अगर /* HAVE_AV_CONFIG_H */

//rounded division & shift
#घोषणा RSHIFT(a,b) ((a) > 0 ? ((a) + ((1<<(b))>>1))>>(b) : ((a) + ((1<<(b))>>1)-1)>>(b))
/* assume b>0 */
#घोषणा ROUNDED_DIV(a,b) (((a)>=0 ? (a) + ((b)>>1) : (a) - ((b)>>1))/(b))
/* Fast a/(1<<b) rounded toward +inf. Assume a>=0 and b>=0 */
#घोषणा AV_CEIL_RSHIFT(a,b) (!av_builtin_constant_p(b) ? -((-(a)) >> (b)) \
                                                       : ((a) + (1<<(b)) - 1) >> (b))
/* Backwards compat. */
#घोषणा FF_CEIL_RSHIFT AV_CEIL_RSHIFT

#घोषणा FFUDIV(a,b) (((a)>0 ?(a):(a)-(b)+1) / (b))
#घोषणा FFUMOD(a,b) ((a)-(b)*FFUDIV(a,b))

/**
 * Absolute value, Note, INT_MIN / INT64_MIN result in undefined behavior as they
 * are not representable as absolute values of their type. This is the same
 * as with *abs()
 * @see FFNABS()
 */
#घोषणा FFABS(a) ((a) >= 0 ? (a) : (-(a)))
#घोषणा FFSIGN(a) ((a) > 0 ? 1 : -1)

/**
 * Negative Absolute value.
 * this works for all integers of all types.
 * As with many macros, this evaluates its argument twice, it thus must not have
 * a sideeffect, that is FFNABS(x++) has undefined behavior.
 */
#घोषणा FFNABS(a) ((a) <= 0 ? (a) : (-(a)))

/**
 * Unsigned Absolute value.
 * This takes the absolute value of a signed int and returns it as a unsigned.
 * This also works with INT_MIN which would otherwise not be representable
 * As with many macros, this evaluates its argument twice.
 */
#घोषणा FFABSU(a) ((a) <= 0 ? -(अचिन्हित)(a) : (अचिन्हित)(a))
#घोषणा FFABS64U(a) ((a) <= 0 ? -(uint64_t)(a) : (uint64_t)(a))

/* misc math functions */

#अगर_अघोषित av_ceil_log2
#   define av_ceil_log2     av_ceil_log2_c
#पूर्ण_अगर
#अगर_अघोषित av_clip
#   define av_clip          av_clip_c
#पूर्ण_अगर
#अगर_अघोषित av_clip64
#   define av_clip64        av_clip64_c
#पूर्ण_अगर
#अगर_अघोषित av_clip_uint8
#   define av_clip_uint8    av_clip_uint8_c
#पूर्ण_अगर
#अगर_अघोषित av_clip_int8
#   define av_clip_int8     av_clip_int8_c
#पूर्ण_अगर
#अगर_अघोषित av_clip_uint16
#   define av_clip_uint16   av_clip_uint16_c
#पूर्ण_अगर
#अगर_अघोषित av_clip_int16
#   define av_clip_int16    av_clip_int16_c
#पूर्ण_अगर
#अगर_अघोषित av_clipl_int32
#   define av_clipl_int32   av_clipl_int32_c
#पूर्ण_अगर
#अगर_अघोषित av_clip_intp2
#   define av_clip_intp2    av_clip_intp2_c
#पूर्ण_अगर
#अगर_अघोषित av_clip_uintp2
#   define av_clip_uintp2   av_clip_uintp2_c
#पूर्ण_अगर
#अगर_अघोषित av_sat_add32
#   define av_sat_add32     av_sat_add32_c
#पूर्ण_अगर
#अगर_अघोषित av_sat_dadd32
#   define av_sat_dadd32    av_sat_dadd32_c
#पूर्ण_अगर
#अगर_अघोषित av_sat_sub32
#   define av_sat_sub32     av_sat_sub32_c
#पूर्ण_अगर
#अगर_अघोषित av_sat_dsub32
#   define av_sat_dsub32    av_sat_dsub32_c
#पूर्ण_अगर
#अगर_अघोषित av_sat_add64
#   define av_sat_add64     av_sat_add64_c
#पूर्ण_अगर
#अगर_अघोषित av_sat_sub64
#   define av_sat_sub64     av_sat_sub64_c
#पूर्ण_अगर
#अगर_अघोषित av_clipf
#   define av_clipf         av_clipf_c
#पूर्ण_अगर
#अगर_अघोषित av_clipd
#   define av_clipd         av_clipd_c
#पूर्ण_अगर
#अगर_अघोषित av_zero_extend
#   define av_zero_extend   av_zero_extend_c
#पूर्ण_अगर
#अगर_अघोषित av_popcount
#   define av_popcount      av_popcount_c
#पूर्ण_अगर
#अगर_अघोषित av_popcount64
#   define av_popcount64    av_popcount64_c
#पूर्ण_अगर
#अगर_अघोषित av_parity
#   define av_parity        av_parity_c
#पूर्ण_अगर

#अगर_अघोषित av_log2
av_const पूर्णांक av_log2(अचिन्हित v);
#पूर्ण_अगर

#अगर_अघोषित av_log2_16bit
av_const पूर्णांक av_log2_16bit(अचिन्हित v);
#पूर्ण_अगर

/**
 * Clip a signed integer value into the amin-amax range.
 * @param a value to clip
 * @param amin minimum value of the clip range
 * @param amax maximum value of the clip range
 * @return clipped value
 */
अटल av_always_inline av_const पूर्णांक av_clip_c(पूर्णांक a, पूर्णांक amin, पूर्णांक amax)
{
#अगर defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    अगर (amin > amax) पात();
#पूर्ण_अगर
    अगर      (a < amin) वापस amin;
    अन्यथा अगर (a > amax) वापस amax;
    अन्यथा               वापस a;
}

/**
 * Clip a signed 64bit integer value into the amin-amax range.
 * @param a value to clip
 * @param amin minimum value of the clip range
 * @param amax maximum value of the clip range
 * @return clipped value
 */
अटल av_always_inline av_const int64_t av_clip64_c(int64_t a, int64_t amin, int64_t amax)
{
#अगर defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    अगर (amin > amax) पात();
#पूर्ण_अगर
    अगर      (a < amin) वापस amin;
    अन्यथा अगर (a > amax) वापस amax;
    अन्यथा               वापस a;
}

/**
 * Clip a signed integer value into the 0-255 range.
 * @param a value to clip
 * @return clipped value
 */
अटल av_always_inline av_const uint8_t av_clip_uint8_c(पूर्णांक a)
{
    अगर (a&(~0xFF)) वापस (~a)>>31;
    अन्यथा           वापस a;
}

/**
 * Clip a signed integer value into the -128,127 range.
 * @param a value to clip
 * @return clipped value
 */
अटल av_always_inline av_const int8_t av_clip_int8_c(पूर्णांक a)
{
    अगर ((a+0x80U) & ~0xFF) वापस (a>>31) ^ 0x7F;
    अन्यथा                  वापस a;
}

/**
 * Clip a signed integer value into the 0-65535 range.
 * @param a value to clip
 * @return clipped value
 */
अटल av_always_inline av_const uint16_t av_clip_uint16_c(पूर्णांक a)
{
    अगर (a&(~0xFFFF)) वापस (~a)>>31;
    अन्यथा             वापस a;
}

/**
 * Clip a signed integer value into the -32768,32767 range.
 * @param a value to clip
 * @return clipped value
 */
अटल av_always_inline av_const int16_t av_clip_int16_c(पूर्णांक a)
{
    अगर ((a+0x8000U) & ~0xFFFF) वापस (a>>31) ^ 0x7FFF;
    अन्यथा                      वापस a;
}

/**
 * Clip a signed 64-bit integer value into the -2147483648,2147483647 range.
 * @param a value to clip
 * @return clipped value
 */
अटल av_always_inline av_const int32_t av_clipl_int32_c(int64_t a)
{
    अगर ((a+UINT64_C(0x80000000)) & ~UINT64_C(0xFFFFFFFF)) वापस (int32_t)((a>>63) ^ 0x7FFFFFFF);
    अन्यथा                                                  वापस (int32_t)a;
}

/**
 * Clip a signed integer into the -(2^p),(2^p-1) range.
 * @param  a value to clip
 * @param  p bit position to clip at
 * @return clipped value
 */
अटल av_always_inline av_const पूर्णांक av_clip_intp2_c(पूर्णांक a, पूर्णांक p)
{
    अगर (((अचिन्हित)a + (1U << p)) & ~((2U << p) - 1))
        वापस (a >> 31) ^ ((1 << p) - 1);
    अन्यथा
        वापस a;
}

/**
 * Clip a signed integer to an unsigned power of two range.
 * @param  a value to clip
 * @param  p bit position to clip at
 * @return clipped value
 */
अटल av_always_inline av_const अचिन्हित av_clip_uintp2_c(पूर्णांक a, पूर्णांक p)
{
    अगर (a & ~((1U<<p) - 1)) वापस (~a) >> 31 & ((1U<<p) - 1);
    अन्यथा                    वापस  a;
}

/**
 * Clear high bits from an unsigned integer starting with specific bit position
 * @param  a value to clip
 * @param  p bit position to clip at. Must be between 0 and 31.
 * @return clipped value
 */
अटल av_always_inline av_const अचिन्हित av_zero_extend_c(अचिन्हित a, अचिन्हित p)
{
#अगर defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    अगर (p > 31) पात();
#पूर्ण_अगर
    वापस a & ((1U << p) - 1);
}

/**
 * Add two signed 32-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return sum with signed saturation
 */
अटल av_always_inline पूर्णांक av_sat_add32_c(पूर्णांक a, पूर्णांक b)
{
    वापस av_clipl_int32((int64_t)a + b);
}

/**
 * Add a doubled value to another value with saturation at both stages.
 *
 * @param  a first value
 * @param  b value doubled and added to a
 * @return sum sat(a + sat(2*b)) with signed saturation
 */
अटल av_always_inline पूर्णांक av_sat_dadd32_c(पूर्णांक a, पूर्णांक b)
{
    वापस av_sat_add32(a, av_sat_add32(b, b));
}

/**
 * Subtract two signed 32-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return difference with signed saturation
 */
अटल av_always_inline पूर्णांक av_sat_sub32_c(पूर्णांक a, पूर्णांक b)
{
    वापस av_clipl_int32((int64_t)a - b);
}

/**
 * Subtract a doubled value from another value with saturation at both stages.
 *
 * @param  a first value
 * @param  b value doubled and subtracted from a
 * @return difference sat(a - sat(2*b)) with signed saturation
 */
अटल av_always_inline पूर्णांक av_sat_dsub32_c(पूर्णांक a, पूर्णांक b)
{
    वापस av_sat_sub32(a, av_sat_add32(b, b));
}

/**
 * Add two signed 64-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return sum with signed saturation
 */
अटल av_always_inline int64_t av_sat_add64_c(int64_t a, int64_t b) {
#अगर (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_add_overflow)
    int64_t tmp;
    वापस !__builtin_add_overflow(a, b, &tmp) ? tmp : (tmp < 0 ? INT64_MAX : INT64_MIN);
#अन्यथा
    int64_t s = a+(uint64_t)b;
    अगर ((int64_t)(a^b | ~s^b) >= 0)
        वापस INT64_MAX ^ (b >> 63);
    वापस s;
#पूर्ण_अगर
}

/**
 * Subtract two signed 64-bit values with saturation.
 *
 * @param  a one value
 * @param  b another value
 * @return difference with signed saturation
 */
अटल av_always_inline int64_t av_sat_sub64_c(int64_t a, int64_t b) {
#अगर (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_sub_overflow)
    int64_t tmp;
    वापस !__builtin_sub_overflow(a, b, &tmp) ? tmp : (tmp < 0 ? INT64_MAX : INT64_MIN);
#अन्यथा
    अगर (b <= 0 && a >= INT64_MAX + b)
        वापस INT64_MAX;
    अगर (b >= 0 && a <= INT64_MIN + b)
        वापस INT64_MIN;
    वापस a - b;
#पूर्ण_अगर
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
अटल av_always_inline av_const भग्न av_clipf_c(भग्न a, भग्न amin, भग्न amax)
{
#अगर defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    अगर (amin > amax) पात();
#पूर्ण_अगर
    वापस FFMIN(FFMAX(a, amin), amax);
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
अटल av_always_inline av_const द्विगुन av_clipd_c(द्विगुन a, द्विगुन amin, द्विगुन amax)
{
#अगर defined(HAVE_AV_CONFIG_H) && defined(ASSERT_LEVEL) && ASSERT_LEVEL >= 2
    अगर (amin > amax) पात();
#पूर्ण_अगर
    वापस FFMIN(FFMAX(a, amin), amax);
}

/** Compute ceil(log2(x)).
 * @param x value used to compute ceil(log2(x))
 * @return computed ceiling of log2(x)
 */
अटल av_always_inline av_const पूर्णांक av_ceil_log2_c(पूर्णांक x)
{
    वापस av_log2((x - 1U) << 1);
}

/**
 * Count number of bits set to one in x
 * @param x value to count bits of
 * @return the number of bits set to one in x
 */
अटल av_always_inline av_const पूर्णांक av_popcount_c(uint32_t x)
{
    x -= (x >> 1) & 0x55555555;
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x += x >> 8;
    वापस (x + (x >> 16)) & 0x3F;
}

/**
 * Count number of bits set to one in x
 * @param x value to count bits of
 * @return the number of bits set to one in x
 */
अटल av_always_inline av_const पूर्णांक av_popcount64_c(uint64_t x)
{
    वापस av_popcount((uint32_t)x) + av_popcount((uint32_t)(x >> 32));
}

अटल av_always_inline av_const पूर्णांक av_parity_c(uint32_t v)
{
    वापस av_popcount(v) & 1;
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
#घोषणा GET_UTF8(val, GET_BYTE, ERROR)\
    val= (uint8_t)(GET_BYTE);\
    {\
        uint32_t शीर्ष = (val & 128) >> 1;\
        अगर ((val & 0xc0) == 0x80 || val >= 0xFE)\
            {ERROR}\
        जबतक (val & शीर्ष) {\
            अचिन्हित पूर्णांक tmp = (uint8_t)(GET_BYTE) - 128;\
            अगर(tmp>>6)\
                {ERROR}\
            val= (val<<6) + tmp;\
            शीर्ष <<= 5;\
        }\
        val &= (शीर्ष << 1) - 1;\
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
#घोषणा GET_UTF16(val, GET_16BIT, ERROR)\
    val = (uint16_t)(GET_16BIT);\
    {\
        अचिन्हित पूर्णांक hi = val - 0xD800;\
        अगर (hi < 0x800) {\
            val = (uint16_t)(GET_16BIT) - 0xDC00;\
            अगर (val > 0x3FFU || hi > 0x3FFU)\
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
#घोषणा PUT_UTF8(val, tmp, PUT_BYTE)\
    {\
        पूर्णांक bytes, shift;\
        uint32_t in = val;\
        अगर (in < 0x80) {\
            tmp = in;\
            PUT_BYTE\
        } अन्यथा {\
            bytes = (av_log2(in) + 4) / 5;\
            shift = (bytes - 1) * 6;\
            tmp = (256 - (256 >> bytes)) | (in >> shift);\
            PUT_BYTE\
            जबतक (shift >= 6) {\
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
#घोषणा PUT_UTF16(val, tmp, PUT_16BIT)\
    {\
        uint32_t in = val;\
        अगर (in < 0x10000) {\
            tmp = in;\
            PUT_16BIT\
        } अन्यथा {\
            tmp = 0xD800 | ((in - 0x10000) >> 10);\
            PUT_16BIT\
            tmp = 0xDC00 | ((in - 0x10000) & 0x3FF);\
            PUT_16BIT\
        }\
    }\

#पूर्ण_अगर /* AVUTIL_COMMON_H */
