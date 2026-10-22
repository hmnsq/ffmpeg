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

#అన్తర్భావ "film_grain_params.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pixdesc.h"

AVFilmGrainParams *av_film_grain_params_alloc(size_t *కొలత)
{
    AVFilmGrainParams *params = av_mallocz(పరిమాణం(AVFilmGrainParams));

    ఒకవేళ (కొలత)
        *కొలత = params ? పరిమాణం(*params) : 0;

    తిరిగి params;
}

AVFilmGrainParams *av_film_grain_params_create_side_దత్తాంశం(AVFrame *చట్రం)
{
    AVFilmGrainParams *fgp;
    AVFrame_Side_దత్తాంశం *side_దత్తాంశం = av_చట్రం_new_side_దత్తాంశం(చట్రం,
                                                        AV_చట్రం_దత్తాంశం_FILM_GRAIN_PARAMS,
                                                        పరిమాణం(AVFilmGrainParams));
    ఒకవేళ (!side_దత్తాంశం)
        తిరిగి ఖాళీ;

    fgp = (AVFilmGrainParams *) side_దత్తాంశం->దత్తాంశం;
    *fgp = (AVFilmGrainParams) {
        .color_range     = AVCOL_RANGE_UNSPECIFIED,
        .color_primaries = AVCOL_PRI_UNSPECIFIED,
        .color_trc       = AVCOL_TRC_UNSPECIFIED,
        .color_space     = AVCOL_SPC_UNSPECIFIED,
    };

    తిరిగి fgp;
}

స్థిరరాశి AVFilmGrainParams *av_film_grain_params_select(స్థిరరాశి AVFrame *చట్రం)
{
    స్థిరరాశి AVFilmGrainParams *fgp, *ఉత్తమ = ఖాళీ;
    స్థిరరాశి AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(చట్రం->format);
    పూర్ణాంకం బిట్టు_లోతు_luma, బిట్టు_లోతు_chroma;
    ఒకవేళ (!desc)
        తిరిగి ఖాళీ;

    /* There are no YUV formats with different bit depth per component,
     * so just check both against the first component for simplicity */
    బిట్టు_లోతు_luma = బిట్టు_లోతు_chroma = desc->comp[0].లోతు;

    కొరకు (పూర్ణాంకం i = 0; i < చట్రం->nb_side_దత్తాంశం; i++) {
        ఒకవేళ (చట్రం->side_దత్తాంశం[i]->type != AV_చట్రం_దత్తాంశం_FILM_GRAIN_PARAMS)
            కొనసాగు;
        fgp = (స్థిరరాశి AVFilmGrainParams*)చట్రం->side_దత్తాంశం[i]->దత్తాంశం;
        ఒకవేళ (fgp->వెడల్పు  && fgp->వెడల్పు  > చట్రం->వెడల్పు ||
            fgp->ఎత్తు && fgp->ఎత్తు > చట్రం->ఎత్తు)
            కొనసాగు;

#నిర్వచించు CHECK(a, b, unspec)                                     \
        ఒకవేళ ((a) != (unspec) && (b) != (unspec) && (a) != (b))   \
            కొనసాగు

        CHECK(fgp->బిట్టు_లోతు_luma,   బిట్టు_లోతు_luma,         0);
        CHECK(fgp->బిట్టు_లోతు_chroma, బిట్టు_లోతు_chroma,       0);
        CHECK(fgp->color_range,      చట్రం->color_range,     AVCOL_RANGE_UNSPECIFIED);
        CHECK(fgp->color_primaries,  చట్రం->color_primaries, AVCOL_PRI_UNSPECIFIED);
        CHECK(fgp->color_trc,        చట్రం->color_trc,       AVCOL_TRC_UNSPECIFIED);
        CHECK(fgp->color_space,      చట్రం->colorspace,      AVCOL_SPC_UNSPECIFIED);

        ఎంపిక (fgp->type) {
        స్థితి AV_FILM_GRAIN_PARAMS_NONE:
            కొనసాగు;
        స్థితి AV_FILM_GRAIN_PARAMS_AV1:
            /* AOM FGS needs an exact match for the chroma resolution */
            ఒకవేళ (fgp->subsampling_x != desc->log2_chroma_w ||
                fgp->subsampling_y != desc->log2_chroma_h)
                కొనసాగు;
            ఆపు;
        స్థితి AV_FILM_GRAIN_PARAMS_H274:
            /* H.274 FGS can be adapted to any lower chroma resolution */
            ఒకవేళ (fgp->subsampling_x > desc->log2_chroma_w ||
                fgp->subsampling_y > desc->log2_chroma_h)
                కొనసాగు;
            ఆపు;
        }

        ఒకవేళ (!ఉత్తమ || ఉత్తమ->వెడల్పు < fgp->వెడల్పు || ఉత్తమ->ఎత్తు < fgp->ఎత్తు)
            ఉత్తమ = fgp;
    }

    తిరిగి ఉత్తమ;
}
