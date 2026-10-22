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
        fail = fabs(f - f2) > fabs(f)/5000000;
    यदि (fail)
        av_log(रिक्त, AV_LOG_ERROR, "%d/%d %f %f\n", q.अङ्कः, q.den, f, f2);
    प्रत्यागम fail;
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    AVRational a,b,r;
    पूर्णाङ्क i,j,k;
    पूर्णाङ्क ret = 0;
    स्थिर ध्रुव int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    प्रति (a.अङ्कः = -2; a.अङ्कः <= 2; a.अङ्कः++) {
        प्रति (a.den = -2; a.den <= 2; a.den++) {
            प्रति (b.अङ्कः = -2; b.अङ्कः <= 2; b.अङ्कः++) {
                प्रति (b.den = -2; b.den <= 2; b.den++) {
                    पूर्णाङ्क c = av_cmp_q(a,b);
                    द्विगुण d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    यदि (d > 0)       d = 1;
                    अन्यथा यदि (d < 0)  d = -1;
                    अन्यथा यदि (d != d) d = INT_MIN;
                    यदि (c != d) {
                        av_log(रिक्त, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.अङ्कः,
                               a.den, b.अङ्कः, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_सङ्कलय_q(b,a), b);
                    यदि(b.den && (r.अङ्कः*a.den != a.अङ्कः*r.den || !r.अङ्कः != !a.अङ्कः || !r.den != !a.den)) {
                        av_log(रिक्त, AV_LOG_ERROR, "%d/%d ", r.अङ्कः, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    स्थिर ध्रुव AVRational unit_mul_q[][3] = {
        {{अधिकतम_पूर्णाङ्कः, 2},      { 2, 1},            { अधिकतम_पूर्णाङ्कः, 1}},
        {{अधिकतम_पूर्णाङ्कः, 2},      {-2, 1},            {-अधिकतम_पूर्णाङ्कः, 1}},
        {{अधिकतम_पूर्णाङ्कः, 2},      { 0, 1},            {0, 1}},
        {{INT_MIN, 2},      { 2, 1},            {-अधिकतम_पूर्णाङ्कः, 1}}, /* not INT_MIN */
        {{INT_MIN, 2},      {-2, 1},            { अधिकतम_पूर्णाङ्कः, 1}},
        {{INT_MIN, 2},      { 0, 1},            {0, 1}},
        {{अधिकतम_पूर्णाङ्कः >> 8, 1}, {अधिकतम_पूर्णाङ्कः >> 8, 1},  {अधिकतम_पूर्णाङ्कः, 1}},
        {{1, अधिकतम_पूर्णाङ्कः >> 8}, {1, अधिकतम_पूर्णाङ्कः >> 8},  {0, 1}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    प्रति (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        प्रति (पूर्णाङ्क c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            यदि (r.अङ्कः != c.अङ्कः || r.den != c.den) {
                av_log(रिक्त, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.अङ्कः, a.den, b.अङ्कः, b.den, r.अङ्कः, r.den, c.अङ्कः, c.den);
                ret = 1;
            }
        }
    }

    स्थिर ध्रुव AVRational unit_सङ्कलय_q[][3] = {
        {{अधिकतम_पूर्णाङ्कः, 1},      { 2, 2},            { अधिकतम_पूर्णाङ्कः, 1}},
        {{अधिकतम_पूर्णाङ्कः, 1},      {-2, 2},            { अधिकतम_पूर्णाङ्कः - 1, 1}},
        {{अधिकतम_पूर्णाङ्कः, 1},      { 0, 2},            { अधिकतम_पूर्णाङ्कः, 1}},
        {{INT_MIN, 1},      { 2, 2},            {-अधिकतम_पूर्णाङ्कः, 1}},
        {{INT_MIN, 1},      {-2, 2},            {-अधिकतम_पूर्णाङ्कः, 1}},
        {{INT_MIN, 1},      { 0, 2},            {-अधिकतम_पूर्णाङ्कः, 1}},
        {{अधिकतम_पूर्णाङ्कः - 10, 1}, {20, 1},            { अधिकतम_पूर्णाङ्कः, 1}},
        {{2, अधिकतम_पूर्णाङ्कः},      {2, अधिकतम_पूर्णाङ्कः},       {4, अधिकतम_पूर्णाङ्कः}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    प्रति (i = 0; i < FF_ARRAY_ELEMS(unit_सङ्कलय_q); i++) {
        प्रति (पूर्णाङ्क c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_सङ्कलय_q[i][c ? 1 : 0];
            AVRational b = unit_सङ्कलय_q[i][c ? 0 : 1];
            AVRational c = unit_सङ्कलय_q[i][2];
            AVRational r = av_सङ्कलय_q(a, b);
            यदि (r.अङ्कः != c.अङ्कः || r.den != c.den) {
                av_log(रिक्त, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.अङ्कः, a.den, b.अङ्कः, b.den, r.अङ्कः, r.den, c.अङ्कः, c.den);
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
                res = av_rescale_rnd(a,b,c, AV_आवर्तनम्_ZERO);

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

    प्रति (a.अङ्कः = 1; a.अङ्कः <= 10; a.अङ्कः++) {
        प्रति (a.den = 1; a.den <= 10; a.den++) {
            यदि (av_gcd(a.अङ्कः, a.den) > 1)
                अनुवर्त;
            प्रति (b.अङ्कः = 1; b.अङ्कः <= 10; b.अङ्कः++) {
                प्रति (b.den = 1; b.den <= 10; b.den++) {
                    पूर्णाङ्क start;
                    यदि (av_gcd(b.अङ्कः, b.den) > 1)
                        अनुवर्त;
                    यदि (av_cmp_q(b, a) < 0)
                        अनुवर्त;
                    प्रति (start = 0; start < 10 ; start++) {
                        पूर्णाङ्क acc= start;
                        पूर्णाङ्क i;

                        प्रति (i = 0; i<100; i++) {
                            पूर्णाङ्क exact = start + av_rescale_q(i+1, b, a);
                            acc = av_सङ्कलय_stable(a, acc, b, 1);
                            यदि (FFABS(acc - exact) > 2) {
                                av_log(रिक्त, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.अङ्कः,
                                       a.den, b.अङ्कः, b.den, acc, exact);
                                प्रत्यागम 1;
                            }
                        }
                    }
                }
            }
        }
    }

    प्रति (int64_t den = 1; den <= अधिकतम_पूर्णाङ्कः; den *= 3) {
        a.den = den;
        प्रति (a.अङ्कः = -1; a.अङ्कः < (1<<27); a.अङ्कः += 1 + a.अङ्कः/100) {
            यदि (check_q2intfloat(a))
                प्रत्यागम 1;
        }
    }

    स्थिर ध्रुव AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {अधिकतम_पूर्णाङ्कः, INT_MIN}, {INT_MIN, अधिकतम_पूर्णाङ्कः}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    प्रति (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    प्रत्यागम ret;
}
