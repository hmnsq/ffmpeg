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

#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ <lzo/lzo1x.h>

#અન્તર્ભાવ "libavutil/log.h"
#અન્તર્ભાવ "libavutil/lzo.h"
#અન્તર્ભાવ "libavutil/mem.h"

#define MAXSZ (10*1024*1024)

/* Define one of these to 1 if you wish to benchmark liblzo
 * instead of our native implementation. */
#define BENCHMARK_LIBLZO_SAFE   0
#define BENCHMARK_LIBLZO_UNSAFE 0

પૂર્ણાંક મુખ્ય(પૂર્ણાંક argc, અક્ષર *argv[]) {
    FILE *in = fopen(argv[1], "rb");
    પૂર્ણાંક comp_level = argc > 2 ? atoi(argv[2]) : 0;
    uint8_t *orig = av_malloc(MAXSZ + 16);
    uint8_t *comp = av_malloc(2*MAXSZ + 16);
    uint8_t *decomp = av_malloc(MAXSZ + 16);
    size_t s = fread(orig, 1, MAXSZ, in);
    lzo_uint clen = 0;
    long tmp[LZO1X_MEM_COMPRESS];
    પૂર્ણાંક inlen, outlen;
    પૂર્ણાંક i;
    av_log_set_level(AV_LOG_DEBUG);
    જો (comp_level == 0) {
        lzo1x_1_compress(orig, s, comp, &clen, tmp);
    } નહીંતર જો (comp_level == 11) {
        lzo1x_1_11_compress(orig, s, comp, &clen, tmp);
    } નહીંતર જો (comp_level == 12) {
        lzo1x_1_12_compress(orig, s, comp, &clen, tmp);
    } નહીંતર જો (comp_level == 15) {
        lzo1x_1_15_compress(orig, s, comp, &clen, tmp);
    } નહીંતર
        lzo1x_999_compress(orig, s, comp, &clen, tmp);
    માટે (i = 0; i < 300; i++) {
        inlen = clen; outlen = MAXSZ;
#જો BENCHMARK_LIBLZO_SAFE
        જો (lzo1x_decompress_safe(comp, inlen, decomp, &outlen, ખાલી))
#અથવાજો BENCHMARK_LIBLZO_UNSAFE
        જો (lzo1x_decompress(comp, inlen, decomp, &outlen, ખાલી))
#નહીંતર
        જો (av_lzo1x_decode(decomp, &outlen, comp, &inlen))
#endif
            av_log(ખાલી, AV_LOG_ERROR, "decompression error\n");
    }
    જો (memcmp(orig, decomp, s))
        av_log(ખાલી, AV_LOG_ERROR, "decompression incorrect\n");
    નહીંતર
        av_log(ખાલી, AV_LOG_ERROR, "decompression OK\n");
    fclose(in);
    av_free(orig);
    av_free(comp);
    av_free(decomp);
    પાછા 0;
}
