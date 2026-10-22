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

#అన్తర్భావ <string.h>

#అన్తర్భావ "frame.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "stereo3d.h"

స్థిర శూన్య get_defaults(AVStereo3D *stereo)
{
    stereo->horizontal_disparity_adjustment = (AVRational) { 0, 1 };
    stereo->horizontal_క్షేత్రం_యొక్క_view = (AVRational) { 0, 1 };
}

AVStereo3D *av_stereo3d_alloc(శూన్య)
{
    తిరిగి av_stereo3d_alloc_కొలత(ఖాళీ);
}

AVStereo3D *av_stereo3d_alloc_కొలత(size_t *కొలత)
{
    AVStereo3D *stereo = av_mallocz(పరిమాణం(AVStereo3D));

    ఒకవేళ (కొలత)
        *కొలత = stereo ? పరిమాణం(*stereo) : 0;

    ఒకవేళ (!stereo)
        తిరిగి ఖాళీ;

    get_defaults(stereo);

    తిరిగి stereo;
}

AVStereo3D *av_stereo3d_create_side_దత్తాంశం(AVFrame *చట్రం)
{
    AVFrame_Side_దత్తాంశం *side_దత్తాంశం = av_చట్రం_new_side_దత్తాంశం(చట్రం,
                                                        AV_చట్రం_దత్తాంశం_STEREO3_D,
                                                        పరిమాణం(AVStereo3D));
    ఒకవేళ (!side_దత్తాంశం)
        తిరిగి ఖాళీ;

    memset(side_దత్తాంశం->దత్తాంశం, 0, పరిమాణం(AVStereo3D));
    get_defaults((AVStereo3D *)side_దత్తాంశం->దత్తాంశం);

    తిరిగి (AVStereo3D *)side_దత్తాంశం->దత్తాంశం;
}

స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి stereo3d_type_పేర్లు[] = {
    [AV_STEREO3D_2D]                  = "2D",
    [AV_STEREO3D_SIDEBYSIDE]          = "side by side",
    [AV_STEREO3D_TOPBOTTOM]           = "top and bottom",
    [AV_STEREO3D_FRAMESEQUENCE]       = "frame alternate",
    [AV_STEREO3D_CHECKERBOARD]        = "checkerboard",
    [AV_STEREO3D_SIDEBYSIDE_QUINCUNX] = "side by side (quincunx subsampling)",
    [AV_STEREO3_D_పంక్తులు]               = "interleaved lines",
    [AV_STEREO3D_COLUMNS]             = "interleaved columns",
    [AV_STEREO3D_UNSPEC]              = "unspecified",
};

స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి stereo3d_view_పేర్లు[] = {
    [AV_STEREO3D_VIEW_PACKED] = "packed",
    [AV_STEREO3_D_VIEW_ఎడమ]   = "left",
    [AV_STEREO3_D_VIEW_కుడి]  = "right",
    [AV_STEREO3D_VIEW_UNSPEC] = "unspecified",
};

స్థిర స్థిరరాశి అక్షరం * స్థిరరాశి stereo3d_primary_eye_పేర్లు[] = {
    [AV_PRIMARY_EYE_NONE]  = "none",
    [AV_PRIMARY_EYE_ఎడమ]  = "left",
    [AV_PRIMARY_EYE_కుడి] = "right",
};

స్థిరరాశి అక్షరం *av_stereo3d_type_name(గుర్తులేని పూర్ణాంకం type)
{
    ఒకవేళ (type >= FF_ARRAY_ELEMS(stereo3d_type_పేర్లు))
        తిరిగి "unknown";

    తిరిగి stereo3d_type_పేర్లు[type];
}

పూర్ణాంకం av_stereo3d_from_name(స్థిరరాశి అక్షరం *name)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(stereo3d_type_పేర్లు); i++) {
        ఒకవేళ (!strcmp(name, stereo3d_type_పేర్లు[i]))
            తిరిగి i;
    }

    తిరిగి -1;
}

స్థిరరాశి అక్షరం *av_stereo3d_view_name(గుర్తులేని పూర్ణాంకం view)
{
    ఒకవేళ (view >= FF_ARRAY_ELEMS(stereo3d_view_పేర్లు))
        తిరిగి "unknown";

    తిరిగి stereo3d_view_పేర్లు[view];
}

పూర్ణాంకం av_stereo3d_view_from_name(స్థిరరాశి అక్షరం *name)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(stereo3d_view_పేర్లు); i++) {
        ఒకవేళ (!strcmp(name, stereo3d_view_పేర్లు[i]))
            తిరిగి i;
    }

    తిరిగి -1;
}

స్థిరరాశి అక్షరం *av_stereo3d_primary_eye_name(గుర్తులేని పూర్ణాంకం eye)
{
    ఒకవేళ (eye >= FF_ARRAY_ELEMS(stereo3d_primary_eye_పేర్లు))
        తిరిగి "unknown";

    తిరిగి stereo3d_primary_eye_పేర్లు[eye];
}

పూర్ణాంకం av_stereo3d_primary_eye_from_name(స్థిరరాశి అక్షరం *name)
{
    పూర్ణాంకం i;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(stereo3d_primary_eye_పేర్లు); i++) {
        ఒకవేళ (!strcmp(name, stereo3d_primary_eye_పేర్లు[i]))
            తిరిగి i;
    }

    తిరిగి -1;
}
