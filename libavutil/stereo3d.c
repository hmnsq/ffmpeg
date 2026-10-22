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
    stereo->horizontal_ميدان_جو_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(فراغ)
{
    أرجع av_stereo3d_alloc_سائيز(عدم);
}

AVStereo3D *av_stereo3d_alloc_سائيز(size_t *سائيز)
{
    AVStereo3D *stereo = av_mallocz(حجم(AVStereo3D));

    إذا (سائيز)
        *سائيز = stereo ? حجم(*stereo) : 0;

    إذا (!stereo)
        أرجع عدم;

    get_defaults(stereo);

    أرجع stereo;
}

AVStereo3D *av_stereo3d_create_side_معلومات(AVFrame *چوکٺو)
{
    AVFrame_Side_معلومات *side_معلومات = av_چوکٺو_new_side_معلومات(چوکٺو,
                                                        AV_چوکٺو_معلومات_STEREO3_D,
                                                        حجم(AVStereo3D));
    إذا (!side_معلومات)
        أرجع عدم;

    memset(side_معلومات->معلومات, 0, حجم(AVStereo3D));
    get_defaults((AVStereo3D *)side_معلومات->معلومات);

    أرجع (AVStereo3D *)side_معلومات->معلومات;
}

ساكن ثابت حرف * ثابت stereo3d_type_نالا[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_سٽون]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

ساكن ثابت حرف * ثابت stereo3d_view_نالا[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_کاٻو]   = "left",
    [AV_STEREO3_D_VIEW_ساڄو]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

ساكن ثابت حرف * ثابت stereo3d_primary_eye_نالا[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_کاٻو]  = "left",
    [AV_PRIMARY_EYE_ساڄو] = "right",
};

ثابت حرف *av_stereo3d_type_name(بنانشان صحيح type)
{
    إذا (type >= FF_ARRAY_ELEMS(stereo3d_type_نالا))
        أرجع "unknown";

    أرجع stereo3d_type_نالا[type];
}

صحيح av_stereo3d_from_name(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_نالا); i++) {
        إذا (!strcmp(name, stereo3d_type_نالا[i]))
            أرجع i;
    }

    أرجع -1;
}

ثابت حرف *av_stereo3d_view_name(بنانشان صحيح view)
{
    إذا (view >= FF_ARRAY_ELEMS(stereo3d_view_نالا))
        أرجع "unknown";

    أرجع stereo3d_view_نالا[view];
}

صحيح av_stereo3d_view_from_name(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_نالا); i++) {
        إذا (!strcmp(name, stereo3d_view_نالا[i]))
            أرجع i;
    }

    أرجع -1;
}

ثابت حرف *av_stereo3d_primary_eye_name(بنانشان صحيح eye)
{
    إذا (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_نالا))
        أرجع "unknown";

    أرجع stereo3d_primary_eye_نالا[eye];
}

صحيح av_stereo3d_primary_eye_from_name(ثابت حرف *name)
{
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_نالا); i++) {
        إذا (!strcmp(name, stereo3d_primary_eye_نالا[i]))
            أرجع i;
    }

    أرجع -1;
}
