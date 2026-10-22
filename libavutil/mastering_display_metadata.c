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

#समावेश <stddef.h>
#समावेश <stdint.h>
#समावेश <string.h>

#समावेश "mastering_display_metadata.h"
#समावेश "mem.h"

अटल व्योम get_defaults(AVMasteringDisplayMetadata *mastering)
{
    क्रम (पूर्णांक i = 0; i < 3; i++)
        क्रम (पूर्णांक j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_point[0] =
    mastering->white_point[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(व्योम)
{
    वापस av_mastering_display_metadata_alloc_आकार(शून्य);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_आकार(माप_प्रकार *आकार)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(माप(AVMasteringDisplayMetadata));

    अगर (आकार)
        *आकार = mastering ? माप(*mastering) : 0;

    अगर (!mastering)
        वापस शून्य;

    get_defaults(mastering);

    वापस mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_तथ्य(AVFrame *frame)
{
    AVFrame_Side_तथ्य *side_तथ्य = av_frame_new_side_तथ्य(frame,
                                                        AV_FRAME_तथ्य_MASTERING_DISPLAY_METADATA,
                                                        माप(AVMasteringDisplayMetadata));
    अगर (!side_तथ्य)
        वापस शून्य;

    स_रखो(side_तथ्य->तथ्य, 0, माप(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_तथ्य->तथ्य);

    वापस (AVMasteringDisplayMetadata *)side_तथ्य->तथ्य;
}

AVContentLightMetadata *av_content_light_metadata_alloc(माप_प्रकार *आकार)
{
    AVContentLightMetadata *metadata = av_mallocz(माप(AVContentLightMetadata));

    अगर (आकार)
        *आकार = metadata ? माप(*metadata) : 0;

    वापस metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_तथ्य(AVFrame *frame)
{
    AVFrame_Side_तथ्य *side_तथ्य = av_frame_new_side_तथ्य(frame,
                                                        AV_FRAME_तथ्य_CONTENT_LIGHT_LEVEL,
                                                        माप(AVContentLightMetadata));
    अगर (!side_तथ्य)
        वापस शून्य;

    स_रखो(side_तथ्य->तथ्य, 0, माप(AVContentLightMetadata));

    वापस (AVContentLightMetadata *)side_तथ्य->तथ्य;
}
