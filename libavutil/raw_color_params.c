/*
 * Copyright (c) 2026 Lynne <dev@lynne.ee>
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

#ਅਨ੍ਤਰ੍ਭਾਵ "raw_color_params.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

AVRawColorParams *av_raw_color_params_alloc(size_t *ਮਾਪ)
{
    AVRawColorParams *p = av_mallocz(ਆਕਾਰ(AVRawColorParams));
    ਜੇ (!p)
        ਵਾਪਸ ਨਿਰਾ;

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = ਆਕਾਰ(*p);

    ਵਾਪਸ p;
}

AVRawColorParams *av_raw_color_params_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ)
{
    AVFrame_Side_ਅੰਕੜੇ *side_ਅੰਕੜੇ =
        av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ(ਚੌਖਟਾ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_RAW_COLOR_PARAMS,
                               ਆਕਾਰ(AVRawColorParams));
    ਜੇ (!side_ਅੰਕੜੇ)
        ਵਾਪਸ ਨਿਰਾ;

    memset(side_ਅੰਕੜੇ->ਅੰਕੜੇ, 0, side_ਅੰਕੜੇ->ਮਾਪ);

    ਵਾਪਸ (AVRawColorParams *)side_ਅੰਕੜੇ->ਅੰਕੜੇ;
}
