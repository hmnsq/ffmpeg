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
                                            unsigned পূর্ণসংখ্যা nb_blocks, size_t *out_আকার)
{
    কাঠামো TestStruct {
        AVVideoEncParams   p;
        AVVideoBlockParams b;
    };
    ধ্রুবক size_t blocks_offset = offsetof(কাঠামো TestStruct, b);
    size_t আকার_2 = blocks_offset;
    AVVideoEncParams *par;

    যদি (nb_blocks > (SIZE_MAX - আকার_2) / আকার(AVVideoBlockParams))
        ফেরত ফাঁকা;
    আকার_2 += আকার(AVVideoBlockParams) * nb_blocks;

    par = av_mallocz(আকার_2);
    যদি (!par)
        ফেরত ফাঁকা;

    par->type          = type;
    par->nb_blocks     = nb_blocks;
    par->block_আকার    = আকার(AVVideoBlockParams);
    par->blocks_offset = blocks_offset;

    যদি (out_আকার)
        *out_আকার = আকার_2;

    ফেরত par;
}

AVVideoEncParams*
av_video_enc_params_create_side_তথ্য(AVFrame *frame, গণনা AVVideoEncParamsType type,
                                     unsigned পূর্ণসংখ্যা nb_blocks)
{
    AVBufferRef      *buf;
    AVVideoEncParams *par;
    size_t আকার_2;

    par = av_video_enc_params_alloc(type, nb_blocks, &আকার_2);
    যদি (!par)
        ফেরত ফাঁকা;
    buf = av_বাফার_create((uint8_t *)par, আকার_2, ফাঁকা, ফাঁকা, 0);
    যদি (!buf) {
        av_freep(&par);
        ফেরত ফাঁকা;
    }

    যদি (!av_frame_new_side_তথ্য_from_buf(frame, AV_FRAME_তথ্য_VIDEO_ENC_PARAMS, buf)) {
        av_বাফার_unref(&buf);
        ফেরত ফাঁকা;
    }

    ফেরত par;
}
