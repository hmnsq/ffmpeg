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
#تعریف_کړه OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#تعریف_کړه INBUF_PADDED 1

تعريفنوع بنية LZOContext {
    ثابت uint8_t *دننه, *دننه_پای_ټکی;
    uint8_t *بهر_پیل, *بهر, *بهر_پای_ټکی;
    صحيح error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
ساكن مضمن صحيح get_byte(LZOContext *c)
{
    إذا (c->دننه < c->دننه_پای_ټکی)
        أرجع *c->دننه++;
    c->error |= AV_LZO_ننوت_DEPLETED;
    أرجع 1;
}

#که_تعریف_شوی INBUF_PADDED
#تعریف_کړه GETB(c) (*(c).دننه++)
#وإلا
#تعریف_کړه GETB(c) get_byte(&(c))
#د_که_پای

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
ساكن مضمن صحيح get_len(LZOContext *c, صحيح x, صحيح ماسک_2)
{
    صحيح cnt = x & ماسک_2;
    إذا (!cnt) {
        طالما (!(x = get_byte(c))) {
            إذا (cnt >= لوی_عدد - 1000) {
                c->error |= AV_LZO_ERROR;
                اكسر;
            }
            cnt += 255;
        }
        cnt += ماسک_2 + x;
    }
    أرجع cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
ساكن مضمن فراغ copy(LZOContext *c, صحيح cnt)
{
    سجل ثابت uint8_t *src = c->دننه;
    سجل uint8_t *dst       = c->بهر;
    av_assert0(cnt >= 0);
    إذا (cnt > c->دننه_پای_ټکی - src) {
        cnt       = FFMAX(c->دننه_پای_ټکی - src, 0);
        c->error |= AV_LZO_ننوت_DEPLETED;
    }
    إذا (cnt > c->بهر_پای_ټکی - dst) {
        cnt       = FFMAX(c->بهر_پای_ټکی - dst, 0);
        c->error |= AV_LZO_OUTPUT_ډک;
    }
#إذا defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    إذا (cnt > 0)
#د_که_پای
    حافظه_نقل(dst, src, cnt);
    c->دننه  = src + cnt;
    c->بهر = dst + cnt;
}

/**
 * @brief Copies previously decoded bytes to current position.
 * @param back how many bytes back we start, must be > 0
 * @param cnt number of bytes to copy, must be > 0
 *
 * cnt > back is valid, this will copy the bytes we just copied,
 * thus creating a repeating pattern with a period length of back.
 */
ساكن مضمن فراغ copy_backptr(LZOContext *c, صحيح شا, صحيح cnt)
{
    سجل uint8_t *dst       = c->بهر;
    av_assert0(cnt > 0);
    إذا (dst - c->بهر_پیل < شا) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        أرجع;
    }
    إذا (cnt > c->بهر_پای_ټکی - dst) {
        cnt       = FFMAX(c->بهر_پای_ټکی - dst, 0);
        c->error |= AV_LZO_OUTPUT_ډک;
    }
    av_memcpy_backptr(dst, شا, cnt);
    c->بهر = dst + cnt;
}

صحيح av_lzo1x_decode(فراغ *بهر, صحيح *outlen, ثابت فراغ *دننه, صحيح *inlen)
{
    صحيح state = 0;
    صحيح x;
    LZOContext c;
    إذا (*outlen <= 0 || *inlen <= 0) {
        صحيح res = 0;
        إذا (*outlen <= 0)
            res |= AV_LZO_OUTPUT_ډک;
        إذا (*inlen <= 0)
            res |= AV_LZO_ننوت_DEPLETED;
        أرجع res;
    }
    c.دننه      = دننه;
    c.دننه_پای_ټکی  = (ثابت uint8_t *)دننه + *inlen;
    c.بهر     = c.بهر_پیل = بهر;
    c.بهر_پای_ټکی = (uint8_t *)بهر + *outlen;
    c.error   = 0;
    x         = GETB(c);
    إذا (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        إذا (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    إذا (c.دننه > c.دننه_پای_ټکی)
        c.error |= AV_LZO_ننوت_DEPLETED;
    طالما (!c.error) {
        صحيح cnt, شا;
        إذا (x > 15) {
            إذا (x > 63) {
                cnt  = (x >> 5) - 1;
                شا = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } وإلا إذا (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                شا = (GETB(c) << 6) + (x >> 2) + 1;
            } وإلا {
                cnt   = get_len(&c, x, 7);
                شا  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                شا += (GETB(c) << 6) + (x >> 2);
                إذا (شا == (1 << 14)) {
                    إذا (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    اكسر;
                }
            }
        } وإلا إذا (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            إذا (x > 15)
                استمر;
            cnt  = 1;
            شا = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } وإلا {
            cnt  = 0;
            شا = (GETB(c) << 2) + (x >> 2) + 1;
        }
        copy_backptr(&c, شا, cnt + 2);
        state =
        cnt   = x & 3;
        copy(&c, cnt);
        x = GETB(c);
    }
    *inlen = c.دننه_پای_ټکی - c.دننه;
    إذا (c.دننه > c.دننه_پای_ټکی)
        *inlen = 0;
    *outlen = c.بهر_پای_ټکی - c.بهر;
    أرجع c.error;
}
