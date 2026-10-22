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

#اگر_تعریف_نشده AVUTIL_ZLIB_UTILS_H
#تعریف_کن AVUTIL_ZLIB_UTILS_H

#ضمن <stdint.h>
#ضمن "log.h"
#ضمن "error.h"
#ضمن "mem.h"

#ضمن <zlib.h>
#تعریف_کن CHUNK_اندازه 1024 * 64

ساكن مضمن صحيح ff_zlib_expand(فراغ *ctx, uint8_t **بیرون, size_t *بیرون_len,
                                 ثابت uint8_t *src, صحيح src_len)
{
    صحيح ret;

    z_جریان جریان = { 0 };
    إذا (inflateInit2(&جریان, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               جریان.پیام);
        أرجع AVERROR(ENOSYS);
    }

    uint64_t buf_اندازه = CHUNK_اندازه * 4;
    uint8_t *buf = av_realloc(عدم, buf_اندازه);
    إذا (!buf) {
        inflate_انتها(&جریان);
        أرجع AVERROR(ENOMEM);
    }

    جریان.بعدی_درون = src;
    جریان.avail_درون = src_len;

    افعل {
        جریان.avail_بیرون = buf_اندازه - جریان.مجموع_بیرون;
        جریان.بعدی_بیرون = buf + جریان.مجموع_بیرون;

        ret = inflate(&جریان, Z_پایان);
        إذا (ret != Z_OK && ret != Z_جریان_انتها && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, جریان.پیام);
            inflate_انتها(&جریان);
            av_free(buf);
            أرجع AVERROR(EINVAL);
        }

        إذا (جریان.avail_بیرون == 0) {
            buf_اندازه += CHUNK_اندازه;
            uint8_t *tmp = av_realloc(buf, buf_اندازه);
            إذا (!tmp) {
                inflate_انتها(&جریان);
                av_free(buf);
                أرجع AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } طالما (ret != Z_جریان_انتها);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[جریان.مجموع_بیرون] = 0;

    inflate_انتها(&جریان);

    *بیرون = buf;
    *بیرون_len = جریان.مجموع_بیرون;

    أرجع 0;
}
#پایان_اگر /* AVUTIL_ZLIB_UTILS_H */
