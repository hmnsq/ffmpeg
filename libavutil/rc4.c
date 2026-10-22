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

#समावेश "error.h"
#समावेश "macros.h"
#समावेश "mem.h"
#समावेश "rc4.h"

AVRC4 *av_rc4_alloc(व्योम)
{
    वापस av_mallocz(माप(काष्ठा AVRC4));
}

पूर्णांक av_rc4_init(AVRC4 *r, स्थिर uint8_t *कुंजी, पूर्णांक कुंजी_bits, पूर्णांक decrypt) {
    पूर्णांक i, j;
    uint8_t y;
    uint8_t *state = r->state;
    पूर्णांक keylen = कुंजी_bits >> 3;
    अगर (कुंजी_bits & 7)
        वापस AVERROR(EINVAL);
    क्रम (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    क्रम (j = 0, i = 0; i < 256; i++, j++) {
        अगर (j == keylen) j = 0;
        y += state[i] + कुंजी[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    वापस 0;
}

व्योम av_rc4_crypt(AVRC4 *r, uint8_t *dst, स्थिर uint8_t *src, पूर्णांक गिनती, uint8_t *iv, पूर्णांक decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    जबतक (गिनती-- > 0) {
        uint8_t योग = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[योग] : state[योग];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
