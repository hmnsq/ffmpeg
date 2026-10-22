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

#ଅନ୍ତର୍ଭାଵ <stddef.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "attributes.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "hmac.h"
#ଅନ୍ତର୍ଭାଵ "md5.h"
#ଅନ୍ତର୍ଭାଵ "sha.h"
#ଅନ୍ତର୍ଭାଵ "sha512.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"

#define MAX_HASHLEN 64
#define MAX_BLOCKLEN 128

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (*hmac_final)(ଶୂନ୍ୟ *ctx, uint8_t *dst);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (*hmac_update)(ଶୂନ୍ୟ *ctx, ଅଚଳ uint8_t *src, size_t len);
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (*hmac_init)(ଶୂନ୍ୟ *ctx);

ସଂରଚନା AVHMAC {
    ଶୂନ୍ୟ *hash;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t ଚାବି[MAX_BLOCKLEN];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା keylen;
};

#define DEFINE_ALGO_BITS_INIT(prefix, bits)        \
ସ୍ଥିର av_cold ଶୂନ୍ୟ prefix##bits##_init(ଶୂନ୍ୟ *ctx) \
{                                                  \
    av_##prefix##_init(ctx, bits);                 \
}

#define DEFINE_ALGO_INIT(prefix)             \
ସ୍ଥିର av_cold ଶୂନ୍ୟ prefix##_init(ଶୂନ୍ୟ *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#define DEFINE_ALGO(prefix)                                            \
ସ୍ଥିର ଶୂନ୍ୟ prefix##_update(ଶୂନ୍ୟ *ctx, ଅଚଳ uint8_t *src, size_t len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
ସ୍ଥିର ଶୂନ୍ୟ prefix##_final(ଶୂନ୍ୟ *ctx, uint8_t *dst)                    \
{                                                                      \
    av_##prefix##_final(ctx, dst);                                     \
}

DEFINE_ALGO_INIT(md5)
DEFINE_ALGO_BITS_INIT(sha, 160)
DEFINE_ALGO_BITS_INIT(sha, 224)
DEFINE_ALGO_BITS_INIT(sha, 256)
DEFINE_ALGO_BITS_INIT(sha512, 384)
DEFINE_ALGO_BITS_INIT(sha512, 512)
DEFINE_ALGO(md5)
DEFINE_ALGO(sha)
DEFINE_ALGO(sha512)

AVHMAC *av_hmac_alloc(ଗଣନା AVHMACType type)
{
    AVHMAC *c = av_mallocz(ଆକାର(*c));
    ଯଦି (!c)
        ଫେରନ୍ତୁ ଖାଲି;
    ବାଛ (type) {
    ସ୍ଥିତି AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        av_free(c);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଯଦି (!c->hash) {
        av_free(c);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ c;
}

ଶୂନ୍ୟ av_hmac_free(AVHMAC *c)
{
    ଯଦି (!c)
        ଫେରନ୍ତୁ;
    av_freep(&c->hash);
    av_free(c);
}

ଶୂନ୍ୟ av_hmac_init(AVHMAC *c, ଅଚଳ uint8_t *ଚାବି, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା keylen)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    uint8_t block[MAX_BLOCKLEN];
    ଯଦି (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, ଚାବି, keylen);
        c->final(c->hash, c->ଚାବି);
        c->keylen = c->hashlen;
    } ଅନ୍ୟଥା {
        memcpy(c->ଚାବି, ଚାବି, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    ପାଇଁ (i = 0; i < c->keylen; i++)
        block[i] = c->ଚାବି[i] ^ 0x36;
    ପାଇଁ (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x36;
    c->update(c->hash, block, c->blocklen);
}

ଶୂନ୍ୟ av_hmac_update(AVHMAC *c, ଅଚଳ uint8_t *data, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    c->update(c->hash, data, len);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hmac_final(AVHMAC *c, uint8_t *out, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା outlen)
{
    uint8_t block[MAX_BLOCKLEN];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ଯଦି (outlen < c->hashlen)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    c->final(c->hash, out);
    c->init(c->hash);
    ପାଇଁ (i = 0; i < c->keylen; i++)
        block[i] = c->ଚାବି[i] ^ 0x5C;
    ପାଇଁ (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x5C;
    c->update(c->hash, block, c->blocklen);
    c->update(c->hash, out, c->hashlen);
    c->final(c->hash, out);
    ଫେରନ୍ତୁ c->hashlen;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hmac_calc(AVHMAC *c, ଅଚଳ uint8_t *data, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା len,
                 ଅଚଳ uint8_t *ଚାବି, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା keylen,
                 uint8_t *out, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା outlen)
{
    av_hmac_init(c, ଚାବି, keylen);
    av_hmac_update(c, data, len);
    ଫେରନ୍ତୁ av_hmac_final(c, out, outlen);
}
