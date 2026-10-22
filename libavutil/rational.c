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

#ضمن "avassert.h"
#ضمن <limits.h>

#ضمن "common.h"
#ضمن "mathematics.h"
#ضمن "rational.h"

صحيح av_reduce(صحيح *dst_انگ, صحيح *dst_den,
              int64_t انگ, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    صحيح sign = (انگ < 0) ^ (den < 0);
    int64_t وڏو_گڏيل_ونڊيندڙ = av_وڏو_گڏيل_ونڊيندڙ(FFABS(انگ), FFABS(den));

    إذا (وڏو_گڏيل_ونڊيندڙ) {
        انگ = FFABS(انگ) / وڏو_گڏيل_ونڊيندڙ;
        den = FFABS(den) / وڏو_گڏيل_ونڊيندڙ;
    }
    إذا (انگ <= max && den <= max) {
        a1 = (AVRational) { انگ, den };
        den = 0;
    }

    طالما (den) {
        uint64_t x        = انگ / den;
        int64_t ايندڙ_den  = انگ - den * x;
        int64_t a2n       = x * a1.انگ + a0.انگ;
        int64_t a2d       = x * a1.den + a0.den;

        إذا (a2n > max || a2d > max) {
            إذا (a1.انگ) x =          (max - a0.انگ) / a1.انگ;
            إذا (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            إذا (den * (2 * x * a1.den + a0.den) > انگ * a1.den)
                a1 = (AVRational) { x * a1.انگ + a0.انگ, x * a1.den + a0.den };
            اكسر;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        انگ = den;
        den = ايندڙ_den;
    }
    av_assert2(av_وڏو_گڏيل_ونڊيندڙ(a1.انگ, a1.den) <= 1U);
    av_assert2(a1.انگ <= max && a1.den <= max);

    *dst_انگ = sign ? -a1.انگ : a1.انگ;
    *dst_den = a1.den;

    أرجع den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.انگ, &b.den,
               b.انگ * (int64_t) c.انگ,
               b.den * (int64_t) c.den, وڌ_کان_وڌ_عدد);
    أرجع b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    أرجع av_mul_q(b, (AVRational) { c.den, c.انگ });
}

AVRational av_جوڙيو_q(AVRational b, AVRational c) {
    av_reduce(&b.انگ, &b.den,
               b.انگ * (int64_t) c.den +
               c.انگ * (int64_t) b.den,
               b.den * (int64_t) c.den, وڌ_کان_وڌ_عدد);
    أرجع b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.انگ, &b.den,
               b.انگ * (int64_t) c.den -
               c.انگ * (int64_t) b.den,
               b.den * (int64_t) c.den, وڌ_کان_وڌ_عدد);
    أرجع b;
}

AVRational av_d2q(مزدوج d, صحيح max)
{
    AVRational a;
    صحيح exponent;
    int64_t den;
    إذا (isnan(d))
        أرجع (AVRational) { 0,0 };
    إذا (fabs(d) > وڌ_کان_وڌ_عدد + 3LL)
        أرجع (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.انگ, &a.den, floor(d * den + 0.5), den, max);

    أرجع a;
}

صحيح av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.انگ * (int64_t)q2.den + q2.انگ * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_مٿي = av_rescale_rnd(a, q.den, b, AV_ڦيرو_مٿي);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_هيٺ_ڏانهن = av_rescale_rnd(a, q.den, b, AV_ڦيرو_هيٺ_ڏانهن);

    أرجع ((x_مٿي > q.انگ) - (x_هيٺ_ڏانهن < q.انگ)) * av_cmp_q(q2, q1);
}

صحيح av_ڳوليو_سڀ_کان_ويجهو_q_idx(AVRational q, ثابت AVRational* q_list)
{
    صحيح i, سڀ_کان_ويجهو_q_idx = 0;
    لكل (i = 0; q_list[i].den; i++)
        إذا (av_nearer_q(q, q_list[i], q_list[سڀ_کان_ويجهو_q_idx]) > 0)
            سڀ_کان_ويجهو_q_idx = i;

    أرجع سڀ_کان_ويجهو_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, انگ = q.انگ, den = q.den;
    صحيح سرڪايو;
    uint32_t sign = 0;

    إذا (den < 0) {
        den = -den;
        انگ = -انگ;
    }
    إذا (انگ < 0) {
        انگ = -انگ;
        sign = 1U << 31;
    }

    إذا (!انگ && !den) أرجع 0xFFC00000;
    إذا (!انگ) أرجع 0;
    إذا (!den) أرجع sign | 0x7F800000;

    سرڪايو = 23 + av_log2(den) - av_log2(انگ);
    إذا (سرڪايو >= 0) n = av_rescale(انگ, 1LL<<سرڪايو, den);
    وإلا            n = av_rescale(انگ, 1, den << -سرڪايو);

    سرڪايو -= n >= (1<<24);
    سرڪايو += n <  (1<<23);

    إذا (سرڪايو >= 0) n = av_rescale(انگ, 1LL<<سرڪايو, den);
    وإلا            n = av_rescale(انگ, 1, den << -سرڪايو);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    أرجع sign | (150-سرڪايو)<<23 | (n - (1<<23));
}

AVRational av_وڏو_گڏيل_ونڊيندڙ_q(AVRational a, AVRational b, صحيح max_den, AVRational def)
{
    int64_t وڏو_گڏيل_ونڊيندڙ, lcm;

    وڏو_گڏيل_ونڊيندڙ = av_وڏو_گڏيل_ونڊيندڙ(a.den, b.den);
    lcm = (a.den / وڏو_گڏيل_ونڊيندڙ) * b.den;
    أرجع lcm < max_den ? av_make_q(av_وڏو_گڏيل_ونڊيندڙ(a.انگ, b.انگ), lcm) : def;
}
