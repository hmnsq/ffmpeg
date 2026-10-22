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

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ <limits.h>

#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "mathematics.h"
#અન્તર્ભાવ "rational.h"

પૂર્ણાંક av_reduce(પૂર્ણાંક *dst_અંક, પૂર્ણાંક *dst_den,
              int64_t અંક, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    પૂર્ણાંક sign = (અંક < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(અંક), FFABS(den));

    જો (gcd) {
        અંક = FFABS(અંક) / gcd;
        den = FFABS(den) / gcd;
    }
    જો (અંક <= max && den <= max) {
        a1 = (AVRational) { અંક, den };
        den = 0;
    }

    જ્યારે (den) {
        uint64_t x        = અંક / den;
        int64_t next_den  = અંક - den * x;
        int64_t a2n       = x * a1.અંક + a0.અંક;
        int64_t a2d       = x * a1.den + a0.den;

        જો (a2n > max || a2d > max) {
            જો (a1.અંક) x =          (max - a0.અંક) / a1.અંક;
            જો (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            જો (den * (2 * x * a1.den + a0.den) > અંક * a1.den)
                a1 = (AVRational) { x * a1.અંક + a0.અંક, x * a1.den + a0.den };
            તોડો;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        અંક = den;
        den = next_den;
    }
    av_assert2(av_gcd(a1.અંક, a1.den) <= 1U);
    av_assert2(a1.અંક <= max && a1.den <= max);

    *dst_અંક = sign ? -a1.અંક : a1.અંક;
    *dst_den = a1.den;

    પાછા den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.અંક, &b.den,
               b.અંક * (int64_t) c.અંક,
               b.den * (int64_t) c.den, INT_MAX);
    પાછા b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    પાછા av_mul_q(b, (AVRational) { c.den, c.અંક });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.અંક, &b.den,
               b.અંક * (int64_t) c.den +
               c.અંક * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    પાછા b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.અંક, &b.den,
               b.અંક * (int64_t) c.den -
               c.અંક * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    પાછા b;
}

AVRational av_d2q(દ્વિગુણ d, પૂર્ણાંક max)
{
    AVRational a;
    પૂર્ણાંક exponent;
    int64_t den;
    જો (isnan(d))
        પાછા (AVRational) { 0,0 };
    જો (fabs(d) > INT_MAX + 3LL)
        પાછા (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.અંક, &a.den, floor(d * den + 0.5), den, max);

    પાછા a;
}

પૂર્ણાંક av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.અંક * (int64_t)q2.den + q2.અંક * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    પાછા ((x_up > q.અંક) - (x_down < q.અંક)) * av_cmp_q(q2, q1);
}

પૂર્ણાંક av_find_nearest_q_idx(AVRational q, અચલ AVRational* q_list)
{
    પૂર્ણાંક i, nearest_q_idx = 0;
    માટે (i = 0; q_list[i].den; i++)
        જો (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    પાછા nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, અંક = q.અંક, den = q.den;
    પૂર્ણાંક shift;
    uint32_t sign = 0;

    જો (den < 0) {
        den = -den;
        અંક = -અંક;
    }
    જો (અંક < 0) {
        અંક = -અંક;
        sign = 1U << 31;
    }

    જો (!અંક && !den) પાછા 0xFFC00000;
    જો (!અંક) પાછા 0;
    જો (!den) પાછા sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(અંક);
    જો (shift >= 0) n = av_rescale(અંક, 1LL<<shift, den);
    નહીંતર            n = av_rescale(અંક, 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    જો (shift >= 0) n = av_rescale(અંક, 1LL<<shift, den);
    નહીંતર            n = av_rescale(અંક, 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    પાછા sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, પૂર્ણાંક max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    પાછા lcm < max_den ? av_make_q(av_gcd(a.અંક, b.અંક), lcm) : def;
}
