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

#شامل "libavutil/log.c"

#شامل <string.h>

ساکن صحیح call_log_format_line2(ثابت حرف *fmt, حرف *بفر, صحیح بفر_سائز, ...)
{
    va_list دلائل;
    صحیح ret;
    صحیح print_سابقہ=1;
    va_start(دلائل, بفر_سائز);
    ret = av_log_format_line2(تہی, AV_LOG_INFO, fmt, دلائل, بفر, بفر_سائز, &print_سابقہ);
    va_end(دلائل);
    واپس ret;
}

صحیح مین(صحیح argc, حرف **argv)
{
    صحیح i;
    av_log_سیٹ_level(AV_LOG_DEBUG);
    check_color_terminal();
    برائے (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(تہی, AV_LOG_FATAL, "use_color: %d\n", use_color);
        برائے (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(تہی, i, " %d", i);
            av_log(تہی, AV_LOG_INFO, "e ");
            av_log(تہی, i + 256*123, "C%d", i);
            av_log(تہی, AV_LOG_INFO, "e");
        }
        av_log(تہی, AV_LOG_PANIC, "\n");
    }
    {
        صحیح نتیجہ;
        حرف بفر[4];
        نتیجہ = call_log_format_line2("foo", تہی, 0);
        اگر(نتیجہ != 3) {
            لکھو("Test NULL buffer failed.\n");
            واپس 1;
        }
        نتیجہ = call_log_format_line2("foo", بفر, 2);
        اگر(نتیجہ != 3 || لڑی_موازنہ(بفر, "f", 2)) {
            لکھو("Test buffer too small failed.\n");
            واپس 1;
        }
        نتیجہ = call_log_format_line2("foo", بفر, 4);
        اگر(نتیجہ != 3 || لڑی_موازنہ(بفر, "foo", 4)) {
            لکھو("Test buffer sufficiently big failed.\n");
            واپس 1;
        }
    }
    واپس 0;
}
