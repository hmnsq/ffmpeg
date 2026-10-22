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

#அந்தர்பாவ "config.h"

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "buffer.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "frame_internal.h"
#அந்தர்பாவ "hwcontext.h"
#அந்தர்பாவ "hwcontext_internal.h"
#அந்தர்பாவ "imgutils.h"
#அந்தர்பாவ "log.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "pixdesc.h"
#அந்தர்பாவ "pixfmt.h"

நிலையான மாறிலி HWContextType * மாறிலி hw_table[] = {
#எனில் CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#endif
#எனில் CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#endif
#எனில் CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#endif
#எனில் CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#endif
#எனில் CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#endif
#எனில் CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#endif
#எனில் CONFIG_QSV
    &ff_hwcontext_type_qsv,
#endif
#எனில் CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#endif
#எனில் CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#endif
#எனில் CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#endif
#எனில் CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#endif
#எனில் CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#endif
#எனில் CONFIG_AMF
    &ff_hwcontext_type_amf,
#endif
#எனில் CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#endif
    வெற்று,
};

நிலையான மாறிலி எழுத்து *மாறிலி hw_type_names[] = {
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

வகைவரை கட்டமைப்பு FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    மாறிலி HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *source_device;
} FFHWDeviceContext;

எண்ணிக்கை AVHWDeviceType av_hwdevice_find_type_by_name(மாறிலி எழுத்து *name)
{
    முழு type;
    க்கு (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        எனில் (hw_type_names[type] && !strcmp(hw_type_names[type], name))
            திரும்பு type;
    }
    திரும்பு AV_HWDEVICE_TYPE_NONE;
}

மாறிலி எழுத்து *av_hwdevice_get_type_name(எண்ணிக்கை AVHWDeviceType type)
{
    எனில் (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        திரும்பு hw_type_names[type];
    இல்லையெனில்
        திரும்பு வெற்று;
}

எண்ணிக்கை AVHWDeviceType av_hwdevice_iterate_types(எண்ணிக்கை AVHWDeviceType prev)
{
    எண்ணிக்கை AVHWDeviceType next;
    முழு i, set = 0;
    க்கு (i = 0; hw_table[i]; i++) {
        எனில் (prev != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= prev)
            தொடர்;
        எனில் (!set || hw_table[i]->type < next) {
            next = hw_table[i]->type;
            set = 1;
        }
    }
    திரும்பு set ? next : AV_HWDEVICE_TYPE_NONE;
}

நிலையான மாறிலி எழுத்து *hwdevice_ctx_get_name(வெறுமை *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    திரும்பு ctx->hw_type->name;
}

நிலையான மாறிலி AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .item_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .version    = LIBAVUTIL_VERSION_INT,
};

நிலையான வெறுமை hwdevice_ctx_free(வெறுமை *opaque, uint8_t *data)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)data;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    எனில் (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    எனில் (ctx->விடுவி)
        ctx->விடுவி(ctx);

    av_buffer_unref(&ctxi->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(எண்ணிக்கை AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    மாறிலி HWContextType *hw_type = வெற்று;
    முழு i;

    க்கு (i = 0; hw_table[i]; i++) {
        எனில் (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            நிறுத்து;
        }
    }
    எனில் (!hw_type)
        திரும்பு வெற்று;

    ctxi = av_mallocz(அளவு(*ctxi));
    எனில் (!ctxi)
        திரும்பு வெற்று;
    ctx = &ctxi->p;

    எனில் (hw_type->device_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_size);
        எனில் (!ctx->hwctx)
            செல் fail;
    }

    buf = av_buffer_create((uint8_t*)ctx, அளவு(*ctx),
                           hwdevice_ctx_free, வெற்று,
                           AV_BUFFER_FLAG_READONLY);
    எனில் (!buf)
        செல் fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    திரும்பு buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    திரும்பு வெற்று;
}

முழு av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->data;
    AVHWDeviceContext *ctx  = &ctxi->p;
    முழு ret = 0;

    எனில் (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    திரும்பு ret;
}

நிலையான மாறிலி AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .item_name  = av_default_item_name,
    .version    = LIBAVUTIL_VERSION_INT,
};

நிலையான வெறுமை hwframe_ctx_free(வெறுமை *opaque, uint8_t *data)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)data;
    AVHWFramesContext *ctx  = &ctxi->p;

    எனில் (ctxi->pool_internal)
        av_buffer_pool_uninit(&ctxi->pool_internal);

    av_buffer_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    எனில் (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    எனில் (ctx->விடுவி)
        ctx->விடுவி(ctx);

    av_buffer_unref(&ctxi->source_frames);

    av_buffer_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_in)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_in->data;
    மாறிலி HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = வெற்று;

    ctxi = av_mallocz(அளவு(*ctxi));
    எனில் (!ctxi)
        திரும்பு வெற்று;
    ctx  = &ctxi->p;

    எனில் (ff_mutex_init(&ctxi->transfer_pool_lock, வெற்று)) {
        av_free(ctxi);
        திரும்பு வெற்று;
    }

    எனில் (hw_type->frames_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_size);
        எனில் (!ctx->hwctx)
            செல் fail;
    }

    device_ref = av_buffer_ref(device_ref_in);
    எனில் (!device_ref)
        செல் fail;

    buf = av_buffer_create((uint8_t*)ctx, அளவு(*ctx),
                           hwframe_ctx_free, வெற்று,
                           AV_BUFFER_FLAG_READONLY);
    எனில் (!buf)
        செல் fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    திரும்பு buf;

fail:
    av_buffer_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    திரும்பு வெற்று;
}

நிலையான முழு hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->data;
    AVFrame **frames;
    முழு i, ret = 0;

    frames = av_calloc(ctx->initial_pool_size, அளவு(*frames));
    எனில் (!frames)
        திரும்பு AVERROR(ENOMEM);

    க்கு (i = 0; i < ctx->initial_pool_size; i++) {
        frames[i] = av_frame_alloc();
        எனில் (!frames[i])
            செல் fail;

        ret = av_hwframe_get_buffer(ref, frames[i], 0);
        எனில் (ret < 0)
            செல் fail;
    }

fail:
    க்கு (i = 0; i < ctx->initial_pool_size; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    திரும்பு ret;
}

முழு av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    மாறிலி எண்ணிக்கை AVPixelFormat *pix_fmt;
    முழு ret;

    எனில் (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        திரும்பு 0;
    }

    /* validate the pixel format */
    க்கு (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        எனில் (*pix_fmt == ctx->format)
            நிறுத்து;
    }
    எனில் (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        திரும்பு AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_size(ctx->width, ctx->height, 0, ctx);
    எனில் (ret < 0)
        திரும்பு ret;

    /* format-specific init */
    எனில் (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        எனில் (ret < 0)
            திரும்பு ret;
    }

    எனில் (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    எனில் (ctx->initial_pool_size > 0) {
        ret = hwframe_pool_prealloc(ref);
        எனில் (ret < 0)
            திரும்பு ret;
    }

    திரும்பு 0;
}

முழு av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    எண்ணிக்கை AVHWFrameTransferDirection dir,
                                    எண்ணிக்கை AVPixelFormat **formats, முழு flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;

    எனில் (!ctxi->hw_type->transfer_get_formats)
        திரும்பு AVERROR(ENOSYS);

    திரும்பு ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

நிலையான வெறுமை transfer_pool_free(வெறுமை *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_buffer_unref(&device_ref);
}

நிலையான AVBufferRef *transfer_buffer_alloc(வெறுமை *opaque, size_t size)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = வெற்று;

    ff_mutex_lock(&ctxi->transfer_pool_lock);
    எனில் (ctxi->transfer_pool_size != size) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_buffer_alloc ?
                                  av_buffer_ref(ctxi->p.device_ref) : வெற்று;

        av_buffer_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_buffer_pool_init2(size, device_ref,
                                 ctxi->hw_type->transfer_buffer_alloc,
                                 transfer_pool_free) :
            av_buffer_pool_init(size, வெற்று);
        ctxi->transfer_pool_size = ctxi->transfer_pool ? size : 0;
        எனில் (!ctxi->transfer_pool)
            av_buffer_unref(&device_ref);
    }
    எனில் (ctxi->transfer_pool)
        buf = av_buffer_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    திரும்பு buf ? buf : av_buffer_alloc(size);
}

முழு av_hwframe_get_transfer_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    திரும்பு ff_frame_get_video_buffer(frame, 0, transfer_buffer_alloc,
                                     hwframe_ctx->data);
}

நிலையான முழு transfer_data_alloc(AVFrame *dst, மாறிலி AVFrame *src, முழு flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    முழு ret = 0;

    எனில் (!src->hw_frames_ctx)
        திரும்பு AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;

    frame_tmp = av_frame_alloc();
    எனில் (!frame_tmp)
        திரும்பு AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    எனில் (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } இல்லையெனில் {
        எண்ணிக்கை AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        எனில் (ret < 0)
            செல் fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_buffer(src->hw_frames_ctx, frame_tmp);
    எனில் (ret < 0)
        செல் fail;

    ret = av_hwframe_transfer_data(frame_tmp, src, flags);
    எனில் (ret < 0)
        செல் fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    திரும்பு ret;
}

முழு av_hwframe_transfer_data(AVFrame *dst, மாறிலி AVFrame *src, முழு flags)
{
    முழு ret;

    எனில் (!dst->buf[0])
        திரும்பு transfer_data_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    எனில் (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->data;

        எனில் (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            திரும்பு AVERROR(ENOSYS);
        }

        எனில் (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            திரும்பு AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        எனில் (src_ctx->hw_type->transfer_data_from)
            ret = src_ctx->hw_type->transfer_data_from(&src_ctx->p, dst, src);
        எனில் (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_data_to)
            ret = dst_ctx->hw_type->transfer_data_to(&dst_ctx->p, dst, src);
        எனில் (ret < 0)
            திரும்பு ret;
    } இல்லையெனில் {
        எனில் (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->data;

            எனில் (!ctx->hw_type->transfer_data_from)
                திரும்பு AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_from(&ctx->p, dst, src);
            எனில் (ret < 0)
                திரும்பு ret;
        } இல்லையெனில் எனில் (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->data;

            எனில் (!ctx->hw_type->transfer_data_to)
                திரும்பு AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_to(&ctx->p, dst, src);
            எனில் (ret < 0)
                திரும்பு ret;
        } இல்லையெனில் {
            திரும்பு AVERROR(ENOSYS);
        }
    }
    திரும்பு 0;
}

முழு av_hwframe_get_buffer(AVBufferRef *hwframe_ref, AVFrame *frame, முழு flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    முழு ret;

    எனில் (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
        எனில் (!frame->hw_frames_ctx)
            திரும்பு AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        எனில் (!src_frame)
            திரும்பு AVERROR(ENOMEM);

        ret = av_hwframe_get_buffer(ctxi->source_frames,
                                    src_frame, 0);
        எனில் (ret < 0) {
            av_frame_free(&src_frame);
            திரும்பு ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        எனில் (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            திரும்பு ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        திரும்பு 0;
    }

    எனில் (!ctxi->hw_type->frames_get_buffer)
        திரும்பு AVERROR(ENOSYS);

    எனில் (!ctx->pool)
        திரும்பு AVERROR(EINVAL);

    frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    எனில் (!frame->hw_frames_ctx)
        திரும்பு AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_buffer(ctx, frame);
    எனில் (ret < 0) {
        av_buffer_unref(&frame->hw_frames_ctx);
        திரும்பு ret;
    }

    frame->extended_data = frame->data;

    திரும்பு 0;
}

வெறுமை *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    மாறிலி HWContextType  *hw_type = ctx->hw_type;

    எனில் (hw_type->device_hwconfig_size == 0)
        திரும்பு வெற்று;

    திரும்பு av_mallocz(hw_type->device_hwconfig_size);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           மாறிலி வெறுமை *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    மாறிலி HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    எனில் (!hw_type->frames_get_constraints)
        திரும்பு வெற்று;

    constraints = av_mallocz(அளவு(*constraints));
    எனில் (!constraints)
        திரும்பு வெற்று;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = INT_MAX;

    எனில் (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        திரும்பு constraints;
    } இல்லையெனில் {
        av_hwframe_constraints_free(&constraints);
        திரும்பு வெற்று;
    }
}

வெறுமை av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    எனில் (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

முழு av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, எண்ணிக்கை AVHWDeviceType type,
                           மாறிலி எழுத்து *device, AVDictionary *opts, முழு flags)
{
    AVBufferRef *device_ref = வெற்று;
    FFHWDeviceContext *device_ctx;
    முழு ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    எனில் (!device_ref) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->data;

    எனில் (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        செல் fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    எனில் (ret < 0)
        செல் fail;

    ret = av_hwdevice_ctx_init(device_ref);
    எனில் (ret < 0)
        செல் fail;

    *pdevice_ref = device_ref;
    திரும்பு 0;
fail:
    av_buffer_unref(&device_ref);
    *pdevice_ref = வெற்று;
    திரும்பு ret;
}

முழு av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        எண்ணிக்கை AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, முழு flags)
{
    AVBufferRef *dst_ref = வெற்று, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    முழு ret = 0;

    tmp_ref = src_ref;
    போது (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        எனில் (tmp_ctx->p.type == type) {
            dst_ref = av_buffer_ref(tmp_ref);
            எனில் (!dst_ref) {
                ret = AVERROR(ENOMEM);
                செல் fail;
            }
            செல் done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    எனில் (!dst_ref) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->data;

    tmp_ref = src_ref;
    போது (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        எனில் (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            எனில் (ret == 0) {
                dst_ctx->source_device = av_buffer_ref(src_ref);
                எனில் (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    செல் fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                எனில் (ret < 0)
                    செல் fail;
                செல் done;
            }
            எனில் (ret != AVERROR(ENOSYS))
                செல் fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    செல் fail;

done:
    *dst_ref_ptr = dst_ref;
    திரும்பு 0;

fail:
    av_buffer_unref(&dst_ref);
    *dst_ref_ptr = வெற்று;
    திரும்பு ret;
}

முழு av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   எண்ணிக்கை AVHWDeviceType type,
                                   AVBufferRef *src_ref, முழு flags)
{
    திரும்பு av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               வெற்று, flags);
}

நிலையான வெறுமை ff_hwframe_unmap(வெறுமை *opaque, uint8_t *data)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)data;
    AVHWFramesContext *ctx = opaque;

    எனில் (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_buffer_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

முழு ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, மாறிலி AVFrame *src,
                          வெறுமை (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          வெறுமை *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->data;
    HWMapDescriptor *hwmap;
    முழு ret;

    hwmap = av_mallocz(அளவு(*hwmap));
    எனில் (!hwmap) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }

    hwmap->source = av_frame_alloc();
    எனில் (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    எனில் (ret < 0)
        செல் fail;

    hwmap->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    எனில் (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_buffer_create((uint8_t*)hwmap, அளவு(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    எனில் (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }

    திரும்பு 0;

fail:
    எனில் (hwmap) {
        av_buffer_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    திரும்பு ret;
}

முழு av_hwframe_map(AVFrame *dst, மாறிலி AVFrame *src, முழு flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    எண்ணிக்கை AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    முழு ret;

    எனில் (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        எனில் ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->data ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            எனில் (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                திரும்பு AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->data;
            திரும்பு av_frame_replace(dst, hwmap->source);
        }
    }

    எனில் (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;

        எனில் (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            எனில் (ret >= 0)
                திரும்பு ret;
            இல்லையெனில் எனில் (ret != AVERROR(ENOSYS))
                செல் fail;
        }
    }

    எனில் (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        எனில் (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            எனில் (ret >= 0)
                திரும்பு ret;
            இல்லையெனில் எனில் (ret != AVERROR(ENOSYS))
                செல் fail;
        }
    }

    திரும்பு AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_frames == வெற்று ||
               orig_dst_frames == dst->hw_frames_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_frames_ctx = வெற்று;
    av_frame_unref(dst);

    dst->hw_frames_ctx = orig_dst_frames;
    dst->format        = orig_dst_fmt;

    திரும்பு ret;
}

முழு av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  எண்ணிக்கை AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  முழு flags)
{
    AVBufferRef   *dst_ref = வெற்று;
    FFHWFramesContext *dsti = வெற்று;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->data;
    AVHWFramesContext *dst, *src = &srci->p;
    முழு ret;

    எனில் (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->data;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->data;

        எனில் (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_buffer_ref(srci->source_frames);
            எனில் (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                செல் fail;
            }
            திரும்பு 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    எனில் (!dst_ref) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->data;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->width     = src->width;
    dst->height    = src->height;

    dsti->source_frames = av_buffer_ref(source_frame_ctx);
    எனில் (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }

    dsti->source_allocation_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_DIRECT);

    ret = AVERROR(ENOSYS);
    எனில் (srci->hw_type->frames_derive_from)
        ret = srci->hw_type->frames_derive_from(dst, src, flags);
    எனில் (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->frames_derive_to)
        ret = dsti->hw_type->frames_derive_to(dst, src, flags);
    எனில் (ret == AVERROR(ENOSYS))
        ret = 0;
    எனில் (ret)
        செல் fail;

    *derived_frame_ctx = dst_ref;
    திரும்பு 0;

fail:
    எனில் (dsti)
        av_buffer_unref(&dsti->source_frames);
    av_buffer_unref(&dst_ref);
    திரும்பு ret;
}

முழு ff_hwframe_map_replace(AVFrame *dst, மாறிலி AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->data;
    திரும்பு av_frame_replace(hwmap->source, src);
}
