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

    जर (!side_data) {
        side_data = av_frame_new_side_data(frame, AV_FRAME_DATA_DOWNMIX_INFO,
                                           आकार(AVDownmixInfo));
        जर (side_data)
            स_रखो(side_data->data, 0, आकार(AVDownmixInfo));
    }

    जर (!side_data)
        परत रिक्त;

    परत (AVDownmixInfo*)side_data->data;
}

#define MAX_CHANNELS 64

स्थिर स्थिरांक पूर्णांक type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmixMatrix *av_downmix_matrix_alloc(गणना AVDownmixType type,
                                         पूर्णांक in_ch_मोजणी, माप_प्रकार *out_size)
{
    संरचना TestStruct {
        AVDownmixMatrix p;
        AVDownmixCoeff  b;
    };
    स्थिरांक माप_प्रकार coeffs_offset = दुरत्व(संरचना TestStruct, b);
    माप_प्रकार size = coeffs_offset;
    अचिन्हित पूर्णांक nb_coeffs;
    AVDownmixMatrix *dc;

    जर ((अचिन्हित)type >= FF_ARRAY_ELEMS(type_map) ||
        (अचिन्हित)in_ch_मोजणी > MAX_CHANNELS)
        परत रिक्त;

    nb_coeffs = type_map[type] * in_ch_मोजणी;
    size += आकार(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(size);
    जर (!dc)
        परत रिक्त;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->in_ch_मोजणी   = in_ch_मोजणी;
    dc->coeffs_offset = coeffs_offset;

    जर (out_size)
        *out_size = size;

    परत dc;
}
