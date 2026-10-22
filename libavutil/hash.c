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
#define HASHES(ENTRY)                   \
    ENTRY(MD5,        "MD5",        16) \
    ENTRY(MURMUR3,    "murmur3",    16) \
    ENTRY(RIPEMD128,  "RIPEMD128",  16) \
    ENTRY(RIPEMD160,  "RIPEMD160",  20) \
    ENTRY(RIPEMD256,  "RIPEMD256",  32) \
    ENTRY(RIPEMD320,  "RIPEMD320",  40) \
    ENTRY(SHA160,     "SHA160",     20) \
    ENTRY(SHA224,     "SHA224",     28) \
    ENTRY(SHA256,     "SHA256",     32) \
    ENTRY(SHA512_224, "SHA512/224", 28) \
    ENTRY(SHA512_256, "SHA512/256", 32) \
    ENTRY(SHA384,     "SHA384",     48) \
    ENTRY(SHA512,     "SHA512",     64) \
    ENTRY(CRC32,      "CRC32",       4) \
    ENTRY(ADLER32,    "adler32",     4) \

ಗಣನಾ hashtype {
#define HASH_TYPE(TYPE, NAME, SIZE) TYPE,
    HASHES(HASH_TYPE)
    ಅಂಕೆ_HASHES
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVHashContext {
    ಶೂನ್ಯ *ctx;
    ಗಣನಾ hashtype type;
    ಧ್ರುವ AVCRC *crctab;
    uint32_t crc;
} AVHashContext;

#define HASH_MAX_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(SIZE, HASH_MAX_SIZE_BEFORE_ ## TYPE) - 1,
ಗಣನಾ {
    HASHES(HASH_MAX_SIZE)
    MAX_HASH_SIZE
};
static_assert(AV_HASH_MAX_SIZE >= MAX_HASH_SIZE, "AV_HASH_MAX_SIZE needs to be updated!");

#define HASH_MAX_NAME_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_NAME_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(ಪರಿಮಾಣ(NAME), HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE) - 1,
ಗಣನಾ {
    HASHES(HASH_MAX_NAME_SIZE)
    MAX_HASH_NAME_SIZE
};

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    ಧ್ರುವ ವರ್ಣ name[MAX_HASH_NAME_SIZE];
    ಪೂರ್ಣಾಙ್ಕ size;
} hashdesc[] = {
#define HASH_DESC(TYPE, NAME, SIZE) [TYPE] = { NAME, SIZE },
    HASHES(HASH_DESC)
};

ಧ್ರುವ ವರ್ಣ *av_hash_names(ಪೂರ್ಣಾಙ್ಕ i)
{
    ಯದಿ (i < 0 || i >= ಅಂಕೆ_HASHES) ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ hashdesc[i].name;
}

ಧ್ರುವ ವರ್ಣ *av_hash_get_name(ಧ್ರುವ AVHashContext *ctx)
{
    ಪ್ರತ್ಯಾಗಮ hashdesc[ctx->type].name;
}

ಪೂರ್ಣಾಙ್ಕ av_hash_get_size(ಧ್ರುವ AVHashContext *ctx)
{
    ಪ್ರತ್ಯಾಗಮ hashdesc[ctx->type].size;
}

ಪೂರ್ಣಾಙ್ಕ av_hash_alloc(AVHashContext **ctx, ಧ್ರುವ ವರ್ಣ *name)
{
    AVHashContext *res;
    ಪೂರ್ಣಾಙ್ಕ i;
    *ctx = ರಿಕ್ತ;
    ಪ್ರತಿ (i = 0; i < ಅಂಕೆ_HASHES; i++)
        ಯದಿ (av_strcasecmp(name, hashdesc[i].name) == 0)
            ಭಙ್ಗ;
    ಯದಿ (i >= ಅಂಕೆ_HASHES) ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    res = av_mallocz(ಪರಿಮಾಣ(*res));
    ಯದಿ (!res) ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    res->type = i;
    ವಿಕಲ್ಪ (i) {
    ಪಕ್ಷ MD5:     res->ctx = av_md5_alloc(); ಭಙ್ಗ;
    ಪಕ್ಷ MURMUR3: res->ctx = av_murmur3_alloc(); ಭಙ್ಗ;
    ಪಕ್ಷ RIPEMD128:
    ಪಕ್ಷ RIPEMD160:
    ಪಕ್ಷ RIPEMD256:
    ಪಕ್ಷ RIPEMD320: res->ctx = av_ripemd_alloc(); ಭಙ್ಗ;
    ಪಕ್ಷ SHA160:
    ಪಕ್ಷ SHA224:
    ಪಕ್ಷ SHA256:  res->ctx = av_sha_alloc(); ಭಙ್ಗ;
    ಪಕ್ಷ SHA512_224:
    ಪಕ್ಷ SHA512_256:
    ಪಕ್ಷ SHA384:
    ಪಕ್ಷ SHA512:  res->ctx = av_sha512_alloc(); ಭಙ್ಗ;
    ಪಕ್ಷ CRC32:   res->crctab = av_crc_get_table(AV_CRC_32_IEEE_LE); ಭಙ್ಗ;
    ಪಕ್ಷ ADLER32: ಭಙ್ಗ;
    }
    ಯದಿ (i != ADLER32 && i != CRC32 && !res->ctx) {
        av_free(res);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }
    *ctx = res;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ av_hash_init(AVHashContext *ctx)
{
    ವಿಕಲ್ಪ (ctx->type) {
    ಪಕ್ಷ MD5:     av_md5_init(ctx->ctx); ಭಙ್ಗ;
    ಪಕ್ಷ MURMUR3: av_murmur3_init(ctx->ctx); ಭಙ್ಗ;
    ಪಕ್ಷ RIPEMD128: av_ripemd_init(ctx->ctx, 128); ಭಙ್ಗ;
    ಪಕ್ಷ RIPEMD160: av_ripemd_init(ctx->ctx, 160); ಭಙ್ಗ;
    ಪಕ್ಷ RIPEMD256: av_ripemd_init(ctx->ctx, 256); ಭಙ್ಗ;
    ಪಕ್ಷ RIPEMD320: av_ripemd_init(ctx->ctx, 320); ಭಙ್ಗ;
    ಪಕ್ಷ SHA160:  av_sha_init(ctx->ctx, 160); ಭಙ್ಗ;
    ಪಕ್ಷ SHA224:  av_sha_init(ctx->ctx, 224); ಭಙ್ಗ;
    ಪಕ್ಷ SHA256:  av_sha_init(ctx->ctx, 256); ಭಙ್ಗ;
    ಪಕ್ಷ SHA512_224:  av_sha512_init(ctx->ctx, 224); ಭಙ್ಗ;
    ಪಕ್ಷ SHA512_256:  av_sha512_init(ctx->ctx, 256); ಭಙ್ಗ;
    ಪಕ್ಷ SHA384:  av_sha512_init(ctx->ctx, 384); ಭಙ್ಗ;
    ಪಕ್ಷ SHA512:  av_sha512_init(ctx->ctx, 512); ಭಙ್ಗ;
    ಪಕ್ಷ CRC32:   ctx->crc = UINT32_MAX; ಭಙ್ಗ;
    ಪಕ್ಷ ADLER32: ctx->crc = 1; ಭಙ್ಗ;
    }
}

ಶೂನ್ಯ av_hash_update(AVHashContext *ctx, ಧ್ರುವ uint8_t *src, size_t len)
{
    ವಿಕಲ್ಪ (ctx->type) {
    ಪಕ್ಷ MD5:     av_md5_update(ctx->ctx, src, len); ಭಙ್ಗ;
    ಪಕ್ಷ MURMUR3: av_murmur3_update(ctx->ctx, src, len); ಭಙ್ಗ;
    ಪಕ್ಷ RIPEMD128:
    ಪಕ್ಷ RIPEMD160:
    ಪಕ್ಷ RIPEMD256:
    ಪಕ್ಷ RIPEMD320: av_ripemd_update(ctx->ctx, src, len); ಭಙ್ಗ;
    ಪಕ್ಷ SHA160:
    ಪಕ್ಷ SHA224:
    ಪಕ್ಷ SHA256:  av_sha_update(ctx->ctx, src, len); ಭಙ್ಗ;
    ಪಕ್ಷ SHA512_224:
    ಪಕ್ಷ SHA512_256:
    ಪಕ್ಷ SHA384:
    ಪಕ್ಷ SHA512:  av_sha512_update(ctx->ctx, src, len); ಭಙ್ಗ;
    ಪಕ್ಷ CRC32:   ctx->crc = av_crc(ctx->crctab, ctx->crc, src, len); ಭಙ್ಗ;
    ಪಕ್ಷ ADLER32: ctx->crc = av_adler32_update(ctx->crc, src, len); ಭಙ್ಗ;
    }
}

ಶೂನ್ಯ av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    ವಿಕಲ್ಪ (ctx->type) {
    ಪಕ್ಷ MD5:     av_md5_final(ctx->ctx, dst); ಭಙ್ಗ;
    ಪಕ್ಷ MURMUR3: av_murmur3_final(ctx->ctx, dst); ಭಙ್ಗ;
    ಪಕ್ಷ RIPEMD128:
    ಪಕ್ಷ RIPEMD160:
    ಪಕ್ಷ RIPEMD256:
    ಪಕ್ಷ RIPEMD320: av_ripemd_final(ctx->ctx, dst); ಭಙ್ಗ;
    ಪಕ್ಷ SHA160:
    ಪಕ್ಷ SHA224:
    ಪಕ್ಷ SHA256:  av_sha_final(ctx->ctx, dst); ಭಙ್ಗ;
    ಪಕ್ಷ SHA512_224:
    ಪಕ್ಷ SHA512_256:
    ಪಕ್ಷ SHA384:
    ಪಕ್ಷ SHA512:  av_sha512_final(ctx->ctx, dst); ಭಙ್ಗ;
    ಪಕ್ಷ CRC32:   AV_WB32(dst, ctx->crc ^ UINT32_MAX); ಭಙ್ಗ;
    ಪಕ್ಷ ADLER32: AV_WB32(dst, ctx->crc); ಭಙ್ಗ;
    }
}

ಶೂನ್ಯ av_hash_final_bin(ಸಂರಚನಾ AVHashContext *ctx, uint8_t *dst, ಪೂರ್ಣಾಙ್ಕ size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx);

    av_hash_final(ctx, buf);
    memcpy(dst, buf, FFMIN(size, rsize));
    ಯದಿ (size > rsize)
        memset(dst + rsize, 0, size - rsize);
}

ಶೂನ್ಯ av_hash_final_hex(ಸಂರಚನಾ AVHashContext *ctx, uint8_t *dst, ಪೂರ್ಣಾಙ್ಕ size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx), i;

    av_hash_final(ctx, buf);
    ಪ್ರತಿ (i = 0; i < FFMIN(rsize, size / 2); i++)
        snprintf(dst + i * 2, size - i * 2, "%02x", buf[i]);
}

ಶೂನ್ಯ av_hash_final_b64(ಸಂರಚನಾ AVHashContext *ctx, uint8_t *dst, ಪೂರ್ಣಾಙ್ಕ size)
{
    uint8_t buf[AV_HASH_MAX_SIZE], b64[AV_BASE64_SIZE(AV_HASH_MAX_SIZE)];
    unsigned rsize = av_hash_get_size(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, ಪರಿಮಾಣ(b64), buf, rsize);
    osize = AV_BASE64_SIZE(rsize);
    memcpy(dst, b64, FFMIN(osize, size));
    ಯದಿ (size < osize)
        dst[size - 1] = 0;
}

ಶೂನ್ಯ av_hash_freep(AVHashContext **ctx)
{
    ಯದಿ (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
