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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lzo/lzo1x.h>

#include "libavutil/log.h"
#include "libavutil/lzo.h"
#include "libavutil/mem.h"

#define MAXSZ (10*1024*1024)

/* Define one of these to 1 if you wish to benchmark liblzo
 * instead of our native implementation. */
#define BENCHMARK_LIBLZO_SAFE   0
#define BENCHMARK_LIBLZO_UNSAFE 0

цео main(цео argc, char *argv[]) {
    FILE *in = fopen(argv[1], "rb");
    цео comp_level = argc > 2 ? atoi(argv[2]) : 0;
    uint8_t *orig = av_malloc(MAXSZ + 16);
    uint8_t *comp = av_malloc(2*MAXSZ + 16);
    uint8_t *decomp = av_malloc(MAXSZ + 16);
    size_t s = fread(orig, 1, MAXSZ, in);
    lzo_uint clen = 0;
    long tmp[LZO1X_MEM_COMPRESS];
    цео inlen, outlen;
    цео i;
    av_log_set_level(AV_LOG_DEBUG);
    ако (comp_level == 0) {
        lzo1x_1_compress(orig, s, comp, &clen, tmp);
    } инако ако (comp_level == 11) {
        lzo1x_1_11_compress(orig, s, comp, &clen, tmp);
    } инако ако (comp_level == 12) {
        lzo1x_1_12_compress(orig, s, comp, &clen, tmp);
    } инако ако (comp_level == 15) {
        lzo1x_1_15_compress(orig, s, comp, &clen, tmp);
    } инако
        lzo1x_999_compress(orig, s, comp, &clen, tmp);
    за (i = 0; i < 300; i++) {
        inlen = clen; outlen = MAXSZ;
#ако BENCHMARK_LIBLZO_SAFE
        ако (lzo1x_decompress_safe(comp, inlen, decomp, &outlen, NULL))
#elif BENCHMARK_LIBLZO_UNSAFE
        ако (lzo1x_decompress(comp, inlen, decomp, &outlen, NULL))
#инако
        ако (av_lzo1x_decode(decomp, &outlen, comp, &inlen))
#endif
            av_log(NULL, AV_LOG_ERROR, "decompression error\n");
    }
    ако (memcmp(orig, decomp, s))
        av_log(NULL, AV_LOG_ERROR, "decompression incorrect\n");
    инако
        av_log(NULL, AV_LOG_ERROR, "decompression OK\n");
    fclose(in);
    av_free(orig);
    av_free(comp);
    av_free(decomp);
    врати 0;
}
