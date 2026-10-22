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

#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "mastering_display_metadata.h"
#അന്തര്ഭാവ "mem.h"

സ്ഥിതം ശൂന്യം get_defaults(AVMasteringDisplayMetadata *mastering)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 3; i++)
        വേണ്ടി (പൂർണ്ണസംഖ്യ j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_point[0] =
    mastering->white_point[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(ശൂന്യം)
{
    തിരികെ av_mastering_display_metadata_alloc_size(ശൂന്യ);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_size(size_t *size)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(വലുപ്പം(AVMasteringDisplayMetadata));

    എങ്കിൽ (size)
        *size = mastering ? വലുപ്പം(*mastering) : 0;

    എങ്കിൽ (!mastering)
        തിരികെ ശൂന്യ;

    get_defaults(mastering);

    തിരികെ mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_MASTERING_DISPLAY_METADATA,
                                                        വലുപ്പം(AVMasteringDisplayMetadata));
    എങ്കിൽ (!side_data)
        തിരികെ ശൂന്യ;

    memset(side_data->data, 0, വലുപ്പം(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_data->data);

    തിരികെ (AVMasteringDisplayMetadata *)side_data->data;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *size)
{
    AVContentLightMetadata *metadata = av_mallocz(വലുപ്പം(AVContentLightMetadata));

    എങ്കിൽ (size)
        *size = metadata ? വലുപ്പം(*metadata) : 0;

    തിരികെ metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                                                        വലുപ്പം(AVContentLightMetadata));
    എങ്കിൽ (!side_data)
        തിരികെ ശൂന്യ;

    memset(side_data->data, 0, വലുപ്പം(AVContentLightMetadata));

    തിരികെ (AVContentLightMetadata *)side_data->data;
}
