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

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ "attributes.h"

ସଂଘ av_intfloat32 {
    uint32_t i;
    ଦଶମିକ    f;
};

ସଂଘ av_intfloat64 {
    uint64_t i;
    ଦ୍ୱିଗୁଣ   f;
};

/**
 * Reinterpret a 32-bit integer as a float.
 */
ସ୍ଥିର av_always_inline ଦଶମିକ av_int2float(uint32_t i)
{
    ସଂଘ av_intfloat32 v;
    v.i = i;
    ଫେରନ୍ତୁ v.f;
}

/**
 * Reinterpret a float as a 32-bit integer.
 */
ସ୍ଥିର av_always_inline uint32_t av_float2int(ଦଶମିକ f)
{
    ସଂଘ av_intfloat32 v;
    v.f = f;
    ଫେରନ୍ତୁ v.i;
}

/**
 * Reinterpret a 64-bit integer as a double.
 */
ସ୍ଥିର av_always_inline ଦ୍ୱିଗୁଣ av_int2double(uint64_t i)
{
    ସଂଘ av_intfloat64 v;
    v.i = i;
    ଫେରନ୍ତୁ v.f;
}

/**
 * Reinterpret a double as a 64-bit integer.
 */
ସ୍ଥିର av_always_inline uint64_t av_double2int(ଦ୍ୱିଗୁଣ f)
{
    ସଂଘ av_intfloat64 v;
    v.f = f;
    ଫେରନ୍ତୁ v.i;
}

#endif /* AVUTIL_INTFLOAT_H */
