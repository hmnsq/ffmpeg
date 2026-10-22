/*
 * Copyright (C) 2012 Martin Storsjo
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

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "attributes.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "hmac.h"
#అన్తర్భావ "md5.h"
#అన్తర్భావ "sha.h"
#అన్తర్భావ "sha512.h"
#అన్తర్భావ "mem.h"

#నిర్వచించు MAX_HASHLEN 64
#నిర్వచించు MAX_BLOCKLEN 128

రకనిర్వచనం శూన్య (*hmac_final)(శూన్య *ctx, uint8_t *dst);
రకనిర్వచనం శూన్య (*hmac_update)(శూన్య *ctx, స్థిరరాశి uint8_t *src, size_t len);
రకనిర్వచనం శూన్య (*hmac_init)(శూన్య *ctx);

నిర్మాణం AVHMAC {
    శూన్య *hash;
    పూర్ణాంకం blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t కీలకం[MAX_BLOCKLEN];
    పూర్ణాంకం keylen;
};

#నిర్వచించు DEFINE_ALGO_బిట్లు_INIT(ఉపసర్గ, బిట్లు)        \
స్థిర av_cold శూన్య ఉపసర్గ##bits##_init(శూన్య *ctx) \
{                                                  \
    av_##prefix##_init(ctx, బిట్లు);                 \
}

#నిర్వచించు DEFINE_ALGO_INIT(ఉపసర్గ)             \
స్థిర av_cold శూన్య ఉపసర్గ##_init(శూన్య *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#నిర్వచించు DEFINE_ALGO(ఉపసర్గ)                                            \
స్థిర శూన్య ఉపసర్గ##_update(శూన్య *ctx, స్థిరరాశి uint8_t *src, size_t len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
స్థిర శూన్య ఉపసర్గ##_final(శూన్య *ctx, uint8_t *dst)                    \
{                                                                      \
    av_##prefix##_final(ctx, dst);                                     \
}

DEFINE_ALGO_INIT(md5)
DEFINE_ALGO_బిట్లు_INIT(sha, 160)
DEFINE_ALGO_బిట్లు_INIT(sha, 224)
DEFINE_ALGO_బిట్లు_INIT(sha, 256)
DEFINE_ALGO_బిట్లు_INIT(sha512, 384)
DEFINE_ALGO_బిట్లు_INIT(sha512, 512)
DEFINE_ALGO(md5)
DEFINE_ALGO(sha)
DEFINE_ALGO(sha512)

AVHMAC *av_hmac_alloc(గణన AVHMACType type)
{
    AVHMAC *c = av_mallocz(పరిమాణం(*c));
    ఒకవేళ (!c)
        తిరిగి ఖాళీ;
    ఎంపిక (type) {
    స్థితి AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        ఆపు;
    స్థితి AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ఆపు;
    స్థితి AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ఆపు;
    స్థితి AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ఆపు;
    స్థితి AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        ఆపు;
    స్థితి AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        ఆపు;
    అప్రమేయ:
        av_free(c);
        తిరిగి ఖాళీ;
    }
    ఒకవేళ (!c->hash) {
        av_free(c);
        తిరిగి ఖాళీ;
    }
    తిరిగి c;
}

శూన్య av_hmac_free(AVHMAC *c)
{
    ఒకవేళ (!c)
        తిరిగి;
    av_freep(&c->hash);
    av_free(c);
}

శూన్య av_hmac_init(AVHMAC *c, స్థిరరాశి uint8_t *కీలకం, గుర్తులేని పూర్ణాంకం keylen)
{
    పూర్ణాంకం i;
    uint8_t ఖండం[MAX_BLOCKLEN];
    ఒకవేళ (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, కీలకం, keylen);
        c->final(c->hash, c->కీలకం);
        c->keylen = c->hashlen;
    } లేకపోతే {
        జ్ఞాపకం_నకలు(c->కీలకం, కీలకం, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    కొరకు (i = 0; i < c->keylen; i++)
        ఖండం[i] = c->కీలకం[i] ^ 0x36;
    కొరకు (i = c->keylen; i < c->blocklen; i++)
        ఖండం[i] = 0x36;
    c->update(c->hash, ఖండం, c->blocklen);
}

శూన్య av_hmac_update(AVHMAC *c, స్థిరరాశి uint8_t *దత్తాంశం, గుర్తులేని పూర్ణాంకం len)
{
    c->update(c->hash, దత్తాంశం, len);
}

పూర్ణాంకం av_hmac_final(AVHMAC *c, uint8_t *బహిర్గతం, గుర్తులేని పూర్ణాంకం outlen)
{
    uint8_t ఖండం[MAX_BLOCKLEN];
    పూర్ణాంకం i;
    ఒకవేళ (outlen < c->hashlen)
        తిరిగి AVERROR(EINVAL);
    c->final(c->hash, బహిర్గతం);
    c->init(c->hash);
    కొరకు (i = 0; i < c->keylen; i++)
        ఖండం[i] = c->కీలకం[i] ^ 0x5C;
    కొరకు (i = c->keylen; i < c->blocklen; i++)
        ఖండం[i] = 0x5C;
    c->update(c->hash, ఖండం, c->blocklen);
    c->update(c->hash, బహిర్గతం, c->hashlen);
    c->final(c->hash, బహిర్గతం);
    తిరిగి c->hashlen;
}

పూర్ణాంకం av_hmac_calc(AVHMAC *c, స్థిరరాశి uint8_t *దత్తాంశం, గుర్తులేని పూర్ణాంకం len,
                 స్థిరరాశి uint8_t *కీలకం, గుర్తులేని పూర్ణాంకం keylen,
                 uint8_t *బహిర్గతం, గుర్తులేని పూర్ణాంకం outlen)
{
    av_hmac_init(c, కీలకం, keylen);
    av_hmac_update(c, దత్తాంశం, len);
    తిరిగి av_hmac_final(c, బహిర్గతం, outlen);
}
