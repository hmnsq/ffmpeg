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

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "mastering_display_metadata.h"
#अन्तर्भाव "mem.h"

स्थिर शून्य get_defaults(AVMasteringDisplayMetadata *mastering)
{
    साठी (पूर्णांक i = 0; i < 3; i++)
        साठी (पूर्णांक j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_point[0] =
    mastering->white_point[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(शून्य)
{
    परत av_mastering_display_metadata_alloc_size(रिक्त);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_size(माप_प्रकार *size)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(आकार(AVMasteringDisplayMetadata));

    जर (size)
        *size = mastering ? आकार(*mastering) : 0;

    जर (!mastering)
        परत रिक्त;

    get_defaults(mastering);

    परत mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_MASTERING_DISPLAY_METADATA,
                                                        आकार(AVMasteringDisplayMetadata));
    जर (!side_data)
        परत रिक्त;

    स_रखो(side_data->data, 0, आकार(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_data->data);

    परत (AVMasteringDisplayMetadata *)side_data->data;
}

AVContentLightMetadata *av_content_light_metadata_alloc(माप_प्रकार *size)
{
    AVContentLightMetadata *metadata = av_mallocz(आकार(AVContentLightMetadata));

    जर (size)
        *size = metadata ? आकार(*metadata) : 0;

    परत metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                                                        आकार(AVContentLightMetadata));
    जर (!side_data)
        परत रिक्त;

    स_रखो(side_data->data, 0, आकार(AVContentLightMetadata));

    परत (AVContentLightMetadata *)side_data->data;
}
