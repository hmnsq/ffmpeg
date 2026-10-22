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

#समावेश <stdatomic.h>
#समावेश <stdint.h>
#समावेश <string.h>

#समावेश <mfxvideo.h>

#समावेश "config.h"

#अगर HAVE_PTHREADS
#समावेश <pthread.h>
#पूर्ण_अगर

#घोषणा COBJMACROS
#अगर CONFIG_VAAPI
#समावेश "hwcontext_vaapi.h"
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
#समावेश "hwcontext_d3d11va.h"
#पूर्ण_अगर
#अगर CONFIG_DXVA2
#समावेश <initguid.h>
#समावेश "hwcontext_dxva2.h"
#पूर्ण_अगर

#समावेश "buffer.h"
#समावेश "common.h"
#समावेश "hwcontext.h"
#समावेश "hwcontext_internal.h"
#समावेश "hwcontext_qsv.h"
#समावेश "mem.h"
#समावेश "pixfmt.h"
#समावेश "pixdesc.h"
#समावेश "time.h"
#समावेश "imgutils.h"
#समावेश "avassert.h"

#घोषणा QSV_VERSION_ATLEAST(MAJOR, MINOR)   \
    (MFX_VERSION_MAJOR > (MAJOR) ||         \
     MFX_VERSION_MAJOR == (MAJOR) && MFX_VERSION_MINOR >= (MINOR))

#घोषणा QSV_RUNTIME_VERSION_ATLEAST(MFX_VERSION, MAJOR, MINOR)          \
    ((MFX_VERSION.Major > (MAJOR)) ||                                   \
     (MFX_VERSION.Major == (MAJOR) && MFX_VERSION.Minor >= (MINOR)))

#घोषणा MFX_IMPL_VIA_MASK(impl) (0x0f00 & (impl))
#घोषणा QSV_ONEVPL       QSV_VERSION_ATLEAST(2, 0)
#घोषणा QSV_HAVE_OPAQUE  !QSV_ONEVPL

#अगर QSV_ONEVPL
#समावेश <mfxdispatcher.h>
#अन्यथा
#घोषणा MFXUnload(a) करो { } जबतक(0)
#पूर्ण_अगर

प्रकार काष्ठा QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

प्रकार काष्ठा QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfxVersion          ver;
    mfxIMPL             impl;

    क्रमागत AVHWDeviceType child_device_type;
    क्रमागत AVPixelFormat  child_pix_fmt;
} QSVDeviceContext;

प्रकार काष्ठा QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#अगर HAVE_PTHREADS
    pthread_mutex_t session_lock;
#पूर्ण_अगर

    AVBufferRef *child_frames_ref;
    mfxFrameSurface1 *surfaces_internal;
    mfxHDLPair *handle_pairs_internal;
    पूर्णांक             nb_surfaces_used;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#अगर QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfx_Ext_बफर *ext_buffers[1];
#पूर्ण_अगर
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

प्रकार काष्ठा QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

अटल स्थिर काष्ठा {
    क्रमागत AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_shift;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#अगर CONFIG_VAAPI
    { AV_PIX_FMT_UYVY422,
                       MFX_FOURCC_UYVY, 0 },
#पूर्ण_अगर
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
#अगर QSV_VERSION_ATLEAST(1, 31)
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
#पूर्ण_अगर
};

बाह्य पूर्णांक ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          क्रमागत AVHWDeviceType base_dev_type,
                                          व्योम **base_handle);

अटल पूर्णांक qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
पूर्णांक ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                   क्रमागत AVHWDeviceType base_dev_type,
                                   व्योम **base_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->तथ्य_2.MemId;
    चयन (base_dev_type) {
#अगर CONFIG_VAAPI
    हाल AV_HWDEVICE_TYPE_VAAPI:
        base_handle[0] = handle_pair->first;
        वापस 0;
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
    हाल AV_HWDEVICE_TYPE_D3D11VA:
        base_handle[0] = handle_pair->first;
        base_handle[1] = handle_pair->second;
        वापस 0;
#पूर्ण_अगर
#अगर CONFIG_DXVA2
    हाल AV_HWDEVICE_TYPE_DXVA2:
        base_handle[0] = handle_pair->first;
        वापस 0;
#पूर्ण_अगर
    }
    वापस AVERROR(EINVAL);
}

अटल uint32_t qsv_fourcc_from_pix_fmt(क्रमागत AVPixelFormat pix_fmt)
{
    पूर्णांक i;
    क्रम (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        अगर (supported_pixel_formats[i].pix_fmt == pix_fmt)
            वापस supported_pixel_formats[i].fourcc;
    }
    वापस 0;
}

अटल uint16_t qsv_shift_from_pix_fmt(क्रमागत AVPixelFormat pix_fmt)
{
    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        अगर (supported_pixel_formats[i].pix_fmt == pix_fmt)
            वापस supported_pixel_formats[i].mfx_shift;
    }

    वापस 0;
}

#अगर CONFIG_D3D11VA
अटल uint32_t qsv_get_d3d11va_bind_flags(पूर्णांक mem_type)
{
    uint32_t bind_flags = 0;

    अगर ((mem_type & MFX_MEMTYPE_VIDEO_MEMORY_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_INTERNAL_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    अन्यथा
        bind_flags = D3D11_BIND_DECODER;

    अगर ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    वापस bind_flags;
}
#पूर्ण_अगर

अटल पूर्णांक qsv_fill_border(AVFrame *dst, स्थिर AVFrame *src)
{
    स्थिर AVPixFmtDescriptor *desc;
    पूर्णांक i, planes_nb = 0;
    अगर (dst->format != src->format)
        वापस AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    क्रम (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    क्रम (i = 0; i < planes_nb; i++) {
        पूर्णांक sheight, dheight, y;
        सूचक_भेद_प्रकार swidth = av_image_get_linesize(src->format,
                                                 src->width,
                                                 i);
        सूचक_भेद_प्रकार dwidth = av_image_get_linesize(dst->format,
                                                 dst->width,
                                                 i);
        स्थिर AVComponentDescriptor comp = desc->comp[i];
        अगर (swidth < 0 || dwidth < 0) {
            av_log(शून्य, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            वापस AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        अगर (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        क्रम (y = 0; y < sheight; y++) {
            व्योम *पंक्ति_ptr = dst->तथ्य[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(पंक्ति_ptr,
                           comp.depth > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        क्रम (y = sheight; y < dheight; y++) {
            स_नकल(dst->तथ्य[i]+y*dst->linesize[i],
                   dst->तथ्य[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    वापस 0;
}

अटल पूर्णांक qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    पूर्णांक   hw_handle_supported = 0;
    mfxHandleType handle_type;
    क्रमागत AVHWDeviceType device_type;
    क्रमागत AVPixelFormat  pix_fmt;
    mfxStatus err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    अगर (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    अगर (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        वापस AVERROR_UNKNOWN;
    }

    अगर (MFX_IMPL_VIA_VAAPI == MFX_IMPL_VIA_MASK(s->impl)) {
#अगर CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#पूर्ण_अगर
    } अन्यथा अगर (MFX_IMPL_VIA_D3D11 == MFX_IMPL_VIA_MASK(s->impl)) {
#अगर CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#पूर्ण_अगर
    } अन्यथा अगर (MFX_IMPL_VIA_D3D9 == MFX_IMPL_VIA_MASK(s->impl)) {
#अगर CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#पूर्ण_अगर
    }

    अगर (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        अगर (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->child_device_type = device_type;
            s->child_pix_fmt     = pix_fmt;
        }
    }
    अगर (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    वापस 0;
}

अटल व्योम qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    अगर (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = शून्य;
    s->session_download_init = 0;

    अगर (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = शून्य;
    s->session_upload_init = 0;

#अगर HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_lock);
#पूर्ण_अगर

    av_freep(&s->mem_ids);
#अगर QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#पूर्ण_अगर
    av_freep(&s->surfaces_internal);
    av_freep(&s->handle_pairs_internal);
    av_frame_unref(&s->realigned_upload_frame);
    av_frame_unref(&s->realigned_download_frame);
    av_बफर_unref(&s->child_frames_ref);
}

अटल व्योम qsv_pool_release_dummy(व्योम *opaque, uint8_t *तथ्य)
{
}

अटल व्योम qsv_pool_release(व्योम *opaque, uint8_t *तथ्य)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)तथ्य;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.तथ्य_2.MemId;
    AVHWFramesContext *child_frames_ctx;

    अगर (!s->child_frames_ref)
        वापस;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->तथ्य;
    अगर (!child_frames_ctx->device_ctx)
        वापस;

#अगर CONFIG_VAAPI
    अगर (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#पूर्ण_अगर

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

अटल AVBufferRef *qsv_fixed_pool_alloc(व्योम *opaque, माप_प्रकार आकार)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    अगर (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        वापस av_बफर_create((uint8_t*)(s->surfaces_internal + s->nb_surfaces_used - 1),
                                माप(*hwctx->surfaces), qsv_pool_release_dummy, शून्य, 0);
    }

    वापस शून्य;
}

अटल AVBufferRef *qsv_dynamic_pool_alloc(व्योम *opaque, माप_प्रकार आकार)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx;
    QSVSurface *qsv_surface = शून्य;
    mfxHDLPair *handle_pairs_internal = शून्य;
    पूर्णांक ret;

    अगर (!s->child_frames_ref)
        जाओ fail;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->तथ्य;
    अगर (!child_frames_ctx->device_ctx)
        जाओ fail;

#अगर CONFIG_DXVA2
    अगर (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        जाओ fail;
    }
#पूर्ण_अगर

    qsv_surface = av_calloc(1, माप(*qsv_surface));
    अगर (!qsv_surface)
        जाओ fail;

    qsv_surface->child_frame = av_frame_alloc();
    अगर (!qsv_surface->child_frame)
        जाओ fail;

    ret = av_hwframe_get_बफर(s->child_frames_ref, qsv_surface->child_frame, 0);
    अगर (ret < 0)
        जाओ fail;

    handle_pairs_internal = av_calloc(1, माप(*handle_pairs_internal));
    अगर (!handle_pairs_internal)
        जाओ fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    अगर (ret < 0)
        जाओ fail;

#अगर CONFIG_VAAPI
    अगर (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, माप(*surface_id_internal));
        अगर (!surface_id_internal)
            जाओ fail;

        *surface_id_internal = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->तथ्य[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
    }
#पूर्ण_अगर

#अगर CONFIG_D3D11VA
    अगर (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        handle_pairs_internal->first = (mfxMemId)qsv_surface->child_frame->तथ्य[0];

        अगर (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        अन्यथा
            handle_pairs_internal->second = (mfxMemId)qsv_surface->child_frame->तथ्य[1];

    }
#पूर्ण_अगर

    qsv_surface->mfx_surface.तथ्य_2.MemId = (mfxMemId)handle_pairs_internal;
    वापस av_बफर_create((uint8_t *)qsv_surface, माप(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    अगर (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_pairs_internal);

    वापस शून्य;
}

अटल AVBufferRef *qsv_pool_alloc(व्योम *opaque, माप_प्रकार आकार)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    अगर (hwctx->nb_surfaces == 0) {
        वापस qsv_dynamic_pool_alloc(opaque, आकार);
    } अन्यथा {
        वापस qsv_fixed_pool_alloc(opaque, आकार);
    }
}

अटल पूर्णांक qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = शून्य;
    AVBufferRef *child_frames_ref = शून्य;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    पूर्णांक i, ret = 0;

    अगर (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        वापस AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    अगर (!child_device_ref)
        वापस AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->तथ्य;

#अगर CONFIG_VAAPI
    अगर (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
    अगर (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        ID3D11Device_AddRef((ID3D11Device*)device_priv->handle);
        child_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#पूर्ण_अगर
#अगर CONFIG_DXVA2
    अगर (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#पूर्ण_अगर

    ret = av_hwdevice_ctx_init(child_device_ref);
    अगर (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        जाओ fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    अगर (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->तथ्य;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_आकार = ctx->initial_pool_आकार;
    child_frames_ctx->width             = FFALIGN(ctx->width, 16);
    child_frames_ctx->height            = FFALIGN(ctx->height, 16);

#अगर CONFIG_D3D11VA
    अगर (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        अगर (hwctx->frame_type == 0)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        अगर (hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
            child_frames_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        child_frames_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->frame_type);
    }
#पूर्ण_अगर
#अगर CONFIG_DXVA2
    अगर (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        अगर (hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET)
            child_frames_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        अन्यथा
            child_frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#पूर्ण_अगर

    ret = av_hwframe_ctx_init(child_frames_ref);
    अगर (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        जाओ fail;
    }

#अगर CONFIG_VAAPI
    अगर (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        क्रम (i = 0; i < ctx->initial_pool_आकार; i++) {
            s->handle_pairs_internal[i].first = child_frames_hwctx->surface_ids + i;
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].तथ्य_2.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
    अगर (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        क्रम (i = 0; i < ctx->initial_pool_आकार; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->texture_infos[i].texture;
            अगर(child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            } अन्यथा {
                s->handle_pairs_internal[i].second = (mfxMemId)child_frames_hwctx->texture_infos[i].सूचकांक;
            }
            s->surfaces_internal[i].तथ्य_2.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        अगर (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } अन्यथा {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
#पूर्ण_अगर
#अगर CONFIG_DXVA2
    अगर (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        क्रम (i = 0; i < ctx->initial_pool_आकार; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->surfaces[i];
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].तथ्य_2.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        अगर (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        अन्यथा
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#पूर्ण_अगर

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = शून्य;

fail:
    av_बफर_unref(&child_device_ref);
    av_बफर_unref(&child_frames_ref);
    वापस ret;
}

अटल पूर्णांक qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    स्थिर AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    अगर (!desc)
        वापस AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    अगर (!fourcc)
        वापस AVERROR(EINVAL);

    surf->Info.BitDepthLuma   = desc->comp[0].depth;
    surf->Info.BitDepthChroma = desc->comp[0].depth;
    surf->Info.Shift          = qsv_shift_from_pix_fmt(ctx->sw_format);

    अगर (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    अन्यथा अगर (desc->log2_chroma_w)
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

    वापस 0;
}

अटल पूर्णांक qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    पूर्णांक i, ret = 0;

    अगर (ctx->initial_pool_आकार < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        वापस AVERROR(EINVAL);
    } अन्यथा अगर (ctx->initial_pool_आकार == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        अगर (ret < 0)
            वापस ret;

        ffhwframesctx(ctx)->pool_internal = av_बफर_pool_init2(माप(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, शून्य);
        अगर (!ffhwframesctx(ctx)->pool_internal)
            वापस AVERROR(ENOMEM);

        स_रखो(&mfx_surf1, 0, माप(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        frames_hwctx->info = &s->frame_info;
        frames_hwctx->nb_surfaces = 0;

        वापस 0;
    }

    s->handle_pairs_internal = av_calloc(ctx->initial_pool_आकार,
                                         माप(*s->handle_pairs_internal));
    अगर (!s->handle_pairs_internal)
        वापस AVERROR(ENOMEM);

    s->surfaces_internal = av_calloc(ctx->initial_pool_आकार,
                                     माप(*s->surfaces_internal));
    अगर (!s->surfaces_internal)
        वापस AVERROR(ENOMEM);

    क्रम (i = 0; i < ctx->initial_pool_आकार; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_internal[i]);
        अगर (ret < 0)
            वापस ret;
    }

#अगर QSV_HAVE_OPAQUE
    अगर (!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        अगर (ret < 0)
            वापस ret;
    }
#अन्यथा
    ret = qsv_init_child_ctx(ctx);
    अगर (ret < 0)
        वापस ret;
#पूर्ण_अगर

    ffhwframesctx(ctx)->pool_internal = av_बफर_pool_init2(माप(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, शून्य);
    अगर (!ffhwframesctx(ctx)->pool_internal)
        वापस AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_आकार;

    वापस 0;
}

अटल mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    अगर (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        वापस MFX_ERR_UNSUPPORTED;
    अगर (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        वापस MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->अंक_Frame_Actual = hwctx->nb_surfaces;

    वापस MFX_ERR_NONE;
}

अटल mfxStatus frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    वापस MFX_ERR_NONE;
}

अटल mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfx_Frame_तथ्य *ptr)
{
    वापस MFX_ERR_UNSUPPORTED;
}

अटल mfxStatus frame_unlock(mfxHDL pthis, mfxMemId mid, mfx_Frame_तथ्य *ptr)
{
    वापस MFX_ERR_UNSUPPORTED;
}

अटल mfxStatus frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    अगर (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    वापस MFX_ERR_NONE;
}

#अगर QSV_ONEVPL

अटल पूर्णांक qsv_d3d11_update_config(व्योम *ctx, mfxHDL handle, mfxConfig cfg)
{
    पूर्णांक ret = AVERROR_UNKNOWN;
#अगर CONFIG_D3D11VA
    mfxStatus sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = शून्य;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_मूल्य = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (व्योम**)&pDXGIDevice);
    अगर (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        अगर (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            वापस ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        अगर (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            जाओ fail;
        }
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        वापस ret;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_U16;
    impl_मूल्य.तथ्य_2.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिर mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_मूल्य);
    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        जाओ fail;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_PTR;
    impl_मूल्य.तथ्य_2.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिर mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_मूल्य);
    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        जाओ fail;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_U32;
    impl_मूल्य.तथ्य_2.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिर mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_मूल्य);
    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        जाओ fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#पूर्ण_अगर
    वापस ret;
}

अटल पूर्णांक qsv_d3d9_update_config(व्योम *ctx, mfxHDL handle, mfxConfig cfg)
{
    पूर्णांक ret = AVERROR_UNKNOWN;
#अगर CONFIG_DXVA2
    mfxStatus sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = शून्य;
    IDirect3DDevice9Ex *device_ex = शून्य;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = शून्य;
    IDirect3D9 *d3d9 = शून्य;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_मूल्य = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    अगर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        जाओ fail;
    }

    hr = IDirect3DDeviceManager9_LockDevice(devmgr, device_handle, &device, TRUE);
    अगर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        जाओ fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (व्योम **)&device_ex);
    IDirect3DDevice9_Release(device);
    अगर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        जाओ unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    अगर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        जाओ unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    अगर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        जाओ unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (व्योम **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    अगर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        जाओ unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    अगर (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        जाओ release;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_PTR;
    impl_मूल्य.तथ्य_2.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिर mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_मूल्य);
    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        जाओ release;
    }

    ret = 0;

release:
    IDirect3D9Ex_Release(d3d9ex);
    IDirect3DDevice9Ex_Release(device_ex);

unlock:
    IDirect3DDeviceManager9_UnlockDevice(devmgr, device_handle, FALSE);
    IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
fail:
#पूर्ण_अगर
    वापस ret;
}

अटल पूर्णांक qsv_va_update_config(व्योम *ctx, mfxHDL handle, mfxConfig cfg)
{
#अगर CONFIG_VAAPI
#अगर VA_CHECK_VERSION(1, 15, 0)
    mfxStatus sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_मूल्य = {0};

    vas = vaGetDisplayAttributes(dpy, &attr, 1);
    अगर (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_मूल्य.Type = MFX_VARIANT_TYPE_U16;
        impl_मूल्य.तथ्य_2.U16 = (attr.मूल्य & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (स्थिर mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_मूल्य);
        अगर (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            जाओ fail;
        }
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        जाओ fail;
    }

    वापस 0;

fail:
#अन्यथा
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#पूर्ण_अगर
#पूर्ण_अगर
    वापस AVERROR_UNKNOWN;
}

अटल पूर्णांक qsv_new_mfx_loader(व्योम *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfxVersion *pver,
                              व्योम **ploader)
{
    mfxStatus sts;
    mfxLoader loader = शून्य;
    mfxConfig cfg;
    mfxVariant impl_मूल्य = {0};

    *ploader = शून्य;
    loader = MFXLoad();
    अगर (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        जाओ fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    अगर (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        जाओ fail;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_U32;
    impl_मूल्य.तथ्य_2.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिर mfxU8 *)"mfxImplDescription.Impl", impl_मूल्य);
    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        जाओ fail;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_U32;
    impl_मूल्य.तथ्य_2.U32 = pver->Version;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिर mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_मूल्य);
    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        जाओ fail;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_U32;
    impl_मूल्य.तथ्य_2.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिर mfxU8 *)"mfxImplDescription.VendorID", impl_मूल्य);
    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        जाओ fail;
    }

    अगर (MFX_HANDLE_VA_DISPLAY == handle_type) {
        अगर (handle && qsv_va_update_config(ctx, handle, cfg))
            जाओ fail;

        impl_मूल्य.तथ्य_2.U32 = MFX_ACCEL_MODE_VIA_VAAPI;
    } अन्यथा अगर (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        अगर (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            जाओ fail;

        impl_मूल्य.तथ्य_2.U32 = MFX_ACCEL_MODE_VIA_D3D9;
    } अन्यथा {
        अगर (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            जाओ fail;

        impl_मूल्य.तथ्य_2.U32 = MFX_ACCEL_MODE_VIA_D3D11;
    }

    impl_मूल्य.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (स्थिर mfxU8 *)"mfxImplDescription.AccelerationMode", impl_मूल्य);
    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        जाओ fail;
    }

    *ploader = loader;

    वापस 0;

fail:
    अगर (loader)
        MFXUnload(loader);

    वापस AVERROR_UNKNOWN;
}

अटल पूर्णांक qsv_create_mfx_session_from_loader(व्योम *ctx, mfxLoader loader, mfxSession *psession)
{
    mfxStatus sts;
    mfxSession session = शून्य;
    uint32_t impl_idx = 0;
    mfxVersion ver;

    जबतक (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        अगर (sts == MFX_ERR_NOT_FOUND)
            अवरोध;
        अन्यथा अगर (sts != MFX_ERR_NONE) {
            impl_idx++;
            जारी;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        अगर (sts == MFX_ERR_NONE)
            अवरोध;

        impl_idx++;
    }

    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        जाओ fail;
    }

    sts = MFXQueryVersion(session, &ver);
    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        जाओ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    वापस 0;

fail:
    अगर (session)
        MFXClose(session);

    वापस AVERROR_UNKNOWN;
}

अटल पूर्णांक qsv_create_mfx_session(व्योम *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  व्योम **ploader)
{
    mfxLoader loader = शून्य;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    अगर (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        वापस AVERROR(EXDEV);
    }

    *psession = शून्य;

    अगर (!*ploader) {
        अगर (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (व्योम **)&loader))
            जाओ fail;

        av_assert0(loader);
    } अन्यथा
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    अगर (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        जाओ fail;

    अगर (!*ploader)
        *ploader = loader;

    वापस 0;

fail:
    अगर (!*ploader && loader)
        MFXUnload(loader);

    वापस AVERROR_UNKNOWN;
}

#अन्यथा

अटल पूर्णांक qsv_create_mfx_session(व्योम *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  व्योम **ploader)
{
    mfxVersion ver;
    mfxStatus sts;
    mfxSession session = शून्य;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    *ploader = शून्य;
    *psession = शून्य;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        जाओ fail;
    }

    sts = MFXQueryVersion(session, &ver);
    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        जाओ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    अगर (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        जाओ fail;
    }

    *psession = session;

    वापस 0;

fail:
    अगर (session)
        MFXClose(session);

    वापस AVERROR_UNKNOWN;
}

#पूर्ण_अगर

अटल पूर्णांक qsv_init_internal_session(AVHWFramesContext *ctx,
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
    व्योम             **loader = &hwctx->loader;
    mfxSession parent_session = hwctx->session;
    mfxIMPL impl;
    mfxVersion ver;

    err = MFXQueryIMPL(parent_session, &impl);
    अगर (err == MFX_ERR_NONE)
        err = MFXQueryVersion(parent_session, &ver);
    अगर (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        वापस AVERROR_UNKNOWN;
    }

#अगर QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#पूर्ण_अगर

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    अगर (ret)
        जाओ fail;

    अगर (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        अगर (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            जाओ fail;
        }
    }

    अगर (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        अगर (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            जाओ fail;
        }
    }

    अगर (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        अगर (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            जाओ fail;
        }
    }

    स_रखो(&par, 0, माप(par));

    अगर (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_OUT_VIDEO_MEMORY :
                                 MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
#अगर QSV_HAVE_OPAQUE
    अन्यथा {
        par.ExtParam    = s->ext_buffers;
        par.अंक_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
        par.IOPattern   = upload ? MFX_IOPATTERN_OUT_OPAQUE_MEMORY :
                                   MFX_IOPATTERN_IN_OPAQUE_MEMORY;
    }
#पूर्ण_अगर

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
    अगर (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        जाओ fail;
    }

    वापस 0;

fail:
    अगर (*session)
        MFXClose(*session);

    *session = शून्य;

    वापस ret;
}

अटल पूर्णांक qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    पूर्णांक opaque = 0;

    uint32_t fourcc;
    पूर्णांक i, ret;

#अगर QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#पूर्ण_अगर

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    अगर (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        वापस AVERROR(ENOSYS);
    }

    अगर (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        अगर (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            वापस ret;
        }
    }

    अगर (!opaque) {
        s->mem_ids = av_calloc(frames_hwctx->nb_surfaces, माप(*s->mem_ids));
        अगर (!s->mem_ids)
            वापस AVERROR(ENOMEM);

        क्रम (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].तथ्य_2.MemId;
    }
#अगर QSV_HAVE_OPAQUE
    अन्यथा {
        s->surface_ptrs = av_calloc(frames_hwctx->nb_surfaces,
                                    माप(*s->surface_ptrs));
        अगर (!s->surface_ptrs)
            वापस AVERROR(ENOMEM);

        क्रम (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.अंक_Surface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.बफर_Id = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.बफर_Sz = माप(s->opaque_alloc);

        s->ext_buffers[0] = (mfx_Ext_बफर*)&s->opaque_alloc;
    }
#पूर्ण_अगर

    s->session_download = शून्य;
    s->session_upload   = शून्य;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#अगर HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, शून्य);
#पूर्ण_अगर

    वापस 0;
}

अटल पूर्णांक qsv_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    अगर (!frame->buf[0])
        वापस AVERROR(ENOMEM);

    frame->तथ्य[3] = frame->buf[0]->तथ्य;
    frame->format  = AV_PIX_FMT_QSV;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    वापस 0;
}

अटल पूर्णांक qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    क्रमागत AVHWFrameTransferDirection dir,
                                    क्रमागत AVPixelFormat **formats)
{
    क्रमागत AVPixelFormat *fmts;

    fmts = av_malloc_array(2, माप(*fmts));
    अगर (!fmts)
        वापस AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    वापस 0;
}

अटल पूर्णांक qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, पूर्णांक flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    पूर्णांक i;

    चयन (dst_ctx->device_ctx->type) {
#अगर CONFIG_VAAPI
    हाल AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               माप(*dst_hwctx->surface_ids));
            अगर (!dst_hwctx->surface_ids)
                वापस AVERROR(ENOMEM);
            क्रम (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].तथ्य_2.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        अवरोध;
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
    हाल AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_आकार = src_ctx->initial_pool_आकार;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 माप(*dst_hwctx->texture_infos));
            अगर (!dst_hwctx->texture_infos)
                वापस AVERROR(ENOMEM);
            अगर (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            क्रम (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].तथ्य_2.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].सूचकांक = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            अगर (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } अन्यथा
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        अवरोध;
#पूर्ण_अगर
#अगर CONFIG_DXVA2
    हाल AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            माप(*dst_hwctx->surfaces));
            अगर (!dst_hwctx->surfaces)
                वापस AVERROR(ENOMEM);
            क्रम (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].तथ्य_2.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            अगर (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            अन्यथा
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        अवरोध;
#पूर्ण_अगर
    शेष:
        वापस AVERROR(ENOSYS);
    }

    वापस 0;
}

अटल पूर्णांक qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, स्थिर AVFrame *src, पूर्णांक flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->तथ्य[3];
    AVHWFramesContext *child_frames_ctx;
    स्थिर AVPixFmtDescriptor *desc;
    uint8_t *child_तथ्य;
    AVFrame *dummy;
    पूर्णांक ret = 0;

    अगर (!s->child_frames_ref)
        वापस AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->तथ्य;

    चयन (child_frames_ctx->device_ctx->type) {
#अगर CONFIG_VAAPI
    हाल AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->तथ्य_2.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_तथ्य = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        अवरोध;
    }
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
    हाल AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->तथ्य_2.MemId;
        child_तथ्य = pair->first;
        अवरोध;
    }
#पूर्ण_अगर
#अगर CONFIG_DXVA2
    हाल AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->तथ्य_2.MemId;
        child_तथ्य = pair->first;
        अवरोध;
    }
#पूर्ण_अगर
    शेष:
        वापस AVERROR(ENOSYS);
    }

    अगर (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, शून्य, शून्य);
        अगर (ret < 0)
            वापस ret;

        dst->width   = src->width;
        dst->height  = src->height;

       अगर (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->तथ्य_2.MemId;
            dst->तथ्य[0] = pair->first;
            dst->तथ्य[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } अन्यथा {
            dst->तथ्य[3] = child_तथ्य;
        }

        वापस 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    अगर (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        वापस AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    अगर (!dummy)
        वापस AVERROR(ENOMEM);

    dummy->buf[0]        = av_बफर_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_बफर_ref(s->child_frames_ref);
    अगर (!dummy->buf[0] || !dummy->hw_frames_ctx)
        जाओ fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;

    अगर (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->तथ्य_2.MemId;
        dummy->तथ्य[0] = pair->first;
        dummy->तथ्य[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } अन्यथा {
        dummy->तथ्य[3] = child_तथ्य;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    वापस ret;
}

अटल पूर्णांक qsv_transfer_तथ्य_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   स्थिर AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->तथ्य;
    पूर्णांक download = !!src->hw_frames_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->तथ्य[3] : dst->तथ्य[3]);

    AVFrame *dummy;
    पूर्णांक ret;

    dummy = av_frame_alloc();
    अगर (!dummy)
        वापस AVERROR(ENOMEM);

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->तथ्य[3]       = surf->तथ्य_2.MemId;
    dummy->hw_frames_ctx = s->child_frames_ref;

    ret = download ? av_hwframe_transfer_तथ्य(dst, dummy, 0) :
                     av_hwframe_transfer_तथ्य(dummy, src, 0);

    dummy->buf[0]        = शून्य;
    dummy->तथ्य[3]       = शून्य;
    dummy->hw_frames_ctx = शून्य;

    av_frame_free(&dummy);

    वापस ret;
}

अटल पूर्णांक map_frame_to_surface(स्थिर AVFrame *frame, mfxFrameSurface1 *surface)
{
    चयन (frame->format) {
    हाल AV_PIX_FMT_NV12:
    हाल AV_PIX_FMT_P010:
    हाल AV_PIX_FMT_P012:
        surface->तथ्य_2.Y  = frame->तथ्य[0];
        surface->तथ्य_2.UV = frame->तथ्य[1];
        अवरोध;

    हाल AV_PIX_FMT_YUV420P:
        surface->तथ्य_2.Y = frame->तथ्य[0];
        surface->तथ्य_2.U = frame->तथ्य[1];
        surface->तथ्य_2.V = frame->तथ्य[2];
        अवरोध;

    हाल AV_PIX_FMT_BGRA:
        surface->तथ्य_2.B = frame->तथ्य[0];
        surface->तथ्य_2.G = frame->तथ्य[0] + 1;
        surface->तथ्य_2.R = frame->तथ्य[0] + 2;
        surface->तथ्य_2.A = frame->तथ्य[0] + 3;
        अवरोध;
    हाल AV_PIX_FMT_YUYV422:
        surface->तथ्य_2.Y = frame->तथ्य[0];
        surface->तथ्य_2.U = frame->तथ्य[0] + 1;
        surface->तथ्य_2.V = frame->तथ्य[0] + 3;
        अवरोध;

    हाल AV_PIX_FMT_Y210:
    हाल AV_PIX_FMT_Y212:
        surface->तथ्य_2.Y16 = (mfxU16 *)frame->तथ्य[0];
        surface->तथ्य_2.U16 = (mfxU16 *)frame->तथ्य[0] + 1;
        surface->तथ्य_2.V16 = (mfxU16 *)frame->तथ्य[0] + 3;
        अवरोध;
    हाल AV_PIX_FMT_VUYX:
        surface->तथ्य_2.V = frame->तथ्य[0];
        surface->तथ्य_2.U = frame->तथ्य[0] + 1;
        surface->तथ्य_2.Y = frame->तथ्य[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->तथ्य_2.A = frame->तथ्य[0] + 3;
        अवरोध;
    हाल AV_PIX_FMT_XV30:
        surface->तथ्य_2.U = frame->तथ्य[0];
        अवरोध;
    हाल AV_PIX_FMT_XV36:
        surface->तथ्य_2.U = frame->तथ्य[0];
        surface->तथ्य_2.Y = frame->तथ्य[0] + 2;
        surface->तथ्य_2.V = frame->तथ्य[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->तथ्य_2.A = frame->तथ्य[0] + 6;
        अवरोध;
#अगर CONFIG_VAAPI
    हाल AV_PIX_FMT_UYVY422:
        surface->तथ्य_2.Y = frame->तथ्य[0] + 1;
        surface->तथ्य_2.U = frame->तथ्य[0];
        surface->तथ्य_2.V = frame->तथ्य[0] + 2;
        अवरोध;
#पूर्ण_अगर
    शेष:
        वापस MFX_ERR_UNSUPPORTED;
    }
    surface->तथ्य_2.Pitch     = frame->linesize[0];
    surface->तथ्य_2.TimeStamp = frame->pts;

    वापस 0;
}

अटल पूर्णांक qsv_internal_session_check_init(AVHWFramesContext *ctx, पूर्णांक upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    पूर्णांक ret = 0;

    अगर (atomic_load(inited))
        वापस 0;

#अगर HAVE_PTHREADS
    pthread_mutex_lock(&s->session_lock);
#पूर्ण_अगर

    अगर (!atomic_load(inited)) {
        ret = qsv_init_internal_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#अगर HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_lock);
#पूर्ण_अगर

    वापस ret;
}

अटल पूर्णांक qsv_transfer_तथ्य_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  स्थिर AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->तथ्य[3];

    mfxSyncPoint sync = शून्य;
    mfxStatus err;
    पूर्णांक ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    पूर्णांक realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 0);
    अगर (ret < 0)
        वापस ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    अगर (dst->height & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        अगर (tmp_frame->format != dst->format ||
            tmp_frame->width  != FFALIGN(dst->linesize[0], 16) ||
            tmp_frame->height != FFALIGN(dst->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = dst->format;
            tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
            tmp_frame->height = FFALIGN(dst->height, 16);
            ret = av_frame_get_बफर(tmp_frame, 0);
            अगर (ret < 0)
                वापस ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    अगर (!s->session_download) {
        अगर (s->child_frames_ref)
            वापस qsv_transfer_तथ्य_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        वापस AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst_frame, &out);

    करो {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, शून्य, &sync);
        अगर (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } जबतक (err == MFX_WRN_DEVICE_BUSY);

    अगर (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        वापस AVERROR_UNKNOWN;
    }

    करो {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } जबतक (err == MFX_WRN_IN_EXECUTION);
    अगर (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        वापस AVERROR_UNKNOWN;
    }

    अगर (realigned) {
        tmp_frame->width  = dst->width;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        अगर (ret < 0)
            वापस ret;
    }

    वापस 0;
}

अटल पूर्णांक qsv_transfer_तथ्य_to(AVHWFramesContext *ctx, AVFrame *dst,
                                स्थिर AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   in = {{ 0 }};
    mfxFrameSurface1 *out = (mfxFrameSurface1*)dst->तथ्य[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = शून्य;
    mfxStatus err;
    पूर्णांक ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    स्थिर AVFrame *src_frame;
    पूर्णांक realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 1);
    अगर (ret < 0)
        वापस ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    अगर (src->height & 15 || src->linesize[0] & 15) {
        realigned = 1;
        अगर (tmp_frame->format != src->format ||
            tmp_frame->width  != FFALIGN(src->width, 16) ||
            tmp_frame->height != FFALIGN(src->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = src->format;
            tmp_frame->width  = FFALIGN(src->width, 16);
            tmp_frame->height = FFALIGN(src->height, 16);
            ret = av_frame_get_बफर(tmp_frame, 0);
            अगर (ret < 0)
                वापस ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        अगर (ret < 0) {
            av_frame_unref(tmp_frame);
            वापस ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        अगर (ret < 0) {
            av_frame_unref(tmp_frame);
            वापस ret;
        }

        tmp_info = out->Info;
        out->Info.CropW = FFMIN(out->Info.Width,  tmp_frame->width);
        out->Info.CropH = FFMIN(out->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    अगर (!s->session_upload) {
        अगर (s->child_frames_ref)
            वापस qsv_transfer_तथ्य_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        वापस AVERROR(ENOSYS);
    }

    in.Info = out->Info;
    map_frame_to_surface(src_frame, &in);

    करो {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_upload, &in, out, शून्य, &sync);
        अगर (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } जबतक (err == MFX_WRN_DEVICE_BUSY);

    अगर (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        वापस AVERROR_UNKNOWN;
    }

    करो {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } जबतक (err == MFX_WRN_IN_EXECUTION);
    अगर (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        वापस AVERROR_UNKNOWN;
    }

    अगर (realigned) {
        out->Info.CropW = tmp_info.CropW;
        out->Info.CropH = tmp_info.CropH;
    }

    वापस 0;
}

अटल पूर्णांक qsv_dynamic_frames_derive_to(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, पूर्णांक flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    चयन (src_ctx->device_ctx->type) {
#अगर CONFIG_VAAPI
    हाल AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        अवरोध;
#पूर्ण_अगर

#अगर CONFIG_D3D11VA
    हाल AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        अगर (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } अन्यथा {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
    अवरोध;
#पूर्ण_अगर

    शेष:
        वापस AVERROR(ENOSYS);
    }

    स_रखो(&mfx_surf1, 0, माप(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    वापस 0;
}

अटल पूर्णांक qsv_fixed_frames_derive_to(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, पूर्णांक flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    पूर्णांक i;

    चयन (src_ctx->device_ctx->type) {
#अगर CONFIG_VAAPI
    हाल AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_आकार,
                                                 माप(*s->handle_pairs_internal));
            अगर (!s->handle_pairs_internal)
                वापस AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             माप(*s->surfaces_internal));
            अगर (!s->surfaces_internal)
                वापस AVERROR(ENOMEM);
            क्रम (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = src_hwctx->surface_ids + i;
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].तथ्य_2.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        अवरोध;
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
    हाल AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_आकार,
                                                 माप(*s->handle_pairs_internal));
            अगर (!s->handle_pairs_internal)
                वापस AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_ctx->initial_pool_आकार,
                                             माप(*s->surfaces_internal));
            अगर (!s->surfaces_internal)
                वापस AVERROR(ENOMEM);
            क्रम (i = 0; i < src_ctx->initial_pool_आकार; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                अगर (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                } अन्यथा {
                    s->handle_pairs_internal[i].second = (mfxMemId)src_hwctx->texture_infos[i].सूचकांक;
                }
                s->surfaces_internal[i].तथ्य_2.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_आकार;
            अगर (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            } अन्यथा {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
            }
        }
        अवरोध;
#पूर्ण_अगर
#अगर CONFIG_DXVA2
    हाल AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_आकार,
                                                 माप(*s->handle_pairs_internal));
            अगर (!s->handle_pairs_internal)
                वापस AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             माप(*s->surfaces_internal));
            अगर (!s->surfaces_internal)
                वापस AVERROR(ENOMEM);
            क्रम (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].तथ्य_2.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            अगर (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            अन्यथा
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        अवरोध;
#पूर्ण_अगर
    शेष:
        वापस AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    वापस 0;
}

अटल पूर्णांक qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, पूर्णांक flags)
{
    अगर (src_ctx->initial_pool_आकार < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        वापस AVERROR(EINVAL);
    } अन्यथा अगर (src_ctx->initial_pool_आकार == 0) {
        वापस qsv_dynamic_frames_derive_to(dst_ctx, src_ctx, flags);
    } अन्यथा {
        वापस qsv_fixed_frames_derive_to(dst_ctx, src_ctx, flags);
    }
}

अटल पूर्णांक qsv_fixed_pool_map_to(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, स्थिर AVFrame *src, पूर्णांक flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    पूर्णांक i, err, सूचकांक = -1;

    क्रम (i = 0; i < hwctx->nb_surfaces && सूचकांक < 0; i++) {
        चयन(src->format) {
#अगर CONFIG_VAAPI
        हाल AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].तथ्य_2.MemId;
            अगर (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->तथ्य[3])
                सूचकांक = i;
            अवरोध;
        }
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
        हाल AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].तथ्य_2.MemId;
            अगर (pair->first == src->तथ्य[0]
                && (pair->second == src->तथ्य[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->तथ्य[1] == (uint8_t *)0)))
                सूचकांक = i;
            अवरोध;
        }
#पूर्ण_अगर
#अगर CONFIG_DXVA2
        हाल AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].तथ्य_2.MemId;
            अगर (pair->first == src->तथ्य[3])
                सूचकांक = i;
            अवरोध;
        }
#पूर्ण_अगर
        }
    }
    अगर (सूचकांक < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        वापस AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, शून्य, शून्य);
    अगर (err)
        वापस err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->तथ्य[3] = (uint8_t*)&hwctx->surfaces[सूचकांक];

    वापस 0;
}

अटल व्योम qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_internal = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_pairs_internal = (mfxHDLPair *)surfaces_internal->तथ्य_2.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_frames->तथ्य;

    चयन (src_ctx->format) {
#अगर CONFIG_VAAPI
    हाल AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_pairs_internal->first);

        अवरोध;
    }
#पूर्ण_अगर

#अगर CONFIG_D3D11VA
    हाल AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        अवरोध;
    }
#पूर्ण_अगर
    शेष:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        अवरोध;
    }

    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
}

अटल पूर्णांक qsv_dynamic_pool_map_to(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, स्थिर AVFrame *src, पूर्णांक flags)
{
    mfxFrameSurface1 *surfaces_internal = शून्य;
    mfxHDLPair *handle_pairs_internal = शून्य;
    पूर्णांक ret = 0;

    surfaces_internal = av_calloc(1, माप(*surfaces_internal));
    अगर (!surfaces_internal) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }

    handle_pairs_internal = av_calloc(1, माप(*handle_pairs_internal));
    अगर (!handle_pairs_internal) {
        ret = AVERROR(ENOMEM);
        जाओ fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_internal);
    अगर (ret < 0)
        जाओ fail;

    चयन (src->format) {
#अगर CONFIG_VAAPI
    हाल AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, माप(*surface_id_internal));
        अगर (!surface_id_internal) {
            ret =AVERROR(ENOMEM);
            जाओ fail;
        }

        *surface_id_internal = (VASurfaceID)(uintptr_t)src->तथ्य[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;

        अवरोध;
    }
#पूर्ण_अगर

#अगर CONFIG_D3D11VA
    हाल AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_frames_ctx->तथ्य;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_pairs_internal->first = (mfxMemId)src->तथ्य[0];

        अगर (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        } अन्यथा {
            handle_pairs_internal->second = (mfxMemId)src->तथ्य[1];
        }

        अवरोध;
    }
#पूर्ण_अगर
    शेष:
        ret = AVERROR(ENOSYS);
        जाओ fail;
    }

    surfaces_internal->तथ्य_2.MemId = (mfxMemId)handle_pairs_internal;

    ret = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_internal);
    अगर (ret)
        जाओ fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->तथ्य[3] = (uint8_t*)surfaces_internal;

    वापस 0;

fail:
    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
    वापस ret;
}

अटल पूर्णांक qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, स्थिर AVFrame *src, पूर्णांक flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    अगर (hwctx->nb_surfaces)
        वापस qsv_fixed_pool_map_to(dst_ctx, dst, src, flags);
    अन्यथा
        वापस qsv_dynamic_pool_map_to(dst_ctx, dst, src, flags);
}

अटल पूर्णांक qsv_frames_get_constraints(AVHWDeviceContext *ctx,
                                      स्थिर व्योम *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    पूर्णांक i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    माप(*constraints->valid_sw_formats));
    अगर (!constraints->valid_sw_formats)
        वापस AVERROR(ENOMEM);

    क्रम (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, माप(*constraints->valid_hw_formats));
    अगर (!constraints->valid_hw_formats)
        वापस AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    वापस 0;
}

अटल व्योम qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    अगर (hwctx->session)
        MFXClose(hwctx->session);

    अगर (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_बफर_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

अटल mfxIMPL choose_implementation(स्थिर अक्षर *device, क्रमागत AVHWDeviceType child_device_type)
{
    अटल स्थिर काष्ठा {
        स्थिर अक्षर *name;
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

    अगर (device) {
        क्रम (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            अगर (!म_भेद(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                अवरोध;
            }
        अगर (i == FF_ARRAY_ELEMS(impl_map))
            impl = म_से_दीर्घ(device, शून्य, 0);
    }

    अगर (impl != MFX_IMPL_SOFTWARE) {
        अगर (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_VIA_D3D11;
        अन्यथा अगर (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_VIA_D3D9;
    }

    वापस impl;
}

अटल पूर्णांक qsv_device_derive_from_child(AVHWDeviceContext *ctx,
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

    चयन (child_device_ctx->type) {
#अगर CONFIG_VAAPI
    हाल AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        अवरोध;
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
    हाल AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        अवरोध;
#पूर्ण_अगर
#अगर CONFIG_DXVA2
    हाल AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        अवरोध;
#पूर्ण_अगर
    शेष:
        ret = AVERROR(ENOSYS);
        जाओ fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    अगर (ret)
        जाओ fail;

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    अगर (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        जाओ fail;
    }

    वापस 0;

fail:
    अगर (hwctx->session)
        MFXClose(hwctx->session);

    अगर (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = शून्य;
    hwctx->loader = शून्य;
    वापस ret;
}

अटल पूर्णांक qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, पूर्णांक flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(माप(*priv));
    अगर (!priv)
        वापस AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->मुक्त = qsv_device_free;

    impl = choose_implementation("hw_any", child_device_ctx->type);
    वापस qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

अटल पूर्णांक qsv_device_create(AVHWDeviceContext *ctx, स्थिर अक्षर *device,
                             AVDictionary *opts, पूर्णांक flags)
{
    QSVDevicePriv *priv;
    क्रमागत AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    पूर्णांक ret;

    priv = av_mallocz(माप(*priv));
    अगर (!priv)
        वापस AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->मुक्त        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", शून्य, 0);
    अगर (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->मूल्य);
        अगर (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->मूल्य);
            वापस AVERROR(EINVAL);
        }
#अगर QSV_ONEVPL
    } अन्यथा अगर (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } अन्यथा अगर (CONFIG_DXVA2) {
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
#अन्यथा
    } अन्यथा अगर (CONFIG_DXVA2) {
        av_log(शून्य, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } अन्यथा अगर (CONFIG_D3D11VA) {
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#पूर्ण_अगर
    } अन्यथा अगर (CONFIG_VAAPI) {
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        वापस AVERROR(ENOSYS);
    }

#अगर CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    अगर (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->मूल्य);
        वापस AVERROR(EINVAL);
    }
#पूर्ण_अगर

    child_device_opts = शून्य;
    चयन (child_device_type) {
#अगर CONFIG_VAAPI
    हाल AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_set(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_set(&child_device_opts, "driver",    "iHD",    0);
        }
        अवरोध;
#पूर्ण_अगर
#अगर CONFIG_D3D11VA
    हाल AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_set(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        अवरोध;
#पूर्ण_अगर
#अगर CONFIG_DXVA2
    हाल AV_HWDEVICE_TYPE_DXVA2:
#अगर QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#पूर्ण_अगर
        अवरोध;
#पूर्ण_अगर
    शेष:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            वापस AVERROR(ENOSYS);
        }
        अवरोध;
    }

    e = av_dict_get(opts, "child_device", शून्य, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->मूल्य : शून्य, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    अगर (ret < 0)
        वापस ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->तथ्य;

    impl = choose_implementation(device, child_device_type);

    वापस qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

स्थिर HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_आकार      = माप(QSVDeviceContext),
    .frames_hwctx_आकार      = माप(QSVFramesContext),

    .device_create          = qsv_device_create,
    .device_derive          = qsv_device_derive,
    .device_init            = qsv_device_init,
    .frames_get_constraints = qsv_frames_get_constraints,
    .frames_init            = qsv_frames_init,
    .frames_uninit          = qsv_frames_uninit,
    .frames_get_बफर      = qsv_get_बफर,
    .transfer_get_formats   = qsv_transfer_get_formats,
    .transfer_तथ्य_to       = qsv_transfer_तथ्य_to,
    .transfer_तथ्य_from     = qsv_transfer_तथ्य_from,
    .map_to                 = qsv_map_to,
    .map_from               = qsv_map_from,
    .frames_derive_to       = qsv_frames_derive_to,
    .frames_derive_from     = qsv_frames_derive_from,

    .pix_fmts = (स्थिर क्रमागत AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
