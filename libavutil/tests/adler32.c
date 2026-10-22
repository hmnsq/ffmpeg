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

#अन्तर्भाव "libavutil/timer.h"

#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/log.h"
#अन्तर्भाव "libavutil/adler32.h"

#परिभाषय LEN 7001

पूर्णाङ्क मुख्यम्(पूर्णाङ्क argc, वर्ण **argv)
{
    पूर्णाङ्क i;
    uint8_t दत्त[LEN];
    AVAdler checksum;

    av_log_समुच्चयः_level(AV_LOG_DEBUG);

    प्रति (i = 0; i < LEN; i++)
        दत्त[i] = ((i * i) >> 3) + 123 * i;

    यदि (argc > 1 && !वाक्यं_तुलय(argv[1], "-t")) {
        प्रति (i = 0; i < 1000; i++) {
            START_TIMER;
            checksum = av_adler32_update(1, दत्त, LEN);
            STOP_TIMER("adler");
        }
    } अन्यथा {
        checksum = av_adler32_update(1, दत्त, LEN);
    }

    av_log(रिक्त, AV_LOG_DEBUG, "%X (expected 50E6E508)\n", checksum);
    प्रत्यागम checksum == 0x50e6e508 ? 0 : 1;
}
// LCOV_EXCL_STOP
