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

#अन्तर्भाव "film_grain_params.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixdesc.h"

AVFilmGrainParams *av_film_grain_params_alloc(size_t *आकार)
{
    AVFilmGrainParams *params = av_mallocz(परिमाण(AVFilmGrainParams));

    यदि (आकार)
        *आकार = params ? परिमाण(*params) : 0;

    प्रत्यागम params;
}

AVFilmGrainParams *av_film_grain_params_create_side_दत्त(AVFrame *frame)
{
    AVFilmGrainParams *fgp;
    AVFrame_Side_दत्त *side_दत्त = av_frame_new_side_दत्त(frame,
                                                        AV_FRAME_दत्त_FILM_GRAIN_PARAMS,
                                                        परिमाण(AVFilmGrainParams));
    यदि (!side_दत्त)
        प्रत्यागम रिक्त;

    fgp = (AVFilmGrainParams *) side_दत्त->दत्त;
    *fgp = (AVFilmGrainParams) {
        .color_range     = AVCOL_RANGE_UNSPECIFIED,
        .color_primaries = AVCOL_PRI_UNSPECIFIED,
        .color_trc       = AVCOL_TRC_UNSPECIFIED,
        .color_space     = AVCOL_SPC_UNSPECIFIED,
    };

    प्रत्यागम fgp;
}

ध्रुव AVFilmGrainParams *av_film_grain_params_select(ध्रुव AVFrame *frame)
{
    ध्रुव AVFilmGrainParams *fgp, *best = रिक्त;
    ध्रुव AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    पूर्णाङ्क bit_गभीरता_luma, bit_गभीरता_chroma;
    यदि (!desc)
        प्रत्यागम रिक्त;

    /* There are no YUV formats with different bit depth per component,
     * so just check both against the first component for simplicity */
    bit_गभीरता_luma = bit_गभीरता_chroma = desc->comp[0].गभीरता;

    प्रति (पूर्णाङ्क i = 0; i < frame->nb_side_दत्त; i++) {
        यदि (frame->side_दत्त[i]->type != AV_FRAME_दत्त_FILM_GRAIN_PARAMS)
            अनुवर्त;
        fgp = (ध्रुव AVFilmGrainParams*)frame->side_दत्त[i]->दत्त;
        यदि (fgp->विस्तारः  && fgp->विस्तारः  > frame->विस्तारः ||
            fgp->height && fgp->height > frame->height)
            अनुवर्त;

#परिभाषय CHECK(a, b, unspec)                                     \
        यदि ((a) != (unspec) && (b) != (unspec) && (a) != (b))   \
            अनुवर्त

        CHECK(fgp->bit_गभीरता_luma,   bit_गभीरता_luma,         0);
        CHECK(fgp->bit_गभीरता_chroma, bit_गभीरता_chroma,       0);
        CHECK(fgp->color_range,      frame->color_range,     AVCOL_RANGE_UNSPECIFIED);
        CHECK(fgp->color_primaries,  frame->color_primaries, AVCOL_PRI_UNSPECIFIED);
        CHECK(fgp->color_trc,        frame->color_trc,       AVCOL_TRC_UNSPECIFIED);
        CHECK(fgp->color_space,      frame->colorspace,      AVCOL_SPC_UNSPECIFIED);

        विकल्प (fgp->type) {
        पक्ष AV_FILM_GRAIN_PARAMS_NONE:
            अनुवर्त;
        पक्ष AV_FILM_GRAIN_PARAMS_AV1:
            /* AOM FGS needs an exact match for the chroma resolution */
            यदि (fgp->subsampling_x != desc->log2_chroma_w ||
                fgp->subsampling_y != desc->log2_chroma_h)
                अनुवर्त;
            भङ्ग;
        पक्ष AV_FILM_GRAIN_PARAMS_H274:
            /* H.274 FGS can be adapted to any lower chroma resolution */
            यदि (fgp->subsampling_x > desc->log2_chroma_w ||
                fgp->subsampling_y > desc->log2_chroma_h)
                अनुवर्त;
            भङ्ग;
        }

        यदि (!best || best->विस्तारः < fgp->विस्तारः || best->height < fgp->height)
            best = fgp;
    }

    प्रत्यागम best;
}
