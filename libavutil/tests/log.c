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

#समावेश "libavutil/log.c"

#समावेश <string.h>

अटल पूर्णांक call_log_format_line2(स्थिर अक्षर *fmt, अक्षर *बफर, पूर्णांक बफर_आकार, ...)
{
    बहु_सूची args;
    पूर्णांक ret;
    पूर्णांक print_prefix=1;
    बहु_शुरू(args, बफर_आकार);
    ret = av_log_format_line2(शून्य, AV_LOG_INFO, fmt, args, बफर, बफर_आकार, &print_prefix);
    बहु_पूर्ण(args);
    वापस ret;
}

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
{
    पूर्णांक i;
    av_log_set_level(AV_LOG_DEBUG);
    check_color_terminal();
    क्रम (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(शून्य, AV_LOG_FATAL, "use_color: %d\n", use_color);
        क्रम (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(शून्य, i, " %d", i);
            av_log(शून्य, AV_LOG_INFO, "e ");
            av_log(शून्य, i + 256*123, "C%d", i);
            av_log(शून्य, AV_LOG_INFO, "e");
        }
        av_log(शून्य, AV_LOG_PANIC, "\n");
    }
    {
        पूर्णांक परिणाम;
        अक्षर बफर[4];
        परिणाम = call_log_format_line2("foo", शून्य, 0);
        अगर(परिणाम != 3) {
            म_लिखो("Test NULL buffer failed.\n");
            वापस 1;
        }
        परिणाम = call_log_format_line2("foo", बफर, 2);
        अगर(परिणाम != 3 || म_भेदन(बफर, "f", 2)) {
            म_लिखो("Test buffer too small failed.\n");
            वापस 1;
        }
        परिणाम = call_log_format_line2("foo", बफर, 4);
        अगर(परिणाम != 3 || म_भेदन(बफर, "foo", 4)) {
            म_लिखो("Test buffer sufficiently big failed.\n");
            वापस 1;
        }
    }
    वापस 0;
}
