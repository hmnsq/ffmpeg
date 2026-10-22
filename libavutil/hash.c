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

#ಅನ್ತರ್ಭಾವ <assert.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ "hash.h"

#ಅನ್ತರ್ಭಾವ "adler32.h"
#ಅನ್ತರ್ಭಾವ "crc.h"
#ಅನ್ತರ್ಭಾವ "md5.h"
#ಅನ್ತರ್ಭಾವ "murmur3.h"
#ಅನ್ತರ್ಭಾವ "ripemd.h"
#ಅನ್ತರ್ಭಾವ "sha.h"
#ಅನ್ತರ್ಭಾವ "sha512.h"

#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "base64.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

// ENTRY(HASH_TYPE, HASH_NAME, HASH_SIZE)
#ವ್ಯಾಖ್ಯಾನಿಸು HASHES(ನಮೂದು_2)                   \
    ನಮೂದು_2(MD5,        "MD5",        16) \
    ನಮೂದು_2(MURMUR3,    "murmur3",    16) \
    ನಮೂದು_2(RIPEMD128,  "RIPEMD128",  16) \
    ನಮೂದು_2(RIPEMD160,  "RIPEMD160",  20) \
    ನಮೂದು_2(RIPEMD256,  "RIPEMD256",  32) \
    ನಮೂದು_2(RIPEMD320,  "RIPEMD320",  40) \
    ನಮೂದು_2(SHA160,     "SHA160",     20) \
    ನಮೂದು_2(SHA224,     "SHA224",     28) \
    ನಮೂದು_2(SHA256,     "SHA256",     32) \
    ನಮೂದು_2(SHA512_224, "SHA512/224", 28) \
    ನಮೂದು_2(SHA512_256, "SHA512/256", 32) \
    ನಮೂದು_2(SHA384,     "SHA384",     48) \
    ನಮೂದು_2(SHA512,     "SHA512",     64) \
    ನಮೂದು_2(ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32,      "CRC32",       4) \
    ನಮೂದು_2(ADLER32,    "adler32",     4) \

ಎಣಿಕೆ hashtype {
#ವ್ಯಾಖ್ಯಾನಿಸು HASH_TYPE(TYPE, NAME, ಗಾತ್ರ_3) TYPE,
    HASHES(HASH_TYPE)
    ಅಂಕೆ_HASHES
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVHashContext {
    ಶೂನ್ಯ *ctx;
    ಎಣಿಕೆ hashtype type;
    ಸ್ಥಿರಾಂಕ AVCRC *crctab;
    uint32_t ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ;
} AVHashContext;

#ವ್ಯಾಖ್ಯಾನಿಸು HASH_MAX_ಗಾತ್ರ(TYPE, NAME, ಗಾತ್ರ_3) \
    HASH_MAX_ಗಾತ್ರ_BEFORE ## TYPE,      \
    HASH_MAX_ಗಾತ್ರ_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(ಗಾತ್ರ_3, HASH_MAX_ಗಾತ್ರ_BEFORE ## TYPE) - 1,
ಎಣಿಕೆ {
    HASHES(HASH_MAX_ಗಾತ್ರ)
    MAX_HASH_ಗಾತ್ರ
};
static_assert(AV_HASH_MAX_ಗಾತ್ರ >= MAX_HASH_ಗಾತ್ರ, "AV_HASH_MAX_SIZE needs to be updated!");

#ವ್ಯಾಖ್ಯಾನಿಸು HASH_MAX_NAME_ಗಾತ್ರ(TYPE, NAME, ಗಾತ್ರ_3) \
    HASH_MAX_NAME_ಗಾತ್ರ_BEFORE ## TYPE,      \
    HASH_MAX_NAME_ಗಾತ್ರ_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(ಗಾತ್ರ(NAME), HASH_MAX_NAME_ಗಾತ್ರ_BEFORE ## TYPE) - 1,
ಎಣಿಕೆ {
    HASHES(HASH_MAX_NAME_ಗಾತ್ರ)
    MAX_HASH_NAME_ಗಾತ್ರ
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ name[MAX_HASH_NAME_ಗಾತ್ರ];
    ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2;
} hashdesc[] = {
#ವ್ಯಾಖ್ಯಾನಿಸು HASH_DESC(TYPE, NAME, ಗಾತ್ರ_3) [TYPE] = { NAME, ಗಾತ್ರ_3 },
    HASHES(HASH_DESC)
};

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_hash_ಹೆಸರುಗಳು(ಪೂರ್ಣಾಂಕ i)
{
    ಆದರೆ (i < 0 || i >= ಅಂಕೆ_HASHES) ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ hashdesc[i].name;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_hash_get_name(ಸ್ಥಿರಾಂಕ AVHashContext *ctx)
{
    ಹಿಂತಿರುಗಿ hashdesc[ctx->type].name;
}

ಪೂರ್ಣಾಂಕ av_hash_get_ಗಾತ್ರ(ಸ್ಥಿರಾಂಕ AVHashContext *ctx)
{
    ಹಿಂತಿರುಗಿ hashdesc[ctx->type].ಗಾತ್ರ_2;
}

ಪೂರ್ಣಾಂಕ av_hash_alloc(AVHashContext **ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    AVHashContext *res;
    ಪೂರ್ಣಾಂಕ i;
    *ctx = ಖಾಲಿ;
    ಗಾಗಿ (i = 0; i < ಅಂಕೆ_HASHES; i++)
        ಆದರೆ (av_strcasecmp(name, hashdesc[i].name) == 0)
            ನಿಲ್ಲಿಸು;
    ಆದರೆ (i >= ಅಂಕೆ_HASHES) ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    res = av_mallocz(ಗಾತ್ರ(*res));
    ಆದರೆ (!res) ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    res->type = i;
    ಆಯ್ಕೆ (i) {
    ಸ್ಥಿತಿ MD5:     res->ctx = av_md5_alloc(); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ MURMUR3: res->ctx = av_murmur3_alloc(); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RIPEMD128:
    ಸ್ಥಿತಿ RIPEMD160:
    ಸ್ಥಿತಿ RIPEMD256:
    ಸ್ಥಿತಿ RIPEMD320: res->ctx = av_ripemd_alloc(); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA160:
    ಸ್ಥಿತಿ SHA224:
    ಸ್ಥಿತಿ SHA256:  res->ctx = av_sha_alloc(); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA512_224:
    ಸ್ಥಿತಿ SHA512_256:
    ಸ್ಥಿತಿ SHA384:
    ಸ್ಥಿತಿ SHA512:  res->ctx = av_sha512_alloc(); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32:   res->crctab = av_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_get_ಕೋಷ್ಟಕ(AV_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_IEEE_LE); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ADLER32: ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (i != ADLER32 && i != ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32 && !res->ctx) {
        av_free(res);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }
    *ctx = res;
    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ av_hash_init(AVHashContext *ctx)
{
    ಆಯ್ಕೆ (ctx->type) {
    ಸ್ಥಿತಿ MD5:     av_md5_init(ctx->ctx); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ MURMUR3: av_murmur3_init(ctx->ctx); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RIPEMD128: av_ripemd_init(ctx->ctx, 128); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RIPEMD160: av_ripemd_init(ctx->ctx, 160); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RIPEMD256: av_ripemd_init(ctx->ctx, 256); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RIPEMD320: av_ripemd_init(ctx->ctx, 320); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA160:  av_sha_init(ctx->ctx, 160); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA224:  av_sha_init(ctx->ctx, 224); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA256:  av_sha_init(ctx->ctx, 256); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA512_224:  av_sha512_init(ctx->ctx, 224); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA512_256:  av_sha512_init(ctx->ctx, 256); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA384:  av_sha512_init(ctx->ctx, 384); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA512:  av_sha512_init(ctx->ctx, 512); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32:   ctx->ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ = UINT32_MAX; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ADLER32: ctx->ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ = 1; ನಿಲ್ಲಿಸು;
    }
}

ಶೂನ್ಯ av_hash_update(AVHashContext *ctx, ಸ್ಥಿರಾಂಕ uint8_t *src, size_t len)
{
    ಆಯ್ಕೆ (ctx->type) {
    ಸ್ಥಿತಿ MD5:     av_md5_update(ctx->ctx, src, len); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ MURMUR3: av_murmur3_update(ctx->ctx, src, len); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RIPEMD128:
    ಸ್ಥಿತಿ RIPEMD160:
    ಸ್ಥಿತಿ RIPEMD256:
    ಸ್ಥಿತಿ RIPEMD320: av_ripemd_update(ctx->ctx, src, len); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA160:
    ಸ್ಥಿತಿ SHA224:
    ಸ್ಥಿತಿ SHA256:  av_sha_update(ctx->ctx, src, len); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA512_224:
    ಸ್ಥಿತಿ SHA512_256:
    ಸ್ಥಿತಿ SHA384:
    ಸ್ಥಿತಿ SHA512:  av_sha512_update(ctx->ctx, src, len); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32:   ctx->ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ = av_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ(ctx->crctab, ctx->ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, src, len); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ADLER32: ctx->ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ = av_adler32_update(ctx->ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, src, len); ನಿಲ್ಲಿಸು;
    }
}

ಶೂನ್ಯ av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    ಆಯ್ಕೆ (ctx->type) {
    ಸ್ಥಿತಿ MD5:     av_md5_final(ctx->ctx, dst); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ MURMUR3: av_murmur3_final(ctx->ctx, dst); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ RIPEMD128:
    ಸ್ಥಿತಿ RIPEMD160:
    ಸ್ಥಿತಿ RIPEMD256:
    ಸ್ಥಿತಿ RIPEMD320: av_ripemd_final(ctx->ctx, dst); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA160:
    ಸ್ಥಿತಿ SHA224:
    ಸ್ಥಿತಿ SHA256:  av_sha_final(ctx->ctx, dst); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SHA512_224:
    ಸ್ಥಿತಿ SHA512_256:
    ಸ್ಥಿತಿ SHA384:
    ಸ್ಥಿತಿ SHA512:  av_sha512_final(ctx->ctx, dst); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32:   AV_WB32(dst, ctx->ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ ^ UINT32_MAX); ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ ADLER32: AV_WB32(dst, ctx->ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ); ನಿಲ್ಲಿಸು;
    }
}

ಶೂನ್ಯ av_hash_final_bin(ರಚನೆ AVHashContext *ctx, uint8_t *dst, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2)
{
    uint8_t buf[AV_HASH_MAX_ಗಾತ್ರ];
    ಚಿಹ್ನೆರಹಿತ rsize = av_hash_get_ಗಾತ್ರ(ctx);

    av_hash_final(ctx, buf);
    ಸ್ಮರಣೆ_ನಕಲು(dst, buf, FFMIN(ಗಾತ್ರ_2, rsize));
    ಆದರೆ (ಗಾತ್ರ_2 > rsize)
        memset(dst + rsize, 0, ಗಾತ್ರ_2 - rsize);
}

ಶೂನ್ಯ av_hash_final_hex(ರಚನೆ AVHashContext *ctx, uint8_t *dst, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2)
{
    uint8_t buf[AV_HASH_MAX_ಗಾತ್ರ];
    ಚಿಹ್ನೆರಹಿತ rsize = av_hash_get_ಗಾತ್ರ(ctx), i;

    av_hash_final(ctx, buf);
    ಗಾಗಿ (i = 0; i < FFMIN(rsize, ಗಾತ್ರ_2 / 2); i++)
        snprintf(dst + i * 2, ಗಾತ್ರ_2 - i * 2, "%02x", buf[i]);
}

ಶೂನ್ಯ av_hash_final_b64(ರಚನೆ AVHashContext *ctx, uint8_t *dst, ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2)
{
    uint8_t buf[AV_HASH_MAX_ಗಾತ್ರ], b64[AV_BASE64_ಗಾತ್ರ(AV_HASH_MAX_ಗಾತ್ರ)];
    ಚಿಹ್ನೆರಹಿತ rsize = av_hash_get_ಗಾತ್ರ(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, ಗಾತ್ರ(b64), buf, rsize);
    osize = AV_BASE64_ಗಾತ್ರ(rsize);
    ಸ್ಮರಣೆ_ನಕಲು(dst, b64, FFMIN(osize, ಗಾತ್ರ_2));
    ಆದರೆ (ಗಾತ್ರ_2 < osize)
        dst[ಗಾತ್ರ_2 - 1] = 0;
}

ಶೂನ್ಯ av_hash_freep(AVHashContext **ctx)
{
    ಆದರೆ (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
