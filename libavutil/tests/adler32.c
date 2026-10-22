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

#شامل "libavutil/timer.h"

#شامل <string.h>

#شامل "libavutil/log.h"
#شامل "libavutil/adler32.h"

#تعریف_کرو LEN 7001

صحیح مین(صحیح argc, حرف **argv)
{
    صحیح i;
    uint8_t ڈیٹا[LEN];
    AVAdler checksum;

    av_log_سیٹ_level(AV_LOG_DEBUG);

    برائے (i = 0; i < LEN; i++)
        ڈیٹا[i] = ((i * i) >> 3) + 123 * i;

    اگر (argc > 1 && !strcmp(argv[1], "-t")) {
        برائے (i = 0; i < 1000; i++) {
            آغاز_TIMER;
            checksum = av_adler32_update(1, ڈیٹا, LEN);
            STOP_TIMER("adler");
        }
    } ورنہ {
        checksum = av_adler32_update(1, ڈیٹا, LEN);
    }

    av_log(تہی, AV_LOG_DEBUG, "%X (expected 50E6E508)\n", checksum);
    واپس checksum == 0x50e6e508 ? 0 : 1;
}
// LCOV_EXCL_STOP
