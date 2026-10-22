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

#অন্তর্ভাব <string.h>

#অন্তর্ভাব "encryption_info.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "intreadwrite.h"

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_গুনতি, uint32_t চাবি_id_আকার, uint32_t iv_আকার)
{
    AVEncryptionInfo *info;

    info = av_mallocz(আকার(*info));
    যদি (!info)
        ফেরত ফাঁকা;

    info->চাবি_id = av_mallocz(চাবি_id_আকার);
    info->চাবি_id_আকার = চাবি_id_আকার;
    info->iv = av_mallocz(iv_আকার);
    info->iv_আকার = iv_আকার;
    info->subsamples = av_calloc(subsample_গুনতি, আকার(*info->subsamples));
    info->subsample_গুনতি = subsample_গুনতি;

    // Allow info->subsamples to be NULL if there are no subsamples.
    যদি (!info->চাবি_id || !info->iv || (!info->subsamples && subsample_গুনতি)) {
        av_encryption_info_free(info);
        ফেরত ফাঁকা;
    }

    ফেরত info;
}

AVEncryptionInfo *av_encryption_info_clone(ধ্রুবক AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_গুনতি, info->চাবি_id_আকার, info->iv_আকার);
    যদি (!ret)
        ফেরত ফাঁকা;

    ret->scheme = info->scheme;
    ret->crypt_byte_block = info->crypt_byte_block;
    ret->skip_byte_block = info->skip_byte_block;
    memcpy(ret->iv, info->iv, info->iv_আকার);
    memcpy(ret->চাবি_id, info->চাবি_id, info->চাবি_id_আকার);
    memcpy(ret->subsamples, info->subsamples, আকার(*info->subsamples) * info->subsample_গুনতি);
    ফেরত ret;
}

শূন্য av_encryption_info_free(AVEncryptionInfo *info)
{
    যদি (info) {
        av_free(info->চাবি_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_তথ্য(ধ্রুবক uint8_t* বাফার, size_t আকার_2)
{
    AVEncryptionInfo *info;
    uint64_t চাবি_id_আকার, iv_আকার, subsample_গুনতি, i;

    যদি (!বাফার || আকার_2 < FF_ENCRYPTION_INFO_EXTRA)
        ফেরত ফাঁকা;

    চাবি_id_আকার = AV_RB32(বাফার + 12);
    iv_আকার = AV_RB32(বাফার + 16);
    subsample_গুনতি = AV_RB32(বাফার + 20);

    যদি (আকার_2 < FF_ENCRYPTION_INFO_EXTRA + চাবি_id_আকার + iv_আকার + subsample_গুনতি * 8)
        ফেরত ফাঁকা;

    info = av_encryption_info_alloc(subsample_গুনতি, চাবি_id_আকার, iv_আকার);
    যদি (!info)
        ফেরত ফাঁকা;

    info->scheme = AV_RB32(বাফার);
    info->crypt_byte_block = AV_RB32(বাফার + 4);
    info->skip_byte_block = AV_RB32(বাফার + 8);
    memcpy(info->চাবি_id, বাফার + 24, চাবি_id_আকার);
    memcpy(info->iv, বাফার + চাবি_id_আকার + 24, iv_আকার);

    বাফার += চাবি_id_আকার + iv_আকার + 24;
    জন্য (i = 0; i < subsample_গুনতি; i++) {
        info->subsamples[i].bytes_of_clear_তথ্য = AV_RB32(বাফার);
        info->subsamples[i].bytes_of_protected_তথ্য = AV_RB32(বাফার + 4);
        বাফার += 8;
    }

    ফেরত info;
}

uint8_t *av_encryption_info_add_side_তথ্য(ধ্রুবক AVEncryptionInfo *info, size_t *আকার_2)
{
    uint8_t *বাফার, *cur_বাফার;
    uint32_t i;

    যদি (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->চাবি_id_আকার ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->চাবি_id_আকার < info->iv_আকার ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->চাবি_id_আকার - info->iv_আকার) / 8 < info->subsample_গুনতি) {
        ফেরত ফাঁকা;
    }

    *আকার_2 = FF_ENCRYPTION_INFO_EXTRA + info->চাবি_id_আকার + info->iv_আকার +
            (info->subsample_গুনতি * 8);
    cur_বাফার = বাফার = av_malloc(*আকার_2);
    যদি (!বাফার)
        ফেরত ফাঁকা;

    AV_WB32(cur_বাফার,      info->scheme);
    AV_WB32(cur_বাফার +  4, info->crypt_byte_block);
    AV_WB32(cur_বাফার +  8, info->skip_byte_block);
    AV_WB32(cur_বাফার + 12, info->চাবি_id_আকার);
    AV_WB32(cur_বাফার + 16, info->iv_আকার);
    AV_WB32(cur_বাফার + 20, info->subsample_গুনতি);
    cur_বাফার += 24;
    memcpy(cur_বাফার, info->চাবি_id, info->চাবি_id_আকার);
    cur_বাফার += info->চাবি_id_আকার;
    memcpy(cur_বাফার, info->iv, info->iv_আকার);
    cur_বাফার += info->iv_আকার;
    জন্য (i = 0; i < info->subsample_গুনতি; i++) {
        AV_WB32(cur_বাফার, info->subsamples[i].bytes_of_clear_তথ্য);
        AV_WB32(cur_বাফার + 4, info->subsamples[i].bytes_of_protected_তথ্য);
        cur_বাফার += 8;
    }

    ফেরত বাফার;
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
    uint32_t system_id_আকার, uint32_t অঙ্ক_চাবি_ids, uint32_t চাবি_id_আকার, uint32_t তথ্য_আকার)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    যদি (অঙ্ক_চাবি_ids && !চাবি_id_আকার)
        ফেরত ফাঁকা;

    info = av_mallocz(আকার(*info));
    যদি (!info)
        ফেরত ফাঁকা;

    info->system_id = av_mallocz(system_id_আকার);
    info->system_id_আকার = system_id_আকার;
    info->চাবি_ids = চাবি_id_আকার ? av_calloc(অঙ্ক_চাবি_ids, আকার(*info->চাবি_ids)) : ফাঁকা;
    info->অঙ্ক_চাবি_ids = অঙ্ক_চাবি_ids;
    info->চাবি_id_আকার = চাবি_id_আকার;
    info->তথ্য = av_mallocz(তথ্য_আকার);
    info->তথ্য_আকার = তথ্য_আকার;

    // Allow pointers to be NULL if the size is 0.
    যদি ((!info->system_id && system_id_আকার) || (!info->তথ্য && তথ্য_আকার) ||
        (!info->চাবি_ids && অঙ্ক_চাবি_ids && চাবি_id_আকার)) {
        av_encryption_init_info_free(info);
        ফেরত ফাঁকা;
    }

    যদি (চাবি_id_আকার) {
        জন্য (i = 0; i < অঙ্ক_চাবি_ids; i++) {
            info->চাবি_ids[i] = av_mallocz(চাবি_id_আকার);
            যদি (!info->চাবি_ids[i]) {
                av_encryption_init_info_free(info);
                ফেরত ফাঁকা;
            }
        }
    }

    ফেরত info;
}

শূন্য av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    যখন (info) {
        AVEncryptionInitInfo *পরবর্তী = info->পরবর্তী;
        uint32_t i;

        জন্য (i = 0; i < info->অঙ্ক_চাবি_ids; i++) {
            av_free(info->চাবি_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->চাবি_ids);
        av_free(info->তথ্য);
        av_free(info);

        info = পরবর্তী;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_তথ্য(
    ধ্রুবক uint8_t *side_তথ্য, size_t side_তথ্য_আকার)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = ফাঁকা, *info, *অস্থায়ী_info;
    uint64_t system_id_আকার, অঙ্ক_চাবি_ids, চাবি_id_আকার, তথ্য_আকার, i, j;
    uint64_t init_info_গুনতি;

    যদি (!side_তথ্য || side_তথ্য_আকার < 4)
        ফেরত ফাঁকা;

    init_info_গুনতি = AV_RB32(side_তথ্য);
    side_তথ্য += 4;
    side_তথ্য_আকার -= 4;
    জন্য (i = 0; i < init_info_গুনতি; i++) {
        যদি (side_তথ্য_আকার < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            ফেরত ফাঁকা;
        }

        system_id_আকার = AV_RB32(side_তথ্য);
        অঙ্ক_চাবি_ids = AV_RB32(side_তথ্য + 4);
        চাবি_id_আকার = AV_RB32(side_তথ্য + 8);
        তথ্য_আকার = AV_RB32(side_তথ্য + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        যদি (side_তথ্য_আকার - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_আকার + তথ্য_আকার + অঙ্ক_চাবি_ids * চাবি_id_আকার) {
            av_encryption_init_info_free(ret);
            ফেরত ফাঁকা;
        }
        side_তথ্য += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_তথ্য_আকার -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        অস্থায়ী_info = av_encryption_init_info_alloc(system_id_আকার, অঙ্ক_চাবি_ids, চাবি_id_আকার, তথ্য_আকার);
        যদি (!অস্থায়ী_info) {
            av_encryption_init_info_free(ret);
            ফেরত ফাঁকা;
        }
        যদি (i == 0) {
            info = ret = অস্থায়ী_info;
        } অন্যথা {
            info->পরবর্তী = অস্থায়ী_info;
            info = অস্থায়ী_info;
        }

        memcpy(info->system_id, side_তথ্য, system_id_আকার);
        side_তথ্য += system_id_আকার;
        side_তথ্য_আকার -= system_id_আকার;
        জন্য (j = 0; j < অঙ্ক_চাবি_ids; j++) {
            memcpy(info->চাবি_ids[j], side_তথ্য, চাবি_id_আকার);
            side_তথ্য += চাবি_id_আকার;
            side_তথ্য_আকার -= চাবি_id_আকার;
        }
        memcpy(info->তথ্য, side_তথ্য, তথ্য_আকার);
        side_তথ্য += তথ্য_আকার;
        side_তথ্য_আকার -= তথ্য_আকার;
    }

    ফেরত ret;
}

পূর্ণসংখ্যা av_encryption_init_info_append_side_তথ্য(uint8_t **side_তথ্য, size_t *side_তথ্য_আকার,
                                             unsigned পূর্ণসংখ্যা *allocated_আকার,
                                             ধ্রুবক AVEncryptionInitInfo *info)
{
    ধ্রুবক AVEncryptionInitInfo *cur_info;
    uint8_t *বাফার, *cur_বাফার;
    uint32_t i;
    uint64_t init_info_গুনতি    = *side_তথ্য ? AV_RB32(*side_তথ্য) : 0;
    size_t   old_side_তথ্য_আকার = *side_তথ্য ? *side_তথ্য_আকার : 4;
    uint64_t new_side_তথ্য_আকার = old_side_তথ্য_আকার;

    জন্য (cur_info = info; cur_info; cur_info = cur_info->পরবর্তী) {
        new_side_তথ্য_আকার += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_আকার + cur_info->তথ্য_আকার;
        যদি (init_info_গুনতি == UINT32_MAX || new_side_তথ্য_আকার > UINT32_MAX)
            ফেরত AVERROR(EINVAL);
        init_info_গুনতি++;

        যদি (cur_info->অঙ্ক_চাবি_ids) {
            new_side_তথ্য_আকার += (uint64_t)cur_info->অঙ্ক_চাবি_ids * cur_info->চাবি_id_আকার;
            যদি (new_side_তথ্য_আকার > UINT32_MAX)
                ফেরত AVERROR(EINVAL);
        }
    }

    বাফার = av_fast_realloc(*side_তথ্য, allocated_আকার, new_side_তথ্য_আকার);
    যদি (!বাফার)
        ফেরত AVERROR(ENOMEM);

    AV_WB32(বাফার, init_info_গুনতি);
    cur_বাফার = বাফার + old_side_তথ্য_আকার;
    জন্য (cur_info = info; cur_info; cur_info = cur_info->পরবর্তী) {
        AV_WB32(cur_বাফার,      cur_info->system_id_আকার);
        AV_WB32(cur_বাফার +  4, cur_info->অঙ্ক_চাবি_ids);
        AV_WB32(cur_বাফার +  8, cur_info->চাবি_id_আকার);
        AV_WB32(cur_বাফার + 12, cur_info->তথ্য_আকার);
        cur_বাফার += 16;

        memcpy(cur_বাফার, cur_info->system_id, cur_info->system_id_আকার);
        cur_বাফার += cur_info->system_id_আকার;
        জন্য (i = 0; i < cur_info->অঙ্ক_চাবি_ids; i++) {
            memcpy(cur_বাফার, cur_info->চাবি_ids[i], cur_info->চাবি_id_আকার);
            cur_বাফার += cur_info->চাবি_id_আকার;
        }
        যদি (cur_info->তথ্য_আকার > 0) {
            memcpy(cur_বাফার, cur_info->তথ্য, cur_info->তথ্য_আকার);
            cur_বাফার += cur_info->তথ্য_আকার;
        }
    }

    *side_তথ্য      = বাফার;
    *side_তথ্য_আকার = new_side_তথ্য_আকার;
    ফেরত 0;
}

uint8_t *av_encryption_init_info_add_side_তথ্য(ধ্রুবক AVEncryptionInitInfo *info, size_t *side_তথ্য_আকার)
{
    uint8_t *side_তথ্য = ফাঁকা;
    unsigned পূর্ণসংখ্যা allocated_আকার = 0;

    যদি (av_encryption_init_info_append_side_তথ্য(&side_তথ্য, side_তথ্য_আকার, &allocated_আকার, info) < 0)
        ফেরত ফাঁকা;
    ফেরত side_তথ্য;
}
