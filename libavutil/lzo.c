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
#وصف_ڪريو OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#وصف_ڪريو INBUF_PADDED 1

تعريفنوع بنية LZOContext {
    ثابت uint8_t *اندريون, *اندريون_پڇاڙي;
    uint8_t *ٻاهريون_شروعات, *ٻاهريون, *ٻاهريون_پڇاڙي;
    صحيح error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
ساكن مضمن صحيح get_byte(LZOContext *c)
{
    إذا (c->اندريون < c->اندريون_پڇاڙي)
        أرجع *c->اندريون++;
    c->error |= AV_LZO_داخلا_DEPLETED;
    أرجع 1;
}

#جيڪڏهن_وصف_ٿيل INBUF_PADDED
#وصف_ڪريو GETB(c) (*(c).اندريون++)
#وإلا
#وصف_ڪريو GETB(c) get_byte(&(c))
#جيڪڏهن_پورو

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
ساكن مضمن صحيح get_len(LZOContext *c, صحيح x, صحيح نقاب_2)
{
    صحيح cnt = x & نقاب_2;
    إذا (!cnt) {
        طالما (!(x = get_byte(c))) {
            إذا (cnt >= وڌ_کان_وڌ_عدد - 1000) {
                c->error |= AV_LZO_ERROR;
                اكسر;
            }
            cnt += 255;
        }
        cnt += نقاب_2 + x;
    }
    أرجع cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
ساكن مضمن فراغ copy(LZOContext *c, صحيح cnt)
{
    سجل ثابت uint8_t *src = c->اندريون;
    سجل uint8_t *dst       = c->ٻاهريون;
    av_assert0(cnt >= 0);
    إذا (cnt > c->اندريون_پڇاڙي - src) {
        cnt       = FFMAX(c->اندريون_پڇاڙي - src, 0);
        c->error |= AV_LZO_داخلا_DEPLETED;
    }
    إذا (cnt > c->ٻاهريون_پڇاڙي - dst) {
        cnt       = FFMAX(c->ٻاهريون_پڇاڙي - dst, 0);
        c->error |= AV_LZO_OUTPUT_ڀريل;
    }
#إذا defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    إذا (cnt > 0)
#جيڪڏهن_پورو
    يادگيري_نقل(dst, src, cnt);
    c->اندريون  = src + cnt;
    c->ٻاهريون = dst + cnt;
}

/**
 * @brief Copies previously decoded bytes to current position.
 * @param back how many bytes back we start, must be > 0
 * @param cnt number of bytes to copy, must be > 0
 *
 * cnt > back is valid, this will copy the bytes we just copied,
 * thus creating a repeating pattern with a period length of back.
 */
ساكن مضمن فراغ copy_backptr(LZOContext *c, صحيح پٺ, صحيح cnt)
{
    سجل uint8_t *dst       = c->ٻاهريون;
    av_assert0(cnt > 0);
    إذا (dst - c->ٻاهريون_شروعات < پٺ) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        أرجع;
    }
    إذا (cnt > c->ٻاهريون_پڇاڙي - dst) {
        cnt       = FFMAX(c->ٻاهريون_پڇاڙي - dst, 0);
        c->error |= AV_LZO_OUTPUT_ڀريل;
    }
    av_memcpy_backptr(dst, پٺ, cnt);
    c->ٻاهريون = dst + cnt;
}

صحيح av_lzo1x_decode(فراغ *ٻاهريون, صحيح *outlen, ثابت فراغ *اندريون, صحيح *inlen)
{
    صحيح state = 0;
    صحيح x;
    LZOContext c;
    إذا (*outlen <= 0 || *inlen <= 0) {
        صحيح res = 0;
        إذا (*outlen <= 0)
            res |= AV_LZO_OUTPUT_ڀريل;
        إذا (*inlen <= 0)
            res |= AV_LZO_داخلا_DEPLETED;
        أرجع res;
    }
    c.اندريون      = اندريون;
    c.اندريون_پڇاڙي  = (ثابت uint8_t *)اندريون + *inlen;
    c.ٻاهريون     = c.ٻاهريون_شروعات = ٻاهريون;
    c.ٻاهريون_پڇاڙي = (uint8_t *)ٻاهريون + *outlen;
    c.error   = 0;
    x         = GETB(c);
    إذا (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        إذا (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    إذا (c.اندريون > c.اندريون_پڇاڙي)
        c.error |= AV_LZO_داخلا_DEPLETED;
    طالما (!c.error) {
        صحيح cnt, پٺ;
        إذا (x > 15) {
            إذا (x > 63) {
                cnt  = (x >> 5) - 1;
                پٺ = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } وإلا إذا (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                پٺ = (GETB(c) << 6) + (x >> 2) + 1;
            } وإلا {
                cnt   = get_len(&c, x, 7);
                پٺ  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                پٺ += (GETB(c) << 6) + (x >> 2);
                إذا (پٺ == (1 << 14)) {
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
            پٺ = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } وإلا {
            cnt  = 0;
            پٺ = (GETB(c) << 2) + (x >> 2) + 1;
        }
        copy_backptr(&c, پٺ, cnt + 2);
        state =
        cnt   = x & 3;
        copy(&c, cnt);
        x = GETB(c);
    }
    *inlen = c.اندريون_پڇاڙي - c.اندريون;
    إذا (c.اندريون > c.اندريون_پڇاڙي)
        *inlen = 0;
    *outlen = c.ٻاهريون_پڇاڙي - c.ٻاهريون;
    أرجع c.error;
}
