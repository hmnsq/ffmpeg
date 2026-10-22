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

#অন্তর্ভাব "error.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "rc4.h"

AVRC4 *av_rc4_alloc(শূন্য)
{
    ফেরত av_mallocz(আকার(কাঠামো AVRC4));
}

পূর্ণসংখ্যা av_rc4_init(AVRC4 *r, ধ্রুবক uint8_t *চাবি, পূর্ণসংখ্যা চাবি_bits, পূর্ণসংখ্যা decrypt) {
    পূর্ণসংখ্যা i, j;
    uint8_t y;
    uint8_t *state = r->state;
    পূর্ণসংখ্যা keylen = চাবি_bits >> 3;
    যদি (চাবি_bits & 7)
        ফেরত AVERROR(EINVAL);
    জন্য (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    জন্য (j = 0, i = 0; i < 256; i++, j++) {
        যদি (j == keylen) j = 0;
        y += state[i] + চাবি[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    ফেরত 0;
}

শূন্য av_rc4_crypt(AVRC4 *r, uint8_t *dst, ধ্রুবক uint8_t *src, পূর্ণসংখ্যা গুনতি, uint8_t *iv, পূর্ণসংখ্যা decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    যখন (গুনতি-- > 0) {
        uint8_t যোগ = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[যোগ] : state[যোগ];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
