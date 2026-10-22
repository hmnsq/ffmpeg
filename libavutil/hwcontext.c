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

#અન્તર્ભાવ "config.h"

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "buffer.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "frame_internal.h"
#અન્તર્ભાવ "hwcontext.h"
#અન્તર્ભાવ "hwcontext_internal.h"
#અન્તર્ભાવ "imgutils.h"
#અન્તર્ભાવ "log.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "pixdesc.h"
#અન્તર્ભાવ "pixfmt.h"

સ્થિર અચલ HWContextType * અચલ hw_table[] = {
#જો CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#endif
#જો CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#endif
#જો CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#endif
#જો CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#endif
#જો CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#endif
#જો CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#endif
#જો CONFIG_QSV
    &ff_hwcontext_type_qsv,
#endif
#જો CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#endif
#જો CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#endif
#જો CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#endif
#જો CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#endif
#જો CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#endif
#જો CONFIG_AMF
    &ff_hwcontext_type_amf,
#endif
#જો CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#endif
    ખાલી,
};

સ્થિર અચલ અક્ષર *અચલ hw_type_names[] = {
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

પ્રકારવ્યાખ્યા સંરચના FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    અચલ HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *source_device;
} FFHWDeviceContext;

ગણના AVHWDeviceType av_hwdevice_find_type_by_name(અચલ અક્ષર *name)
{
    પૂર્ણાંક type;
    માટે (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        જો (hw_type_names[type] && !strcmp(hw_type_names[type], name))
            પાછા type;
    }
    પાછા AV_HWDEVICE_TYPE_NONE;
}

અચલ અક્ષર *av_hwdevice_get_type_name(ગણના AVHWDeviceType type)
{
    જો (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        પાછા hw_type_names[type];
    નહીંતર
        પાછા ખાલી;
}

ગણના AVHWDeviceType av_hwdevice_iterate_types(ગણના AVHWDeviceType prev)
{
    ગણના AVHWDeviceType next;
    પૂર્ણાંક i, set = 0;
    માટે (i = 0; hw_table[i]; i++) {
        જો (prev != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= prev)
            ચાલુ;
        જો (!set || hw_table[i]->type < next) {
            next = hw_table[i]->type;
            set = 1;
        }
    }
    પાછા set ? next : AV_HWDEVICE_TYPE_NONE;
}

સ્થિર અચલ અક્ષર *hwdevice_ctx_get_name(શૂન્ય *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    પાછા ctx->hw_type->name;
}

સ્થિર અચલ AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .item_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .version    = LIBAVUTIL_VERSION_INT,
};

સ્થિર શૂન્ય hwdevice_ctx_free(શૂન્ય *opaque, uint8_t *data)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)data;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    જો (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    જો (ctx->મુક્ત)
        ctx->મુક્ત(ctx);

    av_buffer_unref(&ctxi->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(ગણના AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    અચલ HWContextType *hw_type = ખાલી;
    પૂર્ણાંક i;

    માટે (i = 0; hw_table[i]; i++) {
        જો (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            તોડો;
        }
    }
    જો (!hw_type)
        પાછા ખાલી;

    ctxi = av_mallocz(કદ(*ctxi));
    જો (!ctxi)
        પાછા ખાલી;
    ctx = &ctxi->p;

    જો (hw_type->device_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_size);
        જો (!ctx->hwctx)
            જાઓ fail;
    }

    buf = av_buffer_create((uint8_t*)ctx, કદ(*ctx),
                           hwdevice_ctx_free, ખાલી,
                           AV_BUFFER_FLAG_READONLY);
    જો (!buf)
        જાઓ fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    પાછા buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    પાછા ખાલી;
}

પૂર્ણાંક av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->data;
    AVHWDeviceContext *ctx  = &ctxi->p;
    પૂર્ણાંક ret = 0;

    જો (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    પાછા ret;
}

સ્થિર અચલ AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .item_name  = av_default_item_name,
    .version    = LIBAVUTIL_VERSION_INT,
};

સ્થિર શૂન્ય hwframe_ctx_free(શૂન્ય *opaque, uint8_t *data)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)data;
    AVHWFramesContext *ctx  = &ctxi->p;

    જો (ctxi->pool_internal)
        av_buffer_pool_uninit(&ctxi->pool_internal);

    av_buffer_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    જો (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    જો (ctx->મુક્ત)
        ctx->મુક્ત(ctx);

    av_buffer_unref(&ctxi->source_frames);

    av_buffer_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_in)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_in->data;
    અચલ HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = ખાલી;

    ctxi = av_mallocz(કદ(*ctxi));
    જો (!ctxi)
        પાછા ખાલી;
    ctx  = &ctxi->p;

    જો (ff_mutex_init(&ctxi->transfer_pool_lock, ખાલી)) {
        av_free(ctxi);
        પાછા ખાલી;
    }

    જો (hw_type->frames_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_size);
        જો (!ctx->hwctx)
            જાઓ fail;
    }

    device_ref = av_buffer_ref(device_ref_in);
    જો (!device_ref)
        જાઓ fail;

    buf = av_buffer_create((uint8_t*)ctx, કદ(*ctx),
                           hwframe_ctx_free, ખાલી,
                           AV_BUFFER_FLAG_READONLY);
    જો (!buf)
        જાઓ fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    પાછા buf;

fail:
    av_buffer_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    પાછા ખાલી;
}

સ્થિર પૂર્ણાંક hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->data;
    AVFrame **frames;
    પૂર્ણાંક i, ret = 0;

    frames = av_calloc(ctx->initial_pool_size, કદ(*frames));
    જો (!frames)
        પાછા AVERROR(ENOMEM);

    માટે (i = 0; i < ctx->initial_pool_size; i++) {
        frames[i] = av_frame_alloc();
        જો (!frames[i])
            જાઓ fail;

        ret = av_hwframe_get_buffer(ref, frames[i], 0);
        જો (ret < 0)
            જાઓ fail;
    }

fail:
    માટે (i = 0; i < ctx->initial_pool_size; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    પાછા ret;
}

પૂર્ણાંક av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    અચલ ગણના AVPixelFormat *pix_fmt;
    પૂર્ણાંક ret;

    જો (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        પાછા 0;
    }

    /* validate the pixel format */
    માટે (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        જો (*pix_fmt == ctx->format)
            તોડો;
    }
    જો (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        પાછા AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_size(ctx->width, ctx->height, 0, ctx);
    જો (ret < 0)
        પાછા ret;

    /* format-specific init */
    જો (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        જો (ret < 0)
            પાછા ret;
    }

    જો (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    જો (ctx->initial_pool_size > 0) {
        ret = hwframe_pool_prealloc(ref);
        જો (ret < 0)
            પાછા ret;
    }

    પાછા 0;
}

પૂર્ણાંક av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    ગણના AVHWFrameTransferDirection dir,
                                    ગણના AVPixelFormat **formats, પૂર્ણાંક flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;

    જો (!ctxi->hw_type->transfer_get_formats)
        પાછા AVERROR(ENOSYS);

    પાછા ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

સ્થિર શૂન્ય transfer_pool_free(શૂન્ય *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_buffer_unref(&device_ref);
}

સ્થિર AVBufferRef *transfer_buffer_alloc(શૂન્ય *opaque, size_t size)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = ખાલી;

    ff_mutex_lock(&ctxi->transfer_pool_lock);
    જો (ctxi->transfer_pool_size != size) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_buffer_alloc ?
                                  av_buffer_ref(ctxi->p.device_ref) : ખાલી;

        av_buffer_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_buffer_pool_init2(size, device_ref,
                                 ctxi->hw_type->transfer_buffer_alloc,
                                 transfer_pool_free) :
            av_buffer_pool_init(size, ખાલી);
        ctxi->transfer_pool_size = ctxi->transfer_pool ? size : 0;
        જો (!ctxi->transfer_pool)
            av_buffer_unref(&device_ref);
    }
    જો (ctxi->transfer_pool)
        buf = av_buffer_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    પાછા buf ? buf : av_buffer_alloc(size);
}

પૂર્ણાંક av_hwframe_get_transfer_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    પાછા ff_frame_get_video_buffer(frame, 0, transfer_buffer_alloc,
                                     hwframe_ctx->data);
}

સ્થિર પૂર્ણાંક transfer_data_alloc(AVFrame *dst, અચલ AVFrame *src, પૂર્ણાંક flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    પૂર્ણાંક ret = 0;

    જો (!src->hw_frames_ctx)
        પાછા AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;

    frame_tmp = av_frame_alloc();
    જો (!frame_tmp)
        પાછા AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    જો (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } નહીંતર {
        ગણના AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        જો (ret < 0)
            જાઓ fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_buffer(src->hw_frames_ctx, frame_tmp);
    જો (ret < 0)
        જાઓ fail;

    ret = av_hwframe_transfer_data(frame_tmp, src, flags);
    જો (ret < 0)
        જાઓ fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    પાછા ret;
}

પૂર્ણાંક av_hwframe_transfer_data(AVFrame *dst, અચલ AVFrame *src, પૂર્ણાંક flags)
{
    પૂર્ણાંક ret;

    જો (!dst->buf[0])
        પાછા transfer_data_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    જો (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->data;

        જો (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            પાછા AVERROR(ENOSYS);
        }

        જો (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            પાછા AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        જો (src_ctx->hw_type->transfer_data_from)
            ret = src_ctx->hw_type->transfer_data_from(&src_ctx->p, dst, src);
        જો (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_data_to)
            ret = dst_ctx->hw_type->transfer_data_to(&dst_ctx->p, dst, src);
        જો (ret < 0)
            પાછા ret;
    } નહીંતર {
        જો (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->data;

            જો (!ctx->hw_type->transfer_data_from)
                પાછા AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_from(&ctx->p, dst, src);
            જો (ret < 0)
                પાછા ret;
        } નહીંતર જો (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->data;

            જો (!ctx->hw_type->transfer_data_to)
                પાછા AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_to(&ctx->p, dst, src);
            જો (ret < 0)
                પાછા ret;
        } નહીંતર {
            પાછા AVERROR(ENOSYS);
        }
    }
    પાછા 0;
}

પૂર્ણાંક av_hwframe_get_buffer(AVBufferRef *hwframe_ref, AVFrame *frame, પૂર્ણાંક flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    પૂર્ણાંક ret;

    જો (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
        જો (!frame->hw_frames_ctx)
            પાછા AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        જો (!src_frame)
            પાછા AVERROR(ENOMEM);

        ret = av_hwframe_get_buffer(ctxi->source_frames,
                                    src_frame, 0);
        જો (ret < 0) {
            av_frame_free(&src_frame);
            પાછા ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        જો (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            પાછા ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        પાછા 0;
    }

    જો (!ctxi->hw_type->frames_get_buffer)
        પાછા AVERROR(ENOSYS);

    જો (!ctx->pool)
        પાછા AVERROR(EINVAL);

    frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    જો (!frame->hw_frames_ctx)
        પાછા AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_buffer(ctx, frame);
    જો (ret < 0) {
        av_buffer_unref(&frame->hw_frames_ctx);
        પાછા ret;
    }

    frame->extended_data = frame->data;

    પાછા 0;
}

શૂન્ય *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    અચલ HWContextType  *hw_type = ctx->hw_type;

    જો (hw_type->device_hwconfig_size == 0)
        પાછા ખાલી;

    પાછા av_mallocz(hw_type->device_hwconfig_size);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           અચલ શૂન્ય *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    અચલ HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    જો (!hw_type->frames_get_constraints)
        પાછા ખાલી;

    constraints = av_mallocz(કદ(*constraints));
    જો (!constraints)
        પાછા ખાલી;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = INT_MAX;

    જો (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        પાછા constraints;
    } નહીંતર {
        av_hwframe_constraints_free(&constraints);
        પાછા ખાલી;
    }
}

શૂન્ય av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    જો (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

પૂર્ણાંક av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, ગણના AVHWDeviceType type,
                           અચલ અક્ષર *device, AVDictionary *opts, પૂર્ણાંક flags)
{
    AVBufferRef *device_ref = ખાલી;
    FFHWDeviceContext *device_ctx;
    પૂર્ણાંક ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    જો (!device_ref) {
        ret = AVERROR(ENOMEM);
        જાઓ fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->data;

    જો (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        જાઓ fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    જો (ret < 0)
        જાઓ fail;

    ret = av_hwdevice_ctx_init(device_ref);
    જો (ret < 0)
        જાઓ fail;

    *pdevice_ref = device_ref;
    પાછા 0;
fail:
    av_buffer_unref(&device_ref);
    *pdevice_ref = ખાલી;
    પાછા ret;
}

પૂર્ણાંક av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        ગણના AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, પૂર્ણાંક flags)
{
    AVBufferRef *dst_ref = ખાલી, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    પૂર્ણાંક ret = 0;

    tmp_ref = src_ref;
    જ્યારે (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        જો (tmp_ctx->p.type == type) {
            dst_ref = av_buffer_ref(tmp_ref);
            જો (!dst_ref) {
                ret = AVERROR(ENOMEM);
                જાઓ fail;
            }
            જાઓ done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    જો (!dst_ref) {
        ret = AVERROR(ENOMEM);
        જાઓ fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->data;

    tmp_ref = src_ref;
    જ્યારે (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        જો (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            જો (ret == 0) {
                dst_ctx->source_device = av_buffer_ref(src_ref);
                જો (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    જાઓ fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                જો (ret < 0)
                    જાઓ fail;
                જાઓ done;
            }
            જો (ret != AVERROR(ENOSYS))
                જાઓ fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    જાઓ fail;

done:
    *dst_ref_ptr = dst_ref;
    પાછા 0;

fail:
    av_buffer_unref(&dst_ref);
    *dst_ref_ptr = ખાલી;
    પાછા ret;
}

પૂર્ણાંક av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   ગણના AVHWDeviceType type,
                                   AVBufferRef *src_ref, પૂર્ણાંક flags)
{
    પાછા av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               ખાલી, flags);
}

સ્થિર શૂન્ય ff_hwframe_unmap(શૂન્ય *opaque, uint8_t *data)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)data;
    AVHWFramesContext *ctx = opaque;

    જો (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_buffer_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

પૂર્ણાંક ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, અચલ AVFrame *src,
                          શૂન્ય (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          શૂન્ય *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->data;
    HWMapDescriptor *hwmap;
    પૂર્ણાંક ret;

    hwmap = av_mallocz(કદ(*hwmap));
    જો (!hwmap) {
        ret = AVERROR(ENOMEM);
        જાઓ fail;
    }

    hwmap->source = av_frame_alloc();
    જો (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        જાઓ fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    જો (ret < 0)
        જાઓ fail;

    hwmap->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    જો (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        જાઓ fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_buffer_create((uint8_t*)hwmap, કદ(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    જો (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        જાઓ fail;
    }

    પાછા 0;

fail:
    જો (hwmap) {
        av_buffer_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    પાછા ret;
}

પૂર્ણાંક av_hwframe_map(AVFrame *dst, અચલ AVFrame *src, પૂર્ણાંક flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    ગણના AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    પૂર્ણાંક ret;

    જો (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        જો ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->data ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            જો (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                પાછા AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->data;
            પાછા av_frame_replace(dst, hwmap->source);
        }
    }

    જો (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;

        જો (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            જો (ret >= 0)
                પાછા ret;
            નહીંતર જો (ret != AVERROR(ENOSYS))
                જાઓ fail;
        }
    }

    જો (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        જો (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            જો (ret >= 0)
                પાછા ret;
            નહીંતર જો (ret != AVERROR(ENOSYS))
                જાઓ fail;
        }
    }

    પાછા AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_frames == ખાલી ||
               orig_dst_frames == dst->hw_frames_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_frames_ctx = ખાલી;
    av_frame_unref(dst);

    dst->hw_frames_ctx = orig_dst_frames;
    dst->format        = orig_dst_fmt;

    પાછા ret;
}

પૂર્ણાંક av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  ગણના AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  પૂર્ણાંક flags)
{
    AVBufferRef   *dst_ref = ખાલી;
    FFHWFramesContext *dsti = ખાલી;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->data;
    AVHWFramesContext *dst, *src = &srci->p;
    પૂર્ણાંક ret;

    જો (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->data;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->data;

        જો (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_buffer_ref(srci->source_frames);
            જો (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                જાઓ fail;
            }
            પાછા 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    જો (!dst_ref) {
        ret = AVERROR(ENOMEM);
        જાઓ fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->data;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->width     = src->width;
    dst->height    = src->height;

    dsti->source_frames = av_buffer_ref(source_frame_ctx);
    જો (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        જાઓ fail;
    }

    dsti->source_allocation_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_DIRECT);

    ret = AVERROR(ENOSYS);
    જો (srci->hw_type->frames_derive_from)
        ret = srci->hw_type->frames_derive_from(dst, src, flags);
    જો (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->frames_derive_to)
        ret = dsti->hw_type->frames_derive_to(dst, src, flags);
    જો (ret == AVERROR(ENOSYS))
        ret = 0;
    જો (ret)
        જાઓ fail;

    *derived_frame_ctx = dst_ref;
    પાછા 0;

fail:
    જો (dsti)
        av_buffer_unref(&dsti->source_frames);
    av_buffer_unref(&dst_ref);
    પાછા ret;
}

પૂર્ણાંક ff_hwframe_map_replace(AVFrame *dst, અચલ AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->data;
    પાછા av_frame_replace(hwmap->source, src);
}
