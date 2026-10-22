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

#அந்தர்பாவ "libavutil/log.c"

#அந்தர்பாவ <string.h>

நிலையான முழு call_log_format_line2(மாறிலி எழுத்து *fmt, எழுத்து *buffer, முழு buffer_size, ...)
{
    va_list args;
    முழு ret;
    முழு print_prefix=1;
    va_start(args, buffer_size);
    ret = av_log_format_line2(வெற்று, AV_LOG_INFO, fmt, args, buffer, buffer_size, &print_prefix);
    va_end(args);
    திரும்பு ret;
}

முழு முதன்மை(முழு argc, எழுத்து **argv)
{
    முழு i;
    av_log_set_level(AV_LOG_DEBUG);
    check_color_terminal();
    க்கு (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(வெற்று, AV_LOG_FATAL, "use_color: %d\n", use_color);
        க்கு (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(வெற்று, i, " %d", i);
            av_log(வெற்று, AV_LOG_INFO, "e ");
            av_log(வெற்று, i + 256*123, "C%d", i);
            av_log(வெற்று, AV_LOG_INFO, "e");
        }
        av_log(வெற்று, AV_LOG_PANIC, "\n");
    }
    {
        முழு result;
        எழுத்து buffer[4];
        result = call_log_format_line2("foo", வெற்று, 0);
        எனில்(result != 3) {
            printf("Test NULL buffer failed.\n");
            திரும்பு 1;
        }
        result = call_log_format_line2("foo", buffer, 2);
        எனில்(result != 3 || strncmp(buffer, "f", 2)) {
            printf("Test buffer too small failed.\n");
            திரும்பு 1;
        }
        result = call_log_format_line2("foo", buffer, 4);
        எனில்(result != 3 || strncmp(buffer, "foo", 4)) {
            printf("Test buffer sufficiently big failed.\n");
            திரும்பு 1;
        }
    }
    திரும்பு 0;
}
