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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdatomic.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ <mfxvideo.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ HAVE_PTHREADS
#ਅਨ੍ਤਰ੍ਭਾਵ <pthread.h>
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COBJMACROS
#ਜੇ CONFIG_VAAPI
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_vaapi.h"
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_d3d11va.h"
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
#ਅਨ੍ਤਰ੍ਭਾਵ <initguid.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_dxva2.h"
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hwcontext_qsv.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixdesc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "time.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "imgutils.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ QSV_ਸੰਸਕਰਣ_ATLEAST(MAJOR, MINOR)   \
    (MFX_ਸੰਸਕਰਣ_MAJOR > (MAJOR) ||         \
     MFX_ਸੰਸਕਰਣ_MAJOR == (MAJOR) && MFX_ਸੰਸਕਰਣ_MINOR >= (MINOR))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ QSV_RUNTIME_ਸੰਸਕਰਣ_ATLEAST(MFX_ਸੰਸਕਰਣ, MAJOR, MINOR)          \
    ((MFX_ਸੰਸਕਰਣ.Major > (MAJOR)) ||                                   \
     (MFX_ਸੰਸਕਰਣ.Major == (MAJOR) && MFX_ਸੰਸਕਰਣ.Minor >= (MINOR)))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MFX_IMPL_ਰਾਹੀਂ_ਨਕਾਬ(impl) (0x0f00 & (impl))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ QSV_ONEVPL       QSV_ਸੰਸਕਰਣ_ATLEAST(2, 0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ QSV_HAVE_OPAQUE  !QSV_ONEVPL

#ਜੇ QSV_ONEVPL
#ਅਨ੍ਤਰ੍ਭਾਵ <mfxdispatcher.h>
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MFXUnload(a) ਕਰੋ { } ਜਦੋਂ(0)
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ QSVDevicePriv {
    AVBufferRef *ਬੱਚਾ_device_ctx;
} QSVDevicePriv;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfx_ਸੰਸਕਰਣ          ver;
    mfxIMPL             impl;

    ਗਿਣਤੀ AVHWDeviceType ਬੱਚਾ_device_type;
    ਗਿਣਤੀ AVPixelFormat  ਬੱਚਾ_pix_fmt;
} QSVDeviceContext;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#ਜੇ HAVE_PTHREADS
    pthread_mutex_t session_ਤਾਲਾ;
#ਜੇ_ਅੰਤ

    AVBufferRef *ਬੱਚਾ_ਚੌਖਟੇ_ref;
    mfx_ਚੌਖਟਾ_Surface1 *surfaces_ਅੰਦਰੂਨੀ;
    mfxHDLPair *handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ;
    ਪੂਰਨ             nb_surfaces_ਵਰਤਿਆ;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#ਜੇ QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfx_ਚੌਖਟਾ_Surface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfx_Ext_ਬਫਰ *ext_buffers[1];
#ਜੇ_ਅੰਤ
    AVFrame realigned_upload_ਚੌਖਟਾ;
    AVFrame realigned_download_ਚੌਖਟਾ;

    mfx_ਚੌਖਟਾ_Info ਚੌਖਟਾ_info;
} QSVFramesContext;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ QSVSurface {
    mfx_ਚੌਖਟਾ_Surface1 mfx_surface;
    AVFrame *ਬੱਚਾ_ਚੌਖਟਾ;
} QSVSurface;

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    ਗਿਣਤੀ AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_ਖਿਸਕਾਓ;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#ਜੇ CONFIG_VAAPI
    { AV_PIX_FMT_UYVY422,
                       MFX_FOURCC_UYVY, 0 },
#ਜੇ_ਅੰਤ
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
#ਜੇ QSV_ਸੰਸਕਰਣ_ATLEAST(1, 31)
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
#ਜੇ_ਅੰਤ
};

ਬਾਹਰੀ ਪੂਰਨ ff_qsv_get_surface_ਅਧਾਰ_handle(mfx_ਚੌਖਟਾ_Surface1 *surf,
                                          ਗਿਣਤੀ AVHWDeviceType ਅਧਾਰ_dev_type,
                                          ਖਾਲੀ **ਅਧਾਰ_handle);

ਸਥਿਰ ਪੂਰਨ qsv_init_surface(AVHWFramesContext *ctx, mfx_ਚੌਖਟਾ_Surface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
ਪੂਰਨ ff_qsv_get_surface_ਅਧਾਰ_handle(mfx_ਚੌਖਟਾ_Surface1 *surf,
                                   ਗਿਣਤੀ AVHWDeviceType ਅਧਾਰ_dev_type,
                                   ਖਾਲੀ **ਅਧਾਰ_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->ਅੰਕੜੇ_2.MemId;
    ਚੋਣ (ਅਧਾਰ_dev_type) {
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_HWDEVICE_TYPE_VAAPI:
        ਅਧਾਰ_handle[0] = handle_pair->ਪਹਿਲਾ;
        ਵਾਪਸ 0;
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
    ਹਾਲਤ AV_HWDEVICE_TYPE_D3D11VA:
        ਅਧਾਰ_handle[0] = handle_pair->ਪਹਿਲਾ;
        ਅਧਾਰ_handle[1] = handle_pair->ਦੂਜਾ;
        ਵਾਪਸ 0;
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
    ਹਾਲਤ AV_HWDEVICE_TYPE_DXVA2:
        ਅਧਾਰ_handle[0] = handle_pair->ਪਹਿਲਾ;
        ਵਾਪਸ 0;
#ਜੇ_ਅੰਤ
    }
    ਵਾਪਸ AVERROR(EINVAL);
}

ਸਥਿਰ uint32_t qsv_fourcc_from_pix_fmt(ਗਿਣਤੀ AVPixelFormat pix_fmt)
{
    ਪੂਰਨ i;
    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        ਜੇ (supported_pixel_formats[i].pix_fmt == pix_fmt)
            ਵਾਪਸ supported_pixel_formats[i].fourcc;
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ uint16_t qsv_ਖਿਸਕਾਓ_from_pix_fmt(ਗਿਣਤੀ AVPixelFormat pix_fmt)
{
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        ਜੇ (supported_pixel_formats[i].pix_fmt == pix_fmt)
            ਵਾਪਸ supported_pixel_formats[i].mfx_ਖਿਸਕਾਓ;
    }

    ਵਾਪਸ 0;
}

#ਜੇ CONFIG_D3D11VA
ਸਥਿਰ uint32_t qsv_get_d3d11va_bind_flags(ਪੂਰਨ mem_type)
{
    uint32_t bind_flags = 0;

    ਜੇ ((mem_type & MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_ENCODER_ਨਿਸ਼ਾਨਾ) && (mem_type & MFX_MEMTYPE_ਅੰਦਰੂਨੀ_ਚੌਖਟਾ))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    ਨਹੀਂਤਾਂ
        bind_flags = D3D11_BIND_DECODER;

    ਜੇ ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_PROCESSOR_ਨਿਸ਼ਾਨਾ & mem_type))
        bind_flags = D3_D11_BIND_RENDER_ਨਿਸ਼ਾਨਾ;

    ਵਾਪਸ bind_flags;
}
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ qsv_fill_border(AVFrame *dst, ਅਚਲ AVFrame *src)
{
    ਅਚਲ AVPixFmtDescriptor *desc;
    ਪੂਰਨ i, planes_nb = 0;
    ਜੇ (dst->format != src->format)
        ਵਾਪਸ AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    ਲਈ (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    ਲਈ (i = 0; i < planes_nb; i++) {
        ਪੂਰਨ sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->ਚੌੜਾਈ,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->ਚੌੜਾਈ,
                                                 i);
        ਅਚਲ AVComponentDescriptor comp = desc->comp[i];
        ਜੇ (swidth < 0 || dwidth < 0) {
            av_log(ਨਿਰਾ, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            ਵਾਪਸ AVERROR(EINVAL);
        }
        sheight = src->ਉਚਾਈ;
        dheight = dst->ਉਚਾਈ;
        ਜੇ (i) {
            sheight = AV_CEIL_RSHIFT(src->ਉਚਾਈ, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->ਉਚਾਈ, desc->log2_chroma_h);
        }
        //fill right padding
        ਲਈ (y = 0; y < sheight; y++) {
            ਖਾਲੀ *ਸਤਰ_ptr = dst->ਅੰਕੜੇ[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(ਸਤਰ_ptr,
                           comp.ਡੂੰਘਾਈ > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        ਲਈ (y = sheight; y < dheight; y++) {
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst->ਅੰਕੜੇ[i]+y*dst->linesize[i],
                   dst->ਅੰਕੜੇ[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    ਪੂਰਨ   hw_handle_supported = 0;
    mfxHandleType handle_type;
    ਗਿਣਤੀ AVHWDeviceType device_type;
    ਗਿਣਤੀ AVPixelFormat  pix_fmt;
    mfx_ਸਥਿਤੀ err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    ਜੇ (err == MFX_ERR_NONE)
        err = MFXQuery_ਸੰਸਕਰਣ(hwctx->session, &s->ver);
    ਜੇ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਜੇ (MFX_IMPL_ਰਾਹੀਂ_VAAPI == MFX_IMPL_ਰਾਹੀਂ_ਨਕਾਬ(s->impl)) {
#ਜੇ CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#ਜੇ_ਅੰਤ
    } ਨਹੀਂਤਾਂ ਜੇ (MFX_IMPL_ਰਾਹੀਂ_D3_D11 == MFX_IMPL_ਰਾਹੀਂ_ਨਕਾਬ(s->impl)) {
#ਜੇ CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#ਜੇ_ਅੰਤ
    } ਨਹੀਂਤਾਂ ਜੇ (MFX_IMPL_ਰਾਹੀਂ_D3_D9 == MFX_IMPL_ਰਾਹੀਂ_ਨਕਾਬ(s->impl)) {
#ਜੇ CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#ਜੇ_ਅੰਤ
    }

    ਜੇ (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        ਜੇ (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->ਬੱਚਾ_device_type = device_type;
            s->ਬੱਚਾ_pix_fmt     = pix_fmt;
        }
    }
    ਜੇ (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ qsv_ਚੌਖਟੇ_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    ਜੇ (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = ਨਿਰਾ;
    s->session_download_init = 0;

    ਜੇ (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = ਨਿਰਾ;
    s->session_upload_init = 0;

#ਜੇ HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_ਤਾਲਾ);
#ਜੇ_ਅੰਤ

    av_freep(&s->mem_ids);
#ਜੇ QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#ਜੇ_ਅੰਤ
    av_freep(&s->surfaces_ਅੰਦਰੂਨੀ);
    av_freep(&s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ);
    av_ਚੌਖਟਾ_unref(&s->realigned_upload_ਚੌਖਟਾ);
    av_ਚੌਖਟਾ_unref(&s->realigned_download_ਚੌਖਟਾ);
    av_ਬਫਰ_unref(&s->ਬੱਚਾ_ਚੌਖਟੇ_ref);
}

ਸਥਿਰ ਖਾਲੀ qsv_pool_release_dummy(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
}

ਸਥਿਰ ਖਾਲੀ qsv_pool_release(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)ਅੰਕੜੇ;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.ਅੰਕੜੇ_2.MemId;
    AVHWFramesContext *ਬੱਚਾ_ਚੌਖਟੇ_ctx;

    ਜੇ (!s->ਬੱਚਾ_ਚੌਖਟੇ_ref)
        ਵਾਪਸ;

    ਬੱਚਾ_ਚੌਖਟੇ_ctx = (AVHWFramesContext*)s->ਬੱਚਾ_ਚੌਖਟੇ_ref->ਅੰਕੜੇ;
    ਜੇ (!ਬੱਚਾ_ਚੌਖਟੇ_ctx->device_ctx)
        ਵਾਪਸ;

#ਜੇ CONFIG_VAAPI
    ਜੇ (ਬੱਚਾ_ਚੌਖਟੇ_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->ਪਹਿਲਾ);
#ਜੇ_ਅੰਤ

    av_freep(&hdl_pair);
    av_ਚੌਖਟਾ_free(&qsv_surface->ਬੱਚਾ_ਚੌਖਟਾ);
    av_freep(&qsv_surface);
}

ਸਥਿਰ AVBufferRef *qsv_fixed_pool_alloc(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    ਜੇ (s->nb_surfaces_ਵਰਤਿਆ < hwctx->nb_surfaces) {
        s->nb_surfaces_ਵਰਤਿਆ++;
        ਵਾਪਸ av_ਬਫਰ_create((uint8_t*)(s->surfaces_ਅੰਦਰੂਨੀ + s->nb_surfaces_ਵਰਤਿਆ - 1),
                                ਆਕਾਰ(*hwctx->surfaces), qsv_pool_release_dummy, ਨਿਰਾ, 0);
    }

    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ AVBufferRef *qsv_dynamic_pool_alloc(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *ਬੱਚਾ_ਚੌਖਟੇ_ctx;
    QSVSurface *qsv_surface = ਨਿਰਾ;
    mfxHDLPair *handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    ਪੂਰਨ ret;

    ਜੇ (!s->ਬੱਚਾ_ਚੌਖਟੇ_ref)
        ਜਾਓ fail;

    ਬੱਚਾ_ਚੌਖਟੇ_ctx = (AVHWFramesContext*)s->ਬੱਚਾ_ਚੌਖਟੇ_ref->ਅੰਕੜੇ;
    ਜੇ (!ਬੱਚਾ_ਚੌਖਟੇ_ctx->device_ctx)
        ਜਾਓ fail;

#ਜੇ CONFIG_DXVA2
    ਜੇ (ਬੱਚਾ_ਚੌਖਟੇ_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        ਜਾਓ fail;
    }
#ਜੇ_ਅੰਤ

    qsv_surface = av_calloc(1, ਆਕਾਰ(*qsv_surface));
    ਜੇ (!qsv_surface)
        ਜਾਓ fail;

    qsv_surface->ਬੱਚਾ_ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!qsv_surface->ਬੱਚਾ_ਚੌਖਟਾ)
        ਜਾਓ fail;

    ret = av_hwframe_get_ਬਫਰ(s->ਬੱਚਾ_ਚੌਖਟੇ_ref, qsv_surface->ਬੱਚਾ_ਚੌਖਟਾ, 0);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ = av_calloc(1, ਆਕਾਰ(*handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ));
    ਜੇ (!handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ)
        ਜਾਓ fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

#ਜੇ CONFIG_VAAPI
    ਜੇ (ਬੱਚਾ_ਚੌਖਟੇ_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_ਅੰਦਰੂਨੀ;

        surface_id_ਅੰਦਰੂਨੀ = av_calloc(1, ਆਕਾਰ(*surface_id_ਅੰਦਰੂਨੀ));
        ਜੇ (!surface_id_ਅੰਦਰੂਨੀ)
            ਜਾਓ fail;

        *surface_id_ਅੰਦਰੂਨੀ = (VASurfaceID)(uintptr_t)qsv_surface->ਬੱਚਾ_ਚੌਖਟਾ->ਅੰਕੜੇ[3];
        handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ->ਪਹਿਲਾ = (mfxHDL)surface_id_ਅੰਦਰੂਨੀ;
        handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ->ਦੂਜਾ = (mfxMemId)MFX_INFINITE;
    }
#ਜੇ_ਅੰਤ

#ਜੇ CONFIG_D3D11VA
    ਜੇ (ਬੱਚਾ_ਚੌਖਟੇ_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *ਬੱਚਾ_ਚੌਖਟੇ_hwctx = ਬੱਚਾ_ਚੌਖਟੇ_ctx->hwctx;
        handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ->ਪਹਿਲਾ = (mfxMemId)qsv_surface->ਬੱਚਾ_ਚੌਖਟਾ->ਅੰਕੜੇ[0];

        ਜੇ (ਬੱਚਾ_ਚੌਖਟੇ_hwctx->BindFlags & D3_D11_BIND_RENDER_ਨਿਸ਼ਾਨਾ)
            handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ->ਦੂਜਾ = (mfxMemId)MFX_INFINITE;
        ਨਹੀਂਤਾਂ
            handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ->ਦੂਜਾ = (mfxMemId)qsv_surface->ਬੱਚਾ_ਚੌਖਟਾ->ਅੰਕੜੇ[1];

    }
#ਜੇ_ਅੰਤ

    qsv_surface->mfx_surface.ਅੰਕੜੇ_2.MemId = (mfxMemId)handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ;
    ਵਾਪਸ av_ਬਫਰ_create((uint8_t *)qsv_surface, ਆਕਾਰ(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    ਜੇ (qsv_surface) {
        av_ਚੌਖਟਾ_free(&qsv_surface->ਬੱਚਾ_ਚੌਖਟਾ);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ);

    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ AVBufferRef *qsv_pool_alloc(ਖਾਲੀ *opaque, size_t ਮਾਪ)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    ਜੇ (hwctx->nb_surfaces == 0) {
        ਵਾਪਸ qsv_dynamic_pool_alloc(opaque, ਮਾਪ);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ qsv_fixed_pool_alloc(opaque, ਮਾਪ);
    }
}

ਸਥਿਰ ਪੂਰਨ qsv_init_ਬੱਚਾ_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *ਬੱਚਾ_device_ref = ਨਿਰਾ;
    AVBufferRef *ਬੱਚਾ_ਚੌਖਟੇ_ref = ਨਿਰਾ;

    AVHWDeviceContext *ਬੱਚਾ_device_ctx;
    AVHWFramesContext *ਬੱਚਾ_ਚੌਖਟੇ_ctx;

    ਪੂਰਨ i, ret = 0;

    ਜੇ (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }

    ਬੱਚਾ_device_ref = av_hwdevice_ctx_alloc(device_priv->ਬੱਚਾ_device_type);
    ਜੇ (!ਬੱਚਾ_device_ref)
        ਵਾਪਸ AVERROR(ENOMEM);
    ਬੱਚਾ_device_ctx   = (AVHWDeviceContext*)ਬੱਚਾ_device_ref->ਅੰਕੜੇ;

#ਜੇ CONFIG_VAAPI
    ਜੇ (ਬੱਚਾ_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *ਬੱਚਾ_device_hwctx = ਬੱਚਾ_device_ctx->hwctx;
        ਬੱਚਾ_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
    ਜੇ (ਬੱਚਾ_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *ਬੱਚਾ_device_hwctx = ਬੱਚਾ_device_ctx->hwctx;
        ID3_D11_Device_ਜੋੜੋ_Ref((ID3D11Device*)device_priv->handle);
        ਬੱਚਾ_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
    ਜੇ (ਬੱਚਾ_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *ਬੱਚਾ_device_hwctx = ਬੱਚਾ_device_ctx->hwctx;
        ਬੱਚਾ_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#ਜੇ_ਅੰਤ

    ret = av_hwdevice_ctx_init(ਬੱਚਾ_device_ref);
    ਜੇ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        ਜਾਓ fail;
    }

    ਬੱਚਾ_ਚੌਖਟੇ_ref = av_hwframe_ctx_alloc(ਬੱਚਾ_device_ref);
    ਜੇ (!ਬੱਚਾ_ਚੌਖਟੇ_ref) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }
    ਬੱਚਾ_ਚੌਖਟੇ_ctx = (AVHWFramesContext*)ਬੱਚਾ_ਚੌਖਟੇ_ref->ਅੰਕੜੇ;

    ਬੱਚਾ_ਚੌਖਟੇ_ctx->format            = device_priv->ਬੱਚਾ_pix_fmt;
    ਬੱਚਾ_ਚੌਖਟੇ_ctx->sw_format         = ctx->sw_format;
    ਬੱਚਾ_ਚੌਖਟੇ_ctx->initial_pool_ਮਾਪ = ctx->initial_pool_ਮਾਪ;
    ਬੱਚਾ_ਚੌਖਟੇ_ctx->ਚੌੜਾਈ             = FFALIGN(ctx->ਚੌੜਾਈ, 16);
    ਬੱਚਾ_ਚੌਖਟੇ_ctx->ਉਚਾਈ            = FFALIGN(ctx->ਉਚਾਈ, 16);

#ਜੇ CONFIG_D3D11VA
    ਜੇ (ਬੱਚਾ_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *ਬੱਚਾ_ਚੌਖਟੇ_hwctx = ਬੱਚਾ_ਚੌਖਟੇ_ctx->hwctx;
        ਜੇ (hwctx->ਚੌਖਟਾ_type == 0)
            hwctx->ਚੌਖਟਾ_type = MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_PROCESSOR_ਨਿਸ਼ਾਨਾ;
        ਜੇ (hwctx->ਚੌਖਟਾ_type & MFX_MEMTYPE_SHARED_RESOURCE)
            ਬੱਚਾ_ਚੌਖਟੇ_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        ਬੱਚਾ_ਚੌਖਟੇ_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->ਚੌਖਟਾ_type);
    }
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
    ਜੇ (ਬੱਚਾ_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_ਚੌਖਟੇ_Context *ਬੱਚਾ_ਚੌਖਟੇ_hwctx = ਬੱਚਾ_ਚੌਖਟੇ_ctx->hwctx;
        ਜੇ (hwctx->ਚੌਖਟਾ_type & MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_PROCESSOR_ਨਿਸ਼ਾਨਾ)
            ਬੱਚਾ_ਚੌਖਟੇ_hwctx->surface_type = DXVA2_Video_Processor_Render_ਨਿਸ਼ਾਨਾ;
        ਨਹੀਂਤਾਂ
            ਬੱਚਾ_ਚੌਖਟੇ_hwctx->surface_type = DXVA2_Video_Decoder_Render_ਨਿਸ਼ਾਨਾ;
    }
#ਜੇ_ਅੰਤ

    ret = av_hwframe_ctx_init(ਬੱਚਾ_ਚੌਖਟੇ_ref);
    ਜੇ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        ਜਾਓ fail;
    }

#ਜੇ CONFIG_VAAPI
    ਜੇ (ਬੱਚਾ_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *ਬੱਚਾ_ਚੌਖਟੇ_hwctx = ਬੱਚਾ_ਚੌਖਟੇ_ctx->hwctx;
        ਲਈ (i = 0; i < ctx->initial_pool_ਮਾਪ; i++) {
            s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਪਹਿਲਾ = ਬੱਚਾ_ਚੌਖਟੇ_hwctx->surface_ids + i;
            s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਦੂਜਾ = (mfxMemId)MFX_INFINITE;
            s->surfaces_ਅੰਦਰੂਨੀ[i].ਅੰਕੜੇ_2.MemId = (mfxMemId)&s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i];
        }
        hwctx->ਚੌਖਟਾ_type = MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_DECODER_ਨਿਸ਼ਾਨਾ;
    }
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
    ਜੇ (ਬੱਚਾ_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *ਬੱਚਾ_ਚੌਖਟੇ_hwctx = ਬੱਚਾ_ਚੌਖਟੇ_ctx->hwctx;
        ਲਈ (i = 0; i < ctx->initial_pool_ਮਾਪ; i++) {
            s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਪਹਿਲਾ = (mfxMemId)ਬੱਚਾ_ਚੌਖਟੇ_hwctx->texture_infos[i].texture;
            ਜੇ(ਬੱਚਾ_ਚੌਖਟੇ_hwctx->BindFlags & D3_D11_BIND_RENDER_ਨਿਸ਼ਾਨਾ) {
                s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਦੂਜਾ = (mfxMemId)MFX_INFINITE;
            } ਨਹੀਂਤਾਂ {
                s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਦੂਜਾ = (mfxMemId)ਬੱਚਾ_ਚੌਖਟੇ_hwctx->texture_infos[i].ਸੂਚਕਾਂਕ;
            }
            s->surfaces_ਅੰਦਰੂਨੀ[i].ਅੰਕੜੇ_2.MemId = (mfxMemId)&s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i];
        }
        ਜੇ (ਬੱਚਾ_ਚੌਖਟੇ_hwctx->BindFlags & D3_D11_BIND_RENDER_ਨਿਸ਼ਾਨਾ) {
            hwctx->ਚੌਖਟਾ_type |= MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_PROCESSOR_ਨਿਸ਼ਾਨਾ;
        } ਨਹੀਂਤਾਂ {
            hwctx->ਚੌਖਟਾ_type |= MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_DECODER_ਨਿਸ਼ਾਨਾ;
        }
    }
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
    ਜੇ (ਬੱਚਾ_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_ਚੌਖਟੇ_Context *ਬੱਚਾ_ਚੌਖਟੇ_hwctx = ਬੱਚਾ_ਚੌਖਟੇ_ctx->hwctx;
        ਲਈ (i = 0; i < ctx->initial_pool_ਮਾਪ; i++) {
            s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਪਹਿਲਾ = (mfxMemId)ਬੱਚਾ_ਚੌਖਟੇ_hwctx->surfaces[i];
            s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਦੂਜਾ = (mfxMemId)MFX_INFINITE;
            s->surfaces_ਅੰਦਰੂਨੀ[i].ਅੰਕੜੇ_2.MemId = (mfxMemId)&s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i];
        }
        ਜੇ (ਬੱਚਾ_ਚੌਖਟੇ_hwctx->surface_type == DXVA2_Video_Processor_Render_ਨਿਸ਼ਾਨਾ)
            hwctx->ਚੌਖਟਾ_type = MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_PROCESSOR_ਨਿਸ਼ਾਨਾ;
        ਨਹੀਂਤਾਂ
            hwctx->ਚੌਖਟਾ_type = MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_DECODER_ਨਿਸ਼ਾਨਾ;
    }
#ਜੇ_ਅੰਤ

    s->ਬੱਚਾ_ਚੌਖਟੇ_ref       = ਬੱਚਾ_ਚੌਖਟੇ_ref;
    ਬੱਚਾ_ਚੌਖਟੇ_ref          = ਨਿਰਾ;

fail:
    av_ਬਫਰ_unref(&ਬੱਚਾ_device_ref);
    av_ਬਫਰ_unref(&ਬੱਚਾ_ਚੌਖਟੇ_ref);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ qsv_init_surface(AVHWFramesContext *ctx, mfx_ਚੌਖਟਾ_Surface1 *surf)
{
    ਅਚਲ AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    ਜੇ (!desc)
        ਵਾਪਸ AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    ਜੇ (!fourcc)
        ਵਾਪਸ AVERROR(EINVAL);

    surf->Info.ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_Luma   = desc->comp[0].ਡੂੰਘਾਈ;
    surf->Info.ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_Chroma = desc->comp[0].ਡੂੰਘਾਈ;
    surf->Info.ਖਿਸਕਾਓ_2          = qsv_ਖਿਸਕਾਓ_from_pix_fmt(ctx->sw_format);

    ਜੇ (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    ਨਹੀਂਤਾਂ ਜੇ (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    ਨਹੀਂਤਾਂ
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.ਚੌੜਾਈ_2          = FFALIGN(ctx->ਚੌੜਾਈ, 16);
    surf->Info.CropW          = ctx->ਚੌੜਾਈ;
    surf->Info.ਉਚਾਈ_2         = FFALIGN(ctx->ਉਚਾਈ, 16);
    surf->Info.CropH          = ctx->ਉਚਾਈ;
    surf->Info.ਚੌਖਟਾ_ਦਰ_Ext_N  = 25;
    surf->Info.ਚੌਖਟਾ_ਦਰ_Ext_D  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *ਚੌਖਟੇ_hwctx = &s->p;

    ਪੂਰਨ i, ret = 0;

    ਜੇ (ctx->initial_pool_ਮਾਪ < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        ਵਾਪਸ AVERROR(EINVAL);
    } ਨਹੀਂਤਾਂ ਜੇ (ctx->initial_pool_ਮਾਪ == 0) {
        mfx_ਚੌਖਟਾ_Surface1 mfx_surf1;

        ret = qsv_init_ਬੱਚਾ_ctx(ctx);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;

        ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ = av_ਬਫਰ_pool_init2(ਆਕਾਰ(mfx_ਚੌਖਟਾ_Surface1),
                                                                 ctx, qsv_pool_alloc, ਨਿਰਾ);
        ਜੇ (!ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ)
            ਵਾਪਸ AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, ਆਕਾਰ(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->ਚੌਖਟਾ_info = mfx_surf1.Info;
        ਚੌਖਟੇ_hwctx->info = &s->ਚੌਖਟਾ_info;
        ਚੌਖਟੇ_hwctx->nb_surfaces = 0;

        ਵਾਪਸ 0;
    }

    s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ = av_calloc(ctx->initial_pool_ਮਾਪ,
                                         ਆਕਾਰ(*s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ));
    ਜੇ (!s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ)
        ਵਾਪਸ AVERROR(ENOMEM);

    s->surfaces_ਅੰਦਰੂਨੀ = av_calloc(ctx->initial_pool_ਮਾਪ,
                                     ਆਕਾਰ(*s->surfaces_ਅੰਦਰੂਨੀ));
    ਜੇ (!s->surfaces_ਅੰਦਰੂਨੀ)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (i = 0; i < ctx->initial_pool_ਮਾਪ; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_ਅੰਦਰੂਨੀ[i]);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
    }

#ਜੇ QSV_HAVE_OPAQUE
    ਜੇ (!(ਚੌਖਟੇ_hwctx->ਚੌਖਟਾ_type & MFX_MEMTYPE_OPAQUE_ਚੌਖਟਾ)) {
        ret = qsv_init_ਬੱਚਾ_ctx(ctx);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
    }
#ਨਹੀਂਤਾਂ
    ret = qsv_init_ਬੱਚਾ_ctx(ctx);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;
#ਜੇ_ਅੰਤ

    ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ = av_ਬਫਰ_pool_init2(ਆਕਾਰ(mfx_ਚੌਖਟਾ_Surface1),
                                                             ctx, qsv_pool_alloc, ਨਿਰਾ);
    ਜੇ (!ffhwframesctx(ctx)->pool_ਅੰਦਰੂਨੀ)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਚੌਖਟੇ_hwctx->surfaces    = s->surfaces_ਅੰਦਰੂਨੀ;
    ਚੌਖਟੇ_hwctx->nb_surfaces = ctx->initial_pool_ਮਾਪ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ mfx_ਸਥਿਤੀ ਚੌਖਟਾ_alloc(mfxHDL pthis, mfx_ਚੌਖਟਾ_Alloc_Request *req,
                             mfx_ਚੌਖਟਾ_Alloc_Response *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfx_ਚੌਖਟਾ_Info *i  = &req->Info;
    mfx_ਚੌਖਟਾ_Info *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    ਜੇ (!(req->Type & MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_PROCESSOR_ਨਿਸ਼ਾਨਾ) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_ਚੌਖਟਾ))
        ਵਾਪਸ MFX_ERR_UNSUPPORTED;
    ਜੇ (i->ਚੌੜਾਈ_2  > i1->ਚੌੜਾਈ_2 || i->ਉਚਾਈ_2 > i1->ਉਚਾਈ_2 ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->ਚੌੜਾਈ_2,  i->ਉਚਾਈ_2,  i->FourCC,  i->ChromaFormat,
               i1->ਚੌੜਾਈ_2, i1->ਉਚਾਈ_2, i1->FourCC, i1->ChromaFormat);
        ਵਾਪਸ MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->ਅੰਕ_ਚੌਖਟਾ_Actual = hwctx->nb_surfaces;

    ਵਾਪਸ MFX_ERR_NONE;
}

ਸਥਿਰ mfx_ਸਥਿਤੀ ਚੌਖਟਾ_free(mfxHDL pthis, mfx_ਚੌਖਟਾ_Alloc_Response *resp)
{
    ਵਾਪਸ MFX_ERR_NONE;
}

ਸਥਿਰ mfx_ਸਥਿਤੀ ਚੌਖਟਾ_ਤਾਲਾ(mfxHDL pthis, mfxMemId mid, mfx_ਚੌਖਟਾ_ਅੰਕੜੇ *ptr)
{
    ਵਾਪਸ MFX_ERR_UNSUPPORTED;
}

ਸਥਿਰ mfx_ਸਥਿਤੀ ਚੌਖਟਾ_unlock(mfxHDL pthis, mfxMemId mid, mfx_ਚੌਖਟਾ_ਅੰਕੜੇ *ptr)
{
    ਵਾਪਸ MFX_ERR_UNSUPPORTED;
}

ਸਥਿਰ mfx_ਸਥਿਤੀ ਚੌਖਟਾ_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->ਪਹਿਲਾ = pair_src->ਪਹਿਲਾ;

    ਜੇ (pair_src->ਦੂਜਾ != (mfxMemId)MFX_INFINITE)
        pair_dst->ਦੂਜਾ = pair_src->ਦੂਜਾ;
    ਵਾਪਸ MFX_ERR_NONE;
}

#ਜੇ QSV_ONEVPL

ਸਥਿਰ ਪੂਰਨ qsv_d3d11_update_config(ਖਾਲੀ *ctx, mfxHDL handle, mfxConfig cfg)
{
    ਪੂਰਨ ret = AVERROR_UNKNOWN;
#ਜੇ CONFIG_D3D11VA
    mfx_ਸਥਿਤੀ sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = ਨਿਰਾ;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_ਮੁੱਲ = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (ਖਾਲੀ**)&pDXGIDevice);
    ਜੇ (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        ਜੇ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            ਵਾਪਸ ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        ਜੇ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            ਜਾਓ fail;
        }
    } ਨਹੀਂਤਾਂ {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        ਵਾਪਸ ret;
    }

    impl_ਮੁੱਲ.Type = MFX_VARIANT_TYPE_U16;
    impl_ਮੁੱਲ.ਅੰਕੜੇ_2.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ਅਚਲ mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_ਮੁੱਲ);
    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        ਜਾਓ fail;
    }

    impl_ਮੁੱਲ.Type = MFX_VARIANT_TYPE_PTR;
    impl_ਮੁੱਲ.ਅੰਕੜੇ_2.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ਅਚਲ mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_ਮੁੱਲ);
    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        ਜਾਓ fail;
    }

    impl_ਮੁੱਲ.Type = MFX_VARIANT_TYPE_U32;
    impl_ਮੁੱਲ.ਅੰਕੜੇ_2.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ਅਚਲ mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_ਮੁੱਲ);
    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        ਜਾਓ fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#ਜੇ_ਅੰਤ
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ qsv_d3d9_update_config(ਖਾਲੀ *ctx, mfxHDL handle, mfxConfig cfg)
{
    ਪੂਰਨ ret = AVERROR_UNKNOWN;
#ਜੇ CONFIG_DXVA2
    mfx_ਸਥਿਤੀ sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = ਨਿਰਾ;
    IDirect3DDevice9Ex *device_ex = ਨਿਰਾ;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = ਨਿਰਾ;
    IDirect3D9 *d3d9 = ਨਿਰਾ;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_ਮੁੱਲ = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        ਜਾਓ fail;
    }

    hr = IDirect3_DDevice_Manager9_ਤਾਲਾ_Device(devmgr, device_handle, &device, TRUE);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        ਜਾਓ fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (ਖਾਲੀ **)&device_ex);
    IDirect3DDevice9_Release(device);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        ਜਾਓ unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        ਜਾਓ unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        ਜਾਓ unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (ਖਾਲੀ **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        ਜਾਓ unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    ਜੇ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        ਜਾਓ release;
    }

    impl_ਮੁੱਲ.Type = MFX_VARIANT_TYPE_PTR;
    impl_ਮੁੱਲ.ਅੰਕੜੇ_2.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ਅਚਲ mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_ਮੁੱਲ);
    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        ਜਾਓ release;
    }

    ret = 0;

release:
    IDirect3D9Ex_Release(d3d9ex);
    IDirect3DDevice9Ex_Release(device_ex);

unlock:
    IDirect3DDeviceManager9_UnlockDevice(devmgr, device_handle, FALSE);
    IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
fail:
#ਜੇ_ਅੰਤ
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ qsv_va_update_config(ਖਾਲੀ *ctx, mfxHDL handle, mfxConfig cfg)
{
#ਜੇ CONFIG_VAAPI
#ਜੇ VA_CHECK_ਸੰਸਕਰਣ(1, 15, 0)
    mfx_ਸਥਿਤੀ sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_ਮੁੱਲ = {0};

    vas = va_Get_Display_ਗੁਣ(dpy, &attr, 1);
    ਜੇ (vas == VA_ਸਥਿਤੀ_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_ਮੁੱਲ.Type = MFX_VARIANT_TYPE_U16;
        impl_ਮੁੱਲ.ਅੰਕੜੇ_2.U16 = (attr.ਮੁੱਲ & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ਅਚਲ mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_ਮੁੱਲ);
        ਜੇ (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            ਜਾਓ fail;
        }
    } ਨਹੀਂਤਾਂ {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        ਜਾਓ fail;
    }

    ਵਾਪਸ 0;

fail:
#ਨਹੀਂਤਾਂ
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
    ਵਾਪਸ AVERROR_UNKNOWN;
}

ਸਥਿਰ ਪੂਰਨ qsv_new_mfx_loader(ਖਾਲੀ *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfx_ਸੰਸਕਰਣ *pver,
                              ਖਾਲੀ **ploader)
{
    mfx_ਸਥਿਤੀ sts;
    mfxLoader loader = ਨਿਰਾ;
    mfxConfig cfg;
    mfxVariant impl_ਮੁੱਲ = {0};

    *ploader = ਨਿਰਾ;
    loader = MFXLoad();
    ਜੇ (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        ਜਾਓ fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    ਜੇ (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        ਜਾਓ fail;
    }

    impl_ਮੁੱਲ.Type = MFX_VARIANT_TYPE_U32;
    impl_ਮੁੱਲ.ਅੰਕੜੇ_2.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ਅਚਲ mfxU8 *)"mfxImplDescription.Impl", impl_ਮੁੱਲ);
    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        ਜਾਓ fail;
    }

    impl_ਮੁੱਲ.Type = MFX_VARIANT_TYPE_U32;
    impl_ਮੁੱਲ.ਅੰਕੜੇ_2.U32 = pver->ਸੰਸਕਰਣ_2;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ਅਚਲ mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_ਮੁੱਲ);
    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        ਜਾਓ fail;
    }

    impl_ਮੁੱਲ.Type = MFX_VARIANT_TYPE_U32;
    impl_ਮੁੱਲ.ਅੰਕੜੇ_2.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ਅਚਲ mfxU8 *)"mfxImplDescription.VendorID", impl_ਮੁੱਲ);
    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        ਜਾਓ fail;
    }

    ਜੇ (MFX_HANDLE_VA_DISPLAY == handle_type) {
        ਜੇ (handle && qsv_va_update_config(ctx, handle, cfg))
            ਜਾਓ fail;

        impl_ਮੁੱਲ.ਅੰਕੜੇ_2.U32 = MFX_ACCEL_ਬਹੁਲਕ_ਰਾਹੀਂ_VAAPI;
    } ਨਹੀਂਤਾਂ ਜੇ (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        ਜੇ (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            ਜਾਓ fail;

        impl_ਮੁੱਲ.ਅੰਕੜੇ_2.U32 = MFX_ACCEL_ਬਹੁਲਕ_ਰਾਹੀਂ_D3_D9;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            ਜਾਓ fail;

        impl_ਮੁੱਲ.ਅੰਕੜੇ_2.U32 = MFX_ACCEL_ਬਹੁਲਕ_ਰਾਹੀਂ_D3_D11;
    }

    impl_ਮੁੱਲ.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ਅਚਲ mfxU8 *)"mfxImplDescription.AccelerationMode", impl_ਮੁੱਲ);
    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        ਜਾਓ fail;
    }

    *ploader = loader;

    ਵਾਪਸ 0;

fail:
    ਜੇ (loader)
        MFXUnload(loader);

    ਵਾਪਸ AVERROR_UNKNOWN;
}

ਸਥਿਰ ਪੂਰਨ qsv_create_mfx_session_from_loader(ਖਾਲੀ *ctx, mfxLoader loader, mfxSession *psession)
{
    mfx_ਸਥਿਤੀ sts;
    mfxSession session = ਨਿਰਾ;
    uint32_t impl_idx = 0;
    mfx_ਸੰਸਕਰਣ ver;

    ਜਦੋਂ (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        ਜੇ (sts == MFX_ERR_NOT_ਮਿਲਿਆ)
            ਰੋਕੋ;
        ਨਹੀਂਤਾਂ ਜੇ (sts != MFX_ERR_NONE) {
            impl_idx++;
            ਜਾਰੀ;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        ਜੇ (sts == MFX_ERR_NONE)
            ਰੋਕੋ;

        impl_idx++;
    }

    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        ਜਾਓ fail;
    }

    sts = MFXQuery_ਸੰਸਕਰਣ(session, &ver);
    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        ਜਾਓ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    ਵਾਪਸ 0;

fail:
    ਜੇ (session)
        MFXClose(session);

    ਵਾਪਸ AVERROR_UNKNOWN;
}

ਸਥਿਰ ਪੂਰਨ qsv_create_mfx_session(ਖਾਲੀ *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfx_ਸੰਸਕਰਣ *pver,
                                  mfxSession *psession,
                                  ਖਾਲੀ **ploader)
{
    mfxLoader loader = ਨਿਰਾ;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_ਸੰਸਕਰਣ_MAJOR, MFX_ਸੰਸਕਰਣ_MINOR, pver->Major, pver->Minor);

    ਜੇ (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        ਵਾਪਸ AVERROR(EXDEV);
    }

    *psession = ਨਿਰਾ;

    ਜੇ (!*ploader) {
        ਜੇ (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (ਖਾਲੀ **)&loader))
            ਜਾਓ fail;

        av_assert0(loader);
    } ਨਹੀਂਤਾਂ
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    ਜੇ (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        ਜਾਓ fail;

    ਜੇ (!*ploader)
        *ploader = loader;

    ਵਾਪਸ 0;

fail:
    ਜੇ (!*ploader && loader)
        MFXUnload(loader);

    ਵਾਪਸ AVERROR_UNKNOWN;
}

#ਨਹੀਂਤਾਂ

ਸਥਿਰ ਪੂਰਨ qsv_create_mfx_session(ਖਾਲੀ *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfx_ਸੰਸਕਰਣ *pver,
                                  mfxSession *psession,
                                  ਖਾਲੀ **ploader)
{
    mfx_ਸੰਸਕਰਣ ver;
    mfx_ਸਥਿਤੀ sts;
    mfxSession session = ਨਿਰਾ;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_ਸੰਸਕਰਣ_MAJOR, MFX_ਸੰਸਕਰਣ_MINOR, pver->Major, pver->Minor);

    *ploader = ਨਿਰਾ;
    *psession = ਨਿਰਾ;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        ਜਾਓ fail;
    }

    sts = MFXQuery_ਸੰਸਕਰਣ(session, &ver);
    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        ਜਾਓ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    ਜੇ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        ਜਾਓ fail;
    }

    *psession = session;

    ਵਾਪਸ 0;

fail:
    ਜੇ (session)
        MFXClose(session);

    ਵਾਪਸ AVERROR_UNKNOWN;
}

#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ qsv_init_ਅੰਦਰੂਨੀ_session(AVHWFramesContext *ctx,
                                     mfxSession *session, ਪੂਰਨ upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *ਚੌਖਟੇ_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    ਪੂਰਨ opaque = 0;

    mfx_ਚੌਖਟਾ_Allocator ਚੌਖਟਾ_allocator = {
        .pthis  = ctx,
        .Alloc  = ਚੌਖਟਾ_alloc,
        .ਤਾਲਾ_2   = ਚੌਖਟਾ_ਤਾਲਾ,
        .Unlock = ਚੌਖਟਾ_unlock,
        .GetHDL = ਚੌਖਟਾ_get_hdl,
        .Free   = ਚੌਖਟਾ_free,
    };

    mfxVideoParam par;
    mfx_ਸਥਿਤੀ err;
    ਪੂਰਨ                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    ਖਾਲੀ             **loader = &hwctx->loader;
    mfxSession ਮਾਪਾ_session = hwctx->session;
    mfxIMPL impl;
    mfx_ਸੰਸਕਰਣ ver;

    err = MFXQueryIMPL(ਮਾਪਾ_session, &impl);
    ਜੇ (err == MFX_ERR_NONE)
        err = MFXQuery_ਸੰਸਕਰਣ(ਮਾਪਾ_session, &ver);
    ਜੇ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

#ਜੇ QSV_HAVE_OPAQUE
    opaque = !!(ਚੌਖਟੇ_hwctx->ਚੌਖਟਾ_type & MFX_MEMTYPE_OPAQUE_ਚੌਖਟਾ);
#ਜੇ_ਅੰਤ

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    ਜੇ (ret)
        ਜਾਓ fail;

    ਜੇ (device_priv->handle) {
        err = MFXVideo_CORE_ਸੈੱਟ_Handle(*session, device_priv->handle_type,
                                     device_priv->handle);
        ਜੇ (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            ਜਾਓ fail;
        }
    }

    ਜੇ (QSV_RUNTIME_ਸੰਸਕਰਣ_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(ਮਾਪਾ_session, *session);
        ਜੇ (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            ਜਾਓ fail;
        }
    }

    ਜੇ (!opaque) {
        err = MFXVideo_CORE_ਸੈੱਟ_ਚੌਖਟਾ_Allocator(*session, &ਚੌਖਟਾ_allocator);
        ਜੇ (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            ਜਾਓ fail;
        }
    }

    memset(&par, 0, ਆਕਾਰ(par));

    ਜੇ (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_ਬਾਹਰਲਾ_VIDEO_ਸਮ੍ਰਿਤੀ :
                                 MFX_IOPATTERN_ਵਿੱਚ_VIDEO_ਸਮ੍ਰਿਤੀ;
    }
#ਜੇ QSV_HAVE_OPAQUE
    ਨਹੀਂਤਾਂ {
        par.ExtParam    = s->ext_buffers;
        par.ਅੰਕ_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
        par.IOPattern   = upload ? MFX_IOPATTERN_ਬਾਹਰਲਾ_OPAQUE_ਸਮ੍ਰਿਤੀ :
                                   MFX_IOPATTERN_ਵਿੱਚ_OPAQUE_ਸਮ੍ਰਿਤੀ;
    }
#ਜੇ_ਅੰਤ

    par.IOPattern |= upload ? MFX_IOPATTERN_ਵਿੱਚ_SYSTEM_ਸਮ੍ਰਿਤੀ :
                              MFX_IOPATTERN_ਬਾਹਰਲਾ_SYSTEM_ਸਮ੍ਰਿਤੀ;
    par.Async_ਡੂੰਘਾਈ = 1;

    par.vpp.ਵਿੱਚ_3 = ਚੌਖਟੇ_hwctx->nb_surfaces ? ਚੌਖਟੇ_hwctx->surfaces[0].Info : *ਚੌਖਟੇ_hwctx->info;

    /* Apparently VPP requires the frame rate to be set to some value, otherwise
     * init will fail (probably for the framerate conversion filter). Since we
     * are only doing data upload/download here, we just invent an arbitrary
     * value */
    par.vpp.ਵਿੱਚ_3.ਚੌਖਟਾ_ਦਰ_Ext_N = 25;
    par.vpp.ਵਿੱਚ_3.ਚੌਖਟਾ_ਦਰ_Ext_D = 1;
    par.vpp.ਬਾਹਰਲਾ_2 = par.vpp.ਵਿੱਚ_3;

    err = MFXVideoVPP_Init(*session, &par);
    ਜੇ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        ਜਾਓ fail;
    }

    ਵਾਪਸ 0;

fail:
    ਜੇ (*session)
        MFXClose(*session);

    *session = ਨਿਰਾ;

    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ qsv_ਚੌਖਟੇ_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *ਚੌਖਟੇ_hwctx = &s->p;

    ਪੂਰਨ opaque = 0;

    uint32_t fourcc;
    ਪੂਰਨ i, ret;

#ਜੇ QSV_HAVE_OPAQUE
    opaque = !!(ਚੌਖਟੇ_hwctx->ਚੌਖਟਾ_type & MFX_MEMTYPE_OPAQUE_ਚੌਖਟਾ);
#ਜੇ_ਅੰਤ

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    ਜੇ (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    ਜੇ (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        ਜੇ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            ਵਾਪਸ ret;
        }
    }

    ਜੇ (!opaque) {
        s->mem_ids = av_calloc(ਚੌਖਟੇ_hwctx->nb_surfaces, ਆਕਾਰ(*s->mem_ids));
        ਜੇ (!s->mem_ids)
            ਵਾਪਸ AVERROR(ENOMEM);

        ਲਈ (i = 0; i < ਚੌਖਟੇ_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = ਚੌਖਟੇ_hwctx->surfaces[i].ਅੰਕੜੇ_2.MemId;
    }
#ਜੇ QSV_HAVE_OPAQUE
    ਨਹੀਂਤਾਂ {
        s->surface_ptrs = av_calloc(ਚੌਖਟੇ_hwctx->nb_surfaces,
                                    ਆਕਾਰ(*s->surface_ptrs));
        ਜੇ (!s->surface_ptrs)
            ਵਾਪਸ AVERROR(ENOMEM);

        ਲਈ (i = 0; i < ਚੌਖਟੇ_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = ਚੌਖਟੇ_hwctx->surfaces + i;

        s->opaque_alloc.ਵਿੱਚ_3.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.ਵਿੱਚ_3.ਅੰਕ_Surface = ਚੌਖਟੇ_hwctx->nb_surfaces;
        s->opaque_alloc.ਵਿੱਚ_3.Type       = ਚੌਖਟੇ_hwctx->ਚੌਖਟਾ_type;

        s->opaque_alloc.ਬਾਹਰਲਾ_2 = s->opaque_alloc.ਵਿੱਚ_3;

        s->opaque_alloc.ਸਿਰਲੇਖ_2.ਬਫਰ_Id = MFX_EXTBUFF_OPAQUE_SURFACE_ਵੰਡ;
        s->opaque_alloc.ਸਿਰਲੇਖ_2.ਬਫਰ_Sz = ਆਕਾਰ(s->opaque_alloc);

        s->ext_buffers[0] = (mfx_Ext_ਬਫਰ*)&s->opaque_alloc;
    }
#ਜੇ_ਅੰਤ

    s->session_download = ਨਿਰਾ;
    s->session_upload   = ਨਿਰਾ;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#ਜੇ HAVE_PTHREADS
    pthread_mutex_init(&s->session_ਤਾਲਾ, ਨਿਰਾ);
#ਜੇ_ਅੰਤ

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ qsv_get_ਬਫਰ(AVHWFramesContext *ctx, AVFrame *ਚੌਖਟਾ)
{
    ਚੌਖਟਾ->buf[0] = av_ਬਫਰ_pool_get(ctx->pool);
    ਜੇ (!ਚੌਖਟਾ->buf[0])
        ਵਾਪਸ AVERROR(ENOMEM);

    ਚੌਖਟਾ->ਅੰਕੜੇ[3] = ਚੌਖਟਾ->buf[0]->ਅੰਕੜੇ;
    ਚੌਖਟਾ->format  = AV_PIX_FMT_QSV;
    ਚੌਖਟਾ->ਚੌੜਾਈ   = ctx->ਚੌੜਾਈ;
    ਚੌਖਟਾ->ਉਚਾਈ  = ctx->ਉਚਾਈ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    ਗਿਣਤੀ AVHWFrameTransferDirection dir,
                                    ਗਿਣਤੀ AVPixelFormat **formats)
{
    ਗਿਣਤੀ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ਆਕਾਰ(*fmts));
    ਜੇ (!fmts)
        ਵਾਪਸ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ qsv_ਚੌਖਟੇ_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, ਪੂਰਨ flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    ਪੂਰਨ i;

    ਚੋਣ (dst_ctx->device_ctx->type) {
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               ਆਕਾਰ(*dst_hwctx->surface_ids));
            ਜੇ (!dst_hwctx->surface_ids)
                ਵਾਪਸ AVERROR(ENOMEM);
            ਲਈ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].ਅੰਕੜੇ_2.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->ਪਹਿਲਾ;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
    ਹਾਲਤ AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_ਮਾਪ = src_ctx->initial_pool_ਮਾਪ;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 ਆਕਾਰ(*dst_hwctx->texture_infos));
            ਜੇ (!dst_hwctx->texture_infos)
                ਵਾਪਸ AVERROR(ENOMEM);
            ਜੇ (src_hwctx->ਚੌਖਟਾ_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            ਲਈ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].ਅੰਕੜੇ_2.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->ਪਹਿਲਾ;
                dst_hwctx->texture_infos[i].ਸੂਚਕਾਂਕ = pair->ਦੂਜਾ == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->ਦੂਜਾ;
            }
            ਜੇ (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } ਨਹੀਂਤਾਂ
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->ਚੌਖਟਾ_type);
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
    ਹਾਲਤ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_ਚੌਖਟੇ_Context *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            ਆਕਾਰ(*dst_hwctx->surfaces));
            ਜੇ (!dst_hwctx->surfaces)
                ਵਾਪਸ AVERROR(ENOMEM);
            ਲਈ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].ਅੰਕੜੇ_2.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->ਪਹਿਲਾ;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            ਜੇ (src_hwctx->ਚੌਖਟਾ_type == MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_DECODER_ਨਿਸ਼ਾਨਾ)
                dst_hwctx->surface_type = DXVA2_Video_Decoder_Render_ਨਿਸ਼ਾਨਾ;
            ਨਹੀਂਤਾਂ
                dst_hwctx->surface_type = DXVA2_Video_Processor_Render_ਨਿਸ਼ਾਨਾ;
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfx_ਚੌਖਟਾ_Surface1 *surf = (mfx_ਚੌਖਟਾ_Surface1*)src->ਅੰਕੜੇ[3];
    AVHWFramesContext *ਬੱਚਾ_ਚੌਖਟੇ_ctx;
    ਅਚਲ AVPixFmtDescriptor *desc;
    uint8_t *ਬੱਚਾ_ਅੰਕੜੇ;
    AVFrame *dummy;
    ਪੂਰਨ ret = 0;

    ਜੇ (!s->ਬੱਚਾ_ਚੌਖਟੇ_ref)
        ਵਾਪਸ AVERROR(ENOSYS);
    ਬੱਚਾ_ਚੌਖਟੇ_ctx = (AVHWFramesContext*)s->ਬੱਚਾ_ਚੌਖਟੇ_ref->ਅੰਕੜੇ;

    ਚੋਣ (ਬੱਚਾ_ਚੌਖਟੇ_ctx->device_ctx->type) {
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->ਅੰਕੜੇ_2.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        ਬੱਚਾ_ਅੰਕੜੇ = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->ਪਹਿਲਾ;
        ਰੋਕੋ;
    }
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
    ਹਾਲਤ AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->ਅੰਕੜੇ_2.MemId;
        ਬੱਚਾ_ਅੰਕੜੇ = pair->ਪਹਿਲਾ;
        ਰੋਕੋ;
    }
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
    ਹਾਲਤ AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->ਅੰਕੜੇ_2.MemId;
        ਬੱਚਾ_ਅੰਕੜੇ = pair->ਪਹਿਲਾ;
        ਰੋਕੋ;
    }
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    ਜੇ (dst->format == ਬੱਚਾ_ਚੌਖਟੇ_ctx->format) {
        ret = ff_hwframe_map_create(s->ਬੱਚਾ_ਚੌਖਟੇ_ref,
                                    dst, src, ਨਿਰਾ, ਨਿਰਾ);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;

        dst->ਚੌੜਾਈ   = src->ਚੌੜਾਈ;
        dst->ਉਚਾਈ  = src->ਉਚਾਈ;

       ਜੇ (ਬੱਚਾ_ਚੌਖਟੇ_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->ਅੰਕੜੇ_2.MemId;
            dst->ਅੰਕੜੇ[0] = pair->ਪਹਿਲਾ;
            dst->ਅੰਕੜੇ[1] = pair->ਦੂਜਾ == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->ਦੂਜਾ;
        } ਨਹੀਂਤਾਂ {
            dst->ਅੰਕੜੇ[3] = ਬੱਚਾ_ਅੰਕੜੇ;
        }

        ਵਾਪਸ 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    ਜੇ (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    dummy = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!dummy)
        ਵਾਪਸ AVERROR(ENOMEM);

    dummy->buf[0]        = av_ਬਫਰ_ref(src->buf[0]);
    dummy->hw_ਚੌਖਟੇ_ctx = av_ਬਫਰ_ref(s->ਬੱਚਾ_ਚੌਖਟੇ_ref);
    ਜੇ (!dummy->buf[0] || !dummy->hw_ਚੌਖਟੇ_ctx)
        ਜਾਓ fail;

    dummy->format        = ਬੱਚਾ_ਚੌਖਟੇ_ctx->format;
    dummy->ਚੌੜਾਈ         = src->ਚੌੜਾਈ;
    dummy->ਉਚਾਈ        = src->ਉਚਾਈ;

    ਜੇ (ਬੱਚਾ_ਚੌਖਟੇ_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->ਅੰਕੜੇ_2.MemId;
        dummy->ਅੰਕੜੇ[0] = pair->ਪਹਿਲਾ;
        dummy->ਅੰਕੜੇ[1] = pair->ਦੂਜਾ == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->ਦੂਜਾ;
    } ਨਹੀਂਤਾਂ {
        dummy->ਅੰਕੜੇ[3] = ਬੱਚਾ_ਅੰਕੜੇ;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_ਚੌਖਟਾ_free(&dummy);

    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ qsv_transfer_ਅੰਕੜੇ_ਬੱਚਾ(AVHWFramesContext *ctx, AVFrame *dst,
                                   ਅਚਲ AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *ਬੱਚਾ_ਚੌਖਟੇ_ctx = (AVHWFramesContext*)s->ਬੱਚਾ_ਚੌਖਟੇ_ref->ਅੰਕੜੇ;
    ਪੂਰਨ download = !!src->hw_ਚੌਖਟੇ_ctx;
    mfx_ਚੌਖਟਾ_Surface1 *surf = (mfx_ਚੌਖਟਾ_Surface1*)(download ? src->ਅੰਕੜੇ[3] : dst->ਅੰਕੜੇ[3]);

    AVFrame *dummy;
    ਪੂਰਨ ret;

    dummy = av_ਚੌਖਟਾ_alloc();
    ਜੇ (!dummy)
        ਵਾਪਸ AVERROR(ENOMEM);

    dummy->format        = ਬੱਚਾ_ਚੌਖਟੇ_ctx->format;
    dummy->ਚੌੜਾਈ         = src->ਚੌੜਾਈ;
    dummy->ਉਚਾਈ        = src->ਉਚਾਈ;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->ਅੰਕੜੇ[3]       = surf->ਅੰਕੜੇ_2.MemId;
    dummy->hw_ਚੌਖਟੇ_ctx = s->ਬੱਚਾ_ਚੌਖਟੇ_ref;

    ret = download ? av_hwframe_transfer_ਅੰਕੜੇ(dst, dummy, 0) :
                     av_hwframe_transfer_ਅੰਕੜੇ(dummy, src, 0);

    dummy->buf[0]        = ਨਿਰਾ;
    dummy->ਅੰਕੜੇ[3]       = ਨਿਰਾ;
    dummy->hw_ਚੌਖਟੇ_ctx = ਨਿਰਾ;

    av_ਚੌਖਟਾ_free(&dummy);

    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ map_ਚੌਖਟਾ_ਮੰਜ਼ਿਲ_surface(ਅਚਲ AVFrame *ਚੌਖਟਾ, mfx_ਚੌਖਟਾ_Surface1 *surface)
{
    ਚੋਣ (ਚੌਖਟਾ->format) {
    ਹਾਲਤ AV_PIX_FMT_NV12:
    ਹਾਲਤ AV_PIX_FMT_P010:
    ਹਾਲਤ AV_PIX_FMT_P012:
        surface->ਅੰਕੜੇ_2.Y  = ਚੌਖਟਾ->ਅੰਕੜੇ[0];
        surface->ਅੰਕੜੇ_2.UV = ਚੌਖਟਾ->ਅੰਕੜੇ[1];
        ਰੋਕੋ;

    ਹਾਲਤ AV_PIX_FMT_YUV420P:
        surface->ਅੰਕੜੇ_2.Y = ਚੌਖਟਾ->ਅੰਕੜੇ[0];
        surface->ਅੰਕੜੇ_2.U = ਚੌਖਟਾ->ਅੰਕੜੇ[1];
        surface->ਅੰਕੜੇ_2.V = ਚੌਖਟਾ->ਅੰਕੜੇ[2];
        ਰੋਕੋ;

    ਹਾਲਤ AV_PIX_FMT_BGRA:
        surface->ਅੰਕੜੇ_2.B = ਚੌਖਟਾ->ਅੰਕੜੇ[0];
        surface->ਅੰਕੜੇ_2.G = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 1;
        surface->ਅੰਕੜੇ_2.R = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 2;
        surface->ਅੰਕੜੇ_2.A = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 3;
        ਰੋਕੋ;
    ਹਾਲਤ AV_PIX_FMT_YUYV422:
        surface->ਅੰਕੜੇ_2.Y = ਚੌਖਟਾ->ਅੰਕੜੇ[0];
        surface->ਅੰਕੜੇ_2.U = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 1;
        surface->ਅੰਕੜੇ_2.V = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 3;
        ਰੋਕੋ;

    ਹਾਲਤ AV_PIX_FMT_Y210:
    ਹਾਲਤ AV_PIX_FMT_Y212:
        surface->ਅੰਕੜੇ_2.Y16 = (mfxU16 *)ਚੌਖਟਾ->ਅੰਕੜੇ[0];
        surface->ਅੰਕੜੇ_2.U16 = (mfxU16 *)ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 1;
        surface->ਅੰਕੜੇ_2.V16 = (mfxU16 *)ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 3;
        ਰੋਕੋ;
    ਹਾਲਤ AV_PIX_FMT_VUYX:
        surface->ਅੰਕੜੇ_2.V = ਚੌਖਟਾ->ਅੰਕੜੇ[0];
        surface->ਅੰਕੜੇ_2.U = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 1;
        surface->ਅੰਕੜੇ_2.Y = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->ਅੰਕੜੇ_2.A = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 3;
        ਰੋਕੋ;
    ਹਾਲਤ AV_PIX_FMT_XV30:
        surface->ਅੰਕੜੇ_2.U = ਚੌਖਟਾ->ਅੰਕੜੇ[0];
        ਰੋਕੋ;
    ਹਾਲਤ AV_PIX_FMT_XV36:
        surface->ਅੰਕੜੇ_2.U = ਚੌਖਟਾ->ਅੰਕੜੇ[0];
        surface->ਅੰਕੜੇ_2.Y = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 2;
        surface->ਅੰਕੜੇ_2.V = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->ਅੰਕੜੇ_2.A = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 6;
        ਰੋਕੋ;
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_PIX_FMT_UYVY422:
        surface->ਅੰਕੜੇ_2.Y = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 1;
        surface->ਅੰਕੜੇ_2.U = ਚੌਖਟਾ->ਅੰਕੜੇ[0];
        surface->ਅੰਕੜੇ_2.V = ਚੌਖਟਾ->ਅੰਕੜੇ[0] + 2;
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ਵਾਪਸ MFX_ERR_UNSUPPORTED;
    }
    surface->ਅੰਕੜੇ_2.Pitch     = ਚੌਖਟਾ->linesize[0];
    surface->ਅੰਕੜੇ_2.ਸਮਾਂ_Stamp = ਚੌਖਟਾ->pts;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ qsv_ਅੰਦਰੂਨੀ_session_check_init(AVHWFramesContext *ctx, ਪੂਰਨ upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    ਪੂਰਨ ret = 0;

    ਜੇ (atomic_load(inited))
        ਵਾਪਸ 0;

#ਜੇ HAVE_PTHREADS
    pthread_mutex_ਤਾਲਾ(&s->session_ਤਾਲਾ);
#ਜੇ_ਅੰਤ

    ਜੇ (!atomic_load(inited)) {
        ret = qsv_init_ਅੰਦਰੂਨੀ_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#ਜੇ HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_ਤਾਲਾ);
#ਜੇ_ਅੰਤ

    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ qsv_transfer_ਅੰਕੜੇ_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ਅਚਲ AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfx_ਚੌਖਟਾ_Surface1 ਬਾਹਰਲਾ = {{ 0 }};
    mfx_ਚੌਖਟਾ_Surface1 *ਵਿੱਚ_2 = (mfx_ਚੌਖਟਾ_Surface1*)src->ਅੰਕੜੇ[3];

    mfx_Sync_ਬਿੰਦੂ sync = ਨਿਰਾ;
    mfx_ਸਥਿਤੀ err;
    ਪੂਰਨ ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_ਚੌਖਟਾ = &s->realigned_download_ਚੌਖਟਾ;
    AVFrame *dst_ਚੌਖਟਾ;
    ਪੂਰਨ realigned = 0;

    ret = qsv_ਅੰਦਰੂਨੀ_session_check_init(ctx, 0);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    ਜੇ (dst->ਉਚਾਈ & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        ਜੇ (tmp_ਚੌਖਟਾ->format != dst->format ||
            tmp_ਚੌਖਟਾ->ਚੌੜਾਈ  != FFALIGN(dst->linesize[0], 16) ||
            tmp_ਚੌਖਟਾ->ਉਚਾਈ != FFALIGN(dst->ਉਚਾਈ, 16)) {
            av_ਚੌਖਟਾ_unref(tmp_ਚੌਖਟਾ);

            tmp_ਚੌਖਟਾ->format = dst->format;
            tmp_ਚੌਖਟਾ->ਚੌੜਾਈ  = FFALIGN(dst->linesize[0], 16);
            tmp_ਚੌਖਟਾ->ਉਚਾਈ = FFALIGN(dst->ਉਚਾਈ, 16);
            ret = av_ਚੌਖਟਾ_get_ਬਫਰ(tmp_ਚੌਖਟਾ, 0);
            ਜੇ (ret < 0)
                ਵਾਪਸ ret;
        }
    }

    dst_ਚੌਖਟਾ = realigned ? tmp_ਚੌਖਟਾ : dst;

    ਜੇ (!s->session_download) {
        ਜੇ (s->ਬੱਚਾ_ਚੌਖਟੇ_ref)
            ਵਾਪਸ qsv_transfer_ਅੰਕੜੇ_ਬੱਚਾ(ctx, dst_ਚੌਖਟਾ, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    ਬਾਹਰਲਾ.Info = ਵਿੱਚ_2->Info;
    map_ਚੌਖਟਾ_ਮੰਜ਼ਿਲ_surface(dst_ਚੌਖਟਾ, &ਬਾਹਰਲਾ);

    ਕਰੋ {
        err = MFXVideo_VPP_ਲੜੀਵਾਰ_ਚੌਖਟਾ_VPPAsync(s->session_download, ਵਿੱਚ_2, &ਬਾਹਰਲਾ, ਨਿਰਾ, &sync);
        ਜੇ (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } ਜਦੋਂ (err == MFX_WRN_DEVICE_BUSY);

    ਜੇ (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਕਰੋ {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } ਜਦੋਂ (err == MFX_WRN_ਵਿੱਚ_EXECUTION);
    ਜੇ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਜੇ (realigned) {
        tmp_ਚੌਖਟਾ->ਚੌੜਾਈ  = dst->ਚੌੜਾਈ;
        tmp_ਚੌਖਟਾ->ਉਚਾਈ = dst->ਉਚਾਈ;
        ret = av_ਚੌਖਟਾ_copy(dst, tmp_ਚੌਖਟਾ);
        tmp_ਚੌਖਟਾ->ਚੌੜਾਈ  = FFALIGN(dst->linesize[0], 16);
        tmp_ਚੌਖਟਾ->ਉਚਾਈ = FFALIGN(dst->ਉਚਾਈ, 16);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ qsv_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ(AVHWFramesContext *ctx, AVFrame *dst,
                                ਅਚਲ AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfx_ਚੌਖਟਾ_Surface1   ਵਿੱਚ_2 = {{ 0 }};
    mfx_ਚੌਖਟਾ_Surface1 *ਬਾਹਰਲਾ = (mfx_ਚੌਖਟਾ_Surface1*)dst->ਅੰਕੜੇ[3];
    mfx_ਚੌਖਟਾ_Info tmp_info;

    mfx_Sync_ਬਿੰਦੂ sync = ਨਿਰਾ;
    mfx_ਸਥਿਤੀ err;
    ਪੂਰਨ ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_ਚੌਖਟਾ = &s->realigned_upload_ਚੌਖਟਾ;
    ਅਚਲ AVFrame *src_ਚੌਖਟਾ;
    ਪੂਰਨ realigned = 0;

    ret = qsv_ਅੰਦਰੂਨੀ_session_check_init(ctx, 1);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    ਜੇ (src->ਉਚਾਈ & 15 || src->linesize[0] & 15) {
        realigned = 1;
        ਜੇ (tmp_ਚੌਖਟਾ->format != src->format ||
            tmp_ਚੌਖਟਾ->ਚੌੜਾਈ  != FFALIGN(src->ਚੌੜਾਈ, 16) ||
            tmp_ਚੌਖਟਾ->ਉਚਾਈ != FFALIGN(src->ਉਚਾਈ, 16)) {
            av_ਚੌਖਟਾ_unref(tmp_ਚੌਖਟਾ);

            tmp_ਚੌਖਟਾ->format = src->format;
            tmp_ਚੌਖਟਾ->ਚੌੜਾਈ  = FFALIGN(src->ਚੌੜਾਈ, 16);
            tmp_ਚੌਖਟਾ->ਉਚਾਈ = FFALIGN(src->ਉਚਾਈ, 16);
            ret = av_ਚੌਖਟਾ_get_ਬਫਰ(tmp_ਚੌਖਟਾ, 0);
            ਜੇ (ret < 0)
                ਵਾਪਸ ret;
        }
        ret = av_ਚੌਖਟਾ_copy(tmp_ਚੌਖਟਾ, src);
        ਜੇ (ret < 0) {
            av_ਚੌਖਟਾ_unref(tmp_ਚੌਖਟਾ);
            ਵਾਪਸ ret;
        }
        ret = qsv_fill_border(tmp_ਚੌਖਟਾ, src);
        ਜੇ (ret < 0) {
            av_ਚੌਖਟਾ_unref(tmp_ਚੌਖਟਾ);
            ਵਾਪਸ ret;
        }

        tmp_info = ਬਾਹਰਲਾ->Info;
        ਬਾਹਰਲਾ->Info.CropW = FFMIN(ਬਾਹਰਲਾ->Info.ਚੌੜਾਈ_2,  tmp_ਚੌਖਟਾ->ਚੌੜਾਈ);
        ਬਾਹਰਲਾ->Info.CropH = FFMIN(ਬਾਹਰਲਾ->Info.ਉਚਾਈ_2, tmp_ਚੌਖਟਾ->ਉਚਾਈ);
    }

    src_ਚੌਖਟਾ = realigned ? tmp_ਚੌਖਟਾ : src;

    ਜੇ (!s->session_upload) {
        ਜੇ (s->ਬੱਚਾ_ਚੌਖਟੇ_ref)
            ਵਾਪਸ qsv_transfer_ਅੰਕੜੇ_ਬੱਚਾ(ctx, dst, src_ਚੌਖਟਾ);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    ਵਿੱਚ_2.Info = ਬਾਹਰਲਾ->Info;
    map_ਚੌਖਟਾ_ਮੰਜ਼ਿਲ_surface(src_ਚੌਖਟਾ, &ਵਿੱਚ_2);

    ਕਰੋ {
        err = MFXVideo_VPP_ਲੜੀਵਾਰ_ਚੌਖਟਾ_VPPAsync(s->session_upload, &ਵਿੱਚ_2, ਬਾਹਰਲਾ, ਨਿਰਾ, &sync);
        ਜੇ (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } ਜਦੋਂ (err == MFX_WRN_DEVICE_BUSY);

    ਜੇ (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਕਰੋ {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } ਜਦੋਂ (err == MFX_WRN_ਵਿੱਚ_EXECUTION);
    ਜੇ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        ਵਾਪਸ AVERROR_UNKNOWN;
    }

    ਜੇ (realigned) {
        ਬਾਹਰਲਾ->Info.CropW = tmp_info.CropW;
        ਬਾਹਰਲਾ->Info.CropH = tmp_info.CropH;
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ qsv_dynamic_ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, ਪੂਰਨ flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfx_ਚੌਖਟਾ_Surface1 mfx_surf1;

    ਚੋਣ (src_ctx->device_ctx->type) {
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->ਚੌਖਟਾ_type  = MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_DECODER_ਨਿਸ਼ਾਨਾ;
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ

#ਜੇ CONFIG_D3D11VA
    ਹਾਲਤ AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        ਜੇ (src_hwctx->BindFlags & D3_D11_BIND_RENDER_ਨਿਸ਼ਾਨਾ) {
            dst_hwctx->ਚੌਖਟਾ_type |= MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_PROCESSOR_ਨਿਸ਼ਾਨਾ;
        } ਨਹੀਂਤਾਂ {
            dst_hwctx->ਚੌਖਟਾ_type |= MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_DECODER_ਨਿਸ਼ਾਨਾ;
        }
    }
    ਰੋਕੋ;
#ਜੇ_ਅੰਤ

    ਮੂਲ:
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, ਆਕਾਰ(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->ਚੌਖਟਾ_info = mfx_surf1.Info;
    dst_hwctx->info = &s->ਚੌਖਟਾ_info;
    dst_hwctx->nb_surfaces = 0;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ qsv_fixed_ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, ਪੂਰਨ flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    ਪੂਰਨ i;

    ਚੋਣ (src_ctx->device_ctx->type) {
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ = av_calloc(src_ctx->initial_pool_ਮਾਪ,
                                                 ਆਕਾਰ(*s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ));
            ਜੇ (!s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ)
                ਵਾਪਸ AVERROR(ENOMEM);
            s->surfaces_ਅੰਦਰੂਨੀ = av_calloc(src_hwctx->nb_surfaces,
                                             ਆਕਾਰ(*s->surfaces_ਅੰਦਰੂਨੀ));
            ਜੇ (!s->surfaces_ਅੰਦਰੂਨੀ)
                ਵਾਪਸ AVERROR(ENOMEM);
            ਲਈ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_ਅੰਦਰੂਨੀ[i]);
                s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਪਹਿਲਾ = src_hwctx->surface_ids + i;
                s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਦੂਜਾ = (mfxMemId)MFX_INFINITE;
                s->surfaces_ਅੰਦਰੂਨੀ[i].ਅੰਕੜੇ_2.MemId = (mfxMemId)&s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->ਚੌਖਟਾ_type  = MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_DECODER_ਨਿਸ਼ਾਨਾ;
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
    ਹਾਲਤ AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ = av_calloc(src_ctx->initial_pool_ਮਾਪ,
                                                 ਆਕਾਰ(*s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ));
            ਜੇ (!s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ)
                ਵਾਪਸ AVERROR(ENOMEM);
            s->surfaces_ਅੰਦਰੂਨੀ = av_calloc(src_ctx->initial_pool_ਮਾਪ,
                                             ਆਕਾਰ(*s->surfaces_ਅੰਦਰੂਨੀ));
            ਜੇ (!s->surfaces_ਅੰਦਰੂਨੀ)
                ਵਾਪਸ AVERROR(ENOMEM);
            ਲਈ (i = 0; i < src_ctx->initial_pool_ਮਾਪ; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_ਅੰਦਰੂਨੀ[i]);
                s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਪਹਿਲਾ = (mfxMemId)src_hwctx->texture_infos[i].texture;
                ਜੇ (src_hwctx->BindFlags & D3_D11_BIND_RENDER_ਨਿਸ਼ਾਨਾ) {
                    s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਦੂਜਾ = (mfxMemId)MFX_INFINITE;
                } ਨਹੀਂਤਾਂ {
                    s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਦੂਜਾ = (mfxMemId)src_hwctx->texture_infos[i].ਸੂਚਕਾਂਕ;
                }
                s->surfaces_ਅੰਦਰੂਨੀ[i].ਅੰਕੜੇ_2.MemId = (mfxMemId)&s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_ਮਾਪ;
            ਜੇ (src_hwctx->BindFlags & D3_D11_BIND_RENDER_ਨਿਸ਼ਾਨਾ) {
                dst_hwctx->ਚੌਖਟਾ_type |= MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_PROCESSOR_ਨਿਸ਼ਾਨਾ;
            } ਨਹੀਂਤਾਂ {
                dst_hwctx->ਚੌਖਟਾ_type |= MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_DECODER_ਨਿਸ਼ਾਨਾ;
            }
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
    ਹਾਲਤ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_ਚੌਖਟੇ_Context *src_hwctx = src_ctx->hwctx;
            s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ = av_calloc(src_ctx->initial_pool_ਮਾਪ,
                                                 ਆਕਾਰ(*s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ));
            ਜੇ (!s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ)
                ਵਾਪਸ AVERROR(ENOMEM);
            s->surfaces_ਅੰਦਰੂਨੀ = av_calloc(src_hwctx->nb_surfaces,
                                             ਆਕਾਰ(*s->surfaces_ਅੰਦਰੂਨੀ));
            ਜੇ (!s->surfaces_ਅੰਦਰੂਨੀ)
                ਵਾਪਸ AVERROR(ENOMEM);
            ਲਈ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_ਅੰਦਰੂਨੀ[i]);
                s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਪਹਿਲਾ = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i].ਦੂਜਾ = (mfxMemId)MFX_INFINITE;
                s->surfaces_ਅੰਦਰੂਨੀ[i].ਅੰਕੜੇ_2.MemId = (mfxMemId)&s->handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            ਜੇ (src_hwctx->surface_type == DXVA2_Video_Processor_Render_ਨਿਸ਼ਾਨਾ)
                dst_hwctx->ਚੌਖਟਾ_type = MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_PROCESSOR_ਨਿਸ਼ਾਨਾ;
            ਨਹੀਂਤਾਂ
                dst_hwctx->ਚੌਖਟਾ_type = MFX_MEMTYPE_VIDEO_ਸਮ੍ਰਿਤੀ_DECODER_ਨਿਸ਼ਾਨਾ;
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ਵਾਪਸ AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_ਅੰਦਰੂਨੀ;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ qsv_ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, ਪੂਰਨ flags)
{
    ਜੇ (src_ctx->initial_pool_ਮਾਪ < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        ਵਾਪਸ AVERROR(EINVAL);
    } ਨਹੀਂਤਾਂ ਜੇ (src_ctx->initial_pool_ਮਾਪ == 0) {
        ਵਾਪਸ qsv_dynamic_ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ(dst_ctx, src_ctx, flags);
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ qsv_fixed_ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ(dst_ctx, src_ctx, flags);
    }
}

ਸਥਿਰ ਪੂਰਨ qsv_fixed_pool_map_ਮੰਜ਼ਿਲ(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    ਪੂਰਨ i, err, ਸੂਚਕਾਂਕ = -1;

    ਲਈ (i = 0; i < hwctx->nb_surfaces && ਸੂਚਕਾਂਕ < 0; i++) {
        ਚੋਣ(src->format) {
#ਜੇ CONFIG_VAAPI
        ਹਾਲਤ AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].ਅੰਕੜੇ_2.MemId;
            ਜੇ (*(VASurfaceID*)pair->ਪਹਿਲਾ == (VASurfaceID)(uintptr_t)src->ਅੰਕੜੇ[3])
                ਸੂਚਕਾਂਕ = i;
            ਰੋਕੋ;
        }
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
        ਹਾਲਤ AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].ਅੰਕੜੇ_2.MemId;
            ਜੇ (pair->ਪਹਿਲਾ == src->ਅੰਕੜੇ[0]
                && (pair->ਦੂਜਾ == src->ਅੰਕੜੇ[1]
                    || (pair->ਦੂਜਾ == (mfxMemId)MFX_INFINITE && src->ਅੰਕੜੇ[1] == (uint8_t *)0)))
                ਸੂਚਕਾਂਕ = i;
            ਰੋਕੋ;
        }
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
        ਹਾਲਤ AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].ਅੰਕੜੇ_2.MemId;
            ਜੇ (pair->ਪਹਿਲਾ == src->ਅੰਕੜੇ[3])
                ਸੂਚਕਾਂਕ = i;
            ਰੋਕੋ;
        }
#ਜੇ_ਅੰਤ
        }
    }
    ਜੇ (ਸੂਚਕਾਂਕ < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_ਚੌਖਟੇ_ctx,
                                dst, src, ਨਿਰਾ, ਨਿਰਾ);
    ਜੇ (err)
        ਵਾਪਸ err;

    dst->ਚੌੜਾਈ   = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ  = src->ਉਚਾਈ;
    dst->ਅੰਕੜੇ[3] = (uint8_t*)&hwctx->surfaces[ਸੂਚਕਾਂਕ];

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfx_ਚੌਖਟਾ_Surface1 *surfaces_ਅੰਦਰੂਨੀ = (mfx_ਚੌਖਟਾ_Surface1 *)hwmap->priv;
    mfxHDLPair *handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ = (mfxHDLPair *)surfaces_ਅੰਦਰੂਨੀ->ਅੰਕੜੇ_2.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->ਸਰੋਤ_ਚੌਖਟੇ->ਅੰਕੜੇ;

    ਚੋਣ (src_ctx->format) {
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ->ਪਹਿਲਾ);

        ਰੋਕੋ;
    }
#ਜੇ_ਅੰਤ

#ਜੇ CONFIG_D3D11VA
    ਹਾਲਤ AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        ਰੋਕੋ;
    }
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        ਰੋਕੋ;
    }

    av_freep(&handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ);
    av_freep(&surfaces_ਅੰਦਰੂਨੀ);
}

ਸਥਿਰ ਪੂਰਨ qsv_dynamic_pool_map_ਮੰਜ਼ਿਲ(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    mfx_ਚੌਖਟਾ_Surface1 *surfaces_ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    mfxHDLPair *handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ = ਨਿਰਾ;
    ਪੂਰਨ ret = 0;

    surfaces_ਅੰਦਰੂਨੀ = av_calloc(1, ਆਕਾਰ(*surfaces_ਅੰਦਰੂਨੀ));
    ਜੇ (!surfaces_ਅੰਦਰੂਨੀ) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ = av_calloc(1, ਆਕਾਰ(*handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ));
    ਜੇ (!handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ) {
        ret = AVERROR(ENOMEM);
        ਜਾਓ fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_ਅੰਦਰੂਨੀ);
    ਜੇ (ret < 0)
        ਜਾਓ fail;

    ਚੋਣ (src->format) {
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_ਅੰਦਰੂਨੀ;

        surface_id_ਅੰਦਰੂਨੀ = av_calloc(1, ਆਕਾਰ(*surface_id_ਅੰਦਰੂਨੀ));
        ਜੇ (!surface_id_ਅੰਦਰੂਨੀ) {
            ret =AVERROR(ENOMEM);
            ਜਾਓ fail;
        }

        *surface_id_ਅੰਦਰੂਨੀ = (VASurfaceID)(uintptr_t)src->ਅੰਕੜੇ[3];
        handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ->ਪਹਿਲਾ = (mfxHDL)surface_id_ਅੰਦਰੂਨੀ;
        handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ->ਦੂਜਾ = (mfxMemId)MFX_INFINITE;

        ਰੋਕੋ;
    }
#ਜੇ_ਅੰਤ

#ਜੇ CONFIG_D3D11VA
    ਹਾਲਤ AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_ਚੌਖਟੇ_ctx->ਅੰਕੜੇ;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ->ਪਹਿਲਾ = (mfxMemId)src->ਅੰਕੜੇ[0];

        ਜੇ (src_hwctx->BindFlags & D3_D11_BIND_RENDER_ਨਿਸ਼ਾਨਾ) {
            handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ->ਦੂਜਾ = (mfxMemId)MFX_INFINITE;
        } ਨਹੀਂਤਾਂ {
            handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ->ਦੂਜਾ = (mfxMemId)src->ਅੰਕੜੇ[1];
        }

        ਰੋਕੋ;
    }
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ret = AVERROR(ENOSYS);
        ਜਾਓ fail;
    }

    surfaces_ਅੰਦਰੂਨੀ->ਅੰਕੜੇ_2.MemId = (mfxMemId)handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ;

    ret = ff_hwframe_map_create(dst->hw_ਚੌਖਟੇ_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_ਅੰਦਰੂਨੀ);
    ਜੇ (ret)
        ਜਾਓ fail;

    dst->ਚੌੜਾਈ   = src->ਚੌੜਾਈ;
    dst->ਉਚਾਈ  = src->ਉਚਾਈ;
    dst->ਅੰਕੜੇ[3] = (uint8_t*)surfaces_ਅੰਦਰੂਨੀ;

    ਵਾਪਸ 0;

fail:
    av_freep(&handle_ਜੋੜੇ_ਅੰਦਰੂਨੀ);
    av_freep(&surfaces_ਅੰਦਰੂਨੀ);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ qsv_map_ਮੰਜ਼ਿਲ(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ਅਚਲ AVFrame *src, ਪੂਰਨ flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    ਜੇ (hwctx->nb_surfaces)
        ਵਾਪਸ qsv_fixed_pool_map_ਮੰਜ਼ਿਲ(dst_ctx, dst, src, flags);
    ਨਹੀਂਤਾਂ
        ਵਾਪਸ qsv_dynamic_pool_map_ਮੰਜ਼ਿਲ(dst_ctx, dst, src, flags);
}

ਸਥਿਰ ਪੂਰਨ qsv_ਚੌਖਟੇ_get_constraints(AVHWDeviceContext *ctx,
                                      ਅਚਲ ਖਾਲੀ *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    ਪੂਰਨ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    ਆਕਾਰ(*constraints->valid_sw_formats));
    ਜੇ (!constraints->valid_sw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ਆਕਾਰ(*constraints->valid_hw_formats));
    ਜੇ (!constraints->valid_hw_formats)
        ਵਾਪਸ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    ਜੇ (hwctx->session)
        MFXClose(hwctx->session);

    ਜੇ (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_ਬਫਰ_unref(&priv->ਬੱਚਾ_device_ctx);
    av_freep(&priv);
}

ਸਥਿਰ mfxIMPL ਚੁਣੋ_implementation(ਅਚਲ ਅੱਖਰ *device, ਗਿਣਤੀ AVHWDeviceType ਬੱਚਾ_device_type)
{
    ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
        ਅਚਲ ਅੱਖਰ *name;
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
    ਪੂਰਨ i;

    ਜੇ (device) {
        ਲਈ (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            ਜੇ (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                ਰੋਕੋ;
            }
        ਜੇ (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, ਨਿਰਾ, 0);
    }

    ਜੇ (impl != MFX_IMPL_SOFTWARE) {
        ਜੇ (ਬੱਚਾ_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_ਰਾਹੀਂ_D3_D11;
        ਨਹੀਂਤਾਂ ਜੇ (ਬੱਚਾ_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_ਰਾਹੀਂ_D3_D9;
    }

    ਵਾਪਸ impl;
}

ਸਥਿਰ ਪੂਰਨ qsv_device_derive_from_ਬੱਚਾ(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *ਬੱਚਾ_device_ctx,
                                        ਪੂਰਨ flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfx_ਸੰਸਕਰਣ    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfx_ਸਥਿਤੀ     err;
    ਪੂਰਨ ret;

    ਚੋਣ (ਬੱਚਾ_device_ctx->type) {
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *ਬੱਚਾ_device_hwctx = ਬੱਚਾ_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)ਬੱਚਾ_device_hwctx->display;
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
    ਹਾਲਤ AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *ਬੱਚਾ_device_hwctx = ਬੱਚਾ_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)ਬੱਚਾ_device_hwctx->device;
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
    ਹਾਲਤ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *ਬੱਚਾ_device_hwctx = ਬੱਚਾ_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)ਬੱਚਾ_device_hwctx->devmgr;
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        ret = AVERROR(ENOSYS);
        ਜਾਓ fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    ਜੇ (ret)
        ਜਾਓ fail;

    err = MFXVideo_CORE_ਸੈੱਟ_Handle(hwctx->session, handle_type, handle);
    ਜੇ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        ਜਾਓ fail;
    }

    ਵਾਪਸ 0;

fail:
    ਜੇ (hwctx->session)
        MFXClose(hwctx->session);

    ਜੇ (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = ਨਿਰਾ;
    hwctx->loader = ਨਿਰਾ;
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *ਬੱਚਾ_device_ctx,
                             AVDictionary *opts, ਪੂਰਨ flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(ਆਕਾਰ(*priv));
    ਜੇ (!priv)
        ਵਾਪਸ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ਮੁਕਤ = qsv_device_free;

    impl = ਚੁਣੋ_implementation("hw_any", ਬੱਚਾ_device_ctx->type);
    ਵਾਪਸ qsv_device_derive_from_ਬੱਚਾ(ctx, impl,
                                        ਬੱਚਾ_device_ctx, flags);
}

ਸਥਿਰ ਪੂਰਨ qsv_device_create(AVHWDeviceContext *ctx, ਅਚਲ ਅੱਖਰ *device,
                             AVDictionary *opts, ਪੂਰਨ flags)
{
    QSVDevicePriv *priv;
    ਗਿਣਤੀ AVHWDeviceType ਬੱਚਾ_device_type;
    AVHWDeviceContext *ਬੱਚਾ_device;
    AVDictionary *ਬੱਚਾ_device_opts;
    AVDictionary_ਇੰਦਰਾਜ *e;

    mfxIMPL impl;
    ਪੂਰਨ ret;

    priv = av_mallocz(ਆਕਾਰ(*priv));
    ਜੇ (!priv)
        ਵਾਪਸ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ਮੁਕਤ        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", ਨਿਰਾ, 0);
    ਜੇ (e) {
        ਬੱਚਾ_device_type = av_hwdevice_ਲੱਭੋ_type_by_name(e->ਮੁੱਲ);
        ਜੇ (ਬੱਚਾ_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->ਮੁੱਲ);
            ਵਾਪਸ AVERROR(EINVAL);
        }
#ਜੇ QSV_ONEVPL
    } ਨਹੀਂਤਾਂ ਜੇ (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        ਬੱਚਾ_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } ਨਹੀਂਤਾਂ ਜੇ (CONFIG_DXVA2) {
        ਬੱਚਾ_device_type = AV_HWDEVICE_TYPE_DXVA2;
#ਨਹੀਂਤਾਂ
    } ਨਹੀਂਤਾਂ ਜੇ (CONFIG_DXVA2) {
        av_log(ਨਿਰਾ, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        ਬੱਚਾ_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } ਨਹੀਂਤਾਂ ਜੇ (CONFIG_D3D11VA) {
        ਬੱਚਾ_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#ਜੇ_ਅੰਤ
    } ਨਹੀਂਤਾਂ ਜੇ (CONFIG_VAAPI) {
        ਬੱਚਾ_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } ਨਹੀਂਤਾਂ {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        ਵਾਪਸ AVERROR(ENOSYS);
    }

#ਜੇ CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    ਜੇ (ਬੱਚਾ_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->ਮੁੱਲ);
        ਵਾਪਸ AVERROR(EINVAL);
    }
#ਜੇ_ਅੰਤ

    ਬੱਚਾ_device_opts = ਨਿਰਾ;
    ਚੋਣ (ਬੱਚਾ_device_type) {
#ਜੇ CONFIG_VAAPI
    ਹਾਲਤ AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_ਸੈੱਟ(&ਬੱਚਾ_device_opts, "vendor_id", "0x8086", 0);
            av_dict_ਸੈੱਟ(&ਬੱਚਾ_device_opts, "driver",    "iHD",    0);
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_D3D11VA
    ਹਾਲਤ AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_ਸੈੱਟ(&ਬੱਚਾ_device_opts, "vendor_id",        "0x8086",  0);
        }
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_DXVA2
    ਹਾਲਤ AV_HWDEVICE_TYPE_DXVA2:
#ਜੇ QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#ਜੇ_ਅੰਤ
        ਰੋਕੋ;
#ਜੇ_ਅੰਤ
    ਮੂਲ:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            ਵਾਪਸ AVERROR(ENOSYS);
        }
        ਰੋਕੋ;
    }

    e = av_dict_get(opts, "child_device", ਨਿਰਾ, 0);
    ret = av_hwdevice_ctx_create(&priv->ਬੱਚਾ_device_ctx, ਬੱਚਾ_device_type,
                                 e ? e->ਮੁੱਲ : ਨਿਰਾ, ਬੱਚਾ_device_opts, 0);

    av_dict_free(&ਬੱਚਾ_device_opts);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਬੱਚਾ_device = (AVHWDeviceContext*)priv->ਬੱਚਾ_device_ctx->ਅੰਕੜੇ;

    impl = ਚੁਣੋ_implementation(device, ਬੱਚਾ_device_type);

    ਵਾਪਸ qsv_device_derive_from_ਬੱਚਾ(ctx, impl, ਬੱਚਾ_device, 0);
}

ਅਚਲ HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_ਮਾਪ      = ਆਕਾਰ(QSVDeviceContext),
    .ਚੌਖਟੇ_hwctx_ਮਾਪ      = ਆਕਾਰ(QSVFramesContext),

    .device_create          = qsv_device_create,
    .device_derive          = qsv_device_derive,
    .device_init            = qsv_device_init,
    .ਚੌਖਟੇ_get_constraints = qsv_ਚੌਖਟੇ_get_constraints,
    .ਚੌਖਟੇ_init            = qsv_ਚੌਖਟੇ_init,
    .ਚੌਖਟੇ_uninit          = qsv_ਚੌਖਟੇ_uninit,
    .ਚੌਖਟੇ_get_ਬਫਰ      = qsv_get_ਬਫਰ,
    .transfer_get_formats   = qsv_transfer_get_formats,
    .transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ       = qsv_transfer_ਅੰਕੜੇ_ਮੰਜ਼ਿਲ,
    .transfer_ਅੰਕੜੇ_from     = qsv_transfer_ਅੰਕੜੇ_from,
    .map_ਮੰਜ਼ਿਲ                 = qsv_map_ਮੰਜ਼ਿਲ,
    .map_from               = qsv_map_from,
    .ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ       = qsv_ਚੌਖਟੇ_derive_ਮੰਜ਼ਿਲ,
    .ਚੌਖਟੇ_derive_from     = qsv_ਚੌਖਟੇ_derive_from,

    .pix_fmts = (ਅਚਲ ਗਿਣਤੀ AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
