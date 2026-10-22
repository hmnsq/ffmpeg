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

#অন্তর্ভাব <string.h>

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "aes.h"
#অন্তর্ভাব "aes_internal.h"
#অন্তর্ভাব "attributes.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "intreadwrite.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "thread.h"

ধ্রুব পূর্ণাঙ্ক av_aes_size= পরিমাণ(AVAES);

সংরচনা AVAES *av_aes_alloc(শূন্য)
{
    প্রত্যাগম av_mallocz(পরিমাণ(সংরচনা AVAES));
}

স্থির ধ্রুব uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

স্থির uint8_t     sbox[256];
স্থির uint8_t inv_sbox[256];
#যদি CONFIG_SMALL
স্থির uint32_t enc_multbl[1][256];
স্থির uint32_t dec_multbl[1][256];
#অন্যথা
স্থির uint32_t enc_multbl[4][256];
স্থির uint32_t dec_multbl[4][256];
#endif

#যদি HAVE_BIGENDIAN
#   define ROT(x, s) (((x) >> (s)) | ((x) << (32-(s))))
#অন্যথা
#   define ROT(x, s) (((x) << (s)) | ((x) >> (32-(s))))
#endif

স্থির অন্তঃস্থ শূন্য addkey(av_aes_block *dst, ধ্রুব av_aes_block *src,
                          ধ্রুব av_aes_block *round_চাবি)
{
    dst->u64[0] = src->u64[0] ^ round_চাবি->u64[0];
    dst->u64[1] = src->u64[1] ^ round_চাবি->u64[1];
}

স্থির অন্তঃস্থ শূন্য addkey_s(av_aes_block *dst, ধ্রুব uint8_t *src,
                            ধ্রুব av_aes_block *round_চাবি)
{
    dst->u64[0] = AV_RN64(src)     ^ round_চাবি->u64[0];
    dst->u64[1] = AV_RN64(src + 8) ^ round_চাবি->u64[1];
}

স্থির অন্তঃস্থ শূন্য addkey_d(uint8_t *dst, ধ্রুব av_aes_block *src,
                            ধ্রুব av_aes_block *round_চাবি)
{
    AV_WN64(dst,     src->u64[0] ^ round_চাবি->u64[0]);
    AV_WN64(dst + 8, src->u64[1] ^ round_চাবি->u64[1]);
}

স্থির শূন্য subshift(av_aes_block s0[2], পূর্ণাঙ্ক s, ধ্রুব uint8_t *box)
{
    unsigned বর্ণ *s1_dst = (unsigned বর্ণ*)s0[0].u8 + 3 - s;
    ধ্রুব unsigned বর্ণ *s1_src = s1_dst + পরিমাণ(*s0);
    unsigned বর্ণ *s3_dst = (unsigned বর্ণ*)s0[0].u8 + s + 1;
    ধ্রুব unsigned বর্ণ *s3_src = s3_dst + পরিমাণ(*s0);

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

স্থির অন্তঃস্থ পূর্ণাঙ্ক mix_core(uint32_t multbl[][256], পূর্ণাঙ্ক a, পূর্ণাঙ্ক b, পূর্ণাঙ্ক c, পূর্ণাঙ্ক d)
{
#যদি CONFIG_SMALL
    প্রত্যাগম multbl[0][a] ^ ROT(multbl[0][b], 8) ^ ROT(multbl[0][c], 16) ^ ROT(multbl[0][d], 24);
#অন্যথা
    প্রত্যাগম multbl[0][a] ^ multbl[1][b] ^ multbl[2][c] ^ multbl[3][d];
#endif
}

স্থির অন্তঃস্থ শূন্য mix(av_aes_block state[2], uint32_t multbl[][256], পূর্ণাঙ্ক s1, পূর্ণাঙ্ক s3)
{
    uint8_t (*src)[4] = state[1].u8x4;
    state[0].u32[0] = mix_core(multbl, src[0][0], src[s1    ][1], src[2][2], src[s3    ][3]);
    state[0].u32[1] = mix_core(multbl, src[1][0], src[s3 - 1][1], src[3][2], src[s1 - 1][3]);
    state[0].u32[2] = mix_core(multbl, src[2][0], src[s3    ][1], src[0][2], src[s1    ][3]);
    state[0].u32[3] = mix_core(multbl, src[3][0], src[s1 - 1][1], src[1][2], src[s3 - 1][3]);
}

স্থির অন্তঃস্থ শূন্য aes_crypt(AVAES *a, পূর্ণাঙ্ক s, ধ্রুব uint8_t *sbox_arg,
                         uint32_t multbl[][256])
{
    পূর্ণাঙ্ক r;

    প্রতি (r = a->rounds - 1; r > 0; r--) {
        mix(a->state, multbl, 3 - s, 1 + s);
        addkey(&a->state[1], &a->state[0], &a->round_চাবি[r]);
    }

    subshift(&a->state[0], s, sbox_arg);
}

স্থির শূন্য aes_encrypt(AVAES *a, uint8_t *dst, ধ্রুব uint8_t *src,
                        পূর্ণাঙ্ক গুনতি, uint8_t *iv, পূর্ণাঙ্ক rounds)
{
    যাবত্ (গুনতি--) {
        addkey_s(&a->state[1], src, &a->round_চাবি[rounds]);
        যদি (iv)
            addkey_s(&a->state[1], iv, &a->state[1]);
        aes_crypt(a, 2, sbox, enc_multbl);
        addkey_d(dst, &a->state[0], &a->round_চাবি[0]);
        যদি (iv)
            memcpy(iv, dst, 16);
        src += 16;
        dst += 16;
    }
}

স্থির শূন্য aes_decrypt(AVAES *a, uint8_t *dst, ধ্রুব uint8_t *src,
                        পূর্ণাঙ্ক গুনতি, uint8_t *iv, পূর্ণাঙ্ক rounds)
{
    যাবত্ (গুনতি--) {
        addkey_s(&a->state[1], src, &a->round_চাবি[rounds]);
        aes_crypt(a, 0, inv_sbox, dec_multbl);
        যদি (iv) {
            addkey_s(&a->state[0], iv, &a->state[0]);
            memcpy(iv, src, 16);
        }
        addkey_d(dst, &a->state[0], &a->round_চাবি[0]);
        src += 16;
        dst += 16;
    }
}

শূন্য av_aes_crypt(AVAES *a, uint8_t *dst, ধ্রুব uint8_t *src,
                  পূর্ণাঙ্ক গুনতি, uint8_t *iv, পূর্ণাঙ্ক decrypt)
{
    a->crypt(a, dst, src, গুনতি, iv, a->rounds);
}

স্থির শূন্য init_multbl2(uint32_t tbl[][256], ধ্রুব পূর্ণাঙ্ক c[4],
                         ধ্রুব uint8_t *log8, ধ্রুব uint8_t *alog8,
                         ধ্রুব uint8_t *sbox_arg)
{
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < 256; i++) {
        পূর্ণাঙ্ক x = sbox_arg[i];
        যদি (x) {
            পূর্ণাঙ্ক k, l, m, n;
            x = log8[x];
            k = alog8[x + log8[c[0]]];
            l = alog8[x + log8[c[1]]];
            m = alog8[x + log8[c[2]]];
            n = alog8[x + log8[c[3]]];
            tbl[0][i] = AV_NE(MKBETAG(k, l, m, n), MKTAG(k, l, m, n));
#যদি !CONFIG_SMALL
            tbl[1][i] = ROT(tbl[0][i], 8);
            tbl[2][i] = ROT(tbl[0][i], 16);
            tbl[3][i] = ROT(tbl[0][i], 24);
#endif
        }
    }
}

স্থির AVOnce aes_static_init = AV_ONCE_INIT;

স্থির av_cold শূন্য aes_init_static(শূন্য)
{
    uint8_t log8[256];
    uint8_t alog8[512];
    পূর্ণাঙ্ক i, j = 1;

    প্রতি (i = 0; i < 255; i++) {
        alog8[i] = alog8[i + 255] = j;
        log8[j] = i;
        j ^= j + j;
        যদি (j > 255)
            j ^= 0x11B;
    }
    প্রতি (i = 0; i < 256; i++) {
        j = i ? alog8[255 - log8[i]] : 0;
        j ^= (j << 1) ^ (j << 2) ^ (j << 3) ^ (j << 4);
        j = (j ^ (j >> 8) ^ 99) & 255;
        inv_sbox[j] = i;
        sbox[i]     = j;
    }
    init_multbl2(dec_multbl, (ধ্রুব পূর্ণাঙ্ক[4]) { 0xe, 0x9, 0xd, 0xb },
                 log8, alog8, inv_sbox);
    init_multbl2(enc_multbl, (ধ্রুব পূর্ণাঙ্ক[4]) { 0x2, 0x1, 0x1, 0x3 },
                 log8, alog8, sbox);
}

// this is based on the reference AES code by Paulo Barreto and Vincent Rijmen
পূর্ণাঙ্ক av_aes_init(AVAES *a, ধ্রুব uint8_t *চাবি, পূর্ণাঙ্ক চাবি_bits, পূর্ণাঙ্ক decrypt)
{
    পূর্ণাঙ্ক i, j, t, rconpointer = 0;
    uint8_t tk[8][4];
    পূর্ণাঙ্ক KC = চাবি_bits >> 5;
    পূর্ণাঙ্ক rounds = KC + 6;

    a->rounds = rounds;
    a->crypt = decrypt ? aes_decrypt : aes_encrypt;
#যদি ARCH_X86 && HAVE_X86ASM && HAVE_AESNI_EXTERNAL
    ff_init_aes_x86(a, decrypt);
#নোচেদ্যদি ARCH_AARCH64 && HAVE_ARM_AES
    ff_init_aes_aarch64(a, decrypt);
#endif

    ff_thread_once(&aes_static_init, aes_init_static);

    যদি (চাবি_bits != 128 && চাবি_bits != 192 && চাবি_bits != 256)
        প্রত্যাগম AVERROR(EINVAL);

    memcpy(tk, চাবি, KC * 4);
    memcpy(a->round_চাবি[0].u8, চাবি, KC * 4);

    প্রতি (t = KC * 4; t < (rounds + 1) * 16; t += KC * 4) {
        প্রতি (i = 0; i < 4; i++)
            tk[0][i] ^= sbox[tk[KC - 1][(i + 1) & 3]];
        tk[0][0] ^= rcon[rconpointer++];

        প্রতি (j = 1; j < KC; j++) {
            যদি (KC != 8 || j != KC >> 1)
                প্রতি (i = 0; i < 4; i++)
                    tk[j][i] ^= tk[j - 1][i];
            অন্যথা
                প্রতি (i = 0; i < 4; i++)
                    tk[j][i] ^= sbox[tk[j - 1][i]];
        }

        memcpy((unsigned বর্ণ*)a->round_চাবি + t, tk, KC * 4);
    }

    যদি (decrypt) {
        প্রতি (i = 1; i < rounds; i++) {
            av_aes_block tmp[3];
            tmp[2] = a->round_চাবি[i];
            subshift(&tmp[1], 0, sbox);
            mix(tmp, dec_multbl, 1, 3);
            a->round_চাবি[i] = tmp[0];
        }
    } অন্যথা {
        প্রতি (i = 0; i < (rounds + 1) >> 1; i++)
            FFSWAP(av_aes_block, a->round_চাবি[i], a->round_চাবি[rounds - i]);
    }

    প্রত্যাগম 0;
}
