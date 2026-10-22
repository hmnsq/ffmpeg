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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_X86_INTREADWRITE_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_X86_INTREADWRITE_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਜੇ HAVE_INTRINSICS_SSE2 && defined(__SSE2__)
#ਅਨ੍ਤਰ੍ਭਾਵ <emmintrin.h>
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"

#ਜੇ HAVE_INTRINSICS_SSE2 && defined(__SSE2__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_COPY128 AV_COPY128
ਸਥਿਰ av_always_inline ਖਾਲੀ AV_COPY128(ਖਾਲੀ *d, ਅਚਲ ਖਾਲੀ *s)
{
    __m128i tmp = mm_ਲੱਦੋ_si128((ਅਚਲ __m128i *)s);
    _mm_store_si128((__m128i *)d, tmp);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_COPY128U AV_COPY128U
ਸਥਿਰ av_always_inline ਖਾਲੀ AV_COPY128U(ਖਾਲੀ *d, ਅਚਲ ਖਾਲੀ *s)
{
    __m128i tmp = _mm_loadu_si128((ਅਚਲ __m128i *)s);
    _mm_storeu_si128((__m128i *)d, tmp);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_ZERO128 AV_ZERO128
ਸਥਿਰ av_always_inline ਖਾਲੀ AV_ZERO128(ਖਾਲੀ *d)
{
    __m128i zero = _mm_setzero_si128();
    _mm_store_si128((__m128i *)d, zero);
}

#ਜੇ_ਅੰਤ /* HAVE_INTRINSICS_SSE2 && defined(__SSE2__) */

#ਜੇ_ਅੰਤ /* AVUTIL_X86_INTREADWRITE_H */
