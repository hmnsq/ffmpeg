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
                                            بنانشان صحيح nb_بلاڪون, size_t *ٻاهريون_سائيز)
{
    بنية TestStruct {
        AVVideoEncParams   p;
        AVVideo_بلاڪ_Params b;
    };
    ثابت size_t بلاڪون_وٿي = offsetof(بنية TestStruct, b);
    size_t سائيز = بلاڪون_وٿي;
    AVVideoEncParams *par;

    إذا (nb_بلاڪون > (SIZE_MAX - سائيز) / حجم(AVVideo_بلاڪ_Params))
        أرجع عدم;
    سائيز += حجم(AVVideo_بلاڪ_Params) * nb_بلاڪون;

    par = av_mallocz(سائيز);
    إذا (!par)
        أرجع عدم;

    par->type          = type;
    par->nb_بلاڪون     = nb_بلاڪون;
    par->بلاڪ_سائيز    = حجم(AVVideo_بلاڪ_Params);
    par->بلاڪون_وٿي = بلاڪون_وٿي;

    إذا (ٻاهريون_سائيز)
        *ٻاهريون_سائيز = سائيز;

    أرجع par;
}

AVVideoEncParams*
av_video_enc_params_create_side_معلومات(AVFrame *چوکٺو, تعداد AVVideoEncParamsType type,
                                     بنانشان صحيح nb_بلاڪون)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t سائيز;

    par = av_video_enc_params_alloc(type, nb_بلاڪون, &سائيز);
    إذا (!par)
        أرجع عدم;
    buf = av_بفر_create((uint8_t *)par, سائيز, عدم, عدم, 0);
    إذا (!buf) {
        av_freep(&par);
        أرجع عدم;
    }

    إذا (!av_چوکٺو_new_side_معلومات_from_buf(چوکٺو, AV_چوکٺو_معلومات_VIDEO_ENC_PARAMS, buf)) {
        av_بفر_unref(&buf);
        أرجع عدم;
    }

    أرجع par;
}
