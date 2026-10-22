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

#அந்தர்பாவ <assert.h>
#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ "hash.h"

#அந்தர்பாவ "adler32.h"
#அந்தர்பாவ "crc.h"
#அந்தர்பாவ "md5.h"
#அந்தர்பாவ "murmur3.h"
#அந்தர்பாவ "ripemd.h"
#அந்தர்பாவ "sha.h"
#அந்தர்பாவ "sha512.h"

#அந்தர்பாவ "avstring.h"
#அந்தர்பாவ "base64.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "intreadwrite.h"
#அந்தர்பாவ "mem.h"

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

எண்ணிக்கை hashtype {
#define HASH_TYPE(TYPE, NAME, SIZE) TYPE,
    HASHES(HASH_TYPE)
    இலக்கம்_HASHES
};

வகைவரை கட்டமைப்பு AVHashContext {
    வெறுமை *ctx;
    எண்ணிக்கை hashtype type;
    மாறிலி AVCRC *crctab;
    uint32_t crc;
} AVHashContext;

#define HASH_MAX_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(SIZE, HASH_MAX_SIZE_BEFORE_ ## TYPE) - 1,
எண்ணிக்கை {
    HASHES(HASH_MAX_SIZE)
    MAX_HASH_SIZE
};
static_assert(AV_HASH_MAX_SIZE >= MAX_HASH_SIZE, "AV_HASH_MAX_SIZE needs to be updated!");

#define HASH_MAX_NAME_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_NAME_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(அளவு(NAME), HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE) - 1,
எண்ணிக்கை {
    HASHES(HASH_MAX_NAME_SIZE)
    MAX_HASH_NAME_SIZE
};

நிலையான மாறிலி கட்டமைப்பு {
    மாறிலி எழுத்து name[MAX_HASH_NAME_SIZE];
    முழு size;
} hashdesc[] = {
#define HASH_DESC(TYPE, NAME, SIZE) [TYPE] = { NAME, SIZE },
    HASHES(HASH_DESC)
};

மாறிலி எழுத்து *av_hash_names(முழு i)
{
    எனில் (i < 0 || i >= இலக்கம்_HASHES) திரும்பு வெற்று;
    திரும்பு hashdesc[i].name;
}

மாறிலி எழுத்து *av_hash_get_name(மாறிலி AVHashContext *ctx)
{
    திரும்பு hashdesc[ctx->type].name;
}

முழு av_hash_get_size(மாறிலி AVHashContext *ctx)
{
    திரும்பு hashdesc[ctx->type].size;
}

முழு av_hash_alloc(AVHashContext **ctx, மாறிலி எழுத்து *name)
{
    AVHashContext *res;
    முழு i;
    *ctx = வெற்று;
    க்கு (i = 0; i < இலக்கம்_HASHES; i++)
        எனில் (av_strcasecmp(name, hashdesc[i].name) == 0)
            நிறுத்து;
    எனில் (i >= இலக்கம்_HASHES) திரும்பு AVERROR(EINVAL);
    res = av_mallocz(அளவு(*res));
    எனில் (!res) திரும்பு AVERROR(ENOMEM);
    res->type = i;
    தேர்வு (i) {
    நிலை MD5:     res->ctx = av_md5_alloc(); நிறுத்து;
    நிலை MURMUR3: res->ctx = av_murmur3_alloc(); நிறுத்து;
    நிலை RIPEMD128:
    நிலை RIPEMD160:
    நிலை RIPEMD256:
    நிலை RIPEMD320: res->ctx = av_ripemd_alloc(); நிறுத்து;
    நிலை SHA160:
    நிலை SHA224:
    நிலை SHA256:  res->ctx = av_sha_alloc(); நிறுத்து;
    நிலை SHA512_224:
    நிலை SHA512_256:
    நிலை SHA384:
    நிலை SHA512:  res->ctx = av_sha512_alloc(); நிறுத்து;
    நிலை CRC32:   res->crctab = av_crc_get_table(AV_CRC_32_IEEE_LE); நிறுத்து;
    நிலை ADLER32: நிறுத்து;
    }
    எனில் (i != ADLER32 && i != CRC32 && !res->ctx) {
        av_free(res);
        திரும்பு AVERROR(ENOMEM);
    }
    *ctx = res;
    திரும்பு 0;
}

வெறுமை av_hash_init(AVHashContext *ctx)
{
    தேர்வு (ctx->type) {
    நிலை MD5:     av_md5_init(ctx->ctx); நிறுத்து;
    நிலை MURMUR3: av_murmur3_init(ctx->ctx); நிறுத்து;
    நிலை RIPEMD128: av_ripemd_init(ctx->ctx, 128); நிறுத்து;
    நிலை RIPEMD160: av_ripemd_init(ctx->ctx, 160); நிறுத்து;
    நிலை RIPEMD256: av_ripemd_init(ctx->ctx, 256); நிறுத்து;
    நிலை RIPEMD320: av_ripemd_init(ctx->ctx, 320); நிறுத்து;
    நிலை SHA160:  av_sha_init(ctx->ctx, 160); நிறுத்து;
    நிலை SHA224:  av_sha_init(ctx->ctx, 224); நிறுத்து;
    நிலை SHA256:  av_sha_init(ctx->ctx, 256); நிறுத்து;
    நிலை SHA512_224:  av_sha512_init(ctx->ctx, 224); நிறுத்து;
    நிலை SHA512_256:  av_sha512_init(ctx->ctx, 256); நிறுத்து;
    நிலை SHA384:  av_sha512_init(ctx->ctx, 384); நிறுத்து;
    நிலை SHA512:  av_sha512_init(ctx->ctx, 512); நிறுத்து;
    நிலை CRC32:   ctx->crc = UINT32_MAX; நிறுத்து;
    நிலை ADLER32: ctx->crc = 1; நிறுத்து;
    }
}

வெறுமை av_hash_update(AVHashContext *ctx, மாறிலி uint8_t *src, size_t len)
{
    தேர்வு (ctx->type) {
    நிலை MD5:     av_md5_update(ctx->ctx, src, len); நிறுத்து;
    நிலை MURMUR3: av_murmur3_update(ctx->ctx, src, len); நிறுத்து;
    நிலை RIPEMD128:
    நிலை RIPEMD160:
    நிலை RIPEMD256:
    நிலை RIPEMD320: av_ripemd_update(ctx->ctx, src, len); நிறுத்து;
    நிலை SHA160:
    நிலை SHA224:
    நிலை SHA256:  av_sha_update(ctx->ctx, src, len); நிறுத்து;
    நிலை SHA512_224:
    நிலை SHA512_256:
    நிலை SHA384:
    நிலை SHA512:  av_sha512_update(ctx->ctx, src, len); நிறுத்து;
    நிலை CRC32:   ctx->crc = av_crc(ctx->crctab, ctx->crc, src, len); நிறுத்து;
    நிலை ADLER32: ctx->crc = av_adler32_update(ctx->crc, src, len); நிறுத்து;
    }
}

வெறுமை av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    தேர்வு (ctx->type) {
    நிலை MD5:     av_md5_final(ctx->ctx, dst); நிறுத்து;
    நிலை MURMUR3: av_murmur3_final(ctx->ctx, dst); நிறுத்து;
    நிலை RIPEMD128:
    நிலை RIPEMD160:
    நிலை RIPEMD256:
    நிலை RIPEMD320: av_ripemd_final(ctx->ctx, dst); நிறுத்து;
    நிலை SHA160:
    நிலை SHA224:
    நிலை SHA256:  av_sha_final(ctx->ctx, dst); நிறுத்து;
    நிலை SHA512_224:
    நிலை SHA512_256:
    நிலை SHA384:
    நிலை SHA512:  av_sha512_final(ctx->ctx, dst); நிறுத்து;
    நிலை CRC32:   AV_WB32(dst, ctx->crc ^ UINT32_MAX); நிறுத்து;
    நிலை ADLER32: AV_WB32(dst, ctx->crc); நிறுத்து;
    }
}

வெறுமை av_hash_final_bin(கட்டமைப்பு AVHashContext *ctx, uint8_t *dst, முழு size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx);

    av_hash_final(ctx, buf);
    memcpy(dst, buf, FFMIN(size, rsize));
    எனில் (size > rsize)
        memset(dst + rsize, 0, size - rsize);
}

வெறுமை av_hash_final_hex(கட்டமைப்பு AVHashContext *ctx, uint8_t *dst, முழு size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx), i;

    av_hash_final(ctx, buf);
    க்கு (i = 0; i < FFMIN(rsize, size / 2); i++)
        snprintf(dst + i * 2, size - i * 2, "%02x", buf[i]);
}

வெறுமை av_hash_final_b64(கட்டமைப்பு AVHashContext *ctx, uint8_t *dst, முழு size)
{
    uint8_t buf[AV_HASH_MAX_SIZE], b64[AV_BASE64_SIZE(AV_HASH_MAX_SIZE)];
    unsigned rsize = av_hash_get_size(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, அளவு(b64), buf, rsize);
    osize = AV_BASE64_SIZE(rsize);
    memcpy(dst, b64, FFMIN(osize, size));
    எனில் (size < osize)
        dst[size - 1] = 0;
}

வெறுமை av_hash_freep(AVHashContext **ctx)
{
    எனில் (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
