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

#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ "intfloat.h"

#અન્તર્ભાવ "config.h"

પ્રકારવ્યાખ્યા સંરચના Half2FloatTables {
#જો HAVE_FAST_FLOAT16
    uint8_t dummy;
#નહીંતર
    uint32_t mantissatable[3072];
    uint32_t exponenttable[64];
    uint16_t offsettable[64];
#endif
} Half2FloatTables;

શૂન્ય ff_init_half2float_tables(Half2FloatTables *t);

સ્થિર અંતઃરેખ uint32_t half2float(uint16_t h, અચલ Half2FloatTables *t)
{
#જો HAVE_FAST_FLOAT16
    સંઘ {
        _Float16 f;
        uint16_t i;
    } u;
    u.i = h;
    પાછા av_float2int(u.f);
#નહીંતર
    uint32_t f;

    f = t->mantissatable[t->offsettable[h >> 10] + (h & 0x3ff)] + t->exponenttable[h >> 10];

    પાછા f;
#endif
}

#endif /* AVUTIL_HALF2FLOAT_H */
