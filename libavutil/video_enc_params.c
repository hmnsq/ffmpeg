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
                                            unsigned صحيح nb_blocks, size_t *out_size)
{
    بنية TestStruct {
        AVVideoEncParams   p;
        AVVideoBlockParams b;
    };
    ثابت size_t blocks_offset = offsetof(بنية TestStruct, b);
    size_t size = blocks_offset;
    AVVideoEncParams *par;

    إذا (nb_blocks > (SIZE_MAX - size) / حجم(AVVideoBlockParams))
        إرجاع عدم;
    size += حجم(AVVideoBlockParams) * nb_blocks;

    par = av_mallocz(size);
    إذا (!par)
        إرجاع عدم;

    par->type          = type;
    par->nb_blocks     = nb_blocks;
    par->block_size    = حجم(AVVideoBlockParams);
    par->blocks_offset = blocks_offset;

    إذا (out_size)
        *out_size = size;

    إرجاع par;
}

AVVideoEncParams*
av_video_enc_params_create_side_data(AVFrame *frame, تعداد AVVideoEncParamsType type,
                                     unsigned صحيح nb_blocks)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t size;

    par = av_video_enc_params_alloc(type, nb_blocks, &size);
    إذا (!par)
        إرجاع عدم;
    buf = av_buffer_create((uint8_t *)par, size, عدم, عدم, 0);
    إذا (!buf) {
        av_freep(&par);
        إرجاع عدم;
    }

    إذا (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_ENC_PARAMS, buf)) {
        av_buffer_unref(&buf);
        إرجاع عدم;
    }

    إرجاع par;
}
