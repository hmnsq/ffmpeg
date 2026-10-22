/*
 * A 32-bit implementation of the XTEA algorithm
 * Copyright (c) 2012 Samuel Pitoiset
 *
 * loosely based on the implementation of David Wheeler and Roger Needham
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

/**
 * @file
 * @brief XTEA 32-bit implementation
 * @author Samuel Pitoiset
 * @ingroup lavu_xtea
 */

#समावेश <string.h>
#समावेश "config.h"
#समावेश "intreadwrite.h"
#समावेश "mem.h"
#समावेश "xtea.h"

AVXTEA *av_xtea_alloc(व्योम)
{
    वापस av_mallocz(माप(काष्ठा AVXTEA));
}

व्योम av_xtea_init(AVXTEA *ctx, स्थिर uint8_t कुंजी[16])
{
    पूर्णांक i;

    क्रम (i = 0; i < 4; i++)
        ctx->कुंजी[i] = AV_RB32(कुंजी + (i << 2));
}

व्योम av_xtea_le_init(AVXTEA *ctx, स्थिर uint8_t कुंजी[16])
{
    पूर्णांक i;

    क्रम (i = 0; i < 4; i++)
        ctx->कुंजी[i] = AV_RL32(कुंजी + (i << 2));
}

अटल व्योम xtea_crypt_ecb(AVXTEA *ctx, uint8_t *dst, स्थिर uint8_t *src,
                           पूर्णांक decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
#अगर !CONFIG_SMALL
    uint32_t k0 = ctx->कुंजी[0];
    uint32_t k1 = ctx->कुंजी[1];
    uint32_t k2 = ctx->कुंजी[2];
    uint32_t k3 = ctx->कुंजी[3];
#पूर्ण_अगर

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    अगर (decrypt) {
#अगर CONFIG_SMALL
        पूर्णांक i;
        uint32_t delta = 0x9E3779B9U, योग = delta * 32;

        क्रम (i = 0; i < 32; i++) {
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (योग + ctx->कुंजी[(योग >> 11) & 3]);
            योग -= delta;
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (योग + ctx->कुंजी[योग & 3]);
        }
#अन्यथा
#घोषणा DSTEP(योग_3, K0, K1) \
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (योग_3 + K0); \
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (योग_3 - 0x9E3779B9U + K1)

        DSTEP(0xC6EF3720U, k2, k3);
        DSTEP(0x28B7BD67U, k3, k2);
        DSTEP(0x8A8043AEU, k0, k1);
        DSTEP(0xEC48C9F5U, k1, k0);
        DSTEP(0x4E11503CU, k2, k3);
        DSTEP(0xAFD9D683U, k2, k2);
        DSTEP(0x11A25CCAU, k3, k1);
        DSTEP(0x736AE311U, k0, k0);
        DSTEP(0xD5336958U, k1, k3);
        DSTEP(0x36FBEF9FU, k1, k2);
        DSTEP(0x98C475E6U, k2, k1);
        DSTEP(0xFA8CFC2DU, k3, k0);
        DSTEP(0x5C558274U, k0, k3);
        DSTEP(0xBE1E08BBU, k1, k2);
        DSTEP(0x1FE68F02U, k1, k1);
        DSTEP(0x81AF1549U, k2, k0);
        DSTEP(0xE3779B90U, k3, k3);
        DSTEP(0x454021D7U, k0, k2);
        DSTEP(0xA708A81EU, k1, k1);
        DSTEP(0x08D12E65U, k1, k0);
        DSTEP(0x6A99B4ACU, k2, k3);
        DSTEP(0xCC623AF3U, k3, k2);
        DSTEP(0x2E2AC13AU, k0, k1);
        DSTEP(0x8FF34781U, k0, k0);
        DSTEP(0xF1BBCDC8U, k1, k3);
        DSTEP(0x5384540FU, k2, k2);
        DSTEP(0xB54CDA56U, k3, k1);
        DSTEP(0x1715609DU, k0, k0);
        DSTEP(0x78DDE6E4U, k0, k3);
        DSTEP(0xDAA66D2BU, k1, k2);
        DSTEP(0x3C6EF372U, k2, k1);
        DSTEP(0x9E3779B9U, k3, k0);
#पूर्ण_अगर
        अगर (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            स_नकल(iv, src, 8);
        }
    } अन्यथा {
#अगर CONFIG_SMALL
        पूर्णांक i;
        uint32_t योग = 0, delta = 0x9E3779B9U;

        क्रम (i = 0; i < 32; i++) {
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (योग + ctx->कुंजी[योग & 3]);
            योग += delta;
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (योग + ctx->कुंजी[(योग >> 11) & 3]);
        }
#अन्यथा
#घोषणा ESTEP(योग_3, K0, K1) \
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (योग_3 + K0);\
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (योग_3 + 0x9E3779B9U + K1)
        ESTEP(0x00000000U, k0, k3);
        ESTEP(0x9E3779B9U, k1, k2);
        ESTEP(0x3C6EF372U, k2, k1);
        ESTEP(0xDAA66D2BU, k3, k0);
        ESTEP(0x78DDE6E4U, k0, k0);
        ESTEP(0x1715609DU, k1, k3);
        ESTEP(0xB54CDA56U, k2, k2);
        ESTEP(0x5384540FU, k3, k1);
        ESTEP(0xF1BBCDC8U, k0, k0);
        ESTEP(0x8FF34781U, k1, k0);
        ESTEP(0x2E2AC13AU, k2, k3);
        ESTEP(0xCC623AF3U, k3, k2);
        ESTEP(0x6A99B4ACU, k0, k1);
        ESTEP(0x08D12E65U, k1, k1);
        ESTEP(0xA708A81EU, k2, k0);
        ESTEP(0x454021D7U, k3, k3);
        ESTEP(0xE3779B90U, k0, k2);
        ESTEP(0x81AF1549U, k1, k1);
        ESTEP(0x1FE68F02U, k2, k1);
        ESTEP(0xBE1E08BBU, k3, k0);
        ESTEP(0x5C558274U, k0, k3);
        ESTEP(0xFA8CFC2DU, k1, k2);
        ESTEP(0x98C475E6U, k2, k1);
        ESTEP(0x36FBEF9FU, k3, k1);
        ESTEP(0xD5336958U, k0, k0);
        ESTEP(0x736AE311U, k1, k3);
        ESTEP(0x11A25CCAU, k2, k2);
        ESTEP(0xAFD9D683U, k3, k2);
        ESTEP(0x4E11503CU, k0, k1);
        ESTEP(0xEC48C9F5U, k1, k0);
        ESTEP(0x8A8043AEU, k2, k3);
        ESTEP(0x28B7BD67U, k3, k2);
#पूर्ण_अगर
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

अटल व्योम xtea_le_crypt_ecb(AVXTEA *ctx, uint8_t *dst, स्थिर uint8_t *src,
                              पूर्णांक decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    पूर्णांक i;

    v0 = AV_RL32(src);
    v1 = AV_RL32(src + 4);

    अगर (decrypt) {
        uint32_t delta = 0x9E3779B9, योग = delta * 32;

        क्रम (i = 0; i < 32; i++) {
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (योग + ctx->कुंजी[(योग >> 11) & 3]);
            योग -= delta;
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (योग + ctx->कुंजी[योग & 3]);
        }
        अगर (iv) {
            v0 ^= AV_RL32(iv);
            v1 ^= AV_RL32(iv + 4);
            स_नकल(iv, src, 8);
        }
    } अन्यथा {
        uint32_t योग = 0, delta = 0x9E3779B9;

        क्रम (i = 0; i < 32; i++) {
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (योग + ctx->कुंजी[योग & 3]);
            योग += delta;
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (योग + ctx->कुंजी[(योग >> 11) & 3]);
        }
    }

    AV_WL32(dst, v0);
    AV_WL32(dst + 4, v1);
}

अटल व्योम xtea_crypt(AVXTEA *ctx, uint8_t *dst, स्थिर uint8_t *src, पूर्णांक गिनती,
                       uint8_t *iv, पूर्णांक decrypt,
                       व्योम (*crypt)(AVXTEA *, uint8_t *, स्थिर uint8_t *, पूर्णांक, uint8_t *))
{
    पूर्णांक i;

    अगर (decrypt) {
        जबतक (गिनती--) {
            crypt(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } अन्यथा {
        जबतक (गिनती--) {
            अगर (iv) {
                क्रम (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                crypt(ctx, dst, dst, decrypt, शून्य);
                स_नकल(iv, dst, 8);
            } अन्यथा {
                crypt(ctx, dst, src, decrypt, शून्य);
            }
            src   += 8;
            dst   += 8;
        }
    }
}

व्योम av_xtea_crypt(AVXTEA *ctx, uint8_t *dst, स्थिर uint8_t *src, पूर्णांक गिनती,
                   uint8_t *iv, पूर्णांक decrypt)
{
    xtea_crypt(ctx, dst, src, गिनती, iv, decrypt, xtea_crypt_ecb);
}

व्योम av_xtea_le_crypt(AVXTEA *ctx, uint8_t *dst, स्थिर uint8_t *src, पूर्णांक गिनती,
                      uint8_t *iv, पूर्णांक decrypt)
{
    xtea_crypt(ctx, dst, src, गिनती, iv, decrypt, xtea_le_crypt_ecb);
}
