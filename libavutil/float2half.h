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

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ "intfloat.h"

#அந்தர்பாவ "config.h"

வகைவரை கட்டமைப்பு Float2HalfTables {
#எனில் HAVE_FAST_FLOAT16
    uint8_t dummy;
#இல்லையெனில்
    uint16_t basetable[512];
    uint8_t shifttable[512];
#endif
} Float2HalfTables;

வெறுமை ff_init_float2half_tables(Float2HalfTables *t);

நிலையான உள்வரி uint16_t float2half(uint32_t f, மாறிலி Float2HalfTables *t)
{
#எனில் HAVE_FAST_FLOAT16
    ஒன்றிப்பு {
        _Float16 f;
        uint16_t i;
    } u;
    u.f = av_int2float(f);
    திரும்பு u.i;
#இல்லையெனில்
    uint16_t h;

    h = t->basetable[(f >> 23) & 0x1ff] + ((f & 0x007fffff) >> t->shifttable[(f >> 23) & 0x1ff]);

    திரும்பு h;
#endif
}

#endif /* AVUTIL_FLOAT2HALF_H */
