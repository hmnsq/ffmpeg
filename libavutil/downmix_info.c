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

#ضمن "downmix_info.h"
#ضمن "frame.h"
#ضمن "mem.h"

AVDownmixInfo *av_downmix_info_update_side_داده(AVFrame *قاب)
{
    AVFrame_Side_داده *side_داده;

    side_داده = av_قاب_get_side_داده(قاب, AV_قاب_داده_DOWNMIX_INFO);

    إذا (!side_داده) {
        side_داده = av_قاب_new_side_داده(قاب, AV_قاب_داده_DOWNMIX_INFO,
                                           حجم(AVDownmixInfo));
        إذا (side_داده)
            memset(side_داده->داده, 0, حجم(AVDownmixInfo));
    }

    إذا (!side_داده)
        أرجع عدم;

    أرجع (AVDownmixInfo*)side_داده->داده;
}

#تعریف_کن MAX_CHANNELS 64

ساكن ثابت صحيح type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmix_ماتریس *av_downmix_ماتریس_alloc(تعداد AVDownmixType type,
                                         صحيح درون_ch_شمار, size_t *بیرون_اندازه)
{
    بنية TestStruct {
        AVDownmix_ماتریس p;
        AVDownmixCoeff  b;
    };
    ثابت size_t coeffs_جابه_جایی = offsetof(بنية TestStruct, b);
    size_t اندازه = coeffs_جابه_جایی;
    بیعلامت صحيح nb_coeffs;
    AVDownmix_ماتریس *dc;

    إذا ((بیعلامت)type >= FF_ARRAY_ELEMS(type_map) ||
        (بیعلامت)درون_ch_شمار > MAX_CHANNELS)
        أرجع عدم;

    nb_coeffs = type_map[type] * درون_ch_شمار;
    اندازه += حجم(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(اندازه);
    إذا (!dc)
        أرجع عدم;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->درون_ch_شمار   = درون_ch_شمار;
    dc->coeffs_جابه_جایی = coeffs_جابه_جایی;

    إذا (بیرون_اندازه)
        *بیرون_اندازه = اندازه;

    أرجع dc;
}
