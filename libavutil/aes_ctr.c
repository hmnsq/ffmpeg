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

#परिभाषय AES_खण्डम्_आकार (16)

प्रकारनिर्देश संरचना AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, गणक)[AES_खण्डम्_आकार];
    DECLARE_ALIGNED(8, uint8_t, encrypted_गणक)[AES_खण्डम्_आकार];
    पूर्णाङ्क खण्डम्_विस्थापनम्;
    AVAES aes;
} AVAESCTR;

संरचना AVAESCTR *av_aes_ctr_alloc(शून्य)
{
    प्रत्यागम av_mallocz(परिमाण(संरचना AVAESCTR));
}

शून्य av_aes_ctr_समुच्चयः_iv(संरचना AVAESCTR *a, ध्रुव uint8_t* iv)
{
    स्मृतिं_प्रतिलिख(a->गणक, iv, AES_CTR_IV_आकार);
    स्मृतिं_पूरय(a->गणक + AES_CTR_IV_आकार, 0, परिमाण(a->गणक) - AES_CTR_IV_आकार);
    a->खण्डम्_विस्थापनम् = 0;
}

शून्य av_aes_ctr_समुच्चयः_पूर्णम्_iv(संरचना AVAESCTR *a, ध्रुव uint8_t* iv)
{
    स्मृतिं_प्रतिलिख(a->गणक, iv, परिमाण(a->गणक));
    a->खण्डम्_विस्थापनम् = 0;
}

ध्रुव uint8_t* av_aes_ctr_get_iv(संरचना AVAESCTR *a)
{
    प्रत्यागम a->गणक;
}

शून्य av_aes_ctr_समुच्चयः_random_iv(संरचना AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_बीजम्();
    iv[1] = av_get_random_बीजम्();

    av_aes_ctr_समुच्चयः_iv(a, (uint8_t*)iv);
}

पूर्णाङ्क av_aes_ctr_init(संरचना AVAESCTR *a, ध्रुव uint8_t *कुञ्चिका)
{
    av_aes_init(&a->aes, कुञ्चिका, 128, 0);

    स्मृतिं_पूरय(a->गणक, 0, परिमाण(a->गणक));
    a->खण्डम्_विस्थापनम् = 0;

    प्रत्यागम 0;
}

शून्य av_aes_ctr_free(संरचना AVAESCTR *a)
{
    av_free(a);
}

स्थिर अन्तःस्थ शून्य av_aes_ctr_increment_be64(uint8_t* गणक)
{
    uint64_t c = AV_RB64A(गणक) + 1;
    AV_WB64A(गणक, c);
}

शून्य av_aes_ctr_increment_iv(संरचना AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->गणक);
    स्मृतिं_पूरय(a->गणक + AES_CTR_IV_आकार, 0, परिमाण(a->गणक) - AES_CTR_IV_आकार);
    a->खण्डम्_विस्थापनम् = 0;
}

शून्य av_aes_ctr_crypt(संरचना AVAESCTR *a, uint8_t *dst, ध्रुव uint8_t *src, पूर्णाङ्क गणनम्)
{
    यदि (a->खण्डम्_विस्थापनम् && गणनम् > 0) {
        पूर्णाङ्क वामः = FFMIN(गणनम्, AES_खण्डम्_आकार - a->खण्डम्_विस्थापनम्);
        प्रति (पूर्णाङ्क len = 0; len < वामः; len++)
            dst[len] = src[len] ^ a->encrypted_गणक[a->खण्डम्_विस्थापनम्++];
        a->खण्डम्_विस्थापनम् &= AES_खण्डम्_आकार - 1;
        dst += वामः;
        src += वामः;
        गणनम् -= वामः;
    }

    यावत् (गणनम् >= AES_खण्डम्_आकार) {
        av_aes_crypt(&a->aes, a->encrypted_गणक, a->गणक, 1, रिक्त, 0);
        av_aes_ctr_increment_be64(a->गणक + 8);
#यदि HAVE_FAST_64BIT
        प्रति (पूर्णाङ्क len = 0; len < AES_खण्डम्_आकार; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_गणक[len]));
#अन्यथा
        प्रति (पूर्णाङ्क len = 0; len < AES_खण्डम्_आकार; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_गणक[len]));
#यदि_अन्तः
        dst += AES_खण्डम्_आकार;
        src += AES_खण्डम्_आकार;
        गणनम् -= AES_खण्डम्_आकार;
    }

    यदि (गणनम् > 0) {
        av_aes_crypt(&a->aes, a->encrypted_गणक, a->गणक, 1, रिक्त, 0);
        av_aes_ctr_increment_be64(a->गणक + 8);
        प्रति (पूर्णाङ्क len = 0; len < गणनम्; len++)
            dst[len] = src[len] ^ a->encrypted_गणक[a->खण्डम्_विस्थापनम्++];
    }
}
