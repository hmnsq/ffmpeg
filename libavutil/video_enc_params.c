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

#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <stdint.h>

#അന്തര്ഭാവ "buffer.h"
#അന്തര്ഭാവ "frame.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "video_enc_params.h"

AVVideoEncParams *av_video_enc_params_alloc(എണ്ണൽ AVVideoEncParamsType type,
                                            unsigned പൂർണ്ണസംഖ്യ nb_blocks, size_t *out_size)
{
    ഘടന TestStruct {
        AVVideoEncParams   p;
        AVVideoBlockParams b;
    };
    സ്ഥിരം size_t blocks_offset = offsetof(ഘടന TestStruct, b);
    size_t size = blocks_offset;
    AVVideoEncParams *par;

    എങ്കിൽ (nb_blocks > (SIZE_MAX - size) / വലുപ്പം(AVVideoBlockParams))
        തിരികെ ശൂന്യ;
    size += വലുപ്പം(AVVideoBlockParams) * nb_blocks;

    par = av_mallocz(size);
    എങ്കിൽ (!par)
        തിരികെ ശൂന്യ;

    par->type          = type;
    par->nb_blocks     = nb_blocks;
    par->block_size    = വലുപ്പം(AVVideoBlockParams);
    par->blocks_offset = blocks_offset;

    എങ്കിൽ (out_size)
        *out_size = size;

    തിരികെ par;
}

AVVideoEncParams*
av_video_enc_params_create_side_data(AVFrame *frame, എണ്ണൽ AVVideoEncParamsType type,
                                     unsigned പൂർണ്ണസംഖ്യ nb_blocks)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t size;

    par = av_video_enc_params_alloc(type, nb_blocks, &size);
    എങ്കിൽ (!par)
        തിരികെ ശൂന്യ;
    buf = av_buffer_create((uint8_t *)par, size, ശൂന്യ, ശൂന്യ, 0);
    എങ്കിൽ (!buf) {
        av_freep(&par);
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_VIDEO_ENC_PARAMS, buf)) {
        av_buffer_unref(&buf);
        തിരികെ ശൂന്യ;
    }

    തിരികെ par;
}
