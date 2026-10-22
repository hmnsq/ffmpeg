/*
 * Lagged Fibonacci PRNG
 * Copyright (c) 2008 Michael Niedermayer
 *
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

#ಅನ್ತರ್ಭಾವ <inttypes.h>
#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <math.h>
#ಅನ್ತರ್ಭಾವ "lfg.h"
#ಅನ್ತರ್ಭಾವ "crc.h"
#ಅನ್ತರ್ಭಾವ "md5.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "attributes.h"

av_cold ಶೂನ್ಯ av_lfg_init(AVLFG *c, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬೀಜ)
{
    uint8_t tmp[16] = { 0 };
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 8; i < 64; i += 4) {
        AV_WL32(tmp, ಬೀಜ);
        tmp[4] = i;
        av_md5_ಮೊತ್ತ(tmp, tmp, 16);
        c->state[i    ] = AV_RL32(tmp);
        c->state[i + 1] = AV_RL32(tmp + 4);
        c->state[i + 2] = AV_RL32(tmp + 8);
        c->state[i + 3] = AV_RL32(tmp + 12);
    }
    c->ಸೂಚ್ಯಂಕ = 0;
}

ಶೂನ್ಯ av_bmg_get(AVLFG *lfg, ದ್ವಿಗುಣ ಹೊರಹೋಗು[2])
{
    ದ್ವಿಗುಣ x1, x2, w;

    ಮಾಡು {
        x1 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        x2 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        w  = x1 * x1 + x2 * x2;
    } ಆಗ (w >= 1.0);

    w = ವರ್ಗಮೂಲ((-2.0 * ಲಘುಗಣಕ(w)) / w);
    ಹೊರಹೋಗು[0] = x1 * w;
    ಹೊರಹೋಗು[1] = x2 * w;
}

ಪೂರ್ಣಾಂಕ av_lfg_init_from_ದತ್ತಾಂಶ(AVLFG *c, ಸ್ಥಿರಾಂಕ uint8_t *ದತ್ತಾಂಶ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಉದ್ದಳತೆ) {
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ beg, ಕೊನೆ, segm;
    ಸ್ಥಿರಾಂಕ AVCRC *avcrc;
    uint32_t ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ = 1;

    /* avoid integer overflow in the loop below. */
    ಆದರೆ (ಉದ್ದಳತೆ > (UINT_MAX / 128U)) ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    c->ಸೂಚ್ಯಂಕ = 0;
    avcrc = av_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_get_ಕೋಷ್ಟಕ(AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE); /* This can't fail. It's a well-defined table in crc.c */

    /* across 64 segments of the incoming data,
     * do a running crc of each segment and store the crc as the state for that slot.
     * this works even if the length of the segment is 0 bytes. */
    beg = 0;
    ಗಾಗಿ (segm = 0;segm < 64;segm++) {
        ಕೊನೆ = (((segm + 1) * ಉದ್ದಳತೆ) / 64);
        ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ = av_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ(avcrc, ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, ದತ್ತಾಂಶ + beg, ಕೊನೆ - beg);
        c->state[segm] = (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ)ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ;
        beg = ಕೊನೆ;
    }

    ಹಿಂತಿರುಗಿ 0;
}
