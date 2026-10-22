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

#অন্তর্ভাৱ "libavutil/log.c"

#অন্তর্ভাৱ <string.h>

স্থির পূর্ণাঙ্ক call_log_format_line2(ধ্রুৱ ৱর্ণ *fmt, ৱর্ণ *buffer, পূর্ণাঙ্ক buffer_size, ...)
{
    va_list args;
    পূর্ণাঙ্ক ret;
    পূর্ণাঙ্ক print_prefix=1;
    va_start(args, buffer_size);
    ret = av_log_format_line2(রিক্ত, AV_LOG_INFO, fmt, args, buffer, buffer_size, &print_prefix);
    va_end(args);
    ঘূৰাই ret;
}

পূর্ণাঙ্ক main(পূর্ণাঙ্ক argc, ৱর্ণ **argv)
{
    পূর্ণাঙ্ক i;
    av_log_set_level(AV_LOG_DEBUG);
    check_color_terminal();
    বাবে (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(রিক্ত, AV_LOG_FATAL, "use_color: %d\n", use_color);
        বাবে (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(রিক্ত, i, " %d", i);
            av_log(রিক্ত, AV_LOG_INFO, "e ");
            av_log(রিক্ত, i + 256*123, "C%d", i);
            av_log(রিক্ত, AV_LOG_INFO, "e");
        }
        av_log(রিক্ত, AV_LOG_PANIC, "\n");
    }
    {
        পূর্ণাঙ্ক result;
        ৱর্ণ buffer[4];
        result = call_log_format_line2("foo", রিক্ত, 0);
        যদি(result != 3) {
            printf("Test NULL buffer failed.\n");
            ঘূৰাই 1;
        }
        result = call_log_format_line2("foo", buffer, 2);
        যদি(result != 3 || strncmp(buffer, "f", 2)) {
            printf("Test buffer too small failed.\n");
            ঘূৰাই 1;
        }
        result = call_log_format_line2("foo", buffer, 4);
        যদি(result != 3 || strncmp(buffer, "foo", 4)) {
            printf("Test buffer sufficiently big failed.\n");
            ঘূৰাই 1;
        }
    }
    ঘূৰাই 0;
}
