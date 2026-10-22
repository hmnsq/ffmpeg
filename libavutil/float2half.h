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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_FLOAT2HALF_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_FLOAT2HALF_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "intfloat.h"

#ಅನ್ತರ್ಭಾವ "config.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Float2HalfTables {
#ಆದರೆ HAVE_FAST_FLOAT16
    uint8_t dummy;
#ಇಲ್ಲದಿದ್ದರೆ
    uint16_t basetable[512];
    uint8_t shifttable[512];
#ಆದರೆ_ಅಂತ್ಯ
} Float2HalfTables;

ಶೂನ್ಯ ff_init_float2half_tables(Float2HalfTables *t);

ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint16_t float2half(uint32_t f, ಸ್ಥಿರಾಂಕ Float2HalfTables *t)
{
#ಆದರೆ HAVE_FAST_FLOAT16
    ಒಕ್ಕೂಟ {
        _Float16 f;
        uint16_t i;
    } u;
    u.f = av_int2float(f);
    ಹಿಂತಿರುಗಿ u.i;
#ಇಲ್ಲದಿದ್ದರೆ
    uint16_t h;

    h = t->basetable[(f >> 23) & 0x1ff] + ((f & 0x007fffff) >> t->shifttable[(f >> 23) & 0x1ff]);

    ಹಿಂತಿರುಗಿ h;
#ಆದರೆ_ಅಂತ್ಯ
}

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_FLOAT2HALF_H */
