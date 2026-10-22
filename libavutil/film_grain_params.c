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

#ضمن "film_grain_params.h"
#ضمن "mem.h"
#ضمن "pixdesc.h"

AVFilmGrainParams *av_film_grain_params_alloc(size_t *اندازه)
{
    AVFilmGrainParams *params = av_mallocz(حجم(AVFilmGrainParams));

    إذا (اندازه)
        *اندازه = params ? حجم(*params) : 0;

    أرجع params;
}

AVFilmGrainParams *av_film_grain_params_create_side_معلومات(AVFrame *چوکاټ)
{
    AVFilmGrainParams *fgp;
    AVFrame_Side_معلومات *side_معلومات = av_چوکاټ_new_side_معلومات(چوکاټ,
                                                        AV_چوکاټ_معلومات_FILM_GRAIN_PARAMS,
                                                        حجم(AVFilmGrainParams));
    إذا (!side_معلومات)
        أرجع عدم;

    fgp = (AVFilmGrainParams *) side_معلومات->معلومات;
    *fgp = (AVFilmGrainParams) {
        .color_range     = AVCOL_RANGE_UNSPECIFIED,
        .color_primaries = AVCOL_PRI_UNSPECIFIED,
        .color_trc       = AVCOL_TRC_UNSPECIFIED,
        .color_space     = AVCOL_SPC_UNSPECIFIED,
    };

    أرجع fgp;
}

ثابت AVFilmGrainParams *av_film_grain_params_select(ثابت AVFrame *چوکاټ)
{
    ثابت AVFilmGrainParams *fgp, *غوره = عدم;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(چوکاټ->format);
    صحيح بټ_ژوروالی_luma, بټ_ژوروالی_chroma;
    إذا (!desc)
        أرجع عدم;

    /* There are no YUV formats with different bit depth per component,
     * so just check both against the first component for simplicity */
    بټ_ژوروالی_luma = بټ_ژوروالی_chroma = desc->comp[0].ژوروالی;

    لكل (صحيح i = 0; i < چوکاټ->nb_side_معلومات; i++) {
        إذا (چوکاټ->side_معلومات[i]->type != AV_چوکاټ_معلومات_FILM_GRAIN_PARAMS)
            استمر;
        fgp = (ثابت AVFilmGrainParams*)چوکاټ->side_معلومات[i]->معلومات;
        إذا (fgp->پلنوالی  && fgp->پلنوالی  > چوکاټ->پلنوالی ||
            fgp->لوړوالی && fgp->لوړوالی > چوکاټ->لوړوالی)
            استمر;

#تعریف_کړه CHECK(a, b, unspec)                                     \
        إذا ((a) != (unspec) && (b) != (unspec) && (a) != (b))   \
            استمر

        CHECK(fgp->بټ_ژوروالی_luma,   بټ_ژوروالی_luma,         0);
        CHECK(fgp->بټ_ژوروالی_chroma, بټ_ژوروالی_chroma,       0);
        CHECK(fgp->color_range,      چوکاټ->color_range,     AVCOL_RANGE_UNSPECIFIED);
        CHECK(fgp->color_primaries,  چوکاټ->color_primaries, AVCOL_PRI_UNSPECIFIED);
        CHECK(fgp->color_trc,        چوکاټ->color_trc,       AVCOL_TRC_UNSPECIFIED);
        CHECK(fgp->color_space,      چوکاټ->colorspace,      AVCOL_SPC_UNSPECIFIED);

        بدل (fgp->type) {
        حالة AV_FILM_GRAIN_PARAMS_NONE:
            استمر;
        حالة AV_FILM_GRAIN_PARAMS_AV1:
            /* AOM FGS needs an exact match for the chroma resolution */
            إذا (fgp->subsampling_x != desc->log2_chroma_w ||
                fgp->subsampling_y != desc->log2_chroma_h)
                استمر;
            اكسر;
        حالة AV_FILM_GRAIN_PARAMS_H274:
            /* H.274 FGS can be adapted to any lower chroma resolution */
            إذا (fgp->subsampling_x > desc->log2_chroma_w ||
                fgp->subsampling_y > desc->log2_chroma_h)
                استمر;
            اكسر;
        }

        إذا (!غوره || غوره->پلنوالی < fgp->پلنوالی || غوره->لوړوالی < fgp->لوړوالی)
            غوره = fgp;
    }

    أرجع غوره;
}
