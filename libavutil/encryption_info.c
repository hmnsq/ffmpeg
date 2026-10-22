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

#شامل <string.h>

#شامل "encryption_info.h"
#شامل "error.h"
#شامل "mem.h"
#شامل "intreadwrite.h"

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_گنتی, uint32_t کلید_id_سائز, uint32_t iv_سائز)
{
    AVEncryptionInfo *info;

    info = av_mallocz(حجم(*info));
    اگر (!info)
        واپس تہی;

    info->کلید_id = av_mallocz(کلید_id_سائز);
    info->کلید_id_سائز = کلید_id_سائز;
    info->iv = av_mallocz(iv_سائز);
    info->iv_سائز = iv_سائز;
    info->subsamples = av_calloc(subsample_گنتی, حجم(*info->subsamples));
    info->subsample_گنتی = subsample_گنتی;

    // Allow info->subsamples to be NULL if there are no subsamples.
    اگر (!info->کلید_id || !info->iv || (!info->subsamples && subsample_گنتی)) {
        av_encryption_info_free(info);
        واپس تہی;
    }

    واپس info;
}

AVEncryptionInfo *av_encryption_info_clone(ثابت AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_گنتی, info->کلید_id_سائز, info->iv_سائز);
    اگر (!ret)
        واپس تہی;

    ret->scheme = info->scheme;
    ret->crypt_byte_بلاک = info->crypt_byte_بلاک;
    ret->skip_byte_بلاک = info->skip_byte_بلاک;
    حافظہ_نقل(ret->iv, info->iv, info->iv_سائز);
    حافظہ_نقل(ret->کلید_id, info->کلید_id, info->کلید_id_سائز);
    حافظہ_نقل(ret->subsamples, info->subsamples, حجم(*info->subsamples) * info->subsample_گنتی);
    واپس ret;
}

خالی av_encryption_info_free(AVEncryptionInfo *info)
{
    اگر (info) {
        av_free(info->کلید_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_ڈیٹا(ثابت uint8_t* بفر, size_t سائز)
{
    AVEncryptionInfo *info;
    uint64_t کلید_id_سائز, iv_سائز, subsample_گنتی, i;

    اگر (!بفر || سائز < FF_ENCRYPTION_INFO_EXTRA)
        واپس تہی;

    کلید_id_سائز = AV_RB32(بفر + 12);
    iv_سائز = AV_RB32(بفر + 16);
    subsample_گنتی = AV_RB32(بفر + 20);

    اگر (سائز < FF_ENCRYPTION_INFO_EXTRA + کلید_id_سائز + iv_سائز + subsample_گنتی * 8)
        واپس تہی;

    info = av_encryption_info_alloc(subsample_گنتی, کلید_id_سائز, iv_سائز);
    اگر (!info)
        واپس تہی;

    info->scheme = AV_RB32(بفر);
    info->crypt_byte_بلاک = AV_RB32(بفر + 4);
    info->skip_byte_بلاک = AV_RB32(بفر + 8);
    حافظہ_نقل(info->کلید_id, بفر + 24, کلید_id_سائز);
    حافظہ_نقل(info->iv, بفر + کلید_id_سائز + 24, iv_سائز);

    بفر += کلید_id_سائز + iv_سائز + 24;
    برائے (i = 0; i < subsample_گنتی; i++) {
        info->subsamples[i].بائٹیں_کا_clear_ڈیٹا = AV_RB32(بفر);
        info->subsamples[i].بائٹیں_کا_protected_ڈیٹا = AV_RB32(بفر + 4);
        بفر += 8;
    }

    واپس info;
}

uint8_t *av_encryption_info_جوڑو_side_ڈیٹا(ثابت AVEncryptionInfo *info, size_t *سائز)
{
    uint8_t *بفر, *cur_بفر;
    uint32_t i;

    اگر (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->کلید_id_سائز ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->کلید_id_سائز < info->iv_سائز ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->کلید_id_سائز - info->iv_سائز) / 8 < info->subsample_گنتی) {
        واپس تہی;
    }

    *سائز = FF_ENCRYPTION_INFO_EXTRA + info->کلید_id_سائز + info->iv_سائز +
            (info->subsample_گنتی * 8);
    cur_بفر = بفر = av_malloc(*سائز);
    اگر (!بفر)
        واپس تہی;

    AV_WB32(cur_بفر,      info->scheme);
    AV_WB32(cur_بفر +  4, info->crypt_byte_بلاک);
    AV_WB32(cur_بفر +  8, info->skip_byte_بلاک);
    AV_WB32(cur_بفر + 12, info->کلید_id_سائز);
    AV_WB32(cur_بفر + 16, info->iv_سائز);
    AV_WB32(cur_بفر + 20, info->subsample_گنتی);
    cur_بفر += 24;
    حافظہ_نقل(cur_بفر, info->کلید_id, info->کلید_id_سائز);
    cur_بفر += info->کلید_id_سائز;
    حافظہ_نقل(cur_بفر, info->iv, info->iv_سائز);
    cur_بفر += info->iv_سائز;
    برائے (i = 0; i < info->subsample_گنتی; i++) {
        AV_WB32(cur_بفر, info->subsamples[i].بائٹیں_کا_clear_ڈیٹا);
        AV_WB32(cur_بفر + 4, info->subsamples[i].بائٹیں_کا_protected_ڈیٹا);
        cur_بفر += 8;
    }

    واپس بفر;
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
    uint32_t system_id_سائز, uint32_t عدد_کلید_ids, uint32_t کلید_id_سائز, uint32_t ڈیٹا_سائز)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    اگر (عدد_کلید_ids && !کلید_id_سائز)
        واپس تہی;

    info = av_mallocz(حجم(*info));
    اگر (!info)
        واپس تہی;

    info->system_id = av_mallocz(system_id_سائز);
    info->system_id_سائز = system_id_سائز;
    info->کلید_ids = کلید_id_سائز ? av_calloc(عدد_کلید_ids, حجم(*info->کلید_ids)) : تہی;
    info->عدد_کلید_ids = عدد_کلید_ids;
    info->کلید_id_سائز = کلید_id_سائز;
    info->ڈیٹا = av_mallocz(ڈیٹا_سائز);
    info->ڈیٹا_سائز = ڈیٹا_سائز;

    // Allow pointers to be NULL if the size is 0.
    اگر ((!info->system_id && system_id_سائز) || (!info->ڈیٹا && ڈیٹا_سائز) ||
        (!info->کلید_ids && عدد_کلید_ids && کلید_id_سائز)) {
        av_encryption_init_info_free(info);
        واپس تہی;
    }

    اگر (کلید_id_سائز) {
        برائے (i = 0; i < عدد_کلید_ids; i++) {
            info->کلید_ids[i] = av_mallocz(کلید_id_سائز);
            اگر (!info->کلید_ids[i]) {
                av_encryption_init_info_free(info);
                واپس تہی;
            }
        }
    }

    واپس info;
}

خالی av_encryption_init_info_free(AVEncryptionInitInfo *info)
{
    جب (info) {
        AVEncryptionInitInfo *اگلا = info->اگلا;
        uint32_t i;

        برائے (i = 0; i < info->عدد_کلید_ids; i++) {
            av_free(info->کلید_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->کلید_ids);
        av_free(info->ڈیٹا);
        av_free(info);

        info = اگلا;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_ڈیٹا(
    ثابت uint8_t *side_ڈیٹا, size_t side_ڈیٹا_سائز)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = تہی, *info, *عارضی_info;
    uint64_t system_id_سائز, عدد_کلید_ids, کلید_id_سائز, ڈیٹا_سائز, i, j;
    uint64_t init_info_گنتی;

    اگر (!side_ڈیٹا || side_ڈیٹا_سائز < 4)
        واپس تہی;

    init_info_گنتی = AV_RB32(side_ڈیٹا);
    side_ڈیٹا += 4;
    side_ڈیٹا_سائز -= 4;
    برائے (i = 0; i < init_info_گنتی; i++) {
        اگر (side_ڈیٹا_سائز < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            واپس تہی;
        }

        system_id_سائز = AV_RB32(side_ڈیٹا);
        عدد_کلید_ids = AV_RB32(side_ڈیٹا + 4);
        کلید_id_سائز = AV_RB32(side_ڈیٹا + 8);
        ڈیٹا_سائز = AV_RB32(side_ڈیٹا + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        اگر (side_ڈیٹا_سائز - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_سائز + ڈیٹا_سائز + عدد_کلید_ids * کلید_id_سائز) {
            av_encryption_init_info_free(ret);
            واپس تہی;
        }
        side_ڈیٹا += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_ڈیٹا_سائز -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        عارضی_info = av_encryption_init_info_alloc(system_id_سائز, عدد_کلید_ids, کلید_id_سائز, ڈیٹا_سائز);
        اگر (!عارضی_info) {
            av_encryption_init_info_free(ret);
            واپس تہی;
        }
        اگر (i == 0) {
            info = ret = عارضی_info;
        } ورنہ {
            info->اگلا = عارضی_info;
            info = عارضی_info;
        }

        حافظہ_نقل(info->system_id, side_ڈیٹا, system_id_سائز);
        side_ڈیٹا += system_id_سائز;
        side_ڈیٹا_سائز -= system_id_سائز;
        برائے (j = 0; j < عدد_کلید_ids; j++) {
            حافظہ_نقل(info->کلید_ids[j], side_ڈیٹا, کلید_id_سائز);
            side_ڈیٹا += کلید_id_سائز;
            side_ڈیٹا_سائز -= کلید_id_سائز;
        }
        حافظہ_نقل(info->ڈیٹا, side_ڈیٹا, ڈیٹا_سائز);
        side_ڈیٹا += ڈیٹا_سائز;
        side_ڈیٹا_سائز -= ڈیٹا_سائز;
    }

    واپس ret;
}

صحیح av_encryption_init_info_append_side_ڈیٹا(uint8_t **side_ڈیٹا, size_t *side_ڈیٹا_سائز,
                                             غیرعلامتی صحیح *allocated_سائز,
                                             ثابت AVEncryptionInitInfo *info)
{
    ثابت AVEncryptionInitInfo *cur_info;
    uint8_t *بفر, *cur_بفر;
    uint32_t i;
    uint64_t init_info_گنتی    = *side_ڈیٹا ? AV_RB32(*side_ڈیٹا) : 0;
    size_t   old_side_ڈیٹا_سائز = *side_ڈیٹا ? *side_ڈیٹا_سائز : 4;
    uint64_t new_side_ڈیٹا_سائز = old_side_ڈیٹا_سائز;

    برائے (cur_info = info; cur_info; cur_info = cur_info->اگلا) {
        new_side_ڈیٹا_سائز += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_سائز + cur_info->ڈیٹا_سائز;
        اگر (init_info_گنتی == UINT32_MAX || new_side_ڈیٹا_سائز > UINT32_MAX)
            واپس AVERROR(EINVAL);
        init_info_گنتی++;

        اگر (cur_info->عدد_کلید_ids) {
            new_side_ڈیٹا_سائز += (uint64_t)cur_info->عدد_کلید_ids * cur_info->کلید_id_سائز;
            اگر (new_side_ڈیٹا_سائز > UINT32_MAX)
                واپس AVERROR(EINVAL);
        }
    }

    بفر = av_fast_realloc(*side_ڈیٹا, allocated_سائز, new_side_ڈیٹا_سائز);
    اگر (!بفر)
        واپس AVERROR(ENOMEM);

    AV_WB32(بفر, init_info_گنتی);
    cur_بفر = بفر + old_side_ڈیٹا_سائز;
    برائے (cur_info = info; cur_info; cur_info = cur_info->اگلا) {
        AV_WB32(cur_بفر,      cur_info->system_id_سائز);
        AV_WB32(cur_بفر +  4, cur_info->عدد_کلید_ids);
        AV_WB32(cur_بفر +  8, cur_info->کلید_id_سائز);
        AV_WB32(cur_بفر + 12, cur_info->ڈیٹا_سائز);
        cur_بفر += 16;

        حافظہ_نقل(cur_بفر, cur_info->system_id, cur_info->system_id_سائز);
        cur_بفر += cur_info->system_id_سائز;
        برائے (i = 0; i < cur_info->عدد_کلید_ids; i++) {
            حافظہ_نقل(cur_بفر, cur_info->کلید_ids[i], cur_info->کلید_id_سائز);
            cur_بفر += cur_info->کلید_id_سائز;
        }
        اگر (cur_info->ڈیٹا_سائز > 0) {
            حافظہ_نقل(cur_بفر, cur_info->ڈیٹا, cur_info->ڈیٹا_سائز);
            cur_بفر += cur_info->ڈیٹا_سائز;
        }
    }

    *side_ڈیٹا      = بفر;
    *side_ڈیٹا_سائز = new_side_ڈیٹا_سائز;
    واپس 0;
}

uint8_t *av_encryption_init_info_جوڑو_side_ڈیٹا(ثابت AVEncryptionInitInfo *info, size_t *side_ڈیٹا_سائز)
{
    uint8_t *side_ڈیٹا = تہی;
    غیرعلامتی صحیح allocated_سائز = 0;

    اگر (av_encryption_init_info_append_side_ڈیٹا(&side_ڈیٹا, side_ڈیٹا_سائز, &allocated_سائز, info) < 0)
        واپس تہی;
    واپس side_ڈیٹا;
}
