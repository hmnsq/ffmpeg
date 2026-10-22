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

#अन्तर्भाव "config.h"

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "buffer.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "frame_internal.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "imgutils.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "pixfmt.h"

स्थिर अचर HWContextType * अचर hw_table[] = {
#यदि CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#endif
#यदि CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#endif
#यदि CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#endif
#यदि CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#endif
#यदि CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#endif
#यदि CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#endif
#यदि CONFIG_QSV
    &ff_hwcontext_type_qsv,
#endif
#यदि CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#endif
#यदि CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#endif
#यदि CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#endif
#यदि CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#endif
#यदि CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#endif
#यदि CONFIG_AMF
    &ff_hwcontext_type_amf,
#endif
#यदि CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#endif
    रिक्त,
};

स्थिर अचर वर्ण *अचर hw_type_names[] = {
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

प्रकारनिर्देश संरचना FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    अचर HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *source_device;
} FFHWDeviceContext;

गणना AVHWDeviceType av_hwdevice_find_type_by_name(अचर वर्ण *name)
{
    पूर्णाङ्क type;
    लागि (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        यदि (hw_type_names[type] && !म_भेद(hw_type_names[type], name))
            फर्काऊ type;
    }
    फर्काऊ AV_HWDEVICE_TYPE_NONE;
}

अचर वर्ण *av_hwdevice_get_type_name(गणना AVHWDeviceType type)
{
    यदि (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        फर्काऊ hw_type_names[type];
    अन्यथा
        फर्काऊ रिक्त;
}

गणना AVHWDeviceType av_hwdevice_iterate_types(गणना AVHWDeviceType prev)
{
    गणना AVHWDeviceType next;
    पूर्णाङ्क i, set = 0;
    लागि (i = 0; hw_table[i]; i++) {
        यदि (prev != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= prev)
            जारी;
        यदि (!set || hw_table[i]->type < next) {
            next = hw_table[i]->type;
            set = 1;
        }
    }
    फर्काऊ set ? next : AV_HWDEVICE_TYPE_NONE;
}

स्थिर अचर वर्ण *hwdevice_ctx_get_name(शून्य *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    फर्काऊ ctx->hw_type->name;
}

स्थिर अचर AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .item_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .version    = LIBAVUTIL_VERSION_INT,
};

स्थिर शून्य hwdevice_ctx_free(शून्य *opaque, uint8_t *data)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)data;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    यदि (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    यदि (ctx->मुक्त)
        ctx->मुक्त(ctx);

    av_buffer_unref(&ctxi->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(गणना AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    अचर HWContextType *hw_type = रिक्त;
    पूर्णाङ्क i;

    लागि (i = 0; hw_table[i]; i++) {
        यदि (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            रोक;
        }
    }
    यदि (!hw_type)
        फर्काऊ रिक्त;

    ctxi = av_mallocz(परिमाण(*ctxi));
    यदि (!ctxi)
        फर्काऊ रिक्त;
    ctx = &ctxi->p;

    यदि (hw_type->device_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_size);
        यदि (!ctx->hwctx)
            गच्छ fail;
    }

    buf = av_buffer_create((uint8_t*)ctx, परिमाण(*ctx),
                           hwdevice_ctx_free, रिक्त,
                           AV_BUFFER_FLAG_READONLY);
    यदि (!buf)
        गच्छ fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    फर्काऊ buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    फर्काऊ रिक्त;
}

पूर्णाङ्क av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->data;
    AVHWDeviceContext *ctx  = &ctxi->p;
    पूर्णाङ्क ret = 0;

    यदि (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    फर्काऊ ret;
}

स्थिर अचर AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .item_name  = av_default_item_name,
    .version    = LIBAVUTIL_VERSION_INT,
};

स्थिर शून्य hwframe_ctx_free(शून्य *opaque, uint8_t *data)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)data;
    AVHWFramesContext *ctx  = &ctxi->p;

    यदि (ctxi->pool_internal)
        av_buffer_pool_uninit(&ctxi->pool_internal);

    av_buffer_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    यदि (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    यदि (ctx->मुक्त)
        ctx->मुक्त(ctx);

    av_buffer_unref(&ctxi->source_frames);

    av_buffer_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_in)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_in->data;
    अचर HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = रिक्त;

    ctxi = av_mallocz(परिमाण(*ctxi));
    यदि (!ctxi)
        फर्काऊ रिक्त;
    ctx  = &ctxi->p;

    यदि (ff_mutex_init(&ctxi->transfer_pool_lock, रिक्त)) {
        av_free(ctxi);
        फर्काऊ रिक्त;
    }

    यदि (hw_type->frames_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_size);
        यदि (!ctx->hwctx)
            गच्छ fail;
    }

    device_ref = av_buffer_ref(device_ref_in);
    यदि (!device_ref)
        गच्छ fail;

    buf = av_buffer_create((uint8_t*)ctx, परिमाण(*ctx),
                           hwframe_ctx_free, रिक्त,
                           AV_BUFFER_FLAG_READONLY);
    यदि (!buf)
        गच्छ fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    फर्काऊ buf;

fail:
    av_buffer_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    फर्काऊ रिक्त;
}

स्थिर पूर्णाङ्क hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->data;
    AVFrame **frames;
    पूर्णाङ्क i, ret = 0;

    frames = av_calloc(ctx->initial_pool_size, परिमाण(*frames));
    यदि (!frames)
        फर्काऊ AVERROR(ENOMEM);

    लागि (i = 0; i < ctx->initial_pool_size; i++) {
        frames[i] = av_frame_alloc();
        यदि (!frames[i])
            गच्छ fail;

        ret = av_hwframe_get_buffer(ref, frames[i], 0);
        यदि (ret < 0)
            गच्छ fail;
    }

fail:
    लागि (i = 0; i < ctx->initial_pool_size; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    फर्काऊ ret;
}

पूर्णाङ्क av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    अचर गणना AVPixelFormat *pix_fmt;
    पूर्णाङ्क ret;

    यदि (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        फर्काऊ 0;
    }

    /* validate the pixel format */
    लागि (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        यदि (*pix_fmt == ctx->format)
            रोक;
    }
    यदि (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        फर्काऊ AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_size(ctx->width, ctx->height, 0, ctx);
    यदि (ret < 0)
        फर्काऊ ret;

    /* format-specific init */
    यदि (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        यदि (ret < 0)
            फर्काऊ ret;
    }

    यदि (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    यदि (ctx->initial_pool_size > 0) {
        ret = hwframe_pool_prealloc(ref);
        यदि (ret < 0)
            फर्काऊ ret;
    }

    फर्काऊ 0;
}

पूर्णाङ्क av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    गणना AVHWFrameTransferDirection dir,
                                    गणना AVPixelFormat **formats, पूर्णाङ्क flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;

    यदि (!ctxi->hw_type->transfer_get_formats)
        फर्काऊ AVERROR(ENOSYS);

    फर्काऊ ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

स्थिर शून्य transfer_pool_free(शून्य *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_buffer_unref(&device_ref);
}

स्थिर AVBufferRef *transfer_buffer_alloc(शून्य *opaque, माप_प्रकार size)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = रिक्त;

    ff_mutex_lock(&ctxi->transfer_pool_lock);
    यदि (ctxi->transfer_pool_size != size) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_buffer_alloc ?
                                  av_buffer_ref(ctxi->p.device_ref) : रिक्त;

        av_buffer_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_buffer_pool_init2(size, device_ref,
                                 ctxi->hw_type->transfer_buffer_alloc,
                                 transfer_pool_free) :
            av_buffer_pool_init(size, रिक्त);
        ctxi->transfer_pool_size = ctxi->transfer_pool ? size : 0;
        यदि (!ctxi->transfer_pool)
            av_buffer_unref(&device_ref);
    }
    यदि (ctxi->transfer_pool)
        buf = av_buffer_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    फर्काऊ buf ? buf : av_buffer_alloc(size);
}

पूर्णाङ्क av_hwframe_get_transfer_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    फर्काऊ ff_frame_get_video_buffer(frame, 0, transfer_buffer_alloc,
                                     hwframe_ctx->data);
}

स्थिर पूर्णाङ्क transfer_data_alloc(AVFrame *dst, अचर AVFrame *src, पूर्णाङ्क flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    पूर्णाङ्क ret = 0;

    यदि (!src->hw_frames_ctx)
        फर्काऊ AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;

    frame_tmp = av_frame_alloc();
    यदि (!frame_tmp)
        फर्काऊ AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    यदि (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } अन्यथा {
        गणना AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        यदि (ret < 0)
            गच्छ fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_buffer(src->hw_frames_ctx, frame_tmp);
    यदि (ret < 0)
        गच्छ fail;

    ret = av_hwframe_transfer_data(frame_tmp, src, flags);
    यदि (ret < 0)
        गच्छ fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    फर्काऊ ret;
}

पूर्णाङ्क av_hwframe_transfer_data(AVFrame *dst, अचर AVFrame *src, पूर्णाङ्क flags)
{
    पूर्णाङ्क ret;

    यदि (!dst->buf[0])
        फर्काऊ transfer_data_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    यदि (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->data;

        यदि (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            फर्काऊ AVERROR(ENOSYS);
        }

        यदि (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            फर्काऊ AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        यदि (src_ctx->hw_type->transfer_data_from)
            ret = src_ctx->hw_type->transfer_data_from(&src_ctx->p, dst, src);
        यदि (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_data_to)
            ret = dst_ctx->hw_type->transfer_data_to(&dst_ctx->p, dst, src);
        यदि (ret < 0)
            फर्काऊ ret;
    } अन्यथा {
        यदि (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->data;

            यदि (!ctx->hw_type->transfer_data_from)
                फर्काऊ AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_from(&ctx->p, dst, src);
            यदि (ret < 0)
                फर्काऊ ret;
        } अन्यथा यदि (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->data;

            यदि (!ctx->hw_type->transfer_data_to)
                फर्काऊ AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_to(&ctx->p, dst, src);
            यदि (ret < 0)
                फर्काऊ ret;
        } अन्यथा {
            फर्काऊ AVERROR(ENOSYS);
        }
    }
    फर्काऊ 0;
}

पूर्णाङ्क av_hwframe_get_buffer(AVBufferRef *hwframe_ref, AVFrame *frame, पूर्णाङ्क flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    पूर्णाङ्क ret;

    यदि (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
        यदि (!frame->hw_frames_ctx)
            फर्काऊ AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        यदि (!src_frame)
            फर्काऊ AVERROR(ENOMEM);

        ret = av_hwframe_get_buffer(ctxi->source_frames,
                                    src_frame, 0);
        यदि (ret < 0) {
            av_frame_free(&src_frame);
            फर्काऊ ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        यदि (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            फर्काऊ ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        फर्काऊ 0;
    }

    यदि (!ctxi->hw_type->frames_get_buffer)
        फर्काऊ AVERROR(ENOSYS);

    यदि (!ctx->pool)
        फर्काऊ AVERROR(EINVAL);

    frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    यदि (!frame->hw_frames_ctx)
        फर्काऊ AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_buffer(ctx, frame);
    यदि (ret < 0) {
        av_buffer_unref(&frame->hw_frames_ctx);
        फर्काऊ ret;
    }

    frame->extended_data = frame->data;

    फर्काऊ 0;
}

शून्य *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    अचर HWContextType  *hw_type = ctx->hw_type;

    यदि (hw_type->device_hwconfig_size == 0)
        फर्काऊ रिक्त;

    फर्काऊ av_mallocz(hw_type->device_hwconfig_size);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           अचर शून्य *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    अचर HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    यदि (!hw_type->frames_get_constraints)
        फर्काऊ रिक्त;

    constraints = av_mallocz(परिमाण(*constraints));
    यदि (!constraints)
        फर्काऊ रिक्त;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = पूर्णांक_उच्च;

    यदि (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        फर्काऊ constraints;
    } अन्यथा {
        av_hwframe_constraints_free(&constraints);
        फर्काऊ रिक्त;
    }
}

शून्य av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    यदि (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

पूर्णाङ्क av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, गणना AVHWDeviceType type,
                           अचर वर्ण *device, AVDictionary *opts, पूर्णाङ्क flags)
{
    AVBufferRef *device_ref = रिक्त;
    FFHWDeviceContext *device_ctx;
    पूर्णाङ्क ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    यदि (!device_ref) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->data;

    यदि (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        गच्छ fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    यदि (ret < 0)
        गच्छ fail;

    ret = av_hwdevice_ctx_init(device_ref);
    यदि (ret < 0)
        गच्छ fail;

    *pdevice_ref = device_ref;
    फर्काऊ 0;
fail:
    av_buffer_unref(&device_ref);
    *pdevice_ref = रिक्त;
    फर्काऊ ret;
}

पूर्णाङ्क av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        गणना AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, पूर्णाङ्क flags)
{
    AVBufferRef *dst_ref = रिक्त, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    पूर्णाङ्क ret = 0;

    tmp_ref = src_ref;
    जबसम्म (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        यदि (tmp_ctx->p.type == type) {
            dst_ref = av_buffer_ref(tmp_ref);
            यदि (!dst_ref) {
                ret = AVERROR(ENOMEM);
                गच्छ fail;
            }
            गच्छ done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    यदि (!dst_ref) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->data;

    tmp_ref = src_ref;
    जबसम्म (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        यदि (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            यदि (ret == 0) {
                dst_ctx->source_device = av_buffer_ref(src_ref);
                यदि (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    गच्छ fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                यदि (ret < 0)
                    गच्छ fail;
                गच्छ done;
            }
            यदि (ret != AVERROR(ENOSYS))
                गच्छ fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    गच्छ fail;

done:
    *dst_ref_ptr = dst_ref;
    फर्काऊ 0;

fail:
    av_buffer_unref(&dst_ref);
    *dst_ref_ptr = रिक्त;
    फर्काऊ ret;
}

पूर्णाङ्क av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   गणना AVHWDeviceType type,
                                   AVBufferRef *src_ref, पूर्णाङ्क flags)
{
    फर्काऊ av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               रिक्त, flags);
}

स्थिर शून्य ff_hwframe_unmap(शून्य *opaque, uint8_t *data)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)data;
    AVHWFramesContext *ctx = opaque;

    यदि (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_buffer_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

पूर्णाङ्क ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, अचर AVFrame *src,
                          शून्य (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          शून्य *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->data;
    HWMapDescriptor *hwmap;
    पूर्णाङ्क ret;

    hwmap = av_mallocz(परिमाण(*hwmap));
    यदि (!hwmap) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    hwmap->source = av_frame_alloc();
    यदि (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    यदि (ret < 0)
        गच्छ fail;

    hwmap->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    यदि (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_buffer_create((uint8_t*)hwmap, परिमाण(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    यदि (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    फर्काऊ 0;

fail:
    यदि (hwmap) {
        av_buffer_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    फर्काऊ ret;
}

पूर्णाङ्क av_hwframe_map(AVFrame *dst, अचर AVFrame *src, पूर्णाङ्क flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    गणना AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    पूर्णाङ्क ret;

    यदि (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        यदि ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->data ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            यदि (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                फर्काऊ AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->data;
            फर्काऊ av_frame_replace(dst, hwmap->source);
        }
    }

    यदि (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;

        यदि (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            यदि (ret >= 0)
                फर्काऊ ret;
            अन्यथा यदि (ret != AVERROR(ENOSYS))
                गच्छ fail;
        }
    }

    यदि (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        यदि (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            यदि (ret >= 0)
                फर्काऊ ret;
            अन्यथा यदि (ret != AVERROR(ENOSYS))
                गच्छ fail;
        }
    }

    फर्काऊ AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_frames == रिक्त ||
               orig_dst_frames == dst->hw_frames_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_frames_ctx = रिक्त;
    av_frame_unref(dst);

    dst->hw_frames_ctx = orig_dst_frames;
    dst->format        = orig_dst_fmt;

    फर्काऊ ret;
}

पूर्णाङ्क av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  गणना AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  पूर्णाङ्क flags)
{
    AVBufferRef   *dst_ref = रिक्त;
    FFHWFramesContext *dsti = रिक्त;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->data;
    AVHWFramesContext *dst, *src = &srci->p;
    पूर्णाङ्क ret;

    यदि (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->data;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->data;

        यदि (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_buffer_ref(srci->source_frames);
            यदि (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                गच्छ fail;
            }
            फर्काऊ 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    यदि (!dst_ref) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->data;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->width     = src->width;
    dst->height    = src->height;

    dsti->source_frames = av_buffer_ref(source_frame_ctx);
    यदि (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    dsti->source_allocation_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_DIRECT);

    ret = AVERROR(ENOSYS);
    यदि (srci->hw_type->frames_derive_from)
        ret = srci->hw_type->frames_derive_from(dst, src, flags);
    यदि (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->frames_derive_to)
        ret = dsti->hw_type->frames_derive_to(dst, src, flags);
    यदि (ret == AVERROR(ENOSYS))
        ret = 0;
    यदि (ret)
        गच्छ fail;

    *derived_frame_ctx = dst_ref;
    फर्काऊ 0;

fail:
    यदि (dsti)
        av_buffer_unref(&dsti->source_frames);
    av_buffer_unref(&dst_ref);
    फर्काऊ ret;
}

पूर्णाङ्क ff_hwframe_map_replace(AVFrame *dst, अचर AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->data;
    फर्काऊ av_frame_replace(hwmap->source, src);
}
