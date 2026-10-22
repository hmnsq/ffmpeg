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

#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ "intreadwrite.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "tea.h"

પ્રકારવ્યાખ્યા સંરચના AVTEA {
    uint32_t ચાવી[16];
    પૂર્ણાંક rounds;
} AVTEA;

સંરચના AVTEA *av_tea_alloc(શૂન્ય)
{
    પાછા av_mallocz(કદ(સંરચના AVTEA));
}

અચલ પૂર્ણાંક av_tea_size = કદ(AVTEA);

શૂન્ય av_tea_init(AVTEA *ctx, અચલ uint8_t ચાવી[16], પૂર્ણાંક rounds)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < 4; i++)
        ctx->ચાવી[i] = AV_RB32(ચાવી + (i << 2));

    ctx->rounds = rounds;
}

સ્થિર શૂન્ય tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, અચલ uint8_t *src,
                          પૂર્ણાંક decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    પૂર્ણાંક rounds = ctx->rounds;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->ચાવી[0];
    k1 = ctx->ચાવી[1];
    k2 = ctx->ચાવી[2];
    k3 = ctx->ચાવી[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    જો (decrypt) {
        પૂર્ણાંક i;
        uint32_t delta = 0x9E3779B9U, sum = delta * (rounds / 2);

        માટે (i = 0; i < rounds / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            sum -= delta;
        }
        જો (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            memcpy(iv, src, 8);
        }
    } નહીંતર {
        પૂર્ણાંક i;
        uint32_t sum = 0, delta = 0x9E3779B9U;

        માટે (i = 0; i < rounds / 2; i++) {
            sum += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

શૂન્ય av_tea_crypt(AVTEA *ctx, uint8_t *dst, અચલ uint8_t *src, પૂર્ણાંક ગણતરી,
                  uint8_t *iv, પૂર્ણાંક decrypt)
{
    પૂર્ણાંક i;

    જો (decrypt) {
        જ્યારે (ગણતરી--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } નહીંતર {
        જ્યારે (ગણતરી--) {
            જો (iv) {
                માટે (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, ખાલી);
                memcpy(iv, dst, 8);
            } નહીંતર {
                tea_crypt_ecb(ctx, dst, src, decrypt, ખાલી);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
