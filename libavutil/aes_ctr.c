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

#অন্তর্ভাব <string.h>

#অন্তর্ভাব "aes_ctr.h"
#অন্তর্ভাব "aes.h"
#অন্তর্ভাব "aes_internal.h"
#অন্তর্ভাব "intreadwrite.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "random_seed.h"

#define AES_BLOCK_SIZE (16)

প্রকারনির্দেশ সংরচনা AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_BLOCK_SIZE];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_BLOCK_SIZE];
    পূর্ণাঙ্ক block_offset;
    AVAES aes;
} AVAESCTR;

সংরচনা AVAESCTR *av_aes_ctr_alloc(শূন্য)
{
    প্রত্যাগম av_mallocz(পরিমাণ(সংরচনা AVAESCTR));
}

শূন্য av_aes_ctr_set_iv(সংরচনা AVAESCTR *a, ধ্রুব uint8_t* iv)
{
    memcpy(a->counter, iv, AES_CTR_IV_SIZE);
    memset(a->counter + AES_CTR_IV_SIZE, 0, পরিমাণ(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

শূন্য av_aes_ctr_set_full_iv(সংরচনা AVAESCTR *a, ধ্রুব uint8_t* iv)
{
    memcpy(a->counter, iv, পরিমাণ(a->counter));
    a->block_offset = 0;
}

ধ্রুব uint8_t* av_aes_ctr_get_iv(সংরচনা AVAESCTR *a)
{
    প্রত্যাগম a->counter;
}

শূন্য av_aes_ctr_set_random_iv(সংরচনা AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_seed();
    iv[1] = av_get_random_seed();

    av_aes_ctr_set_iv(a, (uint8_t*)iv);
}

পূর্ণাঙ্ক av_aes_ctr_init(সংরচনা AVAESCTR *a, ধ্রুব uint8_t *চাবি)
{
    av_aes_init(&a->aes, চাবি, 128, 0);

    memset(a->counter, 0, পরিমাণ(a->counter));
    a->block_offset = 0;

    প্রত্যাগম 0;
}

শূন্য av_aes_ctr_free(সংরচনা AVAESCTR *a)
{
    av_free(a);
}

স্থির অন্তঃস্থ শূন্য av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

শূন্য av_aes_ctr_increment_iv(সংরচনা AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    memset(a->counter + AES_CTR_IV_SIZE, 0, পরিমাণ(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

শূন্য av_aes_ctr_crypt(সংরচনা AVAESCTR *a, uint8_t *dst, ধ্রুব uint8_t *src, পূর্ণাঙ্ক গুনতি)
{
    যদি (a->block_offset && গুনতি > 0) {
        পূর্ণাঙ্ক বাম = FFMIN(গুনতি, AES_BLOCK_SIZE - a->block_offset);
        প্রতি (পূর্ণাঙ্ক len = 0; len < বাম; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
        a->block_offset &= AES_BLOCK_SIZE - 1;
        dst += বাম;
        src += বাম;
        গুনতি -= বাম;
    }

    যাবত্ (গুনতি >= AES_BLOCK_SIZE) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, রিক্ত, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#যদি HAVE_FAST_64BIT
        প্রতি (পূর্ণাঙ্ক len = 0; len < AES_BLOCK_SIZE; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#অন্যথা
        প্রতি (পূর্ণাঙ্ক len = 0; len < AES_BLOCK_SIZE; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#endif
        dst += AES_BLOCK_SIZE;
        src += AES_BLOCK_SIZE;
        গুনতি -= AES_BLOCK_SIZE;
    }

    যদি (গুনতি > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, রিক্ত, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        প্রতি (পূর্ণাঙ্ক len = 0; len < গুনতি; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
    }
}
