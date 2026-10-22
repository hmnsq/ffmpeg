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

#شامل <stdio.h>
#شامل <string.h>

#شامل "libavutil/hash.h"

#تعریف_کرو SRC_BUF_سائز 64
#تعریف_کرو DST_BUF_سائز (AV_HASH_MAX_سائز * 8)

صحیح مین(خالی)
{
   ساخت AVHashContext *ctx = تہی;
   صحیح i, j, numhashes = 0;
   ساکن ثابت uint8_t src[SRC_BUF_سائز] = { 0 };
   uint8_t dst[DST_BUF_سائز];

   جب (av_hash_نام(numhashes))
       numhashes++;

   برائے (i = 0; i < numhashes; i++) {
       اگر (av_hash_alloc(&ctx, av_hash_نام(i)) < 0)
           واپس 1;

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_سائز);
       memset(dst, 0, DST_BUF_سائز);
       av_hash_final_hex(ctx, dst, DST_BUF_سائز);
       لکھو("%s hex: %s\n", av_hash_get_name(ctx), dst);

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_سائز);
       av_hash_final_bin(ctx, dst, DST_BUF_سائز);
       لکھو("%s bin:", av_hash_get_name(ctx));
       برائے (j = 0; j < av_hash_get_سائز(ctx); j++) {
           لکھو(" %#x", dst[j]);
       }
       لکھو("\n");

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_سائز);
       av_hash_final_b64(ctx, dst, DST_BUF_سائز);
       لکھو("%s b64: %s\n", av_hash_get_name(ctx), dst);
       av_hash_freep(&ctx);
   }
   واپس 0;
}
