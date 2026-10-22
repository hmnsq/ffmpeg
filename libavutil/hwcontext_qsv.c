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

#ଅନ୍ତର୍ଭାଵ <stdatomic.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ <mfxvideo.h>

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଯଦି HAVE_PTHREADS
#ଅନ୍ତର୍ଭାଵ <pthread.h>
#endif

#define COBJMACROS
#ଯଦି CONFIG_VAAPI
#ଅନ୍ତର୍ଭାଵ "hwcontext_vaapi.h"
#endif
#ଯଦି CONFIG_D3D11VA
#ଅନ୍ତର୍ଭାଵ "hwcontext_d3d11va.h"
#endif
#ଯଦି CONFIG_DXVA2
#ଅନ୍ତର୍ଭାଵ <initguid.h>
#ଅନ୍ତର୍ଭାଵ "hwcontext_dxva2.h"
#endif

#ଅନ୍ତର୍ଭାଵ "buffer.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_internal.h"
#ଅନ୍ତର୍ଭାଵ "hwcontext_qsv.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "pixfmt.h"
#ଅନ୍ତର୍ଭାଵ "pixdesc.h"
#ଅନ୍ତର୍ଭାଵ "time.h"
#ଅନ୍ତର୍ଭାଵ "imgutils.h"
#ଅନ୍ତର୍ଭାଵ "avassert.h"

#define QSV_VERSION_ATLEAST(MAJOR, MINOR)   \
    (MFX_VERSION_MAJOR > (MAJOR) ||         \
     MFX_VERSION_MAJOR == (MAJOR) && MFX_VERSION_MINOR >= (MINOR))

#define QSV_RUNTIME_VERSION_ATLEAST(MFX_VERSION, MAJOR, MINOR)          \
    ((MFX_VERSION.Major > (MAJOR)) ||                                   \
     (MFX_VERSION.Major == (MAJOR) && MFX_VERSION.Minor >= (MINOR)))

#define MFX_IMPL_VIA_MASK(impl) (0x0f00 & (impl))
#define QSV_ONEVPL       QSV_VERSION_ATLEAST(2, 0)
#define QSV_HAVE_OPAQUE  !QSV_ONEVPL

#ଯଦି QSV_ONEVPL
#ଅନ୍ତର୍ଭାଵ <mfxdispatcher.h>
#ଅନ୍ୟଥା
#define MFXUnload(a) କର { } ଯେତେବେଳେ(0)
#endif

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfxVersion          ver;
    mfxIMPL             impl;

    ଗଣନା AVHWDeviceType child_device_type;
    ଗଣନା AVPixelFormat  child_pix_fmt;
} QSVDeviceContext;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#ଯଦି HAVE_PTHREADS
    pthread_mutex_t session_lock;
#endif

    AVBufferRef *child_frames_ref;
    mfxFrameSurface1 *surfaces_internal;
    mfxHDLPair *handle_pairs_internal;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା             nb_surfaces_used;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#ଯଦି QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfxExtBuffer *ext_buffers[1];
#endif
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    ଗଣନା AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_shift;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#ଯଦି CONFIG_VAAPI
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
#ଯଦି QSV_VERSION_ATLEAST(1, 31)
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

ବାହ୍ୟ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          ଗଣନା AVHWDeviceType base_dev_type,
                                          ଶୂନ୍ୟ **base_handle);

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                   ଗଣନା AVHWDeviceType base_dev_type,
                                   ଶୂନ୍ୟ **base_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->Data.MemId;
    ବାଛ (base_dev_type) {
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VAAPI:
        base_handle[0] = handle_pair->first;
        ଫେରନ୍ତୁ 0;
#endif
#ଯଦି CONFIG_D3D11VA
    ସ୍ଥିତି AV_HWDEVICE_TYPE_D3D11VA:
        base_handle[0] = handle_pair->first;
        base_handle[1] = handle_pair->second;
        ଫେରନ୍ତୁ 0;
#endif
#ଯଦି CONFIG_DXVA2
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DXVA2:
        base_handle[0] = handle_pair->first;
        ଫେରନ୍ତୁ 0;
#endif
    }
    ଫେରନ୍ତୁ AVERROR(EINVAL);
}

ସ୍ଥିର uint32_t qsv_fourcc_from_pix_fmt(ଗଣନା AVPixelFormat pix_fmt)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        ଯଦି (supported_pixel_formats[i].pix_fmt == pix_fmt)
            ଫେରନ୍ତୁ supported_pixel_formats[i].fourcc;
    }
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର uint16_t qsv_shift_from_pix_fmt(ଗଣନା AVPixelFormat pix_fmt)
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        ଯଦି (supported_pixel_formats[i].pix_fmt == pix_fmt)
            ଫେରନ୍ତୁ supported_pixel_formats[i].mfx_shift;
    }

    ଫେରନ୍ତୁ 0;
}

#ଯଦି CONFIG_D3D11VA
ସ୍ଥିର uint32_t qsv_get_d3d11va_bind_flags(ପୂର୍ଣ୍ଣସଂଖ୍ୟା mem_type)
{
    uint32_t bind_flags = 0;

    ଯଦି ((mem_type & MFX_MEMTYPE_VIDEO_MEMORY_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_INTERNAL_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    ଅନ୍ୟଥା
        bind_flags = D3D11_BIND_DECODER;

    ଯଦି ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    ଫେରନ୍ତୁ bind_flags;
}
#endif

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_fill_border(AVFrame *dst, ଅଚଳ AVFrame *src)
{
    ଅଚଳ AVPixFmtDescriptor *desc;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, planes_nb = 0;
    ଯଦି (dst->format != src->format)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    ପାଇଁ (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    ପାଇଁ (i = 0; i < planes_nb; i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->width,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->width,
                                                 i);
        ଅଚଳ AVComponentDescriptor comp = desc->comp[i];
        ଯଦି (swidth < 0 || dwidth < 0) {
            av_log(ଖାଲି, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        ଯଦି (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        ପାଇଁ (y = 0; y < sheight; y++) {
            ଶୂନ୍ୟ *ଧାଡ଼ି_ptr = dst->data[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(ଧାଡ଼ି_ptr,
                           comp.depth > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        ପାଇଁ (y = sheight; y < dheight; y++) {
            memcpy(dst->data[i]+y*dst->linesize[i],
                   dst->data[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା   hw_handle_supported = 0;
    mfxHandleType handle_type;
    ଗଣନା AVHWDeviceType device_type;
    ଗଣନା AVPixelFormat  pix_fmt;
    mfxStatus err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    ଯଦି (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    ଯଦି (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଯଦି (MFX_IMPL_VIA_VAAPI == MFX_IMPL_VIA_MASK(s->impl)) {
#ଯଦି CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#endif
    } ଅନ୍ୟଥା ଯଦି (MFX_IMPL_VIA_D3D11 == MFX_IMPL_VIA_MASK(s->impl)) {
#ଯଦି CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#endif
    } ଅନ୍ୟଥା ଯଦି (MFX_IMPL_VIA_D3D9 == MFX_IMPL_VIA_MASK(s->impl)) {
#ଯଦି CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#endif
    }

    ଯଦି (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        ଯଦି (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->child_device_type = device_type;
            s->child_pix_fmt     = pix_fmt;
        }
    }
    ଯଦି (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    ଯଦି (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = ଖାଲି;
    s->session_download_init = 0;

    ଯଦି (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = ଖାଲି;
    s->session_upload_init = 0;

#ଯଦି HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_lock);
#endif

    av_freep(&s->mem_ids);
#ଯଦି QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#endif
    av_freep(&s->surfaces_internal);
    av_freep(&s->handle_pairs_internal);
    av_frame_unref(&s->realigned_upload_frame);
    av_frame_unref(&s->realigned_download_frame);
    av_buffer_unref(&s->child_frames_ref);
}

ସ୍ଥିର ଶୂନ୍ୟ qsv_pool_release_dummy(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
}

ସ୍ଥିର ଶୂନ୍ୟ qsv_pool_release(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)data;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.Data.MemId;
    AVHWFramesContext *child_frames_ctx;

    ଯଦି (!s->child_frames_ref)
        ଫେରନ୍ତୁ;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    ଯଦି (!child_frames_ctx->device_ctx)
        ଫେରନ୍ତୁ;

#ଯଦି CONFIG_VAAPI
    ଯଦି (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#endif

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

ସ୍ଥିର AVBufferRef *qsv_fixed_pool_alloc(ଶୂନ୍ୟ *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    ଯଦି (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        ଫେରନ୍ତୁ av_buffer_create((uint8_t*)(s->surfaces_internal + s->nb_surfaces_used - 1),
                                ଆକାର(*hwctx->surfaces), qsv_pool_release_dummy, ଖାଲି, 0);
    }

    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର AVBufferRef *qsv_dynamic_pool_alloc(ଶୂନ୍ୟ *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx;
    QSVSurface *qsv_surface = ଖାଲି;
    mfxHDLPair *handle_pairs_internal = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!s->child_frames_ref)
        ଯାଅ fail;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    ଯଦି (!child_frames_ctx->device_ctx)
        ଯାଅ fail;

#ଯଦି CONFIG_DXVA2
    ଯଦି (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        ଯାଅ fail;
    }
#endif

    qsv_surface = av_calloc(1, ଆକାର(*qsv_surface));
    ଯଦି (!qsv_surface)
        ଯାଅ fail;

    qsv_surface->child_frame = av_frame_alloc();
    ଯଦି (!qsv_surface->child_frame)
        ଯାଅ fail;

    ret = av_hwframe_get_buffer(s->child_frames_ref, qsv_surface->child_frame, 0);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    handle_pairs_internal = av_calloc(1, ଆକାର(*handle_pairs_internal));
    ଯଦି (!handle_pairs_internal)
        ଯାଅ fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    ଯଦି (ret < 0)
        ଯାଅ fail;

#ଯଦି CONFIG_VAAPI
    ଯଦି (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, ଆକାର(*surface_id_internal));
        ଯଦି (!surface_id_internal)
            ଯାଅ fail;

        *surface_id_internal = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
    }
#endif

#ଯଦି CONFIG_D3D11VA
    ଯଦି (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        handle_pairs_internal->first = (mfxMemId)qsv_surface->child_frame->data[0];

        ଯଦି (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        ଅନ୍ୟଥା
            handle_pairs_internal->second = (mfxMemId)qsv_surface->child_frame->data[1];

    }
#endif

    qsv_surface->mfx_surface.Data.MemId = (mfxMemId)handle_pairs_internal;
    ଫେରନ୍ତୁ av_buffer_create((uint8_t *)qsv_surface, ଆକାର(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    ଯଦି (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_pairs_internal);

    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର AVBufferRef *qsv_pool_alloc(ଶୂନ୍ୟ *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    ଯଦି (hwctx->nb_surfaces == 0) {
        ଫେରନ୍ତୁ qsv_dynamic_pool_alloc(opaque, size);
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ qsv_fixed_pool_alloc(opaque, size);
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = ଖାଲି;
    AVBufferRef *child_frames_ref = ଖାଲି;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret = 0;

    ଯଦି (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    ଯଦି (!child_device_ref)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->data;

#ଯଦି CONFIG_VAAPI
    ଯଦି (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#endif
#ଯଦି CONFIG_D3D11VA
    ଯଦି (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        ID3D11Device_AddRef((ID3D11Device*)device_priv->handle);
        child_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#endif
#ଯଦି CONFIG_DXVA2
    ଯଦି (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#endif

    ret = av_hwdevice_ctx_init(child_device_ref);
    ଯଦି (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        ଯାଅ fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    ଯଦି (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->data;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_size = ctx->initial_pool_size;
    child_frames_ctx->width             = FFALIGN(ctx->width, 16);
    child_frames_ctx->height            = FFALIGN(ctx->height, 16);

#ଯଦି CONFIG_D3D11VA
    ଯଦି (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        ଯଦି (hwctx->frame_type == 0)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        ଯଦି (hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
            child_frames_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        child_frames_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->frame_type);
    }
#endif
#ଯଦି CONFIG_DXVA2
    ଯଦି (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        ଯଦି (hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET)
            child_frames_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        ଅନ୍ୟଥା
            child_frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#endif

    ret = av_hwframe_ctx_init(child_frames_ref);
    ଯଦି (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        ଯାଅ fail;
    }

#ଯଦି CONFIG_VAAPI
    ଯଦି (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        ପାଇଁ (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = child_frames_hwctx->surface_ids + i;
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif
#ଯଦି CONFIG_D3D11VA
    ଯଦି (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        ପାଇଁ (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->texture_infos[i].texture;
            ଯଦି(child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            } ଅନ୍ୟଥା {
                s->handle_pairs_internal[i].second = (mfxMemId)child_frames_hwctx->texture_infos[i].index;
            }
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        ଯଦି (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } ଅନ୍ୟଥା {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
#endif
#ଯଦି CONFIG_DXVA2
    ଯଦି (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        ପାଇଁ (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->surfaces[i];
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        ଯଦି (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        ଅନ୍ୟଥା
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = ଖାଲି;

fail:
    av_buffer_unref(&child_device_ref);
    av_buffer_unref(&child_frames_ref);
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    ଅଚଳ AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    ଯଦି (!desc)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    ଯଦି (!fourcc)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    surf->Info.BitDepthLuma   = desc->comp[0].depth;
    surf->Info.BitDepthChroma = desc->comp[0].depth;
    surf->Info.Shift          = qsv_shift_from_pix_fmt(ctx->sw_format);

    ଯଦି (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    ଅନ୍ୟଥା ଯଦି (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    ଅନ୍ୟଥା
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.Width          = FFALIGN(ctx->width, 16);
    surf->Info.CropW          = ctx->width;
    surf->Info.Height         = FFALIGN(ctx->height, 16);
    surf->Info.CropH          = ctx->height;
    surf->Info.FrameRateExtN  = 25;
    surf->Info.FrameRateExtD  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret = 0;

    ଯଦି (ctx->initial_pool_size < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    } ଅନ୍ୟଥା ଯଦି (ctx->initial_pool_size == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;

        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(ଆକାର(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, ଖାଲି);
        ଯଦି (!ffhwframesctx(ctx)->pool_internal)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, ଆକାର(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        frames_hwctx->info = &s->frame_info;
        frames_hwctx->nb_surfaces = 0;

        ଫେରନ୍ତୁ 0;
    }

    s->handle_pairs_internal = av_calloc(ctx->initial_pool_size,
                                         ଆକାର(*s->handle_pairs_internal));
    ଯଦି (!s->handle_pairs_internal)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     ଆକାର(*s->surfaces_internal));
    ଯଦି (!s->surfaces_internal)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (i = 0; i < ctx->initial_pool_size; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_internal[i]);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
    }

#ଯଦି QSV_HAVE_OPAQUE
    ଯଦି (!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
    }
#ଅନ୍ୟଥା
    ret = qsv_init_child_ctx(ctx);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;
#endif

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(ଆକାର(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, ଖାଲି);
    ଯଦି (!ffhwframesctx(ctx)->pool_internal)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    ଯଦି (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        ଫେରନ୍ତୁ MFX_ERR_UNSUPPORTED;
    ଯଦି (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        ଫେରନ୍ତୁ MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->ଅଙ୍କ_Frame_Actual = hwctx->nb_surfaces;

    ଫେରନ୍ତୁ MFX_ERR_NONE;
}

ସ୍ଥିର mfxStatus frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    ଫେରନ୍ତୁ MFX_ERR_NONE;
}

ସ୍ଥିର mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    ଫେରନ୍ତୁ MFX_ERR_UNSUPPORTED;
}

ସ୍ଥିର mfxStatus frame_unlock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    ଫେରନ୍ତୁ MFX_ERR_UNSUPPORTED;
}

ସ୍ଥିର mfxStatus frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    ଯଦି (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    ଫେରନ୍ତୁ MFX_ERR_NONE;
}

#ଯଦି QSV_ONEVPL

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_d3d11_update_config(ଶୂନ୍ୟ *ctx, mfxHDL handle, mfxConfig cfg)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = AVERROR_UNKNOWN;
#ଯଦି CONFIG_D3D11VA
    mfxStatus sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = ଖାଲି;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_ମୂଲ୍ୟ = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (ଶୂନ୍ୟ**)&pDXGIDevice);
    ଯଦି (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        ଯଦି (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            ଫେରନ୍ତୁ ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        ଯଦି (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            ଯାଅ fail;
        }
    } ଅନ୍ୟଥା {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        ଫେରନ୍ତୁ ret;
    }

    impl_ମୂଲ୍ୟ.Type = MFX_VARIANT_TYPE_U16;
    impl_ମୂଲ୍ୟ.Data.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ଅଚଳ mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_ମୂଲ୍ୟ);
    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        ଯାଅ fail;
    }

    impl_ମୂଲ୍ୟ.Type = MFX_VARIANT_TYPE_PTR;
    impl_ମୂଲ୍ୟ.Data.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ଅଚଳ mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_ମୂଲ୍ୟ);
    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        ଯାଅ fail;
    }

    impl_ମୂଲ୍ୟ.Type = MFX_VARIANT_TYPE_U32;
    impl_ମୂଲ୍ୟ.Data.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ଅଚଳ mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_ମୂଲ୍ୟ);
    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        ଯାଅ fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#endif
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_d3d9_update_config(ଶୂନ୍ୟ *ctx, mfxHDL handle, mfxConfig cfg)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = AVERROR_UNKNOWN;
#ଯଦି CONFIG_DXVA2
    mfxStatus sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = ଖାଲି;
    IDirect3DDevice9Ex *device_ex = ଖାଲି;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = ଖାଲି;
    IDirect3D9 *d3d9 = ଖାଲି;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_ମୂଲ୍ୟ = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    ଯଦି (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        ଯାଅ fail;
    }

    hr = IDirect3DDeviceManager9_LockDevice(devmgr, device_handle, &device, TRUE);
    ଯଦି (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        ଯାଅ fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (ଶୂନ୍ୟ **)&device_ex);
    IDirect3DDevice9_Release(device);
    ଯଦି (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        ଯାଅ unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    ଯଦି (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        ଯାଅ unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    ଯଦି (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        ଯାଅ unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (ଶୂନ୍ୟ **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    ଯଦି (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        ଯାଅ unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    ଯଦି (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        ଯାଅ release;
    }

    impl_ମୂଲ୍ୟ.Type = MFX_VARIANT_TYPE_PTR;
    impl_ମୂଲ୍ୟ.Data.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ଅଚଳ mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_ମୂଲ୍ୟ);
    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        ଯାଅ release;
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
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_va_update_config(ଶୂନ୍ୟ *ctx, mfxHDL handle, mfxConfig cfg)
{
#ଯଦି CONFIG_VAAPI
#ଯଦି VA_CHECK_VERSION(1, 15, 0)
    mfxStatus sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_ମୂଲ୍ୟ = {0};

    vas = vaGetDisplayAttributes(dpy, &attr, 1);
    ଯଦି (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_ମୂଲ୍ୟ.Type = MFX_VARIANT_TYPE_U16;
        impl_ମୂଲ୍ୟ.Data.U16 = (attr.ମୂଲ୍ୟ & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ଅଚଳ mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_ମୂଲ୍ୟ);
        ଯଦି (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            ଯାଅ fail;
        }
    } ଅନ୍ୟଥା {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        ଯାଅ fail;
    }

    ଫେରନ୍ତୁ 0;

fail:
#ଅନ୍ୟଥା
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#endif
#endif
    ଫେରନ୍ତୁ AVERROR_UNKNOWN;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_new_mfx_loader(ଶୂନ୍ୟ *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfxVersion *pver,
                              ଶୂନ୍ୟ **ploader)
{
    mfxStatus sts;
    mfxLoader loader = ଖାଲି;
    mfxConfig cfg;
    mfxVariant impl_ମୂଲ୍ୟ = {0};

    *ploader = ଖାଲି;
    loader = MFXLoad();
    ଯଦି (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        ଯାଅ fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    ଯଦି (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        ଯାଅ fail;
    }

    impl_ମୂଲ୍ୟ.Type = MFX_VARIANT_TYPE_U32;
    impl_ମୂଲ୍ୟ.Data.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ଅଚଳ mfxU8 *)"mfxImplDescription.Impl", impl_ମୂଲ୍ୟ);
    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        ଯାଅ fail;
    }

    impl_ମୂଲ୍ୟ.Type = MFX_VARIANT_TYPE_U32;
    impl_ମୂଲ୍ୟ.Data.U32 = pver->Version;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ଅଚଳ mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_ମୂଲ୍ୟ);
    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        ଯାଅ fail;
    }

    impl_ମୂଲ୍ୟ.Type = MFX_VARIANT_TYPE_U32;
    impl_ମୂଲ୍ୟ.Data.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ଅଚଳ mfxU8 *)"mfxImplDescription.VendorID", impl_ମୂଲ୍ୟ);
    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        ଯାଅ fail;
    }

    ଯଦି (MFX_HANDLE_VA_DISPLAY == handle_type) {
        ଯଦି (handle && qsv_va_update_config(ctx, handle, cfg))
            ଯାଅ fail;

        impl_ମୂଲ୍ୟ.Data.U32 = MFX_ACCEL_MODE_VIA_VAAPI;
    } ଅନ୍ୟଥା ଯଦି (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        ଯଦି (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            ଯାଅ fail;

        impl_ମୂଲ୍ୟ.Data.U32 = MFX_ACCEL_MODE_VIA_D3D9;
    } ଅନ୍ୟଥା {
        ଯଦି (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            ଯାଅ fail;

        impl_ମୂଲ୍ୟ.Data.U32 = MFX_ACCEL_MODE_VIA_D3D11;
    }

    impl_ମୂଲ୍ୟ.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ଅଚଳ mfxU8 *)"mfxImplDescription.AccelerationMode", impl_ମୂଲ୍ୟ);
    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        ଯାଅ fail;
    }

    *ploader = loader;

    ଫେରନ୍ତୁ 0;

fail:
    ଯଦି (loader)
        MFXUnload(loader);

    ଫେରନ୍ତୁ AVERROR_UNKNOWN;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_create_mfx_session_from_loader(ଶୂନ୍ୟ *ctx, mfxLoader loader, mfxSession *psession)
{
    mfxStatus sts;
    mfxSession session = ଖାଲି;
    uint32_t impl_idx = 0;
    mfxVersion ver;

    ଯେତେବେଳେ (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        ଯଦି (sts == MFX_ERR_NOT_FOUND)
            ଭାଙ୍ଗ;
        ଅନ୍ୟଥା ଯଦି (sts != MFX_ERR_NONE) {
            impl_idx++;
            ଜାରି;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        ଯଦି (sts == MFX_ERR_NONE)
            ଭାଙ୍ଗ;

        impl_idx++;
    }

    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        ଯାଅ fail;
    }

    sts = MFXQueryVersion(session, &ver);
    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        ଯାଅ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    ଫେରନ୍ତୁ 0;

fail:
    ଯଦି (session)
        MFXClose(session);

    ଫେରନ୍ତୁ AVERROR_UNKNOWN;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_create_mfx_session(ଶୂନ୍ୟ *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  ଶୂନ୍ୟ **ploader)
{
    mfxLoader loader = ଖାଲି;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    ଯଦି (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        ଫେରନ୍ତୁ AVERROR(EXDEV);
    }

    *psession = ଖାଲି;

    ଯଦି (!*ploader) {
        ଯଦି (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (ଶୂନ୍ୟ **)&loader))
            ଯାଅ fail;

        av_assert0(loader);
    } ଅନ୍ୟଥା
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    ଯଦି (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        ଯାଅ fail;

    ଯଦି (!*ploader)
        *ploader = loader;

    ଫେରନ୍ତୁ 0;

fail:
    ଯଦି (!*ploader && loader)
        MFXUnload(loader);

    ଫେରନ୍ତୁ AVERROR_UNKNOWN;
}

#ଅନ୍ୟଥା

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_create_mfx_session(ଶୂନ୍ୟ *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  ଶୂନ୍ୟ **ploader)
{
    mfxVersion ver;
    mfxStatus sts;
    mfxSession session = ଖାଲି;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    *ploader = ଖାଲି;
    *psession = ଖାଲି;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        ଯାଅ fail;
    }

    sts = MFXQueryVersion(session, &ver);
    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        ଯାଅ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    ଯଦି (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        ଯାଅ fail;
    }

    *psession = session;

    ଫେରନ୍ତୁ 0;

fail:
    ଯଦି (session)
        MFXClose(session);

    ଫେରନ୍ତୁ AVERROR_UNKNOWN;
}

#endif

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_init_internal_session(AVHWFramesContext *ctx,
                                     mfxSession *session, ପୂର୍ଣ୍ଣସଂଖ୍ୟା upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା opaque = 0;

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
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    ଶୂନ୍ୟ             **loader = &hwctx->loader;
    mfxSession parent_session = hwctx->session;
    mfxIMPL impl;
    mfxVersion ver;

    err = MFXQueryIMPL(parent_session, &impl);
    ଯଦି (err == MFX_ERR_NONE)
        err = MFXQueryVersion(parent_session, &ver);
    ଯଦି (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

#ଯଦି QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    ଯଦି (ret)
        ଯାଅ fail;

    ଯଦି (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        ଯଦି (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            ଯାଅ fail;
        }
    }

    ଯଦି (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        ଯଦି (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            ଯାଅ fail;
        }
    }

    ଯଦି (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        ଯଦି (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            ଯାଅ fail;
        }
    }

    memset(&par, 0, ଆକାର(par));

    ଯଦି (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_OUT_VIDEO_MEMORY :
                                 MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
#ଯଦି QSV_HAVE_OPAQUE
    ଅନ୍ୟଥା {
        par.ExtParam    = s->ext_buffers;
        par.ଅଙ୍କ_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
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
    ଯଦି (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        ଯାଅ fail;
    }

    ଫେରନ୍ତୁ 0;

fail:
    ଯଦି (*session)
        MFXClose(*session);

    *session = ଖାଲି;

    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା opaque = 0;

    uint32_t fourcc;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, ret;

#ଯଦି QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    ଯଦି (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    ଯଦି (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        ଯଦି (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            ଫେରନ୍ତୁ ret;
        }
    }

    ଯଦି (!opaque) {
        s->mem_ids = av_calloc(frames_hwctx->nb_surfaces, ଆକାର(*s->mem_ids));
        ଯଦି (!s->mem_ids)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        ପାଇଁ (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].Data.MemId;
    }
#ଯଦି QSV_HAVE_OPAQUE
    ଅନ୍ୟଥା {
        s->surface_ptrs = av_calloc(frames_hwctx->nb_surfaces,
                                    ଆକାର(*s->surface_ptrs));
        ଯଦି (!s->surface_ptrs)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        ପାଇଁ (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.ଅଙ୍କ_Surface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = ଆକାର(s->opaque_alloc);

        s->ext_buffers[0] = (mfxExtBuffer*)&s->opaque_alloc;
    }
#endif

    s->session_download = ଖାଲି;
    s->session_upload   = ଖାଲି;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#ଯଦି HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, ଖାଲି);
#endif

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ଯଦି (!frame->buf[0])
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_QSV;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    ଗଣନା AVHWFrameTransferDirection dir,
                                    ଗଣନା AVPixelFormat **formats)
{
    ଗଣନା AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ଆକାର(*fmts));
    ଯଦି (!fmts)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ବାଛ (dst_ctx->device_ctx->type) {
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               ଆକାର(*dst_hwctx->surface_ids));
            ଯଦି (!dst_hwctx->surface_ids)
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            ପାଇଁ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        ଭାଙ୍ଗ;
#endif
#ଯଦି CONFIG_D3D11VA
    ସ୍ଥିତି AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_size = src_ctx->initial_pool_size;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 ଆକାର(*dst_hwctx->texture_infos));
            ଯଦି (!dst_hwctx->texture_infos)
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            ଯଦି (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            ପାଇଁ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].index = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            ଯଦି (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } ଅନ୍ୟଥା
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        ଭାଙ୍ଗ;
#endif
#ଯଦି CONFIG_DXVA2
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            ଆକାର(*dst_hwctx->surfaces));
            ଯଦି (!dst_hwctx->surfaces)
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            ପାଇଁ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            ଯଦି (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            ଅନ୍ୟଥା
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        ଭାଙ୍ଗ;
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->data[3];
    AVHWFramesContext *child_frames_ctx;
    ଅଚଳ AVPixFmtDescriptor *desc;
    uint8_t *child_data;
    AVFrame *dummy;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    ଯଦି (!s->child_frames_ref)
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;

    ବାଛ (child_frames_ctx->device_ctx->type) {
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_data = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        ଭାଙ୍ଗ;
    }
#endif
#ଯଦି CONFIG_D3D11VA
    ସ୍ଥିତି AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        ଭାଙ୍ଗ;
    }
#endif
#ଯଦି CONFIG_DXVA2
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        ଭାଙ୍ଗ;
    }
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    ଯଦି (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, ଖାଲି, ଖାଲି);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;

        dst->width   = src->width;
        dst->height  = src->height;

       ଯଦି (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
            dst->data[0] = pair->first;
            dst->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } ଅନ୍ୟଥା {
            dst->data[3] = child_data;
        }

        ଫେରନ୍ତୁ 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    ଯଦି (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    ଯଦି (!dummy)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    dummy->buf[0]        = av_buffer_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_buffer_ref(s->child_frames_ref);
    ଯଦି (!dummy->buf[0] || !dummy->hw_frames_ctx)
        ଯାଅ fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;

    ଯଦି (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        dummy->data[0] = pair->first;
        dummy->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } ଅନ୍ୟଥା {
        dummy->data[3] = child_data;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_transfer_data_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   ଅଚଳ AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା download = !!src->hw_frames_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->data[3] : dst->data[3]);

    AVFrame *dummy;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    dummy = av_frame_alloc();
    ଯଦି (!dummy)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->data[3]       = surf->Data.MemId;
    dummy->hw_frames_ctx = s->child_frames_ref;

    ret = download ? av_hwframe_transfer_data(dst, dummy, 0) :
                     av_hwframe_transfer_data(dummy, src, 0);

    dummy->buf[0]        = ଖାଲି;
    dummy->data[3]       = ଖାଲି;
    dummy->hw_frames_ctx = ଖାଲି;

    av_frame_free(&dummy);

    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା map_frame_to_surface(ଅଚଳ AVFrame *frame, mfxFrameSurface1 *surface)
{
    ବାଛ (frame->format) {
    ସ୍ଥିତି AV_PIX_FMT_NV12:
    ସ୍ଥିତି AV_PIX_FMT_P010:
    ସ୍ଥିତି AV_PIX_FMT_P012:
        surface->Data.Y  = frame->data[0];
        surface->Data.UV = frame->data[1];
        ଭାଙ୍ଗ;

    ସ୍ଥିତି AV_PIX_FMT_YUV420P:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[1];
        surface->Data.V = frame->data[2];
        ଭାଙ୍ଗ;

    ସ୍ଥିତି AV_PIX_FMT_BGRA:
        surface->Data.B = frame->data[0];
        surface->Data.G = frame->data[0] + 1;
        surface->Data.R = frame->data[0] + 2;
        surface->Data.A = frame->data[0] + 3;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_PIX_FMT_YUYV422:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.V = frame->data[0] + 3;
        ଭାଙ୍ଗ;

    ସ୍ଥିତି AV_PIX_FMT_Y210:
    ସ୍ଥିତି AV_PIX_FMT_Y212:
        surface->Data.Y16 = (mfxU16 *)frame->data[0];
        surface->Data.U16 = (mfxU16 *)frame->data[0] + 1;
        surface->Data.V16 = (mfxU16 *)frame->data[0] + 3;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_PIX_FMT_VUYX:
        surface->Data.V = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.Y = frame->data[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 3;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_PIX_FMT_XV30:
        surface->Data.U = frame->data[0];
        ଭାଙ୍ଗ;
    ସ୍ଥିତି AV_PIX_FMT_XV36:
        surface->Data.U = frame->data[0];
        surface->Data.Y = frame->data[0] + 2;
        surface->Data.V = frame->data[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 6;
        ଭାଙ୍ଗ;
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_PIX_FMT_UYVY422:
        surface->Data.Y = frame->data[0] + 1;
        surface->Data.U = frame->data[0];
        surface->Data.V = frame->data[0] + 2;
        ଭାଙ୍ଗ;
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ MFX_ERR_UNSUPPORTED;
    }
    surface->Data.Pitch     = frame->linesize[0];
    surface->Data.TimeStamp = frame->pts;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_internal_session_check_init(AVHWFramesContext *ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    ଯଦି (atomic_load(inited))
        ଫେରନ୍ତୁ 0;

#ଯଦି HAVE_PTHREADS
    pthread_mutex_lock(&s->session_lock);
#endif

    ଯଦି (!atomic_load(inited)) {
        ret = qsv_init_internal_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#ଯଦି HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_lock);
#endif

    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ଅଚଳ AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->data[3];

    mfxSyncPoint sync = ଖାଲି;
    mfxStatus err;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 0);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    ଯଦି (dst->height & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        ଯଦି (tmp_frame->format != dst->format ||
            tmp_frame->width  != FFALIGN(dst->linesize[0], 16) ||
            tmp_frame->height != FFALIGN(dst->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = dst->format;
            tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
            tmp_frame->height = FFALIGN(dst->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            ଯଦି (ret < 0)
                ଫେରନ୍ତୁ ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    ଯଦି (!s->session_download) {
        ଯଦି (s->child_frames_ref)
            ଫେରନ୍ତୁ qsv_transfer_data_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst_frame, &out);

    କର {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, ଖାଲି, &sync);
        ଯଦି (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } ଯେତେବେଳେ (err == MFX_WRN_DEVICE_BUSY);

    ଯଦି (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    କର {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } ଯେତେବେଳେ (err == MFX_WRN_IN_EXECUTION);
    ଯଦି (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଯଦି (realigned) {
        tmp_frame->width  = dst->width;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                ଅଚଳ AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   in = {{ 0 }};
    mfxFrameSurface1 *out = (mfxFrameSurface1*)dst->data[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = ଖାଲି;
    mfxStatus err;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    ଅଚଳ AVFrame *src_frame;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 1);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    ଯଦି (src->height & 15 || src->linesize[0] & 15) {
        realigned = 1;
        ଯଦି (tmp_frame->format != src->format ||
            tmp_frame->width  != FFALIGN(src->width, 16) ||
            tmp_frame->height != FFALIGN(src->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = src->format;
            tmp_frame->width  = FFALIGN(src->width, 16);
            tmp_frame->height = FFALIGN(src->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            ଯଦି (ret < 0)
                ଫେରନ୍ତୁ ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        ଯଦି (ret < 0) {
            av_frame_unref(tmp_frame);
            ଫେରନ୍ତୁ ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        ଯଦି (ret < 0) {
            av_frame_unref(tmp_frame);
            ଫେରନ୍ତୁ ret;
        }

        tmp_info = out->Info;
        out->Info.CropW = FFMIN(out->Info.Width,  tmp_frame->width);
        out->Info.CropH = FFMIN(out->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    ଯଦି (!s->session_upload) {
        ଯଦି (s->child_frames_ref)
            ଫେରନ୍ତୁ qsv_transfer_data_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    in.Info = out->Info;
    map_frame_to_surface(src_frame, &in);

    କର {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_upload, &in, out, ଖାଲି, &sync);
        ଯଦି (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } ଯେତେବେଳେ (err == MFX_WRN_DEVICE_BUSY);

    ଯଦି (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    କର {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } ଯେତେବେଳେ (err == MFX_WRN_IN_EXECUTION);
    ଯଦି (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        ଫେରନ୍ତୁ AVERROR_UNKNOWN;
    }

    ଯଦି (realigned) {
        out->Info.CropW = tmp_info.CropW;
        out->Info.CropH = tmp_info.CropH;
    }

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_dynamic_frames_derive_to(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    ବାଛ (src_ctx->device_ctx->type) {
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        ଭାଙ୍ଗ;
#endif

#ଯଦି CONFIG_D3D11VA
    ସ୍ଥିତି AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        ଯଦି (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } ଅନ୍ୟଥା {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
    ଭାଙ୍ଗ;
#endif

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, ଆକାର(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_fixed_frames_derive_to(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ବାଛ (src_ctx->device_ctx->type) {
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 ଆକାର(*s->handle_pairs_internal));
            ଯଦି (!s->handle_pairs_internal)
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             ଆକାର(*s->surfaces_internal));
            ଯଦି (!s->surfaces_internal)
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            ପାଇଁ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = src_hwctx->surface_ids + i;
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        ଭାଙ୍ଗ;
#endif
#ଯଦି CONFIG_D3D11VA
    ସ୍ଥିତି AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 ଆକାର(*s->handle_pairs_internal));
            ଯଦି (!s->handle_pairs_internal)
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_ctx->initial_pool_size,
                                             ଆକାର(*s->surfaces_internal));
            ଯଦି (!s->surfaces_internal)
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            ପାଇଁ (i = 0; i < src_ctx->initial_pool_size; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                ଯଦି (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                } ଅନ୍ୟଥା {
                    s->handle_pairs_internal[i].second = (mfxMemId)src_hwctx->texture_infos[i].index;
                }
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_size;
            ଯଦି (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            } ଅନ୍ୟଥା {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
            }
        }
        ଭାଙ୍ଗ;
#endif
#ଯଦି CONFIG_DXVA2
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 ଆକାର(*s->handle_pairs_internal));
            ଯଦି (!s->handle_pairs_internal)
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             ଆକାର(*s->surfaces_internal));
            ଯଦି (!s->surfaces_internal)
                ଫେରନ୍ତୁ AVERROR(ENOMEM);
            ପାଇଁ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            ଯଦି (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            ଅନ୍ୟଥା
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        ଭାଙ୍ଗ;
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    ଯଦି (src_ctx->initial_pool_size < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    } ଅନ୍ୟଥା ଯଦି (src_ctx->initial_pool_size == 0) {
        ଫେରନ୍ତୁ qsv_dynamic_frames_derive_to(dst_ctx, src_ctx, flags);
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ qsv_fixed_frames_derive_to(dst_ctx, src_ctx, flags);
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_fixed_pool_map_to(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, err, index = -1;

    ପାଇଁ (i = 0; i < hwctx->nb_surfaces && index < 0; i++) {
        ବାଛ(src->format) {
#ଯଦି CONFIG_VAAPI
        ସ୍ଥିତି AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            ଯଦି (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->data[3])
                index = i;
            ଭାଙ୍ଗ;
        }
#endif
#ଯଦି CONFIG_D3D11VA
        ସ୍ଥିତି AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            ଯଦି (pair->first == src->data[0]
                && (pair->second == src->data[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->data[1] == (uint8_t *)0)))
                index = i;
            ଭାଙ୍ଗ;
        }
#endif
#ଯଦି CONFIG_DXVA2
        ସ୍ଥିତି AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            ଯଦି (pair->first == src->data[3])
                index = i;
            ଭାଙ୍ଗ;
        }
#endif
        }
    }
    ଯଦି (index < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, ଖାଲି, ଖାଲି);
    ଯଦି (err)
        ଫେରନ୍ତୁ err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)&hwctx->surfaces[index];

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_internal = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_pairs_internal = (mfxHDLPair *)surfaces_internal->Data.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_frames->data;

    ବାଛ (src_ctx->format) {
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_pairs_internal->first);

        ଭାଙ୍ଗ;
    }
#endif

#ଯଦି CONFIG_D3D11VA
    ସ୍ଥିତି AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        ଭାଙ୍ଗ;
    }
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        ଭାଙ୍ଗ;
    }

    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_dynamic_pool_map_to(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    mfxFrameSurface1 *surfaces_internal = ଖାଲି;
    mfxHDLPair *handle_pairs_internal = ଖାଲି;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    surfaces_internal = av_calloc(1, ଆକାର(*surfaces_internal));
    ଯଦି (!surfaces_internal) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    handle_pairs_internal = av_calloc(1, ଆକାର(*handle_pairs_internal));
    ଯଦି (!handle_pairs_internal) {
        ret = AVERROR(ENOMEM);
        ଯାଅ fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_internal);
    ଯଦି (ret < 0)
        ଯାଅ fail;

    ବାଛ (src->format) {
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, ଆକାର(*surface_id_internal));
        ଯଦି (!surface_id_internal) {
            ret =AVERROR(ENOMEM);
            ଯାଅ fail;
        }

        *surface_id_internal = (VASurfaceID)(uintptr_t)src->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;

        ଭାଙ୍ଗ;
    }
#endif

#ଯଦି CONFIG_D3D11VA
    ସ୍ଥିତି AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_pairs_internal->first = (mfxMemId)src->data[0];

        ଯଦି (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        } ଅନ୍ୟଥା {
            handle_pairs_internal->second = (mfxMemId)src->data[1];
        }

        ଭାଙ୍ଗ;
    }
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ret = AVERROR(ENOSYS);
        ଯାଅ fail;
    }

    surfaces_internal->Data.MemId = (mfxMemId)handle_pairs_internal;

    ret = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_internal);
    ଯଦି (ret)
        ଯାଅ fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)surfaces_internal;

    ଫେରନ୍ତୁ 0;

fail:
    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ଅଚଳ AVFrame *src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    ଯଦି (hwctx->nb_surfaces)
        ଫେରନ୍ତୁ qsv_fixed_pool_map_to(dst_ctx, dst, src, flags);
    ଅନ୍ୟଥା
        ଫେରନ୍ତୁ qsv_dynamic_pool_map_to(dst_ctx, dst, src, flags);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_frames_get_constraints(AVHWDeviceContext *ctx,
                                      ଅଚଳ ଶୂନ୍ୟ *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    ଆକାର(*constraints->valid_sw_formats));
    ଯଦି (!constraints->valid_sw_formats)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ଆକାର(*constraints->valid_hw_formats));
    ଯଦି (!constraints->valid_hw_formats)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    ଯଦି (hwctx->session)
        MFXClose(hwctx->session);

    ଯଦି (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_buffer_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

ସ୍ଥିର mfxIMPL choose_implementation(ଅଚଳ ଅକ୍ଷର *device, ଗଣନା AVHWDeviceType child_device_type)
{
    ସ୍ଥିର ଅଚଳ ସଂରଚନା {
        ଅଚଳ ଅକ୍ଷର *name;
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
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ଯଦି (device) {
        ପାଇଁ (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            ଯଦି (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                ଭାଙ୍ଗ;
            }
        ଯଦି (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, ଖାଲି, 0);
    }

    ଯଦି (impl != MFX_IMPL_SOFTWARE) {
        ଯଦି (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_VIA_D3D11;
        ଅନ୍ୟଥା ଯଦି (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_VIA_D3D9;
    }

    ଫେରନ୍ତୁ impl;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfxVersion    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfxStatus     err;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ବାଛ (child_device_ctx->type) {
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        ଭାଙ୍ଗ;
#endif
#ଯଦି CONFIG_D3D11VA
    ସ୍ଥିତି AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        ଭାଙ୍ଗ;
#endif
#ଯଦି CONFIG_DXVA2
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        ଭାଙ୍ଗ;
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ret = AVERROR(ENOSYS);
        ଯାଅ fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    ଯଦି (ret)
        ଯାଅ fail;

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    ଯଦି (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        ଯାଅ fail;
    }

    ଫେରନ୍ତୁ 0;

fail:
    ଯଦି (hwctx->session)
        MFXClose(hwctx->session);

    ଯଦି (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = ଖାଲି;
    hwctx->loader = ଖାଲି;
    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(ଆକାର(*priv));
    ଯଦି (!priv)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ମୁକ୍ତ = qsv_device_free;

    impl = choose_implementation("hw_any", child_device_ctx->type);
    ଫେରନ୍ତୁ qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା qsv_device_create(AVHWDeviceContext *ctx, ଅଚଳ ଅକ୍ଷର *device,
                             AVDictionary *opts, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    QSVDevicePriv *priv;
    ଗଣନା AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    priv = av_mallocz(ଆକାର(*priv));
    ଯଦି (!priv)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ମୁକ୍ତ        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", ଖାଲି, 0);
    ଯଦି (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->ମୂଲ୍ୟ);
        ଯଦି (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->ମୂଲ୍ୟ);
            ଫେରନ୍ତୁ AVERROR(EINVAL);
        }
#ଯଦି QSV_ONEVPL
    } ଅନ୍ୟଥା ଯଦି (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } ଅନ୍ୟଥା ଯଦି (CONFIG_DXVA2) {
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
#ଅନ୍ୟଥା
    } ଅନ୍ୟଥା ଯଦି (CONFIG_DXVA2) {
        av_log(ଖାଲି, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } ଅନ୍ୟଥା ଯଦି (CONFIG_D3D11VA) {
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#endif
    } ଅନ୍ୟଥା ଯଦି (CONFIG_VAAPI) {
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } ଅନ୍ୟଥା {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        ଫେରନ୍ତୁ AVERROR(ENOSYS);
    }

#ଯଦି CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    ଯଦି (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->ମୂଲ୍ୟ);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
#endif

    child_device_opts = ଖାଲି;
    ବାଛ (child_device_type) {
#ଯଦି CONFIG_VAAPI
    ସ୍ଥିତି AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_set(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_set(&child_device_opts, "driver",    "iHD",    0);
        }
        ଭାଙ୍ଗ;
#endif
#ଯଦି CONFIG_D3D11VA
    ସ୍ଥିତି AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_set(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        ଭାଙ୍ଗ;
#endif
#ଯଦି CONFIG_DXVA2
    ସ୍ଥିତି AV_HWDEVICE_TYPE_DXVA2:
#ଯଦି QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#endif
        ଭାଙ୍ଗ;
#endif
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            ଫେରନ୍ତୁ AVERROR(ENOSYS);
        }
        ଭାଙ୍ଗ;
    }

    e = av_dict_get(opts, "child_device", ଖାଲି, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->ମୂଲ୍ୟ : ଖାଲି, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->data;

    impl = choose_implementation(device, child_device_type);

    ଫେରନ୍ତୁ qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

ଅଚଳ HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_size      = ଆକାର(QSVDeviceContext),
    .frames_hwctx_size      = ଆକାର(QSVFramesContext),

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

    .pix_fmts = (ଅଚଳ ଗଣନା AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
