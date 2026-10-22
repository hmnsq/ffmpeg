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

#تعریف_کړه FF_ENCRYPTION_INFO_EXTRA 24

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_شمېر, uint32_t کلی_id_اندازه, uint32_t iv_اندازه)
{
    AVEncryptionInfo *info;

    info = av_mallocz(حجم(*info));
    إذا (!info)
        أرجع عدم;

    info->کلی_id = av_mallocz(کلی_id_اندازه);
    info->کلی_id_اندازه = کلی_id_اندازه;
    info->iv = av_mallocz(iv_اندازه);
    info->iv_اندازه = iv_اندازه;
    info->subsamples = av_calloc(subsample_شمېر, حجم(*info->subsamples));
    info->subsample_شمېر = subsample_شمېر;

    // Allow info->subsamples to be NULL if there are no subsamples.
    إذا (!info->کلی_id || !info->iv || (!info->subsamples && subsample_شمېر)) {
        av_encryption_info_free(info);
        أرجع عدم;
    }

    أرجع info;
}

AVEncryptionInfo *av_encryption_info_clone(ثابت AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_شمېر, info->کلی_id_اندازه, info->iv_اندازه);
    إذا (!ret)
        أرجع عدم;

    ret->scheme = info->scheme;
    ret->crypt_byte_بلاک = info->crypt_byte_بلاک;
    ret->skip_byte_بلاک = info->skip_byte_بلاک;
    حافظه_نقل(ret->iv, info->iv, info->iv_اندازه);
    حافظه_نقل(ret->کلی_id, info->کلی_id, info->کلی_id_اندازه);
    حافظه_نقل(ret->subsamples, info->subsamples, حجم(*info->subsamples) * info->subsample_شمېر);
    أرجع ret;
}

فراغ av_encryption_info_free(AVEncryptionInfo *info)
{
    إذا (info) {
        av_free(info->کلی_id);
        av_free(info->iv);
        av_free(info->subsamples);
        av_free(info);
    }
}

AVEncryptionInfo *av_encryption_info_get_side_معلومات(ثابت uint8_t* بفر, size_t اندازه)
{
    AVEncryptionInfo *info;
    uint64_t کلی_id_اندازه, iv_اندازه, subsample_شمېر, i;

    إذا (!بفر || اندازه < FF_ENCRYPTION_INFO_EXTRA)
        أرجع عدم;

    کلی_id_اندازه = AV_RB32(بفر + 12);
    iv_اندازه = AV_RB32(بفر + 16);
    subsample_شمېر = AV_RB32(بفر + 20);

    إذا (اندازه < FF_ENCRYPTION_INFO_EXTRA + کلی_id_اندازه + iv_اندازه + subsample_شمېر * 8)
        أرجع عدم;

    info = av_encryption_info_alloc(subsample_شمېر, کلی_id_اندازه, iv_اندازه);
    إذا (!info)
        أرجع عدم;

    info->scheme = AV_RB32(بفر);
    info->crypt_byte_بلاک = AV_RB32(بفر + 4);
    info->skip_byte_بلاک = AV_RB32(بفر + 8);
    حافظه_نقل(info->کلی_id, بفر + 24, کلی_id_اندازه);
    حافظه_نقل(info->iv, بفر + کلی_id_اندازه + 24, iv_اندازه);

    بفر += کلی_id_اندازه + iv_اندازه + 24;
    لكل (i = 0; i < subsample_شمېر; i++) {
        info->subsamples[i].بایټونه_د_clear_معلومات = AV_RB32(بفر);
        info->subsamples[i].بایټونه_د_protected_معلومات = AV_RB32(بفر + 4);
        بفر += 8;
    }

    أرجع info;
}

uint8_t *av_encryption_info_جمع_کړه_side_معلومات(ثابت AVEncryptionInfo *info, size_t *اندازه)
{
    uint8_t *بفر, *cur_بفر;
    uint32_t i;

    إذا (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->کلی_id_اندازه ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->کلی_id_اندازه < info->iv_اندازه ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->کلی_id_اندازه - info->iv_اندازه) / 8 < info->subsample_شمېر) {
        أرجع عدم;
    }

    *اندازه = FF_ENCRYPTION_INFO_EXTRA + info->کلی_id_اندازه + info->iv_اندازه +
            (info->subsample_شمېر * 8);
    cur_بفر = بفر = av_malloc(*اندازه);
    إذا (!بفر)
        أرجع عدم;

    AV_WB32(cur_بفر,      info->scheme);
    AV_WB32(cur_بفر +  4, info->crypt_byte_بلاک);
    AV_WB32(cur_بفر +  8, info->skip_byte_بلاک);
    AV_WB32(cur_بفر + 12, info->کلی_id_اندازه);
    AV_WB32(cur_بفر + 16, info->iv_اندازه);
    AV_WB32(cur_بفر + 20, info->subsample_شمېر);
    cur_بفر += 24;
    حافظه_نقل(cur_بفر, info->کلی_id, info->کلی_id_اندازه);
    cur_بفر += info->کلی_id_اندازه;
    حافظه_نقل(cur_بفر, info->iv, info->iv_اندازه);
    cur_بفر += info->iv_اندازه;
    لكل (i = 0; i < info->subsample_شمېر; i++) {
        AV_WB32(cur_بفر, info->subsamples[i].بایټونه_د_clear_معلومات);
        AV_WB32(cur_بفر + 4, info->subsamples[i].بایټونه_د_protected_معلومات);
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

#تعریف_کړه FF_ENCRYPTION_INIT_INFO_EXTRA 16

AVEncryptionInitInfo *av_encryption_init_info_alloc(
    uint32_t system_id_اندازه, uint32_t عدد_کلی_ids, uint32_t کلی_id_اندازه, uint32_t معلومات_اندازه)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    إذا (عدد_کلی_ids && !کلی_id_اندازه)
        أرجع عدم;

    info = av_mallocz(حجم(*info));
    إذا (!info)
        أرجع عدم;

    info->system_id = av_mallocz(system_id_اندازه);
    info->system_id_اندازه = system_id_اندازه;
    info->کلی_ids = کلی_id_اندازه ? av_calloc(عدد_کلی_ids, حجم(*info->کلی_ids)) : عدم;
    info->عدد_کلی_ids = عدد_کلی_ids;
    info->کلی_id_اندازه = کلی_id_اندازه;
    info->معلومات = av_mallocz(معلومات_اندازه);
    info->معلومات_اندازه = معلومات_اندازه;

    // Allow pointers to be NULL if the size is 0.
    إذا ((!info->system_id && system_id_اندازه) || (!info->معلومات && معلومات_اندازه) ||
        (!info->کلی_ids && عدد_کلی_ids && کلی_id_اندازه)) {
        av_encryption_init_info_free(info);
        أرجع عدم;
    }

    إذا (کلی_id_اندازه) {
        لكل (i = 0; i < عدد_کلی_ids; i++) {
            info->کلی_ids[i] = av_mallocz(کلی_id_اندازه);
            إذا (!info->کلی_ids[i]) {
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
        AVEncryptionInitInfo *بل = info->بل;
        uint32_t i;

        لكل (i = 0; i < info->عدد_کلی_ids; i++) {
            av_free(info->کلی_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->کلی_ids);
        av_free(info->معلومات);
        av_free(info);

        info = بل;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_معلومات(
    ثابت uint8_t *side_معلومات, size_t side_معلومات_اندازه)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = عدم, *info, *لنډمهاله_info;
    uint64_t system_id_اندازه, عدد_کلی_ids, کلی_id_اندازه, معلومات_اندازه, i, j;
    uint64_t init_info_شمېر;

    إذا (!side_معلومات || side_معلومات_اندازه < 4)
        أرجع عدم;

    init_info_شمېر = AV_RB32(side_معلومات);
    side_معلومات += 4;
    side_معلومات_اندازه -= 4;
    لكل (i = 0; i < init_info_شمېر; i++) {
        إذا (side_معلومات_اندازه < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }

        system_id_اندازه = AV_RB32(side_معلومات);
        عدد_کلی_ids = AV_RB32(side_معلومات + 4);
        کلی_id_اندازه = AV_RB32(side_معلومات + 8);
        معلومات_اندازه = AV_RB32(side_معلومات + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        إذا (side_معلومات_اندازه - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_اندازه + معلومات_اندازه + عدد_کلی_ids * کلی_id_اندازه) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }
        side_معلومات += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_معلومات_اندازه -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        لنډمهاله_info = av_encryption_init_info_alloc(system_id_اندازه, عدد_کلی_ids, کلی_id_اندازه, معلومات_اندازه);
        إذا (!لنډمهاله_info) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }
        إذا (i == 0) {
            info = ret = لنډمهاله_info;
        } وإلا {
            info->بل = لنډمهاله_info;
            info = لنډمهاله_info;
        }

        حافظه_نقل(info->system_id, side_معلومات, system_id_اندازه);
        side_معلومات += system_id_اندازه;
        side_معلومات_اندازه -= system_id_اندازه;
        لكل (j = 0; j < عدد_کلی_ids; j++) {
            حافظه_نقل(info->کلی_ids[j], side_معلومات, کلی_id_اندازه);
            side_معلومات += کلی_id_اندازه;
            side_معلومات_اندازه -= کلی_id_اندازه;
        }
        حافظه_نقل(info->معلومات, side_معلومات, معلومات_اندازه);
        side_معلومات += معلومات_اندازه;
        side_معلومات_اندازه -= معلومات_اندازه;
    }

    أرجع ret;
}

صحيح av_encryption_init_info_append_side_معلومات(uint8_t **side_معلومات, size_t *side_معلومات_اندازه,
                                             بینښه صحيح *allocated_اندازه,
                                             ثابت AVEncryptionInitInfo *info)
{
    ثابت AVEncryptionInitInfo *cur_info;
    uint8_t *بفر, *cur_بفر;
    uint32_t i;
    uint64_t init_info_شمېر    = *side_معلومات ? AV_RB32(*side_معلومات) : 0;
    size_t   old_side_معلومات_اندازه = *side_معلومات ? *side_معلومات_اندازه : 4;
    uint64_t new_side_معلومات_اندازه = old_side_معلومات_اندازه;

    لكل (cur_info = info; cur_info; cur_info = cur_info->بل) {
        new_side_معلومات_اندازه += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_اندازه + cur_info->معلومات_اندازه;
        إذا (init_info_شمېر == UINT32_MAX || new_side_معلومات_اندازه > UINT32_MAX)
            أرجع AVERROR(EINVAL);
        init_info_شمېر++;

        إذا (cur_info->عدد_کلی_ids) {
            new_side_معلومات_اندازه += (uint64_t)cur_info->عدد_کلی_ids * cur_info->کلی_id_اندازه;
            إذا (new_side_معلومات_اندازه > UINT32_MAX)
                أرجع AVERROR(EINVAL);
        }
    }

    بفر = av_fast_realloc(*side_معلومات, allocated_اندازه, new_side_معلومات_اندازه);
    إذا (!بفر)
        أرجع AVERROR(ENOMEM);

    AV_WB32(بفر, init_info_شمېر);
    cur_بفر = بفر + old_side_معلومات_اندازه;
    لكل (cur_info = info; cur_info; cur_info = cur_info->بل) {
        AV_WB32(cur_بفر,      cur_info->system_id_اندازه);
        AV_WB32(cur_بفر +  4, cur_info->عدد_کلی_ids);
        AV_WB32(cur_بفر +  8, cur_info->کلی_id_اندازه);
        AV_WB32(cur_بفر + 12, cur_info->معلومات_اندازه);
        cur_بفر += 16;

        حافظه_نقل(cur_بفر, cur_info->system_id, cur_info->system_id_اندازه);
        cur_بفر += cur_info->system_id_اندازه;
        لكل (i = 0; i < cur_info->عدد_کلی_ids; i++) {
            حافظه_نقل(cur_بفر, cur_info->کلی_ids[i], cur_info->کلی_id_اندازه);
            cur_بفر += cur_info->کلی_id_اندازه;
        }
        إذا (cur_info->معلومات_اندازه > 0) {
            حافظه_نقل(cur_بفر, cur_info->معلومات, cur_info->معلومات_اندازه);
            cur_بفر += cur_info->معلومات_اندازه;
        }
    }

    *side_معلومات      = بفر;
    *side_معلومات_اندازه = new_side_معلومات_اندازه;
    أرجع 0;
}

uint8_t *av_encryption_init_info_جمع_کړه_side_معلومات(ثابت AVEncryptionInitInfo *info, size_t *side_معلومات_اندازه)
{
    uint8_t *side_معلومات = عدم;
    بینښه صحيح allocated_اندازه = 0;

    إذا (av_encryption_init_info_append_side_معلومات(&side_معلومات, side_معلومات_اندازه, &allocated_اندازه, info) < 0)
        أرجع عدم;
    أرجع side_معلومات;
}
