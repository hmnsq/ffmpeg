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

#అన్తర్భావ <string.h>

#అన్తర్భావ "encryption_info.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "intreadwrite.h"

#నిర్వచించు FF_ENCRYPTION_INFO_EXTRA 24

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_లెక్క, uint32_t కీలకం_id_కొలత, uint32_t iv_కొలత)
{
    AVEncryptionInfo *info;

    info = av_mallocz(పరిమాణం(*info));
    ఒకవేళ (!info)
        తిరిగి ఖాళీ;

    info->కీలకం_id = av_mallocz(కీలకం_id_కొలత);
    info->కీలకం_id_కొలత = కీలకం_id_కొలత;
    info->iv = av_mallocz(iv_కొలత);
    info->iv_కొలత = iv_కొలత;
    info->subsamples = av_calloc(subsample_లెక్క, పరిమాణం(*info->subsamples));
    info->subsample_లెక్క = subsample_లెక్క;

    // Allow info->subsamples to be NULL if there are no subsamples.
    ఒకవేళ (!info->కీలకం_id || !info->iv || (!info->subsamples && subsample_లెక్క)) {
        av_encryption_info_free(info);
        తిరిగి ఖాళీ;
    }

    తిరిగి info;
}

AVEncryptionInfo *av_encryption_info_clone(స్థిరరాశి AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_లెక్క, info->కీలకం_id_కొలత, info->iv_కొలత);
    ఒకవేళ (!ret)
        తిరిగి ఖాళీ;

    ret->scheme = info->scheme;
    ret->crypt_byte_ఖండం = info->crypt_byte_ఖండం;
    ret->skip_byte_ఖండం = info->skip_byte_ఖండం;
    జ్ఞాపకం_నకలు(ret->iv, info->iv, info->iv_కొలత);
    జ్ఞాపకం_నకలు(ret->కీలకం_id, info->కీలకం_id, info->కీలకం_id_కొలత);
    జ్ఞాపకం_నకలు(ret->subsamples, info->subsamples, పరిమాణం(*info->subsamples) * info->subsample_లెక్క);
    తిరిగి ret;
}

శూన్య av_encryption_info_free(AVEncryptionInfo *info)
{
    ఒకవేళ (info) {
        av_free(info->కీలకం_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_దత్తాంశం(స్థిరరాశి uint8_t* బఫరు, size_t కొలత)
{
    AVEncryptionInfo *info;
    uint64_t కీలకం_id_కొలత, iv_కొలత, subsample_లెక్క, i;

    ఒకవేళ (!బఫరు || కొలత < FF_ENCRYPTION_INFO_EXTRA)
        తిరిగి ఖాళీ;

    కీలకం_id_కొలత = AV_RB32(బఫరు + 12);
    iv_కొలత = AV_RB32(బఫరు + 16);
    subsample_లెక్క = AV_RB32(బఫరు + 20);

    ఒకవేళ (కొలత < FF_ENCRYPTION_INFO_EXTRA + కీలకం_id_కొలత + iv_కొలత + subsample_లెక్క * 8)
        తిరిగి ఖాళీ;

    info = av_encryption_info_alloc(subsample_లెక్క, కీలకం_id_కొలత, iv_కొలత);
    ఒకవేళ (!info)
        తిరిగి ఖాళీ;

    info->scheme = AV_RB32(బఫరు);
    info->crypt_byte_ఖండం = AV_RB32(బఫరు + 4);
    info->skip_byte_ఖండం = AV_RB32(బఫరు + 8);
    జ్ఞాపకం_నకలు(info->కీలకం_id, బఫరు + 24, కీలకం_id_కొలత);
    జ్ఞాపకం_నకలు(info->iv, బఫరు + కీలకం_id_కొలత + 24, iv_కొలత);

    బఫరు += కీలకం_id_కొలత + iv_కొలత + 24;
    కొరకు (i = 0; i < subsample_లెక్క; i++) {
        info->subsamples[i].బైట్లు_యొక్క_clear_దత్తాంశం = AV_RB32(బఫరు);
        info->subsamples[i].బైట్లు_యొక్క_protected_దత్తాంశం = AV_RB32(బఫరు + 4);
        బఫరు += 8;
    }

    తిరిగి info;
}

uint8_t *av_encryption_info_కూడు_side_దత్తాంశం(స్థిరరాశి AVEncryptionInfo *info, size_t *కొలత)
{
    uint8_t *బఫరు, *cur_బఫరు;
    uint32_t i;

    ఒకవేళ (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->కీలకం_id_కొలత ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->కీలకం_id_కొలత < info->iv_కొలత ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->కీలకం_id_కొలత - info->iv_కొలత) / 8 < info->subsample_లెక్క) {
        తిరిగి ఖాళీ;
    }

    *కొలత = FF_ENCRYPTION_INFO_EXTRA + info->కీలకం_id_కొలత + info->iv_కొలత +
            (info->subsample_లెక్క * 8);
    cur_బఫరు = బఫరు = av_malloc(*కొలత);
    ఒకవేళ (!బఫరు)
        తిరిగి ఖాళీ;

    AV_WB32(cur_బఫరు,      info->scheme);
    AV_WB32(cur_బఫరు +  4, info->crypt_byte_ఖండం);
    AV_WB32(cur_బఫరు +  8, info->skip_byte_ఖండం);
    AV_WB32(cur_బఫరు + 12, info->కీలకం_id_కొలత);
    AV_WB32(cur_బఫరు + 16, info->iv_కొలత);
    AV_WB32(cur_బఫరు + 20, info->subsample_లెక్క);
    cur_బఫరు += 24;
    జ్ఞాపకం_నకలు(cur_బఫరు, info->కీలకం_id, info->కీలకం_id_కొలత);
    cur_బఫరు += info->కీలకం_id_కొలత;
    జ్ఞాపకం_నకలు(cur_బఫరు, info->iv, info->iv_కొలత);
    cur_బఫరు += info->iv_కొలత;
    కొరకు (i = 0; i < info->subsample_లెక్క; i++) {
        AV_WB32(cur_బఫరు, info->subsamples[i].బైట్లు_యొక్క_clear_దత్తాంశం);
        AV_WB32(cur_బఫరు + 4, info->subsamples[i].బైట్లు_యొక్క_protected_దత్తాంశం);
        cur_బఫరు += 8;
    }

    తిరిగి బఫరు;
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

#నిర్వచించు FF_ENCRYPTION_INIT_INFO_EXTRA 16

AVEncryptionInitInfo *av_encryption_init_info_alloc(
    uint32_t system_id_కొలత, uint32_t అంకె_కీలకం_ids, uint32_t కీలకం_id_కొలత, uint32_t దత్తాంశం_కొలత)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    ఒకవేళ (అంకె_కీలకం_ids && !కీలకం_id_కొలత)
        తిరిగి ఖాళీ;

    info = av_mallocz(పరిమాణం(*info));
    ఒకవేళ (!info)
        తిరిగి ఖాళీ;

    info->system_id = av_mallocz(system_id_కొలత);
    info->system_id_కొలత = system_id_కొలత;
    info->కీలకం_ids = కీలకం_id_కొలత ? av_calloc(అంకె_కీలకం_ids, పరిమాణం(*info->కీలకం_ids)) : ఖాళీ;
    info->అంకె_కీలకం_ids = అంకె_కీలకం_ids;
    info->కీలకం_id_కొలత = కీలకం_id_కొలత;
    info->దత్తాంశం = av_mallocz(దత్తాంశం_కొలత);
    info->దత్తాంశం_కొలత = దత్తాంశం_కొలత;

    // Allow pointers to be NULL if the size is 0.
    ఒకవేళ ((!info->system_id && system_id_కొలత) || (!info->దత్తాంశం && దత్తాంశం_కొలత) ||
        (!info->కీలకం_ids && అంకె_కీలకం_ids && కీలకం_id_కొలత)) {
        av_encryption_init_info_free(info);
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (కీలకం_id_కొలత) {
        కొరకు (i = 0; i < అంకె_కీలకం_ids; i++) {
            info->కీలకం_ids[i] = av_mallocz(కీలకం_id_కొలత);
            ఒకవేళ (!info->కీలకం_ids[i]) {
                av_encryption_init_info_free(info);
                తిరిగి ఖాళీ;
            }
        }
    }

    తిరిగి info;
}

శూన్య av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    అయితే (info) {
        AVEncryptionInitInfo *తదుపరి = info->తదుపరి;
        uint32_t i;

        కొరకు (i = 0; i < info->అంకె_కీలకం_ids; i++) {
            av_free(info->కీలకం_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->కీలకం_ids);
        av_free(info->దత్తాంశం);
        av_free(info);

        info = తదుపరి;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_దత్తాంశం(
    స్థిరరాశి uint8_t *side_దత్తాంశం, size_t side_దత్తాంశం_కొలత)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = ఖాళీ, *info, *తాత్కాలిక_info;
    uint64_t system_id_కొలత, అంకె_కీలకం_ids, కీలకం_id_కొలత, దత్తాంశం_కొలత, i, j;
    uint64_t init_info_లెక్క;

    ఒకవేళ (!side_దత్తాంశం || side_దత్తాంశం_కొలత < 4)
        తిరిగి ఖాళీ;

    init_info_లెక్క = AV_RB32(side_దత్తాంశం);
    side_దత్తాంశం += 4;
    side_దత్తాంశం_కొలత -= 4;
    కొరకు (i = 0; i < init_info_లెక్క; i++) {
        ఒకవేళ (side_దత్తాంశం_కొలత < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            తిరిగి ఖాళీ;
        }

        system_id_కొలత = AV_RB32(side_దత్తాంశం);
        అంకె_కీలకం_ids = AV_RB32(side_దత్తాంశం + 4);
        కీలకం_id_కొలత = AV_RB32(side_దత్తాంశం + 8);
        దత్తాంశం_కొలత = AV_RB32(side_దత్తాంశం + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        ఒకవేళ (side_దత్తాంశం_కొలత - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_కొలత + దత్తాంశం_కొలత + అంకె_కీలకం_ids * కీలకం_id_కొలత) {
            av_encryption_init_info_free(ret);
            తిరిగి ఖాళీ;
        }
        side_దత్తాంశం += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_దత్తాంశం_కొలత -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        తాత్కాలిక_info = av_encryption_init_info_alloc(system_id_కొలత, అంకె_కీలకం_ids, కీలకం_id_కొలత, దత్తాంశం_కొలత);
        ఒకవేళ (!తాత్కాలిక_info) {
            av_encryption_init_info_free(ret);
            తిరిగి ఖాళీ;
        }
        ఒకవేళ (i == 0) {
            info = ret = తాత్కాలిక_info;
        } లేకపోతే {
            info->తదుపరి = తాత్కాలిక_info;
            info = తాత్కాలిక_info;
        }

        జ్ఞాపకం_నకలు(info->system_id, side_దత్తాంశం, system_id_కొలత);
        side_దత్తాంశం += system_id_కొలత;
        side_దత్తాంశం_కొలత -= system_id_కొలత;
        కొరకు (j = 0; j < అంకె_కీలకం_ids; j++) {
            జ్ఞాపకం_నకలు(info->కీలకం_ids[j], side_దత్తాంశం, కీలకం_id_కొలత);
            side_దత్తాంశం += కీలకం_id_కొలత;
            side_దత్తాంశం_కొలత -= కీలకం_id_కొలత;
        }
        జ్ఞాపకం_నకలు(info->దత్తాంశం, side_దత్తాంశం, దత్తాంశం_కొలత);
        side_దత్తాంశం += దత్తాంశం_కొలత;
        side_దత్తాంశం_కొలత -= దత్తాంశం_కొలత;
    }

    తిరిగి ret;
}

పూర్ణాంకం av_encryption_init_info_append_side_దత్తాంశం(uint8_t **side_దత్తాంశం, size_t *side_దత్తాంశం_కొలత,
                                             గుర్తులేని పూర్ణాంకం *allocated_కొలత,
                                             స్థిరరాశి AVEncryptionInitInfo *info)
{
    స్థిరరాశి AVEncryptionInitInfo *cur_info;
    uint8_t *బఫరు, *cur_బఫరు;
    uint32_t i;
    uint64_t init_info_లెక్క    = *side_దత్తాంశం ? AV_RB32(*side_దత్తాంశం) : 0;
    size_t   old_side_దత్తాంశం_కొలత = *side_దత్తాంశం ? *side_దత్తాంశం_కొలత : 4;
    uint64_t new_side_దత్తాంశం_కొలత = old_side_దత్తాంశం_కొలత;

    కొరకు (cur_info = info; cur_info; cur_info = cur_info->తదుపరి) {
        new_side_దత్తాంశం_కొలత += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_కొలత + cur_info->దత్తాంశం_కొలత;
        ఒకవేళ (init_info_లెక్క == UINT32_MAX || new_side_దత్తాంశం_కొలత > UINT32_MAX)
            తిరిగి AVERROR(EINVAL);
        init_info_లెక్క++;

        ఒకవేళ (cur_info->అంకె_కీలకం_ids) {
            new_side_దత్తాంశం_కొలత += (uint64_t)cur_info->అంకె_కీలకం_ids * cur_info->కీలకం_id_కొలత;
            ఒకవేళ (new_side_దత్తాంశం_కొలత > UINT32_MAX)
                తిరిగి AVERROR(EINVAL);
        }
    }

    బఫరు = av_fast_realloc(*side_దత్తాంశం, allocated_కొలత, new_side_దత్తాంశం_కొలత);
    ఒకవేళ (!బఫరు)
        తిరిగి AVERROR(ENOMEM);

    AV_WB32(బఫరు, init_info_లెక్క);
    cur_బఫరు = బఫరు + old_side_దత్తాంశం_కొలత;
    కొరకు (cur_info = info; cur_info; cur_info = cur_info->తదుపరి) {
        AV_WB32(cur_బఫరు,      cur_info->system_id_కొలత);
        AV_WB32(cur_బఫరు +  4, cur_info->అంకె_కీలకం_ids);
        AV_WB32(cur_బఫరు +  8, cur_info->కీలకం_id_కొలత);
        AV_WB32(cur_బఫరు + 12, cur_info->దత్తాంశం_కొలత);
        cur_బఫరు += 16;

        జ్ఞాపకం_నకలు(cur_బఫరు, cur_info->system_id, cur_info->system_id_కొలత);
        cur_బఫరు += cur_info->system_id_కొలత;
        కొరకు (i = 0; i < cur_info->అంకె_కీలకం_ids; i++) {
            జ్ఞాపకం_నకలు(cur_బఫరు, cur_info->కీలకం_ids[i], cur_info->కీలకం_id_కొలత);
            cur_బఫరు += cur_info->కీలకం_id_కొలత;
        }
        ఒకవేళ (cur_info->దత్తాంశం_కొలత > 0) {
            జ్ఞాపకం_నకలు(cur_బఫరు, cur_info->దత్తాంశం, cur_info->దత్తాంశం_కొలత);
            cur_బఫరు += cur_info->దత్తాంశం_కొలత;
        }
    }

    *side_దత్తాంశం      = బఫరు;
    *side_దత్తాంశం_కొలత = new_side_దత్తాంశం_కొలత;
    తిరిగి 0;
}

uint8_t *av_encryption_init_info_కూడు_side_దత్తాంశం(స్థిరరాశి AVEncryptionInitInfo *info, size_t *side_దత్తాంశం_కొలత)
{
    uint8_t *side_దత్తాంశం = ఖాళీ;
    గుర్తులేని పూర్ణాంకం allocated_కొలత = 0;

    ఒకవేళ (av_encryption_init_info_append_side_దత్తాంశం(&side_దత్తాంశం, side_దత్తాంశం_కొలత, &allocated_కొలత, info) < 0)
        తిరిగి ఖాళీ;
    తిరిగి side_దత్తాంశం;
}
