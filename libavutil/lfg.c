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

#ਅਨ੍ਤਰ੍ਭਾਵ <inttypes.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "lfg.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "crc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "md5.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"

av_cold ਖਾਲੀ av_lfg_init(AVLFG *c, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬੀਜ)
{
    uint8_t tmp[16] = { 0 };
    ਪੂਰਨ i;

    ਲਈ (i = 8; i < 64; i += 4) {
        AV_WL32(tmp, ਬੀਜ);
        tmp[4] = i;
        av_md5_ਜੋੜ(tmp, tmp, 16);
        c->state[i    ] = AV_RL32(tmp);
        c->state[i + 1] = AV_RL32(tmp + 4);
        c->state[i + 2] = AV_RL32(tmp + 8);
        c->state[i + 3] = AV_RL32(tmp + 12);
    }
    c->ਸੂਚਕਾਂਕ = 0;
}

ਖਾਲੀ av_bmg_get(AVLFG *lfg, ਦੁੱਗਣਾ ਬਾਹਰਲਾ[2])
{
    ਦੁੱਗਣਾ x1, x2, w;

    ਕਰੋ {
        x1 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        x2 = 2.0 / UINT_MAX * av_lfg_get(lfg) - 1.0;
        w  = x1 * x1 + x2 * x2;
    } ਜਦੋਂ (w >= 1.0);

    w = ਵਰਗਮੂਲ((-2.0 * ਲਘੂਗਣਕ(w)) / w);
    ਬਾਹਰਲਾ[0] = x1 * w;
    ਬਾਹਰਲਾ[1] = x2 * w;
}

ਪੂਰਨ av_lfg_init_from_ਅੰਕੜੇ(AVLFG *c, ਅਚਲ uint8_t *ਅੰਕੜੇ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਲੰਮਾਈ) {
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ beg, ਸਿਰਾ, segm;
    ਅਚਲ AVCRC *avcrc;
    uint32_t ਚੱਕਰੀ_ਜਾਂਚ = 1;

    /* avoid integer overflow in the loop below. */
    ਜੇ (ਲੰਮਾਈ > (UINT_MAX / 128U)) ਵਾਪਸ AVERROR(EINVAL);

    c->ਸੂਚਕਾਂਕ = 0;
    avcrc = av_ਚੱਕਰੀ_ਜਾਂਚ_get_ਸਾਰਣੀ(AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE); /* This can't fail. It's a well-defined table in crc.c */

    /* across 64 segments of the incoming data,
     * do a running crc of each segment and store the crc as the state for that slot.
     * this works even if the length of the segment is 0 bytes. */
    beg = 0;
    ਲਈ (segm = 0;segm < 64;segm++) {
        ਸਿਰਾ = (((segm + 1) * ਲੰਮਾਈ) / 64);
        ਚੱਕਰੀ_ਜਾਂਚ = av_ਚੱਕਰੀ_ਜਾਂਚ(avcrc, ਚੱਕਰੀ_ਜਾਂਚ, ਅੰਕੜੇ + beg, ਸਿਰਾ - beg);
        c->state[segm] = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ)ਚੱਕਰੀ_ਜਾਂਚ;
        beg = ਸਿਰਾ;
    }

    ਵਾਪਸ 0;
}
