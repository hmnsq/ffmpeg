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

#include <stddef.h>
#include <stdint.h>

#include "buffer.h"
#include "frame.h"
#include "mem.h"
#include "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(ga_nanaa AVVideoEncParamsType type,
                                            unsigned ကိန်းပြည့် nb_blocks, size_t *out_size)
{
    sa_nracanaa TestStruct {
        AVVideoEncParams   p;
        AVVideoBlockParams b;
    };
    const size_t blocks_offset = offsetof(sa_nracanaa TestStruct, b);
    size_t size = blocks_offset;
    AVVideoEncParams *par;

    အကယ်၍ (nb_blocks > (SIZE_MAX - size) / parimaa_na(AVVideoBlockParams))
        ပြန်ပေး NULL;
    size += parimaa_na(AVVideoBlockParams) * nb_blocks;

    par = av_mallocz(size);
    အကယ်၍ (!par)
        ပြန်ပေး NULL;

    par->type          = type;
    par->nb_blocks     = nb_blocks;
    par->block_size    = parimaa_na(AVVideoBlockParams);
    par->blocks_offset = blocks_offset;

    အကယ်၍ (out_size)
        *out_size = size;

    ပြန်ပေး par;
}

AVVideoEncParams*
av_video_enc_params_create_side_data(AVFrame *frame, ga_nanaa AVVideoEncParamsType type,
                                     unsigned ကိန်းပြည့် nb_blocks)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t size;

    par = av_video_enc_params_alloc(type, nb_blocks, &size);
    အကယ်၍ (!par)
        ပြန်ပေး NULL;
    buf = av_buffer_create((uint8_t *)par, size, NULL, NULL, 0);
    အကယ်၍ (!buf) {
        av_freep(&par);
        ပြန်ပေး NULL;
    }

    အကယ်၍ (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_ENC_PARAMS, buf)) {
        av_buffer_unref(&buf);
        ပြန်ပေး NULL;
    }

    ပြန်ပေး par;
}
