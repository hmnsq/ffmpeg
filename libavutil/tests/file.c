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

#ଅନ୍ତର୍ଭାଵ <stdarg.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>

#ଅନ୍ତର୍ଭାଵ "libavutil/file.c"
#ଅନ୍ତର୍ଭାଵ "libavutil/log.h"

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା last_log_level = -1;

ସ୍ଥିର ଶୂନ୍ୟ log_callback(ଶୂନ୍ୟ *ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା level, ଅଚଳ ଅକ୍ଷର *fmt, va_list args)
{
    (ଶୂନ୍ୟ)ctx; (ଶୂନ୍ୟ)fmt; (ଶୂନ୍ୟ)args;
    last_log_level = level;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc, ଅକ୍ଷର **argv)
{
    ଅଚଳ ଅକ୍ଷର *path = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t size;

    av_log_set_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    ଯଦି (av_file_map(path, &buf, &size, 0, ଖାଲି) < 0)
        ଫେରନ୍ତୁ 1;
    av_file_unmap(buf, size);
    ଯଦି (size == 0)
        ଫେରନ୍ତୁ 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 2; i++) {
        last_log_level = -1;
        ଯଦି (av_file_map("no_such_file_xyz", &buf, &size, i, ଖାଲି) >= 0) {
            av_file_unmap(buf, size);
            ଫେରନ୍ତୁ 2;
        }
        ଯଦି (last_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, last_log_level);
            ଫେରନ୍ତୁ 3;
        }
    }

    ଫେରନ୍ତୁ 0;
}
