/*
 * log functions
 * Copyright (c) 2003 Michel Bardiaux
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

#ضمن "libavutil/log.c"

#ضمن <string.h>

ساكن صحيح call_log_format_line2(ثابت حرف *fmt, حرف *میانگیر, صحيح میانگیر_اندازه, ...)
{
    va_list آرگومانها;
    صحيح ret;
    صحيح print_پیشوند=1;
    va_start(آرگومانها, میانگیر_اندازه);
    ret = av_log_format_line2(عدم, AV_LOG_INFO, fmt, آرگومانها, میانگیر, میانگیر_اندازه, &print_پیشوند);
    va_end(آرگومانها);
    أرجع ret;
}

صحيح اصلی(صحيح argc, حرف **argv)
{
    صحيح i;
    av_log_مجموعه_level(AV_LOG_DEBUG);
    check_color_terminal();
    لكل (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(عدم, AV_LOG_FATAL, "use_color: %d\n", use_color);
        لكل (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(عدم, i, " %d", i);
            av_log(عدم, AV_LOG_INFO, "e ");
            av_log(عدم, i + 256*123, "C%d", i);
            av_log(عدم, AV_LOG_INFO, "e");
        }
        av_log(عدم, AV_LOG_PANIC, "\n");
    }
    {
        صحيح نتیجه;
        حرف میانگیر[4];
        نتیجه = call_log_format_line2("foo", عدم, 0);
        إذا(نتیجه != 3) {
            چاپ_کن("Test NULL buffer failed.\n");
            أرجع 1;
        }
        نتیجه = call_log_format_line2("foo", میانگیر, 2);
        إذا(نتیجه != 3 || مقایسه_رشته(میانگیر, "f", 2)) {
            چاپ_کن("Test buffer too small failed.\n");
            أرجع 1;
        }
        نتیجه = call_log_format_line2("foo", میانگیر, 4);
        إذا(نتیجه != 3 || مقایسه_رشته(میانگیر, "foo", 4)) {
            چاپ_کن("Test buffer sufficiently big failed.\n");
            أرجع 1;
        }
    }
    أرجع 0;
}
