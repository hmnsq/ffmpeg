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

#جے_بنا_تعریف AVUTIL_چکری_جانچ_اندرونی_H
#تعریف_کرو AVUTIL_چکری_جانچ_اندرونی_H

#ضمن <stdint.h>
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/reverse.h"

ساكن uint64_t الٹ(uint64_t p, بنانشانی صحيح deg)
{
    uint64_t ret = 0;
    صحيح i;
    لكل (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_الٹ[p & 0xff]);
        p >>= 8;
    }
    صحيح rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_الٹ[p & 0xff] >> (8 - rem));
    أرجع ret;
}

av_بن_ورتیا ساكن uint64_t xnmodp(بنانشانی n, uint64_t poly, بنانشانی deg,
                                 uint64_t *div, صحيح bitreverse)
{
    uint64_t mod, نقاب_2, بلند;

    إذا (n < deg) {
        *div = 0;
        أرجع poly;
    }
    نقاب_2 = ((uint64_t)1 << deg) - 1;
    poly &= نقاب_2;
    mod = poly;
    *div = 1;
    deg--;
    طالما (--n > deg) {
        بلند = (mod >> deg) & 1;
        *div = (*div << 1) | بلند;
        mod <<= 1;
        إذا (بلند)
            mod ^= poly;
    }
    uint64_t ret = mod & نقاب_2;
    إذا (bitreverse) {
        *div = الٹ(*div, deg) << 1;
        أرجع الٹ(ret, deg) << 1;
    }
    أرجع ret;
}

#جے_انت /* AVUTIL_CRC_INTERNAL_H */
