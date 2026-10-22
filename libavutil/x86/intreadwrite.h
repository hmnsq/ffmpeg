/*
 * Copyright (c) 2010 Alexander Strange <astrange@ithinksw.com>
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

#اگر_غیر_تعریف_شدہ AVUTIL_X86_INTREADWRITE_H
#تعریف_کرو AVUTIL_X86_INTREADWRITE_H

#شامل <stdint.h>
#شامل "config.h"
#اگر HAVE_INTRINSICS_SSE2 && defined(__SSE2__)
#شامل <emmintrin.h>
#اگر_ختم
#شامل "libavutil/attributes.h"

#اگر HAVE_INTRINSICS_SSE2 && defined(__SSE2__)

#تعریف_کرو AV_COPY128 AV_COPY128
ساکن av_always_inline خالی AV_COPY128(خالی *d, ثابت خالی *s)
{
    __m128i tmp = mm_بھرو_si128((ثابت __m128i *)s);
    _mm_store_si128((__m128i *)d, tmp);
}

#تعریف_کرو AV_COPY128U AV_COPY128U
ساکن av_always_inline خالی AV_COPY128U(خالی *d, ثابت خالی *s)
{
    __m128i tmp = _mm_loadu_si128((ثابت __m128i *)s);
    _mm_storeu_si128((__m128i *)d, tmp);
}

#تعریف_کرو AV_ZERO128 AV_ZERO128
ساکن av_always_inline خالی AV_ZERO128(خالی *d)
{
    __m128i zero = _mm_setzero_si128();
    _mm_store_si128((__m128i *)d, zero);
}

#اگر_ختم /* HAVE_INTRINSICS_SSE2 && defined(__SSE2__) */

#اگر_ختم /* AVUTIL_X86_INTREADWRITE_H */
