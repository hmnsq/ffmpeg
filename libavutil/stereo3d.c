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

#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "frame.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "stereo3d.h"

ସ୍ଥିର ଶୂନ୍ୟ get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_field_of_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ av_stereo3d_alloc_size(ଖାଲି);
}

AVStereo3D *av_stereo3d_alloc_size(size_t *size)
{
    AVStereo3D *stereo = av_mallocz(ଆକାର(AVStereo3D));

    ଯଦି (size)
        *size = stereo ? ଆକାର(*stereo) : 0;

    ଯଦି (!stereo)
        ଫେରନ୍ତୁ ଖାଲି;

    get_defaults(stereo);

    ଫେରନ୍ତୁ stereo;
}

AVStereo3D *av_stereo3d_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_STEREO3D,
                                                        ଆକାର(AVStereo3D));
    ଯଦି (!side_data)
        ଫେରନ୍ତୁ ଖାଲି;

    memset(side_data->data, 0, ଆକାର(AVStereo3D));
    get_defaults((AVStereo3D *)side_data->data);

    ଫେରନ୍ତୁ (AVStereo3D *)side_data->data;
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ stereo3d_type_names[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_ଧାଡ଼ିଗୁଡ଼ିକ]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ stereo3d_view_names[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_ବାମ]   = "left",
    [AV_STEREO3_D_VIEW_ଡାହାଣ]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର * ଅଚଳ stereo3d_primary_eye_names[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_ବାମ]  = "left",
    [AV_PRIMARY_EYE_ଡାହାଣ] = "right",
};

ଅଚଳ ଅକ୍ଷର *av_stereo3d_type_name(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା type)
{
    ଯଦି (type >= FF_ARRAY_ELEMS(stereo3d_type_names))
        ଫେରନ୍ତୁ "unknown";

    ଫେରନ୍ତୁ stereo3d_type_names[type];
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_stereo3d_from_name(ଅଚଳ ଅକ୍ଷର *name)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_names); i++) {
        ଯଦି (!strcmp(name, stereo3d_type_names[i]))
            ଫେରନ୍ତୁ i;
    }

    ଫେରନ୍ତୁ -1;
}

ଅଚଳ ଅକ୍ଷର *av_stereo3d_view_name(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା view)
{
    ଯଦି (view >= FF_ARRAY_ELEMS(stereo3d_view_names))
        ଫେରନ୍ତୁ "unknown";

    ଫେରନ୍ତୁ stereo3d_view_names[view];
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_stereo3d_view_from_name(ଅଚଳ ଅକ୍ଷର *name)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_names); i++) {
        ଯଦି (!strcmp(name, stereo3d_view_names[i]))
            ଫେରନ୍ତୁ i;
    }

    ଫେରନ୍ତୁ -1;
}

ଅଚଳ ଅକ୍ଷର *av_stereo3d_primary_eye_name(unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା eye)
{
    ଯଦି (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_names))
        ଫେରନ୍ତୁ "unknown";

    ଫେରନ୍ତୁ stereo3d_primary_eye_names[eye];
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_stereo3d_primary_eye_from_name(ଅଚଳ ଅକ୍ଷର *name)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_names); i++) {
        ଯଦି (!strcmp(name, stereo3d_primary_eye_names[i]))
            ଫେରନ୍ତୁ i;
    }

    ଫେରନ୍ତୁ -1;
}
