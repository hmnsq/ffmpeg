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

#അന്തര്ഭാവ "libavutil/log.c"

#അന്തര്ഭാവ <string.h>

സ്ഥിതം പൂർണ്ണസംഖ്യ call_log_format_line2(സ്ഥിരം അക്ഷരം *fmt, അക്ഷരം *buffer, പൂർണ്ണസംഖ്യ buffer_size, ...)
{
    va_list args;
    പൂർണ്ണസംഖ്യ ret;
    പൂർണ്ണസംഖ്യ print_prefix=1;
    va_start(args, buffer_size);
    ret = av_log_format_line2(ശൂന്യ, AV_LOG_INFO, fmt, args, buffer, buffer_size, &print_prefix);
    va_end(args);
    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ പ്രധാന(പൂർണ്ണസംഖ്യ argc, അക്ഷരം **argv)
{
    പൂർണ്ണസംഖ്യ i;
    av_log_set_level(AV_LOG_DEBUG);
    check_color_terminal();
    വേണ്ടി (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(ശൂന്യ, AV_LOG_FATAL, "use_color: %d\n", use_color);
        വേണ്ടി (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(ശൂന്യ, i, " %d", i);
            av_log(ശൂന്യ, AV_LOG_INFO, "e ");
            av_log(ശൂന്യ, i + 256*123, "C%d", i);
            av_log(ശൂന്യ, AV_LOG_INFO, "e");
        }
        av_log(ശൂന്യ, AV_LOG_PANIC, "\n");
    }
    {
        പൂർണ്ണസംഖ്യ result;
        അക്ഷരം buffer[4];
        result = call_log_format_line2("foo", ശൂന്യ, 0);
        എങ്കിൽ(result != 3) {
            printf("Test NULL buffer failed.\n");
            തിരികെ 1;
        }
        result = call_log_format_line2("foo", buffer, 2);
        എങ്കിൽ(result != 3 || strncmp(buffer, "f", 2)) {
            printf("Test buffer too small failed.\n");
            തിരികെ 1;
        }
        result = call_log_format_line2("foo", buffer, 4);
        എങ്കിൽ(result != 3 || strncmp(buffer, "foo", 4)) {
            printf("Test buffer sufficiently big failed.\n");
            തിരികെ 1;
        }
    }
    തിരികെ 0;
}
