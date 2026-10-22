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
#تعریف_کرو OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#تعریف_کرو INBUF_PADDED 1

قسمتعریف ساخت LZOContext {
    ثابت uint8_t *اندر, *اندر_انتہا;
    uint8_t *برآمد_آغاز, *برآمد, *برآمد_انتہا;
    صحیح error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
ساکن اندرونی صحیح get_byte(LZOContext *c)
{
    اگر (c->اندر < c->اندر_انتہا)
        واپس *c->اندر++;
    c->error |= AV_LZO_داخلہ_DEPLETED;
    واپس 1;
}

#اگر_تعریف_شدہ INBUF_PADDED
#تعریف_کرو GETB(c) (*(c).اندر++)
#ورنہ
#تعریف_کرو GETB(c) get_byte(&(c))
#اگر_ختم

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
ساکن اندرونی صحیح get_len(LZOContext *c, صحیح x, صحیح نقاب_2)
{
    صحیح cnt = x & نقاب_2;
    اگر (!cnt) {
        جب (!(x = get_byte(c))) {
            اگر (cnt >= زیادہ_سے_زیادہ_عدد - 1000) {
                c->error |= AV_LZO_ERROR;
                توڑو;
            }
            cnt += 255;
        }
        cnt += نقاب_2 + x;
    }
    واپس cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
ساکن اندرونی خالی copy(LZOContext *c, صحیح cnt)
{
    اندراج ثابت uint8_t *src = c->اندر;
    اندراج uint8_t *dst       = c->برآمد;
    av_assert0(cnt >= 0);
    اگر (cnt > c->اندر_انتہا - src) {
        cnt       = FFMAX(c->اندر_انتہا - src, 0);
        c->error |= AV_LZO_داخلہ_DEPLETED;
    }
    اگر (cnt > c->برآمد_انتہا - dst) {
        cnt       = FFMAX(c->برآمد_انتہا - dst, 0);
        c->error |= AV_LZO_OUTPUT_بھرا;
    }
#اگر defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    اگر (cnt > 0)
#اگر_ختم
    حافظہ_نقل(dst, src, cnt);
    c->اندر  = src + cnt;
    c->برآمد = dst + cnt;
}

/**
 * @brief Copies previously decoded bytes to current position.
 * @param back how many bytes back we start, must be > 0
 * @param cnt number of bytes to copy, must be > 0
 *
 * cnt > back is valid, this will copy the bytes we just copied,
 * thus creating a repeating pattern with a period length of back.
 */
ساکن اندرونی خالی copy_backptr(LZOContext *c, صحیح عقب, صحیح cnt)
{
    اندراج uint8_t *dst       = c->برآمد;
    av_assert0(cnt > 0);
    اگر (dst - c->برآمد_آغاز < عقب) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        واپس;
    }
    اگر (cnt > c->برآمد_انتہا - dst) {
        cnt       = FFMAX(c->برآمد_انتہا - dst, 0);
        c->error |= AV_LZO_OUTPUT_بھرا;
    }
    av_memcpy_backptr(dst, عقب, cnt);
    c->برآمد = dst + cnt;
}

صحیح av_lzo1x_decode(خالی *برآمد, صحیح *outlen, ثابت خالی *اندر, صحیح *inlen)
{
    صحیح state = 0;
    صحیح x;
    LZOContext c;
    اگر (*outlen <= 0 || *inlen <= 0) {
        صحیح res = 0;
        اگر (*outlen <= 0)
            res |= AV_LZO_OUTPUT_بھرا;
        اگر (*inlen <= 0)
            res |= AV_LZO_داخلہ_DEPLETED;
        واپس res;
    }
    c.اندر      = اندر;
    c.اندر_انتہا  = (ثابت uint8_t *)اندر + *inlen;
    c.برآمد     = c.برآمد_آغاز = برآمد;
    c.برآمد_انتہا = (uint8_t *)برآمد + *outlen;
    c.error   = 0;
    x         = GETB(c);
    اگر (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        اگر (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    اگر (c.اندر > c.اندر_انتہا)
        c.error |= AV_LZO_داخلہ_DEPLETED;
    جب (!c.error) {
        صحیح cnt, عقب;
        اگر (x > 15) {
            اگر (x > 63) {
                cnt  = (x >> 5) - 1;
                عقب = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } ورنہ اگر (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                عقب = (GETB(c) << 6) + (x >> 2) + 1;
            } ورنہ {
                cnt   = get_len(&c, x, 7);
                عقب  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                عقب += (GETB(c) << 6) + (x >> 2);
                اگر (عقب == (1 << 14)) {
                    اگر (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    توڑو;
                }
            }
        } ورنہ اگر (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            اگر (x > 15)
                جاری;
            cnt  = 1;
            عقب = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } ورنہ {
            cnt  = 0;
            عقب = (GETB(c) << 2) + (x >> 2) + 1;
        }
        copy_backptr(&c, عقب, cnt + 2);
        state =
        cnt   = x & 3;
        copy(&c, cnt);
        x = GETB(c);
    }
    *inlen = c.اندر_انتہا - c.اندر;
    اگر (c.اندر > c.اندر_انتہا)
        *inlen = 0;
    *outlen = c.برآمد_انتہا - c.برآمد;
    واپس c.error;
}
