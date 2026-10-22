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
ساكن ثابت size_t test_subsample_شمار = حجم(test_subsamples) / حجم(test_subsamples[0]);
ساكن ثابت uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
ساكن ثابت uint8_t test_کلید_id[] = {0x21, 0x22, 0x23, 0x24};
ساكن ثابت uint8_t test_کلید_id_2[] = {0x31, 0x32, 0x33, 0x34};
ساكن ثابت uint8_t test_system_id[] = {0x41, 0x42, 0x43};
ساكن ثابت uint8_t test_داده[] = {0x51, 0x52};

ساكن صحيح compare_encryption_info(ثابت AVEncryptionInfo *a, ثابت AVEncryptionInfo *b) {
    إذا (!a || !b || a->scheme != b->scheme || a->crypt_byte_بلوک != b->crypt_byte_بلوک ||
        a->skip_byte_بلوک != b->skip_byte_بلوک || a->کلید_id_اندازه != b->کلید_id_اندازه ||
        a->iv_اندازه != b->iv_اندازه || a->subsample_شمار != b->subsample_شمار)
        أرجع 1;

    إذا (memcmp(a->کلید_id, b->کلید_id, a->کلید_id_اندازه) != 0 ||
        memcmp(a->iv, b->iv, a->iv_اندازه) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_شمار * حجم(a->subsamples[0])))
        أرجع 1;

    أرجع 0;
}

ساكن صحيح compare_encryption_init_info(ثابت AVEncryptionInitInfo *a, ثابت AVEncryptionInitInfo *b) {
    إذا (!a || !b || a->system_id_اندازه != b->system_id_اندازه ||
        a->رقم_کلید_ids != b->رقم_کلید_ids || a->کلید_id_اندازه != b->کلید_id_اندازه ||
        a->داده_اندازه != b->داده_اندازه)
        أرجع 1;

    إذا (memcmp(a->system_id, b->system_id, a->system_id_اندازه) != 0 ||
        memcmp(a->داده, b->داده, a->داده_اندازه) != 0)
        أرجع 1;

    لكل (uint32_t i = 0; i < a->رقم_کلید_ids; i++) {
        إذا (memcmp(a->کلید_ids[i], b->کلید_ids[i], a->کلید_id_اندازه) != 0)
            أرجع 1;
    }

    إذا (a->بعدی || b->بعدی) {
        إذا (!a->بعدی || !b->بعدی)
            أرجع 1;
        إذا (compare_encryption_init_info(a->بعدی, b->بعدی) != 0)
            أرجع 1;
    }

    أرجع 0;
}

ساكن فراغ پیاپی_encryption_info_test(فراغ)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_داده;
    size_t side_داده_اندازه;

    info = av_encryption_info_alloc(test_subsample_شمار, حجم(test_کلید_id), حجم(test_iv));
    av_assert0(info);
    av_assert0(info->کلید_id);
    av_assert0(info->کلید_id_اندازه == حجم(test_کلید_id));
    av_assert0(info->iv);
    av_assert0(info->iv_اندازه == حجم(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_شمار == test_subsample_شمار);

    info->scheme = 1234;
    info->crypt_byte_بلوک = 333;
    info->skip_byte_بلوک = 444;
    کپی_حافظه(info->کلید_id, test_کلید_id, حجم(test_کلید_id));
    کپی_حافظه(info->iv, test_iv, حجم(test_iv));
    کپی_حافظه(info->subsamples, test_subsamples, حجم(test_subsamples));

    copy = av_encryption_info_clone(info);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);

    side_داده = av_encryption_info_جمع_کن_side_داده(info, &side_داده_اندازه);
    av_assert0(side_داده);
    av_assert0(side_داده_اندازه > 0);

    copy = av_encryption_info_get_side_داده(side_داده, side_داده_اندازه);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);
    av_free(side_داده);

    av_encryption_info_free(info);
}

ساكن AVEncryptionInitInfo *create_init_info(فراغ)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(حجم(test_system_id), 2, حجم(test_کلید_id), حجم(test_داده));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_اندازه == حجم(test_system_id));
    av_assert0(info->کلید_ids);
    av_assert0(info->رقم_کلید_ids == 2);
    av_assert0(info->کلید_id_اندازه == حجم(test_کلید_id));
    av_assert0(info->کلید_ids[0]);
    av_assert0(info->کلید_ids[1]);
    av_assert0(info->داده);
    av_assert0(info->داده_اندازه == حجم(test_داده));
    av_assert0(!info->بعدی);

    کپی_حافظه(info->system_id, test_system_id, حجم(test_system_id));
    کپی_حافظه(info->کلید_ids[0], test_کلید_id, حجم(test_کلید_id));
    کپی_حافظه(info->کلید_ids[1], test_کلید_id_2, حجم(test_کلید_id_2));
    کپی_حافظه(info->داده, test_داده, حجم(test_داده));

    أرجع info;
}

ساكن فراغ پیاپی_encryption_init_info_test(فراغ)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_داده, *appended;
    size_t side_داده_اندازه, appended_اندازه;
    بیعلامت صحيح allocated_اندازه = 0;

    info = create_init_info();

    side_داده = av_encryption_init_info_جمع_کن_side_داده(info, &side_داده_اندازه);
    av_assert0(side_داده);
    av_assert0(side_داده_اندازه > 0);
    copy = av_encryption_init_info_get_side_داده(side_داده, side_داده_اندازه);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);
    av_free(side_داده);

    // Make the first init info different from the second to test the correct order.
    memset(info->system_id, 0, info->system_id_اندازه);
    appended = av_encryption_init_info_جمع_کن_side_داده(info, &appended_اندازه);
    av_assert0(appended);
    info->بعدی = create_init_info();
    side_داده = av_encryption_init_info_جمع_کن_side_داده(info, &side_داده_اندازه);
    av_assert0(side_داده);
    copy = av_encryption_init_info_get_side_داده(side_داده, side_داده_اندازه);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);

    av_assert0(av_encryption_init_info_append_side_داده(&appended, &appended_اندازه, &allocated_اندازه, info->بعدی) == 0);
    av_assert0(appended_اندازه == side_داده_اندازه);
    av_assert0(memcmp(appended, side_داده, side_داده_اندازه) == 0);
    av_free(appended);
    av_free(side_داده);

    av_encryption_init_info_free(info);
}

صحيح اصلی(صحيح argc, حرف **argv)
{
    پیاپی_encryption_info_test();
    پیاپی_encryption_init_info_test();
    أرجع 0;
}
