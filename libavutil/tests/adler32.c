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

#ಅನ್ತರ್ಭಾವ "libavutil/timer.h"

#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/log.h"
#ಅನ್ತರ್ಭಾವ "libavutil/adler32.h"

#ವ್ಯಾಖ್ಯಾನಿಸು LEN 7001

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ **argv)
{
    ಪೂರ್ಣಾಂಕ i;
    uint8_t ದತ್ತಾಂಶ[LEN];
    AVAdler checksum;

    av_log_ಗಣ_level(AV_LOG_DEBUG);

    ಗಾಗಿ (i = 0; i < LEN; i++)
        ದತ್ತಾಂಶ[i] = ((i * i) >> 3) + 123 * i;

    ಆದರೆ (argc > 1 && !strcmp(argv[1], "-t")) {
        ಗಾಗಿ (i = 0; i < 1000; i++) {
            ಆರಂಭ_TIMER;
            checksum = av_adler32_update(1, ದತ್ತಾಂಶ, LEN);
            STOP_TIMER("adler");
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        checksum = av_adler32_update(1, ದತ್ತಾಂಶ, LEN);
    }

    av_log(ಖಾಲಿ, AV_LOG_DEBUG, "%X (expected 50E6E508)\n", checksum);
    ಹಿಂತಿರುಗಿ checksum == 0x50e6e508 ? 0 : 1;
}
// LCOV_EXCL_STOP
