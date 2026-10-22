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

#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/hash.h"

#घोषणा SRC_BUF_आकार 64
#घोषणा DST_BUF_आकार (AV_HASH_MAX_आकार * 8)

पूर्णांक मुख्य(व्योम)
{
   काष्ठा AVHashContext *ctx = शून्य;
   पूर्णांक i, j, numhashes = 0;
   अटल स्थिर uint8_t src[SRC_BUF_आकार] = { 0 };
   uint8_t dst[DST_BUF_आकार];

   जबतक (av_hash_names(numhashes))
       numhashes++;

   क्रम (i = 0; i < numhashes; i++) {
       अगर (av_hash_alloc(&ctx, av_hash_names(i)) < 0)
           वापस 1;

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_आकार);
       स_रखो(dst, 0, DST_BUF_आकार);
       av_hash_final_hex(ctx, dst, DST_BUF_आकार);
       म_लिखो("%s hex: %s\n", av_hash_get_name(ctx), dst);

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_आकार);
       av_hash_final_bin(ctx, dst, DST_BUF_आकार);
       म_लिखो("%s bin:", av_hash_get_name(ctx));
       क्रम (j = 0; j < av_hash_get_आकार(ctx); j++) {
           म_लिखो(" %#x", dst[j]);
       }
       म_लिखो("\n");

       av_hash_init(ctx);
       av_hash_update(ctx, src, SRC_BUF_आकार);
       av_hash_final_b64(ctx, dst, DST_BUF_आकार);
       म_लिखो("%s b64: %s\n", av_hash_get_name(ctx), dst);
       av_hash_freep(&ctx);
   }
   वापस 0;
}
