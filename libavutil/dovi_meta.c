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

AVDOVIDecoder_Configuration_رکورد *av_dovi_alloc(size_t *اندازه)
{
    AVDOVIDecoder_Configuration_رکورد *dovi =
        av_mallocz(حجم(AVDOVIDecoder_Configuration_رکورد));

    إذا (اندازه)
        *اندازه = dovi ? حجم(*dovi) : 0;

    أرجع dovi;
}

تعريفنوع بنية AVDOVIMetadata_داخلی {
    AVDOVIMetadata metadata;
    AVDOVIRpu_داده_سرآیند سرآیند;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDm_داده ext_بلوکها[AV_DOVI_MAX_EXT_بلوکها];
} AVDOVIMetadata_داخلی;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *اندازه)
{
    AVDOVIMetadata_داخلی *dovi = av_mallocz(حجم(AVDOVIMetadata_داخلی));

    إذا (اندازه)
        *اندازه = dovi ? حجم(*dovi) : 0;

    إذا (!dovi)
        أرجع عدم;

    dovi->metadata = (بنية AVDOVIMetadata) {
        .سرآیند_جابه_جایی      = offsetof(AVDOVIMetadata_داخلی, سرآیند),
        .mapping_جابه_جایی     = offsetof(AVDOVIMetadata_داخلی, mapping),
        .color_جابه_جایی       = offsetof(AVDOVIMetadata_داخلی, color),
        .ext_بلوک_جابه_جایی   = offsetof(AVDOVIMetadata_داخلی, ext_بلوکها),
        .ext_بلوک_اندازه     = حجم(AVDOVIDm_داده),
    };

    أرجع &dovi->metadata;
}

AVDOVIDm_داده *av_dovi_پیدا_کن_level(ثابت AVDOVIMetadata *داده, uint8_t level)
{
    لكل (صحيح i = 0; i < داده->رقم_ext_بلوکها; i++) {
        AVDOVIDm_داده *ext = av_dovi_get_ext(داده, i);
        إذا (ext->level == level)
            أرجع ext;
    }

    أرجع عدم;
}
