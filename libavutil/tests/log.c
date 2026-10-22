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

स्थिर पूर्णाङ्क call_log_format_line2(ध्रुव वर्ण *fmt, वर्ण *बफर, पूर्णाङ्क बफर_आकार, ...)
{
    va_list तर्काः;
    पूर्णाङ्क ret;
    पूर्णाङ्क print_उपसर्गः=1;
    va_start(तर्काः, बफर_आकार);
    ret = av_log_format_line2(रिक्त, AV_LOG_INFO, fmt, तर्काः, बफर, बफर_आकार, &print_उपसर्गः);
    va_end(तर्काः);
    प्रत्यागम ret;
}

पूर्णाङ्क मुख्यम्(पूर्णाङ्क argc, वर्ण **argv)
{
    पूर्णाङ्क i;
    av_log_समुच्चयः_level(AV_LOG_DEBUG);
    check_color_terminal();
    प्रति (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(रिक्त, AV_LOG_FATAL, "use_color: %d\n", use_color);
        प्रति (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(रिक्त, i, " %d", i);
            av_log(रिक्त, AV_LOG_INFO, "e ");
            av_log(रिक्त, i + 256*123, "C%d", i);
            av_log(रिक्त, AV_LOG_INFO, "e");
        }
        av_log(रिक्त, AV_LOG_PANIC, "\n");
    }
    {
        पूर्णाङ्क परिणाम;
        वर्ण बफर[4];
        परिणाम = call_log_format_line2("foo", रिक्त, 0);
        यदि(परिणाम != 3) {
            प्रारूप_लिख("Test NULL buffer failed.\n");
            प्रत्यागम 1;
        }
        परिणाम = call_log_format_line2("foo", बफर, 2);
        यदि(परिणाम != 3 || वाक्ये_तुलय(बफर, "f", 2)) {
            प्रारूप_लिख("Test buffer too small failed.\n");
            प्रत्यागम 1;
        }
        परिणाम = call_log_format_line2("foo", बफर, 4);
        यदि(परिणाम != 3 || वाक्ये_तुलय(बफर, "foo", 4)) {
            प्रारूप_लिख("Test buffer sufficiently big failed.\n");
            प्रत्यागम 1;
        }
    }
    प्रत्यागम 0;
}
