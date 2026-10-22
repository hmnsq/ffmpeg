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

ಪೂರ್ಣಾಂಕ av_reduce(ಪೂರ್ಣಾಂಕ *dst_ಅಂಕೆ, ಪೂರ್ಣಾಂಕ *dst_den,
              int64_t ಅಂಕೆ, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    ಪೂರ್ಣಾಂಕ sign = (ಅಂಕೆ < 0) ^ (den < 0);
    int64_t ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ = av_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ(FFABS(ಅಂಕೆ), FFABS(den));

    ಆದರೆ (ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ) {
        ಅಂಕೆ = FFABS(ಅಂಕೆ) / ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ;
        den = FFABS(den) / ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ;
    }
    ಆದರೆ (ಅಂಕೆ <= max && den <= max) {
        a1 = (AVRational) { ಅಂಕೆ, den };
        den = 0;
    }

    ಆಗ (den) {
        uint64_t x        = ಅಂಕೆ / den;
        int64_t ಮುಂದಿನ_den  = ಅಂಕೆ - den * x;
        int64_t a2n       = x * a1.ಅಂಕೆ + a0.ಅಂಕೆ;
        int64_t a2d       = x * a1.den + a0.den;

        ಆದರೆ (a2n > max || a2d > max) {
            ಆದರೆ (a1.ಅಂಕೆ) x =          (max - a0.ಅಂಕೆ) / a1.ಅಂಕೆ;
            ಆದರೆ (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            ಆದರೆ (den * (2 * x * a1.den + a0.den) > ಅಂಕೆ * a1.den)
                a1 = (AVRational) { x * a1.ಅಂಕೆ + a0.ಅಂಕೆ, x * a1.den + a0.den };
            ನಿಲ್ಲಿಸು;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        ಅಂಕೆ = den;
        den = ಮುಂದಿನ_den;
    }
    av_assert2(av_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ(a1.ಅಂಕೆ, a1.den) <= 1U);
    av_assert2(a1.ಅಂಕೆ <= max && a1.den <= max);

    *dst_ಅಂಕೆ = sign ? -a1.ಅಂಕೆ : a1.ಅಂಕೆ;
    *dst_den = a1.den;

    ಹಿಂತಿರುಗಿ den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.ಅಂಕೆ, &b.den,
               b.ಅಂಕೆ * (int64_t) c.ಅಂಕೆ,
               b.den * (int64_t) c.den, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
    ಹಿಂತಿರುಗಿ b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    ಹಿಂತಿರುಗಿ av_mul_q(b, (AVRational) { c.den, c.ಅಂಕೆ });
}

AVRational av_ಕೂಡಿಸು_q(AVRational b, AVRational c) {
    av_reduce(&b.ಅಂಕೆ, &b.den,
               b.ಅಂಕೆ * (int64_t) c.den +
               c.ಅಂಕೆ * (int64_t) b.den,
               b.den * (int64_t) c.den, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
    ಹಿಂತಿರುಗಿ b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.ಅಂಕೆ, &b.den,
               b.ಅಂಕೆ * (int64_t) c.den -
               c.ಅಂಕೆ * (int64_t) b.den,
               b.den * (int64_t) c.den, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
    ಹಿಂತಿರುಗಿ b;
}

AVRational av_d2q(ದ್ವಿಗುಣ d, ಪೂರ್ಣಾಂಕ max)
{
    AVRational a;
    ಪೂರ್ಣಾಂಕ exponent;
    int64_t den;
    ಆದರೆ (isnan(d))
        ಹಿಂತಿರುಗಿ (AVRational) { 0,0 };
    ಆದರೆ (fabs(d) > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ + 3LL)
        ಹಿಂತಿರುಗಿ (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.ಅಂಕೆ, &a.den, floor(d * den + 0.5), den, max);

    ಹಿಂತಿರುಗಿ a;
}

ಪೂರ್ಣಾಂಕ av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.ಅಂಕೆ * (int64_t)q2.den + q2.ಅಂಕೆ * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_ಮೇಲೆ = av_rescale_rnd(a, q.den, b, AV_ಸುತ್ತು_ಮೇಲೆ);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_ಕೆಳಕ್ಕೆ = av_rescale_rnd(a, q.den, b, AV_ಸುತ್ತು_ಕೆಳಕ್ಕೆ);

    ಹಿಂತಿರುಗಿ ((x_ಮೇಲೆ > q.ಅಂಕೆ) - (x_ಕೆಳಕ್ಕೆ < q.ಅಂಕೆ)) * av_cmp_q(q2, q1);
}

ಪೂರ್ಣಾಂಕ av_ಕಂಡುಹಿಡಿ_ಹತ್ತಿರದ_q_idx(AVRational q, ಸ್ಥಿರಾಂಕ AVRational* q_list)
{
    ಪೂರ್ಣಾಂಕ i, ಹತ್ತಿರದ_q_idx = 0;
    ಗಾಗಿ (i = 0; q_list[i].den; i++)
        ಆದರೆ (av_nearer_q(q, q_list[i], q_list[ಹತ್ತಿರದ_q_idx]) > 0)
            ಹತ್ತಿರದ_q_idx = i;

    ಹಿಂತಿರುಗಿ ಹತ್ತಿರದ_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, ಅಂಕೆ = q.ಅಂಕೆ, den = q.den;
    ಪೂರ್ಣಾಂಕ ಸರಿಸು;
    uint32_t sign = 0;

    ಆದರೆ (den < 0) {
        den = -den;
        ಅಂಕೆ = -ಅಂಕೆ;
    }
    ಆದರೆ (ಅಂಕೆ < 0) {
        ಅಂಕೆ = -ಅಂಕೆ;
        sign = 1U << 31;
    }

    ಆದರೆ (!ಅಂಕೆ && !den) ಹಿಂತಿರುಗಿ 0xFFC00000;
    ಆದರೆ (!ಅಂಕೆ) ಹಿಂತಿರುಗಿ 0;
    ಆದರೆ (!den) ಹಿಂತಿರುಗಿ sign | 0x7F800000;

    ಸರಿಸು = 23 + av_log2(den) - av_log2(ಅಂಕೆ);
    ಆದರೆ (ಸರಿಸು >= 0) n = av_rescale(ಅಂಕೆ, 1LL<<ಸರಿಸು, den);
    ಇಲ್ಲದಿದ್ದರೆ            n = av_rescale(ಅಂಕೆ, 1, den << -ಸರಿಸು);

    ಸರಿಸು -= n >= (1<<24);
    ಸರಿಸು += n <  (1<<23);

    ಆದರೆ (ಸರಿಸು >= 0) n = av_rescale(ಅಂಕೆ, 1LL<<ಸರಿಸು, den);
    ಇಲ್ಲದಿದ್ದರೆ            n = av_rescale(ಅಂಕೆ, 1, den << -ಸರಿಸು);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    ಹಿಂತಿರುಗಿ sign | (150-ಸರಿಸು)<<23 | (n - (1<<23));
}

AVRational av_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ_q(AVRational a, AVRational b, ಪೂರ್ಣಾಂಕ max_den, AVRational def)
{
    int64_t ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ, lcm;

    ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ = av_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ(a.den, b.den);
    lcm = (a.den / ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ) * b.den;
    ಹಿಂತಿರುಗಿ lcm < max_den ? av_make_q(av_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ(a.ಅಂಕೆ, b.ಅಂಕೆ), lcm) : def;
}
