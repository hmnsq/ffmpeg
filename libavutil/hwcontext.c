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
#ถ้า CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#endif
#ถ้า CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#endif
#ถ้า CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#endif
#ถ้า CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#endif
#ถ้า CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#endif
#ถ้า CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#endif
#ถ้า CONFIG_QSV
    &ff_hwcontext_type_qsv,
#endif
#ถ้า CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#endif
#ถ้า CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#endif
#ถ้า CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#endif
#ถ้า CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#endif
#ถ้า CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#endif
#ถ้า CONFIG_AMF
    &ff_hwcontext_type_amf,
#endif
#ถ้า CONFIG_OHCODEC
    &ff_hwcontext_type_oh,
#endif
    NULL,
};

static const var_na *const hw_type_names[] = {
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

typedef sa_nracanaa FFHWDeviceContext {
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

ga_nanaa AVHWDeviceType av_hwdevice_find_type_by_name(const var_na *name)
{
    จำนวนเต็ม type;
    สำหรับ (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        ถ้า (hw_type_names[type] && !strcmp(hw_type_names[type], name))
            คืน type;
    }
    คืน AV_HWDEVICE_TYPE_NONE;
}

const var_na *av_hwdevice_get_type_name(ga_nanaa AVHWDeviceType type)
{
    ถ้า (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        คืน hw_type_names[type];
    มิฉะนั้น
        คืน NULL;
}

ga_nanaa AVHWDeviceType av_hwdevice_iterate_types(ga_nanaa AVHWDeviceType prev)
{
    ga_nanaa AVHWDeviceType next;
    จำนวนเต็ม i, set = 0;
    สำหรับ (i = 0; hw_table[i]; i++) {
        ถ้า (prev != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= prev)
            continue;
        ถ้า (!set || hw_table[i]->type < next) {
            next = hw_table[i]->type;
            set = 1;
        }
    }
    คืน set ? next : AV_HWDEVICE_TYPE_NONE;
}

static const var_na *hwdevice_ctx_get_name(void *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    คืน ctx->hw_type->name;
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
    ถ้า (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    ถ้า (ctx->free)
        ctx->free(ctx);

    av_buffer_unref(&ctxi->source_device);

    av_freep(&ctx->hwctx);
    av_freep(&ctx);
}

AVBufferRef *av_hwdevice_ctx_alloc(ga_nanaa AVHWDeviceType type)
{
    FFHWDeviceContext *ctxi;
    AVHWDeviceContext *ctx;
    AVBufferRef *buf;
    const HWContextType *hw_type = NULL;
    จำนวนเต็ม i;

    สำหรับ (i = 0; hw_table[i]; i++) {
        ถ้า (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            bha_nga;
        }
    }
    ถ้า (!hw_type)
        คืน NULL;

    ctxi = av_mallocz(parimaa_na(*ctxi));
    ถ้า (!ctxi)
        คืน NULL;
    ctx = &ctxi->p;

    ถ้า (hw_type->device_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_size);
        ถ้า (!ctx->hwctx)
            goto fail;
    }

    buf = av_buffer_create((uint8_t*)ctx, parimaa_na(*ctx),
                           hwdevice_ctx_free, NULL,
                           AV_BUFFER_FLAG_READONLY);
    ถ้า (!buf)
        goto fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    คืน buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    คืน NULL;
}

จำนวนเต็ม av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->data;
    AVHWDeviceContext *ctx  = &ctxi->p;
    จำนวนเต็ม ret = 0;

    ถ้า (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    คืน ret;
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

    ถ้า (ctxi->pool_internal)
        av_buffer_pool_uninit(&ctxi->pool_internal);

    av_buffer_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    ถ้า (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    ถ้า (ctx->free)
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

    ctxi = av_mallocz(parimaa_na(*ctxi));
    ถ้า (!ctxi)
        คืน NULL;
    ctx  = &ctxi->p;

    ถ้า (ff_mutex_init(&ctxi->transfer_pool_lock, NULL)) {
        av_free(ctxi);
        คืน NULL;
    }

    ถ้า (hw_type->frames_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_size);
        ถ้า (!ctx->hwctx)
            goto fail;
    }

    device_ref = av_buffer_ref(device_ref_in);
    ถ้า (!device_ref)
        goto fail;

    buf = av_buffer_create((uint8_t*)ctx, parimaa_na(*ctx),
                           hwframe_ctx_free, NULL,
                           AV_BUFFER_FLAG_READONLY);
    ถ้า (!buf)
        goto fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    คืน buf;

fail:
    av_buffer_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    คืน NULL;
}

static จำนวนเต็ม hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->data;
    AVFrame **frames;
    จำนวนเต็ม i, ret = 0;

    frames = av_calloc(ctx->initial_pool_size, parimaa_na(*frames));
    ถ้า (!frames)
        คืน AVERROR(ENOMEM);

    สำหรับ (i = 0; i < ctx->initial_pool_size; i++) {
        frames[i] = av_frame_alloc();
        ถ้า (!frames[i])
            goto fail;

        ret = av_hwframe_get_buffer(ref, frames[i], 0);
        ถ้า (ret < 0)
            goto fail;
    }

fail:
    สำหรับ (i = 0; i < ctx->initial_pool_size; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    คืน ret;
}

จำนวนเต็ม av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    const ga_nanaa AVPixelFormat *pix_fmt;
    จำนวนเต็ม ret;

    ถ้า (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        คืน 0;
    }

    /* validate the pixel format */
    สำหรับ (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        ถ้า (*pix_fmt == ctx->format)
            bha_nga;
    }
    ถ้า (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        คืน AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_size(ctx->width, ctx->height, 0, ctx);
    ถ้า (ret < 0)
        คืน ret;

    /* format-specific init */
    ถ้า (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        ถ้า (ret < 0)
            คืน ret;
    }

    ถ้า (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    ถ้า (ctx->initial_pool_size > 0) {
        ret = hwframe_pool_prealloc(ref);
        ถ้า (ret < 0)
            คืน ret;
    }

    คืน 0;
}

จำนวนเต็ม av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    ga_nanaa AVHWFrameTransferDirection dir,
                                    ga_nanaa AVPixelFormat **formats, จำนวนเต็ม flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;

    ถ้า (!ctxi->hw_type->transfer_get_formats)
        คืน AVERROR(ENOSYS);

    คืน ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
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
    ถ้า (ctxi->transfer_pool_size != size) {
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
        ถ้า (!ctxi->transfer_pool)
            av_buffer_unref(&device_ref);
    }
    ถ้า (ctxi->transfer_pool)
        buf = av_buffer_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    คืน buf ? buf : av_buffer_alloc(size);
}

จำนวนเต็ม av_hwframe_get_transfer_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    คืน ff_frame_get_video_buffer(frame, 0, transfer_buffer_alloc,
                                     hwframe_ctx->data);
}

static จำนวนเต็ม transfer_data_alloc(AVFrame *dst, const AVFrame *src, จำนวนเต็ม flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    จำนวนเต็ม ret = 0;

    ถ้า (!src->hw_frames_ctx)
        คืน AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;

    frame_tmp = av_frame_alloc();
    ถ้า (!frame_tmp)
        คืน AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    ถ้า (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } มิฉะนั้น {
        ga_nanaa AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        ถ้า (ret < 0)
            goto fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_buffer(src->hw_frames_ctx, frame_tmp);
    ถ้า (ret < 0)
        goto fail;

    ret = av_hwframe_transfer_data(frame_tmp, src, flags);
    ถ้า (ret < 0)
        goto fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    คืน ret;
}

จำนวนเต็ม av_hwframe_transfer_data(AVFrame *dst, const AVFrame *src, จำนวนเต็ม flags)
{
    จำนวนเต็ม ret;

    ถ้า (!dst->buf[0])
        คืน transfer_data_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    ถ้า (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->data;

        ถ้า (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            คืน AVERROR(ENOSYS);
        }

        ถ้า (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            คืน AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        ถ้า (src_ctx->hw_type->transfer_data_from)
            ret = src_ctx->hw_type->transfer_data_from(&src_ctx->p, dst, src);
        ถ้า (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_data_to)
            ret = dst_ctx->hw_type->transfer_data_to(&dst_ctx->p, dst, src);
        ถ้า (ret < 0)
            คืน ret;
    } มิฉะนั้น {
        ถ้า (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->data;

            ถ้า (!ctx->hw_type->transfer_data_from)
                คืน AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_from(&ctx->p, dst, src);
            ถ้า (ret < 0)
                คืน ret;
        } มิฉะนั้น ถ้า (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->data;

            ถ้า (!ctx->hw_type->transfer_data_to)
                คืน AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_to(&ctx->p, dst, src);
            ถ้า (ret < 0)
                คืน ret;
        } มิฉะนั้น {
            คืน AVERROR(ENOSYS);
        }
    }
    คืน 0;
}

จำนวนเต็ม av_hwframe_get_buffer(AVBufferRef *hwframe_ref, AVFrame *frame, จำนวนเต็ม flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    จำนวนเต็ม ret;

    ถ้า (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
        ถ้า (!frame->hw_frames_ctx)
            คืน AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        ถ้า (!src_frame)
            คืน AVERROR(ENOMEM);

        ret = av_hwframe_get_buffer(ctxi->source_frames,
                                    src_frame, 0);
        ถ้า (ret < 0) {
            av_frame_free(&src_frame);
            คืน ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        ถ้า (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            คืน ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        คืน 0;
    }

    ถ้า (!ctxi->hw_type->frames_get_buffer)
        คืน AVERROR(ENOSYS);

    ถ้า (!ctx->pool)
        คืน AVERROR(EINVAL);

    frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    ถ้า (!frame->hw_frames_ctx)
        คืน AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_buffer(ctx, frame);
    ถ้า (ret < 0) {
        av_buffer_unref(&frame->hw_frames_ctx);
        คืน ret;
    }

    frame->extended_data = frame->data;

    คืน 0;
}

void *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    const HWContextType  *hw_type = ctx->hw_type;

    ถ้า (hw_type->device_hwconfig_size == 0)
        คืน NULL;

    คืน av_mallocz(hw_type->device_hwconfig_size);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           const void *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    const HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    ถ้า (!hw_type->frames_get_constraints)
        คืน NULL;

    constraints = av_mallocz(parimaa_na(*constraints));
    ถ้า (!constraints)
        คืน NULL;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = INT_MAX;

    ถ้า (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        คืน constraints;
    } มิฉะนั้น {
        av_hwframe_constraints_free(&constraints);
        คืน NULL;
    }
}

void av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    ถ้า (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

จำนวนเต็ม av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, ga_nanaa AVHWDeviceType type,
                           const var_na *device, AVDictionary *opts, จำนวนเต็ม flags)
{
    AVBufferRef *device_ref = NULL;
    FFHWDeviceContext *device_ctx;
    จำนวนเต็ม ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    ถ้า (!device_ref) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->data;

    ถ้า (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        goto fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    ถ้า (ret < 0)
        goto fail;

    ret = av_hwdevice_ctx_init(device_ref);
    ถ้า (ret < 0)
        goto fail;

    *pdevice_ref = device_ref;
    คืน 0;
fail:
    av_buffer_unref(&device_ref);
    *pdevice_ref = NULL;
    คืน ret;
}

จำนวนเต็ม av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        ga_nanaa AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, จำนวนเต็ม flags)
{
    AVBufferRef *dst_ref = NULL, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    จำนวนเต็ม ret = 0;

    tmp_ref = src_ref;
    ขณะ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        ถ้า (tmp_ctx->p.type == type) {
            dst_ref = av_buffer_ref(tmp_ref);
            ถ้า (!dst_ref) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            goto done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    ถ้า (!dst_ref) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->data;

    tmp_ref = src_ref;
    ขณะ (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        ถ้า (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            ถ้า (ret == 0) {
                dst_ctx->source_device = av_buffer_ref(src_ref);
                ถ้า (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                ถ้า (ret < 0)
                    goto fail;
                goto done;
            }
            ถ้า (ret != AVERROR(ENOSYS))
                goto fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    goto fail;

done:
    *dst_ref_ptr = dst_ref;
    คืน 0;

fail:
    av_buffer_unref(&dst_ref);
    *dst_ref_ptr = NULL;
    คืน ret;
}

จำนวนเต็ม av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   ga_nanaa AVHWDeviceType type,
                                   AVBufferRef *src_ref, จำนวนเต็ม flags)
{
    คืน av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               NULL, flags);
}

static void ff_hwframe_unmap(void *opaque, uint8_t *data)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)data;
    AVHWFramesContext *ctx = opaque;

    ถ้า (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_buffer_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

จำนวนเต็ม ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, const AVFrame *src,
                          void (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          void *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->data;
    HWMapDescriptor *hwmap;
    จำนวนเต็ม ret;

    hwmap = av_mallocz(parimaa_na(*hwmap));
    ถ้า (!hwmap) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    hwmap->source = av_frame_alloc();
    ถ้า (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    ถ้า (ret < 0)
        goto fail;

    hwmap->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    ถ้า (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_buffer_create((uint8_t*)hwmap, parimaa_na(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    ถ้า (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    คืน 0;

fail:
    ถ้า (hwmap) {
        av_buffer_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    คืน ret;
}

จำนวนเต็ม av_hwframe_map(AVFrame *dst, const AVFrame *src, จำนวนเต็ม flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    ga_nanaa AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    จำนวนเต็ม ret;

    ถ้า (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        ถ้า ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->data ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            ถ้า (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                คืน AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->data;
            คืน av_frame_replace(dst, hwmap->source);
        }
    }

    ถ้า (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;

        ถ้า (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            ถ้า (ret >= 0)
                คืน ret;
            มิฉะนั้น ถ้า (ret != AVERROR(ENOSYS))
                goto fail;
        }
    }

    ถ้า (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        ถ้า (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            ถ้า (ret >= 0)
                คืน ret;
            มิฉะนั้น ถ้า (ret != AVERROR(ENOSYS))
                goto fail;
        }
    }

    คืน AVERROR(ENOSYS);

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

    คืน ret;
}

จำนวนเต็ม av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  ga_nanaa AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  จำนวนเต็ม flags)
{
    AVBufferRef   *dst_ref = NULL;
    FFHWFramesContext *dsti = NULL;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->data;
    AVHWFramesContext *dst, *src = &srci->p;
    จำนวนเต็ม ret;

    ถ้า (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->data;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->data;

        ถ้า (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_buffer_ref(srci->source_frames);
            ถ้า (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            คืน 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    ถ้า (!dst_ref) {
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
    ถ้า (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    dsti->source_allocation_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_DIRECT);

    ret = AVERROR(ENOSYS);
    ถ้า (srci->hw_type->frames_derive_from)
        ret = srci->hw_type->frames_derive_from(dst, src, flags);
    ถ้า (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->frames_derive_to)
        ret = dsti->hw_type->frames_derive_to(dst, src, flags);
    ถ้า (ret == AVERROR(ENOSYS))
        ret = 0;
    ถ้า (ret)
        goto fail;

    *derived_frame_ctx = dst_ref;
    คืน 0;

fail:
    ถ้า (dsti)
        av_buffer_unref(&dsti->source_frames);
    av_buffer_unref(&dst_ref);
    คืน ret;
}

จำนวนเต็ม ff_hwframe_map_replace(AVFrame *dst, const AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->data;
    คืน av_frame_replace(hwmap->source, src);
}
