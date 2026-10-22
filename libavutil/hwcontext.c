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

#شامل "config.h"

#شامل "avassert.h"
#شامل "buffer.h"
#شامل "common.h"
#شامل "frame_internal.h"
#شامل "hwcontext.h"
#شامل "hwcontext_internal.h"
#شامل "imgutils.h"
#شامل "log.h"
#شامل "mem.h"
#شامل "pixdesc.h"
#شامل "pixfmt.h"

ساکن ثابت HWContextType * ثابت hw_جدول[] = {
#اگر CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#اگر_ختم
#اگر CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#اگر_ختم
#اگر CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#اگر_ختم
#اگر CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#اگر_ختم
#اگر CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#اگر_ختم
#اگر CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#اگر_ختم
#اگر CONFIG_QSV
    &ff_hwcontext_type_qsv,
#اگر_ختم
#اگر CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#اگر_ختم
#اگر CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#اگر_ختم
#اگر CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#اگر_ختم
#اگر CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#اگر_ختم
#اگر CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#اگر_ختم
#اگر CONFIG_AMF
    &ff_hwcontext_type_amf,
#اگر_ختم
#اگر CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#اگر_ختم
    تہی,
};

ساکن ثابت حرف *ثابت hw_type_نام[] = {
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

قسمتعریف ساخت FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    ثابت HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *ماخذ_device;
} FFHWDeviceContext;

شمار AVHWDeviceType av_hwdevice_ڈھونڈو_type_by_name(ثابت حرف *name)
{
    صحیح type;
    برائے (type = 0; type < FF_ARRAY_ELEMS(hw_type_نام); type++) {
        اگر (hw_type_نام[type] && !strcmp(hw_type_نام[type], name))
            واپس type;
    }
    واپس AV_HWDEVICE_TYPE_NONE;
}

ثابت حرف *av_hwdevice_get_type_name(شمار AVHWDeviceType type)
{
    اگر (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_نام))
        واپس hw_type_نام[type];
    ورنہ
        واپس تہی;
}

شمار AVHWDeviceType av_hwdevice_iterate_types(شمار AVHWDeviceType پچھلا)
{
    شمار AVHWDeviceType اگلا;
    صحیح i, سیٹ = 0;
    برائے (i = 0; hw_جدول[i]; i++) {
        اگر (پچھلا != AV_HWDEVICE_TYPE_NONE && hw_جدول[i]->type <= پچھلا)
            جاری;
        اگر (!سیٹ || hw_جدول[i]->type < اگلا) {
            اگلا = hw_جدول[i]->type;
            سیٹ = 1;
        }
    }
    واپس سیٹ ? اگلا : AV_HWDEVICE_TYPE_NONE;
}

ساکن ثابت حرف *hwdevice_ctx_get_name(خالی *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    واپس ctx->hw_type->name;
}

ساکن ثابت AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .شے_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .نسخہ    = LIBAVUTIL_نسخہ_INT,
};

ساکن خالی hwdevice_ctx_free(خالی *opaque, uint8_t *ڈیٹا)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ڈیٹا;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    اگر (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    اگر (ctx->آزاد)
        ctx->آزاد(ctx);

    av_بفر_unref(&ctxi->ماخذ_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(شمار AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    ثابت HWContextType *hw_type = تہی;
    صحیح i;

    برائے (i = 0; hw_جدول[i]; i++) {
        اگر (hw_جدول[i]->type == type) {
            hw_type = hw_جدول[i];
            توڑو;
        }
    }
    اگر (!hw_type)
        واپس تہی;

    ctxi = av_mallocz(حجم(*ctxi));
    اگر (!ctxi)
        واپس تہی;
    ctx = &ctxi->p;

    اگر (hw_type->device_hwctx_سائز) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_سائز);
        اگر (!ctx->hwctx)
            جاؤ fail;
    }

    buf = av_بفر_create((uint8_t*)ctx, حجم(*ctx),
                           hwdevice_ctx_free, تہی,
                           AV_بفر_FLAG_READONLY);
    اگر (!buf)
        جاؤ fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    واپس buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    واپس تہی;
}

صحیح av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->ڈیٹا;
    AVHWDeviceContext *ctx  = &ctxi->p;
    صحیح ret = 0;

    اگر (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    واپس ret;
}

ساکن ثابت AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .شے_name  = av_default_شے_name,
    .نسخہ    = LIBAVUTIL_نسخہ_INT,
};

ساکن خالی hwframe_ctx_free(خالی *opaque, uint8_t *ڈیٹا)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ڈیٹا;
    AVHWFramesContext *ctx  = &ctxi->p;

    اگر (ctxi->pool_اندرونی)
        av_بفر_pool_uninit(&ctxi->pool_اندرونی);

    av_بفر_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_تالا);

    اگر (ctxi->hw_type->چوکھٹے_uninit)
        ctxi->hw_type->چوکھٹے_uninit(ctx);

    اگر (ctx->آزاد)
        ctx->آزاد(ctx);

    av_بفر_unref(&ctxi->ماخذ_چوکھٹے);

    av_بفر_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_اندر)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_اندر->ڈیٹا;
    ثابت HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = تہی;

    ctxi = av_mallocz(حجم(*ctxi));
    اگر (!ctxi)
        واپس تہی;
    ctx  = &ctxi->p;

    اگر (ff_mutex_init(&ctxi->transfer_pool_تالا, تہی)) {
        av_free(ctxi);
        واپس تہی;
    }

    اگر (hw_type->چوکھٹے_hwctx_سائز) {
        ctx->hwctx = av_mallocz(hw_type->چوکھٹے_hwctx_سائز);
        اگر (!ctx->hwctx)
            جاؤ fail;
    }

    device_ref = av_بفر_ref(device_ref_اندر);
    اگر (!device_ref)
        جاؤ fail;

    buf = av_بفر_create((uint8_t*)ctx, حجم(*ctx),
                           hwframe_ctx_free, تہی,
                           AV_بفر_FLAG_READONLY);
    اگر (!buf)
        جاؤ fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    واپس buf;

fail:
    av_بفر_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_تالا);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    واپس تہی;
}

ساکن صحیح hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->ڈیٹا;
    AVFrame **چوکھٹے;
    صحیح i, ret = 0;

    چوکھٹے = av_calloc(ctx->initial_pool_سائز, حجم(*چوکھٹے));
    اگر (!چوکھٹے)
        واپس AVERROR(ENOMEM);

    برائے (i = 0; i < ctx->initial_pool_سائز; i++) {
        چوکھٹے[i] = av_چوکھٹا_alloc();
        اگر (!چوکھٹے[i])
            جاؤ fail;

        ret = av_hwframe_get_بفر(ref, چوکھٹے[i], 0);
        اگر (ret < 0)
            جاؤ fail;
    }

fail:
    برائے (i = 0; i < ctx->initial_pool_سائز; i++)
        av_چوکھٹا_free(&چوکھٹے[i]);
    av_freep(&چوکھٹے);

    واپس ret;
}

صحیح av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->ڈیٹا;
    AVHWFramesContext *ctx  = &ctxi->p;
    ثابت شمار AVPixelFormat *pix_fmt;
    صحیح ret;

    اگر (ctxi->ماخذ_چوکھٹے) {
        /* A derived frame context is already initialised. */
        واپس 0;
    }

    /* validate the pixel format */
    برائے (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        اگر (*pix_fmt == ctx->format)
            توڑو;
    }
    اگر (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        واپس AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_سائز(ctx->چوڑائی, ctx->اونچائی, 0, ctx);
    اگر (ret < 0)
        واپس ret;

    /* format-specific init */
    اگر (ctxi->hw_type->چوکھٹے_init) {
        ret = ctxi->hw_type->چوکھٹے_init(ctx);
        اگر (ret < 0)
            واپس ret;
    }

    اگر (ctxi->pool_اندرونی && !ctx->pool)
        ctx->pool = ctxi->pool_اندرونی;

    /* preallocate the frames in the pool, if requested */
    اگر (ctx->initial_pool_سائز > 0) {
        ret = hwframe_pool_prealloc(ref);
        اگر (ret < 0)
            واپس ret;
    }

    واپس 0;
}

صحیح av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    شمار AVHWFrameTransferDirection dir,
                                    شمار AVPixelFormat **formats, صحیح flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->ڈیٹا;

    اگر (!ctxi->hw_type->transfer_get_formats)
        واپس AVERROR(ENOSYS);

    واپس ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

ساکن خالی transfer_pool_free(خالی *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_بفر_unref(&device_ref);
}

ساکن AVBufferRef *transfer_بفر_alloc(خالی *opaque, size_t سائز)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = تہی;

    ff_mutex_تالا(&ctxi->transfer_pool_تالا);
    اگر (ctxi->transfer_pool_سائز != سائز) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_بفر_alloc ?
                                  av_بفر_ref(ctxi->p.device_ref) : تہی;

        av_بفر_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_بفر_pool_init2(سائز, device_ref,
                                 ctxi->hw_type->transfer_بفر_alloc,
                                 transfer_pool_free) :
            av_بفر_pool_init(سائز, تہی);
        ctxi->transfer_pool_سائز = ctxi->transfer_pool ? سائز : 0;
        اگر (!ctxi->transfer_pool)
            av_بفر_unref(&device_ref);
    }
    اگر (ctxi->transfer_pool)
        buf = av_بفر_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_تالا);

    واپس buf ? buf : av_بفر_alloc(سائز);
}

صحیح av_hwframe_get_transfer_بفر(AVBufferRef *hwframe_ctx, AVFrame *چوکھٹا)
{
    واپس ff_چوکھٹا_get_video_بفر(چوکھٹا, 0, transfer_بفر_alloc,
                                     hwframe_ctx->ڈیٹا);
}

ساکن صحیح transfer_ڈیٹا_alloc(AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    AVHWFramesContext *ctx;
    AVFrame *چوکھٹا_tmp;
    صحیح ret = 0;

    اگر (!src->hw_چوکھٹے_ctx)
        واپس AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_چوکھٹے_ctx->ڈیٹا;

    چوکھٹا_tmp = av_چوکھٹا_alloc();
    اگر (!چوکھٹا_tmp)
        واپس AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    اگر (dst->format >= 0) {
        چوکھٹا_tmp->format = dst->format;
    } ورنہ {
        شمار AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_چوکھٹے_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        اگر (ret < 0)
            جاؤ fail;
        چوکھٹا_tmp->format = formats[0];
        av_freep(&formats);
    }
    چوکھٹا_tmp->چوڑائی  = ctx->چوڑائی;
    چوکھٹا_tmp->اونچائی = ctx->اونچائی;

    ret = av_hwframe_get_transfer_بفر(src->hw_چوکھٹے_ctx, چوکھٹا_tmp);
    اگر (ret < 0)
        جاؤ fail;

    ret = av_hwframe_transfer_ڈیٹا(چوکھٹا_tmp, src, flags);
    اگر (ret < 0)
        جاؤ fail;

    چوکھٹا_tmp->چوڑائی  = src->چوڑائی;
    چوکھٹا_tmp->اونچائی = src->اونچائی;

    av_چوکھٹا_move_ref(dst, چوکھٹا_tmp);

fail:
    av_چوکھٹا_free(&چوکھٹا_tmp);
    واپس ret;
}

صحیح av_hwframe_transfer_ڈیٹا(AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    صحیح ret;

    اگر (!dst->buf[0])
        واپس transfer_ڈیٹا_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    اگر (src->hw_چوکھٹے_ctx && dst->hw_چوکھٹے_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_چوکھٹے_ctx->ڈیٹا;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_چوکھٹے_ctx->ڈیٹا;

        اگر (src_ctx->ماخذ_چوکھٹے) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            واپس AVERROR(ENOSYS);
        }

        اگر (dst_ctx->ماخذ_چوکھٹے) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            واپس AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        اگر (src_ctx->hw_type->transfer_ڈیٹا_from)
            ret = src_ctx->hw_type->transfer_ڈیٹا_from(&src_ctx->p, dst, src);
        اگر (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_ڈیٹا_مقصد)
            ret = dst_ctx->hw_type->transfer_ڈیٹا_مقصد(&dst_ctx->p, dst, src);
        اگر (ret < 0)
            واپس ret;
    } ورنہ {
        اگر (src->hw_چوکھٹے_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_چوکھٹے_ctx->ڈیٹا;

            اگر (!ctx->hw_type->transfer_ڈیٹا_from)
                واپس AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_ڈیٹا_from(&ctx->p, dst, src);
            اگر (ret < 0)
                واپس ret;
        } ورنہ اگر (dst->hw_چوکھٹے_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_چوکھٹے_ctx->ڈیٹا;

            اگر (!ctx->hw_type->transfer_ڈیٹا_مقصد)
                واپس AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_ڈیٹا_مقصد(&ctx->p, dst, src);
            اگر (ret < 0)
                واپس ret;
        } ورنہ {
            واپس AVERROR(ENOSYS);
        }
    }
    واپس 0;
}

صحیح av_hwframe_get_بفر(AVBufferRef *hwframe_ref, AVFrame *چوکھٹا, صحیح flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->ڈیٹا;
    AVHWFramesContext *ctx  = &ctxi->p;
    صحیح ret;

    اگر (ctxi->ماخذ_چوکھٹے) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_چوکھٹا;

        چوکھٹا->format = ctx->format;
        چوکھٹا->hw_چوکھٹے_ctx = av_بفر_ref(hwframe_ref);
        اگر (!چوکھٹا->hw_چوکھٹے_ctx)
            واپس AVERROR(ENOMEM);

        src_چوکھٹا = av_چوکھٹا_alloc();
        اگر (!src_چوکھٹا)
            واپس AVERROR(ENOMEM);

        ret = av_hwframe_get_بفر(ctxi->ماخذ_چوکھٹے,
                                    src_چوکھٹا, 0);
        اگر (ret < 0) {
            av_چوکھٹا_free(&src_چوکھٹا);
            واپس ret;
        }

        ret = av_hwframe_map(چوکھٹا, src_چوکھٹا,
                             ctxi->ماخذ_تخصیص_map_flags);
        اگر (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_چوکھٹا_free(&src_چوکھٹا);
            واپس ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_چوکھٹا_free(&src_چوکھٹا);

        واپس 0;
    }

    اگر (!ctxi->hw_type->چوکھٹے_get_بفر)
        واپس AVERROR(ENOSYS);

    اگر (!ctx->pool)
        واپس AVERROR(EINVAL);

    چوکھٹا->hw_چوکھٹے_ctx = av_بفر_ref(hwframe_ref);
    اگر (!چوکھٹا->hw_چوکھٹے_ctx)
        واپس AVERROR(ENOMEM);

    ret = ctxi->hw_type->چوکھٹے_get_بفر(ctx, چوکھٹا);
    اگر (ret < 0) {
        av_بفر_unref(&چوکھٹا->hw_چوکھٹے_ctx);
        واپس ret;
    }

    چوکھٹا->extended_ڈیٹا = چوکھٹا->ڈیٹا;

    واپس 0;
}

خالی *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->ڈیٹا;
    ثابت HWContextType  *hw_type = ctx->hw_type;

    اگر (hw_type->device_hwconfig_سائز == 0)
        واپس تہی;

    واپس av_mallocz(hw_type->device_hwconfig_سائز);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ثابت خالی *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->ڈیٹا;
    ثابت HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    اگر (!hw_type->چوکھٹے_get_constraints)
        واپس تہی;

    constraints = av_mallocz(حجم(*constraints));
    اگر (!constraints)
        واپس تہی;

    constraints->min_چوڑائی = constraints->min_اونچائی = 0;
    constraints->max_چوڑائی = constraints->max_اونچائی = زیادہ_سے_زیادہ_عدد;

    اگر (hw_type->چوکھٹے_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        واپس constraints;
    } ورنہ {
        av_hwframe_constraints_free(&constraints);
        واپس تہی;
    }
}

خالی av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    اگر (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

صحیح av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, شمار AVHWDeviceType type,
                           ثابت حرف *device, AVDictionary *opts, صحیح flags)
{
    AVBufferRef *device_ref = تہی;
    FFHWDeviceContext *device_ctx;
    صحیح ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    اگر (!device_ref) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->ڈیٹا;

    اگر (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        جاؤ fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    اگر (ret < 0)
        جاؤ fail;

    ret = av_hwdevice_ctx_init(device_ref);
    اگر (ret < 0)
        جاؤ fail;

    *pdevice_ref = device_ref;
    واپس 0;
fail:
    av_بفر_unref(&device_ref);
    *pdevice_ref = تہی;
    واپس ret;
}

صحیح av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        شمار AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, صحیح flags)
{
    AVBufferRef *dst_ref = تہی, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    صحیح ret = 0;

    tmp_ref = src_ref;
    جب (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->ڈیٹا;
        اگر (tmp_ctx->p.type == type) {
            dst_ref = av_بفر_ref(tmp_ref);
            اگر (!dst_ref) {
                ret = AVERROR(ENOMEM);
                جاؤ fail;
            }
            جاؤ مکمل;
        }
        tmp_ref = tmp_ctx->ماخذ_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    اگر (!dst_ref) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->ڈیٹا;

    tmp_ref = src_ref;
    جب (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->ڈیٹا;
        اگر (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            اگر (ret == 0) {
                dst_ctx->ماخذ_device = av_بفر_ref(src_ref);
                اگر (!dst_ctx->ماخذ_device) {
                    ret = AVERROR(ENOMEM);
                    جاؤ fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                اگر (ret < 0)
                    جاؤ fail;
                جاؤ مکمل;
            }
            اگر (ret != AVERROR(ENOSYS))
                جاؤ fail;
        }
        tmp_ref = tmp_ctx->ماخذ_device;
    }

    ret = AVERROR(ENOSYS);
    جاؤ fail;

مکمل:
    *dst_ref_ptr = dst_ref;
    واپس 0;

fail:
    av_بفر_unref(&dst_ref);
    *dst_ref_ptr = تہی;
    واپس ret;
}

صحیح av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   شمار AVHWDeviceType type,
                                   AVBufferRef *src_ref, صحیح flags)
{
    واپس av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               تہی, flags);
}

ساکن خالی ff_hwframe_unmap(خالی *opaque, uint8_t *ڈیٹا)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)ڈیٹا;
    AVHWFramesContext *ctx = opaque;

    اگر (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_چوکھٹا_free(&hwmap->ماخذ);

    av_بفر_unref(&hwmap->hw_چوکھٹے_ctx);

    av_free(hwmap);
}

صحیح ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ثابت AVFrame *src,
                          خالی (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          خالی *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->ڈیٹا;
    HWMapDescriptor *hwmap;
    صحیح ret;

    hwmap = av_mallocz(حجم(*hwmap));
    اگر (!hwmap) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }

    hwmap->ماخذ = av_چوکھٹا_alloc();
    اگر (!hwmap->ماخذ) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }
    ret = av_چوکھٹا_ref(hwmap->ماخذ, src);
    اگر (ret < 0)
        جاؤ fail;

    hwmap->hw_چوکھٹے_ctx = av_بفر_ref(hwframe_ref);
    اگر (!hwmap->hw_چوکھٹے_ctx) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_بفر_create((uint8_t*)hwmap, حجم(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    اگر (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }

    واپس 0;

fail:
    اگر (hwmap) {
        av_بفر_unref(&hwmap->hw_چوکھٹے_ctx);
        av_چوکھٹا_free(&hwmap->ماخذ);
    }
    av_free(hwmap);
    واپس ret;
}

صحیح av_hwframe_map(AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    AVBufferRef    *orig_dst_چوکھٹے = dst->hw_چوکھٹے_ctx;
    شمار AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    صحیح ret;

    اگر (src->hw_چوکھٹے_ctx && dst->hw_چوکھٹے_ctx) {
        FFHWFramesContext *src_چوکھٹے = (FFHWFramesContext*)src->hw_چوکھٹے_ctx->ڈیٹا;
        FFHWFramesContext *dst_چوکھٹے = (FFHWFramesContext*)dst->hw_چوکھٹے_ctx->ڈیٹا;

        اگر ((src_چوکھٹے == dst_چوکھٹے &&
             src->format == dst_چوکھٹے->p.sw_format &&
             dst->format == dst_چوکھٹے->p.format) ||
            (src_چوکھٹے->ماخذ_چوکھٹے &&
             src_چوکھٹے->ماخذ_چوکھٹے->ڈیٹا ==
             (uint8_t*)dst_چوکھٹے)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            اگر (!src->buf[0]) {
                av_log(src_چوکھٹے, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                واپس AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->ڈیٹا;
            واپس av_چوکھٹا_replace(dst, hwmap->ماخذ);
        }
    }

    اگر (src->hw_چوکھٹے_ctx) {
        FFHWFramesContext *src_چوکھٹے = (FFHWFramesContext*)src->hw_چوکھٹے_ctx->ڈیٹا;

        اگر (src_چوکھٹے->p.format == src->format &&
            src_چوکھٹے->hw_type->map_from) {
            ret = src_چوکھٹے->hw_type->map_from(&src_چوکھٹے->p,
                                                dst, src, flags);
            اگر (ret >= 0)
                واپس ret;
            ورنہ اگر (ret != AVERROR(ENOSYS))
                جاؤ fail;
        }
    }

    اگر (dst->hw_چوکھٹے_ctx) {
        FFHWFramesContext *dst_چوکھٹے = (FFHWFramesContext*)dst->hw_چوکھٹے_ctx->ڈیٹا;

        اگر (dst_چوکھٹے->p.format == dst->format &&
            dst_چوکھٹے->hw_type->map_مقصد) {
            ret = dst_چوکھٹے->hw_type->map_مقصد(&dst_چوکھٹے->p,
                                              dst, src, flags);
            اگر (ret >= 0)
                واپس ret;
            ورنہ اگر (ret != AVERROR(ENOSYS))
                جاؤ fail;
        }
    }

    واپس AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_چوکھٹے == تہی ||
               orig_dst_چوکھٹے == dst->hw_چوکھٹے_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_چوکھٹے_ctx = تہی;
    av_چوکھٹا_unref(dst);

    dst->hw_چوکھٹے_ctx = orig_dst_چوکھٹے;
    dst->format        = orig_dst_fmt;

    واپس ret;
}

صحیح av_hwframe_ctx_create_derived(AVBufferRef **derived_چوکھٹا_ctx,
                                  شمار AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *ماخذ_چوکھٹا_ctx,
                                  صحیح flags)
{
    AVBufferRef   *dst_ref = تہی;
    FFHWFramesContext *dsti = تہی;
    FFHWFramesContext *srci = (FFHWFramesContext*)ماخذ_چوکھٹا_ctx->ڈیٹا;
    AVHWFramesContext *dst, *src = &srci->p;
    صحیح ret;

    اگر (srci->ماخذ_چوکھٹے) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->ماخذ_چوکھٹے->ڈیٹا;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->ڈیٹا;

        اگر (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_چوکھٹا_ctx = av_بفر_ref(srci->ماخذ_چوکھٹے);
            اگر (!*derived_چوکھٹا_ctx) {
                ret = AVERROR(ENOMEM);
                جاؤ fail;
            }
            واپس 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    اگر (!dst_ref) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->ڈیٹا;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->چوڑائی     = src->چوڑائی;
    dst->اونچائی    = src->اونچائی;

    dsti->ماخذ_چوکھٹے = av_بفر_ref(ماخذ_چوکھٹا_ctx);
    اگر (!dsti->ماخذ_چوکھٹے) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }

    dsti->ماخذ_تخصیص_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_براہ_راست);

    ret = AVERROR(ENOSYS);
    اگر (srci->hw_type->چوکھٹے_derive_from)
        ret = srci->hw_type->چوکھٹے_derive_from(dst, src, flags);
    اگر (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->چوکھٹے_derive_مقصد)
        ret = dsti->hw_type->چوکھٹے_derive_مقصد(dst, src, flags);
    اگر (ret == AVERROR(ENOSYS))
        ret = 0;
    اگر (ret)
        جاؤ fail;

    *derived_چوکھٹا_ctx = dst_ref;
    واپس 0;

fail:
    اگر (dsti)
        av_بفر_unref(&dsti->ماخذ_چوکھٹے);
    av_بفر_unref(&dst_ref);
    واپس ret;
}

صحیح ff_hwframe_map_replace(AVFrame *dst, ثابت AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->ڈیٹا;
    واپس av_چوکھٹا_replace(hwmap->ماخذ, src);
}
