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

#অন্তর্ভাব "config.h"

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব <vdpau/vdpau.h>

#অন্তর্ভাব "buffer.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "hwcontext_internal.h"
#অন্তর্ভাব "hwcontext_vdpau.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "pixfmt.h"
#অন্তর্ভাব "pixdesc.h"

প্রকারলেখ কাঠামো VDPAUPixFmtMap {
    VdpYCbCrFormat vdpau_fmt;
    গণনা AVPixelFormat pix_fmt;
} VDPAUPixFmtMap;

স্থির ধ্রুবক VDPAUPixFmtMap pix_fmts_420[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV12    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV420P },
#ifdef VDP_YCBCR_FORMAT_P016
    { VDP_YCBCR_FORMAT_P016, AV_PIX_FMT_P016    },
    { VDP_YCBCR_FORMAT_P010, AV_PIX_FMT_P010    },
#endif
    { 0,                     AV_PIX_FMT_NONE,   },
};

স্থির ধ্রুবক VDPAUPixFmtMap pix_fmts_422[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV16    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV422P },
    { VDP_YCBCR_FORMAT_UYVY, AV_PIX_FMT_UYVY422 },
    { VDP_YCBCR_FORMAT_YUYV, AV_PIX_FMT_YUYV422 },
    { 0,                     AV_PIX_FMT_NONE,   },
};

স্থির ধ্রুবক VDPAUPixFmtMap pix_fmts_444[] = {
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
    { VDP_YCBCR_FORMAT_Y_U_V_444, AV_PIX_FMT_YUV444P },
#endif
#ifdef VDP_YCBCR_FORMAT_P016
    {VDP_YCBCR_FORMAT_Y_U_V_444_16, AV_PIX_FMT_YUV444P16},
#endif
    { 0,                          AV_PIX_FMT_NONE,   },
};

স্থির ধ্রুবক কাঠামো {
    VdpChromaType chroma_type;
    গণনা AVPixelFormat frames_sw_format;
    ধ্রুবক VDPAUPixFmtMap *map;
} vdpau_pix_fmts[] = {
    { VDP_CHROMA_TYPE_420, AV_PIX_FMT_YUV420P, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422, AV_PIX_FMT_YUV422P, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444, AV_PIX_FMT_YUV444P, pix_fmts_444 },
#ifdef VDP_YCBCR_FORMAT_P016
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P10, pix_fmts_420 },
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P12, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422_16, AV_PIX_FMT_YUV422P10, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P10, pix_fmts_444 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P12, pix_fmts_444 },
#endif
};

প্রকারলেখ কাঠামো VDPAUDeviceContext {
    /**
     * The public AVVDPAUDeviceContext. See hwcontext_vdpau.h for it.
     */
    AVVDPAUDeviceContext p;

    VdpVideoSurfaceQueryGetPutBitsYCbCrCapabilities *get_transfer_caps;
    VdpVideoSurfaceGetBitsYCbCr                     *get_তথ্য;
    VdpVideoSurfacePutBitsYCbCr                     *put_তথ্য;
    VdpVideoSurfaceCreate                           *surf_create;
    VdpVideoSurfaceDestroy                          *surf_destroy;

    গণনা AVPixelFormat *pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
    পূর্ণসংখ্যা              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

প্রকারলেখ কাঠামো VDPAUFramesContext {
    VdpVideoSurfaceGetBitsYCbCr *get_তথ্য;
    VdpVideoSurfacePutBitsYCbCr *put_তথ্য;
    VdpChromaType chroma_type;
    পূর্ণসংখ্যা chroma_idx;

    ধ্রুবক গণনা AVPixelFormat *pix_fmts;
    পূর্ণসংখ্যা                       nb_pix_fmts;
} VDPAUFramesContext;

স্থির পূর্ণসংখ্যা গুনতি_pixfmts(ধ্রুবক VDPAUPixFmtMap *map)
{
    পূর্ণসংখ্যা গুনতি = 0;
    যখন (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        গুনতি++;
    }
    ফেরত গুনতি;
}

স্থির পূর্ণসংখ্যা vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        ধ্রুবক VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        পূর্ণসংখ্যা nb_pix_fmts;

        nb_pix_fmts = গুনতি_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, আকার(*priv->pix_fmts[i]));
        যদি (!priv->pix_fmts[i])
            ফেরত AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        যখন (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            VdpStatus err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            যদি (err == VDP_STATUS_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    ফেরত 0;
}

#define GET_CALLBACK(id, ফলাফল)                                                \
করো {                                                                            \
    শূন্য *tmp;                                                                  \
    err = hwctx->get_proc_address(hwctx->device, id, &tmp);                     \
    যদি (err != VDP_STATUS_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        ফেরত AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    ফলাফল = tmp;                                                               \
} যখন (0)

স্থির পূর্ণসংখ্যা vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    VdpStatus             err;
    পূর্ণসংখ্যা                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_BITS_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_BITS_Y_CB_CR, priv->get_তথ্য);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_BITS_Y_CB_CR, priv->put_তথ্য);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    যদি (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        ফেরত ret;
    }

    ফেরত 0;
}

স্থির শূন্য vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

স্থির পূর্ণসংখ্যা vdpau_frames_get_constraints(AVHWDeviceContext *ctx,
                                        ধ্রুবক শূন্য *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    পূর্ণসংখ্যা nb_sw_formats = 0;
    পূর্ণসংখ্যা i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    আকার(*constraints->valid_sw_formats));
    যদি (!constraints->valid_sw_formats)
        ফেরত AVERROR(ENOMEM);

    জন্য (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        যদি (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].frames_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, আকার(*constraints->valid_hw_formats));
    যদি (!constraints->valid_hw_formats)
        ফেরত AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ফেরত 0;
}

স্থির শূন্য vdpau_বাফার_free(শূন্য *opaque, uint8_t *তথ্য)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)তথ্য;

    device_priv->surf_destroy(surf);
}

স্থির AVBufferRef *vdpau_pool_alloc(শূন্য *opaque, size_t আকার_2)
{
    AVHWFramesContext             *ctx = opaque;
    VDPAUFramesContext           *priv = ctx->hwctx;
    VDPAUDeviceContext    *device_priv = ctx->device_ctx->hwctx;
    AVVDPAUDeviceContext *device_hwctx = &device_priv->p;

    AVBufferRef *ret;
    VdpVideoSurface surf;
    VdpStatus err;

    err = device_priv->surf_create(device_hwctx->device, priv->chroma_type,
                                   ctx->width, ctx->height, &surf);
    যদি (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        ফেরত ফাঁকা;
    }

    ret = av_বাফার_create((uint8_t*)(uintptr_t)surf, আকার(surf),
                           vdpau_বাফার_free, ctx, AV_বাফার_FLAG_READONLY);
    যদি (!ret) {
        device_priv->surf_destroy(surf);
        ফেরত ফাঁকা;
    }

    ফেরত ret;
}

স্থির পূর্ণসংখ্যা vdpau_frames_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    পূর্ণসংখ্যা i;

    জন্য (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        যদি (vdpau_pix_fmts[i].frames_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            বিরতি;
        }
    }
    যদি (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ফেরত AVERROR(ENOSYS);
    }

    যদি (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal =
            av_বাফার_pool_init2(আকার(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, ফাঁকা);
        যদি (!ffhwframesctx(ctx)->pool_internal)
            ফেরত AVERROR(ENOMEM);
    }

    priv->get_তথ্য = device_priv->get_তথ্য;
    priv->put_তথ্য = device_priv->put_তথ্য;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা vdpau_get_বাফার(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_বাফার_pool_get(ctx->pool);
    যদি (!frame->buf[0])
        ফেরত AVERROR(ENOMEM);

    frame->তথ্য[3] = frame->buf[0]->তথ্য;
    frame->format  = AV_PIX_FMT_VDPAU;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      গণনা AVHWFrameTransferDirection dir,
                                      গণনা AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    গণনা AVPixelFormat *fmts;

    যদি (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        ফেরত AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, আকার(*fmts));
    যদি (!fmts)
        ফেরত AVERROR(ENOMEM);

    memcpy(fmts, priv->pix_fmts, আকার(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা vdpau_transfer_তথ্য_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ধ্রুবক AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->তথ্য[3];

    শূন্য *তথ্য[3];
    uint32_t linesize[3];

    ধ্রুবক VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i< FF_ARRAY_ELEMS(তথ্য) && dst->তথ্য[i]; i++) {
        তথ্য[i] = dst->তথ্য[i];
        যদি (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            ফেরত AVERROR(ERANGE);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    জন্য (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        যদি (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            বিরতি;
        }
    }
    যদি (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        ফেরত AVERROR(EINVAL);
    }

    যদি ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
#ifdef VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#endif
            )
        FFSWAP(শূন্য*, তথ্য[1], তথ্য[2]);

    err = priv->get_তথ্য(surf, vdpau_format, তথ্য, linesize);
    যদি (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        ফেরত AVERROR_UNKNOWN;
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা vdpau_transfer_তথ্য_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  ধ্রুবক AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->তথ্য[3];

    ধ্রুবক শূন্য *তথ্য[3];
    uint32_t linesize[3];

    ধ্রুবক VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    পূর্ণসংখ্যা i;

    জন্য (i = 0; i< FF_ARRAY_ELEMS(তথ্য) && src->তথ্য[i]; i++) {
        তথ্য[i] = src->তথ্য[i];
        যদি (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            ফেরত AVERROR(ERANGE);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    জন্য (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        যদি (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            বিরতি;
        }
    }
    যদি (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        ফেরত AVERROR(EINVAL);
    }

    যদি ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
            )
        FFSWAP(ধ্রুবক শূন্য*, তথ্য[1], তথ্য[2]);

    err = priv->put_তথ্য(surf, vdpau_format, তথ্য, linesize);
    যদি (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        ফেরত AVERROR_UNKNOWN;
    }

    ফেরত 0;
}

#যদি HAVE_VDPAU_X11
#অন্তর্ভাব <vdpau/vdpau_x11.h>
#অন্তর্ভাব <X11/Xlib.h>

প্রকারলেখ কাঠামো VDPAUDevicePriv {
    VdpDeviceDestroy *device_destroy;
    Display *dpy;
} VDPAUDevicePriv;

স্থির শূন্য vdpau_device_free(AVHWDeviceContext *ctx)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;
    VDPAUDevicePriv       *priv = ctx->user_opaque;

    যদি (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    যদি (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

স্থির পূর্ণসংখ্যা vdpau_device_create(AVHWDeviceContext *ctx, ধ্রুবক অক্ষর *device,
                               AVDictionary *opts, পূর্ণসংখ্যা flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    VdpStatus err;
    VdpGetInformationString *get_information_string;
    ধ্রুবক অক্ষর *display, *vendor;

    priv = av_mallocz(আকার(*priv));
    যদি (!priv)
        ফেরত AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->মুক্ত        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    যদি (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        ফেরত AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_address);
    যদি (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        ফেরত AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    ফেরত 0;
}
#endif

ধ্রুবক HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_আকার    = আকার(VDPAUDeviceContext),
    .frames_hwctx_আকার    = আকার(VDPAUFramesContext),

#যদি HAVE_VDPAU_X11
    .device_create        = vdpau_device_create,
#endif
    .device_init          = vdpau_device_init,
    .device_uninit        = vdpau_device_uninit,
    .frames_get_constraints = vdpau_frames_get_constraints,
    .frames_init          = vdpau_frames_init,
    .frames_get_বাফার    = vdpau_get_বাফার,
    .transfer_get_formats = vdpau_transfer_get_formats,
    .transfer_তথ্য_to     = vdpau_transfer_তথ্য_to,
    .transfer_তথ্য_from   = vdpau_transfer_তথ্য_from,

    .pix_fmts = (ধ্রুবক গণনা AVPixelFormat[]){ AV_PIX_FMT_VDPAU, AV_PIX_FMT_NONE },
};
