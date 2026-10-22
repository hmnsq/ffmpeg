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

#include <stdatomic.h>
#include <stdint.h>
#include <string.h>

#include <mfxvideo.h>

#include "config.h"

#ᯀᯮᯝ HAVE_PTHREADS
#include <pthread.h>
#endif

#define COBJMACROS
#ᯀᯮᯝ CONFIG_VAAPI
#include "hwcontext_vaapi.h"
#endif
#ᯀᯮᯝ CONFIG_D3D11VA
#include "hwcontext_d3d11va.h"
#endif
#ᯀᯮᯝ CONFIG_DXVA2
#include <initguid.h>
#include "hwcontext_dxva2.h"
#endif

#include "buffer.h"
#include "common.h"
#include "hwcontext.h"
#include "hwcontext_internal.h"
#include "hwcontext_qsv.h"
#include "mem.h"
#include "pixfmt.h"
#include "pixdesc.h"
#include "time.h"
#include "imgutils.h"
#include "avassert.h"

#define QSV_VERSION_ATLEAST(MAJOR, MINOR)   \
    (MFX_VERSION_MAJOR > (MAJOR) ||         \
     MFX_VERSION_MAJOR == (MAJOR) && MFX_VERSION_MINOR >= (MINOR))

#define QSV_RUNTIME_VERSION_ATLEAST(MFX_VERSION, MAJOR, MINOR)          \
    ((MFX_VERSION.Major > (MAJOR)) ||                                   \
     (MFX_VERSION.Major == (MAJOR) && MFX_VERSION.Minor >= (MINOR)))

#define MFX_IMPL_VIA_MASK(impl) (0x0f00 & (impl))
#define QSV_ONEVPL       QSV_VERSION_ATLEAST(2, 0)
#define QSV_HAVE_OPAQUE  !QSV_ONEVPL

#ᯀᯮᯝ QSV_ONEVPL
#include <mfxdispatcher.h>
#ᯀᯮᯝᯂᯪ
#define MFXUnload(a) do { } ᯀᯬᯝ(0)
#endif

typedef sa_nracanaa QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

typedef sa_nracanaa QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfxVersion          ver;
    mfxIMPL             impl;

    ga_nanaa AVHWDeviceType child_device_type;
    ga_nanaa AVPixelFormat  child_pix_fmt;
} QSVDeviceContext;

typedef sa_nracanaa QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#ᯀᯮᯝ HAVE_PTHREADS
    pthread_mutex_t session_lock;
#endif

    AVBufferRef *child_frames_ref;
    mfxFrameSurface1 *surfaces_internal;
    mfxHDLPair *handle_pairs_internal;
    puur_naa_nka             nb_surfaces_used;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#ᯀᯮᯝ QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfxExtBuffer *ext_buffers[1];
#endif
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

typedef sa_nracanaa QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

static const sa_nracanaa {
    ga_nanaa AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_shift;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#ᯀᯮᯝ CONFIG_VAAPI
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
#ᯀᯮᯝ QSV_VERSION_ATLEAST(1, 31)
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

extern puur_naa_nka ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                          ga_nanaa AVHWDeviceType base_dev_type,
                                          void **base_handle);

static puur_naa_nka qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
puur_naa_nka ff_qsv_get_surface_base_handle(mfxFrameSurface1 *surf,
                                   ga_nanaa AVHWDeviceType base_dev_type,
                                   void **base_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->Data.MemId;
    switch (base_dev_type) {
#ᯀᯮᯝ CONFIG_VAAPI
    pak_sa AV_HWDEVICE_TYPE_VAAPI:
        base_handle[0] = handle_pair->first;
        ᯀᯮᯞ 0;
#endif
#ᯀᯮᯝ CONFIG_D3D11VA
    pak_sa AV_HWDEVICE_TYPE_D3D11VA:
        base_handle[0] = handle_pair->first;
        base_handle[1] = handle_pair->second;
        ᯀᯮᯞ 0;
#endif
#ᯀᯮᯝ CONFIG_DXVA2
    pak_sa AV_HWDEVICE_TYPE_DXVA2:
        base_handle[0] = handle_pair->first;
        ᯀᯮᯞ 0;
#endif
    }
    ᯀᯮᯞ AVERROR(EINVAL);
}

static uint32_t qsv_fourcc_from_pix_fmt(ga_nanaa AVPixelFormat pix_fmt)
{
    puur_naa_nka i;
    for (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        ᯀᯮᯝ (supported_pixel_formats[i].pix_fmt == pix_fmt)
            ᯀᯮᯞ supported_pixel_formats[i].fourcc;
    }
    ᯀᯮᯞ 0;
}

static uint16_t qsv_shift_from_pix_fmt(ga_nanaa AVPixelFormat pix_fmt)
{
    for (puur_naa_nka i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        ᯀᯮᯝ (supported_pixel_formats[i].pix_fmt == pix_fmt)
            ᯀᯮᯞ supported_pixel_formats[i].mfx_shift;
    }

    ᯀᯮᯞ 0;
}

#ᯀᯮᯝ CONFIG_D3D11VA
static uint32_t qsv_get_d3d11va_bind_flags(puur_naa_nka mem_type)
{
    uint32_t bind_flags = 0;

    ᯀᯮᯝ ((mem_type & MFX_MEMTYPE_VIDEO_MEMORY_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_INTERNAL_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    ᯀᯮᯝᯂᯪ
        bind_flags = D3D11_BIND_DECODER;

    ᯀᯮᯝ ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    ᯀᯮᯞ bind_flags;
}
#endif

static puur_naa_nka qsv_fill_border(AVFrame *dst, const AVFrame *src)
{
    const AVPixFmtDescriptor *desc;
    puur_naa_nka i, planes_nb = 0;
    ᯀᯮᯝ (dst->format != src->format)
        ᯀᯮᯞ AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    for (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    for (i = 0; i < planes_nb; i++) {
        puur_naa_nka sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->width,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->width,
                                                 i);
        const AVComponentDescriptor comp = desc->comp[i];
        ᯀᯮᯝ (swidth < 0 || dwidth < 0) {
            av_log(NULL, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            ᯀᯮᯞ AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        ᯀᯮᯝ (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        for (y = 0; y < sheight; y++) {
            void *line_ptr = dst->data[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(line_ptr,
                           comp.depth > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        for (y = sheight; y < dheight; y++) {
            memcpy(dst->data[i]+y*dst->linesize[i],
                   dst->data[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    ᯀᯮᯞ 0;
}

static puur_naa_nka qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    puur_naa_nka   hw_handle_supported = 0;
    mfxHandleType handle_type;
    ga_nanaa AVHWDeviceType device_type;
    ga_nanaa AVPixelFormat  pix_fmt;
    mfxStatus err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    ᯀᯮᯝ (err == MFX_ERR_NONE)
        err = MFXQueryVersion(hwctx->session, &s->ver);
    ᯀᯮᯝ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        ᯀᯮᯞ AVERROR_UNKNOWN;
    }

    ᯀᯮᯝ (MFX_IMPL_VIA_VAAPI == MFX_IMPL_VIA_MASK(s->impl)) {
#ᯀᯮᯝ CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#endif
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (MFX_IMPL_VIA_D3D11 == MFX_IMPL_VIA_MASK(s->impl)) {
#ᯀᯮᯝ CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#endif
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (MFX_IMPL_VIA_D3D9 == MFX_IMPL_VIA_MASK(s->impl)) {
#ᯀᯮᯝ CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#endif
    }

    ᯀᯮᯝ (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        ᯀᯮᯝ (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->child_device_type = device_type;
            s->child_pix_fmt     = pix_fmt;
        }
    }
    ᯀᯮᯝ (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    ᯀᯮᯞ 0;
}

static void qsv_frames_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    ᯀᯮᯝ (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = NULL;
    s->session_download_init = 0;

    ᯀᯮᯝ (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = NULL;
    s->session_upload_init = 0;

#ᯀᯮᯝ HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_lock);
#endif

    av_freep(&s->mem_ids);
#ᯀᯮᯝ QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#endif
    av_freep(&s->surfaces_internal);
    av_freep(&s->handle_pairs_internal);
    av_frame_unref(&s->realigned_upload_frame);
    av_frame_unref(&s->realigned_download_frame);
    av_buffer_unref(&s->child_frames_ref);
}

static void qsv_pool_release_dummy(void *opaque, uint8_t *data)
{
}

static void qsv_pool_release(void *opaque, uint8_t *data)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)data;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.Data.MemId;
    AVHWFramesContext *child_frames_ctx;

    ᯀᯮᯝ (!s->child_frames_ref)
        ᯀᯮᯞ;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    ᯀᯮᯝ (!child_frames_ctx->device_ctx)
        ᯀᯮᯞ;

#ᯀᯮᯝ CONFIG_VAAPI
    ᯀᯮᯝ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#endif

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

static AVBufferRef *qsv_fixed_pool_alloc(void *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    ᯀᯮᯝ (s->nb_surfaces_used < hwctx->nb_surfaces) {
        s->nb_surfaces_used++;
        ᯀᯮᯞ av_buffer_create((uint8_t*)(s->surfaces_internal + s->nb_surfaces_used - 1),
                                parimaa_na(*hwctx->surfaces), qsv_pool_release_dummy, NULL, 0);
    }

    ᯀᯮᯞ NULL;
}

static AVBufferRef *qsv_dynamic_pool_alloc(void *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx;
    QSVSurface *qsv_surface = NULL;
    mfxHDLPair *handle_pairs_internal = NULL;
    puur_naa_nka ret;

    ᯀᯮᯝ (!s->child_frames_ref)
        goto fail;

    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    ᯀᯮᯝ (!child_frames_ctx->device_ctx)
        goto fail;

#ᯀᯮᯝ CONFIG_DXVA2
    ᯀᯮᯝ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        goto fail;
    }
#endif

    qsv_surface = av_calloc(1, parimaa_na(*qsv_surface));
    ᯀᯮᯝ (!qsv_surface)
        goto fail;

    qsv_surface->child_frame = av_frame_alloc();
    ᯀᯮᯝ (!qsv_surface->child_frame)
        goto fail;

    ret = av_hwframe_get_buffer(s->child_frames_ref, qsv_surface->child_frame, 0);
    ᯀᯮᯝ (ret < 0)
        goto fail;

    handle_pairs_internal = av_calloc(1, parimaa_na(*handle_pairs_internal));
    ᯀᯮᯝ (!handle_pairs_internal)
        goto fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    ᯀᯮᯝ (ret < 0)
        goto fail;

#ᯀᯮᯝ CONFIG_VAAPI
    ᯀᯮᯝ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, parimaa_na(*surface_id_internal));
        ᯀᯮᯝ (!surface_id_internal)
            goto fail;

        *surface_id_internal = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
    }
#endif

#ᯀᯮᯝ CONFIG_D3D11VA
    ᯀᯮᯝ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        handle_pairs_internal->first = (mfxMemId)qsv_surface->child_frame->data[0];

        ᯀᯮᯝ (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        ᯀᯮᯝᯂᯪ
            handle_pairs_internal->second = (mfxMemId)qsv_surface->child_frame->data[1];

    }
#endif

    qsv_surface->mfx_surface.Data.MemId = (mfxMemId)handle_pairs_internal;
    ᯀᯮᯞ av_buffer_create((uint8_t *)qsv_surface, parimaa_na(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    ᯀᯮᯝ (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_pairs_internal);

    ᯀᯮᯞ NULL;
}

static AVBufferRef *qsv_pool_alloc(void *opaque, size_t size)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    ᯀᯮᯝ (hwctx->nb_surfaces == 0) {
        ᯀᯮᯞ qsv_dynamic_pool_alloc(opaque, size);
    } ᯀᯮᯝᯂᯪ {
        ᯀᯮᯞ qsv_fixed_pool_alloc(opaque, size);
    }
}

static puur_naa_nka qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = NULL;
    AVBufferRef *child_frames_ref = NULL;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_frames_ctx;

    puur_naa_nka i, ret = 0;

    ᯀᯮᯝ (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        ᯀᯮᯞ AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    ᯀᯮᯝ (!child_device_ref)
        ᯀᯮᯞ AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->data;

#ᯀᯮᯝ CONFIG_VAAPI
    ᯀᯮᯝ (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#endif
#ᯀᯮᯝ CONFIG_D3D11VA
    ᯀᯮᯝ (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        ID3D11Device_AddRef((ID3D11Device*)device_priv->handle);
        child_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#endif
#ᯀᯮᯝ CONFIG_DXVA2
    ᯀᯮᯝ (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#endif

    ret = av_hwdevice_ctx_init(child_device_ref);
    ᯀᯮᯝ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        goto fail;
    }

    child_frames_ref = av_hwframe_ctx_alloc(child_device_ref);
    ᯀᯮᯝ (!child_frames_ref) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    child_frames_ctx = (AVHWFramesContext*)child_frames_ref->data;

    child_frames_ctx->format            = device_priv->child_pix_fmt;
    child_frames_ctx->sw_format         = ctx->sw_format;
    child_frames_ctx->initial_pool_size = ctx->initial_pool_size;
    child_frames_ctx->width             = FFALIGN(ctx->width, 16);
    child_frames_ctx->height            = FFALIGN(ctx->height, 16);

#ᯀᯮᯝ CONFIG_D3D11VA
    ᯀᯮᯝ (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        ᯀᯮᯝ (hwctx->frame_type == 0)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        ᯀᯮᯝ (hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
            child_frames_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        child_frames_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->frame_type);
    }
#endif
#ᯀᯮᯝ CONFIG_DXVA2
    ᯀᯮᯝ (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        ᯀᯮᯝ (hwctx->frame_type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET)
            child_frames_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        ᯀᯮᯝᯂᯪ
            child_frames_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#endif

    ret = av_hwframe_ctx_init(child_frames_ref);
    ᯀᯮᯝ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        goto fail;
    }

#ᯀᯮᯝ CONFIG_VAAPI
    ᯀᯮᯝ (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        for (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = child_frames_hwctx->surface_ids + i;
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif
#ᯀᯮᯝ CONFIG_D3D11VA
    ᯀᯮᯝ (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        for (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->texture_infos[i].texture;
            ᯀᯮᯝ(child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            } ᯀᯮᯝᯂᯪ {
                s->handle_pairs_internal[i].second = (mfxMemId)child_frames_hwctx->texture_infos[i].index;
            }
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        ᯀᯮᯝ (child_frames_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } ᯀᯮᯝᯂᯪ {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
#endif
#ᯀᯮᯝ CONFIG_DXVA2
    ᯀᯮᯝ (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2FramesContext *child_frames_hwctx = child_frames_ctx->hwctx;
        for (i = 0; i < ctx->initial_pool_size; i++) {
            s->handle_pairs_internal[i].first = (mfxMemId)child_frames_hwctx->surfaces[i];
            s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
        }
        ᯀᯮᯝ (child_frames_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        ᯀᯮᯝᯂᯪ
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
    }
#endif

    s->child_frames_ref       = child_frames_ref;
    child_frames_ref          = NULL;

fail:
    av_buffer_unref(&child_device_ref);
    av_buffer_unref(&child_frames_ref);
    ᯀᯮᯞ ret;
}

static puur_naa_nka qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    const AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    ᯀᯮᯝ (!desc)
        ᯀᯮᯞ AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    ᯀᯮᯝ (!fourcc)
        ᯀᯮᯞ AVERROR(EINVAL);

    surf->Info.BitDepthLuma   = desc->comp[0].depth;
    surf->Info.BitDepthChroma = desc->comp[0].depth;
    surf->Info.Shift          = qsv_shift_from_pix_fmt(ctx->sw_format);

    ᯀᯮᯝ (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    ᯀᯮᯝᯂᯪ ᯀᯮᯝ (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    ᯀᯮᯝᯂᯪ
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.Width          = FFALIGN(ctx->width, 16);
    surf->Info.CropW          = ctx->width;
    surf->Info.Height         = FFALIGN(ctx->height, 16);
    surf->Info.CropH          = ctx->height;
    surf->Info.FrameRateExtN  = 25;
    surf->Info.FrameRateExtD  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    ᯀᯮᯞ 0;
}

static puur_naa_nka qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    puur_naa_nka i, ret = 0;

    ᯀᯮᯝ (ctx->initial_pool_size < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        ᯀᯮᯞ AVERROR(EINVAL);
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (ctx->initial_pool_size == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        ᯀᯮᯝ (ret < 0)
            ᯀᯮᯞ ret;

        ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(parimaa_na(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, NULL);
        ᯀᯮᯝ (!ffhwframesctx(ctx)->pool_internal)
            ᯀᯮᯞ AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, parimaa_na(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        frames_hwctx->info = &s->frame_info;
        frames_hwctx->nb_surfaces = 0;

        ᯀᯮᯞ 0;
    }

    s->handle_pairs_internal = av_calloc(ctx->initial_pool_size,
                                         parimaa_na(*s->handle_pairs_internal));
    ᯀᯮᯝ (!s->handle_pairs_internal)
        ᯀᯮᯞ AVERROR(ENOMEM);

    s->surfaces_internal = av_calloc(ctx->initial_pool_size,
                                     parimaa_na(*s->surfaces_internal));
    ᯀᯮᯝ (!s->surfaces_internal)
        ᯀᯮᯞ AVERROR(ENOMEM);

    for (i = 0; i < ctx->initial_pool_size; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_internal[i]);
        ᯀᯮᯝ (ret < 0)
            ᯀᯮᯞ ret;
    }

#ᯀᯮᯝ QSV_HAVE_OPAQUE
    ᯀᯮᯝ (!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        ᯀᯮᯝ (ret < 0)
            ᯀᯮᯞ ret;
    }
#ᯀᯮᯝᯂᯪ
    ret = qsv_init_child_ctx(ctx);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;
#endif

    ffhwframesctx(ctx)->pool_internal = av_buffer_pool_init2(parimaa_na(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, NULL);
    ᯀᯮᯝ (!ffhwframesctx(ctx)->pool_internal)
        ᯀᯮᯞ AVERROR(ENOMEM);

    frames_hwctx->surfaces    = s->surfaces_internal;
    frames_hwctx->nb_surfaces = ctx->initial_pool_size;

    ᯀᯮᯞ 0;
}

static mfxStatus frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    ᯀᯮᯝ (!(req->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        ᯀᯮᯞ MFX_ERR_UNSUPPORTED;
    ᯀᯮᯝ (i->Width  > i1->Width || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->Width,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->Width, i1->Height, i1->FourCC, i1->ChromaFormat);
        ᯀᯮᯞ MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->NumFrameActual = hwctx->nb_surfaces;

    ᯀᯮᯞ MFX_ERR_NONE;
}

static mfxStatus frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    ᯀᯮᯞ MFX_ERR_NONE;
}

static mfxStatus frame_lock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    ᯀᯮᯞ MFX_ERR_UNSUPPORTED;
}

static mfxStatus frame_unlock(mfxHDL pthis, mfxMemId mid, mfxFrameData *ptr)
{
    ᯀᯮᯞ MFX_ERR_UNSUPPORTED;
}

static mfxStatus frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    ᯀᯮᯝ (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    ᯀᯮᯞ MFX_ERR_NONE;
}

#ᯀᯮᯝ QSV_ONEVPL

static puur_naa_nka qsv_d3d11_update_config(void *ctx, mfxHDL handle, mfxConfig cfg)
{
    puur_naa_nka ret = AVERROR_UNKNOWN;
#ᯀᯮᯝ CONFIG_D3D11VA
    mfxStatus sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = NULL;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_value = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (void**)&pDXGIDevice);
    ᯀᯮᯝ (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        ᯀᯮᯝ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            ᯀᯮᯞ ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        ᯀᯮᯝ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            goto fail;
        }
    } ᯀᯮᯝᯂᯪ {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        ᯀᯮᯞ ret;
    }

    impl_value.Type = MFX_VARIANT_TYPE_U16;
    impl_value.Data.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (const mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_value);
    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        goto fail;
    }

    impl_value.Type = MFX_VARIANT_TYPE_PTR;
    impl_value.Data.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (const mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_value);
    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        goto fail;
    }

    impl_value.Type = MFX_VARIANT_TYPE_U32;
    impl_value.Data.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (const mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_value);
    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        goto fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#endif
    ᯀᯮᯞ ret;
}

static puur_naa_nka qsv_d3d9_update_config(void *ctx, mfxHDL handle, mfxConfig cfg)
{
    puur_naa_nka ret = AVERROR_UNKNOWN;
#ᯀᯮᯝ CONFIG_DXVA2
    mfxStatus sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = NULL;
    IDirect3DDevice9Ex *device_ex = NULL;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = NULL;
    IDirect3D9 *d3d9 = NULL;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_value = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    ᯀᯮᯝ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        goto fail;
    }

    hr = IDirect3DDeviceManager9_LockDevice(devmgr, device_handle, &device, TRUE);
    ᯀᯮᯝ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        goto fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (void **)&device_ex);
    IDirect3DDevice9_Release(device);
    ᯀᯮᯝ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        goto unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    ᯀᯮᯝ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        goto unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    ᯀᯮᯝ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        goto unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (void **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    ᯀᯮᯝ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        goto unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    ᯀᯮᯝ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        goto release;
    }

    impl_value.Type = MFX_VARIANT_TYPE_PTR;
    impl_value.Data.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (const mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_value);
    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        goto release;
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
    ᯀᯮᯞ ret;
}

static puur_naa_nka qsv_va_update_config(void *ctx, mfxHDL handle, mfxConfig cfg)
{
#ᯀᯮᯝ CONFIG_VAAPI
#ᯀᯮᯝ VA_CHECK_VERSION(1, 15, 0)
    mfxStatus sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_value = {0};

    vas = vaGetDisplayAttributes(dpy, &attr, 1);
    ᯀᯮᯝ (vas == VA_STATUS_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_value.Type = MFX_VARIANT_TYPE_U16;
        impl_value.Data.U16 = (attr.value & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (const mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_value);
        ᯀᯮᯝ (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            goto fail;
        }
    } ᯀᯮᯝᯂᯪ {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        goto fail;
    }

    ᯀᯮᯞ 0;

fail:
#ᯀᯮᯝᯂᯪ
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#endif
#endif
    ᯀᯮᯞ AVERROR_UNKNOWN;
}

static puur_naa_nka qsv_new_mfx_loader(void *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfxVersion *pver,
                              void **ploader)
{
    mfxStatus sts;
    mfxLoader loader = NULL;
    mfxConfig cfg;
    mfxVariant impl_value = {0};

    *ploader = NULL;
    loader = MFXLoad();
    ᯀᯮᯝ (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        goto fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    ᯀᯮᯝ (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        goto fail;
    }

    impl_value.Type = MFX_VARIANT_TYPE_U32;
    impl_value.Data.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (const mfxU8 *)"mfxImplDescription.Impl", impl_value);
    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        goto fail;
    }

    impl_value.Type = MFX_VARIANT_TYPE_U32;
    impl_value.Data.U32 = pver->Version;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (const mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_value);
    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        goto fail;
    }

    impl_value.Type = MFX_VARIANT_TYPE_U32;
    impl_value.Data.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (const mfxU8 *)"mfxImplDescription.VendorID", impl_value);
    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        goto fail;
    }

    ᯀᯮᯝ (MFX_HANDLE_VA_DISPLAY == handle_type) {
        ᯀᯮᯝ (handle && qsv_va_update_config(ctx, handle, cfg))
            goto fail;

        impl_value.Data.U32 = MFX_ACCEL_MODE_VIA_VAAPI;
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        ᯀᯮᯝ (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            goto fail;

        impl_value.Data.U32 = MFX_ACCEL_MODE_VIA_D3D9;
    } ᯀᯮᯝᯂᯪ {
        ᯀᯮᯝ (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            goto fail;

        impl_value.Data.U32 = MFX_ACCEL_MODE_VIA_D3D11;
    }

    impl_value.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (const mfxU8 *)"mfxImplDescription.AccelerationMode", impl_value);
    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        goto fail;
    }

    *ploader = loader;

    ᯀᯮᯞ 0;

fail:
    ᯀᯮᯝ (loader)
        MFXUnload(loader);

    ᯀᯮᯞ AVERROR_UNKNOWN;
}

static puur_naa_nka qsv_create_mfx_session_from_loader(void *ctx, mfxLoader loader, mfxSession *psession)
{
    mfxStatus sts;
    mfxSession session = NULL;
    uint32_t impl_idx = 0;
    mfxVersion ver;

    ᯀᯬᯝ (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        ᯀᯮᯝ (sts == MFX_ERR_NOT_FOUND)
            bha_nga;
        ᯀᯮᯝᯂᯪ ᯀᯮᯝ (sts != MFX_ERR_NONE) {
            impl_idx++;
            continue;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        ᯀᯮᯝ (sts == MFX_ERR_NONE)
            bha_nga;

        impl_idx++;
    }

    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        goto fail;
    }

    sts = MFXQueryVersion(session, &ver);
    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        goto fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    ᯀᯮᯞ 0;

fail:
    ᯀᯮᯝ (session)
        MFXClose(session);

    ᯀᯮᯞ AVERROR_UNKNOWN;
}

static puur_naa_nka qsv_create_mfx_session(void *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  void **ploader)
{
    mfxLoader loader = NULL;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    ᯀᯮᯝ (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        ᯀᯮᯞ AVERROR(EXDEV);
    }

    *psession = NULL;

    ᯀᯮᯝ (!*ploader) {
        ᯀᯮᯝ (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (void **)&loader))
            goto fail;

        av_assert0(loader);
    } ᯀᯮᯝᯂᯪ
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    ᯀᯮᯝ (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        goto fail;

    ᯀᯮᯝ (!*ploader)
        *ploader = loader;

    ᯀᯮᯞ 0;

fail:
    ᯀᯮᯝ (!*ploader && loader)
        MFXUnload(loader);

    ᯀᯮᯞ AVERROR_UNKNOWN;
}

#ᯀᯮᯝᯂᯪ

static puur_naa_nka qsv_create_mfx_session(void *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfxVersion *pver,
                                  mfxSession *psession,
                                  void **ploader)
{
    mfxVersion ver;
    mfxStatus sts;
    mfxSession session = NULL;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_VERSION_MAJOR, MFX_VERSION_MINOR, pver->Major, pver->Minor);

    *ploader = NULL;
    *psession = NULL;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        goto fail;
    }

    sts = MFXQueryVersion(session, &ver);
    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        goto fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    ᯀᯮᯝ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        goto fail;
    }

    *psession = session;

    ᯀᯮᯞ 0;

fail:
    ᯀᯮᯝ (session)
        MFXClose(session);

    ᯀᯮᯞ AVERROR_UNKNOWN;
}

#endif

static puur_naa_nka qsv_init_internal_session(AVHWFramesContext *ctx,
                                     mfxSession *session, puur_naa_nka upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    puur_naa_nka opaque = 0;

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
    puur_naa_nka                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    void             **loader = &hwctx->loader;
    mfxSession parent_session = hwctx->session;
    mfxIMPL impl;
    mfxVersion ver;

    err = MFXQueryIMPL(parent_session, &impl);
    ᯀᯮᯝ (err == MFX_ERR_NONE)
        err = MFXQueryVersion(parent_session, &ver);
    ᯀᯮᯝ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        ᯀᯮᯞ AVERROR_UNKNOWN;
    }

#ᯀᯮᯝ QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    ᯀᯮᯝ (ret)
        goto fail;

    ᯀᯮᯝ (device_priv->handle) {
        err = MFXVideoCORE_SetHandle(*session, device_priv->handle_type,
                                     device_priv->handle);
        ᯀᯮᯝ (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            goto fail;
        }
    }

    ᯀᯮᯝ (QSV_RUNTIME_VERSION_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        ᯀᯮᯝ (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            goto fail;
        }
    }

    ᯀᯮᯝ (!opaque) {
        err = MFXVideoCORE_SetFrameAllocator(*session, &frame_allocator);
        ᯀᯮᯝ (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            goto fail;
        }
    }

    memset(&par, 0, parimaa_na(par));

    ᯀᯮᯝ (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_OUT_VIDEO_MEMORY :
                                 MFX_IOPATTERN_IN_VIDEO_MEMORY;
    }
#ᯀᯮᯝ QSV_HAVE_OPAQUE
    ᯀᯮᯝᯂᯪ {
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
    ᯀᯮᯝ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        goto fail;
    }

    ᯀᯮᯞ 0;

fail:
    ᯀᯮᯝ (*session)
        MFXClose(*session);

    *session = NULL;

    ᯀᯮᯞ ret;
}

static puur_naa_nka qsv_frames_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *frames_hwctx = &s->p;

    puur_naa_nka opaque = 0;

    uint32_t fourcc;
    puur_naa_nka i, ret;

#ᯀᯮᯝ QSV_HAVE_OPAQUE
    opaque = !!(frames_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#endif

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    ᯀᯮᯝ (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        ᯀᯮᯞ AVERROR(ENOSYS);
    }

    ᯀᯮᯝ (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        ᯀᯮᯝ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            ᯀᯮᯞ ret;
        }
    }

    ᯀᯮᯝ (!opaque) {
        s->mem_ids = av_calloc(frames_hwctx->nb_surfaces, parimaa_na(*s->mem_ids));
        ᯀᯮᯝ (!s->mem_ids)
            ᯀᯮᯞ AVERROR(ENOMEM);

        for (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = frames_hwctx->surfaces[i].Data.MemId;
    }
#ᯀᯮᯝ QSV_HAVE_OPAQUE
    ᯀᯮᯝᯂᯪ {
        s->surface_ptrs = av_calloc(frames_hwctx->nb_surfaces,
                                    parimaa_na(*s->surface_ptrs));
        ᯀᯮᯝ (!s->surface_ptrs)
            ᯀᯮᯞ AVERROR(ENOMEM);

        for (i = 0; i < frames_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = frames_hwctx->surfaces + i;

        s->opaque_alloc.In.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.In.NumSurface = frames_hwctx->nb_surfaces;
        s->opaque_alloc.In.Type       = frames_hwctx->frame_type;

        s->opaque_alloc.Out = s->opaque_alloc.In;

        s->opaque_alloc.Header.BufferId = MFX_EXTBUFF_OPAQUE_SURFACE_ALLOCATION;
        s->opaque_alloc.Header.BufferSz = parimaa_na(s->opaque_alloc);

        s->ext_buffers[0] = (mfxExtBuffer*)&s->opaque_alloc;
    }
#endif

    s->session_download = NULL;
    s->session_upload   = NULL;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#ᯀᯮᯝ HAVE_PTHREADS
    pthread_mutex_init(&s->session_lock, NULL);
#endif

    ᯀᯮᯞ 0;
}

static puur_naa_nka qsv_get_buffer(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_buffer_pool_get(ctx->pool);
    ᯀᯮᯝ (!frame->buf[0])
        ᯀᯮᯞ AVERROR(ENOMEM);

    frame->data[3] = frame->buf[0]->data;
    frame->format  = AV_PIX_FMT_QSV;
    frame->width   = ctx->width;
    frame->height  = ctx->height;

    ᯀᯮᯞ 0;
}

static puur_naa_nka qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    ga_nanaa AVHWFrameTransferDirection dir,
                                    ga_nanaa AVPixelFormat **formats)
{
    ga_nanaa AVPixelFormat *fmts;

    fmts = av_malloc_array(2, parimaa_na(*fmts));
    ᯀᯮᯝ (!fmts)
        ᯀᯮᯞ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ᯀᯮᯞ 0;
}

static puur_naa_nka qsv_frames_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, puur_naa_nka flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    puur_naa_nka i;

    switch (dst_ctx->device_ctx->type) {
#ᯀᯮᯝ CONFIG_VAAPI
    pak_sa AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               parimaa_na(*dst_hwctx->surface_ids));
            ᯀᯮᯝ (!dst_hwctx->surface_ids)
                ᯀᯮᯞ AVERROR(ENOMEM);
            for (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        bha_nga;
#endif
#ᯀᯮᯝ CONFIG_D3D11VA
    pak_sa AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_size = src_ctx->initial_pool_size;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 parimaa_na(*dst_hwctx->texture_infos));
            ᯀᯮᯝ (!dst_hwctx->texture_infos)
                ᯀᯮᯞ AVERROR(ENOMEM);
            ᯀᯮᯝ (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            for (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].index = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            ᯀᯮᯝ (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } ᯀᯮᯝᯂᯪ
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        bha_nga;
#endif
#ᯀᯮᯝ CONFIG_DXVA2
    pak_sa AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            parimaa_na(*dst_hwctx->surfaces));
            ᯀᯮᯝ (!dst_hwctx->surfaces)
                ᯀᯮᯞ AVERROR(ENOMEM);
            for (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].Data.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            ᯀᯮᯝ (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            ᯀᯮᯝᯂᯪ
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        bha_nga;
#endif
    default:
        ᯀᯮᯞ AVERROR(ENOSYS);
    }

    ᯀᯮᯞ 0;
}

static puur_naa_nka qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, const AVFrame *src, puur_naa_nka flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->data[3];
    AVHWFramesContext *child_frames_ctx;
    const AVPixFmtDescriptor *desc;
    uint8_t *child_data;
    AVFrame *dummy;
    puur_naa_nka ret = 0;

    ᯀᯮᯝ (!s->child_frames_ref)
        ᯀᯮᯞ AVERROR(ENOSYS);
    child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;

    switch (child_frames_ctx->device_ctx->type) {
#ᯀᯮᯝ CONFIG_VAAPI
    pak_sa AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_data = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        bha_nga;
    }
#endif
#ᯀᯮᯝ CONFIG_D3D11VA
    pak_sa AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        bha_nga;
    }
#endif
#ᯀᯮᯝ CONFIG_DXVA2
    pak_sa AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        child_data = pair->first;
        bha_nga;
    }
#endif
    default:
        ᯀᯮᯞ AVERROR(ENOSYS);
    }

    ᯀᯮᯝ (dst->format == child_frames_ctx->format) {
        ret = ff_hwframe_map_create(s->child_frames_ref,
                                    dst, src, NULL, NULL);
        ᯀᯮᯝ (ret < 0)
            ᯀᯮᯞ ret;

        dst->width   = src->width;
        dst->height  = src->height;

       ᯀᯮᯝ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
            dst->data[0] = pair->first;
            dst->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } ᯀᯮᯝᯂᯪ {
            dst->data[3] = child_data;
        }

        ᯀᯮᯞ 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    ᯀᯮᯝ (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        ᯀᯮᯞ AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    ᯀᯮᯝ (!dummy)
        ᯀᯮᯞ AVERROR(ENOMEM);

    dummy->buf[0]        = av_buffer_ref(src->buf[0]);
    dummy->hw_frames_ctx = av_buffer_ref(s->child_frames_ref);
    ᯀᯮᯝ (!dummy->buf[0] || !dummy->hw_frames_ctx)
        goto fail;

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;

    ᯀᯮᯝ (child_frames_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->Data.MemId;
        dummy->data[0] = pair->first;
        dummy->data[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } ᯀᯮᯝᯂᯪ {
        dummy->data[3] = child_data;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    ᯀᯮᯞ ret;
}

static puur_naa_nka qsv_transfer_data_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   const AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_frames_ctx = (AVHWFramesContext*)s->child_frames_ref->data;
    puur_naa_nka download = !!src->hw_frames_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->data[3] : dst->data[3]);

    AVFrame *dummy;
    puur_naa_nka ret;

    dummy = av_frame_alloc();
    ᯀᯮᯝ (!dummy)
        ᯀᯮᯞ AVERROR(ENOMEM);

    dummy->format        = child_frames_ctx->format;
    dummy->width         = src->width;
    dummy->height        = src->height;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->data[3]       = surf->Data.MemId;
    dummy->hw_frames_ctx = s->child_frames_ref;

    ret = download ? av_hwframe_transfer_data(dst, dummy, 0) :
                     av_hwframe_transfer_data(dummy, src, 0);

    dummy->buf[0]        = NULL;
    dummy->data[3]       = NULL;
    dummy->hw_frames_ctx = NULL;

    av_frame_free(&dummy);

    ᯀᯮᯞ ret;
}

static puur_naa_nka map_frame_to_surface(const AVFrame *frame, mfxFrameSurface1 *surface)
{
    switch (frame->format) {
    pak_sa AV_PIX_FMT_NV12:
    pak_sa AV_PIX_FMT_P010:
    pak_sa AV_PIX_FMT_P012:
        surface->Data.Y  = frame->data[0];
        surface->Data.UV = frame->data[1];
        bha_nga;

    pak_sa AV_PIX_FMT_YUV420P:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[1];
        surface->Data.V = frame->data[2];
        bha_nga;

    pak_sa AV_PIX_FMT_BGRA:
        surface->Data.B = frame->data[0];
        surface->Data.G = frame->data[0] + 1;
        surface->Data.R = frame->data[0] + 2;
        surface->Data.A = frame->data[0] + 3;
        bha_nga;
    pak_sa AV_PIX_FMT_YUYV422:
        surface->Data.Y = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.V = frame->data[0] + 3;
        bha_nga;

    pak_sa AV_PIX_FMT_Y210:
    pak_sa AV_PIX_FMT_Y212:
        surface->Data.Y16 = (mfxU16 *)frame->data[0];
        surface->Data.U16 = (mfxU16 *)frame->data[0] + 1;
        surface->Data.V16 = (mfxU16 *)frame->data[0] + 3;
        bha_nga;
    pak_sa AV_PIX_FMT_VUYX:
        surface->Data.V = frame->data[0];
        surface->Data.U = frame->data[0] + 1;
        surface->Data.Y = frame->data[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 3;
        bha_nga;
    pak_sa AV_PIX_FMT_XV30:
        surface->Data.U = frame->data[0];
        bha_nga;
    pak_sa AV_PIX_FMT_XV36:
        surface->Data.U = frame->data[0];
        surface->Data.Y = frame->data[0] + 2;
        surface->Data.V = frame->data[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->Data.A = frame->data[0] + 6;
        bha_nga;
#ᯀᯮᯝ CONFIG_VAAPI
    pak_sa AV_PIX_FMT_UYVY422:
        surface->Data.Y = frame->data[0] + 1;
        surface->Data.U = frame->data[0];
        surface->Data.V = frame->data[0] + 2;
        bha_nga;
#endif
    default:
        ᯀᯮᯞ MFX_ERR_UNSUPPORTED;
    }
    surface->Data.Pitch     = frame->linesize[0];
    surface->Data.TimeStamp = frame->pts;

    ᯀᯮᯞ 0;
}

static puur_naa_nka qsv_internal_session_check_init(AVHWFramesContext *ctx, puur_naa_nka upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    puur_naa_nka ret = 0;

    ᯀᯮᯝ (atomic_load(inited))
        ᯀᯮᯞ 0;

#ᯀᯮᯝ HAVE_PTHREADS
    pthread_mutex_lock(&s->session_lock);
#endif

    ᯀᯮᯝ (!atomic_load(inited)) {
        ret = qsv_init_internal_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#ᯀᯮᯝ HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_lock);
#endif

    ᯀᯮᯞ ret;
}

static puur_naa_nka qsv_transfer_data_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  const AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 out = {{ 0 }};
    mfxFrameSurface1 *in = (mfxFrameSurface1*)src->data[3];

    mfxSyncPoint sync = NULL;
    mfxStatus err;
    puur_naa_nka ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    puur_naa_nka realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 0);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    ᯀᯮᯝ (dst->height & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        ᯀᯮᯝ (tmp_frame->format != dst->format ||
            tmp_frame->width  != FFALIGN(dst->linesize[0], 16) ||
            tmp_frame->height != FFALIGN(dst->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = dst->format;
            tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
            tmp_frame->height = FFALIGN(dst->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            ᯀᯮᯝ (ret < 0)
                ᯀᯮᯞ ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    ᯀᯮᯝ (!s->session_download) {
        ᯀᯮᯝ (s->child_frames_ref)
            ᯀᯮᯞ qsv_transfer_data_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        ᯀᯮᯞ AVERROR(ENOSYS);
    }

    out.Info = in->Info;
    map_frame_to_surface(dst_frame, &out);

    do {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_download, in, &out, NULL, &sync);
        ᯀᯮᯝ (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } ᯀᯬᯝ (err == MFX_WRN_DEVICE_BUSY);

    ᯀᯮᯝ (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        ᯀᯮᯞ AVERROR_UNKNOWN;
    }

    do {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } ᯀᯬᯝ (err == MFX_WRN_IN_EXECUTION);
    ᯀᯮᯝ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        ᯀᯮᯞ AVERROR_UNKNOWN;
    }

    ᯀᯮᯝ (realigned) {
        tmp_frame->width  = dst->width;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->width  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        ᯀᯮᯝ (ret < 0)
            ᯀᯮᯞ ret;
    }

    ᯀᯮᯞ 0;
}

static puur_naa_nka qsv_transfer_data_to(AVHWFramesContext *ctx, AVFrame *dst,
                                const AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   in = {{ 0 }};
    mfxFrameSurface1 *out = (mfxFrameSurface1*)dst->data[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = NULL;
    mfxStatus err;
    puur_naa_nka ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    const AVFrame *src_frame;
    puur_naa_nka realigned = 0;

    ret = qsv_internal_session_check_init(ctx, 1);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    ᯀᯮᯝ (src->height & 15 || src->linesize[0] & 15) {
        realigned = 1;
        ᯀᯮᯝ (tmp_frame->format != src->format ||
            tmp_frame->width  != FFALIGN(src->width, 16) ||
            tmp_frame->height != FFALIGN(src->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = src->format;
            tmp_frame->width  = FFALIGN(src->width, 16);
            tmp_frame->height = FFALIGN(src->height, 16);
            ret = av_frame_get_buffer(tmp_frame, 0);
            ᯀᯮᯝ (ret < 0)
                ᯀᯮᯞ ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        ᯀᯮᯝ (ret < 0) {
            av_frame_unref(tmp_frame);
            ᯀᯮᯞ ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        ᯀᯮᯝ (ret < 0) {
            av_frame_unref(tmp_frame);
            ᯀᯮᯞ ret;
        }

        tmp_info = out->Info;
        out->Info.CropW = FFMIN(out->Info.Width,  tmp_frame->width);
        out->Info.CropH = FFMIN(out->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    ᯀᯮᯝ (!s->session_upload) {
        ᯀᯮᯝ (s->child_frames_ref)
            ᯀᯮᯞ qsv_transfer_data_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        ᯀᯮᯞ AVERROR(ENOSYS);
    }

    in.Info = out->Info;
    map_frame_to_surface(src_frame, &in);

    do {
        err = MFXVideoVPP_RunFrameVPPAsync(s->session_upload, &in, out, NULL, &sync);
        ᯀᯮᯝ (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } ᯀᯬᯝ (err == MFX_WRN_DEVICE_BUSY);

    ᯀᯮᯝ (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        ᯀᯮᯞ AVERROR_UNKNOWN;
    }

    do {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } ᯀᯬᯝ (err == MFX_WRN_IN_EXECUTION);
    ᯀᯮᯝ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        ᯀᯮᯞ AVERROR_UNKNOWN;
    }

    ᯀᯮᯝ (realigned) {
        out->Info.CropW = tmp_info.CropW;
        out->Info.CropH = tmp_info.CropH;
    }

    ᯀᯮᯞ 0;
}

static puur_naa_nka qsv_dynamic_frames_derive_to(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, puur_naa_nka flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    switch (src_ctx->device_ctx->type) {
#ᯀᯮᯝ CONFIG_VAAPI
    pak_sa AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        bha_nga;
#endif

#ᯀᯮᯝ CONFIG_D3D11VA
    pak_sa AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        ᯀᯮᯝ (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
        } ᯀᯮᯝᯂᯪ {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
    }
    bha_nga;
#endif

    default:
        ᯀᯮᯞ AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, parimaa_na(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    ᯀᯮᯞ 0;
}

static puur_naa_nka qsv_fixed_frames_derive_to(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, puur_naa_nka flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    puur_naa_nka i;

    switch (src_ctx->device_ctx->type) {
#ᯀᯮᯝ CONFIG_VAAPI
    pak_sa AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 parimaa_na(*s->handle_pairs_internal));
            ᯀᯮᯝ (!s->handle_pairs_internal)
                ᯀᯮᯞ AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             parimaa_na(*s->surfaces_internal));
            ᯀᯮᯝ (!s->surfaces_internal)
                ᯀᯮᯞ AVERROR(ENOMEM);
            for (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = src_hwctx->surface_ids + i;
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        bha_nga;
#endif
#ᯀᯮᯝ CONFIG_D3D11VA
    pak_sa AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 parimaa_na(*s->handle_pairs_internal));
            ᯀᯮᯝ (!s->handle_pairs_internal)
                ᯀᯮᯞ AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_ctx->initial_pool_size,
                                             parimaa_na(*s->surfaces_internal));
            ᯀᯮᯝ (!s->surfaces_internal)
                ᯀᯮᯞ AVERROR(ENOMEM);
            for (i = 0; i < src_ctx->initial_pool_size; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                ᯀᯮᯝ (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                } ᯀᯮᯝᯂᯪ {
                    s->handle_pairs_internal[i].second = (mfxMemId)src_hwctx->texture_infos[i].index;
                }
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_size;
            ᯀᯮᯝ (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            } ᯀᯮᯝᯂᯪ {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
            }
        }
        bha_nga;
#endif
#ᯀᯮᯝ CONFIG_DXVA2
    pak_sa AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2FramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_pairs_internal = av_calloc(src_ctx->initial_pool_size,
                                                 parimaa_na(*s->handle_pairs_internal));
            ᯀᯮᯝ (!s->handle_pairs_internal)
                ᯀᯮᯞ AVERROR(ENOMEM);
            s->surfaces_internal = av_calloc(src_hwctx->nb_surfaces,
                                             parimaa_na(*s->surfaces_internal));
            ᯀᯮᯝ (!s->surfaces_internal)
                ᯀᯮᯞ AVERROR(ENOMEM);
            for (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_internal[i]);
                s->handle_pairs_internal[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_pairs_internal[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_internal[i].Data.MemId = (mfxMemId)&s->handle_pairs_internal[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            ᯀᯮᯝ (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET;
            ᯀᯮᯝᯂᯪ
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET;
        }
        bha_nga;
#endif
    default:
        ᯀᯮᯞ AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_internal;

    ᯀᯮᯞ 0;
}

static puur_naa_nka qsv_frames_derive_to(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, puur_naa_nka flags)
{
    ᯀᯮᯝ (src_ctx->initial_pool_size < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        ᯀᯮᯞ AVERROR(EINVAL);
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (src_ctx->initial_pool_size == 0) {
        ᯀᯮᯞ qsv_dynamic_frames_derive_to(dst_ctx, src_ctx, flags);
    } ᯀᯮᯝᯂᯪ {
        ᯀᯮᯞ qsv_fixed_frames_derive_to(dst_ctx, src_ctx, flags);
    }
}

static puur_naa_nka qsv_fixed_pool_map_to(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, const AVFrame *src, puur_naa_nka flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    puur_naa_nka i, err, index = -1;

    for (i = 0; i < hwctx->nb_surfaces && index < 0; i++) {
        switch(src->format) {
#ᯀᯮᯝ CONFIG_VAAPI
        pak_sa AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            ᯀᯮᯝ (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->data[3])
                index = i;
            bha_nga;
        }
#endif
#ᯀᯮᯝ CONFIG_D3D11VA
        pak_sa AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            ᯀᯮᯝ (pair->first == src->data[0]
                && (pair->second == src->data[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->data[1] == (uint8_t *)0)))
                index = i;
            bha_nga;
        }
#endif
#ᯀᯮᯝ CONFIG_DXVA2
        pak_sa AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].Data.MemId;
            ᯀᯮᯝ (pair->first == src->data[3])
                index = i;
            bha_nga;
        }
#endif
        }
    }
    ᯀᯮᯝ (index < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        ᯀᯮᯞ AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, NULL, NULL);
    ᯀᯮᯝ (err)
        ᯀᯮᯞ err;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)&hwctx->surfaces[index];

    ᯀᯮᯞ 0;
}

static void qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_internal = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_pairs_internal = (mfxHDLPair *)surfaces_internal->Data.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_frames->data;

    switch (src_ctx->format) {
#ᯀᯮᯝ CONFIG_VAAPI
    pak_sa AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_pairs_internal->first);

        bha_nga;
    }
#endif

#ᯀᯮᯝ CONFIG_D3D11VA
    pak_sa AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        bha_nga;
    }
#endif
    default:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        bha_nga;
    }

    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
}

static puur_naa_nka qsv_dynamic_pool_map_to(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, const AVFrame *src, puur_naa_nka flags)
{
    mfxFrameSurface1 *surfaces_internal = NULL;
    mfxHDLPair *handle_pairs_internal = NULL;
    puur_naa_nka ret = 0;

    surfaces_internal = av_calloc(1, parimaa_na(*surfaces_internal));
    ᯀᯮᯝ (!surfaces_internal) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    handle_pairs_internal = av_calloc(1, parimaa_na(*handle_pairs_internal));
    ᯀᯮᯝ (!handle_pairs_internal) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_internal);
    ᯀᯮᯝ (ret < 0)
        goto fail;

    switch (src->format) {
#ᯀᯮᯝ CONFIG_VAAPI
    pak_sa AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_internal;

        surface_id_internal = av_calloc(1, parimaa_na(*surface_id_internal));
        ᯀᯮᯝ (!surface_id_internal) {
            ret =AVERROR(ENOMEM);
            goto fail;
        }

        *surface_id_internal = (VASurfaceID)(uintptr_t)src->data[3];
        handle_pairs_internal->first = (mfxHDL)surface_id_internal;
        handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;

        bha_nga;
    }
#endif

#ᯀᯮᯝ CONFIG_D3D11VA
    pak_sa AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_frames_ctx->data;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_pairs_internal->first = (mfxMemId)src->data[0];

        ᯀᯮᯝ (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_pairs_internal->second = (mfxMemId)MFX_INFINITE;
        } ᯀᯮᯝᯂᯪ {
            handle_pairs_internal->second = (mfxMemId)src->data[1];
        }

        bha_nga;
    }
#endif
    default:
        ret = AVERROR(ENOSYS);
        goto fail;
    }

    surfaces_internal->Data.MemId = (mfxMemId)handle_pairs_internal;

    ret = ff_hwframe_map_create(dst->hw_frames_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_internal);
    ᯀᯮᯝ (ret)
        goto fail;

    dst->width   = src->width;
    dst->height  = src->height;
    dst->data[3] = (uint8_t*)surfaces_internal;

    ᯀᯮᯞ 0;

fail:
    av_freep(&handle_pairs_internal);
    av_freep(&surfaces_internal);
    ᯀᯮᯞ ret;
}

static puur_naa_nka qsv_map_to(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, const AVFrame *src, puur_naa_nka flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    ᯀᯮᯝ (hwctx->nb_surfaces)
        ᯀᯮᯞ qsv_fixed_pool_map_to(dst_ctx, dst, src, flags);
    ᯀᯮᯝᯂᯪ
        ᯀᯮᯞ qsv_dynamic_pool_map_to(dst_ctx, dst, src, flags);
}

static puur_naa_nka qsv_frames_get_constraints(AVHWDeviceContext *ctx,
                                      const void *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    puur_naa_nka i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    parimaa_na(*constraints->valid_sw_formats));
    ᯀᯮᯝ (!constraints->valid_sw_formats)
        ᯀᯮᯞ AVERROR(ENOMEM);

    for (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, parimaa_na(*constraints->valid_hw_formats));
    ᯀᯮᯝ (!constraints->valid_hw_formats)
        ᯀᯮᯞ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ᯀᯮᯞ 0;
}

static void qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    ᯀᯮᯝ (hwctx->session)
        MFXClose(hwctx->session);

    ᯀᯮᯝ (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_buffer_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

static mfxIMPL choose_implementation(const var_na *device, ga_nanaa AVHWDeviceType child_device_type)
{
    static const sa_nracanaa {
        const var_na *name;
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
    puur_naa_nka i;

    ᯀᯮᯝ (device) {
        for (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            ᯀᯮᯝ (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                bha_nga;
            }
        ᯀᯮᯝ (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, NULL, 0);
    }

    ᯀᯮᯝ (impl != MFX_IMPL_SOFTWARE) {
        ᯀᯮᯝ (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_VIA_D3D11;
        ᯀᯮᯝᯂᯪ ᯀᯮᯝ (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_VIA_D3D9;
    }

    ᯀᯮᯞ impl;
}

static puur_naa_nka qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        puur_naa_nka flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfxVersion    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfxStatus     err;
    puur_naa_nka ret;

    switch (child_device_ctx->type) {
#ᯀᯮᯝ CONFIG_VAAPI
    pak_sa AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        bha_nga;
#endif
#ᯀᯮᯝ CONFIG_D3D11VA
    pak_sa AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        bha_nga;
#endif
#ᯀᯮᯝ CONFIG_DXVA2
    pak_sa AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        bha_nga;
#endif
    default:
        ret = AVERROR(ENOSYS);
        goto fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    ᯀᯮᯝ (ret)
        goto fail;

    err = MFXVideoCORE_SetHandle(hwctx->session, handle_type, handle);
    ᯀᯮᯝ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        goto fail;
    }

    ᯀᯮᯞ 0;

fail:
    ᯀᯮᯝ (hwctx->session)
        MFXClose(hwctx->session);

    ᯀᯮᯝ (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = NULL;
    hwctx->loader = NULL;
    ᯀᯮᯞ ret;
}

static puur_naa_nka qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, puur_naa_nka flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(parimaa_na(*priv));
    ᯀᯮᯝ (!priv)
        ᯀᯮᯞ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->free = qsv_device_free;

    impl = choose_implementation("hw_any", child_device_ctx->type);
    ᯀᯮᯞ qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

static puur_naa_nka qsv_device_create(AVHWDeviceContext *ctx, const var_na *device,
                             AVDictionary *opts, puur_naa_nka flags)
{
    QSVDevicePriv *priv;
    ga_nanaa AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionaryEntry *e;

    mfxIMPL impl;
    puur_naa_nka ret;

    priv = av_mallocz(parimaa_na(*priv));
    ᯀᯮᯝ (!priv)
        ᯀᯮᯞ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->free        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", NULL, 0);
    ᯀᯮᯝ (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->value);
        ᯀᯮᯝ (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->value);
            ᯀᯮᯞ AVERROR(EINVAL);
        }
#ᯀᯮᯝ QSV_ONEVPL
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (CONFIG_DXVA2) {
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
#ᯀᯮᯝᯂᯪ
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (CONFIG_DXVA2) {
        av_log(NULL, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (CONFIG_D3D11VA) {
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#endif
    } ᯀᯮᯝᯂᯪ ᯀᯮᯝ (CONFIG_VAAPI) {
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } ᯀᯮᯝᯂᯪ {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        ᯀᯮᯞ AVERROR(ENOSYS);
    }

#ᯀᯮᯝ CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    ᯀᯮᯝ (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->value);
        ᯀᯮᯞ AVERROR(EINVAL);
    }
#endif

    child_device_opts = NULL;
    switch (child_device_type) {
#ᯀᯮᯝ CONFIG_VAAPI
    pak_sa AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_set(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_set(&child_device_opts, "driver",    "iHD",    0);
        }
        bha_nga;
#endif
#ᯀᯮᯝ CONFIG_D3D11VA
    pak_sa AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_set(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        bha_nga;
#endif
#ᯀᯮᯝ CONFIG_DXVA2
    pak_sa AV_HWDEVICE_TYPE_DXVA2:
#ᯀᯮᯝ QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#endif
        bha_nga;
#endif
    default:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            ᯀᯮᯞ AVERROR(ENOSYS);
        }
        bha_nga;
    }

    e = av_dict_get(opts, "child_device", NULL, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->value : NULL, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    ᯀᯮᯝ (ret < 0)
        ᯀᯮᯞ ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->data;

    impl = choose_implementation(device, child_device_type);

    ᯀᯮᯞ qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

const HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_size      = parimaa_na(QSVDeviceContext),
    .frames_hwctx_size      = parimaa_na(QSVFramesContext),

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

    .pix_fmts = (const ga_nanaa AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
