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

#అన్తర్భావ "libavutil/log.c"

#అన్తర్భావ <string.h>

స్థిర పూర్ణాంకం call_log_format_line2(స్థిరరాశి అక్షరం *fmt, అక్షరం *బఫరు, పూర్ణాంకం బఫరు_కొలత, ...)
{
    va_list వాదనలు;
    పూర్ణాంకం ret;
    పూర్ణాంకం print_ఉపసర్గ=1;
    va_start(వాదనలు, బఫరు_కొలత);
    ret = av_log_format_line2(ఖాళీ, AV_LOG_INFO, fmt, వాదనలు, బఫరు, బఫరు_కొలత, &print_ఉపసర్గ);
    va_end(వాదనలు);
    తిరిగి ret;
}

పూర్ణాంకం ప్రధాన(పూర్ణాంకం argc, అక్షరం **argv)
{
    పూర్ణాంకం i;
    av_log_సమితి_level(AV_LOG_DEBUG);
    check_color_terminal();
    కొరకు (use_color=0; use_color<=256; use_color = 255*use_color+1) {
        av_log(ఖాళీ, AV_LOG_FATAL, "use_color: %d\n", use_color);
        కొరకు (i = AV_LOG_DEBUG; i>=AV_LOG_QUIET; i-=8) {
            av_log(ఖాళీ, i, " %d", i);
            av_log(ఖాళీ, AV_LOG_INFO, "e ");
            av_log(ఖాళీ, i + 256*123, "C%d", i);
            av_log(ఖాళీ, AV_LOG_INFO, "e");
        }
        av_log(ఖాళీ, AV_LOG_PANIC, "\n");
    }
    {
        పూర్ణాంకం ఫలితం;
        అక్షరం బఫరు[4];
        ఫలితం = call_log_format_line2("foo", ఖాళీ, 0);
        ఒకవేళ(ఫలితం != 3) {
            రాయి("Test NULL buffer failed.\n");
            తిరిగి 1;
        }
        ఫలితం = call_log_format_line2("foo", బఫరు, 2);
        ఒకవేళ(ఫలితం != 3 || అక్షరశ్రేణి_పోలిక(బఫరు, "f", 2)) {
            రాయి("Test buffer too small failed.\n");
            తిరిగి 1;
        }
        ఫలితం = call_log_format_line2("foo", బఫరు, 4);
        ఒకవేళ(ఫలితం != 3 || అక్షరశ్రేణి_పోలిక(బఫరు, "foo", 4)) {
            రాయి("Test buffer sufficiently big failed.\n");
            తిరిగి 1;
        }
    }
    తిరిగి 0;
}
