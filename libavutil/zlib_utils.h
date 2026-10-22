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

#اگر_غیر_تعریف_شدہ AVUTIL_ZLIB_UTILS_H
#تعریف_کرو AVUTIL_ZLIB_UTILS_H

#شامل <stdint.h>
#شامل "log.h"
#شامل "error.h"
#شامل "mem.h"

#شامل <zlib.h>
#تعریف_کرو CHUNK_سائز 1024 * 64

ساکن اندرونی صحیح ff_zlib_expand(خالی *ctx, uint8_t **برآمد, size_t *برآمد_len,
                                 ثابت uint8_t *src, صحیح src_len)
{
    صحیح ret;

    z_دھارا دھارا = { 0 };
    اگر (inflateInit2(&دھارا, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               دھارا.پیغام);
        واپس AVERROR(ENOSYS);
    }

    uint64_t buf_سائز = CHUNK_سائز * 4;
    uint8_t *buf = av_realloc(تہی, buf_سائز);
    اگر (!buf) {
        inflate_انتہا(&دھارا);
        واپس AVERROR(ENOMEM);
    }

    دھارا.اگلا_اندر = src;
    دھارا.avail_اندر = src_len;

    کرو {
        دھارا.avail_برآمد = buf_سائز - دھارا.کل_برآمد;
        دھارا.اگلا_برآمد = buf + دھارا.کل_برآمد;

        ret = inflate(&دھارا, Z_اختتام);
        اگر (ret != Z_OK && ret != Z_دھارا_انتہا && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, دھارا.پیغام);
            inflate_انتہا(&دھارا);
            av_free(buf);
            واپس AVERROR(EINVAL);
        }

        اگر (دھارا.avail_برآمد == 0) {
            buf_سائز += CHUNK_سائز;
            uint8_t *tmp = av_realloc(buf, buf_سائز);
            اگر (!tmp) {
                inflate_انتہا(&دھارا);
                av_free(buf);
                واپس AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } جب (ret != Z_دھارا_انتہا);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[دھارا.کل_برآمد] = 0;

    inflate_انتہا(&دھارا);

    *برآمد = buf;
    *برآمد_len = دھارا.کل_برآمد;

    واپس 0;
}
#اگر_ختم /* AVUTIL_ZLIB_UTILS_H */
