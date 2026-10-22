/*
 * rational numbers
 * Copyright (c) 2003 Michael Niedermayer <michaelni@gmx.at>
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
 * @ingroup lavu_math_rational
 * Utilities for rational number calculation.
 * @author Michael Niedermayer <michaelni@gmx.at>
 */

#ifndef AVUTIL_RATIONAL_H
#define AVUTIL_RATIONAL_H

#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ "attributes.h"

/**
 * @defgroup lavu_math_rational AVRational
 * @ingroup lavu_math
 * Rational number calculation.
 *
 * While rational numbers can be expressed as floating-point numbers, the
 * conversion process is a lossy one, so are floating-point operations. On the
 * other hand, the nature of FFmpeg demands highly accurate calculation of
 * timestamps. This set of rational number utilities serves as a generic
 * interface for manipulating rational numbers as pairs of numerators and
 * denominators.
 *
 * Many of the functions that operate on AVRational's have the suffix `_q`, in
 * reference to the mathematical symbol "ℚ" (Q) which denotes the set of all
 * rational numbers.
 *
 * @{
 */

/**
 * Rational number (pair of numerator and denominator).
 */
પ્રકારવ્યાખ્યા સંરચના AVRational{
    પૂર્ણાંક અંક; ///< Numerator
    પૂર્ણાંક den; ///< Denominator
} AVRational;

/**
 * Create an AVRational.
 *
 * Useful for compilers that do not support compound literals.
 *
 * @note The return value is not reduced.
 * @see av_reduce()
 */
સ્થિર અંતઃરેખ AVRational av_make_q(પૂર્ણાંક અંક, પૂર્ણાંક den)
{
    AVRational r = { અંક, den };
    પાછા r;
}

/**
 * Compare two rationals.
 *
 * @param a First rational
 * @param b Second rational
 *
 * @return One of the following values:
 *         - 0 if `a == b`
 *         - 1 if `a > b`
 *         - -1 if `a < b`
 *         - `INT_MIN` if one of the values is of the form `0 / 0`
 */
સ્થિર અંતઃરેખ પૂર્ણાંક av_cmp_q(AVRational a, AVRational b){
    અચલ int64_t tmp= a.અંક * (int64_t)b.den - b.અંક * (int64_t)a.den;

    જો(tmp) પાછા (પૂર્ણાંક)((tmp ^ a.den ^ b.den)>>63)|1;
    નહીંતર જો(b.den && a.den) પાછા 0;
    નહીંતર જો(a.અંક && b.અંક) પાછા (a.અંક>>31) - (b.અંક>>31);
    નહીંતર                    પાછા INT_MIN;
}

/**
 * Convert an AVRational to a `double`.
 * @param a AVRational to convert
 * @return `a` in floating-point form
 * @see av_d2q()
 */
સ્થિર અંતઃરેખ દ્વિગુણ av_q2d(AVRational a){
    પાછા a.અંક / (દ્વિગુણ) a.den;
}

/**
 * Reduce a fraction.
 *
 * This is useful for framerate calculations.
 *
 * @param[out] dst_num Destination numerator
 * @param[out] dst_den Destination denominator
 * @param[in]      num Source numerator
 * @param[in]      den Source denominator
 * @param[in]      max Maximum allowed values for `dst_num` & `dst_den`
 * @return 1 if the operation is exact, 0 otherwise
 */
પૂર્ણાંક av_reduce(પૂર્ણાંક *dst_અંક, પૂર્ણાંક *dst_den, int64_t અંક, int64_t den, int64_t max);

/**
 * Multiply two rationals.
 * @param b First rational
 * @param c Second rational
 * @return b*c
 */
AVRational av_mul_q(AVRational b, AVRational c) av_const;

/**
 * Divide one rational by another.
 * @param b First rational
 * @param c Second rational
 * @return b/c
 */
AVRational av_div_q(AVRational b, AVRational c) av_const;

/**
 * Add two rationals.
 * @param b First rational
 * @param c Second rational
 * @return b+c
 */
AVRational av_add_q(AVRational b, AVRational c) av_const;

/**
 * Subtract one rational from another.
 * @param b First rational
 * @param c Second rational
 * @return b-c
 */
AVRational av_sub_q(AVRational b, AVRational c) av_const;

/**
 * Invert a rational.
 * @param q value
 * @return 1 / q
 */
સ્થિર av_always_inline AVRational av_inv_q(AVRational q)
{
    AVRational r = { q.den, q.અંક };
    પાછા r;
}

/**
 * Convert a double precision floating point number to a rational.
 *
 * In case of infinity, the returned value is expressed as `{1, 0}` or
 * `{-1, 0}` depending on the sign.
 *
 * In general rational numbers with |num| <= 1<<26 && |den| <= 1<<26
 * can be recovered exactly from their double representation.
 * (no exceptions were found within 1B random ones)
 *
 * @param d   `double` to convert
 * @param max Maximum allowed numerator and denominator
 * @return `d` in AVRational form
 * @see av_q2d()
 */
AVRational av_d2q(દ્વિગુણ d, પૂર્ણાંક max) av_const;

/**
 * Find which of the two rationals is closer to another rational.
 *
 * @param q     Rational to be compared against
 * @param q1    Rational to be tested
 * @param q2    Rational to be tested
 * @return One of the following values:
 *         - 1 if `q1` is nearer to `q` than `q2`
 *         - -1 if `q2` is nearer to `q` than `q1`
 *         - 0 if they have the same distance
 */
પૂર્ણાંક av_nearer_q(AVRational q, AVRational q1, AVRational q2);

/**
 * Find the value in a list of rationals nearest a given reference rational.
 *
 * @param q      Reference rational
 * @param q_list Array of rationals terminated by `{0, 0}`
 * @return Index of the nearest value found in the array
 */
પૂર્ણાંક av_find_nearest_q_idx(AVRational q, અચલ AVRational* q_list);

/**
 * Convert an AVRational to a IEEE 32-bit `float` expressed in fixed-point
 * format.
 *
 * @param q Rational to be converted
 * @return Equivalent floating-point value, expressed as an unsigned 32-bit
 *         integer.
 * @note The returned value is platform-indepedant.
 */
uint32_t av_q2intfloat(AVRational q);

/**
 * Return the best rational so that a and b are multiple of it.
 * If the resulting denominator is larger than max_den, return def.
 */
AVRational av_gcd_q(AVRational a, AVRational b, પૂર્ણાંક max_den, AVRational def);

/**
 * @}
 */

#endif /* AVUTIL_RATIONAL_H */
