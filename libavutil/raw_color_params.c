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

#அந்தர்பாவ "raw_color_params.h"
#அந்தர்பாவ "mem.h"

AVRawColorParams *av_raw_color_params_alloc(size_t *size)
{
    AVRawColorParams *p = av_mallocz(அளவு(AVRawColorParams));
    எனில் (!p)
        திரும்பு வெற்று;

    எனில் (size)
        *size = அளவு(*p);

    திரும்பு p;
}

AVRawColorParams *av_raw_color_params_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data =
        av_frame_new_side_data(frame, AV_FRAME_DATA_RAW_COLOR_PARAMS,
                               அளவு(AVRawColorParams));
    எனில் (!side_data)
        திரும்பு வெற்று;

    memset(side_data->data, 0, side_data->size);

    திரும்பு (AVRawColorParams *)side_data->data;
}
