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

#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/file.c"
#ಅನ್ತರ್ಭಾವ "libavutil/log.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಕೊನೆಯ_log_level = -1;

ಸ್ಥಿರ ಶೂನ್ಯ log_callback(ಶೂನ್ಯ *ctx, ಪೂರ್ಣಾಂಕ level, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *fmt, va_list ವಾದಗಳು)
{
    (ಶೂನ್ಯ)ctx; (ಶೂನ್ಯ)fmt; (ಶೂನ್ಯ)ವಾದಗಳು;
    ಕೊನೆಯ_log_level = level;
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ **argv)
{
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t ಗಾತ್ರ_2;

    av_log_ಗಣ_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    ಆದರೆ (av_file_map(ಮಾರ್ಗ, &buf, &ಗಾತ್ರ_2, 0, ಖಾಲಿ) < 0)
        ಹಿಂತಿರುಗಿ 1;
    av_file_unmap(buf, ಗಾತ್ರ_2);
    ಆದರೆ (ಗಾತ್ರ_2 == 0)
        ಹಿಂತಿರುಗಿ 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 2; i++) {
        ಕೊನೆಯ_log_level = -1;
        ಆದರೆ (av_file_map("no_such_file_xyz", &buf, &ಗಾತ್ರ_2, i, ಖಾಲಿ) >= 0) {
            av_file_unmap(buf, ಗಾತ್ರ_2);
            ಹಿಂತಿರುಗಿ 2;
        }
        ಆದರೆ (ಕೊನೆಯ_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, ಕೊನೆಯ_log_level);
            ಹಿಂತಿರುಗಿ 3;
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}
