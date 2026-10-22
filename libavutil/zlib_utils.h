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

#अगर_अघोषित AVUTIL_ZLIB_UTILS_H
#घोषणा AVUTIL_ZLIB_UTILS_H

#समावेश <stdint.h>
#समावेश "log.h"
#समावेश "error.h"
#समावेश "mem.h"

#समावेश <zlib.h>
#घोषणा CHUNK_आकार 1024 * 64

अटल अंतरभूत पूर्णांक ff_zlib_expand(व्योम *ctx, uint8_t **out, माप_प्रकार *out_len,
                                 स्थिर uint8_t *src, पूर्णांक src_len)
{
    पूर्णांक ret;

    z_stream stream = { 0 };
    अगर (inflateInit2(&stream, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               stream.संदेश);
        वापस AVERROR(ENOSYS);
    }

    uint64_t buf_आकार = CHUNK_आकार * 4;
    uint8_t *buf = av_realloc(शून्य, buf_आकार);
    अगर (!buf) {
        inflateEnd(&stream);
        वापस AVERROR(ENOMEM);
    }

    stream.अग्र_in = src;
    stream.avail_in = src_len;

    करो {
        stream.avail_out = buf_आकार - stream.योग_out;
        stream.अग्र_out = buf + stream.योग_out;

        ret = inflate(&stream, Z_FINISH);
        अगर (ret != Z_OK && ret != Z_STREAM_END && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, stream.संदेश);
            inflateEnd(&stream);
            av_free(buf);
            वापस AVERROR(EINVAL);
        }

        अगर (stream.avail_out == 0) {
            buf_आकार += CHUNK_आकार;
            uint8_t *tmp = av_realloc(buf, buf_आकार);
            अगर (!tmp) {
                inflateEnd(&stream);
                av_free(buf);
                वापस AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } जबतक (ret != Z_STREAM_END);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[stream.योग_out] = 0;

    inflateEnd(&stream);

    *out = buf;
    *out_len = stream.योग_out;

    वापस 0;
}
#पूर्ण_अगर /* AVUTIL_ZLIB_UTILS_H */
