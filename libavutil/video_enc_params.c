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

#ضمن <stddef.h>
#ضمن <stdint.h>

#ضمن "buffer.h"
#ضمن "frame.h"
#ضمن "mem.h"
#ضمن "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(تعداد AVVideoEncParamsType type,
                                            بینښه صحيح nb_بلاکونه, size_t *بهر_اندازه)
{
    بنية TestStruct {
        AVVideoEncParams   p;
        AVVideo_بلاک_Params b;
    };
    ثابت size_t بلاکونه_دننه_واټن = offsetof(بنية TestStruct, b);
    size_t اندازه = بلاکونه_دننه_واټن;
    AVVideoEncParams *par;

    إذا (nb_بلاکونه > (SIZE_MAX - اندازه) / حجم(AVVideo_بلاک_Params))
        أرجع عدم;
    اندازه += حجم(AVVideo_بلاک_Params) * nb_بلاکونه;

    par = av_mallocz(اندازه);
    إذا (!par)
        أرجع عدم;

    par->type          = type;
    par->nb_بلاکونه     = nb_بلاکونه;
    par->بلاک_اندازه    = حجم(AVVideo_بلاک_Params);
    par->بلاکونه_دننه_واټن = بلاکونه_دننه_واټن;

    إذا (بهر_اندازه)
        *بهر_اندازه = اندازه;

    أرجع par;
}

AVVideoEncParams*
av_video_enc_params_create_side_معلومات(AVFrame *چوکاټ, تعداد AVVideoEncParamsType type,
                                     بینښه صحيح nb_بلاکونه)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t اندازه;

    par = av_video_enc_params_alloc(type, nb_بلاکونه, &اندازه);
    إذا (!par)
        أرجع عدم;
    buf = av_بفر_create((uint8_t *)par, اندازه, عدم, عدم, 0);
    إذا (!buf) {
        av_freep(&par);
        أرجع عدم;
    }

    إذا (!av_چوکاټ_new_side_معلومات_from_buf(چوکاټ, AV_چوکاټ_معلومات_VIDEO_ENC_PARAMS, buf)) {
        av_بفر_unref(&buf);
        أرجع عدم;
    }

    أرجع par;
}
