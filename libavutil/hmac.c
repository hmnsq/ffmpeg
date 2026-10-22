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

#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "attributes.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "hmac.h"
#അന്തര്ഭാവ "md5.h"
#അന്തര്ഭാവ "sha.h"
#അന്തര്ഭാവ "sha512.h"
#അന്തര്ഭാവ "mem.h"

#define MAX_HASHLEN 64
#define MAX_BLOCKLEN 128

തരനിർവചനം ശൂന്യം (*hmac_final)(ശൂന്യം *ctx, uint8_t *dst);
തരനിർവചനം ശൂന്യം (*hmac_update)(ശൂന്യം *ctx, സ്ഥിരം uint8_t *src, size_t len);
തരനിർവചനം ശൂന്യം (*hmac_init)(ശൂന്യം *ctx);

ഘടന AVHMAC {
    ശൂന്യം *hash;
    പൂർണ്ണസംഖ്യ blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t താക്കോൽ[MAX_BLOCKLEN];
    പൂർണ്ണസംഖ്യ keylen;
};

#define DEFINE_ALGO_BITS_INIT(prefix, bits)        \
സ്ഥിതം av_cold ശൂന്യം prefix##bits##_init(ശൂന്യം *ctx) \
{                                                  \
    av_##prefix##_init(ctx, bits);                 \
}

#define DEFINE_ALGO_INIT(prefix)             \
സ്ഥിതം av_cold ശൂന്യം prefix##_init(ശൂന്യം *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#define DEFINE_ALGO(prefix)                                            \
സ്ഥിതം ശൂന്യം prefix##_update(ശൂന്യം *ctx, സ്ഥിരം uint8_t *src, size_t len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
സ്ഥിതം ശൂന്യം prefix##_final(ശൂന്യം *ctx, uint8_t *dst)                    \
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

AVHMAC *av_hmac_alloc(എണ്ണൽ AVHMACType type)
{
    AVHMAC *c = av_mallocz(വലുപ്പം(*c));
    എങ്കിൽ (!c)
        തിരികെ ശൂന്യ;
    തിരഞ്ഞെടുപ്പ് (type) {
    അവസ്ഥ AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        നിർത്തുക;
    അവസ്ഥ AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        നിർത്തുക;
    അവസ്ഥ AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        നിർത്തുക;
    അവസ്ഥ AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        നിർത്തുക;
    അവസ്ഥ AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        നിർത്തുക;
    അവസ്ഥ AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        av_free(c);
        തിരികെ ശൂന്യ;
    }
    എങ്കിൽ (!c->hash) {
        av_free(c);
        തിരികെ ശൂന്യ;
    }
    തിരികെ c;
}

ശൂന്യം av_hmac_free(AVHMAC *c)
{
    എങ്കിൽ (!c)
        തിരികെ;
    av_freep(&c->hash);
    av_free(c);
}

ശൂന്യം av_hmac_init(AVHMAC *c, സ്ഥിരം uint8_t *താക്കോൽ, unsigned പൂർണ്ണസംഖ്യ keylen)
{
    പൂർണ്ണസംഖ്യ i;
    uint8_t block[MAX_BLOCKLEN];
    എങ്കിൽ (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, താക്കോൽ, keylen);
        c->final(c->hash, c->താക്കോൽ);
        c->keylen = c->hashlen;
    } അല്ലെങ്കിൽ {
        memcpy(c->താക്കോൽ, താക്കോൽ, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    വേണ്ടി (i = 0; i < c->keylen; i++)
        block[i] = c->താക്കോൽ[i] ^ 0x36;
    വേണ്ടി (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x36;
    c->update(c->hash, block, c->blocklen);
}

ശൂന്യം av_hmac_update(AVHMAC *c, സ്ഥിരം uint8_t *data, unsigned പൂർണ്ണസംഖ്യ len)
{
    c->update(c->hash, data, len);
}

പൂർണ്ണസംഖ്യ av_hmac_final(AVHMAC *c, uint8_t *out, unsigned പൂർണ്ണസംഖ്യ outlen)
{
    uint8_t block[MAX_BLOCKLEN];
    പൂർണ്ണസംഖ്യ i;
    എങ്കിൽ (outlen < c->hashlen)
        തിരികെ AVERROR(EINVAL);
    c->final(c->hash, out);
    c->init(c->hash);
    വേണ്ടി (i = 0; i < c->keylen; i++)
        block[i] = c->താക്കോൽ[i] ^ 0x5C;
    വേണ്ടി (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x5C;
    c->update(c->hash, block, c->blocklen);
    c->update(c->hash, out, c->hashlen);
    c->final(c->hash, out);
    തിരികെ c->hashlen;
}

പൂർണ്ണസംഖ്യ av_hmac_calc(AVHMAC *c, സ്ഥിരം uint8_t *data, unsigned പൂർണ്ണസംഖ്യ len,
                 സ്ഥിരം uint8_t *താക്കോൽ, unsigned പൂർണ്ണസംഖ്യ keylen,
                 uint8_t *out, unsigned പൂർണ്ണസംഖ്യ outlen)
{
    av_hmac_init(c, താക്കോൽ, keylen);
    av_hmac_update(c, data, len);
    തിരികെ av_hmac_final(c, out, outlen);
}
