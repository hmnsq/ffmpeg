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

#ଅନ୍ତର୍ଭାଵ <string.h>
#ଅନ୍ତର୍ଭାଵ "intreadwrite.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "tea.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AVTEA {
    uint32_t ଚାବି[16];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds;
} AVTEA;

ସଂରଚନା AVTEA *av_tea_alloc(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ av_mallocz(ଆକାର(ସଂରଚନା AVTEA));
}

ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_tea_size = ଆକାର(AVTEA);

ଶୂନ୍ୟ av_tea_init(AVTEA *ctx, ଅଚଳ uint8_t ଚାବି[16], ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < 4; i++)
        ctx->ଚାବି[i] = AV_RB32(ଚାବି + (i << 2));

    ctx->rounds = rounds;
}

ସ୍ଥିର ଶୂନ୍ୟ tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, ଅଚଳ uint8_t *src,
                          ପୂର୍ଣ୍ଣସଂଖ୍ୟା decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds = ctx->rounds;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->ଚାବି[0];
    k1 = ctx->ଚାବି[1];
    k2 = ctx->ଚାବି[2];
    k3 = ctx->ଚାବି[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    ଯଦି (decrypt) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
        uint32_t delta = 0x9E3779B9U, sum = delta * (rounds / 2);

        ପାଇଁ (i = 0; i < rounds / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            sum -= delta;
        }
        ଯଦି (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            memcpy(iv, src, 8);
        }
    } ଅନ୍ୟଥା {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
        uint32_t sum = 0, delta = 0x9E3779B9U;

        ପାଇଁ (i = 0; i < rounds / 2; i++) {
            sum += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

ଶୂନ୍ୟ av_tea_crypt(AVTEA *ctx, uint8_t *dst, ଅଚଳ uint8_t *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2,
                  uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା decrypt)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଯଦି (decrypt) {
        ଯେତେବେଳେ (ଗଣନା_2--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } ଅନ୍ୟଥା {
        ଯେତେବେଳେ (ଗଣନା_2--) {
            ଯଦି (iv) {
                ପାଇଁ (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, ଖାଲି);
                memcpy(iv, dst, 8);
            } ଅନ୍ୟଥା {
                tea_crypt_ecb(ctx, dst, src, decrypt, ଖାଲି);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
