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

#ضمن <stdarg.h>
#ضمن <stdio.h>

#ضمن "libavutil/file.c"
#ضمن "libavutil/log.h"

ساكن صحيح last_log_level = -1;

ساكن فراغ log_callback(فراغ *ctx, صحيح level, ثابت حرف *fmt, va_list وسائط)
{
    (فراغ)ctx; (فراغ)fmt; (فراغ)وسائط;
    last_log_level = level;
}

صحيح main(صحيح argc, حرف **argv)
{
    ثابت حرف *path = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t size;

    av_log_set_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    إذا (av_file_map(path, &buf, &size, 0, عدم) < 0)
        أرجع 1;
    av_file_unmap(buf, size);
    إذا (size == 0)
        أرجع 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    لكل (صحيح i = 0; i < 2; i++) {
        last_log_level = -1;
        إذا (av_file_map("no_such_file_xyz", &buf, &size, i, عدم) >= 0) {
            av_file_unmap(buf, size);
            أرجع 2;
        }
        إذا (last_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, last_log_level);
            أرجع 3;
        }
    }

    أرجع 0;
}
