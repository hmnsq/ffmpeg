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

#अन्तर्भाव "raw_color_params.h"
#अन्तर्भाव "mem.h"

AVRawColorParams *av_raw_color_params_alloc(size_t *आकार)
{
    AVRawColorParams *p = av_mallocz(परिमाण(AVRawColorParams));
    यदि (!p)
        प्रत्यागम रिक्त;

    यदि (आकार)
        *आकार = परिमाण(*p);

    प्रत्यागम p;
}

AVRawColorParams *av_raw_color_params_create_side_दत्त(AVFrame *frame)
{
    AVFrame_Side_दत्त *side_दत्त =
        av_frame_new_side_दत्त(frame, AV_FRAME_दत्त_RAW_COLOR_PARAMS,
                               परिमाण(AVRawColorParams));
    यदि (!side_दत्त)
        प्रत्यागम रिक्त;

    स्मृतिं_पूरय(side_दत्त->दत्त, 0, side_दत्त->आकार);

    प्रत्यागम (AVRawColorParams *)side_दत्त->दत्त;
}
