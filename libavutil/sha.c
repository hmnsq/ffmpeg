/*
 * Copyright (C) 2007 Michael Niedermayer <michaelni@gmx.at>
 * Copyright (C) 2009 Konstantin Shishkov
 * based on public domain SHA-1 code by Steve Reid <steve@edmweb.com>
 * and on BSD-licensed SHA-2 code by Aaron D. Gifford
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

#అన్తర్భావ <string.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "attributes.h"
#అన్తర్భావ "bswap.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "sha.h"
#అన్తర్భావ "intreadwrite.h"
#అన్తర్భావ "mem.h"

/** hash context */
రకనిర్వచనం నిర్మాణం AVSHA {
    uint8_t  digest_len;  ///< digest length in 32-bit words
    uint64_t లెక్క;       ///< number of bytes in buffer
    uint8_t  బఫరు[64];  ///< 512-bit buffer of input values used in hash updating
    uint32_t state[8];    ///< current hash value
    /** function used to update hash for 512-bit input block */
    శూన్య     (*transform)(uint32_t *state, స్థిరరాశి uint8_t బఫరు[64]);
} AVSHA;

స్థిరరాశి పూర్ణాంకం av_sha_కొలత = పరిమాణం(AVSHA);

నిర్మాణం AVSHA *av_sha_alloc(శూన్య)
{
    తిరిగి av_mallocz(పరిమాణం(నిర్మాణం AVSHA));
}

#నిర్వచించు rol(విలువ, బిట్లు) (((విలువ) << (బిట్లు)) | ((విలువ) >> (32 - (బిట్లు))))

/* (R0+R1), R2, R3, R4 are the different operations used in SHA1 */
#నిర్వచించు blk0(i) (ఖండం[i] = AV_RB32(బఫరు + 4 * (i)))
#నిర్వచించు blk(i)  (ఖండం[i] = rol(ఖండం[(i)-3] ^ ఖండం[(i)-8] ^ ఖండం[(i)-14] ^ ఖండం[(i)-16], 1))

#నిర్వచించు R0(v,w,x,y,z,i) z += (((w)&((x)^(y)))^(y))       + blk0(i) + 0x5A827999 + rol(v, 5); w = rol(w, 30);
#నిర్వచించు R1(v,w,x,y,z,i) z += (((w)&((x)^(y)))^(y))       + blk (i) + 0x5A827999 + rol(v, 5); w = rol(w, 30);
#నిర్వచించు R2(v,w,x,y,z,i) z += ( (w)^(x)       ^(y))       + blk (i) + 0x6ED9EBA1 + rol(v, 5); w = rol(w, 30);
#నిర్వచించు R3(v,w,x,y,z,i) z += ((((w)|(x))&(y))|((w)&(x))) + blk (i) + 0x8F1BBCDC + rol(v, 5); w = rol(w, 30);
#నిర్వచించు R4(v,w,x,y,z,i) z += ( (w)^(x)       ^(y))       + blk (i) + 0xCA62C1D6 + rol(v, 5); w = rol(w, 30);

/* Hash a single 512-bit block. This is the core of the algorithm. */

స్థిర శూన్య sha1_transform(uint32_t state[5], స్థిరరాశి uint8_t బఫరు[64])
{
    uint32_t ఖండం[80];
    గుర్తులేని పూర్ణాంకం i, a, b, c, d, e;

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
#ఒకవేళ CONFIG_SMALL
    కొరకు (i = 0; i < 80; i++) {
        పూర్ణాంకం t;
        ఒకవేళ (i < 16)
            t = AV_RB32(బఫరు + 4 * i);
        లేకపోతే
            t = rol(ఖండం[i-3] ^ ఖండం[i-8] ^ ఖండం[i-14] ^ ఖండం[i-16], 1);
        ఖండం[i] = t;
        t += e + rol(a, 5);
        ఒకవేళ (i < 40) {
            ఒకవేళ (i < 20)
                t += ((b&(c^d))^d)     + 0x5A827999;
            లేకపోతే
                t += ( b^c     ^d)     + 0x6ED9EBA1;
        } లేకపోతే {
            ఒకవేళ (i < 60)
                t += (((b|c)&d)|(b&c)) + 0x8F1BBCDC;
            లేకపోతే
                t += ( b^c     ^d)     + 0xCA62C1D6;
        }
        e = d;
        d = c;
        c = rol(b, 30);
        b = a;
        a = t;
    }
#లేకపోతే

#నిర్వచించు R1_0 \
    R0(a, b, c, d, e, 0 + i); \
    R0(e, a, b, c, d, 1 + i); \
    R0(d, e, a, b, c, 2 + i); \
    R0(c, d, e, a, b, 3 + i); \
    R0(b, c, d, e, a, 4 + i); \
    i += 5

    i = 0;
    R1_0; R1_0; R1_0;
    R0(a, b, c, d, e, 15);
    R1(e, a, b, c, d, 16);
    R1(d, e, a, b, c, 17);
    R1(c, d, e, a, b, 18);
    R1(b, c, d, e, a, 19);

#నిర్వచించు R1_20 \
    R2(a, b, c, d, e, 0 + i); \
    R2(e, a, b, c, d, 1 + i); \
    R2(d, e, a, b, c, 2 + i); \
    R2(c, d, e, a, b, 3 + i); \
    R2(b, c, d, e, a, 4 + i); \
    i += 5

    i = 20;
    R1_20; R1_20; R1_20; R1_20;

#నిర్వచించు R1_40 \
    R3(a, b, c, d, e, 0 + i); \
    R3(e, a, b, c, d, 1 + i); \
    R3(d, e, a, b, c, 2 + i); \
    R3(c, d, e, a, b, 3 + i); \
    R3(b, c, d, e, a, 4 + i); \
    i += 5

    R1_40; R1_40; R1_40; R1_40;

#నిర్వచించు R1_60 \
    R4(a, b, c, d, e, 0 + i); \
    R4(e, a, b, c, d, 1 + i); \
    R4(d, e, a, b, c, 2 + i); \
    R4(c, d, e, a, b, 3 + i); \
    R4(b, c, d, e, a, 4 + i); \
    i += 5

    R1_60; R1_60; R1_60; R1_60;
#అయితే_ముగింపు
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
}

స్థిర స్థిరరాశి uint32_t K256[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


#నిర్వచించు Ch(x,y,z)   (((x) & ((y) ^ (z))) ^ (z))
#నిర్వచించు Maj(z,y,x)  ((((x) | (y)) & (z)) | ((x) & (y)))

#నిర్వచించు Sigma0_256(x)   (rol((x), 30) ^ rol((x), 19) ^ rol((x), 10))
#నిర్వచించు Sigma1_256(x)   (rol((x), 26) ^ rol((x), 21) ^ rol((x),  7))
#నిర్వచించు sigma0_256(x)   (rol((x), 25) ^ rol((x), 14) ^ ((x) >> 3))
#నిర్వచించు sigma1_256(x)   (rol((x), 15) ^ rol((x), 13) ^ ((x) >> 10))

#నిర్వచనం_రద్దు blk
#నిర్వచించు blk(i)  (ఖండం[i] = ఖండం[i - 16] + sigma0_256(ఖండం[i - 15]) + \
                            sigma1_256(ఖండం[i - 2]) + ఖండం[i - 7])

#నిర్వచించు ROUND256(a,b,c,d,e,f,g,h)   \
    T1 += (h) + Sigma1_256(e) + Ch((e), (f), (g)) + K256[i]; \
    (d) += T1; \
    (h) = T1 + Sigma0_256(a) + Maj((a), (b), (c)); \
    i++

#నిర్వచించు ROUND256_0_గమ్యం_15(a,b,c,d,e,f,g,h)   \
    T1 = blk0(i); \
    ROUND256(a,b,c,d,e,f,g,h)

#నిర్వచించు ROUND256_16_గమ్యం_63(a,b,c,d,e,f,g,h)   \
    T1 = blk(i); \
    ROUND256(a,b,c,d,e,f,g,h)

స్థిర శూన్య sha256_transform(uint32_t *state, స్థిరరాశి uint8_t బఫరు[64])
{
    గుర్తులేని పూర్ణాంకం i, a, b, c, d, e, f, g, h;
    uint32_t ఖండం[64];
    uint32_t T1;

    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];
#ఒకవేళ CONFIG_SMALL
    కొరకు (i = 0; i < 64; i++) {
        uint32_t T2;
        ఒకవేళ (i < 16)
            T1 = blk0(i);
        లేకపోతే
            T1 = blk(i);
        T1 += h + Sigma1_256(e) + Ch(e, f, g) + K256[i];
        T2 = Sigma0_256(a) + Maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }
#లేకపోతే

    i = 0;
#నిర్వచించు R256_0 \
    ROUND256_0_గమ్యం_15(a, b, c, d, e, f, g, h); \
    ROUND256_0_గమ్యం_15(h, a, b, c, d, e, f, g); \
    ROUND256_0_గమ్యం_15(g, h, a, b, c, d, e, f); \
    ROUND256_0_గమ్యం_15(f, g, h, a, b, c, d, e); \
    ROUND256_0_గమ్యం_15(e, f, g, h, a, b, c, d); \
    ROUND256_0_గమ్యం_15(d, e, f, g, h, a, b, c); \
    ROUND256_0_గమ్యం_15(c, d, e, f, g, h, a, b); \
    ROUND256_0_గమ్యం_15(b, c, d, e, f, g, h, a)

    R256_0; R256_0;

#నిర్వచించు R256_16 \
    ROUND256_16_గమ్యం_63(a, b, c, d, e, f, g, h); \
    ROUND256_16_గమ్యం_63(h, a, b, c, d, e, f, g); \
    ROUND256_16_గమ్యం_63(g, h, a, b, c, d, e, f); \
    ROUND256_16_గమ్యం_63(f, g, h, a, b, c, d, e); \
    ROUND256_16_గమ్యం_63(e, f, g, h, a, b, c, d); \
    ROUND256_16_గమ్యం_63(d, e, f, g, h, a, b, c); \
    ROUND256_16_గమ్యం_63(c, d, e, f, g, h, a, b); \
    ROUND256_16_గమ్యం_63(b, c, d, e, f, g, h, a)

    R256_16; R256_16; R256_16;
    R256_16; R256_16; R256_16;
#అయితే_ముగింపు
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
}


av_cold పూర్ణాంకం av_sha_init(AVSHA *ctx, పూర్ణాంకం బిట్లు)
{
    ctx->digest_len = బిట్లు >> 5;
    ఎంపిక (బిట్లు) {
    స్థితి 160: // SHA-1
        ctx->state[0] = 0x67452301;
        ctx->state[1] = 0xEFCDAB89;
        ctx->state[2] = 0x98BADCFE;
        ctx->state[3] = 0x10325476;
        ctx->state[4] = 0xC3D2E1F0;
        ctx->transform = sha1_transform;
        ఆపు;
    స్థితి 224: // SHA-224
        ctx->state[0] = 0xC1059ED8;
        ctx->state[1] = 0x367CD507;
        ctx->state[2] = 0x3070DD17;
        ctx->state[3] = 0xF70E5939;
        ctx->state[4] = 0xFFC00B31;
        ctx->state[5] = 0x68581511;
        ctx->state[6] = 0x64F98FA7;
        ctx->state[7] = 0xBEFA4FA4;
        ctx->transform = sha256_transform;
        ఆపు;
    స్థితి 256: // SHA-256
        ctx->state[0] = 0x6A09E667;
        ctx->state[1] = 0xBB67AE85;
        ctx->state[2] = 0x3C6EF372;
        ctx->state[3] = 0xA54FF53A;
        ctx->state[4] = 0x510E527F;
        ctx->state[5] = 0x9B05688C;
        ctx->state[6] = 0x1F83D9AB;
        ctx->state[7] = 0x5BE0CD19;
        ctx->transform = sha256_transform;
        ఆపు;
    అప్రమేయ:
        తిరిగి AVERROR(EINVAL);
    }
    ctx->లెక్క = 0;
    తిరిగి 0;
}

శూన్య av_sha_update(నిర్మాణం AVSHA *ctx, స్థిరరాశి uint8_t *దత్తాంశం, size_t len)
{
    గుర్తులేని పూర్ణాంకం j;
    size_t i;

    j = ctx->లెక్క & 63;
    ctx->లెక్క += len;
#ఒకవేళ CONFIG_SMALL
    కొరకు (i = 0; i < len; i++) {
        ctx->బఫరు[j++] = దత్తాంశం[i];
        ఒకవేళ (64 == j) {
            ctx->transform(ctx->state, ctx->బఫరు);
            j = 0;
        }
    }
#లేకపోతే
    ఒకవేళ (len >= 64 - j) {
        స్థిరరాశి uint8_t *చివర;
        జ్ఞాపకం_నకలు(&ctx->బఫరు[j], దత్తాంశం, (i = 64 - j));
        ctx->transform(ctx->state, ctx->బఫరు);
        దత్తాంశం += i;
        len  -= i;
        చివర   = దత్తాంశం + (len & ~63);
        len   = len % 64;
        కొరకు (; దత్తాంశం < చివర; దత్తాంశం += 64)
            ctx->transform(ctx->state, దత్తాంశం);
        j = 0;
    }
    జ్ఞాపకం_నకలు(&ctx->బఫరు[j], దత్తాంశం, len);
#అయితే_ముగింపు
}

శూన్య av_sha_final(AVSHA* ctx, uint8_t *digest)
{
    పూర్ణాంకం i;
    uint64_t finalcount = av_be2ne64(ctx->లెక్క << 3);

    av_sha_update(ctx, "\200", 1);
    అయితే ((ctx->లెక్క & 63) != 56)
        av_sha_update(ctx, "", 1);
    av_sha_update(ctx, (uint8_t *)&finalcount, 8); /* Should cause a transform() */
    కొరకు (i = 0; i < ctx->digest_len; i++)
        AV_WB32(digest + i*4, ctx->state[i]);
}
