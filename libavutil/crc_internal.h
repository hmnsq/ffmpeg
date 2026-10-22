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

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ "libavutil/attributes.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/reverse.h"

ସ୍ଥିର uint64_t reverse(uint64_t p, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା deg)
{
    uint64_t ret = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_reverse[p & 0xff]);
        p >>= 8;
    }
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_reverse[p & 0xff] >> (8 - rem));
    ଫେରନ୍ତୁ ret;
}

av_unused ସ୍ଥିର uint64_t xnmodp(unsigned n, uint64_t poly, unsigned deg,
                                 uint64_t *div, ପୂର୍ଣ୍ଣସଂଖ୍ୟା bitreverse)
{
    uint64_t mod, mask, ଉପର;

    ଯଦି (n < deg) {
        *div = 0;
        ଫେରନ୍ତୁ poly;
    }
    mask = ((uint64_t)1 << deg) - 1;
    poly &= mask;
    mod = poly;
    *div = 1;
    deg--;
    ଯେତେବେଳେ (--n > deg) {
        ଉପର = (mod >> deg) & 1;
        *div = (*div << 1) | ଉପର;
        mod <<= 1;
        ଯଦି (ଉପର)
            mod ^= poly;
    }
    uint64_t ret = mod & mask;
    ଯଦି (bitreverse) {
        *div = reverse(*div, deg) << 1;
        ଫେରନ୍ତୁ reverse(ret, deg) << 1;
    }
    ଫେରନ୍ତୁ ret;
}

#endif /* AVUTIL_CRC_INTERNAL_H */
