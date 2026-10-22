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

#ಆದರೆ HAVE_PTHREADS
#ಅನ್ತರ್ಭಾವ <pthread.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು COBJMACROS
#ಆದರೆ CONFIG_VAAPI
#ಅನ್ತರ್ಭಾವ "hwcontext_vaapi.h"
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
#ಅನ್ತರ್ಭಾವ "hwcontext_d3d11va.h"
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
#ಅನ್ತರ್ಭಾವ <initguid.h>
#ಅನ್ತರ್ಭಾವ "hwcontext_dxva2.h"
#ಆದರೆ_ಅಂತ್ಯ

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

#ವ್ಯಾಖ್ಯಾನಿಸು QSV_ಆವೃತ್ತಿ_ATLEAST(MAJOR, MINOR)   \
    (MFX_ಆವೃತ್ತಿ_MAJOR > (MAJOR) ||         \
     MFX_ಆವೃತ್ತಿ_MAJOR == (MAJOR) && MFX_ಆವೃತ್ತಿ_MINOR >= (MINOR))

#ವ್ಯಾಖ್ಯಾನಿಸು QSV_RUNTIME_ಆವೃತ್ತಿ_ATLEAST(MFX_ಆವೃತ್ತಿ, MAJOR, MINOR)          \
    ((MFX_ಆವೃತ್ತಿ.Major > (MAJOR)) ||                                   \
     (MFX_ಆವೃತ್ತಿ.Major == (MAJOR) && MFX_ಆವೃತ್ತಿ.Minor >= (MINOR)))

#ವ್ಯಾಖ್ಯಾನಿಸು MFX_IMPL_ಮೂಲಕ_ಮುಖವಾಡ(impl) (0x0f00 & (impl))
#ವ್ಯಾಖ್ಯಾನಿಸು QSV_ONEVPL       QSV_ಆವೃತ್ತಿ_ATLEAST(2, 0)
#ವ್ಯಾಖ್ಯಾನಿಸು QSV_HAVE_OPAQUE  !QSV_ONEVPL

#ಆದರೆ QSV_ONEVPL
#ಅನ್ತರ್ಭಾವ <mfxdispatcher.h>
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು MFXUnload(a) ಮಾಡು { } ಆಗ(0)
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ QSVDevicePriv {
    AVBufferRef *ಮಗು_device_ctx;
} QSVDevicePriv;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfx_ಆವೃತ್ತಿ          ver;
    mfxIMPL             impl;

    ಎಣಿಕೆ AVHWDeviceType ಮಗು_device_type;
    ಎಣಿಕೆ AVPixelFormat  ಮಗು_pix_fmt;
} QSVDeviceContext;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#ಆದರೆ HAVE_PTHREADS
    pthread_mutex_t session_ಬೀಗ;
#ಆದರೆ_ಅಂತ್ಯ

    AVBufferRef *ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref;
    mfx_ಚೌಕಟ್ಟು_Surface1 *surfaces_ಆಂತರಿಕ;
    mfxHDLPair *handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ;
    ಪೂರ್ಣಾಂಕ             nb_surfaces_ಬಳಸಿದ;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#ಆದರೆ QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfx_ಚೌಕಟ್ಟು_Surface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfx_Ext_ಬಫರ್ *ext_buffers[1];
#ಆದರೆ_ಅಂತ್ಯ
    AVFrame realigned_upload_ಚೌಕಟ್ಟು;
    AVFrame realigned_download_ಚೌಕಟ್ಟು;

    mfx_ಚೌಕಟ್ಟು_Info ಚೌಕಟ್ಟು_info;
} QSVFramesContext;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ QSVSurface {
    mfx_ಚೌಕಟ್ಟು_Surface1 mfx_surface;
    AVFrame *ಮಗು_ಚೌಕಟ್ಟು;
} QSVSurface;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    ಎಣಿಕೆ AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_ಸರಿಸು;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#ಆದರೆ CONFIG_VAAPI
    { AV_PIX_FMT_UYVY422,
                       MFX_FOURCC_UYVY, 0 },
#ಆದರೆ_ಅಂತ್ಯ
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
#ಆದರೆ QSV_ಆವೃತ್ತಿ_ATLEAST(1, 31)
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
#ಆದರೆ_ಅಂತ್ಯ
};

ಬಾಹ್ಯ ಪೂರ್ಣಾಂಕ ff_qsv_get_surface_ತಳ_handle(mfx_ಚೌಕಟ್ಟು_Surface1 *surf,
                                          ಎಣಿಕೆ AVHWDeviceType ತಳ_dev_type,
                                          ಶೂನ್ಯ **ತಳ_handle);

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_init_surface(AVHWFramesContext *ctx, mfx_ಚೌಕಟ್ಟು_Surface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
ಪೂರ್ಣಾಂಕ ff_qsv_get_surface_ತಳ_handle(mfx_ಚೌಕಟ್ಟು_Surface1 *surf,
                                   ಎಣಿಕೆ AVHWDeviceType ತಳ_dev_type,
                                   ಶೂನ್ಯ **ತಳ_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->ದತ್ತಾಂಶ_2.MemId;
    ಆಯ್ಕೆ (ತಳ_dev_type) {
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VAAPI:
        ತಳ_handle[0] = handle_pair->ಮೊದಲ;
        ಹಿಂತಿರುಗಿ 0;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_D3D11VA:
        ತಳ_handle[0] = handle_pair->ಮೊದಲ;
        ತಳ_handle[1] = handle_pair->ಎರಡನೇ;
        ಹಿಂತಿರುಗಿ 0;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DXVA2:
        ತಳ_handle[0] = handle_pair->ಮೊದಲ;
        ಹಿಂತಿರುಗಿ 0;
#ಆದರೆ_ಅಂತ್ಯ
    }
    ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
}

ಸ್ಥಿರ uint32_t qsv_fourcc_from_pix_fmt(ಎಣಿಕೆ AVPixelFormat pix_fmt)
{
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        ಆದರೆ (supported_pixel_formats[i].pix_fmt == pix_fmt)
            ಹಿಂತಿರುಗಿ supported_pixel_formats[i].fourcc;
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ uint16_t qsv_ಸರಿಸು_from_pix_fmt(ಎಣಿಕೆ AVPixelFormat pix_fmt)
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        ಆದರೆ (supported_pixel_formats[i].pix_fmt == pix_fmt)
            ಹಿಂತಿರುಗಿ supported_pixel_formats[i].mfx_ಸರಿಸು;
    }

    ಹಿಂತಿರುಗಿ 0;
}

#ಆದರೆ CONFIG_D3D11VA
ಸ್ಥಿರ uint32_t qsv_get_d3d11va_bind_flags(ಪೂರ್ಣಾಂಕ mem_type)
{
    uint32_t bind_flags = 0;

    ಆದರೆ ((mem_type & MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_ENCODER_ಗುರಿ) && (mem_type & MFX_MEMTYPE_ಆಂತರಿಕ_ಚೌಕಟ್ಟು))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    ಇಲ್ಲದಿದ್ದರೆ
        bind_flags = D3D11_BIND_DECODER;

    ಆದರೆ ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_PROCESSOR_ಗುರಿ & mem_type))
        bind_flags = D3_D11_BIND_RENDER_ಗುರಿ;

    ಹಿಂತಿರುಗಿ bind_flags;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_fill_border(AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc;
    ಪೂರ್ಣಾಂಕ i, planes_nb = 0;
    ಆದರೆ (dst->format != src->format)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    ಗಾಗಿ (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    ಗಾಗಿ (i = 0; i < planes_nb; i++) {
        ಪೂರ್ಣಾಂಕ sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->ಅಗಲ,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->ಅಗಲ,
                                                 i);
        ಸ್ಥಿರಾಂಕ AVComponentDescriptor comp = desc->comp[i];
        ಆದರೆ (swidth < 0 || dwidth < 0) {
            av_log(ಖಾಲಿ, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
        sheight = src->ಎತ್ತರ;
        dheight = dst->ಎತ್ತರ;
        ಆದರೆ (i) {
            sheight = AV_CEIL_RSHIFT(src->ಎತ್ತರ, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->ಎತ್ತರ, desc->log2_chroma_h);
        }
        //fill right padding
        ಗಾಗಿ (y = 0; y < sheight; y++) {
            ಶೂನ್ಯ *ಸಾಲು_ptr = dst->ದತ್ತಾಂಶ[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(ಸಾಲು_ptr,
                           comp.ಆಳ > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        ಗಾಗಿ (y = sheight; y < dheight; y++) {
            ಸ್ಮರಣೆ_ನಕಲು(dst->ದತ್ತಾಂಶ[i]+y*dst->linesize[i],
                   dst->ದತ್ತಾಂಶ[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    ಪೂರ್ಣಾಂಕ   hw_handle_supported = 0;
    mfxHandleType handle_type;
    ಎಣಿಕೆ AVHWDeviceType device_type;
    ಎಣಿಕೆ AVPixelFormat  pix_fmt;
    mfx_ಸ್ಥಿತಿ err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    ಆದರೆ (err == MFX_ERR_NONE)
        err = MFXQuery_ಆವೃತ್ತಿ(hwctx->session, &s->ver);
    ಆದರೆ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಆದರೆ (MFX_IMPL_ಮೂಲಕ_VAAPI == MFX_IMPL_ಮೂಲಕ_ಮುಖವಾಡ(s->impl)) {
#ಆದರೆ CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#ಆದರೆ_ಅಂತ್ಯ
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (MFX_IMPL_ಮೂಲಕ_D3_D11 == MFX_IMPL_ಮೂಲಕ_ಮುಖವಾಡ(s->impl)) {
#ಆದರೆ CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#ಆದರೆ_ಅಂತ್ಯ
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (MFX_IMPL_ಮೂಲಕ_D3_D9 == MFX_IMPL_ಮೂಲಕ_ಮುಖವಾಡ(s->impl)) {
#ಆದರೆ CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#ಆದರೆ_ಅಂತ್ಯ
    }

    ಆದರೆ (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        ಆದರೆ (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->ಮಗು_device_type = device_type;
            s->ಮಗು_pix_fmt     = pix_fmt;
        }
    }
    ಆದರೆ (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ qsv_ಚೌಕಟ್ಟುಗಳು_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    ಆದರೆ (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = ಖಾಲಿ;
    s->session_download_init = 0;

    ಆದರೆ (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = ಖಾಲಿ;
    s->session_upload_init = 0;

#ಆದರೆ HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_ಬೀಗ);
#ಆದರೆ_ಅಂತ್ಯ

    av_freep(&s->mem_ids);
#ಆದರೆ QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#ಆದರೆ_ಅಂತ್ಯ
    av_freep(&s->surfaces_ಆಂತರಿಕ);
    av_freep(&s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ);
    av_ಚೌಕಟ್ಟು_unref(&s->realigned_upload_ಚೌಕಟ್ಟು);
    av_ಚೌಕಟ್ಟು_unref(&s->realigned_download_ಚೌಕಟ್ಟು);
    av_ಬಫರ್_unref(&s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref);
}

ಸ್ಥಿರ ಶೂನ್ಯ qsv_pool_release_dummy(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
}

ಸ್ಥಿರ ಶೂನ್ಯ qsv_pool_release(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)ದತ್ತಾಂಶ;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.ದತ್ತಾಂಶ_2.MemId;
    AVHWFramesContext *ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx;

    ಆದರೆ (!s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref)
        ಹಿಂತಿರುಗಿ;

    ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx = (AVHWFramesContext*)s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref->ದತ್ತಾಂಶ;
    ಆದರೆ (!ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->device_ctx)
        ಹಿಂತಿರುಗಿ;

#ಆದರೆ CONFIG_VAAPI
    ಆದರೆ (ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->ಮೊದಲ);
#ಆದರೆ_ಅಂತ್ಯ

    av_freep(&hdl_pair);
    av_ಚೌಕಟ್ಟು_free(&qsv_surface->ಮಗು_ಚೌಕಟ್ಟು);
    av_freep(&qsv_surface);
}

ಸ್ಥಿರ AVBufferRef *qsv_fixed_pool_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    ಆದರೆ (s->nb_surfaces_ಬಳಸಿದ < hwctx->nb_surfaces) {
        s->nb_surfaces_ಬಳಸಿದ++;
        ಹಿಂತಿರುಗಿ av_ಬಫರ್_create((uint8_t*)(s->surfaces_ಆಂತರಿಕ + s->nb_surfaces_ಬಳಸಿದ - 1),
                                ಗಾತ್ರ(*hwctx->surfaces), qsv_pool_release_dummy, ಖಾಲಿ, 0);
    }

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ AVBufferRef *qsv_dynamic_pool_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx;
    QSVSurface *qsv_surface = ಖಾಲಿ;
    mfxHDLPair *handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref)
        ಹೋಗು fail;

    ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx = (AVHWFramesContext*)s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref->ದತ್ತಾಂಶ;
    ಆದರೆ (!ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->device_ctx)
        ಹೋಗು fail;

#ಆದರೆ CONFIG_DXVA2
    ಆದರೆ (ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        ಹೋಗು fail;
    }
#ಆದರೆ_ಅಂತ್ಯ

    qsv_surface = av_calloc(1, ಗಾತ್ರ(*qsv_surface));
    ಆದರೆ (!qsv_surface)
        ಹೋಗು fail;

    qsv_surface->ಮಗು_ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!qsv_surface->ಮಗು_ಚೌಕಟ್ಟು)
        ಹೋಗು fail;

    ret = av_hwframe_get_ಬಫರ್(s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref, qsv_surface->ಮಗು_ಚೌಕಟ್ಟು, 0);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ = av_calloc(1, ಗಾತ್ರ(*handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ));
    ಆದರೆ (!handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ)
        ಹೋಗು fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

#ಆದರೆ CONFIG_VAAPI
    ಆದರೆ (ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_ಆಂತರಿಕ;

        surface_id_ಆಂತರಿಕ = av_calloc(1, ಗಾತ್ರ(*surface_id_ಆಂತರಿಕ));
        ಆದರೆ (!surface_id_ಆಂತರಿಕ)
            ಹೋಗು fail;

        *surface_id_ಆಂತರಿಕ = (VASurfaceID)(uintptr_t)qsv_surface->ಮಗು_ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[3];
        handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ->ಮೊದಲ = (mfxHDL)surface_id_ಆಂತರಿಕ;
        handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ->ಎರಡನೇ = (mfxMemId)MFX_INFINITE;
    }
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ CONFIG_D3D11VA
    ಆದರೆ (ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx = ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->hwctx;
        handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ->ಮೊದಲ = (mfxMemId)qsv_surface->ಮಗು_ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];

        ಆದರೆ (ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx->BindFlags & D3_D11_BIND_RENDER_ಗುರಿ)
            handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ->ಎರಡನೇ = (mfxMemId)MFX_INFINITE;
        ಇಲ್ಲದಿದ್ದರೆ
            handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ->ಎರಡನೇ = (mfxMemId)qsv_surface->ಮಗು_ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[1];

    }
#ಆದರೆ_ಅಂತ್ಯ

    qsv_surface->mfx_surface.ದತ್ತಾಂಶ_2.MemId = (mfxMemId)handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ;
    ಹಿಂತಿರುಗಿ av_ಬಫರ್_create((uint8_t *)qsv_surface, ಗಾತ್ರ(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    ಆದರೆ (qsv_surface) {
        av_ಚೌಕಟ್ಟು_free(&qsv_surface->ಮಗು_ಚೌಕಟ್ಟು);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ);

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ AVBufferRef *qsv_pool_alloc(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    ಆದರೆ (hwctx->nb_surfaces == 0) {
        ಹಿಂತಿರುಗಿ qsv_dynamic_pool_alloc(opaque, ಗಾತ್ರ_2);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ qsv_fixed_pool_alloc(opaque, ಗಾತ್ರ_2);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_init_ಮಗು_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *ಮಗು_device_ref = ಖಾಲಿ;
    AVBufferRef *ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref = ಖಾಲಿ;

    AVHWDeviceContext *ಮಗು_device_ctx;
    AVHWFramesContext *ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx;

    ಪೂರ್ಣಾಂಕ i, ret = 0;

    ಆದರೆ (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    ಮಗು_device_ref = av_hwdevice_ctx_alloc(device_priv->ಮಗು_device_type);
    ಆದರೆ (!ಮಗು_device_ref)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    ಮಗು_device_ctx   = (AVHWDeviceContext*)ಮಗು_device_ref->ದತ್ತಾಂಶ;

#ಆದರೆ CONFIG_VAAPI
    ಆದರೆ (ಮಗು_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *ಮಗು_device_hwctx = ಮಗು_device_ctx->hwctx;
        ಮಗು_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
    ಆದರೆ (ಮಗು_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *ಮಗು_device_hwctx = ಮಗು_device_ctx->hwctx;
        ID3_D11_Device_ಕೂಡಿಸು_Ref((ID3D11Device*)device_priv->handle);
        ಮಗು_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
    ಆದರೆ (ಮಗು_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *ಮಗು_device_hwctx = ಮಗು_device_ctx->hwctx;
        ಮಗು_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ret = av_hwdevice_ctx_init(ಮಗು_device_ref);
    ಆದರೆ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        ಹೋಗು fail;
    }

    ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref = av_hwframe_ctx_alloc(ಮಗು_device_ref);
    ಆದರೆ (!ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }
    ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx = (AVHWFramesContext*)ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref->ದತ್ತಾಂಶ;

    ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->format            = device_priv->ಮಗು_pix_fmt;
    ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->sw_format         = ctx->sw_format;
    ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->initial_pool_ಗಾತ್ರ = ctx->initial_pool_ಗಾತ್ರ;
    ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->ಅಗಲ             = FFALIGN(ctx->ಅಗಲ, 16);
    ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->ಎತ್ತರ            = FFALIGN(ctx->ಎತ್ತರ, 16);

#ಆದರೆ CONFIG_D3D11VA
    ಆದರೆ (ಮಗು_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx = ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->hwctx;
        ಆದರೆ (hwctx->ಚೌಕಟ್ಟು_type == 0)
            hwctx->ಚೌಕಟ್ಟು_type = MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_PROCESSOR_ಗುರಿ;
        ಆದರೆ (hwctx->ಚೌಕಟ್ಟು_type & MFX_MEMTYPE_SHARED_RESOURCE)
            ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->ಚೌಕಟ್ಟು_type);
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
    ಆದರೆ (ಮಗು_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_ಚೌಕಟ್ಟುಗಳು_Context *ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx = ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->hwctx;
        ಆದರೆ (hwctx->ಚೌಕಟ್ಟು_type & MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_PROCESSOR_ಗುರಿ)
            ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx->surface_type = DXVA2_Video_Processor_Render_ಗುರಿ;
        ಇಲ್ಲದಿದ್ದರೆ
            ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx->surface_type = DXVA2_Video_Decoder_Render_ಗುರಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ret = av_hwframe_ctx_init(ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref);
    ಆದರೆ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        ಹೋಗು fail;
    }

#ಆದರೆ CONFIG_VAAPI
    ಆದರೆ (ಮಗು_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx = ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->hwctx;
        ಗಾಗಿ (i = 0; i < ctx->initial_pool_ಗಾತ್ರ; i++) {
            s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಮೊದಲ = ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx->surface_ids + i;
            s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಎರಡನೇ = (mfxMemId)MFX_INFINITE;
            s->surfaces_ಆಂತರಿಕ[i].ದತ್ತಾಂಶ_2.MemId = (mfxMemId)&s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i];
        }
        hwctx->ಚೌಕಟ್ಟು_type = MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_DECODER_ಗುರಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
    ಆದರೆ (ಮಗು_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx = ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->hwctx;
        ಗಾಗಿ (i = 0; i < ctx->initial_pool_ಗಾತ್ರ; i++) {
            s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಮೊದಲ = (mfxMemId)ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx->texture_infos[i].texture;
            ಆದರೆ(ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx->BindFlags & D3_D11_BIND_RENDER_ಗುರಿ) {
                s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಎರಡನೇ = (mfxMemId)MFX_INFINITE;
            } ಇಲ್ಲದಿದ್ದರೆ {
                s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಎರಡನೇ = (mfxMemId)ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx->texture_infos[i].ಸೂಚ್ಯಂಕ;
            }
            s->surfaces_ಆಂತರಿಕ[i].ದತ್ತಾಂಶ_2.MemId = (mfxMemId)&s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i];
        }
        ಆದರೆ (ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx->BindFlags & D3_D11_BIND_RENDER_ಗುರಿ) {
            hwctx->ಚೌಕಟ್ಟು_type |= MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_PROCESSOR_ಗುರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            hwctx->ಚೌಕಟ್ಟು_type |= MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_DECODER_ಗುರಿ;
        }
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
    ಆದರೆ (ಮಗು_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_ಚೌಕಟ್ಟುಗಳು_Context *ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx = ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->hwctx;
        ಗಾಗಿ (i = 0; i < ctx->initial_pool_ಗಾತ್ರ; i++) {
            s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಮೊದಲ = (mfxMemId)ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx->surfaces[i];
            s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಎರಡನೇ = (mfxMemId)MFX_INFINITE;
            s->surfaces_ಆಂತರಿಕ[i].ದತ್ತಾಂಶ_2.MemId = (mfxMemId)&s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i];
        }
        ಆದರೆ (ಮಗು_ಚೌಕಟ್ಟುಗಳು_hwctx->surface_type == DXVA2_Video_Processor_Render_ಗುರಿ)
            hwctx->ಚೌಕಟ್ಟು_type = MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_PROCESSOR_ಗುರಿ;
        ಇಲ್ಲದಿದ್ದರೆ
            hwctx->ಚೌಕಟ್ಟು_type = MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_DECODER_ಗುರಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ

    s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref       = ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref;
    ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref          = ಖಾಲಿ;

fail:
    av_ಬಫರ್_unref(&ಮಗು_device_ref);
    av_ಬಫರ್_unref(&ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_init_surface(AVHWFramesContext *ctx, mfx_ಚೌಕಟ್ಟು_Surface1 *surf)
{
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    ಆದರೆ (!desc)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    ಆದರೆ (!fourcc)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    surf->Info.ಬಿಟ್_ಆಳ_Luma   = desc->comp[0].ಆಳ;
    surf->Info.ಬಿಟ್_ಆಳ_Chroma = desc->comp[0].ಆಳ;
    surf->Info.ಸರಿಸು_2          = qsv_ಸರಿಸು_from_pix_fmt(ctx->sw_format);

    ಆದರೆ (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    ಇಲ್ಲದಿದ್ದರೆ
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.ಅಗಲ_2          = FFALIGN(ctx->ಅಗಲ, 16);
    surf->Info.CropW          = ctx->ಅಗಲ;
    surf->Info.ಎತ್ತರ_2         = FFALIGN(ctx->ಎತ್ತರ, 16);
    surf->Info.CropH          = ctx->ಎತ್ತರ;
    surf->Info.ಚೌಕಟ್ಟು_ದರ_Ext_N  = 25;
    surf->Info.ಚೌಕಟ್ಟು_ದರ_Ext_D  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *ಚೌಕಟ್ಟುಗಳು_hwctx = &s->p;

    ಪೂರ್ಣಾಂಕ i, ret = 0;

    ಆದರೆ (ctx->initial_pool_ಗಾತ್ರ < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ctx->initial_pool_ಗಾತ್ರ == 0) {
        mfx_ಚೌಕಟ್ಟು_Surface1 mfx_surf1;

        ret = qsv_init_ಮಗು_ctx(ctx);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;

        ffhwframesctx(ctx)->pool_ಆಂತರಿಕ = av_ಬಫರ್_pool_init2(ಗಾತ್ರ(mfx_ಚೌಕಟ್ಟು_Surface1),
                                                                 ctx, qsv_pool_alloc, ಖಾಲಿ);
        ಆದರೆ (!ffhwframesctx(ctx)->pool_ಆಂತರಿಕ)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, ಗಾತ್ರ(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->ಚೌಕಟ್ಟು_info = mfx_surf1.Info;
        ಚೌಕಟ್ಟುಗಳು_hwctx->info = &s->ಚೌಕಟ್ಟು_info;
        ಚೌಕಟ್ಟುಗಳು_hwctx->nb_surfaces = 0;

        ಹಿಂತಿರುಗಿ 0;
    }

    s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ = av_calloc(ctx->initial_pool_ಗಾತ್ರ,
                                         ಗಾತ್ರ(*s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ));
    ಆದರೆ (!s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    s->surfaces_ಆಂತರಿಕ = av_calloc(ctx->initial_pool_ಗಾತ್ರ,
                                     ಗಾತ್ರ(*s->surfaces_ಆಂತರಿಕ));
    ಆದರೆ (!s->surfaces_ಆಂತರಿಕ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (i = 0; i < ctx->initial_pool_ಗಾತ್ರ; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_ಆಂತರಿಕ[i]);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
    }

#ಆದರೆ QSV_HAVE_OPAQUE
    ಆದರೆ (!(ಚೌಕಟ್ಟುಗಳು_hwctx->ಚೌಕಟ್ಟು_type & MFX_MEMTYPE_OPAQUE_ಚೌಕಟ್ಟು)) {
        ret = qsv_init_ಮಗು_ctx(ctx);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ret = qsv_init_ಮಗು_ctx(ctx);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;
#ಆದರೆ_ಅಂತ್ಯ

    ffhwframesctx(ctx)->pool_ಆಂತರಿಕ = av_ಬಫರ್_pool_init2(ಗಾತ್ರ(mfx_ಚೌಕಟ್ಟು_Surface1),
                                                             ctx, qsv_pool_alloc, ಖಾಲಿ);
    ಆದರೆ (!ffhwframesctx(ctx)->pool_ಆಂತರಿಕ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಚೌಕಟ್ಟುಗಳು_hwctx->surfaces    = s->surfaces_ಆಂತರಿಕ;
    ಚೌಕಟ್ಟುಗಳು_hwctx->nb_surfaces = ctx->initial_pool_ಗಾತ್ರ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ mfx_ಸ್ಥಿತಿ ಚೌಕಟ್ಟು_alloc(mfxHDL pthis, mfx_ಚೌಕಟ್ಟು_Alloc_Request *req,
                             mfx_ಚೌಕಟ್ಟು_Alloc_Response *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfx_ಚೌಕಟ್ಟು_Info *i  = &req->Info;
    mfx_ಚೌಕಟ್ಟು_Info *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    ಆದರೆ (!(req->Type & MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_PROCESSOR_ಗುರಿ) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_ಚೌಕಟ್ಟು))
        ಹಿಂತಿರುಗಿ MFX_ERR_UNSUPPORTED;
    ಆದರೆ (i->ಅಗಲ_2  > i1->ಅಗಲ_2 || i->ಎತ್ತರ_2 > i1->ಎತ್ತರ_2 ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->ಅಗಲ_2,  i->ಎತ್ತರ_2,  i->FourCC,  i->ChromaFormat,
               i1->ಅಗಲ_2, i1->ಎತ್ತರ_2, i1->FourCC, i1->ChromaFormat);
        ಹಿಂತಿರುಗಿ MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->ಅಂಕೆ_ಚೌಕಟ್ಟು_Actual = hwctx->nb_surfaces;

    ಹಿಂತಿರುಗಿ MFX_ERR_NONE;
}

ಸ್ಥಿರ mfx_ಸ್ಥಿತಿ ಚೌಕಟ್ಟು_free(mfxHDL pthis, mfx_ಚೌಕಟ್ಟು_Alloc_Response *resp)
{
    ಹಿಂತಿರುಗಿ MFX_ERR_NONE;
}

ಸ್ಥಿರ mfx_ಸ್ಥಿತಿ ಚೌಕಟ್ಟು_ಬೀಗ(mfxHDL pthis, mfxMemId mid, mfx_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ *ptr)
{
    ಹಿಂತಿರುಗಿ MFX_ERR_UNSUPPORTED;
}

ಸ್ಥಿರ mfx_ಸ್ಥಿತಿ ಚೌಕಟ್ಟು_unlock(mfxHDL pthis, mfxMemId mid, mfx_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ *ptr)
{
    ಹಿಂತಿರುಗಿ MFX_ERR_UNSUPPORTED;
}

ಸ್ಥಿರ mfx_ಸ್ಥಿತಿ ಚೌಕಟ್ಟು_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->ಮೊದಲ = pair_src->ಮೊದಲ;

    ಆದರೆ (pair_src->ಎರಡನೇ != (mfxMemId)MFX_INFINITE)
        pair_dst->ಎರಡನೇ = pair_src->ಎರಡನೇ;
    ಹಿಂತಿರುಗಿ MFX_ERR_NONE;
}

#ಆದರೆ QSV_ONEVPL

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_d3d11_update_config(ಶೂನ್ಯ *ctx, mfxHDL handle, mfxConfig cfg)
{
    ಪೂರ್ಣಾಂಕ ret = AVERROR_UNKNOWN;
#ಆದರೆ CONFIG_D3D11VA
    mfx_ಸ್ಥಿತಿ sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = ಖಾಲಿ;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_ಮೌಲ್ಯ = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (ಶೂನ್ಯ**)&pDXGIDevice);
    ಆದರೆ (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        ಆದರೆ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            ಹಿಂತಿರುಗಿ ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        ಆದರೆ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            ಹೋಗು fail;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        ಹಿಂತಿರುಗಿ ret;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U16;
    impl_ಮೌಲ್ಯ.ದತ್ತಾಂಶ_2.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಸ್ಥಿರಾಂಕ mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_ಮೌಲ್ಯ);
    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        ಹೋಗು fail;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_PTR;
    impl_ಮೌಲ್ಯ.ದತ್ತಾಂಶ_2.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಸ್ಥಿರಾಂಕ mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_ಮೌಲ್ಯ);
    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        ಹೋಗು fail;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U32;
    impl_ಮೌಲ್ಯ.ದತ್ತಾಂಶ_2.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಸ್ಥಿರಾಂಕ mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_ಮೌಲ್ಯ);
    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        ಹೋಗು fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_d3d9_update_config(ಶೂನ್ಯ *ctx, mfxHDL handle, mfxConfig cfg)
{
    ಪೂರ್ಣಾಂಕ ret = AVERROR_UNKNOWN;
#ಆದರೆ CONFIG_DXVA2
    mfx_ಸ್ಥಿತಿ sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = ಖಾಲಿ;
    IDirect3DDevice9Ex *device_ex = ಖಾಲಿ;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = ಖಾಲಿ;
    IDirect3D9 *d3d9 = ಖಾಲಿ;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_ಮೌಲ್ಯ = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        ಹೋಗು fail;
    }

    hr = IDirect3_DDevice_Manager9_ಬೀಗ_Device(devmgr, device_handle, &device, TRUE);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        ಹೋಗು fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (ಶೂನ್ಯ **)&device_ex);
    IDirect3DDevice9_Release(device);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        ಹೋಗು unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        ಹೋಗು unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        ಹೋಗು unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (ಶೂನ್ಯ **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        ಹೋಗು unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    ಆದರೆ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        ಹೋಗು release;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_PTR;
    impl_ಮೌಲ್ಯ.ದತ್ತಾಂಶ_2.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಸ್ಥಿರಾಂಕ mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_ಮೌಲ್ಯ);
    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        ಹೋಗು release;
    }

    ret = 0;

release:
    IDirect3D9Ex_Release(d3d9ex);
    IDirect3DDevice9Ex_Release(device_ex);

unlock:
    IDirect3DDeviceManager9_UnlockDevice(devmgr, device_handle, FALSE);
    IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
fail:
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_va_update_config(ಶೂನ್ಯ *ctx, mfxHDL handle, mfxConfig cfg)
{
#ಆದರೆ CONFIG_VAAPI
#ಆದರೆ VA_CHECK_ಆವೃತ್ತಿ(1, 15, 0)
    mfx_ಸ್ಥಿತಿ sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_ಮೌಲ್ಯ = {0};

    vas = va_Get_Display_ಗುಣಲಕ್ಷಣಗಳು(dpy, &attr, 1);
    ಆದರೆ (vas == VA_ಸ್ಥಿತಿ_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U16;
        impl_ಮೌಲ್ಯ.ದತ್ತಾಂಶ_2.U16 = (attr.ಮೌಲ್ಯ & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ಸ್ಥಿರಾಂಕ mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_ಮೌಲ್ಯ);
        ಆದರೆ (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            ಹೋಗು fail;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        ಹೋಗು fail;
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
#ಇಲ್ಲದಿದ್ದರೆ
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_new_mfx_loader(ಶೂನ್ಯ *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfx_ಆವೃತ್ತಿ *pver,
                              ಶೂನ್ಯ **ploader)
{
    mfx_ಸ್ಥಿತಿ sts;
    mfxLoader loader = ಖಾಲಿ;
    mfxConfig cfg;
    mfxVariant impl_ಮೌಲ್ಯ = {0};

    *ploader = ಖಾಲಿ;
    loader = MFXLoad();
    ಆದರೆ (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        ಹೋಗು fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    ಆದರೆ (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        ಹೋಗು fail;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U32;
    impl_ಮೌಲ್ಯ.ದತ್ತಾಂಶ_2.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಸ್ಥಿರಾಂಕ mfxU8 *)"mfxImplDescription.Impl", impl_ಮೌಲ್ಯ);
    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        ಹೋಗು fail;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U32;
    impl_ಮೌಲ್ಯ.ದತ್ತಾಂಶ_2.U32 = pver->ಆವೃತ್ತಿ_2;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಸ್ಥಿರಾಂಕ mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_ಮೌಲ್ಯ);
    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        ಹೋಗು fail;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U32;
    impl_ಮೌಲ್ಯ.ದತ್ತಾಂಶ_2.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಸ್ಥಿರಾಂಕ mfxU8 *)"mfxImplDescription.VendorID", impl_ಮೌಲ್ಯ);
    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        ಹೋಗು fail;
    }

    ಆದರೆ (MFX_HANDLE_VA_DISPLAY == handle_type) {
        ಆದರೆ (handle && qsv_va_update_config(ctx, handle, cfg))
            ಹೋಗು fail;

        impl_ಮೌಲ್ಯ.ದತ್ತಾಂಶ_2.U32 = MFX_ACCEL_ಬಹುಲಕ_ಮೂಲಕ_VAAPI;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        ಆದರೆ (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            ಹೋಗು fail;

        impl_ಮೌಲ್ಯ.ದತ್ತಾಂಶ_2.U32 = MFX_ACCEL_ಬಹುಲಕ_ಮೂಲಕ_D3_D9;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            ಹೋಗು fail;

        impl_ಮೌಲ್ಯ.ದತ್ತಾಂಶ_2.U32 = MFX_ACCEL_ಬಹುಲಕ_ಮೂಲಕ_D3_D11;
    }

    impl_ಮೌಲ್ಯ.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ಸ್ಥಿರಾಂಕ mfxU8 *)"mfxImplDescription.AccelerationMode", impl_ಮೌಲ್ಯ);
    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        ಹೋಗು fail;
    }

    *ploader = loader;

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಆದರೆ (loader)
        MFXUnload(loader);

    ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_create_mfx_session_from_loader(ಶೂನ್ಯ *ctx, mfxLoader loader, mfxSession *psession)
{
    mfx_ಸ್ಥಿತಿ sts;
    mfxSession session = ಖಾಲಿ;
    uint32_t impl_idx = 0;
    mfx_ಆವೃತ್ತಿ ver;

    ಆಗ (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        ಆದರೆ (sts == MFX_ERR_NOT_ಸಿಕ್ಕಿತು)
            ನಿಲ್ಲಿಸು;
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (sts != MFX_ERR_NONE) {
            impl_idx++;
            ಮುಂದುವರಿ;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        ಆದರೆ (sts == MFX_ERR_NONE)
            ನಿಲ್ಲಿಸು;

        impl_idx++;
    }

    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        ಹೋಗು fail;
    }

    sts = MFXQuery_ಆವೃತ್ತಿ(session, &ver);
    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        ಹೋಗು fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಆದರೆ (session)
        MFXClose(session);

    ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_create_mfx_session(ಶೂನ್ಯ *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfx_ಆವೃತ್ತಿ *pver,
                                  mfxSession *psession,
                                  ಶೂನ್ಯ **ploader)
{
    mfxLoader loader = ಖಾಲಿ;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_ಆವೃತ್ತಿ_MAJOR, MFX_ಆವೃತ್ತಿ_MINOR, pver->Major, pver->Minor);

    ಆದರೆ (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        ಹಿಂತಿರುಗಿ AVERROR(EXDEV);
    }

    *psession = ಖಾಲಿ;

    ಆದರೆ (!*ploader) {
        ಆದರೆ (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (ಶೂನ್ಯ **)&loader))
            ಹೋಗು fail;

        av_assert0(loader);
    } ಇಲ್ಲದಿದ್ದರೆ
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    ಆದರೆ (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        ಹೋಗು fail;

    ಆದರೆ (!*ploader)
        *ploader = loader;

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಆದರೆ (!*ploader && loader)
        MFXUnload(loader);

    ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
}

#ಇಲ್ಲದಿದ್ದರೆ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_create_mfx_session(ಶೂನ್ಯ *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfx_ಆವೃತ್ತಿ *pver,
                                  mfxSession *psession,
                                  ಶೂನ್ಯ **ploader)
{
    mfx_ಆವೃತ್ತಿ ver;
    mfx_ಸ್ಥಿತಿ sts;
    mfxSession session = ಖಾಲಿ;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_ಆವೃತ್ತಿ_MAJOR, MFX_ಆವೃತ್ತಿ_MINOR, pver->Major, pver->Minor);

    *ploader = ಖಾಲಿ;
    *psession = ಖಾಲಿ;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        ಹೋಗು fail;
    }

    sts = MFXQuery_ಆವೃತ್ತಿ(session, &ver);
    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        ಹೋಗು fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    ಆದರೆ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        ಹೋಗು fail;
    }

    *psession = session;

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಆದರೆ (session)
        MFXClose(session);

    ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
}

#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_init_ಆಂತರಿಕ_session(AVHWFramesContext *ctx,
                                     mfxSession *session, ಪೂರ್ಣಾಂಕ upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *ಚೌಕಟ್ಟುಗಳು_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    ಪೂರ್ಣಾಂಕ opaque = 0;

    mfx_ಚೌಕಟ್ಟು_Allocator ಚೌಕಟ್ಟು_allocator = {
        .pthis  = ctx,
        .Alloc  = ಚೌಕಟ್ಟು_alloc,
        .ಬೀಗ_3   = ಚೌಕಟ್ಟು_ಬೀಗ,
        .Unlock = ಚೌಕಟ್ಟು_unlock,
        .GetHDL = ಚೌಕಟ್ಟು_get_hdl,
        .Free   = ಚೌಕಟ್ಟು_free,
    };

    mfxVideoParam par;
    mfx_ಸ್ಥಿತಿ err;
    ಪೂರ್ಣಾಂಕ                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    ಶೂನ್ಯ             **loader = &hwctx->loader;
    mfxSession ಪೋಷಕ_session = hwctx->session;
    mfxIMPL impl;
    mfx_ಆವೃತ್ತಿ ver;

    err = MFXQueryIMPL(ಪೋಷಕ_session, &impl);
    ಆದರೆ (err == MFX_ERR_NONE)
        err = MFXQuery_ಆವೃತ್ತಿ(ಪೋಷಕ_session, &ver);
    ಆದರೆ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

#ಆದರೆ QSV_HAVE_OPAQUE
    opaque = !!(ಚೌಕಟ್ಟುಗಳು_hwctx->ಚೌಕಟ್ಟು_type & MFX_MEMTYPE_OPAQUE_ಚೌಕಟ್ಟು);
#ಆದರೆ_ಅಂತ್ಯ

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    ಆದರೆ (ret)
        ಹೋಗು fail;

    ಆದರೆ (device_priv->handle) {
        err = MFXVideo_CORE_ಗಣ_Handle(*session, device_priv->handle_type,
                                     device_priv->handle);
        ಆದರೆ (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            ಹೋಗು fail;
        }
    }

    ಆದರೆ (QSV_RUNTIME_ಆವೃತ್ತಿ_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(ಪೋಷಕ_session, *session);
        ಆದರೆ (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            ಹೋಗು fail;
        }
    }

    ಆದರೆ (!opaque) {
        err = MFXVideo_CORE_ಗಣ_ಚೌಕಟ್ಟು_Allocator(*session, &ಚೌಕಟ್ಟು_allocator);
        ಆದರೆ (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            ಹೋಗು fail;
        }
    }

    memset(&par, 0, ಗಾತ್ರ(par));

    ಆದರೆ (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_ಹೊರಹೋಗು_VIDEO_ಸ್ಮರಣೆ :
                                 MFX_IOPATTERN_ಒಳ_VIDEO_ಸ್ಮರಣೆ;
    }
#ಆದರೆ QSV_HAVE_OPAQUE
    ಇಲ್ಲದಿದ್ದರೆ {
        par.ExtParam    = s->ext_buffers;
        par.ಅಂಕೆ_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
        par.IOPattern   = upload ? MFX_IOPATTERN_ಹೊರಹೋಗು_OPAQUE_ಸ್ಮರಣೆ :
                                   MFX_IOPATTERN_ಒಳ_OPAQUE_ಸ್ಮರಣೆ;
    }
#ಆದರೆ_ಅಂತ್ಯ

    par.IOPattern |= upload ? MFX_IOPATTERN_ಒಳ_SYSTEM_ಸ್ಮರಣೆ :
                              MFX_IOPATTERN_ಹೊರಹೋಗು_SYSTEM_ಸ್ಮರಣೆ;
    par.Async_ಆಳ = 1;

    par.vpp.ಒಳ_2 = ಚೌಕಟ್ಟುಗಳು_hwctx->nb_surfaces ? ಚೌಕಟ್ಟುಗಳು_hwctx->surfaces[0].Info : *ಚೌಕಟ್ಟುಗಳು_hwctx->info;

    /* Apparently VPP requires the frame rate to be set to some value, otherwise
     * init will fail (probably for the framerate conversion filter). Since we
     * are only doing data upload/download here, we just invent an arbitrary
     * value */
    par.vpp.ಒಳ_2.ಚೌಕಟ್ಟು_ದರ_Ext_N = 25;
    par.vpp.ಒಳ_2.ಚೌಕಟ್ಟು_ದರ_Ext_D = 1;
    par.vpp.ಹೊರಹೋಗು_2 = par.vpp.ಒಳ_2;

    err = MFXVideoVPP_Init(*session, &par);
    ಆದರೆ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        ಹೋಗು fail;
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಆದರೆ (*session)
        MFXClose(*session);

    *session = ಖಾಲಿ;

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_ಚೌಕಟ್ಟುಗಳು_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *ಚೌಕಟ್ಟುಗಳು_hwctx = &s->p;

    ಪೂರ್ಣಾಂಕ opaque = 0;

    uint32_t fourcc;
    ಪೂರ್ಣಾಂಕ i, ret;

#ಆದರೆ QSV_HAVE_OPAQUE
    opaque = !!(ಚೌಕಟ್ಟುಗಳು_hwctx->ಚೌಕಟ್ಟು_type & MFX_MEMTYPE_OPAQUE_ಚೌಕಟ್ಟು);
#ಆದರೆ_ಅಂತ್ಯ

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    ಆದರೆ (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    ಆದರೆ (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        ಆದರೆ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            ಹಿಂತಿರುಗಿ ret;
        }
    }

    ಆದರೆ (!opaque) {
        s->mem_ids = av_calloc(ಚೌಕಟ್ಟುಗಳು_hwctx->nb_surfaces, ಗಾತ್ರ(*s->mem_ids));
        ಆದರೆ (!s->mem_ids)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        ಗಾಗಿ (i = 0; i < ಚೌಕಟ್ಟುಗಳು_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = ಚೌಕಟ್ಟುಗಳು_hwctx->surfaces[i].ದತ್ತಾಂಶ_2.MemId;
    }
#ಆದರೆ QSV_HAVE_OPAQUE
    ಇಲ್ಲದಿದ್ದರೆ {
        s->surface_ptrs = av_calloc(ಚೌಕಟ್ಟುಗಳು_hwctx->nb_surfaces,
                                    ಗಾತ್ರ(*s->surface_ptrs));
        ಆದರೆ (!s->surface_ptrs)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        ಗಾಗಿ (i = 0; i < ಚೌಕಟ್ಟುಗಳು_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = ಚೌಕಟ್ಟುಗಳು_hwctx->surfaces + i;

        s->opaque_alloc.ಒಳ_2.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.ಒಳ_2.ಅಂಕೆ_Surface = ಚೌಕಟ್ಟುಗಳು_hwctx->nb_surfaces;
        s->opaque_alloc.ಒಳ_2.Type       = ಚೌಕಟ್ಟುಗಳು_hwctx->ಚೌಕಟ್ಟು_type;

        s->opaque_alloc.ಹೊರಹೋಗು_2 = s->opaque_alloc.ಒಳ_2;

        s->opaque_alloc.ಶೀರ್ಷಿಕೆ_2.ಬಫರ್_Id = MFX_EXTBUFF_OPAQUE_SURFACE_ಹಂಚಿಕೆ;
        s->opaque_alloc.ಶೀರ್ಷಿಕೆ_2.ಬಫರ್_Sz = ಗಾತ್ರ(s->opaque_alloc);

        s->ext_buffers[0] = (mfx_Ext_ಬಫರ್*)&s->opaque_alloc;
    }
#ಆದರೆ_ಅಂತ್ಯ

    s->session_download = ಖಾಲಿ;
    s->session_upload   = ಖಾಲಿ;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#ಆದರೆ HAVE_PTHREADS
    pthread_mutex_init(&s->session_ಬೀಗ, ಖಾಲಿ);
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_get_ಬಫರ್(AVHWFramesContext *ctx, AVFrame *ಚೌಕಟ್ಟು)
{
    ಚೌಕಟ್ಟು->buf[0] = av_ಬಫರ್_pool_get(ctx->pool);
    ಆದರೆ (!ಚೌಕಟ್ಟು->buf[0])
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[3] = ಚೌಕಟ್ಟು->buf[0]->ದತ್ತಾಂಶ;
    ಚೌಕಟ್ಟು->format  = AV_PIX_FMT_QSV;
    ಚೌಕಟ್ಟು->ಅಗಲ   = ctx->ಅಗಲ;
    ಚೌಕಟ್ಟು->ಎತ್ತರ  = ctx->ಎತ್ತರ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    ಎಣಿಕೆ AVHWFrameTransferDirection dir,
                                    ಎಣಿಕೆ AVPixelFormat **formats)
{
    ಎಣಿಕೆ AVPixelFormat *fmts;

    fmts = av_malloc_array(2, ಗಾತ್ರ(*fmts));
    ಆದರೆ (!fmts)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_ಚೌಕಟ್ಟುಗಳು_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, ಪೂರ್ಣಾಂಕ flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    ಪೂರ್ಣಾಂಕ i;

    ಆಯ್ಕೆ (dst_ctx->device_ctx->type) {
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               ಗಾತ್ರ(*dst_hwctx->surface_ids));
            ಆದರೆ (!dst_hwctx->surface_ids)
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            ಗಾಗಿ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].ದತ್ತಾಂಶ_2.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->ಮೊದಲ;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_ಗಾತ್ರ = src_ctx->initial_pool_ಗಾತ್ರ;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 ಗಾತ್ರ(*dst_hwctx->texture_infos));
            ಆದರೆ (!dst_hwctx->texture_infos)
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            ಆದರೆ (src_hwctx->ಚೌಕಟ್ಟು_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            ಗಾಗಿ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].ದತ್ತಾಂಶ_2.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->ಮೊದಲ;
                dst_hwctx->texture_infos[i].ಸೂಚ್ಯಂಕ = pair->ಎರಡನೇ == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->ಎರಡನೇ;
            }
            ಆದರೆ (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } ಇಲ್ಲದಿದ್ದರೆ
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->ಚೌಕಟ್ಟು_type);
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_ಚೌಕಟ್ಟುಗಳು_Context *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            ಗಾತ್ರ(*dst_hwctx->surfaces));
            ಆದರೆ (!dst_hwctx->surfaces)
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            ಗಾಗಿ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].ದತ್ತಾಂಶ_2.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->ಮೊದಲ;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            ಆದರೆ (src_hwctx->ಚೌಕಟ್ಟು_type == MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_DECODER_ಗುರಿ)
                dst_hwctx->surface_type = DXVA2_Video_Decoder_Render_ಗುರಿ;
            ಇಲ್ಲದಿದ್ದರೆ
                dst_hwctx->surface_type = DXVA2_Video_Processor_Render_ಗುರಿ;
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfx_ಚೌಕಟ್ಟು_Surface1 *surf = (mfx_ಚೌಕಟ್ಟು_Surface1*)src->ದತ್ತಾಂಶ[3];
    AVHWFramesContext *ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx;
    ಸ್ಥಿರಾಂಕ AVPixFmtDescriptor *desc;
    uint8_t *ಮಗು_ದತ್ತಾಂಶ;
    AVFrame *dummy;
    ಪೂರ್ಣಾಂಕ ret = 0;

    ಆದರೆ (!s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref)
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx = (AVHWFramesContext*)s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref->ದತ್ತಾಂಶ;

    ಆಯ್ಕೆ (ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->device_ctx->type) {
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->ದತ್ತಾಂಶ_2.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        ಮಗು_ದತ್ತಾಂಶ = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->ಮೊದಲ;
        ನಿಲ್ಲಿಸು;
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->ದತ್ತಾಂಶ_2.MemId;
        ಮಗು_ದತ್ತಾಂಶ = pair->ಮೊದಲ;
        ನಿಲ್ಲಿಸು;
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->ದತ್ತಾಂಶ_2.MemId;
        ಮಗು_ದತ್ತಾಂಶ = pair->ಮೊದಲ;
        ನಿಲ್ಲಿಸು;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    ಆದರೆ (dst->format == ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->format) {
        ret = ff_hwframe_map_create(s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref,
                                    dst, src, ಖಾಲಿ, ಖಾಲಿ);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;

        dst->ಅಗಲ   = src->ಅಗಲ;
        dst->ಎತ್ತರ  = src->ಎತ್ತರ;

       ಆದರೆ (ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->ದತ್ತಾಂಶ_2.MemId;
            dst->ದತ್ತಾಂಶ[0] = pair->ಮೊದಲ;
            dst->ದತ್ತಾಂಶ[1] = pair->ಎರಡನೇ == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->ಎರಡನೇ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dst->ದತ್ತಾಂಶ[3] = ಮಗು_ದತ್ತಾಂಶ;
        }

        ಹಿಂತಿರುಗಿ 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    ಆದರೆ (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    dummy = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!dummy)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    dummy->buf[0]        = av_ಬಫರ್_ref(src->buf[0]);
    dummy->hw_ಚೌಕಟ್ಟುಗಳು_ctx = av_ಬಫರ್_ref(s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref);
    ಆದರೆ (!dummy->buf[0] || !dummy->hw_ಚೌಕಟ್ಟುಗಳು_ctx)
        ಹೋಗು fail;

    dummy->format        = ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->format;
    dummy->ಅಗಲ         = src->ಅಗಲ;
    dummy->ಎತ್ತರ        = src->ಎತ್ತರ;

    ಆದರೆ (ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->ದತ್ತಾಂಶ_2.MemId;
        dummy->ದತ್ತಾಂಶ[0] = pair->ಮೊದಲ;
        dummy->ದತ್ತಾಂಶ[1] = pair->ಎರಡನೇ == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->ಎರಡನೇ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        dummy->ದತ್ತಾಂಶ[3] = ಮಗು_ದತ್ತಾಂಶ;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_ಚೌಕಟ್ಟು_free(&dummy);

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_transfer_ದತ್ತಾಂಶ_ಮಗು(AVHWFramesContext *ctx, AVFrame *dst,
                                   ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx = (AVHWFramesContext*)s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref->ದತ್ತಾಂಶ;
    ಪೂರ್ಣಾಂಕ download = !!src->hw_ಚೌಕಟ್ಟುಗಳು_ctx;
    mfx_ಚೌಕಟ್ಟು_Surface1 *surf = (mfx_ಚೌಕಟ್ಟು_Surface1*)(download ? src->ದತ್ತಾಂಶ[3] : dst->ದತ್ತಾಂಶ[3]);

    AVFrame *dummy;
    ಪೂರ್ಣಾಂಕ ret;

    dummy = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (!dummy)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    dummy->format        = ಮಗು_ಚೌಕಟ್ಟುಗಳು_ctx->format;
    dummy->ಅಗಲ         = src->ಅಗಲ;
    dummy->ಎತ್ತರ        = src->ಎತ್ತರ;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->ದತ್ತಾಂಶ[3]       = surf->ದತ್ತಾಂಶ_2.MemId;
    dummy->hw_ಚೌಕಟ್ಟುಗಳು_ctx = s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref;

    ret = download ? av_hwframe_transfer_ದತ್ತಾಂಶ(dst, dummy, 0) :
                     av_hwframe_transfer_ದತ್ತಾಂಶ(dummy, src, 0);

    dummy->buf[0]        = ಖಾಲಿ;
    dummy->ದತ್ತಾಂಶ[3]       = ಖಾಲಿ;
    dummy->hw_ಚೌಕಟ್ಟುಗಳು_ctx = ಖಾಲಿ;

    av_ಚೌಕಟ್ಟು_free(&dummy);

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ map_ಚೌಕಟ್ಟು_ಗಮ್ಯ_surface(ಸ್ಥಿರಾಂಕ AVFrame *ಚೌಕಟ್ಟು, mfx_ಚೌಕಟ್ಟು_Surface1 *surface)
{
    ಆಯ್ಕೆ (ಚೌಕಟ್ಟು->format) {
    ಸ್ಥಿತಿ AV_PIX_FMT_NV12:
    ಸ್ಥಿತಿ AV_PIX_FMT_P010:
    ಸ್ಥಿತಿ AV_PIX_FMT_P012:
        surface->ದತ್ತಾಂಶ_2.Y  = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];
        surface->ದತ್ತಾಂಶ_2.UV = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[1];
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ AV_PIX_FMT_YUV420P:
        surface->ದತ್ತಾಂಶ_2.Y = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];
        surface->ದತ್ತಾಂಶ_2.U = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[1];
        surface->ದತ್ತಾಂಶ_2.V = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[2];
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ AV_PIX_FMT_BGRA:
        surface->ದತ್ತಾಂಶ_2.B = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];
        surface->ದತ್ತಾಂಶ_2.G = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 1;
        surface->ದತ್ತಾಂಶ_2.R = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 2;
        surface->ದತ್ತಾಂಶ_2.A = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 3;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_PIX_FMT_YUYV422:
        surface->ದತ್ತಾಂಶ_2.Y = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];
        surface->ದತ್ತಾಂಶ_2.U = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 1;
        surface->ದತ್ತಾಂಶ_2.V = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 3;
        ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ AV_PIX_FMT_Y210:
    ಸ್ಥಿತಿ AV_PIX_FMT_Y212:
        surface->ದತ್ತಾಂಶ_2.Y16 = (mfxU16 *)ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];
        surface->ದತ್ತಾಂಶ_2.U16 = (mfxU16 *)ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 1;
        surface->ದತ್ತಾಂಶ_2.V16 = (mfxU16 *)ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 3;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_PIX_FMT_VUYX:
        surface->ದತ್ತಾಂಶ_2.V = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];
        surface->ದತ್ತಾಂಶ_2.U = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 1;
        surface->ದತ್ತಾಂಶ_2.Y = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->ದತ್ತಾಂಶ_2.A = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 3;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_PIX_FMT_XV30:
        surface->ದತ್ತಾಂಶ_2.U = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_PIX_FMT_XV36:
        surface->ದತ್ತಾಂಶ_2.U = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];
        surface->ದತ್ತಾಂಶ_2.Y = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 2;
        surface->ದತ್ತಾಂಶ_2.V = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->ದತ್ತಾಂಶ_2.A = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 6;
        ನಿಲ್ಲಿಸು;
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_PIX_FMT_UYVY422:
        surface->ದತ್ತಾಂಶ_2.Y = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 1;
        surface->ದತ್ತಾಂಶ_2.U = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0];
        surface->ದತ್ತಾಂಶ_2.V = ಚೌಕಟ್ಟು->ದತ್ತಾಂಶ[0] + 2;
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ MFX_ERR_UNSUPPORTED;
    }
    surface->ದತ್ತಾಂಶ_2.Pitch     = ಚೌಕಟ್ಟು->linesize[0];
    surface->ದತ್ತಾಂಶ_2.ಸಮಯ_Stamp = ಚೌಕಟ್ಟು->pts;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_ಆಂತರಿಕ_session_check_init(AVHWFramesContext *ctx, ಪೂರ್ಣಾಂಕ upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    ಪೂರ್ಣಾಂಕ ret = 0;

    ಆದರೆ (atomic_load(inited))
        ಹಿಂತಿರುಗಿ 0;

#ಆದರೆ HAVE_PTHREADS
    pthread_mutex_ಬೀಗ(&s->session_ಬೀಗ);
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!atomic_load(inited)) {
        ret = qsv_init_ಆಂತರಿಕ_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#ಆದರೆ HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_ಬೀಗ);
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_transfer_ದತ್ತಾಂಶ_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfx_ಚೌಕಟ್ಟು_Surface1 ಹೊರಹೋಗು = {{ 0 }};
    mfx_ಚೌಕಟ್ಟು_Surface1 *ಒಳ = (mfx_ಚೌಕಟ್ಟು_Surface1*)src->ದತ್ತಾಂಶ[3];

    mfx_Sync_ಬಿಂದು sync = ಖಾಲಿ;
    mfx_ಸ್ಥಿತಿ err;
    ಪೂರ್ಣಾಂಕ ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_ಚೌಕಟ್ಟು = &s->realigned_download_ಚೌಕಟ್ಟು;
    AVFrame *dst_ಚೌಕಟ್ಟು;
    ಪೂರ್ಣಾಂಕ realigned = 0;

    ret = qsv_ಆಂತರಿಕ_session_check_init(ctx, 0);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    ಆದರೆ (dst->ಎತ್ತರ & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        ಆದರೆ (tmp_ಚೌಕಟ್ಟು->format != dst->format ||
            tmp_ಚೌಕಟ್ಟು->ಅಗಲ  != FFALIGN(dst->linesize[0], 16) ||
            tmp_ಚೌಕಟ್ಟು->ಎತ್ತರ != FFALIGN(dst->ಎತ್ತರ, 16)) {
            av_ಚೌಕಟ್ಟು_unref(tmp_ಚೌಕಟ್ಟು);

            tmp_ಚೌಕಟ್ಟು->format = dst->format;
            tmp_ಚೌಕಟ್ಟು->ಅಗಲ  = FFALIGN(dst->linesize[0], 16);
            tmp_ಚೌಕಟ್ಟು->ಎತ್ತರ = FFALIGN(dst->ಎತ್ತರ, 16);
            ret = av_ಚೌಕಟ್ಟು_get_ಬಫರ್(tmp_ಚೌಕಟ್ಟು, 0);
            ಆದರೆ (ret < 0)
                ಹಿಂತಿರುಗಿ ret;
        }
    }

    dst_ಚೌಕಟ್ಟು = realigned ? tmp_ಚೌಕಟ್ಟು : dst;

    ಆದರೆ (!s->session_download) {
        ಆದರೆ (s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref)
            ಹಿಂತಿರುಗಿ qsv_transfer_ದತ್ತಾಂಶ_ಮಗು(ctx, dst_ಚೌಕಟ್ಟು, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    ಹೊರಹೋಗು.Info = ಒಳ->Info;
    map_ಚೌಕಟ್ಟು_ಗಮ್ಯ_surface(dst_ಚೌಕಟ್ಟು, &ಹೊರಹೋಗು);

    ಮಾಡು {
        err = MFXVideo_VPP_ಸತತ_ಚೌಕಟ್ಟು_VPPAsync(s->session_download, ಒಳ, &ಹೊರಹೋಗು, ಖಾಲಿ, &sync);
        ಆದರೆ (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } ಆಗ (err == MFX_WRN_DEVICE_BUSY);

    ಆದರೆ (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಮಾಡು {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } ಆಗ (err == MFX_WRN_ಒಳ_EXECUTION);
    ಆದರೆ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಆದರೆ (realigned) {
        tmp_ಚೌಕಟ್ಟು->ಅಗಲ  = dst->ಅಗಲ;
        tmp_ಚೌಕಟ್ಟು->ಎತ್ತರ = dst->ಎತ್ತರ;
        ret = av_ಚೌಕಟ್ಟು_copy(dst, tmp_ಚೌಕಟ್ಟು);
        tmp_ಚೌಕಟ್ಟು->ಅಗಲ  = FFALIGN(dst->linesize[0], 16);
        tmp_ಚೌಕಟ್ಟು->ಎತ್ತರ = FFALIGN(dst->ಎತ್ತರ, 16);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ(AVHWFramesContext *ctx, AVFrame *dst,
                                ಸ್ಥಿರಾಂಕ AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfx_ಚೌಕಟ್ಟು_Surface1   ಒಳ = {{ 0 }};
    mfx_ಚೌಕಟ್ಟು_Surface1 *ಹೊರಹೋಗು = (mfx_ಚೌಕಟ್ಟು_Surface1*)dst->ದತ್ತಾಂಶ[3];
    mfx_ಚೌಕಟ್ಟು_Info tmp_info;

    mfx_Sync_ಬಿಂದು sync = ಖಾಲಿ;
    mfx_ಸ್ಥಿತಿ err;
    ಪೂರ್ಣಾಂಕ ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_ಚೌಕಟ್ಟು = &s->realigned_upload_ಚೌಕಟ್ಟು;
    ಸ್ಥಿರಾಂಕ AVFrame *src_ಚೌಕಟ್ಟು;
    ಪೂರ್ಣಾಂಕ realigned = 0;

    ret = qsv_ಆಂತರಿಕ_session_check_init(ctx, 1);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    ಆದರೆ (src->ಎತ್ತರ & 15 || src->linesize[0] & 15) {
        realigned = 1;
        ಆದರೆ (tmp_ಚೌಕಟ್ಟು->format != src->format ||
            tmp_ಚೌಕಟ್ಟು->ಅಗಲ  != FFALIGN(src->ಅಗಲ, 16) ||
            tmp_ಚೌಕಟ್ಟು->ಎತ್ತರ != FFALIGN(src->ಎತ್ತರ, 16)) {
            av_ಚೌಕಟ್ಟು_unref(tmp_ಚೌಕಟ್ಟು);

            tmp_ಚೌಕಟ್ಟು->format = src->format;
            tmp_ಚೌಕಟ್ಟು->ಅಗಲ  = FFALIGN(src->ಅಗಲ, 16);
            tmp_ಚೌಕಟ್ಟು->ಎತ್ತರ = FFALIGN(src->ಎತ್ತರ, 16);
            ret = av_ಚೌಕಟ್ಟು_get_ಬಫರ್(tmp_ಚೌಕಟ್ಟು, 0);
            ಆದರೆ (ret < 0)
                ಹಿಂತಿರುಗಿ ret;
        }
        ret = av_ಚೌಕಟ್ಟು_copy(tmp_ಚೌಕಟ್ಟು, src);
        ಆದರೆ (ret < 0) {
            av_ಚೌಕಟ್ಟು_unref(tmp_ಚೌಕಟ್ಟು);
            ಹಿಂತಿರುಗಿ ret;
        }
        ret = qsv_fill_border(tmp_ಚೌಕಟ್ಟು, src);
        ಆದರೆ (ret < 0) {
            av_ಚೌಕಟ್ಟು_unref(tmp_ಚೌಕಟ್ಟು);
            ಹಿಂತಿರುಗಿ ret;
        }

        tmp_info = ಹೊರಹೋಗು->Info;
        ಹೊರಹೋಗು->Info.CropW = FFMIN(ಹೊರಹೋಗು->Info.ಅಗಲ_2,  tmp_ಚೌಕಟ್ಟು->ಅಗಲ);
        ಹೊರಹೋಗು->Info.CropH = FFMIN(ಹೊರಹೋಗು->Info.ಎತ್ತರ_2, tmp_ಚೌಕಟ್ಟು->ಎತ್ತರ);
    }

    src_ಚೌಕಟ್ಟು = realigned ? tmp_ಚೌಕಟ್ಟು : src;

    ಆದರೆ (!s->session_upload) {
        ಆದರೆ (s->ಮಗು_ಚೌಕಟ್ಟುಗಳು_ref)
            ಹಿಂತಿರುಗಿ qsv_transfer_ದತ್ತಾಂಶ_ಮಗು(ctx, dst, src_ಚೌಕಟ್ಟು);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    ಒಳ.Info = ಹೊರಹೋಗು->Info;
    map_ಚೌಕಟ್ಟು_ಗಮ್ಯ_surface(src_ಚೌಕಟ್ಟು, &ಒಳ);

    ಮಾಡು {
        err = MFXVideo_VPP_ಸತತ_ಚೌಕಟ್ಟು_VPPAsync(s->session_upload, &ಒಳ, ಹೊರಹೋಗು, ಖಾಲಿ, &sync);
        ಆದರೆ (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } ಆಗ (err == MFX_WRN_DEVICE_BUSY);

    ಆದರೆ (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಮಾಡು {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } ಆಗ (err == MFX_WRN_ಒಳ_EXECUTION);
    ಆದರೆ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        ಹಿಂತಿರುಗಿ AVERROR_UNKNOWN;
    }

    ಆದರೆ (realigned) {
        ಹೊರಹೋಗು->Info.CropW = tmp_info.CropW;
        ಹೊರಹೋಗು->Info.CropH = tmp_info.CropH;
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_dynamic_ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, ಪೂರ್ಣಾಂಕ flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfx_ಚೌಕಟ್ಟು_Surface1 mfx_surf1;

    ಆಯ್ಕೆ (src_ctx->device_ctx->type) {
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->ಚೌಕಟ್ಟು_type  = MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_DECODER_ಗುರಿ;
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ CONFIG_D3D11VA
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        ಆದರೆ (src_hwctx->BindFlags & D3_D11_BIND_RENDER_ಗುರಿ) {
            dst_hwctx->ಚೌಕಟ್ಟು_type |= MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_PROCESSOR_ಗುರಿ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            dst_hwctx->ಚೌಕಟ್ಟು_type |= MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_DECODER_ಗುರಿ;
        }
    }
    ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ

    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, ಗಾತ್ರ(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->ಚೌಕಟ್ಟು_info = mfx_surf1.Info;
    dst_hwctx->info = &s->ಚೌಕಟ್ಟು_info;
    dst_hwctx->nb_surfaces = 0;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_fixed_ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, ಪೂರ್ಣಾಂಕ flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    ಪೂರ್ಣಾಂಕ i;

    ಆಯ್ಕೆ (src_ctx->device_ctx->type) {
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ = av_calloc(src_ctx->initial_pool_ಗಾತ್ರ,
                                                 ಗಾತ್ರ(*s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ));
            ಆದರೆ (!s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ)
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            s->surfaces_ಆಂತರಿಕ = av_calloc(src_hwctx->nb_surfaces,
                                             ಗಾತ್ರ(*s->surfaces_ಆಂತರಿಕ));
            ಆದರೆ (!s->surfaces_ಆಂತರಿಕ)
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            ಗಾಗಿ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_ಆಂತರಿಕ[i]);
                s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಮೊದಲ = src_hwctx->surface_ids + i;
                s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಎರಡನೇ = (mfxMemId)MFX_INFINITE;
                s->surfaces_ಆಂತರಿಕ[i].ದತ್ತಾಂಶ_2.MemId = (mfxMemId)&s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->ಚೌಕಟ್ಟು_type  = MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_DECODER_ಗುರಿ;
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ = av_calloc(src_ctx->initial_pool_ಗಾತ್ರ,
                                                 ಗಾತ್ರ(*s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ));
            ಆದರೆ (!s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ)
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            s->surfaces_ಆಂತರಿಕ = av_calloc(src_ctx->initial_pool_ಗಾತ್ರ,
                                             ಗಾತ್ರ(*s->surfaces_ಆಂತರಿಕ));
            ಆದರೆ (!s->surfaces_ಆಂತರಿಕ)
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            ಗಾಗಿ (i = 0; i < src_ctx->initial_pool_ಗಾತ್ರ; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_ಆಂತರಿಕ[i]);
                s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಮೊದಲ = (mfxMemId)src_hwctx->texture_infos[i].texture;
                ಆದರೆ (src_hwctx->BindFlags & D3_D11_BIND_RENDER_ಗುರಿ) {
                    s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಎರಡನೇ = (mfxMemId)MFX_INFINITE;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಎರಡನೇ = (mfxMemId)src_hwctx->texture_infos[i].ಸೂಚ್ಯಂಕ;
                }
                s->surfaces_ಆಂತರಿಕ[i].ದತ್ತಾಂಶ_2.MemId = (mfxMemId)&s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_ಗಾತ್ರ;
            ಆದರೆ (src_hwctx->BindFlags & D3_D11_BIND_RENDER_ಗುರಿ) {
                dst_hwctx->ಚೌಕಟ್ಟು_type |= MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_PROCESSOR_ಗುರಿ;
            } ಇಲ್ಲದಿದ್ದರೆ {
                dst_hwctx->ಚೌಕಟ್ಟು_type |= MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_DECODER_ಗುರಿ;
            }
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_ಚೌಕಟ್ಟುಗಳು_Context *src_hwctx = src_ctx->hwctx;
            s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ = av_calloc(src_ctx->initial_pool_ಗಾತ್ರ,
                                                 ಗಾತ್ರ(*s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ));
            ಆದರೆ (!s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ)
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            s->surfaces_ಆಂತರಿಕ = av_calloc(src_hwctx->nb_surfaces,
                                             ಗಾತ್ರ(*s->surfaces_ಆಂತರಿಕ));
            ಆದರೆ (!s->surfaces_ಆಂತರಿಕ)
                ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
            ಗಾಗಿ (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_ಆಂತರಿಕ[i]);
                s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಮೊದಲ = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i].ಎರಡನೇ = (mfxMemId)MFX_INFINITE;
                s->surfaces_ಆಂತರಿಕ[i].ದತ್ತಾಂಶ_2.MemId = (mfxMemId)&s->handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            ಆದರೆ (src_hwctx->surface_type == DXVA2_Video_Processor_Render_ಗುರಿ)
                dst_hwctx->ಚೌಕಟ್ಟು_type = MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_PROCESSOR_ಗುರಿ;
            ಇಲ್ಲದಿದ್ದರೆ
                dst_hwctx->ಚೌಕಟ್ಟು_type = MFX_MEMTYPE_VIDEO_ಸ್ಮರಣೆ_DECODER_ಗುರಿ;
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_ಆಂತರಿಕ;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, ಪೂರ್ಣಾಂಕ flags)
{
    ಆದರೆ (src_ctx->initial_pool_ಗಾತ್ರ < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (src_ctx->initial_pool_ಗಾತ್ರ == 0) {
        ಹಿಂತಿರುಗಿ qsv_dynamic_ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ(dst_ctx, src_ctx, flags);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ qsv_fixed_ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ(dst_ctx, src_ctx, flags);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_fixed_pool_map_ಗಮ್ಯ(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    ಪೂರ್ಣಾಂಕ i, err, ಸೂಚ್ಯಂಕ = -1;

    ಗಾಗಿ (i = 0; i < hwctx->nb_surfaces && ಸೂಚ್ಯಂಕ < 0; i++) {
        ಆಯ್ಕೆ(src->format) {
#ಆದರೆ CONFIG_VAAPI
        ಸ್ಥಿತಿ AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].ದತ್ತಾಂಶ_2.MemId;
            ಆದರೆ (*(VASurfaceID*)pair->ಮೊದಲ == (VASurfaceID)(uintptr_t)src->ದತ್ತಾಂಶ[3])
                ಸೂಚ್ಯಂಕ = i;
            ನಿಲ್ಲಿಸು;
        }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
        ಸ್ಥಿತಿ AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].ದತ್ತಾಂಶ_2.MemId;
            ಆದರೆ (pair->ಮೊದಲ == src->ದತ್ತಾಂಶ[0]
                && (pair->ಎರಡನೇ == src->ದತ್ತಾಂಶ[1]
                    || (pair->ಎರಡನೇ == (mfxMemId)MFX_INFINITE && src->ದತ್ತಾಂಶ[1] == (uint8_t *)0)))
                ಸೂಚ್ಯಂಕ = i;
            ನಿಲ್ಲಿಸು;
        }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
        ಸ್ಥಿತಿ AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].ದತ್ತಾಂಶ_2.MemId;
            ಆದರೆ (pair->ಮೊದಲ == src->ದತ್ತಾಂಶ[3])
                ಸೂಚ್ಯಂಕ = i;
            ನಿಲ್ಲಿಸು;
        }
#ಆದರೆ_ಅಂತ್ಯ
        }
    }
    ಆದರೆ (ಸೂಚ್ಯಂಕ < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx,
                                dst, src, ಖಾಲಿ, ಖಾಲಿ);
    ಆದರೆ (err)
        ಹಿಂತಿರುಗಿ err;

    dst->ಅಗಲ   = src->ಅಗಲ;
    dst->ಎತ್ತರ  = src->ಎತ್ತರ;
    dst->ದತ್ತಾಂಶ[3] = (uint8_t*)&hwctx->surfaces[ಸೂಚ್ಯಂಕ];

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfx_ಚೌಕಟ್ಟು_Surface1 *surfaces_ಆಂತರಿಕ = (mfx_ಚೌಕಟ್ಟು_Surface1 *)hwmap->priv;
    mfxHDLPair *handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ = (mfxHDLPair *)surfaces_ಆಂತರಿಕ->ದತ್ತಾಂಶ_2.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->ಮೂಲ_ಚೌಕಟ್ಟುಗಳು->ದತ್ತಾಂಶ;

    ಆಯ್ಕೆ (src_ctx->format) {
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ->ಮೊದಲ);

        ನಿಲ್ಲಿಸು;
    }
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ CONFIG_D3D11VA
    ಸ್ಥಿತಿ AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        ನಿಲ್ಲಿಸು;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        ನಿಲ್ಲಿಸು;
    }

    av_freep(&handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ);
    av_freep(&surfaces_ಆಂತರಿಕ);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_dynamic_pool_map_ಗಮ್ಯ(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    mfx_ಚೌಕಟ್ಟು_Surface1 *surfaces_ಆಂತರಿಕ = ಖಾಲಿ;
    mfxHDLPair *handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ret = 0;

    surfaces_ಆಂತರಿಕ = av_calloc(1, ಗಾತ್ರ(*surfaces_ಆಂತರಿಕ));
    ಆದರೆ (!surfaces_ಆಂತರಿಕ) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ = av_calloc(1, ಗಾತ್ರ(*handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ));
    ಆದರೆ (!handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ) {
        ret = AVERROR(ENOMEM);
        ಹೋಗು fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_ಆಂತರಿಕ);
    ಆದರೆ (ret < 0)
        ಹೋಗು fail;

    ಆಯ್ಕೆ (src->format) {
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_ಆಂತರಿಕ;

        surface_id_ಆಂತರಿಕ = av_calloc(1, ಗಾತ್ರ(*surface_id_ಆಂತರಿಕ));
        ಆದರೆ (!surface_id_ಆಂತರಿಕ) {
            ret =AVERROR(ENOMEM);
            ಹೋಗು fail;
        }

        *surface_id_ಆಂತರಿಕ = (VASurfaceID)(uintptr_t)src->ದತ್ತಾಂಶ[3];
        handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ->ಮೊದಲ = (mfxHDL)surface_id_ಆಂತರಿಕ;
        handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ->ಎರಡನೇ = (mfxMemId)MFX_INFINITE;

        ನಿಲ್ಲಿಸು;
    }
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ CONFIG_D3D11VA
    ಸ್ಥಿತಿ AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_ಚೌಕಟ್ಟುಗಳು_ctx->ದತ್ತಾಂಶ;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ->ಮೊದಲ = (mfxMemId)src->ದತ್ತಾಂಶ[0];

        ಆದರೆ (src_hwctx->BindFlags & D3_D11_BIND_RENDER_ಗುರಿ) {
            handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ->ಎರಡನೇ = (mfxMemId)MFX_INFINITE;
        } ಇಲ್ಲದಿದ್ದರೆ {
            handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ->ಎರಡನೇ = (mfxMemId)src->ದತ್ತಾಂಶ[1];
        }

        ನಿಲ್ಲಿಸು;
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ret = AVERROR(ENOSYS);
        ಹೋಗು fail;
    }

    surfaces_ಆಂತರಿಕ->ದತ್ತಾಂಶ_2.MemId = (mfxMemId)handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ;

    ret = ff_hwframe_map_create(dst->hw_ಚೌಕಟ್ಟುಗಳು_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_ಆಂತರಿಕ);
    ಆದರೆ (ret)
        ಹೋಗು fail;

    dst->ಅಗಲ   = src->ಅಗಲ;
    dst->ಎತ್ತರ  = src->ಎತ್ತರ;
    dst->ದತ್ತಾಂಶ[3] = (uint8_t*)surfaces_ಆಂತರಿಕ;

    ಹಿಂತಿರುಗಿ 0;

fail:
    av_freep(&handle_ಜೋಡಿಗಳು_ಆಂತರಿಕ);
    av_freep(&surfaces_ಆಂತರಿಕ);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_map_ಗಮ್ಯ(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ಸ್ಥಿರಾಂಕ AVFrame *src, ಪೂರ್ಣಾಂಕ flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    ಆದರೆ (hwctx->nb_surfaces)
        ಹಿಂತಿರುಗಿ qsv_fixed_pool_map_ಗಮ್ಯ(dst_ctx, dst, src, flags);
    ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ qsv_dynamic_pool_map_ಗಮ್ಯ(dst_ctx, dst, src, flags);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_ಚೌಕಟ್ಟುಗಳು_get_constraints(AVHWDeviceContext *ctx,
                                      ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    ಪೂರ್ಣಾಂಕ i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    ಗಾತ್ರ(*constraints->valid_sw_formats));
    ಆದರೆ (!constraints->valid_sw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, ಗಾತ್ರ(*constraints->valid_hw_formats));
    ಆದರೆ (!constraints->valid_hw_formats)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    ಆದರೆ (hwctx->session)
        MFXClose(hwctx->session);

    ಆದರೆ (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_ಬಫರ್_unref(&priv->ಮಗು_device_ctx);
    av_freep(&priv);
}

ಸ್ಥಿರ mfxIMPL ಆರಿಸು_implementation(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device, ಎಣಿಕೆ AVHWDeviceType ಮಗು_device_type)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name;
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
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (device) {
        ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            ಆದರೆ (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                ನಿಲ್ಲಿಸು;
            }
        ಆದರೆ (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, ಖಾಲಿ, 0);
    }

    ಆದರೆ (impl != MFX_IMPL_SOFTWARE) {
        ಆದರೆ (ಮಗು_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_ಮೂಲಕ_D3_D11;
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಮಗು_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_ಮೂಲಕ_D3_D9;
    }

    ಹಿಂತಿರುಗಿ impl;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_device_derive_from_ಮಗು(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *ಮಗು_device_ctx,
                                        ಪೂರ್ಣಾಂಕ flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfx_ಆವೃತ್ತಿ    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfx_ಸ್ಥಿತಿ     err;
    ಪೂರ್ಣಾಂಕ ret;

    ಆಯ್ಕೆ (ಮಗು_device_ctx->type) {
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *ಮಗು_device_hwctx = ಮಗು_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)ಮಗು_device_hwctx->display;
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *ಮಗು_device_hwctx = ಮಗು_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)ಮಗು_device_hwctx->device;
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *ಮಗು_device_hwctx = ಮಗು_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)ಮಗು_device_hwctx->devmgr;
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        ret = AVERROR(ENOSYS);
        ಹೋಗು fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    ಆದರೆ (ret)
        ಹೋಗು fail;

    err = MFXVideo_CORE_ಗಣ_Handle(hwctx->session, handle_type, handle);
    ಆದರೆ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        ಹೋಗು fail;
    }

    ಹಿಂತಿರುಗಿ 0;

fail:
    ಆದರೆ (hwctx->session)
        MFXClose(hwctx->session);

    ಆದರೆ (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = ಖಾಲಿ;
    hwctx->loader = ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *ಮಗು_device_ctx,
                             AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(ಗಾತ್ರ(*priv));
    ಆದರೆ (!priv)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ಬಿಡುಗಡೆ = qsv_device_free;

    impl = ಆರಿಸು_implementation("hw_any", ಮಗು_device_ctx->type);
    ಹಿಂತಿರುಗಿ qsv_device_derive_from_ಮಗು(ctx, impl,
                                        ಮಗು_device_ctx, flags);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ qsv_device_create(AVHWDeviceContext *ctx, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *device,
                             AVDictionary *opts, ಪೂರ್ಣಾಂಕ flags)
{
    QSVDevicePriv *priv;
    ಎಣಿಕೆ AVHWDeviceType ಮಗು_device_type;
    AVHWDeviceContext *ಮಗು_device;
    AVDictionary *ಮಗು_device_opts;
    AVDictionary_ನಮೂದು *e;

    mfxIMPL impl;
    ಪೂರ್ಣಾಂಕ ret;

    priv = av_mallocz(ಗಾತ್ರ(*priv));
    ಆದರೆ (!priv)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->ಬಿಡುಗಡೆ        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", ಖಾಲಿ, 0);
    ಆದರೆ (e) {
        ಮಗು_device_type = av_hwdevice_ಕಂಡುಹಿಡಿ_type_by_name(e->ಮೌಲ್ಯ);
        ಆದರೆ (ಮಗು_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->ಮೌಲ್ಯ);
            ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
        }
#ಆದರೆ QSV_ONEVPL
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        ಮಗು_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (CONFIG_DXVA2) {
        ಮಗು_device_type = AV_HWDEVICE_TYPE_DXVA2;
#ಇಲ್ಲದಿದ್ದರೆ
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (CONFIG_DXVA2) {
        av_log(ಖಾಲಿ, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        ಮಗು_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (CONFIG_D3D11VA) {
        ಮಗು_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#ಆದರೆ_ಅಂತ್ಯ
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (CONFIG_VAAPI) {
        ಮಗು_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } ಇಲ್ಲದಿದ್ದರೆ {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
    }

#ಆದರೆ CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    ಆದರೆ (ಮಗು_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->ಮೌಲ್ಯ);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಮಗು_device_opts = ಖಾಲಿ;
    ಆಯ್ಕೆ (ಮಗು_device_type) {
#ಆದರೆ CONFIG_VAAPI
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_ಗಣ(&ಮಗು_device_opts, "vendor_id", "0x8086", 0);
            av_dict_ಗಣ(&ಮಗು_device_opts, "driver",    "iHD",    0);
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_D3D11VA
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_ಗಣ(&ಮಗು_device_opts, "vendor_id",        "0x8086",  0);
        }
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ CONFIG_DXVA2
    ಸ್ಥಿತಿ AV_HWDEVICE_TYPE_DXVA2:
#ಆದರೆ QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#ಆದರೆ_ಅಂತ್ಯ
        ನಿಲ್ಲಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
    ಪೂರ್ವನಿಯೋಜಿತ:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
        }
        ನಿಲ್ಲಿಸು;
    }

    e = av_dict_get(opts, "child_device", ಖಾಲಿ, 0);
    ret = av_hwdevice_ctx_create(&priv->ಮಗು_device_ctx, ಮಗು_device_type,
                                 e ? e->ಮೌಲ್ಯ : ಖಾಲಿ, ಮಗು_device_opts, 0);

    av_dict_free(&ಮಗು_device_opts);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಮಗು_device = (AVHWDeviceContext*)priv->ಮಗು_device_ctx->ದತ್ತಾಂಶ;

    impl = ಆರಿಸು_implementation(device, ಮಗು_device_type);

    ಹಿಂತಿರುಗಿ qsv_device_derive_from_ಮಗು(ctx, impl, ಮಗು_device, 0);
}

ಸ್ಥಿರಾಂಕ HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_ಗಾತ್ರ      = ಗಾತ್ರ(QSVDeviceContext),
    .ಚೌಕಟ್ಟುಗಳು_hwctx_ಗಾತ್ರ      = ಗಾತ್ರ(QSVFramesContext),

    .device_create          = qsv_device_create,
    .device_derive          = qsv_device_derive,
    .device_init            = qsv_device_init,
    .ಚೌಕಟ್ಟುಗಳು_get_constraints = qsv_ಚೌಕಟ್ಟುಗಳು_get_constraints,
    .ಚೌಕಟ್ಟುಗಳು_init            = qsv_ಚೌಕಟ್ಟುಗಳು_init,
    .ಚೌಕಟ್ಟುಗಳು_uninit          = qsv_ಚೌಕಟ್ಟುಗಳು_uninit,
    .ಚೌಕಟ್ಟುಗಳು_get_ಬಫರ್      = qsv_get_ಬಫರ್,
    .transfer_get_formats   = qsv_transfer_get_formats,
    .transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ       = qsv_transfer_ದತ್ತಾಂಶ_ಗಮ್ಯ,
    .transfer_ದತ್ತಾಂಶ_from     = qsv_transfer_ದತ್ತಾಂಶ_from,
    .map_ಗಮ್ಯ                 = qsv_map_ಗಮ್ಯ,
    .map_from               = qsv_map_from,
    .ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ       = qsv_ಚೌಕಟ್ಟುಗಳು_derive_ಗಮ್ಯ,
    .ಚೌಕಟ್ಟುಗಳು_derive_from     = qsv_ಚೌಕಟ್ಟುಗಳು_derive_from,

    .pix_fmts = (ಸ್ಥಿರಾಂಕ ಎಣಿಕೆ AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
