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

#அந்தர்பாவ "libavutil/rational.c"
#அந்தர்பாவ "libavutil/integer.h"
#அந்தர்பாவ "libavutil/intfloat.h"

நிலையான முழு check_q2intfloat(AVRational q)
{
    தசம f  = av_int2float(av_q2intfloat(q));
    தசம f2 = av_q2d(q);
    முழு fail;

    எனில் (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    இல்லையெனில் எனில் (isinf(f) || isinf(f2))
        fail = f != f2;
    இல்லையெனில்
        fail = fabs(f - f2) > fabs(f)/5000000;
    எனில் (fail)
        av_log(வெற்று, AV_LOG_ERROR, "%d/%d %f %f\n", q.இலக்கம், q.den, f, f2);
    திரும்பு fail;
}

முழு முதன்மை(வெறுமை)
{
    AVRational a,b,r;
    முழு i,j,k;
    முழு ret = 0;
    நிலையான மாறிலி int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    க்கு (a.இலக்கம் = -2; a.இலக்கம் <= 2; a.இலக்கம்++) {
        க்கு (a.den = -2; a.den <= 2; a.den++) {
            க்கு (b.இலக்கம் = -2; b.இலக்கம் <= 2; b.இலக்கம்++) {
                க்கு (b.den = -2; b.den <= 2; b.den++) {
                    முழு c = av_cmp_q(a,b);
                    இரட்டை d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    எனில் (d > 0)       d = 1;
                    இல்லையெனில் எனில் (d < 0)  d = -1;
                    இல்லையெனில் எனில் (d != d) d = INT_MIN;
                    எனில் (c != d) {
                        av_log(வெற்று, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.இலக்கம்,
                               a.den, b.இலக்கம், b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_add_q(b,a), b);
                    எனில்(b.den && (r.இலக்கம்*a.den != a.இலக்கம்*r.den || !r.இலக்கம் != !a.இலக்கம் || !r.den != !a.den)) {
                        av_log(வெற்று, AV_LOG_ERROR, "%d/%d ", r.இலக்கம், r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    நிலையான மாறிலி AVRational unit_mul_q[][3] = {
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

    க்கு (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        க்கு (முழு c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            எனில் (r.இலக்கம் != c.இலக்கம் || r.den != c.den) {
                av_log(வெற்று, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.இலக்கம், a.den, b.இலக்கம், b.den, r.இலக்கம், r.den, c.இலக்கம், c.den);
                ret = 1;
            }
        }
    }

    நிலையான மாறிலி AVRational unit_add_q[][3] = {
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

    க்கு (i = 0; i < FF_ARRAY_ELEMS(unit_add_q); i++) {
        க்கு (முழு c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_add_q[i][c ? 1 : 0];
            AVRational b = unit_add_q[i][c ? 0 : 1];
            AVRational c = unit_add_q[i][2];
            AVRational r = av_add_q(a, b);
            எனில் (r.இலக்கம் != c.இலக்கம் || r.den != c.den) {
                av_log(வெற்று, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.இலக்கம், a.den, b.இலக்கம், b.den, r.இலக்கம், r.den, c.இலக்கம், c.den);
                ret = 1;
            }
        }
    }

    க்கு (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        க்கு (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            எனில் (b<=0)
                தொடர்;
            க்கு (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                எனில் (c<=0)
                    தொடர்;
                res = av_rescale_rnd(a,b,c, AV_ROUND_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                எனில் (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    தொடர்;
                எனில் (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    தொடர்;
                எனில் (av_cmp_i(ai, av_int2i(res)) == 0)
                    தொடர்;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                எனில் (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    தொடர்;

                av_log(வெற்று, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    க்கு (a.இலக்கம் = 1; a.இலக்கம் <= 10; a.இலக்கம்++) {
        க்கு (a.den = 1; a.den <= 10; a.den++) {
            எனில் (av_gcd(a.இலக்கம், a.den) > 1)
                தொடர்;
            க்கு (b.இலக்கம் = 1; b.இலக்கம் <= 10; b.இலக்கம்++) {
                க்கு (b.den = 1; b.den <= 10; b.den++) {
                    முழு start;
                    எனில் (av_gcd(b.இலக்கம், b.den) > 1)
                        தொடர்;
                    எனில் (av_cmp_q(b, a) < 0)
                        தொடர்;
                    க்கு (start = 0; start < 10 ; start++) {
                        முழு acc= start;
                        முழு i;

                        க்கு (i = 0; i<100; i++) {
                            முழு exact = start + av_rescale_q(i+1, b, a);
                            acc = av_add_stable(a, acc, b, 1);
                            எனில் (FFABS(acc - exact) > 2) {
                                av_log(வெற்று, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.இலக்கம்,
                                       a.den, b.இலக்கம், b.den, acc, exact);
                                திரும்பு 1;
                            }
                        }
                    }
                }
            }
        }
    }

    க்கு (int64_t den = 1; den <= INT_MAX; den *= 3) {
        a.den = den;
        க்கு (a.இலக்கம் = -1; a.இலக்கம் < (1<<27); a.இலக்கம் += 1 + a.இலக்கம்/100) {
            எனில் (check_q2intfloat(a))
                திரும்பு 1;
        }
    }

    நிலையான மாறிலி AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {INT_MAX, INT_MIN}, {INT_MIN, INT_MAX}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    க்கு (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    திரும்பு ret;
}
