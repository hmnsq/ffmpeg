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

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "hmac.h"
#ಅನ್ತರ್ಭಾವ "md5.h"
#ಅನ್ತರ್ಭಾವ "sha.h"
#ಅನ್ತರ್ಭಾವ "sha512.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

#define MAX_HASHLEN 64
#define MAX_BLOCKLEN 128

ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (*hmac_final)(ಶೂನ್ಯ *ctx, uint8_t *dst);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (*hmac_update)(ಶೂನ್ಯ *ctx, ಧ್ರುವ uint8_t *src, size_t len);
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (*hmac_init)(ಶೂನ್ಯ *ctx);

ಸಂರಚನಾ AVHMAC {
    ಶೂನ್ಯ *hash;
    ಪೂರ್ಣಾಙ್ಕ blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t ಕೀಲಿ[MAX_BLOCKLEN];
    ಪೂರ್ಣಾಙ್ಕ keylen;
};

#define DEFINE_ALGO_BITS_INIT(prefix, bits)        \
ಸ್ಥಿರ av_cold ಶೂನ್ಯ prefix##bits##_init(ಶೂನ್ಯ *ctx) \
{                                                  \
    av_##prefix##_init(ctx, bits);                 \
}

#define DEFINE_ALGO_INIT(prefix)             \
ಸ್ಥಿರ av_cold ಶೂನ್ಯ prefix##_init(ಶೂನ್ಯ *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#define DEFINE_ALGO(prefix)                                            \
ಸ್ಥಿರ ಶೂನ್ಯ prefix##_update(ಶೂನ್ಯ *ctx, ಧ್ರುವ uint8_t *src, size_t len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
ಸ್ಥಿರ ಶೂನ್ಯ prefix##_final(ಶೂನ್ಯ *ctx, uint8_t *dst)                    \
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

AVHMAC *av_hmac_alloc(ಗಣನಾ AVHMACType type)
{
    AVHMAC *c = av_mallocz(ಪರಿಮಾಣ(*c));
    ಯದಿ (!c)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ವಿಕಲ್ಪ (type) {
    ಪಕ್ಷ AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        ಭಙ್ಗ;
    ಸ್ವಭಾವ:
        av_free(c);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಯದಿ (!c->hash) {
        av_free(c);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ c;
}

ಶೂನ್ಯ av_hmac_free(AVHMAC *c)
{
    ಯದಿ (!c)
        ಪ್ರತ್ಯಾಗಮ;
    av_freep(&c->hash);
    av_free(c);
}

ಶೂನ್ಯ av_hmac_init(AVHMAC *c, ಧ್ರುವ uint8_t *ಕೀಲಿ, unsigned ಪೂರ್ಣಾಙ್ಕ keylen)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    uint8_t block[MAX_BLOCKLEN];
    ಯದಿ (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, ಕೀಲಿ, keylen);
        c->final(c->hash, c->ಕೀಲಿ);
        c->keylen = c->hashlen;
    } ಅನ್ಯಥಾ {
        memcpy(c->ಕೀಲಿ, ಕೀಲಿ, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    ಪ್ರತಿ (i = 0; i < c->keylen; i++)
        block[i] = c->ಕೀಲಿ[i] ^ 0x36;
    ಪ್ರತಿ (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x36;
    c->update(c->hash, block, c->blocklen);
}

ಶೂನ್ಯ av_hmac_update(AVHMAC *c, ಧ್ರುವ uint8_t *data, unsigned ಪೂರ್ಣಾಙ್ಕ len)
{
    c->update(c->hash, data, len);
}

ಪೂರ್ಣಾಙ್ಕ av_hmac_final(AVHMAC *c, uint8_t *out, unsigned ಪೂರ್ಣಾಙ್ಕ outlen)
{
    uint8_t block[MAX_BLOCKLEN];
    ಪೂರ್ಣಾಙ್ಕ i;
    ಯದಿ (outlen < c->hashlen)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    c->final(c->hash, out);
    c->init(c->hash);
    ಪ್ರತಿ (i = 0; i < c->keylen; i++)
        block[i] = c->ಕೀಲಿ[i] ^ 0x5C;
    ಪ್ರತಿ (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x5C;
    c->update(c->hash, block, c->blocklen);
    c->update(c->hash, out, c->hashlen);
    c->final(c->hash, out);
    ಪ್ರತ್ಯಾಗಮ c->hashlen;
}

ಪೂರ್ಣಾಙ್ಕ av_hmac_calc(AVHMAC *c, ಧ್ರುವ uint8_t *data, unsigned ಪೂರ್ಣಾಙ್ಕ len,
                 ಧ್ರುವ uint8_t *ಕೀಲಿ, unsigned ಪೂರ್ಣಾಙ್ಕ keylen,
                 uint8_t *out, unsigned ಪೂರ್ಣಾಙ್ಕ outlen)
{
    av_hmac_init(c, ಕೀಲಿ, keylen);
    av_hmac_update(c, data, len);
    ಪ್ರತ್ಯಾಗಮ av_hmac_final(c, out, outlen);
}
