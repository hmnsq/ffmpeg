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

#అన్తర్భావ "avassert.h"
#అన్తర్భావ <limits.h>

#అన్తర్భావ "common.h"
#అన్తర్భావ "mathematics.h"
#అన్తర్భావ "rational.h"

పూర్ణాంకం av_reduce(పూర్ణాంకం *dst_అంకె, పూర్ణాంకం *dst_den,
              int64_t అంకె, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    పూర్ణాంకం sign = (అంకె < 0) ^ (den < 0);
    int64_t గరిష్ఠ_సామాన్య_భాజకం = av_గరిష్ఠ_సామాన్య_భాజకం(FFABS(అంకె), FFABS(den));

    ఒకవేళ (గరిష్ఠ_సామాన్య_భాజకం) {
        అంకె = FFABS(అంకె) / గరిష్ఠ_సామాన్య_భాజకం;
        den = FFABS(den) / గరిష్ఠ_సామాన్య_భాజకం;
    }
    ఒకవేళ (అంకె <= max && den <= max) {
        a1 = (AVRational) { అంకె, den };
        den = 0;
    }

    అయితే (den) {
        uint64_t x        = అంకె / den;
        int64_t తదుపరి_den  = అంకె - den * x;
        int64_t a2n       = x * a1.అంకె + a0.అంకె;
        int64_t a2d       = x * a1.den + a0.den;

        ఒకవేళ (a2n > max || a2d > max) {
            ఒకవేళ (a1.అంకె) x =          (max - a0.అంకె) / a1.అంకె;
            ఒకవేళ (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            ఒకవేళ (den * (2 * x * a1.den + a0.den) > అంకె * a1.den)
                a1 = (AVRational) { x * a1.అంకె + a0.అంకె, x * a1.den + a0.den };
            ఆపు;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        అంకె = den;
        den = తదుపరి_den;
    }
    av_assert2(av_గరిష్ఠ_సామాన్య_భాజకం(a1.అంకె, a1.den) <= 1U);
    av_assert2(a1.అంకె <= max && a1.den <= max);

    *dst_అంకె = sign ? -a1.అంకె : a1.అంకె;
    *dst_den = a1.den;

    తిరిగి den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.అంకె, &b.den,
               b.అంకె * (int64_t) c.అంకె,
               b.den * (int64_t) c.den, గరిష్ఠ_పూర్ణాంకం);
    తిరిగి b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    తిరిగి av_mul_q(b, (AVRational) { c.den, c.అంకె });
}

AVRational av_కూడు_q(AVRational b, AVRational c) {
    av_reduce(&b.అంకె, &b.den,
               b.అంకె * (int64_t) c.den +
               c.అంకె * (int64_t) b.den,
               b.den * (int64_t) c.den, గరిష్ఠ_పూర్ణాంకం);
    తిరిగి b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.అంకె, &b.den,
               b.అంకె * (int64_t) c.den -
               c.అంకె * (int64_t) b.den,
               b.den * (int64_t) c.den, గరిష్ఠ_పూర్ణాంకం);
    తిరిగి b;
}

AVRational av_d2q(ద్విగుణ d, పూర్ణాంకం max)
{
    AVRational a;
    పూర్ణాంకం exponent;
    int64_t den;
    ఒకవేళ (isnan(d))
        తిరిగి (AVRational) { 0,0 };
    ఒకవేళ (fabs(d) > గరిష్ఠ_పూర్ణాంకం + 3LL)
        తిరిగి (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.అంకె, &a.den, floor(d * den + 0.5), den, max);

    తిరిగి a;
}

పూర్ణాంకం av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.అంకె * (int64_t)q2.den + q2.అంకె * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_పైకి = av_rescale_rnd(a, q.den, b, AV_విడత_పైకి);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_కిందికి = av_rescale_rnd(a, q.den, b, AV_విడత_కిందికి);

    తిరిగి ((x_పైకి > q.అంకె) - (x_కిందికి < q.అంకె)) * av_cmp_q(q2, q1);
}

పూర్ణాంకం av_కనుగొను_సమీప_q_idx(AVRational q, స్థిరరాశి AVRational* q_list)
{
    పూర్ణాంకం i, సమీప_q_idx = 0;
    కొరకు (i = 0; q_list[i].den; i++)
        ఒకవేళ (av_nearer_q(q, q_list[i], q_list[సమీప_q_idx]) > 0)
            సమీప_q_idx = i;

    తిరిగి సమీప_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, అంకె = q.అంకె, den = q.den;
    పూర్ణాంకం జరుపు;
    uint32_t sign = 0;

    ఒకవేళ (den < 0) {
        den = -den;
        అంకె = -అంకె;
    }
    ఒకవేళ (అంకె < 0) {
        అంకె = -అంకె;
        sign = 1U << 31;
    }

    ఒకవేళ (!అంకె && !den) తిరిగి 0xFFC00000;
    ఒకవేళ (!అంకె) తిరిగి 0;
    ఒకవేళ (!den) తిరిగి sign | 0x7F800000;

    జరుపు = 23 + av_log2(den) - av_log2(అంకె);
    ఒకవేళ (జరుపు >= 0) n = av_rescale(అంకె, 1LL<<జరుపు, den);
    లేకపోతే            n = av_rescale(అంకె, 1, den << -జరుపు);

    జరుపు -= n >= (1<<24);
    జరుపు += n <  (1<<23);

    ఒకవేళ (జరుపు >= 0) n = av_rescale(అంకె, 1LL<<జరుపు, den);
    లేకపోతే            n = av_rescale(అంకె, 1, den << -జరుపు);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    తిరిగి sign | (150-జరుపు)<<23 | (n - (1<<23));
}

AVRational av_గరిష్ఠ_సామాన్య_భాజకం_q(AVRational a, AVRational b, పూర్ణాంకం max_den, AVRational def)
{
    int64_t గరిష్ఠ_సామాన్య_భాజకం, lcm;

    గరిష్ఠ_సామాన్య_భాజకం = av_గరిష్ఠ_సామాన్య_భాజకం(a.den, b.den);
    lcm = (a.den / గరిష్ఠ_సామాన్య_భాజకం) * b.den;
    తిరిగి lcm < max_den ? av_make_q(av_గరిష్ఠ_సామాన్య_భాజకం(a.అంకె, b.అంకె), lcm) : def;
}
