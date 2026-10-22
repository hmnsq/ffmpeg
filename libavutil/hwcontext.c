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

#समावेश "config.h"

#समावेश "avassert.h"
#समावेश "buffer.h"
#समावेश "common.h"
#समावेश "frame_internal.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_internal.h"
#समावेश "imgutils.h"
#समावेश "log.h"
#समावेश "mem.h"
#समावेश "pixdesc.h"
#समावेश "pixfmt.h"

अटल स्थिर HWContextType * स्थिर hw_table[] = {
#अगर CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#पूर्ण_अगर
#अगर CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#पूर्ण_अगर
#अगर CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#पूर्ण_अगर
#अगर CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#पूर्ण_अगर
#अगर CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#पूर्ण_अगर
#अगर CONFIG_QSV
    &ff_hwcontext_type_qsv,
#पूर्ण_अगर
#अगर CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#पूर्ण_अगर
#अगर CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#पूर्ण_अगर
#अगर CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#पूर्ण_अगर
#अगर CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#पूर्ण_अगर
#अगर CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#पूर्ण_अगर
#अगर CONFIG_AMF
    &ff_hwcontext_type_amf,
#पूर्ण_अगर
#अगर CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#पूर्ण_अगर
    शून्य,
};

अटल स्थिर अक्षर *स्थिर hw_type_names[] = {
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

प्रकार काष्ठा FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    स्थिर HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *source_device;
} FFHWDeviceContext;

क्रमागत AVHWDeviceType av_hwdevice_find_type_by_name(स्थिर अक्षर *name)
{
    पूर्णांक type;
    क्रम (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        अगर (hw_type_names[type] && !म_भेद(hw_type_names[type], name))
            वापस type;
    }
    वापस AV_HWDEVICE_TYPE_NONE;
}

स्थिर अक्षर *av_hwdevice_get_type_name(क्रमागत AVHWDeviceType type)
{
    अगर (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        वापस hw_type_names[type];
    अन्यथा
        वापस शून्य;
}

क्रमागत AVHWDeviceType av_hwdevice_iterate_types(क्रमागत AVHWDeviceType पूर्व)
{
    क्रमागत AVHWDeviceType अग्र;
    पूर्णांक i, set = 0;
    क्रम (i = 0; hw_table[i]; i++) {
        अगर (पूर्व != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= पूर्व)
            जारी;
        अगर (!set || hw_table[i]->type < अग्र) {
            अग्र = hw_table[i]->type;
            set = 1;
        }
    }
    वापस set ? अग्र : AV_HWDEVICE_TYPE_NONE;
}

अटल स्थिर अक्षर *hwdevice_ctx_get_name(व्योम *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    वापस ctx->hw_type->name;
}

अटल स्थिर AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .item_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .version    = LIBAVUTIL_VERSION_INT,
};

अटल व्योम hwdevice_ctx_free(व्योम *opaque, uint8_t *तथ्य)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)तथ्य;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    अगर (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    अगर (ctx->मुक्त)
        ctx->मुक्त(ctx);

    av_बफर_unref(&ctxi->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(क्रमागत AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    स्थिर HWContextType *hw_type = शून्य;
    पूर्णांक i;

    क्रम (i = 0; hw_table[i]; i++) {
        अगर (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            अवरोध;
        }
    }
    अगर (!hw_type)
        वापस शून्य;

    ctxi = av_mallocz(माप(*ctxi));
    अगर (!ctxi)
        वापस शून्य;
    ctx = &ctxi->p;

    अगर (hw_type->device_hwctx_आकार) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_आकार);
        अगर (!ctx->hwctx)
            जाओ fail;
    }

    buf = av_बफर_create((uint8_t*)ctx, माप(*ctx),
                           hwdevice_ctx_free, शून्य,
                           AV_बफर_FLAG_READONLY);
    अगर (!buf)
        जाओ fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    वापस buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    वापस शून्य;
}

पूर्णांक av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->तथ्य;
    AVHWDeviceContext *ctx  = &ctxi->p;
    पूर्णांक ret = 0;

    अगर (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    वापस ret;
}

अटल स्थिर AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .item_name  = av_default_item_name,
    .version    = LIBAVUTIL_VERSION_INT,
};

अटल व्योम hwframe_ctx_free(व्योम *opaque, uint8_t *तथ्य)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)तथ्य;
    AVHWFramesContext *ctx  = &ctxi->p;

    अगर (ctxi->pool_internal)
        av_बफर_pool_uninit(&ctxi->pool_internal);

    av_बफर_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    अगर (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    अगर (ctx->मुक्त)
        ctx->मुक्त(ctx);

    av_बफर_unref(&ctxi->source_frames);

    av_बफर_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_in)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_in->तथ्य;
    स्थिर HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = शून्य;

    ctxi = av_mallocz(माप(*ctxi));
    अगर (!ctxi)
        वापस शून्य;
    ctx  = &ctxi->p;

    अगर (ff_mutex_init(&ctxi->transfer_pool_lock, शून्य)) {
        av_free(ctxi);
        वापस शून्य;
    }

    अगर (hw_type->frames_hwctx_आकार) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_आकार);
        अगर (!ctx->hwctx)
            जाओ fail;
    }

    device_ref = av_बफर_ref(device_ref_in);
    अगर (!device_ref)
        जाओ fail;

    buf = av_बफर_create((uint8_t*)ctx, माप(*ctx),
                           hwframe_ctx_free, शून्य,
                           AV_बफर_FLAG_READONLY);
    अगर (!buf)
        जाओ fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    वापस buf;

fail:
    av_बफर_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    वापस शून्य;
}

अटल पूर्णांक hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->तथ्य;
    AVFrame **frames;
    पूर्णांक i, ret = 0;

    frames = av_calloc(ctx->initial_pool_आकार, माप(*frames));
    अगर (!frames)
        वापस AVERROR(ENOMEM);

    क्रम (i = 0; i < ctx->initial_pool_आकार; i++) {
        frames[i] = av_frame_alloc();
        अगर (!frames[i])
            जाओ fail;

        ret = av_hwframe_get_बफर(ref, frames[i], 0);
        अगर (ret < 0)
            जाओ fail;
    }

fail:
    क्रम (i = 0; i < ctx->initial_pool_आकार; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    वापस ret;
}

पूर्णांक av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->तथ्य;
    AVHWFramesContext *ctx  = &ctxi->p;
    स्थिर क्रमागत AVPixelFormat *pix_fmt;
    पूर्णांक ret;

    अगर (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        वापस 0;
    }

    /* validate the pixel format */
    क्रम (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        अगर (*pix_fmt == ctx->format)
            अवरोध;
    }
    अगर (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        वापस AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_आकार(ctx->width, ctx->height, 0, ctx);
    अगर (ret < 0)
        वापस ret;

    /* format-specific init */
    अगर (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        अगर (ret < 0)
            वापस ret;
    }

    अगर (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    अगर (ctx->initial_pool_आकार > 0) {
        ret = hwframe_pool_prealloc(ref);
        अगर (ret < 0)
            वापस ret;
    }

    वापस 0;
}

पूर्णांक av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    क्रमागत AVHWFrameTransferDirection dir,
                                    क्रमागत AVPixelFormat **formats, पूर्णांक flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->तथ्य;

    अगर (!ctxi->hw_type->transfer_get_formats)
        वापस AVERROR(ENOSYS);

    वापस ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

अटल व्योम transfer_pool_free(व्योम *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_बफर_unref(&device_ref);
}

अटल AVBufferRef *transfer_बफर_alloc(व्योम *opaque, माप_प्रकार आकार)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = शून्य;

    ff_mutex_lock(&ctxi->transfer_pool_lock);
    अगर (ctxi->transfer_pool_आकार != आकार) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_बफर_alloc ?
                                  av_बफर_ref(ctxi->p.device_ref) : शून्य;

        av_बफर_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_बफर_pool_init2(आकार, device_ref,
                                 ctxi->hw_type->transfer_बफर_alloc,
                                 transfer_pool_free) :
            av_बफर_pool_init(आकार, शून्य);
        ctxi->transfer_pool_आकार = ctxi->transfer_pool ? आकार : 0;
        अगर (!ctxi->transfer_pool)
            av_बफर_unref(&device_ref);
    }
    अगर (ctxi->transfer_pool)
        buf = av_बफर_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    वापस buf ? buf : av_बफर_alloc(आकार);
}

पूर्णांक av_hwframe_get_transfer_बफर(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    वापस ff_frame_get_video_बफर(frame, 0, transfer_बफर_alloc,
                                     hwframe_ctx->तथ्य);
}

अटल पूर्णांक transfer_तथ्य_alloc(AVFrame *dst, स्थिर AVFrame *src, पूर्णांक flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    पूर्णांक ret = 0;

    अगर (!src->hw_frames_ctx)
        वापस AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->तथ्य;

    frame_tmp = av_frame_alloc();
    अगर (!frame_tmp)
        वापस AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    अगर (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } अन्यथा {
        क्रमागत AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        अगर (ret < 0)
            जाओ fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_बफर(src->hw_frames_ctx, frame_tmp);
    अगर (ret < 0)
        जाओ fail;

    ret = av_hwframe_transfer_तथ्य(frame_tmp, src, flags);
    अगर (ret < 0)
        जाओ fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    वापस ret;
}

पूर्णांक av_hwframe_transfer_तथ्य(AVFrame *dst, स्थिर AVFrame *src, पूर्णांक flags)
{
    पूर्णांक ret;

    अगर (!dst->buf[0])
        वापस transfer_तथ्य_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    अगर (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->तथ्य;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->तथ्य;

        अगर (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            वापस AVERROR(ENOSYS);
        }

        अगर (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            वापस AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        अगर (src_ctx->hw_type->transfer_तथ्य_from)
            ret = src_ctx->hw_type->transfer_तथ्य_from(&src_ctx->p, dst, src);
        अगर (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_तथ्य_to)
            ret = dst_ctx->hw_type->transfer_तथ्य_to(&dst_ctx->p, dst, src);
        अगर (ret < 0)
            वापस ret;
    } अन्यथा {
        अगर (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->तथ्य;

            अगर (!ctx->hw_type->transfer_तथ्य_from)
                वापस AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_तथ्य_from(&ctx->p, dst, src);
            अगर (ret < 0)
                वापस ret;
        } अन्यथा अगर (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->तथ्य;

            अगर (!ctx->hw_type->transfer_तथ्य_to)
                वापस AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_तथ्य_to(&ctx->p, dst, src);
            अगर (ret < 0)
                वापस ret;
        } अन्यथा {
            वापस AVERROR(ENOSYS);
        }
    }
    वापस 0;
}

पूर्णांक av_hwframe_get_बफर(AVBufferRef *hwframe_ref, AVFrame *frame, पूर्णांक flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->तथ्य;
    AVHWFramesContext *ctx  = &ctxi->p;
    पूर्णांक ret;

    अगर (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_बफर_ref(hwframe_ref);
        अगर (!frame->hw_frames_ctx)
            वापस AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        अगर (!src_frame)
            वापस AVERROR(ENOMEM);

        ret = av_hwframe_get_बफर(ctxi->source_frames,
                                    src_frame, 0);
        अगर (ret < 0) {
            av_frame_free(&src_frame);
            वापस ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        अगर (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            वापस ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        वापस 0;
    }

    अगर (!ctxi->hw_type->frames_get_बफर)
        वापस AVERROR(ENOSYS);

    अगर (!ctx->pool)
        वापस AVERROR(EINVAL);

    frame->hw_frames_ctx = av_बफर_ref(hwframe_ref);
    अगर (!frame->hw_frames_ctx)
        वापस AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_बफर(ctx, frame);
    अगर (ret < 0) {
        av_बफर_unref(&frame->hw_frames_ctx);
        वापस ret;
    }

    frame->extended_तथ्य = frame->तथ्य;

    वापस 0;
}

व्योम *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->तथ्य;
    स्थिर HWContextType  *hw_type = ctx->hw_type;

    अगर (hw_type->device_hwconfig_आकार == 0)
        वापस शून्य;

    वापस av_mallocz(hw_type->device_hwconfig_आकार);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           स्थिर व्योम *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->तथ्य;
    स्थिर HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    अगर (!hw_type->frames_get_constraints)
        वापस शून्य;

    constraints = av_mallocz(माप(*constraints));
    अगर (!constraints)
        वापस शून्य;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = पूर्णांक_उच्च;

    अगर (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        वापस constraints;
    } अन्यथा {
        av_hwframe_constraints_free(&constraints);
        वापस शून्य;
    }
}

व्योम av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    अगर (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

पूर्णांक av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, क्रमागत AVHWDeviceType type,
                           स्थिर अक्षर *device, AVDictionary *opts, पूर्णांक flags)
{
    AVBufferRef *device_ref = शून्य;
    FFHWDeviceContext *device_ctx;
    पूर्णांक ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    अगर (!device_ref) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->तथ्य;

    अगर (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        जाओ fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    अगर (ret < 0)
        जाओ fail;

    ret = av_hwdevice_ctx_init(device_ref);
    अगर (ret < 0)
        जाओ fail;

    *pdevice_ref = device_ref;
    वापस 0;
fail:
    av_बफर_unref(&device_ref);
    *pdevice_ref = शून्य;
    वापस ret;
}

पूर्णांक av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        क्रमागत AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, पूर्णांक flags)
{
    AVBufferRef *dst_ref = शून्य, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    पूर्णांक ret = 0;

    tmp_ref = src_ref;
    जबतक (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->तथ्य;
        अगर (tmp_ctx->p.type == type) {
            dst_ref = av_बफर_ref(tmp_ref);
            अगर (!dst_ref) {
                ret = AVERROR(ENOMEM);
                जाओ fail;
            }
            जाओ done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    अगर (!dst_ref) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->तथ्य;

    tmp_ref = src_ref;
    जबतक (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->तथ्य;
        अगर (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            अगर (ret == 0) {
                dst_ctx->source_device = av_बफर_ref(src_ref);
                अगर (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    जाओ fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                अगर (ret < 0)
                    जाओ fail;
                जाओ done;
            }
            अगर (ret != AVERROR(ENOSYS))
                जाओ fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    जाओ fail;

done:
    *dst_ref_ptr = dst_ref;
    वापस 0;

fail:
    av_बफर_unref(&dst_ref);
    *dst_ref_ptr = शून्य;
    वापस ret;
}

पूर्णांक av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   क्रमागत AVHWDeviceType type,
                                   AVBufferRef *src_ref, पूर्णांक flags)
{
    वापस av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               शून्य, flags);
}

अटल व्योम ff_hwframe_unmap(व्योम *opaque, uint8_t *तथ्य)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)तथ्य;
    AVHWFramesContext *ctx = opaque;

    अगर (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_बफर_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

पूर्णांक ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, स्थिर AVFrame *src,
                          व्योम (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          व्योम *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->तथ्य;
    HWMapDescriptor *hwmap;
    पूर्णांक ret;

    hwmap = av_mallocz(माप(*hwmap));
    अगर (!hwmap) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }

    hwmap->source = av_frame_alloc();
    अगर (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    अगर (ret < 0)
        जाओ fail;

    hwmap->hw_frames_ctx = av_बफर_ref(hwframe_ref);
    अगर (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_बफर_create((uint8_t*)hwmap, माप(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    अगर (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }

    वापस 0;

fail:
    अगर (hwmap) {
        av_बफर_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    वापस ret;
}

पूर्णांक av_hwframe_map(AVFrame *dst, स्थिर AVFrame *src, पूर्णांक flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    क्रमागत AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    पूर्णांक ret;

    अगर (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->तथ्य;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->तथ्य;

        अगर ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->तथ्य ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            अगर (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                वापस AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->तथ्य;
            वापस av_frame_replace(dst, hwmap->source);
        }
    }

    अगर (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->तथ्य;

        अगर (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            अगर (ret >= 0)
                वापस ret;
            अन्यथा अगर (ret != AVERROR(ENOSYS))
                जाओ fail;
        }
    }

    अगर (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->तथ्य;

        अगर (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            अगर (ret >= 0)
                वापस ret;
            अन्यथा अगर (ret != AVERROR(ENOSYS))
                जाओ fail;
        }
    }

    वापस AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_frames == शून्य ||
               orig_dst_frames == dst->hw_frames_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_frames_ctx = शून्य;
    av_frame_unref(dst);

    dst->hw_frames_ctx = orig_dst_frames;
    dst->format        = orig_dst_fmt;

    वापस ret;
}

पूर्णांक av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  क्रमागत AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  पूर्णांक flags)
{
    AVBufferRef   *dst_ref = शून्य;
    FFHWFramesContext *dsti = शून्य;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->तथ्य;
    AVHWFramesContext *dst, *src = &srci->p;
    पूर्णांक ret;

    अगर (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->तथ्य;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->तथ्य;

        अगर (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_बफर_ref(srci->source_frames);
            अगर (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                जाओ fail;
            }
            वापस 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    अगर (!dst_ref) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->तथ्य;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->width     = src->width;
    dst->height    = src->height;

    dsti->source_frames = av_बफर_ref(source_frame_ctx);
    अगर (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }

    dsti->source_allocation_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_DIRECT);

    ret = AVERROR(ENOSYS);
    अगर (srci->hw_type->frames_derive_from)
        ret = srci->hw_type->frames_derive_from(dst, src, flags);
    अगर (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->frames_derive_to)
        ret = dsti->hw_type->frames_derive_to(dst, src, flags);
    अगर (ret == AVERROR(ENOSYS))
        ret = 0;
    अगर (ret)
        जाओ fail;

    *derived_frame_ctx = dst_ref;
    वापस 0;

fail:
    अगर (dsti)
        av_बफर_unref(&dsti->source_frames);
    av_बफर_unref(&dst_ref);
    वापस ret;
}

पूर्णांक ff_hwframe_map_replace(AVFrame *dst, स्थिर AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->तथ्य;
    वापस av_frame_replace(hwmap->source, src);
}
