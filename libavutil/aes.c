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

#अन्तर्भाव <string.h>

#अन्तर्भाव "config.h"
#अन्तर्भाव "aes.h"
#अन्तर्भाव "aes_internal.h"
#अन्तर्भाव "attributes.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "intreadwrite.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "thread.h"

स्थिरांक पूर्णांक av_aes_size= आकार(AVAES);

संरचना AVAES *av_aes_alloc(शून्य)
{
    परत av_mallocz(आकार(संरचना AVAES));
}

स्थिर स्थिरांक uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

स्थिर uint8_t     sbox[256];
स्थिर uint8_t inv_sbox[256];
#जर CONFIG_SMALL
स्थिर uint32_t enc_multbl[1][256];
स्थिर uint32_t dec_multbl[1][256];
#अन्यथा
स्थिर uint32_t enc_multbl[4][256];
स्थिर uint32_t dec_multbl[4][256];
#endif

#जर HAVE_BIGENDIAN
#   define ROT(x, s) (((x) >> (s)) | ((x) << (32-(s))))
#अन्यथा
#   define ROT(x, s) (((x) << (s)) | ((x) >> (32-(s))))
#endif

स्थिर ओळीत शून्य addkey(av_aes_block *dst, स्थिरांक av_aes_block *src,
                          स्थिरांक av_aes_block *round_किल्ली)
{
    dst->u64[0] = src->u64[0] ^ round_किल्ली->u64[0];
    dst->u64[1] = src->u64[1] ^ round_किल्ली->u64[1];
}

स्थिर ओळीत शून्य addkey_s(av_aes_block *dst, स्थिरांक uint8_t *src,
                            स्थिरांक av_aes_block *round_किल्ली)
{
    dst->u64[0] = AV_RN64(src)     ^ round_किल्ली->u64[0];
    dst->u64[1] = AV_RN64(src + 8) ^ round_किल्ली->u64[1];
}

स्थिर ओळीत शून्य addkey_d(uint8_t *dst, स्थिरांक av_aes_block *src,
                            स्थिरांक av_aes_block *round_किल्ली)
{
    AV_WN64(dst,     src->u64[0] ^ round_किल्ली->u64[0]);
    AV_WN64(dst + 8, src->u64[1] ^ round_किल्ली->u64[1]);
}

स्थिर शून्य subshift(av_aes_block s0[2], पूर्णांक s, स्थिरांक uint8_t *box)
{
    अचिन्हित अक्षर *s1_dst = (अचिन्हित अक्षर*)s0[0].u8 + 3 - s;
    स्थिरांक अचिन्हित अक्षर *s1_src = s1_dst + आकार(*s0);
    अचिन्हित अक्षर *s3_dst = (अचिन्हित अक्षर*)s0[0].u8 + s + 1;
    स्थिरांक अचिन्हित अक्षर *s3_src = s3_dst + आकार(*s0);

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

स्थिर ओळीत पूर्णांक mix_core(uint32_t multbl[][256], पूर्णांक a, पूर्णांक b, पूर्णांक c, पूर्णांक d)
{
#जर CONFIG_SMALL
    परत multbl[0][a] ^ ROT(multbl[0][b], 8) ^ ROT(multbl[0][c], 16) ^ ROT(multbl[0][d], 24);
#अन्यथा
    परत multbl[0][a] ^ multbl[1][b] ^ multbl[2][c] ^ multbl[3][d];
#endif
}

स्थिर ओळीत शून्य mix(av_aes_block state[2], uint32_t multbl[][256], पूर्णांक s1, पूर्णांक s3)
{
    uint8_t (*src)[4] = state[1].u8x4;
    state[0].u32[0] = mix_core(multbl, src[0][0], src[s1    ][1], src[2][2], src[s3    ][3]);
    state[0].u32[1] = mix_core(multbl, src[1][0], src[s3 - 1][1], src[3][2], src[s1 - 1][3]);
    state[0].u32[2] = mix_core(multbl, src[2][0], src[s3    ][1], src[0][2], src[s1    ][3]);
    state[0].u32[3] = mix_core(multbl, src[3][0], src[s1 - 1][1], src[1][2], src[s3 - 1][3]);
}

स्थिर ओळीत शून्य aes_crypt(AVAES *a, पूर्णांक s, स्थिरांक uint8_t *sbox_arg,
                         uint32_t multbl[][256])
{
    पूर्णांक r;

    साठी (r = a->rounds - 1; r > 0; r--) {
        mix(a->state, multbl, 3 - s, 1 + s);
        addkey(&a->state[1], &a->state[0], &a->round_किल्ली[r]);
    }

    subshift(&a->state[0], s, sbox_arg);
}

स्थिर शून्य aes_encrypt(AVAES *a, uint8_t *dst, स्थिरांक uint8_t *src,
                        पूर्णांक मोजणी, uint8_t *iv, पूर्णांक rounds)
{
    पर्यंत (मोजणी--) {
        addkey_s(&a->state[1], src, &a->round_किल्ली[rounds]);
        जर (iv)
            addkey_s(&a->state[1], iv, &a->state[1]);
        aes_crypt(a, 2, sbox, enc_multbl);
        addkey_d(dst, &a->state[0], &a->round_किल्ली[0]);
        जर (iv)
            स_नकल(iv, dst, 16);
        src += 16;
        dst += 16;
    }
}

स्थिर शून्य aes_decrypt(AVAES *a, uint8_t *dst, स्थिरांक uint8_t *src,
                        पूर्णांक मोजणी, uint8_t *iv, पूर्णांक rounds)
{
    पर्यंत (मोजणी--) {
        addkey_s(&a->state[1], src, &a->round_किल्ली[rounds]);
        aes_crypt(a, 0, inv_sbox, dec_multbl);
        जर (iv) {
            addkey_s(&a->state[0], iv, &a->state[0]);
            स_नकल(iv, src, 16);
        }
        addkey_d(dst, &a->state[0], &a->round_किल्ली[0]);
        src += 16;
        dst += 16;
    }
}

शून्य av_aes_crypt(AVAES *a, uint8_t *dst, स्थिरांक uint8_t *src,
                  पूर्णांक मोजणी, uint8_t *iv, पूर्णांक decrypt)
{
    a->crypt(a, dst, src, मोजणी, iv, a->rounds);
}

स्थिर शून्य init_multbl2(uint32_t tbl[][256], स्थिरांक पूर्णांक c[4],
                         स्थिरांक uint8_t *log8, स्थिरांक uint8_t *alog8,
                         स्थिरांक uint8_t *sbox_arg)
{
    पूर्णांक i;

    साठी (i = 0; i < 256; i++) {
        पूर्णांक x = sbox_arg[i];
        जर (x) {
            पूर्णांक k, l, m, n;
            x = log8[x];
            k = alog8[x + log8[c[0]]];
            l = alog8[x + log8[c[1]]];
            m = alog8[x + log8[c[2]]];
            n = alog8[x + log8[c[3]]];
            tbl[0][i] = AV_NE(MKBETAG(k, l, m, n), MKTAG(k, l, m, n));
#जर !CONFIG_SMALL
            tbl[1][i] = ROT(tbl[0][i], 8);
            tbl[2][i] = ROT(tbl[0][i], 16);
            tbl[3][i] = ROT(tbl[0][i], 24);
#endif
        }
    }
}

स्थिर AVOnce aes_static_init = AV_ONCE_INIT;

स्थिर av_cold शून्य aes_init_static(शून्य)
{
    uint8_t log8[256];
    uint8_t alog8[512];
    पूर्णांक i, j = 1;

    साठी (i = 0; i < 255; i++) {
        alog8[i] = alog8[i + 255] = j;
        log8[j] = i;
        j ^= j + j;
        जर (j > 255)
            j ^= 0x11B;
    }
    साठी (i = 0; i < 256; i++) {
        j = i ? alog8[255 - log8[i]] : 0;
        j ^= (j << 1) ^ (j << 2) ^ (j << 3) ^ (j << 4);
        j = (j ^ (j >> 8) ^ 99) & 255;
        inv_sbox[j] = i;
        sbox[i]     = j;
    }
    init_multbl2(dec_multbl, (स्थिरांक पूर्णांक[4]) { 0xe, 0x9, 0xd, 0xb },
                 log8, alog8, inv_sbox);
    init_multbl2(enc_multbl, (स्थिरांक पूर्णांक[4]) { 0x2, 0x1, 0x1, 0x3 },
                 log8, alog8, sbox);
}

// this is based on the reference AES code by Paulo Barreto and Vincent Rijmen
पूर्णांक av_aes_init(AVAES *a, स्थिरांक uint8_t *किल्ली, पूर्णांक किल्ली_bits, पूर्णांक decrypt)
{
    पूर्णांक i, j, t, rconpointer = 0;
    uint8_t tk[8][4];
    पूर्णांक KC = किल्ली_bits >> 5;
    पूर्णांक rounds = KC + 6;

    a->rounds = rounds;
    a->crypt = decrypt ? aes_decrypt : aes_encrypt;
#जर ARCH_X86 && HAVE_X86ASM && HAVE_AESNI_EXTERNAL
    ff_init_aes_x86(a, decrypt);
#किंवाजर ARCH_AARCH64 && HAVE_ARM_AES
    ff_init_aes_aarch64(a, decrypt);
#endif

    ff_thread_once(&aes_static_init, aes_init_static);

    जर (किल्ली_bits != 128 && किल्ली_bits != 192 && किल्ली_bits != 256)
        परत AVERROR(EINVAL);

    स_नकल(tk, किल्ली, KC * 4);
    स_नकल(a->round_किल्ली[0].u8, किल्ली, KC * 4);

    साठी (t = KC * 4; t < (rounds + 1) * 16; t += KC * 4) {
        साठी (i = 0; i < 4; i++)
            tk[0][i] ^= sbox[tk[KC - 1][(i + 1) & 3]];
        tk[0][0] ^= rcon[rconpointer++];

        साठी (j = 1; j < KC; j++) {
            जर (KC != 8 || j != KC >> 1)
                साठी (i = 0; i < 4; i++)
                    tk[j][i] ^= tk[j - 1][i];
            अन्यथा
                साठी (i = 0; i < 4; i++)
                    tk[j][i] ^= sbox[tk[j - 1][i]];
        }

        स_नकल((अचिन्हित अक्षर*)a->round_किल्ली + t, tk, KC * 4);
    }

    जर (decrypt) {
        साठी (i = 1; i < rounds; i++) {
            av_aes_block tmp[3];
            tmp[2] = a->round_किल्ली[i];
            subshift(&tmp[1], 0, sbox);
            mix(tmp, dec_multbl, 1, 3);
            a->round_किल्ली[i] = tmp[0];
        }
    } अन्यथा {
        साठी (i = 0; i < (rounds + 1) >> 1; i++)
            FFSWAP(av_aes_block, a->round_किल्ली[i], a->round_किल्ली[rounds - i]);
    }

    परत 0;
}
