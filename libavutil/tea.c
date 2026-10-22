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

#समावेश <string.h>
#समावेश "intreadwrite.h"
#समावेश "mem.h"
#समावेश "tea.h"

प्रकार काष्ठा AVTEA {
    uint32_t कुंजी[16];
    पूर्णांक rounds;
} AVTEA;

काष्ठा AVTEA *av_tea_alloc(व्योम)
{
    वापस av_mallocz(माप(काष्ठा AVTEA));
}

स्थिर पूर्णांक av_tea_आकार = माप(AVTEA);

व्योम av_tea_init(AVTEA *ctx, स्थिर uint8_t कुंजी[16], पूर्णांक rounds)
{
    पूर्णांक i;

    क्रम (i = 0; i < 4; i++)
        ctx->कुंजी[i] = AV_RB32(कुंजी + (i << 2));

    ctx->rounds = rounds;
}

अटल व्योम tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, स्थिर uint8_t *src,
                          पूर्णांक decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    पूर्णांक rounds = ctx->rounds;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->कुंजी[0];
    k1 = ctx->कुंजी[1];
    k2 = ctx->कुंजी[2];
    k3 = ctx->कुंजी[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    अगर (decrypt) {
        पूर्णांक i;
        uint32_t delta = 0x9E3779B9U, योग = delta * (rounds / 2);

        क्रम (i = 0; i < rounds / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + योग) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + योग) ^ ((v1 >> 5) + k1);
            योग -= delta;
        }
        अगर (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            स_नकल(iv, src, 8);
        }
    } अन्यथा {
        पूर्णांक i;
        uint32_t योग = 0, delta = 0x9E3779B9U;

        क्रम (i = 0; i < rounds / 2; i++) {
            योग += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + योग) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + योग) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

व्योम av_tea_crypt(AVTEA *ctx, uint8_t *dst, स्थिर uint8_t *src, पूर्णांक गिनती,
                  uint8_t *iv, पूर्णांक decrypt)
{
    पूर्णांक i;

    अगर (decrypt) {
        जबतक (गिनती--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } अन्यथा {
        जबतक (गिनती--) {
            अगर (iv) {
                क्रम (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, शून्य);
                स_नकल(iv, dst, 8);
            } अन्यथा {
                tea_crypt_ecb(ctx, dst, src, decrypt, शून्य);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
