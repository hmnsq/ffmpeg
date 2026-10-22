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

पूर्णाङ्क av_reduce(पूर्णाङ्क *dst_अङ्क, पूर्णाङ्क *dst_den,
              int64_t अङ्क, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    पूर्णाङ्क sign = (अङ्क < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(अङ्क), FFABS(den));

    यदि (gcd) {
        अङ्क = FFABS(अङ्क) / gcd;
        den = FFABS(den) / gcd;
    }
    यदि (अङ्क <= max && den <= max) {
        a1 = (AVRational) { अङ्क, den };
        den = 0;
    }

    जबसम्म (den) {
        uint64_t x        = अङ्क / den;
        int64_t next_den  = अङ्क - den * x;
        int64_t a2n       = x * a1.अङ्क + a0.अङ्क;
        int64_t a2d       = x * a1.den + a0.den;

        यदि (a2n > max || a2d > max) {
            यदि (a1.अङ्क) x =          (max - a0.अङ्क) / a1.अङ्क;
            यदि (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            यदि (den * (2 * x * a1.den + a0.den) > अङ्क * a1.den)
                a1 = (AVRational) { x * a1.अङ्क + a0.अङ्क, x * a1.den + a0.den };
            रोक;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        अङ्क = den;
        den = next_den;
    }
    av_assert2(av_gcd(a1.अङ्क, a1.den) <= 1U);
    av_assert2(a1.अङ्क <= max && a1.den <= max);

    *dst_अङ्क = sign ? -a1.अङ्क : a1.अङ्क;
    *dst_den = a1.den;

    फर्काऊ den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.अङ्क, &b.den,
               b.अङ्क * (int64_t) c.अङ्क,
               b.den * (int64_t) c.den, पूर्णांक_उच्च);
    फर्काऊ b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    फर्काऊ av_mul_q(b, (AVRational) { c.den, c.अङ्क });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.अङ्क, &b.den,
               b.अङ्क * (int64_t) c.den +
               c.अङ्क * (int64_t) b.den,
               b.den * (int64_t) c.den, पूर्णांक_उच्च);
    फर्काऊ b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.अङ्क, &b.den,
               b.अङ्क * (int64_t) c.den -
               c.अङ्क * (int64_t) b.den,
               b.den * (int64_t) c.den, पूर्णांक_उच्च);
    फर्काऊ b;
}

AVRational av_d2q(द्विगुण d, पूर्णाङ्क max)
{
    AVRational a;
    पूर्णाङ्क exponent;
    int64_t den;
    यदि (isnan(d))
        फर्काऊ (AVRational) { 0,0 };
    यदि (भ_असल(d) > पूर्णांक_उच्च + 3LL)
        फर्काऊ (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.अङ्क, &a.den, न्यूनमान(d * den + 0.5), den, max);

    फर्काऊ a;
}

पूर्णाङ्क av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.अङ्क * (int64_t)q2.den + q2.अङ्क * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    फर्काऊ ((x_up > q.अङ्क) - (x_down < q.अङ्क)) * av_cmp_q(q2, q1);
}

पूर्णाङ्क av_find_nearest_q_idx(AVRational q, अचर AVRational* q_list)
{
    पूर्णाङ्क i, nearest_q_idx = 0;
    लागि (i = 0; q_list[i].den; i++)
        यदि (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    फर्काऊ nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, अङ्क = q.अङ्क, den = q.den;
    पूर्णाङ्क shift;
    uint32_t sign = 0;

    यदि (den < 0) {
        den = -den;
        अङ्क = -अङ्क;
    }
    यदि (अङ्क < 0) {
        अङ्क = -अङ्क;
        sign = 1U << 31;
    }

    यदि (!अङ्क && !den) फर्काऊ 0xFFC00000;
    यदि (!अङ्क) फर्काऊ 0;
    यदि (!den) फर्काऊ sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(अङ्क);
    यदि (shift >= 0) n = av_rescale(अङ्क, 1LL<<shift, den);
    अन्यथा            n = av_rescale(अङ्क, 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    यदि (shift >= 0) n = av_rescale(अङ्क, 1LL<<shift, den);
    अन्यथा            n = av_rescale(अङ्क, 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    फर्काऊ sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, पूर्णाङ्क max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    फर्काऊ lcm < max_den ? av_make_q(av_gcd(a.अङ्क, b.अङ्क), lcm) : def;
}
