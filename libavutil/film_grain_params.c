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

#ಅನ್ತರ್ಭಾವ "film_grain_params.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"

AVFilmGrainParams *av_film_grain_params_alloc(size_t *ಗಾತ್ರ_2)
{
    AVFilmGrainParams *params = av_mallocz(ಗಾತ್ರ(AVFilmGrainParams));

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = params ? ಗಾತ್ರ(*params) : 0;

    ಹಿಂತಿರುಗಿ params;
}

AVFilmGrainParams *av_film_grain_params_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು)
{
    AVFilmGrainParams *fgp;
    AVFrame_Side_ದತ್ತಾಂಶ *side_ದತ್ತಾಂಶ = av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು,
                                                        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_FILM_GRAIN_PARAMS,
                                                        ಗಾತ್ರ(AVFilmGrainParams));
    ಆದರೆ (!side_ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    fgp = (AVFilmGrainParams *) side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ;
    *fgp = (AVFilmGrainParams) {
        .color_range     = AVCOL_RANGE_UNSPECIFIED,
        .color_primaries = AVCOL_PRI_UNSPECIFIED,
        .color_trc       = AVCOL_TRC_UNSPECIFIED,
        .color_space     = AVCOL_SPC_UNSPECIFIED,
    };

    ಹಿಂತಿರುಗಿ fgp;
}

ಸ್ಥಿರಾಂಕ AVFilmGrainParams *av_film_grain_params_select(ಸ್ಥಿರಾಂಕ AVFrame *ಚೌಕಟ್ಟು)
{
    ಸ್ಥಿರಾಂಕ AVFilmGrainParams *fgp, *ಉತ್ತಮ = ಖಾಲಿ;
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(ಚೌಕಟ್ಟು->format);
    ಪೂರ್ಣಾಂಕ ಬಿಟ್_ಆಳ_luma, ಬಿಟ್_ಆಳ_chroma;
    ಆದರೆ (!desc)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    /* There are no YUV formats with different bit depth per component,
     * so just check both against the first component for simplicity */
    ಬಿಟ್_ಆಳ_luma = ಬಿಟ್_ಆಳ_chroma = desc->comp[0].ಆಳ;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಚೌಕಟ್ಟು->nb_side_ದತ್ತಾಂಶ; i++) {
        ಆದರೆ (ಚೌಕಟ್ಟು->side_ದತ್ತಾಂಶ[i]->type != AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_FILM_GRAIN_PARAMS)
            ಮುಂದುವರಿ;
        fgp = (ಸ್ಥಿರಾಂಕ AVFilmGrainParams*)ಚೌಕಟ್ಟು->side_ದತ್ತಾಂಶ[i]->ದತ್ತಾಂಶ;
        ಆದರೆ (fgp->ಅಗಲ  && fgp->ಅಗಲ  > ಚೌಕಟ್ಟು->ಅಗಲ ||
            fgp->ಎತ್ತರ && fgp->ಎತ್ತರ > ಚೌಕಟ್ಟು->ಎತ್ತರ)
            ಮುಂದುವರಿ;

#ವ್ಯಾಖ್ಯಾನಿಸು CHECK(a, b, unspec)                                     \
        ಆದರೆ ((a) != (unspec) && (b) != (unspec) && (a) != (b))   \
            ಮುಂದುವರಿ

        CHECK(fgp->ಬಿಟ್_ಆಳ_luma,   ಬಿಟ್_ಆಳ_luma,         0);
        CHECK(fgp->ಬಿಟ್_ಆಳ_chroma, ಬಿಟ್_ಆಳ_chroma,       0);
        CHECK(fgp->color_range,      ಚೌಕಟ್ಟು->color_range,     AVCOL_RANGE_UNSPECIFIED);
        CHECK(fgp->color_primaries,  ಚೌಕಟ್ಟು->color_primaries, AVCOL_PRI_UNSPECIFIED);
        CHECK(fgp->color_trc,        ಚೌಕಟ್ಟು->color_trc,       AVCOL_TRC_UNSPECIFIED);
        CHECK(fgp->color_space,      ಚೌಕಟ್ಟು->colorspace,      AVCOL_SPC_UNSPECIFIED);

        ಆಯ್ಕೆ (fgp->type) {
        ಸ್ಥಿತಿ AV_FILM_GRAIN_PARAMS_NONE:
            ಮುಂದುವರಿ;
        ಸ್ಥಿತಿ AV_FILM_GRAIN_PARAMS_AV1:
            /* AOM FGS needs an exact match for the chroma resolution */
            ಆದರೆ (fgp->subsampling_x != desc->log2_chroma_w ||
                fgp->subsampling_y != desc->log2_chroma_h)
                ಮುಂದುವರಿ;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ AV_FILM_GRAIN_PARAMS_H274:
            /* H.274 FGS can be adapted to any lower chroma resolution */
            ಆದರೆ (fgp->subsampling_x > desc->log2_chroma_w ||
                fgp->subsampling_y > desc->log2_chroma_h)
                ಮುಂದುವರಿ;
            ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (!ಉತ್ತಮ || ಉತ್ತಮ->ಅಗಲ < fgp->ಅಗಲ || ಉತ್ತಮ->ಎತ್ತರ < fgp->ಎತ್ತರ)
            ಉತ್ತಮ = fgp;
    }

    ಹಿಂತಿರುಗಿ ಉತ್ತಮ;
}
