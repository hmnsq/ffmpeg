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

#अन्तर्भाव <assert.h>
#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव "hash.h"

#अन्तर्भाव "adler32.h"
#अन्तर्भाव "crc.h"
#अन्तर्भाव "md5.h"
#अन्तर्भाव "murmur3.h"
#अन्तर्भाव "ripemd.h"
#अन्तर्भाव "sha.h"
#अन्तर्भाव "sha512.h"

#अन्तर्भाव "avstring.h"
#अन्तर्भाव "base64.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "intreadwrite.h"
#अन्तर्भाव "mem.h"

// ENTRY(HASH_TYPE, HASH_NAME, HASH_SIZE)
#परिभाषय HASHES(प्रविष्टिः_2)                   \
    प्रविष्टिः_2(MD5,        "MD5",        16) \
    प्रविष्टिः_2(MURMUR3,    "murmur3",    16) \
    प्रविष्टिः_2(RIPEMD128,  "RIPEMD128",  16) \
    प्रविष्टिः_2(RIPEMD160,  "RIPEMD160",  20) \
    प्रविष्टिः_2(RIPEMD256,  "RIPEMD256",  32) \
    प्रविष्टिः_2(RIPEMD320,  "RIPEMD320",  40) \
    प्रविष्टिः_2(SHA160,     "SHA160",     20) \
    प्रविष्टिः_2(SHA224,     "SHA224",     28) \
    प्रविष्टिः_2(SHA256,     "SHA256",     32) \
    प्रविष्टिः_2(SHA512_224, "SHA512/224", 28) \
    प्रविष्टिः_2(SHA512_256, "SHA512/256", 32) \
    प्रविष्टिः_2(SHA384,     "SHA384",     48) \
    प्रविष्टिः_2(SHA512,     "SHA512",     64) \
    प्रविष्टिः_2(चक्रीयपरीक्षा_32,      "CRC32",       4) \
    प्रविष्टिः_2(ADLER32,    "adler32",     4) \

गणना hashtype {
#परिभाषय HASH_TYPE(TYPE, NAME, आकार_2) TYPE,
    HASHES(HASH_TYPE)
    अङ्कः_HASHES
};

प्रकारनिर्देश संरचना AVHashContext {
    शून्य *ctx;
    गणना hashtype type;
    ध्रुव AVCRC *crctab;
    uint32_t crc;
} AVHashContext;

#परिभाषय HASH_MAX_आकार(TYPE, NAME, आकार_2) \
    HASH_MAX_आकार_BEFORE ## TYPE,      \
    HASH_MAX_आकार_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(आकार_2, HASH_MAX_आकार_BEFORE ## TYPE) - 1,
गणना {
    HASHES(HASH_MAX_आकार)
    MAX_HASH_आकार
};
static_assert(AV_HASH_MAX_आकार >= MAX_HASH_आकार, "AV_HASH_MAX_SIZE needs to be updated!");

#परिभाषय HASH_MAX_NAME_आकार(TYPE, NAME, आकार_2) \
    HASH_MAX_NAME_आकार_BEFORE ## TYPE,      \
    HASH_MAX_NAME_आकार_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(परिमाण(NAME), HASH_MAX_NAME_आकार_BEFORE ## TYPE) - 1,
गणना {
    HASHES(HASH_MAX_NAME_आकार)
    MAX_HASH_NAME_आकार
};

स्थिर ध्रुव संरचना {
    ध्रुव वर्ण name[MAX_HASH_NAME_आकार];
    पूर्णाङ्क आकार;
} hashdesc[] = {
#परिभाषय HASH_DESC(TYPE, NAME, आकार_2) [TYPE] = { NAME, आकार_2 },
    HASHES(HASH_DESC)
};

ध्रुव वर्ण *av_hash_नामानि(पूर्णाङ्क i)
{
    यदि (i < 0 || i >= अङ्कः_HASHES) प्रत्यागम रिक्त;
    प्रत्यागम hashdesc[i].name;
}

ध्रुव वर्ण *av_hash_get_name(ध्रुव AVHashContext *ctx)
{
    प्रत्यागम hashdesc[ctx->type].name;
}

पूर्णाङ्क av_hash_get_आकार(ध्रुव AVHashContext *ctx)
{
    प्रत्यागम hashdesc[ctx->type].आकार;
}

पूर्णाङ्क av_hash_alloc(AVHashContext **ctx, ध्रुव वर्ण *name)
{
    AVHashContext *res;
    पूर्णाङ्क i;
    *ctx = रिक्त;
    प्रति (i = 0; i < अङ्कः_HASHES; i++)
        यदि (av_strcasecmp(name, hashdesc[i].name) == 0)
            भङ्ग;
    यदि (i >= अङ्कः_HASHES) प्रत्यागम AVERROR(EINVAL);
    res = av_mallocz(परिमाण(*res));
    यदि (!res) प्रत्यागम AVERROR(ENOMEM);
    res->type = i;
    विकल्प (i) {
    पक्ष MD5:     res->ctx = av_md5_alloc(); भङ्ग;
    पक्ष MURMUR3: res->ctx = av_murmur3_alloc(); भङ्ग;
    पक्ष RIPEMD128:
    पक्ष RIPEMD160:
    पक्ष RIPEMD256:
    पक्ष RIPEMD320: res->ctx = av_ripemd_alloc(); भङ्ग;
    पक्ष SHA160:
    पक्ष SHA224:
    पक्ष SHA256:  res->ctx = av_sha_alloc(); भङ्ग;
    पक्ष SHA512_224:
    पक्ष SHA512_256:
    पक्ष SHA384:
    पक्ष SHA512:  res->ctx = av_sha512_alloc(); भङ्ग;
    पक्ष चक्रीयपरीक्षा_32:   res->crctab = av_crc_get_सारणी(AV_CRC_32_IEEE_LE); भङ्ग;
    पक्ष ADLER32: भङ्ग;
    }
    यदि (i != ADLER32 && i != चक्रीयपरीक्षा_32 && !res->ctx) {
        av_free(res);
        प्रत्यागम AVERROR(ENOMEM);
    }
    *ctx = res;
    प्रत्यागम 0;
}

शून्य av_hash_init(AVHashContext *ctx)
{
    विकल्प (ctx->type) {
    पक्ष MD5:     av_md5_init(ctx->ctx); भङ्ग;
    पक्ष MURMUR3: av_murmur3_init(ctx->ctx); भङ्ग;
    पक्ष RIPEMD128: av_ripemd_init(ctx->ctx, 128); भङ्ग;
    पक्ष RIPEMD160: av_ripemd_init(ctx->ctx, 160); भङ्ग;
    पक्ष RIPEMD256: av_ripemd_init(ctx->ctx, 256); भङ्ग;
    पक्ष RIPEMD320: av_ripemd_init(ctx->ctx, 320); भङ्ग;
    पक्ष SHA160:  av_sha_init(ctx->ctx, 160); भङ्ग;
    पक्ष SHA224:  av_sha_init(ctx->ctx, 224); भङ्ग;
    पक्ष SHA256:  av_sha_init(ctx->ctx, 256); भङ्ग;
    पक्ष SHA512_224:  av_sha512_init(ctx->ctx, 224); भङ्ग;
    पक्ष SHA512_256:  av_sha512_init(ctx->ctx, 256); भङ्ग;
    पक्ष SHA384:  av_sha512_init(ctx->ctx, 384); भङ्ग;
    पक्ष SHA512:  av_sha512_init(ctx->ctx, 512); भङ्ग;
    पक्ष चक्रीयपरीक्षा_32:   ctx->crc = UINT32_MAX; भङ्ग;
    पक्ष ADLER32: ctx->crc = 1; भङ्ग;
    }
}

शून्य av_hash_update(AVHashContext *ctx, ध्रुव uint8_t *src, size_t len)
{
    विकल्प (ctx->type) {
    पक्ष MD5:     av_md5_update(ctx->ctx, src, len); भङ्ग;
    पक्ष MURMUR3: av_murmur3_update(ctx->ctx, src, len); भङ्ग;
    पक्ष RIPEMD128:
    पक्ष RIPEMD160:
    पक्ष RIPEMD256:
    पक्ष RIPEMD320: av_ripemd_update(ctx->ctx, src, len); भङ्ग;
    पक्ष SHA160:
    पक्ष SHA224:
    पक्ष SHA256:  av_sha_update(ctx->ctx, src, len); भङ्ग;
    पक्ष SHA512_224:
    पक्ष SHA512_256:
    पक्ष SHA384:
    पक्ष SHA512:  av_sha512_update(ctx->ctx, src, len); भङ्ग;
    पक्ष चक्रीयपरीक्षा_32:   ctx->crc = av_crc(ctx->crctab, ctx->crc, src, len); भङ्ग;
    पक्ष ADLER32: ctx->crc = av_adler32_update(ctx->crc, src, len); भङ्ग;
    }
}

शून्य av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    विकल्प (ctx->type) {
    पक्ष MD5:     av_md5_final(ctx->ctx, dst); भङ्ग;
    पक्ष MURMUR3: av_murmur3_final(ctx->ctx, dst); भङ्ग;
    पक्ष RIPEMD128:
    पक्ष RIPEMD160:
    पक्ष RIPEMD256:
    पक्ष RIPEMD320: av_ripemd_final(ctx->ctx, dst); भङ्ग;
    पक्ष SHA160:
    पक्ष SHA224:
    पक्ष SHA256:  av_sha_final(ctx->ctx, dst); भङ्ग;
    पक्ष SHA512_224:
    पक्ष SHA512_256:
    पक्ष SHA384:
    पक्ष SHA512:  av_sha512_final(ctx->ctx, dst); भङ्ग;
    पक्ष चक्रीयपरीक्षा_32:   AV_WB32(dst, ctx->crc ^ UINT32_MAX); भङ्ग;
    पक्ष ADLER32: AV_WB32(dst, ctx->crc); भङ्ग;
    }
}

शून्य av_hash_final_bin(संरचना AVHashContext *ctx, uint8_t *dst, पूर्णाङ्क आकार)
{
    uint8_t buf[AV_HASH_MAX_आकार];
    अचिह्नित rsize = av_hash_get_आकार(ctx);

    av_hash_final(ctx, buf);
    स्मृतिं_प्रतिलिख(dst, buf, FFMIN(आकार, rsize));
    यदि (आकार > rsize)
        स्मृतिं_पूरय(dst + rsize, 0, आकार - rsize);
}

शून्य av_hash_final_hex(संरचना AVHashContext *ctx, uint8_t *dst, पूर्णाङ्क आकार)
{
    uint8_t buf[AV_HASH_MAX_आकार];
    अचिह्नित rsize = av_hash_get_आकार(ctx), i;

    av_hash_final(ctx, buf);
    प्रति (i = 0; i < FFMIN(rsize, आकार / 2); i++)
        snprintf(dst + i * 2, आकार - i * 2, "%02x", buf[i]);
}

शून्य av_hash_final_b64(संरचना AVHashContext *ctx, uint8_t *dst, पूर्णाङ्क आकार)
{
    uint8_t buf[AV_HASH_MAX_आकार], b64[AV_BASE64_आकार(AV_HASH_MAX_आकार)];
    अचिह्नित rsize = av_hash_get_आकार(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, परिमाण(b64), buf, rsize);
    osize = AV_BASE64_आकार(rsize);
    स्मृतिं_प्रतिलिख(dst, b64, FFMIN(osize, आकार));
    यदि (आकार < osize)
        dst[आकार - 1] = 0;
}

शून्य av_hash_freep(AVHashContext **ctx)
{
    यदि (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
