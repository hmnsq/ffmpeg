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

#اگر_تعریف_نشده AVUTIL_بررسی_چرخهای_داخلی_H
#تعریف_کن AVUTIL_بررسی_چرخهای_داخلی_H

#ضمن <stdint.h>
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/reverse.h"

ساكن uint64_t معکوس(uint64_t p, بیعلامت صحيح deg)
{
    uint64_t ret = 0;
    صحيح i;
    لكل (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_معکوس[p & 0xff]);
        p >>= 8;
    }
    صحيح rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_معکوس[p & 0xff] >> (8 - rem));
    أرجع ret;
}

av_استفادهنشده ساكن uint64_t xnmodp(بیعلامت n, uint64_t poly, بیعلامت deg,
                                 uint64_t *div, صحيح bitreverse)
{
    uint64_t mod, ماسک_2, بالا;

    إذا (n < deg) {
        *div = 0;
        أرجع poly;
    }
    ماسک_2 = ((uint64_t)1 << deg) - 1;
    poly &= ماسک_2;
    mod = poly;
    *div = 1;
    deg--;
    طالما (--n > deg) {
        بالا = (mod >> deg) & 1;
        *div = (*div << 1) | بالا;
        mod <<= 1;
        إذا (بالا)
            mod ^= poly;
    }
    uint64_t ret = mod & ماسک_2;
    إذا (bitreverse) {
        *div = معکوس(*div, deg) << 1;
        أرجع معکوس(ret, deg) << 1;
    }
    أرجع ret;
}

#پایان_اگر /* AVUTIL_CRC_INTERNAL_H */
