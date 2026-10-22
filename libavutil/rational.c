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

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mathematics.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "rational.h"

ਪੂਰਨ av_reduce(ਪੂਰਨ *dst_ਅੰਕ, ਪੂਰਨ *dst_den,
              int64_t ਅੰਕ, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    ਪੂਰਨ sign = (ਅੰਕ < 0) ^ (den < 0);
    int64_t ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ = av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ(FFABS(ਅੰਕ), FFABS(den));

    ਜੇ (ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ) {
        ਅੰਕ = FFABS(ਅੰਕ) / ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ;
        den = FFABS(den) / ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ;
    }
    ਜੇ (ਅੰਕ <= max && den <= max) {
        a1 = (AVRational) { ਅੰਕ, den };
        den = 0;
    }

    ਜਦੋਂ (den) {
        uint64_t x        = ਅੰਕ / den;
        int64_t ਅਗਲਾ_den  = ਅੰਕ - den * x;
        int64_t a2n       = x * a1.ਅੰਕ + a0.ਅੰਕ;
        int64_t a2d       = x * a1.den + a0.den;

        ਜੇ (a2n > max || a2d > max) {
            ਜੇ (a1.ਅੰਕ) x =          (max - a0.ਅੰਕ) / a1.ਅੰਕ;
            ਜੇ (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            ਜੇ (den * (2 * x * a1.den + a0.den) > ਅੰਕ * a1.den)
                a1 = (AVRational) { x * a1.ਅੰਕ + a0.ਅੰਕ, x * a1.den + a0.den };
            ਰੋਕੋ;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        ਅੰਕ = den;
        den = ਅਗਲਾ_den;
    }
    av_assert2(av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ(a1.ਅੰਕ, a1.den) <= 1U);
    av_assert2(a1.ਅੰਕ <= max && a1.den <= max);

    *dst_ਅੰਕ = sign ? -a1.ਅੰਕ : a1.ਅੰਕ;
    *dst_den = a1.den;

    ਵਾਪਸ den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.ਅੰਕ, &b.den,
               b.ਅੰਕ * (int64_t) c.ਅੰਕ,
               b.den * (int64_t) c.den, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
    ਵਾਪਸ b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    ਵਾਪਸ av_mul_q(b, (AVRational) { c.den, c.ਅੰਕ });
}

AVRational av_ਜੋੜੋ_q(AVRational b, AVRational c) {
    av_reduce(&b.ਅੰਕ, &b.den,
               b.ਅੰਕ * (int64_t) c.den +
               c.ਅੰਕ * (int64_t) b.den,
               b.den * (int64_t) c.den, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
    ਵਾਪਸ b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.ਅੰਕ, &b.den,
               b.ਅੰਕ * (int64_t) c.den -
               c.ਅੰਕ * (int64_t) b.den,
               b.den * (int64_t) c.den, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
    ਵਾਪਸ b;
}

AVRational av_d2q(ਦੁੱਗਣਾ d, ਪੂਰਨ max)
{
    AVRational a;
    ਪੂਰਨ exponent;
    int64_t den;
    ਜੇ (isnan(d))
        ਵਾਪਸ (AVRational) { 0,0 };
    ਜੇ (fabs(d) > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ + 3LL)
        ਵਾਪਸ (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.ਅੰਕ, &a.den, floor(d * den + 0.5), den, max);

    ਵਾਪਸ a;
}

ਪੂਰਨ av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.ਅੰਕ * (int64_t)q2.den + q2.ਅੰਕ * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_ਉੱਪਰ = av_rescale_rnd(a, q.den, b, AV_ਗੇੜਾ_ਉੱਪਰ);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_ਥੱਲੇ = av_rescale_rnd(a, q.den, b, AV_ਗੇੜਾ_ਥੱਲੇ);

    ਵਾਪਸ ((x_ਉੱਪਰ > q.ਅੰਕ) - (x_ਥੱਲੇ < q.ਅੰਕ)) * av_cmp_q(q2, q1);
}

ਪੂਰਨ av_ਲੱਭੋ_ਸਭ_ਤੋਂ_ਨੇੜੇ_q_idx(AVRational q, ਅਚਲ AVRational* q_list)
{
    ਪੂਰਨ i, ਸਭ_ਤੋਂ_ਨੇੜੇ_q_idx = 0;
    ਲਈ (i = 0; q_list[i].den; i++)
        ਜੇ (av_nearer_q(q, q_list[i], q_list[ਸਭ_ਤੋਂ_ਨੇੜੇ_q_idx]) > 0)
            ਸਭ_ਤੋਂ_ਨੇੜੇ_q_idx = i;

    ਵਾਪਸ ਸਭ_ਤੋਂ_ਨੇੜੇ_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, ਅੰਕ = q.ਅੰਕ, den = q.den;
    ਪੂਰਨ ਖਿਸਕਾਓ;
    uint32_t sign = 0;

    ਜੇ (den < 0) {
        den = -den;
        ਅੰਕ = -ਅੰਕ;
    }
    ਜੇ (ਅੰਕ < 0) {
        ਅੰਕ = -ਅੰਕ;
        sign = 1U << 31;
    }

    ਜੇ (!ਅੰਕ && !den) ਵਾਪਸ 0xFFC00000;
    ਜੇ (!ਅੰਕ) ਵਾਪਸ 0;
    ਜੇ (!den) ਵਾਪਸ sign | 0x7F800000;

    ਖਿਸਕਾਓ = 23 + av_log2(den) - av_log2(ਅੰਕ);
    ਜੇ (ਖਿਸਕਾਓ >= 0) n = av_rescale(ਅੰਕ, 1LL<<ਖਿਸਕਾਓ, den);
    ਨਹੀਂਤਾਂ            n = av_rescale(ਅੰਕ, 1, den << -ਖਿਸਕਾਓ);

    ਖਿਸਕਾਓ -= n >= (1<<24);
    ਖਿਸਕਾਓ += n <  (1<<23);

    ਜੇ (ਖਿਸਕਾਓ >= 0) n = av_rescale(ਅੰਕ, 1LL<<ਖਿਸਕਾਓ, den);
    ਨਹੀਂਤਾਂ            n = av_rescale(ਅੰਕ, 1, den << -ਖਿਸਕਾਓ);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    ਵਾਪਸ sign | (150-ਖਿਸਕਾਓ)<<23 | (n - (1<<23));
}

AVRational av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ_q(AVRational a, AVRational b, ਪੂਰਨ max_den, AVRational def)
{
    int64_t ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ, lcm;

    ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ = av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ(a.den, b.den);
    lcm = (a.den / ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ) * b.den;
    ਵਾਪਸ lcm < max_den ? av_make_q(av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ(a.ਅੰਕ, b.ਅੰਕ), lcm) : def;
}
