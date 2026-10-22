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
#परिभाषय OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#परिभाषय INBUF_PADDED 1

प्रकारनिर्देश संरचना LZOContext {
    ध्रुव uint8_t *अन्तर्, *अन्तर्_अन्तः;
    uint8_t *बहिर्गमनम्_start, *बहिर्गमनम्, *बहिर्गमनम्_अन्तः;
    पूर्णाङ्क error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
स्थिर अन्तःस्थ पूर्णाङ्क get_byte(LZOContext *c)
{
    यदि (c->अन्तर् < c->अन्तर्_अन्तः)
        प्रत्यागम *c->अन्तर्++;
    c->error |= AV_LZO_निवेशः_DEPLETED;
    प्रत्यागम 1;
}

#यदि_परिभाषितम् INBUF_PADDED
#परिभाषय GETB(c) (*(c).अन्तर्++)
#अन्यथा
#परिभाषय GETB(c) get_byte(&(c))
#यदि_अन्तः

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
स्थिर अन्तःस्थ पूर्णाङ्क get_len(LZOContext *c, पूर्णाङ्क x, पूर्णाङ्क आवरणम्_2)
{
    पूर्णाङ्क cnt = x & आवरणम्_2;
    यदि (!cnt) {
        यावत् (!(x = get_byte(c))) {
            यदि (cnt >= अधिकतम_पूर्णाङ्कः - 1000) {
                c->error |= AV_LZO_ERROR;
                भङ्ग;
            }
            cnt += 255;
        }
        cnt += आवरणम्_2 + x;
    }
    प्रत्यागम cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
स्थिर अन्तःस्थ शून्य copy(LZOContext *c, पूर्णाङ्क cnt)
{
    पञ्जिका ध्रुव uint8_t *src = c->अन्तर्;
    पञ्जिका uint8_t *dst       = c->बहिर्गमनम्;
    av_assert0(cnt >= 0);
    यदि (cnt > c->अन्तर्_अन्तः - src) {
        cnt       = FFMAX(c->अन्तर्_अन्तः - src, 0);
        c->error |= AV_LZO_निवेशः_DEPLETED;
    }
    यदि (cnt > c->बहिर्गमनम्_अन्तः - dst) {
        cnt       = FFMAX(c->बहिर्गमनम्_अन्तः - dst, 0);
        c->error |= AV_LZO_OUTPUT_पूर्णम्;
    }
#यदि defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    यदि (cnt > 0)
#यदि_अन्तः
    स्मृतिं_प्रतिलिख(dst, src, cnt);
    c->अन्तर्  = src + cnt;
    c->बहिर्गमनम् = dst + cnt;
}

/**
 * @brief Copies previously decoded bytes to current position.
 * @param back how many bytes back we start, must be > 0
 * @param cnt number of bytes to copy, must be > 0
 *
 * cnt > back is valid, this will copy the bytes we just copied,
 * thus creating a repeating pattern with a period length of back.
 */
स्थिर अन्तःस्थ शून्य copy_backptr(LZOContext *c, पूर्णाङ्क पृष्ठभागः, पूर्णाङ्क cnt)
{
    पञ्जिका uint8_t *dst       = c->बहिर्गमनम्;
    av_assert0(cnt > 0);
    यदि (dst - c->बहिर्गमनम्_start < पृष्ठभागः) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        प्रत्यागम;
    }
    यदि (cnt > c->बहिर्गमनम्_अन्तः - dst) {
        cnt       = FFMAX(c->बहिर्गमनम्_अन्तः - dst, 0);
        c->error |= AV_LZO_OUTPUT_पूर्णम्;
    }
    av_memcpy_backptr(dst, पृष्ठभागः, cnt);
    c->बहिर्गमनम् = dst + cnt;
}

पूर्णाङ्क av_lzo1x_decode(शून्य *बहिर्गमनम्, पूर्णाङ्क *outlen, ध्रुव शून्य *अन्तर्, पूर्णाङ्क *inlen)
{
    पूर्णाङ्क state = 0;
    पूर्णाङ्क x;
    LZOContext c;
    यदि (*outlen <= 0 || *inlen <= 0) {
        पूर्णाङ्क res = 0;
        यदि (*outlen <= 0)
            res |= AV_LZO_OUTPUT_पूर्णम्;
        यदि (*inlen <= 0)
            res |= AV_LZO_निवेशः_DEPLETED;
        प्रत्यागम res;
    }
    c.अन्तर्      = अन्तर्;
    c.अन्तर्_अन्तः  = (ध्रुव uint8_t *)अन्तर् + *inlen;
    c.बहिर्गमनम्     = c.बहिर्गमनम्_start = बहिर्गमनम्;
    c.बहिर्गमनम्_अन्तः = (uint8_t *)बहिर्गमनम् + *outlen;
    c.error   = 0;
    x         = GETB(c);
    यदि (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        यदि (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    यदि (c.अन्तर् > c.अन्तर्_अन्तः)
        c.error |= AV_LZO_निवेशः_DEPLETED;
    यावत् (!c.error) {
        पूर्णाङ्क cnt, पृष्ठभागः;
        यदि (x > 15) {
            यदि (x > 63) {
                cnt  = (x >> 5) - 1;
                पृष्ठभागः = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } अन्यथा यदि (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                पृष्ठभागः = (GETB(c) << 6) + (x >> 2) + 1;
            } अन्यथा {
                cnt   = get_len(&c, x, 7);
                पृष्ठभागः  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                पृष्ठभागः += (GETB(c) << 6) + (x >> 2);
                यदि (पृष्ठभागः == (1 << 14)) {
                    यदि (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    भङ्ग;
                }
            }
        } अन्यथा यदि (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            यदि (x > 15)
                अनुवर्त;
            cnt  = 1;
            पृष्ठभागः = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } अन्यथा {
            cnt  = 0;
            पृष्ठभागः = (GETB(c) << 2) + (x >> 2) + 1;
        }
        copy_backptr(&c, पृष्ठभागः, cnt + 2);
        state =
        cnt   = x & 3;
        copy(&c, cnt);
        x = GETB(c);
    }
    *inlen = c.अन्तर्_अन्तः - c.अन्तर्;
    यदि (c.अन्तर् > c.अन्तर्_अन्तः)
        *inlen = 0;
    *outlen = c.बहिर्गमनम्_अन्तः - c.बहिर्गमनम्;
    प्रत्यागम c.error;
}
