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

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "frame_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ HWContextType * ಸ್ಥಿರಾಂಕ hw_ಕೋಷ್ಟಕ[] = {
#ಆದರೆ CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_QSV
    &ff_hwcontext_type_qsv,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_AMF
    &ff_hwcontext_type_amf,
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#ಆದರೆ_ಅಂತ್ಯ
    ಖಾಲಿ,
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸ್ಥಿರಾಂಕ hw_type_ಹೆಸರುಗಳು[] = {
    [AV_HWDEVICE_TYPE_CUDA]   = "cuda",
    [AV_HWDEVICE_TYPE_DRM]    = "drm",
    [AV_HWDEVICE_TYPE_DXVA2]  = "dxva2",
    [AV_HWDEVICE_TYPE_D3D11VA] = "d3d11va",
    [AV_HWDEVICE_TYPE_D3D12VA] = "d3d12va",
    [AV_HWDEVICE_TYPE_OPENCL] = "opencl",
    [AV_HWDEVICE_TYPE_QSV]    = "qsv",
    [AV_HWDEVICE_TYPE_VAAPI]  = "vaapi",
    [AV_HWDEVICE_TYPE_VDPAU]  = "vdpau",
    [AV_HWDEVICE_TYPE_VIDEOTOOLBOX] = "videotoolbox",
    [AV_HWDEVICE_TYPE_MEDIACODEC] = "mediacodec",
    [AV_HWDEVICE_TYPE_VULKAN] = "vulkan",
    [AV_HWDEVICE_TYPE_AMF] = "amf",
    [AV_HWDEVICE_TYPE_OHCODEC] = "ohcodec",
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    ಸ್ಥಿರಾಂಕ HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *ಮೂಲ_device;
} FFHWDeviceContext;

ಎಣಿಕೆ AVHWDeviceType av_hwdevice_ಕಂಡುಹಿಡಿ_type_by_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಪೂರ್ಣಾಂಕ type;
    ಗಾಗಿ (type = 0; type < FF_ARRAY_ELEMS(hw_type_ಹೆಸರುಗಳು); type++) {
        ಆದರೆ (hw_type_ಹೆಸರುಗಳು[type] && !strcmp(hw_type_ಹೆಸರುಗಳು[type], name))
            ಹಿಂತಿರುಗಿ type;
    }
    ಹಿಂತಿರುಗಿ AV_HWDEVICE_TYPE_NONE;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_hwdevice_get_type_name(ಎಣಿಕೆ AVHWDeviceType type)
{
    ಆದರೆ (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_ಹೆಸರುಗಳು))
        ಹಿಂತಿರುಗಿ hw_type_ಹೆಸರುಗಳು[type];
    ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಎಣಿಕೆ AVHWDeviceType av_hwdevice_iterate_types(ಎಣಿಕೆ AVHWDeviceType prev)
{
    ಎಣಿಕೆ AVHWDeviceType ಮುಂದಿನ;
    ಪೂರ್ಣಾಂಕ i, ಗಣ = 0;
    ಗಾಗಿ (i = 0; hw_ಕೋಷ್ಟಕ[i]; i++) {
        ಆದರೆ (prev != AV_HWDEVICE_TYPE_NONE && hw_ಕೋಷ್ಟಕ[i]->type <= prev)
            ಮುಂದುವರಿ;
        ಆದರೆ (!ಗಣ || hw_ಕೋಷ್ಟಕ[i]->type < ಮುಂದಿನ) {
            ಮುಂದಿನ = hw_ಕೋಷ್ಟಕ[i]->type;
            ಗಣ = 1;
        }
    }
    ಹಿಂತಿರುಗಿ ಗಣ ? ಮುಂದಿನ : AV_HWDEVICE_TYPE_NONE;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hwdevice_ctx_get_name(ಶೂನ್ಯ *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    ಹಿಂತಿರುಗಿ ctx->hw_type->name;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .ಅಂಶ_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .ಆವೃತ್ತಿ    = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
};

ಸ್ಥಿರ ಶೂನ್ಯ hwdevice_ctx_free(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ದತ್ತಾಂಶ;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    ಆದರೆ (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    ಆದರೆ (ctx->ಬಿಡುಗಡೆ)
        ctx->ಬಿಡುಗಡೆ(ctx);

    av_ಬಫರ್_unref(&ctxi->ಮೂಲ_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(ಎಣಿಕೆ AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    ಸ್ಥಿರಾಂಕ HWContextType *hw_type = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ i;

    ಗಾಗಿ (i = 0; hw_ಕೋಷ್ಟಕ[i]; i++) {
        ಆದರೆ (hw_ಕೋಷ್ಟಕ[i]->type == type) {
            hw_type = hw_ಕೋಷ್ಟಕ[i];
            ನಿಲ್ಲಿಸು;
        }
    }
    ಆದರೆ (!hw_type)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ctxi = av_mallocz(ಗಾತ್ರ(*ctxi));
    ಆದರೆ (!ctxi)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ctx = &ctxi->p;

    ಆದರೆ (hw_type->device_hwctx_ಗಾತ್ರ) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_ಗಾತ್ರ);
        ಆದರೆ (!ctx->hwctx)
            ಹೋಗು fail;
    }

    buf = av_ಬಫರ್_create((uint8_t*)ctx, ಗಾತ್ರ(*ctx),
                           hwdevice_ctx_free, ಖಾಲಿ,
                           AV_ಬಫರ್_FLAG_READONLY);
    ಆದರೆ (!buf)
        ಹೋಗು fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    ಹಿಂತಿರುಗಿ buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಪೂರ್ಣಾಂಕ av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->ದತ್ತಾಂಶ;
    AVHWDeviceContext *ctx  = &ctxi->p;
    ಪೂರ್ಣಾಂಕ ret = 0;

    ಆದರೆ (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .ಅಂಶ_name  = av_default_ಅಂಶ_name,
    .ಆವೃತ್ತಿ    = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
};

ಸ್ಥಿರ ಶೂನ್ಯ hwframe_ctx_free(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ದತ್ತಾಂಶ;
    AVHWFramesContext *ctx  = &ctxi->p;

    ಆದರೆ (ctxi->pool_ಆಂತರಿಕ)
        av_ಬಫರ್_pool_uninit(&ctxi->pool_ಆಂತರಿಕ);

    av_ಬಫರ್_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_ಬೀಗ);

    ಆದರೆ (ctxi->hw_type->ಚೌಕಟ್ಟುಗಳು_uninit)
        ctxi->hw_type->ಚೌಕಟ್ಟುಗಳು_uninit(ctx);

    ಆದರೆ (ctx->ಬಿಡುಗಡೆ)
        ctx->ಬಿಡುಗಡೆ(ctx);

    av_ಬಫರ್_unref(&ctxi->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು);

    av_ಬಫರ್_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_ಒಳ)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_ಒಳ->ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = ಖಾಲಿ;

    ctxi = av_mallocz(ಗಾತ್ರ(*ctxi));
    ಆದರೆ (!ctxi)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ctx  = &ctxi->p;

    ಆದರೆ (ff_mutex_init(&ctxi->transfer_pool_ಬೀಗ, ಖಾಲಿ)) {
        av_free(ctxi);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (hw_type->ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ) {
        ctx->hwctx = av_mallocz(hw_type->ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ);
        ಆದರೆ (!ctx->hwctx)
            ಹೋಗು fail;
    }

    device_ref = av_ಬಫರ್_ref(device_ref_ಒಳ);
    ಆದರೆ (!device_ref)
        ಹೋಗು fail;

    buf = av_ಬಫರ್_create((uint8_t*)ctx, ಗಾತ್ರ(*ctx),
                           hwframe_ctx_free, ಖಾಲಿ,
                           AV_ಬಫರ್_FLAG_READONLY);
    ಆದರೆ (!buf)
        ಹೋಗು fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    ಹಿಂತಿರುಗಿ buf;

fail:
    av_ಬಫರ್_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_ಬೀಗ);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->ದತ್ತಾಂಶ;
    AVFrame **ಚೌಕಟ್ಟುಗಳು;
    ಪೂರ್ಣಾಂಕ i, ret = 0;

    ಚೌಕಟ್ಟುಗಳು = av_calloc(ctx->initial_pool_ಗಾತ್ರ, ಗಾತ್ರ(*ಚೌಕಟ್ಟುಗಳು));
    ಆದರೆ (!ಚೌಕಟ್ಟುಗಳು)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (i = 0; i < ctx->initial_pool_ಗಾತ್ರ; i++) {
        ಚೌಕಟ್ಟುಗಳು[i] = av_ಚೌಕಟ್ಟು_alloc();
        ಆದರೆ (!ಚೌಕಟ್ಟುಗಳು[i])
            ಹೋಗು fail;

        ret = av_hwframe_get_ಬಫರ್(ref, ಚೌಕಟ್ಟುಗಳು[i], 0);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;
    }

fail:
    ಗಾಗಿ (i = 0; i < ctx->initial_pool_ಗಾತ್ರ; i++)
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟುಗಳು[i]);
    av_freep(&ಚೌಕಟ್ಟುಗಳು);

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->ದತ್ತಾಂಶ;
    AVHWFramesContext *ctx  = &ctxi->p;
    ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat *pix_fmt;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (ctxi->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು) {
        /* A derived frame context is already initialised. */
        ಹಿಂತಿರುಗಿ 0;
    }

    /* validate the pixel format */
    ಗಾಗಿ (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        ಆದರೆ (*pix_fmt == ctx->format)
            ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_ಗಾತ್ರ(ctx->ಅಗಲ, ctx->ಎತ್ತರ, 0, ctx);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    /* format-specific init */
    ಆದರೆ (ctxi->hw_type->ಚೌಕಟ್ಟುಗಳು_init) {
        ret = ctxi->hw_type->ಚೌಕಟ್ಟುಗಳು_init(ctx);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
    }

    ಆದರೆ (ctxi->pool_ಆಂತರಿಕ && !ctx->pool)
        ctx->pool = ctxi->pool_ಆಂತರಿಕ;

    /* preallocate the frames in the pool, if requested */
    ಆದರೆ (ctx->initial_pool_ಗಾತ್ರ > 0) {
        ret = hwframe_pool_prealloc(ref);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                    ಎಣಿಕೆ AVPixelFormat **formats, ಪೂರ್ಣಾಂಕ flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->ದತ್ತಾಂಶ;

    ಆದರೆ (!ctxi->hw_type->transfer_get_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);

    ಹಿಂತಿರುಗಿ ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

ಸ್ಥಿರ ಶೂನ್ಯ transfer_pool_free(ಶೂನ್ಯ *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_ಬಫರ್_unref(&device_ref);
}

ಸ್ಥಿರ AVBufferRef *transfer_ಬಫರ್_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = ಖಾಲಿ;

    ff_mutex_ಬೀಗ(&ctxi->transfer_pool_ಬೀಗ);
    ಆದರೆ (ctxi->transfer_pool_ಗಾತ್ರ != ಗಾತ್ರ_2) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_ಬಫರ್_alloc ?
                                  av_ಬಫರ್_ref(ctxi->p.device_ref) : ಖಾಲಿ;

        av_ಬಫರ್_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_ಬಫರ್_pool_init2(ಗಾತ್ರ_2, device_ref,
                                 ctxi->hw_type->transfer_ಬಫರ್_alloc,
                                 transfer_pool_free) :
            av_ಬಫರ್_pool_init(ಗಾತ್ರ_2, ಖಾಲಿ);
        ctxi->transfer_pool_ಗಾತ್ರ = ctxi->transfer_pool ? ಗಾತ್ರ_2 : 0;
        ಆದರೆ (!ctxi->transfer_pool)
            av_ಬಫರ್_unref(&device_ref);
    }
    ಆದರೆ (ctxi->transfer_pool)
        buf = av_ಬಫರ್_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_ಬೀಗ);

    ಹಿಂತಿರುಗಿ buf ? buf : av_ಬಫರ್_alloc(ಗಾತ್ರ_2);
}

ಪೂರ್ಣಾಂಕ av_hwframe_get_transfer_ಬಫರ್(AVBufferRef *hwframe_ctx, AVFrame *ಚೌಕಟ್ಟು)
{
    ಹಿಂತಿರುಗಿ ff_ಚೌಕಟ್ಟು_get_video_ಬಫರ್(ಚೌಕಟ್ಟು, 0, transfer_ಬಫರ್_alloc,
                                     hwframe_ctx->ದತ್ತಾಂಶ);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ transfer_ದತ್ತಾಂಶ_alloc(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    AVHWFramesContext *ctx;
    AVFrame *ಚೌಕಟ್ಟು_tmp;
    ಪೂರ್ಣಾಂಕ ret = 0;

    ಆದರೆ (!src->hw_ಚೌಕಟ್ಟುಗಳು_ctx)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;

    ಚೌಕಟ್ಟು_tmp = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!ಚೌಕಟ್ಟು_tmp)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    ಆದರೆ (dst->format >= 0) {
        ಚೌಕಟ್ಟು_tmp->format = dst->format;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಎಣಿಕೆ AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        ಆದರೆ (ret < 0)
            ಹೋಗು fail;
        ಚೌಕಟ್ಟು_tmp->format = formats[0];
        av_freep(&formats);
    }
    ಚೌಕಟ್ಟು_tmp->ಅಗಲ  = ctx->ಅಗಲ;
    ಚೌಕಟ್ಟು_tmp->ಎತ್ತರ = ctx->ಎತ್ತರ;

    ret = av_hwframe_get_transfer_ಬಫರ್(src->hw_ಚೌಕಟ್ಟುಗಳು_ctx, ಚೌಕಟ್ಟು_tmp);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    ret = av_hwframe_transfer_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು_tmp, src, flags);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    ಚೌಕಟ್ಟು_tmp->ಅಗಲ  = src->ಅಗಲ;
    ಚೌಕಟ್ಟು_tmp->ಎತ್ತರ = src->ಎತ್ತರ;

    av_ಚೌಕಟ್ಟು_move_ref(dst, ಚೌಕಟ್ಟು_tmp);

fail:
    av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು_tmp);
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_hwframe_transfer_ದತ್ತಾಂಶ(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!dst->buf[0])
        ಹಿಂತಿರುಗಿ transfer_ದತ್ತಾಂಶ_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    ಆದರೆ (src->hw_ಚೌಕಟ್ಟುಗಳು_ctx && dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;

        ಆದರೆ (src_ctx->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        }

        ಆದರೆ (dst_ctx->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        ಆದರೆ (src_ctx->hw_type->transfer_ದತ್ತಾಂಶ_from)
            ret = src_ctx->hw_type->transfer_ದತ್ತಾಂಶ_from(&src_ctx->p, dst, src);
        ಆದರೆ (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ)
            ret = dst_ctx->hw_type->transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ(&dst_ctx->p, dst, src);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (src->hw_ಚೌಕಟ್ಟುಗಳು_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;

            ಆದರೆ (!ctx->hw_type->transfer_ದತ್ತಾಂಶ_from)
                ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_ದತ್ತಾಂಶ_from(&ctx->p, dst, src);
            ಆದರೆ (ret < 0)
                ಹಿಂತಿರುಗಿ ret;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;

            ಆದರೆ (!ctx->hw_type->transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ)
                ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ(&ctx->p, dst, src);
            ಆದರೆ (ret < 0)
                ಹಿಂತಿರುಗಿ ret;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        }
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_hwframe_get_ಬಫರ್(AVBufferRef *hwframe_ref, AVFrame *ಚೌಕಟ್ಟು, ಪೂರ್ಣಾಂಕ flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->ದತ್ತಾಂಶ;
    AVHWFramesContext *ctx  = &ctxi->p;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (ctxi->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_ಚೌಕಟ್ಟು;

        ಚೌಕಟ್ಟು->format = ctx->format;
        ಚೌಕಟ್ಟು->hw_ಚೌಕಟ್ಟುಗಳು_ctx = av_ಬಫರ್_ref(hwframe_ref);
        ಆದರೆ (!ಚೌಕಟ್ಟು->hw_ಚೌಕಟ್ಟುಗಳು_ctx)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        src_ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
        ಆದರೆ (!src_ಚೌಕಟ್ಟು)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        ret = av_hwframe_get_ಬಫರ್(ctxi->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು,
                                    src_ಚೌಕಟ್ಟು, 0);
        ಆದರೆ (ret < 0) {
            av_ಚೌಕಟ್ಟು_free(&src_ಚೌಕಟ್ಟು);
            ಹಿಂತಿರುಗಿ ret;
        }

        ret = av_hwframe_map(ಚೌಕಟ್ಟು, src_ಚೌಕಟ್ಟು,
                             ctxi->ಮೂಲ_ಹಂಚಿಕೆ_map_flags);
        ಆದರೆ (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_ಚೌಕಟ್ಟು_free(&src_ಚೌಕಟ್ಟು);
            ಹಿಂತಿರುಗಿ ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_ಚೌಕಟ್ಟು_free(&src_ಚೌಕಟ್ಟು);

        ಹಿಂತಿರುಗಿ 0;
    }

    ಆದರೆ (!ctxi->hw_type->ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್)
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);

    ಆದರೆ (!ctx->pool)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಚೌಕಟ್ಟು->hw_ಚೌಕಟ್ಟುಗಳು_ctx = av_ಬಫರ್_ref(hwframe_ref);
    ಆದರೆ (!ಚೌಕಟ್ಟು->hw_ಚೌಕಟ್ಟುಗಳು_ctx)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ret = ctxi->hw_type->ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್(ctx, ಚೌಕಟ್ಟು);
    ಆದರೆ (ret < 0) {
        av_ಬಫರ್_unref(&ಚೌಕಟ್ಟು->hw_ಚೌಕಟ್ಟುಗಳು_ctx);
        ಹಿಂತಿರುಗಿ ret;
    }

    ಚೌಕಟ್ಟು->extended_ದತ್ತಾಂಶ = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ;

    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ HWContextType  *hw_type = ctx->hw_type;

    ಆದರೆ (hw_type->device_hwconfig_ಗಾತ್ರ == 0)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಹಿಂತಿರುಗಿ av_mallocz(hw_type->device_hwconfig_ಗಾತ್ರ);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->ದತ್ತಾಂಶ;
    ಸ್ಥಿರಾಂಕ HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    ಆದರೆ (!hw_type->ಚೌಕಟ್ಟುಗಳು_get_constraints)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    constraints = av_mallocz(ಗಾತ್ರ(*constraints));
    ಆದರೆ (!constraints)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    constraints->min_ಅಗಲ = constraints->min_ಎತ್ತರ = 0;
    constraints->max_ಅಗಲ = constraints->max_ಎತ್ತರ = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;

    ಆದರೆ (hw_type->ಚೌಕಟ್ಟುಗಳು_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        ಹಿಂತಿರುಗಿ constraints;
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_hwframe_constraints_free(&constraints);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
}

ಶೂನ್ಯ av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    ಆದರೆ (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

ಪೂರ್ಣಾಂಕ av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, ಎಣಿಕೆ AVHWDeviceType type,
                           ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device, AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    AVBufferRef *device_ref = ಖಾಲಿ;
    FFHWDeviceContext *device_ctx;
    ಪೂರ್ಣಾಂಕ ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    ಆದರೆ (!device_ref) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->ದತ್ತಾಂಶ;

    ಆದರೆ (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        ಹೋಗು fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    ret = av_hwdevice_ctx_init(device_ref);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    *pdevice_ref = device_ref;
    ಹಿಂತಿರುಗಿ 0;
fail:
    av_ಬಫರ್_unref(&device_ref);
    *pdevice_ref = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        ಎಣಿಕೆ AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, ಪೂರ್ಣಾಂಕ flags)
{
    AVBufferRef *dst_ref = ಖಾಲಿ, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    ಪೂರ್ಣಾಂಕ ret = 0;

    tmp_ref = src_ref;
    ಆಗ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->ದತ್ತಾಂಶ;
        ಆದರೆ (tmp_ctx->p.type == type) {
            dst_ref = av_ಬಫರ್_ref(tmp_ref);
            ಆದರೆ (!dst_ref) {
                ret = AVERROR(ENOMEM);
                ಹೋಗು fail;
            }
            ಹೋಗು ಮುಗಿದ;
        }
        tmp_ref = tmp_ctx->ಮೂಲ_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    ಆದರೆ (!dst_ref) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->ದತ್ತಾಂಶ;

    tmp_ref = src_ref;
    ಆಗ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->ದತ್ತಾಂಶ;
        ಆದರೆ (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            ಆದರೆ (ret == 0) {
                dst_ctx->ಮೂಲ_device = av_ಬಫರ್_ref(src_ref);
                ಆದರೆ (!dst_ctx->ಮೂಲ_device) {
                    ret = AVERROR(ENOMEM);
                    ಹೋಗು fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                ಆದರೆ (ret < 0)
                    ಹೋಗು fail;
                ಹೋಗು ಮುಗಿದ;
            }
            ಆದರೆ (ret != AVERROR(ENOSYS))
                ಹೋಗು fail;
        }
        tmp_ref = tmp_ctx->ಮೂಲ_device;
    }

    ret = AVERROR(ENOSYS);
    ಹೋಗು fail;

ಮುಗಿದ:
    *dst_ref_ptr = dst_ref;
    ಹಿಂತಿರುಗಿ 0;

fail:
    av_ಬಫರ್_unref(&dst_ref);
    *dst_ref_ptr = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   ಎಣಿಕೆ AVHWDeviceType type,
                                   AVBufferRef *src_ref, ಪೂರ್ಣಾಂಕ flags)
{
    ಹಿಂತಿರುಗಿ av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               ಖಾಲಿ, flags);
}

ಸ್ಥಿರ ಶೂನ್ಯ ff_hwframe_unmap(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)ದತ್ತಾಂಶ;
    AVHWFramesContext *ctx = opaque;

    ಆದರೆ (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_ಚೌಕಟ್ಟು_free(&hwmap->ಮೂಲ);

    av_ಬಫರ್_unref(&hwmap->hw_ಚೌಕಟ್ಟುಗಳು_ctx);

    av_free(hwmap);
}

ಪೂರ್ಣಾಂಕ ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src,
                          ಶೂನ್ಯ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          ಶೂನ್ಯ *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->ದತ್ತಾಂಶ;
    HWMapDescriptor *hwmap;
    ಪೂರ್ಣಾಂಕ ret;

    hwmap = av_mallocz(ಗಾತ್ರ(*hwmap));
    ಆದರೆ (!hwmap) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    hwmap->ಮೂಲ = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!hwmap->ಮೂಲ) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }
    ret = av_ಚೌಕಟ್ಟು_ref(hwmap->ಮೂಲ, src);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    hwmap->hw_ಚೌಕಟ್ಟುಗಳು_ctx = av_ಬಫರ್_ref(hwframe_ref);
    ಆದರೆ (!hwmap->hw_ಚೌಕಟ್ಟುಗಳು_ctx) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_ಬಫರ್_create((uint8_t*)hwmap, ಗಾತ್ರ(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    ಆದರೆ (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಆದರೆ (hwmap) {
        av_ಬಫರ್_unref(&hwmap->hw_ಚೌಕಟ್ಟುಗಳು_ctx);
        av_ಚೌಕಟ್ಟು_free(&hwmap->ಮೂಲ);
    }
    av_free(hwmap);
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_hwframe_map(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    AVBufferRef    *orig_dst_ಚೌಕಟ್ಟುಗಳು = dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx;
    ಎಣಿಕೆ AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (src->hw_ಚೌಕಟ್ಟುಗಳು_ctx && dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx) {
        FFHWFramesContext *src_ಚೌಕಟ್ಟುಗಳು = (FFHWFramesContext*)src->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
        FFHWFramesContext *dst_ಚೌಕಟ್ಟುಗಳು = (FFHWFramesContext*)dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;

        ಆದರೆ ((src_ಚೌಕಟ್ಟುಗಳು == dst_ಚೌಕಟ್ಟುಗಳು &&
             src->format == dst_ಚೌಕಟ್ಟುಗಳು->p.sw_format &&
             dst->format == dst_ಚೌಕಟ್ಟುಗಳು->p.format) ||
            (src_ಚೌಕಟ್ಟುಗಳು->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು &&
             src_ಚೌಕಟ್ಟುಗಳು->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು->ದತ್ತಾಂಶ ==
             (uint8_t*)dst_ಚೌಕಟ್ಟುಗಳು)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            ಆದರೆ (!src->buf[0]) {
                av_log(src_ಚೌಕಟ್ಟುಗಳು, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->ದತ್ತಾಂಶ;
            ಹಿಂತಿರುಗಿ av_ಚೌಕಟ್ಟು_replace(dst, hwmap->ಮೂಲ);
        }
    }

    ಆದರೆ (src->hw_ಚೌಕಟ್ಟುಗಳು_ctx) {
        FFHWFramesContext *src_ಚೌಕಟ್ಟುಗಳು = (FFHWFramesContext*)src->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;

        ಆದರೆ (src_ಚೌಕಟ್ಟುಗಳು->p.format == src->format &&
            src_ಚೌಕಟ್ಟುಗಳು->hw_type->map_from) {
            ret = src_ಚೌಕಟ್ಟುಗಳು->hw_type->map_from(&src_ಚೌಕಟ್ಟುಗಳು->p,
                                                dst, src, flags);
            ಆದರೆ (ret >= 0)
                ಹಿಂತಿರುಗಿ ret;
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ret != AVERROR(ENOSYS))
                ಹೋಗು fail;
        }
    }

    ಆದರೆ (dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx) {
        FFHWFramesContext *dst_ಚೌಕಟ್ಟುಗಳು = (FFHWFramesContext*)dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;

        ಆದರೆ (dst_ಚೌಕಟ್ಟುಗಳು->p.format == dst->format &&
            dst_ಚೌಕಟ್ಟುಗಳು->hw_type->map_ಗಮ್ಯ) {
            ret = dst_ಚೌಕಟ್ಟುಗಳು->hw_type->map_ಗಮ್ಯ(&dst_ಚೌಕಟ್ಟುಗಳು->p,
                                              dst, src, flags);
            ಆದರೆ (ret >= 0)
                ಹಿಂತಿರುಗಿ ret;
            ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ret != AVERROR(ENOSYS))
                ಹೋಗು fail;
        }
    }

    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_ಚೌಕಟ್ಟುಗಳು == ಖಾಲಿ ||
               orig_dst_ಚೌಕಟ್ಟುಗಳು == dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx = ಖಾಲಿ;
    av_ಚೌಕಟ್ಟು_unref(dst);

    dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx = orig_dst_ಚೌಕಟ್ಟುಗಳು;
    dst->format        = orig_dst_fmt;

    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_hwframe_ctx_create_derived(AVBufferRef **derived_ಚೌಕಟ್ಟು_ctx,
                                  ಎಣಿಕೆ AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *ಮೂಲ_ಚೌಕಟ್ಟು_ctx,
                                  ಪೂರ್ಣಾಂಕ flags)
{
    AVBufferRef   *dst_ref = ಖಾಲಿ;
    FFHWFramesContext *dsti = ಖಾಲಿ;
    FFHWFramesContext *srci = (FFHWFramesContext*)ಮೂಲ_ಚೌಕಟ್ಟು_ctx->ದತ್ತಾಂಶ;
    AVHWFramesContext *dst, *src = &srci->p;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (srci->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು->ದತ್ತಾಂಶ;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->ದತ್ತಾಂಶ;

        ಆದರೆ (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_ಚೌಕಟ್ಟು_ctx = av_ಬಫರ್_ref(srci->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು);
            ಆದರೆ (!*derived_ಚೌಕಟ್ಟು_ctx) {
                ret = AVERROR(ENOMEM);
                ಹೋಗು fail;
            }
            ಹಿಂತಿರುಗಿ 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    ಆದರೆ (!dst_ref) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->ದತ್ತಾಂಶ;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->ಅಗಲ     = src->ಅಗಲ;
    dst->ಎತ್ತರ    = src->ಎತ್ತರ;

    dsti->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು = av_ಬಫರ್_ref(ಮೂಲ_ಚೌಕಟ್ಟು_ctx);
    ಆದರೆ (!dsti->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    dsti->ಮೂಲ_ಹಂಚಿಕೆ_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_ನೇರ);

    ret = AVERROR(ENOSYS);
    ಆದರೆ (srci->hw_type->ಚೌಕಟ್ಟುಗಳು_derive_from)
        ret = srci->hw_type->ಚೌಕಟ್ಟುಗಳು_derive_from(dst, src, flags);
    ಆದರೆ (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ)
        ret = dsti->hw_type->ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ(dst, src, flags);
    ಆದರೆ (ret == AVERROR(ENOSYS))
        ret = 0;
    ಆದರೆ (ret)
        ಹೋಗು fail;

    *derived_ಚೌಕಟ್ಟು_ctx = dst_ref;
    ಹಿಂತಿರುಗಿ 0;

fail:
    ಆದರೆ (dsti)
        av_ಬಫರ್_unref(&dsti->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು);
    av_ಬಫರ್_unref(&dst_ref);
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ ff_hwframe_map_replace(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->ದತ್ತಾಂಶ;
    ಹಿಂತಿರುಗಿ av_ಚೌಕಟ್ಟು_replace(hwmap->ಮೂಲ, src);
}
