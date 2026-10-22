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

#అన్తర్భావ <inttypes.h>
#అన్తర్భావ <limits.h>
#అన్తర్భావ <math.h>
#అన్తర్భావ "lfg.h"
#అన్తర్భావ "crc.h"
#అన్తర్భావ "md5.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "intreadwrite.h"
#అన్తర్భావ "attributes.h"

av_cold శూన్య av_lfg_init(AVLFG *c, గుర్తులేని పూర్ణాంకం విత్తనం)
{
    uint8_t tmp[16] = { 0 };
    పూర్ణాంకం i;

    కొరకు (i = 8; i < 64; i += 4) {
        AV_WL32(tmp, విత్తనం);
        tmp[4] = i;
        av_md5_కూడిక(tmp, tmp, 16);
        c->state[i    ] = AV_RL32(tmp);
        c->state[i + 1] = AV_RL32(tmp + 4);
        c->state[i + 2] = AV_RL32(tmp + 8);
        c->state[i + 3] = AV_RL32(tmp + 12);
    }
    c->సూచీ = 0;
}

శూన్య av_bmg_get(AVLFG *lfg, ద్విగుణ బహిర్గతం[2])
{
    ద్విగుణ x1, x2, w;

    చేయి {
        x1 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        x2 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        w  = x1 * x1 + x2 * x2;
    } అయితే (w >= 1.0);

    w = వర్గమూలం((-2.0 * సంవర్గమానం(w)) / w);
    బహిర్గతం[0] = x1 * w;
    బహిర్గతం[1] = x2 * w;
}

పూర్ణాంకం av_lfg_init_from_దత్తాంశం(AVLFG *c, స్థిరరాశి uint8_t *దత్తాంశం, గుర్తులేని పూర్ణాంకం నిడివి) {
    గుర్తులేని పూర్ణాంకం beg, చివర, segm;
    స్థిరరాశి AVCRC *avcrc;
    uint32_t చక్రీయ_తనిఖీ = 1;

    /* avoid integer overflow in the loop below. */
    ఒకవేళ (నిడివి > (UINT_MAX / 128U)) తిరిగి AVERROR(EINVAL);

    c->సూచీ = 0;
    avcrc = av_చక్రీయ_తనిఖీ_get_పట్టిక(AV_చక్రీయ_తనిఖీ_32_IEEE); /* This can't fail. It's a well-defined table in crc.c */

    /* across 64 segments of the incoming data,
     * do a running crc of each segment and store the crc as the state for that slot.
     * this works even if the length of the segment is 0 bytes. */
    beg = 0;
    కొరకు (segm = 0;segm < 64;segm++) {
        చివర = (((segm + 1) * నిడివి) / 64);
        చక్రీయ_తనిఖీ = av_చక్రీయ_తనిఖీ(avcrc, చక్రీయ_తనిఖీ, దత్తాంశం + beg, చివర - beg);
        c->state[segm] = (గుర్తులేని పూర్ణాంకం)చక్రీయ_తనిఖీ;
        beg = చివర;
    }

    తిరిగి 0;
}
