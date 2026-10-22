/*
 * Copyright (c) 2015 Kevin Wheatley <kevin.j.wheatley@gmail.com>
 * Copyright (c) 2016 Ronald S. Bultje <rsbultje@gmail.com>
 * Copyright (c) 2023 Leo Izen <leo.izen@gmail.com>
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

/**
 * @file Colorspace functions for libavutil
 * @author Ronald S. Bultje <rsbultje@gmail.com>
 * @author Leo Izen <leo.izen@gmail.com>
 * @author Kevin Wheatley <kevin.j.wheatley@gmail.com>
 */

#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <math.h>

#अन्तर्भाव "attributes.h"
#अन्तर्भाव "csp.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "rational.h"

#परिभाषय AVR(d) { (पूर्णाङ्क)(d * 100000 + 0.5), 100000 }

/*
 * All constants explained in e.g. https://linuxtv.org/downloads/v4l-dvb-apis/ch02s06.html
 * The older ones (bt470bg/m) are also explained in their respective ITU docs
 * (e.g. https://www.itu.int/dms_pubrec/itu-r/rec/bt/R-REC-BT.470-5-199802-S!!PDF-E.pdf)
 * whereas the newer ones can typically be copied directly from wikipedia :)
 */
स्थिर ध्रुव संरचना AVLumaCoefficients luma_coefficients[AVCOL_SPC_NB] = {
    [AVCOL_SPC_FCC]        = { AVR(0.30),   AVR(0.59),   AVR(0.11)   },
    [AVCOL_SPC_BT470BG]    = { AVR(0.299),  AVR(0.587),  AVR(0.114)  },
    [AVCOL_SPC_SMPTE170M]  = { AVR(0.299),  AVR(0.587),  AVR(0.114)  },
    [AVCOL_SPC_BT709]      = { AVR(0.2126), AVR(0.7152), AVR(0.0722) },
    [AVCOL_SPC_SMPTE240M]  = { AVR(0.212),  AVR(0.701),  AVR(0.087)  },
    [AVCOL_SPC_YCOCG]      = { AVR(0.25),   AVR(0.5),    AVR(0.25)   },
    [AVCOL_SPC_RGB]        = { AVR(1),      AVR(1),      AVR(1)      },
    [AVCOL_SPC_BT2020_NCL] = { AVR(0.2627), AVR(0.6780), AVR(0.0593) },
    [AVCOL_SPC_BT2020_CL]  = { AVR(0.2627), AVR(0.6780), AVR(0.0593) },
};

ध्रुव संरचना AVLumaCoefficients *av_csp_luma_coeffs_from_avcsp(गणना AVColorSpace csp)
{
    ध्रुव AVLumaCoefficients *coeffs;

    यदि ((अचिह्नित)csp >= AVCOL_SPC_NB)
        प्रत्यागम रिक्त;
    coeffs = &luma_coefficients[csp];
    यदि (!coeffs->cr.अङ्कः)
        प्रत्यागम रिक्त;

    प्रत्यागम coeffs;
}

#परिभाषय WP_D65 { AVR(0.3127), AVR(0.3290) }
#परिभाषय WP_C   { AVR(0.3100), AVR(0.3160) }
#परिभाषय WP_DCI { AVR(0.3140), AVR(0.3510) }
#परिभाषय WP_E   { {1, 3}, {1, 3} }

स्थिर ध्रुव AVColorPrimariesDesc color_primaries[AVCOL_PRI_NB] = {
    [AVCOL_PRI_BT709]     = { WP_D65, { { AVR(0.640), AVR(0.330) }, { AVR(0.300), AVR(0.600) }, { AVR(0.150), AVR(0.060) } } },
    [AVCOL_PRI_BT470M]    = { WP_C,   { { AVR(0.670), AVR(0.330) }, { AVR(0.210), AVR(0.710) }, { AVR(0.140), AVR(0.080) } } },
    [AVCOL_PRI_BT470BG]   = { WP_D65, { { AVR(0.640), AVR(0.330) }, { AVR(0.290), AVR(0.600) }, { AVR(0.150), AVR(0.060) } } },
    [AVCOL_PRI_SMPTE170M] = { WP_D65, { { AVR(0.630), AVR(0.340) }, { AVR(0.310), AVR(0.595) }, { AVR(0.155), AVR(0.070) } } },
    [AVCOL_PRI_SMPTE240M] = { WP_D65, { { AVR(0.630), AVR(0.340) }, { AVR(0.310), AVR(0.595) }, { AVR(0.155), AVR(0.070) } } },
    [AVCOL_PRI_SMPTE428]  = { WP_E,   { { AVR(0.735), AVR(0.265) }, { AVR(0.274), AVR(0.718) }, { AVR(0.167), AVR(0.009) } } },
    [AVCOL_PRI_SMPTE431]  = { WP_DCI, { { AVR(0.680), AVR(0.320) }, { AVR(0.265), AVR(0.690) }, { AVR(0.150), AVR(0.060) } } },
    [AVCOL_PRI_SMPTE432]  = { WP_D65, { { AVR(0.680), AVR(0.320) }, { AVR(0.265), AVR(0.690) }, { AVR(0.150), AVR(0.060) } } },
    [AVCOL_PRI_FILM]      = { WP_C,   { { AVR(0.681), AVR(0.319) }, { AVR(0.243), AVR(0.692) }, { AVR(0.145), AVR(0.049) } } },
    [AVCOL_PRI_BT2020]    = { WP_D65, { { AVR(0.708), AVR(0.292) }, { AVR(0.170), AVR(0.797) }, { AVR(0.131), AVR(0.046) } } },
    [AVCOL_PRI_JEDEC_P22] = { WP_D65, { { AVR(0.630), AVR(0.340) }, { AVR(0.295), AVR(0.605) }, { AVR(0.155), AVR(0.077) } } },
};

स्थिर ध्रुव AVColorPrimariesDesc color_primaries_ext[AVCOL_PRI_EXT_NB -
                                                      AVCOL_PRI_EXT_आधारः] = {
    [AVCOL_PRI_V_GAMUT - AVCOL_PRI_EXT_आधारः] = { WP_D65, { { AVR(0.730), AVR(0.280) }, { AVR(0.165), AVR(0.840) }, { AVR(0.100), AVR(-0.030) } } },
};

ध्रुव AVColorPrimariesDesc *av_csp_primaries_desc_from_id(गणना AVColorPrimaries prm)
{
    ध्रुव AVColorPrimariesDesc *p = रिक्त;
    यदि ((अचिह्नित)prm < AVCOL_PRI_NB)
        p = &color_primaries[prm];
    अन्यथा यदि (((अचिह्नित)prm >= AVCOL_PRI_EXT_आधारः) &&
             ((अचिह्नित)prm < AVCOL_PRI_EXT_NB))
        p = &color_primaries_ext[prm - AVCOL_PRI_EXT_आधारः];
    यदि (!p || !p->prim.r.x.अङ्कः)
        प्रत्यागम रिक्त;
    प्रत्यागम p;
}

स्थिर av_always_inline AVRational abs_sub_q(AVRational r1, AVRational r2)
{
    AVRational diff = av_sub_q(r1, r2);
    /* denominator assumed to be positive */
    प्रत्यागम av_make_q(निरपेक्षम्(diff.अङ्कः), diff.den);
}

गणना AVColorPrimaries av_csp_primaries_id_from_desc(ध्रुव AVColorPrimariesDesc *prm)
{
    AVRational delta;

    प्रति (गणना AVColorPrimaries p = 0; p < AVCOL_PRI_NB; p++) {
        ध्रुव AVColorPrimariesDesc *ref = &color_primaries[p];
        यदि (!ref->prim.r.x.अङ्कः)
            अनुवर्त;

        delta = abs_sub_q(prm->prim.r.x, ref->prim.r.x);
        delta = av_सङ्कलय_q(delta, abs_sub_q(prm->prim.r.y, ref->prim.r.y));
        delta = av_सङ्कलय_q(delta, abs_sub_q(prm->prim.g.x, ref->prim.g.x));
        delta = av_सङ्कलय_q(delta, abs_sub_q(prm->prim.g.y, ref->prim.g.y));
        delta = av_सङ्कलय_q(delta, abs_sub_q(prm->prim.b.x, ref->prim.b.x));
        delta = av_सङ्कलय_q(delta, abs_sub_q(prm->prim.b.y, ref->prim.b.y));
        delta = av_सङ्कलय_q(delta, abs_sub_q(prm->wp.x, ref->wp.x));
        delta = av_सङ्कलय_q(delta, abs_sub_q(prm->wp.y, ref->wp.y));

        यदि (av_cmp_q(delta, av_make_q(1, 1000)) < 0)
            प्रत्यागम p;
    }

    प्रत्यागम AVCOL_PRI_UNSPECIFIED;
}

स्थिर ध्रुव द्विगुण approximate_gamma[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = 1.961,
    [AVCOL_TRC_SMPTE170M] = 1.961,
    [AVCOL_TRC_SMPTE240M] = 1.961,
    [AVCOL_TRC_BT1361_ECG] = 1.961,
    [AVCOL_TRC_BT2020_10] = 1.961,
    [AVCOL_TRC_BT2020_12] = 1.961,
    [AVCOL_TRC_GAMMA22] = 2.2,
    [AVCOL_TRC_IEC61966_2_1] = 2.2,
    [AVCOL_TRC_GAMMA28] = 2.8,
    [AVCOL_TRC_रैखिकम्] = 1.0,
    [AVCOL_TRC_SMPTE428] = 2.6,
};

स्थिर ध्रुव द्विगुण approximate_gamma_ext[AVCOL_TRC_EXT_NB -
                                          AVCOL_TRC_EXT_आधारः] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_आधारः] = 2.2,
};

द्विगुण av_csp_approximate_trc_gamma(गणना AVColorTransferCharacteristic trc)
{
    यदि (trc < AVCOL_TRC_NB)
        प्रत्यागम approximate_gamma[trc];
    अन्यथा यदि ((trc >= AVCOL_TRC_EXT_आधारः) && (trc < AVCOL_TRC_EXT_NB))
        प्रत्यागम approximate_gamma_ext[trc - AVCOL_TRC_EXT_आधारः];
    प्रत्यागम 0.0;
}

स्थिर ध्रुव द्विगुण approximate_eotf_gamma[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = 2.2,
    [AVCOL_TRC_SMPTE170M] = 2.2,
    [AVCOL_TRC_SMPTE240M] = 2.2,
    [AVCOL_TRC_BT1361_ECG] = 2.2,
    [AVCOL_TRC_BT2020_10] = 2.2,
    [AVCOL_TRC_BT2020_12] = 2.2,
    [AVCOL_TRC_GAMMA22] = 2.2,
    [AVCOL_TRC_IEC61966_2_1] = 2.2,
    [AVCOL_TRC_GAMMA28] = 2.8,
    [AVCOL_TRC_रैखिकम्] = 1.0,
    [AVCOL_TRC_SMPTE428] = 2.6,
};

स्थिर ध्रुव द्विगुण approximate_eotf_gamma_ext[AVCOL_TRC_EXT_NB -
                                               AVCOL_TRC_EXT_आधारः] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_आधारः] = 2.2,
};

द्विगुण av_csp_approximate_eotf_gamma(गणना AVColorTransferCharacteristic trc)
{
    यदि ((अचिह्नित)trc < AVCOL_TRC_NB)
        प्रत्यागम approximate_eotf_gamma[trc];
    अन्यथा यदि (((अचिह्नित)trc >= AVCOL_TRC_EXT_आधारः) &&
             ((अचिह्नित)trc < AVCOL_TRC_EXT_NB))
        प्रत्यागम approximate_eotf_gamma_ext[trc - AVCOL_TRC_EXT_आधारः];
    प्रत्यागम 0.0;
}

#परिभाषय BT709_alpha 1.099296826809442
#परिभाषय BT709_beta 0.018053968510807

स्थिर द्विगुण trc_bt709(द्विगुण Lc)
{
    ध्रुव द्विगुण a = BT709_alpha;
    ध्रुव द्विगुण b = BT709_beta;

    प्रत्यागम (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 4.500 * Lc
         :              a * घातः(Lc, 0.45) - (a - 1.0);
}

स्थिर द्विगुण trc_bt709_inv(द्विगुण E)
{
    ध्रुव द्विगुण a = BT709_alpha;
    ध्रुव द्विगुण b = 4.500 * BT709_beta;

    प्रत्यागम (0.0 > E) ? 0.0
         : (  b > E) ? E / 4.500
         :             घातः((E + (a - 1.0)) / a, 1.0 / 0.45);
}

स्थिर द्विगुण trc_gamma22(द्विगुण Lc)
{
    प्रत्यागम (0.0 > Lc) ? 0.0 : घातः(Lc, 1.0/ 2.2);
}

स्थिर द्विगुण trc_gamma22_inv(द्विगुण E)
{
    प्रत्यागम (0.0 > E) ? 0.0 : घातः(E, 2.2);
}

स्थिर द्विगुण trc_gamma28(द्विगुण Lc)
{
    प्रत्यागम (0.0 > Lc) ? 0.0 : घातः(Lc, 1.0/ 2.8);
}

स्थिर द्विगुण trc_gamma28_inv(द्विगुण E)
{
    प्रत्यागम (0.0 > E) ? 0.0 : घातः(E, 2.8);
}

स्थिर द्विगुण trc_smpte240M(द्विगुण Lc)
{
    ध्रुव द्विगुण a = 1.1115;
    ध्रुव द्विगुण b = 0.0228;

    प्रत्यागम (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 4.000 * Lc
         :              a * घातः(Lc, 0.45) - (a - 1.0);
}

स्थिर द्विगुण trc_smpte240M_inv(द्विगुण E)
{
    ध्रुव द्विगुण a = 1.1115;
    ध्रुव द्विगुण b = 4.000 * 0.0228;

    प्रत्यागम (0.0 > E) ? 0.0
         : (  b > E) ? E / 4.000
         :             घातः((E + (a - 1.0)) / a, 1.0 / 0.45);
}

स्थिर द्विगुण trc_रैखिकम्(द्विगुण Lc)
{
    प्रत्यागम Lc;
}

स्थिर द्विगुण trc_log(द्विगुण Lc)
{
    प्रत्यागम (0.01 > Lc) ? 0.0 : 1.0 + log10(Lc) / 2.0;
}

स्थिर द्विगुण trc_log_inv(द्विगुण E)
{
    प्रत्यागम (0.0 > E) ? 0.01 : घातः(10.0, 2.0 * (E - 1.0));
}

स्थिर द्विगुण trc_log_sqrt(द्विगुण Lc)
{
    // sqrt(10) / 1000
    प्रत्यागम (0.00316227766 > Lc) ? 0.0 : 1.0 + log10(Lc) / 2.5;
}

स्थिर द्विगुण trc_log_sqrt_inv(द्विगुण E)
{
    प्रत्यागम (0.0 > E) ? 0.00316227766 : घातः(10.0, 2.5 * (E - 1.0));
}

स्थिर द्विगुण trc_iec61966_2_4(द्विगुण Lc)
{
    ध्रुव द्विगुण a = BT709_alpha;
    ध्रुव द्विगुण b = BT709_beta;

    प्रत्यागम (-b >= Lc) ? -a * घातः(-Lc, 0.45) + (a - 1.0)
         : ( b >  Lc) ? 4.500 * Lc
         :               a * घातः( Lc, 0.45) - (a - 1.0);
}

स्थिर द्विगुण trc_iec61966_2_4_inv(द्विगुण E)
{
    ध्रुव द्विगुण a = BT709_alpha;
    ध्रुव द्विगुण b = 4.500 * BT709_beta;

    प्रत्यागम (-b >= E) ? -घातः((-E + (a - 1.0)) / a, 1.0 / 0.45)
         : ( b >  E) ? E / 4.500
         :              घातः(( E + (a - 1.0)) / a, 1.0 / 0.45);
}

स्थिर द्विगुण trc_bt1361(द्विगुण Lc)
{
    ध्रुव द्विगुण a = BT709_alpha;
    ध्रुव द्विगुण b = BT709_beta;

    प्रत्यागम (-0.0045 >= Lc) ? -(a * घातः(-4.0 * Lc, 0.45) + (a - 1.0)) / 4.0
         : ( b >  Lc) ? 4.500 * Lc
         :               a * घातः( Lc, 0.45) - (a - 1.0);
}

स्थिर द्विगुण trc_bt1361_inv(द्विगुण E)
{
    ध्रुव द्विगुण a = BT709_alpha;
    ध्रुव द्विगुण b = 4.500 * BT709_beta;

    प्रत्यागम (-0.02025 >= E) ? -घातः((-4.0 * E - (a - 1.0)) / a, 1.0 / 0.45) / 4.0
         : ( b       >  E) ? E / 4.500
         :                    घातः(( E + (a - 1.0)) / a, 1.0 / 0.45);
}

स्थिर द्विगुण trc_iec61966_2_1(द्विगुण Lc)
{
    ध्रुव द्विगुण a = 1.055;
    ध्रुव द्विगुण b = 0.0031308;

    प्रत्यागम (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 12.92 * Lc
         :              a * घातः(Lc, 1.0  / 2.4) - (a - 1.0);
}

स्थिर द्विगुण trc_iec61966_2_1_inv(द्विगुण E)
{
    ध्रुव द्विगुण a = 1.055;
    ध्रुव द्विगुण b = 12.92 * 0.0031308;

    प्रत्यागम (0.0 > E) ? 0.0
         : (  b > E) ? E / 12.92
                     : घातः((E + (a - 1.0)) / a, 2.4);
    प्रत्यागम E;
}

#परिभाषय PQ_c1 (        3424.0 / 4096.0) /* c3-c2 + 1 */
#परिभाषय PQ_c2 ( 32.0 * 2413.0 / 4096.0)
#परिभाषय PQ_c3 ( 32.0 * 2392.0 / 4096.0)
#परिभाषय PQ_m  (128.0 * 2523.0 / 4096.0)
#परिभाषय PQ_n  ( 0.25 * 2610.0 / 4096.0)

स्थिर द्विगुण trc_smpte_st2084(द्विगुण Lc)
{
    ध्रुव द्विगुण c1 = PQ_c1;
    ध्रुव द्विगुण c2 = PQ_c2;
    ध्रुव द्विगुण c3 = PQ_c3;
    ध्रुव द्विगुण m  = PQ_m;
    ध्रुव द्विगुण n  = PQ_n;
    ध्रुव द्विगुण L  = Lc / 10000.0;
    ध्रुव द्विगुण Ln = घातः(L, n);

    प्रत्यागम (0.0 > Lc) ? 0.0
         :              घातः((c1 + c2 * Ln) / (1.0 + c3 * Ln), m);

}

स्थिर द्विगुण trc_smpte_st2084_inv(द्विगुण E)
{
    ध्रुव द्विगुण c1 = PQ_c1;
    ध्रुव द्विगुण c2 = PQ_c2;
    ध्रुव द्विगुण c3 = PQ_c3;
    ध्रुव द्विगुण m  = PQ_m;
    ध्रुव द्विगुण n  = PQ_n;
    ध्रुव द्विगुण Em = घातः(E, 1.0 / m);

    प्रत्यागम (c1 > Em) ? 0.0
                     : 10000.0 * घातः((Em - c1) / (c2 - c3 * Em), 1.0 / n);
}

#परिभाषय DCI_L 48.00
#परिभाषय DCI_P 52.37

स्थिर द्विगुण trc_smpte_st428_1(द्विगुण Lc)
{
    प्रत्यागम (0.0 > Lc) ? 0.0 : घातः(DCI_L / DCI_P * Lc, 1.0 / 2.6);
}

स्थिर द्विगुण trc_smpte_st428_1_inv(द्विगुण E)
{
    प्रत्यागम (0.0 > E) ? 0.0 : DCI_P / DCI_L * घातः(E, 2.6);
}

#परिभाषय HLG_a 0.17883277
#परिभाषय HLG_b 0.28466892
#परिभाषय HLG_c 0.55991073

स्थिर द्विगुण trc_arib_std_b67(द्विगुण Lc) {
    // The function uses the definition from HEVC, which assumes that the peak
    // white is input level = 1. (this is equivalent to scaling E = Lc * 12 and
    // using the definition from the ARIB STD-B67 spec)
    ध्रुव द्विगुण a = HLG_a;
    ध्रुव द्विगुण b = HLG_b;
    ध्रुव द्विगुण c = HLG_c;
    प्रत्यागम (0.0 > Lc) ? 0.0 :
        (Lc <= 1.0 / 12.0 ? वर्गमूलम्(3.0 * Lc) : a * लघुगणकः(12.0 * Lc - b) + c);
}

स्थिर द्विगुण trc_arib_std_b67_inv(द्विगुण E)
{
    ध्रुव द्विगुण a = HLG_a;
    ध्रुव द्विगुण b = HLG_b;
    ध्रुव द्विगुण c = HLG_c;
    प्रत्यागम (0.0 > E) ? 0.0 :
        (E <= 0.5 ? E * E / 3.0 : (घातांकः((E - c) / a) + b) / 12.0);
}

#परिभाषय VLOG_c1 0.01
#परिभाषय VLOG_c2 0.181
#परिभाषय VLOG_b  0.00873
#परिभाषय VLOG_c  0.241514
#परिभाषय VLOG_d  0.598206

स्थिर द्विगुण trc_v_log(द्विगुण E)
{
    ध्रुव द्विगुण c1 = VLOG_c1;
    ध्रुव द्विगुण b = VLOG_b;
    ध्रुव द्विगुण c = VLOG_c;
    ध्रुव द्विगुण d = VLOG_d;
    प्रत्यागम (E < c1) ? (5.6 * E + 0.125) :
        (c * log10(E + b) + d);
}

स्थिर द्विगुण trc_v_log_inv(द्विगुण E)
{
    ध्रुव द्विगुण c2 = VLOG_c2;
    ध्रुव द्विगुण b = VLOG_b;
    ध्रुव द्विगुण c = VLOG_c;
    ध्रुव द्विगुण d = VLOG_d;
    प्रत्यागम (E < c2) ? (E - 0.125) / 5.6 :
        (घातः(10.0, ((E - d) / c)) - b);
}

स्थिर ध्रुव av_csp_trc_function trc_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = trc_bt709,
    [AVCOL_TRC_GAMMA22] = trc_gamma22,
    [AVCOL_TRC_GAMMA28] = trc_gamma28,
    [AVCOL_TRC_SMPTE170M] = trc_bt709,
    [AVCOL_TRC_SMPTE240M] = trc_smpte240M,
    [AVCOL_TRC_रैखिकम्] = trc_रैखिकम्,
    [AVCOL_TRC_LOG] = trc_log,
    [AVCOL_TRC_LOG_SQRT] = trc_log_sqrt,
    [AVCOL_TRC_IEC61966_2_4] = trc_iec61966_2_4,
    [AVCOL_TRC_BT1361_ECG] = trc_bt1361,
    [AVCOL_TRC_IEC61966_2_1] = trc_iec61966_2_1,
    [AVCOL_TRC_BT2020_10] = trc_bt709,
    [AVCOL_TRC_BT2020_12] = trc_bt709,
    [AVCOL_TRC_SMPTE2084] = trc_smpte_st2084,
    [AVCOL_TRC_SMPTE428] = trc_smpte_st428_1,
    [AVCOL_TRC_ARIB_STD_B67] = trc_arib_std_b67,
};

स्थिर ध्रुव av_csp_trc_function trc_funcs_ext[AVCOL_TRC_EXT_NB -
                                               AVCOL_TRC_EXT_आधारः] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_आधारः] = trc_v_log,
};

av_csp_trc_function av_csp_trc_func_from_id(गणना AVColorTransferCharacteristic trc)
{
    यदि ((अचिह्नित)trc < AVCOL_TRC_NB)
        प्रत्यागम trc_funcs[trc];
    अन्यथा यदि (((अचिह्नित)trc >= AVCOL_TRC_EXT_आधारः) &&
             ((अचिह्नित)trc < AVCOL_TRC_EXT_NB))
        प्रत्यागम trc_funcs_ext[trc - AVCOL_TRC_EXT_आधारः];
    प्रत्यागम रिक्त;
}

स्थिर ध्रुव av_csp_trc_function trc_inv_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = trc_bt709_inv,
    [AVCOL_TRC_GAMMA22] = trc_gamma22_inv,
    [AVCOL_TRC_GAMMA28] = trc_gamma28_inv,
    [AVCOL_TRC_SMPTE170M] = trc_bt709_inv,
    [AVCOL_TRC_SMPTE240M] = trc_smpte240M_inv,
    [AVCOL_TRC_रैखिकम्] = trc_रैखिकम्,
    [AVCOL_TRC_LOG] = trc_log_inv,
    [AVCOL_TRC_LOG_SQRT] = trc_log_sqrt_inv,
    [AVCOL_TRC_IEC61966_2_4] = trc_iec61966_2_4_inv,
    [AVCOL_TRC_BT1361_ECG] = trc_bt1361_inv,
    [AVCOL_TRC_IEC61966_2_1] = trc_iec61966_2_1_inv,
    [AVCOL_TRC_BT2020_10] = trc_bt709_inv,
    [AVCOL_TRC_BT2020_12] = trc_bt709_inv,
    [AVCOL_TRC_SMPTE2084] = trc_smpte_st2084_inv,
    [AVCOL_TRC_SMPTE428] = trc_smpte_st428_1_inv,
    [AVCOL_TRC_ARIB_STD_B67] = trc_arib_std_b67_inv,
};

स्थिर ध्रुव av_csp_trc_function trc_inv_funcs_ext[AVCOL_TRC_EXT_NB -
                                                   AVCOL_TRC_EXT_आधारः] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_आधारः] = trc_v_log_inv,
};

av_csp_trc_function av_csp_trc_func_inv_from_id(गणना AVColorTransferCharacteristic trc)
{
    यदि ((अचिह्नित)trc < AVCOL_TRC_NB)
        प्रत्यागम trc_inv_funcs[trc];
    अन्यथा यदि (((अचिह्नित)trc >= AVCOL_TRC_EXT_आधारः) &&
             ((अचिह्नित)trc < AVCOL_TRC_EXT_NB))
        प्रत्यागम trc_inv_funcs_ext[trc - AVCOL_TRC_EXT_आधारः];
    प्रत्यागम रिक्त;
}

स्थिर शून्य eotf_रैखिकम्(ध्रुव द्विगुण Lw, ध्रुव द्विगुण Lb, द्विगुण E[3])
{
    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
        E[i] = (Lw - Lb) * E[i] + Lb;
}

स्थिर शून्य eotf_रैखिकम्_inv(ध्रुव द्विगुण Lw, ध्रुव द्विगुण Lb, द्विगुण L[3])
{
    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
        L[i] = (L[i] - Lb) / (Lw - Lb);
}

#परिभाषय WRAP_SDR_OETF(name)                                         \
स्थिर शून्य oetf_##name(द्विगुण L[3])                                \
{                                                                   \
    प्रति (पूर्णाङ्क i = 0; i < 3; i++)                                     \
        L[i] = trc_##name(L[i]);                                    \
}                                                                   \
                                                                    \
स्थिर शून्य oetf_##name##_inv(द्विगुण E[3])                          \
{                                                                   \
    प्रति (पूर्णाङ्क i = 0; i < 3; i++)                                     \
        E[i] = trc_##name##_inv(E[i]);                              \
}

WRAP_SDR_OETF(gamma22)
WRAP_SDR_OETF(gamma28)
WRAP_SDR_OETF(iec61966_2_1)

#परिभाषय WRAP_SDR_EOTF(name)                                         \
स्थिर शून्य eotf_##name(द्विगुण Lw, द्विगुण Lb, द्विगुण E[3])          \
{                                                                   \
    oetf_##name##_inv(E);                                           \
    eotf_रैखिकम्(Lw, Lb, E);                                         \
}                                                                   \
                                                                    \
स्थिर शून्य eotf_##name##_inv(द्विगुण Lw, द्विगुण Lb, द्विगुण L[3])    \
{                                                                   \
    eotf_रैखिकम्_inv(Lw, Lb, L);                                     \
    oetf_##name(L);                                                 \
}

WRAP_SDR_EOTF(gamma22)
WRAP_SDR_EOTF(gamma28)
WRAP_SDR_EOTF(iec61966_2_1)

स्थिर शून्य eotf_bt1886(ध्रुव द्विगुण Lw, ध्रुव द्विगुण Lb, द्विगुण E[3])
{
    ध्रुव द्विगुण Lw_inv = घातः(Lw, 1.0 / 2.4);
    ध्रुव द्विगुण Lb_inv = घातः(Lb, 1.0 / 2.4);
    ध्रुव द्विगुण a = घातः(Lw_inv - Lb_inv, 2.4);
    ध्रुव द्विगुण b = Lb_inv / (Lw_inv - Lb_inv);

    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
        E[i] = (-b > E[i]) ? 0.0 : a * घातः(E[i] + b, 2.4);
}

स्थिर शून्य eotf_bt1886_inv(ध्रुव द्विगुण Lw, ध्रुव द्विगुण Lb, द्विगुण L[3])
{
    ध्रुव द्विगुण Lw_inv = घातः(Lw, 1.0 / 2.4);
    ध्रुव द्विगुण Lb_inv = घातः(Lb, 1.0 / 2.4);
    ध्रुव द्विगुण a = घातः(Lw_inv - Lb_inv, 2.4);
    ध्रुव द्विगुण b = Lb_inv / (Lw_inv - Lb_inv);

    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
        L[i] = (0.0 > L[i]) ? 0.0 : घातः(L[i] / a, 1.0 / 2.4) - b;
}

स्थिर शून्य eotf_smpte_st2084(ध्रुव द्विगुण Lw, ध्रुव द्विगुण Lb, द्विगुण E[3])
{
    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
        E[i] = trc_smpte_st2084_inv(E[i]);
}

स्थिर शून्य eotf_smpte_st2084_inv(ध्रुव द्विगुण Lw, ध्रुव द्विगुण Lb, द्विगुण L[3])
{
    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
        L[i] = trc_smpte_st2084(L[i]);
}

/* This implementation assumes an SMPTE RP 431-2 reference projector (DCI) */
#परिभाषय DCI_L 48.00
#परिभाषय DCI_P 52.37
#परिभाषय DCI_X (42.94 / DCI_L)
#परिभाषय DCI_Z (45.82 / DCI_L)

स्थिर शून्य eotf_smpte_st428_1(ध्रुव द्विगुण Lw_Y, ध्रुव द्विगुण Lb_Y, द्विगुण E[3])
{
    ध्रुव द्विगुण Lw[3] = { DCI_X * Lw_Y, Lw_Y, DCI_Z * Lw_Y };
    ध्रुव द्विगुण Lb[3] = { DCI_X * Lb_Y, Lb_Y, DCI_Z * Lb_Y };

    प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
        E[i] = (0.0 > E[i]) ? 0.0 : घातः(E[i], 2.6) * DCI_P / DCI_L;
        E[i] = E[i] * (Lw[i] - Lb[i]) + Lb[i];
    }
}

स्थिर शून्य eotf_smpte_st428_1_inv(ध्रुव द्विगुण Lw_Y, ध्रुव द्विगुण Lb_Y, द्विगुण L[3])
{
    ध्रुव द्विगुण Lw[3] = { DCI_X * Lw_Y, Lw_Y, DCI_Z * Lw_Y };
    ध्रुव द्विगुण Lb[3] = { DCI_X * Lb_Y, Lb_Y, DCI_Z * Lb_Y };

    प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
        L[i] = (L[i] - Lb[i]) / (Lw[i] - Lb[i]);
        L[i] = (0.0 > L[i]) ? 0.0 : घातः(L[i] * DCI_L / DCI_P, 1.0 / 2.6);
    }
}

स्थिर शून्य eotf_arib_std_b67(ध्रुव द्विगुण Lw, ध्रुव द्विगुण Lb, द्विगुण E[3])
{
    ध्रुव द्विगुण gamma = fmax(1.2 + 0.42 * log10(Lw / 1000.0), 1.0);

    /**
     * Note: This equation is technically only accurate if the contrast ratio
     * Lw:Lb is greater than 12:1; otherwise we would need to use a different,
     * significantly more complicated solution. Ignore this as a highly
     * degenerate case, since any real world reference display will have a
     * static contrast ratio multiple orders of magnitude higher.
     */
    ध्रुव द्विगुण beta = वर्गमूलम्(3 * घातः(Lb / Lw, 1.0 / gamma));
    द्विगुण luma;

    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
        E[i] = trc_arib_std_b67_inv((1 - beta) * E[i] + beta);

    luma = 0.2627 * E[0] + 0.6780 * E[1] + 0.0593 * E[2];
    luma = घातः(fmax(luma, 0.0), gamma - 1.0);
    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
        E[i] *= Lw * luma;
}

स्थिर शून्य eotf_arib_std_b67_inv(ध्रुव द्विगुण Lw, ध्रुव द्विगुण Lb, द्विगुण L[3])
{
    ध्रुव द्विगुण gamma = fmax(1.2 + 0.42 * log10(Lw / 1000.0), 1.0);
    ध्रुव द्विगुण beta = वर्गमूलम्(3 * घातः(Lb / Lw, 1 / gamma));
    द्विगुण luma = 0.2627 * L[0] + 0.6780 * L[1] + 0.0593 * L[2];

    यदि (luma > 0.0) {
        luma = घातः(luma / Lw, (1 - gamma) / gamma);
        प्रति (पूर्णाङ्क i = 0; i < 3; i++)
            L[i] *= luma / Lw;
    } अन्यथा {
        L[0] = L[1] = L[2] = 0.0;
    }

    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
        L[i] = (trc_arib_std_b67(L[i]) - beta) / (1 - beta);
}

स्थिर ध्रुव av_csp_eotf_function eotf_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = eotf_bt1886,
    [AVCOL_TRC_GAMMA22] = eotf_gamma22,
    [AVCOL_TRC_GAMMA28] = eotf_gamma28,
    [AVCOL_TRC_SMPTE170M] = eotf_bt1886,
    [AVCOL_TRC_SMPTE240M] = eotf_bt1886,
    [AVCOL_TRC_रैखिकम्] = eotf_रैखिकम्,
    /* There is no EOTF associated with these logarithmic encodings, since they
     * are defined purely for transmission of scene referred data. */
    [AVCOL_TRC_LOG] = रिक्त,
    [AVCOL_TRC_LOG_SQRT] = रिक्त,
    /* BT.1886 is already defined for values below 0.0, as far as physically
     * meaningful, so we can directly use it for extended range encodings */
    [AVCOL_TRC_IEC61966_2_4] = eotf_bt1886,
    [AVCOL_TRC_BT1361_ECG] = eotf_bt1886,
    [AVCOL_TRC_IEC61966_2_1] = eotf_iec61966_2_1,
    [AVCOL_TRC_BT2020_10] = eotf_bt1886,
    [AVCOL_TRC_BT2020_12] = eotf_bt1886,
    [AVCOL_TRC_SMPTE2084] = eotf_smpte_st2084,
    [AVCOL_TRC_SMPTE428] = eotf_smpte_st428_1,
    [AVCOL_TRC_ARIB_STD_B67] = eotf_arib_std_b67,
};

av_csp_eotf_function av_csp_itu_eotf(गणना AVColorTransferCharacteristic trc)
{
    यदि ((अचिह्नित)trc >= AVCOL_TRC_NB)
        प्रत्यागम रिक्त;
    प्रत्यागम eotf_funcs[trc];
}

स्थिर ध्रुव av_csp_eotf_function eotf_inv_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = eotf_bt1886_inv,
    [AVCOL_TRC_GAMMA22] = eotf_gamma22_inv,
    [AVCOL_TRC_GAMMA28] = eotf_gamma28_inv,
    [AVCOL_TRC_SMPTE170M] = eotf_bt1886_inv,
    [AVCOL_TRC_SMPTE240M] = eotf_bt1886_inv,
    [AVCOL_TRC_रैखिकम्] = eotf_रैखिकम्_inv,
    [AVCOL_TRC_LOG] = रिक्त,
    [AVCOL_TRC_LOG_SQRT] = रिक्त,
    [AVCOL_TRC_IEC61966_2_4] = eotf_bt1886_inv,
    [AVCOL_TRC_BT1361_ECG] = eotf_bt1886_inv,
    [AVCOL_TRC_IEC61966_2_1] = eotf_iec61966_2_1_inv,
    [AVCOL_TRC_BT2020_10] = eotf_bt1886_inv,
    [AVCOL_TRC_BT2020_12] = eotf_bt1886_inv,
    [AVCOL_TRC_SMPTE2084] = eotf_smpte_st2084_inv,
    [AVCOL_TRC_SMPTE428] = eotf_smpte_st428_1_inv,
    [AVCOL_TRC_ARIB_STD_B67] = eotf_arib_std_b67_inv,
};

av_csp_eotf_function av_csp_itu_eotf_inv(गणना AVColorTransferCharacteristic trc)
{
    यदि ((अचिह्नित)trc >= AVCOL_TRC_NB)
        प्रत्यागम रिक्त;
    प्रत्यागम eotf_inv_funcs[trc];
}
