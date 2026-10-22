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

स्थिर अचर AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
स्थिर अचर माप_प्रकार test_subsample_गन्ती = परिमाण(test_subsamples) / परिमाण(test_subsamples[0]);
स्थिर अचर uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
स्थिर अचर uint8_t test_साँचो_id[] = {0x21, 0x22, 0x23, 0x24};
स्थिर अचर uint8_t test_साँचो_id_2[] = {0x31, 0x32, 0x33, 0x34};
स्थिर अचर uint8_t test_system_id[] = {0x41, 0x42, 0x43};
स्थिर अचर uint8_t test_data[] = {0x51, 0x52};

स्थिर पूर्णाङ्क compare_encryption_info(अचर AVEncryptionInfo *a, अचर AVEncryptionInfo *b) {
    यदि (!a || !b || a->scheme != b->scheme || a->crypt_byte_block != b->crypt_byte_block ||
        a->skip_byte_block != b->skip_byte_block || a->साँचो_id_size != b->साँचो_id_size ||
        a->iv_size != b->iv_size || a->subsample_गन्ती != b->subsample_गन्ती)
        फर्काऊ 1;

    यदि (स_भेद(a->साँचो_id, b->साँचो_id, a->साँचो_id_size) != 0 ||
        स_भेद(a->iv, b->iv, a->iv_size) != 0 ||
        स_भेद(a->subsamples, b->subsamples, a->subsample_गन्ती * परिमाण(a->subsamples[0])))
        फर्काऊ 1;

    फर्काऊ 0;
}

स्थिर पूर्णाङ्क compare_encryption_init_info(अचर AVEncryptionInitInfo *a, अचर AVEncryptionInitInfo *b) {
    यदि (!a || !b || a->system_id_size != b->system_id_size ||
        a->अङ्क_साँचो_ids != b->अङ्क_साँचो_ids || a->साँचो_id_size != b->साँचो_id_size ||
        a->data_size != b->data_size)
        फर्काऊ 1;

    यदि (स_भेद(a->system_id, b->system_id, a->system_id_size) != 0 ||
        स_भेद(a->data, b->data, a->data_size) != 0)
        फर्काऊ 1;

    लागि (uint32_t i = 0; i < a->अङ्क_साँचो_ids; i++) {
        यदि (स_भेद(a->साँचो_ids[i], b->साँचो_ids[i], a->साँचो_id_size) != 0)
            फर्काऊ 1;
    }

    यदि (a->next || b->next) {
        यदि (!a->next || !b->next)
            फर्काऊ 1;
        यदि (compare_encryption_init_info(a->next, b->next) != 0)
            फर्काऊ 1;
    }

    फर्काऊ 0;
}

स्थिर शून्य run_encryption_info_test(शून्य)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_data;
    माप_प्रकार side_data_size;

    info = av_encryption_info_alloc(test_subsample_गन्ती, परिमाण(test_साँचो_id), परिमाण(test_iv));
    av_assert0(info);
    av_assert0(info->साँचो_id);
    av_assert0(info->साँचो_id_size == परिमाण(test_साँचो_id));
    av_assert0(info->iv);
    av_assert0(info->iv_size == परिमाण(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_गन्ती == test_subsample_गन्ती);

    info->scheme = 1234;
    info->crypt_byte_block = 333;
    info->skip_byte_block = 444;
    स_नकल(info->साँचो_id, test_साँचो_id, परिमाण(test_साँचो_id));
    स_नकल(info->iv, test_iv, परिमाण(test_iv));
    स_नकल(info->subsamples, test_subsamples, परिमाण(test_subsamples));

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

    info = av_encryption_init_info_alloc(परिमाण(test_system_id), 2, परिमाण(test_साँचो_id), परिमाण(test_data));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_size == परिमाण(test_system_id));
    av_assert0(info->साँचो_ids);
    av_assert0(info->अङ्क_साँचो_ids == 2);
    av_assert0(info->साँचो_id_size == परिमाण(test_साँचो_id));
    av_assert0(info->साँचो_ids[0]);
    av_assert0(info->साँचो_ids[1]);
    av_assert0(info->data);
    av_assert0(info->data_size == परिमाण(test_data));
    av_assert0(!info->next);

    स_नकल(info->system_id, test_system_id, परिमाण(test_system_id));
    स_नकल(info->साँचो_ids[0], test_साँचो_id, परिमाण(test_साँचो_id));
    स_नकल(info->साँचो_ids[1], test_साँचो_id_2, परिमाण(test_साँचो_id_2));
    स_नकल(info->data, test_data, परिमाण(test_data));

    फर्काऊ info;
}

स्थिर शून्य run_encryption_init_info_test(शून्य)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_data, *appended;
    माप_प्रकार side_data_size, appended_size;
    अचिन्हित पूर्णाङ्क allocated_size = 0;

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
    स_रखो(info->system_id, 0, info->system_id_size);
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
    av_assert0(स_भेद(appended, side_data, side_data_size) == 0);
    av_free(appended);
    av_free(side_data);

    av_encryption_init_info_free(info);
}

पूर्णाङ्क main(पूर्णाङ्क argc, वर्ण **argv)
{
    run_encryption_info_test();
    run_encryption_init_info_test();
    फर्काऊ 0;
}
