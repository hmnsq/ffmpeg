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

#ضمن <math.h>
#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "libavutil/csp.h"
#ضمن "libavutil/macros.h"
#ضمن "libavutil/pixdesc.h"
#ضمن "libavutil/pixfmt.h"

ساكن مضمن صحيح fuzzy_equal(مزدوج a, مزدوج b)
{
    ثابت مزدوج epsilon = fmax(fmax(fabs(a), fabs(b)), 1.0) * 1e-7;
    أرجع fabs(a - b) <= epsilon;
}

#define TEST_EOTF(func, داخلہ, ref) افعل                              \
{                                                                   \
    ثابت مزدوج _b[3] = { (ref)[0], (ref)[1], (ref)[2] };          \
    مزدوج _a[3] = { (داخلہ)[0], (داخلہ)[1], (داخلہ)[2] };          \
    func(Lw, Lb, _a);                                               \
    لكل (صحيح _i = 0; _i < 3; _i++) {                                \
        إذا (!fuzzy_equal(_a[_i], _b[_i])) {                         \
            printf("FAIL: trc=%s %s(%g, %g, %s) != %s\n"            \
                   "  expected {%g, %g, %g}, got {%g, %g, %g}\n",   \
                    trc_name, #func, Lw, Lb, #input, #ref,          \
                    _b[0], _b[1], _b[2], _a[0], _a[1], _a[2]);      \
            أرجع 1;                                               \
        }                                                           \
    }                                                               \
} طالما (0)

صحيح main(صحيح argc, حرف *argv[])
{
    ساكن ثابت مزدوج test_data[] = {
        -0.1, -0.018053968510807, -0.01, -0.00449, 0.0, 0.00316227760, 0.005,
        0.009, 0.015, 0.1, 1.0, 52.37, 125.098765, 1999.11123, 6945.443,
        15123.4567, 19845.88923, 98678.4231, 99999.899998
    };

    لكل (تعداد AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        إذا (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_BASE;

        av_csp_trc_function func = av_csp_trc_func_from_id(trc);
        av_csp_trc_function func_inv = av_csp_trc_func_inv_from_id(trc);
        ثابت حرف *name = av_color_transfer_name(trc);
        إذا (!func)
            استمر;

        لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(test_data); i++) {
            مزدوج result = func(test_data[i]);
            مزدوج roundtrip = func_inv(result);
            printf("trc=%s calling func(%f) expected=%f roundtrip=%f\n",
                    name, test_data[i], result, roundtrip);

            إذا (result > 0.0 && fabs(roundtrip - test_data[i]) > 1e-7) {
                printf("  FAIL\n");
                أرجع 1;
            }
        }
    }

    لكل (تعداد AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        إذا (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_BASE;

        av_csp_eotf_function eotf = av_csp_itu_eotf(trc);
        av_csp_eotf_function eotf_inv = av_csp_itu_eotf_inv(trc);
        ثابت حرف *trc_name = av_color_transfer_name(trc);
        إذا (!eotf)
            استمر;

        إذا (trc == AVCOL_TRC_SMPTE2084) {
            /* This one is equivalent to the TRC already tested above */
            استمر;
        } وإلا إذا (trc == AVCOL_TRC_SMPTE428) {
            /* Test vectors from SMPTE RP-431-2 */
            ثابت بنية { مزدوج E_xyz[3]; مزدوج luma; } tests[] = {
            #define XYZ(X, Y, Z) { X / 4095.0, Y / 4095.0, Z / 4095.0 }
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
            ثابت مزدوج luminance = 48.00;
            ثابت مزدوج contrast = 2000;
            /* Solve for Lw - Lb = luminance, Lw / Lb = contrast */
            ثابت مزدوج Lb = luminance / (contrast - 1);
            ثابت مزدوج Lw = Lb + luminance;

            لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(tests); i++) {
                مزدوج L_xyz[3];
                memcpy(L_xyz, tests[i].E_xyz, حجم(L_xyz));
                eotf(Lw, Lb, L_xyz);
                printf("trc=%s EOTF(%g, %g, {%g, %g, %g}) = {%g, %g %g}, expected Y=%f\n",
                       trc_name, Lw, Lb,
                       tests[i].E_xyz[0], tests[i].E_xyz[1], tests[i].E_xyz[2],
                       L_xyz[0], L_xyz[1], L_xyz[2], tests[i].luma);

                إذا (fabs(L_xyz[1] - tests[i].luma) > 0.01) {
                    printf("  FAIL\n");
                    أرجع 1;
                }
            }
        } وإلا {
            /* Normal, display-relative RGB curve */
            ساكن ثابت مزدوج black_points[] = { 0.0, 1e-6, 0.1, 1.5 };
            ساكن ثابت مزدوج white_points[] = { 50.0, 100.0, 203.0, 1000.0, 10000.0 };

            لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(black_points); i++) {
                لكل (صحيح j = 0; j < FF_ARRAY_ELEMS(white_points); j++) {
                    ثابت مزدوج Lb = black_points[i];
                    ثابت مزدوج Lw = white_points[j];
                    ثابت مزدوج all0[3] = { 0.0, 0.0, 0.0 };
                    ثابت مزدوج all1[3] = { 1.0, 1.0, 1.0 };
                    ثابت مزدوج black[3] = { Lb, Lb, Lb };
                    ثابت مزدوج white[3] = { Lw, Lw, Lw };
                    مزدوج L_prev;

                    TEST_EOTF(eotf, all0, black);
                    TEST_EOTF(eotf, all1, white);
                    TEST_EOTF(eotf_inv, black, all0);
                    TEST_EOTF(eotf_inv, white, all1);

                    /* Test round-trip on grayscale ramp */
                    لكل (مزدوج x = 0.0; x < 1.0; x += 0.1) {
                        ثابت مزدوج E[3] = { x, x, x };
                        مزدوج L[3] = { x, x, x };
                        eotf(Lw, Lb, L);

                        printf("trc=%s EOTF(%g, %g, {%g}) = {%g}\n",
                               trc_name, Lw, Lb, E[1], L[1]);
                        TEST_EOTF(eotf_inv, L, E);

                        إذا (x > 0.0 && L[1] <= L_prev) {
                            printf("  FAIL: non-monotonic!\n");
                            أرجع 1;
                        }
                        L_prev = L[1];
                    }
                }
            }
        }
    }
}
