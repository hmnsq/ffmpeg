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

#অন্তর্ভাৱ <stdio.h>

#অন্তর্ভাৱ "libavutil/csp.h"
#অন্তর্ভাৱ "libavutil/pixdesc.h"
#অন্তর্ভাৱ "libavutil/pixfmt.h"

স্থির শূন্য print_cie(ধ্রুৱ ৱর্ণ *label, AVCIExy xy)
{
    printf("  %s=(%d/%d, %d/%d)\n", label,
           xy.x.অঙ্ক, xy.x.den, xy.y.অঙ্ক, xy.y.den);
}

স্থির পূর্ণাঙ্ক cie_eq(AVCIExy a, AVCIExy b)
{
    ঘূৰাই av_cmp_q(a.x, b.x) == 0 && av_cmp_q(a.y, b.y) == 0;
}

স্থির পূর্ণাঙ্ক desc_eq(ধ্রুৱ AVColorPrimariesDesc *a, ধ্রুৱ AVColorPrimariesDesc *b)
{
    ঘূৰাই cie_eq(a->wp,     b->wp)     &&
           cie_eq(a->prim.r, b->prim.r) &&
           cie_eq(a->prim.g, b->prim.g) &&
           cie_eq(a->prim.b, b->prim.b);
}

পূর্ণাঙ্ক main(শূন্য)
{
    /* av_csp_luma_coeffs_from_avcsp: iterate every defined colorspace */
    printf("Testing av_csp_luma_coeffs_from_avcsp()\n");
    বাবে (গণনা AVColorSpace csp = 0; csp < AVCOL_SPC_NB; csp++) {
        ধ্রুৱ AVLumaCoefficients *c = av_csp_luma_coeffs_from_avcsp(csp);
        ধ্রুৱ ৱর্ণ *name = av_color_space_name(csp);
        যদি (!c) {
            printf("csp=%-16s -> NULL\n", name ? name : "?");
            অনুৱর্ত;
        }
        printf("csp=%-16s -> cr=%d/%d cg=%d/%d cb=%d/%d\n",
               name ? name : "?",
               c->cr.অঙ্ক, c->cr.den,
               c->cg.অঙ্ক, c->cg.den,
               c->cb.অঙ্ক, c->cb.den);
    }
    /* out-of-range enum */
    printf("csp=AVCOL_SPC_NB         -> %s\n",
           av_csp_luma_coeffs_from_avcsp(AVCOL_SPC_NB) ? "FAIL" : "NULL");

    /* av_csp_primaries_desc_from_id + av_csp_primaries_id_from_desc */
    printf("\nTesting av_csp_primaries_desc_from_id() round trip\n");
    বাবে (গণনা AVColorPrimaries prm = 0; prm < AVCOL_PRI_EXT_NB; prm++) {
        ধ্রুৱ AVColorPrimariesDesc *d;
        ধ্রুৱ AVColorPrimariesDesc *d_back;
        গণনা AVColorPrimaries back;
        ধ্রুৱ ৱর্ণ *name, *back_name, *status;

        যদি (prm == AVCOL_PRI_NB)
            prm = AVCOL_PRI_EXT_BASE;

        d    = av_csp_primaries_desc_from_id(prm);
        name = av_color_primaries_name(prm);
        যদি (!d) {
            printf("prm=%-16s -> NULL\n", name ? name : "?");
            অনুৱর্ত;
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
        যদি (back == AVCOL_PRI_UNSPECIFIED)
            status = prm >= AVCOL_PRI_EXT_BASE ? "ext-no-base-match"
                                               : "MISMATCH";
        অন্যথা
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
        গণনা AVColorPrimaries back = av_csp_primaries_id_from_desc(&garbage);
        printf("garbage desc -> %s (expect AVCOL_PRI_UNSPECIFIED)\n",
               av_color_primaries_name(back) ? av_color_primaries_name(back) : "?");
    }

    /* av_csp_approximate_trc_gamma + av_csp_approximate_eotf_gamma:
     * both return values from static tables, so output is bitexact. */
    printf("\nTesting av_csp_approximate_{trc,eotf}_gamma()\n");
    বাবে (গণনা AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        ধ্রুৱ ৱর্ণ *name;
        দ্ৱিগুণ g_trc, g_eotf;

        যদি (trc == AVCOL_TRC_NB)
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

    ঘূৰাই 0;
}
