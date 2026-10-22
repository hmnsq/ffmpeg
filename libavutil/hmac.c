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

#समावेश <stddef.h>
#समावेश <stdint.h>
#समावेश <string.h>

#समावेश "attributes.h"
#समावेश "error.h"
#समावेश "hmac.h"
#समावेश "md5.h"
#समावेश "sha.h"
#समावेश "sha512.h"
#समावेश "mem.h"

#घोषणा MAX_HASHLEN 64
#घोषणा MAX_BLOCKLEN 128

प्रकार व्योम (*hmac_final)(व्योम *ctx, uint8_t *dst);
प्रकार व्योम (*hmac_update)(व्योम *ctx, स्थिर uint8_t *src, माप_प्रकार len);
प्रकार व्योम (*hmac_init)(व्योम *ctx);

काष्ठा AVHMAC {
    व्योम *hash;
    पूर्णांक blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t कुंजी[MAX_BLOCKLEN];
    पूर्णांक keylen;
};

#घोषणा DEFINE_ALGO_BITS_INIT(prefix, bits)        \
अटल av_cold व्योम prefix##bits##_init(व्योम *ctx) \
{                                                  \
    av_##prefix##_init(ctx, bits);                 \
}

#घोषणा DEFINE_ALGO_INIT(prefix)             \
अटल av_cold व्योम prefix##_init(व्योम *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#घोषणा DEFINE_ALGO(prefix)                                            \
अटल व्योम prefix##_update(व्योम *ctx, स्थिर uint8_t *src, माप_प्रकार len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
अटल व्योम prefix##_final(व्योम *ctx, uint8_t *dst)                    \
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

AVHMAC *av_hmac_alloc(क्रमागत AVHMACType type)
{
    AVHMAC *c = av_mallocz(माप(*c));
    अगर (!c)
        वापस शून्य;
    चयन (type) {
    हाल AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        अवरोध;
    हाल AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        अवरोध;
    हाल AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        अवरोध;
    हाल AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        अवरोध;
    हाल AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        अवरोध;
    हाल AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        अवरोध;
    शेष:
        av_free(c);
        वापस शून्य;
    }
    अगर (!c->hash) {
        av_free(c);
        वापस शून्य;
    }
    वापस c;
}

व्योम av_hmac_free(AVHMAC *c)
{
    अगर (!c)
        वापस;
    av_freep(&c->hash);
    av_free(c);
}

व्योम av_hmac_init(AVHMAC *c, स्थिर uint8_t *कुंजी, अचिन्हित पूर्णांक keylen)
{
    पूर्णांक i;
    uint8_t block[MAX_BLOCKLEN];
    अगर (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, कुंजी, keylen);
        c->final(c->hash, c->कुंजी);
        c->keylen = c->hashlen;
    } अन्यथा {
        स_नकल(c->कुंजी, कुंजी, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    क्रम (i = 0; i < c->keylen; i++)
        block[i] = c->कुंजी[i] ^ 0x36;
    क्रम (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x36;
    c->update(c->hash, block, c->blocklen);
}

व्योम av_hmac_update(AVHMAC *c, स्थिर uint8_t *तथ्य, अचिन्हित पूर्णांक len)
{
    c->update(c->hash, तथ्य, len);
}

पूर्णांक av_hmac_final(AVHMAC *c, uint8_t *out, अचिन्हित पूर्णांक outlen)
{
    uint8_t block[MAX_BLOCKLEN];
    पूर्णांक i;
    अगर (outlen < c->hashlen)
        वापस AVERROR(EINVAL);
    c->final(c->hash, out);
    c->init(c->hash);
    क्रम (i = 0; i < c->keylen; i++)
        block[i] = c->कुंजी[i] ^ 0x5C;
    क्रम (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x5C;
    c->update(c->hash, block, c->blocklen);
    c->update(c->hash, out, c->hashlen);
    c->final(c->hash, out);
    वापस c->hashlen;
}

पूर्णांक av_hmac_calc(AVHMAC *c, स्थिर uint8_t *तथ्य, अचिन्हित पूर्णांक len,
                 स्थिर uint8_t *कुंजी, अचिन्हित पूर्णांक keylen,
                 uint8_t *out, अचिन्हित पूर्णांक outlen)
{
    av_hmac_init(c, कुंजी, keylen);
    av_hmac_update(c, तथ्य, len);
    वापस av_hmac_final(c, out, outlen);
}
