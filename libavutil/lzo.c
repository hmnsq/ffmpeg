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

#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "intreadwrite.h"
#അന്തര്ഭാവ "lzo.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"

/// Define if we may write up to 12 bytes beyond the output buffer.
#define OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#define INBUF_PADDED 1

തരനിർവചനം ഘടന LZOContext {
    സ്ഥിരം uint8_t *in, *in_end;
    uint8_t *out_start, *out, *out_end;
    പൂർണ്ണസംഖ്യ error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ get_byte(LZOContext *c)
{
    എങ്കിൽ (c->in < c->in_end)
        തിരികെ *c->in++;
    c->error |= AV_LZO_നിവേശം_DEPLETED;
    തിരികെ 1;
}

#ifdef INBUF_PADDED
#define GETB(c) (*(c).in++)
#അല്ലെങ്കിൽ
#define GETB(c) get_byte(&(c))
#endif

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ get_len(LZOContext *c, പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ mask)
{
    പൂർണ്ണസംഖ്യ cnt = x & mask;
    എങ്കിൽ (!cnt) {
        ആകുമ്പോൾ (!(x = get_byte(c))) {
            എങ്കിൽ (cnt >= INT_MAX - 1000) {
                c->error |= AV_LZO_ERROR;
                നിർത്തുക;
            }
            cnt += 255;
        }
        cnt += mask + x;
    }
    തിരികെ cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
സ്ഥിതം വരിയിൽ ശൂന്യം copy(LZOContext *c, പൂർണ്ണസംഖ്യ cnt)
{
    രജിസ്റ്റർ സ്ഥിരം uint8_t *src = c->in;
    രജിസ്റ്റർ uint8_t *dst       = c->out;
    av_assert0(cnt >= 0);
    എങ്കിൽ (cnt > c->in_end - src) {
        cnt       = FFMAX(c->in_end - src, 0);
        c->error |= AV_LZO_നിവേശം_DEPLETED;
    }
    എങ്കിൽ (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
#എങ്കിൽ defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    എങ്കിൽ (cnt > 0)
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
സ്ഥിതം വരിയിൽ ശൂന്യം copy_backptr(LZOContext *c, പൂർണ്ണസംഖ്യ back, പൂർണ്ണസംഖ്യ cnt)
{
    രജിസ്റ്റർ uint8_t *dst       = c->out;
    av_assert0(cnt > 0);
    എങ്കിൽ (dst - c->out_start < back) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        തിരികെ;
    }
    എങ്കിൽ (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
    av_memcpy_backptr(dst, back, cnt);
    c->out = dst + cnt;
}

പൂർണ്ണസംഖ്യ av_lzo1x_decode(ശൂന്യം *out, പൂർണ്ണസംഖ്യ *outlen, സ്ഥിരം ശൂന്യം *in, പൂർണ്ണസംഖ്യ *inlen)
{
    പൂർണ്ണസംഖ്യ state = 0;
    പൂർണ്ണസംഖ്യ x;
    LZOContext c;
    എങ്കിൽ (*outlen <= 0 || *inlen <= 0) {
        പൂർണ്ണസംഖ്യ res = 0;
        എങ്കിൽ (*outlen <= 0)
            res |= AV_LZO_OUTPUT_FULL;
        എങ്കിൽ (*inlen <= 0)
            res |= AV_LZO_നിവേശം_DEPLETED;
        തിരികെ res;
    }
    c.in      = in;
    c.in_end  = (സ്ഥിരം uint8_t *)in + *inlen;
    c.out     = c.out_start = out;
    c.out_end = (uint8_t *)out + *outlen;
    c.error   = 0;
    x         = GETB(c);
    എങ്കിൽ (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        എങ്കിൽ (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    എങ്കിൽ (c.in > c.in_end)
        c.error |= AV_LZO_നിവേശം_DEPLETED;
    ആകുമ്പോൾ (!c.error) {
        പൂർണ്ണസംഖ്യ cnt, back;
        എങ്കിൽ (x > 15) {
            എങ്കിൽ (x > 63) {
                cnt  = (x >> 5) - 1;
                back = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } അല്ലെങ്കിൽ എങ്കിൽ (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                back = (GETB(c) << 6) + (x >> 2) + 1;
            } അല്ലെങ്കിൽ {
                cnt   = get_len(&c, x, 7);
                back  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                back += (GETB(c) << 6) + (x >> 2);
                എങ്കിൽ (back == (1 << 14)) {
                    എങ്കിൽ (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    നിർത്തുക;
                }
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            എങ്കിൽ (x > 15)
                തുടരുക;
            cnt  = 1;
            back = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } അല്ലെങ്കിൽ {
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
    എങ്കിൽ (c.in > c.in_end)
        *inlen = 0;
    *outlen = c.out_end - c.out;
    തിരികെ c.error;
}
