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

#define AES_BLOCK_SIZE (16)

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_BLOCK_SIZE];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_BLOCK_SIZE];
    ಪೂರ್ಣಾಙ್ಕ block_offset;
    AVAES aes;
} AVAESCTR;

ಸಂರಚನಾ AVAESCTR *av_aes_ctr_alloc(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ av_mallocz(ಪರಿಮಾಣ(ಸಂರಚನಾ AVAESCTR));
}

ಶೂನ್ಯ av_aes_ctr_set_iv(ಸಂರಚನಾ AVAESCTR *a, ಧ್ರುವ uint8_t* iv)
{
    memcpy(a->counter, iv, AES_CTR_IV_SIZE);
    memset(a->counter + AES_CTR_IV_SIZE, 0, ಪರಿಮಾಣ(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

ಶೂನ್ಯ av_aes_ctr_set_full_iv(ಸಂರಚನಾ AVAESCTR *a, ಧ್ರುವ uint8_t* iv)
{
    memcpy(a->counter, iv, ಪರಿಮಾಣ(a->counter));
    a->block_offset = 0;
}

ಧ್ರುವ uint8_t* av_aes_ctr_get_iv(ಸಂರಚನಾ AVAESCTR *a)
{
    ಪ್ರತ್ಯಾಗಮ a->counter;
}

ಶೂನ್ಯ av_aes_ctr_set_random_iv(ಸಂರಚನಾ AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_seed();
    iv[1] = av_get_random_seed();

    av_aes_ctr_set_iv(a, (uint8_t*)iv);
}

ಪೂರ್ಣಾಙ್ಕ av_aes_ctr_init(ಸಂರಚನಾ AVAESCTR *a, ಧ್ರುವ uint8_t *ಕೀಲಿ)
{
    av_aes_init(&a->aes, ಕೀಲಿ, 128, 0);

    memset(a->counter, 0, ಪರಿಮಾಣ(a->counter));
    a->block_offset = 0;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ av_aes_ctr_free(ಸಂರಚನಾ AVAESCTR *a)
{
    av_free(a);
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

ಶೂನ್ಯ av_aes_ctr_increment_iv(ಸಂರಚನಾ AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    memset(a->counter + AES_CTR_IV_SIZE, 0, ಪರಿಮಾಣ(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

ಶೂನ್ಯ av_aes_ctr_crypt(ಸಂರಚನಾ AVAESCTR *a, uint8_t *dst, ಧ್ರುವ uint8_t *src, ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ)
{
    ಯದಿ (a->block_offset && ಎಣಿಕೆ > 0) {
        ಪೂರ್ಣಾಙ್ಕ ಎಡ = FFMIN(ಎಣಿಕೆ, AES_BLOCK_SIZE - a->block_offset);
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ len = 0; len < ಎಡ; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
        a->block_offset &= AES_BLOCK_SIZE - 1;
        dst += ಎಡ;
        src += ಎಡ;
        ಎಣಿಕೆ -= ಎಡ;
    }

    ಯಾವತ್ (ಎಣಿಕೆ >= AES_BLOCK_SIZE) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ರಿಕ್ತ, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#ಯದಿ HAVE_FAST_64BIT
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ len = 0; len < AES_BLOCK_SIZE; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#ಅನ್ಯಥಾ
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ len = 0; len < AES_BLOCK_SIZE; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#endif
        dst += AES_BLOCK_SIZE;
        src += AES_BLOCK_SIZE;
        ಎಣಿಕೆ -= AES_BLOCK_SIZE;
    }

    ಯದಿ (ಎಣಿಕೆ > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ರಿಕ್ತ, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ len = 0; len < ಎಣಿಕೆ; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
    }
}
