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

#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "encryption_info.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "intreadwrite.h"

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_ଗଣନା, uint32_t ଚାବି_id_size, uint32_t iv_size)
{
    AVEncryptionInfo *info;

    info = av_mallocz(ଆକାର(*info));
    ଯଦି (!info)
        ଫେରନ୍ତୁ ଖାଲି;

    info->ଚାବି_id = av_mallocz(ଚାବି_id_size);
    info->ଚାବି_id_size = ଚାବି_id_size;
    info->iv = av_mallocz(iv_size);
    info->iv_size = iv_size;
    info->subsamples = av_calloc(subsample_ଗଣନା, ଆକାର(*info->subsamples));
    info->subsample_ଗଣନା = subsample_ଗଣନା;

    // Allow info->subsamples to be NULL if there are no subsamples.
    ଯଦି (!info->ଚାବି_id || !info->iv || (!info->subsamples && subsample_ଗଣନା)) {
        av_encryption_info_free(info);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ info;
}

AVEncryptionInfo *av_encryption_info_clone(ଅଚଳ AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_ଗଣନା, info->ଚାବି_id_size, info->iv_size);
    ଯଦି (!ret)
        ଫେରନ୍ତୁ ଖାଲି;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    memcpy(ret->iv, info->iv, info->iv_size);
    memcpy(ret->ଚାବି_id, info->ଚାବି_id, info->ଚାବି_id_size);
    memcpy(ret->subsamples, info->subsamples, ଆକାର(*info->subsamples) * info->subsample_ଗଣନା);
    ଫେରନ୍ତୁ ret;
}

ଶୂନ୍ୟ av_encryption_info_free(AVEncryptionInfo *info)
{
    ଯଦି (info) {
        av_free(info->ଚାବି_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_data(ଅଚଳ uint8_t* buffer, size_t size)
{
    AVEncryptionInfo *info;
    uint64_t ଚାବି_id_size, iv_size, subsample_ଗଣନା, i;

    ଯଦି (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        ଫେରନ୍ତୁ ଖାଲି;

    ଚାବି_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_ଗଣନା = AV_RB32(buffer + 20);

    ଯଦି (size < FF_ENCRYPTION_INFO_EXTRA + ଚାବି_id_size + iv_size + subsample_ଗଣନା * 8)
        ଫେରନ୍ତୁ ଖାଲି;

    info = av_encryption_info_alloc(subsample_ଗଣନା, ଚାବି_id_size, iv_size);
    ଯଦି (!info)
        ଫେରନ୍ତୁ ଖାଲି;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    memcpy(info->ଚାବି_id, buffer + 24, ଚାବି_id_size);
    memcpy(info->iv, buffer + ଚାବି_id_size + 24, iv_size);

    buffer += ଚାବି_id_size + iv_size + 24;
    ପାଇଁ (i = 0; i < subsample_ଗଣନା; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    ଫେରନ୍ତୁ info;
}

uint8_t *av_encryption_info_add_side_data(ଅଚଳ AVEncryptionInfo *info, size_t *size)
{
    uint8_t *buffer, *cur_buffer;
    uint32_t i;

    ଯଦି (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->ଚାବି_id_size ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->ଚାବି_id_size < info->iv_size ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->ଚାବି_id_size - info->iv_size) / 8 < info->subsample_ଗଣନା) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    *size = FF_ENCRYPTION_INFO_EXTRA + info->ଚାବି_id_size + info->iv_size +
            (info->subsample_ଗଣନା * 8);
    cur_buffer = buffer = av_malloc(*size);
    ଯଦି (!buffer)
        ଫେରନ୍ତୁ ଖାଲି;

    AV_WB32(cur_buffer,      info->scheme);
    AV_WB32(cur_buffer +  4, info->crypt_byte_block);
    AV_WB32(cur_buffer +  8, info->skip_byte_block);
    AV_WB32(cur_buffer + 12, info->ଚାବି_id_size);
    AV_WB32(cur_buffer + 16, info->iv_size);
    AV_WB32(cur_buffer + 20, info->subsample_ଗଣନା);
    cur_buffer += 24;
    memcpy(cur_buffer, info->ଚାବି_id, info->ଚାବି_id_size);
    cur_buffer += info->ଚାବି_id_size;
    memcpy(cur_buffer, info->iv, info->iv_size);
    cur_buffer += info->iv_size;
    ପାଇଁ (i = 0; i < info->subsample_ଗଣନା; i++) {
        AV_WB32(cur_buffer, info->subsamples[i].bytes_of_clear_data);
        AV_WB32(cur_buffer + 4, info->subsamples[i].bytes_of_protected_data);
        cur_buffer += 8;
    }

    ଫେରନ୍ତୁ buffer;
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
    uint32_t system_id_size, uint32_t ଅଙ୍କ_ଚାବି_ids, uint32_t ଚାବି_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    ଯଦି (ଅଙ୍କ_ଚାବି_ids && !ଚାବି_id_size)
        ଫେରନ୍ତୁ ଖାଲି;

    info = av_mallocz(ଆକାର(*info));
    ଯଦି (!info)
        ଫେରନ୍ତୁ ଖାଲି;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->ଚାବି_ids = ଚାବି_id_size ? av_calloc(ଅଙ୍କ_ଚାବି_ids, ଆକାର(*info->ଚାବି_ids)) : ଖାଲି;
    info->ଅଙ୍କ_ଚାବି_ids = ଅଙ୍କ_ଚାବି_ids;
    info->ଚାବି_id_size = ଚାବି_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    ଯଦି ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->ଚାବି_ids && ଅଙ୍କ_ଚାବି_ids && ଚାବି_id_size)) {
        av_encryption_init_info_free(info);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (ଚାବି_id_size) {
        ପାଇଁ (i = 0; i < ଅଙ୍କ_ଚାବି_ids; i++) {
            info->ଚାବି_ids[i] = av_mallocz(ଚାବି_id_size);
            ଯଦି (!info->ଚାବି_ids[i]) {
                av_encryption_init_info_free(info);
                ଫେରନ୍ତୁ ଖାଲି;
            }
        }
    }

    ଫେରନ୍ତୁ info;
}

ଶୂନ୍ୟ av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    ଯେତେବେଳେ (info) {
        AVEncryptionInitInfo *next = info->next;
        uint32_t i;

        ପାଇଁ (i = 0; i < info->ଅଙ୍କ_ଚାବି_ids; i++) {
            av_free(info->ଚାବି_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->ଚାବି_ids);
        av_free(info->data);
        av_free(info);

        info = next;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_data(
    ଅଚଳ uint8_t *side_data, size_t side_data_size)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = ଖାଲି, *info, *temp_info;
    uint64_t system_id_size, ଅଙ୍କ_ଚାବି_ids, ଚାବି_id_size, data_size, i, j;
    uint64_t init_info_ଗଣନା;

    ଯଦି (!side_data || side_data_size < 4)
        ଫେରନ୍ତୁ ଖାଲି;

    init_info_ଗଣନା = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    ପାଇଁ (i = 0; i < init_info_ଗଣନା; i++) {
        ଯଦି (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            ଫେରନ୍ତୁ ଖାଲି;
        }

        system_id_size = AV_RB32(side_data);
        ଅଙ୍କ_ଚାବି_ids = AV_RB32(side_data + 4);
        ଚାବି_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        ଯଦି (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + ଅଙ୍କ_ଚାବି_ids * ଚାବି_id_size) {
            av_encryption_init_info_free(ret);
            ଫେରନ୍ତୁ ଖାଲି;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, ଅଙ୍କ_ଚାବି_ids, ଚାବି_id_size, data_size);
        ଯଦି (!temp_info) {
            av_encryption_init_info_free(ret);
            ଫେରନ୍ତୁ ଖାଲି;
        }
        ଯଦି (i == 0) {
            info = ret = temp_info;
        } ଅନ୍ୟଥା {
            info->next = temp_info;
            info = temp_info;
        }

        memcpy(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        ପାଇଁ (j = 0; j < ଅଙ୍କ_ଚାବି_ids; j++) {
            memcpy(info->ଚାବି_ids[j], side_data, ଚାବି_id_size);
            side_data += ଚାବି_id_size;
            side_data_size -= ଚାବି_id_size;
        }
        memcpy(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_encryption_init_info_append_side_data(uint8_t **side_data, size_t *side_data_size,
                                             unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *allocated_size,
                                             ଅଚଳ AVEncryptionInitInfo *info)
{
    ଅଚଳ AVEncryptionInitInfo *cur_info;
    uint8_t *buffer, *cur_buffer;
    uint32_t i;
    uint64_t init_info_ଗଣନା    = *side_data ? AV_RB32(*side_data) : 0;
    size_t   old_side_data_size = *side_data ? *side_data_size : 4;
    uint64_t new_side_data_size = old_side_data_size;

    ପାଇଁ (cur_info = info; cur_info; cur_info = cur_info->next) {
        new_side_data_size += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_size + cur_info->data_size;
        ଯଦି (init_info_ଗଣନା == UINT32_MAX || new_side_data_size > UINT32_MAX)
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        init_info_ଗଣନା++;

        ଯଦି (cur_info->ଅଙ୍କ_ଚାବି_ids) {
            new_side_data_size += (uint64_t)cur_info->ଅଙ୍କ_ଚାବି_ids * cur_info->ଚାବି_id_size;
            ଯଦି (new_side_data_size > UINT32_MAX)
                ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
    }

    buffer = av_fast_realloc(*side_data, allocated_size, new_side_data_size);
    ଯଦି (!buffer)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    AV_WB32(buffer, init_info_ଗଣନା);
    cur_buffer = buffer + old_side_data_size;
    ପାଇଁ (cur_info = info; cur_info; cur_info = cur_info->next) {
        AV_WB32(cur_buffer,      cur_info->system_id_size);
        AV_WB32(cur_buffer +  4, cur_info->ଅଙ୍କ_ଚାବି_ids);
        AV_WB32(cur_buffer +  8, cur_info->ଚାବି_id_size);
        AV_WB32(cur_buffer + 12, cur_info->data_size);
        cur_buffer += 16;

        memcpy(cur_buffer, cur_info->system_id, cur_info->system_id_size);
        cur_buffer += cur_info->system_id_size;
        ପାଇଁ (i = 0; i < cur_info->ଅଙ୍କ_ଚାବି_ids; i++) {
            memcpy(cur_buffer, cur_info->ଚାବି_ids[i], cur_info->ଚାବି_id_size);
            cur_buffer += cur_info->ଚାବି_id_size;
        }
        ଯଦି (cur_info->data_size > 0) {
            memcpy(cur_buffer, cur_info->data, cur_info->data_size);
            cur_buffer += cur_info->data_size;
        }
    }

    *side_data      = buffer;
    *side_data_size = new_side_data_size;
    ଫେରନ୍ତୁ 0;
}

uint8_t *av_encryption_init_info_add_side_data(ଅଚଳ AVEncryptionInitInfo *info, size_t *side_data_size)
{
    uint8_t *side_data = ଖାଲି;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା allocated_size = 0;

    ଯଦି (av_encryption_init_info_append_side_data(&side_data, side_data_size, &allocated_size, info) < 0)
        ଫେରନ୍ତୁ ଖାଲି;
    ଫେରନ୍ତୁ side_data;
}
