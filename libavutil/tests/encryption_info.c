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

#અન્તર્ભાવ "libavutil/encryption_info.h"

#અન્તર્ભાવ <stdio.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "libavutil/avassert.h"
#અન્તર્ભાવ "libavutil/mem.h"

સ્થિર અચલ AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
સ્થિર અચલ size_t test_subsample_ગણતરી = કદ(test_subsamples) / કદ(test_subsamples[0]);
સ્થિર અચલ uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
સ્થિર અચલ uint8_t test_ચાવી_id[] = {0x21, 0x22, 0x23, 0x24};
સ્થિર અચલ uint8_t test_ચાવી_id_2[] = {0x31, 0x32, 0x33, 0x34};
સ્થિર અચલ uint8_t test_system_id[] = {0x41, 0x42, 0x43};
સ્થિર અચલ uint8_t test_data[] = {0x51, 0x52};

સ્થિર પૂર્ણાંક compare_encryption_info(અચલ AVEncryptionInfo *a, અચલ AVEncryptionInfo *b) {
    જો (!a || !b || a->scheme != b->scheme || a->crypt_byte_block != b->crypt_byte_block ||
        a->skip_byte_block != b->skip_byte_block || a->ચાવી_id_size != b->ચાવી_id_size ||
        a->iv_size != b->iv_size || a->subsample_ગણતરી != b->subsample_ગણતરી)
        પાછા 1;

    જો (memcmp(a->ચાવી_id, b->ચાવી_id, a->ચાવી_id_size) != 0 ||
        memcmp(a->iv, b->iv, a->iv_size) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_ગણતરી * કદ(a->subsamples[0])))
        પાછા 1;

    પાછા 0;
}

સ્થિર પૂર્ણાંક compare_encryption_init_info(અચલ AVEncryptionInitInfo *a, અચલ AVEncryptionInitInfo *b) {
    જો (!a || !b || a->system_id_size != b->system_id_size ||
        a->અંક_ચાવી_ids != b->અંક_ચાવી_ids || a->ચાવી_id_size != b->ચાવી_id_size ||
        a->data_size != b->data_size)
        પાછા 1;

    જો (memcmp(a->system_id, b->system_id, a->system_id_size) != 0 ||
        memcmp(a->data, b->data, a->data_size) != 0)
        પાછા 1;

    માટે (uint32_t i = 0; i < a->અંક_ચાવી_ids; i++) {
        જો (memcmp(a->ચાવી_ids[i], b->ચાવી_ids[i], a->ચાવી_id_size) != 0)
            પાછા 1;
    }

    જો (a->next || b->next) {
        જો (!a->next || !b->next)
            પાછા 1;
        જો (compare_encryption_init_info(a->next, b->next) != 0)
            પાછા 1;
    }

    પાછા 0;
}

સ્થિર શૂન્ય run_encryption_info_test(શૂન્ય)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_data;
    size_t side_data_size;

    info = av_encryption_info_alloc(test_subsample_ગણતરી, કદ(test_ચાવી_id), કદ(test_iv));
    av_assert0(info);
    av_assert0(info->ચાવી_id);
    av_assert0(info->ચાવી_id_size == કદ(test_ચાવી_id));
    av_assert0(info->iv);
    av_assert0(info->iv_size == કદ(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_ગણતરી == test_subsample_ગણતરી);

    info->scheme = 1234;
    info->crypt_byte_block = 333;
    info->skip_byte_block = 444;
    memcpy(info->ચાવી_id, test_ચાવી_id, કદ(test_ચાવી_id));
    memcpy(info->iv, test_iv, કદ(test_iv));
    memcpy(info->subsamples, test_subsamples, કદ(test_subsamples));

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

સ્થિર AVEncryptionInitInfo *create_init_info(શૂન્ય)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(કદ(test_system_id), 2, કદ(test_ચાવી_id), કદ(test_data));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_size == કદ(test_system_id));
    av_assert0(info->ચાવી_ids);
    av_assert0(info->અંક_ચાવી_ids == 2);
    av_assert0(info->ચાવી_id_size == કદ(test_ચાવી_id));
    av_assert0(info->ચાવી_ids[0]);
    av_assert0(info->ચાવી_ids[1]);
    av_assert0(info->data);
    av_assert0(info->data_size == કદ(test_data));
    av_assert0(!info->next);

    memcpy(info->system_id, test_system_id, કદ(test_system_id));
    memcpy(info->ચાવી_ids[0], test_ચાવી_id, કદ(test_ચાવી_id));
    memcpy(info->ચાવી_ids[1], test_ચાવી_id_2, કદ(test_ચાવી_id_2));
    memcpy(info->data, test_data, કદ(test_data));

    પાછા info;
}

સ્થિર શૂન્ય run_encryption_init_info_test(શૂન્ય)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_data, *appended;
    size_t side_data_size, appended_size;
    unsigned પૂર્ણાંક allocated_size = 0;

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

પૂર્ણાંક મુખ્ય(પૂર્ણાંક argc, અક્ષર **argv)
{
    run_encryption_info_test();
    run_encryption_init_info_test();
    પાછા 0;
}
