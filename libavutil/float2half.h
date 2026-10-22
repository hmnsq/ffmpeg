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

#నిర్వచితం_కాకపోతే AVUTIL_FLOAT2HALF_H
#నిర్వచించు AVUTIL_FLOAT2HALF_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "intfloat.h"

#అన్తర్భావ "config.h"

రకనిర్వచనం నిర్మాణం Float2HalfTables {
#ఒకవేళ HAVE_FAST_FLOAT16
    uint8_t dummy;
#లేకపోతే
    uint16_t basetable[512];
    uint8_t shifttable[512];
#అయితే_ముగింపు
} Float2HalfTables;

శూన్య ff_init_float2half_tables(Float2HalfTables *t);

స్థిర అంతఃవరుస uint16_t float2half(uint32_t f, స్థిరరాశి Float2HalfTables *t)
{
#ఒకవేళ HAVE_FAST_FLOAT16
    సంఘం {
        _Float16 f;
        uint16_t i;
    } u;
    u.f = av_int2float(f);
    తిరిగి u.i;
#లేకపోతే
    uint16_t h;

    h = t->basetable[(f >> 23) & 0x1ff] + ((f & 0x007fffff) >> t->shifttable[(f >> 23) & 0x1ff]);

    తిరిగి h;
#అయితే_ముగింపు
}

#అయితే_ముగింపు /* AVUTIL_FLOAT2HALF_H */
