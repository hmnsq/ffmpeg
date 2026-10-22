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

#شامل <stdarg.h>
#شامل <stdio.h>

#شامل "libavutil/file.c"
#شامل "libavutil/log.h"

ایستا صحیح last_log_level = -1;

ایستا تهی log_callback(تهی *ctx, صحیح level, ثابت نویسه *fmt, va_list args)
{
    (تهی)ctx; (تهی)fmt; (تهی)args;
    last_log_level = level;
}

صحیح اصلی(صحیح argc, نویسه **argv)
{
    ثابت نویسه *path = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t size;

    av_log_set_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    اگر (av_file_map(path, &buf, &size, 0, پوچ) < 0)
        بازگشت 1;
    av_file_unmap(buf, size);
    اگر (size == 0)
        بازگشت 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    برای (صحیح i = 0; i < 2; i++) {
        last_log_level = -1;
        اگر (av_file_map("no_such_file_xyz", &buf, &size, i, پوچ) >= 0) {
            av_file_unmap(buf, size);
            بازگشت 2;
        }
        اگر (last_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, last_log_level);
            بازگشت 3;
        }
    }

    بازگشت 0;
}
