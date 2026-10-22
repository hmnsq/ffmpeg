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

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ <limits.h>

#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "mathematics.h"
#അന്തര്ഭാവ "rational.h"

പൂർണ്ണസംഖ്യ av_reduce(പൂർണ്ണസംഖ്യ *dst_അക്കം, പൂർണ്ണസംഖ്യ *dst_den,
              int64_t അക്കം, int64_t den, int64_t max)
{
    AVRational a0 = { 0, 1 }, a1 = { 1, 0 };
    പൂർണ്ണസംഖ്യ sign = (അക്കം < 0) ^ (den < 0);
    int64_t gcd = av_gcd(FFABS(അക്കം), FFABS(den));

    എങ്കിൽ (gcd) {
        അക്കം = FFABS(അക്കം) / gcd;
        den = FFABS(den) / gcd;
    }
    എങ്കിൽ (അക്കം <= max && den <= max) {
        a1 = (AVRational) { അക്കം, den };
        den = 0;
    }

    ആകുമ്പോൾ (den) {
        uint64_t x        = അക്കം / den;
        int64_t next_den  = അക്കം - den * x;
        int64_t a2n       = x * a1.അക്കം + a0.അക്കം;
        int64_t a2d       = x * a1.den + a0.den;

        എങ്കിൽ (a2n > max || a2d > max) {
            എങ്കിൽ (a1.അക്കം) x =          (max - a0.അക്കം) / a1.അക്കം;
            എങ്കിൽ (a1.den) x = FFMIN(x, (max - a0.den) / a1.den);

            എങ്കിൽ (den * (2 * x * a1.den + a0.den) > അക്കം * a1.den)
                a1 = (AVRational) { x * a1.അക്കം + a0.അക്കം, x * a1.den + a0.den };
            നിർത്തുക;
        }

        a0  = a1;
        a1  = (AVRational) { a2n, a2d };
        അക്കം = den;
        den = next_den;
    }
    av_assert2(av_gcd(a1.അക്കം, a1.den) <= 1U);
    av_assert2(a1.അക്കം <= max && a1.den <= max);

    *dst_അക്കം = sign ? -a1.അക്കം : a1.അക്കം;
    *dst_den = a1.den;

    തിരികെ den == 0;
}

AVRational av_mul_q(AVRational b, AVRational c)
{
    av_reduce(&b.അക്കം, &b.den,
               b.അക്കം * (int64_t) c.അക്കം,
               b.den * (int64_t) c.den, INT_MAX);
    തിരികെ b;
}

AVRational av_div_q(AVRational b, AVRational c)
{
    തിരികെ av_mul_q(b, (AVRational) { c.den, c.അക്കം });
}

AVRational av_add_q(AVRational b, AVRational c) {
    av_reduce(&b.അക്കം, &b.den,
               b.അക്കം * (int64_t) c.den +
               c.അക്കം * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    തിരികെ b;
}

AVRational av_sub_q(AVRational b, AVRational c)
{
    av_reduce(&b.അക്കം, &b.den,
               b.അക്കം * (int64_t) c.den -
               c.അക്കം * (int64_t) b.den,
               b.den * (int64_t) c.den, INT_MAX);
    തിരികെ b;
}

AVRational av_d2q(ഇരട്ട d, പൂർണ്ണസംഖ്യ max)
{
    AVRational a;
    പൂർണ്ണസംഖ്യ exponent;
    int64_t den;
    എങ്കിൽ (isnan(d))
        തിരികെ (AVRational) { 0,0 };
    എങ്കിൽ (fabs(d) > INT_MAX + 3LL)
        തിരികെ (AVRational) { d < 0 ? -1 : 1, 0 };
    frexp(d, &exponent);
    exponent = FFMAX(exponent-1, 0);
    den = 1LL << (62 - exponent);
    // (int64_t)rint() and llrint() do not work with gcc on ia64 and sparc64,
    // see Ticket2713 for affected gcc/glibc versions
    av_reduce(&a.അക്കം, &a.den, floor(d * den + 0.5), den, max);

    തിരികെ a;
}

പൂർണ്ണസംഖ്യ av_nearer_q(AVRational q, AVRational q1, AVRational q2)
{
    /* n/d is q, a/b is the median between q1 and q2 */
    int64_t a = q1.അക്കം * (int64_t)q2.den + q2.അക്കം * (int64_t)q1.den;
    int64_t b = 2 * (int64_t)q1.den * q2.den;

    /* rnd_up(a*d/b) > n => a*d/b > n */
    int64_t x_up = av_rescale_rnd(a, q.den, b, AV_ROUND_UP);

    /* rnd_down(a*d/b) < n => a*d/b < n */
    int64_t x_down = av_rescale_rnd(a, q.den, b, AV_ROUND_DOWN);

    തിരികെ ((x_up > q.അക്കം) - (x_down < q.അക്കം)) * av_cmp_q(q2, q1);
}

പൂർണ്ണസംഖ്യ av_find_nearest_q_idx(AVRational q, സ്ഥിരം AVRational* q_list)
{
    പൂർണ്ണസംഖ്യ i, nearest_q_idx = 0;
    വേണ്ടി (i = 0; q_list[i].den; i++)
        എങ്കിൽ (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    തിരികെ nearest_q_idx;
}

uint32_t av_q2intfloat(AVRational q) {
    int64_t n, അക്കം = q.അക്കം, den = q.den;
    പൂർണ്ണസംഖ്യ shift;
    uint32_t sign = 0;

    എങ്കിൽ (den < 0) {
        den = -den;
        അക്കം = -അക്കം;
    }
    എങ്കിൽ (അക്കം < 0) {
        അക്കം = -അക്കം;
        sign = 1U << 31;
    }

    എങ്കിൽ (!അക്കം && !den) തിരികെ 0xFFC00000;
    എങ്കിൽ (!അക്കം) തിരികെ 0;
    എങ്കിൽ (!den) തിരികെ sign | 0x7F800000;

    shift = 23 + av_log2(den) - av_log2(അക്കം);
    എങ്കിൽ (shift >= 0) n = av_rescale(അക്കം, 1LL<<shift, den);
    അല്ലെങ്കിൽ            n = av_rescale(അക്കം, 1, den << -shift);

    shift -= n >= (1<<24);
    shift += n <  (1<<23);

    എങ്കിൽ (shift >= 0) n = av_rescale(അക്കം, 1LL<<shift, den);
    അല്ലെങ്കിൽ            n = av_rescale(അക്കം, 1, den << -shift);

    av_assert1(n <  (1<<24));
    av_assert1(n >= (1<<23));

    തിരികെ sign | (150-shift)<<23 | (n - (1<<23));
}

AVRational av_gcd_q(AVRational a, AVRational b, പൂർണ്ണസംഖ്യ max_den, AVRational def)
{
    int64_t gcd, lcm;

    gcd = av_gcd(a.den, b.den);
    lcm = (a.den / gcd) * b.den;
    തിരികെ lcm < max_den ? av_make_q(av_gcd(a.അക്കം, b.അക്കം), lcm) : def;
}
