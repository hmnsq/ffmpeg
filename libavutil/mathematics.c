/*
 * Copyright (c) 2005-2012 Michael Niedermayer <michaelni@gmx.at>
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
 * miscellaneous math routines and tables
 */

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <limits.h>

#అన్తర్భావ "avutil.h"
#అన్తర్భావ "mathematics.h"
#అన్తర్భావ "libavutil/intmath.h"
#అన్తర్భావ "libavutil/common.h"
#అన్తర్భావ "avassert.h"

/* Stein's binary GCD algorithm:
 * https://en.wikipedia.org/wiki/Binary_GCD_algorithm */
int64_t av_గరిష్ఠ_సామాన్య_భాజకం(int64_t a, int64_t b) {
    పూర్ణాంకం za, zb, k;
    int64_t u, v;
    ఒకవేళ (a == 0)
        తిరిగి b;
    ఒకవేళ (b == 0)
        తిరిగి a;
    za = ff_ctzll(a);
    zb = ff_ctzll(b);
    k  = FFMIN(za, zb);
    u = llabs(a >> za);
    v = llabs(b >> zb);
    అయితే (u != v) {
        ఒకవేళ (u > v)
            FFSWAP(int64_t, v, u);
        v -= u;
        v >>= ff_ctzll(v);
    }
    తిరిగి (uint64_t)u << k;
}

int64_t av_rescale_rnd(int64_t a, int64_t b, int64_t c, గణన AVRounding rnd)
{
    int64_t r = 0;
    av_assert2(c > 0);
    av_assert2(b >=0);
    av_assert2((గుర్తులేని)(rnd&~AV_విడత_PASS_MINMAX)<=5 && (rnd&~AV_విడత_PASS_MINMAX)!=4);

    ఒకవేళ (c <= 0 || b < 0 || !((గుర్తులేని)(rnd&~AV_విడత_PASS_MINMAX)<=5 && (rnd&~AV_విడత_PASS_MINMAX)!=4))
        తిరిగి INT64_MIN;

    ఒకవేళ (rnd & AV_విడత_PASS_MINMAX) {
        ఒకవేళ (a == INT64_MIN || a == INT64_MAX)
            తిరిగి a;
        rnd -= AV_విడత_PASS_MINMAX;
    }

    ఒకవేళ (a < 0)
        తిరిగి -(uint64_t)av_rescale_rnd(-FFMAX(a, -INT64_MAX), b, c, rnd ^ ((rnd >> 1) & 1));

    ఒకవేళ (rnd == AV_విడత_NEAR_INF)
        r = c / 2;
    లేకపోతే ఒకవేళ (rnd & 1)
        r = c - 1;

    ఒకవేళ (b <= గరిష్ఠ_పూర్ణాంకం && c <= గరిష్ఠ_పూర్ణాంకం) {
        ఒకవేళ (a <= గరిష్ఠ_పూర్ణాంకం)
            తిరిగి (a * b + r) / c;
        లేకపోతే {
            int64_t ad = a / c;
            int64_t a2 = (a % c * b + r) / c;
            ఒకవేళ (ad >= INT32_MAX && b && ad > (INT64_MAX - a2) / b)
                తిరిగి INT64_MIN;
            తిరిగి ad * b + a2;
        }
    } లేకపోతే {
#ఒకవేళ 1
        uint64_t a0  = a & 0xFFFFFFFF;
        uint64_t a1  = a >> 32;
        uint64_t b0  = b & 0xFFFFFFFF;
        uint64_t b1  = b >> 32;
        uint64_t t1  = a0 * b1 + a1 * b0;
        uint64_t t1a = t1 << 32;
        పూర్ణాంకం i;

        a0  = a0 * b0 + t1a;
        a1  = a1 * b1 + (t1 >> 32) + (a0 < t1a);
        a0 += r;
        a1 += a0 < r;

        కొరకు (i = 63; i >= 0; i--) {
            a1 += a1 + ((a0 >> i) & 1);
            t1 += t1;
            ఒకవేళ (c <= a1) {
                a1 -= c;
                t1++;
            }
        }
        ఒకవేళ (t1 > INT64_MAX)
            తిరిగి INT64_MIN;
        తిరిగి t1;
#లేకపోతే
        /* reference code doing (a*b + r) / c, requires libavutil/integer.h */
        AVInteger ai;
        ai = av_mul_i(av_int2i(a), av_int2i(b));
        ai = av_కూడు_i(ai, av_int2i(r));

        తిరిగి av_i2int(av_div_i(ai, av_int2i(c)));
#అయితే_ముగింపు
    }
}

int64_t av_rescale(int64_t a, int64_t b, int64_t c)
{
    తిరిగి av_rescale_rnd(a, b, c, AV_విడత_NEAR_INF);
}

int64_t av_rescale_q_rnd(int64_t a, AVRational bq, AVRational cq,
                         గణన AVRounding rnd)
{
    int64_t b = bq.అంకె * (int64_t)cq.den;
    int64_t c = cq.అంకె * (int64_t)bq.den;
    తిరిగి av_rescale_rnd(a, b, c, rnd);
}

int64_t av_rescale_q(int64_t a, AVRational bq, AVRational cq)
{
    తిరిగి av_rescale_q_rnd(a, bq, cq, AV_విడత_NEAR_INF);
}

పూర్ణాంకం av_compare_ts(int64_t ts_a, AVRational tb_a, int64_t ts_b, AVRational tb_b)
{
    int64_t a = tb_a.అంకె * (int64_t)tb_b.den;
    int64_t b = tb_b.అంకె * (int64_t)tb_a.den;
    ఒకవేళ ((FFABS64U(ts_a)|a|FFABS64U(ts_b)|b) <= గరిష్ఠ_పూర్ణాంకం)
        తిరిగి (ts_a*a > ts_b*b) - (ts_a*a < ts_b*b);
    ఒకవేళ (av_rescale_rnd(ts_a, a, b, AV_విడత_కిందికి) < ts_b)
        తిరిగి -1;
    ఒకవేళ (av_rescale_rnd(ts_b, b, a, AV_విడత_కిందికి) < ts_a)
        తిరిగి 1;
    తిరిగి 0;
}

int64_t av_compare_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    int64_t c = (a - b) & (mod - 1);
    ఒకవేళ (c > (mod >> 1))
        c -= mod;
    తిరిగి c;
}

int64_t av_rescale_delta(AVRational లోపల_tb, int64_t లోపల_ts,  AVRational fs_tb, పూర్ణాంకం duration, int64_t *చివరి, AVRational బహిర్గతం_tb){
    int64_t a, b, this;

    av_assert0(లోపల_ts != AV_NOPTS_విలువ);
    av_assert0(duration >= 0);

    ఒకవేళ (*చివరి == AV_NOPTS_విలువ || !duration || లోపల_tb.అంకె*(int64_t)బహిర్గతం_tb.den <= బహిర్గతం_tb.అంకె*(int64_t)లోపల_tb.den) {
simple_విడత:
        *చివరి = av_rescale_q(లోపల_ts, లోపల_tb, fs_tb) + duration;
        తిరిగి av_rescale_q(లోపల_ts, లోపల_tb, బహిర్గతం_tb);
    }

    a =  av_rescale_q_rnd(2*లోపల_ts-1, లోపల_tb, fs_tb, AV_విడత_కిందికి)   >>1;
    b = (av_rescale_q_rnd(2*లోపల_ts+1, లోపల_tb, fs_tb, AV_విడత_పైకి  )+1)>>1;
    ఒకవేళ (*చివరి < 2*a - b || *చివరి > 2*b - a)
        వెళ్ళు simple_విడత;

    this = av_clip64(*చివరి, a, b);
    *చివరి = this + duration;

    తిరిగి av_rescale_q(this, fs_tb, బహిర్గతం_tb);
}

int64_t av_కూడు_stable(AVRational ts_tb, int64_t ts, AVRational inc_tb, int64_t inc)
{
    int64_t m, d;

    ఒకవేళ (inc != 1)
        inc_tb = av_mul_q(inc_tb, (AVRational) {inc, 1});

    m = inc_tb.అంకె * (int64_t)ts_tb.den;
    d = inc_tb.den * (int64_t)ts_tb.అంకె;

    ఒకవేళ (m % d == 0 && ts <= INT64_MAX - m / d)
        తిరిగి ts + m / d;
    ఒకవేళ (m < d)
        తిరిగి ts;

    {
        int64_t old = av_rescale_q(ts, ts_tb, inc_tb);
        int64_t old_ts = av_rescale_q(old, inc_tb, ts_tb);

        ఒకవేళ (old == INT64_MAX || old == AV_NOPTS_విలువ || old_ts == AV_NOPTS_విలువ)
            తిరిగి ts;

        తిరిగి av_sat_add64(av_rescale_q(old + 1, inc_tb, ts_tb), ts - old_ts);
    }
}

స్థిర అంతఃవరుస ద్విగుణ eval_poly(స్థిరరాశి ద్విగుణ *coeff, పూర్ణాంకం కొలత, ద్విగుణ x) {
    ద్విగుణ కూడిక = coeff[కొలత-1];
    పూర్ణాంకం i;
    కొరకు (i = కొలత-2; i >= 0; --i) {
        కూడిక *= x;
        కూడిక += coeff[i];
    }
    తిరిగి కూడిక;
}

/**
 * 0th order modified bessel function of the first kind.
 * Algorithm taken from the Boost project, source:
 * https://searchcode.com/codesearch/view/14918379/
 * Use, modification and distribution are subject to the
 * Boost Software License, Version 1.0 (see notice below).
 * Boost Software License - Version 1.0 - August 17th, 2003
Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
 */

ద్విగుణ av_bessel_i0(ద్విగుణ x) {
// Modified Bessel function of the first kind of order zero
// minimax rational approximations on intervals, see
// Blair and Edwards, Chalk River Report AECL-4928, 1974
    స్థిర స్థిరరాశి ద్విగుణ p1[] = {
        -2.2335582639474375249e+15,
        -5.5050369673018427753e+14,
        -3.2940087627407749166e+13,
        -8.4925101247114157499e+11,
        -1.1912746104985237192e+10,
        -1.0313066708737980747e+08,
        -5.9545626019847898221e+05,
        -2.4125195876041896775e+03,
        -7.0935347449210549190e+00,
        -1.5453977791786851041e-02,
        -2.5172644670688975051e-05,
        -3.0517226450451067446e-08,
        -2.6843448573468483278e-11,
        -1.5982226675653184646e-14,
        -5.2487866627945699800e-18,
    };
    స్థిర స్థిరరాశి ద్విగుణ q1[] = {
        -2.2335582639474375245e+15,
         7.8858692566751002988e+12,
        -1.2207067397808979846e+10,
         1.0377081058062166144e+07,
        -4.8527560179962773045e+03,
         1.0,
    };
    స్థిర స్థిరరాశి ద్విగుణ p2[] = {
        -2.2210262233306573296e-04,
         1.3067392038106924055e-02,
        -4.4700805721174453923e-01,
         5.5674518371240761397e+00,
        -2.3517945679239481621e+01,
         3.1611322818701131207e+01,
        -9.6090021968656180000e+00,
    };
    స్థిర స్థిరరాశి ద్విగుణ q2[] = {
        -5.5194330231005480228e-04,
         3.2547697594819615062e-02,
        -1.1151759188741312645e+00,
         1.3982595353892851542e+01,
        -6.0228002066743340583e+01,
         8.5539563258012929600e+01,
        -3.1446690275135491500e+01,
        1.0,
    };
    ద్విగుణ y, r, గుణకం;
    ఒకవేళ (x == 0)
        తిరిగి 1.0;
    x = fabs(x);
    ఒకవేళ (x <= 15) {
        y = x * x;
        తిరిగి eval_poly(p1, FF_ARRAY_ELEMS(p1), y) / eval_poly(q1, FF_ARRAY_ELEMS(q1), y);
    }
    లేకపోతే {
        y = 1 / x - 1.0 / 15;
        r = eval_poly(p2, FF_ARRAY_ELEMS(p2), y) / eval_poly(q2, FF_ARRAY_ELEMS(q2), y);
        గుణకం = ఘాతాంకం(x) / వర్గమూలం(x);
        తిరిగి గుణకం * r;
    }
}
