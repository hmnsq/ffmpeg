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

#அந்தர்பாவ <string.h>
#அந்தர்பாவ "intreadwrite.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "tea.h"

வகைவரை கட்டமைப்பு AVTEA {
    uint32_t சாவி[16];
    முழு rounds;
} AVTEA;

கட்டமைப்பு AVTEA *av_tea_alloc(வெறுமை)
{
    திரும்பு av_mallocz(அளவு(கட்டமைப்பு AVTEA));
}

மாறிலி முழு av_tea_size = அளவு(AVTEA);

வெறுமை av_tea_init(AVTEA *ctx, மாறிலி uint8_t சாவி[16], முழு rounds)
{
    முழு i;

    க்கு (i = 0; i < 4; i++)
        ctx->சாவி[i] = AV_RB32(சாவி + (i << 2));

    ctx->rounds = rounds;
}

நிலையான வெறுமை tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, மாறிலி uint8_t *src,
                          முழு decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    முழு rounds = ctx->rounds;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->சாவி[0];
    k1 = ctx->சாவி[1];
    k2 = ctx->சாவி[2];
    k3 = ctx->சாவி[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    எனில் (decrypt) {
        முழு i;
        uint32_t delta = 0x9E3779B9U, sum = delta * (rounds / 2);

        க்கு (i = 0; i < rounds / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            sum -= delta;
        }
        எனில் (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            memcpy(iv, src, 8);
        }
    } இல்லையெனில் {
        முழு i;
        uint32_t sum = 0, delta = 0x9E3779B9U;

        க்கு (i = 0; i < rounds / 2; i++) {
            sum += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

வெறுமை av_tea_crypt(AVTEA *ctx, uint8_t *dst, மாறிலி uint8_t *src, முழு மொத்தம்,
                  uint8_t *iv, முழு decrypt)
{
    முழு i;

    எனில் (decrypt) {
        போது (மொத்தம்--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } இல்லையெனில் {
        போது (மொத்தம்--) {
            எனில் (iv) {
                க்கு (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, வெற்று);
                memcpy(iv, dst, 8);
            } இல்லையெனில் {
                tea_crypt_ecb(ctx, dst, src, decrypt, வெற்று);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
