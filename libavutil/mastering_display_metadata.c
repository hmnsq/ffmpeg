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

#અન્તર્ભાવ <stddef.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "mastering_display_metadata.h"
#અન્તર્ભાવ "mem.h"

સ્થિર શૂન્ય get_defaults(AVMasteringDisplayMetadata *mastering)
{
    માટે (પૂર્ણાંક i = 0; i < 3; i++)
        માટે (પૂર્ણાંક j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_point[0] =
    mastering->white_point[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(શૂન્ય)
{
    પાછા av_mastering_display_metadata_alloc_size(ખાલી);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_size(size_t *size)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(કદ(AVMasteringDisplayMetadata));

    જો (size)
        *size = mastering ? કદ(*mastering) : 0;

    જો (!mastering)
        પાછા ખાલી;

    get_defaults(mastering);

    પાછા mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_MASTERING_DISPLAY_METADATA,
                                                        કદ(AVMasteringDisplayMetadata));
    જો (!side_data)
        પાછા ખાલી;

    memset(side_data->data, 0, કદ(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_data->data);

    પાછા (AVMasteringDisplayMetadata *)side_data->data;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *size)
{
    AVContentLightMetadata *metadata = av_mallocz(કદ(AVContentLightMetadata));

    જો (size)
        *size = metadata ? કદ(*metadata) : 0;

    પાછા metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                                                        કદ(AVContentLightMetadata));
    જો (!side_data)
        પાછા ખાલી;

    memset(side_data->data, 0, કદ(AVContentLightMetadata));

    પાછા (AVContentLightMetadata *)side_data->data;
}
