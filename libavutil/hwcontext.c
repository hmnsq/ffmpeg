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
#د_که_پای
#إذا CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#د_که_پای
#إذا CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#د_که_پای
#إذا CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#د_که_پای
#إذا CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#د_که_پای
#إذا CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#د_که_پای
#إذا CONFIG_QSV
    &ff_hwcontext_type_qsv,
#د_که_پای
#إذا CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#د_که_پای
#إذا CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#د_که_پای
#إذا CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#د_که_پای
#إذا CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#د_که_پای
#إذا CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#د_که_پای
#إذا CONFIG_AMF
    &ff_hwcontext_type_amf,
#د_که_پای
#إذا CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#د_که_پای
    عدم,
};

ساكن ثابت حرف *ثابت hw_type_نومونه[] = {
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
    AVBufferRef *سرچینه_device;
} FFHWDeviceContext;

تعداد AVHWDeviceType av_hwdevice_پیدا_کړه_type_by_name(ثابت حرف *name)
{
    صحيح type;
    لكل (type = 0; type < FF_ARRAY_ELEMS(hw_type_نومونه); type++) {
        إذا (hw_type_نومونه[type] && !strcmp(hw_type_نومونه[type], name))
            أرجع type;
    }
    أرجع AV_HWDEVICE_TYPE_NONE;
}

ثابت حرف *av_hwdevice_get_type_name(تعداد AVHWDeviceType type)
{
    إذا (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_نومونه))
        أرجع hw_type_نومونه[type];
    وإلا
        أرجع عدم;
}

تعداد AVHWDeviceType av_hwdevice_iterate_types(تعداد AVHWDeviceType prev)
{
    تعداد AVHWDeviceType بل;
    صحيح i, سېټ = 0;
    لكل (i = 0; hw_جدول[i]; i++) {
        إذا (prev != AV_HWDEVICE_TYPE_NONE && hw_جدول[i]->type <= prev)
            استمر;
        إذا (!سېټ || hw_جدول[i]->type < بل) {
            بل = hw_جدول[i]->type;
            سېټ = 1;
        }
    }
    أرجع سېټ ? بل : AV_HWDEVICE_TYPE_NONE;
}

ساكن ثابت حرف *hwdevice_ctx_get_name(فراغ *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    أرجع ctx->hw_type->name;
}

ساكن ثابت AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .توکی_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .نسخه    = LIBAVUTIL_نسخه_INT,
};

ساكن فراغ hwdevice_ctx_free(فراغ *opaque, uint8_t *معلومات)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)معلومات;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    إذا (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    إذا (ctx->حرر)
        ctx->حرر(ctx);

    av_بفر_unref(&ctxi->سرچینه_device);

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

    buf = av_بفر_create((uint8_t*)ctx, حجم(*ctx),
                           hwdevice_ctx_free, عدم,
                           AV_بفر_FLAG_READONLY);
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
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->معلومات;
    AVHWDeviceContext *ctx  = &ctxi->p;
    صحيح ret = 0;

    إذا (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    أرجع ret;
}

ساكن ثابت AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .توکی_name  = av_default_توکی_name,
    .نسخه    = LIBAVUTIL_نسخه_INT,
};

ساكن فراغ hwframe_ctx_free(فراغ *opaque, uint8_t *معلومات)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)معلومات;
    AVHWFramesContext *ctx  = &ctxi->p;

    إذا (ctxi->pool_دننی)
        av_بفر_pool_uninit(&ctxi->pool_دننی);

    av_بفر_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_قلف);

    إذا (ctxi->hw_type->چوکاټونه_uninit)
        ctxi->hw_type->چوکاټونه_uninit(ctx);

    إذا (ctx->حرر)
        ctx->حرر(ctx);

    av_بفر_unref(&ctxi->سرچینه_چوکاټونه);

    av_بفر_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_دننه)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_دننه->معلومات;
    ثابت HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = عدم;

    ctxi = av_mallocz(حجم(*ctxi));
    إذا (!ctxi)
        أرجع عدم;
    ctx  = &ctxi->p;

    إذا (ff_mutex_init(&ctxi->transfer_pool_قلف, عدم)) {
        av_free(ctxi);
        أرجع عدم;
    }

    إذا (hw_type->چوکاټونه_hwctx_اندازه) {
        ctx->hwctx = av_mallocz(hw_type->چوکاټونه_hwctx_اندازه);
        إذا (!ctx->hwctx)
            اذهب fail;
    }

    device_ref = av_بفر_ref(device_ref_دننه);
    إذا (!device_ref)
        اذهب fail;

    buf = av_بفر_create((uint8_t*)ctx, حجم(*ctx),
                           hwframe_ctx_free, عدم,
                           AV_بفر_FLAG_READONLY);
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
    av_بفر_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_قلف);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    أرجع عدم;
}

ساكن صحيح hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->معلومات;
    AVFrame **چوکاټونه;
    صحيح i, ret = 0;

    چوکاټونه = av_calloc(ctx->initial_pool_اندازه, حجم(*چوکاټونه));
    إذا (!چوکاټونه)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < ctx->initial_pool_اندازه; i++) {
        چوکاټونه[i] = av_چوکاټ_alloc();
        إذا (!چوکاټونه[i])
            اذهب fail;

        ret = av_hwframe_get_بفر(ref, چوکاټونه[i], 0);
        إذا (ret < 0)
            اذهب fail;
    }

fail:
    لكل (i = 0; i < ctx->initial_pool_اندازه; i++)
        av_چوکاټ_free(&چوکاټونه[i]);
    av_freep(&چوکاټونه);

    أرجع ret;
}

صحيح av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->معلومات;
    AVHWFramesContext *ctx  = &ctxi->p;
    ثابت تعداد AVPixelFormat *pix_fmt;
    صحيح ret;

    إذا (ctxi->سرچینه_چوکاټونه) {
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
    ret = av_image_check_اندازه(ctx->پلنوالی, ctx->لوړوالی, 0, ctx);
    إذا (ret < 0)
        أرجع ret;

    /* format-specific init */
    إذا (ctxi->hw_type->چوکاټونه_init) {
        ret = ctxi->hw_type->چوکاټونه_init(ctx);
        إذا (ret < 0)
            أرجع ret;
    }

    إذا (ctxi->pool_دننی && !ctx->pool)
        ctx->pool = ctxi->pool_دننی;

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
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->معلومات;

    إذا (!ctxi->hw_type->transfer_get_formats)
        أرجع AVERROR(ENOSYS);

    أرجع ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

ساكن فراغ transfer_pool_free(فراغ *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_بفر_unref(&device_ref);
}

ساكن AVBufferRef *transfer_بفر_alloc(فراغ *opaque, size_t اندازه)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = عدم;

    ff_mutex_قلف(&ctxi->transfer_pool_قلف);
    إذا (ctxi->transfer_pool_اندازه != اندازه) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_بفر_alloc ?
                                  av_بفر_ref(ctxi->p.device_ref) : عدم;

        av_بفر_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_بفر_pool_init2(اندازه, device_ref,
                                 ctxi->hw_type->transfer_بفر_alloc,
                                 transfer_pool_free) :
            av_بفر_pool_init(اندازه, عدم);
        ctxi->transfer_pool_اندازه = ctxi->transfer_pool ? اندازه : 0;
        إذا (!ctxi->transfer_pool)
            av_بفر_unref(&device_ref);
    }
    إذا (ctxi->transfer_pool)
        buf = av_بفر_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_قلف);

    أرجع buf ? buf : av_بفر_alloc(اندازه);
}

صحيح av_hwframe_get_transfer_بفر(AVBufferRef *hwframe_ctx, AVFrame *چوکاټ)
{
    أرجع ff_چوکاټ_get_video_بفر(چوکاټ, 0, transfer_بفر_alloc,
                                     hwframe_ctx->معلومات);
}

ساكن صحيح transfer_معلومات_alloc(AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVHWFramesContext *ctx;
    AVFrame *چوکاټ_tmp;
    صحيح ret = 0;

    إذا (!src->hw_چوکاټونه_ctx)
        أرجع AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_چوکاټونه_ctx->معلومات;

    چوکاټ_tmp = av_چوکاټ_alloc();
    إذا (!چوکاټ_tmp)
        أرجع AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    إذا (dst->format >= 0) {
        چوکاټ_tmp->format = dst->format;
    } وإلا {
        تعداد AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_چوکاټونه_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        إذا (ret < 0)
            اذهب fail;
        چوکاټ_tmp->format = formats[0];
        av_freep(&formats);
    }
    چوکاټ_tmp->پلنوالی  = ctx->پلنوالی;
    چوکاټ_tmp->لوړوالی = ctx->لوړوالی;

    ret = av_hwframe_get_transfer_بفر(src->hw_چوکاټونه_ctx, چوکاټ_tmp);
    إذا (ret < 0)
        اذهب fail;

    ret = av_hwframe_transfer_معلومات(چوکاټ_tmp, src, flags);
    إذا (ret < 0)
        اذهب fail;

    چوکاټ_tmp->پلنوالی  = src->پلنوالی;
    چوکاټ_tmp->لوړوالی = src->لوړوالی;

    av_چوکاټ_move_ref(dst, چوکاټ_tmp);

fail:
    av_چوکاټ_free(&چوکاټ_tmp);
    أرجع ret;
}

صحيح av_hwframe_transfer_معلومات(AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    صحيح ret;

    إذا (!dst->buf[0])
        أرجع transfer_معلومات_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    إذا (src->hw_چوکاټونه_ctx && dst->hw_چوکاټونه_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_چوکاټونه_ctx->معلومات;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_چوکاټونه_ctx->معلومات;

        إذا (src_ctx->سرچینه_چوکاټونه) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            أرجع AVERROR(ENOSYS);
        }

        إذا (dst_ctx->سرچینه_چوکاټونه) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            أرجع AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        إذا (src_ctx->hw_type->transfer_معلومات_from)
            ret = src_ctx->hw_type->transfer_معلومات_from(&src_ctx->p, dst, src);
        إذا (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_معلومات_منزل)
            ret = dst_ctx->hw_type->transfer_معلومات_منزل(&dst_ctx->p, dst, src);
        إذا (ret < 0)
            أرجع ret;
    } وإلا {
        إذا (src->hw_چوکاټونه_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_چوکاټونه_ctx->معلومات;

            إذا (!ctx->hw_type->transfer_معلومات_from)
                أرجع AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_معلومات_from(&ctx->p, dst, src);
            إذا (ret < 0)
                أرجع ret;
        } وإلا إذا (dst->hw_چوکاټونه_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_چوکاټونه_ctx->معلومات;

            إذا (!ctx->hw_type->transfer_معلومات_منزل)
                أرجع AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_معلومات_منزل(&ctx->p, dst, src);
            إذا (ret < 0)
                أرجع ret;
        } وإلا {
            أرجع AVERROR(ENOSYS);
        }
    }
    أرجع 0;
}

صحيح av_hwframe_get_بفر(AVBufferRef *hwframe_ref, AVFrame *چوکاټ, صحيح flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->معلومات;
    AVHWFramesContext *ctx  = &ctxi->p;
    صحيح ret;

    إذا (ctxi->سرچینه_چوکاټونه) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_چوکاټ;

        چوکاټ->format = ctx->format;
        چوکاټ->hw_چوکاټونه_ctx = av_بفر_ref(hwframe_ref);
        إذا (!چوکاټ->hw_چوکاټونه_ctx)
            أرجع AVERROR(ENOMEM);

        src_چوکاټ = av_چوکاټ_alloc();
        إذا (!src_چوکاټ)
            أرجع AVERROR(ENOMEM);

        ret = av_hwframe_get_بفر(ctxi->سرچینه_چوکاټونه,
                                    src_چوکاټ, 0);
        إذا (ret < 0) {
            av_چوکاټ_free(&src_چوکاټ);
            أرجع ret;
        }

        ret = av_hwframe_map(چوکاټ, src_چوکاټ,
                             ctxi->سرچینه_ویش_map_flags);
        إذا (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_چوکاټ_free(&src_چوکاټ);
            أرجع ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_چوکاټ_free(&src_چوکاټ);

        أرجع 0;
    }

    إذا (!ctxi->hw_type->چوکاټونه_get_بفر)
        أرجع AVERROR(ENOSYS);

    إذا (!ctx->pool)
        أرجع AVERROR(EINVAL);

    چوکاټ->hw_چوکاټونه_ctx = av_بفر_ref(hwframe_ref);
    إذا (!چوکاټ->hw_چوکاټونه_ctx)
        أرجع AVERROR(ENOMEM);

    ret = ctxi->hw_type->چوکاټونه_get_بفر(ctx, چوکاټ);
    إذا (ret < 0) {
        av_بفر_unref(&چوکاټ->hw_چوکاټونه_ctx);
        أرجع ret;
    }

    چوکاټ->extended_معلومات = چوکاټ->معلومات;

    أرجع 0;
}

فراغ *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->معلومات;
    ثابت HWContextType  *hw_type = ctx->hw_type;

    إذا (hw_type->device_hwconfig_اندازه == 0)
        أرجع عدم;

    أرجع av_mallocz(hw_type->device_hwconfig_اندازه);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ثابت فراغ *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->معلومات;
    ثابت HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    إذا (!hw_type->چوکاټونه_get_constraints)
        أرجع عدم;

    constraints = av_mallocz(حجم(*constraints));
    إذا (!constraints)
        أرجع عدم;

    constraints->min_پلنوالی = constraints->min_لوړوالی = 0;
    constraints->max_پلنوالی = constraints->max_لوړوالی = لوی_عدد;

    إذا (hw_type->چوکاټونه_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
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
    device_ctx = (FFHWDeviceContext*)device_ref->معلومات;

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
    av_بفر_unref(&device_ref);
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
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->معلومات;
        إذا (tmp_ctx->p.type == type) {
            dst_ref = av_بفر_ref(tmp_ref);
            إذا (!dst_ref) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
            اذهب بشپړ;
        }
        tmp_ref = tmp_ctx->سرچینه_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    إذا (!dst_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->معلومات;

    tmp_ref = src_ref;
    طالما (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->معلومات;
        إذا (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            إذا (ret == 0) {
                dst_ctx->سرچینه_device = av_بفر_ref(src_ref);
                إذا (!dst_ctx->سرچینه_device) {
                    ret = AVERROR(ENOMEM);
                    اذهب fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                إذا (ret < 0)
                    اذهب fail;
                اذهب بشپړ;
            }
            إذا (ret != AVERROR(ENOSYS))
                اذهب fail;
        }
        tmp_ref = tmp_ctx->سرچینه_device;
    }

    ret = AVERROR(ENOSYS);
    اذهب fail;

بشپړ:
    *dst_ref_ptr = dst_ref;
    أرجع 0;

fail:
    av_بفر_unref(&dst_ref);
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

ساكن فراغ ff_hwframe_unmap(فراغ *opaque, uint8_t *معلومات)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)معلومات;
    AVHWFramesContext *ctx = opaque;

    إذا (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_چوکاټ_free(&hwmap->سرچینه);

    av_بفر_unref(&hwmap->hw_چوکاټونه_ctx);

    av_free(hwmap);
}

صحيح ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ثابت AVFrame *src,
                          فراغ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          فراغ *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->معلومات;
    HWMapDescriptor *hwmap;
    صحيح ret;

    hwmap = av_mallocz(حجم(*hwmap));
    إذا (!hwmap) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    hwmap->سرچینه = av_چوکاټ_alloc();
    إذا (!hwmap->سرچینه) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    ret = av_چوکاټ_ref(hwmap->سرچینه, src);
    إذا (ret < 0)
        اذهب fail;

    hwmap->hw_چوکاټونه_ctx = av_بفر_ref(hwframe_ref);
    إذا (!hwmap->hw_چوکاټونه_ctx) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_بفر_create((uint8_t*)hwmap, حجم(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    إذا (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    أرجع 0;

fail:
    إذا (hwmap) {
        av_بفر_unref(&hwmap->hw_چوکاټونه_ctx);
        av_چوکاټ_free(&hwmap->سرچینه);
    }
    av_free(hwmap);
    أرجع ret;
}

صحيح av_hwframe_map(AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVBufferRef    *orig_dst_چوکاټونه = dst->hw_چوکاټونه_ctx;
    تعداد AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    صحيح ret;

    إذا (src->hw_چوکاټونه_ctx && dst->hw_چوکاټونه_ctx) {
        FFHWFramesContext *src_چوکاټونه = (FFHWFramesContext*)src->hw_چوکاټونه_ctx->معلومات;
        FFHWFramesContext *dst_چوکاټونه = (FFHWFramesContext*)dst->hw_چوکاټونه_ctx->معلومات;

        إذا ((src_چوکاټونه == dst_چوکاټونه &&
             src->format == dst_چوکاټونه->p.sw_format &&
             dst->format == dst_چوکاټونه->p.format) ||
            (src_چوکاټونه->سرچینه_چوکاټونه &&
             src_چوکاټونه->سرچینه_چوکاټونه->معلومات ==
             (uint8_t*)dst_چوکاټونه)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            إذا (!src->buf[0]) {
                av_log(src_چوکاټونه, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                أرجع AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->معلومات;
            أرجع av_چوکاټ_replace(dst, hwmap->سرچینه);
        }
    }

    إذا (src->hw_چوکاټونه_ctx) {
        FFHWFramesContext *src_چوکاټونه = (FFHWFramesContext*)src->hw_چوکاټونه_ctx->معلومات;

        إذا (src_چوکاټونه->p.format == src->format &&
            src_چوکاټونه->hw_type->map_from) {
            ret = src_چوکاټونه->hw_type->map_from(&src_چوکاټونه->p,
                                                dst, src, flags);
            إذا (ret >= 0)
                أرجع ret;
            وإلا إذا (ret != AVERROR(ENOSYS))
                اذهب fail;
        }
    }

    إذا (dst->hw_چوکاټونه_ctx) {
        FFHWFramesContext *dst_چوکاټونه = (FFHWFramesContext*)dst->hw_چوکاټونه_ctx->معلومات;

        إذا (dst_چوکاټونه->p.format == dst->format &&
            dst_چوکاټونه->hw_type->map_منزل) {
            ret = dst_چوکاټونه->hw_type->map_منزل(&dst_چوکاټونه->p,
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
    av_assert0(orig_dst_چوکاټونه == عدم ||
               orig_dst_چوکاټونه == dst->hw_چوکاټونه_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_چوکاټونه_ctx = عدم;
    av_چوکاټ_unref(dst);

    dst->hw_چوکاټونه_ctx = orig_dst_چوکاټونه;
    dst->format        = orig_dst_fmt;

    أرجع ret;
}

صحيح av_hwframe_ctx_create_derived(AVBufferRef **derived_چوکاټ_ctx,
                                  تعداد AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *سرچینه_چوکاټ_ctx,
                                  صحيح flags)
{
    AVBufferRef   *dst_ref = عدم;
    FFHWFramesContext *dsti = عدم;
    FFHWFramesContext *srci = (FFHWFramesContext*)سرچینه_چوکاټ_ctx->معلومات;
    AVHWFramesContext *dst, *src = &srci->p;
    صحيح ret;

    إذا (srci->سرچینه_چوکاټونه) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->سرچینه_چوکاټونه->معلومات;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->معلومات;

        إذا (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_چوکاټ_ctx = av_بفر_ref(srci->سرچینه_چوکاټونه);
            إذا (!*derived_چوکاټ_ctx) {
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

    dsti = (FFHWFramesContext*)dst_ref->معلومات;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->پلنوالی     = src->پلنوالی;
    dst->لوړوالی    = src->لوړوالی;

    dsti->سرچینه_چوکاټونه = av_بفر_ref(سرچینه_چوکاټ_ctx);
    إذا (!dsti->سرچینه_چوکاټونه) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    dsti->سرچینه_ویش_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_مستقیم);

    ret = AVERROR(ENOSYS);
    إذا (srci->hw_type->چوکاټونه_derive_from)
        ret = srci->hw_type->چوکاټونه_derive_from(dst, src, flags);
    إذا (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->چوکاټونه_derive_منزل)
        ret = dsti->hw_type->چوکاټونه_derive_منزل(dst, src, flags);
    إذا (ret == AVERROR(ENOSYS))
        ret = 0;
    إذا (ret)
        اذهب fail;

    *derived_چوکاټ_ctx = dst_ref;
    أرجع 0;

fail:
    إذا (dsti)
        av_بفر_unref(&dsti->سرچینه_چوکاټونه);
    av_بفر_unref(&dst_ref);
    أرجع ret;
}

صحيح ff_hwframe_map_replace(AVFrame *dst, ثابت AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->معلومات;
    أرجع av_چوکاټ_replace(hwmap->سرچینه, src);
}
