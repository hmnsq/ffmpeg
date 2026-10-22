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

#شامل <stddef.h>
#شامل <stdint.h>

#شامل "buffer.h"
#شامل "frame.h"
#شامل "mem.h"
#شامل "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(شمار AVVideoEncParamsType type,
                                            غیرعلامتی صحیح nb_بلاکیں, size_t *برآمد_سائز)
{
    ساخت TestStruct {
        AVVideoEncParams   p;
        AVVideo_بلاک_Params b;
    };
    ثابت size_t بلاکیں_انحراف = offsetof(ساخت TestStruct, b);
    size_t سائز = بلاکیں_انحراف;
    AVVideoEncParams *par;

    اگر (nb_بلاکیں > (SIZE_MAX - سائز) / حجم(AVVideo_بلاک_Params))
        واپس تہی;
    سائز += حجم(AVVideo_بلاک_Params) * nb_بلاکیں;

    par = av_mallocz(سائز);
    اگر (!par)
        واپس تہی;

    par->type          = type;
    par->nb_بلاکیں     = nb_بلاکیں;
    par->بلاک_سائز    = حجم(AVVideo_بلاک_Params);
    par->بلاکیں_انحراف = بلاکیں_انحراف;

    اگر (برآمد_سائز)
        *برآمد_سائز = سائز;

    واپس par;
}

AVVideoEncParams*
av_video_enc_params_create_side_ڈیٹا(AVFrame *چوکھٹا, شمار AVVideoEncParamsType type,
                                     غیرعلامتی صحیح nb_بلاکیں)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t سائز;

    par = av_video_enc_params_alloc(type, nb_بلاکیں, &سائز);
    اگر (!par)
        واپس تہی;
    buf = av_بفر_create((uint8_t *)par, سائز, تہی, تہی, 0);
    اگر (!buf) {
        av_freep(&par);
        واپس تہی;
    }

    اگر (!av_چوکھٹا_new_side_ڈیٹا_from_buf(چوکھٹا, AV_چوکھٹا_ڈیٹا_VIDEO_ENC_PARAMS, buf)) {
        av_بفر_unref(&buf);
        واپس تہی;
    }

    واپس par;
}
