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

#شامل <string.h>

#شامل "encryption_info.h"
#شامل "error.h"
#شامل "mem.h"
#شامل "intreadwrite.h"

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_شمار, uint32_t کلید_id_size, uint32_t iv_size)
{
    AVEncryptionInfo *info;

    info = av_mallocz(اندازه(*info));
    اگر (!info)
        بازگشت پوچ;

    info->کلید_id = av_mallocz(کلید_id_size);
    info->کلید_id_size = کلید_id_size;
    info->iv = av_mallocz(iv_size);
    info->iv_size = iv_size;
    info->subsamples = av_calloc(subsample_شمار, اندازه(*info->subsamples));
    info->subsample_شمار = subsample_شمار;

    // Allow info->subsamples to be NULL if there are no subsamples.
    اگر (!info->کلید_id || !info->iv || (!info->subsamples && subsample_شمار)) {
        av_encryption_info_free(info);
        بازگشت پوچ;
    }

    بازگشت info;
}

AVEncryptionInfo *av_encryption_info_clone(ثابت AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_شمار, info->کلید_id_size, info->iv_size);
    اگر (!ret)
        بازگشت پوچ;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    memcpy(ret->iv, info->iv, info->iv_size);
    memcpy(ret->کلید_id, info->کلید_id, info->کلید_id_size);
    memcpy(ret->subsamples, info->subsamples, اندازه(*info->subsamples) * info->subsample_شمار);
    بازگشت ret;
}

تهی av_encryption_info_free(AVEncryptionInfo *info)
{
    اگر (info) {
        av_free(info->کلید_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_data(ثابت uint8_t* buffer, size_t size)
{
    AVEncryptionInfo *info;
    uint64_t کلید_id_size, iv_size, subsample_شمار, i;

    اگر (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        بازگشت پوچ;

    کلید_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_شمار = AV_RB32(buffer + 20);

    اگر (size < FF_ENCRYPTION_INFO_EXTRA + کلید_id_size + iv_size + subsample_شمار * 8)
        بازگشت پوچ;

    info = av_encryption_info_alloc(subsample_شمار, کلید_id_size, iv_size);
    اگر (!info)
        بازگشت پوچ;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    memcpy(info->کلید_id, buffer + 24, کلید_id_size);
    memcpy(info->iv, buffer + کلید_id_size + 24, iv_size);

    buffer += کلید_id_size + iv_size + 24;
    برای (i = 0; i < subsample_شمار; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    بازگشت info;
}

uint8_t *av_encryption_info_add_side_data(ثابت AVEncryptionInfo *info, size_t *size)
{
    uint8_t *buffer, *cur_buffer;
    uint32_t i;

    اگر (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->کلید_id_size ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->کلید_id_size < info->iv_size ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->کلید_id_size - info->iv_size) / 8 < info->subsample_شمار) {
        بازگشت پوچ;
    }

    *size = FF_ENCRYPTION_INFO_EXTRA + info->کلید_id_size + info->iv_size +
            (info->subsample_شمار * 8);
    cur_buffer = buffer = av_malloc(*size);
    اگر (!buffer)
        بازگشت پوچ;

    AV_WB32(cur_buffer,      info->scheme);
    AV_WB32(cur_buffer +  4, info->crypt_byte_block);
    AV_WB32(cur_buffer +  8, info->skip_byte_block);
    AV_WB32(cur_buffer + 12, info->کلید_id_size);
    AV_WB32(cur_buffer + 16, info->iv_size);
    AV_WB32(cur_buffer + 20, info->subsample_شمار);
    cur_buffer += 24;
    memcpy(cur_buffer, info->کلید_id, info->کلید_id_size);
    cur_buffer += info->کلید_id_size;
    memcpy(cur_buffer, info->iv, info->iv_size);
    cur_buffer += info->iv_size;
    برای (i = 0; i < info->subsample_شمار; i++) {
        AV_WB32(cur_buffer, info->subsamples[i].bytes_of_clear_data);
        AV_WB32(cur_buffer + 4, info->subsamples[i].bytes_of_protected_data);
        cur_buffer += 8;
    }

    بازگشت buffer;
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
    uint32_t system_id_size, uint32_t رقم_کلید_ids, uint32_t کلید_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    اگر (رقم_کلید_ids && !کلید_id_size)
        بازگشت پوچ;

    info = av_mallocz(اندازه(*info));
    اگر (!info)
        بازگشت پوچ;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->کلید_ids = کلید_id_size ? av_calloc(رقم_کلید_ids, اندازه(*info->کلید_ids)) : پوچ;
    info->رقم_کلید_ids = رقم_کلید_ids;
    info->کلید_id_size = کلید_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    اگر ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->کلید_ids && رقم_کلید_ids && کلید_id_size)) {
        av_encryption_init_info_free(info);
        بازگشت پوچ;
    }

    اگر (کلید_id_size) {
        برای (i = 0; i < رقم_کلید_ids; i++) {
            info->کلید_ids[i] = av_mallocz(کلید_id_size);
            اگر (!info->کلید_ids[i]) {
                av_encryption_init_info_free(info);
                بازگشت پوچ;
            }
        }
    }

    بازگشت info;
}

تهی av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    وقتی (info) {
        AVEncryptionInitInfo *next = info->next;
        uint32_t i;

        برای (i = 0; i < info->رقم_کلید_ids; i++) {
            av_free(info->کلید_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->کلید_ids);
        av_free(info->data);
        av_free(info);

        info = next;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_data(
    ثابت uint8_t *side_data, size_t side_data_size)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = پوچ, *info, *temp_info;
    uint64_t system_id_size, رقم_کلید_ids, کلید_id_size, data_size, i, j;
    uint64_t init_info_شمار;

    اگر (!side_data || side_data_size < 4)
        بازگشت پوچ;

    init_info_شمار = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    برای (i = 0; i < init_info_شمار; i++) {
        اگر (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            بازگشت پوچ;
        }

        system_id_size = AV_RB32(side_data);
        رقم_کلید_ids = AV_RB32(side_data + 4);
        کلید_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        اگر (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + رقم_کلید_ids * کلید_id_size) {
            av_encryption_init_info_free(ret);
            بازگشت پوچ;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, رقم_کلید_ids, کلید_id_size, data_size);
        اگر (!temp_info) {
            av_encryption_init_info_free(ret);
            بازگشت پوچ;
        }
        اگر (i == 0) {
            info = ret = temp_info;
        } وگرنه {
            info->next = temp_info;
            info = temp_info;
        }

        memcpy(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        برای (j = 0; j < رقم_کلید_ids; j++) {
            memcpy(info->کلید_ids[j], side_data, کلید_id_size);
            side_data += کلید_id_size;
            side_data_size -= کلید_id_size;
        }
        memcpy(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    بازگشت ret;
}

صحیح av_encryption_init_info_append_side_data(uint8_t **side_data, size_t *side_data_size,
                                             unsigned صحیح *allocated_size,
                                             ثابت AVEncryptionInitInfo *info)
{
    ثابت AVEncryptionInitInfo *cur_info;
    uint8_t *buffer, *cur_buffer;
    uint32_t i;
    uint64_t init_info_شمار    = *side_data ? AV_RB32(*side_data) : 0;
    size_t   old_side_data_size = *side_data ? *side_data_size : 4;
    uint64_t new_side_data_size = old_side_data_size;

    برای (cur_info = info; cur_info; cur_info = cur_info->next) {
        new_side_data_size += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_size + cur_info->data_size;
        اگر (init_info_شمار == UINT32_MAX || new_side_data_size > UINT32_MAX)
            بازگشت AVERROR(EINVAL);
        init_info_شمار++;

        اگر (cur_info->رقم_کلید_ids) {
            new_side_data_size += (uint64_t)cur_info->رقم_کلید_ids * cur_info->کلید_id_size;
            اگر (new_side_data_size > UINT32_MAX)
                بازگشت AVERROR(EINVAL);
        }
    }

    buffer = av_fast_realloc(*side_data, allocated_size, new_side_data_size);
    اگر (!buffer)
        بازگشت AVERROR(ENOMEM);

    AV_WB32(buffer, init_info_شمار);
    cur_buffer = buffer + old_side_data_size;
    برای (cur_info = info; cur_info; cur_info = cur_info->next) {
        AV_WB32(cur_buffer,      cur_info->system_id_size);
        AV_WB32(cur_buffer +  4, cur_info->رقم_کلید_ids);
        AV_WB32(cur_buffer +  8, cur_info->کلید_id_size);
        AV_WB32(cur_buffer + 12, cur_info->data_size);
        cur_buffer += 16;

        memcpy(cur_buffer, cur_info->system_id, cur_info->system_id_size);
        cur_buffer += cur_info->system_id_size;
        برای (i = 0; i < cur_info->رقم_کلید_ids; i++) {
            memcpy(cur_buffer, cur_info->کلید_ids[i], cur_info->کلید_id_size);
            cur_buffer += cur_info->کلید_id_size;
        }
        اگر (cur_info->data_size > 0) {
            memcpy(cur_buffer, cur_info->data, cur_info->data_size);
            cur_buffer += cur_info->data_size;
        }
    }

    *side_data      = buffer;
    *side_data_size = new_side_data_size;
    بازگشت 0;
}

uint8_t *av_encryption_init_info_add_side_data(ثابت AVEncryptionInitInfo *info, size_t *side_data_size)
{
    uint8_t *side_data = پوچ;
    unsigned صحیح allocated_size = 0;

    اگر (av_encryption_init_info_append_side_data(&side_data, side_data_size, &allocated_size, info) < 0)
        بازگشت پوچ;
    بازگشت side_data;
}
