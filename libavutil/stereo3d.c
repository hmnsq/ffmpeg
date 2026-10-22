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

#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "frame.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "stereo3d.h"

ಸ್ಥಿರ ಶೂನ್ಯ get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_field_of_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ av_stereo3d_alloc_size(ರಿಕ್ತ);
}

AVStereo3D *av_stereo3d_alloc_size(size_t *size)
{
    AVStereo3D *stereo = av_mallocz(ಪರಿಮಾಣ(AVStereo3D));

    ಯದಿ (size)
        *size = stereo ? ಪರಿಮಾಣ(*stereo) : 0;

    ಯದಿ (!stereo)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    get_defaults(stereo);

    ಪ್ರತ್ಯಾಗಮ stereo;
}

AVStereo3D *av_stereo3d_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_STEREO3D,
                                                        ಪರಿಮಾಣ(AVStereo3D));
    ಯದಿ (!side_data)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    memset(side_data->data, 0, ಪರಿಮಾಣ(AVStereo3D));
    get_defaults((AVStereo3D *)side_data->data);

    ಪ್ರತ್ಯಾಗಮ (AVStereo3D *)side_data->data;
}

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_ಸಾಲುಗಳು]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_ಎಡ]   = "left",
    [AV_STEREO3_D_VIEW_ಬಲ]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ * ಧ್ರುವ stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_ಎಡ]  = "left",
    [AV_PRIMARY_EYE_ಬಲ] = "right",
};

ಧ್ರುವ ವರ್ಣ *av_stereo3d_type_name(unsigned ಪೂರ್ಣಾಙ್ಕ type)
{
    ಯದಿ (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        ಪ್ರತ್ಯಾಗಮ "unknown";

    ಪ್ರತ್ಯಾಗಮ stereo3d_type_names[type];
}

ಪೂರ್ಣಾಙ್ಕ av_stereo3d_from_name(ಧ್ರುವ ವರ್ಣ *name)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        ಯದಿ (!strcmp(name, stereo3d_type_names[i]))
            ಪ್ರತ್ಯಾಗಮ i;
    }

    ಪ್ರತ್ಯಾಗಮ -1;
}

ಧ್ರುವ ವರ್ಣ *av_stereo3d_view_name(unsigned ಪೂರ್ಣಾಙ್ಕ view)
{
    ಯದಿ (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        ಪ್ರತ್ಯಾಗಮ "unknown";

    ಪ್ರತ್ಯಾಗಮ stereo3d_view_names[view];
}

ಪೂರ್ಣಾಙ್ಕ av_stereo3d_view_from_name(ಧ್ರುವ ವರ್ಣ *name)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        ಯದಿ (!strcmp(name, stereo3d_view_names[i]))
            ಪ್ರತ್ಯಾಗಮ i;
    }

    ಪ್ರತ್ಯಾಗಮ -1;
}

ಧ್ರುವ ವರ್ಣ *av_stereo3d_primary_eye_name(unsigned ಪೂರ್ಣಾಙ್ಕ eye)
{
    ಯದಿ (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        ಪ್ರತ್ಯಾಗಮ "unknown";

    ಪ್ರತ್ಯಾಗಮ stereo3d_primary_eye_names[eye];
}

ಪೂರ್ಣಾಙ್ಕ av_stereo3d_primary_eye_from_name(ಧ್ರುವ ವರ್ಣ *name)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        ಯದಿ (!strcmp(name, stereo3d_primary_eye_names[i]))
            ಪ್ರತ್ಯಾಗಮ i;
    }

    ಪ್ರತ್ಯಾಗಮ -1;
}
