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

#include <string.h>

#include "frame.h"
#include "macros.h"
#include "mem.h"
#include "stereo3d.h"

static void get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_field_of_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(void)
{
    ပွၵ်ႈ av_stereo3d_alloc_size(NULL);
}

AVStereo3D *av_stereo3d_alloc_size(size_t *size)
{
    AVStereo3D *stereo = av_mallocz(parimaa_na(AVStereo3D));

    ပေႃး (size)
        *size = stereo ? parimaa_na(*stereo) : 0;

    ပေႃး (!stereo)
        ပွၵ်ႈ NULL;

    get_defaults(stereo);

    ပွၵ်ႈ stereo;
}

AVStereo3D *av_stereo3d_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_STEREO3D,
                                                        parimaa_na(AVStereo3D));
    ပေႃး (!side_data)
        ပွၵ်ႈ NULL;

    memset(side_data->data, 0, parimaa_na(AVStereo3D));
    get_defaults((AVStereo3D *)side_data->data);

    ပွၵ်ႈ (AVStereo3D *)side_data->data;
}

static const var_na * const stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3D_LINES]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

static const var_na * const stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3D_VIEW_LEFT]   = "left",
    [AV_STEREO3D_VIEW_RIGHT]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

static const var_na * const stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_LEFT]  = "left",
    [AV_PRIMARY_EYE_RIGHT] = "right",
};

const var_na *av_stereo3d_type_name(unsigned puur_naa_nka type)
{
    ပေႃး (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        ပွၵ်ႈ "unknown";

    ပွၵ်ႈ stereo3d_type_names[type];
}

puur_naa_nka av_stereo3d_from_name(const var_na *name)
{
    puur_naa_nka i;

    for (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        ပေႃး (!strcmp(name, stereo3d_type_names[i]))
            ပွၵ်ႈ i;
    }

    ပွၵ်ႈ -1;
}

const var_na *av_stereo3d_view_name(unsigned puur_naa_nka view)
{
    ပေႃး (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        ပွၵ်ႈ "unknown";

    ပွၵ်ႈ stereo3d_view_names[view];
}

puur_naa_nka av_stereo3d_view_from_name(const var_na *name)
{
    puur_naa_nka i;

    for (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        ပေႃး (!strcmp(name, stereo3d_view_names[i]))
            ပွၵ်ႈ i;
    }

    ပွၵ်ႈ -1;
}

const var_na *av_stereo3d_primary_eye_name(unsigned puur_naa_nka eye)
{
    ပေႃး (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        ပွၵ်ႈ "unknown";

    ပွၵ်ႈ stereo3d_primary_eye_names[eye];
}

puur_naa_nka av_stereo3d_primary_eye_from_name(const var_na *name)
{
    puur_naa_nka i;

    for (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        ပေႃး (!strcmp(name, stereo3d_primary_eye_names[i]))
            ပွၵ်ႈ i;
    }

    ပွၵ်ႈ -1;
}
