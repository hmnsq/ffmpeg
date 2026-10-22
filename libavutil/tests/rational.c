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

ایستا صحیح check_q2intfloat(AVRational q)
{
    اعشاری f  = av_int2float(av_q2intfloat(q));
    اعشاری f2 = av_q2d(q);
    صحیح fail;

    اگر (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    وگرنه اگر (isinf(f) || isinf(f2))
        fail = f != f2;
    وگرنه
        fail = fabs(f - f2) > fabs(f)/5000000;
    اگر (fail)
        av_log(پوچ, AV_LOG_ERROR, "%d/%d %f %f\n", q.رقم, q.den, f, f2);
    بازگشت fail;
}

صحیح اصلی(تهی)
{
    AVRational a,b,r;
    صحیح i,j,k;
    صحیح ret = 0;
    ایستا ثابت int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    برای (a.رقم = -2; a.رقم <= 2; a.رقم++) {
        برای (a.den = -2; a.den <= 2; a.den++) {
            برای (b.رقم = -2; b.رقم <= 2; b.رقم++) {
                برای (b.den = -2; b.den <= 2; b.den++) {
                    صحیح c = av_cmp_q(a,b);
                    دوگانه d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    اگر (d > 0)       d = 1;
                    وگرنه اگر (d < 0)  d = -1;
                    وگرنه اگر (d != d) d = INT_MIN;
                    اگر (c != d) {
                        av_log(پوچ, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.رقم,
                               a.den, b.رقم, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_add_q(b,a), b);
                    اگر(b.den && (r.رقم*a.den != a.رقم*r.den || !r.رقم != !a.رقم || !r.den != !a.den)) {
                        av_log(پوچ, AV_LOG_ERROR, "%d/%d ", r.رقم, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    ایستا ثابت AVRational unit_mul_q[][3] = {
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

    برای (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        برای (صحیح c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            اگر (r.رقم != c.رقم || r.den != c.den) {
                av_log(پوچ, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.رقم, a.den, b.رقم, b.den, r.رقم, r.den, c.رقم, c.den);
                ret = 1;
            }
        }
    }

    ایستا ثابت AVRational unit_add_q[][3] = {
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

    برای (i = 0; i < FF_ARRAY_ELEMS(unit_add_q); i++) {
        برای (صحیح c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_add_q[i][c ? 1 : 0];
            AVRational b = unit_add_q[i][c ? 0 : 1];
            AVRational c = unit_add_q[i][2];
            AVRational r = av_add_q(a, b);
            اگر (r.رقم != c.رقم || r.den != c.den) {
                av_log(پوچ, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.رقم, a.den, b.رقم, b.den, r.رقم, r.den, c.رقم, c.den);
                ret = 1;
            }
        }
    }

    برای (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        برای (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            اگر (b<=0)
                ادامه;
            برای (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                اگر (c<=0)
                    ادامه;
                res = av_rescale_rnd(a,b,c, AV_ROUND_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                اگر (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    ادامه;
                اگر (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    ادامه;
                اگر (av_cmp_i(ai, av_int2i(res)) == 0)
                    ادامه;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                اگر (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    ادامه;

                av_log(پوچ, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    برای (a.رقم = 1; a.رقم <= 10; a.رقم++) {
        برای (a.den = 1; a.den <= 10; a.den++) {
            اگر (av_gcd(a.رقم, a.den) > 1)
                ادامه;
            برای (b.رقم = 1; b.رقم <= 10; b.رقم++) {
                برای (b.den = 1; b.den <= 10; b.den++) {
                    صحیح start;
                    اگر (av_gcd(b.رقم, b.den) > 1)
                        ادامه;
                    اگر (av_cmp_q(b, a) < 0)
                        ادامه;
                    برای (start = 0; start < 10 ; start++) {
                        صحیح acc= start;
                        صحیح i;

                        برای (i = 0; i<100; i++) {
                            صحیح exact = start + av_rescale_q(i+1, b, a);
                            acc = av_add_stable(a, acc, b, 1);
                            اگر (FFABS(acc - exact) > 2) {
                                av_log(پوچ, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.رقم,
                                       a.den, b.رقم, b.den, acc, exact);
                                بازگشت 1;
                            }
                        }
                    }
                }
            }
        }
    }

    برای (int64_t den = 1; den <= INT_MAX; den *= 3) {
        a.den = den;
        برای (a.رقم = -1; a.رقم < (1<<27); a.رقم += 1 + a.رقم/100) {
            اگر (check_q2intfloat(a))
                بازگشت 1;
        }
    }

    ایستا ثابت AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {INT_MAX, INT_MIN}, {INT_MIN, INT_MAX}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    برای (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    بازگشت ret;
}
