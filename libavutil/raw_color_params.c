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

#شامل "raw_color_params.h"
#شامل "mem.h"

AVRawColorParams *av_raw_color_params_alloc(size_t *سائز)
{
    AVRawColorParams *p = av_mallocz(حجم(AVRawColorParams));
    اگر (!p)
        واپس تہی;

    اگر (سائز)
        *سائز = حجم(*p);

    واپس p;
}

AVRawColorParams *av_raw_color_params_create_side_ڈیٹا(AVFrame *چوکھٹا)
{
    AVFrame_Side_ڈیٹا *side_ڈیٹا =
        av_چوکھٹا_new_side_ڈیٹا(چوکھٹا, AV_چوکھٹا_ڈیٹا_RAW_COLOR_PARAMS,
                               حجم(AVRawColorParams));
    اگر (!side_ڈیٹا)
        واپس تہی;

    memset(side_ڈیٹا->ڈیٹا, 0, side_ڈیٹا->سائز);

    واپس (AVRawColorParams *)side_ڈیٹا->ڈیٹا;
}
