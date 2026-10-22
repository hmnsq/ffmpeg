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

#اگر_غیر_تعریف_شدہ AVUTIL_SFC64_H
#تعریف_کرو AVUTIL_SFC64_H

#شامل <inttypes.h>

قسمتعریف ساخت FFSFC64 {
    uint64_t a,b,c,شمار_2;
} FFSFC64;

ساکن اندرونی uint64_t ff_sfc64_get(FFSFC64 *s) {
    uint64_t tmp = s->a + s->b + s->شمار_2++;
    s->a = s->b ^ (s->b >> 11);
    s->b = s->c + (s->c << 3); // This is a multiply by 9
    s->c = (s->c << 24 | s->c >> 40) + tmp;
    واپس tmp;
}

/**
 * Return the previous random value, and step the generator backward.
 *
 * It is safe to take values before the first, but such values can be highly
 * correlated to the seeds.
 */
ساکن اندرونی uint64_t ff_sfc64_الٹ_get(FFSFC64 *s) {
    uint64_t پچھلا_c = s->b * 0x8E38E38E38E38E39;
    uint64_t tmp = s->c - (پچھلا_c << 24 | پچھلا_c >> 40);
    s->b = s->a ^ (s->a >> 11);
    s->b ^= s->b >> 22;
    s->b ^= s->b >> 44;

    s->a = tmp - s->b - --s->شمار_2;
    s->c = پچھلا_c;

    واپس tmp;
}

/**
 * Initialize sfc64 with up to 3 seeds.
 *
 * @param rounds number of rounds mixing up state during init. Generally 8-18, larger numbers will help with bad quality seeds.
 *               12 is a good choice if all 3 seeds are equal
 *
 */
ساکن اندرونی خالی ff_sfc64_init(FFSFC64 *s, uint64_t seeda, uint64_t seedb, uint64_t seedc, صحیح دور) {
    s->a       = seeda;
    s->b       = seedb;
    s->c       = seedc;
    s->شمار_2 = 1;
    جب (دور--)
        ff_sfc64_get(s);
}

#اگر_ختم // AVUTIL_SFC64_H
