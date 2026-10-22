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

#ಅನ್ತರ್ಭಾವ "downmix_info.h"
#ಅನ್ತರ್ಭಾವ "frame.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

AVDownmixInfo *av_downmix_info_update_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data;

    side_data = av_frame_get_side_data(frame, AV_FRAME_DATA_DOWNMIX_INFO);

    ಯದಿ (!side_data) {
        side_data = av_frame_new_side_data(frame, AV_FRAME_DATA_DOWNMIX_INFO,
                                           ಪರಿಮಾಣ(AVDownmixInfo));
        ಯದಿ (side_data)
            memset(side_data->data, 0, ಪರಿಮಾಣ(AVDownmixInfo));
    }

    ಯದಿ (!side_data)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಪ್ರತ್ಯಾಗಮ (AVDownmixInfo*)side_data->data;
}

#define MAX_CHANNELS 64

ಸ್ಥಿರ ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmixMatrix *av_downmix_matrix_alloc(ಗಣನಾ AVDownmixType type,
                                         ಪೂರ್ಣಾಙ್ಕ in_ch_ಎಣಿಕೆ, size_t *out_size)
{
    ಸಂರಚನಾ TestStruct {
        AVDownmixMatrix p;
        AVDownmixCoeff  b;
    };
    ಧ್ರುವ size_t coeffs_offset = offsetof(ಸಂರಚನಾ TestStruct, b);
    size_t size = coeffs_offset;
    unsigned ಪೂರ್ಣಾಙ್ಕ nb_coeffs;
    AVDownmixMatrix *dc;

    ಯದಿ ((unsigned)type >= FF_ARRAY_ELEMS(type_map) ||
        (unsigned)in_ch_ಎಣಿಕೆ > MAX_CHANNELS)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    nb_coeffs = type_map[type] * in_ch_ಎಣಿಕೆ;
    size += ಪರಿಮಾಣ(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(size);
    ಯದಿ (!dc)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->in_ch_ಎಣಿಕೆ   = in_ch_ಎಣಿಕೆ;
    dc->coeffs_offset = coeffs_offset;

    ಯದಿ (out_size)
        *out_size = size;

    ಪ್ರತ್ಯಾಗಮ dc;
}
