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

#अन्तर्भाव "libavutil/rational.c"
#अन्तर्भाव "libavutil/integer.h"
#अन्तर्भाव "libavutil/intfloat.h"

स्थिर पूर्णांक check_q2intfloat(AVRational q)
{
    दशांश f  = av_int2float(av_q2intfloat(q));
    दशांश f2 = av_q2d(q);
    पूर्णांक fail;

    जर (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    अन्यथा जर (isinf(f) || isinf(f2))
        fail = f != f2;
    अन्यथा
        fail = भ_असल(f - f2) > भ_असल(f)/5000000;
    जर (fail)
        av_log(रिक्त, AV_LOG_ERROR, "%d/%d %f %f\n", q.अंक, q.den, f, f2);
    परत fail;
}

पूर्णांक main(शून्य)
{
    AVRational a,b,r;
    पूर्णांक i,j,k;
    पूर्णांक ret = 0;
    स्थिर स्थिरांक int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    साठी (a.अंक = -2; a.अंक <= 2; a.अंक++) {
        साठी (a.den = -2; a.den <= 2; a.den++) {
            साठी (b.अंक = -2; b.अंक <= 2; b.अंक++) {
                साठी (b.den = -2; b.den <= 2; b.den++) {
                    पूर्णांक c = av_cmp_q(a,b);
                    द्विगुण d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    जर (d > 0)       d = 1;
                    अन्यथा जर (d < 0)  d = -1;
                    अन्यथा जर (d != d) d = पूर्णांक_न्यून;
                    जर (c != d) {
                        av_log(रिक्त, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.अंक,
                               a.den, b.अंक, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_add_q(b,a), b);
                    जर(b.den && (r.अंक*a.den != a.अंक*r.den || !r.अंक != !a.अंक || !r.den != !a.den)) {
                        av_log(रिक्त, AV_LOG_ERROR, "%d/%d ", r.अंक, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    स्थिर स्थिरांक AVRational unit_mul_q[][3] = {
        {{पूर्णांक_उच्च, 2},      { 2, 1},            { पूर्णांक_उच्च, 1}},
        {{पूर्णांक_उच्च, 2},      {-2, 1},            {-पूर्णांक_उच्च, 1}},
        {{पूर्णांक_उच्च, 2},      { 0, 1},            {0, 1}},
        {{पूर्णांक_न्यून, 2},      { 2, 1},            {-पूर्णांक_उच्च, 1}}, /* not INT_MIN */
        {{पूर्णांक_न्यून, 2},      {-2, 1},            { पूर्णांक_उच्च, 1}},
        {{पूर्णांक_न्यून, 2},      { 0, 1},            {0, 1}},
        {{पूर्णांक_उच्च >> 8, 1}, {पूर्णांक_उच्च >> 8, 1},  {पूर्णांक_उच्च, 1}},
        {{1, पूर्णांक_उच्च >> 8}, {1, पूर्णांक_उच्च >> 8},  {0, 1}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    साठी (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        साठी (पूर्णांक c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            जर (r.अंक != c.अंक || r.den != c.den) {
                av_log(रिक्त, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.अंक, a.den, b.अंक, b.den, r.अंक, r.den, c.अंक, c.den);
                ret = 1;
            }
        }
    }

    स्थिर स्थिरांक AVRational unit_add_q[][3] = {
        {{पूर्णांक_उच्च, 1},      { 2, 2},            { पूर्णांक_उच्च, 1}},
        {{पूर्णांक_उच्च, 1},      {-2, 2},            { पूर्णांक_उच्च - 1, 1}},
        {{पूर्णांक_उच्च, 1},      { 0, 2},            { पूर्णांक_उच्च, 1}},
        {{पूर्णांक_न्यून, 1},      { 2, 2},            {-पूर्णांक_उच्च, 1}},
        {{पूर्णांक_न्यून, 1},      {-2, 2},            {-पूर्णांक_उच्च, 1}},
        {{पूर्णांक_न्यून, 1},      { 0, 2},            {-पूर्णांक_उच्च, 1}},
        {{पूर्णांक_उच्च - 10, 1}, {20, 1},            { पूर्णांक_उच्च, 1}},
        {{2, पूर्णांक_उच्च},      {2, पूर्णांक_उच्च},       {4, पूर्णांक_उच्च}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    साठी (i = 0; i < FF_ARRAY_ELEMS(unit_add_q); i++) {
        साठी (पूर्णांक c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_add_q[i][c ? 1 : 0];
            AVRational b = unit_add_q[i][c ? 0 : 1];
            AVRational c = unit_add_q[i][2];
            AVRational r = av_add_q(a, b);
            जर (r.अंक != c.अंक || r.den != c.den) {
                av_log(रिक्त, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.अंक, a.den, b.अंक, b.den, r.अंक, r.den, c.अंक, c.den);
                ret = 1;
            }
        }
    }

    साठी (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        साठी (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            जर (b<=0)
                सुरूठेवा;
            साठी (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                जर (c<=0)
                    सुरूठेवा;
                res = av_rescale_rnd(a,b,c, AV_ROUND_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                जर (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    सुरूठेवा;
                जर (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    सुरूठेवा;
                जर (av_cmp_i(ai, av_int2i(res)) == 0)
                    सुरूठेवा;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                जर (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    सुरूठेवा;

                av_log(रिक्त, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    साठी (a.अंक = 1; a.अंक <= 10; a.अंक++) {
        साठी (a.den = 1; a.den <= 10; a.den++) {
            जर (av_gcd(a.अंक, a.den) > 1)
                सुरूठेवा;
            साठी (b.अंक = 1; b.अंक <= 10; b.अंक++) {
                साठी (b.den = 1; b.den <= 10; b.den++) {
                    पूर्णांक start;
                    जर (av_gcd(b.अंक, b.den) > 1)
                        सुरूठेवा;
                    जर (av_cmp_q(b, a) < 0)
                        सुरूठेवा;
                    साठी (start = 0; start < 10 ; start++) {
                        पूर्णांक acc= start;
                        पूर्णांक i;

                        साठी (i = 0; i<100; i++) {
                            पूर्णांक exact = start + av_rescale_q(i+1, b, a);
                            acc = av_add_stable(a, acc, b, 1);
                            जर (FFABS(acc - exact) > 2) {
                                av_log(रिक्त, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.अंक,
                                       a.den, b.अंक, b.den, acc, exact);
                                परत 1;
                            }
                        }
                    }
                }
            }
        }
    }

    साठी (int64_t den = 1; den <= पूर्णांक_उच्च; den *= 3) {
        a.den = den;
        साठी (a.अंक = -1; a.अंक < (1<<27); a.अंक += 1 + a.अंक/100) {
            जर (check_q2intfloat(a))
                परत 1;
        }
    }

    स्थिर स्थिरांक AVRational q2intfloat_list[] = {
        {पूर्णांक_न्यून, 1}, {1, पूर्णांक_न्यून}, {पूर्णांक_न्यून, पूर्णांक_न्यून}, {पूर्णांक_न्यून, -1}, {-1, पूर्णांक_न्यून},
        {पूर्णांक_उच्च, पूर्णांक_न्यून}, {पूर्णांक_न्यून, पूर्णांक_उच्च}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {पूर्णांक_न्यून, 0}, {0, 0}, {0, 1}, {0, पूर्णांक_न्यून},
    };

    साठी (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    परत ret;
}
