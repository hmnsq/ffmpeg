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

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "mastering_display_metadata.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

ਸਥਿਰ ਖਾਲੀ get_defaults(AVMasteringDisplayMetadata *mastering)
{
    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
        ਲਈ (ਪੂਰਨ j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_ਬਿੰਦੂ_2[0] =
    mastering->white_ਬਿੰਦੂ_2[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(ਖਾਲੀ)
{
    ਵਾਪਸ av_mastering_display_metadata_alloc_ਮਾਪ(ਨਿਰਾ);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_ਮਾਪ(size_t *ਮਾਪ)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(ਆਕਾਰ(AVMasteringDisplayMetadata));

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = mastering ? ਆਕਾਰ(*mastering) : 0;

    ਜੇ (!mastering)
        ਵਾਪਸ ਨਿਰਾ;

    get_defaults(mastering);

    ਵਾਪਸ mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ)
{
    AVFrame_Side_ਅੰਕੜੇ *side_ਅੰਕੜੇ = av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ(ਚੌਖਟਾ,
                                                        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_MASTERING_DISPLAY_METADATA,
                                                        ਆਕਾਰ(AVMasteringDisplayMetadata));
    ਜੇ (!side_ਅੰਕੜੇ)
        ਵਾਪਸ ਨਿਰਾ;

    memset(side_ਅੰਕੜੇ->ਅੰਕੜੇ, 0, ਆਕਾਰ(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_ਅੰਕੜੇ->ਅੰਕੜੇ);

    ਵਾਪਸ (AVMasteringDisplayMetadata *)side_ਅੰਕੜੇ->ਅੰਕੜੇ;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *ਮਾਪ)
{
    AVContentLightMetadata *metadata = av_mallocz(ਆਕਾਰ(AVContentLightMetadata));

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = metadata ? ਆਕਾਰ(*metadata) : 0;

    ਵਾਪਸ metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ)
{
    AVFrame_Side_ਅੰਕੜੇ *side_ਅੰਕੜੇ = av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ(ਚੌਖਟਾ,
                                                        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_CONTENT_LIGHT_LEVEL,
                                                        ਆਕਾਰ(AVContentLightMetadata));
    ਜੇ (!side_ਅੰਕੜੇ)
        ਵਾਪਸ ਨਿਰਾ;

    memset(side_ਅੰਕੜੇ->ਅੰਕੜੇ, 0, ਆਕਾਰ(AVContentLightMetadata));

    ਵਾਪਸ (AVContentLightMetadata *)side_ਅੰਕੜੇ->ਅੰਕੜੇ;
}
