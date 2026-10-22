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

#समावेश <string.h>

#समावेश "dovi_meta.h"
#समावेश "mem.h"

AVDOVIDecoderConfigurationRecord *av_dovi_alloc(माप_प्रकार *आकार)
{
    AVDOVIDecoderConfigurationRecord *dovi =
        av_mallocz(माप(AVDOVIDecoderConfigurationRecord));

    अगर (आकार)
        *आकार = dovi ? माप(*dovi) : 0;

    वापस dovi;
}

प्रकार काष्ठा AVDOVIMetadataInternal {
    AVDOVIMetadata metadata;
    AVDOVIRpu_तथ्य_Header header;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDm_तथ्य ext_blocks[AV_DOVI_MAX_EXT_BLOCKS];
} AVDOVIMetadataInternal;

AVDOVIMetadata *av_dovi_metadata_alloc(माप_प्रकार *आकार)
{
    AVDOVIMetadataInternal *dovi = av_mallocz(माप(AVDOVIMetadataInternal));

    अगर (आकार)
        *आकार = dovi ? माप(*dovi) : 0;

    अगर (!dovi)
        वापस शून्य;

    dovi->metadata = (काष्ठा AVDOVIMetadata) {
        .header_offset      = दुरत्व(AVDOVIMetadataInternal, header),
        .mapping_offset     = दुरत्व(AVDOVIMetadataInternal, mapping),
        .color_offset       = दुरत्व(AVDOVIMetadataInternal, color),
        .ext_block_offset   = दुरत्व(AVDOVIMetadataInternal, ext_blocks),
        .ext_block_आकार     = माप(AVDOVIDm_तथ्य),
    };

    वापस &dovi->metadata;
}

AVDOVIDm_तथ्य *av_dovi_find_level(स्थिर AVDOVIMetadata *तथ्य, uint8_t level)
{
    क्रम (पूर्णांक i = 0; i < तथ्य->अंक_ext_blocks; i++) {
        AVDOVIDm_तथ्य *ext = av_dovi_get_ext(तथ्य, i);
        अगर (ext->level == level)
            वापस ext;
    }

    वापस शून्य;
}
