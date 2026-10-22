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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "csp.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "rational.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVR(d) { (ਪੂਰਨ)(d * 100000 + 0.5), 100000 }

/*
 * All constants explained in e.g. https://linuxtv.org/downloads/v4l-dvb-apis/ch02s06.html
 * The older ones (bt470bg/m) are also explained in their respective ITU docs
 * (e.g. https://www.itu.int/dms_pubrec/itu-r/rec/bt/R-REC-BT.470-5-199802-S!!PDF-E.pdf)
 * whereas the newer ones can typically be copied directly from wikipedia :)
 */
ਸਥਿਰ ਅਚਲ ਬਣਤਰ AVLumaCoefficients luma_coefficients[AVCOL_SPC_NB] = {
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

ਅਚਲ ਬਣਤਰ AVLumaCoefficients *av_csp_luma_coeffs_from_avcsp(ਗਿਣਤੀ AVColorSpace csp)
{
    ਅਚਲ AVLumaCoefficients *coeffs;

    ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)csp >= AVCOL_SPC_NB)
        ਵਾਪਸ ਨਿਰਾ;
    coeffs = &luma_coefficients[csp];
    ਜੇ (!coeffs->cr.ਅੰਕ)
        ਵਾਪਸ ਨਿਰਾ;

    ਵਾਪਸ coeffs;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WP_D65 { AVR(0.3127), AVR(0.3290) }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WP_C   { AVR(0.3100), AVR(0.3160) }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WP_DCI { AVR(0.3140), AVR(0.3510) }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WP_E   { {1, 3}, {1, 3} }

ਸਥਿਰ ਅਚਲ AVColorPrimariesDesc color_primaries[AVCOL_PRI_NB] = {
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

ਸਥਿਰ ਅਚਲ AVColorPrimariesDesc color_primaries_ext[AVCOL_PRI_EXT_NB -
                                                      AVCOL_PRI_EXT_ਅਧਾਰ] = {
    [AVCOL_PRI_V_GAMUT - AVCOL_PRI_EXT_ਅਧਾਰ] = { WP_D65, { { AVR(0.730), AVR(0.280) }, { AVR(0.165), AVR(0.840) }, { AVR(0.100), AVR(-0.030) } } },
};

ਅਚਲ AVColorPrimariesDesc *av_csp_primaries_desc_from_id(ਗਿਣਤੀ AVColorPrimaries prm)
{
    ਅਚਲ AVColorPrimariesDesc *p = ਨਿਰਾ;
    ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)prm < AVCOL_PRI_NB)
        p = &color_primaries[prm];
    ਨਹੀਂਤਾਂ ਜੇ (((ਬਿਨਾਨਿਸ਼ਾਨੀ)prm >= AVCOL_PRI_EXT_ਅਧਾਰ) &&
             ((ਬਿਨਾਨਿਸ਼ਾਨੀ)prm < AVCOL_PRI_EXT_NB))
        p = &color_primaries_ext[prm - AVCOL_PRI_EXT_ਅਧਾਰ];
    ਜੇ (!p || !p->prim.r.x.ਅੰਕ)
        ਵਾਪਸ ਨਿਰਾ;
    ਵਾਪਸ p;
}

ਸਥਿਰ av_always_inline AVRational abs_sub_q(AVRational r1, AVRational r2)
{
    AVRational diff = av_sub_q(r1, r2);
    /* denominator assumed to be positive */
    ਵਾਪਸ av_make_q(ਨਿਰਪੇਖ(diff.ਅੰਕ), diff.den);
}

ਗਿਣਤੀ AVColorPrimaries av_csp_primaries_id_from_desc(ਅਚਲ AVColorPrimariesDesc *prm)
{
    AVRational delta;

    ਲਈ (ਗਿਣਤੀ AVColorPrimaries p = 0; p < AVCOL_PRI_NB; p++) {
        ਅਚਲ AVColorPrimariesDesc *ref = &color_primaries[p];
        ਜੇ (!ref->prim.r.x.ਅੰਕ)
            ਜਾਰੀ;

        delta = abs_sub_q(prm->prim.r.x, ref->prim.r.x);
        delta = av_ਜੋੜੋ_q(delta, abs_sub_q(prm->prim.r.y, ref->prim.r.y));
        delta = av_ਜੋੜੋ_q(delta, abs_sub_q(prm->prim.g.x, ref->prim.g.x));
        delta = av_ਜੋੜੋ_q(delta, abs_sub_q(prm->prim.g.y, ref->prim.g.y));
        delta = av_ਜੋੜੋ_q(delta, abs_sub_q(prm->prim.b.x, ref->prim.b.x));
        delta = av_ਜੋੜੋ_q(delta, abs_sub_q(prm->prim.b.y, ref->prim.b.y));
        delta = av_ਜੋੜੋ_q(delta, abs_sub_q(prm->wp.x, ref->wp.x));
        delta = av_ਜੋੜੋ_q(delta, abs_sub_q(prm->wp.y, ref->wp.y));

        ਜੇ (av_cmp_q(delta, av_make_q(1, 1000)) < 0)
            ਵਾਪਸ p;
    }

    ਵਾਪਸ AVCOL_PRI_UNSPECIFIED;
}

ਸਥਿਰ ਅਚਲ ਦੁੱਗਣਾ approximate_gamma[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = 1.961,
    [AVCOL_TRC_SMPTE170M] = 1.961,
    [AVCOL_TRC_SMPTE240M] = 1.961,
    [AVCOL_TRC_BT1361_ECG] = 1.961,
    [AVCOL_TRC_BT2020_10] = 1.961,
    [AVCOL_TRC_BT2020_12] = 1.961,
    [AVCOL_TRC_GAMMA22] = 2.2,
    [AVCOL_TRC_IEC61966_2_1] = 2.2,
    [AVCOL_TRC_GAMMA28] = 2.8,
    [AVCOL_TRC_ਰੇਖਿਕ] = 1.0,
    [AVCOL_TRC_SMPTE428] = 2.6,
};

ਸਥਿਰ ਅਚਲ ਦੁੱਗਣਾ approximate_gamma_ext[AVCOL_TRC_EXT_NB -
                                          AVCOL_TRC_EXT_ਅਧਾਰ] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_ਅਧਾਰ] = 2.2,
};

ਦੁੱਗਣਾ av_csp_approximate_trc_gamma(ਗਿਣਤੀ AVColorTransferCharacteristic trc)
{
    ਜੇ (trc < AVCOL_TRC_NB)
        ਵਾਪਸ approximate_gamma[trc];
    ਨਹੀਂਤਾਂ ਜੇ ((trc >= AVCOL_TRC_EXT_ਅਧਾਰ) && (trc < AVCOL_TRC_EXT_NB))
        ਵਾਪਸ approximate_gamma_ext[trc - AVCOL_TRC_EXT_ਅਧਾਰ];
    ਵਾਪਸ 0.0;
}

ਸਥਿਰ ਅਚਲ ਦੁੱਗਣਾ approximate_eotf_gamma[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = 2.2,
    [AVCOL_TRC_SMPTE170M] = 2.2,
    [AVCOL_TRC_SMPTE240M] = 2.2,
    [AVCOL_TRC_BT1361_ECG] = 2.2,
    [AVCOL_TRC_BT2020_10] = 2.2,
    [AVCOL_TRC_BT2020_12] = 2.2,
    [AVCOL_TRC_GAMMA22] = 2.2,
    [AVCOL_TRC_IEC61966_2_1] = 2.2,
    [AVCOL_TRC_GAMMA28] = 2.8,
    [AVCOL_TRC_ਰੇਖਿਕ] = 1.0,
    [AVCOL_TRC_SMPTE428] = 2.6,
};

ਸਥਿਰ ਅਚਲ ਦੁੱਗਣਾ approximate_eotf_gamma_ext[AVCOL_TRC_EXT_NB -
                                               AVCOL_TRC_EXT_ਅਧਾਰ] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_ਅਧਾਰ] = 2.2,
};

ਦੁੱਗਣਾ av_csp_approximate_eotf_gamma(ਗਿਣਤੀ AVColorTransferCharacteristic trc)
{
    ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)trc < AVCOL_TRC_NB)
        ਵਾਪਸ approximate_eotf_gamma[trc];
    ਨਹੀਂਤਾਂ ਜੇ (((ਬਿਨਾਨਿਸ਼ਾਨੀ)trc >= AVCOL_TRC_EXT_ਅਧਾਰ) &&
             ((ਬਿਨਾਨਿਸ਼ਾਨੀ)trc < AVCOL_TRC_EXT_NB))
        ਵਾਪਸ approximate_eotf_gamma_ext[trc - AVCOL_TRC_EXT_ਅਧਾਰ];
    ਵਾਪਸ 0.0;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BT709_alpha 1.099296826809442
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BT709_beta 0.018053968510807

ਸਥਿਰ ਦੁੱਗਣਾ trc_bt709(ਦੁੱਗਣਾ Lc)
{
    ਅਚਲ ਦੁੱਗਣਾ a = BT709_alpha;
    ਅਚਲ ਦੁੱਗਣਾ b = BT709_beta;

    ਵਾਪਸ (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 4.500 * Lc
         :              a * ਘਾਤ(Lc, 0.45) - (a - 1.0);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_bt709_inv(ਦੁੱਗਣਾ E)
{
    ਅਚਲ ਦੁੱਗਣਾ a = BT709_alpha;
    ਅਚਲ ਦੁੱਗਣਾ b = 4.500 * BT709_beta;

    ਵਾਪਸ (0.0 > E) ? 0.0
         : (  b > E) ? E / 4.500
         :             ਘਾਤ((E + (a - 1.0)) / a, 1.0 / 0.45);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_gamma22(ਦੁੱਗਣਾ Lc)
{
    ਵਾਪਸ (0.0 > Lc) ? 0.0 : ਘਾਤ(Lc, 1.0/ 2.2);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_gamma22_inv(ਦੁੱਗਣਾ E)
{
    ਵਾਪਸ (0.0 > E) ? 0.0 : ਘਾਤ(E, 2.2);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_gamma28(ਦੁੱਗਣਾ Lc)
{
    ਵਾਪਸ (0.0 > Lc) ? 0.0 : ਘਾਤ(Lc, 1.0/ 2.8);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_gamma28_inv(ਦੁੱਗਣਾ E)
{
    ਵਾਪਸ (0.0 > E) ? 0.0 : ਘਾਤ(E, 2.8);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_smpte240M(ਦੁੱਗਣਾ Lc)
{
    ਅਚਲ ਦੁੱਗਣਾ a = 1.1115;
    ਅਚਲ ਦੁੱਗਣਾ b = 0.0228;

    ਵਾਪਸ (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 4.000 * Lc
         :              a * ਘਾਤ(Lc, 0.45) - (a - 1.0);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_smpte240M_inv(ਦੁੱਗਣਾ E)
{
    ਅਚਲ ਦੁੱਗਣਾ a = 1.1115;
    ਅਚਲ ਦੁੱਗਣਾ b = 4.000 * 0.0228;

    ਵਾਪਸ (0.0 > E) ? 0.0
         : (  b > E) ? E / 4.000
         :             ਘਾਤ((E + (a - 1.0)) / a, 1.0 / 0.45);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_ਰੇਖਿਕ(ਦੁੱਗਣਾ Lc)
{
    ਵਾਪਸ Lc;
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_log(ਦੁੱਗਣਾ Lc)
{
    ਵਾਪਸ (0.01 > Lc) ? 0.0 : 1.0 + log10(Lc) / 2.0;
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_log_inv(ਦੁੱਗਣਾ E)
{
    ਵਾਪਸ (0.0 > E) ? 0.01 : ਘਾਤ(10.0, 2.0 * (E - 1.0));
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_log_sqrt(ਦੁੱਗਣਾ Lc)
{
    // sqrt(10) / 1000
    ਵਾਪਸ (0.00316227766 > Lc) ? 0.0 : 1.0 + log10(Lc) / 2.5;
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_log_sqrt_inv(ਦੁੱਗਣਾ E)
{
    ਵਾਪਸ (0.0 > E) ? 0.00316227766 : ਘਾਤ(10.0, 2.5 * (E - 1.0));
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_iec61966_2_4(ਦੁੱਗਣਾ Lc)
{
    ਅਚਲ ਦੁੱਗਣਾ a = BT709_alpha;
    ਅਚਲ ਦੁੱਗਣਾ b = BT709_beta;

    ਵਾਪਸ (-b >= Lc) ? -a * ਘਾਤ(-Lc, 0.45) + (a - 1.0)
         : ( b >  Lc) ? 4.500 * Lc
         :               a * ਘਾਤ( Lc, 0.45) - (a - 1.0);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_iec61966_2_4_inv(ਦੁੱਗਣਾ E)
{
    ਅਚਲ ਦੁੱਗਣਾ a = BT709_alpha;
    ਅਚਲ ਦੁੱਗਣਾ b = 4.500 * BT709_beta;

    ਵਾਪਸ (-b >= E) ? -ਘਾਤ((-E + (a - 1.0)) / a, 1.0 / 0.45)
         : ( b >  E) ? E / 4.500
         :              ਘਾਤ(( E + (a - 1.0)) / a, 1.0 / 0.45);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_bt1361(ਦੁੱਗਣਾ Lc)
{
    ਅਚਲ ਦੁੱਗਣਾ a = BT709_alpha;
    ਅਚਲ ਦੁੱਗਣਾ b = BT709_beta;

    ਵਾਪਸ (-0.0045 >= Lc) ? -(a * ਘਾਤ(-4.0 * Lc, 0.45) + (a - 1.0)) / 4.0
         : ( b >  Lc) ? 4.500 * Lc
         :               a * ਘਾਤ( Lc, 0.45) - (a - 1.0);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_bt1361_inv(ਦੁੱਗਣਾ E)
{
    ਅਚਲ ਦੁੱਗਣਾ a = BT709_alpha;
    ਅਚਲ ਦੁੱਗਣਾ b = 4.500 * BT709_beta;

    ਵਾਪਸ (-0.02025 >= E) ? -ਘਾਤ((-4.0 * E - (a - 1.0)) / a, 1.0 / 0.45) / 4.0
         : ( b       >  E) ? E / 4.500
         :                    ਘਾਤ(( E + (a - 1.0)) / a, 1.0 / 0.45);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_iec61966_2_1(ਦੁੱਗਣਾ Lc)
{
    ਅਚਲ ਦੁੱਗਣਾ a = 1.055;
    ਅਚਲ ਦੁੱਗਣਾ b = 0.0031308;

    ਵਾਪਸ (0.0 > Lc) ? 0.0
         : (  b > Lc) ? 12.92 * Lc
         :              a * ਘਾਤ(Lc, 1.0  / 2.4) - (a - 1.0);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_iec61966_2_1_inv(ਦੁੱਗਣਾ E)
{
    ਅਚਲ ਦੁੱਗਣਾ a = 1.055;
    ਅਚਲ ਦੁੱਗਣਾ b = 12.92 * 0.0031308;

    ਵਾਪਸ (0.0 > E) ? 0.0
         : (  b > E) ? E / 12.92
                     : ਘਾਤ((E + (a - 1.0)) / a, 2.4);
    ਵਾਪਸ E;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PQ_c1 (        3424.0 / 4096.0) /* c3-c2 + 1 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PQ_c2 ( 32.0 * 2413.0 / 4096.0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PQ_c3 ( 32.0 * 2392.0 / 4096.0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PQ_m  (128.0 * 2523.0 / 4096.0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PQ_n  ( 0.25 * 2610.0 / 4096.0)

ਸਥਿਰ ਦੁੱਗਣਾ trc_smpte_st2084(ਦੁੱਗਣਾ Lc)
{
    ਅਚਲ ਦੁੱਗਣਾ c1 = PQ_c1;
    ਅਚਲ ਦੁੱਗਣਾ c2 = PQ_c2;
    ਅਚਲ ਦੁੱਗਣਾ c3 = PQ_c3;
    ਅਚਲ ਦੁੱਗਣਾ m  = PQ_m;
    ਅਚਲ ਦੁੱਗਣਾ n  = PQ_n;
    ਅਚਲ ਦੁੱਗਣਾ L  = Lc / 10000.0;
    ਅਚਲ ਦੁੱਗਣਾ Ln = ਘਾਤ(L, n);

    ਵਾਪਸ (0.0 > Lc) ? 0.0
         :              ਘਾਤ((c1 + c2 * Ln) / (1.0 + c3 * Ln), m);

}

ਸਥਿਰ ਦੁੱਗਣਾ trc_smpte_st2084_inv(ਦੁੱਗਣਾ E)
{
    ਅਚਲ ਦੁੱਗਣਾ c1 = PQ_c1;
    ਅਚਲ ਦੁੱਗਣਾ c2 = PQ_c2;
    ਅਚਲ ਦੁੱਗਣਾ c3 = PQ_c3;
    ਅਚਲ ਦੁੱਗਣਾ m  = PQ_m;
    ਅਚਲ ਦੁੱਗਣਾ n  = PQ_n;
    ਅਚਲ ਦੁੱਗਣਾ Em = ਘਾਤ(E, 1.0 / m);

    ਵਾਪਸ (c1 > Em) ? 0.0
                     : 10000.0 * ਘਾਤ((Em - c1) / (c2 - c3 * Em), 1.0 / n);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DCI_L 48.00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DCI_P 52.37

ਸਥਿਰ ਦੁੱਗਣਾ trc_smpte_st428_1(ਦੁੱਗਣਾ Lc)
{
    ਵਾਪਸ (0.0 > Lc) ? 0.0 : ਘਾਤ(DCI_L / DCI_P * Lc, 1.0 / 2.6);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_smpte_st428_1_inv(ਦੁੱਗਣਾ E)
{
    ਵਾਪਸ (0.0 > E) ? 0.0 : DCI_P / DCI_L * ਘਾਤ(E, 2.6);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HLG_a 0.17883277
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HLG_b 0.28466892
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HLG_c 0.55991073

ਸਥਿਰ ਦੁੱਗਣਾ trc_arib_std_b67(ਦੁੱਗਣਾ Lc) {
    // The function uses the definition from HEVC, which assumes that the peak
    // white is input level = 1. (this is equivalent to scaling E = Lc * 12 and
    // using the definition from the ARIB STD-B67 spec)
    ਅਚਲ ਦੁੱਗਣਾ a = HLG_a;
    ਅਚਲ ਦੁੱਗਣਾ b = HLG_b;
    ਅਚਲ ਦੁੱਗਣਾ c = HLG_c;
    ਵਾਪਸ (0.0 > Lc) ? 0.0 :
        (Lc <= 1.0 / 12.0 ? ਵਰਗਮੂਲ(3.0 * Lc) : a * ਲਘੂਗਣਕ(12.0 * Lc - b) + c);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_arib_std_b67_inv(ਦੁੱਗਣਾ E)
{
    ਅਚਲ ਦੁੱਗਣਾ a = HLG_a;
    ਅਚਲ ਦੁੱਗਣਾ b = HLG_b;
    ਅਚਲ ਦੁੱਗਣਾ c = HLG_c;
    ਵਾਪਸ (0.0 > E) ? 0.0 :
        (E <= 0.5 ? E * E / 3.0 : (ਘਾਤਾਂਕ((E - c) / a) + b) / 12.0);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VLOG_c1 0.01
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VLOG_c2 0.181
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VLOG_b  0.00873
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VLOG_c  0.241514
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VLOG_d  0.598206

ਸਥਿਰ ਦੁੱਗਣਾ trc_v_log(ਦੁੱਗਣਾ E)
{
    ਅਚਲ ਦੁੱਗਣਾ c1 = VLOG_c1;
    ਅਚਲ ਦੁੱਗਣਾ b = VLOG_b;
    ਅਚਲ ਦੁੱਗਣਾ c = VLOG_c;
    ਅਚਲ ਦੁੱਗਣਾ d = VLOG_d;
    ਵਾਪਸ (E < c1) ? (5.6 * E + 0.125) :
        (c * log10(E + b) + d);
}

ਸਥਿਰ ਦੁੱਗਣਾ trc_v_log_inv(ਦੁੱਗਣਾ E)
{
    ਅਚਲ ਦੁੱਗਣਾ c2 = VLOG_c2;
    ਅਚਲ ਦੁੱਗਣਾ b = VLOG_b;
    ਅਚਲ ਦੁੱਗਣਾ c = VLOG_c;
    ਅਚਲ ਦੁੱਗਣਾ d = VLOG_d;
    ਵਾਪਸ (E < c2) ? (E - 0.125) / 5.6 :
        (ਘਾਤ(10.0, ((E - d) / c)) - b);
}

ਸਥਿਰ ਅਚਲ av_csp_trc_function trc_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = trc_bt709,
    [AVCOL_TRC_GAMMA22] = trc_gamma22,
    [AVCOL_TRC_GAMMA28] = trc_gamma28,
    [AVCOL_TRC_SMPTE170M] = trc_bt709,
    [AVCOL_TRC_SMPTE240M] = trc_smpte240M,
    [AVCOL_TRC_ਰੇਖਿਕ] = trc_ਰੇਖਿਕ,
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

ਸਥਿਰ ਅਚਲ av_csp_trc_function trc_funcs_ext[AVCOL_TRC_EXT_NB -
                                               AVCOL_TRC_EXT_ਅਧਾਰ] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_ਅਧਾਰ] = trc_v_log,
};

av_csp_trc_function av_csp_trc_func_from_id(ਗਿਣਤੀ AVColorTransferCharacteristic trc)
{
    ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)trc < AVCOL_TRC_NB)
        ਵਾਪਸ trc_funcs[trc];
    ਨਹੀਂਤਾਂ ਜੇ (((ਬਿਨਾਨਿਸ਼ਾਨੀ)trc >= AVCOL_TRC_EXT_ਅਧਾਰ) &&
             ((ਬਿਨਾਨਿਸ਼ਾਨੀ)trc < AVCOL_TRC_EXT_NB))
        ਵਾਪਸ trc_funcs_ext[trc - AVCOL_TRC_EXT_ਅਧਾਰ];
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਅਚਲ av_csp_trc_function trc_inv_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = trc_bt709_inv,
    [AVCOL_TRC_GAMMA22] = trc_gamma22_inv,
    [AVCOL_TRC_GAMMA28] = trc_gamma28_inv,
    [AVCOL_TRC_SMPTE170M] = trc_bt709_inv,
    [AVCOL_TRC_SMPTE240M] = trc_smpte240M_inv,
    [AVCOL_TRC_ਰੇਖਿਕ] = trc_ਰੇਖਿਕ,
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

ਸਥਿਰ ਅਚਲ av_csp_trc_function trc_inv_funcs_ext[AVCOL_TRC_EXT_NB -
                                                   AVCOL_TRC_EXT_ਅਧਾਰ] = {
    [AVCOL_TRC_V_LOG - AVCOL_TRC_EXT_ਅਧਾਰ] = trc_v_log_inv,
};

av_csp_trc_function av_csp_trc_func_inv_from_id(ਗਿਣਤੀ AVColorTransferCharacteristic trc)
{
    ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)trc < AVCOL_TRC_NB)
        ਵਾਪਸ trc_inv_funcs[trc];
    ਨਹੀਂਤਾਂ ਜੇ (((ਬਿਨਾਨਿਸ਼ਾਨੀ)trc >= AVCOL_TRC_EXT_ਅਧਾਰ) &&
             ((ਬਿਨਾਨਿਸ਼ਾਨੀ)trc < AVCOL_TRC_EXT_NB))
        ਵਾਪਸ trc_inv_funcs_ext[trc - AVCOL_TRC_EXT_ਅਧਾਰ];
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ eotf_ਰੇਖਿਕ(ਅਚਲ ਦੁੱਗਣਾ Lw, ਅਚਲ ਦੁੱਗਣਾ Lb, ਦੁੱਗਣਾ E[3])
{
    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
        E[i] = (Lw - Lb) * E[i] + Lb;
}

ਸਥਿਰ ਖਾਲੀ eotf_ਰੇਖਿਕ_inv(ਅਚਲ ਦੁੱਗਣਾ Lw, ਅਚਲ ਦੁੱਗਣਾ Lb, ਦੁੱਗਣਾ L[3])
{
    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
        L[i] = (L[i] - Lb) / (Lw - Lb);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WRAP_SDR_OETF(name)                                         \
ਸਥਿਰ ਖਾਲੀ oetf_##name(ਦੁੱਗਣਾ L[3])                                \
{                                                                   \
    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)                                     \
        L[i] = trc_##name(L[i]);                                    \
}                                                                   \
                                                                    \
ਸਥਿਰ ਖਾਲੀ oetf_##name##_inv(ਦੁੱਗਣਾ E[3])                          \
{                                                                   \
    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)                                     \
        E[i] = trc_##name##_inv(E[i]);                              \
}

WRAP_SDR_OETF(gamma22)
WRAP_SDR_OETF(gamma28)
WRAP_SDR_OETF(iec61966_2_1)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ WRAP_SDR_EOTF(name)                                         \
ਸਥਿਰ ਖਾਲੀ eotf_##name(ਦੁੱਗਣਾ Lw, ਦੁੱਗਣਾ Lb, ਦੁੱਗਣਾ E[3])          \
{                                                                   \
    oetf_##name##_inv(E);                                           \
    eotf_ਰੇਖਿਕ(Lw, Lb, E);                                         \
}                                                                   \
                                                                    \
ਸਥਿਰ ਖਾਲੀ eotf_##name##_inv(ਦੁੱਗਣਾ Lw, ਦੁੱਗਣਾ Lb, ਦੁੱਗਣਾ L[3])    \
{                                                                   \
    eotf_ਰੇਖਿਕ_inv(Lw, Lb, L);                                     \
    oetf_##name(L);                                                 \
}

WRAP_SDR_EOTF(gamma22)
WRAP_SDR_EOTF(gamma28)
WRAP_SDR_EOTF(iec61966_2_1)

ਸਥਿਰ ਖਾਲੀ eotf_bt1886(ਅਚਲ ਦੁੱਗਣਾ Lw, ਅਚਲ ਦੁੱਗਣਾ Lb, ਦੁੱਗਣਾ E[3])
{
    ਅਚਲ ਦੁੱਗਣਾ Lw_inv = ਘਾਤ(Lw, 1.0 / 2.4);
    ਅਚਲ ਦੁੱਗਣਾ Lb_inv = ਘਾਤ(Lb, 1.0 / 2.4);
    ਅਚਲ ਦੁੱਗਣਾ a = ਘਾਤ(Lw_inv - Lb_inv, 2.4);
    ਅਚਲ ਦੁੱਗਣਾ b = Lb_inv / (Lw_inv - Lb_inv);

    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
        E[i] = (-b > E[i]) ? 0.0 : a * ਘਾਤ(E[i] + b, 2.4);
}

ਸਥਿਰ ਖਾਲੀ eotf_bt1886_inv(ਅਚਲ ਦੁੱਗਣਾ Lw, ਅਚਲ ਦੁੱਗਣਾ Lb, ਦੁੱਗਣਾ L[3])
{
    ਅਚਲ ਦੁੱਗਣਾ Lw_inv = ਘਾਤ(Lw, 1.0 / 2.4);
    ਅਚਲ ਦੁੱਗਣਾ Lb_inv = ਘਾਤ(Lb, 1.0 / 2.4);
    ਅਚਲ ਦੁੱਗਣਾ a = ਘਾਤ(Lw_inv - Lb_inv, 2.4);
    ਅਚਲ ਦੁੱਗਣਾ b = Lb_inv / (Lw_inv - Lb_inv);

    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
        L[i] = (0.0 > L[i]) ? 0.0 : ਘਾਤ(L[i] / a, 1.0 / 2.4) - b;
}

ਸਥਿਰ ਖਾਲੀ eotf_smpte_st2084(ਅਚਲ ਦੁੱਗਣਾ Lw, ਅਚਲ ਦੁੱਗਣਾ Lb, ਦੁੱਗਣਾ E[3])
{
    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
        E[i] = trc_smpte_st2084_inv(E[i]);
}

ਸਥਿਰ ਖਾਲੀ eotf_smpte_st2084_inv(ਅਚਲ ਦੁੱਗਣਾ Lw, ਅਚਲ ਦੁੱਗਣਾ Lb, ਦੁੱਗਣਾ L[3])
{
    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
        L[i] = trc_smpte_st2084(L[i]);
}

/* This implementation assumes an SMPTE RP 431-2 reference projector (DCI) */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DCI_L 48.00
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DCI_P 52.37
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DCI_X (42.94 / DCI_L)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DCI_Z (45.82 / DCI_L)

ਸਥਿਰ ਖਾਲੀ eotf_smpte_st428_1(ਅਚਲ ਦੁੱਗਣਾ Lw_Y, ਅਚਲ ਦੁੱਗਣਾ Lb_Y, ਦੁੱਗਣਾ E[3])
{
    ਅਚਲ ਦੁੱਗਣਾ Lw[3] = { DCI_X * Lw_Y, Lw_Y, DCI_Z * Lw_Y };
    ਅਚਲ ਦੁੱਗਣਾ Lb[3] = { DCI_X * Lb_Y, Lb_Y, DCI_Z * Lb_Y };

    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
        E[i] = (0.0 > E[i]) ? 0.0 : ਘਾਤ(E[i], 2.6) * DCI_P / DCI_L;
        E[i] = E[i] * (Lw[i] - Lb[i]) + Lb[i];
    }
}

ਸਥਿਰ ਖਾਲੀ eotf_smpte_st428_1_inv(ਅਚਲ ਦੁੱਗਣਾ Lw_Y, ਅਚਲ ਦੁੱਗਣਾ Lb_Y, ਦੁੱਗਣਾ L[3])
{
    ਅਚਲ ਦੁੱਗਣਾ Lw[3] = { DCI_X * Lw_Y, Lw_Y, DCI_Z * Lw_Y };
    ਅਚਲ ਦੁੱਗਣਾ Lb[3] = { DCI_X * Lb_Y, Lb_Y, DCI_Z * Lb_Y };

    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
        L[i] = (L[i] - Lb[i]) / (Lw[i] - Lb[i]);
        L[i] = (0.0 > L[i]) ? 0.0 : ਘਾਤ(L[i] * DCI_L / DCI_P, 1.0 / 2.6);
    }
}

ਸਥਿਰ ਖਾਲੀ eotf_arib_std_b67(ਅਚਲ ਦੁੱਗਣਾ Lw, ਅਚਲ ਦੁੱਗਣਾ Lb, ਦੁੱਗਣਾ E[3])
{
    ਅਚਲ ਦੁੱਗਣਾ gamma = fmax(1.2 + 0.42 * log10(Lw / 1000.0), 1.0);

    /**
     * Note: This equation is technically only accurate if the contrast ratio
     * Lw:Lb is greater than 12:1; otherwise we would need to use a different,
     * significantly more complicated solution. Ignore this as a highly
     * degenerate case, since any real world reference display will have a
     * static contrast ratio multiple orders of magnitude higher.
     */
    ਅਚਲ ਦੁੱਗਣਾ beta = ਵਰਗਮੂਲ(3 * ਘਾਤ(Lb / Lw, 1.0 / gamma));
    ਦੁੱਗਣਾ luma;

    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
        E[i] = trc_arib_std_b67_inv((1 - beta) * E[i] + beta);

    luma = 0.2627 * E[0] + 0.6780 * E[1] + 0.0593 * E[2];
    luma = ਘਾਤ(fmax(luma, 0.0), gamma - 1.0);
    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
        E[i] *= Lw * luma;
}

ਸਥਿਰ ਖਾਲੀ eotf_arib_std_b67_inv(ਅਚਲ ਦੁੱਗਣਾ Lw, ਅਚਲ ਦੁੱਗਣਾ Lb, ਦੁੱਗਣਾ L[3])
{
    ਅਚਲ ਦੁੱਗਣਾ gamma = fmax(1.2 + 0.42 * log10(Lw / 1000.0), 1.0);
    ਅਚਲ ਦੁੱਗਣਾ beta = ਵਰਗਮੂਲ(3 * ਘਾਤ(Lb / Lw, 1 / gamma));
    ਦੁੱਗਣਾ luma = 0.2627 * L[0] + 0.6780 * L[1] + 0.0593 * L[2];

    ਜੇ (luma > 0.0) {
        luma = ਘਾਤ(luma / Lw, (1 - gamma) / gamma);
        ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
            L[i] *= luma / Lw;
    } ਨਹੀਂਤਾਂ {
        L[0] = L[1] = L[2] = 0.0;
    }

    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
        L[i] = (trc_arib_std_b67(L[i]) - beta) / (1 - beta);
}

ਸਥਿਰ ਅਚਲ av_csp_eotf_function eotf_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = eotf_bt1886,
    [AVCOL_TRC_GAMMA22] = eotf_gamma22,
    [AVCOL_TRC_GAMMA28] = eotf_gamma28,
    [AVCOL_TRC_SMPTE170M] = eotf_bt1886,
    [AVCOL_TRC_SMPTE240M] = eotf_bt1886,
    [AVCOL_TRC_ਰੇਖਿਕ] = eotf_ਰੇਖਿਕ,
    /* There is no EOTF associated with these logarithmic encodings, since they
     * are defined purely for transmission of scene referred data. */
    [AVCOL_TRC_LOG] = ਨਿਰਾ,
    [AVCOL_TRC_LOG_SQRT] = ਨਿਰਾ,
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

av_csp_eotf_function av_csp_itu_eotf(ਗਿਣਤੀ AVColorTransferCharacteristic trc)
{
    ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)trc >= AVCOL_TRC_NB)
        ਵਾਪਸ ਨਿਰਾ;
    ਵਾਪਸ eotf_funcs[trc];
}

ਸਥਿਰ ਅਚਲ av_csp_eotf_function eotf_inv_funcs[AVCOL_TRC_NB] = {
    [AVCOL_TRC_BT709] = eotf_bt1886_inv,
    [AVCOL_TRC_GAMMA22] = eotf_gamma22_inv,
    [AVCOL_TRC_GAMMA28] = eotf_gamma28_inv,
    [AVCOL_TRC_SMPTE170M] = eotf_bt1886_inv,
    [AVCOL_TRC_SMPTE240M] = eotf_bt1886_inv,
    [AVCOL_TRC_ਰੇਖਿਕ] = eotf_ਰੇਖਿਕ_inv,
    [AVCOL_TRC_LOG] = ਨਿਰਾ,
    [AVCOL_TRC_LOG_SQRT] = ਨਿਰਾ,
    [AVCOL_TRC_IEC61966_2_4] = eotf_bt1886_inv,
    [AVCOL_TRC_BT1361_ECG] = eotf_bt1886_inv,
    [AVCOL_TRC_IEC61966_2_1] = eotf_iec61966_2_1_inv,
    [AVCOL_TRC_BT2020_10] = eotf_bt1886_inv,
    [AVCOL_TRC_BT2020_12] = eotf_bt1886_inv,
    [AVCOL_TRC_SMPTE2084] = eotf_smpte_st2084_inv,
    [AVCOL_TRC_SMPTE428] = eotf_smpte_st428_1_inv,
    [AVCOL_TRC_ARIB_STD_B67] = eotf_arib_std_b67_inv,
};

av_csp_eotf_function av_csp_itu_eotf_inv(ਗਿਣਤੀ AVColorTransferCharacteristic trc)
{
    ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)trc >= AVCOL_TRC_NB)
        ਵਾਪਸ ਨਿਰਾ;
    ਵਾਪਸ eotf_inv_funcs[trc];
}
