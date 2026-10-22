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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_HALF2FLOAT_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_HALF2FLOAT_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "intfloat.h"

#ಅನ್ತರ್ಭಾವ "config.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Half2FloatTables {
#ಆದರೆ HAVE_FAST_FLOAT16
    uint8_t dummy;
#ಇಲ್ಲದಿದ್ದರೆ
    uint32_t mantissatable[3072];
    uint32_t exponenttable[64];
    uint16_t offsettable[64];
#ಆದರೆ_ಅಂತ್ಯ
} Half2FloatTables;

ಶೂನ್ಯ ff_init_half2float_tables(Half2FloatTables *t);

ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint32_t half2float(uint16_t h, ಸ್ಥಿರಾಂಕ Half2FloatTables *t)
{
#ಆದರೆ HAVE_FAST_FLOAT16
    ಒಕ್ಕೂಟ {
        _Float16 f;
        uint16_t i;
    } u;
    u.i = h;
    ಹಿಂತಿರುಗಿ av_float2int(u.f);
#ಇಲ್ಲದಿದ್ದರೆ
    uint32_t f;

    f = t->mantissatable[t->offsettable[h >> 10] + (h & 0x3ff)] + t->exponenttable[h >> 10];

    ಹಿಂತಿರುಗಿ f;
#ಆದರೆ_ಅಂತ್ಯ
}

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_HALF2FLOAT_H */
