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

#समावेश "config.h"

#समावेश <stdint.h>
#समावेश <string.h>

#समावेश <vdpau/vdpau.h>

#समावेश "buffer.h"
#समावेश "common.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_internal.h"
#समावेश "hwcontext_vdpau.h"
#समावेश "mem.h"
#समावेश "pixfmt.h"
#समावेश "pixdesc.h"

प्रकार काष्ठा VDPAUPixFmtMap {
    VdpYCbCrFormat vdpau_fmt;
    क्रमागत AVPixelFormat pix_fmt;
} VDPAUPixFmtMap;

अटल स्थिर VDPAUPixFmtMap pix_fmts_420[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV12    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV420P },
#अगर_घोषित VDP_YCBCR_FORMAT_P016
    { VDP_YCBCR_FORMAT_P016, AV_PIX_FMT_P016    },
    { VDP_YCBCR_FORMAT_P010, AV_PIX_FMT_P010    },
#पूर्ण_अगर
    { 0,                     AV_PIX_FMT_NONE,   },
};

अटल स्थिर VDPAUPixFmtMap pix_fmts_422[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV16    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV422P },
    { VDP_YCBCR_FORMAT_UYVY, AV_PIX_FMT_UYVY422 },
    { VDP_YCBCR_FORMAT_YUYV, AV_PIX_FMT_YUYV422 },
    { 0,                     AV_PIX_FMT_NONE,   },
};

अटल स्थिर VDPAUPixFmtMap pix_fmts_444[] = {
#अगर_घोषित VDP_YCBCR_FORMAT_Y_U_V_444
    { VDP_YCBCR_FORMAT_Y_U_V_444, AV_PIX_FMT_YUV444P },
#पूर्ण_अगर
#अगर_घोषित VDP_YCBCR_FORMAT_P016
    {VDP_YCBCR_FORMAT_Y_U_V_444_16, AV_PIX_FMT_YUV444P16},
#पूर्ण_अगर
    { 0,                          AV_PIX_FMT_NONE,   },
};

अटल स्थिर काष्ठा {
    VdpChromaType chroma_type;
    क्रमागत AVPixelFormat frames_sw_format;
    स्थिर VDPAUPixFmtMap *map;
} vdpau_pix_fmts[] = {
    { VDP_CHROMA_TYPE_420, AV_PIX_FMT_YUV420P, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422, AV_PIX_FMT_YUV422P, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444, AV_PIX_FMT_YUV444P, pix_fmts_444 },
#अगर_घोषित VDP_YCBCR_FORMAT_P016
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P10, pix_fmts_420 },
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P12, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422_16, AV_PIX_FMT_YUV422P10, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P10, pix_fmts_444 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P12, pix_fmts_444 },
#पूर्ण_अगर
};

प्रकार काष्ठा VDPAUDeviceContext {
    /**
     * The public AVVDPAUDeviceContext. See hwcontext_vdpau.h for it.
     */
    AVVDPAUDeviceContext p;

    VdpVideoSurfaceQueryGetPutBitsYCbCrCapabilities *get_transfer_caps;
    VdpVideoSurfaceGetBitsYCbCr                     *get_तथ्य;
    VdpVideoSurfacePutBitsYCbCr                     *put_तथ्य;
    VdpVideoSurfaceCreate                           *surf_create;
    VdpVideoSurfaceDestroy                          *surf_destroy;

    क्रमागत AVPixelFormat *pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
    पूर्णांक              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

प्रकार काष्ठा VDPAUFramesContext {
    VdpVideoSurfaceGetBitsYCbCr *get_तथ्य;
    VdpVideoSurfacePutBitsYCbCr *put_तथ्य;
    VdpChromaType chroma_type;
    पूर्णांक chroma_idx;

    स्थिर क्रमागत AVPixelFormat *pix_fmts;
    पूर्णांक                       nb_pix_fmts;
} VDPAUFramesContext;

अटल पूर्णांक गिनती_pixfmts(स्थिर VDPAUPixFmtMap *map)
{
    पूर्णांक गिनती = 0;
    जबतक (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        गिनती++;
    }
    वापस गिनती;
}

अटल पूर्णांक vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    पूर्णांक i;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        स्थिर VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        पूर्णांक nb_pix_fmts;

        nb_pix_fmts = गिनती_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, माप(*priv->pix_fmts[i]));
        अगर (!priv->pix_fmts[i])
            वापस AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        जबतक (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            VdpStatus err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            अगर (err == VDP_STATUS_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    वापस 0;
}

#घोषणा GET_CALLBACK(id, परिणाम)                                                \
करो {                                                                            \
    व्योम *tmp;                                                                  \
    err = hwctx->get_proc_address(hwctx->device, id, &tmp);                     \
    अगर (err != VDP_STATUS_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        वापस AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    परिणाम = tmp;                                                               \
} जबतक (0)

अटल पूर्णांक vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    VdpStatus             err;
    पूर्णांक                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_BITS_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_BITS_Y_CB_CR, priv->get_तथ्य);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_BITS_Y_CB_CR, priv->put_तथ्य);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    अगर (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        वापस ret;
    }

    वापस 0;
}

अटल व्योम vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    पूर्णांक i;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

अटल पूर्णांक vdpau_frames_get_constraints(AVHWDeviceContext *ctx,
                                        स्थिर व्योम *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    पूर्णांक nb_sw_formats = 0;
    पूर्णांक i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    माप(*constraints->valid_sw_formats));
    अगर (!constraints->valid_sw_formats)
        वापस AVERROR(ENOMEM);

    क्रम (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        अगर (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].frames_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, माप(*constraints->valid_hw_formats));
    अगर (!constraints->valid_hw_formats)
        वापस AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    वापस 0;
}

अटल व्योम vdpau_बफर_free(व्योम *opaque, uint8_t *तथ्य)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)तथ्य;

    device_priv->surf_destroy(surf);
}

अटल AVBufferRef *vdpau_pool_alloc(व्योम *opaque, माप_प्रकार आकार)
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
    अगर (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        वापस शून्य;
    }

    ret = av_बफर_create((uint8_t*)(uintptr_t)surf, माप(surf),
                           vdpau_बफर_free, ctx, AV_बफर_FLAG_READONLY);
    अगर (!ret) {
        device_priv->surf_destroy(surf);
        वापस शून्य;
    }

    वापस ret;
}

अटल पूर्णांक vdpau_frames_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    पूर्णांक i;

    क्रम (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        अगर (vdpau_pix_fmts[i].frames_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            अवरोध;
        }
    }
    अगर (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        वापस AVERROR(ENOSYS);
    }

    अगर (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal =
            av_बफर_pool_init2(माप(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, शून्य);
        अगर (!ffhwframesctx(ctx)->pool_internal)
            वापस AVERROR(ENOMEM);
    }

    priv->get_तथ्य = device_priv->get_तथ्य;
    priv->put_तथ्य = device_priv->put_तथ्य;

    वापस 0;
}

अटल पूर्णांक vdpau_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    अगर (!frame->buf[0])
        वापस AVERROR(ENOMEM);

    frame->तथ्य[3] = frame->buf[0]->तथ्य;
    frame->format  = AV_PIX_FMT_VDPAU;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    वापस 0;
}

अटल पूर्णांक vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      क्रमागत AVHWFrameTransferDirection dir,
                                      क्रमागत AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    क्रमागत AVPixelFormat *fmts;

    अगर (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        वापस AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, माप(*fmts));
    अगर (!fmts)
        वापस AVERROR(ENOMEM);

    स_नकल(fmts, priv->pix_fmts, माप(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    वापस 0;
}

अटल पूर्णांक vdpau_transfer_तथ्य_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    स्थिर AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->तथ्य[3];

    व्योम *तथ्य[3];
    uint32_t linesize[3];

    स्थिर VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    पूर्णांक i;

    क्रम (i = 0; i< FF_ARRAY_ELEMS(तथ्य) && dst->तथ्य[i]; i++) {
        तथ्य[i] = dst->तथ्य[i];
        अगर (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            वापस AVERROR(दुस्फल);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    क्रम (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        अगर (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            अवरोध;
        }
    }
    अगर (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        वापस AVERROR(EINVAL);
    }

    अगर ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#अगर_घोषित VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#पूर्ण_अगर
#अगर_घोषित VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#पूर्ण_अगर
            )
        FFSWAP(व्योम*, तथ्य[1], तथ्य[2]);

    err = priv->get_तथ्य(surf, vdpau_format, तथ्य, linesize);
    अगर (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        वापस AVERROR_UNKNOWN;
    }

    वापस 0;
}

अटल पूर्णांक vdpau_transfer_तथ्य_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  स्थिर AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->तथ्य[3];

    स्थिर व्योम *तथ्य[3];
    uint32_t linesize[3];

    स्थिर VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    पूर्णांक i;

    क्रम (i = 0; i< FF_ARRAY_ELEMS(तथ्य) && src->तथ्य[i]; i++) {
        तथ्य[i] = src->तथ्य[i];
        अगर (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            वापस AVERROR(दुस्फल);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    क्रम (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        अगर (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            अवरोध;
        }
    }
    अगर (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        वापस AVERROR(EINVAL);
    }

    अगर ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#अगर_घोषित VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#पूर्ण_अगर
            )
        FFSWAP(स्थिर व्योम*, तथ्य[1], तथ्य[2]);

    err = priv->put_तथ्य(surf, vdpau_format, तथ्य, linesize);
    अगर (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        वापस AVERROR_UNKNOWN;
    }

    वापस 0;
}

#अगर HAVE_VDPAU_X11
#समावेश <vdpau/vdpau_x11.h>
#समावेश <X11/Xlib.h>

प्रकार काष्ठा VDPAUDevicePriv {
    VdpDeviceDestroy *device_destroy;
    Display *dpy;
} VDPAUDevicePriv;

अटल व्योम vdpau_device_free(AVHWDeviceContext *ctx)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;
    VDPAUDevicePriv       *priv = ctx->user_opaque;

    अगर (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    अगर (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

अटल पूर्णांक vdpau_device_create(AVHWDeviceContext *ctx, स्थिर अक्षर *device,
                               AVDictionary *opts, पूर्णांक flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    VdpStatus err;
    VdpGetInformationString *get_information_string;
    स्थिर अक्षर *display, *vendor;

    priv = av_mallocz(माप(*priv));
    अगर (!priv)
        वापस AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->मुक्त        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    अगर (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        वापस AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_address);
    अगर (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        वापस AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    वापस 0;
}
#पूर्ण_अगर

स्थिर HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_आकार    = माप(VDPAUDeviceContext),
    .frames_hwctx_आकार    = माप(VDPAUFramesContext),

#अगर HAVE_VDPAU_X11
    .device_create        = vdpau_device_create,
#पूर्ण_अगर
    .device_init          = vdpau_device_init,
    .device_uninit        = vdpau_device_uninit,
    .frames_get_constraints = vdpau_frames_get_constraints,
    .frames_init          = vdpau_frames_init,
    .frames_get_बफर    = vdpau_get_बफर,
    .transfer_get_formats = vdpau_transfer_get_formats,
    .transfer_तथ्य_to     = vdpau_transfer_तथ्य_to,
    .transfer_तथ्य_from   = vdpau_transfer_तथ्य_from,

    .pix_fmts = (स्थिर क्रमागत AVPixelFormat[]){ AV_PIX_FMT_VDPAU, AV_PIX_FMT_NONE },
};
