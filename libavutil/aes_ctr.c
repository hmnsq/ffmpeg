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

#ضمن <string.h>

#ضمن "aes_ctr.h"
#ضمن "aes.h"
#ضمن "aes_internal.h"
#ضمن "intreadwrite.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "random_seed.h"

#تعریف_کن AES_بلوک_اندازه (16)

تعريفنوع بنية AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, counter)[AES_بلوک_اندازه];
    DECLARE_ALIGNED(8, uint8_t, encrypted_counter)[AES_بلوک_اندازه];
    صحيح بلوک_جابه_جایی;
    AVAES aes;
} AVAESCTR;

بنية AVAESCTR *av_aes_ctr_alloc(فراغ)
{
    أرجع av_mallocz(حجم(بنية AVAESCTR));
}

فراغ av_aes_ctr_مجموعه_iv(بنية AVAESCTR *a, ثابت uint8_t* iv)
{
    کپی_حافظه(a->counter, iv, AES_CTR_IV_اندازه);
    memset(a->counter + AES_CTR_IV_اندازه, 0, حجم(a->counter) - AES_CTR_IV_اندازه);
    a->بلوک_جابه_جایی = 0;
}

فراغ av_aes_ctr_مجموعه_پر_iv(بنية AVAESCTR *a, ثابت uint8_t* iv)
{
    کپی_حافظه(a->counter, iv, حجم(a->counter));
    a->بلوک_جابه_جایی = 0;
}

ثابت uint8_t* av_aes_ctr_get_iv(بنية AVAESCTR *a)
{
    أرجع a->counter;
}

فراغ av_aes_ctr_مجموعه_random_iv(بنية AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_دانه();
    iv[1] = av_get_random_دانه();

    av_aes_ctr_مجموعه_iv(a, (uint8_t*)iv);
}

صحيح av_aes_ctr_init(بنية AVAESCTR *a, ثابت uint8_t *کلید)
{
    av_aes_init(&a->aes, کلید, 128, 0);

    memset(a->counter, 0, حجم(a->counter));
    a->بلوک_جابه_جایی = 0;

    أرجع 0;
}

فراغ av_aes_ctr_free(بنية AVAESCTR *a)
{
    av_free(a);
}

ساكن مضمن فراغ av_aes_ctr_increment_be64(uint8_t* counter)
{
    uint64_t c = AV_RB64A(counter) + 1;
    AV_WB64A(counter, c);
}

فراغ av_aes_ctr_increment_iv(بنية AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->counter);
    memset(a->counter + AES_CTR_IV_اندازه, 0, حجم(a->counter) - AES_CTR_IV_اندازه);
    a->بلوک_جابه_جایی = 0;
}

فراغ av_aes_ctr_crypt(بنية AVAESCTR *a, uint8_t *dst, ثابت uint8_t *src, صحيح شمار)
{
    إذا (a->بلوک_جابه_جایی && شمار > 0) {
        صحيح چپ = FFMIN(شمار, AES_بلوک_اندازه - a->بلوک_جابه_جایی);
        لكل (صحيح len = 0; len < چپ; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->بلوک_جابه_جایی++];
        a->بلوک_جابه_جایی &= AES_بلوک_اندازه - 1;
        dst += چپ;
        src += چپ;
        شمار -= چپ;
    }

    طالما (شمار >= AES_بلوک_اندازه) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, عدم, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
#إذا HAVE_FAST_64_بیت
        لكل (صحيح len = 0; len < AES_بلوک_اندازه; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_counter[len]));
#وإلا
        لكل (صحيح len = 0; len < AES_بلوک_اندازه; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_counter[len]));
#پایان_اگر
        dst += AES_بلوک_اندازه;
        src += AES_بلوک_اندازه;
        شمار -= AES_بلوک_اندازه;
    }

    إذا (شمار > 0) {
        av_aes_crypt(&a->aes, a->encrypted_counter, a->counter, 1, عدم, 0);
        av_aes_ctr_increment_be64(a->counter + 8);
        لكل (صحيح len = 0; len < شمار; len++)
            dst[len] = src[len] ^ a->encrypted_counter[a->بلوک_جابه_جایی++];
    }
}
