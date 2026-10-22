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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_X86_INTREADWRITE_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_X86_INTREADWRITE_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "config.h"
#ಆದರೆ HAVE_INTRINSICS_SSE2 && defined(__SSE2__)
#ಅನ್ತರ್ಭಾವ <emmintrin.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"

#ಆದರೆ HAVE_INTRINSICS_SSE2 && defined(__SSE2__)

#ವ್ಯಾಖ್ಯಾನಿಸು AV_COPY128 AV_COPY128
ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ AV_COPY128(ಶೂನ್ಯ *d, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *s)
{
    __m128i tmp = mm_ತುಂಬು_si128((ಸ್ಥಿರಾಂಕ __m128i *)s);
    _mm_store_si128((__m128i *)d, tmp);
}

#ವ್ಯಾಖ್ಯಾನಿಸು AV_COPY128U AV_COPY128U
ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ AV_COPY128U(ಶೂನ್ಯ *d, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *s)
{
    __m128i tmp = _mm_loadu_si128((ಸ್ಥಿರಾಂಕ __m128i *)s);
    _mm_storeu_si128((__m128i *)d, tmp);
}

#ವ್ಯಾಖ್ಯಾನಿಸು AV_ZERO128 AV_ZERO128
ಸ್ಥಿರ av_always_inline ಶೂನ್ಯ AV_ZERO128(ಶೂನ್ಯ *d)
{
    __m128i zero = _mm_setzero_si128();
    _mm_store_si128((__m128i *)d, zero);
}

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_INTRINSICS_SSE2 && defined(__SSE2__) */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_X86_INTREADWRITE_H */
