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

ساكن صحيح call_log_format_line2(ثابت حرف *fmt, حرف *بفر, صحيح بفر_اندازه, ...)
{
    va_list دلیلونه;
    صحيح ret;
    صحيح print_مختاړی=1;
    va_start(دلیلونه, بفر_اندازه);
    ret = av_log_format_line2(عدم, AV_LOG_INFO, fmt, دلیلونه, بفر, بفر_اندازه, &print_مختاړی);
    va_end(دلیلونه);
    أرجع ret;
}

صحيح اصلي(صحيح argc, حرف **argv)
{
    صحيح i;
    av_log_سېټ_level(AV_LOG_DEBUG);
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
        صحيح پایله;
        حرف بفر[4];
        پایله = call_log_format_line2("foo", عدم, 0);
        إذا(پایله != 3) {
            چاپ_کړه("Test NULL buffer failed.\n");
            أرجع 1;
        }
        پایله = call_log_format_line2("foo", بفر, 2);
        إذا(پایله != 3 || مزي_پرتله(بفر, "f", 2)) {
            چاپ_کړه("Test buffer too small failed.\n");
            أرجع 1;
        }
        پایله = call_log_format_line2("foo", بفر, 4);
        إذا(پایله != 3 || مزي_پرتله(بفر, "foo", 4)) {
            چاپ_کړه("Test buffer sufficiently big failed.\n");
            أرجع 1;
        }
    }
    أرجع 0;
}
