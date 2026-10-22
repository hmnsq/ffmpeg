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

स्थिर uint64_t reverse(uint64_t p, अचिन्हित पूर्णांक deg)
{
    uint64_t ret = 0;
    पूर्णांक i;
    साठी (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_reverse[p & 0xff]);
        p >>= 8;
    }
    पूर्णांक rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_reverse[p & 0xff] >> (8 - rem));
    परत ret;
}

av_unused स्थिर uint64_t xnmodp(अचिन्हित n, uint64_t poly, अचिन्हित deg,
                                 uint64_t *भाग, पूर्णांक bitreverse)
{
    uint64_t mod, mask, वरचा;

    जर (n < deg) {
        *भाग = 0;
        परत poly;
    }
    mask = ((uint64_t)1 << deg) - 1;
    poly &= mask;
    mod = poly;
    *भाग = 1;
    deg--;
    पर्यंत (--n > deg) {
        वरचा = (mod >> deg) & 1;
        *भाग = (*भाग << 1) | वरचा;
        mod <<= 1;
        जर (वरचा)
            mod ^= poly;
    }
    uint64_t ret = mod & mask;
    जर (bitreverse) {
        *भाग = reverse(*भाग, deg) << 1;
        परत reverse(ret, deg) << 1;
    }
    परत ret;
}

#endif /* AVUTIL_CRC_INTERNAL_H */
