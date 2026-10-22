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

#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "libavutil/hash.h"

#تعریف_کن SRC_BUF_اندازه 64
#تعریف_کن DST_BUF_اندازه (AV_HASH_MAX_اندازه * 8)

صحيح اصلی(فراغ)
{
   بنية AVHashContext *ctx = عدم;
   صحيح i, j, numhashes = 0;
   ساكن ثابت uint8_t src[SRC_BUF_اندازه] = { 0 };
   uint8_t dst[DST_BUF_اندازه];

   طالما (av_hash_نامها(numhashes))
       numhashes++;

   لكل (i = 0; i < numhashes; i++) {
       إذا (av_hash_alloc(&ctx, av_hash_نامها(i)) < 0)
           أرجع 1;

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_اندازه);
       memset(dst, 0, DST_BUF_اندازه);
       av_hash_final_hex(ctx, dst, DST_BUF_اندازه);
       چاپ_کن("%s hex: %s\n", av_hash_get_name(ctx), dst);

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_اندازه);
       av_hash_final_bin(ctx, dst, DST_BUF_اندازه);
       چاپ_کن("%s bin:", av_hash_get_name(ctx));
       لكل (j = 0; j < av_hash_get_اندازه(ctx); j++) {
           چاپ_کن(" %#x", dst[j]);
       }
       چاپ_کن("\n");

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_اندازه);
       av_hash_final_b64(ctx, dst, DST_BUF_اندازه);
       چاپ_کن("%s b64: %s\n", av_hash_get_name(ctx), dst);
       av_hash_freep(&ctx);
   }
   أرجع 0;
}
