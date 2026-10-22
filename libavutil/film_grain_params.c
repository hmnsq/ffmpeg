/**
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

#ਅਨ੍ਤਰ੍ਭਾਵ "film_grain_params.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"

AVFilmGrainParams *av_film_grain_params_alloc(size_t *ਮਾਪ)
{
    AVFilmGrainParams *params = av_mallocz(ਆਕਾਰ(AVFilmGrainParams));

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = params ? ਆਕਾਰ(*params) : 0;

    ਵਾਪਸ params;
}

AVFilmGrainParams *av_film_grain_params_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ)
{
    AVFilmGrainParams *fgp;
    AVFrame_Side_ਅੰਕੜੇ *side_ਅੰਕੜੇ = av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ(ਚੌਖਟਾ,
                                                        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_FILM_GRAIN_PARAMS,
                                                        ਆਕਾਰ(AVFilmGrainParams));
    ਜੇ (!side_ਅੰਕੜੇ)
        ਵਾਪਸ ਨਿਰਾ;

    fgp = (AVFilmGrainParams *) side_ਅੰਕੜੇ->ਅੰਕੜੇ;
    *fgp = (AVFilmGrainParams) {
        .color_range     = AVCOL_RANGE_UNSPECIFIED,
        .color_primaries = AVCOL_PRI_UNSPECIFIED,
        .color_trc       = AVCOL_TRC_UNSPECIFIED,
        .color_space     = AVCOL_SPC_UNSPECIFIED,
    };

    ਵਾਪਸ fgp;
}

ਅਚਲ AVFilmGrainParams *av_film_grain_params_select(ਅਚਲ AVFrame *ਚੌਖਟਾ)
{
    ਅਚਲ AVFilmGrainParams *fgp, *ਉੱਤਮ = ਨਿਰਾ;
    ਅਚਲ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ਚੌਖਟਾ->format);
    ਪੂਰਨ ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_luma, ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_chroma;
    ਜੇ (!desc)
        ਵਾਪਸ ਨਿਰਾ;

    /* There are no YUV formats with different bit depth per component,
     * so just check both against the first component for simplicity */
    ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_luma = ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_chroma = desc->comp[0].ਡੂੰਘਾਈ;

    ਲਈ (ਪੂਰਨ i = 0; i < ਚੌਖਟਾ->nb_side_ਅੰਕੜੇ; i++) {
        ਜੇ (ਚੌਖਟਾ->side_ਅੰਕੜੇ[i]->type != AV_ਚੌਖਟਾ_ਅੰਕੜੇ_FILM_GRAIN_PARAMS)
            ਜਾਰੀ;
        fgp = (ਅਚਲ AVFilmGrainParams*)ਚੌਖਟਾ->side_ਅੰਕੜੇ[i]->ਅੰਕੜੇ;
        ਜੇ (fgp->ਚੌੜਾਈ  && fgp->ਚੌੜਾਈ  > ਚੌਖਟਾ->ਚੌੜਾਈ ||
            fgp->ਉਚਾਈ && fgp->ਉਚਾਈ > ਚੌਖਟਾ->ਉਚਾਈ)
            ਜਾਰੀ;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK(a, b, unspec)                                     \
        ਜੇ ((a) != (unspec) && (b) != (unspec) && (a) != (b))   \
            ਜਾਰੀ

        CHECK(fgp->ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_luma,   ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_luma,         0);
        CHECK(fgp->ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_chroma, ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_chroma,       0);
        CHECK(fgp->color_range,      ਚੌਖਟਾ->color_range,     AVCOL_RANGE_UNSPECIFIED);
        CHECK(fgp->color_primaries,  ਚੌਖਟਾ->color_primaries, AVCOL_PRI_UNSPECIFIED);
        CHECK(fgp->color_trc,        ਚੌਖਟਾ->color_trc,       AVCOL_TRC_UNSPECIFIED);
        CHECK(fgp->color_space,      ਚੌਖਟਾ->colorspace,      AVCOL_SPC_UNSPECIFIED);

        ਚੋਣ (fgp->type) {
        ਹਾਲਤ AV_FILM_GRAIN_PARAMS_NONE:
            ਜਾਰੀ;
        ਹਾਲਤ AV_FILM_GRAIN_PARAMS_AV1:
            /* AOM FGS needs an exact match for the chroma resolution */
            ਜੇ (fgp->subsampling_x != desc->log2_chroma_w ||
                fgp->subsampling_y != desc->log2_chroma_h)
                ਜਾਰੀ;
            ਰੋਕੋ;
        ਹਾਲਤ AV_FILM_GRAIN_PARAMS_H274:
            /* H.274 FGS can be adapted to any lower chroma resolution */
            ਜੇ (fgp->subsampling_x > desc->log2_chroma_w ||
                fgp->subsampling_y > desc->log2_chroma_h)
                ਜਾਰੀ;
            ਰੋਕੋ;
        }

        ਜੇ (!ਉੱਤਮ || ਉੱਤਮ->ਚੌੜਾਈ < fgp->ਚੌੜਾਈ || ਉੱਤਮ->ਉਚਾਈ < fgp->ਉਚਾਈ)
            ਉੱਤਮ = fgp;
    }

    ਵਾਪਸ ਉੱਤਮ;
}
