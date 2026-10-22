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
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 3; i++)
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_point[0] =
    mastering->white_point[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ av_mastering_display_metadata_alloc_size(ರಿಕ್ತ);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_size(size_t *size)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(ಪರಿಮಾಣ(AVMasteringDisplayMetadata));

    ಯದಿ (size)
        *size = mastering ? ಪರಿಮಾಣ(*mastering) : 0;

    ಯದಿ (!mastering)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    get_defaults(mastering);

    ಪ್ರತ್ಯಾಗಮ mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_MASTERING_DISPLAY_METADATA,
                                                        ಪರಿಮಾಣ(AVMasteringDisplayMetadata));
    ಯದಿ (!side_data)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    memset(side_data->data, 0, ಪರಿಮಾಣ(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_data->data);

    ಪ್ರತ್ಯಾಗಮ (AVMasteringDisplayMetadata *)side_data->data;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *size)
{
    AVContentLightMetadata *metadata = av_mallocz(ಪರಿಮಾಣ(AVContentLightMetadata));

    ಯದಿ (size)
        *size = metadata ? ಪರಿಮಾಣ(*metadata) : 0;

    ಪ್ರತ್ಯಾಗಮ metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                                                        ಪರಿಮಾಣ(AVContentLightMetadata));
    ಯದಿ (!side_data)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    memset(side_data->data, 0, ಪರಿಮಾಣ(AVContentLightMetadata));

    ಪ್ರತ್ಯಾಗಮ (AVContentLightMetadata *)side_data->data;
}
