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

#شامل <stddef.h>
#شامل <stdint.h>
#شامل <string.h>

#شامل "attributes.h"
#شامل "error.h"
#شامل "hmac.h"
#شامل "md5.h"
#شامل "sha.h"
#شامل "sha512.h"
#شامل "mem.h"

#define MAX_HASHLEN 64
#define MAX_BLOCKLEN 128

تعریفنوع تهی (*hmac_final)(تهی *ctx, uint8_t *dst);
تعریفنوع تهی (*hmac_update)(تهی *ctx, ثابت uint8_t *src, size_t len);
تعریفنوع تهی (*hmac_init)(تهی *ctx);

ساختار AVHMAC {
    تهی *hash;
    صحیح blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t کلید[MAX_BLOCKLEN];
    صحیح keylen;
};

#define DEFINE_ALGO_BITS_INIT(prefix, bits)        \
ایستا av_cold تهی prefix##bits##_init(تهی *ctx) \
{                                                  \
    av_##prefix##_init(ctx, bits);                 \
}

#define DEFINE_ALGO_INIT(prefix)             \
ایستا av_cold تهی prefix##_init(تهی *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#define DEFINE_ALGO(prefix)                                            \
ایستا تهی prefix##_update(تهی *ctx, ثابت uint8_t *src, size_t len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
ایستا تهی prefix##_final(تهی *ctx, uint8_t *dst)                    \
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

AVHMAC *av_hmac_alloc(شمارش AVHMACType type)
{
    AVHMAC *c = av_mallocz(اندازه(*c));
    اگر (!c)
        بازگشت پوچ;
    انتخاب (type) {
    حالت AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        بشکن;
    حالت AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        بشکن;
    حالت AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        بشکن;
    حالت AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        بشکن;
    حالت AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        بشکن;
    حالت AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        بشکن;
    پیشفرض:
        av_free(c);
        بازگشت پوچ;
    }
    اگر (!c->hash) {
        av_free(c);
        بازگشت پوچ;
    }
    بازگشت c;
}

تهی av_hmac_free(AVHMAC *c)
{
    اگر (!c)
        بازگشت;
    av_freep(&c->hash);
    av_free(c);
}

تهی av_hmac_init(AVHMAC *c, ثابت uint8_t *کلید, unsigned صحیح keylen)
{
    صحیح i;
    uint8_t block[MAX_BLOCKLEN];
    اگر (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, کلید, keylen);
        c->final(c->hash, c->کلید);
        c->keylen = c->hashlen;
    } وگرنه {
        memcpy(c->کلید, کلید, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    برای (i = 0; i < c->keylen; i++)
        block[i] = c->کلید[i] ^ 0x36;
    برای (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x36;
    c->update(c->hash, block, c->blocklen);
}

تهی av_hmac_update(AVHMAC *c, ثابت uint8_t *data, unsigned صحیح len)
{
    c->update(c->hash, data, len);
}

صحیح av_hmac_final(AVHMAC *c, uint8_t *out, unsigned صحیح outlen)
{
    uint8_t block[MAX_BLOCKLEN];
    صحیح i;
    اگر (outlen < c->hashlen)
        بازگشت AVERROR(EINVAL);
    c->final(c->hash, out);
    c->init(c->hash);
    برای (i = 0; i < c->keylen; i++)
        block[i] = c->کلید[i] ^ 0x5C;
    برای (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x5C;
    c->update(c->hash, block, c->blocklen);
    c->update(c->hash, out, c->hashlen);
    c->final(c->hash, out);
    بازگشت c->hashlen;
}

صحیح av_hmac_calc(AVHMAC *c, ثابت uint8_t *data, unsigned صحیح len,
                 ثابت uint8_t *کلید, unsigned صحیح keylen,
                 uint8_t *out, unsigned صحیح outlen)
{
    av_hmac_init(c, کلید, keylen);
    av_hmac_update(c, data, len);
    بازگشت av_hmac_final(c, out, outlen);
}
