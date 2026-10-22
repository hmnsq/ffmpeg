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

#अन्तर्भाव <string.h>

#अन्तर्भाव "frame.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "stereo3d.h"

स्थिर शून्य get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_field_of_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(शून्य)
{
    परत av_stereo3d_alloc_size(रिक्त);
}

AVStereo3D *av_stereo3d_alloc_size(माप_प्रकार *size)
{
    AVStereo3D *stereo = av_mallocz(आकार(AVStereo3D));

    जर (size)
        *size = stereo ? आकार(*stereo) : 0;

    जर (!stereo)
        परत रिक्त;

    get_defaults(stereo);

    परत stereo;
}

AVStereo3D *av_stereo3d_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_STEREO3D,
                                                        आकार(AVStereo3D));
    जर (!side_data)
        परत रिक्त;

    स_रखो(side_data->data, 0, आकार(AVStereo3D));
    get_defaults((AVStereo3D *)side_data->data);

    परत (AVStereo3D *)side_data->data;
}

स्थिर स्थिरांक अक्षर * स्थिरांक stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_ओळी]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

स्थिर स्थिरांक अक्षर * स्थिरांक stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_डावा]   = "left",
    [AV_STEREO3_D_VIEW_उजवा]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

स्थिर स्थिरांक अक्षर * स्थिरांक stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_डावा]  = "left",
    [AV_PRIMARY_EYE_उजवा] = "right",
};

स्थिरांक अक्षर *av_stereo3d_type_name(अचिन्हित पूर्णांक type)
{
    जर (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        परत "unknown";

    परत stereo3d_type_names[type];
}

पूर्णांक av_stereo3d_from_name(स्थिरांक अक्षर *name)
{
    पूर्णांक i;

    साठी (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        जर (!म_भेद(name, stereo3d_type_names[i]))
            परत i;
    }

    परत -1;
}

स्थिरांक अक्षर *av_stereo3d_view_name(अचिन्हित पूर्णांक view)
{
    जर (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        परत "unknown";

    परत stereo3d_view_names[view];
}

पूर्णांक av_stereo3d_view_from_name(स्थिरांक अक्षर *name)
{
    पूर्णांक i;

    साठी (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        जर (!म_भेद(name, stereo3d_view_names[i]))
            परत i;
    }

    परत -1;
}

स्थिरांक अक्षर *av_stereo3d_primary_eye_name(अचिन्हित पूर्णांक eye)
{
    जर (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        परत "unknown";

    परत stereo3d_primary_eye_names[eye];
}

पूर्णांक av_stereo3d_primary_eye_from_name(स्थिरांक अक्षर *name)
{
    पूर्णांक i;

    साठी (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        जर (!म_भेद(name, stereo3d_primary_eye_names[i]))
            परत i;
    }

    परत -1;
}
