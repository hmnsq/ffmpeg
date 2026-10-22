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

#समावेश <assert.h>
#समावेश <stddef.h>
#समावेश <stdint.h>
#समावेश <stdio.h>
#समावेश <string.h>
#समावेश "hash.h"

#समावेश "adler32.h"
#समावेश "crc.h"
#समावेश "md5.h"
#समावेश "murmur3.h"
#समावेश "ripemd.h"
#समावेश "sha.h"
#समावेश "sha512.h"

#समावेश "avstring.h"
#समावेश "base64.h"
#समावेश "error.h"
#समावेश "intreadwrite.h"
#समावेश "mem.h"

// ENTRY(HASH_TYPE, HASH_NAME, HASH_SIZE)
#घोषणा HASHES(ENTRY)                   \
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

क्रमागत hashtype {
#घोषणा HASH_TYPE(TYPE, NAME, आकार_2) TYPE,
    HASHES(HASH_TYPE)
    अंक_HASHES
};

प्रकार काष्ठा AVHashContext {
    व्योम *ctx;
    क्रमागत hashtype type;
    स्थिर AVCRC *crctab;
    uint32_t crc;
} AVHashContext;

#घोषणा HASH_MAX_आकार(TYPE, NAME, आकार_2) \
    HASH_MAX_आकार_BEFORE ## TYPE,      \
    HASH_MAX_आकार_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(आकार_2, HASH_MAX_आकार_BEFORE ## TYPE) - 1,
क्रमागत {
    HASHES(HASH_MAX_आकार)
    MAX_HASH_आकार
};
static_assert(AV_HASH_MAX_आकार >= MAX_HASH_आकार, "AV_HASH_MAX_SIZE needs to be updated!");

#घोषणा HASH_MAX_NAME_आकार(TYPE, NAME, आकार_2) \
    HASH_MAX_NAME_आकार_BEFORE ## TYPE,      \
    HASH_MAX_NAME_आकार_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(माप(NAME), HASH_MAX_NAME_आकार_BEFORE ## TYPE) - 1,
क्रमागत {
    HASHES(HASH_MAX_NAME_आकार)
    MAX_HASH_NAME_आकार
};

अटल स्थिर काष्ठा {
    स्थिर अक्षर name[MAX_HASH_NAME_आकार];
    पूर्णांक आकार;
} hashdesc[] = {
#घोषणा HASH_DESC(TYPE, NAME, आकार_2) [TYPE] = { NAME, आकार_2 },
    HASHES(HASH_DESC)
};

स्थिर अक्षर *av_hash_names(पूर्णांक i)
{
    अगर (i < 0 || i >= अंक_HASHES) वापस शून्य;
    वापस hashdesc[i].name;
}

स्थिर अक्षर *av_hash_get_name(स्थिर AVHashContext *ctx)
{
    वापस hashdesc[ctx->type].name;
}

पूर्णांक av_hash_get_आकार(स्थिर AVHashContext *ctx)
{
    वापस hashdesc[ctx->type].आकार;
}

पूर्णांक av_hash_alloc(AVHashContext **ctx, स्थिर अक्षर *name)
{
    AVHashContext *res;
    पूर्णांक i;
    *ctx = शून्य;
    क्रम (i = 0; i < अंक_HASHES; i++)
        अगर (av_strcasecmp(name, hashdesc[i].name) == 0)
            अवरोध;
    अगर (i >= अंक_HASHES) वापस AVERROR(EINVAL);
    res = av_mallocz(माप(*res));
    अगर (!res) वापस AVERROR(ENOMEM);
    res->type = i;
    चयन (i) {
    हाल MD5:     res->ctx = av_md5_alloc(); अवरोध;
    हाल MURMUR3: res->ctx = av_murmur3_alloc(); अवरोध;
    हाल RIPEMD128:
    हाल RIPEMD160:
    हाल RIPEMD256:
    हाल RIPEMD320: res->ctx = av_ripemd_alloc(); अवरोध;
    हाल SHA160:
    हाल SHA224:
    हाल SHA256:  res->ctx = av_sha_alloc(); अवरोध;
    हाल SHA512_224:
    हाल SHA512_256:
    हाल SHA384:
    हाल SHA512:  res->ctx = av_sha512_alloc(); अवरोध;
    हाल CRC32:   res->crctab = av_crc_get_table(AV_CRC_32_IEEE_LE); अवरोध;
    हाल ADLER32: अवरोध;
    }
    अगर (i != ADLER32 && i != CRC32 && !res->ctx) {
        av_free(res);
        वापस AVERROR(ENOMEM);
    }
    *ctx = res;
    वापस 0;
}

व्योम av_hash_init(AVHashContext *ctx)
{
    चयन (ctx->type) {
    हाल MD5:     av_md5_init(ctx->ctx); अवरोध;
    हाल MURMUR3: av_murmur3_init(ctx->ctx); अवरोध;
    हाल RIPEMD128: av_ripemd_init(ctx->ctx, 128); अवरोध;
    हाल RIPEMD160: av_ripemd_init(ctx->ctx, 160); अवरोध;
    हाल RIPEMD256: av_ripemd_init(ctx->ctx, 256); अवरोध;
    हाल RIPEMD320: av_ripemd_init(ctx->ctx, 320); अवरोध;
    हाल SHA160:  av_sha_init(ctx->ctx, 160); अवरोध;
    हाल SHA224:  av_sha_init(ctx->ctx, 224); अवरोध;
    हाल SHA256:  av_sha_init(ctx->ctx, 256); अवरोध;
    हाल SHA512_224:  av_sha512_init(ctx->ctx, 224); अवरोध;
    हाल SHA512_256:  av_sha512_init(ctx->ctx, 256); अवरोध;
    हाल SHA384:  av_sha512_init(ctx->ctx, 384); अवरोध;
    हाल SHA512:  av_sha512_init(ctx->ctx, 512); अवरोध;
    हाल CRC32:   ctx->crc = UINT32_MAX; अवरोध;
    हाल ADLER32: ctx->crc = 1; अवरोध;
    }
}

व्योम av_hash_update(AVHashContext *ctx, स्थिर uint8_t *src, माप_प्रकार len)
{
    चयन (ctx->type) {
    हाल MD5:     av_md5_update(ctx->ctx, src, len); अवरोध;
    हाल MURMUR3: av_murmur3_update(ctx->ctx, src, len); अवरोध;
    हाल RIPEMD128:
    हाल RIPEMD160:
    हाल RIPEMD256:
    हाल RIPEMD320: av_ripemd_update(ctx->ctx, src, len); अवरोध;
    हाल SHA160:
    हाल SHA224:
    हाल SHA256:  av_sha_update(ctx->ctx, src, len); अवरोध;
    हाल SHA512_224:
    हाल SHA512_256:
    हाल SHA384:
    हाल SHA512:  av_sha512_update(ctx->ctx, src, len); अवरोध;
    हाल CRC32:   ctx->crc = av_crc(ctx->crctab, ctx->crc, src, len); अवरोध;
    हाल ADLER32: ctx->crc = av_adler32_update(ctx->crc, src, len); अवरोध;
    }
}

व्योम av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    चयन (ctx->type) {
    हाल MD5:     av_md5_final(ctx->ctx, dst); अवरोध;
    हाल MURMUR3: av_murmur3_final(ctx->ctx, dst); अवरोध;
    हाल RIPEMD128:
    हाल RIPEMD160:
    हाल RIPEMD256:
    हाल RIPEMD320: av_ripemd_final(ctx->ctx, dst); अवरोध;
    हाल SHA160:
    हाल SHA224:
    हाल SHA256:  av_sha_final(ctx->ctx, dst); अवरोध;
    हाल SHA512_224:
    हाल SHA512_256:
    हाल SHA384:
    हाल SHA512:  av_sha512_final(ctx->ctx, dst); अवरोध;
    हाल CRC32:   AV_WB32(dst, ctx->crc ^ UINT32_MAX); अवरोध;
    हाल ADLER32: AV_WB32(dst, ctx->crc); अवरोध;
    }
}

व्योम av_hash_final_bin(काष्ठा AVHashContext *ctx, uint8_t *dst, पूर्णांक आकार)
{
    uint8_t buf[AV_HASH_MAX_आकार];
    अचिन्हित rsize = av_hash_get_आकार(ctx);

    av_hash_final(ctx, buf);
    स_नकल(dst, buf, FFMIN(आकार, rsize));
    अगर (आकार > rsize)
        स_रखो(dst + rsize, 0, आकार - rsize);
}

व्योम av_hash_final_hex(काष्ठा AVHashContext *ctx, uint8_t *dst, पूर्णांक आकार)
{
    uint8_t buf[AV_HASH_MAX_आकार];
    अचिन्हित rsize = av_hash_get_आकार(ctx), i;

    av_hash_final(ctx, buf);
    क्रम (i = 0; i < FFMIN(rsize, आकार / 2); i++)
        snprintf(dst + i * 2, आकार - i * 2, "%02x", buf[i]);
}

व्योम av_hash_final_b64(काष्ठा AVHashContext *ctx, uint8_t *dst, पूर्णांक आकार)
{
    uint8_t buf[AV_HASH_MAX_आकार], b64[AV_BASE64_आकार(AV_HASH_MAX_आकार)];
    अचिन्हित rsize = av_hash_get_आकार(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, माप(b64), buf, rsize);
    osize = AV_BASE64_आकार(rsize);
    स_नकल(dst, b64, FFMIN(osize, आकार));
    अगर (आकार < osize)
        dst[आकार - 1] = 0;
}

व्योम av_hash_freep(AVHashContext **ctx)
{
    अगर (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
