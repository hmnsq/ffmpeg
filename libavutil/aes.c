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

ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ av_aes_size= ಪರಿಮಾಣ(AVAES);

ಸಂರಚನಾ AVAES *av_aes_alloc(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ av_mallocz(ಪರಿಮಾಣ(ಸಂರಚನಾ AVAES));
}

ಸ್ಥಿರ ಧ್ರುವ uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

ಸ್ಥಿರ uint8_t     sbox[256];
ಸ್ಥಿರ uint8_t inv_sbox[256];
#ಯದಿ CONFIG_SMALL
ಸ್ಥಿರ uint32_t enc_multbl[1][256];
ಸ್ಥಿರ uint32_t dec_multbl[1][256];
#ಅನ್ಯಥಾ
ಸ್ಥಿರ uint32_t enc_multbl[4][256];
ಸ್ಥಿರ uint32_t dec_multbl[4][256];
#endif

#ಯದಿ HAVE_BIGENDIAN
#   define ROT(x, s) (((x) >> (s)) | ((x) << (32-(s))))
#ಅನ್ಯಥಾ
#   define ROT(x, s) (((x) << (s)) | ((x) >> (32-(s))))
#endif

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ addkey(av_aes_block *dst, ಧ್ರುವ av_aes_block *src,
                          ಧ್ರುವ av_aes_block *round_ಕೀಲಿ)
{
    dst->u64[0] = src->u64[0] ^ round_ಕೀಲಿ->u64[0];
    dst->u64[1] = src->u64[1] ^ round_ಕೀಲಿ->u64[1];
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ addkey_s(av_aes_block *dst, ಧ್ರುವ uint8_t *src,
                            ಧ್ರುವ av_aes_block *round_ಕೀಲಿ)
{
    dst->u64[0] = AV_RN64(src)     ^ round_ಕೀಲಿ->u64[0];
    dst->u64[1] = AV_RN64(src + 8) ^ round_ಕೀಲಿ->u64[1];
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ addkey_d(uint8_t *dst, ಧ್ರುವ av_aes_block *src,
                            ಧ್ರುವ av_aes_block *round_ಕೀಲಿ)
{
    AV_WN64(dst,     src->u64[0] ^ round_ಕೀಲಿ->u64[0]);
    AV_WN64(dst + 8, src->u64[1] ^ round_ಕೀಲಿ->u64[1]);
}

ಸ್ಥಿರ ಶೂನ್ಯ subshift(av_aes_block s0[2], ಪೂರ್ಣಾಙ್ಕ s, ಧ್ರುವ uint8_t *box)
{
    unsigned ವರ್ಣ *s1_dst = (unsigned ವರ್ಣ*)s0[0].u8 + 3 - s;
    ಧ್ರುವ unsigned ವರ್ಣ *s1_src = s1_dst + ಪರಿಮಾಣ(*s0);
    unsigned ವರ್ಣ *s3_dst = (unsigned ವರ್ಣ*)s0[0].u8 + s + 1;
    ಧ್ರುವ unsigned ವರ್ಣ *s3_src = s3_dst + ಪರಿಮಾಣ(*s0);

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

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಪೂರ್ಣಾಙ್ಕ mix_core(uint32_t multbl[][256], ಪೂರ್ಣಾಙ್ಕ a, ಪೂರ್ಣಾಙ್ಕ b, ಪೂರ್ಣಾಙ್ಕ c, ಪೂರ್ಣಾಙ್ಕ d)
{
#ಯದಿ CONFIG_SMALL
    ಪ್ರತ್ಯಾಗಮ multbl[0][a] ^ ROT(multbl[0][b], 8) ^ ROT(multbl[0][c], 16) ^ ROT(multbl[0][d], 24);
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ multbl[0][a] ^ multbl[1][b] ^ multbl[2][c] ^ multbl[3][d];
#endif
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ mix(av_aes_block state[2], uint32_t multbl[][256], ಪೂರ್ಣಾಙ್ಕ s1, ಪೂರ್ಣಾಙ್ಕ s3)
{
    uint8_t (*src)[4] = state[1].u8x4;
    state[0].u32[0] = mix_core(multbl, src[0][0], src[s1    ][1], src[2][2], src[s3    ][3]);
    state[0].u32[1] = mix_core(multbl, src[1][0], src[s3 - 1][1], src[3][2], src[s1 - 1][3]);
    state[0].u32[2] = mix_core(multbl, src[2][0], src[s3    ][1], src[0][2], src[s1    ][3]);
    state[0].u32[3] = mix_core(multbl, src[3][0], src[s1 - 1][1], src[1][2], src[s3 - 1][3]);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ aes_crypt(AVAES *a, ಪೂರ್ಣಾಙ್ಕ s, ಧ್ರುವ uint8_t *sbox_arg,
                         uint32_t multbl[][256])
{
    ಪೂರ್ಣಾಙ್ಕ r;

    ಪ್ರತಿ (r = a->rounds - 1; r > 0; r--) {
        mix(a->state, multbl, 3 - s, 1 + s);
        addkey(&a->state[1], &a->state[0], &a->round_ಕೀಲಿ[r]);
    }

    subshift(&a->state[0], s, sbox_arg);
}

ಸ್ಥಿರ ಶೂನ್ಯ aes_encrypt(AVAES *a, uint8_t *dst, ಧ್ರುವ uint8_t *src,
                        ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ, uint8_t *iv, ಪೂರ್ಣಾಙ್ಕ rounds)
{
    ಯಾವತ್ (ಎಣಿಕೆ--) {
        addkey_s(&a->state[1], src, &a->round_ಕೀಲಿ[rounds]);
        ಯದಿ (iv)
            addkey_s(&a->state[1], iv, &a->state[1]);
        aes_crypt(a, 2, sbox, enc_multbl);
        addkey_d(dst, &a->state[0], &a->round_ಕೀಲಿ[0]);
        ಯದಿ (iv)
            memcpy(iv, dst, 16);
        src += 16;
        dst += 16;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ aes_decrypt(AVAES *a, uint8_t *dst, ಧ್ರುವ uint8_t *src,
                        ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ, uint8_t *iv, ಪೂರ್ಣಾಙ್ಕ rounds)
{
    ಯಾವತ್ (ಎಣಿಕೆ--) {
        addkey_s(&a->state[1], src, &a->round_ಕೀಲಿ[rounds]);
        aes_crypt(a, 0, inv_sbox, dec_multbl);
        ಯದಿ (iv) {
            addkey_s(&a->state[0], iv, &a->state[0]);
            memcpy(iv, src, 16);
        }
        addkey_d(dst, &a->state[0], &a->round_ಕೀಲಿ[0]);
        src += 16;
        dst += 16;
    }
}

ಶೂನ್ಯ av_aes_crypt(AVAES *a, uint8_t *dst, ಧ್ರುವ uint8_t *src,
                  ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ, uint8_t *iv, ಪೂರ್ಣಾಙ್ಕ decrypt)
{
    a->crypt(a, dst, src, ಎಣಿಕೆ, iv, a->rounds);
}

ಸ್ಥಿರ ಶೂನ್ಯ init_multbl2(uint32_t tbl[][256], ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ c[4],
                         ಧ್ರುವ uint8_t *log8, ಧ್ರುವ uint8_t *alog8,
                         ಧ್ರುವ uint8_t *sbox_arg)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < 256; i++) {
        ಪೂರ್ಣಾಙ್ಕ x = sbox_arg[i];
        ಯದಿ (x) {
            ಪೂರ್ಣಾಙ್ಕ k, l, m, n;
            x = log8[x];
            k = alog8[x + log8[c[0]]];
            l = alog8[x + log8[c[1]]];
            m = alog8[x + log8[c[2]]];
            n = alog8[x + log8[c[3]]];
            tbl[0][i] = AV_NE(MKBETAG(k, l, m, n), MKTAG(k, l, m, n));
#ಯದಿ !CONFIG_SMALL
            tbl[1][i] = ROT(tbl[0][i], 8);
            tbl[2][i] = ROT(tbl[0][i], 16);
            tbl[3][i] = ROT(tbl[0][i], 24);
#endif
        }
    }
}

ಸ್ಥಿರ AVOnce aes_static_init = AV_ONCE_INIT;

ಸ್ಥಿರ av_cold ಶೂನ್ಯ aes_init_static(ಶೂನ್ಯ)
{
    uint8_t log8[256];
    uint8_t alog8[512];
    ಪೂರ್ಣಾಙ್ಕ i, j = 1;

    ಪ್ರತಿ (i = 0; i < 255; i++) {
        alog8[i] = alog8[i + 255] = j;
        log8[j] = i;
        j ^= j + j;
        ಯದಿ (j > 255)
            j ^= 0x11B;
    }
    ಪ್ರತಿ (i = 0; i < 256; i++) {
        j = i ? alog8[255 - log8[i]] : 0;
        j ^= (j << 1) ^ (j << 2) ^ (j << 3) ^ (j << 4);
        j = (j ^ (j >> 8) ^ 99) & 255;
        inv_sbox[j] = i;
        sbox[i]     = j;
    }
    init_multbl2(dec_multbl, (ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ[4]) { 0xe, 0x9, 0xd, 0xb },
                 log8, alog8, inv_sbox);
    init_multbl2(enc_multbl, (ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ[4]) { 0x2, 0x1, 0x1, 0x3 },
                 log8, alog8, sbox);
}

// this is based on the reference AES code by Paulo Barreto and Vincent Rijmen
ಪೂರ್ಣಾಙ್ಕ av_aes_init(AVAES *a, ಧ್ರುವ uint8_t *ಕೀಲಿ, ಪೂರ್ಣಾಙ್ಕ ಕೀಲಿ_bits, ಪೂರ್ಣಾಙ್ಕ decrypt)
{
    ಪೂರ್ಣಾಙ್ಕ i, j, t, rconpointer = 0;
    uint8_t tk[8][4];
    ಪೂರ್ಣಾಙ್ಕ KC = ಕೀಲಿ_bits >> 5;
    ಪೂರ್ಣಾಙ್ಕ rounds = KC + 6;

    a->rounds = rounds;
    a->crypt = decrypt ? aes_decrypt : aes_encrypt;
#ಯದಿ ARCH_X86 && HAVE_X86ASM && HAVE_AESNI_EXTERNAL
    ff_init_aes_x86(a, decrypt);
#ನೋಚೇದ್ಯದಿ ARCH_AARCH64 && HAVE_ARM_AES
    ff_init_aes_aarch64(a, decrypt);
#endif

    ff_thread_once(&aes_static_init, aes_init_static);

    ಯದಿ (ಕೀಲಿ_bits != 128 && ಕೀಲಿ_bits != 192 && ಕೀಲಿ_bits != 256)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    memcpy(tk, ಕೀಲಿ, KC * 4);
    memcpy(a->round_ಕೀಲಿ[0].u8, ಕೀಲಿ, KC * 4);

    ಪ್ರತಿ (t = KC * 4; t < (rounds + 1) * 16; t += KC * 4) {
        ಪ್ರತಿ (i = 0; i < 4; i++)
            tk[0][i] ^= sbox[tk[KC - 1][(i + 1) & 3]];
        tk[0][0] ^= rcon[rconpointer++];

        ಪ್ರತಿ (j = 1; j < KC; j++) {
            ಯದಿ (KC != 8 || j != KC >> 1)
                ಪ್ರತಿ (i = 0; i < 4; i++)
                    tk[j][i] ^= tk[j - 1][i];
            ಅನ್ಯಥಾ
                ಪ್ರತಿ (i = 0; i < 4; i++)
                    tk[j][i] ^= sbox[tk[j - 1][i]];
        }

        memcpy((unsigned ವರ್ಣ*)a->round_ಕೀಲಿ + t, tk, KC * 4);
    }

    ಯದಿ (decrypt) {
        ಪ್ರತಿ (i = 1; i < rounds; i++) {
            av_aes_block tmp[3];
            tmp[2] = a->round_ಕೀಲಿ[i];
            subshift(&tmp[1], 0, sbox);
            mix(tmp, dec_multbl, 1, 3);
            a->round_ಕೀಲಿ[i] = tmp[0];
        }
    } ಅನ್ಯಥಾ {
        ಪ್ರತಿ (i = 0; i < (rounds + 1) >> 1; i++)
            FFSWAP(av_aes_block, a->round_ಕೀಲಿ[i], a->round_ಕೀಲಿ[rounds - i]);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}
