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

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/hash.h"

#ವ್ಯಾಖ್ಯಾನಿಸು SRC_BUF_ಗಾತ್ರ 64
#ವ್ಯಾಖ್ಯಾನಿಸು DST_BUF_ಗಾತ್ರ (AV_HASH_MAX_ಗಾತ್ರ * 8)

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
   ರಚನೆ AVHashContext *ctx = ಖಾಲಿ;
   ಪೂರ್ಣಾಂಕ i, j, numhashes = 0;
   ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t src[SRC_BUF_ಗಾತ್ರ] = { 0 };
   uint8_t dst[DST_BUF_ಗಾತ್ರ];

   ಆಗ (av_hash_ಹೆಸರುಗಳು(numhashes))
       numhashes++;

   ಗಾಗಿ (i = 0; i < numhashes; i++) {
       ಆದರೆ (av_hash_alloc(&ctx, av_hash_ಹೆಸರುಗಳು(i)) < 0)
           ಹಿಂತಿರುಗಿ 1;

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_ಗಾತ್ರ);
       memset(dst, 0, DST_BUF_ಗಾತ್ರ);
       av_hash_final_hex(ctx, dst, DST_BUF_ಗಾತ್ರ);
       ಬರೆ("%s hex: %s\n", av_hash_get_name(ctx), dst);

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_ಗಾತ್ರ);
       av_hash_final_bin(ctx, dst, DST_BUF_ಗಾತ್ರ);
       ಬರೆ("%s bin:", av_hash_get_name(ctx));
       ಗಾಗಿ (j = 0; j < av_hash_get_ಗಾತ್ರ(ctx); j++) {
           ಬರೆ(" %#x", dst[j]);
       }
       ಬರೆ("\n");

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_ಗಾತ್ರ);
       av_hash_final_b64(ctx, dst, DST_BUF_ಗಾತ್ರ);
       ಬರೆ("%s b64: %s\n", av_hash_get_name(ctx), dst);
       av_hash_freep(&ctx);
   }
   ಹಿಂತಿರುಗಿ 0;
}
