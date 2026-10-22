/**
 * Copyright (c) 2016 Neil Birkbeck <neil.birkbeck@gmail.com>
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

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "mastering_display_metadata.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

ಸ್ಥಿರ ಶೂನ್ಯ get_defaults(AVMasteringDisplayMetadata *mastering)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 3; i++)
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_ಬಿಂದು_2[0] =
    mastering->white_ಬಿಂದು_2[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ av_mastering_display_metadata_alloc_ಗಾತ್ರ(ಖಾಲಿ);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_ಗಾತ್ರ(size_t *ಗಾತ್ರ_2)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(ಗಾತ್ರ(AVMasteringDisplayMetadata));

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = mastering ? ಗಾತ್ರ(*mastering) : 0;

    ಆದರೆ (!mastering)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    get_defaults(mastering);

    ಹಿಂತಿರುಗಿ mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು)
{
    AVFrame_Side_ದತ್ತಾಂಶ *side_ದತ್ತಾಂಶ = av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು,
                                                        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_MASTERING_DISPLAY_METADATA,
                                                        ಗಾತ್ರ(AVMasteringDisplayMetadata));
    ಆದರೆ (!side_ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    memset(side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ, 0, ಗಾತ್ರ(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ);

    ಹಿಂತಿರುಗಿ (AVMasteringDisplayMetadata *)side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *ಗಾತ್ರ_2)
{
    AVContentLightMetadata *metadata = av_mallocz(ಗಾತ್ರ(AVContentLightMetadata));

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = metadata ? ಗಾತ್ರ(*metadata) : 0;

    ಹಿಂತಿರುಗಿ metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು)
{
    AVFrame_Side_ದತ್ತಾಂಶ *side_ದತ್ತಾಂಶ = av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು,
                                                        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_CONTENT_LIGHT_LEVEL,
                                                        ಗಾತ್ರ(AVContentLightMetadata));
    ಆದರೆ (!side_ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    memset(side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ, 0, ಗಾತ್ರ(AVContentLightMetadata));

    ಹಿಂತಿರುಗಿ (AVContentLightMetadata *)side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ;
}
