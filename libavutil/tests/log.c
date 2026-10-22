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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/log.c"

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

ਸਥਿਰ ਪੂਰਨ call_log_format_line2(ਅਚਲ ਅੱਖਰ *fmt, ਅੱਖਰ *ਬਫਰ, ਪੂਰਨ ਬਫਰ_ਮਾਪ, ...)
{
    va_list ਦਲੀਲਾਂ;
    ਪੂਰਨ ret;
    ਪੂਰਨ print_ਅਗੇਤਰ=1;
    va_start(ਦਲੀਲਾਂ, ਬਫਰ_ਮਾਪ);
    ret = av_log_format_line2(ਨਿਰਾ, AV_LOG_INFO, fmt, ਦਲੀਲਾਂ, ਬਫਰ, ਬਫਰ_ਮਾਪ, &print_ਅਗੇਤਰ);
    va_end(ਦਲੀਲਾਂ);
    ਵਾਪਸ ret;
}

ਪੂਰਨ ਮੁੱਖ(ਪੂਰਨ argc, ਅੱਖਰ **argv)
{
    ਪੂਰਨ i;
    av_log_ਸੈੱਟ_level(AV_LOG_DEBUG);
    check_color_terminal();
    ਲਈ (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(ਨਿਰਾ, AV_LOG_FATAL, "use_color: %d\n", use_color);
        ਲਈ (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(ਨਿਰਾ, i, " %d", i);
            av_log(ਨਿਰਾ, AV_LOG_INFO, "e ");
            av_log(ਨਿਰਾ, i + 256*123, "C%d", i);
            av_log(ਨਿਰਾ, AV_LOG_INFO, "e");
        }
        av_log(ਨਿਰਾ, AV_LOG_PANIC, "\n");
    }
    {
        ਪੂਰਨ ਨਤੀਜਾ;
        ਅੱਖਰ ਬਫਰ[4];
        ਨਤੀਜਾ = call_log_format_line2("foo", ਨਿਰਾ, 0);
        ਜੇ(ਨਤੀਜਾ != 3) {
            ਲਿਖੋ("Test NULL buffer failed.\n");
            ਵਾਪਸ 1;
        }
        ਨਤੀਜਾ = call_log_format_line2("foo", ਬਫਰ, 2);
        ਜੇ(ਨਤੀਜਾ != 3 || ਲੜੀ_ਤੁਲਨਾ(ਬਫਰ, "f", 2)) {
            ਲਿਖੋ("Test buffer too small failed.\n");
            ਵਾਪਸ 1;
        }
        ਨਤੀਜਾ = call_log_format_line2("foo", ਬਫਰ, 4);
        ਜੇ(ਨਤੀਜਾ != 3 || ਲੜੀ_ਤੁਲਨਾ(ਬਫਰ, "foo", 4)) {
            ਲਿਖੋ("Test buffer sufficiently big failed.\n");
            ਵਾਪਸ 1;
        }
    }
    ਵਾਪਸ 0;
}
