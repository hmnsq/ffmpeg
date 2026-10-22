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

#నిర్వచితం_కాకపోతే AVUTIL_X86_INTREADWRITE_H
#నిర్వచించు AVUTIL_X86_INTREADWRITE_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "config.h"
#ఒకవేళ HAVE_INTRINSICS_SSE2 && defined(__SSE2__)
#అన్తర్భావ <emmintrin.h>
#అయితే_ముగింపు
#అన్తర్భావ "libavutil/attributes.h"

#ఒకవేళ HAVE_INTRINSICS_SSE2 && defined(__SSE2__)

#నిర్వచించు AV_COPY128 AV_COPY128
స్థిర av_always_inline శూన్య AV_COPY128(శూన్య *d, స్థిరరాశి శూన్య *s)
{
    __m128i tmp = mm_ఎక్కించు_si128((స్థిరరాశి __m128i *)s);
    _mm_store_si128((__m128i *)d, tmp);
}

#నిర్వచించు AV_COPY128U AV_COPY128U
స్థిర av_always_inline శూన్య AV_COPY128U(శూన్య *d, స్థిరరాశి శూన్య *s)
{
    __m128i tmp = _mm_loadu_si128((స్థిరరాశి __m128i *)s);
    _mm_storeu_si128((__m128i *)d, tmp);
}

#నిర్వచించు AV_ZERO128 AV_ZERO128
స్థిర av_always_inline శూన్య AV_ZERO128(శూన్య *d)
{
    __m128i zero = _mm_setzero_si128();
    _mm_store_si128((__m128i *)d, zero);
}

#అయితే_ముగింపు /* HAVE_INTRINSICS_SSE2 && defined(__SSE2__) */

#అయితే_ముగింపు /* AVUTIL_X86_INTREADWRITE_H */
