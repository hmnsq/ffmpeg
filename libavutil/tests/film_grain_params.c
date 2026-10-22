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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/film_grain_params.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"

ਸਥਿਰ AVFrame *create_ਚੌਖਟਾ(ਗਿਣਤੀ AVPixelFormat format, ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ)
{
    AVFrame *ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!ਚੌਖਟਾ)
        ਵਾਪਸ ਨਿਰਾ;
    ਚੌਖਟਾ->format = format;
    ਚੌਖਟਾ->ਚੌੜਾਈ  = ਚੌੜਾਈ;
    ਚੌਖਟਾ->ਉਚਾਈ = ਉਚਾਈ;
    ਵਾਪਸ ਚੌਖਟਾ;
}

ਸਥਿਰ AVFilmGrainParams *ਜੋੜੋ_grain(AVFrame *ਚੌਖਟਾ,
                                     ਗਿਣਤੀ AVFilmGrainParamsType type,
                                     ਪੂਰਨ ਚੌੜਾਈ, ਪੂਰਨ ਉਚਾਈ,
                                     ਪੂਰਨ sub_x, ਪੂਰਨ sub_y,
                                     ਪੂਰਨ bd_luma, ਪੂਰਨ bd_chroma)
{
    AVFilmGrainParams *fgp = av_film_grain_params_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
    ਜੇ (!fgp)
        ਵਾਪਸ ਨਿਰਾ;
    fgp->type             = type;
    fgp->ਚੌੜਾਈ            = ਚੌੜਾਈ;
    fgp->ਉਚਾਈ           = ਉਚਾਈ;
    fgp->subsampling_x    = sub_x;
    fgp->subsampling_y    = sub_y;
    fgp->ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_luma   = bd_luma;
    fgp->ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_chroma = bd_chroma;
    ਵਾਪਸ fgp;
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVFilmGrainParams *fgp;
    ਅਚਲ AVFilmGrainParams *sel;
    AVFrame *ਚੌਖਟਾ;
    size_t ਮਾਪ;

    ਲਿਖੋ("Testing av_film_grain_params_alloc()\n");

    fgp = av_film_grain_params_alloc(&ਮਾਪ);
    ਲਿਖੋ("alloc with size: %s\n", (fgp && ਮਾਪ > 0) ? "OK" : "FAIL");
    av_free(fgp);

    fgp = av_film_grain_params_alloc(ਨਿਰਾ);
    ਲਿਖੋ("alloc without size: %s\n", fgp ? "OK" : "FAIL");
    av_free(fgp);

    ਲਿਖੋ("\nTesting av_film_grain_params_create_side_data()\n");

    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    fgp = av_film_grain_params_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
    ਜੇ (fgp)
        ਲਿਖੋ("create: OK\ndefaults: range=%d pri=%d trc=%d space=%d\n",
               fgp->color_range, fgp->color_primaries,
               fgp->color_trc, fgp->color_space);
    ਨਹੀਂਤਾਂ
        ਲਿਖੋ("create: FAIL\n");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    ਲਿਖੋ("\nTesting av_film_grain_params_select()\n");

    /* invalid format */
    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਚੌਖਟਾ->format = -1;
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("invalid format: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* no side data */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("no side data: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* NONE type - skipped */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_NONE, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("NONE type: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* AV1 exact subsampling match (YUV420P: sub 1,1) */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("AV1 match: %s\n", sel ? "OK" : "FAIL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* AV1 subsampling mismatch */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 0, 0, 0, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("AV1 sub mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* H274 exact match */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_H274, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("H274 match: %s\n", sel ? "OK" : "FAIL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* H274 lower subsampling OK (grain sub 0,0 < YUV420P sub 1,1) */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_H274, 0, 0, 0, 0, 0, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("H274 lower sub: %s\n", sel ? "OK" : "FAIL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* H274 higher subsampling FAIL (grain sub 1,1 > YUV444P sub 0,0) */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV444P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_H274, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("H274 higher sub: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* width too large */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 3840, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("width too large: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* height too large */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 2160, 1, 1, 0, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("height too large: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* width/height = 0 (unspecified) - passes */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("size unspecified: %s\n", sel ? "OK" : "FAIL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* bit_depth_luma mismatch (grain=10, YUV420P=8) */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 10, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("bd_luma mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* bit_depth_chroma mismatch (grain=10, YUV420P=8) */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 10);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("bd_chroma mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* bit_depth = 0 (unspecified) - passes */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("bd unspecified: %s\n", sel ? "OK" : "FAIL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* bit_depth exact match (grain=8, YUV420P=8) */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 8, 8);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("bd exact match: %s\n", sel ? "OK" : "FAIL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* color_range mismatch */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਚੌਖਟਾ->color_range = AVCOL_RANGE_MPEG;
    fgp = ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_range = AVCOL_RANGE_JPEG;
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("color_range mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* color_primaries mismatch */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਚੌਖਟਾ->color_primaries = AVCOL_PRI_BT709;
    fgp = ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_primaries = AVCOL_PRI_BT470M;
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("color_primaries mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* color_trc mismatch */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਚੌਖਟਾ->color_trc = AVCOL_TRC_BT709;
    fgp = ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_trc = AVCOL_TRC_GAMMA22;
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("color_trc mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* color_space mismatch */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਚੌਖਟਾ->colorspace = AVCOL_SPC_BT709;
    fgp = ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    fgp->color_space = AVCOL_SPC_BT470BG;
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("color_space mismatch: %s\n", sel ? "FAIL" : "NULL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* color properties UNSPECIFIED - passes */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 0, 0, 1, 1, 0, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("color unspecified: %s\n", sel ? "OK" : "FAIL");
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    /* multiple entries - best selection by size */
    ਚੌਖਟਾ = create_ਚੌਖਟਾ(AV_PIX_FMT_YUV420P, 1920, 1080);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 640,  480,  1, 1, 0, 0);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 1280, 720,  1, 1, 0, 0);
    ਜੋੜੋ_grain(ਚੌਖਟਾ, AV_FILM_GRAIN_PARAMS_AV1, 1000, 1080, 1, 1, 0, 0);
    sel = av_film_grain_params_select(ਚੌਖਟਾ);
    ਲਿਖੋ("best selection: width=%d height=%d\n",
           sel ? sel->ਚੌੜਾਈ : -1, sel ? sel->ਉਚਾਈ : -1);
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);

    ਵਾਪਸ 0;
}
