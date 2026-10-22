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

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ <vdpau/vdpau.h>

#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_vdpau.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VDPAUPixFmtMap {
    VdpYCbCrFormat vdpau_fmt;
    ಎಣಿಕೆ AVPixelFormat pix_fmt;
} VDPAUPixFmtMap;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VDPAUPixFmtMap pix_fmts_420[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV12    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV420P },
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VDP_YCBCR_FORMAT_P016
    { VDP_YCBCR_FORMAT_P016, AV_PIX_FMT_P016    },
    { VDP_YCBCR_FORMAT_P010, AV_PIX_FMT_P010    },
#ಆದರೆ_ಅಂತ್ಯ
    { 0,                     AV_PIX_FMT_NONE,   },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VDPAUPixFmtMap pix_fmts_422[] = {
    { VDP_YCBCR_FORMAT_NV12, AV_PIX_FMT_NV16    },
    { VDP_YCBCR_FORMAT_YV12, AV_PIX_FMT_YUV422P },
    { VDP_YCBCR_FORMAT_UYVY, AV_PIX_FMT_UYVY422 },
    { VDP_YCBCR_FORMAT_YUYV, AV_PIX_FMT_YUYV422 },
    { 0,                     AV_PIX_FMT_NONE,   },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ VDPAUPixFmtMap pix_fmts_444[] = {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VDP_YCBCR_FORMAT_Y_U_V_444
    { VDP_YCBCR_FORMAT_Y_U_V_444, AV_PIX_FMT_YUV444P },
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VDP_YCBCR_FORMAT_P016
    {VDP_YCBCR_FORMAT_Y_U_V_444_16, AV_PIX_FMT_YUV444P16},
#ಆದರೆ_ಅಂತ್ಯ
    { 0,                          AV_PIX_FMT_NONE,   },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    VdpChromaType chroma_type;
    ಎಣಿಕೆ AVPixelFormat ಚೌಕಟ್ಟುಗಳು_sw_format;
    ಸ್ಥಿರಾಂಕ VDPAUPixFmtMap *map;
} vdpau_pix_fmts[] = {
    { VDP_CHROMA_TYPE_420, AV_PIX_FMT_YUV420P, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422, AV_PIX_FMT_YUV422P, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444, AV_PIX_FMT_YUV444P, pix_fmts_444 },
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VDP_YCBCR_FORMAT_P016
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P10, pix_fmts_420 },
    { VDP_CHROMA_TYPE_420_16, AV_PIX_FMT_YUV420P12, pix_fmts_420 },
    { VDP_CHROMA_TYPE_422_16, AV_PIX_FMT_YUV422P10, pix_fmts_422 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P10, pix_fmts_444 },
    { VDP_CHROMA_TYPE_444_16, AV_PIX_FMT_YUV444P12, pix_fmts_444 },
#ಆದರೆ_ಅಂತ್ಯ
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VDPAUDeviceContext {
    /**
     * The public AVVDPAUDeviceContext. See hwcontext_vdpau.h for it.
     */
    AVVDPAUDeviceContext p;

    Vdp_Video_Surface_Query_Get_Put_ಬಿಟ್ಟುಗಳು_YCb_Cr_Capabilities *get_transfer_caps;
    Vdp_Video_Surface_Get_ಬಿಟ್ಟುಗಳು_YCb_Cr                     *get_ದತ್ತಾಂಶ;
    Vdp_Video_Surface_Put_ಬಿಟ್ಟುಗಳು_YCb_Cr                     *put_ದತ್ತಾಂಶ;
    VdpVideoSurfaceCreate                           *surf_create;
    VdpVideoSurfaceDestroy                          *surf_destroy;

    ಎಣಿಕೆ AVPixelFormat *pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
    ಪೂರ್ಣಾಂಕ              nb_pix_fmts[FF_ARRAY_ELEMS(vdpau_pix_fmts)];
} VDPAUDeviceContext;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VDPAUFramesContext {
    Vdp_Video_Surface_Get_ಬಿಟ್ಟುಗಳು_YCb_Cr *get_ದತ್ತಾಂಶ;
    Vdp_Video_Surface_Put_ಬಿಟ್ಟುಗಳು_YCb_Cr *put_ದತ್ತಾಂಶ;
    VdpChromaType chroma_type;
    ಪೂರ್ಣಾಂಕ chroma_idx;

    ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat *pix_fmts;
    ಪೂರ್ಣಾಂಕ                       nb_pix_fmts;
} VDPAUFramesContext;

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_pixfmts(ಸ್ಥಿರಾಂಕ VDPAUPixFmtMap *map)
{
    ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2 = 0;
    ಆಗ (map->pix_fmt != AV_PIX_FMT_NONE) {
        map++;
        ಎಣಿಕೆ_2++;
    }
    ಹಿಂತಿರುಗಿ ಎಣಿಕೆ_2;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vdpau_init_pixmfts(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++) {
        ಸ್ಥಿರಾಂಕ VDPAUPixFmtMap *map = vdpau_pix_fmts[i].map;
        ಪೂರ್ಣಾಂಕ nb_pix_fmts;

        nb_pix_fmts = ಎಣಿಕೆ_pixfmts(map);
        priv->pix_fmts[i] = av_malloc_array(nb_pix_fmts + 1, ಗಾತ್ರ(*priv->pix_fmts[i]));
        ಆದರೆ (!priv->pix_fmts[i])
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        nb_pix_fmts = 0;
        ಆಗ (map->pix_fmt != AV_PIX_FMT_NONE) {
            VdpBool supported;
            Vdp_ಸ್ಥಿತಿ err = priv->get_transfer_caps(hwctx->device, vdpau_pix_fmts[i].chroma_type,
                                                    map->vdpau_fmt, &supported);
            ಆದರೆ (err == VDP_ಸ್ಥಿತಿ_OK && supported)
                priv->pix_fmts[i][nb_pix_fmts++] = map->pix_fmt;
            map++;
        }
        priv->pix_fmts[i][nb_pix_fmts++] = AV_PIX_FMT_NONE;
        priv->nb_pix_fmts[i]             = nb_pix_fmts;
    }

    ಹಿಂತಿರುಗಿ 0;
}

#ವ್ಯಾಖ್ಯಾನಿಸು GET_CALLBACK(id, ಫಲಿತಾಂಶ)                                                \
ಮಾಡು {                                                                            \
    ಶೂನ್ಯ *tmp;                                                                  \
    err = hwctx->get_proc_ವಿಳಾಸ(hwctx->device, id, &tmp);                     \
    ಆದರೆ (err != VDP_ಸ್ಥಿತಿ_OK) {                                                 \
        av_log(ctx, AV_LOG_ERROR, "Error getting the " #id " callback.\n");     \
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;                                                 \
    }                                                                           \
    ಫಲಿತಾಂಶ = tmp;                                                               \
} ಆಗ (0)

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vdpau_device_init(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext    *priv = ctx->hwctx;
    AVVDPAUDeviceContext *hwctx = &priv->p;
    Vdp_ಸ್ಥಿತಿ             err;
    ಪೂರ್ಣಾಂಕ                   ret;

    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_QUERY_GET_PUT_ಬಿಟ್ಟುಗಳು_Y_CB_CR_CAPABILITIES,
                 priv->get_transfer_caps);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_GET_ಬಿಟ್ಟುಗಳು_Y_CB_CR, priv->get_ದತ್ತಾಂಶ);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_PUT_ಬಿಟ್ಟುಗಳು_Y_CB_CR, priv->put_ದತ್ತಾಂಶ);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_CREATE,           priv->surf_create);
    GET_CALLBACK(VDP_FUNC_ID_VIDEO_SURFACE_DESTROY,          priv->surf_destroy);

    ret = vdpau_init_pixmfts(ctx);
    ಆದರೆ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the supported pixel formats\n");
        ಹಿಂತಿರುಗಿ ret;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ vdpau_device_uninit(AVHWDeviceContext *ctx)
{
    VDPAUDeviceContext *priv = ctx->hwctx;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(priv->pix_fmts); i++)
        av_freep(&priv->pix_fmts[i]);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vdpau_ಚೌಕಟ್ಟುಗಳು_get_constraints(AVHWDeviceContext *ctx,
                                        ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext *priv  = ctx->hwctx;
    ಪೂರ್ಣಾಂಕ nb_sw_formats = 0;
    ಪೂರ್ಣಾಂಕ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    ಗಾತ್ರ(*constraints->valid_sw_formats));
    ಆದರೆ (!constraints->valid_sw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        ಆದರೆ (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].ಚೌಕಟ್ಟುಗಳು_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ಗಾತ್ರ(*constraints->valid_hw_formats));
    ಆದರೆ (!constraints->valid_hw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ vdpau_ಬಫರ್_free(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    AVHWFramesContext          *ctx = opaque;
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VdpVideoSurface            surf = (VdpVideoSurface)(uintptr_t)ದತ್ತಾಂಶ;

    device_priv->surf_destroy(surf);
}

ಸ್ಥಿರ AVBufferRef *vdpau_pool_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    AVHWFramesContext             *ctx = opaque;
    VDPAUFramesContext           *priv = ctx->hwctx;
    VDPAUDeviceContext    *device_priv = ctx->device_ctx->hwctx;
    AVVDPAUDeviceContext *device_hwctx = &device_priv->p;

    AVBufferRef *ret;
    VdpVideoSurface surf;
    Vdp_ಸ್ಥಿತಿ err;

    err = device_priv->surf_create(device_hwctx->device, priv->chroma_type,
                                   ctx->ಅಗಲ, ctx->ಎತ್ತರ, &surf);
    ಆದರೆ (err != VDP_ಸ್ಥಿತಿ_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error allocating a VDPAU video surface\n");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ret = av_ಬಫರ್_create((uint8_t*)(uintptr_t)surf, ಗಾತ್ರ(surf),
                           vdpau_ಬಫರ್_free, ctx, AV_ಬಫರ್_FLAG_READONLY);
    ಆದರೆ (!ret) {
        device_priv->surf_destroy(surf);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vdpau_ಚೌಕಟ್ಟುಗಳು_init(AVHWFramesContext *ctx)
{
    VDPAUDeviceContext *device_priv = ctx->device_ctx->hwctx;
    VDPAUFramesContext        *priv = ctx->hwctx;

    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        ಆದರೆ (vdpau_pix_fmts[i].ಚೌಕಟ್ಟುಗಳು_sw_format == ctx->sw_format) {
            priv->chroma_type = vdpau_pix_fmts[i].chroma_type;
            priv->chroma_idx  = i;
            priv->pix_fmts    = device_priv->pix_fmts[i];
            priv->nb_pix_fmts = device_priv->nb_pix_fmts[i];
            ನಿಲ್ಲಿಸು;
        }
    }
    ಆದರೆ (priv->nb_pix_fmts < 2) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported sw format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    ಆದರೆ (!ctx->pool) {
        ffhwframesctx(ctx)->pool_ಆಂತರಿಕ =
            av_ಬಫರ್_pool_init2(ಗಾತ್ರ(VdpVideoSurface), ctx,
                                 vdpau_pool_alloc, ಖಾಲಿ);
        ಆದರೆ (!ffhwframesctx(ctx)->pool_ಆಂತರಿಕ)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    priv->get_ದತ್ತಾಂಶ = device_priv->get_ದತ್ತಾಂಶ;
    priv->put_ದತ್ತಾಂಶ = device_priv->put_ದತ್ತಾಂಶ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vdpau_get_ಬಫರ್(AVHWFramesContext *ctx, AVFrame *ಚೌಕಟ್ಟು)
{
    ಚೌಕಟ್ಟು->buf[0] = av_ಬಫರ್_pool_get(ctx->pool);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[3] = ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ;
    ಚೌಕಟ್ಟು->format  = AV_PIX_FMT_VDPAU;
    ಚೌಕಟ್ಟು->ಅಗಲ   = ctx->ಅಗಲ;
    ಚೌಕಟ್ಟು->ಎತ್ತರ  = ctx->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                      ಎಣಿಕೆ AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->hwctx;

    ಎಣಿಕೆ AVPixelFormat *fmts;

    ಆದರೆ (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, ಗಾತ್ರ(*fmts));
    ಆದರೆ (!fmts)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಸ್ಮರಣೆ_ನಕಲು(fmts, priv->pix_fmts, ಗಾತ್ರ(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vdpau_transfer_ದತ್ತಾಂಶ_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)src->ದತ್ತಾಂಶ[3];

    ಶೂನ್ಯ *ದತ್ತಾಂಶ[3];
    uint32_t linesize[3];

    ಸ್ಥಿರಾಂಕ VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    Vdp_ಸ್ಥಿತಿ err;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i< FF_ARRAY_ELEMS(ದತ್ತಾಂಶ) && dst->ದತ್ತಾಂಶ[i]; i++) {
        ದತ್ತಾಂಶ[i] = dst->ದತ್ತಾಂಶ[i];
        ಆದರೆ (dst->linesize[i] < 0 || dst->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   dst->linesize[i]);
            ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
        }
        linesize[i] = dst->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    ಗಾಗಿ (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        ಆದರೆ (map[i].pix_fmt == dst->format) {
            vdpau_format = map[i].vdpau_fmt;
            ನಿಲ್ಲಿಸು;
        }
    }
    ಆದರೆ (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported target pixel format: %s\n",
               av_get_pix_fmt_name(dst->format));
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಆದರೆ ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VDP_YCBCR_FORMAT_P016
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444_16)
#ಆದರೆ_ಅಂತ್ಯ
            )
        FFSWAP(ಶೂನ್ಯ*, ದತ್ತಾಂಶ[1], ದತ್ತಾಂಶ[2]);

    err = priv->get_ದತ್ತಾಂಶ(surf, vdpau_format, ದತ್ತಾಂಶ, linesize);
    ಆದರೆ (err != VDP_ಸ್ಥಿತಿ_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error retrieving the data from a VDPAU surface\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vdpau_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ(AVHWFramesContext *ctx, AVFrame *dst,
                                  ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    VDPAUFramesContext *priv = ctx->hwctx;
    VdpVideoSurface     surf = (VdpVideoSurface)(uintptr_t)dst->ದತ್ತಾಂಶ[3];

    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ದತ್ತಾಂಶ[3];
    uint32_t linesize[3];

    ಸ್ಥಿರಾಂಕ VDPAUPixFmtMap *map;
    VdpYCbCrFormat vdpau_format;
    Vdp_ಸ್ಥಿತಿ err;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; i< FF_ARRAY_ELEMS(ದತ್ತಾಂಶ) && src->ದತ್ತಾಂಶ[i]; i++) {
        ದತ್ತಾಂಶ[i] = src->ದತ್ತಾಂಶ[i];
        ಆದರೆ (src->linesize[i] < 0 || src->linesize[i] > UINT32_MAX) {
            av_log(ctx, AV_LOG_ERROR,
                   "The linesize %d cannot be represented as uint32\n",
                   src->linesize[i]);
            ಹಿಂತಿರುಗಿ AVERROR(ERANGE);
        }
        linesize[i] = src->linesize[i];
    }

    map = vdpau_pix_fmts[priv->chroma_idx].map;
    ಗಾಗಿ (i = 0; map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        ಆದರೆ (map[i].pix_fmt == src->format) {
            vdpau_format = map[i].vdpau_fmt;
            ನಿಲ್ಲಿಸು;
        }
    }
    ಆದರೆ (map[i].pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "Unsupported source pixel format: %s\n",
               av_get_pix_fmt_name(src->format));
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಆದರೆ ((vdpau_format == VDP_YCBCR_FORMAT_YV12)
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ VDP_YCBCR_FORMAT_Y_U_V_444
            || (vdpau_format == VDP_YCBCR_FORMAT_Y_U_V_444)
#ಆದರೆ_ಅಂತ್ಯ
            )
        FFSWAP(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ*, ದತ್ತಾಂಶ[1], ದತ್ತಾಂಶ[2]);

    err = priv->put_ದತ್ತಾಂಶ(surf, vdpau_format, ದತ್ತಾಂಶ, linesize);
    ಆದರೆ (err != VDP_ಸ್ಥಿತಿ_OK) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the data to a VDPAU surface\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ HAVE_VDPAU_X11
#ಅನ್ತರ್ಭಾವ <vdpau/vdpau_x11.h>
#ಅನ್ತರ್ಭಾವ <X11/Xlib.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ VDPAUDevicePriv {
    VdpDeviceDestroy *device_destroy;
    Display *dpy;
} VDPAUDevicePriv;

ಸ್ಥಿರ ಶೂನ್ಯ vdpau_device_free(AVHWDeviceContext *ctx)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;
    VDPAUDevicePriv       *priv = ctx->user_opaque;

    ಆದರೆ (priv->device_destroy)
        priv->device_destroy(hwctx->device);
    ಆದರೆ (priv->dpy)
        XCloseDisplay(priv->dpy);
    av_freep(&priv);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ vdpau_device_create(AVHWDeviceContext *ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                               AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    AVVDPAUDeviceContext *hwctx = ctx->hwctx;

    VDPAUDevicePriv *priv;
    Vdp_ಸ್ಥಿತಿ err;
    VdpGetInformationString *get_information_string;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *display, *vendor;

    priv = av_mallocz(ಗಾತ್ರ(*priv));
    ಆದರೆ (!priv)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ಬಿಡುಗಡೆ        = vdpau_device_free;

    priv->dpy = XOpenDisplay(device);
    ಆದರೆ (!priv->dpy) {
        av_log(ctx, AV_LOG_ERROR, "Cannot open the X11 display %s.\n",
               XDisplayName(device));
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }
    display = XDisplayString(priv->dpy);

    err = vdp_device_create_x11(priv->dpy, XDefaultScreen(priv->dpy),
                                &hwctx->device, &hwctx->get_proc_ವಿಳಾಸ);
    ಆದರೆ (err != VDP_ಸ್ಥಿತಿ_OK) {
        av_log(ctx, AV_LOG_ERROR, "VDPAU device creation on X11 display %s failed.\n",
               display);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    GET_CALLBACK(VDP_FUNC_ID_GET_INFORMATION_STRING, get_information_string);
    GET_CALLBACK(VDP_FUNC_ID_DEVICE_DESTROY,         priv->device_destroy);

    get_information_string(&vendor);
    av_log(ctx, AV_LOG_VERBOSE, "Successfully created a VDPAU device (%s) on "
           "X11 display %s\n", vendor, display);

    ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_vdpau = {
    .type                 = AV_HWDEVICE_TYPE_VDPAU,
    .name                 = "VDPAU",

    .device_hwctx_ಗಾತ್ರ    = ಗಾತ್ರ(VDPAUDeviceContext),
    .ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ    = ಗಾತ್ರ(VDPAUFramesContext),

#ಆದರೆ HAVE_VDPAU_X11
    .device_create        = vdpau_device_create,
#ಆದರೆ_ಅಂತ್ಯ
    .device_init          = vdpau_device_init,
    .device_uninit        = vdpau_device_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_constraints = vdpau_ಚೌಕಟ್ಟುಗಳು_get_constraints,
    .ಚೌಕಟ್ಟುಗಳು_init          = vdpau_ಚೌಕಟ್ಟುಗಳು_init,
    .ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್    = vdpau_get_ಬಫರ್,
    .transfer_get_formats = vdpau_transfer_get_formats,
    .transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ     = vdpau_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ,
    .transfer_ದತ್ತಾಂಶ_from   = vdpau_transfer_ದತ್ತಾಂಶ_from,

    .pix_fmts = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat[]){ AV_PIX_FMT_VDPAU, AV_PIX_FMT_NONE },
};
