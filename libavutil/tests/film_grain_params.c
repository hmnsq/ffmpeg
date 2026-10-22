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

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/film_grain_params.h"
#అన్తర్భావ "libavutil/mem.h"

స్థిర AVFrame *create_చట్రం(గణన AVPixelFormat format, పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు)
{
    AVFrame *చట్రం = av_చట్రం_alloc();
    ఒకవేళ (!చట్రం)
        తిరిగి ఖాళీ;
    చట్రం->format = format;
    చట్రం->వెడల్పు  = వెడల్పు;
    చట్రం->ఎత్తు = ఎత్తు;
    తిరిగి చట్రం;
}

స్థిర AVFilmGrainParams *కూడు_grain(AVFrame *చట్రం,
                                     గణన AVFilmGrainParamsType type,
                                     పూర్ణాంకం వెడల్పు, పూర్ణాంకం ఎత్తు,
                                     పూర్ణాంకం sub_x, పూర్ణాంకం sub_y,
                                     పూర్ణాంకం bd_luma, పూర్ణాంకం bd_chroma)
{
    AVFilmGrainParams *fgp = av_film_grain_params_create_side_దత్తాంశం(చట్రం);
    ఒకవేళ (!fgp)
        తిరిగి ఖాళీ;
    fgp->type             = type;
    fgp->వెడల్పు            = వెడల్పు;
    fgp->ఎత్తు           = ఎత్తు;
    fgp->subsampling_x    = sub_x;
    fgp->subsampling_y    = sub_y;
    fgp->బిట్టు_లోతు_luma   = bd_luma;
    fgp->బిట్టు_లోతు_chroma = bd_chroma;
    తిరిగి fgp;
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVFilmGrainParams *fgp;
    స్థిరరాశి AVFilmGrainParams *sel;
    AVFrame *చట్రం;
    size_t కొలత;

    రాయి("Testing av_film_grain_params_alloc()\n");

    fgp = av_film_grain_params_alloc(&కొలత);
    రాయి("alloc with size: %s\n", (fgp && కొలత > 0) ? "OK" : "FAIL");
    av_free(fgp);

    fgp = av_film_grain_params_alloc(ఖాళీ);
    రాయి("alloc without size: %s\n", fgp ? "OK" : "FAIL");
    av_free(fgp);

    రాయి("\nTesting av_film_grain_params_create_side_data()\n");

    చట్రం = av_చట్రం_alloc();
    fgp = av_film_grain_params_create_side_దత్తాంశం(చట్రం);
    ఒకవేళ (fgp)
        రాయి("create: OK\ndefaults: range=%d pri=%d trc=%d space=%d\n",
               fgp->color_range, fgp->color_primaries,
               fgp->color_trc, fgp->color_space);
    లేకపోతే
        రాయి("create: FAIL\n");
    av_చట్రం_free(&చట్రం);

    రాయి("\nTesting av_film_grain_params_select()\n");

    /* invalid format */
    చట్రం = av_చట్రం_alloc();
    చట్రం->format = -1;
    sel = av_film_grain_params_select(చట్రం);
    రాయి("invalid format: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* no side data */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("no side data: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* NONE type - skipped */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_NONE, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("NONE type: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* AV1 exact subsampling match (YUV420P: sub 1,1) */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("AV1 match: %s\n", sel ? "OK" : "FAIL");
    av_చట్రం_free(&చట్రం);

    /* AV1 subsampling mismatch */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 0, 0, 0, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("AV1 sub mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* H274 exact match */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_H274, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("H274 match: %s\n", sel ? "OK" : "FAIL");
    av_చట్రం_free(&చట్రం);

    /* H274 lower subsampling OK (grain sub 0,0 < YUV420P sub 1,1) */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_H274, 0, 0, 0, 0, 0, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("H274 lower sub: %s\n", sel ? "OK" : "FAIL");
    av_చట్రం_free(&చట్రం);

    /* H274 higher subsampling FAIL (grain sub 1,1 > YUV444P sub 0,0) */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV444P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_H274, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("H274 higher sub: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* width too large */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 3840, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("width too large: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* height too large */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 2160, 1, 1, 0, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("height too large: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* width/height = 0 (unspecified) - passes */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("size unspecified: %s\n", sel ? "OK" : "FAIL");
    av_చట్రం_free(&చట్రం);

    /* bit_depth_luma mismatch (grain=10, YUV420P=8) */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 10, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("bd_luma mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* bit_depth_chroma mismatch (grain=10, YUV420P=8) */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 10);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("bd_chroma mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* bit_depth = 0 (unspecified) - passes */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("bd unspecified: %s\n", sel ? "OK" : "FAIL");
    av_చట్రం_free(&చట్రం);

    /* bit_depth exact match (grain=8, YUV420P=8) */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 8, 8);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("bd exact match: %s\n", sel ? "OK" : "FAIL");
    av_చట్రం_free(&చట్రం);

    /* color_range mismatch */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    చట్రం->color_range = AVCOL_RANGE_MPEG;
    fgp = కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_range = AVCOL_RANGE_JPEG;
    sel = av_film_grain_params_select(చట్రం);
    రాయి("color_range mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* color_primaries mismatch */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    చట్రం->color_primaries = AVCOL_PRI_BT709;
    fgp = కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_primaries = AVCOL_PRI_BT470M;
    sel = av_film_grain_params_select(చట్రం);
    రాయి("color_primaries mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* color_trc mismatch */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    చట్రం->color_trc = AVCOL_TRC_BT709;
    fgp = కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_trc = AVCOL_TRC_GAMMA22;
    sel = av_film_grain_params_select(చట్రం);
    రాయి("color_trc mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* color_space mismatch */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    చట్రం->colorspace = AVCOL_SPC_BT709;
    fgp = కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_space = AVCOL_SPC_BT470BG;
    sel = av_film_grain_params_select(చట్రం);
    రాయి("color_space mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_చట్రం_free(&చట్రం);

    /* color properties UNSPECIFIED - passes */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("color unspecified: %s\n", sel ? "OK" : "FAIL");
    av_చట్రం_free(&చట్రం);

    /* multiple entries - best selection by size */
    చట్రం = create_చట్రం(AV_PIX_FMT_YUV420P, 1920, 1080);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 640,  480,  1, 1, 0, 0);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 1280, 720,  1, 1, 0, 0);
    కూడు_grain(చట్రం, AV_FILM_GRAIN_PARAMS_AV1, 1000, 1080, 1, 1, 0, 0);
    sel = av_film_grain_params_select(చట్రం);
    రాయి("best selection: width=%d height=%d\n",
           sel ? sel->వెడల్పు : -1, sel ? sel->ఎత్తు : -1);
    av_చట్రం_free(&చట్రం);

    తిరిగి 0;
}
