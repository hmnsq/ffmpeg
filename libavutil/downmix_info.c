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

#অন্তর্ভাৱ "downmix_info.h"
#অন্তর্ভাৱ "frame.h"
#অন্তর্ভাৱ "mem.h"

AVDownmixInfo *av_downmix_info_update_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data;

    side_data = av_frame_get_side_data(frame, AV_FRAME_DATA_DOWNMIX_INFO);

    যদি (!side_data) {
        side_data = av_frame_new_side_data(frame, AV_FRAME_DATA_DOWNMIX_INFO,
                                           পরিমাণ(AVDownmixInfo));
        যদি (side_data)
            memset(side_data->data, 0, পরিমাণ(AVDownmixInfo));
    }

    যদি (!side_data)
        ঘূৰাই রিক্ত;

    ঘূৰাই (AVDownmixInfo*)side_data->data;
}

#define MAX_CHANNELS 64

স্থির ধ্রুৱ পূর্ণাঙ্ক type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmixMatrix *av_downmix_matrix_alloc(গণনা AVDownmixType type,
                                         পূর্ণাঙ্ক in_ch_গুনতি, size_t *out_size)
{
    সংরচনা TestStruct {
        AVDownmixMatrix p;
        AVDownmixCoeff  b;
    };
    ধ্রুৱ size_t coeffs_offset = offsetof(সংরচনা TestStruct, b);
    size_t size = coeffs_offset;
    unsigned পূর্ণাঙ্ক nb_coeffs;
    AVDownmixMatrix *dc;

    যদি ((unsigned)type >= FF_ARRAY_ELEMS(type_map) ||
        (unsigned)in_ch_গুনতি > MAX_CHANNELS)
        ঘূৰাই রিক্ত;

    nb_coeffs = type_map[type] * in_ch_গুনতি;
    size += পরিমাণ(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(size);
    যদি (!dc)
        ঘূৰাই রিক্ত;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->in_ch_গুনতি   = in_ch_গুনতি;
    dc->coeffs_offset = coeffs_offset;

    যদি (out_size)
        *out_size = size;

    ঘূৰাই dc;
}
