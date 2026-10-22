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

#شامل "config.h"

#شامل <stdint.h>
#شامل <string.h>

#شامل <vdpau/vdpau.h>

#شامل "buffer.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_vdpau.h"
#شامل "mem.h"
#شامل "pixfmt.h"
#شامل "pixdesc.h"

قسمتعریف ساخت VDPAUPixFmtMap {
    VdpYCbCrFormat vdpau_fmt;
    شمار AVPixelFormat pix_fmt;
} VDPAUPixFmtMap;

ساکن ثابت VDPAUPixFmtMap pix_fmts_420[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV12    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV420P },
#اگر_تعریف_شدہ VDP_YCBCR_FORMAT_P016
    { VDP_YCBCR_FORMAT_P016, AV_PIX_FMT_P016    },
    { VDP_YCBCR_FORMAT_P010, AV_PIX_FMT_P010    },
#اگر_ختم
    { 0,                     AV_PIX_FMT_NONE,   },
};

ساکن ثابت VDPAUPixFmtMap pix_fmts_422[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV16    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV422P },
    { VDP_YCBCR_FORMAT_UYVY, AV_PIX_FMT_UYVY422 },
    { VDP_YCBCR_FORMAT_YUYV, AV_PIX_FMT_YUYV422 },
    { 0,                     AV_PIX_FMT_NONE,   },
};

ساکن ثابت VDPAUPixFmtMap pix_fmts_444[] = {
#اگر_تعریف_شدہ VDP_YCBCR_FORMAT_Y_U_V_444
    { VDP_YCBCR_FORMAT_Y_U_V_444, AV_PIX_FMT_YUV444P },
#اگر_ختم
#اگر_تعریف_شدہ VDP_YCBCR_FORMAT_P016
    {VDP_YCBCR_FORMAT_Y_U_V_444_16, AV_PIX_FMT_YUV444P16},
#اگر_ختم
    { 0,                          AV_PIX_FMT_NONE,   },
};

ساکن ثابت ساخت {
    VdpChromaType chroma_type;
    شمار AVPixelFormat چوکھٹے_sw_format;
    ثابت VDPAUPixFmtMap *map;
} vdpau_pix_fmts[] = {
    { VDP_CHROMA_TYPE_420, AV_PIX_FMT_YUV420P, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422, AV_PIX_FMT_YUV422P, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444, AV_PIX_FMT_YUV444P, pix_fmts_444 },
#اگر_تعریف_شدہ VDP_YCBCR_FORMAT_P016
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P10, pix_fmts_420 },
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P12, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422_16, AV_PIX_FMT_YUV422P10, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P10, pix_fmts_444 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P12, pix_fmts_444 },
#اگر_ختم
};

قسمتعریف ساخت VDPAUDeviceContext {
    /**
     * The public AVVDPAUDeviceContext. See hwcontext_vdpau.h for it.
     */
    AVVDPAUDeviceContext p;

    Vdp_Video_Surface_Query_Get_Put_بٹ_YCb_Cr_Capabilities *get_transfer_caps;
    Vdp_Video_Surface_Get_بٹ_YCb_Cr                     *get_ڈیٹا;
    Vdp_Video_Surface_Put_بٹ_YCb_Cr                     *put_ڈیٹا;
    VdpVideoSurfaceCreate                           *surf_create;
    VdpVideoSurfaceDestroy                          *surf_destroy;

    شمار AVPixelFormat *pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
    صحیح              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

قسمتعریف ساخت VDPAUFramesContext {
    Vdp_Video_Surface_Get_بٹ_YCb_Cr *get_ڈیٹا;
    Vdp_Video_Surface_Put_بٹ_YCb_Cr *put_ڈیٹا;
    VdpChromaType chroma_type;
    صحیح chroma_idx;

    ثابت شمار AVPixelFormat *pix_fmts;
    صحیح                       nb_pix_fmts;
} VDPAUFramesContext;

ساکن صحیح گنتی_pixfmts(ثابت VDPAUPixFmtMap *map)
{
    صحیح گنتی = 0;
    جب (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        گنتی++;
    }
    واپس گنتی;
}

ساکن صحیح vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    صحیح i;

    برائے (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        ثابت VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        صحیح nb_pix_fmts;

        nb_pix_fmts = گنتی_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, حجم(*priv->pix_fmts[i]));
        اگر (!priv->pix_fmts[i])
            واپس AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        جب (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            Vdp_حالت err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            اگر (err == VDP_حالت_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    واپس 0;
}

#تعریف_کرو GET_CALLBACK(id, نتیجہ)                                                \
کرو {                                                                            \
    خالی *tmp;                                                                  \
    err = hwctx->get_proc_پتہ(hwctx->device, id, &tmp);                     \
    اگر (err != VDP_حالت_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        واپس AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    نتیجہ = tmp;                                                               \
} جب (0)

ساکن صحیح vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    Vdp_حالت             err;
    صحیح                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_بٹ_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_بٹ_Y_CB_CR, priv->get_ڈیٹا);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_بٹ_Y_CB_CR, priv->put_ڈیٹا);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    اگر (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        واپس ret;
    }

    واپس 0;
}

ساکن خالی vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    صحیح i;

    برائے (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

ساکن صحیح vdpau_چوکھٹے_get_constraints(AVHWDeviceContext *ctx,
                                        ثابت خالی *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    صحیح nb_sw_formats = 0;
    صحیح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        واپس AVERROR(ENOMEM);

    برائے (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        اگر (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].چوکھٹے_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats)
        واپس AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    واپس 0;
}

ساکن خالی vdpau_بفر_free(خالی *opaque, uint8_t *ڈیٹا)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)ڈیٹا;

    device_priv->surf_destroy(surf);
}

ساکن AVBufferRef *vdpau_pool_alloc(خالی *opaque, size_t سائز)
{
    AVHWFramesContext             *ctx = opaque;
    VDPAUFramesContext           *priv = ctx->hwctx;
    VDPAUDeviceContext    *device_priv = ctx->device_ctx->hwctx;
    AVVDPAUDeviceContext *device_hwctx = &device_priv->p;

    AVBufferRef *ret;
    VdpVideoSurface surf;
    Vdp_حالت err;

    err = device_priv->surf_create(device_hwctx->device, priv->chroma_type,
                                   ctx->چوڑائی, ctx->اونچائی, &surf);
    اگر (err != VDP_حالت_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        واپس تہی;
    }

    ret = av_بفر_create((uint8_t*)(uintptr_t)surf, حجم(surf),
                           vdpau_بفر_free, ctx, AV_بفر_FLAG_READONLY);
    اگر (!ret) {
        device_priv->surf_destroy(surf);
        واپس تہی;
    }

    واپس ret;
}

ساکن صحیح vdpau_چوکھٹے_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    صحیح i;

    برائے (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        اگر (vdpau_pix_fmts[i].چوکھٹے_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            توڑو;
        }
    }
    اگر (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        واپس AVERROR(ENOSYS);
    }

    اگر (!ctx->pool) {
        ffhwframesctx(ctx)->pool_اندرونی =
            av_بفر_pool_init2(حجم(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, تہی);
        اگر (!ffhwframesctx(ctx)->pool_اندرونی)
            واپس AVERROR(ENOMEM);
    }

    priv->get_ڈیٹا = device_priv->get_ڈیٹا;
    priv->put_ڈیٹا = device_priv->put_ڈیٹا;

    واپس 0;
}

ساکن صحیح vdpau_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکھٹا)
{
    چوکھٹا->buf[0] = av_بفر_pool_get(ctx->pool);
    اگر (!چوکھٹا->buf[0])
        واپس AVERROR(ENOMEM);

    چوکھٹا->ڈیٹا[3] = چوکھٹا->buf[0]->ڈیٹا;
    چوکھٹا->format  = AV_PIX_FMT_VDPAU;
    چوکھٹا->چوڑائی   = ctx->چوڑائی;
    چوکھٹا->اونچائی  = ctx->اونچائی;

    واپس 0;
}

ساکن صحیح vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      شمار AVHWFrameTransferDirection dir,
                                      شمار AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    شمار AVPixelFormat *fmts;

    اگر (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        واپس AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, حجم(*fmts));
    اگر (!fmts)
        واپس AVERROR(ENOMEM);

    حافظہ_نقل(fmts, priv->pix_fmts, حجم(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    واپس 0;
}

ساکن صحیح vdpau_transfer_ڈیٹا_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ثابت AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->ڈیٹا[3];

    خالی *ڈیٹا[3];
    uint32_t linesize[3];

    ثابت VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    Vdp_حالت err;
    صحیح i;

    برائے (i = 0; i< FF_ARRAY_ELEMS(ڈیٹا) && dst->ڈیٹا[i]; i++) {
        ڈیٹا[i] = dst->ڈیٹا[i];
        اگر (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            واپس AVERROR(ERANGE);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    برائے (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        اگر (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            توڑو;
        }
    }
    اگر (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        واپس AVERROR(EINVAL);
    }

    اگر ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#اگر_تعریف_شدہ VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#اگر_ختم
#اگر_تعریف_شدہ VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#اگر_ختم
            )
        FFSWAP(خالی*, ڈیٹا[1], ڈیٹا[2]);

    err = priv->get_ڈیٹا(surf, vdpau_format, ڈیٹا, linesize);
    اگر (err != VDP_حالت_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        واپس AVERROR_UNKNOWN;
    }

    واپس 0;
}

ساکن صحیح vdpau_transfer_ڈیٹا_مقصد(AVHWFramesContext *ctx, AVFrame *dst,
                                  ثابت AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->ڈیٹا[3];

    ثابت خالی *ڈیٹا[3];
    uint32_t linesize[3];

    ثابت VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    Vdp_حالت err;
    صحیح i;

    برائے (i = 0; i< FF_ARRAY_ELEMS(ڈیٹا) && src->ڈیٹا[i]; i++) {
        ڈیٹا[i] = src->ڈیٹا[i];
        اگر (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            واپس AVERROR(ERANGE);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    برائے (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        اگر (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            توڑو;
        }
    }
    اگر (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        واپس AVERROR(EINVAL);
    }

    اگر ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#اگر_تعریف_شدہ VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#اگر_ختم
            )
        FFSWAP(ثابت خالی*, ڈیٹا[1], ڈیٹا[2]);

    err = priv->put_ڈیٹا(surf, vdpau_format, ڈیٹا, linesize);
    اگر (err != VDP_حالت_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        واپس AVERROR_UNKNOWN;
    }

    واپس 0;
}

#اگر HAVE_VDPAU_X11
#شامل <vdpau/vdpau_x11.h>
#شامل <X11/Xlib.h>

قسمتعریف ساخت VDPAUDevicePriv {
    VdpDeviceDestroy *device_destroy;
    Display *dpy;
} VDPAUDevicePriv;

ساکن خالی vdpau_device_free(AVHWDeviceContext *ctx)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;
    VDPAUDevicePriv       *priv = ctx->user_opaque;

    اگر (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    اگر (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

ساکن صحیح vdpau_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                               AVDictionary *opts, صحیح flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    Vdp_حالت err;
    VdpGetInformationString *get_information_string;
    ثابت حرف *display, *vendor;

    priv = av_mallocz(حجم(*priv));
    اگر (!priv)
        واپس AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->آزاد        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    اگر (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        واپس AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_پتہ);
    اگر (err != VDP_حالت_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        واپس AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    واپس 0;
}
#اگر_ختم

ثابت HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_سائز    = حجم(VDPAUDeviceContext),
    .چوکھٹے_hwctx_سائز    = حجم(VDPAUFramesContext),

#اگر HAVE_VDPAU_X11
    .device_create        = vdpau_device_create,
#اگر_ختم
    .device_init          = vdpau_device_init,
    .device_uninit        = vdpau_device_uninit,
    .چوکھٹے_get_constraints = vdpau_چوکھٹے_get_constraints,
    .چوکھٹے_init          = vdpau_چوکھٹے_init,
    .چوکھٹے_get_بفر    = vdpau_get_بفر,
    .transfer_get_formats = vdpau_transfer_get_formats,
    .transfer_ڈیٹا_مقصد     = vdpau_transfer_ڈیٹا_مقصد,
    .transfer_ڈیٹا_from   = vdpau_transfer_ڈیٹا_from,

    .pix_fmts = (ثابت شمار AVPixelFormat[]){ AV_PIX_FMT_VDPAU, AV_PIX_FMT_NONE },
};
