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

#నిర్వచితం_కాకపోతే AVUTIL_చక్రీయ_తనిఖీ_అంతర్గత_H
#నిర్వచించు AVUTIL_చక్రీయ_తనిఖీ_అంతర్గత_H

#అన్తర్భావ <stdint.h>
#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/reverse.h"

స్థిర uint64_t తిరగేయి(uint64_t p, గుర్తులేని పూర్ణాంకం deg)
{
    uint64_t ret = 0;
    పూర్ణాంకం i;
    కొరకు (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_తిరగేయి[p & 0xff]);
        p >>= 8;
    }
    పూర్ణాంకం rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_తిరగేయి[p & 0xff] >> (8 - rem));
    తిరిగి ret;
}

av_వాడని స్థిర uint64_t xnmodp(గుర్తులేని n, uint64_t poly, గుర్తులేని deg,
                                 uint64_t *div, పూర్ణాంకం bitreverse)
{
    uint64_t mod, ముసుగు_2, ఎగువ;

    ఒకవేళ (n < deg) {
        *div = 0;
        తిరిగి poly;
    }
    ముసుగు_2 = ((uint64_t)1 << deg) - 1;
    poly &= ముసుగు_2;
    mod = poly;
    *div = 1;
    deg--;
    అయితే (--n > deg) {
        ఎగువ = (mod >> deg) & 1;
        *div = (*div << 1) | ఎగువ;
        mod <<= 1;
        ఒకవేళ (ఎగువ)
            mod ^= poly;
    }
    uint64_t ret = mod & ముసుగు_2;
    ఒకవేళ (bitreverse) {
        *div = తిరగేయి(*div, deg) << 1;
        తిరిగి తిరగేయి(ret, deg) << 1;
    }
    తిరిగి ret;
}

#అయితే_ముగింపు /* AVUTIL_CRC_INTERNAL_H */
