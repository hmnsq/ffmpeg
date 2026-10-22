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

#ifndef AVUTIL_X86_INTREADWRITE_H
#define AVUTIL_X86_INTREADWRITE_H

#شامل <stdint.h>
#شامل "config.h"
#اگر HAVE_INTRINSICS_SSE2 && defined(__SSE2__)
#شامل <emmintrin.h>
#endif
#شامل "libavutil/attributes.h"

#اگر HAVE_INTRINSICS_SSE2 && defined(__SSE2__)

#define AV_COPY128 AV_COPY128
ایستا av_always_inline تهی AV_COPY128(تهی *d, ثابت تهی *s)
{
    __m128i tmp = _mm_load_si128((ثابت __m128i *)s);
    _mm_store_si128((__m128i *)d, tmp);
}

#define AV_COPY128U AV_COPY128U
ایستا av_always_inline تهی AV_COPY128U(تهی *d, ثابت تهی *s)
{
    __m128i tmp = _mm_loadu_si128((ثابت __m128i *)s);
    _mm_storeu_si128((__m128i *)d, tmp);
}

#define AV_ZERO128 AV_ZERO128
ایستا av_always_inline تهی AV_ZERO128(تهی *d)
{
    __m128i zero = _mm_setzero_si128();
    _mm_store_si128((__m128i *)d, zero);
}

#endif /* HAVE_INTRINSICS_SSE2 && defined(__SSE2__) */

#endif /* AVUTIL_X86_INTREADWRITE_H */
