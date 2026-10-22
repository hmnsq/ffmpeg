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

#ضمن <stdio.h>

#ضمن "libavutil/film_grain_params.h"
#ضمن "libavutil/mem.h"

ساكن AVFrame *create_قاب(تعداد AVPixelFormat format, صحيح عرض, صحيح ارتفاع)
{
    AVFrame *قاب = av_قاب_alloc();
    إذا (!قاب)
        أرجع عدم;
    قاب->format = format;
    قاب->عرض  = عرض;
    قاب->ارتفاع = ارتفاع;
    أرجع قاب;
}

ساكن AVFilmGrainParams *جمع_کن_grain(AVFrame *قاب,
                                     تعداد AVFilmGrainParamsType type,
                                     صحيح عرض, صحيح ارتفاع,
                                     صحيح sub_x, صحيح sub_y,
                                     صحيح bd_luma, صحيح bd_chroma)
{
    AVFilmGrainParams *fgp = av_film_grain_params_create_side_داده(قاب);
    إذا (!fgp)
        أرجع عدم;
    fgp->type             = type;
    fgp->عرض            = عرض;
    fgp->ارتفاع           = ارتفاع;
    fgp->subsampling_x    = sub_x;
    fgp->subsampling_y    = sub_y;
    fgp->بیت_عمق_luma   = bd_luma;
    fgp->بیت_عمق_chroma = bd_chroma;
    أرجع fgp;
}

صحيح اصلی(فراغ)
{
    AVFilmGrainParams *fgp;
    ثابت AVFilmGrainParams *sel;
    AVFrame *قاب;
    size_t اندازه;

    چاپ_کن("Testing av_film_grain_params_alloc()\n");

    fgp = av_film_grain_params_alloc(&اندازه);
    چاپ_کن("alloc with size: %s\n", (fgp && اندازه > 0) ? "OK" : "FAIL");
    av_free(fgp);

    fgp = av_film_grain_params_alloc(عدم);
    چاپ_کن("alloc without size: %s\n", fgp ? "OK" : "FAIL");
    av_free(fgp);

    چاپ_کن("\nTesting av_film_grain_params_create_side_data()\n");

    قاب = av_قاب_alloc();
    fgp = av_film_grain_params_create_side_داده(قاب);
    إذا (fgp)
        چاپ_کن("create: OK\ndefaults: range=%d pri=%d trc=%d space=%d\n",
               fgp->color_range, fgp->color_primaries,
               fgp->color_trc, fgp->color_space);
    وإلا
        چاپ_کن("create: FAIL\n");
    av_قاب_free(&قاب);

    چاپ_کن("\nTesting av_film_grain_params_select()\n");

    /* invalid format */
    قاب = av_قاب_alloc();
    قاب->format = -1;
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("invalid format: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* no side data */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("no side data: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* NONE type - skipped */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_NONE, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("NONE type: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* AV1 exact subsampling match (YUV420P: sub 1,1) */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("AV1 match: %s\n", sel ? "OK" : "FAIL");
    av_قاب_free(&قاب);

    /* AV1 subsampling mismatch */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 0, 0, 0, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("AV1 sub mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* H274 exact match */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_H274, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("H274 match: %s\n", sel ? "OK" : "FAIL");
    av_قاب_free(&قاب);

    /* H274 lower subsampling OK (grain sub 0,0 < YUV420P sub 1,1) */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_H274, 0, 0, 0, 0, 0, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("H274 lower sub: %s\n", sel ? "OK" : "FAIL");
    av_قاب_free(&قاب);

    /* H274 higher subsampling FAIL (grain sub 1,1 > YUV444P sub 0,0) */
    قاب = create_قاب(AV_PIX_FMT_YUV444P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_H274, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("H274 higher sub: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* width too large */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 3840, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("width too large: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* height too large */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 2160, 1, 1, 0, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("height too large: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* width/height = 0 (unspecified) - passes */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("size unspecified: %s\n", sel ? "OK" : "FAIL");
    av_قاب_free(&قاب);

    /* bit_depth_luma mismatch (grain=10, YUV420P=8) */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 10, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("bd_luma mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* bit_depth_chroma mismatch (grain=10, YUV420P=8) */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 10);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("bd_chroma mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* bit_depth = 0 (unspecified) - passes */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("bd unspecified: %s\n", sel ? "OK" : "FAIL");
    av_قاب_free(&قاب);

    /* bit_depth exact match (grain=8, YUV420P=8) */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 8, 8);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("bd exact match: %s\n", sel ? "OK" : "FAIL");
    av_قاب_free(&قاب);

    /* color_range mismatch */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    قاب->color_range = AVCOL_RANGE_MPEG;
    fgp = جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_range = AVCOL_RANGE_JPEG;
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("color_range mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* color_primaries mismatch */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    قاب->color_primaries = AVCOL_PRI_BT709;
    fgp = جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_primaries = AVCOL_PRI_BT470M;
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("color_primaries mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* color_trc mismatch */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    قاب->color_trc = AVCOL_TRC_BT709;
    fgp = جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_trc = AVCOL_TRC_GAMMA22;
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("color_trc mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* color_space mismatch */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    قاب->colorspace = AVCOL_SPC_BT709;
    fgp = جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_space = AVCOL_SPC_BT470BG;
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("color_space mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_قاب_free(&قاب);

    /* color properties UNSPECIFIED - passes */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("color unspecified: %s\n", sel ? "OK" : "FAIL");
    av_قاب_free(&قاب);

    /* multiple entries - best selection by size */
    قاب = create_قاب(AV_PIX_FMT_YUV420P, 1920, 1080);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 640,  480,  1, 1, 0, 0);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 1280, 720,  1, 1, 0, 0);
    جمع_کن_grain(قاب, AV_FILM_GRAIN_PARAMS_AV1, 1000, 1080, 1, 1, 0, 0);
    sel = av_film_grain_params_select(قاب);
    چاپ_کن("best selection: width=%d height=%d\n",
           sel ? sel->عرض : -1, sel ? sel->ارتفاع : -1);
    av_قاب_free(&قاب);

    أرجع 0;
}
