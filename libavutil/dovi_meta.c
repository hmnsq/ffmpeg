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

AVDOVIDecoder_Configuration_ریکارڈ *av_dovi_alloc(size_t *ناپ)
{
    AVDOVIDecoder_Configuration_ریکارڈ *dovi =
        av_mallocz(حجم(AVDOVIDecoder_Configuration_ریکارڈ));

    إذا (ناپ)
        *ناپ = dovi ? حجم(*dovi) : 0;

    أرجع dovi;
}

تعريفنوع بنية AVDOVIMetadata_اندرونی {
    AVDOVIMetadata metadata;
    AVDOVIRpu_انکڑے_سرخی سرخی;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDm_انکڑے ext_بلاکاں[AV_DOVI_MAX_EXT_بلاکاں];
} AVDOVIMetadata_اندرونی;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *ناپ)
{
    AVDOVIMetadata_اندرونی *dovi = av_mallocz(حجم(AVDOVIMetadata_اندرونی));

    إذا (ناپ)
        *ناپ = dovi ? حجم(*dovi) : 0;

    إذا (!dovi)
        أرجع عدم;

    dovi->metadata = (بنية AVDOVIMetadata) {
        .سرخی_وتھ      = offsetof(AVDOVIMetadata_اندرونی, سرخی),
        .mapping_وتھ     = offsetof(AVDOVIMetadata_اندرونی, mapping),
        .color_وتھ       = offsetof(AVDOVIMetadata_اندرونی, color),
        .ext_بلاک_وتھ   = offsetof(AVDOVIMetadata_اندرونی, ext_بلاکاں),
        .ext_بلاک_ناپ     = حجم(AVDOVIDm_انکڑے),
    };

    أرجع &dovi->metadata;
}

AVDOVIDm_انکڑے *av_dovi_لبھو_level(ثابت AVDOVIMetadata *انکڑے, uint8_t level)
{
    لكل (صحيح i = 0; i < انکڑے->عدد_ext_بلاکاں; i++) {
        AVDOVIDm_انکڑے *ext = av_dovi_get_ext(انکڑے, i);
        إذا (ext->level == level)
            أرجع ext;
    }

    أرجع عدم;
}
