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

#ଅନ୍ତର୍ଭାଵ "libavutil/encryption_info.h"

#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "libavutil/avassert.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/mem.h"

ସ୍ଥିର ଅଚଳ AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
ସ୍ଥିର ଅଚଳ size_t test_subsample_ଗଣନା = ଆକାର(test_subsamples) / ଆକାର(test_subsamples[0]);
ସ୍ଥିର ଅଚଳ uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
ସ୍ଥିର ଅଚଳ uint8_t test_ଚାବି_id[] = {0x21, 0x22, 0x23, 0x24};
ସ୍ଥିର ଅଚଳ uint8_t test_ଚାବି_id_2[] = {0x31, 0x32, 0x33, 0x34};
ସ୍ଥିର ଅଚଳ uint8_t test_system_id[] = {0x41, 0x42, 0x43};
ସ୍ଥିର ଅଚଳ uint8_t test_data[] = {0x51, 0x52};

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା compare_encryption_info(ଅଚଳ AVEncryptionInfo *a, ଅଚଳ AVEncryptionInfo *b) {
    ଯଦି (!a || !b || a->scheme != b->scheme || a->crypt_byte_block != b->crypt_byte_block ||
        a->skip_byte_block != b->skip_byte_block || a->ଚାବି_id_size != b->ଚାବି_id_size ||
        a->iv_size != b->iv_size || a->subsample_ଗଣନା != b->subsample_ଗଣନା)
        ଫେରନ୍ତୁ 1;

    ଯଦି (memcmp(a->ଚାବି_id, b->ଚାବି_id, a->ଚାବି_id_size) != 0 ||
        memcmp(a->iv, b->iv, a->iv_size) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_ଗଣନା * ଆକାର(a->subsamples[0])))
        ଫେରନ୍ତୁ 1;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା compare_encryption_init_info(ଅଚଳ AVEncryptionInitInfo *a, ଅଚଳ AVEncryptionInitInfo *b) {
    ଯଦି (!a || !b || a->system_id_size != b->system_id_size ||
        a->ଅଙ୍କ_ଚାବି_ids != b->ଅଙ୍କ_ଚାବି_ids || a->ଚାବି_id_size != b->ଚାବି_id_size ||
        a->data_size != b->data_size)
        ଫେରନ୍ତୁ 1;

    ଯଦି (memcmp(a->system_id, b->system_id, a->system_id_size) != 0 ||
        memcmp(a->data, b->data, a->data_size) != 0)
        ଫେରନ୍ତୁ 1;

    ପାଇଁ (uint32_t i = 0; i < a->ଅଙ୍କ_ଚାବି_ids; i++) {
        ଯଦି (memcmp(a->ଚାବି_ids[i], b->ଚାବି_ids[i], a->ଚାବି_id_size) != 0)
            ଫେରନ୍ତୁ 1;
    }

    ଯଦି (a->next || b->next) {
        ଯଦି (!a->next || !b->next)
            ଫେରନ୍ତୁ 1;
        ଯଦି (compare_encryption_init_info(a->next, b->next) != 0)
            ଫେରନ୍ତୁ 1;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ run_encryption_info_test(ଶୂନ୍ୟ)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_data;
    size_t side_data_size;

    info = av_encryption_info_alloc(test_subsample_ଗଣନା, ଆକାର(test_ଚାବି_id), ଆକାର(test_iv));
    av_assert0(info);
    av_assert0(info->ଚାବି_id);
    av_assert0(info->ଚାବି_id_size == ଆକାର(test_ଚାବି_id));
    av_assert0(info->iv);
    av_assert0(info->iv_size == ଆକାର(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_ଗଣନା == test_subsample_ଗଣନା);

    info->scheme = 1234;
    info->crypt_byte_block = 333;
    info->skip_byte_block = 444;
    memcpy(info->ଚାବି_id, test_ଚାବି_id, ଆକାର(test_ଚାବି_id));
    memcpy(info->iv, test_iv, ଆକାର(test_iv));
    memcpy(info->subsamples, test_subsamples, ଆକାର(test_subsamples));

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

ସ୍ଥିର AVEncryptionInitInfo *create_init_info(ଶୂନ୍ୟ)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(ଆକାର(test_system_id), 2, ଆକାର(test_ଚାବି_id), ଆକାର(test_data));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_size == ଆକାର(test_system_id));
    av_assert0(info->ଚାବି_ids);
    av_assert0(info->ଅଙ୍କ_ଚାବି_ids == 2);
    av_assert0(info->ଚାବି_id_size == ଆକାର(test_ଚାବି_id));
    av_assert0(info->ଚାବି_ids[0]);
    av_assert0(info->ଚାବି_ids[1]);
    av_assert0(info->data);
    av_assert0(info->data_size == ଆକାର(test_data));
    av_assert0(!info->next);

    memcpy(info->system_id, test_system_id, ଆକାର(test_system_id));
    memcpy(info->ଚାବି_ids[0], test_ଚାବି_id, ଆକାର(test_ଚାବି_id));
    memcpy(info->ଚାବି_ids[1], test_ଚାବି_id_2, ଆକାର(test_ଚାବି_id_2));
    memcpy(info->data, test_data, ଆକାର(test_data));

    ଫେରନ୍ତୁ info;
}

ସ୍ଥିର ଶୂନ୍ୟ run_encryption_init_info_test(ଶୂନ୍ୟ)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_data, *appended;
    size_t side_data_size, appended_size;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା allocated_size = 0;

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

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc, ଅକ୍ଷର **argv)
{
    run_encryption_info_test();
    run_encryption_init_info_test();
    ଫେରନ୍ତୁ 0;
}
