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

#ضمن <stddef.h>
#ضمن <stdint.h>
#ضمن <string.h>

#ضمن "mastering_display_metadata.h"
#ضمن "mem.h"

ساكن فراغ get_defaults(AVMasteringDisplayMetadata *mastering)
{
    עבור (صحيح i = 0; i < 3; i++)
        עבור (صحيح j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_point[0] =
    mastering->white_point[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(فراغ)
{
    החזר av_mastering_display_metadata_alloc_size(عدم);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_size(size_t *size)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(حجم(AVMasteringDisplayMetadata));

    אם (size)
        *size = mastering ? حجم(*mastering) : 0;

    אם (!mastering)
        החזר عدم;

    get_defaults(mastering);

    החזר mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_MASTERING_DISPLAY_METADATA,
                                                        حجم(AVMasteringDisplayMetadata));
    אם (!side_data)
        החזר عدم;

    memset(side_data->data, 0, حجم(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_data->data);

    החזר (AVMasteringDisplayMetadata *)side_data->data;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *size)
{
    AVContentLightMetadata *metadata = av_mallocz(حجم(AVContentLightMetadata));

    אם (size)
        *size = metadata ? حجم(*metadata) : 0;

    החזר metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                                                        حجم(AVContentLightMetadata));
    אם (!side_data)
        החזר عدم;

    memset(side_data->data, 0, حجم(AVContentLightMetadata));

    החזר (AVContentLightMetadata *)side_data->data;
}
