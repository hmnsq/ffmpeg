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

#شامل <stdatomic.h>
#شامل <stdint.h>
#شامل <string.h>

#شامل <mfxvideo.h>

#شامل "config.h"

#اگر HAVE_PTHREADS
#شامل <pthread.h>
#endif

#define COBJMACROS
#اگر CONFIG_VAAPI
#شامل "hwcontext_vaapi.h"
#endif
#اگر CONFIG_D3D11VA
#شامل "hwcontext_d3d11va.h"
#endif
#اگر CONFIG_DXVA2
#شامل <initguid.h>
#شامل "hwcontext_dxva2.h"
#endif

#شامل "buffer.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_qsv.h"
#شامل "mem.h"
#شامل "pixfmt.h"
#شامل "pixdesc.h"
#شامل "time.h"
#شامل "imgutils.h"
#شامل "avassert.h"

#define QSV_VERSION_ATLEAST(MAJOR, MINOR)   \
    (MFX_VERSION_MAJOR > (MAJOR) ||         \
     MFX_VERSION_MAJOR == (MAJOR) && MFX_VERSION_MINOR >= (MINOR))

#define QSV_RUNTIME_VERSION_ATLEAST(MFX_VERSION, MAJOR, MINOR)          \
    ((MFX_VERSION.Major > (MAJOR)) ||                                   \
     (MFX_VERSION.Major == (MAJOR) && MFX_VERSION.Minor >= (MINOR)))

#define MFX_IMPL_VIA_MASK(impl) (0x0f00 & (impl))
#define QSV_ONEVPL       QSV_VERSION_ATLEAST(2, 0)
#define QSV_HAVE_OPAQUE  !QSV_ONEVPL

#اگر QSV_ONEVPL
#شامل <mfxdispatcher.h>
#وگرنه
#define MFXUnload(a) انجامبده { } وقتی(0)
#endif

تعریفنوع ساختار QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

تعریفنوع ساختار QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfxVersion          ver;
    mfxIMPL             impl;

    شمارش AVHWDeviceType child_device_type;
    شمارش AVPixelFormat  child_pix_fmt;
} QSVDeviceContext;

تعریفنوع ساختار QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#اگر HAVE_PTHREADS
    pthread_mutex_t session_lock;
#endif

    AVBufferRef *child_frames_ref;
    mfxFrameSurface1 *surfaces_internal;
    mfxHDLPair *handle_pairs_internal;
    صحیح             nb_surfaces_used;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#اگر QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfxExtBuffer *ext_buffers[1];
#endif
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

تعریفنوع ساختار QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

ایستا ثابت ساختار {
    شمارش AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_shift;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#اگر CONFIG_VAAPI
    { AV_PIX_FMT_UYVY422,
                       MFX_FOURCC_UYVY, 0 },
#endif
    { AV_PIX_FMT_Y210,
                       MFX_FOURCC_Y210, 1 },
    // VUYX is used for VAAPI child device,
    // the SDK only declares support for AYUV
    { AV_PIX_FMT_VUYX,
                       MFX_FOURCC_AYUV, 0 },
    // XV30 is used for VAAPI child device,
    // the SDK only declares support for Y410
    { AV_PIX_FMT_XV30,
                       MFX_FOURCC_Y410, 0 },
#اگر QSV_VERSION_ATLEAST(1, 31)
    // P012 is used for VAAPI child device,
    // the SDK only declares support for P016
    { AV_PIX_FMT_P012,
                       MFX_FOURCC_P016, 1 },
    // Y212 is used for VAAPI child device,
    // the SDK only declares support for Y216
    { AV_PIX_FMT_Y212,
                       MFX_FOURCC_Y216, 1 },
    // XV36 is used for VAAPI child device,
    // the SDK only declares support for Y416
    { AV_PIX_FMT_XV36,
                       MFX_FOURCC_Y416, 1 },
#endif
};

بیرونی صحیح ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          شمارش AVHWDeviceType base_dev_type,
                                          تهی **base_handle);

ایستا صحیح qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
صحیح ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                   شمارش AVHWDeviceType base_dev_type,
                                   تهی **base_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->Data.MemId;
    انتخاب (base_dev_type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
        base_handle[0] = handle_pair->first;
        بازگشت 0;
#endif
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        base_handle[0] = handle_pair->first;
        base_handle[1] = handle_pair->second;
        بازگشت 0;
#endif
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
        base_handle[0] = handle_pair->first;
        بازگشت 0;
#endif
    }
    بازگشت AVERROR(EINVAL);
}

ایستا uint32_t qsv_fourcc_from_pix_fmt(شمارش AVPixelFormat pix_fmt)
{
    صحیح i;
    برای (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        اگر (supported_pixel_formats[i].pix_fmt == pix_fmt)
            بازگشت supported_pixel_formats[i].fourcc;
    }
    بازگشت 0;
}

ایستا uint16_t qsv_shift_from_pix_fmt(شمارش AVPixelFormat pix_fmt)
{
    برای (صحیح i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        اگر (supported_pixel_formats[i].pix_fmt == pix_fmt)
            بازگشت supported_pixel_formats[i].mfx_shift;
    }

    بازگشت 0;
}

#اگر CONFIG_D3D11VA
ایستا uint32_t qsv_get_d3d11va_bind_flags(صحیح mem_type)
{
    uint32_t bind_flags = 0;

    اگر ((mem_type & MFX_MEMTYPE_VIDEO_MEMORY_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_INTERNAL_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    وگرنه
        bind_flags = D3D11_BIND_DECODER;

    اگر ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    بازگشت bind_flags;
}
#endif

ایستا صحیح qsv_fill_border(AVFrame *dst, ثابت AVFrame *src)
{
    ثابت AVPixFmtDescriptor *desc;
    صحیح i, planes_nb = 0;
    اگر (dst->format != src->format)
        بازگشت AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    برای (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    برای (i = 0; i < planes_nb; i++) {
        صحیح sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->width,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->width,
                                                 i);
        ثابت AVComponentDescriptor comp = desc->comp[i];
        اگر (swidth < 0 || dwidth < 0) {
            av_log(پوچ, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            بازگشت AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        اگر (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        برای (y = 0; y < sheight; y++) {
            تهی *سطر_ptr = dst->data[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(سطر_ptr,
                           comp.depth > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        برای (y = sheight; y < dheight; y++) {
            memcpy(dst->data[i]+y*dst->linesize[i],
                   dst->data[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    بازگشت 0;
}

ایستا صحیح qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    صحیح   hw_handle_supported = 0;
    mfxHandleType handle_type;
    شمارش AVHWDeviceType device_type;
    شمارش AVPixelFormat  pix_fmt;
    mfxStatus err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    اگر (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    اگر (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        بازگشت AVERROR_UNKNOWN;
    }

    اگر (MFX_IMPL_VIA_VAAPI == MFX_IMPL_VIA_MASK(s->impl)) {
#اگر CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#endif
    } وگرنه اگر (MFX_IMPL_VIA_D3D11 == MFX_IMPL_VIA_MASK(s->impl)) {
#اگر CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#endif
    } وگرنه اگر (MFX_IMPL_VIA_D3D9 == MFX_IMPL_VIA_MASK(s->impl)) {
#اگر CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#endif
    }

    اگر (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        اگر (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->child_device_type = device_type;
            s->child_pix_fmt     = pix_fmt;
        }
    }
    اگر (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    بازگشت 0;
}

ایستا تهی qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    اگر (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = پوچ;
    s->session_download_init = 0;

    اگر (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = پوچ;
    s->session_upload_init = 0;

#اگر HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_lock);
#endif

    av_freep(&s->mem_ids);
#اگر QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#endif
    av_freep(&s->surfaces_internal);
    av_freep(&s->handle_pairs_internal);
    av_frame_unref(&s->realigned_upload_frame);
    av_frame_unref(&s->realigned_download_frame);
    av_buffer_unref(&s->child_frames_ref);
}

ایستا تهی qsv_pool_release_dummy(تهی *opaque, uint8_t *data)
{
}

ایستا تهی qsv_pool_release(تهی *opaque, uint8_t *data)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)data;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.Data.MemId;
    AVHWFramesContext *child_frames_ctx;

    اگر (!s->child_frames_ref)
        بازگشت;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    اگر (!child_frames_ctx->device_ctx)
        بازگشت;

#اگر CONFIG_VAAPI
    اگر (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#endif

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

ایستا AVBufferRef *qsv_fixed_pool_alloc(تهی *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    اگر (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        بازگشت av_buffer_create((uint8_t*)(s->surfaces_internal + s->nb_surfaces_used - 1),
                                اندازه(*hwctx->surfaces), qsv_pool_release_dummy, پوچ, 0);
    }

    بازگشت پوچ;
}

ایستا AVBufferRef *qsv_dynamic_pool_alloc(تهی *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx;
    QSVSurface *qsv_surface = پوچ;
    mfxHDLPair *handle_pairs_internal = پوچ;
    صحیح ret;

    اگر (!s->child_frames_ref)
        برو fail;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    اگر (!child_frames_ctx->device_ctx)
        برو fail;

#اگر CONFIG_DXVA2
    اگر (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        برو fail;
    }
#endif

    qsv_surface = av_calloc(1, اندازه(*qsv_surface));
    اگر (!qsv_surface)
        برو fail;

    qsv_surface->child_frame = av_frame_alloc();
    اگر (!qsv_surface->child_frame)
        برو fail;

    ret = av_hwframe_get_buffer(s->child_frames_ref, qsv_surface->child_frame, 0);
    اگر (ret < 0)
        برو fail;

    handle_pairs_internal = av_calloc(1, اندازه(*handle_pairs_internal));
    اگر (!handle_pairs_internal)
        برو fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    اگر (ret < 0)
        برو fail;

#اگر CONFIG_VAAPI
    اگر (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, اندازه(*surface_id_internal));
        اگر (!surface_id_internal)
            برو fail;

        *surface_id_internal = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
    }
#endif

#اگر CONFIG_D3D11VA
    اگر (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        handle_pairs_internal->first = (mfxMemId)qsv_surface->child_frame->data[0];

        اگر (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        وگرنه
            handle_pairs_internal->second = (mfxMemId)qsv_surface->child_frame->data[1];

    }
#endif

    qsv_surface->mfx_surface.Data.MemId = (mfxMemId)handle_pairs_internal;
    بازگشت av_buffer_create((uint8_t *)qsv_surface, اندازه(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    اگر (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_pairs_internal);

    بازگشت پوچ;
}

ایستا AVBufferRef *qsv_pool_alloc(تهی *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    اگر (hwctx->nb_surfaces == 0) {
        بازگشت qsv_dynamic_pool_alloc(opaque, size);
    } وگرنه {
        بازگشت qsv_fixed_pool_alloc(opaque, size);
    }
}

ایستا صحیح qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = پوچ;
    AVBufferRef *child_frames_ref = پوچ;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    صحیح i, ret = 0;

    اگر (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        بازگشت AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    اگر (!child_device_ref)
        بازگشت AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->data;

#اگر CONFIG_VAAPI
    اگر (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#endif
#اگر CONFIG_D3D11VA
    اگر (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        ID3D11Device_AddRef((ID3D11Device*)device_priv->handle);
        child_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#endif
#اگر CONFIG_DXVA2
    اگر (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#endif

    ret = av_hwdevice_ctx_init(child_device_ref);
    اگر (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        برو fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    اگر (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->data;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_size = ctx->initial_pool_size;
    child_frames_ctx->width             = FFALIGN(ctx->width, 16);
    child_frames_ctx->height            = FFALIGN(ctx->height, 16);

#اگر CONFIG_D3D11VA
    اگر (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        اگر (hwctx->frame_type == 0)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        اگر (hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
            child_frames_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        child_frames_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->frame_type);
    }
#endif
#اگر CONFIG_DXVA2
    اگر (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        اگر (hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET)
            child_frames_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        وگرنه
            child_frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#endif

    ret = av_hwframe_ctx_init(child_frames_ref);
    اگر (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        برو fail;
    }

#اگر CONFIG_VAAPI
    اگر (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        برای (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = child_frames_hwctx->surface_ids + i;
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif
#اگر CONFIG_D3D11VA
    اگر (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        برای (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->texture_infos[i].texture;
            اگر(child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            } وگرنه {
                s->handle_pairs_internal[i].second = (mfxMemId)child_frames_hwctx->texture_infos[i].index;
            }
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        اگر (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } وگرنه {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
#endif
#اگر CONFIG_DXVA2
    اگر (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        برای (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->surfaces[i];
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        اگر (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        وگرنه
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = پوچ;

fail:
    av_buffer_unref(&child_device_ref);
    av_buffer_unref(&child_frames_ref);
    بازگشت ret;
}

ایستا صحیح qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    ثابت AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    اگر (!desc)
        بازگشت AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    اگر (!fourcc)
        بازگشت AVERROR(EINVAL);

    surf->Info.BitDepthLuma   = desc->comp[0].depth;
    surf->Info.BitDepthChroma = desc->comp[0].depth;
    surf->Info.Shift          = qsv_shift_from_pix_fmt(ctx->sw_format);

    اگر (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    وگرنه اگر (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    وگرنه
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.Width          = FFALIGN(ctx->width, 16);
    surf->Info.CropW          = ctx->width;
    surf->Info.Height         = FFALIGN(ctx->height, 16);
    surf->Info.CropH          = ctx->height;
    surf->Info.FrameRateExtN  = 25;
    surf->Info.FrameRateExtD  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    بازگشت 0;
}

ایستا صحیح qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    صحیح i, ret = 0;

    اگر (ctx->initial_pool_size < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        بازگشت AVERROR(EINVAL);
    } وگرنه اگر (ctx->initial_pool_size == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        اگر (ret < 0)
            بازگشت ret;

        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(اندازه(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, پوچ);
        اگر (!ffhwframesctx(ctx)->pool_internal)
            بازگشت AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, اندازه(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        frames_hwctx->info = &s->frame_info;
        frames_hwctx->nb_surfaces = 0;

        بازگشت 0;
    }

    s->handle_pairs_internal = av_calloc(ctx->initial_pool_size,
                                         اندازه(*s->handle_pairs_internal));
    اگر (!s->handle_pairs_internal)
        بازگشت AVERROR(ENOMEM);

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     اندازه(*s->surfaces_internal));
    اگر (!s->surfaces_internal)
        بازگشت AVERROR(ENOMEM);

    برای (i = 0; i < ctx->initial_pool_size; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_internal[i]);
        اگر (ret < 0)
            بازگشت ret;
    }

#اگر QSV_HAVE_OPAQUE
    اگر (!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        اگر (ret < 0)
            بازگشت ret;
    }
#وگرنه
    ret = qsv_init_child_ctx(ctx);
    اگر (ret < 0)
        بازگشت ret;
#endif

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(اندازه(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, پوچ);
    اگر (!ffhwframesctx(ctx)->pool_internal)
        بازگشت AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    بازگشت 0;
}

ایستا mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    اگر (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        بازگشت MFX_ERR_UNSUPPORTED;
    اگر (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        بازگشت MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->رقم_Frame_Actual = hwctx->nb_surfaces;

    بازگشت MFX_ERR_NONE;
}

ایستا mfxStatus frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    بازگشت MFX_ERR_NONE;
}

ایستا mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    بازگشت MFX_ERR_UNSUPPORTED;
}

ایستا mfxStatus frame_unlock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    بازگشت MFX_ERR_UNSUPPORTED;
}

ایستا mfxStatus frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    اگر (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    بازگشت MFX_ERR_NONE;
}

#اگر QSV_ONEVPL

ایستا صحیح qsv_d3d11_update_config(تهی *ctx, mfxHDL handle, mfxConfig cfg)
{
    صحیح ret = AVERROR_UNKNOWN;
#اگر CONFIG_D3D11VA
    mfxStatus sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = پوچ;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_مقدار = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (تهی**)&pDXGIDevice);
    اگر (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        اگر (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            بازگشت ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        اگر (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            برو fail;
        }
    } وگرنه {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        بازگشت ret;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_U16;
    impl_مقدار.Data.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_مقدار);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        برو fail;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_PTR;
    impl_مقدار.Data.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_مقدار);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        برو fail;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_U32;
    impl_مقدار.Data.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_مقدار);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        برو fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#endif
    بازگشت ret;
}

ایستا صحیح qsv_d3d9_update_config(تهی *ctx, mfxHDL handle, mfxConfig cfg)
{
    صحیح ret = AVERROR_UNKNOWN;
#اگر CONFIG_DXVA2
    mfxStatus sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = پوچ;
    IDirect3DDevice9Ex *device_ex = پوچ;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = پوچ;
    IDirect3D9 *d3d9 = پوچ;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_مقدار = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        برو fail;
    }

    hr = IDirect3DDeviceManager9_LockDevice(devmgr, device_handle, &device, TRUE);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        برو fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (تهی **)&device_ex);
    IDirect3DDevice9_Release(device);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        برو unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        برو unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        برو unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (تهی **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        برو unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        برو release;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_PTR;
    impl_مقدار.Data.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_مقدار);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        برو release;
    }

    ret = 0;

release:
    IDirect3D9Ex_Release(d3d9ex);
    IDirect3DDevice9Ex_Release(device_ex);

unlock:
    IDirect3DDeviceManager9_UnlockDevice(devmgr, device_handle, FALSE);
    IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
fail:
#endif
    بازگشت ret;
}

ایستا صحیح qsv_va_update_config(تهی *ctx, mfxHDL handle, mfxConfig cfg)
{
#اگر CONFIG_VAAPI
#اگر VA_CHECK_VERSION(1, 15, 0)
    mfxStatus sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_مقدار = {0};

    vas = vaGetDisplayAttributes(dpy, &attr, 1);
    اگر (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_مقدار.Type = MFX_VARIANT_TYPE_U16;
        impl_مقدار.Data.U16 = (attr.مقدار & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ثابت mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_مقدار);
        اگر (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            برو fail;
        }
    } وگرنه {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        برو fail;
    }

    بازگشت 0;

fail:
#وگرنه
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#endif
#endif
    بازگشت AVERROR_UNKNOWN;
}

ایستا صحیح qsv_new_mfx_loader(تهی *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfxVersion *pver,
                              تهی **ploader)
{
    mfxStatus sts;
    mfxLoader loader = پوچ;
    mfxConfig cfg;
    mfxVariant impl_مقدار = {0};

    *ploader = پوچ;
    loader = MFXLoad();
    اگر (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        برو fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    اگر (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        برو fail;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_U32;
    impl_مقدار.Data.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.Impl", impl_مقدار);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        برو fail;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_U32;
    impl_مقدار.Data.U32 = pver->Version;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_مقدار);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        برو fail;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_U32;
    impl_مقدار.Data.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.VendorID", impl_مقدار);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        برو fail;
    }

    اگر (MFX_HANDLE_VA_DISPLAY == handle_type) {
        اگر (handle && qsv_va_update_config(ctx, handle, cfg))
            برو fail;

        impl_مقدار.Data.U32 = MFX_ACCEL_MODE_VIA_VAAPI;
    } وگرنه اگر (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        اگر (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            برو fail;

        impl_مقدار.Data.U32 = MFX_ACCEL_MODE_VIA_D3D9;
    } وگرنه {
        اگر (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            برو fail;

        impl_مقدار.Data.U32 = MFX_ACCEL_MODE_VIA_D3D11;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.AccelerationMode", impl_مقدار);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        برو fail;
    }

    *ploader = loader;

    بازگشت 0;

fail:
    اگر (loader)
        MFXUnload(loader);

    بازگشت AVERROR_UNKNOWN;
}

ایستا صحیح qsv_create_mfx_session_from_loader(تهی *ctx, mfxLoader loader, mfxSession *psession)
{
    mfxStatus sts;
    mfxSession session = پوچ;
    uint32_t impl_idx = 0;
    mfxVersion ver;

    وقتی (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        اگر (sts == MFX_ERR_NOT_FOUND)
            بشکن;
        وگرنه اگر (sts != MFX_ERR_NONE) {
            impl_idx++;
            ادامه;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        اگر (sts == MFX_ERR_NONE)
            بشکن;

        impl_idx++;
    }

    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        برو fail;
    }

    sts = MFXQueryVersion(session, &ver);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        برو fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    بازگشت 0;

fail:
    اگر (session)
        MFXClose(session);

    بازگشت AVERROR_UNKNOWN;
}

ایستا صحیح qsv_create_mfx_session(تهی *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  تهی **ploader)
{
    mfxLoader loader = پوچ;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    اگر (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        بازگشت AVERROR(EXDEV);
    }

    *psession = پوچ;

    اگر (!*ploader) {
        اگر (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (تهی **)&loader))
            برو fail;

        av_assert0(loader);
    } وگرنه
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    اگر (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        برو fail;

    اگر (!*ploader)
        *ploader = loader;

    بازگشت 0;

fail:
    اگر (!*ploader && loader)
        MFXUnload(loader);

    بازگشت AVERROR_UNKNOWN;
}

#وگرنه

ایستا صحیح qsv_create_mfx_session(تهی *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  تهی **ploader)
{
    mfxVersion ver;
    mfxStatus sts;
    mfxSession session = پوچ;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    *ploader = پوچ;
    *psession = پوچ;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        برو fail;
    }

    sts = MFXQueryVersion(session, &ver);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        برو fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        برو fail;
    }

    *psession = session;

    بازگشت 0;

fail:
    اگر (session)
        MFXClose(session);

    بازگشت AVERROR_UNKNOWN;
}

#endif

ایستا صحیح qsv_init_internal_session(AVHWFramesContext *ctx,
                                     mfxSession *session, صحیح upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    صحیح opaque = 0;

    mfxFrameAllocator frame_allocator = {
        .pthis  = ctx,
        .Alloc  = frame_alloc,
        .Lock   = frame_lock,
        .Unlock = frame_unlock,
        .GetHDL = frame_get_hdl,
        .Free   = frame_free,
    };

    mfxVideoParam par;
    mfxStatus err;
    صحیح                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    تهی             **loader = &hwctx->loader;
    mfxSession parent_session = hwctx->session;
    mfxIMPL impl;
    mfxVersion ver;

    err = MFXQueryIMPL(parent_session, &impl);
    اگر (err == MFX_ERR_NONE)
        err = MFXQueryVersion(parent_session, &ver);
    اگر (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        بازگشت AVERROR_UNKNOWN;
    }

#اگر QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    اگر (ret)
        برو fail;

    اگر (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        اگر (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            برو fail;
        }
    }

    اگر (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        اگر (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            برو fail;
        }
    }

    اگر (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        اگر (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            برو fail;
        }
    }

    memset(&par, 0, اندازه(par));

    اگر (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_OUT_VIDEO_MEMORY :
                                 MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
#اگر QSV_HAVE_OPAQUE
    وگرنه {
        par.ExtParam    = s->ext_buffers;
        par.رقم_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
        par.IOPattern   = upload ? MFX_IOPATTERN_OUT_OPAQUE_MEMORY :
                                   MFX_IOPATTERN_IN_OPAQUE_MEMORY;
    }
#endif

    par.IOPattern |= upload ? MFX_IOPATTERN_IN_SYSTEM_MEMORY :
                              MFX_IOPATTERN_OUT_SYSTEM_MEMORY;
    par.AsyncDepth = 1;

    par.vpp.In = frames_hwctx->nb_surfaces ? frames_hwctx->surfaces[0].Info : *frames_hwctx->info;

    /* Apparently VPP requires the frame rate to be set to some value, otherwise
     * init will fail (probably for the framerate conversion filter). Since we
     * are only doing data upload/download here, we just invent an arbitrary
     * value */
    par.vpp.In.FrameRateExtN = 25;
    par.vpp.In.FrameRateExtD = 1;
    par.vpp.Out = par.vpp.In;

    err = MFXVideoVPP_Init(*session, &par);
    اگر (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        برو fail;
    }

    بازگشت 0;

fail:
    اگر (*session)
        MFXClose(*session);

    *session = پوچ;

    بازگشت ret;
}

ایستا صحیح qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    صحیح opaque = 0;

    uint32_t fourcc;
    صحیح i, ret;

#اگر QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    اگر (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        بازگشت AVERROR(ENOSYS);
    }

    اگر (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        اگر (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            بازگشت ret;
        }
    }

    اگر (!opaque) {
        s->mem_ids = av_calloc(frames_hwctx->nb_surfaces, اندازه(*s->mem_ids));
        اگر (!s->mem_ids)
            بازگشت AVERROR(ENOMEM);

        برای (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].Data.MemId;
    }
#اگر QSV_HAVE_OPAQUE
    وگرنه {
        s->surface_ptrs = av_calloc(frames_hwctx->nb_surfaces,
                                    اندازه(*s->surface_ptrs));
        اگر (!s->surface_ptrs)
            بازگشت AVERROR(ENOMEM);

        برای (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.رقم_Surface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = اندازه(s->opaque_alloc);

        s->ext_buffers[0] = (mfxExtBuffer*)&s->opaque_alloc;
    }
#endif

    s->session_download = پوچ;
    s->session_upload   = پوچ;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#اگر HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, پوچ);
#endif

    بازگشت 0;
}

ایستا صحیح qsv_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    اگر (!frame->buf[0])
        بازگشت AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_QSV;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    بازگشت 0;
}

ایستا صحیح qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    شمارش AVHWFrameTransferDirection dir,
                                    شمارش AVPixelFormat **formats)
{
    شمارش AVPixelFormat *fmts;

    fmts = av_malloc_array(2, اندازه(*fmts));
    اگر (!fmts)
        بازگشت AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    بازگشت 0;
}

ایستا صحیح qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, صحیح flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    صحیح i;

    انتخاب (dst_ctx->device_ctx->type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               اندازه(*dst_hwctx->surface_ids));
            اگر (!dst_hwctx->surface_ids)
                بازگشت AVERROR(ENOMEM);
            برای (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        بشکن;
#endif
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_size = src_ctx->initial_pool_size;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 اندازه(*dst_hwctx->texture_infos));
            اگر (!dst_hwctx->texture_infos)
                بازگشت AVERROR(ENOMEM);
            اگر (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            برای (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].index = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            اگر (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } وگرنه
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        بشکن;
#endif
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            اندازه(*dst_hwctx->surfaces));
            اگر (!dst_hwctx->surfaces)
                بازگشت AVERROR(ENOMEM);
            برای (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            اگر (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            وگرنه
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        بشکن;
#endif
    پیشفرض:
        بازگشت AVERROR(ENOSYS);
    }

    بازگشت 0;
}

ایستا صحیح qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->data[3];
    AVHWFramesContext *child_frames_ctx;
    ثابت AVPixFmtDescriptor *desc;
    uint8_t *child_data;
    AVFrame *dummy;
    صحیح ret = 0;

    اگر (!s->child_frames_ref)
        بازگشت AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;

    انتخاب (child_frames_ctx->device_ctx->type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_data = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        بشکن;
    }
#endif
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        بشکن;
    }
#endif
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        بشکن;
    }
#endif
    پیشفرض:
        بازگشت AVERROR(ENOSYS);
    }

    اگر (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, پوچ, پوچ);
        اگر (ret < 0)
            بازگشت ret;

        dst->width   = src->width;
        dst->height  = src->height;

       اگر (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
            dst->data[0] = pair->first;
            dst->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } وگرنه {
            dst->data[3] = child_data;
        }

        بازگشت 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    اگر (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        بازگشت AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    اگر (!dummy)
        بازگشت AVERROR(ENOMEM);

    dummy->buf[0]        = av_buffer_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_buffer_ref(s->child_frames_ref);
    اگر (!dummy->buf[0] || !dummy->hw_frames_ctx)
        برو fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;

    اگر (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        dummy->data[0] = pair->first;
        dummy->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } وگرنه {
        dummy->data[3] = child_data;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    بازگشت ret;
}

ایستا صحیح qsv_transfer_data_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   ثابت AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    صحیح download = !!src->hw_frames_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->data[3] : dst->data[3]);

    AVFrame *dummy;
    صحیح ret;

    dummy = av_frame_alloc();
    اگر (!dummy)
        بازگشت AVERROR(ENOMEM);

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->data[3]       = surf->Data.MemId;
    dummy->hw_frames_ctx = s->child_frames_ref;

    ret = download ? av_hwframe_transfer_data(dst, dummy, 0) :
                     av_hwframe_transfer_data(dummy, src, 0);

    dummy->buf[0]        = پوچ;
    dummy->data[3]       = پوچ;
    dummy->hw_frames_ctx = پوچ;

    av_frame_free(&dummy);

    بازگشت ret;
}

ایستا صحیح map_frame_to_surface(ثابت AVFrame *frame, mfxFrameSurface1 *surface)
{
    انتخاب (frame->format) {
    حالت AV_PIX_FMT_NV12:
    حالت AV_PIX_FMT_P010:
    حالت AV_PIX_FMT_P012:
        surface->Data.Y  = frame->data[0];
        surface->Data.UV = frame->data[1];
        بشکن;

    حالت AV_PIX_FMT_YUV420P:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[1];
        surface->Data.V = frame->data[2];
        بشکن;

    حالت AV_PIX_FMT_BGRA:
        surface->Data.B = frame->data[0];
        surface->Data.G = frame->data[0] + 1;
        surface->Data.R = frame->data[0] + 2;
        surface->Data.A = frame->data[0] + 3;
        بشکن;
    حالت AV_PIX_FMT_YUYV422:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.V = frame->data[0] + 3;
        بشکن;

    حالت AV_PIX_FMT_Y210:
    حالت AV_PIX_FMT_Y212:
        surface->Data.Y16 = (mfxU16 *)frame->data[0];
        surface->Data.U16 = (mfxU16 *)frame->data[0] + 1;
        surface->Data.V16 = (mfxU16 *)frame->data[0] + 3;
        بشکن;
    حالت AV_PIX_FMT_VUYX:
        surface->Data.V = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.Y = frame->data[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 3;
        بشکن;
    حالت AV_PIX_FMT_XV30:
        surface->Data.U = frame->data[0];
        بشکن;
    حالت AV_PIX_FMT_XV36:
        surface->Data.U = frame->data[0];
        surface->Data.Y = frame->data[0] + 2;
        surface->Data.V = frame->data[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 6;
        بشکن;
#اگر CONFIG_VAAPI
    حالت AV_PIX_FMT_UYVY422:
        surface->Data.Y = frame->data[0] + 1;
        surface->Data.U = frame->data[0];
        surface->Data.V = frame->data[0] + 2;
        بشکن;
#endif
    پیشفرض:
        بازگشت MFX_ERR_UNSUPPORTED;
    }
    surface->Data.Pitch     = frame->linesize[0];
    surface->Data.TimeStamp = frame->pts;

    بازگشت 0;
}

ایستا صحیح qsv_internal_session_check_init(AVHWFramesContext *ctx, صحیح upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    صحیح ret = 0;

    اگر (atomic_load(inited))
        بازگشت 0;

#اگر HAVE_PTHREADS
    pthread_mutex_lock(&s->session_lock);
#endif

    اگر (!atomic_load(inited)) {
        ret = qsv_init_internal_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#اگر HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_lock);
#endif

    بازگشت ret;
}

ایستا صحیح qsv_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ثابت AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->data[3];

    mfxSyncPoint sync = پوچ;
    mfxStatus err;
    صحیح ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    صحیح realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 0);
    اگر (ret < 0)
        بازگشت ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    اگر (dst->height & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        اگر (tmp_frame->format != dst->format ||
            tmp_frame->width  != FFALIGN(dst->linesize[0], 16) ||
            tmp_frame->height != FFALIGN(dst->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = dst->format;
            tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
            tmp_frame->height = FFALIGN(dst->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            اگر (ret < 0)
                بازگشت ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    اگر (!s->session_download) {
        اگر (s->child_frames_ref)
            بازگشت qsv_transfer_data_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        بازگشت AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst_frame, &out);

    انجامبده {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, پوچ, &sync);
        اگر (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } وقتی (err == MFX_WRN_DEVICE_BUSY);

    اگر (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        بازگشت AVERROR_UNKNOWN;
    }

    انجامبده {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } وقتی (err == MFX_WRN_IN_EXECUTION);
    اگر (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        بازگشت AVERROR_UNKNOWN;
    }

    اگر (realigned) {
        tmp_frame->width  = dst->width;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        اگر (ret < 0)
            بازگشت ret;
    }

    بازگشت 0;
}

ایستا صحیح qsv_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                ثابت AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   in = {{ 0 }};
    mfxFrameSurface1 *out = (mfxFrameSurface1*)dst->data[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = پوچ;
    mfxStatus err;
    صحیح ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    ثابت AVFrame *src_frame;
    صحیح realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 1);
    اگر (ret < 0)
        بازگشت ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    اگر (src->height & 15 || src->linesize[0] & 15) {
        realigned = 1;
        اگر (tmp_frame->format != src->format ||
            tmp_frame->width  != FFALIGN(src->width, 16) ||
            tmp_frame->height != FFALIGN(src->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = src->format;
            tmp_frame->width  = FFALIGN(src->width, 16);
            tmp_frame->height = FFALIGN(src->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            اگر (ret < 0)
                بازگشت ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        اگر (ret < 0) {
            av_frame_unref(tmp_frame);
            بازگشت ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        اگر (ret < 0) {
            av_frame_unref(tmp_frame);
            بازگشت ret;
        }

        tmp_info = out->Info;
        out->Info.CropW = FFMIN(out->Info.Width,  tmp_frame->width);
        out->Info.CropH = FFMIN(out->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    اگر (!s->session_upload) {
        اگر (s->child_frames_ref)
            بازگشت qsv_transfer_data_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        بازگشت AVERROR(ENOSYS);
    }

    in.Info = out->Info;
    map_frame_to_surface(src_frame, &in);

    انجامبده {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_upload, &in, out, پوچ, &sync);
        اگر (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } وقتی (err == MFX_WRN_DEVICE_BUSY);

    اگر (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        بازگشت AVERROR_UNKNOWN;
    }

    انجامبده {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } وقتی (err == MFX_WRN_IN_EXECUTION);
    اگر (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        بازگشت AVERROR_UNKNOWN;
    }

    اگر (realigned) {
        out->Info.CropW = tmp_info.CropW;
        out->Info.CropH = tmp_info.CropH;
    }

    بازگشت 0;
}

ایستا صحیح qsv_dynamic_frames_derive_to(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, صحیح flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    انتخاب (src_ctx->device_ctx->type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        بشکن;
#endif

#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        اگر (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } وگرنه {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
    بشکن;
#endif

    پیشفرض:
        بازگشت AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, اندازه(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    بازگشت 0;
}

ایستا صحیح qsv_fixed_frames_derive_to(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, صحیح flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    صحیح i;

    انتخاب (src_ctx->device_ctx->type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 اندازه(*s->handle_pairs_internal));
            اگر (!s->handle_pairs_internal)
                بازگشت AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             اندازه(*s->surfaces_internal));
            اگر (!s->surfaces_internal)
                بازگشت AVERROR(ENOMEM);
            برای (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = src_hwctx->surface_ids + i;
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        بشکن;
#endif
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 اندازه(*s->handle_pairs_internal));
            اگر (!s->handle_pairs_internal)
                بازگشت AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_ctx->initial_pool_size,
                                             اندازه(*s->surfaces_internal));
            اگر (!s->surfaces_internal)
                بازگشت AVERROR(ENOMEM);
            برای (i = 0; i < src_ctx->initial_pool_size; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                اگر (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                } وگرنه {
                    s->handle_pairs_internal[i].second = (mfxMemId)src_hwctx->texture_infos[i].index;
                }
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_size;
            اگر (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            } وگرنه {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
            }
        }
        بشکن;
#endif
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 اندازه(*s->handle_pairs_internal));
            اگر (!s->handle_pairs_internal)
                بازگشت AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             اندازه(*s->surfaces_internal));
            اگر (!s->surfaces_internal)
                بازگشت AVERROR(ENOMEM);
            برای (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            اگر (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            وگرنه
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        بشکن;
#endif
    پیشفرض:
        بازگشت AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    بازگشت 0;
}

ایستا صحیح qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, صحیح flags)
{
    اگر (src_ctx->initial_pool_size < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        بازگشت AVERROR(EINVAL);
    } وگرنه اگر (src_ctx->initial_pool_size == 0) {
        بازگشت qsv_dynamic_frames_derive_to(dst_ctx, src_ctx, flags);
    } وگرنه {
        بازگشت qsv_fixed_frames_derive_to(dst_ctx, src_ctx, flags);
    }
}

ایستا صحیح qsv_fixed_pool_map_to(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    صحیح i, err, index = -1;

    برای (i = 0; i < hwctx->nb_surfaces && index < 0; i++) {
        انتخاب(src->format) {
#اگر CONFIG_VAAPI
        حالت AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            اگر (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->data[3])
                index = i;
            بشکن;
        }
#endif
#اگر CONFIG_D3D11VA
        حالت AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            اگر (pair->first == src->data[0]
                && (pair->second == src->data[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->data[1] == (uint8_t *)0)))
                index = i;
            بشکن;
        }
#endif
#اگر CONFIG_DXVA2
        حالت AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            اگر (pair->first == src->data[3])
                index = i;
            بشکن;
        }
#endif
        }
    }
    اگر (index < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        بازگشت AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, پوچ, پوچ);
    اگر (err)
        بازگشت err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)&hwctx->surfaces[index];

    بازگشت 0;
}

ایستا تهی qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_internal = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_pairs_internal = (mfxHDLPair *)surfaces_internal->Data.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_frames->data;

    انتخاب (src_ctx->format) {
#اگر CONFIG_VAAPI
    حالت AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_pairs_internal->first);

        بشکن;
    }
#endif

#اگر CONFIG_D3D11VA
    حالت AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        بشکن;
    }
#endif
    پیشفرض:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        بشکن;
    }

    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
}

ایستا صحیح qsv_dynamic_pool_map_to(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    mfxFrameSurface1 *surfaces_internal = پوچ;
    mfxHDLPair *handle_pairs_internal = پوچ;
    صحیح ret = 0;

    surfaces_internal = av_calloc(1, اندازه(*surfaces_internal));
    اگر (!surfaces_internal) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }

    handle_pairs_internal = av_calloc(1, اندازه(*handle_pairs_internal));
    اگر (!handle_pairs_internal) {
        ret = AVERROR(ENOMEM);
        برو fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_internal);
    اگر (ret < 0)
        برو fail;

    انتخاب (src->format) {
#اگر CONFIG_VAAPI
    حالت AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, اندازه(*surface_id_internal));
        اگر (!surface_id_internal) {
            ret =AVERROR(ENOMEM);
            برو fail;
        }

        *surface_id_internal = (VASurfaceID)(uintptr_t)src->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;

        بشکن;
    }
#endif

#اگر CONFIG_D3D11VA
    حالت AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_pairs_internal->first = (mfxMemId)src->data[0];

        اگر (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        } وگرنه {
            handle_pairs_internal->second = (mfxMemId)src->data[1];
        }

        بشکن;
    }
#endif
    پیشفرض:
        ret = AVERROR(ENOSYS);
        برو fail;
    }

    surfaces_internal->Data.MemId = (mfxMemId)handle_pairs_internal;

    ret = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_internal);
    اگر (ret)
        برو fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)surfaces_internal;

    بازگشت 0;

fail:
    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
    بازگشت ret;
}

ایستا صحیح qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    اگر (hwctx->nb_surfaces)
        بازگشت qsv_fixed_pool_map_to(dst_ctx, dst, src, flags);
    وگرنه
        بازگشت qsv_dynamic_pool_map_to(dst_ctx, dst, src, flags);
}

ایستا صحیح qsv_frames_get_constraints(AVHWDeviceContext *ctx,
                                      ثابت تهی *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    صحیح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    اندازه(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        بازگشت AVERROR(ENOMEM);

    برای (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, اندازه(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats)
        بازگشت AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    بازگشت 0;
}

ایستا تهی qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    اگر (hwctx->session)
        MFXClose(hwctx->session);

    اگر (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_buffer_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

ایستا mfxIMPL choose_implementation(ثابت نویسه *device, شمارش AVHWDeviceType child_device_type)
{
    ایستا ثابت ساختار {
        ثابت نویسه *name;
        mfxIMPL     impl;
    } impl_map[] = {
        { "auto",     MFX_IMPL_AUTO         },
        { "sw",       MFX_IMPL_SOFTWARE     },
        { "hw",       MFX_IMPL_HARDWARE     },
        { "auto_any", MFX_IMPL_AUTO_ANY     },
        { "hw_any",   MFX_IMPL_HARDWARE_ANY },
        { "hw2",      MFX_IMPL_HARDWARE2    },
        { "hw3",      MFX_IMPL_HARDWARE3    },
        { "hw4",      MFX_IMPL_HARDWARE4    },
    };

    mfxIMPL impl = MFX_IMPL_AUTO_ANY;
    صحیح i;

    اگر (device) {
        برای (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            اگر (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                بشکن;
            }
        اگر (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, پوچ, 0);
    }

    اگر (impl != MFX_IMPL_SOFTWARE) {
        اگر (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_VIA_D3D11;
        وگرنه اگر (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_VIA_D3D9;
    }

    بازگشت impl;
}

ایستا صحیح qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        صحیح flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfxVersion    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfxStatus     err;
    صحیح ret;

    انتخاب (child_device_ctx->type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        بشکن;
#endif
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        بشکن;
#endif
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        بشکن;
#endif
    پیشفرض:
        ret = AVERROR(ENOSYS);
        برو fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    اگر (ret)
        برو fail;

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    اگر (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        برو fail;
    }

    بازگشت 0;

fail:
    اگر (hwctx->session)
        MFXClose(hwctx->session);

    اگر (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = پوچ;
    hwctx->loader = پوچ;
    بازگشت ret;
}

ایستا صحیح qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, صحیح flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(اندازه(*priv));
    اگر (!priv)
        بازگشت AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->آزاد = qsv_device_free;

    impl = choose_implementation("hw_any", child_device_ctx->type);
    بازگشت qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

ایستا صحیح qsv_device_create(AVHWDeviceContext *ctx, ثابت نویسه *device,
                             AVDictionary *opts, صحیح flags)
{
    QSVDevicePriv *priv;
    شمارش AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    صحیح ret;

    priv = av_mallocz(اندازه(*priv));
    اگر (!priv)
        بازگشت AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->آزاد        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", پوچ, 0);
    اگر (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->مقدار);
        اگر (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->مقدار);
            بازگشت AVERROR(EINVAL);
        }
#اگر QSV_ONEVPL
    } وگرنه اگر (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } وگرنه اگر (CONFIG_DXVA2) {
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
#وگرنه
    } وگرنه اگر (CONFIG_DXVA2) {
        av_log(پوچ, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } وگرنه اگر (CONFIG_D3D11VA) {
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#endif
    } وگرنه اگر (CONFIG_VAAPI) {
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } وگرنه {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        بازگشت AVERROR(ENOSYS);
    }

#اگر CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    اگر (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->مقدار);
        بازگشت AVERROR(EINVAL);
    }
#endif

    child_device_opts = پوچ;
    انتخاب (child_device_type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_set(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_set(&child_device_opts, "driver",    "iHD",    0);
        }
        بشکن;
#endif
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_set(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        بشکن;
#endif
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
#اگر QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#endif
        بشکن;
#endif
    پیشفرض:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            بازگشت AVERROR(ENOSYS);
        }
        بشکن;
    }

    e = av_dict_get(opts, "child_device", پوچ, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->مقدار : پوچ, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    اگر (ret < 0)
        بازگشت ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->data;

    impl = choose_implementation(device, child_device_type);

    بازگشت qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

ثابت HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_size      = اندازه(QSVDeviceContext),
    .frames_hwctx_size      = اندازه(QSVFramesContext),

    .device_create          = qsv_device_create,
    .device_derive          = qsv_device_derive,
    .device_init            = qsv_device_init,
    .frames_get_constraints = qsv_frames_get_constraints,
    .frames_init            = qsv_frames_init,
    .frames_uninit          = qsv_frames_uninit,
    .frames_get_buffer      = qsv_get_buffer,
    .transfer_get_formats   = qsv_transfer_get_formats,
    .transfer_data_to       = qsv_transfer_data_to,
    .transfer_data_from     = qsv_transfer_data_from,
    .map_to                 = qsv_map_to,
    .map_from               = qsv_map_from,
    .frames_derive_to       = qsv_frames_derive_to,
    .frames_derive_from     = qsv_frames_derive_from,

    .pix_fmts = (ثابت شمارش AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
