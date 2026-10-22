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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_HALF2FLOAT_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_HALF2FLOAT_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "intfloat.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Half2FloatTables {
#ਜੇ HAVE_FAST_FLOAT16
    uint8_t dummy;
#ਨਹੀਂਤਾਂ
    uint32_t mantissatable[3072];
    uint32_t exponenttable[64];
    uint16_t offsettable[64];
#ਜੇ_ਅੰਤ
} Half2FloatTables;

ਖਾਲੀ ff_init_half2float_tables(Half2FloatTables *t);

ਸਥਿਰ ਸਤਰਅੰਦਰ uint32_t half2float(uint16_t h, ਅਚਲ Half2FloatTables *t)
{
#ਜੇ HAVE_FAST_FLOAT16
    ਸੰਘ {
        _Float16 f;
        uint16_t i;
    } u;
    u.i = h;
    ਵਾਪਸ av_float2int(u.f);
#ਨਹੀਂਤਾਂ
    uint32_t f;

    f = t->mantissatable[t->offsettable[h >> 10] + (h & 0x3ff)] + t->exponenttable[h >> 10];

    ਵਾਪਸ f;
#ਜੇ_ਅੰਤ
}

#ਜੇ_ਅੰਤ /* AVUTIL_HALF2FLOAT_H */
