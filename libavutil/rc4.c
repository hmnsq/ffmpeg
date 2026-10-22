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

#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "macros.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "rc4.h"

AVRC4 *av_rc4_alloc(શૂન્ય)
{
    પાછા av_mallocz(કદ(સંરચના AVRC4));
}

પૂર્ણાંક av_rc4_init(AVRC4 *r, અચલ uint8_t *ચાવી, પૂર્ણાંક ચાવી_bits, પૂર્ણાંક decrypt) {
    પૂર્ણાંક i, j;
    uint8_t y;
    uint8_t *state = r->state;
    પૂર્ણાંક keylen = ચાવી_bits >> 3;
    જો (ચાવી_bits & 7)
        પાછા AVERROR(EINVAL);
    માટે (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    માટે (j = 0, i = 0; i < 256; i++, j++) {
        જો (j == keylen) j = 0;
        y += state[i] + ચાવી[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    પાછા 0;
}

શૂન્ય av_rc4_crypt(AVRC4 *r, uint8_t *dst, અચલ uint8_t *src, પૂર્ણાંક ગણતરી, uint8_t *iv, પૂર્ણાંક decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    જ્યારે (ગણતરી-- > 0) {
        uint8_t sum = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[sum] : state[sum];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
