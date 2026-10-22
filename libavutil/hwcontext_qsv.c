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

#अन्तर्भाव <stdatomic.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव <mfxvideo.h>

#अन्तर्भाव "config.h"

#जर HAVE_PTHREADS
#अन्तर्भाव <pthread.h>
#endif

#define COBJMACROS
#जर CONFIG_VAAPI
#अन्तर्भाव "hwcontext_vaapi.h"
#endif
#जर CONFIG_D3D11VA
#अन्तर्भाव "hwcontext_d3d11va.h"
#endif
#जर CONFIG_DXVA2
#अन्तर्भाव <initguid.h>
#अन्तर्भाव "hwcontext_dxva2.h"
#endif

#अन्तर्भाव "buffer.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "hwcontext_qsv.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "time.h"
#अन्तर्भाव "imgutils.h"
#अन्तर्भाव "avassert.h"

#define QSV_VERSION_ATLEAST(MAJOR, MINOR)   \
    (MFX_VERSION_MAJOR > (MAJOR) ||         \
     MFX_VERSION_MAJOR == (MAJOR) && MFX_VERSION_MINOR >= (MINOR))

#define QSV_RUNTIME_VERSION_ATLEAST(MFX_VERSION, MAJOR, MINOR)          \
    ((MFX_VERSION.Major > (MAJOR)) ||                                   \
     (MFX_VERSION.Major == (MAJOR) && MFX_VERSION.Minor >= (MINOR)))

#define MFX_IMPL_VIA_MASK(impl) (0x0f00 & (impl))
#define QSV_ONEVPL       QSV_VERSION_ATLEAST(2, 0)
#define QSV_HAVE_OPAQUE  !QSV_ONEVPL

#जर QSV_ONEVPL
#अन्तर्भाव <mfxdispatcher.h>
#अन्यथा
#define MFXUnload(a) करा { } पर्यंत(0)
#endif

प्रकारव्याख्या संरचना QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

प्रकारव्याख्या संरचना QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfxVersion          ver;
    mfxIMPL             impl;

    गणना AVHWDeviceType child_device_type;
    गणना AVPixelFormat  child_pix_fmt;
} QSVDeviceContext;

प्रकारव्याख्या संरचना QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#जर HAVE_PTHREADS
    pthread_mutex_t session_lock;
#endif

    AVBufferRef *child_frames_ref;
    mfxFrameSurface1 *surfaces_internal;
    mfxHDLPair *handle_pairs_internal;
    पूर्णांक             nb_surfaces_used;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#जर QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfxExtBuffer *ext_buffers[1];
#endif
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

प्रकारव्याख्या संरचना QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

स्थिर स्थिरांक संरचना {
    गणना AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_shift;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#जर CONFIG_VAAPI
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
#जर QSV_VERSION_ATLEAST(1, 31)
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

बाह्य पूर्णांक ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          गणना AVHWDeviceType base_dev_type,
                                          शून्य **base_handle);

स्थिर पूर्णांक qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
पूर्णांक ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                   गणना AVHWDeviceType base_dev_type,
                                   शून्य **base_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->Data.MemId;
    निवड (base_dev_type) {
#जर CONFIG_VAAPI
    स्थिती AV_HWDEVICE_TYPE_VAAPI:
        base_handle[0] = handle_pair->first;
        परत 0;
#endif
#जर CONFIG_D3D11VA
    स्थिती AV_HWDEVICE_TYPE_D3D11VA:
        base_handle[0] = handle_pair->first;
        base_handle[1] = handle_pair->second;
        परत 0;
#endif
#जर CONFIG_DXVA2
    स्थिती AV_HWDEVICE_TYPE_DXVA2:
        base_handle[0] = handle_pair->first;
        परत 0;
#endif
    }
    परत AVERROR(EINVAL);
}

स्थिर uint32_t qsv_fourcc_from_pix_fmt(गणना AVPixelFormat pix_fmt)
{
    पूर्णांक i;
    साठी (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        जर (supported_pixel_formats[i].pix_fmt == pix_fmt)
            परत supported_pixel_formats[i].fourcc;
    }
    परत 0;
}

स्थिर uint16_t qsv_shift_from_pix_fmt(गणना AVPixelFormat pix_fmt)
{
    साठी (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        जर (supported_pixel_formats[i].pix_fmt == pix_fmt)
            परत supported_pixel_formats[i].mfx_shift;
    }

    परत 0;
}

#जर CONFIG_D3D11VA
स्थिर uint32_t qsv_get_d3d11va_bind_flags(पूर्णांक mem_type)
{
    uint32_t bind_flags = 0;

    जर ((mem_type & MFX_MEMTYPE_VIDEO_MEMORY_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_INTERNAL_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    अन्यथा
        bind_flags = D3D11_BIND_DECODER;

    जर ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    परत bind_flags;
}
#endif

स्थिर पूर्णांक qsv_fill_border(AVFrame *dst, स्थिरांक AVFrame *src)
{
    स्थिरांक AVPixFmtDescriptor *desc;
    पूर्णांक i, planes_nb = 0;
    जर (dst->format != src->format)
        परत AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    साठी (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    साठी (i = 0; i < planes_nb; i++) {
        पूर्णांक sheight, dheight, y;
        सूचक_भेद_प्रकार swidth = av_image_get_linesize(src->format,
                                                 src->width,
                                                 i);
        सूचक_भेद_प्रकार dwidth = av_image_get_linesize(dst->format,
                                                 dst->width,
                                                 i);
        स्थिरांक AVComponentDescriptor comp = desc->comp[i];
        जर (swidth < 0 || dwidth < 0) {
            av_log(रिक्त, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            परत AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        जर (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        साठी (y = 0; y < sheight; y++) {
            शून्य *ओळ_ptr = dst->data[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(ओळ_ptr,
                           comp.depth > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        साठी (y = sheight; y < dheight; y++) {
            स_नकल(dst->data[i]+y*dst->linesize[i],
                   dst->data[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    परत 0;
}

स्थिर पूर्णांक qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    पूर्णांक   hw_handle_supported = 0;
    mfxHandleType handle_type;
    गणना AVHWDeviceType device_type;
    गणना AVPixelFormat  pix_fmt;
    mfxStatus err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    जर (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    जर (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        परत AVERROR_UNKNOWN;
    }

    जर (MFX_IMPL_VIA_VAAPI == MFX_IMPL_VIA_MASK(s->impl)) {
#जर CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#endif
    } अन्यथा जर (MFX_IMPL_VIA_D3D11 == MFX_IMPL_VIA_MASK(s->impl)) {
#जर CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#endif
    } अन्यथा जर (MFX_IMPL_VIA_D3D9 == MFX_IMPL_VIA_MASK(s->impl)) {
#जर CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#endif
    }

    जर (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        जर (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->child_device_type = device_type;
            s->child_pix_fmt     = pix_fmt;
        }
    }
    जर (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    परत 0;
}

स्थिर शून्य qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    जर (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = रिक्त;
    s->session_download_init = 0;

    जर (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = रिक्त;
    s->session_upload_init = 0;

#जर HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_lock);
#endif

    av_freep(&s->mem_ids);
#जर QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#endif
    av_freep(&s->surfaces_internal);
    av_freep(&s->handle_pairs_internal);
    av_frame_unref(&s->realigned_upload_frame);
    av_frame_unref(&s->realigned_download_frame);
    av_buffer_unref(&s->child_frames_ref);
}

स्थिर शून्य qsv_pool_release_dummy(शून्य *opaque, uint8_t *data)
{
}

स्थिर शून्य qsv_pool_release(शून्य *opaque, uint8_t *data)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)data;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.Data.MemId;
    AVHWFramesContext *child_frames_ctx;

    जर (!s->child_frames_ref)
        परत;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    जर (!child_frames_ctx->device_ctx)
        परत;

#जर CONFIG_VAAPI
    जर (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#endif

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

स्थिर AVBufferRef *qsv_fixed_pool_alloc(शून्य *opaque, माप_प्रकार size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    जर (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        परत av_buffer_create((uint8_t*)(s->surfaces_internal + s->nb_surfaces_used - 1),
                                आकार(*hwctx->surfaces), qsv_pool_release_dummy, रिक्त, 0);
    }

    परत रिक्त;
}

स्थिर AVBufferRef *qsv_dynamic_pool_alloc(शून्य *opaque, माप_प्रकार size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx;
    QSVSurface *qsv_surface = रिक्त;
    mfxHDLPair *handle_pairs_internal = रिक्त;
    पूर्णांक ret;

    जर (!s->child_frames_ref)
        जा fail;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    जर (!child_frames_ctx->device_ctx)
        जा fail;

#जर CONFIG_DXVA2
    जर (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        जा fail;
    }
#endif

    qsv_surface = av_calloc(1, आकार(*qsv_surface));
    जर (!qsv_surface)
        जा fail;

    qsv_surface->child_frame = av_frame_alloc();
    जर (!qsv_surface->child_frame)
        जा fail;

    ret = av_hwframe_get_buffer(s->child_frames_ref, qsv_surface->child_frame, 0);
    जर (ret < 0)
        जा fail;

    handle_pairs_internal = av_calloc(1, आकार(*handle_pairs_internal));
    जर (!handle_pairs_internal)
        जा fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    जर (ret < 0)
        जा fail;

#जर CONFIG_VAAPI
    जर (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, आकार(*surface_id_internal));
        जर (!surface_id_internal)
            जा fail;

        *surface_id_internal = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
    }
#endif

#जर CONFIG_D3D11VA
    जर (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        handle_pairs_internal->first = (mfxMemId)qsv_surface->child_frame->data[0];

        जर (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        अन्यथा
            handle_pairs_internal->second = (mfxMemId)qsv_surface->child_frame->data[1];

    }
#endif

    qsv_surface->mfx_surface.Data.MemId = (mfxMemId)handle_pairs_internal;
    परत av_buffer_create((uint8_t *)qsv_surface, आकार(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    जर (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_pairs_internal);

    परत रिक्त;
}

स्थिर AVBufferRef *qsv_pool_alloc(शून्य *opaque, माप_प्रकार size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    जर (hwctx->nb_surfaces == 0) {
        परत qsv_dynamic_pool_alloc(opaque, size);
    } अन्यथा {
        परत qsv_fixed_pool_alloc(opaque, size);
    }
}

स्थिर पूर्णांक qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = रिक्त;
    AVBufferRef *child_frames_ref = रिक्त;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    पूर्णांक i, ret = 0;

    जर (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        परत AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    जर (!child_device_ref)
        परत AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->data;

#जर CONFIG_VAAPI
    जर (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#endif
#जर CONFIG_D3D11VA
    जर (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        ID3D11Device_AddRef((ID3D11Device*)device_priv->handle);
        child_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#endif
#जर CONFIG_DXVA2
    जर (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#endif

    ret = av_hwdevice_ctx_init(child_device_ref);
    जर (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        जा fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    जर (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        जा fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->data;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_size = ctx->initial_pool_size;
    child_frames_ctx->width             = FFALIGN(ctx->width, 16);
    child_frames_ctx->height            = FFALIGN(ctx->height, 16);

#जर CONFIG_D3D11VA
    जर (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        जर (hwctx->frame_type == 0)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        जर (hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
            child_frames_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        child_frames_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->frame_type);
    }
#endif
#जर CONFIG_DXVA2
    जर (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        जर (hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET)
            child_frames_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        अन्यथा
            child_frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#endif

    ret = av_hwframe_ctx_init(child_frames_ref);
    जर (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        जा fail;
    }

#जर CONFIG_VAAPI
    जर (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        साठी (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = child_frames_hwctx->surface_ids + i;
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif
#जर CONFIG_D3D11VA
    जर (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        साठी (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->texture_infos[i].texture;
            जर(child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            } अन्यथा {
                s->handle_pairs_internal[i].second = (mfxMemId)child_frames_hwctx->texture_infos[i].index;
            }
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        जर (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } अन्यथा {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
#endif
#जर CONFIG_DXVA2
    जर (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        साठी (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->surfaces[i];
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        जर (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        अन्यथा
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = रिक्त;

fail:
    av_buffer_unref(&child_device_ref);
    av_buffer_unref(&child_frames_ref);
    परत ret;
}

स्थिर पूर्णांक qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    स्थिरांक AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    जर (!desc)
        परत AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    जर (!fourcc)
        परत AVERROR(EINVAL);

    surf->Info.BitDepthLuma   = desc->comp[0].depth;
    surf->Info.BitDepthChroma = desc->comp[0].depth;
    surf->Info.Shift          = qsv_shift_from_pix_fmt(ctx->sw_format);

    जर (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    अन्यथा जर (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    अन्यथा
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.Width          = FFALIGN(ctx->width, 16);
    surf->Info.CropW          = ctx->width;
    surf->Info.Height         = FFALIGN(ctx->height, 16);
    surf->Info.CropH          = ctx->height;
    surf->Info.FrameRateExtN  = 25;
    surf->Info.FrameRateExtD  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    परत 0;
}

स्थिर पूर्णांक qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    पूर्णांक i, ret = 0;

    जर (ctx->initial_pool_size < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        परत AVERROR(EINVAL);
    } अन्यथा जर (ctx->initial_pool_size == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        जर (ret < 0)
            परत ret;

        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(आकार(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, रिक्त);
        जर (!ffhwframesctx(ctx)->pool_internal)
            परत AVERROR(ENOMEM);

        स_रखो(&mfx_surf1, 0, आकार(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        frames_hwctx->info = &s->frame_info;
        frames_hwctx->nb_surfaces = 0;

        परत 0;
    }

    s->handle_pairs_internal = av_calloc(ctx->initial_pool_size,
                                         आकार(*s->handle_pairs_internal));
    जर (!s->handle_pairs_internal)
        परत AVERROR(ENOMEM);

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     आकार(*s->surfaces_internal));
    जर (!s->surfaces_internal)
        परत AVERROR(ENOMEM);

    साठी (i = 0; i < ctx->initial_pool_size; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_internal[i]);
        जर (ret < 0)
            परत ret;
    }

#जर QSV_HAVE_OPAQUE
    जर (!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        जर (ret < 0)
            परत ret;
    }
#अन्यथा
    ret = qsv_init_child_ctx(ctx);
    जर (ret < 0)
        परत ret;
#endif

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(आकार(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, रिक्त);
    जर (!ffhwframesctx(ctx)->pool_internal)
        परत AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    परत 0;
}

स्थिर mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    जर (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        परत MFX_ERR_UNSUPPORTED;
    जर (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        परत MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->अंक_Frame_Actual = hwctx->nb_surfaces;

    परत MFX_ERR_NONE;
}

स्थिर mfxStatus frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    परत MFX_ERR_NONE;
}

स्थिर mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    परत MFX_ERR_UNSUPPORTED;
}

स्थिर mfxStatus frame_unlock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    परत MFX_ERR_UNSUPPORTED;
}

स्थिर mfxStatus frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    जर (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    परत MFX_ERR_NONE;
}

#जर QSV_ONEVPL

स्थिर पूर्णांक qsv_d3d11_update_config(शून्य *ctx, mfxHDL handle, mfxConfig cfg)
{
    पूर्णांक ret = AVERROR_UNKNOWN;
#जर CONFIG_D3D11VA
    mfxStatus sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = रिक्त;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_मूल्य = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (शून्य**)&pDXGIDevice);
    जर (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        जर (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            परत ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        जर (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            जा fail;
        }
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        परत ret;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_U16;
    impl_मूल्य.Data.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिरांक mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_मूल्य);
    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        जा fail;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_PTR;
    impl_मूल्य.Data.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिरांक mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_मूल्य);
    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        जा fail;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_U32;
    impl_मूल्य.Data.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिरांक mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_मूल्य);
    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        जा fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#endif
    परत ret;
}

स्थिर पूर्णांक qsv_d3d9_update_config(शून्य *ctx, mfxHDL handle, mfxConfig cfg)
{
    पूर्णांक ret = AVERROR_UNKNOWN;
#जर CONFIG_DXVA2
    mfxStatus sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = रिक्त;
    IDirect3DDevice9Ex *device_ex = रिक्त;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = रिक्त;
    IDirect3D9 *d3d9 = रिक्त;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_मूल्य = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        जा fail;
    }

    hr = IDirect3DDeviceManager9_LockDevice(devmgr, device_handle, &device, TRUE);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        जा fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (शून्य **)&device_ex);
    IDirect3DDevice9_Release(device);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        जा unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        जा unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        जा unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (शून्य **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        जा unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    जर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        जा release;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_PTR;
    impl_मूल्य.Data.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिरांक mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_मूल्य);
    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        जा release;
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
    परत ret;
}

स्थिर पूर्णांक qsv_va_update_config(शून्य *ctx, mfxHDL handle, mfxConfig cfg)
{
#जर CONFIG_VAAPI
#जर VA_CHECK_VERSION(1, 15, 0)
    mfxStatus sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_मूल्य = {0};

    vas = vaGetDisplayAttributes(dpy, &attr, 1);
    जर (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_मूल्य.Type = MFX_VARIANT_TYPE_U16;
        impl_मूल्य.Data.U16 = (attr.मूल्य & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (स्थिरांक mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_मूल्य);
        जर (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            जा fail;
        }
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        जा fail;
    }

    परत 0;

fail:
#अन्यथा
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#endif
#endif
    परत AVERROR_UNKNOWN;
}

स्थिर पूर्णांक qsv_new_mfx_loader(शून्य *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfxVersion *pver,
                              शून्य **ploader)
{
    mfxStatus sts;
    mfxLoader loader = रिक्त;
    mfxConfig cfg;
    mfxVariant impl_मूल्य = {0};

    *ploader = रिक्त;
    loader = MFXLoad();
    जर (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        जा fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    जर (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        जा fail;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_U32;
    impl_मूल्य.Data.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिरांक mfxU8 *)"mfxImplDescription.Impl", impl_मूल्य);
    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        जा fail;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_U32;
    impl_मूल्य.Data.U32 = pver->Version;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिरांक mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_मूल्य);
    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        जा fail;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_U32;
    impl_मूल्य.Data.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिरांक mfxU8 *)"mfxImplDescription.VendorID", impl_मूल्य);
    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        जा fail;
    }

    जर (MFX_HANDLE_VA_DISPLAY == handle_type) {
        जर (handle && qsv_va_update_config(ctx, handle, cfg))
            जा fail;

        impl_मूल्य.Data.U32 = MFX_ACCEL_MODE_VIA_VAAPI;
    } अन्यथा जर (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        जर (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            जा fail;

        impl_मूल्य.Data.U32 = MFX_ACCEL_MODE_VIA_D3D9;
    } अन्यथा {
        जर (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            जा fail;

        impl_मूल्य.Data.U32 = MFX_ACCEL_MODE_VIA_D3D11;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिरांक mfxU8 *)"mfxImplDescription.AccelerationMode", impl_मूल्य);
    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        जा fail;
    }

    *ploader = loader;

    परत 0;

fail:
    जर (loader)
        MFXUnload(loader);

    परत AVERROR_UNKNOWN;
}

स्थिर पूर्णांक qsv_create_mfx_session_from_loader(शून्य *ctx, mfxLoader loader, mfxSession *psession)
{
    mfxStatus sts;
    mfxSession session = रिक्त;
    uint32_t impl_idx = 0;
    mfxVersion ver;

    पर्यंत (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        जर (sts == MFX_ERR_NOT_FOUND)
            थांबा;
        अन्यथा जर (sts != MFX_ERR_NONE) {
            impl_idx++;
            सुरूठेवा;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        जर (sts == MFX_ERR_NONE)
            थांबा;

        impl_idx++;
    }

    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        जा fail;
    }

    sts = MFXQueryVersion(session, &ver);
    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        जा fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    परत 0;

fail:
    जर (session)
        MFXClose(session);

    परत AVERROR_UNKNOWN;
}

स्थिर पूर्णांक qsv_create_mfx_session(शून्य *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  शून्य **ploader)
{
    mfxLoader loader = रिक्त;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    जर (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        परत AVERROR(EXDEV);
    }

    *psession = रिक्त;

    जर (!*ploader) {
        जर (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (शून्य **)&loader))
            जा fail;

        av_assert0(loader);
    } अन्यथा
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    जर (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        जा fail;

    जर (!*ploader)
        *ploader = loader;

    परत 0;

fail:
    जर (!*ploader && loader)
        MFXUnload(loader);

    परत AVERROR_UNKNOWN;
}

#अन्यथा

स्थिर पूर्णांक qsv_create_mfx_session(शून्य *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  शून्य **ploader)
{
    mfxVersion ver;
    mfxStatus sts;
    mfxSession session = रिक्त;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    *ploader = रिक्त;
    *psession = रिक्त;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        जा fail;
    }

    sts = MFXQueryVersion(session, &ver);
    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        जा fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    जर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        जा fail;
    }

    *psession = session;

    परत 0;

fail:
    जर (session)
        MFXClose(session);

    परत AVERROR_UNKNOWN;
}

#endif

स्थिर पूर्णांक qsv_init_internal_session(AVHWFramesContext *ctx,
                                     mfxSession *session, पूर्णांक upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    पूर्णांक opaque = 0;

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
    पूर्णांक                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    शून्य             **loader = &hwctx->loader;
    mfxSession parent_session = hwctx->session;
    mfxIMPL impl;
    mfxVersion ver;

    err = MFXQueryIMPL(parent_session, &impl);
    जर (err == MFX_ERR_NONE)
        err = MFXQueryVersion(parent_session, &ver);
    जर (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        परत AVERROR_UNKNOWN;
    }

#जर QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    जर (ret)
        जा fail;

    जर (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        जर (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            जा fail;
        }
    }

    जर (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        जर (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            जा fail;
        }
    }

    जर (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        जर (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            जा fail;
        }
    }

    स_रखो(&par, 0, आकार(par));

    जर (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_OUT_VIDEO_MEMORY :
                                 MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
#जर QSV_HAVE_OPAQUE
    अन्यथा {
        par.ExtParam    = s->ext_buffers;
        par.अंक_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
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
    जर (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        जा fail;
    }

    परत 0;

fail:
    जर (*session)
        MFXClose(*session);

    *session = रिक्त;

    परत ret;
}

स्थिर पूर्णांक qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    पूर्णांक opaque = 0;

    uint32_t fourcc;
    पूर्णांक i, ret;

#जर QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    जर (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        परत AVERROR(ENOSYS);
    }

    जर (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        जर (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            परत ret;
        }
    }

    जर (!opaque) {
        s->mem_ids = av_calloc(frames_hwctx->nb_surfaces, आकार(*s->mem_ids));
        जर (!s->mem_ids)
            परत AVERROR(ENOMEM);

        साठी (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].Data.MemId;
    }
#जर QSV_HAVE_OPAQUE
    अन्यथा {
        s->surface_ptrs = av_calloc(frames_hwctx->nb_surfaces,
                                    आकार(*s->surface_ptrs));
        जर (!s->surface_ptrs)
            परत AVERROR(ENOMEM);

        साठी (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.अंक_Surface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = आकार(s->opaque_alloc);

        s->ext_buffers[0] = (mfxExtBuffer*)&s->opaque_alloc;
    }
#endif

    s->session_download = रिक्त;
    s->session_upload   = रिक्त;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#जर HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, रिक्त);
#endif

    परत 0;
}

स्थिर पूर्णांक qsv_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    जर (!frame->buf[0])
        परत AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_QSV;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    परत 0;
}

स्थिर पूर्णांक qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    गणना AVHWFrameTransferDirection dir,
                                    गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts;

    fmts = av_malloc_array(2, आकार(*fmts));
    जर (!fmts)
        परत AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    परत 0;
}

स्थिर पूर्णांक qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, पूर्णांक flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    पूर्णांक i;

    निवड (dst_ctx->device_ctx->type) {
#जर CONFIG_VAAPI
    स्थिती AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               आकार(*dst_hwctx->surface_ids));
            जर (!dst_hwctx->surface_ids)
                परत AVERROR(ENOMEM);
            साठी (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        थांबा;
#endif
#जर CONFIG_D3D11VA
    स्थिती AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_size = src_ctx->initial_pool_size;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 आकार(*dst_hwctx->texture_infos));
            जर (!dst_hwctx->texture_infos)
                परत AVERROR(ENOMEM);
            जर (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            साठी (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].index = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            जर (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } अन्यथा
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        थांबा;
#endif
#जर CONFIG_DXVA2
    स्थिती AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            आकार(*dst_hwctx->surfaces));
            जर (!dst_hwctx->surfaces)
                परत AVERROR(ENOMEM);
            साठी (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            जर (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            अन्यथा
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        थांबा;
#endif
    पूर्वनिर्धारित:
        परत AVERROR(ENOSYS);
    }

    परत 0;
}

स्थिर पूर्णांक qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, स्थिरांक AVFrame *src, पूर्णांक flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->data[3];
    AVHWFramesContext *child_frames_ctx;
    स्थिरांक AVPixFmtDescriptor *desc;
    uint8_t *child_data;
    AVFrame *dummy;
    पूर्णांक ret = 0;

    जर (!s->child_frames_ref)
        परत AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;

    निवड (child_frames_ctx->device_ctx->type) {
#जर CONFIG_VAAPI
    स्थिती AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_data = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        थांबा;
    }
#endif
#जर CONFIG_D3D11VA
    स्थिती AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        थांबा;
    }
#endif
#जर CONFIG_DXVA2
    स्थिती AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        थांबा;
    }
#endif
    पूर्वनिर्धारित:
        परत AVERROR(ENOSYS);
    }

    जर (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, रिक्त, रिक्त);
        जर (ret < 0)
            परत ret;

        dst->width   = src->width;
        dst->height  = src->height;

       जर (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
            dst->data[0] = pair->first;
            dst->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } अन्यथा {
            dst->data[3] = child_data;
        }

        परत 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    जर (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        परत AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    जर (!dummy)
        परत AVERROR(ENOMEM);

    dummy->buf[0]        = av_buffer_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_buffer_ref(s->child_frames_ref);
    जर (!dummy->buf[0] || !dummy->hw_frames_ctx)
        जा fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;

    जर (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        dummy->data[0] = pair->first;
        dummy->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } अन्यथा {
        dummy->data[3] = child_data;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    परत ret;
}

स्थिर पूर्णांक qsv_transfer_data_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   स्थिरांक AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    पूर्णांक download = !!src->hw_frames_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->data[3] : dst->data[3]);

    AVFrame *dummy;
    पूर्णांक ret;

    dummy = av_frame_alloc();
    जर (!dummy)
        परत AVERROR(ENOMEM);

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->data[3]       = surf->Data.MemId;
    dummy->hw_frames_ctx = s->child_frames_ref;

    ret = download ? av_hwframe_transfer_data(dst, dummy, 0) :
                     av_hwframe_transfer_data(dummy, src, 0);

    dummy->buf[0]        = रिक्त;
    dummy->data[3]       = रिक्त;
    dummy->hw_frames_ctx = रिक्त;

    av_frame_free(&dummy);

    परत ret;
}

स्थिर पूर्णांक map_frame_to_surface(स्थिरांक AVFrame *frame, mfxFrameSurface1 *surface)
{
    निवड (frame->format) {
    स्थिती AV_PIX_FMT_NV12:
    स्थिती AV_PIX_FMT_P010:
    स्थिती AV_PIX_FMT_P012:
        surface->Data.Y  = frame->data[0];
        surface->Data.UV = frame->data[1];
        थांबा;

    स्थिती AV_PIX_FMT_YUV420P:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[1];
        surface->Data.V = frame->data[2];
        थांबा;

    स्थिती AV_PIX_FMT_BGRA:
        surface->Data.B = frame->data[0];
        surface->Data.G = frame->data[0] + 1;
        surface->Data.R = frame->data[0] + 2;
        surface->Data.A = frame->data[0] + 3;
        थांबा;
    स्थिती AV_PIX_FMT_YUYV422:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.V = frame->data[0] + 3;
        थांबा;

    स्थिती AV_PIX_FMT_Y210:
    स्थिती AV_PIX_FMT_Y212:
        surface->Data.Y16 = (mfxU16 *)frame->data[0];
        surface->Data.U16 = (mfxU16 *)frame->data[0] + 1;
        surface->Data.V16 = (mfxU16 *)frame->data[0] + 3;
        थांबा;
    स्थिती AV_PIX_FMT_VUYX:
        surface->Data.V = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.Y = frame->data[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 3;
        थांबा;
    स्थिती AV_PIX_FMT_XV30:
        surface->Data.U = frame->data[0];
        थांबा;
    स्थिती AV_PIX_FMT_XV36:
        surface->Data.U = frame->data[0];
        surface->Data.Y = frame->data[0] + 2;
        surface->Data.V = frame->data[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 6;
        थांबा;
#जर CONFIG_VAAPI
    स्थिती AV_PIX_FMT_UYVY422:
        surface->Data.Y = frame->data[0] + 1;
        surface->Data.U = frame->data[0];
        surface->Data.V = frame->data[0] + 2;
        थांबा;
#endif
    पूर्वनिर्धारित:
        परत MFX_ERR_UNSUPPORTED;
    }
    surface->Data.Pitch     = frame->linesize[0];
    surface->Data.TimeStamp = frame->pts;

    परत 0;
}

स्थिर पूर्णांक qsv_internal_session_check_init(AVHWFramesContext *ctx, पूर्णांक upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    पूर्णांक ret = 0;

    जर (atomic_load(inited))
        परत 0;

#जर HAVE_PTHREADS
    pthread_mutex_lock(&s->session_lock);
#endif

    जर (!atomic_load(inited)) {
        ret = qsv_init_internal_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#जर HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_lock);
#endif

    परत ret;
}

स्थिर पूर्णांक qsv_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  स्थिरांक AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->data[3];

    mfxSyncPoint sync = रिक्त;
    mfxStatus err;
    पूर्णांक ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    पूर्णांक realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 0);
    जर (ret < 0)
        परत ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    जर (dst->height & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        जर (tmp_frame->format != dst->format ||
            tmp_frame->width  != FFALIGN(dst->linesize[0], 16) ||
            tmp_frame->height != FFALIGN(dst->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = dst->format;
            tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
            tmp_frame->height = FFALIGN(dst->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            जर (ret < 0)
                परत ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    जर (!s->session_download) {
        जर (s->child_frames_ref)
            परत qsv_transfer_data_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        परत AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst_frame, &out);

    करा {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, रिक्त, &sync);
        जर (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } पर्यंत (err == MFX_WRN_DEVICE_BUSY);

    जर (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        परत AVERROR_UNKNOWN;
    }

    करा {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } पर्यंत (err == MFX_WRN_IN_EXECUTION);
    जर (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        परत AVERROR_UNKNOWN;
    }

    जर (realigned) {
        tmp_frame->width  = dst->width;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        जर (ret < 0)
            परत ret;
    }

    परत 0;
}

स्थिर पूर्णांक qsv_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                स्थिरांक AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   in = {{ 0 }};
    mfxFrameSurface1 *out = (mfxFrameSurface1*)dst->data[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = रिक्त;
    mfxStatus err;
    पूर्णांक ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    स्थिरांक AVFrame *src_frame;
    पूर्णांक realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 1);
    जर (ret < 0)
        परत ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    जर (src->height & 15 || src->linesize[0] & 15) {
        realigned = 1;
        जर (tmp_frame->format != src->format ||
            tmp_frame->width  != FFALIGN(src->width, 16) ||
            tmp_frame->height != FFALIGN(src->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = src->format;
            tmp_frame->width  = FFALIGN(src->width, 16);
            tmp_frame->height = FFALIGN(src->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            जर (ret < 0)
                परत ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        जर (ret < 0) {
            av_frame_unref(tmp_frame);
            परत ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        जर (ret < 0) {
            av_frame_unref(tmp_frame);
            परत ret;
        }

        tmp_info = out->Info;
        out->Info.CropW = FFMIN(out->Info.Width,  tmp_frame->width);
        out->Info.CropH = FFMIN(out->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    जर (!s->session_upload) {
        जर (s->child_frames_ref)
            परत qsv_transfer_data_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        परत AVERROR(ENOSYS);
    }

    in.Info = out->Info;
    map_frame_to_surface(src_frame, &in);

    करा {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_upload, &in, out, रिक्त, &sync);
        जर (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } पर्यंत (err == MFX_WRN_DEVICE_BUSY);

    जर (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        परत AVERROR_UNKNOWN;
    }

    करा {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } पर्यंत (err == MFX_WRN_IN_EXECUTION);
    जर (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        परत AVERROR_UNKNOWN;
    }

    जर (realigned) {
        out->Info.CropW = tmp_info.CropW;
        out->Info.CropH = tmp_info.CropH;
    }

    परत 0;
}

स्थिर पूर्णांक qsv_dynamic_frames_derive_to(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, पूर्णांक flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    निवड (src_ctx->device_ctx->type) {
#जर CONFIG_VAAPI
    स्थिती AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        थांबा;
#endif

#जर CONFIG_D3D11VA
    स्थिती AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        जर (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } अन्यथा {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
    थांबा;
#endif

    पूर्वनिर्धारित:
        परत AVERROR(ENOSYS);
    }

    स_रखो(&mfx_surf1, 0, आकार(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    परत 0;
}

स्थिर पूर्णांक qsv_fixed_frames_derive_to(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, पूर्णांक flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    पूर्णांक i;

    निवड (src_ctx->device_ctx->type) {
#जर CONFIG_VAAPI
    स्थिती AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 आकार(*s->handle_pairs_internal));
            जर (!s->handle_pairs_internal)
                परत AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             आकार(*s->surfaces_internal));
            जर (!s->surfaces_internal)
                परत AVERROR(ENOMEM);
            साठी (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = src_hwctx->surface_ids + i;
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        थांबा;
#endif
#जर CONFIG_D3D11VA
    स्थिती AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 आकार(*s->handle_pairs_internal));
            जर (!s->handle_pairs_internal)
                परत AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_ctx->initial_pool_size,
                                             आकार(*s->surfaces_internal));
            जर (!s->surfaces_internal)
                परत AVERROR(ENOMEM);
            साठी (i = 0; i < src_ctx->initial_pool_size; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                जर (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                } अन्यथा {
                    s->handle_pairs_internal[i].second = (mfxMemId)src_hwctx->texture_infos[i].index;
                }
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_size;
            जर (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            } अन्यथा {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
            }
        }
        थांबा;
#endif
#जर CONFIG_DXVA2
    स्थिती AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 आकार(*s->handle_pairs_internal));
            जर (!s->handle_pairs_internal)
                परत AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             आकार(*s->surfaces_internal));
            जर (!s->surfaces_internal)
                परत AVERROR(ENOMEM);
            साठी (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            जर (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            अन्यथा
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        थांबा;
#endif
    पूर्वनिर्धारित:
        परत AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    परत 0;
}

स्थिर पूर्णांक qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, पूर्णांक flags)
{
    जर (src_ctx->initial_pool_size < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        परत AVERROR(EINVAL);
    } अन्यथा जर (src_ctx->initial_pool_size == 0) {
        परत qsv_dynamic_frames_derive_to(dst_ctx, src_ctx, flags);
    } अन्यथा {
        परत qsv_fixed_frames_derive_to(dst_ctx, src_ctx, flags);
    }
}

स्थिर पूर्णांक qsv_fixed_pool_map_to(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, स्थिरांक AVFrame *src, पूर्णांक flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    पूर्णांक i, err, index = -1;

    साठी (i = 0; i < hwctx->nb_surfaces && index < 0; i++) {
        निवड(src->format) {
#जर CONFIG_VAAPI
        स्थिती AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            जर (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->data[3])
                index = i;
            थांबा;
        }
#endif
#जर CONFIG_D3D11VA
        स्थिती AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            जर (pair->first == src->data[0]
                && (pair->second == src->data[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->data[1] == (uint8_t *)0)))
                index = i;
            थांबा;
        }
#endif
#जर CONFIG_DXVA2
        स्थिती AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            जर (pair->first == src->data[3])
                index = i;
            थांबा;
        }
#endif
        }
    }
    जर (index < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        परत AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, रिक्त, रिक्त);
    जर (err)
        परत err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)&hwctx->surfaces[index];

    परत 0;
}

स्थिर शून्य qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_internal = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_pairs_internal = (mfxHDLPair *)surfaces_internal->Data.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_frames->data;

    निवड (src_ctx->format) {
#जर CONFIG_VAAPI
    स्थिती AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_pairs_internal->first);

        थांबा;
    }
#endif

#जर CONFIG_D3D11VA
    स्थिती AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        थांबा;
    }
#endif
    पूर्वनिर्धारित:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        थांबा;
    }

    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
}

स्थिर पूर्णांक qsv_dynamic_pool_map_to(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, स्थिरांक AVFrame *src, पूर्णांक flags)
{
    mfxFrameSurface1 *surfaces_internal = रिक्त;
    mfxHDLPair *handle_pairs_internal = रिक्त;
    पूर्णांक ret = 0;

    surfaces_internal = av_calloc(1, आकार(*surfaces_internal));
    जर (!surfaces_internal) {
        ret = AVERROR(ENOMEM);
        जा fail;
    }

    handle_pairs_internal = av_calloc(1, आकार(*handle_pairs_internal));
    जर (!handle_pairs_internal) {
        ret = AVERROR(ENOMEM);
        जा fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_internal);
    जर (ret < 0)
        जा fail;

    निवड (src->format) {
#जर CONFIG_VAAPI
    स्थिती AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, आकार(*surface_id_internal));
        जर (!surface_id_internal) {
            ret =AVERROR(ENOMEM);
            जा fail;
        }

        *surface_id_internal = (VASurfaceID)(uintptr_t)src->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;

        थांबा;
    }
#endif

#जर CONFIG_D3D11VA
    स्थिती AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_pairs_internal->first = (mfxMemId)src->data[0];

        जर (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        } अन्यथा {
            handle_pairs_internal->second = (mfxMemId)src->data[1];
        }

        थांबा;
    }
#endif
    पूर्वनिर्धारित:
        ret = AVERROR(ENOSYS);
        जा fail;
    }

    surfaces_internal->Data.MemId = (mfxMemId)handle_pairs_internal;

    ret = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_internal);
    जर (ret)
        जा fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)surfaces_internal;

    परत 0;

fail:
    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
    परत ret;
}

स्थिर पूर्णांक qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, स्थिरांक AVFrame *src, पूर्णांक flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    जर (hwctx->nb_surfaces)
        परत qsv_fixed_pool_map_to(dst_ctx, dst, src, flags);
    अन्यथा
        परत qsv_dynamic_pool_map_to(dst_ctx, dst, src, flags);
}

स्थिर पूर्णांक qsv_frames_get_constraints(AVHWDeviceContext *ctx,
                                      स्थिरांक शून्य *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    पूर्णांक i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    आकार(*constraints->valid_sw_formats));
    जर (!constraints->valid_sw_formats)
        परत AVERROR(ENOMEM);

    साठी (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, आकार(*constraints->valid_hw_formats));
    जर (!constraints->valid_hw_formats)
        परत AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    परत 0;
}

स्थिर शून्य qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    जर (hwctx->session)
        MFXClose(hwctx->session);

    जर (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_buffer_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

स्थिर mfxIMPL choose_implementation(स्थिरांक अक्षर *device, गणना AVHWDeviceType child_device_type)
{
    स्थिर स्थिरांक संरचना {
        स्थिरांक अक्षर *name;
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
    पूर्णांक i;

    जर (device) {
        साठी (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            जर (!म_भेद(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                थांबा;
            }
        जर (i == FF_ARRAY_ELEMS(impl_map))
            impl = म_से_दीर्घ(device, रिक्त, 0);
    }

    जर (impl != MFX_IMPL_SOFTWARE) {
        जर (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_VIA_D3D11;
        अन्यथा जर (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_VIA_D3D9;
    }

    परत impl;
}

स्थिर पूर्णांक qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        पूर्णांक flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfxVersion    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfxStatus     err;
    पूर्णांक ret;

    निवड (child_device_ctx->type) {
#जर CONFIG_VAAPI
    स्थिती AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        थांबा;
#endif
#जर CONFIG_D3D11VA
    स्थिती AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        थांबा;
#endif
#जर CONFIG_DXVA2
    स्थिती AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        थांबा;
#endif
    पूर्वनिर्धारित:
        ret = AVERROR(ENOSYS);
        जा fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    जर (ret)
        जा fail;

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    जर (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        जा fail;
    }

    परत 0;

fail:
    जर (hwctx->session)
        MFXClose(hwctx->session);

    जर (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = रिक्त;
    hwctx->loader = रिक्त;
    परत ret;
}

स्थिर पूर्णांक qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, पूर्णांक flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(आकार(*priv));
    जर (!priv)
        परत AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->मुक्त = qsv_device_free;

    impl = choose_implementation("hw_any", child_device_ctx->type);
    परत qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

स्थिर पूर्णांक qsv_device_create(AVHWDeviceContext *ctx, स्थिरांक अक्षर *device,
                             AVDictionary *opts, पूर्णांक flags)
{
    QSVDevicePriv *priv;
    गणना AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    पूर्णांक ret;

    priv = av_mallocz(आकार(*priv));
    जर (!priv)
        परत AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->मुक्त        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", रिक्त, 0);
    जर (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->मूल्य);
        जर (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->मूल्य);
            परत AVERROR(EINVAL);
        }
#जर QSV_ONEVPL
    } अन्यथा जर (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } अन्यथा जर (CONFIG_DXVA2) {
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
#अन्यथा
    } अन्यथा जर (CONFIG_DXVA2) {
        av_log(रिक्त, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } अन्यथा जर (CONFIG_D3D11VA) {
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#endif
    } अन्यथा जर (CONFIG_VAAPI) {
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        परत AVERROR(ENOSYS);
    }

#जर CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    जर (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->मूल्य);
        परत AVERROR(EINVAL);
    }
#endif

    child_device_opts = रिक्त;
    निवड (child_device_type) {
#जर CONFIG_VAAPI
    स्थिती AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_set(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_set(&child_device_opts, "driver",    "iHD",    0);
        }
        थांबा;
#endif
#जर CONFIG_D3D11VA
    स्थिती AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_set(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        थांबा;
#endif
#जर CONFIG_DXVA2
    स्थिती AV_HWDEVICE_TYPE_DXVA2:
#जर QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#endif
        थांबा;
#endif
    पूर्वनिर्धारित:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            परत AVERROR(ENOSYS);
        }
        थांबा;
    }

    e = av_dict_get(opts, "child_device", रिक्त, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->मूल्य : रिक्त, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    जर (ret < 0)
        परत ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->data;

    impl = choose_implementation(device, child_device_type);

    परत qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

स्थिरांक HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_size      = आकार(QSVDeviceContext),
    .frames_hwctx_size      = आकार(QSVFramesContext),

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

    .pix_fmts = (स्थिरांक गणना AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
