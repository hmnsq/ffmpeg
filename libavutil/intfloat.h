/*
 * Copyright (c) 2011 Mans Rullgard
 *
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

#यदि_अपरिभाषितम् AVUTIL_INTFLOAT_H
#परिभाषय AVUTIL_INTFLOAT_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "attributes.h"

सङ्घ av_intfloat32 {
    uint32_t i;
    भिन्न    f;
};

सङ्घ av_intfloat64 {
    uint64_t i;
    द्विगुण   f;
};

/**
 * Reinterpret a 32-bit integer as a float.
 */
स्थिर av_always_inline भिन्न av_int2float(uint32_t i)
{
    सङ्घ av_intfloat32 v;
    v.i = i;
    प्रत्यागम v.f;
}

/**
 * Reinterpret a float as a 32-bit integer.
 */
स्थिर av_always_inline uint32_t av_float2int(भिन्न f)
{
    सङ्घ av_intfloat32 v;
    v.f = f;
    प्रत्यागम v.i;
}

/**
 * Reinterpret a 64-bit integer as a double.
 */
स्थिर av_always_inline द्विगुण av_int2double(uint64_t i)
{
    सङ्घ av_intfloat64 v;
    v.i = i;
    प्रत्यागम v.f;
}

/**
 * Reinterpret a double as a 64-bit integer.
 */
स्थिर av_always_inline uint64_t av_double2int(द्विगुण f)
{
    सङ्घ av_intfloat64 v;
    v.f = f;
    प्रत्यागम v.i;
}

#यदि_अन्तः /* AVUTIL_INTFLOAT_H */
