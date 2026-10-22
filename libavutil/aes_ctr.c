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

#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "aes_ctr.h"
#അന്തര്ഭാവ "aes.h"
#അന്തര്ഭാവ "aes_internal.h"
#അന്തര്ഭാവ "intreadwrite.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "random_seed.h"

#define AES_BLOCK_SIZE (16)

തരനിർവചനം ഘടന AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_BLOCK_SIZE];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_BLOCK_SIZE];
    പൂർണ്ണസംഖ്യ block_offset;
    AVAES aes;
} AVAESCTR;

ഘടന AVAESCTR *av_aes_ctr_alloc(ശൂന്യം)
{
    തിരികെ av_mallocz(വലുപ്പം(ഘടന AVAESCTR));
}

ശൂന്യം av_aes_ctr_set_iv(ഘടന AVAESCTR *a, സ്ഥിരം uint8_t* iv)
{
    memcpy(a->counter, iv, AES_CTR_IV_SIZE);
    memset(a->counter + AES_CTR_IV_SIZE, 0, വലുപ്പം(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

ശൂന്യം av_aes_ctr_set_full_iv(ഘടന AVAESCTR *a, സ്ഥിരം uint8_t* iv)
{
    memcpy(a->counter, iv, വലുപ്പം(a->counter));
    a->block_offset = 0;
}

സ്ഥിരം uint8_t* av_aes_ctr_get_iv(ഘടന AVAESCTR *a)
{
    തിരികെ a->counter;
}

ശൂന്യം av_aes_ctr_set_random_iv(ഘടന AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_seed();
    iv[1] = av_get_random_seed();

    av_aes_ctr_set_iv(a, (uint8_t*)iv);
}

പൂർണ്ണസംഖ്യ av_aes_ctr_init(ഘടന AVAESCTR *a, സ്ഥിരം uint8_t *താക്കോൽ)
{
    av_aes_init(&a->aes, താക്കോൽ, 128, 0);

    memset(a->counter, 0, വലുപ്പം(a->counter));
    a->block_offset = 0;

    തിരികെ 0;
}

ശൂന്യം av_aes_ctr_free(ഘടന AVAESCTR *a)
{
    av_free(a);
}

സ്ഥിതം വരിയിൽ ശൂന്യം av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

ശൂന്യം av_aes_ctr_increment_iv(ഘടന AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    memset(a->counter + AES_CTR_IV_SIZE, 0, വലുപ്പം(a->counter) - AES_CTR_IV_SIZE);
    a->block_offset = 0;
}

ശൂന്യം av_aes_ctr_crypt(ഘടന AVAESCTR *a, uint8_t *dst, സ്ഥിരം uint8_t *src, പൂർണ്ണസംഖ്യ എണ്ണം)
{
    എങ്കിൽ (a->block_offset && എണ്ണം > 0) {
        പൂർണ്ണസംഖ്യ ഇടത് = FFMIN(എണ്ണം, AES_BLOCK_SIZE - a->block_offset);
        വേണ്ടി (പൂർണ്ണസംഖ്യ len = 0; len < ഇടത്; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
        a->block_offset &= AES_BLOCK_SIZE - 1;
        dst += ഇടത്;
        src += ഇടത്;
        എണ്ണം -= ഇടത്;
    }

    ആകുമ്പോൾ (എണ്ണം >= AES_BLOCK_SIZE) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ശൂന്യ, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#എങ്കിൽ HAVE_FAST_64BIT
        വേണ്ടി (പൂർണ്ണസംഖ്യ len = 0; len < AES_BLOCK_SIZE; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#അല്ലെങ്കിൽ
        വേണ്ടി (പൂർണ്ണസംഖ്യ len = 0; len < AES_BLOCK_SIZE; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#endif
        dst += AES_BLOCK_SIZE;
        src += AES_BLOCK_SIZE;
        എണ്ണം -= AES_BLOCK_SIZE;
    }

    എങ്കിൽ (എണ്ണം > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, ശൂന്യ, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        വേണ്ടി (പൂർണ്ണസംഖ്യ len = 0; len < എണ്ണം; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->block_offset++];
    }
}
