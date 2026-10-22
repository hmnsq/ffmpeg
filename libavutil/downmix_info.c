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

AVDownmixInfo *av_downmix_info_update_side_انکڑے(AVFrame *چوکھٹا)
{
    AVFrame_Side_انکڑے *side_انکڑے;

    side_انکڑے = av_چوکھٹا_get_side_انکڑے(چوکھٹا, AV_چوکھٹا_انکڑے_DOWNMIX_INFO);

    إذا (!side_انکڑے) {
        side_انکڑے = av_چوکھٹا_new_side_انکڑے(چوکھٹا, AV_چوکھٹا_انکڑے_DOWNMIX_INFO,
                                           حجم(AVDownmixInfo));
        إذا (side_انکڑے)
            memset(side_انکڑے->انکڑے, 0, حجم(AVDownmixInfo));
    }

    إذا (!side_انکڑے)
        أرجع عدم;

    أرجع (AVDownmixInfo*)side_انکڑے->انکڑے;
}

#تعریف_کرو MAX_CHANNELS 64

ساكن ثابت صحيح type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmix_میٹرکس *av_downmix_میٹرکس_alloc(تعداد AVDownmixType type,
                                         صحيح وچ_ch_گنتی, size_t *باہرلا_ناپ)
{
    بنية TestStruct {
        AVDownmix_میٹرکس p;
        AVDownmixCoeff  b;
    };
    ثابت size_t coeffs_وتھ = offsetof(بنية TestStruct, b);
    size_t ناپ = coeffs_وتھ;
    بنانشانی صحيح nb_coeffs;
    AVDownmix_میٹرکس *dc;

    إذا ((بنانشانی)type >= FF_ARRAY_ELEMS(type_map) ||
        (بنانشانی)وچ_ch_گنتی > MAX_CHANNELS)
        أرجع عدم;

    nb_coeffs = type_map[type] * وچ_ch_گنتی;
    ناپ += حجم(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(ناپ);
    إذا (!dc)
        أرجع عدم;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->وچ_ch_گنتی   = وچ_ch_گنتی;
    dc->coeffs_وتھ = coeffs_وتھ;

    إذا (باہرلا_ناپ)
        *باہرلا_ناپ = ناپ;

    أرجع dc;
}
