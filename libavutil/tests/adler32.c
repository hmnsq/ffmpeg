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

// LCOV_EXCL_START

#అన్తర్భావ "libavutil/timer.h"

#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/log.h"
#అన్తర్భావ "libavutil/adler32.h"

#నిర్వచించు LEN 7001

పూర్ణాంకం ప్రధాన(పూర్ణాంకం argc, అక్షరం **argv)
{
    పూర్ణాంకం i;
    uint8_t దత్తాంశం[LEN];
    AVAdler checksum;

    av_log_సమితి_level(AV_LOG_DEBUG);

    కొరకు (i = 0; i < LEN; i++)
        దత్తాంశం[i] = ((i * i) >> 3) + 123 * i;

    ఒకవేళ (argc > 1 && !strcmp(argv[1], "-t")) {
        కొరకు (i = 0; i < 1000; i++) {
            ప్రారంభం_TIMER;
            checksum = av_adler32_update(1, దత్తాంశం, LEN);
            STOP_TIMER("adler");
        }
    } లేకపోతే {
        checksum = av_adler32_update(1, దత్తాంశం, LEN);
    }

    av_log(ఖాళీ, AV_LOG_DEBUG, "%X (expected 50E6E508)\n", checksum);
    తిరిగి checksum == 0x50e6e508 ? 0 : 1;
}
// LCOV_EXCL_STOP
