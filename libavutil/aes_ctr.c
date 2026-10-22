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

#شامل <string.h>

#شامل "aes_ctr.h"
#شامل "aes.h"
#شامل "aes_internal.h"
#شامل "intreadwrite.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "random_seed.h"

#تعریف_کرو AES_بلاک_سائز (16)

قسمتعریف ساخت AVAESCTR {
    DECLARE_ALIGNED(8, uint8_t, شمار_2)[AES_بلاک_سائز];
    DECLARE_ALIGNED(8, uint8_t, encrypted_شمار)[AES_بلاک_سائز];
    صحیح بلاک_انحراف;
    AVAES aes;
} AVAESCTR;

ساخت AVAESCTR *av_aes_ctr_alloc(خالی)
{
    واپس av_mallocz(حجم(ساخت AVAESCTR));
}

خالی av_aes_ctr_سیٹ_iv(ساخت AVAESCTR *a, ثابت uint8_t* iv)
{
    حافظہ_نقل(a->شمار_2, iv, AES_CTR_IV_سائز);
    memset(a->شمار_2 + AES_CTR_IV_سائز, 0, حجم(a->شمار_2) - AES_CTR_IV_سائز);
    a->بلاک_انحراف = 0;
}

خالی av_aes_ctr_سیٹ_بھرا_iv(ساخت AVAESCTR *a, ثابت uint8_t* iv)
{
    حافظہ_نقل(a->شمار_2, iv, حجم(a->شمار_2));
    a->بلاک_انحراف = 0;
}

ثابت uint8_t* av_aes_ctr_get_iv(ساخت AVAESCTR *a)
{
    واپس a->شمار_2;
}

خالی av_aes_ctr_سیٹ_random_iv(ساخت AVAESCTR *a)
{
    uint32_t iv[2];

    iv[0] = av_get_random_بیج();
    iv[1] = av_get_random_بیج();

    av_aes_ctr_سیٹ_iv(a, (uint8_t*)iv);
}

صحیح av_aes_ctr_init(ساخت AVAESCTR *a, ثابت uint8_t *کلید)
{
    av_aes_init(&a->aes, کلید, 128, 0);

    memset(a->شمار_2, 0, حجم(a->شمار_2));
    a->بلاک_انحراف = 0;

    واپس 0;
}

خالی av_aes_ctr_free(ساخت AVAESCTR *a)
{
    av_free(a);
}

ساکن اندرونی خالی av_aes_ctr_increment_be64(uint8_t* شمار_2)
{
    uint64_t c = AV_RB64A(شمار_2) + 1;
    AV_WB64A(شمار_2, c);
}

خالی av_aes_ctr_increment_iv(ساخت AVAESCTR *a)
{
    av_aes_ctr_increment_be64(a->شمار_2);
    memset(a->شمار_2 + AES_CTR_IV_سائز, 0, حجم(a->شمار_2) - AES_CTR_IV_سائز);
    a->بلاک_انحراف = 0;
}

خالی av_aes_ctr_crypt(ساخت AVAESCTR *a, uint8_t *dst, ثابت uint8_t *src, صحیح گنتی)
{
    اگر (a->بلاک_انحراف && گنتی > 0) {
        صحیح بایاں = FFMIN(گنتی, AES_بلاک_سائز - a->بلاک_انحراف);
        برائے (صحیح len = 0; len < بایاں; len++)
            dst[len] = src[len] ^ a->encrypted_شمار[a->بلاک_انحراف++];
        a->بلاک_انحراف &= AES_بلاک_سائز - 1;
        dst += بایاں;
        src += بایاں;
        گنتی -= بایاں;
    }

    جب (گنتی >= AES_بلاک_سائز) {
        av_aes_crypt(&a->aes, a->encrypted_شمار, a->شمار_2, 1, تہی, 0);
        av_aes_ctr_increment_be64(a->شمار_2 + 8);
#اگر HAVE_FAST_64_ثنائی_ہندسہ
        برائے (صحیح len = 0; len < AES_بلاک_سائز; len += 8)
            AV_WN64(&dst[len], AV_RN64(&src[len]) ^ AV_RN64A(&a->encrypted_شمار[len]));
#ورنہ
        برائے (صحیح len = 0; len < AES_بلاک_سائز; len += 4)
            AV_WN32(&dst[len], AV_RN32(&src[len]) ^ AV_RN32A(&a->encrypted_شمار[len]));
#اگر_ختم
        dst += AES_بلاک_سائز;
        src += AES_بلاک_سائز;
        گنتی -= AES_بلاک_سائز;
    }

    اگر (گنتی > 0) {
        av_aes_crypt(&a->aes, a->encrypted_شمار, a->شمار_2, 1, تہی, 0);
        av_aes_ctr_increment_be64(a->شمار_2 + 8);
        برائے (صحیح len = 0; len < گنتی; len++)
            dst[len] = src[len] ^ a->encrypted_شمار[a->بلاک_انحراف++];
    }
}
