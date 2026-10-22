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

#నిర్వచితం_కాకపోతే AVUTIL_HALF2FLOAT_H
#నిర్వచించు AVUTIL_HALF2FLOAT_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "intfloat.h"

#అన్తర్భావ "config.h"

రకనిర్వచనం నిర్మాణం Half2FloatTables {
#ఒకవేళ HAVE_FAST_FLOAT16
    uint8_t dummy;
#లేకపోతే
    uint32_t mantissatable[3072];
    uint32_t exponenttable[64];
    uint16_t offsettable[64];
#అయితే_ముగింపు
} Half2FloatTables;

శూన్య ff_init_half2float_tables(Half2FloatTables *t);

స్థిర అంతఃవరుస uint32_t half2float(uint16_t h, స్థిరరాశి Half2FloatTables *t)
{
#ఒకవేళ HAVE_FAST_FLOAT16
    సంఘం {
        _Float16 f;
        uint16_t i;
    } u;
    u.i = h;
    తిరిగి av_float2int(u.f);
#లేకపోతే
    uint32_t f;

    f = t->mantissatable[t->offsettable[h >> 10] + (h & 0x3ff)] + t->exponenttable[h >> 10];

    తిరిగి f;
#అయితే_ముగింపు
}

#అయితే_ముగింపు /* AVUTIL_HALF2FLOAT_H */
