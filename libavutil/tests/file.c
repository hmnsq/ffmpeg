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

#अन्तर्भाव <stdarg.h>
#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/file.c"
#अन्तर्भाव "libavutil/log.h"

स्थिर पूर्णाङ्क last_log_level = -1;

स्थिर शून्य log_callback(शून्य *ctx, पूर्णाङ्क level, ध्रुव वर्ण *fmt, va_list args)
{
    (शून्य)ctx; (शून्य)fmt; (शून्य)args;
    last_log_level = level;
}

पूर्णाङ्क main(पूर्णाङ्क argc, वर्ण **argv)
{
    ध्रुव वर्ण *path = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t size;

    av_log_set_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    सचे (av_file_map(path, &buf, &size, 0, रिक्त) < 0)
        पटिनिवत्त 1;
    av_file_unmap(buf, size);
    सचे (size == 0)
        पटिनिवत्त 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    अत्थाय (पूर्णाङ्क i = 0; i < 2; i++) {
        last_log_level = -1;
        सचे (av_file_map("no_such_file_xyz", &buf, &size, i, रिक्त) >= 0) {
            av_file_unmap(buf, size);
            पटिनिवत्त 2;
        }
        सचे (last_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, last_log_level);
            पटिनिवत्त 3;
        }
    }

    पटिनिवत्त 0;
}
