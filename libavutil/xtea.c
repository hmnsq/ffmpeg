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

#অন্তর্ভাব <string.h>
#অন্তর্ভাব "config.h"
#অন্তর্ভাব "intreadwrite.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "xtea.h"

AVXTEA *av_xtea_alloc(শূন্য)
{
    প্রত্যাগম av_mallocz(পরিমাণ(সংরচনা AVXTEA));
}

শূন্য av_xtea_init(AVXTEA *ctx, ধ্রুব uint8_t চাবি[16])
{
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < 4; i++)
        ctx->চাবি[i] = AV_RB32(চাবি + (i << 2));
}

শূন্য av_xtea_le_init(AVXTEA *ctx, ধ্রুব uint8_t চাবি[16])
{
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < 4; i++)
        ctx->চাবি[i] = AV_RL32(চাবি + (i << 2));
}

স্থির শূন্য xtea_crypt_ecb(AVXTEA *ctx, uint8_t *dst, ধ্রুব uint8_t *src,
                           পূর্ণাঙ্ক decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
#যদি !CONFIG_SMALL
    uint32_t k0 = ctx->চাবি[0];
    uint32_t k1 = ctx->চাবি[1];
    uint32_t k2 = ctx->চাবি[2];
    uint32_t k3 = ctx->চাবি[3];
#endif

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    যদি (decrypt) {
#যদি CONFIG_SMALL
        পূর্ণাঙ্ক i;
        uint32_t delta = 0x9E3779B9U, sum = delta * 32;

        প্রতি (i = 0; i < 32; i++) {
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + ctx->চাবি[(sum >> 11) & 3]);
            sum -= delta;
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + ctx->চাবি[sum & 3]);
        }
#অন্যথা
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
        যদি (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            memcpy(iv, src, 8);
        }
    } অন্যথা {
#যদি CONFIG_SMALL
        পূর্ণাঙ্ক i;
        uint32_t sum = 0, delta = 0x9E3779B9U;

        প্রতি (i = 0; i < 32; i++) {
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + ctx->চাবি[sum & 3]);
            sum += delta;
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + ctx->চাবি[(sum >> 11) & 3]);
        }
#অন্যথা
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

স্থির শূন্য xtea_le_crypt_ecb(AVXTEA *ctx, uint8_t *dst, ধ্রুব uint8_t *src,
                              পূর্ণাঙ্ক decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    পূর্ণাঙ্ক i;

    v0 = AV_RL32(src);
    v1 = AV_RL32(src + 4);

    যদি (decrypt) {
        uint32_t delta = 0x9E3779B9, sum = delta * 32;

        প্রতি (i = 0; i < 32; i++) {
            v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + ctx->চাবি[(sum >> 11) & 3]);
            sum -= delta;
            v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + ctx->চাবি[sum & 3]);
        }
        যদি (iv) {
            v0 ^= AV_RL32(iv);
            v1 ^= AV_RL32(iv + 4);
            memcpy(iv, src, 8);
        }
    } অন্যথা {
        uint32_t sum = 0, delta = 0x9E3779B9;

        প্রতি (i = 0; i < 32; i++) {
            v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + ctx->চাবি[sum & 3]);
            sum += delta;
            v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + ctx->চাবি[(sum >> 11) & 3]);
        }
    }

    AV_WL32(dst, v0);
    AV_WL32(dst + 4, v1);
}

স্থির শূন্য xtea_crypt(AVXTEA *ctx, uint8_t *dst, ধ্রুব uint8_t *src, পূর্ণাঙ্ক গুনতি,
                       uint8_t *iv, পূর্ণাঙ্ক decrypt,
                       শূন্য (*crypt)(AVXTEA *, uint8_t *, ধ্রুব uint8_t *, পূর্ণাঙ্ক, uint8_t *))
{
    পূর্ণাঙ্ক i;

    যদি (decrypt) {
        যাবত্ (গুনতি--) {
            crypt(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } অন্যথা {
        যাবত্ (গুনতি--) {
            যদি (iv) {
                প্রতি (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                crypt(ctx, dst, dst, decrypt, রিক্ত);
                memcpy(iv, dst, 8);
            } অন্যথা {
                crypt(ctx, dst, src, decrypt, রিক্ত);
            }
            src   += 8;
            dst   += 8;
        }
    }
}

শূন্য av_xtea_crypt(AVXTEA *ctx, uint8_t *dst, ধ্রুব uint8_t *src, পূর্ণাঙ্ক গুনতি,
                   uint8_t *iv, পূর্ণাঙ্ক decrypt)
{
    xtea_crypt(ctx, dst, src, গুনতি, iv, decrypt, xtea_crypt_ecb);
}

শূন্য av_xtea_le_crypt(AVXTEA *ctx, uint8_t *dst, ধ্রুব uint8_t *src, পূর্ণাঙ্ক গুনতি,
                      uint8_t *iv, পূর্ণাঙ্ক decrypt)
{
    xtea_crypt(ctx, dst, src, গুনতি, iv, decrypt, xtea_le_crypt_ecb);
}
