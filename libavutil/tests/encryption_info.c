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

#അന്തര്ഭാവ "libavutil/encryption_info.h"

#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "libavutil/avassert.h"
#അന്തര്ഭാവ "libavutil/mem.h"

സ്ഥിതം സ്ഥിരം AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
സ്ഥിതം സ്ഥിരം size_t test_subsample_എണ്ണം = വലുപ്പം(test_subsamples) / വലുപ്പം(test_subsamples[0]);
സ്ഥിതം സ്ഥിരം uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
സ്ഥിതം സ്ഥിരം uint8_t test_താക്കോൽ_id[] = {0x21, 0x22, 0x23, 0x24};
സ്ഥിതം സ്ഥിരം uint8_t test_താക്കോൽ_id_2[] = {0x31, 0x32, 0x33, 0x34};
സ്ഥിതം സ്ഥിരം uint8_t test_system_id[] = {0x41, 0x42, 0x43};
സ്ഥിതം സ്ഥിരം uint8_t test_data[] = {0x51, 0x52};

സ്ഥിതം പൂർണ്ണസംഖ്യ compare_encryption_info(സ്ഥിരം AVEncryptionInfo *a, സ്ഥിരം AVEncryptionInfo *b) {
    എങ്കിൽ (!a || !b || a->scheme != b->scheme || a->crypt_byte_block != b->crypt_byte_block ||
        a->skip_byte_block != b->skip_byte_block || a->താക്കോൽ_id_size != b->താക്കോൽ_id_size ||
        a->iv_size != b->iv_size || a->subsample_എണ്ണം != b->subsample_എണ്ണം)
        തിരികെ 1;

    എങ്കിൽ (memcmp(a->താക്കോൽ_id, b->താക്കോൽ_id, a->താക്കോൽ_id_size) != 0 ||
        memcmp(a->iv, b->iv, a->iv_size) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_എണ്ണം * വലുപ്പം(a->subsamples[0])))
        തിരികെ 1;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ compare_encryption_init_info(സ്ഥിരം AVEncryptionInitInfo *a, സ്ഥിരം AVEncryptionInitInfo *b) {
    എങ്കിൽ (!a || !b || a->system_id_size != b->system_id_size ||
        a->അക്കം_താക്കോൽ_ids != b->അക്കം_താക്കോൽ_ids || a->താക്കോൽ_id_size != b->താക്കോൽ_id_size ||
        a->data_size != b->data_size)
        തിരികെ 1;

    എങ്കിൽ (memcmp(a->system_id, b->system_id, a->system_id_size) != 0 ||
        memcmp(a->data, b->data, a->data_size) != 0)
        തിരികെ 1;

    വേണ്ടി (uint32_t i = 0; i < a->അക്കം_താക്കോൽ_ids; i++) {
        എങ്കിൽ (memcmp(a->താക്കോൽ_ids[i], b->താക്കോൽ_ids[i], a->താക്കോൽ_id_size) != 0)
            തിരികെ 1;
    }

    എങ്കിൽ (a->next || b->next) {
        എങ്കിൽ (!a->next || !b->next)
            തിരികെ 1;
        എങ്കിൽ (compare_encryption_init_info(a->next, b->next) != 0)
            തിരികെ 1;
    }

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം run_encryption_info_test(ശൂന്യം)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_data;
    size_t side_data_size;

    info = av_encryption_info_alloc(test_subsample_എണ്ണം, വലുപ്പം(test_താക്കോൽ_id), വലുപ്പം(test_iv));
    av_assert0(info);
    av_assert0(info->താക്കോൽ_id);
    av_assert0(info->താക്കോൽ_id_size == വലുപ്പം(test_താക്കോൽ_id));
    av_assert0(info->iv);
    av_assert0(info->iv_size == വലുപ്പം(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_എണ്ണം == test_subsample_എണ്ണം);

    info->scheme = 1234;
    info->crypt_byte_block = 333;
    info->skip_byte_block = 444;
    memcpy(info->താക്കോൽ_id, test_താക്കോൽ_id, വലുപ്പം(test_താക്കോൽ_id));
    memcpy(info->iv, test_iv, വലുപ്പം(test_iv));
    memcpy(info->subsamples, test_subsamples, വലുപ്പം(test_subsamples));

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

സ്ഥിതം AVEncryptionInitInfo *create_init_info(ശൂന്യം)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(വലുപ്പം(test_system_id), 2, വലുപ്പം(test_താക്കോൽ_id), വലുപ്പം(test_data));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_size == വലുപ്പം(test_system_id));
    av_assert0(info->താക്കോൽ_ids);
    av_assert0(info->അക്കം_താക്കോൽ_ids == 2);
    av_assert0(info->താക്കോൽ_id_size == വലുപ്പം(test_താക്കോൽ_id));
    av_assert0(info->താക്കോൽ_ids[0]);
    av_assert0(info->താക്കോൽ_ids[1]);
    av_assert0(info->data);
    av_assert0(info->data_size == വലുപ്പം(test_data));
    av_assert0(!info->next);

    memcpy(info->system_id, test_system_id, വലുപ്പം(test_system_id));
    memcpy(info->താക്കോൽ_ids[0], test_താക്കോൽ_id, വലുപ്പം(test_താക്കോൽ_id));
    memcpy(info->താക്കോൽ_ids[1], test_താക്കോൽ_id_2, വലുപ്പം(test_താക്കോൽ_id_2));
    memcpy(info->data, test_data, വലുപ്പം(test_data));

    തിരികെ info;
}

സ്ഥിതം ശൂന്യം run_encryption_init_info_test(ശൂന്യം)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_data, *appended;
    size_t side_data_size, appended_size;
    unsigned പൂർണ്ണസംഖ്യ allocated_size = 0;

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

പൂർണ്ണസംഖ്യ പ്രധാന(പൂർണ്ണസംഖ്യ argc, അക്ഷരം **argv)
{
    run_encryption_info_test();
    run_encryption_init_info_test();
    തിരികെ 0;
}
