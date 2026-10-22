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

#ଅନ୍ତର୍ଭାଵ <assert.h>
#ଅନ୍ତର୍ଭାଵ <stddef.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ "hash.h"

#ଅନ୍ତର୍ଭାଵ "adler32.h"
#ଅନ୍ତର୍ଭାଵ "crc.h"
#ଅନ୍ତର୍ଭାଵ "md5.h"
#ଅନ୍ତର୍ଭାଵ "murmur3.h"
#ଅନ୍ତର୍ଭାଵ "ripemd.h"
#ଅନ୍ତର୍ଭାଵ "sha.h"
#ଅନ୍ତର୍ଭାଵ "sha512.h"

#ଅନ୍ତର୍ଭାଵ "avstring.h"
#ଅନ୍ତର୍ଭାଵ "base64.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "intreadwrite.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"

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

ଗଣନା hashtype {
#define HASH_TYPE(TYPE, NAME, SIZE) TYPE,
    HASHES(HASH_TYPE)
    ଅଙ୍କ_HASHES
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AVHashContext {
    ଶୂନ୍ୟ *ctx;
    ଗଣନା hashtype type;
    ଅଚଳ AVCRC *crctab;
    uint32_t crc;
} AVHashContext;

#define HASH_MAX_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(SIZE, HASH_MAX_SIZE_BEFORE_ ## TYPE) - 1,
ଗଣନା {
    HASHES(HASH_MAX_SIZE)
    MAX_HASH_SIZE
};
static_assert(AV_HASH_MAX_SIZE >= MAX_HASH_SIZE, "AV_HASH_MAX_SIZE needs to be updated!");

#define HASH_MAX_NAME_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_NAME_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(ଆକାର(NAME), HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE) - 1,
ଗଣନା {
    HASHES(HASH_MAX_NAME_SIZE)
    MAX_HASH_NAME_SIZE
};

ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    ଅଚଳ ଅକ୍ଷର name[MAX_HASH_NAME_SIZE];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା size;
} hashdesc[] = {
#define HASH_DESC(TYPE, NAME, SIZE) [TYPE] = { NAME, SIZE },
    HASHES(HASH_DESC)
};

ଅଚଳ ଅକ୍ଷର *av_hash_names(ପୂର୍ଣ୍ଣସଂଖ୍ୟା i)
{
    ଯଦି (i < 0 || i >= ଅଙ୍କ_HASHES) ଫେରନ୍ତୁ ଖାଲି;
    ଫେରନ୍ତୁ hashdesc[i].name;
}

ଅଚଳ ଅକ୍ଷର *av_hash_get_name(ଅଚଳ AVHashContext *ctx)
{
    ଫେରନ୍ତୁ hashdesc[ctx->type].name;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hash_get_size(ଅଚଳ AVHashContext *ctx)
{
    ଫେରନ୍ତୁ hashdesc[ctx->type].size;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hash_alloc(AVHashContext **ctx, ଅଚଳ ଅକ୍ଷର *name)
{
    AVHashContext *res;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    *ctx = ଖାଲି;
    ପାଇଁ (i = 0; i < ଅଙ୍କ_HASHES; i++)
        ଯଦି (av_strcasecmp(name, hashdesc[i].name) == 0)
            ଭାଙ୍ଗ;
    ଯଦି (i >= ଅଙ୍କ_HASHES) ଫେରନ୍ତୁ AVERROR(EINVAL);
    res = av_mallocz(ଆକାର(*res));
    ଯଦି (!res) ଫେରନ୍ତୁ AVERROR(ENOMEM);
    res->type = i;
    ବାଛ (i) {
    ସ୍ଥିତି MD5:     res->ctx = av_md5_alloc(); ଭାଙ୍ଗ;
    ସ୍ଥିତି MURMUR3: res->ctx = av_murmur3_alloc(); ଭାଙ୍ଗ;
    ସ୍ଥିତି RIPEMD128:
    ସ୍ଥିତି RIPEMD160:
    ସ୍ଥିତି RIPEMD256:
    ସ୍ଥିତି RIPEMD320: res->ctx = av_ripemd_alloc(); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA160:
    ସ୍ଥିତି SHA224:
    ସ୍ଥିତି SHA256:  res->ctx = av_sha_alloc(); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA512_224:
    ସ୍ଥିତି SHA512_256:
    ସ୍ଥିତି SHA384:
    ସ୍ଥିତି SHA512:  res->ctx = av_sha512_alloc(); ଭାଙ୍ଗ;
    ସ୍ଥିତି CRC32:   res->crctab = av_crc_get_table(AV_CRC_32_IEEE_LE); ଭାଙ୍ଗ;
    ସ୍ଥିତି ADLER32: ଭାଙ୍ଗ;
    }
    ଯଦି (i != ADLER32 && i != CRC32 && !res->ctx) {
        av_free(res);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }
    *ctx = res;
    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ av_hash_init(AVHashContext *ctx)
{
    ବାଛ (ctx->type) {
    ସ୍ଥିତି MD5:     av_md5_init(ctx->ctx); ଭାଙ୍ଗ;
    ସ୍ଥିତି MURMUR3: av_murmur3_init(ctx->ctx); ଭାଙ୍ଗ;
    ସ୍ଥିତି RIPEMD128: av_ripemd_init(ctx->ctx, 128); ଭାଙ୍ଗ;
    ସ୍ଥିତି RIPEMD160: av_ripemd_init(ctx->ctx, 160); ଭାଙ୍ଗ;
    ସ୍ଥିତି RIPEMD256: av_ripemd_init(ctx->ctx, 256); ଭାଙ୍ଗ;
    ସ୍ଥିତି RIPEMD320: av_ripemd_init(ctx->ctx, 320); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA160:  av_sha_init(ctx->ctx, 160); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA224:  av_sha_init(ctx->ctx, 224); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA256:  av_sha_init(ctx->ctx, 256); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA512_224:  av_sha512_init(ctx->ctx, 224); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA512_256:  av_sha512_init(ctx->ctx, 256); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA384:  av_sha512_init(ctx->ctx, 384); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA512:  av_sha512_init(ctx->ctx, 512); ଭାଙ୍ଗ;
    ସ୍ଥିତି CRC32:   ctx->crc = UINT32_MAX; ଭାଙ୍ଗ;
    ସ୍ଥିତି ADLER32: ctx->crc = 1; ଭାଙ୍ଗ;
    }
}

ଶୂନ୍ୟ av_hash_update(AVHashContext *ctx, ଅଚଳ uint8_t *src, size_t len)
{
    ବାଛ (ctx->type) {
    ସ୍ଥିତି MD5:     av_md5_update(ctx->ctx, src, len); ଭାଙ୍ଗ;
    ସ୍ଥିତି MURMUR3: av_murmur3_update(ctx->ctx, src, len); ଭାଙ୍ଗ;
    ସ୍ଥିତି RIPEMD128:
    ସ୍ଥିତି RIPEMD160:
    ସ୍ଥିତି RIPEMD256:
    ସ୍ଥିତି RIPEMD320: av_ripemd_update(ctx->ctx, src, len); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA160:
    ସ୍ଥିତି SHA224:
    ସ୍ଥିତି SHA256:  av_sha_update(ctx->ctx, src, len); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA512_224:
    ସ୍ଥିତି SHA512_256:
    ସ୍ଥିତି SHA384:
    ସ୍ଥିତି SHA512:  av_sha512_update(ctx->ctx, src, len); ଭାଙ୍ଗ;
    ସ୍ଥିତି CRC32:   ctx->crc = av_crc(ctx->crctab, ctx->crc, src, len); ଭାଙ୍ଗ;
    ସ୍ଥିତି ADLER32: ctx->crc = av_adler32_update(ctx->crc, src, len); ଭାଙ୍ଗ;
    }
}

ଶୂନ୍ୟ av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    ବାଛ (ctx->type) {
    ସ୍ଥିତି MD5:     av_md5_final(ctx->ctx, dst); ଭାଙ୍ଗ;
    ସ୍ଥିତି MURMUR3: av_murmur3_final(ctx->ctx, dst); ଭାଙ୍ଗ;
    ସ୍ଥିତି RIPEMD128:
    ସ୍ଥିତି RIPEMD160:
    ସ୍ଥିତି RIPEMD256:
    ସ୍ଥିତି RIPEMD320: av_ripemd_final(ctx->ctx, dst); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA160:
    ସ୍ଥିତି SHA224:
    ସ୍ଥିତି SHA256:  av_sha_final(ctx->ctx, dst); ଭାଙ୍ଗ;
    ସ୍ଥିତି SHA512_224:
    ସ୍ଥିତି SHA512_256:
    ସ୍ଥିତି SHA384:
    ସ୍ଥିତି SHA512:  av_sha512_final(ctx->ctx, dst); ଭାଙ୍ଗ;
    ସ୍ଥିତି CRC32:   AV_WB32(dst, ctx->crc ^ UINT32_MAX); ଭାଙ୍ଗ;
    ସ୍ଥିତି ADLER32: AV_WB32(dst, ctx->crc); ଭାଙ୍ଗ;
    }
}

ଶୂନ୍ୟ av_hash_final_bin(ସଂରଚନା AVHashContext *ctx, uint8_t *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx);

    av_hash_final(ctx, buf);
    memcpy(dst, buf, FFMIN(size, rsize));
    ଯଦି (size > rsize)
        memset(dst + rsize, 0, size - rsize);
}

ଶୂନ୍ୟ av_hash_final_hex(ସଂରଚନା AVHashContext *ctx, uint8_t *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx), i;

    av_hash_final(ctx, buf);
    ପାଇଁ (i = 0; i < FFMIN(rsize, size / 2); i++)
        snprintf(dst + i * 2, size - i * 2, "%02x", buf[i]);
}

ଶୂନ୍ୟ av_hash_final_b64(ସଂରଚନା AVHashContext *ctx, uint8_t *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା size)
{
    uint8_t buf[AV_HASH_MAX_SIZE], b64[AV_BASE64_SIZE(AV_HASH_MAX_SIZE)];
    unsigned rsize = av_hash_get_size(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, ଆକାର(b64), buf, rsize);
    osize = AV_BASE64_SIZE(rsize);
    memcpy(dst, b64, FFMIN(osize, size));
    ଯଦି (size < osize)
        dst[size - 1] = 0;
}

ଶୂନ୍ୟ av_hash_freep(AVHashContext **ctx)
{
    ଯଦି (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
