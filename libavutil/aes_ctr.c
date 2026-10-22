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

प्रकारव्याख्या संरचना AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_BLOCK_SIZE];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_BLOCK_SIZE];
    पूर्णांक block_offset;
    AVAES aes;
} AVAESCTR;

संरचना AVAESCTR *av_aes_ctr_alloc(शून्य)
{
    परत av_mallocz(आकार(संरचना AVAESCTR));
}

शून्य av_aes_ctr_set_iv(संरचना AVAESCTR *a, स्थिरांक uint8_t* iv)
{
    स_नकल(a->counter, iv, AES_CTR_IV_SIZE);
    स_रखो(a->counter + AES_CTR_IV_SIZE, 0, आकार(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

शून्य av_aes_ctr_set_full_iv(संरचना AVAESCTR *a, स्थिरांक uint8_t* iv)
{
    स_नकल(a->counter, iv, आकार(a->counter));
    a->block_offset = 0;
}

स्थिरांक uint8_t* av_aes_ctr_get_iv(संरचना AVAESCTR *a)
{
    परत a->counter;
}

शून्य av_aes_ctr_set_random_iv(संरचना AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_seed();
    iv[1] = av_get_random_seed();

    av_aes_ctr_set_iv(a, (uint8_t*)iv);
}

पूर्णांक av_aes_ctr_init(संरचना AVAESCTR *a, स्थिरांक uint8_t *किल्ली)
{
    av_aes_init(&a->aes, किल्ली, 128, 0);

    स_रखो(a->counter, 0, आकार(a->counter));
    a->block_offset = 0;

    परत 0;
}

शून्य av_aes_ctr_free(संरचना AVAESCTR *a)
{
    av_free(a);
}

स्थिर ओळीत शून्य av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

शून्य av_aes_ctr_increment_iv(संरचना AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    स_रखो(a->counter + AES_CTR_IV_SIZE, 0, आकार(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

शून्य av_aes_ctr_crypt(संरचना AVAESCTR *a, uint8_t *dst, स्थिरांक uint8_t *src, पूर्णांक मोजणी)
{
    जर (a->block_offset && मोजणी > 0) {
        पूर्णांक डावा = FFMIN(मोजणी, AES_BLOCK_SIZE - a->block_offset);
        साठी (पूर्णांक len = 0; len < डावा; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
        a->block_offset &= AES_BLOCK_SIZE - 1;
        dst += डावा;
        src += डावा;
        मोजणी -= डावा;
    }

    पर्यंत (मोजणी >= AES_BLOCK_SIZE) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, रिक्त, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#जर HAVE_FAST_64BIT
        साठी (पूर्णांक len = 0; len < AES_BLOCK_SIZE; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#अन्यथा
        साठी (पूर्णांक len = 0; len < AES_BLOCK_SIZE; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#endif
        dst += AES_BLOCK_SIZE;
        src += AES_BLOCK_SIZE;
        मोजणी -= AES_BLOCK_SIZE;
    }

    जर (मोजणी > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, रिक्त, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        साठी (पूर्णांक len = 0; len < मोजणी; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
    }
}
