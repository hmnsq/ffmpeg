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

#include "libavutil/rational.c"
#include "libavutil/integer.h"
#include "libavutil/intfloat.h"

static ཧྲིལ check_q2intfloat(AVRational q)
{
    float f  = av_int2float(av_q2intfloat(q));
    float f2 = av_q2d(q);
    ཧྲིལ fail;

    གལ་ཏེ (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    དེ་མིན གལ་ཏེ (isinf(f) || isinf(f2))
        fail = f != f2;
    དེ་མིན
        fail = fabs(f - f2) > fabs(f)/5000000;
    གལ་ཏེ (fail)
        av_log(NULL, AV_LOG_ERROR, "%d/%d %f %f\n", q.num, q.den, f, f2);
    ཕྱིར fail;
}

ཧྲིལ གཙོ(void)
{
    AVRational a,b,r;
    ཧྲིལ i,j,k;
    ཧྲིལ ret = 0;
    static const int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    ཆེད་དུ (a.num = -2; a.num <= 2; a.num++) {
        ཆེད་དུ (a.den = -2; a.den <= 2; a.den++) {
            ཆེད་དུ (b.num = -2; b.num <= 2; b.num++) {
                ཆེད་དུ (b.den = -2; b.den <= 2; b.den++) {
                    ཧྲིལ c = av_cmp_q(a,b);
                    dviguu_na d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    གལ་ཏེ (d > 0)       d = 1;
                    དེ་མིན གལ་ཏེ (d < 0)  d = -1;
                    དེ་མིན གལ་ཏེ (d != d) d = INT_MIN;
                    གལ་ཏེ (c != d) {
                        av_log(NULL, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.num,
                               a.den, b.num, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_add_q(b,a), b);
                    གལ་ཏེ(b.den && (r.num*a.den != a.num*r.den || !r.num != !a.num || !r.den != !a.den)) {
                        av_log(NULL, AV_LOG_ERROR, "%d/%d ", r.num, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    static const AVRational unit_mul_q[][3] = {
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

    ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        ཆེད་དུ (ཧྲིལ c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            གལ་ཏེ (r.num != c.num || r.den != c.den) {
                av_log(NULL, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.num, a.den, b.num, b.den, r.num, r.den, c.num, c.den);
                ret = 1;
            }
        }
    }

    static const AVRational unit_add_q[][3] = {
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

    ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(unit_add_q); i++) {
        ཆེད་དུ (ཧྲིལ c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_add_q[i][c ? 1 : 0];
            AVRational b = unit_add_q[i][c ? 0 : 1];
            AVRational c = unit_add_q[i][2];
            AVRational r = av_add_q(a, b);
            གལ་ཏེ (r.num != c.num || r.den != c.den) {
                av_log(NULL, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.num, a.den, b.num, b.den, r.num, r.den, c.num, c.den);
                ret = 1;
            }
        }
    }

    ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        ཆེད་དུ (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            གལ་ཏེ (b<=0)
                continue;
            ཆེད་དུ (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                གལ་ཏེ (c<=0)
                    continue;
                res = av_rescale_rnd(a,b,c, AV_ROUND_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                གལ་ཏེ (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    continue;
                གལ་ཏེ (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    continue;
                གལ་ཏེ (av_cmp_i(ai, av_int2i(res)) == 0)
                    continue;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                གལ་ཏེ (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    continue;

                av_log(NULL, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    ཆེད་དུ (a.num = 1; a.num <= 10; a.num++) {
        ཆེད་དུ (a.den = 1; a.den <= 10; a.den++) {
            གལ་ཏེ (av_gcd(a.num, a.den) > 1)
                continue;
            ཆེད་དུ (b.num = 1; b.num <= 10; b.num++) {
                ཆེད་དུ (b.den = 1; b.den <= 10; b.den++) {
                    ཧྲིལ start;
                    གལ་ཏེ (av_gcd(b.num, b.den) > 1)
                        continue;
                    གལ་ཏེ (av_cmp_q(b, a) < 0)
                        continue;
                    ཆེད་དུ (start = 0; start < 10 ; start++) {
                        ཧྲིལ acc= start;
                        ཧྲིལ i;

                        ཆེད་དུ (i = 0; i<100; i++) {
                            ཧྲིལ exact = start + av_rescale_q(i+1, b, a);
                            acc = av_add_stable(a, acc, b, 1);
                            གལ་ཏེ (FFABS(acc - exact) > 2) {
                                av_log(NULL, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.num,
                                       a.den, b.num, b.den, acc, exact);
                                ཕྱིར 1;
                            }
                        }
                    }
                }
            }
        }
    }

    ཆེད་དུ (int64_t den = 1; den <= INT_MAX; den *= 3) {
        a.den = den;
        ཆེད་དུ (a.num = -1; a.num < (1<<27); a.num += 1 + a.num/100) {
            གལ་ཏེ (check_q2intfloat(a))
                ཕྱིར 1;
        }
    }

    static const AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {INT_MAX, INT_MIN}, {INT_MIN, INT_MAX}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    ཕྱིར ret;
}
