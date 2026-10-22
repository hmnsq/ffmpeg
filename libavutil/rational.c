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

#ضمن "avassert.h"
#ضمن <limits.h>

#ضمن "common.h"
#ضمن "mathematics.h"
#ضمن "rational.h"

صحيح av_reduce(صحيح *dst_رقم, صحيح *dst_den,
              int64_t رقم, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    صحيح sign = (رقم < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(رقم), FFABS(den));

    إذا (gcd) {
        رقم = FFABS(رقم) / gcd;
        den = FFABS(den) / gcd;
    }
    إذا (رقم <= max && den <= max) {
        a1 = (AVRational) { رقم, den };
        den = 0;
    }

    بينما (den) {
        uint64_t x        = رقم / den;
        int64_t next_den  = رقم - den * x;
        int64_t a2n       = x * a1.رقم + a0.رقم;
        int64_t a2d       = x * a1.den + a0.den;

        إذا (a2n > max || a2d > max) {
            إذا (a1.رقم) x =          (max - a0.رقم) / a1.رقم;
            إذا (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            إذا (den * (2 * x * a1.den + a0.den) > رقم * a1.den)
                a1 = (AVRational) { x * a1.رقم + a0.رقم, x * a1.den + a0.den };
            اكسر;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        رقم = den;
        den = next_den;
    }
    av_assert2(av_gcd(a1.رقم, a1.den) <= 1U);
    av_assert2(a1.رقم <= max && a1.den <= max);

    *dst_رقم = sign ? -a1.رقم : a1.رقم;
    *dst_den = a1.den;

    إرجاع den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.رقم, &b.den,
               b.رقم * (int64_t) c.رقم,
               b.den * (int64_t) c.den, INT_MAX);
    إرجاع b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    إرجاع av_mul_q(b, (AVRational) { c.den, c.رقم });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.رقم, &b.den,
               b.رقم * (int64_t) c.den +
               c.رقم * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    إرجاع b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.رقم, &b.den,
               b.رقم * (int64_t) c.den -
               c.رقم * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    إرجاع b;
}

AVRational av_d2q(مزدوج d, صحيح max)
{
    AVRational a;
    صحيح exponent;
    int64_t den;
    إذا (isnan(d))
        إرجاع (AVRational) { 0,0 };
    إذا (fabs(d) > INT_MAX + 3LL)
        إرجاع (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.رقم, &a.den, floor(d * den + 0.5), den, max);

    إرجاع a;
}

صحيح av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.رقم * (int64_t)q2.den + q2.رقم * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    إرجاع ((x_up > q.رقم) - (x_down < q.رقم)) * av_cmp_q(q2, q1);
}

صحيح av_find_nearest_q_idx(AVRational q, ثابت AVRational* q_list)
{
    صحيح i, nearest_q_idx = 0;
    لكل (i = 0; q_list[i].den; i++)
        إذا (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    إرجاع nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, رقم = q.رقم, den = q.den;
    صحيح shift;
    uint32_t sign = 0;

    إذا (den < 0) {
        den = -den;
        رقم = -رقم;
    }
    إذا (رقم < 0) {
        رقم = -رقم;
        sign = 1U << 31;
    }

    إذا (!رقم && !den) إرجاع 0xFFC00000;
    إذا (!رقم) إرجاع 0;
    إذا (!den) إرجاع sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(رقم);
    إذا (shift >= 0) n = av_rescale(رقم, 1LL<<shift, den);
    وإلا            n = av_rescale(رقم, 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    إذا (shift >= 0) n = av_rescale(رقم, 1LL<<shift, den);
    وإلا            n = av_rescale(رقم, 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    إرجاع sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, صحيح max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    إرجاع lcm < max_den ? av_make_q(av_gcd(a.رقم, b.رقم), lcm) : def;
}
