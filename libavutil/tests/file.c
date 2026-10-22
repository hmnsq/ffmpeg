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

#അന്തര്ഭാവ <stdarg.h>
#അന്തര്ഭാവ <stdio.h>

#അന്തര്ഭാവ "libavutil/file.c"
#അന്തര്ഭാവ "libavutil/log.h"

സ്ഥിതം പൂർണ്ണസംഖ്യ last_log_level = -1;

സ്ഥിതം ശൂന്യം log_callback(ശൂന്യം *ctx, പൂർണ്ണസംഖ്യ level, സ്ഥിരം അക്ഷരം *fmt, va_list args)
{
    (ശൂന്യം)ctx; (ശൂന്യം)fmt; (ശൂന്യം)args;
    last_log_level = level;
}

പൂർണ്ണസംഖ്യ പ്രധാന(പൂർണ്ണസംഖ്യ argc, അക്ഷരം **argv)
{
    സ്ഥിരം അക്ഷരം *path = argc > 1 ? argv[1] : "file.c";
    uint8_t *buf;
    size_t size;

    av_log_set_callback(log_callback);

    /* map an existing file and verify it is non-empty and readable */
    എങ്കിൽ (av_file_map(path, &buf, &size, 0, ശൂന്യ) < 0)
        തിരികെ 1;
    av_file_unmap(buf, size);
    എങ്കിൽ (size == 0)
        തിരികെ 1;

    /* for offset i, error must be logged at AV_LOG_ERROR + i */
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 2; i++) {
        last_log_level = -1;
        എങ്കിൽ (av_file_map("no_such_file_xyz", &buf, &size, i, ശൂന്യ) >= 0) {
            av_file_unmap(buf, size);
            തിരികെ 2;
        }
        എങ്കിൽ (last_log_level != AV_LOG_ERROR + i) {
            fprintf(stderr, "expected level %d with offset=%d, got %d\n",
                    AV_LOG_ERROR + i, i, last_log_level);
            തിരികെ 3;
        }
    }

    തിരികെ 0;
}
