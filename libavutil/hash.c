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

#അന്തര്ഭാവ <assert.h>
#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ "hash.h"

#അന്തര്ഭാവ "adler32.h"
#അന്തര്ഭാവ "crc.h"
#അന്തര്ഭാവ "md5.h"
#അന്തര്ഭാവ "murmur3.h"
#അന്തര്ഭാവ "ripemd.h"
#അന്തര്ഭാവ "sha.h"
#അന്തര്ഭാവ "sha512.h"

#അന്തര്ഭാവ "avstring.h"
#അന്തര്ഭാവ "base64.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "intreadwrite.h"
#അന്തര്ഭാവ "mem.h"

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

എണ്ണൽ hashtype {
#define HASH_TYPE(TYPE, NAME, SIZE) TYPE,
    HASHES(HASH_TYPE)
    അക്കം_HASHES
};

തരനിർവചനം ഘടന AVHashContext {
    ശൂന്യം *ctx;
    എണ്ണൽ hashtype type;
    സ്ഥിരം AVCRC *crctab;
    uint32_t crc;
} AVHashContext;

#define HASH_MAX_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(SIZE, HASH_MAX_SIZE_BEFORE_ ## TYPE) - 1,
എണ്ണൽ {
    HASHES(HASH_MAX_SIZE)
    MAX_HASH_SIZE
};
static_assert(AV_HASH_MAX_SIZE >= MAX_HASH_SIZE, "AV_HASH_MAX_SIZE needs to be updated!");

#define HASH_MAX_NAME_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_NAME_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(വലുപ്പം(NAME), HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE) - 1,
എണ്ണൽ {
    HASHES(HASH_MAX_NAME_SIZE)
    MAX_HASH_NAME_SIZE
};

സ്ഥിതം സ്ഥിരം ഘടന {
    സ്ഥിരം അക്ഷരം name[MAX_HASH_NAME_SIZE];
    പൂർണ്ണസംഖ്യ size;
} hashdesc[] = {
#define HASH_DESC(TYPE, NAME, SIZE) [TYPE] = { NAME, SIZE },
    HASHES(HASH_DESC)
};

സ്ഥിരം അക്ഷരം *av_hash_names(പൂർണ്ണസംഖ്യ i)
{
    എങ്കിൽ (i < 0 || i >= അക്കം_HASHES) തിരികെ ശൂന്യ;
    തിരികെ hashdesc[i].name;
}

സ്ഥിരം അക്ഷരം *av_hash_get_name(സ്ഥിരം AVHashContext *ctx)
{
    തിരികെ hashdesc[ctx->type].name;
}

പൂർണ്ണസംഖ്യ av_hash_get_size(സ്ഥിരം AVHashContext *ctx)
{
    തിരികെ hashdesc[ctx->type].size;
}

പൂർണ്ണസംഖ്യ av_hash_alloc(AVHashContext **ctx, സ്ഥിരം അക്ഷരം *name)
{
    AVHashContext *res;
    പൂർണ്ണസംഖ്യ i;
    *ctx = ശൂന്യ;
    വേണ്ടി (i = 0; i < അക്കം_HASHES; i++)
        എങ്കിൽ (av_strcasecmp(name, hashdesc[i].name) == 0)
            നിർത്തുക;
    എങ്കിൽ (i >= അക്കം_HASHES) തിരികെ AVERROR(EINVAL);
    res = av_mallocz(വലുപ്പം(*res));
    എങ്കിൽ (!res) തിരികെ AVERROR(ENOMEM);
    res->type = i;
    തിരഞ്ഞെടുപ്പ് (i) {
    അവസ്ഥ MD5:     res->ctx = av_md5_alloc(); നിർത്തുക;
    അവസ്ഥ MURMUR3: res->ctx = av_murmur3_alloc(); നിർത്തുക;
    അവസ്ഥ RIPEMD128:
    അവസ്ഥ RIPEMD160:
    അവസ്ഥ RIPEMD256:
    അവസ്ഥ RIPEMD320: res->ctx = av_ripemd_alloc(); നിർത്തുക;
    അവസ്ഥ SHA160:
    അവസ്ഥ SHA224:
    അവസ്ഥ SHA256:  res->ctx = av_sha_alloc(); നിർത്തുക;
    അവസ്ഥ SHA512_224:
    അവസ്ഥ SHA512_256:
    അവസ്ഥ SHA384:
    അവസ്ഥ SHA512:  res->ctx = av_sha512_alloc(); നിർത്തുക;
    അവസ്ഥ CRC32:   res->crctab = av_crc_get_table(AV_CRC_32_IEEE_LE); നിർത്തുക;
    അവസ്ഥ ADLER32: നിർത്തുക;
    }
    എങ്കിൽ (i != ADLER32 && i != CRC32 && !res->ctx) {
        av_free(res);
        തിരികെ AVERROR(ENOMEM);
    }
    *ctx = res;
    തിരികെ 0;
}

ശൂന്യം av_hash_init(AVHashContext *ctx)
{
    തിരഞ്ഞെടുപ്പ് (ctx->type) {
    അവസ്ഥ MD5:     av_md5_init(ctx->ctx); നിർത്തുക;
    അവസ്ഥ MURMUR3: av_murmur3_init(ctx->ctx); നിർത്തുക;
    അവസ്ഥ RIPEMD128: av_ripemd_init(ctx->ctx, 128); നിർത്തുക;
    അവസ്ഥ RIPEMD160: av_ripemd_init(ctx->ctx, 160); നിർത്തുക;
    അവസ്ഥ RIPEMD256: av_ripemd_init(ctx->ctx, 256); നിർത്തുക;
    അവസ്ഥ RIPEMD320: av_ripemd_init(ctx->ctx, 320); നിർത്തുക;
    അവസ്ഥ SHA160:  av_sha_init(ctx->ctx, 160); നിർത്തുക;
    അവസ്ഥ SHA224:  av_sha_init(ctx->ctx, 224); നിർത്തുക;
    അവസ്ഥ SHA256:  av_sha_init(ctx->ctx, 256); നിർത്തുക;
    അവസ്ഥ SHA512_224:  av_sha512_init(ctx->ctx, 224); നിർത്തുക;
    അവസ്ഥ SHA512_256:  av_sha512_init(ctx->ctx, 256); നിർത്തുക;
    അവസ്ഥ SHA384:  av_sha512_init(ctx->ctx, 384); നിർത്തുക;
    അവസ്ഥ SHA512:  av_sha512_init(ctx->ctx, 512); നിർത്തുക;
    അവസ്ഥ CRC32:   ctx->crc = UINT32_MAX; നിർത്തുക;
    അവസ്ഥ ADLER32: ctx->crc = 1; നിർത്തുക;
    }
}

ശൂന്യം av_hash_update(AVHashContext *ctx, സ്ഥിരം uint8_t *src, size_t len)
{
    തിരഞ്ഞെടുപ്പ് (ctx->type) {
    അവസ്ഥ MD5:     av_md5_update(ctx->ctx, src, len); നിർത്തുക;
    അവസ്ഥ MURMUR3: av_murmur3_update(ctx->ctx, src, len); നിർത്തുക;
    അവസ്ഥ RIPEMD128:
    അവസ്ഥ RIPEMD160:
    അവസ്ഥ RIPEMD256:
    അവസ്ഥ RIPEMD320: av_ripemd_update(ctx->ctx, src, len); നിർത്തുക;
    അവസ്ഥ SHA160:
    അവസ്ഥ SHA224:
    അവസ്ഥ SHA256:  av_sha_update(ctx->ctx, src, len); നിർത്തുക;
    അവസ്ഥ SHA512_224:
    അവസ്ഥ SHA512_256:
    അവസ്ഥ SHA384:
    അവസ്ഥ SHA512:  av_sha512_update(ctx->ctx, src, len); നിർത്തുക;
    അവസ്ഥ CRC32:   ctx->crc = av_crc(ctx->crctab, ctx->crc, src, len); നിർത്തുക;
    അവസ്ഥ ADLER32: ctx->crc = av_adler32_update(ctx->crc, src, len); നിർത്തുക;
    }
}

ശൂന്യം av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    തിരഞ്ഞെടുപ്പ് (ctx->type) {
    അവസ്ഥ MD5:     av_md5_final(ctx->ctx, dst); നിർത്തുക;
    അവസ്ഥ MURMUR3: av_murmur3_final(ctx->ctx, dst); നിർത്തുക;
    അവസ്ഥ RIPEMD128:
    അവസ്ഥ RIPEMD160:
    അവസ്ഥ RIPEMD256:
    അവസ്ഥ RIPEMD320: av_ripemd_final(ctx->ctx, dst); നിർത്തുക;
    അവസ്ഥ SHA160:
    അവസ്ഥ SHA224:
    അവസ്ഥ SHA256:  av_sha_final(ctx->ctx, dst); നിർത്തുക;
    അവസ്ഥ SHA512_224:
    അവസ്ഥ SHA512_256:
    അവസ്ഥ SHA384:
    അവസ്ഥ SHA512:  av_sha512_final(ctx->ctx, dst); നിർത്തുക;
    അവസ്ഥ CRC32:   AV_WB32(dst, ctx->crc ^ UINT32_MAX); നിർത്തുക;
    അവസ്ഥ ADLER32: AV_WB32(dst, ctx->crc); നിർത്തുക;
    }
}

ശൂന്യം av_hash_final_bin(ഘടന AVHashContext *ctx, uint8_t *dst, പൂർണ്ണസംഖ്യ size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx);

    av_hash_final(ctx, buf);
    memcpy(dst, buf, FFMIN(size, rsize));
    എങ്കിൽ (size > rsize)
        memset(dst + rsize, 0, size - rsize);
}

ശൂന്യം av_hash_final_hex(ഘടന AVHashContext *ctx, uint8_t *dst, പൂർണ്ണസംഖ്യ size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx), i;

    av_hash_final(ctx, buf);
    വേണ്ടി (i = 0; i < FFMIN(rsize, size / 2); i++)
        snprintf(dst + i * 2, size - i * 2, "%02x", buf[i]);
}

ശൂന്യം av_hash_final_b64(ഘടന AVHashContext *ctx, uint8_t *dst, പൂർണ്ണസംഖ്യ size)
{
    uint8_t buf[AV_HASH_MAX_SIZE], b64[AV_BASE64_SIZE(AV_HASH_MAX_SIZE)];
    unsigned rsize = av_hash_get_size(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, വലുപ്പം(b64), buf, rsize);
    osize = AV_BASE64_SIZE(rsize);
    memcpy(dst, b64, FFMIN(osize, size));
    എങ്കിൽ (size < osize)
        dst[size - 1] = 0;
}

ശൂന്യം av_hash_freep(AVHashContext **ctx)
{
    എങ്കിൽ (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
