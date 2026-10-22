/*
 * Copyright (C) 2013 Reimar Döffinger <Reimar.Doeffinger@gmx.de>
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
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/intreadwrite.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/murmur3.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਪੂਰਨ i;
    uint8_t hash_ਨਤੀਜਾ[16] = {0};
    ਬਣਤਰ AVMurMur3 *ctx = av_murmur3_alloc();
#ਜੇ 1
    uint8_t ਵਿੱਚ_2[256] = {0};
    uint8_t *hashes = av_mallocz(256 * 16);
    ਲਈ (i = 0; i < 256; i++)
    {
        ਵਿੱਚ_2[i] = i;
        av_murmur3_init_seeded(ctx, 256 - i);
        // Note: this actually tests hashing 0 bytes
        av_murmur3_update(ctx, ਵਿੱਚ_2, i);
        av_murmur3_final(ctx, hashes + 16 * i);
    }
    av_murmur3_init_seeded(ctx, 0);
    av_murmur3_update(ctx, hashes, 256 * 16);
    av_murmur3_final(ctx, hash_ਨਤੀਜਾ);
    av_free(hashes);
    av_freep(&ctx);
    ਲਿਖੋ("result: 0x%"PRIx64" 0x%"PRIx64"\n", AV_RL64(hash_ਨਤੀਜਾ), AV_RL64(hash_ਨਤੀਜਾ + 8));
    // official reference value is 32 bit
    ਵਾਪਸ AV_RL32(hash_ਨਤੀਜਾ) != 0x6384ba69;
#ਨਹੀਂਤਾਂ
    uint8_t *ਵਿੱਚ_2 = av_mallocz(512*1024);
    av_murmur3_init(ctx);
    ਲਈ (i = 0; i < 40*1024; i++)
        av_murmur3_update(ctx, ਵਿੱਚ_2, 512*1024);
    av_murmur3_final(ctx, hash_ਨਤੀਜਾ);
    av_free(ਵਿੱਚ_2);
    ਵਾਪਸ hash_ਨਤੀਜਾ[0];
#ਜੇ_ਅੰਤ
}
