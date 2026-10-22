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
 * rational numbers
 * @author Michael Niedermayer <michaelni@gmx.at>
 */

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ <limits.h>

#அந்தர்பாவ "common.h"
#அந்தர்பாவ "mathematics.h"
#அந்தர்பாவ "rational.h"

முழு av_reduce(முழு *dst_இலக்கம், முழு *dst_den,
              int64_t இலக்கம், int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    முழு sign = (இலக்கம் < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(இலக்கம்), FFABS(den));

    எனில் (gcd) {
        இலக்கம் = FFABS(இலக்கம்) / gcd;
        den = FFABS(den) / gcd;
    }
    எனில் (இலக்கம் <= max && den <= max) {
        a1 = (AVRational) { இலக்கம், den };
        den = 0;
    }

    போது (den) {
        uint64_t x        = இலக்கம் / den;
        int64_t next_den  = இலக்கம் - den * x;
        int64_t a2n       = x * a1.இலக்கம் + a0.இலக்கம்;
        int64_t a2d       = x * a1.den + a0.den;

        எனில் (a2n > max || a2d > max) {
            எனில் (a1.இலக்கம்) x =          (max - a0.இலக்கம்) / a1.இலக்கம்;
            எனில் (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            எனில் (den * (2 * x * a1.den + a0.den) > இலக்கம் * a1.den)
                a1 = (AVRational) { x * a1.இலக்கம் + a0.இலக்கம், x * a1.den + a0.den };
            நிறுத்து;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        இலக்கம் = den;
        den = next_den;
    }
    av_assert2(av_gcd(a1.இலக்கம், a1.den) <= 1U);
    av_assert2(a1.இலக்கம் <= max && a1.den <= max);

    *dst_இலக்கம் = sign ? -a1.இலக்கம் : a1.இலக்கம்;
    *dst_den = a1.den;

    திரும்பு den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.இலக்கம், &b.den,
               b.இலக்கம் * (int64_t) c.இலக்கம்,
               b.den * (int64_t) c.den, INT_MAX);
    திரும்பு b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    திரும்பு av_mul_q(b, (AVRational) { c.den, c.இலக்கம் });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.இலக்கம், &b.den,
               b.இலக்கம் * (int64_t) c.den +
               c.இலக்கம் * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    திரும்பு b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.இலக்கம், &b.den,
               b.இலக்கம் * (int64_t) c.den -
               c.இலக்கம் * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    திரும்பு b;
}

AVRational av_d2q(இரட்டை d, முழு max)
{
    AVRational a;
    முழு exponent;
    int64_t den;
    எனில் (isnan(d))
        திரும்பு (AVRational) { 0,0 };
    எனில் (fabs(d) > INT_MAX + 3LL)
        திரும்பு (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.இலக்கம், &a.den, floor(d * den + 0.5), den, max);

    திரும்பு a;
}

முழு av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.இலக்கம் * (int64_t)q2.den + q2.இலக்கம் * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    திரும்பு ((x_up > q.இலக்கம்) - (x_down < q.இலக்கம்)) * av_cmp_q(q2, q1);
}

முழு av_find_nearest_q_idx(AVRational q, மாறிலி AVRational* q_list)
{
    முழு i, nearest_q_idx = 0;
    க்கு (i = 0; q_list[i].den; i++)
        எனில் (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    திரும்பு nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, இலக்கம் = q.இலக்கம், den = q.den;
    முழு shift;
    uint32_t sign = 0;

    எனில் (den < 0) {
        den = -den;
        இலக்கம் = -இலக்கம்;
    }
    எனில் (இலக்கம் < 0) {
        இலக்கம் = -இலக்கம்;
        sign = 1U << 31;
    }

    எனில் (!இலக்கம் && !den) திரும்பு 0xFFC00000;
    எனில் (!இலக்கம்) திரும்பு 0;
    எனில் (!den) திரும்பு sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(இலக்கம்);
    எனில் (shift >= 0) n = av_rescale(இலக்கம், 1LL<<shift, den);
    இல்லையெனில்            n = av_rescale(இலக்கம், 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    எனில் (shift >= 0) n = av_rescale(இலக்கம், 1LL<<shift, den);
    இல்லையெனில்            n = av_rescale(இலக்கம், 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    திரும்பு sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, முழு max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    திரும்பு lcm < max_den ? av_make_q(av_gcd(a.இலக்கம், b.இலக்கம்), lcm) : def;
}
