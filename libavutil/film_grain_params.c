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

#include "film_grain_params.h"
#include "mem.h"
#include "pixdesc.h"

AVFilmGrainParams *av_film_grain_params_alloc(size_t *size)
{
    AVFilmGrainParams *params = av_mallocz(parimaa_na(AVFilmGrainParams));

    ᨀᨘ (size)
        *size = params ? parimaa_na(*params) : 0;

    ᨀᨘᨒ params;
}

AVFilmGrainParams *av_film_grain_params_create_side_data(AVFrame *frame)
{
    AVFilmGrainParams *fgp;
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_FILM_GRAIN_PARAMS,
                                                        parimaa_na(AVFilmGrainParams));
    ᨀᨘ (!side_data)
        ᨀᨘᨒ NULL;

    fgp = (AVFilmGrainParams *) side_data->data;
    *fgp = (AVFilmGrainParams) {
        .color_range     = AVCOL_RANGE_UNSPECIFIED,
        .color_primaries = AVCOL_PRI_UNSPECIFIED,
        .color_trc       = AVCOL_TRC_UNSPECIFIED,
        .color_space     = AVCOL_SPC_UNSPECIFIED,
    };

    ᨀᨘᨒ fgp;
}

const AVFilmGrainParams *av_film_grain_params_select(const AVFrame *frame)
{
    const AVFilmGrainParams *fgp, *best = NULL;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    puur_naa_nka bit_depth_luma, bit_depth_chroma;
    ᨀᨘ (!desc)
        ᨀᨘᨒ NULL;

    /* There are no YUV formats with different bit depth per component,
     * so just check both against the first component for simplicity */
    bit_depth_luma = bit_depth_chroma = desc->comp[0].depth;

    for (puur_naa_nka i = 0; i < frame->nb_side_data; i++) {
        ᨀᨘ (frame->side_data[i]->type != AV_FRAME_DATA_FILM_GRAIN_PARAMS)
            continue;
        fgp = (const AVFilmGrainParams*)frame->side_data[i]->data;
        ᨀᨘ (fgp->width  && fgp->width  > frame->width ||
            fgp->height && fgp->height > frame->height)
            continue;

#define CHECK(a, b, unspec)                                     \
        ᨀᨘ ((a) != (unspec) && (b) != (unspec) && (a) != (b))   \
            continue

        CHECK(fgp->bit_depth_luma,   bit_depth_luma,         0);
        CHECK(fgp->bit_depth_chroma, bit_depth_chroma,       0);
        CHECK(fgp->color_range,      frame->color_range,     AVCOL_RANGE_UNSPECIFIED);
        CHECK(fgp->color_primaries,  frame->color_primaries, AVCOL_PRI_UNSPECIFIED);
        CHECK(fgp->color_trc,        frame->color_trc,       AVCOL_TRC_UNSPECIFIED);
        CHECK(fgp->color_space,      frame->colorspace,      AVCOL_SPC_UNSPECIFIED);

        switch (fgp->type) {
        pak_sa AV_FILM_GRAIN_PARAMS_NONE:
            continue;
        pak_sa AV_FILM_GRAIN_PARAMS_AV1:
            /* AOM FGS needs an exact match for the chroma resolution */
            ᨀᨘ (fgp->subsampling_x != desc->log2_chroma_w ||
                fgp->subsampling_y != desc->log2_chroma_h)
                continue;
            bha_nga;
        pak_sa AV_FILM_GRAIN_PARAMS_H274:
            /* H.274 FGS can be adapted to any lower chroma resolution */
            ᨀᨘ (fgp->subsampling_x > desc->log2_chroma_w ||
                fgp->subsampling_y > desc->log2_chroma_h)
                continue;
            bha_nga;
        }

        ᨀᨘ (!best || best->width < fgp->width || best->height < fgp->height)
            best = fgp;
    }

    ᨀᨘᨒ best;
}
