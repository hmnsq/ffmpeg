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

#ଅନ୍ତର୍ଭାଵ "libavutil/rational.c"
#ଅନ୍ତର୍ଭାଵ "libavutil/integer.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/intfloat.h"

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା check_q2intfloat(AVRational q)
{
    ଦଶମିକ f  = av_int2float(av_q2intfloat(q));
    ଦଶମିକ f2 = av_q2d(q);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା fail;

    ଯଦି (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    ଅନ୍ୟଥା ଯଦି (isinf(f) || isinf(f2))
        fail = f != f2;
    ଅନ୍ୟଥା
        fail = fabs(f - f2) > fabs(f)/5000000;
    ଯଦି (fail)
        av_log(ଖାଲି, AV_LOG_ERROR, "%d/%d %f %f\n", q.ଅଙ୍କ, q.den, f, f2);
    ଫେରନ୍ତୁ fail;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ଶୂନ୍ୟ)
{
    AVRational a,b,r;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i,j,k;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;
    ସ୍ଥିର ଅଚଳ int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    ପାଇଁ (a.ଅଙ୍କ = -2; a.ଅଙ୍କ <= 2; a.ଅଙ୍କ++) {
        ପାଇଁ (a.den = -2; a.den <= 2; a.den++) {
            ପାଇଁ (b.ଅଙ୍କ = -2; b.ଅଙ୍କ <= 2; b.ଅଙ୍କ++) {
                ପାଇଁ (b.den = -2; b.den <= 2; b.den++) {
                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = av_cmp_q(a,b);
                    ଦ୍ୱିଗୁଣ d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    ଯଦି (d > 0)       d = 1;
                    ଅନ୍ୟଥା ଯଦି (d < 0)  d = -1;
                    ଅନ୍ୟଥା ଯଦି (d != d) d = INT_MIN;
                    ଯଦି (c != d) {
                        av_log(ଖାଲି, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.ଅଙ୍କ,
                               a.den, b.ଅଙ୍କ, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_add_q(b,a), b);
                    ଯଦି(b.den && (r.ଅଙ୍କ*a.den != a.ଅଙ୍କ*r.den || !r.ଅଙ୍କ != !a.ଅଙ୍କ || !r.den != !a.den)) {
                        av_log(ଖାଲି, AV_LOG_ERROR, "%d/%d ", r.ଅଙ୍କ, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    ସ୍ଥିର ଅଚଳ AVRational unit_mul_q[][3] = {
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

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            ଯଦି (r.ଅଙ୍କ != c.ଅଙ୍କ || r.den != c.den) {
                av_log(ଖାଲି, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.ଅଙ୍କ, a.den, b.ଅଙ୍କ, b.den, r.ଅଙ୍କ, r.den, c.ଅଙ୍କ, c.den);
                ret = 1;
            }
        }
    }

    ସ୍ଥିର ଅଚଳ AVRational unit_add_q[][3] = {
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

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(unit_add_q); i++) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_add_q[i][c ? 1 : 0];
            AVRational b = unit_add_q[i][c ? 0 : 1];
            AVRational c = unit_add_q[i][2];
            AVRational r = av_add_q(a, b);
            ଯଦି (r.ଅଙ୍କ != c.ଅଙ୍କ || r.den != c.den) {
                av_log(ଖାଲି, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.ଅଙ୍କ, a.den, b.ଅଙ୍କ, b.den, r.ଅଙ୍କ, r.den, c.ଅଙ୍କ, c.den);
                ret = 1;
            }
        }
    }

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        ପାଇଁ (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            ଯଦି (b<=0)
                ଜାରି;
            ପାଇଁ (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                ଯଦି (c<=0)
                    ଜାରି;
                res = av_rescale_rnd(a,b,c, AV_ROUND_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                ଯଦି (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    ଜାରି;
                ଯଦି (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    ଜାରି;
                ଯଦି (av_cmp_i(ai, av_int2i(res)) == 0)
                    ଜାରି;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                ଯଦି (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    ଜାରି;

                av_log(ଖାଲି, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    ପାଇଁ (a.ଅଙ୍କ = 1; a.ଅଙ୍କ <= 10; a.ଅଙ୍କ++) {
        ପାଇଁ (a.den = 1; a.den <= 10; a.den++) {
            ଯଦି (av_gcd(a.ଅଙ୍କ, a.den) > 1)
                ଜାରି;
            ପାଇଁ (b.ଅଙ୍କ = 1; b.ଅଙ୍କ <= 10; b.ଅଙ୍କ++) {
                ପାଇଁ (b.den = 1; b.den <= 10; b.den++) {
                    ପୂର୍ଣ୍ଣସଂଖ୍ୟା start;
                    ଯଦି (av_gcd(b.ଅଙ୍କ, b.den) > 1)
                        ଜାରି;
                    ଯଦି (av_cmp_q(b, a) < 0)
                        ଜାରି;
                    ପାଇଁ (start = 0; start < 10 ; start++) {
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା acc= start;
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

                        ପାଇଁ (i = 0; i<100; i++) {
                            ପୂର୍ଣ୍ଣସଂଖ୍ୟା exact = start + av_rescale_q(i+1, b, a);
                            acc = av_add_stable(a, acc, b, 1);
                            ଯଦି (FFABS(acc - exact) > 2) {
                                av_log(ଖାଲି, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.ଅଙ୍କ,
                                       a.den, b.ଅଙ୍କ, b.den, acc, exact);
                                ଫେରନ୍ତୁ 1;
                            }
                        }
                    }
                }
            }
        }
    }

    ପାଇଁ (int64_t den = 1; den <= INT_MAX; den *= 3) {
        a.den = den;
        ପାଇଁ (a.ଅଙ୍କ = -1; a.ଅଙ୍କ < (1<<27); a.ଅଙ୍କ += 1 + a.ଅଙ୍କ/100) {
            ଯଦି (check_q2intfloat(a))
                ଫେରନ୍ତୁ 1;
        }
    }

    ସ୍ଥିର ଅଚଳ AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {INT_MAX, INT_MIN}, {INT_MIN, INT_MAX}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    ଫେରନ୍ତୁ ret;
}
