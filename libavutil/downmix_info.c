/*
 * Copyright (c) 2014 Tim Walker <tdskywalker@gmail.com>
 *
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

#অন্তর্ভাব "downmix_info.h"
#অন্তর্ভাব "frame.h"
#অন্তর্ভাব "mem.h"

AVDownmixInfo *av_downmix_info_update_side_তথ্য(AVFrame *frame)
{
    AVFrame_Side_তথ্য *side_তথ্য;

    side_তথ্য = av_frame_get_side_তথ্য(frame, AV_FRAME_তথ্য_DOWNMIX_INFO);

    যদি (!side_তথ্য) {
        side_তথ্য = av_frame_new_side_তথ্য(frame, AV_FRAME_তথ্য_DOWNMIX_INFO,
                                           আকার(AVDownmixInfo));
        যদি (side_তথ্য)
            memset(side_তথ্য->তথ্য, 0, আকার(AVDownmixInfo));
    }

    যদি (!side_তথ্য)
        ফেরত ফাঁকা;

    ফেরত (AVDownmixInfo*)side_তথ্য->তথ্য;
}

#define MAX_CHANNELS 64

স্থির ধ্রুবক পূর্ণসংখ্যা type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmixMatrix *av_downmix_matrix_alloc(গণনা AVDownmixType type,
                                         পূর্ণসংখ্যা in_ch_গুনতি, size_t *out_আকার)
{
    কাঠামো TestStruct {
        AVDownmixMatrix p;
        AVDownmixCoeff  b;
    };
    ধ্রুবক size_t coeffs_offset = offsetof(কাঠামো TestStruct, b);
    size_t আকার_2 = coeffs_offset;
    unsigned পূর্ণসংখ্যা nb_coeffs;
    AVDownmixMatrix *dc;

    যদি ((unsigned)type >= FF_ARRAY_ELEMS(type_map) ||
        (unsigned)in_ch_গুনতি > MAX_CHANNELS)
        ফেরত ফাঁকা;

    nb_coeffs = type_map[type] * in_ch_গুনতি;
    আকার_2 += আকার(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(আকার_2);
    যদি (!dc)
        ফেরত ফাঁকা;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->in_ch_গুনতি   = in_ch_গুনতি;
    dc->coeffs_offset = coeffs_offset;

    যদি (out_আকার)
        *out_আকার = আকার_2;

    ফেরত dc;
}
