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

#ضمن "libavutil/rational.c"
#ضمن "libavutil/integer.h"
#ضمن "libavutil/intfloat.h"

ساكن صحيح check_q2intfloat(AVRational q)
{
    عائم f  = av_int2float(av_q2intfloat(q));
    عائم f2 = av_q2d(q);
    صحيح fail;

    إذا (isnan(f) || isnan(f2))
        fail = !isnan(f) || !isnan(f2);
    وإلا إذا (isinf(f) || isinf(f2))
        fail = f != f2;
    وإلا
        fail = fabs(f - f2) > fabs(f)/5000000;
    إذا (fail)
        av_log(عدم, AV_LOG_ERROR, "%d/%d %f %f\n", q.انگ, q.den, f, f2);
    أرجع fail;
}

صحيح مکيه(فراغ)
{
    AVRational a,b,r;
    صحيح i,j,k;
    صحيح ret = 0;
    ساكن ثابت int64_t numlist[] = {
        INT64_MIN, INT64_MIN+1, INT64_MAX, INT32_MIN, INT32_MAX, 1,0,-1,
        123456789, INT32_MAX-1, INT32_MAX+1LL, UINT32_MAX-1, UINT32_MAX, UINT32_MAX+1LL
    };

    لكل (a.انگ = -2; a.انگ <= 2; a.انگ++) {
        لكل (a.den = -2; a.den <= 2; a.den++) {
            لكل (b.انگ = -2; b.انگ <= 2; b.انگ++) {
                لكل (b.den = -2; b.den <= 2; b.den++) {
                    صحيح c = av_cmp_q(a,b);
                    مزدوج d = av_q2d(a) == av_q2d(b) ?
                               0 : (av_q2d(a) - av_q2d(b));
                    إذا (d > 0)       d = 1;
                    وإلا إذا (d < 0)  d = -1;
                    وإلا إذا (d != d) d = INT_MIN;
                    إذا (c != d) {
                        av_log(عدم, AV_LOG_ERROR, "%d/%d %d/%d, %d %f\n", a.انگ,
                               a.den, b.انگ, b.den, c,d);
                        ret = 1;
                    }
                    r = av_sub_q(av_جوڙيو_q(b,a), b);
                    إذا(b.den && (r.انگ*a.den != a.انگ*r.den || !r.انگ != !a.انگ || !r.den != !a.den)) {
                        av_log(عدم, AV_LOG_ERROR, "%d/%d ", r.انگ, r.den);
                        ret = 1;
                    }
                }
            }
        }
    }

    /* Check overflow behavior and edge cases */
    ساكن ثابت AVRational unit_mul_q[][3] = {
        {{وڌ_کان_وڌ_عدد, 2},      { 2, 1},            { وڌ_کان_وڌ_عدد, 1}},
        {{وڌ_کان_وڌ_عدد, 2},      {-2, 1},            {-وڌ_کان_وڌ_عدد, 1}},
        {{وڌ_کان_وڌ_عدد, 2},      { 0, 1},            {0, 1}},
        {{INT_MIN, 2},      { 2, 1},            {-وڌ_کان_وڌ_عدد, 1}}, /* not INT_MIN */
        {{INT_MIN, 2},      {-2, 1},            { وڌ_کان_وڌ_عدد, 1}},
        {{INT_MIN, 2},      { 0, 1},            {0, 1}},
        {{وڌ_کان_وڌ_عدد >> 8, 1}, {وڌ_کان_وڌ_عدد >> 8, 1},  {وڌ_کان_وڌ_عدد, 1}},
        {{1, وڌ_کان_وڌ_عدد >> 8}, {1, وڌ_کان_وڌ_عدد >> 8},  {0, 1}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    لكل (i = 0; i < FF_ARRAY_ELEMS(unit_mul_q); i++) {
        لكل (صحيح c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_mul_q[i][c ? 1 : 0];
            AVRational b = unit_mul_q[i][c ? 0 : 1];
            AVRational c = unit_mul_q[i][2];
            AVRational r = av_mul_q(a, b);
            إذا (r.انگ != c.انگ || r.den != c.den) {
                av_log(عدم, AV_LOG_ERROR, "%d/%d * %d/%d = %d/%d, expected %d/%d\n",
                       a.انگ, a.den, b.انگ, b.den, r.انگ, r.den, c.انگ, c.den);
                ret = 1;
            }
        }
    }

    ساكن ثابت AVRational unit_جوڙيو_q[][3] = {
        {{وڌ_کان_وڌ_عدد, 1},      { 2, 2},            { وڌ_کان_وڌ_عدد, 1}},
        {{وڌ_کان_وڌ_عدد, 1},      {-2, 2},            { وڌ_کان_وڌ_عدد - 1, 1}},
        {{وڌ_کان_وڌ_عدد, 1},      { 0, 2},            { وڌ_کان_وڌ_عدد, 1}},
        {{INT_MIN, 1},      { 2, 2},            {-وڌ_کان_وڌ_عدد, 1}},
        {{INT_MIN, 1},      {-2, 2},            {-وڌ_کان_وڌ_عدد, 1}},
        {{INT_MIN, 1},      { 0, 2},            {-وڌ_کان_وڌ_عدد, 1}},
        {{وڌ_کان_وڌ_عدد - 10, 1}, {20, 1},            { وڌ_کان_وڌ_عدد, 1}},
        {{2, وڌ_کان_وڌ_عدد},      {2, وڌ_کان_وڌ_عدد},       {4, وڌ_کان_وڌ_عدد}},
        {{1, 1},            {0, 0},             {0, 0}},
        {{0, 1},            {0, 0},             {0, 0}},
    };

    لكل (i = 0; i < FF_ARRAY_ELEMS(unit_جوڙيو_q); i++) {
        لكل (صحيح c = 0; c < 2; c++) { /* test commutativity */
            AVRational a = unit_جوڙيو_q[i][c ? 1 : 0];
            AVRational b = unit_جوڙيو_q[i][c ? 0 : 1];
            AVRational c = unit_جوڙيو_q[i][2];
            AVRational r = av_جوڙيو_q(a, b);
            إذا (r.انگ != c.انگ || r.den != c.den) {
                av_log(عدم, AV_LOG_ERROR, "%d/%d + %d/%d = %d/%d, expected %d/%d\n",
                       a.انگ, a.den, b.انگ, b.den, r.انگ, r.den, c.انگ, c.den);
                ret = 1;
            }
        }
    }

    لكل (i = 0; i < FF_ARRAY_ELEMS(numlist); i++) {
        int64_t a = numlist[i];

        لكل (j = 0; j < FF_ARRAY_ELEMS(numlist); j++) {
            int64_t b = numlist[j];
            إذا (b<=0)
                استمر;
            لكل (k = 0; k < FF_ARRAY_ELEMS(numlist); k++) {
                int64_t c = numlist[k];
                int64_t res;
                AVInteger ai;

                إذا (c<=0)
                    استمر;
                res = av_rescale_rnd(a,b,c, AV_ڦيرو_ZERO);

                ai = av_mul_i(av_int2i(a), av_int2i(b));
                ai = av_div_i(ai, av_int2i(c));

                إذا (av_cmp_i(ai, av_int2i(INT64_MAX)) > 0 && res == INT64_MIN)
                    استمر;
                إذا (av_cmp_i(ai, av_int2i(INT64_MIN)) < 0 && res == INT64_MIN)
                    استمر;
                إذا (av_cmp_i(ai, av_int2i(res)) == 0)
                    استمر;

                // Special exception for INT64_MIN, remove this in case INT64_MIN is handled without off by 1 error
                إذا (av_cmp_i(ai, av_int2i(res-1)) == 0 && a == INT64_MIN)
                    استمر;

                av_log(عدم, AV_LOG_ERROR, "%"PRId64" * %"PRId64" / %"PRId64" = %"PRId64" or %"PRId64"\n", a,b,c, res, av_i2int(ai));
                ret = 1;
            }
        }
    }

    لكل (a.انگ = 1; a.انگ <= 10; a.انگ++) {
        لكل (a.den = 1; a.den <= 10; a.den++) {
            إذا (av_وڏو_گڏيل_ونڊيندڙ(a.انگ, a.den) > 1)
                استمر;
            لكل (b.انگ = 1; b.انگ <= 10; b.انگ++) {
                لكل (b.den = 1; b.den <= 10; b.den++) {
                    صحيح شروعات;
                    إذا (av_وڏو_گڏيل_ونڊيندڙ(b.انگ, b.den) > 1)
                        استمر;
                    إذا (av_cmp_q(b, a) < 0)
                        استمر;
                    لكل (شروعات = 0; شروعات < 10 ; شروعات++) {
                        صحيح acc= شروعات;
                        صحيح i;

                        لكل (i = 0; i<100; i++) {
                            صحيح exact = شروعات + av_rescale_q(i+1, b, a);
                            acc = av_جوڙيو_stable(a, acc, b, 1);
                            إذا (FFABS(acc - exact) > 2) {
                                av_log(عدم, AV_LOG_ERROR, "%d/%d %d/%d, %d %d\n", a.انگ,
                                       a.den, b.انگ, b.den, acc, exact);
                                أرجع 1;
                            }
                        }
                    }
                }
            }
        }
    }

    لكل (int64_t den = 1; den <= وڌ_کان_وڌ_عدد; den *= 3) {
        a.den = den;
        لكل (a.انگ = -1; a.انگ < (1<<27); a.انگ += 1 + a.انگ/100) {
            إذا (check_q2intfloat(a))
                أرجع 1;
        }
    }

    ساكن ثابت AVRational q2intfloat_list[] = {
        {INT_MIN, 1}, {1, INT_MIN}, {INT_MIN, INT_MIN}, {INT_MIN, -1}, {-1, INT_MIN},
        {وڌ_کان_وڌ_عدد, INT_MIN}, {INT_MIN, وڌ_کان_وڌ_عدد}, {-3, -7}, {3, -7},
        {1, 0}, {-1, 0}, {INT_MIN, 0}, {0, 0}, {0, 1}, {0, INT_MIN},
    };

    لكل (i = 0; i < FF_ARRAY_ELEMS(q2intfloat_list); i++)
        ret |= check_q2intfloat(q2intfloat_list[i]);

    أرجع ret;
}
