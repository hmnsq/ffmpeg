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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/hash.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRC_BUF_ਮਾਪ 64
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DST_BUF_ਮਾਪ (AV_HASH_MAX_ਮਾਪ * 8)

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
   ਬਣਤਰ AVHashContext *ctx = ਨਿਰਾ;
   ਪੂਰਨ i, j, numhashes = 0;
   ਸਥਿਰ ਅਚਲ uint8_t src[SRC_BUF_ਮਾਪ] = { 0 };
   uint8_t dst[DST_BUF_ਮਾਪ];

   ਜਦੋਂ (av_hash_ਨਾਂ(numhashes))
       numhashes++;

   ਲਈ (i = 0; i < numhashes; i++) {
       ਜੇ (av_hash_alloc(&ctx, av_hash_ਨਾਂ(i)) < 0)
           ਵਾਪਸ 1;

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_ਮਾਪ);
       memset(dst, 0, DST_BUF_ਮਾਪ);
       av_hash_final_hex(ctx, dst, DST_BUF_ਮਾਪ);
       ਲਿਖੋ("%s hex: %s\n", av_hash_get_name(ctx), dst);

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_ਮਾਪ);
       av_hash_final_bin(ctx, dst, DST_BUF_ਮਾਪ);
       ਲਿਖੋ("%s bin:", av_hash_get_name(ctx));
       ਲਈ (j = 0; j < av_hash_get_ਮਾਪ(ctx); j++) {
           ਲਿਖੋ(" %#x", dst[j]);
       }
       ਲਿਖੋ("\n");

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_ਮਾਪ);
       av_hash_final_b64(ctx, dst, DST_BUF_ਮਾਪ);
       ਲਿਖੋ("%s b64: %s\n", av_hash_get_name(ctx), dst);
       av_hash_freep(&ctx);
   }
   ਵਾਪਸ 0;
}
