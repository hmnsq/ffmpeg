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

#અન્તર્ભાવ "libavutil/rational.c"
#અન્તર્ભાવ "libavutil/integer.h"
#અન્તર્ભાવ "libavutil/intfloat.h"

સ્થિર પૂર્ણાંક check_q2intfloat(AVRational q)
{
    દશાંશ f  = av_int2float(av_q2intfloat(q));
    દશાંશ f2 = av_q2d(q);
    પૂર્ણાંક fail;

    જો (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    નહીંતર જો (isinf(f) || isinf(f2))
        fail = f != f2;
    નહીંતર
        fail = fabs(f - f2) > fabs(f)/5000000;
    જો (fail)
        av_log(ખાલી, AV_LOG_ERROR, "%d/%d %f %f\n", q.અંક, q.den, f, f2);
    પાછા fail;
}

પૂર્ણાંક મુખ્ય(શૂન્ય)
{
    AVRational a,b,r;
    પૂર્ણાંક i,j,k;
    પૂર્ણાંક ret = 0;
    સ્થિર અચલ int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    માટે (a.અંક = -2; a.અંક <= 2; a.અંક++) {
        માટે (a.den = -2; a.den <= 2; a.den++) {
            માટે (b.અંક = -2; b.અંક <= 2; b.અંક++) {
                માટે (b.den = -2; b.den <= 2; b.den++) {
                    પૂર્ણાંક c = av_cmp_q(a,b);
                    દ્વિગુણ d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    જો (d > 0)       d = 1;
                    નહીંતર જો (d < 0)  d = -1;
                    નહીંતર જો (d != d) d = INT_MIN;
                    જો (c != d) {
                        av_log(ખાલી, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.અંક,
                               a.den, b.અંક, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_add_q(b,a), b);
                    જો(b.den && (r.અંક*a.den != a.અંક*r.den || !r.અંક != !a.અંક || !r.den != !a.den)) {
                        av_log(ખાલી, AV_LOG_ERROR, "%d/%d ", r.અંક, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    સ્થિર અચલ AVRational unit_mul_q[][3] = {
        {{INT_MAX, 2},      { 2, 1},            { INT_MAX, 1}},
        {{INT_MAX, 2},      {-2, 1},            {-INT_MAX, 1}},
        {{INT_MAX, 2},      { 0, 1},            {0, 1}},
        {{INT_MIN, 2},      { 2, 1},            {-INT_MAX, 1}}, /* not INT_MIN */
        {{INT_MIN, 2},      {-2, 1},            { INT_MAX, 1}},
        {{INT_MIN, 2},      { 0, 1},            {0, 1}},
        {{INT_MAX >> 8, 1}, {INT_MAX >> 8, 1},  {INT_MAX, 1}},
        {{1, INT_MAX >> 8}, {1, INT_MAX >> 8},  {0, 1}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    માટે (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        માટે (પૂર્ણાંક c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            જો (r.અંક != c.અંક || r.den != c.den) {
                av_log(ખાલી, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.અંક, a.den, b.અંક, b.den, r.અંક, r.den, c.અંક, c.den);
                ret = 1;
            }
        }
    }

    સ્થિર અચલ AVRational unit_add_q[][3] = {
        {{INT_MAX, 1},      { 2, 2},            { INT_MAX, 1}},
        {{INT_MAX, 1},      {-2, 2},            { INT_MAX - 1, 1}},
        {{INT_MAX, 1},      { 0, 2},            { INT_MAX, 1}},
        {{INT_MIN, 1},      { 2, 2},            {-INT_MAX, 1}},
        {{INT_MIN, 1},      {-2, 2},            {-INT_MAX, 1}},
        {{INT_MIN, 1},      { 0, 2},            {-INT_MAX, 1}},
        {{INT_MAX - 10, 1}, {20, 1},            { INT_MAX, 1}},
        {{2, INT_MAX},      {2, INT_MAX},       {4, INT_MAX}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    માટે (i = 0; i < FF_ARRAY_ELEMS(unit_add_q); i++) {
        માટે (પૂર્ણાંક c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_add_q[i][c ? 1 : 0];
            AVRational b = unit_add_q[i][c ? 0 : 1];
            AVRational c = unit_add_q[i][2];
            AVRational r = av_add_q(a, b);
            જો (r.અંક != c.અંક || r.den != c.den) {
                av_log(ખાલી, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.અંક, a.den, b.અંક, b.den, r.અંક, r.den, c.અંક, c.den);
                ret = 1;
            }
        }
    }

    માટે (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        માટે (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            જો (b<=0)
                ચાલુ;
            માટે (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                જો (c<=0)
                    ચાલુ;
                res = av_rescale_rnd(a,b,c, AV_ROUND_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                જો (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    ચાલુ;
                જો (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    ચાલુ;
                જો (av_cmp_i(ai, av_int2i(res)) == 0)
                    ચાલુ;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                જો (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    ચાલુ;

                av_log(ખાલી, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    માટે (a.અંક = 1; a.અંક <= 10; a.અંક++) {
        માટે (a.den = 1; a.den <= 10; a.den++) {
            જો (av_gcd(a.અંક, a.den) > 1)
                ચાલુ;
            માટે (b.અંક = 1; b.અંક <= 10; b.અંક++) {
                માટે (b.den = 1; b.den <= 10; b.den++) {
                    પૂર્ણાંક start;
                    જો (av_gcd(b.અંક, b.den) > 1)
                        ચાલુ;
                    જો (av_cmp_q(b, a) < 0)
                        ચાલુ;
                    માટે (start = 0; start < 10 ; start++) {
                        પૂર્ણાંક acc= start;
                        પૂર્ણાંક i;

                        માટે (i = 0; i<100; i++) {
                            પૂર્ણાંક exact = start + av_rescale_q(i+1, b, a);
                            acc = av_add_stable(a, acc, b, 1);
                            જો (FFABS(acc - exact) > 2) {
                                av_log(ખાલી, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.અંક,
                                       a.den, b.અંક, b.den, acc, exact);
                                પાછા 1;
                            }
                        }
                    }
                }
            }
        }
    }

    માટે (int64_t den = 1; den <= INT_MAX; den *= 3) {
        a.den = den;
        માટે (a.અંક = -1; a.અંક < (1<<27); a.અંક += 1 + a.અંક/100) {
            જો (check_q2intfloat(a))
                પાછા 1;
        }
    }

    સ્થિર અચલ AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {INT_MAX, INT_MIN}, {INT_MIN, INT_MAX}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    માટે (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    પાછા ret;
}
