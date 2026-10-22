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

#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "encryption_info.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "intreadwrite.h"

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_ગણતરી, uint32_t ચાવી_id_size, uint32_t iv_size)
{
    AVEncryptionInfo *info;

    info = av_mallocz(કદ(*info));
    જો (!info)
        પાછા ખાલી;

    info->ચાવી_id = av_mallocz(ચાવી_id_size);
    info->ચાવી_id_size = ચાવી_id_size;
    info->iv = av_mallocz(iv_size);
    info->iv_size = iv_size;
    info->subsamples = av_calloc(subsample_ગણતરી, કદ(*info->subsamples));
    info->subsample_ગણતરી = subsample_ગણતરી;

    // Allow info->subsamples to be NULL if there are no subsamples.
    જો (!info->ચાવી_id || !info->iv || (!info->subsamples && subsample_ગણતરી)) {
        av_encryption_info_free(info);
        પાછા ખાલી;
    }

    પાછા info;
}

AVEncryptionInfo *av_encryption_info_clone(અચલ AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_ગણતરી, info->ચાવી_id_size, info->iv_size);
    જો (!ret)
        પાછા ખાલી;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    memcpy(ret->iv, info->iv, info->iv_size);
    memcpy(ret->ચાવી_id, info->ચાવી_id, info->ચાવી_id_size);
    memcpy(ret->subsamples, info->subsamples, કદ(*info->subsamples) * info->subsample_ગણતરી);
    પાછા ret;
}

શૂન્ય av_encryption_info_free(AVEncryptionInfo *info)
{
    જો (info) {
        av_free(info->ચાવી_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_data(અચલ uint8_t* buffer, size_t size)
{
    AVEncryptionInfo *info;
    uint64_t ચાવી_id_size, iv_size, subsample_ગણતરી, i;

    જો (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        પાછા ખાલી;

    ચાવી_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_ગણતરી = AV_RB32(buffer + 20);

    જો (size < FF_ENCRYPTION_INFO_EXTRA + ચાવી_id_size + iv_size + subsample_ગણતરી * 8)
        પાછા ખાલી;

    info = av_encryption_info_alloc(subsample_ગણતરી, ચાવી_id_size, iv_size);
    જો (!info)
        પાછા ખાલી;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    memcpy(info->ચાવી_id, buffer + 24, ચાવી_id_size);
    memcpy(info->iv, buffer + ચાવી_id_size + 24, iv_size);

    buffer += ચાવી_id_size + iv_size + 24;
    માટે (i = 0; i < subsample_ગણતરી; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    પાછા info;
}

uint8_t *av_encryption_info_add_side_data(અચલ AVEncryptionInfo *info, size_t *size)
{
    uint8_t *buffer, *cur_buffer;
    uint32_t i;

    જો (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->ચાવી_id_size ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->ચાવી_id_size < info->iv_size ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->ચાવી_id_size - info->iv_size) / 8 < info->subsample_ગણતરી) {
        પાછા ખાલી;
    }

    *size = FF_ENCRYPTION_INFO_EXTRA + info->ચાવી_id_size + info->iv_size +
            (info->subsample_ગણતરી * 8);
    cur_buffer = buffer = av_malloc(*size);
    જો (!buffer)
        પાછા ખાલી;

    AV_WB32(cur_buffer,      info->scheme);
    AV_WB32(cur_buffer +  4, info->crypt_byte_block);
    AV_WB32(cur_buffer +  8, info->skip_byte_block);
    AV_WB32(cur_buffer + 12, info->ચાવી_id_size);
    AV_WB32(cur_buffer + 16, info->iv_size);
    AV_WB32(cur_buffer + 20, info->subsample_ગણતરી);
    cur_buffer += 24;
    memcpy(cur_buffer, info->ચાવી_id, info->ચાવી_id_size);
    cur_buffer += info->ચાવી_id_size;
    memcpy(cur_buffer, info->iv, info->iv_size);
    cur_buffer += info->iv_size;
    માટે (i = 0; i < info->subsample_ગણતરી; i++) {
        AV_WB32(cur_buffer, info->subsamples[i].bytes_of_clear_data);
        AV_WB32(cur_buffer + 4, info->subsamples[i].bytes_of_protected_data);
        cur_buffer += 8;
    }

    પાછા buffer;
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
    uint32_t system_id_size, uint32_t અંક_ચાવી_ids, uint32_t ચાવી_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    જો (અંક_ચાવી_ids && !ચાવી_id_size)
        પાછા ખાલી;

    info = av_mallocz(કદ(*info));
    જો (!info)
        પાછા ખાલી;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->ચાવી_ids = ચાવી_id_size ? av_calloc(અંક_ચાવી_ids, કદ(*info->ચાવી_ids)) : ખાલી;
    info->અંક_ચાવી_ids = અંક_ચાવી_ids;
    info->ચાવી_id_size = ચાવી_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    જો ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->ચાવી_ids && અંક_ચાવી_ids && ચાવી_id_size)) {
        av_encryption_init_info_free(info);
        પાછા ખાલી;
    }

    જો (ચાવી_id_size) {
        માટે (i = 0; i < અંક_ચાવી_ids; i++) {
            info->ચાવી_ids[i] = av_mallocz(ચાવી_id_size);
            જો (!info->ચાવી_ids[i]) {
                av_encryption_init_info_free(info);
                પાછા ખાલી;
            }
        }
    }

    પાછા info;
}

શૂન્ય av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    જ્યારે (info) {
        AVEncryptionInitInfo *next = info->next;
        uint32_t i;

        માટે (i = 0; i < info->અંક_ચાવી_ids; i++) {
            av_free(info->ચાવી_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->ચાવી_ids);
        av_free(info->data);
        av_free(info);

        info = next;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_data(
    અચલ uint8_t *side_data, size_t side_data_size)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = ખાલી, *info, *temp_info;
    uint64_t system_id_size, અંક_ચાવી_ids, ચાવી_id_size, data_size, i, j;
    uint64_t init_info_ગણતરી;

    જો (!side_data || side_data_size < 4)
        પાછા ખાલી;

    init_info_ગણતરી = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    માટે (i = 0; i < init_info_ગણતરી; i++) {
        જો (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            પાછા ખાલી;
        }

        system_id_size = AV_RB32(side_data);
        અંક_ચાવી_ids = AV_RB32(side_data + 4);
        ચાવી_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        જો (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + અંક_ચાવી_ids * ચાવી_id_size) {
            av_encryption_init_info_free(ret);
            પાછા ખાલી;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, અંક_ચાવી_ids, ચાવી_id_size, data_size);
        જો (!temp_info) {
            av_encryption_init_info_free(ret);
            પાછા ખાલી;
        }
        જો (i == 0) {
            info = ret = temp_info;
        } નહીંતર {
            info->next = temp_info;
            info = temp_info;
        }

        memcpy(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        માટે (j = 0; j < અંક_ચાવી_ids; j++) {
            memcpy(info->ચાવી_ids[j], side_data, ચાવી_id_size);
            side_data += ચાવી_id_size;
            side_data_size -= ચાવી_id_size;
        }
        memcpy(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    પાછા ret;
}

પૂર્ણાંક av_encryption_init_info_append_side_data(uint8_t **side_data, size_t *side_data_size,
                                             unsigned પૂર્ણાંક *allocated_size,
                                             અચલ AVEncryptionInitInfo *info)
{
    અચલ AVEncryptionInitInfo *cur_info;
    uint8_t *buffer, *cur_buffer;
    uint32_t i;
    uint64_t init_info_ગણતરી    = *side_data ? AV_RB32(*side_data) : 0;
    size_t   old_side_data_size = *side_data ? *side_data_size : 4;
    uint64_t new_side_data_size = old_side_data_size;

    માટે (cur_info = info; cur_info; cur_info = cur_info->next) {
        new_side_data_size += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_size + cur_info->data_size;
        જો (init_info_ગણતરી == UINT32_MAX || new_side_data_size > UINT32_MAX)
            પાછા AVERROR(EINVAL);
        init_info_ગણતરી++;

        જો (cur_info->અંક_ચાવી_ids) {
            new_side_data_size += (uint64_t)cur_info->અંક_ચાવી_ids * cur_info->ચાવી_id_size;
            જો (new_side_data_size > UINT32_MAX)
                પાછા AVERROR(EINVAL);
        }
    }

    buffer = av_fast_realloc(*side_data, allocated_size, new_side_data_size);
    જો (!buffer)
        પાછા AVERROR(ENOMEM);

    AV_WB32(buffer, init_info_ગણતરી);
    cur_buffer = buffer + old_side_data_size;
    માટે (cur_info = info; cur_info; cur_info = cur_info->next) {
        AV_WB32(cur_buffer,      cur_info->system_id_size);
        AV_WB32(cur_buffer +  4, cur_info->અંક_ચાવી_ids);
        AV_WB32(cur_buffer +  8, cur_info->ચાવી_id_size);
        AV_WB32(cur_buffer + 12, cur_info->data_size);
        cur_buffer += 16;

        memcpy(cur_buffer, cur_info->system_id, cur_info->system_id_size);
        cur_buffer += cur_info->system_id_size;
        માટે (i = 0; i < cur_info->અંક_ચાવી_ids; i++) {
            memcpy(cur_buffer, cur_info->ચાવી_ids[i], cur_info->ચાવી_id_size);
            cur_buffer += cur_info->ચાવી_id_size;
        }
        જો (cur_info->data_size > 0) {
            memcpy(cur_buffer, cur_info->data, cur_info->data_size);
            cur_buffer += cur_info->data_size;
        }
    }

    *side_data      = buffer;
    *side_data_size = new_side_data_size;
    પાછા 0;
}

uint8_t *av_encryption_init_info_add_side_data(અચલ AVEncryptionInitInfo *info, size_t *side_data_size)
{
    uint8_t *side_data = ખાલી;
    unsigned પૂર્ણાંક allocated_size = 0;

    જો (av_encryption_init_info_append_side_data(&side_data, side_data_size, &allocated_size, info) < 0)
        પાછા ખાલી;
    પાછા side_data;
}
