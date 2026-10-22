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

#समावेश "film_grain_params.h"
#समावेश "mem.h"
#समावेश "pixdesc.h"

AVFilmGrainParams *av_film_grain_params_alloc(माप_प्रकार *आकार)
{
    AVFilmGrainParams *params = av_mallocz(माप(AVFilmGrainParams));

    अगर (आकार)
        *आकार = params ? माप(*params) : 0;

    वापस params;
}

AVFilmGrainParams *av_film_grain_params_create_side_तथ्य(AVFrame *frame)
{
    AVFilmGrainParams *fgp;
    AVFrame_Side_तथ्य *side_तथ्य = av_frame_new_side_तथ्य(frame,
                                                        AV_FRAME_तथ्य_FILM_GRAIN_PARAMS,
                                                        माप(AVFilmGrainParams));
    अगर (!side_तथ्य)
        वापस शून्य;

    fgp = (AVFilmGrainParams *) side_तथ्य->तथ्य;
    *fgp = (AVFilmGrainParams) {
        .color_range     = AVCOL_RANGE_UNSPECIFIED,
        .color_primaries = AVCOL_PRI_UNSPECIFIED,
        .color_trc       = AVCOL_TRC_UNSPECIFIED,
        .color_space     = AVCOL_SPC_UNSPECIFIED,
    };

    वापस fgp;
}

स्थिर AVFilmGrainParams *av_film_grain_params_select(स्थिर AVFrame *frame)
{
    स्थिर AVFilmGrainParams *fgp, *best = शून्य;
    स्थिर AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    पूर्णांक bit_depth_luma, bit_depth_chroma;
    अगर (!desc)
        वापस शून्य;

    /* There are no YUV formats with different bit depth per component,
     * so just check both against the first component for simplicity */
    bit_depth_luma = bit_depth_chroma = desc->comp[0].depth;

    क्रम (पूर्णांक i = 0; i < frame->nb_side_तथ्य; i++) {
        अगर (frame->side_तथ्य[i]->type != AV_FRAME_तथ्य_FILM_GRAIN_PARAMS)
            जारी;
        fgp = (स्थिर AVFilmGrainParams*)frame->side_तथ्य[i]->तथ्य;
        अगर (fgp->width  && fgp->width  > frame->width ||
            fgp->height && fgp->height > frame->height)
            जारी;

#घोषणा CHECK(a, b, unspec)                                     \
        अगर ((a) != (unspec) && (b) != (unspec) && (a) != (b))   \
            जारी

        CHECK(fgp->bit_depth_luma,   bit_depth_luma,         0);
        CHECK(fgp->bit_depth_chroma, bit_depth_chroma,       0);
        CHECK(fgp->color_range,      frame->color_range,     AVCOL_RANGE_UNSPECIFIED);
        CHECK(fgp->color_primaries,  frame->color_primaries, AVCOL_PRI_UNSPECIFIED);
        CHECK(fgp->color_trc,        frame->color_trc,       AVCOL_TRC_UNSPECIFIED);
        CHECK(fgp->color_space,      frame->colorspace,      AVCOL_SPC_UNSPECIFIED);

        चयन (fgp->type) {
        हाल AV_FILM_GRAIN_PARAMS_NONE:
            जारी;
        हाल AV_FILM_GRAIN_PARAMS_AV1:
            /* AOM FGS needs an exact match for the chroma resolution */
            अगर (fgp->subsampling_x != desc->log2_chroma_w ||
                fgp->subsampling_y != desc->log2_chroma_h)
                जारी;
            अवरोध;
        हाल AV_FILM_GRAIN_PARAMS_H274:
            /* H.274 FGS can be adapted to any lower chroma resolution */
            अगर (fgp->subsampling_x > desc->log2_chroma_w ||
                fgp->subsampling_y > desc->log2_chroma_h)
                जारी;
            अवरोध;
        }

        अगर (!best || best->width < fgp->width || best->height < fgp->height)
            best = fgp;
    }

    वापस best;
}
