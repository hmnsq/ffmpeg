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
        av_log(रिक्त, AV_LOG_ERROR, "%d/%d %f %f\n", q.अंक, q.den, f, f2);
    प्रत्यागम fail;
}

पूर्णाङ्क main(शून्य)
{
    AVRational a,b,r;
    पूर्णाङ्क i,j,k;
    पूर्णाङ्क ret = 0;
    स्थिर ध्रुव int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    प्रति (a.अंक = -2; a.अंक <= 2; a.अंक++) {
        प्रति (a.den = -2; a.den <= 2; a.den++) {
            प्रति (b.अंक = -2; b.अंक <= 2; b.अंक++) {
                प्रति (b.den = -2; b.den <= 2; b.den++) {
                    पूर्णाङ्क c = av_cmp_q(a,b);
                    द्विगुण d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    यदि (d > 0)       d = 1;
                    अन्यथा यदि (d < 0)  d = -1;
                    अन्यथा यदि (d != d) d = पूर्णांक_न्यून;
                    यदि (c != d) {
                        av_log(रिक्त, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.अंक,
                               a.den, b.अंक, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_add_q(b,a), b);
                    यदि(b.den && (r.अंक*a.den != a.अंक*r.den || !r.अंक != !a.अंक || !r.den != !a.den)) {
                        av_log(रिक्त, AV_LOG_ERROR, "%d/%d ", r.अंक, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    स्थिर ध्रुव AVRational unit_mul_q[][3] = {
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

    प्रति (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        प्रति (पूर्णाङ्क c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            यदि (r.अंक != c.अंक || r.den != c.den) {
                av_log(रिक्त, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.अंक, a.den, b.अंक, b.den, r.अंक, r.den, c.अंक, c.den);
                ret = 1;
            }
        }
    }

    स्थिर ध्रुव AVRational unit_add_q[][3] = {
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

    प्रति (i = 0; i < FF_ARRAY_ELEMS(unit_add_q); i++) {
        प्रति (पूर्णाङ्क c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_add_q[i][c ? 1 : 0];
            AVRational b = unit_add_q[i][c ? 0 : 1];
            AVRational c = unit_add_q[i][2];
            AVRational r = av_add_q(a, b);
            यदि (r.अंक != c.अंक || r.den != c.den) {
                av_log(रिक्त, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.अंक, a.den, b.अंक, b.den, r.अंक, r.den, c.अंक, c.den);
                ret = 1;
            }
        }
    }

    प्रति (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        प्रति (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            यदि (b<=0)
                अनुवर्त;
            प्रति (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                यदि (c<=0)
                    अनुवर्त;
                res = av_rescale_rnd(a,b,c, AV_ROUND_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                यदि (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    अनुवर्त;
                यदि (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    अनुवर्त;
                यदि (av_cmp_i(ai, av_int2i(res)) == 0)
                    अनुवर्त;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                यदि (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    अनुवर्त;

                av_log(रिक्त, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    प्रति (a.अंक = 1; a.अंक <= 10; a.अंक++) {
        प्रति (a.den = 1; a.den <= 10; a.den++) {
            यदि (av_gcd(a.अंक, a.den) > 1)
                अनुवर्त;
            प्रति (b.अंक = 1; b.अंक <= 10; b.अंक++) {
                प्रति (b.den = 1; b.den <= 10; b.den++) {
                    पूर्णाङ्क start;
                    यदि (av_gcd(b.अंक, b.den) > 1)
                        अनुवर्त;
                    यदि (av_cmp_q(b, a) < 0)
                        अनुवर्त;
                    प्रति (start = 0; start < 10 ; start++) {
                        पूर्णाङ्क acc= start;
                        पूर्णाङ्क i;

                        प्रति (i = 0; i<100; i++) {
                            पूर्णाङ्क exact = start + av_rescale_q(i+1, b, a);
                            acc = av_add_stable(a, acc, b, 1);
                            यदि (FFABS(acc - exact) > 2) {
                                av_log(रिक्त, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.अंक,
                                       a.den, b.अंक, b.den, acc, exact);
                                प्रत्यागम 1;
                            }
                        }
                    }
                }
            }
        }
    }

    प्रति (int64_t den = 1; den <= पूर्णांक_उच्च; den *= 3) {
        a.den = den;
        प्रति (a.अंक = -1; a.अंक < (1<<27); a.अंक += 1 + a.अंक/100) {
            यदि (check_q2intfloat(a))
                प्रत्यागम 1;
        }
    }

    स्थिर ध्रुव AVRational q2intfloat_list[] = {
        {पूर्णांक_न्यून, 1}, {1, पूर्णांक_न्यून}, {पूर्णांक_न्यून, पूर्णांक_न्यून}, {पूर्णांक_न्यून, -1}, {-1, पूर्णांक_न्यून},
        {पूर्णांक_उच्च, पूर्णांक_न्यून}, {पूर्णांक_न्यून, पूर्णांक_उच्च}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {पूर्णांक_न्यून, 0}, {0, 0}, {0, 1}, {0, पूर्णांक_न्यून},
    };

    प्रति (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    प्रत्यागम ret;
}
