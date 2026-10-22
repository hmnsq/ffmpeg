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

#ਅਨ੍ਤਰ੍ਭਾਵ "downmix_info.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

AVDownmixInfo *av_downmix_info_update_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ)
{
    AVFrame_Side_ਅੰਕੜੇ *side_ਅੰਕੜੇ;

    side_ਅੰਕੜੇ = av_ਚੌਖਟਾ_get_side_ਅੰਕੜੇ(ਚੌਖਟਾ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DOWNMIX_INFO);

    ਜੇ (!side_ਅੰਕੜੇ) {
        side_ਅੰਕੜੇ = av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ(ਚੌਖਟਾ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DOWNMIX_INFO,
                                           ਆਕਾਰ(AVDownmixInfo));
        ਜੇ (side_ਅੰਕੜੇ)
            memset(side_ਅੰਕੜੇ->ਅੰਕੜੇ, 0, ਆਕਾਰ(AVDownmixInfo));
    }

    ਜੇ (!side_ਅੰਕੜੇ)
        ਵਾਪਸ ਨਿਰਾ;

    ਵਾਪਸ (AVDownmixInfo*)side_ਅੰਕੜੇ->ਅੰਕੜੇ;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_CHANNELS 64

ਸਥਿਰ ਅਚਲ ਪੂਰਨ type_map[] = {
    [AV_DOWNMIX_TYPE_UNKNOWN] = 0,
    [AV_DOWNMIX_TYPE_LORO]    = 2,
    [AV_DOWNMIX_TYPE_LTRT]    = 2,
    [AV_DOWNMIX_TYPE_DPLII]   = 2,
};

AVDownmix_ਮੈਟ੍ਰਿਕਸ *av_downmix_ਮੈਟ੍ਰਿਕਸ_alloc(ਗਿਣਤੀ AVDownmixType type,
                                         ਪੂਰਨ ਵਿੱਚ_ch_ਗਿਣਤੀ, size_t *ਬਾਹਰਲਾ_ਮਾਪ)
{
    ਬਣਤਰ TestStruct {
        AVDownmix_ਮੈਟ੍ਰਿਕਸ p;
        AVDownmixCoeff  b;
    };
    ਅਚਲ size_t coeffs_ਵਿੱਥ = offsetof(ਬਣਤਰ TestStruct, b);
    size_t ਮਾਪ = coeffs_ਵਿੱਥ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ nb_coeffs;
    AVDownmix_ਮੈਟ੍ਰਿਕਸ *dc;

    ਜੇ ((ਬਿਨਾਨਿਸ਼ਾਨੀ)type >= FF_ARRAY_ELEMS(type_map) ||
        (ਬਿਨਾਨਿਸ਼ਾਨੀ)ਵਿੱਚ_ch_ਗਿਣਤੀ > MAX_CHANNELS)
        ਵਾਪਸ ਨਿਰਾ;

    nb_coeffs = type_map[type] * ਵਿੱਚ_ch_ਗਿਣਤੀ;
    ਮਾਪ += ਆਕਾਰ(AVDownmixCoeff) * nb_coeffs;

    dc = av_mallocz(ਮਾਪ);
    ਜੇ (!dc)
        ਵਾਪਸ ਨਿਰਾ;

    dc->downmix_type  = type;
    dc->nb_coeffs     = nb_coeffs;
    dc->ਵਿੱਚ_ch_ਗਿਣਤੀ   = ਵਿੱਚ_ch_ਗਿਣਤੀ;
    dc->coeffs_ਵਿੱਥ = coeffs_ਵਿੱਥ;

    ਜੇ (ਬਾਹਰਲਾ_ਮਾਪ)
        *ਬਾਹਰਲਾ_ਮਾਪ = ਮਾਪ;

    ਵਾਪਸ dc;
}
