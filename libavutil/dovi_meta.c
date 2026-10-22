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

AVDOVIDecoder_Configuration_लेखः *av_dovi_alloc(size_t *आकार)
{
    AVDOVIDecoder_Configuration_लेखः *dovi =
        av_mallocz(परिमाण(AVDOVIDecoder_Configuration_लेखः));

    यदि (आकार)
        *आकार = dovi ? परिमाण(*dovi) : 0;

    प्रत्यागम dovi;
}

प्रकारनिर्देश संरचना AVDOVIMetadata_आन्तरिकम् {
    AVDOVIMetadata metadata;
    AVDOVIRpu_दत्त_शीर्षकम् शीर्षकम्;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDm_दत्त ext_खण्डानि[AV_DOVI_MAX_EXT_खण्डानि];
} AVDOVIMetadata_आन्तरिकम्;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *आकार)
{
    AVDOVIMetadata_आन्तरिकम् *dovi = av_mallocz(परिमाण(AVDOVIMetadata_आन्तरिकम्));

    यदि (आकार)
        *आकार = dovi ? परिमाण(*dovi) : 0;

    यदि (!dovi)
        प्रत्यागम रिक्त;

    dovi->metadata = (संरचना AVDOVIMetadata) {
        .शीर्षकम्_विस्थापनम्      = offsetof(AVDOVIMetadata_आन्तरिकम्, शीर्षकम्),
        .mapping_विस्थापनम्     = offsetof(AVDOVIMetadata_आन्तरिकम्, mapping),
        .color_विस्थापनम्       = offsetof(AVDOVIMetadata_आन्तरिकम्, color),
        .ext_खण्डम्_विस्थापनम्   = offsetof(AVDOVIMetadata_आन्तरिकम्, ext_खण्डानि),
        .ext_खण्डम्_आकार     = परिमाण(AVDOVIDm_दत्त),
    };

    प्रत्यागम &dovi->metadata;
}

AVDOVIDm_दत्त *av_dovi_find_level(ध्रुव AVDOVIMetadata *दत्त, uint8_t level)
{
    प्रति (पूर्णाङ्क i = 0; i < दत्त->अङ्कः_ext_खण्डानि; i++) {
        AVDOVIDm_दत्त *ext = av_dovi_get_ext(दत्त, i);
        यदि (ext->level == level)
            प्रत्यागम ext;
    }

    प्रत्यागम रिक्त;
}
