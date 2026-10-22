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

#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "encryption_info.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_ಎಣಿಕೆ, uint32_t ಕೀಲಿ_id_size, uint32_t iv_size)
{
    AVEncryptionInfo *info;

    info = av_mallocz(ಪರಿಮಾಣ(*info));
    ಯದಿ (!info)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    info->ಕೀಲಿ_id = av_mallocz(ಕೀಲಿ_id_size);
    info->ಕೀಲಿ_id_size = ಕೀಲಿ_id_size;
    info->iv = av_mallocz(iv_size);
    info->iv_size = iv_size;
    info->subsamples = av_calloc(subsample_ಎಣಿಕೆ, ಪರಿಮಾಣ(*info->subsamples));
    info->subsample_ಎಣಿಕೆ = subsample_ಎಣಿಕೆ;

    // Allow info->subsamples to be NULL if there are no subsamples.
    ಯದಿ (!info->ಕೀಲಿ_id || !info->iv || (!info->subsamples && subsample_ಎಣಿಕೆ)) {
        av_encryption_info_free(info);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ info;
}

AVEncryptionInfo *av_encryption_info_clone(ಧ್ರುವ AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_ಎಣಿಕೆ, info->ಕೀಲಿ_id_size, info->iv_size);
    ಯದಿ (!ret)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    memcpy(ret->iv, info->iv, info->iv_size);
    memcpy(ret->ಕೀಲಿ_id, info->ಕೀಲಿ_id, info->ಕೀಲಿ_id_size);
    memcpy(ret->subsamples, info->subsamples, ಪರಿಮಾಣ(*info->subsamples) * info->subsample_ಎಣಿಕೆ);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಶೂನ್ಯ av_encryption_info_free(AVEncryptionInfo *info)
{
    ಯದಿ (info) {
        av_free(info->ಕೀಲಿ_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_data(ಧ್ರುವ uint8_t* buffer, size_t size)
{
    AVEncryptionInfo *info;
    uint64_t ಕೀಲಿ_id_size, iv_size, subsample_ಎಣಿಕೆ, i;

    ಯದಿ (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಕೀಲಿ_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_ಎಣಿಕೆ = AV_RB32(buffer + 20);

    ಯದಿ (size < FF_ENCRYPTION_INFO_EXTRA + ಕೀಲಿ_id_size + iv_size + subsample_ಎಣಿಕೆ * 8)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    info = av_encryption_info_alloc(subsample_ಎಣಿಕೆ, ಕೀಲಿ_id_size, iv_size);
    ಯದಿ (!info)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    memcpy(info->ಕೀಲಿ_id, buffer + 24, ಕೀಲಿ_id_size);
    memcpy(info->iv, buffer + ಕೀಲಿ_id_size + 24, iv_size);

    buffer += ಕೀಲಿ_id_size + iv_size + 24;
    ಪ್ರತಿ (i = 0; i < subsample_ಎಣಿಕೆ; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    ಪ್ರತ್ಯಾಗಮ info;
}

uint8_t *av_encryption_info_add_side_data(ಧ್ರುವ AVEncryptionInfo *info, size_t *size)
{
    uint8_t *buffer, *cur_buffer;
    uint32_t i;

    ಯದಿ (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->ಕೀಲಿ_id_size ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->ಕೀಲಿ_id_size < info->iv_size ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->ಕೀಲಿ_id_size - info->iv_size) / 8 < info->subsample_ಎಣಿಕೆ) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    *size = FF_ENCRYPTION_INFO_EXTRA + info->ಕೀಲಿ_id_size + info->iv_size +
            (info->subsample_ಎಣಿಕೆ * 8);
    cur_buffer = buffer = av_malloc(*size);
    ಯದಿ (!buffer)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    AV_WB32(cur_buffer,      info->scheme);
    AV_WB32(cur_buffer +  4, info->crypt_byte_block);
    AV_WB32(cur_buffer +  8, info->skip_byte_block);
    AV_WB32(cur_buffer + 12, info->ಕೀಲಿ_id_size);
    AV_WB32(cur_buffer + 16, info->iv_size);
    AV_WB32(cur_buffer + 20, info->subsample_ಎಣಿಕೆ);
    cur_buffer += 24;
    memcpy(cur_buffer, info->ಕೀಲಿ_id, info->ಕೀಲಿ_id_size);
    cur_buffer += info->ಕೀಲಿ_id_size;
    memcpy(cur_buffer, info->iv, info->iv_size);
    cur_buffer += info->iv_size;
    ಪ್ರತಿ (i = 0; i < info->subsample_ಎಣಿಕೆ; i++) {
        AV_WB32(cur_buffer, info->subsamples[i].bytes_of_clear_data);
        AV_WB32(cur_buffer + 4, info->subsamples[i].bytes_of_protected_data);
        cur_buffer += 8;
    }

    ಪ್ರತ್ಯಾಗಮ buffer;
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
    uint32_t system_id_size, uint32_t ಅಂಕೆ_ಕೀಲಿ_ids, uint32_t ಕೀಲಿ_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    ಯದಿ (ಅಂಕೆ_ಕೀಲಿ_ids && !ಕೀಲಿ_id_size)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    info = av_mallocz(ಪರಿಮಾಣ(*info));
    ಯದಿ (!info)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->ಕೀಲಿ_ids = ಕೀಲಿ_id_size ? av_calloc(ಅಂಕೆ_ಕೀಲಿ_ids, ಪರಿಮಾಣ(*info->ಕೀಲಿ_ids)) : ರಿಕ್ತ;
    info->ಅಂಕೆ_ಕೀಲಿ_ids = ಅಂಕೆ_ಕೀಲಿ_ids;
    info->ಕೀಲಿ_id_size = ಕೀಲಿ_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    ಯದಿ ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->ಕೀಲಿ_ids && ಅಂಕೆ_ಕೀಲಿ_ids && ಕೀಲಿ_id_size)) {
        av_encryption_init_info_free(info);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (ಕೀಲಿ_id_size) {
        ಪ್ರತಿ (i = 0; i < ಅಂಕೆ_ಕೀಲಿ_ids; i++) {
            info->ಕೀಲಿ_ids[i] = av_mallocz(ಕೀಲಿ_id_size);
            ಯದಿ (!info->ಕೀಲಿ_ids[i]) {
                av_encryption_init_info_free(info);
                ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ info;
}

ಶೂನ್ಯ av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    ಯಾವತ್ (info) {
        AVEncryptionInitInfo *next = info->next;
        uint32_t i;

        ಪ್ರತಿ (i = 0; i < info->ಅಂಕೆ_ಕೀಲಿ_ids; i++) {
            av_free(info->ಕೀಲಿ_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->ಕೀಲಿ_ids);
        av_free(info->data);
        av_free(info);

        info = next;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_data(
    ಧ್ರುವ uint8_t *side_data, size_t side_data_size)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = ರಿಕ್ತ, *info, *temp_info;
    uint64_t system_id_size, ಅಂಕೆ_ಕೀಲಿ_ids, ಕೀಲಿ_id_size, data_size, i, j;
    uint64_t init_info_ಎಣಿಕೆ;

    ಯದಿ (!side_data || side_data_size < 4)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    init_info_ಎಣಿಕೆ = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    ಪ್ರತಿ (i = 0; i < init_info_ಎಣಿಕೆ; i++) {
        ಯದಿ (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }

        system_id_size = AV_RB32(side_data);
        ಅಂಕೆ_ಕೀಲಿ_ids = AV_RB32(side_data + 4);
        ಕೀಲಿ_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        ಯದಿ (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + ಅಂಕೆ_ಕೀಲಿ_ids * ಕೀಲಿ_id_size) {
            av_encryption_init_info_free(ret);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, ಅಂಕೆ_ಕೀಲಿ_ids, ಕೀಲಿ_id_size, data_size);
        ಯದಿ (!temp_info) {
            av_encryption_init_info_free(ret);
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        ಯದಿ (i == 0) {
            info = ret = temp_info;
        } ಅನ್ಯಥಾ {
            info->next = temp_info;
            info = temp_info;
        }

        memcpy(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        ಪ್ರತಿ (j = 0; j < ಅಂಕೆ_ಕೀಲಿ_ids; j++) {
            memcpy(info->ಕೀಲಿ_ids[j], side_data, ಕೀಲಿ_id_size);
            side_data += ಕೀಲಿ_id_size;
            side_data_size -= ಕೀಲಿ_id_size;
        }
        memcpy(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_encryption_init_info_append_side_data(uint8_t **side_data, size_t *side_data_size,
                                             unsigned ಪೂರ್ಣಾಙ್ಕ *allocated_size,
                                             ಧ್ರುವ AVEncryptionInitInfo *info)
{
    ಧ್ರುವ AVEncryptionInitInfo *cur_info;
    uint8_t *buffer, *cur_buffer;
    uint32_t i;
    uint64_t init_info_ಎಣಿಕೆ    = *side_data ? AV_RB32(*side_data) : 0;
    size_t   old_side_data_size = *side_data ? *side_data_size : 4;
    uint64_t new_side_data_size = old_side_data_size;

    ಪ್ರತಿ (cur_info = info; cur_info; cur_info = cur_info->next) {
        new_side_data_size += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_size + cur_info->data_size;
        ಯದಿ (init_info_ಎಣಿಕೆ == UINT32_MAX || new_side_data_size > UINT32_MAX)
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        init_info_ಎಣಿಕೆ++;

        ಯದಿ (cur_info->ಅಂಕೆ_ಕೀಲಿ_ids) {
            new_side_data_size += (uint64_t)cur_info->ಅಂಕೆ_ಕೀಲಿ_ids * cur_info->ಕೀಲಿ_id_size;
            ಯದಿ (new_side_data_size > UINT32_MAX)
                ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
    }

    buffer = av_fast_realloc(*side_data, allocated_size, new_side_data_size);
    ಯದಿ (!buffer)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    AV_WB32(buffer, init_info_ಎಣಿಕೆ);
    cur_buffer = buffer + old_side_data_size;
    ಪ್ರತಿ (cur_info = info; cur_info; cur_info = cur_info->next) {
        AV_WB32(cur_buffer,      cur_info->system_id_size);
        AV_WB32(cur_buffer +  4, cur_info->ಅಂಕೆ_ಕೀಲಿ_ids);
        AV_WB32(cur_buffer +  8, cur_info->ಕೀಲಿ_id_size);
        AV_WB32(cur_buffer + 12, cur_info->data_size);
        cur_buffer += 16;

        memcpy(cur_buffer, cur_info->system_id, cur_info->system_id_size);
        cur_buffer += cur_info->system_id_size;
        ಪ್ರತಿ (i = 0; i < cur_info->ಅಂಕೆ_ಕೀಲಿ_ids; i++) {
            memcpy(cur_buffer, cur_info->ಕೀಲಿ_ids[i], cur_info->ಕೀಲಿ_id_size);
            cur_buffer += cur_info->ಕೀಲಿ_id_size;
        }
        ಯದಿ (cur_info->data_size > 0) {
            memcpy(cur_buffer, cur_info->data, cur_info->data_size);
            cur_buffer += cur_info->data_size;
        }
    }

    *side_data      = buffer;
    *side_data_size = new_side_data_size;
    ಪ್ರತ್ಯಾಗಮ 0;
}

uint8_t *av_encryption_init_info_add_side_data(ಧ್ರುವ AVEncryptionInitInfo *info, size_t *side_data_size)
{
    uint8_t *side_data = ರಿಕ್ತ;
    unsigned ಪೂರ್ಣಾಙ್ಕ allocated_size = 0;

    ಯದಿ (av_encryption_init_info_append_side_data(&side_data, side_data_size, &allocated_size, info) < 0)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ side_data;
}
