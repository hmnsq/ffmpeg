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

#सचे HAVE_PTHREADS
#अन्तर्भाव <pthread.h>
#endif

#define COBJMACROS
#सचे CONFIG_VAAPI
#अन्तर्भाव "hwcontext_vaapi.h"
#endif
#सचे CONFIG_D3D11VA
#अन्तर्भाव "hwcontext_d3d11va.h"
#endif
#सचे CONFIG_DXVA2
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

#सचे QSV_ONEVPL
#अन्तर्भाव <mfxdispatcher.h>
#अञ्ञथा
#define MFXUnload(a) करोहि { } याव(0)
#endif

प्रकारनिर्देश संरचना QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

प्रकारनिर्देश संरचना QSVDeviceContext {
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

प्रकारनिर्देश संरचना QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#सचे HAVE_PTHREADS
    pthread_mutex_t session_lock;
#endif

    AVBufferRef *child_frames_ref;
    mfxFrameSurface1 *surfaces_internal;
    mfxHDLPair *handle_pairs_internal;
    पूर्णाङ्क             nb_surfaces_used;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#सचे QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfxExtBuffer *ext_buffers[1];
#endif
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

प्रकारनिर्देश संरचना QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

स्थिर ध्रुव संरचना {
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
#सचे CONFIG_VAAPI
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
#सचे QSV_VERSION_ATLEAST(1, 31)
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

बाह्य पूर्णाङ्क ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          गणना AVHWDeviceType base_dev_type,
                                          शून्य **base_handle);

स्थिर पूर्णाङ्क qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
पूर्णाङ्क ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                   गणना AVHWDeviceType base_dev_type,
                                   शून्य **base_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->Data.MemId;
    विकल्प (base_dev_type) {
#सचे CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        base_handle[0] = handle_pair->first;
        पटिनिवत्त 0;
#endif
#सचे CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        base_handle[0] = handle_pair->first;
        base_handle[1] = handle_pair->second;
        पटिनिवत्त 0;
#endif
#सचे CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        base_handle[0] = handle_pair->first;
        पटिनिवत्त 0;
#endif
    }
    पटिनिवत्त AVERROR(EINVAL);
}

स्थिर uint32_t qsv_fourcc_from_pix_fmt(गणना AVPixelFormat pix_fmt)
{
    पूर्णाङ्क i;
    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        सचे (supported_pixel_formats[i].pix_fmt == pix_fmt)
            पटिनिवत्त supported_pixel_formats[i].fourcc;
    }
    पटिनिवत्त 0;
}

स्थिर uint16_t qsv_shift_from_pix_fmt(गणना AVPixelFormat pix_fmt)
{
    अत्थाय (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        सचे (supported_pixel_formats[i].pix_fmt == pix_fmt)
            पटिनिवत्त supported_pixel_formats[i].mfx_shift;
    }

    पटिनिवत्त 0;
}

#सचे CONFIG_D3D11VA
स्थिर uint32_t qsv_get_d3d11va_bind_flags(पूर्णाङ्क mem_type)
{
    uint32_t bind_flags = 0;

    सचे ((mem_type & MFX_MEMTYPE_VIDEO_MEMORY_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_INTERNAL_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    अञ्ञथा
        bind_flags = D3D11_BIND_DECODER;

    सचे ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    पटिनिवत्त bind_flags;
}
#endif

स्थिर पूर्णाङ्क qsv_fill_border(AVFrame *dst, ध्रुव AVFrame *src)
{
    ध्रुव AVPixFmtDescriptor *desc;
    पूर्णाङ्क i, planes_nb = 0;
    सचे (dst->format != src->format)
        पटिनिवत्त AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    अत्थाय (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    अत्थाय (i = 0; i < planes_nb; i++) {
        पूर्णाङ्क sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->width,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->width,
                                                 i);
        ध्रुव AVComponentDescriptor comp = desc->comp[i];
        सचे (swidth < 0 || dwidth < 0) {
            av_log(रिक्त, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            पटिनिवत्त AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        सचे (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        अत्थाय (y = 0; y < sheight; y++) {
            शून्य *पङ्क्तिः_ptr = dst->data[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(पङ्क्तिः_ptr,
                           comp.depth > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        अत्थाय (y = sheight; y < dheight; y++) {
            memcpy(dst->data[i]+y*dst->linesize[i],
                   dst->data[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    पूर्णाङ्क   hw_handle_supported = 0;
    mfxHandleType handle_type;
    गणना AVHWDeviceType device_type;
    गणना AVPixelFormat  pix_fmt;
    mfxStatus err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    सचे (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    सचे (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        पटिनिवत्त AVERROR_UNKNOWN;
    }

    सचे (MFX_IMPL_VIA_VAAPI == MFX_IMPL_VIA_MASK(s->impl)) {
#सचे CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#endif
    } अञ्ञथा सचे (MFX_IMPL_VIA_D3D11 == MFX_IMPL_VIA_MASK(s->impl)) {
#सचे CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#endif
    } अञ्ञथा सचे (MFX_IMPL_VIA_D3D9 == MFX_IMPL_VIA_MASK(s->impl)) {
#सचे CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#endif
    }

    सचे (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        सचे (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->child_device_type = device_type;
            s->child_pix_fmt     = pix_fmt;
        }
    }
    सचे (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    पटिनिवत्त 0;
}

स्थिर शून्य qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    सचे (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = रिक्त;
    s->session_download_init = 0;

    सचे (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = रिक्त;
    s->session_upload_init = 0;

#सचे HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_lock);
#endif

    av_freep(&s->mem_ids);
#सचे QSV_HAVE_OPAQUE
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

    सचे (!s->child_frames_ref)
        पटिनिवत्त;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    सचे (!child_frames_ctx->device_ctx)
        पटिनिवत्त;

#सचे CONFIG_VAAPI
    सचे (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#endif

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

स्थिर AVBufferRef *qsv_fixed_pool_alloc(शून्य *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    सचे (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        पटिनिवत्त av_buffer_create((uint8_t*)(s->surfaces_internal + s->nb_surfaces_used - 1),
                                परिमाण(*hwctx->surfaces), qsv_pool_release_dummy, रिक्त, 0);
    }

    पटिनिवत्त रिक्त;
}

स्थिर AVBufferRef *qsv_dynamic_pool_alloc(शून्य *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx;
    QSVSurface *qsv_surface = रिक्त;
    mfxHDLPair *handle_pairs_internal = रिक्त;
    पूर्णाङ्क ret;

    सचे (!s->child_frames_ref)
        गच्छ fail;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    सचे (!child_frames_ctx->device_ctx)
        गच्छ fail;

#सचे CONFIG_DXVA2
    सचे (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        गच्छ fail;
    }
#endif

    qsv_surface = av_calloc(1, परिमाण(*qsv_surface));
    सचे (!qsv_surface)
        गच्छ fail;

    qsv_surface->child_frame = av_frame_alloc();
    सचे (!qsv_surface->child_frame)
        गच्छ fail;

    ret = av_hwframe_get_buffer(s->child_frames_ref, qsv_surface->child_frame, 0);
    सचे (ret < 0)
        गच्छ fail;

    handle_pairs_internal = av_calloc(1, परिमाण(*handle_pairs_internal));
    सचे (!handle_pairs_internal)
        गच्छ fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    सचे (ret < 0)
        गच्छ fail;

#सचे CONFIG_VAAPI
    सचे (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, परिमाण(*surface_id_internal));
        सचे (!surface_id_internal)
            गच्छ fail;

        *surface_id_internal = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
    }
#endif

#सचे CONFIG_D3D11VA
    सचे (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        handle_pairs_internal->first = (mfxMemId)qsv_surface->child_frame->data[0];

        सचे (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        अञ्ञथा
            handle_pairs_internal->second = (mfxMemId)qsv_surface->child_frame->data[1];

    }
#endif

    qsv_surface->mfx_surface.Data.MemId = (mfxMemId)handle_pairs_internal;
    पटिनिवत्त av_buffer_create((uint8_t *)qsv_surface, परिमाण(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    सचे (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_pairs_internal);

    पटिनिवत्त रिक्त;
}

स्थिर AVBufferRef *qsv_pool_alloc(शून्य *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    सचे (hwctx->nb_surfaces == 0) {
        पटिनिवत्त qsv_dynamic_pool_alloc(opaque, size);
    } अञ्ञथा {
        पटिनिवत्त qsv_fixed_pool_alloc(opaque, size);
    }
}

स्थिर पूर्णाङ्क qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = रिक्त;
    AVBufferRef *child_frames_ref = रिक्त;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    पूर्णाङ्क i, ret = 0;

    सचे (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        पटिनिवत्त AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    सचे (!child_device_ref)
        पटिनिवत्त AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->data;

#सचे CONFIG_VAAPI
    सचे (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#endif
#सचे CONFIG_D3D11VA
    सचे (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        ID3D11Device_AddRef((ID3D11Device*)device_priv->handle);
        child_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#endif
#सचे CONFIG_DXVA2
    सचे (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#endif

    ret = av_hwdevice_ctx_init(child_device_ref);
    सचे (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        गच्छ fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    सचे (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->data;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_size = ctx->initial_pool_size;
    child_frames_ctx->width             = FFALIGN(ctx->width, 16);
    child_frames_ctx->height            = FFALIGN(ctx->height, 16);

#सचे CONFIG_D3D11VA
    सचे (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        सचे (hwctx->frame_type == 0)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        सचे (hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
            child_frames_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        child_frames_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->frame_type);
    }
#endif
#सचे CONFIG_DXVA2
    सचे (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        सचे (hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET)
            child_frames_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        अञ्ञथा
            child_frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#endif

    ret = av_hwframe_ctx_init(child_frames_ref);
    सचे (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        गच्छ fail;
    }

#सचे CONFIG_VAAPI
    सचे (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        अत्थाय (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = child_frames_hwctx->surface_ids + i;
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif
#सचे CONFIG_D3D11VA
    सचे (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        अत्थाय (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->texture_infos[i].texture;
            सचे(child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            } अञ्ञथा {
                s->handle_pairs_internal[i].second = (mfxMemId)child_frames_hwctx->texture_infos[i].index;
            }
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        सचे (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } अञ्ञथा {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
#endif
#सचे CONFIG_DXVA2
    सचे (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        अत्थाय (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->surfaces[i];
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        सचे (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        अञ्ञथा
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = रिक्त;

fail:
    av_buffer_unref(&child_device_ref);
    av_buffer_unref(&child_frames_ref);
    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    ध्रुव AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    सचे (!desc)
        पटिनिवत्त AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    सचे (!fourcc)
        पटिनिवत्त AVERROR(EINVAL);

    surf->Info.BitDepthLuma   = desc->comp[0].depth;
    surf->Info.BitDepthChroma = desc->comp[0].depth;
    surf->Info.Shift          = qsv_shift_from_pix_fmt(ctx->sw_format);

    सचे (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    अञ्ञथा सचे (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    अञ्ञथा
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.Width          = FFALIGN(ctx->width, 16);
    surf->Info.CropW          = ctx->width;
    surf->Info.Height         = FFALIGN(ctx->height, 16);
    surf->Info.CropH          = ctx->height;
    surf->Info.FrameRateExtN  = 25;
    surf->Info.FrameRateExtD  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    पूर्णाङ्क i, ret = 0;

    सचे (ctx->initial_pool_size < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        पटिनिवत्त AVERROR(EINVAL);
    } अञ्ञथा सचे (ctx->initial_pool_size == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        सचे (ret < 0)
            पटिनिवत्त ret;

        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(परिमाण(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, रिक्त);
        सचे (!ffhwframesctx(ctx)->pool_internal)
            पटिनिवत्त AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, परिमाण(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        frames_hwctx->info = &s->frame_info;
        frames_hwctx->nb_surfaces = 0;

        पटिनिवत्त 0;
    }

    s->handle_pairs_internal = av_calloc(ctx->initial_pool_size,
                                         परिमाण(*s->handle_pairs_internal));
    सचे (!s->handle_pairs_internal)
        पटिनिवत्त AVERROR(ENOMEM);

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     परिमाण(*s->surfaces_internal));
    सचे (!s->surfaces_internal)
        पटिनिवत्त AVERROR(ENOMEM);

    अत्थाय (i = 0; i < ctx->initial_pool_size; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_internal[i]);
        सचे (ret < 0)
            पटिनिवत्त ret;
    }

#सचे QSV_HAVE_OPAQUE
    सचे (!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        सचे (ret < 0)
            पटिनिवत्त ret;
    }
#अञ्ञथा
    ret = qsv_init_child_ctx(ctx);
    सचे (ret < 0)
        पटिनिवत्त ret;
#endif

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(परिमाण(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, रिक्त);
    सचे (!ffhwframesctx(ctx)->pool_internal)
        पटिनिवत्त AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    पटिनिवत्त 0;
}

स्थिर mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    सचे (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        पटिनिवत्त MFX_ERR_UNSUPPORTED;
    सचे (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        पटिनिवत्त MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->अङ्कः_Frame_Actual = hwctx->nb_surfaces;

    पटिनिवत्त MFX_ERR_NONE;
}

स्थिर mfxStatus frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    पटिनिवत्त MFX_ERR_NONE;
}

स्थिर mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    पटिनिवत्त MFX_ERR_UNSUPPORTED;
}

स्थिर mfxStatus frame_unlock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    पटिनिवत्त MFX_ERR_UNSUPPORTED;
}

स्थिर mfxStatus frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    सचे (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    पटिनिवत्त MFX_ERR_NONE;
}

#सचे QSV_ONEVPL

स्थिर पूर्णाङ्क qsv_d3d11_update_config(शून्य *ctx, mfxHDL handle, mfxConfig cfg)
{
    पूर्णाङ्क ret = AVERROR_UNKNOWN;
#सचे CONFIG_D3D11VA
    mfxStatus sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = रिक्त;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_मानम् = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (शून्य**)&pDXGIDevice);
    सचे (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        सचे (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            पटिनिवत्त ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        सचे (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            गच्छ fail;
        }
    } अञ्ञथा {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        पटिनिवत्त ret;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_U16;
    impl_मानम्.Data.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_मानम्);
    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        गच्छ fail;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_PTR;
    impl_मानम्.Data.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_मानम्);
    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        गच्छ fail;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_U32;
    impl_मानम्.Data.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_मानम्);
    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        गच्छ fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#endif
    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क qsv_d3d9_update_config(शून्य *ctx, mfxHDL handle, mfxConfig cfg)
{
    पूर्णाङ्क ret = AVERROR_UNKNOWN;
#सचे CONFIG_DXVA2
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
    mfxVariant impl_मानम् = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    सचे (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        गच्छ fail;
    }

    hr = IDirect3DDeviceManager9_LockDevice(devmgr, device_handle, &device, TRUE);
    सचे (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        गच्छ fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (शून्य **)&device_ex);
    IDirect3DDevice9_Release(device);
    सचे (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        गच्छ unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    सचे (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        गच्छ unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    सचे (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        गच्छ unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (शून्य **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    सचे (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        गच्छ unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    सचे (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        गच्छ release;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_PTR;
    impl_मानम्.Data.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_मानम्);
    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        गच्छ release;
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
    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क qsv_va_update_config(शून्य *ctx, mfxHDL handle, mfxConfig cfg)
{
#सचे CONFIG_VAAPI
#सचे VA_CHECK_VERSION(1, 15, 0)
    mfxStatus sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_मानम् = {0};

    vas = vaGetDisplayAttributes(dpy, &attr, 1);
    सचे (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_मानम्.Type = MFX_VARIANT_TYPE_U16;
        impl_मानम्.Data.U16 = (attr.मानम् & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ध्रुव mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_मानम्);
        सचे (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            गच्छ fail;
        }
    } अञ्ञथा {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        गच्छ fail;
    }

    पटिनिवत्त 0;

fail:
#अञ्ञथा
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#endif
#endif
    पटिनिवत्त AVERROR_UNKNOWN;
}

स्थिर पूर्णाङ्क qsv_new_mfx_loader(शून्य *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfxVersion *pver,
                              शून्य **ploader)
{
    mfxStatus sts;
    mfxLoader loader = रिक्त;
    mfxConfig cfg;
    mfxVariant impl_मानम् = {0};

    *ploader = रिक्त;
    loader = MFXLoad();
    सचे (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        गच्छ fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    सचे (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        गच्छ fail;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_U32;
    impl_मानम्.Data.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxImplDescription.Impl", impl_मानम्);
    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        गच्छ fail;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_U32;
    impl_मानम्.Data.U32 = pver->Version;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_मानम्);
    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        गच्छ fail;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_U32;
    impl_मानम्.Data.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxImplDescription.VendorID", impl_मानम्);
    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        गच्छ fail;
    }

    सचे (MFX_HANDLE_VA_DISPLAY == handle_type) {
        सचे (handle && qsv_va_update_config(ctx, handle, cfg))
            गच्छ fail;

        impl_मानम्.Data.U32 = MFX_ACCEL_MODE_VIA_VAAPI;
    } अञ्ञथा सचे (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        सचे (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            गच्छ fail;

        impl_मानम्.Data.U32 = MFX_ACCEL_MODE_VIA_D3D9;
    } अञ्ञथा {
        सचे (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            गच्छ fail;

        impl_मानम्.Data.U32 = MFX_ACCEL_MODE_VIA_D3D11;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxImplDescription.AccelerationMode", impl_मानम्);
    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        गच्छ fail;
    }

    *ploader = loader;

    पटिनिवत्त 0;

fail:
    सचे (loader)
        MFXUnload(loader);

    पटिनिवत्त AVERROR_UNKNOWN;
}

स्थिर पूर्णाङ्क qsv_create_mfx_session_from_loader(शून्य *ctx, mfxLoader loader, mfxSession *psession)
{
    mfxStatus sts;
    mfxSession session = रिक्त;
    uint32_t impl_idx = 0;
    mfxVersion ver;

    याव (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        सचे (sts == MFX_ERR_NOT_FOUND)
            भङ्ग;
        अञ्ञथा सचे (sts != MFX_ERR_NONE) {
            impl_idx++;
            अनुवर्त;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        सचे (sts == MFX_ERR_NONE)
            भङ्ग;

        impl_idx++;
    }

    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        गच्छ fail;
    }

    sts = MFXQueryVersion(session, &ver);
    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        गच्छ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    पटिनिवत्त 0;

fail:
    सचे (session)
        MFXClose(session);

    पटिनिवत्त AVERROR_UNKNOWN;
}

स्थिर पूर्णाङ्क qsv_create_mfx_session(शून्य *ctx,
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

    सचे (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        पटिनिवत्त AVERROR(EXDEV);
    }

    *psession = रिक्त;

    सचे (!*ploader) {
        सचे (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (शून्य **)&loader))
            गच्छ fail;

        av_assert0(loader);
    } अञ्ञथा
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    सचे (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        गच्छ fail;

    सचे (!*ploader)
        *ploader = loader;

    पटिनिवत्त 0;

fail:
    सचे (!*ploader && loader)
        MFXUnload(loader);

    पटिनिवत्त AVERROR_UNKNOWN;
}

#अञ्ञथा

स्थिर पूर्णाङ्क qsv_create_mfx_session(शून्य *ctx,
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
    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        गच्छ fail;
    }

    sts = MFXQueryVersion(session, &ver);
    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        गच्छ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    सचे (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        गच्छ fail;
    }

    *psession = session;

    पटिनिवत्त 0;

fail:
    सचे (session)
        MFXClose(session);

    पटिनिवत्त AVERROR_UNKNOWN;
}

#endif

स्थिर पूर्णाङ्क qsv_init_internal_session(AVHWFramesContext *ctx,
                                     mfxSession *session, पूर्णाङ्क upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    पूर्णाङ्क opaque = 0;

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
    पूर्णाङ्क                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    शून्य             **loader = &hwctx->loader;
    mfxSession parent_session = hwctx->session;
    mfxIMPL impl;
    mfxVersion ver;

    err = MFXQueryIMPL(parent_session, &impl);
    सचे (err == MFX_ERR_NONE)
        err = MFXQueryVersion(parent_session, &ver);
    सचे (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        पटिनिवत्त AVERROR_UNKNOWN;
    }

#सचे QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    सचे (ret)
        गच्छ fail;

    सचे (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        सचे (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            गच्छ fail;
        }
    }

    सचे (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        सचे (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            गच्छ fail;
        }
    }

    सचे (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        सचे (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            गच्छ fail;
        }
    }

    memset(&par, 0, परिमाण(par));

    सचे (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_OUT_VIDEO_MEMORY :
                                 MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
#सचे QSV_HAVE_OPAQUE
    अञ्ञथा {
        par.ExtParam    = s->ext_buffers;
        par.अङ्कः_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
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
    सचे (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        गच्छ fail;
    }

    पटिनिवत्त 0;

fail:
    सचे (*session)
        MFXClose(*session);

    *session = रिक्त;

    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    पूर्णाङ्क opaque = 0;

    uint32_t fourcc;
    पूर्णाङ्क i, ret;

#सचे QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    सचे (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        पटिनिवत्त AVERROR(ENOSYS);
    }

    सचे (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        सचे (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            पटिनिवत्त ret;
        }
    }

    सचे (!opaque) {
        s->mem_ids = av_calloc(frames_hwctx->nb_surfaces, परिमाण(*s->mem_ids));
        सचे (!s->mem_ids)
            पटिनिवत्त AVERROR(ENOMEM);

        अत्थाय (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].Data.MemId;
    }
#सचे QSV_HAVE_OPAQUE
    अञ्ञथा {
        s->surface_ptrs = av_calloc(frames_hwctx->nb_surfaces,
                                    परिमाण(*s->surface_ptrs));
        सचे (!s->surface_ptrs)
            पटिनिवत्त AVERROR(ENOMEM);

        अत्थाय (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.अङ्कः_Surface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = परिमाण(s->opaque_alloc);

        s->ext_buffers[0] = (mfxExtBuffer*)&s->opaque_alloc;
    }
#endif

    s->session_download = रिक्त;
    s->session_upload   = रिक्त;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#सचे HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, रिक्त);
#endif

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क qsv_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    सचे (!frame->buf[0])
        पटिनिवत्त AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_QSV;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    गणना AVHWFrameTransferDirection dir,
                                    गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts;

    fmts = av_malloc_array(2, परिमाण(*fmts));
    सचे (!fmts)
        पटिनिवत्त AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, पूर्णाङ्क flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    पूर्णाङ्क i;

    विकल्प (dst_ctx->device_ctx->type) {
#सचे CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               परिमाण(*dst_hwctx->surface_ids));
            सचे (!dst_hwctx->surface_ids)
                पटिनिवत्त AVERROR(ENOMEM);
            अत्थाय (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        भङ्ग;
#endif
#सचे CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_size = src_ctx->initial_pool_size;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 परिमाण(*dst_hwctx->texture_infos));
            सचे (!dst_hwctx->texture_infos)
                पटिनिवत्त AVERROR(ENOMEM);
            सचे (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            अत्थाय (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].index = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            सचे (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } अञ्ञथा
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        भङ्ग;
#endif
#सचे CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            परिमाण(*dst_hwctx->surfaces));
            सचे (!dst_hwctx->surfaces)
                पटिनिवत्त AVERROR(ENOMEM);
            अत्थाय (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            सचे (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            अञ्ञथा
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        भङ्ग;
#endif
    स्वभाव:
        पटिनिवत्त AVERROR(ENOSYS);
    }

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->data[3];
    AVHWFramesContext *child_frames_ctx;
    ध्रुव AVPixFmtDescriptor *desc;
    uint8_t *child_data;
    AVFrame *dummy;
    पूर्णाङ्क ret = 0;

    सचे (!s->child_frames_ref)
        पटिनिवत्त AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;

    विकल्प (child_frames_ctx->device_ctx->type) {
#सचे CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_data = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        भङ्ग;
    }
#endif
#सचे CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        भङ्ग;
    }
#endif
#सचे CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        भङ्ग;
    }
#endif
    स्वभाव:
        पटिनिवत्त AVERROR(ENOSYS);
    }

    सचे (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, रिक्त, रिक्त);
        सचे (ret < 0)
            पटिनिवत्त ret;

        dst->width   = src->width;
        dst->height  = src->height;

       सचे (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
            dst->data[0] = pair->first;
            dst->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } अञ्ञथा {
            dst->data[3] = child_data;
        }

        पटिनिवत्त 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    सचे (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        पटिनिवत्त AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    सचे (!dummy)
        पटिनिवत्त AVERROR(ENOMEM);

    dummy->buf[0]        = av_buffer_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_buffer_ref(s->child_frames_ref);
    सचे (!dummy->buf[0] || !dummy->hw_frames_ctx)
        गच्छ fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;

    सचे (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        dummy->data[0] = pair->first;
        dummy->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } अञ्ञथा {
        dummy->data[3] = child_data;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क qsv_transfer_data_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   ध्रुव AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    पूर्णाङ्क download = !!src->hw_frames_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->data[3] : dst->data[3]);

    AVFrame *dummy;
    पूर्णाङ्क ret;

    dummy = av_frame_alloc();
    सचे (!dummy)
        पटिनिवत्त AVERROR(ENOMEM);

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

    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क map_frame_to_surface(ध्रुव AVFrame *frame, mfxFrameSurface1 *surface)
{
    विकल्प (frame->format) {
    पक्ष AV_PIX_FMT_NV12:
    पक्ष AV_PIX_FMT_P010:
    पक्ष AV_PIX_FMT_P012:
        surface->Data.Y  = frame->data[0];
        surface->Data.UV = frame->data[1];
        भङ्ग;

    पक्ष AV_PIX_FMT_YUV420P:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[1];
        surface->Data.V = frame->data[2];
        भङ्ग;

    पक्ष AV_PIX_FMT_BGRA:
        surface->Data.B = frame->data[0];
        surface->Data.G = frame->data[0] + 1;
        surface->Data.R = frame->data[0] + 2;
        surface->Data.A = frame->data[0] + 3;
        भङ्ग;
    पक्ष AV_PIX_FMT_YUYV422:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.V = frame->data[0] + 3;
        भङ्ग;

    पक्ष AV_PIX_FMT_Y210:
    पक्ष AV_PIX_FMT_Y212:
        surface->Data.Y16 = (mfxU16 *)frame->data[0];
        surface->Data.U16 = (mfxU16 *)frame->data[0] + 1;
        surface->Data.V16 = (mfxU16 *)frame->data[0] + 3;
        भङ्ग;
    पक्ष AV_PIX_FMT_VUYX:
        surface->Data.V = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.Y = frame->data[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 3;
        भङ्ग;
    पक्ष AV_PIX_FMT_XV30:
        surface->Data.U = frame->data[0];
        भङ्ग;
    पक्ष AV_PIX_FMT_XV36:
        surface->Data.U = frame->data[0];
        surface->Data.Y = frame->data[0] + 2;
        surface->Data.V = frame->data[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 6;
        भङ्ग;
#सचे CONFIG_VAAPI
    पक्ष AV_PIX_FMT_UYVY422:
        surface->Data.Y = frame->data[0] + 1;
        surface->Data.U = frame->data[0];
        surface->Data.V = frame->data[0] + 2;
        भङ्ग;
#endif
    स्वभाव:
        पटिनिवत्त MFX_ERR_UNSUPPORTED;
    }
    surface->Data.Pitch     = frame->linesize[0];
    surface->Data.TimeStamp = frame->pts;

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क qsv_internal_session_check_init(AVHWFramesContext *ctx, पूर्णाङ्क upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    पूर्णाङ्क ret = 0;

    सचे (atomic_load(inited))
        पटिनिवत्त 0;

#सचे HAVE_PTHREADS
    pthread_mutex_lock(&s->session_lock);
#endif

    सचे (!atomic_load(inited)) {
        ret = qsv_init_internal_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#सचे HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_lock);
#endif

    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क qsv_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ध्रुव AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->data[3];

    mfxSyncPoint sync = रिक्त;
    mfxStatus err;
    पूर्णाङ्क ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    पूर्णाङ्क realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 0);
    सचे (ret < 0)
        पटिनिवत्त ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    सचे (dst->height & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        सचे (tmp_frame->format != dst->format ||
            tmp_frame->width  != FFALIGN(dst->linesize[0], 16) ||
            tmp_frame->height != FFALIGN(dst->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = dst->format;
            tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
            tmp_frame->height = FFALIGN(dst->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            सचे (ret < 0)
                पटिनिवत्त ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    सचे (!s->session_download) {
        सचे (s->child_frames_ref)
            पटिनिवत्त qsv_transfer_data_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        पटिनिवत्त AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst_frame, &out);

    करोहि {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, रिक्त, &sync);
        सचे (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } याव (err == MFX_WRN_DEVICE_BUSY);

    सचे (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        पटिनिवत्त AVERROR_UNKNOWN;
    }

    करोहि {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } याव (err == MFX_WRN_IN_EXECUTION);
    सचे (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        पटिनिवत्त AVERROR_UNKNOWN;
    }

    सचे (realigned) {
        tmp_frame->width  = dst->width;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        सचे (ret < 0)
            पटिनिवत्त ret;
    }

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क qsv_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                ध्रुव AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   in = {{ 0 }};
    mfxFrameSurface1 *out = (mfxFrameSurface1*)dst->data[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = रिक्त;
    mfxStatus err;
    पूर्णाङ्क ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    ध्रुव AVFrame *src_frame;
    पूर्णाङ्क realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 1);
    सचे (ret < 0)
        पटिनिवत्त ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    सचे (src->height & 15 || src->linesize[0] & 15) {
        realigned = 1;
        सचे (tmp_frame->format != src->format ||
            tmp_frame->width  != FFALIGN(src->width, 16) ||
            tmp_frame->height != FFALIGN(src->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = src->format;
            tmp_frame->width  = FFALIGN(src->width, 16);
            tmp_frame->height = FFALIGN(src->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            सचे (ret < 0)
                पटिनिवत्त ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        सचे (ret < 0) {
            av_frame_unref(tmp_frame);
            पटिनिवत्त ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        सचे (ret < 0) {
            av_frame_unref(tmp_frame);
            पटिनिवत्त ret;
        }

        tmp_info = out->Info;
        out->Info.CropW = FFMIN(out->Info.Width,  tmp_frame->width);
        out->Info.CropH = FFMIN(out->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    सचे (!s->session_upload) {
        सचे (s->child_frames_ref)
            पटिनिवत्त qsv_transfer_data_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        पटिनिवत्त AVERROR(ENOSYS);
    }

    in.Info = out->Info;
    map_frame_to_surface(src_frame, &in);

    करोहि {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_upload, &in, out, रिक्त, &sync);
        सचे (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } याव (err == MFX_WRN_DEVICE_BUSY);

    सचे (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        पटिनिवत्त AVERROR_UNKNOWN;
    }

    करोहि {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } याव (err == MFX_WRN_IN_EXECUTION);
    सचे (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        पटिनिवत्त AVERROR_UNKNOWN;
    }

    सचे (realigned) {
        out->Info.CropW = tmp_info.CropW;
        out->Info.CropH = tmp_info.CropH;
    }

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क qsv_dynamic_frames_derive_to(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, पूर्णाङ्क flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    विकल्प (src_ctx->device_ctx->type) {
#सचे CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        भङ्ग;
#endif

#सचे CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        सचे (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } अञ्ञथा {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
    भङ्ग;
#endif

    स्वभाव:
        पटिनिवत्त AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, परिमाण(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क qsv_fixed_frames_derive_to(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, पूर्णाङ्क flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    पूर्णाङ्क i;

    विकल्प (src_ctx->device_ctx->type) {
#सचे CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 परिमाण(*s->handle_pairs_internal));
            सचे (!s->handle_pairs_internal)
                पटिनिवत्त AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             परिमाण(*s->surfaces_internal));
            सचे (!s->surfaces_internal)
                पटिनिवत्त AVERROR(ENOMEM);
            अत्थाय (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = src_hwctx->surface_ids + i;
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        भङ्ग;
#endif
#सचे CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 परिमाण(*s->handle_pairs_internal));
            सचे (!s->handle_pairs_internal)
                पटिनिवत्त AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_ctx->initial_pool_size,
                                             परिमाण(*s->surfaces_internal));
            सचे (!s->surfaces_internal)
                पटिनिवत्त AVERROR(ENOMEM);
            अत्थाय (i = 0; i < src_ctx->initial_pool_size; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                सचे (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                } अञ्ञथा {
                    s->handle_pairs_internal[i].second = (mfxMemId)src_hwctx->texture_infos[i].index;
                }
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_size;
            सचे (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            } अञ्ञथा {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
            }
        }
        भङ्ग;
#endif
#सचे CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 परिमाण(*s->handle_pairs_internal));
            सचे (!s->handle_pairs_internal)
                पटिनिवत्त AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             परिमाण(*s->surfaces_internal));
            सचे (!s->surfaces_internal)
                पटिनिवत्त AVERROR(ENOMEM);
            अत्थाय (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            सचे (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            अञ्ञथा
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        भङ्ग;
#endif
    स्वभाव:
        पटिनिवत्त AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, पूर्णाङ्क flags)
{
    सचे (src_ctx->initial_pool_size < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        पटिनिवत्त AVERROR(EINVAL);
    } अञ्ञथा सचे (src_ctx->initial_pool_size == 0) {
        पटिनिवत्त qsv_dynamic_frames_derive_to(dst_ctx, src_ctx, flags);
    } अञ्ञथा {
        पटिनिवत्त qsv_fixed_frames_derive_to(dst_ctx, src_ctx, flags);
    }
}

स्थिर पूर्णाङ्क qsv_fixed_pool_map_to(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    पूर्णाङ्क i, err, index = -1;

    अत्थाय (i = 0; i < hwctx->nb_surfaces && index < 0; i++) {
        विकल्प(src->format) {
#सचे CONFIG_VAAPI
        पक्ष AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            सचे (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->data[3])
                index = i;
            भङ्ग;
        }
#endif
#सचे CONFIG_D3D11VA
        पक्ष AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            सचे (pair->first == src->data[0]
                && (pair->second == src->data[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->data[1] == (uint8_t *)0)))
                index = i;
            भङ्ग;
        }
#endif
#सचे CONFIG_DXVA2
        पक्ष AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            सचे (pair->first == src->data[3])
                index = i;
            भङ्ग;
        }
#endif
        }
    }
    सचे (index < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        पटिनिवत्त AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, रिक्त, रिक्त);
    सचे (err)
        पटिनिवत्त err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)&hwctx->surfaces[index];

    पटिनिवत्त 0;
}

स्थिर शून्य qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_internal = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_pairs_internal = (mfxHDLPair *)surfaces_internal->Data.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_frames->data;

    विकल्प (src_ctx->format) {
#सचे CONFIG_VAAPI
    पक्ष AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_pairs_internal->first);

        भङ्ग;
    }
#endif

#सचे CONFIG_D3D11VA
    पक्ष AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        भङ्ग;
    }
#endif
    स्वभाव:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        भङ्ग;
    }

    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
}

स्थिर पूर्णाङ्क qsv_dynamic_pool_map_to(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    mfxFrameSurface1 *surfaces_internal = रिक्त;
    mfxHDLPair *handle_pairs_internal = रिक्त;
    पूर्णाङ्क ret = 0;

    surfaces_internal = av_calloc(1, परिमाण(*surfaces_internal));
    सचे (!surfaces_internal) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    handle_pairs_internal = av_calloc(1, परिमाण(*handle_pairs_internal));
    सचे (!handle_pairs_internal) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_internal);
    सचे (ret < 0)
        गच्छ fail;

    विकल्प (src->format) {
#सचे CONFIG_VAAPI
    पक्ष AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, परिमाण(*surface_id_internal));
        सचे (!surface_id_internal) {
            ret =AVERROR(ENOMEM);
            गच्छ fail;
        }

        *surface_id_internal = (VASurfaceID)(uintptr_t)src->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;

        भङ्ग;
    }
#endif

#सचे CONFIG_D3D11VA
    पक्ष AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_pairs_internal->first = (mfxMemId)src->data[0];

        सचे (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        } अञ्ञथा {
            handle_pairs_internal->second = (mfxMemId)src->data[1];
        }

        भङ्ग;
    }
#endif
    स्वभाव:
        ret = AVERROR(ENOSYS);
        गच्छ fail;
    }

    surfaces_internal->Data.MemId = (mfxMemId)handle_pairs_internal;

    ret = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_internal);
    सचे (ret)
        गच्छ fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)surfaces_internal;

    पटिनिवत्त 0;

fail:
    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    सचे (hwctx->nb_surfaces)
        पटिनिवत्त qsv_fixed_pool_map_to(dst_ctx, dst, src, flags);
    अञ्ञथा
        पटिनिवत्त qsv_dynamic_pool_map_to(dst_ctx, dst, src, flags);
}

स्थिर पूर्णाङ्क qsv_frames_get_constraints(AVHWDeviceContext *ctx,
                                      ध्रुव शून्य *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    पूर्णाङ्क i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    परिमाण(*constraints->valid_sw_formats));
    सचे (!constraints->valid_sw_formats)
        पटिनिवत्त AVERROR(ENOMEM);

    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
    सचे (!constraints->valid_hw_formats)
        पटिनिवत्त AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    पटिनिवत्त 0;
}

स्थिर शून्य qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    सचे (hwctx->session)
        MFXClose(hwctx->session);

    सचे (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_buffer_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

स्थिर mfxIMPL choose_implementation(ध्रुव वर्ण *device, गणना AVHWDeviceType child_device_type)
{
    स्थिर ध्रुव संरचना {
        ध्रुव वर्ण *name;
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
    पूर्णाङ्क i;

    सचे (device) {
        अत्थाय (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            सचे (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                भङ्ग;
            }
        सचे (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, रिक्त, 0);
    }

    सचे (impl != MFX_IMPL_SOFTWARE) {
        सचे (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_VIA_D3D11;
        अञ्ञथा सचे (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_VIA_D3D9;
    }

    पटिनिवत्त impl;
}

स्थिर पूर्णाङ्क qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        पूर्णाङ्क flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfxVersion    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfxStatus     err;
    पूर्णाङ्क ret;

    विकल्प (child_device_ctx->type) {
#सचे CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        भङ्ग;
#endif
#सचे CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        भङ्ग;
#endif
#सचे CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        भङ्ग;
#endif
    स्वभाव:
        ret = AVERROR(ENOSYS);
        गच्छ fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    सचे (ret)
        गच्छ fail;

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    सचे (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        गच्छ fail;
    }

    पटिनिवत्त 0;

fail:
    सचे (hwctx->session)
        MFXClose(hwctx->session);

    सचे (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = रिक्त;
    hwctx->loader = रिक्त;
    पटिनिवत्त ret;
}

स्थिर पूर्णाङ्क qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, पूर्णाङ्क flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(परिमाण(*priv));
    सचे (!priv)
        पटिनिवत्त AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->मुक्त = qsv_device_free;

    impl = choose_implementation("hw_any", child_device_ctx->type);
    पटिनिवत्त qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

स्थिर पूर्णाङ्क qsv_device_create(AVHWDeviceContext *ctx, ध्रुव वर्ण *device,
                             AVDictionary *opts, पूर्णाङ्क flags)
{
    QSVDevicePriv *priv;
    गणना AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    पूर्णाङ्क ret;

    priv = av_mallocz(परिमाण(*priv));
    सचे (!priv)
        पटिनिवत्त AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->मुक्त        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", रिक्त, 0);
    सचे (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->मानम्);
        सचे (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->मानम्);
            पटिनिवत्त AVERROR(EINVAL);
        }
#सचे QSV_ONEVPL
    } अञ्ञथा सचे (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } अञ्ञथा सचे (CONFIG_DXVA2) {
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
#अञ्ञथा
    } अञ्ञथा सचे (CONFIG_DXVA2) {
        av_log(रिक्त, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } अञ्ञथा सचे (CONFIG_D3D11VA) {
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#endif
    } अञ्ञथा सचे (CONFIG_VAAPI) {
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } अञ्ञथा {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        पटिनिवत्त AVERROR(ENOSYS);
    }

#सचे CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    सचे (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->मानम्);
        पटिनिवत्त AVERROR(EINVAL);
    }
#endif

    child_device_opts = रिक्त;
    विकल्प (child_device_type) {
#सचे CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_set(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_set(&child_device_opts, "driver",    "iHD",    0);
        }
        भङ्ग;
#endif
#सचे CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_set(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        भङ्ग;
#endif
#सचे CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
#सचे QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#endif
        भङ्ग;
#endif
    स्वभाव:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            पटिनिवत्त AVERROR(ENOSYS);
        }
        भङ्ग;
    }

    e = av_dict_get(opts, "child_device", रिक्त, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->मानम् : रिक्त, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    सचे (ret < 0)
        पटिनिवत्त ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->data;

    impl = choose_implementation(device, child_device_type);

    पटिनिवत्त qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

ध्रुव HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_size      = परिमाण(QSVDeviceContext),
    .frames_hwctx_size      = परिमाण(QSVFramesContext),

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

    .pix_fmts = (ध्रुव गणना AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
