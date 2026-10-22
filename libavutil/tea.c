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

#অন্তর্ভাৱ <string.h>
#অন্তর্ভাৱ "intreadwrite.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "tea.h"

প্রকারনির্দেশ সংরচনা AVTEA {
    uint32_t চাবি[16];
    পূর্ণাঙ্ক rounds;
} AVTEA;

সংরচনা AVTEA *av_tea_alloc(শূন্য)
{
    ঘূৰাই av_mallocz(পরিমাণ(সংরচনা AVTEA));
}

ধ্রুৱ পূর্ণাঙ্ক av_tea_size = পরিমাণ(AVTEA);

শূন্য av_tea_init(AVTEA *ctx, ধ্রুৱ uint8_t চাবি[16], পূর্ণাঙ্ক rounds)
{
    পূর্ণাঙ্ক i;

    বাবে (i = 0; i < 4; i++)
        ctx->চাবি[i] = AV_RB32(চাবি + (i << 2));

    ctx->rounds = rounds;
}

স্থির শূন্য tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, ধ্রুৱ uint8_t *src,
                          পূর্ণাঙ্ক decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    পূর্ণাঙ্ক rounds = ctx->rounds;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->চাবি[0];
    k1 = ctx->চাবি[1];
    k2 = ctx->চাবি[2];
    k3 = ctx->চাবি[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    যদি (decrypt) {
        পূর্ণাঙ্ক i;
        uint32_t delta = 0x9E3779B9U, sum = delta * (rounds / 2);

        বাবে (i = 0; i < rounds / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            sum -= delta;
        }
        যদি (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            memcpy(iv, src, 8);
        }
    } অন্যথা {
        পূর্ণাঙ্ক i;
        uint32_t sum = 0, delta = 0x9E3779B9U;

        বাবে (i = 0; i < rounds / 2; i++) {
            sum += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

শূন্য av_tea_crypt(AVTEA *ctx, uint8_t *dst, ধ্রুৱ uint8_t *src, পূর্ণাঙ্ক গুনতি,
                  uint8_t *iv, পূর্ণাঙ্ক decrypt)
{
    পূর্ণাঙ্ক i;

    যদি (decrypt) {
        যেতিয়ালৈ (গুনতি--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } অন্যথা {
        যেতিয়ালৈ (গুনতি--) {
            যদি (iv) {
                বাবে (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, রিক্ত);
                memcpy(iv, dst, 8);
            } অন্যথা {
                tea_crypt_ecb(ctx, dst, src, decrypt, রিক্ত);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
