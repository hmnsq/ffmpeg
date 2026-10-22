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

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ "log.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"

#ଅନ୍ତର୍ଭାଵ <zlib.h>
#define CHUNK_SIZE 1024 * 64

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_zlib_expand(ଶୂନ୍ୟ *ctx, uint8_t **out, size_t *out_len,
                                 ଅଚଳ uint8_t *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_len)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    z_stream stream = { 0 };
    ଯଦି (inflateInit2(&stream, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               stream.ସନ୍ଦେଶ);
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    uint64_t buf_size = CHUNK_SIZE * 4;
    uint8_t *buf = av_realloc(ଖାଲି, buf_size);
    ଯଦି (!buf) {
        inflateEnd(&stream);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    stream.next_in = src;
    stream.avail_in = src_len;

    କର {
        stream.avail_out = buf_size - stream.total_out;
        stream.next_out = buf + stream.total_out;

        ret = inflate(&stream, Z_FINISH);
        ଯଦି (ret != Z_OK && ret != Z_STREAM_END && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, stream.ସନ୍ଦେଶ);
            inflateEnd(&stream);
            av_free(buf);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }

        ଯଦି (stream.avail_out == 0) {
            buf_size += CHUNK_SIZE;
            uint8_t *tmp = av_realloc(buf, buf_size);
            ଯଦି (!tmp) {
                inflateEnd(&stream);
                av_free(buf);
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } ଯେତେବେଳେ (ret != Z_STREAM_END);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[stream.total_out] = 0;

    inflateEnd(&stream);

    *out = buf;
    *out_len = stream.total_out;

    ଫେରନ୍ତୁ 0;
}
#endif /* AVUTIL_ZLIB_UTILS_H */
