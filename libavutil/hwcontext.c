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

স্থির ধ্রুবক HWContextType * ধ্রুবক hw_table[] = {
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
    ফাঁকা,
};

স্থির ধ্রুবক অক্ষর *ধ্রুবক hw_type_names[] = {
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

প্রকারলেখ কাঠামো FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    ধ্রুবক HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *source_device;
} FFHWDeviceContext;

গণনা AVHWDeviceType av_hwdevice_find_type_by_name(ধ্রুবক অক্ষর *name)
{
    পূর্ণসংখ্যা type;
    জন্য (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        যদি (hw_type_names[type] && !strcmp(hw_type_names[type], name))
            ফেরত type;
    }
    ফেরত AV_HWDEVICE_TYPE_NONE;
}

ধ্রুবক অক্ষর *av_hwdevice_get_type_name(গণনা AVHWDeviceType type)
{
    যদি (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        ফেরত hw_type_names[type];
    অন্যথা
        ফেরত ফাঁকা;
}

গণনা AVHWDeviceType av_hwdevice_iterate_types(গণনা AVHWDeviceType পূর্ব)
{
    গণনা AVHWDeviceType পরবর্তী;
    পূর্ণসংখ্যা i, set = 0;
    জন্য (i = 0; hw_table[i]; i++) {
        যদি (পূর্ব != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= পূর্ব)
            চালু;
        যদি (!set || hw_table[i]->type < পরবর্তী) {
            পরবর্তী = hw_table[i]->type;
            set = 1;
        }
    }
    ফেরত set ? পরবর্তী : AV_HWDEVICE_TYPE_NONE;
}

স্থির ধ্রুবক অক্ষর *hwdevice_ctx_get_name(শূন্য *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    ফেরত ctx->hw_type->name;
}

স্থির ধ্রুবক AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .item_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .version    = LIBAVUTIL_VERSION_INT,
};

স্থির শূন্য hwdevice_ctx_free(শূন্য *opaque, uint8_t *তথ্য)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)তথ্য;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    যদি (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    যদি (ctx->মুক্ত)
        ctx->মুক্ত(ctx);

    av_বাফার_unref(&ctxi->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(গণনা AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    ধ্রুবক HWContextType *hw_type = ফাঁকা;
    পূর্ণসংখ্যা i;

    জন্য (i = 0; hw_table[i]; i++) {
        যদি (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            বিরতি;
        }
    }
    যদি (!hw_type)
        ফেরত ফাঁকা;

    ctxi = av_mallocz(আকার(*ctxi));
    যদি (!ctxi)
        ফেরত ফাঁকা;
    ctx = &ctxi->p;

    যদি (hw_type->device_hwctx_আকার) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_আকার);
        যদি (!ctx->hwctx)
            যাও fail;
    }

    buf = av_বাফার_create((uint8_t*)ctx, আকার(*ctx),
                           hwdevice_ctx_free, ফাঁকা,
                           AV_বাফার_FLAG_READONLY);
    যদি (!buf)
        যাও fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    ফেরত buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ফেরত ফাঁকা;
}

পূর্ণসংখ্যা av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->তথ্য;
    AVHWDeviceContext *ctx  = &ctxi->p;
    পূর্ণসংখ্যা ret = 0;

    যদি (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    ফেরত ret;
}

স্থির ধ্রুবক AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .item_name  = av_default_item_name,
    .version    = LIBAVUTIL_VERSION_INT,
};

স্থির শূন্য hwframe_ctx_free(শূন্য *opaque, uint8_t *তথ্য)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)তথ্য;
    AVHWFramesContext *ctx  = &ctxi->p;

    যদি (ctxi->pool_internal)
        av_বাফার_pool_uninit(&ctxi->pool_internal);

    av_বাফার_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    যদি (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    যদি (ctx->মুক্ত)
        ctx->মুক্ত(ctx);

    av_বাফার_unref(&ctxi->source_frames);

    av_বাফার_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_in)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_in->তথ্য;
    ধ্রুবক HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = ফাঁকা;

    ctxi = av_mallocz(আকার(*ctxi));
    যদি (!ctxi)
        ফেরত ফাঁকা;
    ctx  = &ctxi->p;

    যদি (ff_mutex_init(&ctxi->transfer_pool_lock, ফাঁকা)) {
        av_free(ctxi);
        ফেরত ফাঁকা;
    }

    যদি (hw_type->frames_hwctx_আকার) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_আকার);
        যদি (!ctx->hwctx)
            যাও fail;
    }

    device_ref = av_বাফার_ref(device_ref_in);
    যদি (!device_ref)
        যাও fail;

    buf = av_বাফার_create((uint8_t*)ctx, আকার(*ctx),
                           hwframe_ctx_free, ফাঁকা,
                           AV_বাফার_FLAG_READONLY);
    যদি (!buf)
        যাও fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    ফেরত buf;

fail:
    av_বাফার_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ফেরত ফাঁকা;
}

স্থির পূর্ণসংখ্যা hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->তথ্য;
    AVFrame **frames;
    পূর্ণসংখ্যা i, ret = 0;

    frames = av_calloc(ctx->initial_pool_আকার, আকার(*frames));
    যদি (!frames)
        ফেরত AVERROR(ENOMEM);

    জন্য (i = 0; i < ctx->initial_pool_আকার; i++) {
        frames[i] = av_frame_alloc();
        যদি (!frames[i])
            যাও fail;

        ret = av_hwframe_get_বাফার(ref, frames[i], 0);
        যদি (ret < 0)
            যাও fail;
    }

fail:
    জন্য (i = 0; i < ctx->initial_pool_আকার; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    ফেরত ret;
}

পূর্ণসংখ্যা av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->তথ্য;
    AVHWFramesContext *ctx  = &ctxi->p;
    ধ্রুবক গণনা AVPixelFormat *pix_fmt;
    পূর্ণসংখ্যা ret;

    যদি (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        ফেরত 0;
    }

    /* validate the pixel format */
    জন্য (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        যদি (*pix_fmt == ctx->format)
            বিরতি;
    }
    যদি (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        ফেরত AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_আকার(ctx->width, ctx->height, 0, ctx);
    যদি (ret < 0)
        ফেরত ret;

    /* format-specific init */
    যদি (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        যদি (ret < 0)
            ফেরত ret;
    }

    যদি (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    যদি (ctx->initial_pool_আকার > 0) {
        ret = hwframe_pool_prealloc(ref);
        যদি (ret < 0)
            ফেরত ret;
    }

    ফেরত 0;
}

পূর্ণসংখ্যা av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    গণনা AVHWFrameTransferDirection dir,
                                    গণনা AVPixelFormat **formats, পূর্ণসংখ্যা flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->তথ্য;

    যদি (!ctxi->hw_type->transfer_get_formats)
        ফেরত AVERROR(ENOSYS);

    ফেরত ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

স্থির শূন্য transfer_pool_free(শূন্য *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_বাফার_unref(&device_ref);
}

স্থির AVBufferRef *transfer_বাফার_alloc(শূন্য *opaque, size_t আকার_2)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = ফাঁকা;

    ff_mutex_lock(&ctxi->transfer_pool_lock);
    যদি (ctxi->transfer_pool_আকার != আকার_2) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_বাফার_alloc ?
                                  av_বাফার_ref(ctxi->p.device_ref) : ফাঁকা;

        av_বাফার_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_বাফার_pool_init2(আকার_2, device_ref,
                                 ctxi->hw_type->transfer_বাফার_alloc,
                                 transfer_pool_free) :
            av_বাফার_pool_init(আকার_2, ফাঁকা);
        ctxi->transfer_pool_আকার = ctxi->transfer_pool ? আকার_2 : 0;
        যদি (!ctxi->transfer_pool)
            av_বাফার_unref(&device_ref);
    }
    যদি (ctxi->transfer_pool)
        buf = av_বাফার_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    ফেরত buf ? buf : av_বাফার_alloc(আকার_2);
}

পূর্ণসংখ্যা av_hwframe_get_transfer_বাফার(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    ফেরত ff_frame_get_video_বাফার(frame, 0, transfer_বাফার_alloc,
                                     hwframe_ctx->তথ্য);
}

স্থির পূর্ণসংখ্যা transfer_তথ্য_alloc(AVFrame *dst, ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    পূর্ণসংখ্যা ret = 0;

    যদি (!src->hw_frames_ctx)
        ফেরত AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->তথ্য;

    frame_tmp = av_frame_alloc();
    যদি (!frame_tmp)
        ফেরত AVERROR(ENOMEM);

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
            যাও fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_বাফার(src->hw_frames_ctx, frame_tmp);
    যদি (ret < 0)
        যাও fail;

    ret = av_hwframe_transfer_তথ্য(frame_tmp, src, flags);
    যদি (ret < 0)
        যাও fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    ফেরত ret;
}

পূর্ণসংখ্যা av_hwframe_transfer_তথ্য(AVFrame *dst, ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    পূর্ণসংখ্যা ret;

    যদি (!dst->buf[0])
        ফেরত transfer_তথ্য_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    যদি (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->তথ্য;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->তথ্য;

        যদি (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            ফেরত AVERROR(ENOSYS);
        }

        যদি (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            ফেরত AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        যদি (src_ctx->hw_type->transfer_তথ্য_from)
            ret = src_ctx->hw_type->transfer_তথ্য_from(&src_ctx->p, dst, src);
        যদি (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_তথ্য_to)
            ret = dst_ctx->hw_type->transfer_তথ্য_to(&dst_ctx->p, dst, src);
        যদি (ret < 0)
            ফেরত ret;
    } অন্যথা {
        যদি (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->তথ্য;

            যদি (!ctx->hw_type->transfer_তথ্য_from)
                ফেরত AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_তথ্য_from(&ctx->p, dst, src);
            যদি (ret < 0)
                ফেরত ret;
        } অন্যথা যদি (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->তথ্য;

            যদি (!ctx->hw_type->transfer_তথ্য_to)
                ফেরত AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_তথ্য_to(&ctx->p, dst, src);
            যদি (ret < 0)
                ফেরত ret;
        } অন্যথা {
            ফেরত AVERROR(ENOSYS);
        }
    }
    ফেরত 0;
}

পূর্ণসংখ্যা av_hwframe_get_বাফার(AVBufferRef *hwframe_ref, AVFrame *frame, পূর্ণসংখ্যা flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->তথ্য;
    AVHWFramesContext *ctx  = &ctxi->p;
    পূর্ণসংখ্যা ret;

    যদি (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_বাফার_ref(hwframe_ref);
        যদি (!frame->hw_frames_ctx)
            ফেরত AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        যদি (!src_frame)
            ফেরত AVERROR(ENOMEM);

        ret = av_hwframe_get_বাফার(ctxi->source_frames,
                                    src_frame, 0);
        যদি (ret < 0) {
            av_frame_free(&src_frame);
            ফেরত ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        যদি (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            ফেরত ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        ফেরত 0;
    }

    যদি (!ctxi->hw_type->frames_get_বাফার)
        ফেরত AVERROR(ENOSYS);

    যদি (!ctx->pool)
        ফেরত AVERROR(EINVAL);

    frame->hw_frames_ctx = av_বাফার_ref(hwframe_ref);
    যদি (!frame->hw_frames_ctx)
        ফেরত AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_বাফার(ctx, frame);
    যদি (ret < 0) {
        av_বাফার_unref(&frame->hw_frames_ctx);
        ফেরত ret;
    }

    frame->extended_তথ্য = frame->তথ্য;

    ফেরত 0;
}

শূন্য *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->তথ্য;
    ধ্রুবক HWContextType  *hw_type = ctx->hw_type;

    যদি (hw_type->device_hwconfig_আকার == 0)
        ফেরত ফাঁকা;

    ফেরত av_mallocz(hw_type->device_hwconfig_আকার);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ধ্রুবক শূন্য *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->তথ্য;
    ধ্রুবক HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    যদি (!hw_type->frames_get_constraints)
        ফেরত ফাঁকা;

    constraints = av_mallocz(আকার(*constraints));
    যদি (!constraints)
        ফেরত ফাঁকা;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = INT_MAX;

    যদি (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        ফেরত constraints;
    } অন্যথা {
        av_hwframe_constraints_free(&constraints);
        ফেরত ফাঁকা;
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

পূর্ণসংখ্যা av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, গণনা AVHWDeviceType type,
                           ধ্রুবক অক্ষর *device, AVDictionary *opts, পূর্ণসংখ্যা flags)
{
    AVBufferRef *device_ref = ফাঁকা;
    FFHWDeviceContext *device_ctx;
    পূর্ণসংখ্যা ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    যদি (!device_ref) {
        ret = AVERROR(ENOMEM);
        যাও fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->তথ্য;

    যদি (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        যাও fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    যদি (ret < 0)
        যাও fail;

    ret = av_hwdevice_ctx_init(device_ref);
    যদি (ret < 0)
        যাও fail;

    *pdevice_ref = device_ref;
    ফেরত 0;
fail:
    av_বাফার_unref(&device_ref);
    *pdevice_ref = ফাঁকা;
    ফেরত ret;
}

পূর্ণসংখ্যা av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        গণনা AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, পূর্ণসংখ্যা flags)
{
    AVBufferRef *dst_ref = ফাঁকা, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    পূর্ণসংখ্যা ret = 0;

    tmp_ref = src_ref;
    যখন (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->তথ্য;
        যদি (tmp_ctx->p.type == type) {
            dst_ref = av_বাফার_ref(tmp_ref);
            যদি (!dst_ref) {
                ret = AVERROR(ENOMEM);
                যাও fail;
            }
            যাও done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    যদি (!dst_ref) {
        ret = AVERROR(ENOMEM);
        যাও fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->তথ্য;

    tmp_ref = src_ref;
    যখন (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->তথ্য;
        যদি (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            যদি (ret == 0) {
                dst_ctx->source_device = av_বাফার_ref(src_ref);
                যদি (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    যাও fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                যদি (ret < 0)
                    যাও fail;
                যাও done;
            }
            যদি (ret != AVERROR(ENOSYS))
                যাও fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    যাও fail;

done:
    *dst_ref_ptr = dst_ref;
    ফেরত 0;

fail:
    av_বাফার_unref(&dst_ref);
    *dst_ref_ptr = ফাঁকা;
    ফেরত ret;
}

পূর্ণসংখ্যা av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   গণনা AVHWDeviceType type,
                                   AVBufferRef *src_ref, পূর্ণসংখ্যা flags)
{
    ফেরত av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               ফাঁকা, flags);
}

স্থির শূন্য ff_hwframe_unmap(শূন্য *opaque, uint8_t *তথ্য)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)তথ্য;
    AVHWFramesContext *ctx = opaque;

    যদি (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_বাফার_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

পূর্ণসংখ্যা ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ধ্রুবক AVFrame *src,
                          শূন্য (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          শূন্য *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->তথ্য;
    HWMapDescriptor *hwmap;
    পূর্ণসংখ্যা ret;

    hwmap = av_mallocz(আকার(*hwmap));
    যদি (!hwmap) {
        ret = AVERROR(ENOMEM);
        যাও fail;
    }

    hwmap->source = av_frame_alloc();
    যদি (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        যাও fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    যদি (ret < 0)
        যাও fail;

    hwmap->hw_frames_ctx = av_বাফার_ref(hwframe_ref);
    যদি (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        যাও fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_বাফার_create((uint8_t*)hwmap, আকার(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    যদি (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        যাও fail;
    }

    ফেরত 0;

fail:
    যদি (hwmap) {
        av_বাফার_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    ফেরত ret;
}

পূর্ণসংখ্যা av_hwframe_map(AVFrame *dst, ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    গণনা AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    পূর্ণসংখ্যা ret;

    যদি (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->তথ্য;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->তথ্য;

        যদি ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->তথ্য ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            যদি (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                ফেরত AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->তথ্য;
            ফেরত av_frame_replace(dst, hwmap->source);
        }
    }

    যদি (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->তথ্য;

        যদি (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            যদি (ret >= 0)
                ফেরত ret;
            অন্যথা যদি (ret != AVERROR(ENOSYS))
                যাও fail;
        }
    }

    যদি (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->তথ্য;

        যদি (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            যদি (ret >= 0)
                ফেরত ret;
            অন্যথা যদি (ret != AVERROR(ENOSYS))
                যাও fail;
        }
    }

    ফেরত AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_frames == ফাঁকা ||
               orig_dst_frames == dst->hw_frames_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_frames_ctx = ফাঁকা;
    av_frame_unref(dst);

    dst->hw_frames_ctx = orig_dst_frames;
    dst->format        = orig_dst_fmt;

    ফেরত ret;
}

পূর্ণসংখ্যা av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  গণনা AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  পূর্ণসংখ্যা flags)
{
    AVBufferRef   *dst_ref = ফাঁকা;
    FFHWFramesContext *dsti = ফাঁকা;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->তথ্য;
    AVHWFramesContext *dst, *src = &srci->p;
    পূর্ণসংখ্যা ret;

    যদি (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->তথ্য;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->তথ্য;

        যদি (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_বাফার_ref(srci->source_frames);
            যদি (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                যাও fail;
            }
            ফেরত 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    যদি (!dst_ref) {
        ret = AVERROR(ENOMEM);
        যাও fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->তথ্য;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->width     = src->width;
    dst->height    = src->height;

    dsti->source_frames = av_বাফার_ref(source_frame_ctx);
    যদি (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        যাও fail;
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
        যাও fail;

    *derived_frame_ctx = dst_ref;
    ফেরত 0;

fail:
    যদি (dsti)
        av_বাফার_unref(&dsti->source_frames);
    av_বাফার_unref(&dst_ref);
    ফেরত ret;
}

পূর্ণসংখ্যা ff_hwframe_map_replace(AVFrame *dst, ধ্রুবক AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->তথ্য;
    ফেরত av_frame_replace(hwmap->source, src);
}
