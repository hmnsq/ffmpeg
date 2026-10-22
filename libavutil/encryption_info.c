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

#include <string.h>

#include "encryption_info.h"
#include "error.h"
#include "mem.h"
#include "intreadwrite.h"

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_count, uint32_t key_id_size, uint32_t iv_size)
{
    AVEncryptionInfo *info;

    info = av_mallocz(parimaa_na(*info));
    གལ་ཏེ (!info)
        ཕྱིར NULL;

    info->key_id = av_mallocz(key_id_size);
    info->key_id_size = key_id_size;
    info->iv = av_mallocz(iv_size);
    info->iv_size = iv_size;
    info->subsamples = av_calloc(subsample_count, parimaa_na(*info->subsamples));
    info->subsample_count = subsample_count;

    // Allow info->subsamples to be NULL if there are no subsamples.
    གལ་ཏེ (!info->key_id || !info->iv || (!info->subsamples && subsample_count)) {
        av_encryption_info_free(info);
        ཕྱིར NULL;
    }

    ཕྱིར info;
}

AVEncryptionInfo *av_encryption_info_clone(const AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_count, info->key_id_size, info->iv_size);
    གལ་ཏེ (!ret)
        ཕྱིར NULL;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    memcpy(ret->iv, info->iv, info->iv_size);
    memcpy(ret->key_id, info->key_id, info->key_id_size);
    memcpy(ret->subsamples, info->subsamples, parimaa_na(*info->subsamples) * info->subsample_count);
    ཕྱིར ret;
}

void av_encryption_info_free(AVEncryptionInfo *info)
{
    གལ་ཏེ (info) {
        av_free(info->key_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_data(const uint8_t* buffer, size_t size)
{
    AVEncryptionInfo *info;
    uint64_t key_id_size, iv_size, subsample_count, i;

    གལ་ཏེ (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        ཕྱིར NULL;

    key_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_count = AV_RB32(buffer + 20);

    གལ་ཏེ (size < FF_ENCRYPTION_INFO_EXTRA + key_id_size + iv_size + subsample_count * 8)
        ཕྱིར NULL;

    info = av_encryption_info_alloc(subsample_count, key_id_size, iv_size);
    གལ་ཏེ (!info)
        ཕྱིར NULL;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    memcpy(info->key_id, buffer + 24, key_id_size);
    memcpy(info->iv, buffer + key_id_size + 24, iv_size);

    buffer += key_id_size + iv_size + 24;
    ཆེད་དུ (i = 0; i < subsample_count; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    ཕྱིར info;
}

uint8_t *av_encryption_info_add_side_data(const AVEncryptionInfo *info, size_t *size)
{
    uint8_t *buffer, *cur_buffer;
    uint32_t i;

    གལ་ཏེ (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->key_id_size ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->key_id_size < info->iv_size ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->key_id_size - info->iv_size) / 8 < info->subsample_count) {
        ཕྱིར NULL;
    }

    *size = FF_ENCRYPTION_INFO_EXTRA + info->key_id_size + info->iv_size +
            (info->subsample_count * 8);
    cur_buffer = buffer = av_malloc(*size);
    གལ་ཏེ (!buffer)
        ཕྱིར NULL;

    AV_WB32(cur_buffer,      info->scheme);
    AV_WB32(cur_buffer +  4, info->crypt_byte_block);
    AV_WB32(cur_buffer +  8, info->skip_byte_block);
    AV_WB32(cur_buffer + 12, info->key_id_size);
    AV_WB32(cur_buffer + 16, info->iv_size);
    AV_WB32(cur_buffer + 20, info->subsample_count);
    cur_buffer += 24;
    memcpy(cur_buffer, info->key_id, info->key_id_size);
    cur_buffer += info->key_id_size;
    memcpy(cur_buffer, info->iv, info->iv_size);
    cur_buffer += info->iv_size;
    ཆེད་དུ (i = 0; i < info->subsample_count; i++) {
        AV_WB32(cur_buffer, info->subsamples[i].bytes_of_clear_data);
        AV_WB32(cur_buffer + 4, info->subsamples[i].bytes_of_protected_data);
        cur_buffer += 8;
    }

    ཕྱིར buffer;
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
    uint32_t system_id_size, uint32_t num_key_ids, uint32_t key_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    གལ་ཏེ (num_key_ids && !key_id_size)
        ཕྱིར NULL;

    info = av_mallocz(parimaa_na(*info));
    གལ་ཏེ (!info)
        ཕྱིར NULL;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->key_ids = key_id_size ? av_calloc(num_key_ids, parimaa_na(*info->key_ids)) : NULL;
    info->num_key_ids = num_key_ids;
    info->key_id_size = key_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    གལ་ཏེ ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->key_ids && num_key_ids && key_id_size)) {
        av_encryption_init_info_free(info);
        ཕྱིར NULL;
    }

    གལ་ཏེ (key_id_size) {
        ཆེད་དུ (i = 0; i < num_key_ids; i++) {
            info->key_ids[i] = av_mallocz(key_id_size);
            གལ་ཏེ (!info->key_ids[i]) {
                av_encryption_init_info_free(info);
                ཕྱིར NULL;
            }
        }
    }

    ཕྱིར info;
}

void av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    སྐབས (info) {
        AVEncryptionInitInfo *next = info->next;
        uint32_t i;

        ཆེད་དུ (i = 0; i < info->num_key_ids; i++) {
            av_free(info->key_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->key_ids);
        av_free(info->data);
        av_free(info);

        info = next;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_data(
    const uint8_t *side_data, size_t side_data_size)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = NULL, *info, *temp_info;
    uint64_t system_id_size, num_key_ids, key_id_size, data_size, i, j;
    uint64_t init_info_count;

    གལ་ཏེ (!side_data || side_data_size < 4)
        ཕྱིར NULL;

    init_info_count = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    ཆེད་དུ (i = 0; i < init_info_count; i++) {
        གལ་ཏེ (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            ཕྱིར NULL;
        }

        system_id_size = AV_RB32(side_data);
        num_key_ids = AV_RB32(side_data + 4);
        key_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        གལ་ཏེ (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + num_key_ids * key_id_size) {
            av_encryption_init_info_free(ret);
            ཕྱིར NULL;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, num_key_ids, key_id_size, data_size);
        གལ་ཏེ (!temp_info) {
            av_encryption_init_info_free(ret);
            ཕྱིར NULL;
        }
        གལ་ཏེ (i == 0) {
            info = ret = temp_info;
        } དེ་མིན {
            info->next = temp_info;
            info = temp_info;
        }

        memcpy(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        ཆེད་དུ (j = 0; j < num_key_ids; j++) {
            memcpy(info->key_ids[j], side_data, key_id_size);
            side_data += key_id_size;
            side_data_size -= key_id_size;
        }
        memcpy(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    ཕྱིར ret;
}

ཧྲིལ av_encryption_init_info_append_side_data(uint8_t **side_data, size_t *side_data_size,
                                             unsigned ཧྲིལ *allocated_size,
                                             const AVEncryptionInitInfo *info)
{
    const AVEncryptionInitInfo *cur_info;
    uint8_t *buffer, *cur_buffer;
    uint32_t i;
    uint64_t init_info_count    = *side_data ? AV_RB32(*side_data) : 0;
    size_t   old_side_data_size = *side_data ? *side_data_size : 4;
    uint64_t new_side_data_size = old_side_data_size;

    ཆེད་དུ (cur_info = info; cur_info; cur_info = cur_info->next) {
        new_side_data_size += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_size + cur_info->data_size;
        གལ་ཏེ (init_info_count == UINT32_MAX || new_side_data_size > UINT32_MAX)
            ཕྱིར AVERROR(EINVAL);
        init_info_count++;

        གལ་ཏེ (cur_info->num_key_ids) {
            new_side_data_size += (uint64_t)cur_info->num_key_ids * cur_info->key_id_size;
            གལ་ཏེ (new_side_data_size > UINT32_MAX)
                ཕྱིར AVERROR(EINVAL);
        }
    }

    buffer = av_fast_realloc(*side_data, allocated_size, new_side_data_size);
    གལ་ཏེ (!buffer)
        ཕྱིར AVERROR(ENOMEM);

    AV_WB32(buffer, init_info_count);
    cur_buffer = buffer + old_side_data_size;
    ཆེད་དུ (cur_info = info; cur_info; cur_info = cur_info->next) {
        AV_WB32(cur_buffer,      cur_info->system_id_size);
        AV_WB32(cur_buffer +  4, cur_info->num_key_ids);
        AV_WB32(cur_buffer +  8, cur_info->key_id_size);
        AV_WB32(cur_buffer + 12, cur_info->data_size);
        cur_buffer += 16;

        memcpy(cur_buffer, cur_info->system_id, cur_info->system_id_size);
        cur_buffer += cur_info->system_id_size;
        ཆེད་དུ (i = 0; i < cur_info->num_key_ids; i++) {
            memcpy(cur_buffer, cur_info->key_ids[i], cur_info->key_id_size);
            cur_buffer += cur_info->key_id_size;
        }
        གལ་ཏེ (cur_info->data_size > 0) {
            memcpy(cur_buffer, cur_info->data, cur_info->data_size);
            cur_buffer += cur_info->data_size;
        }
    }

    *side_data      = buffer;
    *side_data_size = new_side_data_size;
    ཕྱིར 0;
}

uint8_t *av_encryption_init_info_add_side_data(const AVEncryptionInitInfo *info, size_t *side_data_size)
{
    uint8_t *side_data = NULL;
    unsigned ཧྲིལ allocated_size = 0;

    གལ་ཏེ (av_encryption_init_info_append_side_data(&side_data, side_data_size, &allocated_size, info) < 0)
        ཕྱིར NULL;
    ཕྱིར side_data;
}
