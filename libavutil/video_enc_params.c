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

#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <stdint.h>

#অন্তর্ভাব "buffer.h"
#অন্তর্ভাব "frame.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(গণনা AVVideoEncParamsType type,
                                            unsigned পূর্ণাঙ্ক nb_blocks, size_t *out_size)
{
    সংরচনা TestStruct {
        AVVideoEncParams   p;
        AVVideoBlockParams b;
    };
    ধ্রুব size_t blocks_offset = offsetof(সংরচনা TestStruct, b);
    size_t size = blocks_offset;
    AVVideoEncParams *par;

    যদি (nb_blocks > (SIZE_MAX - size) / পরিমাণ(AVVideoBlockParams))
        প্রত্যাগম রিক্ত;
    size += পরিমাণ(AVVideoBlockParams) * nb_blocks;

    par = av_mallocz(size);
    যদি (!par)
        প্রত্যাগম রিক্ত;

    par->type          = type;
    par->nb_blocks     = nb_blocks;
    par->block_size    = পরিমাণ(AVVideoBlockParams);
    par->blocks_offset = blocks_offset;

    যদি (out_size)
        *out_size = size;

    প্রত্যাগম par;
}

AVVideoEncParams*
av_video_enc_params_create_side_data(AVFrame *frame, গণনা AVVideoEncParamsType type,
                                     unsigned পূর্ণাঙ্ক nb_blocks)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t size;

    par = av_video_enc_params_alloc(type, nb_blocks, &size);
    যদি (!par)
        প্রত্যাগম রিক্ত;
    buf = av_buffer_create((uint8_t *)par, size, রিক্ত, রিক্ত, 0);
    যদি (!buf) {
        av_freep(&par);
        প্রত্যাগম রিক্ত;
    }

    যদি (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_ENC_PARAMS, buf)) {
        av_buffer_unref(&buf);
        প্রত্যাগম রিক্ত;
    }

    প্রত্যাগম par;
}
