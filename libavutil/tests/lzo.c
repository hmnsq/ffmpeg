/*
 * Copyright (c) 2006 Reimar Doeffinger
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
#समावेश <stdlib.h>
#समावेश <string.h>
#समावेश <lzo/lzo1x.h>

#समावेश "libavutil/log.h"
#समावेश "libavutil/lzo.h"
#समावेश "libavutil/mem.h"

#घोषणा MAXSZ (10*1024*1024)

/* Define one of these to 1 if you wish to benchmark liblzo
 * instead of our native implementation. */
#घोषणा BENCHMARK_LIBLZO_SAFE   0
#घोषणा BENCHMARK_LIBLZO_UNSAFE 0

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[]) {
    खाता *in = ख_खोलो(argv[1], "rb");
    पूर्णांक comp_level = argc > 2 ? म_से_प(argv[2]) : 0;
    uint8_t *orig = av_malloc(MAXSZ + 16);
    uint8_t *comp = av_malloc(2*MAXSZ + 16);
    uint8_t *decomp = av_malloc(MAXSZ + 16);
    माप_प्रकार s = ख_पढ़ो(orig, 1, MAXSZ, in);
    lzo_uint clen = 0;
    दीर्घ tmp[LZO1X_MEM_COMPRESS];
    पूर्णांक inlen, outlen;
    पूर्णांक i;
    av_log_set_level(AV_LOG_DEBUG);
    अगर (comp_level == 0) {
        lzo1x_1_compress(orig, s, comp, &clen, tmp);
    } अन्यथा अगर (comp_level == 11) {
        lzo1x_1_11_compress(orig, s, comp, &clen, tmp);
    } अन्यथा अगर (comp_level == 12) {
        lzo1x_1_12_compress(orig, s, comp, &clen, tmp);
    } अन्यथा अगर (comp_level == 15) {
        lzo1x_1_15_compress(orig, s, comp, &clen, tmp);
    } अन्यथा
        lzo1x_999_compress(orig, s, comp, &clen, tmp);
    क्रम (i = 0; i < 300; i++) {
        inlen = clen; outlen = MAXSZ;
#अगर BENCHMARK_LIBLZO_SAFE
        अगर (lzo1x_decompress_safe(comp, inlen, decomp, &outlen, शून्य))
#या_अगर BENCHMARK_LIBLZO_UNSAFE
        अगर (lzo1x_decompress(comp, inlen, decomp, &outlen, शून्य))
#अन्यथा
        अगर (av_lzo1x_decode(decomp, &outlen, comp, &inlen))
#पूर्ण_अगर
            av_log(शून्य, AV_LOG_ERROR, "decompression error\n");
    }
    अगर (स_भेद(orig, decomp, s))
        av_log(शून्य, AV_LOG_ERROR, "decompression incorrect\n");
    अन्यथा
        av_log(शून्य, AV_LOG_ERROR, "decompression OK\n");
    ख_बंद(in);
    av_free(orig);
    av_free(comp);
    av_free(decomp);
    वापस 0;
}
