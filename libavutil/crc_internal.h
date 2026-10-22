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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/reverse.h"

स्थिर uint64_t reverse(uint64_t p, unsigned पूर्णाङ्क deg)
{
    uint64_t ret = 0;
    पूर्णाङ्क i;
    प्रति (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_reverse[p & 0xff]);
        p >>= 8;
    }
    पूर्णाङ्क rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_reverse[p & 0xff] >> (8 - rem));
    प्रत्यागम ret;
}

av_unused स्थिर uint64_t xnmodp(unsigned n, uint64_t poly, unsigned deg,
                                 uint64_t *div, पूर्णाङ्क bitreverse)
{
    uint64_t mod, mask, उच्चः;

    जइ (n < deg) {
        *div = 0;
        प्रत्यागम poly;
    }
    mask = ((uint64_t)1 << deg) - 1;
    poly &= mask;
    mod = poly;
    *div = 1;
    deg--;
    जाव (--n > deg) {
        उच्चः = (mod >> deg) & 1;
        *div = (*div << 1) | उच्चः;
        mod <<= 1;
        जइ (उच्चः)
            mod ^= poly;
    }
    uint64_t ret = mod & mask;
    जइ (bitreverse) {
        *div = reverse(*div, deg) << 1;
        प्रत्यागम reverse(ret, deg) << 1;
    }
    प्रत्यागम ret;
}

#endif /* AVUTIL_CRC_INTERNAL_H */
