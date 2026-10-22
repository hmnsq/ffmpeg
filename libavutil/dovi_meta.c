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

#అన్తర్భావ <string.h>

#అన్తర్భావ "dovi_meta.h"
#అన్తర్భావ "mem.h"

AVDOVIDecoder_Configuration_రికార్డు *av_dovi_alloc(size_t *కొలత)
{
    AVDOVIDecoder_Configuration_రికార్డు *dovi =
        av_mallocz(పరిమాణం(AVDOVIDecoder_Configuration_రికార్డు));

    ఒకవేళ (కొలత)
        *కొలత = dovi ? పరిమాణం(*dovi) : 0;

    తిరిగి dovi;
}

రకనిర్వచనం నిర్మాణం AVDOVIMetadata_అంతర్గత {
    AVDOVIMetadata metadata;
    AVDOVIRpu_దత్తాంశం_శీర్షిక శీర్షిక;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDm_దత్తాంశం ext_ఖండాలు[AV_DOVI_MAX_EXT_ఖండాలు];
} AVDOVIMetadata_అంతర్గత;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *కొలత)
{
    AVDOVIMetadata_అంతర్గత *dovi = av_mallocz(పరిమాణం(AVDOVIMetadata_అంతర్గత));

    ఒకవేళ (కొలత)
        *కొలత = dovi ? పరిమాణం(*dovi) : 0;

    ఒకవేళ (!dovi)
        తిరిగి ఖాళీ;

    dovi->metadata = (నిర్మాణం AVDOVIMetadata) {
        .శీర్షిక_స్థానభ్రంశం      = offsetof(AVDOVIMetadata_అంతర్గత, శీర్షిక),
        .mapping_స్థానభ్రంశం     = offsetof(AVDOVIMetadata_అంతర్గత, mapping),
        .color_స్థానభ్రంశం       = offsetof(AVDOVIMetadata_అంతర్గత, color),
        .ext_ఖండం_స్థానభ్రంశం   = offsetof(AVDOVIMetadata_అంతర్గత, ext_ఖండాలు),
        .ext_ఖండం_కొలత     = పరిమాణం(AVDOVIDm_దత్తాంశం),
    };

    తిరిగి &dovi->metadata;
}

AVDOVIDm_దత్తాంశం *av_dovi_కనుగొను_level(స్థిరరాశి AVDOVIMetadata *దత్తాంశం, uint8_t level)
{
    కొరకు (పూర్ణాంకం i = 0; i < దత్తాంశం->అంకె_ext_ఖండాలు; i++) {
        AVDOVIDm_దత్తాంశం *ext = av_dovi_get_ext(దత్తాంశం, i);
        ఒకవేళ (ext->level == level)
            తిరిగి ext;
    }

    తిరిగి ఖాళీ;
}
