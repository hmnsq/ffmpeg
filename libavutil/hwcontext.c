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

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "frame_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "imgutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"

ਸਥਿਰ ਅਚਲ HWContextType * ਅਚਲ hw_ਸਾਰਣੀ[] = {
#ਜੇ CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_QSV
    &ff_hwcontext_type_qsv,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_AMF
    &ff_hwcontext_type_amf,
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#ਜੇ_ਅੰਤ
    ਨਿਰਾ,
};

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *ਅਚਲ hw_type_ਨਾਂ[] = {
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

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    ਅਚਲ HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *ਸਰੋਤ_device;
} FFHWDeviceContext;

ਗਿਣਤੀ AVHWDeviceType av_hwdevice_ਲੱਭੋ_type_by_name(ਅਚਲ ਅੱਖਰ *name)
{
    ਪੂਰਨ type;
    ਲਈ (type = 0; type < FF_ARRAY_ELEMS(hw_type_ਨਾਂ); type++) {
        ਜੇ (hw_type_ਨਾਂ[type] && !strcmp(hw_type_ਨਾਂ[type], name))
            ਵਾਪਸ type;
    }
    ਵਾਪਸ AV_HWDEVICE_TYPE_NONE;
}

ਅਚਲ ਅੱਖਰ *av_hwdevice_get_type_name(ਗਿਣਤੀ AVHWDeviceType type)
{
    ਜੇ (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_ਨਾਂ))
        ਵਾਪਸ hw_type_ਨਾਂ[type];
    ਨਹੀਂਤਾਂ
        ਵਾਪਸ ਨਿਰਾ;
}

ਗਿਣਤੀ AVHWDeviceType av_hwdevice_iterate_types(ਗਿਣਤੀ AVHWDeviceType prev)
{
    ਗਿਣਤੀ AVHWDeviceType ਅਗਲਾ;
    ਪੂਰਨ i, ਸੈੱਟ = 0;
    ਲਈ (i = 0; hw_ਸਾਰਣੀ[i]; i++) {
        ਜੇ (prev != AV_HWDEVICE_TYPE_NONE && hw_ਸਾਰਣੀ[i]->type <= prev)
            ਜਾਰੀ;
        ਜੇ (!ਸੈੱਟ || hw_ਸਾਰਣੀ[i]->type < ਅਗਲਾ) {
            ਅਗਲਾ = hw_ਸਾਰਣੀ[i]->type;
            ਸੈੱਟ = 1;
        }
    }
    ਵਾਪਸ ਸੈੱਟ ? ਅਗਲਾ : AV_HWDEVICE_TYPE_NONE;
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *hwdevice_ctx_get_name(ਖਾਲੀ *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    ਵਾਪਸ ctx->hw_type->name;
}

ਸਥਿਰ ਅਚਲ AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .ਵਸਤੂ_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .ਸੰਸਕਰਣ    = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
};

ਸਥਿਰ ਖਾਲੀ hwdevice_ctx_free(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ਅੰਕੜੇ;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    ਜੇ (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    ਜੇ (ctx->ਮੁਕਤ)
        ctx->ਮੁਕਤ(ctx);

    av_ਬਫਰ_unref(&ctxi->ਸਰੋਤ_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(ਗਿਣਤੀ AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    ਅਚਲ HWContextType *hw_type = ਨਿਰਾ;
    ਪੂਰਨ i;

    ਲਈ (i = 0; hw_ਸਾਰਣੀ[i]; i++) {
        ਜੇ (hw_ਸਾਰਣੀ[i]->type == type) {
            hw_type = hw_ਸਾਰਣੀ[i];
            ਰੋਕੋ;
        }
    }
    ਜੇ (!hw_type)
        ਵਾਪਸ ਨਿਰਾ;

    ctxi = av_mallocz(ਆਕਾਰ(*ctxi));
    ਜੇ (!ctxi)
        ਵਾਪਸ ਨਿਰਾ;
    ctx = &ctxi->p;

    ਜੇ (hw_type->device_hwctx_ਮਾਪ) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_ਮਾਪ);
        ਜੇ (!ctx->hwctx)
            ਜਾਓ fail;
    }

    buf = av_ਬਫਰ_create((uint8_t*)ctx, ਆਕਾਰ(*ctx),
                           hwdevice_ctx_free, ਨਿਰਾ,
                           AV_ਬਫਰ_FLAG_READONLY);
    ਜੇ (!buf)
        ਜਾਓ fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    ਵਾਪਸ buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ਵਾਪਸ ਨਿਰਾ;
}

ਪੂਰਨ av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->ਅੰਕੜੇ;
    AVHWDeviceContext *ctx  = &ctxi->p;
    ਪੂਰਨ ret = 0;

    ਜੇ (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    ਵਾਪਸ ret;
}

ਸਥਿਰ ਅਚਲ AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .ਵਸਤੂ_name  = av_default_ਵਸਤੂ_name,
    .ਸੰਸਕਰਣ    = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
};

ਸਥਿਰ ਖਾਲੀ hwframe_ctx_free(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ਅੰਕੜੇ;
    AVHWFramesContext *ctx  = &ctxi->p;

    ਜੇ (ctxi->pool_ਅੰਦਰੂਨੀ)
        av_ਬਫਰ_pool_uninit(&ctxi->pool_ਅੰਦਰੂਨੀ);

    av_ਬਫਰ_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_ਤਾਲਾ);

    ਜੇ (ctxi->hw_type->ਚੌਖਟੇ_uninit)
        ctxi->hw_type->ਚੌਖਟੇ_uninit(ctx);

    ਜੇ (ctx->ਮੁਕਤ)
        ctx->ਮੁਕਤ(ctx);

    av_ਬਫਰ_unref(&ctxi->ਸਰੋਤ_ਚੌਖਟੇ);

    av_ਬਫਰ_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_ਵਿੱਚ)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_ਵਿੱਚ->ਅੰਕੜੇ;
    ਅਚਲ HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = ਨਿਰਾ;

    ctxi = av_mallocz(ਆਕਾਰ(*ctxi));
    ਜੇ (!ctxi)
        ਵਾਪਸ ਨਿਰਾ;
    ctx  = &ctxi->p;

    ਜੇ (ff_mutex_init(&ctxi->transfer_pool_ਤਾਲਾ, ਨਿਰਾ)) {
        av_free(ctxi);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (hw_type->ਚੌਖਟੇ_hwctx_ਮਾਪ) {
        ctx->hwctx = av_mallocz(hw_type->ਚੌਖਟੇ_hwctx_ਮਾਪ);
        ਜੇ (!ctx->hwctx)
            ਜਾਓ fail;
    }

    device_ref = av_ਬਫਰ_ref(device_ref_ਵਿੱਚ);
    ਜੇ (!device_ref)
        ਜਾਓ fail;

    buf = av_ਬਫਰ_create((uint8_t*)ctx, ਆਕਾਰ(*ctx),
                           hwframe_ctx_free, ਨਿਰਾ,
                           AV_ਬਫਰ_FLAG_READONLY);
    ਜੇ (!buf)
        ਜਾਓ fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    ਵਾਪਸ buf;

fail:
    av_ਬਫਰ_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_ਤਾਲਾ);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਪੂਰਨ hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->ਅੰਕੜੇ;
    AVFrame **ਚੌਖਟੇ;
    ਪੂਰਨ i, ret = 0;

    ਚੌਖਟੇ = av_calloc(ctx->initial_pool_ਮਾਪ, ਆਕਾਰ(*ਚੌਖਟੇ));
    ਜੇ (!ਚੌਖਟੇ)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (i = 0; i < ctx->initial_pool_ਮਾਪ; i++) {
        ਚੌਖਟੇ[i] = av_ਚੌਖਟਾ_alloc();
        ਜੇ (!ਚੌਖਟੇ[i])
            ਜਾਓ fail;

        ret = av_hwframe_get_ਬਫਰ(ref, ਚੌਖਟੇ[i], 0);
        ਜੇ (ret < 0)
            ਜਾਓ fail;
    }

fail:
    ਲਈ (i = 0; i < ctx->initial_pool_ਮਾਪ; i++)
        av_ਚੌਖਟਾ_free(&ਚੌਖਟੇ[i]);
    av_freep(&ਚੌਖਟੇ);

    ਵਾਪਸ ret;
}

ਪੂਰਨ av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->ਅੰਕੜੇ;
    AVHWFramesContext *ctx  = &ctxi->p;
    ਅਚਲ ਗਿਣਤੀ AVPixelFormat *pix_fmt;
    ਪੂਰਨ ret;

    ਜੇ (ctxi->ਸਰੋਤ_ਚੌਖਟੇ) {
        /* A derived frame context is already initialised. */
        ਵਾਪਸ 0;
    }

    /* validate the pixel format */
    ਲਈ (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        ਜੇ (*pix_fmt == ctx->format)
            ਰੋਕੋ;
    }
    ਜੇ (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_ਮਾਪ(ctx->ਚੌੜਾਈ, ctx->ਉਚਾਈ, 0, ctx);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    /* format-specific init */
    ਜੇ (ctxi->hw_type->ਚੌਖਟੇ_init) {
        ret = ctxi->hw_type->ਚੌਖਟੇ_init(ctx);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
    }

    ਜੇ (ctxi->pool_ਅੰਦਰੂਨੀ && !ctx->pool)
        ctx->pool = ctxi->pool_ਅੰਦਰੂਨੀ;

    /* preallocate the frames in the pool, if requested */
    ਜੇ (ctx->initial_pool_ਮਾਪ > 0) {
        ret = hwframe_pool_prealloc(ref);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                    ਗਿਣਤੀ AVPixelFormat **formats, ਪੂਰਨ flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->ਅੰਕੜੇ;

    ਜੇ (!ctxi->hw_type->transfer_get_formats)
        ਵਾਪਸ AVERROR(ENOSYS);

    ਵਾਪਸ ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

ਸਥਿਰ ਖਾਲੀ transfer_pool_free(ਖਾਲੀ *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_ਬਫਰ_unref(&device_ref);
}

ਸਥਿਰ AVBufferRef *transfer_ਬਫਰ_alloc(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = ਨਿਰਾ;

    ff_mutex_ਤਾਲਾ(&ctxi->transfer_pool_ਤਾਲਾ);
    ਜੇ (ctxi->transfer_pool_ਮਾਪ != ਮਾਪ) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_ਬਫਰ_alloc ?
                                  av_ਬਫਰ_ref(ctxi->p.device_ref) : ਨਿਰਾ;

        av_ਬਫਰ_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_ਬਫਰ_pool_init2(ਮਾਪ, device_ref,
                                 ctxi->hw_type->transfer_ਬਫਰ_alloc,
                                 transfer_pool_free) :
            av_ਬਫਰ_pool_init(ਮਾਪ, ਨਿਰਾ);
        ctxi->transfer_pool_ਮਾਪ = ctxi->transfer_pool ? ਮਾਪ : 0;
        ਜੇ (!ctxi->transfer_pool)
            av_ਬਫਰ_unref(&device_ref);
    }
    ਜੇ (ctxi->transfer_pool)
        buf = av_ਬਫਰ_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_ਤਾਲਾ);

    ਵਾਪਸ buf ? buf : av_ਬਫਰ_alloc(ਮਾਪ);
}

ਪੂਰਨ av_hwframe_get_transfer_ਬਫਰ(AVBufferRef *hwframe_ctx, AVFrame *ਚੌਖਟਾ)
{
    ਵਾਪਸ ff_ਚੌਖਟਾ_get_video_ਬਫਰ(ਚੌਖਟਾ, 0, transfer_ਬਫਰ_alloc,
                                     hwframe_ctx->ਅੰਕੜੇ);
}

ਸਥਿਰ ਪੂਰਨ transfer_ਅੰਕੜੇ_alloc(AVFrame *dst, ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    AVHWFramesContext *ctx;
    AVFrame *ਚੌਖਟਾ_tmp;
    ਪੂਰਨ ret = 0;

    ਜੇ (!src->hw_ਚੌਖਟੇ_ctx)
        ਵਾਪਸ AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;

    ਚੌਖਟਾ_tmp = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!ਚੌਖਟਾ_tmp)
        ਵਾਪਸ AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    ਜੇ (dst->format >= 0) {
        ਚੌਖਟਾ_tmp->format = dst->format;
    } ਨਹੀਂਤਾਂ {
        ਗਿਣਤੀ AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_ਚੌਖਟੇ_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        ਜੇ (ret < 0)
            ਜਾਓ fail;
        ਚੌਖਟਾ_tmp->format = formats[0];
        av_freep(&formats);
    }
    ਚੌਖਟਾ_tmp->ਚੌੜਾਈ  = ctx->ਚੌੜਾਈ;
    ਚੌਖਟਾ_tmp->ਉਚਾਈ = ctx->ਉਚਾਈ;

    ret = av_hwframe_get_transfer_ਬਫਰ(src->hw_ਚੌਖਟੇ_ctx, ਚੌਖਟਾ_tmp);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    ret = av_hwframe_transfer_ਅੰਕੜੇ(ਚੌਖਟਾ_tmp, src, flags);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    ਚੌਖਟਾ_tmp->ਚੌੜਾਈ  = src->ਚੌੜਾਈ;
    ਚੌਖਟਾ_tmp->ਉਚਾਈ = src->ਉਚਾਈ;

    av_ਚੌਖਟਾ_move_ref(dst, ਚੌਖਟਾ_tmp);

fail:
    av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ_tmp);
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_hwframe_transfer_ਅੰਕੜੇ(AVFrame *dst, ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    ਪੂਰਨ ret;

    ਜੇ (!dst->buf[0])
        ਵਾਪਸ transfer_ਅੰਕੜੇ_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    ਜੇ (src->hw_ਚੌਖਟੇ_ctx && dst->hw_ਚੌਖਟੇ_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;

        ਜੇ (src_ctx->ਸਰੋਤ_ਚੌਖਟੇ) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            ਵਾਪਸ AVERROR(ENOSYS);
        }

        ਜੇ (dst_ctx->ਸਰੋਤ_ਚੌਖਟੇ) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            ਵਾਪਸ AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        ਜੇ (src_ctx->hw_type->transfer_ਅੰਕੜੇ_from)
            ret = src_ctx->hw_type->transfer_ਅੰਕੜੇ_from(&src_ctx->p, dst, src);
        ਜੇ (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ)
            ret = dst_ctx->hw_type->transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ(&dst_ctx->p, dst, src);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (src->hw_ਚੌਖਟੇ_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;

            ਜੇ (!ctx->hw_type->transfer_ਅੰਕੜੇ_from)
                ਵਾਪਸ AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_ਅੰਕੜੇ_from(&ctx->p, dst, src);
            ਜੇ (ret < 0)
                ਵਾਪਸ ret;
        } ਨਹੀਂਤਾਂ ਜੇ (dst->hw_ਚੌਖਟੇ_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;

            ਜੇ (!ctx->hw_type->transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ)
                ਵਾਪਸ AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ(&ctx->p, dst, src);
            ਜੇ (ret < 0)
                ਵਾਪਸ ret;
        } ਨਹੀਂਤਾਂ {
            ਵਾਪਸ AVERROR(ENOSYS);
        }
    }
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_hwframe_get_ਬਫਰ(AVBufferRef *hwframe_ref, AVFrame *ਚੌਖਟਾ, ਪੂਰਨ flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->ਅੰਕੜੇ;
    AVHWFramesContext *ctx  = &ctxi->p;
    ਪੂਰਨ ret;

    ਜੇ (ctxi->ਸਰੋਤ_ਚੌਖਟੇ) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_ਚੌਖਟਾ;

        ਚੌਖਟਾ->format = ctx->format;
        ਚੌਖਟਾ->hw_ਚੌਖਟੇ_ctx = av_ਬਫਰ_ref(hwframe_ref);
        ਜੇ (!ਚੌਖਟਾ->hw_ਚੌਖਟੇ_ctx)
            ਵਾਪਸ AVERROR(ENOMEM);

        src_ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
        ਜੇ (!src_ਚੌਖਟਾ)
            ਵਾਪਸ AVERROR(ENOMEM);

        ret = av_hwframe_get_ਬਫਰ(ctxi->ਸਰੋਤ_ਚੌਖਟੇ,
                                    src_ਚੌਖਟਾ, 0);
        ਜੇ (ret < 0) {
            av_ਚੌਖਟਾ_free(&src_ਚੌਖਟਾ);
            ਵਾਪਸ ret;
        }

        ret = av_hwframe_map(ਚੌਖਟਾ, src_ਚੌਖਟਾ,
                             ctxi->ਸਰੋਤ_ਵੰਡ_map_flags);
        ਜੇ (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_ਚੌਖਟਾ_free(&src_ਚੌਖਟਾ);
            ਵਾਪਸ ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_ਚੌਖਟਾ_free(&src_ਚੌਖਟਾ);

        ਵਾਪਸ 0;
    }

    ਜੇ (!ctxi->hw_type->ਚੌਖਟੇ_get_ਬਫਰ)
        ਵਾਪਸ AVERROR(ENOSYS);

    ਜੇ (!ctx->pool)
        ਵਾਪਸ AVERROR(EINVAL);

    ਚੌਖਟਾ->hw_ਚੌਖਟੇ_ctx = av_ਬਫਰ_ref(hwframe_ref);
    ਜੇ (!ਚੌਖਟਾ->hw_ਚੌਖਟੇ_ctx)
        ਵਾਪਸ AVERROR(ENOMEM);

    ret = ctxi->hw_type->ਚੌਖਟੇ_get_ਬਫਰ(ctx, ਚੌਖਟਾ);
    ਜੇ (ret < 0) {
        av_ਬਫਰ_unref(&ਚੌਖਟਾ->hw_ਚੌਖਟੇ_ctx);
        ਵਾਪਸ ret;
    }

    ਚੌਖਟਾ->extended_ਅੰਕੜੇ = ਚੌਖਟਾ->ਅੰਕੜੇ;

    ਵਾਪਸ 0;
}

ਖਾਲੀ *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->ਅੰਕੜੇ;
    ਅਚਲ HWContextType  *hw_type = ctx->hw_type;

    ਜੇ (hw_type->device_hwconfig_ਮਾਪ == 0)
        ਵਾਪਸ ਨਿਰਾ;

    ਵਾਪਸ av_mallocz(hw_type->device_hwconfig_ਮਾਪ);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ਅਚਲ ਖਾਲੀ *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->ਅੰਕੜੇ;
    ਅਚਲ HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    ਜੇ (!hw_type->ਚੌਖਟੇ_get_constraints)
        ਵਾਪਸ ਨਿਰਾ;

    constraints = av_mallocz(ਆਕਾਰ(*constraints));
    ਜੇ (!constraints)
        ਵਾਪਸ ਨਿਰਾ;

    constraints->min_ਚੌੜਾਈ = constraints->min_ਉਚਾਈ = 0;
    constraints->max_ਚੌੜਾਈ = constraints->max_ਉਚਾਈ = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;

    ਜੇ (hw_type->ਚੌਖਟੇ_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        ਵਾਪਸ constraints;
    } ਨਹੀਂਤਾਂ {
        av_hwframe_constraints_free(&constraints);
        ਵਾਪਸ ਨਿਰਾ;
    }
}

ਖਾਲੀ av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    ਜੇ (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

ਪੂਰਨ av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, ਗਿਣਤੀ AVHWDeviceType type,
                           ਅਚਲ ਅੱਖਰ *device, AVDictionary *opts, ਪੂਰਨ flags)
{
    AVBufferRef *device_ref = ਨਿਰਾ;
    FFHWDeviceContext *device_ctx;
    ਪੂਰਨ ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    ਜੇ (!device_ref) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->ਅੰਕੜੇ;

    ਜੇ (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        ਜਾਓ fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    ret = av_hwdevice_ctx_init(device_ref);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    *pdevice_ref = device_ref;
    ਵਾਪਸ 0;
fail:
    av_ਬਫਰ_unref(&device_ref);
    *pdevice_ref = ਨਿਰਾ;
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        ਗਿਣਤੀ AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, ਪੂਰਨ flags)
{
    AVBufferRef *dst_ref = ਨਿਰਾ, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    ਪੂਰਨ ret = 0;

    tmp_ref = src_ref;
    ਜਦੋਂ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->ਅੰਕੜੇ;
        ਜੇ (tmp_ctx->p.type == type) {
            dst_ref = av_ਬਫਰ_ref(tmp_ref);
            ਜੇ (!dst_ref) {
                ret = AVERROR(ENOMEM);
                ਜਾਓ fail;
            }
            ਜਾਓ ਪੂਰਾ;
        }
        tmp_ref = tmp_ctx->ਸਰੋਤ_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    ਜੇ (!dst_ref) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->ਅੰਕੜੇ;

    tmp_ref = src_ref;
    ਜਦੋਂ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->ਅੰਕੜੇ;
        ਜੇ (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            ਜੇ (ret == 0) {
                dst_ctx->ਸਰੋਤ_device = av_ਬਫਰ_ref(src_ref);
                ਜੇ (!dst_ctx->ਸਰੋਤ_device) {
                    ret = AVERROR(ENOMEM);
                    ਜਾਓ fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                ਜੇ (ret < 0)
                    ਜਾਓ fail;
                ਜਾਓ ਪੂਰਾ;
            }
            ਜੇ (ret != AVERROR(ENOSYS))
                ਜਾਓ fail;
        }
        tmp_ref = tmp_ctx->ਸਰੋਤ_device;
    }

    ret = AVERROR(ENOSYS);
    ਜਾਓ fail;

ਪੂਰਾ:
    *dst_ref_ptr = dst_ref;
    ਵਾਪਸ 0;

fail:
    av_ਬਫਰ_unref(&dst_ref);
    *dst_ref_ptr = ਨਿਰਾ;
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   ਗਿਣਤੀ AVHWDeviceType type,
                                   AVBufferRef *src_ref, ਪੂਰਨ flags)
{
    ਵਾਪਸ av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               ਨਿਰਾ, flags);
}

ਸਥਿਰ ਖਾਲੀ ff_hwframe_unmap(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)ਅੰਕੜੇ;
    AVHWFramesContext *ctx = opaque;

    ਜੇ (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_ਚੌਖਟਾ_free(&hwmap->ਸਰੋਤ);

    av_ਬਫਰ_unref(&hwmap->hw_ਚੌਖਟੇ_ctx);

    av_free(hwmap);
}

ਪੂਰਨ ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ਅਚਲ AVFrame *src,
                          ਖਾਲੀ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          ਖਾਲੀ *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->ਅੰਕੜੇ;
    HWMapDescriptor *hwmap;
    ਪੂਰਨ ret;

    hwmap = av_mallocz(ਆਕਾਰ(*hwmap));
    ਜੇ (!hwmap) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    hwmap->ਸਰੋਤ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!hwmap->ਸਰੋਤ) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }
    ret = av_ਚੌਖਟਾ_ref(hwmap->ਸਰੋਤ, src);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    hwmap->hw_ਚੌਖਟੇ_ctx = av_ਬਫਰ_ref(hwframe_ref);
    ਜੇ (!hwmap->hw_ਚੌਖਟੇ_ctx) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_ਬਫਰ_create((uint8_t*)hwmap, ਆਕਾਰ(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    ਜੇ (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    ਵਾਪਸ 0;

fail:
    ਜੇ (hwmap) {
        av_ਬਫਰ_unref(&hwmap->hw_ਚੌਖਟੇ_ctx);
        av_ਚੌਖਟਾ_free(&hwmap->ਸਰੋਤ);
    }
    av_free(hwmap);
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_hwframe_map(AVFrame *dst, ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    AVBufferRef    *orig_dst_ਚੌਖਟੇ = dst->hw_ਚੌਖਟੇ_ctx;
    ਗਿਣਤੀ AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    ਪੂਰਨ ret;

    ਜੇ (src->hw_ਚੌਖਟੇ_ctx && dst->hw_ਚੌਖਟੇ_ctx) {
        FFHWFramesContext *src_ਚੌਖਟੇ = (FFHWFramesContext*)src->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
        FFHWFramesContext *dst_ਚੌਖਟੇ = (FFHWFramesContext*)dst->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;

        ਜੇ ((src_ਚੌਖਟੇ == dst_ਚੌਖਟੇ &&
             src->format == dst_ਚੌਖਟੇ->p.sw_format &&
             dst->format == dst_ਚੌਖਟੇ->p.format) ||
            (src_ਚੌਖਟੇ->ਸਰੋਤ_ਚੌਖਟੇ &&
             src_ਚੌਖਟੇ->ਸਰੋਤ_ਚੌਖਟੇ->ਅੰਕੜੇ ==
             (uint8_t*)dst_ਚੌਖਟੇ)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            ਜੇ (!src->buf[0]) {
                av_log(src_ਚੌਖਟੇ, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                ਵਾਪਸ AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->ਅੰਕੜੇ;
            ਵਾਪਸ av_ਚੌਖਟਾ_replace(dst, hwmap->ਸਰੋਤ);
        }
    }

    ਜੇ (src->hw_ਚੌਖਟੇ_ctx) {
        FFHWFramesContext *src_ਚੌਖਟੇ = (FFHWFramesContext*)src->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;

        ਜੇ (src_ਚੌਖਟੇ->p.format == src->format &&
            src_ਚੌਖਟੇ->hw_type->map_from) {
            ret = src_ਚੌਖਟੇ->hw_type->map_from(&src_ਚੌਖਟੇ->p,
                                                dst, src, flags);
            ਜੇ (ret >= 0)
                ਵਾਪਸ ret;
            ਨਹੀਂਤਾਂ ਜੇ (ret != AVERROR(ENOSYS))
                ਜਾਓ fail;
        }
    }

    ਜੇ (dst->hw_ਚੌਖਟੇ_ctx) {
        FFHWFramesContext *dst_ਚੌਖਟੇ = (FFHWFramesContext*)dst->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;

        ਜੇ (dst_ਚੌਖਟੇ->p.format == dst->format &&
            dst_ਚੌਖਟੇ->hw_type->map_ਮੰਜ਼ਿਲ) {
            ret = dst_ਚੌਖਟੇ->hw_type->map_ਮੰਜ਼ਿਲ(&dst_ਚੌਖਟੇ->p,
                                              dst, src, flags);
            ਜੇ (ret >= 0)
                ਵਾਪਸ ret;
            ਨਹੀਂਤਾਂ ਜੇ (ret != AVERROR(ENOSYS))
                ਜਾਓ fail;
        }
    }

    ਵਾਪਸ AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_ਚੌਖਟੇ == ਨਿਰਾ ||
               orig_dst_ਚੌਖਟੇ == dst->hw_ਚੌਖਟੇ_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_ਚੌਖਟੇ_ctx = ਨਿਰਾ;
    av_ਚੌਖਟਾ_unref(dst);

    dst->hw_ਚੌਖਟੇ_ctx = orig_dst_ਚੌਖਟੇ;
    dst->format        = orig_dst_fmt;

    ਵਾਪਸ ret;
}

ਪੂਰਨ av_hwframe_ctx_create_derived(AVBufferRef **derived_ਚੌਖਟਾ_ctx,
                                  ਗਿਣਤੀ AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *ਸਰੋਤ_ਚੌਖਟਾ_ctx,
                                  ਪੂਰਨ flags)
{
    AVBufferRef   *dst_ref = ਨਿਰਾ;
    FFHWFramesContext *dsti = ਨਿਰਾ;
    FFHWFramesContext *srci = (FFHWFramesContext*)ਸਰੋਤ_ਚੌਖਟਾ_ctx->ਅੰਕੜੇ;
    AVHWFramesContext *dst, *src = &srci->p;
    ਪੂਰਨ ret;

    ਜੇ (srci->ਸਰੋਤ_ਚੌਖਟੇ) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->ਸਰੋਤ_ਚੌਖਟੇ->ਅੰਕੜੇ;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->ਅੰਕੜੇ;

        ਜੇ (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_ਚੌਖਟਾ_ctx = av_ਬਫਰ_ref(srci->ਸਰੋਤ_ਚੌਖਟੇ);
            ਜੇ (!*derived_ਚੌਖਟਾ_ctx) {
                ret = AVERROR(ENOMEM);
                ਜਾਓ fail;
            }
            ਵਾਪਸ 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    ਜੇ (!dst_ref) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->ਅੰਕੜੇ;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->ਚੌੜਾਈ     = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ    = src->ਉਚਾਈ;

    dsti->ਸਰੋਤ_ਚੌਖਟੇ = av_ਬਫਰ_ref(ਸਰੋਤ_ਚੌਖਟਾ_ctx);
    ਜੇ (!dsti->ਸਰੋਤ_ਚੌਖਟੇ) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    dsti->ਸਰੋਤ_ਵੰਡ_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_ਸਿੱਧਾ);

    ret = AVERROR(ENOSYS);
    ਜੇ (srci->hw_type->ਚੌਖਟੇ_derive_from)
        ret = srci->hw_type->ਚੌਖਟੇ_derive_from(dst, src, flags);
    ਜੇ (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ)
        ret = dsti->hw_type->ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ(dst, src, flags);
    ਜੇ (ret == AVERROR(ENOSYS))
        ret = 0;
    ਜੇ (ret)
        ਜਾਓ fail;

    *derived_ਚੌਖਟਾ_ctx = dst_ref;
    ਵਾਪਸ 0;

fail:
    ਜੇ (dsti)
        av_ਬਫਰ_unref(&dsti->ਸਰੋਤ_ਚੌਖਟੇ);
    av_ਬਫਰ_unref(&dst_ref);
    ਵਾਪਸ ret;
}

ਪੂਰਨ ff_hwframe_map_replace(AVFrame *dst, ਅਚਲ AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->ਅੰਕੜੇ;
    ਵਾਪਸ av_ਚੌਖਟਾ_replace(hwmap->ਸਰੋਤ, src);
}
