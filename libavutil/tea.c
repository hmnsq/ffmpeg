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

#شامل <string.h>
#شامل "intreadwrite.h"
#شامل "mem.h"
#شامل "tea.h"

تعریفنوع ساختار AVTEA {
    uint32_t کلید[16];
    صحیح rounds;
} AVTEA;

ساختار AVTEA *av_tea_alloc(تهی)
{
    بازگشت av_mallocz(اندازه(ساختار AVTEA));
}

ثابت صحیح av_tea_size = اندازه(AVTEA);

تهی av_tea_init(AVTEA *ctx, ثابت uint8_t کلید[16], صحیح rounds)
{
    صحیح i;

    برای (i = 0; i < 4; i++)
        ctx->کلید[i] = AV_RB32(کلید + (i << 2));

    ctx->rounds = rounds;
}

ایستا تهی tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, ثابت uint8_t *src,
                          صحیح decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    صحیح rounds = ctx->rounds;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->کلید[0];
    k1 = ctx->کلید[1];
    k2 = ctx->کلید[2];
    k3 = ctx->کلید[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    اگر (decrypt) {
        صحیح i;
        uint32_t delta = 0x9E3779B9U, sum = delta * (rounds / 2);

        برای (i = 0; i < rounds / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            sum -= delta;
        }
        اگر (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            memcpy(iv, src, 8);
        }
    } وگرنه {
        صحیح i;
        uint32_t sum = 0, delta = 0x9E3779B9U;

        برای (i = 0; i < rounds / 2; i++) {
            sum += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

تهی av_tea_crypt(AVTEA *ctx, uint8_t *dst, ثابت uint8_t *src, صحیح شمار,
                  uint8_t *iv, صحیح decrypt)
{
    صحیح i;

    اگر (decrypt) {
        وقتی (شمار--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } وگرنه {
        وقتی (شمار--) {
            اگر (iv) {
                برای (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, پوچ);
                memcpy(iv, dst, 8);
            } وگرنه {
                tea_crypt_ecb(ctx, dst, src, decrypt, پوچ);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
