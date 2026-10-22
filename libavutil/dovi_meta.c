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

AVDOVIDecoder_Configuration_رڪارڊ *av_dovi_alloc(size_t *سائيز)
{
    AVDOVIDecoder_Configuration_رڪارڊ *dovi =
        av_mallocz(حجم(AVDOVIDecoder_Configuration_رڪارڊ));

    إذا (سائيز)
        *سائيز = dovi ? حجم(*dovi) : 0;

    أرجع dovi;
}

تعريفنوع بنية AVDOVIMetadata_اندروني {
    AVDOVIMetadata metadata;
    AVDOVIRpu_معلومات_سرو سرو;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDm_معلومات ext_بلاڪون[AV_DOVI_MAX_EXT_بلاڪون];
} AVDOVIMetadata_اندروني;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *سائيز)
{
    AVDOVIMetadata_اندروني *dovi = av_mallocz(حجم(AVDOVIMetadata_اندروني));

    إذا (سائيز)
        *سائيز = dovi ? حجم(*dovi) : 0;

    إذا (!dovi)
        أرجع عدم;

    dovi->metadata = (بنية AVDOVIMetadata) {
        .سرو_وٿي      = offsetof(AVDOVIMetadata_اندروني, سرو),
        .mapping_وٿي     = offsetof(AVDOVIMetadata_اندروني, mapping),
        .color_وٿي       = offsetof(AVDOVIMetadata_اندروني, color),
        .ext_بلاڪ_وٿي   = offsetof(AVDOVIMetadata_اندروني, ext_بلاڪون),
        .ext_بلاڪ_سائيز     = حجم(AVDOVIDm_معلومات),
    };

    أرجع &dovi->metadata;
}

AVDOVIDm_معلومات *av_dovi_ڳوليو_level(ثابت AVDOVIMetadata *معلومات, uint8_t level)
{
    لكل (صحيح i = 0; i < معلومات->انگ_ext_بلاڪون; i++) {
        AVDOVIDm_معلومات *ext = av_dovi_get_ext(معلومات, i);
        إذا (ext->level == level)
            أرجع ext;
    }

    أرجع عدم;
}
