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

#ifndef AVUTIL_FLOAT2HALF_H
#define AVUTIL_FLOAT2HALF_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "intfloat.h"

#अन्तर्भाव "config.h"

प्रकारनिर्देश संरचना Float2HalfTables {
#यदि HAVE_FAST_FLOAT16
    uint8_t dummy;
#अन्यथा
    uint16_t basetable[512];
    uint8_t shifttable[512];
#endif
} Float2HalfTables;

शून्य ff_init_float2half_tables(Float2HalfTables *t);

स्थिर अन्तःस्थ uint16_t float2half(uint32_t f, ध्रुव Float2HalfTables *t)
{
#यदि HAVE_FAST_FLOAT16
    सङ्घ {
        _Float16 f;
        uint16_t i;
    } u;
    u.f = av_int2float(f);
    प्रत्यागम u.i;
#अन्यथा
    uint16_t h;

    h = t->basetable[(f >> 23) & 0x1ff] + ((f & 0x007fffff) >> t->shifttable[(f >> 23) & 0x1ff]);

    प्रत्यागम h;
#endif
}

#endif /* AVUTIL_FLOAT2HALF_H */
