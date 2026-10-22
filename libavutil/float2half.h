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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_FLOAT2HALF_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_FLOAT2HALF_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "intfloat.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Float2HalfTables {
#ਜੇ HAVE_FAST_FLOAT16
    uint8_t dummy;
#ਨਹੀਂਤਾਂ
    uint16_t basetable[512];
    uint8_t shifttable[512];
#ਜੇ_ਅੰਤ
} Float2HalfTables;

ਖਾਲੀ ff_init_float2half_tables(Float2HalfTables *t);

ਸਥਿਰ ਸਤਰਅੰਦਰ uint16_t float2half(uint32_t f, ਅਚਲ Float2HalfTables *t)
{
#ਜੇ HAVE_FAST_FLOAT16
    ਸੰਘ {
        _Float16 f;
        uint16_t i;
    } u;
    u.f = av_int2float(f);
    ਵਾਪਸ u.i;
#ਨਹੀਂਤਾਂ
    uint16_t h;

    h = t->basetable[(f >> 23) & 0x1ff] + ((f & 0x007fffff) >> t->shifttable[(f >> 23) & 0x1ff]);

    ਵਾਪਸ h;
#ਜੇ_ਅੰਤ
}

#ਜੇ_ਅੰਤ /* AVUTIL_FLOAT2HALF_H */
