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

#அந்தர்பாவ "error.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "rc4.h"

AVRC4 *av_rc4_alloc(வெறுமை)
{
    திரும்பு av_mallocz(அளவு(கட்டமைப்பு AVRC4));
}

முழு av_rc4_init(AVRC4 *r, மாறிலி uint8_t *சாவி, முழு சாவி_bits, முழு decrypt) {
    முழு i, j;
    uint8_t y;
    uint8_t *state = r->state;
    முழு keylen = சாவி_bits >> 3;
    எனில் (சாவி_bits & 7)
        திரும்பு AVERROR(EINVAL);
    க்கு (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    க்கு (j = 0, i = 0; i < 256; i++, j++) {
        எனில் (j == keylen) j = 0;
        y += state[i] + சாவி[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    திரும்பு 0;
}

வெறுமை av_rc4_crypt(AVRC4 *r, uint8_t *dst, மாறிலி uint8_t *src, முழு மொத்தம், uint8_t *iv, முழு decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    போது (மொத்தம்-- > 0) {
        uint8_t sum = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[sum] : state[sum];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
