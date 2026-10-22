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

#ضمن <stdatomic.h>
#ضمن <stdint.h>
#ضمن <string.h>

#ضمن <mfxvideo.h>

#ضمن "config.h"

#אם HAVE_PTHREADS
#ضمن <pthread.h>
#endif

#define COBJMACROS
#אם CONFIG_VAAPI
#ضمن "hwcontext_vaapi.h"
#endif
#אם CONFIG_D3D11VA
#ضمن "hwcontext_d3d11va.h"
#endif
#אם CONFIG_DXVA2
#ضمن <initguid.h>
#ضمن "hwcontext_dxva2.h"
#endif

#ضمن "buffer.h"
#ضمن "common.h"
#ضمن "hwcontext.h"
#ضمن "hwcontext_internal.h"
#ضمن "hwcontext_qsv.h"
#ضمن "mem.h"
#ضمن "pixfmt.h"
#ضمن "pixdesc.h"
#ضمن "time.h"
#ضمن "imgutils.h"
#ضمن "avassert.h"

#define QSV_VERSION_ATLEAST(MAJOR, MINOR)   \
    (MFX_VERSION_MAJOR > (MAJOR) ||         \
     MFX_VERSION_MAJOR == (MAJOR) && MFX_VERSION_MINOR >= (MINOR))

#define QSV_RUNTIME_VERSION_ATLEAST(MFX_VERSION, MAJOR, MINOR)          \
    ((MFX_VERSION.Major > (MAJOR)) ||                                   \
     (MFX_VERSION.Major == (MAJOR) && MFX_VERSION.Minor >= (MINOR)))

#define MFX_IMPL_VIA_MASK(impl) (0x0f00 & (impl))
#define QSV_ONEVPL       QSV_VERSION_ATLEAST(2, 0)
#define QSV_HAVE_OPAQUE  !QSV_ONEVPL

#אם QSV_ONEVPL
#ضمن <mfxdispatcher.h>
#אחרת
#define MFXUnload(a) עשה { } כלעוד(0)
#endif

تعريفنوع بنية QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

تعريفنوع بنية QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfxVersion          ver;
    mfxIMPL             impl;

    تعداد AVHWDeviceType child_device_type;
    تعداد AVPixelFormat  child_pix_fmt;
} QSVDeviceContext;

تعريفنوع بنية QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#אם HAVE_PTHREADS
    pthread_mutex_t session_lock;
#endif

    AVBufferRef *child_frames_ref;
    mfxFrameSurface1 *surfaces_internal;
    mfxHDLPair *handle_pairs_internal;
    صحيح             nb_surfaces_used;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#אם QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfxExtBuffer *ext_buffers[1];
#endif
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

تعريفنوع بنية QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

ساكن ثابت بنية {
    تعداد AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_shift;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#אם CONFIG_VAAPI
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
#אם QSV_VERSION_ATLEAST(1, 31)
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

خارجي صحيح ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          تعداد AVHWDeviceType base_dev_type,
                                          فراغ **base_handle);

ساكن صحيح qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
صحيح ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                   تعداد AVHWDeviceType base_dev_type,
                                   فراغ **base_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->Data.MemId;
    بدل (base_dev_type) {
#אם CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        base_handle[0] = handle_pair->first;
        החזר 0;
#endif
#אם CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        base_handle[0] = handle_pair->first;
        base_handle[1] = handle_pair->second;
        החזר 0;
#endif
#אם CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        base_handle[0] = handle_pair->first;
        החזר 0;
#endif
    }
    החזר AVERROR(EINVAL);
}

ساكن uint32_t qsv_fourcc_from_pix_fmt(تعداد AVPixelFormat pix_fmt)
{
    صحيح i;
    עבור (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        אם (supported_pixel_formats[i].pix_fmt == pix_fmt)
            החזר supported_pixel_formats[i].fourcc;
    }
    החזר 0;
}

ساكن uint16_t qsv_shift_from_pix_fmt(تعداد AVPixelFormat pix_fmt)
{
    עבור (صحيح i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        אם (supported_pixel_formats[i].pix_fmt == pix_fmt)
            החזר supported_pixel_formats[i].mfx_shift;
    }

    החזר 0;
}

#אם CONFIG_D3D11VA
ساكن uint32_t qsv_get_d3d11va_bind_flags(صحيح mem_type)
{
    uint32_t bind_flags = 0;

    אם ((mem_type & MFX_MEMTYPE_VIDEO_MEMORY_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_INTERNAL_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    אחרת
        bind_flags = D3D11_BIND_DECODER;

    אם ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    החזר bind_flags;
}
#endif

ساكن صحيح qsv_fill_border(AVFrame *dst, ثابت AVFrame *src)
{
    ثابت AVPixFmtDescriptor *desc;
    صحيح i, planes_nb = 0;
    אם (dst->format != src->format)
        החזר AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    עבור (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    עבור (i = 0; i < planes_nb; i++) {
        صحيح sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->width,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->width,
                                                 i);
        ثابت AVComponentDescriptor comp = desc->comp[i];
        אם (swidth < 0 || dwidth < 0) {
            av_log(عدم, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            החזר AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        אם (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        עבור (y = 0; y < sheight; y++) {
            فراغ *line_ptr = dst->data[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(line_ptr,
                           comp.depth > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        עבור (y = sheight; y < dheight; y++) {
            memcpy(dst->data[i]+y*dst->linesize[i],
                   dst->data[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    החזר 0;
}

ساكن صحيح qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    صحيح   hw_handle_supported = 0;
    mfxHandleType handle_type;
    تعداد AVHWDeviceType device_type;
    تعداد AVPixelFormat  pix_fmt;
    mfxStatus err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    אם (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    אם (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        החזר AVERROR_UNKNOWN;
    }

    אם (MFX_IMPL_VIA_VAAPI == MFX_IMPL_VIA_MASK(s->impl)) {
#אם CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#endif
    } אחרת אם (MFX_IMPL_VIA_D3D11 == MFX_IMPL_VIA_MASK(s->impl)) {
#אם CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#endif
    } אחרת אם (MFX_IMPL_VIA_D3D9 == MFX_IMPL_VIA_MASK(s->impl)) {
#אם CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#endif
    }

    אם (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        אם (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->child_device_type = device_type;
            s->child_pix_fmt     = pix_fmt;
        }
    }
    אם (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    החזר 0;
}

ساكن فراغ qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    אם (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = عدم;
    s->session_download_init = 0;

    אם (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = عدم;
    s->session_upload_init = 0;

#אם HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_lock);
#endif

    av_freep(&s->mem_ids);
#אם QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#endif
    av_freep(&s->surfaces_internal);
    av_freep(&s->handle_pairs_internal);
    av_frame_unref(&s->realigned_upload_frame);
    av_frame_unref(&s->realigned_download_frame);
    av_buffer_unref(&s->child_frames_ref);
}

ساكن فراغ qsv_pool_release_dummy(فراغ *opaque, uint8_t *data)
{
}

ساكن فراغ qsv_pool_release(فراغ *opaque, uint8_t *data)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)data;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.Data.MemId;
    AVHWFramesContext *child_frames_ctx;

    אם (!s->child_frames_ref)
        החזר;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    אם (!child_frames_ctx->device_ctx)
        החזר;

#אם CONFIG_VAAPI
    אם (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#endif

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

ساكن AVBufferRef *qsv_fixed_pool_alloc(فراغ *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    אם (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        החזר av_buffer_create((uint8_t*)(s->surfaces_internal + s->nb_surfaces_used - 1),
                                حجم(*hwctx->surfaces), qsv_pool_release_dummy, عدم, 0);
    }

    החזר عدم;
}

ساكن AVBufferRef *qsv_dynamic_pool_alloc(فراغ *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx;
    QSVSurface *qsv_surface = عدم;
    mfxHDLPair *handle_pairs_internal = عدم;
    صحيح ret;

    אם (!s->child_frames_ref)
        اذهب fail;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    אם (!child_frames_ctx->device_ctx)
        اذهب fail;

#אם CONFIG_DXVA2
    אם (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        اذهب fail;
    }
#endif

    qsv_surface = av_calloc(1, حجم(*qsv_surface));
    אם (!qsv_surface)
        اذهب fail;

    qsv_surface->child_frame = av_frame_alloc();
    אם (!qsv_surface->child_frame)
        اذهب fail;

    ret = av_hwframe_get_buffer(s->child_frames_ref, qsv_surface->child_frame, 0);
    אם (ret < 0)
        اذهب fail;

    handle_pairs_internal = av_calloc(1, حجم(*handle_pairs_internal));
    אם (!handle_pairs_internal)
        اذهب fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    אם (ret < 0)
        اذهب fail;

#אם CONFIG_VAAPI
    אם (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, حجم(*surface_id_internal));
        אם (!surface_id_internal)
            اذهب fail;

        *surface_id_internal = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
    }
#endif

#אם CONFIG_D3D11VA
    אם (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        handle_pairs_internal->first = (mfxMemId)qsv_surface->child_frame->data[0];

        אם (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        אחרת
            handle_pairs_internal->second = (mfxMemId)qsv_surface->child_frame->data[1];

    }
#endif

    qsv_surface->mfx_surface.Data.MemId = (mfxMemId)handle_pairs_internal;
    החזר av_buffer_create((uint8_t *)qsv_surface, حجم(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    אם (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_pairs_internal);

    החזר عدم;
}

ساكن AVBufferRef *qsv_pool_alloc(فراغ *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    אם (hwctx->nb_surfaces == 0) {
        החזר qsv_dynamic_pool_alloc(opaque, size);
    } אחרת {
        החזר qsv_fixed_pool_alloc(opaque, size);
    }
}

ساكن صحيح qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = عدم;
    AVBufferRef *child_frames_ref = عدم;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    صحيح i, ret = 0;

    אם (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        החזר AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    אם (!child_device_ref)
        החזר AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->data;

#אם CONFIG_VAAPI
    אם (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#endif
#אם CONFIG_D3D11VA
    אם (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        ID3D11Device_AddRef((ID3D11Device*)device_priv->handle);
        child_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#endif
#אם CONFIG_DXVA2
    אם (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#endif

    ret = av_hwdevice_ctx_init(child_device_ref);
    אם (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        اذهب fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    אם (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->data;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_size = ctx->initial_pool_size;
    child_frames_ctx->width             = FFALIGN(ctx->width, 16);
    child_frames_ctx->height            = FFALIGN(ctx->height, 16);

#אם CONFIG_D3D11VA
    אם (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        אם (hwctx->frame_type == 0)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        אם (hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
            child_frames_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        child_frames_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->frame_type);
    }
#endif
#אם CONFIG_DXVA2
    אם (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        אם (hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET)
            child_frames_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        אחרת
            child_frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#endif

    ret = av_hwframe_ctx_init(child_frames_ref);
    אם (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        اذهب fail;
    }

#אם CONFIG_VAAPI
    אם (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        עבור (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = child_frames_hwctx->surface_ids + i;
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif
#אם CONFIG_D3D11VA
    אם (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        עבור (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->texture_infos[i].texture;
            אם(child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            } אחרת {
                s->handle_pairs_internal[i].second = (mfxMemId)child_frames_hwctx->texture_infos[i].index;
            }
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        אם (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } אחרת {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
#endif
#אם CONFIG_DXVA2
    אם (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        עבור (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->surfaces[i];
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        אם (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        אחרת
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = عدم;

fail:
    av_buffer_unref(&child_device_ref);
    av_buffer_unref(&child_frames_ref);
    החזר ret;
}

ساكن صحيح qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    ثابت AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    אם (!desc)
        החזר AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    אם (!fourcc)
        החזר AVERROR(EINVAL);

    surf->Info.BitDepthLuma   = desc->comp[0].depth;
    surf->Info.BitDepthChroma = desc->comp[0].depth;
    surf->Info.Shift          = qsv_shift_from_pix_fmt(ctx->sw_format);

    אם (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    אחרת אם (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    אחרת
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.Width          = FFALIGN(ctx->width, 16);
    surf->Info.CropW          = ctx->width;
    surf->Info.Height         = FFALIGN(ctx->height, 16);
    surf->Info.CropH          = ctx->height;
    surf->Info.FrameRateExtN  = 25;
    surf->Info.FrameRateExtD  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    החזר 0;
}

ساكن صحيح qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    صحيح i, ret = 0;

    אם (ctx->initial_pool_size < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        החזר AVERROR(EINVAL);
    } אחרת אם (ctx->initial_pool_size == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        אם (ret < 0)
            החזר ret;

        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(حجم(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, عدم);
        אם (!ffhwframesctx(ctx)->pool_internal)
            החזר AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, حجم(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        frames_hwctx->info = &s->frame_info;
        frames_hwctx->nb_surfaces = 0;

        החזר 0;
    }

    s->handle_pairs_internal = av_calloc(ctx->initial_pool_size,
                                         حجم(*s->handle_pairs_internal));
    אם (!s->handle_pairs_internal)
        החזר AVERROR(ENOMEM);

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     حجم(*s->surfaces_internal));
    אם (!s->surfaces_internal)
        החזר AVERROR(ENOMEM);

    עבור (i = 0; i < ctx->initial_pool_size; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_internal[i]);
        אם (ret < 0)
            החזר ret;
    }

#אם QSV_HAVE_OPAQUE
    אם (!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        אם (ret < 0)
            החזר ret;
    }
#אחרת
    ret = qsv_init_child_ctx(ctx);
    אם (ret < 0)
        החזר ret;
#endif

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(حجم(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, عدم);
    אם (!ffhwframesctx(ctx)->pool_internal)
        החזר AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    החזר 0;
}

ساكن mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    אם (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        החזר MFX_ERR_UNSUPPORTED;
    אם (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        החזר MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->NumFrameActual = hwctx->nb_surfaces;

    החזר MFX_ERR_NONE;
}

ساكن mfxStatus frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    החזר MFX_ERR_NONE;
}

ساكن mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    החזר MFX_ERR_UNSUPPORTED;
}

ساكن mfxStatus frame_unlock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    החזר MFX_ERR_UNSUPPORTED;
}

ساكن mfxStatus frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    אם (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    החזר MFX_ERR_NONE;
}

#אם QSV_ONEVPL

ساكن صحيح qsv_d3d11_update_config(فراغ *ctx, mfxHDL handle, mfxConfig cfg)
{
    صحيح ret = AVERROR_UNKNOWN;
#אם CONFIG_D3D11VA
    mfxStatus sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = عدم;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_value = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (فراغ**)&pDXGIDevice);
    אם (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        אם (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            החזר ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        אם (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            اذهب fail;
        }
    } אחרת {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        החזר ret;
    }

    impl_value.Type = MFX_VARIANT_TYPE_U16;
    impl_value.Data.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_value);
    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        اذهب fail;
    }

    impl_value.Type = MFX_VARIANT_TYPE_PTR;
    impl_value.Data.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_value);
    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        اذهب fail;
    }

    impl_value.Type = MFX_VARIANT_TYPE_U32;
    impl_value.Data.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_value);
    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        اذهب fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#endif
    החזר ret;
}

ساكن صحيح qsv_d3d9_update_config(فراغ *ctx, mfxHDL handle, mfxConfig cfg)
{
    صحيح ret = AVERROR_UNKNOWN;
#אם CONFIG_DXVA2
    mfxStatus sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = عدم;
    IDirect3DDevice9Ex *device_ex = عدم;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = عدم;
    IDirect3D9 *d3d9 = عدم;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_value = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    אם (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        اذهب fail;
    }

    hr = IDirect3DDeviceManager9_LockDevice(devmgr, device_handle, &device, TRUE);
    אם (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        اذهب fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (فراغ **)&device_ex);
    IDirect3DDevice9_Release(device);
    אם (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        اذهب unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    אם (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        اذهب unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    אם (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        اذهب unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (فراغ **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    אם (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        اذهب unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    אם (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        اذهب release;
    }

    impl_value.Type = MFX_VARIANT_TYPE_PTR;
    impl_value.Data.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_value);
    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        اذهب release;
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
    החזר ret;
}

ساكن صحيح qsv_va_update_config(فراغ *ctx, mfxHDL handle, mfxConfig cfg)
{
#אם CONFIG_VAAPI
#אם VA_CHECK_VERSION(1, 15, 0)
    mfxStatus sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_value = {0};

    vas = vaGetDisplayAttributes(dpy, &attr, 1);
    אם (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_value.Type = MFX_VARIANT_TYPE_U16;
        impl_value.Data.U16 = (attr.value & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ثابت mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_value);
        אם (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            اذهب fail;
        }
    } אחרת {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        اذهب fail;
    }

    החזר 0;

fail:
#אחרת
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#endif
#endif
    החזר AVERROR_UNKNOWN;
}

ساكن صحيح qsv_new_mfx_loader(فراغ *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfxVersion *pver,
                              فراغ **ploader)
{
    mfxStatus sts;
    mfxLoader loader = عدم;
    mfxConfig cfg;
    mfxVariant impl_value = {0};

    *ploader = عدم;
    loader = MFXLoad();
    אם (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        اذهب fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    אם (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        اذهب fail;
    }

    impl_value.Type = MFX_VARIANT_TYPE_U32;
    impl_value.Data.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.Impl", impl_value);
    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        اذهب fail;
    }

    impl_value.Type = MFX_VARIANT_TYPE_U32;
    impl_value.Data.U32 = pver->Version;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_value);
    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        اذهب fail;
    }

    impl_value.Type = MFX_VARIANT_TYPE_U32;
    impl_value.Data.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.VendorID", impl_value);
    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        اذهب fail;
    }

    אם (MFX_HANDLE_VA_DISPLAY == handle_type) {
        אם (handle && qsv_va_update_config(ctx, handle, cfg))
            اذهب fail;

        impl_value.Data.U32 = MFX_ACCEL_MODE_VIA_VAAPI;
    } אחרת אם (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        אם (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            اذهب fail;

        impl_value.Data.U32 = MFX_ACCEL_MODE_VIA_D3D9;
    } אחרת {
        אם (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            اذهب fail;

        impl_value.Data.U32 = MFX_ACCEL_MODE_VIA_D3D11;
    }

    impl_value.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.AccelerationMode", impl_value);
    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        اذهب fail;
    }

    *ploader = loader;

    החזר 0;

fail:
    אם (loader)
        MFXUnload(loader);

    החזר AVERROR_UNKNOWN;
}

ساكن صحيح qsv_create_mfx_session_from_loader(فراغ *ctx, mfxLoader loader, mfxSession *psession)
{
    mfxStatus sts;
    mfxSession session = عدم;
    uint32_t impl_idx = 0;
    mfxVersion ver;

    כלעוד (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        אם (sts == MFX_ERR_NOT_FOUND)
            اكسر;
        אחרת אם (sts != MFX_ERR_NONE) {
            impl_idx++;
            استمر;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        אם (sts == MFX_ERR_NONE)
            اكسر;

        impl_idx++;
    }

    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        اذهب fail;
    }

    sts = MFXQueryVersion(session, &ver);
    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        اذهب fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    החזר 0;

fail:
    אם (session)
        MFXClose(session);

    החזר AVERROR_UNKNOWN;
}

ساكن صحيح qsv_create_mfx_session(فراغ *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  فراغ **ploader)
{
    mfxLoader loader = عدم;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    אם (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        החזר AVERROR(EXDEV);
    }

    *psession = عدم;

    אם (!*ploader) {
        אם (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (فراغ **)&loader))
            اذهب fail;

        av_assert0(loader);
    } אחרת
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    אם (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        اذهب fail;

    אם (!*ploader)
        *ploader = loader;

    החזר 0;

fail:
    אם (!*ploader && loader)
        MFXUnload(loader);

    החזר AVERROR_UNKNOWN;
}

#אחרת

ساكن صحيح qsv_create_mfx_session(فراغ *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  فراغ **ploader)
{
    mfxVersion ver;
    mfxStatus sts;
    mfxSession session = عدم;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    *ploader = عدم;
    *psession = عدم;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        اذهب fail;
    }

    sts = MFXQueryVersion(session, &ver);
    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        اذهب fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    אם (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        اذهب fail;
    }

    *psession = session;

    החזר 0;

fail:
    אם (session)
        MFXClose(session);

    החזר AVERROR_UNKNOWN;
}

#endif

ساكن صحيح qsv_init_internal_session(AVHWFramesContext *ctx,
                                     mfxSession *session, صحيح upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    صحيح opaque = 0;

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
    صحيح                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    فراغ             **loader = &hwctx->loader;
    mfxSession parent_session = hwctx->session;
    mfxIMPL impl;
    mfxVersion ver;

    err = MFXQueryIMPL(parent_session, &impl);
    אם (err == MFX_ERR_NONE)
        err = MFXQueryVersion(parent_session, &ver);
    אם (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        החזר AVERROR_UNKNOWN;
    }

#אם QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    אם (ret)
        اذهب fail;

    אם (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        אם (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            اذهب fail;
        }
    }

    אם (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        אם (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            اذهب fail;
        }
    }

    אם (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        אם (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            اذهب fail;
        }
    }

    memset(&par, 0, حجم(par));

    אם (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_OUT_VIDEO_MEMORY :
                                 MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
#אם QSV_HAVE_OPAQUE
    אחרת {
        par.ExtParam    = s->ext_buffers;
        par.NumExtParam = FF_ARRAY_ELEMS(s->ext_buffers);
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
    אם (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        اذهب fail;
    }

    החזר 0;

fail:
    אם (*session)
        MFXClose(*session);

    *session = عدم;

    החזר ret;
}

ساكن صحيح qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    صحيح opaque = 0;

    uint32_t fourcc;
    صحيح i, ret;

#אם QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    אם (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        החזר AVERROR(ENOSYS);
    }

    אם (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        אם (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            החזר ret;
        }
    }

    אם (!opaque) {
        s->mem_ids = av_calloc(frames_hwctx->nb_surfaces, حجم(*s->mem_ids));
        אם (!s->mem_ids)
            החזר AVERROR(ENOMEM);

        עבור (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].Data.MemId;
    }
#אם QSV_HAVE_OPAQUE
    אחרת {
        s->surface_ptrs = av_calloc(frames_hwctx->nb_surfaces,
                                    حجم(*s->surface_ptrs));
        אם (!s->surface_ptrs)
            החזר AVERROR(ENOMEM);

        עבור (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.NumSurface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = حجم(s->opaque_alloc);

        s->ext_buffers[0] = (mfxExtBuffer*)&s->opaque_alloc;
    }
#endif

    s->session_download = عدم;
    s->session_upload   = عدم;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#אם HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, عدم);
#endif

    החזר 0;
}

ساكن صحيح qsv_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    אם (!frame->buf[0])
        החזר AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_QSV;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    החזר 0;
}

ساكن صحيح qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    تعداد AVHWFrameTransferDirection dir,
                                    تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    אם (!fmts)
        החזר AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    החזר 0;
}

ساكن صحيح qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, صحيح flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    صحيح i;

    بدل (dst_ctx->device_ctx->type) {
#אם CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               حجم(*dst_hwctx->surface_ids));
            אם (!dst_hwctx->surface_ids)
                החזר AVERROR(ENOMEM);
            עבור (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        اكسر;
#endif
#אם CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_size = src_ctx->initial_pool_size;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 حجم(*dst_hwctx->texture_infos));
            אם (!dst_hwctx->texture_infos)
                החזר AVERROR(ENOMEM);
            אם (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            עבור (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].index = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            אם (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } אחרת
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        اكسر;
#endif
#אם CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            حجم(*dst_hwctx->surfaces));
            אם (!dst_hwctx->surfaces)
                החזר AVERROR(ENOMEM);
            עבור (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            אם (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            אחרת
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        اكسر;
#endif
    افتراضي:
        החזר AVERROR(ENOSYS);
    }

    החזר 0;
}

ساكن صحيح qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->data[3];
    AVHWFramesContext *child_frames_ctx;
    ثابت AVPixFmtDescriptor *desc;
    uint8_t *child_data;
    AVFrame *dummy;
    صحيح ret = 0;

    אם (!s->child_frames_ref)
        החזר AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;

    بدل (child_frames_ctx->device_ctx->type) {
#אם CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_data = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        اكسر;
    }
#endif
#אם CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        اكسر;
    }
#endif
#אם CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        اكسر;
    }
#endif
    افتراضي:
        החזר AVERROR(ENOSYS);
    }

    אם (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, عدم, عدم);
        אם (ret < 0)
            החזר ret;

        dst->width   = src->width;
        dst->height  = src->height;

       אם (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
            dst->data[0] = pair->first;
            dst->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } אחרת {
            dst->data[3] = child_data;
        }

        החזר 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    אם (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        החזר AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    אם (!dummy)
        החזר AVERROR(ENOMEM);

    dummy->buf[0]        = av_buffer_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_buffer_ref(s->child_frames_ref);
    אם (!dummy->buf[0] || !dummy->hw_frames_ctx)
        اذهب fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;

    אם (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        dummy->data[0] = pair->first;
        dummy->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } אחרת {
        dummy->data[3] = child_data;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    החזר ret;
}

ساكن صحيح qsv_transfer_data_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   ثابت AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    صحيح download = !!src->hw_frames_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->data[3] : dst->data[3]);

    AVFrame *dummy;
    صحيح ret;

    dummy = av_frame_alloc();
    אם (!dummy)
        החזר AVERROR(ENOMEM);

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->data[3]       = surf->Data.MemId;
    dummy->hw_frames_ctx = s->child_frames_ref;

    ret = download ? av_hwframe_transfer_data(dst, dummy, 0) :
                     av_hwframe_transfer_data(dummy, src, 0);

    dummy->buf[0]        = عدم;
    dummy->data[3]       = عدم;
    dummy->hw_frames_ctx = عدم;

    av_frame_free(&dummy);

    החזר ret;
}

ساكن صحيح map_frame_to_surface(ثابت AVFrame *frame, mfxFrameSurface1 *surface)
{
    بدل (frame->format) {
    حالة AV_PIX_FMT_NV12:
    حالة AV_PIX_FMT_P010:
    حالة AV_PIX_FMT_P012:
        surface->Data.Y  = frame->data[0];
        surface->Data.UV = frame->data[1];
        اكسر;

    حالة AV_PIX_FMT_YUV420P:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[1];
        surface->Data.V = frame->data[2];
        اكسر;

    حالة AV_PIX_FMT_BGRA:
        surface->Data.B = frame->data[0];
        surface->Data.G = frame->data[0] + 1;
        surface->Data.R = frame->data[0] + 2;
        surface->Data.A = frame->data[0] + 3;
        اكسر;
    حالة AV_PIX_FMT_YUYV422:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.V = frame->data[0] + 3;
        اكسر;

    حالة AV_PIX_FMT_Y210:
    حالة AV_PIX_FMT_Y212:
        surface->Data.Y16 = (mfxU16 *)frame->data[0];
        surface->Data.U16 = (mfxU16 *)frame->data[0] + 1;
        surface->Data.V16 = (mfxU16 *)frame->data[0] + 3;
        اكسر;
    حالة AV_PIX_FMT_VUYX:
        surface->Data.V = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.Y = frame->data[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 3;
        اكسر;
    حالة AV_PIX_FMT_XV30:
        surface->Data.U = frame->data[0];
        اكسر;
    حالة AV_PIX_FMT_XV36:
        surface->Data.U = frame->data[0];
        surface->Data.Y = frame->data[0] + 2;
        surface->Data.V = frame->data[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 6;
        اكسر;
#אם CONFIG_VAAPI
    حالة AV_PIX_FMT_UYVY422:
        surface->Data.Y = frame->data[0] + 1;
        surface->Data.U = frame->data[0];
        surface->Data.V = frame->data[0] + 2;
        اكسر;
#endif
    افتراضي:
        החזר MFX_ERR_UNSUPPORTED;
    }
    surface->Data.Pitch     = frame->linesize[0];
    surface->Data.TimeStamp = frame->pts;

    החזר 0;
}

ساكن صحيح qsv_internal_session_check_init(AVHWFramesContext *ctx, صحيح upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    صحيح ret = 0;

    אם (atomic_load(inited))
        החזר 0;

#אם HAVE_PTHREADS
    pthread_mutex_lock(&s->session_lock);
#endif

    אם (!atomic_load(inited)) {
        ret = qsv_init_internal_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#אם HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_lock);
#endif

    החזר ret;
}

ساكن صحيح qsv_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ثابت AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->data[3];

    mfxSyncPoint sync = عدم;
    mfxStatus err;
    صحيح ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    صحيح realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 0);
    אם (ret < 0)
        החזר ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    אם (dst->height & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        אם (tmp_frame->format != dst->format ||
            tmp_frame->width  != FFALIGN(dst->linesize[0], 16) ||
            tmp_frame->height != FFALIGN(dst->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = dst->format;
            tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
            tmp_frame->height = FFALIGN(dst->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            אם (ret < 0)
                החזר ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    אם (!s->session_download) {
        אם (s->child_frames_ref)
            החזר qsv_transfer_data_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        החזר AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst_frame, &out);

    עשה {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, عدم, &sync);
        אם (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } כלעוד (err == MFX_WRN_DEVICE_BUSY);

    אם (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        החזר AVERROR_UNKNOWN;
    }

    עשה {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } כלעוד (err == MFX_WRN_IN_EXECUTION);
    אם (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        החזר AVERROR_UNKNOWN;
    }

    אם (realigned) {
        tmp_frame->width  = dst->width;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        אם (ret < 0)
            החזר ret;
    }

    החזר 0;
}

ساكن صحيح qsv_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                ثابت AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   in = {{ 0 }};
    mfxFrameSurface1 *out = (mfxFrameSurface1*)dst->data[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = عدم;
    mfxStatus err;
    صحيح ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    ثابت AVFrame *src_frame;
    صحيح realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 1);
    אם (ret < 0)
        החזר ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    אם (src->height & 15 || src->linesize[0] & 15) {
        realigned = 1;
        אם (tmp_frame->format != src->format ||
            tmp_frame->width  != FFALIGN(src->width, 16) ||
            tmp_frame->height != FFALIGN(src->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = src->format;
            tmp_frame->width  = FFALIGN(src->width, 16);
            tmp_frame->height = FFALIGN(src->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            אם (ret < 0)
                החזר ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        אם (ret < 0) {
            av_frame_unref(tmp_frame);
            החזר ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        אם (ret < 0) {
            av_frame_unref(tmp_frame);
            החזר ret;
        }

        tmp_info = out->Info;
        out->Info.CropW = FFMIN(out->Info.Width,  tmp_frame->width);
        out->Info.CropH = FFMIN(out->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    אם (!s->session_upload) {
        אם (s->child_frames_ref)
            החזר qsv_transfer_data_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        החזר AVERROR(ENOSYS);
    }

    in.Info = out->Info;
    map_frame_to_surface(src_frame, &in);

    עשה {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_upload, &in, out, عدم, &sync);
        אם (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } כלעוד (err == MFX_WRN_DEVICE_BUSY);

    אם (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        החזר AVERROR_UNKNOWN;
    }

    עשה {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } כלעוד (err == MFX_WRN_IN_EXECUTION);
    אם (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        החזר AVERROR_UNKNOWN;
    }

    אם (realigned) {
        out->Info.CropW = tmp_info.CropW;
        out->Info.CropH = tmp_info.CropH;
    }

    החזר 0;
}

ساكن صحيح qsv_dynamic_frames_derive_to(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, صحيح flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    بدل (src_ctx->device_ctx->type) {
#אם CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        اكسر;
#endif

#אם CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        אם (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } אחרת {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
    اكسر;
#endif

    افتراضي:
        החזר AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, حجم(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    החזר 0;
}

ساكن صحيح qsv_fixed_frames_derive_to(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, صحيح flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    صحيح i;

    بدل (src_ctx->device_ctx->type) {
#אם CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 حجم(*s->handle_pairs_internal));
            אם (!s->handle_pairs_internal)
                החזר AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             حجم(*s->surfaces_internal));
            אם (!s->surfaces_internal)
                החזר AVERROR(ENOMEM);
            עבור (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = src_hwctx->surface_ids + i;
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        اكسر;
#endif
#אם CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 حجم(*s->handle_pairs_internal));
            אם (!s->handle_pairs_internal)
                החזר AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_ctx->initial_pool_size,
                                             حجم(*s->surfaces_internal));
            אם (!s->surfaces_internal)
                החזר AVERROR(ENOMEM);
            עבור (i = 0; i < src_ctx->initial_pool_size; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                אם (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                } אחרת {
                    s->handle_pairs_internal[i].second = (mfxMemId)src_hwctx->texture_infos[i].index;
                }
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_size;
            אם (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            } אחרת {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
            }
        }
        اكسر;
#endif
#אם CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 حجم(*s->handle_pairs_internal));
            אם (!s->handle_pairs_internal)
                החזר AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             حجم(*s->surfaces_internal));
            אם (!s->surfaces_internal)
                החזר AVERROR(ENOMEM);
            עבור (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            אם (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            אחרת
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        اكسر;
#endif
    افتراضي:
        החזר AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    החזר 0;
}

ساكن صحيح qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, صحيح flags)
{
    אם (src_ctx->initial_pool_size < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        החזר AVERROR(EINVAL);
    } אחרת אם (src_ctx->initial_pool_size == 0) {
        החזר qsv_dynamic_frames_derive_to(dst_ctx, src_ctx, flags);
    } אחרת {
        החזר qsv_fixed_frames_derive_to(dst_ctx, src_ctx, flags);
    }
}

ساكن صحيح qsv_fixed_pool_map_to(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    صحيح i, err, index = -1;

    עבור (i = 0; i < hwctx->nb_surfaces && index < 0; i++) {
        بدل(src->format) {
#אם CONFIG_VAAPI
        حالة AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            אם (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->data[3])
                index = i;
            اكسر;
        }
#endif
#אם CONFIG_D3D11VA
        حالة AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            אם (pair->first == src->data[0]
                && (pair->second == src->data[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->data[1] == (uint8_t *)0)))
                index = i;
            اكسر;
        }
#endif
#אם CONFIG_DXVA2
        حالة AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            אם (pair->first == src->data[3])
                index = i;
            اكسر;
        }
#endif
        }
    }
    אם (index < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        החזר AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, عدم, عدم);
    אם (err)
        החזר err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)&hwctx->surfaces[index];

    החזר 0;
}

ساكن فراغ qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_internal = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_pairs_internal = (mfxHDLPair *)surfaces_internal->Data.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_frames->data;

    بدل (src_ctx->format) {
#אם CONFIG_VAAPI
    حالة AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_pairs_internal->first);

        اكسر;
    }
#endif

#אם CONFIG_D3D11VA
    حالة AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        اكسر;
    }
#endif
    افتراضي:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        اكسر;
    }

    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
}

ساكن صحيح qsv_dynamic_pool_map_to(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    mfxFrameSurface1 *surfaces_internal = عدم;
    mfxHDLPair *handle_pairs_internal = عدم;
    صحيح ret = 0;

    surfaces_internal = av_calloc(1, حجم(*surfaces_internal));
    אם (!surfaces_internal) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    handle_pairs_internal = av_calloc(1, حجم(*handle_pairs_internal));
    אם (!handle_pairs_internal) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_internal);
    אם (ret < 0)
        اذهب fail;

    بدل (src->format) {
#אם CONFIG_VAAPI
    حالة AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, حجم(*surface_id_internal));
        אם (!surface_id_internal) {
            ret =AVERROR(ENOMEM);
            اذهب fail;
        }

        *surface_id_internal = (VASurfaceID)(uintptr_t)src->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;

        اكسر;
    }
#endif

#אם CONFIG_D3D11VA
    حالة AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_pairs_internal->first = (mfxMemId)src->data[0];

        אם (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        } אחרת {
            handle_pairs_internal->second = (mfxMemId)src->data[1];
        }

        اكسر;
    }
#endif
    افتراضي:
        ret = AVERROR(ENOSYS);
        اذهب fail;
    }

    surfaces_internal->Data.MemId = (mfxMemId)handle_pairs_internal;

    ret = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_internal);
    אם (ret)
        اذهب fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)surfaces_internal;

    החזר 0;

fail:
    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
    החזר ret;
}

ساكن صحيح qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    אם (hwctx->nb_surfaces)
        החזר qsv_fixed_pool_map_to(dst_ctx, dst, src, flags);
    אחרת
        החזר qsv_dynamic_pool_map_to(dst_ctx, dst, src, flags);
}

ساكن صحيح qsv_frames_get_constraints(AVHWDeviceContext *ctx,
                                      ثابت فراغ *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    صحيح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    אם (!constraints->valid_sw_formats)
        החזר AVERROR(ENOMEM);

    עבור (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    אם (!constraints->valid_hw_formats)
        החזר AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    החזר 0;
}

ساكن فراغ qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    אם (hwctx->session)
        MFXClose(hwctx->session);

    אם (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_buffer_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

ساكن mfxIMPL choose_implementation(ثابت حرف *device, تعداد AVHWDeviceType child_device_type)
{
    ساكن ثابت بنية {
        ثابت حرف *name;
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
    صحيح i;

    אם (device) {
        עבור (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            אם (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                اكسر;
            }
        אם (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, عدم, 0);
    }

    אם (impl != MFX_IMPL_SOFTWARE) {
        אם (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_VIA_D3D11;
        אחרת אם (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_VIA_D3D9;
    }

    החזר impl;
}

ساكن صحيح qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        صحيح flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfxVersion    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfxStatus     err;
    صحيح ret;

    بدل (child_device_ctx->type) {
#אם CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        اكسر;
#endif
#אם CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        اكسر;
#endif
#אם CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        اكسر;
#endif
    افتراضي:
        ret = AVERROR(ENOSYS);
        اذهب fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    אם (ret)
        اذهب fail;

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    אם (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        اذهب fail;
    }

    החזר 0;

fail:
    אם (hwctx->session)
        MFXClose(hwctx->session);

    אם (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = عدم;
    hwctx->loader = عدم;
    החזר ret;
}

ساكن صحيح qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, صحيح flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(حجم(*priv));
    אם (!priv)
        החזר AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->حرر = qsv_device_free;

    impl = choose_implementation("hw_any", child_device_ctx->type);
    החזר qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

ساكن صحيح qsv_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                             AVDictionary *opts, صحيح flags)
{
    QSVDevicePriv *priv;
    تعداد AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    صحيح ret;

    priv = av_mallocz(حجم(*priv));
    אם (!priv)
        החזר AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->حرر        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", عدم, 0);
    אם (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->value);
        אם (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->value);
            החזר AVERROR(EINVAL);
        }
#אם QSV_ONEVPL
    } אחרת אם (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } אחרת אם (CONFIG_DXVA2) {
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
#אחרת
    } אחרת אם (CONFIG_DXVA2) {
        av_log(عدم, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } אחרת אם (CONFIG_D3D11VA) {
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#endif
    } אחרת אם (CONFIG_VAAPI) {
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } אחרת {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        החזר AVERROR(ENOSYS);
    }

#אם CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    אם (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->value);
        החזר AVERROR(EINVAL);
    }
#endif

    child_device_opts = عدم;
    بدل (child_device_type) {
#אם CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_set(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_set(&child_device_opts, "driver",    "iHD",    0);
        }
        اكسر;
#endif
#אם CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_set(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        اكسر;
#endif
#אם CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
#אם QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#endif
        اكسر;
#endif
    افتراضي:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            החזר AVERROR(ENOSYS);
        }
        اكسر;
    }

    e = av_dict_get(opts, "child_device", عدم, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->value : عدم, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    אם (ret < 0)
        החזר ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->data;

    impl = choose_implementation(device, child_device_type);

    החזר qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

ثابت HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_size      = حجم(QSVDeviceContext),
    .frames_hwctx_size      = حجم(QSVFramesContext),

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

    .pix_fmts = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
