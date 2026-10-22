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

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/csp.h"
#అన్తర్భావ "libavutil/pixdesc.h"
#అన్తర్భావ "libavutil/pixfmt.h"

స్థిర శూన్య print_cie(స్థిరరాశి అక్షరం *label, AVCIExy xy)
{
    రాయి("  %s=(%d/%d, %d/%d)\n", label,
           xy.x.అంకె, xy.x.den, xy.y.అంకె, xy.y.den);
}

స్థిర పూర్ణాంకం cie_eq(AVCIExy a, AVCIExy b)
{
    తిరిగి av_cmp_q(a.x, b.x) == 0 && av_cmp_q(a.y, b.y) == 0;
}

స్థిర పూర్ణాంకం desc_eq(స్థిరరాశి AVColorPrimariesDesc *a, స్థిరరాశి AVColorPrimariesDesc *b)
{
    తిరిగి cie_eq(a->wp,     b->wp)     &&
           cie_eq(a->prim.r, b->prim.r) &&
           cie_eq(a->prim.g, b->prim.g) &&
           cie_eq(a->prim.b, b->prim.b);
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    /* av_csp_luma_coeffs_from_avcsp: iterate every defined colorspace */
    రాయి("Testing av_csp_luma_coeffs_from_avcsp()\n");
    కొరకు (గణన AVColorSpace csp = 0; csp < AVCOL_SPC_NB; csp++) {
        స్థిరరాశి AVLumaCoefficients *c = av_csp_luma_coeffs_from_avcsp(csp);
        స్థిరరాశి అక్షరం *name = av_color_space_name(csp);
        ఒకవేళ (!c) {
            రాయి("csp=%-16s -> NULL\n", name ? name : "?");
            కొనసాగు;
        }
        రాయి("csp=%-16s -> cr=%d/%d cg=%d/%d cb=%d/%d\n",
               name ? name : "?",
               c->cr.అంకె, c->cr.den,
               c->cg.అంకె, c->cg.den,
               c->cb.అంకె, c->cb.den);
    }
    /* out-of-range enum */
    రాయి("csp=AVCOL_SPC_NB         -> %s\n",
           av_csp_luma_coeffs_from_avcsp(AVCOL_SPC_NB) ? "FAIL" : "NULL");

    /* av_csp_primaries_desc_from_id + av_csp_primaries_id_from_desc */
    రాయి("\nTesting av_csp_primaries_desc_from_id() round trip\n");
    కొరకు (గణన AVColorPrimaries prm = 0; prm < AVCOL_PRI_EXT_NB; prm++) {
        స్థిరరాశి AVColorPrimariesDesc *d;
        స్థిరరాశి AVColorPrimariesDesc *d_వెనుక;
        గణన AVColorPrimaries వెనుక;
        స్థిరరాశి అక్షరం *name, *వెనుక_name, *స్థితి_2;

        ఒకవేళ (prm == AVCOL_PRI_NB)
            prm = AVCOL_PRI_EXT_పునాది;

        d    = av_csp_primaries_desc_from_id(prm);
        name = av_color_primaries_name(prm);
        ఒకవేళ (!d) {
            రాయి("prm=%-16s -> NULL\n", name ? name : "?");
            కొనసాగు;
        }
        రాయి("prm=%-16s ->\n", name ? name : "?");
        print_cie("wp ", d->wp);
        print_cie("r  ", d->prim.r);
        print_cie("g  ", d->prim.g);
        print_cie("b  ", d->prim.b);

        /* For colorspaces with identical primaries (e.g. smpte170m and
         * smpte240m), the canonical first match may differ from the input
         * enum, so compare descs not enums.  id_from_desc only searches
         * the base AVCOL_PRI_* range and returns UNSPECIFIED for
         * extended-range inputs that have no base match. */
        వెనుక      = av_csp_primaries_id_from_desc(d);
        d_వెనుక    = av_csp_primaries_desc_from_id(వెనుక);
        వెనుక_name = av_color_primaries_name(వెనుక);
        ఒకవేళ (వెనుక == AVCOL_PRI_UNSPECIFIED)
            స్థితి_2 = prm >= AVCOL_PRI_EXT_పునాది ? "ext-no-base-match"
                                               : "MISMATCH";
        లేకపోతే
            స్థితి_2 = d_వెనుక && desc_eq(d, d_వెనుక) ? "OK" : "MISMATCH";
        రాయి("  round-trip id=%-16s desc=%s\n",
               వెనుక_name ? వెనుక_name : "?", స్థితి_2);
    }
    /* out-of-range enum */
    రాయి("prm=AVCOL_PRI_NB         -> %s\n",
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
        గణన AVColorPrimaries వెనుక = av_csp_primaries_id_from_desc(&garbage);
        రాయి("garbage desc -> %s (expect AVCOL_PRI_UNSPECIFIED)\n",
               av_color_primaries_name(వెనుక) ? av_color_primaries_name(వెనుక) : "?");
    }

    /* av_csp_approximate_trc_gamma + av_csp_approximate_eotf_gamma:
     * both return values from static tables, so output is bitexact. */
    రాయి("\nTesting av_csp_approximate_{trc,eotf}_gamma()\n");
    కొరకు (గణన AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        స్థిరరాశి అక్షరం *name;
        ద్విగుణ g_trc, g_eotf;

        ఒకవేళ (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_పునాది;

        name   = av_color_transfer_name(trc);
        g_trc  = av_csp_approximate_trc_gamma(trc);
        g_eotf = av_csp_approximate_eotf_gamma(trc);
        రాయి("trc=%-16s trc_gamma=%.6f eotf_gamma=%.6f\n",
               name ? name : "?", g_trc, g_eotf);
    }
    /* out-of-range enum: both must return 0.0 */
    రాయి("trc=AVCOL_TRC_NB         trc_gamma=%.6f eotf_gamma=%.6f\n",
           av_csp_approximate_trc_gamma(AVCOL_TRC_NB),
           av_csp_approximate_eotf_gamma(AVCOL_TRC_NB));

    తిరిగి 0;
}
