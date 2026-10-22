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
#define HASH_TYPE(TYPE, NAME, আকার_3) TYPE,
    HASHES(HASH_TYPE)
    অঙ্ক_HASHES
};

প্রকারলেখ কাঠামো AVHashContext {
    শূন্য *ctx;
    গণনা hashtype type;
    ধ্রুবক AVCRC *crctab;
    uint32_t crc;
} AVHashContext;

#define HASH_MAX_আকার(TYPE, NAME, আকার_3) \
    HASH_MAX_আকার_BEFORE ## TYPE,      \
    HASH_MAX_আকার_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(আকার_3, HASH_MAX_আকার_BEFORE ## TYPE) - 1,
গণনা {
    HASHES(HASH_MAX_আকার)
    MAX_HASH_আকার
};
static_assert(AV_HASH_MAX_আকার >= MAX_HASH_আকার, "AV_HASH_MAX_SIZE needs to be updated!");

#define HASH_MAX_NAME_আকার(TYPE, NAME, আকার_3) \
    HASH_MAX_NAME_আকার_BEFORE ## TYPE,      \
    HASH_MAX_NAME_আকার_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(আকার(NAME), HASH_MAX_NAME_আকার_BEFORE ## TYPE) - 1,
গণনা {
    HASHES(HASH_MAX_NAME_আকার)
    MAX_HASH_NAME_আকার
};

স্থির ধ্রুবক কাঠামো {
    ধ্রুবক অক্ষর name[MAX_HASH_NAME_আকার];
    পূর্ণসংখ্যা আকার_2;
} hashdesc[] = {
#define HASH_DESC(TYPE, NAME, আকার_3) [TYPE] = { NAME, আকার_3 },
    HASHES(HASH_DESC)
};

ধ্রুবক অক্ষর *av_hash_names(পূর্ণসংখ্যা i)
{
    যদি (i < 0 || i >= অঙ্ক_HASHES) ফেরত ফাঁকা;
    ফেরত hashdesc[i].name;
}

ধ্রুবক অক্ষর *av_hash_get_name(ধ্রুবক AVHashContext *ctx)
{
    ফেরত hashdesc[ctx->type].name;
}

পূর্ণসংখ্যা av_hash_get_আকার(ধ্রুবক AVHashContext *ctx)
{
    ফেরত hashdesc[ctx->type].আকার_2;
}

পূর্ণসংখ্যা av_hash_alloc(AVHashContext **ctx, ধ্রুবক অক্ষর *name)
{
    AVHashContext *res;
    পূর্ণসংখ্যা i;
    *ctx = ফাঁকা;
    জন্য (i = 0; i < অঙ্ক_HASHES; i++)
        যদি (av_strcasecmp(name, hashdesc[i].name) == 0)
            বিরতি;
    যদি (i >= অঙ্ক_HASHES) ফেরত AVERROR(EINVAL);
    res = av_mallocz(আকার(*res));
    যদি (!res) ফেরত AVERROR(ENOMEM);
    res->type = i;
    নির্বাচন (i) {
    ক্ষেত্র MD5:     res->ctx = av_md5_alloc(); বিরতি;
    ক্ষেত্র MURMUR3: res->ctx = av_murmur3_alloc(); বিরতি;
    ক্ষেত্র RIPEMD128:
    ক্ষেত্র RIPEMD160:
    ক্ষেত্র RIPEMD256:
    ক্ষেত্র RIPEMD320: res->ctx = av_ripemd_alloc(); বিরতি;
    ক্ষেত্র SHA160:
    ক্ষেত্র SHA224:
    ক্ষেত্র SHA256:  res->ctx = av_sha_alloc(); বিরতি;
    ক্ষেত্র SHA512_224:
    ক্ষেত্র SHA512_256:
    ক্ষেত্র SHA384:
    ক্ষেত্র SHA512:  res->ctx = av_sha512_alloc(); বিরতি;
    ক্ষেত্র CRC32:   res->crctab = av_crc_get_table(AV_CRC_32_IEEE_LE); বিরতি;
    ক্ষেত্র ADLER32: বিরতি;
    }
    যদি (i != ADLER32 && i != CRC32 && !res->ctx) {
        av_free(res);
        ফেরত AVERROR(ENOMEM);
    }
    *ctx = res;
    ফেরত 0;
}

শূন্য av_hash_init(AVHashContext *ctx)
{
    নির্বাচন (ctx->type) {
    ক্ষেত্র MD5:     av_md5_init(ctx->ctx); বিরতি;
    ক্ষেত্র MURMUR3: av_murmur3_init(ctx->ctx); বিরতি;
    ক্ষেত্র RIPEMD128: av_ripemd_init(ctx->ctx, 128); বিরতি;
    ক্ষেত্র RIPEMD160: av_ripemd_init(ctx->ctx, 160); বিরতি;
    ক্ষেত্র RIPEMD256: av_ripemd_init(ctx->ctx, 256); বিরতি;
    ক্ষেত্র RIPEMD320: av_ripemd_init(ctx->ctx, 320); বিরতি;
    ক্ষেত্র SHA160:  av_sha_init(ctx->ctx, 160); বিরতি;
    ক্ষেত্র SHA224:  av_sha_init(ctx->ctx, 224); বিরতি;
    ক্ষেত্র SHA256:  av_sha_init(ctx->ctx, 256); বিরতি;
    ক্ষেত্র SHA512_224:  av_sha512_init(ctx->ctx, 224); বিরতি;
    ক্ষেত্র SHA512_256:  av_sha512_init(ctx->ctx, 256); বিরতি;
    ক্ষেত্র SHA384:  av_sha512_init(ctx->ctx, 384); বিরতি;
    ক্ষেত্র SHA512:  av_sha512_init(ctx->ctx, 512); বিরতি;
    ক্ষেত্র CRC32:   ctx->crc = UINT32_MAX; বিরতি;
    ক্ষেত্র ADLER32: ctx->crc = 1; বিরতি;
    }
}

শূন্য av_hash_update(AVHashContext *ctx, ধ্রুবক uint8_t *src, size_t len)
{
    নির্বাচন (ctx->type) {
    ক্ষেত্র MD5:     av_md5_update(ctx->ctx, src, len); বিরতি;
    ক্ষেত্র MURMUR3: av_murmur3_update(ctx->ctx, src, len); বিরতি;
    ক্ষেত্র RIPEMD128:
    ক্ষেত্র RIPEMD160:
    ক্ষেত্র RIPEMD256:
    ক্ষেত্র RIPEMD320: av_ripemd_update(ctx->ctx, src, len); বিরতি;
    ক্ষেত্র SHA160:
    ক্ষেত্র SHA224:
    ক্ষেত্র SHA256:  av_sha_update(ctx->ctx, src, len); বিরতি;
    ক্ষেত্র SHA512_224:
    ক্ষেত্র SHA512_256:
    ক্ষেত্র SHA384:
    ক্ষেত্র SHA512:  av_sha512_update(ctx->ctx, src, len); বিরতি;
    ক্ষেত্র CRC32:   ctx->crc = av_crc(ctx->crctab, ctx->crc, src, len); বিরতি;
    ক্ষেত্র ADLER32: ctx->crc = av_adler32_update(ctx->crc, src, len); বিরতি;
    }
}

শূন্য av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    নির্বাচন (ctx->type) {
    ক্ষেত্র MD5:     av_md5_final(ctx->ctx, dst); বিরতি;
    ক্ষেত্র MURMUR3: av_murmur3_final(ctx->ctx, dst); বিরতি;
    ক্ষেত্র RIPEMD128:
    ক্ষেত্র RIPEMD160:
    ক্ষেত্র RIPEMD256:
    ক্ষেত্র RIPEMD320: av_ripemd_final(ctx->ctx, dst); বিরতি;
    ক্ষেত্র SHA160:
    ক্ষেত্র SHA224:
    ক্ষেত্র SHA256:  av_sha_final(ctx->ctx, dst); বিরতি;
    ক্ষেত্র SHA512_224:
    ক্ষেত্র SHA512_256:
    ক্ষেত্র SHA384:
    ক্ষেত্র SHA512:  av_sha512_final(ctx->ctx, dst); বিরতি;
    ক্ষেত্র CRC32:   AV_WB32(dst, ctx->crc ^ UINT32_MAX); বিরতি;
    ক্ষেত্র ADLER32: AV_WB32(dst, ctx->crc); বিরতি;
    }
}

শূন্য av_hash_final_bin(কাঠামো AVHashContext *ctx, uint8_t *dst, পূর্ণসংখ্যা আকার_2)
{
    uint8_t buf[AV_HASH_MAX_আকার];
    unsigned rsize = av_hash_get_আকার(ctx);

    av_hash_final(ctx, buf);
    memcpy(dst, buf, FFMIN(আকার_2, rsize));
    যদি (আকার_2 > rsize)
        memset(dst + rsize, 0, আকার_2 - rsize);
}

শূন্য av_hash_final_hex(কাঠামো AVHashContext *ctx, uint8_t *dst, পূর্ণসংখ্যা আকার_2)
{
    uint8_t buf[AV_HASH_MAX_আকার];
    unsigned rsize = av_hash_get_আকার(ctx), i;

    av_hash_final(ctx, buf);
    জন্য (i = 0; i < FFMIN(rsize, আকার_2 / 2); i++)
        snprintf(dst + i * 2, আকার_2 - i * 2, "%02x", buf[i]);
}

শূন্য av_hash_final_b64(কাঠামো AVHashContext *ctx, uint8_t *dst, পূর্ণসংখ্যা আকার_2)
{
    uint8_t buf[AV_HASH_MAX_আকার], b64[AV_BASE64_আকার(AV_HASH_MAX_আকার)];
    unsigned rsize = av_hash_get_আকার(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, আকার(b64), buf, rsize);
    osize = AV_BASE64_আকার(rsize);
    memcpy(dst, b64, FFMIN(osize, আকার_2));
    যদি (আকার_2 < osize)
        dst[আকার_2 - 1] = 0;
}

শূন্য av_hash_freep(AVHashContext **ctx)
{
    যদি (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
