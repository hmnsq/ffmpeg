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

#ಅನ್ತರ್ಭಾವ "libavutil/rational.c"
#ಅನ್ತರ್ಭಾವ "libavutil/integer.h"
#ಅನ್ತರ್ಭಾವ "libavutil/intfloat.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ check_q2intfloat(AVRational q)
{
    ಭಿನ್ನ f  = av_int2float(av_q2intfloat(q));
    ಭಿನ್ನ f2 = av_q2d(q);
    ಪೂರ್ಣಾಙ್ಕ fail;

    ಯದಿ (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    ಅನ್ಯಥಾ ಯದಿ (isinf(f) || isinf(f2))
        fail = f != f2;
    ಅನ್ಯಥಾ
        fail = fabs(f - f2) > fabs(f)/5000000;
    ಯದಿ (fail)
        av_log(ರಿಕ್ತ, AV_LOG_ERROR, "%d/%d %f %f\n", q.ಅಂಕೆ, q.den, f, f2);
    ಪ್ರತ್ಯಾಗಮ fail;
}

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    AVRational a,b,r;
    ಪೂರ್ಣಾಙ್ಕ i,j,k;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;
    ಸ್ಥಿರ ಧ್ರುವ int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    ಪ್ರತಿ (a.ಅಂಕೆ = -2; a.ಅಂಕೆ <= 2; a.ಅಂಕೆ++) {
        ಪ್ರತಿ (a.den = -2; a.den <= 2; a.den++) {
            ಪ್ರತಿ (b.ಅಂಕೆ = -2; b.ಅಂಕೆ <= 2; b.ಅಂಕೆ++) {
                ಪ್ರತಿ (b.den = -2; b.den <= 2; b.den++) {
                    ಪೂರ್ಣಾಙ್ಕ c = av_cmp_q(a,b);
                    ದ್ವಿಗುಣ d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    ಯದಿ (d > 0)       d = 1;
                    ಅನ್ಯಥಾ ಯದಿ (d < 0)  d = -1;
                    ಅನ್ಯಥಾ ಯದಿ (d != d) d = INT_MIN;
                    ಯದಿ (c != d) {
                        av_log(ರಿಕ್ತ, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.ಅಂಕೆ,
                               a.den, b.ಅಂಕೆ, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_add_q(b,a), b);
                    ಯದಿ(b.den && (r.ಅಂಕೆ*a.den != a.ಅಂಕೆ*r.den || !r.ಅಂಕೆ != !a.ಅಂಕೆ || !r.den != !a.den)) {
                        av_log(ರಿಕ್ತ, AV_LOG_ERROR, "%d/%d ", r.ಅಂಕೆ, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    ಸ್ಥಿರ ಧ್ರುವ AVRational unit_mul_q[][3] = {
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

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            ಯದಿ (r.ಅಂಕೆ != c.ಅಂಕೆ || r.den != c.den) {
                av_log(ರಿಕ್ತ, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.ಅಂಕೆ, a.den, b.ಅಂಕೆ, b.den, r.ಅಂಕೆ, r.den, c.ಅಂಕೆ, c.den);
                ret = 1;
            }
        }
    }

    ಸ್ಥಿರ ಧ್ರುವ AVRational unit_add_q[][3] = {
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

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(unit_add_q); i++) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_add_q[i][c ? 1 : 0];
            AVRational b = unit_add_q[i][c ? 0 : 1];
            AVRational c = unit_add_q[i][2];
            AVRational r = av_add_q(a, b);
            ಯದಿ (r.ಅಂಕೆ != c.ಅಂಕೆ || r.den != c.den) {
                av_log(ರಿಕ್ತ, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.ಅಂಕೆ, a.den, b.ಅಂಕೆ, b.den, r.ಅಂಕೆ, r.den, c.ಅಂಕೆ, c.den);
                ret = 1;
            }
        }
    }

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        ಪ್ರತಿ (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            ಯದಿ (b<=0)
                ಅನುವರ್ತ;
            ಪ್ರತಿ (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                ಯದಿ (c<=0)
                    ಅನುವರ್ತ;
                res = av_rescale_rnd(a,b,c, AV_ROUND_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                ಯದಿ (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    ಅನುವರ್ತ;
                ಯದಿ (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    ಅನುವರ್ತ;
                ಯದಿ (av_cmp_i(ai, av_int2i(res)) == 0)
                    ಅನುವರ್ತ;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                ಯದಿ (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    ಅನುವರ್ತ;

                av_log(ರಿಕ್ತ, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    ಪ್ರತಿ (a.ಅಂಕೆ = 1; a.ಅಂಕೆ <= 10; a.ಅಂಕೆ++) {
        ಪ್ರತಿ (a.den = 1; a.den <= 10; a.den++) {
            ಯದಿ (av_gcd(a.ಅಂಕೆ, a.den) > 1)
                ಅನುವರ್ತ;
            ಪ್ರತಿ (b.ಅಂಕೆ = 1; b.ಅಂಕೆ <= 10; b.ಅಂಕೆ++) {
                ಪ್ರತಿ (b.den = 1; b.den <= 10; b.den++) {
                    ಪೂರ್ಣಾಙ್ಕ start;
                    ಯದಿ (av_gcd(b.ಅಂಕೆ, b.den) > 1)
                        ಅನುವರ್ತ;
                    ಯದಿ (av_cmp_q(b, a) < 0)
                        ಅನುವರ್ತ;
                    ಪ್ರತಿ (start = 0; start < 10 ; start++) {
                        ಪೂರ್ಣಾಙ್ಕ acc= start;
                        ಪೂರ್ಣಾಙ್ಕ i;

                        ಪ್ರತಿ (i = 0; i<100; i++) {
                            ಪೂರ್ಣಾಙ್ಕ exact = start + av_rescale_q(i+1, b, a);
                            acc = av_add_stable(a, acc, b, 1);
                            ಯದಿ (FFABS(acc - exact) > 2) {
                                av_log(ರಿಕ್ತ, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.ಅಂಕೆ,
                                       a.den, b.ಅಂಕೆ, b.den, acc, exact);
                                ಪ್ರತ್ಯಾಗಮ 1;
                            }
                        }
                    }
                }
            }
        }
    }

    ಪ್ರತಿ (int64_t den = 1; den <= INT_MAX; den *= 3) {
        a.den = den;
        ಪ್ರತಿ (a.ಅಂಕೆ = -1; a.ಅಂಕೆ < (1<<27); a.ಅಂಕೆ += 1 + a.ಅಂಕೆ/100) {
            ಯದಿ (check_q2intfloat(a))
                ಪ್ರತ್ಯಾಗಮ 1;
        }
    }

    ಸ್ಥಿರ ಧ್ರುವ AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {INT_MAX, INT_MIN}, {INT_MIN, INT_MAX}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    ಪ್ರತ್ಯಾಗಮ ret;
}
