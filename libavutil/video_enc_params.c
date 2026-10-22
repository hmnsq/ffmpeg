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
                                            अचिन्हित पूर्णाङ्क nb_blocks, माप_प्रकार *out_size)
{
    संरचना TestStruct {
        AVVideoEncParams   p;
        AVVideoBlockParams b;
    };
    ध्रुव माप_प्रकार blocks_offset = दुरत्व(संरचना TestStruct, b);
    माप_प्रकार size = blocks_offset;
    AVVideoEncParams *par;

    यदि (nb_blocks > (SIZE_MAX - size) / परिमाण(AVVideoBlockParams))
        प्रत्यागम रिक्त;
    size += परिमाण(AVVideoBlockParams) * nb_blocks;

    par = av_mallocz(size);
    यदि (!par)
        प्रत्यागम रिक्त;

    par->type          = type;
    par->nb_blocks     = nb_blocks;
    par->block_size    = परिमाण(AVVideoBlockParams);
    par->blocks_offset = blocks_offset;

    यदि (out_size)
        *out_size = size;

    प्रत्यागम par;
}

AVVideoEncParams*
av_video_enc_params_create_side_data(AVFrame *frame, गणना AVVideoEncParamsType type,
                                     अचिन्हित पूर्णाङ्क nb_blocks)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    माप_प्रकार size;

    par = av_video_enc_params_alloc(type, nb_blocks, &size);
    यदि (!par)
        प्रत्यागम रिक्त;
    buf = av_buffer_create((uint8_t *)par, size, रिक्त, रिक्त, 0);
    यदि (!buf) {
        av_freep(&par);
        प्रत्यागम रिक्त;
    }

    यदि (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_ENC_PARAMS, buf)) {
        av_buffer_unref(&buf);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम par;
}
