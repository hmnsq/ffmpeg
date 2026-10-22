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

#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "rc4.h"

AVRC4 *av_rc4_alloc(ਖਾਲੀ)
{
    ਵਾਪਸ av_mallocz(ਆਕਾਰ(ਬਣਤਰ AVRC4));
}

ਪੂਰਨ av_rc4_init(AVRC4 *r, ਅਚਲ uint8_t *ਕੁੰਜੀ, ਪੂਰਨ ਕੁੰਜੀ_ਬਿੱਟ, ਪੂਰਨ decrypt) {
    ਪੂਰਨ i, j;
    uint8_t y;
    uint8_t *state = r->state;
    ਪੂਰਨ keylen = ਕੁੰਜੀ_ਬਿੱਟ >> 3;
    ਜੇ (ਕੁੰਜੀ_ਬਿੱਟ & 7)
        ਵਾਪਸ AVERROR(EINVAL);
    ਲਈ (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    ਲਈ (j = 0, i = 0; i < 256; i++, j++) {
        ਜੇ (j == keylen) j = 0;
        y += state[i] + ਕੁੰਜੀ[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    ਵਾਪਸ 0;
}

ਖਾਲੀ av_rc4_crypt(AVRC4 *r, uint8_t *dst, ਅਚਲ uint8_t *src, ਪੂਰਨ ਗਿਣਤੀ_2, uint8_t *iv, ਪੂਰਨ decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    ਜਦੋਂ (ਗਿਣਤੀ_2-- > 0) {
        uint8_t ਜੋੜ = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[ਜੋੜ] : state[ਜੋੜ];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
