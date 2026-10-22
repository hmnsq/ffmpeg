/*
 * RC4 encryption/decryption/pseudo-random number generator
 * Copyright (c) 2007 Reimar Doeffinger
 *
 * loosely based on LibTomCrypt by Tom St Denis
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

#شامل "error.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "rc4.h"

AVRC4 *av_rc4_alloc(خالی)
{
    واپس av_mallocz(حجم(ساخت AVRC4));
}

صحیح av_rc4_init(AVRC4 *r, ثابت uint8_t *کلید, صحیح کلید_بٹ, صحیح decrypt) {
    صحیح i, j;
    uint8_t y;
    uint8_t *state = r->state;
    صحیح keylen = کلید_بٹ >> 3;
    اگر (کلید_بٹ & 7)
        واپس AVERROR(EINVAL);
    برائے (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    برائے (j = 0, i = 0; i < 256; i++, j++) {
        اگر (j == keylen) j = 0;
        y += state[i] + کلید[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    واپس 0;
}

خالی av_rc4_crypt(AVRC4 *r, uint8_t *dst, ثابت uint8_t *src, صحیح گنتی, uint8_t *iv, صحیح decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    جب (گنتی-- > 0) {
        uint8_t مجموع = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[مجموع] : state[مجموع];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
