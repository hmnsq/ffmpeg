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
    पटिनिवत्त av_stereo3d_alloc_size(रिक्त);
}

AVStereo3D *av_stereo3d_alloc_size(size_t *size)
{
    AVStereo3D *stereo = av_mallocz(परिमाण(AVStereo3D));

    सचे (size)
        *size = stereo ? परिमाण(*stereo) : 0;

    सचे (!stereo)
        पटिनिवत्त रिक्त;

    get_defaults(stereo);

    पटिनिवत्त stereo;
}

AVStereo3D *av_stereo3d_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_STEREO3D,
                                                        परिमाण(AVStereo3D));
    सचे (!side_data)
        पटिनिवत्त रिक्त;

    memset(side_data->data, 0, परिमाण(AVStereo3D));
    get_defaults((AVStereo3D *)side_data->data);

    पटिनिवत्त (AVStereo3D *)side_data->data;
}

स्थिर ध्रुव वर्ण * ध्रुव stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_पङ्क्तयः]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

स्थिर ध्रुव वर्ण * ध्रुव stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_वामः]   = "left",
    [AV_STEREO3_D_VIEW_दक्षिणः]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

स्थिर ध्रुव वर्ण * ध्रुव stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_वामः]  = "left",
    [AV_PRIMARY_EYE_दक्षिणः] = "right",
};

ध्रुव वर्ण *av_stereo3d_type_name(unsigned पूर्णाङ्क type)
{
    सचे (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        पटिनिवत्त "unknown";

    पटिनिवत्त stereo3d_type_names[type];
}

पूर्णाङ्क av_stereo3d_from_name(ध्रुव वर्ण *name)
{
    पूर्णाङ्क i;

    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        सचे (!strcmp(name, stereo3d_type_names[i]))
            पटिनिवत्त i;
    }

    पटिनिवत्त -1;
}

ध्रुव वर्ण *av_stereo3d_view_name(unsigned पूर्णाङ्क view)
{
    सचे (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        पटिनिवत्त "unknown";

    पटिनिवत्त stereo3d_view_names[view];
}

पूर्णाङ्क av_stereo3d_view_from_name(ध्रुव वर्ण *name)
{
    पूर्णाङ्क i;

    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        सचे (!strcmp(name, stereo3d_view_names[i]))
            पटिनिवत्त i;
    }

    पटिनिवत्त -1;
}

ध्रुव वर्ण *av_stereo3d_primary_eye_name(unsigned पूर्णाङ्क eye)
{
    सचे (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        पटिनिवत्त "unknown";

    पटिनिवत्त stereo3d_primary_eye_names[eye];
}

पूर्णाङ्क av_stereo3d_primary_eye_from_name(ध्रुव वर्ण *name)
{
    पूर्णाङ्क i;

    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        सचे (!strcmp(name, stereo3d_primary_eye_names[i]))
            पटिनिवत्त i;
    }

    पटिनिवत्त -1;
}
