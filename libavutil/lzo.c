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

#ضمن <limits.h>
#ضمن <stdint.h>
#ضمن <string.h>

#ضمن "avassert.h"
#ضمن "intreadwrite.h"
#ضمن "lzo.h"
#ضمن "macros.h"
#ضمن "mem.h"

/// Define if we may write up to 12 bytes beyond the output buffer.
#define OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#define INBUF_PADDED 1

تعريفنوع بنية LZOContext {
    ثابت uint8_t *in, *in_end;
    uint8_t *out_start, *out, *out_end;
    صحيح error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
ساكن مضمن صحيح get_byte(LZOContext *c)
{
    𐡄𐡍 (c->in < c->in_end)
        أرجع *c->in++;
    c->error |= AV_LZO_INPUT_DEPLETED;
    أرجع 1;
}

#ifdef INBUF_PADDED
#define GETB(c) (*(c).in++)
#وإلا
#define GETB(c) get_byte(&(c))
#endif

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
ساكن مضمن صحيح get_len(LZOContext *c, صحيح x, صحيح mask)
{
    صحيح cnt = x & mask;
    𐡄𐡍 (!cnt) {
        طالما (!(x = get_byte(c))) {
            𐡄𐡍 (cnt >= INT_MAX - 1000) {
                c->error |= AV_LZO_ERROR;
                اكسر;
            }
            cnt += 255;
        }
        cnt += mask + x;
    }
    أرجع cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
ساكن مضمن فراغ copy(LZOContext *c, صحيح cnt)
{
    سجل ثابت uint8_t *src = c->in;
    سجل uint8_t *dst       = c->out;
    av_assert0(cnt >= 0);
    𐡄𐡍 (cnt > c->in_end - src) {
        cnt       = FFMAX(c->in_end - src, 0);
        c->error |= AV_LZO_INPUT_DEPLETED;
    }
    𐡄𐡍 (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
#𐡄𐡍 defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    𐡄𐡍 (cnt > 0)
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
ساكن مضمن فراغ copy_backptr(LZOContext *c, صحيح back, صحيح cnt)
{
    سجل uint8_t *dst       = c->out;
    av_assert0(cnt > 0);
    𐡄𐡍 (dst - c->out_start < back) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        أرجع;
    }
    𐡄𐡍 (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
    av_memcpy_backptr(dst, back, cnt);
    c->out = dst + cnt;
}

صحيح av_lzo1x_decode(فراغ *out, صحيح *outlen, ثابت فراغ *in, صحيح *inlen)
{
    صحيح state = 0;
    صحيح x;
    LZOContext c;
    𐡄𐡍 (*outlen <= 0 || *inlen <= 0) {
        صحيح res = 0;
        𐡄𐡍 (*outlen <= 0)
            res |= AV_LZO_OUTPUT_FULL;
        𐡄𐡍 (*inlen <= 0)
            res |= AV_LZO_INPUT_DEPLETED;
        أرجع res;
    }
    c.in      = in;
    c.in_end  = (ثابت uint8_t *)in + *inlen;
    c.out     = c.out_start = out;
    c.out_end = (uint8_t *)out + *outlen;
    c.error   = 0;
    x         = GETB(c);
    𐡄𐡍 (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        𐡄𐡍 (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    𐡄𐡍 (c.in > c.in_end)
        c.error |= AV_LZO_INPUT_DEPLETED;
    طالما (!c.error) {
        صحيح cnt, back;
        𐡄𐡍 (x > 15) {
            𐡄𐡍 (x > 63) {
                cnt  = (x >> 5) - 1;
                back = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } وإلا 𐡄𐡍 (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                back = (GETB(c) << 6) + (x >> 2) + 1;
            } وإلا {
                cnt   = get_len(&c, x, 7);
                back  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                back += (GETB(c) << 6) + (x >> 2);
                𐡄𐡍 (back == (1 << 14)) {
                    𐡄𐡍 (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    اكسر;
                }
            }
        } وإلا 𐡄𐡍 (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            𐡄𐡍 (x > 15)
                استمر;
            cnt  = 1;
            back = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } وإلا {
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
    𐡄𐡍 (c.in > c.in_end)
        *inlen = 0;
    *outlen = c.out_end - c.out;
    أرجع c.error;
}
