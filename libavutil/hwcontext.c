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
#အကယ်၍ CONFIG_CUDA
    &ff_hwcontext_type_cuda,
#endif
#အကယ်၍ CONFIG_D3D11VA
    &ff_hwcontext_type_d3d11va,
#endif
#အကယ်၍ CONFIG_D3D12VA
    &ff_hwcontext_type_d3d12va,
#endif
#အကယ်၍ CONFIG_LIBDRM
    &ff_hwcontext_type_drm,
#endif
#အကယ်၍ CONFIG_DXVA2
    &ff_hwcontext_type_dxva2,
#endif
#အကယ်၍ CONFIG_OPENCL
    &ff_hwcontext_type_opencl,
#endif
#အကယ်၍ CONFIG_QSV
    &ff_hwcontext_type_qsv,
#endif
#အကယ်၍ CONFIG_VAAPI
    &ff_hwcontext_type_vaapi,
#endif
#အကယ်၍ CONFIG_VDPAU
    &ff_hwcontext_type_vdpau,
#endif
#အကယ်၍ CONFIG_VIDEOTOOLBOX
    &ff_hwcontext_type_videotoolbox,
#endif
#အကယ်၍ CONFIG_MEDIACODEC
    &ff_hwcontext_type_mediacodec,
#endif
#အကယ်၍ CONFIG_VULKAN
    &ff_hwcontext_type_vulkan,
#endif
#အကယ်၍ CONFIG_AMF
    &ff_hwcontext_type_amf,
#endif
#အကယ်၍ CONFIG_OHCODEC
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
    ကိန်းပြည့် type;
    အတွက် (type = 0; type < FF_ARRAY_ELEMS(hw_type_names); type++) {
        အကယ်၍ (hw_type_names[type] && !strcmp(hw_type_names[type], name))
            ပြန်ပေး type;
    }
    ပြန်ပေး AV_HWDEVICE_TYPE_NONE;
}

const var_na *av_hwdevice_get_type_name(ga_nanaa AVHWDeviceType type)
{
    အကယ်၍ (type > AV_HWDEVICE_TYPE_NONE &&
        type < FF_ARRAY_ELEMS(hw_type_names))
        ပြန်ပေး hw_type_names[type];
    မဟုတ်ပါက
        ပြန်ပေး NULL;
}

ga_nanaa AVHWDeviceType av_hwdevice_iterate_types(ga_nanaa AVHWDeviceType prev)
{
    ga_nanaa AVHWDeviceType next;
    ကိန်းပြည့် i, set = 0;
    အတွက် (i = 0; hw_table[i]; i++) {
        အကယ်၍ (prev != AV_HWDEVICE_TYPE_NONE && hw_table[i]->type <= prev)
            continue;
        အကယ်၍ (!set || hw_table[i]->type < next) {
            next = hw_table[i]->type;
            set = 1;
        }
    }
    ပြန်ပေး set ? next : AV_HWDEVICE_TYPE_NONE;
}

static const var_na *hwdevice_ctx_get_name(void *ptr)
{
    FFHWDeviceContext *ctx = ptr;
    ပြန်ပေး ctx->hw_type->name;
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
    အကယ်၍ (ctxi->hw_type->device_uninit)
        ctxi->hw_type->device_uninit(ctx);

    အကယ်၍ (ctx->free)
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
    ကိန်းပြည့် i;

    အတွက် (i = 0; hw_table[i]; i++) {
        အကယ်၍ (hw_table[i]->type == type) {
            hw_type = hw_table[i];
            bha_nga;
        }
    }
    အကယ်၍ (!hw_type)
        ပြန်ပေး NULL;

    ctxi = av_mallocz(parimaa_na(*ctxi));
    အကယ်၍ (!ctxi)
        ပြန်ပေး NULL;
    ctx = &ctxi->p;

    အကယ်၍ (hw_type->device_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->device_hwctx_size);
        အကယ်၍ (!ctx->hwctx)
            goto fail;
    }

    buf = av_buffer_create((uint8_t*)ctx, parimaa_na(*ctx),
                           hwdevice_ctx_free, NULL,
                           AV_BUFFER_FLAG_READONLY);
    အကယ်၍ (!buf)
        goto fail;

    ctx->type     = type;
    ctx->av_class = &hwdevice_ctx_class;

    ctxi->hw_type = hw_type;

    ပြန်ပေး buf;

fail:
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ပြန်ပေး NULL;
}

ကိန်းပြည့် av_hwdevice_ctx_init(AVBufferRef *ref)
{
    FFHWDeviceContext *ctxi = (FFHWDeviceContext*)ref->data;
    AVHWDeviceContext *ctx  = &ctxi->p;
    ကိန်းပြည့် ret = 0;

    အကယ်၍ (ctxi->hw_type->device_init)
        ret = ctxi->hw_type->device_init(ctx);

    ပြန်ပေး ret;
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

    အကယ်၍ (ctxi->pool_internal)
        av_buffer_pool_uninit(&ctxi->pool_internal);

    av_buffer_pool_uninit(&ctxi->transfer_pool);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);

    အကယ်၍ (ctxi->hw_type->frames_uninit)
        ctxi->hw_type->frames_uninit(ctx);

    အကယ်၍ (ctx->free)
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
    အကယ်၍ (!ctxi)
        ပြန်ပေး NULL;
    ctx  = &ctxi->p;

    အကယ်၍ (ff_mutex_init(&ctxi->transfer_pool_lock, NULL)) {
        av_free(ctxi);
        ပြန်ပေး NULL;
    }

    အကယ်၍ (hw_type->frames_hwctx_size) {
        ctx->hwctx = av_mallocz(hw_type->frames_hwctx_size);
        အကယ်၍ (!ctx->hwctx)
            goto fail;
    }

    device_ref = av_buffer_ref(device_ref_in);
    အကယ်၍ (!device_ref)
        goto fail;

    buf = av_buffer_create((uint8_t*)ctx, parimaa_na(*ctx),
                           hwframe_ctx_free, NULL,
                           AV_BUFFER_FLAG_READONLY);
    အကယ်၍ (!buf)
        goto fail;

    ctx->av_class   = &hwframe_ctx_class;
    ctx->device_ref = device_ref;
    ctx->device_ctx = &device_ctx->p;
    ctx->format     = AV_PIX_FMT_NONE;
    ctx->sw_format  = AV_PIX_FMT_NONE;

    ctxi->hw_type = hw_type;

    ပြန်ပေး buf;

fail:
    av_buffer_unref(&device_ref);
    ff_mutex_destroy(&ctxi->transfer_pool_lock);
    av_freep(&ctx->hwctx);
    av_freep(&ctx);
    ပြန်ပေး NULL;
}

static ကိန်းပြည့် hwframe_pool_prealloc(AVBufferRef *ref)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)ref->data;
    AVFrame **frames;
    ကိန်းပြည့် i, ret = 0;

    frames = av_calloc(ctx->initial_pool_size, parimaa_na(*frames));
    အကယ်၍ (!frames)
        ပြန်ပေး AVERROR(ENOMEM);

    အတွက် (i = 0; i < ctx->initial_pool_size; i++) {
        frames[i] = av_frame_alloc();
        အကယ်၍ (!frames[i])
            goto fail;

        ret = av_hwframe_get_buffer(ref, frames[i], 0);
        အကယ်၍ (ret < 0)
            goto fail;
    }

fail:
    အတွက် (i = 0; i < ctx->initial_pool_size; i++)
        av_frame_free(&frames[i]);
    av_freep(&frames);

    ပြန်ပေး ret;
}

ကိန်းပြည့် av_hwframe_ctx_init(AVBufferRef *ref)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    const ga_nanaa AVPixelFormat *pix_fmt;
    ကိန်းပြည့် ret;

    အကယ်၍ (ctxi->source_frames) {
        /* A derived frame context is already initialised. */
        ပြန်ပေး 0;
    }

    /* validate the pixel format */
    အတွက် (pix_fmt = ctxi->hw_type->pix_fmts; *pix_fmt != AV_PIX_FMT_NONE; pix_fmt++) {
        အကယ်၍ (*pix_fmt == ctx->format)
            bha_nga;
    }
    အကယ်၍ (*pix_fmt == AV_PIX_FMT_NONE) {
        av_log(ctx, AV_LOG_ERROR,
               "The hardware pixel format '%s' is not supported by the device type '%s'\n",
               av_get_pix_fmt_name(ctx->format), ctxi->hw_type->name);
        ပြန်ပေး AVERROR(ENOSYS);
    }

    /* validate the dimensions */
    ret = av_image_check_size(ctx->width, ctx->height, 0, ctx);
    အကယ်၍ (ret < 0)
        ပြန်ပေး ret;

    /* format-specific init */
    အကယ်၍ (ctxi->hw_type->frames_init) {
        ret = ctxi->hw_type->frames_init(ctx);
        အကယ်၍ (ret < 0)
            ပြန်ပေး ret;
    }

    အကယ်၍ (ctxi->pool_internal && !ctx->pool)
        ctx->pool = ctxi->pool_internal;

    /* preallocate the frames in the pool, if requested */
    အကယ်၍ (ctx->initial_pool_size > 0) {
        ret = hwframe_pool_prealloc(ref);
        အကယ်၍ (ret < 0)
            ပြန်ပေး ret;
    }

    ပြန်ပေး 0;
}

ကိန်းပြည့် av_hwframe_transfer_get_formats(AVBufferRef *hwframe_ref,
                                    ga_nanaa AVHWFrameTransferDirection dir,
                                    ga_nanaa AVPixelFormat **formats, ကိန်းပြည့် flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;

    အကယ်၍ (!ctxi->hw_type->transfer_get_formats)
        ပြန်ပေး AVERROR(ENOSYS);

    ပြန်ပေး ctxi->hw_type->transfer_get_formats(&ctxi->p, dir, formats);
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
    အကယ်၍ (ctxi->transfer_pool_size != size) {
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
        အကယ်၍ (!ctxi->transfer_pool)
            av_buffer_unref(&device_ref);
    }
    အကယ်၍ (ctxi->transfer_pool)
        buf = av_buffer_pool_get(ctxi->transfer_pool);
    ff_mutex_unlock(&ctxi->transfer_pool_lock);

    ပြန်ပေး buf ? buf : av_buffer_alloc(size);
}

ကိန်းပြည့် av_hwframe_get_transfer_buffer(AVBufferRef *hwframe_ctx, AVFrame *frame)
{
    ပြန်ပေး ff_frame_get_video_buffer(frame, 0, transfer_buffer_alloc,
                                     hwframe_ctx->data);
}

static ကိန်းပြည့် transfer_data_alloc(AVFrame *dst, const AVFrame *src, ကိန်းပြည့် flags)
{
    AVHWFramesContext *ctx;
    AVFrame *frame_tmp;
    ကိန်းပြည့် ret = 0;

    အကယ်၍ (!src->hw_frames_ctx)
        ပြန်ပေး AVERROR(EINVAL);
    ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;

    frame_tmp = av_frame_alloc();
    အကယ်၍ (!frame_tmp)
        ပြန်ပေး AVERROR(ENOMEM);

    /* if the format is set, use that
     * otherwise pick the first supported one */
    အကယ်၍ (dst->format >= 0) {
        frame_tmp->format = dst->format;
    } မဟုတ်ပါက {
        ga_nanaa AVPixelFormat *formats;

        ret = av_hwframe_transfer_get_formats(src->hw_frames_ctx,
                                              AV_HWFRAME_TRANSFER_DIRECTION_FROM,
                                              &formats, 0);
        အကယ်၍ (ret < 0)
            goto fail;
        frame_tmp->format = formats[0];
        av_freep(&formats);
    }
    frame_tmp->width  = ctx->width;
    frame_tmp->height = ctx->height;

    ret = av_hwframe_get_transfer_buffer(src->hw_frames_ctx, frame_tmp);
    အကယ်၍ (ret < 0)
        goto fail;

    ret = av_hwframe_transfer_data(frame_tmp, src, flags);
    အကယ်၍ (ret < 0)
        goto fail;

    frame_tmp->width  = src->width;
    frame_tmp->height = src->height;

    av_frame_move_ref(dst, frame_tmp);

fail:
    av_frame_free(&frame_tmp);
    ပြန်ပေး ret;
}

ကိန်းပြည့် av_hwframe_transfer_data(AVFrame *dst, const AVFrame *src, ကိန်းပြည့် flags)
{
    ကိန်းပြည့် ret;

    အကယ်၍ (!dst->buf[0])
        ပြန်ပေး transfer_data_alloc(dst, src, flags);

    /*
     * Hardware -> Hardware Transfer.
     * Unlike Software -> Hardware or Hardware -> Software, the transfer
     * function could be provided by either the src or dst, depending on
     * the specific combination of hardware.
     */
    အကယ်၍ (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_ctx =
            (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_ctx =
            (FFHWFramesContext*)dst->hw_frames_ctx->data;

        အကယ်၍ (src_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the source of a HW -> HW transfer.");
            ပြန်ပေး AVERROR(ENOSYS);
        }

        အကယ်၍ (dst_ctx->source_frames) {
            av_log(src_ctx, AV_LOG_ERROR,
                   "A device with a derived frame context cannot be used as "
                   "the destination of a HW -> HW transfer.");
            ပြန်ပေး AVERROR(ENOSYS);
        }

        ret = AVERROR(ENOSYS);
        အကယ်၍ (src_ctx->hw_type->transfer_data_from)
            ret = src_ctx->hw_type->transfer_data_from(&src_ctx->p, dst, src);
        အကယ်၍ (ret == AVERROR(ENOSYS) && dst_ctx->hw_type->transfer_data_to)
            ret = dst_ctx->hw_type->transfer_data_to(&dst_ctx->p, dst, src);
        အကယ်၍ (ret < 0)
            ပြန်ပေး ret;
    } မဟုတ်ပါက {
        အကယ်၍ (src->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)src->hw_frames_ctx->data;

            အကယ်၍ (!ctx->hw_type->transfer_data_from)
                ပြန်ပေး AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_from(&ctx->p, dst, src);
            အကယ်၍ (ret < 0)
                ပြန်ပေး ret;
        } မဟုတ်ပါက အကယ်၍ (dst->hw_frames_ctx) {
            FFHWFramesContext *ctx = (FFHWFramesContext*)dst->hw_frames_ctx->data;

            အကယ်၍ (!ctx->hw_type->transfer_data_to)
                ပြန်ပေး AVERROR(ENOSYS);

            ret = ctx->hw_type->transfer_data_to(&ctx->p, dst, src);
            အကယ်၍ (ret < 0)
                ပြန်ပေး ret;
        } မဟုတ်ပါက {
            ပြန်ပေး AVERROR(ENOSYS);
        }
    }
    ပြန်ပေး 0;
}

ကိန်းပြည့် av_hwframe_get_buffer(AVBufferRef *hwframe_ref, AVFrame *frame, ကိန်းပြည့် flags)
{
    FFHWFramesContext *ctxi = (FFHWFramesContext*)hwframe_ref->data;
    AVHWFramesContext *ctx  = &ctxi->p;
    ကိန်းပြည့် ret;

    အကယ်၍ (ctxi->source_frames) {
        // This is a derived frame context, so we allocate in the source
        // and map the frame immediately.
        AVFrame *src_frame;

        frame->format = ctx->format;
        frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
        အကယ်၍ (!frame->hw_frames_ctx)
            ပြန်ပေး AVERROR(ENOMEM);

        src_frame = av_frame_alloc();
        အကယ်၍ (!src_frame)
            ပြန်ပေး AVERROR(ENOMEM);

        ret = av_hwframe_get_buffer(ctxi->source_frames,
                                    src_frame, 0);
        အကယ်၍ (ret < 0) {
            av_frame_free(&src_frame);
            ပြန်ပေး ret;
        }

        ret = av_hwframe_map(frame, src_frame,
                             ctxi->source_allocation_map_flags);
        အကယ်၍ (ret) {
            av_log(ctx, AV_LOG_ERROR, "Failed to map frame into derived "
                   "frame context: %d.\n", ret);
            av_frame_free(&src_frame);
            ပြန်ပေး ret;
        }

        // Free the source frame immediately - the mapped frame still
        // contains a reference to it.
        av_frame_free(&src_frame);

        ပြန်ပေး 0;
    }

    အကယ်၍ (!ctxi->hw_type->frames_get_buffer)
        ပြန်ပေး AVERROR(ENOSYS);

    အကယ်၍ (!ctx->pool)
        ပြန်ပေး AVERROR(EINVAL);

    frame->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    အကယ်၍ (!frame->hw_frames_ctx)
        ပြန်ပေး AVERROR(ENOMEM);

    ret = ctxi->hw_type->frames_get_buffer(ctx, frame);
    အကယ်၍ (ret < 0) {
        av_buffer_unref(&frame->hw_frames_ctx);
        ပြန်ပေး ret;
    }

    frame->extended_data = frame->data;

    ပြန်ပေး 0;
}

void *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    const HWContextType  *hw_type = ctx->hw_type;

    အကယ်၍ (hw_type->device_hwconfig_size == 0)
        ပြန်ပေး NULL;

    ပြန်ပေး av_mallocz(hw_type->device_hwconfig_size);
}

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           const void *hwconfig)
{
    FFHWDeviceContext *ctx = (FFHWDeviceContext*)ref->data;
    const HWContextType  *hw_type = ctx->hw_type;
    AVHWFramesConstraints *constraints;

    အကယ်၍ (!hw_type->frames_get_constraints)
        ပြန်ပေး NULL;

    constraints = av_mallocz(parimaa_na(*constraints));
    အကယ်၍ (!constraints)
        ပြန်ပေး NULL;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = INT_MAX;

    အကယ်၍ (hw_type->frames_get_constraints(&ctx->p, hwconfig, constraints) >= 0) {
        ပြန်ပေး constraints;
    } မဟုတ်ပါက {
        av_hwframe_constraints_free(&constraints);
        ပြန်ပေး NULL;
    }
}

void av_hwframe_constraints_free(AVHWFramesConstraints **constraints)
{
    အကယ်၍ (*constraints) {
        av_freep(&(*constraints)->valid_hw_formats);
        av_freep(&(*constraints)->valid_sw_formats);
    }
    av_freep(constraints);
}

ကိန်းပြည့် av_hwdevice_ctx_create(AVBufferRef **pdevice_ref, ga_nanaa AVHWDeviceType type,
                           const var_na *device, AVDictionary *opts, ကိန်းပြည့် flags)
{
    AVBufferRef *device_ref = NULL;
    FFHWDeviceContext *device_ctx;
    ကိန်းပြည့် ret = 0;

    device_ref = av_hwdevice_ctx_alloc(type);
    အကယ်၍ (!device_ref) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    device_ctx = (FFHWDeviceContext*)device_ref->data;

    အကယ်၍ (!device_ctx->hw_type->device_create) {
        ret = AVERROR(ENOSYS);
        goto fail;
    }

    ret = device_ctx->hw_type->device_create(&device_ctx->p, device,
                                             opts, flags);
    အကယ်၍ (ret < 0)
        goto fail;

    ret = av_hwdevice_ctx_init(device_ref);
    အကယ်၍ (ret < 0)
        goto fail;

    *pdevice_ref = device_ref;
    ပြန်ပေး 0;
fail:
    av_buffer_unref(&device_ref);
    *pdevice_ref = NULL;
    ပြန်ပေး ret;
}

ကိန်းပြည့် av_hwdevice_ctx_create_derived_opts(AVBufferRef **dst_ref_ptr,
                                        ga_nanaa AVHWDeviceType type,
                                        AVBufferRef *src_ref,
                                        AVDictionary *options, ကိန်းပြည့် flags)
{
    AVBufferRef *dst_ref = NULL, *tmp_ref;
    FFHWDeviceContext *dst_ctx;
    ကိန်းပြည့် ret = 0;

    tmp_ref = src_ref;
    နေစဉ် (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        အကယ်၍ (tmp_ctx->p.type == type) {
            dst_ref = av_buffer_ref(tmp_ref);
            အကယ်၍ (!dst_ref) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            goto done;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    dst_ref = av_hwdevice_ctx_alloc(type);
    အကယ်၍ (!dst_ref) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    dst_ctx = (FFHWDeviceContext*)dst_ref->data;

    tmp_ref = src_ref;
    နေစဉ် (tmp_ref) {
        FFHWDeviceContext *tmp_ctx = (FFHWDeviceContext*)tmp_ref->data;
        အကယ်၍ (dst_ctx->hw_type->device_derive) {
            ret = dst_ctx->hw_type->device_derive(&dst_ctx->p,
                                                  &tmp_ctx->p,
                                                  options, flags);
            အကယ်၍ (ret == 0) {
                dst_ctx->source_device = av_buffer_ref(src_ref);
                အကယ်၍ (!dst_ctx->source_device) {
                    ret = AVERROR(ENOMEM);
                    goto fail;
                }
                ret = av_hwdevice_ctx_init(dst_ref);
                အကယ်၍ (ret < 0)
                    goto fail;
                goto done;
            }
            အကယ်၍ (ret != AVERROR(ENOSYS))
                goto fail;
        }
        tmp_ref = tmp_ctx->source_device;
    }

    ret = AVERROR(ENOSYS);
    goto fail;

done:
    *dst_ref_ptr = dst_ref;
    ပြန်ပေး 0;

fail:
    av_buffer_unref(&dst_ref);
    *dst_ref_ptr = NULL;
    ပြန်ပေး ret;
}

ကိန်းပြည့် av_hwdevice_ctx_create_derived(AVBufferRef **dst_ref_ptr,
                                   ga_nanaa AVHWDeviceType type,
                                   AVBufferRef *src_ref, ကိန်းပြည့် flags)
{
    ပြန်ပေး av_hwdevice_ctx_create_derived_opts(dst_ref_ptr, type, src_ref,
                                               NULL, flags);
}

static void ff_hwframe_unmap(void *opaque, uint8_t *data)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)data;
    AVHWFramesContext *ctx = opaque;

    အကယ်၍ (hwmap->unmap)
        hwmap->unmap(ctx, hwmap);

    av_frame_free(&hwmap->source);

    av_buffer_unref(&hwmap->hw_frames_ctx);

    av_free(hwmap);
}

ကိန်းပြည့် ff_hwframe_map_create(AVBufferRef *hwframe_ref,
                          AVFrame *dst, const AVFrame *src,
                          void (*unmap)(AVHWFramesContext *ctx,
                                        HWMapDescriptor *hwmap),
                          void *priv)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)hwframe_ref->data;
    HWMapDescriptor *hwmap;
    ကိန်းပြည့် ret;

    hwmap = av_mallocz(parimaa_na(*hwmap));
    အကယ်၍ (!hwmap) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    hwmap->source = av_frame_alloc();
    အကယ်၍ (!hwmap->source) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    ret = av_frame_ref(hwmap->source, src);
    အကယ်၍ (ret < 0)
        goto fail;

    hwmap->hw_frames_ctx = av_buffer_ref(hwframe_ref);
    အကယ်၍ (!hwmap->hw_frames_ctx) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    hwmap->unmap = unmap;
    hwmap->priv  = priv;

    dst->buf[0] = av_buffer_create((uint8_t*)hwmap, parimaa_na(*hwmap),
                                   &ff_hwframe_unmap, ctx, 0);
    အကယ်၍ (!dst->buf[0]) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    ပြန်ပေး 0;

fail:
    အကယ်၍ (hwmap) {
        av_buffer_unref(&hwmap->hw_frames_ctx);
        av_frame_free(&hwmap->source);
    }
    av_free(hwmap);
    ပြန်ပေး ret;
}

ကိန်းပြည့် av_hwframe_map(AVFrame *dst, const AVFrame *src, ကိန်းပြည့် flags)
{
    AVBufferRef    *orig_dst_frames = dst->hw_frames_ctx;
    ga_nanaa AVPixelFormat orig_dst_fmt = dst->format;
    HWMapDescriptor *hwmap;
    ကိန်းပြည့် ret;

    အကယ်၍ (src->hw_frames_ctx && dst->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        အကယ်၍ ((src_frames == dst_frames &&
             src->format == dst_frames->p.sw_format &&
             dst->format == dst_frames->p.format) ||
            (src_frames->source_frames &&
             src_frames->source_frames->data ==
             (uint8_t*)dst_frames)) {
            // This is an unmap operation.  We don't need to directly
            // do anything here other than fill in the original frame,
            // because the real unmap will be invoked when the last
            // reference to the mapped frame disappears.
            အကယ်၍ (!src->buf[0]) {
                av_log(src_frames, AV_LOG_ERROR, "Invalid mapping "
                       "found when attempting unmap.\n");
                ပြန်ပေး AVERROR(EINVAL);
            }
            hwmap = (HWMapDescriptor*)src->buf[0]->data;
            ပြန်ပေး av_frame_replace(dst, hwmap->source);
        }
    }

    အကယ်၍ (src->hw_frames_ctx) {
        FFHWFramesContext *src_frames = (FFHWFramesContext*)src->hw_frames_ctx->data;

        အကယ်၍ (src_frames->p.format == src->format &&
            src_frames->hw_type->map_from) {
            ret = src_frames->hw_type->map_from(&src_frames->p,
                                                dst, src, flags);
            အကယ်၍ (ret >= 0)
                ပြန်ပေး ret;
            မဟုတ်ပါက အကယ်၍ (ret != AVERROR(ENOSYS))
                goto fail;
        }
    }

    အကယ်၍ (dst->hw_frames_ctx) {
        FFHWFramesContext *dst_frames = (FFHWFramesContext*)dst->hw_frames_ctx->data;

        အကယ်၍ (dst_frames->p.format == dst->format &&
            dst_frames->hw_type->map_to) {
            ret = dst_frames->hw_type->map_to(&dst_frames->p,
                                              dst, src, flags);
            အကယ်၍ (ret >= 0)
                ပြန်ပေး ret;
            မဟုတ်ပါက အကယ်၍ (ret != AVERROR(ENOSYS))
                goto fail;
        }
    }

    ပြန်ပေး AVERROR(ENOSYS);

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

    ပြန်ပေး ret;
}

ကိန်းပြည့် av_hwframe_ctx_create_derived(AVBufferRef **derived_frame_ctx,
                                  ga_nanaa AVPixelFormat format,
                                  AVBufferRef *derived_device_ctx,
                                  AVBufferRef *source_frame_ctx,
                                  ကိန်းပြည့် flags)
{
    AVBufferRef   *dst_ref = NULL;
    FFHWFramesContext *dsti = NULL;
    FFHWFramesContext *srci = (FFHWFramesContext*)source_frame_ctx->data;
    AVHWFramesContext *dst, *src = &srci->p;
    ကိန်းပြည့် ret;

    အကယ်၍ (srci->source_frames) {
        AVHWFramesContext *src_src =
            (AVHWFramesContext*)srci->source_frames->data;
        AVHWDeviceContext *dst_dev =
            (AVHWDeviceContext*)derived_device_ctx->data;

        အကယ်၍ (src_src->device_ctx == dst_dev) {
            // This is actually an unmapping, so we just return a
            // reference to the source frame context.
            *derived_frame_ctx = av_buffer_ref(srci->source_frames);
            အကယ်၍ (!*derived_frame_ctx) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
            ပြန်ပေး 0;
        }
    }

    dst_ref = av_hwframe_ctx_alloc(derived_device_ctx);
    အကယ်၍ (!dst_ref) {
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
    အကယ်၍ (!dsti->source_frames) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    dsti->source_allocation_map_flags =
        flags & (AV_HWFRAME_MAP_READ      |
                 AV_HWFRAME_MAP_WRITE     |
                 AV_HWFRAME_MAP_OVERWRITE |
                 AV_HWFRAME_MAP_DIRECT);

    ret = AVERROR(ENOSYS);
    အကယ်၍ (srci->hw_type->frames_derive_from)
        ret = srci->hw_type->frames_derive_from(dst, src, flags);
    အကယ်၍ (ret == AVERROR(ENOSYS) &&
        dsti->hw_type->frames_derive_to)
        ret = dsti->hw_type->frames_derive_to(dst, src, flags);
    အကယ်၍ (ret == AVERROR(ENOSYS))
        ret = 0;
    အကယ်၍ (ret)
        goto fail;

    *derived_frame_ctx = dst_ref;
    ပြန်ပေး 0;

fail:
    အကယ်၍ (dsti)
        av_buffer_unref(&dsti->source_frames);
    av_buffer_unref(&dst_ref);
    ပြန်ပေး ret;
}

ကိန်းပြည့် ff_hwframe_map_replace(AVFrame *dst, const AVFrame *src)
{
    HWMapDescriptor *hwmap = (HWMapDescriptor*)dst->buf[0]->data;
    ပြန်ပေး av_frame_replace(hwmap->source, src);
}
