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

#అన్తర్భావ "libavutil/rational.c"
#అన్తర్భావ "libavutil/integer.h"
#అన్తర్భావ "libavutil/intfloat.h"

స్థిర పూర్ణాంకం check_q2intfloat(AVRational q)
{
    దశాంశం f  = av_int2float(av_q2intfloat(q));
    దశాంశం f2 = av_q2d(q);
    పూర్ణాంకం fail;

    ఒకవేళ (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    లేకపోతే ఒకవేళ (isinf(f) || isinf(f2))
        fail = f != f2;
    లేకపోతే
        fail = fabs(f - f2) > fabs(f)/5000000;
    ఒకవేళ (fail)
        av_log(ఖాళీ, AV_LOG_ERROR, "%d/%d %f %f\n", q.అంకె, q.den, f, f2);
    తిరిగి fail;
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVRational a,b,r;
    పూర్ణాంకం i,j,k;
    పూర్ణాంకం ret = 0;
    స్థిర స్థిరరాశి int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    కొరకు (a.అంకె = -2; a.అంకె <= 2; a.అంకె++) {
        కొరకు (a.den = -2; a.den <= 2; a.den++) {
            కొరకు (b.అంకె = -2; b.అంకె <= 2; b.అంకె++) {
                కొరకు (b.den = -2; b.den <= 2; b.den++) {
                    పూర్ణాంకం c = av_cmp_q(a,b);
                    ద్విగుణ d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    ఒకవేళ (d > 0)       d = 1;
                    లేకపోతే ఒకవేళ (d < 0)  d = -1;
                    లేకపోతే ఒకవేళ (d != d) d = INT_MIN;
                    ఒకవేళ (c != d) {
                        av_log(ఖాళీ, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.అంకె,
                               a.den, b.అంకె, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_కూడు_q(b,a), b);
                    ఒకవేళ(b.den && (r.అంకె*a.den != a.అంకె*r.den || !r.అంకె != !a.అంకె || !r.den != !a.den)) {
                        av_log(ఖాళీ, AV_LOG_ERROR, "%d/%d ", r.అంకె, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    స్థిర స్థిరరాశి AVRational unit_mul_q[][3] = {
        {{గరిష్ఠ_పూర్ణాంకం, 2},      { 2, 1},            { గరిష్ఠ_పూర్ణాంకం, 1}},
        {{గరిష్ఠ_పూర్ణాంకం, 2},      {-2, 1},            {-గరిష్ఠ_పూర్ణాంకం, 1}},
        {{గరిష్ఠ_పూర్ణాంకం, 2},      { 0, 1},            {0, 1}},
        {{INT_MIN, 2},      { 2, 1},            {-గరిష్ఠ_పూర్ణాంకం, 1}}, /* not INT_MIN */
        {{INT_MIN, 2},      {-2, 1},            { గరిష్ఠ_పూర్ణాంకం, 1}},
        {{INT_MIN, 2},      { 0, 1},            {0, 1}},
        {{గరిష్ఠ_పూర్ణాంకం >> 8, 1}, {గరిష్ఠ_పూర్ణాంకం >> 8, 1},  {గరిష్ఠ_పూర్ణాంకం, 1}},
        {{1, గరిష్ఠ_పూర్ణాంకం >> 8}, {1, గరిష్ఠ_పూర్ణాంకం >> 8},  {0, 1}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        కొరకు (పూర్ణాంకం c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            ఒకవేళ (r.అంకె != c.అంకె || r.den != c.den) {
                av_log(ఖాళీ, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.అంకె, a.den, b.అంకె, b.den, r.అంకె, r.den, c.అంకె, c.den);
                ret = 1;
            }
        }
    }

    స్థిర స్థిరరాశి AVRational unit_కూడు_q[][3] = {
        {{గరిష్ఠ_పూర్ణాంకం, 1},      { 2, 2},            { గరిష్ఠ_పూర్ణాంకం, 1}},
        {{గరిష్ఠ_పూర్ణాంకం, 1},      {-2, 2},            { గరిష్ఠ_పూర్ణాంకం - 1, 1}},
        {{గరిష్ఠ_పూర్ణాంకం, 1},      { 0, 2},            { గరిష్ఠ_పూర్ణాంకం, 1}},
        {{INT_MIN, 1},      { 2, 2},            {-గరిష్ఠ_పూర్ణాంకం, 1}},
        {{INT_MIN, 1},      {-2, 2},            {-గరిష్ఠ_పూర్ణాంకం, 1}},
        {{INT_MIN, 1},      { 0, 2},            {-గరిష్ఠ_పూర్ణాంకం, 1}},
        {{గరిష్ఠ_పూర్ణాంకం - 10, 1}, {20, 1},            { గరిష్ఠ_పూర్ణాంకం, 1}},
        {{2, గరిష్ఠ_పూర్ణాంకం},      {2, గరిష్ఠ_పూర్ణాంకం},       {4, గరిష్ఠ_పూర్ణాంకం}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(unit_కూడు_q); i++) {
        కొరకు (పూర్ణాంకం c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_కూడు_q[i][c ? 1 : 0];
            AVRational b = unit_కూడు_q[i][c ? 0 : 1];
            AVRational c = unit_కూడు_q[i][2];
            AVRational r = av_కూడు_q(a, b);
            ఒకవేళ (r.అంకె != c.అంకె || r.den != c.den) {
                av_log(ఖాళీ, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.అంకె, a.den, b.అంకె, b.den, r.అంకె, r.den, c.అంకె, c.den);
                ret = 1;
            }
        }
    }

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        కొరకు (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            ఒకవేళ (b<=0)
                కొనసాగు;
            కొరకు (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                ఒకవేళ (c<=0)
                    కొనసాగు;
                res = av_rescale_rnd(a,b,c, AV_విడత_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                ఒకవేళ (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    కొనసాగు;
                ఒకవేళ (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    కొనసాగు;
                ఒకవేళ (av_cmp_i(ai, av_int2i(res)) == 0)
                    కొనసాగు;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                ఒకవేళ (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    కొనసాగు;

                av_log(ఖాళీ, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    కొరకు (a.అంకె = 1; a.అంకె <= 10; a.అంకె++) {
        కొరకు (a.den = 1; a.den <= 10; a.den++) {
            ఒకవేళ (av_గరిష్ఠ_సామాన్య_భాజకం(a.అంకె, a.den) > 1)
                కొనసాగు;
            కొరకు (b.అంకె = 1; b.అంకె <= 10; b.అంకె++) {
                కొరకు (b.den = 1; b.den <= 10; b.den++) {
                    పూర్ణాంకం ప్రారంభం;
                    ఒకవేళ (av_గరిష్ఠ_సామాన్య_భాజకం(b.అంకె, b.den) > 1)
                        కొనసాగు;
                    ఒకవేళ (av_cmp_q(b, a) < 0)
                        కొనసాగు;
                    కొరకు (ప్రారంభం = 0; ప్రారంభం < 10 ; ప్రారంభం++) {
                        పూర్ణాంకం acc= ప్రారంభం;
                        పూర్ణాంకం i;

                        కొరకు (i = 0; i<100; i++) {
                            పూర్ణాంకం exact = ప్రారంభం + av_rescale_q(i+1, b, a);
                            acc = av_కూడు_stable(a, acc, b, 1);
                            ఒకవేళ (FFABS(acc - exact) > 2) {
                                av_log(ఖాళీ, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.అంకె,
                                       a.den, b.అంకె, b.den, acc, exact);
                                తిరిగి 1;
                            }
                        }
                    }
                }
            }
        }
    }

    కొరకు (int64_t den = 1; den <= గరిష్ఠ_పూర్ణాంకం; den *= 3) {
        a.den = den;
        కొరకు (a.అంకె = -1; a.అంకె < (1<<27); a.అంకె += 1 + a.అంకె/100) {
            ఒకవేళ (check_q2intfloat(a))
                తిరిగి 1;
        }
    }

    స్థిర స్థిరరాశి AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {గరిష్ఠ_పూర్ణాంకం, INT_MIN}, {INT_MIN, గరిష్ఠ_పూర్ణాంకం}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    తిరిగి ret;
}
