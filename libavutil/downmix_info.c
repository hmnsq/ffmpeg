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

AVDownmixInfo *av_downmix_info_update_side_दत्त(AVFrame *frame)
{
    AVFrame_Side_दत्त *side_दत्त;

    side_दत्त = av_frame_get_side_दत्त(frame, AV_FRAME_दत्त_DOWNMIX_INFO);

    यदि (!side_दत्त) {
        side_दत्त = av_frame_new_side_दत्त(frame, AV_FRAME_दत्त_DOWNMIX_INFO,
                                           परिमाण(AVDownmixInfo));
        यदि (side_दत्त)
            स्मृतिं_पूरय(side_दत्त->दत्त, 0, परिमाण(AVDownmixInfo));
    }

    यदि (!side_दत्त)
        प्रत्यागम रिक्त;

    प्रत्यागम (AVDownmixInfo*)side_दत्त->दत्त;
}

#परिभाषय MAX_CHANNELS 64

स्थिर ध्रुव पूर्णाङ्क type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmixMatrix *av_downmix_matrix_alloc(गणना AVDownmixType type,
                                         पूर्णाङ्क अन्तर्_ch_गणनम्, size_t *बहिर्गमनम्_आकार)
{
    संरचना TestStruct {
        AVDownmixMatrix p;
        AVDownmixCoeff  b;
    };
    ध्रुव size_t coeffs_विस्थापनम् = offsetof(संरचना TestStruct, b);
    size_t आकार = coeffs_विस्थापनम्;
    अचिह्नित पूर्णाङ्क nb_coeffs;
    AVDownmixMatrix *dc;

    यदि ((अचिह्नित)type >= FF_ARRAY_ELEMS(type_map) ||
        (अचिह्नित)अन्तर्_ch_गणनम् > MAX_CHANNELS)
        प्रत्यागम रिक्त;

    nb_coeffs = type_map[type] * अन्तर्_ch_गणनम्;
    आकार += परिमाण(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(आकार);
    यदि (!dc)
        प्रत्यागम रिक्त;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->अन्तर्_ch_गणनम्   = अन्तर्_ch_गणनम्;
    dc->coeffs_विस्थापनम् = coeffs_विस्थापनम्;

    यदि (बहिर्गमनम्_आकार)
        *बहिर्गमनम्_आकार = आकार;

    प्रत्यागम dc;
}
