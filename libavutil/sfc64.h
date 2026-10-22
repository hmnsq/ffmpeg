/*
 * Copyright (c) 2024 Michael Niedermayer <michael-ffmpeg@niedermayer.cc>
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
 *
 */

/**
 * @file
 * simple Pseudo Random Number Generator
 *
 * This is a implementation of SFC64, a 64-bit PRNG by Chris Doty-Humphrey.
 *
 * This Generator is much faster (0m1.872s) than 64bit KISS (0m3.823s) and PCG-XSH-RR-64/32 (0m2.700s)
 * And passes testu01 and practrand test suits.
 */

#अगर_अघोषित AVUTIL_SFC64_H
#घोषणा AVUTIL_SFC64_H

#समावेश <inttypes.h>

प्रकार काष्ठा FFSFC64 {
    uint64_t a,b,c,गणक;
} FFSFC64;

अटल अंतरभूत uint64_t ff_sfc64_get(FFSFC64 *s) {
    uint64_t tmp = s->a + s->b + s->गणक++;
    s->a = s->b ^ (s->b >> 11);
    s->b = s->c + (s->c << 3); // This is a multiply by 9
    s->c = (s->c << 24 | s->c >> 40) + tmp;
    वापस tmp;
}

/**
 * Return the previous random value, and step the generator backward.
 *
 * It is safe to take values before the first, but such values can be highly
 * correlated to the seeds.
 */
अटल अंतरभूत uint64_t ff_sfc64_reverse_get(FFSFC64 *s) {
    uint64_t पूर्व_c = s->b * 0x8E38E38E38E38E39;
    uint64_t tmp = s->c - (पूर्व_c << 24 | पूर्व_c >> 40);
    s->b = s->a ^ (s->a >> 11);
    s->b ^= s->b >> 22;
    s->b ^= s->b >> 44;

    s->a = tmp - s->b - --s->गणक;
    s->c = पूर्व_c;

    वापस tmp;
}

/**
 * Initialize sfc64 with up to 3 seeds.
 *
 * @param rounds number of rounds mixing up state during init. Generally 8-18, larger numbers will help with bad quality seeds.
 *               12 is a good choice if all 3 seeds are equal
 *
 */
अटल अंतरभूत व्योम ff_sfc64_init(FFSFC64 *s, uint64_t seeda, uint64_t seedb, uint64_t seedc, पूर्णांक rounds) {
    s->a       = seeda;
    s->b       = seedb;
    s->c       = seedc;
    s->गणक = 1;
    जबतक (rounds--)
        ff_sfc64_get(s);
}

#पूर्ण_अगर // AVUTIL_SFC64_H
