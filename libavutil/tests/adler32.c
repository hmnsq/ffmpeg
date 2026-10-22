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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/timer.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/adler32.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LEN 7001

ਪੂਰਨ ਮੁੱਖ(ਪੂਰਨ argc, ਅੱਖਰ **argv)
{
    ਪੂਰਨ i;
    uint8_t ਅੰਕੜੇ[LEN];
    AVAdler checksum;

    av_log_ਸੈੱਟ_level(AV_LOG_DEBUG);

    ਲਈ (i = 0; i < LEN; i++)
        ਅੰਕੜੇ[i] = ((i * i) >> 3) + 123 * i;

    ਜੇ (argc > 1 && !strcmp(argv[1], "-t")) {
        ਲਈ (i = 0; i < 1000; i++) {
            ਸ਼ੁਰੂ_TIMER;
            checksum = av_adler32_update(1, ਅੰਕੜੇ, LEN);
            STOP_TIMER("adler");
        }
    } ਨਹੀਂਤਾਂ {
        checksum = av_adler32_update(1, ਅੰਕੜੇ, LEN);
    }

    av_log(ਨਿਰਾ, AV_LOG_DEBUG, "%X (expected 50E6E508)\n", checksum);
    ਵਾਪਸ checksum == 0x50e6e508 ? 0 : 1;
}
// LCOV_EXCL_STOP
