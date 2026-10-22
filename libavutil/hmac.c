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

#અન્તર્ભાવ <stddef.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "attributes.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "hmac.h"
#અન્તર્ભાવ "md5.h"
#અન્તર્ભાવ "sha.h"
#અન્તર્ભાવ "sha512.h"
#અન્તર્ભાવ "mem.h"

#define MAX_HASHLEN 64
#define MAX_BLOCKLEN 128

પ્રકારવ્યાખ્યા શૂન્ય (*hmac_final)(શૂન્ય *ctx, uint8_t *dst);
પ્રકારવ્યાખ્યા શૂન્ય (*hmac_update)(શૂન્ય *ctx, અચલ uint8_t *src, size_t len);
પ્રકારવ્યાખ્યા શૂન્ય (*hmac_init)(શૂન્ય *ctx);

સંરચના AVHMAC {
    શૂન્ય *hash;
    પૂર્ણાંક blocklen, hashlen;
    hmac_final  final;
    hmac_update update;
    hmac_init   init;
    uint8_t ચાવી[MAX_BLOCKLEN];
    પૂર્ણાંક keylen;
};

#define DEFINE_ALGO_BITS_INIT(prefix, bits)        \
સ્થિર av_cold શૂન્ય prefix##bits##_init(શૂન્ય *ctx) \
{                                                  \
    av_##prefix##_init(ctx, bits);                 \
}

#define DEFINE_ALGO_INIT(prefix)             \
સ્થિર av_cold શૂન્ય prefix##_init(શૂન્ય *ctx) \
{                                            \
    av_##prefix##_init(ctx);                 \
}

#define DEFINE_ALGO(prefix)                                            \
સ્થિર શૂન્ય prefix##_update(શૂન્ય *ctx, અચલ uint8_t *src, size_t len) \
{                                                                      \
    av_##prefix##_update(ctx, src, len);                               \
}                                                                      \
સ્થિર શૂન્ય prefix##_final(શૂન્ય *ctx, uint8_t *dst)                    \
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

AVHMAC *av_hmac_alloc(ગણના AVHMACType type)
{
    AVHMAC *c = av_mallocz(કદ(*c));
    જો (!c)
        પાછા ખાલી;
    પસંદગી (type) {
    સ્થિતિ AV_HMAC_MD5:
        c->blocklen = 64;
        c->hashlen  = 16;
        c->init     = md5_init;
        c->update   = md5_update;
        c->final    = md5_final;
        c->hash     = av_md5_alloc();
        તોડો;
    સ્થિતિ AV_HMAC_SHA1:
        c->blocklen = 64;
        c->hashlen  = 20;
        c->init     = sha160_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        તોડો;
    સ્થિતિ AV_HMAC_SHA224:
        c->blocklen = 64;
        c->hashlen  = 28;
        c->init     = sha224_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        તોડો;
    સ્થિતિ AV_HMAC_SHA256:
        c->blocklen = 64;
        c->hashlen  = 32;
        c->init     = sha256_init;
        c->update   = sha_update;
        c->final    = sha_final;
        c->hash     = av_sha_alloc();
        તોડો;
    સ્થિતિ AV_HMAC_SHA384:
        c->blocklen = 128;
        c->hashlen  = 48;
        c->init     = sha512384_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        તોડો;
    સ્થિતિ AV_HMAC_SHA512:
        c->blocklen = 128;
        c->hashlen  = 64;
        c->init     = sha512512_init;
        c->update   = sha512_update;
        c->final    = sha512_final;
        c->hash     = av_sha512_alloc();
        તોડો;
    મૂળભૂત:
        av_free(c);
        પાછા ખાલી;
    }
    જો (!c->hash) {
        av_free(c);
        પાછા ખાલી;
    }
    પાછા c;
}

શૂન્ય av_hmac_free(AVHMAC *c)
{
    જો (!c)
        પાછા;
    av_freep(&c->hash);
    av_free(c);
}

શૂન્ય av_hmac_init(AVHMAC *c, અચલ uint8_t *ચાવી, unsigned પૂર્ણાંક keylen)
{
    પૂર્ણાંક i;
    uint8_t block[MAX_BLOCKLEN];
    જો (keylen > c->blocklen) {
        c->init(c->hash);
        c->update(c->hash, ચાવી, keylen);
        c->final(c->hash, c->ચાવી);
        c->keylen = c->hashlen;
    } નહીંતર {
        memcpy(c->ચાવી, ચાવી, keylen);
        c->keylen = keylen;
    }
    c->init(c->hash);
    માટે (i = 0; i < c->keylen; i++)
        block[i] = c->ચાવી[i] ^ 0x36;
    માટે (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x36;
    c->update(c->hash, block, c->blocklen);
}

શૂન્ય av_hmac_update(AVHMAC *c, અચલ uint8_t *data, unsigned પૂર્ણાંક len)
{
    c->update(c->hash, data, len);
}

પૂર્ણાંક av_hmac_final(AVHMAC *c, uint8_t *out, unsigned પૂર્ણાંક outlen)
{
    uint8_t block[MAX_BLOCKLEN];
    પૂર્ણાંક i;
    જો (outlen < c->hashlen)
        પાછા AVERROR(EINVAL);
    c->final(c->hash, out);
    c->init(c->hash);
    માટે (i = 0; i < c->keylen; i++)
        block[i] = c->ચાવી[i] ^ 0x5C;
    માટે (i = c->keylen; i < c->blocklen; i++)
        block[i] = 0x5C;
    c->update(c->hash, block, c->blocklen);
    c->update(c->hash, out, c->hashlen);
    c->final(c->hash, out);
    પાછા c->hashlen;
}

પૂર્ણાંક av_hmac_calc(AVHMAC *c, અચલ uint8_t *data, unsigned પૂર્ણાંક len,
                 અચલ uint8_t *ચાવી, unsigned પૂર્ણાંક keylen,
                 uint8_t *out, unsigned પૂર્ણાંક outlen)
{
    av_hmac_init(c, ચાવી, keylen);
    av_hmac_update(c, data, len);
    પાછા av_hmac_final(c, out, outlen);
}
