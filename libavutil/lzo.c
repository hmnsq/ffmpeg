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

#समावेश <limits.h>
#समावेश <stdint.h>
#समावेश <string.h>

#समावेश "avassert.h"
#समावेश "intreadwrite.h"
#समावेश "lzo.h"
#समावेश "macros.h"
#समावेश "mem.h"

/// Define if we may write up to 12 bytes beyond the output buffer.
#घोषणा OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#घोषणा INBUF_PADDED 1

प्रकार काष्ठा LZOContext {
    स्थिर uint8_t *in, *in_end;
    uint8_t *out_start, *out, *out_end;
    पूर्णांक error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
अटल अंतरभूत पूर्णांक get_byte(LZOContext *c)
{
    अगर (c->in < c->in_end)
        वापस *c->in++;
    c->error |= AV_LZO_निवेश_DEPLETED;
    वापस 1;
}

#अगर_घोषित INBUF_PADDED
#घोषणा GETB(c) (*(c).in++)
#अन्यथा
#घोषणा GETB(c) get_byte(&(c))
#पूर्ण_अगर

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
अटल अंतरभूत पूर्णांक get_len(LZOContext *c, पूर्णांक x, पूर्णांक mask)
{
    पूर्णांक cnt = x & mask;
    अगर (!cnt) {
        जबतक (!(x = get_byte(c))) {
            अगर (cnt >= पूर्णांक_उच्च - 1000) {
                c->error |= AV_LZO_ERROR;
                अवरोध;
            }
            cnt += 255;
        }
        cnt += mask + x;
    }
    वापस cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
अटल अंतरभूत व्योम copy(LZOContext *c, पूर्णांक cnt)
{
    रेजिस्टर स्थिर uint8_t *src = c->in;
    रेजिस्टर uint8_t *dst       = c->out;
    av_assert0(cnt >= 0);
    अगर (cnt > c->in_end - src) {
        cnt       = FFMAX(c->in_end - src, 0);
        c->error |= AV_LZO_निवेश_DEPLETED;
    }
    अगर (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
#अगर defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    अगर (cnt > 0)
#पूर्ण_अगर
    स_नकल(dst, src, cnt);
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
अटल अंतरभूत व्योम copy_backptr(LZOContext *c, पूर्णांक back, पूर्णांक cnt)
{
    रेजिस्टर uint8_t *dst       = c->out;
    av_assert0(cnt > 0);
    अगर (dst - c->out_start < back) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        वापस;
    }
    अगर (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
    av_memcpy_backptr(dst, back, cnt);
    c->out = dst + cnt;
}

पूर्णांक av_lzo1x_decode(व्योम *out, पूर्णांक *outlen, स्थिर व्योम *in, पूर्णांक *inlen)
{
    पूर्णांक state = 0;
    पूर्णांक x;
    LZOContext c;
    अगर (*outlen <= 0 || *inlen <= 0) {
        पूर्णांक res = 0;
        अगर (*outlen <= 0)
            res |= AV_LZO_OUTPUT_FULL;
        अगर (*inlen <= 0)
            res |= AV_LZO_निवेश_DEPLETED;
        वापस res;
    }
    c.in      = in;
    c.in_end  = (स्थिर uint8_t *)in + *inlen;
    c.out     = c.out_start = out;
    c.out_end = (uint8_t *)out + *outlen;
    c.error   = 0;
    x         = GETB(c);
    अगर (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        अगर (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    अगर (c.in > c.in_end)
        c.error |= AV_LZO_निवेश_DEPLETED;
    जबतक (!c.error) {
        पूर्णांक cnt, back;
        अगर (x > 15) {
            अगर (x > 63) {
                cnt  = (x >> 5) - 1;
                back = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } अन्यथा अगर (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                back = (GETB(c) << 6) + (x >> 2) + 1;
            } अन्यथा {
                cnt   = get_len(&c, x, 7);
                back  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                back += (GETB(c) << 6) + (x >> 2);
                अगर (back == (1 << 14)) {
                    अगर (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    अवरोध;
                }
            }
        } अन्यथा अगर (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            अगर (x > 15)
                जारी;
            cnt  = 1;
            back = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } अन्यथा {
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
    अगर (c.in > c.in_end)
        *inlen = 0;
    *outlen = c.out_end - c.out;
    वापस c.error;
}
