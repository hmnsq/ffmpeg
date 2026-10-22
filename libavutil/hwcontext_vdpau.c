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

#అన్తర్భావ "config.h"

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ <vdpau/vdpau.h>

#అన్తర్భావ "buffer.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "hwcontext_vdpau.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pixfmt.h"
#అన్తర్భావ "pixdesc.h"

రకనిర్వచనం నిర్మాణం VDPAUPixFmtMap {
    VdpYCbCrFormat vdpau_fmt;
    గణన AVPixelFormat pix_fmt;
} VDPAUPixFmtMap;

స్థిర స్థిరరాశి VDPAUPixFmtMap pix_fmts_420[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV12    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV420P },
#నిర్వచితమైతే VDP_YCBCR_FORMAT_P016
    { VDP_YCBCR_FORMAT_P016, AV_PIX_FMT_P016    },
    { VDP_YCBCR_FORMAT_P010, AV_PIX_FMT_P010    },
#అయితే_ముగింపు
    { 0,                     AV_PIX_FMT_NONE,   },
};

స్థిర స్థిరరాశి VDPAUPixFmtMap pix_fmts_422[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV16    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV422P },
    { VDP_YCBCR_FORMAT_UYVY, AV_PIX_FMT_UYVY422 },
    { VDP_YCBCR_FORMAT_YUYV, AV_PIX_FMT_YUYV422 },
    { 0,                     AV_PIX_FMT_NONE,   },
};

స్థిర స్థిరరాశి VDPAUPixFmtMap pix_fmts_444[] = {
#నిర్వచితమైతే VDP_YCBCR_FORMAT_Y_U_V_444
    { VDP_YCBCR_FORMAT_Y_U_V_444, AV_PIX_FMT_YUV444P },
#అయితే_ముగింపు
#నిర్వచితమైతే VDP_YCBCR_FORMAT_P016
    {VDP_YCBCR_FORMAT_Y_U_V_444_16, AV_PIX_FMT_YUV444P16},
#అయితే_ముగింపు
    { 0,                          AV_PIX_FMT_NONE,   },
};

స్థిర స్థిరరాశి నిర్మాణం {
    VdpChromaType chroma_type;
    గణన AVPixelFormat చట్రాలు_sw_format;
    స్థిరరాశి VDPAUPixFmtMap *map;
} vdpau_pix_fmts[] = {
    { VDP_CHROMA_TYPE_420, AV_PIX_FMT_YUV420P, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422, AV_PIX_FMT_YUV422P, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444, AV_PIX_FMT_YUV444P, pix_fmts_444 },
#నిర్వచితమైతే VDP_YCBCR_FORMAT_P016
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P10, pix_fmts_420 },
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P12, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422_16, AV_PIX_FMT_YUV422P10, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P10, pix_fmts_444 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P12, pix_fmts_444 },
#అయితే_ముగింపు
};

రకనిర్వచనం నిర్మాణం VDPAUDeviceContext {
    /**
     * The public AVVDPAUDeviceContext. See hwcontext_vdpau.h for it.
     */
    AVVDPAUDeviceContext p;

    Vdp_Video_Surface_Query_Get_Put_బిట్లు_YCb_Cr_Capabilities *get_transfer_caps;
    Vdp_Video_Surface_Get_బిట్లు_YCb_Cr                     *get_దత్తాంశం;
    Vdp_Video_Surface_Put_బిట్లు_YCb_Cr                     *put_దత్తాంశం;
    VdpVideoSurfaceCreate                           *surf_create;
    VdpVideoSurfaceDestroy                          *surf_destroy;

    గణన AVPixelFormat *pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
    పూర్ణాంకం              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

రకనిర్వచనం నిర్మాణం VDPAUFramesContext {
    Vdp_Video_Surface_Get_బిట్లు_YCb_Cr *get_దత్తాంశం;
    Vdp_Video_Surface_Put_బిట్లు_YCb_Cr *put_దత్తాంశం;
    VdpChromaType chroma_type;
    పూర్ణాంకం chroma_idx;

    స్థిరరాశి గణన AVPixelFormat *pix_fmts;
    పూర్ణాంకం                       nb_pix_fmts;
} VDPAUFramesContext;

స్థిర పూర్ణాంకం లెక్క_pixfmts(స్థిరరాశి VDPAUPixFmtMap *map)
{
    పూర్ణాంకం లెక్క = 0;
    అయితే (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        లెక్క++;
    }
    తిరిగి లెక్క;
}

స్థిర పూర్ణాంకం vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    పూర్ణాంకం i;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        స్థిరరాశి VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        పూర్ణాంకం nb_pix_fmts;

        nb_pix_fmts = లెక్క_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, పరిమాణం(*priv->pix_fmts[i]));
        ఒకవేళ (!priv->pix_fmts[i])
            తిరిగి AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        అయితే (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            Vdp_స్థితి err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            ఒకవేళ (err == VDP_స్థితి_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    తిరిగి 0;
}

#నిర్వచించు GET_CALLBACK(id, ఫలితం)                                                \
చేయి {                                                                            \
    శూన్య *tmp;                                                                  \
    err = hwctx->get_proc_చిరునామా(hwctx->device, id, &tmp);                     \
    ఒకవేళ (err != VDP_స్థితి_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        తిరిగి AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    ఫలితం = tmp;                                                               \
} అయితే (0)

స్థిర పూర్ణాంకం vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    Vdp_స్థితి             err;
    పూర్ణాంకం                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_బిట్లు_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_బిట్లు_Y_CB_CR, priv->get_దత్తాంశం);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_బిట్లు_Y_CB_CR, priv->put_దత్తాంశం);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    ఒకవేళ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        తిరిగి ret;
    }

    తిరిగి 0;
}

స్థిర శూన్య vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    పూర్ణాంకం i;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

స్థిర పూర్ణాంకం vdpau_చట్రాలు_get_constraints(AVHWDeviceContext *ctx,
                                        స్థిరరాశి శూన్య *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    పూర్ణాంకం nb_sw_formats = 0;
    పూర్ణాంకం i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    పరిమాణం(*constraints->valid_sw_formats));
    ఒకవేళ (!constraints->valid_sw_formats)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        ఒకవేళ (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].చట్రాలు_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, పరిమాణం(*constraints->valid_hw_formats));
    ఒకవేళ (!constraints->valid_hw_formats)
        తిరిగి AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    తిరిగి 0;
}

స్థిర శూన్య vdpau_బఫరు_free(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)దత్తాంశం;

    device_priv->surf_destroy(surf);
}

స్థిర AVBufferRef *vdpau_pool_alloc(శూన్య *opaque, size_t కొలత)
{
    AVHWFramesContext             *ctx = opaque;
    VDPAUFramesContext           *priv = ctx->hwctx;
    VDPAUDeviceContext    *device_priv = ctx->device_ctx->hwctx;
    AVVDPAUDeviceContext *device_hwctx = &device_priv->p;

    AVBufferRef *ret;
    VdpVideoSurface surf;
    Vdp_స్థితి err;

    err = device_priv->surf_create(device_hwctx->device, priv->chroma_type,
                                   ctx->వెడల్పు, ctx->ఎత్తు, &surf);
    ఒకవేళ (err != VDP_స్థితి_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        తిరిగి ఖాళీ;
    }

    ret = av_బఫరు_create((uint8_t*)(uintptr_t)surf, పరిమాణం(surf),
                           vdpau_బఫరు_free, ctx, AV_బఫరు_FLAG_READONLY);
    ఒకవేళ (!ret) {
        device_priv->surf_destroy(surf);
        తిరిగి ఖాళీ;
    }

    తిరిగి ret;
}

స్థిర పూర్ణాంకం vdpau_చట్రాలు_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    పూర్ణాంకం i;

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        ఒకవేళ (vdpau_pix_fmts[i].చట్రాలు_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            ఆపు;
        }
    }
    ఒకవేళ (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        తిరిగి AVERROR(ENOSYS);
    }

    ఒకవేళ (!ctx->pool) {
        ffhwframesctx(ctx)->pool_అంతర్గత =
            av_బఫరు_pool_init2(పరిమాణం(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, ఖాళీ);
        ఒకవేళ (!ffhwframesctx(ctx)->pool_అంతర్గత)
            తిరిగి AVERROR(ENOMEM);
    }

    priv->get_దత్తాంశం = device_priv->get_దత్తాంశం;
    priv->put_దత్తాంశం = device_priv->put_దత్తాంశం;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vdpau_get_బఫరు(AVHWFramesContext *ctx, AVFrame *చట్రం)
{
    చట్రం->buf[0] = av_బఫరు_pool_get(ctx->pool);
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి AVERROR(ENOMEM);

    చట్రం->దత్తాంశం[3] = చట్రం->buf[0]->దత్తాంశం;
    చట్రం->format  = AV_PIX_FMT_VDPAU;
    చట్రం->వెడల్పు   = ctx->వెడల్పు;
    చట్రం->ఎత్తు  = ctx->ఎత్తు;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      గణన AVHWFrameTransferDirection dir,
                                      గణన AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    గణన AVPixelFormat *fmts;

    ఒకవేళ (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        తిరిగి AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, పరిమాణం(*fmts));
    ఒకవేళ (!fmts)
        తిరిగి AVERROR(ENOMEM);

    జ్ఞాపకం_నకలు(fmts, priv->pix_fmts, పరిమాణం(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vdpau_transfer_దత్తాంశం_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    స్థిరరాశి AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->దత్తాంశం[3];

    శూన్య *దత్తాంశం[3];
    uint32_t linesize[3];

    స్థిరరాశి VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    Vdp_స్థితి err;
    పూర్ణాంకం i;

    కొరకు (i = 0; i< FF_ARRAY_ELEMS(దత్తాంశం) && dst->దత్తాంశం[i]; i++) {
        దత్తాంశం[i] = dst->దత్తాంశం[i];
        ఒకవేళ (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            తిరిగి AVERROR(ERANGE);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    కొరకు (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        ఒకవేళ (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            ఆపు;
        }
    }
    ఒకవేళ (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        తిరిగి AVERROR(EINVAL);
    }

    ఒకవేళ ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#నిర్వచితమైతే VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#అయితే_ముగింపు
#నిర్వచితమైతే VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#అయితే_ముగింపు
            )
        FFSWAP(శూన్య*, దత్తాంశం[1], దత్తాంశం[2]);

    err = priv->get_దత్తాంశం(surf, vdpau_format, దత్తాంశం, linesize);
    ఒకవేళ (err != VDP_స్థితి_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం vdpau_transfer_దత్తాంశం_గమ్యం(AVHWFramesContext *ctx, AVFrame *dst,
                                  స్థిరరాశి AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->దత్తాంశం[3];

    స్థిరరాశి శూన్య *దత్తాంశం[3];
    uint32_t linesize[3];

    స్థిరరాశి VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    Vdp_స్థితి err;
    పూర్ణాంకం i;

    కొరకు (i = 0; i< FF_ARRAY_ELEMS(దత్తాంశం) && src->దత్తాంశం[i]; i++) {
        దత్తాంశం[i] = src->దత్తాంశం[i];
        ఒకవేళ (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            తిరిగి AVERROR(ERANGE);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    కొరకు (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        ఒకవేళ (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            ఆపు;
        }
    }
    ఒకవేళ (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        తిరిగి AVERROR(EINVAL);
    }

    ఒకవేళ ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#నిర్వచితమైతే VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#అయితే_ముగింపు
            )
        FFSWAP(స్థిరరాశి శూన్య*, దత్తాంశం[1], దత్తాంశం[2]);

    err = priv->put_దత్తాంశం(surf, vdpau_format, దత్తాంశం, linesize);
    ఒకవేళ (err != VDP_స్థితి_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    తిరిగి 0;
}

#ఒకవేళ HAVE_VDPAU_X11
#అన్తర్భావ <vdpau/vdpau_x11.h>
#అన్తర్భావ <X11/Xlib.h>

రకనిర్వచనం నిర్మాణం VDPAUDevicePriv {
    VdpDeviceDestroy *device_destroy;
    Display *dpy;
} VDPAUDevicePriv;

స్థిర శూన్య vdpau_device_free(AVHWDeviceContext *ctx)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;
    VDPAUDevicePriv       *priv = ctx->user_opaque;

    ఒకవేళ (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    ఒకవేళ (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

స్థిర పూర్ణాంకం vdpau_device_create(AVHWDeviceContext *ctx, స్థిరరాశి అక్షరం *device,
                               AVDictionary *opts, పూర్ణాంకం flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    Vdp_స్థితి err;
    VdpGetInformationString *get_information_string;
    స్థిరరాశి అక్షరం *display, *vendor;

    priv = av_mallocz(పరిమాణం(*priv));
    ఒకవేళ (!priv)
        తిరిగి AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->విడుదల        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    ఒకవేళ (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        తిరిగి AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_చిరునామా);
    ఒకవేళ (err != VDP_స్థితి_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        తిరిగి AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    తిరిగి 0;
}
#అయితే_ముగింపు

స్థిరరాశి HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_కొలత    = పరిమాణం(VDPAUDeviceContext),
    .చట్రాలు_hwctx_కొలత    = పరిమాణం(VDPAUFramesContext),

#ఒకవేళ HAVE_VDPAU_X11
    .device_create        = vdpau_device_create,
#అయితే_ముగింపు
    .device_init          = vdpau_device_init,
    .device_uninit        = vdpau_device_uninit,
    .చట్రాలు_get_constraints = vdpau_చట్రాలు_get_constraints,
    .చట్రాలు_init          = vdpau_చట్రాలు_init,
    .చట్రాలు_get_బఫరు    = vdpau_get_బఫరు,
    .transfer_get_formats = vdpau_transfer_get_formats,
    .transfer_దత్తాంశం_గమ్యం     = vdpau_transfer_దత్తాంశం_గమ్యం,
    .transfer_దత్తాంశం_from   = vdpau_transfer_దత్తాంశం_from,

    .pix_fmts = (స్థిరరాశి గణన AVPixelFormat[]){ AV_PIX_FMT_VDPAU, AV_PIX_FMT_NONE },
};
