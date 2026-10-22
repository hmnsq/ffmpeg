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

#अन्तर्भाव "avassert.h"
#अन्तर्भाव <limits.h>

#अन्तर्भाव "common.h"
#अन्तर्भाव "mathematics.h"
#अन्तर्भाव "rational.h"

पूर्णाङ्क av_reduce(पूर्णाङ्क *dst_अङ्कः, पूर्णाङ्क *dst_den,
              int64_t अङ्कः, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    पूर्णाङ्क sign = (अङ्कः < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(अङ्कः), FFABS(den));

    जइ (gcd) {
        अङ्कः = FFABS(अङ्कः) / gcd;
        den = FFABS(den) / gcd;
    }
    जइ (अङ्कः <= max && den <= max) {
        a1 = (AVRational) { अङ्कः, den };
        den = 0;
    }

    जाव (den) {
        uint64_t x        = अङ्कः / den;
        int64_t next_den  = अङ्कः - den * x;
        int64_t a2n       = x * a1.अङ्कः + a0.अङ्कः;
        int64_t a2d       = x * a1.den + a0.den;

        जइ (a2n > max || a2d > max) {
            जइ (a1.अङ्कः) x =          (max - a0.अङ्कः) / a1.अङ्कः;
            जइ (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            जइ (den * (2 * x * a1.den + a0.den) > अङ्कः * a1.den)
                a1 = (AVRational) { x * a1.अङ्कः + a0.अङ्कः, x * a1.den + a0.den };
            भङ्ग;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        अङ्कः = den;
        den = next_den;
    }
    av_assert2(av_gcd(a1.अङ्कः, a1.den) <= 1U);
    av_assert2(a1.अङ्कः <= max && a1.den <= max);

    *dst_अङ्कः = sign ? -a1.अङ्कः : a1.अङ्कः;
    *dst_den = a1.den;

    प्रत्यागम den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.अङ्कः, &b.den,
               b.अङ्कः * (int64_t) c.अङ्कः,
               b.den * (int64_t) c.den, INT_MAX);
    प्रत्यागम b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    प्रत्यागम av_mul_q(b, (AVRational) { c.den, c.अङ्कः });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.अङ्कः, &b.den,
               b.अङ्कः * (int64_t) c.den +
               c.अङ्कः * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    प्रत्यागम b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.अङ्कः, &b.den,
               b.अङ्कः * (int64_t) c.den -
               c.अङ्कः * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    प्रत्यागम b;
}

AVRational av_d2q(द्विगुण d, पूर्णाङ्क max)
{
    AVRational a;
    पूर्णाङ्क exponent;
    int64_t den;
    जइ (isnan(d))
        प्रत्यागम (AVRational) { 0,0 };
    जइ (fabs(d) > INT_MAX + 3LL)
        प्रत्यागम (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.अङ्कः, &a.den, floor(d * den + 0.5), den, max);

    प्रत्यागम a;
}

पूर्णाङ्क av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.अङ्कः * (int64_t)q2.den + q2.अङ्कः * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    प्रत्यागम ((x_up > q.अङ्कः) - (x_down < q.अङ्कः)) * av_cmp_q(q2, q1);
}

पूर्णाङ्क av_find_nearest_q_idx(AVRational q, ध्रुव AVRational* q_list)
{
    पूर्णाङ्क i, nearest_q_idx = 0;
    प्रति (i = 0; q_list[i].den; i++)
        जइ (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    प्रत्यागम nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, अङ्कः = q.अङ्कः, den = q.den;
    पूर्णाङ्क shift;
    uint32_t sign = 0;

    जइ (den < 0) {
        den = -den;
        अङ्कः = -अङ्कः;
    }
    जइ (अङ्कः < 0) {
        अङ्कः = -अङ्कः;
        sign = 1U << 31;
    }

    जइ (!अङ्कः && !den) प्रत्यागम 0xFFC00000;
    जइ (!अङ्कः) प्रत्यागम 0;
    जइ (!den) प्रत्यागम sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(अङ्कः);
    जइ (shift >= 0) n = av_rescale(अङ्कः, 1LL<<shift, den);
    अण्णहा            n = av_rescale(अङ्कः, 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    जइ (shift >= 0) n = av_rescale(अङ्कः, 1LL<<shift, den);
    अण्णहा            n = av_rescale(अङ्कः, 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    प्रत्यागम sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, पूर्णाङ्क max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    प्रत्यागम lcm < max_den ? av_make_q(av_gcd(a.अङ्कः, b.अङ्कः), lcm) : def;
}
