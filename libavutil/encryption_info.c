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

#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "encryption_info.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "intreadwrite.h"

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_എണ്ണം, uint32_t താക്കോൽ_id_size, uint32_t iv_size)
{
    AVEncryptionInfo *info;

    info = av_mallocz(വലുപ്പം(*info));
    എങ്കിൽ (!info)
        തിരികെ ശൂന്യ;

    info->താക്കോൽ_id = av_mallocz(താക്കോൽ_id_size);
    info->താക്കോൽ_id_size = താക്കോൽ_id_size;
    info->iv = av_mallocz(iv_size);
    info->iv_size = iv_size;
    info->subsamples = av_calloc(subsample_എണ്ണം, വലുപ്പം(*info->subsamples));
    info->subsample_എണ്ണം = subsample_എണ്ണം;

    // Allow info->subsamples to be NULL if there are no subsamples.
    എങ്കിൽ (!info->താക്കോൽ_id || !info->iv || (!info->subsamples && subsample_എണ്ണം)) {
        av_encryption_info_free(info);
        തിരികെ ശൂന്യ;
    }

    തിരികെ info;
}

AVEncryptionInfo *av_encryption_info_clone(സ്ഥിരം AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_എണ്ണം, info->താക്കോൽ_id_size, info->iv_size);
    എങ്കിൽ (!ret)
        തിരികെ ശൂന്യ;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    memcpy(ret->iv, info->iv, info->iv_size);
    memcpy(ret->താക്കോൽ_id, info->താക്കോൽ_id, info->താക്കോൽ_id_size);
    memcpy(ret->subsamples, info->subsamples, വലുപ്പം(*info->subsamples) * info->subsample_എണ്ണം);
    തിരികെ ret;
}

ശൂന്യം av_encryption_info_free(AVEncryptionInfo *info)
{
    എങ്കിൽ (info) {
        av_free(info->താക്കോൽ_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_data(സ്ഥിരം uint8_t* buffer, size_t size)
{
    AVEncryptionInfo *info;
    uint64_t താക്കോൽ_id_size, iv_size, subsample_എണ്ണം, i;

    എങ്കിൽ (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        തിരികെ ശൂന്യ;

    താക്കോൽ_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_എണ്ണം = AV_RB32(buffer + 20);

    എങ്കിൽ (size < FF_ENCRYPTION_INFO_EXTRA + താക്കോൽ_id_size + iv_size + subsample_എണ്ണം * 8)
        തിരികെ ശൂന്യ;

    info = av_encryption_info_alloc(subsample_എണ്ണം, താക്കോൽ_id_size, iv_size);
    എങ്കിൽ (!info)
        തിരികെ ശൂന്യ;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    memcpy(info->താക്കോൽ_id, buffer + 24, താക്കോൽ_id_size);
    memcpy(info->iv, buffer + താക്കോൽ_id_size + 24, iv_size);

    buffer += താക്കോൽ_id_size + iv_size + 24;
    വേണ്ടി (i = 0; i < subsample_എണ്ണം; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    തിരികെ info;
}

uint8_t *av_encryption_info_add_side_data(സ്ഥിരം AVEncryptionInfo *info, size_t *size)
{
    uint8_t *buffer, *cur_buffer;
    uint32_t i;

    എങ്കിൽ (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->താക്കോൽ_id_size ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->താക്കോൽ_id_size < info->iv_size ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->താക്കോൽ_id_size - info->iv_size) / 8 < info->subsample_എണ്ണം) {
        തിരികെ ശൂന്യ;
    }

    *size = FF_ENCRYPTION_INFO_EXTRA + info->താക്കോൽ_id_size + info->iv_size +
            (info->subsample_എണ്ണം * 8);
    cur_buffer = buffer = av_malloc(*size);
    എങ്കിൽ (!buffer)
        തിരികെ ശൂന്യ;

    AV_WB32(cur_buffer,      info->scheme);
    AV_WB32(cur_buffer +  4, info->crypt_byte_block);
    AV_WB32(cur_buffer +  8, info->skip_byte_block);
    AV_WB32(cur_buffer + 12, info->താക്കോൽ_id_size);
    AV_WB32(cur_buffer + 16, info->iv_size);
    AV_WB32(cur_buffer + 20, info->subsample_എണ്ണം);
    cur_buffer += 24;
    memcpy(cur_buffer, info->താക്കോൽ_id, info->താക്കോൽ_id_size);
    cur_buffer += info->താക്കോൽ_id_size;
    memcpy(cur_buffer, info->iv, info->iv_size);
    cur_buffer += info->iv_size;
    വേണ്ടി (i = 0; i < info->subsample_എണ്ണം; i++) {
        AV_WB32(cur_buffer, info->subsamples[i].bytes_of_clear_data);
        AV_WB32(cur_buffer + 4, info->subsamples[i].bytes_of_protected_data);
        cur_buffer += 8;
    }

    തിരികെ buffer;
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
    uint32_t system_id_size, uint32_t അക്കം_താക്കോൽ_ids, uint32_t താക്കോൽ_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    എങ്കിൽ (അക്കം_താക്കോൽ_ids && !താക്കോൽ_id_size)
        തിരികെ ശൂന്യ;

    info = av_mallocz(വലുപ്പം(*info));
    എങ്കിൽ (!info)
        തിരികെ ശൂന്യ;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->താക്കോൽ_ids = താക്കോൽ_id_size ? av_calloc(അക്കം_താക്കോൽ_ids, വലുപ്പം(*info->താക്കോൽ_ids)) : ശൂന്യ;
    info->അക്കം_താക്കോൽ_ids = അക്കം_താക്കോൽ_ids;
    info->താക്കോൽ_id_size = താക്കോൽ_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    എങ്കിൽ ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->താക്കോൽ_ids && അക്കം_താക്കോൽ_ids && താക്കോൽ_id_size)) {
        av_encryption_init_info_free(info);
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (താക്കോൽ_id_size) {
        വേണ്ടി (i = 0; i < അക്കം_താക്കോൽ_ids; i++) {
            info->താക്കോൽ_ids[i] = av_mallocz(താക്കോൽ_id_size);
            എങ്കിൽ (!info->താക്കോൽ_ids[i]) {
                av_encryption_init_info_free(info);
                തിരികെ ശൂന്യ;
            }
        }
    }

    തിരികെ info;
}

ശൂന്യം av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    ആകുമ്പോൾ (info) {
        AVEncryptionInitInfo *next = info->next;
        uint32_t i;

        വേണ്ടി (i = 0; i < info->അക്കം_താക്കോൽ_ids; i++) {
            av_free(info->താക്കോൽ_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->താക്കോൽ_ids);
        av_free(info->data);
        av_free(info);

        info = next;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_data(
    സ്ഥിരം uint8_t *side_data, size_t side_data_size)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = ശൂന്യ, *info, *temp_info;
    uint64_t system_id_size, അക്കം_താക്കോൽ_ids, താക്കോൽ_id_size, data_size, i, j;
    uint64_t init_info_എണ്ണം;

    എങ്കിൽ (!side_data || side_data_size < 4)
        തിരികെ ശൂന്യ;

    init_info_എണ്ണം = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    വേണ്ടി (i = 0; i < init_info_എണ്ണം; i++) {
        എങ്കിൽ (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            തിരികെ ശൂന്യ;
        }

        system_id_size = AV_RB32(side_data);
        അക്കം_താക്കോൽ_ids = AV_RB32(side_data + 4);
        താക്കോൽ_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        എങ്കിൽ (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + അക്കം_താക്കോൽ_ids * താക്കോൽ_id_size) {
            av_encryption_init_info_free(ret);
            തിരികെ ശൂന്യ;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, അക്കം_താക്കോൽ_ids, താക്കോൽ_id_size, data_size);
        എങ്കിൽ (!temp_info) {
            av_encryption_init_info_free(ret);
            തിരികെ ശൂന്യ;
        }
        എങ്കിൽ (i == 0) {
            info = ret = temp_info;
        } അല്ലെങ്കിൽ {
            info->next = temp_info;
            info = temp_info;
        }

        memcpy(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        വേണ്ടി (j = 0; j < അക്കം_താക്കോൽ_ids; j++) {
            memcpy(info->താക്കോൽ_ids[j], side_data, താക്കോൽ_id_size);
            side_data += താക്കോൽ_id_size;
            side_data_size -= താക്കോൽ_id_size;
        }
        memcpy(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    തിരികെ ret;
}

പൂർണ്ണസംഖ്യ av_encryption_init_info_append_side_data(uint8_t **side_data, size_t *side_data_size,
                                             unsigned പൂർണ്ണസംഖ്യ *allocated_size,
                                             സ്ഥിരം AVEncryptionInitInfo *info)
{
    സ്ഥിരം AVEncryptionInitInfo *cur_info;
    uint8_t *buffer, *cur_buffer;
    uint32_t i;
    uint64_t init_info_എണ്ണം    = *side_data ? AV_RB32(*side_data) : 0;
    size_t   old_side_data_size = *side_data ? *side_data_size : 4;
    uint64_t new_side_data_size = old_side_data_size;

    വേണ്ടി (cur_info = info; cur_info; cur_info = cur_info->next) {
        new_side_data_size += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_size + cur_info->data_size;
        എങ്കിൽ (init_info_എണ്ണം == UINT32_MAX || new_side_data_size > UINT32_MAX)
            തിരികെ AVERROR(EINVAL);
        init_info_എണ്ണം++;

        എങ്കിൽ (cur_info->അക്കം_താക്കോൽ_ids) {
            new_side_data_size += (uint64_t)cur_info->അക്കം_താക്കോൽ_ids * cur_info->താക്കോൽ_id_size;
            എങ്കിൽ (new_side_data_size > UINT32_MAX)
                തിരികെ AVERROR(EINVAL);
        }
    }

    buffer = av_fast_realloc(*side_data, allocated_size, new_side_data_size);
    എങ്കിൽ (!buffer)
        തിരികെ AVERROR(ENOMEM);

    AV_WB32(buffer, init_info_എണ്ണം);
    cur_buffer = buffer + old_side_data_size;
    വേണ്ടി (cur_info = info; cur_info; cur_info = cur_info->next) {
        AV_WB32(cur_buffer,      cur_info->system_id_size);
        AV_WB32(cur_buffer +  4, cur_info->അക്കം_താക്കോൽ_ids);
        AV_WB32(cur_buffer +  8, cur_info->താക്കോൽ_id_size);
        AV_WB32(cur_buffer + 12, cur_info->data_size);
        cur_buffer += 16;

        memcpy(cur_buffer, cur_info->system_id, cur_info->system_id_size);
        cur_buffer += cur_info->system_id_size;
        വേണ്ടി (i = 0; i < cur_info->അക്കം_താക്കോൽ_ids; i++) {
            memcpy(cur_buffer, cur_info->താക്കോൽ_ids[i], cur_info->താക്കോൽ_id_size);
            cur_buffer += cur_info->താക്കോൽ_id_size;
        }
        എങ്കിൽ (cur_info->data_size > 0) {
            memcpy(cur_buffer, cur_info->data, cur_info->data_size);
            cur_buffer += cur_info->data_size;
        }
    }

    *side_data      = buffer;
    *side_data_size = new_side_data_size;
    തിരികെ 0;
}

uint8_t *av_encryption_init_info_add_side_data(സ്ഥിരം AVEncryptionInitInfo *info, size_t *side_data_size)
{
    uint8_t *side_data = ശൂന്യ;
    unsigned പൂർണ്ണസംഖ്യ allocated_size = 0;

    എങ്കിൽ (av_encryption_init_info_append_side_data(&side_data, side_data_size, &allocated_size, info) < 0)
        തിരികെ ശൂന്യ;
    തിരികെ side_data;
}
