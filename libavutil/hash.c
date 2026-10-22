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

#অন্তর্ভাব <assert.h>
#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>
#অন্তর্ভাব "hash.h"

#অন্তর্ভাব "adler32.h"
#অন্তর্ভাব "crc.h"
#অন্তর্ভাব "md5.h"
#অন্তর্ভাব "murmur3.h"
#অন্তর্ভাব "ripemd.h"
#অন্তর্ভাব "sha.h"
#অন্তর্ভাব "sha512.h"

#অন্তর্ভাব "avstring.h"
#অন্তর্ভাব "base64.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "intreadwrite.h"
#অন্তর্ভাব "mem.h"

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

গণনা hashtype {
#define HASH_TYPE(TYPE, NAME, SIZE) TYPE,
    HASHES(HASH_TYPE)
    অঙ্ক_HASHES
};

প্রকারনির্দেশ সংরচনা AVHashContext {
    শূন্য *ctx;
    গণনা hashtype type;
    ধ্রুব AVCRC *crctab;
    uint32_t crc;
} AVHashContext;

#define HASH_MAX_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(SIZE, HASH_MAX_SIZE_BEFORE_ ## TYPE) - 1,
গণনা {
    HASHES(HASH_MAX_SIZE)
    MAX_HASH_SIZE
};
static_assert(AV_HASH_MAX_SIZE >= MAX_HASH_SIZE, "AV_HASH_MAX_SIZE needs to be updated!");

#define HASH_MAX_NAME_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_NAME_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(পরিমাণ(NAME), HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE) - 1,
গণনা {
    HASHES(HASH_MAX_NAME_SIZE)
    MAX_HASH_NAME_SIZE
};

স্থির ধ্রুব সংরচনা {
    ধ্রুব বর্ণ name[MAX_HASH_NAME_SIZE];
    পূর্ণাঙ্ক size;
} hashdesc[] = {
#define HASH_DESC(TYPE, NAME, SIZE) [TYPE] = { NAME, SIZE },
    HASHES(HASH_DESC)
};

ধ্রুব বর্ণ *av_hash_names(পূর্ণাঙ্ক i)
{
    যদি (i < 0 || i >= অঙ্ক_HASHES) প্রত্যাগম রিক্ত;
    প্রত্যাগম hashdesc[i].name;
}

ধ্রুব বর্ণ *av_hash_get_name(ধ্রুব AVHashContext *ctx)
{
    প্রত্যাগম hashdesc[ctx->type].name;
}

পূর্ণাঙ্ক av_hash_get_size(ধ্রুব AVHashContext *ctx)
{
    প্রত্যাগম hashdesc[ctx->type].size;
}

পূর্ণাঙ্ক av_hash_alloc(AVHashContext **ctx, ধ্রুব বর্ণ *name)
{
    AVHashContext *res;
    পূর্ণাঙ্ক i;
    *ctx = রিক্ত;
    প্রতি (i = 0; i < অঙ্ক_HASHES; i++)
        যদি (av_strcasecmp(name, hashdesc[i].name) == 0)
            ভঙ্গ;
    যদি (i >= অঙ্ক_HASHES) প্রত্যাগম AVERROR(EINVAL);
    res = av_mallocz(পরিমাণ(*res));
    যদি (!res) প্রত্যাগম AVERROR(ENOMEM);
    res->type = i;
    বিকল্প (i) {
    পক্ষ MD5:     res->ctx = av_md5_alloc(); ভঙ্গ;
    পক্ষ MURMUR3: res->ctx = av_murmur3_alloc(); ভঙ্গ;
    পক্ষ RIPEMD128:
    পক্ষ RIPEMD160:
    পক্ষ RIPEMD256:
    পক্ষ RIPEMD320: res->ctx = av_ripemd_alloc(); ভঙ্গ;
    পক্ষ SHA160:
    পক্ষ SHA224:
    পক্ষ SHA256:  res->ctx = av_sha_alloc(); ভঙ্গ;
    পক্ষ SHA512_224:
    পক্ষ SHA512_256:
    পক্ষ SHA384:
    পক্ষ SHA512:  res->ctx = av_sha512_alloc(); ভঙ্গ;
    পক্ষ CRC32:   res->crctab = av_crc_get_table(AV_CRC_32_IEEE_LE); ভঙ্গ;
    পক্ষ ADLER32: ভঙ্গ;
    }
    যদি (i != ADLER32 && i != CRC32 && !res->ctx) {
        av_free(res);
        প্রত্যাগম AVERROR(ENOMEM);
    }
    *ctx = res;
    প্রত্যাগম 0;
}

শূন্য av_hash_init(AVHashContext *ctx)
{
    বিকল্প (ctx->type) {
    পক্ষ MD5:     av_md5_init(ctx->ctx); ভঙ্গ;
    পক্ষ MURMUR3: av_murmur3_init(ctx->ctx); ভঙ্গ;
    পক্ষ RIPEMD128: av_ripemd_init(ctx->ctx, 128); ভঙ্গ;
    পক্ষ RIPEMD160: av_ripemd_init(ctx->ctx, 160); ভঙ্গ;
    পক্ষ RIPEMD256: av_ripemd_init(ctx->ctx, 256); ভঙ্গ;
    পক্ষ RIPEMD320: av_ripemd_init(ctx->ctx, 320); ভঙ্গ;
    পক্ষ SHA160:  av_sha_init(ctx->ctx, 160); ভঙ্গ;
    পক্ষ SHA224:  av_sha_init(ctx->ctx, 224); ভঙ্গ;
    পক্ষ SHA256:  av_sha_init(ctx->ctx, 256); ভঙ্গ;
    পক্ষ SHA512_224:  av_sha512_init(ctx->ctx, 224); ভঙ্গ;
    পক্ষ SHA512_256:  av_sha512_init(ctx->ctx, 256); ভঙ্গ;
    পক্ষ SHA384:  av_sha512_init(ctx->ctx, 384); ভঙ্গ;
    পক্ষ SHA512:  av_sha512_init(ctx->ctx, 512); ভঙ্গ;
    পক্ষ CRC32:   ctx->crc = UINT32_MAX; ভঙ্গ;
    পক্ষ ADLER32: ctx->crc = 1; ভঙ্গ;
    }
}

শূন্য av_hash_update(AVHashContext *ctx, ধ্রুব uint8_t *src, size_t len)
{
    বিকল্প (ctx->type) {
    পক্ষ MD5:     av_md5_update(ctx->ctx, src, len); ভঙ্গ;
    পক্ষ MURMUR3: av_murmur3_update(ctx->ctx, src, len); ভঙ্গ;
    পক্ষ RIPEMD128:
    পক্ষ RIPEMD160:
    পক্ষ RIPEMD256:
    পক্ষ RIPEMD320: av_ripemd_update(ctx->ctx, src, len); ভঙ্গ;
    পক্ষ SHA160:
    পক্ষ SHA224:
    পক্ষ SHA256:  av_sha_update(ctx->ctx, src, len); ভঙ্গ;
    পক্ষ SHA512_224:
    পক্ষ SHA512_256:
    পক্ষ SHA384:
    পক্ষ SHA512:  av_sha512_update(ctx->ctx, src, len); ভঙ্গ;
    পক্ষ CRC32:   ctx->crc = av_crc(ctx->crctab, ctx->crc, src, len); ভঙ্গ;
    পক্ষ ADLER32: ctx->crc = av_adler32_update(ctx->crc, src, len); ভঙ্গ;
    }
}

শূন্য av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    বিকল্প (ctx->type) {
    পক্ষ MD5:     av_md5_final(ctx->ctx, dst); ভঙ্গ;
    পক্ষ MURMUR3: av_murmur3_final(ctx->ctx, dst); ভঙ্গ;
    পক্ষ RIPEMD128:
    পক্ষ RIPEMD160:
    পক্ষ RIPEMD256:
    পক্ষ RIPEMD320: av_ripemd_final(ctx->ctx, dst); ভঙ্গ;
    পক্ষ SHA160:
    পক্ষ SHA224:
    পক্ষ SHA256:  av_sha_final(ctx->ctx, dst); ভঙ্গ;
    পক্ষ SHA512_224:
    পক্ষ SHA512_256:
    পক্ষ SHA384:
    পক্ষ SHA512:  av_sha512_final(ctx->ctx, dst); ভঙ্গ;
    পক্ষ CRC32:   AV_WB32(dst, ctx->crc ^ UINT32_MAX); ভঙ্গ;
    পক্ষ ADLER32: AV_WB32(dst, ctx->crc); ভঙ্গ;
    }
}

শূন্য av_hash_final_bin(সংরচনা AVHashContext *ctx, uint8_t *dst, পূর্ণাঙ্ক size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx);

    av_hash_final(ctx, buf);
    memcpy(dst, buf, FFMIN(size, rsize));
    যদি (size > rsize)
        memset(dst + rsize, 0, size - rsize);
}

শূন্য av_hash_final_hex(সংরচনা AVHashContext *ctx, uint8_t *dst, পূর্ণাঙ্ক size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx), i;

    av_hash_final(ctx, buf);
    প্রতি (i = 0; i < FFMIN(rsize, size / 2); i++)
        snprintf(dst + i * 2, size - i * 2, "%02x", buf[i]);
}

শূন্য av_hash_final_b64(সংরচনা AVHashContext *ctx, uint8_t *dst, পূর্ণাঙ্ক size)
{
    uint8_t buf[AV_HASH_MAX_SIZE], b64[AV_BASE64_SIZE(AV_HASH_MAX_SIZE)];
    unsigned rsize = av_hash_get_size(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, পরিমাণ(b64), buf, rsize);
    osize = AV_BASE64_SIZE(rsize);
    memcpy(dst, b64, FFMIN(osize, size));
    যদি (size < osize)
        dst[size - 1] = 0;
}

শূন্য av_hash_freep(AVHashContext **ctx)
{
    যদি (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
