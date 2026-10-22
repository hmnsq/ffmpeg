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
    ಹಿಂತಿರುಗಿ av_mallocz(ಗಾತ್ರ(ರಚನೆ AVRC4));
}

ಪೂರ್ಣಾಂಕ av_rc4_init(AVRC4 *r, ಸ್ಥಿರಾಂಕ uint8_t *ಕೀಲಿ, ಪೂರ್ಣಾಂಕ ಕೀಲಿ_ಬಿಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ decrypt) {
    ಪೂರ್ಣಾಂಕ i, j;
    uint8_t y;
    uint8_t *state = r->state;
    ಪೂರ್ಣಾಂಕ keylen = ಕೀಲಿ_ಬಿಟ್ಟುಗಳು >> 3;
    ಆದರೆ (ಕೀಲಿ_ಬಿಟ್ಟುಗಳು & 7)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    ಗಾಗಿ (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    ಗಾಗಿ (j = 0, i = 0; i < 256; i++, j++) {
        ಆದರೆ (j == keylen) j = 0;
        y += state[i] + ಕೀಲಿ[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ av_rc4_crypt(AVRC4 *r, uint8_t *dst, ಸ್ಥಿರಾಂಕ uint8_t *src, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, uint8_t *iv, ಪೂರ್ಣಾಂಕ decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    ಆಗ (ಎಣಿಕೆ_2-- > 0) {
        uint8_t ಮೊತ್ತ = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[ಮೊತ್ತ] : state[ಮೊತ್ತ];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
