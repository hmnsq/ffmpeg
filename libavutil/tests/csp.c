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

#அந்தர்பாவ <stdio.h>

#அந்தர்பாவ "libavutil/csp.h"
#அந்தர்பாவ "libavutil/pixdesc.h"
#அந்தர்பாவ "libavutil/pixfmt.h"

நிலையான வெறுமை print_cie(மாறிலி எழுத்து *label, AVCIExy xy)
{
    printf("  %s=(%d/%d, %d/%d)\n", label,
           xy.x.இலக்கம், xy.x.den, xy.y.இலக்கம், xy.y.den);
}

நிலையான முழு cie_eq(AVCIExy a, AVCIExy b)
{
    திரும்பு av_cmp_q(a.x, b.x) == 0 && av_cmp_q(a.y, b.y) == 0;
}

நிலையான முழு desc_eq(மாறிலி AVColorPrimariesDesc *a, மாறிலி AVColorPrimariesDesc *b)
{
    திரும்பு cie_eq(a->wp,     b->wp)     &&
           cie_eq(a->prim.r, b->prim.r) &&
           cie_eq(a->prim.g, b->prim.g) &&
           cie_eq(a->prim.b, b->prim.b);
}

முழு முதன்மை(வெறுமை)
{
    /* av_csp_luma_coeffs_from_avcsp: iterate every defined colorspace */
    printf("Testing av_csp_luma_coeffs_from_avcsp()\n");
    க்கு (எண்ணிக்கை AVColorSpace csp = 0; csp < AVCOL_SPC_NB; csp++) {
        மாறிலி AVLumaCoefficients *c = av_csp_luma_coeffs_from_avcsp(csp);
        மாறிலி எழுத்து *name = av_color_space_name(csp);
        எனில் (!c) {
            printf("csp=%-16s -> NULL\n", name ? name : "?");
            தொடர்;
        }
        printf("csp=%-16s -> cr=%d/%d cg=%d/%d cb=%d/%d\n",
               name ? name : "?",
               c->cr.இலக்கம், c->cr.den,
               c->cg.இலக்கம், c->cg.den,
               c->cb.இலக்கம், c->cb.den);
    }
    /* out-of-range enum */
    printf("csp=AVCOL_SPC_NB         -> %s\n",
           av_csp_luma_coeffs_from_avcsp(AVCOL_SPC_NB) ? "FAIL" : "NULL");

    /* av_csp_primaries_desc_from_id + av_csp_primaries_id_from_desc */
    printf("\nTesting av_csp_primaries_desc_from_id() round trip\n");
    க்கு (எண்ணிக்கை AVColorPrimaries prm = 0; prm < AVCOL_PRI_EXT_NB; prm++) {
        மாறிலி AVColorPrimariesDesc *d;
        மாறிலி AVColorPrimariesDesc *d_back;
        எண்ணிக்கை AVColorPrimaries back;
        மாறிலி எழுத்து *name, *back_name, *status;

        எனில் (prm == AVCOL_PRI_NB)
            prm = AVCOL_PRI_EXT_BASE;

        d    = av_csp_primaries_desc_from_id(prm);
        name = av_color_primaries_name(prm);
        எனில் (!d) {
            printf("prm=%-16s -> NULL\n", name ? name : "?");
            தொடர்;
        }
        printf("prm=%-16s ->\n", name ? name : "?");
        print_cie("wp ", d->wp);
        print_cie("r  ", d->prim.r);
        print_cie("g  ", d->prim.g);
        print_cie("b  ", d->prim.b);

        /* For colorspaces with identical primaries (e.g. smpte170m and
         * smpte240m), the canonical first match may differ from the input
         * enum, so compare descs not enums.  id_from_desc only searches
         * the base AVCOL_PRI_* range and returns UNSPECIFIED for
         * extended-range inputs that have no base match. */
        back      = av_csp_primaries_id_from_desc(d);
        d_back    = av_csp_primaries_desc_from_id(back);
        back_name = av_color_primaries_name(back);
        எனில் (back == AVCOL_PRI_UNSPECIFIED)
            status = prm >= AVCOL_PRI_EXT_BASE ? "ext-no-base-match"
                                               : "MISMATCH";
        இல்லையெனில்
            status = d_back && desc_eq(d, d_back) ? "OK" : "MISMATCH";
        printf("  round-trip id=%-16s desc=%s\n",
               back_name ? back_name : "?", status);
    }
    /* out-of-range enum */
    printf("prm=AVCOL_PRI_NB         -> %s\n",
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
        எண்ணிக்கை AVColorPrimaries back = av_csp_primaries_id_from_desc(&garbage);
        printf("garbage desc -> %s (expect AVCOL_PRI_UNSPECIFIED)\n",
               av_color_primaries_name(back) ? av_color_primaries_name(back) : "?");
    }

    /* av_csp_approximate_trc_gamma + av_csp_approximate_eotf_gamma:
     * both return values from static tables, so output is bitexact. */
    printf("\nTesting av_csp_approximate_{trc,eotf}_gamma()\n");
    க்கு (எண்ணிக்கை AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        மாறிலி எழுத்து *name;
        இரட்டை g_trc, g_eotf;

        எனில் (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_BASE;

        name   = av_color_transfer_name(trc);
        g_trc  = av_csp_approximate_trc_gamma(trc);
        g_eotf = av_csp_approximate_eotf_gamma(trc);
        printf("trc=%-16s trc_gamma=%.6f eotf_gamma=%.6f\n",
               name ? name : "?", g_trc, g_eotf);
    }
    /* out-of-range enum: both must return 0.0 */
    printf("trc=AVCOL_TRC_NB         trc_gamma=%.6f eotf_gamma=%.6f\n",
           av_csp_approximate_trc_gamma(AVCOL_TRC_NB),
           av_csp_approximate_eotf_gamma(AVCOL_TRC_NB));

    திரும்பு 0;
}
