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

#अन्तर्भाव "config.h"

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव <vdpau/vdpau.h>

#अन्तर्भाव "buffer.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "hwcontext_vdpau.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "pixdesc.h"

प्रकारनिर्देश संरचना VDPAUPixFmtMap {
    VdpYCbCrFormat vdpau_fmt;
    गणना AVPixelFormat pix_fmt;
} VDPAUPixFmtMap;

स्थिर ध्रुव VDPAUPixFmtMap pix_fmts_420[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV12    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV420P },
#ifdef VDP_YCBCR_FORMAT_P016
    { VDP_YCBCR_FORMAT_P016, AV_PIX_FMT_P016    },
    { VDP_YCBCR_FORMAT_P010, AV_PIX_FMT_P010    },
#endif
    { 0,                     AV_PIX_FMT_NONE,   },
};

स्थिर ध्रुव VDPAUPixFmtMap pix_fmts_422[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV16    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV422P },
    { VDP_YCBCR_FORMAT_UYVY, AV_PIX_FMT_UYVY422 },
    { VDP_YCBCR_FORMAT_YUYV, AV_PIX_FMT_YUYV422 },
    { 0,                     AV_PIX_FMT_NONE,   },
};

स्थिर ध्रुव VDPAUPixFmtMap pix_fmts_444[] = {
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
    { VDP_YCBCR_FORMAT_Y_U_V_444, AV_PIX_FMT_YUV444P },
#endif
#ifdef VDP_YCBCR_FORMAT_P016
    {VDP_YCBCR_FORMAT_Y_U_V_444_16, AV_PIX_FMT_YUV444P16},
#endif
    { 0,                          AV_PIX_FMT_NONE,   },
};

स्थिर ध्रुव संरचना {
    VdpChromaType chroma_type;
    गणना AVPixelFormat frames_sw_format;
    ध्रुव VDPAUPixFmtMap *map;
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

प्रकारनिर्देश संरचना VDPAUDeviceContext {
    /**
     * The public AVVDPAUDeviceContext. See hwcontext_vdpau.h for it.
     */
    AVVDPAUDeviceContext p;

    VdpVideoSurfaceQueryGetPutBitsYCbCrCapabilities *get_transfer_caps;
    VdpVideoSurfaceGetBitsYCbCr                     *get_data;
    VdpVideoSurfacePutBitsYCbCr                     *put_data;
    VdpVideoSurfaceCreate                           *surf_create;
    VdpVideoSurfaceDestroy                          *surf_destroy;

    गणना AVPixelFormat *pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
    पूर्णाङ्क              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

प्रकारनिर्देश संरचना VDPAUFramesContext {
    VdpVideoSurfaceGetBitsYCbCr *get_data;
    VdpVideoSurfacePutBitsYCbCr *put_data;
    VdpChromaType chroma_type;
    पूर्णाङ्क chroma_idx;

    ध्रुव गणना AVPixelFormat *pix_fmts;
    पूर्णाङ्क                       nb_pix_fmts;
} VDPAUFramesContext;

स्थिर पूर्णाङ्क मोजणी_pixfmts(ध्रुव VDPAUPixFmtMap *map)
{
    पूर्णाङ्क मोजणी = 0;
    यावत् (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        मोजणी++;
    }
    प्रत्यागम मोजणी;
}

स्थिर पूर्णाङ्क vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    पूर्णाङ्क i;

    प्रति (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        ध्रुव VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        पूर्णाङ्क nb_pix_fmts;

        nb_pix_fmts = मोजणी_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, परिमाण(*priv->pix_fmts[i]));
        यदि (!priv->pix_fmts[i])
            प्रत्यागम AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        यावत् (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            VdpStatus err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            यदि (err == VDP_STATUS_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    प्रत्यागम 0;
}

#define GET_CALLBACK(id, result)                                                \
कुरु {                                                                            \
    शून्य *tmp;                                                                  \
    err = hwctx->get_proc_address(hwctx->device, id, &tmp);                     \
    यदि (err != VDP_STATUS_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        प्रत्यागम AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    result = tmp;                                                               \
} यावत् (0)

स्थिर पूर्णाङ्क vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    VdpStatus             err;
    पूर्णाङ्क                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_BITS_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_BITS_Y_CB_CR, priv->get_data);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_BITS_Y_CB_CR, priv->put_data);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    यदि (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        प्रत्यागम ret;
    }

    प्रत्यागम 0;
}

स्थिर शून्य vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    पूर्णाङ्क i;

    प्रति (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

स्थिर पूर्णाङ्क vdpau_frames_get_constraints(AVHWDeviceContext *ctx,
                                        ध्रुव शून्य *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    पूर्णाङ्क nb_sw_formats = 0;
    पूर्णाङ्क i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    परिमाण(*constraints->valid_sw_formats));
    यदि (!constraints->valid_sw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        यदि (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].frames_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
    यदि (!constraints->valid_hw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    प्रत्यागम 0;
}

स्थिर शून्य vdpau_buffer_free(शून्य *opaque, uint8_t *data)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)data;

    device_priv->surf_destroy(surf);
}

स्थिर AVBufferRef *vdpau_pool_alloc(शून्य *opaque, size_t size)
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
    यदि (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        प्रत्यागम रिक्त;
    }

    ret = av_buffer_create((uint8_t*)(uintptr_t)surf, परिमाण(surf),
                           vdpau_buffer_free, ctx, AV_BUFFER_FLAG_READONLY);
    यदि (!ret) {
        device_priv->surf_destroy(surf);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क vdpau_frames_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    पूर्णाङ्क i;

    प्रति (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        यदि (vdpau_pix_fmts[i].frames_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            भङ्ग;
        }
    }
    यदि (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        प्रत्यागम AVERROR(ENOSYS);
    }

    यदि (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(परिमाण(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, रिक्त);
        यदि (!ffhwframesctx(ctx)->pool_internal)
            प्रत्यागम AVERROR(ENOMEM);
    }

    priv->get_data = device_priv->get_data;
    priv->put_data = device_priv->put_data;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vdpau_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    यदि (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VDPAU;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      गणना AVHWFrameTransferDirection dir,
                                      गणना AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    गणना AVPixelFormat *fmts;

    यदि (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        प्रत्यागम AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, परिमाण(*fmts));
    यदि (!fmts)
        प्रत्यागम AVERROR(ENOMEM);

    memcpy(fmts, priv->pix_fmts, परिमाण(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vdpau_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ध्रुव AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->data[3];

    शून्य *data[3];
    uint32_t linesize[3];

    ध्रुव VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    पूर्णाङ्क i;

    प्रति (i = 0; i< FF_ARRAY_ELEMS(data) && dst->data[i]; i++) {
        data[i] = dst->data[i];
        यदि (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            प्रत्यागम AVERROR(ERANGE);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    प्रति (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        यदि (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            भङ्ग;
        }
    }
    यदि (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        प्रत्यागम AVERROR(EINVAL);
    }

    यदि ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
#ifdef VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#endif
            )
        FFSWAP(शून्य*, data[1], data[2]);

    err = priv->get_data(surf, vdpau_format, data, linesize);
    यदि (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क vdpau_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  ध्रुव AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->data[3];

    ध्रुव शून्य *data[3];
    uint32_t linesize[3];

    ध्रुव VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    पूर्णाङ्क i;

    प्रति (i = 0; i< FF_ARRAY_ELEMS(data) && src->data[i]; i++) {
        data[i] = src->data[i];
        यदि (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            प्रत्यागम AVERROR(ERANGE);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    प्रति (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        यदि (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            भङ्ग;
        }
    }
    यदि (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        प्रत्यागम AVERROR(EINVAL);
    }

    यदि ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
            )
        FFSWAP(ध्रुव शून्य*, data[1], data[2]);

    err = priv->put_data(surf, vdpau_format, data, linesize);
    यदि (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}

#यदि HAVE_VDPAU_X11
#अन्तर्भाव <vdpau/vdpau_x11.h>
#अन्तर्भाव <X11/Xlib.h>

प्रकारनिर्देश संरचना VDPAUDevicePriv {
    VdpDeviceDestroy *device_destroy;
    Display *dpy;
} VDPAUDevicePriv;

स्थिर शून्य vdpau_device_free(AVHWDeviceContext *ctx)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;
    VDPAUDevicePriv       *priv = ctx->user_opaque;

    यदि (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    यदि (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

स्थिर पूर्णाङ्क vdpau_device_create(AVHWDeviceContext *ctx, ध्रुव वर्ण *device,
                               AVDictionary *opts, पूर्णाङ्क flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    VdpStatus err;
    VdpGetInformationString *get_information_string;
    ध्रुव वर्ण *display, *vendor;

    priv = av_mallocz(परिमाण(*priv));
    यदि (!priv)
        प्रत्यागम AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->मुक्त        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    यदि (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        प्रत्यागम AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_address);
    यदि (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    प्रत्यागम 0;
}
#endif

ध्रुव HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_size    = परिमाण(VDPAUDeviceContext),
    .frames_hwctx_size    = परिमाण(VDPAUFramesContext),

#यदि HAVE_VDPAU_X11
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

    .pix_fmts = (ध्रुव गणना AVPixelFormat[]){ AV_PIX_FMT_VDPAU, AV_PIX_FMT_NONE },
};
