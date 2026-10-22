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

#समावेश <string.h>

#समावेश "aes_ctr.h"
#समावेश "aes.h"
#समावेश "aes_internal.h"
#समावेश "intreadwrite.h"
#समावेश "macros.h"
#समावेश "mem.h"
#समावेश "random_seed.h"

#घोषणा AES_BLOCK_आकार (16)

प्रकार काष्ठा AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, गणक)[AES_BLOCK_आकार];
    DECLARE_ALIGNED(8, uint8_t, encrypted_गणक)[AES_BLOCK_आकार];
    पूर्णांक block_offset;
    AVAES aes;
} AVAESCTR;

काष्ठा AVAESCTR *av_aes_ctr_alloc(व्योम)
{
    वापस av_mallocz(माप(काष्ठा AVAESCTR));
}

व्योम av_aes_ctr_set_iv(काष्ठा AVAESCTR *a, स्थिर uint8_t* iv)
{
    स_नकल(a->गणक, iv, AES_CTR_IV_आकार);
    स_रखो(a->गणक + AES_CTR_IV_आकार, 0, माप(a->गणक) - AES_CTR_IV_आकार);
    a->block_offset = 0;
}

व्योम av_aes_ctr_set_full_iv(काष्ठा AVAESCTR *a, स्थिर uint8_t* iv)
{
    स_नकल(a->गणक, iv, माप(a->गणक));
    a->block_offset = 0;
}

स्थिर uint8_t* av_aes_ctr_get_iv(काष्ठा AVAESCTR *a)
{
    वापस a->गणक;
}

व्योम av_aes_ctr_set_random_iv(काष्ठा AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_seed();
    iv[1] = av_get_random_seed();

    av_aes_ctr_set_iv(a, (uint8_t*)iv);
}

पूर्णांक av_aes_ctr_init(काष्ठा AVAESCTR *a, स्थिर uint8_t *कुंजी)
{
    av_aes_init(&a->aes, कुंजी, 128, 0);

    स_रखो(a->गणक, 0, माप(a->गणक));
    a->block_offset = 0;

    वापस 0;
}

व्योम av_aes_ctr_free(काष्ठा AVAESCTR *a)
{
    av_free(a);
}

अटल अंतरभूत व्योम av_aes_ctr_increment_be64(uint8_t* गणक)
{
    uint64_t c = AV_RB64A(गणक) + 1;
    AV_WB64A(गणक, c);
}

व्योम av_aes_ctr_increment_iv(काष्ठा AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->गणक);
    स_रखो(a->गणक + AES_CTR_IV_आकार, 0, माप(a->गणक) - AES_CTR_IV_आकार);
    a->block_offset = 0;
}

व्योम av_aes_ctr_crypt(काष्ठा AVAESCTR *a, uint8_t *dst, स्थिर uint8_t *src, पूर्णांक गिनती)
{
    अगर (a->block_offset && गिनती > 0) {
        पूर्णांक बायाँ = FFMIN(गिनती, AES_BLOCK_आकार - a->block_offset);
        क्रम (पूर्णांक len = 0; len < बायाँ; len++)
            dst[len] = src[len] ^ a->encrypted_गणक[a->block_offset++];
        a->block_offset &= AES_BLOCK_आकार - 1;
        dst += बायाँ;
        src += बायाँ;
        गिनती -= बायाँ;
    }

    जबतक (गिनती >= AES_BLOCK_आकार) {
        av_aes_crypt(&a->aes, a->encrypted_गणक, a->गणक, 1, शून्य, 0);
        av_aes_ctr_increment_be64(a->गणक + 8);
#अगर HAVE_FAST_64BIT
        क्रम (पूर्णांक len = 0; len < AES_BLOCK_आकार; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_गणक[len]));
#अन्यथा
        क्रम (पूर्णांक len = 0; len < AES_BLOCK_आकार; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_गणक[len]));
#पूर्ण_अगर
        dst += AES_BLOCK_आकार;
        src += AES_BLOCK_आकार;
        गिनती -= AES_BLOCK_आकार;
    }

    अगर (गिनती > 0) {
        av_aes_crypt(&a->aes, a->encrypted_गणक, a->गणक, 1, शून्य, 0);
        av_aes_ctr_increment_be64(a->गणक + 8);
        क्रम (पूर्णांक len = 0; len < गिनती; len++)
            dst[len] = src[len] ^ a->encrypted_गणक[a->block_offset++];
    }
}
