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
    ফেরত av_stereo3d_alloc_আকার(ফাঁকা);
}

AVStereo3D *av_stereo3d_alloc_আকার(size_t *আকার_2)
{
    AVStereo3D *stereo = av_mallocz(আকার(AVStereo3D));

    যদি (আকার_2)
        *আকার_2 = stereo ? আকার(*stereo) : 0;

    যদি (!stereo)
        ফেরত ফাঁকা;

    get_defaults(stereo);

    ফেরত stereo;
}

AVStereo3D *av_stereo3d_create_side_তথ্য(AVFrame *frame)
{
    AVFrame_Side_তথ্য *side_তথ্য = av_frame_new_side_তথ্য(frame,
                                                        AV_FRAME_তথ্য_STEREO3_D,
                                                        আকার(AVStereo3D));
    যদি (!side_তথ্য)
        ফেরত ফাঁকা;

    memset(side_তথ্য->তথ্য, 0, আকার(AVStereo3D));
    get_defaults((AVStereo3D *)side_তথ্য->তথ্য);

    ফেরত (AVStereo3D *)side_তথ্য->তথ্য;
}

স্থির ধ্রুবক অক্ষর * ধ্রুবক stereo3d_type_names[] = {
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

স্থির ধ্রুবক অক্ষর * ধ্রুবক stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_বাম]   = "left",
    [AV_STEREO3_D_VIEW_ডান]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

স্থির ধ্রুবক অক্ষর * ধ্রুবক stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_বাম]  = "left",
    [AV_PRIMARY_EYE_ডান] = "right",
};

ধ্রুবক অক্ষর *av_stereo3d_type_name(unsigned পূর্ণসংখ্যা type)
{
    যদি (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        ফেরত "unknown";

    ফেরত stereo3d_type_names[type];
}

পূর্ণসংখ্যা av_stereo3d_from_name(ধ্রুবক অক্ষর *name)
{
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        যদি (!strcmp(name, stereo3d_type_names[i]))
            ফেরত i;
    }

    ফেরত -1;
}

ধ্রুবক অক্ষর *av_stereo3d_view_name(unsigned পূর্ণসংখ্যা view)
{
    যদি (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        ফেরত "unknown";

    ফেরত stereo3d_view_names[view];
}

পূর্ণসংখ্যা av_stereo3d_view_from_name(ধ্রুবক অক্ষর *name)
{
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        যদি (!strcmp(name, stereo3d_view_names[i]))
            ফেরত i;
    }

    ফেরত -1;
}

ধ্রুবক অক্ষর *av_stereo3d_primary_eye_name(unsigned পূর্ণসংখ্যা eye)
{
    যদি (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        ফেরত "unknown";

    ফেরত stereo3d_primary_eye_names[eye];
}

পূর্ণসংখ্যা av_stereo3d_primary_eye_from_name(ধ্রুবক অক্ষর *name)
{
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        যদি (!strcmp(name, stereo3d_primary_eye_names[i]))
            ফেরত i;
    }

    ফেরত -1;
}
