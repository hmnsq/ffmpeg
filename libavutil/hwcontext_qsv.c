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

#அந்தர்பாவ <stdatomic.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ <mfxvideo.h>

#அந்தர்பாவ "config.h"

#எனில் HAVE_PTHREADS
#அந்தர்பாவ <pthread.h>
#endif

#define COBJMACROS
#எனில் CONFIG_VAAPI
#அந்தர்பாவ "hwcontext_vaapi.h"
#endif
#எனில் CONFIG_D3D11VA
#அந்தர்பாவ "hwcontext_d3d11va.h"
#endif
#எனில் CONFIG_DXVA2
#அந்தர்பாவ <initguid.h>
#அந்தர்பாவ "hwcontext_dxva2.h"
#endif

#அந்தர்பாவ "buffer.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "hwcontext.h"
#அந்தர்பாவ "hwcontext_internal.h"
#அந்தர்பாவ "hwcontext_qsv.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "pixfmt.h"
#அந்தர்பாவ "pixdesc.h"
#அந்தர்பாவ "time.h"
#அந்தர்பாவ "imgutils.h"
#அந்தர்பாவ "avassert.h"

#define QSV_VERSION_ATLEAST(MAJOR, MINOR)   \
    (MFX_VERSION_MAJOR > (MAJOR) ||         \
     MFX_VERSION_MAJOR == (MAJOR) && MFX_VERSION_MINOR >= (MINOR))

#define QSV_RUNTIME_VERSION_ATLEAST(MFX_VERSION, MAJOR, MINOR)          \
    ((MFX_VERSION.Major > (MAJOR)) ||                                   \
     (MFX_VERSION.Major == (MAJOR) && MFX_VERSION.Minor >= (MINOR)))

#define MFX_IMPL_VIA_MASK(impl) (0x0f00 & (impl))
#define QSV_ONEVPL       QSV_VERSION_ATLEAST(2, 0)
#define QSV_HAVE_OPAQUE  !QSV_ONEVPL

#எனில் QSV_ONEVPL
#அந்தர்பாவ <mfxdispatcher.h>
#இல்லையெனில்
#define MFXUnload(a) செய் { } போது(0)
#endif

வகைவரை கட்டமைப்பு QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

வகைவரை கட்டமைப்பு QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfxVersion          ver;
    mfxIMPL             impl;

    எண்ணிக்கை AVHWDeviceType child_device_type;
    எண்ணிக்கை AVPixelFormat  child_pix_fmt;
} QSVDeviceContext;

வகைவரை கட்டமைப்பு QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#எனில் HAVE_PTHREADS
    pthread_mutex_t session_lock;
#endif

    AVBufferRef *child_frames_ref;
    mfxFrameSurface1 *surfaces_internal;
    mfxHDLPair *handle_pairs_internal;
    முழு             nb_surfaces_used;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#எனில் QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfxExtBuffer *ext_buffers[1];
#endif
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

வகைவரை கட்டமைப்பு QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

நிலையான மாறிலி கட்டமைப்பு {
    எண்ணிக்கை AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_shift;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#எனில் CONFIG_VAAPI
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
#எனில் QSV_VERSION_ATLEAST(1, 31)
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

வெளி முழு ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          எண்ணிக்கை AVHWDeviceType base_dev_type,
                                          வெறுமை **base_handle);

நிலையான முழு qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
முழு ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                   எண்ணிக்கை AVHWDeviceType base_dev_type,
                                   வெறுமை **base_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->Data.MemId;
    தேர்வு (base_dev_type) {
#எனில் CONFIG_VAAPI
    நிலை AV_HWDEVICE_TYPE_VAAPI:
        base_handle[0] = handle_pair->first;
        திரும்பு 0;
#endif
#எனில் CONFIG_D3D11VA
    நிலை AV_HWDEVICE_TYPE_D3D11VA:
        base_handle[0] = handle_pair->first;
        base_handle[1] = handle_pair->second;
        திரும்பு 0;
#endif
#எனில் CONFIG_DXVA2
    நிலை AV_HWDEVICE_TYPE_DXVA2:
        base_handle[0] = handle_pair->first;
        திரும்பு 0;
#endif
    }
    திரும்பு AVERROR(EINVAL);
}

நிலையான uint32_t qsv_fourcc_from_pix_fmt(எண்ணிக்கை AVPixelFormat pix_fmt)
{
    முழு i;
    க்கு (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        எனில் (supported_pixel_formats[i].pix_fmt == pix_fmt)
            திரும்பு supported_pixel_formats[i].fourcc;
    }
    திரும்பு 0;
}

நிலையான uint16_t qsv_shift_from_pix_fmt(எண்ணிக்கை AVPixelFormat pix_fmt)
{
    க்கு (முழு i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        எனில் (supported_pixel_formats[i].pix_fmt == pix_fmt)
            திரும்பு supported_pixel_formats[i].mfx_shift;
    }

    திரும்பு 0;
}

#எனில் CONFIG_D3D11VA
நிலையான uint32_t qsv_get_d3d11va_bind_flags(முழு mem_type)
{
    uint32_t bind_flags = 0;

    எனில் ((mem_type & MFX_MEMTYPE_VIDEO_MEMORY_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_INTERNAL_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    இல்லையெனில்
        bind_flags = D3D11_BIND_DECODER;

    எனில் ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    திரும்பு bind_flags;
}
#endif

நிலையான முழு qsv_fill_border(AVFrame *dst, மாறிலி AVFrame *src)
{
    மாறிலி AVPixFmtDescriptor *desc;
    முழு i, planes_nb = 0;
    எனில் (dst->format != src->format)
        திரும்பு AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    க்கு (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    க்கு (i = 0; i < planes_nb; i++) {
        முழு sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->width,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->width,
                                                 i);
        மாறிலி AVComponentDescriptor comp = desc->comp[i];
        எனில் (swidth < 0 || dwidth < 0) {
            av_log(வெற்று, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            திரும்பு AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        எனில் (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        க்கு (y = 0; y < sheight; y++) {
            வெறுமை *வரி_ptr = dst->data[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(வரி_ptr,
                           comp.depth > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        க்கு (y = sheight; y < dheight; y++) {
            memcpy(dst->data[i]+y*dst->linesize[i],
                   dst->data[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    திரும்பு 0;
}

நிலையான முழு qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    முழு   hw_handle_supported = 0;
    mfxHandleType handle_type;
    எண்ணிக்கை AVHWDeviceType device_type;
    எண்ணிக்கை AVPixelFormat  pix_fmt;
    mfxStatus err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    எனில் (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    எனில் (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    எனில் (MFX_IMPL_VIA_VAAPI == MFX_IMPL_VIA_MASK(s->impl)) {
#எனில் CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#endif
    } இல்லையெனில் எனில் (MFX_IMPL_VIA_D3D11 == MFX_IMPL_VIA_MASK(s->impl)) {
#எனில் CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#endif
    } இல்லையெனில் எனில் (MFX_IMPL_VIA_D3D9 == MFX_IMPL_VIA_MASK(s->impl)) {
#எனில் CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#endif
    }

    எனில் (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        எனில் (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->child_device_type = device_type;
            s->child_pix_fmt     = pix_fmt;
        }
    }
    எனில் (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    திரும்பு 0;
}

நிலையான வெறுமை qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    எனில் (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = வெற்று;
    s->session_download_init = 0;

    எனில் (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = வெற்று;
    s->session_upload_init = 0;

#எனில் HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_lock);
#endif

    av_freep(&s->mem_ids);
#எனில் QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#endif
    av_freep(&s->surfaces_internal);
    av_freep(&s->handle_pairs_internal);
    av_frame_unref(&s->realigned_upload_frame);
    av_frame_unref(&s->realigned_download_frame);
    av_buffer_unref(&s->child_frames_ref);
}

நிலையான வெறுமை qsv_pool_release_dummy(வெறுமை *opaque, uint8_t *data)
{
}

நிலையான வெறுமை qsv_pool_release(வெறுமை *opaque, uint8_t *data)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)data;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.Data.MemId;
    AVHWFramesContext *child_frames_ctx;

    எனில் (!s->child_frames_ref)
        திரும்பு;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    எனில் (!child_frames_ctx->device_ctx)
        திரும்பு;

#எனில் CONFIG_VAAPI
    எனில் (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#endif

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

நிலையான AVBufferRef *qsv_fixed_pool_alloc(வெறுமை *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    எனில் (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        திரும்பு av_buffer_create((uint8_t*)(s->surfaces_internal + s->nb_surfaces_used - 1),
                                அளவு(*hwctx->surfaces), qsv_pool_release_dummy, வெற்று, 0);
    }

    திரும்பு வெற்று;
}

நிலையான AVBufferRef *qsv_dynamic_pool_alloc(வெறுமை *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx;
    QSVSurface *qsv_surface = வெற்று;
    mfxHDLPair *handle_pairs_internal = வெற்று;
    முழு ret;

    எனில் (!s->child_frames_ref)
        செல் fail;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    எனில் (!child_frames_ctx->device_ctx)
        செல் fail;

#எனில் CONFIG_DXVA2
    எனில் (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        செல் fail;
    }
#endif

    qsv_surface = av_calloc(1, அளவு(*qsv_surface));
    எனில் (!qsv_surface)
        செல் fail;

    qsv_surface->child_frame = av_frame_alloc();
    எனில் (!qsv_surface->child_frame)
        செல் fail;

    ret = av_hwframe_get_buffer(s->child_frames_ref, qsv_surface->child_frame, 0);
    எனில் (ret < 0)
        செல் fail;

    handle_pairs_internal = av_calloc(1, அளவு(*handle_pairs_internal));
    எனில் (!handle_pairs_internal)
        செல் fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    எனில் (ret < 0)
        செல் fail;

#எனில் CONFIG_VAAPI
    எனில் (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, அளவு(*surface_id_internal));
        எனில் (!surface_id_internal)
            செல் fail;

        *surface_id_internal = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
    }
#endif

#எனில் CONFIG_D3D11VA
    எனில் (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        handle_pairs_internal->first = (mfxMemId)qsv_surface->child_frame->data[0];

        எனில் (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        இல்லையெனில்
            handle_pairs_internal->second = (mfxMemId)qsv_surface->child_frame->data[1];

    }
#endif

    qsv_surface->mfx_surface.Data.MemId = (mfxMemId)handle_pairs_internal;
    திரும்பு av_buffer_create((uint8_t *)qsv_surface, அளவு(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    எனில் (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_pairs_internal);

    திரும்பு வெற்று;
}

நிலையான AVBufferRef *qsv_pool_alloc(வெறுமை *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    எனில் (hwctx->nb_surfaces == 0) {
        திரும்பு qsv_dynamic_pool_alloc(opaque, size);
    } இல்லையெனில் {
        திரும்பு qsv_fixed_pool_alloc(opaque, size);
    }
}

நிலையான முழு qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = வெற்று;
    AVBufferRef *child_frames_ref = வெற்று;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    முழு i, ret = 0;

    எனில் (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        திரும்பு AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    எனில் (!child_device_ref)
        திரும்பு AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->data;

#எனில் CONFIG_VAAPI
    எனில் (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#endif
#எனில் CONFIG_D3D11VA
    எனில் (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        ID3D11Device_AddRef((ID3D11Device*)device_priv->handle);
        child_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#endif
#எனில் CONFIG_DXVA2
    எனில் (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#endif

    ret = av_hwdevice_ctx_init(child_device_ref);
    எனில் (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        செல் fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    எனில் (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->data;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_size = ctx->initial_pool_size;
    child_frames_ctx->width             = FFALIGN(ctx->width, 16);
    child_frames_ctx->height            = FFALIGN(ctx->height, 16);

#எனில் CONFIG_D3D11VA
    எனில் (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        எனில் (hwctx->frame_type == 0)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        எனில் (hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
            child_frames_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        child_frames_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->frame_type);
    }
#endif
#எனில் CONFIG_DXVA2
    எனில் (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        எனில் (hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET)
            child_frames_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        இல்லையெனில்
            child_frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#endif

    ret = av_hwframe_ctx_init(child_frames_ref);
    எனில் (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        செல் fail;
    }

#எனில் CONFIG_VAAPI
    எனில் (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        க்கு (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = child_frames_hwctx->surface_ids + i;
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif
#எனில் CONFIG_D3D11VA
    எனில் (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        க்கு (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->texture_infos[i].texture;
            எனில்(child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            } இல்லையெனில் {
                s->handle_pairs_internal[i].second = (mfxMemId)child_frames_hwctx->texture_infos[i].index;
            }
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        எனில் (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } இல்லையெனில் {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
#endif
#எனில் CONFIG_DXVA2
    எனில் (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        க்கு (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->surfaces[i];
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        எனில் (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        இல்லையெனில்
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = வெற்று;

fail:
    av_buffer_unref(&child_device_ref);
    av_buffer_unref(&child_frames_ref);
    திரும்பு ret;
}

நிலையான முழு qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    மாறிலி AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    எனில் (!desc)
        திரும்பு AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    எனில் (!fourcc)
        திரும்பு AVERROR(EINVAL);

    surf->Info.BitDepthLuma   = desc->comp[0].depth;
    surf->Info.BitDepthChroma = desc->comp[0].depth;
    surf->Info.Shift          = qsv_shift_from_pix_fmt(ctx->sw_format);

    எனில் (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    இல்லையெனில் எனில் (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    இல்லையெனில்
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.Width          = FFALIGN(ctx->width, 16);
    surf->Info.CropW          = ctx->width;
    surf->Info.Height         = FFALIGN(ctx->height, 16);
    surf->Info.CropH          = ctx->height;
    surf->Info.FrameRateExtN  = 25;
    surf->Info.FrameRateExtD  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    திரும்பு 0;
}

நிலையான முழு qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    முழு i, ret = 0;

    எனில் (ctx->initial_pool_size < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        திரும்பு AVERROR(EINVAL);
    } இல்லையெனில் எனில் (ctx->initial_pool_size == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        எனில் (ret < 0)
            திரும்பு ret;

        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(அளவு(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, வெற்று);
        எனில் (!ffhwframesctx(ctx)->pool_internal)
            திரும்பு AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, அளவு(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        frames_hwctx->info = &s->frame_info;
        frames_hwctx->nb_surfaces = 0;

        திரும்பு 0;
    }

    s->handle_pairs_internal = av_calloc(ctx->initial_pool_size,
                                         அளவு(*s->handle_pairs_internal));
    எனில் (!s->handle_pairs_internal)
        திரும்பு AVERROR(ENOMEM);

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     அளவு(*s->surfaces_internal));
    எனில் (!s->surfaces_internal)
        திரும்பு AVERROR(ENOMEM);

    க்கு (i = 0; i < ctx->initial_pool_size; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_internal[i]);
        எனில் (ret < 0)
            திரும்பு ret;
    }

#எனில் QSV_HAVE_OPAQUE
    எனில் (!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        எனில் (ret < 0)
            திரும்பு ret;
    }
#இல்லையெனில்
    ret = qsv_init_child_ctx(ctx);
    எனில் (ret < 0)
        திரும்பு ret;
#endif

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(அளவு(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, வெற்று);
    எனில் (!ffhwframesctx(ctx)->pool_internal)
        திரும்பு AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    திரும்பு 0;
}

நிலையான mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    எனில் (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        திரும்பு MFX_ERR_UNSUPPORTED;
    எனில் (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        திரும்பு MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->இலக்கம்_Frame_Actual = hwctx->nb_surfaces;

    திரும்பு MFX_ERR_NONE;
}

நிலையான mfxStatus frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    திரும்பு MFX_ERR_NONE;
}

நிலையான mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    திரும்பு MFX_ERR_UNSUPPORTED;
}

நிலையான mfxStatus frame_unlock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    திரும்பு MFX_ERR_UNSUPPORTED;
}

நிலையான mfxStatus frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    எனில் (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    திரும்பு MFX_ERR_NONE;
}

#எனில் QSV_ONEVPL

நிலையான முழு qsv_d3d11_update_config(வெறுமை *ctx, mfxHDL handle, mfxConfig cfg)
{
    முழு ret = AVERROR_UNKNOWN;
#எனில் CONFIG_D3D11VA
    mfxStatus sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = வெற்று;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_மதிப்பு = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (வெறுமை**)&pDXGIDevice);
    எனில் (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        எனில் (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            திரும்பு ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        எனில் (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            செல் fail;
        }
    } இல்லையெனில் {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        திரும்பு ret;
    }

    impl_மதிப்பு.Type = MFX_VARIANT_TYPE_U16;
    impl_மதிப்பு.Data.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (மாறிலி mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_மதிப்பு);
    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        செல் fail;
    }

    impl_மதிப்பு.Type = MFX_VARIANT_TYPE_PTR;
    impl_மதிப்பு.Data.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (மாறிலி mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_மதிப்பு);
    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        செல் fail;
    }

    impl_மதிப்பு.Type = MFX_VARIANT_TYPE_U32;
    impl_மதிப்பு.Data.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (மாறிலி mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_மதிப்பு);
    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        செல் fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#endif
    திரும்பு ret;
}

நிலையான முழு qsv_d3d9_update_config(வெறுமை *ctx, mfxHDL handle, mfxConfig cfg)
{
    முழு ret = AVERROR_UNKNOWN;
#எனில் CONFIG_DXVA2
    mfxStatus sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = வெற்று;
    IDirect3DDevice9Ex *device_ex = வெற்று;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = வெற்று;
    IDirect3D9 *d3d9 = வெற்று;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_மதிப்பு = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    எனில் (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        செல் fail;
    }

    hr = IDirect3DDeviceManager9_LockDevice(devmgr, device_handle, &device, TRUE);
    எனில் (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        செல் fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (வெறுமை **)&device_ex);
    IDirect3DDevice9_Release(device);
    எனில் (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        செல் unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    எனில் (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        செல் unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    எனில் (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        செல் unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (வெறுமை **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    எனில் (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        செல் unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    எனில் (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        செல் release;
    }

    impl_மதிப்பு.Type = MFX_VARIANT_TYPE_PTR;
    impl_மதிப்பு.Data.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (மாறிலி mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_மதிப்பு);
    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        செல் release;
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
    திரும்பு ret;
}

நிலையான முழு qsv_va_update_config(வெறுமை *ctx, mfxHDL handle, mfxConfig cfg)
{
#எனில் CONFIG_VAAPI
#எனில் VA_CHECK_VERSION(1, 15, 0)
    mfxStatus sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_மதிப்பு = {0};

    vas = vaGetDisplayAttributes(dpy, &attr, 1);
    எனில் (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_மதிப்பு.Type = MFX_VARIANT_TYPE_U16;
        impl_மதிப்பு.Data.U16 = (attr.மதிப்பு & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (மாறிலி mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_மதிப்பு);
        எனில் (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            செல் fail;
        }
    } இல்லையெனில் {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        செல் fail;
    }

    திரும்பு 0;

fail:
#இல்லையெனில்
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#endif
#endif
    திரும்பு AVERROR_UNKNOWN;
}

நிலையான முழு qsv_new_mfx_loader(வெறுமை *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfxVersion *pver,
                              வெறுமை **ploader)
{
    mfxStatus sts;
    mfxLoader loader = வெற்று;
    mfxConfig cfg;
    mfxVariant impl_மதிப்பு = {0};

    *ploader = வெற்று;
    loader = MFXLoad();
    எனில் (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        செல் fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    எனில் (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        செல் fail;
    }

    impl_மதிப்பு.Type = MFX_VARIANT_TYPE_U32;
    impl_மதிப்பு.Data.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (மாறிலி mfxU8 *)"mfxImplDescription.Impl", impl_மதிப்பு);
    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        செல் fail;
    }

    impl_மதிப்பு.Type = MFX_VARIANT_TYPE_U32;
    impl_மதிப்பு.Data.U32 = pver->Version;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (மாறிலி mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_மதிப்பு);
    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        செல் fail;
    }

    impl_மதிப்பு.Type = MFX_VARIANT_TYPE_U32;
    impl_மதிப்பு.Data.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (மாறிலி mfxU8 *)"mfxImplDescription.VendorID", impl_மதிப்பு);
    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        செல் fail;
    }

    எனில் (MFX_HANDLE_VA_DISPLAY == handle_type) {
        எனில் (handle && qsv_va_update_config(ctx, handle, cfg))
            செல் fail;

        impl_மதிப்பு.Data.U32 = MFX_ACCEL_MODE_VIA_VAAPI;
    } இல்லையெனில் எனில் (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        எனில் (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            செல் fail;

        impl_மதிப்பு.Data.U32 = MFX_ACCEL_MODE_VIA_D3D9;
    } இல்லையெனில் {
        எனில் (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            செல் fail;

        impl_மதிப்பு.Data.U32 = MFX_ACCEL_MODE_VIA_D3D11;
    }

    impl_மதிப்பு.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (மாறிலி mfxU8 *)"mfxImplDescription.AccelerationMode", impl_மதிப்பு);
    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        செல் fail;
    }

    *ploader = loader;

    திரும்பு 0;

fail:
    எனில் (loader)
        MFXUnload(loader);

    திரும்பு AVERROR_UNKNOWN;
}

நிலையான முழு qsv_create_mfx_session_from_loader(வெறுமை *ctx, mfxLoader loader, mfxSession *psession)
{
    mfxStatus sts;
    mfxSession session = வெற்று;
    uint32_t impl_idx = 0;
    mfxVersion ver;

    போது (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        எனில் (sts == MFX_ERR_NOT_FOUND)
            நிறுத்து;
        இல்லையெனில் எனில் (sts != MFX_ERR_NONE) {
            impl_idx++;
            தொடர்;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        எனில் (sts == MFX_ERR_NONE)
            நிறுத்து;

        impl_idx++;
    }

    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        செல் fail;
    }

    sts = MFXQueryVersion(session, &ver);
    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        செல் fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    திரும்பு 0;

fail:
    எனில் (session)
        MFXClose(session);

    திரும்பு AVERROR_UNKNOWN;
}

நிலையான முழு qsv_create_mfx_session(வெறுமை *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  வெறுமை **ploader)
{
    mfxLoader loader = வெற்று;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    எனில் (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        திரும்பு AVERROR(EXDEV);
    }

    *psession = வெற்று;

    எனில் (!*ploader) {
        எனில் (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (வெறுமை **)&loader))
            செல் fail;

        av_assert0(loader);
    } இல்லையெனில்
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    எனில் (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        செல் fail;

    எனில் (!*ploader)
        *ploader = loader;

    திரும்பு 0;

fail:
    எனில் (!*ploader && loader)
        MFXUnload(loader);

    திரும்பு AVERROR_UNKNOWN;
}

#இல்லையெனில்

நிலையான முழு qsv_create_mfx_session(வெறுமை *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  வெறுமை **ploader)
{
    mfxVersion ver;
    mfxStatus sts;
    mfxSession session = வெற்று;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    *ploader = வெற்று;
    *psession = வெற்று;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        செல் fail;
    }

    sts = MFXQueryVersion(session, &ver);
    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        செல் fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    எனில் (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        செல் fail;
    }

    *psession = session;

    திரும்பு 0;

fail:
    எனில் (session)
        MFXClose(session);

    திரும்பு AVERROR_UNKNOWN;
}

#endif

நிலையான முழு qsv_init_internal_session(AVHWFramesContext *ctx,
                                     mfxSession *session, முழு upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    முழு opaque = 0;

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
    முழு                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    வெறுமை             **loader = &hwctx->loader;
    mfxSession parent_session = hwctx->session;
    mfxIMPL impl;
    mfxVersion ver;

    err = MFXQueryIMPL(parent_session, &impl);
    எனில் (err == MFX_ERR_NONE)
        err = MFXQueryVersion(parent_session, &ver);
    எனில் (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        திரும்பு AVERROR_UNKNOWN;
    }

#எனில் QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    எனில் (ret)
        செல் fail;

    எனில் (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        எனில் (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            செல் fail;
        }
    }

    எனில் (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        எனில் (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            செல் fail;
        }
    }

    எனில் (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        எனில் (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            செல் fail;
        }
    }

    memset(&par, 0, அளவு(par));

    எனில் (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_OUT_VIDEO_MEMORY :
                                 MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
#எனில் QSV_HAVE_OPAQUE
    இல்லையெனில் {
        par.ExtParam    = s->ext_buffers;
        par.இலக்கம்_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
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
    எனில் (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        செல் fail;
    }

    திரும்பு 0;

fail:
    எனில் (*session)
        MFXClose(*session);

    *session = வெற்று;

    திரும்பு ret;
}

நிலையான முழு qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    முழு opaque = 0;

    uint32_t fourcc;
    முழு i, ret;

#எனில் QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    எனில் (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        திரும்பு AVERROR(ENOSYS);
    }

    எனில் (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        எனில் (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            திரும்பு ret;
        }
    }

    எனில் (!opaque) {
        s->mem_ids = av_calloc(frames_hwctx->nb_surfaces, அளவு(*s->mem_ids));
        எனில் (!s->mem_ids)
            திரும்பு AVERROR(ENOMEM);

        க்கு (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].Data.MemId;
    }
#எனில் QSV_HAVE_OPAQUE
    இல்லையெனில் {
        s->surface_ptrs = av_calloc(frames_hwctx->nb_surfaces,
                                    அளவு(*s->surface_ptrs));
        எனில் (!s->surface_ptrs)
            திரும்பு AVERROR(ENOMEM);

        க்கு (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.இலக்கம்_Surface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = அளவு(s->opaque_alloc);

        s->ext_buffers[0] = (mfxExtBuffer*)&s->opaque_alloc;
    }
#endif

    s->session_download = வெற்று;
    s->session_upload   = வெற்று;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#எனில் HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, வெற்று);
#endif

    திரும்பு 0;
}

நிலையான முழு qsv_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    எனில் (!frame->buf[0])
        திரும்பு AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_QSV;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    திரும்பு 0;
}

நிலையான முழு qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    எண்ணிக்கை AVHWFrameTransferDirection dir,
                                    எண்ணிக்கை AVPixelFormat **formats)
{
    எண்ணிக்கை AVPixelFormat *fmts;

    fmts = av_malloc_array(2, அளவு(*fmts));
    எனில் (!fmts)
        திரும்பு AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    திரும்பு 0;
}

நிலையான முழு qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, முழு flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    முழு i;

    தேர்வு (dst_ctx->device_ctx->type) {
#எனில் CONFIG_VAAPI
    நிலை AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               அளவு(*dst_hwctx->surface_ids));
            எனில் (!dst_hwctx->surface_ids)
                திரும்பு AVERROR(ENOMEM);
            க்கு (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        நிறுத்து;
#endif
#எனில் CONFIG_D3D11VA
    நிலை AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_size = src_ctx->initial_pool_size;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 அளவு(*dst_hwctx->texture_infos));
            எனில் (!dst_hwctx->texture_infos)
                திரும்பு AVERROR(ENOMEM);
            எனில் (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            க்கு (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].index = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            எனில் (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } இல்லையெனில்
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        நிறுத்து;
#endif
#எனில் CONFIG_DXVA2
    நிலை AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            அளவு(*dst_hwctx->surfaces));
            எனில் (!dst_hwctx->surfaces)
                திரும்பு AVERROR(ENOMEM);
            க்கு (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            எனில் (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            இல்லையெனில்
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        நிறுத்து;
#endif
    இயல்பு:
        திரும்பு AVERROR(ENOSYS);
    }

    திரும்பு 0;
}

நிலையான முழு qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, மாறிலி AVFrame *src, முழு flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->data[3];
    AVHWFramesContext *child_frames_ctx;
    மாறிலி AVPixFmtDescriptor *desc;
    uint8_t *child_data;
    AVFrame *dummy;
    முழு ret = 0;

    எனில் (!s->child_frames_ref)
        திரும்பு AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;

    தேர்வு (child_frames_ctx->device_ctx->type) {
#எனில் CONFIG_VAAPI
    நிலை AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_data = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        நிறுத்து;
    }
#endif
#எனில் CONFIG_D3D11VA
    நிலை AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        நிறுத்து;
    }
#endif
#எனில் CONFIG_DXVA2
    நிலை AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        நிறுத்து;
    }
#endif
    இயல்பு:
        திரும்பு AVERROR(ENOSYS);
    }

    எனில் (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, வெற்று, வெற்று);
        எனில் (ret < 0)
            திரும்பு ret;

        dst->width   = src->width;
        dst->height  = src->height;

       எனில் (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
            dst->data[0] = pair->first;
            dst->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } இல்லையெனில் {
            dst->data[3] = child_data;
        }

        திரும்பு 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    எனில் (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        திரும்பு AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    எனில் (!dummy)
        திரும்பு AVERROR(ENOMEM);

    dummy->buf[0]        = av_buffer_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_buffer_ref(s->child_frames_ref);
    எனில் (!dummy->buf[0] || !dummy->hw_frames_ctx)
        செல் fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;

    எனில் (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        dummy->data[0] = pair->first;
        dummy->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } இல்லையெனில் {
        dummy->data[3] = child_data;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    திரும்பு ret;
}

நிலையான முழு qsv_transfer_data_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   மாறிலி AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    முழு download = !!src->hw_frames_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->data[3] : dst->data[3]);

    AVFrame *dummy;
    முழு ret;

    dummy = av_frame_alloc();
    எனில் (!dummy)
        திரும்பு AVERROR(ENOMEM);

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->data[3]       = surf->Data.MemId;
    dummy->hw_frames_ctx = s->child_frames_ref;

    ret = download ? av_hwframe_transfer_data(dst, dummy, 0) :
                     av_hwframe_transfer_data(dummy, src, 0);

    dummy->buf[0]        = வெற்று;
    dummy->data[3]       = வெற்று;
    dummy->hw_frames_ctx = வெற்று;

    av_frame_free(&dummy);

    திரும்பு ret;
}

நிலையான முழு map_frame_to_surface(மாறிலி AVFrame *frame, mfxFrameSurface1 *surface)
{
    தேர்வு (frame->format) {
    நிலை AV_PIX_FMT_NV12:
    நிலை AV_PIX_FMT_P010:
    நிலை AV_PIX_FMT_P012:
        surface->Data.Y  = frame->data[0];
        surface->Data.UV = frame->data[1];
        நிறுத்து;

    நிலை AV_PIX_FMT_YUV420P:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[1];
        surface->Data.V = frame->data[2];
        நிறுத்து;

    நிலை AV_PIX_FMT_BGRA:
        surface->Data.B = frame->data[0];
        surface->Data.G = frame->data[0] + 1;
        surface->Data.R = frame->data[0] + 2;
        surface->Data.A = frame->data[0] + 3;
        நிறுத்து;
    நிலை AV_PIX_FMT_YUYV422:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.V = frame->data[0] + 3;
        நிறுத்து;

    நிலை AV_PIX_FMT_Y210:
    நிலை AV_PIX_FMT_Y212:
        surface->Data.Y16 = (mfxU16 *)frame->data[0];
        surface->Data.U16 = (mfxU16 *)frame->data[0] + 1;
        surface->Data.V16 = (mfxU16 *)frame->data[0] + 3;
        நிறுத்து;
    நிலை AV_PIX_FMT_VUYX:
        surface->Data.V = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.Y = frame->data[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 3;
        நிறுத்து;
    நிலை AV_PIX_FMT_XV30:
        surface->Data.U = frame->data[0];
        நிறுத்து;
    நிலை AV_PIX_FMT_XV36:
        surface->Data.U = frame->data[0];
        surface->Data.Y = frame->data[0] + 2;
        surface->Data.V = frame->data[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 6;
        நிறுத்து;
#எனில் CONFIG_VAAPI
    நிலை AV_PIX_FMT_UYVY422:
        surface->Data.Y = frame->data[0] + 1;
        surface->Data.U = frame->data[0];
        surface->Data.V = frame->data[0] + 2;
        நிறுத்து;
#endif
    இயல்பு:
        திரும்பு MFX_ERR_UNSUPPORTED;
    }
    surface->Data.Pitch     = frame->linesize[0];
    surface->Data.TimeStamp = frame->pts;

    திரும்பு 0;
}

நிலையான முழு qsv_internal_session_check_init(AVHWFramesContext *ctx, முழு upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    முழு ret = 0;

    எனில் (atomic_load(inited))
        திரும்பு 0;

#எனில் HAVE_PTHREADS
    pthread_mutex_lock(&s->session_lock);
#endif

    எனில் (!atomic_load(inited)) {
        ret = qsv_init_internal_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#எனில் HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_lock);
#endif

    திரும்பு ret;
}

நிலையான முழு qsv_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  மாறிலி AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->data[3];

    mfxSyncPoint sync = வெற்று;
    mfxStatus err;
    முழு ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    முழு realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 0);
    எனில் (ret < 0)
        திரும்பு ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    எனில் (dst->height & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        எனில் (tmp_frame->format != dst->format ||
            tmp_frame->width  != FFALIGN(dst->linesize[0], 16) ||
            tmp_frame->height != FFALIGN(dst->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = dst->format;
            tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
            tmp_frame->height = FFALIGN(dst->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            எனில் (ret < 0)
                திரும்பு ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    எனில் (!s->session_download) {
        எனில் (s->child_frames_ref)
            திரும்பு qsv_transfer_data_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        திரும்பு AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst_frame, &out);

    செய் {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, வெற்று, &sync);
        எனில் (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } போது (err == MFX_WRN_DEVICE_BUSY);

    எனில் (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    செய் {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } போது (err == MFX_WRN_IN_EXECUTION);
    எனில் (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        திரும்பு AVERROR_UNKNOWN;
    }

    எனில் (realigned) {
        tmp_frame->width  = dst->width;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        எனில் (ret < 0)
            திரும்பு ret;
    }

    திரும்பு 0;
}

நிலையான முழு qsv_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                மாறிலி AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   in = {{ 0 }};
    mfxFrameSurface1 *out = (mfxFrameSurface1*)dst->data[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = வெற்று;
    mfxStatus err;
    முழு ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    மாறிலி AVFrame *src_frame;
    முழு realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 1);
    எனில் (ret < 0)
        திரும்பு ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    எனில் (src->height & 15 || src->linesize[0] & 15) {
        realigned = 1;
        எனில் (tmp_frame->format != src->format ||
            tmp_frame->width  != FFALIGN(src->width, 16) ||
            tmp_frame->height != FFALIGN(src->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = src->format;
            tmp_frame->width  = FFALIGN(src->width, 16);
            tmp_frame->height = FFALIGN(src->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            எனில் (ret < 0)
                திரும்பு ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        எனில் (ret < 0) {
            av_frame_unref(tmp_frame);
            திரும்பு ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        எனில் (ret < 0) {
            av_frame_unref(tmp_frame);
            திரும்பு ret;
        }

        tmp_info = out->Info;
        out->Info.CropW = FFMIN(out->Info.Width,  tmp_frame->width);
        out->Info.CropH = FFMIN(out->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    எனில் (!s->session_upload) {
        எனில் (s->child_frames_ref)
            திரும்பு qsv_transfer_data_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        திரும்பு AVERROR(ENOSYS);
    }

    in.Info = out->Info;
    map_frame_to_surface(src_frame, &in);

    செய் {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_upload, &in, out, வெற்று, &sync);
        எனில் (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } போது (err == MFX_WRN_DEVICE_BUSY);

    எனில் (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    செய் {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } போது (err == MFX_WRN_IN_EXECUTION);
    எனில் (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        திரும்பு AVERROR_UNKNOWN;
    }

    எனில் (realigned) {
        out->Info.CropW = tmp_info.CropW;
        out->Info.CropH = tmp_info.CropH;
    }

    திரும்பு 0;
}

நிலையான முழு qsv_dynamic_frames_derive_to(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, முழு flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    தேர்வு (src_ctx->device_ctx->type) {
#எனில் CONFIG_VAAPI
    நிலை AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        நிறுத்து;
#endif

#எனில் CONFIG_D3D11VA
    நிலை AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        எனில் (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } இல்லையெனில் {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
    நிறுத்து;
#endif

    இயல்பு:
        திரும்பு AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, அளவு(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    திரும்பு 0;
}

நிலையான முழு qsv_fixed_frames_derive_to(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, முழு flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    முழு i;

    தேர்வு (src_ctx->device_ctx->type) {
#எனில் CONFIG_VAAPI
    நிலை AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 அளவு(*s->handle_pairs_internal));
            எனில் (!s->handle_pairs_internal)
                திரும்பு AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             அளவு(*s->surfaces_internal));
            எனில் (!s->surfaces_internal)
                திரும்பு AVERROR(ENOMEM);
            க்கு (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = src_hwctx->surface_ids + i;
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        நிறுத்து;
#endif
#எனில் CONFIG_D3D11VA
    நிலை AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 அளவு(*s->handle_pairs_internal));
            எனில் (!s->handle_pairs_internal)
                திரும்பு AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_ctx->initial_pool_size,
                                             அளவு(*s->surfaces_internal));
            எனில் (!s->surfaces_internal)
                திரும்பு AVERROR(ENOMEM);
            க்கு (i = 0; i < src_ctx->initial_pool_size; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                எனில் (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                } இல்லையெனில் {
                    s->handle_pairs_internal[i].second = (mfxMemId)src_hwctx->texture_infos[i].index;
                }
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_size;
            எனில் (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            } இல்லையெனில் {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
            }
        }
        நிறுத்து;
#endif
#எனில் CONFIG_DXVA2
    நிலை AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 அளவு(*s->handle_pairs_internal));
            எனில் (!s->handle_pairs_internal)
                திரும்பு AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             அளவு(*s->surfaces_internal));
            எனில் (!s->surfaces_internal)
                திரும்பு AVERROR(ENOMEM);
            க்கு (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            எனில் (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            இல்லையெனில்
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        நிறுத்து;
#endif
    இயல்பு:
        திரும்பு AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    திரும்பு 0;
}

நிலையான முழு qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, முழு flags)
{
    எனில் (src_ctx->initial_pool_size < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        திரும்பு AVERROR(EINVAL);
    } இல்லையெனில் எனில் (src_ctx->initial_pool_size == 0) {
        திரும்பு qsv_dynamic_frames_derive_to(dst_ctx, src_ctx, flags);
    } இல்லையெனில் {
        திரும்பு qsv_fixed_frames_derive_to(dst_ctx, src_ctx, flags);
    }
}

நிலையான முழு qsv_fixed_pool_map_to(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, மாறிலி AVFrame *src, முழு flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    முழு i, err, index = -1;

    க்கு (i = 0; i < hwctx->nb_surfaces && index < 0; i++) {
        தேர்வு(src->format) {
#எனில் CONFIG_VAAPI
        நிலை AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            எனில் (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->data[3])
                index = i;
            நிறுத்து;
        }
#endif
#எனில் CONFIG_D3D11VA
        நிலை AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            எனில் (pair->first == src->data[0]
                && (pair->second == src->data[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->data[1] == (uint8_t *)0)))
                index = i;
            நிறுத்து;
        }
#endif
#எனில் CONFIG_DXVA2
        நிலை AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            எனில் (pair->first == src->data[3])
                index = i;
            நிறுத்து;
        }
#endif
        }
    }
    எனில் (index < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        திரும்பு AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, வெற்று, வெற்று);
    எனில் (err)
        திரும்பு err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)&hwctx->surfaces[index];

    திரும்பு 0;
}

நிலையான வெறுமை qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_internal = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_pairs_internal = (mfxHDLPair *)surfaces_internal->Data.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_frames->data;

    தேர்வு (src_ctx->format) {
#எனில் CONFIG_VAAPI
    நிலை AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_pairs_internal->first);

        நிறுத்து;
    }
#endif

#எனில் CONFIG_D3D11VA
    நிலை AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        நிறுத்து;
    }
#endif
    இயல்பு:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        நிறுத்து;
    }

    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
}

நிலையான முழு qsv_dynamic_pool_map_to(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, மாறிலி AVFrame *src, முழு flags)
{
    mfxFrameSurface1 *surfaces_internal = வெற்று;
    mfxHDLPair *handle_pairs_internal = வெற்று;
    முழு ret = 0;

    surfaces_internal = av_calloc(1, அளவு(*surfaces_internal));
    எனில் (!surfaces_internal) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }

    handle_pairs_internal = av_calloc(1, அளவு(*handle_pairs_internal));
    எனில் (!handle_pairs_internal) {
        ret = AVERROR(ENOMEM);
        செல் fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_internal);
    எனில் (ret < 0)
        செல் fail;

    தேர்வு (src->format) {
#எனில் CONFIG_VAAPI
    நிலை AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, அளவு(*surface_id_internal));
        எனில் (!surface_id_internal) {
            ret =AVERROR(ENOMEM);
            செல் fail;
        }

        *surface_id_internal = (VASurfaceID)(uintptr_t)src->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;

        நிறுத்து;
    }
#endif

#எனில் CONFIG_D3D11VA
    நிலை AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_pairs_internal->first = (mfxMemId)src->data[0];

        எனில் (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        } இல்லையெனில் {
            handle_pairs_internal->second = (mfxMemId)src->data[1];
        }

        நிறுத்து;
    }
#endif
    இயல்பு:
        ret = AVERROR(ENOSYS);
        செல் fail;
    }

    surfaces_internal->Data.MemId = (mfxMemId)handle_pairs_internal;

    ret = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_internal);
    எனில் (ret)
        செல் fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)surfaces_internal;

    திரும்பு 0;

fail:
    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
    திரும்பு ret;
}

நிலையான முழு qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, மாறிலி AVFrame *src, முழு flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    எனில் (hwctx->nb_surfaces)
        திரும்பு qsv_fixed_pool_map_to(dst_ctx, dst, src, flags);
    இல்லையெனில்
        திரும்பு qsv_dynamic_pool_map_to(dst_ctx, dst, src, flags);
}

நிலையான முழு qsv_frames_get_constraints(AVHWDeviceContext *ctx,
                                      மாறிலி வெறுமை *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    முழு i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    அளவு(*constraints->valid_sw_formats));
    எனில் (!constraints->valid_sw_formats)
        திரும்பு AVERROR(ENOMEM);

    க்கு (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, அளவு(*constraints->valid_hw_formats));
    எனில் (!constraints->valid_hw_formats)
        திரும்பு AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    திரும்பு 0;
}

நிலையான வெறுமை qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    எனில் (hwctx->session)
        MFXClose(hwctx->session);

    எனில் (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_buffer_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

நிலையான mfxIMPL choose_implementation(மாறிலி எழுத்து *device, எண்ணிக்கை AVHWDeviceType child_device_type)
{
    நிலையான மாறிலி கட்டமைப்பு {
        மாறிலி எழுத்து *name;
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
    முழு i;

    எனில் (device) {
        க்கு (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            எனில் (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                நிறுத்து;
            }
        எனில் (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, வெற்று, 0);
    }

    எனில் (impl != MFX_IMPL_SOFTWARE) {
        எனில் (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_VIA_D3D11;
        இல்லையெனில் எனில் (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_VIA_D3D9;
    }

    திரும்பு impl;
}

நிலையான முழு qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        முழு flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfxVersion    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfxStatus     err;
    முழு ret;

    தேர்வு (child_device_ctx->type) {
#எனில் CONFIG_VAAPI
    நிலை AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        நிறுத்து;
#endif
#எனில் CONFIG_D3D11VA
    நிலை AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        நிறுத்து;
#endif
#எனில் CONFIG_DXVA2
    நிலை AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        நிறுத்து;
#endif
    இயல்பு:
        ret = AVERROR(ENOSYS);
        செல் fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    எனில் (ret)
        செல் fail;

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    எனில் (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        செல் fail;
    }

    திரும்பு 0;

fail:
    எனில் (hwctx->session)
        MFXClose(hwctx->session);

    எனில் (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = வெற்று;
    hwctx->loader = வெற்று;
    திரும்பு ret;
}

நிலையான முழு qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, முழு flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(அளவு(*priv));
    எனில் (!priv)
        திரும்பு AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->விடுவி = qsv_device_free;

    impl = choose_implementation("hw_any", child_device_ctx->type);
    திரும்பு qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

நிலையான முழு qsv_device_create(AVHWDeviceContext *ctx, மாறிலி எழுத்து *device,
                             AVDictionary *opts, முழு flags)
{
    QSVDevicePriv *priv;
    எண்ணிக்கை AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    முழு ret;

    priv = av_mallocz(அளவு(*priv));
    எனில் (!priv)
        திரும்பு AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->விடுவி        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", வெற்று, 0);
    எனில் (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->மதிப்பு);
        எனில் (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->மதிப்பு);
            திரும்பு AVERROR(EINVAL);
        }
#எனில் QSV_ONEVPL
    } இல்லையெனில் எனில் (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } இல்லையெனில் எனில் (CONFIG_DXVA2) {
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
#இல்லையெனில்
    } இல்லையெனில் எனில் (CONFIG_DXVA2) {
        av_log(வெற்று, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } இல்லையெனில் எனில் (CONFIG_D3D11VA) {
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#endif
    } இல்லையெனில் எனில் (CONFIG_VAAPI) {
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } இல்லையெனில் {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        திரும்பு AVERROR(ENOSYS);
    }

#எனில் CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    எனில் (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->மதிப்பு);
        திரும்பு AVERROR(EINVAL);
    }
#endif

    child_device_opts = வெற்று;
    தேர்வு (child_device_type) {
#எனில் CONFIG_VAAPI
    நிலை AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_set(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_set(&child_device_opts, "driver",    "iHD",    0);
        }
        நிறுத்து;
#endif
#எனில் CONFIG_D3D11VA
    நிலை AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_set(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        நிறுத்து;
#endif
#எனில் CONFIG_DXVA2
    நிலை AV_HWDEVICE_TYPE_DXVA2:
#எனில் QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#endif
        நிறுத்து;
#endif
    இயல்பு:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            திரும்பு AVERROR(ENOSYS);
        }
        நிறுத்து;
    }

    e = av_dict_get(opts, "child_device", வெற்று, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->மதிப்பு : வெற்று, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    எனில் (ret < 0)
        திரும்பு ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->data;

    impl = choose_implementation(device, child_device_type);

    திரும்பு qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

மாறிலி HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_size      = அளவு(QSVDeviceContext),
    .frames_hwctx_size      = அளவு(QSVFramesContext),

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

    .pix_fmts = (மாறிலி எண்ணிக்கை AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
