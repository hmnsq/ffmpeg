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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "intreadwrite.h"
#అన్తర్భావ "lzo.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"

/// Define if we may write up to 12 bytes beyond the output buffer.
#నిర్వచించు OUTBUF_PADDED 1
/// Define if we may read up to 8 bytes beyond the input buffer.
#నిర్వచించు INBUF_PADDED 1

రకనిర్వచనం నిర్మాణం LZOContext {
    స్థిరరాశి uint8_t *లోపల, *లోపల_చివర;
    uint8_t *బహిర్గతం_ప్రారంభం, *బహిర్గతం, *బహిర్గతం_చివర;
    పూర్ణాంకం error;
} LZOContext;

/**
 * @brief Reads one byte from the input buffer, avoiding an overrun.
 * @return byte read
 */
స్థిర అంతఃవరుస పూర్ణాంకం get_byte(LZOContext *c)
{
    ఒకవేళ (c->లోపల < c->లోపల_చివర)
        తిరిగి *c->లోపల++;
    c->error |= AV_LZO_ఆదానం_DEPLETED;
    తిరిగి 1;
}

#నిర్వచితమైతే INBUF_PADDED
#నిర్వచించు GETB(c) (*(c).లోపల++)
#లేకపోతే
#నిర్వచించు GETB(c) get_byte(&(c))
#అయితే_ముగింపు

/**
 * @brief Decodes a length value in the coding used by lzo.
 * @param x previous byte value
 * @param mask bits used from x
 * @return decoded length value
 */
స్థిర అంతఃవరుస పూర్ణాంకం get_len(LZOContext *c, పూర్ణాంకం x, పూర్ణాంకం ముసుగు_2)
{
    పూర్ణాంకం cnt = x & ముసుగు_2;
    ఒకవేళ (!cnt) {
        అయితే (!(x = get_byte(c))) {
            ఒకవేళ (cnt >= గరిష్ఠ_పూర్ణాంకం - 1000) {
                c->error |= AV_LZO_ERROR;
                ఆపు;
            }
            cnt += 255;
        }
        cnt += ముసుగు_2 + x;
    }
    తిరిగి cnt;
}

/**
 * @brief Copies bytes from input to output buffer with checking.
 * @param cnt number of bytes to copy, must be >= 0
 */
స్థిర అంతఃవరుస శూన్య copy(LZOContext *c, పూర్ణాంకం cnt)
{
    నమోదు స్థిరరాశి uint8_t *src = c->లోపల;
    నమోదు uint8_t *dst       = c->బహిర్గతం;
    av_assert0(cnt >= 0);
    ఒకవేళ (cnt > c->లోపల_చివర - src) {
        cnt       = FFMAX(c->లోపల_చివర - src, 0);
        c->error |= AV_LZO_ఆదానం_DEPLETED;
    }
    ఒకవేళ (cnt > c->బహిర్గతం_చివర - dst) {
        cnt       = FFMAX(c->బహిర్గతం_చివర - dst, 0);
        c->error |= AV_LZO_OUTPUT_నిండిన;
    }
#ఒకవేళ defined(INBUF_PADDED) && defined(OUTBUF_PADDED)
    AV_COPY32U(dst, src);
    src += 4;
    dst += 4;
    cnt -= 4;
    ఒకవేళ (cnt > 0)
#అయితే_ముగింపు
    జ్ఞాపకం_నకలు(dst, src, cnt);
    c->లోపల  = src + cnt;
    c->బహిర్గతం = dst + cnt;
}

/**
 * @brief Copies previously decoded bytes to current position.
 * @param back how many bytes back we start, must be > 0
 * @param cnt number of bytes to copy, must be > 0
 *
 * cnt > back is valid, this will copy the bytes we just copied,
 * thus creating a repeating pattern with a period length of back.
 */
స్థిర అంతఃవరుస శూన్య copy_backptr(LZOContext *c, పూర్ణాంకం వెనుక, పూర్ణాంకం cnt)
{
    నమోదు uint8_t *dst       = c->బహిర్గతం;
    av_assert0(cnt > 0);
    ఒకవేళ (dst - c->బహిర్గతం_ప్రారంభం < వెనుక) {
        c->error |= AV_LZO_INVALID_BACKPTR;
        తిరిగి;
    }
    ఒకవేళ (cnt > c->బహిర్గతం_చివర - dst) {
        cnt       = FFMAX(c->బహిర్గతం_చివర - dst, 0);
        c->error |= AV_LZO_OUTPUT_నిండిన;
    }
    av_memcpy_backptr(dst, వెనుక, cnt);
    c->బహిర్గతం = dst + cnt;
}

పూర్ణాంకం av_lzo1x_decode(శూన్య *బహిర్గతం, పూర్ణాంకం *outlen, స్థిరరాశి శూన్య *లోపల, పూర్ణాంకం *inlen)
{
    పూర్ణాంకం state = 0;
    పూర్ణాంకం x;
    LZOContext c;
    ఒకవేళ (*outlen <= 0 || *inlen <= 0) {
        పూర్ణాంకం res = 0;
        ఒకవేళ (*outlen <= 0)
            res |= AV_LZO_OUTPUT_నిండిన;
        ఒకవేళ (*inlen <= 0)
            res |= AV_LZO_ఆదానం_DEPLETED;
        తిరిగి res;
    }
    c.లోపల      = లోపల;
    c.లోపల_చివర  = (స్థిరరాశి uint8_t *)లోపల + *inlen;
    c.బహిర్గతం     = c.బహిర్గతం_ప్రారంభం = బహిర్గతం;
    c.బహిర్గతం_చివర = (uint8_t *)బహిర్గతం + *outlen;
    c.error   = 0;
    x         = GETB(c);
    ఒకవేళ (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        ఒకవేళ (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    ఒకవేళ (c.లోపల > c.లోపల_చివర)
        c.error |= AV_LZO_ఆదానం_DEPLETED;
    అయితే (!c.error) {
        పూర్ణాంకం cnt, వెనుక;
        ఒకవేళ (x > 15) {
            ఒకవేళ (x > 63) {
                cnt  = (x >> 5) - 1;
                వెనుక = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } లేకపోతే ఒకవేళ (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                వెనుక = (GETB(c) << 6) + (x >> 2) + 1;
            } లేకపోతే {
                cnt   = get_len(&c, x, 7);
                వెనుక  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                వెనుక += (GETB(c) << 6) + (x >> 2);
                ఒకవేళ (వెనుక == (1 << 14)) {
                    ఒకవేళ (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    ఆపు;
                }
            }
        } లేకపోతే ఒకవేళ (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            ఒకవేళ (x > 15)
                కొనసాగు;
            cnt  = 1;
            వెనుక = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } లేకపోతే {
            cnt  = 0;
            వెనుక = (GETB(c) << 2) + (x >> 2) + 1;
        }
        copy_backptr(&c, వెనుక, cnt + 2);
        state =
        cnt   = x & 3;
        copy(&c, cnt);
        x = GETB(c);
    }
    *inlen = c.లోపల_చివర - c.లోపల;
    ఒకవేళ (c.లోపల > c.లోపల_చివర)
        *inlen = 0;
    *outlen = c.బహిర్గతం_చివర - c.బహిర్గతం;
    తిరిగి c.error;
}
