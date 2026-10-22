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

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "frame.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(ಗಣನಾ AVVideoEncParamsType type,
                                            unsigned ಪೂರ್ಣಾಙ್ಕ nb_blocks, size_t *out_size)
{
    ಸಂರಚನಾ TestStruct {
        AVVideoEncParams   p;
        AVVideoBlockParams b;
    };
    ಧ್ರುವ size_t blocks_offset = offsetof(ಸಂರಚನಾ TestStruct, b);
    size_t size = blocks_offset;
    AVVideoEncParams *par;

    ಯದಿ (nb_blocks > (SIZE_MAX - size) / ಪರಿಮಾಣ(AVVideoBlockParams))
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    size += ಪರಿಮಾಣ(AVVideoBlockParams) * nb_blocks;

    par = av_mallocz(size);
    ಯದಿ (!par)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    par->type          = type;
    par->nb_blocks     = nb_blocks;
    par->block_size    = ಪರಿಮಾಣ(AVVideoBlockParams);
    par->blocks_offset = blocks_offset;

    ಯದಿ (out_size)
        *out_size = size;

    ಪ್ರತ್ಯಾಗಮ par;
}

AVVideoEncParams*
av_video_enc_params_create_side_data(AVFrame *frame, ಗಣನಾ AVVideoEncParamsType type,
                                     unsigned ಪೂರ್ಣಾಙ್ಕ nb_blocks)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t size;

    par = av_video_enc_params_alloc(type, nb_blocks, &size);
    ಯದಿ (!par)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    buf = av_buffer_create((uint8_t *)par, size, ರಿಕ್ತ, ರಿಕ್ತ, 0);
    ಯದಿ (!buf) {
        av_freep(&par);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_ENC_PARAMS, buf)) {
        av_buffer_unref(&buf);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ par;
}
