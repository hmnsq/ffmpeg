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

#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "attributes.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "hmac.h"
#அந்தர்பாவ "md5.h"
#அந்தர்பாவ "sha.h"
#அந்தர்பாவ "sha512.h"
#அந்தர்பாவ "mem.h"

#define MAX_HASHLEN 64
#define MAX_BLOCKLEN 128

வகைவரை வெறுமை (*hmac_final)(வெறுமை *ctx, uint8_t *dst);
வகைவரை வெறுமை (*hmac_update)(வெறுமை *ctx, மாறிலி uint8_t *src, size_t len);
வகைவரை வெறுமை (*hmac_init)(வெறுமை *ctx);

கட்டமைப்பு AVHMAC {
    வெறுமை *hash;
    முழு blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t சாவி[MAX_BLOCKLEN];
    முழு keylen;
};

#define DEFINE_ALGO_BITS_INIT(prefix, bits)        \
நிலையான av_cold வெறுமை prefix##bits##_init(வெறுமை *ctx) \
{                                                  \
    av_##prefix##_init(ctx, bits);                 \
}

#define DEFINE_ALGO_INIT(prefix)             \
நிலையான av_cold வெறுமை prefix##_init(வெறுமை *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#define DEFINE_ALGO(prefix)                                            \
நிலையான வெறுமை prefix##_update(வெறுமை *ctx, மாறிலி uint8_t *src, size_t len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
நிலையான வெறுமை prefix##_final(வெறுமை *ctx, uint8_t *dst)                    \
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

AVHMAC *av_hmac_alloc(எண்ணிக்கை AVHMACType type)
{
    AVHMAC *c = av_mallocz(அளவு(*c));
    எனில் (!c)
        திரும்பு வெற்று;
    தேர்வு (type) {
    நிலை AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        நிறுத்து;
    நிலை AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        நிறுத்து;
    நிலை AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        நிறுத்து;
    நிலை AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        நிறுத்து;
    நிலை AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        நிறுத்து;
    நிலை AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        நிறுத்து;
    இயல்பு:
        av_free(c);
        திரும்பு வெற்று;
    }
    எனில் (!c->hash) {
        av_free(c);
        திரும்பு வெற்று;
    }
    திரும்பு c;
}

வெறுமை av_hmac_free(AVHMAC *c)
{
    எனில் (!c)
        திரும்பு;
    av_freep(&c->hash);
    av_free(c);
}

வெறுமை av_hmac_init(AVHMAC *c, மாறிலி uint8_t *சாவி, unsigned முழு keylen)
{
    முழு i;
    uint8_t block[MAX_BLOCKLEN];
    எனில் (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, சாவி, keylen);
        c->final(c->hash, c->சாவி);
        c->keylen = c->hashlen;
    } இல்லையெனில் {
        memcpy(c->சாவி, சாவி, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    க்கு (i = 0; i < c->keylen; i++)
        block[i] = c->சாவி[i] ^ 0x36;
    க்கு (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x36;
    c->update(c->hash, block, c->blocklen);
}

வெறுமை av_hmac_update(AVHMAC *c, மாறிலி uint8_t *data, unsigned முழு len)
{
    c->update(c->hash, data, len);
}

முழு av_hmac_final(AVHMAC *c, uint8_t *out, unsigned முழு outlen)
{
    uint8_t block[MAX_BLOCKLEN];
    முழு i;
    எனில் (outlen < c->hashlen)
        திரும்பு AVERROR(EINVAL);
    c->final(c->hash, out);
    c->init(c->hash);
    க்கு (i = 0; i < c->keylen; i++)
        block[i] = c->சாவி[i] ^ 0x5C;
    க்கு (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x5C;
    c->update(c->hash, block, c->blocklen);
    c->update(c->hash, out, c->hashlen);
    c->final(c->hash, out);
    திரும்பு c->hashlen;
}

முழு av_hmac_calc(AVHMAC *c, மாறிலி uint8_t *data, unsigned முழு len,
                 மாறிலி uint8_t *சாவி, unsigned முழு keylen,
                 uint8_t *out, unsigned முழு outlen)
{
    av_hmac_init(c, சாவி, keylen);
    av_hmac_update(c, data, len);
    திரும்பு av_hmac_final(c, out, outlen);
}
