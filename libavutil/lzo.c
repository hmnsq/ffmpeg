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

#include <limits.h>
#include <stdint.h>
#include <string.h>

#include "avassert.h"
#include "intreadwrite.h"
#include "lzo.h"
#include "macros.h"
#include "mem.h"

/// Define if we may write up to 12 bytes beyond the output buffer.
#define OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#define INBUF_PADDED 1

typedef struct LZOContext {
    const uint8_t *in, *in_end;
    uint8_t *out_start, *out, *out_end;
    цео error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
static inline цео get_byte(LZOContext *c)
{
    ако (c->in < c->in_end)
        врати *c->in++;
    c->error |= AV_LZO_INPUT_DEPLETED;
    врати 1;
}

#ifdef INBUF_PADDED
#define GETB(c) (*(c).in++)
#инако
#define GETB(c) get_byte(&(c))
#endif

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
static inline цео get_len(LZOContext *c, цео x, цео mask)
{
    цео cnt = x & mask;
    ако (!cnt) {
        док (!(x = get_byte(c))) {
            ако (cnt >= INT_MAX - 1000) {
                c->error |= AV_LZO_ERROR;
                break;
            }
            cnt += 255;
        }
        cnt += mask + x;
    }
    врати cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
static inline void copy(LZOContext *c, цео cnt)
{
    register const uint8_t *src = c->in;
    register uint8_t *dst       = c->out;
    av_assert0(cnt >= 0);
    ако (cnt > c->in_end - src) {
        cnt       = FFMAX(c->in_end - src, 0);
        c->error |= AV_LZO_INPUT_DEPLETED;
    }
    ако (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
#ако defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    ако (cnt > 0)
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
static inline void copy_backptr(LZOContext *c, цео back, цео cnt)
{
    register uint8_t *dst       = c->out;
    av_assert0(cnt > 0);
    ако (dst - c->out_start < back) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        врати;
    }
    ако (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
    av_memcpy_backptr(dst, back, cnt);
    c->out = dst + cnt;
}

цео av_lzo1x_decode(void *out, цео *outlen, const void *in, цео *inlen)
{
    цео state = 0;
    цео x;
    LZOContext c;
    ако (*outlen <= 0 || *inlen <= 0) {
        цео res = 0;
        ако (*outlen <= 0)
            res |= AV_LZO_OUTPUT_FULL;
        ако (*inlen <= 0)
            res |= AV_LZO_INPUT_DEPLETED;
        врати res;
    }
    c.in      = in;
    c.in_end  = (const uint8_t *)in + *inlen;
    c.out     = c.out_start = out;
    c.out_end = (uint8_t *)out + *outlen;
    c.error   = 0;
    x         = GETB(c);
    ако (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        ако (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    ако (c.in > c.in_end)
        c.error |= AV_LZO_INPUT_DEPLETED;
    док (!c.error) {
        цео cnt, back;
        ако (x > 15) {
            ако (x > 63) {
                cnt  = (x >> 5) - 1;
                back = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } инако ако (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                back = (GETB(c) << 6) + (x >> 2) + 1;
            } инако {
                cnt   = get_len(&c, x, 7);
                back  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                back += (GETB(c) << 6) + (x >> 2);
                ако (back == (1 << 14)) {
                    ако (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    break;
                }
            }
        } инако ако (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            ако (x > 15)
                continue;
            cnt  = 1;
            back = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } инако {
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
    ако (c.in > c.in_end)
        *inlen = 0;
    *outlen = c.out_end - c.out;
    врати c.error;
}
