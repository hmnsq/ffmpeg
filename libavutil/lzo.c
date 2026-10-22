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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "intreadwrite.h"
#अन्तर्भाव "lzo.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"

/// Define if we may write up to 12 bytes beyond the output buffer.
#define OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#define INBUF_PADDED 1

प्रकारव्याख्या संरचना LZOContext {
    स्थिरांक uint8_t *in, *in_end;
    uint8_t *out_start, *out, *out_end;
    पूर्णांक error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
स्थिर ओळीत पूर्णांक get_byte(LZOContext *c)
{
    जर (c->in < c->in_end)
        परत *c->in++;
    c->error |= AV_LZO_आदान_DEPLETED;
    परत 1;
}

#ifdef INBUF_PADDED
#define GETB(c) (*(c).in++)
#अन्यथा
#define GETB(c) get_byte(&(c))
#endif

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
स्थिर ओळीत पूर्णांक get_len(LZOContext *c, पूर्णांक x, पूर्णांक mask)
{
    पूर्णांक cnt = x & mask;
    जर (!cnt) {
        पर्यंत (!(x = get_byte(c))) {
            जर (cnt >= पूर्णांक_उच्च - 1000) {
                c->error |= AV_LZO_ERROR;
                थांबा;
            }
            cnt += 255;
        }
        cnt += mask + x;
    }
    परत cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
स्थिर ओळीत शून्य copy(LZOContext *c, पूर्णांक cnt)
{
    नोंदणी स्थिरांक uint8_t *src = c->in;
    नोंदणी uint8_t *dst       = c->out;
    av_assert0(cnt >= 0);
    जर (cnt > c->in_end - src) {
        cnt       = FFMAX(c->in_end - src, 0);
        c->error |= AV_LZO_आदान_DEPLETED;
    }
    जर (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
#जर defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    जर (cnt > 0)
#endif
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
स्थिर ओळीत शून्य copy_backptr(LZOContext *c, पूर्णांक back, पूर्णांक cnt)
{
    नोंदणी uint8_t *dst       = c->out;
    av_assert0(cnt > 0);
    जर (dst - c->out_start < back) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        परत;
    }
    जर (cnt > c->out_end - dst) {
        cnt       = FFMAX(c->out_end - dst, 0);
        c->error |= AV_LZO_OUTPUT_FULL;
    }
    av_memcpy_backptr(dst, back, cnt);
    c->out = dst + cnt;
}

पूर्णांक av_lzo1x_decode(शून्य *out, पूर्णांक *outlen, स्थिरांक शून्य *in, पूर्णांक *inlen)
{
    पूर्णांक state = 0;
    पूर्णांक x;
    LZOContext c;
    जर (*outlen <= 0 || *inlen <= 0) {
        पूर्णांक res = 0;
        जर (*outlen <= 0)
            res |= AV_LZO_OUTPUT_FULL;
        जर (*inlen <= 0)
            res |= AV_LZO_आदान_DEPLETED;
        परत res;
    }
    c.in      = in;
    c.in_end  = (स्थिरांक uint8_t *)in + *inlen;
    c.out     = c.out_start = out;
    c.out_end = (uint8_t *)out + *outlen;
    c.error   = 0;
    x         = GETB(c);
    जर (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        जर (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    जर (c.in > c.in_end)
        c.error |= AV_LZO_आदान_DEPLETED;
    पर्यंत (!c.error) {
        पूर्णांक cnt, back;
        जर (x > 15) {
            जर (x > 63) {
                cnt  = (x >> 5) - 1;
                back = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } अन्यथा जर (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                back = (GETB(c) << 6) + (x >> 2) + 1;
            } अन्यथा {
                cnt   = get_len(&c, x, 7);
                back  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                back += (GETB(c) << 6) + (x >> 2);
                जर (back == (1 << 14)) {
                    जर (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    थांबा;
                }
            }
        } अन्यथा जर (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            जर (x > 15)
                सुरूठेवा;
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
    जर (c.in > c.in_end)
        *inlen = 0;
    *outlen = c.out_end - c.out;
    परत c.error;
}
