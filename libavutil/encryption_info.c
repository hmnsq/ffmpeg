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

#अन्तर्भाव <string.h>

#अन्तर्भाव "encryption_info.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "intreadwrite.h"

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_गिनती, uint32_t कुंजी_id_size, uint32_t iv_size)
{
    AVEncryptionInfo *info;

    info = av_mallocz(परिमाण(*info));
    यदि (!info)
        प्रत्यागम रिक्त;

    info->कुंजी_id = av_mallocz(कुंजी_id_size);
    info->कुंजी_id_size = कुंजी_id_size;
    info->iv = av_mallocz(iv_size);
    info->iv_size = iv_size;
    info->subsamples = av_calloc(subsample_गिनती, परिमाण(*info->subsamples));
    info->subsample_गिनती = subsample_गिनती;

    // Allow info->subsamples to be NULL if there are no subsamples.
    यदि (!info->कुंजी_id || !info->iv || (!info->subsamples && subsample_गिनती)) {
        av_encryption_info_free(info);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम info;
}

AVEncryptionInfo *av_encryption_info_clone(ध्रुव AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_गिनती, info->कुंजी_id_size, info->iv_size);
    यदि (!ret)
        प्रत्यागम रिक्त;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    memcpy(ret->iv, info->iv, info->iv_size);
    memcpy(ret->कुंजी_id, info->कुंजी_id, info->कुंजी_id_size);
    memcpy(ret->subsamples, info->subsamples, परिमाण(*info->subsamples) * info->subsample_गिनती);
    प्रत्यागम ret;
}

शून्य av_encryption_info_free(AVEncryptionInfo *info)
{
    यदि (info) {
        av_free(info->कुंजी_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_data(ध्रुव uint8_t* buffer, size_t size)
{
    AVEncryptionInfo *info;
    uint64_t कुंजी_id_size, iv_size, subsample_गिनती, i;

    यदि (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        प्रत्यागम रिक्त;

    कुंजी_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_गिनती = AV_RB32(buffer + 20);

    यदि (size < FF_ENCRYPTION_INFO_EXTRA + कुंजी_id_size + iv_size + subsample_गिनती * 8)
        प्रत्यागम रिक्त;

    info = av_encryption_info_alloc(subsample_गिनती, कुंजी_id_size, iv_size);
    यदि (!info)
        प्रत्यागम रिक्त;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    memcpy(info->कुंजी_id, buffer + 24, कुंजी_id_size);
    memcpy(info->iv, buffer + कुंजी_id_size + 24, iv_size);

    buffer += कुंजी_id_size + iv_size + 24;
    प्रति (i = 0; i < subsample_गिनती; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    प्रत्यागम info;
}

uint8_t *av_encryption_info_add_side_data(ध्रुव AVEncryptionInfo *info, size_t *size)
{
    uint8_t *buffer, *cur_buffer;
    uint32_t i;

    यदि (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->कुंजी_id_size ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->कुंजी_id_size < info->iv_size ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->कुंजी_id_size - info->iv_size) / 8 < info->subsample_गिनती) {
        प्रत्यागम रिक्त;
    }

    *size = FF_ENCRYPTION_INFO_EXTRA + info->कुंजी_id_size + info->iv_size +
            (info->subsample_गिनती * 8);
    cur_buffer = buffer = av_malloc(*size);
    यदि (!buffer)
        प्रत्यागम रिक्त;

    AV_WB32(cur_buffer,      info->scheme);
    AV_WB32(cur_buffer +  4, info->crypt_byte_block);
    AV_WB32(cur_buffer +  8, info->skip_byte_block);
    AV_WB32(cur_buffer + 12, info->कुंजी_id_size);
    AV_WB32(cur_buffer + 16, info->iv_size);
    AV_WB32(cur_buffer + 20, info->subsample_गिनती);
    cur_buffer += 24;
    memcpy(cur_buffer, info->कुंजी_id, info->कुंजी_id_size);
    cur_buffer += info->कुंजी_id_size;
    memcpy(cur_buffer, info->iv, info->iv_size);
    cur_buffer += info->iv_size;
    प्रति (i = 0; i < info->subsample_गिनती; i++) {
        AV_WB32(cur_buffer, info->subsamples[i].bytes_of_clear_data);
        AV_WB32(cur_buffer + 4, info->subsamples[i].bytes_of_protected_data);
        cur_buffer += 8;
    }

    प्रत्यागम buffer;
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
    uint32_t system_id_size, uint32_t अंक_कुंजी_ids, uint32_t कुंजी_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    यदि (अंक_कुंजी_ids && !कुंजी_id_size)
        प्रत्यागम रिक्त;

    info = av_mallocz(परिमाण(*info));
    यदि (!info)
        प्रत्यागम रिक्त;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->कुंजी_ids = कुंजी_id_size ? av_calloc(अंक_कुंजी_ids, परिमाण(*info->कुंजी_ids)) : रिक्त;
    info->अंक_कुंजी_ids = अंक_कुंजी_ids;
    info->कुंजी_id_size = कुंजी_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    यदि ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->कुंजी_ids && अंक_कुंजी_ids && कुंजी_id_size)) {
        av_encryption_init_info_free(info);
        प्रत्यागम रिक्त;
    }

    यदि (कुंजी_id_size) {
        प्रति (i = 0; i < अंक_कुंजी_ids; i++) {
            info->कुंजी_ids[i] = av_mallocz(कुंजी_id_size);
            यदि (!info->कुंजी_ids[i]) {
                av_encryption_init_info_free(info);
                प्रत्यागम रिक्त;
            }
        }
    }

    प्रत्यागम info;
}

शून्य av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    यावत् (info) {
        AVEncryptionInitInfo *next = info->next;
        uint32_t i;

        प्रति (i = 0; i < info->अंक_कुंजी_ids; i++) {
            av_free(info->कुंजी_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->कुंजी_ids);
        av_free(info->data);
        av_free(info);

        info = next;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_data(
    ध्रुव uint8_t *side_data, size_t side_data_size)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = रिक्त, *info, *temp_info;
    uint64_t system_id_size, अंक_कुंजी_ids, कुंजी_id_size, data_size, i, j;
    uint64_t init_info_गिनती;

    यदि (!side_data || side_data_size < 4)
        प्रत्यागम रिक्त;

    init_info_गिनती = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    प्रति (i = 0; i < init_info_गिनती; i++) {
        यदि (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            प्रत्यागम रिक्त;
        }

        system_id_size = AV_RB32(side_data);
        अंक_कुंजी_ids = AV_RB32(side_data + 4);
        कुंजी_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        यदि (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + अंक_कुंजी_ids * कुंजी_id_size) {
            av_encryption_init_info_free(ret);
            प्रत्यागम रिक्त;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, अंक_कुंजी_ids, कुंजी_id_size, data_size);
        यदि (!temp_info) {
            av_encryption_init_info_free(ret);
            प्रत्यागम रिक्त;
        }
        यदि (i == 0) {
            info = ret = temp_info;
        } अन्यथा {
            info->next = temp_info;
            info = temp_info;
        }

        memcpy(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        प्रति (j = 0; j < अंक_कुंजी_ids; j++) {
            memcpy(info->कुंजी_ids[j], side_data, कुंजी_id_size);
            side_data += कुंजी_id_size;
            side_data_size -= कुंजी_id_size;
        }
        memcpy(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    प्रत्यागम ret;
}

पूर्णाङ्क av_encryption_init_info_append_side_data(uint8_t **side_data, size_t *side_data_size,
                                             unsigned पूर्णाङ्क *allocated_size,
                                             ध्रुव AVEncryptionInitInfo *info)
{
    ध्रुव AVEncryptionInitInfo *cur_info;
    uint8_t *buffer, *cur_buffer;
    uint32_t i;
    uint64_t init_info_गिनती    = *side_data ? AV_RB32(*side_data) : 0;
    size_t   old_side_data_size = *side_data ? *side_data_size : 4;
    uint64_t new_side_data_size = old_side_data_size;

    प्रति (cur_info = info; cur_info; cur_info = cur_info->next) {
        new_side_data_size += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_size + cur_info->data_size;
        यदि (init_info_गिनती == UINT32_MAX || new_side_data_size > UINT32_MAX)
            प्रत्यागम AVERROR(EINVAL);
        init_info_गिनती++;

        यदि (cur_info->अंक_कुंजी_ids) {
            new_side_data_size += (uint64_t)cur_info->अंक_कुंजी_ids * cur_info->कुंजी_id_size;
            यदि (new_side_data_size > UINT32_MAX)
                प्रत्यागम AVERROR(EINVAL);
        }
    }

    buffer = av_fast_realloc(*side_data, allocated_size, new_side_data_size);
    यदि (!buffer)
        प्रत्यागम AVERROR(ENOMEM);

    AV_WB32(buffer, init_info_गिनती);
    cur_buffer = buffer + old_side_data_size;
    प्रति (cur_info = info; cur_info; cur_info = cur_info->next) {
        AV_WB32(cur_buffer,      cur_info->system_id_size);
        AV_WB32(cur_buffer +  4, cur_info->अंक_कुंजी_ids);
        AV_WB32(cur_buffer +  8, cur_info->कुंजी_id_size);
        AV_WB32(cur_buffer + 12, cur_info->data_size);
        cur_buffer += 16;

        memcpy(cur_buffer, cur_info->system_id, cur_info->system_id_size);
        cur_buffer += cur_info->system_id_size;
        प्रति (i = 0; i < cur_info->अंक_कुंजी_ids; i++) {
            memcpy(cur_buffer, cur_info->कुंजी_ids[i], cur_info->कुंजी_id_size);
            cur_buffer += cur_info->कुंजी_id_size;
        }
        यदि (cur_info->data_size > 0) {
            memcpy(cur_buffer, cur_info->data, cur_info->data_size);
            cur_buffer += cur_info->data_size;
        }
    }

    *side_data      = buffer;
    *side_data_size = new_side_data_size;
    प्रत्यागम 0;
}

uint8_t *av_encryption_init_info_add_side_data(ध्रुव AVEncryptionInitInfo *info, size_t *side_data_size)
{
    uint8_t *side_data = रिक्त;
    unsigned पूर्णाङ्क allocated_size = 0;

    यदि (av_encryption_init_info_append_side_data(&side_data, side_data_size, &allocated_size, info) < 0)
        प्रत्यागम रिक्त;
    प्रत्यागम side_data;
}
