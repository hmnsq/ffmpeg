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

#અન્તર્ભાવ "libavutil/log.c"

#અન્તર્ભાવ <string.h>

સ્થિર પૂર્ણાંક call_log_format_line2(અચલ અક્ષર *fmt, અક્ષર *buffer, પૂર્ણાંક buffer_size, ...)
{
    va_list args;
    પૂર્ણાંક ret;
    પૂર્ણાંક print_prefix=1;
    va_start(args, buffer_size);
    ret = av_log_format_line2(ખાલી, AV_LOG_INFO, fmt, args, buffer, buffer_size, &print_prefix);
    va_end(args);
    પાછા ret;
}

પૂર્ણાંક મુખ્ય(પૂર્ણાંક argc, અક્ષર **argv)
{
    પૂર્ણાંક i;
    av_log_set_level(AV_LOG_DEBUG);
    check_color_terminal();
    માટે (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(ખાલી, AV_LOG_FATAL, "use_color: %d\n", use_color);
        માટે (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(ખાલી, i, " %d", i);
            av_log(ખાલી, AV_LOG_INFO, "e ");
            av_log(ખાલી, i + 256*123, "C%d", i);
            av_log(ખાલી, AV_LOG_INFO, "e");
        }
        av_log(ખાલી, AV_LOG_PANIC, "\n");
    }
    {
        પૂર્ણાંક result;
        અક્ષર buffer[4];
        result = call_log_format_line2("foo", ખાલી, 0);
        જો(result != 3) {
            printf("Test NULL buffer failed.\n");
            પાછા 1;
        }
        result = call_log_format_line2("foo", buffer, 2);
        જો(result != 3 || strncmp(buffer, "f", 2)) {
            printf("Test buffer too small failed.\n");
            પાછા 1;
        }
        result = call_log_format_line2("foo", buffer, 4);
        જો(result != 3 || strncmp(buffer, "foo", 4)) {
            printf("Test buffer sufficiently big failed.\n");
            પાછા 1;
        }
    }
    પાછા 0;
}
