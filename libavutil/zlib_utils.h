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

#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ "log.h"
#অন্তর্ভাৱ "error.h"
#অন্তর্ভাৱ "mem.h"

#অন্তর্ভাৱ <zlib.h>
#define CHUNK_SIZE 1024 * 64

স্থির অন্তঃস্থ পূর্ণাঙ্ক ff_zlib_expand(শূন্য *ctx, uint8_t **out, size_t *out_len,
                                 ধ্রুৱ uint8_t *src, পূর্ণাঙ্ক src_len)
{
    পূর্ণাঙ্ক ret;

    z_stream stream = { 0 };
    যদি (inflateInit2(&stream, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               stream.বাৰ্তা);
        ঘূৰাই AVERROR(ENOSYS);
    }

    uint64_t buf_size = CHUNK_SIZE * 4;
    uint8_t *buf = av_realloc(রিক্ত, buf_size);
    যদি (!buf) {
        inflateEnd(&stream);
        ঘূৰাই AVERROR(ENOMEM);
    }

    stream.next_in = src;
    stream.avail_in = src_len;

    কৰা {
        stream.avail_out = buf_size - stream.total_out;
        stream.next_out = buf + stream.total_out;

        ret = inflate(&stream, Z_FINISH);
        যদি (ret != Z_OK && ret != Z_STREAM_END && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, stream.বাৰ্তা);
            inflateEnd(&stream);
            av_free(buf);
            ঘূৰাই AVERROR(EINVAL);
        }

        যদি (stream.avail_out == 0) {
            buf_size += CHUNK_SIZE;
            uint8_t *tmp = av_realloc(buf, buf_size);
            যদি (!tmp) {
                inflateEnd(&stream);
                av_free(buf);
                ঘূৰাই AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } যেতিয়ালৈ (ret != Z_STREAM_END);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[stream.total_out] = 0;

    inflateEnd(&stream);

    *out = buf;
    *out_len = stream.total_out;

    ঘূৰাই 0;
}
#endif /* AVUTIL_ZLIB_UTILS_H */
