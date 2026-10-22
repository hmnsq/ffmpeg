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
    stereo->horizontal_میدان_دا_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(فراغ)
{
    أرجع av_stereo3d_alloc_ناپ(عدم);
}

AVStereo3D *av_stereo3d_alloc_ناپ(size_t *ناپ)
{
    AVStereo3D *stereo = av_mallocz(حجم(AVStereo3D));

    إذا (ناپ)
        *ناپ = stereo ? حجم(*stereo) : 0;

    إذا (!stereo)
        أرجع عدم;

    get_defaults(stereo);

    أرجع stereo;
}

AVStereo3D *av_stereo3d_create_side_انکڑے(AVFrame *چوکھٹا)
{
    AVFrame_Side_انکڑے *side_انکڑے = av_چوکھٹا_new_side_انکڑے(چوکھٹا,
                                                        AV_چوکھٹا_انکڑے_STEREO3_D,
                                                        حجم(AVStereo3D));
    إذا (!side_انکڑے)
        أرجع عدم;

    memset(side_انکڑے->انکڑے, 0, حجم(AVStereo3D));
    get_defaults((AVStereo3D *)side_انکڑے->انکڑے);

    أرجع (AVStereo3D *)side_انکڑے->انکڑے;
}

ساكن ثابت حرف * ثابت stereo3d_type_ناں[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_سطریں]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

ساكن ثابت حرف * ثابت stereo3d_view_ناں[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_بایاں]   = "left",
    [AV_STEREO3_D_VIEW_دایاں]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

ساكن ثابت حرف * ثابت stereo3d_primary_eye_ناں[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_بایاں]  = "left",
    [AV_PRIMARY_EYE_دایاں] = "right",
};

ثابت حرف *av_stereo3d_type_name(بنانشانی صحيح type)
{
    إذا (type >= FF_ARRAY_ELEMS(stereo3d_type_ناں))
        أرجع "unknown";

    أرجع stereo3d_type_ناں[type];
}

صحيح av_stereo3d_from_name(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_ناں); i++) {
        إذا (!strcmp(name, stereo3d_type_ناں[i]))
            أرجع i;
    }

    أرجع -1;
}

ثابت حرف *av_stereo3d_view_name(بنانشانی صحيح view)
{
    إذا (view >= FF_ARRAY_ELEMS(stereo3d_view_ناں))
        أرجع "unknown";

    أرجع stereo3d_view_ناں[view];
}

صحيح av_stereo3d_view_from_name(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_ناں); i++) {
        إذا (!strcmp(name, stereo3d_view_ناں[i]))
            أرجع i;
    }

    أرجع -1;
}

ثابت حرف *av_stereo3d_primary_eye_name(بنانشانی صحيح eye)
{
    إذا (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_ناں))
        أرجع "unknown";

    أرجع stereo3d_primary_eye_ناں[eye];
}

صحيح av_stereo3d_primary_eye_from_name(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_ناں); i++) {
        إذا (!strcmp(name, stereo3d_primary_eye_ناں[i]))
            أرجع i;
    }

    أرجع -1;
}
