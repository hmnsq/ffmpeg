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

स्थिर पूर्णाङ्क check_q2intfloat(AVRational q)
{
    भिन्न f  = av_int2float(av_q2intfloat(q));
    भिन्न f2 = av_q2d(q);
    पूर्णाङ्क fail;

    यदि (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    अन्यथा यदि (isinf(f) || isinf(f2))
        fail = f != f2;
    अन्यथा
        fail = भ_असल(f - f2) > भ_असल(f)/5000000;
    यदि (fail)
        av_log(रिक्त, AV_LOG_ERROR, "%d/%d %f %f\n", q.अङ्क, q.den, f, f2);
    फर्काऊ fail;
}

पूर्णाङ्क main(शून्य)
{
    AVRational a,b,r;
    पूर्णाङ्क i,j,k;
    पूर्णाङ्क ret = 0;
    स्थिर अचर int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    लागि (a.अङ्क = -2; a.अङ्क <= 2; a.अङ्क++) {
        लागि (a.den = -2; a.den <= 2; a.den++) {
            लागि (b.अङ्क = -2; b.अङ्क <= 2; b.अङ्क++) {
                लागि (b.den = -2; b.den <= 2; b.den++) {
                    पूर्णाङ्क c = av_cmp_q(a,b);
                    द्विगुण d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    यदि (d > 0)       d = 1;
                    अन्यथा यदि (d < 0)  d = -1;
                    अन्यथा यदि (d != d) d = पूर्णांक_न्यून;
                    यदि (c != d) {
                        av_log(रिक्त, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.अङ्क,
                               a.den, b.अङ्क, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_add_q(b,a), b);
                    यदि(b.den && (r.अङ्क*a.den != a.अङ्क*r.den || !r.अङ्क != !a.अङ्क || !r.den != !a.den)) {
                        av_log(रिक्त, AV_LOG_ERROR, "%d/%d ", r.अङ्क, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    स्थिर अचर AVRational unit_mul_q[][3] = {
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

    लागि (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        लागि (पूर्णाङ्क c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            यदि (r.अङ्क != c.अङ्क || r.den != c.den) {
                av_log(रिक्त, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.अङ्क, a.den, b.अङ्क, b.den, r.अङ्क, r.den, c.अङ्क, c.den);
                ret = 1;
            }
        }
    }

    स्थिर अचर AVRational unit_add_q[][3] = {
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

    लागि (i = 0; i < FF_ARRAY_ELEMS(unit_add_q); i++) {
        लागि (पूर्णाङ्क c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_add_q[i][c ? 1 : 0];
            AVRational b = unit_add_q[i][c ? 0 : 1];
            AVRational c = unit_add_q[i][2];
            AVRational r = av_add_q(a, b);
            यदि (r.अङ्क != c.अङ्क || r.den != c.den) {
                av_log(रिक्त, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.अङ्क, a.den, b.अङ्क, b.den, r.अङ्क, r.den, c.अङ्क, c.den);
                ret = 1;
            }
        }
    }

    लागि (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        लागि (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            यदि (b<=0)
                जारी;
            लागि (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                यदि (c<=0)
                    जारी;
                res = av_rescale_rnd(a,b,c, AV_ROUND_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                यदि (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    जारी;
                यदि (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    जारी;
                यदि (av_cmp_i(ai, av_int2i(res)) == 0)
                    जारी;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                यदि (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    जारी;

                av_log(रिक्त, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    लागि (a.अङ्क = 1; a.अङ्क <= 10; a.अङ्क++) {
        लागि (a.den = 1; a.den <= 10; a.den++) {
            यदि (av_gcd(a.अङ्क, a.den) > 1)
                जारी;
            लागि (b.अङ्क = 1; b.अङ्क <= 10; b.अङ्क++) {
                लागि (b.den = 1; b.den <= 10; b.den++) {
                    पूर्णाङ्क start;
                    यदि (av_gcd(b.अङ्क, b.den) > 1)
                        जारी;
                    यदि (av_cmp_q(b, a) < 0)
                        जारी;
                    लागि (start = 0; start < 10 ; start++) {
                        पूर्णाङ्क acc= start;
                        पूर्णाङ्क i;

                        लागि (i = 0; i<100; i++) {
                            पूर्णाङ्क exact = start + av_rescale_q(i+1, b, a);
                            acc = av_add_stable(a, acc, b, 1);
                            यदि (FFABS(acc - exact) > 2) {
                                av_log(रिक्त, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.अङ्क,
                                       a.den, b.अङ्क, b.den, acc, exact);
                                फर्काऊ 1;
                            }
                        }
                    }
                }
            }
        }
    }

    लागि (int64_t den = 1; den <= पूर्णांक_उच्च; den *= 3) {
        a.den = den;
        लागि (a.अङ्क = -1; a.अङ्क < (1<<27); a.अङ्क += 1 + a.अङ्क/100) {
            यदि (check_q2intfloat(a))
                फर्काऊ 1;
        }
    }

    स्थिर अचर AVRational q2intfloat_list[] = {
        {पूर्णांक_न्यून, 1}, {1, पूर्णांक_न्यून}, {पूर्णांक_न्यून, पूर्णांक_न्यून}, {पूर्णांक_न्यून, -1}, {-1, पूर्णांक_न्यून},
        {पूर्णांक_उच्च, पूर्णांक_न्यून}, {पूर्णांक_न्यून, पूर्णांक_उच्च}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {पूर्णांक_न्यून, 0}, {0, 0}, {0, 1}, {0, पूर्णांक_न्यून},
    };

    लागि (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    फर्काऊ ret;
}
