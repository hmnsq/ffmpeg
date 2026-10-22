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

#অন্তর্ভাব "libavutil/log.c"

#অন্তর্ভাব <string.h>

স্থির পূর্ণসংখ্যা call_log_format_line2(ধ্রুবক অক্ষর *fmt, অক্ষর *বাফার, পূর্ণসংখ্যা বাফার_আকার, ...)
{
    va_list args;
    পূর্ণসংখ্যা ret;
    পূর্ণসংখ্যা print_prefix=1;
    va_start(args, বাফার_আকার);
    ret = av_log_format_line2(ফাঁকা, AV_LOG_INFO, fmt, args, বাফার, বাফার_আকার, &print_prefix);
    va_end(args);
    ফেরত ret;
}

পূর্ণসংখ্যা প্রধান(পূর্ণসংখ্যা argc, অক্ষর **argv)
{
    পূর্ণসংখ্যা i;
    av_log_set_level(AV_LOG_DEBUG);
    check_color_terminal();
    জন্য (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(ফাঁকা, AV_LOG_FATAL, "use_color: %d\n", use_color);
        জন্য (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(ফাঁকা, i, " %d", i);
            av_log(ফাঁকা, AV_LOG_INFO, "e ");
            av_log(ফাঁকা, i + 256*123, "C%d", i);
            av_log(ফাঁকা, AV_LOG_INFO, "e");
        }
        av_log(ফাঁকা, AV_LOG_PANIC, "\n");
    }
    {
        পূর্ণসংখ্যা ফলাফল;
        অক্ষর বাফার[4];
        ফলাফল = call_log_format_line2("foo", ফাঁকা, 0);
        যদি(ফলাফল != 3) {
            printf("Test NULL buffer failed.\n");
            ফেরত 1;
        }
        ফলাফল = call_log_format_line2("foo", বাফার, 2);
        যদি(ফলাফল != 3 || strncmp(বাফার, "f", 2)) {
            printf("Test buffer too small failed.\n");
            ফেরত 1;
        }
        ফলাফল = call_log_format_line2("foo", বাফার, 4);
        যদি(ফলাফল != 3 || strncmp(বাফার, "foo", 4)) {
            printf("Test buffer sufficiently big failed.\n");
            ফেরত 1;
        }
    }
    ফেরত 0;
}
