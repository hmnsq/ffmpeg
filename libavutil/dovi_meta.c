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

#अन्तर्भाव <string.h>

#अन्तर्भाव "dovi_meta.h"
#अन्तर्भाव "mem.h"

AVDOVIDecoderConfigurationRecord *av_dovi_alloc(size_t *size)
{
    AVDOVIDecoderConfigurationRecord *dovi =
        av_mallocz(परिमाण(AVDOVIDecoderConfigurationRecord));

    सचे (size)
        *size = dovi ? परिमाण(*dovi) : 0;

    पटिनिवत्त dovi;
}

प्रकारनिर्देश संरचना AVDOVIMetadataInternal {
    AVDOVIMetadata metadata;
    AVDOVIRpuDataHeader header;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDmData ext_blocks[AV_DOVI_MAX_EXT_BLOCKS];
} AVDOVIMetadataInternal;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *size)
{
    AVDOVIMetadataInternal *dovi = av_mallocz(परिमाण(AVDOVIMetadataInternal));

    सचे (size)
        *size = dovi ? परिमाण(*dovi) : 0;

    सचे (!dovi)
        पटिनिवत्त रिक्त;

    dovi->metadata = (संरचना AVDOVIMetadata) {
        .header_offset      = offsetof(AVDOVIMetadataInternal, header),
        .mapping_offset     = offsetof(AVDOVIMetadataInternal, mapping),
        .color_offset       = offsetof(AVDOVIMetadataInternal, color),
        .ext_block_offset   = offsetof(AVDOVIMetadataInternal, ext_blocks),
        .ext_block_size     = परिमाण(AVDOVIDmData),
    };

    पटिनिवत्त &dovi->metadata;
}

AVDOVIDmData *av_dovi_find_level(ध्रुव AVDOVIMetadata *data, uint8_t level)
{
    अत्थाय (पूर्णाङ्क i = 0; i < data->अङ्कः_ext_blocks; i++) {
        AVDOVIDmData *ext = av_dovi_get_ext(data, i);
        सचे (ext->level == level)
            पटिनिवत्त ext;
    }

    पटिनिवत्त रिक्त;
}
