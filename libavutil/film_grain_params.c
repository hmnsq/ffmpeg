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

AVFilmGrainParams *av_film_grain_params_alloc(size_t *ناپ)
{
    AVFilmGrainParams *params = av_mallocz(حجم(AVFilmGrainParams));

    إذا (ناپ)
        *ناپ = params ? حجم(*params) : 0;

    أرجع params;
}

AVFilmGrainParams *av_film_grain_params_create_side_انکڑے(AVFrame *چوکھٹا)
{
    AVFilmGrainParams *fgp;
    AVFrame_Side_انکڑے *side_انکڑے = av_چوکھٹا_new_side_انکڑے(چوکھٹا,
                                                        AV_چوکھٹا_انکڑے_FILM_GRAIN_PARAMS,
                                                        حجم(AVFilmGrainParams));
    إذا (!side_انکڑے)
        أرجع عدم;

    fgp = (AVFilmGrainParams *) side_انکڑے->انکڑے;
    *fgp = (AVFilmGrainParams) {
        .color_range     = AVCOL_RANGE_UNSPECIFIED,
        .color_primaries = AVCOL_PRI_UNSPECIFIED,
        .color_trc       = AVCOL_TRC_UNSPECIFIED,
        .color_space     = AVCOL_SPC_UNSPECIFIED,
    };

    أرجع fgp;
}

ثابت AVFilmGrainParams *av_film_grain_params_select(ثابت AVFrame *چوکھٹا)
{
    ثابت AVFilmGrainParams *fgp, *بہترین = عدم;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(چوکھٹا->format);
    صحيح ثنائی_ہندسہ_ڈونگھائی_luma, ثنائی_ہندسہ_ڈونگھائی_chroma;
    إذا (!desc)
        أرجع عدم;

    /* There are no YUV formats with different bit depth per component,
     * so just check both against the first component for simplicity */
    ثنائی_ہندسہ_ڈونگھائی_luma = ثنائی_ہندسہ_ڈونگھائی_chroma = desc->comp[0].ڈونگھائی;

    لكل (صحيح i = 0; i < چوکھٹا->nb_side_انکڑے; i++) {
        إذا (چوکھٹا->side_انکڑے[i]->type != AV_چوکھٹا_انکڑے_FILM_GRAIN_PARAMS)
            استمر;
        fgp = (ثابت AVFilmGrainParams*)چوکھٹا->side_انکڑے[i]->انکڑے;
        إذا (fgp->چوڑائی  && fgp->چوڑائی  > چوکھٹا->چوڑائی ||
            fgp->اچائی && fgp->اچائی > چوکھٹا->اچائی)
            استمر;

#تعریف_کرو CHECK(a, b, unspec)                                     \
        إذا ((a) != (unspec) && (b) != (unspec) && (a) != (b))   \
            استمر

        CHECK(fgp->ثنائی_ہندسہ_ڈونگھائی_luma,   ثنائی_ہندسہ_ڈونگھائی_luma,         0);
        CHECK(fgp->ثنائی_ہندسہ_ڈونگھائی_chroma, ثنائی_ہندسہ_ڈونگھائی_chroma,       0);
        CHECK(fgp->color_range,      چوکھٹا->color_range,     AVCOL_RANGE_UNSPECIFIED);
        CHECK(fgp->color_primaries,  چوکھٹا->color_primaries, AVCOL_PRI_UNSPECIFIED);
        CHECK(fgp->color_trc,        چوکھٹا->color_trc,       AVCOL_TRC_UNSPECIFIED);
        CHECK(fgp->color_space,      چوکھٹا->colorspace,      AVCOL_SPC_UNSPECIFIED);

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

        إذا (!بہترین || بہترین->چوڑائی < fgp->چوڑائی || بہترین->اچائی < fgp->اچائی)
            بہترین = fgp;
    }

    أرجع بہترین;
}
