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

#شامل "avassert.h"
#شامل <limits.h>

#شامل "common.h"
#شامل "mathematics.h"
#شامل "rational.h"

صحیح av_reduce(صحیح *dst_عدد, صحیح *dst_den,
              int64_t عدد, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    صحیح sign = (عدد < 0) ^ (den < 0);
    int64_t عاد_اعظم = av_عاد_اعظم(FFABS(عدد), FFABS(den));

    اگر (عاد_اعظم) {
        عدد = FFABS(عدد) / عاد_اعظم;
        den = FFABS(den) / عاد_اعظم;
    }
    اگر (عدد <= max && den <= max) {
        a1 = (AVRational) { عدد, den };
        den = 0;
    }

    جب (den) {
        uint64_t x        = عدد / den;
        int64_t اگلا_den  = عدد - den * x;
        int64_t a2n       = x * a1.عدد + a0.عدد;
        int64_t a2d       = x * a1.den + a0.den;

        اگر (a2n > max || a2d > max) {
            اگر (a1.عدد) x =          (max - a0.عدد) / a1.عدد;
            اگر (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            اگر (den * (2 * x * a1.den + a0.den) > عدد * a1.den)
                a1 = (AVRational) { x * a1.عدد + a0.عدد, x * a1.den + a0.den };
            توڑو;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        عدد = den;
        den = اگلا_den;
    }
    av_assert2(av_عاد_اعظم(a1.عدد, a1.den) <= 1U);
    av_assert2(a1.عدد <= max && a1.den <= max);

    *dst_عدد = sign ? -a1.عدد : a1.عدد;
    *dst_den = a1.den;

    واپس den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.عدد, &b.den,
               b.عدد * (int64_t) c.عدد,
               b.den * (int64_t) c.den, زیادہ_سے_زیادہ_عدد);
    واپس b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    واپس av_mul_q(b, (AVRational) { c.den, c.عدد });
}

AVRational av_جوڑو_q(AVRational b, AVRational c) {
    av_reduce(&b.عدد, &b.den,
               b.عدد * (int64_t) c.den +
               c.عدد * (int64_t) b.den,
               b.den * (int64_t) c.den, زیادہ_سے_زیادہ_عدد);
    واپس b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.عدد, &b.den,
               b.عدد * (int64_t) c.den -
               c.عدد * (int64_t) b.den,
               b.den * (int64_t) c.den, زیادہ_سے_زیادہ_عدد);
    واپس b;
}

AVRational av_d2q(دوہرا d, صحیح max)
{
    AVRational a;
    صحیح exponent;
    int64_t den;
    اگر (isnan(d))
        واپس (AVRational) { 0,0 };
    اگر (fabs(d) > زیادہ_سے_زیادہ_عدد + 3LL)
        واپس (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.عدد, &a.den, floor(d * den + 0.5), den, max);

    واپس a;
}

صحیح av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.عدد * (int64_t)q2.den + q2.عدد * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_اوپر = av_rescale_rnd(a, q.den, b, AV_باری_اوپر);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_نیچے_کو = av_rescale_rnd(a, q.den, b, AV_باری_نیچے_کو);

    واپس ((x_اوپر > q.عدد) - (x_نیچے_کو < q.عدد)) * av_cmp_q(q2, q1);
}

صحیح av_ڈھونڈو_قریب_ترین_q_idx(AVRational q, ثابت AVRational* q_list)
{
    صحیح i, قریب_ترین_q_idx = 0;
    برائے (i = 0; q_list[i].den; i++)
        اگر (av_nearer_q(q, q_list[i], q_list[قریب_ترین_q_idx]) > 0)
            قریب_ترین_q_idx = i;

    واپس قریب_ترین_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, عدد = q.عدد, den = q.den;
    صحیح سرکاؤ;
    uint32_t sign = 0;

    اگر (den < 0) {
        den = -den;
        عدد = -عدد;
    }
    اگر (عدد < 0) {
        عدد = -عدد;
        sign = 1U << 31;
    }

    اگر (!عدد && !den) واپس 0xFFC00000;
    اگر (!عدد) واپس 0;
    اگر (!den) واپس sign | 0x7F800000;

    سرکاؤ = 23 + av_log2(den) - av_log2(عدد);
    اگر (سرکاؤ >= 0) n = av_rescale(عدد, 1LL<<سرکاؤ, den);
    ورنہ            n = av_rescale(عدد, 1, den << -سرکاؤ);

    سرکاؤ -= n >= (1<<24);
    سرکاؤ += n <  (1<<23);

    اگر (سرکاؤ >= 0) n = av_rescale(عدد, 1LL<<سرکاؤ, den);
    ورنہ            n = av_rescale(عدد, 1, den << -سرکاؤ);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    واپس sign | (150-سرکاؤ)<<23 | (n - (1<<23));
}

AVRational av_عاد_اعظم_q(AVRational a, AVRational b, صحیح max_den, AVRational def)
{
    int64_t عاد_اعظم, lcm;

    عاد_اعظم = av_عاد_اعظم(a.den, b.den);
    lcm = (a.den / عاد_اعظم) * b.den;
    واپس lcm < max_den ? av_make_q(av_عاد_اعظم(a.عدد, b.عدد), lcm) : def;
}
