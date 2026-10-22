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
#define OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#define INBUF_PADDED 1

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ LZOContext {
    ಧ್ರುವ uint8_t *in, *in_end;
    uint8_t *out_start, *out, *out_end;
    ಪೂರ್ಣಾಙ್ಕ error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ get_byte(LZOContext *c)
{
    ಯದಿ (c->in < c->in_end)
        ಪ್ರತ್ಯಾಗಮ *c->in++;
    c->error |= AV_LZO_ಒಳಹರಿವು_DEPLETED;
    ಪ್ರತ್ಯಾಗಮ 1;
}

#ifdef INBUF_PADDED
#define GETB(c) (*(c).in++)
#ಅನ್ಯಥಾ
#define GETB(c) get_byte(&(c))
#endif

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ get_len(LZOContext *c, ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ mask)
{
    ಪೂರ್ಣಾಙ್ಕ cnt = x & mask;
    ಯದಿ (!cnt) {
        ಯಾವತ್ (!(x = get_byte(c))) {
            ಯದಿ (cnt >= INT_MAX - 1000) {
                c->error |= AV_LZO_ERROR;
                ಭಙ್ಗ;
            }
            cnt += 255;
        }
        cnt += mask + x;
    }
    ಪ್ರತ್ಯಾಗಮ cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ copy(LZOContext *c, ಪೂರ್ಣಾಙ್ಕ cnt)
{
    ಪಞ್ಜಿಕಾ ಧ್ರುವ uint8_t *src = c->in;
    ಪಞ್ಜಿಕಾ uint8_t *dst       = c->out;
    av_assert0(cnt >= 0);
    ಯದಿ (cnt > c->in_end - src) {
        cnt       = FFMAX(c->in_end - src, 0);
        c->error |= AV_LZO_ಒಳಹರಿವು_DEPLETED;
    }
    ಯದಿ (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
#ಯದಿ defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    ಯದಿ (cnt > 0)
#endif
    memcpy(dst, src, cnt);
    c->in  = src + cnt;
    c->out = dst + cnt;
}

/**
 * @brief Copies previously decoded bytes to current position.
 * @param back how many bytes back we start, must be > 0
 * @param cnt number of bytes to copy, must be > 0
 *
 * cnt > back is valid, this will copy the bytes we just copied,
 * thus creating a repeating pattern with a period length of back.
 */
ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ copy_backptr(LZOContext *c, ಪೂರ್ಣಾಙ್ಕ back, ಪೂರ್ಣಾಙ್ಕ cnt)
{
    ಪಞ್ಜಿಕಾ uint8_t *dst       = c->out;
    av_assert0(cnt > 0);
    ಯದಿ (dst - c->out_start < back) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        ಪ್ರತ್ಯಾಗಮ;
    }
    ಯದಿ (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
    av_memcpy_backptr(dst, back, cnt);
    c->out = dst + cnt;
}

ಪೂರ್ಣಾಙ್ಕ av_lzo1x_decode(ಶೂನ್ಯ *out, ಪೂರ್ಣಾಙ್ಕ *outlen, ಧ್ರುವ ಶೂನ್ಯ *in, ಪೂರ್ಣಾಙ್ಕ *inlen)
{
    ಪೂರ್ಣಾಙ್ಕ state = 0;
    ಪೂರ್ಣಾಙ್ಕ x;
    LZOContext c;
    ಯದಿ (*outlen <= 0 || *inlen <= 0) {
        ಪೂರ್ಣಾಙ್ಕ res = 0;
        ಯದಿ (*outlen <= 0)
            res |= AV_LZO_OUTPUT_FULL;
        ಯದಿ (*inlen <= 0)
            res |= AV_LZO_ಒಳಹರಿವು_DEPLETED;
        ಪ್ರತ್ಯಾಗಮ res;
    }
    c.in      = in;
    c.in_end  = (ಧ್ರುವ uint8_t *)in + *inlen;
    c.out     = c.out_start = out;
    c.out_end = (uint8_t *)out + *outlen;
    c.error   = 0;
    x         = GETB(c);
    ಯದಿ (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        ಯದಿ (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    ಯದಿ (c.in > c.in_end)
        c.error |= AV_LZO_ಒಳಹರಿವು_DEPLETED;
    ಯಾವತ್ (!c.error) {
        ಪೂರ್ಣಾಙ್ಕ cnt, back;
        ಯದಿ (x > 15) {
            ಯದಿ (x > 63) {
                cnt  = (x >> 5) - 1;
                back = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } ಅನ್ಯಥಾ ಯದಿ (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                back = (GETB(c) << 6) + (x >> 2) + 1;
            } ಅನ್ಯಥಾ {
                cnt   = get_len(&c, x, 7);
                back  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                back += (GETB(c) << 6) + (x >> 2);
                ಯದಿ (back == (1 << 14)) {
                    ಯದಿ (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    ಭಙ್ಗ;
                }
            }
        } ಅನ್ಯಥಾ ಯದಿ (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            ಯದಿ (x > 15)
                ಅನುವರ್ತ;
            cnt  = 1;
            back = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } ಅನ್ಯಥಾ {
            cnt  = 0;
            back = (GETB(c) << 2) + (x >> 2) + 1;
        }
        copy_backptr(&c, back, cnt + 2);
        state =
        cnt   = x & 3;
        copy(&c, cnt);
        x = GETB(c);
    }
    *inlen = c.in_end - c.in;
    ಯದಿ (c.in > c.in_end)
        *inlen = 0;
    *outlen = c.out_end - c.out;
    ಪ್ರತ್ಯಾಗಮ c.error;
}
