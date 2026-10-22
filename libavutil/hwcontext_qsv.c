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

#ಅನ್ತರ್ಭಾವ <stdatomic.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ <mfxvideo.h>

#ಅನ್ತರ್ಭಾವ "config.h"

#ಯದಿ HAVE_PTHREADS
#ಅನ್ತರ್ಭಾವ <pthread.h>
#endif

#define COBJMACROS
#ಯದಿ CONFIG_VAAPI
#ಅನ್ತರ್ಭಾವ "hwcontext_vaapi.h"
#endif
#ಯದಿ CONFIG_D3D11VA
#ಅನ್ತರ್ಭಾವ "hwcontext_d3d11va.h"
#endif
#ಯದಿ CONFIG_DXVA2
#ಅನ್ತರ್ಭಾವ <initguid.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_dxva2.h"
#endif

#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "hwcontext.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_internal.h"
#ಅನ್ತರ್ಭಾವ "hwcontext_qsv.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "pixfmt.h"
#ಅನ್ತರ್ಭಾವ "pixdesc.h"
#ಅನ್ತರ್ಭಾವ "time.h"
#ಅನ್ತರ್ಭಾವ "imgutils.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"

#define QSV_VERSION_ATLEAST(MAJOR, MINOR)   \
    (MFX_VERSION_MAJOR > (MAJOR) ||         \
     MFX_VERSION_MAJOR == (MAJOR) && MFX_VERSION_MINOR >= (MINOR))

#define QSV_RUNTIME_VERSION_ATLEAST(MFX_VERSION, MAJOR, MINOR)          \
    ((MFX_VERSION.Major > (MAJOR)) ||                                   \
     (MFX_VERSION.Major == (MAJOR) && MFX_VERSION.Minor >= (MINOR)))

#define MFX_IMPL_VIA_MASK(impl) (0x0f00 & (impl))
#define QSV_ONEVPL       QSV_VERSION_ATLEAST(2, 0)
#define QSV_HAVE_OPAQUE  !QSV_ONEVPL

#ಯದಿ QSV_ONEVPL
#ಅನ್ತರ್ಭಾವ <mfxdispatcher.h>
#ಅನ್ಯಥಾ
#define MFXUnload(a) ಕುರು { } ಯಾವತ್(0)
#endif

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfxVersion          ver;
    mfxIMPL             impl;

    ಗಣನಾ AVHWDeviceType child_device_type;
    ಗಣನಾ AVPixelFormat  child_pix_fmt;
} QSVDeviceContext;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#ಯದಿ HAVE_PTHREADS
    pthread_mutex_t session_lock;
#endif

    AVBufferRef *child_frames_ref;
    mfxFrameSurface1 *surfaces_internal;
    mfxHDLPair *handle_pairs_internal;
    ಪೂರ್ಣಾಙ್ಕ             nb_surfaces_used;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#ಯದಿ QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfxExtBuffer *ext_buffers[1];
#endif
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    ಗಣನಾ AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_shift;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#ಯದಿ CONFIG_VAAPI
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
#ಯದಿ QSV_VERSION_ATLEAST(1, 31)
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

ಬಾಹ್ಯ ಪೂರ್ಣಾಙ್ಕ ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          ಗಣನಾ AVHWDeviceType base_dev_type,
                                          ಶೂನ್ಯ **base_handle);

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
ಪೂರ್ಣಾಙ್ಕ ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                   ಗಣನಾ AVHWDeviceType base_dev_type,
                                   ಶೂನ್ಯ **base_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->Data.MemId;
    ವಿಕಲ್ಪ (base_dev_type) {
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VAAPI:
        base_handle[0] = handle_pair->first;
        ಪ್ರತ್ಯಾಗಮ 0;
#endif
#ಯದಿ CONFIG_D3D11VA
    ಪಕ್ಷ AV_HWDEVICE_TYPE_D3D11VA:
        base_handle[0] = handle_pair->first;
        base_handle[1] = handle_pair->second;
        ಪ್ರತ್ಯಾಗಮ 0;
#endif
#ಯದಿ CONFIG_DXVA2
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DXVA2:
        base_handle[0] = handle_pair->first;
        ಪ್ರತ್ಯಾಗಮ 0;
#endif
    }
    ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
}

ಸ್ಥಿರ uint32_t qsv_fourcc_from_pix_fmt(ಗಣನಾ AVPixelFormat pix_fmt)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        ಯದಿ (supported_pixel_formats[i].pix_fmt == pix_fmt)
            ಪ್ರತ್ಯಾಗಮ supported_pixel_formats[i].fourcc;
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ uint16_t qsv_shift_from_pix_fmt(ಗಣನಾ AVPixelFormat pix_fmt)
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        ಯದಿ (supported_pixel_formats[i].pix_fmt == pix_fmt)
            ಪ್ರತ್ಯಾಗಮ supported_pixel_formats[i].mfx_shift;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

#ಯದಿ CONFIG_D3D11VA
ಸ್ಥಿರ uint32_t qsv_get_d3d11va_bind_flags(ಪೂರ್ಣಾಙ್ಕ mem_type)
{
    uint32_t bind_flags = 0;

    ಯದಿ ((mem_type & MFX_MEMTYPE_VIDEO_MEMORY_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_INTERNAL_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    ಅನ್ಯಥಾ
        bind_flags = D3D11_BIND_DECODER;

    ಯದಿ ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    ಪ್ರತ್ಯಾಗಮ bind_flags;
}
#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_fill_border(AVFrame *dst, ಧ್ರುವ AVFrame *src)
{
    ಧ್ರುವ AVPixFmtDescriptor *desc;
    ಪೂರ್ಣಾಙ್ಕ i, planes_nb = 0;
    ಯದಿ (dst->format != src->format)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    ಪ್ರತಿ (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    ಪ್ರತಿ (i = 0; i < planes_nb; i++) {
        ಪೂರ್ಣಾಙ್ಕ sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->width,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->width,
                                                 i);
        ಧ್ರುವ AVComponentDescriptor comp = desc->comp[i];
        ಯದಿ (swidth < 0 || dwidth < 0) {
            av_log(ರಿಕ್ತ, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        ಯದಿ (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        ಪ್ರತಿ (y = 0; y < sheight; y++) {
            ಶೂನ್ಯ *ಸಾಲು_ptr = dst->data[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(ಸಾಲು_ptr,
                           comp.depth > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        ಪ್ರತಿ (y = sheight; y < dheight; y++) {
            memcpy(dst->data[i]+y*dst->linesize[i],
                   dst->data[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    ಪೂರ್ಣಾಙ್ಕ   hw_handle_supported = 0;
    mfxHandleType handle_type;
    ಗಣನಾ AVHWDeviceType device_type;
    ಗಣನಾ AVPixelFormat  pix_fmt;
    mfxStatus err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    ಯದಿ (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    ಯದಿ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಯದಿ (MFX_IMPL_VIA_VAAPI == MFX_IMPL_VIA_MASK(s->impl)) {
#ಯದಿ CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#endif
    } ಅನ್ಯಥಾ ಯದಿ (MFX_IMPL_VIA_D3D11 == MFX_IMPL_VIA_MASK(s->impl)) {
#ಯದಿ CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#endif
    } ಅನ್ಯಥಾ ಯದಿ (MFX_IMPL_VIA_D3D9 == MFX_IMPL_VIA_MASK(s->impl)) {
#ಯದಿ CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#endif
    }

    ಯದಿ (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        ಯದಿ (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->child_device_type = device_type;
            s->child_pix_fmt     = pix_fmt;
        }
    }
    ಯದಿ (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    ಯದಿ (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = ರಿಕ್ತ;
    s->session_download_init = 0;

    ಯದಿ (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = ರಿಕ್ತ;
    s->session_upload_init = 0;

#ಯದಿ HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_lock);
#endif

    av_freep(&s->mem_ids);
#ಯದಿ QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#endif
    av_freep(&s->surfaces_internal);
    av_freep(&s->handle_pairs_internal);
    av_frame_unref(&s->realigned_upload_frame);
    av_frame_unref(&s->realigned_download_frame);
    av_buffer_unref(&s->child_frames_ref);
}

ಸ್ಥಿರ ಶೂನ್ಯ qsv_pool_release_dummy(ಶೂನ್ಯ *opaque, uint8_t *data)
{
}

ಸ್ಥಿರ ಶೂನ್ಯ qsv_pool_release(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)data;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.Data.MemId;
    AVHWFramesContext *child_frames_ctx;

    ಯದಿ (!s->child_frames_ref)
        ಪ್ರತ್ಯಾಗಮ;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    ಯದಿ (!child_frames_ctx->device_ctx)
        ಪ್ರತ್ಯಾಗಮ;

#ಯದಿ CONFIG_VAAPI
    ಯದಿ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#endif

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

ಸ್ಥಿರ AVBufferRef *qsv_fixed_pool_alloc(ಶೂನ್ಯ *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    ಯದಿ (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        ಪ್ರತ್ಯಾಗಮ av_buffer_create((uint8_t*)(s->surfaces_internal + s->nb_surfaces_used - 1),
                                ಪರಿಮಾಣ(*hwctx->surfaces), qsv_pool_release_dummy, ರಿಕ್ತ, 0);
    }

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ AVBufferRef *qsv_dynamic_pool_alloc(ಶೂನ್ಯ *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx;
    QSVSurface *qsv_surface = ರಿಕ್ತ;
    mfxHDLPair *handle_pairs_internal = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!s->child_frames_ref)
        ಗಚ್ಛ fail;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    ಯದಿ (!child_frames_ctx->device_ctx)
        ಗಚ್ಛ fail;

#ಯದಿ CONFIG_DXVA2
    ಯದಿ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        ಗಚ್ಛ fail;
    }
#endif

    qsv_surface = av_calloc(1, ಪರಿಮಾಣ(*qsv_surface));
    ಯದಿ (!qsv_surface)
        ಗಚ್ಛ fail;

    qsv_surface->child_frame = av_frame_alloc();
    ಯದಿ (!qsv_surface->child_frame)
        ಗಚ್ಛ fail;

    ret = av_hwframe_get_buffer(s->child_frames_ref, qsv_surface->child_frame, 0);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    handle_pairs_internal = av_calloc(1, ಪರಿಮಾಣ(*handle_pairs_internal));
    ಯದಿ (!handle_pairs_internal)
        ಗಚ್ಛ fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

#ಯದಿ CONFIG_VAAPI
    ಯದಿ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, ಪರಿಮಾಣ(*surface_id_internal));
        ಯದಿ (!surface_id_internal)
            ಗಚ್ಛ fail;

        *surface_id_internal = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
    }
#endif

#ಯದಿ CONFIG_D3D11VA
    ಯದಿ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        handle_pairs_internal->first = (mfxMemId)qsv_surface->child_frame->data[0];

        ಯದಿ (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        ಅನ್ಯಥಾ
            handle_pairs_internal->second = (mfxMemId)qsv_surface->child_frame->data[1];

    }
#endif

    qsv_surface->mfx_surface.Data.MemId = (mfxMemId)handle_pairs_internal;
    ಪ್ರತ್ಯಾಗಮ av_buffer_create((uint8_t *)qsv_surface, ಪರಿಮಾಣ(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    ಯದಿ (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_pairs_internal);

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ AVBufferRef *qsv_pool_alloc(ಶೂನ್ಯ *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    ಯದಿ (hwctx->nb_surfaces == 0) {
        ಪ್ರತ್ಯಾಗಮ qsv_dynamic_pool_alloc(opaque, size);
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ qsv_fixed_pool_alloc(opaque, size);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = ರಿಕ್ತ;
    AVBufferRef *child_frames_ref = ರಿಕ್ತ;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    ಪೂರ್ಣಾಙ್ಕ i, ret = 0;

    ಯದಿ (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    ಯದಿ (!child_device_ref)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->data;

#ಯದಿ CONFIG_VAAPI
    ಯದಿ (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#endif
#ಯದಿ CONFIG_D3D11VA
    ಯದಿ (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        ID3D11Device_AddRef((ID3D11Device*)device_priv->handle);
        child_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#endif
#ಯದಿ CONFIG_DXVA2
    ಯದಿ (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#endif

    ret = av_hwdevice_ctx_init(child_device_ref);
    ಯದಿ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        ಗಚ್ಛ fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    ಯದಿ (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->data;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_size = ctx->initial_pool_size;
    child_frames_ctx->width             = FFALIGN(ctx->width, 16);
    child_frames_ctx->height            = FFALIGN(ctx->height, 16);

#ಯದಿ CONFIG_D3D11VA
    ಯದಿ (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        ಯದಿ (hwctx->frame_type == 0)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        ಯದಿ (hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
            child_frames_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        child_frames_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->frame_type);
    }
#endif
#ಯದಿ CONFIG_DXVA2
    ಯದಿ (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        ಯದಿ (hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET)
            child_frames_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        ಅನ್ಯಥಾ
            child_frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#endif

    ret = av_hwframe_ctx_init(child_frames_ref);
    ಯದಿ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        ಗಚ್ಛ fail;
    }

#ಯದಿ CONFIG_VAAPI
    ಯದಿ (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        ಪ್ರತಿ (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = child_frames_hwctx->surface_ids + i;
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif
#ಯದಿ CONFIG_D3D11VA
    ಯದಿ (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        ಪ್ರತಿ (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->texture_infos[i].texture;
            ಯದಿ(child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            } ಅನ್ಯಥಾ {
                s->handle_pairs_internal[i].second = (mfxMemId)child_frames_hwctx->texture_infos[i].index;
            }
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        ಯದಿ (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } ಅನ್ಯಥಾ {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
#endif
#ಯದಿ CONFIG_DXVA2
    ಯದಿ (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        ಪ್ರತಿ (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->surfaces[i];
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        ಯದಿ (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        ಅನ್ಯಥಾ
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = ರಿಕ್ತ;

fail:
    av_buffer_unref(&child_device_ref);
    av_buffer_unref(&child_frames_ref);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    ಧ್ರುವ AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    ಯದಿ (!desc)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    ಯದಿ (!fourcc)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    surf->Info.BitDepthLuma   = desc->comp[0].depth;
    surf->Info.BitDepthChroma = desc->comp[0].depth;
    surf->Info.Shift          = qsv_shift_from_pix_fmt(ctx->sw_format);

    ಯದಿ (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    ಅನ್ಯಥಾ ಯದಿ (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    ಅನ್ಯಥಾ
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.Width          = FFALIGN(ctx->width, 16);
    surf->Info.CropW          = ctx->width;
    surf->Info.Height         = FFALIGN(ctx->height, 16);
    surf->Info.CropH          = ctx->height;
    surf->Info.FrameRateExtN  = 25;
    surf->Info.FrameRateExtD  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    ಪೂರ್ಣಾಙ್ಕ i, ret = 0;

    ಯದಿ (ctx->initial_pool_size < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    } ಅನ್ಯಥಾ ಯದಿ (ctx->initial_pool_size == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;

        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(ಪರಿಮಾಣ(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, ರಿಕ್ತ);
        ಯದಿ (!ffhwframesctx(ctx)->pool_internal)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, ಪರಿಮಾಣ(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        frames_hwctx->info = &s->frame_info;
        frames_hwctx->nb_surfaces = 0;

        ಪ್ರತ್ಯಾಗಮ 0;
    }

    s->handle_pairs_internal = av_calloc(ctx->initial_pool_size,
                                         ಪರಿಮಾಣ(*s->handle_pairs_internal));
    ಯದಿ (!s->handle_pairs_internal)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     ಪರಿಮಾಣ(*s->surfaces_internal));
    ಯದಿ (!s->surfaces_internal)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (i = 0; i < ctx->initial_pool_size; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_internal[i]);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
    }

#ಯದಿ QSV_HAVE_OPAQUE
    ಯದಿ (!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
    }
#ಅನ್ಯಥಾ
    ret = qsv_init_child_ctx(ctx);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;
#endif

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(ಪರಿಮಾಣ(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, ರಿಕ್ತ);
    ಯದಿ (!ffhwframesctx(ctx)->pool_internal)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    ಯದಿ (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        ಪ್ರತ್ಯಾಗಮ MFX_ERR_UNSUPPORTED;
    ಯದಿ (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        ಪ್ರತ್ಯಾಗಮ MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->ಅಂಕೆ_Frame_Actual = hwctx->nb_surfaces;

    ಪ್ರತ್ಯಾಗಮ MFX_ERR_NONE;
}

ಸ್ಥಿರ mfxStatus frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    ಪ್ರತ್ಯಾಗಮ MFX_ERR_NONE;
}

ಸ್ಥಿರ mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    ಪ್ರತ್ಯಾಗಮ MFX_ERR_UNSUPPORTED;
}

ಸ್ಥಿರ mfxStatus frame_unlock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    ಪ್ರತ್ಯಾಗಮ MFX_ERR_UNSUPPORTED;
}

ಸ್ಥಿರ mfxStatus frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    ಯದಿ (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    ಪ್ರತ್ಯಾಗಮ MFX_ERR_NONE;
}

#ಯದಿ QSV_ONEVPL

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_d3d11_update_config(ಶೂನ್ಯ *ctx, mfxHDL handle, mfxConfig cfg)
{
    ಪೂರ್ಣಾಙ್ಕ ret = AVERROR_UNKNOWN;
#ಯದಿ CONFIG_D3D11VA
    mfxStatus sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = ರಿಕ್ತ;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_ಮೌಲ್ಯ = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (ಶೂನ್ಯ**)&pDXGIDevice);
    ಯದಿ (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        ಯದಿ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            ಪ್ರತ್ಯಾಗಮ ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        ಯದಿ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            ಗಚ್ಛ fail;
        }
    } ಅನ್ಯಥಾ {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        ಪ್ರತ್ಯಾಗಮ ret;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U16;
    impl_ಮೌಲ್ಯ.Data.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಧ್ರುವ mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_ಮೌಲ್ಯ);
    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        ಗಚ್ಛ fail;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_PTR;
    impl_ಮೌಲ್ಯ.Data.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಧ್ರುವ mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_ಮೌಲ್ಯ);
    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        ಗಚ್ಛ fail;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U32;
    impl_ಮೌಲ್ಯ.Data.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಧ್ರುವ mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_ಮೌಲ್ಯ);
    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        ಗಚ್ಛ fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#endif
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_d3d9_update_config(ಶೂನ್ಯ *ctx, mfxHDL handle, mfxConfig cfg)
{
    ಪೂರ್ಣಾಙ್ಕ ret = AVERROR_UNKNOWN;
#ಯದಿ CONFIG_DXVA2
    mfxStatus sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = ರಿಕ್ತ;
    IDirect3DDevice9Ex *device_ex = ರಿಕ್ತ;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = ರಿಕ್ತ;
    IDirect3D9 *d3d9 = ರಿಕ್ತ;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_ಮೌಲ್ಯ = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        ಗಚ್ಛ fail;
    }

    hr = IDirect3DDeviceManager9_LockDevice(devmgr, device_handle, &device, TRUE);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        ಗಚ್ಛ fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (ಶೂನ್ಯ **)&device_ex);
    IDirect3DDevice9_Release(device);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        ಗಚ್ಛ unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        ಗಚ್ಛ unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        ಗಚ್ಛ unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (ಶೂನ್ಯ **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        ಗಚ್ಛ unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    ಯದಿ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        ಗಚ್ಛ release;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_PTR;
    impl_ಮೌಲ್ಯ.Data.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಧ್ರುವ mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_ಮೌಲ್ಯ);
    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        ಗಚ್ಛ release;
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
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_va_update_config(ಶೂನ್ಯ *ctx, mfxHDL handle, mfxConfig cfg)
{
#ಯದಿ CONFIG_VAAPI
#ಯದಿ VA_CHECK_VERSION(1, 15, 0)
    mfxStatus sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_ಮೌಲ್ಯ = {0};

    vas = vaGetDisplayAttributes(dpy, &attr, 1);
    ಯದಿ (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U16;
        impl_ಮೌಲ್ಯ.Data.U16 = (attr.ಮೌಲ್ಯ & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ಧ್ರುವ mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_ಮೌಲ್ಯ);
        ಯದಿ (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            ಗಚ್ಛ fail;
        }
    } ಅನ್ಯಥಾ {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        ಗಚ್ಛ fail;
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
#ಅನ್ಯಥಾ
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#endif
#endif
    ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_new_mfx_loader(ಶೂನ್ಯ *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfxVersion *pver,
                              ಶೂನ್ಯ **ploader)
{
    mfxStatus sts;
    mfxLoader loader = ರಿಕ್ತ;
    mfxConfig cfg;
    mfxVariant impl_ಮೌಲ್ಯ = {0};

    *ploader = ರಿಕ್ತ;
    loader = MFXLoad();
    ಯದಿ (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        ಗಚ್ಛ fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    ಯದಿ (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        ಗಚ್ಛ fail;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U32;
    impl_ಮೌಲ್ಯ.Data.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಧ್ರುವ mfxU8 *)"mfxImplDescription.Impl", impl_ಮೌಲ್ಯ);
    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        ಗಚ್ಛ fail;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U32;
    impl_ಮೌಲ್ಯ.Data.U32 = pver->Version;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಧ್ರುವ mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_ಮೌಲ್ಯ);
    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        ಗಚ್ಛ fail;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U32;
    impl_ಮೌಲ್ಯ.Data.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಧ್ರುವ mfxU8 *)"mfxImplDescription.VendorID", impl_ಮೌಲ್ಯ);
    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        ಗಚ್ಛ fail;
    }

    ಯದಿ (MFX_HANDLE_VA_DISPLAY == handle_type) {
        ಯದಿ (handle && qsv_va_update_config(ctx, handle, cfg))
            ಗಚ್ಛ fail;

        impl_ಮೌಲ್ಯ.Data.U32 = MFX_ACCEL_MODE_VIA_VAAPI;
    } ಅನ್ಯಥಾ ಯದಿ (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        ಯದಿ (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            ಗಚ್ಛ fail;

        impl_ಮೌಲ್ಯ.Data.U32 = MFX_ACCEL_MODE_VIA_D3D9;
    } ಅನ್ಯಥಾ {
        ಯದಿ (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            ಗಚ್ಛ fail;

        impl_ಮೌಲ್ಯ.Data.U32 = MFX_ACCEL_MODE_VIA_D3D11;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಧ್ರುವ mfxU8 *)"mfxImplDescription.AccelerationMode", impl_ಮೌಲ್ಯ);
    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        ಗಚ್ಛ fail;
    }

    *ploader = loader;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಯದಿ (loader)
        MFXUnload(loader);

    ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_create_mfx_session_from_loader(ಶೂನ್ಯ *ctx, mfxLoader loader, mfxSession *psession)
{
    mfxStatus sts;
    mfxSession session = ರಿಕ್ತ;
    uint32_t impl_idx = 0;
    mfxVersion ver;

    ಯಾವತ್ (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        ಯದಿ (sts == MFX_ERR_NOT_FOUND)
            ಭಙ್ಗ;
        ಅನ್ಯಥಾ ಯದಿ (sts != MFX_ERR_NONE) {
            impl_idx++;
            ಅನುವರ್ತ;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        ಯದಿ (sts == MFX_ERR_NONE)
            ಭಙ್ಗ;

        impl_idx++;
    }

    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        ಗಚ್ಛ fail;
    }

    sts = MFXQueryVersion(session, &ver);
    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        ಗಚ್ಛ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಯದಿ (session)
        MFXClose(session);

    ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_create_mfx_session(ಶೂನ್ಯ *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  ಶೂನ್ಯ **ploader)
{
    mfxLoader loader = ರಿಕ್ತ;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    ಯದಿ (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EXDEV);
    }

    *psession = ರಿಕ್ತ;

    ಯದಿ (!*ploader) {
        ಯದಿ (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (ಶೂನ್ಯ **)&loader))
            ಗಚ್ಛ fail;

        av_assert0(loader);
    } ಅನ್ಯಥಾ
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    ಯದಿ (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        ಗಚ್ಛ fail;

    ಯದಿ (!*ploader)
        *ploader = loader;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಯದಿ (!*ploader && loader)
        MFXUnload(loader);

    ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
}

#ಅನ್ಯಥಾ

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_create_mfx_session(ಶೂನ್ಯ *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  ಶೂನ್ಯ **ploader)
{
    mfxVersion ver;
    mfxStatus sts;
    mfxSession session = ರಿಕ್ತ;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    *ploader = ರಿಕ್ತ;
    *psession = ರಿಕ್ತ;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        ಗಚ್ಛ fail;
    }

    sts = MFXQueryVersion(session, &ver);
    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        ಗಚ್ಛ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    ಯದಿ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        ಗಚ್ಛ fail;
    }

    *psession = session;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಯದಿ (session)
        MFXClose(session);

    ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
}

#endif

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_init_internal_session(AVHWFramesContext *ctx,
                                     mfxSession *session, ಪೂರ್ಣಾಙ್ಕ upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    ಪೂರ್ಣಾಙ್ಕ opaque = 0;

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
    ಪೂರ್ಣಾಙ್ಕ                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    ಶೂನ್ಯ             **loader = &hwctx->loader;
    mfxSession parent_session = hwctx->session;
    mfxIMPL impl;
    mfxVersion ver;

    err = MFXQueryIMPL(parent_session, &impl);
    ಯದಿ (err == MFX_ERR_NONE)
        err = MFXQueryVersion(parent_session, &ver);
    ಯದಿ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

#ಯದಿ QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    ಯದಿ (ret)
        ಗಚ್ಛ fail;

    ಯದಿ (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        ಯದಿ (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            ಗಚ್ಛ fail;
        }
    }

    ಯದಿ (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        ಯದಿ (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            ಗಚ್ಛ fail;
        }
    }

    ಯದಿ (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        ಯದಿ (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            ಗಚ್ಛ fail;
        }
    }

    memset(&par, 0, ಪರಿಮಾಣ(par));

    ಯದಿ (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_OUT_VIDEO_MEMORY :
                                 MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
#ಯದಿ QSV_HAVE_OPAQUE
    ಅನ್ಯಥಾ {
        par.ExtParam    = s->ext_buffers;
        par.ಅಂಕೆ_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
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
    ಯದಿ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        ಗಚ್ಛ fail;
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಯದಿ (*session)
        MFXClose(*session);

    *session = ರಿಕ್ತ;

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    ಪೂರ್ಣಾಙ್ಕ opaque = 0;

    uint32_t fourcc;
    ಪೂರ್ಣಾಙ್ಕ i, ret;

#ಯದಿ QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    ಯದಿ (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    ಯದಿ (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        ಯದಿ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            ಪ್ರತ್ಯಾಗಮ ret;
        }
    }

    ಯದಿ (!opaque) {
        s->mem_ids = av_calloc(frames_hwctx->nb_surfaces, ಪರಿಮಾಣ(*s->mem_ids));
        ಯದಿ (!s->mem_ids)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        ಪ್ರತಿ (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].Data.MemId;
    }
#ಯದಿ QSV_HAVE_OPAQUE
    ಅನ್ಯಥಾ {
        s->surface_ptrs = av_calloc(frames_hwctx->nb_surfaces,
                                    ಪರಿಮಾಣ(*s->surface_ptrs));
        ಯದಿ (!s->surface_ptrs)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        ಪ್ರತಿ (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.ಅಂಕೆ_Surface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = ಪರಿಮಾಣ(s->opaque_alloc);

        s->ext_buffers[0] = (mfxExtBuffer*)&s->opaque_alloc;
    }
#endif

    s->session_download = ರಿಕ್ತ;
    s->session_upload   = ರಿಕ್ತ;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#ಯದಿ HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, ರಿಕ್ತ);
#endif

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ಯದಿ (!frame->buf[0])
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_QSV;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    ಗಣನಾ AVHWFrameTransferDirection dir,
                                    ಗಣನಾ AVPixelFormat **formats)
{
    ಗಣನಾ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ಪರಿಮಾಣ(*fmts));
    ಯದಿ (!fmts)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    ಪೂರ್ಣಾಙ್ಕ i;

    ವಿಕಲ್ಪ (dst_ctx->device_ctx->type) {
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               ಪರಿಮಾಣ(*dst_hwctx->surface_ids));
            ಯದಿ (!dst_hwctx->surface_ids)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            ಪ್ರತಿ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        ಭಙ್ಗ;
#endif
#ಯದಿ CONFIG_D3D11VA
    ಪಕ್ಷ AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_size = src_ctx->initial_pool_size;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 ಪರಿಮಾಣ(*dst_hwctx->texture_infos));
            ಯದಿ (!dst_hwctx->texture_infos)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            ಯದಿ (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            ಪ್ರತಿ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].index = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            ಯದಿ (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } ಅನ್ಯಥಾ
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        ಭಙ್ಗ;
#endif
#ಯದಿ CONFIG_DXVA2
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            ಪರಿಮಾಣ(*dst_hwctx->surfaces));
            ಯದಿ (!dst_hwctx->surfaces)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            ಪ್ರತಿ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            ಯದಿ (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            ಅನ್ಯಥಾ
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        ಭಙ್ಗ;
#endif
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->data[3];
    AVHWFramesContext *child_frames_ctx;
    ಧ್ರುವ AVPixFmtDescriptor *desc;
    uint8_t *child_data;
    AVFrame *dummy;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    ಯದಿ (!s->child_frames_ref)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;

    ವಿಕಲ್ಪ (child_frames_ctx->device_ctx->type) {
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_data = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        ಭಙ್ಗ;
    }
#endif
#ಯದಿ CONFIG_D3D11VA
    ಪಕ್ಷ AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        ಭಙ್ಗ;
    }
#endif
#ಯದಿ CONFIG_DXVA2
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        ಭಙ್ಗ;
    }
#endif
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    ಯದಿ (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, ರಿಕ್ತ, ರಿಕ್ತ);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;

        dst->width   = src->width;
        dst->height  = src->height;

       ಯದಿ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
            dst->data[0] = pair->first;
            dst->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } ಅನ್ಯಥಾ {
            dst->data[3] = child_data;
        }

        ಪ್ರತ್ಯಾಗಮ 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    ಯದಿ (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    ಯದಿ (!dummy)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    dummy->buf[0]        = av_buffer_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_buffer_ref(s->child_frames_ref);
    ಯದಿ (!dummy->buf[0] || !dummy->hw_frames_ctx)
        ಗಚ್ಛ fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;

    ಯದಿ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        dummy->data[0] = pair->first;
        dummy->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } ಅನ್ಯಥಾ {
        dummy->data[3] = child_data;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_transfer_data_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   ಧ್ರುವ AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    ಪೂರ್ಣಾಙ್ಕ download = !!src->hw_frames_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->data[3] : dst->data[3]);

    AVFrame *dummy;
    ಪೂರ್ಣಾಙ್ಕ ret;

    dummy = av_frame_alloc();
    ಯದಿ (!dummy)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->data[3]       = surf->Data.MemId;
    dummy->hw_frames_ctx = s->child_frames_ref;

    ret = download ? av_hwframe_transfer_data(dst, dummy, 0) :
                     av_hwframe_transfer_data(dummy, src, 0);

    dummy->buf[0]        = ರಿಕ್ತ;
    dummy->data[3]       = ರಿಕ್ತ;
    dummy->hw_frames_ctx = ರಿಕ್ತ;

    av_frame_free(&dummy);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ map_frame_to_surface(ಧ್ರುವ AVFrame *frame, mfxFrameSurface1 *surface)
{
    ವಿಕಲ್ಪ (frame->format) {
    ಪಕ್ಷ AV_PIX_FMT_NV12:
    ಪಕ್ಷ AV_PIX_FMT_P010:
    ಪಕ್ಷ AV_PIX_FMT_P012:
        surface->Data.Y  = frame->data[0];
        surface->Data.UV = frame->data[1];
        ಭಙ್ಗ;

    ಪಕ್ಷ AV_PIX_FMT_YUV420P:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[1];
        surface->Data.V = frame->data[2];
        ಭಙ್ಗ;

    ಪಕ್ಷ AV_PIX_FMT_BGRA:
        surface->Data.B = frame->data[0];
        surface->Data.G = frame->data[0] + 1;
        surface->Data.R = frame->data[0] + 2;
        surface->Data.A = frame->data[0] + 3;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_PIX_FMT_YUYV422:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.V = frame->data[0] + 3;
        ಭಙ್ಗ;

    ಪಕ್ಷ AV_PIX_FMT_Y210:
    ಪಕ್ಷ AV_PIX_FMT_Y212:
        surface->Data.Y16 = (mfxU16 *)frame->data[0];
        surface->Data.U16 = (mfxU16 *)frame->data[0] + 1;
        surface->Data.V16 = (mfxU16 *)frame->data[0] + 3;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_PIX_FMT_VUYX:
        surface->Data.V = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.Y = frame->data[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 3;
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_PIX_FMT_XV30:
        surface->Data.U = frame->data[0];
        ಭಙ್ಗ;
    ಪಕ್ಷ AV_PIX_FMT_XV36:
        surface->Data.U = frame->data[0];
        surface->Data.Y = frame->data[0] + 2;
        surface->Data.V = frame->data[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 6;
        ಭಙ್ಗ;
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_PIX_FMT_UYVY422:
        surface->Data.Y = frame->data[0] + 1;
        surface->Data.U = frame->data[0];
        surface->Data.V = frame->data[0] + 2;
        ಭಙ್ಗ;
#endif
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ MFX_ERR_UNSUPPORTED;
    }
    surface->Data.Pitch     = frame->linesize[0];
    surface->Data.TimeStamp = frame->pts;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_internal_session_check_init(AVHWFramesContext *ctx, ಪೂರ್ಣಾಙ್ಕ upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    ಯದಿ (atomic_load(inited))
        ಪ್ರತ್ಯಾಗಮ 0;

#ಯದಿ HAVE_PTHREADS
    pthread_mutex_lock(&s->session_lock);
#endif

    ಯದಿ (!atomic_load(inited)) {
        ret = qsv_init_internal_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#ಯದಿ HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_lock);
#endif

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ಧ್ರುವ AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->data[3];

    mfxSyncPoint sync = ರಿಕ್ತ;
    mfxStatus err;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    ಪೂರ್ಣಾಙ್ಕ realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 0);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    ಯದಿ (dst->height & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        ಯದಿ (tmp_frame->format != dst->format ||
            tmp_frame->width  != FFALIGN(dst->linesize[0], 16) ||
            tmp_frame->height != FFALIGN(dst->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = dst->format;
            tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
            tmp_frame->height = FFALIGN(dst->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            ಯದಿ (ret < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    ಯದಿ (!s->session_download) {
        ಯದಿ (s->child_frames_ref)
            ಪ್ರತ್ಯಾಗಮ qsv_transfer_data_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst_frame, &out);

    ಕುರು {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, ರಿಕ್ತ, &sync);
        ಯದಿ (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } ಯಾವತ್ (err == MFX_WRN_DEVICE_BUSY);

    ಯದಿ (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಕುರು {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } ಯಾವತ್ (err == MFX_WRN_IN_EXECUTION);
    ಯದಿ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಯದಿ (realigned) {
        tmp_frame->width  = dst->width;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                ಧ್ರುವ AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   in = {{ 0 }};
    mfxFrameSurface1 *out = (mfxFrameSurface1*)dst->data[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = ರಿಕ್ತ;
    mfxStatus err;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    ಧ್ರುವ AVFrame *src_frame;
    ಪೂರ್ಣಾಙ್ಕ realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 1);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    ಯದಿ (src->height & 15 || src->linesize[0] & 15) {
        realigned = 1;
        ಯದಿ (tmp_frame->format != src->format ||
            tmp_frame->width  != FFALIGN(src->width, 16) ||
            tmp_frame->height != FFALIGN(src->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = src->format;
            tmp_frame->width  = FFALIGN(src->width, 16);
            tmp_frame->height = FFALIGN(src->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            ಯದಿ (ret < 0)
                ಪ್ರತ್ಯಾಗಮ ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        ಯದಿ (ret < 0) {
            av_frame_unref(tmp_frame);
            ಪ್ರತ್ಯಾಗಮ ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        ಯದಿ (ret < 0) {
            av_frame_unref(tmp_frame);
            ಪ್ರತ್ಯಾಗಮ ret;
        }

        tmp_info = out->Info;
        out->Info.CropW = FFMIN(out->Info.Width,  tmp_frame->width);
        out->Info.CropH = FFMIN(out->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    ಯದಿ (!s->session_upload) {
        ಯದಿ (s->child_frames_ref)
            ಪ್ರತ್ಯಾಗಮ qsv_transfer_data_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    in.Info = out->Info;
    map_frame_to_surface(src_frame, &in);

    ಕುರು {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_upload, &in, out, ರಿಕ್ತ, &sync);
        ಯದಿ (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } ಯಾವತ್ (err == MFX_WRN_DEVICE_BUSY);

    ಯದಿ (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಕುರು {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } ಯಾವತ್ (err == MFX_WRN_IN_EXECUTION);
    ಯದಿ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_UNKNOWN;
    }

    ಯದಿ (realigned) {
        out->Info.CropW = tmp_info.CropW;
        out->Info.CropH = tmp_info.CropH;
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_dynamic_frames_derive_to(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, ಪೂರ್ಣಾಙ್ಕ flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    ವಿಕಲ್ಪ (src_ctx->device_ctx->type) {
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        ಭಙ್ಗ;
#endif

#ಯದಿ CONFIG_D3D11VA
    ಪಕ್ಷ AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        ಯದಿ (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } ಅನ್ಯಥಾ {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
    ಭಙ್ಗ;
#endif

    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, ಪರಿಮಾಣ(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_fixed_frames_derive_to(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, ಪೂರ್ಣಾಙ್ಕ flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    ಪೂರ್ಣಾಙ್ಕ i;

    ವಿಕಲ್ಪ (src_ctx->device_ctx->type) {
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 ಪರಿಮಾಣ(*s->handle_pairs_internal));
            ಯದಿ (!s->handle_pairs_internal)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             ಪರಿಮಾಣ(*s->surfaces_internal));
            ಯದಿ (!s->surfaces_internal)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            ಪ್ರತಿ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = src_hwctx->surface_ids + i;
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        ಭಙ್ಗ;
#endif
#ಯದಿ CONFIG_D3D11VA
    ಪಕ್ಷ AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 ಪರಿಮಾಣ(*s->handle_pairs_internal));
            ಯದಿ (!s->handle_pairs_internal)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_ctx->initial_pool_size,
                                             ಪರಿಮಾಣ(*s->surfaces_internal));
            ಯದಿ (!s->surfaces_internal)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            ಪ್ರತಿ (i = 0; i < src_ctx->initial_pool_size; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                ಯದಿ (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                } ಅನ್ಯಥಾ {
                    s->handle_pairs_internal[i].second = (mfxMemId)src_hwctx->texture_infos[i].index;
                }
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_size;
            ಯದಿ (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            } ಅನ್ಯಥಾ {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
            }
        }
        ಭಙ್ಗ;
#endif
#ಯದಿ CONFIG_DXVA2
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 ಪರಿಮಾಣ(*s->handle_pairs_internal));
            ಯದಿ (!s->handle_pairs_internal)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             ಪರಿಮಾಣ(*s->surfaces_internal));
            ಯದಿ (!s->surfaces_internal)
                ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
            ಪ್ರತಿ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            ಯದಿ (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            ಅನ್ಯಥಾ
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        ಭಙ್ಗ;
#endif
    ಸ್ವಭಾವ:
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, ಪೂರ್ಣಾಙ್ಕ flags)
{
    ಯದಿ (src_ctx->initial_pool_size < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    } ಅನ್ಯಥಾ ಯದಿ (src_ctx->initial_pool_size == 0) {
        ಪ್ರತ್ಯಾಗಮ qsv_dynamic_frames_derive_to(dst_ctx, src_ctx, flags);
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ qsv_fixed_frames_derive_to(dst_ctx, src_ctx, flags);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_fixed_pool_map_to(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    ಪೂರ್ಣಾಙ್ಕ i, err, index = -1;

    ಪ್ರತಿ (i = 0; i < hwctx->nb_surfaces && index < 0; i++) {
        ವಿಕಲ್ಪ(src->format) {
#ಯದಿ CONFIG_VAAPI
        ಪಕ್ಷ AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            ಯದಿ (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->data[3])
                index = i;
            ಭಙ್ಗ;
        }
#endif
#ಯದಿ CONFIG_D3D11VA
        ಪಕ್ಷ AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            ಯದಿ (pair->first == src->data[0]
                && (pair->second == src->data[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->data[1] == (uint8_t *)0)))
                index = i;
            ಭಙ್ಗ;
        }
#endif
#ಯದಿ CONFIG_DXVA2
        ಪಕ್ಷ AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            ಯದಿ (pair->first == src->data[3])
                index = i;
            ಭಙ್ಗ;
        }
#endif
        }
    }
    ಯದಿ (index < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, ರಿಕ್ತ, ರಿಕ್ತ);
    ಯದಿ (err)
        ಪ್ರತ್ಯಾಗಮ err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)&hwctx->surfaces[index];

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_internal = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_pairs_internal = (mfxHDLPair *)surfaces_internal->Data.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_frames->data;

    ವಿಕಲ್ಪ (src_ctx->format) {
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_pairs_internal->first);

        ಭಙ್ಗ;
    }
#endif

#ಯದಿ CONFIG_D3D11VA
    ಪಕ್ಷ AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        ಭಙ್ಗ;
    }
#endif
    ಸ್ವಭಾವ:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        ಭಙ್ಗ;
    }

    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_dynamic_pool_map_to(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    mfxFrameSurface1 *surfaces_internal = ರಿಕ್ತ;
    mfxHDLPair *handle_pairs_internal = ರಿಕ್ತ;
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    surfaces_internal = av_calloc(1, ಪರಿಮಾಣ(*surfaces_internal));
    ಯದಿ (!surfaces_internal) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    handle_pairs_internal = av_calloc(1, ಪರಿಮಾಣ(*handle_pairs_internal));
    ಯದಿ (!handle_pairs_internal) {
        ret = AVERROR(ENOMEM);
        ಗಚ್ಛ fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_internal);
    ಯದಿ (ret < 0)
        ಗಚ್ಛ fail;

    ವಿಕಲ್ಪ (src->format) {
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, ಪರಿಮಾಣ(*surface_id_internal));
        ಯದಿ (!surface_id_internal) {
            ret =AVERROR(ENOMEM);
            ಗಚ್ಛ fail;
        }

        *surface_id_internal = (VASurfaceID)(uintptr_t)src->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;

        ಭಙ್ಗ;
    }
#endif

#ಯದಿ CONFIG_D3D11VA
    ಪಕ್ಷ AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_pairs_internal->first = (mfxMemId)src->data[0];

        ಯದಿ (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        } ಅನ್ಯಥಾ {
            handle_pairs_internal->second = (mfxMemId)src->data[1];
        }

        ಭಙ್ಗ;
    }
#endif
    ಸ್ವಭಾವ:
        ret = AVERROR(ENOSYS);
        ಗಚ್ಛ fail;
    }

    surfaces_internal->Data.MemId = (mfxMemId)handle_pairs_internal;

    ret = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_internal);
    ಯದಿ (ret)
        ಗಚ್ಛ fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)surfaces_internal;

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ಧ್ರುವ AVFrame *src, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    ಯದಿ (hwctx->nb_surfaces)
        ಪ್ರತ್ಯಾಗಮ qsv_fixed_pool_map_to(dst_ctx, dst, src, flags);
    ಅನ್ಯಥಾ
        ಪ್ರತ್ಯಾಗಮ qsv_dynamic_pool_map_to(dst_ctx, dst, src, flags);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_frames_get_constraints(AVHWDeviceContext *ctx,
                                      ಧ್ರುವ ಶೂನ್ಯ *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    ಪರಿಮಾಣ(*constraints->valid_sw_formats));
    ಯದಿ (!constraints->valid_sw_formats)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ಪರಿಮಾಣ(*constraints->valid_hw_formats));
    ಯದಿ (!constraints->valid_hw_formats)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    ಯದಿ (hwctx->session)
        MFXClose(hwctx->session);

    ಯದಿ (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_buffer_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

ಸ್ಥಿರ mfxIMPL choose_implementation(ಧ್ರುವ ವರ್ಣ *device, ಗಣನಾ AVHWDeviceType child_device_type)
{
    ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
        ಧ್ರುವ ವರ್ಣ *name;
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
    ಪೂರ್ಣಾಙ್ಕ i;

    ಯದಿ (device) {
        ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            ಯದಿ (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                ಭಙ್ಗ;
            }
        ಯದಿ (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, ರಿಕ್ತ, 0);
    }

    ಯದಿ (impl != MFX_IMPL_SOFTWARE) {
        ಯದಿ (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_VIA_D3D11;
        ಅನ್ಯಥಾ ಯದಿ (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_VIA_D3D9;
    }

    ಪ್ರತ್ಯಾಗಮ impl;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfxVersion    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfxStatus     err;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ವಿಕಲ್ಪ (child_device_ctx->type) {
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        ಭಙ್ಗ;
#endif
#ಯದಿ CONFIG_D3D11VA
    ಪಕ್ಷ AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        ಭಙ್ಗ;
#endif
#ಯದಿ CONFIG_DXVA2
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        ಭಙ್ಗ;
#endif
    ಸ್ವಭಾವ:
        ret = AVERROR(ENOSYS);
        ಗಚ್ಛ fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    ಯದಿ (ret)
        ಗಚ್ಛ fail;

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    ಯದಿ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        ಗಚ್ಛ fail;
    }

    ಪ್ರತ್ಯಾಗಮ 0;

fail:
    ಯದಿ (hwctx->session)
        MFXClose(hwctx->session);

    ಯದಿ (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = ರಿಕ್ತ;
    hwctx->loader = ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(ಪರಿಮಾಣ(*priv));
    ಯದಿ (!priv)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ಮುಕ್ತ = qsv_device_free;

    impl = choose_implementation("hw_any", child_device_ctx->type);
    ಪ್ರತ್ಯಾಗಮ qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ qsv_device_create(AVHWDeviceContext *ctx, ಧ್ರುವ ವರ್ಣ *device,
                             AVDictionary *opts, ಪೂರ್ಣಾಙ್ಕ flags)
{
    QSVDevicePriv *priv;
    ಗಣನಾ AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    ಪೂರ್ಣಾಙ್ಕ ret;

    priv = av_mallocz(ಪರಿಮಾಣ(*priv));
    ಯದಿ (!priv)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ಮುಕ್ತ        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", ರಿಕ್ತ, 0);
    ಯದಿ (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->ಮೌಲ್ಯ);
        ಯದಿ (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->ಮೌಲ್ಯ);
            ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
        }
#ಯದಿ QSV_ONEVPL
    } ಅನ್ಯಥಾ ಯದಿ (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } ಅನ್ಯಥಾ ಯದಿ (CONFIG_DXVA2) {
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
#ಅನ್ಯಥಾ
    } ಅನ್ಯಥಾ ಯದಿ (CONFIG_DXVA2) {
        av_log(ರಿಕ್ತ, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } ಅನ್ಯಥಾ ಯದಿ (CONFIG_D3D11VA) {
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#endif
    } ಅನ್ಯಥಾ ಯದಿ (CONFIG_VAAPI) {
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } ಅನ್ಯಥಾ {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
    }

#ಯದಿ CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    ಯದಿ (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->ಮೌಲ್ಯ);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
#endif

    child_device_opts = ರಿಕ್ತ;
    ವಿಕಲ್ಪ (child_device_type) {
#ಯದಿ CONFIG_VAAPI
    ಪಕ್ಷ AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_set(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_set(&child_device_opts, "driver",    "iHD",    0);
        }
        ಭಙ್ಗ;
#endif
#ಯದಿ CONFIG_D3D11VA
    ಪಕ್ಷ AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_set(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        ಭಙ್ಗ;
#endif
#ಯದಿ CONFIG_DXVA2
    ಪಕ್ಷ AV_HWDEVICE_TYPE_DXVA2:
#ಯದಿ QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#endif
        ಭಙ್ಗ;
#endif
    ಸ್ವಭಾವ:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
        }
        ಭಙ್ಗ;
    }

    e = av_dict_get(opts, "child_device", ರಿಕ್ತ, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->ಮೌಲ್ಯ : ರಿಕ್ತ, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->data;

    impl = choose_implementation(device, child_device_type);

    ಪ್ರತ್ಯಾಗಮ qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

ಧ್ರುವ HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_size      = ಪರಿಮಾಣ(QSVDeviceContext),
    .frames_hwctx_size      = ಪರಿಮಾಣ(QSVFramesContext),

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

    .pix_fmts = (ಧ್ರುವ ಗಣನಾ AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
