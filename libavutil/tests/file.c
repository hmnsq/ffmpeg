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

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ last_log_level = -1;

ಸ್ಥಿರ ಶೂನ್ಯ log_callback(ಶೂನ್ಯ *ctx, ಪೂರ್ಣಾಙ್ಕ level, ಧ್ರುವ ವರ್ಣ *fmt, va_list args)
{
    (ಶೂನ್ಯ)ctx; (ಶೂನ್ಯ)fmt; (ಶೂನ್ಯ)args;
    last_log_level = level;
}

ಪೂರ್ಣಾಙ್ಕ main(ಪೂರ್ಣಾಙ್ಕ argc, ವರ್ಣ **argv)
{
    ಧ್ರುವ ವರ್ಣ *path = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t size;

    av_log_set_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    ಯದಿ (av_file_map(path, &buf, &size, 0, ರಿಕ್ತ) < 0)
        ಪ್ರತ್ಯಾಗಮ 1;
    av_file_unmap(buf, size);
    ಯದಿ (size == 0)
        ಪ್ರತ್ಯಾಗಮ 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 2; i++) {
        last_log_level = -1;
        ಯದಿ (av_file_map("no_such_file_xyz", &buf, &size, i, ರಿಕ್ತ) >= 0) {
            av_file_unmap(buf, size);
            ಪ್ರತ್ಯಾಗಮ 2;
        }
        ಯದಿ (last_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, last_log_level);
            ಪ್ರತ್ಯಾಗಮ 3;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}
