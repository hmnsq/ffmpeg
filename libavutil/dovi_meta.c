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

#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "dovi_meta.h"
#અન્તર્ભાવ "mem.h"

AVDOVIDecoderConfigurationRecord *av_dovi_alloc(size_t *size)
{
    AVDOVIDecoderConfigurationRecord *dovi =
        av_mallocz(કદ(AVDOVIDecoderConfigurationRecord));

    જો (size)
        *size = dovi ? કદ(*dovi) : 0;

    પાછા dovi;
}

પ્રકારવ્યાખ્યા સંરચના AVDOVIMetadataInternal {
    AVDOVIMetadata metadata;
    AVDOVIRpuDataHeader header;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDmData ext_blocks[AV_DOVI_MAX_EXT_BLOCKS];
} AVDOVIMetadataInternal;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *size)
{
    AVDOVIMetadataInternal *dovi = av_mallocz(કદ(AVDOVIMetadataInternal));

    જો (size)
        *size = dovi ? કદ(*dovi) : 0;

    જો (!dovi)
        પાછા ખાલી;

    dovi->metadata = (સંરચના AVDOVIMetadata) {
        .header_offset      = offsetof(AVDOVIMetadataInternal, header),
        .mapping_offset     = offsetof(AVDOVIMetadataInternal, mapping),
        .color_offset       = offsetof(AVDOVIMetadataInternal, color),
        .ext_block_offset   = offsetof(AVDOVIMetadataInternal, ext_blocks),
        .ext_block_size     = કદ(AVDOVIDmData),
    };

    પાછા &dovi->metadata;
}

AVDOVIDmData *av_dovi_find_level(અચલ AVDOVIMetadata *data, uint8_t level)
{
    માટે (પૂર્ણાંક i = 0; i < data->અંક_ext_blocks; i++) {
        AVDOVIDmData *ext = av_dovi_get_ext(data, i);
        જો (ext->level == level)
            પાછા ext;
    }

    પાછા ખાલી;
}
