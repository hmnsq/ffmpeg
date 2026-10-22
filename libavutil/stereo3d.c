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
    stereo->horizontal_ಕ್ಷೇತ್ರ_ದ_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ av_stereo3d_alloc_ಗಾತ್ರ(ಖಾಲಿ);
}

AVStereo3D *av_stereo3d_alloc_ಗಾತ್ರ(size_t *ಗಾತ್ರ_2)
{
    AVStereo3D *stereo = av_mallocz(ಗಾತ್ರ(AVStereo3D));

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = stereo ? ಗಾತ್ರ(*stereo) : 0;

    ಆದರೆ (!stereo)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    get_defaults(stereo);

    ಹಿಂತಿರುಗಿ stereo;
}

AVStereo3D *av_stereo3d_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು)
{
    AVFrame_Side_ದತ್ತಾಂಶ *side_ದತ್ತಾಂಶ = av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು,
                                                        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_STEREO3_D,
                                                        ಗಾತ್ರ(AVStereo3D));
    ಆದರೆ (!side_ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    memset(side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ, 0, ಗಾತ್ರ(AVStereo3D));
    get_defaults((AVStereo3D *)side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ);

    ಹಿಂತಿರುಗಿ (AVStereo3D *)side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ stereo3d_type_ಹೆಸರುಗಳು[] = {
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ stereo3d_view_ಹೆಸರುಗಳು[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_ಎಡ]   = "left",
    [AV_STEREO3_D_VIEW_ಬಲ]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ * ಸ್ಥಿರಾಂಕ stereo3d_primary_eye_ಹೆಸರುಗಳು[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_ಎಡ]  = "left",
    [AV_PRIMARY_EYE_ಬಲ] = "right",
};

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_stereo3d_type_name(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ type)
{
    ಆದರೆ (type >= FF_ARRAY_ELEMS(stereo3d_type_ಹೆಸರುಗಳು))
        ಹಿಂತಿರುಗಿ "unknown";

    ಹಿಂತಿರುಗಿ stereo3d_type_ಹೆಸರುಗಳು[type];
}

ಪೂರ್ಣಾಂಕ av_stereo3d_from_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_ಹೆಸರುಗಳು); i++) {
        ಆದರೆ (!strcmp(name, stereo3d_type_ಹೆಸರುಗಳು[i]))
            ಹಿಂತಿರುಗಿ i;
    }

    ಹಿಂತಿರುಗಿ -1;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_stereo3d_view_name(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ view)
{
    ಆದರೆ (view >= FF_ARRAY_ELEMS(stereo3d_view_ಹೆಸರುಗಳು))
        ಹಿಂತಿರುಗಿ "unknown";

    ಹಿಂತಿರುಗಿ stereo3d_view_ಹೆಸರುಗಳು[view];
}

ಪೂರ್ಣಾಂಕ av_stereo3d_view_from_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_ಹೆಸರುಗಳು); i++) {
        ಆದರೆ (!strcmp(name, stereo3d_view_ಹೆಸರುಗಳು[i]))
            ಹಿಂತಿರುಗಿ i;
    }

    ಹಿಂತಿರುಗಿ -1;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_stereo3d_primary_eye_name(ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ eye)
{
    ಆದರೆ (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_ಹೆಸರುಗಳು))
        ಹಿಂತಿರುಗಿ "unknown";

    ಹಿಂತಿರುಗಿ stereo3d_primary_eye_ಹೆಸರುಗಳು[eye];
}

ಪೂರ್ಣಾಂಕ av_stereo3d_primary_eye_from_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_ಹೆಸರುಗಳು); i++) {
        ಆದರೆ (!strcmp(name, stereo3d_primary_eye_ಹೆಸರುಗಳು[i]))
            ಹಿಂತಿರುಗಿ i;
    }

    ಹಿಂತಿರುಗಿ -1;
}
