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

#که_نه_تعریف_شوی AVUTIL_دوراني_ازموینه_دننی_H
#تعریف_کړه AVUTIL_دوراني_ازموینه_دننی_H

#ضمن <stdint.h>
#ضمن "libavutil/attributes.h"
#ضمن "libavutil/reverse.h"

ساكن uint64_t سرچپه(uint64_t p, بینښه صحيح deg)
{
    uint64_t ret = 0;
    صحيح i;
    لكل (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_سرچپه[p & 0xff]);
        p >>= 8;
    }
    صحيح rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_سرچپه[p & 0xff] >> (8 - rem));
    أرجع ret;
}

av_ناکارول_شوی ساكن uint64_t xnmodp(بینښه n, uint64_t poly, بینښه deg,
                                 uint64_t *div, صحيح bitreverse)
{
    uint64_t mod, ماسک_2, لوړ;

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
        لوړ = (mod >> deg) & 1;
        *div = (*div << 1) | لوړ;
        mod <<= 1;
        إذا (لوړ)
            mod ^= poly;
    }
    uint64_t ret = mod & ماسک_2;
    إذا (bitreverse) {
        *div = سرچپه(*div, deg) << 1;
        أرجع سرچپه(ret, deg) << 1;
    }
    أرجع ret;
}

#د_که_پای /* AVUTIL_CRC_INTERNAL_H */
