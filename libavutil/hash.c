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
#تعریف_کرو HASHES(اندراج_3)                   \
    اندراج_3(MD5,        "MD5",        16) \
    اندراج_3(MURMUR3,    "murmur3",    16) \
    اندراج_3(RIPEMD128,  "RIPEMD128",  16) \
    اندراج_3(RIPEMD160,  "RIPEMD160",  20) \
    اندراج_3(RIPEMD256,  "RIPEMD256",  32) \
    اندراج_3(RIPEMD320,  "RIPEMD320",  40) \
    اندراج_3(SHA160,     "SHA160",     20) \
    اندراج_3(SHA224,     "SHA224",     28) \
    اندراج_3(SHA256,     "SHA256",     32) \
    اندراج_3(SHA512_224, "SHA512/224", 28) \
    اندراج_3(SHA512_256, "SHA512/256", 32) \
    اندراج_3(SHA384,     "SHA384",     48) \
    اندراج_3(SHA512,     "SHA512",     64) \
    اندراج_3(چکری_جانچ_32,      "CRC32",       4) \
    اندراج_3(ADLER32,    "adler32",     4) \

شمار hashtype {
#تعریف_کرو HASH_TYPE(TYPE, NAME, سائز_2) TYPE,
    HASHES(HASH_TYPE)
    عدد_HASHES
};

قسمتعریف ساخت AVHashContext {
    خالی *ctx;
    شمار hashtype type;
    ثابت AVCRC *crctab;
    uint32_t چکری_جانچ;
} AVHashContext;

#تعریف_کرو HASH_MAX_سائز(TYPE, NAME, سائز_2) \
    HASH_MAX_سائز_BEFORE ## TYPE,      \
    HASH_MAX_سائز_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(سائز_2, HASH_MAX_سائز_BEFORE ## TYPE) - 1,
شمار {
    HASHES(HASH_MAX_سائز)
    MAX_HASH_سائز
};
static_assert(AV_HASH_MAX_سائز >= MAX_HASH_سائز, "AV_HASH_MAX_SIZE needs to be updated!");

#تعریف_کرو HASH_MAX_NAME_سائز(TYPE, NAME, سائز_2) \
    HASH_MAX_NAME_سائز_BEFORE ## TYPE,      \
    HASH_MAX_NAME_سائز_UNTIL ## TYPE ## _MINUS_ONE = FFMAX(حجم(NAME), HASH_MAX_NAME_سائز_BEFORE ## TYPE) - 1,
شمار {
    HASHES(HASH_MAX_NAME_سائز)
    MAX_HASH_NAME_سائز
};

ساکن ثابت ساخت {
    ثابت حرف name[MAX_HASH_NAME_سائز];
    صحیح سائز;
} hashdesc[] = {
#تعریف_کرو HASH_DESC(TYPE, NAME, سائز_2) [TYPE] = { NAME, سائز_2 },
    HASHES(HASH_DESC)
};

ثابت حرف *av_hash_نام(صحیح i)
{
    اگر (i < 0 || i >= عدد_HASHES) واپس تہی;
    واپس hashdesc[i].name;
}

ثابت حرف *av_hash_get_name(ثابت AVHashContext *ctx)
{
    واپس hashdesc[ctx->type].name;
}

صحیح av_hash_get_سائز(ثابت AVHashContext *ctx)
{
    واپس hashdesc[ctx->type].سائز;
}

صحیح av_hash_alloc(AVHashContext **ctx, ثابت حرف *name)
{
    AVHashContext *res;
    صحیح i;
    *ctx = تہی;
    برائے (i = 0; i < عدد_HASHES; i++)
        اگر (av_strcasecmp(name, hashdesc[i].name) == 0)
            توڑو;
    اگر (i >= عدد_HASHES) واپس AVERROR(EINVAL);
    res = av_mallocz(حجم(*res));
    اگر (!res) واپس AVERROR(ENOMEM);
    res->type = i;
    انتخاب (i) {
    حالت MD5:     res->ctx = av_md5_alloc(); توڑو;
    حالت MURMUR3: res->ctx = av_murmur3_alloc(); توڑو;
    حالت RIPEMD128:
    حالت RIPEMD160:
    حالت RIPEMD256:
    حالت RIPEMD320: res->ctx = av_ripemd_alloc(); توڑو;
    حالت SHA160:
    حالت SHA224:
    حالت SHA256:  res->ctx = av_sha_alloc(); توڑو;
    حالت SHA512_224:
    حالت SHA512_256:
    حالت SHA384:
    حالت SHA512:  res->ctx = av_sha512_alloc(); توڑو;
    حالت چکری_جانچ_32:   res->crctab = av_چکری_جانچ_get_جدول(AV_چکری_جانچ_32_IEEE_LE); توڑو;
    حالت ADLER32: توڑو;
    }
    اگر (i != ADLER32 && i != چکری_جانچ_32 && !res->ctx) {
        av_free(res);
        واپس AVERROR(ENOMEM);
    }
    *ctx = res;
    واپس 0;
}

خالی av_hash_init(AVHashContext *ctx)
{
    انتخاب (ctx->type) {
    حالت MD5:     av_md5_init(ctx->ctx); توڑو;
    حالت MURMUR3: av_murmur3_init(ctx->ctx); توڑو;
    حالت RIPEMD128: av_ripemd_init(ctx->ctx, 128); توڑو;
    حالت RIPEMD160: av_ripemd_init(ctx->ctx, 160); توڑو;
    حالت RIPEMD256: av_ripemd_init(ctx->ctx, 256); توڑو;
    حالت RIPEMD320: av_ripemd_init(ctx->ctx, 320); توڑو;
    حالت SHA160:  av_sha_init(ctx->ctx, 160); توڑو;
    حالت SHA224:  av_sha_init(ctx->ctx, 224); توڑو;
    حالت SHA256:  av_sha_init(ctx->ctx, 256); توڑو;
    حالت SHA512_224:  av_sha512_init(ctx->ctx, 224); توڑو;
    حالت SHA512_256:  av_sha512_init(ctx->ctx, 256); توڑو;
    حالت SHA384:  av_sha512_init(ctx->ctx, 384); توڑو;
    حالت SHA512:  av_sha512_init(ctx->ctx, 512); توڑو;
    حالت چکری_جانچ_32:   ctx->چکری_جانچ = UINT32_MAX; توڑو;
    حالت ADLER32: ctx->چکری_جانچ = 1; توڑو;
    }
}

خالی av_hash_update(AVHashContext *ctx, ثابت uint8_t *src, size_t len)
{
    انتخاب (ctx->type) {
    حالت MD5:     av_md5_update(ctx->ctx, src, len); توڑو;
    حالت MURMUR3: av_murmur3_update(ctx->ctx, src, len); توڑو;
    حالت RIPEMD128:
    حالت RIPEMD160:
    حالت RIPEMD256:
    حالت RIPEMD320: av_ripemd_update(ctx->ctx, src, len); توڑو;
    حالت SHA160:
    حالت SHA224:
    حالت SHA256:  av_sha_update(ctx->ctx, src, len); توڑو;
    حالت SHA512_224:
    حالت SHA512_256:
    حالت SHA384:
    حالت SHA512:  av_sha512_update(ctx->ctx, src, len); توڑو;
    حالت چکری_جانچ_32:   ctx->چکری_جانچ = av_چکری_جانچ(ctx->crctab, ctx->چکری_جانچ, src, len); توڑو;
    حالت ADLER32: ctx->چکری_جانچ = av_adler32_update(ctx->چکری_جانچ, src, len); توڑو;
    }
}

خالی av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    انتخاب (ctx->type) {
    حالت MD5:     av_md5_final(ctx->ctx, dst); توڑو;
    حالت MURMUR3: av_murmur3_final(ctx->ctx, dst); توڑو;
    حالت RIPEMD128:
    حالت RIPEMD160:
    حالت RIPEMD256:
    حالت RIPEMD320: av_ripemd_final(ctx->ctx, dst); توڑو;
    حالت SHA160:
    حالت SHA224:
    حالت SHA256:  av_sha_final(ctx->ctx, dst); توڑو;
    حالت SHA512_224:
    حالت SHA512_256:
    حالت SHA384:
    حالت SHA512:  av_sha512_final(ctx->ctx, dst); توڑو;
    حالت چکری_جانچ_32:   AV_WB32(dst, ctx->چکری_جانچ ^ UINT32_MAX); توڑو;
    حالت ADLER32: AV_WB32(dst, ctx->چکری_جانچ); توڑو;
    }
}

خالی av_hash_final_bin(ساخت AVHashContext *ctx, uint8_t *dst, صحیح سائز)
{
    uint8_t buf[AV_HASH_MAX_سائز];
    غیرعلامتی rsize = av_hash_get_سائز(ctx);

    av_hash_final(ctx, buf);
    حافظہ_نقل(dst, buf, FFMIN(سائز, rsize));
    اگر (سائز > rsize)
        memset(dst + rsize, 0, سائز - rsize);
}

خالی av_hash_final_hex(ساخت AVHashContext *ctx, uint8_t *dst, صحیح سائز)
{
    uint8_t buf[AV_HASH_MAX_سائز];
    غیرعلامتی rsize = av_hash_get_سائز(ctx), i;

    av_hash_final(ctx, buf);
    برائے (i = 0; i < FFMIN(rsize, سائز / 2); i++)
        snprintf(dst + i * 2, سائز - i * 2, "%02x", buf[i]);
}

خالی av_hash_final_b64(ساخت AVHashContext *ctx, uint8_t *dst, صحیح سائز)
{
    uint8_t buf[AV_HASH_MAX_سائز], b64[AV_BASE64_سائز(AV_HASH_MAX_سائز)];
    غیرعلامتی rsize = av_hash_get_سائز(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, حجم(b64), buf, rsize);
    osize = AV_BASE64_سائز(rsize);
    حافظہ_نقل(dst, b64, FFMIN(osize, سائز));
    اگر (سائز < osize)
        dst[سائز - 1] = 0;
}

خالی av_hash_freep(AVHashContext **ctx)
{
    اگر (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
