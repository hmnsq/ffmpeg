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

#અન્તર્ભાવ <assert.h>
#અન્તર્ભાવ <stddef.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ "hash.h"

#અન્તર્ભાવ "adler32.h"
#અન્તર્ભાવ "crc.h"
#અન્તર્ભાવ "md5.h"
#અન્તર્ભાવ "murmur3.h"
#અન્તર્ભાવ "ripemd.h"
#અન્તર્ભાવ "sha.h"
#અન્તર્ભાવ "sha512.h"

#અન્તર્ભાવ "avstring.h"
#અન્તર્ભાવ "base64.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "intreadwrite.h"
#અન્તર્ભાવ "mem.h"

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

ગણના hashtype {
#define HASH_TYPE(TYPE, NAME, SIZE) TYPE,
    HASHES(HASH_TYPE)
    અંક_HASHES
};

પ્રકારવ્યાખ્યા સંરચના AVHashContext {
    શૂન્ય *ctx;
    ગણના hashtype type;
    અચલ AVCRC *crctab;
    uint32_t crc;
} AVHashContext;

#define HASH_MAX_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(SIZE, HASH_MAX_SIZE_BEFORE_ ## TYPE) - 1,
ગણના {
    HASHES(HASH_MAX_SIZE)
    MAX_HASH_SIZE
};
static_assert(AV_HASH_MAX_SIZE >= MAX_HASH_SIZE, "AV_HASH_MAX_SIZE needs to be updated!");

#define HASH_MAX_NAME_SIZE(TYPE, NAME, SIZE) \
    HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE,      \
    HASH_MAX_NAME_SIZE_UNTIL_ ## TYPE ## _MINUS_ONE = FFMAX(કદ(NAME), HASH_MAX_NAME_SIZE_BEFORE_ ## TYPE) - 1,
ગણના {
    HASHES(HASH_MAX_NAME_SIZE)
    MAX_HASH_NAME_SIZE
};

સ્થિર અચલ સંરચના {
    અચલ અક્ષર name[MAX_HASH_NAME_SIZE];
    પૂર્ણાંક size;
} hashdesc[] = {
#define HASH_DESC(TYPE, NAME, SIZE) [TYPE] = { NAME, SIZE },
    HASHES(HASH_DESC)
};

અચલ અક્ષર *av_hash_names(પૂર્ણાંક i)
{
    જો (i < 0 || i >= અંક_HASHES) પાછા ખાલી;
    પાછા hashdesc[i].name;
}

અચલ અક્ષર *av_hash_get_name(અચલ AVHashContext *ctx)
{
    પાછા hashdesc[ctx->type].name;
}

પૂર્ણાંક av_hash_get_size(અચલ AVHashContext *ctx)
{
    પાછા hashdesc[ctx->type].size;
}

પૂર્ણાંક av_hash_alloc(AVHashContext **ctx, અચલ અક્ષર *name)
{
    AVHashContext *res;
    પૂર્ણાંક i;
    *ctx = ખાલી;
    માટે (i = 0; i < અંક_HASHES; i++)
        જો (av_strcasecmp(name, hashdesc[i].name) == 0)
            તોડો;
    જો (i >= અંક_HASHES) પાછા AVERROR(EINVAL);
    res = av_mallocz(કદ(*res));
    જો (!res) પાછા AVERROR(ENOMEM);
    res->type = i;
    પસંદગી (i) {
    સ્થિતિ MD5:     res->ctx = av_md5_alloc(); તોડો;
    સ્થિતિ MURMUR3: res->ctx = av_murmur3_alloc(); તોડો;
    સ્થિતિ RIPEMD128:
    સ્થિતિ RIPEMD160:
    સ્થિતિ RIPEMD256:
    સ્થિતિ RIPEMD320: res->ctx = av_ripemd_alloc(); તોડો;
    સ્થિતિ SHA160:
    સ્થિતિ SHA224:
    સ્થિતિ SHA256:  res->ctx = av_sha_alloc(); તોડો;
    સ્થિતિ SHA512_224:
    સ્થિતિ SHA512_256:
    સ્થિતિ SHA384:
    સ્થિતિ SHA512:  res->ctx = av_sha512_alloc(); તોડો;
    સ્થિતિ CRC32:   res->crctab = av_crc_get_table(AV_CRC_32_IEEE_LE); તોડો;
    સ્થિતિ ADLER32: તોડો;
    }
    જો (i != ADLER32 && i != CRC32 && !res->ctx) {
        av_free(res);
        પાછા AVERROR(ENOMEM);
    }
    *ctx = res;
    પાછા 0;
}

શૂન્ય av_hash_init(AVHashContext *ctx)
{
    પસંદગી (ctx->type) {
    સ્થિતિ MD5:     av_md5_init(ctx->ctx); તોડો;
    સ્થિતિ MURMUR3: av_murmur3_init(ctx->ctx); તોડો;
    સ્થિતિ RIPEMD128: av_ripemd_init(ctx->ctx, 128); તોડો;
    સ્થિતિ RIPEMD160: av_ripemd_init(ctx->ctx, 160); તોડો;
    સ્થિતિ RIPEMD256: av_ripemd_init(ctx->ctx, 256); તોડો;
    સ્થિતિ RIPEMD320: av_ripemd_init(ctx->ctx, 320); તોડો;
    સ્થિતિ SHA160:  av_sha_init(ctx->ctx, 160); તોડો;
    સ્થિતિ SHA224:  av_sha_init(ctx->ctx, 224); તોડો;
    સ્થિતિ SHA256:  av_sha_init(ctx->ctx, 256); તોડો;
    સ્થિતિ SHA512_224:  av_sha512_init(ctx->ctx, 224); તોડો;
    સ્થિતિ SHA512_256:  av_sha512_init(ctx->ctx, 256); તોડો;
    સ્થિતિ SHA384:  av_sha512_init(ctx->ctx, 384); તોડો;
    સ્થિતિ SHA512:  av_sha512_init(ctx->ctx, 512); તોડો;
    સ્થિતિ CRC32:   ctx->crc = UINT32_MAX; તોડો;
    સ્થિતિ ADLER32: ctx->crc = 1; તોડો;
    }
}

શૂન્ય av_hash_update(AVHashContext *ctx, અચલ uint8_t *src, size_t len)
{
    પસંદગી (ctx->type) {
    સ્થિતિ MD5:     av_md5_update(ctx->ctx, src, len); તોડો;
    સ્થિતિ MURMUR3: av_murmur3_update(ctx->ctx, src, len); તોડો;
    સ્થિતિ RIPEMD128:
    સ્થિતિ RIPEMD160:
    સ્થિતિ RIPEMD256:
    સ્થિતિ RIPEMD320: av_ripemd_update(ctx->ctx, src, len); તોડો;
    સ્થિતિ SHA160:
    સ્થિતિ SHA224:
    સ્થિતિ SHA256:  av_sha_update(ctx->ctx, src, len); તોડો;
    સ્થિતિ SHA512_224:
    સ્થિતિ SHA512_256:
    સ્થિતિ SHA384:
    સ્થિતિ SHA512:  av_sha512_update(ctx->ctx, src, len); તોડો;
    સ્થિતિ CRC32:   ctx->crc = av_crc(ctx->crctab, ctx->crc, src, len); તોડો;
    સ્થિતિ ADLER32: ctx->crc = av_adler32_update(ctx->crc, src, len); તોડો;
    }
}

શૂન્ય av_hash_final(AVHashContext *ctx, uint8_t *dst)
{
    પસંદગી (ctx->type) {
    સ્થિતિ MD5:     av_md5_final(ctx->ctx, dst); તોડો;
    સ્થિતિ MURMUR3: av_murmur3_final(ctx->ctx, dst); તોડો;
    સ્થિતિ RIPEMD128:
    સ્થિતિ RIPEMD160:
    સ્થિતિ RIPEMD256:
    સ્થિતિ RIPEMD320: av_ripemd_final(ctx->ctx, dst); તોડો;
    સ્થિતિ SHA160:
    સ્થિતિ SHA224:
    સ્થિતિ SHA256:  av_sha_final(ctx->ctx, dst); તોડો;
    સ્થિતિ SHA512_224:
    સ્થિતિ SHA512_256:
    સ્થિતિ SHA384:
    સ્થિતિ SHA512:  av_sha512_final(ctx->ctx, dst); તોડો;
    સ્થિતિ CRC32:   AV_WB32(dst, ctx->crc ^ UINT32_MAX); તોડો;
    સ્થિતિ ADLER32: AV_WB32(dst, ctx->crc); તોડો;
    }
}

શૂન્ય av_hash_final_bin(સંરચના AVHashContext *ctx, uint8_t *dst, પૂર્ણાંક size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx);

    av_hash_final(ctx, buf);
    memcpy(dst, buf, FFMIN(size, rsize));
    જો (size > rsize)
        memset(dst + rsize, 0, size - rsize);
}

શૂન્ય av_hash_final_hex(સંરચના AVHashContext *ctx, uint8_t *dst, પૂર્ણાંક size)
{
    uint8_t buf[AV_HASH_MAX_SIZE];
    unsigned rsize = av_hash_get_size(ctx), i;

    av_hash_final(ctx, buf);
    માટે (i = 0; i < FFMIN(rsize, size / 2); i++)
        snprintf(dst + i * 2, size - i * 2, "%02x", buf[i]);
}

શૂન્ય av_hash_final_b64(સંરચના AVHashContext *ctx, uint8_t *dst, પૂર્ણાંક size)
{
    uint8_t buf[AV_HASH_MAX_SIZE], b64[AV_BASE64_SIZE(AV_HASH_MAX_SIZE)];
    unsigned rsize = av_hash_get_size(ctx), osize;

    av_hash_final(ctx, buf);
    av_base64_encode(b64, કદ(b64), buf, rsize);
    osize = AV_BASE64_SIZE(rsize);
    memcpy(dst, b64, FFMIN(osize, size));
    જો (size < osize)
        dst[size - 1] = 0;
}

શૂન્ય av_hash_freep(AVHashContext **ctx)
{
    જો (*ctx)
        av_freep(&(*ctx)->ctx);
    av_freep(ctx);
}
