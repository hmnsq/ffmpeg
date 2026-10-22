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

#ਅਨ੍ਤਰ੍ਭਾਵ <inttypes.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avutil.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mathematics.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/rational.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    int64_t ਆਖਰੀ;

    /* av_gcd */
    ਲਿਖੋ("Testing av_gcd()\n");
    ਸਥਿਰ ਅਚਲ ਬਣਤਰ { int64_t a, b, expected; } ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ_tests[] = {
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
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ_tests); i++)
        ਲਿਖੋ("gcd(%"PRId64", %"PRId64") = %"PRId64" %s\n",
               ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ_tests[i].a, ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ_tests[i].b,
               av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ(ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ_tests[i].a, ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ_tests[i].b),
               av_ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ(ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ_tests[i].a, ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ_tests[i].b) == ਮਹੱਤਮ_ਸਾਂਝਾ_ਭਾਜਕ_tests[i].expected ? "OK" : "FAIL");

    /* av_rescale */
    ਲਿਖੋ("\nTesting av_rescale()\n");
    ਲਿਖੋ("rescale(6, 3, 2) = %"PRId64"\n", av_rescale(6, 3, 2));
    ਲਿਖੋ("rescale(0, 3, 2) = %"PRId64"\n", av_rescale(0, 3, 2));
    ਲਿਖੋ("rescale(1, 1, 1) = %"PRId64"\n", av_rescale(1, 1, 1));
    ਲਿਖੋ("rescale(-6, 3, 2) = %"PRId64"\n", av_rescale(-6, 3, 2));
    ਲਿਖੋ("rescale(90000, 1, 90000) = %"PRId64"\n", av_rescale(90000, 1, 90000));

    /* av_rescale_rnd with different rounding modes */
    ਲਿਖੋ("\nTesting av_rescale_rnd()\n");
    ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
        int64_t a, b, c;
        ਗਿਣਤੀ AVRounding rnd;
        int64_t expected;
    } rnd_tests[] = {
        {  7,  1,  2, AV_ਗੇੜਾ_ZERO,      3 },
        {  7,  1,  2, AV_ਗੇੜਾ_INF,       4 },
        {  7,  1,  2, AV_ਗੇੜਾ_ਥੱਲੇ,      3 },
        {  7,  1,  2, AV_ਗੇੜਾ_ਉੱਪਰ,        4 },
        {  7,  1,  2, AV_ਗੇੜਾ_NEAR_INF,  4 },
        { -7,  1,  2, AV_ਗੇੜਾ_ZERO,     -3 },
        { -7,  1,  2, AV_ਗੇੜਾ_INF,      -4 },
        { -7,  1,  2, AV_ਗੇੜਾ_ਥੱਲੇ,     -4 },
        { -7,  1,  2, AV_ਗੇੜਾ_ਉੱਪਰ,       -3 },
        {  6,  1,  2, AV_ਗੇੜਾ_NEAR_INF,  3 },
    };
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(rnd_tests); i++) {
        int64_t r = av_rescale_rnd(rnd_tests[i].a, rnd_tests[i].b,
                                   rnd_tests[i].c, rnd_tests[i].rnd);
        ਲਿਖੋ("rescale_rnd(%"PRId64", %"PRId64", %"PRId64", %d) = %"PRId64" %s\n",
               rnd_tests[i].a, rnd_tests[i].b, rnd_tests[i].c,
               rnd_tests[i].rnd, r,
               r == rnd_tests[i].expected ? "OK" : "FAIL");
    }

    /* AV_ROUND_PASS_MINMAX */
    ਲਿਖੋ("\nTesting AV_ROUND_PASS_MINMAX\n");
    ਲਿਖੋ("INT64_MIN passthrough: %s\n",
           av_rescale_rnd(INT64_MIN, 1, 2,
                          AV_ਗੇੜਾ_ਉੱਪਰ | AV_ਗੇੜਾ_PASS_MINMAX) == INT64_MIN ? "OK" : "FAIL");
    ਲਿਖੋ("INT64_MAX passthrough: %s\n",
           av_rescale_rnd(INT64_MAX, 1, 2,
                          AV_ਗੇੜਾ_ਉੱਪਰ | AV_ਗੇੜਾ_PASS_MINMAX) == INT64_MAX ? "OK" : "FAIL");
    ਲਿਖੋ("normal with PASS_MINMAX: %"PRId64"\n",
           av_rescale_rnd(3, 1, 2, AV_ਗੇੜਾ_ਉੱਪਰ | AV_ਗੇੜਾ_PASS_MINMAX));

    /* large value rescale (exercises 128-bit multiply path) */
    ਲਿਖੋ("\nTesting large value rescale\n");
    ਲਿਖੋ("rescale(INT64_MAX/2, 2, 1) = %"PRId64"\n",
           av_rescale_rnd(INT64_MAX / 2, 2, 1, AV_ਗੇੜਾ_ZERO));
    ਲਿਖੋ("rescale(1000000007, 1000000009, 1000000007) = %"PRId64"\n",
           av_rescale(1000000007LL, 1000000009LL, 1000000007LL));
    /* b and c both > INT_MAX triggers 128-bit multiply */
    ਲਿਖੋ("rescale_rnd(10, INT_MAX+1, INT_MAX+1, ZERO) = %"PRId64"\n",
           av_rescale_rnd(10, (int64_t)INT32_MAX + 1, (int64_t)INT32_MAX + 1, AV_ਗੇੜਾ_ZERO));
    ਲਿਖੋ("rescale_rnd(7, 3000000000, 2000000000, NEAR_INF) = %"PRId64"\n",
           av_rescale_rnd(7, 3000000000LL, 2000000000LL, AV_ਗੇੜਾ_NEAR_INF));

    /* av_rescale_q */
    ਲਿਖੋ("\nTesting av_rescale_q()\n");
    ਲਿਖੋ("rescale_q(90000, 1/90000, 1/1000) = %"PRId64"\n",
           av_rescale_q(90000, (AVRational){1, 90000}, (AVRational){1, 1000}));
    ਲਿਖੋ("rescale_q(48000, 1/48000, 1/44100) = %"PRId64"\n",
           av_rescale_q(48000, (AVRational){1, 48000}, (AVRational){1, 44100}));

    /* av_compare_ts */
    ਲਿਖੋ("\nTesting av_compare_ts()\n");
    ਲਿਖੋ("compare(1, 1/1, 1, 1/1) = %d\n",
           av_compare_ts(1, (AVRational){1, 1}, 1, (AVRational){1, 1}));
    ਲਿਖੋ("compare(1, 1/1, 2, 1/1) = %d\n",
           av_compare_ts(1, (AVRational){1, 1}, 2, (AVRational){1, 1}));
    ਲਿਖੋ("compare(2, 1/1, 1, 1/1) = %d\n",
           av_compare_ts(2, (AVRational){1, 1}, 1, (AVRational){1, 1}));
    ਲਿਖੋ("compare(1, 1/1000, 1, 1/90000) = %d\n",
           av_compare_ts(1, (AVRational){1, 1000}, 1, (AVRational){1, 90000}));
    /* large values trigger rescale-based comparison path */
    ਲਿਖੋ("compare(INT64_MAX/2, 1/1, INT64_MAX/3, 1/1) = %d\n",
           av_compare_ts(INT64_MAX / 2, (AVRational){1, 1},
                         INT64_MAX / 3, (AVRational){1, 1}));

    /* av_compare_mod */
    ਲਿਖੋ("\nTesting av_compare_mod()\n");
    ਲਿਖੋ("compare_mod(3, 1, 16) = %"PRId64"\n", av_compare_mod(3, 1, 16));
    ਲਿਖੋ("compare_mod(1, 3, 16) = %"PRId64"\n", av_compare_mod(1, 3, 16));
    ਲਿਖੋ("compare_mod(5, 5, 16) = %"PRId64"\n", av_compare_mod(5, 5, 16));

    /* av_rescale_delta */
    ਲਿਖੋ("\nTesting av_rescale_delta()\n");
    ਆਖਰੀ = AV_NOPTS_ਮੁੱਲ;
    ਲਈ (ਪੂਰਨ i = 0; i < 4; i++)
        ਲਿਖੋ("delta step %d: %"PRId64"\n", i,
               av_rescale_delta((AVRational){1, 48000}, i * 1024,
                                (AVRational){1, 48000}, 1024,
                                &ਆਖਰੀ, (AVRational){1, 44100}));
    /* trigger clip-based path: use different in_tb and fs_tb */
    ਆਖਰੀ = AV_NOPTS_ਮੁੱਲ;
    ਲਈ (ਪੂਰਨ i = 0; i < 4; i++)
        ਲਿਖੋ("delta clip %d: %"PRId64"\n", i,
               av_rescale_delta((AVRational){1, 44100}, i * 940,
                                (AVRational){1, 48000}, 1024,
                                &ਆਖਰੀ, (AVRational){1, 90000}));

    /* av_add_stable */
    ਲਿਖੋ("\nTesting av_add_stable()\n");
    ਲਿਖੋ("add_stable(0, 1/1, 1/1000, 500) = %"PRId64"\n",
           av_ਜੋੜੋ_stable((AVRational){1, 1}, 0, (AVRational){1, 1000}, 500));
    ਲਿਖੋ("add_stable(1000, 1/90000, 1/48000, 1024) = %"PRId64"\n",
           av_ਜੋੜੋ_stable((AVRational){1, 90000}, 1000, (AVRational){1, 48000}, 1024));
    /* non-exact division path (m >= d, general case) */
    ਲਿਖੋ("add_stable(0, 1/48000, 1/90000, 90000) = %"PRId64"\n",
           av_ਜੋੜੋ_stable((AVRational){1, 48000}, 0, (AVRational){1, 90000}, 90000));
    ਲਿਖੋ("add_stable(100, 1/1000, 1/90000, 3000) = %"PRId64"\n",
           av_ਜੋੜੋ_stable((AVRational){1, 1000}, 100, (AVRational){1, 90000}, 3000));
    /* repeated addition: verify no rounding error accumulation */
    {
        int64_t ts = 0;
        ਲਈ (ਪੂਰਨ i = 0; i < 10000; i++)
            ts = av_ਜੋੜੋ_stable((AVRational){1, 48000}, ts, (AVRational){1, 48000}, 1024);
        ਲਿਖੋ("add_stable 10000x1024 at 1/48000: %"PRId64" (expected %"PRId64") %s\n",
               ts, (int64_t)10000 * 1024,
               ts == (int64_t)10000 * 1024 ? "OK" : "FAIL");
    }

    ਵਾਪਸ 0;
}
