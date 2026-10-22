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

#অন্তর্ভাব <string.h>

#অন্তর্ভাব "dovi_meta.h"
#অন্তর্ভাব "mem.h"

AVDOVIDecoderConfigurationRecord *av_dovi_alloc(size_t *আকার_2)
{
    AVDOVIDecoderConfigurationRecord *dovi =
        av_mallocz(আকার(AVDOVIDecoderConfigurationRecord));

    যদি (আকার_2)
        *আকার_2 = dovi ? আকার(*dovi) : 0;

    ফেরত dovi;
}

প্রকারলেখ কাঠামো AVDOVIMetadataInternal {
    AVDOVIMetadata metadata;
    AVDOVIRpu_তথ্য_Header header;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDm_তথ্য ext_blocks[AV_DOVI_MAX_EXT_BLOCKS];
} AVDOVIMetadataInternal;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *আকার_2)
{
    AVDOVIMetadataInternal *dovi = av_mallocz(আকার(AVDOVIMetadataInternal));

    যদি (আকার_2)
        *আকার_2 = dovi ? আকার(*dovi) : 0;

    যদি (!dovi)
        ফেরত ফাঁকা;

    dovi->metadata = (কাঠামো AVDOVIMetadata) {
        .header_offset      = offsetof(AVDOVIMetadataInternal, header),
        .mapping_offset     = offsetof(AVDOVIMetadataInternal, mapping),
        .color_offset       = offsetof(AVDOVIMetadataInternal, color),
        .ext_block_offset   = offsetof(AVDOVIMetadataInternal, ext_blocks),
        .ext_block_আকার     = আকার(AVDOVIDm_তথ্য),
    };

    ফেরত &dovi->metadata;
}

AVDOVIDm_তথ্য *av_dovi_find_level(ধ্রুবক AVDOVIMetadata *তথ্য, uint8_t level)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < তথ্য->অঙ্ক_ext_blocks; i++) {
        AVDOVIDm_তথ্য *ext = av_dovi_get_ext(তথ্য, i);
        যদি (ext->level == level)
            ফেরত ext;
    }

    ফেরত ফাঁকা;
}
