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

#અન્તર્ભાવ <stdarg.h>
#અન્તર્ભાવ <stdio.h>

#અન્તર્ભાવ "libavutil/file.c"
#અન્તર્ભાવ "libavutil/log.h"

સ્થિર પૂર્ણાંક last_log_level = -1;

સ્થિર શૂન્ય log_callback(શૂન્ય *ctx, પૂર્ણાંક level, અચલ અક્ષર *fmt, va_list args)
{
    (શૂન્ય)ctx; (શૂન્ય)fmt; (શૂન્ય)args;
    last_log_level = level;
}

પૂર્ણાંક મુખ્ય(પૂર્ણાંક argc, અક્ષર **argv)
{
    અચલ અક્ષર *path = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t size;

    av_log_set_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    જો (av_file_map(path, &buf, &size, 0, ખાલી) < 0)
        પાછા 1;
    av_file_unmap(buf, size);
    જો (size == 0)
        પાછા 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    માટે (પૂર્ણાંક i = 0; i < 2; i++) {
        last_log_level = -1;
        જો (av_file_map("no_such_file_xyz", &buf, &size, i, ખાલી) >= 0) {
            av_file_unmap(buf, size);
            પાછા 2;
        }
        જો (last_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, last_log_level);
            પાછા 3;
        }
    }

    પાછા 0;
}
