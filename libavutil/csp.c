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

#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <math.h>

#అన్తర్భావ "attributes.h"
#అన్తర్భావ "csp.h"
#అన్తర్భావ "pixfmt.h"
#అన్తర్భావ "rational.h"

#నిర్వచించు AVR(d) { (పూర్ణాంకం)(d * 100000 + 0.5), 100000 }

/*
 * All constants explained in e.g. https://linuxtv.org/downloads/v4l-dvb-apis/ch02s06.html
 * The older ones (bt470bg/m) are also explained in their respective ITU docs
 * (e.g. https://www.itu.int/dms_pubrec/itu-r/rec/bt/R-REC-BT.470-5-199802-S!!PDF-E.pdf)
 * whereas the newer ones can typically be copied directly from wikipedia :)
 */
స్థిర స్థిరరాశి నిర్మాణం AVLumaCoefficients luma_coefficients[AVCOL_SPC_NB] = {
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

స్థిరరాశి నిర్మాణం AVLumaCoefficients *av_csp_luma_coeffs_from_avcsp(గణన AVColorSpace csp)
{
    స్థిరరాశి AVLumaCoefficients *coeffs;

    ఒకవేళ ((గుర్తులేని)csp >= AVCOL_SPC_NB)
        తిరిగి ఖాళీ;
    coeffs = &luma_coefficients[csp];
    ఒకవేళ (!coeffs->cr.అంకె)
        తిరిగి ఖాళీ;

    తిరిగి coeffs;
}

#నిర్వచించు WP_D65 { AVR(0.3127), AVR(0.3290) }
#నిర్వచించు WP_C   { AVR(0.3100), AVR(0.3160) }
#నిర్వచించు WP_DCI { AVR(0.3140), AVR(0.3510) }
#నిర్వచించు WP_E   { {1, 3}, {1, 3} }

స్థిర స్థిరరాశి AVColorPrimariesDesc color_primaries[AVCOL_PRI_NB] = {
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

స్థిర స్థిరరాశి AVColorPrimariesDesc color_primaries_ext[AVCOL_PRI_EXT_NB -
                                                      AVCOL_PRI_EXT_పునాది] = {
    [AVCOL_PRI_V_GAMUT - AVCOL_PRI_EXT_పునాది] = { WP_D65, { { AVR(0.730), AVR(0.280) }, { AVR(0.165), AVR(0.840) }, { AVR(0.100), AVR(-0.030) } } },
};

స్థిరరాశి AVColorPrimariesDesc *av_csp_primaries_desc_from_id(గణన AVColorPrimaries prm)
{
    స్థిరరాశి AVColorPrimariesDesc *p = ఖాళీ;
    ఒకవేళ ((గుర్తులేని)prm < AVCOL_PRI_NB)
        p = &color_primaries[prm];
    లేకపోతే ఒకవేళ (((గుర్తులేని)prm >= AVCOL_PRI_EXT_పునాది) &&
             ((గుర్తులేని)prm < AVCOL_PRI_EXT_NB))
        p = &color_primaries_ext[prm - AVCOL_PRI_EXT_పునాది];
    ఒకవేళ (!p || !p->prim.r.x.అంకె)
        తిరిగి ఖాళీ;
    తిరిగి p;
}

స్థిర av_always_inline AVRational abs_sub_q(AVRational r1, AVRational r2)
{
    AVRational diff = av_sub_q(r1, r2);
    /* denominator assumed to be positive */
    తిరిగి av_make_q(నిరపేక్ష(diff.అంకె), diff.den);
}

గణన AVColorPrimaries av_csp_primaries_id_from_desc(స్థిరరాశి AVColorPrimariesDesc *prm)
{
    AVRational delta;

    కొరకు (గణన AVColorPrimaries p = 0; p < AVCOL_PRI_NB; p++) {
        స్థిరరాశి AVColorPrimariesDesc *ref = &color_primaries[p];
        ఒకవేళ (!ref->prim.r.x.అంకె)
            కొనసాగు;

        delta = abs_sub_q(prm->prim.r.x, ref->prim.r.x);
        delta = av_కూడు_q(delta, abs_sub_q(prm->prim.r.y, ref->prim.r.y));
        delta = av_కూడు_q(delta, abs_sub_q(prm->prim.g.x, ref->prim.g.x));
        delta = av_కూడు_q(delta, abs_sub_q(prm->prim.g.y, ref->prim.g.y));
        delta = av_కూడు_q(delta, abs_sub_q(prm->prim.b.x, ref->prim.b.x));
        delta = av_కూడు_q(delta, abs_sub_q(prm->prim.b.y, ref->prim.b.y));
        delta = av_కూడు_q(delta, abs_sub_q(prm->wp.x, ref->wp.x));
        delta = av_కూడు_q(delta, abs_sub_q(prm->wp.y, ref->wp.y));

        ఒకవేళ (av_cmp_q(delta, av_make_q(1, 1000)) < 0)
            తిరిగి p;
    }

    తిరిగి AVCOL_PRI_UNSPECIFIED;
}

స్థిర స్థిరరాశి ద్విగుణ approximate_gamma[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = 1.961,
    [AVCOL_TRC_SMPTE170M] = 1.961,
    [AVCOL_TRC_SMPTE240M] = 1.961,
    [AVCOL_TRC_BT1361_ECG] = 1.961,
    [AVCOL_TRC_BT2020_10] = 1.961,
    [AVCOL_TRC_BT2020_12] = 1.961,
    [AVCOL_TRC_GAMMA22] = 2.2,
    [AVCOL_TRC_IEC61966_2_1] = 2.2,
    [AVCOL_TRC_GAMMA28] = 2.8,
    [AVCOL_TRC_రేఖీయ] = 1.0,
    [AVCOL_TRC_SMPTE428] = 2.6,
};

స్థిర స్థిరరాశి ద్విగుణ approximate_gamma_ext[AVCOL_TRC_EXT_NB -
                                          AVCOL_TRC_EXT_పునాది] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_పునాది] = 2.2,
};

ద్విగుణ av_csp_approximate_trc_gamma(గణన AVColorTransferCharacteristic trc)
{
    ఒకవేళ (trc < AVCOL_TRC_NB)
        తిరిగి approximate_gamma[trc];
    లేకపోతే ఒకవేళ ((trc >= AVCOL_TRC_EXT_పునాది) && (trc < AVCOL_TRC_EXT_NB))
        తిరిగి approximate_gamma_ext[trc - AVCOL_TRC_EXT_పునాది];
    తిరిగి 0.0;
}

స్థిర స్థిరరాశి ద్విగుణ approximate_eotf_gamma[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = 2.2,
    [AVCOL_TRC_SMPTE170M] = 2.2,
    [AVCOL_TRC_SMPTE240M] = 2.2,
    [AVCOL_TRC_BT1361_ECG] = 2.2,
    [AVCOL_TRC_BT2020_10] = 2.2,
    [AVCOL_TRC_BT2020_12] = 2.2,
    [AVCOL_TRC_GAMMA22] = 2.2,
    [AVCOL_TRC_IEC61966_2_1] = 2.2,
    [AVCOL_TRC_GAMMA28] = 2.8,
    [AVCOL_TRC_రేఖీయ] = 1.0,
    [AVCOL_TRC_SMPTE428] = 2.6,
};

స్థిర స్థిరరాశి ద్విగుణ approximate_eotf_gamma_ext[AVCOL_TRC_EXT_NB -
                                               AVCOL_TRC_EXT_పునాది] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_పునాది] = 2.2,
};

ద్విగుణ av_csp_approximate_eotf_gamma(గణన AVColorTransferCharacteristic trc)
{
    ఒకవేళ ((గుర్తులేని)trc < AVCOL_TRC_NB)
        తిరిగి approximate_eotf_gamma[trc];
    లేకపోతే ఒకవేళ (((గుర్తులేని)trc >= AVCOL_TRC_EXT_పునాది) &&
             ((గుర్తులేని)trc < AVCOL_TRC_EXT_NB))
        తిరిగి approximate_eotf_gamma_ext[trc - AVCOL_TRC_EXT_పునాది];
    తిరిగి 0.0;
}

#నిర్వచించు BT709_alpha 1.099296826809442
#నిర్వచించు BT709_beta 0.018053968510807

స్థిర ద్విగుణ trc_bt709(ద్విగుణ Lc)
{
    స్థిరరాశి ద్విగుణ a = BT709_alpha;
    స్థిరరాశి ద్విగుణ b = BT709_beta;

    తిరిగి (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 4.500 * Lc
         :              a * ఘాతం(Lc, 0.45) - (a - 1.0);
}

స్థిర ద్విగుణ trc_bt709_inv(ద్విగుణ E)
{
    స్థిరరాశి ద్విగుణ a = BT709_alpha;
    స్థిరరాశి ద్విగుణ b = 4.500 * BT709_beta;

    తిరిగి (0.0 > E) ? 0.0
         : (  b > E) ? E / 4.500
         :             ఘాతం((E + (a - 1.0)) / a, 1.0 / 0.45);
}

స్థిర ద్విగుణ trc_gamma22(ద్విగుణ Lc)
{
    తిరిగి (0.0 > Lc) ? 0.0 : ఘాతం(Lc, 1.0/ 2.2);
}

స్థిర ద్విగుణ trc_gamma22_inv(ద్విగుణ E)
{
    తిరిగి (0.0 > E) ? 0.0 : ఘాతం(E, 2.2);
}

స్థిర ద్విగుణ trc_gamma28(ద్విగుణ Lc)
{
    తిరిగి (0.0 > Lc) ? 0.0 : ఘాతం(Lc, 1.0/ 2.8);
}

స్థిర ద్విగుణ trc_gamma28_inv(ద్విగుణ E)
{
    తిరిగి (0.0 > E) ? 0.0 : ఘాతం(E, 2.8);
}

స్థిర ద్విగుణ trc_smpte240M(ద్విగుణ Lc)
{
    స్థిరరాశి ద్విగుణ a = 1.1115;
    స్థిరరాశి ద్విగుణ b = 0.0228;

    తిరిగి (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 4.000 * Lc
         :              a * ఘాతం(Lc, 0.45) - (a - 1.0);
}

స్థిర ద్విగుణ trc_smpte240M_inv(ద్విగుణ E)
{
    స్థిరరాశి ద్విగుణ a = 1.1115;
    స్థిరరాశి ద్విగుణ b = 4.000 * 0.0228;

    తిరిగి (0.0 > E) ? 0.0
         : (  b > E) ? E / 4.000
         :             ఘాతం((E + (a - 1.0)) / a, 1.0 / 0.45);
}

స్థిర ద్విగుణ trc_రేఖీయ(ద్విగుణ Lc)
{
    తిరిగి Lc;
}

స్థిర ద్విగుణ trc_log(ద్విగుణ Lc)
{
    తిరిగి (0.01 > Lc) ? 0.0 : 1.0 + log10(Lc) / 2.0;
}

స్థిర ద్విగుణ trc_log_inv(ద్విగుణ E)
{
    తిరిగి (0.0 > E) ? 0.01 : ఘాతం(10.0, 2.0 * (E - 1.0));
}

స్థిర ద్విగుణ trc_log_sqrt(ద్విగుణ Lc)
{
    // sqrt(10) / 1000
    తిరిగి (0.00316227766 > Lc) ? 0.0 : 1.0 + log10(Lc) / 2.5;
}

స్థిర ద్విగుణ trc_log_sqrt_inv(ద్విగుణ E)
{
    తిరిగి (0.0 > E) ? 0.00316227766 : ఘాతం(10.0, 2.5 * (E - 1.0));
}

స్థిర ద్విగుణ trc_iec61966_2_4(ద్విగుణ Lc)
{
    స్థిరరాశి ద్విగుణ a = BT709_alpha;
    స్థిరరాశి ద్విగుణ b = BT709_beta;

    తిరిగి (-b >= Lc) ? -a * ఘాతం(-Lc, 0.45) + (a - 1.0)
         : ( b >  Lc) ? 4.500 * Lc
         :               a * ఘాతం( Lc, 0.45) - (a - 1.0);
}

స్థిర ద్విగుణ trc_iec61966_2_4_inv(ద్విగుణ E)
{
    స్థిరరాశి ద్విగుణ a = BT709_alpha;
    స్థిరరాశి ద్విగుణ b = 4.500 * BT709_beta;

    తిరిగి (-b >= E) ? -ఘాతం((-E + (a - 1.0)) / a, 1.0 / 0.45)
         : ( b >  E) ? E / 4.500
         :              ఘాతం(( E + (a - 1.0)) / a, 1.0 / 0.45);
}

స్థిర ద్విగుణ trc_bt1361(ద్విగుణ Lc)
{
    స్థిరరాశి ద్విగుణ a = BT709_alpha;
    స్థిరరాశి ద్విగుణ b = BT709_beta;

    తిరిగి (-0.0045 >= Lc) ? -(a * ఘాతం(-4.0 * Lc, 0.45) + (a - 1.0)) / 4.0
         : ( b >  Lc) ? 4.500 * Lc
         :               a * ఘాతం( Lc, 0.45) - (a - 1.0);
}

స్థిర ద్విగుణ trc_bt1361_inv(ద్విగుణ E)
{
    స్థిరరాశి ద్విగుణ a = BT709_alpha;
    స్థిరరాశి ద్విగుణ b = 4.500 * BT709_beta;

    తిరిగి (-0.02025 >= E) ? -ఘాతం((-4.0 * E - (a - 1.0)) / a, 1.0 / 0.45) / 4.0
         : ( b       >  E) ? E / 4.500
         :                    ఘాతం(( E + (a - 1.0)) / a, 1.0 / 0.45);
}

స్థిర ద్విగుణ trc_iec61966_2_1(ద్విగుణ Lc)
{
    స్థిరరాశి ద్విగుణ a = 1.055;
    స్థిరరాశి ద్విగుణ b = 0.0031308;

    తిరిగి (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 12.92 * Lc
         :              a * ఘాతం(Lc, 1.0  / 2.4) - (a - 1.0);
}

స్థిర ద్విగుణ trc_iec61966_2_1_inv(ద్విగుణ E)
{
    స్థిరరాశి ద్విగుణ a = 1.055;
    స్థిరరాశి ద్విగుణ b = 12.92 * 0.0031308;

    తిరిగి (0.0 > E) ? 0.0
         : (  b > E) ? E / 12.92
                     : ఘాతం((E + (a - 1.0)) / a, 2.4);
    తిరిగి E;
}

#నిర్వచించు PQ_c1 (        3424.0 / 4096.0) /* c3-c2 + 1 */
#నిర్వచించు PQ_c2 ( 32.0 * 2413.0 / 4096.0)
#నిర్వచించు PQ_c3 ( 32.0 * 2392.0 / 4096.0)
#నిర్వచించు PQ_m  (128.0 * 2523.0 / 4096.0)
#నిర్వచించు PQ_n  ( 0.25 * 2610.0 / 4096.0)

స్థిర ద్విగుణ trc_smpte_st2084(ద్విగుణ Lc)
{
    స్థిరరాశి ద్విగుణ c1 = PQ_c1;
    స్థిరరాశి ద్విగుణ c2 = PQ_c2;
    స్థిరరాశి ద్విగుణ c3 = PQ_c3;
    స్థిరరాశి ద్విగుణ m  = PQ_m;
    స్థిరరాశి ద్విగుణ n  = PQ_n;
    స్థిరరాశి ద్విగుణ L  = Lc / 10000.0;
    స్థిరరాశి ద్విగుణ Ln = ఘాతం(L, n);

    తిరిగి (0.0 > Lc) ? 0.0
         :              ఘాతం((c1 + c2 * Ln) / (1.0 + c3 * Ln), m);

}

స్థిర ద్విగుణ trc_smpte_st2084_inv(ద్విగుణ E)
{
    స్థిరరాశి ద్విగుణ c1 = PQ_c1;
    స్థిరరాశి ద్విగుణ c2 = PQ_c2;
    స్థిరరాశి ద్విగుణ c3 = PQ_c3;
    స్థిరరాశి ద్విగుణ m  = PQ_m;
    స్థిరరాశి ద్విగుణ n  = PQ_n;
    స్థిరరాశి ద్విగుణ Em = ఘాతం(E, 1.0 / m);

    తిరిగి (c1 > Em) ? 0.0
                     : 10000.0 * ఘాతం((Em - c1) / (c2 - c3 * Em), 1.0 / n);
}

#నిర్వచించు DCI_L 48.00
#నిర్వచించు DCI_P 52.37

స్థిర ద్విగుణ trc_smpte_st428_1(ద్విగుణ Lc)
{
    తిరిగి (0.0 > Lc) ? 0.0 : ఘాతం(DCI_L / DCI_P * Lc, 1.0 / 2.6);
}

స్థిర ద్విగుణ trc_smpte_st428_1_inv(ద్విగుణ E)
{
    తిరిగి (0.0 > E) ? 0.0 : DCI_P / DCI_L * ఘాతం(E, 2.6);
}

#నిర్వచించు HLG_a 0.17883277
#నిర్వచించు HLG_b 0.28466892
#నిర్వచించు HLG_c 0.55991073

స్థిర ద్విగుణ trc_arib_std_b67(ద్విగుణ Lc) {
    // The function uses the definition from HEVC, which assumes that the peak
    // white is input level = 1. (this is equivalent to scaling E = Lc * 12 and
    // using the definition from the ARIB STD-B67 spec)
    స్థిరరాశి ద్విగుణ a = HLG_a;
    స్థిరరాశి ద్విగుణ b = HLG_b;
    స్థిరరాశి ద్విగుణ c = HLG_c;
    తిరిగి (0.0 > Lc) ? 0.0 :
        (Lc <= 1.0 / 12.0 ? వర్గమూలం(3.0 * Lc) : a * సంవర్గమానం(12.0 * Lc - b) + c);
}

స్థిర ద్విగుణ trc_arib_std_b67_inv(ద్విగుణ E)
{
    స్థిరరాశి ద్విగుణ a = HLG_a;
    స్థిరరాశి ద్విగుణ b = HLG_b;
    స్థిరరాశి ద్విగుణ c = HLG_c;
    తిరిగి (0.0 > E) ? 0.0 :
        (E <= 0.5 ? E * E / 3.0 : (ఘాతాంకం((E - c) / a) + b) / 12.0);
}

#నిర్వచించు VLOG_c1 0.01
#నిర్వచించు VLOG_c2 0.181
#నిర్వచించు VLOG_b  0.00873
#నిర్వచించు VLOG_c  0.241514
#నిర్వచించు VLOG_d  0.598206

స్థిర ద్విగుణ trc_v_log(ద్విగుణ E)
{
    స్థిరరాశి ద్విగుణ c1 = VLOG_c1;
    స్థిరరాశి ద్విగుణ b = VLOG_b;
    స్థిరరాశి ద్విగుణ c = VLOG_c;
    స్థిరరాశి ద్విగుణ d = VLOG_d;
    తిరిగి (E < c1) ? (5.6 * E + 0.125) :
        (c * log10(E + b) + d);
}

స్థిర ద్విగుణ trc_v_log_inv(ద్విగుణ E)
{
    స్థిరరాశి ద్విగుణ c2 = VLOG_c2;
    స్థిరరాశి ద్విగుణ b = VLOG_b;
    స్థిరరాశి ద్విగుణ c = VLOG_c;
    స్థిరరాశి ద్విగుణ d = VLOG_d;
    తిరిగి (E < c2) ? (E - 0.125) / 5.6 :
        (ఘాతం(10.0, ((E - d) / c)) - b);
}

స్థిర స్థిరరాశి av_csp_trc_function trc_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = trc_bt709,
    [AVCOL_TRC_GAMMA22] = trc_gamma22,
    [AVCOL_TRC_GAMMA28] = trc_gamma28,
    [AVCOL_TRC_SMPTE170M] = trc_bt709,
    [AVCOL_TRC_SMPTE240M] = trc_smpte240M,
    [AVCOL_TRC_రేఖీయ] = trc_రేఖీయ,
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

స్థిర స్థిరరాశి av_csp_trc_function trc_funcs_ext[AVCOL_TRC_EXT_NB -
                                               AVCOL_TRC_EXT_పునాది] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_పునాది] = trc_v_log,
};

av_csp_trc_function av_csp_trc_func_from_id(గణన AVColorTransferCharacteristic trc)
{
    ఒకవేళ ((గుర్తులేని)trc < AVCOL_TRC_NB)
        తిరిగి trc_funcs[trc];
    లేకపోతే ఒకవేళ (((గుర్తులేని)trc >= AVCOL_TRC_EXT_పునాది) &&
             ((గుర్తులేని)trc < AVCOL_TRC_EXT_NB))
        తిరిగి trc_funcs_ext[trc - AVCOL_TRC_EXT_పునాది];
    తిరిగి ఖాళీ;
}

స్థిర స్థిరరాశి av_csp_trc_function trc_inv_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = trc_bt709_inv,
    [AVCOL_TRC_GAMMA22] = trc_gamma22_inv,
    [AVCOL_TRC_GAMMA28] = trc_gamma28_inv,
    [AVCOL_TRC_SMPTE170M] = trc_bt709_inv,
    [AVCOL_TRC_SMPTE240M] = trc_smpte240M_inv,
    [AVCOL_TRC_రేఖీయ] = trc_రేఖీయ,
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

స్థిర స్థిరరాశి av_csp_trc_function trc_inv_funcs_ext[AVCOL_TRC_EXT_NB -
                                                   AVCOL_TRC_EXT_పునాది] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_పునాది] = trc_v_log_inv,
};

av_csp_trc_function av_csp_trc_func_inv_from_id(గణన AVColorTransferCharacteristic trc)
{
    ఒకవేళ ((గుర్తులేని)trc < AVCOL_TRC_NB)
        తిరిగి trc_inv_funcs[trc];
    లేకపోతే ఒకవేళ (((గుర్తులేని)trc >= AVCOL_TRC_EXT_పునాది) &&
             ((గుర్తులేని)trc < AVCOL_TRC_EXT_NB))
        తిరిగి trc_inv_funcs_ext[trc - AVCOL_TRC_EXT_పునాది];
    తిరిగి ఖాళీ;
}

స్థిర శూన్య eotf_రేఖీయ(స్థిరరాశి ద్విగుణ Lw, స్థిరరాశి ద్విగుణ Lb, ద్విగుణ E[3])
{
    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
        E[i] = (Lw - Lb) * E[i] + Lb;
}

స్థిర శూన్య eotf_రేఖీయ_inv(స్థిరరాశి ద్విగుణ Lw, స్థిరరాశి ద్విగుణ Lb, ద్విగుణ L[3])
{
    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
        L[i] = (L[i] - Lb) / (Lw - Lb);
}

#నిర్వచించు WRAP_SDR_OETF(name)                                         \
స్థిర శూన్య oetf_##name(ద్విగుణ L[3])                                \
{                                                                   \
    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)                                     \
        L[i] = trc_##name(L[i]);                                    \
}                                                                   \
                                                                    \
స్థిర శూన్య oetf_##name##_inv(ద్విగుణ E[3])                          \
{                                                                   \
    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)                                     \
        E[i] = trc_##name##_inv(E[i]);                              \
}

WRAP_SDR_OETF(gamma22)
WRAP_SDR_OETF(gamma28)
WRAP_SDR_OETF(iec61966_2_1)

#నిర్వచించు WRAP_SDR_EOTF(name)                                         \
స్థిర శూన్య eotf_##name(ద్విగుణ Lw, ద్విగుణ Lb, ద్విగుణ E[3])          \
{                                                                   \
    oetf_##name##_inv(E);                                           \
    eotf_రేఖీయ(Lw, Lb, E);                                         \
}                                                                   \
                                                                    \
స్థిర శూన్య eotf_##name##_inv(ద్విగుణ Lw, ద్విగుణ Lb, ద్విగుణ L[3])    \
{                                                                   \
    eotf_రేఖీయ_inv(Lw, Lb, L);                                     \
    oetf_##name(L);                                                 \
}

WRAP_SDR_EOTF(gamma22)
WRAP_SDR_EOTF(gamma28)
WRAP_SDR_EOTF(iec61966_2_1)

స్థిర శూన్య eotf_bt1886(స్థిరరాశి ద్విగుణ Lw, స్థిరరాశి ద్విగుణ Lb, ద్విగుణ E[3])
{
    స్థిరరాశి ద్విగుణ Lw_inv = ఘాతం(Lw, 1.0 / 2.4);
    స్థిరరాశి ద్విగుణ Lb_inv = ఘాతం(Lb, 1.0 / 2.4);
    స్థిరరాశి ద్విగుణ a = ఘాతం(Lw_inv - Lb_inv, 2.4);
    స్థిరరాశి ద్విగుణ b = Lb_inv / (Lw_inv - Lb_inv);

    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
        E[i] = (-b > E[i]) ? 0.0 : a * ఘాతం(E[i] + b, 2.4);
}

స్థిర శూన్య eotf_bt1886_inv(స్థిరరాశి ద్విగుణ Lw, స్థిరరాశి ద్విగుణ Lb, ద్విగుణ L[3])
{
    స్థిరరాశి ద్విగుణ Lw_inv = ఘాతం(Lw, 1.0 / 2.4);
    స్థిరరాశి ద్విగుణ Lb_inv = ఘాతం(Lb, 1.0 / 2.4);
    స్థిరరాశి ద్విగుణ a = ఘాతం(Lw_inv - Lb_inv, 2.4);
    స్థిరరాశి ద్విగుణ b = Lb_inv / (Lw_inv - Lb_inv);

    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
        L[i] = (0.0 > L[i]) ? 0.0 : ఘాతం(L[i] / a, 1.0 / 2.4) - b;
}

స్థిర శూన్య eotf_smpte_st2084(స్థిరరాశి ద్విగుణ Lw, స్థిరరాశి ద్విగుణ Lb, ద్విగుణ E[3])
{
    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
        E[i] = trc_smpte_st2084_inv(E[i]);
}

స్థిర శూన్య eotf_smpte_st2084_inv(స్థిరరాశి ద్విగుణ Lw, స్థిరరాశి ద్విగుణ Lb, ద్విగుణ L[3])
{
    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
        L[i] = trc_smpte_st2084(L[i]);
}

/* This implementation assumes an SMPTE RP 431-2 reference projector (DCI) */
#నిర్వచించు DCI_L 48.00
#నిర్వచించు DCI_P 52.37
#నిర్వచించు DCI_X (42.94 / DCI_L)
#నిర్వచించు DCI_Z (45.82 / DCI_L)

స్థిర శూన్య eotf_smpte_st428_1(స్థిరరాశి ద్విగుణ Lw_Y, స్థిరరాశి ద్విగుణ Lb_Y, ద్విగుణ E[3])
{
    స్థిరరాశి ద్విగుణ Lw[3] = { DCI_X * Lw_Y, Lw_Y, DCI_Z * Lw_Y };
    స్థిరరాశి ద్విగుణ Lb[3] = { DCI_X * Lb_Y, Lb_Y, DCI_Z * Lb_Y };

    కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
        E[i] = (0.0 > E[i]) ? 0.0 : ఘాతం(E[i], 2.6) * DCI_P / DCI_L;
        E[i] = E[i] * (Lw[i] - Lb[i]) + Lb[i];
    }
}

స్థిర శూన్య eotf_smpte_st428_1_inv(స్థిరరాశి ద్విగుణ Lw_Y, స్థిరరాశి ద్విగుణ Lb_Y, ద్విగుణ L[3])
{
    స్థిరరాశి ద్విగుణ Lw[3] = { DCI_X * Lw_Y, Lw_Y, DCI_Z * Lw_Y };
    స్థిరరాశి ద్విగుణ Lb[3] = { DCI_X * Lb_Y, Lb_Y, DCI_Z * Lb_Y };

    కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
        L[i] = (L[i] - Lb[i]) / (Lw[i] - Lb[i]);
        L[i] = (0.0 > L[i]) ? 0.0 : ఘాతం(L[i] * DCI_L / DCI_P, 1.0 / 2.6);
    }
}

స్థిర శూన్య eotf_arib_std_b67(స్థిరరాశి ద్విగుణ Lw, స్థిరరాశి ద్విగుణ Lb, ద్విగుణ E[3])
{
    స్థిరరాశి ద్విగుణ gamma = fmax(1.2 + 0.42 * log10(Lw / 1000.0), 1.0);

    /**
     * Note: This equation is technically only accurate if the contrast ratio
     * Lw:Lb is greater than 12:1; otherwise we would need to use a different,
     * significantly more complicated solution. Ignore this as a highly
     * degenerate case, since any real world reference display will have a
     * static contrast ratio multiple orders of magnitude higher.
     */
    స్థిరరాశి ద్విగుణ beta = వర్గమూలం(3 * ఘాతం(Lb / Lw, 1.0 / gamma));
    ద్విగుణ luma;

    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
        E[i] = trc_arib_std_b67_inv((1 - beta) * E[i] + beta);

    luma = 0.2627 * E[0] + 0.6780 * E[1] + 0.0593 * E[2];
    luma = ఘాతం(fmax(luma, 0.0), gamma - 1.0);
    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
        E[i] *= Lw * luma;
}

స్థిర శూన్య eotf_arib_std_b67_inv(స్థిరరాశి ద్విగుణ Lw, స్థిరరాశి ద్విగుణ Lb, ద్విగుణ L[3])
{
    స్థిరరాశి ద్విగుణ gamma = fmax(1.2 + 0.42 * log10(Lw / 1000.0), 1.0);
    స్థిరరాశి ద్విగుణ beta = వర్గమూలం(3 * ఘాతం(Lb / Lw, 1 / gamma));
    ద్విగుణ luma = 0.2627 * L[0] + 0.6780 * L[1] + 0.0593 * L[2];

    ఒకవేళ (luma > 0.0) {
        luma = ఘాతం(luma / Lw, (1 - gamma) / gamma);
        కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
            L[i] *= luma / Lw;
    } లేకపోతే {
        L[0] = L[1] = L[2] = 0.0;
    }

    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
        L[i] = (trc_arib_std_b67(L[i]) - beta) / (1 - beta);
}

స్థిర స్థిరరాశి av_csp_eotf_function eotf_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = eotf_bt1886,
    [AVCOL_TRC_GAMMA22] = eotf_gamma22,
    [AVCOL_TRC_GAMMA28] = eotf_gamma28,
    [AVCOL_TRC_SMPTE170M] = eotf_bt1886,
    [AVCOL_TRC_SMPTE240M] = eotf_bt1886,
    [AVCOL_TRC_రేఖీయ] = eotf_రేఖీయ,
    /* There is no EOTF associated with these logarithmic encodings, since they
     * are defined purely for transmission of scene referred data. */
    [AVCOL_TRC_LOG] = ఖాళీ,
    [AVCOL_TRC_LOG_SQRT] = ఖాళీ,
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

av_csp_eotf_function av_csp_itu_eotf(గణన AVColorTransferCharacteristic trc)
{
    ఒకవేళ ((గుర్తులేని)trc >= AVCOL_TRC_NB)
        తిరిగి ఖాళీ;
    తిరిగి eotf_funcs[trc];
}

స్థిర స్థిరరాశి av_csp_eotf_function eotf_inv_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = eotf_bt1886_inv,
    [AVCOL_TRC_GAMMA22] = eotf_gamma22_inv,
    [AVCOL_TRC_GAMMA28] = eotf_gamma28_inv,
    [AVCOL_TRC_SMPTE170M] = eotf_bt1886_inv,
    [AVCOL_TRC_SMPTE240M] = eotf_bt1886_inv,
    [AVCOL_TRC_రేఖీయ] = eotf_రేఖీయ_inv,
    [AVCOL_TRC_LOG] = ఖాళీ,
    [AVCOL_TRC_LOG_SQRT] = ఖాళీ,
    [AVCOL_TRC_IEC61966_2_4] = eotf_bt1886_inv,
    [AVCOL_TRC_BT1361_ECG] = eotf_bt1886_inv,
    [AVCOL_TRC_IEC61966_2_1] = eotf_iec61966_2_1_inv,
    [AVCOL_TRC_BT2020_10] = eotf_bt1886_inv,
    [AVCOL_TRC_BT2020_12] = eotf_bt1886_inv,
    [AVCOL_TRC_SMPTE2084] = eotf_smpte_st2084_inv,
    [AVCOL_TRC_SMPTE428] = eotf_smpte_st428_1_inv,
    [AVCOL_TRC_ARIB_STD_B67] = eotf_arib_std_b67_inv,
};

av_csp_eotf_function av_csp_itu_eotf_inv(గణన AVColorTransferCharacteristic trc)
{
    ఒకవేళ ((గుర్తులేని)trc >= AVCOL_TRC_NB)
        తిరిగి ఖాళీ;
    తిరిగి eotf_inv_funcs[trc];
}
