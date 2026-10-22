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

#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "rc4.h"

AVRC4 *av_rc4_alloc(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ av_mallocz(ଆକାର(ସଂରଚନା AVRC4));
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_rc4_init(AVRC4 *r, ଅଚଳ uint8_t *ଚାବି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଚାବି_bits, ପୂର୍ଣ୍ଣସଂଖ୍ୟା decrypt) {
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j;
    uint8_t y;
    uint8_t *state = r->state;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା keylen = ଚାବି_bits >> 3;
    ଯଦି (ଚାବି_bits & 7)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    ପାଇଁ (i = 0; i < 256; i++)
        state[i] = i;
    y = 0;
    // j is i % keylen
    ପାଇଁ (j = 0, i = 0; i < 256; i++, j++) {
        ଯଦି (j == keylen) j = 0;
        y += state[i] + ଚାବି[j];
        FFSWAP(uint8_t, state[i], state[y]);
    }
    r->x = 1;
    r->y = state[1];
    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ av_rc4_crypt(AVRC4 *r, uint8_t *dst, ଅଚଳ uint8_t *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା decrypt) {
    uint8_t x = r->x, y = r->y;
    uint8_t *state = r->state;
    ଯେତେବେଳେ (ଗଣନା_2-- > 0) {
        uint8_t sum = state[x] + state[y];
        FFSWAP(uint8_t, state[x], state[y]);
        *dst++ = src ? *src++ ^ state[sum] : state[sum];
        x++;
        y += state[x];
    }
    r->x = x; r->y = y;
}
