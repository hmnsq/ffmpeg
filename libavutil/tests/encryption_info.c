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

#अन्तर्भाव "libavutil/encryption_info.h"

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/avassert.h"
#अन्तर्भाव "libavutil/mem.h"

स्थिर ध्रुव AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
स्थिर ध्रुव size_t test_subsample_गणनम् = परिमाण(test_subsamples) / परिमाण(test_subsamples[0]);
स्थिर ध्रुव uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
स्थिर ध्रुव uint8_t test_कुञ्चिका_id[] = {0x21, 0x22, 0x23, 0x24};
स्थिर ध्रुव uint8_t test_कुञ्चिका_id_2[] = {0x31, 0x32, 0x33, 0x34};
स्थिर ध्रुव uint8_t test_system_id[] = {0x41, 0x42, 0x43};
स्थिर ध्रुव uint8_t test_data[] = {0x51, 0x52};

स्थिर पूर्णाङ्क compare_encryption_info(ध्रुव AVEncryptionInfo *a, ध्रुव AVEncryptionInfo *b) {
    जइ (!a || !b || a->scheme != b->scheme || a->crypt_byte_block != b->crypt_byte_block ||
        a->skip_byte_block != b->skip_byte_block || a->कुञ्चिका_id_size != b->कुञ्चिका_id_size ||
        a->iv_size != b->iv_size || a->subsample_गणनम् != b->subsample_गणनम्)
        प्रत्यागम 1;

    जइ (memcmp(a->कुञ्चिका_id, b->कुञ्चिका_id, a->कुञ्चिका_id_size) != 0 ||
        memcmp(a->iv, b->iv, a->iv_size) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_गणनम् * परिमाण(a->subsamples[0])))
        प्रत्यागम 1;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क compare_encryption_init_info(ध्रुव AVEncryptionInitInfo *a, ध्रुव AVEncryptionInitInfo *b) {
    जइ (!a || !b || a->system_id_size != b->system_id_size ||
        a->अङ्कः_कुञ्चिका_ids != b->अङ्कः_कुञ्चिका_ids || a->कुञ्चिका_id_size != b->कुञ्चिका_id_size ||
        a->data_size != b->data_size)
        प्रत्यागम 1;

    जइ (memcmp(a->system_id, b->system_id, a->system_id_size) != 0 ||
        memcmp(a->data, b->data, a->data_size) != 0)
        प्रत्यागम 1;

    प्रति (uint32_t i = 0; i < a->अङ्कः_कुञ्चिका_ids; i++) {
        जइ (memcmp(a->कुञ्चिका_ids[i], b->कुञ्चिका_ids[i], a->कुञ्चिका_id_size) != 0)
            प्रत्यागम 1;
    }

    जइ (a->next || b->next) {
        जइ (!a->next || !b->next)
            प्रत्यागम 1;
        जइ (compare_encryption_init_info(a->next, b->next) != 0)
            प्रत्यागम 1;
    }

    प्रत्यागम 0;
}

स्थिर शून्य run_encryption_info_test(शून्य)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_data;
    size_t side_data_size;

    info = av_encryption_info_alloc(test_subsample_गणनम्, परिमाण(test_कुञ्चिका_id), परिमाण(test_iv));
    av_assert0(info);
    av_assert0(info->कुञ्चिका_id);
    av_assert0(info->कुञ्चिका_id_size == परिमाण(test_कुञ्चिका_id));
    av_assert0(info->iv);
    av_assert0(info->iv_size == परिमाण(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_गणनम् == test_subsample_गणनम्);

    info->scheme = 1234;
    info->crypt_byte_block = 333;
    info->skip_byte_block = 444;
    memcpy(info->कुञ्चिका_id, test_कुञ्चिका_id, परिमाण(test_कुञ्चिका_id));
    memcpy(info->iv, test_iv, परिमाण(test_iv));
    memcpy(info->subsamples, test_subsamples, परिमाण(test_subsamples));

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

स्थिर AVEncryptionInitInfo *create_init_info(शून्य)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(परिमाण(test_system_id), 2, परिमाण(test_कुञ्चिका_id), परिमाण(test_data));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_size == परिमाण(test_system_id));
    av_assert0(info->कुञ्चिका_ids);
    av_assert0(info->अङ्कः_कुञ्चिका_ids == 2);
    av_assert0(info->कुञ्चिका_id_size == परिमाण(test_कुञ्चिका_id));
    av_assert0(info->कुञ्चिका_ids[0]);
    av_assert0(info->कुञ्चिका_ids[1]);
    av_assert0(info->data);
    av_assert0(info->data_size == परिमाण(test_data));
    av_assert0(!info->next);

    memcpy(info->system_id, test_system_id, परिमाण(test_system_id));
    memcpy(info->कुञ्चिका_ids[0], test_कुञ्चिका_id, परिमाण(test_कुञ्चिका_id));
    memcpy(info->कुञ्चिका_ids[1], test_कुञ्चिका_id_2, परिमाण(test_कुञ्चिका_id_2));
    memcpy(info->data, test_data, परिमाण(test_data));

    प्रत्यागम info;
}

स्थिर शून्य run_encryption_init_info_test(शून्य)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_data, *appended;
    size_t side_data_size, appended_size;
    unsigned पूर्णाङ्क allocated_size = 0;

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

पूर्णाङ्क main(पूर्णाङ्क argc, वर्ण **argv)
{
    run_encryption_info_test();
    run_encryption_init_info_test();
    प्रत्यागम 0;
}
