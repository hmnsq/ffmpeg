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

#شامل <string.h>

#شامل "config.h"
#شامل "aes.h"
#شامل "aes_internal.h"
#شامل "attributes.h"
#شامل "error.h"
#شامل "intreadwrite.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "thread.h"

ثابت صحیح av_aes_سائز= حجم(AVAES);

ساخت AVAES *av_aes_alloc(خالی)
{
    واپس av_mallocz(حجم(ساخت AVAES));
}

ساکن ثابت uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

ساکن uint8_t     sbox[256];
ساکن uint8_t inv_sbox[256];
#اگر CONFIG_SMALL
ساکن uint32_t enc_multbl[1][256];
ساکن uint32_t dec_multbl[1][256];
#ورنہ
ساکن uint32_t enc_multbl[4][256];
ساکن uint32_t dec_multbl[4][256];
#اگر_ختم

#اگر HAVE_BIGENDIAN
#   define ROT(x, s) (((x) >> (s)) | ((x) << (32-(s))))
#ورنہ
#   define ROT(x, s) (((x) << (s)) | ((x) >> (32-(s))))
#اگر_ختم

ساکن اندرونی خالی addkey(av_aes_بلاک *dst, ثابت av_aes_بلاک *src,
                          ثابت av_aes_بلاک *باری_کلید)
{
    dst->u64[0] = src->u64[0] ^ باری_کلید->u64[0];
    dst->u64[1] = src->u64[1] ^ باری_کلید->u64[1];
}

ساکن اندرونی خالی addkey_s(av_aes_بلاک *dst, ثابت uint8_t *src,
                            ثابت av_aes_بلاک *باری_کلید)
{
    dst->u64[0] = AV_RN64(src)     ^ باری_کلید->u64[0];
    dst->u64[1] = AV_RN64(src + 8) ^ باری_کلید->u64[1];
}

ساکن اندرونی خالی addkey_d(uint8_t *dst, ثابت av_aes_بلاک *src,
                            ثابت av_aes_بلاک *باری_کلید)
{
    AV_WN64(dst,     src->u64[0] ^ باری_کلید->u64[0]);
    AV_WN64(dst + 8, src->u64[1] ^ باری_کلید->u64[1]);
}

ساکن خالی subshift(av_aes_بلاک s0[2], صحیح s, ثابت uint8_t *box)
{
    غیرعلامتی حرف *s1_dst = (غیرعلامتی حرف*)s0[0].u8 + 3 - s;
    ثابت غیرعلامتی حرف *s1_src = s1_dst + حجم(*s0);
    غیرعلامتی حرف *s3_dst = (غیرعلامتی حرف*)s0[0].u8 + s + 1;
    ثابت غیرعلامتی حرف *s3_src = s3_dst + حجم(*s0);

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

ساکن اندرونی صحیح mix_core(uint32_t multbl[][256], صحیح a, صحیح b, صحیح c, صحیح d)
{
#اگر CONFIG_SMALL
    واپس multbl[0][a] ^ ROT(multbl[0][b], 8) ^ ROT(multbl[0][c], 16) ^ ROT(multbl[0][d], 24);
#ورنہ
    واپس multbl[0][a] ^ multbl[1][b] ^ multbl[2][c] ^ multbl[3][d];
#اگر_ختم
}

ساکن اندرونی خالی mix(av_aes_بلاک state[2], uint32_t multbl[][256], صحیح s1, صحیح s3)
{
    uint8_t (*src)[4] = state[1].u8x4;
    state[0].u32[0] = mix_core(multbl, src[0][0], src[s1    ][1], src[2][2], src[s3    ][3]);
    state[0].u32[1] = mix_core(multbl, src[1][0], src[s3 - 1][1], src[3][2], src[s1 - 1][3]);
    state[0].u32[2] = mix_core(multbl, src[2][0], src[s3    ][1], src[0][2], src[s1    ][3]);
    state[0].u32[3] = mix_core(multbl, src[3][0], src[s1 - 1][1], src[1][2], src[s3 - 1][3]);
}

ساکن اندرونی خالی aes_crypt(AVAES *a, صحیح s, ثابت uint8_t *sbox_arg,
                         uint32_t multbl[][256])
{
    صحیح r;

    برائے (r = a->دور - 1; r > 0; r--) {
        mix(a->state, multbl, 3 - s, 1 + s);
        addkey(&a->state[1], &a->state[0], &a->باری_کلید[r]);
    }

    subshift(&a->state[0], s, sbox_arg);
}

ساکن خالی aes_encrypt(AVAES *a, uint8_t *dst, ثابت uint8_t *src,
                        صحیح گنتی, uint8_t *iv, صحیح دور)
{
    جب (گنتی--) {
        addkey_s(&a->state[1], src, &a->باری_کلید[دور]);
        اگر (iv)
            addkey_s(&a->state[1], iv, &a->state[1]);
        aes_crypt(a, 2, sbox, enc_multbl);
        addkey_d(dst, &a->state[0], &a->باری_کلید[0]);
        اگر (iv)
            حافظہ_نقل(iv, dst, 16);
        src += 16;
        dst += 16;
    }
}

ساکن خالی aes_decrypt(AVAES *a, uint8_t *dst, ثابت uint8_t *src,
                        صحیح گنتی, uint8_t *iv, صحیح دور)
{
    جب (گنتی--) {
        addkey_s(&a->state[1], src, &a->باری_کلید[دور]);
        aes_crypt(a, 0, inv_sbox, dec_multbl);
        اگر (iv) {
            addkey_s(&a->state[0], iv, &a->state[0]);
            حافظہ_نقل(iv, src, 16);
        }
        addkey_d(dst, &a->state[0], &a->باری_کلید[0]);
        src += 16;
        dst += 16;
    }
}

خالی av_aes_crypt(AVAES *a, uint8_t *dst, ثابت uint8_t *src,
                  صحیح گنتی, uint8_t *iv, صحیح decrypt)
{
    a->crypt(a, dst, src, گنتی, iv, a->دور);
}

ساکن خالی init_multbl2(uint32_t tbl[][256], ثابت صحیح c[4],
                         ثابت uint8_t *log8, ثابت uint8_t *alog8,
                         ثابت uint8_t *sbox_arg)
{
    صحیح i;

    برائے (i = 0; i < 256; i++) {
        صحیح x = sbox_arg[i];
        اگر (x) {
            صحیح k, l, m, n;
            x = log8[x];
            k = alog8[x + log8[c[0]]];
            l = alog8[x + log8[c[1]]];
            m = alog8[x + log8[c[2]]];
            n = alog8[x + log8[c[3]]];
            tbl[0][i] = AV_NE(MKBETAG(k, l, m, n), MKTAG(k, l, m, n));
#اگر !CONFIG_SMALL
            tbl[1][i] = ROT(tbl[0][i], 8);
            tbl[2][i] = ROT(tbl[0][i], 16);
            tbl[3][i] = ROT(tbl[0][i], 24);
#اگر_ختم
        }
    }
}

ساکن AVOnce aes_static_init = AV_ONCE_INIT;

ساکن av_cold خالی aes_init_static(خالی)
{
    uint8_t log8[256];
    uint8_t alog8[512];
    صحیح i, j = 1;

    برائے (i = 0; i < 255; i++) {
        alog8[i] = alog8[i + 255] = j;
        log8[j] = i;
        j ^= j + j;
        اگر (j > 255)
            j ^= 0x11B;
    }
    برائے (i = 0; i < 256; i++) {
        j = i ? alog8[255 - log8[i]] : 0;
        j ^= (j << 1) ^ (j << 2) ^ (j << 3) ^ (j << 4);
        j = (j ^ (j >> 8) ^ 99) & 255;
        inv_sbox[j] = i;
        sbox[i]     = j;
    }
    init_multbl2(dec_multbl, (ثابت صحیح[4]) { 0xe, 0x9, 0xd, 0xb },
                 log8, alog8, inv_sbox);
    init_multbl2(enc_multbl, (ثابت صحیح[4]) { 0x2, 0x1, 0x1, 0x3 },
                 log8, alog8, sbox);
}

// this is based on the reference AES code by Paulo Barreto and Vincent Rijmen
صحیح av_aes_init(AVAES *a, ثابت uint8_t *کلید, صحیح کلید_بٹ, صحیح decrypt)
{
    صحیح i, j, t, rconpointer = 0;
    uint8_t tk[8][4];
    صحیح KC = کلید_بٹ >> 5;
    صحیح دور = KC + 6;

    a->دور = دور;
    a->crypt = decrypt ? aes_decrypt : aes_encrypt;
#اگر ARCH_X86 && HAVE_X86ASM && HAVE_AESNI_EXTERNAL
    ff_init_aes_x86(a, decrypt);
#وگرنہ_اگر ARCH_AARCH64 && HAVE_ARM_AES
    ff_init_aes_aarch64(a, decrypt);
#اگر_ختم

    ff_thread_once(&aes_static_init, aes_init_static);

    اگر (کلید_بٹ != 128 && کلید_بٹ != 192 && کلید_بٹ != 256)
        واپس AVERROR(EINVAL);

    حافظہ_نقل(tk, کلید, KC * 4);
    حافظہ_نقل(a->باری_کلید[0].u8, کلید, KC * 4);

    برائے (t = KC * 4; t < (دور + 1) * 16; t += KC * 4) {
        برائے (i = 0; i < 4; i++)
            tk[0][i] ^= sbox[tk[KC - 1][(i + 1) & 3]];
        tk[0][0] ^= rcon[rconpointer++];

        برائے (j = 1; j < KC; j++) {
            اگر (KC != 8 || j != KC >> 1)
                برائے (i = 0; i < 4; i++)
                    tk[j][i] ^= tk[j - 1][i];
            ورنہ
                برائے (i = 0; i < 4; i++)
                    tk[j][i] ^= sbox[tk[j - 1][i]];
        }

        حافظہ_نقل((غیرعلامتی حرف*)a->باری_کلید + t, tk, KC * 4);
    }

    اگر (decrypt) {
        برائے (i = 1; i < دور; i++) {
            av_aes_بلاک tmp[3];
            tmp[2] = a->باری_کلید[i];
            subshift(&tmp[1], 0, sbox);
            mix(tmp, dec_multbl, 1, 3);
            a->باری_کلید[i] = tmp[0];
        }
    } ورنہ {
        برائے (i = 0; i < (دور + 1) >> 1; i++)
            FFSWAP(av_aes_بلاک, a->باری_کلید[i], a->باری_کلید[دور - i]);
    }

    واپس 0;
}
