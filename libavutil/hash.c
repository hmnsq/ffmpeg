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

#ضمن <assert.h>
#ضمن <stddef.h>
#ضمن <stdint.h>
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن "hash.h"

#ضمن "adler32.h"
#ضمن "crc.h"
#ضمن "md5.h"
#ضمن "murmur3.h"
#ضمن "ripemd.h"
#ضمن "sha.h"
#ضمن "sha512.h"

#ضمن "avstring.h"
#ضمن "base64.h"
#ضمن "error.h"
#ضمن "intreadwrite.h"
#ضمن "mem.h"

// ENTRY(HASH_TYPE, HASH_NAME, HASH_SIZE)
#تعریف_کرو HASHES(اندراج_2)                   \
    اندراج_2(MD5,        "MD5",        16) \
    اندراج_2(MURMUR3,    "murmur3",    16) \
    اندراج_2(RIPEMD128,  "RIPEMD128",  16) \
    اندراج_2(RIPEMD160,  "RIPEMD160",  20) \
    اندراج_2(RIPEMD256,  "RIPEMD256",  32) \
    اندراج_2(RIPEMD320,  "RIPEMD320",  40) \
    اندراج_2(SHA160,     "SHA160",     20) \
    اندراج_2(SHA224,     "SHA224",     28) \
    اندراج_2(SHA256,     "SHA256",     32) \
    اندراج_2(SHA512_224, "SHA512/224", 28) \
    اندراج_2(SHA512_256, "SHA512/256", 32) \
    اندراج_2(SHA384,     "SHA384",     48) \
    اندراج_2(SHA512,     "SHA512",     64) \
    اندراج_2(چکری_جانچ_32,      "CRC32",       4) \
    اندراج_2(ADLER32,    "adler32",     4) \

تعداد hashtype {
#تعریف_کرو HASH_TYPE(TYPE, NAME, ناپ_2) TYPE,
    HASHES(HASH_TYPE)
    عدد_HASHES
};

تعريفنوع بنية AVHashContext {
    فراغ *ctx;
    تعداد hashtype type;
    ثابت AVCRC *crctab;
    uint32_t چکری_جانچ;
} AVHashContext;

#تعریف_کرو HASH_MAX_ناپ(TYPE, NAME, ناپ_2) \
    HASH_MAX_ناپ_BEFORE ## TYPE,      \
    HASH_MAX_ناپ_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(ناپ_2, HASH_MAX_ناپ_BEFORE ## TYPE) - 1,
تعداد {
    HASHES(HASH_MAX_ناپ)
    MAX_HASH_ناپ
};
static_assert(AV_HASH_MAX_ناپ >= MAX_HASH_ناپ, "AV_HASH_MAX_SIZE needs to be updated!");

#تعریف_کرو HASH_MAX_NAME_ناپ(TYPE, NAME, ناپ_2) \
    HASH_MAX_NAME_ناپ_BEFORE ## TYPE,      \
    HASH_MAX_NAME_ناپ_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(حجم(NAME), HASH_MAX_NAME_ناپ_BEFORE ## TYPE) - 1,
تعداد {
    HASHES(HASH_MAX_NAME_ناپ)
    MAX_HASH_NAME_ناپ
};

ساكن ثابت بنية {
    ثابت حرف name[MAX_HASH_NAME_ناپ];
    صحيح ناپ;
} hashdesc[] = {
#تعریف_کرو HASH_DESC(TYPE, NAME, ناپ_2) [TYPE] = { NAME, ناپ_2 },
    HASHES(HASH_DESC)
};

ثابت حرف *av_hash_ناں(صحيح i)
{
    إذا (i < 0 || i >= عدد_HASHES) أرجع عدم;
    أرجع hashdesc[i].name;
}

ثابت حرف *av_hash_get_name(ثابت AVHashContext *ctx)
{
    أرجع hashdesc[ctx->type].name;
}

صحيح av_hash_get_ناپ(ثابت AVHashContext *ctx)
{
    أرجع hashdesc[ctx->type].ناپ;
}

صحيح av_hash_alloc(AVHashContext **ctx, ثابت حرف *name)
{
    AVHashContext *res;
    صحيح i;
    *ctx = عدم;
    لكل (i = 0; i < عدد_HASHES; i++)
        إذا (av_strcasecmp(name, hashdesc[i].name) == 0)
            اكسر;
    إذا (i >= عدد_HASHES) أرجع AVERROR(EINVAL);
    res = av_mallocz(حجم(*res));
    إذا (!res) أرجع AVERROR(ENOMEM);
    res->type = i;
    بدل (i) {
    حالة MD5:     res->ctx = av_md5_alloc(); اكسر;
    حالة MURMUR3: res->ctx = av_murmur3_alloc(); اكسر;
    حالة RIPEMD128:
    حالة RIPEMD160:
    حالة RIPEMD256:
    حالة RIPEMD320: res->ctx = av_ripemd_alloc(); اكسر;
    حالة SHA160:
    حالة SHA224:
    حالة SHA256:  res->ctx = av_sha_alloc(); اكسر;
    حالة SHA512_224:
    حالة SHA512_256:
    حالة SHA384:
    حالة SHA512:  res->ctx = av_sha512_alloc(); اكسر;
    حالة چکری_جانچ_32:   res->crctab = av_چکری_جانچ_get_جدول(AV_چکری_جانچ_32_IEEE_LE); اكسر;
    حالة ADLER32: اكسر;
    }
    إذا (i != ADLER32 && i != چکری_جانچ_32 && !res->ctx) {
        av_free(res);
        أرجع AVERROR(ENOMEM);
    }
    *ctx = res;
    أرجع 0;
}

فراغ av_hash_init(AVHashContext *ctx)
{
    بدل (ctx->type) {
    حالة MD5:     av_md5_init(ctx->ctx); اكسر;
    حالة MURMUR3: av_murmur3_init(ctx->ctx); اكسر;
    حالة RIPEMD128: av_ripemd_init(ctx->ctx, 128); اكسر;
    حالة RIPEMD160: av_ripemd_init(ctx->ctx, 160); اكسر;
    حالة RIPEMD256: av_ripemd_init(ctx->ctx, 256); اكسر;
    حالة RIPEMD320: av_ripemd_init(ctx->ctx, 320); اكسر;
    حالة SHA160:  av_sha_init(ctx->ctx, 160); اكسر;
    حالة SHA224:  av_sha_init(ctx->ctx, 224); اكسر;
    حالة SHA256:  av_sha_init(ctx->ctx, 256); اكسر;
    حالة SHA512_224:  av_sha512_init(ctx->ctx, 224); اكسر;
    حالة SHA512_256:  av_sha512_init(ctx->ctx, 256); اكسر;
    حالة SHA384:  av_sha512_init(ctx->ctx, 384); اكسر;
    حالة SHA512:  av_sha512_init(ctx->ctx, 512); اكسر;
    حالة چکری_جانچ_32:   ctx->چکری_جانچ = UINT32_MAX; اكسر;
    حالة ADLER32: ctx->چکری_جانچ = 1; اكسر;
    }
}

فراغ av_hash_update(AVHashContext *ctx, ثابت uint8_t *src, size_t len)
{
    بدل (ctx->type) {
    حالة MD5:     av_md5_update(ctx->ctx, src, len); اكسر;
    حالة MURMUR3: av_murmur3_update(ctx->ctx, src, len); اكسر;
    حالة RIPEMD128:
    حالة RIPEMD160:
    حالة RIPEMD256:
    حالة RIPEMD320: av_ripemd_update(ctx->ctx, src, len); اكسر;
    حالة SHA160:
    حالة SHA224:
    حالة SHA256:  av_sha_update(ctx->ctx, src, len); اكسر;
    حالة SHA512_224:
    حالة SHA512_256:
    حالة SHA384:
    حالة SHA512:  av_sha512_update(ctx->ctx, src, len); اكسر;
    حالة چکری_جانچ_32:   ctx->چکری_جانچ = av_چکری_جانچ(ctx->crctab, ctx->چکری_جانچ, src, len); اكسر;
    حالة ADLER32: ctx->چکری_جانچ = av_adler32_update(ctx->چکری_جانچ, src, len); اكسر;
    }
}

فراغ av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    بدل (ctx->type) {
    حالة MD5:     av_md5_final(ctx->ctx, dst); اكسر;
    حالة MURMUR3: av_murmur3_final(ctx->ctx, dst); اكسر;
    حالة RIPEMD128:
    حالة RIPEMD160:
    حالة RIPEMD256:
    حالة RIPEMD320: av_ripemd_final(ctx->ctx, dst); اكسر;
    حالة SHA160:
    حالة SHA224:
    حالة SHA256:  av_sha_final(ctx->ctx, dst); اكسر;
    حالة SHA512_224:
    حالة SHA512_256:
    حالة SHA384:
    حالة SHA512:  av_sha512_final(ctx->ctx, dst); اكسر;
    حالة چکری_جانچ_32:   AV_WB32(dst, ctx->چکری_جانچ ^ UINT32_MAX); اكسر;
    حالة ADLER32: AV_WB32(dst, ctx->چکری_جانچ); اكسر;
    }
}

فراغ av_hash_final_bin(بنية AVHashContext *ctx, uint8_t *dst, صحيح ناپ)
{
    uint8_t buf[AV_HASH_MAX_ناپ];
    بنانشانی rsize = av_hash_get_ناپ(ctx);

    av_hash_final(ctx, buf);
    حافظہ_نقل(dst, buf, FFMIN(ناپ, rsize));
    إذا (ناپ > rsize)
        memset(dst + rsize, 0, ناپ - rsize);
}

فراغ av_hash_final_hex(بنية AVHashContext *ctx, uint8_t *dst, صحيح ناپ)
{
    uint8_t buf[AV_HASH_MAX_ناپ];
    بنانشانی rsize = av_hash_get_ناپ(ctx), i;

    av_hash_final(ctx, buf);
    لكل (i = 0; i < FFMIN(rsize, ناپ / 2); i++)
        snprintf(dst + i * 2, ناپ - i * 2, "%02x", buf[i]);
}

فراغ av_hash_final_b64(بنية AVHashContext *ctx, uint8_t *dst, صحيح ناپ)
{
    uint8_t buf[AV_HASH_MAX_ناپ], b64[AV_BASE64_ناپ(AV_HASH_MAX_ناپ)];
    بنانشانی rsize = av_hash_get_ناپ(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, حجم(b64), buf, rsize);
    osize = AV_BASE64_ناپ(rsize);
    حافظہ_نقل(dst, b64, FFMIN(osize, ناپ));
    إذا (ناپ < osize)
        dst[ناپ - 1] = 0;
}

فراغ av_hash_freep(AVHashContext **ctx)
{
    إذا (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
