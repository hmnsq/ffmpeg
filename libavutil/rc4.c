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

#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "rc4.h"

AVRC4 *av_rc4_alloc(ശൂന്യം)
{
    തിരികെ av_mallocz(വലുപ്പം(ഘടന AVRC4));
}

പൂർണ്ണസംഖ്യ av_rc4_init(AVRC4 *r, സ്ഥിരം uint8_t *താക്കോൽ, പൂർണ്ണസംഖ്യ താക്കോൽ_bits, പൂർണ്ണസംഖ്യ decrypt) {
    പൂർണ്ണസംഖ്യ i, j;
    uint8_t y;
    uint8_t *state = r->state;
    പൂർണ്ണസംഖ്യ keylen = താക്കോൽ_bits >> 3;
    എങ്കിൽ (താക്കോൽ_bits & 7)
        തിരികെ AVERROR(EINVAL);
    വേണ്ടി (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    വേണ്ടി (j = 0, i = 0; i < 256; i++, j++) {
        എങ്കിൽ (j == keylen) j = 0;
        y += state[i] + താക്കോൽ[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    തിരികെ 0;
}

ശൂന്യം av_rc4_crypt(AVRC4 *r, uint8_t *dst, സ്ഥിരം uint8_t *src, പൂർണ്ണസംഖ്യ എണ്ണം, uint8_t *iv, പൂർണ്ണസംഖ്യ decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    ആകുമ്പോൾ (എണ്ണം-- > 0) {
        uint8_t sum = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[sum] : state[sum];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
