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

#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "aes_ctr.h"
#ಅನ್ತರ್ಭಾವ "aes.h"
#ಅನ್ತರ್ಭಾವ "aes_internal.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "random_seed.h"

#ವ್ಯಾಖ್ಯಾನಿಸು AES_ಖಂಡ_ಗಾತ್ರ (16)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_ಖಂಡ_ಗಾತ್ರ];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_ಖಂಡ_ಗಾತ್ರ];
    ಪೂರ್ಣಾಂಕ ಖಂಡ_ಸ್ಥಾನಾಂತರ;
    AVAES aes;
} AVAESCTR;

ರಚನೆ AVAESCTR *av_aes_ctr_alloc(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ av_mallocz(ಗಾತ್ರ(ರಚನೆ AVAESCTR));
}

ಶೂನ್ಯ av_aes_ctr_ಗಣ_iv(ರಚನೆ AVAESCTR *a, ಸ್ಥಿರಾಂಕ uint8_t* iv)
{
    ಸ್ಮರಣೆ_ನಕಲು(a->counter, iv, AES_CTR_IV_ಗಾತ್ರ);
    memset(a->counter + AES_CTR_IV_ಗಾತ್ರ, 0, ಗಾತ್ರ(a->counter) - AES_CTR_IV_ಗಾತ್ರ);
    a->ಖಂಡ_ಸ್ಥಾನಾಂತರ = 0;
}

ಶೂನ್ಯ av_aes_ctr_ಗಣ_ತುಂಬಿದ_iv(ರಚನೆ AVAESCTR *a, ಸ್ಥಿರಾಂಕ uint8_t* iv)
{
    ಸ್ಮರಣೆ_ನಕಲು(a->counter, iv, ಗಾತ್ರ(a->counter));
    a->ಖಂಡ_ಸ್ಥಾನಾಂತರ = 0;
}

ಸ್ಥಿರಾಂಕ uint8_t* av_aes_ctr_get_iv(ರಚನೆ AVAESCTR *a)
{
    ಹಿಂತಿರುಗಿ a->counter;
}

ಶೂನ್ಯ av_aes_ctr_ಗಣ_random_iv(ರಚನೆ AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_ಬೀಜ();
    iv[1] = av_get_random_ಬೀಜ();

    av_aes_ctr_ಗಣ_iv(a, (uint8_t*)iv);
}

ಪೂರ್ಣಾಂಕ av_aes_ctr_init(ರಚನೆ AVAESCTR *a, ಸ್ಥಿರಾಂಕ uint8_t *ಕೀಲಿ)
{
    av_aes_init(&a->aes, ಕೀಲಿ, 128, 0);

    memset(a->counter, 0, ಗಾತ್ರ(a->counter));
    a->ಖಂಡ_ಸ್ಥಾನಾಂತರ = 0;

    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ av_aes_ctr_free(ರಚನೆ AVAESCTR *a)
{
    av_free(a);
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

ಶೂನ್ಯ av_aes_ctr_increment_iv(ರಚನೆ AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    memset(a->counter + AES_CTR_IV_ಗಾತ್ರ, 0, ಗಾತ್ರ(a->counter) - AES_CTR_IV_ಗಾತ್ರ);
    a->ಖಂಡ_ಸ್ಥಾನಾಂತರ = 0;
}

ಶೂನ್ಯ av_aes_ctr_crypt(ರಚನೆ AVAESCTR *a, uint8_t *dst, ಸ್ಥಿರಾಂಕ uint8_t *src, ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2)
{
    ಆದರೆ (a->ಖಂಡ_ಸ್ಥಾನಾಂತರ && ಎಣಿಕೆ_2 > 0) {
        ಪೂರ್ಣಾಂಕ ಎಡ = FFMIN(ಎಣಿಕೆ_2, AES_ಖಂಡ_ಗಾತ್ರ - a->ಖಂಡ_ಸ್ಥಾನಾಂತರ);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ len = 0; len < ಎಡ; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->ಖಂಡ_ಸ್ಥಾನಾಂತರ++];
        a->ಖಂಡ_ಸ್ಥಾನಾಂತರ &= AES_ಖಂಡ_ಗಾತ್ರ - 1;
        dst += ಎಡ;
        src += ಎಡ;
        ಎಣಿಕೆ_2 -= ಎಡ;
    }

    ಆಗ (ಎಣಿಕೆ_2 >= AES_ಖಂಡ_ಗಾತ್ರ) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ಖಾಲಿ, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#ಆದರೆ HAVE_FAST_64_ಬಿಟ್
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ len = 0; len < AES_ಖಂಡ_ಗಾತ್ರ; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#ಇಲ್ಲದಿದ್ದರೆ
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ len = 0; len < AES_ಖಂಡ_ಗಾತ್ರ; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#ಆದರೆ_ಅಂತ್ಯ
        dst += AES_ಖಂಡ_ಗಾತ್ರ;
        src += AES_ಖಂಡ_ಗಾತ್ರ;
        ಎಣಿಕೆ_2 -= AES_ಖಂಡ_ಗಾತ್ರ;
    }

    ಆದರೆ (ಎಣಿಕೆ_2 > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ಖಾಲಿ, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ len = 0; len < ಎಣಿಕೆ_2; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->ಖಂಡ_ಸ್ಥಾನಾಂತರ++];
    }
}
