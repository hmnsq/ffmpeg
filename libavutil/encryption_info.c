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

#ضمن <string.h>

#ضمن "encryption_info.h"
#ضمن "error.h"
#ضمن "mem.h"
#ضمن "intreadwrite.h"

#وصف_ڪريو FF_ENCRYPTION_INFO_EXTRA 24

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_ڳڻپ, uint32_t ڪنجي_id_سائيز, uint32_t iv_سائيز)
{
    AVEncryptionInfo *info;

    info = av_mallocz(حجم(*info));
    إذا (!info)
        أرجع عدم;

    info->ڪنجي_id = av_mallocz(ڪنجي_id_سائيز);
    info->ڪنجي_id_سائيز = ڪنجي_id_سائيز;
    info->iv = av_mallocz(iv_سائيز);
    info->iv_سائيز = iv_سائيز;
    info->subsamples = av_calloc(subsample_ڳڻپ, حجم(*info->subsamples));
    info->subsample_ڳڻپ = subsample_ڳڻپ;

    // Allow info->subsamples to be NULL if there are no subsamples.
    إذا (!info->ڪنجي_id || !info->iv || (!info->subsamples && subsample_ڳڻپ)) {
        av_encryption_info_free(info);
        أرجع عدم;
    }

    أرجع info;
}

AVEncryptionInfo *av_encryption_info_clone(ثابت AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_ڳڻپ, info->ڪنجي_id_سائيز, info->iv_سائيز);
    إذا (!ret)
        أرجع عدم;

    ret->scheme = info->scheme;
    ret->crypt_byte_بلاڪ = info->crypt_byte_بلاڪ;
    ret->skip_byte_بلاڪ = info->skip_byte_بلاڪ;
    يادگيري_نقل(ret->iv, info->iv, info->iv_سائيز);
    يادگيري_نقل(ret->ڪنجي_id, info->ڪنجي_id, info->ڪنجي_id_سائيز);
    يادگيري_نقل(ret->subsamples, info->subsamples, حجم(*info->subsamples) * info->subsample_ڳڻپ);
    أرجع ret;
}

فراغ av_encryption_info_free(AVEncryptionInfo *info)
{
    إذا (info) {
        av_free(info->ڪنجي_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_معلومات(ثابت uint8_t* بفر, size_t سائيز)
{
    AVEncryptionInfo *info;
    uint64_t ڪنجي_id_سائيز, iv_سائيز, subsample_ڳڻپ, i;

    إذا (!بفر || سائيز < FF_ENCRYPTION_INFO_EXTRA)
        أرجع عدم;

    ڪنجي_id_سائيز = AV_RB32(بفر + 12);
    iv_سائيز = AV_RB32(بفر + 16);
    subsample_ڳڻپ = AV_RB32(بفر + 20);

    إذا (سائيز < FF_ENCRYPTION_INFO_EXTRA + ڪنجي_id_سائيز + iv_سائيز + subsample_ڳڻپ * 8)
        أرجع عدم;

    info = av_encryption_info_alloc(subsample_ڳڻپ, ڪنجي_id_سائيز, iv_سائيز);
    إذا (!info)
        أرجع عدم;

    info->scheme = AV_RB32(بفر);
    info->crypt_byte_بلاڪ = AV_RB32(بفر + 4);
    info->skip_byte_بلاڪ = AV_RB32(بفر + 8);
    يادگيري_نقل(info->ڪنجي_id, بفر + 24, ڪنجي_id_سائيز);
    يادگيري_نقل(info->iv, بفر + ڪنجي_id_سائيز + 24, iv_سائيز);

    بفر += ڪنجي_id_سائيز + iv_سائيز + 24;
    لكل (i = 0; i < subsample_ڳڻپ; i++) {
        info->subsamples[i].بائيٽون_جو_clear_معلومات = AV_RB32(بفر);
        info->subsamples[i].بائيٽون_جو_protected_معلومات = AV_RB32(بفر + 4);
        بفر += 8;
    }

    أرجع info;
}

uint8_t *av_encryption_info_جوڙيو_side_معلومات(ثابت AVEncryptionInfo *info, size_t *سائيز)
{
    uint8_t *بفر, *cur_بفر;
    uint32_t i;

    إذا (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->ڪنجي_id_سائيز ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->ڪنجي_id_سائيز < info->iv_سائيز ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->ڪنجي_id_سائيز - info->iv_سائيز) / 8 < info->subsample_ڳڻپ) {
        أرجع عدم;
    }

    *سائيز = FF_ENCRYPTION_INFO_EXTRA + info->ڪنجي_id_سائيز + info->iv_سائيز +
            (info->subsample_ڳڻپ * 8);
    cur_بفر = بفر = av_malloc(*سائيز);
    إذا (!بفر)
        أرجع عدم;

    AV_WB32(cur_بفر,      info->scheme);
    AV_WB32(cur_بفر +  4, info->crypt_byte_بلاڪ);
    AV_WB32(cur_بفر +  8, info->skip_byte_بلاڪ);
    AV_WB32(cur_بفر + 12, info->ڪنجي_id_سائيز);
    AV_WB32(cur_بفر + 16, info->iv_سائيز);
    AV_WB32(cur_بفر + 20, info->subsample_ڳڻپ);
    cur_بفر += 24;
    يادگيري_نقل(cur_بفر, info->ڪنجي_id, info->ڪنجي_id_سائيز);
    cur_بفر += info->ڪنجي_id_سائيز;
    يادگيري_نقل(cur_بفر, info->iv, info->iv_سائيز);
    cur_بفر += info->iv_سائيز;
    لكل (i = 0; i < info->subsample_ڳڻپ; i++) {
        AV_WB32(cur_بفر, info->subsamples[i].بائيٽون_جو_clear_معلومات);
        AV_WB32(cur_بفر + 4, info->subsamples[i].بائيٽون_جو_protected_معلومات);
        cur_بفر += 8;
    }

    أرجع بفر;
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

#وصف_ڪريو FF_ENCRYPTION_INIT_INFO_EXTRA 16

AVEncryptionInitInfo *av_encryption_init_info_alloc(
    uint32_t system_id_سائيز, uint32_t انگ_ڪنجي_ids, uint32_t ڪنجي_id_سائيز, uint32_t معلومات_سائيز)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    إذا (انگ_ڪنجي_ids && !ڪنجي_id_سائيز)
        أرجع عدم;

    info = av_mallocz(حجم(*info));
    إذا (!info)
        أرجع عدم;

    info->system_id = av_mallocz(system_id_سائيز);
    info->system_id_سائيز = system_id_سائيز;
    info->ڪنجي_ids = ڪنجي_id_سائيز ? av_calloc(انگ_ڪنجي_ids, حجم(*info->ڪنجي_ids)) : عدم;
    info->انگ_ڪنجي_ids = انگ_ڪنجي_ids;
    info->ڪنجي_id_سائيز = ڪنجي_id_سائيز;
    info->معلومات = av_mallocz(معلومات_سائيز);
    info->معلومات_سائيز = معلومات_سائيز;

    // Allow pointers to be NULL if the size is 0.
    إذا ((!info->system_id && system_id_سائيز) || (!info->معلومات && معلومات_سائيز) ||
        (!info->ڪنجي_ids && انگ_ڪنجي_ids && ڪنجي_id_سائيز)) {
        av_encryption_init_info_free(info);
        أرجع عدم;
    }

    إذا (ڪنجي_id_سائيز) {
        لكل (i = 0; i < انگ_ڪنجي_ids; i++) {
            info->ڪنجي_ids[i] = av_mallocz(ڪنجي_id_سائيز);
            إذا (!info->ڪنجي_ids[i]) {
                av_encryption_init_info_free(info);
                أرجع عدم;
            }
        }
    }

    أرجع info;
}

فراغ av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    طالما (info) {
        AVEncryptionInitInfo *ايندڙ = info->ايندڙ;
        uint32_t i;

        لكل (i = 0; i < info->انگ_ڪنجي_ids; i++) {
            av_free(info->ڪنجي_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->ڪنجي_ids);
        av_free(info->معلومات);
        av_free(info);

        info = ايندڙ;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_معلومات(
    ثابت uint8_t *side_معلومات, size_t side_معلومات_سائيز)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = عدم, *info, *عارضي_info;
    uint64_t system_id_سائيز, انگ_ڪنجي_ids, ڪنجي_id_سائيز, معلومات_سائيز, i, j;
    uint64_t init_info_ڳڻپ;

    إذا (!side_معلومات || side_معلومات_سائيز < 4)
        أرجع عدم;

    init_info_ڳڻپ = AV_RB32(side_معلومات);
    side_معلومات += 4;
    side_معلومات_سائيز -= 4;
    لكل (i = 0; i < init_info_ڳڻپ; i++) {
        إذا (side_معلومات_سائيز < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }

        system_id_سائيز = AV_RB32(side_معلومات);
        انگ_ڪنجي_ids = AV_RB32(side_معلومات + 4);
        ڪنجي_id_سائيز = AV_RB32(side_معلومات + 8);
        معلومات_سائيز = AV_RB32(side_معلومات + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        إذا (side_معلومات_سائيز - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_سائيز + معلومات_سائيز + انگ_ڪنجي_ids * ڪنجي_id_سائيز) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }
        side_معلومات += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_معلومات_سائيز -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        عارضي_info = av_encryption_init_info_alloc(system_id_سائيز, انگ_ڪنجي_ids, ڪنجي_id_سائيز, معلومات_سائيز);
        إذا (!عارضي_info) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }
        إذا (i == 0) {
            info = ret = عارضي_info;
        } وإلا {
            info->ايندڙ = عارضي_info;
            info = عارضي_info;
        }

        يادگيري_نقل(info->system_id, side_معلومات, system_id_سائيز);
        side_معلومات += system_id_سائيز;
        side_معلومات_سائيز -= system_id_سائيز;
        لكل (j = 0; j < انگ_ڪنجي_ids; j++) {
            يادگيري_نقل(info->ڪنجي_ids[j], side_معلومات, ڪنجي_id_سائيز);
            side_معلومات += ڪنجي_id_سائيز;
            side_معلومات_سائيز -= ڪنجي_id_سائيز;
        }
        يادگيري_نقل(info->معلومات, side_معلومات, معلومات_سائيز);
        side_معلومات += معلومات_سائيز;
        side_معلومات_سائيز -= معلومات_سائيز;
    }

    أرجع ret;
}

صحيح av_encryption_init_info_append_side_معلومات(uint8_t **side_معلومات, size_t *side_معلومات_سائيز,
                                             بنانشان صحيح *allocated_سائيز,
                                             ثابت AVEncryptionInitInfo *info)
{
    ثابت AVEncryptionInitInfo *cur_info;
    uint8_t *بفر, *cur_بفر;
    uint32_t i;
    uint64_t init_info_ڳڻپ    = *side_معلومات ? AV_RB32(*side_معلومات) : 0;
    size_t   old_side_معلومات_سائيز = *side_معلومات ? *side_معلومات_سائيز : 4;
    uint64_t new_side_معلومات_سائيز = old_side_معلومات_سائيز;

    لكل (cur_info = info; cur_info; cur_info = cur_info->ايندڙ) {
        new_side_معلومات_سائيز += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_سائيز + cur_info->معلومات_سائيز;
        إذا (init_info_ڳڻپ == UINT32_MAX || new_side_معلومات_سائيز > UINT32_MAX)
            أرجع AVERROR(EINVAL);
        init_info_ڳڻپ++;

        إذا (cur_info->انگ_ڪنجي_ids) {
            new_side_معلومات_سائيز += (uint64_t)cur_info->انگ_ڪنجي_ids * cur_info->ڪنجي_id_سائيز;
            إذا (new_side_معلومات_سائيز > UINT32_MAX)
                أرجع AVERROR(EINVAL);
        }
    }

    بفر = av_fast_realloc(*side_معلومات, allocated_سائيز, new_side_معلومات_سائيز);
    إذا (!بفر)
        أرجع AVERROR(ENOMEM);

    AV_WB32(بفر, init_info_ڳڻپ);
    cur_بفر = بفر + old_side_معلومات_سائيز;
    لكل (cur_info = info; cur_info; cur_info = cur_info->ايندڙ) {
        AV_WB32(cur_بفر,      cur_info->system_id_سائيز);
        AV_WB32(cur_بفر +  4, cur_info->انگ_ڪنجي_ids);
        AV_WB32(cur_بفر +  8, cur_info->ڪنجي_id_سائيز);
        AV_WB32(cur_بفر + 12, cur_info->معلومات_سائيز);
        cur_بفر += 16;

        يادگيري_نقل(cur_بفر, cur_info->system_id, cur_info->system_id_سائيز);
        cur_بفر += cur_info->system_id_سائيز;
        لكل (i = 0; i < cur_info->انگ_ڪنجي_ids; i++) {
            يادگيري_نقل(cur_بفر, cur_info->ڪنجي_ids[i], cur_info->ڪنجي_id_سائيز);
            cur_بفر += cur_info->ڪنجي_id_سائيز;
        }
        إذا (cur_info->معلومات_سائيز > 0) {
            يادگيري_نقل(cur_بفر, cur_info->معلومات, cur_info->معلومات_سائيز);
            cur_بفر += cur_info->معلومات_سائيز;
        }
    }

    *side_معلومات      = بفر;
    *side_معلومات_سائيز = new_side_معلومات_سائيز;
    أرجع 0;
}

uint8_t *av_encryption_init_info_جوڙيو_side_معلومات(ثابت AVEncryptionInitInfo *info, size_t *side_معلومات_سائيز)
{
    uint8_t *side_معلومات = عدم;
    بنانشان صحيح allocated_سائيز = 0;

    إذا (av_encryption_init_info_append_side_معلومات(&side_معلومات, side_معلومات_سائيز, &allocated_سائيز, info) < 0)
        أرجع عدم;
    أرجع side_معلومات;
}
