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

#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <stdint.h>

#அந்தர்பாவ "buffer.h"
#அந்தர்பாவ "frame.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(எண்ணிக்கை AVVideoEncParamsType type,
                                            unsigned முழு nb_blocks, size_t *out_size)
{
    கட்டமைப்பு TestStruct {
        AVVideoEncParams   p;
        AVVideoBlockParams b;
    };
    மாறிலி size_t blocks_offset = offsetof(கட்டமைப்பு TestStruct, b);
    size_t size = blocks_offset;
    AVVideoEncParams *par;

    எனில் (nb_blocks > (SIZE_MAX - size) / அளவு(AVVideoBlockParams))
        திரும்பு வெற்று;
    size += அளவு(AVVideoBlockParams) * nb_blocks;

    par = av_mallocz(size);
    எனில் (!par)
        திரும்பு வெற்று;

    par->type          = type;
    par->nb_blocks     = nb_blocks;
    par->block_size    = அளவு(AVVideoBlockParams);
    par->blocks_offset = blocks_offset;

    எனில் (out_size)
        *out_size = size;

    திரும்பு par;
}

AVVideoEncParams*
av_video_enc_params_create_side_data(AVFrame *frame, எண்ணிக்கை AVVideoEncParamsType type,
                                     unsigned முழு nb_blocks)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t size;

    par = av_video_enc_params_alloc(type, nb_blocks, &size);
    எனில் (!par)
        திரும்பு வெற்று;
    buf = av_buffer_create((uint8_t *)par, size, வெற்று, வெற்று, 0);
    எனில் (!buf) {
        av_freep(&par);
        திரும்பு வெற்று;
    }

    எனில் (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_ENC_PARAMS, buf)) {
        av_buffer_unref(&buf);
        திரும்பு வெற்று;
    }

    திரும்பு par;
}
