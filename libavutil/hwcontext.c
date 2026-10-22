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

ساكن ثابت HWContextType * ثابت hw_table[] = {
#ܐܢ CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#endif
#ܐܢ CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#endif
#ܐܢ CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#endif
#ܐܢ CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#endif
#ܐܢ CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#endif
#ܐܢ CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#endif
#ܐܢ CONFIG_QSV
    &ff_hwcontext_type_qsv,
#endif
#ܐܢ CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#endif
#ܐܢ CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#endif
#ܐܢ CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#endif
#ܐܢ CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#endif
#ܐܢ CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#endif
#ܐܢ CONFIG_AMF
    &ff_hwcontext_type_amf,
#endif
#ܐܢ CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#endif
    عدم,
};

ساكن ثابت حرف *ثابت hw_type_names[] = {
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
    AVBufferRef *source_device;
} FFHWDeviceContext;

تعداد AVHWDeviceType av_hwdevice_find_type_by_name(ثابت حرف *name)
{
    صحيح type;
    لكل (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        ܐܢ (hw_type_names[type] && !strcmp(hw_type_names[type], name))
            ܦܢܐ type;
    }
    ܦܢܐ AV_HWDEVICE_TYPE_NONE;
}

ثابت حرف *av_hwdevice_get_type_name(تعداد AVHWDeviceType type)
{
    ܐܢ (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        ܦܢܐ hw_type_names[type];
    ܐܚܪܢܐ
        ܦܢܐ عدم;
}

تعداد AVHWDeviceType av_hwdevice_iterate_types(تعداد AVHWDeviceType prev)
{
    تعداد AVHWDeviceType next;
    صحيح i, set = 0;
    لكل (i = 0; hw_table[i]; i++) {
        ܐܢ (prev != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= prev)
            استمر;
        ܐܢ (!set || hw_table[i]->type < next) {
            next = hw_table[i]->type;
            set = 1;
        }
    }
    ܦܢܐ set ? next : AV_HWDEVICE_TYPE_NONE;
}

ساكن ثابت حرف *hwdevice_ctx_get_name(فراغ *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    ܦܢܐ ctx->hw_type->name;
}

ساكن ثابت AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .item_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .version    = LIBAVUTIL_VERSION_INT,
};

ساكن فراغ hwdevice_ctx_free(فراغ *opaque, uint8_t *data)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)data;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    ܐܢ (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    ܐܢ (ctx->حرر)
        ctx->حرر(ctx);

    av_buffer_unref(&ctxi->source_device);

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

    لكل (i = 0; hw_table[i]; i++) {
        ܐܢ (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            اكسر;
        }
    }
    ܐܢ (!hw_type)
        ܦܢܐ عدم;

    ctxi = av_mallocz(حجم(*ctxi));
    ܐܢ (!ctxi)
        ܦܢܐ عدم;
    ctx = &ctxi->p;

    ܐܢ (hw_type->device_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_size);
        ܐܢ (!ctx->hwctx)
            اذهب fail;
    }

    buf = av_buffer_create((uint8_t*)ctx, حجم(*ctx),
                           hwdevice_ctx_free, عدم,
                           AV_BUFFER_FLAG_READONLY);
    ܐܢ (!buf)
        اذهب fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    ܦܢܐ buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ܦܢܐ عدم;
}

صحيح av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->data;
    AVHWDeviceContext *ctx  = &ctxi->p;
    صحيح ret = 0;

    ܐܢ (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    ܦܢܐ ret;
}

ساكن ثابت AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .item_name  = av_default_item_name,
    .version    = LIBAVUTIL_VERSION_INT,
};

ساكن فراغ hwframe_ctx_free(فراغ *opaque, uint8_t *data)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)data;
    AVHWFramesContext *ctx  = &ctxi->p;

    ܐܢ (ctxi->pool_internal)
        av_buffer_pool_uninit(&ctxi->pool_internal);

    av_buffer_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    ܐܢ (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    ܐܢ (ctx->حرر)
        ctx->حرر(ctx);

    av_buffer_unref(&ctxi->source_frames);

    av_buffer_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_in)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_in->data;
    ثابت HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = عدم;

    ctxi = av_mallocz(حجم(*ctxi));
    ܐܢ (!ctxi)
        ܦܢܐ عدم;
    ctx  = &ctxi->p;

    ܐܢ (ff_mutex_init(&ctxi->transfer_pool_lock, عدم)) {
        av_free(ctxi);
        ܦܢܐ عدم;
    }

    ܐܢ (hw_type->frames_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_size);
        ܐܢ (!ctx->hwctx)
            اذهب fail;
    }

    device_ref = av_buffer_ref(device_ref_in);
    ܐܢ (!device_ref)
        اذهب fail;

    buf = av_buffer_create((uint8_t*)ctx, حجم(*ctx),
                           hwframe_ctx_free, عدم,
                           AV_BUFFER_FLAG_READONLY);
    ܐܢ (!buf)
        اذهب fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    ܦܢܐ buf;

fail:
    av_buffer_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ܦܢܐ عدم;
}

ساكن صحيح hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->data;
    AVFrame **frames;
    صحيح i, ret = 0;

    frames = av_calloc(ctx->initial_pool_size, حجم(*frames));
    ܐܢ (!frames)
        ܦܢܐ AVERROR(ENOMEM);

    لكل (i = 0; i < ctx->initial_pool_size; i++) {
        frames[i] = av_frame_alloc();
        ܐܢ (!frames[i])
            اذهب fail;

        ret = av_hwframe_get_buffer(ref, frames[i], 0);
        ܐܢ (ret < 0)
            اذهب fail;
    }

fail:
    لكل (i = 0; i < ctx->initial_pool_size; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    ܦܢܐ ret;
}

صحيح av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    ثابت تعداد AVPixelFormat *pix_fmt;
    صحيح ret;

    ܐܢ (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        ܦܢܐ 0;
    }

    /* validate the pixel format */
    لكل (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        ܐܢ (*pix_fmt == ctx->format)
            اكسر;
    }
    ܐܢ (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        ܦܢܐ AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_size(ctx->width, ctx->height, 0, ctx);
    ܐܢ (ret < 0)
        ܦܢܐ ret;

    /* format-specific init */
    ܐܢ (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        ܐܢ (ret < 0)
            ܦܢܐ ret;
    }

    ܐܢ (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    ܐܢ (ctx->initial_pool_size > 0) {
        ret = hwframe_pool_prealloc(ref);
        ܐܢ (ret < 0)
            ܦܢܐ ret;
    }

    ܦܢܐ 0;
}

صحيح av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    تعداد AVHWFrameTransferDirection dir,
                                    تعداد AVPixelFormat **formats, صحيح flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;

    ܐܢ (!ctxi->hw_type->transfer_get_formats)
        ܦܢܐ AVERROR(ENOSYS);

    ܦܢܐ ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

ساكن فراغ transfer_pool_free(فراغ *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_buffer_unref(&device_ref);
}

ساكن AVBufferRef *transfer_buffer_alloc(فراغ *opaque, size_t size)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = عدم;

    ff_mutex_lock(&ctxi->transfer_pool_lock);
    ܐܢ (ctxi->transfer_pool_size != size) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_buffer_alloc ?
                                  av_buffer_ref(ctxi->p.device_ref) : عدم;

        av_buffer_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_buffer_pool_init2(size, device_ref,
                                 ctxi->hw_type->transfer_buffer_alloc,
                                 transfer_pool_free) :
            av_buffer_pool_init(size, عدم);
        ctxi->transfer_pool_size = ctxi->transfer_pool ? size : 0;
        ܐܢ (!ctxi->transfer_pool)
            av_buffer_unref(&device_ref);
    }
    ܐܢ (ctxi->transfer_pool)
        buf = av_buffer_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    ܦܢܐ buf ? buf : av_buffer_alloc(size);
}

صحيح av_hwframe_get_transfer_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    ܦܢܐ ff_frame_get_video_buffer(frame, 0, transfer_buffer_alloc,
                                     hwframe_ctx->data);
}

ساكن صحيح transfer_data_alloc(AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    صحيح ret = 0;

    ܐܢ (!src->hw_frames_ctx)
        ܦܢܐ AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;

    frame_tmp = av_frame_alloc();
    ܐܢ (!frame_tmp)
        ܦܢܐ AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    ܐܢ (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } ܐܚܪܢܐ {
        تعداد AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        ܐܢ (ret < 0)
            اذهب fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_buffer(src->hw_frames_ctx, frame_tmp);
    ܐܢ (ret < 0)
        اذهب fail;

    ret = av_hwframe_transfer_data(frame_tmp, src, flags);
    ܐܢ (ret < 0)
        اذهب fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    ܦܢܐ ret;
}

صحيح av_hwframe_transfer_data(AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    صحيح ret;

    ܐܢ (!dst->buf[0])
        ܦܢܐ transfer_data_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    ܐܢ (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->data;

        ܐܢ (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            ܦܢܐ AVERROR(ENOSYS);
        }

        ܐܢ (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            ܦܢܐ AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        ܐܢ (src_ctx->hw_type->transfer_data_from)
            ret = src_ctx->hw_type->transfer_data_from(&src_ctx->p, dst, src);
        ܐܢ (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_data_to)
            ret = dst_ctx->hw_type->transfer_data_to(&dst_ctx->p, dst, src);
        ܐܢ (ret < 0)
            ܦܢܐ ret;
    } ܐܚܪܢܐ {
        ܐܢ (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->data;

            ܐܢ (!ctx->hw_type->transfer_data_from)
                ܦܢܐ AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_from(&ctx->p, dst, src);
            ܐܢ (ret < 0)
                ܦܢܐ ret;
        } ܐܚܪܢܐ ܐܢ (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->data;

            ܐܢ (!ctx->hw_type->transfer_data_to)
                ܦܢܐ AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_to(&ctx->p, dst, src);
            ܐܢ (ret < 0)
                ܦܢܐ ret;
        } ܐܚܪܢܐ {
            ܦܢܐ AVERROR(ENOSYS);
        }
    }
    ܦܢܐ 0;
}

صحيح av_hwframe_get_buffer(AVBufferRef *hwframe_ref, AVFrame *frame, صحيح flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    صحيح ret;

    ܐܢ (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
        ܐܢ (!frame->hw_frames_ctx)
            ܦܢܐ AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        ܐܢ (!src_frame)
            ܦܢܐ AVERROR(ENOMEM);

        ret = av_hwframe_get_buffer(ctxi->source_frames,
                                    src_frame, 0);
        ܐܢ (ret < 0) {
            av_frame_free(&src_frame);
            ܦܢܐ ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        ܐܢ (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            ܦܢܐ ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        ܦܢܐ 0;
    }

    ܐܢ (!ctxi->hw_type->frames_get_buffer)
        ܦܢܐ AVERROR(ENOSYS);

    ܐܢ (!ctx->pool)
        ܦܢܐ AVERROR(EINVAL);

    frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    ܐܢ (!frame->hw_frames_ctx)
        ܦܢܐ AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_buffer(ctx, frame);
    ܐܢ (ret < 0) {
        av_buffer_unref(&frame->hw_frames_ctx);
        ܦܢܐ ret;
    }

    frame->extended_data = frame->data;

    ܦܢܐ 0;
}

فراغ *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    ثابت HWContextType  *hw_type = ctx->hw_type;

    ܐܢ (hw_type->device_hwconfig_size == 0)
        ܦܢܐ عدم;

    ܦܢܐ av_mallocz(hw_type->device_hwconfig_size);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ثابت فراغ *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    ثابت HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    ܐܢ (!hw_type->frames_get_constraints)
        ܦܢܐ عدم;

    constraints = av_mallocz(حجم(*constraints));
    ܐܢ (!constraints)
        ܦܢܐ عدم;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = INT_MAX;

    ܐܢ (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        ܦܢܐ constraints;
    } ܐܚܪܢܐ {
        av_hwframe_constraints_free(&constraints);
        ܦܢܐ عدم;
    }
}

فراغ av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    ܐܢ (*constraints) {
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
    ܐܢ (!device_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->data;

    ܐܢ (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        اذهب fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    ܐܢ (ret < 0)
        اذهب fail;

    ret = av_hwdevice_ctx_init(device_ref);
    ܐܢ (ret < 0)
        اذهب fail;

    *pdevice_ref = device_ref;
    ܦܢܐ 0;
fail:
    av_buffer_unref(&device_ref);
    *pdevice_ref = عدم;
    ܦܢܐ ret;
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
    ܟܡܐ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        ܐܢ (tmp_ctx->p.type == type) {
            dst_ref = av_buffer_ref(tmp_ref);
            ܐܢ (!dst_ref) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
            اذهب done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    ܐܢ (!dst_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->data;

    tmp_ref = src_ref;
    ܟܡܐ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        ܐܢ (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            ܐܢ (ret == 0) {
                dst_ctx->source_device = av_buffer_ref(src_ref);
                ܐܢ (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    اذهب fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                ܐܢ (ret < 0)
                    اذهب fail;
                اذهب done;
            }
            ܐܢ (ret != AVERROR(ENOSYS))
                اذهب fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    اذهب fail;

done:
    *dst_ref_ptr = dst_ref;
    ܦܢܐ 0;

fail:
    av_buffer_unref(&dst_ref);
    *dst_ref_ptr = عدم;
    ܦܢܐ ret;
}

صحيح av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   تعداد AVHWDeviceType type,
                                   AVBufferRef *src_ref, صحيح flags)
{
    ܦܢܐ av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               عدم, flags);
}

ساكن فراغ ff_hwframe_unmap(فراغ *opaque, uint8_t *data)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)data;
    AVHWFramesContext *ctx = opaque;

    ܐܢ (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_buffer_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

صحيح ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ثابت AVFrame *src,
                          فراغ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          فراغ *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->data;
    HWMapDescriptor *hwmap;
    صحيح ret;

    hwmap = av_mallocz(حجم(*hwmap));
    ܐܢ (!hwmap) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    hwmap->source = av_frame_alloc();
    ܐܢ (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    ܐܢ (ret < 0)
        اذهب fail;

    hwmap->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    ܐܢ (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_buffer_create((uint8_t*)hwmap, حجم(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    ܐܢ (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    ܦܢܐ 0;

fail:
    ܐܢ (hwmap) {
        av_buffer_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    ܦܢܐ ret;
}

صحيح av_hwframe_map(AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    تعداد AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    صحيح ret;

    ܐܢ (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        ܐܢ ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->data ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            ܐܢ (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                ܦܢܐ AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->data;
            ܦܢܐ av_frame_replace(dst, hwmap->source);
        }
    }

    ܐܢ (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;

        ܐܢ (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            ܐܢ (ret >= 0)
                ܦܢܐ ret;
            ܐܚܪܢܐ ܐܢ (ret != AVERROR(ENOSYS))
                اذهب fail;
        }
    }

    ܐܢ (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        ܐܢ (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            ܐܢ (ret >= 0)
                ܦܢܐ ret;
            ܐܚܪܢܐ ܐܢ (ret != AVERROR(ENOSYS))
                اذهب fail;
        }
    }

    ܦܢܐ AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_frames == عدم ||
               orig_dst_frames == dst->hw_frames_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_frames_ctx = عدم;
    av_frame_unref(dst);

    dst->hw_frames_ctx = orig_dst_frames;
    dst->format        = orig_dst_fmt;

    ܦܢܐ ret;
}

صحيح av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  تعداد AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  صحيح flags)
{
    AVBufferRef   *dst_ref = عدم;
    FFHWFramesContext *dsti = عدم;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->data;
    AVHWFramesContext *dst, *src = &srci->p;
    صحيح ret;

    ܐܢ (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->data;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->data;

        ܐܢ (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_buffer_ref(srci->source_frames);
            ܐܢ (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                اذهب fail;
            }
            ܦܢܐ 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    ܐܢ (!dst_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->data;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->width     = src->width;
    dst->height    = src->height;

    dsti->source_frames = av_buffer_ref(source_frame_ctx);
    ܐܢ (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    dsti->source_allocation_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_DIRECT);

    ret = AVERROR(ENOSYS);
    ܐܢ (srci->hw_type->frames_derive_from)
        ret = srci->hw_type->frames_derive_from(dst, src, flags);
    ܐܢ (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->frames_derive_to)
        ret = dsti->hw_type->frames_derive_to(dst, src, flags);
    ܐܢ (ret == AVERROR(ENOSYS))
        ret = 0;
    ܐܢ (ret)
        اذهب fail;

    *derived_frame_ctx = dst_ref;
    ܦܢܐ 0;

fail:
    ܐܢ (dsti)
        av_buffer_unref(&dsti->source_frames);
    av_buffer_unref(&dst_ref);
    ܦܢܐ ret;
}

صحيح ff_hwframe_map_replace(AVFrame *dst, ثابت AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->data;
    ܦܢܐ av_frame_replace(hwmap->source, src);
}
