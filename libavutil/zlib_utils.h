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

#که_نه_تعریف_شوی AVUTIL_ZLIB_UTILS_H
#تعریف_کړه AVUTIL_ZLIB_UTILS_H

#ضمن <stdint.h>
#ضمن "log.h"
#ضمن "error.h"
#ضمن "mem.h"

#ضمن <zlib.h>
#تعریف_کړه CHUNK_اندازه 1024 * 64

ساكن مضمن صحيح ff_zlib_expand(فراغ *ctx, uint8_t **بهر, size_t *بهر_len,
                                 ثابت uint8_t *src, صحيح src_len)
{
    صحيح ret;

    z_بهیر بهیر = { 0 };
    إذا (inflateInit2(&بهیر, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               بهیر.پیغام);
        أرجع AVERROR(ENOSYS);
    }

    uint64_t buf_اندازه = CHUNK_اندازه * 4;
    uint8_t *buf = av_realloc(عدم, buf_اندازه);
    إذا (!buf) {
        inflate_پای_ټکی(&بهیر);
        أرجع AVERROR(ENOMEM);
    }

    بهیر.بل_دننه = src;
    بهیر.avail_دننه = src_len;

    افعل {
        بهیر.avail_بهر = buf_اندازه - بهیر.ټول_بهر;
        بهیر.بل_بهر = buf + بهیر.ټول_بهر;

        ret = inflate(&بهیر, Z_پای);
        إذا (ret != Z_OK && ret != Z_بهیر_پای_ټکی && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, بهیر.پیغام);
            inflate_پای_ټکی(&بهیر);
            av_free(buf);
            أرجع AVERROR(EINVAL);
        }

        إذا (بهیر.avail_بهر == 0) {
            buf_اندازه += CHUNK_اندازه;
            uint8_t *tmp = av_realloc(buf, buf_اندازه);
            إذا (!tmp) {
                inflate_پای_ټکی(&بهیر);
                av_free(buf);
                أرجع AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } طالما (ret != Z_بهیر_پای_ټکی);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[بهیر.ټول_بهر] = 0;

    inflate_پای_ټکی(&بهیر);

    *بهر = buf;
    *بهر_len = بهیر.ټول_بهر;

    أرجع 0;
}
#د_که_پای /* AVUTIL_ZLIB_UTILS_H */
