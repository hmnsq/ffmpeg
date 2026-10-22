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

#समावेश "raw_color_params.h"
#समावेश "mem.h"

AVRawColorParams *av_raw_color_params_alloc(माप_प्रकार *आकार)
{
    AVRawColorParams *p = av_mallocz(माप(AVRawColorParams));
    अगर (!p)
        वापस शून्य;

    अगर (आकार)
        *आकार = माप(*p);

    वापस p;
}

AVRawColorParams *av_raw_color_params_create_side_तथ्य(AVFrame *frame)
{
    AVFrame_Side_तथ्य *side_तथ्य =
        av_frame_new_side_तथ्य(frame, AV_FRAME_तथ्य_RAW_COLOR_PARAMS,
                               माप(AVRawColorParams));
    अगर (!side_तथ्य)
        वापस शून्य;

    स_रखो(side_तथ्य->तथ्य, 0, side_तथ्य->आकार);

    वापस (AVRawColorParams *)side_तथ्य->तथ्य;
}
