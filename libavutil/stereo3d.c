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

ساکن خالی get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_میدان_کا_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(خالی)
{
    واپس av_stereo3d_alloc_سائز(تہی);
}

AVStereo3D *av_stereo3d_alloc_سائز(size_t *سائز)
{
    AVStereo3D *stereo = av_mallocz(حجم(AVStereo3D));

    اگر (سائز)
        *سائز = stereo ? حجم(*stereo) : 0;

    اگر (!stereo)
        واپس تہی;

    get_defaults(stereo);

    واپس stereo;
}

AVStereo3D *av_stereo3d_create_side_ڈیٹا(AVFrame *چوکھٹا)
{
    AVFrame_Side_ڈیٹا *side_ڈیٹا = av_چوکھٹا_new_side_ڈیٹا(چوکھٹا,
                                                        AV_چوکھٹا_ڈیٹا_STEREO3_D,
                                                        حجم(AVStereo3D));
    اگر (!side_ڈیٹا)
        واپس تہی;

    memset(side_ڈیٹا->ڈیٹا, 0, حجم(AVStereo3D));
    get_defaults((AVStereo3D *)side_ڈیٹا->ڈیٹا);

    واپس (AVStereo3D *)side_ڈیٹا->ڈیٹا;
}

ساکن ثابت حرف * ثابت stereo3d_type_نام[] = {
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

ساکن ثابت حرف * ثابت stereo3d_view_نام[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_بایاں]   = "left",
    [AV_STEREO3_D_VIEW_دایاں]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

ساکن ثابت حرف * ثابت stereo3d_primary_eye_نام[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_بایاں]  = "left",
    [AV_PRIMARY_EYE_دایاں] = "right",
};

ثابت حرف *av_stereo3d_type_name(غیرعلامتی صحیح type)
{
    اگر (type >= FF_ARRAY_ELEMS(stereo3d_type_نام))
        واپس "unknown";

    واپس stereo3d_type_نام[type];
}

صحیح av_stereo3d_from_name(ثابت حرف *name)
{
    صحیح i;

    برائے (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_نام); i++) {
        اگر (!strcmp(name, stereo3d_type_نام[i]))
            واپس i;
    }

    واپس -1;
}

ثابت حرف *av_stereo3d_view_name(غیرعلامتی صحیح view)
{
    اگر (view >= FF_ARRAY_ELEMS(stereo3d_view_نام))
        واپس "unknown";

    واپس stereo3d_view_نام[view];
}

صحیح av_stereo3d_view_from_name(ثابت حرف *name)
{
    صحیح i;

    برائے (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_نام); i++) {
        اگر (!strcmp(name, stereo3d_view_نام[i]))
            واپس i;
    }

    واپس -1;
}

ثابت حرف *av_stereo3d_primary_eye_name(غیرعلامتی صحیح eye)
{
    اگر (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_نام))
        واپس "unknown";

    واپس stereo3d_primary_eye_نام[eye];
}

صحیح av_stereo3d_primary_eye_from_name(ثابت حرف *name)
{
    صحیح i;

    برائے (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_نام); i++) {
        اگر (!strcmp(name, stereo3d_primary_eye_نام[i]))
            واپس i;
    }

    واپس -1;
}
