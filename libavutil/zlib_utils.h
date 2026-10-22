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

#यदि_अपरिभाषितम् AVUTIL_ZLIB_UTILS_H
#परिभाषय AVUTIL_ZLIB_UTILS_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "log.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "mem.h"

#अन्तर्भाव <zlib.h>
#परिभाषय CHUNK_आकार 1024 * 64

स्थिर अन्तःस्थ पूर्णाङ्क ff_zlib_expand(शून्य *ctx, uint8_t **बहिर्गमनम्, size_t *बहिर्गमनम्_len,
                                 ध्रुव uint8_t *src, पूर्णाङ्क src_len)
{
    पूर्णाङ्क ret;

    z_प्रवाहः प्रवाहः = { 0 };
    यदि (inflateInit2(&प्रवाहः, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               प्रवाहः.सन्देशः);
        प्रत्यागम AVERROR(ENOSYS);
    }

    uint64_t buf_आकार = CHUNK_आकार * 4;
    uint8_t *buf = av_realloc(रिक्त, buf_आकार);
    यदि (!buf) {
        inflate_अन्तः(&प्रवाहः);
        प्रत्यागम AVERROR(ENOMEM);
    }

    प्रवाहः.अग्र_अन्तर् = src;
    प्रवाहः.avail_अन्तर् = src_len;

    कुरु {
        प्रवाहः.avail_बहिर्गमनम् = buf_आकार - प्रवाहः.योग_बहिर्गमनम्;
        प्रवाहः.अग्र_बहिर्गमनम् = buf + प्रवाहः.योग_बहिर्गमनम्;

        ret = inflate(&प्रवाहः, Z_FINISH);
        यदि (ret != Z_OK && ret != Z_प्रवाहः_अन्तः && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, प्रवाहः.सन्देशः);
            inflate_अन्तः(&प्रवाहः);
            av_free(buf);
            प्रत्यागम AVERROR(EINVAL);
        }

        यदि (प्रवाहः.avail_बहिर्गमनम् == 0) {
            buf_आकार += CHUNK_आकार;
            uint8_t *tmp = av_realloc(buf, buf_आकार);
            यदि (!tmp) {
                inflate_अन्तः(&प्रवाहः);
                av_free(buf);
                प्रत्यागम AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } यावत् (ret != Z_प्रवाहः_अन्तः);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[प्रवाहः.योग_बहिर्गमनम्] = 0;

    inflate_अन्तः(&प्रवाहः);

    *बहिर्गमनम् = buf;
    *बहिर्गमनम्_len = प्रवाहः.योग_बहिर्गमनम्;

    प्रत्यागम 0;
}
#यदि_अन्तः /* AVUTIL_ZLIB_UTILS_H */
