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

#अन्तर्भाव "libavutil/log.c"

#अन्तर्भाव <string.h>

स्थिर पूर्णाङ्क call_log_format_line2(अचर वर्ण *fmt, वर्ण *buffer, पूर्णाङ्क buffer_size, ...)
{
    बहु_सूची args;
    पूर्णाङ्क ret;
    पूर्णाङ्क print_prefix=1;
    बहु_शुरू(args, buffer_size);
    ret = av_log_format_line2(रिक्त, AV_LOG_INFO, fmt, args, buffer, buffer_size, &print_prefix);
    बहु_पूर्ण(args);
    फर्काऊ ret;
}

पूर्णाङ्क main(पूर्णाङ्क argc, वर्ण **argv)
{
    पूर्णाङ्क i;
    av_log_set_level(AV_LOG_DEBUG);
    check_color_terminal();
    लागि (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(रिक्त, AV_LOG_FATAL, "use_color: %d\n", use_color);
        लागि (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(रिक्त, i, " %d", i);
            av_log(रिक्त, AV_LOG_INFO, "e ");
            av_log(रिक्त, i + 256*123, "C%d", i);
            av_log(रिक्त, AV_LOG_INFO, "e");
        }
        av_log(रिक्त, AV_LOG_PANIC, "\n");
    }
    {
        पूर्णाङ्क result;
        वर्ण buffer[4];
        result = call_log_format_line2("foo", रिक्त, 0);
        यदि(result != 3) {
            म_लिखो("Test NULL buffer failed.\n");
            फर्काऊ 1;
        }
        result = call_log_format_line2("foo", buffer, 2);
        यदि(result != 3 || म_भेदन(buffer, "f", 2)) {
            म_लिखो("Test buffer too small failed.\n");
            फर्काऊ 1;
        }
        result = call_log_format_line2("foo", buffer, 4);
        यदि(result != 3 || म_भेदन(buffer, "foo", 4)) {
            म_लिखो("Test buffer sufficiently big failed.\n");
            फर्काऊ 1;
        }
    }
    फर्काऊ 0;
}
