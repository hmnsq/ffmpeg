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

#অন্তর্ভাব "config.h"

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "buffer.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "frame_internal.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "hwcontext_internal.h"
#অন্তর্ভাব "imgutils.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "pixdesc.h"
#অন্তর্ভাব "pixfmt.h"

স্থির ধ্রুব HWContextType * ধ্রুব hw_table[] = {
#যদি CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#endif
#যদি CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#endif
#যদি CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#endif
#যদি CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#endif
#যদি CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#endif
#যদি CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#endif
#যদি CONFIG_QSV
    &ff_hwcontext_type_qsv,
#endif
#যদি CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#endif
#যদি CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#endif
#যদি CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#endif
#যদি CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#endif
#যদি CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#endif
#যদি CONFIG_AMF
    &ff_hwcontext_type_amf,
#endif
#যদি CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#endif
    রিক্ত,
};

স্থির ধ্রুব বর্ণ *ধ্রুব hw_type_names[] = {
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

প্রকারনির্দেশ সংরচনা FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    ধ্রুব HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *source_device;
} FFHWDeviceContext;

গণনা AVHWDeviceType av_hwdevice_find_type_by_name(ধ্রুব বর্ণ *name)
{
    পূর্ণাঙ্ক type;
    প্রতি (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        যদি (hw_type_names[type] && !strcmp(hw_type_names[type], name))
            প্রত্যাগম type;
    }
    প্রত্যাগম AV_HWDEVICE_TYPE_NONE;
}

ধ্রুব বর্ণ *av_hwdevice_get_type_name(গণনা AVHWDeviceType type)
{
    যদি (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        প্রত্যাগম hw_type_names[type];
    অন্যথা
        প্রত্যাগম রিক্ত;
}

গণনা AVHWDeviceType av_hwdevice_iterate_types(গণনা AVHWDeviceType prev)
{
    গণনা AVHWDeviceType next;
    পূর্ণাঙ্ক i, set = 0;
    প্রতি (i = 0; hw_table[i]; i++) {
        যদি (prev != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= prev)
            অনুবর্ত;
        যদি (!set || hw_table[i]->type < next) {
            next = hw_table[i]->type;
            set = 1;
        }
    }
    প্রত্যাগম set ? next : AV_HWDEVICE_TYPE_NONE;
}

স্থির ধ্রুব বর্ণ *hwdevice_ctx_get_name(শূন্য *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    প্রত্যাগম ctx->hw_type->name;
}

স্থির ধ্রুব AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .item_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .version    = LIBAVUTIL_VERSION_INT,
};

স্থির শূন্য hwdevice_ctx_free(শূন্য *opaque, uint8_t *data)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)data;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    যদি (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    যদি (ctx->মুক্ত)
        ctx->মুক্ত(ctx);

    av_buffer_unref(&ctxi->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(গণনা AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    ধ্রুব HWContextType *hw_type = রিক্ত;
    পূর্ণাঙ্ক i;

    প্রতি (i = 0; hw_table[i]; i++) {
        যদি (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            ভঙ্গ;
        }
    }
    যদি (!hw_type)
        প্রত্যাগম রিক্ত;

    ctxi = av_mallocz(পরিমাণ(*ctxi));
    যদি (!ctxi)
        প্রত্যাগম রিক্ত;
    ctx = &ctxi->p;

    যদি (hw_type->device_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_size);
        যদি (!ctx->hwctx)
            গচ্ছ fail;
    }

    buf = av_buffer_create((uint8_t*)ctx, পরিমাণ(*ctx),
                           hwdevice_ctx_free, রিক্ত,
                           AV_BUFFER_FLAG_READONLY);
    যদি (!buf)
        গচ্ছ fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    প্রত্যাগম buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    প্রত্যাগম রিক্ত;
}

পূর্ণাঙ্ক av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->data;
    AVHWDeviceContext *ctx  = &ctxi->p;
    পূর্ণাঙ্ক ret = 0;

    যদি (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    প্রত্যাগম ret;
}

স্থির ধ্রুব AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .item_name  = av_default_item_name,
    .version    = LIBAVUTIL_VERSION_INT,
};

স্থির শূন্য hwframe_ctx_free(শূন্য *opaque, uint8_t *data)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)data;
    AVHWFramesContext *ctx  = &ctxi->p;

    যদি (ctxi->pool_internal)
        av_buffer_pool_uninit(&ctxi->pool_internal);

    av_buffer_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    যদি (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    যদি (ctx->মুক্ত)
        ctx->মুক্ত(ctx);

    av_buffer_unref(&ctxi->source_frames);

    av_buffer_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_in)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_in->data;
    ধ্রুব HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = রিক্ত;

    ctxi = av_mallocz(পরিমাণ(*ctxi));
    যদি (!ctxi)
        প্রত্যাগম রিক্ত;
    ctx  = &ctxi->p;

    যদি (ff_mutex_init(&ctxi->transfer_pool_lock, রিক্ত)) {
        av_free(ctxi);
        প্রত্যাগম রিক্ত;
    }

    যদি (hw_type->frames_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_size);
        যদি (!ctx->hwctx)
            গচ্ছ fail;
    }

    device_ref = av_buffer_ref(device_ref_in);
    যদি (!device_ref)
        গচ্ছ fail;

    buf = av_buffer_create((uint8_t*)ctx, পরিমাণ(*ctx),
                           hwframe_ctx_free, রিক্ত,
                           AV_BUFFER_FLAG_READONLY);
    যদি (!buf)
        গচ্ছ fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    প্রত্যাগম buf;

fail:
    av_buffer_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    প্রত্যাগম রিক্ত;
}

স্থির পূর্ণাঙ্ক hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->data;
    AVFrame **frames;
    পূর্ণাঙ্ক i, ret = 0;

    frames = av_calloc(ctx->initial_pool_size, পরিমাণ(*frames));
    যদি (!frames)
        প্রত্যাগম AVERROR(ENOMEM);

    প্রতি (i = 0; i < ctx->initial_pool_size; i++) {
        frames[i] = av_frame_alloc();
        যদি (!frames[i])
            গচ্ছ fail;

        ret = av_hwframe_get_buffer(ref, frames[i], 0);
        যদি (ret < 0)
            গচ্ছ fail;
    }

fail:
    প্রতি (i = 0; i < ctx->initial_pool_size; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    ধ্রুব গণনা AVPixelFormat *pix_fmt;
    পূর্ণাঙ্ক ret;

    যদি (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        প্রত্যাগম 0;
    }

    /* validate the pixel format */
    প্রতি (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        যদি (*pix_fmt == ctx->format)
            ভঙ্গ;
    }
    যদি (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        প্রত্যাগম AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_size(ctx->width, ctx->height, 0, ctx);
    যদি (ret < 0)
        প্রত্যাগম ret;

    /* format-specific init */
    যদি (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        যদি (ret < 0)
            প্রত্যাগম ret;
    }

    যদি (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    যদি (ctx->initial_pool_size > 0) {
        ret = hwframe_pool_prealloc(ref);
        যদি (ret < 0)
            প্রত্যাগম ret;
    }

    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    গণনা AVHWFrameTransferDirection dir,
                                    গণনা AVPixelFormat **formats, পূর্ণাঙ্ক flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;

    যদি (!ctxi->hw_type->transfer_get_formats)
        প্রত্যাগম AVERROR(ENOSYS);

    প্রত্যাগম ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

স্থির শূন্য transfer_pool_free(শূন্য *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_buffer_unref(&device_ref);
}

স্থির AVBufferRef *transfer_buffer_alloc(শূন্য *opaque, size_t size)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = রিক্ত;

    ff_mutex_lock(&ctxi->transfer_pool_lock);
    যদি (ctxi->transfer_pool_size != size) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_buffer_alloc ?
                                  av_buffer_ref(ctxi->p.device_ref) : রিক্ত;

        av_buffer_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_buffer_pool_init2(size, device_ref,
                                 ctxi->hw_type->transfer_buffer_alloc,
                                 transfer_pool_free) :
            av_buffer_pool_init(size, রিক্ত);
        ctxi->transfer_pool_size = ctxi->transfer_pool ? size : 0;
        যদি (!ctxi->transfer_pool)
            av_buffer_unref(&device_ref);
    }
    যদি (ctxi->transfer_pool)
        buf = av_buffer_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    প্রত্যাগম buf ? buf : av_buffer_alloc(size);
}

পূর্ণাঙ্ক av_hwframe_get_transfer_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    প্রত্যাগম ff_frame_get_video_buffer(frame, 0, transfer_buffer_alloc,
                                     hwframe_ctx->data);
}

স্থির পূর্ণাঙ্ক transfer_data_alloc(AVFrame *dst, ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    পূর্ণাঙ্ক ret = 0;

    যদি (!src->hw_frames_ctx)
        প্রত্যাগম AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;

    frame_tmp = av_frame_alloc();
    যদি (!frame_tmp)
        প্রত্যাগম AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    যদি (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } অন্যথা {
        গণনা AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        যদি (ret < 0)
            গচ্ছ fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_buffer(src->hw_frames_ctx, frame_tmp);
    যদি (ret < 0)
        গচ্ছ fail;

    ret = av_hwframe_transfer_data(frame_tmp, src, flags);
    যদি (ret < 0)
        গচ্ছ fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_hwframe_transfer_data(AVFrame *dst, ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    পূর্ণাঙ্ক ret;

    যদি (!dst->buf[0])
        প্রত্যাগম transfer_data_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    যদি (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->data;

        যদি (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            প্রত্যাগম AVERROR(ENOSYS);
        }

        যদি (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            প্রত্যাগম AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        যদি (src_ctx->hw_type->transfer_data_from)
            ret = src_ctx->hw_type->transfer_data_from(&src_ctx->p, dst, src);
        যদি (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_data_to)
            ret = dst_ctx->hw_type->transfer_data_to(&dst_ctx->p, dst, src);
        যদি (ret < 0)
            প্রত্যাগম ret;
    } অন্যথা {
        যদি (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->data;

            যদি (!ctx->hw_type->transfer_data_from)
                প্রত্যাগম AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_from(&ctx->p, dst, src);
            যদি (ret < 0)
                প্রত্যাগম ret;
        } অন্যথা যদি (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->data;

            যদি (!ctx->hw_type->transfer_data_to)
                প্রত্যাগম AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_to(&ctx->p, dst, src);
            যদি (ret < 0)
                প্রত্যাগম ret;
        } অন্যথা {
            প্রত্যাগম AVERROR(ENOSYS);
        }
    }
    প্রত্যাগম 0;
}

পূর্ণাঙ্ক av_hwframe_get_buffer(AVBufferRef *hwframe_ref, AVFrame *frame, পূর্ণাঙ্ক flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    পূর্ণাঙ্ক ret;

    যদি (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
        যদি (!frame->hw_frames_ctx)
            প্রত্যাগম AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        যদি (!src_frame)
            প্রত্যাগম AVERROR(ENOMEM);

        ret = av_hwframe_get_buffer(ctxi->source_frames,
                                    src_frame, 0);
        যদি (ret < 0) {
            av_frame_free(&src_frame);
            প্রত্যাগম ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        যদি (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            প্রত্যাগম ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        প্রত্যাগম 0;
    }

    যদি (!ctxi->hw_type->frames_get_buffer)
        প্রত্যাগম AVERROR(ENOSYS);

    যদি (!ctx->pool)
        প্রত্যাগম AVERROR(EINVAL);

    frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    যদি (!frame->hw_frames_ctx)
        প্রত্যাগম AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_buffer(ctx, frame);
    যদি (ret < 0) {
        av_buffer_unref(&frame->hw_frames_ctx);
        প্রত্যাগম ret;
    }

    frame->extended_data = frame->data;

    প্রত্যাগম 0;
}

শূন্য *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    ধ্রুব HWContextType  *hw_type = ctx->hw_type;

    যদি (hw_type->device_hwconfig_size == 0)
        প্রত্যাগম রিক্ত;

    প্রত্যাগম av_mallocz(hw_type->device_hwconfig_size);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ধ্রুব শূন্য *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    ধ্রুব HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    যদি (!hw_type->frames_get_constraints)
        প্রত্যাগম রিক্ত;

    constraints = av_mallocz(পরিমাণ(*constraints));
    যদি (!constraints)
        প্রত্যাগম রিক্ত;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = INT_MAX;

    যদি (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        প্রত্যাগম constraints;
    } অন্যথা {
        av_hwframe_constraints_free(&constraints);
        প্রত্যাগম রিক্ত;
    }
}

শূন্য av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    যদি (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

পূর্ণাঙ্ক av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, গণনা AVHWDeviceType type,
                           ধ্রুব বর্ণ *device, AVDictionary *opts, পূর্ণাঙ্ক flags)
{
    AVBufferRef *device_ref = রিক্ত;
    FFHWDeviceContext *device_ctx;
    পূর্ণাঙ্ক ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    যদি (!device_ref) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->data;

    যদি (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        গচ্ছ fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    যদি (ret < 0)
        গচ্ছ fail;

    ret = av_hwdevice_ctx_init(device_ref);
    যদি (ret < 0)
        গচ্ছ fail;

    *pdevice_ref = device_ref;
    প্রত্যাগম 0;
fail:
    av_buffer_unref(&device_ref);
    *pdevice_ref = রিক্ত;
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        গণনা AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, পূর্ণাঙ্ক flags)
{
    AVBufferRef *dst_ref = রিক্ত, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    পূর্ণাঙ্ক ret = 0;

    tmp_ref = src_ref;
    যাবত্ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        যদি (tmp_ctx->p.type == type) {
            dst_ref = av_buffer_ref(tmp_ref);
            যদি (!dst_ref) {
                ret = AVERROR(ENOMEM);
                গচ্ছ fail;
            }
            গচ্ছ done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    যদি (!dst_ref) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->data;

    tmp_ref = src_ref;
    যাবত্ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        যদি (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            যদি (ret == 0) {
                dst_ctx->source_device = av_buffer_ref(src_ref);
                যদি (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    গচ্ছ fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                যদি (ret < 0)
                    গচ্ছ fail;
                গচ্ছ done;
            }
            যদি (ret != AVERROR(ENOSYS))
                গচ্ছ fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    গচ্ছ fail;

done:
    *dst_ref_ptr = dst_ref;
    প্রত্যাগম 0;

fail:
    av_buffer_unref(&dst_ref);
    *dst_ref_ptr = রিক্ত;
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   গণনা AVHWDeviceType type,
                                   AVBufferRef *src_ref, পূর্ণাঙ্ক flags)
{
    প্রত্যাগম av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               রিক্ত, flags);
}

স্থির শূন্য ff_hwframe_unmap(শূন্য *opaque, uint8_t *data)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)data;
    AVHWFramesContext *ctx = opaque;

    যদি (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_buffer_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

পূর্ণাঙ্ক ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ধ্রুব AVFrame *src,
                          শূন্য (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          শূন্য *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->data;
    HWMapDescriptor *hwmap;
    পূর্ণাঙ্ক ret;

    hwmap = av_mallocz(পরিমাণ(*hwmap));
    যদি (!hwmap) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    hwmap->source = av_frame_alloc();
    যদি (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    যদি (ret < 0)
        গচ্ছ fail;

    hwmap->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    যদি (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_buffer_create((uint8_t*)hwmap, পরিমাণ(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    যদি (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    প্রত্যাগম 0;

fail:
    যদি (hwmap) {
        av_buffer_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_hwframe_map(AVFrame *dst, ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    গণনা AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    পূর্ণাঙ্ক ret;

    যদি (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        যদি ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->data ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            যদি (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                প্রত্যাগম AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->data;
            প্রত্যাগম av_frame_replace(dst, hwmap->source);
        }
    }

    যদি (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;

        যদি (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            যদি (ret >= 0)
                প্রত্যাগম ret;
            অন্যথা যদি (ret != AVERROR(ENOSYS))
                গচ্ছ fail;
        }
    }

    যদি (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        যদি (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            যদি (ret >= 0)
                প্রত্যাগম ret;
            অন্যথা যদি (ret != AVERROR(ENOSYS))
                গচ্ছ fail;
        }
    }

    প্রত্যাগম AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_frames == রিক্ত ||
               orig_dst_frames == dst->hw_frames_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_frames_ctx = রিক্ত;
    av_frame_unref(dst);

    dst->hw_frames_ctx = orig_dst_frames;
    dst->format        = orig_dst_fmt;

    প্রত্যাগম ret;
}

পূর্ণাঙ্ক av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  গণনা AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  পূর্ণাঙ্ক flags)
{
    AVBufferRef   *dst_ref = রিক্ত;
    FFHWFramesContext *dsti = রিক্ত;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->data;
    AVHWFramesContext *dst, *src = &srci->p;
    পূর্ণাঙ্ক ret;

    যদি (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->data;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->data;

        যদি (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_buffer_ref(srci->source_frames);
            যদি (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                গচ্ছ fail;
            }
            প্রত্যাগম 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    যদি (!dst_ref) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->data;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->width     = src->width;
    dst->height    = src->height;

    dsti->source_frames = av_buffer_ref(source_frame_ctx);
    যদি (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    dsti->source_allocation_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_DIRECT);

    ret = AVERROR(ENOSYS);
    যদি (srci->hw_type->frames_derive_from)
        ret = srci->hw_type->frames_derive_from(dst, src, flags);
    যদি (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->frames_derive_to)
        ret = dsti->hw_type->frames_derive_to(dst, src, flags);
    যদি (ret == AVERROR(ENOSYS))
        ret = 0;
    যদি (ret)
        গচ্ছ fail;

    *derived_frame_ctx = dst_ref;
    প্রত্যাগম 0;

fail:
    যদি (dsti)
        av_buffer_unref(&dsti->source_frames);
    av_buffer_unref(&dst_ref);
    প্রত্যাগম ret;
}

পূর্ণাঙ্ক ff_hwframe_map_replace(AVFrame *dst, ধ্রুব AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->data;
    প্রত্যাগম av_frame_replace(hwmap->source, src);
}
