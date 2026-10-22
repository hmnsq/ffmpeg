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

قسمتعریف ساخت AVTEA {
    uint32_t کلید[16];
    صحیح دور;
} AVTEA;

ساخت AVTEA *av_tea_alloc(خالی)
{
    واپس av_mallocz(حجم(ساخت AVTEA));
}

ثابت صحیح av_tea_سائز = حجم(AVTEA);

خالی av_tea_init(AVTEA *ctx, ثابت uint8_t کلید[16], صحیح دور)
{
    صحیح i;

    برائے (i = 0; i < 4; i++)
        ctx->کلید[i] = AV_RB32(کلید + (i << 2));

    ctx->دور = دور;
}

ساکن خالی tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, ثابت uint8_t *src,
                          صحیح decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    صحیح دور = ctx->دور;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->کلید[0];
    k1 = ctx->کلید[1];
    k2 = ctx->کلید[2];
    k3 = ctx->کلید[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    اگر (decrypt) {
        صحیح i;
        uint32_t delta = 0x9E3779B9U, مجموع = delta * (دور / 2);

        برائے (i = 0; i < دور / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + مجموع) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + مجموع) ^ ((v1 >> 5) + k1);
            مجموع -= delta;
        }
        اگر (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            حافظہ_نقل(iv, src, 8);
        }
    } ورنہ {
        صحیح i;
        uint32_t مجموع = 0, delta = 0x9E3779B9U;

        برائے (i = 0; i < دور / 2; i++) {
            مجموع += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + مجموع) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + مجموع) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

خالی av_tea_crypt(AVTEA *ctx, uint8_t *dst, ثابت uint8_t *src, صحیح گنتی,
                  uint8_t *iv, صحیح decrypt)
{
    صحیح i;

    اگر (decrypt) {
        جب (گنتی--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } ورنہ {
        جب (گنتی--) {
            اگر (iv) {
                برائے (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, تہی);
                حافظہ_نقل(iv, dst, 8);
            } ورنہ {
                tea_crypt_ecb(ctx, dst, src, decrypt, تہی);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
