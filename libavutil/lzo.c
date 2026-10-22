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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "lzo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

/// Define if we may write up to 12 bytes beyond the output buffer.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ INBUF_PADDED 1

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ LZOContext {
    ਅਚਲ uint8_t *ਵਿੱਚ_2, *ਵਿੱਚ_ਸਿਰਾ;
    uint8_t *ਬਾਹਰਲਾ_ਸ਼ੁਰੂ, *ਬਾਹਰਲਾ, *ਬਾਹਰਲਾ_ਸਿਰਾ;
    ਪੂਰਨ error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ get_byte(LZOContext *c)
{
    ਜੇ (c->ਵਿੱਚ_2 < c->ਵਿੱਚ_ਸਿਰਾ)
        ਵਾਪਸ *c->ਵਿੱਚ_2++;
    c->error |= AV_LZO_ਨਿਵੇਸ਼_DEPLETED;
    ਵਾਪਸ 1;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ INBUF_PADDED
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GETB(c) (*(c).ਵਿੱਚ_2++)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GETB(c) get_byte(&(c))
#ਜੇ_ਅੰਤ

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ get_len(LZOContext *c, ਪੂਰਨ x, ਪੂਰਨ ਨਕਾਬ_2)
{
    ਪੂਰਨ cnt = x & ਨਕਾਬ_2;
    ਜੇ (!cnt) {
        ਜਦੋਂ (!(x = get_byte(c))) {
            ਜੇ (cnt >= ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ - 1000) {
                c->error |= AV_LZO_ERROR;
                ਰੋਕੋ;
            }
            cnt += 255;
        }
        cnt += ਨਕਾਬ_2 + x;
    }
    ਵਾਪਸ cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ copy(LZOContext *c, ਪੂਰਨ cnt)
{
    ਰਜਿਸਟਰ ਅਚਲ uint8_t *src = c->ਵਿੱਚ_2;
    ਰਜਿਸਟਰ uint8_t *dst       = c->ਬਾਹਰਲਾ;
    av_assert0(cnt >= 0);
    ਜੇ (cnt > c->ਵਿੱਚ_ਸਿਰਾ - src) {
        cnt       = FFMAX(c->ਵਿੱਚ_ਸਿਰਾ - src, 0);
        c->error |= AV_LZO_ਨਿਵੇਸ਼_DEPLETED;
    }
    ਜੇ (cnt > c->ਬਾਹਰਲਾ_ਸਿਰਾ - dst) {
        cnt       = FFMAX(c->ਬਾਹਰਲਾ_ਸਿਰਾ - dst, 0);
        c->error |= AV_LZO_OUTPUT_ਭਰਿਆ;
    }
#ਜੇ defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    ਜੇ (cnt > 0)
#ਜੇ_ਅੰਤ
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst, src, cnt);
    c->ਵਿੱਚ_2  = src + cnt;
    c->ਬਾਹਰਲਾ = dst + cnt;
}

/**
 * @brief Copies previously decoded bytes to current position.
 * @param back how many bytes back we start, must be > 0
 * @param cnt number of bytes to copy, must be > 0
 *
 * cnt > back is valid, this will copy the bytes we just copied,
 * thus creating a repeating pattern with a period length of back.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ copy_backptr(LZOContext *c, ਪੂਰਨ ਪਿੱਠ, ਪੂਰਨ cnt)
{
    ਰਜਿਸਟਰ uint8_t *dst       = c->ਬਾਹਰਲਾ;
    av_assert0(cnt > 0);
    ਜੇ (dst - c->ਬਾਹਰਲਾ_ਸ਼ੁਰੂ < ਪਿੱਠ) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        ਵਾਪਸ;
    }
    ਜੇ (cnt > c->ਬਾਹਰਲਾ_ਸਿਰਾ - dst) {
        cnt       = FFMAX(c->ਬਾਹਰਲਾ_ਸਿਰਾ - dst, 0);
        c->error |= AV_LZO_OUTPUT_ਭਰਿਆ;
    }
    av_memcpy_backptr(dst, ਪਿੱਠ, cnt);
    c->ਬਾਹਰਲਾ = dst + cnt;
}

ਪੂਰਨ av_lzo1x_decode(ਖਾਲੀ *ਬਾਹਰਲਾ, ਪੂਰਨ *outlen, ਅਚਲ ਖਾਲੀ *ਵਿੱਚ_2, ਪੂਰਨ *inlen)
{
    ਪੂਰਨ state = 0;
    ਪੂਰਨ x;
    LZOContext c;
    ਜੇ (*outlen <= 0 || *inlen <= 0) {
        ਪੂਰਨ res = 0;
        ਜੇ (*outlen <= 0)
            res |= AV_LZO_OUTPUT_ਭਰਿਆ;
        ਜੇ (*inlen <= 0)
            res |= AV_LZO_ਨਿਵੇਸ਼_DEPLETED;
        ਵਾਪਸ res;
    }
    c.ਵਿੱਚ_2      = ਵਿੱਚ_2;
    c.ਵਿੱਚ_ਸਿਰਾ  = (ਅਚਲ uint8_t *)ਵਿੱਚ_2 + *inlen;
    c.ਬਾਹਰਲਾ     = c.ਬਾਹਰਲਾ_ਸ਼ੁਰੂ = ਬਾਹਰਲਾ;
    c.ਬਾਹਰਲਾ_ਸਿਰਾ = (uint8_t *)ਬਾਹਰਲਾ + *outlen;
    c.error   = 0;
    x         = GETB(c);
    ਜੇ (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        ਜੇ (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    ਜੇ (c.ਵਿੱਚ_2 > c.ਵਿੱਚ_ਸਿਰਾ)
        c.error |= AV_LZO_ਨਿਵੇਸ਼_DEPLETED;
    ਜਦੋਂ (!c.error) {
        ਪੂਰਨ cnt, ਪਿੱਠ;
        ਜੇ (x > 15) {
            ਜੇ (x > 63) {
                cnt  = (x >> 5) - 1;
                ਪਿੱਠ = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } ਨਹੀਂਤਾਂ ਜੇ (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                ਪਿੱਠ = (GETB(c) << 6) + (x >> 2) + 1;
            } ਨਹੀਂਤਾਂ {
                cnt   = get_len(&c, x, 7);
                ਪਿੱਠ  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                ਪਿੱਠ += (GETB(c) << 6) + (x >> 2);
                ਜੇ (ਪਿੱਠ == (1 << 14)) {
                    ਜੇ (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    ਰੋਕੋ;
                }
            }
        } ਨਹੀਂਤਾਂ ਜੇ (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            ਜੇ (x > 15)
                ਜਾਰੀ;
            cnt  = 1;
            ਪਿੱਠ = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } ਨਹੀਂਤਾਂ {
            cnt  = 0;
            ਪਿੱਠ = (GETB(c) << 2) + (x >> 2) + 1;
        }
        copy_backptr(&c, ਪਿੱਠ, cnt + 2);
        state =
        cnt   = x & 3;
        copy(&c, cnt);
        x = GETB(c);
    }
    *inlen = c.ਵਿੱਚ_ਸਿਰਾ - c.ਵਿੱਚ_2;
    ਜੇ (c.ਵਿੱਚ_2 > c.ਵਿੱਚ_ਸਿਰਾ)
        *inlen = 0;
    *outlen = c.ਬਾਹਰਲਾ_ਸਿਰਾ - c.ਬਾਹਰਲਾ;
    ਵਾਪਸ c.error;
}
