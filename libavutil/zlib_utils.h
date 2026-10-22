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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "mem.h"

#অন্তর্ভাব <zlib.h>
#define CHUNK_আকার 1024 * 64

স্থির অন্তঃরেখ পূর্ণসংখ্যা ff_zlib_expand(শূন্য *ctx, uint8_t **out, size_t *out_len,
                                 ধ্রুবক uint8_t *src, পূর্ণসংখ্যা src_len)
{
    পূর্ণসংখ্যা ret;

    z_stream stream = { 0 };
    যদি (inflateInit2(&stream, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               stream.বার্তা);
        ফেরত AVERROR(ENOSYS);
    }

    uint64_t buf_আকার = CHUNK_আকার * 4;
    uint8_t *buf = av_realloc(ফাঁকা, buf_আকার);
    যদি (!buf) {
        inflateEnd(&stream);
        ফেরত AVERROR(ENOMEM);
    }

    stream.পরবর্তী_in = src;
    stream.avail_in = src_len;

    করো {
        stream.avail_out = buf_আকার - stream.যোগ_out;
        stream.পরবর্তী_out = buf + stream.যোগ_out;

        ret = inflate(&stream, Z_FINISH);
        যদি (ret != Z_OK && ret != Z_STREAM_END && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, stream.বার্তা);
            inflateEnd(&stream);
            av_free(buf);
            ফেরত AVERROR(EINVAL);
        }

        যদি (stream.avail_out == 0) {
            buf_আকার += CHUNK_আকার;
            uint8_t *tmp = av_realloc(buf, buf_আকার);
            যদি (!tmp) {
                inflateEnd(&stream);
                av_free(buf);
                ফেরত AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } যখন (ret != Z_STREAM_END);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[stream.যোগ_out] = 0;

    inflateEnd(&stream);

    *out = buf;
    *out_len = stream.যোগ_out;

    ফেরত 0;
}
#endif /* AVUTIL_ZLIB_UTILS_H */
