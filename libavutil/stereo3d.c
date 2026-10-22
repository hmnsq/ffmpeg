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

#अन्तर्भाव <string.h>

#अन्तर्भाव "frame.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "stereo3d.h"

स्थिर शून्य get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_क्षेत्रम्_सम्बन्धि_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(शून्य)
{
    प्रत्यागम av_stereo3d_alloc_आकार(रिक्त);
}

AVStereo3D *av_stereo3d_alloc_आकार(size_t *आकार)
{
    AVStereo3D *stereo = av_mallocz(परिमाण(AVStereo3D));

    यदि (आकार)
        *आकार = stereo ? परिमाण(*stereo) : 0;

    यदि (!stereo)
        प्रत्यागम रिक्त;

    get_defaults(stereo);

    प्रत्यागम stereo;
}

AVStereo3D *av_stereo3d_create_side_दत्त(AVFrame *frame)
{
    AVFrame_Side_दत्त *side_दत्त = av_frame_new_side_दत्त(frame,
                                                        AV_FRAME_दत्त_STEREO3_D,
                                                        परिमाण(AVStereo3D));
    यदि (!side_दत्त)
        प्रत्यागम रिक्त;

    स्मृतिं_पूरय(side_दत्त->दत्त, 0, परिमाण(AVStereo3D));
    get_defaults((AVStereo3D *)side_दत्त->दत्त);

    प्रत्यागम (AVStereo3D *)side_दत्त->दत्त;
}

स्थिर ध्रुव वर्ण * ध्रुव stereo3d_type_नामानि[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_पङ्क्तयः]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

स्थिर ध्रुव वर्ण * ध्रुव stereo3d_view_नामानि[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_वामः]   = "left",
    [AV_STEREO3_D_VIEW_दक्षिणः]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

स्थिर ध्रुव वर्ण * ध्रुव stereo3d_primary_eye_नामानि[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_वामः]  = "left",
    [AV_PRIMARY_EYE_दक्षिणः] = "right",
};

ध्रुव वर्ण *av_stereo3d_type_name(अचिह्नित पूर्णाङ्क type)
{
    यदि (type >= FF_ARRAY_ELEMS(stereo3d_type_नामानि))
        प्रत्यागम "unknown";

    प्रत्यागम stereo3d_type_नामानि[type];
}

पूर्णाङ्क av_stereo3d_from_name(ध्रुव वर्ण *name)
{
    पूर्णाङ्क i;

    प्रति (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_नामानि); i++) {
        यदि (!वाक्यं_तुलय(name, stereo3d_type_नामानि[i]))
            प्रत्यागम i;
    }

    प्रत्यागम -1;
}

ध्रुव वर्ण *av_stereo3d_view_name(अचिह्नित पूर्णाङ्क view)
{
    यदि (view >= FF_ARRAY_ELEMS(stereo3d_view_नामानि))
        प्रत्यागम "unknown";

    प्रत्यागम stereo3d_view_नामानि[view];
}

पूर्णाङ्क av_stereo3d_view_from_name(ध्रुव वर्ण *name)
{
    पूर्णाङ्क i;

    प्रति (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_नामानि); i++) {
        यदि (!वाक्यं_तुलय(name, stereo3d_view_नामानि[i]))
            प्रत्यागम i;
    }

    प्रत्यागम -1;
}

ध्रुव वर्ण *av_stereo3d_primary_eye_name(अचिह्नित पूर्णाङ्क eye)
{
    यदि (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_नामानि))
        प्रत्यागम "unknown";

    प्रत्यागम stereo3d_primary_eye_नामानि[eye];
}

पूर्णाङ्क av_stereo3d_primary_eye_from_name(ध्रुव वर्ण *name)
{
    पूर्णाङ्क i;

    प्रति (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_नामानि); i++) {
        यदि (!वाक्यं_तुलय(name, stereo3d_primary_eye_नामानि[i]))
            प्रत्यागम i;
    }

    प्रत्यागम -1;
}
