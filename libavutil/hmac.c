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

#ضمن <stddef.h>
#ضمن <stdint.h>
#ضمن <string.h>

#ضمن "attributes.h"
#ضمن "error.h"
#ضمن "hmac.h"
#ضمن "md5.h"
#ضمن "sha.h"
#ضمن "sha512.h"
#ضمن "mem.h"

#تعریف_کرو MAX_HASHLEN 64
#تعریف_کرو MAX_BLOCKLEN 128

تعريفنوع فراغ (*hmac_final)(فراغ *ctx, uint8_t *dst);
تعريفنوع فراغ (*hmac_update)(فراغ *ctx, ثابت uint8_t *src, size_t len);
تعريفنوع فراغ (*hmac_init)(فراغ *ctx);

بنية AVHMAC {
    فراغ *hash;
    صحيح blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t کلید[MAX_BLOCKLEN];
    صحيح keylen;
};

#تعریف_کرو DEFINE_ALGO_بٹ_INIT(اگیتر, بٹ)        \
ساكن av_cold فراغ اگیتر##bits##_init(فراغ *ctx) \
{                                                  \
    av_##prefix##_init(ctx, بٹ);                 \
}

#تعریف_کرو DEFINE_ALGO_INIT(اگیتر)             \
ساكن av_cold فراغ اگیتر##_init(فراغ *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#تعریف_کرو DEFINE_ALGO(اگیتر)                                            \
ساكن فراغ اگیتر##_update(فراغ *ctx, ثابت uint8_t *src, size_t len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
ساكن فراغ اگیتر##_final(فراغ *ctx, uint8_t *dst)                    \
{                                                                      \
    av_##prefix##_final(ctx, dst);                                     \
}

DEFINE_ALGO_INIT(md5)
DEFINE_ALGO_بٹ_INIT(sha, 160)
DEFINE_ALGO_بٹ_INIT(sha, 224)
DEFINE_ALGO_بٹ_INIT(sha, 256)
DEFINE_ALGO_بٹ_INIT(sha512, 384)
DEFINE_ALGO_بٹ_INIT(sha512, 512)
DEFINE_ALGO(md5)
DEFINE_ALGO(sha)
DEFINE_ALGO(sha512)

AVHMAC *av_hmac_alloc(تعداد AVHMACType type)
{
    AVHMAC *c = av_mallocz(حجم(*c));
    إذا (!c)
        أرجع عدم;
    بدل (type) {
    حالة AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        اكسر;
    حالة AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        اكسر;
    حالة AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        اكسر;
    حالة AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        اكسر;
    حالة AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        اكسر;
    حالة AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        اكسر;
    افتراضي:
        av_free(c);
        أرجع عدم;
    }
    إذا (!c->hash) {
        av_free(c);
        أرجع عدم;
    }
    أرجع c;
}

فراغ av_hmac_free(AVHMAC *c)
{
    إذا (!c)
        أرجع;
    av_freep(&c->hash);
    av_free(c);
}

فراغ av_hmac_init(AVHMAC *c, ثابت uint8_t *کلید, بنانشانی صحيح keylen)
{
    صحيح i;
    uint8_t بلاک[MAX_BLOCKLEN];
    إذا (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, کلید, keylen);
        c->final(c->hash, c->کلید);
        c->keylen = c->hashlen;
    } وإلا {
        حافظہ_نقل(c->کلید, کلید, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    لكل (i = 0; i < c->keylen; i++)
        بلاک[i] = c->کلید[i] ^ 0x36;
    لكل (i = c->keylen; i < c->blocklen; i++)
        بلاک[i] = 0x36;
    c->update(c->hash, بلاک, c->blocklen);
}

فراغ av_hmac_update(AVHMAC *c, ثابت uint8_t *انکڑے, بنانشانی صحيح len)
{
    c->update(c->hash, انکڑے, len);
}

صحيح av_hmac_final(AVHMAC *c, uint8_t *باہرلا, بنانشانی صحيح outlen)
{
    uint8_t بلاک[MAX_BLOCKLEN];
    صحيح i;
    إذا (outlen < c->hashlen)
        أرجع AVERROR(EINVAL);
    c->final(c->hash, باہرلا);
    c->init(c->hash);
    لكل (i = 0; i < c->keylen; i++)
        بلاک[i] = c->کلید[i] ^ 0x5C;
    لكل (i = c->keylen; i < c->blocklen; i++)
        بلاک[i] = 0x5C;
    c->update(c->hash, بلاک, c->blocklen);
    c->update(c->hash, باہرلا, c->hashlen);
    c->final(c->hash, باہرلا);
    أرجع c->hashlen;
}

صحيح av_hmac_calc(AVHMAC *c, ثابت uint8_t *انکڑے, بنانشانی صحيح len,
                 ثابت uint8_t *کلید, بنانشانی صحيح keylen,
                 uint8_t *باہرلا, بنانشانی صحيح outlen)
{
    av_hmac_init(c, کلید, keylen);
    av_hmac_update(c, انکڑے, len);
    أرجع av_hmac_final(c, باہرلا, outlen);
}
