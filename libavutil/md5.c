/*
 * Copyright (C) 2006 Michael Niedermayer (michaelni@gmx.at)
 * Copyright (C) 2003-2005 by Christopher R. Hertel (crh@ubiqx.mn.org)
 *
 * References:
 *  IETF RFC 1321: The MD5 Message-Digest Algorithm
 *       Ron Rivest. IETF, April, 1992
 *
 * based on http://ubiqx.org/libcifs/source/Auth/MD5.c
 *          from Christopher R. Hertel (crh@ubiqx.mn.org)
 * Simplified, cleaned and IMO redundant comments removed by Michael.
 *
 * If you use gcc, then version 4.1 or later and -fomit-frame-pointer is
 * strongly recommended.
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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "bswap.h"
#అన్తర్భావ "intreadwrite.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "md5.h"

రకనిర్వచనం నిర్మాణం AVMD5 {
    uint64_t len;
    uint8_t  ఖండం[64];
    uint32_t ABCD[4];
} AVMD5;

స్థిరరాశి పూర్ణాంకం av_md5_కొలత = పరిమాణం(AVMD5);

నిర్మాణం AVMD5 *av_md5_alloc(శూన్య)
{
    తిరిగి av_mallocz(పరిమాణం(నిర్మాణం AVMD5));
}

స్థిర స్థిరరాశి uint8_t S[4][4] = {
    { 7, 12, 17, 22 },  /* round 1 */
    { 5,  9, 14, 20 },  /* round 2 */
    { 4, 11, 16, 23 },  /* round 3 */
    { 6, 10, 15, 21 }   /* round 4 */
};

స్థిర స్థిరరాశి uint32_t T[64] = { // T[i]= fabs(sin(i+1)<<32)
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,   /* round 1 */
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,

    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,   /* round 2 */
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,

    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,   /* round 3 */
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,

    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,   /* round 4 */
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

#నిర్వచించు CORE(i, a, b, c, d)                                             \
    చేయి {                                                                \
        t  = S[i >> 4][i & 3];                                          \
        a += T[i];                                                      \
                                                                        \
        ఒకవేళ (i < 32) {                                                   \
            ఒకవేళ (i < 16)                                                 \
                a += (d ^ (b & (c ^ d)))  + AV_RL32(X+(       i  & 15));\
            లేకపోతే                                                        \
                a += ((d & b) | (~d & c)) + AV_RL32(X+((1 + 5*i) & 15));\
        } లేకపోతే {                                                        \
            ఒకవేళ (i < 48)                                                 \
                a += (b ^ c ^ d)          + AV_RL32(X+((5 + 3*i) & 15));\
            లేకపోతే                                                        \
                a += (c ^ (b | ~d))       + AV_RL32(X+((    7*i) & 15));\
        }                                                               \
        a = b + (a << t | a >> (32 - t));                               \
    } అయితే (0)

స్థిర శూన్య body(uint32_t ABCD[4], స్థిరరాశి uint8_t *src, size_t nblocks)
{
    స్థిరరాశి uint32_t *X;
    uint32_t a, b, c, d, t;

    కొరకు (size_t n = 0; n < nblocks; n++) {
        a = ABCD[3];
        b = ABCD[2];
        c = ABCD[1];
        d = ABCD[0];

        X = (స్థిరరాశి uint32_t *)src + n * 16;

#ఒకవేళ CONFIG_SMALL
        కొరకు (పూర్ణాంకం i = 0; i < 64; i++) {
            CORE(i, a, b, c, d);
            t = d;
            d = c;
            c = b;
            b = a;
            a = t;
        }
#లేకపోతే
#నిర్వచించు CORE2(i)                                                        \
        CORE(i, a, b, c, d); CORE((i + 1), d, a, b, c);                 \
        CORE((i + 2), c, d, a, b); CORE((i + 3), b, c, d, a)
#నిర్వచించు CORE4(i) CORE2(i); CORE2((i + 4)); CORE2((i + 8)); CORE2((i + 12))
        CORE4(0);
        CORE4(16);
        CORE4(32);
        CORE4(48);
#అయితే_ముగింపు

        ABCD[0] += d;
        ABCD[1] += c;
        ABCD[2] += b;
        ABCD[3] += a;
    }
}

శూన్య av_md5_init(AVMD5 *ctx)
{
    ctx->len     = 0;

    ctx->ABCD[0] = 0x10325476;
    ctx->ABCD[1] = 0x98badcfe;
    ctx->ABCD[2] = 0xefcdab89;
    ctx->ABCD[3] = 0x67452301;
}

శూన్య av_md5_update(AVMD5 *ctx, స్థిరరాశి uint8_t *src, size_t len)
{
    స్థిరరాశి uint8_t *చివర;
    పూర్ణాంకం j;

    j         = ctx->len & 63;
    ctx->len += len;

    ఒకవేళ (j) {
        పూర్ణాంకం cnt = FFMIN(len, 64 - j);
        జ్ఞాపకం_నకలు(ctx->ఖండం + j, src, cnt);
        src += cnt;
        len -= cnt;
        ఒకవేళ (j + cnt < 64)
            తిరిగి;
        body(ctx->ABCD, ctx->ఖండం, 1);
    }

    చివర = src + (len & ~63);
    ఒకవేళ (!HAVE_FAST_UNALIGNED && ((intptr_t)src & 3)) {
       అయితే (src < చివర) {
           జ్ఞాపకం_నకలు(ctx->ఖండం, src, 64);
           body(ctx->ABCD, ctx->ఖండం, 1);
           src += 64;
        }
    } లేకపోతే {
        size_t nblocks = len / 64;
        body(ctx->ABCD, src, nblocks);
        src = చివర;
    }
    len &= 63;
    ఒకవేళ (len > 0)
        జ్ఞాపకం_నకలు(ctx->ఖండం, src, len);
}

శూన్య av_md5_final(AVMD5 *ctx, uint8_t *dst)
{
    పూర్ణాంకం i;
    uint64_t finalcount = av_le2ne64(ctx->len << 3);

    av_md5_update(ctx, "\200", 1);
    అయితే ((ctx->len & 63) != 56)
        av_md5_update(ctx, "", 1);

    av_md5_update(ctx, (uint8_t *) &finalcount, 8);

    కొరకు (i = 0; i < 4; i++)
        AV_WL32(dst + 4 * i, ctx->ABCD[3 - i]);
}

శూన్య av_md5_కూడిక(uint8_t *dst, స్థిరరాశి uint8_t *src, size_t len)
{
    AVMD5 ctx;

    av_md5_init(&ctx);
    av_md5_update(&ctx, src, len);
    av_md5_final(&ctx, dst);
}
