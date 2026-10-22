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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/rational.c"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/integer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/intfloat.h"

ਸਥਿਰ ਪੂਰਨ check_q2intfloat(AVRational q)
{
    ਦਸ਼ਮਲਵ f  = av_int2float(av_q2intfloat(q));
    ਦਸ਼ਮਲਵ f2 = av_q2d(q);
    ਪੂਰਨ fail;

    ਜੇ (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    ਨਹੀਂਤਾਂ ਜੇ (isinf(f) || isinf(f2))
        fail = f != f2;
    ਨਹੀਂਤਾਂ
        fail = fabs(f - f2) > fabs(f)/5000000;
    ਜੇ (fail)
        av_log(ਨਿਰਾ, AV_LOG_ERROR, "%d/%d %f %f\n", q.ਅੰਕ, q.den, f, f2);
    ਵਾਪਸ fail;
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVRational a,b,r;
    ਪੂਰਨ i,j,k;
    ਪੂਰਨ ret = 0;
    ਸਥਿਰ ਅਚਲ int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    ਲਈ (a.ਅੰਕ = -2; a.ਅੰਕ <= 2; a.ਅੰਕ++) {
        ਲਈ (a.den = -2; a.den <= 2; a.den++) {
            ਲਈ (b.ਅੰਕ = -2; b.ਅੰਕ <= 2; b.ਅੰਕ++) {
                ਲਈ (b.den = -2; b.den <= 2; b.den++) {
                    ਪੂਰਨ c = av_cmp_q(a,b);
                    ਦੁੱਗਣਾ d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    ਜੇ (d > 0)       d = 1;
                    ਨਹੀਂਤਾਂ ਜੇ (d < 0)  d = -1;
                    ਨਹੀਂਤਾਂ ਜੇ (d != d) d = INT_MIN;
                    ਜੇ (c != d) {
                        av_log(ਨਿਰਾ, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.ਅੰਕ,
                               a.den, b.ਅੰਕ, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_ਜੋੜੋ_q(b,a), b);
                    ਜੇ(b.den && (r.ਅੰਕ*a.den != a.ਅੰਕ*r.den || !r.ਅੰਕ != !a.ਅੰਕ || !r.den != !a.den)) {
                        av_log(ਨਿਰਾ, AV_LOG_ERROR, "%d/%d ", r.ਅੰਕ, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    ਸਥਿਰ ਅਚਲ AVRational unit_mul_q[][3] = {
        {{ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 2},      { 2, 1},            { ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1}},
        {{ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 2},      {-2, 1},            {-ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1}},
        {{ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 2},      { 0, 1},            {0, 1}},
        {{INT_MIN, 2},      { 2, 1},            {-ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1}}, /* not INT_MIN */
        {{INT_MIN, 2},      {-2, 1},            { ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1}},
        {{INT_MIN, 2},      { 0, 1},            {0, 1}},
        {{ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ >> 8, 1}, {ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ >> 8, 1},  {ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1}},
        {{1, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ >> 8}, {1, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ >> 8},  {0, 1}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        ਲਈ (ਪੂਰਨ c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            ਜੇ (r.ਅੰਕ != c.ਅੰਕ || r.den != c.den) {
                av_log(ਨਿਰਾ, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.ਅੰਕ, a.den, b.ਅੰਕ, b.den, r.ਅੰਕ, r.den, c.ਅੰਕ, c.den);
                ret = 1;
            }
        }
    }

    ਸਥਿਰ ਅਚਲ AVRational unit_ਜੋੜੋ_q[][3] = {
        {{ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1},      { 2, 2},            { ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1}},
        {{ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1},      {-2, 2},            { ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ - 1, 1}},
        {{ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1},      { 0, 2},            { ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1}},
        {{INT_MIN, 1},      { 2, 2},            {-ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1}},
        {{INT_MIN, 1},      {-2, 2},            {-ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1}},
        {{INT_MIN, 1},      { 0, 2},            {-ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1}},
        {{ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ - 10, 1}, {20, 1},            { ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, 1}},
        {{2, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ},      {2, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ},       {4, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(unit_ਜੋੜੋ_q); i++) {
        ਲਈ (ਪੂਰਨ c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_ਜੋੜੋ_q[i][c ? 1 : 0];
            AVRational b = unit_ਜੋੜੋ_q[i][c ? 0 : 1];
            AVRational c = unit_ਜੋੜੋ_q[i][2];
            AVRational r = av_ਜੋੜੋ_q(a, b);
            ਜੇ (r.ਅੰਕ != c.ਅੰਕ || r.den != c.den) {
                av_log(ਨਿਰਾ, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.ਅੰਕ, a.den, b.ਅੰਕ, b.den, r.ਅੰਕ, r.den, c.ਅੰਕ, c.den);
                ret = 1;
            }
        }
    }

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        ਲਈ (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            ਜੇ (b<=0)
                ਜਾਰੀ;
            ਲਈ (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                ਜੇ (c<=0)
                    ਜਾਰੀ;
                res = av_rescale_rnd(a,b,c, AV_ਗੇੜਾ_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                ਜੇ (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    ਜਾਰੀ;
                ਜੇ (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    ਜਾਰੀ;
                ਜੇ (av_cmp_i(ai, av_int2i(res)) == 0)
                    ਜਾਰੀ;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                ਜੇ (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    ਜਾਰੀ;

                av_log(ਨਿਰਾ, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    ਲਈ (a.ਅੰਕ = 1; a.ਅੰਕ <= 10; a.ਅੰਕ++) {
        ਲਈ (a.den = 1; a.den <= 10; a.den++) {
            ਜੇ (av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ(a.ਅੰਕ, a.den) > 1)
                ਜਾਰੀ;
            ਲਈ (b.ਅੰਕ = 1; b.ਅੰਕ <= 10; b.ਅੰਕ++) {
                ਲਈ (b.den = 1; b.den <= 10; b.den++) {
                    ਪੂਰਨ ਸ਼ੁਰੂ;
                    ਜੇ (av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ(b.ਅੰਕ, b.den) > 1)
                        ਜਾਰੀ;
                    ਜੇ (av_cmp_q(b, a) < 0)
                        ਜਾਰੀ;
                    ਲਈ (ਸ਼ੁਰੂ = 0; ਸ਼ੁਰੂ < 10 ; ਸ਼ੁਰੂ++) {
                        ਪੂਰਨ acc= ਸ਼ੁਰੂ;
                        ਪੂਰਨ i;

                        ਲਈ (i = 0; i<100; i++) {
                            ਪੂਰਨ exact = ਸ਼ੁਰੂ + av_rescale_q(i+1, b, a);
                            acc = av_ਜੋੜੋ_stable(a, acc, b, 1);
                            ਜੇ (FFABS(acc - exact) > 2) {
                                av_log(ਨਿਰਾ, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.ਅੰਕ,
                                       a.den, b.ਅੰਕ, b.den, acc, exact);
                                ਵਾਪਸ 1;
                            }
                        }
                    }
                }
            }
        }
    }

    ਲਈ (int64_t den = 1; den <= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ; den *= 3) {
        a.den = den;
        ਲਈ (a.ਅੰਕ = -1; a.ਅੰਕ < (1<<27); a.ਅੰਕ += 1 + a.ਅੰਕ/100) {
            ਜੇ (check_q2intfloat(a))
                ਵਾਪਸ 1;
        }
    }

    ਸਥਿਰ ਅਚਲ AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, INT_MIN}, {INT_MIN, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    ਵਾਪਸ ret;
}
