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

#অন্তর্ভাব "libavutil/rational.c"
#অন্তর্ভাব "libavutil/integer.h"
#অন্তর্ভাব "libavutil/intfloat.h"

স্থির পূর্ণসংখ্যা check_q2intfloat(AVRational q)
{
    দশমিক f  = av_int2float(av_q2intfloat(q));
    দশমিক f2 = av_q2d(q);
    পূর্ণসংখ্যা fail;

    যদি (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    অন্যথা যদি (isinf(f) || isinf(f2))
        fail = f != f2;
    অন্যথা
        fail = fabs(f - f2) > fabs(f)/5000000;
    যদি (fail)
        av_log(ফাঁকা, AV_LOG_ERROR, "%d/%d %f %f\n", q.অঙ্ক, q.den, f, f2);
    ফেরত fail;
}

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    AVRational a,b,r;
    পূর্ণসংখ্যা i,j,k;
    পূর্ণসংখ্যা ret = 0;
    স্থির ধ্রুবক int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    জন্য (a.অঙ্ক = -2; a.অঙ্ক <= 2; a.অঙ্ক++) {
        জন্য (a.den = -2; a.den <= 2; a.den++) {
            জন্য (b.অঙ্ক = -2; b.অঙ্ক <= 2; b.অঙ্ক++) {
                জন্য (b.den = -2; b.den <= 2; b.den++) {
                    পূর্ণসংখ্যা c = av_cmp_q(a,b);
                    দ্বিগুণ d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    যদি (d > 0)       d = 1;
                    অন্যথা যদি (d < 0)  d = -1;
                    অন্যথা যদি (d != d) d = INT_MIN;
                    যদি (c != d) {
                        av_log(ফাঁকা, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.অঙ্ক,
                               a.den, b.অঙ্ক, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_add_q(b,a), b);
                    যদি(b.den && (r.অঙ্ক*a.den != a.অঙ্ক*r.den || !r.অঙ্ক != !a.অঙ্ক || !r.den != !a.den)) {
                        av_log(ফাঁকা, AV_LOG_ERROR, "%d/%d ", r.অঙ্ক, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    স্থির ধ্রুবক AVRational unit_mul_q[][3] = {
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

    জন্য (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        জন্য (পূর্ণসংখ্যা c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            যদি (r.অঙ্ক != c.অঙ্ক || r.den != c.den) {
                av_log(ফাঁকা, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.অঙ্ক, a.den, b.অঙ্ক, b.den, r.অঙ্ক, r.den, c.অঙ্ক, c.den);
                ret = 1;
            }
        }
    }

    স্থির ধ্রুবক AVRational unit_add_q[][3] = {
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

    জন্য (i = 0; i < FF_ARRAY_ELEMS(unit_add_q); i++) {
        জন্য (পূর্ণসংখ্যা c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_add_q[i][c ? 1 : 0];
            AVRational b = unit_add_q[i][c ? 0 : 1];
            AVRational c = unit_add_q[i][2];
            AVRational r = av_add_q(a, b);
            যদি (r.অঙ্ক != c.অঙ্ক || r.den != c.den) {
                av_log(ফাঁকা, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.অঙ্ক, a.den, b.অঙ্ক, b.den, r.অঙ্ক, r.den, c.অঙ্ক, c.den);
                ret = 1;
            }
        }
    }

    জন্য (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        জন্য (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            যদি (b<=0)
                চালু;
            জন্য (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                যদি (c<=0)
                    চালু;
                res = av_rescale_rnd(a,b,c, AV_ROUND_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                যদি (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    চালু;
                যদি (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    চালু;
                যদি (av_cmp_i(ai, av_int2i(res)) == 0)
                    চালু;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                যদি (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    চালু;

                av_log(ফাঁকা, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    জন্য (a.অঙ্ক = 1; a.অঙ্ক <= 10; a.অঙ্ক++) {
        জন্য (a.den = 1; a.den <= 10; a.den++) {
            যদি (av_gcd(a.অঙ্ক, a.den) > 1)
                চালু;
            জন্য (b.অঙ্ক = 1; b.অঙ্ক <= 10; b.অঙ্ক++) {
                জন্য (b.den = 1; b.den <= 10; b.den++) {
                    পূর্ণসংখ্যা start;
                    যদি (av_gcd(b.অঙ্ক, b.den) > 1)
                        চালু;
                    যদি (av_cmp_q(b, a) < 0)
                        চালু;
                    জন্য (start = 0; start < 10 ; start++) {
                        পূর্ণসংখ্যা acc= start;
                        পূর্ণসংখ্যা i;

                        জন্য (i = 0; i<100; i++) {
                            পূর্ণসংখ্যা exact = start + av_rescale_q(i+1, b, a);
                            acc = av_add_stable(a, acc, b, 1);
                            যদি (FFABS(acc - exact) > 2) {
                                av_log(ফাঁকা, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.অঙ্ক,
                                       a.den, b.অঙ্ক, b.den, acc, exact);
                                ফেরত 1;
                            }
                        }
                    }
                }
            }
        }
    }

    জন্য (int64_t den = 1; den <= INT_MAX; den *= 3) {
        a.den = den;
        জন্য (a.অঙ্ক = -1; a.অঙ্ক < (1<<27); a.অঙ্ক += 1 + a.অঙ্ক/100) {
            যদি (check_q2intfloat(a))
                ফেরত 1;
        }
    }

    স্থির ধ্রুবক AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {INT_MAX, INT_MIN}, {INT_MIN, INT_MAX}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    জন্য (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    ফেরত ret;
}
