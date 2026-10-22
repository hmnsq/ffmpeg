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

#include "libavutil/encryption_info.h"

#include <stdio.h>
#include <string.h>

#include "libavutil/avassert.h"
#include "libavutil/mem.h"

static const AVSubsampleEncryptionInfo test_subsamples[] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
static const size_t test_subsample_बिलांग = sizeof(test_subsamples) / sizeof(test_subsamples[0]);
static const uint8_t test_iv[] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
static const uint8_t test_सुसि_id[] = {0x21, 0x22, 0x23, 0x24};
static const uint8_t test_सुसि_id_2[] = {0x31, 0x32, 0x33, 0x34};
static const uint8_t test_system_id[] = {0x41, 0x42, 0x43};
static const uint8_t test_data[] = {0x51, 0x52};

static int compare_encryption_info(const AVEncryptionInfo *a, const AVEncryptionInfo *b) {
    if (!a || !b || a->scheme != b->scheme || a->crypt_byte_block != b->crypt_byte_block ||
        a->skip_byte_block != b->skip_byte_block || a->सुसि_id_size != b->सुसि_id_size ||
        a->iv_size != b->iv_size || a->subsample_बिलांग != b->subsample_बिलांग)
        return 1;

    if (memcmp(a->सुसि_id, b->सुसि_id, a->सुसि_id_size) != 0 ||
        memcmp(a->iv, b->iv, a->iv_size) != 0 ||
        memcmp(a->subsamples, b->subsamples, a->subsample_बिलांग * sizeof(a->subsamples[0])))
        return 1;

    return 0;
}

static int compare_encryption_init_info(const AVEncryptionInitInfo *a, const AVEncryptionInitInfo *b) {
    if (!a || !b || a->system_id_size != b->system_id_size ||
        a->नुमेरो_सुसि_ids != b->नुमेरो_सुसि_ids || a->सुसि_id_size != b->सुसि_id_size ||
        a->data_size != b->data_size)
        return 1;

    if (memcmp(a->system_id, b->system_id, a->system_id_size) != 0 ||
        memcmp(a->data, b->data, a->data_size) != 0)
        return 1;

    for (uint32_t i = 0; i < a->नुमेरो_सुसि_ids; i++) {
        if (memcmp(a->सुसि_ids[i], b->सुसि_ids[i], a->सुसि_id_size) != 0)
            return 1;
    }

    if (a->next || b->next) {
        if (!a->next || !b->next)
            return 1;
        if (compare_encryption_init_info(a->next, b->next) != 0)
            return 1;
    }

    return 0;
}

static void run_encryption_info_test(void)
{
    AVEncryptionInfo *info, *copy;
    uint8_t *side_data;
    size_t side_data_size;

    info = av_encryption_info_alloc(test_subsample_बिलांग, sizeof(test_सुसि_id), sizeof(test_iv));
    av_assert0(info);
    av_assert0(info->सुसि_id);
    av_assert0(info->सुसि_id_size == sizeof(test_सुसि_id));
    av_assert0(info->iv);
    av_assert0(info->iv_size == sizeof(test_iv));
    av_assert0(info->subsamples);
    av_assert0(info->subsample_बिलांग == test_subsample_बिलांग);

    info->scheme = 1234;
    info->crypt_byte_block = 333;
    info->skip_byte_block = 444;
    memcpy(info->सुसि_id, test_सुसि_id, sizeof(test_सुसि_id));
    memcpy(info->iv, test_iv, sizeof(test_iv));
    memcpy(info->subsamples, test_subsamples, sizeof(test_subsamples));

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

static AVEncryptionInitInfo *create_init_info(void)
{
    AVEncryptionInitInfo *info;

    info = av_encryption_init_info_alloc(sizeof(test_system_id), 2, sizeof(test_सुसि_id), sizeof(test_data));
    av_assert0(info);
    av_assert0(info->system_id);
    av_assert0(info->system_id_size == sizeof(test_system_id));
    av_assert0(info->सुसि_ids);
    av_assert0(info->नुमेरो_सुसि_ids == 2);
    av_assert0(info->सुसि_id_size == sizeof(test_सुसि_id));
    av_assert0(info->सुसि_ids[0]);
    av_assert0(info->सुसि_ids[1]);
    av_assert0(info->data);
    av_assert0(info->data_size == sizeof(test_data));
    av_assert0(!info->next);

    memcpy(info->system_id, test_system_id, sizeof(test_system_id));
    memcpy(info->सुसि_ids[0], test_सुसि_id, sizeof(test_सुसि_id));
    memcpy(info->सुसि_ids[1], test_सुसि_id_2, sizeof(test_सुसि_id_2));
    memcpy(info->data, test_data, sizeof(test_data));

    return info;
}

static void run_encryption_init_info_test(void)
{
    AVEncryptionInitInfo *info, *copy;
    uint8_t *side_data, *appended;
    size_t side_data_size, appended_size;
    unsigned int allocated_size = 0;

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

int main(int argc, char **argv)
{
    run_encryption_info_test();
    run_encryption_init_info_test();
    return 0;
}
