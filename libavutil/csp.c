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

#समावेश <stdlib.h>
#समावेश <math.h>

#समावेश "attributes.h"
#समावेश "csp.h"
#समावेश "pixfmt.h"
#समावेश "rational.h"

#घोषणा AVR(d) { (पूर्णांक)(d * 100000 + 0.5), 100000 }

/*
 * All constants explained in e.g. https://linuxtv.org/downloads/v4l-dvb-apis/ch02s06.html
 * The older ones (bt470bg/m) are also explained in their respective ITU docs
 * (e.g. https://www.itu.int/dms_pubrec/itu-r/rec/bt/R-REC-BT.470-5-199802-S!!PDF-E.pdf)
 * whereas the newer ones can typically be copied directly from wikipedia :)
 */
अटल स्थिर काष्ठा AVLumaCoefficients luma_coefficients[AVCOL_SPC_NB] = {
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

स्थिर काष्ठा AVLumaCoefficients *av_csp_luma_coeffs_from_avcsp(क्रमागत AVColorSpace csp)
{
    स्थिर AVLumaCoefficients *coeffs;

    अगर ((अचिन्हित)csp >= AVCOL_SPC_NB)
        वापस शून्य;
    coeffs = &luma_coefficients[csp];
    अगर (!coeffs->cr.अंक)
        वापस शून्य;

    वापस coeffs;
}

#घोषणा WP_D65 { AVR(0.3127), AVR(0.3290) }
#घोषणा WP_C   { AVR(0.3100), AVR(0.3160) }
#घोषणा WP_DCI { AVR(0.3140), AVR(0.3510) }
#घोषणा WP_E   { {1, 3}, {1, 3} }

अटल स्थिर AVColorPrimariesDesc color_primaries[AVCOL_PRI_NB] = {
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

अटल स्थिर AVColorPrimariesDesc color_primaries_ext[AVCOL_PRI_EXT_NB -
                                                      AVCOL_PRI_EXT_BASE] = {
    [AVCOL_PRI_V_GAMUT - AVCOL_PRI_EXT_BASE] = { WP_D65, { { AVR(0.730), AVR(0.280) }, { AVR(0.165), AVR(0.840) }, { AVR(0.100), AVR(-0.030) } } },
};

स्थिर AVColorPrimariesDesc *av_csp_primaries_desc_from_id(क्रमागत AVColorPrimaries prm)
{
    स्थिर AVColorPrimariesDesc *p = शून्य;
    अगर ((अचिन्हित)prm < AVCOL_PRI_NB)
        p = &color_primaries[prm];
    अन्यथा अगर (((अचिन्हित)prm >= AVCOL_PRI_EXT_BASE) &&
             ((अचिन्हित)prm < AVCOL_PRI_EXT_NB))
        p = &color_primaries_ext[prm - AVCOL_PRI_EXT_BASE];
    अगर (!p || !p->prim.r.x.अंक)
        वापस शून्य;
    वापस p;
}

अटल av_always_inline AVRational abs_sub_q(AVRational r1, AVRational r2)
{
    AVRational diff = av_sub_q(r1, r2);
    /* denominator assumed to be positive */
    वापस av_make_q(असल(diff.अंक), diff.den);
}

क्रमागत AVColorPrimaries av_csp_primaries_id_from_desc(स्थिर AVColorPrimariesDesc *prm)
{
    AVRational delta;

    क्रम (क्रमागत AVColorPrimaries p = 0; p < AVCOL_PRI_NB; p++) {
        स्थिर AVColorPrimariesDesc *ref = &color_primaries[p];
        अगर (!ref->prim.r.x.अंक)
            जारी;

        delta = abs_sub_q(prm->prim.r.x, ref->prim.r.x);
        delta = av_add_q(delta, abs_sub_q(prm->prim.r.y, ref->prim.r.y));
        delta = av_add_q(delta, abs_sub_q(prm->prim.g.x, ref->prim.g.x));
        delta = av_add_q(delta, abs_sub_q(prm->prim.g.y, ref->prim.g.y));
        delta = av_add_q(delta, abs_sub_q(prm->prim.b.x, ref->prim.b.x));
        delta = av_add_q(delta, abs_sub_q(prm->prim.b.y, ref->prim.b.y));
        delta = av_add_q(delta, abs_sub_q(prm->wp.x, ref->wp.x));
        delta = av_add_q(delta, abs_sub_q(prm->wp.y, ref->wp.y));

        अगर (av_cmp_q(delta, av_make_q(1, 1000)) < 0)
            वापस p;
    }

    वापस AVCOL_PRI_UNSPECIFIED;
}

अटल स्थिर द्विगुन approximate_gamma[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = 1.961,
    [AVCOL_TRC_SMPTE170M] = 1.961,
    [AVCOL_TRC_SMPTE240M] = 1.961,
    [AVCOL_TRC_BT1361_ECG] = 1.961,
    [AVCOL_TRC_BT2020_10] = 1.961,
    [AVCOL_TRC_BT2020_12] = 1.961,
    [AVCOL_TRC_GAMMA22] = 2.2,
    [AVCOL_TRC_IEC61966_2_1] = 2.2,
    [AVCOL_TRC_GAMMA28] = 2.8,
    [AVCOL_TRC_LINEAR] = 1.0,
    [AVCOL_TRC_SMPTE428] = 2.6,
};

अटल स्थिर द्विगुन approximate_gamma_ext[AVCOL_TRC_EXT_NB -
                                          AVCOL_TRC_EXT_BASE] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_BASE] = 2.2,
};

द्विगुन av_csp_approximate_trc_gamma(क्रमागत AVColorTransferCharacteristic trc)
{
    अगर (trc < AVCOL_TRC_NB)
        वापस approximate_gamma[trc];
    अन्यथा अगर ((trc >= AVCOL_TRC_EXT_BASE) && (trc < AVCOL_TRC_EXT_NB))
        वापस approximate_gamma_ext[trc - AVCOL_TRC_EXT_BASE];
    वापस 0.0;
}

अटल स्थिर द्विगुन approximate_eotf_gamma[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = 2.2,
    [AVCOL_TRC_SMPTE170M] = 2.2,
    [AVCOL_TRC_SMPTE240M] = 2.2,
    [AVCOL_TRC_BT1361_ECG] = 2.2,
    [AVCOL_TRC_BT2020_10] = 2.2,
    [AVCOL_TRC_BT2020_12] = 2.2,
    [AVCOL_TRC_GAMMA22] = 2.2,
    [AVCOL_TRC_IEC61966_2_1] = 2.2,
    [AVCOL_TRC_GAMMA28] = 2.8,
    [AVCOL_TRC_LINEAR] = 1.0,
    [AVCOL_TRC_SMPTE428] = 2.6,
};

अटल स्थिर द्विगुन approximate_eotf_gamma_ext[AVCOL_TRC_EXT_NB -
                                               AVCOL_TRC_EXT_BASE] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_BASE] = 2.2,
};

द्विगुन av_csp_approximate_eotf_gamma(क्रमागत AVColorTransferCharacteristic trc)
{
    अगर ((अचिन्हित)trc < AVCOL_TRC_NB)
        वापस approximate_eotf_gamma[trc];
    अन्यथा अगर (((अचिन्हित)trc >= AVCOL_TRC_EXT_BASE) &&
             ((अचिन्हित)trc < AVCOL_TRC_EXT_NB))
        वापस approximate_eotf_gamma_ext[trc - AVCOL_TRC_EXT_BASE];
    वापस 0.0;
}

#घोषणा BT709_alpha 1.099296826809442
#घोषणा BT709_beta 0.018053968510807

अटल द्विगुन trc_bt709(द्विगुन Lc)
{
    स्थिर द्विगुन a = BT709_alpha;
    स्थिर द्विगुन b = BT709_beta;

    वापस (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 4.500 * Lc
         :              a * घात(Lc, 0.45) - (a - 1.0);
}

अटल द्विगुन trc_bt709_inv(द्विगुन E)
{
    स्थिर द्विगुन a = BT709_alpha;
    स्थिर द्विगुन b = 4.500 * BT709_beta;

    वापस (0.0 > E) ? 0.0
         : (  b > E) ? E / 4.500
         :             घात((E + (a - 1.0)) / a, 1.0 / 0.45);
}

अटल द्विगुन trc_gamma22(द्विगुन Lc)
{
    वापस (0.0 > Lc) ? 0.0 : घात(Lc, 1.0/ 2.2);
}

अटल द्विगुन trc_gamma22_inv(द्विगुन E)
{
    वापस (0.0 > E) ? 0.0 : घात(E, 2.2);
}

अटल द्विगुन trc_gamma28(द्विगुन Lc)
{
    वापस (0.0 > Lc) ? 0.0 : घात(Lc, 1.0/ 2.8);
}

अटल द्विगुन trc_gamma28_inv(द्विगुन E)
{
    वापस (0.0 > E) ? 0.0 : घात(E, 2.8);
}

अटल द्विगुन trc_smpte240M(द्विगुन Lc)
{
    स्थिर द्विगुन a = 1.1115;
    स्थिर द्विगुन b = 0.0228;

    वापस (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 4.000 * Lc
         :              a * घात(Lc, 0.45) - (a - 1.0);
}

अटल द्विगुन trc_smpte240M_inv(द्विगुन E)
{
    स्थिर द्विगुन a = 1.1115;
    स्थिर द्विगुन b = 4.000 * 0.0228;

    वापस (0.0 > E) ? 0.0
         : (  b > E) ? E / 4.000
         :             घात((E + (a - 1.0)) / a, 1.0 / 0.45);
}

अटल द्विगुन trc_linear(द्विगुन Lc)
{
    वापस Lc;
}

अटल द्विगुन trc_log(द्विगुन Lc)
{
    वापस (0.01 > Lc) ? 0.0 : 1.0 + log10(Lc) / 2.0;
}

अटल द्विगुन trc_log_inv(द्विगुन E)
{
    वापस (0.0 > E) ? 0.01 : घात(10.0, 2.0 * (E - 1.0));
}

अटल द्विगुन trc_log_sqrt(द्विगुन Lc)
{
    // sqrt(10) / 1000
    वापस (0.00316227766 > Lc) ? 0.0 : 1.0 + log10(Lc) / 2.5;
}

अटल द्विगुन trc_log_sqrt_inv(द्विगुन E)
{
    वापस (0.0 > E) ? 0.00316227766 : घात(10.0, 2.5 * (E - 1.0));
}

अटल द्विगुन trc_iec61966_2_4(द्विगुन Lc)
{
    स्थिर द्विगुन a = BT709_alpha;
    स्थिर द्विगुन b = BT709_beta;

    वापस (-b >= Lc) ? -a * घात(-Lc, 0.45) + (a - 1.0)
         : ( b >  Lc) ? 4.500 * Lc
         :               a * घात( Lc, 0.45) - (a - 1.0);
}

अटल द्विगुन trc_iec61966_2_4_inv(द्विगुन E)
{
    स्थिर द्विगुन a = BT709_alpha;
    स्थिर द्विगुन b = 4.500 * BT709_beta;

    वापस (-b >= E) ? -घात((-E + (a - 1.0)) / a, 1.0 / 0.45)
         : ( b >  E) ? E / 4.500
         :              घात(( E + (a - 1.0)) / a, 1.0 / 0.45);
}

अटल द्विगुन trc_bt1361(द्विगुन Lc)
{
    स्थिर द्विगुन a = BT709_alpha;
    स्थिर द्विगुन b = BT709_beta;

    वापस (-0.0045 >= Lc) ? -(a * घात(-4.0 * Lc, 0.45) + (a - 1.0)) / 4.0
         : ( b >  Lc) ? 4.500 * Lc
         :               a * घात( Lc, 0.45) - (a - 1.0);
}

अटल द्विगुन trc_bt1361_inv(द्विगुन E)
{
    स्थिर द्विगुन a = BT709_alpha;
    स्थिर द्विगुन b = 4.500 * BT709_beta;

    वापस (-0.02025 >= E) ? -घात((-4.0 * E - (a - 1.0)) / a, 1.0 / 0.45) / 4.0
         : ( b       >  E) ? E / 4.500
         :                    घात(( E + (a - 1.0)) / a, 1.0 / 0.45);
}

अटल द्विगुन trc_iec61966_2_1(द्विगुन Lc)
{
    स्थिर द्विगुन a = 1.055;
    स्थिर द्विगुन b = 0.0031308;

    वापस (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 12.92 * Lc
         :              a * घात(Lc, 1.0  / 2.4) - (a - 1.0);
}

अटल द्विगुन trc_iec61966_2_1_inv(द्विगुन E)
{
    स्थिर द्विगुन a = 1.055;
    स्थिर द्विगुन b = 12.92 * 0.0031308;

    वापस (0.0 > E) ? 0.0
         : (  b > E) ? E / 12.92
                     : घात((E + (a - 1.0)) / a, 2.4);
    वापस E;
}

#घोषणा PQ_c1 (        3424.0 / 4096.0) /* c3-c2 + 1 */
#घोषणा PQ_c2 ( 32.0 * 2413.0 / 4096.0)
#घोषणा PQ_c3 ( 32.0 * 2392.0 / 4096.0)
#घोषणा PQ_m  (128.0 * 2523.0 / 4096.0)
#घोषणा PQ_n  ( 0.25 * 2610.0 / 4096.0)

अटल द्विगुन trc_smpte_st2084(द्विगुन Lc)
{
    स्थिर द्विगुन c1 = PQ_c1;
    स्थिर द्विगुन c2 = PQ_c2;
    स्थिर द्विगुन c3 = PQ_c3;
    स्थिर द्विगुन m  = PQ_m;
    स्थिर द्विगुन n  = PQ_n;
    स्थिर द्विगुन L  = Lc / 10000.0;
    स्थिर द्विगुन Ln = घात(L, n);

    वापस (0.0 > Lc) ? 0.0
         :              घात((c1 + c2 * Ln) / (1.0 + c3 * Ln), m);

}

अटल द्विगुन trc_smpte_st2084_inv(द्विगुन E)
{
    स्थिर द्विगुन c1 = PQ_c1;
    स्थिर द्विगुन c2 = PQ_c2;
    स्थिर द्विगुन c3 = PQ_c3;
    स्थिर द्विगुन m  = PQ_m;
    स्थिर द्विगुन n  = PQ_n;
    स्थिर द्विगुन Em = घात(E, 1.0 / m);

    वापस (c1 > Em) ? 0.0
                     : 10000.0 * घात((Em - c1) / (c2 - c3 * Em), 1.0 / n);
}

#घोषणा DCI_L 48.00
#घोषणा DCI_P 52.37

अटल द्विगुन trc_smpte_st428_1(द्विगुन Lc)
{
    वापस (0.0 > Lc) ? 0.0 : घात(DCI_L / DCI_P * Lc, 1.0 / 2.6);
}

अटल द्विगुन trc_smpte_st428_1_inv(द्विगुन E)
{
    वापस (0.0 > E) ? 0.0 : DCI_P / DCI_L * घात(E, 2.6);
}

#घोषणा HLG_a 0.17883277
#घोषणा HLG_b 0.28466892
#घोषणा HLG_c 0.55991073

अटल द्विगुन trc_arib_std_b67(द्विगुन Lc) {
    // The function uses the definition from HEVC, which assumes that the peak
    // white is input level = 1. (this is equivalent to scaling E = Lc * 12 and
    // using the definition from the ARIB STD-B67 spec)
    स्थिर द्विगुन a = HLG_a;
    स्थिर द्विगुन b = HLG_b;
    स्थिर द्विगुन c = HLG_c;
    वापस (0.0 > Lc) ? 0.0 :
        (Lc <= 1.0 / 12.0 ? वर्ग_मूल(3.0 * Lc) : a * log(12.0 * Lc - b) + c);
}

अटल द्विगुन trc_arib_std_b67_inv(द्विगुन E)
{
    स्थिर द्विगुन a = HLG_a;
    स्थिर द्विगुन b = HLG_b;
    स्थिर द्विगुन c = HLG_c;
    वापस (0.0 > E) ? 0.0 :
        (E <= 0.5 ? E * E / 3.0 : (exp((E - c) / a) + b) / 12.0);
}

#घोषणा VLOG_c1 0.01
#घोषणा VLOG_c2 0.181
#घोषणा VLOG_b  0.00873
#घोषणा VLOG_c  0.241514
#घोषणा VLOG_d  0.598206

अटल द्विगुन trc_v_log(द्विगुन E)
{
    स्थिर द्विगुन c1 = VLOG_c1;
    स्थिर द्विगुन b = VLOG_b;
    स्थिर द्विगुन c = VLOG_c;
    स्थिर द्विगुन d = VLOG_d;
    वापस (E < c1) ? (5.6 * E + 0.125) :
        (c * log10(E + b) + d);
}

अटल द्विगुन trc_v_log_inv(द्विगुन E)
{
    स्थिर द्विगुन c2 = VLOG_c2;
    स्थिर द्विगुन b = VLOG_b;
    स्थिर द्विगुन c = VLOG_c;
    स्थिर द्विगुन d = VLOG_d;
    वापस (E < c2) ? (E - 0.125) / 5.6 :
        (घात(10.0, ((E - d) / c)) - b);
}

अटल स्थिर av_csp_trc_function trc_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = trc_bt709,
    [AVCOL_TRC_GAMMA22] = trc_gamma22,
    [AVCOL_TRC_GAMMA28] = trc_gamma28,
    [AVCOL_TRC_SMPTE170M] = trc_bt709,
    [AVCOL_TRC_SMPTE240M] = trc_smpte240M,
    [AVCOL_TRC_LINEAR] = trc_linear,
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

अटल स्थिर av_csp_trc_function trc_funcs_ext[AVCOL_TRC_EXT_NB -
                                               AVCOL_TRC_EXT_BASE] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_BASE] = trc_v_log,
};

av_csp_trc_function av_csp_trc_func_from_id(क्रमागत AVColorTransferCharacteristic trc)
{
    अगर ((अचिन्हित)trc < AVCOL_TRC_NB)
        वापस trc_funcs[trc];
    अन्यथा अगर (((अचिन्हित)trc >= AVCOL_TRC_EXT_BASE) &&
             ((अचिन्हित)trc < AVCOL_TRC_EXT_NB))
        वापस trc_funcs_ext[trc - AVCOL_TRC_EXT_BASE];
    वापस शून्य;
}

अटल स्थिर av_csp_trc_function trc_inv_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = trc_bt709_inv,
    [AVCOL_TRC_GAMMA22] = trc_gamma22_inv,
    [AVCOL_TRC_GAMMA28] = trc_gamma28_inv,
    [AVCOL_TRC_SMPTE170M] = trc_bt709_inv,
    [AVCOL_TRC_SMPTE240M] = trc_smpte240M_inv,
    [AVCOL_TRC_LINEAR] = trc_linear,
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

अटल स्थिर av_csp_trc_function trc_inv_funcs_ext[AVCOL_TRC_EXT_NB -
                                                   AVCOL_TRC_EXT_BASE] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_BASE] = trc_v_log_inv,
};

av_csp_trc_function av_csp_trc_func_inv_from_id(क्रमागत AVColorTransferCharacteristic trc)
{
    अगर ((अचिन्हित)trc < AVCOL_TRC_NB)
        वापस trc_inv_funcs[trc];
    अन्यथा अगर (((अचिन्हित)trc >= AVCOL_TRC_EXT_BASE) &&
             ((अचिन्हित)trc < AVCOL_TRC_EXT_NB))
        वापस trc_inv_funcs_ext[trc - AVCOL_TRC_EXT_BASE];
    वापस शून्य;
}

अटल व्योम eotf_linear(स्थिर द्विगुन Lw, स्थिर द्विगुन Lb, द्विगुन E[3])
{
    क्रम (पूर्णांक i = 0; i < 3; i++)
        E[i] = (Lw - Lb) * E[i] + Lb;
}

अटल व्योम eotf_linear_inv(स्थिर द्विगुन Lw, स्थिर द्विगुन Lb, द्विगुन L[3])
{
    क्रम (पूर्णांक i = 0; i < 3; i++)
        L[i] = (L[i] - Lb) / (Lw - Lb);
}

#घोषणा WRAP_SDR_OETF(name)                                         \
अटल व्योम oetf_##name(द्विगुन L[3])                                \
{                                                                   \
    क्रम (पूर्णांक i = 0; i < 3; i++)                                     \
        L[i] = trc_##name(L[i]);                                    \
}                                                                   \
                                                                    \
अटल व्योम oetf_##name##_inv(द्विगुन E[3])                          \
{                                                                   \
    क्रम (पूर्णांक i = 0; i < 3; i++)                                     \
        E[i] = trc_##name##_inv(E[i]);                              \
}

WRAP_SDR_OETF(gamma22)
WRAP_SDR_OETF(gamma28)
WRAP_SDR_OETF(iec61966_2_1)

#घोषणा WRAP_SDR_EOTF(name)                                         \
अटल व्योम eotf_##name(द्विगुन Lw, द्विगुन Lb, द्विगुन E[3])          \
{                                                                   \
    oetf_##name##_inv(E);                                           \
    eotf_linear(Lw, Lb, E);                                         \
}                                                                   \
                                                                    \
अटल व्योम eotf_##name##_inv(द्विगुन Lw, द्विगुन Lb, द्विगुन L[3])    \
{                                                                   \
    eotf_linear_inv(Lw, Lb, L);                                     \
    oetf_##name(L);                                                 \
}

WRAP_SDR_EOTF(gamma22)
WRAP_SDR_EOTF(gamma28)
WRAP_SDR_EOTF(iec61966_2_1)

अटल व्योम eotf_bt1886(स्थिर द्विगुन Lw, स्थिर द्विगुन Lb, द्विगुन E[3])
{
    स्थिर द्विगुन Lw_inv = घात(Lw, 1.0 / 2.4);
    स्थिर द्विगुन Lb_inv = घात(Lb, 1.0 / 2.4);
    स्थिर द्विगुन a = घात(Lw_inv - Lb_inv, 2.4);
    स्थिर द्विगुन b = Lb_inv / (Lw_inv - Lb_inv);

    क्रम (पूर्णांक i = 0; i < 3; i++)
        E[i] = (-b > E[i]) ? 0.0 : a * घात(E[i] + b, 2.4);
}

अटल व्योम eotf_bt1886_inv(स्थिर द्विगुन Lw, स्थिर द्विगुन Lb, द्विगुन L[3])
{
    स्थिर द्विगुन Lw_inv = घात(Lw, 1.0 / 2.4);
    स्थिर द्विगुन Lb_inv = घात(Lb, 1.0 / 2.4);
    स्थिर द्विगुन a = घात(Lw_inv - Lb_inv, 2.4);
    स्थिर द्विगुन b = Lb_inv / (Lw_inv - Lb_inv);

    क्रम (पूर्णांक i = 0; i < 3; i++)
        L[i] = (0.0 > L[i]) ? 0.0 : घात(L[i] / a, 1.0 / 2.4) - b;
}

अटल व्योम eotf_smpte_st2084(स्थिर द्विगुन Lw, स्थिर द्विगुन Lb, द्विगुन E[3])
{
    क्रम (पूर्णांक i = 0; i < 3; i++)
        E[i] = trc_smpte_st2084_inv(E[i]);
}

अटल व्योम eotf_smpte_st2084_inv(स्थिर द्विगुन Lw, स्थिर द्विगुन Lb, द्विगुन L[3])
{
    क्रम (पूर्णांक i = 0; i < 3; i++)
        L[i] = trc_smpte_st2084(L[i]);
}

/* This implementation assumes an SMPTE RP 431-2 reference projector (DCI) */
#घोषणा DCI_L 48.00
#घोषणा DCI_P 52.37
#घोषणा DCI_X (42.94 / DCI_L)
#घोषणा DCI_Z (45.82 / DCI_L)

अटल व्योम eotf_smpte_st428_1(स्थिर द्विगुन Lw_Y, स्थिर द्विगुन Lb_Y, द्विगुन E[3])
{
    स्थिर द्विगुन Lw[3] = { DCI_X * Lw_Y, Lw_Y, DCI_Z * Lw_Y };
    स्थिर द्विगुन Lb[3] = { DCI_X * Lb_Y, Lb_Y, DCI_Z * Lb_Y };

    क्रम (पूर्णांक i = 0; i < 3; i++) {
        E[i] = (0.0 > E[i]) ? 0.0 : घात(E[i], 2.6) * DCI_P / DCI_L;
        E[i] = E[i] * (Lw[i] - Lb[i]) + Lb[i];
    }
}

अटल व्योम eotf_smpte_st428_1_inv(स्थिर द्विगुन Lw_Y, स्थिर द्विगुन Lb_Y, द्विगुन L[3])
{
    स्थिर द्विगुन Lw[3] = { DCI_X * Lw_Y, Lw_Y, DCI_Z * Lw_Y };
    स्थिर द्विगुन Lb[3] = { DCI_X * Lb_Y, Lb_Y, DCI_Z * Lb_Y };

    क्रम (पूर्णांक i = 0; i < 3; i++) {
        L[i] = (L[i] - Lb[i]) / (Lw[i] - Lb[i]);
        L[i] = (0.0 > L[i]) ? 0.0 : घात(L[i] * DCI_L / DCI_P, 1.0 / 2.6);
    }
}

अटल व्योम eotf_arib_std_b67(स्थिर द्विगुन Lw, स्थिर द्विगुन Lb, द्विगुन E[3])
{
    स्थिर द्विगुन gamma = fmax(1.2 + 0.42 * log10(Lw / 1000.0), 1.0);

    /**
     * Note: This equation is technically only accurate if the contrast ratio
     * Lw:Lb is greater than 12:1; otherwise we would need to use a different,
     * significantly more complicated solution. Ignore this as a highly
     * degenerate case, since any real world reference display will have a
     * static contrast ratio multiple orders of magnitude higher.
     */
    स्थिर द्विगुन beta = वर्ग_मूल(3 * घात(Lb / Lw, 1.0 / gamma));
    द्विगुन luma;

    क्रम (पूर्णांक i = 0; i < 3; i++)
        E[i] = trc_arib_std_b67_inv((1 - beta) * E[i] + beta);

    luma = 0.2627 * E[0] + 0.6780 * E[1] + 0.0593 * E[2];
    luma = घात(fmax(luma, 0.0), gamma - 1.0);
    क्रम (पूर्णांक i = 0; i < 3; i++)
        E[i] *= Lw * luma;
}

अटल व्योम eotf_arib_std_b67_inv(स्थिर द्विगुन Lw, स्थिर द्विगुन Lb, द्विगुन L[3])
{
    स्थिर द्विगुन gamma = fmax(1.2 + 0.42 * log10(Lw / 1000.0), 1.0);
    स्थिर द्विगुन beta = वर्ग_मूल(3 * घात(Lb / Lw, 1 / gamma));
    द्विगुन luma = 0.2627 * L[0] + 0.6780 * L[1] + 0.0593 * L[2];

    अगर (luma > 0.0) {
        luma = घात(luma / Lw, (1 - gamma) / gamma);
        क्रम (पूर्णांक i = 0; i < 3; i++)
            L[i] *= luma / Lw;
    } अन्यथा {
        L[0] = L[1] = L[2] = 0.0;
    }

    क्रम (पूर्णांक i = 0; i < 3; i++)
        L[i] = (trc_arib_std_b67(L[i]) - beta) / (1 - beta);
}

अटल स्थिर av_csp_eotf_function eotf_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = eotf_bt1886,
    [AVCOL_TRC_GAMMA22] = eotf_gamma22,
    [AVCOL_TRC_GAMMA28] = eotf_gamma28,
    [AVCOL_TRC_SMPTE170M] = eotf_bt1886,
    [AVCOL_TRC_SMPTE240M] = eotf_bt1886,
    [AVCOL_TRC_LINEAR] = eotf_linear,
    /* There is no EOTF associated with these logarithmic encodings, since they
     * are defined purely for transmission of scene referred data. */
    [AVCOL_TRC_LOG] = शून्य,
    [AVCOL_TRC_LOG_SQRT] = शून्य,
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

av_csp_eotf_function av_csp_itu_eotf(क्रमागत AVColorTransferCharacteristic trc)
{
    अगर ((अचिन्हित)trc >= AVCOL_TRC_NB)
        वापस शून्य;
    वापस eotf_funcs[trc];
}

अटल स्थिर av_csp_eotf_function eotf_inv_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = eotf_bt1886_inv,
    [AVCOL_TRC_GAMMA22] = eotf_gamma22_inv,
    [AVCOL_TRC_GAMMA28] = eotf_gamma28_inv,
    [AVCOL_TRC_SMPTE170M] = eotf_bt1886_inv,
    [AVCOL_TRC_SMPTE240M] = eotf_bt1886_inv,
    [AVCOL_TRC_LINEAR] = eotf_linear_inv,
    [AVCOL_TRC_LOG] = शून्य,
    [AVCOL_TRC_LOG_SQRT] = शून्य,
    [AVCOL_TRC_IEC61966_2_4] = eotf_bt1886_inv,
    [AVCOL_TRC_BT1361_ECG] = eotf_bt1886_inv,
    [AVCOL_TRC_IEC61966_2_1] = eotf_iec61966_2_1_inv,
    [AVCOL_TRC_BT2020_10] = eotf_bt1886_inv,
    [AVCOL_TRC_BT2020_12] = eotf_bt1886_inv,
    [AVCOL_TRC_SMPTE2084] = eotf_smpte_st2084_inv,
    [AVCOL_TRC_SMPTE428] = eotf_smpte_st428_1_inv,
    [AVCOL_TRC_ARIB_STD_B67] = eotf_arib_std_b67_inv,
};

av_csp_eotf_function av_csp_itu_eotf_inv(क्रमागत AVColorTransferCharacteristic trc)
{
    अगर ((अचिन्हित)trc >= AVCOL_TRC_NB)
        वापस शून्य;
    वापस eotf_inv_funcs[trc];
}
