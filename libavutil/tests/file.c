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

#অন্তর্ভাব <stdarg.h>
#অন্তর্ভাব <stdio.h>

#অন্তর্ভাব "libavutil/file.c"
#অন্তর্ভাব "libavutil/log.h"

স্থির পূর্ণসংখ্যা last_log_level = -1;

স্থির শূন্য log_callback(শূন্য *ctx, পূর্ণসংখ্যা level, ধ্রুবক অক্ষর *fmt, va_list args)
{
    (শূন্য)ctx; (শূন্য)fmt; (শূন্য)args;
    last_log_level = level;
}

পূর্ণসংখ্যা প্রধান(পূর্ণসংখ্যা argc, অক্ষর **argv)
{
    ধ্রুবক অক্ষর *path = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t আকার_2;

    av_log_set_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    যদি (av_file_map(path, &buf, &আকার_2, 0, ফাঁকা) < 0)
        ফেরত 1;
    av_file_unmap(buf, আকার_2);
    যদি (আকার_2 == 0)
        ফেরত 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    জন্য (পূর্ণসংখ্যা i = 0; i < 2; i++) {
        last_log_level = -1;
        যদি (av_file_map("no_such_file_xyz", &buf, &আকার_2, i, ফাঁকা) >= 0) {
            av_file_unmap(buf, আকার_2);
            ফেরত 2;
        }
        যদি (last_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, last_log_level);
            ফেরত 3;
        }
    }

    ফেরত 0;
}
