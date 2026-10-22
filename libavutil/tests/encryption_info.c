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

#অন্তর্ভাব "libavutil/encryption_info.h"

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "libavutil/avassert.h"
#অন্তর্ভাব "libavutil/mem.h"

স্থির ধ্রুবক AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
স্থির ধ্রুবক size_t test_subsample_গুনতি = আকার(test_subsamples) / আকার(test_subsamples[0]);
স্থির ধ্রুবক uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
স্থির ধ্রুবক uint8_t test_চাবি_id[] = {0x21, 0x22, 0x23, 0x24};
স্থির ধ্রুবক uint8_t test_চাবি_id_2[] = {0x31, 0x32, 0x33, 0x34};
স্থির ধ্রুবক uint8_t test_system_id[] = {0x41, 0x42, 0x43};
স্থির ধ্রুবক uint8_t test_তথ্য[] = {0x51, 0x52};

স্থির পূর্ণসংখ্যা compare_encryption_info(ধ্রুবক AVEncryptionInfo *a, ধ্রুবক AVEncryptionInfo *b) {
    যদি (!a || !b || a->scheme != b->scheme || a->crypt_byte_block != b->crypt_byte_block ||
        a->skip_byte_block != b->skip_byte_block || a->চাবি_id_আকার != b->চাবি_id_আকার ||
        a->iv_আকার != b->iv_আকার || a->subsample_গুনতি != b->subsample_গুনতি)
        ফেরত 1;

    যদি (memcmp(a->চাবি_id, b->চাবি_id, a->চাবি_id_আকার) != 0 ||
        memcmp(a->iv, b->iv, a->iv_আকার) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_গুনতি * আকার(a->subsamples[0])))
        ফেরত 1;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা compare_encryption_init_info(ধ্রুবক AVEncryptionInitInfo *a, ধ্রুবক AVEncryptionInitInfo *b) {
    যদি (!a || !b || a->system_id_আকার != b->system_id_আকার ||
        a->অঙ্ক_চাবি_ids != b->অঙ্ক_চাবি_ids || a->চাবি_id_আকার != b->চাবি_id_আকার ||
        a->তথ্য_আকার != b->তথ্য_আকার)
        ফেরত 1;

    যদি (memcmp(a->system_id, b->system_id, a->system_id_আকার) != 0 ||
        memcmp(a->তথ্য, b->তথ্য, a->তথ্য_আকার) != 0)
        ফেরত 1;

    জন্য (uint32_t i = 0; i < a->অঙ্ক_চাবি_ids; i++) {
        যদি (memcmp(a->চাবি_ids[i], b->চাবি_ids[i], a->চাবি_id_আকার) != 0)
            ফেরত 1;
    }

    যদি (a->পরবর্তী || b->পরবর্তী) {
        যদি (!a->পরবর্তী || !b->পরবর্তী)
            ফেরত 1;
        যদি (compare_encryption_init_info(a->পরবর্তী, b->পরবর্তী) != 0)
            ফেরত 1;
    }

    ফেরত 0;
}

স্থির শূন্য run_encryption_info_test(শূন্য)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_তথ্য;
    size_t side_তথ্য_আকার;

    info = av_encryption_info_alloc(test_subsample_গুনতি, আকার(test_চাবি_id), আকার(test_iv));
    av_assert0(info);
    av_assert0(info->চাবি_id);
    av_assert0(info->চাবি_id_আকার == আকার(test_চাবি_id));
    av_assert0(info->iv);
    av_assert0(info->iv_আকার == আকার(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_গুনতি == test_subsample_গুনতি);

    info->scheme = 1234;
    info->crypt_byte_block = 333;
    info->skip_byte_block = 444;
    memcpy(info->চাবি_id, test_চাবি_id, আকার(test_চাবি_id));
    memcpy(info->iv, test_iv, আকার(test_iv));
    memcpy(info->subsamples, test_subsamples, আকার(test_subsamples));

    copy = av_encryption_info_clone(info);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);

    side_তথ্য = av_encryption_info_add_side_তথ্য(info, &side_তথ্য_আকার);
    av_assert0(side_তথ্য);
    av_assert0(side_তথ্য_আকার > 0);

    copy = av_encryption_info_get_side_তথ্য(side_তথ্য, side_তথ্য_আকার);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);
    av_free(side_তথ্য);

    av_encryption_info_free(info);
}

স্থির AVEncryptionInitInfo *create_init_info(শূন্য)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(আকার(test_system_id), 2, আকার(test_চাবি_id), আকার(test_তথ্য));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_আকার == আকার(test_system_id));
    av_assert0(info->চাবি_ids);
    av_assert0(info->অঙ্ক_চাবি_ids == 2);
    av_assert0(info->চাবি_id_আকার == আকার(test_চাবি_id));
    av_assert0(info->চাবি_ids[0]);
    av_assert0(info->চাবি_ids[1]);
    av_assert0(info->তথ্য);
    av_assert0(info->তথ্য_আকার == আকার(test_তথ্য));
    av_assert0(!info->পরবর্তী);

    memcpy(info->system_id, test_system_id, আকার(test_system_id));
    memcpy(info->চাবি_ids[0], test_চাবি_id, আকার(test_চাবি_id));
    memcpy(info->চাবি_ids[1], test_চাবি_id_2, আকার(test_চাবি_id_2));
    memcpy(info->তথ্য, test_তথ্য, আকার(test_তথ্য));

    ফেরত info;
}

স্থির শূন্য run_encryption_init_info_test(শূন্য)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_তথ্য, *appended;
    size_t side_তথ্য_আকার, appended_আকার;
    unsigned পূর্ণসংখ্যা allocated_আকার = 0;

    info = create_init_info();

    side_তথ্য = av_encryption_init_info_add_side_তথ্য(info, &side_তথ্য_আকার);
    av_assert0(side_তথ্য);
    av_assert0(side_তথ্য_আকার > 0);
    copy = av_encryption_init_info_get_side_তথ্য(side_তথ্য, side_তথ্য_আকার);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);
    av_free(side_তথ্য);

    // Make the first init info different from the second to test the correct order.
    memset(info->system_id, 0, info->system_id_আকার);
    appended = av_encryption_init_info_add_side_তথ্য(info, &appended_আকার);
    av_assert0(appended);
    info->পরবর্তী = create_init_info();
    side_তথ্য = av_encryption_init_info_add_side_তথ্য(info, &side_তথ্য_আকার);
    av_assert0(side_তথ্য);
    copy = av_encryption_init_info_get_side_তথ্য(side_তথ্য, side_তথ্য_আকার);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);

    av_assert0(av_encryption_init_info_append_side_তথ্য(&appended, &appended_আকার, &allocated_আকার, info->পরবর্তী) == 0);
    av_assert0(appended_আকার == side_তথ্য_আকার);
    av_assert0(memcmp(appended, side_তথ্য, side_তথ্য_আকার) == 0);
    av_free(appended);
    av_free(side_তথ্য);

    av_encryption_init_info_free(info);
}

পূর্ণসংখ্যা প্রধান(পূর্ণসংখ্যা argc, অক্ষর **argv)
{
    run_encryption_info_test();
    run_encryption_init_info_test();
    ফেরত 0;
}
