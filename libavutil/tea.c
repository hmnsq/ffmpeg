/*
 * A 32-bit implementation of the TEA algorithm
 * Copyright (c) 2015 Vesselin Bontchev
 *
 * Loosely based on the implementation of David Wheeler and Roger Needham,
 * https://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm#Reference_code
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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tea.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVTEA {
    uint32_t ਕੁੰਜੀ[16];
    ਪੂਰਨ ਗੇੜ;
} AVTEA;

ਬਣਤਰ AVTEA *av_tea_alloc(ਖਾਲੀ)
{
    ਵਾਪਸ av_mallocz(ਆਕਾਰ(ਬਣਤਰ AVTEA));
}

ਅਚਲ ਪੂਰਨ av_tea_ਮਾਪ = ਆਕਾਰ(AVTEA);

ਖਾਲੀ av_tea_init(AVTEA *ctx, ਅਚਲ uint8_t ਕੁੰਜੀ[16], ਪੂਰਨ ਗੇੜ)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < 4; i++)
        ctx->ਕੁੰਜੀ[i] = AV_RB32(ਕੁੰਜੀ + (i << 2));

    ctx->ਗੇੜ = ਗੇੜ;
}

ਸਥਿਰ ਖਾਲੀ tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, ਅਚਲ uint8_t *src,
                          ਪੂਰਨ decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    ਪੂਰਨ ਗੇੜ = ctx->ਗੇੜ;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->ਕੁੰਜੀ[0];
    k1 = ctx->ਕੁੰਜੀ[1];
    k2 = ctx->ਕੁੰਜੀ[2];
    k3 = ctx->ਕੁੰਜੀ[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    ਜੇ (decrypt) {
        ਪੂਰਨ i;
        uint32_t delta = 0x9E3779B9U, ਜੋੜ = delta * (ਗੇੜ / 2);

        ਲਈ (i = 0; i < ਗੇੜ / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + ਜੋੜ) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + ਜੋੜ) ^ ((v1 >> 5) + k1);
            ਜੋੜ -= delta;
        }
        ਜੇ (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(iv, src, 8);
        }
    } ਨਹੀਂਤਾਂ {
        ਪੂਰਨ i;
        uint32_t ਜੋੜ = 0, delta = 0x9E3779B9U;

        ਲਈ (i = 0; i < ਗੇੜ / 2; i++) {
            ਜੋੜ += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + ਜੋੜ) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + ਜੋੜ) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

ਖਾਲੀ av_tea_crypt(AVTEA *ctx, uint8_t *dst, ਅਚਲ uint8_t *src, ਪੂਰਨ ਗਿਣਤੀ_2,
                  uint8_t *iv, ਪੂਰਨ decrypt)
{
    ਪੂਰਨ i;

    ਜੇ (decrypt) {
        ਜਦੋਂ (ਗਿਣਤੀ_2--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } ਨਹੀਂਤਾਂ {
        ਜਦੋਂ (ਗਿਣਤੀ_2--) {
            ਜੇ (iv) {
                ਲਈ (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, ਨਿਰਾ);
                ਸਮ੍ਰਿਤੀ_ਨਕਲ(iv, dst, 8);
            } ਨਹੀਂਤਾਂ {
                tea_crypt_ecb(ctx, dst, src, decrypt, ਨਿਰਾ);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
