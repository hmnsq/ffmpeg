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

#അന്തര്ഭാവ "libavutil/rational.c"
#അന്തര്ഭാവ "libavutil/integer.h"
#അന്തര്ഭാവ "libavutil/intfloat.h"

സ്ഥിതം പൂർണ്ണസംഖ്യ check_q2intfloat(AVRational q)
{
    ദശാംശം f  = av_int2float(av_q2intfloat(q));
    ദശാംശം f2 = av_q2d(q);
    പൂർണ്ണസംഖ്യ fail;

    എങ്കിൽ (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    അല്ലെങ്കിൽ എങ്കിൽ (isinf(f) || isinf(f2))
        fail = f != f2;
    അല്ലെങ്കിൽ
        fail = fabs(f - f2) > fabs(f)/5000000;
    എങ്കിൽ (fail)
        av_log(ശൂന്യ, AV_LOG_ERROR, "%d/%d %f %f\n", q.അക്കം, q.den, f, f2);
    തിരികെ fail;
}

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    AVRational a,b,r;
    പൂർണ്ണസംഖ്യ i,j,k;
    പൂർണ്ണസംഖ്യ ret = 0;
    സ്ഥിതം സ്ഥിരം int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    വേണ്ടി (a.അക്കം = -2; a.അക്കം <= 2; a.അക്കം++) {
        വേണ്ടി (a.den = -2; a.den <= 2; a.den++) {
            വേണ്ടി (b.അക്കം = -2; b.അക്കം <= 2; b.അക്കം++) {
                വേണ്ടി (b.den = -2; b.den <= 2; b.den++) {
                    പൂർണ്ണസംഖ്യ c = av_cmp_q(a,b);
                    ഇരട്ട d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    എങ്കിൽ (d > 0)       d = 1;
                    അല്ലെങ്കിൽ എങ്കിൽ (d < 0)  d = -1;
                    അല്ലെങ്കിൽ എങ്കിൽ (d != d) d = INT_MIN;
                    എങ്കിൽ (c != d) {
                        av_log(ശൂന്യ, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.അക്കം,
                               a.den, b.അക്കം, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_add_q(b,a), b);
                    എങ്കിൽ(b.den && (r.അക്കം*a.den != a.അക്കം*r.den || !r.അക്കം != !a.അക്കം || !r.den != !a.den)) {
                        av_log(ശൂന്യ, AV_LOG_ERROR, "%d/%d ", r.അക്കം, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    സ്ഥിതം സ്ഥിരം AVRational unit_mul_q[][3] = {
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

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            എങ്കിൽ (r.അക്കം != c.അക്കം || r.den != c.den) {
                av_log(ശൂന്യ, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.അക്കം, a.den, b.അക്കം, b.den, r.അക്കം, r.den, c.അക്കം, c.den);
                ret = 1;
            }
        }
    }

    സ്ഥിതം സ്ഥിരം AVRational unit_add_q[][3] = {
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

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(unit_add_q); i++) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_add_q[i][c ? 1 : 0];
            AVRational b = unit_add_q[i][c ? 0 : 1];
            AVRational c = unit_add_q[i][2];
            AVRational r = av_add_q(a, b);
            എങ്കിൽ (r.അക്കം != c.അക്കം || r.den != c.den) {
                av_log(ശൂന്യ, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.അക്കം, a.den, b.അക്കം, b.den, r.അക്കം, r.den, c.അക്കം, c.den);
                ret = 1;
            }
        }
    }

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        വേണ്ടി (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            എങ്കിൽ (b<=0)
                തുടരുക;
            വേണ്ടി (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                എങ്കിൽ (c<=0)
                    തുടരുക;
                res = av_rescale_rnd(a,b,c, AV_ROUND_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                എങ്കിൽ (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    തുടരുക;
                എങ്കിൽ (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    തുടരുക;
                എങ്കിൽ (av_cmp_i(ai, av_int2i(res)) == 0)
                    തുടരുക;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                എങ്കിൽ (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    തുടരുക;

                av_log(ശൂന്യ, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    വേണ്ടി (a.അക്കം = 1; a.അക്കം <= 10; a.അക്കം++) {
        വേണ്ടി (a.den = 1; a.den <= 10; a.den++) {
            എങ്കിൽ (av_gcd(a.അക്കം, a.den) > 1)
                തുടരുക;
            വേണ്ടി (b.അക്കം = 1; b.അക്കം <= 10; b.അക്കം++) {
                വേണ്ടി (b.den = 1; b.den <= 10; b.den++) {
                    പൂർണ്ണസംഖ്യ start;
                    എങ്കിൽ (av_gcd(b.അക്കം, b.den) > 1)
                        തുടരുക;
                    എങ്കിൽ (av_cmp_q(b, a) < 0)
                        തുടരുക;
                    വേണ്ടി (start = 0; start < 10 ; start++) {
                        പൂർണ്ണസംഖ്യ acc= start;
                        പൂർണ്ണസംഖ്യ i;

                        വേണ്ടി (i = 0; i<100; i++) {
                            പൂർണ്ണസംഖ്യ exact = start + av_rescale_q(i+1, b, a);
                            acc = av_add_stable(a, acc, b, 1);
                            എങ്കിൽ (FFABS(acc - exact) > 2) {
                                av_log(ശൂന്യ, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.അക്കം,
                                       a.den, b.അക്കം, b.den, acc, exact);
                                തിരികെ 1;
                            }
                        }
                    }
                }
            }
        }
    }

    വേണ്ടി (int64_t den = 1; den <= INT_MAX; den *= 3) {
        a.den = den;
        വേണ്ടി (a.അക്കം = -1; a.അക്കം < (1<<27); a.അക്കം += 1 + a.അക്കം/100) {
            എങ്കിൽ (check_q2intfloat(a))
                തിരികെ 1;
        }
    }

    സ്ഥിതം സ്ഥിരം AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {INT_MAX, INT_MIN}, {INT_MIN, INT_MAX}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    തിരികെ ret;
}
