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

#समावेश <stddef.h>
#समावेश <stdint.h>

#समावेश "buffer.h"
#समावेश "frame.h"
#समावेश "mem.h"
#समावेश "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(क्रमागत AVVideoEncParamsType type,
                                            अचिन्हित पूर्णांक nb_blocks, माप_प्रकार *out_आकार)
{
    काष्ठा TestStruct {
        AVVideoEncParams   p;
        AVVideoBlockParams b;
    };
    स्थिर माप_प्रकार blocks_offset = दुरत्व(काष्ठा TestStruct, b);
    माप_प्रकार आकार = blocks_offset;
    AVVideoEncParams *par;

    अगर (nb_blocks > (SIZE_MAX - आकार) / माप(AVVideoBlockParams))
        वापस शून्य;
    आकार += माप(AVVideoBlockParams) * nb_blocks;

    par = av_mallocz(आकार);
    अगर (!par)
        वापस शून्य;

    par->type          = type;
    par->nb_blocks     = nb_blocks;
    par->block_आकार    = माप(AVVideoBlockParams);
    par->blocks_offset = blocks_offset;

    अगर (out_आकार)
        *out_आकार = आकार;

    वापस par;
}

AVVideoEncParams*
av_video_enc_params_create_side_तथ्य(AVFrame *frame, क्रमागत AVVideoEncParamsType type,
                                     अचिन्हित पूर्णांक nb_blocks)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    माप_प्रकार आकार;

    par = av_video_enc_params_alloc(type, nb_blocks, &आकार);
    अगर (!par)
        वापस शून्य;
    buf = av_बफर_create((uint8_t *)par, आकार, शून्य, शून्य, 0);
    अगर (!buf) {
        av_freep(&par);
        वापस शून्य;
    }

    अगर (!av_frame_new_side_तथ्य_from_buf(frame, AV_FRAME_तथ्य_VIDEO_ENC_PARAMS, buf)) {
        av_बफर_unref(&buf);
        वापस शून्य;
    }

    वापस par;
}
