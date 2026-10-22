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

#অন্তর্ভাব <string.h>

#অন্তর্ভাব "frame.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "stereo3d.h"

স্থির শূন্য get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_field_of_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(শূন্য)
{
    প্রত্যাগম av_stereo3d_alloc_size(রিক্ত);
}

AVStereo3D *av_stereo3d_alloc_size(size_t *size)
{
    AVStereo3D *stereo = av_mallocz(পরিমাণ(AVStereo3D));

    যদি (size)
        *size = stereo ? পরিমাণ(*stereo) : 0;

    যদি (!stereo)
        প্রত্যাগম রিক্ত;

    get_defaults(stereo);

    প্রত্যাগম stereo;
}

AVStereo3D *av_stereo3d_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_STEREO3D,
                                                        পরিমাণ(AVStereo3D));
    যদি (!side_data)
        প্রত্যাগম রিক্ত;

    memset(side_data->data, 0, পরিমাণ(AVStereo3D));
    get_defaults((AVStereo3D *)side_data->data);

    প্রত্যাগম (AVStereo3D *)side_data->data;
}

স্থির ধ্রুব বর্ণ * ধ্রুব stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_সারিগুলি]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

স্থির ধ্রুব বর্ণ * ধ্রুব stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_বাম]   = "left",
    [AV_STEREO3_D_VIEW_ডান]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

স্থির ধ্রুব বর্ণ * ধ্রুব stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_বাম]  = "left",
    [AV_PRIMARY_EYE_ডান] = "right",
};

ধ্রুব বর্ণ *av_stereo3d_type_name(unsigned পূর্ণাঙ্ক type)
{
    যদি (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        প্রত্যাগম "unknown";

    প্রত্যাগম stereo3d_type_names[type];
}

পূর্ণাঙ্ক av_stereo3d_from_name(ধ্রুব বর্ণ *name)
{
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        যদি (!strcmp(name, stereo3d_type_names[i]))
            প্রত্যাগম i;
    }

    প্রত্যাগম -1;
}

ধ্রুব বর্ণ *av_stereo3d_view_name(unsigned পূর্ণাঙ্ক view)
{
    যদি (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        প্রত্যাগম "unknown";

    প্রত্যাগম stereo3d_view_names[view];
}

পূর্ণাঙ্ক av_stereo3d_view_from_name(ধ্রুব বর্ণ *name)
{
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        যদি (!strcmp(name, stereo3d_view_names[i]))
            প্রত্যাগম i;
    }

    প্রত্যাগম -1;
}

ধ্রুব বর্ণ *av_stereo3d_primary_eye_name(unsigned পূর্ণাঙ্ক eye)
{
    যদি (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        প্রত্যাগম "unknown";

    প্রত্যাগম stereo3d_primary_eye_names[eye];
}

পূর্ণাঙ্ক av_stereo3d_primary_eye_from_name(ধ্রুব বর্ণ *name)
{
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        যদি (!strcmp(name, stereo3d_primary_eye_names[i]))
            প্রত্যাগম i;
    }

    প্রত্যাগম -1;
}
