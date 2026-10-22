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

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव <lzo/lzo1x.h>

#अन्तर्भाव "libavutil/log.h"
#अन्तर्भाव "libavutil/lzo.h"
#अन्तर्भाव "libavutil/mem.h"

#परिभाषय MAXSZ (10*1024*1024)

/* Define one of these to 1 if you wish to benchmark liblzo
 * instead of our native implementation. */
#परिभाषय BENCHMARK_LIBLZO_SAFE   0
#परिभाषय BENCHMARK_LIBLZO_UNSAFE 0

पूर्णाङ्क मुख्यम्(पूर्णाङ्क argc, वर्ण *argv[]) {
    FILE *अन्तर् = fopen(argv[1], "rb");
    पूर्णाङ्क comp_level = argc > 2 ? atoi(argv[2]) : 0;
    uint8_t *orig = av_malloc(MAXSZ + 16);
    uint8_t *comp = av_malloc(2*MAXSZ + 16);
    uint8_t *decomp = av_malloc(MAXSZ + 16);
    size_t s = fread(orig, 1, MAXSZ, अन्तर्);
    lzo_uint clen = 0;
    दीर्घ tmp[LZO1X_MEM_COMPRESS];
    पूर्णाङ्क inlen, outlen;
    पूर्णाङ्क i;
    av_log_समुच्चयः_level(AV_LOG_DEBUG);
    यदि (comp_level == 0) {
        lzo1x_1_compress(orig, s, comp, &clen, tmp);
    } अन्यथा यदि (comp_level == 11) {
        lzo1x_1_11_compress(orig, s, comp, &clen, tmp);
    } अन्यथा यदि (comp_level == 12) {
        lzo1x_1_12_compress(orig, s, comp, &clen, tmp);
    } अन्यथा यदि (comp_level == 15) {
        lzo1x_1_15_compress(orig, s, comp, &clen, tmp);
    } अन्यथा
        lzo1x_999_compress(orig, s, comp, &clen, tmp);
    प्रति (i = 0; i < 300; i++) {
        inlen = clen; outlen = MAXSZ;
#यदि BENCHMARK_LIBLZO_SAFE
        यदि (lzo1x_decompress_safe(comp, inlen, decomp, &outlen, रिक्त))
#नोचेद्यदि BENCHMARK_LIBLZO_UNSAFE
        यदि (lzo1x_decompress(comp, inlen, decomp, &outlen, रिक्त))
#अन्यथा
        यदि (av_lzo1x_decode(decomp, &outlen, comp, &inlen))
#यदि_अन्तः
            av_log(रिक्त, AV_LOG_ERROR, "decompression error\n");
    }
    यदि (memcmp(orig, decomp, s))
        av_log(रिक्त, AV_LOG_ERROR, "decompression incorrect\n");
    अन्यथा
        av_log(रिक्त, AV_LOG_ERROR, "decompression OK\n");
    fclose(अन्तर्);
    av_free(orig);
    av_free(comp);
    av_free(decomp);
    प्रत्यागम 0;
}
