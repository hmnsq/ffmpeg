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

#شامل "libavutil/rational.c"
#شامل "libavutil/integer.h"
#شامل "libavutil/intfloat.h"

ساکن صحیح check_q2intfloat(AVRational q)
{
    اعشاری f  = av_int2float(av_q2intfloat(q));
    اعشاری f2 = av_q2d(q);
    صحیح fail;

    اگر (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    ورنہ اگر (isinf(f) || isinf(f2))
        fail = f != f2;
    ورنہ
        fail = fabs(f - f2) > fabs(f)/5000000;
    اگر (fail)
        av_log(تہی, AV_LOG_ERROR, "%d/%d %f %f\n", q.عدد, q.den, f, f2);
    واپس fail;
}

صحیح مین(خالی)
{
    AVRational a,b,r;
    صحیح i,j,k;
    صحیح ret = 0;
    ساکن ثابت int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    برائے (a.عدد = -2; a.عدد <= 2; a.عدد++) {
        برائے (a.den = -2; a.den <= 2; a.den++) {
            برائے (b.عدد = -2; b.عدد <= 2; b.عدد++) {
                برائے (b.den = -2; b.den <= 2; b.den++) {
                    صحیح c = av_cmp_q(a,b);
                    دوہرا d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    اگر (d > 0)       d = 1;
                    ورنہ اگر (d < 0)  d = -1;
                    ورنہ اگر (d != d) d = INT_MIN;
                    اگر (c != d) {
                        av_log(تہی, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.عدد,
                               a.den, b.عدد, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_جوڑو_q(b,a), b);
                    اگر(b.den && (r.عدد*a.den != a.عدد*r.den || !r.عدد != !a.عدد || !r.den != !a.den)) {
                        av_log(تہی, AV_LOG_ERROR, "%d/%d ", r.عدد, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    ساکن ثابت AVRational unit_mul_q[][3] = {
        {{زیادہ_سے_زیادہ_عدد, 2},      { 2, 1},            { زیادہ_سے_زیادہ_عدد, 1}},
        {{زیادہ_سے_زیادہ_عدد, 2},      {-2, 1},            {-زیادہ_سے_زیادہ_عدد, 1}},
        {{زیادہ_سے_زیادہ_عدد, 2},      { 0, 1},            {0, 1}},
        {{INT_MIN, 2},      { 2, 1},            {-زیادہ_سے_زیادہ_عدد, 1}}, /* not INT_MIN */
        {{INT_MIN, 2},      {-2, 1},            { زیادہ_سے_زیادہ_عدد, 1}},
        {{INT_MIN, 2},      { 0, 1},            {0, 1}},
        {{زیادہ_سے_زیادہ_عدد >> 8, 1}, {زیادہ_سے_زیادہ_عدد >> 8, 1},  {زیادہ_سے_زیادہ_عدد, 1}},
        {{1, زیادہ_سے_زیادہ_عدد >> 8}, {1, زیادہ_سے_زیادہ_عدد >> 8},  {0, 1}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    برائے (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        برائے (صحیح c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            اگر (r.عدد != c.عدد || r.den != c.den) {
                av_log(تہی, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.عدد, a.den, b.عدد, b.den, r.عدد, r.den, c.عدد, c.den);
                ret = 1;
            }
        }
    }

    ساکن ثابت AVRational unit_جوڑو_q[][3] = {
        {{زیادہ_سے_زیادہ_عدد, 1},      { 2, 2},            { زیادہ_سے_زیادہ_عدد, 1}},
        {{زیادہ_سے_زیادہ_عدد, 1},      {-2, 2},            { زیادہ_سے_زیادہ_عدد - 1, 1}},
        {{زیادہ_سے_زیادہ_عدد, 1},      { 0, 2},            { زیادہ_سے_زیادہ_عدد, 1}},
        {{INT_MIN, 1},      { 2, 2},            {-زیادہ_سے_زیادہ_عدد, 1}},
        {{INT_MIN, 1},      {-2, 2},            {-زیادہ_سے_زیادہ_عدد, 1}},
        {{INT_MIN, 1},      { 0, 2},            {-زیادہ_سے_زیادہ_عدد, 1}},
        {{زیادہ_سے_زیادہ_عدد - 10, 1}, {20, 1},            { زیادہ_سے_زیادہ_عدد, 1}},
        {{2, زیادہ_سے_زیادہ_عدد},      {2, زیادہ_سے_زیادہ_عدد},       {4, زیادہ_سے_زیادہ_عدد}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    برائے (i = 0; i < FF_ARRAY_ELEMS(unit_جوڑو_q); i++) {
        برائے (صحیح c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_جوڑو_q[i][c ? 1 : 0];
            AVRational b = unit_جوڑو_q[i][c ? 0 : 1];
            AVRational c = unit_جوڑو_q[i][2];
            AVRational r = av_جوڑو_q(a, b);
            اگر (r.عدد != c.عدد || r.den != c.den) {
                av_log(تہی, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.عدد, a.den, b.عدد, b.den, r.عدد, r.den, c.عدد, c.den);
                ret = 1;
            }
        }
    }

    برائے (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        برائے (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            اگر (b<=0)
                جاری;
            برائے (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                اگر (c<=0)
                    جاری;
                res = av_rescale_rnd(a,b,c, AV_باری_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                اگر (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    جاری;
                اگر (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    جاری;
                اگر (av_cmp_i(ai, av_int2i(res)) == 0)
                    جاری;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                اگر (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    جاری;

                av_log(تہی, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    برائے (a.عدد = 1; a.عدد <= 10; a.عدد++) {
        برائے (a.den = 1; a.den <= 10; a.den++) {
            اگر (av_عاد_اعظم(a.عدد, a.den) > 1)
                جاری;
            برائے (b.عدد = 1; b.عدد <= 10; b.عدد++) {
                برائے (b.den = 1; b.den <= 10; b.den++) {
                    صحیح آغاز;
                    اگر (av_عاد_اعظم(b.عدد, b.den) > 1)
                        جاری;
                    اگر (av_cmp_q(b, a) < 0)
                        جاری;
                    برائے (آغاز = 0; آغاز < 10 ; آغاز++) {
                        صحیح acc= آغاز;
                        صحیح i;

                        برائے (i = 0; i<100; i++) {
                            صحیح exact = آغاز + av_rescale_q(i+1, b, a);
                            acc = av_جوڑو_stable(a, acc, b, 1);
                            اگر (FFABS(acc - exact) > 2) {
                                av_log(تہی, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.عدد,
                                       a.den, b.عدد, b.den, acc, exact);
                                واپس 1;
                            }
                        }
                    }
                }
            }
        }
    }

    برائے (int64_t den = 1; den <= زیادہ_سے_زیادہ_عدد; den *= 3) {
        a.den = den;
        برائے (a.عدد = -1; a.عدد < (1<<27); a.عدد += 1 + a.عدد/100) {
            اگر (check_q2intfloat(a))
                واپس 1;
        }
    }

    ساکن ثابت AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {زیادہ_سے_زیادہ_عدد, INT_MIN}, {INT_MIN, زیادہ_سے_زیادہ_عدد}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    برائے (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    واپس ret;
}
