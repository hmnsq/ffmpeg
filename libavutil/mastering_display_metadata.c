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

#অন্তর্ভাৱ <stddef.h>
#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <string.h>

#অন্তর্ভাৱ "mastering_display_metadata.h"
#অন্তর্ভাৱ "mem.h"

স্থির শূন্য get_defaults(AVMasteringDisplayMetadata *mastering)
{
    বাবে (পূর্ণাঙ্ক i = 0; i < 3; i++)
        বাবে (পূর্ণাঙ্ক j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_point[0] =
    mastering->white_point[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(শূন্য)
{
    ঘূৰাই av_mastering_display_metadata_alloc_size(রিক্ত);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_size(size_t *size)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(পরিমাণ(AVMasteringDisplayMetadata));

    যদি (size)
        *size = mastering ? পরিমাণ(*mastering) : 0;

    যদি (!mastering)
        ঘূৰাই রিক্ত;

    get_defaults(mastering);

    ঘূৰাই mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_MASTERING_DISPLAY_METADATA,
                                                        পরিমাণ(AVMasteringDisplayMetadata));
    যদি (!side_data)
        ঘূৰাই রিক্ত;

    memset(side_data->data, 0, পরিমাণ(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_data->data);

    ঘূৰাই (AVMasteringDisplayMetadata *)side_data->data;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *size)
{
    AVContentLightMetadata *metadata = av_mallocz(পরিমাণ(AVContentLightMetadata));

    যদি (size)
        *size = metadata ? পরিমাণ(*metadata) : 0;

    ঘূৰাই metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                                                        পরিমাণ(AVContentLightMetadata));
    যদি (!side_data)
        ঘূৰাই রিক্ত;

    memset(side_data->data, 0, পরিমাণ(AVContentLightMetadata));

    ঘূৰাই (AVContentLightMetadata *)side_data->data;
}
