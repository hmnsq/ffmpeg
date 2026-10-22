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

#അന്തര്ഭാവ <string.h>
#അന്തര്ഭാവ "intreadwrite.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "tea.h"

തരനിർവചനം ഘടന AVTEA {
    uint32_t താക്കോൽ[16];
    പൂർണ്ണസംഖ്യ rounds;
} AVTEA;

ഘടന AVTEA *av_tea_alloc(ശൂന്യം)
{
    തിരികെ av_mallocz(വലുപ്പം(ഘടന AVTEA));
}

സ്ഥിരം പൂർണ്ണസംഖ്യ av_tea_size = വലുപ്പം(AVTEA);

ശൂന്യം av_tea_init(AVTEA *ctx, സ്ഥിരം uint8_t താക്കോൽ[16], പൂർണ്ണസംഖ്യ rounds)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < 4; i++)
        ctx->താക്കോൽ[i] = AV_RB32(താക്കോൽ + (i << 2));

    ctx->rounds = rounds;
}

സ്ഥിതം ശൂന്യം tea_crypt_ecb(AVTEA *ctx, uint8_t *dst, സ്ഥിരം uint8_t *src,
                          പൂർണ്ണസംഖ്യ decrypt, uint8_t *iv)
{
    uint32_t v0, v1;
    പൂർണ്ണസംഖ്യ rounds = ctx->rounds;
    uint32_t k0, k1, k2, k3;
    k0 = ctx->താക്കോൽ[0];
    k1 = ctx->താക്കോൽ[1];
    k2 = ctx->താക്കോൽ[2];
    k3 = ctx->താക്കോൽ[3];

    v0 = AV_RB32(src);
    v1 = AV_RB32(src + 4);

    എങ്കിൽ (decrypt) {
        പൂർണ്ണസംഖ്യ i;
        uint32_t delta = 0x9E3779B9U, sum = delta * (rounds / 2);

        വേണ്ടി (i = 0; i < rounds / 2; i++) {
            v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
            v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            sum -= delta;
        }
        എങ്കിൽ (iv) {
            v0 ^= AV_RB32(iv);
            v1 ^= AV_RB32(iv + 4);
            memcpy(iv, src, 8);
        }
    } അല്ലെങ്കിൽ {
        പൂർണ്ണസംഖ്യ i;
        uint32_t sum = 0, delta = 0x9E3779B9U;

        വേണ്ടി (i = 0; i < rounds / 2; i++) {
            sum += delta;
            v0 += ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
            v1 += ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        }
    }

    AV_WB32(dst, v0);
    AV_WB32(dst + 4, v1);
}

ശൂന്യം av_tea_crypt(AVTEA *ctx, uint8_t *dst, സ്ഥിരം uint8_t *src, പൂർണ്ണസംഖ്യ എണ്ണം,
                  uint8_t *iv, പൂർണ്ണസംഖ്യ decrypt)
{
    പൂർണ്ണസംഖ്യ i;

    എങ്കിൽ (decrypt) {
        ആകുമ്പോൾ (എണ്ണം--) {
            tea_crypt_ecb(ctx, dst, src, decrypt, iv);

            src   += 8;
            dst   += 8;
        }
    } അല്ലെങ്കിൽ {
        ആകുമ്പോൾ (എണ്ണം--) {
            എങ്കിൽ (iv) {
                വേണ്ടി (i = 0; i < 8; i++)
                    dst[i] = src[i] ^ iv[i];
                tea_crypt_ecb(ctx, dst, dst, decrypt, ശൂന്യ);
                memcpy(iv, dst, 8);
            } അല്ലെങ്കിൽ {
                tea_crypt_ecb(ctx, dst, src, decrypt, ശൂന്യ);
            }
            src   += 8;
            dst   += 8;
        }
    }
}
