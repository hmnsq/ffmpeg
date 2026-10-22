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

#समावेश <string.h>

#समावेश "frame.h"
#समावेश "macros.h"
#समावेश "mem.h"
#समावेश "stereo3d.h"

अटल व्योम get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_field_of_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(व्योम)
{
    वापस av_stereo3d_alloc_आकार(शून्य);
}

AVStereo3D *av_stereo3d_alloc_आकार(माप_प्रकार *आकार)
{
    AVStereo3D *stereo = av_mallocz(माप(AVStereo3D));

    अगर (आकार)
        *आकार = stereo ? माप(*stereo) : 0;

    अगर (!stereo)
        वापस शून्य;

    get_defaults(stereo);

    वापस stereo;
}

AVStereo3D *av_stereo3d_create_side_तथ्य(AVFrame *frame)
{
    AVFrame_Side_तथ्य *side_तथ्य = av_frame_new_side_तथ्य(frame,
                                                        AV_FRAME_तथ्य_STEREO3_D,
                                                        माप(AVStereo3D));
    अगर (!side_तथ्य)
        वापस शून्य;

    स_रखो(side_तथ्य->तथ्य, 0, माप(AVStereo3D));
    get_defaults((AVStereo3D *)side_तथ्य->तथ्य);

    वापस (AVStereo3D *)side_तथ्य->तथ्य;
}

अटल स्थिर अक्षर * स्थिर stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_पंक्तियाँ]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

अटल स्थिर अक्षर * स्थिर stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_बायाँ]   = "left",
    [AV_STEREO3_D_VIEW_दायाँ]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

अटल स्थिर अक्षर * स्थिर stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_बायाँ]  = "left",
    [AV_PRIMARY_EYE_दायाँ] = "right",
};

स्थिर अक्षर *av_stereo3d_type_name(अचिन्हित पूर्णांक type)
{
    अगर (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        वापस "unknown";

    वापस stereo3d_type_names[type];
}

पूर्णांक av_stereo3d_from_name(स्थिर अक्षर *name)
{
    पूर्णांक i;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        अगर (!म_भेद(name, stereo3d_type_names[i]))
            वापस i;
    }

    वापस -1;
}

स्थिर अक्षर *av_stereo3d_view_name(अचिन्हित पूर्णांक view)
{
    अगर (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        वापस "unknown";

    वापस stereo3d_view_names[view];
}

पूर्णांक av_stereo3d_view_from_name(स्थिर अक्षर *name)
{
    पूर्णांक i;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        अगर (!म_भेद(name, stereo3d_view_names[i]))
            वापस i;
    }

    वापस -1;
}

स्थिर अक्षर *av_stereo3d_primary_eye_name(अचिन्हित पूर्णांक eye)
{
    अगर (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        वापस "unknown";

    वापस stereo3d_primary_eye_names[eye];
}

पूर्णांक av_stereo3d_primary_eye_from_name(स्थिर अक्षर *name)
{
    पूर्णांक i;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        अगर (!म_भेद(name, stereo3d_primary_eye_names[i]))
            वापस i;
    }

    वापस -1;
}
