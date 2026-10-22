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

#అన్తర్భావ "error.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "rc4.h"

AVRC4 *av_rc4_alloc(శూన్య)
{
    తిరిగి av_mallocz(పరిమాణం(నిర్మాణం AVRC4));
}

పూర్ణాంకం av_rc4_init(AVRC4 *r, స్థిరరాశి uint8_t *కీలకం, పూర్ణాంకం కీలకం_బిట్లు, పూర్ణాంకం decrypt) {
    పూర్ణాంకం i, j;
    uint8_t y;
    uint8_t *state = r->state;
    పూర్ణాంకం keylen = కీలకం_బిట్లు >> 3;
    ఒకవేళ (కీలకం_బిట్లు & 7)
        తిరిగి AVERROR(EINVAL);
    కొరకు (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    కొరకు (j = 0, i = 0; i < 256; i++, j++) {
        ఒకవేళ (j == keylen) j = 0;
        y += state[i] + కీలకం[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    తిరిగి 0;
}

శూన్య av_rc4_crypt(AVRC4 *r, uint8_t *dst, స్థిరరాశి uint8_t *src, పూర్ణాంకం లెక్క, uint8_t *iv, పూర్ణాంకం decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    అయితే (లెక్క-- > 0) {
        uint8_t కూడిక = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[కూడిక] : state[కూడిక];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
