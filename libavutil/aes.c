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

#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "aes.h"
#અન્તર્ભાવ "aes_internal.h"
#અન્તર્ભાવ "attributes.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "intreadwrite.h"
#અન્તર્ભાવ "macros.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "thread.h"

અચલ પૂર્ણાંક av_aes_size= કદ(AVAES);

સંરચના AVAES *av_aes_alloc(શૂન્ય)
{
    પાછા av_mallocz(કદ(સંરચના AVAES));
}

સ્થિર અચલ uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

સ્થિર uint8_t     sbox[256];
સ્થિર uint8_t inv_sbox[256];
#જો CONFIG_SMALL
સ્થિર uint32_t enc_multbl[1][256];
સ્થિર uint32_t dec_multbl[1][256];
#નહીંતર
સ્થિર uint32_t enc_multbl[4][256];
સ્થિર uint32_t dec_multbl[4][256];
#endif

#જો HAVE_BIGENDIAN
#   define ROT(x, s) (((x) >> (s)) | ((x) << (32-(s))))
#નહીંતર
#   define ROT(x, s) (((x) << (s)) | ((x) >> (32-(s))))
#endif

સ્થિર અંતઃરેખ શૂન્ય addkey(av_aes_block *dst, અચલ av_aes_block *src,
                          અચલ av_aes_block *round_ચાવી)
{
    dst->u64[0] = src->u64[0] ^ round_ચાવી->u64[0];
    dst->u64[1] = src->u64[1] ^ round_ચાવી->u64[1];
}

સ્થિર અંતઃરેખ શૂન્ય addkey_s(av_aes_block *dst, અચલ uint8_t *src,
                            અચલ av_aes_block *round_ચાવી)
{
    dst->u64[0] = AV_RN64(src)     ^ round_ચાવી->u64[0];
    dst->u64[1] = AV_RN64(src + 8) ^ round_ચાવી->u64[1];
}

સ્થિર અંતઃરેખ શૂન્ય addkey_d(uint8_t *dst, અચલ av_aes_block *src,
                            અચલ av_aes_block *round_ચાવી)
{
    AV_WN64(dst,     src->u64[0] ^ round_ચાવી->u64[0]);
    AV_WN64(dst + 8, src->u64[1] ^ round_ચાવી->u64[1]);
}

સ્થિર શૂન્ય subshift(av_aes_block s0[2], પૂર્ણાંક s, અચલ uint8_t *box)
{
    unsigned અક્ષર *s1_dst = (unsigned અક્ષર*)s0[0].u8 + 3 - s;
    અચલ unsigned અક્ષર *s1_src = s1_dst + કદ(*s0);
    unsigned અક્ષર *s3_dst = (unsigned અક્ષર*)s0[0].u8 + s + 1;
    અચલ unsigned અક્ષર *s3_src = s3_dst + કદ(*s0);

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

સ્થિર અંતઃરેખ પૂર્ણાંક mix_core(uint32_t multbl[][256], પૂર્ણાંક a, પૂર્ણાંક b, પૂર્ણાંક c, પૂર્ણાંક d)
{
#જો CONFIG_SMALL
    પાછા multbl[0][a] ^ ROT(multbl[0][b], 8) ^ ROT(multbl[0][c], 16) ^ ROT(multbl[0][d], 24);
#નહીંતર
    પાછા multbl[0][a] ^ multbl[1][b] ^ multbl[2][c] ^ multbl[3][d];
#endif
}

સ્થિર અંતઃરેખ શૂન્ય mix(av_aes_block state[2], uint32_t multbl[][256], પૂર્ણાંક s1, પૂર્ણાંક s3)
{
    uint8_t (*src)[4] = state[1].u8x4;
    state[0].u32[0] = mix_core(multbl, src[0][0], src[s1    ][1], src[2][2], src[s3    ][3]);
    state[0].u32[1] = mix_core(multbl, src[1][0], src[s3 - 1][1], src[3][2], src[s1 - 1][3]);
    state[0].u32[2] = mix_core(multbl, src[2][0], src[s3    ][1], src[0][2], src[s1    ][3]);
    state[0].u32[3] = mix_core(multbl, src[3][0], src[s1 - 1][1], src[1][2], src[s3 - 1][3]);
}

સ્થિર અંતઃરેખ શૂન્ય aes_crypt(AVAES *a, પૂર્ણાંક s, અચલ uint8_t *sbox_arg,
                         uint32_t multbl[][256])
{
    પૂર્ણાંક r;

    માટે (r = a->rounds - 1; r > 0; r--) {
        mix(a->state, multbl, 3 - s, 1 + s);
        addkey(&a->state[1], &a->state[0], &a->round_ચાવી[r]);
    }

    subshift(&a->state[0], s, sbox_arg);
}

સ્થિર શૂન્ય aes_encrypt(AVAES *a, uint8_t *dst, અચલ uint8_t *src,
                        પૂર્ણાંક ગણતરી, uint8_t *iv, પૂર્ણાંક rounds)
{
    જ્યારે (ગણતરી--) {
        addkey_s(&a->state[1], src, &a->round_ચાવી[rounds]);
        જો (iv)
            addkey_s(&a->state[1], iv, &a->state[1]);
        aes_crypt(a, 2, sbox, enc_multbl);
        addkey_d(dst, &a->state[0], &a->round_ચાવી[0]);
        જો (iv)
            memcpy(iv, dst, 16);
        src += 16;
        dst += 16;
    }
}

સ્થિર શૂન્ય aes_decrypt(AVAES *a, uint8_t *dst, અચલ uint8_t *src,
                        પૂર્ણાંક ગણતરી, uint8_t *iv, પૂર્ણાંક rounds)
{
    જ્યારે (ગણતરી--) {
        addkey_s(&a->state[1], src, &a->round_ચાવી[rounds]);
        aes_crypt(a, 0, inv_sbox, dec_multbl);
        જો (iv) {
            addkey_s(&a->state[0], iv, &a->state[0]);
            memcpy(iv, src, 16);
        }
        addkey_d(dst, &a->state[0], &a->round_ચાવી[0]);
        src += 16;
        dst += 16;
    }
}

શૂન્ય av_aes_crypt(AVAES *a, uint8_t *dst, અચલ uint8_t *src,
                  પૂર્ણાંક ગણતરી, uint8_t *iv, પૂર્ણાંક decrypt)
{
    a->crypt(a, dst, src, ગણતરી, iv, a->rounds);
}

સ્થિર શૂન્ય init_multbl2(uint32_t tbl[][256], અચલ પૂર્ણાંક c[4],
                         અચલ uint8_t *log8, અચલ uint8_t *alog8,
                         અચલ uint8_t *sbox_arg)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < 256; i++) {
        પૂર્ણાંક x = sbox_arg[i];
        જો (x) {
            પૂર્ણાંક k, l, m, n;
            x = log8[x];
            k = alog8[x + log8[c[0]]];
            l = alog8[x + log8[c[1]]];
            m = alog8[x + log8[c[2]]];
            n = alog8[x + log8[c[3]]];
            tbl[0][i] = AV_NE(MKBETAG(k, l, m, n), MKTAG(k, l, m, n));
#જો !CONFIG_SMALL
            tbl[1][i] = ROT(tbl[0][i], 8);
            tbl[2][i] = ROT(tbl[0][i], 16);
            tbl[3][i] = ROT(tbl[0][i], 24);
#endif
        }
    }
}

સ્થિર AVOnce aes_static_init = AV_ONCE_INIT;

સ્થિર av_cold શૂન્ય aes_init_static(શૂન્ય)
{
    uint8_t log8[256];
    uint8_t alog8[512];
    પૂર્ણાંક i, j = 1;

    માટે (i = 0; i < 255; i++) {
        alog8[i] = alog8[i + 255] = j;
        log8[j] = i;
        j ^= j + j;
        જો (j > 255)
            j ^= 0x11B;
    }
    માટે (i = 0; i < 256; i++) {
        j = i ? alog8[255 - log8[i]] : 0;
        j ^= (j << 1) ^ (j << 2) ^ (j << 3) ^ (j << 4);
        j = (j ^ (j >> 8) ^ 99) & 255;
        inv_sbox[j] = i;
        sbox[i]     = j;
    }
    init_multbl2(dec_multbl, (અચલ પૂર્ણાંક[4]) { 0xe, 0x9, 0xd, 0xb },
                 log8, alog8, inv_sbox);
    init_multbl2(enc_multbl, (અચલ પૂર્ણાંક[4]) { 0x2, 0x1, 0x1, 0x3 },
                 log8, alog8, sbox);
}

// this is based on the reference AES code by Paulo Barreto and Vincent Rijmen
પૂર્ણાંક av_aes_init(AVAES *a, અચલ uint8_t *ચાવી, પૂર્ણાંક ચાવી_bits, પૂર્ણાંક decrypt)
{
    પૂર્ણાંક i, j, t, rconpointer = 0;
    uint8_t tk[8][4];
    પૂર્ણાંક KC = ચાવી_bits >> 5;
    પૂર્ણાંક rounds = KC + 6;

    a->rounds = rounds;
    a->crypt = decrypt ? aes_decrypt : aes_encrypt;
#જો ARCH_X86 && HAVE_X86ASM && HAVE_AESNI_EXTERNAL
    ff_init_aes_x86(a, decrypt);
#અથવાજો ARCH_AARCH64 && HAVE_ARM_AES
    ff_init_aes_aarch64(a, decrypt);
#endif

    ff_thread_once(&aes_static_init, aes_init_static);

    જો (ચાવી_bits != 128 && ચાવી_bits != 192 && ચાવી_bits != 256)
        પાછા AVERROR(EINVAL);

    memcpy(tk, ચાવી, KC * 4);
    memcpy(a->round_ચાવી[0].u8, ચાવી, KC * 4);

    માટે (t = KC * 4; t < (rounds + 1) * 16; t += KC * 4) {
        માટે (i = 0; i < 4; i++)
            tk[0][i] ^= sbox[tk[KC - 1][(i + 1) & 3]];
        tk[0][0] ^= rcon[rconpointer++];

        માટે (j = 1; j < KC; j++) {
            જો (KC != 8 || j != KC >> 1)
                માટે (i = 0; i < 4; i++)
                    tk[j][i] ^= tk[j - 1][i];
            નહીંતર
                માટે (i = 0; i < 4; i++)
                    tk[j][i] ^= sbox[tk[j - 1][i]];
        }

        memcpy((unsigned અક્ષર*)a->round_ચાવી + t, tk, KC * 4);
    }

    જો (decrypt) {
        માટે (i = 1; i < rounds; i++) {
            av_aes_block tmp[3];
            tmp[2] = a->round_ચાવી[i];
            subshift(&tmp[1], 0, sbox);
            mix(tmp, dec_multbl, 1, 3);
            a->round_ચાવી[i] = tmp[0];
        }
    } નહીંતર {
        માટે (i = 0; i < (rounds + 1) >> 1; i++)
            FFSWAP(av_aes_block, a->round_ચાવી[i], a->round_ચાવી[rounds - i]);
    }

    પાછા 0;
}
