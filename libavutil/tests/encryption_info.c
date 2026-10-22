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
ساكن ثابت size_t test_subsample_ڳڻپ = حجم(test_subsamples) / حجم(test_subsamples[0]);
ساكن ثابت uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
ساكن ثابت uint8_t test_ڪنجي_id[] = {0x21, 0x22, 0x23, 0x24};
ساكن ثابت uint8_t test_ڪنجي_id_2[] = {0x31, 0x32, 0x33, 0x34};
ساكن ثابت uint8_t test_system_id[] = {0x41, 0x42, 0x43};
ساكن ثابت uint8_t test_معلومات[] = {0x51, 0x52};

ساكن صحيح compare_encryption_info(ثابت AVEncryptionInfo *a, ثابت AVEncryptionInfo *b) {
    إذا (!a || !b || a->scheme != b->scheme || a->crypt_byte_بلاڪ != b->crypt_byte_بلاڪ ||
        a->skip_byte_بلاڪ != b->skip_byte_بلاڪ || a->ڪنجي_id_سائيز != b->ڪنجي_id_سائيز ||
        a->iv_سائيز != b->iv_سائيز || a->subsample_ڳڻپ != b->subsample_ڳڻپ)
        أرجع 1;

    إذا (memcmp(a->ڪنجي_id, b->ڪنجي_id, a->ڪنجي_id_سائيز) != 0 ||
        memcmp(a->iv, b->iv, a->iv_سائيز) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_ڳڻپ * حجم(a->subsamples[0])))
        أرجع 1;

    أرجع 0;
}

ساكن صحيح compare_encryption_init_info(ثابت AVEncryptionInitInfo *a, ثابت AVEncryptionInitInfo *b) {
    إذا (!a || !b || a->system_id_سائيز != b->system_id_سائيز ||
        a->انگ_ڪنجي_ids != b->انگ_ڪنجي_ids || a->ڪنجي_id_سائيز != b->ڪنجي_id_سائيز ||
        a->معلومات_سائيز != b->معلومات_سائيز)
        أرجع 1;

    إذا (memcmp(a->system_id, b->system_id, a->system_id_سائيز) != 0 ||
        memcmp(a->معلومات, b->معلومات, a->معلومات_سائيز) != 0)
        أرجع 1;

    لكل (uint32_t i = 0; i < a->انگ_ڪنجي_ids; i++) {
        إذا (memcmp(a->ڪنجي_ids[i], b->ڪنجي_ids[i], a->ڪنجي_id_سائيز) != 0)
            أرجع 1;
    }

    إذا (a->ايندڙ || b->ايندڙ) {
        إذا (!a->ايندڙ || !b->ايندڙ)
            أرجع 1;
        إذا (compare_encryption_init_info(a->ايندڙ, b->ايندڙ) != 0)
            أرجع 1;
    }

    أرجع 0;
}

ساكن فراغ لاڳيتو_encryption_info_test(فراغ)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_معلومات;
    size_t side_معلومات_سائيز;

    info = av_encryption_info_alloc(test_subsample_ڳڻپ, حجم(test_ڪنجي_id), حجم(test_iv));
    av_assert0(info);
    av_assert0(info->ڪنجي_id);
    av_assert0(info->ڪنجي_id_سائيز == حجم(test_ڪنجي_id));
    av_assert0(info->iv);
    av_assert0(info->iv_سائيز == حجم(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_ڳڻپ == test_subsample_ڳڻپ);

    info->scheme = 1234;
    info->crypt_byte_بلاڪ = 333;
    info->skip_byte_بلاڪ = 444;
    يادگيري_نقل(info->ڪنجي_id, test_ڪنجي_id, حجم(test_ڪنجي_id));
    يادگيري_نقل(info->iv, test_iv, حجم(test_iv));
    يادگيري_نقل(info->subsamples, test_subsamples, حجم(test_subsamples));

    copy = av_encryption_info_clone(info);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);

    side_معلومات = av_encryption_info_جوڙيو_side_معلومات(info, &side_معلومات_سائيز);
    av_assert0(side_معلومات);
    av_assert0(side_معلومات_سائيز > 0);

    copy = av_encryption_info_get_side_معلومات(side_معلومات, side_معلومات_سائيز);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);
    av_free(side_معلومات);

    av_encryption_info_free(info);
}

ساكن AVEncryptionInitInfo *create_init_info(فراغ)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(حجم(test_system_id), 2, حجم(test_ڪنجي_id), حجم(test_معلومات));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_سائيز == حجم(test_system_id));
    av_assert0(info->ڪنجي_ids);
    av_assert0(info->انگ_ڪنجي_ids == 2);
    av_assert0(info->ڪنجي_id_سائيز == حجم(test_ڪنجي_id));
    av_assert0(info->ڪنجي_ids[0]);
    av_assert0(info->ڪنجي_ids[1]);
    av_assert0(info->معلومات);
    av_assert0(info->معلومات_سائيز == حجم(test_معلومات));
    av_assert0(!info->ايندڙ);

    يادگيري_نقل(info->system_id, test_system_id, حجم(test_system_id));
    يادگيري_نقل(info->ڪنجي_ids[0], test_ڪنجي_id, حجم(test_ڪنجي_id));
    يادگيري_نقل(info->ڪنجي_ids[1], test_ڪنجي_id_2, حجم(test_ڪنجي_id_2));
    يادگيري_نقل(info->معلومات, test_معلومات, حجم(test_معلومات));

    أرجع info;
}

ساكن فراغ لاڳيتو_encryption_init_info_test(فراغ)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_معلومات, *appended;
    size_t side_معلومات_سائيز, appended_سائيز;
    بنانشان صحيح allocated_سائيز = 0;

    info = create_init_info();

    side_معلومات = av_encryption_init_info_جوڙيو_side_معلومات(info, &side_معلومات_سائيز);
    av_assert0(side_معلومات);
    av_assert0(side_معلومات_سائيز > 0);
    copy = av_encryption_init_info_get_side_معلومات(side_معلومات, side_معلومات_سائيز);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);
    av_free(side_معلومات);

    // Make the first init info different from the second to test the correct order.
    memset(info->system_id, 0, info->system_id_سائيز);
    appended = av_encryption_init_info_جوڙيو_side_معلومات(info, &appended_سائيز);
    av_assert0(appended);
    info->ايندڙ = create_init_info();
    side_معلومات = av_encryption_init_info_جوڙيو_side_معلومات(info, &side_معلومات_سائيز);
    av_assert0(side_معلومات);
    copy = av_encryption_init_info_get_side_معلومات(side_معلومات, side_معلومات_سائيز);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);

    av_assert0(av_encryption_init_info_append_side_معلومات(&appended, &appended_سائيز, &allocated_سائيز, info->ايندڙ) == 0);
    av_assert0(appended_سائيز == side_معلومات_سائيز);
    av_assert0(memcmp(appended, side_معلومات, side_معلومات_سائيز) == 0);
    av_free(appended);
    av_free(side_معلومات);

    av_encryption_init_info_free(info);
}

صحيح مکيه(صحيح argc, حرف **argv)
{
    لاڳيتو_encryption_info_test();
    لاڳيتو_encryption_init_info_test();
    أرجع 0;
}
