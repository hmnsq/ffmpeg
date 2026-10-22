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

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVTEA {
    uint32_t ಕೀಲಿ[16];
    ಪೂರ್ಣಾಙ್ಕ rounds;
} AVTEA;

ಸಂರಚನಾ AVTEA *av_tea_alloc(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ av_mallocz(ಪರಿಮಾಣ(ಸಂರಚನಾ AVTEA));
}

ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ av_tea_size = ಪರಿಮಾಣ(AVTEA);

ಶೂನ್ಯ av_tea_init(AVTEA *ctx, ಧ್ರುವ uint8_t ಕೀಲಿ[16], ಪೂರ್ಣಾಙ್ಕ rounds)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < 4; i++)
        ctx->ಕೀಲಿ[i] = AV_RB32(ಕೀಲಿ + (i << 2));

    ctx->rounds = rounds;
}

ಸ್ಥಿರ ಶೂನ್ಯ tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, ಧ್ರುವ uint8_t *src,
                          ಪೂರ್ಣಾಙ್ಕ decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    ಪೂರ್ಣಾಙ್ಕ rounds = ctx->rounds;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->ಕೀಲಿ[0];
    k1 = ctx->ಕೀಲಿ[1];
    k2 = ctx->ಕೀಲಿ[2];
    k3 = ctx->ಕೀಲಿ[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    ಯದಿ (decrypt) {
        ಪೂರ್ಣಾಙ್ಕ i;
        uint32_t delta = 0x9E3779B9U, sum = delta * (rounds / 2);

        ಪ್ರತಿ (i = 0; i < rounds / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            sum -= delta;
        }
        ಯದಿ (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            memcpy(iv, src, 8);
        }
    } ಅನ್ಯಥಾ {
        ಪೂರ್ಣಾಙ್ಕ i;
        uint32_t sum = 0, delta = 0x9E3779B9U;

        ಪ್ರತಿ (i = 0; i < rounds / 2; i++) {
            sum += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

ಶೂನ್ಯ av_tea_crypt(AVTEA *ctx, uint8_t *dst, ಧ್ರುವ uint8_t *src, ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ,
                  uint8_t *iv, ಪೂರ್ಣಾಙ್ಕ decrypt)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (decrypt) {
        ಯಾವತ್ (ಎಣಿಕೆ--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } ಅನ್ಯಥಾ {
        ಯಾವತ್ (ಎಣಿಕೆ--) {
            ಯದಿ (iv) {
                ಪ್ರತಿ (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, ರಿಕ್ತ);
                memcpy(iv, dst, 8);
            } ಅನ್ಯಥಾ {
                tea_crypt_ecb(ctx, dst, src, decrypt, ರಿಕ್ತ);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
