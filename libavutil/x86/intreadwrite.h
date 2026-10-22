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

#अगर_अघोषित AVUTIL_X86_INTREADWRITE_H
#घोषणा AVUTIL_X86_INTREADWRITE_H

#समावेश <stdint.h>
#समावेश "config.h"
#अगर HAVE_INTRINSICS_SSE2 && defined(__SSE2__)
#समावेश <emmintrin.h>
#पूर्ण_अगर
#समावेश "libavutil/attributes.h"

#अगर HAVE_INTRINSICS_SSE2 && defined(__SSE2__)

#घोषणा AV_COPY128 AV_COPY128
अटल av_always_inline व्योम AV_COPY128(व्योम *d, स्थिर व्योम *s)
{
    __m128i tmp = _mm_load_si128((स्थिर __m128i *)s);
    _mm_store_si128((__m128i *)d, tmp);
}

#घोषणा AV_COPY128U AV_COPY128U
अटल av_always_inline व्योम AV_COPY128U(व्योम *d, स्थिर व्योम *s)
{
    __m128i tmp = _mm_loadu_si128((स्थिर __m128i *)s);
    _mm_storeu_si128((__m128i *)d, tmp);
}

#घोषणा AV_ZERO128 AV_ZERO128
अटल av_always_inline व्योम AV_ZERO128(व्योम *d)
{
    __m128i zero = _mm_setzero_si128();
    _mm_store_si128((__m128i *)d, zero);
}

#पूर्ण_अगर /* HAVE_INTRINSICS_SSE2 && defined(__SSE2__) */

#पूर्ण_अगर /* AVUTIL_X86_INTREADWRITE_H */
