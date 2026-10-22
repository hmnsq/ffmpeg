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

#ಅನ್ತರ್ಭಾವ "libavutil/encryption_info.h"

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/avassert.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

ಸ್ಥಿರ ಧ್ರುವ AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
ಸ್ಥಿರ ಧ್ರುವ size_t test_subsample_ಎಣಿಕೆ = ಪರಿಮಾಣ(test_subsamples) / ಪರಿಮಾಣ(test_subsamples[0]);
ಸ್ಥಿರ ಧ್ರುವ uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
ಸ್ಥಿರ ಧ್ರುವ uint8_t test_ಕೀಲಿ_id[] = {0x21, 0x22, 0x23, 0x24};
ಸ್ಥಿರ ಧ್ರುವ uint8_t test_ಕೀಲಿ_id_2[] = {0x31, 0x32, 0x33, 0x34};
ಸ್ಥಿರ ಧ್ರುವ uint8_t test_system_id[] = {0x41, 0x42, 0x43};
ಸ್ಥಿರ ಧ್ರುವ uint8_t test_data[] = {0x51, 0x52};

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ compare_encryption_info(ಧ್ರುವ AVEncryptionInfo *a, ಧ್ರುವ AVEncryptionInfo *b) {
    ಯದಿ (!a || !b || a->scheme != b->scheme || a->crypt_byte_block != b->crypt_byte_block ||
        a->skip_byte_block != b->skip_byte_block || a->ಕೀಲಿ_id_size != b->ಕೀಲಿ_id_size ||
        a->iv_size != b->iv_size || a->subsample_ಎಣಿಕೆ != b->subsample_ಎಣಿಕೆ)
        ಪ್ರತ್ಯಾಗಮ 1;

    ಯದಿ (memcmp(a->ಕೀಲಿ_id, b->ಕೀಲಿ_id, a->ಕೀಲಿ_id_size) != 0 ||
        memcmp(a->iv, b->iv, a->iv_size) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_ಎಣಿಕೆ * ಪರಿಮಾಣ(a->subsamples[0])))
        ಪ್ರತ್ಯಾಗಮ 1;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ compare_encryption_init_info(ಧ್ರುವ AVEncryptionInitInfo *a, ಧ್ರುವ AVEncryptionInitInfo *b) {
    ಯದಿ (!a || !b || a->system_id_size != b->system_id_size ||
        a->ಅಂಕೆ_ಕೀಲಿ_ids != b->ಅಂಕೆ_ಕೀಲಿ_ids || a->ಕೀಲಿ_id_size != b->ಕೀಲಿ_id_size ||
        a->data_size != b->data_size)
        ಪ್ರತ್ಯಾಗಮ 1;

    ಯದಿ (memcmp(a->system_id, b->system_id, a->system_id_size) != 0 ||
        memcmp(a->data, b->data, a->data_size) != 0)
        ಪ್ರತ್ಯಾಗಮ 1;

    ಪ್ರತಿ (uint32_t i = 0; i < a->ಅಂಕೆ_ಕೀಲಿ_ids; i++) {
        ಯದಿ (memcmp(a->ಕೀಲಿ_ids[i], b->ಕೀಲಿ_ids[i], a->ಕೀಲಿ_id_size) != 0)
            ಪ್ರತ್ಯಾಗಮ 1;
    }

    ಯದಿ (a->next || b->next) {
        ಯದಿ (!a->next || !b->next)
            ಪ್ರತ್ಯಾಗಮ 1;
        ಯದಿ (compare_encryption_init_info(a->next, b->next) != 0)
            ಪ್ರತ್ಯಾಗಮ 1;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ run_encryption_info_test(ಶೂನ್ಯ)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_data;
    size_t side_data_size;

    info = av_encryption_info_alloc(test_subsample_ಎಣಿಕೆ, ಪರಿಮಾಣ(test_ಕೀಲಿ_id), ಪರಿಮಾಣ(test_iv));
    av_assert0(info);
    av_assert0(info->ಕೀಲಿ_id);
    av_assert0(info->ಕೀಲಿ_id_size == ಪರಿಮಾಣ(test_ಕೀಲಿ_id));
    av_assert0(info->iv);
    av_assert0(info->iv_size == ಪರಿಮಾಣ(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_ಎಣಿಕೆ == test_subsample_ಎಣಿಕೆ);

    info->scheme = 1234;
    info->crypt_byte_block = 333;
    info->skip_byte_block = 444;
    memcpy(info->ಕೀಲಿ_id, test_ಕೀಲಿ_id, ಪರಿಮಾಣ(test_ಕೀಲಿ_id));
    memcpy(info->iv, test_iv, ಪರಿಮಾಣ(test_iv));
    memcpy(info->subsamples, test_subsamples, ಪರಿಮಾಣ(test_subsamples));

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

ಸ್ಥಿರ AVEncryptionInitInfo *create_init_info(ಶೂನ್ಯ)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(ಪರಿಮಾಣ(test_system_id), 2, ಪರಿಮಾಣ(test_ಕೀಲಿ_id), ಪರಿಮಾಣ(test_data));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_size == ಪರಿಮಾಣ(test_system_id));
    av_assert0(info->ಕೀಲಿ_ids);
    av_assert0(info->ಅಂಕೆ_ಕೀಲಿ_ids == 2);
    av_assert0(info->ಕೀಲಿ_id_size == ಪರಿಮಾಣ(test_ಕೀಲಿ_id));
    av_assert0(info->ಕೀಲಿ_ids[0]);
    av_assert0(info->ಕೀಲಿ_ids[1]);
    av_assert0(info->data);
    av_assert0(info->data_size == ಪರಿಮಾಣ(test_data));
    av_assert0(!info->next);

    memcpy(info->system_id, test_system_id, ಪರಿಮಾಣ(test_system_id));
    memcpy(info->ಕೀಲಿ_ids[0], test_ಕೀಲಿ_id, ಪರಿಮಾಣ(test_ಕೀಲಿ_id));
    memcpy(info->ಕೀಲಿ_ids[1], test_ಕೀಲಿ_id_2, ಪರಿಮಾಣ(test_ಕೀಲಿ_id_2));
    memcpy(info->data, test_data, ಪರಿಮಾಣ(test_data));

    ಪ್ರತ್ಯಾಗಮ info;
}

ಸ್ಥಿರ ಶೂನ್ಯ run_encryption_init_info_test(ಶೂನ್ಯ)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_data, *appended;
    size_t side_data_size, appended_size;
    unsigned ಪೂರ್ಣಾಙ್ಕ allocated_size = 0;

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

ಪೂರ್ಣಾಙ್ಕ main(ಪೂರ್ಣಾಙ್ಕ argc, ವರ್ಣ **argv)
{
    run_encryption_info_test();
    run_encryption_init_info_test();
    ಪ್ರತ್ಯಾಗಮ 0;
}
