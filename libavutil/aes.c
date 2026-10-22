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

#அந்தர்பாவ <string.h>

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "aes.h"
#அந்தர்பாவ "aes_internal.h"
#அந்தர்பாவ "attributes.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "intreadwrite.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "thread.h"

மாறிலி முழு av_aes_size= அளவு(AVAES);

கட்டமைப்பு AVAES *av_aes_alloc(வெறுமை)
{
    திரும்பு av_mallocz(அளவு(கட்டமைப்பு AVAES));
}

நிலையான மாறிலி uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

நிலையான uint8_t     sbox[256];
நிலையான uint8_t inv_sbox[256];
#எனில் CONFIG_SMALL
நிலையான uint32_t enc_multbl[1][256];
நிலையான uint32_t dec_multbl[1][256];
#இல்லையெனில்
நிலையான uint32_t enc_multbl[4][256];
நிலையான uint32_t dec_multbl[4][256];
#endif

#எனில் HAVE_BIGENDIAN
#   define ROT(x, s) (((x) >> (s)) | ((x) << (32-(s))))
#இல்லையெனில்
#   define ROT(x, s) (((x) << (s)) | ((x) >> (32-(s))))
#endif

நிலையான உள்வரி வெறுமை addkey(av_aes_block *dst, மாறிலி av_aes_block *src,
                          மாறிலி av_aes_block *round_சாவி)
{
    dst->u64[0] = src->u64[0] ^ round_சாவி->u64[0];
    dst->u64[1] = src->u64[1] ^ round_சாவி->u64[1];
}

நிலையான உள்வரி வெறுமை addkey_s(av_aes_block *dst, மாறிலி uint8_t *src,
                            மாறிலி av_aes_block *round_சாவி)
{
    dst->u64[0] = AV_RN64(src)     ^ round_சாவி->u64[0];
    dst->u64[1] = AV_RN64(src + 8) ^ round_சாவி->u64[1];
}

நிலையான உள்வரி வெறுமை addkey_d(uint8_t *dst, மாறிலி av_aes_block *src,
                            மாறிலி av_aes_block *round_சாவி)
{
    AV_WN64(dst,     src->u64[0] ^ round_சாவி->u64[0]);
    AV_WN64(dst + 8, src->u64[1] ^ round_சாவி->u64[1]);
}

நிலையான வெறுமை subshift(av_aes_block s0[2], முழு s, மாறிலி uint8_t *box)
{
    unsigned எழுத்து *s1_dst = (unsigned எழுத்து*)s0[0].u8 + 3 - s;
    மாறிலி unsigned எழுத்து *s1_src = s1_dst + அளவு(*s0);
    unsigned எழுத்து *s3_dst = (unsigned எழுத்து*)s0[0].u8 + s + 1;
    மாறிலி unsigned எழுத்து *s3_src = s3_dst + அளவு(*s0);

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

நிலையான உள்வரி முழு mix_core(uint32_t multbl[][256], முழு a, முழு b, முழு c, முழு d)
{
#எனில் CONFIG_SMALL
    திரும்பு multbl[0][a] ^ ROT(multbl[0][b], 8) ^ ROT(multbl[0][c], 16) ^ ROT(multbl[0][d], 24);
#இல்லையெனில்
    திரும்பு multbl[0][a] ^ multbl[1][b] ^ multbl[2][c] ^ multbl[3][d];
#endif
}

நிலையான உள்வரி வெறுமை mix(av_aes_block state[2], uint32_t multbl[][256], முழு s1, முழு s3)
{
    uint8_t (*src)[4] = state[1].u8x4;
    state[0].u32[0] = mix_core(multbl, src[0][0], src[s1    ][1], src[2][2], src[s3    ][3]);
    state[0].u32[1] = mix_core(multbl, src[1][0], src[s3 - 1][1], src[3][2], src[s1 - 1][3]);
    state[0].u32[2] = mix_core(multbl, src[2][0], src[s3    ][1], src[0][2], src[s1    ][3]);
    state[0].u32[3] = mix_core(multbl, src[3][0], src[s1 - 1][1], src[1][2], src[s3 - 1][3]);
}

நிலையான உள்வரி வெறுமை aes_crypt(AVAES *a, முழு s, மாறிலி uint8_t *sbox_arg,
                         uint32_t multbl[][256])
{
    முழு r;

    க்கு (r = a->rounds - 1; r > 0; r--) {
        mix(a->state, multbl, 3 - s, 1 + s);
        addkey(&a->state[1], &a->state[0], &a->round_சாவி[r]);
    }

    subshift(&a->state[0], s, sbox_arg);
}

நிலையான வெறுமை aes_encrypt(AVAES *a, uint8_t *dst, மாறிலி uint8_t *src,
                        முழு மொத்தம், uint8_t *iv, முழு rounds)
{
    போது (மொத்தம்--) {
        addkey_s(&a->state[1], src, &a->round_சாவி[rounds]);
        எனில் (iv)
            addkey_s(&a->state[1], iv, &a->state[1]);
        aes_crypt(a, 2, sbox, enc_multbl);
        addkey_d(dst, &a->state[0], &a->round_சாவி[0]);
        எனில் (iv)
            memcpy(iv, dst, 16);
        src += 16;
        dst += 16;
    }
}

நிலையான வெறுமை aes_decrypt(AVAES *a, uint8_t *dst, மாறிலி uint8_t *src,
                        முழு மொத்தம், uint8_t *iv, முழு rounds)
{
    போது (மொத்தம்--) {
        addkey_s(&a->state[1], src, &a->round_சாவி[rounds]);
        aes_crypt(a, 0, inv_sbox, dec_multbl);
        எனில் (iv) {
            addkey_s(&a->state[0], iv, &a->state[0]);
            memcpy(iv, src, 16);
        }
        addkey_d(dst, &a->state[0], &a->round_சாவி[0]);
        src += 16;
        dst += 16;
    }
}

வெறுமை av_aes_crypt(AVAES *a, uint8_t *dst, மாறிலி uint8_t *src,
                  முழு மொத்தம், uint8_t *iv, முழு decrypt)
{
    a->crypt(a, dst, src, மொத்தம், iv, a->rounds);
}

நிலையான வெறுமை init_multbl2(uint32_t tbl[][256], மாறிலி முழு c[4],
                         மாறிலி uint8_t *log8, மாறிலி uint8_t *alog8,
                         மாறிலி uint8_t *sbox_arg)
{
    முழு i;

    க்கு (i = 0; i < 256; i++) {
        முழு x = sbox_arg[i];
        எனில் (x) {
            முழு k, l, m, n;
            x = log8[x];
            k = alog8[x + log8[c[0]]];
            l = alog8[x + log8[c[1]]];
            m = alog8[x + log8[c[2]]];
            n = alog8[x + log8[c[3]]];
            tbl[0][i] = AV_NE(MKBETAG(k, l, m, n), MKTAG(k, l, m, n));
#எனில் !CONFIG_SMALL
            tbl[1][i] = ROT(tbl[0][i], 8);
            tbl[2][i] = ROT(tbl[0][i], 16);
            tbl[3][i] = ROT(tbl[0][i], 24);
#endif
        }
    }
}

நிலையான AVOnce aes_static_init = AV_ONCE_INIT;

நிலையான av_cold வெறுமை aes_init_static(வெறுமை)
{
    uint8_t log8[256];
    uint8_t alog8[512];
    முழு i, j = 1;

    க்கு (i = 0; i < 255; i++) {
        alog8[i] = alog8[i + 255] = j;
        log8[j] = i;
        j ^= j + j;
        எனில் (j > 255)
            j ^= 0x11B;
    }
    க்கு (i = 0; i < 256; i++) {
        j = i ? alog8[255 - log8[i]] : 0;
        j ^= (j << 1) ^ (j << 2) ^ (j << 3) ^ (j << 4);
        j = (j ^ (j >> 8) ^ 99) & 255;
        inv_sbox[j] = i;
        sbox[i]     = j;
    }
    init_multbl2(dec_multbl, (மாறிலி முழு[4]) { 0xe, 0x9, 0xd, 0xb },
                 log8, alog8, inv_sbox);
    init_multbl2(enc_multbl, (மாறிலி முழு[4]) { 0x2, 0x1, 0x1, 0x3 },
                 log8, alog8, sbox);
}

// this is based on the reference AES code by Paulo Barreto and Vincent Rijmen
முழு av_aes_init(AVAES *a, மாறிலி uint8_t *சாவி, முழு சாவி_bits, முழு decrypt)
{
    முழு i, j, t, rconpointer = 0;
    uint8_t tk[8][4];
    முழு KC = சாவி_bits >> 5;
    முழு rounds = KC + 6;

    a->rounds = rounds;
    a->crypt = decrypt ? aes_decrypt : aes_encrypt;
#எனில் ARCH_X86 && HAVE_X86ASM && HAVE_AESNI_EXTERNAL
    ff_init_aes_x86(a, decrypt);
#அல்லதெனில் ARCH_AARCH64 && HAVE_ARM_AES
    ff_init_aes_aarch64(a, decrypt);
#endif

    ff_thread_once(&aes_static_init, aes_init_static);

    எனில் (சாவி_bits != 128 && சாவி_bits != 192 && சாவி_bits != 256)
        திரும்பு AVERROR(EINVAL);

    memcpy(tk, சாவி, KC * 4);
    memcpy(a->round_சாவி[0].u8, சாவி, KC * 4);

    க்கு (t = KC * 4; t < (rounds + 1) * 16; t += KC * 4) {
        க்கு (i = 0; i < 4; i++)
            tk[0][i] ^= sbox[tk[KC - 1][(i + 1) & 3]];
        tk[0][0] ^= rcon[rconpointer++];

        க்கு (j = 1; j < KC; j++) {
            எனில் (KC != 8 || j != KC >> 1)
                க்கு (i = 0; i < 4; i++)
                    tk[j][i] ^= tk[j - 1][i];
            இல்லையெனில்
                க்கு (i = 0; i < 4; i++)
                    tk[j][i] ^= sbox[tk[j - 1][i]];
        }

        memcpy((unsigned எழுத்து*)a->round_சாவி + t, tk, KC * 4);
    }

    எனில் (decrypt) {
        க்கு (i = 1; i < rounds; i++) {
            av_aes_block tmp[3];
            tmp[2] = a->round_சாவி[i];
            subshift(&tmp[1], 0, sbox);
            mix(tmp, dec_multbl, 1, 3);
            a->round_சாவி[i] = tmp[0];
        }
    } இல்லையெனில் {
        க்கு (i = 0; i < (rounds + 1) >> 1; i++)
            FFSWAP(av_aes_block, a->round_சாவி[i], a->round_சாவி[rounds - i]);
    }

    திரும்பு 0;
}
