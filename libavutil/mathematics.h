/*
 * copyright (c) 2005-2012 Michael Niedermayer <michaelni@gmx.at>
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
 * @addtogroup lavu_math
 * Mathematical utilities for working with timestamp and time base.
 */

#यदि_अपरिभाषितम् AVUTIL_MATHEMATICS_H
#परिभाषय AVUTIL_MATHEMATICS_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <math.h>
#अन्तर्भाव "attributes.h"
#अन्तर्भाव "rational.h"
#अन्तर्भाव "intfloat.h"

#यदि_अपरिभाषितम् M_E
#परिभाषय M_E            2.7182818284590452354   /* e */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_Ef
#परिभाषय M_Ef           2.7182818284590452354f  /* e */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_LN2
#परिभाषय M_LN2          0.69314718055994530942  /* log_e 2 */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_LN2f
#परिभाषय M_LN2f         0.69314718055994530942f /* log_e 2 */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_LN10
#परिभाषय M_LN10         2.30258509299404568402  /* log_e 10 */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_LN10f
#परिभाषय M_LN10f        2.30258509299404568402f /* log_e 10 */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_LOG2_10
#परिभाषय M_LOG2_10      3.32192809488736234787  /* log_2 10 */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_LOG2_10f
#परिभाषय M_LOG2_10f     3.32192809488736234787f /* log_2 10 */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_PHI
#परिभाषय M_PHI          1.61803398874989484820   /* phi / golden ratio */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_PHIf
#परिभाषय M_PHIf         1.61803398874989484820f  /* phi / golden ratio */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_PI
#परिभाषय M_PI           3.14159265358979323846  /* pi */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_PIf
#परिभाषय M_PIf          3.14159265358979323846f /* pi */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_PI_2
#परिभाषय M_PI_2         1.57079632679489661923  /* pi/2 */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_PI_2f
#परिभाषय M_PI_2f        1.57079632679489661923f /* pi/2 */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_PI_4
#परिभाषय M_PI_4         0.78539816339744830962  /* pi/4 */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_PI_4f
#परिभाषय M_PI_4f        0.78539816339744830962f /* pi/4 */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_1_PI
#परिभाषय M_1_PI         0.31830988618379067154  /* 1/pi */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_1_PIf
#परिभाषय M_1_PIf        0.31830988618379067154f /* 1/pi */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_2_PI
#परिभाषय M_2_PI         0.63661977236758134308  /* 2/pi */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_2_PIf
#परिभाषय M_2_PIf        0.63661977236758134308f /* 2/pi */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_2_SQRTPI
#परिभाषय M_2_SQRTPI     1.12837916709551257390  /* 2/sqrt(pi) */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_2_SQRTPIf
#परिभाषय M_2_SQRTPIf    1.12837916709551257390f /* 2/sqrt(pi) */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_SQRT1_2
#परिभाषय M_SQRT1_2      0.70710678118654752440  /* 1/sqrt(2) */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_SQRT1_2f
#परिभाषय M_SQRT1_2f     0.70710678118654752440f /* 1/sqrt(2) */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_SQRT2
#परिभाषय M_SQRT2        1.41421356237309504880  /* sqrt(2) */
#यदि_अन्तः
#यदि_अपरिभाषितम् M_SQRT2f
#परिभाषय M_SQRT2f       1.41421356237309504880f /* sqrt(2) */
#यदि_अन्तः
#यदि_अपरिभाषितम् NAN
#परिभाषय NAN            av_int2float(0x7fc00000)
#यदि_अन्तः
#यदि_अपरिभाषितम् INFINITY
#परिभाषय INFINITY       av_int2float(0x7f800000)
#यदि_अन्तः

/**
 * @addtogroup lavu_math
 *
 * @{
 */

/**
 * Rounding methods.
 */
गणना AVRounding {
    AV_आवर्तनम्_ZERO     = 0, ///< Round toward zero.
    AV_आवर्तनम्_INF      = 1, ///< Round away from zero.
    AV_आवर्तनम्_अधस्तात्     = 2, ///< Round toward -infinity.
    AV_आवर्तनम्_ऊर्ध्वम्       = 3, ///< Round toward +infinity.
    AV_आवर्तनम्_NEAR_INF = 5, ///< Round to nearest and halfway cases away from zero.
    /**
     * Flag telling rescaling functions to pass `INT64_MIN`/`MAX` through
     * unchanged, avoiding special cases for #AV_NOPTS_VALUE.
     *
     * Unlike other values of the enumeration AVRounding, this value is a
     * bitmask that must be used in conjunction with another value of the
     * enumeration through a bitwise OR, in order to set behavior for normal
     * cases.
     *
     * @code{.c}
     * av_rescale_rnd(3, 1, 2, AV_ROUND_UP | AV_ROUND_PASS_MINMAX);
     * // Rescaling 3:
     * //     Calculating 3 * 1 / 2
     * //     3 / 2 is rounded up to 2
     * //     => 2
     *
     * av_rescale_rnd(AV_NOPTS_VALUE, 1, 2, AV_ROUND_UP | AV_ROUND_PASS_MINMAX);
     * // Rescaling AV_NOPTS_VALUE:
     * //     AV_NOPTS_VALUE == INT64_MIN
     * //     AV_NOPTS_VALUE is passed through
     * //     => AV_NOPTS_VALUE
     * @endcode
     */
    AV_आवर्तनम्_PASS_MINMAX = 8192,
};

/**
 * Compute the greatest common divisor of two integer operands.
 *
 * @param a Operand
 * @param b Operand
 * @return GCD of a and b up to sign; if a >= 0 and b >= 0, return value is >= 0;
 * if a == 0 and b == 0, returns 0.
 */
int64_t av_const av_gcd(int64_t a, int64_t b);

/**
 * Rescale a 64-bit integer with rounding to nearest.
 *
 * The operation is mathematically equivalent to `a * b / c`, but writing that
 * directly can overflow.
 *
 * This function is equivalent to av_rescale_rnd() with #AV_ROUND_NEAR_INF.
 *
 * @see av_rescale_rnd(), av_rescale_q(), av_rescale_q_rnd()
 */
int64_t av_rescale(int64_t a, int64_t b, int64_t c) av_const;

/**
 * Rescale a 64-bit integer with specified rounding.
 *
 * The operation is mathematically equivalent to `a * b / c`, but writing that
 * directly can overflow, and does not support different rounding methods.
 * If the result is not representable then INT64_MIN is returned.
 *
 * @see av_rescale(), av_rescale_q(), av_rescale_q_rnd()
 */
int64_t av_rescale_rnd(int64_t a, int64_t b, int64_t c, गणना AVRounding rnd) av_const;

/**
 * Rescale a 64-bit integer by 2 rational numbers.
 *
 * The operation is mathematically equivalent to `a * bq / cq`.
 *
 * This function is equivalent to av_rescale_q_rnd() with #AV_ROUND_NEAR_INF.
 *
 * @see av_rescale(), av_rescale_rnd(), av_rescale_q_rnd()
 */
int64_t av_rescale_q(int64_t a, AVRational bq, AVRational cq) av_const;

/**
 * Rescale a 64-bit integer by 2 rational numbers with specified rounding.
 *
 * The operation is mathematically equivalent to `a * bq / cq`.
 *
 * @see av_rescale(), av_rescale_rnd(), av_rescale_q()
 */
int64_t av_rescale_q_rnd(int64_t a, AVRational bq, AVRational cq,
                         गणना AVRounding rnd) av_const;

/**
 * Compare two timestamps each in its own time base.
 *
 * @return One of the following values:
 *         - -1 if `ts_a` is before `ts_b`
 *         - 1 if `ts_a` is after `ts_b`
 *         - 0 if they represent the same position
 *
 * @warning
 * The result of the function is undefined if one of the timestamps is outside
 * the `int64_t` range when represented in the other's timebase.
 */
पूर्णाङ्क av_compare_ts(int64_t ts_a, AVRational tb_a, int64_t ts_b, AVRational tb_b);

/**
 * Compare the remainders of two integer operands divided by a common divisor.
 *
 * In other words, compare the least significant `log2(mod)` bits of integers
 * `a` and `b`.
 *
 * @code{.c}
 * av_compare_mod(0x11, 0x02, 0x10) < 0 // since 0x11 % 0x10  (0x1) < 0x02 % 0x10  (0x2)
 * av_compare_mod(0x11, 0x02, 0x20) > 0 // since 0x11 % 0x20 (0x11) > 0x02 % 0x20 (0x02)
 * @endcode
 *
 * @param a Operand
 * @param b Operand
 * @param mod Divisor; must be a power of 2
 * @return
 *         - a negative value if `a % mod < b % mod`
 *         - a positive value if `a % mod > b % mod`
 *         - zero             if `a % mod == b % mod`
 */
int64_t av_compare_mod(uint64_t a, uint64_t b, uint64_t mod);

/**
 * Rescale a timestamp while preserving known durations.
 *
 * This function is designed to be called per audio packet to scale the input
 * timestamp to a different time base. Compared to a simple av_rescale_q()
 * call, this function is robust against possible inconsistent frame durations.
 *
 * The `last` parameter is a state variable that must be preserved for all
 * subsequent calls for the same stream. For the first call, `*last` should be
 * initialized to #AV_NOPTS_VALUE.
 *
 * @param[in]     in_tb    Input time base
 * @param[in]     in_ts    Input timestamp
 * @param[in]     fs_tb    Duration time base; typically this is finer-grained
 *                         (greater) than `in_tb` and `out_tb`
 * @param[in]     duration Duration till the next call to this function (i.e.
 *                         duration of the current packet/frame)
 * @param[in,out] last     Pointer to a timestamp expressed in terms of
 *                         `fs_tb`, acting as a state variable
 * @param[in]     out_tb   Output timebase
 * @return        Timestamp expressed in terms of `out_tb`
 *
 * @note In the context of this function, "duration" is in term of samples, not
 *       seconds.
 */
int64_t av_rescale_delta(AVRational अन्तर्_tb, int64_t अन्तर्_ts,  AVRational fs_tb, पूर्णाङ्क duration, int64_t *चरमः, AVRational बहिर्गमनम्_tb);

/**
 * Add a value to a timestamp.
 *
 * This function guarantees that when the same value is repeatedly added that
 * no accumulation of rounding errors occurs.
 *
 * @param[in] ts     Input timestamp
 * @param[in] ts_tb  Input timestamp time base
 * @param[in] inc    Value to be added
 * @param[in] inc_tb Time base of `inc`
 */
int64_t av_सङ्कलय_stable(AVRational ts_tb, int64_t ts, AVRational inc_tb, int64_t inc);

/**
 * 0th order modified bessel function of the first kind.
 */
द्विगुण av_bessel_i0(द्विगुण x);

/**
 * @}
 */

#यदि_अन्तः /* AVUTIL_MATHEMATICS_H */
