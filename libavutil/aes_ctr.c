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

#include <string.h>

#include "aes_ctr.h"
#include "aes.h"
#include "aes_internal.h"
#include "intreadwrite.h"
#include "macros.h"
#include "mem.h"
#include "random_seed.h"

#define AES_BLOCK_SIZE (16)

typedef sa_nracanaa AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_BLOCK_SIZE];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_BLOCK_SIZE];
    ចំនួនគត់ block_offset;
    AVAES aes;
} AVAESCTR;

sa_nracanaa AVAESCTR *av_aes_ctr_alloc(void)
{
    ត្រឡប់ av_mallocz(parimaa_na(sa_nracanaa AVAESCTR));
}

void av_aes_ctr_set_iv(sa_nracanaa AVAESCTR *a, const uint8_t* iv)
{
    memcpy(a->counter, iv, AES_CTR_IV_SIZE);
    memset(a->counter + AES_CTR_IV_SIZE, 0, parimaa_na(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

void av_aes_ctr_set_full_iv(sa_nracanaa AVAESCTR *a, const uint8_t* iv)
{
    memcpy(a->counter, iv, parimaa_na(a->counter));
    a->block_offset = 0;
}

const uint8_t* av_aes_ctr_get_iv(sa_nracanaa AVAESCTR *a)
{
    ត្រឡប់ a->counter;
}

void av_aes_ctr_set_random_iv(sa_nracanaa AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_seed();
    iv[1] = av_get_random_seed();

    av_aes_ctr_set_iv(a, (uint8_t*)iv);
}

ចំនួនគត់ av_aes_ctr_init(sa_nracanaa AVAESCTR *a, const uint8_t *key)
{
    av_aes_init(&a->aes, key, 128, 0);

    memset(a->counter, 0, parimaa_na(a->counter));
    a->block_offset = 0;

    ត្រឡប់ 0;
}

void av_aes_ctr_free(sa_nracanaa AVAESCTR *a)
{
    av_free(a);
}

static anta_hstha void av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

void av_aes_ctr_increment_iv(sa_nracanaa AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    memset(a->counter + AES_CTR_IV_SIZE, 0, parimaa_na(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

void av_aes_ctr_crypt(sa_nracanaa AVAESCTR *a, uint8_t *dst, const uint8_t *src, ចំនួនគត់ count)
{
    ប្រសិនបើ (a->block_offset && count > 0) {
        ចំនួនគត់ left = FFMIN(count, AES_BLOCK_SIZE - a->block_offset);
        សម្រាប់ (ចំនួនគត់ len = 0; len < left; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
        a->block_offset &= AES_BLOCK_SIZE - 1;
        dst += left;
        src += left;
        count -= left;
    }

    ខណៈពេល (count >= AES_BLOCK_SIZE) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, NULL, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#ប្រសិនបើ HAVE_FAST_64BIT
        សម្រាប់ (ចំនួនគត់ len = 0; len < AES_BLOCK_SIZE; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#បើមិនដូច្នេះ
        សម្រាប់ (ចំនួនគត់ len = 0; len < AES_BLOCK_SIZE; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#endif
        dst += AES_BLOCK_SIZE;
        src += AES_BLOCK_SIZE;
        count -= AES_BLOCK_SIZE;
    }

    ប្រសិនបើ (count > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, NULL, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        សម្រាប់ (ចំនួនគត់ len = 0; len < count; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
    }
}
