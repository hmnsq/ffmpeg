/**
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

#অন্তর্ভাৱ <string.h>

#অন্তর্ভাৱ "encryption_info.h"
#অন্তর্ভাৱ "error.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "intreadwrite.h"

#define FF_ENCRYPTION_INFO_EXTRA 24

// The format of the AVEncryptionInfo side data:
// u32be scheme
// u32be crypt_byte_block
// u32be skip_byte_block
// u32be key_id_size
// u32be iv_size
// u32be subsample_count
// u8[key_id_size] key_id
// u8[iv_size] iv
// {
//   u32be bytes_of_clear_data
//   u32be bytes_of_protected_data
// }[subsample_count]

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_গুনতি, uint32_t চাবি_id_size, uint32_t iv_size)
{
    AVEncryptionInfo *info;

    info = av_mallocz(পরিমাণ(*info));
    যদি (!info)
        ঘূৰাই রিক্ত;

    info->চাবি_id = av_mallocz(চাবি_id_size);
    info->চাবি_id_size = চাবি_id_size;
    info->iv = av_mallocz(iv_size);
    info->iv_size = iv_size;
    info->subsamples = av_calloc(subsample_গুনতি, পরিমাণ(*info->subsamples));
    info->subsample_গুনতি = subsample_গুনতি;

    // Allow info->subsamples to be NULL if there are no subsamples.
    যদি (!info->চাবি_id || !info->iv || (!info->subsamples && subsample_গুনতি)) {
        av_encryption_info_free(info);
        ঘূৰাই রিক্ত;
    }

    ঘূৰাই info;
}

AVEncryptionInfo *av_encryption_info_clone(ধ্রুৱ AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_গুনতি, info->চাবি_id_size, info->iv_size);
    যদি (!ret)
        ঘূৰাই রিক্ত;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    memcpy(ret->iv, info->iv, info->iv_size);
    memcpy(ret->চাবি_id, info->চাবি_id, info->চাবি_id_size);
    memcpy(ret->subsamples, info->subsamples, পরিমাণ(*info->subsamples) * info->subsample_গুনতি);
    ঘূৰাই ret;
}

শূন্য av_encryption_info_free(AVEncryptionInfo *info)
{
    যদি (info) {
        av_free(info->চাবি_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_data(ধ্রুৱ uint8_t* buffer, size_t size)
{
    AVEncryptionInfo *info;
    uint64_t চাবি_id_size, iv_size, subsample_গুনতি, i;

    যদি (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        ঘূৰাই রিক্ত;

    চাবি_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_গুনতি = AV_RB32(buffer + 20);

    যদি (size < FF_ENCRYPTION_INFO_EXTRA + চাবি_id_size + iv_size + subsample_গুনতি * 8)
        ঘূৰাই রিক্ত;

    info = av_encryption_info_alloc(subsample_গুনতি, চাবি_id_size, iv_size);
    যদি (!info)
        ঘূৰাই রিক্ত;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    memcpy(info->চাবি_id, buffer + 24, চাবি_id_size);
    memcpy(info->iv, buffer + চাবি_id_size + 24, iv_size);

    buffer += চাবি_id_size + iv_size + 24;
    বাবে (i = 0; i < subsample_গুনতি; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    ঘূৰাই info;
}

uint8_t *av_encryption_info_add_side_data(ধ্রুৱ AVEncryptionInfo *info, size_t *size)
{
    uint8_t *buffer, *cur_buffer;
    uint32_t i;

    যদি (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->চাবি_id_size ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->চাবি_id_size < info->iv_size ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->চাবি_id_size - info->iv_size) / 8 < info->subsample_গুনতি) {
        ঘূৰাই রিক্ত;
    }

    *size = FF_ENCRYPTION_INFO_EXTRA + info->চাবি_id_size + info->iv_size +
            (info->subsample_গুনতি * 8);
    cur_buffer = buffer = av_malloc(*size);
    যদি (!buffer)
        ঘূৰাই রিক্ত;

    AV_WB32(cur_buffer,      info->scheme);
    AV_WB32(cur_buffer +  4, info->crypt_byte_block);
    AV_WB32(cur_buffer +  8, info->skip_byte_block);
    AV_WB32(cur_buffer + 12, info->চাবি_id_size);
    AV_WB32(cur_buffer + 16, info->iv_size);
    AV_WB32(cur_buffer + 20, info->subsample_গুনতি);
    cur_buffer += 24;
    memcpy(cur_buffer, info->চাবি_id, info->চাবি_id_size);
    cur_buffer += info->চাবি_id_size;
    memcpy(cur_buffer, info->iv, info->iv_size);
    cur_buffer += info->iv_size;
    বাবে (i = 0; i < info->subsample_গুনতি; i++) {
        AV_WB32(cur_buffer, info->subsamples[i].bytes_of_clear_data);
        AV_WB32(cur_buffer + 4, info->subsamples[i].bytes_of_protected_data);
        cur_buffer += 8;
    }

    ঘূৰাই buffer;
}

// The format of the AVEncryptionInitInfo side data:
// u32be init_info_count
// {
//   u32be system_id_size
//   u32be num_key_ids
//   u32be key_id_size
//   u32be data_size
//   u8[system_id_size] system_id
//   u8[key_id_size][num_key_id] key_ids
//   u8[data_size] data
// }[init_info_count]

#define FF_ENCRYPTION_INIT_INFO_EXTRA 16

AVEncryptionInitInfo *av_encryption_init_info_alloc(
    uint32_t system_id_size, uint32_t অঙ্ক_চাবি_ids, uint32_t চাবি_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    যদি (অঙ্ক_চাবি_ids && !চাবি_id_size)
        ঘূৰাই রিক্ত;

    info = av_mallocz(পরিমাণ(*info));
    যদি (!info)
        ঘূৰাই রিক্ত;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->চাবি_ids = চাবি_id_size ? av_calloc(অঙ্ক_চাবি_ids, পরিমাণ(*info->চাবি_ids)) : রিক্ত;
    info->অঙ্ক_চাবি_ids = অঙ্ক_চাবি_ids;
    info->চাবি_id_size = চাবি_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    যদি ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->চাবি_ids && অঙ্ক_চাবি_ids && চাবি_id_size)) {
        av_encryption_init_info_free(info);
        ঘূৰাই রিক্ত;
    }

    যদি (চাবি_id_size) {
        বাবে (i = 0; i < অঙ্ক_চাবি_ids; i++) {
            info->চাবি_ids[i] = av_mallocz(চাবি_id_size);
            যদি (!info->চাবি_ids[i]) {
                av_encryption_init_info_free(info);
                ঘূৰাই রিক্ত;
            }
        }
    }

    ঘূৰাই info;
}

শূন্য av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    যেতিয়ালৈ (info) {
        AVEncryptionInitInfo *next = info->next;
        uint32_t i;

        বাবে (i = 0; i < info->অঙ্ক_চাবি_ids; i++) {
            av_free(info->চাবি_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->চাবি_ids);
        av_free(info->data);
        av_free(info);

        info = next;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_data(
    ধ্রুৱ uint8_t *side_data, size_t side_data_size)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = রিক্ত, *info, *temp_info;
    uint64_t system_id_size, অঙ্ক_চাবি_ids, চাবি_id_size, data_size, i, j;
    uint64_t init_info_গুনতি;

    যদি (!side_data || side_data_size < 4)
        ঘূৰাই রিক্ত;

    init_info_গুনতি = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    বাবে (i = 0; i < init_info_গুনতি; i++) {
        যদি (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            ঘূৰাই রিক্ত;
        }

        system_id_size = AV_RB32(side_data);
        অঙ্ক_চাবি_ids = AV_RB32(side_data + 4);
        চাবি_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        যদি (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + অঙ্ক_চাবি_ids * চাবি_id_size) {
            av_encryption_init_info_free(ret);
            ঘূৰাই রিক্ত;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, অঙ্ক_চাবি_ids, চাবি_id_size, data_size);
        যদি (!temp_info) {
            av_encryption_init_info_free(ret);
            ঘূৰাই রিক্ত;
        }
        যদি (i == 0) {
            info = ret = temp_info;
        } অন্যথা {
            info->next = temp_info;
            info = temp_info;
        }

        memcpy(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        বাবে (j = 0; j < অঙ্ক_চাবি_ids; j++) {
            memcpy(info->চাবি_ids[j], side_data, চাবি_id_size);
            side_data += চাবি_id_size;
            side_data_size -= চাবি_id_size;
        }
        memcpy(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    ঘূৰাই ret;
}

পূর্ণাঙ্ক av_encryption_init_info_append_side_data(uint8_t **side_data, size_t *side_data_size,
                                             unsigned পূর্ণাঙ্ক *allocated_size,
                                             ধ্রুৱ AVEncryptionInitInfo *info)
{
    ধ্রুৱ AVEncryptionInitInfo *cur_info;
    uint8_t *buffer, *cur_buffer;
    uint32_t i;
    uint64_t init_info_গুনতি    = *side_data ? AV_RB32(*side_data) : 0;
    size_t   old_side_data_size = *side_data ? *side_data_size : 4;
    uint64_t new_side_data_size = old_side_data_size;

    বাবে (cur_info = info; cur_info; cur_info = cur_info->next) {
        new_side_data_size += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_size + cur_info->data_size;
        যদি (init_info_গুনতি == UINT32_MAX || new_side_data_size > UINT32_MAX)
            ঘূৰাই AVERROR(EINVAL);
        init_info_গুনতি++;

        যদি (cur_info->অঙ্ক_চাবি_ids) {
            new_side_data_size += (uint64_t)cur_info->অঙ্ক_চাবি_ids * cur_info->চাবি_id_size;
            যদি (new_side_data_size > UINT32_MAX)
                ঘূৰাই AVERROR(EINVAL);
        }
    }

    buffer = av_fast_realloc(*side_data, allocated_size, new_side_data_size);
    যদি (!buffer)
        ঘূৰাই AVERROR(ENOMEM);

    AV_WB32(buffer, init_info_গুনতি);
    cur_buffer = buffer + old_side_data_size;
    বাবে (cur_info = info; cur_info; cur_info = cur_info->next) {
        AV_WB32(cur_buffer,      cur_info->system_id_size);
        AV_WB32(cur_buffer +  4, cur_info->অঙ্ক_চাবি_ids);
        AV_WB32(cur_buffer +  8, cur_info->চাবি_id_size);
        AV_WB32(cur_buffer + 12, cur_info->data_size);
        cur_buffer += 16;

        memcpy(cur_buffer, cur_info->system_id, cur_info->system_id_size);
        cur_buffer += cur_info->system_id_size;
        বাবে (i = 0; i < cur_info->অঙ্ক_চাবি_ids; i++) {
            memcpy(cur_buffer, cur_info->চাবি_ids[i], cur_info->চাবি_id_size);
            cur_buffer += cur_info->চাবি_id_size;
        }
        যদি (cur_info->data_size > 0) {
            memcpy(cur_buffer, cur_info->data, cur_info->data_size);
            cur_buffer += cur_info->data_size;
        }
    }

    *side_data      = buffer;
    *side_data_size = new_side_data_size;
    ঘূৰাই 0;
}

uint8_t *av_encryption_init_info_add_side_data(ধ্রুৱ AVEncryptionInitInfo *info, size_t *side_data_size)
{
    uint8_t *side_data = রিক্ত;
    unsigned পূর্ণাঙ্ক allocated_size = 0;

    যদি (av_encryption_init_info_append_side_data(&side_data, side_data_size, &allocated_size, info) < 0)
        ঘূৰাই রিক্ত;
    ঘূৰাই side_data;
}
