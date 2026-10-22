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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_गन्ती, uint32_t साँचो_id_size, uint32_t iv_size)
{
    AVEncryptionInfo *info;

    info = av_mallocz(परिमाण(*info));
    यदि (!info)
        फर्काऊ रिक्त;

    info->साँचो_id = av_mallocz(साँचो_id_size);
    info->साँचो_id_size = साँचो_id_size;
    info->iv = av_mallocz(iv_size);
    info->iv_size = iv_size;
    info->subsamples = av_calloc(subsample_गन्ती, परिमाण(*info->subsamples));
    info->subsample_गन्ती = subsample_गन्ती;

    // Allow info->subsamples to be NULL if there are no subsamples.
    यदि (!info->साँचो_id || !info->iv || (!info->subsamples && subsample_गन्ती)) {
        av_encryption_info_free(info);
        फर्काऊ रिक्त;
    }

    फर्काऊ info;
}

AVEncryptionInfo *av_encryption_info_clone(अचर AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_गन्ती, info->साँचो_id_size, info->iv_size);
    यदि (!ret)
        फर्काऊ रिक्त;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    स_नकल(ret->iv, info->iv, info->iv_size);
    स_नकल(ret->साँचो_id, info->साँचो_id, info->साँचो_id_size);
    स_नकल(ret->subsamples, info->subsamples, परिमाण(*info->subsamples) * info->subsample_गन्ती);
    फर्काऊ ret;
}

शून्य av_encryption_info_free(AVEncryptionInfo *info)
{
    यदि (info) {
        av_free(info->साँचो_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_data(अचर uint8_t* buffer, माप_प्रकार size)
{
    AVEncryptionInfo *info;
    uint64_t साँचो_id_size, iv_size, subsample_गन्ती, i;

    यदि (!buffer || size < FF_ENCRYPTION_INFO_EXTRA)
        फर्काऊ रिक्त;

    साँचो_id_size = AV_RB32(buffer + 12);
    iv_size = AV_RB32(buffer + 16);
    subsample_गन्ती = AV_RB32(buffer + 20);

    यदि (size < FF_ENCRYPTION_INFO_EXTRA + साँचो_id_size + iv_size + subsample_गन्ती * 8)
        फर्काऊ रिक्त;

    info = av_encryption_info_alloc(subsample_गन्ती, साँचो_id_size, iv_size);
    यदि (!info)
        फर्काऊ रिक्त;

    info->scheme = AV_RB32(buffer);
    info->crypt_byte_block = AV_RB32(buffer + 4);
    info->skip_byte_block = AV_RB32(buffer + 8);
    स_नकल(info->साँचो_id, buffer + 24, साँचो_id_size);
    स_नकल(info->iv, buffer + साँचो_id_size + 24, iv_size);

    buffer += साँचो_id_size + iv_size + 24;
    लागि (i = 0; i < subsample_गन्ती; i++) {
        info->subsamples[i].bytes_of_clear_data = AV_RB32(buffer);
        info->subsamples[i].bytes_of_protected_data = AV_RB32(buffer + 4);
        buffer += 8;
    }

    फर्काऊ info;
}

uint8_t *av_encryption_info_add_side_data(अचर AVEncryptionInfo *info, माप_प्रकार *size)
{
    uint8_t *buffer, *cur_buffer;
    uint32_t i;

    यदि (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->साँचो_id_size ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->साँचो_id_size < info->iv_size ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->साँचो_id_size - info->iv_size) / 8 < info->subsample_गन्ती) {
        फर्काऊ रिक्त;
    }

    *size = FF_ENCRYPTION_INFO_EXTRA + info->साँचो_id_size + info->iv_size +
            (info->subsample_गन्ती * 8);
    cur_buffer = buffer = av_malloc(*size);
    यदि (!buffer)
        फर्काऊ रिक्त;

    AV_WB32(cur_buffer,      info->scheme);
    AV_WB32(cur_buffer +  4, info->crypt_byte_block);
    AV_WB32(cur_buffer +  8, info->skip_byte_block);
    AV_WB32(cur_buffer + 12, info->साँचो_id_size);
    AV_WB32(cur_buffer + 16, info->iv_size);
    AV_WB32(cur_buffer + 20, info->subsample_गन्ती);
    cur_buffer += 24;
    स_नकल(cur_buffer, info->साँचो_id, info->साँचो_id_size);
    cur_buffer += info->साँचो_id_size;
    स_नकल(cur_buffer, info->iv, info->iv_size);
    cur_buffer += info->iv_size;
    लागि (i = 0; i < info->subsample_गन्ती; i++) {
        AV_WB32(cur_buffer, info->subsamples[i].bytes_of_clear_data);
        AV_WB32(cur_buffer + 4, info->subsamples[i].bytes_of_protected_data);
        cur_buffer += 8;
    }

    फर्काऊ buffer;
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
    uint32_t system_id_size, uint32_t अङ्क_साँचो_ids, uint32_t साँचो_id_size, uint32_t data_size)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    यदि (अङ्क_साँचो_ids && !साँचो_id_size)
        फर्काऊ रिक्त;

    info = av_mallocz(परिमाण(*info));
    यदि (!info)
        फर्काऊ रिक्त;

    info->system_id = av_mallocz(system_id_size);
    info->system_id_size = system_id_size;
    info->साँचो_ids = साँचो_id_size ? av_calloc(अङ्क_साँचो_ids, परिमाण(*info->साँचो_ids)) : रिक्त;
    info->अङ्क_साँचो_ids = अङ्क_साँचो_ids;
    info->साँचो_id_size = साँचो_id_size;
    info->data = av_mallocz(data_size);
    info->data_size = data_size;

    // Allow pointers to be NULL if the size is 0.
    यदि ((!info->system_id && system_id_size) || (!info->data && data_size) ||
        (!info->साँचो_ids && अङ्क_साँचो_ids && साँचो_id_size)) {
        av_encryption_init_info_free(info);
        फर्काऊ रिक्त;
    }

    यदि (साँचो_id_size) {
        लागि (i = 0; i < अङ्क_साँचो_ids; i++) {
            info->साँचो_ids[i] = av_mallocz(साँचो_id_size);
            यदि (!info->साँचो_ids[i]) {
                av_encryption_init_info_free(info);
                फर्काऊ रिक्त;
            }
        }
    }

    फर्काऊ info;
}

शून्य av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    जबसम्म (info) {
        AVEncryptionInitInfo *next = info->next;
        uint32_t i;

        लागि (i = 0; i < info->अङ्क_साँचो_ids; i++) {
            av_free(info->साँचो_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->साँचो_ids);
        av_free(info->data);
        av_free(info);

        info = next;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_data(
    अचर uint8_t *side_data, माप_प्रकार side_data_size)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = रिक्त, *info, *temp_info;
    uint64_t system_id_size, अङ्क_साँचो_ids, साँचो_id_size, data_size, i, j;
    uint64_t init_info_गन्ती;

    यदि (!side_data || side_data_size < 4)
        फर्काऊ रिक्त;

    init_info_गन्ती = AV_RB32(side_data);
    side_data += 4;
    side_data_size -= 4;
    लागि (i = 0; i < init_info_गन्ती; i++) {
        यदि (side_data_size < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            फर्काऊ रिक्त;
        }

        system_id_size = AV_RB32(side_data);
        अङ्क_साँचो_ids = AV_RB32(side_data + 4);
        साँचो_id_size = AV_RB32(side_data + 8);
        data_size = AV_RB32(side_data + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        यदि (side_data_size - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_size + data_size + अङ्क_साँचो_ids * साँचो_id_size) {
            av_encryption_init_info_free(ret);
            फर्काऊ रिक्त;
        }
        side_data += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_data_size -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        temp_info = av_encryption_init_info_alloc(system_id_size, अङ्क_साँचो_ids, साँचो_id_size, data_size);
        यदि (!temp_info) {
            av_encryption_init_info_free(ret);
            फर्काऊ रिक्त;
        }
        यदि (i == 0) {
            info = ret = temp_info;
        } अन्यथा {
            info->next = temp_info;
            info = temp_info;
        }

        स_नकल(info->system_id, side_data, system_id_size);
        side_data += system_id_size;
        side_data_size -= system_id_size;
        लागि (j = 0; j < अङ्क_साँचो_ids; j++) {
            स_नकल(info->साँचो_ids[j], side_data, साँचो_id_size);
            side_data += साँचो_id_size;
            side_data_size -= साँचो_id_size;
        }
        स_नकल(info->data, side_data, data_size);
        side_data += data_size;
        side_data_size -= data_size;
    }

    फर्काऊ ret;
}

पूर्णाङ्क av_encryption_init_info_append_side_data(uint8_t **side_data, माप_प्रकार *side_data_size,
                                             अचिन्हित पूर्णाङ्क *allocated_size,
                                             अचर AVEncryptionInitInfo *info)
{
    अचर AVEncryptionInitInfo *cur_info;
    uint8_t *buffer, *cur_buffer;
    uint32_t i;
    uint64_t init_info_गन्ती    = *side_data ? AV_RB32(*side_data) : 0;
    माप_प्रकार   old_side_data_size = *side_data ? *side_data_size : 4;
    uint64_t new_side_data_size = old_side_data_size;

    लागि (cur_info = info; cur_info; cur_info = cur_info->next) {
        new_side_data_size += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_size + cur_info->data_size;
        यदि (init_info_गन्ती == UINT32_MAX || new_side_data_size > UINT32_MAX)
            फर्काऊ AVERROR(EINVAL);
        init_info_गन्ती++;

        यदि (cur_info->अङ्क_साँचो_ids) {
            new_side_data_size += (uint64_t)cur_info->अङ्क_साँचो_ids * cur_info->साँचो_id_size;
            यदि (new_side_data_size > UINT32_MAX)
                फर्काऊ AVERROR(EINVAL);
        }
    }

    buffer = av_fast_realloc(*side_data, allocated_size, new_side_data_size);
    यदि (!buffer)
        फर्काऊ AVERROR(ENOMEM);

    AV_WB32(buffer, init_info_गन्ती);
    cur_buffer = buffer + old_side_data_size;
    लागि (cur_info = info; cur_info; cur_info = cur_info->next) {
        AV_WB32(cur_buffer,      cur_info->system_id_size);
        AV_WB32(cur_buffer +  4, cur_info->अङ्क_साँचो_ids);
        AV_WB32(cur_buffer +  8, cur_info->साँचो_id_size);
        AV_WB32(cur_buffer + 12, cur_info->data_size);
        cur_buffer += 16;

        स_नकल(cur_buffer, cur_info->system_id, cur_info->system_id_size);
        cur_buffer += cur_info->system_id_size;
        लागि (i = 0; i < cur_info->अङ्क_साँचो_ids; i++) {
            स_नकल(cur_buffer, cur_info->साँचो_ids[i], cur_info->साँचो_id_size);
            cur_buffer += cur_info->साँचो_id_size;
        }
        यदि (cur_info->data_size > 0) {
            स_नकल(cur_buffer, cur_info->data, cur_info->data_size);
            cur_buffer += cur_info->data_size;
        }
    }

    *side_data      = buffer;
    *side_data_size = new_side_data_size;
    फर्काऊ 0;
}

uint8_t *av_encryption_init_info_add_side_data(अचर AVEncryptionInitInfo *info, माप_प्रकार *side_data_size)
{
    uint8_t *side_data = रिक्त;
    अचिन्हित पूर्णाङ्क allocated_size = 0;

    यदि (av_encryption_init_info_append_side_data(&side_data, side_data_size, &allocated_size, info) < 0)
        फर्काऊ रिक्त;
    फर्काऊ side_data;
}
