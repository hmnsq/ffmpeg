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

#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "frame.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "stereo3d.h"

സ്ഥിതം ശൂന്യം get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_field_of_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(ശൂന്യം)
{
    തിരികെ av_stereo3d_alloc_size(ശൂന്യ);
}

AVStereo3D *av_stereo3d_alloc_size(size_t *size)
{
    AVStereo3D *stereo = av_mallocz(വലുപ്പം(AVStereo3D));

    എങ്കിൽ (size)
        *size = stereo ? വലുപ്പം(*stereo) : 0;

    എങ്കിൽ (!stereo)
        തിരികെ ശൂന്യ;

    get_defaults(stereo);

    തിരികെ stereo;
}

AVStereo3D *av_stereo3d_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_STEREO3D,
                                                        വലുപ്പം(AVStereo3D));
    എങ്കിൽ (!side_data)
        തിരികെ ശൂന്യ;

    memset(side_data->data, 0, വലുപ്പം(AVStereo3D));
    get_defaults((AVStereo3D *)side_data->data);

    തിരികെ (AVStereo3D *)side_data->data;
}

സ്ഥിതം സ്ഥിരം അക്ഷരം * സ്ഥിരം stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_വരികൾ]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

സ്ഥിതം സ്ഥിരം അക്ഷരം * സ്ഥിരം stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_ഇടത്]   = "left",
    [AV_STEREO3_D_VIEW_വലത്]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

സ്ഥിതം സ്ഥിരം അക്ഷരം * സ്ഥിരം stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_ഇടത്]  = "left",
    [AV_PRIMARY_EYE_വലത്] = "right",
};

സ്ഥിരം അക്ഷരം *av_stereo3d_type_name(unsigned പൂർണ്ണസംഖ്യ type)
{
    എങ്കിൽ (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        തിരികെ "unknown";

    തിരികെ stereo3d_type_names[type];
}

പൂർണ്ണസംഖ്യ av_stereo3d_from_name(സ്ഥിരം അക്ഷരം *name)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        എങ്കിൽ (!strcmp(name, stereo3d_type_names[i]))
            തിരികെ i;
    }

    തിരികെ -1;
}

സ്ഥിരം അക്ഷരം *av_stereo3d_view_name(unsigned പൂർണ്ണസംഖ്യ view)
{
    എങ്കിൽ (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        തിരികെ "unknown";

    തിരികെ stereo3d_view_names[view];
}

പൂർണ്ണസംഖ്യ av_stereo3d_view_from_name(സ്ഥിരം അക്ഷരം *name)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        എങ്കിൽ (!strcmp(name, stereo3d_view_names[i]))
            തിരികെ i;
    }

    തിരികെ -1;
}

സ്ഥിരം അക്ഷരം *av_stereo3d_primary_eye_name(unsigned പൂർണ്ണസംഖ്യ eye)
{
    എങ്കിൽ (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        തിരികെ "unknown";

    തിരികെ stereo3d_primary_eye_names[eye];
}

പൂർണ്ണസംഖ്യ av_stereo3d_primary_eye_from_name(സ്ഥിരം അക്ഷരം *name)
{
    പൂർണ്ണസംഖ്യ i;

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        എങ്കിൽ (!strcmp(name, stereo3d_primary_eye_names[i]))
            തിരികെ i;
    }

    തിരികെ -1;
}
