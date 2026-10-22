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

ایستا ثابت HWContextType * ثابت hw_table[] = {
#اگر CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#endif
#اگر CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#endif
#اگر CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#endif
#اگر CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#endif
#اگر CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#endif
#اگر CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#endif
#اگر CONFIG_QSV
    &ff_hwcontext_type_qsv,
#endif
#اگر CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#endif
#اگر CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#endif
#اگر CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#endif
#اگر CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#endif
#اگر CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#endif
#اگر CONFIG_AMF
    &ff_hwcontext_type_amf,
#endif
#اگر CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#endif
    پوچ,
};

ایستا ثابت نویسه *ثابت hw_type_names[] = {
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

تعریفنوع ساختار FFHWDeviceContext {
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

شمارش AVHWDeviceType av_hwdevice_find_type_by_name(ثابت نویسه *name)
{
    صحیح type;
    برای (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        اگر (hw_type_names[type] && !strcmp(hw_type_names[type], name))
            بازگشت type;
    }
    بازگشت AV_HWDEVICE_TYPE_NONE;
}

ثابت نویسه *av_hwdevice_get_type_name(شمارش AVHWDeviceType type)
{
    اگر (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        بازگشت hw_type_names[type];
    وگرنه
        بازگشت پوچ;
}

شمارش AVHWDeviceType av_hwdevice_iterate_types(شمارش AVHWDeviceType prev)
{
    شمارش AVHWDeviceType next;
    صحیح i, set = 0;
    برای (i = 0; hw_table[i]; i++) {
        اگر (prev != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= prev)
            ادامه;
        اگر (!set || hw_table[i]->type < next) {
            next = hw_table[i]->type;
            set = 1;
        }
    }
    بازگشت set ? next : AV_HWDEVICE_TYPE_NONE;
}

ایستا ثابت نویسه *hwdevice_ctx_get_name(تهی *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    بازگشت ctx->hw_type->name;
}

ایستا ثابت AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .item_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .version    = LIBAVUTIL_VERSION_INT,
};

ایستا تهی hwdevice_ctx_free(تهی *opaque, uint8_t *data)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)data;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    اگر (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    اگر (ctx->آزاد)
        ctx->آزاد(ctx);

    av_buffer_unref(&ctxi->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(شمارش AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    ثابت HWContextType *hw_type = پوچ;
    صحیح i;

    برای (i = 0; hw_table[i]; i++) {
        اگر (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            بشکن;
        }
    }
    اگر (!hw_type)
        بازگشت پوچ;

    ctxi = av_mallocz(اندازه(*ctxi));
    اگر (!ctxi)
        بازگشت پوچ;
    ctx = &ctxi->p;

    اگر (hw_type->device_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_size);
        اگر (!ctx->hwctx)
            برو fail;
    }

    buf = av_buffer_create((uint8_t*)ctx, اندازه(*ctx),
                           hwdevice_ctx_free, پوچ,
                           AV_BUFFER_FLAG_READONLY);
    اگر (!buf)
        برو fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    بازگشت buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    بازگشت پوچ;
}

صحیح av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->data;
    AVHWDeviceContext *ctx  = &ctxi->p;
    صحیح ret = 0;

    اگر (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    بازگشت ret;
}

ایستا ثابت AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .item_name  = av_default_item_name,
    .version    = LIBAVUTIL_VERSION_INT,
};

ایستا تهی hwframe_ctx_free(تهی *opaque, uint8_t *data)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)data;
    AVHWFramesContext *ctx  = &ctxi->p;

    اگر (ctxi->pool_internal)
        av_buffer_pool_uninit(&ctxi->pool_internal);

    av_buffer_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    اگر (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    اگر (ctx->آزاد)
        ctx->آزاد(ctx);

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
    AVBufferRef *buf, *device_ref = پوچ;

    ctxi = av_mallocz(اندازه(*ctxi));
    اگر (!ctxi)
        بازگشت پوچ;
    ctx  = &ctxi->p;

    اگر (ff_mutex_init(&ctxi->transfer_pool_lock, پوچ)) {
        av_free(ctxi);
        بازگشت پوچ;
    }

    اگر (hw_type->frames_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_size);
        اگر (!ctx->hwctx)
            برو fail;
    }

    device_ref = av_buffer_ref(device_ref_in);
    اگر (!device_ref)
        برو fail;

    buf = av_buffer_create((uint8_t*)ctx, اندازه(*ctx),
                           hwframe_ctx_free, پوچ,
                           AV_BUFFER_FLAG_READONLY);
    اگر (!buf)
        برو fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    بازگشت buf;

fail:
    av_buffer_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    بازگشت پوچ;
}

ایستا صحیح hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->data;
    AVFrame **frames;
    صحیح i, ret = 0;

    frames = av_calloc(ctx->initial_pool_size, اندازه(*frames));
    اگر (!frames)
        بازگشت AVERROR(ENOMEM);

    برای (i = 0; i < ctx->initial_pool_size; i++) {
        frames[i] = av_frame_alloc();
        اگر (!frames[i])
            برو fail;

        ret = av_hwframe_get_buffer(ref, frames[i], 0);
        اگر (ret < 0)
            برو fail;
    }

fail:
    برای (i = 0; i < ctx->initial_pool_size; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    بازگشت ret;
}

صحیح av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    ثابت شمارش AVPixelFormat *pix_fmt;
    صحیح ret;

    اگر (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        بازگشت 0;
    }

    /* validate the pixel format */
    برای (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        اگر (*pix_fmt == ctx->format)
            بشکن;
    }
    اگر (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        بازگشت AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_size(ctx->width, ctx->height, 0, ctx);
    اگر (ret < 0)
        بازگشت ret;

    /* format-specific init */
    اگر (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        اگر (ret < 0)
            بازگشت ret;
    }

    اگر (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    اگر (ctx->initial_pool_size > 0) {
        ret = hwframe_pool_prealloc(ref);
        اگر (ret < 0)
            بازگشت ret;
    }

    بازگشت 0;
}

صحیح av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    شمارش AVHWFrameTransferDirection dir,
                                    شمارش AVPixelFormat **formats, صحیح flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;

    اگر (!ctxi->hw_type->transfer_get_formats)
        بازگشت AVERROR(ENOSYS);

    بازگشت ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

ایستا تهی transfer_pool_free(تهی *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_buffer_unref(&device_ref);
}

ایستا AVBufferRef *transfer_buffer_alloc(تهی *opaque, size_t size)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = پوچ;

    ff_mutex_lock(&ctxi->transfer_pool_lock);
    اگر (ctxi->transfer_pool_size != size) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_buffer_alloc ?
                                  av_buffer_ref(ctxi->p.device_ref) : پوچ;

        av_buffer_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_buffer_pool_init2(size, device_ref,
                                 ctxi->hw_type->transfer_buffer_alloc,
                                 transfer_pool_free) :
            av_buffer_pool_init(size, پوچ);
        ctxi->transfer_pool_size = ctxi->transfer_pool ? size : 0;
        اگر (!ctxi->transfer_pool)
            av_buffer_unref(&device_ref);
    }
    اگر (ctxi->transfer_pool)
        buf = av_buffer_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    بازگشت buf ? buf : av_buffer_alloc(size);
}

صحیح av_hwframe_get_transfer_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    بازگشت ff_frame_get_video_buffer(frame, 0, transfer_buffer_alloc,
                                     hwframe_ctx->data);
}

ایستا صحیح transfer_data_alloc(AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    صحیح ret = 0;

    اگر (!src->hw_frames_ctx)
        بازگشت AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;

    frame_tmp = av_frame_alloc();
    اگر (!frame_tmp)
        بازگشت AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    اگر (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } وگرنه {
        شمارش AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        اگر (ret < 0)
            برو fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_buffer(src->hw_frames_ctx, frame_tmp);
    اگر (ret < 0)
        برو fail;

    ret = av_hwframe_transfer_data(frame_tmp, src, flags);
    اگر (ret < 0)
        برو fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    بازگشت ret;
}

صحیح av_hwframe_transfer_data(AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    صحیح ret;

    اگر (!dst->buf[0])
        بازگشت transfer_data_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    اگر (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->data;

        اگر (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            بازگشت AVERROR(ENOSYS);
        }

        اگر (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            بازگشت AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        اگر (src_ctx->hw_type->transfer_data_from)
            ret = src_ctx->hw_type->transfer_data_from(&src_ctx->p, dst, src);
        اگر (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_data_to)
            ret = dst_ctx->hw_type->transfer_data_to(&dst_ctx->p, dst, src);
        اگر (ret < 0)
            بازگشت ret;
    } وگرنه {
        اگر (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->data;

            اگر (!ctx->hw_type->transfer_data_from)
                بازگشت AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_from(&ctx->p, dst, src);
            اگر (ret < 0)
                بازگشت ret;
        } وگرنه اگر (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->data;

            اگر (!ctx->hw_type->transfer_data_to)
                بازگشت AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_to(&ctx->p, dst, src);
            اگر (ret < 0)
                بازگشت ret;
        } وگرنه {
            بازگشت AVERROR(ENOSYS);
        }
    }
    بازگشت 0;
}

صحیح av_hwframe_get_buffer(AVBufferRef *hwframe_ref, AVFrame *frame, صحیح flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    صحیح ret;

    اگر (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
        اگر (!frame->hw_frames_ctx)
            بازگشت AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        اگر (!src_frame)
            بازگشت AVERROR(ENOMEM);

        ret = av_hwframe_get_buffer(ctxi->source_frames,
                                    src_frame, 0);
        اگر (ret < 0) {
            av_frame_free(&src_frame);
            بازگشت ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        اگر (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            بازگشت ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        بازگشت 0;
    }

    اگر (!ctxi->hw_type->frames_get_buffer)
        بازگشت AVERROR(ENOSYS);

    اگر (!ctx->pool)
        بازگشت AVERROR(EINVAL);

    frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    اگر (!frame->hw_frames_ctx)
        بازگشت AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_buffer(ctx, frame);
    اگر (ret < 0) {
        av_buffer_unref(&frame->hw_frames_ctx);
        بازگشت ret;
    }

    frame->extended_data = frame->data;

    بازگشت 0;
}

تهی *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    ثابت HWContextType  *hw_type = ctx->hw_type;

    اگر (hw_type->device_hwconfig_size == 0)
        بازگشت پوچ;

    بازگشت av_mallocz(hw_type->device_hwconfig_size);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ثابت تهی *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    ثابت HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    اگر (!hw_type->frames_get_constraints)
        بازگشت پوچ;

    constraints = av_mallocz(اندازه(*constraints));
    اگر (!constraints)
        بازگشت پوچ;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = INT_MAX;

    اگر (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        بازگشت constraints;
    } وگرنه {
        av_hwframe_constraints_free(&constraints);
        بازگشت پوچ;
    }
}

تهی av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    اگر (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

صحیح av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, شمارش AVHWDeviceType type,
                           ثابت نویسه *device, AVDictionary *opts, صحیح flags)
{
    AVBufferRef *device_ref = پوچ;
    FFHWDeviceContext *device_ctx;
    صحیح ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    اگر (!device_ref) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->data;

    اگر (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        برو fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    اگر (ret < 0)
        برو fail;

    ret = av_hwdevice_ctx_init(device_ref);
    اگر (ret < 0)
        برو fail;

    *pdevice_ref = device_ref;
    بازگشت 0;
fail:
    av_buffer_unref(&device_ref);
    *pdevice_ref = پوچ;
    بازگشت ret;
}

صحیح av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        شمارش AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, صحیح flags)
{
    AVBufferRef *dst_ref = پوچ, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    صحیح ret = 0;

    tmp_ref = src_ref;
    وقتی (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        اگر (tmp_ctx->p.type == type) {
            dst_ref = av_buffer_ref(tmp_ref);
            اگر (!dst_ref) {
                ret = AVERROR(ENOMEM);
                برو fail;
            }
            برو done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    اگر (!dst_ref) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->data;

    tmp_ref = src_ref;
    وقتی (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        اگر (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            اگر (ret == 0) {
                dst_ctx->source_device = av_buffer_ref(src_ref);
                اگر (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    برو fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                اگر (ret < 0)
                    برو fail;
                برو done;
            }
            اگر (ret != AVERROR(ENOSYS))
                برو fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    برو fail;

done:
    *dst_ref_ptr = dst_ref;
    بازگشت 0;

fail:
    av_buffer_unref(&dst_ref);
    *dst_ref_ptr = پوچ;
    بازگشت ret;
}

صحیح av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   شمارش AVHWDeviceType type,
                                   AVBufferRef *src_ref, صحیح flags)
{
    بازگشت av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               پوچ, flags);
}

ایستا تهی ff_hwframe_unmap(تهی *opaque, uint8_t *data)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)data;
    AVHWFramesContext *ctx = opaque;

    اگر (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_buffer_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

صحیح ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ثابت AVFrame *src,
                          تهی (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          تهی *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->data;
    HWMapDescriptor *hwmap;
    صحیح ret;

    hwmap = av_mallocz(اندازه(*hwmap));
    اگر (!hwmap) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }

    hwmap->source = av_frame_alloc();
    اگر (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    اگر (ret < 0)
        برو fail;

    hwmap->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    اگر (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_buffer_create((uint8_t*)hwmap, اندازه(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    اگر (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }

    بازگشت 0;

fail:
    اگر (hwmap) {
        av_buffer_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    بازگشت ret;
}

صحیح av_hwframe_map(AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    شمارش AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    صحیح ret;

    اگر (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        اگر ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->data ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            اگر (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                بازگشت AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->data;
            بازگشت av_frame_replace(dst, hwmap->source);
        }
    }

    اگر (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;

        اگر (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            اگر (ret >= 0)
                بازگشت ret;
            وگرنه اگر (ret != AVERROR(ENOSYS))
                برو fail;
        }
    }

    اگر (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        اگر (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            اگر (ret >= 0)
                بازگشت ret;
            وگرنه اگر (ret != AVERROR(ENOSYS))
                برو fail;
        }
    }

    بازگشت AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_frames == پوچ ||
               orig_dst_frames == dst->hw_frames_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_frames_ctx = پوچ;
    av_frame_unref(dst);

    dst->hw_frames_ctx = orig_dst_frames;
    dst->format        = orig_dst_fmt;

    بازگشت ret;
}

صحیح av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  شمارش AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  صحیح flags)
{
    AVBufferRef   *dst_ref = پوچ;
    FFHWFramesContext *dsti = پوچ;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->data;
    AVHWFramesContext *dst, *src = &srci->p;
    صحیح ret;

    اگر (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->data;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->data;

        اگر (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_buffer_ref(srci->source_frames);
            اگر (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                برو fail;
            }
            بازگشت 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    اگر (!dst_ref) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->data;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->width     = src->width;
    dst->height    = src->height;

    dsti->source_frames = av_buffer_ref(source_frame_ctx);
    اگر (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }

    dsti->source_allocation_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_DIRECT);

    ret = AVERROR(ENOSYS);
    اگر (srci->hw_type->frames_derive_from)
        ret = srci->hw_type->frames_derive_from(dst, src, flags);
    اگر (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->frames_derive_to)
        ret = dsti->hw_type->frames_derive_to(dst, src, flags);
    اگر (ret == AVERROR(ENOSYS))
        ret = 0;
    اگر (ret)
        برو fail;

    *derived_frame_ctx = dst_ref;
    بازگشت 0;

fail:
    اگر (dsti)
        av_buffer_unref(&dsti->source_frames);
    av_buffer_unref(&dst_ref);
    بازگشت ret;
}

صحیح ff_hwframe_map_replace(AVFrame *dst, ثابت AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->data;
    بازگشت av_frame_replace(hwmap->source, src);
}
