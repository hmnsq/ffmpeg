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

#यदि_अपरिभाषितम् AVUTIL_CRC_आन्तरिकम्_H
#परिभाषय AVUTIL_CRC_आन्तरिकम्_H

#अन्तर्भाव <stdint.h>
#अन्तर्भाव "libavutil/attributes.h"
#अन्तर्भाव "libavutil/reverse.h"

स्थिर uint64_t reverse(uint64_t p, अचिह्नित पूर्णाङ्क deg)
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

av_अप्रयुक्तम् स्थिर uint64_t xnmodp(अचिह्नित n, uint64_t poly, अचिह्नित deg,
                                 uint64_t *भाजय, पूर्णाङ्क bitreverse)
{
    uint64_t mod, आवरणम्_2, उच्चः;

    यदि (n < deg) {
        *भाजय = 0;
        प्रत्यागम poly;
    }
    आवरणम्_2 = ((uint64_t)1 << deg) - 1;
    poly &= आवरणम्_2;
    mod = poly;
    *भाजय = 1;
    deg--;
    यावत् (--n > deg) {
        उच्चः = (mod >> deg) & 1;
        *भाजय = (*भाजय << 1) | उच्चः;
        mod <<= 1;
        यदि (उच्चः)
            mod ^= poly;
    }
    uint64_t ret = mod & आवरणम्_2;
    यदि (bitreverse) {
        *भाजय = reverse(*भाजय, deg) << 1;
        प्रत्यागम reverse(ret, deg) << 1;
    }
    प्रत्यागम ret;
}

#यदि_अन्तः /* AVUTIL_CRC_INTERNAL_H */
