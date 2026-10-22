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

#شامل <inttypes.h>
#شامل <limits.h>
#شامل <math.h>
#شامل "lfg.h"
#شامل "crc.h"
#شامل "md5.h"
#شامل "error.h"
#شامل "intreadwrite.h"
#شامل "attributes.h"

av_cold خالی av_lfg_init(AVLFG *c, غیرعلامتی صحیح بیج)
{
    uint8_t tmp[16] = { 0 };
    صحیح i;

    برائے (i = 8; i < 64; i += 4) {
        AV_WL32(tmp, بیج);
        tmp[4] = i;
        av_md5_مجموع(tmp, tmp, 16);
        c->state[i    ] = AV_RL32(tmp);
        c->state[i + 1] = AV_RL32(tmp + 4);
        c->state[i + 2] = AV_RL32(tmp + 8);
        c->state[i + 3] = AV_RL32(tmp + 12);
    }
    c->اشاریہ = 0;
}

خالی av_bmg_get(AVLFG *lfg, دوہرا برآمد[2])
{
    دوہرا x1, x2, w;

    کرو {
        x1 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        x2 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        w  = x1 * x1 + x2 * x2;
    } جب (w >= 1.0);

    w = جذر((-2.0 * لوگارتھم(w)) / w);
    برآمد[0] = x1 * w;
    برآمد[1] = x2 * w;
}

صحیح av_lfg_init_from_ڈیٹا(AVLFG *c, ثابت uint8_t *ڈیٹا, غیرعلامتی صحیح لمبائی) {
    غیرعلامتی صحیح beg, انتہا, segm;
    ثابت AVCRC *avcrc;
    uint32_t چکری_جانچ = 1;

    /* avoid integer overflow in the loop below. */
    اگر (لمبائی > (UINT_MAX / 128U)) واپس AVERROR(EINVAL);

    c->اشاریہ = 0;
    avcrc = av_چکری_جانچ_get_جدول(AV_چکری_جانچ_32_IEEE); /* This can't fail. It's a well-defined table in crc.c */

    /* across 64 segments of the incoming data,
     * do a running crc of each segment and store the crc as the state for that slot.
     * this works even if the length of the segment is 0 bytes. */
    beg = 0;
    برائے (segm = 0;segm < 64;segm++) {
        انتہا = (((segm + 1) * لمبائی) / 64);
        چکری_جانچ = av_چکری_جانچ(avcrc, چکری_جانچ, ڈیٹا + beg, انتہا - beg);
        c->state[segm] = (غیرعلامتی صحیح)چکری_جانچ;
        beg = انتہا;
    }

    واپس 0;
}
