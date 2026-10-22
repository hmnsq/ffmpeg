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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_ಆಂತರಿಕ_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/reverse.h"

ಸ್ಥಿರ uint64_t ಹಿಮ್ಮುಖ(uint64_t p, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ deg)
{
    uint64_t ret = 0;
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < (deg / 8); i += 1) {
        ret = (ret << 8) | (ff_ಹಿಮ್ಮುಖ[p & 0xff]);
        p >>= 8;
    }
    ಪೂರ್ಣಾಂಕ rem = (deg + 1) - 8 * i;
    ret = (ret << rem) | (ff_ಹಿಮ್ಮುಖ[p & 0xff] >> (8 - rem));
    ಹಿಂತಿರುಗಿ ret;
}

av_ಬಳಸದ ಸ್ಥಿರ uint64_t xnmodp(ಚಿಹ್ನೆರಹಿತ n, uint64_t poly, ಚಿಹ್ನೆರಹಿತ deg,
                                 uint64_t *div, ಪೂರ್ಣಾಂಕ bitreverse)
{
    uint64_t mod, ಮುಖವಾಡ_2, ಮೇಲಿನ;

    ಆದರೆ (n < deg) {
        *div = 0;
        ಹಿಂತಿರುಗಿ poly;
    }
    ಮುಖವಾಡ_2 = ((uint64_t)1 << deg) - 1;
    poly &= ಮುಖವಾಡ_2;
    mod = poly;
    *div = 1;
    deg--;
    ಆಗ (--n > deg) {
        ಮೇಲಿನ = (mod >> deg) & 1;
        *div = (*div << 1) | ಮೇಲಿನ;
        mod <<= 1;
        ಆದರೆ (ಮೇಲಿನ)
            mod ^= poly;
    }
    uint64_t ret = mod & ಮುಖವಾಡ_2;
    ಆದರೆ (bitreverse) {
        *div = ಹಿಮ್ಮುಖ(*div, deg) << 1;
        ಹಿಂತಿರುಗಿ ಹಿಮ್ಮುಖ(ret, deg) << 1;
    }
    ಹಿಂತಿರುಗಿ ret;
}

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_CRC_INTERNAL_H */
