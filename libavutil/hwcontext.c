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

#ضمن "config.h"

#ضمن "avassert.h"
#ضمن "buffer.h"
#ضمن "common.h"
#ضمن "frame_internal.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_internal.h"
#ضمن "imgutils.h"
#ضمن "log.h"
#ضمن "mem.h"
#ضمن "pixdesc.h"
#ضمن "pixfmt.h"

ساكن ثابت HWContextType * ثابت hw_جدول[] = {
#إذا CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#پایان_اگر
#إذا CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#پایان_اگر
#إذا CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#پایان_اگر
#إذا CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#پایان_اگر
#إذا CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#پایان_اگر
#إذا CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#پایان_اگر
#إذا CONFIG_QSV
    &ff_hwcontext_type_qsv,
#پایان_اگر
#إذا CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#پایان_اگر
#إذا CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#پایان_اگر
#إذا CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#پایان_اگر
#إذا CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#پایان_اگر
#إذا CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#پایان_اگر
#إذا CONFIG_AMF
    &ff_hwcontext_type_amf,
#پایان_اگر
#إذا CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#پایان_اگر
    عدم,
};

ساكن ثابت حرف *ثابت hw_type_نامها[] = {
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

تعريفنوع بنية FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    ثابت HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *منبع_device;
} FFHWDeviceContext;

تعداد AVHWDeviceType av_hwdevice_پیدا_کن_type_by_name(ثابت حرف *name)
{
    صحيح type;
    لكل (type = 0; type < FF_ARRAY_ELEMS(hw_type_نامها); type++) {
        إذا (hw_type_نامها[type] && !strcmp(hw_type_نامها[type], name))
            أرجع type;
    }
    أرجع AV_HWDEVICE_TYPE_NONE;
}

ثابت حرف *av_hwdevice_get_type_name(تعداد AVHWDeviceType type)
{
    إذا (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_نامها))
        أرجع hw_type_نامها[type];
    وإلا
        أرجع عدم;
}

تعداد AVHWDeviceType av_hwdevice_iterate_types(تعداد AVHWDeviceType prev)
{
    تعداد AVHWDeviceType بعدی;
    صحيح i, مجموعه = 0;
    لكل (i = 0; hw_جدول[i]; i++) {
        إذا (prev != AV_HWDEVICE_TYPE_NONE && hw_جدول[i]->type <= prev)
            استمر;
        إذا (!مجموعه || hw_جدول[i]->type < بعدی) {
            بعدی = hw_جدول[i]->type;
            مجموعه = 1;
        }
    }
    أرجع مجموعه ? بعدی : AV_HWDEVICE_TYPE_NONE;
}

ساكن ثابت حرف *hwdevice_ctx_get_name(فراغ *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    أرجع ctx->hw_type->name;
}

ساكن ثابت AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .قلم_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .نسخه    = LIBAVUTIL_نسخه_INT,
};

ساكن فراغ hwdevice_ctx_free(فراغ *opaque, uint8_t *داده)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)داده;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    إذا (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    إذا (ctx->حرر)
        ctx->حرر(ctx);

    av_میانگیر_unref(&ctxi->منبع_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(تعداد AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    ثابت HWContextType *hw_type = عدم;
    صحيح i;

    لكل (i = 0; hw_جدول[i]; i++) {
        إذا (hw_جدول[i]->type == type) {
            hw_type = hw_جدول[i];
            اكسر;
        }
    }
    إذا (!hw_type)
        أرجع عدم;

    ctxi = av_mallocz(حجم(*ctxi));
    إذا (!ctxi)
        أرجع عدم;
    ctx = &ctxi->p;

    إذا (hw_type->device_hwctx_اندازه) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_اندازه);
        إذا (!ctx->hwctx)
            اذهب fail;
    }

    buf = av_میانگیر_create((uint8_t*)ctx, حجم(*ctx),
                           hwdevice_ctx_free, عدم,
                           AV_میانگیر_FLAG_READONLY);
    إذا (!buf)
        اذهب fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    أرجع buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    أرجع عدم;
}

صحيح av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->داده;
    AVHWDeviceContext *ctx  = &ctxi->p;
    صحيح ret = 0;

    إذا (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    أرجع ret;
}

ساكن ثابت AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .قلم_name  = av_default_قلم_name,
    .نسخه    = LIBAVUTIL_نسخه_INT,
};

ساكن فراغ hwframe_ctx_free(فراغ *opaque, uint8_t *داده)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)داده;
    AVHWFramesContext *ctx  = &ctxi->p;

    إذا (ctxi->pool_داخلی)
        av_میانگیر_pool_uninit(&ctxi->pool_داخلی);

    av_میانگیر_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_قفل);

    إذا (ctxi->hw_type->قابها_uninit)
        ctxi->hw_type->قابها_uninit(ctx);

    إذا (ctx->حرر)
        ctx->حرر(ctx);

    av_میانگیر_unref(&ctxi->منبع_قابها);

    av_میانگیر_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_درون)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_درون->داده;
    ثابت HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = عدم;

    ctxi = av_mallocz(حجم(*ctxi));
    إذا (!ctxi)
        أرجع عدم;
    ctx  = &ctxi->p;

    إذا (ff_mutex_init(&ctxi->transfer_pool_قفل, عدم)) {
        av_free(ctxi);
        أرجع عدم;
    }

    إذا (hw_type->قابها_hwctx_اندازه) {
        ctx->hwctx = av_mallocz(hw_type->قابها_hwctx_اندازه);
        إذا (!ctx->hwctx)
            اذهب fail;
    }

    device_ref = av_میانگیر_ref(device_ref_درون);
    إذا (!device_ref)
        اذهب fail;

    buf = av_میانگیر_create((uint8_t*)ctx, حجم(*ctx),
                           hwframe_ctx_free, عدم,
                           AV_میانگیر_FLAG_READONLY);
    إذا (!buf)
        اذهب fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    أرجع buf;

fail:
    av_میانگیر_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_قفل);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    أرجع عدم;
}

ساكن صحيح hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->داده;
    AVFrame **قابها;
    صحيح i, ret = 0;

    قابها = av_calloc(ctx->initial_pool_اندازه, حجم(*قابها));
    إذا (!قابها)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < ctx->initial_pool_اندازه; i++) {
        قابها[i] = av_قاب_alloc();
        إذا (!قابها[i])
            اذهب fail;

        ret = av_hwframe_get_میانگیر(ref, قابها[i], 0);
        إذا (ret < 0)
            اذهب fail;
    }

fail:
    لكل (i = 0; i < ctx->initial_pool_اندازه; i++)
        av_قاب_free(&قابها[i]);
    av_freep(&قابها);

    أرجع ret;
}

صحيح av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->داده;
    AVHWFramesContext *ctx  = &ctxi->p;
    ثابت تعداد AVPixelFormat *pix_fmt;
    صحيح ret;

    إذا (ctxi->منبع_قابها) {
        /* A derived frame context is already initialised. */
        أرجع 0;
    }

    /* validate the pixel format */
    لكل (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        إذا (*pix_fmt == ctx->format)
            اكسر;
    }
    إذا (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        أرجع AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_اندازه(ctx->عرض, ctx->ارتفاع, 0, ctx);
    إذا (ret < 0)
        أرجع ret;

    /* format-specific init */
    إذا (ctxi->hw_type->قابها_init) {
        ret = ctxi->hw_type->قابها_init(ctx);
        إذا (ret < 0)
            أرجع ret;
    }

    إذا (ctxi->pool_داخلی && !ctx->pool)
        ctx->pool = ctxi->pool_داخلی;

    /* preallocate the frames in the pool, if requested */
    إذا (ctx->initial_pool_اندازه > 0) {
        ret = hwframe_pool_prealloc(ref);
        إذا (ret < 0)
            أرجع ret;
    }

    أرجع 0;
}

صحيح av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    تعداد AVHWFrameTransferDirection dir,
                                    تعداد AVPixelFormat **formats, صحيح flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->داده;

    إذا (!ctxi->hw_type->transfer_get_formats)
        أرجع AVERROR(ENOSYS);

    أرجع ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

ساكن فراغ transfer_pool_free(فراغ *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_میانگیر_unref(&device_ref);
}

ساكن AVBufferRef *transfer_میانگیر_alloc(فراغ *opaque, size_t اندازه)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = عدم;

    ff_mutex_قفل(&ctxi->transfer_pool_قفل);
    إذا (ctxi->transfer_pool_اندازه != اندازه) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_میانگیر_alloc ?
                                  av_میانگیر_ref(ctxi->p.device_ref) : عدم;

        av_میانگیر_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_میانگیر_pool_init2(اندازه, device_ref,
                                 ctxi->hw_type->transfer_میانگیر_alloc,
                                 transfer_pool_free) :
            av_میانگیر_pool_init(اندازه, عدم);
        ctxi->transfer_pool_اندازه = ctxi->transfer_pool ? اندازه : 0;
        إذا (!ctxi->transfer_pool)
            av_میانگیر_unref(&device_ref);
    }
    إذا (ctxi->transfer_pool)
        buf = av_میانگیر_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_قفل);

    أرجع buf ? buf : av_میانگیر_alloc(اندازه);
}

صحيح av_hwframe_get_transfer_میانگیر(AVBufferRef *hwframe_ctx, AVFrame *قاب)
{
    أرجع ff_قاب_get_video_میانگیر(قاب, 0, transfer_میانگیر_alloc,
                                     hwframe_ctx->داده);
}

ساكن صحيح transfer_داده_alloc(AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVHWFramesContext *ctx;
    AVFrame *قاب_tmp;
    صحيح ret = 0;

    إذا (!src->hw_قابها_ctx)
        أرجع AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_قابها_ctx->داده;

    قاب_tmp = av_قاب_alloc();
    إذا (!قاب_tmp)
        أرجع AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    إذا (dst->format >= 0) {
        قاب_tmp->format = dst->format;
    } وإلا {
        تعداد AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_قابها_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        إذا (ret < 0)
            اذهب fail;
        قاب_tmp->format = formats[0];
        av_freep(&formats);
    }
    قاب_tmp->عرض  = ctx->عرض;
    قاب_tmp->ارتفاع = ctx->ارتفاع;

    ret = av_hwframe_get_transfer_میانگیر(src->hw_قابها_ctx, قاب_tmp);
    إذا (ret < 0)
        اذهب fail;

    ret = av_hwframe_transfer_داده(قاب_tmp, src, flags);
    إذا (ret < 0)
        اذهب fail;

    قاب_tmp->عرض  = src->عرض;
    قاب_tmp->ارتفاع = src->ارتفاع;

    av_قاب_move_ref(dst, قاب_tmp);

fail:
    av_قاب_free(&قاب_tmp);
    أرجع ret;
}

صحيح av_hwframe_transfer_داده(AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    صحيح ret;

    إذا (!dst->buf[0])
        أرجع transfer_داده_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    إذا (src->hw_قابها_ctx && dst->hw_قابها_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_قابها_ctx->داده;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_قابها_ctx->داده;

        إذا (src_ctx->منبع_قابها) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            أرجع AVERROR(ENOSYS);
        }

        إذا (dst_ctx->منبع_قابها) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            أرجع AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        إذا (src_ctx->hw_type->transfer_داده_from)
            ret = src_ctx->hw_type->transfer_داده_from(&src_ctx->p, dst, src);
        إذا (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_داده_مقصد)
            ret = dst_ctx->hw_type->transfer_داده_مقصد(&dst_ctx->p, dst, src);
        إذا (ret < 0)
            أرجع ret;
    } وإلا {
        إذا (src->hw_قابها_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_قابها_ctx->داده;

            إذا (!ctx->hw_type->transfer_داده_from)
                أرجع AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_داده_from(&ctx->p, dst, src);
            إذا (ret < 0)
                أرجع ret;
        } وإلا إذا (dst->hw_قابها_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_قابها_ctx->داده;

            إذا (!ctx->hw_type->transfer_داده_مقصد)
                أرجع AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_داده_مقصد(&ctx->p, dst, src);
            إذا (ret < 0)
                أرجع ret;
        } وإلا {
            أرجع AVERROR(ENOSYS);
        }
    }
    أرجع 0;
}

صحيح av_hwframe_get_میانگیر(AVBufferRef *hwframe_ref, AVFrame *قاب, صحيح flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->داده;
    AVHWFramesContext *ctx  = &ctxi->p;
    صحيح ret;

    إذا (ctxi->منبع_قابها) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_قاب;

        قاب->format = ctx->format;
        قاب->hw_قابها_ctx = av_میانگیر_ref(hwframe_ref);
        إذا (!قاب->hw_قابها_ctx)
            أرجع AVERROR(ENOMEM);

        src_قاب = av_قاب_alloc();
        إذا (!src_قاب)
            أرجع AVERROR(ENOMEM);

        ret = av_hwframe_get_میانگیر(ctxi->منبع_قابها,
                                    src_قاب, 0);
        إذا (ret < 0) {
            av_قاب_free(&src_قاب);
            أرجع ret;
        }

        ret = av_hwframe_map(قاب, src_قاب,
                             ctxi->منبع_تخصیص_map_flags);
        إذا (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_قاب_free(&src_قاب);
            أرجع ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_قاب_free(&src_قاب);

        أرجع 0;
    }

    إذا (!ctxi->hw_type->قابها_get_میانگیر)
        أرجع AVERROR(ENOSYS);

    إذا (!ctx->pool)
        أرجع AVERROR(EINVAL);

    قاب->hw_قابها_ctx = av_میانگیر_ref(hwframe_ref);
    إذا (!قاب->hw_قابها_ctx)
        أرجع AVERROR(ENOMEM);

    ret = ctxi->hw_type->قابها_get_میانگیر(ctx, قاب);
    إذا (ret < 0) {
        av_میانگیر_unref(&قاب->hw_قابها_ctx);
        أرجع ret;
    }

    قاب->extended_داده = قاب->داده;

    أرجع 0;
}

فراغ *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->داده;
    ثابت HWContextType  *hw_type = ctx->hw_type;

    إذا (hw_type->device_hwconfig_اندازه == 0)
        أرجع عدم;

    أرجع av_mallocz(hw_type->device_hwconfig_اندازه);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ثابت فراغ *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->داده;
    ثابت HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    إذا (!hw_type->قابها_get_constraints)
        أرجع عدم;

    constraints = av_mallocz(حجم(*constraints));
    إذا (!constraints)
        أرجع عدم;

    constraints->min_عرض = constraints->min_ارتفاع = 0;
    constraints->max_عرض = constraints->max_ارتفاع = بیشترین_صحیح;

    إذا (hw_type->قابها_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        أرجع constraints;
    } وإلا {
        av_hwframe_constraints_free(&constraints);
        أرجع عدم;
    }
}

فراغ av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    إذا (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

صحيح av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, تعداد AVHWDeviceType type,
                           ثابت حرف *device, AVDictionary *opts, صحيح flags)
{
    AVBufferRef *device_ref = عدم;
    FFHWDeviceContext *device_ctx;
    صحيح ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    إذا (!device_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->داده;

    إذا (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        اذهب fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    إذا (ret < 0)
        اذهب fail;

    ret = av_hwdevice_ctx_init(device_ref);
    إذا (ret < 0)
        اذهب fail;

    *pdevice_ref = device_ref;
    أرجع 0;
fail:
    av_میانگیر_unref(&device_ref);
    *pdevice_ref = عدم;
    أرجع ret;
}

صحيح av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        تعداد AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, صحيح flags)
{
    AVBufferRef *dst_ref = عدم, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    صحيح ret = 0;

    tmp_ref = src_ref;
    طالما (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->داده;
        إذا (tmp_ctx->p.type == type) {
            dst_ref = av_میانگیر_ref(tmp_ref);
            إذا (!dst_ref) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
            اذهب انجامشده;
        }
        tmp_ref = tmp_ctx->منبع_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    إذا (!dst_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->داده;

    tmp_ref = src_ref;
    طالما (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->داده;
        إذا (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            إذا (ret == 0) {
                dst_ctx->منبع_device = av_میانگیر_ref(src_ref);
                إذا (!dst_ctx->منبع_device) {
                    ret = AVERROR(ENOMEM);
                    اذهب fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                إذا (ret < 0)
                    اذهب fail;
                اذهب انجامشده;
            }
            إذا (ret != AVERROR(ENOSYS))
                اذهب fail;
        }
        tmp_ref = tmp_ctx->منبع_device;
    }

    ret = AVERROR(ENOSYS);
    اذهب fail;

انجامشده:
    *dst_ref_ptr = dst_ref;
    أرجع 0;

fail:
    av_میانگیر_unref(&dst_ref);
    *dst_ref_ptr = عدم;
    أرجع ret;
}

صحيح av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   تعداد AVHWDeviceType type,
                                   AVBufferRef *src_ref, صحيح flags)
{
    أرجع av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               عدم, flags);
}

ساكن فراغ ff_hwframe_unmap(فراغ *opaque, uint8_t *داده)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)داده;
    AVHWFramesContext *ctx = opaque;

    إذا (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_قاب_free(&hwmap->منبع);

    av_میانگیر_unref(&hwmap->hw_قابها_ctx);

    av_free(hwmap);
}

صحيح ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ثابت AVFrame *src,
                          فراغ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          فراغ *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->داده;
    HWMapDescriptor *hwmap;
    صحيح ret;

    hwmap = av_mallocz(حجم(*hwmap));
    إذا (!hwmap) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    hwmap->منبع = av_قاب_alloc();
    إذا (!hwmap->منبع) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    ret = av_قاب_ref(hwmap->منبع, src);
    إذا (ret < 0)
        اذهب fail;

    hwmap->hw_قابها_ctx = av_میانگیر_ref(hwframe_ref);
    إذا (!hwmap->hw_قابها_ctx) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_میانگیر_create((uint8_t*)hwmap, حجم(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    إذا (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    أرجع 0;

fail:
    إذا (hwmap) {
        av_میانگیر_unref(&hwmap->hw_قابها_ctx);
        av_قاب_free(&hwmap->منبع);
    }
    av_free(hwmap);
    أرجع ret;
}

صحيح av_hwframe_map(AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVBufferRef    *orig_dst_قابها = dst->hw_قابها_ctx;
    تعداد AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    صحيح ret;

    إذا (src->hw_قابها_ctx && dst->hw_قابها_ctx) {
        FFHWFramesContext *src_قابها = (FFHWFramesContext*)src->hw_قابها_ctx->داده;
        FFHWFramesContext *dst_قابها = (FFHWFramesContext*)dst->hw_قابها_ctx->داده;

        إذا ((src_قابها == dst_قابها &&
             src->format == dst_قابها->p.sw_format &&
             dst->format == dst_قابها->p.format) ||
            (src_قابها->منبع_قابها &&
             src_قابها->منبع_قابها->داده ==
             (uint8_t*)dst_قابها)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            إذا (!src->buf[0]) {
                av_log(src_قابها, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                أرجع AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->داده;
            أرجع av_قاب_replace(dst, hwmap->منبع);
        }
    }

    إذا (src->hw_قابها_ctx) {
        FFHWFramesContext *src_قابها = (FFHWFramesContext*)src->hw_قابها_ctx->داده;

        إذا (src_قابها->p.format == src->format &&
            src_قابها->hw_type->map_from) {
            ret = src_قابها->hw_type->map_from(&src_قابها->p,
                                                dst, src, flags);
            إذا (ret >= 0)
                أرجع ret;
            وإلا إذا (ret != AVERROR(ENOSYS))
                اذهب fail;
        }
    }

    إذا (dst->hw_قابها_ctx) {
        FFHWFramesContext *dst_قابها = (FFHWFramesContext*)dst->hw_قابها_ctx->داده;

        إذا (dst_قابها->p.format == dst->format &&
            dst_قابها->hw_type->map_مقصد) {
            ret = dst_قابها->hw_type->map_مقصد(&dst_قابها->p,
                                              dst, src, flags);
            إذا (ret >= 0)
                أرجع ret;
            وإلا إذا (ret != AVERROR(ENOSYS))
                اذهب fail;
        }
    }

    أرجع AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_قابها == عدم ||
               orig_dst_قابها == dst->hw_قابها_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_قابها_ctx = عدم;
    av_قاب_unref(dst);

    dst->hw_قابها_ctx = orig_dst_قابها;
    dst->format        = orig_dst_fmt;

    أرجع ret;
}

صحيح av_hwframe_ctx_create_derived(AVBufferRef **derived_قاب_ctx,
                                  تعداد AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *منبع_قاب_ctx,
                                  صحيح flags)
{
    AVBufferRef   *dst_ref = عدم;
    FFHWFramesContext *dsti = عدم;
    FFHWFramesContext *srci = (FFHWFramesContext*)منبع_قاب_ctx->داده;
    AVHWFramesContext *dst, *src = &srci->p;
    صحيح ret;

    إذا (srci->منبع_قابها) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->منبع_قابها->داده;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->داده;

        إذا (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_قاب_ctx = av_میانگیر_ref(srci->منبع_قابها);
            إذا (!*derived_قاب_ctx) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
            أرجع 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    إذا (!dst_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->داده;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->عرض     = src->عرض;
    dst->ارتفاع    = src->ارتفاع;

    dsti->منبع_قابها = av_میانگیر_ref(منبع_قاب_ctx);
    إذا (!dsti->منبع_قابها) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    dsti->منبع_تخصیص_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_مستقیم);

    ret = AVERROR(ENOSYS);
    إذا (srci->hw_type->قابها_derive_from)
        ret = srci->hw_type->قابها_derive_from(dst, src, flags);
    إذا (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->قابها_derive_مقصد)
        ret = dsti->hw_type->قابها_derive_مقصد(dst, src, flags);
    إذا (ret == AVERROR(ENOSYS))
        ret = 0;
    إذا (ret)
        اذهب fail;

    *derived_قاب_ctx = dst_ref;
    أرجع 0;

fail:
    إذا (dsti)
        av_میانگیر_unref(&dsti->منبع_قابها);
    av_میانگیر_unref(&dst_ref);
    أرجع ret;
}

صحيح ff_hwframe_map_replace(AVFrame *dst, ثابت AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->داده;
    أرجع av_قاب_replace(hwmap->منبع, src);
}
