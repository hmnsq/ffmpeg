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

#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "aes_ctr.h"
#ଅନ୍ତର୍ଭାଵ "aes.h"
#ଅନ୍ତର୍ଭାଵ "aes_internal.h"
#ଅନ୍ତର୍ଭାଵ "intreadwrite.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "random_seed.h"

#define AES_BLOCK_SIZE (16)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_BLOCK_SIZE];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_BLOCK_SIZE];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା block_offset;
    AVAES aes;
} AVAESCTR;

ସଂରଚନା AVAESCTR *av_aes_ctr_alloc(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ av_mallocz(ଆକାର(ସଂରଚନା AVAESCTR));
}

ଶୂନ୍ୟ av_aes_ctr_set_iv(ସଂରଚନା AVAESCTR *a, ଅଚଳ uint8_t* iv)
{
    memcpy(a->counter, iv, AES_CTR_IV_SIZE);
    memset(a->counter + AES_CTR_IV_SIZE, 0, ଆକାର(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

ଶୂନ୍ୟ av_aes_ctr_set_full_iv(ସଂରଚନା AVAESCTR *a, ଅଚଳ uint8_t* iv)
{
    memcpy(a->counter, iv, ଆକାର(a->counter));
    a->block_offset = 0;
}

ଅଚଳ uint8_t* av_aes_ctr_get_iv(ସଂରଚନା AVAESCTR *a)
{
    ଫେରନ୍ତୁ a->counter;
}

ଶୂନ୍ୟ av_aes_ctr_set_random_iv(ସଂରଚନା AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_seed();
    iv[1] = av_get_random_seed();

    av_aes_ctr_set_iv(a, (uint8_t*)iv);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_aes_ctr_init(ସଂରଚନା AVAESCTR *a, ଅଚଳ uint8_t *ଚାବି)
{
    av_aes_init(&a->aes, ଚାବି, 128, 0);

    memset(a->counter, 0, ଆକାର(a->counter));
    a->block_offset = 0;

    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ av_aes_ctr_free(ସଂରଚନା AVAESCTR *a)
{
    av_free(a);
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

ଶୂନ୍ୟ av_aes_ctr_increment_iv(ସଂରଚନା AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    memset(a->counter + AES_CTR_IV_SIZE, 0, ଆକାର(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

ଶୂନ୍ୟ av_aes_ctr_crypt(ସଂରଚନା AVAESCTR *a, uint8_t *dst, ଅଚଳ uint8_t *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2)
{
    ଯଦି (a->block_offset && ଗଣନା_2 > 0) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ବାମ = FFMIN(ଗଣନା_2, AES_BLOCK_SIZE - a->block_offset);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = 0; len < ବାମ; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
        a->block_offset &= AES_BLOCK_SIZE - 1;
        dst += ବାମ;
        src += ବାମ;
        ଗଣନା_2 -= ବାମ;
    }

    ଯେତେବେଳେ (ଗଣନା_2 >= AES_BLOCK_SIZE) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ଖାଲି, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#ଯଦି HAVE_FAST_64BIT
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = 0; len < AES_BLOCK_SIZE; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#ଅନ୍ୟଥା
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = 0; len < AES_BLOCK_SIZE; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#endif
        dst += AES_BLOCK_SIZE;
        src += AES_BLOCK_SIZE;
        ଗଣନା_2 -= AES_BLOCK_SIZE;
    }

    ଯଦି (ଗଣନା_2 > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ଖାଲି, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = 0; len < ଗଣନା_2; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
    }
}
