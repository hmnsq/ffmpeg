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

#அந்தர்பாவ <stdarg.h>
#அந்தர்பாவ <stdio.h>

#அந்தர்பாவ "libavutil/file.c"
#அந்தர்பாவ "libavutil/log.h"

நிலையான முழு last_log_level = -1;

நிலையான வெறுமை log_callback(வெறுமை *ctx, முழு level, மாறிலி எழுத்து *fmt, va_list args)
{
    (வெறுமை)ctx; (வெறுமை)fmt; (வெறுமை)args;
    last_log_level = level;
}

முழு முதன்மை(முழு argc, எழுத்து **argv)
{
    மாறிலி எழுத்து *path = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t size;

    av_log_set_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    எனில் (av_file_map(path, &buf, &size, 0, வெற்று) < 0)
        திரும்பு 1;
    av_file_unmap(buf, size);
    எனில் (size == 0)
        திரும்பு 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    க்கு (முழு i = 0; i < 2; i++) {
        last_log_level = -1;
        எனில் (av_file_map("no_such_file_xyz", &buf, &size, i, வெற்று) >= 0) {
            av_file_unmap(buf, size);
            திரும்பு 2;
        }
        எனில் (last_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, last_log_level);
            திரும்பு 3;
        }
    }

    திரும்பு 0;
}
