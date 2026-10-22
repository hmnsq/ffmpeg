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

पूर्णाङ्क av_reduce(पूर्णाङ्क *dst_अंक, पूर्णाङ्क *dst_den,
              int64_t अंक, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    पूर्णाङ्क sign = (अंक < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(अंक), FFABS(den));

    यदि (gcd) {
        अंक = FFABS(अंक) / gcd;
        den = FFABS(den) / gcd;
    }
    यदि (अंक <= max && den <= max) {
        a1 = (AVRational) { अंक, den };
        den = 0;
    }

    यावत् (den) {
        uint64_t x        = अंक / den;
        int64_t next_den  = अंक - den * x;
        int64_t a2n       = x * a1.अंक + a0.अंक;
        int64_t a2d       = x * a1.den + a0.den;

        यदि (a2n > max || a2d > max) {
            यदि (a1.अंक) x =          (max - a0.अंक) / a1.अंक;
            यदि (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            यदि (den * (2 * x * a1.den + a0.den) > अंक * a1.den)
                a1 = (AVRational) { x * a1.अंक + a0.अंक, x * a1.den + a0.den };
            भङ्ग;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        अंक = den;
        den = next_den;
    }
    av_assert2(av_gcd(a1.अंक, a1.den) <= 1U);
    av_assert2(a1.अंक <= max && a1.den <= max);

    *dst_अंक = sign ? -a1.अंक : a1.अंक;
    *dst_den = a1.den;

    प्रत्यागम den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.अंक, &b.den,
               b.अंक * (int64_t) c.अंक,
               b.den * (int64_t) c.den, पूर्णांक_उच्च);
    प्रत्यागम b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    प्रत्यागम av_mul_q(b, (AVRational) { c.den, c.अंक });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.अंक, &b.den,
               b.अंक * (int64_t) c.den +
               c.अंक * (int64_t) b.den,
               b.den * (int64_t) c.den, पूर्णांक_उच्च);
    प्रत्यागम b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.अंक, &b.den,
               b.अंक * (int64_t) c.den -
               c.अंक * (int64_t) b.den,
               b.den * (int64_t) c.den, पूर्णांक_उच्च);
    प्रत्यागम b;
}

AVRational av_d2q(द्विगुण d, पूर्णाङ्क max)
{
    AVRational a;
    पूर्णाङ्क exponent;
    int64_t den;
    यदि (isnan(d))
        प्रत्यागम (AVRational) { 0,0 };
    यदि (भ_असल(d) > पूर्णांक_उच्च + 3LL)
        प्रत्यागम (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.अंक, &a.den, न्यूनमान(d * den + 0.5), den, max);

    प्रत्यागम a;
}

पूर्णाङ्क av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.अंक * (int64_t)q2.den + q2.अंक * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    प्रत्यागम ((x_up > q.अंक) - (x_down < q.अंक)) * av_cmp_q(q2, q1);
}

पूर्णाङ्क av_find_nearest_q_idx(AVRational q, ध्रुव AVRational* q_list)
{
    पूर्णाङ्क i, nearest_q_idx = 0;
    प्रति (i = 0; q_list[i].den; i++)
        यदि (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    प्रत्यागम nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, अंक = q.अंक, den = q.den;
    पूर्णाङ्क shift;
    uint32_t sign = 0;

    यदि (den < 0) {
        den = -den;
        अंक = -अंक;
    }
    यदि (अंक < 0) {
        अंक = -अंक;
        sign = 1U << 31;
    }

    यदि (!अंक && !den) प्रत्यागम 0xFFC00000;
    यदि (!अंक) प्रत्यागम 0;
    यदि (!den) प्रत्यागम sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(अंक);
    यदि (shift >= 0) n = av_rescale(अंक, 1LL<<shift, den);
    अन्यथा            n = av_rescale(अंक, 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    यदि (shift >= 0) n = av_rescale(अंक, 1LL<<shift, den);
    अन्यथा            n = av_rescale(अंक, 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    प्रत्यागम sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, पूर्णाङ्क max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    प्रत्यागम lcm < max_den ? av_make_q(av_gcd(a.अंक, b.अंक), lcm) : def;
}
