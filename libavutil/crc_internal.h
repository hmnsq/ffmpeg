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

#اگر_غیر_تعریف_شدہ AVUTIL_چکری_جانچ_اندرونی_H
#تعریف_کرو AVUTIL_چکری_جانچ_اندرونی_H

#شامل <stdint.h>
#شامل "libavutil/attributes.h"
#شامل "libavutil/reverse.h"

ساکن uint64_t الٹ(uint64_t p, غیرعلامتی صحیح deg)
{
    uint64_t ret = 0;
    صحیح i;
    برائے (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_الٹ[p & 0xff]);
        p >>= 8;
    }
    صحیح rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_الٹ[p & 0xff] >> (8 - rem));
    واپس ret;
}

av_غیر_مستعمل ساکن uint64_t xnmodp(غیرعلامتی n, uint64_t poly, غیرعلامتی deg,
                                 uint64_t *div, صحیح bitreverse)
{
    uint64_t mod, نقاب_2, بلند;

    اگر (n < deg) {
        *div = 0;
        واپس poly;
    }
    نقاب_2 = ((uint64_t)1 << deg) - 1;
    poly &= نقاب_2;
    mod = poly;
    *div = 1;
    deg--;
    جب (--n > deg) {
        بلند = (mod >> deg) & 1;
        *div = (*div << 1) | بلند;
        mod <<= 1;
        اگر (بلند)
            mod ^= poly;
    }
    uint64_t ret = mod & نقاب_2;
    اگر (bitreverse) {
        *div = الٹ(*div, deg) << 1;
        واپس الٹ(ret, deg) << 1;
    }
    واپس ret;
}

#اگر_ختم /* AVUTIL_CRC_INTERNAL_H */
