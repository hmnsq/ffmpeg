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

#ضمن <stdio.h>

#ضمن "libavutil/csp.h"
#ضمن "libavutil/pixdesc.h"
#ضمن "libavutil/pixfmt.h"

ساكن فراغ print_cie(ثابت حرف *label, AVCIExy xy)
{
    لکو("  %s=(%d/%d, %d/%d)\n", label,
           xy.x.انگ, xy.x.den, xy.y.انگ, xy.y.den);
}

ساكن صحيح cie_eq(AVCIExy a, AVCIExy b)
{
    أرجع av_cmp_q(a.x, b.x) == 0 && av_cmp_q(a.y, b.y) == 0;
}

ساكن صحيح desc_eq(ثابت AVColorPrimariesDesc *a, ثابت AVColorPrimariesDesc *b)
{
    أرجع cie_eq(a->wp,     b->wp)     &&
           cie_eq(a->prim.r, b->prim.r) &&
           cie_eq(a->prim.g, b->prim.g) &&
           cie_eq(a->prim.b, b->prim.b);
}

صحيح مکيه(فراغ)
{
    /* av_csp_luma_coeffs_from_avcsp: iterate every defined colorspace */
    لکو("Testing av_csp_luma_coeffs_from_avcsp()\n");
    لكل (تعداد AVColorSpace csp = 0; csp < AVCOL_SPC_NB; csp++) {
        ثابت AVLumaCoefficients *c = av_csp_luma_coeffs_from_avcsp(csp);
        ثابت حرف *name = av_color_space_name(csp);
        إذا (!c) {
            لکو("csp=%-16s -> NULL\n", name ? name : "?");
            استمر;
        }
        لکو("csp=%-16s -> cr=%d/%d cg=%d/%d cb=%d/%d\n",
               name ? name : "?",
               c->cr.انگ, c->cr.den,
               c->cg.انگ, c->cg.den,
               c->cb.انگ, c->cb.den);
    }
    /* out-of-range enum */
    لکو("csp=AVCOL_SPC_NB         -> %s\n",
           av_csp_luma_coeffs_from_avcsp(AVCOL_SPC_NB) ? "FAIL" : "NULL");

    /* av_csp_primaries_desc_from_id + av_csp_primaries_id_from_desc */
    لکو("\nTesting av_csp_primaries_desc_from_id() round trip\n");
    لكل (تعداد AVColorPrimaries prm = 0; prm < AVCOL_PRI_EXT_NB; prm++) {
        ثابت AVColorPrimariesDesc *d;
        ثابت AVColorPrimariesDesc *d_پٺ;
        تعداد AVColorPrimaries پٺ;
        ثابت حرف *name, *پٺ_name, *حالت;

        إذا (prm == AVCOL_PRI_NB)
            prm = AVCOL_PRI_EXT_بنياد;

        d    = av_csp_primaries_desc_from_id(prm);
        name = av_color_primaries_name(prm);
        إذا (!d) {
            لکو("prm=%-16s -> NULL\n", name ? name : "?");
            استمر;
        }
        لکو("prm=%-16s ->\n", name ? name : "?");
        print_cie("wp ", d->wp);
        print_cie("r  ", d->prim.r);
        print_cie("g  ", d->prim.g);
        print_cie("b  ", d->prim.b);

        /* For colorspaces with identical primaries (e.g. smpte170m and
         * smpte240m), the canonical first match may differ from the input
         * enum, so compare descs not enums.  id_from_desc only searches
         * the base AVCOL_PRI_* range and returns UNSPECIFIED for
         * extended-range inputs that have no base match. */
        پٺ      = av_csp_primaries_id_from_desc(d);
        d_پٺ    = av_csp_primaries_desc_from_id(پٺ);
        پٺ_name = av_color_primaries_name(پٺ);
        إذا (پٺ == AVCOL_PRI_UNSPECIFIED)
            حالت = prm >= AVCOL_PRI_EXT_بنياد ? "ext-no-base-match"
                                               : "MISMATCH";
        وإلا
            حالت = d_پٺ && desc_eq(d, d_پٺ) ? "OK" : "MISMATCH";
        لکو("  round-trip id=%-16s desc=%s\n",
               پٺ_name ? پٺ_name : "?", حالت);
    }
    /* out-of-range enum */
    لکو("prm=AVCOL_PRI_NB         -> %s\n",
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
        تعداد AVColorPrimaries پٺ = av_csp_primaries_id_from_desc(&garbage);
        لکو("garbage desc -> %s (expect AVCOL_PRI_UNSPECIFIED)\n",
               av_color_primaries_name(پٺ) ? av_color_primaries_name(پٺ) : "?");
    }

    /* av_csp_approximate_trc_gamma + av_csp_approximate_eotf_gamma:
     * both return values from static tables, so output is bitexact. */
    لکو("\nTesting av_csp_approximate_{trc,eotf}_gamma()\n");
    لكل (تعداد AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        ثابت حرف *name;
        مزدوج g_trc, g_eotf;

        إذا (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_بنياد;

        name   = av_color_transfer_name(trc);
        g_trc  = av_csp_approximate_trc_gamma(trc);
        g_eotf = av_csp_approximate_eotf_gamma(trc);
        لکو("trc=%-16s trc_gamma=%.6f eotf_gamma=%.6f\n",
               name ? name : "?", g_trc, g_eotf);
    }
    /* out-of-range enum: both must return 0.0 */
    لکو("trc=AVCOL_TRC_NB         trc_gamma=%.6f eotf_gamma=%.6f\n",
           av_csp_approximate_trc_gamma(AVCOL_TRC_NB),
           av_csp_approximate_eotf_gamma(AVCOL_TRC_NB));

    أرجع 0;
}
