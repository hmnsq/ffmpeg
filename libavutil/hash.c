/*
 * Copyright (C) 2013 Reimar Döffinger <Reimar.Doeffinger@gmx.de>
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

#ਅਨ੍ਤਰ੍ਭਾਵ <assert.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "hash.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "adler32.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "crc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "md5.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "murmur3.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "ripemd.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "sha.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "sha512.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "base64.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

// ENTRY(HASH_TYPE, HASH_NAME, HASH_SIZE)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HASHES(ਇੰਦਰਾਜ_2)                   \
    ਇੰਦਰਾਜ_2(MD5,        "MD5",        16) \
    ਇੰਦਰਾਜ_2(MURMUR3,    "murmur3",    16) \
    ਇੰਦਰਾਜ_2(RIPEMD128,  "RIPEMD128",  16) \
    ਇੰਦਰਾਜ_2(RIPEMD160,  "RIPEMD160",  20) \
    ਇੰਦਰਾਜ_2(RIPEMD256,  "RIPEMD256",  32) \
    ਇੰਦਰਾਜ_2(RIPEMD320,  "RIPEMD320",  40) \
    ਇੰਦਰਾਜ_2(SHA160,     "SHA160",     20) \
    ਇੰਦਰਾਜ_2(SHA224,     "SHA224",     28) \
    ਇੰਦਰਾਜ_2(SHA256,     "SHA256",     32) \
    ਇੰਦਰਾਜ_2(SHA512_224, "SHA512/224", 28) \
    ਇੰਦਰਾਜ_2(SHA512_256, "SHA512/256", 32) \
    ਇੰਦਰਾਜ_2(SHA384,     "SHA384",     48) \
    ਇੰਦਰਾਜ_2(SHA512,     "SHA512",     64) \
    ਇੰਦਰਾਜ_2(ਚੱਕਰੀ_ਜਾਂਚ_32,      "CRC32",       4) \
    ਇੰਦਰਾਜ_2(ADLER32,    "adler32",     4) \

ਗਿਣਤੀ hashtype {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HASH_TYPE(TYPE, NAME, ਮਾਪ_2) TYPE,
    HASHES(HASH_TYPE)
    ਅੰਕ_HASHES
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVHashContext {
    ਖਾਲੀ *ctx;
    ਗਿਣਤੀ hashtype type;
    ਅਚਲ AVCRC *crctab;
    uint32_t ਚੱਕਰੀ_ਜਾਂਚ;
} AVHashContext;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HASH_MAX_ਮਾਪ(TYPE, NAME, ਮਾਪ_2) \
    HASH_MAX_ਮਾਪ_BEFORE ## TYPE,      \
    HASH_MAX_ਮਾਪ_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(ਮਾਪ_2, HASH_MAX_ਮਾਪ_BEFORE ## TYPE) - 1,
ਗਿਣਤੀ {
    HASHES(HASH_MAX_ਮਾਪ)
    MAX_HASH_ਮਾਪ
};
static_assert(AV_HASH_MAX_ਮਾਪ >= MAX_HASH_ਮਾਪ, "AV_HASH_MAX_SIZE needs to be updated!");

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HASH_MAX_NAME_ਮਾਪ(TYPE, NAME, ਮਾਪ_2) \
    HASH_MAX_NAME_ਮਾਪ_BEFORE ## TYPE,      \
    HASH_MAX_NAME_ਮਾਪ_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(ਆਕਾਰ(NAME), HASH_MAX_NAME_ਮਾਪ_BEFORE ## TYPE) - 1,
ਗਿਣਤੀ {
    HASHES(HASH_MAX_NAME_ਮਾਪ)
    MAX_HASH_NAME_ਮਾਪ
};

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    ਅਚਲ ਅੱਖਰ name[MAX_HASH_NAME_ਮਾਪ];
    ਪੂਰਨ ਮਾਪ;
} hashdesc[] = {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HASH_DESC(TYPE, NAME, ਮਾਪ_2) [TYPE] = { NAME, ਮਾਪ_2 },
    HASHES(HASH_DESC)
};

ਅਚਲ ਅੱਖਰ *av_hash_ਨਾਂ(ਪੂਰਨ i)
{
    ਜੇ (i < 0 || i >= ਅੰਕ_HASHES) ਵਾਪਸ ਨਿਰਾ;
    ਵਾਪਸ hashdesc[i].name;
}

ਅਚਲ ਅੱਖਰ *av_hash_get_name(ਅਚਲ AVHashContext *ctx)
{
    ਵਾਪਸ hashdesc[ctx->type].name;
}

ਪੂਰਨ av_hash_get_ਮਾਪ(ਅਚਲ AVHashContext *ctx)
{
    ਵਾਪਸ hashdesc[ctx->type].ਮਾਪ;
}

ਪੂਰਨ av_hash_alloc(AVHashContext **ctx, ਅਚਲ ਅੱਖਰ *name)
{
    AVHashContext *res;
    ਪੂਰਨ i;
    *ctx = ਨਿਰਾ;
    ਲਈ (i = 0; i < ਅੰਕ_HASHES; i++)
        ਜੇ (av_strcasecmp(name, hashdesc[i].name) == 0)
            ਰੋਕੋ;
    ਜੇ (i >= ਅੰਕ_HASHES) ਵਾਪਸ AVERROR(EINVAL);
    res = av_mallocz(ਆਕਾਰ(*res));
    ਜੇ (!res) ਵਾਪਸ AVERROR(ENOMEM);
    res->type = i;
    ਚੋਣ (i) {
    ਹਾਲਤ MD5:     res->ctx = av_md5_alloc(); ਰੋਕੋ;
    ਹਾਲਤ MURMUR3: res->ctx = av_murmur3_alloc(); ਰੋਕੋ;
    ਹਾਲਤ RIPEMD128:
    ਹਾਲਤ RIPEMD160:
    ਹਾਲਤ RIPEMD256:
    ਹਾਲਤ RIPEMD320: res->ctx = av_ripemd_alloc(); ਰੋਕੋ;
    ਹਾਲਤ SHA160:
    ਹਾਲਤ SHA224:
    ਹਾਲਤ SHA256:  res->ctx = av_sha_alloc(); ਰੋਕੋ;
    ਹਾਲਤ SHA512_224:
    ਹਾਲਤ SHA512_256:
    ਹਾਲਤ SHA384:
    ਹਾਲਤ SHA512:  res->ctx = av_sha512_alloc(); ਰੋਕੋ;
    ਹਾਲਤ ਚੱਕਰੀ_ਜਾਂਚ_32:   res->crctab = av_ਚੱਕਰੀ_ਜਾਂਚ_get_ਸਾਰਣੀ(AV_ਚੱਕਰੀ_ਜਾਂਚ_32_IEEE_LE); ਰੋਕੋ;
    ਹਾਲਤ ADLER32: ਰੋਕੋ;
    }
    ਜੇ (i != ADLER32 && i != ਚੱਕਰੀ_ਜਾਂਚ_32 && !res->ctx) {
        av_free(res);
        ਵਾਪਸ AVERROR(ENOMEM);
    }
    *ctx = res;
    ਵਾਪਸ 0;
}

ਖਾਲੀ av_hash_init(AVHashContext *ctx)
{
    ਚੋਣ (ctx->type) {
    ਹਾਲਤ MD5:     av_md5_init(ctx->ctx); ਰੋਕੋ;
    ਹਾਲਤ MURMUR3: av_murmur3_init(ctx->ctx); ਰੋਕੋ;
    ਹਾਲਤ RIPEMD128: av_ripemd_init(ctx->ctx, 128); ਰੋਕੋ;
    ਹਾਲਤ RIPEMD160: av_ripemd_init(ctx->ctx, 160); ਰੋਕੋ;
    ਹਾਲਤ RIPEMD256: av_ripemd_init(ctx->ctx, 256); ਰੋਕੋ;
    ਹਾਲਤ RIPEMD320: av_ripemd_init(ctx->ctx, 320); ਰੋਕੋ;
    ਹਾਲਤ SHA160:  av_sha_init(ctx->ctx, 160); ਰੋਕੋ;
    ਹਾਲਤ SHA224:  av_sha_init(ctx->ctx, 224); ਰੋਕੋ;
    ਹਾਲਤ SHA256:  av_sha_init(ctx->ctx, 256); ਰੋਕੋ;
    ਹਾਲਤ SHA512_224:  av_sha512_init(ctx->ctx, 224); ਰੋਕੋ;
    ਹਾਲਤ SHA512_256:  av_sha512_init(ctx->ctx, 256); ਰੋਕੋ;
    ਹਾਲਤ SHA384:  av_sha512_init(ctx->ctx, 384); ਰੋਕੋ;
    ਹਾਲਤ SHA512:  av_sha512_init(ctx->ctx, 512); ਰੋਕੋ;
    ਹਾਲਤ ਚੱਕਰੀ_ਜਾਂਚ_32:   ctx->ਚੱਕਰੀ_ਜਾਂਚ = UINT32_MAX; ਰੋਕੋ;
    ਹਾਲਤ ADLER32: ctx->ਚੱਕਰੀ_ਜਾਂਚ = 1; ਰੋਕੋ;
    }
}

ਖਾਲੀ av_hash_update(AVHashContext *ctx, ਅਚਲ uint8_t *src, size_t len)
{
    ਚੋਣ (ctx->type) {
    ਹਾਲਤ MD5:     av_md5_update(ctx->ctx, src, len); ਰੋਕੋ;
    ਹਾਲਤ MURMUR3: av_murmur3_update(ctx->ctx, src, len); ਰੋਕੋ;
    ਹਾਲਤ RIPEMD128:
    ਹਾਲਤ RIPEMD160:
    ਹਾਲਤ RIPEMD256:
    ਹਾਲਤ RIPEMD320: av_ripemd_update(ctx->ctx, src, len); ਰੋਕੋ;
    ਹਾਲਤ SHA160:
    ਹਾਲਤ SHA224:
    ਹਾਲਤ SHA256:  av_sha_update(ctx->ctx, src, len); ਰੋਕੋ;
    ਹਾਲਤ SHA512_224:
    ਹਾਲਤ SHA512_256:
    ਹਾਲਤ SHA384:
    ਹਾਲਤ SHA512:  av_sha512_update(ctx->ctx, src, len); ਰੋਕੋ;
    ਹਾਲਤ ਚੱਕਰੀ_ਜਾਂਚ_32:   ctx->ਚੱਕਰੀ_ਜਾਂਚ = av_ਚੱਕਰੀ_ਜਾਂਚ(ctx->crctab, ctx->ਚੱਕਰੀ_ਜਾਂਚ, src, len); ਰੋਕੋ;
    ਹਾਲਤ ADLER32: ctx->ਚੱਕਰੀ_ਜਾਂਚ = av_adler32_update(ctx->ਚੱਕਰੀ_ਜਾਂਚ, src, len); ਰੋਕੋ;
    }
}

ਖਾਲੀ av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    ਚੋਣ (ctx->type) {
    ਹਾਲਤ MD5:     av_md5_final(ctx->ctx, dst); ਰੋਕੋ;
    ਹਾਲਤ MURMUR3: av_murmur3_final(ctx->ctx, dst); ਰੋਕੋ;
    ਹਾਲਤ RIPEMD128:
    ਹਾਲਤ RIPEMD160:
    ਹਾਲਤ RIPEMD256:
    ਹਾਲਤ RIPEMD320: av_ripemd_final(ctx->ctx, dst); ਰੋਕੋ;
    ਹਾਲਤ SHA160:
    ਹਾਲਤ SHA224:
    ਹਾਲਤ SHA256:  av_sha_final(ctx->ctx, dst); ਰੋਕੋ;
    ਹਾਲਤ SHA512_224:
    ਹਾਲਤ SHA512_256:
    ਹਾਲਤ SHA384:
    ਹਾਲਤ SHA512:  av_sha512_final(ctx->ctx, dst); ਰੋਕੋ;
    ਹਾਲਤ ਚੱਕਰੀ_ਜਾਂਚ_32:   AV_WB32(dst, ctx->ਚੱਕਰੀ_ਜਾਂਚ ^ UINT32_MAX); ਰੋਕੋ;
    ਹਾਲਤ ADLER32: AV_WB32(dst, ctx->ਚੱਕਰੀ_ਜਾਂਚ); ਰੋਕੋ;
    }
}

ਖਾਲੀ av_hash_final_bin(ਬਣਤਰ AVHashContext *ctx, uint8_t *dst, ਪੂਰਨ ਮਾਪ)
{
    uint8_t buf[AV_HASH_MAX_ਮਾਪ];
    ਬਿਨਾਨਿਸ਼ਾਨੀ rsize = av_hash_get_ਮਾਪ(ctx);

    av_hash_final(ctx, buf);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst, buf, FFMIN(ਮਾਪ, rsize));
    ਜੇ (ਮਾਪ > rsize)
        memset(dst + rsize, 0, ਮਾਪ - rsize);
}

ਖਾਲੀ av_hash_final_hex(ਬਣਤਰ AVHashContext *ctx, uint8_t *dst, ਪੂਰਨ ਮਾਪ)
{
    uint8_t buf[AV_HASH_MAX_ਮਾਪ];
    ਬਿਨਾਨਿਸ਼ਾਨੀ rsize = av_hash_get_ਮਾਪ(ctx), i;

    av_hash_final(ctx, buf);
    ਲਈ (i = 0; i < FFMIN(rsize, ਮਾਪ / 2); i++)
        snprintf(dst + i * 2, ਮਾਪ - i * 2, "%02x", buf[i]);
}

ਖਾਲੀ av_hash_final_b64(ਬਣਤਰ AVHashContext *ctx, uint8_t *dst, ਪੂਰਨ ਮਾਪ)
{
    uint8_t buf[AV_HASH_MAX_ਮਾਪ], b64[AV_BASE64_ਮਾਪ(AV_HASH_MAX_ਮਾਪ)];
    ਬਿਨਾਨਿਸ਼ਾਨੀ rsize = av_hash_get_ਮਾਪ(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, ਆਕਾਰ(b64), buf, rsize);
    osize = AV_BASE64_ਮਾਪ(rsize);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst, b64, FFMIN(osize, ਮਾਪ));
    ਜੇ (ਮਾਪ < osize)
        dst[ਮਾਪ - 1] = 0;
}

ਖਾਲੀ av_hash_freep(AVHashContext **ctx)
{
    ਜੇ (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
