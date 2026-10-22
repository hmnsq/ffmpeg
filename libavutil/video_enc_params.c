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

#અન્તર્ભાવ <stddef.h>
#અન્તર્ભાવ <stdint.h>

#અન્તર્ભાવ "buffer.h"
#અન્તર્ભાવ "frame.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(ગણના AVVideoEncParamsType type,
                                            unsigned પૂર્ણાંક nb_blocks, size_t *out_size)
{
    સંરચના TestStruct {
        AVVideoEncParams   p;
        AVVideoBlockParams b;
    };
    અચલ size_t blocks_offset = offsetof(સંરચના TestStruct, b);
    size_t size = blocks_offset;
    AVVideoEncParams *par;

    જો (nb_blocks > (SIZE_MAX - size) / કદ(AVVideoBlockParams))
        પાછા ખાલી;
    size += કદ(AVVideoBlockParams) * nb_blocks;

    par = av_mallocz(size);
    જો (!par)
        પાછા ખાલી;

    par->type          = type;
    par->nb_blocks     = nb_blocks;
    par->block_size    = કદ(AVVideoBlockParams);
    par->blocks_offset = blocks_offset;

    જો (out_size)
        *out_size = size;

    પાછા par;
}

AVVideoEncParams*
av_video_enc_params_create_side_data(AVFrame *frame, ગણના AVVideoEncParamsType type,
                                     unsigned પૂર્ણાંક nb_blocks)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t size;

    par = av_video_enc_params_alloc(type, nb_blocks, &size);
    જો (!par)
        પાછા ખાલી;
    buf = av_buffer_create((uint8_t *)par, size, ખાલી, ખાલી, 0);
    જો (!buf) {
        av_freep(&par);
        પાછા ખાલી;
    }

    જો (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_ENC_PARAMS, buf)) {
        av_buffer_unref(&buf);
        પાછા ખાલી;
    }

    પાછા par;
}
