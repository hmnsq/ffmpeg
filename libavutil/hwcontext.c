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

ಸ್ಥಿರ ಧ್ರುವ HWContextType * ಧ್ರುವ hw_table[] = {
#ಯದಿ CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#endif
#ಯದಿ CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#endif
#ಯದಿ CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#endif
#ಯದಿ CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#endif
#ಯದಿ CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#endif
#ಯದಿ CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#endif
#ಯದಿ CONFIG_QSV
    &ff_hwcontext_type_qsv,
#endif
#ಯದಿ CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#endif
#ಯದಿ CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#endif
#ಯದಿ CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#endif
#ಯದಿ CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#endif
#ಯದಿ CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#endif
#ಯದಿ CONFIG_AMF
    &ff_hwcontext_type_amf,
#endif
#ಯದಿ CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#endif
    ರಿಕ್ತ,
};

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ hw_type_names[] = {
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

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    ಧ್ರುವ HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *source_device;
} FFHWDeviceContext;

ಗಣನಾ AVHWDeviceType av_hwdevice_find_type_by_name(ಧ್ರುವ ವರ್ಣ *name)
{
    ಪೂರ್ಣಾಙ್ಕ type;
    ಪ್ರತಿ (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        ಯದಿ (hw_type_names[type] && !strcmp(hw_type_names[type], name))
            ಪ್ರತ್ಯಾಗಮ type;
    }
    ಪ್ರತ್ಯಾಗಮ AV_HWDEVICE_TYPE_NONE;
}

ಧ್ರುವ ವರ್ಣ *av_hwdevice_get_type_name(ಗಣನಾ AVHWDeviceType type)
{
    ಯದಿ (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        ಪ್ರತ್ಯಾಗಮ hw_type_names[type];
    ಅನ್ಯಥಾ
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಗಣನಾ AVHWDeviceType av_hwdevice_iterate_types(ಗಣನಾ AVHWDeviceType prev)
{
    ಗಣನಾ AVHWDeviceType next;
    ಪೂರ್ಣಾಙ್ಕ i, set = 0;
    ಪ್ರತಿ (i = 0; hw_table[i]; i++) {
        ಯದಿ (prev != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= prev)
            ಅನುವರ್ತ;
        ಯದಿ (!set || hw_table[i]->type < next) {
            next = hw_table[i]->type;
            set = 1;
        }
    }
    ಪ್ರತ್ಯಾಗಮ set ? next : AV_HWDEVICE_TYPE_NONE;
}

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ *hwdevice_ctx_get_name(ಶೂನ್ಯ *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    ಪ್ರತ್ಯಾಗಮ ctx->hw_type->name;
}

ಸ್ಥಿರ ಧ್ರುವ AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .item_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .version    = LIBAVUTIL_VERSION_INT,
};

ಸ್ಥಿರ ಶೂನ್ಯ hwdevice_ctx_free(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)data;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    ಯದಿ (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    ಯದಿ (ctx->ಮುಕ್ತ)
        ctx->ಮುಕ್ತ(ctx);

    av_buffer_unref(&ctxi->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(ಗಣನಾ AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    ಧ್ರುವ HWContextType *hw_type = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ (i = 0; hw_table[i]; i++) {
        ಯದಿ (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            ಭಙ್ಗ;
        }
    }
    ಯದಿ (!hw_type)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ctxi = av_mallocz(ಪರಿಮಾಣ(*ctxi));
    ಯದಿ (!ctxi)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ctx = &ctxi->p;

    ಯದಿ (hw_type->device_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_size);
        ಯದಿ (!ctx->hwctx)
            ಗಚ್ಛ fail;
    }

    buf = av_buffer_create((uint8_t*)ctx, ಪರಿಮಾಣ(*ctx),
                           hwdevice_ctx_free, ರಿಕ್ತ,
                           AV_BUFFER_FLAG_READONLY);
    ಯದಿ (!buf)
        ಗಚ್ಛ fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    ಪ್ರತ್ಯಾಗಮ buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಪೂರ್ಣಾಙ್ಕ av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->data;
    AVHWDeviceContext *ctx  = &ctxi->p;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    ಯದಿ (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಧ್ರುವ AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .item_name  = av_default_item_name,
    .version    = LIBAVUTIL_VERSION_INT,
};

ಸ್ಥಿರ ಶೂನ್ಯ hwframe_ctx_free(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)data;
    AVHWFramesContext *ctx  = &ctxi->p;

    ಯದಿ (ctxi->pool_internal)
        av_buffer_pool_uninit(&ctxi->pool_internal);

    av_buffer_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    ಯದಿ (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    ಯದಿ (ctx->ಮುಕ್ತ)
        ctx->ಮುಕ್ತ(ctx);

    av_buffer_unref(&ctxi->source_frames);

    av_buffer_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_in)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_in->data;
    ಧ್ರುವ HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = ರಿಕ್ತ;

    ctxi = av_mallocz(ಪರಿಮಾಣ(*ctxi));
    ಯದಿ (!ctxi)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ctx  = &ctxi->p;

    ಯದಿ (ff_mutex_init(&ctxi->transfer_pool_lock, ರಿಕ್ತ)) {
        av_free(ctxi);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (hw_type->frames_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_size);
        ಯದಿ (!ctx->hwctx)
            ಗಚ್ಛ fail;
    }

    device_ref = av_buffer_ref(device_ref_in);
    ಯದಿ (!device_ref)
        ಗಚ್ಛ fail;

    buf = av_buffer_create((uint8_t*)ctx, ಪರಿಮಾಣ(*ctx),
                           hwframe_ctx_free, ರಿಕ್ತ,
                           AV_BUFFER_FLAG_READONLY);
    ಯದಿ (!buf)
        ಗಚ್ಛ fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    ಪ್ರತ್ಯಾಗಮ buf;

fail:
    av_buffer_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->data;
    AVFrame **frames;
    ಪೂರ್ಣಾಙ್ಕ i, ret = 0;

    frames = av_calloc(ctx->initial_pool_size, ಪರಿಮಾಣ(*frames));
    ಯದಿ (!frames)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (i = 0; i < ctx->initial_pool_size; i++) {
        frames[i] = av_frame_alloc();
        ಯದಿ (!frames[i])
            ಗಚ್ಛ fail;

        ret = av_hwframe_get_buffer(ref, frames[i], 0);
        ಯದಿ (ret < 0)
            ಗಚ್ಛ fail;
    }

fail:
    ಪ್ರತಿ (i = 0; i < ctx->initial_pool_size; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    ಧ್ರುವ ಗಣನಾ AVPixelFormat *pix_fmt;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    /* validate the pixel format */
    ಪ್ರತಿ (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        ಯದಿ (*pix_fmt == ctx->format)
            ಭಙ್ಗ;
    }
    ಯದಿ (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_size(ctx->width, ctx->height, 0, ctx);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    /* format-specific init */
    ಯದಿ (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
    }

    ಯದಿ (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    ಯದಿ (ctx->initial_pool_size > 0) {
        ret = hwframe_pool_prealloc(ref);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    ಗಣನಾ AVHWFrameTransferDirection dir,
                                    ಗಣನಾ AVPixelFormat **formats, ಪೂರ್ಣಾಙ್ಕ flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;

    ಯದಿ (!ctxi->hw_type->transfer_get_formats)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);

    ಪ್ರತ್ಯಾಗಮ ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

ಸ್ಥಿರ ಶೂನ್ಯ transfer_pool_free(ಶೂನ್ಯ *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_buffer_unref(&device_ref);
}

ಸ್ಥಿರ AVBufferRef *transfer_buffer_alloc(ಶೂನ್ಯ *opaque, size_t size)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = ರಿಕ್ತ;

    ff_mutex_lock(&ctxi->transfer_pool_lock);
    ಯದಿ (ctxi->transfer_pool_size != size) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_buffer_alloc ?
                                  av_buffer_ref(ctxi->p.device_ref) : ರಿಕ್ತ;

        av_buffer_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_buffer_pool_init2(size, device_ref,
                                 ctxi->hw_type->transfer_buffer_alloc,
                                 transfer_pool_free) :
            av_buffer_pool_init(size, ರಿಕ್ತ);
        ctxi->transfer_pool_size = ctxi->transfer_pool ? size : 0;
        ಯದಿ (!ctxi->transfer_pool)
            av_buffer_unref(&device_ref);
    }
    ಯದಿ (ctxi->transfer_pool)
        buf = av_buffer_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    ಪ್ರತ್ಯಾಗಮ buf ? buf : av_buffer_alloc(size);
}

ಪೂರ್ಣಾಙ್ಕ av_hwframe_get_transfer_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    ಪ್ರತ್ಯಾಗಮ ff_frame_get_video_buffer(frame, 0, transfer_buffer_alloc,
                                     hwframe_ctx->data);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ transfer_data_alloc(AVFrame *dst, ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    ಯದಿ (!src->hw_frames_ctx)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;

    frame_tmp = av_frame_alloc();
    ಯದಿ (!frame_tmp)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    ಯದಿ (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } ಅನ್ಯಥಾ {
        ಗಣನಾ AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        ಯದಿ (ret < 0)
            ಗಚ್ಛ fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_buffer(src->hw_frames_ctx, frame_tmp);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    ret = av_hwframe_transfer_data(frame_tmp, src, flags);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_hwframe_transfer_data(AVFrame *dst, ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!dst->buf[0])
        ಪ್ರತ್ಯಾಗಮ transfer_data_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    ಯದಿ (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->data;

        ಯದಿ (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        }

        ಯದಿ (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        ಯದಿ (src_ctx->hw_type->transfer_data_from)
            ret = src_ctx->hw_type->transfer_data_from(&src_ctx->p, dst, src);
        ಯದಿ (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_data_to)
            ret = dst_ctx->hw_type->transfer_data_to(&dst_ctx->p, dst, src);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
    } ಅನ್ಯಥಾ {
        ಯದಿ (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->data;

            ಯದಿ (!ctx->hw_type->transfer_data_from)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_from(&ctx->p, dst, src);
            ಯದಿ (ret < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
        } ಅನ್ಯಥಾ ಯದಿ (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->data;

            ಯದಿ (!ctx->hw_type->transfer_data_to)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_to(&ctx->p, dst, src);
            ಯದಿ (ret < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
        } ಅನ್ಯಥಾ {
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        }
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_hwframe_get_buffer(AVBufferRef *hwframe_ref, AVFrame *frame, ಪೂರ್ಣಾಙ್ಕ flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
        ಯದಿ (!frame->hw_frames_ctx)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        ಯದಿ (!src_frame)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        ret = av_hwframe_get_buffer(ctxi->source_frames,
                                    src_frame, 0);
        ಯದಿ (ret < 0) {
            av_frame_free(&src_frame);
            ಪ್ರತ್ಯಾಗಮ ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        ಯದಿ (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            ಪ್ರತ್ಯಾಗಮ ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಯದಿ (!ctxi->hw_type->frames_get_buffer)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);

    ಯದಿ (!ctx->pool)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    ಯದಿ (!frame->hw_frames_ctx)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_buffer(ctx, frame);
    ಯದಿ (ret < 0) {
        av_buffer_unref(&frame->hw_frames_ctx);
        ಪ್ರತ್ಯಾಗಮ ret;
    }

    frame->extended_data = frame->data;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    ಧ್ರುವ HWContextType  *hw_type = ctx->hw_type;

    ಯದಿ (hw_type->device_hwconfig_size == 0)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಪ್ರತ್ಯಾಗಮ av_mallocz(hw_type->device_hwconfig_size);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ಧ್ರುವ ಶೂನ್ಯ *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    ಧ್ರುವ HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    ಯದಿ (!hw_type->frames_get_constraints)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    constraints = av_mallocz(ಪರಿಮಾಣ(*constraints));
    ಯದಿ (!constraints)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = INT_MAX;

    ಯದಿ (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        ಪ್ರತ್ಯಾಗಮ constraints;
    } ಅನ್ಯಥಾ {
        av_hwframe_constraints_free(&constraints);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
}

ಶೂನ್ಯ av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    ಯದಿ (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

ಪೂರ್ಣಾಙ್ಕ av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, ಗಣನಾ AVHWDeviceType type,
                           ಧ್ರುವ ವರ್ಣ *device, AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVBufferRef *device_ref = ರಿಕ್ತ;
    FFHWDeviceContext *device_ctx;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    ಯದಿ (!device_ref) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->data;

    ಯದಿ (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        ಗಚ್ಛ fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    ret = av_hwdevice_ctx_init(device_ref);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    *pdevice_ref = device_ref;
    ಪ್ರತ್ಯಾಗಮ 0;
fail:
    av_buffer_unref(&device_ref);
    *pdevice_ref = ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        ಗಣನಾ AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVBufferRef *dst_ref = ರಿಕ್ತ, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    tmp_ref = src_ref;
    ಯಾವತ್ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        ಯದಿ (tmp_ctx->p.type == type) {
            dst_ref = av_buffer_ref(tmp_ref);
            ಯದಿ (!dst_ref) {
                ret = AVERROR(ENOMEM);
                ಗಚ್ಛ fail;
            }
            ಗಚ್ಛ done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    ಯದಿ (!dst_ref) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->data;

    tmp_ref = src_ref;
    ಯಾವತ್ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        ಯದಿ (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            ಯದಿ (ret == 0) {
                dst_ctx->source_device = av_buffer_ref(src_ref);
                ಯದಿ (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    ಗಚ್ಛ fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                ಯದಿ (ret < 0)
                    ಗಚ್ಛ fail;
                ಗಚ್ಛ done;
            }
            ಯದಿ (ret != AVERROR(ENOSYS))
                ಗಚ್ಛ fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    ಗಚ್ಛ fail;

done:
    *dst_ref_ptr = dst_ref;
    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    av_buffer_unref(&dst_ref);
    *dst_ref_ptr = ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   ಗಣನಾ AVHWDeviceType type,
                                   AVBufferRef *src_ref, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಪ್ರತ್ಯಾಗಮ av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               ರಿಕ್ತ, flags);
}

ಸ್ಥಿರ ಶೂನ್ಯ ff_hwframe_unmap(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)data;
    AVHWFramesContext *ctx = opaque;

    ಯದಿ (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_buffer_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

ಪೂರ್ಣಾಙ್ಕ ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ಧ್ರುವ AVFrame *src,
                          ಶೂನ್ಯ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          ಶೂನ್ಯ *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->data;
    HWMapDescriptor *hwmap;
    ಪೂರ್ಣಾಙ್ಕ ret;

    hwmap = av_mallocz(ಪರಿಮಾಣ(*hwmap));
    ಯದಿ (!hwmap) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    hwmap->source = av_frame_alloc();
    ಯದಿ (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    hwmap->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    ಯದಿ (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_buffer_create((uint8_t*)hwmap, ಪರಿಮಾಣ(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    ಯದಿ (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಯದಿ (hwmap) {
        av_buffer_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_hwframe_map(AVFrame *dst, ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    ಗಣನಾ AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        ಯದಿ ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->data ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            ಯದಿ (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->data;
            ಪ್ರತ್ಯಾಗಮ av_frame_replace(dst, hwmap->source);
        }
    }

    ಯದಿ (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;

        ಯದಿ (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            ಯದಿ (ret >= 0)
                ಪ್ರತ್ಯಾಗಮ ret;
            ಅನ್ಯಥಾ ಯದಿ (ret != AVERROR(ENOSYS))
                ಗಚ್ಛ fail;
        }
    }

    ಯದಿ (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        ಯದಿ (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            ಯದಿ (ret >= 0)
                ಪ್ರತ್ಯಾಗಮ ret;
            ಅನ್ಯಥಾ ಯದಿ (ret != AVERROR(ENOSYS))
                ಗಚ್ಛ fail;
        }
    }

    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_frames == ರಿಕ್ತ ||
               orig_dst_frames == dst->hw_frames_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_frames_ctx = ರಿಕ್ತ;
    av_frame_unref(dst);

    dst->hw_frames_ctx = orig_dst_frames;
    dst->format        = orig_dst_fmt;

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  ಗಣನಾ AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVBufferRef   *dst_ref = ರಿಕ್ತ;
    FFHWFramesContext *dsti = ರಿಕ್ತ;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->data;
    AVHWFramesContext *dst, *src = &srci->p;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->data;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->data;

        ಯದಿ (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_buffer_ref(srci->source_frames);
            ಯದಿ (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                ಗಚ್ಛ fail;
            }
            ಪ್ರತ್ಯಾಗಮ 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    ಯದಿ (!dst_ref) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->data;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->width     = src->width;
    dst->height    = src->height;

    dsti->source_frames = av_buffer_ref(source_frame_ctx);
    ಯದಿ (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    dsti->source_allocation_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_DIRECT);

    ret = AVERROR(ENOSYS);
    ಯದಿ (srci->hw_type->frames_derive_from)
        ret = srci->hw_type->frames_derive_from(dst, src, flags);
    ಯದಿ (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->frames_derive_to)
        ret = dsti->hw_type->frames_derive_to(dst, src, flags);
    ಯದಿ (ret == AVERROR(ENOSYS))
        ret = 0;
    ಯದಿ (ret)
        ಗಚ್ಛ fail;

    *derived_frame_ctx = dst_ref;
    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಯದಿ (dsti)
        av_buffer_unref(&dsti->source_frames);
    av_buffer_unref(&dst_ref);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪೂರ್ಣಾಙ್ಕ ff_hwframe_map_replace(AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->data;
    ಪ್ರತ್ಯಾಗಮ av_frame_replace(hwmap->source, src);
}
