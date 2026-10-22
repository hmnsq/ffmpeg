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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "intfloat.h"

#अन्तर्भाव "config.h"

प्रकारनिर्देश संरचना Half2FloatTables {
#जइ HAVE_FAST_FLOAT16
    uint8_t dummy;
#अण्णहा
    uint32_t mantissatable[3072];
    uint32_t exponenttable[64];
    uint16_t offsettable[64];
#endif
} Half2FloatTables;

शून्य ff_init_half2float_tables(Half2FloatTables *t);

स्थिर अन्तःस्थ uint32_t half2float(uint16_t h, ध्रुव Half2FloatTables *t)
{
#जइ HAVE_FAST_FLOAT16
    सङ्घ {
        _Float16 f;
        uint16_t i;
    } u;
    u.i = h;
    प्रत्यागम av_float2int(u.f);
#अण्णहा
    uint32_t f;

    f = t->mantissatable[t->offsettable[h >> 10] + (h & 0x3ff)] + t->exponenttable[h >> 10];

    प्रत्यागम f;
#endif
}

#endif /* AVUTIL_HALF2FLOAT_H */
