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

#அந்தர்பாவ <string.h>

#அந்தர்பாவ "encryption_info.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "intreadwrite.h"

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_மொத்தம், uint32_t சாவி_id_size, uint32_t iv_size)
{
    AVEncryptionInfo *info;

    info = av_mallocz(அளவு(*info));
    எனில் (!info)
        திரும்பு வெற்று;

    info->சாவி_id = av_mallocz(சாவி_id_size);
    info->சாவி_id_size = சாவி_id_size;
    info->iv = av_mallocz(iv_size);
    info->iv_size = iv_size;
    info->subsamples = av_calloc(subsample_மொத்தம், அளவு(*info->subsamples));
    info->subsample_மொத்தம் = subsample_மொத்தம்;

    // Allow info->subsamples to be NULL if there are no subsamples.
    எனில் (!info->சாவி_id || !info->iv || (!info->subsamples && subsample_மொத்தம்)) {
        av_encryption_info_free(info);
        திரும்பு வெற்று;
    }

    திரும்பு info;
}

AVEncryptionInfo *av_encryption_info_clone(மாறிலி AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_மொத்தம், info->சாவி_id_size, info->iv_size);
    எனில் (!ret)
        திரும்பு வெற்று;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    memcpy(ret->iv, info->iv, info->iv_size);
    memcpy(ret->சாவி_id, info->சாவி_id, info->சாவி_id_size);
    memcpy(ret->subsamples, info->subsamples, அளவு(*info->subsamples) * info->subsample_மொத்தம்);
    திரும்பு ret;
}

வெறுமை av_encryption_info_free(AVEncryptionInfo *info)
{
    எனில் (info) {
        av_free(info->சாவி_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_data(மாறிலி uint8_t* buffer, size_t size)
{
    AVEncryptionInfo *info;
    uint64_t சாவி_id_size, iv_size, subsample_மொத்தம், i;

    எனில் (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        திரும்பு வெற்று;

    சாவி_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_மொத்தம் = AV_RB32(buffer + 20);

    எனில் (size < FF_ENCRYPTION_INFO_EXTRA + சாவி_id_size + iv_size + subsample_மொத்தம் * 8)
        திரும்பு வெற்று;

    info = av_encryption_info_alloc(subsample_மொத்தம், சாவி_id_size, iv_size);
    எனில் (!info)
        திரும்பு வெற்று;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    memcpy(info->சாவி_id, buffer + 24, சாவி_id_size);
    memcpy(info->iv, buffer + சாவி_id_size + 24, iv_size);

    buffer += சாவி_id_size + iv_size + 24;
    க்கு (i = 0; i < subsample_மொத்தம்; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    திரும்பு info;
}

uint8_t *av_encryption_info_add_side_data(மாறிலி AVEncryptionInfo *info, size_t *size)
{
    uint8_t *buffer, *cur_buffer;
    uint32_t i;

    எனில் (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->சாவி_id_size ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->சாவி_id_size < info->iv_size ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->சாவி_id_size - info->iv_size) / 8 < info->subsample_மொத்தம்) {
        திரும்பு வெற்று;
    }

    *size = FF_ENCRYPTION_INFO_EXTRA + info->சாவி_id_size + info->iv_size +
            (info->subsample_மொத்தம் * 8);
    cur_buffer = buffer = av_malloc(*size);
    எனில் (!buffer)
        திரும்பு வெற்று;

    AV_WB32(cur_buffer,      info->scheme);
    AV_WB32(cur_buffer +  4, info->crypt_byte_block);
    AV_WB32(cur_buffer +  8, info->skip_byte_block);
    AV_WB32(cur_buffer + 12, info->சாவி_id_size);
    AV_WB32(cur_buffer + 16, info->iv_size);
    AV_WB32(cur_buffer + 20, info->subsample_மொத்தம்);
    cur_buffer += 24;
    memcpy(cur_buffer, info->சாவி_id, info->சாவி_id_size);
    cur_buffer += info->சாவி_id_size;
    memcpy(cur_buffer, info->iv, info->iv_size);
    cur_buffer += info->iv_size;
    க்கு (i = 0; i < info->subsample_மொத்தம்; i++) {
        AV_WB32(cur_buffer, info->subsamples[i].bytes_of_clear_data);
        AV_WB32(cur_buffer + 4, info->subsamples[i].bytes_of_protected_data);
        cur_buffer += 8;
    }

    திரும்பு buffer;
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
    uint32_t system_id_size, uint32_t இலக்கம்_சாவி_ids, uint32_t சாவி_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    எனில் (இலக்கம்_சாவி_ids && !சாவி_id_size)
        திரும்பு வெற்று;

    info = av_mallocz(அளவு(*info));
    எனில் (!info)
        திரும்பு வெற்று;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->சாவி_ids = சாவி_id_size ? av_calloc(இலக்கம்_சாவி_ids, அளவு(*info->சாவி_ids)) : வெற்று;
    info->இலக்கம்_சாவி_ids = இலக்கம்_சாவி_ids;
    info->சாவி_id_size = சாவி_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    எனில் ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->சாவி_ids && இலக்கம்_சாவி_ids && சாவி_id_size)) {
        av_encryption_init_info_free(info);
        திரும்பு வெற்று;
    }

    எனில் (சாவி_id_size) {
        க்கு (i = 0; i < இலக்கம்_சாவி_ids; i++) {
            info->சாவி_ids[i] = av_mallocz(சாவி_id_size);
            எனில் (!info->சாவி_ids[i]) {
                av_encryption_init_info_free(info);
                திரும்பு வெற்று;
            }
        }
    }

    திரும்பு info;
}

வெறுமை av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    போது (info) {
        AVEncryptionInitInfo *next = info->next;
        uint32_t i;

        க்கு (i = 0; i < info->இலக்கம்_சாவி_ids; i++) {
            av_free(info->சாவி_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->சாவி_ids);
        av_free(info->data);
        av_free(info);

        info = next;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_data(
    மாறிலி uint8_t *side_data, size_t side_data_size)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = வெற்று, *info, *temp_info;
    uint64_t system_id_size, இலக்கம்_சாவி_ids, சாவி_id_size, data_size, i, j;
    uint64_t init_info_மொத்தம்;

    எனில் (!side_data || side_data_size < 4)
        திரும்பு வெற்று;

    init_info_மொத்தம் = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    க்கு (i = 0; i < init_info_மொத்தம்; i++) {
        எனில் (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            திரும்பு வெற்று;
        }

        system_id_size = AV_RB32(side_data);
        இலக்கம்_சாவி_ids = AV_RB32(side_data + 4);
        சாவி_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        எனில் (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + இலக்கம்_சாவி_ids * சாவி_id_size) {
            av_encryption_init_info_free(ret);
            திரும்பு வெற்று;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, இலக்கம்_சாவி_ids, சாவி_id_size, data_size);
        எனில் (!temp_info) {
            av_encryption_init_info_free(ret);
            திரும்பு வெற்று;
        }
        எனில் (i == 0) {
            info = ret = temp_info;
        } இல்லையெனில் {
            info->next = temp_info;
            info = temp_info;
        }

        memcpy(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        க்கு (j = 0; j < இலக்கம்_சாவி_ids; j++) {
            memcpy(info->சாவி_ids[j], side_data, சாவி_id_size);
            side_data += சாவி_id_size;
            side_data_size -= சாவி_id_size;
        }
        memcpy(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    திரும்பு ret;
}

முழு av_encryption_init_info_append_side_data(uint8_t **side_data, size_t *side_data_size,
                                             unsigned முழு *allocated_size,
                                             மாறிலி AVEncryptionInitInfo *info)
{
    மாறிலி AVEncryptionInitInfo *cur_info;
    uint8_t *buffer, *cur_buffer;
    uint32_t i;
    uint64_t init_info_மொத்தம்    = *side_data ? AV_RB32(*side_data) : 0;
    size_t   old_side_data_size = *side_data ? *side_data_size : 4;
    uint64_t new_side_data_size = old_side_data_size;

    க்கு (cur_info = info; cur_info; cur_info = cur_info->next) {
        new_side_data_size += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_size + cur_info->data_size;
        எனில் (init_info_மொத்தம் == UINT32_MAX || new_side_data_size > UINT32_MAX)
            திரும்பு AVERROR(EINVAL);
        init_info_மொத்தம்++;

        எனில் (cur_info->இலக்கம்_சாவி_ids) {
            new_side_data_size += (uint64_t)cur_info->இலக்கம்_சாவி_ids * cur_info->சாவி_id_size;
            எனில் (new_side_data_size > UINT32_MAX)
                திரும்பு AVERROR(EINVAL);
        }
    }

    buffer = av_fast_realloc(*side_data, allocated_size, new_side_data_size);
    எனில் (!buffer)
        திரும்பு AVERROR(ENOMEM);

    AV_WB32(buffer, init_info_மொத்தம்);
    cur_buffer = buffer + old_side_data_size;
    க்கு (cur_info = info; cur_info; cur_info = cur_info->next) {
        AV_WB32(cur_buffer,      cur_info->system_id_size);
        AV_WB32(cur_buffer +  4, cur_info->இலக்கம்_சாவி_ids);
        AV_WB32(cur_buffer +  8, cur_info->சாவி_id_size);
        AV_WB32(cur_buffer + 12, cur_info->data_size);
        cur_buffer += 16;

        memcpy(cur_buffer, cur_info->system_id, cur_info->system_id_size);
        cur_buffer += cur_info->system_id_size;
        க்கு (i = 0; i < cur_info->இலக்கம்_சாவி_ids; i++) {
            memcpy(cur_buffer, cur_info->சாவி_ids[i], cur_info->சாவி_id_size);
            cur_buffer += cur_info->சாவி_id_size;
        }
        எனில் (cur_info->data_size > 0) {
            memcpy(cur_buffer, cur_info->data, cur_info->data_size);
            cur_buffer += cur_info->data_size;
        }
    }

    *side_data      = buffer;
    *side_data_size = new_side_data_size;
    திரும்பு 0;
}

uint8_t *av_encryption_init_info_add_side_data(மாறிலி AVEncryptionInitInfo *info, size_t *side_data_size)
{
    uint8_t *side_data = வெற்று;
    unsigned முழு allocated_size = 0;

    எனில் (av_encryption_init_info_append_side_data(&side_data, side_data_size, &allocated_size, info) < 0)
        திரும்பு வெற்று;
    திரும்பு side_data;
}
