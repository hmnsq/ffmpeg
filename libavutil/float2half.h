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

#اگر_تعریف_نشده AVUTIL_FLOAT2HALF_H
#تعریف_کن AVUTIL_FLOAT2HALF_H

#ضمن <stdint.h>
#ضمن "intfloat.h"

#ضمن "config.h"

تعريفنوع بنية Float2HalfTables {
#إذا HAVE_FAST_FLOAT16
    uint8_t dummy;
#وإلا
    uint16_t basetable[512];
    uint8_t shifttable[512];
#پایان_اگر
} Float2HalfTables;

فراغ ff_init_float2half_tables(Float2HalfTables *t);

ساكن مضمن uint16_t float2half(uint32_t f, ثابت Float2HalfTables *t)
{
#إذا HAVE_FAST_FLOAT16
    اتحاد {
        _Float16 f;
        uint16_t i;
    } u;
    u.f = av_int2float(f);
    أرجع u.i;
#وإلا
    uint16_t h;

    h = t->basetable[(f >> 23) & 0x1ff] + ((f & 0x007fffff) >> t->shifttable[(f >> 23) & 0x1ff]);

    أرجع h;
#پایان_اگر
}

#پایان_اگر /* AVUTIL_FLOAT2HALF_H */
