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

#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "rc4.h"

AVRC4 *av_rc4_alloc(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ av_mallocz(ಪರಿಮಾಣ(ಸಂರಚನಾ AVRC4));
}

ಪೂರ್ಣಾಙ್ಕ av_rc4_init(AVRC4 *r, ಧ್ರುವ uint8_t *ಕೀಲಿ, ಪೂರ್ಣಾಙ್ಕ ಕೀಲಿ_bits, ಪೂರ್ಣಾಙ್ಕ decrypt) {
    ಪೂರ್ಣಾಙ್ಕ i, j;
    uint8_t y;
    uint8_t *state = r->state;
    ಪೂರ್ಣಾಙ್ಕ keylen = ಕೀಲಿ_bits >> 3;
    ಯದಿ (ಕೀಲಿ_bits & 7)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    ಪ್ರತಿ (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    ಪ್ರತಿ (j = 0, i = 0; i < 256; i++, j++) {
        ಯದಿ (j == keylen) j = 0;
        y += state[i] + ಕೀಲಿ[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ av_rc4_crypt(AVRC4 *r, uint8_t *dst, ಧ್ರುವ uint8_t *src, ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ, uint8_t *iv, ಪೂರ್ಣಾಙ್ಕ decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    ಯಾವತ್ (ಎಣಿಕೆ-- > 0) {
        uint8_t sum = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[sum] : state[sum];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
