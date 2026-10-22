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

#ifndef AVUTIL_CRC_INTERNAL_H
#define AVUTIL_CRC_INTERNAL_H

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ "libavutil/attributes.h"
#அந்தர்பாவ "libavutil/reverse.h"

நிலையான uint64_t reverse(uint64_t p, unsigned முழு deg)
{
    uint64_t ret = 0;
    முழு i;
    க்கு (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_reverse[p & 0xff]);
        p >>= 8;
    }
    முழு rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_reverse[p & 0xff] >> (8 - rem));
    திரும்பு ret;
}

av_unused நிலையான uint64_t xnmodp(unsigned n, uint64_t poly, unsigned deg,
                                 uint64_t *div, முழு bitreverse)
{
    uint64_t mod, mask, உயர்வு;

    எனில் (n < deg) {
        *div = 0;
        திரும்பு poly;
    }
    mask = ((uint64_t)1 << deg) - 1;
    poly &= mask;
    mod = poly;
    *div = 1;
    deg--;
    போது (--n > deg) {
        உயர்வு = (mod >> deg) & 1;
        *div = (*div << 1) | உயர்வு;
        mod <<= 1;
        எனில் (உயர்வு)
            mod ^= poly;
    }
    uint64_t ret = mod & mask;
    எனில் (bitreverse) {
        *div = reverse(*div, deg) << 1;
        திரும்பு reverse(ret, deg) << 1;
    }
    திரும்பு ret;
}

#endif /* AVUTIL_CRC_INTERNAL_H */
