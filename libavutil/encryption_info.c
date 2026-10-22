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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_बिलांग, uint32_t सुसि_id_size, uint32_t iv_size)
{
    AVEncryptionInfo *info;

    info = av_mallocz(sizeof(*info));
    if (!info)
        return NULL;

    info->सुसि_id = av_mallocz(सुसि_id_size);
    info->सुसि_id_size = सुसि_id_size;
    info->iv = av_mallocz(iv_size);
    info->iv_size = iv_size;
    info->subsamples = av_calloc(subsample_बिलांग, sizeof(*info->subsamples));
    info->subsample_बिलांग = subsample_बिलांग;

    // Allow info->subsamples to be NULL if there are no subsamples.
    if (!info->सुसि_id || !info->iv || (!info->subsamples && subsample_बिलांग)) {
        av_encryption_info_free(info);
        return NULL;
    }

    return info;
}

AVEncryptionInfo *av_encryption_info_clone(const AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_बिलांग, info->सुसि_id_size, info->iv_size);
    if (!ret)
        return NULL;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    memcpy(ret->iv, info->iv, info->iv_size);
    memcpy(ret->सुसि_id, info->सुसि_id, info->सुसि_id_size);
    memcpy(ret->subsamples, info->subsamples, sizeof(*info->subsamples) * info->subsample_बिलांग);
    return ret;
}

void av_encryption_info_free(AVEncryptionInfo *info)
{
    if (info) {
        av_free(info->सुसि_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_data(const uint8_t* buffer, size_t size)
{
    AVEncryptionInfo *info;
    uint64_t सुसि_id_size, iv_size, subsample_बिलांग, i;

    if (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        return NULL;

    सुसि_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_बिलांग = AV_RB32(buffer + 20);

    if (size < FF_ENCRYPTION_INFO_EXTRA + सुसि_id_size + iv_size + subsample_बिलांग * 8)
        return NULL;

    info = av_encryption_info_alloc(subsample_बिलांग, सुसि_id_size, iv_size);
    if (!info)
        return NULL;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    memcpy(info->सुसि_id, buffer + 24, सुसि_id_size);
    memcpy(info->iv, buffer + सुसि_id_size + 24, iv_size);

    buffer += सुसि_id_size + iv_size + 24;
    for (i = 0; i < subsample_बिलांग; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    return info;
}

uint8_t *av_encryption_info_add_side_data(const AVEncryptionInfo *info, size_t *size)
{
    uint8_t *buffer, *cur_buffer;
    uint32_t i;

    if (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->सुसि_id_size ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->सुसि_id_size < info->iv_size ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->सुसि_id_size - info->iv_size) / 8 < info->subsample_बिलांग) {
        return NULL;
    }

    *size = FF_ENCRYPTION_INFO_EXTRA + info->सुसि_id_size + info->iv_size +
            (info->subsample_बिलांग * 8);
    cur_buffer = buffer = av_malloc(*size);
    if (!buffer)
        return NULL;

    AV_WB32(cur_buffer,      info->scheme);
    AV_WB32(cur_buffer +  4, info->crypt_byte_block);
    AV_WB32(cur_buffer +  8, info->skip_byte_block);
    AV_WB32(cur_buffer + 12, info->सुसि_id_size);
    AV_WB32(cur_buffer + 16, info->iv_size);
    AV_WB32(cur_buffer + 20, info->subsample_बिलांग);
    cur_buffer += 24;
    memcpy(cur_buffer, info->सुसि_id, info->सुसि_id_size);
    cur_buffer += info->सुसि_id_size;
    memcpy(cur_buffer, info->iv, info->iv_size);
    cur_buffer += info->iv_size;
    for (i = 0; i < info->subsample_बिलांग; i++) {
        AV_WB32(cur_buffer, info->subsamples[i].bytes_of_clear_data);
        AV_WB32(cur_buffer + 4, info->subsamples[i].bytes_of_protected_data);
        cur_buffer += 8;
    }

    return buffer;
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
    uint32_t system_id_size, uint32_t नुमेरो_सुसि_ids, uint32_t सुसि_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    if (नुमेरो_सुसि_ids && !सुसि_id_size)
        return NULL;

    info = av_mallocz(sizeof(*info));
    if (!info)
        return NULL;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->सुसि_ids = सुसि_id_size ? av_calloc(नुमेरो_सुसि_ids, sizeof(*info->सुसि_ids)) : NULL;
    info->नुमेरो_सुसि_ids = नुमेरो_सुसि_ids;
    info->सुसि_id_size = सुसि_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    if ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->सुसि_ids && नुमेरो_सुसि_ids && सुसि_id_size)) {
        av_encryption_init_info_free(info);
        return NULL;
    }

    if (सुसि_id_size) {
        for (i = 0; i < नुमेरो_सुसि_ids; i++) {
            info->सुसि_ids[i] = av_mallocz(सुसि_id_size);
            if (!info->सुसि_ids[i]) {
                av_encryption_init_info_free(info);
                return NULL;
            }
        }
    }

    return info;
}

void av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    while (info) {
        AVEncryptionInitInfo *next = info->next;
        uint32_t i;

        for (i = 0; i < info->नुमेरो_सुसि_ids; i++) {
            av_free(info->सुसि_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->सुसि_ids);
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
    uint64_t system_id_size, नुमेरो_सुसि_ids, सुसि_id_size, data_size, i, j;
    uint64_t init_info_बिलांग;

    if (!side_data || side_data_size < 4)
        return NULL;

    init_info_बिलांग = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    for (i = 0; i < init_info_बिलांग; i++) {
        if (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            return NULL;
        }

        system_id_size = AV_RB32(side_data);
        नुमेरो_सुसि_ids = AV_RB32(side_data + 4);
        सुसि_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        if (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + नुमेरो_सुसि_ids * सुसि_id_size) {
            av_encryption_init_info_free(ret);
            return NULL;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, नुमेरो_सुसि_ids, सुसि_id_size, data_size);
        if (!temp_info) {
            av_encryption_init_info_free(ret);
            return NULL;
        }
        if (i == 0) {
            info = ret = temp_info;
        } else {
            info->next = temp_info;
            info = temp_info;
        }

        memcpy(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        for (j = 0; j < नुमेरो_सुसि_ids; j++) {
            memcpy(info->सुसि_ids[j], side_data, सुसि_id_size);
            side_data += सुसि_id_size;
            side_data_size -= सुसि_id_size;
        }
        memcpy(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    return ret;
}

int av_encryption_init_info_append_side_data(uint8_t **side_data, size_t *side_data_size,
                                             unsigned int *allocated_size,
                                             const AVEncryptionInitInfo *info)
{
    const AVEncryptionInitInfo *cur_info;
    uint8_t *buffer, *cur_buffer;
    uint32_t i;
    uint64_t init_info_बिलांग    = *side_data ? AV_RB32(*side_data) : 0;
    size_t   old_side_data_size = *side_data ? *side_data_size : 4;
    uint64_t new_side_data_size = old_side_data_size;

    for (cur_info = info; cur_info; cur_info = cur_info->next) {
        new_side_data_size += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_size + cur_info->data_size;
        if (init_info_बिलांग == UINT32_MAX || new_side_data_size > UINT32_MAX)
            return AVERROR(EINVAL);
        init_info_बिलांग++;

        if (cur_info->नुमेरो_सुसि_ids) {
            new_side_data_size += (uint64_t)cur_info->नुमेरो_सुसि_ids * cur_info->सुसि_id_size;
            if (new_side_data_size > UINT32_MAX)
                return AVERROR(EINVAL);
        }
    }

    buffer = av_fast_realloc(*side_data, allocated_size, new_side_data_size);
    if (!buffer)
        return AVERROR(ENOMEM);

    AV_WB32(buffer, init_info_बिलांग);
    cur_buffer = buffer + old_side_data_size;
    for (cur_info = info; cur_info; cur_info = cur_info->next) {
        AV_WB32(cur_buffer,      cur_info->system_id_size);
        AV_WB32(cur_buffer +  4, cur_info->नुमेरो_सुसि_ids);
        AV_WB32(cur_buffer +  8, cur_info->सुसि_id_size);
        AV_WB32(cur_buffer + 12, cur_info->data_size);
        cur_buffer += 16;

        memcpy(cur_buffer, cur_info->system_id, cur_info->system_id_size);
        cur_buffer += cur_info->system_id_size;
        for (i = 0; i < cur_info->नुमेरो_सुसि_ids; i++) {
            memcpy(cur_buffer, cur_info->सुसि_ids[i], cur_info->सुसि_id_size);
            cur_buffer += cur_info->सुसि_id_size;
        }
        if (cur_info->data_size > 0) {
            memcpy(cur_buffer, cur_info->data, cur_info->data_size);
            cur_buffer += cur_info->data_size;
        }
    }

    *side_data      = buffer;
    *side_data_size = new_side_data_size;
    return 0;
}

uint8_t *av_encryption_init_info_add_side_data(const AVEncryptionInitInfo *info, size_t *side_data_size)
{
    uint8_t *side_data = NULL;
    unsigned int allocated_size = 0;

    if (av_encryption_init_info_append_side_data(&side_data, side_data_size, &allocated_size, info) < 0)
        return NULL;
    return side_data;
}
