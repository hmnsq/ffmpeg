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

#ضمن <string.h>

#ضمن "encryption_info.h"
#ضمن "error.h"
#ضمن "mem.h"
#ضمن "intreadwrite.h"

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_كدي, uint32_t مبودي_id_size, uint32_t iv_size)
{
    AVEncryptionInfo *info;

    info = av_mallocz(حجم(*info));
    إذا (!info)
        أرجع عدم;

    info->مبودي_id = av_mallocz(مبودي_id_size);
    info->مبودي_id_size = مبودي_id_size;
    info->iv = av_mallocz(iv_size);
    info->iv_size = iv_size;
    info->subsamples = av_calloc(subsample_كدي, حجم(*info->subsamples));
    info->subsample_كدي = subsample_كدي;

    // Allow info->subsamples to be NULL if there are no subsamples.
    إذا (!info->مبودي_id || !info->iv || (!info->subsamples && subsample_كدي)) {
        av_encryption_info_free(info);
        أرجع عدم;
    }

    أرجع info;
}

AVEncryptionInfo *av_encryption_info_clone(ثابت AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_كدي, info->مبودي_id_size, info->iv_size);
    إذا (!ret)
        أرجع عدم;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    memcpy(ret->iv, info->iv, info->iv_size);
    memcpy(ret->مبودي_id, info->مبودي_id, info->مبودي_id_size);
    memcpy(ret->subsamples, info->subsamples, حجم(*info->subsamples) * info->subsample_كدي);
    أرجع ret;
}

فراغ av_encryption_info_free(AVEncryptionInfo *info)
{
    إذا (info) {
        av_free(info->مبودي_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_data(ثابت uint8_t* buffer, size_t size)
{
    AVEncryptionInfo *info;
    uint64_t مبودي_id_size, iv_size, subsample_كدي, i;

    إذا (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        أرجع عدم;

    مبودي_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_كدي = AV_RB32(buffer + 20);

    إذا (size < FF_ENCRYPTION_INFO_EXTRA + مبودي_id_size + iv_size + subsample_كدي * 8)
        أرجع عدم;

    info = av_encryption_info_alloc(subsample_كدي, مبودي_id_size, iv_size);
    إذا (!info)
        أرجع عدم;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    memcpy(info->مبودي_id, buffer + 24, مبودي_id_size);
    memcpy(info->iv, buffer + مبودي_id_size + 24, iv_size);

    buffer += مبودي_id_size + iv_size + 24;
    لكل (i = 0; i < subsample_كدي; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    أرجع info;
}

uint8_t *av_encryption_info_add_side_data(ثابت AVEncryptionInfo *info, size_t *size)
{
    uint8_t *buffer, *cur_buffer;
    uint32_t i;

    إذا (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->مبودي_id_size ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->مبودي_id_size < info->iv_size ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->مبودي_id_size - info->iv_size) / 8 < info->subsample_كدي) {
        أرجع عدم;
    }

    *size = FF_ENCRYPTION_INFO_EXTRA + info->مبودي_id_size + info->iv_size +
            (info->subsample_كدي * 8);
    cur_buffer = buffer = av_malloc(*size);
    إذا (!buffer)
        أرجع عدم;

    AV_WB32(cur_buffer,      info->scheme);
    AV_WB32(cur_buffer +  4, info->crypt_byte_block);
    AV_WB32(cur_buffer +  8, info->skip_byte_block);
    AV_WB32(cur_buffer + 12, info->مبودي_id_size);
    AV_WB32(cur_buffer + 16, info->iv_size);
    AV_WB32(cur_buffer + 20, info->subsample_كدي);
    cur_buffer += 24;
    memcpy(cur_buffer, info->مبودي_id, info->مبودي_id_size);
    cur_buffer += info->مبودي_id_size;
    memcpy(cur_buffer, info->iv, info->iv_size);
    cur_buffer += info->iv_size;
    لكل (i = 0; i < info->subsample_كدي; i++) {
        AV_WB32(cur_buffer, info->subsamples[i].bytes_of_clear_data);
        AV_WB32(cur_buffer + 4, info->subsamples[i].bytes_of_protected_data);
        cur_buffer += 8;
    }

    أرجع buffer;
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
    uint32_t system_id_size, uint32_t لمب_مبودي_ids, uint32_t مبودي_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    إذا (لمب_مبودي_ids && !مبودي_id_size)
        أرجع عدم;

    info = av_mallocz(حجم(*info));
    إذا (!info)
        أرجع عدم;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->مبودي_ids = مبودي_id_size ? av_calloc(لمب_مبودي_ids, حجم(*info->مبودي_ids)) : عدم;
    info->لمب_مبودي_ids = لمب_مبودي_ids;
    info->مبودي_id_size = مبودي_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    إذا ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->مبودي_ids && لمب_مبودي_ids && مبودي_id_size)) {
        av_encryption_init_info_free(info);
        أرجع عدم;
    }

    إذا (مبودي_id_size) {
        لكل (i = 0; i < لمب_مبودي_ids; i++) {
            info->مبودي_ids[i] = av_mallocz(مبودي_id_size);
            إذا (!info->مبودي_ids[i]) {
                av_encryption_init_info_free(info);
                أرجع عدم;
            }
        }
    }

    أرجع info;
}

فراغ av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    طالما (info) {
        AVEncryptionInitInfo *next = info->next;
        uint32_t i;

        لكل (i = 0; i < info->لمب_مبودي_ids; i++) {
            av_free(info->مبودي_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->مبودي_ids);
        av_free(info->data);
        av_free(info);

        info = next;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_data(
    ثابت uint8_t *side_data, size_t side_data_size)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = عدم, *info, *temp_info;
    uint64_t system_id_size, لمب_مبودي_ids, مبودي_id_size, data_size, i, j;
    uint64_t init_info_كدي;

    إذا (!side_data || side_data_size < 4)
        أرجع عدم;

    init_info_كدي = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    لكل (i = 0; i < init_info_كدي; i++) {
        إذا (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }

        system_id_size = AV_RB32(side_data);
        لمب_مبودي_ids = AV_RB32(side_data + 4);
        مبودي_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        إذا (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + لمب_مبودي_ids * مبودي_id_size) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, لمب_مبودي_ids, مبودي_id_size, data_size);
        إذا (!temp_info) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }
        إذا (i == 0) {
            info = ret = temp_info;
        } وإلا {
            info->next = temp_info;
            info = temp_info;
        }

        memcpy(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        لكل (j = 0; j < لمب_مبودي_ids; j++) {
            memcpy(info->مبودي_ids[j], side_data, مبودي_id_size);
            side_data += مبودي_id_size;
            side_data_size -= مبودي_id_size;
        }
        memcpy(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    أرجع ret;
}

صحيح av_encryption_init_info_append_side_data(uint8_t **side_data, size_t *side_data_size,
                                             unsigned صحيح *allocated_size,
                                             ثابت AVEncryptionInitInfo *info)
{
    ثابت AVEncryptionInitInfo *cur_info;
    uint8_t *buffer, *cur_buffer;
    uint32_t i;
    uint64_t init_info_كدي    = *side_data ? AV_RB32(*side_data) : 0;
    size_t   old_side_data_size = *side_data ? *side_data_size : 4;
    uint64_t new_side_data_size = old_side_data_size;

    لكل (cur_info = info; cur_info; cur_info = cur_info->next) {
        new_side_data_size += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_size + cur_info->data_size;
        إذا (init_info_كدي == UINT32_MAX || new_side_data_size > UINT32_MAX)
            أرجع AVERROR(EINVAL);
        init_info_كدي++;

        إذا (cur_info->لمب_مبودي_ids) {
            new_side_data_size += (uint64_t)cur_info->لمب_مبودي_ids * cur_info->مبودي_id_size;
            إذا (new_side_data_size > UINT32_MAX)
                أرجع AVERROR(EINVAL);
        }
    }

    buffer = av_fast_realloc(*side_data, allocated_size, new_side_data_size);
    إذا (!buffer)
        أرجع AVERROR(ENOMEM);

    AV_WB32(buffer, init_info_كدي);
    cur_buffer = buffer + old_side_data_size;
    لكل (cur_info = info; cur_info; cur_info = cur_info->next) {
        AV_WB32(cur_buffer,      cur_info->system_id_size);
        AV_WB32(cur_buffer +  4, cur_info->لمب_مبودي_ids);
        AV_WB32(cur_buffer +  8, cur_info->مبودي_id_size);
        AV_WB32(cur_buffer + 12, cur_info->data_size);
        cur_buffer += 16;

        memcpy(cur_buffer, cur_info->system_id, cur_info->system_id_size);
        cur_buffer += cur_info->system_id_size;
        لكل (i = 0; i < cur_info->لمب_مبودي_ids; i++) {
            memcpy(cur_buffer, cur_info->مبودي_ids[i], cur_info->مبودي_id_size);
            cur_buffer += cur_info->مبودي_id_size;
        }
        إذا (cur_info->data_size > 0) {
            memcpy(cur_buffer, cur_info->data, cur_info->data_size);
            cur_buffer += cur_info->data_size;
        }
    }

    *side_data      = buffer;
    *side_data_size = new_side_data_size;
    أرجع 0;
}

uint8_t *av_encryption_init_info_add_side_data(ثابت AVEncryptionInitInfo *info, size_t *side_data_size)
{
    uint8_t *side_data = عدم;
    unsigned صحيح allocated_size = 0;

    إذا (av_encryption_init_info_append_side_data(&side_data, side_data_size, &allocated_size, info) < 0)
        أرجع عدم;
    أرجع side_data;
}
