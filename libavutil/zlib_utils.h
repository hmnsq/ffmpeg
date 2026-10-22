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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_ZLIB_UTILS_H
#وصف_ڪريو AVUTIL_ZLIB_UTILS_H

#ضمن <stdint.h>
#ضمن "log.h"
#ضمن "error.h"
#ضمن "mem.h"

#ضمن <zlib.h>
#وصف_ڪريو CHUNK_سائيز 1024 * 64

ساكن مضمن صحيح ff_zlib_expand(فراغ *ctx, uint8_t **ٻاهريون, size_t *ٻاهريون_len,
                                 ثابت uint8_t *src, صحيح src_len)
{
    صحيح ret;

    z_وهڪرو وهڪرو = { 0 };
    إذا (inflateInit2(&وهڪرو, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               وهڪرو.نياپو);
        أرجع AVERROR(ENOSYS);
    }

    uint64_t buf_سائيز = CHUNK_سائيز * 4;
    uint8_t *buf = av_realloc(عدم, buf_سائيز);
    إذا (!buf) {
        inflate_پڇاڙي(&وهڪرو);
        أرجع AVERROR(ENOMEM);
    }

    وهڪرو.ايندڙ_اندريون = src;
    وهڪرو.avail_اندريون = src_len;

    افعل {
        وهڪرو.avail_ٻاهريون = buf_سائيز - وهڪرو.ڪل_ٻاهريون;
        وهڪرو.ايندڙ_ٻاهريون = buf + وهڪرو.ڪل_ٻاهريون;

        ret = inflate(&وهڪرو, Z_پڄاڻي);
        إذا (ret != Z_OK && ret != Z_وهڪرو_پڇاڙي && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, وهڪرو.نياپو);
            inflate_پڇاڙي(&وهڪرو);
            av_free(buf);
            أرجع AVERROR(EINVAL);
        }

        إذا (وهڪرو.avail_ٻاهريون == 0) {
            buf_سائيز += CHUNK_سائيز;
            uint8_t *tmp = av_realloc(buf, buf_سائيز);
            إذا (!tmp) {
                inflate_پڇاڙي(&وهڪرو);
                av_free(buf);
                أرجع AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } طالما (ret != Z_وهڪرو_پڇاڙي);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[وهڪرو.ڪل_ٻاهريون] = 0;

    inflate_پڇاڙي(&وهڪرو);

    *ٻاهريون = buf;
    *ٻاهريون_len = وهڪرو.ڪل_ٻاهريون;

    أرجع 0;
}
#جيڪڏهن_پورو /* AVUTIL_ZLIB_UTILS_H */
