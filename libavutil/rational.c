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

#include "avassert.h"
#include <limits.h>

#include "common.h"
#include "mathematics.h"
#include "rational.h"

цяло av_reduce(цяло *dst_num, цяло *dst_den,
              int64_t num, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    цяло sign = (num < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(num), FFABS(den));

    ако (gcd) {
        num = FFABS(num) / gcd;
        den = FFABS(den) / gcd;
    }
    ако (num <= max && den <= max) {
        a1 = (AVRational) { num, den };
        den = 0;
    }

    докато (den) {
        uint64_t x        = num / den;
        int64_t next_den  = num - den * x;
        int64_t a2n       = x * a1.num + a0.num;
        int64_t a2d       = x * a1.den + a0.den;

        ако (a2n > max || a2d > max) {
            ако (a1.num) x =          (max - a0.num) / a1.num;
            ако (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            ако (den * (2 * x * a1.den + a0.den) > num * a1.den)
                a1 = (AVRational) { x * a1.num + a0.num, x * a1.den + a0.den };
            break;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        num = den;
        den = next_den;
    }
    av_assert2(av_gcd(a1.num, a1.den) <= 1U);
    av_assert2(a1.num <= max && a1.den <= max);

    *dst_num = sign ? -a1.num : a1.num;
    *dst_den = a1.den;

    върни den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.num, &b.den,
               b.num * (int64_t) c.num,
               b.den * (int64_t) c.den, INT_MAX);
    върни b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    върни av_mul_q(b, (AVRational) { c.den, c.num });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.num, &b.den,
               b.num * (int64_t) c.den +
               c.num * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    върни b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.num, &b.den,
               b.num * (int64_t) c.den -
               c.num * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    върни b;
}

AVRational av_d2q(double d, цяло max)
{
    AVRational a;
    цяло exponent;
    int64_t den;
    ако (isnan(d))
        върни (AVRational) { 0,0 };
    ако (fabs(d) > INT_MAX + 3LL)
        върни (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.num, &a.den, floor(d * den + 0.5), den, max);

    върни a;
}

цяло av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.num * (int64_t)q2.den + q2.num * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    върни ((x_up > q.num) - (x_down < q.num)) * av_cmp_q(q2, q1);
}

цяло av_find_nearest_q_idx(AVRational q, const AVRational* q_list)
{
    цяло i, nearest_q_idx = 0;
    за (i = 0; q_list[i].den; i++)
        ако (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    върни nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, num = q.num, den = q.den;
    цяло shift;
    uint32_t sign = 0;

    ако (den < 0) {
        den = -den;
        num = -num;
    }
    ако (num < 0) {
        num = -num;
        sign = 1U << 31;
    }

    ако (!num && !den) върни 0xFFC00000;
    ако (!num) върни 0;
    ако (!den) върни sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(num);
    ако (shift >= 0) n = av_rescale(num, 1LL<<shift, den);
    иначе            n = av_rescale(num, 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    ако (shift >= 0) n = av_rescale(num, 1LL<<shift, den);
    иначе            n = av_rescale(num, 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    върни sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, цяло max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    върни lcm < max_den ? av_make_q(av_gcd(a.num, b.num), lcm) : def;
}
