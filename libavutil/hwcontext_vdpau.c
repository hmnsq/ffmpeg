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

تعریفنوع ساختار VDPAUPixFmtMap {
    VdpYCbCrFormat vdpau_fmt;
    شمارش AVPixelFormat pix_fmt;
} VDPAUPixFmtMap;

ایستا ثابت VDPAUPixFmtMap pix_fmts_420[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV12    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV420P },
#ifdef VDP_YCBCR_FORMAT_P016
    { VDP_YCBCR_FORMAT_P016, AV_PIX_FMT_P016    },
    { VDP_YCBCR_FORMAT_P010, AV_PIX_FMT_P010    },
#endif
    { 0,                     AV_PIX_FMT_NONE,   },
};

ایستا ثابت VDPAUPixFmtMap pix_fmts_422[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV16    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV422P },
    { VDP_YCBCR_FORMAT_UYVY, AV_PIX_FMT_UYVY422 },
    { VDP_YCBCR_FORMAT_YUYV, AV_PIX_FMT_YUYV422 },
    { 0,                     AV_PIX_FMT_NONE,   },
};

ایستا ثابت VDPAUPixFmtMap pix_fmts_444[] = {
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
    { VDP_YCBCR_FORMAT_Y_U_V_444, AV_PIX_FMT_YUV444P },
#endif
#ifdef VDP_YCBCR_FORMAT_P016
    {VDP_YCBCR_FORMAT_Y_U_V_444_16, AV_PIX_FMT_YUV444P16},
#endif
    { 0,                          AV_PIX_FMT_NONE,   },
};

ایستا ثابت ساختار {
    VdpChromaType chroma_type;
    شمارش AVPixelFormat frames_sw_format;
    ثابت VDPAUPixFmtMap *map;
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

تعریفنوع ساختار VDPAUDeviceContext {
    /**
     * The public AVVDPAUDeviceContext. See hwcontext_vdpau.h for it.
     */
    AVVDPAUDeviceContext p;

    VdpVideoSurfaceQueryGetPutBitsYCbCrCapabilities *get_transfer_caps;
    VdpVideoSurfaceGetBitsYCbCr                     *get_data;
    VdpVideoSurfacePutBitsYCbCr                     *put_data;
    VdpVideoSurfaceCreate                           *surf_create;
    VdpVideoSurfaceDestroy                          *surf_destroy;

    شمارش AVPixelFormat *pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
    صحیح              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

تعریفنوع ساختار VDPAUFramesContext {
    VdpVideoSurfaceGetBitsYCbCr *get_data;
    VdpVideoSurfacePutBitsYCbCr *put_data;
    VdpChromaType chroma_type;
    صحیح chroma_idx;

    ثابت شمارش AVPixelFormat *pix_fmts;
    صحیح                       nb_pix_fmts;
} VDPAUFramesContext;

ایستا صحیح شمار_pixfmts(ثابت VDPAUPixFmtMap *map)
{
    صحیح شمار = 0;
    وقتی (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        شمار++;
    }
    بازگشت شمار;
}

ایستا صحیح vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    صحیح i;

    برای (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        ثابت VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        صحیح nb_pix_fmts;

        nb_pix_fmts = شمار_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, اندازه(*priv->pix_fmts[i]));
        اگر (!priv->pix_fmts[i])
            بازگشت AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        وقتی (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            VdpStatus err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            اگر (err == VDP_STATUS_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    بازگشت 0;
}

#define GET_CALLBACK(id, result)                                                \
انجامبده {                                                                            \
    تهی *tmp;                                                                  \
    err = hwctx->get_proc_address(hwctx->device, id, &tmp);                     \
    اگر (err != VDP_STATUS_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        بازگشت AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    result = tmp;                                                               \
} وقتی (0)

ایستا صحیح vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    VdpStatus             err;
    صحیح                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_BITS_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_BITS_Y_CB_CR, priv->get_data);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_BITS_Y_CB_CR, priv->put_data);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    اگر (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        بازگشت ret;
    }

    بازگشت 0;
}

ایستا تهی vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    صحیح i;

    برای (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

ایستا صحیح vdpau_frames_get_constraints(AVHWDeviceContext *ctx,
                                        ثابت تهی *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    صحیح nb_sw_formats = 0;
    صحیح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    اندازه(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        بازگشت AVERROR(ENOMEM);

    برای (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        اگر (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].frames_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, اندازه(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats)
        بازگشت AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    بازگشت 0;
}

ایستا تهی vdpau_buffer_free(تهی *opaque, uint8_t *data)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)data;

    device_priv->surf_destroy(surf);
}

ایستا AVBufferRef *vdpau_pool_alloc(تهی *opaque, size_t size)
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
    اگر (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        بازگشت پوچ;
    }

    ret = av_buffer_create((uint8_t*)(uintptr_t)surf, اندازه(surf),
                           vdpau_buffer_free, ctx, AV_BUFFER_FLAG_READONLY);
    اگر (!ret) {
        device_priv->surf_destroy(surf);
        بازگشت پوچ;
    }

    بازگشت ret;
}

ایستا صحیح vdpau_frames_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    صحیح i;

    برای (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        اگر (vdpau_pix_fmts[i].frames_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            بشکن;
        }
    }
    اگر (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        بازگشت AVERROR(ENOSYS);
    }

    اگر (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(اندازه(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, پوچ);
        اگر (!ffhwframesctx(ctx)->pool_internal)
            بازگشت AVERROR(ENOMEM);
    }

    priv->get_data = device_priv->get_data;
    priv->put_data = device_priv->put_data;

    بازگشت 0;
}

ایستا صحیح vdpau_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    اگر (!frame->buf[0])
        بازگشت AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VDPAU;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    بازگشت 0;
}

ایستا صحیح vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      شمارش AVHWFrameTransferDirection dir,
                                      شمارش AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    شمارش AVPixelFormat *fmts;

    اگر (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        بازگشت AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, اندازه(*fmts));
    اگر (!fmts)
        بازگشت AVERROR(ENOMEM);

    memcpy(fmts, priv->pix_fmts, اندازه(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    بازگشت 0;
}

ایستا صحیح vdpau_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ثابت AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->data[3];

    تهی *data[3];
    uint32_t linesize[3];

    ثابت VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    صحیح i;

    برای (i = 0; i< FF_ARRAY_ELEMS(data) && dst->data[i]; i++) {
        data[i] = dst->data[i];
        اگر (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            بازگشت AVERROR(ERANGE);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    برای (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        اگر (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            بشکن;
        }
    }
    اگر (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        بازگشت AVERROR(EINVAL);
    }

    اگر ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
#ifdef VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#endif
            )
        FFSWAP(تهی*, data[1], data[2]);

    err = priv->get_data(surf, vdpau_format, data, linesize);
    اگر (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        بازگشت AVERROR_UNKNOWN;
    }

    بازگشت 0;
}

ایستا صحیح vdpau_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  ثابت AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->data[3];

    ثابت تهی *data[3];
    uint32_t linesize[3];

    ثابت VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    صحیح i;

    برای (i = 0; i< FF_ARRAY_ELEMS(data) && src->data[i]; i++) {
        data[i] = src->data[i];
        اگر (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            بازگشت AVERROR(ERANGE);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    برای (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        اگر (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            بشکن;
        }
    }
    اگر (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        بازگشت AVERROR(EINVAL);
    }

    اگر ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
            )
        FFSWAP(ثابت تهی*, data[1], data[2]);

    err = priv->put_data(surf, vdpau_format, data, linesize);
    اگر (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        بازگشت AVERROR_UNKNOWN;
    }

    بازگشت 0;
}

#اگر HAVE_VDPAU_X11
#شامل <vdpau/vdpau_x11.h>
#شامل <X11/Xlib.h>

تعریفنوع ساختار VDPAUDevicePriv {
    VdpDeviceDestroy *device_destroy;
    Display *dpy;
} VDPAUDevicePriv;

ایستا تهی vdpau_device_free(AVHWDeviceContext *ctx)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;
    VDPAUDevicePriv       *priv = ctx->user_opaque;

    اگر (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    اگر (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

ایستا صحیح vdpau_device_create(AVHWDeviceContext *ctx, ثابت نویسه *device,
                               AVDictionary *opts, صحیح flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    VdpStatus err;
    VdpGetInformationString *get_information_string;
    ثابت نویسه *display, *vendor;

    priv = av_mallocz(اندازه(*priv));
    اگر (!priv)
        بازگشت AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->آزاد        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    اگر (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        بازگشت AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_address);
    اگر (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        بازگشت AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    بازگشت 0;
}
#endif

ثابت HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_size    = اندازه(VDPAUDeviceContext),
    .frames_hwctx_size    = اندازه(VDPAUFramesContext),

#اگر HAVE_VDPAU_X11
    .device_create        = vdpau_device_create,
#endif
    .device_init          = vdpau_device_init,
    .device_uninit        = vdpau_device_uninit,
    .frames_get_constraints = vdpau_frames_get_constraints,
    .frames_init          = vdpau_frames_init,
    .frames_get_buffer    = vdpau_get_buffer,
    .transfer_get_formats = vdpau_transfer_get_formats,
    .transfer_data_to     = vdpau_transfer_data_to,
    .transfer_data_from   = vdpau_transfer_data_from,

    .pix_fmts = (ثابت شمارش AVPixelFormat[]){ AV_PIX_FMT_VDPAU, AV_PIX_FMT_NONE },
};
