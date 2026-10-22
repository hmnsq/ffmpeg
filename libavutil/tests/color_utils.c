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

#समावेश <math.h>
#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/csp.h"
#समावेश "libavutil/macros.h"
#समावेश "libavutil/pixdesc.h"
#समावेश "libavutil/pixfmt.h"

अटल अंतरभूत पूर्णांक fuzzy_equal(द्विगुन a, द्विगुन b)
{
    स्थिर द्विगुन epsilon = fmax(fmax(भ_असल(a), भ_असल(b)), 1.0) * 1e-7;
    वापस भ_असल(a - b) <= epsilon;
}

#घोषणा TEST_EOTF(func, निवेश, ref) करो                              \
{                                                                   \
    स्थिर द्विगुन _b[3] = { (ref)[0], (ref)[1], (ref)[2] };          \
    द्विगुन _a[3] = { (निवेश)[0], (निवेश)[1], (निवेश)[2] };          \
    func(Lw, Lb, _a);                                               \
    क्रम (पूर्णांक _i = 0; _i < 3; _i++) {                                \
        अगर (!fuzzy_equal(_a[_i], _b[_i])) {                         \
            म_लिखो("FAIL: trc=%s %s(%g, %g, %s) != %s\n"            \
                   "  expected {%g, %g, %g}, got {%g, %g, %g}\n",   \
                    trc_name, #func, Lw, Lb, #input, #ref,          \
                    _b[0], _b[1], _b[2], _a[0], _a[1], _a[2]);      \
            वापस 1;                                               \
        }                                                           \
    }                                                               \
} जबतक (0)

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
{
    अटल स्थिर द्विगुन test_तथ्य[] = {
        -0.1, -0.018053968510807, -0.01, -0.00449, 0.0, 0.00316227760, 0.005,
        0.009, 0.015, 0.1, 1.0, 52.37, 125.098765, 1999.11123, 6945.443,
        15123.4567, 19845.88923, 98678.4231, 99999.899998
    };

    क्रम (क्रमागत AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        अगर (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_BASE;

        av_csp_trc_function func = av_csp_trc_func_from_id(trc);
        av_csp_trc_function func_inv = av_csp_trc_func_inv_from_id(trc);
        स्थिर अक्षर *name = av_color_transfer_name(trc);
        अगर (!func)
            जारी;

        क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(test_तथ्य); i++) {
            द्विगुन परिणाम = func(test_तथ्य[i]);
            द्विगुन roundtrip = func_inv(परिणाम);
            म_लिखो("trc=%s calling func(%f) expected=%f roundtrip=%f\n",
                    name, test_तथ्य[i], परिणाम, roundtrip);

            अगर (परिणाम > 0.0 && भ_असल(roundtrip - test_तथ्य[i]) > 1e-7) {
                म_लिखो("  FAIL\n");
                वापस 1;
            }
        }
    }

    क्रम (क्रमागत AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        अगर (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_BASE;

        av_csp_eotf_function eotf = av_csp_itu_eotf(trc);
        av_csp_eotf_function eotf_inv = av_csp_itu_eotf_inv(trc);
        स्थिर अक्षर *trc_name = av_color_transfer_name(trc);
        अगर (!eotf)
            जारी;

        अगर (trc == AVCOL_TRC_SMPTE2084) {
            /* This one is equivalent to the TRC already tested above */
            जारी;
        } अन्यथा अगर (trc == AVCOL_TRC_SMPTE428) {
            /* Test vectors from SMPTE RP-431-2 */
            स्थिर काष्ठा { द्विगुन E_xyz[3]; द्विगुन luma; } tests[] = {
            #घोषणा XYZ(X, Y, Z) { X / 4095.0, Y / 4095.0, Z / 4095.0 }
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
            स्थिर द्विगुन luminance = 48.00;
            स्थिर द्विगुन contrast = 2000;
            /* Solve for Lw - Lb = luminance, Lw / Lb = contrast */
            स्थिर द्विगुन Lb = luminance / (contrast - 1);
            स्थिर द्विगुन Lw = Lb + luminance;

            क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(tests); i++) {
                द्विगुन L_xyz[3];
                स_नकल(L_xyz, tests[i].E_xyz, माप(L_xyz));
                eotf(Lw, Lb, L_xyz);
                म_लिखो("trc=%s EOTF(%g, %g, {%g, %g, %g}) = {%g, %g %g}, expected Y=%f\n",
                       trc_name, Lw, Lb,
                       tests[i].E_xyz[0], tests[i].E_xyz[1], tests[i].E_xyz[2],
                       L_xyz[0], L_xyz[1], L_xyz[2], tests[i].luma);

                अगर (भ_असल(L_xyz[1] - tests[i].luma) > 0.01) {
                    म_लिखो("  FAIL\n");
                    वापस 1;
                }
            }
        } अन्यथा {
            /* Normal, display-relative RGB curve */
            अटल स्थिर द्विगुन black_points[] = { 0.0, 1e-6, 0.1, 1.5 };
            अटल स्थिर द्विगुन white_points[] = { 50.0, 100.0, 203.0, 1000.0, 10000.0 };

            क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(black_points); i++) {
                क्रम (पूर्णांक j = 0; j < FF_ARRAY_ELEMS(white_points); j++) {
                    स्थिर द्विगुन Lb = black_points[i];
                    स्थिर द्विगुन Lw = white_points[j];
                    स्थिर द्विगुन all0[3] = { 0.0, 0.0, 0.0 };
                    स्थिर द्विगुन all1[3] = { 1.0, 1.0, 1.0 };
                    स्थिर द्विगुन black[3] = { Lb, Lb, Lb };
                    स्थिर द्विगुन white[3] = { Lw, Lw, Lw };
                    द्विगुन L_पूर्व;

                    TEST_EOTF(eotf, all0, black);
                    TEST_EOTF(eotf, all1, white);
                    TEST_EOTF(eotf_inv, black, all0);
                    TEST_EOTF(eotf_inv, white, all1);

                    /* Test round-trip on grayscale ramp */
                    क्रम (द्विगुन x = 0.0; x < 1.0; x += 0.1) {
                        स्थिर द्विगुन E[3] = { x, x, x };
                        द्विगुन L[3] = { x, x, x };
                        eotf(Lw, Lb, L);

                        म_लिखो("trc=%s EOTF(%g, %g, {%g}) = {%g}\n",
                               trc_name, Lw, Lb, E[1], L[1]);
                        TEST_EOTF(eotf_inv, L, E);

                        अगर (x > 0.0 && L[1] <= L_पूर्व) {
                            म_लिखो("  FAIL: non-monotonic!\n");
                            वापस 1;
                        }
                        L_पूर्व = L[1];
                    }
                }
            }
        }
    }
}
