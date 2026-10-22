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

#شامل <stdio.h>

#شامل "libavutil/csp.h"
#شامل "libavutil/pixdesc.h"
#شامل "libavutil/pixfmt.h"

ساکن خالی print_cie(ثابت حرف *label, AVCIExy xy)
{
    لکھو("  %s=(%d/%d, %d/%d)\n", label,
           xy.x.عدد, xy.x.den, xy.y.عدد, xy.y.den);
}

ساکن صحیح cie_eq(AVCIExy a, AVCIExy b)
{
    واپس av_cmp_q(a.x, b.x) == 0 && av_cmp_q(a.y, b.y) == 0;
}

ساکن صحیح desc_eq(ثابت AVColorPrimariesDesc *a, ثابت AVColorPrimariesDesc *b)
{
    واپس cie_eq(a->wp,     b->wp)     &&
           cie_eq(a->prim.r, b->prim.r) &&
           cie_eq(a->prim.g, b->prim.g) &&
           cie_eq(a->prim.b, b->prim.b);
}

صحیح مین(خالی)
{
    /* av_csp_luma_coeffs_from_avcsp: iterate every defined colorspace */
    لکھو("Testing av_csp_luma_coeffs_from_avcsp()\n");
    برائے (شمار AVColorSpace csp = 0; csp < AVCOL_SPC_NB; csp++) {
        ثابت AVLumaCoefficients *c = av_csp_luma_coeffs_from_avcsp(csp);
        ثابت حرف *name = av_color_space_name(csp);
        اگر (!c) {
            لکھو("csp=%-16s -> NULL\n", name ? name : "?");
            جاری;
        }
        لکھو("csp=%-16s -> cr=%d/%d cg=%d/%d cb=%d/%d\n",
               name ? name : "?",
               c->cr.عدد, c->cr.den,
               c->cg.عدد, c->cg.den,
               c->cb.عدد, c->cb.den);
    }
    /* out-of-range enum */
    لکھو("csp=AVCOL_SPC_NB         -> %s\n",
           av_csp_luma_coeffs_from_avcsp(AVCOL_SPC_NB) ? "FAIL" : "NULL");

    /* av_csp_primaries_desc_from_id + av_csp_primaries_id_from_desc */
    لکھو("\nTesting av_csp_primaries_desc_from_id() round trip\n");
    برائے (شمار AVColorPrimaries prm = 0; prm < AVCOL_PRI_EXT_NB; prm++) {
        ثابت AVColorPrimariesDesc *d;
        ثابت AVColorPrimariesDesc *d_عقب;
        شمار AVColorPrimaries عقب;
        ثابت حرف *name, *عقب_name, *حالت_2;

        اگر (prm == AVCOL_PRI_NB)
            prm = AVCOL_PRI_EXT_بنیاد;

        d    = av_csp_primaries_desc_from_id(prm);
        name = av_color_primaries_name(prm);
        اگر (!d) {
            لکھو("prm=%-16s -> NULL\n", name ? name : "?");
            جاری;
        }
        لکھو("prm=%-16s ->\n", name ? name : "?");
        print_cie("wp ", d->wp);
        print_cie("r  ", d->prim.r);
        print_cie("g  ", d->prim.g);
        print_cie("b  ", d->prim.b);

        /* For colorspaces with identical primaries (e.g. smpte170m and
         * smpte240m), the canonical first match may differ from the input
         * enum, so compare descs not enums.  id_from_desc only searches
         * the base AVCOL_PRI_* range and returns UNSPECIFIED for
         * extended-range inputs that have no base match. */
        عقب      = av_csp_primaries_id_from_desc(d);
        d_عقب    = av_csp_primaries_desc_from_id(عقب);
        عقب_name = av_color_primaries_name(عقب);
        اگر (عقب == AVCOL_PRI_UNSPECIFIED)
            حالت_2 = prm >= AVCOL_PRI_EXT_بنیاد ? "ext-no-base-match"
                                               : "MISMATCH";
        ورنہ
            حالت_2 = d_عقب && desc_eq(d, d_عقب) ? "OK" : "MISMATCH";
        لکھو("  round-trip id=%-16s desc=%s\n",
               عقب_name ? عقب_name : "?", حالت_2);
    }
    /* out-of-range enum */
    لکھو("prm=AVCOL_PRI_NB         -> %s\n",
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
        شمار AVColorPrimaries عقب = av_csp_primaries_id_from_desc(&garbage);
        لکھو("garbage desc -> %s (expect AVCOL_PRI_UNSPECIFIED)\n",
               av_color_primaries_name(عقب) ? av_color_primaries_name(عقب) : "?");
    }

    /* av_csp_approximate_trc_gamma + av_csp_approximate_eotf_gamma:
     * both return values from static tables, so output is bitexact. */
    لکھو("\nTesting av_csp_approximate_{trc,eotf}_gamma()\n");
    برائے (شمار AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        ثابت حرف *name;
        دوہرا g_trc, g_eotf;

        اگر (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_بنیاد;

        name   = av_color_transfer_name(trc);
        g_trc  = av_csp_approximate_trc_gamma(trc);
        g_eotf = av_csp_approximate_eotf_gamma(trc);
        لکھو("trc=%-16s trc_gamma=%.6f eotf_gamma=%.6f\n",
               name ? name : "?", g_trc, g_eotf);
    }
    /* out-of-range enum: both must return 0.0 */
    لکھو("trc=AVCOL_TRC_NB         trc_gamma=%.6f eotf_gamma=%.6f\n",
           av_csp_approximate_trc_gamma(AVCOL_TRC_NB),
           av_csp_approximate_eotf_gamma(AVCOL_TRC_NB));

    واپس 0;
}
