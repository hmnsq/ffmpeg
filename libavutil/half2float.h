/*
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

#ifndef AVUTIL_HALF2FLOAT_H
#define AVUTIL_HALF2FLOAT_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "intfloat.h"

#ಅನ್ತರ್ಭಾವ "config.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ Half2FloatTables {
#ಯದಿ HAVE_FAST_FLOAT16
    uint8_t dummy;
#ಅನ್ಯಥಾ
    uint32_t mantissatable[3072];
    uint32_t exponenttable[64];
    uint16_t offsettable[64];
#endif
} Half2FloatTables;

ಶೂನ್ಯ ff_init_half2float_tables(Half2FloatTables *t);

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ uint32_t half2float(uint16_t h, ಧ್ರುವ Half2FloatTables *t)
{
#ಯದಿ HAVE_FAST_FLOAT16
    ಸಙ್ಘ {
        _Float16 f;
        uint16_t i;
    } u;
    u.i = h;
    ಪ್ರತ್ಯಾಗಮ av_float2int(u.f);
#ಅನ್ಯಥಾ
    uint32_t f;

    f = t->mantissatable[t->offsettable[h >> 10] + (h & 0x3ff)] + t->exponenttable[h >> 10];

    ಪ್ರತ್ಯಾಗಮ f;
#endif
}

#endif /* AVUTIL_HALF2FLOAT_H */
