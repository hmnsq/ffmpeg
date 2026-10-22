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

#ifndef AVUTIL_ZLIB_UTILS_H
#define AVUTIL_ZLIB_UTILS_H

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ "log.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "mem.h"

#அந்தர்பாவ <zlib.h>
#define CHUNK_SIZE 1024 * 64

நிலையான உள்வரி முழு ff_zlib_expand(வெறுமை *ctx, uint8_t **out, size_t *out_len,
                                 மாறிலி uint8_t *src, முழு src_len)
{
    முழு ret;

    z_stream stream = { 0 };
    எனில் (inflateInit2(&stream, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               stream.செய்தி);
        திரும்பு AVERROR(ENOSYS);
    }

    uint64_t buf_size = CHUNK_SIZE * 4;
    uint8_t *buf = av_realloc(வெற்று, buf_size);
    எனில் (!buf) {
        inflateEnd(&stream);
        திரும்பு AVERROR(ENOMEM);
    }

    stream.next_in = src;
    stream.avail_in = src_len;

    செய் {
        stream.avail_out = buf_size - stream.total_out;
        stream.next_out = buf + stream.total_out;

        ret = inflate(&stream, Z_FINISH);
        எனில் (ret != Z_OK && ret != Z_STREAM_END && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, stream.செய்தி);
            inflateEnd(&stream);
            av_free(buf);
            திரும்பு AVERROR(EINVAL);
        }

        எனில் (stream.avail_out == 0) {
            buf_size += CHUNK_SIZE;
            uint8_t *tmp = av_realloc(buf, buf_size);
            எனில் (!tmp) {
                inflateEnd(&stream);
                av_free(buf);
                திரும்பு AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } போது (ret != Z_STREAM_END);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[stream.total_out] = 0;

    inflateEnd(&stream);

    *out = buf;
    *out_len = stream.total_out;

    திரும்பு 0;
}
#endif /* AVUTIL_ZLIB_UTILS_H */
