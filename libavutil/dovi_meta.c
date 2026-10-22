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

#شامل <string.h>

#شامل "dovi_meta.h"
#شامل "mem.h"

AVDOVIDecoder_Configuration_ریکارڈ *av_dovi_alloc(size_t *سائز)
{
    AVDOVIDecoder_Configuration_ریکارڈ *dovi =
        av_mallocz(حجم(AVDOVIDecoder_Configuration_ریکارڈ));

    اگر (سائز)
        *سائز = dovi ? حجم(*dovi) : 0;

    واپس dovi;
}

قسمتعریف ساخت AVDOVIMetadata_اندرونی {
    AVDOVIMetadata metadata;
    AVDOVIRpu_ڈیٹا_سرخی سرخی;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDm_ڈیٹا ext_بلاکیں[AV_DOVI_MAX_EXT_بلاکیں];
} AVDOVIMetadata_اندرونی;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *سائز)
{
    AVDOVIMetadata_اندرونی *dovi = av_mallocz(حجم(AVDOVIMetadata_اندرونی));

    اگر (سائز)
        *سائز = dovi ? حجم(*dovi) : 0;

    اگر (!dovi)
        واپس تہی;

    dovi->metadata = (ساخت AVDOVIMetadata) {
        .سرخی_انحراف      = offsetof(AVDOVIMetadata_اندرونی, سرخی),
        .mapping_انحراف     = offsetof(AVDOVIMetadata_اندرونی, mapping),
        .color_انحراف       = offsetof(AVDOVIMetadata_اندرونی, color),
        .ext_بلاک_انحراف   = offsetof(AVDOVIMetadata_اندرونی, ext_بلاکیں),
        .ext_بلاک_سائز     = حجم(AVDOVIDm_ڈیٹا),
    };

    واپس &dovi->metadata;
}

AVDOVIDm_ڈیٹا *av_dovi_ڈھونڈو_level(ثابت AVDOVIMetadata *ڈیٹا, uint8_t level)
{
    برائے (صحیح i = 0; i < ڈیٹا->عدد_ext_بلاکیں; i++) {
        AVDOVIDm_ڈیٹا *ext = av_dovi_get_ext(ڈیٹا, i);
        اگر (ext->level == level)
            واپس ext;
    }

    واپس تہی;
}
