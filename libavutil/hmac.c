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

#ವ್ಯಾಖ್ಯಾನಿಸು MAX_HASHLEN 64
#ವ್ಯಾಖ್ಯಾನಿಸು MAX_BLOCKLEN 128

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*hmac_final)(ಶೂನ್ಯ *ctx, uint8_t *dst);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*hmac_update)(ಶೂನ್ಯ *ctx, ಸ್ಥಿರಾಂಕ uint8_t *src, size_t len);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*hmac_init)(ಶೂನ್ಯ *ctx);

ರಚನೆ AVHMAC {
    ಶೂನ್ಯ *hash;
    ಪೂರ್ಣಾಂಕ blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t ಕೀಲಿ[MAX_BLOCKLEN];
    ಪೂರ್ಣಾಂಕ keylen;
};

#ವ್ಯಾಖ್ಯಾನಿಸು DEFINE_ALGO_ಬಿಟ್ಟುಗಳು_INIT(ಪೂರ್ವಪ್ರತ್ಯಯ, ಬಿಟ್ಟುಗಳು)        \
ಸ್ಥಿರ av_cold ಶೂನ್ಯ ಪೂರ್ವಪ್ರತ್ಯಯ##bits##_init(ಶೂನ್ಯ *ctx) \
{                                                  \
    av_##prefix##_init(ctx, ಬಿಟ್ಟುಗಳು);                 \
}

#ವ್ಯಾಖ್ಯಾನಿಸು DEFINE_ALGO_INIT(ಪೂರ್ವಪ್ರತ್ಯಯ)             \
ಸ್ಥಿರ av_cold ಶೂನ್ಯ ಪೂರ್ವಪ್ರತ್ಯಯ##_init(ಶೂನ್ಯ *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#ವ್ಯಾಖ್ಯಾನಿಸು DEFINE_ALGO(ಪೂರ್ವಪ್ರತ್ಯಯ)                                            \
ಸ್ಥಿರ ಶೂನ್ಯ ಪೂರ್ವಪ್ರತ್ಯಯ##_update(ಶೂನ್ಯ *ctx, ಸ್ಥಿರಾಂಕ uint8_t *src, size_t len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
ಸ್ಥಿರ ಶೂನ್ಯ ಪೂರ್ವಪ್ರತ್ಯಯ##_final(ಶೂನ್ಯ *ctx, uint8_t *dst)                    \
{                                                                      \
    av_##prefix##_final(ctx, dst);                                     \
}

DEFINE_ALGO_INIT(md5)
DEFINE_ALGO_ಬಿಟ್ಟುಗಳು_INIT(sha, 160)
DEFINE_ALGO_ಬಿಟ್ಟುಗಳು_INIT(sha, 224)
DEFINE_ALGO_ಬಿಟ್ಟುಗಳು_INIT(sha, 256)
DEFINE_ALGO_ಬಿಟ್ಟುಗಳು_INIT(sha512, 384)
DEFINE_ALGO_ಬಿಟ್ಟುಗಳು_INIT(sha512, 512)
DEFINE_ALGO(md5)
DEFINE_ALGO(sha)
DEFINE_ALGO(sha512)

AVHMAC *av_hmac_alloc(ಎಣಿಕೆ AVHMACType type)
{
    AVHMAC *c = av_mallocz(ಗಾತ್ರ(*c));
    ಆದರೆ (!c)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಆಯ್ಕೆ (type) {
    ಸ್ಥಿತಿ AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        av_free(c);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಆದರೆ (!c->hash) {
        av_free(c);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ c;
}

ಶೂನ್ಯ av_hmac_free(AVHMAC *c)
{
    ಆದರೆ (!c)
        ಹಿಂತಿರುಗಿ;
    av_freep(&c->hash);
    av_free(c);
}

ಶೂನ್ಯ av_hmac_init(AVHMAC *c, ಸ್ಥಿರಾಂಕ uint8_t *ಕೀಲಿ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ keylen)
{
    ಪೂರ್ಣಾಂಕ i;
    uint8_t ಖಂಡ[MAX_BLOCKLEN];
    ಆದರೆ (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, ಕೀಲಿ, keylen);
        c->final(c->hash, c->ಕೀಲಿ);
        c->keylen = c->hashlen;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಸ್ಮರಣೆ_ನಕಲು(c->ಕೀಲಿ, ಕೀಲಿ, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    ಗಾಗಿ (i = 0; i < c->keylen; i++)
        ಖಂಡ[i] = c->ಕೀಲಿ[i] ^ 0x36;
    ಗಾಗಿ (i = c->keylen; i < c->blocklen; i++)
        ಖಂಡ[i] = 0x36;
    c->update(c->hash, ಖಂಡ, c->blocklen);
}

ಶೂನ್ಯ av_hmac_update(AVHMAC *c, ಸ್ಥಿರಾಂಕ uint8_t *ದತ್ತಾಂಶ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ len)
{
    c->update(c->hash, ದತ್ತಾಂಶ, len);
}

ಪೂರ್ಣಾಂಕ av_hmac_final(AVHMAC *c, uint8_t *ಹೊರಹೋಗು, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ outlen)
{
    uint8_t ಖಂಡ[MAX_BLOCKLEN];
    ಪೂರ್ಣಾಂಕ i;
    ಆದರೆ (outlen < c->hashlen)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    c->final(c->hash, ಹೊರಹೋಗು);
    c->init(c->hash);
    ಗಾಗಿ (i = 0; i < c->keylen; i++)
        ಖಂಡ[i] = c->ಕೀಲಿ[i] ^ 0x5C;
    ಗಾಗಿ (i = c->keylen; i < c->blocklen; i++)
        ಖಂಡ[i] = 0x5C;
    c->update(c->hash, ಖಂಡ, c->blocklen);
    c->update(c->hash, ಹೊರಹೋಗು, c->hashlen);
    c->final(c->hash, ಹೊರಹೋಗು);
    ಹಿಂತಿರುಗಿ c->hashlen;
}

ಪೂರ್ಣಾಂಕ av_hmac_calc(AVHMAC *c, ಸ್ಥಿರಾಂಕ uint8_t *ದತ್ತಾಂಶ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ len,
                 ಸ್ಥಿರಾಂಕ uint8_t *ಕೀಲಿ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ keylen,
                 uint8_t *ಹೊರಹೋಗು, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ outlen)
{
    av_hmac_init(c, ಕೀಲಿ, keylen);
    av_hmac_update(c, ದತ್ತಾಂಶ, len);
    ಹಿಂತಿರುಗಿ av_hmac_final(c, ಹೊರಹೋಗು, outlen);
}
