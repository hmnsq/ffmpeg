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

#include "error.h"
#include "macros.h"
#include "mem.h"
#include "rc4.h"

AVRC4 *av_rc4_alloc(void)
{
    ආපසු av_mallocz(parimaa_na(sa_nracanaa AVRC4));
}

පූර්ණ_සංඛ්‍යා av_rc4_init(AVRC4 *r, const uint8_t *key, පූර්ණ_සංඛ්‍යා key_bits, පූර්ණ_සංඛ්‍යා decrypt) {
    පූර්ණ_සංඛ්‍යා i, j;
    uint8_t y;
    uint8_t *state = r->state;
    පූර්ණ_සංඛ්‍යා keylen = key_bits >> 3;
    නම් (key_bits & 7)
        ආපසු AVERROR(EINVAL);
    සඳහා (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    සඳහා (j = 0, i = 0; i < 256; i++, j++) {
        නම් (j == keylen) j = 0;
        y += state[i] + key[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    ආපසු 0;
}

void av_rc4_crypt(AVRC4 *r, uint8_t *dst, const uint8_t *src, පූර්ණ_සංඛ්‍යා count, uint8_t *iv, පූර්ණ_සංඛ්‍යා decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    අතරතුර (count-- > 0) {
        uint8_t sum = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[sum] : state[sum];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
