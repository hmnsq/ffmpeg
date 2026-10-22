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

#నిర్వచితం_కాకపోతే AVUTIL_ZLIB_UTILS_H
#నిర్వచించు AVUTIL_ZLIB_UTILS_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "log.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "mem.h"

#అన్తర్భావ <zlib.h>
#నిర్వచించు CHUNK_కొలత 1024 * 64

స్థిర అంతఃవరుస పూర్ణాంకం ff_zlib_expand(శూన్య *ctx, uint8_t **బహిర్గతం, size_t *బహిర్గతం_len,
                                 స్థిరరాశి uint8_t *src, పూర్ణాంకం src_len)
{
    పూర్ణాంకం ret;

    z_ప్రవాహం ప్రవాహం = { 0 };
    ఒకవేళ (inflateInit2(&ప్రవాహం, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               ప్రవాహం.సందేశం);
        తిరిగి AVERROR(ENOSYS);
    }

    uint64_t buf_కొలత = CHUNK_కొలత * 4;
    uint8_t *buf = av_realloc(ఖాళీ, buf_కొలత);
    ఒకవేళ (!buf) {
        inflate_చివర(&ప్రవాహం);
        తిరిగి AVERROR(ENOMEM);
    }

    ప్రవాహం.తదుపరి_లోపల = src;
    ప్రవాహం.avail_లోపల = src_len;

    చేయి {
        ప్రవాహం.avail_బహిర్గతం = buf_కొలత - ప్రవాహం.మొత్తం_బహిర్గతం;
        ప్రవాహం.తదుపరి_బహిర్గతం = buf + ప్రవాహం.మొత్తం_బహిర్గతం;

        ret = inflate(&ప్రవాహం, Z_ముగింపు);
        ఒకవేళ (ret != Z_OK && ret != Z_ప్రవాహం_చివర && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, ప్రవాహం.సందేశం);
            inflate_చివర(&ప్రవాహం);
            av_free(buf);
            తిరిగి AVERROR(EINVAL);
        }

        ఒకవేళ (ప్రవాహం.avail_బహిర్గతం == 0) {
            buf_కొలత += CHUNK_కొలత;
            uint8_t *tmp = av_realloc(buf, buf_కొలత);
            ఒకవేళ (!tmp) {
                inflate_చివర(&ప్రవాహం);
                av_free(buf);
                తిరిగి AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } అయితే (ret != Z_ప్రవాహం_చివర);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[ప్రవాహం.మొత్తం_బహిర్గతం] = 0;

    inflate_చివర(&ప్రవాహం);

    *బహిర్గతం = buf;
    *బహిర్గతం_len = ప్రవాహం.మొత్తం_బహిర్గతం;

    తిరిగి 0;
}
#అయితే_ముగింపు /* AVUTIL_ZLIB_UTILS_H */
