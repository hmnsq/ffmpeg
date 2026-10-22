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

#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "dovi_meta.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"

AVDOVIDecoderConfigurationRecord *av_dovi_alloc(size_t *size)
{
    AVDOVIDecoderConfigurationRecord *dovi =
        av_mallocz(ଆକାର(AVDOVIDecoderConfigurationRecord));

    ଯଦି (size)
        *size = dovi ? ଆକାର(*dovi) : 0;

    ଫେରନ୍ତୁ dovi;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AVDOVIMetadataInternal {
    AVDOVIMetadata metadata;
    AVDOVIRpuDataHeader header;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDmData ext_blocks[AV_DOVI_MAX_EXT_BLOCKS];
} AVDOVIMetadataInternal;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *size)
{
    AVDOVIMetadataInternal *dovi = av_mallocz(ଆକାର(AVDOVIMetadataInternal));

    ଯଦି (size)
        *size = dovi ? ଆକାର(*dovi) : 0;

    ଯଦି (!dovi)
        ଫେରନ୍ତୁ ଖାଲି;

    dovi->metadata = (ସଂରଚନା AVDOVIMetadata) {
        .header_offset      = offsetof(AVDOVIMetadataInternal, header),
        .mapping_offset     = offsetof(AVDOVIMetadataInternal, mapping),
        .color_offset       = offsetof(AVDOVIMetadataInternal, color),
        .ext_block_offset   = offsetof(AVDOVIMetadataInternal, ext_blocks),
        .ext_block_size     = ଆକାର(AVDOVIDmData),
    };

    ଫେରନ୍ତୁ &dovi->metadata;
}

AVDOVIDmData *av_dovi_find_level(ଅଚଳ AVDOVIMetadata *data, uint8_t level)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < data->ଅଙ୍କ_ext_blocks; i++) {
        AVDOVIDmData *ext = av_dovi_get_ext(data, i);
        ଯଦି (ext->level == level)
            ଫେରନ୍ତୁ ext;
    }

    ଫେରନ୍ତୁ ଖାଲି;
}
