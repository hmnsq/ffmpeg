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

#ಅನ್ತರ್ಭಾವ <inttypes.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/avutil.h"
#ಅನ್ತರ್ಭಾವ "libavutil/macros.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mathematics.h"
#ಅನ್ತರ್ಭಾವ "libavutil/rational.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    int64_t ಕೊನೆಯ;

    /* av_gcd */
    ಬರೆ("Testing av_gcd()\n");
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ { int64_t a, b, expected; } ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ_tests[] = {
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
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ_tests); i++)
        ಬರೆ("gcd(%"PRId64", %"PRId64") = %"PRId64" %s\n",
               ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ_tests[i].a, ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ_tests[i].b,
               av_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ(ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ_tests[i].a, ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ_tests[i].b),
               av_ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ(ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ_tests[i].a, ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ_tests[i].b) == ಮಹತ್ತಮ_ಸಾಮಾನ್ಯ_ಅಪವರ್ತನ_tests[i].expected ? "OK" : "FAIL");

    /* av_rescale */
    ಬರೆ("\nTesting av_rescale()\n");
    ಬರೆ("rescale(6, 3, 2) = %"PRId64"\n", av_rescale(6, 3, 2));
    ಬರೆ("rescale(0, 3, 2) = %"PRId64"\n", av_rescale(0, 3, 2));
    ಬರೆ("rescale(1, 1, 1) = %"PRId64"\n", av_rescale(1, 1, 1));
    ಬರೆ("rescale(-6, 3, 2) = %"PRId64"\n", av_rescale(-6, 3, 2));
    ಬರೆ("rescale(90000, 1, 90000) = %"PRId64"\n", av_rescale(90000, 1, 90000));

    /* av_rescale_rnd with different rounding modes */
    ಬರೆ("\nTesting av_rescale_rnd()\n");
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
        int64_t a, b, c;
        ಎಣಿಕೆ AVRounding rnd;
        int64_t expected;
    } rnd_tests[] = {
        {  7,  1,  2, AV_ಸುತ್ತು_ZERO,      3 },
        {  7,  1,  2, AV_ಸುತ್ತು_INF,       4 },
        {  7,  1,  2, AV_ಸುತ್ತು_ಕೆಳಕ್ಕೆ,      3 },
        {  7,  1,  2, AV_ಸುತ್ತು_ಮೇಲೆ,        4 },
        {  7,  1,  2, AV_ಸುತ್ತು_NEAR_INF,  4 },
        { -7,  1,  2, AV_ಸುತ್ತು_ZERO,     -3 },
        { -7,  1,  2, AV_ಸುತ್ತು_INF,      -4 },
        { -7,  1,  2, AV_ಸುತ್ತು_ಕೆಳಕ್ಕೆ,     -4 },
        { -7,  1,  2, AV_ಸುತ್ತು_ಮೇಲೆ,       -3 },
        {  6,  1,  2, AV_ಸುತ್ತು_NEAR_INF,  3 },
    };
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(rnd_tests); i++) {
        int64_t r = av_rescale_rnd(rnd_tests[i].a, rnd_tests[i].b,
                                   rnd_tests[i].c, rnd_tests[i].rnd);
        ಬರೆ("rescale_rnd(%"PRId64", %"PRId64", %"PRId64", %d) = %"PRId64" %s\n",
               rnd_tests[i].a, rnd_tests[i].b, rnd_tests[i].c,
               rnd_tests[i].rnd, r,
               r == rnd_tests[i].expected ? "OK" : "FAIL");
    }

    /* AV_ROUND_PASS_MINMAX */
    ಬರೆ("\nTesting AV_ROUND_PASS_MINMAX\n");
    ಬರೆ("INT64_MIN passthrough: %s\n",
           av_rescale_rnd(INT64_MIN, 1, 2,
                          AV_ಸುತ್ತು_ಮೇಲೆ | AV_ಸುತ್ತು_PASS_MINMAX) == INT64_MIN ? "OK" : "FAIL");
    ಬರೆ("INT64_MAX passthrough: %s\n",
           av_rescale_rnd(INT64_MAX, 1, 2,
                          AV_ಸುತ್ತು_ಮೇಲೆ | AV_ಸುತ್ತು_PASS_MINMAX) == INT64_MAX ? "OK" : "FAIL");
    ಬರೆ("normal with PASS_MINMAX: %"PRId64"\n",
           av_rescale_rnd(3, 1, 2, AV_ಸುತ್ತು_ಮೇಲೆ | AV_ಸುತ್ತು_PASS_MINMAX));

    /* large value rescale (exercises 128-bit multiply path) */
    ಬರೆ("\nTesting large value rescale\n");
    ಬರೆ("rescale(INT64_MAX/2, 2, 1) = %"PRId64"\n",
           av_rescale_rnd(INT64_MAX / 2, 2, 1, AV_ಸುತ್ತು_ZERO));
    ಬರೆ("rescale(1000000007, 1000000009, 1000000007) = %"PRId64"\n",
           av_rescale(1000000007LL, 1000000009LL, 1000000007LL));
    /* b and c both > INT_MAX triggers 128-bit multiply */
    ಬರೆ("rescale_rnd(10, INT_MAX+1, INT_MAX+1, ZERO) = %"PRId64"\n",
           av_rescale_rnd(10, (int64_t)INT32_MAX + 1, (int64_t)INT32_MAX + 1, AV_ಸುತ್ತು_ZERO));
    ಬರೆ("rescale_rnd(7, 3000000000, 2000000000, NEAR_INF) = %"PRId64"\n",
           av_rescale_rnd(7, 3000000000LL, 2000000000LL, AV_ಸುತ್ತು_NEAR_INF));

    /* av_rescale_q */
    ಬರೆ("\nTesting av_rescale_q()\n");
    ಬರೆ("rescale_q(90000, 1/90000, 1/1000) = %"PRId64"\n",
           av_rescale_q(90000, (AVRational){1, 90000}, (AVRational){1, 1000}));
    ಬರೆ("rescale_q(48000, 1/48000, 1/44100) = %"PRId64"\n",
           av_rescale_q(48000, (AVRational){1, 48000}, (AVRational){1, 44100}));

    /* av_compare_ts */
    ಬರೆ("\nTesting av_compare_ts()\n");
    ಬರೆ("compare(1, 1/1, 1, 1/1) = %d\n",
           av_compare_ts(1, (AVRational){1, 1}, 1, (AVRational){1, 1}));
    ಬರೆ("compare(1, 1/1, 2, 1/1) = %d\n",
           av_compare_ts(1, (AVRational){1, 1}, 2, (AVRational){1, 1}));
    ಬರೆ("compare(2, 1/1, 1, 1/1) = %d\n",
           av_compare_ts(2, (AVRational){1, 1}, 1, (AVRational){1, 1}));
    ಬರೆ("compare(1, 1/1000, 1, 1/90000) = %d\n",
           av_compare_ts(1, (AVRational){1, 1000}, 1, (AVRational){1, 90000}));
    /* large values trigger rescale-based comparison path */
    ಬರೆ("compare(INT64_MAX/2, 1/1, INT64_MAX/3, 1/1) = %d\n",
           av_compare_ts(INT64_MAX / 2, (AVRational){1, 1},
                         INT64_MAX / 3, (AVRational){1, 1}));

    /* av_compare_mod */
    ಬರೆ("\nTesting av_compare_mod()\n");
    ಬರೆ("compare_mod(3, 1, 16) = %"PRId64"\n", av_compare_mod(3, 1, 16));
    ಬರೆ("compare_mod(1, 3, 16) = %"PRId64"\n", av_compare_mod(1, 3, 16));
    ಬರೆ("compare_mod(5, 5, 16) = %"PRId64"\n", av_compare_mod(5, 5, 16));

    /* av_rescale_delta */
    ಬರೆ("\nTesting av_rescale_delta()\n");
    ಕೊನೆಯ = AV_NOPTS_ಮೌಲ್ಯ;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 4; i++)
        ಬರೆ("delta step %d: %"PRId64"\n", i,
               av_rescale_delta((AVRational){1, 48000}, i * 1024,
                                (AVRational){1, 48000}, 1024,
                                &ಕೊನೆಯ, (AVRational){1, 44100}));
    /* trigger clip-based path: use different in_tb and fs_tb */
    ಕೊನೆಯ = AV_NOPTS_ಮೌಲ್ಯ;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 4; i++)
        ಬರೆ("delta clip %d: %"PRId64"\n", i,
               av_rescale_delta((AVRational){1, 44100}, i * 940,
                                (AVRational){1, 48000}, 1024,
                                &ಕೊನೆಯ, (AVRational){1, 90000}));

    /* av_add_stable */
    ಬರೆ("\nTesting av_add_stable()\n");
    ಬರೆ("add_stable(0, 1/1, 1/1000, 500) = %"PRId64"\n",
           av_ಕೂಡಿಸು_stable((AVRational){1, 1}, 0, (AVRational){1, 1000}, 500));
    ಬರೆ("add_stable(1000, 1/90000, 1/48000, 1024) = %"PRId64"\n",
           av_ಕೂಡಿಸು_stable((AVRational){1, 90000}, 1000, (AVRational){1, 48000}, 1024));
    /* non-exact division path (m >= d, general case) */
    ಬರೆ("add_stable(0, 1/48000, 1/90000, 90000) = %"PRId64"\n",
           av_ಕೂಡಿಸು_stable((AVRational){1, 48000}, 0, (AVRational){1, 90000}, 90000));
    ಬರೆ("add_stable(100, 1/1000, 1/90000, 3000) = %"PRId64"\n",
           av_ಕೂಡಿಸು_stable((AVRational){1, 1000}, 100, (AVRational){1, 90000}, 3000));
    /* repeated addition: verify no rounding error accumulation */
    {
        int64_t ts = 0;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 10000; i++)
            ts = av_ಕೂಡಿಸು_stable((AVRational){1, 48000}, ts, (AVRational){1, 48000}, 1024);
        ಬರೆ("add_stable 10000x1024 at 1/48000: %"PRId64" (expected %"PRId64") %s\n",
               ts, (int64_t)10000 * 1024,
               ts == (int64_t)10000 * 1024 ? "OK" : "FAIL");
    }

    ಹಿಂತಿರುಗಿ 0;
}
