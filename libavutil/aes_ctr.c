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

#define AES_BLOCK_আকার (16)

প্রকারলেখ কাঠামো AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, গণক)[AES_BLOCK_আকার];
    DECLARE_ALIGNED(8, uint8_t, encrypted_গণক)[AES_BLOCK_আকার];
    পূর্ণসংখ্যা block_offset;
    AVAES aes;
} AVAESCTR;

কাঠামো AVAESCTR *av_aes_ctr_alloc(শূন্য)
{
    ফেরত av_mallocz(আকার(কাঠামো AVAESCTR));
}

শূন্য av_aes_ctr_set_iv(কাঠামো AVAESCTR *a, ধ্রুবক uint8_t* iv)
{
    memcpy(a->গণক, iv, AES_CTR_IV_আকার);
    memset(a->গণক + AES_CTR_IV_আকার, 0, আকার(a->গণক) - AES_CTR_IV_আকার);
    a->block_offset = 0;
}

শূন্য av_aes_ctr_set_full_iv(কাঠামো AVAESCTR *a, ধ্রুবক uint8_t* iv)
{
    memcpy(a->গণক, iv, আকার(a->গণক));
    a->block_offset = 0;
}

ধ্রুবক uint8_t* av_aes_ctr_get_iv(কাঠামো AVAESCTR *a)
{
    ফেরত a->গণক;
}

শূন্য av_aes_ctr_set_random_iv(কাঠামো AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_seed();
    iv[1] = av_get_random_seed();

    av_aes_ctr_set_iv(a, (uint8_t*)iv);
}

পূর্ণসংখ্যা av_aes_ctr_init(কাঠামো AVAESCTR *a, ধ্রুবক uint8_t *চাবি)
{
    av_aes_init(&a->aes, চাবি, 128, 0);

    memset(a->গণক, 0, আকার(a->গণক));
    a->block_offset = 0;

    ফেরত 0;
}

শূন্য av_aes_ctr_free(কাঠামো AVAESCTR *a)
{
    av_free(a);
}

স্থির অন্তঃরেখ শূন্য av_aes_ctr_increment_be64(uint8_t* গণক)
{
    uint64_t c = AV_RB64A(গণক) + 1;
    AV_WB64A(গণক, c);
}

শূন্য av_aes_ctr_increment_iv(কাঠামো AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->গণক);
    memset(a->গণক + AES_CTR_IV_আকার, 0, আকার(a->গণক) - AES_CTR_IV_আকার);
    a->block_offset = 0;
}

শূন্য av_aes_ctr_crypt(কাঠামো AVAESCTR *a, uint8_t *dst, ধ্রুবক uint8_t *src, পূর্ণসংখ্যা গুনতি)
{
    যদি (a->block_offset && গুনতি > 0) {
        পূর্ণসংখ্যা বাম = FFMIN(গুনতি, AES_BLOCK_আকার - a->block_offset);
        জন্য (পূর্ণসংখ্যা len = 0; len < বাম; len++)
            dst[len] = src[len] ^ a->encrypted_গণক[a->block_offset++];
        a->block_offset &= AES_BLOCK_আকার - 1;
        dst += বাম;
        src += বাম;
        গুনতি -= বাম;
    }

    যখন (গুনতি >= AES_BLOCK_আকার) {
        av_aes_crypt(&a->aes, a->encrypted_গণক, a->গণক, 1, ফাঁকা, 0);
        av_aes_ctr_increment_be64(a->গণক + 8);
#যদি HAVE_FAST_64BIT
        জন্য (পূর্ণসংখ্যা len = 0; len < AES_BLOCK_আকার; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_গণক[len]));
#অন্যথা
        জন্য (পূর্ণসংখ্যা len = 0; len < AES_BLOCK_আকার; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_গণক[len]));
#endif
        dst += AES_BLOCK_আকার;
        src += AES_BLOCK_আকার;
        গুনতি -= AES_BLOCK_আকার;
    }

    যদি (গুনতি > 0) {
        av_aes_crypt(&a->aes, a->encrypted_গণক, a->গণক, 1, ফাঁকা, 0);
        av_aes_ctr_increment_be64(a->গণক + 8);
        জন্য (পূর্ণসংখ্যা len = 0; len < গুনতি; len++)
            dst[len] = src[len] ^ a->encrypted_গণক[a->block_offset++];
    }
}
