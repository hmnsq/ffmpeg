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

#ଅନ୍ତର୍ଭାଵ "downmix_info.h"
#ଅନ୍ତର୍ଭାଵ "frame.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"

AVDownmixInfo *av_downmix_info_update_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data;

    side_data = av_frame_get_side_data(frame, AV_FRAME_DATA_DOWNMIX_INFO);

    ଯଦି (!side_data) {
        side_data = av_frame_new_side_data(frame, AV_FRAME_DATA_DOWNMIX_INFO,
                                           ଆକାର(AVDownmixInfo));
        ଯଦି (side_data)
            memset(side_data->data, 0, ଆକାର(AVDownmixInfo));
    }

    ଯଦି (!side_data)
        ଫେରନ୍ତୁ ଖାଲି;

    ଫେରନ୍ତୁ (AVDownmixInfo*)side_data->data;
}

#define MAX_CHANNELS 64

ସ୍ଥିର ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmixMatrix *av_downmix_matrix_alloc(ଗଣନା AVDownmixType type,
                                         ପୂର୍ଣ୍ଣସଂଖ୍ୟା in_ch_ଗଣନା, size_t *out_size)
{
    ସଂରଚନା TestStruct {
        AVDownmixMatrix p;
        AVDownmixCoeff  b;
    };
    ଅଚଳ size_t coeffs_offset = offsetof(ସଂରଚନା TestStruct, b);
    size_t size = coeffs_offset;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_coeffs;
    AVDownmixMatrix *dc;

    ଯଦି ((unsigned)type >= FF_ARRAY_ELEMS(type_map) ||
        (unsigned)in_ch_ଗଣନା > MAX_CHANNELS)
        ଫେରନ୍ତୁ ଖାଲି;

    nb_coeffs = type_map[type] * in_ch_ଗଣନା;
    size += ଆକାର(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(size);
    ଯଦି (!dc)
        ଫେରନ୍ତୁ ଖାଲି;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->in_ch_ଗଣନା   = in_ch_ଗଣନା;
    dc->coeffs_offset = coeffs_offset;

    ଯଦି (out_size)
        *out_size = size;

    ଫେରନ୍ତୁ dc;
}
