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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "encryption_info.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_ENCRYPTION_INFO_EXTRA 24

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_ਗਿਣਤੀ, uint32_t ਕੁੰਜੀ_id_ਮਾਪ, uint32_t iv_ਮਾਪ)
{
    AVEncryptionInfo *info;

    info = av_mallocz(ਆਕਾਰ(*info));
    ਜੇ (!info)
        ਵਾਪਸ ਨਿਰਾ;

    info->ਕੁੰਜੀ_id = av_mallocz(ਕੁੰਜੀ_id_ਮਾਪ);
    info->ਕੁੰਜੀ_id_ਮਾਪ = ਕੁੰਜੀ_id_ਮਾਪ;
    info->iv = av_mallocz(iv_ਮਾਪ);
    info->iv_ਮਾਪ = iv_ਮਾਪ;
    info->subsamples = av_calloc(subsample_ਗਿਣਤੀ, ਆਕਾਰ(*info->subsamples));
    info->subsample_ਗਿਣਤੀ = subsample_ਗਿਣਤੀ;

    // Allow info->subsamples to be NULL if there are no subsamples.
    ਜੇ (!info->ਕੁੰਜੀ_id || !info->iv || (!info->subsamples && subsample_ਗਿਣਤੀ)) {
        av_encryption_info_free(info);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ info;
}

AVEncryptionInfo *av_encryption_info_clone(ਅਚਲ AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_ਗਿਣਤੀ, info->ਕੁੰਜੀ_id_ਮਾਪ, info->iv_ਮਾਪ);
    ਜੇ (!ret)
        ਵਾਪਸ ਨਿਰਾ;

    ret->scheme = info->scheme;
    ret->crypt_byte_ਖੰਡ = info->crypt_byte_ਖੰਡ;
    ret->skip_byte_ਖੰਡ = info->skip_byte_ਖੰਡ;
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(ret->iv, info->iv, info->iv_ਮਾਪ);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(ret->ਕੁੰਜੀ_id, info->ਕੁੰਜੀ_id, info->ਕੁੰਜੀ_id_ਮਾਪ);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(ret->subsamples, info->subsamples, ਆਕਾਰ(*info->subsamples) * info->subsample_ਗਿਣਤੀ);
    ਵਾਪਸ ret;
}

ਖਾਲੀ av_encryption_info_free(AVEncryptionInfo *info)
{
    ਜੇ (info) {
        av_free(info->ਕੁੰਜੀ_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_ਅੰਕੜੇ(ਅਚਲ uint8_t* ਬਫਰ, size_t ਮਾਪ)
{
    AVEncryptionInfo *info;
    uint64_t ਕੁੰਜੀ_id_ਮਾਪ, iv_ਮਾਪ, subsample_ਗਿਣਤੀ, i;

    ਜੇ (!ਬਫਰ || ਮਾਪ < FF_ENCRYPTION_INFO_EXTRA)
        ਵਾਪਸ ਨਿਰਾ;

    ਕੁੰਜੀ_id_ਮਾਪ = AV_RB32(ਬਫਰ + 12);
    iv_ਮਾਪ = AV_RB32(ਬਫਰ + 16);
    subsample_ਗਿਣਤੀ = AV_RB32(ਬਫਰ + 20);

    ਜੇ (ਮਾਪ < FF_ENCRYPTION_INFO_EXTRA + ਕੁੰਜੀ_id_ਮਾਪ + iv_ਮਾਪ + subsample_ਗਿਣਤੀ * 8)
        ਵਾਪਸ ਨਿਰਾ;

    info = av_encryption_info_alloc(subsample_ਗਿਣਤੀ, ਕੁੰਜੀ_id_ਮਾਪ, iv_ਮਾਪ);
    ਜੇ (!info)
        ਵਾਪਸ ਨਿਰਾ;

    info->scheme = AV_RB32(ਬਫਰ);
    info->crypt_byte_ਖੰਡ = AV_RB32(ਬਫਰ + 4);
    info->skip_byte_ਖੰਡ = AV_RB32(ਬਫਰ + 8);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(info->ਕੁੰਜੀ_id, ਬਫਰ + 24, ਕੁੰਜੀ_id_ਮਾਪ);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(info->iv, ਬਫਰ + ਕੁੰਜੀ_id_ਮਾਪ + 24, iv_ਮਾਪ);

    ਬਫਰ += ਕੁੰਜੀ_id_ਮਾਪ + iv_ਮਾਪ + 24;
    ਲਈ (i = 0; i < subsample_ਗਿਣਤੀ; i++) {
        info->subsamples[i].ਬਾਈਟਾਂ_ਦਾ_clear_ਅੰਕੜੇ = AV_RB32(ਬਫਰ);
        info->subsamples[i].ਬਾਈਟਾਂ_ਦਾ_protected_ਅੰਕੜੇ = AV_RB32(ਬਫਰ + 4);
        ਬਫਰ += 8;
    }

    ਵਾਪਸ info;
}

uint8_t *av_encryption_info_ਜੋੜੋ_side_ਅੰਕੜੇ(ਅਚਲ AVEncryptionInfo *info, size_t *ਮਾਪ)
{
    uint8_t *ਬਫਰ, *cur_ਬਫਰ;
    uint32_t i;

    ਜੇ (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->ਕੁੰਜੀ_id_ਮਾਪ ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->ਕੁੰਜੀ_id_ਮਾਪ < info->iv_ਮਾਪ ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->ਕੁੰਜੀ_id_ਮਾਪ - info->iv_ਮਾਪ) / 8 < info->subsample_ਗਿਣਤੀ) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    *ਮਾਪ = FF_ENCRYPTION_INFO_EXTRA + info->ਕੁੰਜੀ_id_ਮਾਪ + info->iv_ਮਾਪ +
            (info->subsample_ਗਿਣਤੀ * 8);
    cur_ਬਫਰ = ਬਫਰ = av_malloc(*ਮਾਪ);
    ਜੇ (!ਬਫਰ)
        ਵਾਪਸ ਨਿਰਾ;

    AV_WB32(cur_ਬਫਰ,      info->scheme);
    AV_WB32(cur_ਬਫਰ +  4, info->crypt_byte_ਖੰਡ);
    AV_WB32(cur_ਬਫਰ +  8, info->skip_byte_ਖੰਡ);
    AV_WB32(cur_ਬਫਰ + 12, info->ਕੁੰਜੀ_id_ਮਾਪ);
    AV_WB32(cur_ਬਫਰ + 16, info->iv_ਮਾਪ);
    AV_WB32(cur_ਬਫਰ + 20, info->subsample_ਗਿਣਤੀ);
    cur_ਬਫਰ += 24;
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(cur_ਬਫਰ, info->ਕੁੰਜੀ_id, info->ਕੁੰਜੀ_id_ਮਾਪ);
    cur_ਬਫਰ += info->ਕੁੰਜੀ_id_ਮਾਪ;
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(cur_ਬਫਰ, info->iv, info->iv_ਮਾਪ);
    cur_ਬਫਰ += info->iv_ਮਾਪ;
    ਲਈ (i = 0; i < info->subsample_ਗਿਣਤੀ; i++) {
        AV_WB32(cur_ਬਫਰ, info->subsamples[i].ਬਾਈਟਾਂ_ਦਾ_clear_ਅੰਕੜੇ);
        AV_WB32(cur_ਬਫਰ + 4, info->subsamples[i].ਬਾਈਟਾਂ_ਦਾ_protected_ਅੰਕੜੇ);
        cur_ਬਫਰ += 8;
    }

    ਵਾਪਸ ਬਫਰ;
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_ENCRYPTION_INIT_INFO_EXTRA 16

AVEncryptionInitInfo *av_encryption_init_info_alloc(
    uint32_t system_id_ਮਾਪ, uint32_t ਅੰਕ_ਕੁੰਜੀ_ids, uint32_t ਕੁੰਜੀ_id_ਮਾਪ, uint32_t ਅੰਕੜੇ_ਮਾਪ)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    ਜੇ (ਅੰਕ_ਕੁੰਜੀ_ids && !ਕੁੰਜੀ_id_ਮਾਪ)
        ਵਾਪਸ ਨਿਰਾ;

    info = av_mallocz(ਆਕਾਰ(*info));
    ਜੇ (!info)
        ਵਾਪਸ ਨਿਰਾ;

    info->system_id = av_mallocz(system_id_ਮਾਪ);
    info->system_id_ਮਾਪ = system_id_ਮਾਪ;
    info->ਕੁੰਜੀ_ids = ਕੁੰਜੀ_id_ਮਾਪ ? av_calloc(ਅੰਕ_ਕੁੰਜੀ_ids, ਆਕਾਰ(*info->ਕੁੰਜੀ_ids)) : ਨਿਰਾ;
    info->ਅੰਕ_ਕੁੰਜੀ_ids = ਅੰਕ_ਕੁੰਜੀ_ids;
    info->ਕੁੰਜੀ_id_ਮਾਪ = ਕੁੰਜੀ_id_ਮਾਪ;
    info->ਅੰਕੜੇ = av_mallocz(ਅੰਕੜੇ_ਮਾਪ);
    info->ਅੰਕੜੇ_ਮਾਪ = ਅੰਕੜੇ_ਮਾਪ;

    // Allow pointers to be NULL if the size is 0.
    ਜੇ ((!info->system_id && system_id_ਮਾਪ) || (!info->ਅੰਕੜੇ && ਅੰਕੜੇ_ਮਾਪ) ||
        (!info->ਕੁੰਜੀ_ids && ਅੰਕ_ਕੁੰਜੀ_ids && ਕੁੰਜੀ_id_ਮਾਪ)) {
        av_encryption_init_info_free(info);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (ਕੁੰਜੀ_id_ਮਾਪ) {
        ਲਈ (i = 0; i < ਅੰਕ_ਕੁੰਜੀ_ids; i++) {
            info->ਕੁੰਜੀ_ids[i] = av_mallocz(ਕੁੰਜੀ_id_ਮਾਪ);
            ਜੇ (!info->ਕੁੰਜੀ_ids[i]) {
                av_encryption_init_info_free(info);
                ਵਾਪਸ ਨਿਰਾ;
            }
        }
    }

    ਵਾਪਸ info;
}

ਖਾਲੀ av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    ਜਦੋਂ (info) {
        AVEncryptionInitInfo *ਅਗਲਾ = info->ਅਗਲਾ;
        uint32_t i;

        ਲਈ (i = 0; i < info->ਅੰਕ_ਕੁੰਜੀ_ids; i++) {
            av_free(info->ਕੁੰਜੀ_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->ਕੁੰਜੀ_ids);
        av_free(info->ਅੰਕੜੇ);
        av_free(info);

        info = ਅਗਲਾ;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_ਅੰਕੜੇ(
    ਅਚਲ uint8_t *side_ਅੰਕੜੇ, size_t side_ਅੰਕੜੇ_ਮਾਪ)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = ਨਿਰਾ, *info, *ਆਰਜ਼ੀ_info;
    uint64_t system_id_ਮਾਪ, ਅੰਕ_ਕੁੰਜੀ_ids, ਕੁੰਜੀ_id_ਮਾਪ, ਅੰਕੜੇ_ਮਾਪ, i, j;
    uint64_t init_info_ਗਿਣਤੀ;

    ਜੇ (!side_ਅੰਕੜੇ || side_ਅੰਕੜੇ_ਮਾਪ < 4)
        ਵਾਪਸ ਨਿਰਾ;

    init_info_ਗਿਣਤੀ = AV_RB32(side_ਅੰਕੜੇ);
    side_ਅੰਕੜੇ += 4;
    side_ਅੰਕੜੇ_ਮਾਪ -= 4;
    ਲਈ (i = 0; i < init_info_ਗਿਣਤੀ; i++) {
        ਜੇ (side_ਅੰਕੜੇ_ਮਾਪ < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            ਵਾਪਸ ਨਿਰਾ;
        }

        system_id_ਮਾਪ = AV_RB32(side_ਅੰਕੜੇ);
        ਅੰਕ_ਕੁੰਜੀ_ids = AV_RB32(side_ਅੰਕੜੇ + 4);
        ਕੁੰਜੀ_id_ਮਾਪ = AV_RB32(side_ਅੰਕੜੇ + 8);
        ਅੰਕੜੇ_ਮਾਪ = AV_RB32(side_ਅੰਕੜੇ + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        ਜੇ (side_ਅੰਕੜੇ_ਮਾਪ - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_ਮਾਪ + ਅੰਕੜੇ_ਮਾਪ + ਅੰਕ_ਕੁੰਜੀ_ids * ਕੁੰਜੀ_id_ਮਾਪ) {
            av_encryption_init_info_free(ret);
            ਵਾਪਸ ਨਿਰਾ;
        }
        side_ਅੰਕੜੇ += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_ਅੰਕੜੇ_ਮਾਪ -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        ਆਰਜ਼ੀ_info = av_encryption_init_info_alloc(system_id_ਮਾਪ, ਅੰਕ_ਕੁੰਜੀ_ids, ਕੁੰਜੀ_id_ਮਾਪ, ਅੰਕੜੇ_ਮਾਪ);
        ਜੇ (!ਆਰਜ਼ੀ_info) {
            av_encryption_init_info_free(ret);
            ਵਾਪਸ ਨਿਰਾ;
        }
        ਜੇ (i == 0) {
            info = ret = ਆਰਜ਼ੀ_info;
        } ਨਹੀਂਤਾਂ {
            info->ਅਗਲਾ = ਆਰਜ਼ੀ_info;
            info = ਆਰਜ਼ੀ_info;
        }

        ਸਮ੍ਰਿਤੀ_ਨਕਲ(info->system_id, side_ਅੰਕੜੇ, system_id_ਮਾਪ);
        side_ਅੰਕੜੇ += system_id_ਮਾਪ;
        side_ਅੰਕੜੇ_ਮਾਪ -= system_id_ਮਾਪ;
        ਲਈ (j = 0; j < ਅੰਕ_ਕੁੰਜੀ_ids; j++) {
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(info->ਕੁੰਜੀ_ids[j], side_ਅੰਕੜੇ, ਕੁੰਜੀ_id_ਮਾਪ);
            side_ਅੰਕੜੇ += ਕੁੰਜੀ_id_ਮਾਪ;
            side_ਅੰਕੜੇ_ਮਾਪ -= ਕੁੰਜੀ_id_ਮਾਪ;
        }
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(info->ਅੰਕੜੇ, side_ਅੰਕੜੇ, ਅੰਕੜੇ_ਮਾਪ);
        side_ਅੰਕੜੇ += ਅੰਕੜੇ_ਮਾਪ;
        side_ਅੰਕੜੇ_ਮਾਪ -= ਅੰਕੜੇ_ਮਾਪ;
    }

    ਵਾਪਸ ret;
}

ਪੂਰਨ av_encryption_init_info_append_side_ਅੰਕੜੇ(uint8_t **side_ਅੰਕੜੇ, size_t *side_ਅੰਕੜੇ_ਮਾਪ,
                                             ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *allocated_ਮਾਪ,
                                             ਅਚਲ AVEncryptionInitInfo *info)
{
    ਅਚਲ AVEncryptionInitInfo *cur_info;
    uint8_t *ਬਫਰ, *cur_ਬਫਰ;
    uint32_t i;
    uint64_t init_info_ਗਿਣਤੀ    = *side_ਅੰਕੜੇ ? AV_RB32(*side_ਅੰਕੜੇ) : 0;
    size_t   old_side_ਅੰਕੜੇ_ਮਾਪ = *side_ਅੰਕੜੇ ? *side_ਅੰਕੜੇ_ਮਾਪ : 4;
    uint64_t new_side_ਅੰਕੜੇ_ਮਾਪ = old_side_ਅੰਕੜੇ_ਮਾਪ;

    ਲਈ (cur_info = info; cur_info; cur_info = cur_info->ਅਗਲਾ) {
        new_side_ਅੰਕੜੇ_ਮਾਪ += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_ਮਾਪ + cur_info->ਅੰਕੜੇ_ਮਾਪ;
        ਜੇ (init_info_ਗਿਣਤੀ == UINT32_MAX || new_side_ਅੰਕੜੇ_ਮਾਪ > UINT32_MAX)
            ਵਾਪਸ AVERROR(EINVAL);
        init_info_ਗਿਣਤੀ++;

        ਜੇ (cur_info->ਅੰਕ_ਕੁੰਜੀ_ids) {
            new_side_ਅੰਕੜੇ_ਮਾਪ += (uint64_t)cur_info->ਅੰਕ_ਕੁੰਜੀ_ids * cur_info->ਕੁੰਜੀ_id_ਮਾਪ;
            ਜੇ (new_side_ਅੰਕੜੇ_ਮਾਪ > UINT32_MAX)
                ਵਾਪਸ AVERROR(EINVAL);
        }
    }

    ਬਫਰ = av_fast_realloc(*side_ਅੰਕੜੇ, allocated_ਮਾਪ, new_side_ਅੰਕੜੇ_ਮਾਪ);
    ਜੇ (!ਬਫਰ)
        ਵਾਪਸ AVERROR(ENOMEM);

    AV_WB32(ਬਫਰ, init_info_ਗਿਣਤੀ);
    cur_ਬਫਰ = ਬਫਰ + old_side_ਅੰਕੜੇ_ਮਾਪ;
    ਲਈ (cur_info = info; cur_info; cur_info = cur_info->ਅਗਲਾ) {
        AV_WB32(cur_ਬਫਰ,      cur_info->system_id_ਮਾਪ);
        AV_WB32(cur_ਬਫਰ +  4, cur_info->ਅੰਕ_ਕੁੰਜੀ_ids);
        AV_WB32(cur_ਬਫਰ +  8, cur_info->ਕੁੰਜੀ_id_ਮਾਪ);
        AV_WB32(cur_ਬਫਰ + 12, cur_info->ਅੰਕੜੇ_ਮਾਪ);
        cur_ਬਫਰ += 16;

        ਸਮ੍ਰਿਤੀ_ਨਕਲ(cur_ਬਫਰ, cur_info->system_id, cur_info->system_id_ਮਾਪ);
        cur_ਬਫਰ += cur_info->system_id_ਮਾਪ;
        ਲਈ (i = 0; i < cur_info->ਅੰਕ_ਕੁੰਜੀ_ids; i++) {
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(cur_ਬਫਰ, cur_info->ਕੁੰਜੀ_ids[i], cur_info->ਕੁੰਜੀ_id_ਮਾਪ);
            cur_ਬਫਰ += cur_info->ਕੁੰਜੀ_id_ਮਾਪ;
        }
        ਜੇ (cur_info->ਅੰਕੜੇ_ਮਾਪ > 0) {
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(cur_ਬਫਰ, cur_info->ਅੰਕੜੇ, cur_info->ਅੰਕੜੇ_ਮਾਪ);
            cur_ਬਫਰ += cur_info->ਅੰਕੜੇ_ਮਾਪ;
        }
    }

    *side_ਅੰਕੜੇ      = ਬਫਰ;
    *side_ਅੰਕੜੇ_ਮਾਪ = new_side_ਅੰਕੜੇ_ਮਾਪ;
    ਵਾਪਸ 0;
}

uint8_t *av_encryption_init_info_ਜੋੜੋ_side_ਅੰਕੜੇ(ਅਚਲ AVEncryptionInitInfo *info, size_t *side_ਅੰਕੜੇ_ਮਾਪ)
{
    uint8_t *side_ਅੰਕੜੇ = ਨਿਰਾ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ allocated_ਮਾਪ = 0;

    ਜੇ (av_encryption_init_info_append_side_ਅੰਕੜੇ(&side_ਅੰਕੜੇ, side_ਅੰਕੜੇ_ਮਾਪ, &allocated_ਮਾਪ, info) < 0)
        ਵਾਪਸ ਨਿਰਾ;
    ਵਾਪਸ side_ਅੰਕੜੇ;
}
