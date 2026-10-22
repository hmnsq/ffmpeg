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

puur_naa_nka av_reduce(puur_naa_nka *dst_num, puur_naa_nka *dst_den,
              int64_t num, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    puur_naa_nka sign = (num < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(num), FFABS(den));

    ᨀᨘ (gcd) {
        num = FFABS(num) / gcd;
        den = FFABS(den) / gcd;
    }
    ᨀᨘ (num <= max && den <= max) {
        a1 = (AVRational) { num, den };
        den = 0;
    }

    ᨀᨛ (den) {
        uint64_t x        = num / den;
        int64_t next_den  = num - den * x;
        int64_t a2n       = x * a1.num + a0.num;
        int64_t a2d       = x * a1.den + a0.den;

        ᨀᨘ (a2n > max || a2d > max) {
            ᨀᨘ (a1.num) x =          (max - a0.num) / a1.num;
            ᨀᨘ (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            ᨀᨘ (den * (2 * x * a1.den + a0.den) > num * a1.den)
                a1 = (AVRational) { x * a1.num + a0.num, x * a1.den + a0.den };
            bha_nga;
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

    ᨀᨘᨒ den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.num, &b.den,
               b.num * (int64_t) c.num,
               b.den * (int64_t) c.den, INT_MAX);
    ᨀᨘᨒ b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    ᨀᨘᨒ av_mul_q(b, (AVRational) { c.den, c.num });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.num, &b.den,
               b.num * (int64_t) c.den +
               c.num * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    ᨀᨘᨒ b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.num, &b.den,
               b.num * (int64_t) c.den -
               c.num * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    ᨀᨘᨒ b;
}

AVRational av_d2q(dviguu_na d, puur_naa_nka max)
{
    AVRational a;
    puur_naa_nka exponent;
    int64_t den;
    ᨀᨘ (isnan(d))
        ᨀᨘᨒ (AVRational) { 0,0 };
    ᨀᨘ (fabs(d) > INT_MAX + 3LL)
        ᨀᨘᨒ (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.num, &a.den, floor(d * den + 0.5), den, max);

    ᨀᨘᨒ a;
}

puur_naa_nka av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.num * (int64_t)q2.den + q2.num * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    ᨀᨘᨒ ((x_up > q.num) - (x_down < q.num)) * av_cmp_q(q2, q1);
}

puur_naa_nka av_find_nearest_q_idx(AVRational q, const AVRational* q_list)
{
    puur_naa_nka i, nearest_q_idx = 0;
    for (i = 0; q_list[i].den; i++)
        ᨀᨘ (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    ᨀᨘᨒ nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, num = q.num, den = q.den;
    puur_naa_nka shift;
    uint32_t sign = 0;

    ᨀᨘ (den < 0) {
        den = -den;
        num = -num;
    }
    ᨀᨘ (num < 0) {
        num = -num;
        sign = 1U << 31;
    }

    ᨀᨘ (!num && !den) ᨀᨘᨒ 0xFFC00000;
    ᨀᨘ (!num) ᨀᨘᨒ 0;
    ᨀᨘ (!den) ᨀᨘᨒ sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(num);
    ᨀᨘ (shift >= 0) n = av_rescale(num, 1LL<<shift, den);
    ᨀᨘᨁ            n = av_rescale(num, 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    ᨀᨘ (shift >= 0) n = av_rescale(num, 1LL<<shift, den);
    ᨀᨘᨁ            n = av_rescale(num, 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    ᨀᨘᨒ sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, puur_naa_nka max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    ᨀᨘᨒ lcm < max_den ? av_make_q(av_gcd(a.num, b.num), lcm) : def;
}
