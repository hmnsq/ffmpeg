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

#परिभाषय FF_ENCRYPTION_INFO_EXTRA 24

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_गणनम्, uint32_t कुञ्चिका_id_आकार, uint32_t iv_आकार)
{
    AVEncryptionInfo *info;

    info = av_mallocz(परिमाण(*info));
    यदि (!info)
        प्रत्यागम रिक्त;

    info->कुञ्चिका_id = av_mallocz(कुञ्चिका_id_आकार);
    info->कुञ्चिका_id_आकार = कुञ्चिका_id_आकार;
    info->iv = av_mallocz(iv_आकार);
    info->iv_आकार = iv_आकार;
    info->subsamples = av_calloc(subsample_गणनम्, परिमाण(*info->subsamples));
    info->subsample_गणनम् = subsample_गणनम्;

    // Allow info->subsamples to be NULL if there are no subsamples.
    यदि (!info->कुञ्चिका_id || !info->iv || (!info->subsamples && subsample_गणनम्)) {
        av_encryption_info_free(info);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम info;
}

AVEncryptionInfo *av_encryption_info_clone(ध्रुव AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_गणनम्, info->कुञ्चिका_id_आकार, info->iv_आकार);
    यदि (!ret)
        प्रत्यागम रिक्त;

    ret->scheme = info->scheme;
    ret->crypt_byte_खण्डम् = info->crypt_byte_खण्डम्;
    ret->skip_byte_खण्डम् = info->skip_byte_खण्डम्;
    स्मृतिं_प्रतिलिख(ret->iv, info->iv, info->iv_आकार);
    स्मृतिं_प्रतिलिख(ret->कुञ्चिका_id, info->कुञ्चिका_id, info->कुञ्चिका_id_आकार);
    स्मृतिं_प्रतिलिख(ret->subsamples, info->subsamples, परिमाण(*info->subsamples) * info->subsample_गणनम्);
    प्रत्यागम ret;
}

शून्य av_encryption_info_free(AVEncryptionInfo *info)
{
    यदि (info) {
        av_free(info->कुञ्चिका_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_दत्त(ध्रुव uint8_t* बफर, size_t आकार)
{
    AVEncryptionInfo *info;
    uint64_t कुञ्चिका_id_आकार, iv_आकार, subsample_गणनम्, i;

    यदि (!बफर || आकार < FF_ENCRYPTION_INFO_EXTRA)
        प्रत्यागम रिक्त;

    कुञ्चिका_id_आकार = AV_RB32(बफर + 12);
    iv_आकार = AV_RB32(बफर + 16);
    subsample_गणनम् = AV_RB32(बफर + 20);

    यदि (आकार < FF_ENCRYPTION_INFO_EXTRA + कुञ्चिका_id_आकार + iv_आकार + subsample_गणनम् * 8)
        प्रत्यागम रिक्त;

    info = av_encryption_info_alloc(subsample_गणनम्, कुञ्चिका_id_आकार, iv_आकार);
    यदि (!info)
        प्रत्यागम रिक्त;

    info->scheme = AV_RB32(बफर);
    info->crypt_byte_खण्डम् = AV_RB32(बफर + 4);
    info->skip_byte_खण्डम् = AV_RB32(बफर + 8);
    स्मृतिं_प्रतिलिख(info->कुञ्चिका_id, बफर + 24, कुञ्चिका_id_आकार);
    स्मृतिं_प्रतिलिख(info->iv, बफर + कुञ्चिका_id_आकार + 24, iv_आकार);

    बफर += कुञ्चिका_id_आकार + iv_आकार + 24;
    प्रति (i = 0; i < subsample_गणनम्; i++) {
        info->subsamples[i].अष्टकानि_सम्बन्धि_clear_दत्त = AV_RB32(बफर);
        info->subsamples[i].अष्टकानि_सम्बन्धि_protected_दत्त = AV_RB32(बफर + 4);
        बफर += 8;
    }

    प्रत्यागम info;
}

uint8_t *av_encryption_info_सङ्कलय_side_दत्त(ध्रुव AVEncryptionInfo *info, size_t *आकार)
{
    uint8_t *बफर, *cur_बफर;
    uint32_t i;

    यदि (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->कुञ्चिका_id_आकार ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->कुञ्चिका_id_आकार < info->iv_आकार ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->कुञ्चिका_id_आकार - info->iv_आकार) / 8 < info->subsample_गणनम्) {
        प्रत्यागम रिक्त;
    }

    *आकार = FF_ENCRYPTION_INFO_EXTRA + info->कुञ्चिका_id_आकार + info->iv_आकार +
            (info->subsample_गणनम् * 8);
    cur_बफर = बफर = av_malloc(*आकार);
    यदि (!बफर)
        प्रत्यागम रिक्त;

    AV_WB32(cur_बफर,      info->scheme);
    AV_WB32(cur_बफर +  4, info->crypt_byte_खण्डम्);
    AV_WB32(cur_बफर +  8, info->skip_byte_खण्डम्);
    AV_WB32(cur_बफर + 12, info->कुञ्चिका_id_आकार);
    AV_WB32(cur_बफर + 16, info->iv_आकार);
    AV_WB32(cur_बफर + 20, info->subsample_गणनम्);
    cur_बफर += 24;
    स्मृतिं_प्रतिलिख(cur_बफर, info->कुञ्चिका_id, info->कुञ्चिका_id_आकार);
    cur_बफर += info->कुञ्चिका_id_आकार;
    स्मृतिं_प्रतिलिख(cur_बफर, info->iv, info->iv_आकार);
    cur_बफर += info->iv_आकार;
    प्रति (i = 0; i < info->subsample_गणनम्; i++) {
        AV_WB32(cur_बफर, info->subsamples[i].अष्टकानि_सम्बन्धि_clear_दत्त);
        AV_WB32(cur_बफर + 4, info->subsamples[i].अष्टकानि_सम्बन्धि_protected_दत्त);
        cur_बफर += 8;
    }

    प्रत्यागम बफर;
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

#परिभाषय FF_ENCRYPTION_INIT_INFO_EXTRA 16

AVEncryptionInitInfo *av_encryption_init_info_alloc(
    uint32_t system_id_आकार, uint32_t अङ्कः_कुञ्चिका_ids, uint32_t कुञ्चिका_id_आकार, uint32_t दत्त_आकार)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    यदि (अङ्कः_कुञ्चिका_ids && !कुञ्चिका_id_आकार)
        प्रत्यागम रिक्त;

    info = av_mallocz(परिमाण(*info));
    यदि (!info)
        प्रत्यागम रिक्त;

    info->system_id = av_mallocz(system_id_आकार);
    info->system_id_आकार = system_id_आकार;
    info->कुञ्चिका_ids = कुञ्चिका_id_आकार ? av_calloc(अङ्कः_कुञ्चिका_ids, परिमाण(*info->कुञ्चिका_ids)) : रिक्त;
    info->अङ्कः_कुञ्चिका_ids = अङ्कः_कुञ्चिका_ids;
    info->कुञ्चिका_id_आकार = कुञ्चिका_id_आकार;
    info->दत्त = av_mallocz(दत्त_आकार);
    info->दत्त_आकार = दत्त_आकार;

    // Allow pointers to be NULL if the size is 0.
    यदि ((!info->system_id && system_id_आकार) || (!info->दत्त && दत्त_आकार) ||
        (!info->कुञ्चिका_ids && अङ्कः_कुञ्चिका_ids && कुञ्चिका_id_आकार)) {
        av_encryption_init_info_free(info);
        प्रत्यागम रिक्त;
    }

    यदि (कुञ्चिका_id_आकार) {
        प्रति (i = 0; i < अङ्कः_कुञ्चिका_ids; i++) {
            info->कुञ्चिका_ids[i] = av_mallocz(कुञ्चिका_id_आकार);
            यदि (!info->कुञ्चिका_ids[i]) {
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
        AVEncryptionInitInfo *अग्र = info->अग्र;
        uint32_t i;

        प्रति (i = 0; i < info->अङ्कः_कुञ्चिका_ids; i++) {
            av_free(info->कुञ्चिका_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->कुञ्चिका_ids);
        av_free(info->दत्त);
        av_free(info);

        info = अग्र;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_दत्त(
    ध्रुव uint8_t *side_दत्त, size_t side_दत्त_आकार)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = रिक्त, *info, *अस्थायी_info;
    uint64_t system_id_आकार, अङ्कः_कुञ्चिका_ids, कुञ्चिका_id_आकार, दत्त_आकार, i, j;
    uint64_t init_info_गणनम्;

    यदि (!side_दत्त || side_दत्त_आकार < 4)
        प्रत्यागम रिक्त;

    init_info_गणनम् = AV_RB32(side_दत्त);
    side_दत्त += 4;
    side_दत्त_आकार -= 4;
    प्रति (i = 0; i < init_info_गणनम्; i++) {
        यदि (side_दत्त_आकार < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            प्रत्यागम रिक्त;
        }

        system_id_आकार = AV_RB32(side_दत्त);
        अङ्कः_कुञ्चिका_ids = AV_RB32(side_दत्त + 4);
        कुञ्चिका_id_आकार = AV_RB32(side_दत्त + 8);
        दत्त_आकार = AV_RB32(side_दत्त + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        यदि (side_दत्त_आकार - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_आकार + दत्त_आकार + अङ्कः_कुञ्चिका_ids * कुञ्चिका_id_आकार) {
            av_encryption_init_info_free(ret);
            प्रत्यागम रिक्त;
        }
        side_दत्त += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_दत्त_आकार -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        अस्थायी_info = av_encryption_init_info_alloc(system_id_आकार, अङ्कः_कुञ्चिका_ids, कुञ्चिका_id_आकार, दत्त_आकार);
        यदि (!अस्थायी_info) {
            av_encryption_init_info_free(ret);
            प्रत्यागम रिक्त;
        }
        यदि (i == 0) {
            info = ret = अस्थायी_info;
        } अन्यथा {
            info->अग्र = अस्थायी_info;
            info = अस्थायी_info;
        }

        स्मृतिं_प्रतिलिख(info->system_id, side_दत्त, system_id_आकार);
        side_दत्त += system_id_आकार;
        side_दत्त_आकार -= system_id_आकार;
        प्रति (j = 0; j < अङ्कः_कुञ्चिका_ids; j++) {
            स्मृतिं_प्रतिलिख(info->कुञ्चिका_ids[j], side_दत्त, कुञ्चिका_id_आकार);
            side_दत्त += कुञ्चिका_id_आकार;
            side_दत्त_आकार -= कुञ्चिका_id_आकार;
        }
        स्मृतिं_प्रतिलिख(info->दत्त, side_दत्त, दत्त_आकार);
        side_दत्त += दत्त_आकार;
        side_दत्त_आकार -= दत्त_आकार;
    }

    प्रत्यागम ret;
}

पूर्णाङ्क av_encryption_init_info_append_side_दत्त(uint8_t **side_दत्त, size_t *side_दत्त_आकार,
                                             अचिह्नित पूर्णाङ्क *allocated_आकार,
                                             ध्रुव AVEncryptionInitInfo *info)
{
    ध्रुव AVEncryptionInitInfo *cur_info;
    uint8_t *बफर, *cur_बफर;
    uint32_t i;
    uint64_t init_info_गणनम्    = *side_दत्त ? AV_RB32(*side_दत्त) : 0;
    size_t   old_side_दत्त_आकार = *side_दत्त ? *side_दत्त_आकार : 4;
    uint64_t new_side_दत्त_आकार = old_side_दत्त_आकार;

    प्रति (cur_info = info; cur_info; cur_info = cur_info->अग्र) {
        new_side_दत्त_आकार += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_आकार + cur_info->दत्त_आकार;
        यदि (init_info_गणनम् == UINT32_MAX || new_side_दत्त_आकार > UINT32_MAX)
            प्रत्यागम AVERROR(EINVAL);
        init_info_गणनम्++;

        यदि (cur_info->अङ्कः_कुञ्चिका_ids) {
            new_side_दत्त_आकार += (uint64_t)cur_info->अङ्कः_कुञ्चिका_ids * cur_info->कुञ्चिका_id_आकार;
            यदि (new_side_दत्त_आकार > UINT32_MAX)
                प्रत्यागम AVERROR(EINVAL);
        }
    }

    बफर = av_fast_realloc(*side_दत्त, allocated_आकार, new_side_दत्त_आकार);
    यदि (!बफर)
        प्रत्यागम AVERROR(ENOMEM);

    AV_WB32(बफर, init_info_गणनम्);
    cur_बफर = बफर + old_side_दत्त_आकार;
    प्रति (cur_info = info; cur_info; cur_info = cur_info->अग्र) {
        AV_WB32(cur_बफर,      cur_info->system_id_आकार);
        AV_WB32(cur_बफर +  4, cur_info->अङ्कः_कुञ्चिका_ids);
        AV_WB32(cur_बफर +  8, cur_info->कुञ्चिका_id_आकार);
        AV_WB32(cur_बफर + 12, cur_info->दत्त_आकार);
        cur_बफर += 16;

        स्मृतिं_प्रतिलिख(cur_बफर, cur_info->system_id, cur_info->system_id_आकार);
        cur_बफर += cur_info->system_id_आकार;
        प्रति (i = 0; i < cur_info->अङ्कः_कुञ्चिका_ids; i++) {
            स्मृतिं_प्रतिलिख(cur_बफर, cur_info->कुञ्चिका_ids[i], cur_info->कुञ्चिका_id_आकार);
            cur_बफर += cur_info->कुञ्चिका_id_आकार;
        }
        यदि (cur_info->दत्त_आकार > 0) {
            स्मृतिं_प्रतिलिख(cur_बफर, cur_info->दत्त, cur_info->दत्त_आकार);
            cur_बफर += cur_info->दत्त_आकार;
        }
    }

    *side_दत्त      = बफर;
    *side_दत्त_आकार = new_side_दत्त_आकार;
    प्रत्यागम 0;
}

uint8_t *av_encryption_init_info_सङ्कलय_side_दत्त(ध्रुव AVEncryptionInitInfo *info, size_t *side_दत्त_आकार)
{
    uint8_t *side_दत्त = रिक्त;
    अचिह्नित पूर्णाङ्क allocated_आकार = 0;

    यदि (av_encryption_init_info_append_side_दत्त(&side_दत्त, side_दत्त_आकार, &allocated_आकार, info) < 0)
        प्रत्यागम रिक्त;
    प्रत्यागम side_दत्त;
}
