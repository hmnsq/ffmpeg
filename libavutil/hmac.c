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

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "attributes.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "hmac.h"
#अन्तर्भाव "md5.h"
#अन्तर्भाव "sha.h"
#अन्तर्भाव "sha512.h"
#अन्तर्भाव "mem.h"

#define MAX_HASHLEN 64
#define MAX_BLOCKLEN 128

प्रकारव्याख्या शून्य (*hmac_final)(शून्य *ctx, uint8_t *dst);
प्रकारव्याख्या शून्य (*hmac_update)(शून्य *ctx, स्थिरांक uint8_t *src, माप_प्रकार len);
प्रकारव्याख्या शून्य (*hmac_init)(शून्य *ctx);

संरचना AVHMAC {
    शून्य *hash;
    पूर्णांक blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t किल्ली[MAX_BLOCKLEN];
    पूर्णांक keylen;
};

#define DEFINE_ALGO_BITS_INIT(prefix, bits)        \
स्थिर av_cold शून्य prefix##bits##_init(शून्य *ctx) \
{                                                  \
    av_##prefix##_init(ctx, bits);                 \
}

#define DEFINE_ALGO_INIT(prefix)             \
स्थिर av_cold शून्य prefix##_init(शून्य *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#define DEFINE_ALGO(prefix)                                            \
स्थिर शून्य prefix##_update(शून्य *ctx, स्थिरांक uint8_t *src, माप_प्रकार len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
स्थिर शून्य prefix##_final(शून्य *ctx, uint8_t *dst)                    \
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

AVHMAC *av_hmac_alloc(गणना AVHMACType type)
{
    AVHMAC *c = av_mallocz(आकार(*c));
    जर (!c)
        परत रिक्त;
    निवड (type) {
    स्थिती AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        थांबा;
    स्थिती AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        थांबा;
    स्थिती AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        थांबा;
    स्थिती AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        थांबा;
    स्थिती AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        थांबा;
    स्थिती AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        थांबा;
    पूर्वनिर्धारित:
        av_free(c);
        परत रिक्त;
    }
    जर (!c->hash) {
        av_free(c);
        परत रिक्त;
    }
    परत c;
}

शून्य av_hmac_free(AVHMAC *c)
{
    जर (!c)
        परत;
    av_freep(&c->hash);
    av_free(c);
}

शून्य av_hmac_init(AVHMAC *c, स्थिरांक uint8_t *किल्ली, अचिन्हित पूर्णांक keylen)
{
    पूर्णांक i;
    uint8_t block[MAX_BLOCKLEN];
    जर (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, किल्ली, keylen);
        c->final(c->hash, c->किल्ली);
        c->keylen = c->hashlen;
    } अन्यथा {
        स_नकल(c->किल्ली, किल्ली, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    साठी (i = 0; i < c->keylen; i++)
        block[i] = c->किल्ली[i] ^ 0x36;
    साठी (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x36;
    c->update(c->hash, block, c->blocklen);
}

शून्य av_hmac_update(AVHMAC *c, स्थिरांक uint8_t *data, अचिन्हित पूर्णांक len)
{
    c->update(c->hash, data, len);
}

पूर्णांक av_hmac_final(AVHMAC *c, uint8_t *out, अचिन्हित पूर्णांक outlen)
{
    uint8_t block[MAX_BLOCKLEN];
    पूर्णांक i;
    जर (outlen < c->hashlen)
        परत AVERROR(EINVAL);
    c->final(c->hash, out);
    c->init(c->hash);
    साठी (i = 0; i < c->keylen; i++)
        block[i] = c->किल्ली[i] ^ 0x5C;
    साठी (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x5C;
    c->update(c->hash, block, c->blocklen);
    c->update(c->hash, out, c->hashlen);
    c->final(c->hash, out);
    परत c->hashlen;
}

पूर्णांक av_hmac_calc(AVHMAC *c, स्थिरांक uint8_t *data, अचिन्हित पूर्णांक len,
                 स्थिरांक uint8_t *किल्ली, अचिन्हित पूर्णांक keylen,
                 uint8_t *out, अचिन्हित पूर्णांक outlen)
{
    av_hmac_init(c, किल्ली, keylen);
    av_hmac_update(c, data, len);
    परत av_hmac_final(c, out, outlen);
}
