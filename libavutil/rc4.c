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

#अन्तर्भाव "error.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "rc4.h"

AVRC4 *av_rc4_alloc(शून्य)
{
    फर्काऊ av_mallocz(परिमाण(संरचना AVRC4));
}

पूर्णाङ्क av_rc4_init(AVRC4 *r, अचर uint8_t *साँचो, पूर्णाङ्क साँचो_bits, पूर्णाङ्क decrypt) {
    पूर्णाङ्क i, j;
    uint8_t y;
    uint8_t *state = r->state;
    पूर्णाङ्क keylen = साँचो_bits >> 3;
    यदि (साँचो_bits & 7)
        फर्काऊ AVERROR(EINVAL);
    लागि (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    लागि (j = 0, i = 0; i < 256; i++, j++) {
        यदि (j == keylen) j = 0;
        y += state[i] + साँचो[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    फर्काऊ 0;
}

शून्य av_rc4_crypt(AVRC4 *r, uint8_t *dst, अचर uint8_t *src, पूर्णाङ्क गन्ती, uint8_t *iv, पूर्णाङ्क decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    जबसम्म (गन्ती-- > 0) {
        uint8_t sum = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[sum] : state[sum];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
