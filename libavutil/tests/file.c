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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdarg.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/file.c"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/log.h"

ਸਥਿਰ ਪੂਰਨ ਆਖਰੀ_log_level = -1;

ਸਥਿਰ ਖਾਲੀ log_callback(ਖਾਲੀ *ctx, ਪੂਰਨ level, ਅਚਲ ਅੱਖਰ *fmt, va_list ਦਲੀਲਾਂ)
{
    (ਖਾਲੀ)ctx; (ਖਾਲੀ)fmt; (ਖਾਲੀ)ਦਲੀਲਾਂ;
    ਆਖਰੀ_log_level = level;
}

ਪੂਰਨ ਮੁੱਖ(ਪੂਰਨ argc, ਅੱਖਰ **argv)
{
    ਅਚਲ ਅੱਖਰ *ਰਸਤਾ = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t ਮਾਪ;

    av_log_ਸੈੱਟ_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    ਜੇ (av_file_map(ਰਸਤਾ, &buf, &ਮਾਪ, 0, ਨਿਰਾ) < 0)
        ਵਾਪਸ 1;
    av_file_unmap(buf, ਮਾਪ);
    ਜੇ (ਮਾਪ == 0)
        ਵਾਪਸ 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    ਲਈ (ਪੂਰਨ i = 0; i < 2; i++) {
        ਆਖਰੀ_log_level = -1;
        ਜੇ (av_file_map("no_such_file_xyz", &buf, &ਮਾਪ, i, ਨਿਰਾ) >= 0) {
            av_file_unmap(buf, ਮਾਪ);
            ਵਾਪਸ 2;
        }
        ਜੇ (ਆਖਰੀ_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, ਆਖਰੀ_log_level);
            ਵਾਪਸ 3;
        }
    }

    ਵਾਪਸ 0;
}
