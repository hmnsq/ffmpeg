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

#شامل "downmix_info.h"
#شامل "frame.h"
#شامل "mem.h"

AVDownmixInfo *av_downmix_info_update_side_ڈیٹا(AVFrame *چوکھٹا)
{
    AVFrame_Side_ڈیٹا *side_ڈیٹا;

    side_ڈیٹا = av_چوکھٹا_get_side_ڈیٹا(چوکھٹا, AV_چوکھٹا_ڈیٹا_DOWNMIX_INFO);

    اگر (!side_ڈیٹا) {
        side_ڈیٹا = av_چوکھٹا_new_side_ڈیٹا(چوکھٹا, AV_چوکھٹا_ڈیٹا_DOWNMIX_INFO,
                                           حجم(AVDownmixInfo));
        اگر (side_ڈیٹا)
            memset(side_ڈیٹا->ڈیٹا, 0, حجم(AVDownmixInfo));
    }

    اگر (!side_ڈیٹا)
        واپس تہی;

    واپس (AVDownmixInfo*)side_ڈیٹا->ڈیٹا;
}

#تعریف_کرو MAX_CHANNELS 64

ساکن ثابت صحیح type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmix_میٹرکس *av_downmix_میٹرکس_alloc(شمار AVDownmixType type,
                                         صحیح اندر_ch_گنتی, size_t *برآمد_سائز)
{
    ساخت TestStruct {
        AVDownmix_میٹرکس p;
        AVDownmixCoeff  b;
    };
    ثابت size_t coeffs_انحراف = offsetof(ساخت TestStruct, b);
    size_t سائز = coeffs_انحراف;
    غیرعلامتی صحیح nb_coeffs;
    AVDownmix_میٹرکس *dc;

    اگر ((غیرعلامتی)type >= FF_ARRAY_ELEMS(type_map) ||
        (غیرعلامتی)اندر_ch_گنتی > MAX_CHANNELS)
        واپس تہی;

    nb_coeffs = type_map[type] * اندر_ch_گنتی;
    سائز += حجم(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(سائز);
    اگر (!dc)
        واپس تہی;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->اندر_ch_گنتی   = اندر_ch_گنتی;
    dc->coeffs_انحراف = coeffs_انحراف;

    اگر (برآمد_سائز)
        *برآمد_سائز = سائز;

    واپس dc;
}
