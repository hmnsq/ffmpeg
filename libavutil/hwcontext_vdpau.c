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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <vdpau/vdpau.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_vdpau.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VDPAUPixFmtMap {
    VdpYCbCrFormat vdpau_fmt;
    ਗਿਣਤੀ AVPixelFormat pix_fmt;
} VDPAUPixFmtMap;

ਸਥਿਰ ਅਚਲ VDPAUPixFmtMap pix_fmts_420[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV12    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV420P },
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VDP_YCBCR_FORMAT_P016
    { VDP_YCBCR_FORMAT_P016, AV_PIX_FMT_P016    },
    { VDP_YCBCR_FORMAT_P010, AV_PIX_FMT_P010    },
#ਜੇ_ਅੰਤ
    { 0,                     AV_PIX_FMT_NONE,   },
};

ਸਥਿਰ ਅਚਲ VDPAUPixFmtMap pix_fmts_422[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV16    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV422P },
    { VDP_YCBCR_FORMAT_UYVY, AV_PIX_FMT_UYVY422 },
    { VDP_YCBCR_FORMAT_YUYV, AV_PIX_FMT_YUYV422 },
    { 0,                     AV_PIX_FMT_NONE,   },
};

ਸਥਿਰ ਅਚਲ VDPAUPixFmtMap pix_fmts_444[] = {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VDP_YCBCR_FORMAT_Y_U_V_444
    { VDP_YCBCR_FORMAT_Y_U_V_444, AV_PIX_FMT_YUV444P },
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VDP_YCBCR_FORMAT_P016
    {VDP_YCBCR_FORMAT_Y_U_V_444_16, AV_PIX_FMT_YUV444P16},
#ਜੇ_ਅੰਤ
    { 0,                          AV_PIX_FMT_NONE,   },
};

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    VdpChromaType chroma_type;
    ਗਿਣਤੀ AVPixelFormat ਚੌਖਟੇ_sw_format;
    ਅਚਲ VDPAUPixFmtMap *map;
} vdpau_pix_fmts[] = {
    { VDP_CHROMA_TYPE_420, AV_PIX_FMT_YUV420P, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422, AV_PIX_FMT_YUV422P, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444, AV_PIX_FMT_YUV444P, pix_fmts_444 },
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VDP_YCBCR_FORMAT_P016
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P10, pix_fmts_420 },
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P12, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422_16, AV_PIX_FMT_YUV422P10, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P10, pix_fmts_444 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P12, pix_fmts_444 },
#ਜੇ_ਅੰਤ
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VDPAUDeviceContext {
    /**
     * The public AVVDPAUDeviceContext. See hwcontext_vdpau.h for it.
     */
    AVVDPAUDeviceContext p;

    Vdp_Video_Surface_Query_Get_Put_ਬਿੱਟ_YCb_Cr_Capabilities *get_transfer_caps;
    Vdp_Video_Surface_Get_ਬਿੱਟ_YCb_Cr                     *get_ਅੰਕੜੇ;
    Vdp_Video_Surface_Put_ਬਿੱਟ_YCb_Cr                     *put_ਅੰਕੜੇ;
    VdpVideoSurfaceCreate                           *surf_create;
    VdpVideoSurfaceDestroy                          *surf_destroy;

    ਗਿਣਤੀ AVPixelFormat *pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
    ਪੂਰਨ              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VDPAUFramesContext {
    Vdp_Video_Surface_Get_ਬਿੱਟ_YCb_Cr *get_ਅੰਕੜੇ;
    Vdp_Video_Surface_Put_ਬਿੱਟ_YCb_Cr *put_ਅੰਕੜੇ;
    VdpChromaType chroma_type;
    ਪੂਰਨ chroma_idx;

    ਅਚਲ ਗਿਣਤੀ AVPixelFormat *pix_fmts;
    ਪੂਰਨ                       nb_pix_fmts;
} VDPAUFramesContext;

ਸਥਿਰ ਪੂਰਨ ਗਿਣਤੀ_pixfmts(ਅਚਲ VDPAUPixFmtMap *map)
{
    ਪੂਰਨ ਗਿਣਤੀ_2 = 0;
    ਜਦੋਂ (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        ਗਿਣਤੀ_2++;
    }
    ਵਾਪਸ ਗਿਣਤੀ_2;
}

ਸਥਿਰ ਪੂਰਨ vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        ਅਚਲ VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        ਪੂਰਨ nb_pix_fmts;

        nb_pix_fmts = ਗਿਣਤੀ_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, ਆਕਾਰ(*priv->pix_fmts[i]));
        ਜੇ (!priv->pix_fmts[i])
            ਵਾਪਸ AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        ਜਦੋਂ (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            Vdp_ਸਥਿਤੀ err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            ਜੇ (err == VDP_ਸਥਿਤੀ_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    ਵਾਪਸ 0;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET_CALLBACK(id, ਨਤੀਜਾ)                                                \
ਕਰੋ {                                                                            \
    ਖਾਲੀ *tmp;                                                                  \
    err = hwctx->get_proc_ਪਤਾ(hwctx->device, id, &tmp);                     \
    ਜੇ (err != VDP_ਸਥਿਤੀ_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        ਵਾਪਸ AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    ਨਤੀਜਾ = tmp;                                                               \
} ਜਦੋਂ (0)

ਸਥਿਰ ਪੂਰਨ vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    Vdp_ਸਥਿਤੀ             err;
    ਪੂਰਨ                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_ਬਿੱਟ_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_ਬਿੱਟ_Y_CB_CR, priv->get_ਅੰਕੜੇ);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_ਬਿੱਟ_Y_CB_CR, priv->put_ਅੰਕੜੇ);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    ਜੇ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        ਵਾਪਸ ret;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    ਪੂਰਨ i;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

ਸਥਿਰ ਪੂਰਨ vdpau_ਚੌਖਟੇ_get_constraints(AVHWDeviceContext *ctx,
                                        ਅਚਲ ਖਾਲੀ *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    ਪੂਰਨ nb_sw_formats = 0;
    ਪੂਰਨ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    ਆਕਾਰ(*constraints->valid_sw_formats));
    ਜੇ (!constraints->valid_sw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        ਜੇ (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].ਚੌਖਟੇ_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ਆਕਾਰ(*constraints->valid_hw_formats));
    ਜੇ (!constraints->valid_hw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ vdpau_ਬਫਰ_free(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)ਅੰਕੜੇ;

    device_priv->surf_destroy(surf);
}

ਸਥਿਰ AVBufferRef *vdpau_pool_alloc(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    AVHWFramesContext             *ctx = opaque;
    VDPAUFramesContext           *priv = ctx->hwctx;
    VDPAUDeviceContext    *device_priv = ctx->device_ctx->hwctx;
    AVVDPAUDeviceContext *device_hwctx = &device_priv->p;

    AVBufferRef *ret;
    VdpVideoSurface surf;
    Vdp_ਸਥਿਤੀ err;

    err = device_priv->surf_create(device_hwctx->device, priv->chroma_type,
                                   ctx->ਚੌੜਾਈ, ctx->ਉਚਾਈ, &surf);
    ਜੇ (err != VDP_ਸਥਿਤੀ_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        ਵਾਪਸ ਨਿਰਾ;
    }

    ret = av_ਬਫਰ_create((uint8_t*)(uintptr_t)surf, ਆਕਾਰ(surf),
                           vdpau_ਬਫਰ_free, ctx, AV_ਬਫਰ_FLAG_READONLY);
    ਜੇ (!ret) {
        device_priv->surf_destroy(surf);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ vdpau_ਚੌਖਟੇ_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    ਪੂਰਨ i;

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        ਜੇ (vdpau_pix_fmts[i].ਚੌਖਟੇ_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            ਰੋਕੋ;
        }
    }
    ਜੇ (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    ਜੇ (!ctx->pool) {
        ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ =
            av_ਬਫਰ_pool_init2(ਆਕਾਰ(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, ਨਿਰਾ);
        ਜੇ (!ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ)
            ਵਾਪਸ AVERROR(ENOMEM);
    }

    priv->get_ਅੰਕੜੇ = device_priv->get_ਅੰਕੜੇ;
    priv->put_ਅੰਕੜੇ = device_priv->put_ਅੰਕੜੇ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vdpau_get_ਬਫਰ(AVHWFramesContext *ctx, AVFrame *ਚੌਖਟਾ)
{
    ਚੌਖਟਾ->buf[0] = av_ਬਫਰ_pool_get(ctx->pool);
    ਜੇ (!ਚੌਖਟਾ->buf[0])
        ਵਾਪਸ AVERROR(ENOMEM);

    ਚੌਖਟਾ->ਅੰਕੜੇ[3] = ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ;
    ਚੌਖਟਾ->format  = AV_PIX_FMT_VDPAU;
    ਚੌਖਟਾ->ਚੌੜਾਈ   = ctx->ਚੌੜਾਈ;
    ਚੌਖਟਾ->ਉਚਾਈ  = ctx->ਉਚਾਈ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                      ਗਿਣਤੀ AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    ਗਿਣਤੀ AVPixelFormat *fmts;

    ਜੇ (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, ਆਕਾਰ(*fmts));
    ਜੇ (!fmts)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(fmts, priv->pix_fmts, ਆਕਾਰ(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vdpau_transfer_ਅੰਕੜੇ_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ਅਚਲ AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->ਅੰਕੜੇ[3];

    ਖਾਲੀ *ਅੰਕੜੇ[3];
    uint32_t linesize[3];

    ਅਚਲ VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    Vdp_ਸਥਿਤੀ err;
    ਪੂਰਨ i;

    ਲਈ (i = 0; i< FF_ARRAY_ELEMS(ਅੰਕੜੇ) && dst->ਅੰਕੜੇ[i]; i++) {
        ਅੰਕੜੇ[i] = dst->ਅੰਕੜੇ[i];
        ਜੇ (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            ਵਾਪਸ AVERROR(ERANGE);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    ਲਈ (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        ਜੇ (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            ਰੋਕੋ;
        }
    }
    ਜੇ (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ਜੇ ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#ਜੇ_ਅੰਤ
            )
        FFSWAP(ਖਾਲੀ*, ਅੰਕੜੇ[1], ਅੰਕੜੇ[2]);

    err = priv->get_ਅੰਕੜੇ(surf, vdpau_format, ਅੰਕੜੇ, linesize);
    ਜੇ (err != VDP_ਸਥਿਤੀ_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ vdpau_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ(AVHWFramesContext *ctx, AVFrame *dst,
                                  ਅਚਲ AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->ਅੰਕੜੇ[3];

    ਅਚਲ ਖਾਲੀ *ਅੰਕੜੇ[3];
    uint32_t linesize[3];

    ਅਚਲ VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    Vdp_ਸਥਿਤੀ err;
    ਪੂਰਨ i;

    ਲਈ (i = 0; i< FF_ARRAY_ELEMS(ਅੰਕੜੇ) && src->ਅੰਕੜੇ[i]; i++) {
        ਅੰਕੜੇ[i] = src->ਅੰਕੜੇ[i];
        ਜੇ (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            ਵਾਪਸ AVERROR(ERANGE);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    ਲਈ (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        ਜੇ (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            ਰੋਕੋ;
        }
    }
    ਜੇ (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ਜੇ ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#ਜੇ_ਅੰਤ
            )
        FFSWAP(ਅਚਲ ਖਾਲੀ*, ਅੰਕੜੇ[1], ਅੰਕੜੇ[2]);

    err = priv->put_ਅੰਕੜੇ(surf, vdpau_format, ਅੰਕੜੇ, linesize);
    ਜੇ (err != VDP_ਸਥਿਤੀ_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਵਾਪਸ 0;
}

#ਜੇ HAVE_VDPAU_X11
#ਅਨ੍ਤਰ੍ਭਾਵ <vdpau/vdpau_x11.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <X11/Xlib.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ VDPAUDevicePriv {
    VdpDeviceDestroy *device_destroy;
    Display *dpy;
} VDPAUDevicePriv;

ਸਥਿਰ ਖਾਲੀ vdpau_device_free(AVHWDeviceContext *ctx)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;
    VDPAUDevicePriv       *priv = ctx->user_opaque;

    ਜੇ (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    ਜੇ (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

ਸਥਿਰ ਪੂਰਨ vdpau_device_create(AVHWDeviceContext *ctx, ਅਚਲ ਅੱਖਰ *device,
                               AVDictionary *opts, ਪੂਰਨ flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    Vdp_ਸਥਿਤੀ err;
    VdpGetInformationString *get_information_string;
    ਅਚਲ ਅੱਖਰ *display, *vendor;

    priv = av_mallocz(ਆਕਾਰ(*priv));
    ਜੇ (!priv)
        ਵਾਪਸ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ਮੁਕਤ        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    ਜੇ (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        ਵਾਪਸ AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_ਪਤਾ);
    ਜੇ (err != VDP_ਸਥਿਤੀ_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    ਵਾਪਸ 0;
}
#ਜੇ_ਅੰਤ

ਅਚਲ HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_ਮਾਪ    = ਆਕਾਰ(VDPAUDeviceContext),
    .ਚੌਖਟੇ_hwctx_ਮਾਪ    = ਆਕਾਰ(VDPAUFramesContext),

#ਜੇ HAVE_VDPAU_X11
    .device_create        = vdpau_device_create,
#ਜੇ_ਅੰਤ
    .device_init          = vdpau_device_init,
    .device_uninit        = vdpau_device_uninit,
    .ਚੌਖਟੇ_get_constraints = vdpau_ਚੌਖਟੇ_get_constraints,
    .ਚੌਖਟੇ_init          = vdpau_ਚੌਖਟੇ_init,
    .ਚੌਖਟੇ_get_ਬਫਰ    = vdpau_get_ਬਫਰ,
    .transfer_get_formats = vdpau_transfer_get_formats,
    .transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ     = vdpau_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ,
    .transfer_ਅੰਕੜੇ_from   = vdpau_transfer_ਅੰਕੜੇ_from,

    .pix_fmts = (ਅਚਲ ਗਿਣਤੀ AVPixelFormat[]){ AV_PIX_FMT_VDPAU, AV_PIX_FMT_NONE },
};
