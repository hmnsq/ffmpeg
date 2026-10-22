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

#अन्तर्भाव <string.h>

#अन्तर्भाव "aes_ctr.h"
#अन्तर्भाव "aes.h"
#अन्तर्भाव "aes_internal.h"
#अन्तर्भाव "intreadwrite.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "random_seed.h"

#define AES_BLOCK_SIZE (16)

प्रकारनिर्देश संरचना AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_BLOCK_SIZE];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_BLOCK_SIZE];
    पूर्णाङ्क block_offset;
    AVAES aes;
} AVAESCTR;

संरचना AVAESCTR *av_aes_ctr_alloc(शून्य)
{
    प्रत्यागम av_mallocz(परिमाण(संरचना AVAESCTR));
}

शून्य av_aes_ctr_set_iv(संरचना AVAESCTR *a, ध्रुव uint8_t* iv)
{
    memcpy(a->counter, iv, AES_CTR_IV_SIZE);
    memset(a->counter + AES_CTR_IV_SIZE, 0, परिमाण(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

शून्य av_aes_ctr_set_full_iv(संरचना AVAESCTR *a, ध्रुव uint8_t* iv)
{
    memcpy(a->counter, iv, परिमाण(a->counter));
    a->block_offset = 0;
}

ध्रुव uint8_t* av_aes_ctr_get_iv(संरचना AVAESCTR *a)
{
    प्रत्यागम a->counter;
}

शून्य av_aes_ctr_set_random_iv(संरचना AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_seed();
    iv[1] = av_get_random_seed();

    av_aes_ctr_set_iv(a, (uint8_t*)iv);
}

पूर्णाङ्क av_aes_ctr_init(संरचना AVAESCTR *a, ध्रुव uint8_t *किल्ली)
{
    av_aes_init(&a->aes, किल्ली, 128, 0);

    memset(a->counter, 0, परिमाण(a->counter));
    a->block_offset = 0;

    प्रत्यागम 0;
}

शून्य av_aes_ctr_free(संरचना AVAESCTR *a)
{
    av_free(a);
}

स्थिर अन्तःस्थ शून्य av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

शून्य av_aes_ctr_increment_iv(संरचना AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    memset(a->counter + AES_CTR_IV_SIZE, 0, परिमाण(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

शून्य av_aes_ctr_crypt(संरचना AVAESCTR *a, uint8_t *dst, ध्रुव uint8_t *src, पूर्णाङ्क मोजणी)
{
    यदि (a->block_offset && मोजणी > 0) {
        पूर्णाङ्क डावा = FFMIN(मोजणी, AES_BLOCK_SIZE - a->block_offset);
        प्रति (पूर्णाङ्क len = 0; len < डावा; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
        a->block_offset &= AES_BLOCK_SIZE - 1;
        dst += डावा;
        src += डावा;
        मोजणी -= डावा;
    }

    यावत् (मोजणी >= AES_BLOCK_SIZE) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, रिक्त, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#यदि HAVE_FAST_64BIT
        प्रति (पूर्णाङ्क len = 0; len < AES_BLOCK_SIZE; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#अन्यथा
        प्रति (पूर्णाङ्क len = 0; len < AES_BLOCK_SIZE; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#endif
        dst += AES_BLOCK_SIZE;
        src += AES_BLOCK_SIZE;
        मोजणी -= AES_BLOCK_SIZE;
    }

    यदि (मोजणी > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, रिक्त, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        प्रति (पूर्णाङ्क len = 0; len < मोजणी; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
    }
}
