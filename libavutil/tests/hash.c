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

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/hash.h"

#నిర్వచించు SRC_BUF_కొలత 64
#నిర్వచించు DST_BUF_కొలత (AV_HASH_MAX_కొలత * 8)

పూర్ణాంకం ప్రధాన(శూన్య)
{
   నిర్మాణం AVHashContext *ctx = ఖాళీ;
   పూర్ణాంకం i, j, numhashes = 0;
   స్థిర స్థిరరాశి uint8_t src[SRC_BUF_కొలత] = { 0 };
   uint8_t dst[DST_BUF_కొలత];

   అయితే (av_hash_పేర్లు(numhashes))
       numhashes++;

   కొరకు (i = 0; i < numhashes; i++) {
       ఒకవేళ (av_hash_alloc(&ctx, av_hash_పేర్లు(i)) < 0)
           తిరిగి 1;

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_కొలత);
       memset(dst, 0, DST_BUF_కొలత);
       av_hash_final_hex(ctx, dst, DST_BUF_కొలత);
       రాయి("%s hex: %s\n", av_hash_get_name(ctx), dst);

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_కొలత);
       av_hash_final_bin(ctx, dst, DST_BUF_కొలత);
       రాయి("%s bin:", av_hash_get_name(ctx));
       కొరకు (j = 0; j < av_hash_get_కొలత(ctx); j++) {
           రాయి(" %#x", dst[j]);
       }
       రాయి("\n");

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_కొలత);
       av_hash_final_b64(ctx, dst, DST_BUF_కొలత);
       రాయి("%s b64: %s\n", av_hash_get_name(ctx), dst);
       av_hash_freep(&ctx);
   }
   తిరిగి 0;
}
