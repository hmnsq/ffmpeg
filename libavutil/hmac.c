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

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hmac.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "md5.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "sha.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "sha512.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_HASHLEN 64
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_BLOCKLEN 128

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*hmac_final)(ਖਾਲੀ *ctx, uint8_t *dst);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*hmac_update)(ਖਾਲੀ *ctx, ਅਚਲ uint8_t *src, size_t len);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*hmac_init)(ਖਾਲੀ *ctx);

ਬਣਤਰ AVHMAC {
    ਖਾਲੀ *hash;
    ਪੂਰਨ blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t ਕੁੰਜੀ[MAX_BLOCKLEN];
    ਪੂਰਨ keylen;
};

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFINE_ALGO_ਬਿੱਟ_INIT(ਅਗੇਤਰ, ਬਿੱਟ)        \
ਸਥਿਰ av_cold ਖਾਲੀ ਅਗੇਤਰ##bits##_init(ਖਾਲੀ *ctx) \
{                                                  \
    av_##prefix##_init(ctx, ਬਿੱਟ);                 \
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFINE_ALGO_INIT(ਅਗੇਤਰ)             \
ਸਥਿਰ av_cold ਖਾਲੀ ਅਗੇਤਰ##_init(ਖਾਲੀ *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DEFINE_ALGO(ਅਗੇਤਰ)                                            \
ਸਥਿਰ ਖਾਲੀ ਅਗੇਤਰ##_update(ਖਾਲੀ *ctx, ਅਚਲ uint8_t *src, size_t len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
ਸਥਿਰ ਖਾਲੀ ਅਗੇਤਰ##_final(ਖਾਲੀ *ctx, uint8_t *dst)                    \
{                                                                      \
    av_##prefix##_final(ctx, dst);                                     \
}

DEFINE_ALGO_INIT(md5)
DEFINE_ALGO_ਬਿੱਟ_INIT(sha, 160)
DEFINE_ALGO_ਬਿੱਟ_INIT(sha, 224)
DEFINE_ALGO_ਬਿੱਟ_INIT(sha, 256)
DEFINE_ALGO_ਬਿੱਟ_INIT(sha512, 384)
DEFINE_ALGO_ਬਿੱਟ_INIT(sha512, 512)
DEFINE_ALGO(md5)
DEFINE_ALGO(sha)
DEFINE_ALGO(sha512)

AVHMAC *av_hmac_alloc(ਗਿਣਤੀ AVHMACType type)
{
    AVHMAC *c = av_mallocz(ਆਕਾਰ(*c));
    ਜੇ (!c)
        ਵਾਪਸ ਨਿਰਾ;
    ਚੋਣ (type) {
    ਹਾਲਤ AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        ਰੋਕੋ;
    ਹਾਲਤ AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ਰੋਕੋ;
    ਹਾਲਤ AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ਰੋਕੋ;
    ਹਾਲਤ AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ਰੋਕੋ;
    ਹਾਲਤ AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        ਰੋਕੋ;
    ਹਾਲਤ AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        ਰੋਕੋ;
    ਮੂਲ:
        av_free(c);
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਜੇ (!c->hash) {
        av_free(c);
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ c;
}

ਖਾਲੀ av_hmac_free(AVHMAC *c)
{
    ਜੇ (!c)
        ਵਾਪਸ;
    av_freep(&c->hash);
    av_free(c);
}

ਖਾਲੀ av_hmac_init(AVHMAC *c, ਅਚਲ uint8_t *ਕੁੰਜੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ keylen)
{
    ਪੂਰਨ i;
    uint8_t ਖੰਡ[MAX_BLOCKLEN];
    ਜੇ (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, ਕੁੰਜੀ, keylen);
        c->final(c->hash, c->ਕੁੰਜੀ);
        c->keylen = c->hashlen;
    } ਨਹੀਂਤਾਂ {
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(c->ਕੁੰਜੀ, ਕੁੰਜੀ, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    ਲਈ (i = 0; i < c->keylen; i++)
        ਖੰਡ[i] = c->ਕੁੰਜੀ[i] ^ 0x36;
    ਲਈ (i = c->keylen; i < c->blocklen; i++)
        ਖੰਡ[i] = 0x36;
    c->update(c->hash, ਖੰਡ, c->blocklen);
}

ਖਾਲੀ av_hmac_update(AVHMAC *c, ਅਚਲ uint8_t *ਅੰਕੜੇ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ len)
{
    c->update(c->hash, ਅੰਕੜੇ, len);
}

ਪੂਰਨ av_hmac_final(AVHMAC *c, uint8_t *ਬਾਹਰਲਾ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ outlen)
{
    uint8_t ਖੰਡ[MAX_BLOCKLEN];
    ਪੂਰਨ i;
    ਜੇ (outlen < c->hashlen)
        ਵਾਪਸ AVERROR(EINVAL);
    c->final(c->hash, ਬਾਹਰਲਾ);
    c->init(c->hash);
    ਲਈ (i = 0; i < c->keylen; i++)
        ਖੰਡ[i] = c->ਕੁੰਜੀ[i] ^ 0x5C;
    ਲਈ (i = c->keylen; i < c->blocklen; i++)
        ਖੰਡ[i] = 0x5C;
    c->update(c->hash, ਖੰਡ, c->blocklen);
    c->update(c->hash, ਬਾਹਰਲਾ, c->hashlen);
    c->final(c->hash, ਬਾਹਰਲਾ);
    ਵਾਪਸ c->hashlen;
}

ਪੂਰਨ av_hmac_calc(AVHMAC *c, ਅਚਲ uint8_t *ਅੰਕੜੇ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ len,
                 ਅਚਲ uint8_t *ਕੁੰਜੀ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ keylen,
                 uint8_t *ਬਾਹਰਲਾ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ outlen)
{
    av_hmac_init(c, ਕੁੰਜੀ, keylen);
    av_hmac_update(c, ਅੰਕੜੇ, len);
    ਵਾਪਸ av_hmac_final(c, ਬਾਹਰਲਾ, outlen);
}
