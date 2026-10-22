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

#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "aes.h"
#ଅନ୍ତର୍ଭାଵ "aes_internal.h"
#ଅନ୍ତର୍ଭାଵ "attributes.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "intreadwrite.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "thread.h"

ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_aes_size= ଆକାର(AVAES);

ସଂରଚନା AVAES *av_aes_alloc(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ av_mallocz(ଆକାର(ସଂରଚନା AVAES));
}

ସ୍ଥିର ଅଚଳ uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

ସ୍ଥିର uint8_t     sbox[256];
ସ୍ଥିର uint8_t inv_sbox[256];
#ଯଦି CONFIG_SMALL
ସ୍ଥିର uint32_t enc_multbl[1][256];
ସ୍ଥିର uint32_t dec_multbl[1][256];
#ଅନ୍ୟଥା
ସ୍ଥିର uint32_t enc_multbl[4][256];
ସ୍ଥିର uint32_t dec_multbl[4][256];
#endif

#ଯଦି HAVE_BIGENDIAN
#   define ROT(x, s) (((x) >> (s)) | ((x) << (32-(s))))
#ଅନ୍ୟଥା
#   define ROT(x, s) (((x) << (s)) | ((x) >> (32-(s))))
#endif

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ addkey(av_aes_block *dst, ଅଚଳ av_aes_block *src,
                          ଅଚଳ av_aes_block *round_ଚାବି)
{
    dst->u64[0] = src->u64[0] ^ round_ଚାବି->u64[0];
    dst->u64[1] = src->u64[1] ^ round_ଚାବି->u64[1];
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ addkey_s(av_aes_block *dst, ଅଚଳ uint8_t *src,
                            ଅଚଳ av_aes_block *round_ଚାବି)
{
    dst->u64[0] = AV_RN64(src)     ^ round_ଚାବି->u64[0];
    dst->u64[1] = AV_RN64(src + 8) ^ round_ଚାବି->u64[1];
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ addkey_d(uint8_t *dst, ଅଚଳ av_aes_block *src,
                            ଅଚଳ av_aes_block *round_ଚାବି)
{
    AV_WN64(dst,     src->u64[0] ^ round_ଚାବି->u64[0]);
    AV_WN64(dst + 8, src->u64[1] ^ round_ଚାବି->u64[1]);
}

ସ୍ଥିର ଶୂନ୍ୟ subshift(av_aes_block s0[2], ପୂର୍ଣ୍ଣସଂଖ୍ୟା s, ଅଚଳ uint8_t *box)
{
    unsigned ଅକ୍ଷର *s1_dst = (unsigned ଅକ୍ଷର*)s0[0].u8 + 3 - s;
    ଅଚଳ unsigned ଅକ୍ଷର *s1_src = s1_dst + ଆକାର(*s0);
    unsigned ଅକ୍ଷର *s3_dst = (unsigned ଅକ୍ଷର*)s0[0].u8 + s + 1;
    ଅଚଳ unsigned ଅକ୍ଷର *s3_src = s3_dst + ଆକାର(*s0);

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

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ପୂର୍ଣ୍ଣସଂଖ୍ୟା mix_core(uint32_t multbl[][256], ପୂର୍ଣ୍ଣସଂଖ୍ୟା a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା b, ପୂର୍ଣ୍ଣସଂଖ୍ୟା c, ପୂର୍ଣ୍ଣସଂଖ୍ୟା d)
{
#ଯଦି CONFIG_SMALL
    ଫେରନ୍ତୁ multbl[0][a] ^ ROT(multbl[0][b], 8) ^ ROT(multbl[0][c], 16) ^ ROT(multbl[0][d], 24);
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ multbl[0][a] ^ multbl[1][b] ^ multbl[2][c] ^ multbl[3][d];
#endif
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ mix(av_aes_block state[2], uint32_t multbl[][256], ପୂର୍ଣ୍ଣସଂଖ୍ୟା s1, ପୂର୍ଣ୍ଣସଂଖ୍ୟା s3)
{
    uint8_t (*src)[4] = state[1].u8x4;
    state[0].u32[0] = mix_core(multbl, src[0][0], src[s1    ][1], src[2][2], src[s3    ][3]);
    state[0].u32[1] = mix_core(multbl, src[1][0], src[s3 - 1][1], src[3][2], src[s1 - 1][3]);
    state[0].u32[2] = mix_core(multbl, src[2][0], src[s3    ][1], src[0][2], src[s1    ][3]);
    state[0].u32[3] = mix_core(multbl, src[3][0], src[s1 - 1][1], src[1][2], src[s3 - 1][3]);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ aes_crypt(AVAES *a, ପୂର୍ଣ୍ଣସଂଖ୍ୟା s, ଅଚଳ uint8_t *sbox_arg,
                         uint32_t multbl[][256])
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା r;

    ପାଇଁ (r = a->rounds - 1; r > 0; r--) {
        mix(a->state, multbl, 3 - s, 1 + s);
        addkey(&a->state[1], &a->state[0], &a->round_ଚାବି[r]);
    }

    subshift(&a->state[0], s, sbox_arg);
}

ସ୍ଥିର ଶୂନ୍ୟ aes_encrypt(AVAES *a, uint8_t *dst, ଅଚଳ uint8_t *src,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds)
{
    ଯେତେବେଳେ (ଗଣନା_2--) {
        addkey_s(&a->state[1], src, &a->round_ଚାବି[rounds]);
        ଯଦି (iv)
            addkey_s(&a->state[1], iv, &a->state[1]);
        aes_crypt(a, 2, sbox, enc_multbl);
        addkey_d(dst, &a->state[0], &a->round_ଚାବି[0]);
        ଯଦି (iv)
            memcpy(iv, dst, 16);
        src += 16;
        dst += 16;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ aes_decrypt(AVAES *a, uint8_t *dst, ଅଚଳ uint8_t *src,
                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds)
{
    ଯେତେବେଳେ (ଗଣନା_2--) {
        addkey_s(&a->state[1], src, &a->round_ଚାବି[rounds]);
        aes_crypt(a, 0, inv_sbox, dec_multbl);
        ଯଦି (iv) {
            addkey_s(&a->state[0], iv, &a->state[0]);
            memcpy(iv, src, 16);
        }
        addkey_d(dst, &a->state[0], &a->round_ଚାବି[0]);
        src += 16;
        dst += 16;
    }
}

ଶୂନ୍ୟ av_aes_crypt(AVAES *a, uint8_t *dst, ଅଚଳ uint8_t *src,
                  ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2, uint8_t *iv, ପୂର୍ଣ୍ଣସଂଖ୍ୟା decrypt)
{
    a->crypt(a, dst, src, ଗଣନା_2, iv, a->rounds);
}

ସ୍ଥିର ଶୂନ୍ୟ init_multbl2(uint32_t tbl[][256], ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା c[4],
                         ଅଚଳ uint8_t *log8, ଅଚଳ uint8_t *alog8,
                         ଅଚଳ uint8_t *sbox_arg)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < 256; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା x = sbox_arg[i];
        ଯଦି (x) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା k, l, m, n;
            x = log8[x];
            k = alog8[x + log8[c[0]]];
            l = alog8[x + log8[c[1]]];
            m = alog8[x + log8[c[2]]];
            n = alog8[x + log8[c[3]]];
            tbl[0][i] = AV_NE(MKBETAG(k, l, m, n), MKTAG(k, l, m, n));
#ଯଦି !CONFIG_SMALL
            tbl[1][i] = ROT(tbl[0][i], 8);
            tbl[2][i] = ROT(tbl[0][i], 16);
            tbl[3][i] = ROT(tbl[0][i], 24);
#endif
        }
    }
}

ସ୍ଥିର AVOnce aes_static_init = AV_ONCE_INIT;

ସ୍ଥିର av_cold ଶୂନ୍ୟ aes_init_static(ଶୂନ୍ୟ)
{
    uint8_t log8[256];
    uint8_t alog8[512];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j = 1;

    ପାଇଁ (i = 0; i < 255; i++) {
        alog8[i] = alog8[i + 255] = j;
        log8[j] = i;
        j ^= j + j;
        ଯଦି (j > 255)
            j ^= 0x11B;
    }
    ପାଇଁ (i = 0; i < 256; i++) {
        j = i ? alog8[255 - log8[i]] : 0;
        j ^= (j << 1) ^ (j << 2) ^ (j << 3) ^ (j << 4);
        j = (j ^ (j >> 8) ^ 99) & 255;
        inv_sbox[j] = i;
        sbox[i]     = j;
    }
    init_multbl2(dec_multbl, (ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା[4]) { 0xe, 0x9, 0xd, 0xb },
                 log8, alog8, inv_sbox);
    init_multbl2(enc_multbl, (ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା[4]) { 0x2, 0x1, 0x1, 0x3 },
                 log8, alog8, sbox);
}

// this is based on the reference AES code by Paulo Barreto and Vincent Rijmen
ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_aes_init(AVAES *a, ଅଚଳ uint8_t *ଚାବି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଚାବି_bits, ପୂର୍ଣ୍ଣସଂଖ୍ୟା decrypt)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j, t, rconpointer = 0;
    uint8_t tk[8][4];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା KC = ଚାବି_bits >> 5;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rounds = KC + 6;

    a->rounds = rounds;
    a->crypt = decrypt ? aes_decrypt : aes_encrypt;
#ଯଦି ARCH_X86 && HAVE_X86ASM && HAVE_AESNI_EXTERNAL
    ff_init_aes_x86(a, decrypt);
#ନଚେତଯଦି ARCH_AARCH64 && HAVE_ARM_AES
    ff_init_aes_aarch64(a, decrypt);
#endif

    ff_thread_once(&aes_static_init, aes_init_static);

    ଯଦି (ଚାବି_bits != 128 && ଚାବି_bits != 192 && ଚାବି_bits != 256)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    memcpy(tk, ଚାବି, KC * 4);
    memcpy(a->round_ଚାବି[0].u8, ଚାବି, KC * 4);

    ପାଇଁ (t = KC * 4; t < (rounds + 1) * 16; t += KC * 4) {
        ପାଇଁ (i = 0; i < 4; i++)
            tk[0][i] ^= sbox[tk[KC - 1][(i + 1) & 3]];
        tk[0][0] ^= rcon[rconpointer++];

        ପାଇଁ (j = 1; j < KC; j++) {
            ଯଦି (KC != 8 || j != KC >> 1)
                ପାଇଁ (i = 0; i < 4; i++)
                    tk[j][i] ^= tk[j - 1][i];
            ଅନ୍ୟଥା
                ପାଇଁ (i = 0; i < 4; i++)
                    tk[j][i] ^= sbox[tk[j - 1][i]];
        }

        memcpy((unsigned ଅକ୍ଷର*)a->round_ଚାବି + t, tk, KC * 4);
    }

    ଯଦି (decrypt) {
        ପାଇଁ (i = 1; i < rounds; i++) {
            av_aes_block tmp[3];
            tmp[2] = a->round_ଚାବି[i];
            subshift(&tmp[1], 0, sbox);
            mix(tmp, dec_multbl, 1, 3);
            a->round_ଚାବି[i] = tmp[0];
        }
    } ଅନ୍ୟଥା {
        ପାଇଁ (i = 0; i < (rounds + 1) >> 1; i++)
            FFSWAP(av_aes_block, a->round_ଚାବି[i], a->round_ଚାବି[rounds - i]);
    }

    ଫେରନ୍ତୁ 0;
}
