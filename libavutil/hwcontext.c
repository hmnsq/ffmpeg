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

#include "config.h"

#include "avassert.h"
#include "buffer.h"
#include "common.h"
#include "frame_internal.h"
#include "hwcontext.h"
#include "hwcontext_internal.h"
#include "imgutils.h"
#include "log.h"
#include "mem.h"
#include "pixdesc.h"
#include "pixfmt.h"

static const HWContextType * const hw_table[] = {
#nếu CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#endif
#nếu CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#endif
#nếu CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#endif
#nếu CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#endif
#nếu CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#endif
#nếu CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#endif
#nếu CONFIG_QSV
    &ff_hwcontext_type_qsv,
#endif
#nếu CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#endif
#nếu CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#endif
#nếu CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#endif
#nếu CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#endif
#nếu CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#endif
#nếu CONFIG_AMF
    &ff_hwcontext_type_amf,
#endif
#nếu CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#endif
    NULL,
};

static const char *const hw_type_names[] = {
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

typedef struct FFHWDeviceContext {
    /**
     * The public AVHWDeviceContext. See hwcontext.h for it.
     */
    AVHWDeviceContext p;

    const HWContextType *hw_type;

    /**
     * For a derived device, a reference to the original device
     * context it was derived from.
     */
    AVBufferRef *source_device;
} FFHWDeviceContext;

enum AVHWDeviceType av_hwdevice_find_type_by_name(const char *name)
{
    số_nguyên type;
    cho (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        nếu (hw_type_names[type] && !strcmp(hw_type_names[type], name))
            trả_về type;
    }
    trả_về AV_HWDEVICE_TYPE_NONE;
}

const char *av_hwdevice_get_type_name(enum AVHWDeviceType type)
{
    nếu (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        trả_về hw_type_names[type];
    không_thì
        trả_về NULL;
}

enum AVHWDeviceType av_hwdevice_iterate_types(enum AVHWDeviceType prev)
{
    enum AVHWDeviceType next;
    số_nguyên i, set = 0;
    cho (i = 0; hw_table[i]; i++) {
        nếu (prev != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= prev)
            continue;
        nếu (!set || hw_table[i]->type < next) {
            next = hw_table[i]->type;
            set = 1;
        }
    }
    trả_về set ? next : AV_HWDEVICE_TYPE_NONE;
}

static const char *hwdevice_ctx_get_name(void *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    trả_về ctx->hw_type->name;
}

static const AVClass hwdevice_ctx_class = {
    .class_name = "AVHWDeviceContext",
    .item_name  = hwdevice_ctx_get_name,
    .category   = AV_CLASS_CATEGORY_HWDEVICE,
    .version    = LIBAVUTIL_VERSION_INT,
};

static void hwdevice_ctx_free(void *opaque, uint8_t *data)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)data;
    AVHWDeviceContext *ctx  = &ctxi->p;

    /* uninit might still want access the hw context and the user
     * free() callback might destroy it, so uninit has to be called first */
    nếu (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    nếu (ctx->free)
        ctx->free(ctx);

    av_buffer_unref(&ctxi->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(enum AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    const HWContextType *hw_type = NULL;
    số_nguyên i;

    cho (i = 0; hw_table[i]; i++) {
        nếu (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            break;
        }
    }
    nếu (!hw_type)
        trả_về NULL;

    ctxi = av_mallocz(sizeof(*ctxi));
    nếu (!ctxi)
        trả_về NULL;
    ctx = &ctxi->p;

    nếu (hw_type->device_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_size);
        nếu (!ctx->hwctx)
            goto fail;
    }

    buf = av_buffer_create((uint8_t*)ctx, sizeof(*ctx),
                           hwdevice_ctx_free, NULL,
                           AV_BUFFER_FLAG_READONLY);
    nếu (!buf)
        goto fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    trả_về buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    trả_về NULL;
}

số_nguyên av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->data;
    AVHWDeviceContext *ctx  = &ctxi->p;
    số_nguyên ret = 0;

    nếu (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    trả_về ret;
}

static const AVClass hwframe_ctx_class = {
    .class_name = "AVHWFramesContext",
    .item_name  = av_default_item_name,
    .version    = LIBAVUTIL_VERSION_INT,
};

static void hwframe_ctx_free(void *opaque, uint8_t *data)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)data;
    AVHWFramesContext *ctx  = &ctxi->p;

    nếu (ctxi->pool_internal)
        av_buffer_pool_uninit(&ctxi->pool_internal);

    av_buffer_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    nếu (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    nếu (ctx->free)
        ctx->free(ctx);

    av_buffer_unref(&ctxi->source_frames);

    av_buffer_unref(&ctx->device_ref);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwframe_ctx_alloc(AVBufferRef *device_ref_in)
{
    FFHWDeviceContext *device_ctx = (FFHWDeviceContext*)device_ref_in->data;
    const HWContextType  *hw_type = device_ctx->hw_type;
    FFHWFramesContext *ctxi;
    AVHWFramesContext *ctx;
    AVBufferRef *buf, *device_ref = NULL;

    ctxi = av_mallocz(sizeof(*ctxi));
    nếu (!ctxi)
        trả_về NULL;
    ctx  = &ctxi->p;

    nếu (ff_mutex_init(&ctxi->transfer_pool_lock, NULL)) {
        av_free(ctxi);
        trả_về NULL;
    }

    nếu (hw_type->frames_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_size);
        nếu (!ctx->hwctx)
            goto fail;
    }

    device_ref = av_buffer_ref(device_ref_in);
    nếu (!device_ref)
        goto fail;

    buf = av_buffer_create((uint8_t*)ctx, sizeof(*ctx),
                           hwframe_ctx_free, NULL,
                           AV_BUFFER_FLAG_READONLY);
    nếu (!buf)
        goto fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    trả_về buf;

fail:
    av_buffer_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    trả_về NULL;
}

static số_nguyên hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->data;
    AVFrame **frames;
    số_nguyên i, ret = 0;

    frames = av_calloc(ctx->initial_pool_size, sizeof(*frames));
    nếu (!frames)
        trả_về AVERROR(ENOMEM);

    cho (i = 0; i < ctx->initial_pool_size; i++) {
        frames[i] = av_frame_alloc();
        nếu (!frames[i])
            goto fail;

        ret = av_hwframe_get_buffer(ref, frames[i], 0);
        nếu (ret < 0)
            goto fail;
    }

fail:
    cho (i = 0; i < ctx->initial_pool_size; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    trả_về ret;
}

số_nguyên av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    const enum AVPixelFormat *pix_fmt;
    số_nguyên ret;

    nếu (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        trả_về 0;
    }

    /* validate the pixel format */
    cho (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        nếu (*pix_fmt == ctx->format)
            break;
    }
    nếu (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        trả_về AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_size(ctx->width, ctx->height, 0, ctx);
    nếu (ret < 0)
        trả_về ret;

    /* format-specific init */
    nếu (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        nếu (ret < 0)
            trả_về ret;
    }

    nếu (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    nếu (ctx->initial_pool_size > 0) {
        ret = hwframe_pool_prealloc(ref);
        nếu (ret < 0)
            trả_về ret;
    }

    trả_về 0;
}

số_nguyên av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    enum AVHWFrameTransferDirection dir,
                                    enum AVPixelFormat **formats, số_nguyên flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;

    nếu (!ctxi->hw_type->transfer_get_formats)
        trả_về AVERROR(ENOSYS);

    trả_về ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
}

static void transfer_pool_free(void *opaque)
{
    AVBufferRef *device_ref = opaque;
    av_buffer_unref(&device_ref);
}

static AVBufferRef *transfer_buffer_alloc(void *opaque, size_t size)
{
    FFHWFramesContext *ctxi = opaque;
    AVBufferRef *buf = NULL;

    ff_mutex_lock(&ctxi->transfer_pool_lock);
    nếu (ctxi->transfer_pool_size != size) {
        /* buffers of the hardware context type need the device to be freed */
        AVBufferRef *device_ref = ctxi->hw_type->transfer_buffer_alloc ?
                                  av_buffer_ref(ctxi->p.device_ref) : NULL;

        av_buffer_pool_uninit(&ctxi->transfer_pool);
        ctxi->transfer_pool      = device_ref ?
            av_buffer_pool_init2(size, device_ref,
                                 ctxi->hw_type->transfer_buffer_alloc,
                                 transfer_pool_free) :
            av_buffer_pool_init(size, NULL);
        ctxi->transfer_pool_size = ctxi->transfer_pool ? size : 0;
        nếu (!ctxi->transfer_pool)
            av_buffer_unref(&device_ref);
    }
    nếu (ctxi->transfer_pool)
        buf = av_buffer_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    trả_về buf ? buf : av_buffer_alloc(size);
}

số_nguyên av_hwframe_get_transfer_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    trả_về ff_frame_get_video_buffer(frame, 0, transfer_buffer_alloc,
                                     hwframe_ctx->data);
}

static số_nguyên transfer_data_alloc(AVFrame *dst, const AVFrame *src, số_nguyên flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    số_nguyên ret = 0;

    nếu (!src->hw_frames_ctx)
        trả_về AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;

    frame_tmp = av_frame_alloc();
    nếu (!frame_tmp)
        trả_về AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    nếu (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } không_thì {
        enum AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        nếu (ret < 0)
            goto fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_buffer(src->hw_frames_ctx, frame_tmp);
    nếu (ret < 0)
        goto fail;

    ret = av_hwframe_transfer_data(frame_tmp, src, flags);
    nếu (ret < 0)
        goto fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    trả_về ret;
}

số_nguyên av_hwframe_transfer_data(AVFrame *dst, const AVFrame *src, số_nguyên flags)
{
    số_nguyên ret;

    nếu (!dst->buf[0])
        trả_về transfer_data_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    nếu (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->data;

        nếu (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            trả_về AVERROR(ENOSYS);
        }

        nếu (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            trả_về AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        nếu (src_ctx->hw_type->transfer_data_from)
            ret = src_ctx->hw_type->transfer_data_from(&src_ctx->p, dst, src);
        nếu (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_data_to)
            ret = dst_ctx->hw_type->transfer_data_to(&dst_ctx->p, dst, src);
        nếu (ret < 0)
            trả_về ret;
    } không_thì {
        nếu (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->data;

            nếu (!ctx->hw_type->transfer_data_from)
                trả_về AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_from(&ctx->p, dst, src);
            nếu (ret < 0)
                trả_về ret;
        } không_thì nếu (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->data;

            nếu (!ctx->hw_type->transfer_data_to)
                trả_về AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_to(&ctx->p, dst, src);
            nếu (ret < 0)
                trả_về ret;
        } không_thì {
            trả_về AVERROR(ENOSYS);
        }
    }
    trả_về 0;
}

số_nguyên av_hwframe_get_buffer(AVBufferRef *hwframe_ref, AVFrame *frame, số_nguyên flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    số_nguyên ret;

    nếu (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
        nếu (!frame->hw_frames_ctx)
            trả_về AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        nếu (!src_frame)
            trả_về AVERROR(ENOMEM);

        ret = av_hwframe_get_buffer(ctxi->source_frames,
                                    src_frame, 0);
        nếu (ret < 0) {
            av_frame_free(&src_frame);
            trả_về ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        nếu (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            trả_về ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        trả_về 0;
    }

    nếu (!ctxi->hw_type->frames_get_buffer)
        trả_về AVERROR(ENOSYS);

    nếu (!ctx->pool)
        trả_về AVERROR(EINVAL);

    frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    nếu (!frame->hw_frames_ctx)
        trả_về AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_buffer(ctx, frame);
    nếu (ret < 0) {
        av_buffer_unref(&frame->hw_frames_ctx);
        trả_về ret;
    }

    frame->extended_data = frame->data;

    trả_về 0;
}

void *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    const HWContextType  *hw_type = ctx->hw_type;

    nếu (hw_type->device_hwconfig_size == 0)
        trả_về NULL;

    trả_về av_mallocz(hw_type->device_hwconfig_size);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           const void *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    const HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    nếu (!hw_type->frames_get_constraints)
        trả_về NULL;

    constraints = av_mallocz(sizeof(*constraints));
    nếu (!constraints)
        trả_về NULL;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = INT_MAX;

    nếu (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        trả_về constraints;
    } không_thì {
        av_hwframe_constraints_free(&constraints);
        trả_về NULL;
    }
}

void av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    nếu (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

số_nguyên av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, enum AVHWDeviceType type,
                           const char *device, AVDictionary *opts, số_nguyên flags)
{
    AVBufferRef *device_ref = NULL;
    FFHWDeviceContext *device_ctx;
    số_nguyên ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    nếu (!device_ref) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->data;

    nếu (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        goto fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    nếu (ret < 0)
        goto fail;

    ret = av_hwdevice_ctx_init(device_ref);
    nếu (ret < 0)
        goto fail;

    *pdevice_ref = device_ref;
    trả_về 0;
fail:
    av_buffer_unref(&device_ref);
    *pdevice_ref = NULL;
    trả_về ret;
}

số_nguyên av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        enum AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, số_nguyên flags)
{
    AVBufferRef *dst_ref = NULL, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    số_nguyên ret = 0;

    tmp_ref = src_ref;
    trong_khi (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        nếu (tmp_ctx->p.type == type) {
            dst_ref = av_buffer_ref(tmp_ref);
            nếu (!dst_ref) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            goto done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    nếu (!dst_ref) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->data;

    tmp_ref = src_ref;
    trong_khi (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        nếu (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            nếu (ret == 0) {
                dst_ctx->source_device = av_buffer_ref(src_ref);
                nếu (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                nếu (ret < 0)
                    goto fail;
                goto done;
            }
            nếu (ret != AVERROR(ENOSYS))
                goto fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    goto fail;

done:
    *dst_ref_ptr = dst_ref;
    trả_về 0;

fail:
    av_buffer_unref(&dst_ref);
    *dst_ref_ptr = NULL;
    trả_về ret;
}

số_nguyên av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   enum AVHWDeviceType type,
                                   AVBufferRef *src_ref, số_nguyên flags)
{
    trả_về av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               NULL, flags);
}

static void ff_hwframe_unmap(void *opaque, uint8_t *data)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)data;
    AVHWFramesContext *ctx = opaque;

    nếu (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_buffer_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

số_nguyên ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, const AVFrame *src,
                          void (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          void *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->data;
    HWMapDescriptor *hwmap;
    số_nguyên ret;

    hwmap = av_mallocz(sizeof(*hwmap));
    nếu (!hwmap) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    hwmap->source = av_frame_alloc();
    nếu (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    nếu (ret < 0)
        goto fail;

    hwmap->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    nếu (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_buffer_create((uint8_t*)hwmap, sizeof(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    nếu (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    trả_về 0;

fail:
    nếu (hwmap) {
        av_buffer_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    trả_về ret;
}

số_nguyên av_hwframe_map(AVFrame *dst, const AVFrame *src, số_nguyên flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    enum AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    số_nguyên ret;

    nếu (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        nếu ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->data ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            nếu (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                trả_về AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->data;
            trả_về av_frame_replace(dst, hwmap->source);
        }
    }

    nếu (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;

        nếu (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            nếu (ret >= 0)
                trả_về ret;
            không_thì nếu (ret != AVERROR(ENOSYS))
                goto fail;
        }
    }

    nếu (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        nếu (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            nếu (ret >= 0)
                trả_về ret;
            không_thì nếu (ret != AVERROR(ENOSYS))
                goto fail;
        }
    }

    trả_về AVERROR(ENOSYS);

fail:
    // if the caller provided dst frames context, it should be preserved
    // by this function
    av_assert0(orig_dst_frames == NULL ||
               orig_dst_frames == dst->hw_frames_ctx);

    // preserve user-provided dst frame fields, but clean
    // anything we might have set
    dst->hw_frames_ctx = NULL;
    av_frame_unref(dst);

    dst->hw_frames_ctx = orig_dst_frames;
    dst->format        = orig_dst_fmt;

    trả_về ret;
}

số_nguyên av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  enum AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  số_nguyên flags)
{
    AVBufferRef   *dst_ref = NULL;
    FFHWFramesContext *dsti = NULL;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->data;
    AVHWFramesContext *dst, *src = &srci->p;
    số_nguyên ret;

    nếu (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->data;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->data;

        nếu (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_buffer_ref(srci->source_frames);
            nếu (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            trả_về 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    nếu (!dst_ref) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    dsti = (FFHWFramesContext*)dst_ref->data;
    dst  = &dsti->p;

    dst->format    = format;
    dst->sw_format = src->sw_format;
    dst->width     = src->width;
    dst->height    = src->height;

    dsti->source_frames = av_buffer_ref(source_frame_ctx);
    nếu (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    dsti->source_allocation_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_DIRECT);

    ret = AVERROR(ENOSYS);
    nếu (srci->hw_type->frames_derive_from)
        ret = srci->hw_type->frames_derive_from(dst, src, flags);
    nếu (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->frames_derive_to)
        ret = dsti->hw_type->frames_derive_to(dst, src, flags);
    nếu (ret == AVERROR(ENOSYS))
        ret = 0;
    nếu (ret)
        goto fail;

    *derived_frame_ctx = dst_ref;
    trả_về 0;

fail:
    nếu (dsti)
        av_buffer_unref(&dsti->source_frames);
    av_buffer_unref(&dst_ref);
    trả_về ret;
}

số_nguyên ff_hwframe_map_replace(AVFrame *dst, const AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->data;
    trả_về av_frame_replace(hwmap->source, src);
}
