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

#ضمن "libavutil/rational.c"
#ضمن "libavutil/integer.h"
#ضمن "libavutil/intfloat.h"

ساكن صحيح check_q2intfloat(AVRational q)
{
    عائم f  = av_int2float(av_q2intfloat(q));
    عائم f2 = av_q2d(q);
    صحيح fail;

    إذا (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    وإلا إذا (isinf(f) || isinf(f2))
        fail = f != f2;
    وإلا
        fail = fabs(f - f2) > fabs(f)/5000000;
    إذا (fail)
        av_log(عدم, AV_LOG_ERROR, "%d/%d %f %f\n", q.عدد, q.den, f, f2);
    أرجع fail;
}

صحيح اصلي(فراغ)
{
    AVRational a,b,r;
    صحيح i,j,k;
    صحيح ret = 0;
    ساكن ثابت int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    لكل (a.عدد = -2; a.عدد <= 2; a.عدد++) {
        لكل (a.den = -2; a.den <= 2; a.den++) {
            لكل (b.عدد = -2; b.عدد <= 2; b.عدد++) {
                لكل (b.den = -2; b.den <= 2; b.den++) {
                    صحيح c = av_cmp_q(a,b);
                    مزدوج d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    إذا (d > 0)       d = 1;
                    وإلا إذا (d < 0)  d = -1;
                    وإلا إذا (d != d) d = INT_MIN;
                    إذا (c != d) {
                        av_log(عدم, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.عدد,
                               a.den, b.عدد, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_جمع_کړه_q(b,a), b);
                    إذا(b.den && (r.عدد*a.den != a.عدد*r.den || !r.عدد != !a.عدد || !r.den != !a.den)) {
                        av_log(عدم, AV_LOG_ERROR, "%d/%d ", r.عدد, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    ساكن ثابت AVRational unit_mul_q[][3] = {
        {{لوی_عدد, 2},      { 2, 1},            { لوی_عدد, 1}},
        {{لوی_عدد, 2},      {-2, 1},            {-لوی_عدد, 1}},
        {{لوی_عدد, 2},      { 0, 1},            {0, 1}},
        {{INT_MIN, 2},      { 2, 1},            {-لوی_عدد, 1}}, /* not INT_MIN */
        {{INT_MIN, 2},      {-2, 1},            { لوی_عدد, 1}},
        {{INT_MIN, 2},      { 0, 1},            {0, 1}},
        {{لوی_عدد >> 8, 1}, {لوی_عدد >> 8, 1},  {لوی_عدد, 1}},
        {{1, لوی_عدد >> 8}, {1, لوی_عدد >> 8},  {0, 1}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    لكل (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        لكل (صحيح c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            إذا (r.عدد != c.عدد || r.den != c.den) {
                av_log(عدم, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.عدد, a.den, b.عدد, b.den, r.عدد, r.den, c.عدد, c.den);
                ret = 1;
            }
        }
    }

    ساكن ثابت AVRational unit_جمع_کړه_q[][3] = {
        {{لوی_عدد, 1},      { 2, 2},            { لوی_عدد, 1}},
        {{لوی_عدد, 1},      {-2, 2},            { لوی_عدد - 1, 1}},
        {{لوی_عدد, 1},      { 0, 2},            { لوی_عدد, 1}},
        {{INT_MIN, 1},      { 2, 2},            {-لوی_عدد, 1}},
        {{INT_MIN, 1},      {-2, 2},            {-لوی_عدد, 1}},
        {{INT_MIN, 1},      { 0, 2},            {-لوی_عدد, 1}},
        {{لوی_عدد - 10, 1}, {20, 1},            { لوی_عدد, 1}},
        {{2, لوی_عدد},      {2, لوی_عدد},       {4, لوی_عدد}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    لكل (i = 0; i < FF_ARRAY_ELEMS(unit_جمع_کړه_q); i++) {
        لكل (صحيح c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_جمع_کړه_q[i][c ? 1 : 0];
            AVRational b = unit_جمع_کړه_q[i][c ? 0 : 1];
            AVRational c = unit_جمع_کړه_q[i][2];
            AVRational r = av_جمع_کړه_q(a, b);
            إذا (r.عدد != c.عدد || r.den != c.den) {
                av_log(عدم, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.عدد, a.den, b.عدد, b.den, r.عدد, r.den, c.عدد, c.den);
                ret = 1;
            }
        }
    }

    لكل (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        لكل (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            إذا (b<=0)
                استمر;
            لكل (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                إذا (c<=0)
                    استمر;
                res = av_rescale_rnd(a,b,c, AV_پړاو_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                إذا (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    استمر;
                إذا (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    استمر;
                إذا (av_cmp_i(ai, av_int2i(res)) == 0)
                    استمر;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                إذا (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    استمر;

                av_log(عدم, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    لكل (a.عدد = 1; a.عدد <= 10; a.عدد++) {
        لكل (a.den = 1; a.den <= 10; a.den++) {
            إذا (av_لوی_ګډ_وېشونکی(a.عدد, a.den) > 1)
                استمر;
            لكل (b.عدد = 1; b.عدد <= 10; b.عدد++) {
                لكل (b.den = 1; b.den <= 10; b.den++) {
                    صحيح پیل;
                    إذا (av_لوی_ګډ_وېشونکی(b.عدد, b.den) > 1)
                        استمر;
                    إذا (av_cmp_q(b, a) < 0)
                        استمر;
                    لكل (پیل = 0; پیل < 10 ; پیل++) {
                        صحيح acc= پیل;
                        صحيح i;

                        لكل (i = 0; i<100; i++) {
                            صحيح exact = پیل + av_rescale_q(i+1, b, a);
                            acc = av_جمع_کړه_stable(a, acc, b, 1);
                            إذا (FFABS(acc - exact) > 2) {
                                av_log(عدم, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.عدد,
                                       a.den, b.عدد, b.den, acc, exact);
                                أرجع 1;
                            }
                        }
                    }
                }
            }
        }
    }

    لكل (int64_t den = 1; den <= لوی_عدد; den *= 3) {
        a.den = den;
        لكل (a.عدد = -1; a.عدد < (1<<27); a.عدد += 1 + a.عدد/100) {
            إذا (check_q2intfloat(a))
                أرجع 1;
        }
    }

    ساكن ثابت AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {لوی_عدد, INT_MIN}, {INT_MIN, لوی_عدد}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    لكل (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    أرجع ret;
}
