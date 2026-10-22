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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "attributes.h"

ಸಙ್ಘ av_intfloat32 {
    uint32_t i;
    ಭಿನ್ನ    f;
};

ಸಙ್ಘ av_intfloat64 {
    uint64_t i;
    ದ್ವಿಗುಣ   f;
};

/**
 * Reinterpret a 32-bit integer as a float.
 */
ಸ್ಥಿರ av_always_inline ಭಿನ್ನ av_int2float(uint32_t i)
{
    ಸಙ್ಘ av_intfloat32 v;
    v.i = i;
    ಪ್ರತ್ಯಾಗಮ v.f;
}

/**
 * Reinterpret a float as a 32-bit integer.
 */
ಸ್ಥಿರ av_always_inline uint32_t av_float2int(ಭಿನ್ನ f)
{
    ಸಙ್ಘ av_intfloat32 v;
    v.f = f;
    ಪ್ರತ್ಯಾಗಮ v.i;
}

/**
 * Reinterpret a 64-bit integer as a double.
 */
ಸ್ಥಿರ av_always_inline ದ್ವಿಗುಣ av_int2double(uint64_t i)
{
    ಸಙ್ಘ av_intfloat64 v;
    v.i = i;
    ಪ್ರತ್ಯಾಗಮ v.f;
}

/**
 * Reinterpret a double as a 64-bit integer.
 */
ಸ್ಥಿರ av_always_inline uint64_t av_double2int(ದ್ವಿಗುಣ f)
{
    ಸಙ್ಘ av_intfloat64 v;
    v.f = f;
    ಪ್ರತ್ಯಾಗಮ v.i;
}

#endif /* AVUTIL_INTFLOAT_H */
