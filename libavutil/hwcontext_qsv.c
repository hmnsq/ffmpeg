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

#অন্তর্ভাব <stdatomic.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব <mfxvideo.h>

#অন্তর্ভাব "config.h"

#যদি HAVE_PTHREADS
#অন্তর্ভাব <pthread.h>
#endif

#define COBJMACROS
#যদি CONFIG_VAAPI
#অন্তর্ভাব "hwcontext_vaapi.h"
#endif
#যদি CONFIG_D3D11VA
#অন্তর্ভাব "hwcontext_d3d11va.h"
#endif
#যদি CONFIG_DXVA2
#অন্তর্ভাব <initguid.h>
#অন্তর্ভাব "hwcontext_dxva2.h"
#endif

#অন্তর্ভাব "buffer.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "hwcontext.h"
#অন্তর্ভাব "hwcontext_internal.h"
#অন্তর্ভাব "hwcontext_qsv.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "pixfmt.h"
#অন্তর্ভাব "pixdesc.h"
#অন্তর্ভাব "time.h"
#অন্তর্ভাব "imgutils.h"
#অন্তর্ভাব "avassert.h"

#define QSV_VERSION_ATLEAST(MAJOR, MINOR)   \
    (MFX_VERSION_MAJOR > (MAJOR) ||         \
     MFX_VERSION_MAJOR == (MAJOR) && MFX_VERSION_MINOR >= (MINOR))

#define QSV_RUNTIME_VERSION_ATLEAST(MFX_VERSION, MAJOR, MINOR)          \
    ((MFX_VERSION.Major > (MAJOR)) ||                                   \
     (MFX_VERSION.Major == (MAJOR) && MFX_VERSION.Minor >= (MINOR)))

#define MFX_IMPL_VIA_MASK(impl) (0x0f00 & (impl))
#define QSV_ONEVPL       QSV_VERSION_ATLEAST(2, 0)
#define QSV_HAVE_OPAQUE  !QSV_ONEVPL

#যদি QSV_ONEVPL
#অন্তর্ভাব <mfxdispatcher.h>
#অন্যথা
#define MFXUnload(a) কুরু { } যাবত্(0)
#endif

প্রকারনির্দেশ সংরচনা QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

প্রকারনির্দেশ সংরচনা QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfxVersion          ver;
    mfxIMPL             impl;

    গণনা AVHWDeviceType child_device_type;
    গণনা AVPixelFormat  child_pix_fmt;
} QSVDeviceContext;

প্রকারনির্দেশ সংরচনা QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#যদি HAVE_PTHREADS
    pthread_mutex_t session_lock;
#endif

    AVBufferRef *child_frames_ref;
    mfxFrameSurface1 *surfaces_internal;
    mfxHDLPair *handle_pairs_internal;
    পূর্ণাঙ্ক             nb_surfaces_used;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#যদি QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfxExtBuffer *ext_buffers[1];
#endif
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

প্রকারনির্দেশ সংরচনা QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

স্থির ধ্রুব সংরচনা {
    গণনা AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_shift;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#যদি CONFIG_VAAPI
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
#যদি QSV_VERSION_ATLEAST(1, 31)
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

বাহ্য পূর্ণাঙ্ক ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          গণনা AVHWDeviceType base_dev_type,
                                          শূন্য **base_handle);

স্থির পূর্ণাঙ্ক qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
পূর্ণাঙ্ক ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                   গণনা AVHWDeviceType base_dev_type,
                                   শূন্য **base_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->Data.MemId;
    বিকল্প (base_dev_type) {
#যদি CONFIG_VAAPI
    পক্ষ AV_HWDEVICE_TYPE_VAAPI:
        base_handle[0] = handle_pair->first;
        প্রত্যাগম 0;
#endif
#যদি CONFIG_D3D11VA
    পক্ষ AV_HWDEVICE_TYPE_D3D11VA:
        base_handle[0] = handle_pair->first;
        base_handle[1] = handle_pair->second;
        প্রত্যাগম 0;
#endif
#যদি CONFIG_DXVA2
    পক্ষ AV_HWDEVICE_TYPE_DXVA2:
        base_handle[0] = handle_pair->first;
        প্রত্যাগম 0;
#endif
    }
    প্রত্যাগম AVERROR(EINVAL);
}

স্থির uint32_t qsv_fourcc_from_pix_fmt(গণনা AVPixelFormat pix_fmt)
{
    পূর্ণাঙ্ক i;
    প্রতি (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        যদি (supported_pixel_formats[i].pix_fmt == pix_fmt)
            প্রত্যাগম supported_pixel_formats[i].fourcc;
    }
    প্রত্যাগম 0;
}

স্থির uint16_t qsv_shift_from_pix_fmt(গণনা AVPixelFormat pix_fmt)
{
    প্রতি (পূর্ণাঙ্ক i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        যদি (supported_pixel_formats[i].pix_fmt == pix_fmt)
            প্রত্যাগম supported_pixel_formats[i].mfx_shift;
    }

    প্রত্যাগম 0;
}

#যদি CONFIG_D3D11VA
স্থির uint32_t qsv_get_d3d11va_bind_flags(পূর্ণাঙ্ক mem_type)
{
    uint32_t bind_flags = 0;

    যদি ((mem_type & MFX_MEMTYPE_VIDEO_MEMORY_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_INTERNAL_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    অন্যথা
        bind_flags = D3D11_BIND_DECODER;

    যদি ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    প্রত্যাগম bind_flags;
}
#endif

স্থির পূর্ণাঙ্ক qsv_fill_border(AVFrame *dst, ধ্রুব AVFrame *src)
{
    ধ্রুব AVPixFmtDescriptor *desc;
    পূর্ণাঙ্ক i, planes_nb = 0;
    যদি (dst->format != src->format)
        প্রত্যাগম AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    প্রতি (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    প্রতি (i = 0; i < planes_nb; i++) {
        পূর্ণাঙ্ক sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->width,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->width,
                                                 i);
        ধ্রুব AVComponentDescriptor comp = desc->comp[i];
        যদি (swidth < 0 || dwidth < 0) {
            av_log(রিক্ত, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            প্রত্যাগম AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        যদি (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        প্রতি (y = 0; y < sheight; y++) {
            শূন্য *সারি_ptr = dst->data[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(সারি_ptr,
                           comp.depth > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        প্রতি (y = sheight; y < dheight; y++) {
            memcpy(dst->data[i]+y*dst->linesize[i],
                   dst->data[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    পূর্ণাঙ্ক   hw_handle_supported = 0;
    mfxHandleType handle_type;
    গণনা AVHWDeviceType device_type;
    গণনা AVPixelFormat  pix_fmt;
    mfxStatus err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    যদি (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    যদি (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    যদি (MFX_IMPL_VIA_VAAPI == MFX_IMPL_VIA_MASK(s->impl)) {
#যদি CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#endif
    } অন্যথা যদি (MFX_IMPL_VIA_D3D11 == MFX_IMPL_VIA_MASK(s->impl)) {
#যদি CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#endif
    } অন্যথা যদি (MFX_IMPL_VIA_D3D9 == MFX_IMPL_VIA_MASK(s->impl)) {
#যদি CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#endif
    }

    যদি (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        যদি (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->child_device_type = device_type;
            s->child_pix_fmt     = pix_fmt;
        }
    }
    যদি (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    প্রত্যাগম 0;
}

স্থির শূন্য qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    যদি (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = রিক্ত;
    s->session_download_init = 0;

    যদি (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = রিক্ত;
    s->session_upload_init = 0;

#যদি HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_lock);
#endif

    av_freep(&s->mem_ids);
#যদি QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#endif
    av_freep(&s->surfaces_internal);
    av_freep(&s->handle_pairs_internal);
    av_frame_unref(&s->realigned_upload_frame);
    av_frame_unref(&s->realigned_download_frame);
    av_buffer_unref(&s->child_frames_ref);
}

স্থির শূন্য qsv_pool_release_dummy(শূন্য *opaque, uint8_t *data)
{
}

স্থির শূন্য qsv_pool_release(শূন্য *opaque, uint8_t *data)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)data;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.Data.MemId;
    AVHWFramesContext *child_frames_ctx;

    যদি (!s->child_frames_ref)
        প্রত্যাগম;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    যদি (!child_frames_ctx->device_ctx)
        প্রত্যাগম;

#যদি CONFIG_VAAPI
    যদি (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#endif

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

স্থির AVBufferRef *qsv_fixed_pool_alloc(শূন্য *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    যদি (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        প্রত্যাগম av_buffer_create((uint8_t*)(s->surfaces_internal + s->nb_surfaces_used - 1),
                                পরিমাণ(*hwctx->surfaces), qsv_pool_release_dummy, রিক্ত, 0);
    }

    প্রত্যাগম রিক্ত;
}

স্থির AVBufferRef *qsv_dynamic_pool_alloc(শূন্য *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx;
    QSVSurface *qsv_surface = রিক্ত;
    mfxHDLPair *handle_pairs_internal = রিক্ত;
    পূর্ণাঙ্ক ret;

    যদি (!s->child_frames_ref)
        গচ্ছ fail;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    যদি (!child_frames_ctx->device_ctx)
        গচ্ছ fail;

#যদি CONFIG_DXVA2
    যদি (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        গচ্ছ fail;
    }
#endif

    qsv_surface = av_calloc(1, পরিমাণ(*qsv_surface));
    যদি (!qsv_surface)
        গচ্ছ fail;

    qsv_surface->child_frame = av_frame_alloc();
    যদি (!qsv_surface->child_frame)
        গচ্ছ fail;

    ret = av_hwframe_get_buffer(s->child_frames_ref, qsv_surface->child_frame, 0);
    যদি (ret < 0)
        গচ্ছ fail;

    handle_pairs_internal = av_calloc(1, পরিমাণ(*handle_pairs_internal));
    যদি (!handle_pairs_internal)
        গচ্ছ fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    যদি (ret < 0)
        গচ্ছ fail;

#যদি CONFIG_VAAPI
    যদি (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, পরিমাণ(*surface_id_internal));
        যদি (!surface_id_internal)
            গচ্ছ fail;

        *surface_id_internal = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
    }
#endif

#যদি CONFIG_D3D11VA
    যদি (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        handle_pairs_internal->first = (mfxMemId)qsv_surface->child_frame->data[0];

        যদি (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        অন্যথা
            handle_pairs_internal->second = (mfxMemId)qsv_surface->child_frame->data[1];

    }
#endif

    qsv_surface->mfx_surface.Data.MemId = (mfxMemId)handle_pairs_internal;
    প্রত্যাগম av_buffer_create((uint8_t *)qsv_surface, পরিমাণ(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    যদি (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_pairs_internal);

    প্রত্যাগম রিক্ত;
}

স্থির AVBufferRef *qsv_pool_alloc(শূন্য *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    যদি (hwctx->nb_surfaces == 0) {
        প্রত্যাগম qsv_dynamic_pool_alloc(opaque, size);
    } অন্যথা {
        প্রত্যাগম qsv_fixed_pool_alloc(opaque, size);
    }
}

স্থির পূর্ণাঙ্ক qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = রিক্ত;
    AVBufferRef *child_frames_ref = রিক্ত;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    পূর্ণাঙ্ক i, ret = 0;

    যদি (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        প্রত্যাগম AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    যদি (!child_device_ref)
        প্রত্যাগম AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->data;

#যদি CONFIG_VAAPI
    যদি (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#endif
#যদি CONFIG_D3D11VA
    যদি (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        ID3D11Device_AddRef((ID3D11Device*)device_priv->handle);
        child_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#endif
#যদি CONFIG_DXVA2
    যদি (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#endif

    ret = av_hwdevice_ctx_init(child_device_ref);
    যদি (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        গচ্ছ fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    যদি (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->data;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_size = ctx->initial_pool_size;
    child_frames_ctx->width             = FFALIGN(ctx->width, 16);
    child_frames_ctx->height            = FFALIGN(ctx->height, 16);

#যদি CONFIG_D3D11VA
    যদি (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        যদি (hwctx->frame_type == 0)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        যদি (hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
            child_frames_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        child_frames_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->frame_type);
    }
#endif
#যদি CONFIG_DXVA2
    যদি (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        যদি (hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET)
            child_frames_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        অন্যথা
            child_frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#endif

    ret = av_hwframe_ctx_init(child_frames_ref);
    যদি (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        গচ্ছ fail;
    }

#যদি CONFIG_VAAPI
    যদি (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        প্রতি (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = child_frames_hwctx->surface_ids + i;
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif
#যদি CONFIG_D3D11VA
    যদি (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        প্রতি (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->texture_infos[i].texture;
            যদি(child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            } অন্যথা {
                s->handle_pairs_internal[i].second = (mfxMemId)child_frames_hwctx->texture_infos[i].index;
            }
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        যদি (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } অন্যথা {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
#endif
#যদি CONFIG_DXVA2
    যদি (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        প্রতি (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->surfaces[i];
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        যদি (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        অন্যথা
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = রিক্ত;

fail:
    av_buffer_unref(&child_device_ref);
    av_buffer_unref(&child_frames_ref);
    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    ধ্রুব AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    যদি (!desc)
        প্রত্যাগম AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    যদি (!fourcc)
        প্রত্যাগম AVERROR(EINVAL);

    surf->Info.BitDepthLuma   = desc->comp[0].depth;
    surf->Info.BitDepthChroma = desc->comp[0].depth;
    surf->Info.Shift          = qsv_shift_from_pix_fmt(ctx->sw_format);

    যদি (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    অন্যথা যদি (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    অন্যথা
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.Width          = FFALIGN(ctx->width, 16);
    surf->Info.CropW          = ctx->width;
    surf->Info.Height         = FFALIGN(ctx->height, 16);
    surf->Info.CropH          = ctx->height;
    surf->Info.FrameRateExtN  = 25;
    surf->Info.FrameRateExtD  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    পূর্ণাঙ্ক i, ret = 0;

    যদি (ctx->initial_pool_size < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        প্রত্যাগম AVERROR(EINVAL);
    } অন্যথা যদি (ctx->initial_pool_size == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        যদি (ret < 0)
            প্রত্যাগম ret;

        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(পরিমাণ(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, রিক্ত);
        যদি (!ffhwframesctx(ctx)->pool_internal)
            প্রত্যাগম AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, পরিমাণ(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        frames_hwctx->info = &s->frame_info;
        frames_hwctx->nb_surfaces = 0;

        প্রত্যাগম 0;
    }

    s->handle_pairs_internal = av_calloc(ctx->initial_pool_size,
                                         পরিমাণ(*s->handle_pairs_internal));
    যদি (!s->handle_pairs_internal)
        প্রত্যাগম AVERROR(ENOMEM);

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     পরিমাণ(*s->surfaces_internal));
    যদি (!s->surfaces_internal)
        প্রত্যাগম AVERROR(ENOMEM);

    প্রতি (i = 0; i < ctx->initial_pool_size; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_internal[i]);
        যদি (ret < 0)
            প্রত্যাগম ret;
    }

#যদি QSV_HAVE_OPAQUE
    যদি (!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        যদি (ret < 0)
            প্রত্যাগম ret;
    }
#অন্যথা
    ret = qsv_init_child_ctx(ctx);
    যদি (ret < 0)
        প্রত্যাগম ret;
#endif

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(পরিমাণ(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, রিক্ত);
    যদি (!ffhwframesctx(ctx)->pool_internal)
        প্রত্যাগম AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    প্রত্যাগম 0;
}

স্থির mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    যদি (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        প্রত্যাগম MFX_ERR_UNSUPPORTED;
    যদি (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        প্রত্যাগম MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->অঙ্ক_Frame_Actual = hwctx->nb_surfaces;

    প্রত্যাগম MFX_ERR_NONE;
}

স্থির mfxStatus frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    প্রত্যাগম MFX_ERR_NONE;
}

স্থির mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    প্রত্যাগম MFX_ERR_UNSUPPORTED;
}

স্থির mfxStatus frame_unlock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    প্রত্যাগম MFX_ERR_UNSUPPORTED;
}

স্থির mfxStatus frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    যদি (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    প্রত্যাগম MFX_ERR_NONE;
}

#যদি QSV_ONEVPL

স্থির পূর্ণাঙ্ক qsv_d3d11_update_config(শূন্য *ctx, mfxHDL handle, mfxConfig cfg)
{
    পূর্ণাঙ্ক ret = AVERROR_UNKNOWN;
#যদি CONFIG_D3D11VA
    mfxStatus sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = রিক্ত;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_মান = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (শূন্য**)&pDXGIDevice);
    যদি (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        যদি (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            প্রত্যাগম ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        যদি (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            গচ্ছ fail;
        }
    } অন্যথা {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        প্রত্যাগম ret;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_U16;
    impl_মান.Data.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুব mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        গচ্ছ fail;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_PTR;
    impl_মান.Data.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুব mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        গচ্ছ fail;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_U32;
    impl_মান.Data.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুব mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        গচ্ছ fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#endif
    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক qsv_d3d9_update_config(শূন্য *ctx, mfxHDL handle, mfxConfig cfg)
{
    পূর্ণাঙ্ক ret = AVERROR_UNKNOWN;
#যদি CONFIG_DXVA2
    mfxStatus sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = রিক্ত;
    IDirect3DDevice9Ex *device_ex = রিক্ত;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = রিক্ত;
    IDirect3D9 *d3d9 = রিক্ত;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_মান = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        গচ্ছ fail;
    }

    hr = IDirect3DDeviceManager9_LockDevice(devmgr, device_handle, &device, TRUE);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        গচ্ছ fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (শূন্য **)&device_ex);
    IDirect3DDevice9_Release(device);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        গচ্ছ unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        গচ্ছ unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        গচ্ছ unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (শূন্য **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        গচ্ছ unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        গচ্ছ release;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_PTR;
    impl_মান.Data.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুব mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        গচ্ছ release;
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
    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক qsv_va_update_config(শূন্য *ctx, mfxHDL handle, mfxConfig cfg)
{
#যদি CONFIG_VAAPI
#যদি VA_CHECK_VERSION(1, 15, 0)
    mfxStatus sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_মান = {0};

    vas = vaGetDisplayAttributes(dpy, &attr, 1);
    যদি (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_মান.Type = MFX_VARIANT_TYPE_U16;
        impl_মান.Data.U16 = (attr.মান & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ধ্রুব mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_মান);
        যদি (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            গচ্ছ fail;
        }
    } অন্যথা {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        গচ্ছ fail;
    }

    প্রত্যাগম 0;

fail:
#অন্যথা
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#endif
#endif
    প্রত্যাগম AVERROR_UNKNOWN;
}

স্থির পূর্ণাঙ্ক qsv_new_mfx_loader(শূন্য *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfxVersion *pver,
                              শূন্য **ploader)
{
    mfxStatus sts;
    mfxLoader loader = রিক্ত;
    mfxConfig cfg;
    mfxVariant impl_মান = {0};

    *ploader = রিক্ত;
    loader = MFXLoad();
    যদি (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        গচ্ছ fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    যদি (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        গচ্ছ fail;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_U32;
    impl_মান.Data.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুব mfxU8 *)"mfxImplDescription.Impl", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        গচ্ছ fail;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_U32;
    impl_মান.Data.U32 = pver->Version;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুব mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        গচ্ছ fail;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_U32;
    impl_মান.Data.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুব mfxU8 *)"mfxImplDescription.VendorID", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        গচ্ছ fail;
    }

    যদি (MFX_HANDLE_VA_DISPLAY == handle_type) {
        যদি (handle && qsv_va_update_config(ctx, handle, cfg))
            গচ্ছ fail;

        impl_মান.Data.U32 = MFX_ACCEL_MODE_VIA_VAAPI;
    } অন্যথা যদি (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        যদি (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            গচ্ছ fail;

        impl_মান.Data.U32 = MFX_ACCEL_MODE_VIA_D3D9;
    } অন্যথা {
        যদি (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            গচ্ছ fail;

        impl_মান.Data.U32 = MFX_ACCEL_MODE_VIA_D3D11;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুব mfxU8 *)"mfxImplDescription.AccelerationMode", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        গচ্ছ fail;
    }

    *ploader = loader;

    প্রত্যাগম 0;

fail:
    যদি (loader)
        MFXUnload(loader);

    প্রত্যাগম AVERROR_UNKNOWN;
}

স্থির পূর্ণাঙ্ক qsv_create_mfx_session_from_loader(শূন্য *ctx, mfxLoader loader, mfxSession *psession)
{
    mfxStatus sts;
    mfxSession session = রিক্ত;
    uint32_t impl_idx = 0;
    mfxVersion ver;

    যাবত্ (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        যদি (sts == MFX_ERR_NOT_FOUND)
            ভঙ্গ;
        অন্যথা যদি (sts != MFX_ERR_NONE) {
            impl_idx++;
            অনুবর্ত;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        যদি (sts == MFX_ERR_NONE)
            ভঙ্গ;

        impl_idx++;
    }

    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        গচ্ছ fail;
    }

    sts = MFXQueryVersion(session, &ver);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        গচ্ছ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    প্রত্যাগম 0;

fail:
    যদি (session)
        MFXClose(session);

    প্রত্যাগম AVERROR_UNKNOWN;
}

স্থির পূর্ণাঙ্ক qsv_create_mfx_session(শূন্য *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  শূন্য **ploader)
{
    mfxLoader loader = রিক্ত;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    যদি (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        প্রত্যাগম AVERROR(EXDEV);
    }

    *psession = রিক্ত;

    যদি (!*ploader) {
        যদি (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (শূন্য **)&loader))
            গচ্ছ fail;

        av_assert0(loader);
    } অন্যথা
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    যদি (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        গচ্ছ fail;

    যদি (!*ploader)
        *ploader = loader;

    প্রত্যাগম 0;

fail:
    যদি (!*ploader && loader)
        MFXUnload(loader);

    প্রত্যাগম AVERROR_UNKNOWN;
}

#অন্যথা

স্থির পূর্ণাঙ্ক qsv_create_mfx_session(শূন্য *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  শূন্য **ploader)
{
    mfxVersion ver;
    mfxStatus sts;
    mfxSession session = রিক্ত;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    *ploader = রিক্ত;
    *psession = রিক্ত;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        গচ্ছ fail;
    }

    sts = MFXQueryVersion(session, &ver);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        গচ্ছ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        গচ্ছ fail;
    }

    *psession = session;

    প্রত্যাগম 0;

fail:
    যদি (session)
        MFXClose(session);

    প্রত্যাগম AVERROR_UNKNOWN;
}

#endif

স্থির পূর্ণাঙ্ক qsv_init_internal_session(AVHWFramesContext *ctx,
                                     mfxSession *session, পূর্ণাঙ্ক upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    পূর্ণাঙ্ক opaque = 0;

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
    পূর্ণাঙ্ক                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    শূন্য             **loader = &hwctx->loader;
    mfxSession parent_session = hwctx->session;
    mfxIMPL impl;
    mfxVersion ver;

    err = MFXQueryIMPL(parent_session, &impl);
    যদি (err == MFX_ERR_NONE)
        err = MFXQueryVersion(parent_session, &ver);
    যদি (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        প্রত্যাগম AVERROR_UNKNOWN;
    }

#যদি QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    যদি (ret)
        গচ্ছ fail;

    যদি (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        যদি (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            গচ্ছ fail;
        }
    }

    যদি (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        যদি (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            গচ্ছ fail;
        }
    }

    যদি (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        যদি (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            গচ্ছ fail;
        }
    }

    memset(&par, 0, পরিমাণ(par));

    যদি (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_OUT_VIDEO_MEMORY :
                                 MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
#যদি QSV_HAVE_OPAQUE
    অন্যথা {
        par.ExtParam    = s->ext_buffers;
        par.অঙ্ক_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
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
    যদি (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        গচ্ছ fail;
    }

    প্রত্যাগম 0;

fail:
    যদি (*session)
        MFXClose(*session);

    *session = রিক্ত;

    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    পূর্ণাঙ্ক opaque = 0;

    uint32_t fourcc;
    পূর্ণাঙ্ক i, ret;

#যদি QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    যদি (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        প্রত্যাগম AVERROR(ENOSYS);
    }

    যদি (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        যদি (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            প্রত্যাগম ret;
        }
    }

    যদি (!opaque) {
        s->mem_ids = av_calloc(frames_hwctx->nb_surfaces, পরিমাণ(*s->mem_ids));
        যদি (!s->mem_ids)
            প্রত্যাগম AVERROR(ENOMEM);

        প্রতি (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].Data.MemId;
    }
#যদি QSV_HAVE_OPAQUE
    অন্যথা {
        s->surface_ptrs = av_calloc(frames_hwctx->nb_surfaces,
                                    পরিমাণ(*s->surface_ptrs));
        যদি (!s->surface_ptrs)
            প্রত্যাগম AVERROR(ENOMEM);

        প্রতি (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.অঙ্ক_Surface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = পরিমাণ(s->opaque_alloc);

        s->ext_buffers[0] = (mfxExtBuffer*)&s->opaque_alloc;
    }
#endif

    s->session_download = রিক্ত;
    s->session_upload   = রিক্ত;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#যদি HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, রিক্ত);
#endif

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক qsv_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    যদি (!frame->buf[0])
        প্রত্যাগম AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_QSV;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    গণনা AVHWFrameTransferDirection dir,
                                    গণনা AVPixelFormat **formats)
{
    গণনা AVPixelFormat *fmts;

    fmts = av_malloc_array(2, পরিমাণ(*fmts));
    যদি (!fmts)
        প্রত্যাগম AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, পূর্ণাঙ্ক flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    পূর্ণাঙ্ক i;

    বিকল্প (dst_ctx->device_ctx->type) {
#যদি CONFIG_VAAPI
    পক্ষ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               পরিমাণ(*dst_hwctx->surface_ids));
            যদি (!dst_hwctx->surface_ids)
                প্রত্যাগম AVERROR(ENOMEM);
            প্রতি (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        ভঙ্গ;
#endif
#যদি CONFIG_D3D11VA
    পক্ষ AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_size = src_ctx->initial_pool_size;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 পরিমাণ(*dst_hwctx->texture_infos));
            যদি (!dst_hwctx->texture_infos)
                প্রত্যাগম AVERROR(ENOMEM);
            যদি (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            প্রতি (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].index = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            যদি (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } অন্যথা
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        ভঙ্গ;
#endif
#যদি CONFIG_DXVA2
    পক্ষ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            পরিমাণ(*dst_hwctx->surfaces));
            যদি (!dst_hwctx->surfaces)
                প্রত্যাগম AVERROR(ENOMEM);
            প্রতি (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            যদি (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            অন্যথা
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        ভঙ্গ;
#endif
    স্বভাব:
        প্রত্যাগম AVERROR(ENOSYS);
    }

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->data[3];
    AVHWFramesContext *child_frames_ctx;
    ধ্রুব AVPixFmtDescriptor *desc;
    uint8_t *child_data;
    AVFrame *dummy;
    পূর্ণাঙ্ক ret = 0;

    যদি (!s->child_frames_ref)
        প্রত্যাগম AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;

    বিকল্প (child_frames_ctx->device_ctx->type) {
#যদি CONFIG_VAAPI
    পক্ষ AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_data = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        ভঙ্গ;
    }
#endif
#যদি CONFIG_D3D11VA
    পক্ষ AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        ভঙ্গ;
    }
#endif
#যদি CONFIG_DXVA2
    পক্ষ AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        ভঙ্গ;
    }
#endif
    স্বভাব:
        প্রত্যাগম AVERROR(ENOSYS);
    }

    যদি (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, রিক্ত, রিক্ত);
        যদি (ret < 0)
            প্রত্যাগম ret;

        dst->width   = src->width;
        dst->height  = src->height;

       যদি (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
            dst->data[0] = pair->first;
            dst->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } অন্যথা {
            dst->data[3] = child_data;
        }

        প্রত্যাগম 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    যদি (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        প্রত্যাগম AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    যদি (!dummy)
        প্রত্যাগম AVERROR(ENOMEM);

    dummy->buf[0]        = av_buffer_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_buffer_ref(s->child_frames_ref);
    যদি (!dummy->buf[0] || !dummy->hw_frames_ctx)
        গচ্ছ fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;

    যদি (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        dummy->data[0] = pair->first;
        dummy->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } অন্যথা {
        dummy->data[3] = child_data;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক qsv_transfer_data_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   ধ্রুব AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    পূর্ণাঙ্ক download = !!src->hw_frames_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->data[3] : dst->data[3]);

    AVFrame *dummy;
    পূর্ণাঙ্ক ret;

    dummy = av_frame_alloc();
    যদি (!dummy)
        প্রত্যাগম AVERROR(ENOMEM);

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->data[3]       = surf->Data.MemId;
    dummy->hw_frames_ctx = s->child_frames_ref;

    ret = download ? av_hwframe_transfer_data(dst, dummy, 0) :
                     av_hwframe_transfer_data(dummy, src, 0);

    dummy->buf[0]        = রিক্ত;
    dummy->data[3]       = রিক্ত;
    dummy->hw_frames_ctx = রিক্ত;

    av_frame_free(&dummy);

    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক map_frame_to_surface(ধ্রুব AVFrame *frame, mfxFrameSurface1 *surface)
{
    বিকল্প (frame->format) {
    পক্ষ AV_PIX_FMT_NV12:
    পক্ষ AV_PIX_FMT_P010:
    পক্ষ AV_PIX_FMT_P012:
        surface->Data.Y  = frame->data[0];
        surface->Data.UV = frame->data[1];
        ভঙ্গ;

    পক্ষ AV_PIX_FMT_YUV420P:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[1];
        surface->Data.V = frame->data[2];
        ভঙ্গ;

    পক্ষ AV_PIX_FMT_BGRA:
        surface->Data.B = frame->data[0];
        surface->Data.G = frame->data[0] + 1;
        surface->Data.R = frame->data[0] + 2;
        surface->Data.A = frame->data[0] + 3;
        ভঙ্গ;
    পক্ষ AV_PIX_FMT_YUYV422:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.V = frame->data[0] + 3;
        ভঙ্গ;

    পক্ষ AV_PIX_FMT_Y210:
    পক্ষ AV_PIX_FMT_Y212:
        surface->Data.Y16 = (mfxU16 *)frame->data[0];
        surface->Data.U16 = (mfxU16 *)frame->data[0] + 1;
        surface->Data.V16 = (mfxU16 *)frame->data[0] + 3;
        ভঙ্গ;
    পক্ষ AV_PIX_FMT_VUYX:
        surface->Data.V = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.Y = frame->data[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 3;
        ভঙ্গ;
    পক্ষ AV_PIX_FMT_XV30:
        surface->Data.U = frame->data[0];
        ভঙ্গ;
    পক্ষ AV_PIX_FMT_XV36:
        surface->Data.U = frame->data[0];
        surface->Data.Y = frame->data[0] + 2;
        surface->Data.V = frame->data[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 6;
        ভঙ্গ;
#যদি CONFIG_VAAPI
    পক্ষ AV_PIX_FMT_UYVY422:
        surface->Data.Y = frame->data[0] + 1;
        surface->Data.U = frame->data[0];
        surface->Data.V = frame->data[0] + 2;
        ভঙ্গ;
#endif
    স্বভাব:
        প্রত্যাগম MFX_ERR_UNSUPPORTED;
    }
    surface->Data.Pitch     = frame->linesize[0];
    surface->Data.TimeStamp = frame->pts;

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক qsv_internal_session_check_init(AVHWFramesContext *ctx, পূর্ণাঙ্ক upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    পূর্ণাঙ্ক ret = 0;

    যদি (atomic_load(inited))
        প্রত্যাগম 0;

#যদি HAVE_PTHREADS
    pthread_mutex_lock(&s->session_lock);
#endif

    যদি (!atomic_load(inited)) {
        ret = qsv_init_internal_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#যদি HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_lock);
#endif

    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক qsv_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ধ্রুব AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->data[3];

    mfxSyncPoint sync = রিক্ত;
    mfxStatus err;
    পূর্ণাঙ্ক ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    পূর্ণাঙ্ক realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 0);
    যদি (ret < 0)
        প্রত্যাগম ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    যদি (dst->height & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        যদি (tmp_frame->format != dst->format ||
            tmp_frame->width  != FFALIGN(dst->linesize[0], 16) ||
            tmp_frame->height != FFALIGN(dst->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = dst->format;
            tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
            tmp_frame->height = FFALIGN(dst->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            যদি (ret < 0)
                প্রত্যাগম ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    যদি (!s->session_download) {
        যদি (s->child_frames_ref)
            প্রত্যাগম qsv_transfer_data_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        প্রত্যাগম AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst_frame, &out);

    কুরু {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, রিক্ত, &sync);
        যদি (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } যাবত্ (err == MFX_WRN_DEVICE_BUSY);

    যদি (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    কুরু {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } যাবত্ (err == MFX_WRN_IN_EXECUTION);
    যদি (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    যদি (realigned) {
        tmp_frame->width  = dst->width;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        যদি (ret < 0)
            প্রত্যাগম ret;
    }

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক qsv_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                ধ্রুব AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   in = {{ 0 }};
    mfxFrameSurface1 *out = (mfxFrameSurface1*)dst->data[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = রিক্ত;
    mfxStatus err;
    পূর্ণাঙ্ক ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    ধ্রুব AVFrame *src_frame;
    পূর্ণাঙ্ক realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 1);
    যদি (ret < 0)
        প্রত্যাগম ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    যদি (src->height & 15 || src->linesize[0] & 15) {
        realigned = 1;
        যদি (tmp_frame->format != src->format ||
            tmp_frame->width  != FFALIGN(src->width, 16) ||
            tmp_frame->height != FFALIGN(src->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = src->format;
            tmp_frame->width  = FFALIGN(src->width, 16);
            tmp_frame->height = FFALIGN(src->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            যদি (ret < 0)
                প্রত্যাগম ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        যদি (ret < 0) {
            av_frame_unref(tmp_frame);
            প্রত্যাগম ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        যদি (ret < 0) {
            av_frame_unref(tmp_frame);
            প্রত্যাগম ret;
        }

        tmp_info = out->Info;
        out->Info.CropW = FFMIN(out->Info.Width,  tmp_frame->width);
        out->Info.CropH = FFMIN(out->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    যদি (!s->session_upload) {
        যদি (s->child_frames_ref)
            প্রত্যাগম qsv_transfer_data_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        প্রত্যাগম AVERROR(ENOSYS);
    }

    in.Info = out->Info;
    map_frame_to_surface(src_frame, &in);

    কুরু {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_upload, &in, out, রিক্ত, &sync);
        যদি (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } যাবত্ (err == MFX_WRN_DEVICE_BUSY);

    যদি (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    কুরু {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } যাবত্ (err == MFX_WRN_IN_EXECUTION);
    যদি (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        প্রত্যাগম AVERROR_UNKNOWN;
    }

    যদি (realigned) {
        out->Info.CropW = tmp_info.CropW;
        out->Info.CropH = tmp_info.CropH;
    }

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক qsv_dynamic_frames_derive_to(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, পূর্ণাঙ্ক flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    বিকল্প (src_ctx->device_ctx->type) {
#যদি CONFIG_VAAPI
    পক্ষ AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        ভঙ্গ;
#endif

#যদি CONFIG_D3D11VA
    পক্ষ AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        যদি (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } অন্যথা {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
    ভঙ্গ;
#endif

    স্বভাব:
        প্রত্যাগম AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, পরিমাণ(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক qsv_fixed_frames_derive_to(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, পূর্ণাঙ্ক flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    পূর্ণাঙ্ক i;

    বিকল্প (src_ctx->device_ctx->type) {
#যদি CONFIG_VAAPI
    পক্ষ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 পরিমাণ(*s->handle_pairs_internal));
            যদি (!s->handle_pairs_internal)
                প্রত্যাগম AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             পরিমাণ(*s->surfaces_internal));
            যদি (!s->surfaces_internal)
                প্রত্যাগম AVERROR(ENOMEM);
            প্রতি (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = src_hwctx->surface_ids + i;
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        ভঙ্গ;
#endif
#যদি CONFIG_D3D11VA
    পক্ষ AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 পরিমাণ(*s->handle_pairs_internal));
            যদি (!s->handle_pairs_internal)
                প্রত্যাগম AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_ctx->initial_pool_size,
                                             পরিমাণ(*s->surfaces_internal));
            যদি (!s->surfaces_internal)
                প্রত্যাগম AVERROR(ENOMEM);
            প্রতি (i = 0; i < src_ctx->initial_pool_size; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                যদি (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                } অন্যথা {
                    s->handle_pairs_internal[i].second = (mfxMemId)src_hwctx->texture_infos[i].index;
                }
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_size;
            যদি (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            } অন্যথা {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
            }
        }
        ভঙ্গ;
#endif
#যদি CONFIG_DXVA2
    পক্ষ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 পরিমাণ(*s->handle_pairs_internal));
            যদি (!s->handle_pairs_internal)
                প্রত্যাগম AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             পরিমাণ(*s->surfaces_internal));
            যদি (!s->surfaces_internal)
                প্রত্যাগম AVERROR(ENOMEM);
            প্রতি (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            যদি (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            অন্যথা
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        ভঙ্গ;
#endif
    স্বভাব:
        প্রত্যাগম AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, পূর্ণাঙ্ক flags)
{
    যদি (src_ctx->initial_pool_size < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        প্রত্যাগম AVERROR(EINVAL);
    } অন্যথা যদি (src_ctx->initial_pool_size == 0) {
        প্রত্যাগম qsv_dynamic_frames_derive_to(dst_ctx, src_ctx, flags);
    } অন্যথা {
        প্রত্যাগম qsv_fixed_frames_derive_to(dst_ctx, src_ctx, flags);
    }
}

স্থির পূর্ণাঙ্ক qsv_fixed_pool_map_to(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    পূর্ণাঙ্ক i, err, index = -1;

    প্রতি (i = 0; i < hwctx->nb_surfaces && index < 0; i++) {
        বিকল্প(src->format) {
#যদি CONFIG_VAAPI
        পক্ষ AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            যদি (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->data[3])
                index = i;
            ভঙ্গ;
        }
#endif
#যদি CONFIG_D3D11VA
        পক্ষ AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            যদি (pair->first == src->data[0]
                && (pair->second == src->data[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->data[1] == (uint8_t *)0)))
                index = i;
            ভঙ্গ;
        }
#endif
#যদি CONFIG_DXVA2
        পক্ষ AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            যদি (pair->first == src->data[3])
                index = i;
            ভঙ্গ;
        }
#endif
        }
    }
    যদি (index < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        প্রত্যাগম AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, রিক্ত, রিক্ত);
    যদি (err)
        প্রত্যাগম err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)&hwctx->surfaces[index];

    প্রত্যাগম 0;
}

স্থির শূন্য qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_internal = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_pairs_internal = (mfxHDLPair *)surfaces_internal->Data.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_frames->data;

    বিকল্প (src_ctx->format) {
#যদি CONFIG_VAAPI
    পক্ষ AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_pairs_internal->first);

        ভঙ্গ;
    }
#endif

#যদি CONFIG_D3D11VA
    পক্ষ AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        ভঙ্গ;
    }
#endif
    স্বভাব:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        ভঙ্গ;
    }

    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
}

স্থির পূর্ণাঙ্ক qsv_dynamic_pool_map_to(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    mfxFrameSurface1 *surfaces_internal = রিক্ত;
    mfxHDLPair *handle_pairs_internal = রিক্ত;
    পূর্ণাঙ্ক ret = 0;

    surfaces_internal = av_calloc(1, পরিমাণ(*surfaces_internal));
    যদি (!surfaces_internal) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    handle_pairs_internal = av_calloc(1, পরিমাণ(*handle_pairs_internal));
    যদি (!handle_pairs_internal) {
        ret = AVERROR(ENOMEM);
        গচ্ছ fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_internal);
    যদি (ret < 0)
        গচ্ছ fail;

    বিকল্প (src->format) {
#যদি CONFIG_VAAPI
    পক্ষ AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, পরিমাণ(*surface_id_internal));
        যদি (!surface_id_internal) {
            ret =AVERROR(ENOMEM);
            গচ্ছ fail;
        }

        *surface_id_internal = (VASurfaceID)(uintptr_t)src->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;

        ভঙ্গ;
    }
#endif

#যদি CONFIG_D3D11VA
    পক্ষ AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_pairs_internal->first = (mfxMemId)src->data[0];

        যদি (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        } অন্যথা {
            handle_pairs_internal->second = (mfxMemId)src->data[1];
        }

        ভঙ্গ;
    }
#endif
    স্বভাব:
        ret = AVERROR(ENOSYS);
        গচ্ছ fail;
    }

    surfaces_internal->Data.MemId = (mfxMemId)handle_pairs_internal;

    ret = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_internal);
    যদি (ret)
        গচ্ছ fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)surfaces_internal;

    প্রত্যাগম 0;

fail:
    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ধ্রুব AVFrame *src, পূর্ণাঙ্ক flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    যদি (hwctx->nb_surfaces)
        প্রত্যাগম qsv_fixed_pool_map_to(dst_ctx, dst, src, flags);
    অন্যথা
        প্রত্যাগম qsv_dynamic_pool_map_to(dst_ctx, dst, src, flags);
}

স্থির পূর্ণাঙ্ক qsv_frames_get_constraints(AVHWDeviceContext *ctx,
                                      ধ্রুব শূন্য *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    পূর্ণাঙ্ক i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    পরিমাণ(*constraints->valid_sw_formats));
    যদি (!constraints->valid_sw_formats)
        প্রত্যাগম AVERROR(ENOMEM);

    প্রতি (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, পরিমাণ(*constraints->valid_hw_formats));
    যদি (!constraints->valid_hw_formats)
        প্রত্যাগম AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    প্রত্যাগম 0;
}

স্থির শূন্য qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    যদি (hwctx->session)
        MFXClose(hwctx->session);

    যদি (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_buffer_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

স্থির mfxIMPL choose_implementation(ধ্রুব বর্ণ *device, গণনা AVHWDeviceType child_device_type)
{
    স্থির ধ্রুব সংরচনা {
        ধ্রুব বর্ণ *name;
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
    পূর্ণাঙ্ক i;

    যদি (device) {
        প্রতি (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            যদি (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                ভঙ্গ;
            }
        যদি (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, রিক্ত, 0);
    }

    যদি (impl != MFX_IMPL_SOFTWARE) {
        যদি (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_VIA_D3D11;
        অন্যথা যদি (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_VIA_D3D9;
    }

    প্রত্যাগম impl;
}

স্থির পূর্ণাঙ্ক qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        পূর্ণাঙ্ক flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfxVersion    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfxStatus     err;
    পূর্ণাঙ্ক ret;

    বিকল্প (child_device_ctx->type) {
#যদি CONFIG_VAAPI
    পক্ষ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        ভঙ্গ;
#endif
#যদি CONFIG_D3D11VA
    পক্ষ AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        ভঙ্গ;
#endif
#যদি CONFIG_DXVA2
    পক্ষ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        ভঙ্গ;
#endif
    স্বভাব:
        ret = AVERROR(ENOSYS);
        গচ্ছ fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    যদি (ret)
        গচ্ছ fail;

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    যদি (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        গচ্ছ fail;
    }

    প্রত্যাগম 0;

fail:
    যদি (hwctx->session)
        MFXClose(hwctx->session);

    যদি (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = রিক্ত;
    hwctx->loader = রিক্ত;
    প্রত্যাগম ret;
}

স্থির পূর্ণাঙ্ক qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, পূর্ণাঙ্ক flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(পরিমাণ(*priv));
    যদি (!priv)
        প্রত্যাগম AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->মুক্ত = qsv_device_free;

    impl = choose_implementation("hw_any", child_device_ctx->type);
    প্রত্যাগম qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

স্থির পূর্ণাঙ্ক qsv_device_create(AVHWDeviceContext *ctx, ধ্রুব বর্ণ *device,
                             AVDictionary *opts, পূর্ণাঙ্ক flags)
{
    QSVDevicePriv *priv;
    গণনা AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    পূর্ণাঙ্ক ret;

    priv = av_mallocz(পরিমাণ(*priv));
    যদি (!priv)
        প্রত্যাগম AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->মুক্ত        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", রিক্ত, 0);
    যদি (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->মান);
        যদি (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->মান);
            প্রত্যাগম AVERROR(EINVAL);
        }
#যদি QSV_ONEVPL
    } অন্যথা যদি (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } অন্যথা যদি (CONFIG_DXVA2) {
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
#অন্যথা
    } অন্যথা যদি (CONFIG_DXVA2) {
        av_log(রিক্ত, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } অন্যথা যদি (CONFIG_D3D11VA) {
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#endif
    } অন্যথা যদি (CONFIG_VAAPI) {
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } অন্যথা {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        প্রত্যাগম AVERROR(ENOSYS);
    }

#যদি CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    যদি (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->মান);
        প্রত্যাগম AVERROR(EINVAL);
    }
#endif

    child_device_opts = রিক্ত;
    বিকল্প (child_device_type) {
#যদি CONFIG_VAAPI
    পক্ষ AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_set(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_set(&child_device_opts, "driver",    "iHD",    0);
        }
        ভঙ্গ;
#endif
#যদি CONFIG_D3D11VA
    পক্ষ AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_set(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        ভঙ্গ;
#endif
#যদি CONFIG_DXVA2
    পক্ষ AV_HWDEVICE_TYPE_DXVA2:
#যদি QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#endif
        ভঙ্গ;
#endif
    স্বভাব:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            প্রত্যাগম AVERROR(ENOSYS);
        }
        ভঙ্গ;
    }

    e = av_dict_get(opts, "child_device", রিক্ত, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->মান : রিক্ত, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    যদি (ret < 0)
        প্রত্যাগম ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->data;

    impl = choose_implementation(device, child_device_type);

    প্রত্যাগম qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

ধ্রুব HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_size      = পরিমাণ(QSVDeviceContext),
    .frames_hwctx_size      = পরিমাণ(QSVFramesContext),

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

    .pix_fmts = (ধ্রুব গণনা AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
