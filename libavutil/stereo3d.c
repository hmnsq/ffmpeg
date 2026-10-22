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

#شامل <string.h>

#شامل "frame.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "stereo3d.h"

ایستا تهی get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_field_of_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(تهی)
{
    بازگشت av_stereo3d_alloc_size(پوچ);
}

AVStereo3D *av_stereo3d_alloc_size(size_t *size)
{
    AVStereo3D *stereo = av_mallocz(اندازه(AVStereo3D));

    اگر (size)
        *size = stereo ? اندازه(*stereo) : 0;

    اگر (!stereo)
        بازگشت پوچ;

    get_defaults(stereo);

    بازگشت stereo;
}

AVStereo3D *av_stereo3d_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_STEREO3D,
                                                        اندازه(AVStereo3D));
    اگر (!side_data)
        بازگشت پوچ;

    memset(side_data->data, 0, اندازه(AVStereo3D));
    get_defaults((AVStereo3D *)side_data->data);

    بازگشت (AVStereo3D *)side_data->data;
}

ایستا ثابت نویسه * ثابت stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_سطرها]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

ایستا ثابت نویسه * ثابت stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_چپ]   = "left",
    [AV_STEREO3_D_VIEW_راست]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

ایستا ثابت نویسه * ثابت stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_چپ]  = "left",
    [AV_PRIMARY_EYE_راست] = "right",
};

ثابت نویسه *av_stereo3d_type_name(unsigned صحیح type)
{
    اگر (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        بازگشت "unknown";

    بازگشت stereo3d_type_names[type];
}

صحیح av_stereo3d_from_name(ثابت نویسه *name)
{
    صحیح i;

    برای (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        اگر (!strcmp(name, stereo3d_type_names[i]))
            بازگشت i;
    }

    بازگشت -1;
}

ثابت نویسه *av_stereo3d_view_name(unsigned صحیح view)
{
    اگر (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        بازگشت "unknown";

    بازگشت stereo3d_view_names[view];
}

صحیح av_stereo3d_view_from_name(ثابت نویسه *name)
{
    صحیح i;

    برای (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        اگر (!strcmp(name, stereo3d_view_names[i]))
            بازگشت i;
    }

    بازگشت -1;
}

ثابت نویسه *av_stereo3d_primary_eye_name(unsigned صحیح eye)
{
    اگر (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        بازگشت "unknown";

    بازگشت stereo3d_primary_eye_names[eye];
}

صحیح av_stereo3d_primary_eye_from_name(ثابت نویسه *name)
{
    صحیح i;

    برای (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        اگر (!strcmp(name, stereo3d_primary_eye_names[i]))
            بازگشت i;
    }

    بازگشت -1;
}
