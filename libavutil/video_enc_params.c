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

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>

#अन्तर्भाव "buffer.h"
#अन्तर्भाव "frame.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(गणना AVVideoEncParamsType type,
                                            अचिह्नित पूर्णाङ्क nb_खण्डानि, size_t *बहिर्गमनम्_आकार)
{
    संरचना TestStruct {
        AVVideoEncParams   p;
        AVVideo_खण्डम्_Params b;
    };
    ध्रुव size_t खण्डानि_विस्थापनम् = offsetof(संरचना TestStruct, b);
    size_t आकार = खण्डानि_विस्थापनम्;
    AVVideoEncParams *par;

    यदि (nb_खण्डानि > (SIZE_MAX - आकार) / परिमाण(AVVideo_खण्डम्_Params))
        प्रत्यागम रिक्त;
    आकार += परिमाण(AVVideo_खण्डम्_Params) * nb_खण्डानि;

    par = av_mallocz(आकार);
    यदि (!par)
        प्रत्यागम रिक्त;

    par->type          = type;
    par->nb_खण्डानि     = nb_खण्डानि;
    par->खण्डम्_आकार    = परिमाण(AVVideo_खण्डम्_Params);
    par->खण्डानि_विस्थापनम् = खण्डानि_विस्थापनम्;

    यदि (बहिर्गमनम्_आकार)
        *बहिर्गमनम्_आकार = आकार;

    प्रत्यागम par;
}

AVVideoEncParams*
av_video_enc_params_create_side_दत्त(AVFrame *frame, गणना AVVideoEncParamsType type,
                                     अचिह्नित पूर्णाङ्क nb_खण्डानि)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t आकार;

    par = av_video_enc_params_alloc(type, nb_खण्डानि, &आकार);
    यदि (!par)
        प्रत्यागम रिक्त;
    buf = av_बफर_create((uint8_t *)par, आकार, रिक्त, रिक्त, 0);
    यदि (!buf) {
        av_freep(&par);
        प्रत्यागम रिक्त;
    }

    यदि (!av_frame_new_side_दत्त_from_buf(frame, AV_FRAME_दत्त_VIDEO_ENC_PARAMS, buf)) {
        av_बफर_unref(&buf);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम par;
}
