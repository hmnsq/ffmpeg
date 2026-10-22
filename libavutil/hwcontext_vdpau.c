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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ <vdpau/vdpau.h>

#ଅନ୍ତର୍ଭାଵ "buffer.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_internal.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_vdpau.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "pixfmt.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VDPAUPixFmtMap {
    VdpYCbCrFormat vdpau_fmt;
    ଗଣନା AVPixelFormat pix_fmt;
} VDPAUPixFmtMap;

ସ୍ଥିର ଅଚଳ VDPAUPixFmtMap pix_fmts_420[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV12    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV420P },
#ifdef VDP_YCBCR_FORMAT_P016
    { VDP_YCBCR_FORMAT_P016, AV_PIX_FMT_P016    },
    { VDP_YCBCR_FORMAT_P010, AV_PIX_FMT_P010    },
#endif
    { 0,                     AV_PIX_FMT_NONE,   },
};

ସ୍ଥିର ଅଚଳ VDPAUPixFmtMap pix_fmts_422[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV16    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV422P },
    { VDP_YCBCR_FORMAT_UYVY, AV_PIX_FMT_UYVY422 },
    { VDP_YCBCR_FORMAT_YUYV, AV_PIX_FMT_YUYV422 },
    { 0,                     AV_PIX_FMT_NONE,   },
};

ସ୍ଥିର ଅଚଳ VDPAUPixFmtMap pix_fmts_444[] = {
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
    { VDP_YCBCR_FORMAT_Y_U_V_444, AV_PIX_FMT_YUV444P },
#endif
#ifdef VDP_YCBCR_FORMAT_P016
    {VDP_YCBCR_FORMAT_Y_U_V_444_16, AV_PIX_FMT_YUV444P16},
#endif
    { 0,                          AV_PIX_FMT_NONE,   },
};

ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    VdpChromaType chroma_type;
    ଗଣନା AVPixelFormat frames_sw_format;
    ଅଚଳ VDPAUPixFmtMap *map;
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VDPAUDeviceContext {
    /**
     * The public AVVDPAUDeviceContext. See hwcontext_vdpau.h for it.
     */
    AVVDPAUDeviceContext p;

    VdpVideoSurfaceQueryGetPutBitsYCbCrCapabilities *get_transfer_caps;
    VdpVideoSurfaceGetBitsYCbCr                     *get_data;
    VdpVideoSurfacePutBitsYCbCr                     *put_data;
    VdpVideoSurfaceCreate                           *surf_create;
    VdpVideoSurfaceDestroy                          *surf_destroy;

    ଗଣନା AVPixelFormat *pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VDPAUFramesContext {
    VdpVideoSurfaceGetBitsYCbCr *get_data;
    VdpVideoSurfacePutBitsYCbCr *put_data;
    VdpChromaType chroma_type;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା chroma_idx;

    ଅଚଳ ଗଣନା AVPixelFormat *pix_fmts;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା                       nb_pix_fmts;
} VDPAUFramesContext;

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_pixfmts(ଅଚଳ VDPAUPixFmtMap *map)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2 = 0;
    ଯେତେବେଳେ (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        ଗଣନା_2++;
    }
    ଫେରନ୍ତୁ ଗଣନା_2;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        ଅଚଳ VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_pix_fmts;

        nb_pix_fmts = ଗଣନା_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, ଆକାର(*priv->pix_fmts[i]));
        ଯଦି (!priv->pix_fmts[i])
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        ଯେତେବେଳେ (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            VdpStatus err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            ଯଦି (err == VDP_STATUS_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    ଫେରନ୍ତୁ 0;
}

#define GET_CALLBACK(id, result)                                                \
କର {                                                                            \
    ଶୂନ୍ୟ *tmp;                                                                  \
    err = hwctx->get_proc_address(hwctx->device, id, &tmp);                     \
    ଯଦି (err != VDP_STATUS_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    result = tmp;                                                               \
} ଯେତେବେଳେ (0)

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    VdpStatus             err;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_BITS_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_BITS_Y_CB_CR, priv->get_data);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_BITS_Y_CB_CR, priv->put_data);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    ଯଦି (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        ଫେରନ୍ତୁ ret;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vdpau_frames_get_constraints(AVHWDeviceContext *ctx,
                                        ଅଚଳ ଶୂନ୍ୟ *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_sw_formats = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    ଆକାର(*constraints->valid_sw_formats));
    ଯଦି (!constraints->valid_sw_formats)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        ଯଦି (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].frames_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ଆକାର(*constraints->valid_hw_formats));
    ଯଦି (!constraints->valid_hw_formats)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ vdpau_buffer_free(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)data;

    device_priv->surf_destroy(surf);
}

ସ୍ଥିର AVBufferRef *vdpau_pool_alloc(ଶୂନ୍ୟ *opaque, size_t size)
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
    ଯଦି (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ret = av_buffer_create((uint8_t*)(uintptr_t)surf, ଆକାର(surf),
                           vdpau_buffer_free, ctx, AV_BUFFER_FLAG_READONLY);
    ଯଦି (!ret) {
        device_priv->surf_destroy(surf);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vdpau_frames_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        ଯଦି (vdpau_pix_fmts[i].frames_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            ଭାଙ୍ଗ;
        }
    }
    ଯଦି (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    ଯଦି (!ctx->pool) {
        ffhwframesctx(ctx)->pool_internal =
            av_buffer_pool_init2(ଆକାର(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, ଖାଲି);
        ଯଦି (!ffhwframesctx(ctx)->pool_internal)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    priv->get_data = device_priv->get_data;
    priv->put_data = device_priv->put_data;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vdpau_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ଯଦି (!frame->buf[0])
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_VDPAU;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      ଗଣନା AVHWFrameTransferDirection dir,
                                      ଗଣନା AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    ଗଣନା AVPixelFormat *fmts;

    ଯଦି (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, ଆକାର(*fmts));
    ଯଦି (!fmts)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    memcpy(fmts, priv->pix_fmts, ଆକାର(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vdpau_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ଅଚଳ AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->data[3];

    ଶୂନ୍ୟ *data[3];
    uint32_t linesize[3];

    ଅଚଳ VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i< FF_ARRAY_ELEMS(data) && dst->data[i]; i++) {
        data[i] = dst->data[i];
        ଯଦି (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            ଫେରନ୍ତୁ AVERROR(ERANGE);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    ପାଇଁ (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        ଯଦି (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            ଭାଙ୍ଗ;
        }
    }
    ଯଦି (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ଯଦି ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
#ifdef VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#endif
            )
        FFSWAP(ଶୂନ୍ୟ*, data[1], data[2]);

    err = priv->get_data(surf, vdpau_format, data, linesize);
    ଯଦି (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vdpau_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                  ଅଚଳ AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->data[3];

    ଅଚଳ ଶୂନ୍ୟ *data[3];
    uint32_t linesize[3];

    ଅଚଳ VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    VdpStatus err;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; i< FF_ARRAY_ELEMS(data) && src->data[i]; i++) {
        data[i] = src->data[i];
        ଯଦି (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            ଫେରନ୍ତୁ AVERROR(ERANGE);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    ପାଇଁ (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        ଯଦି (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            ଭାଙ୍ଗ;
        }
    }
    ଯଦି (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    ଯଦି ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ifdef VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#endif
            )
        FFSWAP(ଅଚଳ ଶୂନ୍ୟ*, data[1], data[2]);

    err = priv->put_data(surf, vdpau_format, data, linesize);
    ଯଦି (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଫେରନ୍ତୁ 0;
}

#ଯଦି HAVE_VDPAU_X11
#ଅନ୍ତର୍ଭାଵ <vdpau/vdpau_x11.h>
#ଅନ୍ତର୍ଭାଵ <X11/Xlib.h>

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା VDPAUDevicePriv {
    VdpDeviceDestroy *device_destroy;
    Display *dpy;
} VDPAUDevicePriv;

ସ୍ଥିର ଶୂନ୍ୟ vdpau_device_free(AVHWDeviceContext *ctx)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;
    VDPAUDevicePriv       *priv = ctx->user_opaque;

    ଯଦି (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    ଯଦି (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା vdpau_device_create(AVHWDeviceContext *ctx, ଅଚଳ ଅକ୍ଷର *device,
                               AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    VdpStatus err;
    VdpGetInformationString *get_information_string;
    ଅଚଳ ଅକ୍ଷର *display, *vendor;

    priv = av_mallocz(ଆକାର(*priv));
    ଯଦି (!priv)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ମୁକ୍ତ        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    ଯଦି (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_address);
    ଯଦି (err != VDP_STATUS_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    ଫେରନ୍ତୁ 0;
}
#endif

ଅଚଳ HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_size    = ଆକାର(VDPAUDeviceContext),
    .frames_hwctx_size    = ଆକାର(VDPAUFramesContext),

#ଯଦି HAVE_VDPAU_X11
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

    .pix_fmts = (ଅଚଳ ଗଣନା AVPixelFormat[]){ AV_PIX_FMT_VDPAU, AV_PIX_FMT_NONE },
};
