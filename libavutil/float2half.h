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

#अगर_अघोषित AVUTIL_FLOAT2HALF_H
#घोषणा AVUTIL_FLOAT2HALF_H

#समावेश <stdint.h>
#समावेश "intfloat.h"

#समावेश "config.h"

प्रकार काष्ठा Float2HalfTables {
#अगर HAVE_FAST_FLOAT16
    uint8_t dummy;
#अन्यथा
    uint16_t basetable[512];
    uint8_t shifttable[512];
#पूर्ण_अगर
} Float2HalfTables;

व्योम ff_init_float2half_tables(Float2HalfTables *t);

अटल अंतरभूत uint16_t float2half(uint32_t f, स्थिर Float2HalfTables *t)
{
#अगर HAVE_FAST_FLOAT16
    जोड़ {
        _Float16 f;
        uint16_t i;
    } u;
    u.f = av_int2float(f);
    वापस u.i;
#अन्यथा
    uint16_t h;

    h = t->basetable[(f >> 23) & 0x1ff] + ((f & 0x007fffff) >> t->shifttable[(f >> 23) & 0x1ff]);

    वापस h;
#पूर्ण_अगर
}

#पूर्ण_अगर /* AVUTIL_FLOAT2HALF_H */
