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

#ifndef AVUTIL_INTFLOAT_H
#define AVUTIL_INTFLOAT_H

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব "attributes.h"

সঙ্ঘ av_intfloat32 {
    uint32_t i;
    ভিন্ন    f;
};

সঙ্ঘ av_intfloat64 {
    uint64_t i;
    দ্বিগুণ   f;
};

/**
 * Reinterpret a 32-bit integer as a float.
 */
স্থির av_always_inline ভিন্ন av_int2float(uint32_t i)
{
    সঙ্ঘ av_intfloat32 v;
    v.i = i;
    প্রত্যাগম v.f;
}

/**
 * Reinterpret a float as a 32-bit integer.
 */
স্থির av_always_inline uint32_t av_float2int(ভিন্ন f)
{
    সঙ্ঘ av_intfloat32 v;
    v.f = f;
    প্রত্যাগম v.i;
}

/**
 * Reinterpret a 64-bit integer as a double.
 */
স্থির av_always_inline দ্বিগুণ av_int2double(uint64_t i)
{
    সঙ্ঘ av_intfloat64 v;
    v.i = i;
    প্রত্যাগম v.f;
}

/**
 * Reinterpret a double as a 64-bit integer.
 */
স্থির av_always_inline uint64_t av_double2int(দ্বিগুণ f)
{
    সঙ্ঘ av_intfloat64 v;
    v.f = f;
    প্রত্যাগম v.i;
}

#endif /* AVUTIL_INTFLOAT_H */
