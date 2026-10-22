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

#اگر_غیر_تعریف_شدہ AVUTIL_HALF2FLOAT_H
#تعریف_کرو AVUTIL_HALF2FLOAT_H

#شامل <stdint.h>
#شامل "intfloat.h"

#شامل "config.h"

قسمتعریف ساخت Half2FloatTables {
#اگر HAVE_FAST_FLOAT16
    uint8_t dummy;
#ورنہ
    uint32_t mantissatable[3072];
    uint32_t exponenttable[64];
    uint16_t offsettable[64];
#اگر_ختم
} Half2FloatTables;

خالی ff_init_half2float_tables(Half2FloatTables *t);

ساکن اندرونی uint32_t half2float(uint16_t h, ثابت Half2FloatTables *t)
{
#اگر HAVE_FAST_FLOAT16
    اتحاد {
        _Float16 f;
        uint16_t i;
    } u;
    u.i = h;
    واپس av_float2int(u.f);
#ورنہ
    uint32_t f;

    f = t->mantissatable[t->offsettable[h >> 10] + (h & 0x3ff)] + t->exponenttable[h >> 10];

    واپس f;
#اگر_ختم
}

#اگر_ختم /* AVUTIL_HALF2FLOAT_H */
