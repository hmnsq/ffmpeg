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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "tea.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVTEA {
    uint32_t ಕೀಲಿ[16];
    ಪೂರ್ಣಾಂಕ ಸುತ್ತುಗಳು;
} AVTEA;

ರಚನೆ AVTEA *av_tea_alloc(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ av_mallocz(ಗಾತ್ರ(ರಚನೆ AVTEA));
}

ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ av_tea_ಗಾತ್ರ = ಗಾತ್ರ(AVTEA);

ಶೂನ್ಯ av_tea_init(AVTEA *ctx, ಸ್ಥಿರಾಂಕ uint8_t ಕೀಲಿ[16], ಪೂರ್ಣಾಂಕ ಸುತ್ತುಗಳು)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < 4; i++)
        ctx->ಕೀಲಿ[i] = AV_RB32(ಕೀಲಿ + (i << 2));

    ctx->ಸುತ್ತುಗಳು = ಸುತ್ತುಗಳು;
}

ಸ್ಥಿರ ಶೂನ್ಯ tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, ಸ್ಥಿರಾಂಕ uint8_t *src,
                          ಪೂರ್ಣಾಂಕ decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    ಪೂರ್ಣಾಂಕ ಸುತ್ತುಗಳು = ctx->ಸುತ್ತುಗಳು;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->ಕೀಲಿ[0];
    k1 = ctx->ಕೀಲಿ[1];
    k2 = ctx->ಕೀಲಿ[2];
    k3 = ctx->ಕೀಲಿ[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    ಆದರೆ (decrypt) {
        ಪೂರ್ಣಾಂಕ i;
        uint32_t delta = 0x9E3779B9U, ಮೊತ್ತ = delta * (ಸುತ್ತುಗಳು / 2);

        ಗಾಗಿ (i = 0; i < ಸುತ್ತುಗಳು / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + ಮೊತ್ತ) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + ಮೊತ್ತ) ^ ((v1 >> 5) + k1);
            ಮೊತ್ತ -= delta;
        }
        ಆದರೆ (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            ಸ್ಮರಣೆ_ನಕಲು(iv, src, 8);
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಪೂರ್ಣಾಂಕ i;
        uint32_t ಮೊತ್ತ = 0, delta = 0x9E3779B9U;

        ಗಾಗಿ (i = 0; i < ಸುತ್ತುಗಳು / 2; i++) {
            ಮೊತ್ತ += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + ಮೊತ್ತ) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + ಮೊತ್ತ) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

ಶೂನ್ಯ av_tea_crypt(AVTEA *ctx, uint8_t *dst, ಸ್ಥಿರಾಂಕ uint8_t *src, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2,
                  uint8_t *iv, ಪೂರ್ಣಾಂಕ decrypt)
{
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (decrypt) {
        ಆಗ (ಎಣಿಕೆ_2--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆಗ (ಎಣಿಕೆ_2--) {
            ಆದರೆ (iv) {
                ಗಾಗಿ (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, ಖಾಲಿ);
                ಸ್ಮರಣೆ_ನಕಲು(iv, dst, 8);
            } ಇಲ್ಲದಿದ್ದರೆ {
                tea_crypt_ecb(ctx, dst, src, decrypt, ಖಾಲಿ);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
