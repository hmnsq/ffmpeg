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

#شامل "avassert.h"
#شامل <limits.h>

#شامل "common.h"
#شامل "mathematics.h"
#شامل "rational.h"

صحیح av_reduce(صحیح *dst_رقم, صحیح *dst_den,
              int64_t رقم, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    صحیح sign = (رقم < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(رقم), FFABS(den));

    اگر (gcd) {
        رقم = FFABS(رقم) / gcd;
        den = FFABS(den) / gcd;
    }
    اگر (رقم <= max && den <= max) {
        a1 = (AVRational) { رقم, den };
        den = 0;
    }

    وقتی (den) {
        uint64_t x        = رقم / den;
        int64_t next_den  = رقم - den * x;
        int64_t a2n       = x * a1.رقم + a0.رقم;
        int64_t a2d       = x * a1.den + a0.den;

        اگر (a2n > max || a2d > max) {
            اگر (a1.رقم) x =          (max - a0.رقم) / a1.رقم;
            اگر (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            اگر (den * (2 * x * a1.den + a0.den) > رقم * a1.den)
                a1 = (AVRational) { x * a1.رقم + a0.رقم, x * a1.den + a0.den };
            بشکن;
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

    بازگشت den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.رقم, &b.den,
               b.رقم * (int64_t) c.رقم,
               b.den * (int64_t) c.den, INT_MAX);
    بازگشت b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    بازگشت av_mul_q(b, (AVRational) { c.den, c.رقم });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.رقم, &b.den,
               b.رقم * (int64_t) c.den +
               c.رقم * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    بازگشت b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.رقم, &b.den,
               b.رقم * (int64_t) c.den -
               c.رقم * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    بازگشت b;
}

AVRational av_d2q(دوگانه d, صحیح max)
{
    AVRational a;
    صحیح exponent;
    int64_t den;
    اگر (isnan(d))
        بازگشت (AVRational) { 0,0 };
    اگر (fabs(d) > INT_MAX + 3LL)
        بازگشت (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.رقم, &a.den, floor(d * den + 0.5), den, max);

    بازگشت a;
}

صحیح av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.رقم * (int64_t)q2.den + q2.رقم * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    بازگشت ((x_up > q.رقم) - (x_down < q.رقم)) * av_cmp_q(q2, q1);
}

صحیح av_find_nearest_q_idx(AVRational q, ثابت AVRational* q_list)
{
    صحیح i, nearest_q_idx = 0;
    برای (i = 0; q_list[i].den; i++)
        اگر (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    بازگشت nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, رقم = q.رقم, den = q.den;
    صحیح shift;
    uint32_t sign = 0;

    اگر (den < 0) {
        den = -den;
        رقم = -رقم;
    }
    اگر (رقم < 0) {
        رقم = -رقم;
        sign = 1U << 31;
    }

    اگر (!رقم && !den) بازگشت 0xFFC00000;
    اگر (!رقم) بازگشت 0;
    اگر (!den) بازگشت sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(رقم);
    اگر (shift >= 0) n = av_rescale(رقم, 1LL<<shift, den);
    وگرنه            n = av_rescale(رقم, 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    اگر (shift >= 0) n = av_rescale(رقم, 1LL<<shift, den);
    وگرنه            n = av_rescale(رقم, 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    بازگشت sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, صحیح max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    بازگشت lcm < max_den ? av_make_q(av_gcd(a.رقم, b.رقم), lcm) : def;
}
