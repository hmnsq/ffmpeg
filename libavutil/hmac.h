/*
 * Copyright (C) 2012 Martin Storsjo
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

#ifndef AVUTIL_HMAC_H
#define AVUTIL_HMAC_H

#अन्तर्भाव <stdint.h>

/**
 * @defgroup lavu_hmac HMAC
 * @ingroup lavu_crypto
 * @{
 */

गणना AVHMACType {
    AV_HMAC_MD5,
    AV_HMAC_SHA1,
    AV_HMAC_SHA224,
    AV_HMAC_SHA256,
    AV_HMAC_SHA384,
    AV_HMAC_SHA512,
};

प्रकारव्याख्या संरचना AVHMAC AVHMAC;

/**
 * Allocate an AVHMAC context.
 * @param type The hash function used for the HMAC.
 */
AVHMAC *av_hmac_alloc(गणना AVHMACType type);

/**
 * Free an AVHMAC context.
 * @param ctx The context to free, may be NULL
 */
शून्य av_hmac_free(AVHMAC *ctx);

/**
 * Initialize an AVHMAC context with an authentication key.
 * @param ctx    The HMAC context
 * @param key    The authentication key
 * @param keylen The length of the key, in bytes
 */
शून्य av_hmac_init(AVHMAC *ctx, स्थिरांक uint8_t *किल्ली, अचिन्हित पूर्णांक keylen);

/**
 * Hash data with the HMAC.
 * @param ctx  The HMAC context
 * @param data The data to hash
 * @param len  The length of the data, in bytes
 */
शून्य av_hmac_update(AVHMAC *ctx, स्थिरांक uint8_t *data, अचिन्हित पूर्णांक len);

/**
 * Finish hashing and output the HMAC digest.
 * @param ctx    The HMAC context
 * @param out    The output buffer to write the digest into
 * @param outlen The length of the out buffer, in bytes
 * @return       The number of bytes written to out, or a negative error code.
 */
पूर्णांक av_hmac_final(AVHMAC *ctx, uint8_t *out, अचिन्हित पूर्णांक outlen);

/**
 * Hash an array of data with a key.
 * @param ctx    The HMAC context
 * @param data   The data to hash
 * @param len    The length of the data, in bytes
 * @param key    The authentication key
 * @param keylen The length of the key, in bytes
 * @param out    The output buffer to write the digest into
 * @param outlen The length of the out buffer, in bytes
 * @return       The number of bytes written to out, or a negative error code.
 */
पूर्णांक av_hmac_calc(AVHMAC *ctx, स्थिरांक uint8_t *data, अचिन्हित पूर्णांक len,
                 स्थिरांक uint8_t *किल्ली, अचिन्हित पूर्णांक keylen,
                 uint8_t *out, अचिन्हित पूर्णांक outlen);

/**
 * @}
 */

#endif /* AVUTIL_HMAC_H */
