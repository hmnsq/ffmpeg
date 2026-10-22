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

#அந்தர்பாவ "config.h"

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ <vdpau/vdpau.h>

#அந்தர்பாவ "buffer.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "hwcontext.h"
#அந்தர்பாவ "hwcontext_internal.h"
#அந்தர்பாவ "hwcontext_vdpau.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "pixfmt.h"
#அந்தர்பாவ "pixdesc.h"

வகைவரை கட்டமைப்பு VDPAUPixFmtMap {
    VdpYCbCrFormat vdpau_fmt;
    எண்ணிக்கை AVPixelFormat pix_fmt;
} VDPAUPixFmtMap;

நிலையான மாறிலி VDPAUPixFmtMap pix_fmts_420[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV12    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV420P },
#ifdef VDP_YCBCR_FORMAT_P016
    { VDP_YCBCR_FORMAT_P016, AV_PIX_FMT_P016    },
    { VDP_YCBCR_FORMAT_P010, AV_PIX_FMT_P010    },
#endif
    { 0,                     AV_PIX_FMT_NONE,   },
};

நிலையான மாறிலி VDPAUPixFmtMap pix_fmts_422[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV16    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV422P },
    { VDP_YCBCR_FORMAT_UYVY, AV_PIX_FMT_UYVY422 },
    { VDP_YCBCR_FORMAT_YUYV, AV_PIX_FMT_YUYV422 },
    { 0,                     AV_PIX_FMT_NONE,   },
};

நிலையான மாறிலி VDPAUPixFmtMap pix_fmts_444[] = {
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
    { VDP_YCBCR_FORMAT_Y_U_V_444, AV_PIX_FMT_YUV444P },
#endif
#ifdef VDP_YCBCR_FORMAT_P016
    {VDP_YCBCR_FORMAT_Y_U_V_444_16, AV_PIX_FMT_YUV444P16},
#endif
    { 0,                          AV_PIX_FMT_NONE,   },
};

நிலையான மாறிலி கட்டமைப்பு {
    VdpChromaType chroma_type;
    எண்ணிக்கை AVPixelFormat frames_sw_format;
    மாறிலி VDPAUPixFmtMap *map;
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

வகைவரை கட்டமைப்பு VDPAUDeviceContext {
    /**
     * The public AVVDPAUDeviceContext. See hwcontext_vdpau.h for it.
     */
    AVVDPAUDeviceContext p;

    VdpVideoSurfaceQueryGetPutBitsYCbCrCapabilities *get_transfer_caps;
    VdpVideoSurfaceGetBitsYCbCr                     *get_data;
    VdpVideoSurfacePutBitsYCbCr                     *put_data;
    VdpVideoSurfaceCreate                           *surf_create;
    VdpVideoSurfaceDestroy                          *surf_destroy;

    எண்ணிக்கை AVPixelFormat *pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
    முழு              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

வகைவரை கட்டமைப்பு VDPAUFramesContext {
    VdpVideoSurfaceGetBitsYCbCr *get_data;
    VdpVideoSurfacePutBitsYCbCr *put_data;
    VdpChromaType chroma_type;
    முழு chroma_idx;

    மாறிலி எண்ணிக்கை AVPixelFormat *pix_fmts;
    முழு                       nb_pix_fmts;
} VDPAUFramesContext;

நிலையான முழு மொத்தம்_pixfmts(மாறிலி VDPAUPixFmtMap *map)
{
    முழு மொத்தம் = 0;
    போது (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        மொத்தம்++;
    }
    திரும்பு மொத்தம்;
}

நிலையான முழு vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    முழு i;

    க்கு (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        மாறிலி VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        முழு nb_pix_fmts;

        nb_pix_fmts = மொத்தம்_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, அளவு(*priv->pix_fmts[i]));
        எனில் (!priv->pix_fmts[i])
            திரும்பு AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        போது (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            VdpStatus err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            எனில் (err == VDP_STATUS_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    திரும்பு 0;
}

#define GET_CALLBACK(id, result)                                                \
செய் {                                                                            \
    வெறுமை *tmp;                                                                  \
    err = hwctx->get_proc_address(hwctx->device, id, &tmp);                     \
    எனில் (err != VDP_STATUS_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        திரும்பு AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    result = tmp;                                                               \
} போது (0)

நிலையான முழு vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    VdpStatus             err;
    முழு                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_BITS_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_BITS_Y_CB_CR, priv->get_data);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_BITS_Y_CB_CR, priv->put_data);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    எனில் (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        திரும்பு ret;
    }

    திரும்பு 0;
}

நிலையான வெறுமை vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    முழு i;

    க்கு (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

நிலையான முழு vdpau_frames_get_constraints(AVHWDeviceContext *ctx,
                                        மாறிலி வெறுமை *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    முழு nb_sw_formats = 0;
    முழு i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    அளவு(*constraints->valid_sw_formats));
    எனில் (!constraints->valid_sw_formats)
        திரும்பு AVERROR(ENOMEM);

    க்கு (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        எனில் (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].frames_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, அளவு(*constraints->valid_hw_formats));
    எனில் (!constraints->valid_hw_formats)
        திரும்பு AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    திரும்பு 0;
}

நிலையான வெறுமை vdpau_buffer_free(வெறுமை *opaque, uint8_t *data)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)data;

    device_priv->surf_destroy(surf);
}

நிலையான AVBufferRef *vdpau_pool_alloc(வெறுமை *opaque, size_t size)
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
    எனில் (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        திரும்பு வெற்று;
    }

    ret = av_buffer_create((uint8_t*)(uintptr_t)surf, அளவு(surf),
                           vdpau_buffer_free, ctx, AV_BUFFER_FLAG_READONLY);
    எனில் (!ret) {
        device_priv->surf_destroy(surf);
        திரும்பு வெற்று;
    }

    திரும்பு ret;
}

நிலையான முழு vdpau_frames_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    முழு i;

    க்கு (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        எனில் (vdpau_pix_fmts[i].frames_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            நிறுத்து;
        }
    }
    எனில் (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        திரும்பு AVERROR(ENOSYS);
    }

    எனில் (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(அளவு(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, வெற்று);
        எனில் (!ffhwframesctx(ctx)->pool_internal)
            திரும்பு AVERROR(ENOMEM);
    }

    priv->get_data = device_priv->get_data;
    priv->put_data = device_priv->put_data;

    திரும்பு 0;
}

நிலையான முழு vdpau_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    எனில் (!frame->buf[0])
        திரும்பு AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VDPAU;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    திரும்பு 0;
}

நிலையான முழு vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      எண்ணிக்கை AVHWFrameTransferDirection dir,
                                      எண்ணிக்கை AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    எண்ணிக்கை AVPixelFormat *fmts;

    எனில் (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        திரும்பு AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, அளவு(*fmts));
    எனில் (!fmts)
        திரும்பு AVERROR(ENOMEM);

    memcpy(fmts, priv->pix_fmts, அளவு(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    திரும்பு 0;
}

நிலையான முழு vdpau_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    மாறிலி AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->data[3];

    வெறுமை *data[3];
    uint32_t linesize[3];

    மாறிலி VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    முழு i;

    க்கு (i = 0; i< FF_ARRAY_ELEMS(data) && dst->data[i]; i++) {
        data[i] = dst->data[i];
        எனில் (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            திரும்பு AVERROR(ERANGE);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    க்கு (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        எனில் (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            நிறுத்து;
        }
    }
    எனில் (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        திரும்பு AVERROR(EINVAL);
    }

    எனில் ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
#ifdef VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#endif
            )
        FFSWAP(வெறுமை*, data[1], data[2]);

    err = priv->get_data(surf, vdpau_format, data, linesize);
    எனில் (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    திரும்பு 0;
}

நிலையான முழு vdpau_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  மாறிலி AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->data[3];

    மாறிலி வெறுமை *data[3];
    uint32_t linesize[3];

    மாறிலி VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    முழு i;

    க்கு (i = 0; i< FF_ARRAY_ELEMS(data) && src->data[i]; i++) {
        data[i] = src->data[i];
        எனில் (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            திரும்பு AVERROR(ERANGE);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    க்கு (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        எனில் (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            நிறுத்து;
        }
    }
    எனில் (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        திரும்பு AVERROR(EINVAL);
    }

    எனில் ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
            )
        FFSWAP(மாறிலி வெறுமை*, data[1], data[2]);

    err = priv->put_data(surf, vdpau_format, data, linesize);
    எனில் (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    திரும்பு 0;
}

#எனில் HAVE_VDPAU_X11
#அந்தர்பாவ <vdpau/vdpau_x11.h>
#அந்தர்பாவ <X11/Xlib.h>

வகைவரை கட்டமைப்பு VDPAUDevicePriv {
    VdpDeviceDestroy *device_destroy;
    Display *dpy;
} VDPAUDevicePriv;

நிலையான வெறுமை vdpau_device_free(AVHWDeviceContext *ctx)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;
    VDPAUDevicePriv       *priv = ctx->user_opaque;

    எனில் (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    எனில் (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

நிலையான முழு vdpau_device_create(AVHWDeviceContext *ctx, மாறிலி எழுத்து *device,
                               AVDictionary *opts, முழு flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    VdpStatus err;
    VdpGetInformationString *get_information_string;
    மாறிலி எழுத்து *display, *vendor;

    priv = av_mallocz(அளவு(*priv));
    எனில் (!priv)
        திரும்பு AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->விடுவி        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    எனில் (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        திரும்பு AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_address);
    எனில் (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        திரும்பு AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    திரும்பு 0;
}
#endif

மாறிலி HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_size    = அளவு(VDPAUDeviceContext),
    .frames_hwctx_size    = அளவு(VDPAUFramesContext),

#எனில் HAVE_VDPAU_X11
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

    .pix_fmts = (மாறிலி எண்ணிக்கை AVPixelFormat[]){ AV_PIX_FMT_VDPAU, AV_PIX_FMT_NONE },
};
