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

#அந்தர்பாவ "downmix_info.h"
#அந்தர்பாவ "frame.h"
#அந்தர்பாவ "mem.h"

AVDownmixInfo *av_downmix_info_update_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data;

    side_data = av_frame_get_side_data(frame, AV_FRAME_DATA_DOWNMIX_INFO);

    எனில் (!side_data) {
        side_data = av_frame_new_side_data(frame, AV_FRAME_DATA_DOWNMIX_INFO,
                                           அளவு(AVDownmixInfo));
        எனில் (side_data)
            memset(side_data->data, 0, அளவு(AVDownmixInfo));
    }

    எனில் (!side_data)
        திரும்பு வெற்று;

    திரும்பு (AVDownmixInfo*)side_data->data;
}

#define MAX_CHANNELS 64

நிலையான மாறிலி முழு type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmixMatrix *av_downmix_matrix_alloc(எண்ணிக்கை AVDownmixType type,
                                         முழு in_ch_மொத்தம், size_t *out_size)
{
    கட்டமைப்பு TestStruct {
        AVDownmixMatrix p;
        AVDownmixCoeff  b;
    };
    மாறிலி size_t coeffs_offset = offsetof(கட்டமைப்பு TestStruct, b);
    size_t size = coeffs_offset;
    unsigned முழு nb_coeffs;
    AVDownmixMatrix *dc;

    எனில் ((unsigned)type >= FF_ARRAY_ELEMS(type_map) ||
        (unsigned)in_ch_மொத்தம் > MAX_CHANNELS)
        திரும்பு வெற்று;

    nb_coeffs = type_map[type] * in_ch_மொத்தம்;
    size += அளவு(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(size);
    எனில் (!dc)
        திரும்பு வெற்று;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->in_ch_மொத்தம்   = in_ch_மொத்தம்;
    dc->coeffs_offset = coeffs_offset;

    எனில் (out_size)
        *out_size = size;

    திரும்பு dc;
}
