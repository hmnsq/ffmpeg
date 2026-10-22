/*
 * Copyright (c) 2015 Kevin Wheatley <kevin.j.wheatley@gmail.com>
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

#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/csp.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixfmt.h"

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ fuzzy_equal(ਦੁੱਗਣਾ a, ਦੁੱਗਣਾ b)
{
    ਅਚਲ ਦੁੱਗਣਾ epsilon = fmax(fmax(fabs(a), fabs(b)), 1.0) * 1e-7;
    ਵਾਪਸ fabs(a - b) <= epsilon;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST_EOTF(func, ਨਿਵੇਸ਼, ref) ਕਰੋ                              \
{                                                                   \
    ਅਚਲ ਦੁੱਗਣਾ _b[3] = { (ref)[0], (ref)[1], (ref)[2] };          \
    ਦੁੱਗਣਾ _a[3] = { (ਨਿਵੇਸ਼)[0], (ਨਿਵੇਸ਼)[1], (ਨਿਵੇਸ਼)[2] };          \
    func(Lw, Lb, _a);                                               \
    ਲਈ (ਪੂਰਨ _i = 0; _i < 3; _i++) {                                \
        ਜੇ (!fuzzy_equal(_a[_i], _b[_i])) {                         \
            ਲਿਖੋ("FAIL: trc=%s %s(%g, %g, %s) != %s\n"            \
                   "  expected {%g, %g, %g}, got {%g, %g, %g}\n",   \
                    trc_name, #func, Lw, Lb, #input, #ref,          \
                    _b[0], _b[1], _b[2], _a[0], _a[1], _a[2]);      \
            ਵਾਪਸ 1;                                               \
        }                                                           \
    }                                                               \
} ਜਦੋਂ (0)

ਪੂਰਨ ਮੁੱਖ(ਪੂਰਨ argc, ਅੱਖਰ *argv[])
{
    ਸਥਿਰ ਅਚਲ ਦੁੱਗਣਾ test_ਅੰਕੜੇ[] = {
        -0.1, -0.018053968510807, -0.01, -0.00449, 0.0, 0.00316227760, 0.005,
        0.009, 0.015, 0.1, 1.0, 52.37, 125.098765, 1999.11123, 6945.443,
        15123.4567, 19845.88923, 98678.4231, 99999.899998
    };

    ਲਈ (ਗਿਣਤੀ AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        ਜੇ (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_ਅਧਾਰ;

        av_csp_trc_function func = av_csp_trc_func_from_id(trc);
        av_csp_trc_function func_inv = av_csp_trc_func_inv_from_id(trc);
        ਅਚਲ ਅੱਖਰ *name = av_color_transfer_name(trc);
        ਜੇ (!func)
            ਜਾਰੀ;

        ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(test_ਅੰਕੜੇ); i++) {
            ਦੁੱਗਣਾ ਨਤੀਜਾ = func(test_ਅੰਕੜੇ[i]);
            ਦੁੱਗਣਾ roundtrip = func_inv(ਨਤੀਜਾ);
            ਲਿਖੋ("trc=%s calling func(%f) expected=%f roundtrip=%f\n",
                    name, test_ਅੰਕੜੇ[i], ਨਤੀਜਾ, roundtrip);

            ਜੇ (ਨਤੀਜਾ > 0.0 && fabs(roundtrip - test_ਅੰਕੜੇ[i]) > 1e-7) {
                ਲਿਖੋ("  FAIL\n");
                ਵਾਪਸ 1;
            }
        }
    }

    ਲਈ (ਗਿਣਤੀ AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        ਜੇ (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_ਅਧਾਰ;

        av_csp_eotf_function eotf = av_csp_itu_eotf(trc);
        av_csp_eotf_function eotf_inv = av_csp_itu_eotf_inv(trc);
        ਅਚਲ ਅੱਖਰ *trc_name = av_color_transfer_name(trc);
        ਜੇ (!eotf)
            ਜਾਰੀ;

        ਜੇ (trc == AVCOL_TRC_SMPTE2084) {
            /* This one is equivalent to the TRC already tested above */
            ਜਾਰੀ;
        } ਨਹੀਂਤਾਂ ਜੇ (trc == AVCOL_TRC_SMPTE428) {
            /* Test vectors from SMPTE RP-431-2 */
            ਅਚਲ ਬਣਤਰ { ਦੁੱਗਣਾ E_xyz[3]; ਦੁੱਗਣਾ luma; } tests[] = {
            #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XYZ(X, Y, Z) { X / 4095.0, Y / 4095.0, Z / 4095.0 }
                { XYZ( 379,  396,  389),  0.14 },
                { XYZ( 759,  792,  778),  0.75 },
                { XYZ(1138, 1188, 1167),  2.12 },
                { XYZ(1518, 1584, 1556),  4.45 },
                { XYZ(1897, 1980, 1945),  7.94 },
                { XYZ(2276, 2376, 2334), 12.74 },
                { XYZ(2656, 2772, 2723), 19.01 },
                { XYZ(3035, 3168, 3112), 26.89 },
                { XYZ(3415, 3564, 3501), 36.52 },
                { XYZ(3794, 3960, 3890), 48.02 },
            };
            /* DCI reference display */
            ਅਚਲ ਦੁੱਗਣਾ luminance = 48.00;
            ਅਚਲ ਦੁੱਗਣਾ contrast = 2000;
            /* Solve for Lw - Lb = luminance, Lw / Lb = contrast */
            ਅਚਲ ਦੁੱਗਣਾ Lb = luminance / (contrast - 1);
            ਅਚਲ ਦੁੱਗਣਾ Lw = Lb + luminance;

            ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(tests); i++) {
                ਦੁੱਗਣਾ L_xyz[3];
                ਸਮ੍ਰਿਤੀ_ਨਕਲ(L_xyz, tests[i].E_xyz, ਆਕਾਰ(L_xyz));
                eotf(Lw, Lb, L_xyz);
                ਲਿਖੋ("trc=%s EOTF(%g, %g, {%g, %g, %g}) = {%g, %g %g}, expected Y=%f\n",
                       trc_name, Lw, Lb,
                       tests[i].E_xyz[0], tests[i].E_xyz[1], tests[i].E_xyz[2],
                       L_xyz[0], L_xyz[1], L_xyz[2], tests[i].luma);

                ਜੇ (fabs(L_xyz[1] - tests[i].luma) > 0.01) {
                    ਲਿਖੋ("  FAIL\n");
                    ਵਾਪਸ 1;
                }
            }
        } ਨਹੀਂਤਾਂ {
            /* Normal, display-relative RGB curve */
            ਸਥਿਰ ਅਚਲ ਦੁੱਗਣਾ black_points[] = { 0.0, 1e-6, 0.1, 1.5 };
            ਸਥਿਰ ਅਚਲ ਦੁੱਗਣਾ white_points[] = { 50.0, 100.0, 203.0, 1000.0, 10000.0 };

            ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(black_points); i++) {
                ਲਈ (ਪੂਰਨ j = 0; j < FF_ARRAY_ELEMS(white_points); j++) {
                    ਅਚਲ ਦੁੱਗਣਾ Lb = black_points[i];
                    ਅਚਲ ਦੁੱਗਣਾ Lw = white_points[j];
                    ਅਚਲ ਦੁੱਗਣਾ all0[3] = { 0.0, 0.0, 0.0 };
                    ਅਚਲ ਦੁੱਗਣਾ all1[3] = { 1.0, 1.0, 1.0 };
                    ਅਚਲ ਦੁੱਗਣਾ black[3] = { Lb, Lb, Lb };
                    ਅਚਲ ਦੁੱਗਣਾ white[3] = { Lw, Lw, Lw };
                    ਦੁੱਗਣਾ L_prev;

                    TEST_EOTF(eotf, all0, black);
                    TEST_EOTF(eotf, all1, white);
                    TEST_EOTF(eotf_inv, black, all0);
                    TEST_EOTF(eotf_inv, white, all1);

                    /* Test round-trip on grayscale ramp */
                    ਲਈ (ਦੁੱਗਣਾ x = 0.0; x < 1.0; x += 0.1) {
                        ਅਚਲ ਦੁੱਗਣਾ E[3] = { x, x, x };
                        ਦੁੱਗਣਾ L[3] = { x, x, x };
                        eotf(Lw, Lb, L);

                        ਲਿਖੋ("trc=%s EOTF(%g, %g, {%g}) = {%g}\n",
                               trc_name, Lw, Lb, E[1], L[1]);
                        TEST_EOTF(eotf_inv, L, E);

                        ਜੇ (x > 0.0 && L[1] <= L_prev) {
                            ਲਿਖੋ("  FAIL: non-monotonic!\n");
                            ਵਾਪਸ 1;
                        }
                        L_prev = L[1];
                    }
                }
            }
        }
    }
}
