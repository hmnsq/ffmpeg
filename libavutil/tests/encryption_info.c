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

#شامل "libavutil/encryption_info.h"

#شامل <stdio.h>
#شامل <string.h>

#شامل "libavutil/avassert.h"
#شامل "libavutil/mem.h"

ساکن ثابت AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
ساکن ثابت size_t test_subsample_گنتی = حجم(test_subsamples) / حجم(test_subsamples[0]);
ساکن ثابت uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
ساکن ثابت uint8_t test_کلید_id[] = {0x21, 0x22, 0x23, 0x24};
ساکن ثابت uint8_t test_کلید_id_2[] = {0x31, 0x32, 0x33, 0x34};
ساکن ثابت uint8_t test_system_id[] = {0x41, 0x42, 0x43};
ساکن ثابت uint8_t test_ڈیٹا[] = {0x51, 0x52};

ساکن صحیح compare_encryption_info(ثابت AVEncryptionInfo *a, ثابت AVEncryptionInfo *b) {
    اگر (!a || !b || a->scheme != b->scheme || a->crypt_byte_بلاک != b->crypt_byte_بلاک ||
        a->skip_byte_بلاک != b->skip_byte_بلاک || a->کلید_id_سائز != b->کلید_id_سائز ||
        a->iv_سائز != b->iv_سائز || a->subsample_گنتی != b->subsample_گنتی)
        واپس 1;

    اگر (memcmp(a->کلید_id, b->کلید_id, a->کلید_id_سائز) != 0 ||
        memcmp(a->iv, b->iv, a->iv_سائز) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_گنتی * حجم(a->subsamples[0])))
        واپس 1;

    واپس 0;
}

ساکن صحیح compare_encryption_init_info(ثابت AVEncryptionInitInfo *a, ثابت AVEncryptionInitInfo *b) {
    اگر (!a || !b || a->system_id_سائز != b->system_id_سائز ||
        a->عدد_کلید_ids != b->عدد_کلید_ids || a->کلید_id_سائز != b->کلید_id_سائز ||
        a->ڈیٹا_سائز != b->ڈیٹا_سائز)
        واپس 1;

    اگر (memcmp(a->system_id, b->system_id, a->system_id_سائز) != 0 ||
        memcmp(a->ڈیٹا, b->ڈیٹا, a->ڈیٹا_سائز) != 0)
        واپس 1;

    برائے (uint32_t i = 0; i < a->عدد_کلید_ids; i++) {
        اگر (memcmp(a->کلید_ids[i], b->کلید_ids[i], a->کلید_id_سائز) != 0)
            واپس 1;
    }

    اگر (a->اگلا || b->اگلا) {
        اگر (!a->اگلا || !b->اگلا)
            واپس 1;
        اگر (compare_encryption_init_info(a->اگلا, b->اگلا) != 0)
            واپس 1;
    }

    واپس 0;
}

ساکن خالی تسلسل_encryption_info_test(خالی)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_ڈیٹا;
    size_t side_ڈیٹا_سائز;

    info = av_encryption_info_alloc(test_subsample_گنتی, حجم(test_کلید_id), حجم(test_iv));
    av_assert0(info);
    av_assert0(info->کلید_id);
    av_assert0(info->کلید_id_سائز == حجم(test_کلید_id));
    av_assert0(info->iv);
    av_assert0(info->iv_سائز == حجم(test_iv));
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

    side_ڈیٹا = av_encryption_info_جوڑو_side_ڈیٹا(info, &side_ڈیٹا_سائز);
    av_assert0(side_ڈیٹا);
    av_assert0(side_ڈیٹا_سائز > 0);

    copy = av_encryption_info_get_side_ڈیٹا(side_ڈیٹا, side_ڈیٹا_سائز);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);
    av_free(side_ڈیٹا);

    av_encryption_info_free(info);
}

ساکن AVEncryptionInitInfo *create_init_info(خالی)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(حجم(test_system_id), 2, حجم(test_کلید_id), حجم(test_ڈیٹا));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_سائز == حجم(test_system_id));
    av_assert0(info->کلید_ids);
    av_assert0(info->عدد_کلید_ids == 2);
    av_assert0(info->کلید_id_سائز == حجم(test_کلید_id));
    av_assert0(info->کلید_ids[0]);
    av_assert0(info->کلید_ids[1]);
    av_assert0(info->ڈیٹا);
    av_assert0(info->ڈیٹا_سائز == حجم(test_ڈیٹا));
    av_assert0(!info->اگلا);

    حافظہ_نقل(info->system_id, test_system_id, حجم(test_system_id));
    حافظہ_نقل(info->کلید_ids[0], test_کلید_id, حجم(test_کلید_id));
    حافظہ_نقل(info->کلید_ids[1], test_کلید_id_2, حجم(test_کلید_id_2));
    حافظہ_نقل(info->ڈیٹا, test_ڈیٹا, حجم(test_ڈیٹا));

    واپس info;
}

ساکن خالی تسلسل_encryption_init_info_test(خالی)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_ڈیٹا, *appended;
    size_t side_ڈیٹا_سائز, appended_سائز;
    غیرعلامتی صحیح allocated_سائز = 0;

    info = create_init_info();

    side_ڈیٹا = av_encryption_init_info_جوڑو_side_ڈیٹا(info, &side_ڈیٹا_سائز);
    av_assert0(side_ڈیٹا);
    av_assert0(side_ڈیٹا_سائز > 0);
    copy = av_encryption_init_info_get_side_ڈیٹا(side_ڈیٹا, side_ڈیٹا_سائز);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);
    av_free(side_ڈیٹا);

    // Make the first init info different from the second to test the correct order.
    memset(info->system_id, 0, info->system_id_سائز);
    appended = av_encryption_init_info_جوڑو_side_ڈیٹا(info, &appended_سائز);
    av_assert0(appended);
    info->اگلا = create_init_info();
    side_ڈیٹا = av_encryption_init_info_جوڑو_side_ڈیٹا(info, &side_ڈیٹا_سائز);
    av_assert0(side_ڈیٹا);
    copy = av_encryption_init_info_get_side_ڈیٹا(side_ڈیٹا, side_ڈیٹا_سائز);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);

    av_assert0(av_encryption_init_info_append_side_ڈیٹا(&appended, &appended_سائز, &allocated_سائز, info->اگلا) == 0);
    av_assert0(appended_سائز == side_ڈیٹا_سائز);
    av_assert0(memcmp(appended, side_ڈیٹا, side_ڈیٹا_سائز) == 0);
    av_free(appended);
    av_free(side_ڈیٹا);

    av_encryption_init_info_free(info);
}

صحیح مین(صحیح argc, حرف **argv)
{
    تسلسل_encryption_info_test();
    تسلسل_encryption_init_info_test();
    واپس 0;
}
