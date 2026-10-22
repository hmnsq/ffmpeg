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

#অন্তর্ভাৱ <string.h>

#অন্তর্ভাৱ "dovi_meta.h"
#অন্তর্ভাৱ "mem.h"

AVDOVIDecoderConfigurationRecord *av_dovi_alloc(size_t *size)
{
    AVDOVIDecoderConfigurationRecord *dovi =
        av_mallocz(পরিমাণ(AVDOVIDecoderConfigurationRecord));

    যদি (size)
        *size = dovi ? পরিমাণ(*dovi) : 0;

    ঘূৰাই dovi;
}

প্রকারনির্দেশ সংরচনা AVDOVIMetadataInternal {
    AVDOVIMetadata metadata;
    AVDOVIRpuDataHeader header;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDmData ext_blocks[AV_DOVI_MAX_EXT_BLOCKS];
} AVDOVIMetadataInternal;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *size)
{
    AVDOVIMetadataInternal *dovi = av_mallocz(পরিমাণ(AVDOVIMetadataInternal));

    যদি (size)
        *size = dovi ? পরিমাণ(*dovi) : 0;

    যদি (!dovi)
        ঘূৰাই রিক্ত;

    dovi->metadata = (সংরচনা AVDOVIMetadata) {
        .header_offset      = offsetof(AVDOVIMetadataInternal, header),
        .mapping_offset     = offsetof(AVDOVIMetadataInternal, mapping),
        .color_offset       = offsetof(AVDOVIMetadataInternal, color),
        .ext_block_offset   = offsetof(AVDOVIMetadataInternal, ext_blocks),
        .ext_block_size     = পরিমাণ(AVDOVIDmData),
    };

    ঘূৰাই &dovi->metadata;
}

AVDOVIDmData *av_dovi_find_level(ধ্রুৱ AVDOVIMetadata *data, uint8_t level)
{
    বাবে (পূর্ণাঙ্ক i = 0; i < data->অঙ্ক_ext_blocks; i++) {
        AVDOVIDmData *ext = av_dovi_get_ext(data, i);
        যদি (ext->level == level)
            ঘূৰাই ext;
    }

    ঘূৰাই রিক্ত;
}
