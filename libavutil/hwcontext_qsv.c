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
#پایان_اگر

#تعریف_کن COBJMACROS
#إذا CONFIG_VAAPI
#ضمن "hwcontext_vaapi.h"
#پایان_اگر
#إذا CONFIG_D3D11VA
#ضمن "hwcontext_d3d11va.h"
#پایان_اگر
#إذا CONFIG_DXVA2
#ضمن <initguid.h>
#ضمن "hwcontext_dxva2.h"
#پایان_اگر

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

#تعریف_کن QSV_نسخه_ATLEAST(MAJOR, MINOR)   \
    (MFX_نسخه_MAJOR > (MAJOR) ||         \
     MFX_نسخه_MAJOR == (MAJOR) && MFX_نسخه_MINOR >= (MINOR))

#تعریف_کن QSV_RUNTIME_نسخه_ATLEAST(MFX_نسخه, MAJOR, MINOR)          \
    ((MFX_نسخه.Major > (MAJOR)) ||                                   \
     (MFX_نسخه.Major == (MAJOR) && MFX_نسخه.Minor >= (MINOR)))

#تعریف_کن MFX_IMPL_از_طریق_ماسک(impl) (0x0f00 & (impl))
#تعریف_کن QSV_ONEVPL       QSV_نسخه_ATLEAST(2, 0)
#تعریف_کن QSV_HAVE_OPAQUE  !QSV_ONEVPL

#إذا QSV_ONEVPL
#ضمن <mfxdispatcher.h>
#وإلا
#تعریف_کن MFXUnload(a) افعل { } طالما(0)
#پایان_اگر

تعريفنوع بنية QSVDevicePriv {
    AVBufferRef *فرزند_device_ctx;
} QSVDevicePriv;

تعريفنوع بنية QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfx_نسخه          ver;
    mfxIMPL             impl;

    تعداد AVHWDeviceType فرزند_device_type;
    تعداد AVPixelFormat  فرزند_pix_fmt;
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
    pthread_mutex_t session_قفل;
#پایان_اگر

    AVBufferRef *فرزند_قابها_ref;
    mfx_قاب_Surface1 *surfaces_داخلی;
    mfxHDLPair *handle_جفتها_داخلی;
    صحيح             nb_surfaces_استفاده_شده;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#إذا QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfx_قاب_Surface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfx_Ext_میانگیر *ext_buffers[1];
#پایان_اگر
    AVFrame realigned_upload_قاب;
    AVFrame realigned_download_قاب;

    mfx_قاب_Info قاب_info;
} QSVFramesContext;

تعريفنوع بنية QSVSurface {
    mfx_قاب_Surface1 mfx_surface;
    AVFrame *فرزند_قاب;
} QSVSurface;

ساكن ثابت بنية {
    تعداد AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_لغزش;
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
#پایان_اگر
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
#إذا QSV_نسخه_ATLEAST(1, 31)
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
#پایان_اگر
};

خارجي صحيح ff_qsv_get_surface_پایه_handle(mfx_قاب_Surface1 *surf,
                                          تعداد AVHWDeviceType پایه_dev_type,
                                          فراغ **پایه_handle);

ساكن صحيح qsv_init_surface(AVHWFramesContext *ctx, mfx_قاب_Surface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
صحيح ff_qsv_get_surface_پایه_handle(mfx_قاب_Surface1 *surf,
                                   تعداد AVHWDeviceType پایه_dev_type,
                                   فراغ **پایه_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->داده_2.MemId;
    بدل (پایه_dev_type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        پایه_handle[0] = handle_pair->اولی;
        أرجع 0;
#پایان_اگر
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        پایه_handle[0] = handle_pair->اولی;
        پایه_handle[1] = handle_pair->دومی;
        أرجع 0;
#پایان_اگر
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        پایه_handle[0] = handle_pair->اولی;
        أرجع 0;
#پایان_اگر
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

ساكن uint16_t qsv_لغزش_from_pix_fmt(تعداد AVPixelFormat pix_fmt)
{
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        إذا (supported_pixel_formats[i].pix_fmt == pix_fmt)
            أرجع supported_pixel_formats[i].mfx_لغزش;
    }

    أرجع 0;
}

#إذا CONFIG_D3D11VA
ساكن uint32_t qsv_get_d3d11va_bind_flags(صحيح mem_type)
{
    uint32_t bind_flags = 0;

    إذا ((mem_type & MFX_MEMTYPE_VIDEO_حافظه_ENCODER_هدف) && (mem_type & MFX_MEMTYPE_داخلی_قاب))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    وإلا
        bind_flags = D3D11_BIND_DECODER;

    إذا ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_حافظه_PROCESSOR_هدف & mem_type))
        bind_flags = D3_D11_BIND_RENDER_هدف;

    أرجع bind_flags;
}
#پایان_اگر

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
                                                 src->عرض,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->عرض,
                                                 i);
        ثابت AVComponentDescriptor comp = desc->comp[i];
        إذا (swidth < 0 || dwidth < 0) {
            av_log(عدم, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            أرجع AVERROR(EINVAL);
        }
        sheight = src->ارتفاع;
        dheight = dst->ارتفاع;
        إذا (i) {
            sheight = AV_CEIL_RSHIFT(src->ارتفاع, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->ارتفاع, desc->log2_chroma_h);
        }
        //fill right padding
        لكل (y = 0; y < sheight; y++) {
            فراغ *سطر_ptr = dst->داده[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(سطر_ptr,
                           comp.عمق > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        لكل (y = sheight; y < dheight; y++) {
            کپی_حافظه(dst->داده[i]+y*dst->linesize[i],
                   dst->داده[i]+(sheight-1)*dst->linesize[i],
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
    mfx_وضعیت err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    إذا (err == MFX_ERR_NONE)
        err = MFXQuery_نسخه(hwctx->session, &s->ver);
    إذا (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        أرجع AVERROR_UNKNOWN;
    }

    إذا (MFX_IMPL_از_طریق_VAAPI == MFX_IMPL_از_طریق_ماسک(s->impl)) {
#إذا CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#پایان_اگر
    } وإلا إذا (MFX_IMPL_از_طریق_D3_D11 == MFX_IMPL_از_طریق_ماسک(s->impl)) {
#إذا CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#پایان_اگر
    } وإلا إذا (MFX_IMPL_از_طریق_D3_D9 == MFX_IMPL_از_طریق_ماسک(s->impl)) {
#إذا CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#پایان_اگر
    }

    إذا (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        إذا (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->فرزند_device_type = device_type;
            s->فرزند_pix_fmt     = pix_fmt;
        }
    }
    إذا (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    أرجع 0;
}

ساكن فراغ qsv_قابها_uninit(AVHWFramesContext *ctx)
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
    pthread_mutex_destroy(&s->session_قفل);
#پایان_اگر

    av_freep(&s->mem_ids);
#إذا QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#پایان_اگر
    av_freep(&s->surfaces_داخلی);
    av_freep(&s->handle_جفتها_داخلی);
    av_قاب_unref(&s->realigned_upload_قاب);
    av_قاب_unref(&s->realigned_download_قاب);
    av_میانگیر_unref(&s->فرزند_قابها_ref);
}

ساكن فراغ qsv_pool_release_dummy(فراغ *opaque, uint8_t *داده)
{
}

ساكن فراغ qsv_pool_release(فراغ *opaque, uint8_t *داده)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)داده;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.داده_2.MemId;
    AVHWFramesContext *فرزند_قابها_ctx;

    إذا (!s->فرزند_قابها_ref)
        أرجع;

    فرزند_قابها_ctx = (AVHWFramesContext*)s->فرزند_قابها_ref->داده;
    إذا (!فرزند_قابها_ctx->device_ctx)
        أرجع;

#إذا CONFIG_VAAPI
    إذا (فرزند_قابها_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->اولی);
#پایان_اگر

    av_freep(&hdl_pair);
    av_قاب_free(&qsv_surface->فرزند_قاب);
    av_freep(&qsv_surface);
}

ساكن AVBufferRef *qsv_fixed_pool_alloc(فراغ *opaque, size_t اندازه)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    إذا (s->nb_surfaces_استفاده_شده < hwctx->nb_surfaces) {
        s->nb_surfaces_استفاده_شده++;
        أرجع av_میانگیر_create((uint8_t*)(s->surfaces_داخلی + s->nb_surfaces_استفاده_شده - 1),
                                حجم(*hwctx->surfaces), qsv_pool_release_dummy, عدم, 0);
    }

    أرجع عدم;
}

ساكن AVBufferRef *qsv_dynamic_pool_alloc(فراغ *opaque, size_t اندازه)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *فرزند_قابها_ctx;
    QSVSurface *qsv_surface = عدم;
    mfxHDLPair *handle_جفتها_داخلی = عدم;
    صحيح ret;

    إذا (!s->فرزند_قابها_ref)
        اذهب fail;

    فرزند_قابها_ctx = (AVHWFramesContext*)s->فرزند_قابها_ref->داده;
    إذا (!فرزند_قابها_ctx->device_ctx)
        اذهب fail;

#إذا CONFIG_DXVA2
    إذا (فرزند_قابها_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        اذهب fail;
    }
#پایان_اگر

    qsv_surface = av_calloc(1, حجم(*qsv_surface));
    إذا (!qsv_surface)
        اذهب fail;

    qsv_surface->فرزند_قاب = av_قاب_alloc();
    إذا (!qsv_surface->فرزند_قاب)
        اذهب fail;

    ret = av_hwframe_get_میانگیر(s->فرزند_قابها_ref, qsv_surface->فرزند_قاب, 0);
    إذا (ret < 0)
        اذهب fail;

    handle_جفتها_داخلی = av_calloc(1, حجم(*handle_جفتها_داخلی));
    إذا (!handle_جفتها_داخلی)
        اذهب fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    إذا (ret < 0)
        اذهب fail;

#إذا CONFIG_VAAPI
    إذا (فرزند_قابها_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_داخلی;

        surface_id_داخلی = av_calloc(1, حجم(*surface_id_داخلی));
        إذا (!surface_id_داخلی)
            اذهب fail;

        *surface_id_داخلی = (VASurfaceID)(uintptr_t)qsv_surface->فرزند_قاب->داده[3];
        handle_جفتها_داخلی->اولی = (mfxHDL)surface_id_داخلی;
        handle_جفتها_داخلی->دومی = (mfxMemId)MFX_INFINITE;
    }
#پایان_اگر

#إذا CONFIG_D3D11VA
    إذا (فرزند_قابها_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *فرزند_قابها_hwctx = فرزند_قابها_ctx->hwctx;
        handle_جفتها_داخلی->اولی = (mfxMemId)qsv_surface->فرزند_قاب->داده[0];

        إذا (فرزند_قابها_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف)
            handle_جفتها_داخلی->دومی = (mfxMemId)MFX_INFINITE;
        وإلا
            handle_جفتها_داخلی->دومی = (mfxMemId)qsv_surface->فرزند_قاب->داده[1];

    }
#پایان_اگر

    qsv_surface->mfx_surface.داده_2.MemId = (mfxMemId)handle_جفتها_داخلی;
    أرجع av_میانگیر_create((uint8_t *)qsv_surface, حجم(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    إذا (qsv_surface) {
        av_قاب_free(&qsv_surface->فرزند_قاب);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_جفتها_داخلی);

    أرجع عدم;
}

ساكن AVBufferRef *qsv_pool_alloc(فراغ *opaque, size_t اندازه)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    إذا (hwctx->nb_surfaces == 0) {
        أرجع qsv_dynamic_pool_alloc(opaque, اندازه);
    } وإلا {
        أرجع qsv_fixed_pool_alloc(opaque, اندازه);
    }
}

ساكن صحيح qsv_init_فرزند_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *فرزند_device_ref = عدم;
    AVBufferRef *فرزند_قابها_ref = عدم;

    AVHWDeviceContext *فرزند_device_ctx;
    AVHWFramesContext *فرزند_قابها_ctx;

    صحيح i, ret = 0;

    إذا (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        أرجع AVERROR(EINVAL);
    }

    فرزند_device_ref = av_hwdevice_ctx_alloc(device_priv->فرزند_device_type);
    إذا (!فرزند_device_ref)
        أرجع AVERROR(ENOMEM);
    فرزند_device_ctx   = (AVHWDeviceContext*)فرزند_device_ref->داده;

#إذا CONFIG_VAAPI
    إذا (فرزند_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *فرزند_device_hwctx = فرزند_device_ctx->hwctx;
        فرزند_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#پایان_اگر
#إذا CONFIG_D3D11VA
    إذا (فرزند_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *فرزند_device_hwctx = فرزند_device_ctx->hwctx;
        ID3_D11_Device_جمع_کن_Ref((ID3D11Device*)device_priv->handle);
        فرزند_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#پایان_اگر
#إذا CONFIG_DXVA2
    إذا (فرزند_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *فرزند_device_hwctx = فرزند_device_ctx->hwctx;
        فرزند_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#پایان_اگر

    ret = av_hwdevice_ctx_init(فرزند_device_ref);
    إذا (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        اذهب fail;
    }

    فرزند_قابها_ref = av_hwframe_ctx_alloc(فرزند_device_ref);
    إذا (!فرزند_قابها_ref) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }
    فرزند_قابها_ctx = (AVHWFramesContext*)فرزند_قابها_ref->داده;

    فرزند_قابها_ctx->format            = device_priv->فرزند_pix_fmt;
    فرزند_قابها_ctx->sw_format         = ctx->sw_format;
    فرزند_قابها_ctx->initial_pool_اندازه = ctx->initial_pool_اندازه;
    فرزند_قابها_ctx->عرض             = FFALIGN(ctx->عرض, 16);
    فرزند_قابها_ctx->ارتفاع            = FFALIGN(ctx->ارتفاع, 16);

#إذا CONFIG_D3D11VA
    إذا (فرزند_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *فرزند_قابها_hwctx = فرزند_قابها_ctx->hwctx;
        إذا (hwctx->قاب_type == 0)
            hwctx->قاب_type = MFX_MEMTYPE_VIDEO_حافظه_PROCESSOR_هدف;
        إذا (hwctx->قاب_type & MFX_MEMTYPE_SHARED_RESOURCE)
            فرزند_قابها_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        فرزند_قابها_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->قاب_type);
    }
#پایان_اگر
#إذا CONFIG_DXVA2
    إذا (فرزند_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_قابها_Context *فرزند_قابها_hwctx = فرزند_قابها_ctx->hwctx;
        إذا (hwctx->قاب_type & MFX_MEMTYPE_VIDEO_حافظه_PROCESSOR_هدف)
            فرزند_قابها_hwctx->surface_type = DXVA2_Video_Processor_Render_هدف;
        وإلا
            فرزند_قابها_hwctx->surface_type = DXVA2_Video_Decoder_Render_هدف;
    }
#پایان_اگر

    ret = av_hwframe_ctx_init(فرزند_قابها_ref);
    إذا (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        اذهب fail;
    }

#إذا CONFIG_VAAPI
    إذا (فرزند_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *فرزند_قابها_hwctx = فرزند_قابها_ctx->hwctx;
        لكل (i = 0; i < ctx->initial_pool_اندازه; i++) {
            s->handle_جفتها_داخلی[i].اولی = فرزند_قابها_hwctx->surface_ids + i;
            s->handle_جفتها_داخلی[i].دومی = (mfxMemId)MFX_INFINITE;
            s->surfaces_داخلی[i].داده_2.MemId = (mfxMemId)&s->handle_جفتها_داخلی[i];
        }
        hwctx->قاب_type = MFX_MEMTYPE_VIDEO_حافظه_DECODER_هدف;
    }
#پایان_اگر
#إذا CONFIG_D3D11VA
    إذا (فرزند_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *فرزند_قابها_hwctx = فرزند_قابها_ctx->hwctx;
        لكل (i = 0; i < ctx->initial_pool_اندازه; i++) {
            s->handle_جفتها_داخلی[i].اولی = (mfxMemId)فرزند_قابها_hwctx->texture_infos[i].texture;
            إذا(فرزند_قابها_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف) {
                s->handle_جفتها_داخلی[i].دومی = (mfxMemId)MFX_INFINITE;
            } وإلا {
                s->handle_جفتها_داخلی[i].دومی = (mfxMemId)فرزند_قابها_hwctx->texture_infos[i].شاخص;
            }
            s->surfaces_داخلی[i].داده_2.MemId = (mfxMemId)&s->handle_جفتها_داخلی[i];
        }
        إذا (فرزند_قابها_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف) {
            hwctx->قاب_type |= MFX_MEMTYPE_VIDEO_حافظه_PROCESSOR_هدف;
        } وإلا {
            hwctx->قاب_type |= MFX_MEMTYPE_VIDEO_حافظه_DECODER_هدف;
        }
    }
#پایان_اگر
#إذا CONFIG_DXVA2
    إذا (فرزند_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_قابها_Context *فرزند_قابها_hwctx = فرزند_قابها_ctx->hwctx;
        لكل (i = 0; i < ctx->initial_pool_اندازه; i++) {
            s->handle_جفتها_داخلی[i].اولی = (mfxMemId)فرزند_قابها_hwctx->surfaces[i];
            s->handle_جفتها_داخلی[i].دومی = (mfxMemId)MFX_INFINITE;
            s->surfaces_داخلی[i].داده_2.MemId = (mfxMemId)&s->handle_جفتها_داخلی[i];
        }
        إذا (فرزند_قابها_hwctx->surface_type == DXVA2_Video_Processor_Render_هدف)
            hwctx->قاب_type = MFX_MEMTYPE_VIDEO_حافظه_PROCESSOR_هدف;
        وإلا
            hwctx->قاب_type = MFX_MEMTYPE_VIDEO_حافظه_DECODER_هدف;
    }
#پایان_اگر

    s->فرزند_قابها_ref       = فرزند_قابها_ref;
    فرزند_قابها_ref          = عدم;

fail:
    av_میانگیر_unref(&فرزند_device_ref);
    av_میانگیر_unref(&فرزند_قابها_ref);
    أرجع ret;
}

ساكن صحيح qsv_init_surface(AVHWFramesContext *ctx, mfx_قاب_Surface1 *surf)
{
    ثابت AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    إذا (!desc)
        أرجع AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    إذا (!fourcc)
        أرجع AVERROR(EINVAL);

    surf->Info.بیت_عمق_Luma   = desc->comp[0].عمق;
    surf->Info.بیت_عمق_Chroma = desc->comp[0].عمق;
    surf->Info.لغزش_2          = qsv_لغزش_from_pix_fmt(ctx->sw_format);

    إذا (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    وإلا إذا (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    وإلا
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.عرض_2          = FFALIGN(ctx->عرض, 16);
    surf->Info.CropW          = ctx->عرض;
    surf->Info.ارتفاع_2         = FFALIGN(ctx->ارتفاع, 16);
    surf->Info.CropH          = ctx->ارتفاع;
    surf->Info.قاب_نرخ_Ext_N  = 25;
    surf->Info.قاب_نرخ_Ext_D  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    أرجع 0;
}

ساكن صحيح qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *قابها_hwctx = &s->p;

    صحيح i, ret = 0;

    إذا (ctx->initial_pool_اندازه < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        أرجع AVERROR(EINVAL);
    } وإلا إذا (ctx->initial_pool_اندازه == 0) {
        mfx_قاب_Surface1 mfx_surf1;

        ret = qsv_init_فرزند_ctx(ctx);
        إذا (ret < 0)
            أرجع ret;

        ffhwframesctx(ctx)->pool_داخلی = av_میانگیر_pool_init2(حجم(mfx_قاب_Surface1),
                                                                 ctx, qsv_pool_alloc, عدم);
        إذا (!ffhwframesctx(ctx)->pool_داخلی)
            أرجع AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, حجم(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->قاب_info = mfx_surf1.Info;
        قابها_hwctx->info = &s->قاب_info;
        قابها_hwctx->nb_surfaces = 0;

        أرجع 0;
    }

    s->handle_جفتها_داخلی = av_calloc(ctx->initial_pool_اندازه,
                                         حجم(*s->handle_جفتها_داخلی));
    إذا (!s->handle_جفتها_داخلی)
        أرجع AVERROR(ENOMEM);

    s->surfaces_داخلی = av_calloc(ctx->initial_pool_اندازه,
                                     حجم(*s->surfaces_داخلی));
    إذا (!s->surfaces_داخلی)
        أرجع AVERROR(ENOMEM);

    لكل (i = 0; i < ctx->initial_pool_اندازه; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_داخلی[i]);
        إذا (ret < 0)
            أرجع ret;
    }

#إذا QSV_HAVE_OPAQUE
    إذا (!(قابها_hwctx->قاب_type & MFX_MEMTYPE_OPAQUE_قاب)) {
        ret = qsv_init_فرزند_ctx(ctx);
        إذا (ret < 0)
            أرجع ret;
    }
#وإلا
    ret = qsv_init_فرزند_ctx(ctx);
    إذا (ret < 0)
        أرجع ret;
#پایان_اگر

    ffhwframesctx(ctx)->pool_داخلی = av_میانگیر_pool_init2(حجم(mfx_قاب_Surface1),
                                                             ctx, qsv_pool_alloc, عدم);
    إذا (!ffhwframesctx(ctx)->pool_داخلی)
        أرجع AVERROR(ENOMEM);

    قابها_hwctx->surfaces    = s->surfaces_داخلی;
    قابها_hwctx->nb_surfaces = ctx->initial_pool_اندازه;

    أرجع 0;
}

ساكن mfx_وضعیت قاب_alloc(mfxHDL pthis, mfx_قاب_Alloc_Request *req,
                             mfx_قاب_Alloc_Response *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfx_قاب_Info *i  = &req->Info;
    mfx_قاب_Info *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    إذا (!(req->Type & MFX_MEMTYPE_VIDEO_حافظه_PROCESSOR_هدف) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_قاب))
        أرجع MFX_ERR_UNSUPPORTED;
    إذا (i->عرض_2  > i1->عرض_2 || i->ارتفاع_2 > i1->ارتفاع_2 ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->عرض_2,  i->ارتفاع_2,  i->FourCC,  i->ChromaFormat,
               i1->عرض_2, i1->ارتفاع_2, i1->FourCC, i1->ChromaFormat);
        أرجع MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->رقم_قاب_Actual = hwctx->nb_surfaces;

    أرجع MFX_ERR_NONE;
}

ساكن mfx_وضعیت قاب_free(mfxHDL pthis, mfx_قاب_Alloc_Response *resp)
{
    أرجع MFX_ERR_NONE;
}

ساكن mfx_وضعیت قاب_قفل(mfxHDL pthis, mfxMemId mid, mfx_قاب_داده *ptr)
{
    أرجع MFX_ERR_UNSUPPORTED;
}

ساكن mfx_وضعیت قاب_unlock(mfxHDL pthis, mfxMemId mid, mfx_قاب_داده *ptr)
{
    أرجع MFX_ERR_UNSUPPORTED;
}

ساكن mfx_وضعیت قاب_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->اولی = pair_src->اولی;

    إذا (pair_src->دومی != (mfxMemId)MFX_INFINITE)
        pair_dst->دومی = pair_src->دومی;
    أرجع MFX_ERR_NONE;
}

#إذا QSV_ONEVPL

ساكن صحيح qsv_d3d11_update_config(فراغ *ctx, mfxHDL handle, mfxConfig cfg)
{
    صحيح ret = AVERROR_UNKNOWN;
#إذا CONFIG_D3D11VA
    mfx_وضعیت sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = عدم;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_مقدار = {0};

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

    impl_مقدار.Type = MFX_VARIANT_TYPE_U16;
    impl_مقدار.داده_2.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_مقدار);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        اذهب fail;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_PTR;
    impl_مقدار.داده_2.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_مقدار);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        اذهب fail;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_U32;
    impl_مقدار.داده_2.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_مقدار);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        اذهب fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#پایان_اگر
    أرجع ret;
}

ساكن صحيح qsv_d3d9_update_config(فراغ *ctx, mfxHDL handle, mfxConfig cfg)
{
    صحيح ret = AVERROR_UNKNOWN;
#إذا CONFIG_DXVA2
    mfx_وضعیت sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = عدم;
    IDirect3DDevice9Ex *device_ex = عدم;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = عدم;
    IDirect3D9 *d3d9 = عدم;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_مقدار = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    إذا (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        اذهب fail;
    }

    hr = IDirect3_DDevice_Manager9_قفل_Device(devmgr, device_handle, &device, TRUE);
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

    impl_مقدار.Type = MFX_VARIANT_TYPE_PTR;
    impl_مقدار.داده_2.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_مقدار);
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
#پایان_اگر
    أرجع ret;
}

ساكن صحيح qsv_va_update_config(فراغ *ctx, mfxHDL handle, mfxConfig cfg)
{
#إذا CONFIG_VAAPI
#إذا VA_CHECK_نسخه(1, 15, 0)
    mfx_وضعیت sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_مقدار = {0};

    vas = va_Get_Display_صفات(dpy, &attr, 1);
    إذا (vas == VA_وضعیت_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_مقدار.Type = MFX_VARIANT_TYPE_U16;
        impl_مقدار.داده_2.U16 = (attr.مقدار & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ثابت mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_مقدار);
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
#پایان_اگر
#پایان_اگر
    أرجع AVERROR_UNKNOWN;
}

ساكن صحيح qsv_new_mfx_loader(فراغ *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfx_نسخه *pver,
                              فراغ **ploader)
{
    mfx_وضعیت sts;
    mfxLoader loader = عدم;
    mfxConfig cfg;
    mfxVariant impl_مقدار = {0};

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

    impl_مقدار.Type = MFX_VARIANT_TYPE_U32;
    impl_مقدار.داده_2.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.Impl", impl_مقدار);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        اذهب fail;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_U32;
    impl_مقدار.داده_2.U32 = pver->نسخه_2;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_مقدار);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        اذهب fail;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_U32;
    impl_مقدار.داده_2.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.VendorID", impl_مقدار);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        اذهب fail;
    }

    إذا (MFX_HANDLE_VA_DISPLAY == handle_type) {
        إذا (handle && qsv_va_update_config(ctx, handle, cfg))
            اذهب fail;

        impl_مقدار.داده_2.U32 = MFX_ACCEL_نما_از_طریق_VAAPI;
    } وإلا إذا (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        إذا (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            اذهب fail;

        impl_مقدار.داده_2.U32 = MFX_ACCEL_نما_از_طریق_D3_D9;
    } وإلا {
        إذا (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            اذهب fail;

        impl_مقدار.داده_2.U32 = MFX_ACCEL_نما_از_طریق_D3_D11;
    }

    impl_مقدار.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.AccelerationMode", impl_مقدار);
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
    mfx_وضعیت sts;
    mfxSession session = عدم;
    uint32_t impl_idx = 0;
    mfx_نسخه ver;

    طالما (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        إذا (sts == MFX_ERR_NOT_یافت)
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

    sts = MFXQuery_نسخه(session, &ver);
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
                                  mfx_نسخه *pver,
                                  mfxSession *psession,
                                  فراغ **ploader)
{
    mfxLoader loader = عدم;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_نسخه_MAJOR, MFX_نسخه_MINOR, pver->Major, pver->Minor);

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
                                  mfx_نسخه *pver,
                                  mfxSession *psession,
                                  فراغ **ploader)
{
    mfx_نسخه ver;
    mfx_وضعیت sts;
    mfxSession session = عدم;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_نسخه_MAJOR, MFX_نسخه_MINOR, pver->Major, pver->Minor);

    *ploader = عدم;
    *psession = عدم;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    إذا (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        اذهب fail;
    }

    sts = MFXQuery_نسخه(session, &ver);
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

#پایان_اگر

ساكن صحيح qsv_init_داخلی_session(AVHWFramesContext *ctx,
                                     mfxSession *session, صحيح upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *قابها_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    صحيح opaque = 0;

    mfx_قاب_Allocator قاب_allocator = {
        .pthis  = ctx,
        .Alloc  = قاب_alloc,
        .قفل_3   = قاب_قفل,
        .Unlock = قاب_unlock,
        .GetHDL = قاب_get_hdl,
        .Free   = قاب_free,
    };

    mfxVideoParam par;
    mfx_وضعیت err;
    صحيح                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    فراغ             **loader = &hwctx->loader;
    mfxSession والد_session = hwctx->session;
    mfxIMPL impl;
    mfx_نسخه ver;

    err = MFXQueryIMPL(والد_session, &impl);
    إذا (err == MFX_ERR_NONE)
        err = MFXQuery_نسخه(والد_session, &ver);
    إذا (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        أرجع AVERROR_UNKNOWN;
    }

#إذا QSV_HAVE_OPAQUE
    opaque = !!(قابها_hwctx->قاب_type & MFX_MEMTYPE_OPAQUE_قاب);
#پایان_اگر

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    إذا (ret)
        اذهب fail;

    إذا (device_priv->handle) {
        err = MFXVideo_CORE_مجموعه_Handle(*session, device_priv->handle_type,
                                     device_priv->handle);
        إذا (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            اذهب fail;
        }
    }

    إذا (QSV_RUNTIME_نسخه_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(والد_session, *session);
        إذا (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            اذهب fail;
        }
    }

    إذا (!opaque) {
        err = MFXVideo_CORE_مجموعه_قاب_Allocator(*session, &قاب_allocator);
        إذا (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            اذهب fail;
        }
    }

    memset(&par, 0, حجم(par));

    إذا (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_بیرون_VIDEO_حافظه :
                                 MFX_IOPATTERN_درون_VIDEO_حافظه;
    }
#إذا QSV_HAVE_OPAQUE
    وإلا {
        par.ExtParam    = s->ext_buffers;
        par.رقم_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
        par.IOPattern   = upload ? MFX_IOPATTERN_بیرون_OPAQUE_حافظه :
                                   MFX_IOPATTERN_درون_OPAQUE_حافظه;
    }
#پایان_اگر

    par.IOPattern |= upload ? MFX_IOPATTERN_درون_SYSTEM_حافظه :
                              MFX_IOPATTERN_بیرون_SYSTEM_حافظه;
    par.Async_عمق = 1;

    par.vpp.درون_2 = قابها_hwctx->nb_surfaces ? قابها_hwctx->surfaces[0].Info : *قابها_hwctx->info;

    /* Apparently VPP requires the frame rate to be set to some value, otherwise
     * init will fail (probably for the framerate conversion filter). Since we
     * are only doing data upload/download here, we just invent an arbitrary
     * value */
    par.vpp.درون_2.قاب_نرخ_Ext_N = 25;
    par.vpp.درون_2.قاب_نرخ_Ext_D = 1;
    par.vpp.بیرون_2 = par.vpp.درون_2;

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

ساكن صحيح qsv_قابها_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *قابها_hwctx = &s->p;

    صحيح opaque = 0;

    uint32_t fourcc;
    صحيح i, ret;

#إذا QSV_HAVE_OPAQUE
    opaque = !!(قابها_hwctx->قاب_type & MFX_MEMTYPE_OPAQUE_قاب);
#پایان_اگر

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
        s->mem_ids = av_calloc(قابها_hwctx->nb_surfaces, حجم(*s->mem_ids));
        إذا (!s->mem_ids)
            أرجع AVERROR(ENOMEM);

        لكل (i = 0; i < قابها_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = قابها_hwctx->surfaces[i].داده_2.MemId;
    }
#إذا QSV_HAVE_OPAQUE
    وإلا {
        s->surface_ptrs = av_calloc(قابها_hwctx->nb_surfaces,
                                    حجم(*s->surface_ptrs));
        إذا (!s->surface_ptrs)
            أرجع AVERROR(ENOMEM);

        لكل (i = 0; i < قابها_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = قابها_hwctx->surfaces + i;

        s->opaque_alloc.درون_2.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.درون_2.رقم_Surface = قابها_hwctx->nb_surfaces;
        s->opaque_alloc.درون_2.Type       = قابها_hwctx->قاب_type;

        s->opaque_alloc.بیرون_2 = s->opaque_alloc.درون_2;

        s->opaque_alloc.سرآیند_2.میانگیر_Id = MFX_EXTBUFF_OPAQUE_SURFACE_تخصیص;
        s->opaque_alloc.سرآیند_2.میانگیر_Sz = حجم(s->opaque_alloc);

        s->ext_buffers[0] = (mfx_Ext_میانگیر*)&s->opaque_alloc;
    }
#پایان_اگر

    s->session_download = عدم;
    s->session_upload   = عدم;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#إذا HAVE_PTHREADS
    pthread_mutex_init(&s->session_قفل, عدم);
#پایان_اگر

    أرجع 0;
}

ساكن صحيح qsv_get_میانگیر(AVHWFramesContext *ctx, AVFrame *قاب)
{
    قاب->buf[0] = av_میانگیر_pool_get(ctx->pool);
    إذا (!قاب->buf[0])
        أرجع AVERROR(ENOMEM);

    قاب->داده[3] = قاب->buf[0]->داده;
    قاب->format  = AV_PIX_FMT_QSV;
    قاب->عرض   = ctx->عرض;
    قاب->ارتفاع  = ctx->ارتفاع;

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

ساكن صحيح qsv_قابها_derive_from(AVHWFramesContext *dst_ctx,
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
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].داده_2.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->اولی;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        اكسر;
#پایان_اگر
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_اندازه = src_ctx->initial_pool_اندازه;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 حجم(*dst_hwctx->texture_infos));
            إذا (!dst_hwctx->texture_infos)
                أرجع AVERROR(ENOMEM);
            إذا (src_hwctx->قاب_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            لكل (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].داده_2.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->اولی;
                dst_hwctx->texture_infos[i].شاخص = pair->دومی == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->دومی;
            }
            إذا (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } وإلا
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->قاب_type);
        }
        اكسر;
#پایان_اگر
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_قابها_Context *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            حجم(*dst_hwctx->surfaces));
            إذا (!dst_hwctx->surfaces)
                أرجع AVERROR(ENOMEM);
            لكل (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].داده_2.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->اولی;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            إذا (src_hwctx->قاب_type == MFX_MEMTYPE_VIDEO_حافظه_DECODER_هدف)
                dst_hwctx->surface_type = DXVA2_Video_Decoder_Render_هدف;
            وإلا
                dst_hwctx->surface_type = DXVA2_Video_Processor_Render_هدف;
        }
        اكسر;
#پایان_اگر
    افتراضي:
        أرجع AVERROR(ENOSYS);
    }

    أرجع 0;
}

ساكن صحيح qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfx_قاب_Surface1 *surf = (mfx_قاب_Surface1*)src->داده[3];
    AVHWFramesContext *فرزند_قابها_ctx;
    ثابت AVPixFmtDescriptor *desc;
    uint8_t *فرزند_داده;
    AVFrame *dummy;
    صحيح ret = 0;

    إذا (!s->فرزند_قابها_ref)
        أرجع AVERROR(ENOSYS);
    فرزند_قابها_ctx = (AVHWFramesContext*)s->فرزند_قابها_ref->داده;

    بدل (فرزند_قابها_ctx->device_ctx->type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->داده_2.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        فرزند_داده = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->اولی;
        اكسر;
    }
#پایان_اگر
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->داده_2.MemId;
        فرزند_داده = pair->اولی;
        اكسر;
    }
#پایان_اگر
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->داده_2.MemId;
        فرزند_داده = pair->اولی;
        اكسر;
    }
#پایان_اگر
    افتراضي:
        أرجع AVERROR(ENOSYS);
    }

    إذا (dst->format == فرزند_قابها_ctx->format) {
        ret = ff_hwframe_map_create(s->فرزند_قابها_ref,
                                    dst, src, عدم, عدم);
        إذا (ret < 0)
            أرجع ret;

        dst->عرض   = src->عرض;
        dst->ارتفاع  = src->ارتفاع;

       إذا (فرزند_قابها_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->داده_2.MemId;
            dst->داده[0] = pair->اولی;
            dst->داده[1] = pair->دومی == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->دومی;
        } وإلا {
            dst->داده[3] = فرزند_داده;
        }

        أرجع 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    إذا (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        أرجع AVERROR(ENOSYS);
    }

    dummy = av_قاب_alloc();
    إذا (!dummy)
        أرجع AVERROR(ENOMEM);

    dummy->buf[0]        = av_میانگیر_ref(src->buf[0]);
    dummy->hw_قابها_ctx = av_میانگیر_ref(s->فرزند_قابها_ref);
    إذا (!dummy->buf[0] || !dummy->hw_قابها_ctx)
        اذهب fail;

    dummy->format        = فرزند_قابها_ctx->format;
    dummy->عرض         = src->عرض;
    dummy->ارتفاع        = src->ارتفاع;

    إذا (فرزند_قابها_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->داده_2.MemId;
        dummy->داده[0] = pair->اولی;
        dummy->داده[1] = pair->دومی == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->دومی;
    } وإلا {
        dummy->داده[3] = فرزند_داده;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_قاب_free(&dummy);

    أرجع ret;
}

ساكن صحيح qsv_transfer_داده_فرزند(AVHWFramesContext *ctx, AVFrame *dst,
                                   ثابت AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *فرزند_قابها_ctx = (AVHWFramesContext*)s->فرزند_قابها_ref->داده;
    صحيح download = !!src->hw_قابها_ctx;
    mfx_قاب_Surface1 *surf = (mfx_قاب_Surface1*)(download ? src->داده[3] : dst->داده[3]);

    AVFrame *dummy;
    صحيح ret;

    dummy = av_قاب_alloc();
    إذا (!dummy)
        أرجع AVERROR(ENOMEM);

    dummy->format        = فرزند_قابها_ctx->format;
    dummy->عرض         = src->عرض;
    dummy->ارتفاع        = src->ارتفاع;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->داده[3]       = surf->داده_2.MemId;
    dummy->hw_قابها_ctx = s->فرزند_قابها_ref;

    ret = download ? av_hwframe_transfer_داده(dst, dummy, 0) :
                     av_hwframe_transfer_داده(dummy, src, 0);

    dummy->buf[0]        = عدم;
    dummy->داده[3]       = عدم;
    dummy->hw_قابها_ctx = عدم;

    av_قاب_free(&dummy);

    أرجع ret;
}

ساكن صحيح map_قاب_مقصد_surface(ثابت AVFrame *قاب, mfx_قاب_Surface1 *surface)
{
    بدل (قاب->format) {
    حالة AV_PIX_FMT_NV12:
    حالة AV_PIX_FMT_P010:
    حالة AV_PIX_FMT_P012:
        surface->داده_2.Y  = قاب->داده[0];
        surface->داده_2.UV = قاب->داده[1];
        اكسر;

    حالة AV_PIX_FMT_YUV420P:
        surface->داده_2.Y = قاب->داده[0];
        surface->داده_2.U = قاب->داده[1];
        surface->داده_2.V = قاب->داده[2];
        اكسر;

    حالة AV_PIX_FMT_BGRA:
        surface->داده_2.B = قاب->داده[0];
        surface->داده_2.G = قاب->داده[0] + 1;
        surface->داده_2.R = قاب->داده[0] + 2;
        surface->داده_2.A = قاب->داده[0] + 3;
        اكسر;
    حالة AV_PIX_FMT_YUYV422:
        surface->داده_2.Y = قاب->داده[0];
        surface->داده_2.U = قاب->داده[0] + 1;
        surface->داده_2.V = قاب->داده[0] + 3;
        اكسر;

    حالة AV_PIX_FMT_Y210:
    حالة AV_PIX_FMT_Y212:
        surface->داده_2.Y16 = (mfxU16 *)قاب->داده[0];
        surface->داده_2.U16 = (mfxU16 *)قاب->داده[0] + 1;
        surface->داده_2.V16 = (mfxU16 *)قاب->داده[0] + 3;
        اكسر;
    حالة AV_PIX_FMT_VUYX:
        surface->داده_2.V = قاب->داده[0];
        surface->داده_2.U = قاب->داده[0] + 1;
        surface->داده_2.Y = قاب->داده[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->داده_2.A = قاب->داده[0] + 3;
        اكسر;
    حالة AV_PIX_FMT_XV30:
        surface->داده_2.U = قاب->داده[0];
        اكسر;
    حالة AV_PIX_FMT_XV36:
        surface->داده_2.U = قاب->داده[0];
        surface->داده_2.Y = قاب->داده[0] + 2;
        surface->داده_2.V = قاب->داده[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->داده_2.A = قاب->داده[0] + 6;
        اكسر;
#إذا CONFIG_VAAPI
    حالة AV_PIX_FMT_UYVY422:
        surface->داده_2.Y = قاب->داده[0] + 1;
        surface->داده_2.U = قاب->داده[0];
        surface->داده_2.V = قاب->داده[0] + 2;
        اكسر;
#پایان_اگر
    افتراضي:
        أرجع MFX_ERR_UNSUPPORTED;
    }
    surface->داده_2.Pitch     = قاب->linesize[0];
    surface->داده_2.زمان_Stamp = قاب->pts;

    أرجع 0;
}

ساكن صحيح qsv_داخلی_session_check_init(AVHWFramesContext *ctx, صحيح upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    صحيح ret = 0;

    إذا (atomic_load(inited))
        أرجع 0;

#إذا HAVE_PTHREADS
    pthread_mutex_قفل(&s->session_قفل);
#پایان_اگر

    إذا (!atomic_load(inited)) {
        ret = qsv_init_داخلی_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#إذا HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_قفل);
#پایان_اگر

    أرجع ret;
}

ساكن صحيح qsv_transfer_داده_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ثابت AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfx_قاب_Surface1 بیرون = {{ 0 }};
    mfx_قاب_Surface1 *درون = (mfx_قاب_Surface1*)src->داده[3];

    mfx_Sync_نقطه sync = عدم;
    mfx_وضعیت err;
    صحيح ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_قاب = &s->realigned_download_قاب;
    AVFrame *dst_قاب;
    صحيح realigned = 0;

    ret = qsv_داخلی_session_check_init(ctx, 0);
    إذا (ret < 0)
        أرجع ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    إذا (dst->ارتفاع & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        إذا (tmp_قاب->format != dst->format ||
            tmp_قاب->عرض  != FFALIGN(dst->linesize[0], 16) ||
            tmp_قاب->ارتفاع != FFALIGN(dst->ارتفاع, 16)) {
            av_قاب_unref(tmp_قاب);

            tmp_قاب->format = dst->format;
            tmp_قاب->عرض  = FFALIGN(dst->linesize[0], 16);
            tmp_قاب->ارتفاع = FFALIGN(dst->ارتفاع, 16);
            ret = av_قاب_get_میانگیر(tmp_قاب, 0);
            إذا (ret < 0)
                أرجع ret;
        }
    }

    dst_قاب = realigned ? tmp_قاب : dst;

    إذا (!s->session_download) {
        إذا (s->فرزند_قابها_ref)
            أرجع qsv_transfer_داده_فرزند(ctx, dst_قاب, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        أرجع AVERROR(ENOSYS);
    }

    بیرون.Info = درون->Info;
    map_قاب_مقصد_surface(dst_قاب, &بیرون);

    افعل {
        err = MFXVideo_VPP_پیاپی_قاب_VPPAsync(s->session_download, درون, &بیرون, عدم, &sync);
        إذا (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } طالما (err == MFX_WRN_DEVICE_BUSY);

    إذا (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        أرجع AVERROR_UNKNOWN;
    }

    افعل {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } طالما (err == MFX_WRN_درون_EXECUTION);
    إذا (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        أرجع AVERROR_UNKNOWN;
    }

    إذا (realigned) {
        tmp_قاب->عرض  = dst->عرض;
        tmp_قاب->ارتفاع = dst->ارتفاع;
        ret = av_قاب_copy(dst, tmp_قاب);
        tmp_قاب->عرض  = FFALIGN(dst->linesize[0], 16);
        tmp_قاب->ارتفاع = FFALIGN(dst->ارتفاع, 16);
        إذا (ret < 0)
            أرجع ret;
    }

    أرجع 0;
}

ساكن صحيح qsv_transfer_داده_مقصد(AVHWFramesContext *ctx, AVFrame *dst,
                                ثابت AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfx_قاب_Surface1   درون = {{ 0 }};
    mfx_قاب_Surface1 *بیرون = (mfx_قاب_Surface1*)dst->داده[3];
    mfx_قاب_Info tmp_info;

    mfx_Sync_نقطه sync = عدم;
    mfx_وضعیت err;
    صحيح ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_قاب = &s->realigned_upload_قاب;
    ثابت AVFrame *src_قاب;
    صحيح realigned = 0;

    ret = qsv_داخلی_session_check_init(ctx, 1);
    إذا (ret < 0)
        أرجع ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    إذا (src->ارتفاع & 15 || src->linesize[0] & 15) {
        realigned = 1;
        إذا (tmp_قاب->format != src->format ||
            tmp_قاب->عرض  != FFALIGN(src->عرض, 16) ||
            tmp_قاب->ارتفاع != FFALIGN(src->ارتفاع, 16)) {
            av_قاب_unref(tmp_قاب);

            tmp_قاب->format = src->format;
            tmp_قاب->عرض  = FFALIGN(src->عرض, 16);
            tmp_قاب->ارتفاع = FFALIGN(src->ارتفاع, 16);
            ret = av_قاب_get_میانگیر(tmp_قاب, 0);
            إذا (ret < 0)
                أرجع ret;
        }
        ret = av_قاب_copy(tmp_قاب, src);
        إذا (ret < 0) {
            av_قاب_unref(tmp_قاب);
            أرجع ret;
        }
        ret = qsv_fill_border(tmp_قاب, src);
        إذا (ret < 0) {
            av_قاب_unref(tmp_قاب);
            أرجع ret;
        }

        tmp_info = بیرون->Info;
        بیرون->Info.CropW = FFMIN(بیرون->Info.عرض_2,  tmp_قاب->عرض);
        بیرون->Info.CropH = FFMIN(بیرون->Info.ارتفاع_2, tmp_قاب->ارتفاع);
    }

    src_قاب = realigned ? tmp_قاب : src;

    إذا (!s->session_upload) {
        إذا (s->فرزند_قابها_ref)
            أرجع qsv_transfer_داده_فرزند(ctx, dst, src_قاب);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        أرجع AVERROR(ENOSYS);
    }

    درون.Info = بیرون->Info;
    map_قاب_مقصد_surface(src_قاب, &درون);

    افعل {
        err = MFXVideo_VPP_پیاپی_قاب_VPPAsync(s->session_upload, &درون, بیرون, عدم, &sync);
        إذا (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } طالما (err == MFX_WRN_DEVICE_BUSY);

    إذا (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        أرجع AVERROR_UNKNOWN;
    }

    افعل {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } طالما (err == MFX_WRN_درون_EXECUTION);
    إذا (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        أرجع AVERROR_UNKNOWN;
    }

    إذا (realigned) {
        بیرون->Info.CropW = tmp_info.CropW;
        بیرون->Info.CropH = tmp_info.CropH;
    }

    أرجع 0;
}

ساكن صحيح qsv_dynamic_قابها_derive_مقصد(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, صحيح flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfx_قاب_Surface1 mfx_surf1;

    بدل (src_ctx->device_ctx->type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->قاب_type  = MFX_MEMTYPE_VIDEO_حافظه_DECODER_هدف;
        اكسر;
#پایان_اگر

#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        إذا (src_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف) {
            dst_hwctx->قاب_type |= MFX_MEMTYPE_VIDEO_حافظه_PROCESSOR_هدف;
        } وإلا {
            dst_hwctx->قاب_type |= MFX_MEMTYPE_VIDEO_حافظه_DECODER_هدف;
        }
    }
    اكسر;
#پایان_اگر

    افتراضي:
        أرجع AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, حجم(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->قاب_info = mfx_surf1.Info;
    dst_hwctx->info = &s->قاب_info;
    dst_hwctx->nb_surfaces = 0;
    أرجع 0;
}

ساكن صحيح qsv_fixed_قابها_derive_مقصد(AVHWFramesContext *dst_ctx,
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
            s->handle_جفتها_داخلی = av_calloc(src_ctx->initial_pool_اندازه,
                                                 حجم(*s->handle_جفتها_داخلی));
            إذا (!s->handle_جفتها_داخلی)
                أرجع AVERROR(ENOMEM);
            s->surfaces_داخلی = av_calloc(src_hwctx->nb_surfaces,
                                             حجم(*s->surfaces_داخلی));
            إذا (!s->surfaces_داخلی)
                أرجع AVERROR(ENOMEM);
            لكل (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_داخلی[i]);
                s->handle_جفتها_داخلی[i].اولی = src_hwctx->surface_ids + i;
                s->handle_جفتها_داخلی[i].دومی = (mfxMemId)MFX_INFINITE;
                s->surfaces_داخلی[i].داده_2.MemId = (mfxMemId)&s->handle_جفتها_داخلی[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->قاب_type  = MFX_MEMTYPE_VIDEO_حافظه_DECODER_هدف;
        }
        اكسر;
#پایان_اگر
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_جفتها_داخلی = av_calloc(src_ctx->initial_pool_اندازه,
                                                 حجم(*s->handle_جفتها_داخلی));
            إذا (!s->handle_جفتها_داخلی)
                أرجع AVERROR(ENOMEM);
            s->surfaces_داخلی = av_calloc(src_ctx->initial_pool_اندازه,
                                             حجم(*s->surfaces_داخلی));
            إذا (!s->surfaces_داخلی)
                أرجع AVERROR(ENOMEM);
            لكل (i = 0; i < src_ctx->initial_pool_اندازه; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_داخلی[i]);
                s->handle_جفتها_داخلی[i].اولی = (mfxMemId)src_hwctx->texture_infos[i].texture;
                إذا (src_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف) {
                    s->handle_جفتها_داخلی[i].دومی = (mfxMemId)MFX_INFINITE;
                } وإلا {
                    s->handle_جفتها_داخلی[i].دومی = (mfxMemId)src_hwctx->texture_infos[i].شاخص;
                }
                s->surfaces_داخلی[i].داده_2.MemId = (mfxMemId)&s->handle_جفتها_داخلی[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_اندازه;
            إذا (src_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف) {
                dst_hwctx->قاب_type |= MFX_MEMTYPE_VIDEO_حافظه_PROCESSOR_هدف;
            } وإلا {
                dst_hwctx->قاب_type |= MFX_MEMTYPE_VIDEO_حافظه_DECODER_هدف;
            }
        }
        اكسر;
#پایان_اگر
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_قابها_Context *src_hwctx = src_ctx->hwctx;
            s->handle_جفتها_داخلی = av_calloc(src_ctx->initial_pool_اندازه,
                                                 حجم(*s->handle_جفتها_داخلی));
            إذا (!s->handle_جفتها_داخلی)
                أرجع AVERROR(ENOMEM);
            s->surfaces_داخلی = av_calloc(src_hwctx->nb_surfaces,
                                             حجم(*s->surfaces_داخلی));
            إذا (!s->surfaces_داخلی)
                أرجع AVERROR(ENOMEM);
            لكل (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_داخلی[i]);
                s->handle_جفتها_داخلی[i].اولی = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_جفتها_داخلی[i].دومی = (mfxMemId)MFX_INFINITE;
                s->surfaces_داخلی[i].داده_2.MemId = (mfxMemId)&s->handle_جفتها_داخلی[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            إذا (src_hwctx->surface_type == DXVA2_Video_Processor_Render_هدف)
                dst_hwctx->قاب_type = MFX_MEMTYPE_VIDEO_حافظه_PROCESSOR_هدف;
            وإلا
                dst_hwctx->قاب_type = MFX_MEMTYPE_VIDEO_حافظه_DECODER_هدف;
        }
        اكسر;
#پایان_اگر
    افتراضي:
        أرجع AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_داخلی;

    أرجع 0;
}

ساكن صحيح qsv_قابها_derive_مقصد(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, صحيح flags)
{
    إذا (src_ctx->initial_pool_اندازه < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        أرجع AVERROR(EINVAL);
    } وإلا إذا (src_ctx->initial_pool_اندازه == 0) {
        أرجع qsv_dynamic_قابها_derive_مقصد(dst_ctx, src_ctx, flags);
    } وإلا {
        أرجع qsv_fixed_قابها_derive_مقصد(dst_ctx, src_ctx, flags);
    }
}

ساكن صحيح qsv_fixed_pool_map_مقصد(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    صحيح i, err, شاخص = -1;

    لكل (i = 0; i < hwctx->nb_surfaces && شاخص < 0; i++) {
        بدل(src->format) {
#إذا CONFIG_VAAPI
        حالة AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].داده_2.MemId;
            إذا (*(VASurfaceID*)pair->اولی == (VASurfaceID)(uintptr_t)src->داده[3])
                شاخص = i;
            اكسر;
        }
#پایان_اگر
#إذا CONFIG_D3D11VA
        حالة AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].داده_2.MemId;
            إذا (pair->اولی == src->داده[0]
                && (pair->دومی == src->داده[1]
                    || (pair->دومی == (mfxMemId)MFX_INFINITE && src->داده[1] == (uint8_t *)0)))
                شاخص = i;
            اكسر;
        }
#پایان_اگر
#إذا CONFIG_DXVA2
        حالة AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].داده_2.MemId;
            إذا (pair->اولی == src->داده[3])
                شاخص = i;
            اكسر;
        }
#پایان_اگر
        }
    }
    إذا (شاخص < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        أرجع AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_قابها_ctx,
                                dst, src, عدم, عدم);
    إذا (err)
        أرجع err;

    dst->عرض   = src->عرض;
    dst->ارتفاع  = src->ارتفاع;
    dst->داده[3] = (uint8_t*)&hwctx->surfaces[شاخص];

    أرجع 0;
}

ساكن فراغ qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfx_قاب_Surface1 *surfaces_داخلی = (mfx_قاب_Surface1 *)hwmap->priv;
    mfxHDLPair *handle_جفتها_داخلی = (mfxHDLPair *)surfaces_داخلی->داده_2.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->منبع_قابها->داده;

    بدل (src_ctx->format) {
#إذا CONFIG_VAAPI
    حالة AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_جفتها_داخلی->اولی);

        اكسر;
    }
#پایان_اگر

#إذا CONFIG_D3D11VA
    حالة AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        اكسر;
    }
#پایان_اگر
    افتراضي:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        اكسر;
    }

    av_freep(&handle_جفتها_داخلی);
    av_freep(&surfaces_داخلی);
}

ساكن صحيح qsv_dynamic_pool_map_مقصد(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    mfx_قاب_Surface1 *surfaces_داخلی = عدم;
    mfxHDLPair *handle_جفتها_داخلی = عدم;
    صحيح ret = 0;

    surfaces_داخلی = av_calloc(1, حجم(*surfaces_داخلی));
    إذا (!surfaces_داخلی) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    handle_جفتها_داخلی = av_calloc(1, حجم(*handle_جفتها_داخلی));
    إذا (!handle_جفتها_داخلی) {
        ret = AVERROR(ENOMEM);
        اذهب fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_داخلی);
    إذا (ret < 0)
        اذهب fail;

    بدل (src->format) {
#إذا CONFIG_VAAPI
    حالة AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_داخلی;

        surface_id_داخلی = av_calloc(1, حجم(*surface_id_داخلی));
        إذا (!surface_id_داخلی) {
            ret =AVERROR(ENOMEM);
            اذهب fail;
        }

        *surface_id_داخلی = (VASurfaceID)(uintptr_t)src->داده[3];
        handle_جفتها_داخلی->اولی = (mfxHDL)surface_id_داخلی;
        handle_جفتها_داخلی->دومی = (mfxMemId)MFX_INFINITE;

        اكسر;
    }
#پایان_اگر

#إذا CONFIG_D3D11VA
    حالة AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_قابها_ctx->داده;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_جفتها_داخلی->اولی = (mfxMemId)src->داده[0];

        إذا (src_hwctx->BindFlags & D3_D11_BIND_RENDER_هدف) {
            handle_جفتها_داخلی->دومی = (mfxMemId)MFX_INFINITE;
        } وإلا {
            handle_جفتها_داخلی->دومی = (mfxMemId)src->داده[1];
        }

        اكسر;
    }
#پایان_اگر
    افتراضي:
        ret = AVERROR(ENOSYS);
        اذهب fail;
    }

    surfaces_داخلی->داده_2.MemId = (mfxMemId)handle_جفتها_داخلی;

    ret = ff_hwframe_map_create(dst->hw_قابها_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_داخلی);
    إذا (ret)
        اذهب fail;

    dst->عرض   = src->عرض;
    dst->ارتفاع  = src->ارتفاع;
    dst->داده[3] = (uint8_t*)surfaces_داخلی;

    أرجع 0;

fail:
    av_freep(&handle_جفتها_داخلی);
    av_freep(&surfaces_داخلی);
    أرجع ret;
}

ساكن صحيح qsv_map_مقصد(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ثابت AVFrame *src, صحيح flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    إذا (hwctx->nb_surfaces)
        أرجع qsv_fixed_pool_map_مقصد(dst_ctx, dst, src, flags);
    وإلا
        أرجع qsv_dynamic_pool_map_مقصد(dst_ctx, dst, src, flags);
}

ساكن صحيح qsv_قابها_get_constraints(AVHWDeviceContext *ctx,
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
    av_میانگیر_unref(&priv->فرزند_device_ctx);
    av_freep(&priv);
}

ساكن mfxIMPL انتخاب_implementation(ثابت حرف *device, تعداد AVHWDeviceType فرزند_device_type)
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
        إذا (فرزند_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_از_طریق_D3_D11;
        وإلا إذا (فرزند_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_از_طریق_D3_D9;
    }

    أرجع impl;
}

ساكن صحيح qsv_device_derive_from_فرزند(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *فرزند_device_ctx,
                                        صحيح flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfx_نسخه    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfx_وضعیت     err;
    صحيح ret;

    بدل (فرزند_device_ctx->type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *فرزند_device_hwctx = فرزند_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)فرزند_device_hwctx->display;
        }
        اكسر;
#پایان_اگر
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *فرزند_device_hwctx = فرزند_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)فرزند_device_hwctx->device;
        }
        اكسر;
#پایان_اگر
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *فرزند_device_hwctx = فرزند_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)فرزند_device_hwctx->devmgr;
        }
        اكسر;
#پایان_اگر
    افتراضي:
        ret = AVERROR(ENOSYS);
        اذهب fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    إذا (ret)
        اذهب fail;

    err = MFXVideo_CORE_مجموعه_Handle(hwctx->session, handle_type, handle);
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
                             AVHWDeviceContext *فرزند_device_ctx,
                             AVDictionary *opts, صحيح flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(حجم(*priv));
    إذا (!priv)
        أرجع AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->حرر = qsv_device_free;

    impl = انتخاب_implementation("hw_any", فرزند_device_ctx->type);
    أرجع qsv_device_derive_from_فرزند(ctx, impl,
                                        فرزند_device_ctx, flags);
}

ساكن صحيح qsv_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                             AVDictionary *opts, صحيح flags)
{
    QSVDevicePriv *priv;
    تعداد AVHWDeviceType فرزند_device_type;
    AVHWDeviceContext *فرزند_device;
    AVDictionary *فرزند_device_opts;
    AVDictionary_مدخل *e;

    mfxIMPL impl;
    صحيح ret;

    priv = av_mallocz(حجم(*priv));
    إذا (!priv)
        أرجع AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->حرر        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", عدم, 0);
    إذا (e) {
        فرزند_device_type = av_hwdevice_پیدا_کن_type_by_name(e->مقدار);
        إذا (فرزند_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->مقدار);
            أرجع AVERROR(EINVAL);
        }
#إذا QSV_ONEVPL
    } وإلا إذا (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        فرزند_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } وإلا إذا (CONFIG_DXVA2) {
        فرزند_device_type = AV_HWDEVICE_TYPE_DXVA2;
#وإلا
    } وإلا إذا (CONFIG_DXVA2) {
        av_log(عدم, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        فرزند_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } وإلا إذا (CONFIG_D3D11VA) {
        فرزند_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#پایان_اگر
    } وإلا إذا (CONFIG_VAAPI) {
        فرزند_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } وإلا {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        أرجع AVERROR(ENOSYS);
    }

#إذا CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    إذا (فرزند_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->مقدار);
        أرجع AVERROR(EINVAL);
    }
#پایان_اگر

    فرزند_device_opts = عدم;
    بدل (فرزند_device_type) {
#إذا CONFIG_VAAPI
    حالة AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_مجموعه(&فرزند_device_opts, "vendor_id", "0x8086", 0);
            av_dict_مجموعه(&فرزند_device_opts, "driver",    "iHD",    0);
        }
        اكسر;
#پایان_اگر
#إذا CONFIG_D3D11VA
    حالة AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_مجموعه(&فرزند_device_opts, "vendor_id",        "0x8086",  0);
        }
        اكسر;
#پایان_اگر
#إذا CONFIG_DXVA2
    حالة AV_HWDEVICE_TYPE_DXVA2:
#إذا QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#پایان_اگر
        اكسر;
#پایان_اگر
    افتراضي:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            أرجع AVERROR(ENOSYS);
        }
        اكسر;
    }

    e = av_dict_get(opts, "child_device", عدم, 0);
    ret = av_hwdevice_ctx_create(&priv->فرزند_device_ctx, فرزند_device_type,
                                 e ? e->مقدار : عدم, فرزند_device_opts, 0);

    av_dict_free(&فرزند_device_opts);
    إذا (ret < 0)
        أرجع ret;

    فرزند_device = (AVHWDeviceContext*)priv->فرزند_device_ctx->داده;

    impl = انتخاب_implementation(device, فرزند_device_type);

    أرجع qsv_device_derive_from_فرزند(ctx, impl, فرزند_device, 0);
}

ثابت HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_اندازه      = حجم(QSVDeviceContext),
    .قابها_hwctx_اندازه      = حجم(QSVFramesContext),

    .device_create          = qsv_device_create,
    .device_derive          = qsv_device_derive,
    .device_init            = qsv_device_init,
    .قابها_get_constraints = qsv_قابها_get_constraints,
    .قابها_init            = qsv_قابها_init,
    .قابها_uninit          = qsv_قابها_uninit,
    .قابها_get_میانگیر      = qsv_get_میانگیر,
    .transfer_get_formats   = qsv_transfer_get_formats,
    .transfer_داده_مقصد       = qsv_transfer_داده_مقصد,
    .transfer_داده_from     = qsv_transfer_داده_from,
    .map_مقصد                 = qsv_map_مقصد,
    .map_from               = qsv_map_from,
    .قابها_derive_مقصد       = qsv_قابها_derive_مقصد,
    .قابها_derive_from     = qsv_قابها_derive_from,

    .pix_fmts = (ثابت تعداد AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
