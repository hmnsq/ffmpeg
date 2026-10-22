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

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>

#అన్తర్భావ "buffer.h"
#అన్తర్భావ "frame.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(గణన AVVideoEncParamsType type,
                                            గుర్తులేని పూర్ణాంకం nb_ఖండాలు, size_t *బహిర్గతం_కొలత)
{
    నిర్మాణం TestStruct {
        AVVideoEncParams   p;
        AVVideo_ఖండం_Params b;
    };
    స్థిరరాశి size_t ఖండాలు_స్థానభ్రంశం = offsetof(నిర్మాణం TestStruct, b);
    size_t కొలత = ఖండాలు_స్థానభ్రంశం;
    AVVideoEncParams *par;

    ఒకవేళ (nb_ఖండాలు > (SIZE_MAX - కొలత) / పరిమాణం(AVVideo_ఖండం_Params))
        తిరిగి ఖాళీ;
    కొలత += పరిమాణం(AVVideo_ఖండం_Params) * nb_ఖండాలు;

    par = av_mallocz(కొలత);
    ఒకవేళ (!par)
        తిరిగి ఖాళీ;

    par->type          = type;
    par->nb_ఖండాలు     = nb_ఖండాలు;
    par->ఖండం_కొలత    = పరిమాణం(AVVideo_ఖండం_Params);
    par->ఖండాలు_స్థానభ్రంశం = ఖండాలు_స్థానభ్రంశం;

    ఒకవేళ (బహిర్గతం_కొలత)
        *బహిర్గతం_కొలత = కొలత;

    తిరిగి par;
}

AVVideoEncParams*
av_video_enc_params_create_side_దత్తాంశం(AVFrame *చట్రం, గణన AVVideoEncParamsType type,
                                     గుర్తులేని పూర్ణాంకం nb_ఖండాలు)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t కొలత;

    par = av_video_enc_params_alloc(type, nb_ఖండాలు, &కొలత);
    ఒకవేళ (!par)
        తిరిగి ఖాళీ;
    buf = av_బఫరు_create((uint8_t *)par, కొలత, ఖాళీ, ఖాళీ, 0);
    ఒకవేళ (!buf) {
        av_freep(&par);
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!av_చట్రం_new_side_దత్తాంశం_from_buf(చట్రం, AV_చట్రం_దత్తాంశం_VIDEO_ENC_PARAMS, buf)) {
        av_బఫరు_unref(&buf);
        తిరిగి ఖాళీ;
    }

    తిరిగి par;
}
