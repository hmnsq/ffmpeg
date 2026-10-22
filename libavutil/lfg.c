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

#अन्तर्भाव <inttypes.h>
#अन्तर्भाव <limits.h>
#अन्तर्भाव <math.h>
#अन्तर्भाव "lfg.h"
#अन्तर्भाव "crc.h"
#अन्तर्भाव "md5.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "intreadwrite.h"
#अन्तर्भाव "attributes.h"

av_cold शून्य av_lfg_init(AVLFG *c, अचिह्नित पूर्णाङ्क बीजम्)
{
    uint8_t tmp[16] = { 0 };
    पूर्णाङ्क i;

    प्रति (i = 8; i < 64; i += 4) {
        AV_WL32(tmp, बीजम्);
        tmp[4] = i;
        av_md5_योग(tmp, tmp, 16);
        c->state[i    ] = AV_RL32(tmp);
        c->state[i + 1] = AV_RL32(tmp + 4);
        c->state[i + 2] = AV_RL32(tmp + 8);
        c->state[i + 3] = AV_RL32(tmp + 12);
    }
    c->सूचकांक = 0;
}

शून्य av_bmg_get(AVLFG *lfg, द्विगुण बहिर्गमनम्[2])
{
    द्विगुण x1, x2, w;

    कुरु {
        x1 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        x2 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        w  = x1 * x1 + x2 * x2;
    } यावत् (w >= 1.0);

    w = वर्गमूलम्((-2.0 * लघुगणकः(w)) / w);
    बहिर्गमनम्[0] = x1 * w;
    बहिर्गमनम्[1] = x2 * w;
}

पूर्णाङ्क av_lfg_init_from_दत्त(AVLFG *c, ध्रुव uint8_t *दत्त, अचिह्नित पूर्णाङ्क दीर्घता) {
    अचिह्नित पूर्णाङ्क beg, अन्तः_2, segm;
    ध्रुव AVCRC *avcrc;
    uint32_t crc = 1;

    /* avoid integer overflow in the loop below. */
    यदि (दीर्घता > (UINT_MAX / 128U)) प्रत्यागम AVERROR(EINVAL);

    c->सूचकांक = 0;
    avcrc = av_crc_get_सारणी(AV_CRC_32_IEEE); /* This can't fail. It's a well-defined table in crc.c */

    /* across 64 segments of the incoming data,
     * do a running crc of each segment and store the crc as the state for that slot.
     * this works even if the length of the segment is 0 bytes. */
    beg = 0;
    प्रति (segm = 0;segm < 64;segm++) {
        अन्तः_2 = (((segm + 1) * दीर्घता) / 64);
        crc = av_crc(avcrc, crc, दत्त + beg, अन्तः_2 - beg);
        c->state[segm] = (अचिह्नित पूर्णाङ्क)crc;
        beg = अन्तः_2;
    }

    प्रत्यागम 0;
}
