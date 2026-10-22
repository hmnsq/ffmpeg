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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_ZLIB_UTILS_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_ZLIB_UTILS_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

#ಅನ್ತರ್ಭಾವ <zlib.h>
#ವ್ಯಾಖ್ಯಾನಿಸು CHUNK_ಗಾತ್ರ 1024 * 64

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ ff_zlib_expand(ಶೂನ್ಯ *ctx, uint8_t **ಹೊರಹೋಗು, size_t *ಹೊರಹೋಗು_len,
                                 ಸ್ಥಿರಾಂಕ uint8_t *src, ಪೂರ್ಣಾಂಕ src_len)
{
    ಪೂರ್ಣಾಂಕ ret;

    z_ಹರಿವು ಹರಿವು = { 0 };
    ಆದರೆ (inflateInit2(&ಹರಿವು, 32 + 15) != Z_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error during zlib initialisation: %s\n",
               ಹರಿವು.ಸಂದೇಶ);
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    uint64_t buf_ಗಾತ್ರ = CHUNK_ಗಾತ್ರ * 4;
    uint8_t *buf = av_realloc(ಖಾಲಿ, buf_ಗಾತ್ರ);
    ಆದರೆ (!buf) {
        inflate_ಕೊನೆ(&ಹರಿವು);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    ಹರಿವು.ಮುಂದಿನ_ಒಳ = src;
    ಹರಿವು.avail_ಒಳ = src_len;

    ಮಾಡು {
        ಹರಿವು.avail_ಹೊರಹೋಗು = buf_ಗಾತ್ರ - ಹರಿವು.ಒಟ್ಟು_ಹೊರಹೋಗು;
        ಹರಿವು.ಮುಂದಿನ_ಹೊರಹೋಗು = buf + ಹರಿವು.ಒಟ್ಟು_ಹೊರಹೋಗು;

        ret = inflate(&ಹರಿವು, Z_ಮುಕ್ತಾಯ);
        ಆದರೆ (ret != Z_OK && ret != Z_ಹರಿವು_ಕೊನೆ && ret != Z_BUF_ERROR) {
            av_log(ctx, AV_LOG_ERROR, "zlib inflate error(%d): %s\n",
                   ret, ಹರಿವು.ಸಂದೇಶ);
            inflate_ಕೊನೆ(&ಹರಿವು);
            av_free(buf);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }

        ಆದರೆ (ಹರಿವು.avail_ಹೊರಹೋಗು == 0) {
            buf_ಗಾತ್ರ += CHUNK_ಗಾತ್ರ;
            uint8_t *tmp = av_realloc(buf, buf_ಗಾತ್ರ);
            ಆದರೆ (!tmp) {
                inflate_ಕೊನೆ(&ಹರಿವು);
                av_free(buf);
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            }
            buf = tmp;
        }
    } ಆಗ (ret != Z_ಹರಿವು_ಕೊನೆ);

    // NULL-terminate string
    // there is guaranteed to be space for this, due to condition in loop
    buf[ಹರಿವು.ಒಟ್ಟು_ಹೊರಹೋಗು] = 0;

    inflate_ಕೊನೆ(&ಹರಿವು);

    *ಹೊರಹೋಗು = buf;
    *ಹೊರಹೋಗು_len = ಹರಿವು.ಒಟ್ಟು_ಹೊರಹೋಗು;

    ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_ZLIB_UTILS_H */
