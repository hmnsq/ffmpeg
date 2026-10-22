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
#define MFXUnload(a) করো { } যখন(0)
#endif

প্রকারলেখ কাঠামো QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

প্রকারলেখ কাঠামো QSVDeviceContext {
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

প্রকারলেখ কাঠামো QSVFramesContext {
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
    পূর্ণসংখ্যা             nb_surfaces_used;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#যদি QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfx_Ext_বাফার *ext_buffers[1];
#endif
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

প্রকারলেখ কাঠামো QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

স্থির ধ্রুবক কাঠামো {
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

বাহ্যিক পূর্ণসংখ্যা ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          গণনা AVHWDeviceType base_dev_type,
                                          শূন্য **base_handle);

স্থির পূর্ণসংখ্যা qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
পূর্ণসংখ্যা ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                   গণনা AVHWDeviceType base_dev_type,
                                   শূন্য **base_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->তথ্য_2.MemId;
    নির্বাচন (base_dev_type) {
#যদি CONFIG_VAAPI
    ক্ষেত্র AV_HWDEVICE_TYPE_VAAPI:
        base_handle[0] = handle_pair->first;
        ফেরত 0;
#endif
#যদি CONFIG_D3D11VA
    ক্ষেত্র AV_HWDEVICE_TYPE_D3D11VA:
        base_handle[0] = handle_pair->first;
        base_handle[1] = handle_pair->second;
        ফেরত 0;
#endif
#যদি CONFIG_DXVA2
    ক্ষেত্র AV_HWDEVICE_TYPE_DXVA2:
        base_handle[0] = handle_pair->first;
        ফেরত 0;
#endif
    }
    ফেরত AVERROR(EINVAL);
}

স্থির uint32_t qsv_fourcc_from_pix_fmt(গণনা AVPixelFormat pix_fmt)
{
    পূর্ণসংখ্যা i;
    জন্য (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        যদি (supported_pixel_formats[i].pix_fmt == pix_fmt)
            ফেরত supported_pixel_formats[i].fourcc;
    }
    ফেরত 0;
}

স্থির uint16_t qsv_shift_from_pix_fmt(গণনা AVPixelFormat pix_fmt)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        যদি (supported_pixel_formats[i].pix_fmt == pix_fmt)
            ফেরত supported_pixel_formats[i].mfx_shift;
    }

    ফেরত 0;
}

#যদি CONFIG_D3D11VA
স্থির uint32_t qsv_get_d3d11va_bind_flags(পূর্ণসংখ্যা mem_type)
{
    uint32_t bind_flags = 0;

    যদি ((mem_type & MFX_MEMTYPE_VIDEO_MEMORY_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_INTERNAL_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    অন্যথা
        bind_flags = D3D11_BIND_DECODER;

    যদি ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    ফেরত bind_flags;
}
#endif

স্থির পূর্ণসংখ্যা qsv_fill_border(AVFrame *dst, ধ্রুবক AVFrame *src)
{
    ধ্রুবক AVPixFmtDescriptor *desc;
    পূর্ণসংখ্যা i, planes_nb = 0;
    যদি (dst->format != src->format)
        ফেরত AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    জন্য (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    জন্য (i = 0; i < planes_nb; i++) {
        পূর্ণসংখ্যা sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->width,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->width,
                                                 i);
        ধ্রুবক AVComponentDescriptor comp = desc->comp[i];
        যদি (swidth < 0 || dwidth < 0) {
            av_log(ফাঁকা, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            ফেরত AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        যদি (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        জন্য (y = 0; y < sheight; y++) {
            শূন্য *সারি_ptr = dst->তথ্য[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(সারি_ptr,
                           comp.depth > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        জন্য (y = sheight; y < dheight; y++) {
            memcpy(dst->তথ্য[i]+y*dst->linesize[i],
                   dst->তথ্য[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    ফেরত 0;
}

স্থির পূর্ণসংখ্যা qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    পূর্ণসংখ্যা   hw_handle_supported = 0;
    mfxHandleType handle_type;
    গণনা AVHWDeviceType device_type;
    গণনা AVPixelFormat  pix_fmt;
    mfxStatus err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    যদি (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    যদি (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        ফেরত AVERROR_UNKNOWN;
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
    ফেরত 0;
}

স্থির শূন্য qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    যদি (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = ফাঁকা;
    s->session_download_init = 0;

    যদি (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = ফাঁকা;
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
    av_বাফার_unref(&s->child_frames_ref);
}

স্থির শূন্য qsv_pool_release_dummy(শূন্য *opaque, uint8_t *তথ্য)
{
}

স্থির শূন্য qsv_pool_release(শূন্য *opaque, uint8_t *তথ্য)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)তথ্য;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.তথ্য_2.MemId;
    AVHWFramesContext *child_frames_ctx;

    যদি (!s->child_frames_ref)
        ফেরত;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->তথ্য;
    যদি (!child_frames_ctx->device_ctx)
        ফেরত;

#যদি CONFIG_VAAPI
    যদি (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#endif

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

স্থির AVBufferRef *qsv_fixed_pool_alloc(শূন্য *opaque, size_t আকার_2)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    যদি (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        ফেরত av_বাফার_create((uint8_t*)(s->surfaces_internal + s->nb_surfaces_used - 1),
                                আকার(*hwctx->surfaces), qsv_pool_release_dummy, ফাঁকা, 0);
    }

    ফেরত ফাঁকা;
}

স্থির AVBufferRef *qsv_dynamic_pool_alloc(শূন্য *opaque, size_t আকার_2)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx;
    QSVSurface *qsv_surface = ফাঁকা;
    mfxHDLPair *handle_pairs_internal = ফাঁকা;
    পূর্ণসংখ্যা ret;

    যদি (!s->child_frames_ref)
        যাও fail;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->তথ্য;
    যদি (!child_frames_ctx->device_ctx)
        যাও fail;

#যদি CONFIG_DXVA2
    যদি (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        যাও fail;
    }
#endif

    qsv_surface = av_calloc(1, আকার(*qsv_surface));
    যদি (!qsv_surface)
        যাও fail;

    qsv_surface->child_frame = av_frame_alloc();
    যদি (!qsv_surface->child_frame)
        যাও fail;

    ret = av_hwframe_get_বাফার(s->child_frames_ref, qsv_surface->child_frame, 0);
    যদি (ret < 0)
        যাও fail;

    handle_pairs_internal = av_calloc(1, আকার(*handle_pairs_internal));
    যদি (!handle_pairs_internal)
        যাও fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    যদি (ret < 0)
        যাও fail;

#যদি CONFIG_VAAPI
    যদি (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, আকার(*surface_id_internal));
        যদি (!surface_id_internal)
            যাও fail;

        *surface_id_internal = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->তথ্য[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
    }
#endif

#যদি CONFIG_D3D11VA
    যদি (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        handle_pairs_internal->first = (mfxMemId)qsv_surface->child_frame->তথ্য[0];

        যদি (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        অন্যথা
            handle_pairs_internal->second = (mfxMemId)qsv_surface->child_frame->তথ্য[1];

    }
#endif

    qsv_surface->mfx_surface.তথ্য_2.MemId = (mfxMemId)handle_pairs_internal;
    ফেরত av_বাফার_create((uint8_t *)qsv_surface, আকার(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    যদি (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_pairs_internal);

    ফেরত ফাঁকা;
}

স্থির AVBufferRef *qsv_pool_alloc(শূন্য *opaque, size_t আকার_2)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    যদি (hwctx->nb_surfaces == 0) {
        ফেরত qsv_dynamic_pool_alloc(opaque, আকার_2);
    } অন্যথা {
        ফেরত qsv_fixed_pool_alloc(opaque, আকার_2);
    }
}

স্থির পূর্ণসংখ্যা qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = ফাঁকা;
    AVBufferRef *child_frames_ref = ফাঁকা;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    পূর্ণসংখ্যা i, ret = 0;

    যদি (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        ফেরত AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    যদি (!child_device_ref)
        ফেরত AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->তথ্য;

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
        যাও fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    যদি (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        যাও fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->তথ্য;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_আকার = ctx->initial_pool_আকার;
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
        যাও fail;
    }

#যদি CONFIG_VAAPI
    যদি (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        জন্য (i = 0; i < ctx->initial_pool_আকার; i++) {
            s->handle_pairs_internal[i].first = child_frames_hwctx->surface_ids + i;
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].তথ্য_2.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif
#যদি CONFIG_D3D11VA
    যদি (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        জন্য (i = 0; i < ctx->initial_pool_আকার; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->texture_infos[i].texture;
            যদি(child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            } অন্যথা {
                s->handle_pairs_internal[i].second = (mfxMemId)child_frames_hwctx->texture_infos[i].সূচক;
            }
            s->surfaces_internal[i].তথ্য_2.MemId = (mfxMemId)&s->handle_pairs_internal[i];
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
        জন্য (i = 0; i < ctx->initial_pool_আকার; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->surfaces[i];
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].তথ্য_2.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        যদি (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        অন্যথা
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = ফাঁকা;

fail:
    av_বাফার_unref(&child_device_ref);
    av_বাফার_unref(&child_frames_ref);
    ফেরত ret;
}

স্থির পূর্ণসংখ্যা qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    ধ্রুবক AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    যদি (!desc)
        ফেরত AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    যদি (!fourcc)
        ফেরত AVERROR(EINVAL);

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

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    পূর্ণসংখ্যা i, ret = 0;

    যদি (ctx->initial_pool_আকার < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        ফেরত AVERROR(EINVAL);
    } অন্যথা যদি (ctx->initial_pool_আকার == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        যদি (ret < 0)
            ফেরত ret;

        ffhwframesctx(ctx)->pool_internal = av_বাফার_pool_init2(আকার(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, ফাঁকা);
        যদি (!ffhwframesctx(ctx)->pool_internal)
            ফেরত AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, আকার(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        frames_hwctx->info = &s->frame_info;
        frames_hwctx->nb_surfaces = 0;

        ফেরত 0;
    }

    s->handle_pairs_internal = av_calloc(ctx->initial_pool_আকার,
                                         আকার(*s->handle_pairs_internal));
    যদি (!s->handle_pairs_internal)
        ফেরত AVERROR(ENOMEM);

    s->surfaces_internal = av_calloc(ctx->initial_pool_আকার,
                                     আকার(*s->surfaces_internal));
    যদি (!s->surfaces_internal)
        ফেরত AVERROR(ENOMEM);

    জন্য (i = 0; i < ctx->initial_pool_আকার; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_internal[i]);
        যদি (ret < 0)
            ফেরত ret;
    }

#যদি QSV_HAVE_OPAQUE
    যদি (!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        যদি (ret < 0)
            ফেরত ret;
    }
#অন্যথা
    ret = qsv_init_child_ctx(ctx);
    যদি (ret < 0)
        ফেরত ret;
#endif

    ffhwframesctx(ctx)->pool_internal = av_বাফার_pool_init2(আকার(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, ফাঁকা);
    যদি (!ffhwframesctx(ctx)->pool_internal)
        ফেরত AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_আকার;

    ফেরত 0;
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
        ফেরত MFX_ERR_UNSUPPORTED;
    যদি (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        ফেরত MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->অঙ্ক_Frame_Actual = hwctx->nb_surfaces;

    ফেরত MFX_ERR_NONE;
}

স্থির mfxStatus frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    ফেরত MFX_ERR_NONE;
}

স্থির mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfx_Frame_তথ্য *ptr)
{
    ফেরত MFX_ERR_UNSUPPORTED;
}

স্থির mfxStatus frame_unlock(mfxHDL pthis, mfxMemId mid, mfx_Frame_তথ্য *ptr)
{
    ফেরত MFX_ERR_UNSUPPORTED;
}

স্থির mfxStatus frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    যদি (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    ফেরত MFX_ERR_NONE;
}

#যদি QSV_ONEVPL

স্থির পূর্ণসংখ্যা qsv_d3d11_update_config(শূন্য *ctx, mfxHDL handle, mfxConfig cfg)
{
    পূর্ণসংখ্যা ret = AVERROR_UNKNOWN;
#যদি CONFIG_D3D11VA
    mfxStatus sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = ফাঁকা;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_মান = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (শূন্য**)&pDXGIDevice);
    যদি (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        যদি (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            ফেরত ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        যদি (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            যাও fail;
        }
    } অন্যথা {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        ফেরত ret;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_U16;
    impl_মান.তথ্য_2.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুবক mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        যাও fail;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_PTR;
    impl_মান.তথ্য_2.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুবক mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        যাও fail;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_U32;
    impl_মান.তথ্য_2.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুবক mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        যাও fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#endif
    ফেরত ret;
}

স্থির পূর্ণসংখ্যা qsv_d3d9_update_config(শূন্য *ctx, mfxHDL handle, mfxConfig cfg)
{
    পূর্ণসংখ্যা ret = AVERROR_UNKNOWN;
#যদি CONFIG_DXVA2
    mfxStatus sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = ফাঁকা;
    IDirect3DDevice9Ex *device_ex = ফাঁকা;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = ফাঁকা;
    IDirect3D9 *d3d9 = ফাঁকা;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_মান = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        যাও fail;
    }

    hr = IDirect3DDeviceManager9_LockDevice(devmgr, device_handle, &device, TRUE);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        যাও fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (শূন্য **)&device_ex);
    IDirect3DDevice9_Release(device);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        যাও unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        যাও unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        যাও unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (শূন্য **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        যাও unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    যদি (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        যাও release;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_PTR;
    impl_মান.তথ্য_2.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুবক mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        যাও release;
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
    ফেরত ret;
}

স্থির পূর্ণসংখ্যা qsv_va_update_config(শূন্য *ctx, mfxHDL handle, mfxConfig cfg)
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
        impl_মান.তথ্য_2.U16 = (attr.মান & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ধ্রুবক mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_মান);
        যদি (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            যাও fail;
        }
    } অন্যথা {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        যাও fail;
    }

    ফেরত 0;

fail:
#অন্যথা
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#endif
#endif
    ফেরত AVERROR_UNKNOWN;
}

স্থির পূর্ণসংখ্যা qsv_new_mfx_loader(শূন্য *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfxVersion *pver,
                              শূন্য **ploader)
{
    mfxStatus sts;
    mfxLoader loader = ফাঁকা;
    mfxConfig cfg;
    mfxVariant impl_মান = {0};

    *ploader = ফাঁকা;
    loader = MFXLoad();
    যদি (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        যাও fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    যদি (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        যাও fail;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_U32;
    impl_মান.তথ্য_2.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুবক mfxU8 *)"mfxImplDescription.Impl", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        যাও fail;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_U32;
    impl_মান.তথ্য_2.U32 = pver->Version;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুবক mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        যাও fail;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_U32;
    impl_মান.তথ্য_2.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুবক mfxU8 *)"mfxImplDescription.VendorID", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        যাও fail;
    }

    যদি (MFX_HANDLE_VA_DISPLAY == handle_type) {
        যদি (handle && qsv_va_update_config(ctx, handle, cfg))
            যাও fail;

        impl_মান.তথ্য_2.U32 = MFX_ACCEL_MODE_VIA_VAAPI;
    } অন্যথা যদি (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        যদি (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            যাও fail;

        impl_মান.তথ্য_2.U32 = MFX_ACCEL_MODE_VIA_D3D9;
    } অন্যথা {
        যদি (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            যাও fail;

        impl_মান.তথ্য_2.U32 = MFX_ACCEL_MODE_VIA_D3D11;
    }

    impl_মান.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ধ্রুবক mfxU8 *)"mfxImplDescription.AccelerationMode", impl_মান);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        যাও fail;
    }

    *ploader = loader;

    ফেরত 0;

fail:
    যদি (loader)
        MFXUnload(loader);

    ফেরত AVERROR_UNKNOWN;
}

স্থির পূর্ণসংখ্যা qsv_create_mfx_session_from_loader(শূন্য *ctx, mfxLoader loader, mfxSession *psession)
{
    mfxStatus sts;
    mfxSession session = ফাঁকা;
    uint32_t impl_idx = 0;
    mfxVersion ver;

    যখন (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        যদি (sts == MFX_ERR_NOT_FOUND)
            বিরতি;
        অন্যথা যদি (sts != MFX_ERR_NONE) {
            impl_idx++;
            চালু;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        যদি (sts == MFX_ERR_NONE)
            বিরতি;

        impl_idx++;
    }

    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        যাও fail;
    }

    sts = MFXQueryVersion(session, &ver);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        যাও fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    ফেরত 0;

fail:
    যদি (session)
        MFXClose(session);

    ফেরত AVERROR_UNKNOWN;
}

স্থির পূর্ণসংখ্যা qsv_create_mfx_session(শূন্য *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  শূন্য **ploader)
{
    mfxLoader loader = ফাঁকা;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    যদি (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        ফেরত AVERROR(EXDEV);
    }

    *psession = ফাঁকা;

    যদি (!*ploader) {
        যদি (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (শূন্য **)&loader))
            যাও fail;

        av_assert0(loader);
    } অন্যথা
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    যদি (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        যাও fail;

    যদি (!*ploader)
        *ploader = loader;

    ফেরত 0;

fail:
    যদি (!*ploader && loader)
        MFXUnload(loader);

    ফেরত AVERROR_UNKNOWN;
}

#অন্যথা

স্থির পূর্ণসংখ্যা qsv_create_mfx_session(শূন্য *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  শূন্য **ploader)
{
    mfxVersion ver;
    mfxStatus sts;
    mfxSession session = ফাঁকা;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    *ploader = ফাঁকা;
    *psession = ফাঁকা;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        যাও fail;
    }

    sts = MFXQueryVersion(session, &ver);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        যাও fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    যদি (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        যাও fail;
    }

    *psession = session;

    ফেরত 0;

fail:
    যদি (session)
        MFXClose(session);

    ফেরত AVERROR_UNKNOWN;
}

#endif

স্থির পূর্ণসংখ্যা qsv_init_internal_session(AVHWFramesContext *ctx,
                                     mfxSession *session, পূর্ণসংখ্যা upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    পূর্ণসংখ্যা opaque = 0;

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
    পূর্ণসংখ্যা                   ret = AVERROR_UNKNOWN;
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
        ফেরত AVERROR_UNKNOWN;
    }

#যদি QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    যদি (ret)
        যাও fail;

    যদি (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        যদি (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            যাও fail;
        }
    }

    যদি (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        যদি (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            যাও fail;
        }
    }

    যদি (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        যদি (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            যাও fail;
        }
    }

    memset(&par, 0, আকার(par));

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
        যাও fail;
    }

    ফেরত 0;

fail:
    যদি (*session)
        MFXClose(*session);

    *session = ফাঁকা;

    ফেরত ret;
}

স্থির পূর্ণসংখ্যা qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    পূর্ণসংখ্যা opaque = 0;

    uint32_t fourcc;
    পূর্ণসংখ্যা i, ret;

#যদি QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    যদি (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        ফেরত AVERROR(ENOSYS);
    }

    যদি (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        যদি (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            ফেরত ret;
        }
    }

    যদি (!opaque) {
        s->mem_ids = av_calloc(frames_hwctx->nb_surfaces, আকার(*s->mem_ids));
        যদি (!s->mem_ids)
            ফেরত AVERROR(ENOMEM);

        জন্য (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].তথ্য_2.MemId;
    }
#যদি QSV_HAVE_OPAQUE
    অন্যথা {
        s->surface_ptrs = av_calloc(frames_hwctx->nb_surfaces,
                                    আকার(*s->surface_ptrs));
        যদি (!s->surface_ptrs)
            ফেরত AVERROR(ENOMEM);

        জন্য (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.অঙ্ক_Surface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.বাফার_Id = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.বাফার_Sz = আকার(s->opaque_alloc);

        s->ext_buffers[0] = (mfx_Ext_বাফার*)&s->opaque_alloc;
    }
#endif

    s->session_download = ফাঁকা;
    s->session_upload   = ফাঁকা;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#যদি HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, ফাঁকা);
#endif

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা qsv_get_বাফার(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_বাফার_pool_get(ctx->pool);
    যদি (!frame->buf[0])
        ফেরত AVERROR(ENOMEM);

    frame->তথ্য[3] = frame->buf[0]->তথ্য;
    frame->format  = AV_PIX_FMT_QSV;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    গণনা AVHWFrameTransferDirection dir,
                                    গণনা AVPixelFormat **formats)
{
    গণনা AVPixelFormat *fmts;

    fmts = av_malloc_array(2, আকার(*fmts));
    যদি (!fmts)
        ফেরত AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, পূর্ণসংখ্যা flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    পূর্ণসংখ্যা i;

    নির্বাচন (dst_ctx->device_ctx->type) {
#যদি CONFIG_VAAPI
    ক্ষেত্র AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               আকার(*dst_hwctx->surface_ids));
            যদি (!dst_hwctx->surface_ids)
                ফেরত AVERROR(ENOMEM);
            জন্য (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].তথ্য_2.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        বিরতি;
#endif
#যদি CONFIG_D3D11VA
    ক্ষেত্র AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_আকার = src_ctx->initial_pool_আকার;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 আকার(*dst_hwctx->texture_infos));
            যদি (!dst_hwctx->texture_infos)
                ফেরত AVERROR(ENOMEM);
            যদি (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            জন্য (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].তথ্য_2.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].সূচক = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            যদি (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } অন্যথা
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        বিরতি;
#endif
#যদি CONFIG_DXVA2
    ক্ষেত্র AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            আকার(*dst_hwctx->surfaces));
            যদি (!dst_hwctx->surfaces)
                ফেরত AVERROR(ENOMEM);
            জন্য (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].তথ্য_2.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            যদি (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            অন্যথা
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        বিরতি;
#endif
    পূর্বনির্ধারিত:
        ফেরত AVERROR(ENOSYS);
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->তথ্য[3];
    AVHWFramesContext *child_frames_ctx;
    ধ্রুবক AVPixFmtDescriptor *desc;
    uint8_t *child_তথ্য;
    AVFrame *dummy;
    পূর্ণসংখ্যা ret = 0;

    যদি (!s->child_frames_ref)
        ফেরত AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->তথ্য;

    নির্বাচন (child_frames_ctx->device_ctx->type) {
#যদি CONFIG_VAAPI
    ক্ষেত্র AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->তথ্য_2.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_তথ্য = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        বিরতি;
    }
#endif
#যদি CONFIG_D3D11VA
    ক্ষেত্র AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->তথ্য_2.MemId;
        child_তথ্য = pair->first;
        বিরতি;
    }
#endif
#যদি CONFIG_DXVA2
    ক্ষেত্র AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->তথ্য_2.MemId;
        child_তথ্য = pair->first;
        বিরতি;
    }
#endif
    পূর্বনির্ধারিত:
        ফেরত AVERROR(ENOSYS);
    }

    যদি (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, ফাঁকা, ফাঁকা);
        যদি (ret < 0)
            ফেরত ret;

        dst->width   = src->width;
        dst->height  = src->height;

       যদি (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->তথ্য_2.MemId;
            dst->তথ্য[0] = pair->first;
            dst->তথ্য[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } অন্যথা {
            dst->তথ্য[3] = child_তথ্য;
        }

        ফেরত 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    যদি (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        ফেরত AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    যদি (!dummy)
        ফেরত AVERROR(ENOMEM);

    dummy->buf[0]        = av_বাফার_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_বাফার_ref(s->child_frames_ref);
    যদি (!dummy->buf[0] || !dummy->hw_frames_ctx)
        যাও fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;

    যদি (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->তথ্য_2.MemId;
        dummy->তথ্য[0] = pair->first;
        dummy->তথ্য[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } অন্যথা {
        dummy->তথ্য[3] = child_তথ্য;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    ফেরত ret;
}

স্থির পূর্ণসংখ্যা qsv_transfer_তথ্য_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   ধ্রুবক AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->তথ্য;
    পূর্ণসংখ্যা download = !!src->hw_frames_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->তথ্য[3] : dst->তথ্য[3]);

    AVFrame *dummy;
    পূর্ণসংখ্যা ret;

    dummy = av_frame_alloc();
    যদি (!dummy)
        ফেরত AVERROR(ENOMEM);

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->তথ্য[3]       = surf->তথ্য_2.MemId;
    dummy->hw_frames_ctx = s->child_frames_ref;

    ret = download ? av_hwframe_transfer_তথ্য(dst, dummy, 0) :
                     av_hwframe_transfer_তথ্য(dummy, src, 0);

    dummy->buf[0]        = ফাঁকা;
    dummy->তথ্য[3]       = ফাঁকা;
    dummy->hw_frames_ctx = ফাঁকা;

    av_frame_free(&dummy);

    ফেরত ret;
}

স্থির পূর্ণসংখ্যা map_frame_to_surface(ধ্রুবক AVFrame *frame, mfxFrameSurface1 *surface)
{
    নির্বাচন (frame->format) {
    ক্ষেত্র AV_PIX_FMT_NV12:
    ক্ষেত্র AV_PIX_FMT_P010:
    ক্ষেত্র AV_PIX_FMT_P012:
        surface->তথ্য_2.Y  = frame->তথ্য[0];
        surface->তথ্য_2.UV = frame->তথ্য[1];
        বিরতি;

    ক্ষেত্র AV_PIX_FMT_YUV420P:
        surface->তথ্য_2.Y = frame->তথ্য[0];
        surface->তথ্য_2.U = frame->তথ্য[1];
        surface->তথ্য_2.V = frame->তথ্য[2];
        বিরতি;

    ক্ষেত্র AV_PIX_FMT_BGRA:
        surface->তথ্য_2.B = frame->তথ্য[0];
        surface->তথ্য_2.G = frame->তথ্য[0] + 1;
        surface->তথ্য_2.R = frame->তথ্য[0] + 2;
        surface->তথ্য_2.A = frame->তথ্য[0] + 3;
        বিরতি;
    ক্ষেত্র AV_PIX_FMT_YUYV422:
        surface->তথ্য_2.Y = frame->তথ্য[0];
        surface->তথ্য_2.U = frame->তথ্য[0] + 1;
        surface->তথ্য_2.V = frame->তথ্য[0] + 3;
        বিরতি;

    ক্ষেত্র AV_PIX_FMT_Y210:
    ক্ষেত্র AV_PIX_FMT_Y212:
        surface->তথ্য_2.Y16 = (mfxU16 *)frame->তথ্য[0];
        surface->তথ্য_2.U16 = (mfxU16 *)frame->তথ্য[0] + 1;
        surface->তথ্য_2.V16 = (mfxU16 *)frame->তথ্য[0] + 3;
        বিরতি;
    ক্ষেত্র AV_PIX_FMT_VUYX:
        surface->তথ্য_2.V = frame->তথ্য[0];
        surface->তথ্য_2.U = frame->তথ্য[0] + 1;
        surface->তথ্য_2.Y = frame->তথ্য[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->তথ্য_2.A = frame->তথ্য[0] + 3;
        বিরতি;
    ক্ষেত্র AV_PIX_FMT_XV30:
        surface->তথ্য_2.U = frame->তথ্য[0];
        বিরতি;
    ক্ষেত্র AV_PIX_FMT_XV36:
        surface->তথ্য_2.U = frame->তথ্য[0];
        surface->তথ্য_2.Y = frame->তথ্য[0] + 2;
        surface->তথ্য_2.V = frame->তথ্য[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->তথ্য_2.A = frame->তথ্য[0] + 6;
        বিরতি;
#যদি CONFIG_VAAPI
    ক্ষেত্র AV_PIX_FMT_UYVY422:
        surface->তথ্য_2.Y = frame->তথ্য[0] + 1;
        surface->তথ্য_2.U = frame->তথ্য[0];
        surface->তথ্য_2.V = frame->তথ্য[0] + 2;
        বিরতি;
#endif
    পূর্বনির্ধারিত:
        ফেরত MFX_ERR_UNSUPPORTED;
    }
    surface->তথ্য_2.Pitch     = frame->linesize[0];
    surface->তথ্য_2.TimeStamp = frame->pts;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা qsv_internal_session_check_init(AVHWFramesContext *ctx, পূর্ণসংখ্যা upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    পূর্ণসংখ্যা ret = 0;

    যদি (atomic_load(inited))
        ফেরত 0;

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

    ফেরত ret;
}

স্থির পূর্ণসংখ্যা qsv_transfer_তথ্য_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ধ্রুবক AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->তথ্য[3];

    mfxSyncPoint sync = ফাঁকা;
    mfxStatus err;
    পূর্ণসংখ্যা ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    পূর্ণসংখ্যা realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 0);
    যদি (ret < 0)
        ফেরত ret;

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
            ret = av_frame_get_বাফার(tmp_frame, 0);
            যদি (ret < 0)
                ফেরত ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    যদি (!s->session_download) {
        যদি (s->child_frames_ref)
            ফেরত qsv_transfer_তথ্য_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        ফেরত AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst_frame, &out);

    করো {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, ফাঁকা, &sync);
        যদি (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } যখন (err == MFX_WRN_DEVICE_BUSY);

    যদি (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        ফেরত AVERROR_UNKNOWN;
    }

    করো {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } যখন (err == MFX_WRN_IN_EXECUTION);
    যদি (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        ফেরত AVERROR_UNKNOWN;
    }

    যদি (realigned) {
        tmp_frame->width  = dst->width;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        যদি (ret < 0)
            ফেরত ret;
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা qsv_transfer_তথ্য_to(AVHWFramesContext *ctx, AVFrame *dst,
                                ধ্রুবক AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   in = {{ 0 }};
    mfxFrameSurface1 *out = (mfxFrameSurface1*)dst->তথ্য[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = ফাঁকা;
    mfxStatus err;
    পূর্ণসংখ্যা ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    ধ্রুবক AVFrame *src_frame;
    পূর্ণসংখ্যা realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 1);
    যদি (ret < 0)
        ফেরত ret;

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
            ret = av_frame_get_বাফার(tmp_frame, 0);
            যদি (ret < 0)
                ফেরত ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        যদি (ret < 0) {
            av_frame_unref(tmp_frame);
            ফেরত ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        যদি (ret < 0) {
            av_frame_unref(tmp_frame);
            ফেরত ret;
        }

        tmp_info = out->Info;
        out->Info.CropW = FFMIN(out->Info.Width,  tmp_frame->width);
        out->Info.CropH = FFMIN(out->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    যদি (!s->session_upload) {
        যদি (s->child_frames_ref)
            ফেরত qsv_transfer_তথ্য_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        ফেরত AVERROR(ENOSYS);
    }

    in.Info = out->Info;
    map_frame_to_surface(src_frame, &in);

    করো {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_upload, &in, out, ফাঁকা, &sync);
        যদি (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } যখন (err == MFX_WRN_DEVICE_BUSY);

    যদি (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        ফেরত AVERROR_UNKNOWN;
    }

    করো {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } যখন (err == MFX_WRN_IN_EXECUTION);
    যদি (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        ফেরত AVERROR_UNKNOWN;
    }

    যদি (realigned) {
        out->Info.CropW = tmp_info.CropW;
        out->Info.CropH = tmp_info.CropH;
    }

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা qsv_dynamic_frames_derive_to(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, পূর্ণসংখ্যা flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    নির্বাচন (src_ctx->device_ctx->type) {
#যদি CONFIG_VAAPI
    ক্ষেত্র AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        বিরতি;
#endif

#যদি CONFIG_D3D11VA
    ক্ষেত্র AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        যদি (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } অন্যথা {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
    বিরতি;
#endif

    পূর্বনির্ধারিত:
        ফেরত AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, আকার(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    ফেরত 0;
}

স্থির পূর্ণসংখ্যা qsv_fixed_frames_derive_to(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, পূর্ণসংখ্যা flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    পূর্ণসংখ্যা i;

    নির্বাচন (src_ctx->device_ctx->type) {
#যদি CONFIG_VAAPI
    ক্ষেত্র AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_আকার,
                                                 আকার(*s->handle_pairs_internal));
            যদি (!s->handle_pairs_internal)
                ফেরত AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             আকার(*s->surfaces_internal));
            যদি (!s->surfaces_internal)
                ফেরত AVERROR(ENOMEM);
            জন্য (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = src_hwctx->surface_ids + i;
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].তথ্য_2.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        বিরতি;
#endif
#যদি CONFIG_D3D11VA
    ক্ষেত্র AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_আকার,
                                                 আকার(*s->handle_pairs_internal));
            যদি (!s->handle_pairs_internal)
                ফেরত AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_ctx->initial_pool_আকার,
                                             আকার(*s->surfaces_internal));
            যদি (!s->surfaces_internal)
                ফেরত AVERROR(ENOMEM);
            জন্য (i = 0; i < src_ctx->initial_pool_আকার; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                যদি (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                } অন্যথা {
                    s->handle_pairs_internal[i].second = (mfxMemId)src_hwctx->texture_infos[i].সূচক;
                }
                s->surfaces_internal[i].তথ্য_2.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_আকার;
            যদি (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            } অন্যথা {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
            }
        }
        বিরতি;
#endif
#যদি CONFIG_DXVA2
    ক্ষেত্র AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_আকার,
                                                 আকার(*s->handle_pairs_internal));
            যদি (!s->handle_pairs_internal)
                ফেরত AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             আকার(*s->surfaces_internal));
            যদি (!s->surfaces_internal)
                ফেরত AVERROR(ENOMEM);
            জন্য (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].তথ্য_2.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            যদি (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            অন্যথা
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        বিরতি;
#endif
    পূর্বনির্ধারিত:
        ফেরত AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    ফেরত 0;
}

স্থির পূর্ণসংখ্যা qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, পূর্ণসংখ্যা flags)
{
    যদি (src_ctx->initial_pool_আকার < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        ফেরত AVERROR(EINVAL);
    } অন্যথা যদি (src_ctx->initial_pool_আকার == 0) {
        ফেরত qsv_dynamic_frames_derive_to(dst_ctx, src_ctx, flags);
    } অন্যথা {
        ফেরত qsv_fixed_frames_derive_to(dst_ctx, src_ctx, flags);
    }
}

স্থির পূর্ণসংখ্যা qsv_fixed_pool_map_to(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    পূর্ণসংখ্যা i, err, সূচক = -1;

    জন্য (i = 0; i < hwctx->nb_surfaces && সূচক < 0; i++) {
        নির্বাচন(src->format) {
#যদি CONFIG_VAAPI
        ক্ষেত্র AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].তথ্য_2.MemId;
            যদি (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->তথ্য[3])
                সূচক = i;
            বিরতি;
        }
#endif
#যদি CONFIG_D3D11VA
        ক্ষেত্র AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].তথ্য_2.MemId;
            যদি (pair->first == src->তথ্য[0]
                && (pair->second == src->তথ্য[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->তথ্য[1] == (uint8_t *)0)))
                সূচক = i;
            বিরতি;
        }
#endif
#যদি CONFIG_DXVA2
        ক্ষেত্র AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].তথ্য_2.MemId;
            যদি (pair->first == src->তথ্য[3])
                সূচক = i;
            বিরতি;
        }
#endif
        }
    }
    যদি (সূচক < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        ফেরত AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, ফাঁকা, ফাঁকা);
    যদি (err)
        ফেরত err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->তথ্য[3] = (uint8_t*)&hwctx->surfaces[সূচক];

    ফেরত 0;
}

স্থির শূন্য qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_internal = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_pairs_internal = (mfxHDLPair *)surfaces_internal->তথ্য_2.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_frames->তথ্য;

    নির্বাচন (src_ctx->format) {
#যদি CONFIG_VAAPI
    ক্ষেত্র AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_pairs_internal->first);

        বিরতি;
    }
#endif

#যদি CONFIG_D3D11VA
    ক্ষেত্র AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        বিরতি;
    }
#endif
    পূর্বনির্ধারিত:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        বিরতি;
    }

    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
}

স্থির পূর্ণসংখ্যা qsv_dynamic_pool_map_to(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    mfxFrameSurface1 *surfaces_internal = ফাঁকা;
    mfxHDLPair *handle_pairs_internal = ফাঁকা;
    পূর্ণসংখ্যা ret = 0;

    surfaces_internal = av_calloc(1, আকার(*surfaces_internal));
    যদি (!surfaces_internal) {
        ret = AVERROR(ENOMEM);
        যাও fail;
    }

    handle_pairs_internal = av_calloc(1, আকার(*handle_pairs_internal));
    যদি (!handle_pairs_internal) {
        ret = AVERROR(ENOMEM);
        যাও fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_internal);
    যদি (ret < 0)
        যাও fail;

    নির্বাচন (src->format) {
#যদি CONFIG_VAAPI
    ক্ষেত্র AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, আকার(*surface_id_internal));
        যদি (!surface_id_internal) {
            ret =AVERROR(ENOMEM);
            যাও fail;
        }

        *surface_id_internal = (VASurfaceID)(uintptr_t)src->তথ্য[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;

        বিরতি;
    }
#endif

#যদি CONFIG_D3D11VA
    ক্ষেত্র AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_frames_ctx->তথ্য;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_pairs_internal->first = (mfxMemId)src->তথ্য[0];

        যদি (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        } অন্যথা {
            handle_pairs_internal->second = (mfxMemId)src->তথ্য[1];
        }

        বিরতি;
    }
#endif
    পূর্বনির্ধারিত:
        ret = AVERROR(ENOSYS);
        যাও fail;
    }

    surfaces_internal->তথ্য_2.MemId = (mfxMemId)handle_pairs_internal;

    ret = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_internal);
    যদি (ret)
        যাও fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->তথ্য[3] = (uint8_t*)surfaces_internal;

    ফেরত 0;

fail:
    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
    ফেরত ret;
}

স্থির পূর্ণসংখ্যা qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ধ্রুবক AVFrame *src, পূর্ণসংখ্যা flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    যদি (hwctx->nb_surfaces)
        ফেরত qsv_fixed_pool_map_to(dst_ctx, dst, src, flags);
    অন্যথা
        ফেরত qsv_dynamic_pool_map_to(dst_ctx, dst, src, flags);
}

স্থির পূর্ণসংখ্যা qsv_frames_get_constraints(AVHWDeviceContext *ctx,
                                      ধ্রুবক শূন্য *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    পূর্ণসংখ্যা i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    আকার(*constraints->valid_sw_formats));
    যদি (!constraints->valid_sw_formats)
        ফেরত AVERROR(ENOMEM);

    জন্য (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, আকার(*constraints->valid_hw_formats));
    যদি (!constraints->valid_hw_formats)
        ফেরত AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ফেরত 0;
}

স্থির শূন্য qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    যদি (hwctx->session)
        MFXClose(hwctx->session);

    যদি (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_বাফার_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

স্থির mfxIMPL choose_implementation(ধ্রুবক অক্ষর *device, গণনা AVHWDeviceType child_device_type)
{
    স্থির ধ্রুবক কাঠামো {
        ধ্রুবক অক্ষর *name;
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
    পূর্ণসংখ্যা i;

    যদি (device) {
        জন্য (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            যদি (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                বিরতি;
            }
        যদি (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, ফাঁকা, 0);
    }

    যদি (impl != MFX_IMPL_SOFTWARE) {
        যদি (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_VIA_D3D11;
        অন্যথা যদি (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_VIA_D3D9;
    }

    ফেরত impl;
}

স্থির পূর্ণসংখ্যা qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        পূর্ণসংখ্যা flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfxVersion    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfxStatus     err;
    পূর্ণসংখ্যা ret;

    নির্বাচন (child_device_ctx->type) {
#যদি CONFIG_VAAPI
    ক্ষেত্র AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        বিরতি;
#endif
#যদি CONFIG_D3D11VA
    ক্ষেত্র AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        বিরতি;
#endif
#যদি CONFIG_DXVA2
    ক্ষেত্র AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        বিরতি;
#endif
    পূর্বনির্ধারিত:
        ret = AVERROR(ENOSYS);
        যাও fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    যদি (ret)
        যাও fail;

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    যদি (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        যাও fail;
    }

    ফেরত 0;

fail:
    যদি (hwctx->session)
        MFXClose(hwctx->session);

    যদি (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = ফাঁকা;
    hwctx->loader = ফাঁকা;
    ফেরত ret;
}

স্থির পূর্ণসংখ্যা qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, পূর্ণসংখ্যা flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(আকার(*priv));
    যদি (!priv)
        ফেরত AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->মুক্ত = qsv_device_free;

    impl = choose_implementation("hw_any", child_device_ctx->type);
    ফেরত qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

স্থির পূর্ণসংখ্যা qsv_device_create(AVHWDeviceContext *ctx, ধ্রুবক অক্ষর *device,
                             AVDictionary *opts, পূর্ণসংখ্যা flags)
{
    QSVDevicePriv *priv;
    গণনা AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    পূর্ণসংখ্যা ret;

    priv = av_mallocz(আকার(*priv));
    যদি (!priv)
        ফেরত AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->মুক্ত        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", ফাঁকা, 0);
    যদি (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->মান);
        যদি (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->মান);
            ফেরত AVERROR(EINVAL);
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
        av_log(ফাঁকা, AV_LOG_WARNING,
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
        ফেরত AVERROR(ENOSYS);
    }

#যদি CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    যদি (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->মান);
        ফেরত AVERROR(EINVAL);
    }
#endif

    child_device_opts = ফাঁকা;
    নির্বাচন (child_device_type) {
#যদি CONFIG_VAAPI
    ক্ষেত্র AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_set(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_set(&child_device_opts, "driver",    "iHD",    0);
        }
        বিরতি;
#endif
#যদি CONFIG_D3D11VA
    ক্ষেত্র AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_set(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        বিরতি;
#endif
#যদি CONFIG_DXVA2
    ক্ষেত্র AV_HWDEVICE_TYPE_DXVA2:
#যদি QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#endif
        বিরতি;
#endif
    পূর্বনির্ধারিত:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            ফেরত AVERROR(ENOSYS);
        }
        বিরতি;
    }

    e = av_dict_get(opts, "child_device", ফাঁকা, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->মান : ফাঁকা, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    যদি (ret < 0)
        ফেরত ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->তথ্য;

    impl = choose_implementation(device, child_device_type);

    ফেরত qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

ধ্রুবক HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_আকার      = আকার(QSVDeviceContext),
    .frames_hwctx_আকার      = আকার(QSVFramesContext),

    .device_create          = qsv_device_create,
    .device_derive          = qsv_device_derive,
    .device_init            = qsv_device_init,
    .frames_get_constraints = qsv_frames_get_constraints,
    .frames_init            = qsv_frames_init,
    .frames_uninit          = qsv_frames_uninit,
    .frames_get_বাফার      = qsv_get_বাফার,
    .transfer_get_formats   = qsv_transfer_get_formats,
    .transfer_তথ্য_to       = qsv_transfer_তথ্য_to,
    .transfer_তথ্য_from     = qsv_transfer_তথ্য_from,
    .map_to                 = qsv_map_to,
    .map_from               = qsv_map_from,
    .frames_derive_to       = qsv_frames_derive_to,
    .frames_derive_from     = qsv_frames_derive_from,

    .pix_fmts = (ধ্রুবক গণনা AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
