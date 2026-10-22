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

#ଅନ୍ତର୍ଭାଵ "film_grain_params.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"

AVFilmGrainParams *av_film_grain_params_alloc(size_t *size)
{
    AVFilmGrainParams *params = av_mallocz(ଆକାର(AVFilmGrainParams));

    ଯଦି (size)
        *size = params ? ଆକାର(*params) : 0;

    ଫେରନ୍ତୁ params;
}

AVFilmGrainParams *av_film_grain_params_create_side_data(AVFrame *frame)
{
    AVFilmGrainParams *fgp;
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_FILM_GRAIN_PARAMS,
                                                        ଆକାର(AVFilmGrainParams));
    ଯଦି (!side_data)
        ଫେରନ୍ତୁ ଖାଲି;

    fgp = (AVFilmGrainParams *) side_data->data;
    *fgp = (AVFilmGrainParams) {
        .color_range     = AVCOL_RANGE_UNSPECIFIED,
        .color_primaries = AVCOL_PRI_UNSPECIFIED,
        .color_trc       = AVCOL_TRC_UNSPECIFIED,
        .color_space     = AVCOL_SPC_UNSPECIFIED,
    };

    ଫେରନ୍ତୁ fgp;
}

ଅଚଳ AVFilmGrainParams *av_film_grain_params_select(ଅଚଳ AVFrame *frame)
{
    ଅଚଳ AVFilmGrainParams *fgp, *best = ଖାଲି;
    ଅଚଳ AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା bit_depth_luma, bit_depth_chroma;
    ଯଦି (!desc)
        ଫେରନ୍ତୁ ଖାଲି;

    /* There are no YUV formats with different bit depth per component,
     * so just check both against the first component for simplicity */
    bit_depth_luma = bit_depth_chroma = desc->comp[0].depth;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < frame->nb_side_data; i++) {
        ଯଦି (frame->side_data[i]->type != AV_FRAME_DATA_FILM_GRAIN_PARAMS)
            ଜାରି;
        fgp = (ଅଚଳ AVFilmGrainParams*)frame->side_data[i]->data;
        ଯଦି (fgp->width  && fgp->width  > frame->width ||
            fgp->height && fgp->height > frame->height)
            ଜାରି;

#define CHECK(a, b, unspec)                                     \
        ଯଦି ((a) != (unspec) && (b) != (unspec) && (a) != (b))   \
            ଜାରି

        CHECK(fgp->bit_depth_luma,   bit_depth_luma,         0);
        CHECK(fgp->bit_depth_chroma, bit_depth_chroma,       0);
        CHECK(fgp->color_range,      frame->color_range,     AVCOL_RANGE_UNSPECIFIED);
        CHECK(fgp->color_primaries,  frame->color_primaries, AVCOL_PRI_UNSPECIFIED);
        CHECK(fgp->color_trc,        frame->color_trc,       AVCOL_TRC_UNSPECIFIED);
        CHECK(fgp->color_space,      frame->colorspace,      AVCOL_SPC_UNSPECIFIED);

        ବାଛ (fgp->type) {
        ସ୍ଥିତି AV_FILM_GRAIN_PARAMS_NONE:
            ଜାରି;
        ସ୍ଥିତି AV_FILM_GRAIN_PARAMS_AV1:
            /* AOM FGS needs an exact match for the chroma resolution */
            ଯଦି (fgp->subsampling_x != desc->log2_chroma_w ||
                fgp->subsampling_y != desc->log2_chroma_h)
                ଜାରି;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି AV_FILM_GRAIN_PARAMS_H274:
            /* H.274 FGS can be adapted to any lower chroma resolution */
            ଯଦି (fgp->subsampling_x > desc->log2_chroma_w ||
                fgp->subsampling_y > desc->log2_chroma_h)
                ଜାରି;
            ଭାଙ୍ଗ;
        }

        ଯଦି (!best || best->width < fgp->width || best->height < fgp->height)
            best = fgp;
    }

    ଫେରନ୍ତୁ best;
}
