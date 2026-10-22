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

#ಅನ್ತರ್ಭಾವ <math.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/csp.h"
#ಅನ್ತರ್ಭಾವ "libavutil/macros.h"
#ಅನ್ತರ್ಭಾವ "libavutil/pixdesc.h"
#ಅನ್ತರ್ಭಾವ "libavutil/pixfmt.h"

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ fuzzy_equal(ದ್ವಿಗುಣ a, ದ್ವಿಗುಣ b)
{
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ epsilon = fmax(fmax(fabs(a), fabs(b)), 1.0) * 1e-7;
    ಹಿಂತಿರುಗಿ fabs(a - b) <= epsilon;
}

#ವ್ಯಾಖ್ಯಾನಿಸು TEST_EOTF(func, ಒಳಹರಿವು, ref) ಮಾಡು                              \
{                                                                   \
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ _b[3] = { (ref)[0], (ref)[1], (ref)[2] };          \
    ದ್ವಿಗುಣ _a[3] = { (ಒಳಹರಿವು)[0], (ಒಳಹರಿವು)[1], (ಒಳಹರಿವು)[2] };          \
    func(Lw, Lb, _a);                                               \
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ _i = 0; _i < 3; _i++) {                                \
        ಆದರೆ (!fuzzy_equal(_a[_i], _b[_i])) {                         \
            ಬರೆ("FAIL: trc=%s %s(%g, %g, %s) != %s\n"            \
                   "  expected {%g, %g, %g}, got {%g, %g, %g}\n",   \
                    trc_name, #func, Lw, Lb, #input, #ref,          \
                    _b[0], _b[1], _b[2], _a[0], _a[1], _a[2]);      \
            ಹಿಂತಿರುಗಿ 1;                                               \
        }                                                           \
    }                                                               \
} ಆಗ (0)

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ *argv[])
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ test_ದತ್ತಾಂಶ[] = {
        -0.1, -0.018053968510807, -0.01, -0.00449, 0.0, 0.00316227760, 0.005,
        0.009, 0.015, 0.1, 1.0, 52.37, 125.098765, 1999.11123, 6945.443,
        15123.4567, 19845.88923, 98678.4231, 99999.899998
    };

    ಗಾಗಿ (ಎಣಿಕೆ AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        ಆದರೆ (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_ತಳ;

        av_csp_trc_function func = av_csp_trc_func_from_id(trc);
        av_csp_trc_function func_inv = av_csp_trc_func_inv_from_id(trc);
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_color_transfer_name(trc);
        ಆದರೆ (!func)
            ಮುಂದುವರಿ;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(test_ದತ್ತಾಂಶ); i++) {
            ದ್ವಿಗುಣ ಫಲಿತಾಂಶ = func(test_ದತ್ತಾಂಶ[i]);
            ದ್ವಿಗುಣ roundtrip = func_inv(ಫಲಿತಾಂಶ);
            ಬರೆ("trc=%s calling func(%f) expected=%f roundtrip=%f\n",
                    name, test_ದತ್ತಾಂಶ[i], ಫಲಿತಾಂಶ, roundtrip);

            ಆದರೆ (ಫಲಿತಾಂಶ > 0.0 && fabs(roundtrip - test_ದತ್ತಾಂಶ[i]) > 1e-7) {
                ಬರೆ("  FAIL\n");
                ಹಿಂತಿರುಗಿ 1;
            }
        }
    }

    ಗಾಗಿ (ಎಣಿಕೆ AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        ಆದರೆ (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_ತಳ;

        av_csp_eotf_function eotf = av_csp_itu_eotf(trc);
        av_csp_eotf_function eotf_inv = av_csp_itu_eotf_inv(trc);
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *trc_name = av_color_transfer_name(trc);
        ಆದರೆ (!eotf)
            ಮುಂದುವರಿ;

        ಆದರೆ (trc == AVCOL_TRC_SMPTE2084) {
            /* This one is equivalent to the TRC already tested above */
            ಮುಂದುವರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (trc == AVCOL_TRC_SMPTE428) {
            /* Test vectors from SMPTE RP-431-2 */
            ಸ್ಥಿರಾಂಕ ರಚನೆ { ದ್ವಿಗುಣ E_xyz[3]; ದ್ವಿಗುಣ luma; } tests[] = {
            #ವ್ಯಾಖ್ಯಾನಿಸು XYZ(X, Y, Z) { X / 4095.0, Y / 4095.0, Z / 4095.0 }
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
            ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ luminance = 48.00;
            ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ contrast = 2000;
            /* Solve for Lw - Lb = luminance, Lw / Lb = contrast */
            ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ Lb = luminance / (contrast - 1);
            ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ Lw = Lb + luminance;

            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(tests); i++) {
                ದ್ವಿಗುಣ L_xyz[3];
                ಸ್ಮರಣೆ_ನಕಲು(L_xyz, tests[i].E_xyz, ಗಾತ್ರ(L_xyz));
                eotf(Lw, Lb, L_xyz);
                ಬರೆ("trc=%s EOTF(%g, %g, {%g, %g, %g}) = {%g, %g %g}, expected Y=%f\n",
                       trc_name, Lw, Lb,
                       tests[i].E_xyz[0], tests[i].E_xyz[1], tests[i].E_xyz[2],
                       L_xyz[0], L_xyz[1], L_xyz[2], tests[i].luma);

                ಆದರೆ (fabs(L_xyz[1] - tests[i].luma) > 0.01) {
                    ಬರೆ("  FAIL\n");
                    ಹಿಂತಿರುಗಿ 1;
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            /* Normal, display-relative RGB curve */
            ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ black_points[] = { 0.0, 1e-6, 0.1, 1.5 };
            ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ white_points[] = { 50.0, 100.0, 203.0, 1000.0, 10000.0 };

            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(black_points); i++) {
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < FF_ARRAY_ELEMS(white_points); j++) {
                    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ Lb = black_points[i];
                    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ Lw = white_points[j];
                    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ all0[3] = { 0.0, 0.0, 0.0 };
                    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ all1[3] = { 1.0, 1.0, 1.0 };
                    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ black[3] = { Lb, Lb, Lb };
                    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ white[3] = { Lw, Lw, Lw };
                    ದ್ವಿಗುಣ L_prev;

                    TEST_EOTF(eotf, all0, black);
                    TEST_EOTF(eotf, all1, white);
                    TEST_EOTF(eotf_inv, black, all0);
                    TEST_EOTF(eotf_inv, white, all1);

                    /* Test round-trip on grayscale ramp */
                    ಗಾಗಿ (ದ್ವಿಗುಣ x = 0.0; x < 1.0; x += 0.1) {
                        ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ E[3] = { x, x, x };
                        ದ್ವಿಗುಣ L[3] = { x, x, x };
                        eotf(Lw, Lb, L);

                        ಬರೆ("trc=%s EOTF(%g, %g, {%g}) = {%g}\n",
                               trc_name, Lw, Lb, E[1], L[1]);
                        TEST_EOTF(eotf_inv, L, E);

                        ಆದರೆ (x > 0.0 && L[1] <= L_prev) {
                            ಬರೆ("  FAIL: non-monotonic!\n");
                            ಹಿಂತಿರುಗಿ 1;
                        }
                        L_prev = L[1];
                    }
                }
            }
        }
    }
}
