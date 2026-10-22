/*
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ਚੱਕਰੀ_ਜਾਂਚ_ਅੰਦਰੂਨੀ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ਚੱਕਰੀ_ਜਾਂਚ_ਅੰਦਰੂਨੀ_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/reverse.h"

ਸਥਿਰ uint64_t ਉਲਟ(uint64_t p, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ deg)
{
    uint64_t ret = 0;
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_ਉਲਟ[p & 0xff]);
        p >>= 8;
    }
    ਪੂਰਨ rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_ਉਲਟ[p & 0xff] >> (8 - rem));
    ਵਾਪਸ ret;
}

av_ਅਣਵਰਤਿਆ ਸਥਿਰ uint64_t xnmodp(ਬਿਨਾਨਿਸ਼ਾਨੀ n, uint64_t poly, ਬਿਨਾਨਿਸ਼ਾਨੀ deg,
                                 uint64_t *div, ਪੂਰਨ bitreverse)
{
    uint64_t mod, ਨਕਾਬ_2, ਉੱਚਾ;

    ਜੇ (n < deg) {
        *div = 0;
        ਵਾਪਸ poly;
    }
    ਨਕਾਬ_2 = ((uint64_t)1 << deg) - 1;
    poly &= ਨਕਾਬ_2;
    mod = poly;
    *div = 1;
    deg--;
    ਜਦੋਂ (--n > deg) {
        ਉੱਚਾ = (mod >> deg) & 1;
        *div = (*div << 1) | ਉੱਚਾ;
        mod <<= 1;
        ਜੇ (ਉੱਚਾ)
            mod ^= poly;
    }
    uint64_t ret = mod & ਨਕਾਬ_2;
    ਜੇ (bitreverse) {
        *div = ਉਲਟ(*div, deg) << 1;
        ਵਾਪਸ ਉਲਟ(ret, deg) << 1;
    }
    ਵਾਪਸ ret;
}

#ਜੇ_ਅੰਤ /* AVUTIL_CRC_INTERNAL_H */
