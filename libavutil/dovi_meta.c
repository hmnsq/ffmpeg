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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "dovi_meta.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

AVDOVIDecoder_Configuration_ਰਿਕਾਰਡ *av_dovi_alloc(size_t *ਮਾਪ)
{
    AVDOVIDecoder_Configuration_ਰਿਕਾਰਡ *dovi =
        av_mallocz(ਆਕਾਰ(AVDOVIDecoder_Configuration_ਰਿਕਾਰਡ));

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = dovi ? ਆਕਾਰ(*dovi) : 0;

    ਵਾਪਸ dovi;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVDOVIMetadata_ਅੰਦਰੂਨੀ {
    AVDOVIMetadata metadata;
    AVDOVIRpu_ਅੰਕੜੇ_ਸਿਰਲੇਖ ਸਿਰਲੇਖ;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDm_ਅੰਕੜੇ ext_ਖੰਡਾਂ[AV_DOVI_MAX_EXT_ਖੰਡਾਂ];
} AVDOVIMetadata_ਅੰਦਰੂਨੀ;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *ਮਾਪ)
{
    AVDOVIMetadata_ਅੰਦਰੂਨੀ *dovi = av_mallocz(ਆਕਾਰ(AVDOVIMetadata_ਅੰਦਰੂਨੀ));

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = dovi ? ਆਕਾਰ(*dovi) : 0;

    ਜੇ (!dovi)
        ਵਾਪਸ ਨਿਰਾ;

    dovi->metadata = (ਬਣਤਰ AVDOVIMetadata) {
        .ਸਿਰਲੇਖ_ਵਿੱਥ      = offsetof(AVDOVIMetadata_ਅੰਦਰੂਨੀ, ਸਿਰਲੇਖ),
        .mapping_ਵਿੱਥ     = offsetof(AVDOVIMetadata_ਅੰਦਰੂਨੀ, mapping),
        .color_ਵਿੱਥ       = offsetof(AVDOVIMetadata_ਅੰਦਰੂਨੀ, color),
        .ext_ਖੰਡ_ਵਿੱਥ   = offsetof(AVDOVIMetadata_ਅੰਦਰੂਨੀ, ext_ਖੰਡਾਂ),
        .ext_ਖੰਡ_ਮਾਪ     = ਆਕਾਰ(AVDOVIDm_ਅੰਕੜੇ),
    };

    ਵਾਪਸ &dovi->metadata;
}

AVDOVIDm_ਅੰਕੜੇ *av_dovi_ਲੱਭੋ_level(ਅਚਲ AVDOVIMetadata *ਅੰਕੜੇ, uint8_t level)
{
    ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕੜੇ->ਅੰਕ_ext_ਖੰਡਾਂ; i++) {
        AVDOVIDm_ਅੰਕੜੇ *ext = av_dovi_get_ext(ਅੰਕੜੇ, i);
        ਜੇ (ext->level == level)
            ਵਾਪਸ ext;
    }

    ਵਾਪਸ ਨਿਰਾ;
}
