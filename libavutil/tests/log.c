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

#ಅನ್ತರ್ಭಾವ "libavutil/log.c"

#ಅನ್ತರ್ಭಾವ <string.h>

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ call_log_format_line2(ಧ್ರುವ ವರ್ಣ *fmt, ವರ್ಣ *buffer, ಪೂರ್ಣಾಙ್ಕ buffer_size, ...)
{
    va_list args;
    ಪೂರ್ಣಾಙ್ಕ ret;
    ಪೂರ್ಣಾಙ್ಕ print_prefix=1;
    va_start(args, buffer_size);
    ret = av_log_format_line2(ರಿಕ್ತ, AV_LOG_INFO, fmt, args, buffer, buffer_size, &print_prefix);
    va_end(args);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ main(ಪೂರ್ಣಾಙ್ಕ argc, ವರ್ಣ **argv)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    av_log_set_level(AV_LOG_DEBUG);
    check_color_terminal();
    ಪ್ರತಿ (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(ರಿಕ್ತ, AV_LOG_FATAL, "use_color: %d\n", use_color);
        ಪ್ರತಿ (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(ರಿಕ್ತ, i, " %d", i);
            av_log(ರಿಕ್ತ, AV_LOG_INFO, "e ");
            av_log(ರಿಕ್ತ, i + 256*123, "C%d", i);
            av_log(ರಿಕ್ತ, AV_LOG_INFO, "e");
        }
        av_log(ರಿಕ್ತ, AV_LOG_PANIC, "\n");
    }
    {
        ಪೂರ್ಣಾಙ್ಕ result;
        ವರ್ಣ buffer[4];
        result = call_log_format_line2("foo", ರಿಕ್ತ, 0);
        ಯದಿ(result != 3) {
            printf("Test NULL buffer failed.\n");
            ಪ್ರತ್ಯಾಗಮ 1;
        }
        result = call_log_format_line2("foo", buffer, 2);
        ಯದಿ(result != 3 || strncmp(buffer, "f", 2)) {
            printf("Test buffer too small failed.\n");
            ಪ್ರತ್ಯಾಗಮ 1;
        }
        result = call_log_format_line2("foo", buffer, 4);
        ಯದಿ(result != 3 || strncmp(buffer, "foo", 4)) {
            printf("Test buffer sufficiently big failed.\n");
            ಪ್ರತ್ಯಾಗಮ 1;
        }
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}
