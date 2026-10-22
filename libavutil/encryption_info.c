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

#تعریف_کن FF_ENCRYPTION_INFO_EXTRA 24

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

AVEncryptionInfo *av_encryption_info_alloc(uint32_t subsample_شمار, uint32_t کلید_id_اندازه, uint32_t iv_اندازه)
{
    AVEncryptionInfo *info;

    info = av_mallocz(حجم(*info));
    إذا (!info)
        أرجع عدم;

    info->کلید_id = av_mallocz(کلید_id_اندازه);
    info->کلید_id_اندازه = کلید_id_اندازه;
    info->iv = av_mallocz(iv_اندازه);
    info->iv_اندازه = iv_اندازه;
    info->subsamples = av_calloc(subsample_شمار, حجم(*info->subsamples));
    info->subsample_شمار = subsample_شمار;

    // Allow info->subsamples to be NULL if there are no subsamples.
    إذا (!info->کلید_id || !info->iv || (!info->subsamples && subsample_شمار)) {
        av_encryption_info_free(info);
        أرجع عدم;
    }

    أرجع info;
}

AVEncryptionInfo *av_encryption_info_clone(ثابت AVEncryptionInfo *info)
{
    AVEncryptionInfo *ret;

    ret = av_encryption_info_alloc(info->subsample_شمار, info->کلید_id_اندازه, info->iv_اندازه);
    إذا (!ret)
        أرجع عدم;

    ret->scheme = info->scheme;
    ret->crypt_byte_بلوک = info->crypt_byte_بلوک;
    ret->skip_byte_بلوک = info->skip_byte_بلوک;
    کپی_حافظه(ret->iv, info->iv, info->iv_اندازه);
    کپی_حافظه(ret->کلید_id, info->کلید_id, info->کلید_id_اندازه);
    کپی_حافظه(ret->subsamples, info->subsamples, حجم(*info->subsamples) * info->subsample_شمار);
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

AVEncryptionInfo *av_encryption_info_get_side_داده(ثابت uint8_t* میانگیر, size_t اندازه)
{
    AVEncryptionInfo *info;
    uint64_t کلید_id_اندازه, iv_اندازه, subsample_شمار, i;

    إذا (!میانگیر || اندازه < FF_ENCRYPTION_INFO_EXTRA)
        أرجع عدم;

    کلید_id_اندازه = AV_RB32(میانگیر + 12);
    iv_اندازه = AV_RB32(میانگیر + 16);
    subsample_شمار = AV_RB32(میانگیر + 20);

    إذا (اندازه < FF_ENCRYPTION_INFO_EXTRA + کلید_id_اندازه + iv_اندازه + subsample_شمار * 8)
        أرجع عدم;

    info = av_encryption_info_alloc(subsample_شمار, کلید_id_اندازه, iv_اندازه);
    إذا (!info)
        أرجع عدم;

    info->scheme = AV_RB32(میانگیر);
    info->crypt_byte_بلوک = AV_RB32(میانگیر + 4);
    info->skip_byte_بلوک = AV_RB32(میانگیر + 8);
    کپی_حافظه(info->کلید_id, میانگیر + 24, کلید_id_اندازه);
    کپی_حافظه(info->iv, میانگیر + کلید_id_اندازه + 24, iv_اندازه);

    میانگیر += کلید_id_اندازه + iv_اندازه + 24;
    لكل (i = 0; i < subsample_شمار; i++) {
        info->subsamples[i].بایتها_از_clear_داده = AV_RB32(میانگیر);
        info->subsamples[i].بایتها_از_protected_داده = AV_RB32(میانگیر + 4);
        میانگیر += 8;
    }

    أرجع info;
}

uint8_t *av_encryption_info_جمع_کن_side_داده(ثابت AVEncryptionInfo *info, size_t *اندازه)
{
    uint8_t *میانگیر, *cur_میانگیر;
    uint32_t i;

    إذا (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA < info->کلید_id_اندازه ||
        UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->کلید_id_اندازه < info->iv_اندازه ||
        (UINT32_MAX - FF_ENCRYPTION_INFO_EXTRA - info->کلید_id_اندازه - info->iv_اندازه) / 8 < info->subsample_شمار) {
        أرجع عدم;
    }

    *اندازه = FF_ENCRYPTION_INFO_EXTRA + info->کلید_id_اندازه + info->iv_اندازه +
            (info->subsample_شمار * 8);
    cur_میانگیر = میانگیر = av_malloc(*اندازه);
    إذا (!میانگیر)
        أرجع عدم;

    AV_WB32(cur_میانگیر,      info->scheme);
    AV_WB32(cur_میانگیر +  4, info->crypt_byte_بلوک);
    AV_WB32(cur_میانگیر +  8, info->skip_byte_بلوک);
    AV_WB32(cur_میانگیر + 12, info->کلید_id_اندازه);
    AV_WB32(cur_میانگیر + 16, info->iv_اندازه);
    AV_WB32(cur_میانگیر + 20, info->subsample_شمار);
    cur_میانگیر += 24;
    کپی_حافظه(cur_میانگیر, info->کلید_id, info->کلید_id_اندازه);
    cur_میانگیر += info->کلید_id_اندازه;
    کپی_حافظه(cur_میانگیر, info->iv, info->iv_اندازه);
    cur_میانگیر += info->iv_اندازه;
    لكل (i = 0; i < info->subsample_شمار; i++) {
        AV_WB32(cur_میانگیر, info->subsamples[i].بایتها_از_clear_داده);
        AV_WB32(cur_میانگیر + 4, info->subsamples[i].بایتها_از_protected_داده);
        cur_میانگیر += 8;
    }

    أرجع میانگیر;
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

#تعریف_کن FF_ENCRYPTION_INIT_INFO_EXTRA 16

AVEncryptionInitInfo *av_encryption_init_info_alloc(
    uint32_t system_id_اندازه, uint32_t رقم_کلید_ids, uint32_t کلید_id_اندازه, uint32_t داده_اندازه)
{
    AVEncryptionInitInfo *info;
    uint32_t i;

    إذا (رقم_کلید_ids && !کلید_id_اندازه)
        أرجع عدم;

    info = av_mallocz(حجم(*info));
    إذا (!info)
        أرجع عدم;

    info->system_id = av_mallocz(system_id_اندازه);
    info->system_id_اندازه = system_id_اندازه;
    info->کلید_ids = کلید_id_اندازه ? av_calloc(رقم_کلید_ids, حجم(*info->کلید_ids)) : عدم;
    info->رقم_کلید_ids = رقم_کلید_ids;
    info->کلید_id_اندازه = کلید_id_اندازه;
    info->داده = av_mallocz(داده_اندازه);
    info->داده_اندازه = داده_اندازه;

    // Allow pointers to be NULL if the size is 0.
    إذا ((!info->system_id && system_id_اندازه) || (!info->داده && داده_اندازه) ||
        (!info->کلید_ids && رقم_کلید_ids && کلید_id_اندازه)) {
        av_encryption_init_info_free(info);
        أرجع عدم;
    }

    إذا (کلید_id_اندازه) {
        لكل (i = 0; i < رقم_کلید_ids; i++) {
            info->کلید_ids[i] = av_mallocz(کلید_id_اندازه);
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
        AVEncryptionInitInfo *بعدی = info->بعدی;
        uint32_t i;

        لكل (i = 0; i < info->رقم_کلید_ids; i++) {
            av_free(info->کلید_ids[i]);
        }
        av_free(info->system_id);
        av_free(info->کلید_ids);
        av_free(info->داده);
        av_free(info);

        info = بعدی;
    }
}

AVEncryptionInitInfo *av_encryption_init_info_get_side_داده(
    ثابت uint8_t *side_داده, size_t side_داده_اندازه)
{
    // |ret| tracks the front of the list, |info| tracks the back.
    AVEncryptionInitInfo *ret = عدم, *info, *موقت_info;
    uint64_t system_id_اندازه, رقم_کلید_ids, کلید_id_اندازه, داده_اندازه, i, j;
    uint64_t init_info_شمار;

    إذا (!side_داده || side_داده_اندازه < 4)
        أرجع عدم;

    init_info_شمار = AV_RB32(side_داده);
    side_داده += 4;
    side_داده_اندازه -= 4;
    لكل (i = 0; i < init_info_شمار; i++) {
        إذا (side_داده_اندازه < FF_ENCRYPTION_INIT_INFO_EXTRA) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }

        system_id_اندازه = AV_RB32(side_داده);
        رقم_کلید_ids = AV_RB32(side_داده + 4);
        کلید_id_اندازه = AV_RB32(side_داده + 8);
        داده_اندازه = AV_RB32(side_داده + 12);

        // UINT32_MAX + UINT32_MAX + UINT32_MAX * UINT32_MAX == UINT64_MAX
        إذا (side_داده_اندازه - FF_ENCRYPTION_INIT_INFO_EXTRA < system_id_اندازه + داده_اندازه + رقم_کلید_ids * کلید_id_اندازه) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }
        side_داده += FF_ENCRYPTION_INIT_INFO_EXTRA;
        side_داده_اندازه -= FF_ENCRYPTION_INIT_INFO_EXTRA;

        موقت_info = av_encryption_init_info_alloc(system_id_اندازه, رقم_کلید_ids, کلید_id_اندازه, داده_اندازه);
        إذا (!موقت_info) {
            av_encryption_init_info_free(ret);
            أرجع عدم;
        }
        إذا (i == 0) {
            info = ret = موقت_info;
        } وإلا {
            info->بعدی = موقت_info;
            info = موقت_info;
        }

        کپی_حافظه(info->system_id, side_داده, system_id_اندازه);
        side_داده += system_id_اندازه;
        side_داده_اندازه -= system_id_اندازه;
        لكل (j = 0; j < رقم_کلید_ids; j++) {
            کپی_حافظه(info->کلید_ids[j], side_داده, کلید_id_اندازه);
            side_داده += کلید_id_اندازه;
            side_داده_اندازه -= کلید_id_اندازه;
        }
        کپی_حافظه(info->داده, side_داده, داده_اندازه);
        side_داده += داده_اندازه;
        side_داده_اندازه -= داده_اندازه;
    }

    أرجع ret;
}

صحيح av_encryption_init_info_append_side_داده(uint8_t **side_داده, size_t *side_داده_اندازه,
                                             بیعلامت صحيح *allocated_اندازه,
                                             ثابت AVEncryptionInitInfo *info)
{
    ثابت AVEncryptionInitInfo *cur_info;
    uint8_t *میانگیر, *cur_میانگیر;
    uint32_t i;
    uint64_t init_info_شمار    = *side_داده ? AV_RB32(*side_داده) : 0;
    size_t   old_side_داده_اندازه = *side_داده ? *side_داده_اندازه : 4;
    uint64_t new_side_داده_اندازه = old_side_داده_اندازه;

    لكل (cur_info = info; cur_info; cur_info = cur_info->بعدی) {
        new_side_داده_اندازه += (uint64_t)FF_ENCRYPTION_INIT_INFO_EXTRA + cur_info->system_id_اندازه + cur_info->داده_اندازه;
        إذا (init_info_شمار == UINT32_MAX || new_side_داده_اندازه > UINT32_MAX)
            أرجع AVERROR(EINVAL);
        init_info_شمار++;

        إذا (cur_info->رقم_کلید_ids) {
            new_side_داده_اندازه += (uint64_t)cur_info->رقم_کلید_ids * cur_info->کلید_id_اندازه;
            إذا (new_side_داده_اندازه > UINT32_MAX)
                أرجع AVERROR(EINVAL);
        }
    }

    میانگیر = av_fast_realloc(*side_داده, allocated_اندازه, new_side_داده_اندازه);
    إذا (!میانگیر)
        أرجع AVERROR(ENOMEM);

    AV_WB32(میانگیر, init_info_شمار);
    cur_میانگیر = میانگیر + old_side_داده_اندازه;
    لكل (cur_info = info; cur_info; cur_info = cur_info->بعدی) {
        AV_WB32(cur_میانگیر,      cur_info->system_id_اندازه);
        AV_WB32(cur_میانگیر +  4, cur_info->رقم_کلید_ids);
        AV_WB32(cur_میانگیر +  8, cur_info->کلید_id_اندازه);
        AV_WB32(cur_میانگیر + 12, cur_info->داده_اندازه);
        cur_میانگیر += 16;

        کپی_حافظه(cur_میانگیر, cur_info->system_id, cur_info->system_id_اندازه);
        cur_میانگیر += cur_info->system_id_اندازه;
        لكل (i = 0; i < cur_info->رقم_کلید_ids; i++) {
            کپی_حافظه(cur_میانگیر, cur_info->کلید_ids[i], cur_info->کلید_id_اندازه);
            cur_میانگیر += cur_info->کلید_id_اندازه;
        }
        إذا (cur_info->داده_اندازه > 0) {
            کپی_حافظه(cur_میانگیر, cur_info->داده, cur_info->داده_اندازه);
            cur_میانگیر += cur_info->داده_اندازه;
        }
    }

    *side_داده      = میانگیر;
    *side_داده_اندازه = new_side_داده_اندازه;
    أرجع 0;
}

uint8_t *av_encryption_init_info_جمع_کن_side_داده(ثابت AVEncryptionInitInfo *info, size_t *side_داده_اندازه)
{
    uint8_t *side_داده = عدم;
    بیعلامت صحيح allocated_اندازه = 0;

    إذا (av_encryption_init_info_append_side_داده(&side_داده, side_داده_اندازه, &allocated_اندازه, info) < 0)
        أرجع عدم;
    أرجع side_داده;
}
