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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "buffer.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "frame_internal.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_internal.h"
#ଅନ୍ତର୍ଭାଵ "imgutils.h"
#ଅନ୍ତର୍ଭାଵ "log.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"
#ଅନ୍ତର୍ଭାଵ "pixfmt.h"

ସ୍ଥିର ଅଚଳ HWContextType * ଅଚଳ hw_table[] = {
#ଯଦି CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#endif
#ଯଦି CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#endif
#ଯଦି CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#endif
#ଯଦି CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#endif
#ଯଦି CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#endif
#ଯଦି CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#endif
#ଯଦି CONFIG_QSV
    &ff_hwcontext_type_qsv,
#endif
#ଯଦି CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#endif
#ଯଦି CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#endif
#ଯଦି CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#endif
#ଯଦି CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#endif
#ଯଦି CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#endif
#ଯଦି CONFIG_AMF
    &ff_hwcontext_type_amf,
#endif
#ଯଦି CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#endif
    ଖାଲି,
};

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *ଅଚଳ hw_type_names[] = {
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

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    ଅଚଳ HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *source_device;
} FFHWDeviceContext;

ଗଣନା AVHWDeviceType av_hwdevice_find_type_by_name(ଅଚଳ ଅକ୍ଷର *name)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା type;
    ପାଇଁ (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        ଯଦି (hw_type_names[type] && !strcmp(hw_type_names[type], name))
            ଫେରନ୍ତୁ type;
    }
    ଫେରନ୍ତୁ AV_HWDEVICE_TYPE_NONE;
}

ଅଚଳ ଅକ୍ଷର *av_hwdevice_get_type_name(ଗଣନା AVHWDeviceType type)
{
    ଯଦି (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        ଫେରନ୍ତୁ hw_type_names[type];
    ଅନ୍ୟଥା
        ଫେରନ୍ତୁ ଖାଲି;
}

ଗଣନା AVHWDeviceType av_hwdevice_iterate_types(ଗଣନା AVHWDeviceType prev)
{
    ଗଣନା AVHWDeviceType next;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, set = 0;
    ପାଇଁ (i = 0; hw_table[i]; i++) {
        ଯଦି (prev != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= prev)
            ଜାରି;
        ଯଦି (!set || hw_table[i]->type < next) {
            next = hw_table[i]->type;
            set = 1;
        }
    }
    ଫେରନ୍ତୁ set ? next : AV_HWDEVICE_TYPE_NONE;
}

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର *hwdevice_ctx_get_name(ଶୂନ୍ୟ *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    ଫେରନ୍ତୁ ctx->hw_type->name;
}

ସ୍ଥିର ଅଚଳ AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .item_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .version    = LIBAVUTIL_VERSION_INT,
};

ସ୍ଥିର ଶୂନ୍ୟ hwdevice_ctx_free(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)data;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    ଯଦି (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    ଯଦି (ctx->ମୁକ୍ତ)
        ctx->ମୁକ୍ତ(ctx);

    av_buffer_unref(&ctxi->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(ଗଣନା AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    ଅଚଳ HWContextType *hw_type = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ (i = 0; hw_table[i]; i++) {
        ଯଦି (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            ଭାଙ୍ଗ;
        }
    }
    ଯଦି (!hw_type)
        ଫେରନ୍ତୁ ଖାଲି;

    ctxi = av_mallocz(ଆକାର(*ctxi));
    ଯଦି (!ctxi)
        ଫେରନ୍ତୁ ଖାଲି;
    ctx = &ctxi->p;

    ଯଦି (hw_type->device_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_size);
        ଯଦି (!ctx->hwctx)
            ଯାଅ fail;
    }

    buf = av_buffer_create((uint8_t*)ctx, ଆକାର(*ctx),
                           hwdevice_ctx_free, ଖାଲି,
                           AV_BUFFER_FLAG_READONLY);
    ଯଦି (!buf)
        ଯାଅ fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    ଫେରନ୍ତୁ buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ଫେରନ୍ତୁ ଖାଲି;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->data;
    AVHWDeviceContext *ctx  = &ctxi->p;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    ଯଦି (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ଅଚଳ AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .item_name  = av_default_item_name,
    .version    = LIBAVUTIL_VERSION_INT,
};

ସ୍ଥିର ଶୂନ୍ୟ hwframe_ctx_free(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)data;
    AVHWFramesContext *ctx  = &ctxi->p;

    ଯଦି (ctxi->pool_internal)
        av_buffer_pool_uninit(&ctxi->pool_internal);

    av_buffer_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    ଯଦି (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    ଯଦି (ctx->ମୁକ୍ତ)
        ctx->ମୁକ୍ତ(ctx);

    av_buffer_unref(&ctxi->source_frames);

    av_buffer_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_in)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_in->data;
    ଅଚଳ HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = ଖାଲି;

    ctxi = av_mallocz(ଆକାର(*ctxi));
    ଯଦି (!ctxi)
        ଫେରନ୍ତୁ ଖାଲି;
    ctx  = &ctxi->p;

    ଯଦି (ff_mutex_init(&ctxi->transfer_pool_lock, ଖାଲି)) {
        av_free(ctxi);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (hw_type->frames_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_size);
        ଯଦି (!ctx->hwctx)
            ଯାଅ fail;
    }

    device_ref = av_buffer_ref(device_ref_in);
    ଯଦି (!device_ref)
        ଯାଅ fail;

    buf = av_buffer_create((uint8_t*)ctx, ଆକାର(*ctx),
                           hwframe_ctx_free, ଖାଲି,
                           AV_BUFFER_FLAG_READONLY);
    ଯଦି (!buf)
        ଯାଅ fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    ଫେରନ୍ତୁ buf;

fail:
    av_buffer_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->data;
    AVFrame **frames;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret = 0;

    frames = av_calloc(ctx->initial_pool_size, ଆକାର(*frames));
    ଯଦି (!frames)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (i = 0; i < ctx->initial_pool_size; i++) {
        frames[i] = av_frame_alloc();
        ଯଦି (!frames[i])
            ଯାଅ fail;

        ret = av_hwframe_get_buffer(ref, frames[i], 0);
        ଯଦି (ret < 0)
            ଯାଅ fail;
    }

fail:
    ପାଇଁ (i = 0; i < ctx->initial_pool_size; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    ଅଚଳ ଗଣନା AVPixelFormat *pix_fmt;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        ଫେରନ୍ତୁ 0;
    }

    /* validate the pixel format */
    ପାଇଁ (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        ଯଦି (*pix_fmt == ctx->format)
            ଭାଙ୍ଗ;
    }
    ଯଦି (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_size(ctx->width, ctx->height, 0, ctx);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    /* format-specific init */
    ଯଦି (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
    }

    ଯଦି (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    ଯଦି (ctx->initial_pool_size > 0) {
        ret = hwframe_pool_prealloc(ref);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    ଗଣନା AVHWFrameTransferDirection dir,
                                    ଗଣନା AVPixelFormat **formats, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;

    ଯଦି (!ctxi->hw_type->transfer_get_formats)
        ଫେରନ୍ତୁ AVERROR(ENOSYS);

    ଫେରନ୍ତୁ ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

ସ୍ଥିର ଶୂନ୍ୟ transfer_pool_free(ଶୂନ୍ୟ *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_buffer_unref(&device_ref);
}

ସ୍ଥିର AVBufferRef *transfer_buffer_alloc(ଶୂନ୍ୟ *opaque, size_t size)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = ଖାଲି;

    ff_mutex_lock(&ctxi->transfer_pool_lock);
    ଯଦି (ctxi->transfer_pool_size != size) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_buffer_alloc ?
                                  av_buffer_ref(ctxi->p.device_ref) : ଖାଲି;

        av_buffer_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_buffer_pool_init2(size, device_ref,
                                 ctxi->hw_type->transfer_buffer_alloc,
                                 transfer_pool_free) :
            av_buffer_pool_init(size, ଖାଲି);
        ctxi->transfer_pool_size = ctxi->transfer_pool ? size : 0;
        ଯଦି (!ctxi->transfer_pool)
            av_buffer_unref(&device_ref);
    }
    ଯଦି (ctxi->transfer_pool)
        buf = av_buffer_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    ଫେରନ୍ତୁ buf ? buf : av_buffer_alloc(size);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hwframe_get_transfer_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    ଫେରନ୍ତୁ ff_frame_get_video_buffer(frame, 0, transfer_buffer_alloc,
                                     hwframe_ctx->data);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା transfer_data_alloc(AVFrame *dst, ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    ଯଦି (!src->hw_frames_ctx)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;

    frame_tmp = av_frame_alloc();
    ଯଦି (!frame_tmp)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    ଯଦି (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } ଅନ୍ୟଥା {
        ଗଣନା AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        ଯଦି (ret < 0)
            ଯାଅ fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_buffer(src->hw_frames_ctx, frame_tmp);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    ret = av_hwframe_transfer_data(frame_tmp, src, flags);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hwframe_transfer_data(AVFrame *dst, ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!dst->buf[0])
        ଫେରନ୍ତୁ transfer_data_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    ଯଦି (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->data;

        ଯଦି (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        }

        ଯଦି (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        ଯଦି (src_ctx->hw_type->transfer_data_from)
            ret = src_ctx->hw_type->transfer_data_from(&src_ctx->p, dst, src);
        ଯଦି (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_data_to)
            ret = dst_ctx->hw_type->transfer_data_to(&dst_ctx->p, dst, src);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
    } ଅନ୍ୟଥା {
        ଯଦି (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->data;

            ଯଦି (!ctx->hw_type->transfer_data_from)
                ଫେରନ୍ତୁ AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_from(&ctx->p, dst, src);
            ଯଦି (ret < 0)
                ଫେରନ୍ତୁ ret;
        } ଅନ୍ୟଥା ଯଦି (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->data;

            ଯଦି (!ctx->hw_type->transfer_data_to)
                ଫେରନ୍ତୁ AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_to(&ctx->p, dst, src);
            ଯଦି (ret < 0)
                ଫେରନ୍ତୁ ret;
        } ଅନ୍ୟଥା {
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        }
    }
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hwframe_get_buffer(AVBufferRef *hwframe_ref, AVFrame *frame, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
        ଯଦି (!frame->hw_frames_ctx)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        ଯଦି (!src_frame)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        ret = av_hwframe_get_buffer(ctxi->source_frames,
                                    src_frame, 0);
        ଯଦି (ret < 0) {
            av_frame_free(&src_frame);
            ଫେରନ୍ତୁ ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        ଯଦି (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            ଫେରନ୍ତୁ ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        ଫେରନ୍ତୁ 0;
    }

    ଯଦି (!ctxi->hw_type->frames_get_buffer)
        ଫେରନ୍ତୁ AVERROR(ENOSYS);

    ଯଦି (!ctx->pool)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    ଯଦି (!frame->hw_frames_ctx)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_buffer(ctx, frame);
    ଯଦି (ret < 0) {
        av_buffer_unref(&frame->hw_frames_ctx);
        ଫେରନ୍ତୁ ret;
    }

    frame->extended_data = frame->data;

    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    ଅଚଳ HWContextType  *hw_type = ctx->hw_type;

    ଯଦି (hw_type->device_hwconfig_size == 0)
        ଫେରନ୍ତୁ ଖାଲି;

    ଫେରନ୍ତୁ av_mallocz(hw_type->device_hwconfig_size);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           ଅଚଳ ଶୂନ୍ୟ *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    ଅଚଳ HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    ଯଦି (!hw_type->frames_get_constraints)
        ଫେରନ୍ତୁ ଖାଲି;

    constraints = av_mallocz(ଆକାର(*constraints));
    ଯଦି (!constraints)
        ଫେରନ୍ତୁ ଖାଲି;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = INT_MAX;

    ଯଦି (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        ଫେରନ୍ତୁ constraints;
    } ଅନ୍ୟଥା {
        av_hwframe_constraints_free(&constraints);
        ଫେରନ୍ତୁ ଖାଲି;
    }
}

ଶୂନ୍ୟ av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    ଯଦି (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, ଗଣନା AVHWDeviceType type,
                           ଅଚଳ ଅକ୍ଷର *device, AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVBufferRef *device_ref = ଖାଲି;
    FFHWDeviceContext *device_ctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    ଯଦି (!device_ref) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->data;

    ଯଦି (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        ଯାଅ fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    ret = av_hwdevice_ctx_init(device_ref);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    *pdevice_ref = device_ref;
    ଫେରନ୍ତୁ 0;
fail:
    av_buffer_unref(&device_ref);
    *pdevice_ref = ଖାଲି;
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        ଗଣନା AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVBufferRef *dst_ref = ଖାଲି, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    tmp_ref = src_ref;
    ଯେତେବେଳେ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        ଯଦି (tmp_ctx->p.type == type) {
            dst_ref = av_buffer_ref(tmp_ref);
            ଯଦି (!dst_ref) {
                ret = AVERROR(ENOMEM);
                ଯାଅ fail;
            }
            ଯାଅ done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    ଯଦି (!dst_ref) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->data;

    tmp_ref = src_ref;
    ଯେତେବେଳେ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        ଯଦି (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            ଯଦି (ret == 0) {
                dst_ctx->source_device = av_buffer_ref(src_ref);
                ଯଦି (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    ଯାଅ fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                ଯଦି (ret < 0)
                    ଯାଅ fail;
                ଯାଅ done;
            }
            ଯଦି (ret != AVERROR(ENOSYS))
                ଯାଅ fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    ଯାଅ fail;

done:
    *dst_ref_ptr = dst_ref;
    ଫେରନ୍ତୁ 0;

fail:
    av_buffer_unref(&dst_ref);
    *dst_ref_ptr = ଖାଲି;
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   ଗଣନା AVHWDeviceType type,
                                   AVBufferRef *src_ref, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଫେରନ୍ତୁ av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               ଖାଲି, flags);
}

ସ୍ଥିର ଶୂନ୍ୟ ff_hwframe_unmap(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)data;
    AVHWFramesContext *ctx = opaque;

    ଯଦି (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_buffer_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, ଅଚଳ AVFrame *src,
                          ଶୂନ୍ୟ (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          ଶୂନ୍ୟ *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->data;
    HWMapDescriptor *hwmap;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    hwmap = av_mallocz(ଆକାର(*hwmap));
    ଯଦି (!hwmap) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    hwmap->source = av_frame_alloc();
    ଯଦି (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    hwmap->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    ଯଦି (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_buffer_create((uint8_t*)hwmap, ଆକାର(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    ଯଦି (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    ଫେରନ୍ତୁ 0;

fail:
    ଯଦି (hwmap) {
        av_buffer_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hwframe_map(AVFrame *dst, ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    ଗଣନା AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        ଯଦି ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->data ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            ଯଦି (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                ଫେରନ୍ତୁ AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->data;
            ଫେରନ୍ତୁ av_frame_replace(dst, hwmap->source);
        }
    }

    ଯଦି (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;

        ଯଦି (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            ଯଦି (ret >= 0)
                ଫେରନ୍ତୁ ret;
            ଅନ୍ୟଥା ଯଦି (ret != AVERROR(ENOSYS))
                ଯାଅ fail;
        }
    }

    ଯଦି (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        ଯଦି (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            ଯଦି (ret >= 0)
                ଫେରନ୍ତୁ ret;
            ଅନ୍ୟଥା ଯଦି (ret != AVERROR(ENOSYS))
                ଯାଅ fail;
        }
    }

    ଫେରନ୍ତୁ AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_frames == ଖାଲି ||
               orig_dst_frames == dst->hw_frames_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_frames_ctx = ଖାଲି;
    av_frame_unref(dst);

    dst->hw_frames_ctx = orig_dst_frames;
    dst->format        = orig_dst_fmt;

    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  ଗଣନା AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVBufferRef   *dst_ref = ଖାଲି;
    FFHWFramesContext *dsti = ଖାଲି;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->data;
    AVHWFramesContext *dst, *src = &srci->p;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->data;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->data;

        ଯଦି (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_buffer_ref(srci->source_frames);
            ଯଦି (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                ଯାଅ fail;
            }
            ଫେରନ୍ତୁ 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    ଯଦି (!dst_ref) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->data;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->width     = src->width;
    dst->height    = src->height;

    dsti->source_frames = av_buffer_ref(source_frame_ctx);
    ଯଦି (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    dsti->source_allocation_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_DIRECT);

    ret = AVERROR(ENOSYS);
    ଯଦି (srci->hw_type->frames_derive_from)
        ret = srci->hw_type->frames_derive_from(dst, src, flags);
    ଯଦି (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->frames_derive_to)
        ret = dsti->hw_type->frames_derive_to(dst, src, flags);
    ଯଦି (ret == AVERROR(ENOSYS))
        ret = 0;
    ଯଦି (ret)
        ଯାଅ fail;

    *derived_frame_ctx = dst_ref;
    ଫେରନ୍ତୁ 0;

fail:
    ଯଦି (dsti)
        av_buffer_unref(&dsti->source_frames);
    av_buffer_unref(&dst_ref);
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_hwframe_map_replace(AVFrame *dst, ଅଚଳ AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->data;
    ଫେରନ୍ତୁ av_frame_replace(hwmap->source, src);
}
