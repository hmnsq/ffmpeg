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

#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "aes.h"
#അന്തര്ഭാവ "aes_internal.h"
#അന്തര്ഭാവ "attributes.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "intreadwrite.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "thread.h"

സ്ഥിരം പൂർണ്ണസംഖ്യ av_aes_size= വലുപ്പം(AVAES);

ഘടന AVAES *av_aes_alloc(ശൂന്യം)
{
    തിരികെ av_mallocz(വലുപ്പം(ഘടന AVAES));
}

സ്ഥിതം സ്ഥിരം uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

സ്ഥിതം uint8_t     sbox[256];
സ്ഥിതം uint8_t inv_sbox[256];
#എങ്കിൽ CONFIG_SMALL
സ്ഥിതം uint32_t enc_multbl[1][256];
സ്ഥിതം uint32_t dec_multbl[1][256];
#അല്ലെങ്കിൽ
സ്ഥിതം uint32_t enc_multbl[4][256];
സ്ഥിതം uint32_t dec_multbl[4][256];
#endif

#എങ്കിൽ HAVE_BIGENDIAN
#   define ROT(x, s) (((x) >> (s)) | ((x) << (32-(s))))
#അല്ലെങ്കിൽ
#   define ROT(x, s) (((x) << (s)) | ((x) >> (32-(s))))
#endif

സ്ഥിതം വരിയിൽ ശൂന്യം addkey(av_aes_block *dst, സ്ഥിരം av_aes_block *src,
                          സ്ഥിരം av_aes_block *round_താക്കോൽ)
{
    dst->u64[0] = src->u64[0] ^ round_താക്കോൽ->u64[0];
    dst->u64[1] = src->u64[1] ^ round_താക്കോൽ->u64[1];
}

സ്ഥിതം വരിയിൽ ശൂന്യം addkey_s(av_aes_block *dst, സ്ഥിരം uint8_t *src,
                            സ്ഥിരം av_aes_block *round_താക്കോൽ)
{
    dst->u64[0] = AV_RN64(src)     ^ round_താക്കോൽ->u64[0];
    dst->u64[1] = AV_RN64(src + 8) ^ round_താക്കോൽ->u64[1];
}

സ്ഥിതം വരിയിൽ ശൂന്യം addkey_d(uint8_t *dst, സ്ഥിരം av_aes_block *src,
                            സ്ഥിരം av_aes_block *round_താക്കോൽ)
{
    AV_WN64(dst,     src->u64[0] ^ round_താക്കോൽ->u64[0]);
    AV_WN64(dst + 8, src->u64[1] ^ round_താക്കോൽ->u64[1]);
}

സ്ഥിതം ശൂന്യം subshift(av_aes_block s0[2], പൂർണ്ണസംഖ്യ s, സ്ഥിരം uint8_t *box)
{
    unsigned അക്ഷരം *s1_dst = (unsigned അക്ഷരം*)s0[0].u8 + 3 - s;
    സ്ഥിരം unsigned അക്ഷരം *s1_src = s1_dst + വലുപ്പം(*s0);
    unsigned അക്ഷരം *s3_dst = (unsigned അക്ഷരം*)s0[0].u8 + s + 1;
    സ്ഥിരം unsigned അക്ഷരം *s3_src = s3_dst + വലുപ്പം(*s0);

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

സ്ഥിതം വരിയിൽ പൂർണ്ണസംഖ്യ mix_core(uint32_t multbl[][256], പൂർണ്ണസംഖ്യ a, പൂർണ്ണസംഖ്യ b, പൂർണ്ണസംഖ്യ c, പൂർണ്ണസംഖ്യ d)
{
#എങ്കിൽ CONFIG_SMALL
    തിരികെ multbl[0][a] ^ ROT(multbl[0][b], 8) ^ ROT(multbl[0][c], 16) ^ ROT(multbl[0][d], 24);
#അല്ലെങ്കിൽ
    തിരികെ multbl[0][a] ^ multbl[1][b] ^ multbl[2][c] ^ multbl[3][d];
#endif
}

സ്ഥിതം വരിയിൽ ശൂന്യം mix(av_aes_block state[2], uint32_t multbl[][256], പൂർണ്ണസംഖ്യ s1, പൂർണ്ണസംഖ്യ s3)
{
    uint8_t (*src)[4] = state[1].u8x4;
    state[0].u32[0] = mix_core(multbl, src[0][0], src[s1    ][1], src[2][2], src[s3    ][3]);
    state[0].u32[1] = mix_core(multbl, src[1][0], src[s3 - 1][1], src[3][2], src[s1 - 1][3]);
    state[0].u32[2] = mix_core(multbl, src[2][0], src[s3    ][1], src[0][2], src[s1    ][3]);
    state[0].u32[3] = mix_core(multbl, src[3][0], src[s1 - 1][1], src[1][2], src[s3 - 1][3]);
}

സ്ഥിതം വരിയിൽ ശൂന്യം aes_crypt(AVAES *a, പൂർണ്ണസംഖ്യ s, സ്ഥിരം uint8_t *sbox_arg,
                         uint32_t multbl[][256])
{
    പൂർണ്ണസംഖ്യ r;

    വേണ്ടി (r = a->rounds - 1; r > 0; r--) {
        mix(a->state, multbl, 3 - s, 1 + s);
        addkey(&a->state[1], &a->state[0], &a->round_താക്കോൽ[r]);
    }

    subshift(&a->state[0], s, sbox_arg);
}

സ്ഥിതം ശൂന്യം aes_encrypt(AVAES *a, uint8_t *dst, സ്ഥിരം uint8_t *src,
                        പൂർണ്ണസംഖ്യ എണ്ണം, uint8_t *iv, പൂർണ്ണസംഖ്യ rounds)
{
    ആകുമ്പോൾ (എണ്ണം--) {
        addkey_s(&a->state[1], src, &a->round_താക്കോൽ[rounds]);
        എങ്കിൽ (iv)
            addkey_s(&a->state[1], iv, &a->state[1]);
        aes_crypt(a, 2, sbox, enc_multbl);
        addkey_d(dst, &a->state[0], &a->round_താക്കോൽ[0]);
        എങ്കിൽ (iv)
            memcpy(iv, dst, 16);
        src += 16;
        dst += 16;
    }
}

സ്ഥിതം ശൂന്യം aes_decrypt(AVAES *a, uint8_t *dst, സ്ഥിരം uint8_t *src,
                        പൂർണ്ണസംഖ്യ എണ്ണം, uint8_t *iv, പൂർണ്ണസംഖ്യ rounds)
{
    ആകുമ്പോൾ (എണ്ണം--) {
        addkey_s(&a->state[1], src, &a->round_താക്കോൽ[rounds]);
        aes_crypt(a, 0, inv_sbox, dec_multbl);
        എങ്കിൽ (iv) {
            addkey_s(&a->state[0], iv, &a->state[0]);
            memcpy(iv, src, 16);
        }
        addkey_d(dst, &a->state[0], &a->round_താക്കോൽ[0]);
        src += 16;
        dst += 16;
    }
}

ശൂന്യം av_aes_crypt(AVAES *a, uint8_t *dst, സ്ഥിരം uint8_t *src,
                  പൂർണ്ണസംഖ്യ എണ്ണം, uint8_t *iv, പൂർണ്ണസംഖ്യ decrypt)
{
    a->crypt(a, dst, src, എണ്ണം, iv, a->rounds);
}

സ്ഥിതം ശൂന്യം init_multbl2(uint32_t tbl[][256], സ്ഥിരം പൂർണ്ണസംഖ്യ c[4],
                         സ്ഥിരം uint8_t *log8, സ്ഥിരം uint8_t *alog8,
                         സ്ഥിരം uint8_t *sbox_arg)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < 256; i++) {
        പൂർണ്ണസംഖ്യ x = sbox_arg[i];
        എങ്കിൽ (x) {
            പൂർണ്ണസംഖ്യ k, l, m, n;
            x = log8[x];
            k = alog8[x + log8[c[0]]];
            l = alog8[x + log8[c[1]]];
            m = alog8[x + log8[c[2]]];
            n = alog8[x + log8[c[3]]];
            tbl[0][i] = AV_NE(MKBETAG(k, l, m, n), MKTAG(k, l, m, n));
#എങ്കിൽ !CONFIG_SMALL
            tbl[1][i] = ROT(tbl[0][i], 8);
            tbl[2][i] = ROT(tbl[0][i], 16);
            tbl[3][i] = ROT(tbl[0][i], 24);
#endif
        }
    }
}

സ്ഥിതം AVOnce aes_static_init = AV_ONCE_INIT;

സ്ഥിതം av_cold ശൂന്യം aes_init_static(ശൂന്യം)
{
    uint8_t log8[256];
    uint8_t alog8[512];
    പൂർണ്ണസംഖ്യ i, j = 1;

    വേണ്ടി (i = 0; i < 255; i++) {
        alog8[i] = alog8[i + 255] = j;
        log8[j] = i;
        j ^= j + j;
        എങ്കിൽ (j > 255)
            j ^= 0x11B;
    }
    വേണ്ടി (i = 0; i < 256; i++) {
        j = i ? alog8[255 - log8[i]] : 0;
        j ^= (j << 1) ^ (j << 2) ^ (j << 3) ^ (j << 4);
        j = (j ^ (j >> 8) ^ 99) & 255;
        inv_sbox[j] = i;
        sbox[i]     = j;
    }
    init_multbl2(dec_multbl, (സ്ഥിരം പൂർണ്ണസംഖ്യ[4]) { 0xe, 0x9, 0xd, 0xb },
                 log8, alog8, inv_sbox);
    init_multbl2(enc_multbl, (സ്ഥിരം പൂർണ്ണസംഖ്യ[4]) { 0x2, 0x1, 0x1, 0x3 },
                 log8, alog8, sbox);
}

// this is based on the reference AES code by Paulo Barreto and Vincent Rijmen
പൂർണ്ണസംഖ്യ av_aes_init(AVAES *a, സ്ഥിരം uint8_t *താക്കോൽ, പൂർണ്ണസംഖ്യ താക്കോൽ_bits, പൂർണ്ണസംഖ്യ decrypt)
{
    പൂർണ്ണസംഖ്യ i, j, t, rconpointer = 0;
    uint8_t tk[8][4];
    പൂർണ്ണസംഖ്യ KC = താക്കോൽ_bits >> 5;
    പൂർണ്ണസംഖ്യ rounds = KC + 6;

    a->rounds = rounds;
    a->crypt = decrypt ? aes_decrypt : aes_encrypt;
#എങ്കിൽ ARCH_X86 && HAVE_X86ASM && HAVE_AESNI_EXTERNAL
    ff_init_aes_x86(a, decrypt);
#അല്ലെങ്കിലെങ്കിൽ ARCH_AARCH64 && HAVE_ARM_AES
    ff_init_aes_aarch64(a, decrypt);
#endif

    ff_thread_once(&aes_static_init, aes_init_static);

    എങ്കിൽ (താക്കോൽ_bits != 128 && താക്കോൽ_bits != 192 && താക്കോൽ_bits != 256)
        തിരികെ AVERROR(EINVAL);

    memcpy(tk, താക്കോൽ, KC * 4);
    memcpy(a->round_താക്കോൽ[0].u8, താക്കോൽ, KC * 4);

    വേണ്ടി (t = KC * 4; t < (rounds + 1) * 16; t += KC * 4) {
        വേണ്ടി (i = 0; i < 4; i++)
            tk[0][i] ^= sbox[tk[KC - 1][(i + 1) & 3]];
        tk[0][0] ^= rcon[rconpointer++];

        വേണ്ടി (j = 1; j < KC; j++) {
            എങ്കിൽ (KC != 8 || j != KC >> 1)
                വേണ്ടി (i = 0; i < 4; i++)
                    tk[j][i] ^= tk[j - 1][i];
            അല്ലെങ്കിൽ
                വേണ്ടി (i = 0; i < 4; i++)
                    tk[j][i] ^= sbox[tk[j - 1][i]];
        }

        memcpy((unsigned അക്ഷരം*)a->round_താക്കോൽ + t, tk, KC * 4);
    }

    എങ്കിൽ (decrypt) {
        വേണ്ടി (i = 1; i < rounds; i++) {
            av_aes_block tmp[3];
            tmp[2] = a->round_താക്കോൽ[i];
            subshift(&tmp[1], 0, sbox);
            mix(tmp, dec_multbl, 1, 3);
            a->round_താക്കോൽ[i] = tmp[0];
        }
    } അല്ലെങ്കിൽ {
        വേണ്ടി (i = 0; i < (rounds + 1) >> 1; i++)
            FFSWAP(av_aes_block, a->round_താക്കോൽ[i], a->round_താക്കോൽ[rounds - i]);
    }

    തിരികെ 0;
}
