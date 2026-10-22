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

#అన్తర్భావ "raw_color_params.h"
#అన్తర్భావ "mem.h"

AVRawColorParams *av_raw_color_params_alloc(size_t *కొలత)
{
    AVRawColorParams *p = av_mallocz(పరిమాణం(AVRawColorParams));
    ఒకవేళ (!p)
        తిరిగి ఖాళీ;

    ఒకవేళ (కొలత)
        *కొలత = పరిమాణం(*p);

    తిరిగి p;
}

AVRawColorParams *av_raw_color_params_create_side_దత్తాంశం(AVFrame *చట్రం)
{
    AVFrame_Side_దత్తాంశం *side_దత్తాంశం =
        av_చట్రం_new_side_దత్తాంశం(చట్రం, AV_చట్రం_దత్తాంశం_RAW_COLOR_PARAMS,
                               పరిమాణం(AVRawColorParams));
    ఒకవేళ (!side_దత్తాంశం)
        తిరిగి ఖాళీ;

    memset(side_దత్తాంశం->దత్తాంశం, 0, side_దత్తాంశం->కొలత);

    తిరిగి (AVRawColorParams *)side_దత్తాంశం->దత్తాంశం;
}
