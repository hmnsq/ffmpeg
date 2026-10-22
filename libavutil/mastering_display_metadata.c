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

#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "mastering_display_metadata.h"
#அந்தர்பாவ "mem.h"

நிலையான வெறுமை get_defaults(AVMasteringDisplayMetadata *mastering)
{
    க்கு (முழு i = 0; i < 3; i++)
        க்கு (முழு j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_point[0] =
    mastering->white_point[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(வெறுமை)
{
    திரும்பு av_mastering_display_metadata_alloc_size(வெற்று);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_size(size_t *size)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(அளவு(AVMasteringDisplayMetadata));

    எனில் (size)
        *size = mastering ? அளவு(*mastering) : 0;

    எனில் (!mastering)
        திரும்பு வெற்று;

    get_defaults(mastering);

    திரும்பு mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_MASTERING_DISPLAY_METADATA,
                                                        அளவு(AVMasteringDisplayMetadata));
    எனில் (!side_data)
        திரும்பு வெற்று;

    memset(side_data->data, 0, அளவு(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_data->data);

    திரும்பு (AVMasteringDisplayMetadata *)side_data->data;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *size)
{
    AVContentLightMetadata *metadata = av_mallocz(அளவு(AVContentLightMetadata));

    எனில் (size)
        *size = metadata ? அளவு(*metadata) : 0;

    திரும்பு metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                                                        அளவு(AVContentLightMetadata));
    எனில் (!side_data)
        திரும்பு வெற்று;

    memset(side_data->data, 0, அளவு(AVContentLightMetadata));

    திரும்பு (AVContentLightMetadata *)side_data->data;
}
