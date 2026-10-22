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

#include "raw_color_params.h"
#include "mem.h"

AVRawColorParams *av_raw_color_params_alloc(size_t *size)
{
    AVRawColorParams *p = av_mallocz(sizeof(AVRawColorParams));
    如果 (!p)
        返回 NULL;

    如果 (size)
        *size = sizeof(*p);

    返回 p;
}

AVRawColorParams *av_raw_color_params_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data =
        av_frame_new_side_data(frame, AV_FRAME_DATA_RAW_COLOR_PARAMS,
                               sizeof(AVRawColorParams));
    如果 (!side_data)
        返回 NULL;

    memset(side_data->data, 0, side_data->size);

    返回 (AVRawColorParams *)side_data->data;
}
