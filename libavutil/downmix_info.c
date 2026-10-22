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

AVDownmixInfo *av_downmix_info_update_side_معلومات(AVFrame *چوکاټ)
{
    AVFrame_Side_معلومات *side_معلومات;

    side_معلومات = av_چوکاټ_get_side_معلومات(چوکاټ, AV_چوکاټ_معلومات_DOWNMIX_INFO);

    إذا (!side_معلومات) {
        side_معلومات = av_چوکاټ_new_side_معلومات(چوکاټ, AV_چوکاټ_معلومات_DOWNMIX_INFO,
                                           حجم(AVDownmixInfo));
        إذا (side_معلومات)
            memset(side_معلومات->معلومات, 0, حجم(AVDownmixInfo));
    }

    إذا (!side_معلومات)
        أرجع عدم;

    أرجع (AVDownmixInfo*)side_معلومات->معلومات;
}

#تعریف_کړه MAX_CHANNELS 64

ساكن ثابت صحيح type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmix_ماتریکس *av_downmix_ماتریکس_alloc(تعداد AVDownmixType type,
                                         صحيح دننه_ch_شمېر, size_t *بهر_اندازه)
{
    بنية TestStruct {
        AVDownmix_ماتریکس p;
        AVDownmixCoeff  b;
    };
    ثابت size_t coeffs_دننه_واټن = offsetof(بنية TestStruct, b);
    size_t اندازه = coeffs_دننه_واټن;
    بینښه صحيح nb_coeffs;
    AVDownmix_ماتریکس *dc;

    إذا ((بینښه)type >= FF_ARRAY_ELEMS(type_map) ||
        (بینښه)دننه_ch_شمېر > MAX_CHANNELS)
        أرجع عدم;

    nb_coeffs = type_map[type] * دننه_ch_شمېر;
    اندازه += حجم(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(اندازه);
    إذا (!dc)
        أرجع عدم;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->دننه_ch_شمېر   = دننه_ch_شمېر;
    dc->coeffs_دننه_واټن = coeffs_دننه_واټن;

    إذا (بهر_اندازه)
        *بهر_اندازه = اندازه;

    أرجع dc;
}
