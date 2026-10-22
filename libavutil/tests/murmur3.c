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

#ಅನ್ತರ್ಭಾವ <inttypes.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"
#ಅನ್ತರ್ಭಾವ "libavutil/murmur3.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ i;
    uint8_t hash_ಫಲಿತಾಂಶ[16] = {0};
    ರಚನೆ AVMurMur3 *ctx = av_murmur3_alloc();
#ಆದರೆ 1
    uint8_t ಒಳ[256] = {0};
    uint8_t *hashes = av_mallocz(256 * 16);
    ಗಾಗಿ (i = 0; i < 256; i++)
    {
        ಒಳ[i] = i;
        av_murmur3_init_seeded(ctx, 256 - i);
        // Note: this actually tests hashing 0 bytes
        av_murmur3_update(ctx, ಒಳ, i);
        av_murmur3_final(ctx, hashes + 16 * i);
    }
    av_murmur3_init_seeded(ctx, 0);
    av_murmur3_update(ctx, hashes, 256 * 16);
    av_murmur3_final(ctx, hash_ಫಲಿತಾಂಶ);
    av_free(hashes);
    av_freep(&ctx);
    ಬರೆ("result: 0x%"PRIx64" 0x%"PRIx64"\n", AV_RL64(hash_ಫಲಿತಾಂಶ), AV_RL64(hash_ಫಲಿತಾಂಶ + 8));
    // official reference value is 32 bit
    ಹಿಂತಿರುಗಿ AV_RL32(hash_ಫಲಿತಾಂಶ) != 0x6384ba69;
#ಇಲ್ಲದಿದ್ದರೆ
    uint8_t *ಒಳ = av_mallocz(512*1024);
    av_murmur3_init(ctx);
    ಗಾಗಿ (i = 0; i < 40*1024; i++)
        av_murmur3_update(ctx, ಒಳ, 512*1024);
    av_murmur3_final(ctx, hash_ಫಲಿತಾಂಶ);
    av_free(ಒಳ);
    ಹಿಂತಿರುಗಿ hash_ಫಲಿತಾಂಶ[0];
#ಆದರೆ_ಅಂತ್ಯ
}
