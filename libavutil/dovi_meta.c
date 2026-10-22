/*
 * Copyright (c) 2020 Jun Zhao<barryjzhao@tencent.com>
 *
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

#ضمن "dovi_meta.h"
#ضمن "mem.h"

AVDOVIDecoder_Configuration_ریکارډ *av_dovi_alloc(size_t *اندازه)
{
    AVDOVIDecoder_Configuration_ریکارډ *dovi =
        av_mallocz(حجم(AVDOVIDecoder_Configuration_ریکارډ));

    إذا (اندازه)
        *اندازه = dovi ? حجم(*dovi) : 0;

    أرجع dovi;
}

تعريفنوع بنية AVDOVIMetadata_دننی {
    AVDOVIMetadata metadata;
    AVDOVIRpu_معلومات_سرلیک سرلیک;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDm_معلومات ext_بلاکونه[AV_DOVI_MAX_EXT_بلاکونه];
} AVDOVIMetadata_دننی;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *اندازه)
{
    AVDOVIMetadata_دننی *dovi = av_mallocz(حجم(AVDOVIMetadata_دننی));

    إذا (اندازه)
        *اندازه = dovi ? حجم(*dovi) : 0;

    إذا (!dovi)
        أرجع عدم;

    dovi->metadata = (بنية AVDOVIMetadata) {
        .سرلیک_دننه_واټن      = offsetof(AVDOVIMetadata_دننی, سرلیک),
        .mapping_دننه_واټن     = offsetof(AVDOVIMetadata_دننی, mapping),
        .color_دننه_واټن       = offsetof(AVDOVIMetadata_دننی, color),
        .ext_بلاک_دننه_واټن   = offsetof(AVDOVIMetadata_دننی, ext_بلاکونه),
        .ext_بلاک_اندازه     = حجم(AVDOVIDm_معلومات),
    };

    أرجع &dovi->metadata;
}

AVDOVIDm_معلومات *av_dovi_پیدا_کړه_level(ثابت AVDOVIMetadata *معلومات, uint8_t level)
{
    لكل (صحيح i = 0; i < معلومات->عدد_ext_بلاکونه; i++) {
        AVDOVIDm_معلومات *ext = av_dovi_get_ext(معلومات, i);
        إذا (ext->level == level)
            أرجع ext;
    }

    أرجع عدم;
}
