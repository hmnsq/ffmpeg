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
#جے_انت
#إذا CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#جے_انت
#إذا CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#جے_انت
#إذا CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#جے_انت
#إذا CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#جے_انت
#إذا CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#جے_انت
#إذا CONFIG_QSV
    &ff_hwcontext_type_qsv,
#جے_انت
#إذا CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#جے_انت
#إذا CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#جے_انت
#إذا CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#جے_انت
#إذا CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#جے_انت
#إذا CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#جے_انت
#إذا CONFIG_AMF
    &ff_hwcontext_type_amf,
#جے_انت
#إذا CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#جے_انت
    عدم,
};

ساكن ثابت حرف *ثابت hw_type_ناں[] = {
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
    AVBufferRef *سروت_device;
} FFHWDeviceContext;

تعداد AVHWDeviceType av_hwdevice_لبھو_type_by_name(ثابت حرف *name)
{
    صحيح type;
    لكل (type = 0; type < FF_ARRAY_ELEMS(hw_type_ناں); type++) {
        إذا (hw_type_ناں[type] && !strcmp(hw_type_ناں[type], name))
            أرجع type;
    }
    أرجع AV_HWDEVICE_TYPE_NONE;
}

ثابت حرف *av_hwdevice_get_type_name(تعداد AVHWDeviceType type)
{
    إذا (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_ناں))
        أرجع hw_type_ناں[type];
    وإلا
        أرجع عدم;
}

تعداد AVHWDeviceType av_hwdevice_iterate_types(تعداد AVHWDeviceType prev)
{
    تعداد AVHWDeviceType اگلا;
    صحيح i, سیٹ = 0;
    لكل (i = 0; hw_جدول[i]; i++) {
        إذا (prev != AV_HWDEVICE_TYPE_NONE && hw_جدول[i]->type <= prev)
            استمر;
        إذا (!سیٹ || hw_جدول[i]->type < اگلا) {
            اگلا = hw_جدول[i]->type;
            سیٹ = 1;
        }
    }
    أرجع سیٹ ? اگلا : AV_HWDEVICE_TYPE_NONE;
}

ساكن ثابت حرف *hwdevice_ctx_get_name(فراغ *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    أرجع ctx->hw_type->name;
}

ساكن ثابت AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .شے_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .نسخہ    = LIBAVUTIL_نسخہ_INT,
};

ساكن فراغ hwdevice_ctx_free(فراغ *opaque, uint8_t *انکڑے)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)انکڑے;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    إذا (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    إذا (ctx->حرر)
        ctx->حرر(ctx);

    av_بفر_unref(&ctxi->سروت_device);

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

    إذا (hw_type->device_hwctx_ناپ) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_ناپ);
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
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->انکڑے;
    AVHWDeviceContext *ctx  = &ctxi->p;
    صحيح ret = 0;

    إذا (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    أرجع ret;
}

ساكن ثابت AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .شے_name  = av_default_شے_name,
    .نسخہ    = LIBAVUTIL_نسخہ_INT,
};

ساكن فراغ hwframe_ctx_free(فراغ *opaque, uint8_t *انکڑے)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)انکڑے;
    AVHWFramesContext *ctx  = &ctxi->p;

    إذا (ctxi->pool_اندرونی)
        av_بفر_pool_uninit(&ctxi->pool_اندرونی);

    av_بفر_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_جندرا);

    إذا (ctxi->hw_type->چوکھٹے_uninit)
        ctxi->hw_type->چوکھٹے_uninit(ctx);

    إذا (ctx->حرر)
        ctx->حرر(ctx);

    av_بفر_unref(&ctxi->سروت_چوکھٹے);

    av_بفر_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_وچ)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_وچ->انکڑے;
    ثابت HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = عدم;

    ctxi = av_mallocz(حجم(*ctxi));
    إذا (!ctxi)
        أرجع عدم;
    ctx  = &ctxi->p;

    إذا (ff_mutex_init(&ctxi->transfer_pool_جندرا, عدم)) {
        av_free(ctxi);
        أرجع عدم;
    }

    إذا (hw_type->چوکھٹے_hwctx_ناپ) {
        ctx->hwctx = av_mallocz(hw_type->چوکھٹے_hwctx_ناپ);
        إذا (!ctx->hwctx)
            اذهب fail;
    }

    device_ref = av_بفر_ref(device_ref_وچ);
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
    ff_mutex_destroy(&ctxi->transfer_pool_جندرا);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    أرجع عدم;
}

ساكن صحيح hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->انکڑے;
    AVFrame **چوکھٹے;
    صحيح i, ret = 0;

    چوکھٹے = av_calloc(ctx->initial_pool_ناپ, حجم(*چوکھٹے));
    إذا (!چوکھٹے)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < ctx->initial_pool_ناپ; i++) {
        چوکھٹے[i] = av_چوکھٹا_alloc();
        إذا (!چوکھٹے[i])
            اذهب fail;

        ret = av_hwframe_get_بفر(ref, چوکھٹے[i], 0);
        إذا (ret < 0)
            اذهب fail;
    }

fail:
    لكل (i = 0; i < ctx->initial_pool_ناپ; i++)
        av_چوکھٹا_free(&چوکھٹے[i]);
    av_freep(&چوکھٹے);

    أرجع ret;
}

صحيح av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->انکڑے;
    AVHWFramesContext *ctx  = &ctxi->p;
    ثابت تعداد AVPixelFormat *pix_fmt;
    صحيح ret;

    إذا (ctxi->سروت_چوکھٹے) {
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
    ret = av_image_check_ناپ(ctx->چوڑائی, ctx->اچائی, 0, ctx);
    إذا (ret < 0)
        أرجع ret;

    /* format-specific init */
    إذا (ctxi->hw_type->چوکھٹے_init) {
        ret = ctxi->hw_type->چوکھٹے_init(ctx);
        إذا (ret < 0)
            أرجع ret;
    }

    إذا (ctxi->pool_اندرونی && !ctx->pool)
        ctx->pool = ctxi->pool_اندرونی;

    /* preallocate the frames in the pool, if requested */
    إذا (ctx->initial_pool_ناپ > 0) {
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
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->انکڑے;

    إذا (!ctxi->hw_type->transfer_get_formats)
        أرجع AVERROR(ENOSYS);

    أرجع ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

ساكن فراغ transfer_pool_free(فراغ *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_بفر_unref(&device_ref);
}

ساكن AVBufferRef *transfer_بفر_alloc(فراغ *opaque, size_t ناپ)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = عدم;

    ff_mutex_جندرا(&ctxi->transfer_pool_جندرا);
    إذا (ctxi->transfer_pool_ناپ != ناپ) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_بفر_alloc ?
                                  av_بفر_ref(ctxi->p.device_ref) : عدم;

        av_بفر_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_بفر_pool_init2(ناپ, device_ref,
                                 ctxi->hw_type->transfer_بفر_alloc,
                                 transfer_pool_free) :
            av_بفر_pool_init(ناپ, عدم);
        ctxi->transfer_pool_ناپ = ctxi->transfer_pool ? ناپ : 0;
        إذا (!ctxi->transfer_pool)
            av_بفر_unref(&device_ref);
    }
    إذا (ctxi->transfer_pool)
        buf = av_بفر_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_جندرا);

    أرجع buf ? buf : av_بفر_alloc(ناپ);
}

صحيح av_hwframe_get_transfer_بفر(AVBufferRef *hwframe_ctx, AVFrame *چوکھٹا)
{
    أرجع ff_چوکھٹا_get_video_بفر(چوکھٹا, 0, transfer_بفر_alloc,
                                     hwframe_ctx->انکڑے);
}

ساكن صحيح transfer_انکڑے_alloc(AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVHWFramesContext *ctx;
    AVFrame *چوکھٹا_tmp;
    صحيح ret = 0;

    إذا (!src->hw_چوکھٹے_ctx)
        أرجع AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_چوکھٹے_ctx->انکڑے;

    چوکھٹا_tmp = av_چوکھٹا_alloc();
    إذا (!چوکھٹا_tmp)
        أرجع AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    إذا (dst->format >= 0) {
        چوکھٹا_tmp->format = dst->format;
    } وإلا {
        تعداد AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_چوکھٹے_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        إذا (ret < 0)
            اذهب fail;
        چوکھٹا_tmp->format = formats[0];
        av_freep(&formats);
    }
    چوکھٹا_tmp->چوڑائی  = ctx->چوڑائی;
    چوکھٹا_tmp->اچائی = ctx->اچائی;

    ret = av_hwframe_get_transfer_بفر(src->hw_چوکھٹے_ctx, چوکھٹا_tmp);
    إذا (ret < 0)
        اذهب fail;

    ret = av_hwframe_transfer_انکڑے(چوکھٹا_tmp, src, flags);
    إذا (ret < 0)
        اذهب fail;

    چوکھٹا_tmp->چوڑائی  = src->چوڑائی;
    چوکھٹا_tmp->اچائی = src->اچائی;

    av_چوکھٹا_move_ref(dst, چوکھٹا_tmp);

fail:
    av_چوکھٹا_free(&چوکھٹا_tmp);
    أرجع ret;
}

صحيح av_hwframe_transfer_انکڑے(AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    صحيح ret;

    إذا (!dst->buf[0])
        أرجع transfer_انکڑے_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    إذا (src->hw_چوکھٹے_ctx && dst->hw_چوکھٹے_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_چوکھٹے_ctx->انکڑے;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_چوکھٹے_ctx->انکڑے;

        إذا (src_ctx->سروت_چوکھٹے) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            أرجع AVERROR(ENOSYS);
        }

        إذا (dst_ctx->سروت_چوکھٹے) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            أرجع AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        إذا (src_ctx->hw_type->transfer_انکڑے_from)
            ret = src_ctx->hw_type->transfer_انکڑے_from(&src_ctx->p, dst, src);
        إذا (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_انکڑے_منزل)
            ret = dst_ctx->hw_type->transfer_انکڑے_منزل(&dst_ctx->p, dst, src);
        إذا (ret < 0)
            أرجع ret;
    } وإلا {
        إذا (src->hw_چوکھٹے_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_چوکھٹے_ctx->انکڑے;

            إذا (!ctx->hw_type->transfer_انکڑے_from)
                أرجع AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_انکڑے_from(&ctx->p, dst, src);
            إذا (ret < 0)
                أرجع ret;
        } وإلا إذا (dst->hw_چوکھٹے_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_چوکھٹے_ctx->انکڑے;

            إذا (!ctx->hw_type->transfer_انکڑے_منزل)
                أرجع AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_انکڑے_منزل(&ctx->p, dst, src);
            إذا (ret < 0)
                أرجع ret;
        } وإلا {
            أرجع AVERROR(ENOSYS);
        }
    }
    أرجع 0;
}

صحيح av_hwframe_get_بفر(AVBufferRef *hwframe_ref, AVFrame *چوکھٹا, صحيح flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->انکڑے;
    AVHWFramesContext *ctx  = &ctxi->p;
    صحيح ret;

    إذا (ctxi->سروت_چوکھٹے) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_چوکھٹا;

        چوکھٹا->format = ctx->format;
        چوکھٹا->hw_چوکھٹے_ctx = av_بفر_ref(hwframe_ref);
        إذا (!چوکھٹا->hw_چوکھٹے_ctx)
            أرجع AVERROR(ENOMEM);

        src_چوکھٹا = av_چوکھٹا_alloc();
        إذا (!src_چوکھٹا)
            أرجع AVERROR(ENOMEM);

        ret = av_hwframe_get_بفر(ctxi->سروت_چوکھٹے,
                                    src_چوکھٹا, 0);
        إذا (ret < 0) {
            av_چوکھٹا_free(&src_چوکھٹا);
            أرجع ret;
        }

        ret = av_hwframe_map(چوکھٹا, src_چوکھٹا,
                             ctxi->سروت_ونڈ_map_flags);
        إذا (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_چوکھٹا_free(&src_چوکھٹا);
            أرجع ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_چوکھٹا_free(&src_چوکھٹا);

        أرجع 0;
    }

    إذا (!ctxi->hw_type->چوکھٹے_get_بفر)
        أرجع AVERROR(ENOSYS);

    إذا (!ctx->pool)
        أرجع AVERROR(EINVAL);

    چوکھٹا->hw_چوکھٹے_ctx = av_بفر_ref(hwframe_ref);
    إذا (!چوکھٹا->hw_چوکھٹے_ctx)
        أرجع AVERROR(ENOMEM);

    ret = ctxi->hw_type->چوکھٹے_get_بفر(ctx, چوکھٹا);
    إذا (ret < 0) {
        av_بفر_unref(&چوکھٹا->hw_چوکھٹے_ctx);
        أرجع ret;
    }

    چوکھٹا->extended_انکڑے = چوکھٹا->انکڑے;

    أرجع 0;
}

فراغ *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->انکڑے;
    ثابت HWContextType  *hw_type = ctx->hw_type;

    إذا (hw_type->device_hwconfig_ناپ == 0)
        أرجع عدم;

    أرجع av_mallocz(hw_type->device_hwconfig_ناپ);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ثابت فراغ *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->انکڑے;
    ثابت HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    إذا (!hw_type->چوکھٹے_get_constraints)
        أرجع عدم;

    constraints = av_mallocz(حجم(*constraints));
    إذا (!constraints)
        أرجع عدم;

    constraints->min_چوڑائی = constraints->min_اچائی = 0;
    constraints->max_چوڑائی = constraints->max_اچائی = ودھ_توں_ودھ_عدد;

    إذا (hw_type->چوکھٹے_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
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
    device_ctx = (FFHWDeviceContext*)device_ref->انکڑے;

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
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->انکڑے;
        إذا (tmp_ctx->p.type == type) {
            dst_ref = av_بفر_ref(tmp_ref);
            إذا (!dst_ref) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
            اذهب پورا;
        }
        tmp_ref = tmp_ctx->سروت_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    إذا (!dst_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->انکڑے;

    tmp_ref = src_ref;
    طالما (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->انکڑے;
        إذا (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            إذا (ret == 0) {
                dst_ctx->سروت_device = av_بفر_ref(src_ref);
                إذا (!dst_ctx->سروت_device) {
                    ret = AVERROR(ENOMEM);
                    اذهب fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                إذا (ret < 0)
                    اذهب fail;
                اذهب پورا;
            }
            إذا (ret != AVERROR(ENOSYS))
                اذهب fail;
        }
        tmp_ref = tmp_ctx->سروت_device;
    }

    ret = AVERROR(ENOSYS);
    اذهب fail;

پورا:
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

ساكن فراغ ff_hwframe_unmap(فراغ *opaque, uint8_t *انکڑے)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)انکڑے;
    AVHWFramesContext *ctx = opaque;

    إذا (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_چوکھٹا_free(&hwmap->سروت);

    av_بفر_unref(&hwmap->hw_چوکھٹے_ctx);

    av_free(hwmap);
}

صحيح ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ثابت AVFrame *src,
                          فراغ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          فراغ *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->انکڑے;
    HWMapDescriptor *hwmap;
    صحيح ret;

    hwmap = av_mallocz(حجم(*hwmap));
    إذا (!hwmap) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    hwmap->سروت = av_چوکھٹا_alloc();
    إذا (!hwmap->سروت) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    ret = av_چوکھٹا_ref(hwmap->سروت, src);
    إذا (ret < 0)
        اذهب fail;

    hwmap->hw_چوکھٹے_ctx = av_بفر_ref(hwframe_ref);
    إذا (!hwmap->hw_چوکھٹے_ctx) {
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
        av_بفر_unref(&hwmap->hw_چوکھٹے_ctx);
        av_چوکھٹا_free(&hwmap->سروت);
    }
    av_free(hwmap);
    أرجع ret;
}

صحيح av_hwframe_map(AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVBufferRef    *orig_dst_چوکھٹے = dst->hw_چوکھٹے_ctx;
    تعداد AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    صحيح ret;

    إذا (src->hw_چوکھٹے_ctx && dst->hw_چوکھٹے_ctx) {
        FFHWFramesContext *src_چوکھٹے = (FFHWFramesContext*)src->hw_چوکھٹے_ctx->انکڑے;
        FFHWFramesContext *dst_چوکھٹے = (FFHWFramesContext*)dst->hw_چوکھٹے_ctx->انکڑے;

        إذا ((src_چوکھٹے == dst_چوکھٹے &&
             src->format == dst_چوکھٹے->p.sw_format &&
             dst->format == dst_چوکھٹے->p.format) ||
            (src_چوکھٹے->سروت_چوکھٹے &&
             src_چوکھٹے->سروت_چوکھٹے->انکڑے ==
             (uint8_t*)dst_چوکھٹے)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            إذا (!src->buf[0]) {
                av_log(src_چوکھٹے, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                أرجع AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->انکڑے;
            أرجع av_چوکھٹا_replace(dst, hwmap->سروت);
        }
    }

    إذا (src->hw_چوکھٹے_ctx) {
        FFHWFramesContext *src_چوکھٹے = (FFHWFramesContext*)src->hw_چوکھٹے_ctx->انکڑے;

        إذا (src_چوکھٹے->p.format == src->format &&
            src_چوکھٹے->hw_type->map_from) {
            ret = src_چوکھٹے->hw_type->map_from(&src_چوکھٹے->p,
                                                dst, src, flags);
            إذا (ret >= 0)
                أرجع ret;
            وإلا إذا (ret != AVERROR(ENOSYS))
                اذهب fail;
        }
    }

    إذا (dst->hw_چوکھٹے_ctx) {
        FFHWFramesContext *dst_چوکھٹے = (FFHWFramesContext*)dst->hw_چوکھٹے_ctx->انکڑے;

        إذا (dst_چوکھٹے->p.format == dst->format &&
            dst_چوکھٹے->hw_type->map_منزل) {
            ret = dst_چوکھٹے->hw_type->map_منزل(&dst_چوکھٹے->p,
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
    av_assert0(orig_dst_چوکھٹے == عدم ||
               orig_dst_چوکھٹے == dst->hw_چوکھٹے_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_چوکھٹے_ctx = عدم;
    av_چوکھٹا_unref(dst);

    dst->hw_چوکھٹے_ctx = orig_dst_چوکھٹے;
    dst->format        = orig_dst_fmt;

    أرجع ret;
}

صحيح av_hwframe_ctx_create_derived(AVBufferRef **derived_چوکھٹا_ctx,
                                  تعداد AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *سروت_چوکھٹا_ctx,
                                  صحيح flags)
{
    AVBufferRef   *dst_ref = عدم;
    FFHWFramesContext *dsti = عدم;
    FFHWFramesContext *srci = (FFHWFramesContext*)سروت_چوکھٹا_ctx->انکڑے;
    AVHWFramesContext *dst, *src = &srci->p;
    صحيح ret;

    إذا (srci->سروت_چوکھٹے) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->سروت_چوکھٹے->انکڑے;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->انکڑے;

        إذا (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_چوکھٹا_ctx = av_بفر_ref(srci->سروت_چوکھٹے);
            إذا (!*derived_چوکھٹا_ctx) {
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

    dsti = (FFHWFramesContext*)dst_ref->انکڑے;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->چوڑائی     = src->چوڑائی;
    dst->اچائی    = src->اچائی;

    dsti->سروت_چوکھٹے = av_بفر_ref(سروت_چوکھٹا_ctx);
    إذا (!dsti->سروت_چوکھٹے) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    dsti->سروت_ونڈ_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_سدھا);

    ret = AVERROR(ENOSYS);
    إذا (srci->hw_type->چوکھٹے_derive_from)
        ret = srci->hw_type->چوکھٹے_derive_from(dst, src, flags);
    إذا (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->چوکھٹے_derive_منزل)
        ret = dsti->hw_type->چوکھٹے_derive_منزل(dst, src, flags);
    إذا (ret == AVERROR(ENOSYS))
        ret = 0;
    إذا (ret)
        اذهب fail;

    *derived_چوکھٹا_ctx = dst_ref;
    أرجع 0;

fail:
    إذا (dsti)
        av_بفر_unref(&dsti->سروت_چوکھٹے);
    av_بفر_unref(&dst_ref);
    أرجع ret;
}

صحيح ff_hwframe_map_replace(AVFrame *dst, ثابت AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->انکڑے;
    أرجع av_چوکھٹا_replace(hwmap->سروت, src);
}
