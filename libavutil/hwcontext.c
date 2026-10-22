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

#అన్తర్భావ "config.h"

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "buffer.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "frame_internal.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "imgutils.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pixdesc.h"
#అన్తర్భావ "pixfmt.h"

స్థిర స్థిరరాశి HWContextType * స్థిరరాశి hw_పట్టిక[] = {
#ఒకవేళ CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_QSV
    &ff_hwcontext_type_qsv,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_AMF
    &ff_hwcontext_type_amf,
#అయితే_ముగింపు
#ఒకవేళ CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#అయితే_ముగింపు
    ఖాళీ,
};

స్థిర స్థిరరాశి అక్షరం *స్థిరరాశి hw_type_పేర్లు[] = {
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

రకనిర్వచనం నిర్మాణం FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    స్థిరరాశి HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *ఆధారం_device;
} FFHWDeviceContext;

గణన AVHWDeviceType av_hwdevice_కనుగొను_type_by_name(స్థిరరాశి అక్షరం *name)
{
    పూర్ణాంకం type;
    కొరకు (type = 0; type < FF_ARRAY_ELEMS(hw_type_పేర్లు); type++) {
        ఒకవేళ (hw_type_పేర్లు[type] && !strcmp(hw_type_పేర్లు[type], name))
            తిరిగి type;
    }
    తిరిగి AV_HWDEVICE_TYPE_NONE;
}

స్థిరరాశి అక్షరం *av_hwdevice_get_type_name(గణన AVHWDeviceType type)
{
    ఒకవేళ (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_పేర్లు))
        తిరిగి hw_type_పేర్లు[type];
    లేకపోతే
        తిరిగి ఖాళీ;
}

గణన AVHWDeviceType av_hwdevice_iterate_types(గణన AVHWDeviceType prev)
{
    గణన AVHWDeviceType తదుపరి;
    పూర్ణాంకం i, సమితి = 0;
    కొరకు (i = 0; hw_పట్టిక[i]; i++) {
        ఒకవేళ (prev != AV_HWDEVICE_TYPE_NONE && hw_పట్టిక[i]->type <= prev)
            కొనసాగు;
        ఒకవేళ (!సమితి || hw_పట్టిక[i]->type < తదుపరి) {
            తదుపరి = hw_పట్టిక[i]->type;
            సమితి = 1;
        }
    }
    తిరిగి సమితి ? తదుపరి : AV_HWDEVICE_TYPE_NONE;
}

స్థిర స్థిరరాశి అక్షరం *hwdevice_ctx_get_name(శూన్య *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    తిరిగి ctx->hw_type->name;
}

స్థిర స్థిరరాశి AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .అంశం_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .సంస్కరణ    = LIBAVUTIL_సంస్కరణ_INT,
};

స్థిర శూన్య hwdevice_ctx_free(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)దత్తాంశం;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    ఒకవేళ (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    ఒకవేళ (ctx->విడుదల)
        ctx->విడుదల(ctx);

    av_బఫరు_unref(&ctxi->ఆధారం_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(గణన AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    స్థిరరాశి HWContextType *hw_type = ఖాళీ;
    పూర్ణాంకం i;

    కొరకు (i = 0; hw_పట్టిక[i]; i++) {
        ఒకవేళ (hw_పట్టిక[i]->type == type) {
            hw_type = hw_పట్టిక[i];
            ఆపు;
        }
    }
    ఒకవేళ (!hw_type)
        తిరిగి ఖాళీ;

    ctxi = av_mallocz(పరిమాణం(*ctxi));
    ఒకవేళ (!ctxi)
        తిరిగి ఖాళీ;
    ctx = &ctxi->p;

    ఒకవేళ (hw_type->device_hwctx_కొలత) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_కొలత);
        ఒకవేళ (!ctx->hwctx)
            వెళ్ళు fail;
    }

    buf = av_బఫరు_create((uint8_t*)ctx, పరిమాణం(*ctx),
                           hwdevice_ctx_free, ఖాళీ,
                           AV_బఫరు_FLAG_READONLY);
    ఒకవేళ (!buf)
        వెళ్ళు fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    తిరిగి buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    తిరిగి ఖాళీ;
}

పూర్ణాంకం av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->దత్తాంశం;
    AVHWDeviceContext *ctx  = &ctxi->p;
    పూర్ణాంకం ret = 0;

    ఒకవేళ (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    తిరిగి ret;
}

స్థిర స్థిరరాశి AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .అంశం_name  = av_default_అంశం_name,
    .సంస్కరణ    = LIBAVUTIL_సంస్కరణ_INT,
};

స్థిర శూన్య hwframe_ctx_free(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)దత్తాంశం;
    AVHWFramesContext *ctx  = &ctxi->p;

    ఒకవేళ (ctxi->pool_అంతర్గత)
        av_బఫరు_pool_uninit(&ctxi->pool_అంతర్గత);

    av_బఫరు_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_తాళం);

    ఒకవేళ (ctxi->hw_type->చట్రాలు_uninit)
        ctxi->hw_type->చట్రాలు_uninit(ctx);

    ఒకవేళ (ctx->విడుదల)
        ctx->విడుదల(ctx);

    av_బఫరు_unref(&ctxi->ఆధారం_చట్రాలు);

    av_బఫరు_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_లోపల)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_లోపల->దత్తాంశం;
    స్థిరరాశి HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = ఖాళీ;

    ctxi = av_mallocz(పరిమాణం(*ctxi));
    ఒకవేళ (!ctxi)
        తిరిగి ఖాళీ;
    ctx  = &ctxi->p;

    ఒకవేళ (ff_mutex_init(&ctxi->transfer_pool_తాళం, ఖాళీ)) {
        av_free(ctxi);
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (hw_type->చట్రాలు_hwctx_కొలత) {
        ctx->hwctx = av_mallocz(hw_type->చట్రాలు_hwctx_కొలత);
        ఒకవేళ (!ctx->hwctx)
            వెళ్ళు fail;
    }

    device_ref = av_బఫరు_ref(device_ref_లోపల);
    ఒకవేళ (!device_ref)
        వెళ్ళు fail;

    buf = av_బఫరు_create((uint8_t*)ctx, పరిమాణం(*ctx),
                           hwframe_ctx_free, ఖాళీ,
                           AV_బఫరు_FLAG_READONLY);
    ఒకవేళ (!buf)
        వెళ్ళు fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    తిరిగి buf;

fail:
    av_బఫరు_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_తాళం);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    తిరిగి ఖాళీ;
}

స్థిర పూర్ణాంకం hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->దత్తాంశం;
    AVFrame **చట్రాలు;
    పూర్ణాంకం i, ret = 0;

    చట్రాలు = av_calloc(ctx->initial_pool_కొలత, పరిమాణం(*చట్రాలు));
    ఒకవేళ (!చట్రాలు)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (i = 0; i < ctx->initial_pool_కొలత; i++) {
        చట్రాలు[i] = av_చట్రం_alloc();
        ఒకవేళ (!చట్రాలు[i])
            వెళ్ళు fail;

        ret = av_hwframe_get_బఫరు(ref, చట్రాలు[i], 0);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;
    }

fail:
    కొరకు (i = 0; i < ctx->initial_pool_కొలత; i++)
        av_చట్రం_free(&చట్రాలు[i]);
    av_freep(&చట్రాలు);

    తిరిగి ret;
}

పూర్ణాంకం av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->దత్తాంశం;
    AVHWFramesContext *ctx  = &ctxi->p;
    స్థిరరాశి గణన AVPixelFormat *pix_fmt;
    పూర్ణాంకం ret;

    ఒకవేళ (ctxi->ఆధారం_చట్రాలు) {
        /* A derived frame context is already initialised. */
        తిరిగి 0;
    }

    /* validate the pixel format */
    కొరకు (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        ఒకవేళ (*pix_fmt == ctx->format)
            ఆపు;
    }
    ఒకవేళ (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        తిరిగి AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_కొలత(ctx->వెడల్పు, ctx->ఎత్తు, 0, ctx);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    /* format-specific init */
    ఒకవేళ (ctxi->hw_type->చట్రాలు_init) {
        ret = ctxi->hw_type->చట్రాలు_init(ctx);
        ఒకవేళ (ret < 0)
            తిరిగి ret;
    }

    ఒకవేళ (ctxi->pool_అంతర్గత && !ctx->pool)
        ctx->pool = ctxi->pool_అంతర్గత;

    /* preallocate the frames in the pool, if requested */
    ఒకవేళ (ctx->initial_pool_కొలత > 0) {
        ret = hwframe_pool_prealloc(ref);
        ఒకవేళ (ret < 0)
            తిరిగి ret;
    }

    తిరిగి 0;
}

పూర్ణాంకం av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    గణన AVHWFrameTransferDirection dir,
                                    గణన AVPixelFormat **formats, పూర్ణాంకం flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->దత్తాంశం;

    ఒకవేళ (!ctxi->hw_type->transfer_get_formats)
        తిరిగి AVERROR(ENOSYS);

    తిరిగి ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

స్థిర శూన్య transfer_pool_free(శూన్య *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_బఫరు_unref(&device_ref);
}

స్థిర AVBufferRef *transfer_బఫరు_alloc(శూన్య *opaque, size_t కొలత)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = ఖాళీ;

    ff_mutex_తాళం(&ctxi->transfer_pool_తాళం);
    ఒకవేళ (ctxi->transfer_pool_కొలత != కొలత) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_బఫరు_alloc ?
                                  av_బఫరు_ref(ctxi->p.device_ref) : ఖాళీ;

        av_బఫరు_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_బఫరు_pool_init2(కొలత, device_ref,
                                 ctxi->hw_type->transfer_బఫరు_alloc,
                                 transfer_pool_free) :
            av_బఫరు_pool_init(కొలత, ఖాళీ);
        ctxi->transfer_pool_కొలత = ctxi->transfer_pool ? కొలత : 0;
        ఒకవేళ (!ctxi->transfer_pool)
            av_బఫరు_unref(&device_ref);
    }
    ఒకవేళ (ctxi->transfer_pool)
        buf = av_బఫరు_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_తాళం);

    తిరిగి buf ? buf : av_బఫరు_alloc(కొలత);
}

పూర్ణాంకం av_hwframe_get_transfer_బఫరు(AVBufferRef *hwframe_ctx, AVFrame *చట్రం)
{
    తిరిగి ff_చట్రం_get_video_బఫరు(చట్రం, 0, transfer_బఫరు_alloc,
                                     hwframe_ctx->దత్తాంశం);
}

స్థిర పూర్ణాంకం transfer_దత్తాంశం_alloc(AVFrame *dst, స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    AVHWFramesContext *ctx;
    AVFrame *చట్రం_tmp;
    పూర్ణాంకం ret = 0;

    ఒకవేళ (!src->hw_చట్రాలు_ctx)
        తిరిగి AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_చట్రాలు_ctx->దత్తాంశం;

    చట్రం_tmp = av_చట్రం_alloc();
    ఒకవేళ (!చట్రం_tmp)
        తిరిగి AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    ఒకవేళ (dst->format >= 0) {
        చట్రం_tmp->format = dst->format;
    } లేకపోతే {
        గణన AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_చట్రాలు_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        ఒకవేళ (ret < 0)
            వెళ్ళు fail;
        చట్రం_tmp->format = formats[0];
        av_freep(&formats);
    }
    చట్రం_tmp->వెడల్పు  = ctx->వెడల్పు;
    చట్రం_tmp->ఎత్తు = ctx->ఎత్తు;

    ret = av_hwframe_get_transfer_బఫరు(src->hw_చట్రాలు_ctx, చట్రం_tmp);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    ret = av_hwframe_transfer_దత్తాంశం(చట్రం_tmp, src, flags);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    చట్రం_tmp->వెడల్పు  = src->వెడల్పు;
    చట్రం_tmp->ఎత్తు = src->ఎత్తు;

    av_చట్రం_move_ref(dst, చట్రం_tmp);

fail:
    av_చట్రం_free(&చట్రం_tmp);
    తిరిగి ret;
}

పూర్ణాంకం av_hwframe_transfer_దత్తాంశం(AVFrame *dst, స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    పూర్ణాంకం ret;

    ఒకవేళ (!dst->buf[0])
        తిరిగి transfer_దత్తాంశం_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    ఒకవేళ (src->hw_చట్రాలు_ctx && dst->hw_చట్రాలు_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_చట్రాలు_ctx->దత్తాంశం;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_చట్రాలు_ctx->దత్తాంశం;

        ఒకవేళ (src_ctx->ఆధారం_చట్రాలు) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            తిరిగి AVERROR(ENOSYS);
        }

        ఒకవేళ (dst_ctx->ఆధారం_చట్రాలు) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            తిరిగి AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        ఒకవేళ (src_ctx->hw_type->transfer_దత్తాంశం_from)
            ret = src_ctx->hw_type->transfer_దత్తాంశం_from(&src_ctx->p, dst, src);
        ఒకవేళ (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_దత్తాంశం_గమ్యం)
            ret = dst_ctx->hw_type->transfer_దత్తాంశం_గమ్యం(&dst_ctx->p, dst, src);
        ఒకవేళ (ret < 0)
            తిరిగి ret;
    } లేకపోతే {
        ఒకవేళ (src->hw_చట్రాలు_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_చట్రాలు_ctx->దత్తాంశం;

            ఒకవేళ (!ctx->hw_type->transfer_దత్తాంశం_from)
                తిరిగి AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_దత్తాంశం_from(&ctx->p, dst, src);
            ఒకవేళ (ret < 0)
                తిరిగి ret;
        } లేకపోతే ఒకవేళ (dst->hw_చట్రాలు_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_చట్రాలు_ctx->దత్తాంశం;

            ఒకవేళ (!ctx->hw_type->transfer_దత్తాంశం_గమ్యం)
                తిరిగి AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_దత్తాంశం_గమ్యం(&ctx->p, dst, src);
            ఒకవేళ (ret < 0)
                తిరిగి ret;
        } లేకపోతే {
            తిరిగి AVERROR(ENOSYS);
        }
    }
    తిరిగి 0;
}

పూర్ణాంకం av_hwframe_get_బఫరు(AVBufferRef *hwframe_ref, AVFrame *చట్రం, పూర్ణాంకం flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->దత్తాంశం;
    AVHWFramesContext *ctx  = &ctxi->p;
    పూర్ణాంకం ret;

    ఒకవేళ (ctxi->ఆధారం_చట్రాలు) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_చట్రం;

        చట్రం->format = ctx->format;
        చట్రం->hw_చట్రాలు_ctx = av_బఫరు_ref(hwframe_ref);
        ఒకవేళ (!చట్రం->hw_చట్రాలు_ctx)
            తిరిగి AVERROR(ENOMEM);

        src_చట్రం = av_చట్రం_alloc();
        ఒకవేళ (!src_చట్రం)
            తిరిగి AVERROR(ENOMEM);

        ret = av_hwframe_get_బఫరు(ctxi->ఆధారం_చట్రాలు,
                                    src_చట్రం, 0);
        ఒకవేళ (ret < 0) {
            av_చట్రం_free(&src_చట్రం);
            తిరిగి ret;
        }

        ret = av_hwframe_map(చట్రం, src_చట్రం,
                             ctxi->ఆధారం_కేటాయింపు_map_flags);
        ఒకవేళ (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_చట్రం_free(&src_చట్రం);
            తిరిగి ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_చట్రం_free(&src_చట్రం);

        తిరిగి 0;
    }

    ఒకవేళ (!ctxi->hw_type->చట్రాలు_get_బఫరు)
        తిరిగి AVERROR(ENOSYS);

    ఒకవేళ (!ctx->pool)
        తిరిగి AVERROR(EINVAL);

    చట్రం->hw_చట్రాలు_ctx = av_బఫరు_ref(hwframe_ref);
    ఒకవేళ (!చట్రం->hw_చట్రాలు_ctx)
        తిరిగి AVERROR(ENOMEM);

    ret = ctxi->hw_type->చట్రాలు_get_బఫరు(ctx, చట్రం);
    ఒకవేళ (ret < 0) {
        av_బఫరు_unref(&చట్రం->hw_చట్రాలు_ctx);
        తిరిగి ret;
    }

    చట్రం->extended_దత్తాంశం = చట్రం->దత్తాంశం;

    తిరిగి 0;
}

శూన్య *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->దత్తాంశం;
    స్థిరరాశి HWContextType  *hw_type = ctx->hw_type;

    ఒకవేళ (hw_type->device_hwconfig_కొలత == 0)
        తిరిగి ఖాళీ;

    తిరిగి av_mallocz(hw_type->device_hwconfig_కొలత);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           స్థిరరాశి శూన్య *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->దత్తాంశం;
    స్థిరరాశి HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    ఒకవేళ (!hw_type->చట్రాలు_get_constraints)
        తిరిగి ఖాళీ;

    constraints = av_mallocz(పరిమాణం(*constraints));
    ఒకవేళ (!constraints)
        తిరిగి ఖాళీ;

    constraints->min_వెడల్పు = constraints->min_ఎత్తు = 0;
    constraints->max_వెడల్పు = constraints->max_ఎత్తు = గరిష్ఠ_పూర్ణాంకం;

    ఒకవేళ (hw_type->చట్రాలు_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        తిరిగి constraints;
    } లేకపోతే {
        av_hwframe_constraints_free(&constraints);
        తిరిగి ఖాళీ;
    }
}

శూన్య av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    ఒకవేళ (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

పూర్ణాంకం av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, గణన AVHWDeviceType type,
                           స్థిరరాశి అక్షరం *device, AVDictionary *opts, పూర్ణాంకం flags)
{
    AVBufferRef *device_ref = ఖాళీ;
    FFHWDeviceContext *device_ctx;
    పూర్ణాంకం ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    ఒకవేళ (!device_ref) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->దత్తాంశం;

    ఒకవేళ (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        వెళ్ళు fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    ret = av_hwdevice_ctx_init(device_ref);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    *pdevice_ref = device_ref;
    తిరిగి 0;
fail:
    av_బఫరు_unref(&device_ref);
    *pdevice_ref = ఖాళీ;
    తిరిగి ret;
}

పూర్ణాంకం av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        గణన AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, పూర్ణాంకం flags)
{
    AVBufferRef *dst_ref = ఖాళీ, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    పూర్ణాంకం ret = 0;

    tmp_ref = src_ref;
    అయితే (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->దత్తాంశం;
        ఒకవేళ (tmp_ctx->p.type == type) {
            dst_ref = av_బఫరు_ref(tmp_ref);
            ఒకవేళ (!dst_ref) {
                ret = AVERROR(ENOMEM);
                వెళ్ళు fail;
            }
            వెళ్ళు పూర్తి;
        }
        tmp_ref = tmp_ctx->ఆధారం_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    ఒకవేళ (!dst_ref) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->దత్తాంశం;

    tmp_ref = src_ref;
    అయితే (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->దత్తాంశం;
        ఒకవేళ (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            ఒకవేళ (ret == 0) {
                dst_ctx->ఆధారం_device = av_బఫరు_ref(src_ref);
                ఒకవేళ (!dst_ctx->ఆధారం_device) {
                    ret = AVERROR(ENOMEM);
                    వెళ్ళు fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                ఒకవేళ (ret < 0)
                    వెళ్ళు fail;
                వెళ్ళు పూర్తి;
            }
            ఒకవేళ (ret != AVERROR(ENOSYS))
                వెళ్ళు fail;
        }
        tmp_ref = tmp_ctx->ఆధారం_device;
    }

    ret = AVERROR(ENOSYS);
    వెళ్ళు fail;

పూర్తి:
    *dst_ref_ptr = dst_ref;
    తిరిగి 0;

fail:
    av_బఫరు_unref(&dst_ref);
    *dst_ref_ptr = ఖాళీ;
    తిరిగి ret;
}

పూర్ణాంకం av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   గణన AVHWDeviceType type,
                                   AVBufferRef *src_ref, పూర్ణాంకం flags)
{
    తిరిగి av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               ఖాళీ, flags);
}

స్థిర శూన్య ff_hwframe_unmap(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)దత్తాంశం;
    AVHWFramesContext *ctx = opaque;

    ఒకవేళ (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_చట్రం_free(&hwmap->ఆధారం);

    av_బఫరు_unref(&hwmap->hw_చట్రాలు_ctx);

    av_free(hwmap);
}

పూర్ణాంకం ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, స్థిరరాశి AVFrame *src,
                          శూన్య (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          శూన్య *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->దత్తాంశం;
    HWMapDescriptor *hwmap;
    పూర్ణాంకం ret;

    hwmap = av_mallocz(పరిమాణం(*hwmap));
    ఒకవేళ (!hwmap) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    hwmap->ఆధారం = av_చట్రం_alloc();
    ఒకవేళ (!hwmap->ఆధారం) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }
    ret = av_చట్రం_ref(hwmap->ఆధారం, src);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    hwmap->hw_చట్రాలు_ctx = av_బఫరు_ref(hwframe_ref);
    ఒకవేళ (!hwmap->hw_చట్రాలు_ctx) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_బఫరు_create((uint8_t*)hwmap, పరిమాణం(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    ఒకవేళ (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    తిరిగి 0;

fail:
    ఒకవేళ (hwmap) {
        av_బఫరు_unref(&hwmap->hw_చట్రాలు_ctx);
        av_చట్రం_free(&hwmap->ఆధారం);
    }
    av_free(hwmap);
    తిరిగి ret;
}

పూర్ణాంకం av_hwframe_map(AVFrame *dst, స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    AVBufferRef    *orig_dst_చట్రాలు = dst->hw_చట్రాలు_ctx;
    గణన AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    పూర్ణాంకం ret;

    ఒకవేళ (src->hw_చట్రాలు_ctx && dst->hw_చట్రాలు_ctx) {
        FFHWFramesContext *src_చట్రాలు = (FFHWFramesContext*)src->hw_చట్రాలు_ctx->దత్తాంశం;
        FFHWFramesContext *dst_చట్రాలు = (FFHWFramesContext*)dst->hw_చట్రాలు_ctx->దత్తాంశం;

        ఒకవేళ ((src_చట్రాలు == dst_చట్రాలు &&
             src->format == dst_చట్రాలు->p.sw_format &&
             dst->format == dst_చట్రాలు->p.format) ||
            (src_చట్రాలు->ఆధారం_చట్రాలు &&
             src_చట్రాలు->ఆధారం_చట్రాలు->దత్తాంశం ==
             (uint8_t*)dst_చట్రాలు)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            ఒకవేళ (!src->buf[0]) {
                av_log(src_చట్రాలు, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                తిరిగి AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->దత్తాంశం;
            తిరిగి av_చట్రం_replace(dst, hwmap->ఆధారం);
        }
    }

    ఒకవేళ (src->hw_చట్రాలు_ctx) {
        FFHWFramesContext *src_చట్రాలు = (FFHWFramesContext*)src->hw_చట్రాలు_ctx->దత్తాంశం;

        ఒకవేళ (src_చట్రాలు->p.format == src->format &&
            src_చట్రాలు->hw_type->map_from) {
            ret = src_చట్రాలు->hw_type->map_from(&src_చట్రాలు->p,
                                                dst, src, flags);
            ఒకవేళ (ret >= 0)
                తిరిగి ret;
            లేకపోతే ఒకవేళ (ret != AVERROR(ENOSYS))
                వెళ్ళు fail;
        }
    }

    ఒకవేళ (dst->hw_చట్రాలు_ctx) {
        FFHWFramesContext *dst_చట్రాలు = (FFHWFramesContext*)dst->hw_చట్రాలు_ctx->దత్తాంశం;

        ఒకవేళ (dst_చట్రాలు->p.format == dst->format &&
            dst_చట్రాలు->hw_type->map_గమ్యం) {
            ret = dst_చట్రాలు->hw_type->map_గమ్యం(&dst_చట్రాలు->p,
                                              dst, src, flags);
            ఒకవేళ (ret >= 0)
                తిరిగి ret;
            లేకపోతే ఒకవేళ (ret != AVERROR(ENOSYS))
                వెళ్ళు fail;
        }
    }

    తిరిగి AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_చట్రాలు == ఖాళీ ||
               orig_dst_చట్రాలు == dst->hw_చట్రాలు_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_చట్రాలు_ctx = ఖాళీ;
    av_చట్రం_unref(dst);

    dst->hw_చట్రాలు_ctx = orig_dst_చట్రాలు;
    dst->format        = orig_dst_fmt;

    తిరిగి ret;
}

పూర్ణాంకం av_hwframe_ctx_create_derived(AVBufferRef **derived_చట్రం_ctx,
                                  గణన AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *ఆధారం_చట్రం_ctx,
                                  పూర్ణాంకం flags)
{
    AVBufferRef   *dst_ref = ఖాళీ;
    FFHWFramesContext *dsti = ఖాళీ;
    FFHWFramesContext *srci = (FFHWFramesContext*)ఆధారం_చట్రం_ctx->దత్తాంశం;
    AVHWFramesContext *dst, *src = &srci->p;
    పూర్ణాంకం ret;

    ఒకవేళ (srci->ఆధారం_చట్రాలు) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->ఆధారం_చట్రాలు->దత్తాంశం;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->దత్తాంశం;

        ఒకవేళ (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_చట్రం_ctx = av_బఫరు_ref(srci->ఆధారం_చట్రాలు);
            ఒకవేళ (!*derived_చట్రం_ctx) {
                ret = AVERROR(ENOMEM);
                వెళ్ళు fail;
            }
            తిరిగి 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    ఒకవేళ (!dst_ref) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->దత్తాంశం;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->వెడల్పు     = src->వెడల్పు;
    dst->ఎత్తు    = src->ఎత్తు;

    dsti->ఆధారం_చట్రాలు = av_బఫరు_ref(ఆధారం_చట్రం_ctx);
    ఒకవేళ (!dsti->ఆధారం_చట్రాలు) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    dsti->ఆధారం_కేటాయింపు_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_ప్రత్యక్ష);

    ret = AVERROR(ENOSYS);
    ఒకవేళ (srci->hw_type->చట్రాలు_derive_from)
        ret = srci->hw_type->చట్రాలు_derive_from(dst, src, flags);
    ఒకవేళ (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->చట్రాలు_derive_గమ్యం)
        ret = dsti->hw_type->చట్రాలు_derive_గమ్యం(dst, src, flags);
    ఒకవేళ (ret == AVERROR(ENOSYS))
        ret = 0;
    ఒకవేళ (ret)
        వెళ్ళు fail;

    *derived_చట్రం_ctx = dst_ref;
    తిరిగి 0;

fail:
    ఒకవేళ (dsti)
        av_బఫరు_unref(&dsti->ఆధారం_చట్రాలు);
    av_బఫరు_unref(&dst_ref);
    తిరిగి ret;
}

పూర్ణాంకం ff_hwframe_map_replace(AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->దత్తాంశం;
    తిరిగి av_చట్రం_replace(hwmap->ఆధారం, src);
}
