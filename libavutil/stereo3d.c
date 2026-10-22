/*
 * Copyright (c) 2013 Vittorio Giovara <vittorio.giovara@gmail.com>
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

#include <string.h>

#include "frame.h"
#include "macros.h"
#include "mem.h"
#include "stereo3d.h"

static void get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_field_of_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(void)
{
    반환 av_stereo3d_alloc_size(NULL);
}

AVStereo3D *av_stereo3d_alloc_size(size_t *size)
{
    AVStereo3D *stereo = av_mallocz(sizeof(AVStereo3D));

    만약 (size)
        *size = stereo ? sizeof(*stereo) : 0;

    만약 (!stereo)
        반환 NULL;

    get_defaults(stereo);

    반환 stereo;
}

AVStereo3D *av_stereo3d_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_STEREO3D,
                                                        sizeof(AVStereo3D));
    만약 (!side_data)
        반환 NULL;

    memset(side_data->data, 0, sizeof(AVStereo3D));
    get_defaults((AVStereo3D *)side_data->data);

    반환 (AVStereo3D *)side_data->data;
}

static const char * const stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3D_LINES]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

static const char * const stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3D_VIEW_LEFT]   = "left",
    [AV_STEREO3D_VIEW_RIGHT]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

static const char * const stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_LEFT]  = "left",
    [AV_PRIMARY_EYE_RIGHT] = "right",
};

const char *av_stereo3d_type_name(unsigned 정수 type)
{
    만약 (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        반환 "unknown";

    반환 stereo3d_type_names[type];
}

정수 av_stereo3d_from_name(const char *name)
{
    정수 i;

    위해 (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        만약 (!strcmp(name, stereo3d_type_names[i]))
            반환 i;
    }

    반환 -1;
}

const char *av_stereo3d_view_name(unsigned 정수 view)
{
    만약 (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        반환 "unknown";

    반환 stereo3d_view_names[view];
}

정수 av_stereo3d_view_from_name(const char *name)
{
    정수 i;

    위해 (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        만약 (!strcmp(name, stereo3d_view_names[i]))
            반환 i;
    }

    반환 -1;
}

const char *av_stereo3d_primary_eye_name(unsigned 정수 eye)
{
    만약 (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        반환 "unknown";

    반환 stereo3d_primary_eye_names[eye];
}

정수 av_stereo3d_primary_eye_from_name(const char *name)
{
    정수 i;

    위해 (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        만약 (!strcmp(name, stereo3d_primary_eye_names[i]))
            반환 i;
    }

    반환 -1;
}
