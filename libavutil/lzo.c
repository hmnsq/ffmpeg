/*
 * LZO 1x decompression
 * Copyright (c) 2006 Reimar Doeffinger
 *
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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "lzo.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

/// Define if we may write up to 12 bytes beyond the output buffer.
#ವ್ಯಾಖ್ಯಾನಿಸು OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#ವ್ಯಾಖ್ಯಾನಿಸು INBUF_PADDED 1

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ LZOContext {
    ಸ್ಥಿರಾಂಕ uint8_t *ಒಳ, *ಒಳ_ಕೊನೆ;
    uint8_t *ಹೊರಹೋಗು_ಆರಂಭ, *ಹೊರಹೋಗು, *ಹೊರಹೋಗು_ಕೊನೆ;
    ಪೂರ್ಣಾಂಕ error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ get_byte(LZOContext *c)
{
    ಆದರೆ (c->ಒಳ < c->ಒಳ_ಕೊನೆ)
        ಹಿಂತಿರುಗಿ *c->ಒಳ++;
    c->error |= AV_LZO_ಒಳಹರಿವು_DEPLETED;
    ಹಿಂತಿರುಗಿ 1;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ INBUF_PADDED
#ವ್ಯಾಖ್ಯಾನಿಸು GETB(c) (*(c).ಒಳ++)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು GETB(c) get_byte(&(c))
#ಆದರೆ_ಅಂತ್ಯ

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ get_len(LZOContext *c, ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ_2)
{
    ಪೂರ್ಣಾಂಕ cnt = x & ಮುಖವಾಡ_2;
    ಆದರೆ (!cnt) {
        ಆಗ (!(x = get_byte(c))) {
            ಆದರೆ (cnt >= ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ - 1000) {
                c->error |= AV_LZO_ERROR;
                ನಿಲ್ಲಿಸು;
            }
            cnt += 255;
        }
        cnt += ಮುಖವಾಡ_2 + x;
    }
    ಹಿಂತಿರುಗಿ cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ copy(LZOContext *c, ಪೂರ್ಣಾಂಕ cnt)
{
    ನೋಂದಣಿ ಸ್ಥಿರಾಂಕ uint8_t *src = c->ಒಳ;
    ನೋಂದಣಿ uint8_t *dst       = c->ಹೊರಹೋಗು;
    av_assert0(cnt >= 0);
    ಆದರೆ (cnt > c->ಒಳ_ಕೊನೆ - src) {
        cnt       = FFMAX(c->ಒಳ_ಕೊನೆ - src, 0);
        c->error |= AV_LZO_ಒಳಹರಿವು_DEPLETED;
    }
    ಆದರೆ (cnt > c->ಹೊರಹೋಗು_ಕೊನೆ - dst) {
        cnt       = FFMAX(c->ಹೊರಹೋಗು_ಕೊನೆ - dst, 0);
        c->error |= AV_LZO_OUTPUT_ತುಂಬಿದ;
    }
#ಆದರೆ defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    ಆದರೆ (cnt > 0)
#ಆದರೆ_ಅಂತ್ಯ
    ಸ್ಮರಣೆ_ನಕಲು(dst, src, cnt);
    c->ಒಳ  = src + cnt;
    c->ಹೊರಹೋಗು = dst + cnt;
}

/**
 * @brief Copies previously decoded bytes to current position.
 * @param back how many bytes back we start, must be > 0
 * @param cnt number of bytes to copy, must be > 0
 *
 * cnt > back is valid, this will copy the bytes we just copied,
 * thus creating a repeating pattern with a period length of back.
 */
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ copy_backptr(LZOContext *c, ಪೂರ್ಣಾಂಕ ಹಿಂಭಾಗ, ಪೂರ್ಣಾಂಕ cnt)
{
    ನೋಂದಣಿ uint8_t *dst       = c->ಹೊರಹೋಗು;
    av_assert0(cnt > 0);
    ಆದರೆ (dst - c->ಹೊರಹೋಗು_ಆರಂಭ < ಹಿಂಭಾಗ) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        ಹಿಂತಿರುಗಿ;
    }
    ಆದರೆ (cnt > c->ಹೊರಹೋಗು_ಕೊನೆ - dst) {
        cnt       = FFMAX(c->ಹೊರಹೋಗು_ಕೊನೆ - dst, 0);
        c->error |= AV_LZO_OUTPUT_ತುಂಬಿದ;
    }
    av_memcpy_backptr(dst, ಹಿಂಭಾಗ, cnt);
    c->ಹೊರಹೋಗು = dst + cnt;
}

ಪೂರ್ಣಾಂಕ av_lzo1x_decode(ಶೂನ್ಯ *ಹೊರಹೋಗು, ಪೂರ್ಣಾಂಕ *outlen, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಒಳ, ಪೂರ್ಣಾಂಕ *inlen)
{
    ಪೂರ್ಣಾಂಕ state = 0;
    ಪೂರ್ಣಾಂಕ x;
    LZOContext c;
    ಆದರೆ (*outlen <= 0 || *inlen <= 0) {
        ಪೂರ್ಣಾಂಕ res = 0;
        ಆದರೆ (*outlen <= 0)
            res |= AV_LZO_OUTPUT_ತುಂಬಿದ;
        ಆದರೆ (*inlen <= 0)
            res |= AV_LZO_ಒಳಹರಿವು_DEPLETED;
        ಹಿಂತಿರುಗಿ res;
    }
    c.ಒಳ      = ಒಳ;
    c.ಒಳ_ಕೊನೆ  = (ಸ್ಥಿರಾಂಕ uint8_t *)ಒಳ + *inlen;
    c.ಹೊರಹೋಗು     = c.ಹೊರಹೋಗು_ಆರಂಭ = ಹೊರಹೋಗು;
    c.ಹೊರಹೋಗು_ಕೊನೆ = (uint8_t *)ಹೊರಹೋಗು + *outlen;
    c.error   = 0;
    x         = GETB(c);
    ಆದರೆ (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        ಆದರೆ (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    ಆದರೆ (c.ಒಳ > c.ಒಳ_ಕೊನೆ)
        c.error |= AV_LZO_ಒಳಹರಿವು_DEPLETED;
    ಆಗ (!c.error) {
        ಪೂರ್ಣಾಂಕ cnt, ಹಿಂಭಾಗ;
        ಆದರೆ (x > 15) {
            ಆದರೆ (x > 63) {
                cnt  = (x >> 5) - 1;
                ಹಿಂಭಾಗ = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                ಹಿಂಭಾಗ = (GETB(c) << 6) + (x >> 2) + 1;
            } ಇಲ್ಲದಿದ್ದರೆ {
                cnt   = get_len(&c, x, 7);
                ಹಿಂಭಾಗ  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                ಹಿಂಭಾಗ += (GETB(c) << 6) + (x >> 2);
                ಆದರೆ (ಹಿಂಭಾಗ == (1 << 14)) {
                    ಆದರೆ (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    ನಿಲ್ಲಿಸು;
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            ಆದರೆ (x > 15)
                ಮುಂದುವರಿ;
            cnt  = 1;
            ಹಿಂಭಾಗ = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } ಇಲ್ಲದಿದ್ದರೆ {
            cnt  = 0;
            ಹಿಂಭಾಗ = (GETB(c) << 2) + (x >> 2) + 1;
        }
        copy_backptr(&c, ಹಿಂಭಾಗ, cnt + 2);
        state =
        cnt   = x & 3;
        copy(&c, cnt);
        x = GETB(c);
    }
    *inlen = c.ಒಳ_ಕೊನೆ - c.ಒಳ;
    ಆದರೆ (c.ಒಳ > c.ಒಳ_ಕೊನೆ)
        *inlen = 0;
    *outlen = c.ಹೊರಹೋಗು_ಕೊನೆ - c.ಹೊರಹೋಗು;
    ಹಿಂತಿರುಗಿ c.error;
}
