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

#إذا HAVE_PTHREADS
#ضمن <pthread.h>
#جيڪڏهن_پورو

#وصف_ڪريو COBJMACROS
#إذا CONFIG_VAAPI
#ضمن "hwcontext_vaapi.h"
#جيڪڏهن_پورو
#إذا CONFIG_D3D11VA
#ضمن "hwcontext_d3d11va.h"
#جيڪڏهن_پورو
#إذا CONFIG_DXVA2
#ضمن <initguid.h>
#ضمن "hwcontext_dxva2.h"
#جيڪڏهن_پورو

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

#وصف_ڪريو QSV_نسخو_ATLEAST(MAJOR, MINOR)   \
    (MFX_نسخو_MAJOR > (MAJOR) ||         \
     MFX_نسخو_MAJOR == (MAJOR) && MFX_نسخو_MINOR >= (MINOR))

#وصف_ڪريو QSV_RUNTIME_نسخو_ATLEAST(MFX_نسخو, MAJOR, MINOR)          \
    ((MFX_نسخو.Major > (MAJOR)) ||                                   \
     (MFX_نسخو.Major == (MAJOR) && MFX_نسخو.Minor >= (MINOR)))

#وصف_ڪريو MFX_IMPL_ذريعي_نقاب(impl) (0x0f00 & (impl))
#وصف_ڪريو QSV_ONEVPL       QSV_نسخو_ATLEAST(2, 0)
#وصف_ڪريو QSV_HAVE_OPAQUE  !QSV_ONEVPL

#إذا QSV_ONEVPL
#ضمن <mfxdispatcher.h>
#وإلا
#وصف_ڪريو MFXUnload(a) افعل { } طالما(0)
#جيڪڏهن_پورو

تعريفنوع بنية QSVDevicePriv {
    AVBufferRef *ٻار_device_ctx;
} QSVDevicePriv;

تعريفنوع بنية QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfx_نسخو          ver;
    mfxIMPL             impl;

    تعداد AVHWDeviceType ٻار_device_type;
    تعداد AVPixelFormat  ٻار_pix_fmt;
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
#إذا HAVE_PTHREADS
    pthread_mutex_t session_تالو;
#جيڪڏهن_پورو

    AVBufferRef *ٻار_چوکٺا_ref;
    mfx_چوکٺو_Surface1 *surfaces_اندروني;
    mfxHDLPair *handle_جوڙا_اندروني;
    صحيح             nb_surfaces_استعمال_ٿيل;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#إذا QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfx_چوکٺو_Surface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfx_Ext_بفر *ext_buffers[1];
#جيڪڏهن_پورو
    AVFrame realigned_upload_چوکٺو;
    AVFrame realigned_download_چوکٺو;

    mfx_چوکٺو_Info چوکٺو_info;
} QSVFramesContext;

تعريفنوع بنية QSVSurface {
    mfx_چوکٺو_Surface1 mfx_surface;
    AVFrame *ٻار_چوکٺو;
} QSVSurface;

ساكن ثابت بنية {
    تعداد AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_سرڪايو;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#إذا CONFIG_VAAPI
    { AV_PIX_FMT_UYVY422,
                       MFX_FOURCC_UYVY, 0 },
#جيڪڏهن_پورو
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
#إذا QSV_نسخو_ATLEAST(1, 31)
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
#جيڪڏهن_پورو
};

خارجي صحيح ff_qsv_get_surface_بنياد_handle(mfx_چوکٺو_Surface1 *surf,
                                          تعداد AVHWDeviceType بنياد_dev_type,
                                          فراغ **بنياد_handle);

ساكن صحيح qsv_init_surface(AVHWFramesContext *ctx, mfx_چوکٺو_Surface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
صحيح ff_qsv_get_surface_بنياد_handle(mfx_چوکٺو_Surface1 *surf,
                                   تعداد AVHWDeviceType بنياد_dev_type,
                                   فراغ **بنياد_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->معلومات_2.MemId;
    بدل (بنياد_dev_type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        بنياد_handle[0] = handle_pair->پهريون;
        أرجع 0;
#جيڪڏهن_پورو
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        بنياد_handle[0] = handle_pair->پهريون;
        بنياد_handle[1] = handle_pair->ٻيو;
        أرجع 0;
#جيڪڏهن_پورو
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        بنياد_handle[0] = handle_pair->پهريون;
        أرجع 0;
#جيڪڏهن_پورو
    }
    أرجع AVERROR(EINVAL);
}

ساكن uint32_t qsv_fourcc_from_pix_fmt(تعداد AVPixelFormat pix_fmt)
{
    صحيح i;
    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        إذا (supported_pixel_formats[i].pix_fmt == pix_fmt)
            أرجع supported_pixel_formats[i].fourcc;
    }
    أرجع 0;
}

ساكن uint16_t qsv_سرڪايو_from_pix_fmt(تعداد AVPixelFormat pix_fmt)
{
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        إذا (supported_pixel_formats[i].pix_fmt == pix_fmt)
            أرجع supported_pixel_formats[i].mfx_سرڪايو;
    }

    أرجع 0;
}

#إذا CONFIG_D3D11VA
ساكن uint32_t qsv_get_d3d11va_bind_flags(صحيح mem_type)
{
    uint32_t bind_flags = 0;

    إذا ((mem_type & MFX_MEMTYPE_VIDEO_يادگيري_ENCODER_هدف) && (mem_type & MFX_MEMTYPE_اندروني_چوکٺو))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    وإلا
        bind_flags = D3D11_BIND_DECODER;

    إذا ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_يادگيري_PROCESSOR_هدف & mem_type))
        bind_flags = D3_D11_BIND_RENDER_هدف;

    أرجع bind_flags;
}
#جيڪڏهن_پورو

ساكن صحيح qsv_fill_border(AVFrame *dst, ثابت AVFrame *src)
{
    ثابت AVPixFmtDescriptor *desc;
    صحيح i, planes_nb = 0;
    إذا (dst->format != src->format)
        أرجع AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    لكل (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    لكل (i = 0; i < planes_nb; i++) {
        صحيح sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->ويڪر,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->ويڪر,
                                                 i);
        ثابت AVComponentDescriptor comp = desc->comp[i];
        إذا (swidth < 0 || dwidth < 0) {
            av_log(عدم, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            أرجع AVERROR(EINVAL);
        }
        sheight = src->اوچائي;
        dheight = dst->اوچائي;
        إذا (i) {
            sheight = AV_CEIL_RSHIFT(src->اوچائي, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->اوچائي, desc->log2_chroma_h);
        }
        //fill right padding
        لكل (y = 0; y < sheight; y++) {
            فراغ *سٽ_ptr = dst->معلومات[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(سٽ_ptr,
                           comp.اونهائي > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        لكل (y = sheight; y < dheight; y++) {
            يادگيري_نقل(dst->معلومات[i]+y*dst->linesize[i],
                   dst->معلومات[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    أرجع 0;
}

ساكن صحيح qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    صحيح   hw_handle_supported = 0;
    mfxHandleType handle_type;
    تعداد AVHWDeviceType device_type;
    تعداد AVPixelFormat  pix_fmt;
    mfx_حالت err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    إذا (err == MFX_ERR_NONE)
        err = MFXQuery_نسخو(hwctx->session, &s->ver);
    إذا (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        أرجع AVERROR_UNKNOWN;
    }

    إذا (MFX_IMPL_ذريعي_VAAPI == MFX_IMPL_ذريعي_نقاب(s->impl)) {
#إذا CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#جيڪڏهن_پورو
    } وإلا إذا (MFX_IMPL_ذريعي_D3_D11 == MFX_IMPL_ذريعي_نقاب(s->impl)) {
#إذا CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#جيڪڏهن_پورو
    } وإلا إذا (MFX_IMPL_ذريعي_D3_D9 == MFX_IMPL_ذريعي_نقاب(s->impl)) {
#إذا CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#جيڪڏهن_پورو
    }

    إذا (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        إذا (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->ٻار_device_type = device_type;
            s->ٻار_pix_fmt     = pix_fmt;
        }
    }
    إذا (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    أرجع 0;
}

ساكن فراغ qsv_چوکٺا_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    إذا (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = عدم;
    s->session_download_init = 0;

    إذا (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = عدم;
    s->session_upload_init = 0;

#إذا HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_تالو);
#جيڪڏهن_پورو

    av_freep(&s->mem_ids);
#إذا QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#جيڪڏهن_پورو
    av_freep(&s->surfaces_اندروني);
    av_freep(&s->handle_جوڙا_اندروني);
    av_چوکٺو_unref(&s->realigned_upload_چوکٺو);
    av_چوکٺو_unref(&s->realigned_download_چوکٺو);
    av_بفر_unref(&s->ٻار_چوکٺا_ref);
}

ساكن فراغ qsv_pool_release_dummy(فراغ *opaque, uint8_t *معلومات)
{
}

ساكن فراغ qsv_pool_release(فراغ *opaque, uint8_t *معلومات)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)معلومات;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.معلومات_2.MemId;
    AVHWFramesContext *ٻار_چوکٺا_ctx;

    إذا (!s->ٻار_چوکٺا_ref)
        أرجع;

    ٻار_چوکٺا_ctx = (AVHWFramesContext*)s->ٻار_چوکٺا_ref->معلومات;
    إذا (!ٻار_چوکٺا_ctx->device_ctx)
        أرجع;

#إذا CONFIG_VAAPI
    إذا (ٻار_چوکٺا_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->پهريون);
#جيڪڏهن_پورو

    av_freep(&hdl_pair);
    av_چوکٺو_free(&qsv_surface->ٻار_چوکٺو);
    av_freep(&qsv_surface);
}

ساكن AVBufferRef *qsv_fixed_pool_alloc(فراغ *opaque, size_t سائيز)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    إذا (s->nb_surfaces_استعمال_ٿيل < hwctx->nb_surfaces) {
        s->nb_surfaces_استعمال_ٿيل++;
        أرجع av_بفر_create((uint8_t*)(s->surfaces_اندروني + s->nb_surfaces_استعمال_ٿيل - 1),
                                حجم(*hwctx->surfaces), qsv_pool_release_dummy, عدم, 0);
    }

    أرجع عدم;
}

ساكن AVBufferRef *qsv_dynamic_pool_alloc(فراغ *opaque, size_t سائيز)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *ٻار_چوکٺا_ctx;
    QSVSurface *qsv_surface = عدم;
    mfxHDLPair *handle_جوڙا_اندروني = عدم;
    صحيح ret;

    إذا (!s->ٻار_چوکٺا_ref)
        اذهب fail;

    ٻار_چوکٺا_ctx = (AVHWFramesContext*)s->ٻار_چوکٺا_ref->معلومات;
    إذا (!ٻار_چوکٺا_ctx->device_ctx)
        اذهب fail;

#إذا CONFIG_DXVA2
    إذا (ٻار_چوکٺا_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        اذهب fail;
    }
#جيڪڏهن_پورو

    qsv_surface = av_calloc(1, حجم(*qsv_surface));
    إذا (!qsv_surface)
        اذهب fail;

    qsv_surface->ٻار_چوکٺو = av_چوکٺو_alloc();
    إذا (!qsv_surface->ٻار_چوکٺو)
        اذهب fail;

    ret = av_hwframe_get_بفر(s->ٻار_چوکٺا_ref, qsv_surface->ٻار_چوکٺو, 0);
    إذا (ret < 0)
        اذهب fail;

    handle_جوڙا_اندروني = av_calloc(1, حجم(*handle_جوڙا_اندروني));
    إذا (!handle_جوڙا_اندروني)
        اذهب fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    إذا (ret < 0)
        اذهب fail;

#إذا CONFIG_VAAPI
    إذا (ٻار_چوکٺا_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_اندروني;

        surface_id_اندروني = av_calloc(1, حجم(*surface_id_اندروني));
        إذا (!surface_id_اندروني)
            اذهب fail;

        *surface_id_اندروني = (VASurfaceID)(uintptr_t)qsv_surface->ٻار_چوکٺو->معلومات[3];
        handle_جوڙا_اندروني->پهريون = (mfxHDL)surface_id_اندروني;
        handle_جوڙا_اندروني->ٻيو = (mfxMemId)MFX_INFINITE;
    }
#جيڪڏهن_پورو

#إذا CONFIG_D3D11VA
    إذا (ٻار_چوکٺا_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *ٻار_چوکٺا_hwctx = ٻار_چوکٺا_ctx->hwctx;
        handle_جوڙا_اندروني->پهريون = (mfxMemId)qsv_surface->ٻار_چوکٺو->معلومات[0];

        إذا (ٻار_چوکٺا_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف)
            handle_جوڙا_اندروني->ٻيو = (mfxMemId)MFX_INFINITE;
        وإلا
            handle_جوڙا_اندروني->ٻيو = (mfxMemId)qsv_surface->ٻار_چوکٺو->معلومات[1];

    }
#جيڪڏهن_پورو

    qsv_surface->mfx_surface.معلومات_2.MemId = (mfxMemId)handle_جوڙا_اندروني;
    أرجع av_بفر_create((uint8_t *)qsv_surface, حجم(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    إذا (qsv_surface) {
        av_چوکٺو_free(&qsv_surface->ٻار_چوکٺو);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_جوڙا_اندروني);

    أرجع عدم;
}

ساكن AVBufferRef *qsv_pool_alloc(فراغ *opaque, size_t سائيز)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    إذا (hwctx->nb_surfaces == 0) {
        أرجع qsv_dynamic_pool_alloc(opaque, سائيز);
    } وإلا {
        أرجع qsv_fixed_pool_alloc(opaque, سائيز);
    }
}

ساكن صحيح qsv_init_ٻار_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *ٻار_device_ref = عدم;
    AVBufferRef *ٻار_چوکٺا_ref = عدم;

    AVHWDeviceContext *ٻار_device_ctx;
    AVHWFramesContext *ٻار_چوکٺا_ctx;

    صحيح i, ret = 0;

    إذا (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        أرجع AVERROR(EINVAL);
    }

    ٻار_device_ref = av_hwdevice_ctx_alloc(device_priv->ٻار_device_type);
    إذا (!ٻار_device_ref)
        أرجع AVERROR(ENOMEM);
    ٻار_device_ctx   = (AVHWDeviceContext*)ٻار_device_ref->معلومات;

#إذا CONFIG_VAAPI
    إذا (ٻار_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *ٻار_device_hwctx = ٻار_device_ctx->hwctx;
        ٻار_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#جيڪڏهن_پورو
#إذا CONFIG_D3D11VA
    إذا (ٻار_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *ٻار_device_hwctx = ٻار_device_ctx->hwctx;
        ID3_D11_Device_جوڙيو_Ref((ID3D11Device*)device_priv->handle);
        ٻار_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#جيڪڏهن_پورو
#إذا CONFIG_DXVA2
    إذا (ٻار_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *ٻار_device_hwctx = ٻار_device_ctx->hwctx;
        ٻار_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#جيڪڏهن_پورو

    ret = av_hwdevice_ctx_init(ٻار_device_ref);
    إذا (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        اذهب fail;
    }

    ٻار_چوکٺا_ref = av_hwframe_ctx_alloc(ٻار_device_ref);
    إذا (!ٻار_چوکٺا_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    ٻار_چوکٺا_ctx = (AVHWFramesContext*)ٻار_چوکٺا_ref->معلومات;

    ٻار_چوکٺا_ctx->format            = device_priv->ٻار_pix_fmt;
    ٻار_چوکٺا_ctx->sw_format         = ctx->sw_format;
    ٻار_چوکٺا_ctx->initial_pool_سائيز = ctx->initial_pool_سائيز;
    ٻار_چوکٺا_ctx->ويڪر             = FFALIGN(ctx->ويڪر, 16);
    ٻار_چوکٺا_ctx->اوچائي            = FFALIGN(ctx->اوچائي, 16);

#إذا CONFIG_D3D11VA
    إذا (ٻار_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *ٻار_چوکٺا_hwctx = ٻار_چوکٺا_ctx->hwctx;
        إذا (hwctx->چوکٺو_type == 0)
            hwctx->چوکٺو_type = MFX_MEMTYPE_VIDEO_يادگيري_PROCESSOR_هدف;
        إذا (hwctx->چوکٺو_type & MFX_MEMTYPE_SHARED_RESOURCE)
            ٻار_چوکٺا_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        ٻار_چوکٺا_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->چوکٺو_type);
    }
#جيڪڏهن_پورو
#إذا CONFIG_DXVA2
    إذا (ٻار_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_چوکٺا_Context *ٻار_چوکٺا_hwctx = ٻار_چوکٺا_ctx->hwctx;
        إذا (hwctx->چوکٺو_type & MFX_MEMTYPE_VIDEO_يادگيري_PROCESSOR_هدف)
            ٻار_چوکٺا_hwctx->surface_type = DXVA2_Video_Processor_Render_هدف;
        وإلا
            ٻار_چوکٺا_hwctx->surface_type = DXVA2_Video_Decoder_Render_هدف;
    }
#جيڪڏهن_پورو

    ret = av_hwframe_ctx_init(ٻار_چوکٺا_ref);
    إذا (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        اذهب fail;
    }

#إذا CONFIG_VAAPI
    إذا (ٻار_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *ٻار_چوکٺا_hwctx = ٻار_چوکٺا_ctx->hwctx;
        لكل (i = 0; i < ctx->initial_pool_سائيز; i++) {
            s->handle_جوڙا_اندروني[i].پهريون = ٻار_چوکٺا_hwctx->surface_ids + i;
            s->handle_جوڙا_اندروني[i].ٻيو = (mfxMemId)MFX_INFINITE;
            s->surfaces_اندروني[i].معلومات_2.MemId = (mfxMemId)&s->handle_جوڙا_اندروني[i];
        }
        hwctx->چوکٺو_type = MFX_MEMTYPE_VIDEO_يادگيري_DECODER_هدف;
    }
#جيڪڏهن_پورو
#إذا CONFIG_D3D11VA
    إذا (ٻار_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *ٻار_چوکٺا_hwctx = ٻار_چوکٺا_ctx->hwctx;
        لكل (i = 0; i < ctx->initial_pool_سائيز; i++) {
            s->handle_جوڙا_اندروني[i].پهريون = (mfxMemId)ٻار_چوکٺا_hwctx->texture_infos[i].texture;
            إذا(ٻار_چوکٺا_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف) {
                s->handle_جوڙا_اندروني[i].ٻيو = (mfxMemId)MFX_INFINITE;
            } وإلا {
                s->handle_جوڙا_اندروني[i].ٻيو = (mfxMemId)ٻار_چوکٺا_hwctx->texture_infos[i].اشاريو;
            }
            s->surfaces_اندروني[i].معلومات_2.MemId = (mfxMemId)&s->handle_جوڙا_اندروني[i];
        }
        إذا (ٻار_چوکٺا_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف) {
            hwctx->چوکٺو_type |= MFX_MEMTYPE_VIDEO_يادگيري_PROCESSOR_هدف;
        } وإلا {
            hwctx->چوکٺو_type |= MFX_MEMTYPE_VIDEO_يادگيري_DECODER_هدف;
        }
    }
#جيڪڏهن_پورو
#إذا CONFIG_DXVA2
    إذا (ٻار_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_چوکٺا_Context *ٻار_چوکٺا_hwctx = ٻار_چوکٺا_ctx->hwctx;
        لكل (i = 0; i < ctx->initial_pool_سائيز; i++) {
            s->handle_جوڙا_اندروني[i].پهريون = (mfxMemId)ٻار_چوکٺا_hwctx->surfaces[i];
            s->handle_جوڙا_اندروني[i].ٻيو = (mfxMemId)MFX_INFINITE;
            s->surfaces_اندروني[i].معلومات_2.MemId = (mfxMemId)&s->handle_جوڙا_اندروني[i];
        }
        إذا (ٻار_چوکٺا_hwctx->surface_type == DXVA2_Video_Processor_Render_هدف)
            hwctx->چوکٺو_type = MFX_MEMTYPE_VIDEO_يادگيري_PROCESSOR_هدف;
        وإلا
            hwctx->چوکٺو_type = MFX_MEMTYPE_VIDEO_يادگيري_DECODER_هدف;
    }
#جيڪڏهن_پورو

    s->ٻار_چوکٺا_ref       = ٻار_چوکٺا_ref;
    ٻار_چوکٺا_ref          = عدم;

fail:
    av_بفر_unref(&ٻار_device_ref);
    av_بفر_unref(&ٻار_چوکٺا_ref);
    أرجع ret;
}

ساكن صحيح qsv_init_surface(AVHWFramesContext *ctx, mfx_چوکٺو_Surface1 *surf)
{
    ثابت AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    إذا (!desc)
        أرجع AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    إذا (!fourcc)
        أرجع AVERROR(EINVAL);

    surf->Info.ٻٽو_انگ_اونهائي_Luma   = desc->comp[0].اونهائي;
    surf->Info.ٻٽو_انگ_اونهائي_Chroma = desc->comp[0].اونهائي;
    surf->Info.سرڪايو_2          = qsv_سرڪايو_from_pix_fmt(ctx->sw_format);

    إذا (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    وإلا إذا (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    وإلا
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.ويڪر_2          = FFALIGN(ctx->ويڪر, 16);
    surf->Info.CropW          = ctx->ويڪر;
    surf->Info.اوچائي_2         = FFALIGN(ctx->اوچائي, 16);
    surf->Info.CropH          = ctx->اوچائي;
    surf->Info.چوکٺو_شرح_Ext_N  = 25;
    surf->Info.چوکٺو_شرح_Ext_D  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    أرجع 0;
}

ساكن صحيح qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *چوکٺا_hwctx = &s->p;

    صحيح i, ret = 0;

    إذا (ctx->initial_pool_سائيز < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        أرجع AVERROR(EINVAL);
    } وإلا إذا (ctx->initial_pool_سائيز == 0) {
        mfx_چوکٺو_Surface1 mfx_surf1;

        ret = qsv_init_ٻار_ctx(ctx);
        إذا (ret < 0)
            أرجع ret;

        ffhwframesctx(ctx)->pool_اندروني = av_بفر_pool_init2(حجم(mfx_چوکٺو_Surface1),
                                                                 ctx, qsv_pool_alloc, عدم);
        إذا (!ffhwframesctx(ctx)->pool_اندروني)
            أرجع AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, حجم(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->چوکٺو_info = mfx_surf1.Info;
        چوکٺا_hwctx->info = &s->چوکٺو_info;
        چوکٺا_hwctx->nb_surfaces = 0;

        أرجع 0;
    }

    s->handle_جوڙا_اندروني = av_calloc(ctx->initial_pool_سائيز,
                                         حجم(*s->handle_جوڙا_اندروني));
    إذا (!s->handle_جوڙا_اندروني)
        أرجع AVERROR(ENOMEM);

    s->surfaces_اندروني = av_calloc(ctx->initial_pool_سائيز,
                                     حجم(*s->surfaces_اندروني));
    إذا (!s->surfaces_اندروني)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < ctx->initial_pool_سائيز; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_اندروني[i]);
        إذا (ret < 0)
            أرجع ret;
    }

#إذا QSV_HAVE_OPAQUE
    إذا (!(چوکٺا_hwctx->چوکٺو_type & MFX_MEMTYPE_OPAQUE_چوکٺو)) {
        ret = qsv_init_ٻار_ctx(ctx);
        إذا (ret < 0)
            أرجع ret;
    }
#وإلا
    ret = qsv_init_ٻار_ctx(ctx);
    إذا (ret < 0)
        أرجع ret;
#جيڪڏهن_پورو

    ffhwframesctx(ctx)->pool_اندروني = av_بفر_pool_init2(حجم(mfx_چوکٺو_Surface1),
                                                             ctx, qsv_pool_alloc, عدم);
    إذا (!ffhwframesctx(ctx)->pool_اندروني)
        أرجع AVERROR(ENOMEM);

    چوکٺا_hwctx->surfaces    = s->surfaces_اندروني;
    چوکٺا_hwctx->nb_surfaces = ctx->initial_pool_سائيز;

    أرجع 0;
}

ساكن mfx_حالت چوکٺو_alloc(mfxHDL pthis, mfx_چوکٺو_Alloc_Request *req,
                             mfx_چوکٺو_Alloc_Response *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfx_چوکٺو_Info *i  = &req->Info;
    mfx_چوکٺو_Info *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    إذا (!(req->Type & MFX_MEMTYPE_VIDEO_يادگيري_PROCESSOR_هدف) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_چوکٺو))
        أرجع MFX_ERR_UNSUPPORTED;
    إذا (i->ويڪر_2  > i1->ويڪر_2 || i->اوچائي_2 > i1->اوچائي_2 ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->ويڪر_2,  i->اوچائي_2,  i->FourCC,  i->ChromaFormat,
               i1->ويڪر_2, i1->اوچائي_2, i1->FourCC, i1->ChromaFormat);
        أرجع MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->انگ_چوکٺو_Actual = hwctx->nb_surfaces;

    أرجع MFX_ERR_NONE;
}

ساكن mfx_حالت چوکٺو_free(mfxHDL pthis, mfx_چوکٺو_Alloc_Response *resp)
{
    أرجع MFX_ERR_NONE;
}

ساكن mfx_حالت چوکٺو_تالو(mfxHDL pthis, mfxMemId mid, mfx_چوکٺو_معلومات *ptr)
{
    أرجع MFX_ERR_UNSUPPORTED;
}

ساكن mfx_حالت چوکٺو_unlock(mfxHDL pthis, mfxMemId mid, mfx_چوکٺو_معلومات *ptr)
{
    أرجع MFX_ERR_UNSUPPORTED;
}

ساكن mfx_حالت چوکٺو_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->پهريون = pair_src->پهريون;

    إذا (pair_src->ٻيو != (mfxMemId)MFX_INFINITE)
        pair_dst->ٻيو = pair_src->ٻيو;
    أرجع MFX_ERR_NONE;
}

#إذا QSV_ONEVPL

ساكن صحيح qsv_d3d11_update_config(فراغ *ctx, mfxHDL handle, mfxConfig cfg)
{
    صحيح ret = AVERROR_UNKNOWN;
#إذا CONFIG_D3D11VA
    mfx_حالت sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = عدم;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_قدر = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (فراغ**)&pDXGIDevice);
    إذا (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        إذا (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            أرجع ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        إذا (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            اذهب fail;
        }
    } وإلا {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        أرجع ret;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_U16;
    impl_قدر.معلومات_2.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_قدر);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        اذهب fail;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_PTR;
    impl_قدر.معلومات_2.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_قدر);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        اذهب fail;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_U32;
    impl_قدر.معلومات_2.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_قدر);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        اذهب fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#جيڪڏهن_پورو
    أرجع ret;
}

ساكن صحيح qsv_d3d9_update_config(فراغ *ctx, mfxHDL handle, mfxConfig cfg)
{
    صحيح ret = AVERROR_UNKNOWN;
#إذا CONFIG_DXVA2
    mfx_حالت sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = عدم;
    IDirect3DDevice9Ex *device_ex = عدم;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = عدم;
    IDirect3D9 *d3d9 = عدم;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_قدر = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        اذهب fail;
    }

    hr = IDirect3_DDevice_Manager9_تالو_Device(devmgr, device_handle, &device, TRUE);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        اذهب fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (فراغ **)&device_ex);
    IDirect3DDevice9_Release(device);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        اذهب unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        اذهب unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        اذهب unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (فراغ **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        اذهب unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        اذهب release;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_PTR;
    impl_قدر.معلومات_2.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_قدر);
    إذا (sts != MFX_ERR_NONE) {
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
#جيڪڏهن_پورو
    أرجع ret;
}

ساكن صحيح qsv_va_update_config(فراغ *ctx, mfxHDL handle, mfxConfig cfg)
{
#إذا CONFIG_VAAPI
#إذا VA_CHECK_نسخو(1, 15, 0)
    mfx_حالت sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_قدر = {0};

    vas = va_Get_Display_خاصيتون(dpy, &attr, 1);
    إذا (vas == VA_حالت_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_قدر.Type = MFX_VARIANT_TYPE_U16;
        impl_قدر.معلومات_2.U16 = (attr.قدر & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ثابت mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_قدر);
        إذا (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            اذهب fail;
        }
    } وإلا {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        اذهب fail;
    }

    أرجع 0;

fail:
#وإلا
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#جيڪڏهن_پورو
#جيڪڏهن_پورو
    أرجع AVERROR_UNKNOWN;
}

ساكن صحيح qsv_new_mfx_loader(فراغ *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfx_نسخو *pver,
                              فراغ **ploader)
{
    mfx_حالت sts;
    mfxLoader loader = عدم;
    mfxConfig cfg;
    mfxVariant impl_قدر = {0};

    *ploader = عدم;
    loader = MFXLoad();
    إذا (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        اذهب fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    إذا (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        اذهب fail;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_U32;
    impl_قدر.معلومات_2.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.Impl", impl_قدر);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        اذهب fail;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_U32;
    impl_قدر.معلومات_2.U32 = pver->نسخو_2;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_قدر);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        اذهب fail;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_U32;
    impl_قدر.معلومات_2.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.VendorID", impl_قدر);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        اذهب fail;
    }

    إذا (MFX_HANDLE_VA_DISPLAY == handle_type) {
        إذا (handle && qsv_va_update_config(ctx, handle, cfg))
            اذهب fail;

        impl_قدر.معلومات_2.U32 = MFX_ACCEL_گهڻائي_ذريعي_VAAPI;
    } وإلا إذا (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        إذا (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            اذهب fail;

        impl_قدر.معلومات_2.U32 = MFX_ACCEL_گهڻائي_ذريعي_D3_D9;
    } وإلا {
        إذا (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            اذهب fail;

        impl_قدر.معلومات_2.U32 = MFX_ACCEL_گهڻائي_ذريعي_D3_D11;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.AccelerationMode", impl_قدر);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        اذهب fail;
    }

    *ploader = loader;

    أرجع 0;

fail:
    إذا (loader)
        MFXUnload(loader);

    أرجع AVERROR_UNKNOWN;
}

ساكن صحيح qsv_create_mfx_session_from_loader(فراغ *ctx, mfxLoader loader, mfxSession *psession)
{
    mfx_حالت sts;
    mfxSession session = عدم;
    uint32_t impl_idx = 0;
    mfx_نسخو ver;

    طالما (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        إذا (sts == MFX_ERR_NOT_مليو)
            اكسر;
        وإلا إذا (sts != MFX_ERR_NONE) {
            impl_idx++;
            استمر;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        إذا (sts == MFX_ERR_NONE)
            اكسر;

        impl_idx++;
    }

    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        اذهب fail;
    }

    sts = MFXQuery_نسخو(session, &ver);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        اذهب fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    أرجع 0;

fail:
    إذا (session)
        MFXClose(session);

    أرجع AVERROR_UNKNOWN;
}

ساكن صحيح qsv_create_mfx_session(فراغ *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfx_نسخو *pver,
                                  mfxSession *psession,
                                  فراغ **ploader)
{
    mfxLoader loader = عدم;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_نسخو_MAJOR, MFX_نسخو_MINOR, pver->Major, pver->Minor);

    إذا (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        أرجع AVERROR(EXDEV);
    }

    *psession = عدم;

    إذا (!*ploader) {
        إذا (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (فراغ **)&loader))
            اذهب fail;

        av_assert0(loader);
    } وإلا
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    إذا (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        اذهب fail;

    إذا (!*ploader)
        *ploader = loader;

    أرجع 0;

fail:
    إذا (!*ploader && loader)
        MFXUnload(loader);

    أرجع AVERROR_UNKNOWN;
}

#وإلا

ساكن صحيح qsv_create_mfx_session(فراغ *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfx_نسخو *pver,
                                  mfxSession *psession,
                                  فراغ **ploader)
{
    mfx_نسخو ver;
    mfx_حالت sts;
    mfxSession session = عدم;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_نسخو_MAJOR, MFX_نسخو_MINOR, pver->Major, pver->Minor);

    *ploader = عدم;
    *psession = عدم;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        اذهب fail;
    }

    sts = MFXQuery_نسخو(session, &ver);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        اذهب fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        اذهب fail;
    }

    *psession = session;

    أرجع 0;

fail:
    إذا (session)
        MFXClose(session);

    أرجع AVERROR_UNKNOWN;
}

#جيڪڏهن_پورو

ساكن صحيح qsv_init_اندروني_session(AVHWFramesContext *ctx,
                                     mfxSession *session, صحيح upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *چوکٺا_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    صحيح opaque = 0;

    mfx_چوکٺو_Allocator چوکٺو_allocator = {
        .pthis  = ctx,
        .Alloc  = چوکٺو_alloc,
        .تالو_2   = چوکٺو_تالو,
        .Unlock = چوکٺو_unlock,
        .GetHDL = چوکٺو_get_hdl,
        .Free   = چوکٺو_free,
    };

    mfxVideoParam par;
    mfx_حالت err;
    صحيح                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    فراغ             **loader = &hwctx->loader;
    mfxSession والد_session = hwctx->session;
    mfxIMPL impl;
    mfx_نسخو ver;

    err = MFXQueryIMPL(والد_session, &impl);
    إذا (err == MFX_ERR_NONE)
        err = MFXQuery_نسخو(والد_session, &ver);
    إذا (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        أرجع AVERROR_UNKNOWN;
    }

#إذا QSV_HAVE_OPAQUE
    opaque = !!(چوکٺا_hwctx->چوکٺو_type & MFX_MEMTYPE_OPAQUE_چوکٺو);
#جيڪڏهن_پورو

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    إذا (ret)
        اذهب fail;

    إذا (device_priv->handle) {
        err = MFXVideo_CORE_سيٽ_Handle(*session, device_priv->handle_type,
                                     device_priv->handle);
        إذا (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            اذهب fail;
        }
    }

    إذا (QSV_RUNTIME_نسخو_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(والد_session, *session);
        إذا (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            اذهب fail;
        }
    }

    إذا (!opaque) {
        err = MFXVideo_CORE_سيٽ_چوکٺو_Allocator(*session, &چوکٺو_allocator);
        إذا (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            اذهب fail;
        }
    }

    memset(&par, 0, حجم(par));

    إذا (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_ٻاهريون_VIDEO_يادگيري :
                                 MFX_IOPATTERN_اندريون_VIDEO_يادگيري;
    }
#إذا QSV_HAVE_OPAQUE
    وإلا {
        par.ExtParam    = s->ext_buffers;
        par.انگ_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
        par.IOPattern   = upload ? MFX_IOPATTERN_ٻاهريون_OPAQUE_يادگيري :
                                   MFX_IOPATTERN_اندريون_OPAQUE_يادگيري;
    }
#جيڪڏهن_پورو

    par.IOPattern |= upload ? MFX_IOPATTERN_اندريون_SYSTEM_يادگيري :
                              MFX_IOPATTERN_ٻاهريون_SYSTEM_يادگيري;
    par.Async_اونهائي = 1;

    par.vpp.اندريون_2 = چوکٺا_hwctx->nb_surfaces ? چوکٺا_hwctx->surfaces[0].Info : *چوکٺا_hwctx->info;

    /* Apparently VPP requires the frame rate to be set to some value, otherwise
     * init will fail (probably for the framerate conversion filter). Since we
     * are only doing data upload/download here, we just invent an arbitrary
     * value */
    par.vpp.اندريون_2.چوکٺو_شرح_Ext_N = 25;
    par.vpp.اندريون_2.چوکٺو_شرح_Ext_D = 1;
    par.vpp.ٻاهريون_2 = par.vpp.اندريون_2;

    err = MFXVideoVPP_Init(*session, &par);
    إذا (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        اذهب fail;
    }

    أرجع 0;

fail:
    إذا (*session)
        MFXClose(*session);

    *session = عدم;

    أرجع ret;
}

ساكن صحيح qsv_چوکٺا_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *چوکٺا_hwctx = &s->p;

    صحيح opaque = 0;

    uint32_t fourcc;
    صحيح i, ret;

#إذا QSV_HAVE_OPAQUE
    opaque = !!(چوکٺا_hwctx->چوکٺو_type & MFX_MEMTYPE_OPAQUE_چوکٺو);
#جيڪڏهن_پورو

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    إذا (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        أرجع AVERROR(ENOSYS);
    }

    إذا (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        إذا (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            أرجع ret;
        }
    }

    إذا (!opaque) {
        s->mem_ids = av_calloc(چوکٺا_hwctx->nb_surfaces, حجم(*s->mem_ids));
        إذا (!s->mem_ids)
            أرجع AVERROR(ENOMEM);

        لكل (i = 0; i < چوکٺا_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = چوکٺا_hwctx->surfaces[i].معلومات_2.MemId;
    }
#إذا QSV_HAVE_OPAQUE
    وإلا {
        s->surface_ptrs = av_calloc(چوکٺا_hwctx->nb_surfaces,
                                    حجم(*s->surface_ptrs));
        إذا (!s->surface_ptrs)
            أرجع AVERROR(ENOMEM);

        لكل (i = 0; i < چوکٺا_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = چوکٺا_hwctx->surfaces + i;

        s->opaque_alloc.اندريون_2.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.اندريون_2.انگ_Surface = چوکٺا_hwctx->nb_surfaces;
        s->opaque_alloc.اندريون_2.Type       = چوکٺا_hwctx->چوکٺو_type;

        s->opaque_alloc.ٻاهريون_2 = s->opaque_alloc.اندريون_2;

        s->opaque_alloc.سرو_2.بفر_Id = MFX_EXTBUFF_OPAQUE_SURFACE_ورهاست;
        s->opaque_alloc.سرو_2.بفر_Sz = حجم(s->opaque_alloc);

        s->ext_buffers[0] = (mfx_Ext_بفر*)&s->opaque_alloc;
    }
#جيڪڏهن_پورو

    s->session_download = عدم;
    s->session_upload   = عدم;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#إذا HAVE_PTHREADS
    pthread_mutex_init(&s->session_تالو, عدم);
#جيڪڏهن_پورو

    أرجع 0;
}

ساكن صحيح qsv_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکٺو)
{
    چوکٺو->buf[0] = av_بفر_pool_get(ctx->pool);
    إذا (!چوکٺو->buf[0])
        أرجع AVERROR(ENOMEM);

    چوکٺو->معلومات[3] = چوکٺو->buf[0]->معلومات;
    چوکٺو->format  = AV_PIX_FMT_QSV;
    چوکٺو->ويڪر   = ctx->ويڪر;
    چوکٺو->اوچائي  = ctx->اوچائي;

    أرجع 0;
}

ساكن صحيح qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    تعداد AVHWFrameTransferDirection dir,
                                    تعداد AVPixelFormat **formats)
{
    تعداد AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    إذا (!fmts)
        أرجع AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    أرجع 0;
}

ساكن صحيح qsv_چوکٺا_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, صحيح flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    صحيح i;

    بدل (dst_ctx->device_ctx->type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               حجم(*dst_hwctx->surface_ids));
            إذا (!dst_hwctx->surface_ids)
                أرجع AVERROR(ENOMEM);
            لكل (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].معلومات_2.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->پهريون;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        اكسر;
#جيڪڏهن_پورو
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_سائيز = src_ctx->initial_pool_سائيز;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 حجم(*dst_hwctx->texture_infos));
            إذا (!dst_hwctx->texture_infos)
                أرجع AVERROR(ENOMEM);
            إذا (src_hwctx->چوکٺو_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            لكل (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].معلومات_2.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->پهريون;
                dst_hwctx->texture_infos[i].اشاريو = pair->ٻيو == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->ٻيو;
            }
            إذا (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } وإلا
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->چوکٺو_type);
        }
        اكسر;
#جيڪڏهن_پورو
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_چوکٺا_Context *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            حجم(*dst_hwctx->surfaces));
            إذا (!dst_hwctx->surfaces)
                أرجع AVERROR(ENOMEM);
            لكل (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].معلومات_2.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->پهريون;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            إذا (src_hwctx->چوکٺو_type == MFX_MEMTYPE_VIDEO_يادگيري_DECODER_هدف)
                dst_hwctx->surface_type = DXVA2_Video_Decoder_Render_هدف;
            وإلا
                dst_hwctx->surface_type = DXVA2_Video_Processor_Render_هدف;
        }
        اكسر;
#جيڪڏهن_پورو
    افتراضي:
        أرجع AVERROR(ENOSYS);
    }

    أرجع 0;
}

ساكن صحيح qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfx_چوکٺو_Surface1 *surf = (mfx_چوکٺو_Surface1*)src->معلومات[3];
    AVHWFramesContext *ٻار_چوکٺا_ctx;
    ثابت AVPixFmtDescriptor *desc;
    uint8_t *ٻار_معلومات;
    AVFrame *dummy;
    صحيح ret = 0;

    إذا (!s->ٻار_چوکٺا_ref)
        أرجع AVERROR(ENOSYS);
    ٻار_چوکٺا_ctx = (AVHWFramesContext*)s->ٻار_چوکٺا_ref->معلومات;

    بدل (ٻار_چوکٺا_ctx->device_ctx->type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->معلومات_2.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        ٻار_معلومات = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->پهريون;
        اكسر;
    }
#جيڪڏهن_پورو
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->معلومات_2.MemId;
        ٻار_معلومات = pair->پهريون;
        اكسر;
    }
#جيڪڏهن_پورو
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->معلومات_2.MemId;
        ٻار_معلومات = pair->پهريون;
        اكسر;
    }
#جيڪڏهن_پورو
    افتراضي:
        أرجع AVERROR(ENOSYS);
    }

    إذا (dst->format == ٻار_چوکٺا_ctx->format) {
        ret = ff_hwframe_map_create(s->ٻار_چوکٺا_ref,
                                    dst, src, عدم, عدم);
        إذا (ret < 0)
            أرجع ret;

        dst->ويڪر   = src->ويڪر;
        dst->اوچائي  = src->اوچائي;

       إذا (ٻار_چوکٺا_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->معلومات_2.MemId;
            dst->معلومات[0] = pair->پهريون;
            dst->معلومات[1] = pair->ٻيو == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->ٻيو;
        } وإلا {
            dst->معلومات[3] = ٻار_معلومات;
        }

        أرجع 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    إذا (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        أرجع AVERROR(ENOSYS);
    }

    dummy = av_چوکٺو_alloc();
    إذا (!dummy)
        أرجع AVERROR(ENOMEM);

    dummy->buf[0]        = av_بفر_ref(src->buf[0]);
    dummy->hw_چوکٺا_ctx = av_بفر_ref(s->ٻار_چوکٺا_ref);
    إذا (!dummy->buf[0] || !dummy->hw_چوکٺا_ctx)
        اذهب fail;

    dummy->format        = ٻار_چوکٺا_ctx->format;
    dummy->ويڪر         = src->ويڪر;
    dummy->اوچائي        = src->اوچائي;

    إذا (ٻار_چوکٺا_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->معلومات_2.MemId;
        dummy->معلومات[0] = pair->پهريون;
        dummy->معلومات[1] = pair->ٻيو == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->ٻيو;
    } وإلا {
        dummy->معلومات[3] = ٻار_معلومات;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_چوکٺو_free(&dummy);

    أرجع ret;
}

ساكن صحيح qsv_transfer_معلومات_ٻار(AVHWFramesContext *ctx, AVFrame *dst,
                                   ثابت AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *ٻار_چوکٺا_ctx = (AVHWFramesContext*)s->ٻار_چوکٺا_ref->معلومات;
    صحيح download = !!src->hw_چوکٺا_ctx;
    mfx_چوکٺو_Surface1 *surf = (mfx_چوکٺو_Surface1*)(download ? src->معلومات[3] : dst->معلومات[3]);

    AVFrame *dummy;
    صحيح ret;

    dummy = av_چوکٺو_alloc();
    إذا (!dummy)
        أرجع AVERROR(ENOMEM);

    dummy->format        = ٻار_چوکٺا_ctx->format;
    dummy->ويڪر         = src->ويڪر;
    dummy->اوچائي        = src->اوچائي;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->معلومات[3]       = surf->معلومات_2.MemId;
    dummy->hw_چوکٺا_ctx = s->ٻار_چوکٺا_ref;

    ret = download ? av_hwframe_transfer_معلومات(dst, dummy, 0) :
                     av_hwframe_transfer_معلومات(dummy, src, 0);

    dummy->buf[0]        = عدم;
    dummy->معلومات[3]       = عدم;
    dummy->hw_چوکٺا_ctx = عدم;

    av_چوکٺو_free(&dummy);

    أرجع ret;
}

ساكن صحيح map_چوکٺو_منزل_surface(ثابت AVFrame *چوکٺو, mfx_چوکٺو_Surface1 *surface)
{
    بدل (چوکٺو->format) {
    حالة AV_PIX_FMT_NV12:
    حالة AV_PIX_FMT_P010:
    حالة AV_PIX_FMT_P012:
        surface->معلومات_2.Y  = چوکٺو->معلومات[0];
        surface->معلومات_2.UV = چوکٺو->معلومات[1];
        اكسر;

    حالة AV_PIX_FMT_YUV420P:
        surface->معلومات_2.Y = چوکٺو->معلومات[0];
        surface->معلومات_2.U = چوکٺو->معلومات[1];
        surface->معلومات_2.V = چوکٺو->معلومات[2];
        اكسر;

    حالة AV_PIX_FMT_BGRA:
        surface->معلومات_2.B = چوکٺو->معلومات[0];
        surface->معلومات_2.G = چوکٺو->معلومات[0] + 1;
        surface->معلومات_2.R = چوکٺو->معلومات[0] + 2;
        surface->معلومات_2.A = چوکٺو->معلومات[0] + 3;
        اكسر;
    حالة AV_PIX_FMT_YUYV422:
        surface->معلومات_2.Y = چوکٺو->معلومات[0];
        surface->معلومات_2.U = چوکٺو->معلومات[0] + 1;
        surface->معلومات_2.V = چوکٺو->معلومات[0] + 3;
        اكسر;

    حالة AV_PIX_FMT_Y210:
    حالة AV_PIX_FMT_Y212:
        surface->معلومات_2.Y16 = (mfxU16 *)چوکٺو->معلومات[0];
        surface->معلومات_2.U16 = (mfxU16 *)چوکٺو->معلومات[0] + 1;
        surface->معلومات_2.V16 = (mfxU16 *)چوکٺو->معلومات[0] + 3;
        اكسر;
    حالة AV_PIX_FMT_VUYX:
        surface->معلومات_2.V = چوکٺو->معلومات[0];
        surface->معلومات_2.U = چوکٺو->معلومات[0] + 1;
        surface->معلومات_2.Y = چوکٺو->معلومات[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->معلومات_2.A = چوکٺو->معلومات[0] + 3;
        اكسر;
    حالة AV_PIX_FMT_XV30:
        surface->معلومات_2.U = چوکٺو->معلومات[0];
        اكسر;
    حالة AV_PIX_FMT_XV36:
        surface->معلومات_2.U = چوکٺو->معلومات[0];
        surface->معلومات_2.Y = چوکٺو->معلومات[0] + 2;
        surface->معلومات_2.V = چوکٺو->معلومات[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->معلومات_2.A = چوکٺو->معلومات[0] + 6;
        اكسر;
#إذا CONFIG_VAAPI
    حالة AV_PIX_FMT_UYVY422:
        surface->معلومات_2.Y = چوکٺو->معلومات[0] + 1;
        surface->معلومات_2.U = چوکٺو->معلومات[0];
        surface->معلومات_2.V = چوکٺو->معلومات[0] + 2;
        اكسر;
#جيڪڏهن_پورو
    افتراضي:
        أرجع MFX_ERR_UNSUPPORTED;
    }
    surface->معلومات_2.Pitch     = چوکٺو->linesize[0];
    surface->معلومات_2.وقت_Stamp = چوکٺو->pts;

    أرجع 0;
}

ساكن صحيح qsv_اندروني_session_check_init(AVHWFramesContext *ctx, صحيح upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    صحيح ret = 0;

    إذا (atomic_load(inited))
        أرجع 0;

#إذا HAVE_PTHREADS
    pthread_mutex_تالو(&s->session_تالو);
#جيڪڏهن_پورو

    إذا (!atomic_load(inited)) {
        ret = qsv_init_اندروني_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#إذا HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_تالو);
#جيڪڏهن_پورو

    أرجع ret;
}

ساكن صحيح qsv_transfer_معلومات_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ثابت AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfx_چوکٺو_Surface1 ٻاهريون = {{ 0 }};
    mfx_چوکٺو_Surface1 *اندريون = (mfx_چوکٺو_Surface1*)src->معلومات[3];

    mfx_Sync_نقطو sync = عدم;
    mfx_حالت err;
    صحيح ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_چوکٺو = &s->realigned_download_چوکٺو;
    AVFrame *dst_چوکٺو;
    صحيح realigned = 0;

    ret = qsv_اندروني_session_check_init(ctx, 0);
    إذا (ret < 0)
        أرجع ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    إذا (dst->اوچائي & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        إذا (tmp_چوکٺو->format != dst->format ||
            tmp_چوکٺو->ويڪر  != FFALIGN(dst->linesize[0], 16) ||
            tmp_چوکٺو->اوچائي != FFALIGN(dst->اوچائي, 16)) {
            av_چوکٺو_unref(tmp_چوکٺو);

            tmp_چوکٺو->format = dst->format;
            tmp_چوکٺو->ويڪر  = FFALIGN(dst->linesize[0], 16);
            tmp_چوکٺو->اوچائي = FFALIGN(dst->اوچائي, 16);
            ret = av_چوکٺو_get_بفر(tmp_چوکٺو, 0);
            إذا (ret < 0)
                أرجع ret;
        }
    }

    dst_چوکٺو = realigned ? tmp_چوکٺو : dst;

    إذا (!s->session_download) {
        إذا (s->ٻار_چوکٺا_ref)
            أرجع qsv_transfer_معلومات_ٻار(ctx, dst_چوکٺو, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        أرجع AVERROR(ENOSYS);
    }

    ٻاهريون.Info = اندريون->Info;
    map_چوکٺو_منزل_surface(dst_چوکٺو, &ٻاهريون);

    افعل {
        err = MFXVideo_VPP_لاڳيتو_چوکٺو_VPPAsync(s->session_download, اندريون, &ٻاهريون, عدم, &sync);
        إذا (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } طالما (err == MFX_WRN_DEVICE_BUSY);

    إذا (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        أرجع AVERROR_UNKNOWN;
    }

    افعل {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } طالما (err == MFX_WRN_اندريون_EXECUTION);
    إذا (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        أرجع AVERROR_UNKNOWN;
    }

    إذا (realigned) {
        tmp_چوکٺو->ويڪر  = dst->ويڪر;
        tmp_چوکٺو->اوچائي = dst->اوچائي;
        ret = av_چوکٺو_copy(dst, tmp_چوکٺو);
        tmp_چوکٺو->ويڪر  = FFALIGN(dst->linesize[0], 16);
        tmp_چوکٺو->اوچائي = FFALIGN(dst->اوچائي, 16);
        إذا (ret < 0)
            أرجع ret;
    }

    أرجع 0;
}

ساكن صحيح qsv_transfer_معلومات_منزل(AVHWFramesContext *ctx, AVFrame *dst,
                                ثابت AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfx_چوکٺو_Surface1   اندريون = {{ 0 }};
    mfx_چوکٺو_Surface1 *ٻاهريون = (mfx_چوکٺو_Surface1*)dst->معلومات[3];
    mfx_چوکٺو_Info tmp_info;

    mfx_Sync_نقطو sync = عدم;
    mfx_حالت err;
    صحيح ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_چوکٺو = &s->realigned_upload_چوکٺو;
    ثابت AVFrame *src_چوکٺو;
    صحيح realigned = 0;

    ret = qsv_اندروني_session_check_init(ctx, 1);
    إذا (ret < 0)
        أرجع ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    إذا (src->اوچائي & 15 || src->linesize[0] & 15) {
        realigned = 1;
        إذا (tmp_چوکٺو->format != src->format ||
            tmp_چوکٺو->ويڪر  != FFALIGN(src->ويڪر, 16) ||
            tmp_چوکٺو->اوچائي != FFALIGN(src->اوچائي, 16)) {
            av_چوکٺو_unref(tmp_چوکٺو);

            tmp_چوکٺو->format = src->format;
            tmp_چوکٺو->ويڪر  = FFALIGN(src->ويڪر, 16);
            tmp_چوکٺو->اوچائي = FFALIGN(src->اوچائي, 16);
            ret = av_چوکٺو_get_بفر(tmp_چوکٺو, 0);
            إذا (ret < 0)
                أرجع ret;
        }
        ret = av_چوکٺو_copy(tmp_چوکٺو, src);
        إذا (ret < 0) {
            av_چوکٺو_unref(tmp_چوکٺو);
            أرجع ret;
        }
        ret = qsv_fill_border(tmp_چوکٺو, src);
        إذا (ret < 0) {
            av_چوکٺو_unref(tmp_چوکٺو);
            أرجع ret;
        }

        tmp_info = ٻاهريون->Info;
        ٻاهريون->Info.CropW = FFMIN(ٻاهريون->Info.ويڪر_2,  tmp_چوکٺو->ويڪر);
        ٻاهريون->Info.CropH = FFMIN(ٻاهريون->Info.اوچائي_2, tmp_چوکٺو->اوچائي);
    }

    src_چوکٺو = realigned ? tmp_چوکٺو : src;

    إذا (!s->session_upload) {
        إذا (s->ٻار_چوکٺا_ref)
            أرجع qsv_transfer_معلومات_ٻار(ctx, dst, src_چوکٺو);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        أرجع AVERROR(ENOSYS);
    }

    اندريون.Info = ٻاهريون->Info;
    map_چوکٺو_منزل_surface(src_چوکٺو, &اندريون);

    افعل {
        err = MFXVideo_VPP_لاڳيتو_چوکٺو_VPPAsync(s->session_upload, &اندريون, ٻاهريون, عدم, &sync);
        إذا (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } طالما (err == MFX_WRN_DEVICE_BUSY);

    إذا (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        أرجع AVERROR_UNKNOWN;
    }

    افعل {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } طالما (err == MFX_WRN_اندريون_EXECUTION);
    إذا (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        أرجع AVERROR_UNKNOWN;
    }

    إذا (realigned) {
        ٻاهريون->Info.CropW = tmp_info.CropW;
        ٻاهريون->Info.CropH = tmp_info.CropH;
    }

    أرجع 0;
}

ساكن صحيح qsv_dynamic_چوکٺا_derive_منزل(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, صحيح flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfx_چوکٺو_Surface1 mfx_surf1;

    بدل (src_ctx->device_ctx->type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->چوکٺو_type  = MFX_MEMTYPE_VIDEO_يادگيري_DECODER_هدف;
        اكسر;
#جيڪڏهن_پورو

#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        إذا (src_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف) {
            dst_hwctx->چوکٺو_type |= MFX_MEMTYPE_VIDEO_يادگيري_PROCESSOR_هدف;
        } وإلا {
            dst_hwctx->چوکٺو_type |= MFX_MEMTYPE_VIDEO_يادگيري_DECODER_هدف;
        }
    }
    اكسر;
#جيڪڏهن_پورو

    افتراضي:
        أرجع AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, حجم(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->چوکٺو_info = mfx_surf1.Info;
    dst_hwctx->info = &s->چوکٺو_info;
    dst_hwctx->nb_surfaces = 0;
    أرجع 0;
}

ساكن صحيح qsv_fixed_چوکٺا_derive_منزل(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, صحيح flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    صحيح i;

    بدل (src_ctx->device_ctx->type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_جوڙا_اندروني = av_calloc(src_ctx->initial_pool_سائيز,
                                                 حجم(*s->handle_جوڙا_اندروني));
            إذا (!s->handle_جوڙا_اندروني)
                أرجع AVERROR(ENOMEM);
            s->surfaces_اندروني = av_calloc(src_hwctx->nb_surfaces,
                                             حجم(*s->surfaces_اندروني));
            إذا (!s->surfaces_اندروني)
                أرجع AVERROR(ENOMEM);
            لكل (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_اندروني[i]);
                s->handle_جوڙا_اندروني[i].پهريون = src_hwctx->surface_ids + i;
                s->handle_جوڙا_اندروني[i].ٻيو = (mfxMemId)MFX_INFINITE;
                s->surfaces_اندروني[i].معلومات_2.MemId = (mfxMemId)&s->handle_جوڙا_اندروني[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->چوکٺو_type  = MFX_MEMTYPE_VIDEO_يادگيري_DECODER_هدف;
        }
        اكسر;
#جيڪڏهن_پورو
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_جوڙا_اندروني = av_calloc(src_ctx->initial_pool_سائيز,
                                                 حجم(*s->handle_جوڙا_اندروني));
            إذا (!s->handle_جوڙا_اندروني)
                أرجع AVERROR(ENOMEM);
            s->surfaces_اندروني = av_calloc(src_ctx->initial_pool_سائيز,
                                             حجم(*s->surfaces_اندروني));
            إذا (!s->surfaces_اندروني)
                أرجع AVERROR(ENOMEM);
            لكل (i = 0; i < src_ctx->initial_pool_سائيز; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_اندروني[i]);
                s->handle_جوڙا_اندروني[i].پهريون = (mfxMemId)src_hwctx->texture_infos[i].texture;
                إذا (src_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف) {
                    s->handle_جوڙا_اندروني[i].ٻيو = (mfxMemId)MFX_INFINITE;
                } وإلا {
                    s->handle_جوڙا_اندروني[i].ٻيو = (mfxMemId)src_hwctx->texture_infos[i].اشاريو;
                }
                s->surfaces_اندروني[i].معلومات_2.MemId = (mfxMemId)&s->handle_جوڙا_اندروني[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_سائيز;
            إذا (src_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف) {
                dst_hwctx->چوکٺو_type |= MFX_MEMTYPE_VIDEO_يادگيري_PROCESSOR_هدف;
            } وإلا {
                dst_hwctx->چوکٺو_type |= MFX_MEMTYPE_VIDEO_يادگيري_DECODER_هدف;
            }
        }
        اكسر;
#جيڪڏهن_پورو
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_چوکٺا_Context *src_hwctx = src_ctx->hwctx;
            s->handle_جوڙا_اندروني = av_calloc(src_ctx->initial_pool_سائيز,
                                                 حجم(*s->handle_جوڙا_اندروني));
            إذا (!s->handle_جوڙا_اندروني)
                أرجع AVERROR(ENOMEM);
            s->surfaces_اندروني = av_calloc(src_hwctx->nb_surfaces,
                                             حجم(*s->surfaces_اندروني));
            إذا (!s->surfaces_اندروني)
                أرجع AVERROR(ENOMEM);
            لكل (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_اندروني[i]);
                s->handle_جوڙا_اندروني[i].پهريون = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_جوڙا_اندروني[i].ٻيو = (mfxMemId)MFX_INFINITE;
                s->surfaces_اندروني[i].معلومات_2.MemId = (mfxMemId)&s->handle_جوڙا_اندروني[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            إذا (src_hwctx->surface_type == DXVA2_Video_Processor_Render_هدف)
                dst_hwctx->چوکٺو_type = MFX_MEMTYPE_VIDEO_يادگيري_PROCESSOR_هدف;
            وإلا
                dst_hwctx->چوکٺو_type = MFX_MEMTYPE_VIDEO_يادگيري_DECODER_هدف;
        }
        اكسر;
#جيڪڏهن_پورو
    افتراضي:
        أرجع AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_اندروني;

    أرجع 0;
}

ساكن صحيح qsv_چوکٺا_derive_منزل(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, صحيح flags)
{
    إذا (src_ctx->initial_pool_سائيز < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        أرجع AVERROR(EINVAL);
    } وإلا إذا (src_ctx->initial_pool_سائيز == 0) {
        أرجع qsv_dynamic_چوکٺا_derive_منزل(dst_ctx, src_ctx, flags);
    } وإلا {
        أرجع qsv_fixed_چوکٺا_derive_منزل(dst_ctx, src_ctx, flags);
    }
}

ساكن صحيح qsv_fixed_pool_map_منزل(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    صحيح i, err, اشاريو = -1;

    لكل (i = 0; i < hwctx->nb_surfaces && اشاريو < 0; i++) {
        بدل(src->format) {
#إذا CONFIG_VAAPI
        حالة AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].معلومات_2.MemId;
            إذا (*(VASurfaceID*)pair->پهريون == (VASurfaceID)(uintptr_t)src->معلومات[3])
                اشاريو = i;
            اكسر;
        }
#جيڪڏهن_پورو
#إذا CONFIG_D3D11VA
        حالة AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].معلومات_2.MemId;
            إذا (pair->پهريون == src->معلومات[0]
                && (pair->ٻيو == src->معلومات[1]
                    || (pair->ٻيو == (mfxMemId)MFX_INFINITE && src->معلومات[1] == (uint8_t *)0)))
                اشاريو = i;
            اكسر;
        }
#جيڪڏهن_پورو
#إذا CONFIG_DXVA2
        حالة AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].معلومات_2.MemId;
            إذا (pair->پهريون == src->معلومات[3])
                اشاريو = i;
            اكسر;
        }
#جيڪڏهن_پورو
        }
    }
    إذا (اشاريو < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        أرجع AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_چوکٺا_ctx,
                                dst, src, عدم, عدم);
    إذا (err)
        أرجع err;

    dst->ويڪر   = src->ويڪر;
    dst->اوچائي  = src->اوچائي;
    dst->معلومات[3] = (uint8_t*)&hwctx->surfaces[اشاريو];

    أرجع 0;
}

ساكن فراغ qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfx_چوکٺو_Surface1 *surfaces_اندروني = (mfx_چوکٺو_Surface1 *)hwmap->priv;
    mfxHDLPair *handle_جوڙا_اندروني = (mfxHDLPair *)surfaces_اندروني->معلومات_2.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->ذريعو_چوکٺا->معلومات;

    بدل (src_ctx->format) {
#إذا CONFIG_VAAPI
    حالة AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_جوڙا_اندروني->پهريون);

        اكسر;
    }
#جيڪڏهن_پورو

#إذا CONFIG_D3D11VA
    حالة AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        اكسر;
    }
#جيڪڏهن_پورو
    افتراضي:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        اكسر;
    }

    av_freep(&handle_جوڙا_اندروني);
    av_freep(&surfaces_اندروني);
}

ساكن صحيح qsv_dynamic_pool_map_منزل(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    mfx_چوکٺو_Surface1 *surfaces_اندروني = عدم;
    mfxHDLPair *handle_جوڙا_اندروني = عدم;
    صحيح ret = 0;

    surfaces_اندروني = av_calloc(1, حجم(*surfaces_اندروني));
    إذا (!surfaces_اندروني) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    handle_جوڙا_اندروني = av_calloc(1, حجم(*handle_جوڙا_اندروني));
    إذا (!handle_جوڙا_اندروني) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_اندروني);
    إذا (ret < 0)
        اذهب fail;

    بدل (src->format) {
#إذا CONFIG_VAAPI
    حالة AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_اندروني;

        surface_id_اندروني = av_calloc(1, حجم(*surface_id_اندروني));
        إذا (!surface_id_اندروني) {
            ret =AVERROR(ENOMEM);
            اذهب fail;
        }

        *surface_id_اندروني = (VASurfaceID)(uintptr_t)src->معلومات[3];
        handle_جوڙا_اندروني->پهريون = (mfxHDL)surface_id_اندروني;
        handle_جوڙا_اندروني->ٻيو = (mfxMemId)MFX_INFINITE;

        اكسر;
    }
#جيڪڏهن_پورو

#إذا CONFIG_D3D11VA
    حالة AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_چوکٺا_ctx->معلومات;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_جوڙا_اندروني->پهريون = (mfxMemId)src->معلومات[0];

        إذا (src_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف) {
            handle_جوڙا_اندروني->ٻيو = (mfxMemId)MFX_INFINITE;
        } وإلا {
            handle_جوڙا_اندروني->ٻيو = (mfxMemId)src->معلومات[1];
        }

        اكسر;
    }
#جيڪڏهن_پورو
    افتراضي:
        ret = AVERROR(ENOSYS);
        اذهب fail;
    }

    surfaces_اندروني->معلومات_2.MemId = (mfxMemId)handle_جوڙا_اندروني;

    ret = ff_hwframe_map_create(dst->hw_چوکٺا_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_اندروني);
    إذا (ret)
        اذهب fail;

    dst->ويڪر   = src->ويڪر;
    dst->اوچائي  = src->اوچائي;
    dst->معلومات[3] = (uint8_t*)surfaces_اندروني;

    أرجع 0;

fail:
    av_freep(&handle_جوڙا_اندروني);
    av_freep(&surfaces_اندروني);
    أرجع ret;
}

ساكن صحيح qsv_map_منزل(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    إذا (hwctx->nb_surfaces)
        أرجع qsv_fixed_pool_map_منزل(dst_ctx, dst, src, flags);
    وإلا
        أرجع qsv_dynamic_pool_map_منزل(dst_ctx, dst, src, flags);
}

ساكن صحيح qsv_چوکٺا_get_constraints(AVHWDeviceContext *ctx,
                                      ثابت فراغ *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    صحيح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    إذا (!constraints->valid_sw_formats)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    إذا (!constraints->valid_hw_formats)
        أرجع AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    أرجع 0;
}

ساكن فراغ qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    إذا (hwctx->session)
        MFXClose(hwctx->session);

    إذا (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_بفر_unref(&priv->ٻار_device_ctx);
    av_freep(&priv);
}

ساكن mfxIMPL چونڊيو_implementation(ثابت حرف *device, تعداد AVHWDeviceType ٻار_device_type)
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

    إذا (device) {
        لكل (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            إذا (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                اكسر;
            }
        إذا (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, عدم, 0);
    }

    إذا (impl != MFX_IMPL_SOFTWARE) {
        إذا (ٻار_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_ذريعي_D3_D11;
        وإلا إذا (ٻار_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_ذريعي_D3_D9;
    }

    أرجع impl;
}

ساكن صحيح qsv_device_derive_from_ٻار(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *ٻار_device_ctx,
                                        صحيح flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfx_نسخو    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfx_حالت     err;
    صحيح ret;

    بدل (ٻار_device_ctx->type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *ٻار_device_hwctx = ٻار_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)ٻار_device_hwctx->display;
        }
        اكسر;
#جيڪڏهن_پورو
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *ٻار_device_hwctx = ٻار_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)ٻار_device_hwctx->device;
        }
        اكسر;
#جيڪڏهن_پورو
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *ٻار_device_hwctx = ٻار_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)ٻار_device_hwctx->devmgr;
        }
        اكسر;
#جيڪڏهن_پورو
    افتراضي:
        ret = AVERROR(ENOSYS);
        اذهب fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    إذا (ret)
        اذهب fail;

    err = MFXVideo_CORE_سيٽ_Handle(hwctx->session, handle_type, handle);
    إذا (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        اذهب fail;
    }

    أرجع 0;

fail:
    إذا (hwctx->session)
        MFXClose(hwctx->session);

    إذا (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = عدم;
    hwctx->loader = عدم;
    أرجع ret;
}

ساكن صحيح qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *ٻار_device_ctx,
                             AVDictionary *opts, صحيح flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(حجم(*priv));
    إذا (!priv)
        أرجع AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->حرر = qsv_device_free;

    impl = چونڊيو_implementation("hw_any", ٻار_device_ctx->type);
    أرجع qsv_device_derive_from_ٻار(ctx, impl,
                                        ٻار_device_ctx, flags);
}

ساكن صحيح qsv_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                             AVDictionary *opts, صحيح flags)
{
    QSVDevicePriv *priv;
    تعداد AVHWDeviceType ٻار_device_type;
    AVHWDeviceContext *ٻار_device;
    AVDictionary *ٻار_device_opts;
    AVDictionary_داخلا *e;

    mfxIMPL impl;
    صحيح ret;

    priv = av_mallocz(حجم(*priv));
    إذا (!priv)
        أرجع AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->حرر        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", عدم, 0);
    إذا (e) {
        ٻار_device_type = av_hwdevice_ڳوليو_type_by_name(e->قدر);
        إذا (ٻار_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->قدر);
            أرجع AVERROR(EINVAL);
        }
#إذا QSV_ONEVPL
    } وإلا إذا (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        ٻار_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } وإلا إذا (CONFIG_DXVA2) {
        ٻار_device_type = AV_HWDEVICE_TYPE_DXVA2;
#وإلا
    } وإلا إذا (CONFIG_DXVA2) {
        av_log(عدم, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        ٻار_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } وإلا إذا (CONFIG_D3D11VA) {
        ٻار_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#جيڪڏهن_پورو
    } وإلا إذا (CONFIG_VAAPI) {
        ٻار_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } وإلا {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        أرجع AVERROR(ENOSYS);
    }

#إذا CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    إذا (ٻار_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->قدر);
        أرجع AVERROR(EINVAL);
    }
#جيڪڏهن_پورو

    ٻار_device_opts = عدم;
    بدل (ٻار_device_type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_سيٽ(&ٻار_device_opts, "vendor_id", "0x8086", 0);
            av_dict_سيٽ(&ٻار_device_opts, "driver",    "iHD",    0);
        }
        اكسر;
#جيڪڏهن_پورو
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_سيٽ(&ٻار_device_opts, "vendor_id",        "0x8086",  0);
        }
        اكسر;
#جيڪڏهن_پورو
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
#إذا QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#جيڪڏهن_پورو
        اكسر;
#جيڪڏهن_پورو
    افتراضي:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            أرجع AVERROR(ENOSYS);
        }
        اكسر;
    }

    e = av_dict_get(opts, "child_device", عدم, 0);
    ret = av_hwdevice_ctx_create(&priv->ٻار_device_ctx, ٻار_device_type,
                                 e ? e->قدر : عدم, ٻار_device_opts, 0);

    av_dict_free(&ٻار_device_opts);
    إذا (ret < 0)
        أرجع ret;

    ٻار_device = (AVHWDeviceContext*)priv->ٻار_device_ctx->معلومات;

    impl = چونڊيو_implementation(device, ٻار_device_type);

    أرجع qsv_device_derive_from_ٻار(ctx, impl, ٻار_device, 0);
}

ثابت HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_سائيز      = حجم(QSVDeviceContext),
    .چوکٺا_hwctx_سائيز      = حجم(QSVFramesContext),

    .device_create          = qsv_device_create,
    .device_derive          = qsv_device_derive,
    .device_init            = qsv_device_init,
    .چوکٺا_get_constraints = qsv_چوکٺا_get_constraints,
    .چوکٺا_init            = qsv_چوکٺا_init,
    .چوکٺا_uninit          = qsv_چوکٺا_uninit,
    .چوکٺا_get_بفر      = qsv_get_بفر,
    .transfer_get_formats   = qsv_transfer_get_formats,
    .transfer_معلومات_منزل       = qsv_transfer_معلومات_منزل,
    .transfer_معلومات_from     = qsv_transfer_معلومات_from,
    .map_منزل                 = qsv_map_منزل,
    .map_from               = qsv_map_from,
    .چوکٺا_derive_منزل       = qsv_چوکٺا_derive_منزل,
    .چوکٺا_derive_from     = qsv_چوکٺا_derive_from,

    .pix_fmts = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
