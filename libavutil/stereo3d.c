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

#ضمن <string.h>

#ضمن "frame.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "stereo3d.h"

ساكن فراغ get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_field_of_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(فراغ)
{
    أرجع av_stereo3d_alloc_size(عدم);
}

AVStereo3D *av_stereo3d_alloc_size(size_t *size)
{
    AVStereo3D *stereo = av_mallocz(حجم(AVStereo3D));

    إذا (size)
        *size = stereo ? حجم(*stereo) : 0;

    إذا (!stereo)
        أرجع عدم;

    get_defaults(stereo);

    أرجع stereo;
}

AVStereo3D *av_stereo3d_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_STEREO3D,
                                                        حجم(AVStereo3D));
    إذا (!side_data)
        أرجع عدم;

    memset(side_data->data, 0, حجم(AVStereo3D));
    get_defaults((AVStereo3D *)side_data->data);

    أرجع (AVStereo3D *)side_data->data;
}

ساكن ثابت حرف * ثابت stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_أسطر]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

ساكن ثابت حرف * ثابت stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_يسار]   = "left",
    [AV_STEREO3_D_VIEW_يمين]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

ساكن ثابت حرف * ثابت stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_يسار]  = "left",
    [AV_PRIMARY_EYE_يمين] = "right",
};

ثابت حرف *av_stereo3d_type_name(unsigned صحيح type)
{
    إذا (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        أرجع "unknown";

    أرجع stereo3d_type_names[type];
}

صحيح av_stereo3d_from_name(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        إذا (!strcmp(name, stereo3d_type_names[i]))
            أرجع i;
    }

    أرجع -1;
}

ثابت حرف *av_stereo3d_view_name(unsigned صحيح view)
{
    إذا (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        أرجع "unknown";

    أرجع stereo3d_view_names[view];
}

صحيح av_stereo3d_view_from_name(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        إذا (!strcmp(name, stereo3d_view_names[i]))
            أرجع i;
    }

    أرجع -1;
}

ثابت حرف *av_stereo3d_primary_eye_name(unsigned صحيح eye)
{
    إذا (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        أرجع "unknown";

    أرجع stereo3d_primary_eye_names[eye];
}

صحيح av_stereo3d_primary_eye_from_name(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        إذا (!strcmp(name, stereo3d_primary_eye_names[i]))
            أرجع i;
    }

    أرجع -1;
}
