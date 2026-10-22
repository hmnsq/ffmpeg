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

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ <limits.h>

#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "mathematics.h"
#ಅನ್ತರ್ಭಾವ "rational.h"

ಪೂರ್ಣಾಙ್ಕ av_reduce(ಪೂರ್ಣಾಙ್ಕ *dst_ಅಂಕೆ, ಪೂರ್ಣಾಙ್ಕ *dst_den,
              int64_t ಅಂಕೆ, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    ಪೂರ್ಣಾಙ್ಕ sign = (ಅಂಕೆ < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(ಅಂಕೆ), FFABS(den));

    ಯದಿ (gcd) {
        ಅಂಕೆ = FFABS(ಅಂಕೆ) / gcd;
        den = FFABS(den) / gcd;
    }
    ಯದಿ (ಅಂಕೆ <= max && den <= max) {
        a1 = (AVRational) { ಅಂಕೆ, den };
        den = 0;
    }

    ಯಾವತ್ (den) {
        uint64_t x        = ಅಂಕೆ / den;
        int64_t next_den  = ಅಂಕೆ - den * x;
        int64_t a2n       = x * a1.ಅಂಕೆ + a0.ಅಂಕೆ;
        int64_t a2d       = x * a1.den + a0.den;

        ಯದಿ (a2n > max || a2d > max) {
            ಯದಿ (a1.ಅಂಕೆ) x =          (max - a0.ಅಂಕೆ) / a1.ಅಂಕೆ;
            ಯದಿ (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            ಯದಿ (den * (2 * x * a1.den + a0.den) > ಅಂಕೆ * a1.den)
                a1 = (AVRational) { x * a1.ಅಂಕೆ + a0.ಅಂಕೆ, x * a1.den + a0.den };
            ಭಙ್ಗ;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        ಅಂಕೆ = den;
        den = next_den;
    }
    av_assert2(av_gcd(a1.ಅಂಕೆ, a1.den) <= 1U);
    av_assert2(a1.ಅಂಕೆ <= max && a1.den <= max);

    *dst_ಅಂಕೆ = sign ? -a1.ಅಂಕೆ : a1.ಅಂಕೆ;
    *dst_den = a1.den;

    ಪ್ರತ್ಯಾಗಮ den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.ಅಂಕೆ, &b.den,
               b.ಅಂಕೆ * (int64_t) c.ಅಂಕೆ,
               b.den * (int64_t) c.den, INT_MAX);
    ಪ್ರತ್ಯಾಗಮ b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    ಪ್ರತ್ಯಾಗಮ av_mul_q(b, (AVRational) { c.den, c.ಅಂಕೆ });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.ಅಂಕೆ, &b.den,
               b.ಅಂಕೆ * (int64_t) c.den +
               c.ಅಂಕೆ * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    ಪ್ರತ್ಯಾಗಮ b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.ಅಂಕೆ, &b.den,
               b.ಅಂಕೆ * (int64_t) c.den -
               c.ಅಂಕೆ * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    ಪ್ರತ್ಯಾಗಮ b;
}

AVRational av_d2q(ದ್ವಿಗುಣ d, ಪೂರ್ಣಾಙ್ಕ max)
{
    AVRational a;
    ಪೂರ್ಣಾಙ್ಕ exponent;
    int64_t den;
    ಯದಿ (isnan(d))
        ಪ್ರತ್ಯಾಗಮ (AVRational) { 0,0 };
    ಯದಿ (fabs(d) > INT_MAX + 3LL)
        ಪ್ರತ್ಯಾಗಮ (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.ಅಂಕೆ, &a.den, floor(d * den + 0.5), den, max);

    ಪ್ರತ್ಯಾಗಮ a;
}

ಪೂರ್ಣಾಙ್ಕ av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.ಅಂಕೆ * (int64_t)q2.den + q2.ಅಂಕೆ * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    ಪ್ರತ್ಯಾಗಮ ((x_up > q.ಅಂಕೆ) - (x_down < q.ಅಂಕೆ)) * av_cmp_q(q2, q1);
}

ಪೂರ್ಣಾಙ್ಕ av_find_nearest_q_idx(AVRational q, ಧ್ರುವ AVRational* q_list)
{
    ಪೂರ್ಣಾಙ್ಕ i, nearest_q_idx = 0;
    ಪ್ರತಿ (i = 0; q_list[i].den; i++)
        ಯದಿ (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    ಪ್ರತ್ಯಾಗಮ nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, ಅಂಕೆ = q.ಅಂಕೆ, den = q.den;
    ಪೂರ್ಣಾಙ್ಕ shift;
    uint32_t sign = 0;

    ಯದಿ (den < 0) {
        den = -den;
        ಅಂಕೆ = -ಅಂಕೆ;
    }
    ಯದಿ (ಅಂಕೆ < 0) {
        ಅಂಕೆ = -ಅಂಕೆ;
        sign = 1U << 31;
    }

    ಯದಿ (!ಅಂಕೆ && !den) ಪ್ರತ್ಯಾಗಮ 0xFFC00000;
    ಯದಿ (!ಅಂಕೆ) ಪ್ರತ್ಯಾಗಮ 0;
    ಯದಿ (!den) ಪ್ರತ್ಯಾಗಮ sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(ಅಂಕೆ);
    ಯದಿ (shift >= 0) n = av_rescale(ಅಂಕೆ, 1LL<<shift, den);
    ಅನ್ಯಥಾ            n = av_rescale(ಅಂಕೆ, 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    ಯದಿ (shift >= 0) n = av_rescale(ಅಂಕೆ, 1LL<<shift, den);
    ಅನ್ಯಥಾ            n = av_rescale(ಅಂಕೆ, 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    ಪ್ರತ್ಯಾಗಮ sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, ಪೂರ್ಣಾಙ್ಕ max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    ಪ್ರತ್ಯಾಗಮ lcm < max_den ? av_make_q(av_gcd(a.ಅಂಕೆ, b.ಅಂಕೆ), lcm) : def;
}
