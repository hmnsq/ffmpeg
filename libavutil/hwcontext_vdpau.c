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
    ཧྲིལ              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

typedef sa_nracanaa VDPAUFramesContext {
    VdpVideoSurfaceGetBitsYCbCr *get_data;
    VdpVideoSurfacePutBitsYCbCr *put_data;
    VdpChromaType chroma_type;
    ཧྲིལ chroma_idx;

    const ga_nanaa AVPixelFormat *pix_fmts;
    ཧྲིལ                       nb_pix_fmts;
} VDPAUFramesContext;

static ཧྲིལ count_pixfmts(const VDPAUPixFmtMap *map)
{
    ཧྲིལ count = 0;
    སྐབས (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        count++;
    }
    ཕྱིར count;
}

static ཧྲིལ vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    ཧྲིལ i;

    ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        const VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        ཧྲིལ nb_pix_fmts;

        nb_pix_fmts = count_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, parimaa_na(*priv->pix_fmts[i]));
        གལ་ཏེ (!priv->pix_fmts[i])
            ཕྱིར AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        སྐབས (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            VdpStatus err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            གལ་ཏེ (err == VDP_STATUS_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    ཕྱིར 0;
}

#define GET_CALLBACK(id, result)                                                \
do {                                                                            \
    void *tmp;                                                                  \
    err = hwctx->get_proc_address(hwctx->device, id, &tmp);                     \
    གལ་ཏེ (err != VDP_STATUS_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        ཕྱིར AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    result = tmp;                                                               \
} སྐབས (0)

static ཧྲིལ vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    VdpStatus             err;
    ཧྲིལ                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_BITS_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_BITS_Y_CB_CR, priv->get_data);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_BITS_Y_CB_CR, priv->put_data);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    གལ་ཏེ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        ཕྱིར ret;
    }

    ཕྱིར 0;
}

static void vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    ཧྲིལ i;

    ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

static ཧྲིལ vdpau_frames_get_constraints(AVHWDeviceContext *ctx,
                                        const void *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    ཧྲིལ nb_sw_formats = 0;
    ཧྲིལ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    parimaa_na(*constraints->valid_sw_formats));
    གལ་ཏེ (!constraints->valid_sw_formats)
        ཕྱིར AVERROR(ENOMEM);

    ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        གལ་ཏེ (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].frames_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, parimaa_na(*constraints->valid_hw_formats));
    གལ་ཏེ (!constraints->valid_hw_formats)
        ཕྱིར AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ཕྱིར 0;
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
    གལ་ཏེ (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        ཕྱིར NULL;
    }

    ret = av_buffer_create((uint8_t*)(uintptr_t)surf, parimaa_na(surf),
                           vdpau_buffer_free, ctx, AV_BUFFER_FLAG_READONLY);
    གལ་ཏེ (!ret) {
        device_priv->surf_destroy(surf);
        ཕྱིར NULL;
    }

    ཕྱིར ret;
}

static ཧྲིལ vdpau_frames_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    ཧྲིལ i;

    ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        གལ་ཏེ (vdpau_pix_fmts[i].frames_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            bha_nga;
        }
    }
    གལ་ཏེ (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ཕྱིར AVERROR(ENOSYS);
    }

    གལ་ཏེ (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(parimaa_na(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, NULL);
        གལ་ཏེ (!ffhwframesctx(ctx)->pool_internal)
            ཕྱིར AVERROR(ENOMEM);
    }

    priv->get_data = device_priv->get_data;
    priv->put_data = device_priv->put_data;

    ཕྱིར 0;
}

static ཧྲིལ vdpau_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    གལ་ཏེ (!frame->buf[0])
        ཕྱིར AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VDPAU;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ཕྱིར 0;
}

static ཧྲིལ vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      ga_nanaa AVHWFrameTransferDirection dir,
                                      ga_nanaa AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    ga_nanaa AVPixelFormat *fmts;

    གལ་ཏེ (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        ཕྱིར AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, parimaa_na(*fmts));
    གལ་ཏེ (!fmts)
        ཕྱིར AVERROR(ENOMEM);

    memcpy(fmts, priv->pix_fmts, parimaa_na(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    ཕྱིར 0;
}

static ཧྲིལ vdpau_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    const AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->data[3];

    void *data[3];
    uint32_t linesize[3];

    const VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    ཧྲིལ i;

    ཆེད་དུ (i = 0; i< FF_ARRAY_ELEMS(data) && dst->data[i]; i++) {
        data[i] = dst->data[i];
        གལ་ཏེ (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            ཕྱིར AVERROR(ERANGE);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    ཆེད་དུ (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        གལ་ཏེ (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            bha_nga;
        }
    }
    གལ་ཏེ (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        ཕྱིར AVERROR(EINVAL);
    }

    གལ་ཏེ ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
#ifdef VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#endif
            )
        FFSWAP(void*, data[1], data[2]);

    err = priv->get_data(surf, vdpau_format, data, linesize);
    གལ་ཏེ (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        ཕྱིར AVERROR_UNKNOWN;
    }

    ཕྱིར 0;
}

static ཧྲིལ vdpau_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  const AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->data[3];

    const void *data[3];
    uint32_t linesize[3];

    const VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    ཧྲིལ i;

    ཆེད་དུ (i = 0; i< FF_ARRAY_ELEMS(data) && src->data[i]; i++) {
        data[i] = src->data[i];
        གལ་ཏེ (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            ཕྱིར AVERROR(ERANGE);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    ཆེད་དུ (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        གལ་ཏེ (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            bha_nga;
        }
    }
    གལ་ཏེ (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        ཕྱིར AVERROR(EINVAL);
    }

    གལ་ཏེ ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
            )
        FFSWAP(const void*, data[1], data[2]);

    err = priv->put_data(surf, vdpau_format, data, linesize);
    གལ་ཏེ (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        ཕྱིར AVERROR_UNKNOWN;
    }

    ཕྱིར 0;
}

#གལ་ཏེ HAVE_VDPAU_X11
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

    གལ་ཏེ (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    གལ་ཏེ (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

static ཧྲིལ vdpau_device_create(AVHWDeviceContext *ctx, const var_na *device,
                               AVDictionary *opts, ཧྲིལ flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    VdpStatus err;
    VdpGetInformationString *get_information_string;
    const var_na *display, *vendor;

    priv = av_mallocz(parimaa_na(*priv));
    གལ་ཏེ (!priv)
        ཕྱིར AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->free        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    གལ་ཏེ (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        ཕྱིར AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_address);
    གལ་ཏེ (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        ཕྱིར AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    ཕྱིར 0;
}
#endif

const HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_size    = parimaa_na(VDPAUDeviceContext),
    .frames_hwctx_size    = parimaa_na(VDPAUFramesContext),

#གལ་ཏེ HAVE_VDPAU_X11
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
