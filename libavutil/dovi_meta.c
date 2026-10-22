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

#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "dovi_meta.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

AVDOVIDecoder_Configuration_ದಾಖಲೆ *av_dovi_alloc(size_t *ಗಾತ್ರ_2)
{
    AVDOVIDecoder_Configuration_ದಾಖಲೆ *dovi =
        av_mallocz(ಗಾತ್ರ(AVDOVIDecoder_Configuration_ದಾಖಲೆ));

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = dovi ? ಗಾತ್ರ(*dovi) : 0;

    ಹಿಂತಿರುಗಿ dovi;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDOVIMetadata_ಆಂತರಿಕ {
    AVDOVIMetadata metadata;
    AVDOVIRpu_ದತ್ತಾಂಶ_ಶೀರ್ಷಿಕೆ ಶೀರ್ಷಿಕೆ;
    AVDOVIDataMapping mapping;
    AVDOVIColorMetadata color;
    AVDOVIDm_ದತ್ತಾಂಶ ext_ಖಂಡಗಳು[AV_DOVI_MAX_EXT_ಖಂಡಗಳು];
} AVDOVIMetadata_ಆಂತರಿಕ;

AVDOVIMetadata *av_dovi_metadata_alloc(size_t *ಗಾತ್ರ_2)
{
    AVDOVIMetadata_ಆಂತರಿಕ *dovi = av_mallocz(ಗಾತ್ರ(AVDOVIMetadata_ಆಂತರಿಕ));

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = dovi ? ಗಾತ್ರ(*dovi) : 0;

    ಆದರೆ (!dovi)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    dovi->metadata = (ರಚನೆ AVDOVIMetadata) {
        .ಶೀರ್ಷಿಕೆ_ಸ್ಥಾನಾಂತರ      = offsetof(AVDOVIMetadata_ಆಂತರಿಕ, ಶೀರ್ಷಿಕೆ),
        .mapping_ಸ್ಥಾನಾಂತರ     = offsetof(AVDOVIMetadata_ಆಂತರಿಕ, mapping),
        .color_ಸ್ಥಾನಾಂತರ       = offsetof(AVDOVIMetadata_ಆಂತರಿಕ, color),
        .ext_ಖಂಡ_ಸ್ಥಾನಾಂತರ   = offsetof(AVDOVIMetadata_ಆಂತರಿಕ, ext_ಖಂಡಗಳು),
        .ext_ಖಂಡ_ಗಾತ್ರ     = ಗಾತ್ರ(AVDOVIDm_ದತ್ತಾಂಶ),
    };

    ಹಿಂತಿರುಗಿ &dovi->metadata;
}

AVDOVIDm_ದತ್ತಾಂಶ *av_dovi_ಕಂಡುಹಿಡಿ_level(ಸ್ಥಿರಾಂಕ AVDOVIMetadata *ದತ್ತಾಂಶ, uint8_t level)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ದತ್ತಾಂಶ->ಅಂಕೆ_ext_ಖಂಡಗಳು; i++) {
        AVDOVIDm_ದತ್ತಾಂಶ *ext = av_dovi_get_ext(ದತ್ತಾಂಶ, i);
        ಆದರೆ (ext->level == level)
            ಹಿಂತಿರುಗಿ ext;
    }

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}
