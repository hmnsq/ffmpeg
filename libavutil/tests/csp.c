/*
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

#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/csp.h"
#ಅನ್ತರ್ಭಾವ "libavutil/pixdesc.h"
#ಅನ್ತರ್ಭಾವ "libavutil/pixfmt.h"

ಸ್ಥಿರ ಶೂನ್ಯ print_cie(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *label, AVCIExy xy)
{
    ಬರೆ("  %s=(%d/%d, %d/%d)\n", label,
           xy.x.ಅಂಕೆ, xy.x.den, xy.y.ಅಂಕೆ, xy.y.den);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ cie_eq(AVCIExy a, AVCIExy b)
{
    ಹಿಂತಿರುಗಿ av_cmp_q(a.x, b.x) == 0 && av_cmp_q(a.y, b.y) == 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ desc_eq(ಸ್ಥಿರಾಂಕ AVColorPrimariesDesc *a, ಸ್ಥಿರಾಂಕ AVColorPrimariesDesc *b)
{
    ಹಿಂತಿರುಗಿ cie_eq(a->wp,     b->wp)     &&
           cie_eq(a->prim.r, b->prim.r) &&
           cie_eq(a->prim.g, b->prim.g) &&
           cie_eq(a->prim.b, b->prim.b);
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    /* av_csp_luma_coeffs_from_avcsp: iterate every defined colorspace */
    ಬರೆ("Testing av_csp_luma_coeffs_from_avcsp()\n");
    ಗಾಗಿ (ಎಣಿಕೆ AVColorSpace csp = 0; csp < AVCOL_SPC_NB; csp++) {
        ಸ್ಥಿರಾಂಕ AVLumaCoefficients *c = av_csp_luma_coeffs_from_avcsp(csp);
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name = av_color_space_name(csp);
        ಆದರೆ (!c) {
            ಬರೆ("csp=%-16s -> NULL\n", name ? name : "?");
            ಮುಂದುವರಿ;
        }
        ಬರೆ("csp=%-16s -> cr=%d/%d cg=%d/%d cb=%d/%d\n",
               name ? name : "?",
               c->cr.ಅಂಕೆ, c->cr.den,
               c->cg.ಅಂಕೆ, c->cg.den,
               c->cb.ಅಂಕೆ, c->cb.den);
    }
    /* out-of-range enum */
    ಬರೆ("csp=AVCOL_SPC_NB         -> %s\n",
           av_csp_luma_coeffs_from_avcsp(AVCOL_SPC_NB) ? "FAIL" : "NULL");

    /* av_csp_primaries_desc_from_id + av_csp_primaries_id_from_desc */
    ಬರೆ("\nTesting av_csp_primaries_desc_from_id() round trip\n");
    ಗಾಗಿ (ಎಣಿಕೆ AVColorPrimaries prm = 0; prm < AVCOL_PRI_EXT_NB; prm++) {
        ಸ್ಥಿರಾಂಕ AVColorPrimariesDesc *d;
        ಸ್ಥಿರಾಂಕ AVColorPrimariesDesc *d_ಹಿಂಭಾಗ;
        ಎಣಿಕೆ AVColorPrimaries ಹಿಂಭಾಗ;
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name, *ಹಿಂಭಾಗ_name, *ಸ್ಥಿತಿ_2;

        ಆದರೆ (prm == AVCOL_PRI_NB)
            prm = AVCOL_PRI_EXT_ತಳ;

        d    = av_csp_primaries_desc_from_id(prm);
        name = av_color_primaries_name(prm);
        ಆದರೆ (!d) {
            ಬರೆ("prm=%-16s -> NULL\n", name ? name : "?");
            ಮುಂದುವರಿ;
        }
        ಬರೆ("prm=%-16s ->\n", name ? name : "?");
        print_cie("wp ", d->wp);
        print_cie("r  ", d->prim.r);
        print_cie("g  ", d->prim.g);
        print_cie("b  ", d->prim.b);

        /* For colorspaces with identical primaries (e.g. smpte170m and
         * smpte240m), the canonical first match may differ from the input
         * enum, so compare descs not enums.  id_from_desc only searches
         * the base AVCOL_PRI_* range and returns UNSPECIFIED for
         * extended-range inputs that have no base match. */
        ಹಿಂಭಾಗ      = av_csp_primaries_id_from_desc(d);
        d_ಹಿಂಭಾಗ    = av_csp_primaries_desc_from_id(ಹಿಂಭಾಗ);
        ಹಿಂಭಾಗ_name = av_color_primaries_name(ಹಿಂಭಾಗ);
        ಆದರೆ (ಹಿಂಭಾಗ == AVCOL_PRI_UNSPECIFIED)
            ಸ್ಥಿತಿ_2 = prm >= AVCOL_PRI_EXT_ತಳ ? "ext-no-base-match"
                                               : "MISMATCH";
        ಇಲ್ಲದಿದ್ದರೆ
            ಸ್ಥಿತಿ_2 = d_ಹಿಂಭಾಗ && desc_eq(d, d_ಹಿಂಭಾಗ) ? "OK" : "MISMATCH";
        ಬರೆ("  round-trip id=%-16s desc=%s\n",
               ಹಿಂಭಾಗ_name ? ಹಿಂಭಾಗ_name : "?", ಸ್ಥಿತಿ_2);
    }
    /* out-of-range enum */
    ಬರೆ("prm=AVCOL_PRI_NB         -> %s\n",
           av_csp_primaries_desc_from_id(AVCOL_PRI_NB) ? "FAIL" : "NULL");

    /* id_from_desc on a garbage description returns UNSPECIFIED */
    {
        AVColorPrimariesDesc garbage = {
            .wp   = { { 0, 1 }, { 0, 1 } },
            .prim = {
                .r = { { 0, 1 }, { 0, 1 } },
                .g = { { 0, 1 }, { 0, 1 } },
                .b = { { 0, 1 }, { 0, 1 } },
            },
        };
        ಎಣಿಕೆ AVColorPrimaries ಹಿಂಭಾಗ = av_csp_primaries_id_from_desc(&garbage);
        ಬರೆ("garbage desc -> %s (expect AVCOL_PRI_UNSPECIFIED)\n",
               av_color_primaries_name(ಹಿಂಭಾಗ) ? av_color_primaries_name(ಹಿಂಭಾಗ) : "?");
    }

    /* av_csp_approximate_trc_gamma + av_csp_approximate_eotf_gamma:
     * both return values from static tables, so output is bitexact. */
    ಬರೆ("\nTesting av_csp_approximate_{trc,eotf}_gamma()\n");
    ಗಾಗಿ (ಎಣಿಕೆ AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;
        ದ್ವಿಗುಣ g_trc, g_eotf;

        ಆದರೆ (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_ತಳ;

        name   = av_color_transfer_name(trc);
        g_trc  = av_csp_approximate_trc_gamma(trc);
        g_eotf = av_csp_approximate_eotf_gamma(trc);
        ಬರೆ("trc=%-16s trc_gamma=%.6f eotf_gamma=%.6f\n",
               name ? name : "?", g_trc, g_eotf);
    }
    /* out-of-range enum: both must return 0.0 */
    ಬರೆ("trc=AVCOL_TRC_NB         trc_gamma=%.6f eotf_gamma=%.6f\n",
           av_csp_approximate_trc_gamma(AVCOL_TRC_NB),
           av_csp_approximate_eotf_gamma(AVCOL_TRC_NB));

    ಹಿಂತಿರುಗಿ 0;
}
