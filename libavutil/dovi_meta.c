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

#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "dovi_meta.h"
#അന്തര്ഭാവ "mem.h"

AVDOVIDecoderConfigurationRecord *av_dovi_alloc(size_t *size)
{
    AVDOVIDecoderConfigurationRecord *dovi =
        av_mallocz(വലുപ്പം(AVDOVIDecoderConfigurationRecord));

    എങ്കിൽ (size)
        *size = dovi ? വലുപ്പം(*dovi) : 0;

    തിരികെ dovi;
}

തരനിർവചനം ഘടന AVDOVIMetadataInternal {
    AVDOVIMetadata metadata;
    AVDOVIRpuDataHeader header;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDmData ext_blocks[AV_DOVI_MAX_EXT_BLOCKS];
} AVDOVIMetadataInternal;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *size)
{
    AVDOVIMetadataInternal *dovi = av_mallocz(വലുപ്പം(AVDOVIMetadataInternal));

    എങ്കിൽ (size)
        *size = dovi ? വലുപ്പം(*dovi) : 0;

    എങ്കിൽ (!dovi)
        തിരികെ ശൂന്യ;

    dovi->metadata = (ഘടന AVDOVIMetadata) {
        .header_offset      = offsetof(AVDOVIMetadataInternal, header),
        .mapping_offset     = offsetof(AVDOVIMetadataInternal, mapping),
        .color_offset       = offsetof(AVDOVIMetadataInternal, color),
        .ext_block_offset   = offsetof(AVDOVIMetadataInternal, ext_blocks),
        .ext_block_size     = വലുപ്പം(AVDOVIDmData),
    };

    തിരികെ &dovi->metadata;
}

AVDOVIDmData *av_dovi_find_level(സ്ഥിരം AVDOVIMetadata *data, uint8_t level)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < data->അക്കം_ext_blocks; i++) {
        AVDOVIDmData *ext = av_dovi_get_ext(data, i);
        എങ്കിൽ (ext->level == level)
            തിരികെ ext;
    }

    തിരികെ ശൂന്യ;
}
