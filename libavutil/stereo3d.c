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

#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stereo3d.h"

ਸਥਿਰ ਖਾਲੀ get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_ਖੇਤਰ_ਦਾ_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(ਖਾਲੀ)
{
    ਵਾਪਸ av_stereo3d_alloc_ਮਾਪ(ਨਿਰਾ);
}

AVStereo3D *av_stereo3d_alloc_ਮਾਪ(size_t *ਮਾਪ)
{
    AVStereo3D *stereo = av_mallocz(ਆਕਾਰ(AVStereo3D));

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = stereo ? ਆਕਾਰ(*stereo) : 0;

    ਜੇ (!stereo)
        ਵਾਪਸ ਨਿਰਾ;

    get_defaults(stereo);

    ਵਾਪਸ stereo;
}

AVStereo3D *av_stereo3d_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ)
{
    AVFrame_Side_ਅੰਕੜੇ *side_ਅੰਕੜੇ = av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ(ਚੌਖਟਾ,
                                                        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_STEREO3_D,
                                                        ਆਕਾਰ(AVStereo3D));
    ਜੇ (!side_ਅੰਕੜੇ)
        ਵਾਪਸ ਨਿਰਾ;

    memset(side_ਅੰਕੜੇ->ਅੰਕੜੇ, 0, ਆਕਾਰ(AVStereo3D));
    get_defaults((AVStereo3D *)side_ਅੰਕੜੇ->ਅੰਕੜੇ);

    ਵਾਪਸ (AVStereo3D *)side_ਅੰਕੜੇ->ਅੰਕੜੇ;
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ stereo3d_type_ਨਾਂ[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_ਸਤਰਾਂ]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ stereo3d_view_ਨਾਂ[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_ਖੱਬਾ]   = "left",
    [AV_STEREO3_D_VIEW_ਸੱਜਾ]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

ਸਥਿਰ ਅਚਲ ਅੱਖਰ * ਅਚਲ stereo3d_primary_eye_ਨਾਂ[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_ਖੱਬਾ]  = "left",
    [AV_PRIMARY_EYE_ਸੱਜਾ] = "right",
};

ਅਚਲ ਅੱਖਰ *av_stereo3d_type_name(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ type)
{
    ਜੇ (type >= FF_ARRAY_ELEMS(stereo3d_type_ਨਾਂ))
        ਵਾਪਸ "unknown";

    ਵਾਪਸ stereo3d_type_ਨਾਂ[type];
}

ਪੂਰਨ av_stereo3d_from_name(ਅਚਲ ਅੱਖਰ *name)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_ਨਾਂ); i++) {
        ਜੇ (!strcmp(name, stereo3d_type_ਨਾਂ[i]))
            ਵਾਪਸ i;
    }

    ਵਾਪਸ -1;
}

ਅਚਲ ਅੱਖਰ *av_stereo3d_view_name(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ view)
{
    ਜੇ (view >= FF_ARRAY_ELEMS(stereo3d_view_ਨਾਂ))
        ਵਾਪਸ "unknown";

    ਵਾਪਸ stereo3d_view_ਨਾਂ[view];
}

ਪੂਰਨ av_stereo3d_view_from_name(ਅਚਲ ਅੱਖਰ *name)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_ਨਾਂ); i++) {
        ਜੇ (!strcmp(name, stereo3d_view_ਨਾਂ[i]))
            ਵਾਪਸ i;
    }

    ਵਾਪਸ -1;
}

ਅਚਲ ਅੱਖਰ *av_stereo3d_primary_eye_name(ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ eye)
{
    ਜੇ (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_ਨਾਂ))
        ਵਾਪਸ "unknown";

    ਵਾਪਸ stereo3d_primary_eye_ਨਾਂ[eye];
}

ਪੂਰਨ av_stereo3d_primary_eye_from_name(ਅਚਲ ਅੱਖਰ *name)
{
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_ਨਾਂ); i++) {
        ਜੇ (!strcmp(name, stereo3d_primary_eye_ਨਾਂ[i]))
            ਵਾਪਸ i;
    }

    ਵਾਪਸ -1;
}
