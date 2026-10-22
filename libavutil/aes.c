/*
 * copyright (c) 2007 Michael Niedermayer <michaelni@gmx.at>
 *
 * some optimization ideas from aes128.c by Reimar Doeffinger
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

#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "aes.h"
#ಅನ್ತರ್ಭಾವ "aes_internal.h"
#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "thread.h"

ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ av_aes_ಗಾತ್ರ= ಗಾತ್ರ(AVAES);

ರಚನೆ AVAES *av_aes_alloc(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ av_mallocz(ಗಾತ್ರ(ರಚನೆ AVAES));
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

ಸ್ಥಿರ uint8_t     sbox[256];
ಸ್ಥಿರ uint8_t inv_sbox[256];
#ಆದರೆ CONFIG_SMALL
ಸ್ಥಿರ uint32_t enc_multbl[1][256];
ಸ್ಥಿರ uint32_t dec_multbl[1][256];
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ uint32_t enc_multbl[4][256];
ಸ್ಥಿರ uint32_t dec_multbl[4][256];
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_BIGENDIAN
#   define ROT(x, s) (((x) >> (s)) | ((x) << (32-(s))))
#ಇಲ್ಲದಿದ್ದರೆ
#   define ROT(x, s) (((x) << (s)) | ((x) >> (32-(s))))
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ addkey(av_aes_ಖಂಡ *dst, ಸ್ಥಿರಾಂಕ av_aes_ಖಂಡ *src,
                          ಸ್ಥಿರಾಂಕ av_aes_ಖಂಡ *ಸುತ್ತು_ಕೀಲಿ)
{
    dst->u64[0] = src->u64[0] ^ ಸುತ್ತು_ಕೀಲಿ->u64[0];
    dst->u64[1] = src->u64[1] ^ ಸುತ್ತು_ಕೀಲಿ->u64[1];
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ addkey_s(av_aes_ಖಂಡ *dst, ಸ್ಥಿರಾಂಕ uint8_t *src,
                            ಸ್ಥಿರಾಂಕ av_aes_ಖಂಡ *ಸುತ್ತು_ಕೀಲಿ)
{
    dst->u64[0] = AV_RN64(src)     ^ ಸುತ್ತು_ಕೀಲಿ->u64[0];
    dst->u64[1] = AV_RN64(src + 8) ^ ಸುತ್ತು_ಕೀಲಿ->u64[1];
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ addkey_d(uint8_t *dst, ಸ್ಥಿರಾಂಕ av_aes_ಖಂಡ *src,
                            ಸ್ಥಿರಾಂಕ av_aes_ಖಂಡ *ಸುತ್ತು_ಕೀಲಿ)
{
    AV_WN64(dst,     src->u64[0] ^ ಸುತ್ತು_ಕೀಲಿ->u64[0]);
    AV_WN64(dst + 8, src->u64[1] ^ ಸುತ್ತು_ಕೀಲಿ->u64[1]);
}

ಸ್ಥಿರ ಶೂನ್ಯ subshift(av_aes_ಖಂಡ s0[2], ಪೂರ್ಣಾಂಕ s, ಸ್ಥಿರಾಂಕ uint8_t *box)
{
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *s1_dst = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ*)s0[0].u8 + 3 - s;
    ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *s1_src = s1_dst + ಗಾತ್ರ(*s0);
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *s3_dst = (ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ*)s0[0].u8 + s + 1;
    ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *s3_src = s3_dst + ಗಾತ್ರ(*s0);

    s0[0].u8[ 0] = box[s0[1].u8[ 0]];
    s0[0].u8[ 4] = box[s0[1].u8[ 4]];
    s0[0].u8[ 8] = box[s0[1].u8[ 8]];
    s0[0].u8[12] = box[s0[1].u8[12]];
    s1_dst[ 0] = box[s1_src[ 4]];
    s1_dst[ 4] = box[s1_src[ 8]];
    s1_dst[ 8] = box[s1_src[12]];
    s1_dst[12] = box[s1_src[ 0]];
    s0[0].u8[ 2] = box[s0[1].u8[10]];
    s0[0].u8[10] = box[s0[1].u8[ 2]];
    s0[0].u8[ 6] = box[s0[1].u8[14]];
    s0[0].u8[14] = box[s0[1].u8[ 6]];
    s3_dst[ 0] = box[s3_src[12]];
    s3_dst[12] = box[s3_src[ 8]];
    s3_dst[ 8] = box[s3_src[ 4]];
    s3_dst[ 4] = box[s3_src[ 0]];
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಪೂರ್ಣಾಂಕ mix_core(uint32_t multbl[][256], ಪೂರ್ಣಾಂಕ a, ಪೂರ್ಣಾಂಕ b, ಪೂರ್ಣಾಂಕ c, ಪೂರ್ಣಾಂಕ d)
{
#ಆದರೆ CONFIG_SMALL
    ಹಿಂತಿರುಗಿ multbl[0][a] ^ ROT(multbl[0][b], 8) ^ ROT(multbl[0][c], 16) ^ ROT(multbl[0][d], 24);
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ multbl[0][a] ^ multbl[1][b] ^ multbl[2][c] ^ multbl[3][d];
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ mix(av_aes_ಖಂಡ state[2], uint32_t multbl[][256], ಪೂರ್ಣಾಂಕ s1, ಪೂರ್ಣಾಂಕ s3)
{
    uint8_t (*src)[4] = state[1].u8x4;
    state[0].u32[0] = mix_core(multbl, src[0][0], src[s1    ][1], src[2][2], src[s3    ][3]);
    state[0].u32[1] = mix_core(multbl, src[1][0], src[s3 - 1][1], src[3][2], src[s1 - 1][3]);
    state[0].u32[2] = mix_core(multbl, src[2][0], src[s3    ][1], src[0][2], src[s1    ][3]);
    state[0].u32[3] = mix_core(multbl, src[3][0], src[s1 - 1][1], src[1][2], src[s3 - 1][3]);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ aes_crypt(AVAES *a, ಪೂರ್ಣಾಂಕ s, ಸ್ಥಿರಾಂಕ uint8_t *sbox_arg,
                         uint32_t multbl[][256])
{
    ಪೂರ್ಣಾಂಕ r;

    ಗಾಗಿ (r = a->ಸುತ್ತುಗಳು - 1; r > 0; r--) {
        mix(a->state, multbl, 3 - s, 1 + s);
        addkey(&a->state[1], &a->state[0], &a->ಸುತ್ತು_ಕೀಲಿ[r]);
    }

    subshift(&a->state[0], s, sbox_arg);
}

ಸ್ಥಿರ ಶೂನ್ಯ aes_encrypt(AVAES *a, uint8_t *dst, ಸ್ಥಿರಾಂಕ uint8_t *src,
                        ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, uint8_t *iv, ಪೂರ್ಣಾಂಕ ಸುತ್ತುಗಳು)
{
    ಆಗ (ಎಣಿಕೆ_2--) {
        addkey_s(&a->state[1], src, &a->ಸುತ್ತು_ಕೀಲಿ[ಸುತ್ತುಗಳು]);
        ಆದರೆ (iv)
            addkey_s(&a->state[1], iv, &a->state[1]);
        aes_crypt(a, 2, sbox, enc_multbl);
        addkey_d(dst, &a->state[0], &a->ಸುತ್ತು_ಕೀಲಿ[0]);
        ಆದರೆ (iv)
            ಸ್ಮರಣೆ_ನಕಲು(iv, dst, 16);
        src += 16;
        dst += 16;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ aes_decrypt(AVAES *a, uint8_t *dst, ಸ್ಥಿರಾಂಕ uint8_t *src,
                        ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, uint8_t *iv, ಪೂರ್ಣಾಂಕ ಸುತ್ತುಗಳು)
{
    ಆಗ (ಎಣಿಕೆ_2--) {
        addkey_s(&a->state[1], src, &a->ಸುತ್ತು_ಕೀಲಿ[ಸುತ್ತುಗಳು]);
        aes_crypt(a, 0, inv_sbox, dec_multbl);
        ಆದರೆ (iv) {
            addkey_s(&a->state[0], iv, &a->state[0]);
            ಸ್ಮರಣೆ_ನಕಲು(iv, src, 16);
        }
        addkey_d(dst, &a->state[0], &a->ಸುತ್ತು_ಕೀಲಿ[0]);
        src += 16;
        dst += 16;
    }
}

ಶೂನ್ಯ av_aes_crypt(AVAES *a, uint8_t *dst, ಸ್ಥಿರಾಂಕ uint8_t *src,
                  ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2, uint8_t *iv, ಪೂರ್ಣಾಂಕ decrypt)
{
    a->crypt(a, dst, src, ಎಣಿಕೆ_2, iv, a->ಸುತ್ತುಗಳು);
}

ಸ್ಥಿರ ಶೂನ್ಯ init_multbl2(uint32_t tbl[][256], ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ c[4],
                         ಸ್ಥಿರಾಂಕ uint8_t *log8, ಸ್ಥಿರಾಂಕ uint8_t *alog8,
                         ಸ್ಥಿರಾಂಕ uint8_t *sbox_arg)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < 256; i++) {
        ಪೂರ್ಣಾಂಕ x = sbox_arg[i];
        ಆದರೆ (x) {
            ಪೂರ್ಣಾಂಕ k, l, m, n;
            x = log8[x];
            k = alog8[x + log8[c[0]]];
            l = alog8[x + log8[c[1]]];
            m = alog8[x + log8[c[2]]];
            n = alog8[x + log8[c[3]]];
            tbl[0][i] = AV_NE(MKBETAG(k, l, m, n), MKTAG(k, l, m, n));
#ಆದರೆ !CONFIG_SMALL
            tbl[1][i] = ROT(tbl[0][i], 8);
            tbl[2][i] = ROT(tbl[0][i], 16);
            tbl[3][i] = ROT(tbl[0][i], 24);
#ಆದರೆ_ಅಂತ್ಯ
        }
    }
}

ಸ್ಥಿರ AVOnce aes_static_init = AV_ONCE_INIT;

ಸ್ಥಿರ av_cold ಶೂನ್ಯ aes_init_static(ಶೂನ್ಯ)
{
    uint8_t log8[256];
    uint8_t alog8[512];
    ಪೂರ್ಣಾಂಕ i, j = 1;

    ಗಾಗಿ (i = 0; i < 255; i++) {
        alog8[i] = alog8[i + 255] = j;
        log8[j] = i;
        j ^= j + j;
        ಆದರೆ (j > 255)
            j ^= 0x11B;
    }
    ಗಾಗಿ (i = 0; i < 256; i++) {
        j = i ? alog8[255 - log8[i]] : 0;
        j ^= (j << 1) ^ (j << 2) ^ (j << 3) ^ (j << 4);
        j = (j ^ (j >> 8) ^ 99) & 255;
        inv_sbox[j] = i;
        sbox[i]     = j;
    }
    init_multbl2(dec_multbl, (ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ[4]) { 0xe, 0x9, 0xd, 0xb },
                 log8, alog8, inv_sbox);
    init_multbl2(enc_multbl, (ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ[4]) { 0x2, 0x1, 0x1, 0x3 },
                 log8, alog8, sbox);
}

// this is based on the reference AES code by Paulo Barreto and Vincent Rijmen
ಪೂರ್ಣಾಂಕ av_aes_init(AVAES *a, ಸ್ಥಿರಾಂಕ uint8_t *ಕೀಲಿ, ಪೂರ್ಣಾಂಕ ಕೀಲಿ_ಬಿಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ decrypt)
{
    ಪೂರ್ಣಾಂಕ i, j, t, rconpointer = 0;
    uint8_t tk[8][4];
    ಪೂರ್ಣಾಂಕ KC = ಕೀಲಿ_ಬಿಟ್ಟುಗಳು >> 5;
    ಪೂರ್ಣಾಂಕ ಸುತ್ತುಗಳು = KC + 6;

    a->ಸುತ್ತುಗಳು = ಸುತ್ತುಗಳು;
    a->crypt = decrypt ? aes_decrypt : aes_encrypt;
#ಆದರೆ ARCH_X86 && HAVE_X86ASM && HAVE_AESNI_EXTERNAL
    ff_init_aes_x86(a, decrypt);
#ಅಥವಾಆದರೆ ARCH_AARCH64 && HAVE_ARM_AES
    ff_init_aes_aarch64(a, decrypt);
#ಆದರೆ_ಅಂತ್ಯ

    ff_thread_once(&aes_static_init, aes_init_static);

    ಆದರೆ (ಕೀಲಿ_ಬಿಟ್ಟುಗಳು != 128 && ಕೀಲಿ_ಬಿಟ್ಟುಗಳು != 192 && ಕೀಲಿ_ಬಿಟ್ಟುಗಳು != 256)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಸ್ಮರಣೆ_ನಕಲು(tk, ಕೀಲಿ, KC * 4);
    ಸ್ಮರಣೆ_ನಕಲು(a->ಸುತ್ತು_ಕೀಲಿ[0].u8, ಕೀಲಿ, KC * 4);

    ಗಾಗಿ (t = KC * 4; t < (ಸುತ್ತುಗಳು + 1) * 16; t += KC * 4) {
        ಗಾಗಿ (i = 0; i < 4; i++)
            tk[0][i] ^= sbox[tk[KC - 1][(i + 1) & 3]];
        tk[0][0] ^= rcon[rconpointer++];

        ಗಾಗಿ (j = 1; j < KC; j++) {
            ಆದರೆ (KC != 8 || j != KC >> 1)
                ಗಾಗಿ (i = 0; i < 4; i++)
                    tk[j][i] ^= tk[j - 1][i];
            ಇಲ್ಲದಿದ್ದರೆ
                ಗಾಗಿ (i = 0; i < 4; i++)
                    tk[j][i] ^= sbox[tk[j - 1][i]];
        }

        ಸ್ಮರಣೆ_ನಕಲು((ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ*)a->ಸುತ್ತು_ಕೀಲಿ + t, tk, KC * 4);
    }

    ಆದರೆ (decrypt) {
        ಗಾಗಿ (i = 1; i < ಸುತ್ತುಗಳು; i++) {
            av_aes_ಖಂಡ tmp[3];
            tmp[2] = a->ಸುತ್ತು_ಕೀಲಿ[i];
            subshift(&tmp[1], 0, sbox);
            mix(tmp, dec_multbl, 1, 3);
            a->ಸುತ್ತು_ಕೀಲಿ[i] = tmp[0];
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಗಾಗಿ (i = 0; i < (ಸುತ್ತುಗಳು + 1) >> 1; i++)
            FFSWAP(av_aes_ಖಂಡ, a->ಸುತ್ತು_ಕೀಲಿ[i], a->ಸುತ್ತು_ಕೀಲಿ[ಸುತ್ತುಗಳು - i]);
    }

    ಹಿಂತಿರುಗಿ 0;
}
