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

#अन्तर्भाव "downmix_info.h"
#अन्तर्भाव "frame.h"
#अन्तर्भाव "mem.h"

AVDownmixInfo *av_downmix_info_update_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data;

    side_data = av_frame_get_side_data(frame, AV_FRAME_DATA_DOWNMIX_INFO);

    जइ (!side_data) {
        side_data = av_frame_new_side_data(frame, AV_FRAME_DATA_DOWNMIX_INFO,
                                           परिमाण(AVDownmixInfo));
        जइ (side_data)
            memset(side_data->data, 0, परिमाण(AVDownmixInfo));
    }

    जइ (!side_data)
        प्रत्यागम रिक्त;

    प्रत्यागम (AVDownmixInfo*)side_data->data;
}

#define MAX_CHANNELS 64

स्थिर ध्रुव पूर्णाङ्क type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmixMatrix *av_downmix_matrix_alloc(गणना AVDownmixType type,
                                         पूर्णाङ्क in_ch_गणनम्, size_t *out_size)
{
    संरचना TestStruct {
        AVDownmixMatrix p;
        AVDownmixCoeff  b;
    };
    ध्रुव size_t coeffs_offset = offsetof(संरचना TestStruct, b);
    size_t size = coeffs_offset;
    unsigned पूर्णाङ्क nb_coeffs;
    AVDownmixMatrix *dc;

    जइ ((unsigned)type >= FF_ARRAY_ELEMS(type_map) ||
        (unsigned)in_ch_गणनम् > MAX_CHANNELS)
        प्रत्यागम रिक्त;

    nb_coeffs = type_map[type] * in_ch_गणनम्;
    size += परिमाण(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(size);
    जइ (!dc)
        प्रत्यागम रिक्त;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->in_ch_गणनम्   = in_ch_गणनम्;
    dc->coeffs_offset = coeffs_offset;

    जइ (out_size)
        *out_size = size;

    प्रत्यागम dc;
}
