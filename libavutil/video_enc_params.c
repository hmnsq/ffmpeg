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

#ଅନ୍ତର୍ଭାଵ <stddef.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>

#ଅନ୍ତର୍ଭାଵ "buffer.h"
#ଅନ୍ତର୍ଭାଵ "frame.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(ଗଣନା AVVideoEncParamsType type,
                                            unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_blocks, size_t *out_size)
{
    ସଂରଚନା TestStruct {
        AVVideoEncParams   p;
        AVVideoBlockParams b;
    };
    ଅଚଳ size_t blocks_offset = offsetof(ସଂରଚନା TestStruct, b);
    size_t size = blocks_offset;
    AVVideoEncParams *par;

    ଯଦି (nb_blocks > (SIZE_MAX - size) / ଆକାର(AVVideoBlockParams))
        ଫେରନ୍ତୁ ଖାଲି;
    size += ଆକାର(AVVideoBlockParams) * nb_blocks;

    par = av_mallocz(size);
    ଯଦି (!par)
        ଫେରନ୍ତୁ ଖାଲି;

    par->type          = type;
    par->nb_blocks     = nb_blocks;
    par->block_size    = ଆକାର(AVVideoBlockParams);
    par->blocks_offset = blocks_offset;

    ଯଦି (out_size)
        *out_size = size;

    ଫେରନ୍ତୁ par;
}

AVVideoEncParams*
av_video_enc_params_create_side_data(AVFrame *frame, ଗଣନା AVVideoEncParamsType type,
                                     unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_blocks)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t size;

    par = av_video_enc_params_alloc(type, nb_blocks, &size);
    ଯଦି (!par)
        ଫେରନ୍ତୁ ଖାଲି;
    buf = av_buffer_create((uint8_t *)par, size, ଖାଲି, ଖାଲି, 0);
    ଯଦି (!buf) {
        av_freep(&par);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_ENC_PARAMS, buf)) {
        av_buffer_unref(&buf);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ par;
}
