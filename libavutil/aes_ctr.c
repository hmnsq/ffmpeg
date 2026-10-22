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

#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "aes_ctr.h"
#અન્તર્ભાવ "aes.h"
#અન્તર્ભાવ "aes_internal.h"
#અન્તર્ભાવ "intreadwrite.h"
#અન્તર્ભાવ "macros.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "random_seed.h"

#define AES_BLOCK_SIZE (16)

પ્રકારવ્યાખ્યા સંરચના AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_BLOCK_SIZE];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_BLOCK_SIZE];
    પૂર્ણાંક block_offset;
    AVAES aes;
} AVAESCTR;

સંરચના AVAESCTR *av_aes_ctr_alloc(શૂન્ય)
{
    પાછા av_mallocz(કદ(સંરચના AVAESCTR));
}

શૂન્ય av_aes_ctr_set_iv(સંરચના AVAESCTR *a, અચલ uint8_t* iv)
{
    memcpy(a->counter, iv, AES_CTR_IV_SIZE);
    memset(a->counter + AES_CTR_IV_SIZE, 0, કદ(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

શૂન્ય av_aes_ctr_set_full_iv(સંરચના AVAESCTR *a, અચલ uint8_t* iv)
{
    memcpy(a->counter, iv, કદ(a->counter));
    a->block_offset = 0;
}

અચલ uint8_t* av_aes_ctr_get_iv(સંરચના AVAESCTR *a)
{
    પાછા a->counter;
}

શૂન્ય av_aes_ctr_set_random_iv(સંરચના AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_seed();
    iv[1] = av_get_random_seed();

    av_aes_ctr_set_iv(a, (uint8_t*)iv);
}

પૂર્ણાંક av_aes_ctr_init(સંરચના AVAESCTR *a, અચલ uint8_t *ચાવી)
{
    av_aes_init(&a->aes, ચાવી, 128, 0);

    memset(a->counter, 0, કદ(a->counter));
    a->block_offset = 0;

    પાછા 0;
}

શૂન્ય av_aes_ctr_free(સંરચના AVAESCTR *a)
{
    av_free(a);
}

સ્થિર અંતઃરેખ શૂન્ય av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

શૂન્ય av_aes_ctr_increment_iv(સંરચના AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    memset(a->counter + AES_CTR_IV_SIZE, 0, કદ(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

શૂન્ય av_aes_ctr_crypt(સંરચના AVAESCTR *a, uint8_t *dst, અચલ uint8_t *src, પૂર્ણાંક ગણતરી)
{
    જો (a->block_offset && ગણતરી > 0) {
        પૂર્ણાંક ડાબું = FFMIN(ગણતરી, AES_BLOCK_SIZE - a->block_offset);
        માટે (પૂર્ણાંક len = 0; len < ડાબું; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
        a->block_offset &= AES_BLOCK_SIZE - 1;
        dst += ડાબું;
        src += ડાબું;
        ગણતરી -= ડાબું;
    }

    જ્યારે (ગણતરી >= AES_BLOCK_SIZE) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ખાલી, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#જો HAVE_FAST_64BIT
        માટે (પૂર્ણાંક len = 0; len < AES_BLOCK_SIZE; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#નહીંતર
        માટે (પૂર્ણાંક len = 0; len < AES_BLOCK_SIZE; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#endif
        dst += AES_BLOCK_SIZE;
        src += AES_BLOCK_SIZE;
        ગણતરી -= AES_BLOCK_SIZE;
    }

    જો (ગણતરી > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ખાલી, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        માટે (પૂર્ણાંક len = 0; len < ગણતરી; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
    }
}
