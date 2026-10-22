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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/reverse.h"

ಸ್ಥಿರ uint64_t reverse(uint64_t p, unsigned ಪೂರ್ಣಾಙ್ಕ deg)
{
    uint64_t ret = 0;
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_reverse[p & 0xff]);
        p >>= 8;
    }
    ಪೂರ್ಣಾಙ್ಕ rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_reverse[p & 0xff] >> (8 - rem));
    ಪ್ರತ್ಯಾಗಮ ret;
}

av_unused ಸ್ಥಿರ uint64_t xnmodp(unsigned n, uint64_t poly, unsigned deg,
                                 uint64_t *div, ಪೂರ್ಣಾಙ್ಕ bitreverse)
{
    uint64_t mod, mask, ಮೇಲಿನ;

    ಯದಿ (n < deg) {
        *div = 0;
        ಪ್ರತ್ಯಾಗಮ poly;
    }
    mask = ((uint64_t)1 << deg) - 1;
    poly &= mask;
    mod = poly;
    *div = 1;
    deg--;
    ಯಾವತ್ (--n > deg) {
        ಮೇಲಿನ = (mod >> deg) & 1;
        *div = (*div << 1) | ಮೇಲಿನ;
        mod <<= 1;
        ಯದಿ (ಮೇಲಿನ)
            mod ^= poly;
    }
    uint64_t ret = mod & mask;
    ಯದಿ (bitreverse) {
        *div = reverse(*div, deg) << 1;
        ಪ್ರತ್ಯಾಗಮ reverse(ret, deg) << 1;
    }
    ಪ್ರತ್ಯಾಗಮ ret;
}

#endif /* AVUTIL_CRC_INTERNAL_H */
