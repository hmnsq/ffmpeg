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

AVDOVIDecoderConfigurationRecord *av_dovi_alloc(माप_प्रकार *size)
{
    AVDOVIDecoderConfigurationRecord *dovi =
        av_mallocz(परिमाण(AVDOVIDecoderConfigurationRecord));

    यदि (size)
        *size = dovi ? परिमाण(*dovi) : 0;

    प्रत्यागम dovi;
}

प्रकारनिर्देश संरचना AVDOVIMetadataInternal {
    AVDOVIMetadata metadata;
    AVDOVIRpuDataHeader header;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDmData ext_blocks[AV_DOVI_MAX_EXT_BLOCKS];
} AVDOVIMetadataInternal;

AVDOVIMetadata *av_dovi_metadata_alloc(माप_प्रकार *size)
{
    AVDOVIMetadataInternal *dovi = av_mallocz(परिमाण(AVDOVIMetadataInternal));

    यदि (size)
        *size = dovi ? परिमाण(*dovi) : 0;

    यदि (!dovi)
        प्रत्यागम रिक्त;

    dovi->metadata = (संरचना AVDOVIMetadata) {
        .header_offset      = दुरत्व(AVDOVIMetadataInternal, header),
        .mapping_offset     = दुरत्व(AVDOVIMetadataInternal, mapping),
        .color_offset       = दुरत्व(AVDOVIMetadataInternal, color),
        .ext_block_offset   = दुरत्व(AVDOVIMetadataInternal, ext_blocks),
        .ext_block_size     = परिमाण(AVDOVIDmData),
    };

    प्रत्यागम &dovi->metadata;
}

AVDOVIDmData *av_dovi_find_level(ध्रुव AVDOVIMetadata *data, uint8_t level)
{
    प्रति (पूर्णाङ्क i = 0; i < data->अंक_ext_blocks; i++) {
        AVDOVIDmData *ext = av_dovi_get_ext(data, i);
        यदि (ext->level == level)
            प्रत्यागम ext;
    }

    प्रत्यागम रिक्त;
}
