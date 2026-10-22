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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ZLIB_UTILS_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ZLIB_UTILS_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <zlib.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHUNK_ਮਾਪ 1024 * 64

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ ff_zlib_expand(ਖਾਲੀ *ctx, uint8_t **ਬਾਹਰਲਾ, size_t *ਬਾਹਰਲਾ_len,
                                 ਅਚਲ uint8_t *src, ਪੂਰਨ src_len)
{
    ਪੂਰਨ ret;

    z_ਧਾਰਾ ਧਾਰਾ = { 0 };
    ਜੇ (inflateInit2(&ਧਾਰਾ, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               ਧਾਰਾ.ਸੁਨੇਹਾ);
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    uint64_t buf_ਮਾਪ = CHUNK_ਮਾਪ * 4;
    uint8_t *buf = av_realloc(ਨਿਰਾ, buf_ਮਾਪ);
    ਜੇ (!buf) {
        inflate_ਸਿਰਾ(&ਧਾਰਾ);
        ਵਾਪਸ AVERROR(ENOMEM);
    }

    ਧਾਰਾ.ਅਗਲਾ_ਵਿੱਚ = src;
    ਧਾਰਾ.avail_ਵਿੱਚ = src_len;

    ਕਰੋ {
        ਧਾਰਾ.avail_ਬਾਹਰਲਾ = buf_ਮਾਪ - ਧਾਰਾ.ਕੁੱਲ_ਬਾਹਰਲਾ;
        ਧਾਰਾ.ਅਗਲਾ_ਬਾਹਰਲਾ = buf + ਧਾਰਾ.ਕੁੱਲ_ਬਾਹਰਲਾ;

        ret = inflate(&ਧਾਰਾ, Z_ਅੰਤ);
        ਜੇ (ret != Z_OK && ret != Z_ਧਾਰਾ_ਸਿਰਾ && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, ਧਾਰਾ.ਸੁਨੇਹਾ);
            inflate_ਸਿਰਾ(&ਧਾਰਾ);
            av_free(buf);
            ਵਾਪਸ AVERROR(EINVAL);
        }

        ਜੇ (ਧਾਰਾ.avail_ਬਾਹਰਲਾ == 0) {
            buf_ਮਾਪ += CHUNK_ਮਾਪ;
            uint8_t *tmp = av_realloc(buf, buf_ਮਾਪ);
            ਜੇ (!tmp) {
                inflate_ਸਿਰਾ(&ਧਾਰਾ);
                av_free(buf);
                ਵਾਪਸ AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } ਜਦੋਂ (ret != Z_ਧਾਰਾ_ਸਿਰਾ);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[ਧਾਰਾ.ਕੁੱਲ_ਬਾਹਰਲਾ] = 0;

    inflate_ਸਿਰਾ(&ਧਾਰਾ);

    *ਬਾਹਰਲਾ = buf;
    *ਬਾਹਰਲਾ_len = ਧਾਰਾ.ਕੁੱਲ_ਬਾਹਰਲਾ;

    ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ /* AVUTIL_ZLIB_UTILS_H */
