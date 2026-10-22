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

#অন্তর্ভাব "film_grain_params.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "pixdesc.h"

AVFilmGrainParams *av_film_grain_params_alloc(size_t *আকার_2)
{
    AVFilmGrainParams *params = av_mallocz(আকার(AVFilmGrainParams));

    যদি (আকার_2)
        *আকার_2 = params ? আকার(*params) : 0;

    ফেরত params;
}

AVFilmGrainParams *av_film_grain_params_create_side_তথ্য(AVFrame *frame)
{
    AVFilmGrainParams *fgp;
    AVFrame_Side_তথ্য *side_তথ্য = av_frame_new_side_তথ্য(frame,
                                                        AV_FRAME_তথ্য_FILM_GRAIN_PARAMS,
                                                        আকার(AVFilmGrainParams));
    যদি (!side_তথ্য)
        ফেরত ফাঁকা;

    fgp = (AVFilmGrainParams *) side_তথ্য->তথ্য;
    *fgp = (AVFilmGrainParams) {
        .color_range     = AVCOL_RANGE_UNSPECIFIED,
        .color_primaries = AVCOL_PRI_UNSPECIFIED,
        .color_trc       = AVCOL_TRC_UNSPECIFIED,
        .color_space     = AVCOL_SPC_UNSPECIFIED,
    };

    ফেরত fgp;
}

ধ্রুবক AVFilmGrainParams *av_film_grain_params_select(ধ্রুবক AVFrame *frame)
{
    ধ্রুবক AVFilmGrainParams *fgp, *best = ফাঁকা;
    ধ্রুবক AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(frame->format);
    পূর্ণসংখ্যা bit_depth_luma, bit_depth_chroma;
    যদি (!desc)
        ফেরত ফাঁকা;

    /* There are no YUV formats with different bit depth per component,
     * so just check both against the first component for simplicity */
    bit_depth_luma = bit_depth_chroma = desc->comp[0].depth;

    জন্য (পূর্ণসংখ্যা i = 0; i < frame->nb_side_তথ্য; i++) {
        যদি (frame->side_তথ্য[i]->type != AV_FRAME_তথ্য_FILM_GRAIN_PARAMS)
            চালু;
        fgp = (ধ্রুবক AVFilmGrainParams*)frame->side_তথ্য[i]->তথ্য;
        যদি (fgp->width  && fgp->width  > frame->width ||
            fgp->height && fgp->height > frame->height)
            চালু;

#define CHECK(a, b, unspec)                                     \
        যদি ((a) != (unspec) && (b) != (unspec) && (a) != (b))   \
            চালু

        CHECK(fgp->bit_depth_luma,   bit_depth_luma,         0);
        CHECK(fgp->bit_depth_chroma, bit_depth_chroma,       0);
        CHECK(fgp->color_range,      frame->color_range,     AVCOL_RANGE_UNSPECIFIED);
        CHECK(fgp->color_primaries,  frame->color_primaries, AVCOL_PRI_UNSPECIFIED);
        CHECK(fgp->color_trc,        frame->color_trc,       AVCOL_TRC_UNSPECIFIED);
        CHECK(fgp->color_space,      frame->colorspace,      AVCOL_SPC_UNSPECIFIED);

        নির্বাচন (fgp->type) {
        ক্ষেত্র AV_FILM_GRAIN_PARAMS_NONE:
            চালু;
        ক্ষেত্র AV_FILM_GRAIN_PARAMS_AV1:
            /* AOM FGS needs an exact match for the chroma resolution */
            যদি (fgp->subsampling_x != desc->log2_chroma_w ||
                fgp->subsampling_y != desc->log2_chroma_h)
                চালু;
            বিরতি;
        ক্ষেত্র AV_FILM_GRAIN_PARAMS_H274:
            /* H.274 FGS can be adapted to any lower chroma resolution */
            যদি (fgp->subsampling_x > desc->log2_chroma_w ||
                fgp->subsampling_y > desc->log2_chroma_h)
                চালু;
            বিরতি;
        }

        যদি (!best || best->width < fgp->width || best->height < fgp->height)
            best = fgp;
    }

    ফেরত best;
}
