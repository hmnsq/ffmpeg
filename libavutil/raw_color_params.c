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

#അന്തര്ഭാവ "raw_color_params.h"
#അന്തര്ഭാവ "mem.h"

AVRawColorParams *av_raw_color_params_alloc(size_t *size)
{
    AVRawColorParams *p = av_mallocz(വലുപ്പം(AVRawColorParams));
    എങ്കിൽ (!p)
        തിരികെ ശൂന്യ;

    എങ്കിൽ (size)
        *size = വലുപ്പം(*p);

    തിരികെ p;
}

AVRawColorParams *av_raw_color_params_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data =
        av_frame_new_side_data(frame, AV_FRAME_DATA_RAW_COLOR_PARAMS,
                               വലുപ്പം(AVRawColorParams));
    എങ്കിൽ (!side_data)
        തിരികെ ശൂന്യ;

    memset(side_data->data, 0, side_data->size);

    തിരികെ (AVRawColorParams *)side_data->data;
}
