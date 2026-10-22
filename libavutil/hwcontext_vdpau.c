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

#ضمن "config.h"

#ضمن <stdint.h>
#ضمن <string.h>

#ضمن <vdpau/vdpau.h>

#ضمن "buffer.h"
#ضمن "common.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_internal.h"
#ضمن "hwcontext_vdpau.h"
#ضمن "mem.h"
#ضمن "pixfmt.h"
#ضمن "pixdesc.h"

تعريفنوع بنية VDPAUPixFmtMap {
    VdpYCbCrFormat vdpau_fmt;
    تعداد AVPixelFormat pix_fmt;
} VDPAUPixFmtMap;

ساكن ثابت VDPAUPixFmtMap pix_fmts_420[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV12    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV420P },
#جيڪڏهن_وصف_ٿيل VDP_YCBCR_FORMAT_P016
    { VDP_YCBCR_FORMAT_P016, AV_PIX_FMT_P016    },
    { VDP_YCBCR_FORMAT_P010, AV_PIX_FMT_P010    },
#جيڪڏهن_پورو
    { 0,                     AV_PIX_FMT_NONE,   },
};

ساكن ثابت VDPAUPixFmtMap pix_fmts_422[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV16    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV422P },
    { VDP_YCBCR_FORMAT_UYVY, AV_PIX_FMT_UYVY422 },
    { VDP_YCBCR_FORMAT_YUYV, AV_PIX_FMT_YUYV422 },
    { 0,                     AV_PIX_FMT_NONE,   },
};

ساكن ثابت VDPAUPixFmtMap pix_fmts_444[] = {
#جيڪڏهن_وصف_ٿيل VDP_YCBCR_FORMAT_Y_U_V_444
    { VDP_YCBCR_FORMAT_Y_U_V_444, AV_PIX_FMT_YUV444P },
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VDP_YCBCR_FORMAT_P016
    {VDP_YCBCR_FORMAT_Y_U_V_444_16, AV_PIX_FMT_YUV444P16},
#جيڪڏهن_پورو
    { 0,                          AV_PIX_FMT_NONE,   },
};

ساكن ثابت بنية {
    VdpChromaType chroma_type;
    تعداد AVPixelFormat چوکٺا_sw_format;
    ثابت VDPAUPixFmtMap *map;
} vdpau_pix_fmts[] = {
    { VDP_CHROMA_TYPE_420, AV_PIX_FMT_YUV420P, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422, AV_PIX_FMT_YUV422P, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444, AV_PIX_FMT_YUV444P, pix_fmts_444 },
#جيڪڏهن_وصف_ٿيل VDP_YCBCR_FORMAT_P016
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P10, pix_fmts_420 },
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P12, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422_16, AV_PIX_FMT_YUV422P10, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P10, pix_fmts_444 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P12, pix_fmts_444 },
#جيڪڏهن_پورو
};

تعريفنوع بنية VDPAUDeviceContext {
    /**
     * The public AVVDPAUDeviceContext. See hwcontext_vdpau.h for it.
     */
    AVVDPAUDeviceContext p;

    Vdp_Video_Surface_Query_Get_Put_بٽ_YCb_Cr_Capabilities *get_transfer_caps;
    Vdp_Video_Surface_Get_بٽ_YCb_Cr                     *get_معلومات;
    Vdp_Video_Surface_Put_بٽ_YCb_Cr                     *put_معلومات;
    VdpVideoSurfaceCreate                           *surf_create;
    VdpVideoSurfaceDestroy                          *surf_destroy;

    تعداد AVPixelFormat *pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
    صحيح              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

تعريفنوع بنية VDPAUFramesContext {
    Vdp_Video_Surface_Get_بٽ_YCb_Cr *get_معلومات;
    Vdp_Video_Surface_Put_بٽ_YCb_Cr *put_معلومات;
    VdpChromaType chroma_type;
    صحيح chroma_idx;

    ثابت تعداد AVPixelFormat *pix_fmts;
    صحيح                       nb_pix_fmts;
} VDPAUFramesContext;

ساكن صحيح ڳڻپ_pixfmts(ثابت VDPAUPixFmtMap *map)
{
    صحيح ڳڻپ = 0;
    طالما (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        ڳڻپ++;
    }
    أرجع ڳڻپ;
}

ساكن صحيح vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        ثابت VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        صحيح nb_pix_fmts;

        nb_pix_fmts = ڳڻپ_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, حجم(*priv->pix_fmts[i]));
        إذا (!priv->pix_fmts[i])
            أرجع AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        طالما (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            Vdp_حالت err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            إذا (err == VDP_حالت_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    أرجع 0;
}

#وصف_ڪريو GET_CALLBACK(id, نتيجو)                                                \
افعل {                                                                            \
    فراغ *tmp;                                                                  \
    err = hwctx->get_proc_پتو(hwctx->device, id, &tmp);                     \
    إذا (err != VDP_حالت_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        أرجع AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    نتيجو = tmp;                                                               \
} طالما (0)

ساكن صحيح vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    Vdp_حالت             err;
    صحيح                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_بٽ_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_بٽ_Y_CB_CR, priv->get_معلومات);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_بٽ_Y_CB_CR, priv->put_معلومات);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    إذا (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        أرجع ret;
    }

    أرجع 0;
}

ساكن فراغ vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

ساكن صحيح vdpau_چوکٺا_get_constraints(AVHWDeviceContext *ctx,
                                        ثابت فراغ *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    صحيح nb_sw_formats = 0;
    صحيح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    إذا (!constraints->valid_sw_formats)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        إذا (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].چوکٺا_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    إذا (!constraints->valid_hw_formats)
        أرجع AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    أرجع 0;
}

ساكن فراغ vdpau_بفر_free(فراغ *opaque, uint8_t *معلومات)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)معلومات;

    device_priv->surf_destroy(surf);
}

ساكن AVBufferRef *vdpau_pool_alloc(فراغ *opaque, size_t سائيز)
{
    AVHWFramesContext             *ctx = opaque;
    VDPAUFramesContext           *priv = ctx->hwctx;
    VDPAUDeviceContext    *device_priv = ctx->device_ctx->hwctx;
    AVVDPAUDeviceContext *device_hwctx = &device_priv->p;

    AVBufferRef *ret;
    VdpVideoSurface surf;
    Vdp_حالت err;

    err = device_priv->surf_create(device_hwctx->device, priv->chroma_type,
                                   ctx->ويڪر, ctx->اوچائي, &surf);
    إذا (err != VDP_حالت_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        أرجع عدم;
    }

    ret = av_بفر_create((uint8_t*)(uintptr_t)surf, حجم(surf),
                           vdpau_بفر_free, ctx, AV_بفر_FLAG_READONLY);
    إذا (!ret) {
        device_priv->surf_destroy(surf);
        أرجع عدم;
    }

    أرجع ret;
}

ساكن صحيح vdpau_چوکٺا_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    صحيح i;

    لكل (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        إذا (vdpau_pix_fmts[i].چوکٺا_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            اكسر;
        }
    }
    إذا (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        أرجع AVERROR(ENOSYS);
    }

    إذا (!ctx->pool) {
        ffhwframesctx(ctx)->pool_اندروني =
            av_بفر_pool_init2(حجم(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, عدم);
        إذا (!ffhwframesctx(ctx)->pool_اندروني)
            أرجع AVERROR(ENOMEM);
    }

    priv->get_معلومات = device_priv->get_معلومات;
    priv->put_معلومات = device_priv->put_معلومات;

    أرجع 0;
}

ساكن صحيح vdpau_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکٺو)
{
    چوکٺو->buf[0] = av_بفر_pool_get(ctx->pool);
    إذا (!چوکٺو->buf[0])
        أرجع AVERROR(ENOMEM);

    چوکٺو->معلومات[3] = چوکٺو->buf[0]->معلومات;
    چوکٺو->format  = AV_PIX_FMT_VDPAU;
    چوکٺو->ويڪر   = ctx->ويڪر;
    چوکٺو->اوچائي  = ctx->اوچائي;

    أرجع 0;
}

ساكن صحيح vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      تعداد AVHWFrameTransferDirection dir,
                                      تعداد AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    تعداد AVPixelFormat *fmts;

    إذا (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        أرجع AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, حجم(*fmts));
    إذا (!fmts)
        أرجع AVERROR(ENOMEM);

    يادگيري_نقل(fmts, priv->pix_fmts, حجم(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    أرجع 0;
}

ساكن صحيح vdpau_transfer_معلومات_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ثابت AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->معلومات[3];

    فراغ *معلومات[3];
    uint32_t linesize[3];

    ثابت VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    Vdp_حالت err;
    صحيح i;

    لكل (i = 0; i< FF_ARRAY_ELEMS(معلومات) && dst->معلومات[i]; i++) {
        معلومات[i] = dst->معلومات[i];
        إذا (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            أرجع AVERROR(ERANGE);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    لكل (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        إذا (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            اكسر;
        }
    }
    إذا (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        أرجع AVERROR(EINVAL);
    }

    إذا ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#جيڪڏهن_وصف_ٿيل VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#جيڪڏهن_پورو
#جيڪڏهن_وصف_ٿيل VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#جيڪڏهن_پورو
            )
        FFSWAP(فراغ*, معلومات[1], معلومات[2]);

    err = priv->get_معلومات(surf, vdpau_format, معلومات, linesize);
    إذا (err != VDP_حالت_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}

ساكن صحيح vdpau_transfer_معلومات_منزل(AVHWFramesContext *ctx, AVFrame *dst,
                                  ثابت AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->معلومات[3];

    ثابت فراغ *معلومات[3];
    uint32_t linesize[3];

    ثابت VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    Vdp_حالت err;
    صحيح i;

    لكل (i = 0; i< FF_ARRAY_ELEMS(معلومات) && src->معلومات[i]; i++) {
        معلومات[i] = src->معلومات[i];
        إذا (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            أرجع AVERROR(ERANGE);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    لكل (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        إذا (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            اكسر;
        }
    }
    إذا (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        أرجع AVERROR(EINVAL);
    }

    إذا ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#جيڪڏهن_وصف_ٿيل VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#جيڪڏهن_پورو
            )
        FFSWAP(ثابت فراغ*, معلومات[1], معلومات[2]);

    err = priv->put_معلومات(surf, vdpau_format, معلومات, linesize);
    إذا (err != VDP_حالت_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        أرجع AVERROR_UNKNOWN;
    }

    أرجع 0;
}

#إذا HAVE_VDPAU_X11
#ضمن <vdpau/vdpau_x11.h>
#ضمن <X11/Xlib.h>

تعريفنوع بنية VDPAUDevicePriv {
    VdpDeviceDestroy *device_destroy;
    Display *dpy;
} VDPAUDevicePriv;

ساكن فراغ vdpau_device_free(AVHWDeviceContext *ctx)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;
    VDPAUDevicePriv       *priv = ctx->user_opaque;

    إذا (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    إذا (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

ساكن صحيح vdpau_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                               AVDictionary *opts, صحيح flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    Vdp_حالت err;
    VdpGetInformationString *get_information_string;
    ثابت حرف *display, *vendor;

    priv = av_mallocz(حجم(*priv));
    إذا (!priv)
        أرجع AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->حرر        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    إذا (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        أرجع AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_پتو);
    إذا (err != VDP_حالت_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        أرجع AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    أرجع 0;
}
#جيڪڏهن_پورو

ثابت HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_سائيز    = حجم(VDPAUDeviceContext),
    .چوکٺا_hwctx_سائيز    = حجم(VDPAUFramesContext),

#إذا HAVE_VDPAU_X11
    .device_create        = vdpau_device_create,
#جيڪڏهن_پورو
    .device_init          = vdpau_device_init,
    .device_uninit        = vdpau_device_uninit,
    .چوکٺا_get_constraints = vdpau_چوکٺا_get_constraints,
    .چوکٺا_init          = vdpau_چوکٺا_init,
    .چوکٺا_get_بفر    = vdpau_get_بفر,
    .transfer_get_formats = vdpau_transfer_get_formats,
    .transfer_معلومات_منزل     = vdpau_transfer_معلومات_منزل,
    .transfer_معلومات_from   = vdpau_transfer_معلومات_from,

    .pix_fmts = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_VDPAU, AV_PIX_FMT_NONE },
};
