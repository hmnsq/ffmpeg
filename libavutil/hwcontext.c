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

स्थिर ध्रुव HWContextType * ध्रुव hw_सारणी[] = {
#यदि CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#यदि_अन्तः
#यदि CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#यदि_अन्तः
#यदि CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#यदि_अन्तः
#यदि CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#यदि_अन्तः
#यदि CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#यदि_अन्तः
#यदि CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#यदि_अन्तः
#यदि CONFIG_QSV
    &ff_hwcontext_type_qsv,
#यदि_अन्तः
#यदि CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#यदि_अन्तः
#यदि CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#यदि_अन्तः
#यदि CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#यदि_अन्तः
#यदि CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#यदि_अन्तः
#यदि CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#यदि_अन्तः
#यदि CONFIG_AMF
    &ff_hwcontext_type_amf,
#यदि_अन्तः
#यदि CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#यदि_अन्तः
    रिक्त,
};

स्थिर ध्रुव वर्ण *ध्रुव hw_type_नामानि[] = {
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

    ध्रुव HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *source_device;
} FFHWDeviceContext;

गणना AVHWDeviceType av_hwdevice_find_type_by_name(ध्रुव वर्ण *name)
{
    पूर्णाङ्क type;
    प्रति (type = 0; type < FF_ARRAY_ELEMS(hw_type_नामानि); type++) {
        यदि (hw_type_नामानि[type] && !वाक्यं_तुलय(hw_type_नामानि[type], name))
            प्रत्यागम type;
    }
    प्रत्यागम AV_HWDEVICE_TYPE_NONE;
}

ध्रुव वर्ण *av_hwdevice_get_type_name(गणना AVHWDeviceType type)
{
    यदि (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_नामानि))
        प्रत्यागम hw_type_नामानि[type];
    अन्यथा
        प्रत्यागम रिक्त;
}

गणना AVHWDeviceType av_hwdevice_iterate_types(गणना AVHWDeviceType पूर्व)
{
    गणना AVHWDeviceType अग्र;
    पूर्णाङ्क i, समुच्चयः = 0;
    प्रति (i = 0; hw_सारणी[i]; i++) {
        यदि (पूर्व != AV_HWDEVICE_TYPE_NONE && hw_सारणी[i]->type <= पूर्व)
            अनुवर्त;
        यदि (!समुच्चयः || hw_सारणी[i]->type < अग्र) {
            अग्र = hw_सारणी[i]->type;
            समुच्चयः = 1;
        }
    }
    प्रत्यागम समुच्चयः ? अग्र : AV_HWDEVICE_TYPE_NONE;
}

स्थिर ध्रुव वर्ण *hwdevice_ctx_get_name(शून्य *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    प्रत्यागम ctx->hw_type->name;
}

स्थिर ध्रुव AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .item_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .संस्करणम्    = LIBAVUTIL_संस्करणम्_INT,
};

स्थिर शून्य hwdevice_ctx_free(शून्य *opaque, uint8_t *दत्त)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)दत्त;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    यदि (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    यदि (ctx->मुक्त)
        ctx->मुक्त(ctx);

    av_बफर_unref(&ctxi->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(गणना AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    ध्रुव HWContextType *hw_type = रिक्त;
    पूर्णाङ्क i;

    प्रति (i = 0; hw_सारणी[i]; i++) {
        यदि (hw_सारणी[i]->type == type) {
            hw_type = hw_सारणी[i];
            भङ्ग;
        }
    }
    यदि (!hw_type)
        प्रत्यागम रिक्त;

    ctxi = av_mallocz(परिमाण(*ctxi));
    यदि (!ctxi)
        प्रत्यागम रिक्त;
    ctx = &ctxi->p;

    यदि (hw_type->device_hwctx_आकार) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_आकार);
        यदि (!ctx->hwctx)
            गच्छ fail;
    }

    buf = av_बफर_create((uint8_t*)ctx, परिमाण(*ctx),
                           hwdevice_ctx_free, रिक्त,
                           AV_बफर_FLAG_READONLY);
    यदि (!buf)
        गच्छ fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    प्रत्यागम buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    प्रत्यागम रिक्त;
}

पूर्णाङ्क av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->दत्त;
    AVHWDeviceContext *ctx  = &ctxi->p;
    पूर्णाङ्क ret = 0;

    यदि (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    प्रत्यागम ret;
}

स्थिर ध्रुव AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .item_name  = av_default_item_name,
    .संस्करणम्    = LIBAVUTIL_संस्करणम्_INT,
};

स्थिर शून्य hwframe_ctx_free(शून्य *opaque, uint8_t *दत्त)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)दत्त;
    AVHWFramesContext *ctx  = &ctxi->p;

    यदि (ctxi->pool_आन्तरिकम्)
        av_बफर_pool_uninit(&ctxi->pool_आन्तरिकम्);

    av_बफर_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_तालकम्);

    यदि (ctxi->hw_type->चौकटाः_uninit)
        ctxi->hw_type->चौकटाः_uninit(ctx);

    यदि (ctx->मुक्त)
        ctx->मुक्त(ctx);

    av_बफर_unref(&ctxi->source_चौकटाः);

    av_बफर_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_अन्तर्)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_अन्तर्->दत्त;
    ध्रुव HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = रिक्त;

    ctxi = av_mallocz(परिमाण(*ctxi));
    यदि (!ctxi)
        प्रत्यागम रिक्त;
    ctx  = &ctxi->p;

    यदि (ff_mutex_init(&ctxi->transfer_pool_तालकम्, रिक्त)) {
        av_free(ctxi);
        प्रत्यागम रिक्त;
    }

    यदि (hw_type->चौकटाः_hwctx_आकार) {
        ctx->hwctx = av_mallocz(hw_type->चौकटाः_hwctx_आकार);
        यदि (!ctx->hwctx)
            गच्छ fail;
    }

    device_ref = av_बफर_ref(device_ref_अन्तर्);
    यदि (!device_ref)
        गच्छ fail;

    buf = av_बफर_create((uint8_t*)ctx, परिमाण(*ctx),
                           hwframe_ctx_free, रिक्त,
                           AV_बफर_FLAG_READONLY);
    यदि (!buf)
        गच्छ fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    प्रत्यागम buf;

fail:
    av_बफर_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_तालकम्);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    प्रत्यागम रिक्त;
}

स्थिर पूर्णाङ्क hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->दत्त;
    AVFrame **चौकटाः;
    पूर्णाङ्क i, ret = 0;

    चौकटाः = av_calloc(ctx->initial_pool_आकार, परिमाण(*चौकटाः));
    यदि (!चौकटाः)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (i = 0; i < ctx->initial_pool_आकार; i++) {
        चौकटाः[i] = av_frame_alloc();
        यदि (!चौकटाः[i])
            गच्छ fail;

        ret = av_hwframe_get_बफर(ref, चौकटाः[i], 0);
        यदि (ret < 0)
            गच्छ fail;
    }

fail:
    प्रति (i = 0; i < ctx->initial_pool_आकार; i++)
        av_frame_free(&चौकटाः[i]);
    av_freep(&चौकटाः);

    प्रत्यागम ret;
}

पूर्णाङ्क av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->दत्त;
    AVHWFramesContext *ctx  = &ctxi->p;
    ध्रुव गणना AVPixelFormat *pix_fmt;
    पूर्णाङ्क ret;

    यदि (ctxi->source_चौकटाः) {
        /* A derived frame context is already initialised. */
        प्रत्यागम 0;
    }

    /* validate the pixel format */
    प्रति (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        यदि (*pix_fmt == ctx->format)
            भङ्ग;
    }
    यदि (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        प्रत्यागम AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_आकार(ctx->विस्तारः, ctx->height, 0, ctx);
    यदि (ret < 0)
        प्रत्यागम ret;

    /* format-specific init */
    यदि (ctxi->hw_type->चौकटाः_init) {
        ret = ctxi->hw_type->चौकटाः_init(ctx);
        यदि (ret < 0)
            प्रत्यागम ret;
    }

    यदि (ctxi->pool_आन्तरिकम् && !ctx->pool)
        ctx->pool = ctxi->pool_आन्तरिकम्;

    /* preallocate the frames in the pool, if requested */
    यदि (ctx->initial_pool_आकार > 0) {
        ret = hwframe_pool_prealloc(ref);
        यदि (ret < 0)
            प्रत्यागम ret;
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    गणना AVHWFrameTransferDirection dir,
                                    गणना AVPixelFormat **formats, पूर्णाङ्क flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->दत्त;

    यदि (!ctxi->hw_type->transfer_get_formats)
        प्रत्यागम AVERROR(ENOSYS);

    प्रत्यागम ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

स्थिर शून्य transfer_pool_free(शून्य *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_बफर_unref(&device_ref);
}

स्थिर AVBufferRef *transfer_बफर_alloc(शून्य *opaque, size_t आकार)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = रिक्त;

    ff_mutex_तालकम्(&ctxi->transfer_pool_तालकम्);
    यदि (ctxi->transfer_pool_आकार != आकार) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_बफर_alloc ?
                                  av_बफर_ref(ctxi->p.device_ref) : रिक्त;

        av_बफर_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_बफर_pool_init2(आकार, device_ref,
                                 ctxi->hw_type->transfer_बफर_alloc,
                                 transfer_pool_free) :
            av_बफर_pool_init(आकार, रिक्त);
        ctxi->transfer_pool_आकार = ctxi->transfer_pool ? आकार : 0;
        यदि (!ctxi->transfer_pool)
            av_बफर_unref(&device_ref);
    }
    यदि (ctxi->transfer_pool)
        buf = av_बफर_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_तालकम्);

    प्रत्यागम buf ? buf : av_बफर_alloc(आकार);
}

पूर्णाङ्क av_hwframe_get_transfer_बफर(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    प्रत्यागम ff_frame_get_video_बफर(frame, 0, transfer_बफर_alloc,
                                     hwframe_ctx->दत्त);
}

स्थिर पूर्णाङ्क transfer_दत्त_alloc(AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    पूर्णाङ्क ret = 0;

    यदि (!src->hw_चौकटाः_ctx)
        प्रत्यागम AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_चौकटाः_ctx->दत्त;

    frame_tmp = av_frame_alloc();
    यदि (!frame_tmp)
        प्रत्यागम AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    यदि (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } अन्यथा {
        गणना AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_चौकटाः_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        यदि (ret < 0)
            गच्छ fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->विस्तारः  = ctx->विस्तारः;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_बफर(src->hw_चौकटाः_ctx, frame_tmp);
    यदि (ret < 0)
        गच्छ fail;

    ret = av_hwframe_transfer_दत्त(frame_tmp, src, flags);
    यदि (ret < 0)
        गच्छ fail;

    frame_tmp->विस्तारः  = src->विस्तारः;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    प्रत्यागम ret;
}

पूर्णाङ्क av_hwframe_transfer_दत्त(AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    पूर्णाङ्क ret;

    यदि (!dst->buf[0])
        प्रत्यागम transfer_दत्त_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    यदि (src->hw_चौकटाः_ctx && dst->hw_चौकटाः_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_चौकटाः_ctx->दत्त;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_चौकटाः_ctx->दत्त;

        यदि (src_ctx->source_चौकटाः) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            प्रत्यागम AVERROR(ENOSYS);
        }

        यदि (dst_ctx->source_चौकटाः) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            प्रत्यागम AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        यदि (src_ctx->hw_type->transfer_दत्त_from)
            ret = src_ctx->hw_type->transfer_दत्त_from(&src_ctx->p, dst, src);
        यदि (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_दत्त_गन्तव्यम्)
            ret = dst_ctx->hw_type->transfer_दत्त_गन्तव्यम्(&dst_ctx->p, dst, src);
        यदि (ret < 0)
            प्रत्यागम ret;
    } अन्यथा {
        यदि (src->hw_चौकटाः_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_चौकटाः_ctx->दत्त;

            यदि (!ctx->hw_type->transfer_दत्त_from)
                प्रत्यागम AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_दत्त_from(&ctx->p, dst, src);
            यदि (ret < 0)
                प्रत्यागम ret;
        } अन्यथा यदि (dst->hw_चौकटाः_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_चौकटाः_ctx->दत्त;

            यदि (!ctx->hw_type->transfer_दत्त_गन्तव्यम्)
                प्रत्यागम AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_दत्त_गन्तव्यम्(&ctx->p, dst, src);
            यदि (ret < 0)
                प्रत्यागम ret;
        } अन्यथा {
            प्रत्यागम AVERROR(ENOSYS);
        }
    }
    प्रत्यागम 0;
}

पूर्णाङ्क av_hwframe_get_बफर(AVBufferRef *hwframe_ref, AVFrame *frame, पूर्णाङ्क flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->दत्त;
    AVHWFramesContext *ctx  = &ctxi->p;
    पूर्णाङ्क ret;

    यदि (ctxi->source_चौकटाः) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_चौकटाः_ctx = av_बफर_ref(hwframe_ref);
        यदि (!frame->hw_चौकटाः_ctx)
            प्रत्यागम AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        यदि (!src_frame)
            प्रत्यागम AVERROR(ENOMEM);

        ret = av_hwframe_get_बफर(ctxi->source_चौकटाः,
                                    src_frame, 0);
        यदि (ret < 0) {
            av_frame_free(&src_frame);
            प्रत्यागम ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_आवण्टनम्_map_flags);
        यदि (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            प्रत्यागम ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        प्रत्यागम 0;
    }

    यदि (!ctxi->hw_type->चौकटाः_get_बफर)
        प्रत्यागम AVERROR(ENOSYS);

    यदि (!ctx->pool)
        प्रत्यागम AVERROR(EINVAL);

    frame->hw_चौकटाः_ctx = av_बफर_ref(hwframe_ref);
    यदि (!frame->hw_चौकटाः_ctx)
        प्रत्यागम AVERROR(ENOMEM);

    ret = ctxi->hw_type->चौकटाः_get_बफर(ctx, frame);
    यदि (ret < 0) {
        av_बफर_unref(&frame->hw_चौकटाः_ctx);
        प्रत्यागम ret;
    }

    frame->extended_दत्त = frame->दत्त;

    प्रत्यागम 0;
}

शून्य *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->दत्त;
    ध्रुव HWContextType  *hw_type = ctx->hw_type;

    यदि (hw_type->device_hwconfig_आकार == 0)
        प्रत्यागम रिक्त;

    प्रत्यागम av_mallocz(hw_type->device_hwconfig_आकार);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ध्रुव शून्य *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->दत्त;
    ध्रुव HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    यदि (!hw_type->चौकटाः_get_constraints)
        प्रत्यागम रिक्त;

    constraints = av_mallocz(परिमाण(*constraints));
    यदि (!constraints)
        प्रत्यागम रिक्त;

    constraints->min_विस्तारः = constraints->min_height = 0;
    constraints->max_विस्तारः = constraints->max_height = अधिकतम_पूर्णाङ्कः;

    यदि (hw_type->चौकटाः_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        प्रत्यागम constraints;
    } अन्यथा {
        av_hwframe_constraints_free(&constraints);
        प्रत्यागम रिक्त;
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
                           ध्रुव वर्ण *device, AVDictionary *opts, पूर्णाङ्क flags)
{
    AVBufferRef *device_ref = रिक्त;
    FFHWDeviceContext *device_ctx;
    पूर्णाङ्क ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    यदि (!device_ref) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->दत्त;

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
    प्रत्यागम 0;
fail:
    av_बफर_unref(&device_ref);
    *pdevice_ref = रिक्त;
    प्रत्यागम ret;
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
    यावत् (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->दत्त;
        यदि (tmp_ctx->p.type == type) {
            dst_ref = av_बफर_ref(tmp_ref);
            यदि (!dst_ref) {
                ret = AVERROR(ENOMEM);
                गच्छ fail;
            }
            गच्छ समाप्तम्;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    यदि (!dst_ref) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->दत्त;

    tmp_ref = src_ref;
    यावत् (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->दत्त;
        यदि (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            यदि (ret == 0) {
                dst_ctx->source_device = av_बफर_ref(src_ref);
                यदि (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    गच्छ fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                यदि (ret < 0)
                    गच्छ fail;
                गच्छ समाप्तम्;
            }
            यदि (ret != AVERROR(ENOSYS))
                गच्छ fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    गच्छ fail;

समाप्तम्:
    *dst_ref_ptr = dst_ref;
    प्रत्यागम 0;

fail:
    av_बफर_unref(&dst_ref);
    *dst_ref_ptr = रिक्त;
    प्रत्यागम ret;
}

पूर्णाङ्क av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   गणना AVHWDeviceType type,
                                   AVBufferRef *src_ref, पूर्णाङ्क flags)
{
    प्रत्यागम av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               रिक्त, flags);
}

स्थिर शून्य ff_hwframe_unmap(शून्य *opaque, uint8_t *दत्त)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)दत्त;
    AVHWFramesContext *ctx = opaque;

    यदि (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_बफर_unref(&hwmap->hw_चौकटाः_ctx);

    av_free(hwmap);
}

पूर्णाङ्क ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ध्रुव AVFrame *src,
                          शून्य (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          शून्य *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->दत्त;
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

    hwmap->hw_चौकटाः_ctx = av_बफर_ref(hwframe_ref);
    यदि (!hwmap->hw_चौकटाः_ctx) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_बफर_create((uint8_t*)hwmap, परिमाण(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    यदि (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    प्रत्यागम 0;

fail:
    यदि (hwmap) {
        av_बफर_unref(&hwmap->hw_चौकटाः_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    प्रत्यागम ret;
}

पूर्णाङ्क av_hwframe_map(AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    AVBufferRef    *orig_dst_चौकटाः = dst->hw_चौकटाः_ctx;
    गणना AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    पूर्णाङ्क ret;

    यदि (src->hw_चौकटाः_ctx && dst->hw_चौकटाः_ctx) {
        FFHWFramesContext *src_चौकटाः = (FFHWFramesContext*)src->hw_चौकटाः_ctx->दत्त;
        FFHWFramesContext *dst_चौकटाः = (FFHWFramesContext*)dst->hw_चौकटाः_ctx->दत्त;

        यदि ((src_चौकटाः == dst_चौकटाः &&
             src->format == dst_चौकटाः->p.sw_format &&
             dst->format == dst_चौकटाः->p.format) ||
            (src_चौकटाः->source_चौकटाः &&
             src_चौकटाः->source_चौकटाः->दत्त ==
             (uint8_t*)dst_चौकटाः)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            यदि (!src->buf[0]) {
                av_log(src_चौकटाः, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                प्रत्यागम AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->दत्त;
            प्रत्यागम av_frame_replace(dst, hwmap->source);
        }
    }

    यदि (src->hw_चौकटाः_ctx) {
        FFHWFramesContext *src_चौकटाः = (FFHWFramesContext*)src->hw_चौकटाः_ctx->दत्त;

        यदि (src_चौकटाः->p.format == src->format &&
            src_चौकटाः->hw_type->map_from) {
            ret = src_चौकटाः->hw_type->map_from(&src_चौकटाः->p,
                                                dst, src, flags);
            यदि (ret >= 0)
                प्रत्यागम ret;
            अन्यथा यदि (ret != AVERROR(ENOSYS))
                गच्छ fail;
        }
    }

    यदि (dst->hw_चौकटाः_ctx) {
        FFHWFramesContext *dst_चौकटाः = (FFHWFramesContext*)dst->hw_चौकटाः_ctx->दत्त;

        यदि (dst_चौकटाः->p.format == dst->format &&
            dst_चौकटाः->hw_type->map_गन्तव्यम्) {
            ret = dst_चौकटाः->hw_type->map_गन्तव्यम्(&dst_चौकटाः->p,
                                              dst, src, flags);
            यदि (ret >= 0)
                प्रत्यागम ret;
            अन्यथा यदि (ret != AVERROR(ENOSYS))
                गच्छ fail;
        }
    }

    प्रत्यागम AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_चौकटाः == रिक्त ||
               orig_dst_चौकटाः == dst->hw_चौकटाः_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_चौकटाः_ctx = रिक्त;
    av_frame_unref(dst);

    dst->hw_चौकटाः_ctx = orig_dst_चौकटाः;
    dst->format        = orig_dst_fmt;

    प्रत्यागम ret;
}

पूर्णाङ्क av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  गणना AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  पूर्णाङ्क flags)
{
    AVBufferRef   *dst_ref = रिक्त;
    FFHWFramesContext *dsti = रिक्त;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->दत्त;
    AVHWFramesContext *dst, *src = &srci->p;
    पूर्णाङ्क ret;

    यदि (srci->source_चौकटाः) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_चौकटाः->दत्त;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->दत्त;

        यदि (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_बफर_ref(srci->source_चौकटाः);
            यदि (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                गच्छ fail;
            }
            प्रत्यागम 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    यदि (!dst_ref) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->दत्त;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->विस्तारः     = src->विस्तारः;
    dst->height    = src->height;

    dsti->source_चौकटाः = av_बफर_ref(source_frame_ctx);
    यदि (!dsti->source_चौकटाः) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    dsti->source_आवण्टनम्_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_प्रत्यक्षम्);

    ret = AVERROR(ENOSYS);
    यदि (srci->hw_type->चौकटाः_derive_from)
        ret = srci->hw_type->चौकटाः_derive_from(dst, src, flags);
    यदि (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->चौकटाः_derive_गन्तव्यम्)
        ret = dsti->hw_type->चौकटाः_derive_गन्तव्यम्(dst, src, flags);
    यदि (ret == AVERROR(ENOSYS))
        ret = 0;
    यदि (ret)
        गच्छ fail;

    *derived_frame_ctx = dst_ref;
    प्रत्यागम 0;

fail:
    यदि (dsti)
        av_बफर_unref(&dsti->source_चौकटाः);
    av_बफर_unref(&dst_ref);
    प्रत्यागम ret;
}

पूर्णाङ्क ff_hwframe_map_replace(AVFrame *dst, ध्रुव AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->दत्त;
    प्रत्यागम av_frame_replace(hwmap->source, src);
}
