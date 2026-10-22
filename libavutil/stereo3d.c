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

#அந்தர்பாவ <string.h>

#அந்தர்பாவ "frame.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "stereo3d.h"

நிலையான வெறுமை get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_field_of_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(வெறுமை)
{
    திரும்பு av_stereo3d_alloc_size(வெற்று);
}

AVStereo3D *av_stereo3d_alloc_size(size_t *size)
{
    AVStereo3D *stereo = av_mallocz(அளவு(AVStereo3D));

    எனில் (size)
        *size = stereo ? அளவு(*stereo) : 0;

    எனில் (!stereo)
        திரும்பு வெற்று;

    get_defaults(stereo);

    திரும்பு stereo;
}

AVStereo3D *av_stereo3d_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_STEREO3D,
                                                        அளவு(AVStereo3D));
    எனில் (!side_data)
        திரும்பு வெற்று;

    memset(side_data->data, 0, அளவு(AVStereo3D));
    get_defaults((AVStereo3D *)side_data->data);

    திரும்பு (AVStereo3D *)side_data->data;
}

நிலையான மாறிலி எழுத்து * மாறிலி stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_வரிகள்]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

நிலையான மாறிலி எழுத்து * மாறிலி stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_இடது]   = "left",
    [AV_STEREO3_D_VIEW_வலது]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

நிலையான மாறிலி எழுத்து * மாறிலி stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_இடது]  = "left",
    [AV_PRIMARY_EYE_வலது] = "right",
};

மாறிலி எழுத்து *av_stereo3d_type_name(unsigned முழு type)
{
    எனில் (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        திரும்பு "unknown";

    திரும்பு stereo3d_type_names[type];
}

முழு av_stereo3d_from_name(மாறிலி எழுத்து *name)
{
    முழு i;

    க்கு (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        எனில் (!strcmp(name, stereo3d_type_names[i]))
            திரும்பு i;
    }

    திரும்பு -1;
}

மாறிலி எழுத்து *av_stereo3d_view_name(unsigned முழு view)
{
    எனில் (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        திரும்பு "unknown";

    திரும்பு stereo3d_view_names[view];
}

முழு av_stereo3d_view_from_name(மாறிலி எழுத்து *name)
{
    முழு i;

    க்கு (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        எனில் (!strcmp(name, stereo3d_view_names[i]))
            திரும்பு i;
    }

    திரும்பு -1;
}

மாறிலி எழுத்து *av_stereo3d_primary_eye_name(unsigned முழு eye)
{
    எனில் (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        திரும்பு "unknown";

    திரும்பு stereo3d_primary_eye_names[eye];
}

முழு av_stereo3d_primary_eye_from_name(மாறிலி எழுத்து *name)
{
    முழு i;

    க்கு (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        எனில் (!strcmp(name, stereo3d_primary_eye_names[i]))
            திரும்பு i;
    }

    திரும்பு -1;
}
