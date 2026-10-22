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

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব <limits.h>

#অন্তর্ভাব "common.h"
#অন্তর্ভাব "mathematics.h"
#অন্তর্ভাব "rational.h"

পূর্ণাঙ্ক av_reduce(পূর্ণাঙ্ক *dst_অঙ্ক, পূর্ণাঙ্ক *dst_den,
              int64_t অঙ্ক, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    পূর্ণাঙ্ক sign = (অঙ্ক < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(অঙ্ক), FFABS(den));

    যদি (gcd) {
        অঙ্ক = FFABS(অঙ্ক) / gcd;
        den = FFABS(den) / gcd;
    }
    যদি (অঙ্ক <= max && den <= max) {
        a1 = (AVRational) { অঙ্ক, den };
        den = 0;
    }

    যাবত্ (den) {
        uint64_t x        = অঙ্ক / den;
        int64_t next_den  = অঙ্ক - den * x;
        int64_t a2n       = x * a1.অঙ্ক + a0.অঙ্ক;
        int64_t a2d       = x * a1.den + a0.den;

        যদি (a2n > max || a2d > max) {
            যদি (a1.অঙ্ক) x =          (max - a0.অঙ্ক) / a1.অঙ্ক;
            যদি (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            যদি (den * (2 * x * a1.den + a0.den) > অঙ্ক * a1.den)
                a1 = (AVRational) { x * a1.অঙ্ক + a0.অঙ্ক, x * a1.den + a0.den };
            ভঙ্গ;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        অঙ্ক = den;
        den = next_den;
    }
    av_assert2(av_gcd(a1.অঙ্ক, a1.den) <= 1U);
    av_assert2(a1.অঙ্ক <= max && a1.den <= max);

    *dst_অঙ্ক = sign ? -a1.অঙ্ক : a1.অঙ্ক;
    *dst_den = a1.den;

    প্রত্যাগম den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.অঙ্ক, &b.den,
               b.অঙ্ক * (int64_t) c.অঙ্ক,
               b.den * (int64_t) c.den, INT_MAX);
    প্রত্যাগম b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    প্রত্যাগম av_mul_q(b, (AVRational) { c.den, c.অঙ্ক });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.অঙ্ক, &b.den,
               b.অঙ্ক * (int64_t) c.den +
               c.অঙ্ক * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    প্রত্যাগম b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.অঙ্ক, &b.den,
               b.অঙ্ক * (int64_t) c.den -
               c.অঙ্ক * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    প্রত্যাগম b;
}

AVRational av_d2q(দ্বিগুণ d, পূর্ণাঙ্ক max)
{
    AVRational a;
    পূর্ণাঙ্ক exponent;
    int64_t den;
    যদি (isnan(d))
        প্রত্যাগম (AVRational) { 0,0 };
    যদি (fabs(d) > INT_MAX + 3LL)
        প্রত্যাগম (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.অঙ্ক, &a.den, floor(d * den + 0.5), den, max);

    প্রত্যাগম a;
}

পূর্ণাঙ্ক av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.অঙ্ক * (int64_t)q2.den + q2.অঙ্ক * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    প্রত্যাগম ((x_up > q.অঙ্ক) - (x_down < q.অঙ্ক)) * av_cmp_q(q2, q1);
}

পূর্ণাঙ্ক av_find_nearest_q_idx(AVRational q, ধ্রুব AVRational* q_list)
{
    পূর্ণাঙ্ক i, nearest_q_idx = 0;
    প্রতি (i = 0; q_list[i].den; i++)
        যদি (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    প্রত্যাগম nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, অঙ্ক = q.অঙ্ক, den = q.den;
    পূর্ণাঙ্ক shift;
    uint32_t sign = 0;

    যদি (den < 0) {
        den = -den;
        অঙ্ক = -অঙ্ক;
    }
    যদি (অঙ্ক < 0) {
        অঙ্ক = -অঙ্ক;
        sign = 1U << 31;
    }

    যদি (!অঙ্ক && !den) প্রত্যাগম 0xFFC00000;
    যদি (!অঙ্ক) প্রত্যাগম 0;
    যদি (!den) প্রত্যাগম sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(অঙ্ক);
    যদি (shift >= 0) n = av_rescale(অঙ্ক, 1LL<<shift, den);
    অন্যথা            n = av_rescale(অঙ্ক, 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    যদি (shift >= 0) n = av_rescale(অঙ্ক, 1LL<<shift, den);
    অন্যথা            n = av_rescale(অঙ্ক, 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    প্রত্যাগম sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, পূর্ণাঙ্ক max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    প্রত্যাগম lcm < max_den ? av_make_q(av_gcd(a.অঙ্ক, b.অঙ্ক), lcm) : def;
}
