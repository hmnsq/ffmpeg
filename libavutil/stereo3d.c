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

#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "frame.h"
#અન્તર્ભાવ "macros.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "stereo3d.h"

સ્થિર શૂન્ય get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_field_of_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(શૂન્ય)
{
    પાછા av_stereo3d_alloc_size(ખાલી);
}

AVStereo3D *av_stereo3d_alloc_size(size_t *size)
{
    AVStereo3D *stereo = av_mallocz(કદ(AVStereo3D));

    જો (size)
        *size = stereo ? કદ(*stereo) : 0;

    જો (!stereo)
        પાછા ખાલી;

    get_defaults(stereo);

    પાછા stereo;
}

AVStereo3D *av_stereo3d_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_STEREO3D,
                                                        કદ(AVStereo3D));
    જો (!side_data)
        પાછા ખાલી;

    memset(side_data->data, 0, કદ(AVStereo3D));
    get_defaults((AVStereo3D *)side_data->data);

    પાછા (AVStereo3D *)side_data->data;
}

સ્થિર અચલ અક્ષર * અચલ stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_લીટીઓ]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

સ્થિર અચલ અક્ષર * અચલ stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_ડાબું]   = "left",
    [AV_STEREO3_D_VIEW_જમણું]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

સ્થિર અચલ અક્ષર * અચલ stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_ડાબું]  = "left",
    [AV_PRIMARY_EYE_જમણું] = "right",
};

અચલ અક્ષર *av_stereo3d_type_name(unsigned પૂર્ણાંક type)
{
    જો (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        પાછા "unknown";

    પાછા stereo3d_type_names[type];
}

પૂર્ણાંક av_stereo3d_from_name(અચલ અક્ષર *name)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        જો (!strcmp(name, stereo3d_type_names[i]))
            પાછા i;
    }

    પાછા -1;
}

અચલ અક્ષર *av_stereo3d_view_name(unsigned પૂર્ણાંક view)
{
    જો (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        પાછા "unknown";

    પાછા stereo3d_view_names[view];
}

પૂર્ણાંક av_stereo3d_view_from_name(અચલ અક્ષર *name)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        જો (!strcmp(name, stereo3d_view_names[i]))
            પાછા i;
    }

    પાછા -1;
}

અચલ અક્ષર *av_stereo3d_primary_eye_name(unsigned પૂર્ણાંક eye)
{
    જો (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        પાછા "unknown";

    પાછા stereo3d_primary_eye_names[eye];
}

પૂર્ણાંક av_stereo3d_primary_eye_from_name(અચલ અક્ષર *name)
{
    પૂર્ણાંક i;

    માટે (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        જો (!strcmp(name, stereo3d_primary_eye_names[i]))
            પાછા i;
    }

    પાછા -1;
}
