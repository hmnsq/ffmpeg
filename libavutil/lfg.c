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

#ضمن <inttypes.h>
#ضمن <limits.h>
#ضمن <math.h>
#ضمن "lfg.h"
#ضمن "crc.h"
#ضمن "md5.h"
#ضمن "error.h"
#ضمن "intreadwrite.h"
#ضمن "attributes.h"

av_cold فراغ av_lfg_init(AVLFG *c, بینښه صحيح تخم)
{
    uint8_t tmp[16] = { 0 };
    صحيح i;

    لكل (i = 8; i < 64; i += 4) {
        AV_WL32(tmp, تخم);
        tmp[4] = i;
        av_md5_مجموعه(tmp, tmp, 16);
        c->state[i    ] = AV_RL32(tmp);
        c->state[i + 1] = AV_RL32(tmp + 4);
        c->state[i + 2] = AV_RL32(tmp + 8);
        c->state[i + 3] = AV_RL32(tmp + 12);
    }
    c->شاخص = 0;
}

فراغ av_bmg_get(AVLFG *lfg, مزدوج بهر[2])
{
    مزدوج x1, x2, w;

    افعل {
        x1 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        x2 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        w  = x1 * x1 + x2 * x2;
    } طالما (w >= 1.0);

    w = جذر((-2.0 * لوګاریتم(w)) / w);
    بهر[0] = x1 * w;
    بهر[1] = x2 * w;
}

صحيح av_lfg_init_from_معلومات(AVLFG *c, ثابت uint8_t *معلومات, بینښه صحيح اوږدتیا) {
    بینښه صحيح beg, پای_ټکی, segm;
    ثابت AVCRC *avcrc;
    uint32_t دوراني_ازموینه = 1;

    /* avoid integer overflow in the loop below. */
    إذا (اوږدتیا > (UINT_MAX / 128U)) أرجع AVERROR(EINVAL);

    c->شاخص = 0;
    avcrc = av_دوراني_ازموینه_get_جدول(AV_دوراني_ازموینه_32_IEEE); /* This can't fail. It's a well-defined table in crc.c */

    /* across 64 segments of the incoming data,
     * do a running crc of each segment and store the crc as the state for that slot.
     * this works even if the length of the segment is 0 bytes. */
    beg = 0;
    لكل (segm = 0;segm < 64;segm++) {
        پای_ټکی = (((segm + 1) * اوږدتیا) / 64);
        دوراني_ازموینه = av_دوراني_ازموینه(avcrc, دوراني_ازموینه, معلومات + beg, پای_ټکی - beg);
        c->state[segm] = (بینښه صحيح)دوراني_ازموینه;
        beg = پای_ټکی;
    }

    أرجع 0;
}
