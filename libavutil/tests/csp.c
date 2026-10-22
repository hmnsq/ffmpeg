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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/csp.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/pixfmt.h"

ਸਥਿਰ ਖਾਲੀ print_cie(ਅਚਲ ਅੱਖਰ *label, AVCIExy xy)
{
    ਲਿਖੋ("  %s=(%d/%d, %d/%d)\n", label,
           xy.x.ਅੰਕ, xy.x.den, xy.y.ਅੰਕ, xy.y.den);
}

ਸਥਿਰ ਪੂਰਨ cie_eq(AVCIExy a, AVCIExy b)
{
    ਵਾਪਸ av_cmp_q(a.x, b.x) == 0 && av_cmp_q(a.y, b.y) == 0;
}

ਸਥਿਰ ਪੂਰਨ desc_eq(ਅਚਲ AVColorPrimariesDesc *a, ਅਚਲ AVColorPrimariesDesc *b)
{
    ਵਾਪਸ cie_eq(a->wp,     b->wp)     &&
           cie_eq(a->prim.r, b->prim.r) &&
           cie_eq(a->prim.g, b->prim.g) &&
           cie_eq(a->prim.b, b->prim.b);
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    /* av_csp_luma_coeffs_from_avcsp: iterate every defined colorspace */
    ਲਿਖੋ("Testing av_csp_luma_coeffs_from_avcsp()\n");
    ਲਈ (ਗਿਣਤੀ AVColorSpace csp = 0; csp < AVCOL_SPC_NB; csp++) {
        ਅਚਲ AVLumaCoefficients *c = av_csp_luma_coeffs_from_avcsp(csp);
        ਅਚਲ ਅੱਖਰ *name = av_color_space_name(csp);
        ਜੇ (!c) {
            ਲਿਖੋ("csp=%-16s -> NULL\n", name ? name : "?");
            ਜਾਰੀ;
        }
        ਲਿਖੋ("csp=%-16s -> cr=%d/%d cg=%d/%d cb=%d/%d\n",
               name ? name : "?",
               c->cr.ਅੰਕ, c->cr.den,
               c->cg.ਅੰਕ, c->cg.den,
               c->cb.ਅੰਕ, c->cb.den);
    }
    /* out-of-range enum */
    ਲਿਖੋ("csp=AVCOL_SPC_NB         -> %s\n",
           av_csp_luma_coeffs_from_avcsp(AVCOL_SPC_NB) ? "FAIL" : "NULL");

    /* av_csp_primaries_desc_from_id + av_csp_primaries_id_from_desc */
    ਲਿਖੋ("\nTesting av_csp_primaries_desc_from_id() round trip\n");
    ਲਈ (ਗਿਣਤੀ AVColorPrimaries prm = 0; prm < AVCOL_PRI_EXT_NB; prm++) {
        ਅਚਲ AVColorPrimariesDesc *d;
        ਅਚਲ AVColorPrimariesDesc *d_ਪਿੱਠ;
        ਗਿਣਤੀ AVColorPrimaries ਪਿੱਠ;
        ਅਚਲ ਅੱਖਰ *name, *ਪਿੱਠ_name, *ਸਥਿਤੀ;

        ਜੇ (prm == AVCOL_PRI_NB)
            prm = AVCOL_PRI_EXT_ਅਧਾਰ;

        d    = av_csp_primaries_desc_from_id(prm);
        name = av_color_primaries_name(prm);
        ਜੇ (!d) {
            ਲਿਖੋ("prm=%-16s -> NULL\n", name ? name : "?");
            ਜਾਰੀ;
        }
        ਲਿਖੋ("prm=%-16s ->\n", name ? name : "?");
        print_cie("wp ", d->wp);
        print_cie("r  ", d->prim.r);
        print_cie("g  ", d->prim.g);
        print_cie("b  ", d->prim.b);

        /* For colorspaces with identical primaries (e.g. smpte170m and
         * smpte240m), the canonical first match may differ from the input
         * enum, so compare descs not enums.  id_from_desc only searches
         * the base AVCOL_PRI_* range and returns UNSPECIFIED for
         * extended-range inputs that have no base match. */
        ਪਿੱਠ      = av_csp_primaries_id_from_desc(d);
        d_ਪਿੱਠ    = av_csp_primaries_desc_from_id(ਪਿੱਠ);
        ਪਿੱਠ_name = av_color_primaries_name(ਪਿੱਠ);
        ਜੇ (ਪਿੱਠ == AVCOL_PRI_UNSPECIFIED)
            ਸਥਿਤੀ = prm >= AVCOL_PRI_EXT_ਅਧਾਰ ? "ext-no-base-match"
                                               : "MISMATCH";
        ਨਹੀਂਤਾਂ
            ਸਥਿਤੀ = d_ਪਿੱਠ && desc_eq(d, d_ਪਿੱਠ) ? "OK" : "MISMATCH";
        ਲਿਖੋ("  round-trip id=%-16s desc=%s\n",
               ਪਿੱਠ_name ? ਪਿੱਠ_name : "?", ਸਥਿਤੀ);
    }
    /* out-of-range enum */
    ਲਿਖੋ("prm=AVCOL_PRI_NB         -> %s\n",
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
        ਗਿਣਤੀ AVColorPrimaries ਪਿੱਠ = av_csp_primaries_id_from_desc(&garbage);
        ਲਿਖੋ("garbage desc -> %s (expect AVCOL_PRI_UNSPECIFIED)\n",
               av_color_primaries_name(ਪਿੱਠ) ? av_color_primaries_name(ਪਿੱਠ) : "?");
    }

    /* av_csp_approximate_trc_gamma + av_csp_approximate_eotf_gamma:
     * both return values from static tables, so output is bitexact. */
    ਲਿਖੋ("\nTesting av_csp_approximate_{trc,eotf}_gamma()\n");
    ਲਈ (ਗਿਣਤੀ AVColorTransferCharacteristic trc = 0; trc < AVCOL_TRC_EXT_NB; trc++) {
        ਅਚਲ ਅੱਖਰ *name;
        ਦੁੱਗਣਾ g_trc, g_eotf;

        ਜੇ (trc == AVCOL_TRC_NB)
            trc = AVCOL_TRC_EXT_ਅਧਾਰ;

        name   = av_color_transfer_name(trc);
        g_trc  = av_csp_approximate_trc_gamma(trc);
        g_eotf = av_csp_approximate_eotf_gamma(trc);
        ਲਿਖੋ("trc=%-16s trc_gamma=%.6f eotf_gamma=%.6f\n",
               name ? name : "?", g_trc, g_eotf);
    }
    /* out-of-range enum: both must return 0.0 */
    ਲਿਖੋ("trc=AVCOL_TRC_NB         trc_gamma=%.6f eotf_gamma=%.6f\n",
           av_csp_approximate_trc_gamma(AVCOL_TRC_NB),
           av_csp_approximate_eotf_gamma(AVCOL_TRC_NB));

    ਵਾਪਸ 0;
}
