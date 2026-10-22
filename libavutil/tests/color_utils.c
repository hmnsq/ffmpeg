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

#अन्तर्भाव <math.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/csp.h"
#अन्तर्भाव "libavutil/macros.h"
#अन्तर्भाव "libavutil/pixdesc.h"
#अन्तर्भाव "libavutil/pixfmt.h"

स्थिर अन्तःस्थ पूर्णाङ्क fuzzy_equal(द्विगुण a, द्विगुण b)
{
    ध्रुव द्विगुण epsilon = fmax(fmax(fabs(a), fabs(b)), 1.0) * 1e-7;
    प्रत्यागम fabs(a - b) <= epsilon;
}

#define TEST_EOTF(func, आदान, ref) कुरु                              \
{                                                                   \
    ध्रुव द्विगुण _b[3] = { (ref)[0], (ref)[1], (ref)[2] };          \
    द्विगुण _a[3] = { (आदान)[0], (आदान)[1], (आदान)[2] };          \
    func(Lw, Lb, _a);                                               \
    प्रति (पूर्णाङ्क _i = 0; _i < 3; _i++) {                                \
        यदि (!fuzzy_equal(_a[_i], _b[_i])) {                         \
            printf("FAIL: trc=%s %s(%g, %g, %s) != %s\n"            \
                   "  expected {%g, %g, %g}, got {%g, %g, %g}\n",   \
                    trc_name, #func, Lw, Lb, #input, #ref,          \
                    _b[0], _b[1], _b[2], _a[0], _a[1], _a[2]);      \
            प्रत्यागम 1;                                               \
        }                                                           \
    }                                                               \
} यावत् (0)

पूर्णाङ्क main(पूर्णाङ्क argc, वर्ण *argv[])
{
    स्थिर ध्रुव द्विगुण test_data[] = {
        -0.1, -0.018053968510807, -0.01, -0.00449, 0.0, 0.00316227760, 0.005,
        0.009, 0.015, 0.1, 1.0, 52.37, 125.098765, 1999.11123, 6945.443,
        15123.4567, 19845.88923, 98678.4231, 99999.899998
    };

    प्रति (गणना AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        यदि (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_BASE;

        av_csp_trc_function func = av_csp_trc_func_from_id(trc);
        av_csp_trc_function func_inv = av_csp_trc_func_inv_from_id(trc);
        ध्रुव वर्ण *name = av_color_transfer_name(trc);
        यदि (!func)
            अनुवर्त;

        प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(test_data); i++) {
            द्विगुण result = func(test_data[i]);
            द्विगुण roundtrip = func_inv(result);
            printf("trc=%s calling func(%f) expected=%f roundtrip=%f\n",
                    name, test_data[i], result, roundtrip);

            यदि (result > 0.0 && fabs(roundtrip - test_data[i]) > 1e-7) {
                printf("  FAIL\n");
                प्रत्यागम 1;
            }
        }
    }

    प्रति (गणना AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        यदि (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_BASE;

        av_csp_eotf_function eotf = av_csp_itu_eotf(trc);
        av_csp_eotf_function eotf_inv = av_csp_itu_eotf_inv(trc);
        ध्रुव वर्ण *trc_name = av_color_transfer_name(trc);
        यदि (!eotf)
            अनुवर्त;

        यदि (trc == AVCOL_TRC_SMPTE2084) {
            /* This one is equivalent to the TRC already tested above */
            अनुवर्त;
        } अन्यथा यदि (trc == AVCOL_TRC_SMPTE428) {
            /* Test vectors from SMPTE RP-431-2 */
            ध्रुव संरचना { द्विगुण E_xyz[3]; द्विगुण luma; } tests[] = {
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
            ध्रुव द्विगुण luminance = 48.00;
            ध्रुव द्विगुण contrast = 2000;
            /* Solve for Lw - Lb = luminance, Lw / Lb = contrast */
            ध्रुव द्विगुण Lb = luminance / (contrast - 1);
            ध्रुव द्विगुण Lw = Lb + luminance;

            प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(tests); i++) {
                द्विगुण L_xyz[3];
                memcpy(L_xyz, tests[i].E_xyz, परिमाण(L_xyz));
                eotf(Lw, Lb, L_xyz);
                printf("trc=%s EOTF(%g, %g, {%g, %g, %g}) = {%g, %g %g}, expected Y=%f\n",
                       trc_name, Lw, Lb,
                       tests[i].E_xyz[0], tests[i].E_xyz[1], tests[i].E_xyz[2],
                       L_xyz[0], L_xyz[1], L_xyz[2], tests[i].luma);

                यदि (fabs(L_xyz[1] - tests[i].luma) > 0.01) {
                    printf("  FAIL\n");
                    प्रत्यागम 1;
                }
            }
        } अन्यथा {
            /* Normal, display-relative RGB curve */
            स्थिर ध्रुव द्विगुण black_points[] = { 0.0, 1e-6, 0.1, 1.5 };
            स्थिर ध्रुव द्विगुण white_points[] = { 50.0, 100.0, 203.0, 1000.0, 10000.0 };

            प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(black_points); i++) {
                प्रति (पूर्णाङ्क j = 0; j < FF_ARRAY_ELEMS(white_points); j++) {
                    ध्रुव द्विगुण Lb = black_points[i];
                    ध्रुव द्विगुण Lw = white_points[j];
                    ध्रुव द्विगुण all0[3] = { 0.0, 0.0, 0.0 };
                    ध्रुव द्विगुण all1[3] = { 1.0, 1.0, 1.0 };
                    ध्रुव द्विगुण black[3] = { Lb, Lb, Lb };
                    ध्रुव द्विगुण white[3] = { Lw, Lw, Lw };
                    द्विगुण L_prev;

                    TEST_EOTF(eotf, all0, black);
                    TEST_EOTF(eotf, all1, white);
                    TEST_EOTF(eotf_inv, black, all0);
                    TEST_EOTF(eotf_inv, white, all1);

                    /* Test round-trip on grayscale ramp */
                    प्रति (द्विगुण x = 0.0; x < 1.0; x += 0.1) {
                        ध्रुव द्विगुण E[3] = { x, x, x };
                        द्विगुण L[3] = { x, x, x };
                        eotf(Lw, Lb, L);

                        printf("trc=%s EOTF(%g, %g, {%g}) = {%g}\n",
                               trc_name, Lw, Lb, E[1], L[1]);
                        TEST_EOTF(eotf_inv, L, E);

                        यदि (x > 0.0 && L[1] <= L_prev) {
                            printf("  FAIL: non-monotonic!\n");
                            प्रत्यागम 1;
                        }
                        L_prev = L[1];
                    }
                }
            }
        }
    }
}
