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

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ <limits.h>

#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "mathematics.h"
#ଅନ୍ତର୍ଭାଵ "rational.h"

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_reduce(ପୂର୍ଣ୍ଣସଂଖ୍ୟା *dst_ଅଙ୍କ, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *dst_den,
              int64_t ଅଙ୍କ, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା sign = (ଅଙ୍କ < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(ଅଙ୍କ), FFABS(den));

    ଯଦି (gcd) {
        ଅଙ୍କ = FFABS(ଅଙ୍କ) / gcd;
        den = FFABS(den) / gcd;
    }
    ଯଦି (ଅଙ୍କ <= max && den <= max) {
        a1 = (AVRational) { ଅଙ୍କ, den };
        den = 0;
    }

    ଯେତେବେଳେ (den) {
        uint64_t x        = ଅଙ୍କ / den;
        int64_t next_den  = ଅଙ୍କ - den * x;
        int64_t a2n       = x * a1.ଅଙ୍କ + a0.ଅଙ୍କ;
        int64_t a2d       = x * a1.den + a0.den;

        ଯଦି (a2n > max || a2d > max) {
            ଯଦି (a1.ଅଙ୍କ) x =          (max - a0.ଅଙ୍କ) / a1.ଅଙ୍କ;
            ଯଦି (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            ଯଦି (den * (2 * x * a1.den + a0.den) > ଅଙ୍କ * a1.den)
                a1 = (AVRational) { x * a1.ଅଙ୍କ + a0.ଅଙ୍କ, x * a1.den + a0.den };
            ଭାଙ୍ଗ;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        ଅଙ୍କ = den;
        den = next_den;
    }
    av_assert2(av_gcd(a1.ଅଙ୍କ, a1.den) <= 1U);
    av_assert2(a1.ଅଙ୍କ <= max && a1.den <= max);

    *dst_ଅଙ୍କ = sign ? -a1.ଅଙ୍କ : a1.ଅଙ୍କ;
    *dst_den = a1.den;

    ଫେରନ୍ତୁ den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.ଅଙ୍କ, &b.den,
               b.ଅଙ୍କ * (int64_t) c.ଅଙ୍କ,
               b.den * (int64_t) c.den, INT_MAX);
    ଫେରନ୍ତୁ b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    ଫେରନ୍ତୁ av_mul_q(b, (AVRational) { c.den, c.ଅଙ୍କ });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.ଅଙ୍କ, &b.den,
               b.ଅଙ୍କ * (int64_t) c.den +
               c.ଅଙ୍କ * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    ଫେରନ୍ତୁ b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.ଅଙ୍କ, &b.den,
               b.ଅଙ୍କ * (int64_t) c.den -
               c.ଅଙ୍କ * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    ଫେରନ୍ତୁ b;
}

AVRational av_d2q(ଦ୍ୱିଗୁଣ d, ପୂର୍ଣ୍ଣସଂଖ୍ୟା max)
{
    AVRational a;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା exponent;
    int64_t den;
    ଯଦି (isnan(d))
        ଫେରନ୍ତୁ (AVRational) { 0,0 };
    ଯଦି (fabs(d) > INT_MAX + 3LL)
        ଫେରନ୍ତୁ (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.ଅଙ୍କ, &a.den, floor(d * den + 0.5), den, max);

    ଫେରନ୍ତୁ a;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.ଅଙ୍କ * (int64_t)q2.den + q2.ଅଙ୍କ * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    ଫେରନ୍ତୁ ((x_up > q.ଅଙ୍କ) - (x_down < q.ଅଙ୍କ)) * av_cmp_q(q2, q1);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_find_nearest_q_idx(AVRational q, ଅଚଳ AVRational* q_list)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, nearest_q_idx = 0;
    ପାଇଁ (i = 0; q_list[i].den; i++)
        ଯଦି (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    ଫେରନ୍ତୁ nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, ଅଙ୍କ = q.ଅଙ୍କ, den = q.den;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା shift;
    uint32_t sign = 0;

    ଯଦି (den < 0) {
        den = -den;
        ଅଙ୍କ = -ଅଙ୍କ;
    }
    ଯଦି (ଅଙ୍କ < 0) {
        ଅଙ୍କ = -ଅଙ୍କ;
        sign = 1U << 31;
    }

    ଯଦି (!ଅଙ୍କ && !den) ଫେରନ୍ତୁ 0xFFC00000;
    ଯଦି (!ଅଙ୍କ) ଫେରନ୍ତୁ 0;
    ଯଦି (!den) ଫେରନ୍ତୁ sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(ଅଙ୍କ);
    ଯଦି (shift >= 0) n = av_rescale(ଅଙ୍କ, 1LL<<shift, den);
    ଅନ୍ୟଥା            n = av_rescale(ଅଙ୍କ, 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    ଯଦି (shift >= 0) n = av_rescale(ଅଙ୍କ, 1LL<<shift, den);
    ଅନ୍ୟଥା            n = av_rescale(ଅଙ୍କ, 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    ଫେରନ୍ତୁ sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    ଫେରନ୍ତୁ lcm < max_den ? av_make_q(av_gcd(a.ଅଙ୍କ, b.ଅଙ୍କ), lcm) : def;
}
