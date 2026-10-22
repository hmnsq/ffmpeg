/*
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

#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/film_grain_params.h"
#अन्तर्भाव "libavutil/mem.h"

स्थिर AVFrame *create_frame(गणना AVPixelFormat format, पूर्णांक width, पूर्णांक height)
{
    AVFrame *frame = av_frame_alloc();
    जर (!frame)
        परत रिक्त;
    frame->format = format;
    frame->width  = width;
    frame->height = height;
    परत frame;
}

स्थिर AVFilmGrainParams *add_grain(AVFrame *frame,
                                     गणना AVFilmGrainParamsType type,
                                     पूर्णांक width, पूर्णांक height,
                                     पूर्णांक sub_x, पूर्णांक sub_y,
                                     पूर्णांक bd_luma, पूर्णांक bd_chroma)
{
    AVFilmGrainParams *fgp = av_film_grain_params_create_side_data(frame);
    जर (!fgp)
        परत रिक्त;
    fgp->type             = type;
    fgp->width            = width;
    fgp->height           = height;
    fgp->subsampling_x    = sub_x;
    fgp->subsampling_y    = sub_y;
    fgp->bit_depth_luma   = bd_luma;
    fgp->bit_depth_chroma = bd_chroma;
    परत fgp;
}

पूर्णांक main(शून्य)
{
    AVFilmGrainParams *fgp;
    स्थिरांक AVFilmGrainParams *sel;
    AVFrame *frame;
    माप_प्रकार size;

    म_लिखो("Testing av_film_grain_params_alloc()\n");

    fgp = av_film_grain_params_alloc(&size);
    म_लिखो("alloc with size: %s\n", (fgp && size > 0) ? "OK" : "FAIL");
    av_free(fgp);

    fgp = av_film_grain_params_alloc(रिक्त);
    म_लिखो("alloc without size: %s\n", fgp ? "OK" : "FAIL");
    av_free(fgp);

    म_लिखो("\nTesting av_film_grain_params_create_side_data()\n");

    frame = av_frame_alloc();
    fgp = av_film_grain_params_create_side_data(frame);
    जर (fgp)
        म_लिखो("create: OK\ndefaults: range=%d pri=%d trc=%d space=%d\n",
               fgp->color_range, fgp->color_primaries,
               fgp->color_trc, fgp->color_space);
    अन्यथा
        म_लिखो("create: FAIL\n");
    av_frame_free(&frame);

    म_लिखो("\nTesting av_film_grain_params_select()\n");

    /* invalid format */
    frame = av_frame_alloc();
    frame->format = -1;
    sel = av_film_grain_params_select(frame);
    म_लिखो("invalid format: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* no side data */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    sel = av_film_grain_params_select(frame);
    म_लिखो("no side data: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* NONE type - skipped */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_NONE, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("NONE type: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* AV1 exact subsampling match (YUV420P: sub 1,1) */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("AV1 match: %s\n", sel ? "OK" : "FAIL");
    av_frame_free(&frame);

    /* AV1 subsampling mismatch */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 0, 0, 0, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("AV1 sub mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* H274 exact match */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_H274, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("H274 match: %s\n", sel ? "OK" : "FAIL");
    av_frame_free(&frame);

    /* H274 lower subsampling OK (grain sub 0,0 < YUV420P sub 1,1) */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_H274, 0, 0, 0, 0, 0, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("H274 lower sub: %s\n", sel ? "OK" : "FAIL");
    av_frame_free(&frame);

    /* H274 higher subsampling FAIL (grain sub 1,1 > YUV444P sub 0,0) */
    frame = create_frame(AV_PIX_FMT_YUV444P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_H274, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("H274 higher sub: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* width too large */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 3840, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("width too large: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* height too large */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 2160, 1, 1, 0, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("height too large: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* width/height = 0 (unspecified) - passes */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("size unspecified: %s\n", sel ? "OK" : "FAIL");
    av_frame_free(&frame);

    /* bit_depth_luma mismatch (grain=10, YUV420P=8) */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 10, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("bd_luma mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* bit_depth_chroma mismatch (grain=10, YUV420P=8) */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 10);
    sel = av_film_grain_params_select(frame);
    म_लिखो("bd_chroma mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* bit_depth = 0 (unspecified) - passes */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("bd unspecified: %s\n", sel ? "OK" : "FAIL");
    av_frame_free(&frame);

    /* bit_depth exact match (grain=8, YUV420P=8) */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 8, 8);
    sel = av_film_grain_params_select(frame);
    म_लिखो("bd exact match: %s\n", sel ? "OK" : "FAIL");
    av_frame_free(&frame);

    /* color_range mismatch */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    frame->color_range = AVCOL_RANGE_MPEG;
    fgp = add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_range = AVCOL_RANGE_JPEG;
    sel = av_film_grain_params_select(frame);
    म_लिखो("color_range mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* color_primaries mismatch */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    frame->color_primaries = AVCOL_PRI_BT709;
    fgp = add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_primaries = AVCOL_PRI_BT470M;
    sel = av_film_grain_params_select(frame);
    म_लिखो("color_primaries mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* color_trc mismatch */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    frame->color_trc = AVCOL_TRC_BT709;
    fgp = add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_trc = AVCOL_TRC_GAMMA22;
    sel = av_film_grain_params_select(frame);
    म_लिखो("color_trc mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* color_space mismatch */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    frame->colorspace = AVCOL_SPC_BT709;
    fgp = add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_space = AVCOL_SPC_BT470BG;
    sel = av_film_grain_params_select(frame);
    म_लिखो("color_space mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_frame_free(&frame);

    /* color properties UNSPECIFIED - passes */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("color unspecified: %s\n", sel ? "OK" : "FAIL");
    av_frame_free(&frame);

    /* multiple entries - best selection by size */
    frame = create_frame(AV_PIX_FMT_YUV420P, 1920, 1080);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 640,  480,  1, 1, 0, 0);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 1280, 720,  1, 1, 0, 0);
    add_grain(frame, AV_FILM_GRAIN_PARAMS_AV1, 1000, 1080, 1, 1, 0, 0);
    sel = av_film_grain_params_select(frame);
    म_लिखो("best selection: width=%d height=%d\n",
           sel ? sel->width : -1, sel ? sel->height : -1);
    av_frame_free(&frame);

    परत 0;
}
