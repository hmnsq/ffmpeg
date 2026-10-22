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

#جے_بنا_تعریف AVUTIL_INTFLOAT_H
#تعریف_کرو AVUTIL_INTFLOAT_H

#ضمن <stdint.h>
#ضمن "attributes.h"

اتحاد av_intfloat32 {
    uint32_t i;
    عائم    f;
};

اتحاد av_intfloat64 {
    uint64_t i;
    مزدوج   f;
};

/**
 * Reinterpret a 32-bit integer as a float.
 */
ساكن av_always_inline عائم av_int2float(uint32_t i)
{
    اتحاد av_intfloat32 v;
    v.i = i;
    أرجع v.f;
}

/**
 * Reinterpret a float as a 32-bit integer.
 */
ساكن av_always_inline uint32_t av_float2int(عائم f)
{
    اتحاد av_intfloat32 v;
    v.f = f;
    أرجع v.i;
}

/**
 * Reinterpret a 64-bit integer as a double.
 */
ساكن av_always_inline مزدوج av_int2double(uint64_t i)
{
    اتحاد av_intfloat64 v;
    v.i = i;
    أرجع v.f;
}

/**
 * Reinterpret a double as a 64-bit integer.
 */
ساكن av_always_inline uint64_t av_double2int(مزدوج f)
{
    اتحاد av_intfloat64 v;
    v.f = f;
    أرجع v.i;
}

#جے_انت /* AVUTIL_INTFLOAT_H */
