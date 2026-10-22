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

#ଅନ୍ତର୍ଭାଵ <stddef.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "mastering_display_metadata.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"

ସ୍ଥିର ଶୂନ୍ୟ get_defaults(AVMasteringDisplayMetadata *mastering)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 3; i++)
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_point[0] =
    mastering->white_point[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ av_mastering_display_metadata_alloc_size(ଖାଲି);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_size(size_t *size)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(ଆକାର(AVMasteringDisplayMetadata));

    ଯଦି (size)
        *size = mastering ? ଆକାର(*mastering) : 0;

    ଯଦି (!mastering)
        ଫେରନ୍ତୁ ଖାଲି;

    get_defaults(mastering);

    ଫେରନ୍ତୁ mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_MASTERING_DISPLAY_METADATA,
                                                        ଆକାର(AVMasteringDisplayMetadata));
    ଯଦି (!side_data)
        ଫେରନ୍ତୁ ଖାଲି;

    memset(side_data->data, 0, ଆକାର(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_data->data);

    ଫେରନ୍ତୁ (AVMasteringDisplayMetadata *)side_data->data;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *size)
{
    AVContentLightMetadata *metadata = av_mallocz(ଆକାର(AVContentLightMetadata));

    ଯଦି (size)
        *size = metadata ? ଆକାର(*metadata) : 0;

    ଫେରନ୍ତୁ metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                                                        ଆକାର(AVContentLightMetadata));
    ଯଦି (!side_data)
        ଫେରନ୍ତୁ ଖାଲି;

    memset(side_data->data, 0, ଆକାର(AVContentLightMetadata));

    ଫେରନ୍ତୁ (AVContentLightMetadata *)side_data->data;
}
