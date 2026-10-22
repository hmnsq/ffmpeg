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
                                            بیعلامت صحيح nb_بلوکها, size_t *بیرون_اندازه)
{
    بنية TestStruct {
        AVVideoEncParams   p;
        AVVideo_بلوک_Params b;
    };
    ثابت size_t بلوکها_جابه_جایی = offsetof(بنية TestStruct, b);
    size_t اندازه = بلوکها_جابه_جایی;
    AVVideoEncParams *par;

    إذا (nb_بلوکها > (SIZE_MAX - اندازه) / حجم(AVVideo_بلوک_Params))
        أرجع عدم;
    اندازه += حجم(AVVideo_بلوک_Params) * nb_بلوکها;

    par = av_mallocz(اندازه);
    إذا (!par)
        أرجع عدم;

    par->type          = type;
    par->nb_بلوکها     = nb_بلوکها;
    par->بلوک_اندازه    = حجم(AVVideo_بلوک_Params);
    par->بلوکها_جابه_جایی = بلوکها_جابه_جایی;

    إذا (بیرون_اندازه)
        *بیرون_اندازه = اندازه;

    أرجع par;
}

AVVideoEncParams*
av_video_enc_params_create_side_داده(AVFrame *قاب, تعداد AVVideoEncParamsType type,
                                     بیعلامت صحيح nb_بلوکها)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t اندازه;

    par = av_video_enc_params_alloc(type, nb_بلوکها, &اندازه);
    إذا (!par)
        أرجع عدم;
    buf = av_میانگیر_create((uint8_t *)par, اندازه, عدم, عدم, 0);
    إذا (!buf) {
        av_freep(&par);
        أرجع عدم;
    }

    إذا (!av_قاب_new_side_داده_from_buf(قاب, AV_قاب_داده_VIDEO_ENC_PARAMS, buf)) {
        av_میانگیر_unref(&buf);
        أرجع عدم;
    }

    أرجع par;
}
