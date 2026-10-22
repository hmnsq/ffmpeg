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

#समावेश "libavutil/encryption_info.h"

#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/avassert.h"
#समावेश "libavutil/mem.h"

अटल स्थिर AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
अटल स्थिर माप_प्रकार test_subsample_गिनती = माप(test_subsamples) / माप(test_subsamples[0]);
अटल स्थिर uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
अटल स्थिर uint8_t test_कुंजी_id[] = {0x21, 0x22, 0x23, 0x24};
अटल स्थिर uint8_t test_कुंजी_id_2[] = {0x31, 0x32, 0x33, 0x34};
अटल स्थिर uint8_t test_system_id[] = {0x41, 0x42, 0x43};
अटल स्थिर uint8_t test_तथ्य[] = {0x51, 0x52};

अटल पूर्णांक compare_encryption_info(स्थिर AVEncryptionInfo *a, स्थिर AVEncryptionInfo *b) {
    अगर (!a || !b || a->scheme != b->scheme || a->crypt_byte_block != b->crypt_byte_block ||
        a->skip_byte_block != b->skip_byte_block || a->कुंजी_id_आकार != b->कुंजी_id_आकार ||
        a->iv_आकार != b->iv_आकार || a->subsample_गिनती != b->subsample_गिनती)
        वापस 1;

    अगर (स_भेद(a->कुंजी_id, b->कुंजी_id, a->कुंजी_id_आकार) != 0 ||
        स_भेद(a->iv, b->iv, a->iv_आकार) != 0 ||
        स_भेद(a->subsamples, b->subsamples, a->subsample_गिनती * माप(a->subsamples[0])))
        वापस 1;

    वापस 0;
}

अटल पूर्णांक compare_encryption_init_info(स्थिर AVEncryptionInitInfo *a, स्थिर AVEncryptionInitInfo *b) {
    अगर (!a || !b || a->system_id_आकार != b->system_id_आकार ||
        a->अंक_कुंजी_ids != b->अंक_कुंजी_ids || a->कुंजी_id_आकार != b->कुंजी_id_आकार ||
        a->तथ्य_आकार != b->तथ्य_आकार)
        वापस 1;

    अगर (स_भेद(a->system_id, b->system_id, a->system_id_आकार) != 0 ||
        स_भेद(a->तथ्य, b->तथ्य, a->तथ्य_आकार) != 0)
        वापस 1;

    क्रम (uint32_t i = 0; i < a->अंक_कुंजी_ids; i++) {
        अगर (स_भेद(a->कुंजी_ids[i], b->कुंजी_ids[i], a->कुंजी_id_आकार) != 0)
            वापस 1;
    }

    अगर (a->अग्र || b->अग्र) {
        अगर (!a->अग्र || !b->अग्र)
            वापस 1;
        अगर (compare_encryption_init_info(a->अग्र, b->अग्र) != 0)
            वापस 1;
    }

    वापस 0;
}

अटल व्योम run_encryption_info_test(व्योम)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_तथ्य;
    माप_प्रकार side_तथ्य_आकार;

    info = av_encryption_info_alloc(test_subsample_गिनती, माप(test_कुंजी_id), माप(test_iv));
    av_assert0(info);
    av_assert0(info->कुंजी_id);
    av_assert0(info->कुंजी_id_आकार == माप(test_कुंजी_id));
    av_assert0(info->iv);
    av_assert0(info->iv_आकार == माप(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_गिनती == test_subsample_गिनती);

    info->scheme = 1234;
    info->crypt_byte_block = 333;
    info->skip_byte_block = 444;
    स_नकल(info->कुंजी_id, test_कुंजी_id, माप(test_कुंजी_id));
    स_नकल(info->iv, test_iv, माप(test_iv));
    स_नकल(info->subsamples, test_subsamples, माप(test_subsamples));

    copy = av_encryption_info_clone(info);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);

    side_तथ्य = av_encryption_info_add_side_तथ्य(info, &side_तथ्य_आकार);
    av_assert0(side_तथ्य);
    av_assert0(side_तथ्य_आकार > 0);

    copy = av_encryption_info_get_side_तथ्य(side_तथ्य, side_तथ्य_आकार);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);
    av_free(side_तथ्य);

    av_encryption_info_free(info);
}

अटल AVEncryptionInitInfo *create_init_info(व्योम)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(माप(test_system_id), 2, माप(test_कुंजी_id), माप(test_तथ्य));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_आकार == माप(test_system_id));
    av_assert0(info->कुंजी_ids);
    av_assert0(info->अंक_कुंजी_ids == 2);
    av_assert0(info->कुंजी_id_आकार == माप(test_कुंजी_id));
    av_assert0(info->कुंजी_ids[0]);
    av_assert0(info->कुंजी_ids[1]);
    av_assert0(info->तथ्य);
    av_assert0(info->तथ्य_आकार == माप(test_तथ्य));
    av_assert0(!info->अग्र);

    स_नकल(info->system_id, test_system_id, माप(test_system_id));
    स_नकल(info->कुंजी_ids[0], test_कुंजी_id, माप(test_कुंजी_id));
    स_नकल(info->कुंजी_ids[1], test_कुंजी_id_2, माप(test_कुंजी_id_2));
    स_नकल(info->तथ्य, test_तथ्य, माप(test_तथ्य));

    वापस info;
}

अटल व्योम run_encryption_init_info_test(व्योम)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_तथ्य, *appended;
    माप_प्रकार side_तथ्य_आकार, appended_आकार;
    अचिन्हित पूर्णांक allocated_आकार = 0;

    info = create_init_info();

    side_तथ्य = av_encryption_init_info_add_side_तथ्य(info, &side_तथ्य_आकार);
    av_assert0(side_तथ्य);
    av_assert0(side_तथ्य_आकार > 0);
    copy = av_encryption_init_info_get_side_तथ्य(side_तथ्य, side_तथ्य_आकार);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);
    av_free(side_तथ्य);

    // Make the first init info different from the second to test the correct order.
    स_रखो(info->system_id, 0, info->system_id_आकार);
    appended = av_encryption_init_info_add_side_तथ्य(info, &appended_आकार);
    av_assert0(appended);
    info->अग्र = create_init_info();
    side_तथ्य = av_encryption_init_info_add_side_तथ्य(info, &side_तथ्य_आकार);
    av_assert0(side_तथ्य);
    copy = av_encryption_init_info_get_side_तथ्य(side_तथ्य, side_तथ्य_आकार);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);

    av_assert0(av_encryption_init_info_append_side_तथ्य(&appended, &appended_आकार, &allocated_आकार, info->अग्र) == 0);
    av_assert0(appended_आकार == side_तथ्य_आकार);
    av_assert0(स_भेद(appended, side_तथ्य, side_तथ्य_आकार) == 0);
    av_free(appended);
    av_free(side_तथ्य);

    av_encryption_init_info_free(info);
}

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
{
    run_encryption_info_test();
    run_encryption_init_info_test();
    वापस 0;
}
