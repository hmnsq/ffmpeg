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

#అన్తర్భావ <string.h>
#అన్తర్భావ "intreadwrite.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "tea.h"

రకనిర్వచనం నిర్మాణం AVTEA {
    uint32_t కీలకం[16];
    పూర్ణాంకం విడతలు;
} AVTEA;

నిర్మాణం AVTEA *av_tea_alloc(శూన్య)
{
    తిరిగి av_mallocz(పరిమాణం(నిర్మాణం AVTEA));
}

స్థిరరాశి పూర్ణాంకం av_tea_కొలత = పరిమాణం(AVTEA);

శూన్య av_tea_init(AVTEA *ctx, స్థిరరాశి uint8_t కీలకం[16], పూర్ణాంకం విడతలు)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < 4; i++)
        ctx->కీలకం[i] = AV_RB32(కీలకం + (i << 2));

    ctx->విడతలు = విడతలు;
}

స్థిర శూన్య tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, స్థిరరాశి uint8_t *src,
                          పూర్ణాంకం decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    పూర్ణాంకం విడతలు = ctx->విడతలు;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->కీలకం[0];
    k1 = ctx->కీలకం[1];
    k2 = ctx->కీలకం[2];
    k3 = ctx->కీలకం[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    ఒకవేళ (decrypt) {
        పూర్ణాంకం i;
        uint32_t delta = 0x9E3779B9U, కూడిక = delta * (విడతలు / 2);

        కొరకు (i = 0; i < విడతలు / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + కూడిక) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + కూడిక) ^ ((v1 >> 5) + k1);
            కూడిక -= delta;
        }
        ఒకవేళ (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            జ్ఞాపకం_నకలు(iv, src, 8);
        }
    } లేకపోతే {
        పూర్ణాంకం i;
        uint32_t కూడిక = 0, delta = 0x9E3779B9U;

        కొరకు (i = 0; i < విడతలు / 2; i++) {
            కూడిక += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + కూడిక) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + కూడిక) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

శూన్య av_tea_crypt(AVTEA *ctx, uint8_t *dst, స్థిరరాశి uint8_t *src, పూర్ణాంకం లెక్క,
                  uint8_t *iv, పూర్ణాంకం decrypt)
{
    పూర్ణాంకం i;

    ఒకవేళ (decrypt) {
        అయితే (లెక్క--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } లేకపోతే {
        అయితే (లెక్క--) {
            ఒకవేళ (iv) {
                కొరకు (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, ఖాళీ);
                జ్ఞాపకం_నకలు(iv, dst, 8);
            } లేకపోతే {
                tea_crypt_ecb(ctx, dst, src, decrypt, ఖాళీ);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
