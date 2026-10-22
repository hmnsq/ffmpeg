/*
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

#شامل <inttypes.h>
#شامل <stdint.h>
#شامل <stdio.h>

#شامل "libavutil/avutil.h"
#شامل "libavutil/macros.h"
#شامل "libavutil/mathematics.h"
#شامل "libavutil/rational.h"

صحیح مین(خالی)
{
    int64_t آخری;

    /* av_gcd */
    لکھو("Testing av_gcd()\n");
    ساکن ثابت ساخت { int64_t a, b, expected; } عاد_اعظم_tests[] = {
        {   0,   0,  0 },
        {   1,   0,  1 },
        {   0,   1,  1 },
        {   6,   4,  2 },
        {  12,   8,  4 },
        {  17,  13,  1 },
        { 100,  75, 25 },
        {  -6,   4,  2 },
        {   6,  -4,  2 },
    };
    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(عاد_اعظم_tests); i++)
        لکھو("gcd(%"PRId64", %"PRId64") = %"PRId64" %s\n",
               عاد_اعظم_tests[i].a, عاد_اعظم_tests[i].b,
               av_عاد_اعظم(عاد_اعظم_tests[i].a, عاد_اعظم_tests[i].b),
               av_عاد_اعظم(عاد_اعظم_tests[i].a, عاد_اعظم_tests[i].b) == عاد_اعظم_tests[i].expected ? "OK" : "FAIL");

    /* av_rescale */
    لکھو("\nTesting av_rescale()\n");
    لکھو("rescale(6, 3, 2) = %"PRId64"\n", av_rescale(6, 3, 2));
    لکھو("rescale(0, 3, 2) = %"PRId64"\n", av_rescale(0, 3, 2));
    لکھو("rescale(1, 1, 1) = %"PRId64"\n", av_rescale(1, 1, 1));
    لکھو("rescale(-6, 3, 2) = %"PRId64"\n", av_rescale(-6, 3, 2));
    لکھو("rescale(90000, 1, 90000) = %"PRId64"\n", av_rescale(90000, 1, 90000));

    /* av_rescale_rnd with different rounding modes */
    لکھو("\nTesting av_rescale_rnd()\n");
    ساکن ثابت ساخت {
        int64_t a, b, c;
        شمار AVRounding rnd;
        int64_t expected;
    } rnd_tests[] = {
        {  7,  1,  2, AV_باری_ZERO,      3 },
        {  7,  1,  2, AV_باری_INF,       4 },
        {  7,  1,  2, AV_باری_نیچے_کو,      3 },
        {  7,  1,  2, AV_باری_اوپر,        4 },
        {  7,  1,  2, AV_باری_NEAR_INF,  4 },
        { -7,  1,  2, AV_باری_ZERO,     -3 },
        { -7,  1,  2, AV_باری_INF,      -4 },
        { -7,  1,  2, AV_باری_نیچے_کو,     -4 },
        { -7,  1,  2, AV_باری_اوپر,       -3 },
        {  6,  1,  2, AV_باری_NEAR_INF,  3 },
    };
    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(rnd_tests); i++) {
        int64_t r = av_rescale_rnd(rnd_tests[i].a, rnd_tests[i].b,
                                   rnd_tests[i].c, rnd_tests[i].rnd);
        لکھو("rescale_rnd(%"PRId64", %"PRId64", %"PRId64", %d) = %"PRId64" %s\n",
               rnd_tests[i].a, rnd_tests[i].b, rnd_tests[i].c,
               rnd_tests[i].rnd, r,
               r == rnd_tests[i].expected ? "OK" : "FAIL");
    }

    /* AV_ROUND_PASS_MINMAX */
    لکھو("\nTesting AV_ROUND_PASS_MINMAX\n");
    لکھو("INT64_MIN passthrough: %s\n",
           av_rescale_rnd(INT64_MIN, 1, 2,
                          AV_باری_اوپر | AV_باری_PASS_MINMAX) == INT64_MIN ? "OK" : "FAIL");
    لکھو("INT64_MAX passthrough: %s\n",
           av_rescale_rnd(INT64_MAX, 1, 2,
                          AV_باری_اوپر | AV_باری_PASS_MINMAX) == INT64_MAX ? "OK" : "FAIL");
    لکھو("normal with PASS_MINMAX: %"PRId64"\n",
           av_rescale_rnd(3, 1, 2, AV_باری_اوپر | AV_باری_PASS_MINMAX));

    /* large value rescale (exercises 128-bit multiply path) */
    لکھو("\nTesting large value rescale\n");
    لکھو("rescale(INT64_MAX/2, 2, 1) = %"PRId64"\n",
           av_rescale_rnd(INT64_MAX / 2, 2, 1, AV_باری_ZERO));
    لکھو("rescale(1000000007, 1000000009, 1000000007) = %"PRId64"\n",
           av_rescale(1000000007LL, 1000000009LL, 1000000007LL));
    /* b and c both > INT_MAX triggers 128-bit multiply */
    لکھو("rescale_rnd(10, INT_MAX+1, INT_MAX+1, ZERO) = %"PRId64"\n",
           av_rescale_rnd(10, (int64_t)INT32_MAX + 1, (int64_t)INT32_MAX + 1, AV_باری_ZERO));
    لکھو("rescale_rnd(7, 3000000000, 2000000000, NEAR_INF) = %"PRId64"\n",
           av_rescale_rnd(7, 3000000000LL, 2000000000LL, AV_باری_NEAR_INF));

    /* av_rescale_q */
    لکھو("\nTesting av_rescale_q()\n");
    لکھو("rescale_q(90000, 1/90000, 1/1000) = %"PRId64"\n",
           av_rescale_q(90000, (AVRational){1, 90000}, (AVRational){1, 1000}));
    لکھو("rescale_q(48000, 1/48000, 1/44100) = %"PRId64"\n",
           av_rescale_q(48000, (AVRational){1, 48000}, (AVRational){1, 44100}));

    /* av_compare_ts */
    لکھو("\nTesting av_compare_ts()\n");
    لکھو("compare(1, 1/1, 1, 1/1) = %d\n",
           av_compare_ts(1, (AVRational){1, 1}, 1, (AVRational){1, 1}));
    لکھو("compare(1, 1/1, 2, 1/1) = %d\n",
           av_compare_ts(1, (AVRational){1, 1}, 2, (AVRational){1, 1}));
    لکھو("compare(2, 1/1, 1, 1/1) = %d\n",
           av_compare_ts(2, (AVRational){1, 1}, 1, (AVRational){1, 1}));
    لکھو("compare(1, 1/1000, 1, 1/90000) = %d\n",
           av_compare_ts(1, (AVRational){1, 1000}, 1, (AVRational){1, 90000}));
    /* large values trigger rescale-based comparison path */
    لکھو("compare(INT64_MAX/2, 1/1, INT64_MAX/3, 1/1) = %d\n",
           av_compare_ts(INT64_MAX / 2, (AVRational){1, 1},
                         INT64_MAX / 3, (AVRational){1, 1}));

    /* av_compare_mod */
    لکھو("\nTesting av_compare_mod()\n");
    لکھو("compare_mod(3, 1, 16) = %"PRId64"\n", av_compare_mod(3, 1, 16));
    لکھو("compare_mod(1, 3, 16) = %"PRId64"\n", av_compare_mod(1, 3, 16));
    لکھو("compare_mod(5, 5, 16) = %"PRId64"\n", av_compare_mod(5, 5, 16));

    /* av_rescale_delta */
    لکھو("\nTesting av_rescale_delta()\n");
    آخری = AV_NOPTS_قدر;
    برائے (صحیح i = 0; i < 4; i++)
        لکھو("delta step %d: %"PRId64"\n", i,
               av_rescale_delta((AVRational){1, 48000}, i * 1024,
                                (AVRational){1, 48000}, 1024,
                                &آخری, (AVRational){1, 44100}));
    /* trigger clip-based path: use different in_tb and fs_tb */
    آخری = AV_NOPTS_قدر;
    برائے (صحیح i = 0; i < 4; i++)
        لکھو("delta clip %d: %"PRId64"\n", i,
               av_rescale_delta((AVRational){1, 44100}, i * 940,
                                (AVRational){1, 48000}, 1024,
                                &آخری, (AVRational){1, 90000}));

    /* av_add_stable */
    لکھو("\nTesting av_add_stable()\n");
    لکھو("add_stable(0, 1/1, 1/1000, 500) = %"PRId64"\n",
           av_جوڑو_stable((AVRational){1, 1}, 0, (AVRational){1, 1000}, 500));
    لکھو("add_stable(1000, 1/90000, 1/48000, 1024) = %"PRId64"\n",
           av_جوڑو_stable((AVRational){1, 90000}, 1000, (AVRational){1, 48000}, 1024));
    /* non-exact division path (m >= d, general case) */
    لکھو("add_stable(0, 1/48000, 1/90000, 90000) = %"PRId64"\n",
           av_جوڑو_stable((AVRational){1, 48000}, 0, (AVRational){1, 90000}, 90000));
    لکھو("add_stable(100, 1/1000, 1/90000, 3000) = %"PRId64"\n",
           av_جوڑو_stable((AVRational){1, 1000}, 100, (AVRational){1, 90000}, 3000));
    /* repeated addition: verify no rounding error accumulation */
    {
        int64_t ts = 0;
        برائے (صحیح i = 0; i < 10000; i++)
            ts = av_جوڑو_stable((AVRational){1, 48000}, ts, (AVRational){1, 48000}, 1024);
        لکھو("add_stable 10000x1024 at 1/48000: %"PRId64" (expected %"PRId64") %s\n",
               ts, (int64_t)10000 * 1024,
               ts == (int64_t)10000 * 1024 ? "OK" : "FAIL");
    }

    واپس 0;
}
