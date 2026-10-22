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

#include "config.h"

#include <stdint.h>
#include <string.h>

#include <vdpau/vdpau.h>

#include "buffer.h"
#include "common.h"
#include "hwcontext.h"
#include "hwcontext_internal.h"
#include "hwcontext_vdpau.h"
#include "mem.h"
#include "pixfmt.h"
#include "pixdesc.h"

typedef sa_nracanaa VDPAUPixFmtMap {
    VdpYCbCrFormat vdpau_fmt;
    ga_nanaa AVPixelFormat pix_fmt;
} VDPAUPixFmtMap;

static const VDPAUPixFmtMap pix_fmts_420[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV12    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV420P },
#ifdef VDP_YCBCR_FORMAT_P016
    { VDP_YCBCR_FORMAT_P016, AV_PIX_FMT_P016    },
    { VDP_YCBCR_FORMAT_P010, AV_PIX_FMT_P010    },
#endif
    { 0,                     AV_PIX_FMT_NONE,   },
};

static const VDPAUPixFmtMap pix_fmts_422[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV16    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV422P },
    { VDP_YCBCR_FORMAT_UYVY, AV_PIX_FMT_UYVY422 },
    { VDP_YCBCR_FORMAT_YUYV, AV_PIX_FMT_YUYV422 },
    { 0,                     AV_PIX_FMT_NONE,   },
};

static const VDPAUPixFmtMap pix_fmts_444[] = {
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
    { VDP_YCBCR_FORMAT_Y_U_V_444, AV_PIX_FMT_YUV444P },
#endif
#ifdef VDP_YCBCR_FORMAT_P016
    {VDP_YCBCR_FORMAT_Y_U_V_444_16, AV_PIX_FMT_YUV444P16},
#endif
    { 0,                          AV_PIX_FMT_NONE,   },
};

static const sa_nracanaa {
    VdpChromaType chroma_type;
    ga_nanaa AVPixelFormat frames_sw_format;
    const VDPAUPixFmtMap *map;
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

typedef sa_nracanaa VDPAUDeviceContext {
    /**
     * The public AVVDPAUDeviceContext. See hwcontext_vdpau.h for it.
     */
    AVVDPAUDeviceContext p;

    VdpVideoSurfaceQueryGetPutBitsYCbCrCapabilities *get_transfer_caps;
    VdpVideoSurfaceGetBitsYCbCr                     *get_data;
    VdpVideoSurfacePutBitsYCbCr                     *put_data;
    VdpVideoSurfaceCreate                           *surf_create;
    VdpVideoSurfaceDestroy                          *surf_destroy;

    ga_nanaa AVPixelFormat *pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
    ကိန်းပြည့်              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

typedef sa_nracanaa VDPAUFramesContext {
    VdpVideoSurfaceGetBitsYCbCr *get_data;
    VdpVideoSurfacePutBitsYCbCr *put_data;
    VdpChromaType chroma_type;
    ကိန်းပြည့် chroma_idx;

    const ga_nanaa AVPixelFormat *pix_fmts;
    ကိန်းပြည့်                       nb_pix_fmts;
} VDPAUFramesContext;

static ကိန်းပြည့် count_pixfmts(const VDPAUPixFmtMap *map)
{
    ကိန်းပြည့် count = 0;
    နေစဉ် (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        count++;
    }
    ပြန်ပေး count;
}

static ကိန်းပြည့် vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    ကိန်းပြည့် i;

    အတွက် (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        const VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        ကိန်းပြည့် nb_pix_fmts;

        nb_pix_fmts = count_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, parimaa_na(*priv->pix_fmts[i]));
        အကယ်၍ (!priv->pix_fmts[i])
            ပြန်ပေး AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        နေစဉ် (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            VdpStatus err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            အကယ်၍ (err == VDP_STATUS_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    ပြန်ပေး 0;
}

#define GET_CALLBACK(id, result)                                                \
do {                                                                            \
    void *tmp;                                                                  \
    err = hwctx->get_proc_address(hwctx->device, id, &tmp);                     \
    အကယ်၍ (err != VDP_STATUS_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        ပြန်ပေး AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    result = tmp;                                                               \
} နေစဉ် (0)

static ကိန်းပြည့် vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    VdpStatus             err;
    ကိန်းပြည့်                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_BITS_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_BITS_Y_CB_CR, priv->get_data);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_BITS_Y_CB_CR, priv->put_data);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    အကယ်၍ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        ပြန်ပေး ret;
    }

    ပြန်ပေး 0;
}

static void vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    ကိန်းပြည့် i;

    အတွက် (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

static ကိန်းပြည့် vdpau_frames_get_constraints(AVHWDeviceContext *ctx,
                                        const void *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    ကိန်းပြည့် nb_sw_formats = 0;
    ကိန်းပြည့် i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    parimaa_na(*constraints->valid_sw_formats));
    အကယ်၍ (!constraints->valid_sw_formats)
        ပြန်ပေး AVERROR(ENOMEM);

    အတွက် (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        အကယ်၍ (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].frames_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, parimaa_na(*constraints->valid_hw_formats));
    အကယ်၍ (!constraints->valid_hw_formats)
        ပြန်ပေး AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ပြန်ပေး 0;
}

static void vdpau_buffer_free(void *opaque, uint8_t *data)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)data;

    device_priv->surf_destroy(surf);
}

static AVBufferRef *vdpau_pool_alloc(void *opaque, size_t size)
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
    အကယ်၍ (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        ပြန်ပေး NULL;
    }

    ret = av_buffer_create((uint8_t*)(uintptr_t)surf, parimaa_na(surf),
                           vdpau_buffer_free, ctx, AV_BUFFER_FLAG_READONLY);
    အကယ်၍ (!ret) {
        device_priv->surf_destroy(surf);
        ပြန်ပေး NULL;
    }

    ပြန်ပေး ret;
}

static ကိန်းပြည့် vdpau_frames_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    ကိန်းပြည့် i;

    အတွက် (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        အကယ်၍ (vdpau_pix_fmts[i].frames_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            bha_nga;
        }
    }
    အကယ်၍ (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ပြန်ပေး AVERROR(ENOSYS);
    }

    အကယ်၍ (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(parimaa_na(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, NULL);
        အကယ်၍ (!ffhwframesctx(ctx)->pool_internal)
            ပြန်ပေး AVERROR(ENOMEM);
    }

    priv->get_data = device_priv->get_data;
    priv->put_data = device_priv->put_data;

    ပြန်ပေး 0;
}

static ကိန်းပြည့် vdpau_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    အကယ်၍ (!frame->buf[0])
        ပြန်ပေး AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VDPAU;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ပြန်ပေး 0;
}

static ကိန်းပြည့် vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      ga_nanaa AVHWFrameTransferDirection dir,
                                      ga_nanaa AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    ga_nanaa AVPixelFormat *fmts;

    အကယ်၍ (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        ပြန်ပေး AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, parimaa_na(*fmts));
    အကယ်၍ (!fmts)
        ပြန်ပေး AVERROR(ENOMEM);

    memcpy(fmts, priv->pix_fmts, parimaa_na(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    ပြန်ပေး 0;
}

static ကိန်းပြည့် vdpau_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    const AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->data[3];

    void *data[3];
    uint32_t linesize[3];

    const VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    ကိန်းပြည့် i;

    အတွက် (i = 0; i< FF_ARRAY_ELEMS(data) && dst->data[i]; i++) {
        data[i] = dst->data[i];
        အကယ်၍ (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            ပြန်ပေး AVERROR(ERANGE);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    အတွက် (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        အကယ်၍ (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            bha_nga;
        }
    }
    အကယ်၍ (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        ပြန်ပေး AVERROR(EINVAL);
    }

    အကယ်၍ ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
#ifdef VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#endif
            )
        FFSWAP(void*, data[1], data[2]);

    err = priv->get_data(surf, vdpau_format, data, linesize);
    အကယ်၍ (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        ပြန်ပေး AVERROR_UNKNOWN;
    }

    ပြန်ပေး 0;
}

static ကိန်းပြည့် vdpau_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  const AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->data[3];

    const void *data[3];
    uint32_t linesize[3];

    const VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    ကိန်းပြည့် i;

    အတွက် (i = 0; i< FF_ARRAY_ELEMS(data) && src->data[i]; i++) {
        data[i] = src->data[i];
        အကယ်၍ (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            ပြန်ပေး AVERROR(ERANGE);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    အတွက် (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        အကယ်၍ (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            bha_nga;
        }
    }
    အကယ်၍ (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        ပြန်ပေး AVERROR(EINVAL);
    }

    အကယ်၍ ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
            )
        FFSWAP(const void*, data[1], data[2]);

    err = priv->put_data(surf, vdpau_format, data, linesize);
    အကယ်၍ (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        ပြန်ပေး AVERROR_UNKNOWN;
    }

    ပြန်ပေး 0;
}

#အကယ်၍ HAVE_VDPAU_X11
#include <vdpau/vdpau_x11.h>
#include <X11/Xlib.h>

typedef sa_nracanaa VDPAUDevicePriv {
    VdpDeviceDestroy *device_destroy;
    Display *dpy;
} VDPAUDevicePriv;

static void vdpau_device_free(AVHWDeviceContext *ctx)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;
    VDPAUDevicePriv       *priv = ctx->user_opaque;

    အကယ်၍ (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    အကယ်၍ (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

static ကိန်းပြည့် vdpau_device_create(AVHWDeviceContext *ctx, const var_na *device,
                               AVDictionary *opts, ကိန်းပြည့် flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    VdpStatus err;
    VdpGetInformationString *get_information_string;
    const var_na *display, *vendor;

    priv = av_mallocz(parimaa_na(*priv));
    အကယ်၍ (!priv)
        ပြန်ပေး AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->free        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    အကယ်၍ (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        ပြန်ပေး AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_address);
    အကယ်၍ (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        ပြန်ပေး AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    ပြန်ပေး 0;
}
#endif

const HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_size    = parimaa_na(VDPAUDeviceContext),
    .frames_hwctx_size    = parimaa_na(VDPAUFramesContext),

#အကယ်၍ HAVE_VDPAU_X11
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

    .pix_fmts = (const ga_nanaa AVPixelFormat[]){ AV_PIX_FMT_VDPAU, AV_PIX_FMT_NONE },
};
