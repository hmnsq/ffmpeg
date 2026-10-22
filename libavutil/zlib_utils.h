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

#جے_بنا_تعریف AVUTIL_ZLIB_UTILS_H
#تعریف_کرو AVUTIL_ZLIB_UTILS_H

#ضمن <stdint.h>
#ضمن "log.h"
#ضمن "error.h"
#ضمن "mem.h"

#ضمن <zlib.h>
#تعریف_کرو CHUNK_ناپ 1024 * 64

ساكن مضمن صحيح ff_zlib_expand(فراغ *ctx, uint8_t **باہرلا, size_t *باہرلا_len,
                                 ثابت uint8_t *src, صحيح src_len)
{
    صحيح ret;

    z_دھارا دھارا = { 0 };
    إذا (inflateInit2(&دھارا, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               دھارا.پیغام);
        أرجع AVERROR(ENOSYS);
    }

    uint64_t buf_ناپ = CHUNK_ناپ * 4;
    uint8_t *buf = av_realloc(عدم, buf_ناپ);
    إذا (!buf) {
        inflate_سرا(&دھارا);
        أرجع AVERROR(ENOMEM);
    }

    دھارا.اگلا_وچ = src;
    دھارا.avail_وچ = src_len;

    افعل {
        دھارا.avail_باہرلا = buf_ناپ - دھارا.کل_باہرلا;
        دھارا.اگلا_باہرلا = buf + دھارا.کل_باہرلا;

        ret = inflate(&دھارا, Z_انت);
        إذا (ret != Z_OK && ret != Z_دھارا_سرا && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, دھارا.پیغام);
            inflate_سرا(&دھارا);
            av_free(buf);
            أرجع AVERROR(EINVAL);
        }

        إذا (دھارا.avail_باہرلا == 0) {
            buf_ناپ += CHUNK_ناپ;
            uint8_t *tmp = av_realloc(buf, buf_ناپ);
            إذا (!tmp) {
                inflate_سرا(&دھارا);
                av_free(buf);
                أرجع AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } طالما (ret != Z_دھارا_سرا);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[دھارا.کل_باہرلا] = 0;

    inflate_سرا(&دھارا);

    *باہرلا = buf;
    *باہرلا_len = دھارا.کل_باہرلا;

    أرجع 0;
}
#جے_انت /* AVUTIL_ZLIB_UTILS_H */
