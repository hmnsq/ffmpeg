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

#ଅନ୍ତର୍ଭାଵ "libavutil/log.c"

#ଅନ୍ତର୍ଭାଵ <string.h>

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା call_log_format_line2(ଅଚଳ ଅକ୍ଷର *fmt, ଅକ୍ଷର *buffer, ପୂର୍ଣ୍ଣସଂଖ୍ୟା buffer_size, ...)
{
    va_list args;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା print_prefix=1;
    va_start(args, buffer_size);
    ret = av_log_format_line2(ଖାଲି, AV_LOG_INFO, fmt, args, buffer, buffer_size, &print_prefix);
    va_end(args);
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc, ଅକ୍ଷର **argv)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    av_log_set_level(AV_LOG_DEBUG);
    check_color_terminal();
    ପାଇଁ (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(ଖାଲି, AV_LOG_FATAL, "use_color: %d\n", use_color);
        ପାଇଁ (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(ଖାଲି, i, " %d", i);
            av_log(ଖାଲି, AV_LOG_INFO, "e ");
            av_log(ଖାଲି, i + 256*123, "C%d", i);
            av_log(ଖାଲି, AV_LOG_INFO, "e");
        }
        av_log(ଖାଲି, AV_LOG_PANIC, "\n");
    }
    {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା result;
        ଅକ୍ଷର buffer[4];
        result = call_log_format_line2("foo", ଖାଲି, 0);
        ଯଦି(result != 3) {
            printf("Test NULL buffer failed.\n");
            ଫେରନ୍ତୁ 1;
        }
        result = call_log_format_line2("foo", buffer, 2);
        ଯଦି(result != 3 || strncmp(buffer, "f", 2)) {
            printf("Test buffer too small failed.\n");
            ଫେରନ୍ତୁ 1;
        }
        result = call_log_format_line2("foo", buffer, 4);
        ଯଦି(result != 3 || strncmp(buffer, "foo", 4)) {
            printf("Test buffer sufficiently big failed.\n");
            ଫେରନ୍ତୁ 1;
        }
    }
    ଫେରନ୍ତୁ 0;
}
