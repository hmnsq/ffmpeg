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

#అన్తర్భావ <math.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/csp.h"
#అన్తర్భావ "libavutil/macros.h"
#అన్తర్భావ "libavutil/pixdesc.h"
#అన్తర్భావ "libavutil/pixfmt.h"

స్థిర అంతఃవరుస పూర్ణాంకం fuzzy_equal(ద్విగుణ a, ద్విగుణ b)
{
    స్థిరరాశి ద్విగుణ epsilon = fmax(fmax(fabs(a), fabs(b)), 1.0) * 1e-7;
    తిరిగి fabs(a - b) <= epsilon;
}

#నిర్వచించు TEST_EOTF(func, ఆదానం, ref) చేయి                              \
{                                                                   \
    స్థిరరాశి ద్విగుణ _b[3] = { (ref)[0], (ref)[1], (ref)[2] };          \
    ద్విగుణ _a[3] = { (ఆదానం)[0], (ఆదానం)[1], (ఆదానం)[2] };          \
    func(Lw, Lb, _a);                                               \
    కొరకు (పూర్ణాంకం _i = 0; _i < 3; _i++) {                                \
        ఒకవేళ (!fuzzy_equal(_a[_i], _b[_i])) {                         \
            రాయి("FAIL: trc=%s %s(%g, %g, %s) != %s\n"            \
                   "  expected {%g, %g, %g}, got {%g, %g, %g}\n",   \
                    trc_name, #func, Lw, Lb, #input, #ref,          \
                    _b[0], _b[1], _b[2], _a[0], _a[1], _a[2]);      \
            తిరిగి 1;                                               \
        }                                                           \
    }                                                               \
} అయితే (0)

పూర్ణాంకం ప్రధాన(పూర్ణాంకం argc, అక్షరం *argv[])
{
    స్థిర స్థిరరాశి ద్విగుణ test_దత్తాంశం[] = {
        -0.1, -0.018053968510807, -0.01, -0.00449, 0.0, 0.00316227760, 0.005,
        0.009, 0.015, 0.1, 1.0, 52.37, 125.098765, 1999.11123, 6945.443,
        15123.4567, 19845.88923, 98678.4231, 99999.899998
    };

    కొరకు (గణన AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        ఒకవేళ (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_పునాది;

        av_csp_trc_function func = av_csp_trc_func_from_id(trc);
        av_csp_trc_function func_inv = av_csp_trc_func_inv_from_id(trc);
        స్థిరరాశి అక్షరం *name = av_color_transfer_name(trc);
        ఒకవేళ (!func)
            కొనసాగు;

        కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(test_దత్తాంశం); i++) {
            ద్విగుణ ఫలితం = func(test_దత్తాంశం[i]);
            ద్విగుణ roundtrip = func_inv(ఫలితం);
            రాయి("trc=%s calling func(%f) expected=%f roundtrip=%f\n",
                    name, test_దత్తాంశం[i], ఫలితం, roundtrip);

            ఒకవేళ (ఫలితం > 0.0 && fabs(roundtrip - test_దత్తాంశం[i]) > 1e-7) {
                రాయి("  FAIL\n");
                తిరిగి 1;
            }
        }
    }

    కొరకు (గణన AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        ఒకవేళ (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_పునాది;

        av_csp_eotf_function eotf = av_csp_itu_eotf(trc);
        av_csp_eotf_function eotf_inv = av_csp_itu_eotf_inv(trc);
        స్థిరరాశి అక్షరం *trc_name = av_color_transfer_name(trc);
        ఒకవేళ (!eotf)
            కొనసాగు;

        ఒకవేళ (trc == AVCOL_TRC_SMPTE2084) {
            /* This one is equivalent to the TRC already tested above */
            కొనసాగు;
        } లేకపోతే ఒకవేళ (trc == AVCOL_TRC_SMPTE428) {
            /* Test vectors from SMPTE RP-431-2 */
            స్థిరరాశి నిర్మాణం { ద్విగుణ E_xyz[3]; ద్విగుణ luma; } tests[] = {
            #నిర్వచించు XYZ(X, Y, Z) { X / 4095.0, Y / 4095.0, Z / 4095.0 }
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
            స్థిరరాశి ద్విగుణ luminance = 48.00;
            స్థిరరాశి ద్విగుణ contrast = 2000;
            /* Solve for Lw - Lb = luminance, Lw / Lb = contrast */
            స్థిరరాశి ద్విగుణ Lb = luminance / (contrast - 1);
            స్థిరరాశి ద్విగుణ Lw = Lb + luminance;

            కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(tests); i++) {
                ద్విగుణ L_xyz[3];
                జ్ఞాపకం_నకలు(L_xyz, tests[i].E_xyz, పరిమాణం(L_xyz));
                eotf(Lw, Lb, L_xyz);
                రాయి("trc=%s EOTF(%g, %g, {%g, %g, %g}) = {%g, %g %g}, expected Y=%f\n",
                       trc_name, Lw, Lb,
                       tests[i].E_xyz[0], tests[i].E_xyz[1], tests[i].E_xyz[2],
                       L_xyz[0], L_xyz[1], L_xyz[2], tests[i].luma);

                ఒకవేళ (fabs(L_xyz[1] - tests[i].luma) > 0.01) {
                    రాయి("  FAIL\n");
                    తిరిగి 1;
                }
            }
        } లేకపోతే {
            /* Normal, display-relative RGB curve */
            స్థిర స్థిరరాశి ద్విగుణ black_points[] = { 0.0, 1e-6, 0.1, 1.5 };
            స్థిర స్థిరరాశి ద్విగుణ white_points[] = { 50.0, 100.0, 203.0, 1000.0, 10000.0 };

            కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(black_points); i++) {
                కొరకు (పూర్ణాంకం j = 0; j < FF_ARRAY_ELEMS(white_points); j++) {
                    స్థిరరాశి ద్విగుణ Lb = black_points[i];
                    స్థిరరాశి ద్విగుణ Lw = white_points[j];
                    స్థిరరాశి ద్విగుణ all0[3] = { 0.0, 0.0, 0.0 };
                    స్థిరరాశి ద్విగుణ all1[3] = { 1.0, 1.0, 1.0 };
                    స్థిరరాశి ద్విగుణ black[3] = { Lb, Lb, Lb };
                    స్థిరరాశి ద్విగుణ white[3] = { Lw, Lw, Lw };
                    ద్విగుణ L_prev;

                    TEST_EOTF(eotf, all0, black);
                    TEST_EOTF(eotf, all1, white);
                    TEST_EOTF(eotf_inv, black, all0);
                    TEST_EOTF(eotf_inv, white, all1);

                    /* Test round-trip on grayscale ramp */
                    కొరకు (ద్విగుణ x = 0.0; x < 1.0; x += 0.1) {
                        స్థిరరాశి ద్విగుణ E[3] = { x, x, x };
                        ద్విగుణ L[3] = { x, x, x };
                        eotf(Lw, Lb, L);

                        రాయి("trc=%s EOTF(%g, %g, {%g}) = {%g}\n",
                               trc_name, Lw, Lb, E[1], L[1]);
                        TEST_EOTF(eotf_inv, L, E);

                        ఒకవేళ (x > 0.0 && L[1] <= L_prev) {
                            రాయి("  FAIL: non-monotonic!\n");
                            తిరిగి 1;
                        }
                        L_prev = L[1];
                    }
                }
            }
        }
    }
}
