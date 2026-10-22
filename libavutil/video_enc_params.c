/*
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

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(ਗਿਣਤੀ AVVideoEncParamsType type,
                                            ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ nb_ਖੰਡਾਂ, size_t *ਬਾਹਰਲਾ_ਮਾਪ)
{
    ਬਣਤਰ TestStruct {
        AVVideoEncParams   p;
        AVVideo_ਖੰਡ_Params b;
    };
    ਅਚਲ size_t ਖੰਡਾਂ_ਵਿੱਥ = offsetof(ਬਣਤਰ TestStruct, b);
    size_t ਮਾਪ = ਖੰਡਾਂ_ਵਿੱਥ;
    AVVideoEncParams *par;

    ਜੇ (nb_ਖੰਡਾਂ > (SIZE_MAX - ਮਾਪ) / ਆਕਾਰ(AVVideo_ਖੰਡ_Params))
        ਵਾਪਸ ਨਿਰਾ;
    ਮਾਪ += ਆਕਾਰ(AVVideo_ਖੰਡ_Params) * nb_ਖੰਡਾਂ;

    par = av_mallocz(ਮਾਪ);
    ਜੇ (!par)
        ਵਾਪਸ ਨਿਰਾ;

    par->type          = type;
    par->nb_ਖੰਡਾਂ     = nb_ਖੰਡਾਂ;
    par->ਖੰਡ_ਮਾਪ    = ਆਕਾਰ(AVVideo_ਖੰਡ_Params);
    par->ਖੰਡਾਂ_ਵਿੱਥ = ਖੰਡਾਂ_ਵਿੱਥ;

    ਜੇ (ਬਾਹਰਲਾ_ਮਾਪ)
        *ਬਾਹਰਲਾ_ਮਾਪ = ਮਾਪ;

    ਵਾਪਸ par;
}

AVVideoEncParams*
av_video_enc_params_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ, ਗਿਣਤੀ AVVideoEncParamsType type,
                                     ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ nb_ਖੰਡਾਂ)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t ਮਾਪ;

    par = av_video_enc_params_alloc(type, nb_ਖੰਡਾਂ, &ਮਾਪ);
    ਜੇ (!par)
        ਵਾਪਸ ਨਿਰਾ;
    buf = av_ਬਫਰ_create((uint8_t *)par, ਮਾਪ, ਨਿਰਾ, ਨਿਰਾ, 0);
    ਜੇ (!buf) {
        av_freep(&par);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ_from_buf(ਚੌਖਟਾ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_VIDEO_ENC_PARAMS, buf)) {
        av_ਬਫਰ_unref(&buf);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ par;
}
