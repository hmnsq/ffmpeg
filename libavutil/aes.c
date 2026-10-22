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

#ضمن <string.h>

#ضمن "config.h"
#ضمن "aes.h"
#ضمن "aes_internal.h"
#ضمن "attributes.h"
#ضمن "error.h"
#ضمن "intreadwrite.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "thread.h"

ثابت صحيح av_aes_ناپ= حجم(AVAES);

بنية AVAES *av_aes_alloc(فراغ)
{
    أرجع av_mallocz(حجم(بنية AVAES));
}

ساكن ثابت uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

ساكن uint8_t     sbox[256];
ساكن uint8_t inv_sbox[256];
#إذا CONFIG_SMALL
ساكن uint32_t enc_multbl[1][256];
ساكن uint32_t dec_multbl[1][256];
#وإلا
ساكن uint32_t enc_multbl[4][256];
ساكن uint32_t dec_multbl[4][256];
#جے_انت

#إذا HAVE_BIGENDIAN
#   define ROT(x, s) (((x) >> (s)) | ((x) << (32-(s))))
#وإلا
#   define ROT(x, s) (((x) << (s)) | ((x) >> (32-(s))))
#جے_انت

ساكن مضمن فراغ addkey(av_aes_بلاک *dst, ثابت av_aes_بلاک *src,
                          ثابت av_aes_بلاک *گیڑا_کلید)
{
    dst->u64[0] = src->u64[0] ^ گیڑا_کلید->u64[0];
    dst->u64[1] = src->u64[1] ^ گیڑا_کلید->u64[1];
}

ساكن مضمن فراغ addkey_s(av_aes_بلاک *dst, ثابت uint8_t *src,
                            ثابت av_aes_بلاک *گیڑا_کلید)
{
    dst->u64[0] = AV_RN64(src)     ^ گیڑا_کلید->u64[0];
    dst->u64[1] = AV_RN64(src + 8) ^ گیڑا_کلید->u64[1];
}

ساكن مضمن فراغ addkey_d(uint8_t *dst, ثابت av_aes_بلاک *src,
                            ثابت av_aes_بلاک *گیڑا_کلید)
{
    AV_WN64(dst,     src->u64[0] ^ گیڑا_کلید->u64[0]);
    AV_WN64(dst + 8, src->u64[1] ^ گیڑا_کلید->u64[1]);
}

ساكن فراغ subshift(av_aes_بلاک s0[2], صحيح s, ثابت uint8_t *box)
{
    بنانشانی حرف *s1_dst = (بنانشانی حرف*)s0[0].u8 + 3 - s;
    ثابت بنانشانی حرف *s1_src = s1_dst + حجم(*s0);
    بنانشانی حرف *s3_dst = (بنانشانی حرف*)s0[0].u8 + s + 1;
    ثابت بنانشانی حرف *s3_src = s3_dst + حجم(*s0);

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

ساكن مضمن صحيح mix_core(uint32_t multbl[][256], صحيح a, صحيح b, صحيح c, صحيح d)
{
#إذا CONFIG_SMALL
    أرجع multbl[0][a] ^ ROT(multbl[0][b], 8) ^ ROT(multbl[0][c], 16) ^ ROT(multbl[0][d], 24);
#وإلا
    أرجع multbl[0][a] ^ multbl[1][b] ^ multbl[2][c] ^ multbl[3][d];
#جے_انت
}

ساكن مضمن فراغ mix(av_aes_بلاک state[2], uint32_t multbl[][256], صحيح s1, صحيح s3)
{
    uint8_t (*src)[4] = state[1].u8x4;
    state[0].u32[0] = mix_core(multbl, src[0][0], src[s1    ][1], src[2][2], src[s3    ][3]);
    state[0].u32[1] = mix_core(multbl, src[1][0], src[s3 - 1][1], src[3][2], src[s1 - 1][3]);
    state[0].u32[2] = mix_core(multbl, src[2][0], src[s3    ][1], src[0][2], src[s1    ][3]);
    state[0].u32[3] = mix_core(multbl, src[3][0], src[s1 - 1][1], src[1][2], src[s3 - 1][3]);
}

ساكن مضمن فراغ aes_crypt(AVAES *a, صحيح s, ثابت uint8_t *sbox_arg,
                         uint32_t multbl[][256])
{
    صحيح r;

    لكل (r = a->گیڑ - 1; r > 0; r--) {
        mix(a->state, multbl, 3 - s, 1 + s);
        addkey(&a->state[1], &a->state[0], &a->گیڑا_کلید[r]);
    }

    subshift(&a->state[0], s, sbox_arg);
}

ساكن فراغ aes_encrypt(AVAES *a, uint8_t *dst, ثابت uint8_t *src,
                        صحيح گنتی, uint8_t *iv, صحيح گیڑ)
{
    طالما (گنتی--) {
        addkey_s(&a->state[1], src, &a->گیڑا_کلید[گیڑ]);
        إذا (iv)
            addkey_s(&a->state[1], iv, &a->state[1]);
        aes_crypt(a, 2, sbox, enc_multbl);
        addkey_d(dst, &a->state[0], &a->گیڑا_کلید[0]);
        إذا (iv)
            حافظہ_نقل(iv, dst, 16);
        src += 16;
        dst += 16;
    }
}

ساكن فراغ aes_decrypt(AVAES *a, uint8_t *dst, ثابت uint8_t *src,
                        صحيح گنتی, uint8_t *iv, صحيح گیڑ)
{
    طالما (گنتی--) {
        addkey_s(&a->state[1], src, &a->گیڑا_کلید[گیڑ]);
        aes_crypt(a, 0, inv_sbox, dec_multbl);
        إذا (iv) {
            addkey_s(&a->state[0], iv, &a->state[0]);
            حافظہ_نقل(iv, src, 16);
        }
        addkey_d(dst, &a->state[0], &a->گیڑا_کلید[0]);
        src += 16;
        dst += 16;
    }
}

فراغ av_aes_crypt(AVAES *a, uint8_t *dst, ثابت uint8_t *src,
                  صحيح گنتی, uint8_t *iv, صحيح decrypt)
{
    a->crypt(a, dst, src, گنتی, iv, a->گیڑ);
}

ساكن فراغ init_multbl2(uint32_t tbl[][256], ثابت صحيح c[4],
                         ثابت uint8_t *log8, ثابت uint8_t *alog8,
                         ثابت uint8_t *sbox_arg)
{
    صحيح i;

    لكل (i = 0; i < 256; i++) {
        صحيح x = sbox_arg[i];
        إذا (x) {
            صحيح k, l, m, n;
            x = log8[x];
            k = alog8[x + log8[c[0]]];
            l = alog8[x + log8[c[1]]];
            m = alog8[x + log8[c[2]]];
            n = alog8[x + log8[c[3]]];
            tbl[0][i] = AV_NE(MKBETAG(k, l, m, n), MKTAG(k, l, m, n));
#إذا !CONFIG_SMALL
            tbl[1][i] = ROT(tbl[0][i], 8);
            tbl[2][i] = ROT(tbl[0][i], 16);
            tbl[3][i] = ROT(tbl[0][i], 24);
#جے_انت
        }
    }
}

ساكن AVOnce aes_static_init = AV_ONCE_INIT;

ساكن av_cold فراغ aes_init_static(فراغ)
{
    uint8_t log8[256];
    uint8_t alog8[512];
    صحيح i, j = 1;

    لكل (i = 0; i < 255; i++) {
        alog8[i] = alog8[i + 255] = j;
        log8[j] = i;
        j ^= j + j;
        إذا (j > 255)
            j ^= 0x11B;
    }
    لكل (i = 0; i < 256; i++) {
        j = i ? alog8[255 - log8[i]] : 0;
        j ^= (j << 1) ^ (j << 2) ^ (j << 3) ^ (j << 4);
        j = (j ^ (j >> 8) ^ 99) & 255;
        inv_sbox[j] = i;
        sbox[i]     = j;
    }
    init_multbl2(dec_multbl, (ثابت صحيح[4]) { 0xe, 0x9, 0xd, 0xb },
                 log8, alog8, inv_sbox);
    init_multbl2(enc_multbl, (ثابت صحيح[4]) { 0x2, 0x1, 0x1, 0x3 },
                 log8, alog8, sbox);
}

// this is based on the reference AES code by Paulo Barreto and Vincent Rijmen
صحيح av_aes_init(AVAES *a, ثابت uint8_t *کلید, صحيح کلید_بٹ, صحيح decrypt)
{
    صحيح i, j, t, rconpointer = 0;
    uint8_t tk[8][4];
    صحيح KC = کلید_بٹ >> 5;
    صحيح گیڑ = KC + 6;

    a->گیڑ = گیڑ;
    a->crypt = decrypt ? aes_decrypt : aes_encrypt;
#إذا ARCH_X86 && HAVE_X86ASM && HAVE_AESNI_EXTERNAL
    ff_init_aes_x86(a, decrypt);
#وإلاإذا ARCH_AARCH64 && HAVE_ARM_AES
    ff_init_aes_aarch64(a, decrypt);
#جے_انت

    ff_thread_once(&aes_static_init, aes_init_static);

    إذا (کلید_بٹ != 128 && کلید_بٹ != 192 && کلید_بٹ != 256)
        أرجع AVERROR(EINVAL);

    حافظہ_نقل(tk, کلید, KC * 4);
    حافظہ_نقل(a->گیڑا_کلید[0].u8, کلید, KC * 4);

    لكل (t = KC * 4; t < (گیڑ + 1) * 16; t += KC * 4) {
        لكل (i = 0; i < 4; i++)
            tk[0][i] ^= sbox[tk[KC - 1][(i + 1) & 3]];
        tk[0][0] ^= rcon[rconpointer++];

        لكل (j = 1; j < KC; j++) {
            إذا (KC != 8 || j != KC >> 1)
                لكل (i = 0; i < 4; i++)
                    tk[j][i] ^= tk[j - 1][i];
            وإلا
                لكل (i = 0; i < 4; i++)
                    tk[j][i] ^= sbox[tk[j - 1][i]];
        }

        حافظہ_نقل((بنانشانی حرف*)a->گیڑا_کلید + t, tk, KC * 4);
    }

    إذا (decrypt) {
        لكل (i = 1; i < گیڑ; i++) {
            av_aes_بلاک tmp[3];
            tmp[2] = a->گیڑا_کلید[i];
            subshift(&tmp[1], 0, sbox);
            mix(tmp, dec_multbl, 1, 3);
            a->گیڑا_کلید[i] = tmp[0];
        }
    } وإلا {
        لكل (i = 0; i < (گیڑ + 1) >> 1; i++)
            FFSWAP(av_aes_بلاک, a->گیڑا_کلید[i], a->گیڑا_کلید[گیڑ - i]);
    }

    أرجع 0;
}
