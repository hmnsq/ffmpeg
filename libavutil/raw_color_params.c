/*
 * Copyright (c) 2026 Lynne <dev@lynne.ee>
 *
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

#অন্তর্ভাব "raw_color_params.h"
#অন্তর্ভাব "mem.h"

AVRawColorParams *av_raw_color_params_alloc(size_t *আকার_2)
{
    AVRawColorParams *p = av_mallocz(আকার(AVRawColorParams));
    যদি (!p)
        ফেরত ফাঁকা;

    যদি (আকার_2)
        *আকার_2 = আকার(*p);

    ফেরত p;
}

AVRawColorParams *av_raw_color_params_create_side_তথ্য(AVFrame *frame)
{
    AVFrame_Side_তথ্য *side_তথ্য =
        av_frame_new_side_তথ্য(frame, AV_FRAME_তথ্য_RAW_COLOR_PARAMS,
                               আকার(AVRawColorParams));
    যদি (!side_তথ্য)
        ফেরত ফাঁকা;

    memset(side_তথ্য->তথ্য, 0, side_তথ্য->আকার_2);

    ফেরত (AVRawColorParams *)side_তথ্য->তথ্য;
}
