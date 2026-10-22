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

av_cold فراغ av_lfg_init(AVLFG *c, بنانشانی صحيح بیج)
{
    uint8_t tmp[16] = { 0 };
    صحيح i;

    لكل (i = 8; i < 64; i += 4) {
        AV_WL32(tmp, بیج);
        tmp[4] = i;
        av_md5_جوڑ(tmp, tmp, 16);
        c->state[i    ] = AV_RL32(tmp);
        c->state[i + 1] = AV_RL32(tmp + 4);
        c->state[i + 2] = AV_RL32(tmp + 8);
        c->state[i + 3] = AV_RL32(tmp + 12);
    }
    c->اشاریہ = 0;
}

فراغ av_bmg_get(AVLFG *lfg, مزدوج باہرلا[2])
{
    مزدوج x1, x2, w;

    افعل {
        x1 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        x2 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        w  = x1 * x1 + x2 * x2;
    } طالما (w >= 1.0);

    w = جذر((-2.0 * لوگارتھم(w)) / w);
    باہرلا[0] = x1 * w;
    باہرلا[1] = x2 * w;
}

صحيح av_lfg_init_from_انکڑے(AVLFG *c, ثابت uint8_t *انکڑے, بنانشانی صحيح لمائی) {
    بنانشانی صحيح beg, سرا, segm;
    ثابت AVCRC *avcrc;
    uint32_t چکری_جانچ = 1;

    /* avoid integer overflow in the loop below. */
    إذا (لمائی > (UINT_MAX / 128U)) أرجع AVERROR(EINVAL);

    c->اشاریہ = 0;
    avcrc = av_چکری_جانچ_get_جدول(AV_چکری_جانچ_32_IEEE); /* This can't fail. It's a well-defined table in crc.c */

    /* across 64 segments of the incoming data,
     * do a running crc of each segment and store the crc as the state for that slot.
     * this works even if the length of the segment is 0 bytes. */
    beg = 0;
    لكل (segm = 0;segm < 64;segm++) {
        سرا = (((segm + 1) * لمائی) / 64);
        چکری_جانچ = av_چکری_جانچ(avcrc, چکری_جانچ, انکڑے + beg, سرا - beg);
        c->state[segm] = (بنانشانی صحيح)چکری_جانچ;
        beg = سرا;
    }

    أرجع 0;
}
