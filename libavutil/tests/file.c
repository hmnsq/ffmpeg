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

ساکن صحیح آخری_log_level = -1;

ساکن خالی log_callback(خالی *ctx, صحیح level, ثابت حرف *fmt, va_list دلائل)
{
    (خالی)ctx; (خالی)fmt; (خالی)دلائل;
    آخری_log_level = level;
}

صحیح مین(صحیح argc, حرف **argv)
{
    ثابت حرف *راستہ = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t سائز;

    av_log_سیٹ_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    اگر (av_file_map(راستہ, &buf, &سائز, 0, تہی) < 0)
        واپس 1;
    av_file_unmap(buf, سائز);
    اگر (سائز == 0)
        واپس 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    برائے (صحیح i = 0; i < 2; i++) {
        آخری_log_level = -1;
        اگر (av_file_map("no_such_file_xyz", &buf, &سائز, i, تہی) >= 0) {
            av_file_unmap(buf, سائز);
            واپس 2;
        }
        اگر (آخری_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, آخری_log_level);
            واپس 3;
        }
    }

    واپس 0;
}
