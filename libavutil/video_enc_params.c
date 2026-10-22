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
                                            بنانشانی صحيح nb_بلاکاں, size_t *باہرلا_ناپ)
{
    بنية TestStruct {
        AVVideoEncParams   p;
        AVVideo_بلاک_Params b;
    };
    ثابت size_t بلاکاں_وتھ = offsetof(بنية TestStruct, b);
    size_t ناپ = بلاکاں_وتھ;
    AVVideoEncParams *par;

    إذا (nb_بلاکاں > (SIZE_MAX - ناپ) / حجم(AVVideo_بلاک_Params))
        أرجع عدم;
    ناپ += حجم(AVVideo_بلاک_Params) * nb_بلاکاں;

    par = av_mallocz(ناپ);
    إذا (!par)
        أرجع عدم;

    par->type          = type;
    par->nb_بلاکاں     = nb_بلاکاں;
    par->بلاک_ناپ    = حجم(AVVideo_بلاک_Params);
    par->بلاکاں_وتھ = بلاکاں_وتھ;

    إذا (باہرلا_ناپ)
        *باہرلا_ناپ = ناپ;

    أرجع par;
}

AVVideoEncParams*
av_video_enc_params_create_side_انکڑے(AVFrame *چوکھٹا, تعداد AVVideoEncParamsType type,
                                     بنانشانی صحيح nb_بلاکاں)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t ناپ;

    par = av_video_enc_params_alloc(type, nb_بلاکاں, &ناپ);
    إذا (!par)
        أرجع عدم;
    buf = av_بفر_create((uint8_t *)par, ناپ, عدم, عدم, 0);
    إذا (!buf) {
        av_freep(&par);
        أرجع عدم;
    }

    إذا (!av_چوکھٹا_new_side_انکڑے_from_buf(چوکھٹا, AV_چوکھٹا_انکڑے_VIDEO_ENC_PARAMS, buf)) {
        av_بفر_unref(&buf);
        أرجع عدم;
    }

    أرجع par;
}
