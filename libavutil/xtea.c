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

#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "xtea.h"

AVXTEA *av_xtea_alloc(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ av_mallocz(ಪರಿಮಾಣ(ಸಂರಚನಾ AVXTEA));
}

ಶೂನ್ಯ av_xtea_init(AVXTEA *ctx, ಧ್ರುವ uint8_t ಕೀಲಿ[16])
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < 4; i++)
        ctx->ಕೀಲಿ[i] = AV_RB32(ಕೀಲಿ + (i << 2));
}

ಶೂನ್ಯ av_xtea_le_init(AVXTEA *ctx, ಧ್ರುವ uint8_t ಕೀಲಿ[16])
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < 4; i++)
        ctx->ಕೀಲಿ[i] = AV_RL32(ಕೀಲಿ + (i << 2));
}

ಸ್ಥಿರ ಶೂನ್ಯ xtea_crypt_ecb(AVXTEA *ctx, uint8_t *dst, ಧ್ರುವ uint8_t *src,
                           ಪೂರ್ಣಾಙ್ಕ decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
#ಯದಿ !CONFIG_SMALL
    uint32_t k0 = ctx->ಕೀಲಿ[0];
    uint32_t k1 = ctx->ಕೀಲಿ[1];
    uint32_t k2 = ctx->ಕೀಲಿ[2];
    uint32_t k3 = ctx->ಕೀಲಿ[3];
#endif

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    ಯದಿ (decrypt) {
#ಯದಿ CONFIG_SMALL
        ಪೂರ್ಣಾಙ್ಕ i;
        uint32_t delta = 0x9E3779B9U, sum = delta * 32;

        ಪ್ರತಿ (i = 0; i < 32; i++) {
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + ctx->ಕೀಲಿ[(sum >> 11) & 3]);
            sum -= delta;
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + ctx->ಕೀಲಿ[sum & 3]);
        }
#ಅನ್ಯಥಾ
#define DSTEP(SUM, K0, K1) \
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (SUM + K0); \
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (SUM - 0x9E3779B9U + K1)

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
#endif
        ಯದಿ (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            memcpy(iv, src, 8);
        }
    } ಅನ್ಯಥಾ {
#ಯದಿ CONFIG_SMALL
        ಪೂರ್ಣಾಙ್ಕ i;
        uint32_t sum = 0, delta = 0x9E3779B9U;

        ಪ್ರತಿ (i = 0; i < 32; i++) {
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + ctx->ಕೀಲಿ[sum & 3]);
            sum += delta;
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + ctx->ಕೀಲಿ[(sum >> 11) & 3]);
        }
#ಅನ್ಯಥಾ
#define ESTEP(SUM, K0, K1) \
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (SUM + K0);\
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (SUM + 0x9E3779B9U + K1)
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
#endif
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

ಸ್ಥಿರ ಶೂನ್ಯ xtea_le_crypt_ecb(AVXTEA *ctx, uint8_t *dst, ಧ್ರುವ uint8_t *src,
                              ಪೂರ್ಣಾಙ್ಕ decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    ಪೂರ್ಣಾಙ್ಕ i;

    v0 = AV_RL32(src);
    v1 = AV_RL32(src + 4);

    ಯದಿ (decrypt) {
        uint32_t delta = 0x9E3779B9, sum = delta * 32;

        ಪ್ರತಿ (i = 0; i < 32; i++) {
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + ctx->ಕೀಲಿ[(sum >> 11) & 3]);
            sum -= delta;
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + ctx->ಕೀಲಿ[sum & 3]);
        }
        ಯದಿ (iv) {
            v0 ^= AV_RL32(iv);
            v1 ^= AV_RL32(iv + 4);
            memcpy(iv, src, 8);
        }
    } ಅನ್ಯಥಾ {
        uint32_t sum = 0, delta = 0x9E3779B9;

        ಪ್ರತಿ (i = 0; i < 32; i++) {
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + ctx->ಕೀಲಿ[sum & 3]);
            sum += delta;
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + ctx->ಕೀಲಿ[(sum >> 11) & 3]);
        }
    }

    AV_WL32(dst, v0);
    AV_WL32(dst + 4, v1);
}

ಸ್ಥಿರ ಶೂನ್ಯ xtea_crypt(AVXTEA *ctx, uint8_t *dst, ಧ್ರುವ uint8_t *src, ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ,
                       uint8_t *iv, ಪೂರ್ಣಾಙ್ಕ decrypt,
                       ಶೂನ್ಯ (*crypt)(AVXTEA *, uint8_t *, ಧ್ರುವ uint8_t *, ಪೂರ್ಣಾಙ್ಕ, uint8_t *))
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (decrypt) {
        ಯಾವತ್ (ಎಣಿಕೆ--) {
            crypt(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } ಅನ್ಯಥಾ {
        ಯಾವತ್ (ಎಣಿಕೆ--) {
            ಯದಿ (iv) {
                ಪ್ರತಿ (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                crypt(ctx, dst, dst, decrypt, ರಿಕ್ತ);
                memcpy(iv, dst, 8);
            } ಅನ್ಯಥಾ {
                crypt(ctx, dst, src, decrypt, ರಿಕ್ತ);
            }
            src   += 8;
            dst   += 8;
        }
    }
}

ಶೂನ್ಯ av_xtea_crypt(AVXTEA *ctx, uint8_t *dst, ಧ್ರುವ uint8_t *src, ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ,
                   uint8_t *iv, ಪೂರ್ಣಾಙ್ಕ decrypt)
{
    xtea_crypt(ctx, dst, src, ಎಣಿಕೆ, iv, decrypt, xtea_crypt_ecb);
}

ಶೂನ್ಯ av_xtea_le_crypt(AVXTEA *ctx, uint8_t *dst, ಧ್ರುವ uint8_t *src, ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ,
                      uint8_t *iv, ಪೂರ್ಣಾಙ್ಕ decrypt)
{
    xtea_crypt(ctx, dst, src, ಎಣಿಕೆ, iv, decrypt, xtea_le_crypt_ecb);
}
