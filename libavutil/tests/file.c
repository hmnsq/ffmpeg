/*
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

#అన్తర్భావ <stdarg.h>
#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/file.c"
#అన్తర్భావ "libavutil/log.h"

స్థిర పూర్ణాంకం చివరి_log_level = -1;

స్థిర శూన్య log_callback(శూన్య *ctx, పూర్ణాంకం level, స్థిరరాశి అక్షరం *fmt, va_list వాదనలు)
{
    (శూన్య)ctx; (శూన్య)fmt; (శూన్య)వాదనలు;
    చివరి_log_level = level;
}

పూర్ణాంకం ప్రధాన(పూర్ణాంకం argc, అక్షరం **argv)
{
    స్థిరరాశి అక్షరం *మార్గం = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t కొలత;

    av_log_సమితి_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    ఒకవేళ (av_file_map(మార్గం, &buf, &కొలత, 0, ఖాళీ) < 0)
        తిరిగి 1;
    av_file_unmap(buf, కొలత);
    ఒకవేళ (కొలత == 0)
        తిరిగి 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    కొరకు (పూర్ణాంకం i = 0; i < 2; i++) {
        చివరి_log_level = -1;
        ఒకవేళ (av_file_map("no_such_file_xyz", &buf, &కొలత, i, ఖాళీ) >= 0) {
            av_file_unmap(buf, కొలత);
            తిరిగి 2;
        }
        ఒకవేళ (చివరి_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, చివరి_log_level);
            తిరిగి 3;
        }
    }

    తిరిగి 0;
}
