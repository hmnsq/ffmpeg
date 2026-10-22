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

#تعریف_کرو FF_ENCRYPTION_INFO_EXTRA 24

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_گنتی, uint32_t کلید_id_ناپ, uint32_t iv_ناپ)
{
    AVEncryptionInfo *info;

    info = av_mallocz(حجم(*info));
    إذا (!info)
        أرجع عدم;

    info->کلید_id = av_mallocz(کلید_id_ناپ);
    info->کلید_id_ناپ = کلید_id_ناپ;
    info->iv = av_mallocz(iv_ناپ);
    info->iv_ناپ = iv_ناپ;
    info->subsamples = av_calloc(subsample_گنتی, حجم(*info->subsamples));
    info->subsample_گنتی = subsample_گنتی;

    // Allow info->subsamples to be NULL if there are no subsamples.
    إذا (!info->کلید_id || !info->iv || (!info->subsamples && subsample_گنتی)) {
        av_encryption_info_free(info);
        أرجع عدم;
    }

    أرجع info;
}

AVEncryptionInfo *av_encryption_info_clone(ثابت AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_گنتی, info->کلید_id_ناپ, info->iv_ناپ);
    إذا (!ret)
        أرجع عدم;

    ret->scheme = info->scheme;
    ret->crypt_byte_بلاک = info->crypt_byte_بلاک;
    ret->skip_byte_بلاک = info->skip_byte_بلاک;
    حافظہ_نقل(ret->iv, info->iv, info->iv_ناپ);
    حافظہ_نقل(ret->کلید_id, info->کلید_id, info->کلید_id_ناپ);
    حافظہ_نقل(ret->subsamples, info->subsamples, حجم(*info->subsamples) * info->subsample_گنتی);
    أرجع ret;
}

فراغ av_encryption_info_free(AVEncryptionInfo *info)
{
    إذا (info) {
        av_free(info->کلید_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_انکڑے(ثابت uint8_t* بفر, size_t ناپ)
{
    AVEncryptionInfo *info;
    uint64_t کلید_id_ناپ, iv_ناپ, subsample_گنتی, i;

    إذا (!بفر || ناپ < FF_ENCRYPTION_INFO_EXTRA)
        أرجع عدم;

    کلید_id_ناپ = AV_RB32(بفر + 12);
    iv_ناپ = AV_RB32(بفر + 16);
    subsample_گنتی = AV_RB32(بفر + 20);

    إذا (ناپ < FF_ENCRYPTION_INFO_EXTRA + کلید_id_ناپ + iv_ناپ + subsample_گنتی * 8)
        أرجع عدم;

    info = av_encryption_info_alloc(subsample_گنتی, کلید_id_ناپ, iv_ناپ);
    إذا (!info)
        أرجع عدم;

    info->scheme = AV_RB32(بفر);
    info->crypt_byte_بلاک = AV_RB32(بفر + 4);
    info->skip_byte_بلاک = AV_RB32(بفر + 8);
    حافظہ_نقل(info->کلید_id, بفر + 24, کلید_id_ناپ);
    حافظہ_نقل(info->iv, بفر + کلید_id_ناپ + 24, iv_ناپ);

    بفر += کلید_id_ناپ + iv_ناپ + 24;
    لكل (i = 0; i < subsample_گنتی; i++) {
        info->subsamples[i].بائٹاں_دا_clear_انکڑے = AV_RB32(بفر);
        info->subsamples[i].بائٹاں_دا_protected_انکڑے = AV_RB32(بفر + 4);
        بفر += 8;
    }

    أرجع info;
}

uint8_t *av_encryption_info_جوڑو_side_انکڑے(ثابت AVEncryptionInfo *info, size_t *ناپ)
{
    uint8_t *بفر, *cur_بفر;
    uint32_t i;

    إذا (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->کلید_id_ناپ ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->کلید_id_ناپ < info->iv_ناپ ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->کلید_id_ناپ - info->iv_ناپ) / 8 < info->subsample_گنتی) {
        أرجع عدم;
    }

    *ناپ = FF_ENCRYPTION_INFO_EXTRA + info->کلید_id_ناپ + info->iv_ناپ +
            (info->subsample_گنتی * 8);
    cur_بفر = بفر = av_malloc(*ناپ);
    إذا (!بفر)
        أرجع عدم;

    AV_WB32(cur_بفر,      info->scheme);
    AV_WB32(cur_بفر +  4, info->crypt_byte_بلاک);
    AV_WB32(cur_بفر +  8, info->skip_byte_بلاک);
    AV_WB32(cur_بفر + 12, info->کلید_id_ناپ);
    AV_WB32(cur_بفر + 16, info->iv_ناپ);
    AV_WB32(cur_بفر + 20, info->subsample_گنتی);
    cur_بفر += 24;
    حافظہ_نقل(cur_بفر, info->کلید_id, info->کلید_id_ناپ);
    cur_بفر += info->کلید_id_ناپ;
    حافظہ_نقل(cur_بفر, info->iv, info->iv_ناپ);
    cur_بفر += info->iv_ناپ;
    لكل (i = 0; i < info->subsample_گنتی; i++) {
        AV_WB32(cur_بفر, info->subsamples[i].بائٹاں_دا_clear_انکڑے);
        AV_WB32(cur_بفر + 4, info->subsamples[i].بائٹاں_دا_protected_انکڑے);
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

#تعریف_کرو FF_ENCRYPTION_INIT_INFO_EXTRA 16

AVEncryptionInitInfo *av_encryption_init_info_alloc(
    uint32_t system_id_ناپ, uint32_t عدد_کلید_ids, uint32_t کلید_id_ناپ, uint32_t انکڑے_ناپ)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    إذا (عدد_کلید_ids && !کلید_id_ناپ)
        أرجع عدم;

    info = av_mallocz(حجم(*info));
    إذا (!info)
        أرجع عدم;

    info->system_id = av_mallocz(system_id_ناپ);
    info->system_id_ناپ = system_id_ناپ;
    info->کلید_ids = کلید_id_ناپ ? av_calloc(عدد_کلید_ids, حجم(*info->کلید_ids)) : عدم;
    info->عدد_کلید_ids = عدد_کلید_ids;
    info->کلید_id_ناپ = کلید_id_ناپ;
    info->انکڑے = av_mallocz(انکڑے_ناپ);
    info->انکڑے_ناپ = انکڑے_ناپ;

    // Allow pointers to be NULL if the size is 0.
    إذا ((!info->system_id && system_id_ناپ) || (!info->انکڑے && انکڑے_ناپ) ||
        (!info->کلید_ids && عدد_کلید_ids && کلید_id_ناپ)) {
        av_encryption_init_info_free(info);
        أرجع عدم;
    }

    إذا (کلید_id_ناپ) {
        لكل (i = 0; i < عدد_کلید_ids; i++) {
            info->کلید_ids[i] = av_mallocz(کلید_id_ناپ);
            إذا (!info->کلید_ids[i]) {
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
        AVEncryptionInitInfo *اگلا = info->اگلا;
        uint32_t i;

        لكل (i = 0; i < info->عدد_کلید_ids; i++) {
            av_free(info->کلید_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->کلید_ids);
        av_free(info->انکڑے);
        av_free(info);

        info = اگلا;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_انکڑے(
    ثابت uint8_t *side_انکڑے, size_t side_انکڑے_ناپ)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = عدم, *info, *عارضی_info;
    uint64_t system_id_ناپ, عدد_کلید_ids, کلید_id_ناپ, انکڑے_ناپ, i, j;
    uint64_t init_info_گنتی;

    إذا (!side_انکڑے || side_انکڑے_ناپ < 4)
        أرجع عدم;

    init_info_گنتی = AV_RB32(side_انکڑے);
    side_انکڑے += 4;
    side_انکڑے_ناپ -= 4;
    لكل (i = 0; i < init_info_گنتی; i++) {
        إذا (side_انکڑے_ناپ < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }

        system_id_ناپ = AV_RB32(side_انکڑے);
        عدد_کلید_ids = AV_RB32(side_انکڑے + 4);
        کلید_id_ناپ = AV_RB32(side_انکڑے + 8);
        انکڑے_ناپ = AV_RB32(side_انکڑے + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        إذا (side_انکڑے_ناپ - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_ناپ + انکڑے_ناپ + عدد_کلید_ids * کلید_id_ناپ) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }
        side_انکڑے += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_انکڑے_ناپ -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        عارضی_info = av_encryption_init_info_alloc(system_id_ناپ, عدد_کلید_ids, کلید_id_ناپ, انکڑے_ناپ);
        إذا (!عارضی_info) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }
        إذا (i == 0) {
            info = ret = عارضی_info;
        } وإلا {
            info->اگلا = عارضی_info;
            info = عارضی_info;
        }

        حافظہ_نقل(info->system_id, side_انکڑے, system_id_ناپ);
        side_انکڑے += system_id_ناپ;
        side_انکڑے_ناپ -= system_id_ناپ;
        لكل (j = 0; j < عدد_کلید_ids; j++) {
            حافظہ_نقل(info->کلید_ids[j], side_انکڑے, کلید_id_ناپ);
            side_انکڑے += کلید_id_ناپ;
            side_انکڑے_ناپ -= کلید_id_ناپ;
        }
        حافظہ_نقل(info->انکڑے, side_انکڑے, انکڑے_ناپ);
        side_انکڑے += انکڑے_ناپ;
        side_انکڑے_ناپ -= انکڑے_ناپ;
    }

    أرجع ret;
}

صحيح av_encryption_init_info_append_side_انکڑے(uint8_t **side_انکڑے, size_t *side_انکڑے_ناپ,
                                             بنانشانی صحيح *allocated_ناپ,
                                             ثابت AVEncryptionInitInfo *info)
{
    ثابت AVEncryptionInitInfo *cur_info;
    uint8_t *بفر, *cur_بفر;
    uint32_t i;
    uint64_t init_info_گنتی    = *side_انکڑے ? AV_RB32(*side_انکڑے) : 0;
    size_t   old_side_انکڑے_ناپ = *side_انکڑے ? *side_انکڑے_ناپ : 4;
    uint64_t new_side_انکڑے_ناپ = old_side_انکڑے_ناپ;

    لكل (cur_info = info; cur_info; cur_info = cur_info->اگلا) {
        new_side_انکڑے_ناپ += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_ناپ + cur_info->انکڑے_ناپ;
        إذا (init_info_گنتی == UINT32_MAX || new_side_انکڑے_ناپ > UINT32_MAX)
            أرجع AVERROR(EINVAL);
        init_info_گنتی++;

        إذا (cur_info->عدد_کلید_ids) {
            new_side_انکڑے_ناپ += (uint64_t)cur_info->عدد_کلید_ids * cur_info->کلید_id_ناپ;
            إذا (new_side_انکڑے_ناپ > UINT32_MAX)
                أرجع AVERROR(EINVAL);
        }
    }

    بفر = av_fast_realloc(*side_انکڑے, allocated_ناپ, new_side_انکڑے_ناپ);
    إذا (!بفر)
        أرجع AVERROR(ENOMEM);

    AV_WB32(بفر, init_info_گنتی);
    cur_بفر = بفر + old_side_انکڑے_ناپ;
    لكل (cur_info = info; cur_info; cur_info = cur_info->اگلا) {
        AV_WB32(cur_بفر,      cur_info->system_id_ناپ);
        AV_WB32(cur_بفر +  4, cur_info->عدد_کلید_ids);
        AV_WB32(cur_بفر +  8, cur_info->کلید_id_ناپ);
        AV_WB32(cur_بفر + 12, cur_info->انکڑے_ناپ);
        cur_بفر += 16;

        حافظہ_نقل(cur_بفر, cur_info->system_id, cur_info->system_id_ناپ);
        cur_بفر += cur_info->system_id_ناپ;
        لكل (i = 0; i < cur_info->عدد_کلید_ids; i++) {
            حافظہ_نقل(cur_بفر, cur_info->کلید_ids[i], cur_info->کلید_id_ناپ);
            cur_بفر += cur_info->کلید_id_ناپ;
        }
        إذا (cur_info->انکڑے_ناپ > 0) {
            حافظہ_نقل(cur_بفر, cur_info->انکڑے, cur_info->انکڑے_ناپ);
            cur_بفر += cur_info->انکڑے_ناپ;
        }
    }

    *side_انکڑے      = بفر;
    *side_انکڑے_ناپ = new_side_انکڑے_ناپ;
    أرجع 0;
}

uint8_t *av_encryption_init_info_جوڑو_side_انکڑے(ثابت AVEncryptionInitInfo *info, size_t *side_انکڑے_ناپ)
{
    uint8_t *side_انکڑے = عدم;
    بنانشانی صحيح allocated_ناپ = 0;

    إذا (av_encryption_init_info_append_side_انکڑے(&side_انکڑے, side_انکڑے_ناپ, &allocated_ناپ, info) < 0)
        أرجع عدم;
    أرجع side_انکڑے;
}
