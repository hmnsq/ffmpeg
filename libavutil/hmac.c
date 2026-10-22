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

#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "attributes.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "hmac.h"
#অন্তর্ভাব "md5.h"
#অন্তর্ভাব "sha.h"
#অন্তর্ভাব "sha512.h"
#অন্তর্ভাব "mem.h"

#define MAX_HASHLEN 64
#define MAX_BLOCKLEN 128

প্রকারনির্দেশ শূন্য (*hmac_final)(শূন্য *ctx, uint8_t *dst);
প্রকারনির্দেশ শূন্য (*hmac_update)(শূন্য *ctx, ধ্রুব uint8_t *src, size_t len);
প্রকারনির্দেশ শূন্য (*hmac_init)(শূন্য *ctx);

সংরচনা AVHMAC {
    শূন্য *hash;
    পূর্ণাঙ্ক blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t চাবি[MAX_BLOCKLEN];
    পূর্ণাঙ্ক keylen;
};

#define DEFINE_ALGO_BITS_INIT(prefix, bits)        \
স্থির av_cold শূন্য prefix##bits##_init(শূন্য *ctx) \
{                                                  \
    av_##prefix##_init(ctx, bits);                 \
}

#define DEFINE_ALGO_INIT(prefix)             \
স্থির av_cold শূন্য prefix##_init(শূন্য *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#define DEFINE_ALGO(prefix)                                            \
স্থির শূন্য prefix##_update(শূন্য *ctx, ধ্রুব uint8_t *src, size_t len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
স্থির শূন্য prefix##_final(শূন্য *ctx, uint8_t *dst)                    \
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

AVHMAC *av_hmac_alloc(গণনা AVHMACType type)
{
    AVHMAC *c = av_mallocz(পরিমাণ(*c));
    যদি (!c)
        প্রত্যাগম রিক্ত;
    বিকল্প (type) {
    পক্ষ AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        ভঙ্গ;
    পক্ষ AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ভঙ্গ;
    পক্ষ AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ভঙ্গ;
    পক্ষ AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ভঙ্গ;
    পক্ষ AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        ভঙ্গ;
    পক্ষ AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        ভঙ্গ;
    স্বভাব:
        av_free(c);
        প্রত্যাগম রিক্ত;
    }
    যদি (!c->hash) {
        av_free(c);
        প্রত্যাগম রিক্ত;
    }
    প্রত্যাগম c;
}

শূন্য av_hmac_free(AVHMAC *c)
{
    যদি (!c)
        প্রত্যাগম;
    av_freep(&c->hash);
    av_free(c);
}

শূন্য av_hmac_init(AVHMAC *c, ধ্রুব uint8_t *চাবি, unsigned পূর্ণাঙ্ক keylen)
{
    পূর্ণাঙ্ক i;
    uint8_t block[MAX_BLOCKLEN];
    যদি (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, চাবি, keylen);
        c->final(c->hash, c->চাবি);
        c->keylen = c->hashlen;
    } অন্যথা {
        memcpy(c->চাবি, চাবি, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    প্রতি (i = 0; i < c->keylen; i++)
        block[i] = c->চাবি[i] ^ 0x36;
    প্রতি (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x36;
    c->update(c->hash, block, c->blocklen);
}

শূন্য av_hmac_update(AVHMAC *c, ধ্রুব uint8_t *data, unsigned পূর্ণাঙ্ক len)
{
    c->update(c->hash, data, len);
}

পূর্ণাঙ্ক av_hmac_final(AVHMAC *c, uint8_t *out, unsigned পূর্ণাঙ্ক outlen)
{
    uint8_t block[MAX_BLOCKLEN];
    পূর্ণাঙ্ক i;
    যদি (outlen < c->hashlen)
        প্রত্যাগম AVERROR(EINVAL);
    c->final(c->hash, out);
    c->init(c->hash);
    প্রতি (i = 0; i < c->keylen; i++)
        block[i] = c->চাবি[i] ^ 0x5C;
    প্রতি (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x5C;
    c->update(c->hash, block, c->blocklen);
    c->update(c->hash, out, c->hashlen);
    c->final(c->hash, out);
    প্রত্যাগম c->hashlen;
}

পূর্ণাঙ্ক av_hmac_calc(AVHMAC *c, ধ্রুব uint8_t *data, unsigned পূর্ণাঙ্ক len,
                 ধ্রুব uint8_t *চাবি, unsigned পূর্ণাঙ্ক keylen,
                 uint8_t *out, unsigned পূর্ণাঙ্ক outlen)
{
    av_hmac_init(c, চাবি, keylen);
    av_hmac_update(c, data, len);
    প্রত্যাগম av_hmac_final(c, out, outlen);
}
