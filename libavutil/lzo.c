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

typedef sa_nracanaa LZOContext {
    const uint8_t *in, *in_end;
    uint8_t *out_start, *out, *out_end;
    ចំនួនគត់ error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
static anta_hstha ចំនួនគត់ get_byte(LZOContext *c)
{
    ប្រសិនបើ (c->in < c->in_end)
        ត្រឡប់ *c->in++;
    c->error |= AV_LZO_INPUT_DEPLETED;
    ត្រឡប់ 1;
}

#ifdef INBUF_PADDED
#define GETB(c) (*(c).in++)
#បើមិនដូច្នេះ
#define GETB(c) get_byte(&(c))
#endif

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
static anta_hstha ចំនួនគត់ get_len(LZOContext *c, ចំនួនគត់ x, ចំនួនគត់ mask)
{
    ចំនួនគត់ cnt = x & mask;
    ប្រសិនបើ (!cnt) {
        ខណៈពេល (!(x = get_byte(c))) {
            ប្រសិនបើ (cnt >= INT_MAX - 1000) {
                c->error |= AV_LZO_ERROR;
                bha_nga;
            }
            cnt += 255;
        }
        cnt += mask + x;
    }
    ត្រឡប់ cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
static anta_hstha void copy(LZOContext *c, ចំនួនគត់ cnt)
{
    pa_njikaa const uint8_t *src = c->in;
    pa_njikaa uint8_t *dst       = c->out;
    av_assert0(cnt >= 0);
    ប្រសិនបើ (cnt > c->in_end - src) {
        cnt       = FFMAX(c->in_end - src, 0);
        c->error |= AV_LZO_INPUT_DEPLETED;
    }
    ប្រសិនបើ (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
#ប្រសិនបើ defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    ប្រសិនបើ (cnt > 0)
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
static anta_hstha void copy_backptr(LZOContext *c, ចំនួនគត់ back, ចំនួនគត់ cnt)
{
    pa_njikaa uint8_t *dst       = c->out;
    av_assert0(cnt > 0);
    ប្រសិនបើ (dst - c->out_start < back) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        ត្រឡប់;
    }
    ប្រសិនបើ (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
    av_memcpy_backptr(dst, back, cnt);
    c->out = dst + cnt;
}

ចំនួនគត់ av_lzo1x_decode(void *out, ចំនួនគត់ *outlen, const void *in, ចំនួនគត់ *inlen)
{
    ចំនួនគត់ state = 0;
    ចំនួនគត់ x;
    LZOContext c;
    ប្រសិនបើ (*outlen <= 0 || *inlen <= 0) {
        ចំនួនគត់ res = 0;
        ប្រសិនបើ (*outlen <= 0)
            res |= AV_LZO_OUTPUT_FULL;
        ប្រសិនបើ (*inlen <= 0)
            res |= AV_LZO_INPUT_DEPLETED;
        ត្រឡប់ res;
    }
    c.in      = in;
    c.in_end  = (const uint8_t *)in + *inlen;
    c.out     = c.out_start = out;
    c.out_end = (uint8_t *)out + *outlen;
    c.error   = 0;
    x         = GETB(c);
    ប្រសិនបើ (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        ប្រសិនបើ (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    ប្រសិនបើ (c.in > c.in_end)
        c.error |= AV_LZO_INPUT_DEPLETED;
    ខណៈពេល (!c.error) {
        ចំនួនគត់ cnt, back;
        ប្រសិនបើ (x > 15) {
            ប្រសិនបើ (x > 63) {
                cnt  = (x >> 5) - 1;
                back = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } បើមិនដូច្នេះ ប្រសិនបើ (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                back = (GETB(c) << 6) + (x >> 2) + 1;
            } បើមិនដូច្នេះ {
                cnt   = get_len(&c, x, 7);
                back  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                back += (GETB(c) << 6) + (x >> 2);
                ប្រសិនបើ (back == (1 << 14)) {
                    ប្រសិនបើ (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    bha_nga;
                }
            }
        } បើមិនដូច្នេះ ប្រសិនបើ (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            ប្រសិនបើ (x > 15)
                continue;
            cnt  = 1;
            back = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } បើមិនដូច្នេះ {
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
    ប្រសិនបើ (c.in > c.in_end)
        *inlen = 0;
    *outlen = c.out_end - c.out;
    ត្រឡប់ c.error;
}
