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

#అన్తర్భావ <string.h>

#అన్తర్భావ "aes_ctr.h"
#అన్తర్భావ "aes.h"
#అన్తర్భావ "aes_internal.h"
#అన్తర్భావ "intreadwrite.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "random_seed.h"

#నిర్వచించు AES_ఖండం_కొలత (16)

రకనిర్వచనం నిర్మాణం AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_ఖండం_కొలత];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_ఖండం_కొలత];
    పూర్ణాంకం ఖండం_స్థానభ్రంశం;
    AVAES aes;
} AVAESCTR;

నిర్మాణం AVAESCTR *av_aes_ctr_alloc(శూన్య)
{
    తిరిగి av_mallocz(పరిమాణం(నిర్మాణం AVAESCTR));
}

శూన్య av_aes_ctr_సమితి_iv(నిర్మాణం AVAESCTR *a, స్థిరరాశి uint8_t* iv)
{
    జ్ఞాపకం_నకలు(a->counter, iv, AES_CTR_IV_కొలత);
    memset(a->counter + AES_CTR_IV_కొలత, 0, పరిమాణం(a->counter) - AES_CTR_IV_కొలత);
    a->ఖండం_స్థానభ్రంశం = 0;
}

శూన్య av_aes_ctr_సమితి_నిండిన_iv(నిర్మాణం AVAESCTR *a, స్థిరరాశి uint8_t* iv)
{
    జ్ఞాపకం_నకలు(a->counter, iv, పరిమాణం(a->counter));
    a->ఖండం_స్థానభ్రంశం = 0;
}

స్థిరరాశి uint8_t* av_aes_ctr_get_iv(నిర్మాణం AVAESCTR *a)
{
    తిరిగి a->counter;
}

శూన్య av_aes_ctr_సమితి_random_iv(నిర్మాణం AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_విత్తనం();
    iv[1] = av_get_random_విత్తనం();

    av_aes_ctr_సమితి_iv(a, (uint8_t*)iv);
}

పూర్ణాంకం av_aes_ctr_init(నిర్మాణం AVAESCTR *a, స్థిరరాశి uint8_t *కీలకం)
{
    av_aes_init(&a->aes, కీలకం, 128, 0);

    memset(a->counter, 0, పరిమాణం(a->counter));
    a->ఖండం_స్థానభ్రంశం = 0;

    తిరిగి 0;
}

శూన్య av_aes_ctr_free(నిర్మాణం AVAESCTR *a)
{
    av_free(a);
}

స్థిర అంతఃవరుస శూన్య av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

శూన్య av_aes_ctr_increment_iv(నిర్మాణం AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    memset(a->counter + AES_CTR_IV_కొలత, 0, పరిమాణం(a->counter) - AES_CTR_IV_కొలత);
    a->ఖండం_స్థానభ్రంశం = 0;
}

శూన్య av_aes_ctr_crypt(నిర్మాణం AVAESCTR *a, uint8_t *dst, స్థిరరాశి uint8_t *src, పూర్ణాంకం లెక్క)
{
    ఒకవేళ (a->ఖండం_స్థానభ్రంశం && లెక్క > 0) {
        పూర్ణాంకం ఎడమ = FFMIN(లెక్క, AES_ఖండం_కొలత - a->ఖండం_స్థానభ్రంశం);
        కొరకు (పూర్ణాంకం len = 0; len < ఎడమ; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->ఖండం_స్థానభ్రంశం++];
        a->ఖండం_స్థానభ్రంశం &= AES_ఖండం_కొలత - 1;
        dst += ఎడమ;
        src += ఎడమ;
        లెక్క -= ఎడమ;
    }

    అయితే (లెక్క >= AES_ఖండం_కొలత) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ఖాళీ, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#ఒకవేళ HAVE_FAST_64_బిట్టు
        కొరకు (పూర్ణాంకం len = 0; len < AES_ఖండం_కొలత; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#లేకపోతే
        కొరకు (పూర్ణాంకం len = 0; len < AES_ఖండం_కొలత; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#అయితే_ముగింపు
        dst += AES_ఖండం_కొలత;
        src += AES_ఖండం_కొలత;
        లెక్క -= AES_ఖండం_కొలత;
    }

    ఒకవేళ (లెక్క > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ఖాళీ, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        కొరకు (పూర్ణాంకం len = 0; len < లెక్క; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->ఖండం_స్థానభ్రంశం++];
    }
}
