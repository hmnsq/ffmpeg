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

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ check_q2intfloat(AVRational q)
{
    ದಶಮಾಂಶ f  = av_int2float(av_q2intfloat(q));
    ದಶಮಾಂಶ f2 = av_q2d(q);
    ಪೂರ್ಣಾಂಕ fail;

    ಆದರೆ (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (isinf(f) || isinf(f2))
        fail = f != f2;
    ಇಲ್ಲದಿದ್ದರೆ
        fail = fabs(f - f2) > fabs(f)/5000000;
    ಆದರೆ (fail)
        av_log(ಖಾಲಿ, AV_LOG_ERROR, "%d/%d %f %f\n", q.ಅಂಕೆ, q.den, f, f2);
    ಹಿಂತಿರುಗಿ fail;
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVRational a,b,r;
    ಪೂರ್ಣಾಂಕ i,j,k;
    ಪೂರ್ಣಾಂಕ ret = 0;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    ಗಾಗಿ (a.ಅಂಕೆ = -2; a.ಅಂಕೆ <= 2; a.ಅಂಕೆ++) {
        ಗಾಗಿ (a.den = -2; a.den <= 2; a.den++) {
            ಗಾಗಿ (b.ಅಂಕೆ = -2; b.ಅಂಕೆ <= 2; b.ಅಂಕೆ++) {
                ಗಾಗಿ (b.den = -2; b.den <= 2; b.den++) {
                    ಪೂರ್ಣಾಂಕ c = av_cmp_q(a,b);
                    ದ್ವಿಗುಣ d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    ಆದರೆ (d > 0)       d = 1;
                    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d < 0)  d = -1;
                    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (d != d) d = INT_MIN;
                    ಆದರೆ (c != d) {
                        av_log(ಖಾಲಿ, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.ಅಂಕೆ,
                               a.den, b.ಅಂಕೆ, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_ಕೂಡಿಸು_q(b,a), b);
                    ಆದರೆ(b.den && (r.ಅಂಕೆ*a.den != a.ಅಂಕೆ*r.den || !r.ಅಂಕೆ != !a.ಅಂಕೆ || !r.den != !a.den)) {
                        av_log(ಖಾಲಿ, AV_LOG_ERROR, "%d/%d ", r.ಅಂಕೆ, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVRational unit_mul_q[][3] = {
        {{ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 2},      { 2, 1},            { ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1}},
        {{ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 2},      {-2, 1},            {-ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1}},
        {{ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 2},      { 0, 1},            {0, 1}},
        {{INT_MIN, 2},      { 2, 1},            {-ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1}}, /* not INT_MIN */
        {{INT_MIN, 2},      {-2, 1},            { ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1}},
        {{INT_MIN, 2},      { 0, 1},            {0, 1}},
        {{ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ >> 8, 1}, {ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ >> 8, 1},  {ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1}},
        {{1, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ >> 8}, {1, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ >> 8},  {0, 1}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            ಆದರೆ (r.ಅಂಕೆ != c.ಅಂಕೆ || r.den != c.den) {
                av_log(ಖಾಲಿ, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.ಅಂಕೆ, a.den, b.ಅಂಕೆ, b.den, r.ಅಂಕೆ, r.den, c.ಅಂಕೆ, c.den);
                ret = 1;
            }
        }
    }

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVRational unit_ಕೂಡಿಸು_q[][3] = {
        {{ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1},      { 2, 2},            { ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1}},
        {{ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1},      {-2, 2},            { ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ - 1, 1}},
        {{ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1},      { 0, 2},            { ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1}},
        {{INT_MIN, 1},      { 2, 2},            {-ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1}},
        {{INT_MIN, 1},      {-2, 2},            {-ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1}},
        {{INT_MIN, 1},      { 0, 2},            {-ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1}},
        {{ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ - 10, 1}, {20, 1},            { ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, 1}},
        {{2, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ},      {2, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ},       {4, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(unit_ಕೂಡಿಸು_q); i++) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_ಕೂಡಿಸು_q[i][c ? 1 : 0];
            AVRational b = unit_ಕೂಡಿಸು_q[i][c ? 0 : 1];
            AVRational c = unit_ಕೂಡಿಸು_q[i][2];
            AVRational r = av_ಕೂಡಿಸು_q(a, b);
            ಆದರೆ (r.ಅಂಕೆ != c.ಅಂಕೆ || r.den != c.den) {
                av_log(ಖಾಲಿ, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.ಅಂಕೆ, a.den, b.ಅಂಕೆ, b.den, r.ಅಂಕೆ, r.den, c.ಅಂಕೆ, c.den);
                ret = 1;
            }
        }
    }

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        ಗಾಗಿ (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            ಆದರೆ (b<=0)
                ಮುಂದುವರಿ;
            ಗಾಗಿ (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                ಆದರೆ (c<=0)
                    ಮುಂದುವರಿ;
                res = av_rescale_rnd(a,b,c, AV_ಸುತ್ತು_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                ಆದರೆ (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    ಮುಂದುವರಿ;
                ಆದರೆ (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    ಮುಂದುವರಿ;
                ಆದರೆ (av_cmp_i(ai, av_int2i(res)) == 0)
                    ಮುಂದುವರಿ;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                ಆದರೆ (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    ಮುಂದುವರಿ;

                av_log(ಖಾಲಿ, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    ಗಾಗಿ (a.ಅಂಕೆ = 1; a.ಅಂಕೆ <= 10; a.ಅಂಕೆ++) {
        ಗಾಗಿ (a.den = 1; a.den <= 10; a.den++) {
            ಆದರೆ (av_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ(a.ಅಂಕೆ, a.den) > 1)
                ಮುಂದುವರಿ;
            ಗಾಗಿ (b.ಅಂಕೆ = 1; b.ಅಂಕೆ <= 10; b.ಅಂಕೆ++) {
                ಗಾಗಿ (b.den = 1; b.den <= 10; b.den++) {
                    ಪೂರ್ಣಾಂಕ ಆರಂಭ;
                    ಆದರೆ (av_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ(b.ಅಂಕೆ, b.den) > 1)
                        ಮುಂದುವರಿ;
                    ಆದರೆ (av_cmp_q(b, a) < 0)
                        ಮುಂದುವರಿ;
                    ಗಾಗಿ (ಆರಂಭ = 0; ಆರಂಭ < 10 ; ಆರಂಭ++) {
                        ಪೂರ್ಣಾಂಕ acc= ಆರಂಭ;
                        ಪೂರ್ಣಾಂಕ i;

                        ಗಾಗಿ (i = 0; i<100; i++) {
                            ಪೂರ್ಣಾಂಕ exact = ಆರಂಭ + av_rescale_q(i+1, b, a);
                            acc = av_ಕೂಡಿಸು_stable(a, acc, b, 1);
                            ಆದರೆ (FFABS(acc - exact) > 2) {
                                av_log(ಖಾಲಿ, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.ಅಂಕೆ,
                                       a.den, b.ಅಂಕೆ, b.den, acc, exact);
                                ಹಿಂತಿರುಗಿ 1;
                            }
                        }
                    }
                }
            }
        }
    }

    ಗಾಗಿ (int64_t den = 1; den <= ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ; den *= 3) {
        a.den = den;
        ಗಾಗಿ (a.ಅಂಕೆ = -1; a.ಅಂಕೆ < (1<<27); a.ಅಂಕೆ += 1 + a.ಅಂಕೆ/100) {
            ಆದರೆ (check_q2intfloat(a))
                ಹಿಂತಿರುಗಿ 1;
        }
    }

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, INT_MIN}, {INT_MIN, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    ಹಿಂತಿರುಗಿ ret;
}
