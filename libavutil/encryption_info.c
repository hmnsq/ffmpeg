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

#समावेश <string.h>

#समावेश "encryption_info.h"
#समावेश "error.h"
#समावेश "mem.h"
#समावेश "intreadwrite.h"

#घोषणा FF_ENCRYPTION_INFO_EXTRA 24

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_गिनती, uint32_t कुंजी_id_आकार, uint32_t iv_आकार)
{
    AVEncryptionInfo *info;

    info = av_mallocz(माप(*info));
    अगर (!info)
        वापस शून्य;

    info->कुंजी_id = av_mallocz(कुंजी_id_आकार);
    info->कुंजी_id_आकार = कुंजी_id_आकार;
    info->iv = av_mallocz(iv_आकार);
    info->iv_आकार = iv_आकार;
    info->subsamples = av_calloc(subsample_गिनती, माप(*info->subsamples));
    info->subsample_गिनती = subsample_गिनती;

    // Allow info->subsamples to be NULL if there are no subsamples.
    अगर (!info->कुंजी_id || !info->iv || (!info->subsamples && subsample_गिनती)) {
        av_encryption_info_free(info);
        वापस शून्य;
    }

    वापस info;
}

AVEncryptionInfo *av_encryption_info_clone(स्थिर AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_गिनती, info->कुंजी_id_आकार, info->iv_आकार);
    अगर (!ret)
        वापस शून्य;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    स_नकल(ret->iv, info->iv, info->iv_आकार);
    स_नकल(ret->कुंजी_id, info->कुंजी_id, info->कुंजी_id_आकार);
    स_नकल(ret->subsamples, info->subsamples, माप(*info->subsamples) * info->subsample_गिनती);
    वापस ret;
}

व्योम av_encryption_info_free(AVEncryptionInfo *info)
{
    अगर (info) {
        av_free(info->कुंजी_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_तथ्य(स्थिर uint8_t* बफर, माप_प्रकार आकार)
{
    AVEncryptionInfo *info;
    uint64_t कुंजी_id_आकार, iv_आकार, subsample_गिनती, i;

    अगर (!बफर || आकार < FF_ENCRYPTION_INFO_EXTRA)
        वापस शून्य;

    कुंजी_id_आकार = AV_RB32(बफर + 12);
    iv_आकार = AV_RB32(बफर + 16);
    subsample_गिनती = AV_RB32(बफर + 20);

    अगर (आकार < FF_ENCRYPTION_INFO_EXTRA + कुंजी_id_आकार + iv_आकार + subsample_गिनती * 8)
        वापस शून्य;

    info = av_encryption_info_alloc(subsample_गिनती, कुंजी_id_आकार, iv_आकार);
    अगर (!info)
        वापस शून्य;

    info->scheme = AV_RB32(बफर);
    info->crypt_byte_block = AV_RB32(बफर + 4);
    info->skip_byte_block = AV_RB32(बफर + 8);
    स_नकल(info->कुंजी_id, बफर + 24, कुंजी_id_आकार);
    स_नकल(info->iv, बफर + कुंजी_id_आकार + 24, iv_आकार);

    बफर += कुंजी_id_आकार + iv_आकार + 24;
    क्रम (i = 0; i < subsample_गिनती; i++) {
        info->subsamples[i].bytes_of_clear_तथ्य = AV_RB32(बफर);
        info->subsamples[i].bytes_of_protected_तथ्य = AV_RB32(बफर + 4);
        बफर += 8;
    }

    वापस info;
}

uint8_t *av_encryption_info_add_side_तथ्य(स्थिर AVEncryptionInfo *info, माप_प्रकार *आकार)
{
    uint8_t *बफर, *cur_बफर;
    uint32_t i;

    अगर (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->कुंजी_id_आकार ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->कुंजी_id_आकार < info->iv_आकार ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->कुंजी_id_आकार - info->iv_आकार) / 8 < info->subsample_गिनती) {
        वापस शून्य;
    }

    *आकार = FF_ENCRYPTION_INFO_EXTRA + info->कुंजी_id_आकार + info->iv_आकार +
            (info->subsample_गिनती * 8);
    cur_बफर = बफर = av_malloc(*आकार);
    अगर (!बफर)
        वापस शून्य;

    AV_WB32(cur_बफर,      info->scheme);
    AV_WB32(cur_बफर +  4, info->crypt_byte_block);
    AV_WB32(cur_बफर +  8, info->skip_byte_block);
    AV_WB32(cur_बफर + 12, info->कुंजी_id_आकार);
    AV_WB32(cur_बफर + 16, info->iv_आकार);
    AV_WB32(cur_बफर + 20, info->subsample_गिनती);
    cur_बफर += 24;
    स_नकल(cur_बफर, info->कुंजी_id, info->कुंजी_id_आकार);
    cur_बफर += info->कुंजी_id_आकार;
    स_नकल(cur_बफर, info->iv, info->iv_आकार);
    cur_बफर += info->iv_आकार;
    क्रम (i = 0; i < info->subsample_गिनती; i++) {
        AV_WB32(cur_बफर, info->subsamples[i].bytes_of_clear_तथ्य);
        AV_WB32(cur_बफर + 4, info->subsamples[i].bytes_of_protected_तथ्य);
        cur_बफर += 8;
    }

    वापस बफर;
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

#घोषणा FF_ENCRYPTION_INIT_INFO_EXTRA 16

AVEncryptionInitInfo *av_encryption_init_info_alloc(
    uint32_t system_id_आकार, uint32_t अंक_कुंजी_ids, uint32_t कुंजी_id_आकार, uint32_t तथ्य_आकार)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    अगर (अंक_कुंजी_ids && !कुंजी_id_आकार)
        वापस शून्य;

    info = av_mallocz(माप(*info));
    अगर (!info)
        वापस शून्य;

    info->system_id = av_mallocz(system_id_आकार);
    info->system_id_आकार = system_id_आकार;
    info->कुंजी_ids = कुंजी_id_आकार ? av_calloc(अंक_कुंजी_ids, माप(*info->कुंजी_ids)) : शून्य;
    info->अंक_कुंजी_ids = अंक_कुंजी_ids;
    info->कुंजी_id_आकार = कुंजी_id_आकार;
    info->तथ्य = av_mallocz(तथ्य_आकार);
    info->तथ्य_आकार = तथ्य_आकार;

    // Allow pointers to be NULL if the size is 0.
    अगर ((!info->system_id && system_id_आकार) || (!info->तथ्य && तथ्य_आकार) ||
        (!info->कुंजी_ids && अंक_कुंजी_ids && कुंजी_id_आकार)) {
        av_encryption_init_info_free(info);
        वापस शून्य;
    }

    अगर (कुंजी_id_आकार) {
        क्रम (i = 0; i < अंक_कुंजी_ids; i++) {
            info->कुंजी_ids[i] = av_mallocz(कुंजी_id_आकार);
            अगर (!info->कुंजी_ids[i]) {
                av_encryption_init_info_free(info);
                वापस शून्य;
            }
        }
    }

    वापस info;
}

व्योम av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    जबतक (info) {
        AVEncryptionInitInfo *अग्र = info->अग्र;
        uint32_t i;

        क्रम (i = 0; i < info->अंक_कुंजी_ids; i++) {
            av_free(info->कुंजी_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->कुंजी_ids);
        av_free(info->तथ्य);
        av_free(info);

        info = अग्र;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_तथ्य(
    स्थिर uint8_t *side_तथ्य, माप_प्रकार side_तथ्य_आकार)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = शून्य, *info, *अस्थायी_info;
    uint64_t system_id_आकार, अंक_कुंजी_ids, कुंजी_id_आकार, तथ्य_आकार, i, j;
    uint64_t init_info_गिनती;

    अगर (!side_तथ्य || side_तथ्य_आकार < 4)
        वापस शून्य;

    init_info_गिनती = AV_RB32(side_तथ्य);
    side_तथ्य += 4;
    side_तथ्य_आकार -= 4;
    क्रम (i = 0; i < init_info_गिनती; i++) {
        अगर (side_तथ्य_आकार < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            वापस शून्य;
        }

        system_id_आकार = AV_RB32(side_तथ्य);
        अंक_कुंजी_ids = AV_RB32(side_तथ्य + 4);
        कुंजी_id_आकार = AV_RB32(side_तथ्य + 8);
        तथ्य_आकार = AV_RB32(side_तथ्य + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        अगर (side_तथ्य_आकार - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_आकार + तथ्य_आकार + अंक_कुंजी_ids * कुंजी_id_आकार) {
            av_encryption_init_info_free(ret);
            वापस शून्य;
        }
        side_तथ्य += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_तथ्य_आकार -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        अस्थायी_info = av_encryption_init_info_alloc(system_id_आकार, अंक_कुंजी_ids, कुंजी_id_आकार, तथ्य_आकार);
        अगर (!अस्थायी_info) {
            av_encryption_init_info_free(ret);
            वापस शून्य;
        }
        अगर (i == 0) {
            info = ret = अस्थायी_info;
        } अन्यथा {
            info->अग्र = अस्थायी_info;
            info = अस्थायी_info;
        }

        स_नकल(info->system_id, side_तथ्य, system_id_आकार);
        side_तथ्य += system_id_आकार;
        side_तथ्य_आकार -= system_id_आकार;
        क्रम (j = 0; j < अंक_कुंजी_ids; j++) {
            स_नकल(info->कुंजी_ids[j], side_तथ्य, कुंजी_id_आकार);
            side_तथ्य += कुंजी_id_आकार;
            side_तथ्य_आकार -= कुंजी_id_आकार;
        }
        स_नकल(info->तथ्य, side_तथ्य, तथ्य_आकार);
        side_तथ्य += तथ्य_आकार;
        side_तथ्य_आकार -= तथ्य_आकार;
    }

    वापस ret;
}

पूर्णांक av_encryption_init_info_append_side_तथ्य(uint8_t **side_तथ्य, माप_प्रकार *side_तथ्य_आकार,
                                             अचिन्हित पूर्णांक *allocated_आकार,
                                             स्थिर AVEncryptionInitInfo *info)
{
    स्थिर AVEncryptionInitInfo *cur_info;
    uint8_t *बफर, *cur_बफर;
    uint32_t i;
    uint64_t init_info_गिनती    = *side_तथ्य ? AV_RB32(*side_तथ्य) : 0;
    माप_प्रकार   old_side_तथ्य_आकार = *side_तथ्य ? *side_तथ्य_आकार : 4;
    uint64_t new_side_तथ्य_आकार = old_side_तथ्य_आकार;

    क्रम (cur_info = info; cur_info; cur_info = cur_info->अग्र) {
        new_side_तथ्य_आकार += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_आकार + cur_info->तथ्य_आकार;
        अगर (init_info_गिनती == UINT32_MAX || new_side_तथ्य_आकार > UINT32_MAX)
            वापस AVERROR(EINVAL);
        init_info_गिनती++;

        अगर (cur_info->अंक_कुंजी_ids) {
            new_side_तथ्य_आकार += (uint64_t)cur_info->अंक_कुंजी_ids * cur_info->कुंजी_id_आकार;
            अगर (new_side_तथ्य_आकार > UINT32_MAX)
                वापस AVERROR(EINVAL);
        }
    }

    बफर = av_fast_realloc(*side_तथ्य, allocated_आकार, new_side_तथ्य_आकार);
    अगर (!बफर)
        वापस AVERROR(ENOMEM);

    AV_WB32(बफर, init_info_गिनती);
    cur_बफर = बफर + old_side_तथ्य_आकार;
    क्रम (cur_info = info; cur_info; cur_info = cur_info->अग्र) {
        AV_WB32(cur_बफर,      cur_info->system_id_आकार);
        AV_WB32(cur_बफर +  4, cur_info->अंक_कुंजी_ids);
        AV_WB32(cur_बफर +  8, cur_info->कुंजी_id_आकार);
        AV_WB32(cur_बफर + 12, cur_info->तथ्य_आकार);
        cur_बफर += 16;

        स_नकल(cur_बफर, cur_info->system_id, cur_info->system_id_आकार);
        cur_बफर += cur_info->system_id_आकार;
        क्रम (i = 0; i < cur_info->अंक_कुंजी_ids; i++) {
            स_नकल(cur_बफर, cur_info->कुंजी_ids[i], cur_info->कुंजी_id_आकार);
            cur_बफर += cur_info->कुंजी_id_आकार;
        }
        अगर (cur_info->तथ्य_आकार > 0) {
            स_नकल(cur_बफर, cur_info->तथ्य, cur_info->तथ्य_आकार);
            cur_बफर += cur_info->तथ्य_आकार;
        }
    }

    *side_तथ्य      = बफर;
    *side_तथ्य_आकार = new_side_तथ्य_आकार;
    वापस 0;
}

uint8_t *av_encryption_init_info_add_side_तथ्य(स्थिर AVEncryptionInitInfo *info, माप_प्रकार *side_तथ्य_आकार)
{
    uint8_t *side_तथ्य = शून्य;
    अचिन्हित पूर्णांक allocated_आकार = 0;

    अगर (av_encryption_init_info_append_side_तथ्य(&side_तथ्य, side_तथ्य_आकार, &allocated_आकार, info) < 0)
        वापस शून्य;
    वापस side_तथ्य;
}
