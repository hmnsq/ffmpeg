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

#अगर_अघोषित AVUTIL_HALF2FLOAT_H
#घोषणा AVUTIL_HALF2FLOAT_H

#समावेश <stdint.h>
#समावेश "intfloat.h"

#समावेश "config.h"

प्रकार काष्ठा Half2FloatTables {
#अगर HAVE_FAST_FLOAT16
    uint8_t dummy;
#अन्यथा
    uint32_t mantissatable[3072];
    uint32_t exponenttable[64];
    uint16_t offsettable[64];
#पूर्ण_अगर
} Half2FloatTables;

व्योम ff_init_half2float_tables(Half2FloatTables *t);

अटल अंतरभूत uint32_t half2float(uint16_t h, स्थिर Half2FloatTables *t)
{
#अगर HAVE_FAST_FLOAT16
    जोड़ {
        _Float16 f;
        uint16_t i;
    } u;
    u.i = h;
    वापस av_float2int(u.f);
#अन्यथा
    uint32_t f;

    f = t->mantissatable[t->offsettable[h >> 10] + (h & 0x3ff)] + t->exponenttable[h >> 10];

    वापस f;
#पूर्ण_अगर
}

#पूर्ण_अगर /* AVUTIL_HALF2FLOAT_H */
