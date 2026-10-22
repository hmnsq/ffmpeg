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

#ضمن <stdlib.h>
#ضمن <math.h>

#ضمن "attributes.h"
#ضمن "csp.h"
#ضمن "pixfmt.h"
#ضمن "rational.h"

#define AVR(d) { (صحيح)(d * 100000 + 0.5), 100000 }

/*
 * All constants explained in e.g. https://linuxtv.org/downloads/v4l-dvb-apis/ch02s06.html
 * The older ones (bt470bg/m) are also explained in their respective ITU docs
 * (e.g. https://www.itu.int/dms_pubrec/itu-r/rec/bt/R-REC-BT.470-5-199802-S!!PDF-E.pdf)
 * whereas the newer ones can typically be copied directly from wikipedia :)
 */
ساكن ثابت بنية AVLumaCoefficients luma_coefficients[AVCOL_SPC_NB] = {
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

ثابت بنية AVLumaCoefficients *av_csp_luma_coeffs_from_avcsp(تعداد AVColorSpace csp)
{
    ثابت AVLumaCoefficients *coeffs;

    אם ((unsigned)csp >= AVCOL_SPC_NB)
        החזר عدم;
    coeffs = &luma_coefficients[csp];
    אם (!coeffs->cr.num)
        החזר عدم;

    החזר coeffs;
}

#define WP_D65 { AVR(0.3127), AVR(0.3290) }
#define WP_C   { AVR(0.3100), AVR(0.3160) }
#define WP_DCI { AVR(0.3140), AVR(0.3510) }
#define WP_E   { {1, 3}, {1, 3} }

ساكن ثابت AVColorPrimariesDesc color_primaries[AVCOL_PRI_NB] = {
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

ساكن ثابت AVColorPrimariesDesc color_primaries_ext[AVCOL_PRI_EXT_NB -
                                                      AVCOL_PRI_EXT_BASE] = {
    [AVCOL_PRI_V_GAMUT - AVCOL_PRI_EXT_BASE] = { WP_D65, { { AVR(0.730), AVR(0.280) }, { AVR(0.165), AVR(0.840) }, { AVR(0.100), AVR(-0.030) } } },
};

ثابت AVColorPrimariesDesc *av_csp_primaries_desc_from_id(تعداد AVColorPrimaries prm)
{
    ثابت AVColorPrimariesDesc *p = عدم;
    אם ((unsigned)prm < AVCOL_PRI_NB)
        p = &color_primaries[prm];
    אחרת אם (((unsigned)prm >= AVCOL_PRI_EXT_BASE) &&
             ((unsigned)prm < AVCOL_PRI_EXT_NB))
        p = &color_primaries_ext[prm - AVCOL_PRI_EXT_BASE];
    אם (!p || !p->prim.r.x.num)
        החזר عدم;
    החזר p;
}

ساكن av_always_inline AVRational abs_sub_q(AVRational r1, AVRational r2)
{
    AVRational diff = av_sub_q(r1, r2);
    /* denominator assumed to be positive */
    החזר av_make_q(abs(diff.num), diff.den);
}

تعداد AVColorPrimaries av_csp_primaries_id_from_desc(ثابت AVColorPrimariesDesc *prm)
{
    AVRational delta;

    עבור (تعداد AVColorPrimaries p = 0; p < AVCOL_PRI_NB; p++) {
        ثابت AVColorPrimariesDesc *ref = &color_primaries[p];
        אם (!ref->prim.r.x.num)
            استمر;

        delta = abs_sub_q(prm->prim.r.x, ref->prim.r.x);
        delta = av_add_q(delta, abs_sub_q(prm->prim.r.y, ref->prim.r.y));
        delta = av_add_q(delta, abs_sub_q(prm->prim.g.x, ref->prim.g.x));
        delta = av_add_q(delta, abs_sub_q(prm->prim.g.y, ref->prim.g.y));
        delta = av_add_q(delta, abs_sub_q(prm->prim.b.x, ref->prim.b.x));
        delta = av_add_q(delta, abs_sub_q(prm->prim.b.y, ref->prim.b.y));
        delta = av_add_q(delta, abs_sub_q(prm->wp.x, ref->wp.x));
        delta = av_add_q(delta, abs_sub_q(prm->wp.y, ref->wp.y));

        אם (av_cmp_q(delta, av_make_q(1, 1000)) < 0)
            החזר p;
    }

    החזר AVCOL_PRI_UNSPECIFIED;
}

ساكن ثابت مزدوج approximate_gamma[AVCOL_TRC_NB] = {
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

ساكن ثابت مزدوج approximate_gamma_ext[AVCOL_TRC_EXT_NB -
                                          AVCOL_TRC_EXT_BASE] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_BASE] = 2.2,
};

مزدوج av_csp_approximate_trc_gamma(تعداد AVColorTransferCharacteristic trc)
{
    אם (trc < AVCOL_TRC_NB)
        החזר approximate_gamma[trc];
    אחרת אם ((trc >= AVCOL_TRC_EXT_BASE) && (trc < AVCOL_TRC_EXT_NB))
        החזר approximate_gamma_ext[trc - AVCOL_TRC_EXT_BASE];
    החזר 0.0;
}

ساكن ثابت مزدوج approximate_eotf_gamma[AVCOL_TRC_NB] = {
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

ساكن ثابت مزدوج approximate_eotf_gamma_ext[AVCOL_TRC_EXT_NB -
                                               AVCOL_TRC_EXT_BASE] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_BASE] = 2.2,
};

مزدوج av_csp_approximate_eotf_gamma(تعداد AVColorTransferCharacteristic trc)
{
    אם ((unsigned)trc < AVCOL_TRC_NB)
        החזר approximate_eotf_gamma[trc];
    אחרת אם (((unsigned)trc >= AVCOL_TRC_EXT_BASE) &&
             ((unsigned)trc < AVCOL_TRC_EXT_NB))
        החזר approximate_eotf_gamma_ext[trc - AVCOL_TRC_EXT_BASE];
    החזר 0.0;
}

#define BT709_alpha 1.099296826809442
#define BT709_beta 0.018053968510807

ساكن مزدوج trc_bt709(مزدوج Lc)
{
    ثابت مزدوج a = BT709_alpha;
    ثابت مزدوج b = BT709_beta;

    החזר (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 4.500 * Lc
         :              a * pow(Lc, 0.45) - (a - 1.0);
}

ساكن مزدوج trc_bt709_inv(مزدوج E)
{
    ثابت مزدوج a = BT709_alpha;
    ثابت مزدوج b = 4.500 * BT709_beta;

    החזר (0.0 > E) ? 0.0
         : (  b > E) ? E / 4.500
         :             pow((E + (a - 1.0)) / a, 1.0 / 0.45);
}

ساكن مزدوج trc_gamma22(مزدوج Lc)
{
    החזר (0.0 > Lc) ? 0.0 : pow(Lc, 1.0/ 2.2);
}

ساكن مزدوج trc_gamma22_inv(مزدوج E)
{
    החזר (0.0 > E) ? 0.0 : pow(E, 2.2);
}

ساكن مزدوج trc_gamma28(مزدوج Lc)
{
    החזר (0.0 > Lc) ? 0.0 : pow(Lc, 1.0/ 2.8);
}

ساكن مزدوج trc_gamma28_inv(مزدوج E)
{
    החזר (0.0 > E) ? 0.0 : pow(E, 2.8);
}

ساكن مزدوج trc_smpte240M(مزدوج Lc)
{
    ثابت مزدوج a = 1.1115;
    ثابت مزدوج b = 0.0228;

    החזר (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 4.000 * Lc
         :              a * pow(Lc, 0.45) - (a - 1.0);
}

ساكن مزدوج trc_smpte240M_inv(مزدوج E)
{
    ثابت مزدوج a = 1.1115;
    ثابت مزدوج b = 4.000 * 0.0228;

    החזר (0.0 > E) ? 0.0
         : (  b > E) ? E / 4.000
         :             pow((E + (a - 1.0)) / a, 1.0 / 0.45);
}

ساكن مزدوج trc_linear(مزدوج Lc)
{
    החזר Lc;
}

ساكن مزدوج trc_log(مزدوج Lc)
{
    החזר (0.01 > Lc) ? 0.0 : 1.0 + log10(Lc) / 2.0;
}

ساكن مزدوج trc_log_inv(مزدوج E)
{
    החזר (0.0 > E) ? 0.01 : pow(10.0, 2.0 * (E - 1.0));
}

ساكن مزدوج trc_log_sqrt(مزدوج Lc)
{
    // sqrt(10) / 1000
    החזר (0.00316227766 > Lc) ? 0.0 : 1.0 + log10(Lc) / 2.5;
}

ساكن مزدوج trc_log_sqrt_inv(مزدوج E)
{
    החזר (0.0 > E) ? 0.00316227766 : pow(10.0, 2.5 * (E - 1.0));
}

ساكن مزدوج trc_iec61966_2_4(مزدوج Lc)
{
    ثابت مزدوج a = BT709_alpha;
    ثابت مزدوج b = BT709_beta;

    החזר (-b >= Lc) ? -a * pow(-Lc, 0.45) + (a - 1.0)
         : ( b >  Lc) ? 4.500 * Lc
         :               a * pow( Lc, 0.45) - (a - 1.0);
}

ساكن مزدوج trc_iec61966_2_4_inv(مزدوج E)
{
    ثابت مزدوج a = BT709_alpha;
    ثابت مزدوج b = 4.500 * BT709_beta;

    החזר (-b >= E) ? -pow((-E + (a - 1.0)) / a, 1.0 / 0.45)
         : ( b >  E) ? E / 4.500
         :              pow(( E + (a - 1.0)) / a, 1.0 / 0.45);
}

ساكن مزدوج trc_bt1361(مزدوج Lc)
{
    ثابت مزدوج a = BT709_alpha;
    ثابت مزدوج b = BT709_beta;

    החזר (-0.0045 >= Lc) ? -(a * pow(-4.0 * Lc, 0.45) + (a - 1.0)) / 4.0
         : ( b >  Lc) ? 4.500 * Lc
         :               a * pow( Lc, 0.45) - (a - 1.0);
}

ساكن مزدوج trc_bt1361_inv(مزدوج E)
{
    ثابت مزدوج a = BT709_alpha;
    ثابت مزدوج b = 4.500 * BT709_beta;

    החזר (-0.02025 >= E) ? -pow((-4.0 * E - (a - 1.0)) / a, 1.0 / 0.45) / 4.0
         : ( b       >  E) ? E / 4.500
         :                    pow(( E + (a - 1.0)) / a, 1.0 / 0.45);
}

ساكن مزدوج trc_iec61966_2_1(مزدوج Lc)
{
    ثابت مزدوج a = 1.055;
    ثابت مزدوج b = 0.0031308;

    החזר (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 12.92 * Lc
         :              a * pow(Lc, 1.0  / 2.4) - (a - 1.0);
}

ساكن مزدوج trc_iec61966_2_1_inv(مزدوج E)
{
    ثابت مزدوج a = 1.055;
    ثابت مزدوج b = 12.92 * 0.0031308;

    החזר (0.0 > E) ? 0.0
         : (  b > E) ? E / 12.92
                     : pow((E + (a - 1.0)) / a, 2.4);
    החזר E;
}

#define PQ_c1 (        3424.0 / 4096.0) /* c3-c2 + 1 */
#define PQ_c2 ( 32.0 * 2413.0 / 4096.0)
#define PQ_c3 ( 32.0 * 2392.0 / 4096.0)
#define PQ_m  (128.0 * 2523.0 / 4096.0)
#define PQ_n  ( 0.25 * 2610.0 / 4096.0)

ساكن مزدوج trc_smpte_st2084(مزدوج Lc)
{
    ثابت مزدوج c1 = PQ_c1;
    ثابت مزدوج c2 = PQ_c2;
    ثابت مزدوج c3 = PQ_c3;
    ثابت مزدوج m  = PQ_m;
    ثابت مزدوج n  = PQ_n;
    ثابت مزدوج L  = Lc / 10000.0;
    ثابت مزدوج Ln = pow(L, n);

    החזר (0.0 > Lc) ? 0.0
         :              pow((c1 + c2 * Ln) / (1.0 + c3 * Ln), m);

}

ساكن مزدوج trc_smpte_st2084_inv(مزدوج E)
{
    ثابت مزدوج c1 = PQ_c1;
    ثابت مزدوج c2 = PQ_c2;
    ثابت مزدوج c3 = PQ_c3;
    ثابت مزدوج m  = PQ_m;
    ثابت مزدوج n  = PQ_n;
    ثابت مزدوج Em = pow(E, 1.0 / m);

    החזר (c1 > Em) ? 0.0
                     : 10000.0 * pow((Em - c1) / (c2 - c3 * Em), 1.0 / n);
}

#define DCI_L 48.00
#define DCI_P 52.37

ساكن مزدوج trc_smpte_st428_1(مزدوج Lc)
{
    החזר (0.0 > Lc) ? 0.0 : pow(DCI_L / DCI_P * Lc, 1.0 / 2.6);
}

ساكن مزدوج trc_smpte_st428_1_inv(مزدوج E)
{
    החזר (0.0 > E) ? 0.0 : DCI_P / DCI_L * pow(E, 2.6);
}

#define HLG_a 0.17883277
#define HLG_b 0.28466892
#define HLG_c 0.55991073

ساكن مزدوج trc_arib_std_b67(مزدوج Lc) {
    // The function uses the definition from HEVC, which assumes that the peak
    // white is input level = 1. (this is equivalent to scaling E = Lc * 12 and
    // using the definition from the ARIB STD-B67 spec)
    ثابت مزدوج a = HLG_a;
    ثابت مزدوج b = HLG_b;
    ثابت مزدوج c = HLG_c;
    החזר (0.0 > Lc) ? 0.0 :
        (Lc <= 1.0 / 12.0 ? sqrt(3.0 * Lc) : a * log(12.0 * Lc - b) + c);
}

ساكن مزدوج trc_arib_std_b67_inv(مزدوج E)
{
    ثابت مزدوج a = HLG_a;
    ثابت مزدوج b = HLG_b;
    ثابت مزدوج c = HLG_c;
    החזר (0.0 > E) ? 0.0 :
        (E <= 0.5 ? E * E / 3.0 : (exp((E - c) / a) + b) / 12.0);
}

#define VLOG_c1 0.01
#define VLOG_c2 0.181
#define VLOG_b  0.00873
#define VLOG_c  0.241514
#define VLOG_d  0.598206

ساكن مزدوج trc_v_log(مزدوج E)
{
    ثابت مزدوج c1 = VLOG_c1;
    ثابت مزدوج b = VLOG_b;
    ثابت مزدوج c = VLOG_c;
    ثابت مزدوج d = VLOG_d;
    החזר (E < c1) ? (5.6 * E + 0.125) :
        (c * log10(E + b) + d);
}

ساكن مزدوج trc_v_log_inv(مزدوج E)
{
    ثابت مزدوج c2 = VLOG_c2;
    ثابت مزدوج b = VLOG_b;
    ثابت مزدوج c = VLOG_c;
    ثابت مزدوج d = VLOG_d;
    החזר (E < c2) ? (E - 0.125) / 5.6 :
        (pow(10.0, ((E - d) / c)) - b);
}

ساكن ثابت av_csp_trc_function trc_funcs[AVCOL_TRC_NB] = {
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

ساكن ثابت av_csp_trc_function trc_funcs_ext[AVCOL_TRC_EXT_NB -
                                               AVCOL_TRC_EXT_BASE] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_BASE] = trc_v_log,
};

av_csp_trc_function av_csp_trc_func_from_id(تعداد AVColorTransferCharacteristic trc)
{
    אם ((unsigned)trc < AVCOL_TRC_NB)
        החזר trc_funcs[trc];
    אחרת אם (((unsigned)trc >= AVCOL_TRC_EXT_BASE) &&
             ((unsigned)trc < AVCOL_TRC_EXT_NB))
        החזר trc_funcs_ext[trc - AVCOL_TRC_EXT_BASE];
    החזר عدم;
}

ساكن ثابت av_csp_trc_function trc_inv_funcs[AVCOL_TRC_NB] = {
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

ساكن ثابت av_csp_trc_function trc_inv_funcs_ext[AVCOL_TRC_EXT_NB -
                                                   AVCOL_TRC_EXT_BASE] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_BASE] = trc_v_log_inv,
};

av_csp_trc_function av_csp_trc_func_inv_from_id(تعداد AVColorTransferCharacteristic trc)
{
    אם ((unsigned)trc < AVCOL_TRC_NB)
        החזר trc_inv_funcs[trc];
    אחרת אם (((unsigned)trc >= AVCOL_TRC_EXT_BASE) &&
             ((unsigned)trc < AVCOL_TRC_EXT_NB))
        החזר trc_inv_funcs_ext[trc - AVCOL_TRC_EXT_BASE];
    החזר عدم;
}

ساكن فراغ eotf_linear(ثابت مزدوج Lw, ثابت مزدوج Lb, مزدوج E[3])
{
    עבור (صحيح i = 0; i < 3; i++)
        E[i] = (Lw - Lb) * E[i] + Lb;
}

ساكن فراغ eotf_linear_inv(ثابت مزدوج Lw, ثابت مزدوج Lb, مزدوج L[3])
{
    עבור (صحيح i = 0; i < 3; i++)
        L[i] = (L[i] - Lb) / (Lw - Lb);
}

#define WRAP_SDR_OETF(name)                                         \
ساكن فراغ oetf_##name(مزدوج L[3])                                \
{                                                                   \
    עבור (صحيح i = 0; i < 3; i++)                                     \
        L[i] = trc_##name(L[i]);                                    \
}                                                                   \
                                                                    \
ساكن فراغ oetf_##name##_inv(مزدوج E[3])                          \
{                                                                   \
    עבור (صحيح i = 0; i < 3; i++)                                     \
        E[i] = trc_##name##_inv(E[i]);                              \
}

WRAP_SDR_OETF(gamma22)
WRAP_SDR_OETF(gamma28)
WRAP_SDR_OETF(iec61966_2_1)

#define WRAP_SDR_EOTF(name)                                         \
ساكن فراغ eotf_##name(مزدوج Lw, مزدوج Lb, مزدوج E[3])          \
{                                                                   \
    oetf_##name##_inv(E);                                           \
    eotf_linear(Lw, Lb, E);                                         \
}                                                                   \
                                                                    \
ساكن فراغ eotf_##name##_inv(مزدوج Lw, مزدوج Lb, مزدوج L[3])    \
{                                                                   \
    eotf_linear_inv(Lw, Lb, L);                                     \
    oetf_##name(L);                                                 \
}

WRAP_SDR_EOTF(gamma22)
WRAP_SDR_EOTF(gamma28)
WRAP_SDR_EOTF(iec61966_2_1)

ساكن فراغ eotf_bt1886(ثابت مزدوج Lw, ثابت مزدوج Lb, مزدوج E[3])
{
    ثابت مزدوج Lw_inv = pow(Lw, 1.0 / 2.4);
    ثابت مزدوج Lb_inv = pow(Lb, 1.0 / 2.4);
    ثابت مزدوج a = pow(Lw_inv - Lb_inv, 2.4);
    ثابت مزدوج b = Lb_inv / (Lw_inv - Lb_inv);

    עבור (صحيح i = 0; i < 3; i++)
        E[i] = (-b > E[i]) ? 0.0 : a * pow(E[i] + b, 2.4);
}

ساكن فراغ eotf_bt1886_inv(ثابت مزدوج Lw, ثابت مزدوج Lb, مزدوج L[3])
{
    ثابت مزدوج Lw_inv = pow(Lw, 1.0 / 2.4);
    ثابت مزدوج Lb_inv = pow(Lb, 1.0 / 2.4);
    ثابت مزدوج a = pow(Lw_inv - Lb_inv, 2.4);
    ثابت مزدوج b = Lb_inv / (Lw_inv - Lb_inv);

    עבור (صحيح i = 0; i < 3; i++)
        L[i] = (0.0 > L[i]) ? 0.0 : pow(L[i] / a, 1.0 / 2.4) - b;
}

ساكن فراغ eotf_smpte_st2084(ثابت مزدوج Lw, ثابت مزدوج Lb, مزدوج E[3])
{
    עבור (صحيح i = 0; i < 3; i++)
        E[i] = trc_smpte_st2084_inv(E[i]);
}

ساكن فراغ eotf_smpte_st2084_inv(ثابت مزدوج Lw, ثابت مزدوج Lb, مزدوج L[3])
{
    עבור (صحيح i = 0; i < 3; i++)
        L[i] = trc_smpte_st2084(L[i]);
}

/* This implementation assumes an SMPTE RP 431-2 reference projector (DCI) */
#define DCI_L 48.00
#define DCI_P 52.37
#define DCI_X (42.94 / DCI_L)
#define DCI_Z (45.82 / DCI_L)

ساكن فراغ eotf_smpte_st428_1(ثابت مزدوج Lw_Y, ثابت مزدوج Lb_Y, مزدوج E[3])
{
    ثابت مزدوج Lw[3] = { DCI_X * Lw_Y, Lw_Y, DCI_Z * Lw_Y };
    ثابت مزدوج Lb[3] = { DCI_X * Lb_Y, Lb_Y, DCI_Z * Lb_Y };

    עבור (صحيح i = 0; i < 3; i++) {
        E[i] = (0.0 > E[i]) ? 0.0 : pow(E[i], 2.6) * DCI_P / DCI_L;
        E[i] = E[i] * (Lw[i] - Lb[i]) + Lb[i];
    }
}

ساكن فراغ eotf_smpte_st428_1_inv(ثابت مزدوج Lw_Y, ثابت مزدوج Lb_Y, مزدوج L[3])
{
    ثابت مزدوج Lw[3] = { DCI_X * Lw_Y, Lw_Y, DCI_Z * Lw_Y };
    ثابت مزدوج Lb[3] = { DCI_X * Lb_Y, Lb_Y, DCI_Z * Lb_Y };

    עבור (صحيح i = 0; i < 3; i++) {
        L[i] = (L[i] - Lb[i]) / (Lw[i] - Lb[i]);
        L[i] = (0.0 > L[i]) ? 0.0 : pow(L[i] * DCI_L / DCI_P, 1.0 / 2.6);
    }
}

ساكن فراغ eotf_arib_std_b67(ثابت مزدوج Lw, ثابت مزدوج Lb, مزدوج E[3])
{
    ثابت مزدوج gamma = fmax(1.2 + 0.42 * log10(Lw / 1000.0), 1.0);

    /**
     * Note: This equation is technically only accurate if the contrast ratio
     * Lw:Lb is greater than 12:1; otherwise we would need to use a different,
     * significantly more complicated solution. Ignore this as a highly
     * degenerate case, since any real world reference display will have a
     * static contrast ratio multiple orders of magnitude higher.
     */
    ثابت مزدوج beta = sqrt(3 * pow(Lb / Lw, 1.0 / gamma));
    مزدوج luma;

    עבור (صحيح i = 0; i < 3; i++)
        E[i] = trc_arib_std_b67_inv((1 - beta) * E[i] + beta);

    luma = 0.2627 * E[0] + 0.6780 * E[1] + 0.0593 * E[2];
    luma = pow(fmax(luma, 0.0), gamma - 1.0);
    עבור (صحيح i = 0; i < 3; i++)
        E[i] *= Lw * luma;
}

ساكن فراغ eotf_arib_std_b67_inv(ثابت مزدوج Lw, ثابت مزدوج Lb, مزدوج L[3])
{
    ثابت مزدوج gamma = fmax(1.2 + 0.42 * log10(Lw / 1000.0), 1.0);
    ثابت مزدوج beta = sqrt(3 * pow(Lb / Lw, 1 / gamma));
    مزدوج luma = 0.2627 * L[0] + 0.6780 * L[1] + 0.0593 * L[2];

    אם (luma > 0.0) {
        luma = pow(luma / Lw, (1 - gamma) / gamma);
        עבור (صحيح i = 0; i < 3; i++)
            L[i] *= luma / Lw;
    } אחרת {
        L[0] = L[1] = L[2] = 0.0;
    }

    עבור (صحيح i = 0; i < 3; i++)
        L[i] = (trc_arib_std_b67(L[i]) - beta) / (1 - beta);
}

ساكن ثابت av_csp_eotf_function eotf_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = eotf_bt1886,
    [AVCOL_TRC_GAMMA22] = eotf_gamma22,
    [AVCOL_TRC_GAMMA28] = eotf_gamma28,
    [AVCOL_TRC_SMPTE170M] = eotf_bt1886,
    [AVCOL_TRC_SMPTE240M] = eotf_bt1886,
    [AVCOL_TRC_LINEAR] = eotf_linear,
    /* There is no EOTF associated with these logarithmic encodings, since they
     * are defined purely for transmission of scene referred data. */
    [AVCOL_TRC_LOG] = عدم,
    [AVCOL_TRC_LOG_SQRT] = عدم,
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

av_csp_eotf_function av_csp_itu_eotf(تعداد AVColorTransferCharacteristic trc)
{
    אם ((unsigned)trc >= AVCOL_TRC_NB)
        החזר عدم;
    החזר eotf_funcs[trc];
}

ساكن ثابت av_csp_eotf_function eotf_inv_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = eotf_bt1886_inv,
    [AVCOL_TRC_GAMMA22] = eotf_gamma22_inv,
    [AVCOL_TRC_GAMMA28] = eotf_gamma28_inv,
    [AVCOL_TRC_SMPTE170M] = eotf_bt1886_inv,
    [AVCOL_TRC_SMPTE240M] = eotf_bt1886_inv,
    [AVCOL_TRC_LINEAR] = eotf_linear_inv,
    [AVCOL_TRC_LOG] = عدم,
    [AVCOL_TRC_LOG_SQRT] = عدم,
    [AVCOL_TRC_IEC61966_2_4] = eotf_bt1886_inv,
    [AVCOL_TRC_BT1361_ECG] = eotf_bt1886_inv,
    [AVCOL_TRC_IEC61966_2_1] = eotf_iec61966_2_1_inv,
    [AVCOL_TRC_BT2020_10] = eotf_bt1886_inv,
    [AVCOL_TRC_BT2020_12] = eotf_bt1886_inv,
    [AVCOL_TRC_SMPTE2084] = eotf_smpte_st2084_inv,
    [AVCOL_TRC_SMPTE428] = eotf_smpte_st428_1_inv,
    [AVCOL_TRC_ARIB_STD_B67] = eotf_arib_std_b67_inv,
};

av_csp_eotf_function av_csp_itu_eotf_inv(تعداد AVColorTransferCharacteristic trc)
{
    אם ((unsigned)trc >= AVCOL_TRC_NB)
        החזר عدم;
    החזר eotf_inv_funcs[trc];
}
