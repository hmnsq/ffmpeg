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

#অন্তর্ভাব "libavutil/timer.h"

#অন্তর্ভাব <string.h>

#অন্তর্ভাব "libavutil/log.h"
#অন্তর্ভাব "libavutil/adler32.h"

#define LEN 7001

পূর্ণসংখ্যা প্রধান(পূর্ণসংখ্যা argc, অক্ষর **argv)
{
    পূর্ণসংখ্যা i;
    uint8_t তথ্য[LEN];
    AVAdler checksum;

    av_log_set_level(AV_LOG_DEBUG);

    জন্য (i = 0; i < LEN; i++)
        তথ্য[i] = ((i * i) >> 3) + 123 * i;

    যদি (argc > 1 && !strcmp(argv[1], "-t")) {
        জন্য (i = 0; i < 1000; i++) {
            START_TIMER;
            checksum = av_adler32_update(1, তথ্য, LEN);
            STOP_TIMER("adler");
        }
    } অন্যথা {
        checksum = av_adler32_update(1, তথ্য, LEN);
    }

    av_log(ফাঁকা, AV_LOG_DEBUG, "%X (expected 50E6E508)\n", checksum);
    ফেরত checksum == 0x50e6e508 ? 0 : 1;
}
// LCOV_EXCL_STOP
