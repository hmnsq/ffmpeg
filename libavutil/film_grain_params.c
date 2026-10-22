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

#شامل "film_grain_params.h"
#شامل "mem.h"
#شامل "pixdesc.h"

AVFilmGrainParams *av_film_grain_params_alloc(size_t *سائز)
{
    AVFilmGrainParams *params = av_mallocz(حجم(AVFilmGrainParams));

    اگر (سائز)
        *سائز = params ? حجم(*params) : 0;

    واپس params;
}

AVFilmGrainParams *av_film_grain_params_create_side_ڈیٹا(AVFrame *چوکھٹا)
{
    AVFilmGrainParams *fgp;
    AVFrame_Side_ڈیٹا *side_ڈیٹا = av_چوکھٹا_new_side_ڈیٹا(چوکھٹا,
                                                        AV_چوکھٹا_ڈیٹا_FILM_GRAIN_PARAMS,
                                                        حجم(AVFilmGrainParams));
    اگر (!side_ڈیٹا)
        واپس تہی;

    fgp = (AVFilmGrainParams *) side_ڈیٹا->ڈیٹا;
    *fgp = (AVFilmGrainParams) {
        .color_range     = AVCOL_RANGE_UNSPECIFIED,
        .color_primaries = AVCOL_PRI_UNSPECIFIED,
        .color_trc       = AVCOL_TRC_UNSPECIFIED,
        .color_space     = AVCOL_SPC_UNSPECIFIED,
    };

    واپس fgp;
}

ثابت AVFilmGrainParams *av_film_grain_params_select(ثابت AVFrame *چوکھٹا)
{
    ثابت AVFilmGrainParams *fgp, *بہترین = تہی;
    ثابت AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(چوکھٹا->format);
    صحیح ثنائی_ہندسہ_گہرائی_luma, ثنائی_ہندسہ_گہرائی_chroma;
    اگر (!desc)
        واپس تہی;

    /* There are no YUV formats with different bit depth per component,
     * so just check both against the first component for simplicity */
    ثنائی_ہندسہ_گہرائی_luma = ثنائی_ہندسہ_گہرائی_chroma = desc->comp[0].گہرائی;

    برائے (صحیح i = 0; i < چوکھٹا->nb_side_ڈیٹا; i++) {
        اگر (چوکھٹا->side_ڈیٹا[i]->type != AV_چوکھٹا_ڈیٹا_FILM_GRAIN_PARAMS)
            جاری;
        fgp = (ثابت AVFilmGrainParams*)چوکھٹا->side_ڈیٹا[i]->ڈیٹا;
        اگر (fgp->چوڑائی  && fgp->چوڑائی  > چوکھٹا->چوڑائی ||
            fgp->اونچائی && fgp->اونچائی > چوکھٹا->اونچائی)
            جاری;

#تعریف_کرو CHECK(a, b, unspec)                                     \
        اگر ((a) != (unspec) && (b) != (unspec) && (a) != (b))   \
            جاری

        CHECK(fgp->ثنائی_ہندسہ_گہرائی_luma,   ثنائی_ہندسہ_گہرائی_luma,         0);
        CHECK(fgp->ثنائی_ہندسہ_گہرائی_chroma, ثنائی_ہندسہ_گہرائی_chroma,       0);
        CHECK(fgp->color_range,      چوکھٹا->color_range,     AVCOL_RANGE_UNSPECIFIED);
        CHECK(fgp->color_primaries,  چوکھٹا->color_primaries, AVCOL_PRI_UNSPECIFIED);
        CHECK(fgp->color_trc,        چوکھٹا->color_trc,       AVCOL_TRC_UNSPECIFIED);
        CHECK(fgp->color_space,      چوکھٹا->colorspace,      AVCOL_SPC_UNSPECIFIED);

        انتخاب (fgp->type) {
        حالت AV_FILM_GRAIN_PARAMS_NONE:
            جاری;
        حالت AV_FILM_GRAIN_PARAMS_AV1:
            /* AOM FGS needs an exact match for the chroma resolution */
            اگر (fgp->subsampling_x != desc->log2_chroma_w ||
                fgp->subsampling_y != desc->log2_chroma_h)
                جاری;
            توڑو;
        حالت AV_FILM_GRAIN_PARAMS_H274:
            /* H.274 FGS can be adapted to any lower chroma resolution */
            اگر (fgp->subsampling_x > desc->log2_chroma_w ||
                fgp->subsampling_y > desc->log2_chroma_h)
                جاری;
            توڑو;
        }

        اگر (!بہترین || بہترین->چوڑائی < fgp->چوڑائی || بہترین->اونچائی < fgp->اونچائی)
            بہترین = fgp;
    }

    واپس بہترین;
}
