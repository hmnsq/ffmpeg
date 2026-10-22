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

#شامل <assert.h>
#شامل <stddef.h>
#شامل <stdint.h>
#شامل <stdio.h>
#شامل <string.h>
#شامل "hash.h"

#شامل "adler32.h"
#شامل "crc.h"
#شامل "md5.h"
#شامل "murmur3.h"
#شامل "ripemd.h"
#شامل "sha.h"
#شامل "sha512.h"

#شامل "avstring.h"
#شامل "base64.h"
#شامل "error.h"
#شامل "intreadwrite.h"
#شامل "mem.h"

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

شمارش hashtype {
#define HASH_TYPE(TYPE, NAME, SIZE) TYPE,
    HASHES(HASH_TYPE)
    رقم_HASHES
};

تعریفنوع ساختار AVHashContext {
    تهی *ctx;
    شمارش hashtype type;
    ثابت AVCRC *crctab;
    uint32_t crc;
} AVHashContext;

#define HASH_MAX_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(SIZE, HASH_MAX_SIZE_BEFORE_ ## TYPE) - 1,
شمارش {
    HASHES(HASH_MAX_SIZE)
    MAX_HASH_SIZE
};
static_assert(AV_HASH_MAX_SIZE >= MAX_HASH_SIZE, "AV_HASH_MAX_SIZE needs to be updated!");

#define HASH_MAX_NAME_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_NAME_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(اندازه(NAME), HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE) - 1,
شمارش {
    HASHES(HASH_MAX_NAME_SIZE)
    MAX_HASH_NAME_SIZE
};

ایستا ثابت ساختار {
    ثابت نویسه name[MAX_HASH_NAME_SIZE];
    صحیح size;
} hashdesc[] = {
#define HASH_DESC(TYPE, NAME, SIZE) [TYPE] = { NAME, SIZE },
    HASHES(HASH_DESC)
};

ثابت نویسه *av_hash_names(صحیح i)
{
    اگر (i < 0 || i >= رقم_HASHES) بازگشت پوچ;
    بازگشت hashdesc[i].name;
}

ثابت نویسه *av_hash_get_name(ثابت AVHashContext *ctx)
{
    بازگشت hashdesc[ctx->type].name;
}

صحیح av_hash_get_size(ثابت AVHashContext *ctx)
{
    بازگشت hashdesc[ctx->type].size;
}

صحیح av_hash_alloc(AVHashContext **ctx, ثابت نویسه *name)
{
    AVHashContext *res;
    صحیح i;
    *ctx = پوچ;
    برای (i = 0; i < رقم_HASHES; i++)
        اگر (av_strcasecmp(name, hashdesc[i].name) == 0)
            بشکن;
    اگر (i >= رقم_HASHES) بازگشت AVERROR(EINVAL);
    res = av_mallocz(اندازه(*res));
    اگر (!res) بازگشت AVERROR(ENOMEM);
    res->type = i;
    انتخاب (i) {
    حالت MD5:     res->ctx = av_md5_alloc(); بشکن;
    حالت MURMUR3: res->ctx = av_murmur3_alloc(); بشکن;
    حالت RIPEMD128:
    حالت RIPEMD160:
    حالت RIPEMD256:
    حالت RIPEMD320: res->ctx = av_ripemd_alloc(); بشکن;
    حالت SHA160:
    حالت SHA224:
    حالت SHA256:  res->ctx = av_sha_alloc(); بشکن;
    حالت SHA512_224:
    حالت SHA512_256:
    حالت SHA384:
    حالت SHA512:  res->ctx = av_sha512_alloc(); بشکن;
    حالت CRC32:   res->crctab = av_crc_get_table(AV_CRC_32_IEEE_LE); بشکن;
    حالت ADLER32: بشکن;
    }
    اگر (i != ADLER32 && i != CRC32 && !res->ctx) {
        av_free(res);
        بازگشت AVERROR(ENOMEM);
    }
    *ctx = res;
    بازگشت 0;
}

تهی av_hash_init(AVHashContext *ctx)
{
    انتخاب (ctx->type) {
    حالت MD5:     av_md5_init(ctx->ctx); بشکن;
    حالت MURMUR3: av_murmur3_init(ctx->ctx); بشکن;
    حالت RIPEMD128: av_ripemd_init(ctx->ctx, 128); بشکن;
    حالت RIPEMD160: av_ripemd_init(ctx->ctx, 160); بشکن;
    حالت RIPEMD256: av_ripemd_init(ctx->ctx, 256); بشکن;
    حالت RIPEMD320: av_ripemd_init(ctx->ctx, 320); بشکن;
    حالت SHA160:  av_sha_init(ctx->ctx, 160); بشکن;
    حالت SHA224:  av_sha_init(ctx->ctx, 224); بشکن;
    حالت SHA256:  av_sha_init(ctx->ctx, 256); بشکن;
    حالت SHA512_224:  av_sha512_init(ctx->ctx, 224); بشکن;
    حالت SHA512_256:  av_sha512_init(ctx->ctx, 256); بشکن;
    حالت SHA384:  av_sha512_init(ctx->ctx, 384); بشکن;
    حالت SHA512:  av_sha512_init(ctx->ctx, 512); بشکن;
    حالت CRC32:   ctx->crc = UINT32_MAX; بشکن;
    حالت ADLER32: ctx->crc = 1; بشکن;
    }
}

تهی av_hash_update(AVHashContext *ctx, ثابت uint8_t *src, size_t len)
{
    انتخاب (ctx->type) {
    حالت MD5:     av_md5_update(ctx->ctx, src, len); بشکن;
    حالت MURMUR3: av_murmur3_update(ctx->ctx, src, len); بشکن;
    حالت RIPEMD128:
    حالت RIPEMD160:
    حالت RIPEMD256:
    حالت RIPEMD320: av_ripemd_update(ctx->ctx, src, len); بشکن;
    حالت SHA160:
    حالت SHA224:
    حالت SHA256:  av_sha_update(ctx->ctx, src, len); بشکن;
    حالت SHA512_224:
    حالت SHA512_256:
    حالت SHA384:
    حالت SHA512:  av_sha512_update(ctx->ctx, src, len); بشکن;
    حالت CRC32:   ctx->crc = av_crc(ctx->crctab, ctx->crc, src, len); بشکن;
    حالت ADLER32: ctx->crc = av_adler32_update(ctx->crc, src, len); بشکن;
    }
}

تهی av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    انتخاب (ctx->type) {
    حالت MD5:     av_md5_final(ctx->ctx, dst); بشکن;
    حالت MURMUR3: av_murmur3_final(ctx->ctx, dst); بشکن;
    حالت RIPEMD128:
    حالت RIPEMD160:
    حالت RIPEMD256:
    حالت RIPEMD320: av_ripemd_final(ctx->ctx, dst); بشکن;
    حالت SHA160:
    حالت SHA224:
    حالت SHA256:  av_sha_final(ctx->ctx, dst); بشکن;
    حالت SHA512_224:
    حالت SHA512_256:
    حالت SHA384:
    حالت SHA512:  av_sha512_final(ctx->ctx, dst); بشکن;
    حالت CRC32:   AV_WB32(dst, ctx->crc ^ UINT32_MAX); بشکن;
    حالت ADLER32: AV_WB32(dst, ctx->crc); بشکن;
    }
}

تهی av_hash_final_bin(ساختار AVHashContext *ctx, uint8_t *dst, صحیح size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx);

    av_hash_final(ctx, buf);
    memcpy(dst, buf, FFMIN(size, rsize));
    اگر (size > rsize)
        memset(dst + rsize, 0, size - rsize);
}

تهی av_hash_final_hex(ساختار AVHashContext *ctx, uint8_t *dst, صحیح size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx), i;

    av_hash_final(ctx, buf);
    برای (i = 0; i < FFMIN(rsize, size / 2); i++)
        snprintf(dst + i * 2, size - i * 2, "%02x", buf[i]);
}

تهی av_hash_final_b64(ساختار AVHashContext *ctx, uint8_t *dst, صحیح size)
{
    uint8_t buf[AV_HASH_MAX_SIZE], b64[AV_BASE64_SIZE(AV_HASH_MAX_SIZE)];
    unsigned rsize = av_hash_get_size(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, اندازه(b64), buf, rsize);
    osize = AV_BASE64_SIZE(rsize);
    memcpy(dst, b64, FFMIN(osize, size));
    اگر (size < osize)
        dst[size - 1] = 0;
}

تهی av_hash_freep(AVHashContext **ctx)
{
    اگر (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
