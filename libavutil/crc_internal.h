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

#شامل <stdint.h>
#شامل "libavutil/attributes.h"
#شامل "libavutil/reverse.h"

ایستا uint64_t reverse(uint64_t p, unsigned صحیح deg)
{
    uint64_t ret = 0;
    صحیح i;
    برای (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_reverse[p & 0xff]);
        p >>= 8;
    }
    صحیح rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_reverse[p & 0xff] >> (8 - rem));
    بازگشت ret;
}

av_unused ایستا uint64_t xnmodp(unsigned n, uint64_t poly, unsigned deg,
                                 uint64_t *div, صحیح bitreverse)
{
    uint64_t mod, mask, بالا;

    اگر (n < deg) {
        *div = 0;
        بازگشت poly;
    }
    mask = ((uint64_t)1 << deg) - 1;
    poly &= mask;
    mod = poly;
    *div = 1;
    deg--;
    وقتی (--n > deg) {
        بالا = (mod >> deg) & 1;
        *div = (*div << 1) | بالا;
        mod <<= 1;
        اگر (بالا)
            mod ^= poly;
    }
    uint64_t ret = mod & mask;
    اگر (bitreverse) {
        *div = reverse(*div, deg) << 1;
        بازگشت reverse(ret, deg) << 1;
    }
    بازگشت ret;
}

#endif /* AVUTIL_CRC_INTERNAL_H */
