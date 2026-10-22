/*
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

#ضمن "libavutil/encryption_info.h"

#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "libavutil/avassert.h"
#ضمن "libavutil/mem.h"

ساكن ثابت AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
ساكن ثابت size_t test_subsample_گنتی = حجم(test_subsamples) / حجم(test_subsamples[0]);
ساكن ثابت uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
ساكن ثابت uint8_t test_کلید_id[] = {0x21, 0x22, 0x23, 0x24};
ساكن ثابت uint8_t test_کلید_id_2[] = {0x31, 0x32, 0x33, 0x34};
ساكن ثابت uint8_t test_system_id[] = {0x41, 0x42, 0x43};
ساكن ثابت uint8_t test_انکڑے[] = {0x51, 0x52};

ساكن صحيح compare_encryption_info(ثابت AVEncryptionInfo *a, ثابت AVEncryptionInfo *b) {
    إذا (!a || !b || a->scheme != b->scheme || a->crypt_byte_بلاک != b->crypt_byte_بلاک ||
        a->skip_byte_بلاک != b->skip_byte_بلاک || a->کلید_id_ناپ != b->کلید_id_ناپ ||
        a->iv_ناپ != b->iv_ناپ || a->subsample_گنتی != b->subsample_گنتی)
        أرجع 1;

    إذا (memcmp(a->کلید_id, b->کلید_id, a->کلید_id_ناپ) != 0 ||
        memcmp(a->iv, b->iv, a->iv_ناپ) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_گنتی * حجم(a->subsamples[0])))
        أرجع 1;

    أرجع 0;
}

ساكن صحيح compare_encryption_init_info(ثابت AVEncryptionInitInfo *a, ثابت AVEncryptionInitInfo *b) {
    إذا (!a || !b || a->system_id_ناپ != b->system_id_ناپ ||
        a->عدد_کلید_ids != b->عدد_کلید_ids || a->کلید_id_ناپ != b->کلید_id_ناپ ||
        a->انکڑے_ناپ != b->انکڑے_ناپ)
        أرجع 1;

    إذا (memcmp(a->system_id, b->system_id, a->system_id_ناپ) != 0 ||
        memcmp(a->انکڑے, b->انکڑے, a->انکڑے_ناپ) != 0)
        أرجع 1;

    لكل (uint32_t i = 0; i < a->عدد_کلید_ids; i++) {
        إذا (memcmp(a->کلید_ids[i], b->کلید_ids[i], a->کلید_id_ناپ) != 0)
            أرجع 1;
    }

    إذا (a->اگلا || b->اگلا) {
        إذا (!a->اگلا || !b->اگلا)
            أرجع 1;
        إذا (compare_encryption_init_info(a->اگلا, b->اگلا) != 0)
            أرجع 1;
    }

    أرجع 0;
}

ساكن فراغ لگاتار_encryption_info_test(فراغ)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_انکڑے;
    size_t side_انکڑے_ناپ;

    info = av_encryption_info_alloc(test_subsample_گنتی, حجم(test_کلید_id), حجم(test_iv));
    av_assert0(info);
    av_assert0(info->کلید_id);
    av_assert0(info->کلید_id_ناپ == حجم(test_کلید_id));
    av_assert0(info->iv);
    av_assert0(info->iv_ناپ == حجم(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_گنتی == test_subsample_گنتی);

    info->scheme = 1234;
    info->crypt_byte_بلاک = 333;
    info->skip_byte_بلاک = 444;
    حافظہ_نقل(info->کلید_id, test_کلید_id, حجم(test_کلید_id));
    حافظہ_نقل(info->iv, test_iv, حجم(test_iv));
    حافظہ_نقل(info->subsamples, test_subsamples, حجم(test_subsamples));

    copy = av_encryption_info_clone(info);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);

    side_انکڑے = av_encryption_info_جوڑو_side_انکڑے(info, &side_انکڑے_ناپ);
    av_assert0(side_انکڑے);
    av_assert0(side_انکڑے_ناپ > 0);

    copy = av_encryption_info_get_side_انکڑے(side_انکڑے, side_انکڑے_ناپ);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);
    av_free(side_انکڑے);

    av_encryption_info_free(info);
}

ساكن AVEncryptionInitInfo *create_init_info(فراغ)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(حجم(test_system_id), 2, حجم(test_کلید_id), حجم(test_انکڑے));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_ناپ == حجم(test_system_id));
    av_assert0(info->کلید_ids);
    av_assert0(info->عدد_کلید_ids == 2);
    av_assert0(info->کلید_id_ناپ == حجم(test_کلید_id));
    av_assert0(info->کلید_ids[0]);
    av_assert0(info->کلید_ids[1]);
    av_assert0(info->انکڑے);
    av_assert0(info->انکڑے_ناپ == حجم(test_انکڑے));
    av_assert0(!info->اگلا);

    حافظہ_نقل(info->system_id, test_system_id, حجم(test_system_id));
    حافظہ_نقل(info->کلید_ids[0], test_کلید_id, حجم(test_کلید_id));
    حافظہ_نقل(info->کلید_ids[1], test_کلید_id_2, حجم(test_کلید_id_2));
    حافظہ_نقل(info->انکڑے, test_انکڑے, حجم(test_انکڑے));

    أرجع info;
}

ساكن فراغ لگاتار_encryption_init_info_test(فراغ)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_انکڑے, *appended;
    size_t side_انکڑے_ناپ, appended_ناپ;
    بنانشانی صحيح allocated_ناپ = 0;

    info = create_init_info();

    side_انکڑے = av_encryption_init_info_جوڑو_side_انکڑے(info, &side_انکڑے_ناپ);
    av_assert0(side_انکڑے);
    av_assert0(side_انکڑے_ناپ > 0);
    copy = av_encryption_init_info_get_side_انکڑے(side_انکڑے, side_انکڑے_ناپ);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);
    av_free(side_انکڑے);

    // Make the first init info different from the second to test the correct order.
    memset(info->system_id, 0, info->system_id_ناپ);
    appended = av_encryption_init_info_جوڑو_side_انکڑے(info, &appended_ناپ);
    av_assert0(appended);
    info->اگلا = create_init_info();
    side_انکڑے = av_encryption_init_info_جوڑو_side_انکڑے(info, &side_انکڑے_ناپ);
    av_assert0(side_انکڑے);
    copy = av_encryption_init_info_get_side_انکڑے(side_انکڑے, side_انکڑے_ناپ);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);

    av_assert0(av_encryption_init_info_append_side_انکڑے(&appended, &appended_ناپ, &allocated_ناپ, info->اگلا) == 0);
    av_assert0(appended_ناپ == side_انکڑے_ناپ);
    av_assert0(memcmp(appended, side_انکڑے, side_انکڑے_ناپ) == 0);
    av_free(appended);
    av_free(side_انکڑے);

    av_encryption_init_info_free(info);
}

صحيح مکھ(صحيح argc, حرف **argv)
{
    لگاتار_encryption_info_test();
    لگاتار_encryption_init_info_test();
    أرجع 0;
}
