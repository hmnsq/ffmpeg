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

#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "encryption_info.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"

#ವ್ಯಾಖ್ಯಾನಿಸು FF_ENCRYPTION_INFO_EXTRA 24

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_ಎಣಿಕೆ, uint32_t ಕೀಲಿ_id_ಗಾತ್ರ, uint32_t iv_ಗಾತ್ರ)
{
    AVEncryptionInfo *info;

    info = av_mallocz(ಗಾತ್ರ(*info));
    ಆದರೆ (!info)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    info->ಕೀಲಿ_id = av_mallocz(ಕೀಲಿ_id_ಗಾತ್ರ);
    info->ಕೀಲಿ_id_ಗಾತ್ರ = ಕೀಲಿ_id_ಗಾತ್ರ;
    info->iv = av_mallocz(iv_ಗಾತ್ರ);
    info->iv_ಗಾತ್ರ = iv_ಗಾತ್ರ;
    info->subsamples = av_calloc(subsample_ಎಣಿಕೆ, ಗಾತ್ರ(*info->subsamples));
    info->subsample_ಎಣಿಕೆ = subsample_ಎಣಿಕೆ;

    // Allow info->subsamples to be NULL if there are no subsamples.
    ಆದರೆ (!info->ಕೀಲಿ_id || !info->iv || (!info->subsamples && subsample_ಎಣಿಕೆ)) {
        av_encryption_info_free(info);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ info;
}

AVEncryptionInfo *av_encryption_info_clone(ಸ್ಥಿರಾಂಕ AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_ಎಣಿಕೆ, info->ಕೀಲಿ_id_ಗಾತ್ರ, info->iv_ಗಾತ್ರ);
    ಆದರೆ (!ret)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ret->scheme = info->scheme;
    ret->crypt_byte_ಖಂಡ = info->crypt_byte_ಖಂಡ;
    ret->skip_byte_ಖಂಡ = info->skip_byte_ಖಂಡ;
    ಸ್ಮರಣೆ_ನಕಲು(ret->iv, info->iv, info->iv_ಗಾತ್ರ);
    ಸ್ಮರಣೆ_ನಕಲು(ret->ಕೀಲಿ_id, info->ಕೀಲಿ_id, info->ಕೀಲಿ_id_ಗಾತ್ರ);
    ಸ್ಮರಣೆ_ನಕಲು(ret->subsamples, info->subsamples, ಗಾತ್ರ(*info->subsamples) * info->subsample_ಎಣಿಕೆ);
    ಹಿಂತಿರುಗಿ ret;
}

ಶೂನ್ಯ av_encryption_info_free(AVEncryptionInfo *info)
{
    ಆದರೆ (info) {
        av_free(info->ಕೀಲಿ_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_ದತ್ತಾಂಶ(ಸ್ಥಿರಾಂಕ uint8_t* ಬಫರ್, size_t ಗಾತ್ರ_2)
{
    AVEncryptionInfo *info;
    uint64_t ಕೀಲಿ_id_ಗಾತ್ರ, iv_ಗಾತ್ರ, subsample_ಎಣಿಕೆ, i;

    ಆದರೆ (!ಬಫರ್ || ಗಾತ್ರ_2 < FF_ENCRYPTION_INFO_EXTRA)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಕೀಲಿ_id_ಗಾತ್ರ = AV_RB32(ಬಫರ್ + 12);
    iv_ಗಾತ್ರ = AV_RB32(ಬಫರ್ + 16);
    subsample_ಎಣಿಕೆ = AV_RB32(ಬಫರ್ + 20);

    ಆದರೆ (ಗಾತ್ರ_2 < FF_ENCRYPTION_INFO_EXTRA + ಕೀಲಿ_id_ಗಾತ್ರ + iv_ಗಾತ್ರ + subsample_ಎಣಿಕೆ * 8)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    info = av_encryption_info_alloc(subsample_ಎಣಿಕೆ, ಕೀಲಿ_id_ಗಾತ್ರ, iv_ಗಾತ್ರ);
    ಆದರೆ (!info)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    info->scheme = AV_RB32(ಬಫರ್);
    info->crypt_byte_ಖಂಡ = AV_RB32(ಬಫರ್ + 4);
    info->skip_byte_ಖಂಡ = AV_RB32(ಬಫರ್ + 8);
    ಸ್ಮರಣೆ_ನಕಲು(info->ಕೀಲಿ_id, ಬಫರ್ + 24, ಕೀಲಿ_id_ಗಾತ್ರ);
    ಸ್ಮರಣೆ_ನಕಲು(info->iv, ಬಫರ್ + ಕೀಲಿ_id_ಗಾತ್ರ + 24, iv_ಗಾತ್ರ);

    ಬಫರ್ += ಕೀಲಿ_id_ಗಾತ್ರ + iv_ಗಾತ್ರ + 24;
    ಗಾಗಿ (i = 0; i < subsample_ಎಣಿಕೆ; i++) {
        info->subsamples[i].ಬೈಟುಗಳು_ದ_clear_ದತ್ತಾಂಶ = AV_RB32(ಬಫರ್);
        info->subsamples[i].ಬೈಟುಗಳು_ದ_protected_ದತ್ತಾಂಶ = AV_RB32(ಬಫರ್ + 4);
        ಬಫರ್ += 8;
    }

    ಹಿಂತಿರುಗಿ info;
}

uint8_t *av_encryption_info_ಕೂಡಿಸು_side_ದತ್ತಾಂಶ(ಸ್ಥಿರಾಂಕ AVEncryptionInfo *info, size_t *ಗಾತ್ರ_2)
{
    uint8_t *ಬಫರ್, *cur_ಬಫರ್;
    uint32_t i;

    ಆದರೆ (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->ಕೀಲಿ_id_ಗಾತ್ರ ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->ಕೀಲಿ_id_ಗಾತ್ರ < info->iv_ಗಾತ್ರ ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->ಕೀಲಿ_id_ಗಾತ್ರ - info->iv_ಗಾತ್ರ) / 8 < info->subsample_ಎಣಿಕೆ) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    *ಗಾತ್ರ_2 = FF_ENCRYPTION_INFO_EXTRA + info->ಕೀಲಿ_id_ಗಾತ್ರ + info->iv_ಗಾತ್ರ +
            (info->subsample_ಎಣಿಕೆ * 8);
    cur_ಬಫರ್ = ಬಫರ್ = av_malloc(*ಗಾತ್ರ_2);
    ಆದರೆ (!ಬಫರ್)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    AV_WB32(cur_ಬಫರ್,      info->scheme);
    AV_WB32(cur_ಬಫರ್ +  4, info->crypt_byte_ಖಂಡ);
    AV_WB32(cur_ಬಫರ್ +  8, info->skip_byte_ಖಂಡ);
    AV_WB32(cur_ಬಫರ್ + 12, info->ಕೀಲಿ_id_ಗಾತ್ರ);
    AV_WB32(cur_ಬಫರ್ + 16, info->iv_ಗಾತ್ರ);
    AV_WB32(cur_ಬಫರ್ + 20, info->subsample_ಎಣಿಕೆ);
    cur_ಬಫರ್ += 24;
    ಸ್ಮರಣೆ_ನಕಲು(cur_ಬಫರ್, info->ಕೀಲಿ_id, info->ಕೀಲಿ_id_ಗಾತ್ರ);
    cur_ಬಫರ್ += info->ಕೀಲಿ_id_ಗಾತ್ರ;
    ಸ್ಮರಣೆ_ನಕಲು(cur_ಬಫರ್, info->iv, info->iv_ಗಾತ್ರ);
    cur_ಬಫರ್ += info->iv_ಗಾತ್ರ;
    ಗಾಗಿ (i = 0; i < info->subsample_ಎಣಿಕೆ; i++) {
        AV_WB32(cur_ಬಫರ್, info->subsamples[i].ಬೈಟುಗಳು_ದ_clear_ದತ್ತಾಂಶ);
        AV_WB32(cur_ಬಫರ್ + 4, info->subsamples[i].ಬೈಟುಗಳು_ದ_protected_ದತ್ತಾಂಶ);
        cur_ಬಫರ್ += 8;
    }

    ಹಿಂತಿರುಗಿ ಬಫರ್;
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

#ವ್ಯಾಖ್ಯಾನಿಸು FF_ENCRYPTION_INIT_INFO_EXTRA 16

AVEncryptionInitInfo *av_encryption_init_info_alloc(
    uint32_t system_id_ಗಾತ್ರ, uint32_t ಅಂಕೆ_ಕೀಲಿ_ids, uint32_t ಕೀಲಿ_id_ಗಾತ್ರ, uint32_t ದತ್ತಾಂಶ_ಗಾತ್ರ)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    ಆದರೆ (ಅಂಕೆ_ಕೀಲಿ_ids && !ಕೀಲಿ_id_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    info = av_mallocz(ಗಾತ್ರ(*info));
    ಆದರೆ (!info)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    info->system_id = av_mallocz(system_id_ಗಾತ್ರ);
    info->system_id_ಗಾತ್ರ = system_id_ಗಾತ್ರ;
    info->ಕೀಲಿ_ids = ಕೀಲಿ_id_ಗಾತ್ರ ? av_calloc(ಅಂಕೆ_ಕೀಲಿ_ids, ಗಾತ್ರ(*info->ಕೀಲಿ_ids)) : ಖಾಲಿ;
    info->ಅಂಕೆ_ಕೀಲಿ_ids = ಅಂಕೆ_ಕೀಲಿ_ids;
    info->ಕೀಲಿ_id_ಗಾತ್ರ = ಕೀಲಿ_id_ಗಾತ್ರ;
    info->ದತ್ತಾಂಶ = av_mallocz(ದತ್ತಾಂಶ_ಗಾತ್ರ);
    info->ದತ್ತಾಂಶ_ಗಾತ್ರ = ದತ್ತಾಂಶ_ಗಾತ್ರ;

    // Allow pointers to be NULL if the size is 0.
    ಆದರೆ ((!info->system_id && system_id_ಗಾತ್ರ) || (!info->ದತ್ತಾಂಶ && ದತ್ತಾಂಶ_ಗಾತ್ರ) ||
        (!info->ಕೀಲಿ_ids && ಅಂಕೆ_ಕೀಲಿ_ids && ಕೀಲಿ_id_ಗಾತ್ರ)) {
        av_encryption_init_info_free(info);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (ಕೀಲಿ_id_ಗಾತ್ರ) {
        ಗಾಗಿ (i = 0; i < ಅಂಕೆ_ಕೀಲಿ_ids; i++) {
            info->ಕೀಲಿ_ids[i] = av_mallocz(ಕೀಲಿ_id_ಗಾತ್ರ);
            ಆದರೆ (!info->ಕೀಲಿ_ids[i]) {
                av_encryption_init_info_free(info);
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            }
        }
    }

    ಹಿಂತಿರುಗಿ info;
}

ಶೂನ್ಯ av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    ಆಗ (info) {
        AVEncryptionInitInfo *ಮುಂದಿನ = info->ಮುಂದಿನ;
        uint32_t i;

        ಗಾಗಿ (i = 0; i < info->ಅಂಕೆ_ಕೀಲಿ_ids; i++) {
            av_free(info->ಕೀಲಿ_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->ಕೀಲಿ_ids);
        av_free(info->ದತ್ತಾಂಶ);
        av_free(info);

        info = ಮುಂದಿನ;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_ದತ್ತಾಂಶ(
    ಸ್ಥಿರಾಂಕ uint8_t *side_ದತ್ತಾಂಶ, size_t side_ದತ್ತಾಂಶ_ಗಾತ್ರ)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = ಖಾಲಿ, *info, *ತಾತ್ಕಾಲಿಕ_info;
    uint64_t system_id_ಗಾತ್ರ, ಅಂಕೆ_ಕೀಲಿ_ids, ಕೀಲಿ_id_ಗಾತ್ರ, ದತ್ತಾಂಶ_ಗಾತ್ರ, i, j;
    uint64_t init_info_ಎಣಿಕೆ;

    ಆದರೆ (!side_ದತ್ತಾಂಶ || side_ದತ್ತಾಂಶ_ಗಾತ್ರ < 4)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    init_info_ಎಣಿಕೆ = AV_RB32(side_ದತ್ತಾಂಶ);
    side_ದತ್ತಾಂಶ += 4;
    side_ದತ್ತಾಂಶ_ಗಾತ್ರ -= 4;
    ಗಾಗಿ (i = 0; i < init_info_ಎಣಿಕೆ; i++) {
        ಆದರೆ (side_ದತ್ತಾಂಶ_ಗಾತ್ರ < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }

        system_id_ಗಾತ್ರ = AV_RB32(side_ದತ್ತಾಂಶ);
        ಅಂಕೆ_ಕೀಲಿ_ids = AV_RB32(side_ದತ್ತಾಂಶ + 4);
        ಕೀಲಿ_id_ಗಾತ್ರ = AV_RB32(side_ದತ್ತಾಂಶ + 8);
        ದತ್ತಾಂಶ_ಗಾತ್ರ = AV_RB32(side_ದತ್ತಾಂಶ + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        ಆದರೆ (side_ದತ್ತಾಂಶ_ಗಾತ್ರ - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_ಗಾತ್ರ + ದತ್ತಾಂಶ_ಗಾತ್ರ + ಅಂಕೆ_ಕೀಲಿ_ids * ಕೀಲಿ_id_ಗಾತ್ರ) {
            av_encryption_init_info_free(ret);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        side_ದತ್ತಾಂಶ += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_ದತ್ತಾಂಶ_ಗಾತ್ರ -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        ತಾತ್ಕಾಲಿಕ_info = av_encryption_init_info_alloc(system_id_ಗಾತ್ರ, ಅಂಕೆ_ಕೀಲಿ_ids, ಕೀಲಿ_id_ಗಾತ್ರ, ದತ್ತಾಂಶ_ಗಾತ್ರ);
        ಆದರೆ (!ತಾತ್ಕಾಲಿಕ_info) {
            av_encryption_init_info_free(ret);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        ಆದರೆ (i == 0) {
            info = ret = ತಾತ್ಕಾಲಿಕ_info;
        } ಇಲ್ಲದಿದ್ದರೆ {
            info->ಮುಂದಿನ = ತಾತ್ಕಾಲಿಕ_info;
            info = ತಾತ್ಕಾಲಿಕ_info;
        }

        ಸ್ಮರಣೆ_ನಕಲು(info->system_id, side_ದತ್ತಾಂಶ, system_id_ಗಾತ್ರ);
        side_ದತ್ತಾಂಶ += system_id_ಗಾತ್ರ;
        side_ದತ್ತಾಂಶ_ಗಾತ್ರ -= system_id_ಗಾತ್ರ;
        ಗಾಗಿ (j = 0; j < ಅಂಕೆ_ಕೀಲಿ_ids; j++) {
            ಸ್ಮರಣೆ_ನಕಲು(info->ಕೀಲಿ_ids[j], side_ದತ್ತಾಂಶ, ಕೀಲಿ_id_ಗಾತ್ರ);
            side_ದತ್ತಾಂಶ += ಕೀಲಿ_id_ಗಾತ್ರ;
            side_ದತ್ತಾಂಶ_ಗಾತ್ರ -= ಕೀಲಿ_id_ಗಾತ್ರ;
        }
        ಸ್ಮರಣೆ_ನಕಲು(info->ದತ್ತಾಂಶ, side_ದತ್ತಾಂಶ, ದತ್ತಾಂಶ_ಗಾತ್ರ);
        side_ದತ್ತಾಂಶ += ದತ್ತಾಂಶ_ಗಾತ್ರ;
        side_ದತ್ತಾಂಶ_ಗಾತ್ರ -= ದತ್ತಾಂಶ_ಗಾತ್ರ;
    }

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_encryption_init_info_append_side_ದತ್ತಾಂಶ(uint8_t **side_ದತ್ತಾಂಶ, size_t *side_ದತ್ತಾಂಶ_ಗಾತ್ರ,
                                             ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *allocated_ಗಾತ್ರ,
                                             ಸ್ಥಿರಾಂಕ AVEncryptionInitInfo *info)
{
    ಸ್ಥಿರಾಂಕ AVEncryptionInitInfo *cur_info;
    uint8_t *ಬಫರ್, *cur_ಬಫರ್;
    uint32_t i;
    uint64_t init_info_ಎಣಿಕೆ    = *side_ದತ್ತಾಂಶ ? AV_RB32(*side_ದತ್ತಾಂಶ) : 0;
    size_t   old_side_ದತ್ತಾಂಶ_ಗಾತ್ರ = *side_ದತ್ತಾಂಶ ? *side_ದತ್ತಾಂಶ_ಗಾತ್ರ : 4;
    uint64_t new_side_ದತ್ತಾಂಶ_ಗಾತ್ರ = old_side_ದತ್ತಾಂಶ_ಗಾತ್ರ;

    ಗಾಗಿ (cur_info = info; cur_info; cur_info = cur_info->ಮುಂದಿನ) {
        new_side_ದತ್ತಾಂಶ_ಗಾತ್ರ += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_ಗಾತ್ರ + cur_info->ದತ್ತಾಂಶ_ಗಾತ್ರ;
        ಆದರೆ (init_info_ಎಣಿಕೆ == UINT32_MAX || new_side_ದತ್ತಾಂಶ_ಗಾತ್ರ > UINT32_MAX)
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        init_info_ಎಣಿಕೆ++;

        ಆದರೆ (cur_info->ಅಂಕೆ_ಕೀಲಿ_ids) {
            new_side_ದತ್ತಾಂಶ_ಗಾತ್ರ += (uint64_t)cur_info->ಅಂಕೆ_ಕೀಲಿ_ids * cur_info->ಕೀಲಿ_id_ಗಾತ್ರ;
            ಆದರೆ (new_side_ದತ್ತಾಂಶ_ಗಾತ್ರ > UINT32_MAX)
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
    }

    ಬಫರ್ = av_fast_realloc(*side_ದತ್ತಾಂಶ, allocated_ಗಾತ್ರ, new_side_ದತ್ತಾಂಶ_ಗಾತ್ರ);
    ಆದರೆ (!ಬಫರ್)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    AV_WB32(ಬಫರ್, init_info_ಎಣಿಕೆ);
    cur_ಬಫರ್ = ಬಫರ್ + old_side_ದತ್ತಾಂಶ_ಗಾತ್ರ;
    ಗಾಗಿ (cur_info = info; cur_info; cur_info = cur_info->ಮುಂದಿನ) {
        AV_WB32(cur_ಬಫರ್,      cur_info->system_id_ಗಾತ್ರ);
        AV_WB32(cur_ಬಫರ್ +  4, cur_info->ಅಂಕೆ_ಕೀಲಿ_ids);
        AV_WB32(cur_ಬಫರ್ +  8, cur_info->ಕೀಲಿ_id_ಗಾತ್ರ);
        AV_WB32(cur_ಬಫರ್ + 12, cur_info->ದತ್ತಾಂಶ_ಗಾತ್ರ);
        cur_ಬಫರ್ += 16;

        ಸ್ಮರಣೆ_ನಕಲು(cur_ಬಫರ್, cur_info->system_id, cur_info->system_id_ಗಾತ್ರ);
        cur_ಬಫರ್ += cur_info->system_id_ಗಾತ್ರ;
        ಗಾಗಿ (i = 0; i < cur_info->ಅಂಕೆ_ಕೀಲಿ_ids; i++) {
            ಸ್ಮರಣೆ_ನಕಲು(cur_ಬಫರ್, cur_info->ಕೀಲಿ_ids[i], cur_info->ಕೀಲಿ_id_ಗಾತ್ರ);
            cur_ಬಫರ್ += cur_info->ಕೀಲಿ_id_ಗಾತ್ರ;
        }
        ಆದರೆ (cur_info->ದತ್ತಾಂಶ_ಗಾತ್ರ > 0) {
            ಸ್ಮರಣೆ_ನಕಲು(cur_ಬಫರ್, cur_info->ದತ್ತಾಂಶ, cur_info->ದತ್ತಾಂಶ_ಗಾತ್ರ);
            cur_ಬಫರ್ += cur_info->ದತ್ತಾಂಶ_ಗಾತ್ರ;
        }
    }

    *side_ದತ್ತಾಂಶ      = ಬಫರ್;
    *side_ದತ್ತಾಂಶ_ಗಾತ್ರ = new_side_ದತ್ತಾಂಶ_ಗಾತ್ರ;
    ಹಿಂತಿರುಗಿ 0;
}

uint8_t *av_encryption_init_info_ಕೂಡಿಸು_side_ದತ್ತಾಂಶ(ಸ್ಥಿರಾಂಕ AVEncryptionInitInfo *info, size_t *side_ದತ್ತಾಂಶ_ಗಾತ್ರ)
{
    uint8_t *side_ದತ್ತಾಂಶ = ಖಾಲಿ;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ allocated_ಗಾತ್ರ = 0;

    ಆದರೆ (av_encryption_init_info_append_side_ದತ್ತಾಂಶ(&side_ದತ್ತಾಂಶ, side_ದತ್ತಾಂಶ_ಗಾತ್ರ, &allocated_ಗಾತ್ರ, info) < 0)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ side_ದತ್ತಾಂಶ;
}
