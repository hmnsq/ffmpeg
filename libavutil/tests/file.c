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

#অন্তর্ভাৱ <stdarg.h>
#অন্তর্ভাৱ <stdio.h>

#অন্তর্ভাৱ "libavutil/file.c"
#অন্তর্ভাৱ "libavutil/log.h"

স্থির পূর্ণাঙ্ক last_log_level = -1;

স্থির শূন্য log_callback(শূন্য *ctx, পূর্ণাঙ্ক level, ধ্রুৱ ৱর্ণ *fmt, va_list args)
{
    (শূন্য)ctx; (শূন্য)fmt; (শূন্য)args;
    last_log_level = level;
}

পূর্ণাঙ্ক main(পূর্ণাঙ্ক argc, ৱর্ণ **argv)
{
    ধ্রুৱ ৱর্ণ *path = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t size;

    av_log_set_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    যদি (av_file_map(path, &buf, &size, 0, রিক্ত) < 0)
        ঘূৰাই 1;
    av_file_unmap(buf, size);
    যদি (size == 0)
        ঘূৰাই 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    বাবে (পূর্ণাঙ্ক i = 0; i < 2; i++) {
        last_log_level = -1;
        যদি (av_file_map("no_such_file_xyz", &buf, &size, i, রিক্ত) >= 0) {
            av_file_unmap(buf, size);
            ঘূৰাই 2;
        }
        যদি (last_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, last_log_level);
            ঘূৰাই 3;
        }
    }

    ঘূৰাই 0;
}
