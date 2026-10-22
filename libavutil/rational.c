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

صحيح av_reduce(صحيح *dst_رقم, صحيح *dst_den,
              int64_t رقم, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    صحيح sign = (رقم < 0) ^ (den < 0);
    int64_t بزرگترین_مقسوم_علیه = av_بزرگترین_مقسوم_علیه(FFABS(رقم), FFABS(den));

    إذا (بزرگترین_مقسوم_علیه) {
        رقم = FFABS(رقم) / بزرگترین_مقسوم_علیه;
        den = FFABS(den) / بزرگترین_مقسوم_علیه;
    }
    إذا (رقم <= max && den <= max) {
        a1 = (AVRational) { رقم, den };
        den = 0;
    }

    طالما (den) {
        uint64_t x        = رقم / den;
        int64_t بعدی_den  = رقم - den * x;
        int64_t a2n       = x * a1.رقم + a0.رقم;
        int64_t a2d       = x * a1.den + a0.den;

        إذا (a2n > max || a2d > max) {
            إذا (a1.رقم) x =          (max - a0.رقم) / a1.رقم;
            إذا (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            إذا (den * (2 * x * a1.den + a0.den) > رقم * a1.den)
                a1 = (AVRational) { x * a1.رقم + a0.رقم, x * a1.den + a0.den };
            اكسر;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        رقم = den;
        den = بعدی_den;
    }
    av_assert2(av_بزرگترین_مقسوم_علیه(a1.رقم, a1.den) <= 1U);
    av_assert2(a1.رقم <= max && a1.den <= max);

    *dst_رقم = sign ? -a1.رقم : a1.رقم;
    *dst_den = a1.den;

    أرجع den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.رقم, &b.den,
               b.رقم * (int64_t) c.رقم,
               b.den * (int64_t) c.den, بیشترین_صحیح);
    أرجع b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    أرجع av_mul_q(b, (AVRational) { c.den, c.رقم });
}

AVRational av_جمع_کن_q(AVRational b, AVRational c) {
    av_reduce(&b.رقم, &b.den,
               b.رقم * (int64_t) c.den +
               c.رقم * (int64_t) b.den,
               b.den * (int64_t) c.den, بیشترین_صحیح);
    أرجع b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.رقم, &b.den,
               b.رقم * (int64_t) c.den -
               c.رقم * (int64_t) b.den,
               b.den * (int64_t) c.den, بیشترین_صحیح);
    أرجع b;
}

AVRational av_d2q(مزدوج d, صحيح max)
{
    AVRational a;
    صحيح exponent;
    int64_t den;
    إذا (isnan(d))
        أرجع (AVRational) { 0,0 };
    إذا (fabs(d) > بیشترین_صحیح + 3LL)
        أرجع (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.رقم, &a.den, floor(d * den + 0.5), den, max);

    أرجع a;
}

صحيح av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.رقم * (int64_t)q2.den + q2.رقم * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_به_بالا = av_rescale_rnd(a, q.den, b, AV_دور_به_بالا);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_پایین = av_rescale_rnd(a, q.den, b, AV_دور_پایین);

    أرجع ((x_به_بالا > q.رقم) - (x_پایین < q.رقم)) * av_cmp_q(q2, q1);
}

صحيح av_پیدا_کن_نزدیکترین_q_idx(AVRational q, ثابت AVRational* q_list)
{
    صحيح i, نزدیکترین_q_idx = 0;
    لكل (i = 0; q_list[i].den; i++)
        إذا (av_nearer_q(q, q_list[i], q_list[نزدیکترین_q_idx]) > 0)
            نزدیکترین_q_idx = i;

    أرجع نزدیکترین_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, رقم = q.رقم, den = q.den;
    صحيح لغزش;
    uint32_t sign = 0;

    إذا (den < 0) {
        den = -den;
        رقم = -رقم;
    }
    إذا (رقم < 0) {
        رقم = -رقم;
        sign = 1U << 31;
    }

    إذا (!رقم && !den) أرجع 0xFFC00000;
    إذا (!رقم) أرجع 0;
    إذا (!den) أرجع sign | 0x7F800000;

    لغزش = 23 + av_log2(den) - av_log2(رقم);
    إذا (لغزش >= 0) n = av_rescale(رقم, 1LL<<لغزش, den);
    وإلا            n = av_rescale(رقم, 1, den << -لغزش);

    لغزش -= n >= (1<<24);
    لغزش += n <  (1<<23);

    إذا (لغزش >= 0) n = av_rescale(رقم, 1LL<<لغزش, den);
    وإلا            n = av_rescale(رقم, 1, den << -لغزش);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    أرجع sign | (150-لغزش)<<23 | (n - (1<<23));
}

AVRational av_بزرگترین_مقسوم_علیه_q(AVRational a, AVRational b, صحيح max_den, AVRational def)
{
    int64_t بزرگترین_مقسوم_علیه, lcm;

    بزرگترین_مقسوم_علیه = av_بزرگترین_مقسوم_علیه(a.den, b.den);
    lcm = (a.den / بزرگترین_مقسوم_علیه) * b.den;
    أرجع lcm < max_den ? av_make_q(av_بزرگترین_مقسوم_علیه(a.رقم, b.رقم), lcm) : def;
}
