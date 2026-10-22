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

#অন্তর্ভাৱ "libavutil/encryption_info.h"

#অন্তর্ভাৱ <stdio.h>
#অন্তর্ভাৱ <string.h>

#অন্তর্ভাৱ "libavutil/avassert.h"
#অন্তর্ভাৱ "libavutil/mem.h"

স্থির ধ্রুৱ AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
স্থির ধ্রুৱ size_t test_subsample_গুনতি = পরিমাণ(test_subsamples) / পরিমাণ(test_subsamples[0]);
স্থির ধ্রুৱ uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
স্থির ধ্রুৱ uint8_t test_চাবি_id[] = {0x21, 0x22, 0x23, 0x24};
স্থির ধ্রুৱ uint8_t test_চাবি_id_2[] = {0x31, 0x32, 0x33, 0x34};
স্থির ধ্রুৱ uint8_t test_system_id[] = {0x41, 0x42, 0x43};
স্থির ধ্রুৱ uint8_t test_data[] = {0x51, 0x52};

স্থির পূর্ণাঙ্ক compare_encryption_info(ধ্রুৱ AVEncryptionInfo *a, ধ্রুৱ AVEncryptionInfo *b) {
    যদি (!a || !b || a->scheme != b->scheme || a->crypt_byte_block != b->crypt_byte_block ||
        a->skip_byte_block != b->skip_byte_block || a->চাবি_id_size != b->চাবি_id_size ||
        a->iv_size != b->iv_size || a->subsample_গুনতি != b->subsample_গুনতি)
        ঘূৰাই 1;

    যদি (memcmp(a->চাবি_id, b->চাবি_id, a->চাবি_id_size) != 0 ||
        memcmp(a->iv, b->iv, a->iv_size) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_গুনতি * পরিমাণ(a->subsamples[0])))
        ঘূৰাই 1;

    ঘূৰাই 0;
}

স্থির পূর্ণাঙ্ক compare_encryption_init_info(ধ্রুৱ AVEncryptionInitInfo *a, ধ্রুৱ AVEncryptionInitInfo *b) {
    যদি (!a || !b || a->system_id_size != b->system_id_size ||
        a->অঙ্ক_চাবি_ids != b->অঙ্ক_চাবি_ids || a->চাবি_id_size != b->চাবি_id_size ||
        a->data_size != b->data_size)
        ঘূৰাই 1;

    যদি (memcmp(a->system_id, b->system_id, a->system_id_size) != 0 ||
        memcmp(a->data, b->data, a->data_size) != 0)
        ঘূৰাই 1;

    বাবে (uint32_t i = 0; i < a->অঙ্ক_চাবি_ids; i++) {
        যদি (memcmp(a->চাবি_ids[i], b->চাবি_ids[i], a->চাবি_id_size) != 0)
            ঘূৰাই 1;
    }

    যদি (a->next || b->next) {
        যদি (!a->next || !b->next)
            ঘূৰাই 1;
        যদি (compare_encryption_init_info(a->next, b->next) != 0)
            ঘূৰাই 1;
    }

    ঘূৰাই 0;
}

স্থির শূন্য run_encryption_info_test(শূন্য)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_data;
    size_t side_data_size;

    info = av_encryption_info_alloc(test_subsample_গুনতি, পরিমাণ(test_চাবি_id), পরিমাণ(test_iv));
    av_assert0(info);
    av_assert0(info->চাবি_id);
    av_assert0(info->চাবি_id_size == পরিমাণ(test_চাবি_id));
    av_assert0(info->iv);
    av_assert0(info->iv_size == পরিমাণ(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_গুনতি == test_subsample_গুনতি);

    info->scheme = 1234;
    info->crypt_byte_block = 333;
    info->skip_byte_block = 444;
    memcpy(info->চাবি_id, test_চাবি_id, পরিমাণ(test_চাবি_id));
    memcpy(info->iv, test_iv, পরিমাণ(test_iv));
    memcpy(info->subsamples, test_subsamples, পরিমাণ(test_subsamples));

    copy = av_encryption_info_clone(info);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);

    side_data = av_encryption_info_add_side_data(info, &side_data_size);
    av_assert0(side_data);
    av_assert0(side_data_size > 0);

    copy = av_encryption_info_get_side_data(side_data, side_data_size);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);
    av_free(side_data);

    av_encryption_info_free(info);
}

স্থির AVEncryptionInitInfo *create_init_info(শূন্য)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(পরিমাণ(test_system_id), 2, পরিমাণ(test_চাবি_id), পরিমাণ(test_data));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_size == পরিমাণ(test_system_id));
    av_assert0(info->চাবি_ids);
    av_assert0(info->অঙ্ক_চাবি_ids == 2);
    av_assert0(info->চাবি_id_size == পরিমাণ(test_চাবি_id));
    av_assert0(info->চাবি_ids[0]);
    av_assert0(info->চাবি_ids[1]);
    av_assert0(info->data);
    av_assert0(info->data_size == পরিমাণ(test_data));
    av_assert0(!info->next);

    memcpy(info->system_id, test_system_id, পরিমাণ(test_system_id));
    memcpy(info->চাবি_ids[0], test_চাবি_id, পরিমাণ(test_চাবি_id));
    memcpy(info->চাবি_ids[1], test_চাবি_id_2, পরিমাণ(test_চাবি_id_2));
    memcpy(info->data, test_data, পরিমাণ(test_data));

    ঘূৰাই info;
}

স্থির শূন্য run_encryption_init_info_test(শূন্য)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_data, *appended;
    size_t side_data_size, appended_size;
    unsigned পূর্ণাঙ্ক allocated_size = 0;

    info = create_init_info();

    side_data = av_encryption_init_info_add_side_data(info, &side_data_size);
    av_assert0(side_data);
    av_assert0(side_data_size > 0);
    copy = av_encryption_init_info_get_side_data(side_data, side_data_size);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);
    av_free(side_data);

    // Make the first init info different from the second to test the correct order.
    memset(info->system_id, 0, info->system_id_size);
    appended = av_encryption_init_info_add_side_data(info, &appended_size);
    av_assert0(appended);
    info->next = create_init_info();
    side_data = av_encryption_init_info_add_side_data(info, &side_data_size);
    av_assert0(side_data);
    copy = av_encryption_init_info_get_side_data(side_data, side_data_size);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);

    av_assert0(av_encryption_init_info_append_side_data(&appended, &appended_size, &allocated_size, info->next) == 0);
    av_assert0(appended_size == side_data_size);
    av_assert0(memcmp(appended, side_data, side_data_size) == 0);
    av_free(appended);
    av_free(side_data);

    av_encryption_init_info_free(info);
}

পূর্ণাঙ্ক main(পূর্ণাঙ্ক argc, ৱর্ণ **argv)
{
    run_encryption_info_test();
    run_encryption_init_info_test();
    ঘূৰাই 0;
}
