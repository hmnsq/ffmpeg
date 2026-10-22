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

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "mastering_display_metadata.h"
#include "mem.h"

static void get_defaults(AVMasteringDisplayMetadata *mastering)
{
    ꦏꦁꦒꦺꦴ (puur_naa_nka i = 0; i < 3; i++)
        ꦏꦁꦒꦺꦴ (puur_naa_nka j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_point[0] =
    mastering->white_point[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(void)
{
    ꦮꦭꦶ av_mastering_display_metadata_alloc_size(NULL);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_size(size_t *size)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(parimaa_na(AVMasteringDisplayMetadata));

    ꦪꦼꦤ꧀ (size)
        *size = mastering ? parimaa_na(*mastering) : 0;

    ꦪꦼꦤ꧀ (!mastering)
        ꦮꦭꦶ NULL;

    get_defaults(mastering);

    ꦮꦭꦶ mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_MASTERING_DISPLAY_METADATA,
                                                        parimaa_na(AVMasteringDisplayMetadata));
    ꦪꦼꦤ꧀ (!side_data)
        ꦮꦭꦶ NULL;

    memset(side_data->data, 0, parimaa_na(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_data->data);

    ꦮꦭꦶ (AVMasteringDisplayMetadata *)side_data->data;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *size)
{
    AVContentLightMetadata *metadata = av_mallocz(parimaa_na(AVContentLightMetadata));

    ꦪꦼꦤ꧀ (size)
        *size = metadata ? parimaa_na(*metadata) : 0;

    ꦮꦭꦶ metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_CONTENT_LIGHT_LEVEL,
                                                        parimaa_na(AVContentLightMetadata));
    ꦪꦼꦤ꧀ (!side_data)
        ꦮꦭꦶ NULL;

    memset(side_data->data, 0, parimaa_na(AVContentLightMetadata));

    ꦮꦭꦶ (AVContentLightMetadata *)side_data->data;
}
