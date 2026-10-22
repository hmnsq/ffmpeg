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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avutil.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mathematics.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/intmath.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"

/* Stein's binary GCD algorithm:
 * https://en.wikipedia.org/wiki/Binary_GCD_algorithm */
int64_t av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ(int64_t a, int64_t b) {
    ਪੂਰਨ za, zb, k;
    int64_t u, v;
    ਜੇ (a == 0)
        ਵਾਪਸ b;
    ਜੇ (b == 0)
        ਵਾਪਸ a;
    za = ff_ctzll(a);
    zb = ff_ctzll(b);
    k  = FFMIN(za, zb);
    u = llabs(a >> za);
    v = llabs(b >> zb);
    ਜਦੋਂ (u != v) {
        ਜੇ (u > v)
            FFSWAP(int64_t, v, u);
        v -= u;
        v >>= ff_ctzll(v);
    }
    ਵਾਪਸ (uint64_t)u << k;
}

int64_t av_rescale_rnd(int64_t a, int64_t b, int64_t c, ਗਿਣਤੀ AVRounding rnd)
{
    int64_t r = 0;
    av_assert2(c > 0);
    av_assert2(b >=0);
    av_assert2((ਬਿਨਾਨਿਸ਼ਾਨੀ)(rnd&~AV_ਗੇੜਾ_PASS_MINMAX)<=5 && (rnd&~AV_ਗੇੜਾ_PASS_MINMAX)!=4);

    ਜੇ (c <= 0 || b < 0 || !((ਬਿਨਾਨਿਸ਼ਾਨੀ)(rnd&~AV_ਗੇੜਾ_PASS_MINMAX)<=5 && (rnd&~AV_ਗੇੜਾ_PASS_MINMAX)!=4))
        ਵਾਪਸ INT64_MIN;

    ਜੇ (rnd & AV_ਗੇੜਾ_PASS_MINMAX) {
        ਜੇ (a == INT64_MIN || a == INT64_MAX)
            ਵਾਪਸ a;
        rnd -= AV_ਗੇੜਾ_PASS_MINMAX;
    }

    ਜੇ (a < 0)
        ਵਾਪਸ -(uint64_t)av_rescale_rnd(-FFMAX(a, -INT64_MAX), b, c, rnd ^ ((rnd >> 1) & 1));

    ਜੇ (rnd == AV_ਗੇੜਾ_NEAR_INF)
        r = c / 2;
    ਨਹੀਂਤਾਂ ਜੇ (rnd & 1)
        r = c - 1;

    ਜੇ (b <= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ && c <= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ) {
        ਜੇ (a <= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ)
            ਵਾਪਸ (a * b + r) / c;
        ਨਹੀਂਤਾਂ {
            int64_t ad = a / c;
            int64_t a2 = (a % c * b + r) / c;
            ਜੇ (ad >= INT32_MAX && b && ad > (INT64_MAX - a2) / b)
                ਵਾਪਸ INT64_MIN;
            ਵਾਪਸ ad * b + a2;
        }
    } ਨਹੀਂਤਾਂ {
#ਜੇ 1
        uint64_t a0  = a & 0xFFFFFFFF;
        uint64_t a1  = a >> 32;
        uint64_t b0  = b & 0xFFFFFFFF;
        uint64_t b1  = b >> 32;
        uint64_t t1  = a0 * b1 + a1 * b0;
        uint64_t t1a = t1 << 32;
        ਪੂਰਨ i;

        a0  = a0 * b0 + t1a;
        a1  = a1 * b1 + (t1 >> 32) + (a0 < t1a);
        a0 += r;
        a1 += a0 < r;

        ਲਈ (i = 63; i >= 0; i--) {
            a1 += a1 + ((a0 >> i) & 1);
            t1 += t1;
            ਜੇ (c <= a1) {
                a1 -= c;
                t1++;
            }
        }
        ਜੇ (t1 > INT64_MAX)
            ਵਾਪਸ INT64_MIN;
        ਵਾਪਸ t1;
#ਨਹੀਂਤਾਂ
        /* reference code doing (a*b + r) / c, requires libavutil/integer.h */
        AVInteger ai;
        ai = av_mul_i(av_int2i(a), av_int2i(b));
        ai = av_ਜੋੜੋ_i(ai, av_int2i(r));

        ਵਾਪਸ av_i2int(av_div_i(ai, av_int2i(c)));
#ਜੇ_ਅੰਤ
    }
}

int64_t av_rescale(int64_t a, int64_t b, int64_t c)
{
    ਵਾਪਸ av_rescale_rnd(a, b, c, AV_ਗੇੜਾ_NEAR_INF);
}

int64_t av_rescale_q_rnd(int64_t a, AVRational bq, AVRational cq,
                         ਗਿਣਤੀ AVRounding rnd)
{
    int64_t b = bq.ਅੰਕ * (int64_t)cq.den;
    int64_t c = cq.ਅੰਕ * (int64_t)bq.den;
    ਵਾਪਸ av_rescale_rnd(a, b, c, rnd);
}

int64_t av_rescale_q(int64_t a, AVRational bq, AVRational cq)
{
    ਵਾਪਸ av_rescale_q_rnd(a, bq, cq, AV_ਗੇੜਾ_NEAR_INF);
}

ਪੂਰਨ av_compare_ts(int64_t ts_a, AVRational tb_a, int64_t ts_b, AVRational tb_b)
{
    int64_t a = tb_a.ਅੰਕ * (int64_t)tb_b.den;
    int64_t b = tb_b.ਅੰਕ * (int64_t)tb_a.den;
    ਜੇ ((FFABS64U(ts_a)|a|FFABS64U(ts_b)|b) <= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ)
        ਵਾਪਸ (ts_a*a > ts_b*b) - (ts_a*a < ts_b*b);
    ਜੇ (av_rescale_rnd(ts_a, a, b, AV_ਗੇੜਾ_ਥੱਲੇ) < ts_b)
        ਵਾਪਸ -1;
    ਜੇ (av_rescale_rnd(ts_b, b, a, AV_ਗੇੜਾ_ਥੱਲੇ) < ts_a)
        ਵਾਪਸ 1;
    ਵਾਪਸ 0;
}

int64_t av_compare_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    int64_t c = (a - b) & (mod - 1);
    ਜੇ (c > (mod >> 1))
        c -= mod;
    ਵਾਪਸ c;
}

int64_t av_rescale_delta(AVRational ਵਿੱਚ_tb, int64_t ਵਿੱਚ_ts,  AVRational fs_tb, ਪੂਰਨ duration, int64_t *ਆਖਰੀ, AVRational ਬਾਹਰਲਾ_tb){
    int64_t a, b, this;

    av_assert0(ਵਿੱਚ_ts != AV_NOPTS_ਮੁੱਲ);
    av_assert0(duration >= 0);

    ਜੇ (*ਆਖਰੀ == AV_NOPTS_ਮੁੱਲ || !duration || ਵਿੱਚ_tb.ਅੰਕ*(int64_t)ਬਾਹਰਲਾ_tb.den <= ਬਾਹਰਲਾ_tb.ਅੰਕ*(int64_t)ਵਿੱਚ_tb.den) {
simple_ਗੇੜਾ:
        *ਆਖਰੀ = av_rescale_q(ਵਿੱਚ_ts, ਵਿੱਚ_tb, fs_tb) + duration;
        ਵਾਪਸ av_rescale_q(ਵਿੱਚ_ts, ਵਿੱਚ_tb, ਬਾਹਰਲਾ_tb);
    }

    a =  av_rescale_q_rnd(2*ਵਿੱਚ_ts-1, ਵਿੱਚ_tb, fs_tb, AV_ਗੇੜਾ_ਥੱਲੇ)   >>1;
    b = (av_rescale_q_rnd(2*ਵਿੱਚ_ts+1, ਵਿੱਚ_tb, fs_tb, AV_ਗੇੜਾ_ਉੱਪਰ  )+1)>>1;
    ਜੇ (*ਆਖਰੀ < 2*a - b || *ਆਖਰੀ > 2*b - a)
        ਜਾਓ simple_ਗੇੜਾ;

    this = av_clip64(*ਆਖਰੀ, a, b);
    *ਆਖਰੀ = this + duration;

    ਵਾਪਸ av_rescale_q(this, fs_tb, ਬਾਹਰਲਾ_tb);
}

int64_t av_ਜੋੜੋ_stable(AVRational ts_tb, int64_t ts, AVRational inc_tb, int64_t inc)
{
    int64_t m, d;

    ਜੇ (inc != 1)
        inc_tb = av_mul_q(inc_tb, (AVRational) {inc, 1});

    m = inc_tb.ਅੰਕ * (int64_t)ts_tb.den;
    d = inc_tb.den * (int64_t)ts_tb.ਅੰਕ;

    ਜੇ (m % d == 0 && ts <= INT64_MAX - m / d)
        ਵਾਪਸ ts + m / d;
    ਜੇ (m < d)
        ਵਾਪਸ ts;

    {
        int64_t old = av_rescale_q(ts, ts_tb, inc_tb);
        int64_t old_ts = av_rescale_q(old, inc_tb, ts_tb);

        ਜੇ (old == INT64_MAX || old == AV_NOPTS_ਮੁੱਲ || old_ts == AV_NOPTS_ਮੁੱਲ)
            ਵਾਪਸ ts;

        ਵਾਪਸ av_sat_add64(av_rescale_q(old + 1, inc_tb, ts_tb), ts - old_ts);
    }
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਦੁੱਗਣਾ eval_poly(ਅਚਲ ਦੁੱਗਣਾ *coeff, ਪੂਰਨ ਮਾਪ, ਦੁੱਗਣਾ x) {
    ਦੁੱਗਣਾ ਜੋੜ = coeff[ਮਾਪ-1];
    ਪੂਰਨ i;
    ਲਈ (i = ਮਾਪ-2; i >= 0; --i) {
        ਜੋੜ *= x;
        ਜੋੜ += coeff[i];
    }
    ਵਾਪਸ ਜੋੜ;
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

ਦੁੱਗਣਾ av_bessel_i0(ਦੁੱਗਣਾ x) {
// Modified Bessel function of the first kind of order zero
// minimax rational approximations on intervals, see
// Blair and Edwards, Chalk River Report AECL-4928, 1974
    ਸਥਿਰ ਅਚਲ ਦੁੱਗਣਾ p1[] = {
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
    ਸਥਿਰ ਅਚਲ ਦੁੱਗਣਾ q1[] = {
        -2.2335582639474375245e+15,
         7.8858692566751002988e+12,
        -1.2207067397808979846e+10,
         1.0377081058062166144e+07,
        -4.8527560179962773045e+03,
         1.0,
    };
    ਸਥਿਰ ਅਚਲ ਦੁੱਗਣਾ p2[] = {
        -2.2210262233306573296e-04,
         1.3067392038106924055e-02,
        -4.4700805721174453923e-01,
         5.5674518371240761397e+00,
        -2.3517945679239481621e+01,
         3.1611322818701131207e+01,
        -9.6090021968656180000e+00,
    };
    ਸਥਿਰ ਅਚਲ ਦੁੱਗਣਾ q2[] = {
        -5.5194330231005480228e-04,
         3.2547697594819615062e-02,
        -1.1151759188741312645e+00,
         1.3982595353892851542e+01,
        -6.0228002066743340583e+01,
         8.5539563258012929600e+01,
        -3.1446690275135491500e+01,
        1.0,
    };
    ਦੁੱਗਣਾ y, r, ਗੁਣਕ;
    ਜੇ (x == 0)
        ਵਾਪਸ 1.0;
    x = fabs(x);
    ਜੇ (x <= 15) {
        y = x * x;
        ਵਾਪਸ eval_poly(p1, FF_ARRAY_ELEMS(p1), y) / eval_poly(q1, FF_ARRAY_ELEMS(q1), y);
    }
    ਨਹੀਂਤਾਂ {
        y = 1 / x - 1.0 / 15;
        r = eval_poly(p2, FF_ARRAY_ELEMS(p2), y) / eval_poly(q2, FF_ARRAY_ELEMS(q2), y);
        ਗੁਣਕ = ਘਾਤਾਂਕ(x) / ਵਰਗਮੂਲ(x);
        ਵਾਪਸ ਗੁਣਕ * r;
    }
}
