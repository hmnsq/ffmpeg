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

#அந்தர்பாவ <string.h>

#அந்தர்பாவ "aes_ctr.h"
#அந்தர்பாவ "aes.h"
#அந்தர்பாவ "aes_internal.h"
#அந்தர்பாவ "intreadwrite.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "random_seed.h"

#define AES_BLOCK_SIZE (16)

வகைவரை கட்டமைப்பு AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_BLOCK_SIZE];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_BLOCK_SIZE];
    முழு block_offset;
    AVAES aes;
} AVAESCTR;

கட்டமைப்பு AVAESCTR *av_aes_ctr_alloc(வெறுமை)
{
    திரும்பு av_mallocz(அளவு(கட்டமைப்பு AVAESCTR));
}

வெறுமை av_aes_ctr_set_iv(கட்டமைப்பு AVAESCTR *a, மாறிலி uint8_t* iv)
{
    memcpy(a->counter, iv, AES_CTR_IV_SIZE);
    memset(a->counter + AES_CTR_IV_SIZE, 0, அளவு(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

வெறுமை av_aes_ctr_set_full_iv(கட்டமைப்பு AVAESCTR *a, மாறிலி uint8_t* iv)
{
    memcpy(a->counter, iv, அளவு(a->counter));
    a->block_offset = 0;
}

மாறிலி uint8_t* av_aes_ctr_get_iv(கட்டமைப்பு AVAESCTR *a)
{
    திரும்பு a->counter;
}

வெறுமை av_aes_ctr_set_random_iv(கட்டமைப்பு AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_seed();
    iv[1] = av_get_random_seed();

    av_aes_ctr_set_iv(a, (uint8_t*)iv);
}

முழு av_aes_ctr_init(கட்டமைப்பு AVAESCTR *a, மாறிலி uint8_t *சாவி)
{
    av_aes_init(&a->aes, சாவி, 128, 0);

    memset(a->counter, 0, அளவு(a->counter));
    a->block_offset = 0;

    திரும்பு 0;
}

வெறுமை av_aes_ctr_free(கட்டமைப்பு AVAESCTR *a)
{
    av_free(a);
}

நிலையான உள்வரி வெறுமை av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

வெறுமை av_aes_ctr_increment_iv(கட்டமைப்பு AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    memset(a->counter + AES_CTR_IV_SIZE, 0, அளவு(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

வெறுமை av_aes_ctr_crypt(கட்டமைப்பு AVAESCTR *a, uint8_t *dst, மாறிலி uint8_t *src, முழு மொத்தம்)
{
    எனில் (a->block_offset && மொத்தம் > 0) {
        முழு இடது = FFMIN(மொத்தம், AES_BLOCK_SIZE - a->block_offset);
        க்கு (முழு len = 0; len < இடது; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
        a->block_offset &= AES_BLOCK_SIZE - 1;
        dst += இடது;
        src += இடது;
        மொத்தம் -= இடது;
    }

    போது (மொத்தம் >= AES_BLOCK_SIZE) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, வெற்று, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#எனில் HAVE_FAST_64BIT
        க்கு (முழு len = 0; len < AES_BLOCK_SIZE; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#இல்லையெனில்
        க்கு (முழு len = 0; len < AES_BLOCK_SIZE; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#endif
        dst += AES_BLOCK_SIZE;
        src += AES_BLOCK_SIZE;
        மொத்தம் -= AES_BLOCK_SIZE;
    }

    எனில் (மொத்தம் > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, வெற்று, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        க்கு (முழு len = 0; len < மொத்தம்; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
    }
}
