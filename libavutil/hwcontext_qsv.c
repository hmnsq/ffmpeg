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

#അന്തര്ഭാവ <stdatomic.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ <mfxvideo.h>

#അന്തര്ഭാവ "config.h"

#എങ്കിൽ HAVE_PTHREADS
#അന്തര്ഭാവ <pthread.h>
#endif

#define COBJMACROS
#എങ്കിൽ CONFIG_VAAPI
#അന്തര്ഭാവ "hwcontext_vaapi.h"
#endif
#എങ്കിൽ CONFIG_D3D11VA
#അന്തര്ഭാവ "hwcontext_d3d11va.h"
#endif
#എങ്കിൽ CONFIG_DXVA2
#അന്തര്ഭാവ <initguid.h>
#അന്തര്ഭാവ "hwcontext_dxva2.h"
#endif

#അന്തര്ഭാവ "buffer.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "hwcontext.h"
#അന്തര്ഭാവ "hwcontext_internal.h"
#അന്തര്ഭാവ "hwcontext_qsv.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "pixfmt.h"
#അന്തര്ഭാവ "pixdesc.h"
#അന്തര്ഭാവ "time.h"
#അന്തര്ഭാവ "imgutils.h"
#അന്തര്ഭാവ "avassert.h"

#define QSV_VERSION_ATLEAST(MAJOR, MINOR)   \
    (MFX_VERSION_MAJOR > (MAJOR) ||         \
     MFX_VERSION_MAJOR == (MAJOR) && MFX_VERSION_MINOR >= (MINOR))

#define QSV_RUNTIME_VERSION_ATLEAST(MFX_VERSION, MAJOR, MINOR)          \
    ((MFX_VERSION.Major > (MAJOR)) ||                                   \
     (MFX_VERSION.Major == (MAJOR) && MFX_VERSION.Minor >= (MINOR)))

#define MFX_IMPL_VIA_MASK(impl) (0x0f00 & (impl))
#define QSV_ONEVPL       QSV_VERSION_ATLEAST(2, 0)
#define QSV_HAVE_OPAQUE  !QSV_ONEVPL

#എങ്കിൽ QSV_ONEVPL
#അന്തര്ഭാവ <mfxdispatcher.h>
#അല്ലെങ്കിൽ
#define MFXUnload(a) ചെയ്യുക { } ആകുമ്പോൾ(0)
#endif

തരനിർവചനം ഘടന QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

തരനിർവചനം ഘടന QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfxVersion          ver;
    mfxIMPL             impl;

    എണ്ണൽ AVHWDeviceType child_device_type;
    എണ്ണൽ AVPixelFormat  child_pix_fmt;
} QSVDeviceContext;

തരനിർവചനം ഘടന QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#എങ്കിൽ HAVE_PTHREADS
    pthread_mutex_t session_lock;
#endif

    AVBufferRef *child_frames_ref;
    mfxFrameSurface1 *surfaces_internal;
    mfxHDLPair *handle_pairs_internal;
    പൂർണ്ണസംഖ്യ             nb_surfaces_used;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#എങ്കിൽ QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfxExtBuffer *ext_buffers[1];
#endif
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

തരനിർവചനം ഘടന QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

സ്ഥിതം സ്ഥിരം ഘടന {
    എണ്ണൽ AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_shift;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#എങ്കിൽ CONFIG_VAAPI
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
#എങ്കിൽ QSV_VERSION_ATLEAST(1, 31)
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

ബാഹ്യ പൂർണ്ണസംഖ്യ ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          എണ്ണൽ AVHWDeviceType base_dev_type,
                                          ശൂന്യം **base_handle);

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
പൂർണ്ണസംഖ്യ ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                   എണ്ണൽ AVHWDeviceType base_dev_type,
                                   ശൂന്യം **base_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->Data.MemId;
    തിരഞ്ഞെടുപ്പ് (base_dev_type) {
#എങ്കിൽ CONFIG_VAAPI
    അവസ്ഥ AV_HWDEVICE_TYPE_VAAPI:
        base_handle[0] = handle_pair->first;
        തിരികെ 0;
#endif
#എങ്കിൽ CONFIG_D3D11VA
    അവസ്ഥ AV_HWDEVICE_TYPE_D3D11VA:
        base_handle[0] = handle_pair->first;
        base_handle[1] = handle_pair->second;
        തിരികെ 0;
#endif
#എങ്കിൽ CONFIG_DXVA2
    അവസ്ഥ AV_HWDEVICE_TYPE_DXVA2:
        base_handle[0] = handle_pair->first;
        തിരികെ 0;
#endif
    }
    തിരികെ AVERROR(EINVAL);
}

സ്ഥിതം uint32_t qsv_fourcc_from_pix_fmt(എണ്ണൽ AVPixelFormat pix_fmt)
{
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        എങ്കിൽ (supported_pixel_formats[i].pix_fmt == pix_fmt)
            തിരികെ supported_pixel_formats[i].fourcc;
    }
    തിരികെ 0;
}

സ്ഥിതം uint16_t qsv_shift_from_pix_fmt(എണ്ണൽ AVPixelFormat pix_fmt)
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        എങ്കിൽ (supported_pixel_formats[i].pix_fmt == pix_fmt)
            തിരികെ supported_pixel_formats[i].mfx_shift;
    }

    തിരികെ 0;
}

#എങ്കിൽ CONFIG_D3D11VA
സ്ഥിതം uint32_t qsv_get_d3d11va_bind_flags(പൂർണ്ണസംഖ്യ mem_type)
{
    uint32_t bind_flags = 0;

    എങ്കിൽ ((mem_type & MFX_MEMTYPE_VIDEO_MEMORY_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_INTERNAL_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    അല്ലെങ്കിൽ
        bind_flags = D3D11_BIND_DECODER;

    എങ്കിൽ ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    തിരികെ bind_flags;
}
#endif

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_fill_border(AVFrame *dst, സ്ഥിരം AVFrame *src)
{
    സ്ഥിരം AVPixFmtDescriptor *desc;
    പൂർണ്ണസംഖ്യ i, planes_nb = 0;
    എങ്കിൽ (dst->format != src->format)
        തിരികെ AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    വേണ്ടി (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    വേണ്ടി (i = 0; i < planes_nb; i++) {
        പൂർണ്ണസംഖ്യ sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->width,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->width,
                                                 i);
        സ്ഥിരം AVComponentDescriptor comp = desc->comp[i];
        എങ്കിൽ (swidth < 0 || dwidth < 0) {
            av_log(ശൂന്യ, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            തിരികെ AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        എങ്കിൽ (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        വേണ്ടി (y = 0; y < sheight; y++) {
            ശൂന്യം *വരി_ptr = dst->data[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(വരി_ptr,
                           comp.depth > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        വേണ്ടി (y = sheight; y < dheight; y++) {
            memcpy(dst->data[i]+y*dst->linesize[i],
                   dst->data[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    പൂർണ്ണസംഖ്യ   hw_handle_supported = 0;
    mfxHandleType handle_type;
    എണ്ണൽ AVHWDeviceType device_type;
    എണ്ണൽ AVPixelFormat  pix_fmt;
    mfxStatus err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    എങ്കിൽ (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    എങ്കിൽ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    എങ്കിൽ (MFX_IMPL_VIA_VAAPI == MFX_IMPL_VIA_MASK(s->impl)) {
#എങ്കിൽ CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#endif
    } അല്ലെങ്കിൽ എങ്കിൽ (MFX_IMPL_VIA_D3D11 == MFX_IMPL_VIA_MASK(s->impl)) {
#എങ്കിൽ CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#endif
    } അല്ലെങ്കിൽ എങ്കിൽ (MFX_IMPL_VIA_D3D9 == MFX_IMPL_VIA_MASK(s->impl)) {
#എങ്കിൽ CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#endif
    }

    എങ്കിൽ (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        എങ്കിൽ (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->child_device_type = device_type;
            s->child_pix_fmt     = pix_fmt;
        }
    }
    എങ്കിൽ (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    എങ്കിൽ (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = ശൂന്യ;
    s->session_download_init = 0;

    എങ്കിൽ (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = ശൂന്യ;
    s->session_upload_init = 0;

#എങ്കിൽ HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_lock);
#endif

    av_freep(&s->mem_ids);
#എങ്കിൽ QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#endif
    av_freep(&s->surfaces_internal);
    av_freep(&s->handle_pairs_internal);
    av_frame_unref(&s->realigned_upload_frame);
    av_frame_unref(&s->realigned_download_frame);
    av_buffer_unref(&s->child_frames_ref);
}

സ്ഥിതം ശൂന്യം qsv_pool_release_dummy(ശൂന്യം *opaque, uint8_t *data)
{
}

സ്ഥിതം ശൂന്യം qsv_pool_release(ശൂന്യം *opaque, uint8_t *data)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)data;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.Data.MemId;
    AVHWFramesContext *child_frames_ctx;

    എങ്കിൽ (!s->child_frames_ref)
        തിരികെ;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    എങ്കിൽ (!child_frames_ctx->device_ctx)
        തിരികെ;

#എങ്കിൽ CONFIG_VAAPI
    എങ്കിൽ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#endif

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

സ്ഥിതം AVBufferRef *qsv_fixed_pool_alloc(ശൂന്യം *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    എങ്കിൽ (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        തിരികെ av_buffer_create((uint8_t*)(s->surfaces_internal + s->nb_surfaces_used - 1),
                                വലുപ്പം(*hwctx->surfaces), qsv_pool_release_dummy, ശൂന്യ, 0);
    }

    തിരികെ ശൂന്യ;
}

സ്ഥിതം AVBufferRef *qsv_dynamic_pool_alloc(ശൂന്യം *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx;
    QSVSurface *qsv_surface = ശൂന്യ;
    mfxHDLPair *handle_pairs_internal = ശൂന്യ;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (!s->child_frames_ref)
        പോകുക fail;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    എങ്കിൽ (!child_frames_ctx->device_ctx)
        പോകുക fail;

#എങ്കിൽ CONFIG_DXVA2
    എങ്കിൽ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        പോകുക fail;
    }
#endif

    qsv_surface = av_calloc(1, വലുപ്പം(*qsv_surface));
    എങ്കിൽ (!qsv_surface)
        പോകുക fail;

    qsv_surface->child_frame = av_frame_alloc();
    എങ്കിൽ (!qsv_surface->child_frame)
        പോകുക fail;

    ret = av_hwframe_get_buffer(s->child_frames_ref, qsv_surface->child_frame, 0);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    handle_pairs_internal = av_calloc(1, വലുപ്പം(*handle_pairs_internal));
    എങ്കിൽ (!handle_pairs_internal)
        പോകുക fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

#എങ്കിൽ CONFIG_VAAPI
    എങ്കിൽ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, വലുപ്പം(*surface_id_internal));
        എങ്കിൽ (!surface_id_internal)
            പോകുക fail;

        *surface_id_internal = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
    }
#endif

#എങ്കിൽ CONFIG_D3D11VA
    എങ്കിൽ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        handle_pairs_internal->first = (mfxMemId)qsv_surface->child_frame->data[0];

        എങ്കിൽ (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        അല്ലെങ്കിൽ
            handle_pairs_internal->second = (mfxMemId)qsv_surface->child_frame->data[1];

    }
#endif

    qsv_surface->mfx_surface.Data.MemId = (mfxMemId)handle_pairs_internal;
    തിരികെ av_buffer_create((uint8_t *)qsv_surface, വലുപ്പം(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    എങ്കിൽ (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_pairs_internal);

    തിരികെ ശൂന്യ;
}

സ്ഥിതം AVBufferRef *qsv_pool_alloc(ശൂന്യം *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    എങ്കിൽ (hwctx->nb_surfaces == 0) {
        തിരികെ qsv_dynamic_pool_alloc(opaque, size);
    } അല്ലെങ്കിൽ {
        തിരികെ qsv_fixed_pool_alloc(opaque, size);
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = ശൂന്യ;
    AVBufferRef *child_frames_ref = ശൂന്യ;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    പൂർണ്ണസംഖ്യ i, ret = 0;

    എങ്കിൽ (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        തിരികെ AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    എങ്കിൽ (!child_device_ref)
        തിരികെ AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->data;

#എങ്കിൽ CONFIG_VAAPI
    എങ്കിൽ (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#endif
#എങ്കിൽ CONFIG_D3D11VA
    എങ്കിൽ (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        ID3D11Device_AddRef((ID3D11Device*)device_priv->handle);
        child_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#endif
#എങ്കിൽ CONFIG_DXVA2
    എങ്കിൽ (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#endif

    ret = av_hwdevice_ctx_init(child_device_ref);
    എങ്കിൽ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        പോകുക fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    എങ്കിൽ (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        പോകുക fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->data;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_size = ctx->initial_pool_size;
    child_frames_ctx->width             = FFALIGN(ctx->width, 16);
    child_frames_ctx->height            = FFALIGN(ctx->height, 16);

#എങ്കിൽ CONFIG_D3D11VA
    എങ്കിൽ (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        എങ്കിൽ (hwctx->frame_type == 0)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        എങ്കിൽ (hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
            child_frames_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        child_frames_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->frame_type);
    }
#endif
#എങ്കിൽ CONFIG_DXVA2
    എങ്കിൽ (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        എങ്കിൽ (hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET)
            child_frames_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        അല്ലെങ്കിൽ
            child_frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#endif

    ret = av_hwframe_ctx_init(child_frames_ref);
    എങ്കിൽ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        പോകുക fail;
    }

#എങ്കിൽ CONFIG_VAAPI
    എങ്കിൽ (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        വേണ്ടി (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = child_frames_hwctx->surface_ids + i;
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif
#എങ്കിൽ CONFIG_D3D11VA
    എങ്കിൽ (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        വേണ്ടി (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->texture_infos[i].texture;
            എങ്കിൽ(child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            } അല്ലെങ്കിൽ {
                s->handle_pairs_internal[i].second = (mfxMemId)child_frames_hwctx->texture_infos[i].index;
            }
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        എങ്കിൽ (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } അല്ലെങ്കിൽ {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
#endif
#എങ്കിൽ CONFIG_DXVA2
    എങ്കിൽ (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        വേണ്ടി (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->surfaces[i];
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        എങ്കിൽ (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        അല്ലെങ്കിൽ
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = ശൂന്യ;

fail:
    av_buffer_unref(&child_device_ref);
    av_buffer_unref(&child_frames_ref);
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    സ്ഥിരം AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    എങ്കിൽ (!desc)
        തിരികെ AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    എങ്കിൽ (!fourcc)
        തിരികെ AVERROR(EINVAL);

    surf->Info.BitDepthLuma   = desc->comp[0].depth;
    surf->Info.BitDepthChroma = desc->comp[0].depth;
    surf->Info.Shift          = qsv_shift_from_pix_fmt(ctx->sw_format);

    എങ്കിൽ (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    അല്ലെങ്കിൽ എങ്കിൽ (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    അല്ലെങ്കിൽ
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.Width          = FFALIGN(ctx->width, 16);
    surf->Info.CropW          = ctx->width;
    surf->Info.Height         = FFALIGN(ctx->height, 16);
    surf->Info.CropH          = ctx->height;
    surf->Info.FrameRateExtN  = 25;
    surf->Info.FrameRateExtD  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    പൂർണ്ണസംഖ്യ i, ret = 0;

    എങ്കിൽ (ctx->initial_pool_size < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        തിരികെ AVERROR(EINVAL);
    } അല്ലെങ്കിൽ എങ്കിൽ (ctx->initial_pool_size == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;

        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(വലുപ്പം(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, ശൂന്യ);
        എങ്കിൽ (!ffhwframesctx(ctx)->pool_internal)
            തിരികെ AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, വലുപ്പം(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        frames_hwctx->info = &s->frame_info;
        frames_hwctx->nb_surfaces = 0;

        തിരികെ 0;
    }

    s->handle_pairs_internal = av_calloc(ctx->initial_pool_size,
                                         വലുപ്പം(*s->handle_pairs_internal));
    എങ്കിൽ (!s->handle_pairs_internal)
        തിരികെ AVERROR(ENOMEM);

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     വലുപ്പം(*s->surfaces_internal));
    എങ്കിൽ (!s->surfaces_internal)
        തിരികെ AVERROR(ENOMEM);

    വേണ്ടി (i = 0; i < ctx->initial_pool_size; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_internal[i]);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;
    }

#എങ്കിൽ QSV_HAVE_OPAQUE
    എങ്കിൽ (!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;
    }
#അല്ലെങ്കിൽ
    ret = qsv_init_child_ctx(ctx);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;
#endif

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(വലുപ്പം(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, ശൂന്യ);
    എങ്കിൽ (!ffhwframesctx(ctx)->pool_internal)
        തിരികെ AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    തിരികെ 0;
}

സ്ഥിതം mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    എങ്കിൽ (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        തിരികെ MFX_ERR_UNSUPPORTED;
    എങ്കിൽ (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        തിരികെ MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->അക്കം_Frame_Actual = hwctx->nb_surfaces;

    തിരികെ MFX_ERR_NONE;
}

സ്ഥിതം mfxStatus frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    തിരികെ MFX_ERR_NONE;
}

സ്ഥിതം mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    തിരികെ MFX_ERR_UNSUPPORTED;
}

സ്ഥിതം mfxStatus frame_unlock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    തിരികെ MFX_ERR_UNSUPPORTED;
}

സ്ഥിതം mfxStatus frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    എങ്കിൽ (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    തിരികെ MFX_ERR_NONE;
}

#എങ്കിൽ QSV_ONEVPL

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_d3d11_update_config(ശൂന്യം *ctx, mfxHDL handle, mfxConfig cfg)
{
    പൂർണ്ണസംഖ്യ ret = AVERROR_UNKNOWN;
#എങ്കിൽ CONFIG_D3D11VA
    mfxStatus sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = ശൂന്യ;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_മൂല്യം = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (ശൂന്യം**)&pDXGIDevice);
    എങ്കിൽ (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        എങ്കിൽ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            തിരികെ ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        എങ്കിൽ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            പോകുക fail;
        }
    } അല്ലെങ്കിൽ {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        തിരികെ ret;
    }

    impl_മൂല്യം.Type = MFX_VARIANT_TYPE_U16;
    impl_മൂല്യം.Data.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (സ്ഥിരം mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_മൂല്യം);
    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        പോകുക fail;
    }

    impl_മൂല്യം.Type = MFX_VARIANT_TYPE_PTR;
    impl_മൂല്യം.Data.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (സ്ഥിരം mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_മൂല്യം);
    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        പോകുക fail;
    }

    impl_മൂല്യം.Type = MFX_VARIANT_TYPE_U32;
    impl_മൂല്യം.Data.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (സ്ഥിരം mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_മൂല്യം);
    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        പോകുക fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#endif
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_d3d9_update_config(ശൂന്യം *ctx, mfxHDL handle, mfxConfig cfg)
{
    പൂർണ്ണസംഖ്യ ret = AVERROR_UNKNOWN;
#എങ്കിൽ CONFIG_DXVA2
    mfxStatus sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = ശൂന്യ;
    IDirect3DDevice9Ex *device_ex = ശൂന്യ;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = ശൂന്യ;
    IDirect3D9 *d3d9 = ശൂന്യ;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_മൂല്യം = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        പോകുക fail;
    }

    hr = IDirect3DDeviceManager9_LockDevice(devmgr, device_handle, &device, TRUE);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        പോകുക fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (ശൂന്യം **)&device_ex);
    IDirect3DDevice9_Release(device);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        പോകുക unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        പോകുക unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        പോകുക unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (ശൂന്യം **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        പോകുക unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    എങ്കിൽ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        പോകുക release;
    }

    impl_മൂല്യം.Type = MFX_VARIANT_TYPE_PTR;
    impl_മൂല്യം.Data.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (സ്ഥിരം mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_മൂല്യം);
    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        പോകുക release;
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
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_va_update_config(ശൂന്യം *ctx, mfxHDL handle, mfxConfig cfg)
{
#എങ്കിൽ CONFIG_VAAPI
#എങ്കിൽ VA_CHECK_VERSION(1, 15, 0)
    mfxStatus sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_മൂല്യം = {0};

    vas = vaGetDisplayAttributes(dpy, &attr, 1);
    എങ്കിൽ (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_മൂല്യം.Type = MFX_VARIANT_TYPE_U16;
        impl_മൂല്യം.Data.U16 = (attr.മൂല്യം & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (സ്ഥിരം mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_മൂല്യം);
        എങ്കിൽ (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            പോകുക fail;
        }
    } അല്ലെങ്കിൽ {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        പോകുക fail;
    }

    തിരികെ 0;

fail:
#അല്ലെങ്കിൽ
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#endif
#endif
    തിരികെ AVERROR_UNKNOWN;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_new_mfx_loader(ശൂന്യം *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfxVersion *pver,
                              ശൂന്യം **ploader)
{
    mfxStatus sts;
    mfxLoader loader = ശൂന്യ;
    mfxConfig cfg;
    mfxVariant impl_മൂല്യം = {0};

    *ploader = ശൂന്യ;
    loader = MFXLoad();
    എങ്കിൽ (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        പോകുക fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    എങ്കിൽ (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        പോകുക fail;
    }

    impl_മൂല്യം.Type = MFX_VARIANT_TYPE_U32;
    impl_മൂല്യം.Data.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (സ്ഥിരം mfxU8 *)"mfxImplDescription.Impl", impl_മൂല്യം);
    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        പോകുക fail;
    }

    impl_മൂല്യം.Type = MFX_VARIANT_TYPE_U32;
    impl_മൂല്യം.Data.U32 = pver->Version;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (സ്ഥിരം mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_മൂല്യം);
    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        പോകുക fail;
    }

    impl_മൂല്യം.Type = MFX_VARIANT_TYPE_U32;
    impl_മൂല്യം.Data.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (സ്ഥിരം mfxU8 *)"mfxImplDescription.VendorID", impl_മൂല്യം);
    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        പോകുക fail;
    }

    എങ്കിൽ (MFX_HANDLE_VA_DISPLAY == handle_type) {
        എങ്കിൽ (handle && qsv_va_update_config(ctx, handle, cfg))
            പോകുക fail;

        impl_മൂല്യം.Data.U32 = MFX_ACCEL_MODE_VIA_VAAPI;
    } അല്ലെങ്കിൽ എങ്കിൽ (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        എങ്കിൽ (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            പോകുക fail;

        impl_മൂല്യം.Data.U32 = MFX_ACCEL_MODE_VIA_D3D9;
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            പോകുക fail;

        impl_മൂല്യം.Data.U32 = MFX_ACCEL_MODE_VIA_D3D11;
    }

    impl_മൂല്യം.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (സ്ഥിരം mfxU8 *)"mfxImplDescription.AccelerationMode", impl_മൂല്യം);
    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        പോകുക fail;
    }

    *ploader = loader;

    തിരികെ 0;

fail:
    എങ്കിൽ (loader)
        MFXUnload(loader);

    തിരികെ AVERROR_UNKNOWN;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_create_mfx_session_from_loader(ശൂന്യം *ctx, mfxLoader loader, mfxSession *psession)
{
    mfxStatus sts;
    mfxSession session = ശൂന്യ;
    uint32_t impl_idx = 0;
    mfxVersion ver;

    ആകുമ്പോൾ (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        എങ്കിൽ (sts == MFX_ERR_NOT_FOUND)
            നിർത്തുക;
        അല്ലെങ്കിൽ എങ്കിൽ (sts != MFX_ERR_NONE) {
            impl_idx++;
            തുടരുക;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        എങ്കിൽ (sts == MFX_ERR_NONE)
            നിർത്തുക;

        impl_idx++;
    }

    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        പോകുക fail;
    }

    sts = MFXQueryVersion(session, &ver);
    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        പോകുക fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    തിരികെ 0;

fail:
    എങ്കിൽ (session)
        MFXClose(session);

    തിരികെ AVERROR_UNKNOWN;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_create_mfx_session(ശൂന്യം *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  ശൂന്യം **ploader)
{
    mfxLoader loader = ശൂന്യ;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    എങ്കിൽ (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        തിരികെ AVERROR(EXDEV);
    }

    *psession = ശൂന്യ;

    എങ്കിൽ (!*ploader) {
        എങ്കിൽ (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (ശൂന്യം **)&loader))
            പോകുക fail;

        av_assert0(loader);
    } അല്ലെങ്കിൽ
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    എങ്കിൽ (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        പോകുക fail;

    എങ്കിൽ (!*ploader)
        *ploader = loader;

    തിരികെ 0;

fail:
    എങ്കിൽ (!*ploader && loader)
        MFXUnload(loader);

    തിരികെ AVERROR_UNKNOWN;
}

#അല്ലെങ്കിൽ

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_create_mfx_session(ശൂന്യം *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  ശൂന്യം **ploader)
{
    mfxVersion ver;
    mfxStatus sts;
    mfxSession session = ശൂന്യ;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    *ploader = ശൂന്യ;
    *psession = ശൂന്യ;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        പോകുക fail;
    }

    sts = MFXQueryVersion(session, &ver);
    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        പോകുക fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    എങ്കിൽ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        പോകുക fail;
    }

    *psession = session;

    തിരികെ 0;

fail:
    എങ്കിൽ (session)
        MFXClose(session);

    തിരികെ AVERROR_UNKNOWN;
}

#endif

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_init_internal_session(AVHWFramesContext *ctx,
                                     mfxSession *session, പൂർണ്ണസംഖ്യ upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    പൂർണ്ണസംഖ്യ opaque = 0;

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
    പൂർണ്ണസംഖ്യ                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    ശൂന്യം             **loader = &hwctx->loader;
    mfxSession parent_session = hwctx->session;
    mfxIMPL impl;
    mfxVersion ver;

    err = MFXQueryIMPL(parent_session, &impl);
    എങ്കിൽ (err == MFX_ERR_NONE)
        err = MFXQueryVersion(parent_session, &ver);
    എങ്കിൽ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        തിരികെ AVERROR_UNKNOWN;
    }

#എങ്കിൽ QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    എങ്കിൽ (ret)
        പോകുക fail;

    എങ്കിൽ (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        എങ്കിൽ (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            പോകുക fail;
        }
    }

    എങ്കിൽ (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        എങ്കിൽ (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            പോകുക fail;
        }
    }

    എങ്കിൽ (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        എങ്കിൽ (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            പോകുക fail;
        }
    }

    memset(&par, 0, വലുപ്പം(par));

    എങ്കിൽ (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_OUT_VIDEO_MEMORY :
                                 MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
#എങ്കിൽ QSV_HAVE_OPAQUE
    അല്ലെങ്കിൽ {
        par.ExtParam    = s->ext_buffers;
        par.അക്കം_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
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
    എങ്കിൽ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        പോകുക fail;
    }

    തിരികെ 0;

fail:
    എങ്കിൽ (*session)
        MFXClose(*session);

    *session = ശൂന്യ;

    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    പൂർണ്ണസംഖ്യ opaque = 0;

    uint32_t fourcc;
    പൂർണ്ണസംഖ്യ i, ret;

#എങ്കിൽ QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    എങ്കിൽ (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        തിരികെ AVERROR(ENOSYS);
    }

    എങ്കിൽ (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        എങ്കിൽ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            തിരികെ ret;
        }
    }

    എങ്കിൽ (!opaque) {
        s->mem_ids = av_calloc(frames_hwctx->nb_surfaces, വലുപ്പം(*s->mem_ids));
        എങ്കിൽ (!s->mem_ids)
            തിരികെ AVERROR(ENOMEM);

        വേണ്ടി (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].Data.MemId;
    }
#എങ്കിൽ QSV_HAVE_OPAQUE
    അല്ലെങ്കിൽ {
        s->surface_ptrs = av_calloc(frames_hwctx->nb_surfaces,
                                    വലുപ്പം(*s->surface_ptrs));
        എങ്കിൽ (!s->surface_ptrs)
            തിരികെ AVERROR(ENOMEM);

        വേണ്ടി (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.അക്കം_Surface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = വലുപ്പം(s->opaque_alloc);

        s->ext_buffers[0] = (mfxExtBuffer*)&s->opaque_alloc;
    }
#endif

    s->session_download = ശൂന്യ;
    s->session_upload   = ശൂന്യ;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#എങ്കിൽ HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, ശൂന്യ);
#endif

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    എങ്കിൽ (!frame->buf[0])
        തിരികെ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_QSV;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    എണ്ണൽ AVHWFrameTransferDirection dir,
                                    എണ്ണൽ AVPixelFormat **formats)
{
    എണ്ണൽ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, വലുപ്പം(*fmts));
    എങ്കിൽ (!fmts)
        തിരികെ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, പൂർണ്ണസംഖ്യ flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    പൂർണ്ണസംഖ്യ i;

    തിരഞ്ഞെടുപ്പ് (dst_ctx->device_ctx->type) {
#എങ്കിൽ CONFIG_VAAPI
    അവസ്ഥ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               വലുപ്പം(*dst_hwctx->surface_ids));
            എങ്കിൽ (!dst_hwctx->surface_ids)
                തിരികെ AVERROR(ENOMEM);
            വേണ്ടി (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        നിർത്തുക;
#endif
#എങ്കിൽ CONFIG_D3D11VA
    അവസ്ഥ AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_size = src_ctx->initial_pool_size;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 വലുപ്പം(*dst_hwctx->texture_infos));
            എങ്കിൽ (!dst_hwctx->texture_infos)
                തിരികെ AVERROR(ENOMEM);
            എങ്കിൽ (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            വേണ്ടി (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].index = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            എങ്കിൽ (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } അല്ലെങ്കിൽ
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        നിർത്തുക;
#endif
#എങ്കിൽ CONFIG_DXVA2
    അവസ്ഥ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            വലുപ്പം(*dst_hwctx->surfaces));
            എങ്കിൽ (!dst_hwctx->surfaces)
                തിരികെ AVERROR(ENOMEM);
            വേണ്ടി (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            എങ്കിൽ (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            അല്ലെങ്കിൽ
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        നിർത്തുക;
#endif
    സ്ഥിരസ്ഥിതി:
        തിരികെ AVERROR(ENOSYS);
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->data[3];
    AVHWFramesContext *child_frames_ctx;
    സ്ഥിരം AVPixFmtDescriptor *desc;
    uint8_t *child_data;
    AVFrame *dummy;
    പൂർണ്ണസംഖ്യ ret = 0;

    എങ്കിൽ (!s->child_frames_ref)
        തിരികെ AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;

    തിരഞ്ഞെടുപ്പ് (child_frames_ctx->device_ctx->type) {
#എങ്കിൽ CONFIG_VAAPI
    അവസ്ഥ AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_data = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        നിർത്തുക;
    }
#endif
#എങ്കിൽ CONFIG_D3D11VA
    അവസ്ഥ AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        നിർത്തുക;
    }
#endif
#എങ്കിൽ CONFIG_DXVA2
    അവസ്ഥ AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        നിർത്തുക;
    }
#endif
    സ്ഥിരസ്ഥിതി:
        തിരികെ AVERROR(ENOSYS);
    }

    എങ്കിൽ (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, ശൂന്യ, ശൂന്യ);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;

        dst->width   = src->width;
        dst->height  = src->height;

       എങ്കിൽ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
            dst->data[0] = pair->first;
            dst->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } അല്ലെങ്കിൽ {
            dst->data[3] = child_data;
        }

        തിരികെ 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    എങ്കിൽ (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        തിരികെ AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    എങ്കിൽ (!dummy)
        തിരികെ AVERROR(ENOMEM);

    dummy->buf[0]        = av_buffer_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_buffer_ref(s->child_frames_ref);
    എങ്കിൽ (!dummy->buf[0] || !dummy->hw_frames_ctx)
        പോകുക fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;

    എങ്കിൽ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        dummy->data[0] = pair->first;
        dummy->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } അല്ലെങ്കിൽ {
        dummy->data[3] = child_data;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_transfer_data_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   സ്ഥിരം AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    പൂർണ്ണസംഖ്യ download = !!src->hw_frames_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->data[3] : dst->data[3]);

    AVFrame *dummy;
    പൂർണ്ണസംഖ്യ ret;

    dummy = av_frame_alloc();
    എങ്കിൽ (!dummy)
        തിരികെ AVERROR(ENOMEM);

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->data[3]       = surf->Data.MemId;
    dummy->hw_frames_ctx = s->child_frames_ref;

    ret = download ? av_hwframe_transfer_data(dst, dummy, 0) :
                     av_hwframe_transfer_data(dummy, src, 0);

    dummy->buf[0]        = ശൂന്യ;
    dummy->data[3]       = ശൂന്യ;
    dummy->hw_frames_ctx = ശൂന്യ;

    av_frame_free(&dummy);

    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ map_frame_to_surface(സ്ഥിരം AVFrame *frame, mfxFrameSurface1 *surface)
{
    തിരഞ്ഞെടുപ്പ് (frame->format) {
    അവസ്ഥ AV_PIX_FMT_NV12:
    അവസ്ഥ AV_PIX_FMT_P010:
    അവസ്ഥ AV_PIX_FMT_P012:
        surface->Data.Y  = frame->data[0];
        surface->Data.UV = frame->data[1];
        നിർത്തുക;

    അവസ്ഥ AV_PIX_FMT_YUV420P:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[1];
        surface->Data.V = frame->data[2];
        നിർത്തുക;

    അവസ്ഥ AV_PIX_FMT_BGRA:
        surface->Data.B = frame->data[0];
        surface->Data.G = frame->data[0] + 1;
        surface->Data.R = frame->data[0] + 2;
        surface->Data.A = frame->data[0] + 3;
        നിർത്തുക;
    അവസ്ഥ AV_PIX_FMT_YUYV422:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.V = frame->data[0] + 3;
        നിർത്തുക;

    അവസ്ഥ AV_PIX_FMT_Y210:
    അവസ്ഥ AV_PIX_FMT_Y212:
        surface->Data.Y16 = (mfxU16 *)frame->data[0];
        surface->Data.U16 = (mfxU16 *)frame->data[0] + 1;
        surface->Data.V16 = (mfxU16 *)frame->data[0] + 3;
        നിർത്തുക;
    അവസ്ഥ AV_PIX_FMT_VUYX:
        surface->Data.V = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.Y = frame->data[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 3;
        നിർത്തുക;
    അവസ്ഥ AV_PIX_FMT_XV30:
        surface->Data.U = frame->data[0];
        നിർത്തുക;
    അവസ്ഥ AV_PIX_FMT_XV36:
        surface->Data.U = frame->data[0];
        surface->Data.Y = frame->data[0] + 2;
        surface->Data.V = frame->data[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 6;
        നിർത്തുക;
#എങ്കിൽ CONFIG_VAAPI
    അവസ്ഥ AV_PIX_FMT_UYVY422:
        surface->Data.Y = frame->data[0] + 1;
        surface->Data.U = frame->data[0];
        surface->Data.V = frame->data[0] + 2;
        നിർത്തുക;
#endif
    സ്ഥിരസ്ഥിതി:
        തിരികെ MFX_ERR_UNSUPPORTED;
    }
    surface->Data.Pitch     = frame->linesize[0];
    surface->Data.TimeStamp = frame->pts;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_internal_session_check_init(AVHWFramesContext *ctx, പൂർണ്ണസംഖ്യ upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    പൂർണ്ണസംഖ്യ ret = 0;

    എങ്കിൽ (atomic_load(inited))
        തിരികെ 0;

#എങ്കിൽ HAVE_PTHREADS
    pthread_mutex_lock(&s->session_lock);
#endif

    എങ്കിൽ (!atomic_load(inited)) {
        ret = qsv_init_internal_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#എങ്കിൽ HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_lock);
#endif

    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  സ്ഥിരം AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->data[3];

    mfxSyncPoint sync = ശൂന്യ;
    mfxStatus err;
    പൂർണ്ണസംഖ്യ ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    പൂർണ്ണസംഖ്യ realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 0);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    എങ്കിൽ (dst->height & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        എങ്കിൽ (tmp_frame->format != dst->format ||
            tmp_frame->width  != FFALIGN(dst->linesize[0], 16) ||
            tmp_frame->height != FFALIGN(dst->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = dst->format;
            tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
            tmp_frame->height = FFALIGN(dst->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            എങ്കിൽ (ret < 0)
                തിരികെ ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    എങ്കിൽ (!s->session_download) {
        എങ്കിൽ (s->child_frames_ref)
            തിരികെ qsv_transfer_data_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        തിരികെ AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst_frame, &out);

    ചെയ്യുക {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, ശൂന്യ, &sync);
        എങ്കിൽ (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } ആകുമ്പോൾ (err == MFX_WRN_DEVICE_BUSY);

    എങ്കിൽ (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    ചെയ്യുക {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } ആകുമ്പോൾ (err == MFX_WRN_IN_EXECUTION);
    എങ്കിൽ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        തിരികെ AVERROR_UNKNOWN;
    }

    എങ്കിൽ (realigned) {
        tmp_frame->width  = dst->width;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                സ്ഥിരം AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   in = {{ 0 }};
    mfxFrameSurface1 *out = (mfxFrameSurface1*)dst->data[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = ശൂന്യ;
    mfxStatus err;
    പൂർണ്ണസംഖ്യ ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    സ്ഥിരം AVFrame *src_frame;
    പൂർണ്ണസംഖ്യ realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 1);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    എങ്കിൽ (src->height & 15 || src->linesize[0] & 15) {
        realigned = 1;
        എങ്കിൽ (tmp_frame->format != src->format ||
            tmp_frame->width  != FFALIGN(src->width, 16) ||
            tmp_frame->height != FFALIGN(src->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = src->format;
            tmp_frame->width  = FFALIGN(src->width, 16);
            tmp_frame->height = FFALIGN(src->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            എങ്കിൽ (ret < 0)
                തിരികെ ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        എങ്കിൽ (ret < 0) {
            av_frame_unref(tmp_frame);
            തിരികെ ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        എങ്കിൽ (ret < 0) {
            av_frame_unref(tmp_frame);
            തിരികെ ret;
        }

        tmp_info = out->Info;
        out->Info.CropW = FFMIN(out->Info.Width,  tmp_frame->width);
        out->Info.CropH = FFMIN(out->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    എങ്കിൽ (!s->session_upload) {
        എങ്കിൽ (s->child_frames_ref)
            തിരികെ qsv_transfer_data_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        തിരികെ AVERROR(ENOSYS);
    }

    in.Info = out->Info;
    map_frame_to_surface(src_frame, &in);

    ചെയ്യുക {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_upload, &in, out, ശൂന്യ, &sync);
        എങ്കിൽ (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } ആകുമ്പോൾ (err == MFX_WRN_DEVICE_BUSY);

    എങ്കിൽ (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    ചെയ്യുക {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } ആകുമ്പോൾ (err == MFX_WRN_IN_EXECUTION);
    എങ്കിൽ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        തിരികെ AVERROR_UNKNOWN;
    }

    എങ്കിൽ (realigned) {
        out->Info.CropW = tmp_info.CropW;
        out->Info.CropH = tmp_info.CropH;
    }

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_dynamic_frames_derive_to(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, പൂർണ്ണസംഖ്യ flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    തിരഞ്ഞെടുപ്പ് (src_ctx->device_ctx->type) {
#എങ്കിൽ CONFIG_VAAPI
    അവസ്ഥ AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        നിർത്തുക;
#endif

#എങ്കിൽ CONFIG_D3D11VA
    അവസ്ഥ AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        എങ്കിൽ (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } അല്ലെങ്കിൽ {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
    നിർത്തുക;
#endif

    സ്ഥിരസ്ഥിതി:
        തിരികെ AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, വലുപ്പം(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_fixed_frames_derive_to(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, പൂർണ്ണസംഖ്യ flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    പൂർണ്ണസംഖ്യ i;

    തിരഞ്ഞെടുപ്പ് (src_ctx->device_ctx->type) {
#എങ്കിൽ CONFIG_VAAPI
    അവസ്ഥ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 വലുപ്പം(*s->handle_pairs_internal));
            എങ്കിൽ (!s->handle_pairs_internal)
                തിരികെ AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             വലുപ്പം(*s->surfaces_internal));
            എങ്കിൽ (!s->surfaces_internal)
                തിരികെ AVERROR(ENOMEM);
            വേണ്ടി (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = src_hwctx->surface_ids + i;
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        നിർത്തുക;
#endif
#എങ്കിൽ CONFIG_D3D11VA
    അവസ്ഥ AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 വലുപ്പം(*s->handle_pairs_internal));
            എങ്കിൽ (!s->handle_pairs_internal)
                തിരികെ AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_ctx->initial_pool_size,
                                             വലുപ്പം(*s->surfaces_internal));
            എങ്കിൽ (!s->surfaces_internal)
                തിരികെ AVERROR(ENOMEM);
            വേണ്ടി (i = 0; i < src_ctx->initial_pool_size; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                എങ്കിൽ (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                } അല്ലെങ്കിൽ {
                    s->handle_pairs_internal[i].second = (mfxMemId)src_hwctx->texture_infos[i].index;
                }
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_size;
            എങ്കിൽ (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            } അല്ലെങ്കിൽ {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
            }
        }
        നിർത്തുക;
#endif
#എങ്കിൽ CONFIG_DXVA2
    അവസ്ഥ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 വലുപ്പം(*s->handle_pairs_internal));
            എങ്കിൽ (!s->handle_pairs_internal)
                തിരികെ AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             വലുപ്പം(*s->surfaces_internal));
            എങ്കിൽ (!s->surfaces_internal)
                തിരികെ AVERROR(ENOMEM);
            വേണ്ടി (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            എങ്കിൽ (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            അല്ലെങ്കിൽ
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        നിർത്തുക;
#endif
    സ്ഥിരസ്ഥിതി:
        തിരികെ AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, പൂർണ്ണസംഖ്യ flags)
{
    എങ്കിൽ (src_ctx->initial_pool_size < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        തിരികെ AVERROR(EINVAL);
    } അല്ലെങ്കിൽ എങ്കിൽ (src_ctx->initial_pool_size == 0) {
        തിരികെ qsv_dynamic_frames_derive_to(dst_ctx, src_ctx, flags);
    } അല്ലെങ്കിൽ {
        തിരികെ qsv_fixed_frames_derive_to(dst_ctx, src_ctx, flags);
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_fixed_pool_map_to(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    പൂർണ്ണസംഖ്യ i, err, index = -1;

    വേണ്ടി (i = 0; i < hwctx->nb_surfaces && index < 0; i++) {
        തിരഞ്ഞെടുപ്പ്(src->format) {
#എങ്കിൽ CONFIG_VAAPI
        അവസ്ഥ AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            എങ്കിൽ (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->data[3])
                index = i;
            നിർത്തുക;
        }
#endif
#എങ്കിൽ CONFIG_D3D11VA
        അവസ്ഥ AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            എങ്കിൽ (pair->first == src->data[0]
                && (pair->second == src->data[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->data[1] == (uint8_t *)0)))
                index = i;
            നിർത്തുക;
        }
#endif
#എങ്കിൽ CONFIG_DXVA2
        അവസ്ഥ AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            എങ്കിൽ (pair->first == src->data[3])
                index = i;
            നിർത്തുക;
        }
#endif
        }
    }
    എങ്കിൽ (index < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        തിരികെ AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, ശൂന്യ, ശൂന്യ);
    എങ്കിൽ (err)
        തിരികെ err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)&hwctx->surfaces[index];

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_internal = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_pairs_internal = (mfxHDLPair *)surfaces_internal->Data.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_frames->data;

    തിരഞ്ഞെടുപ്പ് (src_ctx->format) {
#എങ്കിൽ CONFIG_VAAPI
    അവസ്ഥ AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_pairs_internal->first);

        നിർത്തുക;
    }
#endif

#എങ്കിൽ CONFIG_D3D11VA
    അവസ്ഥ AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        നിർത്തുക;
    }
#endif
    സ്ഥിരസ്ഥിതി:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        നിർത്തുക;
    }

    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_dynamic_pool_map_to(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    mfxFrameSurface1 *surfaces_internal = ശൂന്യ;
    mfxHDLPair *handle_pairs_internal = ശൂന്യ;
    പൂർണ്ണസംഖ്യ ret = 0;

    surfaces_internal = av_calloc(1, വലുപ്പം(*surfaces_internal));
    എങ്കിൽ (!surfaces_internal) {
        ret = AVERROR(ENOMEM);
        പോകുക fail;
    }

    handle_pairs_internal = av_calloc(1, വലുപ്പം(*handle_pairs_internal));
    എങ്കിൽ (!handle_pairs_internal) {
        ret = AVERROR(ENOMEM);
        പോകുക fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_internal);
    എങ്കിൽ (ret < 0)
        പോകുക fail;

    തിരഞ്ഞെടുപ്പ് (src->format) {
#എങ്കിൽ CONFIG_VAAPI
    അവസ്ഥ AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, വലുപ്പം(*surface_id_internal));
        എങ്കിൽ (!surface_id_internal) {
            ret =AVERROR(ENOMEM);
            പോകുക fail;
        }

        *surface_id_internal = (VASurfaceID)(uintptr_t)src->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;

        നിർത്തുക;
    }
#endif

#എങ്കിൽ CONFIG_D3D11VA
    അവസ്ഥ AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_pairs_internal->first = (mfxMemId)src->data[0];

        എങ്കിൽ (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        } അല്ലെങ്കിൽ {
            handle_pairs_internal->second = (mfxMemId)src->data[1];
        }

        നിർത്തുക;
    }
#endif
    സ്ഥിരസ്ഥിതി:
        ret = AVERROR(ENOSYS);
        പോകുക fail;
    }

    surfaces_internal->Data.MemId = (mfxMemId)handle_pairs_internal;

    ret = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_internal);
    എങ്കിൽ (ret)
        പോകുക fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)surfaces_internal;

    തിരികെ 0;

fail:
    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, സ്ഥിരം AVFrame *src, പൂർണ്ണസംഖ്യ flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    എങ്കിൽ (hwctx->nb_surfaces)
        തിരികെ qsv_fixed_pool_map_to(dst_ctx, dst, src, flags);
    അല്ലെങ്കിൽ
        തിരികെ qsv_dynamic_pool_map_to(dst_ctx, dst, src, flags);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_frames_get_constraints(AVHWDeviceContext *ctx,
                                      സ്ഥിരം ശൂന്യം *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    പൂർണ്ണസംഖ്യ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    വലുപ്പം(*constraints->valid_sw_formats));
    എങ്കിൽ (!constraints->valid_sw_formats)
        തിരികെ AVERROR(ENOMEM);

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, വലുപ്പം(*constraints->valid_hw_formats));
    എങ്കിൽ (!constraints->valid_hw_formats)
        തിരികെ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    എങ്കിൽ (hwctx->session)
        MFXClose(hwctx->session);

    എങ്കിൽ (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_buffer_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

സ്ഥിതം mfxIMPL choose_implementation(സ്ഥിരം അക്ഷരം *device, എണ്ണൽ AVHWDeviceType child_device_type)
{
    സ്ഥിതം സ്ഥിരം ഘടന {
        സ്ഥിരം അക്ഷരം *name;
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
    പൂർണ്ണസംഖ്യ i;

    എങ്കിൽ (device) {
        വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            എങ്കിൽ (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                നിർത്തുക;
            }
        എങ്കിൽ (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, ശൂന്യ, 0);
    }

    എങ്കിൽ (impl != MFX_IMPL_SOFTWARE) {
        എങ്കിൽ (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_VIA_D3D11;
        അല്ലെങ്കിൽ എങ്കിൽ (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_VIA_D3D9;
    }

    തിരികെ impl;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        പൂർണ്ണസംഖ്യ flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfxVersion    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfxStatus     err;
    പൂർണ്ണസംഖ്യ ret;

    തിരഞ്ഞെടുപ്പ് (child_device_ctx->type) {
#എങ്കിൽ CONFIG_VAAPI
    അവസ്ഥ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        നിർത്തുക;
#endif
#എങ്കിൽ CONFIG_D3D11VA
    അവസ്ഥ AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        നിർത്തുക;
#endif
#എങ്കിൽ CONFIG_DXVA2
    അവസ്ഥ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        നിർത്തുക;
#endif
    സ്ഥിരസ്ഥിതി:
        ret = AVERROR(ENOSYS);
        പോകുക fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    എങ്കിൽ (ret)
        പോകുക fail;

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    എങ്കിൽ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        പോകുക fail;
    }

    തിരികെ 0;

fail:
    എങ്കിൽ (hwctx->session)
        MFXClose(hwctx->session);

    എങ്കിൽ (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = ശൂന്യ;
    hwctx->loader = ശൂന്യ;
    തിരികെ ret;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, പൂർണ്ണസംഖ്യ flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(വലുപ്പം(*priv));
    എങ്കിൽ (!priv)
        തിരികെ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->സ്വതന്ത്രം = qsv_device_free;

    impl = choose_implementation("hw_any", child_device_ctx->type);
    തിരികെ qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ qsv_device_create(AVHWDeviceContext *ctx, സ്ഥിരം അക്ഷരം *device,
                             AVDictionary *opts, പൂർണ്ണസംഖ്യ flags)
{
    QSVDevicePriv *priv;
    എണ്ണൽ AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    പൂർണ്ണസംഖ്യ ret;

    priv = av_mallocz(വലുപ്പം(*priv));
    എങ്കിൽ (!priv)
        തിരികെ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->സ്വതന്ത്രം        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", ശൂന്യ, 0);
    എങ്കിൽ (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->മൂല്യം);
        എങ്കിൽ (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->മൂല്യം);
            തിരികെ AVERROR(EINVAL);
        }
#എങ്കിൽ QSV_ONEVPL
    } അല്ലെങ്കിൽ എങ്കിൽ (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } അല്ലെങ്കിൽ എങ്കിൽ (CONFIG_DXVA2) {
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
#അല്ലെങ്കിൽ
    } അല്ലെങ്കിൽ എങ്കിൽ (CONFIG_DXVA2) {
        av_log(ശൂന്യ, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } അല്ലെങ്കിൽ എങ്കിൽ (CONFIG_D3D11VA) {
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#endif
    } അല്ലെങ്കിൽ എങ്കിൽ (CONFIG_VAAPI) {
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } അല്ലെങ്കിൽ {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        തിരികെ AVERROR(ENOSYS);
    }

#എങ്കിൽ CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    എങ്കിൽ (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->മൂല്യം);
        തിരികെ AVERROR(EINVAL);
    }
#endif

    child_device_opts = ശൂന്യ;
    തിരഞ്ഞെടുപ്പ് (child_device_type) {
#എങ്കിൽ CONFIG_VAAPI
    അവസ്ഥ AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_set(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_set(&child_device_opts, "driver",    "iHD",    0);
        }
        നിർത്തുക;
#endif
#എങ്കിൽ CONFIG_D3D11VA
    അവസ്ഥ AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_set(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        നിർത്തുക;
#endif
#എങ്കിൽ CONFIG_DXVA2
    അവസ്ഥ AV_HWDEVICE_TYPE_DXVA2:
#എങ്കിൽ QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#endif
        നിർത്തുക;
#endif
    സ്ഥിരസ്ഥിതി:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            തിരികെ AVERROR(ENOSYS);
        }
        നിർത്തുക;
    }

    e = av_dict_get(opts, "child_device", ശൂന്യ, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->മൂല്യം : ശൂന്യ, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->data;

    impl = choose_implementation(device, child_device_type);

    തിരികെ qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

സ്ഥിരം HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_size      = വലുപ്പം(QSVDeviceContext),
    .frames_hwctx_size      = വലുപ്പം(QSVFramesContext),

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

    .pix_fmts = (സ്ഥിരം എണ്ണൽ AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
