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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "aes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "aes_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"

ਅਚਲ ਪੂਰਨ av_aes_ਮਾਪ= ਆਕਾਰ(AVAES);

ਬਣਤਰ AVAES *av_aes_alloc(ਖਾਲੀ)
{
    ਵਾਪਸ av_mallocz(ਆਕਾਰ(ਬਣਤਰ AVAES));
}

ਸਥਿਰ ਅਚਲ uint8_t rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

ਸਥਿਰ uint8_t     sbox[256];
ਸਥਿਰ uint8_t inv_sbox[256];
#ਜੇ CONFIG_SMALL
ਸਥਿਰ uint32_t enc_multbl[1][256];
ਸਥਿਰ uint32_t dec_multbl[1][256];
#ਨਹੀਂਤਾਂ
ਸਥਿਰ uint32_t enc_multbl[4][256];
ਸਥਿਰ uint32_t dec_multbl[4][256];
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_BIGENDIAN
#   define ROT(x, s) (((x) >> (s)) | ((x) << (32-(s))))
#ਨਹੀਂਤਾਂ
#   define ROT(x, s) (((x) << (s)) | ((x) >> (32-(s))))
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ addkey(av_aes_ਖੰਡ *dst, ਅਚਲ av_aes_ਖੰਡ *src,
                          ਅਚਲ av_aes_ਖੰਡ *ਗੇੜਾ_ਕੁੰਜੀ)
{
    dst->u64[0] = src->u64[0] ^ ਗੇੜਾ_ਕੁੰਜੀ->u64[0];
    dst->u64[1] = src->u64[1] ^ ਗੇੜਾ_ਕੁੰਜੀ->u64[1];
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ addkey_s(av_aes_ਖੰਡ *dst, ਅਚਲ uint8_t *src,
                            ਅਚਲ av_aes_ਖੰਡ *ਗੇੜਾ_ਕੁੰਜੀ)
{
    dst->u64[0] = AV_RN64(src)     ^ ਗੇੜਾ_ਕੁੰਜੀ->u64[0];
    dst->u64[1] = AV_RN64(src + 8) ^ ਗੇੜਾ_ਕੁੰਜੀ->u64[1];
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ addkey_d(uint8_t *dst, ਅਚਲ av_aes_ਖੰਡ *src,
                            ਅਚਲ av_aes_ਖੰਡ *ਗੇੜਾ_ਕੁੰਜੀ)
{
    AV_WN64(dst,     src->u64[0] ^ ਗੇੜਾ_ਕੁੰਜੀ->u64[0]);
    AV_WN64(dst + 8, src->u64[1] ^ ਗੇੜਾ_ਕੁੰਜੀ->u64[1]);
}

ਸਥਿਰ ਖਾਲੀ subshift(av_aes_ਖੰਡ s0[2], ਪੂਰਨ s, ਅਚਲ uint8_t *box)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *s1_dst = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ*)s0[0].u8 + 3 - s;
    ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *s1_src = s1_dst + ਆਕਾਰ(*s0);
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *s3_dst = (ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ*)s0[0].u8 + s + 1;
    ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *s3_src = s3_dst + ਆਕਾਰ(*s0);

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

ਸਥਿਰ ਸਤਰਅੰਦਰ ਪੂਰਨ mix_core(uint32_t multbl[][256], ਪੂਰਨ a, ਪੂਰਨ b, ਪੂਰਨ c, ਪੂਰਨ d)
{
#ਜੇ CONFIG_SMALL
    ਵਾਪਸ multbl[0][a] ^ ROT(multbl[0][b], 8) ^ ROT(multbl[0][c], 16) ^ ROT(multbl[0][d], 24);
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ multbl[0][a] ^ multbl[1][b] ^ multbl[2][c] ^ multbl[3][d];
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ mix(av_aes_ਖੰਡ state[2], uint32_t multbl[][256], ਪੂਰਨ s1, ਪੂਰਨ s3)
{
    uint8_t (*src)[4] = state[1].u8x4;
    state[0].u32[0] = mix_core(multbl, src[0][0], src[s1    ][1], src[2][2], src[s3    ][3]);
    state[0].u32[1] = mix_core(multbl, src[1][0], src[s3 - 1][1], src[3][2], src[s1 - 1][3]);
    state[0].u32[2] = mix_core(multbl, src[2][0], src[s3    ][1], src[0][2], src[s1    ][3]);
    state[0].u32[3] = mix_core(multbl, src[3][0], src[s1 - 1][1], src[1][2], src[s3 - 1][3]);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ aes_crypt(AVAES *a, ਪੂਰਨ s, ਅਚਲ uint8_t *sbox_arg,
                         uint32_t multbl[][256])
{
    ਪੂਰਨ r;

    ਲਈ (r = a->ਗੇੜ - 1; r > 0; r--) {
        mix(a->state, multbl, 3 - s, 1 + s);
        addkey(&a->state[1], &a->state[0], &a->ਗੇੜਾ_ਕੁੰਜੀ[r]);
    }

    subshift(&a->state[0], s, sbox_arg);
}

ਸਥਿਰ ਖਾਲੀ aes_encrypt(AVAES *a, uint8_t *dst, ਅਚਲ uint8_t *src,
                        ਪੂਰਨ ਗਿਣਤੀ_2, uint8_t *iv, ਪੂਰਨ ਗੇੜ)
{
    ਜਦੋਂ (ਗਿਣਤੀ_2--) {
        addkey_s(&a->state[1], src, &a->ਗੇੜਾ_ਕੁੰਜੀ[ਗੇੜ]);
        ਜੇ (iv)
            addkey_s(&a->state[1], iv, &a->state[1]);
        aes_crypt(a, 2, sbox, enc_multbl);
        addkey_d(dst, &a->state[0], &a->ਗੇੜਾ_ਕੁੰਜੀ[0]);
        ਜੇ (iv)
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(iv, dst, 16);
        src += 16;
        dst += 16;
    }
}

ਸਥਿਰ ਖਾਲੀ aes_decrypt(AVAES *a, uint8_t *dst, ਅਚਲ uint8_t *src,
                        ਪੂਰਨ ਗਿਣਤੀ_2, uint8_t *iv, ਪੂਰਨ ਗੇੜ)
{
    ਜਦੋਂ (ਗਿਣਤੀ_2--) {
        addkey_s(&a->state[1], src, &a->ਗੇੜਾ_ਕੁੰਜੀ[ਗੇੜ]);
        aes_crypt(a, 0, inv_sbox, dec_multbl);
        ਜੇ (iv) {
            addkey_s(&a->state[0], iv, &a->state[0]);
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(iv, src, 16);
        }
        addkey_d(dst, &a->state[0], &a->ਗੇੜਾ_ਕੁੰਜੀ[0]);
        src += 16;
        dst += 16;
    }
}

ਖਾਲੀ av_aes_crypt(AVAES *a, uint8_t *dst, ਅਚਲ uint8_t *src,
                  ਪੂਰਨ ਗਿਣਤੀ_2, uint8_t *iv, ਪੂਰਨ decrypt)
{
    a->crypt(a, dst, src, ਗਿਣਤੀ_2, iv, a->ਗੇੜ);
}

ਸਥਿਰ ਖਾਲੀ init_multbl2(uint32_t tbl[][256], ਅਚਲ ਪੂਰਨ c[4],
                         ਅਚਲ uint8_t *log8, ਅਚਲ uint8_t *alog8,
                         ਅਚਲ uint8_t *sbox_arg)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < 256; i++) {
        ਪੂਰਨ x = sbox_arg[i];
        ਜੇ (x) {
            ਪੂਰਨ k, l, m, n;
            x = log8[x];
            k = alog8[x + log8[c[0]]];
            l = alog8[x + log8[c[1]]];
            m = alog8[x + log8[c[2]]];
            n = alog8[x + log8[c[3]]];
            tbl[0][i] = AV_NE(MKBETAG(k, l, m, n), MKTAG(k, l, m, n));
#ਜੇ !CONFIG_SMALL
            tbl[1][i] = ROT(tbl[0][i], 8);
            tbl[2][i] = ROT(tbl[0][i], 16);
            tbl[3][i] = ROT(tbl[0][i], 24);
#ਜੇ_ਅੰਤ
        }
    }
}

ਸਥਿਰ AVOnce aes_static_init = AV_ONCE_INIT;

ਸਥਿਰ av_cold ਖਾਲੀ aes_init_static(ਖਾਲੀ)
{
    uint8_t log8[256];
    uint8_t alog8[512];
    ਪੂਰਨ i, j = 1;

    ਲਈ (i = 0; i < 255; i++) {
        alog8[i] = alog8[i + 255] = j;
        log8[j] = i;
        j ^= j + j;
        ਜੇ (j > 255)
            j ^= 0x11B;
    }
    ਲਈ (i = 0; i < 256; i++) {
        j = i ? alog8[255 - log8[i]] : 0;
        j ^= (j << 1) ^ (j << 2) ^ (j << 3) ^ (j << 4);
        j = (j ^ (j >> 8) ^ 99) & 255;
        inv_sbox[j] = i;
        sbox[i]     = j;
    }
    init_multbl2(dec_multbl, (ਅਚਲ ਪੂਰਨ[4]) { 0xe, 0x9, 0xd, 0xb },
                 log8, alog8, inv_sbox);
    init_multbl2(enc_multbl, (ਅਚਲ ਪੂਰਨ[4]) { 0x2, 0x1, 0x1, 0x3 },
                 log8, alog8, sbox);
}

// this is based on the reference AES code by Paulo Barreto and Vincent Rijmen
ਪੂਰਨ av_aes_init(AVAES *a, ਅਚਲ uint8_t *ਕੁੰਜੀ, ਪੂਰਨ ਕੁੰਜੀ_ਬਿੱਟ, ਪੂਰਨ decrypt)
{
    ਪੂਰਨ i, j, t, rconpointer = 0;
    uint8_t tk[8][4];
    ਪੂਰਨ KC = ਕੁੰਜੀ_ਬਿੱਟ >> 5;
    ਪੂਰਨ ਗੇੜ = KC + 6;

    a->ਗੇੜ = ਗੇੜ;
    a->crypt = decrypt ? aes_decrypt : aes_encrypt;
#ਜੇ ARCH_X86 && HAVE_X86ASM && HAVE_AESNI_EXTERNAL
    ff_init_aes_x86(a, decrypt);
#ਜਾਂਜੇ ARCH_AARCH64 && HAVE_ARM_AES
    ff_init_aes_aarch64(a, decrypt);
#ਜੇ_ਅੰਤ

    ff_thread_once(&aes_static_init, aes_init_static);

    ਜੇ (ਕੁੰਜੀ_ਬਿੱਟ != 128 && ਕੁੰਜੀ_ਬਿੱਟ != 192 && ਕੁੰਜੀ_ਬਿੱਟ != 256)
        ਵਾਪਸ AVERROR(EINVAL);

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(tk, ਕੁੰਜੀ, KC * 4);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(a->ਗੇੜਾ_ਕੁੰਜੀ[0].u8, ਕੁੰਜੀ, KC * 4);

    ਲਈ (t = KC * 4; t < (ਗੇੜ + 1) * 16; t += KC * 4) {
        ਲਈ (i = 0; i < 4; i++)
            tk[0][i] ^= sbox[tk[KC - 1][(i + 1) & 3]];
        tk[0][0] ^= rcon[rconpointer++];

        ਲਈ (j = 1; j < KC; j++) {
            ਜੇ (KC != 8 || j != KC >> 1)
                ਲਈ (i = 0; i < 4; i++)
                    tk[j][i] ^= tk[j - 1][i];
            ਨਹੀਂਤਾਂ
                ਲਈ (i = 0; i < 4; i++)
                    tk[j][i] ^= sbox[tk[j - 1][i]];
        }

        ਸਮ੍ਰਿਤੀ_ਨਕਲ((ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ*)a->ਗੇੜਾ_ਕੁੰਜੀ + t, tk, KC * 4);
    }

    ਜੇ (decrypt) {
        ਲਈ (i = 1; i < ਗੇੜ; i++) {
            av_aes_ਖੰਡ tmp[3];
            tmp[2] = a->ਗੇੜਾ_ਕੁੰਜੀ[i];
            subshift(&tmp[1], 0, sbox);
            mix(tmp, dec_multbl, 1, 3);
            a->ਗੇੜਾ_ਕੁੰਜੀ[i] = tmp[0];
        }
    } ਨਹੀਂਤਾਂ {
        ਲਈ (i = 0; i < (ਗੇੜ + 1) >> 1; i++)
            FFSWAP(av_aes_ਖੰਡ, a->ਗੇੜਾ_ਕੁੰਜੀ[i], a->ਗੇੜਾ_ਕੁੰਜੀ[ਗੇੜ - i]);
    }

    ਵਾਪਸ 0;
}
