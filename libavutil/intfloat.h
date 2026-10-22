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

#నిర్వచితం_కాకపోతే AVUTIL_INTFLOAT_H
#నిర్వచించు AVUTIL_INTFLOAT_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "attributes.h"

సంఘం av_intfloat32 {
    uint32_t i;
    దశాంశం    f;
};

సంఘం av_intfloat64 {
    uint64_t i;
    ద్విగుణ   f;
};

/**
 * Reinterpret a 32-bit integer as a float.
 */
స్థిర av_always_inline దశాంశం av_int2float(uint32_t i)
{
    సంఘం av_intfloat32 v;
    v.i = i;
    తిరిగి v.f;
}

/**
 * Reinterpret a float as a 32-bit integer.
 */
స్థిర av_always_inline uint32_t av_float2int(దశాంశం f)
{
    సంఘం av_intfloat32 v;
    v.f = f;
    తిరిగి v.i;
}

/**
 * Reinterpret a 64-bit integer as a double.
 */
స్థిర av_always_inline ద్విగుణ av_int2double(uint64_t i)
{
    సంఘం av_intfloat64 v;
    v.i = i;
    తిరిగి v.f;
}

/**
 * Reinterpret a double as a 64-bit integer.
 */
స్థిర av_always_inline uint64_t av_double2int(ద్విగుణ f)
{
    సంఘం av_intfloat64 v;
    v.f = f;
    తిరిగి v.i;
}

#అయితే_ముగింపు /* AVUTIL_INTFLOAT_H */
