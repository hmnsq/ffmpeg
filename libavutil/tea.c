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

#अन्तर्भाव <string.h>
#अन्तर्भाव "intreadwrite.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "tea.h"

प्रकारनिर्देश संरचना AVTEA {
    uint32_t कुंजी[16];
    पूर्णाङ्क rounds;
} AVTEA;

संरचना AVTEA *av_tea_alloc(शून्य)
{
    प्रत्यागम av_mallocz(परिमाण(संरचना AVTEA));
}

ध्रुव पूर्णाङ्क av_tea_size = परिमाण(AVTEA);

शून्य av_tea_init(AVTEA *ctx, ध्रुव uint8_t कुंजी[16], पूर्णाङ्क rounds)
{
    पूर्णाङ्क i;

    प्रति (i = 0; i < 4; i++)
        ctx->कुंजी[i] = AV_RB32(कुंजी + (i << 2));

    ctx->rounds = rounds;
}

स्थिर शून्य tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, ध्रुव uint8_t *src,
                          पूर्णाङ्क decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    पूर्णाङ्क rounds = ctx->rounds;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->कुंजी[0];
    k1 = ctx->कुंजी[1];
    k2 = ctx->कुंजी[2];
    k3 = ctx->कुंजी[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    यदि (decrypt) {
        पूर्णाङ्क i;
        uint32_t delta = 0x9E3779B9U, sum = delta * (rounds / 2);

        प्रति (i = 0; i < rounds / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            sum -= delta;
        }
        यदि (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            memcpy(iv, src, 8);
        }
    } अन्यथा {
        पूर्णाङ्क i;
        uint32_t sum = 0, delta = 0x9E3779B9U;

        प्रति (i = 0; i < rounds / 2; i++) {
            sum += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

शून्य av_tea_crypt(AVTEA *ctx, uint8_t *dst, ध्रुव uint8_t *src, पूर्णाङ्क गिनती,
                  uint8_t *iv, पूर्णाङ्क decrypt)
{
    पूर्णाङ्क i;

    यदि (decrypt) {
        यावत् (गिनती--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } अन्यथा {
        यावत् (गिनती--) {
            यदि (iv) {
                प्रति (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, रिक्त);
                memcpy(iv, dst, 8);
            } अन्यथा {
                tea_crypt_ecb(ctx, dst, src, decrypt, रिक्त);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
