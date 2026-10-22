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

#ضمن "raw_color_params.h"
#ضمن "mem.h"

AVRawColorParams *av_raw_color_params_alloc(size_t *سائيز)
{
    AVRawColorParams *p = av_mallocz(حجم(AVRawColorParams));
    إذا (!p)
        أرجع عدم;

    إذا (سائيز)
        *سائيز = حجم(*p);

    أرجع p;
}

AVRawColorParams *av_raw_color_params_create_side_معلومات(AVFrame *چوکٺو)
{
    AVFrame_Side_معلومات *side_معلومات =
        av_چوکٺو_new_side_معلومات(چوکٺو, AV_چوکٺو_معلومات_RAW_COLOR_PARAMS,
                               حجم(AVRawColorParams));
    إذا (!side_معلومات)
        أرجع عدم;

    memset(side_معلومات->معلومات, 0, side_معلومات->سائيز);

    أرجع (AVRawColorParams *)side_معلومات->معلومات;
}
