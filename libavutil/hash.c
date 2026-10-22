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

#అన్తర్భావ <assert.h>
#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ "hash.h"

#అన్తర్భావ "adler32.h"
#అన్తర్భావ "crc.h"
#అన్తర్భావ "md5.h"
#అన్తర్భావ "murmur3.h"
#అన్తర్భావ "ripemd.h"
#అన్తర్భావ "sha.h"
#అన్తర్భావ "sha512.h"

#అన్తర్భావ "avstring.h"
#అన్తర్భావ "base64.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "intreadwrite.h"
#అన్తర్భావ "mem.h"

// ENTRY(HASH_TYPE, HASH_NAME, HASH_SIZE)
#నిర్వచించు HASHES(నమోదు_3)                   \
    నమోదు_3(MD5,        "MD5",        16) \
    నమోదు_3(MURMUR3,    "murmur3",    16) \
    నమోదు_3(RIPEMD128,  "RIPEMD128",  16) \
    నమోదు_3(RIPEMD160,  "RIPEMD160",  20) \
    నమోదు_3(RIPEMD256,  "RIPEMD256",  32) \
    నమోదు_3(RIPEMD320,  "RIPEMD320",  40) \
    నమోదు_3(SHA160,     "SHA160",     20) \
    నమోదు_3(SHA224,     "SHA224",     28) \
    నమోదు_3(SHA256,     "SHA256",     32) \
    నమోదు_3(SHA512_224, "SHA512/224", 28) \
    నమోదు_3(SHA512_256, "SHA512/256", 32) \
    నమోదు_3(SHA384,     "SHA384",     48) \
    నమోదు_3(SHA512,     "SHA512",     64) \
    నమోదు_3(చక్రీయ_తనిఖీ_32,      "CRC32",       4) \
    నమోదు_3(ADLER32,    "adler32",     4) \

గణన hashtype {
#నిర్వచించు HASH_TYPE(TYPE, NAME, కొలత_2) TYPE,
    HASHES(HASH_TYPE)
    అంకె_HASHES
};

రకనిర్వచనం నిర్మాణం AVHashContext {
    శూన్య *ctx;
    గణన hashtype type;
    స్థిరరాశి AVCRC *crctab;
    uint32_t చక్రీయ_తనిఖీ;
} AVHashContext;

#నిర్వచించు HASH_MAX_కొలత(TYPE, NAME, కొలత_2) \
    HASH_MAX_కొలత_BEFORE ## TYPE,      \
    HASH_MAX_కొలత_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(కొలత_2, HASH_MAX_కొలత_BEFORE ## TYPE) - 1,
గణన {
    HASHES(HASH_MAX_కొలత)
    MAX_HASH_కొలత
};
static_assert(AV_HASH_MAX_కొలత >= MAX_HASH_కొలత, "AV_HASH_MAX_SIZE needs to be updated!");

#నిర్వచించు HASH_MAX_NAME_కొలత(TYPE, NAME, కొలత_2) \
    HASH_MAX_NAME_కొలత_BEFORE ## TYPE,      \
    HASH_MAX_NAME_కొలత_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(పరిమాణం(NAME), HASH_MAX_NAME_కొలత_BEFORE ## TYPE) - 1,
గణన {
    HASHES(HASH_MAX_NAME_కొలత)
    MAX_HASH_NAME_కొలత
};

స్థిర స్థిరరాశి నిర్మాణం {
    స్థిరరాశి అక్షరం name[MAX_HASH_NAME_కొలత];
    పూర్ణాంకం కొలత;
} hashdesc[] = {
#నిర్వచించు HASH_DESC(TYPE, NAME, కొలత_2) [TYPE] = { NAME, కొలత_2 },
    HASHES(HASH_DESC)
};

స్థిరరాశి అక్షరం *av_hash_పేర్లు(పూర్ణాంకం i)
{
    ఒకవేళ (i < 0 || i >= అంకె_HASHES) తిరిగి ఖాళీ;
    తిరిగి hashdesc[i].name;
}

స్థిరరాశి అక్షరం *av_hash_get_name(స్థిరరాశి AVHashContext *ctx)
{
    తిరిగి hashdesc[ctx->type].name;
}

పూర్ణాంకం av_hash_get_కొలత(స్థిరరాశి AVHashContext *ctx)
{
    తిరిగి hashdesc[ctx->type].కొలత;
}

పూర్ణాంకం av_hash_alloc(AVHashContext **ctx, స్థిరరాశి అక్షరం *name)
{
    AVHashContext *res;
    పూర్ణాంకం i;
    *ctx = ఖాళీ;
    కొరకు (i = 0; i < అంకె_HASHES; i++)
        ఒకవేళ (av_strcasecmp(name, hashdesc[i].name) == 0)
            ఆపు;
    ఒకవేళ (i >= అంకె_HASHES) తిరిగి AVERROR(EINVAL);
    res = av_mallocz(పరిమాణం(*res));
    ఒకవేళ (!res) తిరిగి AVERROR(ENOMEM);
    res->type = i;
    ఎంపిక (i) {
    స్థితి MD5:     res->ctx = av_md5_alloc(); ఆపు;
    స్థితి MURMUR3: res->ctx = av_murmur3_alloc(); ఆపు;
    స్థితి RIPEMD128:
    స్థితి RIPEMD160:
    స్థితి RIPEMD256:
    స్థితి RIPEMD320: res->ctx = av_ripemd_alloc(); ఆపు;
    స్థితి SHA160:
    స్థితి SHA224:
    స్థితి SHA256:  res->ctx = av_sha_alloc(); ఆపు;
    స్థితి SHA512_224:
    స్థితి SHA512_256:
    స్థితి SHA384:
    స్థితి SHA512:  res->ctx = av_sha512_alloc(); ఆపు;
    స్థితి చక్రీయ_తనిఖీ_32:   res->crctab = av_చక్రీయ_తనిఖీ_get_పట్టిక(AV_చక్రీయ_తనిఖీ_32_IEEE_LE); ఆపు;
    స్థితి ADLER32: ఆపు;
    }
    ఒకవేళ (i != ADLER32 && i != చక్రీయ_తనిఖీ_32 && !res->ctx) {
        av_free(res);
        తిరిగి AVERROR(ENOMEM);
    }
    *ctx = res;
    తిరిగి 0;
}

శూన్య av_hash_init(AVHashContext *ctx)
{
    ఎంపిక (ctx->type) {
    స్థితి MD5:     av_md5_init(ctx->ctx); ఆపు;
    స్థితి MURMUR3: av_murmur3_init(ctx->ctx); ఆపు;
    స్థితి RIPEMD128: av_ripemd_init(ctx->ctx, 128); ఆపు;
    స్థితి RIPEMD160: av_ripemd_init(ctx->ctx, 160); ఆపు;
    స్థితి RIPEMD256: av_ripemd_init(ctx->ctx, 256); ఆపు;
    స్థితి RIPEMD320: av_ripemd_init(ctx->ctx, 320); ఆపు;
    స్థితి SHA160:  av_sha_init(ctx->ctx, 160); ఆపు;
    స్థితి SHA224:  av_sha_init(ctx->ctx, 224); ఆపు;
    స్థితి SHA256:  av_sha_init(ctx->ctx, 256); ఆపు;
    స్థితి SHA512_224:  av_sha512_init(ctx->ctx, 224); ఆపు;
    స్థితి SHA512_256:  av_sha512_init(ctx->ctx, 256); ఆపు;
    స్థితి SHA384:  av_sha512_init(ctx->ctx, 384); ఆపు;
    స్థితి SHA512:  av_sha512_init(ctx->ctx, 512); ఆపు;
    స్థితి చక్రీయ_తనిఖీ_32:   ctx->చక్రీయ_తనిఖీ = UINT32_MAX; ఆపు;
    స్థితి ADLER32: ctx->చక్రీయ_తనిఖీ = 1; ఆపు;
    }
}

శూన్య av_hash_update(AVHashContext *ctx, స్థిరరాశి uint8_t *src, size_t len)
{
    ఎంపిక (ctx->type) {
    స్థితి MD5:     av_md5_update(ctx->ctx, src, len); ఆపు;
    స్థితి MURMUR3: av_murmur3_update(ctx->ctx, src, len); ఆపు;
    స్థితి RIPEMD128:
    స్థితి RIPEMD160:
    స్థితి RIPEMD256:
    స్థితి RIPEMD320: av_ripemd_update(ctx->ctx, src, len); ఆపు;
    స్థితి SHA160:
    స్థితి SHA224:
    స్థితి SHA256:  av_sha_update(ctx->ctx, src, len); ఆపు;
    స్థితి SHA512_224:
    స్థితి SHA512_256:
    స్థితి SHA384:
    స్థితి SHA512:  av_sha512_update(ctx->ctx, src, len); ఆపు;
    స్థితి చక్రీయ_తనిఖీ_32:   ctx->చక్రీయ_తనిఖీ = av_చక్రీయ_తనిఖీ(ctx->crctab, ctx->చక్రీయ_తనిఖీ, src, len); ఆపు;
    స్థితి ADLER32: ctx->చక్రీయ_తనిఖీ = av_adler32_update(ctx->చక్రీయ_తనిఖీ, src, len); ఆపు;
    }
}

శూన్య av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    ఎంపిక (ctx->type) {
    స్థితి MD5:     av_md5_final(ctx->ctx, dst); ఆపు;
    స్థితి MURMUR3: av_murmur3_final(ctx->ctx, dst); ఆపు;
    స్థితి RIPEMD128:
    స్థితి RIPEMD160:
    స్థితి RIPEMD256:
    స్థితి RIPEMD320: av_ripemd_final(ctx->ctx, dst); ఆపు;
    స్థితి SHA160:
    స్థితి SHA224:
    స్థితి SHA256:  av_sha_final(ctx->ctx, dst); ఆపు;
    స్థితి SHA512_224:
    స్థితి SHA512_256:
    స్థితి SHA384:
    స్థితి SHA512:  av_sha512_final(ctx->ctx, dst); ఆపు;
    స్థితి చక్రీయ_తనిఖీ_32:   AV_WB32(dst, ctx->చక్రీయ_తనిఖీ ^ UINT32_MAX); ఆపు;
    స్థితి ADLER32: AV_WB32(dst, ctx->చక్రీయ_తనిఖీ); ఆపు;
    }
}

శూన్య av_hash_final_bin(నిర్మాణం AVHashContext *ctx, uint8_t *dst, పూర్ణాంకం కొలత)
{
    uint8_t buf[AV_HASH_MAX_కొలత];
    గుర్తులేని rsize = av_hash_get_కొలత(ctx);

    av_hash_final(ctx, buf);
    జ్ఞాపకం_నకలు(dst, buf, FFMIN(కొలత, rsize));
    ఒకవేళ (కొలత > rsize)
        memset(dst + rsize, 0, కొలత - rsize);
}

శూన్య av_hash_final_hex(నిర్మాణం AVHashContext *ctx, uint8_t *dst, పూర్ణాంకం కొలత)
{
    uint8_t buf[AV_HASH_MAX_కొలత];
    గుర్తులేని rsize = av_hash_get_కొలత(ctx), i;

    av_hash_final(ctx, buf);
    కొరకు (i = 0; i < FFMIN(rsize, కొలత / 2); i++)
        snprintf(dst + i * 2, కొలత - i * 2, "%02x", buf[i]);
}

శూన్య av_hash_final_b64(నిర్మాణం AVHashContext *ctx, uint8_t *dst, పూర్ణాంకం కొలత)
{
    uint8_t buf[AV_HASH_MAX_కొలత], b64[AV_BASE64_కొలత(AV_HASH_MAX_కొలత)];
    గుర్తులేని rsize = av_hash_get_కొలత(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, పరిమాణం(b64), buf, rsize);
    osize = AV_BASE64_కొలత(rsize);
    జ్ఞాపకం_నకలు(dst, b64, FFMIN(osize, కొలత));
    ఒకవేళ (కొలత < osize)
        dst[కొలత - 1] = 0;
}

శూన్య av_hash_freep(AVHashContext **ctx)
{
    ఒకవేళ (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
