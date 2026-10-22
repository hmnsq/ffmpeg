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
स्थिर ध्रुव uint8_t test_दत्त[] = {0x51, 0x52};

स्थिर पूर्णाङ्क compare_encryption_info(ध्रुव AVEncryptionInfo *a, ध्रुव AVEncryptionInfo *b) {
    यदि (!a || !b || a->scheme != b->scheme || a->crypt_byte_खण्डम् != b->crypt_byte_खण्डम् ||
        a->skip_byte_खण्डम् != b->skip_byte_खण्डम् || a->कुञ्चिका_id_आकार != b->कुञ्चिका_id_आकार ||
        a->iv_आकार != b->iv_आकार || a->subsample_गणनम् != b->subsample_गणनम्)
        प्रत्यागम 1;

    यदि (memcmp(a->कुञ्चिका_id, b->कुञ्चिका_id, a->कुञ्चिका_id_आकार) != 0 ||
        memcmp(a->iv, b->iv, a->iv_आकार) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_गणनम् * परिमाण(a->subsamples[0])))
        प्रत्यागम 1;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क compare_encryption_init_info(ध्रुव AVEncryptionInitInfo *a, ध्रुव AVEncryptionInitInfo *b) {
    यदि (!a || !b || a->system_id_आकार != b->system_id_आकार ||
        a->अङ्कः_कुञ्चिका_ids != b->अङ्कः_कुञ्चिका_ids || a->कुञ्चिका_id_आकार != b->कुञ्चिका_id_आकार ||
        a->दत्त_आकार != b->दत्त_आकार)
        प्रत्यागम 1;

    यदि (memcmp(a->system_id, b->system_id, a->system_id_आकार) != 0 ||
        memcmp(a->दत्त, b->दत्त, a->दत्त_आकार) != 0)
        प्रत्यागम 1;

    प्रति (uint32_t i = 0; i < a->अङ्कः_कुञ्चिका_ids; i++) {
        यदि (memcmp(a->कुञ्चिका_ids[i], b->कुञ्चिका_ids[i], a->कुञ्चिका_id_आकार) != 0)
            प्रत्यागम 1;
    }

    यदि (a->अग्र || b->अग्र) {
        यदि (!a->अग्र || !b->अग्र)
            प्रत्यागम 1;
        यदि (compare_encryption_init_info(a->अग्र, b->अग्र) != 0)
            प्रत्यागम 1;
    }

    प्रत्यागम 0;
}

स्थिर शून्य सततम्_encryption_info_test(शून्य)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_दत्त;
    size_t side_दत्त_आकार;

    info = av_encryption_info_alloc(test_subsample_गणनम्, परिमाण(test_कुञ्चिका_id), परिमाण(test_iv));
    av_assert0(info);
    av_assert0(info->कुञ्चिका_id);
    av_assert0(info->कुञ्चिका_id_आकार == परिमाण(test_कुञ्चिका_id));
    av_assert0(info->iv);
    av_assert0(info->iv_आकार == परिमाण(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_गणनम् == test_subsample_गणनम्);

    info->scheme = 1234;
    info->crypt_byte_खण्डम् = 333;
    info->skip_byte_खण्डम् = 444;
    स्मृतिं_प्रतिलिख(info->कुञ्चिका_id, test_कुञ्चिका_id, परिमाण(test_कुञ्चिका_id));
    स्मृतिं_प्रतिलिख(info->iv, test_iv, परिमाण(test_iv));
    स्मृतिं_प्रतिलिख(info->subsamples, test_subsamples, परिमाण(test_subsamples));

    copy = av_encryption_info_clone(info);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);

    side_दत्त = av_encryption_info_सङ्कलय_side_दत्त(info, &side_दत्त_आकार);
    av_assert0(side_दत्त);
    av_assert0(side_दत्त_आकार > 0);

    copy = av_encryption_info_get_side_दत्त(side_दत्त, side_दत्त_आकार);
    av_assert0(copy);
    av_assert0(copy != info);
    av_assert0(compare_encryption_info(info, copy) == 0);
    av_encryption_info_free(copy);
    av_free(side_दत्त);

    av_encryption_info_free(info);
}

स्थिर AVEncryptionInitInfo *create_init_info(शून्य)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(परिमाण(test_system_id), 2, परिमाण(test_कुञ्चिका_id), परिमाण(test_दत्त));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_आकार == परिमाण(test_system_id));
    av_assert0(info->कुञ्चिका_ids);
    av_assert0(info->अङ्कः_कुञ्चिका_ids == 2);
    av_assert0(info->कुञ्चिका_id_आकार == परिमाण(test_कुञ्चिका_id));
    av_assert0(info->कुञ्चिका_ids[0]);
    av_assert0(info->कुञ्चिका_ids[1]);
    av_assert0(info->दत्त);
    av_assert0(info->दत्त_आकार == परिमाण(test_दत्त));
    av_assert0(!info->अग्र);

    स्मृतिं_प्रतिलिख(info->system_id, test_system_id, परिमाण(test_system_id));
    स्मृतिं_प्रतिलिख(info->कुञ्चिका_ids[0], test_कुञ्चिका_id, परिमाण(test_कुञ्चिका_id));
    स्मृतिं_प्रतिलिख(info->कुञ्चिका_ids[1], test_कुञ्चिका_id_2, परिमाण(test_कुञ्चिका_id_2));
    स्मृतिं_प्रतिलिख(info->दत्त, test_दत्त, परिमाण(test_दत्त));

    प्रत्यागम info;
}

स्थिर शून्य सततम्_encryption_init_info_test(शून्य)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_दत्त, *appended;
    size_t side_दत्त_आकार, appended_आकार;
    अचिह्नित पूर्णाङ्क allocated_आकार = 0;

    info = create_init_info();

    side_दत्त = av_encryption_init_info_सङ्कलय_side_दत्त(info, &side_दत्त_आकार);
    av_assert0(side_दत्त);
    av_assert0(side_दत्त_आकार > 0);
    copy = av_encryption_init_info_get_side_दत्त(side_दत्त, side_दत्त_आकार);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);
    av_free(side_दत्त);

    // Make the first init info different from the second to test the correct order.
    स्मृतिं_पूरय(info->system_id, 0, info->system_id_आकार);
    appended = av_encryption_init_info_सङ्कलय_side_दत्त(info, &appended_आकार);
    av_assert0(appended);
    info->अग्र = create_init_info();
    side_दत्त = av_encryption_init_info_सङ्कलय_side_दत्त(info, &side_दत्त_आकार);
    av_assert0(side_दत्त);
    copy = av_encryption_init_info_get_side_दत्त(side_दत्त, side_दत्त_आकार);
    av_assert0(copy);
    av_assert0(compare_encryption_init_info(info, copy) == 0);
    av_encryption_init_info_free(copy);

    av_assert0(av_encryption_init_info_append_side_दत्त(&appended, &appended_आकार, &allocated_आकार, info->अग्र) == 0);
    av_assert0(appended_आकार == side_दत्त_आकार);
    av_assert0(memcmp(appended, side_दत्त, side_दत्त_आकार) == 0);
    av_free(appended);
    av_free(side_दत्त);

    av_encryption_init_info_free(info);
}

पूर्णाङ्क मुख्यम्(पूर्णाङ्क argc, वर्ण **argv)
{
    सततम्_encryption_info_test();
    सततम्_encryption_init_info_test();
    प्रत्यागम 0;
}
