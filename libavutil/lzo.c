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

#شامل <limits.h>
#شامل <stdint.h>
#شامل <string.h>

#شامل "avassert.h"
#شامل "intreadwrite.h"
#شامل "lzo.h"
#شامل "macros.h"
#شامل "mem.h"

/// Define if we may write up to 12 bytes beyond the output buffer.
#define OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#define INBUF_PADDED 1

تعریفنوع ساختار LZOContext {
    ثابت uint8_t *in, *in_end;
    uint8_t *out_start, *out, *out_end;
    صحیح error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
ایستا درونخطی صحیح get_byte(LZOContext *c)
{
    اگر (c->in < c->in_end)
        بازگشت *c->in++;
    c->error |= AV_LZO_درون_داد_DEPLETED;
    بازگشت 1;
}

#ifdef INBUF_PADDED
#define GETB(c) (*(c).in++)
#وگرنه
#define GETB(c) get_byte(&(c))
#endif

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
ایستا درونخطی صحیح get_len(LZOContext *c, صحیح x, صحیح mask)
{
    صحیح cnt = x & mask;
    اگر (!cnt) {
        وقتی (!(x = get_byte(c))) {
            اگر (cnt >= INT_MAX - 1000) {
                c->error |= AV_LZO_ERROR;
                بشکن;
            }
            cnt += 255;
        }
        cnt += mask + x;
    }
    بازگشت cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
ایستا درونخطی تهی copy(LZOContext *c, صحیح cnt)
{
    ثبات ثابت uint8_t *src = c->in;
    ثبات uint8_t *dst       = c->out;
    av_assert0(cnt >= 0);
    اگر (cnt > c->in_end - src) {
        cnt       = FFMAX(c->in_end - src, 0);
        c->error |= AV_LZO_درون_داد_DEPLETED;
    }
    اگر (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
#اگر defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    اگر (cnt > 0)
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
ایستا درونخطی تهی copy_backptr(LZOContext *c, صحیح back, صحیح cnt)
{
    ثبات uint8_t *dst       = c->out;
    av_assert0(cnt > 0);
    اگر (dst - c->out_start < back) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        بازگشت;
    }
    اگر (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
    av_memcpy_backptr(dst, back, cnt);
    c->out = dst + cnt;
}

صحیح av_lzo1x_decode(تهی *out, صحیح *outlen, ثابت تهی *in, صحیح *inlen)
{
    صحیح state = 0;
    صحیح x;
    LZOContext c;
    اگر (*outlen <= 0 || *inlen <= 0) {
        صحیح res = 0;
        اگر (*outlen <= 0)
            res |= AV_LZO_OUTPUT_FULL;
        اگر (*inlen <= 0)
            res |= AV_LZO_درون_داد_DEPLETED;
        بازگشت res;
    }
    c.in      = in;
    c.in_end  = (ثابت uint8_t *)in + *inlen;
    c.out     = c.out_start = out;
    c.out_end = (uint8_t *)out + *outlen;
    c.error   = 0;
    x         = GETB(c);
    اگر (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        اگر (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    اگر (c.in > c.in_end)
        c.error |= AV_LZO_درون_داد_DEPLETED;
    وقتی (!c.error) {
        صحیح cnt, back;
        اگر (x > 15) {
            اگر (x > 63) {
                cnt  = (x >> 5) - 1;
                back = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } وگرنه اگر (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                back = (GETB(c) << 6) + (x >> 2) + 1;
            } وگرنه {
                cnt   = get_len(&c, x, 7);
                back  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                back += (GETB(c) << 6) + (x >> 2);
                اگر (back == (1 << 14)) {
                    اگر (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    بشکن;
                }
            }
        } وگرنه اگر (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            اگر (x > 15)
                ادامه;
            cnt  = 1;
            back = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } وگرنه {
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
    اگر (c.in > c.in_end)
        *inlen = 0;
    *outlen = c.out_end - c.out;
    بازگشت c.error;
}
