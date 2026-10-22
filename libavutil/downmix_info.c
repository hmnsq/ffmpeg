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

#అన్తర్భావ "downmix_info.h"
#అన్తర్భావ "frame.h"
#అన్తర్భావ "mem.h"

AVDownmixInfo *av_downmix_info_update_side_దత్తాంశం(AVFrame *చట్రం)
{
    AVFrame_Side_దత్తాంశం *side_దత్తాంశం;

    side_దత్తాంశం = av_చట్రం_get_side_దత్తాంశం(చట్రం, AV_చట్రం_దత్తాంశం_DOWNMIX_INFO);

    ఒకవేళ (!side_దత్తాంశం) {
        side_దత్తాంశం = av_చట్రం_new_side_దత్తాంశం(చట్రం, AV_చట్రం_దత్తాంశం_DOWNMIX_INFO,
                                           పరిమాణం(AVDownmixInfo));
        ఒకవేళ (side_దత్తాంశం)
            memset(side_దత్తాంశం->దత్తాంశం, 0, పరిమాణం(AVDownmixInfo));
    }

    ఒకవేళ (!side_దత్తాంశం)
        తిరిగి ఖాళీ;

    తిరిగి (AVDownmixInfo*)side_దత్తాంశం->దత్తాంశం;
}

#నిర్వచించు MAX_CHANNELS 64

స్థిర స్థిరరాశి పూర్ణాంకం type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmix_మాతృక *av_downmix_మాతృక_alloc(గణన AVDownmixType type,
                                         పూర్ణాంకం లోపల_ch_లెక్క, size_t *బహిర్గతం_కొలత)
{
    నిర్మాణం TestStruct {
        AVDownmix_మాతృక p;
        AVDownmixCoeff  b;
    };
    స్థిరరాశి size_t coeffs_స్థానభ్రంశం = offsetof(నిర్మాణం TestStruct, b);
    size_t కొలత = coeffs_స్థానభ్రంశం;
    గుర్తులేని పూర్ణాంకం nb_coeffs;
    AVDownmix_మాతృక *dc;

    ఒకవేళ ((గుర్తులేని)type >= FF_ARRAY_ELEMS(type_map) ||
        (గుర్తులేని)లోపల_ch_లెక్క > MAX_CHANNELS)
        తిరిగి ఖాళీ;

    nb_coeffs = type_map[type] * లోపల_ch_లెక్క;
    కొలత += పరిమాణం(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(కొలత);
    ఒకవేళ (!dc)
        తిరిగి ఖాళీ;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->లోపల_ch_లెక్క   = లోపల_ch_లెక్క;
    dc->coeffs_స్థానభ్రంశం = coeffs_స్థానభ్రంశం;

    ఒకవేళ (బహిర్గతం_కొలత)
        *బహిర్గతం_కొలత = కొలత;

    తిరిగి dc;
}
