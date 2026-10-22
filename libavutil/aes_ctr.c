/*
 * AES-CTR cipher
 * Copyright (c) 2015 Eran Kornblau <erankor at gmail dot com>
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

#ਅਨ੍ਤਰ੍ਭਾਵ "aes_ctr.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "aes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "aes_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "random_seed.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AES_ਖੰਡ_ਮਾਪ (16)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_ਖੰਡ_ਮਾਪ];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_ਖੰਡ_ਮਾਪ];
    ਪੂਰਨ ਖੰਡ_ਵਿੱਥ;
    AVAES aes;
} AVAESCTR;

ਬਣਤਰ AVAESCTR *av_aes_ctr_alloc(ਖਾਲੀ)
{
    ਵਾਪਸ av_mallocz(ਆਕਾਰ(ਬਣਤਰ AVAESCTR));
}

ਖਾਲੀ av_aes_ctr_ਸੈੱਟ_iv(ਬਣਤਰ AVAESCTR *a, ਅਚਲ uint8_t* iv)
{
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(a->counter, iv, AES_CTR_IV_ਮਾਪ);
    memset(a->counter + AES_CTR_IV_ਮਾਪ, 0, ਆਕਾਰ(a->counter) - AES_CTR_IV_ਮਾਪ);
    a->ਖੰਡ_ਵਿੱਥ = 0;
}

ਖਾਲੀ av_aes_ctr_ਸੈੱਟ_ਭਰਿਆ_iv(ਬਣਤਰ AVAESCTR *a, ਅਚਲ uint8_t* iv)
{
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(a->counter, iv, ਆਕਾਰ(a->counter));
    a->ਖੰਡ_ਵਿੱਥ = 0;
}

ਅਚਲ uint8_t* av_aes_ctr_get_iv(ਬਣਤਰ AVAESCTR *a)
{
    ਵਾਪਸ a->counter;
}

ਖਾਲੀ av_aes_ctr_ਸੈੱਟ_random_iv(ਬਣਤਰ AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_ਬੀਜ();
    iv[1] = av_get_random_ਬੀਜ();

    av_aes_ctr_ਸੈੱਟ_iv(a, (uint8_t*)iv);
}

ਪੂਰਨ av_aes_ctr_init(ਬਣਤਰ AVAESCTR *a, ਅਚਲ uint8_t *ਕੁੰਜੀ)
{
    av_aes_init(&a->aes, ਕੁੰਜੀ, 128, 0);

    memset(a->counter, 0, ਆਕਾਰ(a->counter));
    a->ਖੰਡ_ਵਿੱਥ = 0;

    ਵਾਪਸ 0;
}

ਖਾਲੀ av_aes_ctr_free(ਬਣਤਰ AVAESCTR *a)
{
    av_free(a);
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

ਖਾਲੀ av_aes_ctr_increment_iv(ਬਣਤਰ AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    memset(a->counter + AES_CTR_IV_ਮਾਪ, 0, ਆਕਾਰ(a->counter) - AES_CTR_IV_ਮਾਪ);
    a->ਖੰਡ_ਵਿੱਥ = 0;
}

ਖਾਲੀ av_aes_ctr_crypt(ਬਣਤਰ AVAESCTR *a, uint8_t *dst, ਅਚਲ uint8_t *src, ਪੂਰਨ ਗਿਣਤੀ_2)
{
    ਜੇ (a->ਖੰਡ_ਵਿੱਥ && ਗਿਣਤੀ_2 > 0) {
        ਪੂਰਨ ਖੱਬਾ = FFMIN(ਗਿਣਤੀ_2, AES_ਖੰਡ_ਮਾਪ - a->ਖੰਡ_ਵਿੱਥ);
        ਲਈ (ਪੂਰਨ len = 0; len < ਖੱਬਾ; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->ਖੰਡ_ਵਿੱਥ++];
        a->ਖੰਡ_ਵਿੱਥ &= AES_ਖੰਡ_ਮਾਪ - 1;
        dst += ਖੱਬਾ;
        src += ਖੱਬਾ;
        ਗਿਣਤੀ_2 -= ਖੱਬਾ;
    }

    ਜਦੋਂ (ਗਿਣਤੀ_2 >= AES_ਖੰਡ_ਮਾਪ) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ਨਿਰਾ, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#ਜੇ HAVE_FAST_64_ਦੋਆਧਾਰੀ_ਅੰਕ
        ਲਈ (ਪੂਰਨ len = 0; len < AES_ਖੰਡ_ਮਾਪ; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#ਨਹੀਂਤਾਂ
        ਲਈ (ਪੂਰਨ len = 0; len < AES_ਖੰਡ_ਮਾਪ; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#ਜੇ_ਅੰਤ
        dst += AES_ਖੰਡ_ਮਾਪ;
        src += AES_ਖੰਡ_ਮਾਪ;
        ਗਿਣਤੀ_2 -= AES_ਖੰਡ_ਮਾਪ;
    }

    ਜੇ (ਗਿਣਤੀ_2 > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ਨਿਰਾ, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        ਲਈ (ਪੂਰਨ len = 0; len < ਗਿਣਤੀ_2; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->ਖੰਡ_ਵਿੱਥ++];
    }
}
