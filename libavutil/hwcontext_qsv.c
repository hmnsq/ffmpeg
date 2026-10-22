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

#شامل <stdatomic.h>
#شامل <stdint.h>
#شامل <string.h>

#شامل <mfxvideo.h>

#شامل "config.h"

#اگر HAVE_PTHREADS
#شامل <pthread.h>
#اگر_ختم

#تعریف_کرو COBJMACROS
#اگر CONFIG_VAAPI
#شامل "hwcontext_vaapi.h"
#اگر_ختم
#اگر CONFIG_D3D11VA
#شامل "hwcontext_d3d11va.h"
#اگر_ختم
#اگر CONFIG_DXVA2
#شامل <initguid.h>
#شامل "hwcontext_dxva2.h"
#اگر_ختم

#شامل "buffer.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_internal.h"
#شامل "hwcontext_qsv.h"
#شامل "mem.h"
#شامل "pixfmt.h"
#شامل "pixdesc.h"
#شامل "time.h"
#شامل "imgutils.h"
#شامل "avassert.h"

#تعریف_کرو QSV_نسخہ_ATLEAST(MAJOR, MINOR)   \
    (MFX_نسخہ_MAJOR > (MAJOR) ||         \
     MFX_نسخہ_MAJOR == (MAJOR) && MFX_نسخہ_MINOR >= (MINOR))

#تعریف_کرو QSV_RUNTIME_نسخہ_ATLEAST(MFX_نسخہ, MAJOR, MINOR)          \
    ((MFX_نسخہ.Major > (MAJOR)) ||                                   \
     (MFX_نسخہ.Major == (MAJOR) && MFX_نسخہ.Minor >= (MINOR)))

#تعریف_کرو MFX_IMPL_بذریعہ_نقاب(impl) (0x0f00 & (impl))
#تعریف_کرو QSV_ONEVPL       QSV_نسخہ_ATLEAST(2, 0)
#تعریف_کرو QSV_HAVE_OPAQUE  !QSV_ONEVPL

#اگر QSV_ONEVPL
#شامل <mfxdispatcher.h>
#ورنہ
#تعریف_کرو MFXUnload(a) کرو { } جب(0)
#اگر_ختم

قسمتعریف ساخت QSVDevicePriv {
    AVBufferRef *بچہ_device_ctx;
} QSVDevicePriv;

قسمتعریف ساخت QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfx_نسخہ          ver;
    mfxIMPL             impl;

    شمار AVHWDeviceType بچہ_device_type;
    شمار AVPixelFormat  بچہ_pix_fmt;
} QSVDeviceContext;

قسمتعریف ساخت QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#اگر HAVE_PTHREADS
    pthread_mutex_t session_تالا;
#اگر_ختم

    AVBufferRef *بچہ_چوکھٹے_ref;
    mfx_چوکھٹا_Surface1 *surfaces_اندرونی;
    mfxHDLPair *handle_جوڑے_اندرونی;
    صحیح             nb_surfaces_مستعمل;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#اگر QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfx_چوکھٹا_Surface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfx_Ext_بفر *ext_buffers[1];
#اگر_ختم
    AVFrame realigned_upload_چوکھٹا;
    AVFrame realigned_download_چوکھٹا;

    mfx_چوکھٹا_Info چوکھٹا_info;
} QSVFramesContext;

قسمتعریف ساخت QSVSurface {
    mfx_چوکھٹا_Surface1 mfx_surface;
    AVFrame *بچہ_چوکھٹا;
} QSVSurface;

ساکن ثابت ساخت {
    شمار AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_سرکاؤ;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#اگر CONFIG_VAAPI
    { AV_PIX_FMT_UYVY422,
                       MFX_FOURCC_UYVY, 0 },
#اگر_ختم
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
#اگر QSV_نسخہ_ATLEAST(1, 31)
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
#اگر_ختم
};

خارجی صحیح ff_qsv_get_surface_بنیاد_handle(mfx_چوکھٹا_Surface1 *surf,
                                          شمار AVHWDeviceType بنیاد_dev_type,
                                          خالی **بنیاد_handle);

ساکن صحیح qsv_init_surface(AVHWFramesContext *ctx, mfx_چوکھٹا_Surface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
صحیح ff_qsv_get_surface_بنیاد_handle(mfx_چوکھٹا_Surface1 *surf,
                                   شمار AVHWDeviceType بنیاد_dev_type,
                                   خالی **بنیاد_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->ڈیٹا_2.MemId;
    انتخاب (بنیاد_dev_type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
        بنیاد_handle[0] = handle_pair->پہلا;
        واپس 0;
#اگر_ختم
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        بنیاد_handle[0] = handle_pair->پہلا;
        بنیاد_handle[1] = handle_pair->دوسرا;
        واپس 0;
#اگر_ختم
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
        بنیاد_handle[0] = handle_pair->پہلا;
        واپس 0;
#اگر_ختم
    }
    واپس AVERROR(EINVAL);
}

ساکن uint32_t qsv_fourcc_from_pix_fmt(شمار AVPixelFormat pix_fmt)
{
    صحیح i;
    برائے (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        اگر (supported_pixel_formats[i].pix_fmt == pix_fmt)
            واپس supported_pixel_formats[i].fourcc;
    }
    واپس 0;
}

ساکن uint16_t qsv_سرکاؤ_from_pix_fmt(شمار AVPixelFormat pix_fmt)
{
    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        اگر (supported_pixel_formats[i].pix_fmt == pix_fmt)
            واپس supported_pixel_formats[i].mfx_سرکاؤ;
    }

    واپس 0;
}

#اگر CONFIG_D3D11VA
ساکن uint32_t qsv_get_d3d11va_bind_flags(صحیح mem_type)
{
    uint32_t bind_flags = 0;

    اگر ((mem_type & MFX_MEMTYPE_VIDEO_حافظہ_ENCODER_ہدف) && (mem_type & MFX_MEMTYPE_اندرونی_چوکھٹا))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    ورنہ
        bind_flags = D3D11_BIND_DECODER;

    اگر ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_حافظہ_PROCESSOR_ہدف & mem_type))
        bind_flags = D3_D11_BIND_RENDER_ہدف;

    واپس bind_flags;
}
#اگر_ختم

ساکن صحیح qsv_fill_border(AVFrame *dst, ثابت AVFrame *src)
{
    ثابت AVPixFmtDescriptor *desc;
    صحیح i, planes_nb = 0;
    اگر (dst->format != src->format)
        واپس AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    برائے (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    برائے (i = 0; i < planes_nb; i++) {
        صحیح sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->چوڑائی,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->چوڑائی,
                                                 i);
        ثابت AVComponentDescriptor comp = desc->comp[i];
        اگر (swidth < 0 || dwidth < 0) {
            av_log(تہی, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            واپس AVERROR(EINVAL);
        }
        sheight = src->اونچائی;
        dheight = dst->اونچائی;
        اگر (i) {
            sheight = AV_CEIL_RSHIFT(src->اونچائی, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->اونچائی, desc->log2_chroma_h);
        }
        //fill right padding
        برائے (y = 0; y < sheight; y++) {
            خالی *سطر_ptr = dst->ڈیٹا[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(سطر_ptr,
                           comp.گہرائی > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        برائے (y = sheight; y < dheight; y++) {
            حافظہ_نقل(dst->ڈیٹا[i]+y*dst->linesize[i],
                   dst->ڈیٹا[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    واپس 0;
}

ساکن صحیح qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    صحیح   hw_handle_supported = 0;
    mfxHandleType handle_type;
    شمار AVHWDeviceType device_type;
    شمار AVPixelFormat  pix_fmt;
    mfx_حالت err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    اگر (err == MFX_ERR_NONE)
        err = MFXQuery_نسخہ(hwctx->session, &s->ver);
    اگر (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        واپس AVERROR_UNKNOWN;
    }

    اگر (MFX_IMPL_بذریعہ_VAAPI == MFX_IMPL_بذریعہ_نقاب(s->impl)) {
#اگر CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#اگر_ختم
    } ورنہ اگر (MFX_IMPL_بذریعہ_D3_D11 == MFX_IMPL_بذریعہ_نقاب(s->impl)) {
#اگر CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#اگر_ختم
    } ورنہ اگر (MFX_IMPL_بذریعہ_D3_D9 == MFX_IMPL_بذریعہ_نقاب(s->impl)) {
#اگر CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#اگر_ختم
    }

    اگر (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        اگر (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->بچہ_device_type = device_type;
            s->بچہ_pix_fmt     = pix_fmt;
        }
    }
    اگر (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    واپس 0;
}

ساکن خالی qsv_چوکھٹے_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    اگر (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = تہی;
    s->session_download_init = 0;

    اگر (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = تہی;
    s->session_upload_init = 0;

#اگر HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_تالا);
#اگر_ختم

    av_freep(&s->mem_ids);
#اگر QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#اگر_ختم
    av_freep(&s->surfaces_اندرونی);
    av_freep(&s->handle_جوڑے_اندرونی);
    av_چوکھٹا_unref(&s->realigned_upload_چوکھٹا);
    av_چوکھٹا_unref(&s->realigned_download_چوکھٹا);
    av_بفر_unref(&s->بچہ_چوکھٹے_ref);
}

ساکن خالی qsv_pool_release_dummy(خالی *opaque, uint8_t *ڈیٹا)
{
}

ساکن خالی qsv_pool_release(خالی *opaque, uint8_t *ڈیٹا)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)ڈیٹا;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.ڈیٹا_2.MemId;
    AVHWFramesContext *بچہ_چوکھٹے_ctx;

    اگر (!s->بچہ_چوکھٹے_ref)
        واپس;

    بچہ_چوکھٹے_ctx = (AVHWFramesContext*)s->بچہ_چوکھٹے_ref->ڈیٹا;
    اگر (!بچہ_چوکھٹے_ctx->device_ctx)
        واپس;

#اگر CONFIG_VAAPI
    اگر (بچہ_چوکھٹے_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->پہلا);
#اگر_ختم

    av_freep(&hdl_pair);
    av_چوکھٹا_free(&qsv_surface->بچہ_چوکھٹا);
    av_freep(&qsv_surface);
}

ساکن AVBufferRef *qsv_fixed_pool_alloc(خالی *opaque, size_t سائز)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    اگر (s->nb_surfaces_مستعمل < hwctx->nb_surfaces) {
        s->nb_surfaces_مستعمل++;
        واپس av_بفر_create((uint8_t*)(s->surfaces_اندرونی + s->nb_surfaces_مستعمل - 1),
                                حجم(*hwctx->surfaces), qsv_pool_release_dummy, تہی, 0);
    }

    واپس تہی;
}

ساکن AVBufferRef *qsv_dynamic_pool_alloc(خالی *opaque, size_t سائز)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *بچہ_چوکھٹے_ctx;
    QSVSurface *qsv_surface = تہی;
    mfxHDLPair *handle_جوڑے_اندرونی = تہی;
    صحیح ret;

    اگر (!s->بچہ_چوکھٹے_ref)
        جاؤ fail;

    بچہ_چوکھٹے_ctx = (AVHWFramesContext*)s->بچہ_چوکھٹے_ref->ڈیٹا;
    اگر (!بچہ_چوکھٹے_ctx->device_ctx)
        جاؤ fail;

#اگر CONFIG_DXVA2
    اگر (بچہ_چوکھٹے_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        جاؤ fail;
    }
#اگر_ختم

    qsv_surface = av_calloc(1, حجم(*qsv_surface));
    اگر (!qsv_surface)
        جاؤ fail;

    qsv_surface->بچہ_چوکھٹا = av_چوکھٹا_alloc();
    اگر (!qsv_surface->بچہ_چوکھٹا)
        جاؤ fail;

    ret = av_hwframe_get_بفر(s->بچہ_چوکھٹے_ref, qsv_surface->بچہ_چوکھٹا, 0);
    اگر (ret < 0)
        جاؤ fail;

    handle_جوڑے_اندرونی = av_calloc(1, حجم(*handle_جوڑے_اندرونی));
    اگر (!handle_جوڑے_اندرونی)
        جاؤ fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    اگر (ret < 0)
        جاؤ fail;

#اگر CONFIG_VAAPI
    اگر (بچہ_چوکھٹے_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_اندرونی;

        surface_id_اندرونی = av_calloc(1, حجم(*surface_id_اندرونی));
        اگر (!surface_id_اندرونی)
            جاؤ fail;

        *surface_id_اندرونی = (VASurfaceID)(uintptr_t)qsv_surface->بچہ_چوکھٹا->ڈیٹا[3];
        handle_جوڑے_اندرونی->پہلا = (mfxHDL)surface_id_اندرونی;
        handle_جوڑے_اندرونی->دوسرا = (mfxMemId)MFX_INFINITE;
    }
#اگر_ختم

#اگر CONFIG_D3D11VA
    اگر (بچہ_چوکھٹے_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *بچہ_چوکھٹے_hwctx = بچہ_چوکھٹے_ctx->hwctx;
        handle_جوڑے_اندرونی->پہلا = (mfxMemId)qsv_surface->بچہ_چوکھٹا->ڈیٹا[0];

        اگر (بچہ_چوکھٹے_hwctx->BindFlags & D3_D11_BIND_RENDER_ہدف)
            handle_جوڑے_اندرونی->دوسرا = (mfxMemId)MFX_INFINITE;
        ورنہ
            handle_جوڑے_اندرونی->دوسرا = (mfxMemId)qsv_surface->بچہ_چوکھٹا->ڈیٹا[1];

    }
#اگر_ختم

    qsv_surface->mfx_surface.ڈیٹا_2.MemId = (mfxMemId)handle_جوڑے_اندرونی;
    واپس av_بفر_create((uint8_t *)qsv_surface, حجم(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    اگر (qsv_surface) {
        av_چوکھٹا_free(&qsv_surface->بچہ_چوکھٹا);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_جوڑے_اندرونی);

    واپس تہی;
}

ساکن AVBufferRef *qsv_pool_alloc(خالی *opaque, size_t سائز)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    اگر (hwctx->nb_surfaces == 0) {
        واپس qsv_dynamic_pool_alloc(opaque, سائز);
    } ورنہ {
        واپس qsv_fixed_pool_alloc(opaque, سائز);
    }
}

ساکن صحیح qsv_init_بچہ_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *بچہ_device_ref = تہی;
    AVBufferRef *بچہ_چوکھٹے_ref = تہی;

    AVHWDeviceContext *بچہ_device_ctx;
    AVHWFramesContext *بچہ_چوکھٹے_ctx;

    صحیح i, ret = 0;

    اگر (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        واپس AVERROR(EINVAL);
    }

    بچہ_device_ref = av_hwdevice_ctx_alloc(device_priv->بچہ_device_type);
    اگر (!بچہ_device_ref)
        واپس AVERROR(ENOMEM);
    بچہ_device_ctx   = (AVHWDeviceContext*)بچہ_device_ref->ڈیٹا;

#اگر CONFIG_VAAPI
    اگر (بچہ_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *بچہ_device_hwctx = بچہ_device_ctx->hwctx;
        بچہ_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#اگر_ختم
#اگر CONFIG_D3D11VA
    اگر (بچہ_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *بچہ_device_hwctx = بچہ_device_ctx->hwctx;
        ID3_D11_Device_جوڑو_Ref((ID3D11Device*)device_priv->handle);
        بچہ_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#اگر_ختم
#اگر CONFIG_DXVA2
    اگر (بچہ_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *بچہ_device_hwctx = بچہ_device_ctx->hwctx;
        بچہ_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#اگر_ختم

    ret = av_hwdevice_ctx_init(بچہ_device_ref);
    اگر (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        جاؤ fail;
    }

    بچہ_چوکھٹے_ref = av_hwframe_ctx_alloc(بچہ_device_ref);
    اگر (!بچہ_چوکھٹے_ref) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }
    بچہ_چوکھٹے_ctx = (AVHWFramesContext*)بچہ_چوکھٹے_ref->ڈیٹا;

    بچہ_چوکھٹے_ctx->format            = device_priv->بچہ_pix_fmt;
    بچہ_چوکھٹے_ctx->sw_format         = ctx->sw_format;
    بچہ_چوکھٹے_ctx->initial_pool_سائز = ctx->initial_pool_سائز;
    بچہ_چوکھٹے_ctx->چوڑائی             = FFALIGN(ctx->چوڑائی, 16);
    بچہ_چوکھٹے_ctx->اونچائی            = FFALIGN(ctx->اونچائی, 16);

#اگر CONFIG_D3D11VA
    اگر (بچہ_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *بچہ_چوکھٹے_hwctx = بچہ_چوکھٹے_ctx->hwctx;
        اگر (hwctx->چوکھٹا_type == 0)
            hwctx->چوکھٹا_type = MFX_MEMTYPE_VIDEO_حافظہ_PROCESSOR_ہدف;
        اگر (hwctx->چوکھٹا_type & MFX_MEMTYPE_SHARED_RESOURCE)
            بچہ_چوکھٹے_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        بچہ_چوکھٹے_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->چوکھٹا_type);
    }
#اگر_ختم
#اگر CONFIG_DXVA2
    اگر (بچہ_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_چوکھٹے_Context *بچہ_چوکھٹے_hwctx = بچہ_چوکھٹے_ctx->hwctx;
        اگر (hwctx->چوکھٹا_type & MFX_MEMTYPE_VIDEO_حافظہ_PROCESSOR_ہدف)
            بچہ_چوکھٹے_hwctx->surface_type = DXVA2_Video_Processor_Render_ہدف;
        ورنہ
            بچہ_چوکھٹے_hwctx->surface_type = DXVA2_Video_Decoder_Render_ہدف;
    }
#اگر_ختم

    ret = av_hwframe_ctx_init(بچہ_چوکھٹے_ref);
    اگر (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        جاؤ fail;
    }

#اگر CONFIG_VAAPI
    اگر (بچہ_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *بچہ_چوکھٹے_hwctx = بچہ_چوکھٹے_ctx->hwctx;
        برائے (i = 0; i < ctx->initial_pool_سائز; i++) {
            s->handle_جوڑے_اندرونی[i].پہلا = بچہ_چوکھٹے_hwctx->surface_ids + i;
            s->handle_جوڑے_اندرونی[i].دوسرا = (mfxMemId)MFX_INFINITE;
            s->surfaces_اندرونی[i].ڈیٹا_2.MemId = (mfxMemId)&s->handle_جوڑے_اندرونی[i];
        }
        hwctx->چوکھٹا_type = MFX_MEMTYPE_VIDEO_حافظہ_DECODER_ہدف;
    }
#اگر_ختم
#اگر CONFIG_D3D11VA
    اگر (بچہ_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *بچہ_چوکھٹے_hwctx = بچہ_چوکھٹے_ctx->hwctx;
        برائے (i = 0; i < ctx->initial_pool_سائز; i++) {
            s->handle_جوڑے_اندرونی[i].پہلا = (mfxMemId)بچہ_چوکھٹے_hwctx->texture_infos[i].texture;
            اگر(بچہ_چوکھٹے_hwctx->BindFlags & D3_D11_BIND_RENDER_ہدف) {
                s->handle_جوڑے_اندرونی[i].دوسرا = (mfxMemId)MFX_INFINITE;
            } ورنہ {
                s->handle_جوڑے_اندرونی[i].دوسرا = (mfxMemId)بچہ_چوکھٹے_hwctx->texture_infos[i].اشاریہ;
            }
            s->surfaces_اندرونی[i].ڈیٹا_2.MemId = (mfxMemId)&s->handle_جوڑے_اندرونی[i];
        }
        اگر (بچہ_چوکھٹے_hwctx->BindFlags & D3_D11_BIND_RENDER_ہدف) {
            hwctx->چوکھٹا_type |= MFX_MEMTYPE_VIDEO_حافظہ_PROCESSOR_ہدف;
        } ورنہ {
            hwctx->چوکھٹا_type |= MFX_MEMTYPE_VIDEO_حافظہ_DECODER_ہدف;
        }
    }
#اگر_ختم
#اگر CONFIG_DXVA2
    اگر (بچہ_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_چوکھٹے_Context *بچہ_چوکھٹے_hwctx = بچہ_چوکھٹے_ctx->hwctx;
        برائے (i = 0; i < ctx->initial_pool_سائز; i++) {
            s->handle_جوڑے_اندرونی[i].پہلا = (mfxMemId)بچہ_چوکھٹے_hwctx->surfaces[i];
            s->handle_جوڑے_اندرونی[i].دوسرا = (mfxMemId)MFX_INFINITE;
            s->surfaces_اندرونی[i].ڈیٹا_2.MemId = (mfxMemId)&s->handle_جوڑے_اندرونی[i];
        }
        اگر (بچہ_چوکھٹے_hwctx->surface_type == DXVA2_Video_Processor_Render_ہدف)
            hwctx->چوکھٹا_type = MFX_MEMTYPE_VIDEO_حافظہ_PROCESSOR_ہدف;
        ورنہ
            hwctx->چوکھٹا_type = MFX_MEMTYPE_VIDEO_حافظہ_DECODER_ہدف;
    }
#اگر_ختم

    s->بچہ_چوکھٹے_ref       = بچہ_چوکھٹے_ref;
    بچہ_چوکھٹے_ref          = تہی;

fail:
    av_بفر_unref(&بچہ_device_ref);
    av_بفر_unref(&بچہ_چوکھٹے_ref);
    واپس ret;
}

ساکن صحیح qsv_init_surface(AVHWFramesContext *ctx, mfx_چوکھٹا_Surface1 *surf)
{
    ثابت AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    اگر (!desc)
        واپس AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    اگر (!fourcc)
        واپس AVERROR(EINVAL);

    surf->Info.ثنائی_ہندسہ_گہرائی_Luma   = desc->comp[0].گہرائی;
    surf->Info.ثنائی_ہندسہ_گہرائی_Chroma = desc->comp[0].گہرائی;
    surf->Info.سرکاؤ_2          = qsv_سرکاؤ_from_pix_fmt(ctx->sw_format);

    اگر (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    ورنہ اگر (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    ورنہ
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.چوڑائی_2          = FFALIGN(ctx->چوڑائی, 16);
    surf->Info.CropW          = ctx->چوڑائی;
    surf->Info.اونچائی_2         = FFALIGN(ctx->اونچائی, 16);
    surf->Info.CropH          = ctx->اونچائی;
    surf->Info.چوکھٹا_شرح_Ext_N  = 25;
    surf->Info.چوکھٹا_شرح_Ext_D  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    واپس 0;
}

ساکن صحیح qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *چوکھٹے_hwctx = &s->p;

    صحیح i, ret = 0;

    اگر (ctx->initial_pool_سائز < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        واپس AVERROR(EINVAL);
    } ورنہ اگر (ctx->initial_pool_سائز == 0) {
        mfx_چوکھٹا_Surface1 mfx_surf1;

        ret = qsv_init_بچہ_ctx(ctx);
        اگر (ret < 0)
            واپس ret;

        ffhwframesctx(ctx)->pool_اندرونی = av_بفر_pool_init2(حجم(mfx_چوکھٹا_Surface1),
                                                                 ctx, qsv_pool_alloc, تہی);
        اگر (!ffhwframesctx(ctx)->pool_اندرونی)
            واپس AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, حجم(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->چوکھٹا_info = mfx_surf1.Info;
        چوکھٹے_hwctx->info = &s->چوکھٹا_info;
        چوکھٹے_hwctx->nb_surfaces = 0;

        واپس 0;
    }

    s->handle_جوڑے_اندرونی = av_calloc(ctx->initial_pool_سائز,
                                         حجم(*s->handle_جوڑے_اندرونی));
    اگر (!s->handle_جوڑے_اندرونی)
        واپس AVERROR(ENOMEM);

    s->surfaces_اندرونی = av_calloc(ctx->initial_pool_سائز,
                                     حجم(*s->surfaces_اندرونی));
    اگر (!s->surfaces_اندرونی)
        واپس AVERROR(ENOMEM);

    برائے (i = 0; i < ctx->initial_pool_سائز; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_اندرونی[i]);
        اگر (ret < 0)
            واپس ret;
    }

#اگر QSV_HAVE_OPAQUE
    اگر (!(چوکھٹے_hwctx->چوکھٹا_type & MFX_MEMTYPE_OPAQUE_چوکھٹا)) {
        ret = qsv_init_بچہ_ctx(ctx);
        اگر (ret < 0)
            واپس ret;
    }
#ورنہ
    ret = qsv_init_بچہ_ctx(ctx);
    اگر (ret < 0)
        واپس ret;
#اگر_ختم

    ffhwframesctx(ctx)->pool_اندرونی = av_بفر_pool_init2(حجم(mfx_چوکھٹا_Surface1),
                                                             ctx, qsv_pool_alloc, تہی);
    اگر (!ffhwframesctx(ctx)->pool_اندرونی)
        واپس AVERROR(ENOMEM);

    چوکھٹے_hwctx->surfaces    = s->surfaces_اندرونی;
    چوکھٹے_hwctx->nb_surfaces = ctx->initial_pool_سائز;

    واپس 0;
}

ساکن mfx_حالت چوکھٹا_alloc(mfxHDL pthis, mfx_چوکھٹا_Alloc_Request *req,
                             mfx_چوکھٹا_Alloc_Response *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfx_چوکھٹا_Info *i  = &req->Info;
    mfx_چوکھٹا_Info *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    اگر (!(req->Type & MFX_MEMTYPE_VIDEO_حافظہ_PROCESSOR_ہدف) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_چوکھٹا))
        واپس MFX_ERR_UNSUPPORTED;
    اگر (i->چوڑائی_2  > i1->چوڑائی_2 || i->اونچائی_2 > i1->اونچائی_2 ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->چوڑائی_2,  i->اونچائی_2,  i->FourCC,  i->ChromaFormat,
               i1->چوڑائی_2, i1->اونچائی_2, i1->FourCC, i1->ChromaFormat);
        واپس MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->عدد_چوکھٹا_Actual = hwctx->nb_surfaces;

    واپس MFX_ERR_NONE;
}

ساکن mfx_حالت چوکھٹا_free(mfxHDL pthis, mfx_چوکھٹا_Alloc_Response *resp)
{
    واپس MFX_ERR_NONE;
}

ساکن mfx_حالت چوکھٹا_تالا(mfxHDL pthis, mfxMemId mid, mfx_چوکھٹا_ڈیٹا *ptr)
{
    واپس MFX_ERR_UNSUPPORTED;
}

ساکن mfx_حالت چوکھٹا_unlock(mfxHDL pthis, mfxMemId mid, mfx_چوکھٹا_ڈیٹا *ptr)
{
    واپس MFX_ERR_UNSUPPORTED;
}

ساکن mfx_حالت چوکھٹا_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->پہلا = pair_src->پہلا;

    اگر (pair_src->دوسرا != (mfxMemId)MFX_INFINITE)
        pair_dst->دوسرا = pair_src->دوسرا;
    واپس MFX_ERR_NONE;
}

#اگر QSV_ONEVPL

ساکن صحیح qsv_d3d11_update_config(خالی *ctx, mfxHDL handle, mfxConfig cfg)
{
    صحیح ret = AVERROR_UNKNOWN;
#اگر CONFIG_D3D11VA
    mfx_حالت sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = تہی;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_قدر = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (خالی**)&pDXGIDevice);
    اگر (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        اگر (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            واپس ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        اگر (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            جاؤ fail;
        }
    } ورنہ {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        واپس ret;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_U16;
    impl_قدر.ڈیٹا_2.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_قدر);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        جاؤ fail;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_PTR;
    impl_قدر.ڈیٹا_2.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_قدر);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        جاؤ fail;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_U32;
    impl_قدر.ڈیٹا_2.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_قدر);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        جاؤ fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#اگر_ختم
    واپس ret;
}

ساکن صحیح qsv_d3d9_update_config(خالی *ctx, mfxHDL handle, mfxConfig cfg)
{
    صحیح ret = AVERROR_UNKNOWN;
#اگر CONFIG_DXVA2
    mfx_حالت sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = تہی;
    IDirect3DDevice9Ex *device_ex = تہی;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = تہی;
    IDirect3D9 *d3d9 = تہی;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_قدر = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        جاؤ fail;
    }

    hr = IDirect3_DDevice_Manager9_تالا_Device(devmgr, device_handle, &device, TRUE);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        جاؤ fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (خالی **)&device_ex);
    IDirect3DDevice9_Release(device);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        جاؤ unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        جاؤ unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        جاؤ unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (خالی **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        جاؤ unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        جاؤ release;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_PTR;
    impl_قدر.ڈیٹا_2.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_قدر);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        جاؤ release;
    }

    ret = 0;

release:
    IDirect3D9Ex_Release(d3d9ex);
    IDirect3DDevice9Ex_Release(device_ex);

unlock:
    IDirect3DDeviceManager9_UnlockDevice(devmgr, device_handle, FALSE);
    IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
fail:
#اگر_ختم
    واپس ret;
}

ساکن صحیح qsv_va_update_config(خالی *ctx, mfxHDL handle, mfxConfig cfg)
{
#اگر CONFIG_VAAPI
#اگر VA_CHECK_نسخہ(1, 15, 0)
    mfx_حالت sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_قدر = {0};

    vas = va_Get_Display_اوصاف(dpy, &attr, 1);
    اگر (vas == VA_حالت_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_قدر.Type = MFX_VARIANT_TYPE_U16;
        impl_قدر.ڈیٹا_2.U16 = (attr.قدر & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ثابت mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_قدر);
        اگر (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            جاؤ fail;
        }
    } ورنہ {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        جاؤ fail;
    }

    واپس 0;

fail:
#ورنہ
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#اگر_ختم
#اگر_ختم
    واپس AVERROR_UNKNOWN;
}

ساکن صحیح qsv_new_mfx_loader(خالی *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfx_نسخہ *pver,
                              خالی **ploader)
{
    mfx_حالت sts;
    mfxLoader loader = تہی;
    mfxConfig cfg;
    mfxVariant impl_قدر = {0};

    *ploader = تہی;
    loader = MFXLoad();
    اگر (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        جاؤ fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    اگر (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        جاؤ fail;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_U32;
    impl_قدر.ڈیٹا_2.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.Impl", impl_قدر);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        جاؤ fail;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_U32;
    impl_قدر.ڈیٹا_2.U32 = pver->نسخہ_2;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_قدر);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        جاؤ fail;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_U32;
    impl_قدر.ڈیٹا_2.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.VendorID", impl_قدر);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        جاؤ fail;
    }

    اگر (MFX_HANDLE_VA_DISPLAY == handle_type) {
        اگر (handle && qsv_va_update_config(ctx, handle, cfg))
            جاؤ fail;

        impl_قدر.ڈیٹا_2.U32 = MFX_ACCEL_منوال_بذریعہ_VAAPI;
    } ورنہ اگر (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        اگر (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            جاؤ fail;

        impl_قدر.ڈیٹا_2.U32 = MFX_ACCEL_منوال_بذریعہ_D3_D9;
    } ورنہ {
        اگر (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            جاؤ fail;

        impl_قدر.ڈیٹا_2.U32 = MFX_ACCEL_منوال_بذریعہ_D3_D11;
    }

    impl_قدر.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ثابت mfxU8 *)"mfxImplDescription.AccelerationMode", impl_قدر);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        جاؤ fail;
    }

    *ploader = loader;

    واپس 0;

fail:
    اگر (loader)
        MFXUnload(loader);

    واپس AVERROR_UNKNOWN;
}

ساکن صحیح qsv_create_mfx_session_from_loader(خالی *ctx, mfxLoader loader, mfxSession *psession)
{
    mfx_حالت sts;
    mfxSession session = تہی;
    uint32_t impl_idx = 0;
    mfx_نسخہ ver;

    جب (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        اگر (sts == MFX_ERR_NOT_ملا)
            توڑو;
        ورنہ اگر (sts != MFX_ERR_NONE) {
            impl_idx++;
            جاری;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        اگر (sts == MFX_ERR_NONE)
            توڑو;

        impl_idx++;
    }

    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        جاؤ fail;
    }

    sts = MFXQuery_نسخہ(session, &ver);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        جاؤ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    واپس 0;

fail:
    اگر (session)
        MFXClose(session);

    واپس AVERROR_UNKNOWN;
}

ساکن صحیح qsv_create_mfx_session(خالی *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfx_نسخہ *pver,
                                  mfxSession *psession,
                                  خالی **ploader)
{
    mfxLoader loader = تہی;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_نسخہ_MAJOR, MFX_نسخہ_MINOR, pver->Major, pver->Minor);

    اگر (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        واپس AVERROR(EXDEV);
    }

    *psession = تہی;

    اگر (!*ploader) {
        اگر (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (خالی **)&loader))
            جاؤ fail;

        av_assert0(loader);
    } ورنہ
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    اگر (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        جاؤ fail;

    اگر (!*ploader)
        *ploader = loader;

    واپس 0;

fail:
    اگر (!*ploader && loader)
        MFXUnload(loader);

    واپس AVERROR_UNKNOWN;
}

#ورنہ

ساکن صحیح qsv_create_mfx_session(خالی *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfx_نسخہ *pver,
                                  mfxSession *psession,
                                  خالی **ploader)
{
    mfx_نسخہ ver;
    mfx_حالت sts;
    mfxSession session = تہی;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_نسخہ_MAJOR, MFX_نسخہ_MINOR, pver->Major, pver->Minor);

    *ploader = تہی;
    *psession = تہی;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        جاؤ fail;
    }

    sts = MFXQuery_نسخہ(session, &ver);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        جاؤ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    اگر (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        جاؤ fail;
    }

    *psession = session;

    واپس 0;

fail:
    اگر (session)
        MFXClose(session);

    واپس AVERROR_UNKNOWN;
}

#اگر_ختم

ساکن صحیح qsv_init_اندرونی_session(AVHWFramesContext *ctx,
                                     mfxSession *session, صحیح upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *چوکھٹے_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    صحیح opaque = 0;

    mfx_چوکھٹا_Allocator چوکھٹا_allocator = {
        .pthis  = ctx,
        .Alloc  = چوکھٹا_alloc,
        .تالا_3   = چوکھٹا_تالا,
        .Unlock = چوکھٹا_unlock,
        .GetHDL = چوکھٹا_get_hdl,
        .Free   = چوکھٹا_free,
    };

    mfxVideoParam par;
    mfx_حالت err;
    صحیح                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    خالی             **loader = &hwctx->loader;
    mfxSession والد_session = hwctx->session;
    mfxIMPL impl;
    mfx_نسخہ ver;

    err = MFXQueryIMPL(والد_session, &impl);
    اگر (err == MFX_ERR_NONE)
        err = MFXQuery_نسخہ(والد_session, &ver);
    اگر (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        واپس AVERROR_UNKNOWN;
    }

#اگر QSV_HAVE_OPAQUE
    opaque = !!(چوکھٹے_hwctx->چوکھٹا_type & MFX_MEMTYPE_OPAQUE_چوکھٹا);
#اگر_ختم

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    اگر (ret)
        جاؤ fail;

    اگر (device_priv->handle) {
        err = MFXVideo_CORE_سیٹ_Handle(*session, device_priv->handle_type,
                                     device_priv->handle);
        اگر (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            جاؤ fail;
        }
    }

    اگر (QSV_RUNTIME_نسخہ_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(والد_session, *session);
        اگر (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            جاؤ fail;
        }
    }

    اگر (!opaque) {
        err = MFXVideo_CORE_سیٹ_چوکھٹا_Allocator(*session, &چوکھٹا_allocator);
        اگر (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            جاؤ fail;
        }
    }

    memset(&par, 0, حجم(par));

    اگر (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_برآمد_VIDEO_حافظہ :
                                 MFX_IOPATTERN_اندر_VIDEO_حافظہ;
    }
#اگر QSV_HAVE_OPAQUE
    ورنہ {
        par.ExtParam    = s->ext_buffers;
        par.عدد_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
        par.IOPattern   = upload ? MFX_IOPATTERN_برآمد_OPAQUE_حافظہ :
                                   MFX_IOPATTERN_اندر_OPAQUE_حافظہ;
    }
#اگر_ختم

    par.IOPattern |= upload ? MFX_IOPATTERN_اندر_SYSTEM_حافظہ :
                              MFX_IOPATTERN_برآمد_SYSTEM_حافظہ;
    par.Async_گہرائی = 1;

    par.vpp.اندر_2 = چوکھٹے_hwctx->nb_surfaces ? چوکھٹے_hwctx->surfaces[0].Info : *چوکھٹے_hwctx->info;

    /* Apparently VPP requires the frame rate to be set to some value, otherwise
     * init will fail (probably for the framerate conversion filter). Since we
     * are only doing data upload/download here, we just invent an arbitrary
     * value */
    par.vpp.اندر_2.چوکھٹا_شرح_Ext_N = 25;
    par.vpp.اندر_2.چوکھٹا_شرح_Ext_D = 1;
    par.vpp.برآمد_2 = par.vpp.اندر_2;

    err = MFXVideoVPP_Init(*session, &par);
    اگر (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        جاؤ fail;
    }

    واپس 0;

fail:
    اگر (*session)
        MFXClose(*session);

    *session = تہی;

    واپس ret;
}

ساکن صحیح qsv_چوکھٹے_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *چوکھٹے_hwctx = &s->p;

    صحیح opaque = 0;

    uint32_t fourcc;
    صحیح i, ret;

#اگر QSV_HAVE_OPAQUE
    opaque = !!(چوکھٹے_hwctx->چوکھٹا_type & MFX_MEMTYPE_OPAQUE_چوکھٹا);
#اگر_ختم

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    اگر (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        واپس AVERROR(ENOSYS);
    }

    اگر (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        اگر (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            واپس ret;
        }
    }

    اگر (!opaque) {
        s->mem_ids = av_calloc(چوکھٹے_hwctx->nb_surfaces, حجم(*s->mem_ids));
        اگر (!s->mem_ids)
            واپس AVERROR(ENOMEM);

        برائے (i = 0; i < چوکھٹے_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = چوکھٹے_hwctx->surfaces[i].ڈیٹا_2.MemId;
    }
#اگر QSV_HAVE_OPAQUE
    ورنہ {
        s->surface_ptrs = av_calloc(چوکھٹے_hwctx->nb_surfaces,
                                    حجم(*s->surface_ptrs));
        اگر (!s->surface_ptrs)
            واپس AVERROR(ENOMEM);

        برائے (i = 0; i < چوکھٹے_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = چوکھٹے_hwctx->surfaces + i;

        s->opaque_alloc.اندر_2.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.اندر_2.عدد_Surface = چوکھٹے_hwctx->nb_surfaces;
        s->opaque_alloc.اندر_2.Type       = چوکھٹے_hwctx->چوکھٹا_type;

        s->opaque_alloc.برآمد_2 = s->opaque_alloc.اندر_2;

        s->opaque_alloc.سرخی_2.بفر_Id = MFX_EXTBUFF_OPAQUE_SURFACE_تخصیص;
        s->opaque_alloc.سرخی_2.بفر_Sz = حجم(s->opaque_alloc);

        s->ext_buffers[0] = (mfx_Ext_بفر*)&s->opaque_alloc;
    }
#اگر_ختم

    s->session_download = تہی;
    s->session_upload   = تہی;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#اگر HAVE_PTHREADS
    pthread_mutex_init(&s->session_تالا, تہی);
#اگر_ختم

    واپس 0;
}

ساکن صحیح qsv_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکھٹا)
{
    چوکھٹا->buf[0] = av_بفر_pool_get(ctx->pool);
    اگر (!چوکھٹا->buf[0])
        واپس AVERROR(ENOMEM);

    چوکھٹا->ڈیٹا[3] = چوکھٹا->buf[0]->ڈیٹا;
    چوکھٹا->format  = AV_PIX_FMT_QSV;
    چوکھٹا->چوڑائی   = ctx->چوڑائی;
    چوکھٹا->اونچائی  = ctx->اونچائی;

    واپس 0;
}

ساکن صحیح qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    شمار AVHWFrameTransferDirection dir,
                                    شمار AVPixelFormat **formats)
{
    شمار AVPixelFormat *fmts;

    fmts = av_malloc_array(2, حجم(*fmts));
    اگر (!fmts)
        واپس AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    واپس 0;
}

ساکن صحیح qsv_چوکھٹے_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, صحیح flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    صحیح i;

    انتخاب (dst_ctx->device_ctx->type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               حجم(*dst_hwctx->surface_ids));
            اگر (!dst_hwctx->surface_ids)
                واپس AVERROR(ENOMEM);
            برائے (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].ڈیٹا_2.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->پہلا;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        توڑو;
#اگر_ختم
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_سائز = src_ctx->initial_pool_سائز;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 حجم(*dst_hwctx->texture_infos));
            اگر (!dst_hwctx->texture_infos)
                واپس AVERROR(ENOMEM);
            اگر (src_hwctx->چوکھٹا_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            برائے (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].ڈیٹا_2.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->پہلا;
                dst_hwctx->texture_infos[i].اشاریہ = pair->دوسرا == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->دوسرا;
            }
            اگر (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } ورنہ
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->چوکھٹا_type);
        }
        توڑو;
#اگر_ختم
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_چوکھٹے_Context *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            حجم(*dst_hwctx->surfaces));
            اگر (!dst_hwctx->surfaces)
                واپس AVERROR(ENOMEM);
            برائے (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].ڈیٹا_2.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->پہلا;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            اگر (src_hwctx->چوکھٹا_type == MFX_MEMTYPE_VIDEO_حافظہ_DECODER_ہدف)
                dst_hwctx->surface_type = DXVA2_Video_Decoder_Render_ہدف;
            ورنہ
                dst_hwctx->surface_type = DXVA2_Video_Processor_Render_ہدف;
        }
        توڑو;
#اگر_ختم
    طےشدہ:
        واپس AVERROR(ENOSYS);
    }

    واپس 0;
}

ساکن صحیح qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfx_چوکھٹا_Surface1 *surf = (mfx_چوکھٹا_Surface1*)src->ڈیٹا[3];
    AVHWFramesContext *بچہ_چوکھٹے_ctx;
    ثابت AVPixFmtDescriptor *desc;
    uint8_t *بچہ_ڈیٹا;
    AVFrame *dummy;
    صحیح ret = 0;

    اگر (!s->بچہ_چوکھٹے_ref)
        واپس AVERROR(ENOSYS);
    بچہ_چوکھٹے_ctx = (AVHWFramesContext*)s->بچہ_چوکھٹے_ref->ڈیٹا;

    انتخاب (بچہ_چوکھٹے_ctx->device_ctx->type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->ڈیٹا_2.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        بچہ_ڈیٹا = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->پہلا;
        توڑو;
    }
#اگر_ختم
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->ڈیٹا_2.MemId;
        بچہ_ڈیٹا = pair->پہلا;
        توڑو;
    }
#اگر_ختم
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->ڈیٹا_2.MemId;
        بچہ_ڈیٹا = pair->پہلا;
        توڑو;
    }
#اگر_ختم
    طےشدہ:
        واپس AVERROR(ENOSYS);
    }

    اگر (dst->format == بچہ_چوکھٹے_ctx->format) {
        ret = ff_hwframe_map_create(s->بچہ_چوکھٹے_ref,
                                    dst, src, تہی, تہی);
        اگر (ret < 0)
            واپس ret;

        dst->چوڑائی   = src->چوڑائی;
        dst->اونچائی  = src->اونچائی;

       اگر (بچہ_چوکھٹے_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->ڈیٹا_2.MemId;
            dst->ڈیٹا[0] = pair->پہلا;
            dst->ڈیٹا[1] = pair->دوسرا == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->دوسرا;
        } ورنہ {
            dst->ڈیٹا[3] = بچہ_ڈیٹا;
        }

        واپس 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    اگر (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        واپس AVERROR(ENOSYS);
    }

    dummy = av_چوکھٹا_alloc();
    اگر (!dummy)
        واپس AVERROR(ENOMEM);

    dummy->buf[0]        = av_بفر_ref(src->buf[0]);
    dummy->hw_چوکھٹے_ctx = av_بفر_ref(s->بچہ_چوکھٹے_ref);
    اگر (!dummy->buf[0] || !dummy->hw_چوکھٹے_ctx)
        جاؤ fail;

    dummy->format        = بچہ_چوکھٹے_ctx->format;
    dummy->چوڑائی         = src->چوڑائی;
    dummy->اونچائی        = src->اونچائی;

    اگر (بچہ_چوکھٹے_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->ڈیٹا_2.MemId;
        dummy->ڈیٹا[0] = pair->پہلا;
        dummy->ڈیٹا[1] = pair->دوسرا == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->دوسرا;
    } ورنہ {
        dummy->ڈیٹا[3] = بچہ_ڈیٹا;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_چوکھٹا_free(&dummy);

    واپس ret;
}

ساکن صحیح qsv_transfer_ڈیٹا_بچہ(AVHWFramesContext *ctx, AVFrame *dst,
                                   ثابت AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *بچہ_چوکھٹے_ctx = (AVHWFramesContext*)s->بچہ_چوکھٹے_ref->ڈیٹا;
    صحیح download = !!src->hw_چوکھٹے_ctx;
    mfx_چوکھٹا_Surface1 *surf = (mfx_چوکھٹا_Surface1*)(download ? src->ڈیٹا[3] : dst->ڈیٹا[3]);

    AVFrame *dummy;
    صحیح ret;

    dummy = av_چوکھٹا_alloc();
    اگر (!dummy)
        واپس AVERROR(ENOMEM);

    dummy->format        = بچہ_چوکھٹے_ctx->format;
    dummy->چوڑائی         = src->چوڑائی;
    dummy->اونچائی        = src->اونچائی;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->ڈیٹا[3]       = surf->ڈیٹا_2.MemId;
    dummy->hw_چوکھٹے_ctx = s->بچہ_چوکھٹے_ref;

    ret = download ? av_hwframe_transfer_ڈیٹا(dst, dummy, 0) :
                     av_hwframe_transfer_ڈیٹا(dummy, src, 0);

    dummy->buf[0]        = تہی;
    dummy->ڈیٹا[3]       = تہی;
    dummy->hw_چوکھٹے_ctx = تہی;

    av_چوکھٹا_free(&dummy);

    واپس ret;
}

ساکن صحیح map_چوکھٹا_مقصد_surface(ثابت AVFrame *چوکھٹا, mfx_چوکھٹا_Surface1 *surface)
{
    انتخاب (چوکھٹا->format) {
    حالت AV_PIX_FMT_NV12:
    حالت AV_PIX_FMT_P010:
    حالت AV_PIX_FMT_P012:
        surface->ڈیٹا_2.Y  = چوکھٹا->ڈیٹا[0];
        surface->ڈیٹا_2.UV = چوکھٹا->ڈیٹا[1];
        توڑو;

    حالت AV_PIX_FMT_YUV420P:
        surface->ڈیٹا_2.Y = چوکھٹا->ڈیٹا[0];
        surface->ڈیٹا_2.U = چوکھٹا->ڈیٹا[1];
        surface->ڈیٹا_2.V = چوکھٹا->ڈیٹا[2];
        توڑو;

    حالت AV_PIX_FMT_BGRA:
        surface->ڈیٹا_2.B = چوکھٹا->ڈیٹا[0];
        surface->ڈیٹا_2.G = چوکھٹا->ڈیٹا[0] + 1;
        surface->ڈیٹا_2.R = چوکھٹا->ڈیٹا[0] + 2;
        surface->ڈیٹا_2.A = چوکھٹا->ڈیٹا[0] + 3;
        توڑو;
    حالت AV_PIX_FMT_YUYV422:
        surface->ڈیٹا_2.Y = چوکھٹا->ڈیٹا[0];
        surface->ڈیٹا_2.U = چوکھٹا->ڈیٹا[0] + 1;
        surface->ڈیٹا_2.V = چوکھٹا->ڈیٹا[0] + 3;
        توڑو;

    حالت AV_PIX_FMT_Y210:
    حالت AV_PIX_FMT_Y212:
        surface->ڈیٹا_2.Y16 = (mfxU16 *)چوکھٹا->ڈیٹا[0];
        surface->ڈیٹا_2.U16 = (mfxU16 *)چوکھٹا->ڈیٹا[0] + 1;
        surface->ڈیٹا_2.V16 = (mfxU16 *)چوکھٹا->ڈیٹا[0] + 3;
        توڑو;
    حالت AV_PIX_FMT_VUYX:
        surface->ڈیٹا_2.V = چوکھٹا->ڈیٹا[0];
        surface->ڈیٹا_2.U = چوکھٹا->ڈیٹا[0] + 1;
        surface->ڈیٹا_2.Y = چوکھٹا->ڈیٹا[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->ڈیٹا_2.A = چوکھٹا->ڈیٹا[0] + 3;
        توڑو;
    حالت AV_PIX_FMT_XV30:
        surface->ڈیٹا_2.U = چوکھٹا->ڈیٹا[0];
        توڑو;
    حالت AV_PIX_FMT_XV36:
        surface->ڈیٹا_2.U = چوکھٹا->ڈیٹا[0];
        surface->ڈیٹا_2.Y = چوکھٹا->ڈیٹا[0] + 2;
        surface->ڈیٹا_2.V = چوکھٹا->ڈیٹا[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->ڈیٹا_2.A = چوکھٹا->ڈیٹا[0] + 6;
        توڑو;
#اگر CONFIG_VAAPI
    حالت AV_PIX_FMT_UYVY422:
        surface->ڈیٹا_2.Y = چوکھٹا->ڈیٹا[0] + 1;
        surface->ڈیٹا_2.U = چوکھٹا->ڈیٹا[0];
        surface->ڈیٹا_2.V = چوکھٹا->ڈیٹا[0] + 2;
        توڑو;
#اگر_ختم
    طےشدہ:
        واپس MFX_ERR_UNSUPPORTED;
    }
    surface->ڈیٹا_2.Pitch     = چوکھٹا->linesize[0];
    surface->ڈیٹا_2.وقت_Stamp = چوکھٹا->pts;

    واپس 0;
}

ساکن صحیح qsv_اندرونی_session_check_init(AVHWFramesContext *ctx, صحیح upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    صحیح ret = 0;

    اگر (atomic_load(inited))
        واپس 0;

#اگر HAVE_PTHREADS
    pthread_mutex_تالا(&s->session_تالا);
#اگر_ختم

    اگر (!atomic_load(inited)) {
        ret = qsv_init_اندرونی_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#اگر HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_تالا);
#اگر_ختم

    واپس ret;
}

ساکن صحیح qsv_transfer_ڈیٹا_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ثابت AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfx_چوکھٹا_Surface1 برآمد = {{ 0 }};
    mfx_چوکھٹا_Surface1 *اندر = (mfx_چوکھٹا_Surface1*)src->ڈیٹا[3];

    mfx_Sync_نقطہ sync = تہی;
    mfx_حالت err;
    صحیح ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_چوکھٹا = &s->realigned_download_چوکھٹا;
    AVFrame *dst_چوکھٹا;
    صحیح realigned = 0;

    ret = qsv_اندرونی_session_check_init(ctx, 0);
    اگر (ret < 0)
        واپس ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    اگر (dst->اونچائی & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        اگر (tmp_چوکھٹا->format != dst->format ||
            tmp_چوکھٹا->چوڑائی  != FFALIGN(dst->linesize[0], 16) ||
            tmp_چوکھٹا->اونچائی != FFALIGN(dst->اونچائی, 16)) {
            av_چوکھٹا_unref(tmp_چوکھٹا);

            tmp_چوکھٹا->format = dst->format;
            tmp_چوکھٹا->چوڑائی  = FFALIGN(dst->linesize[0], 16);
            tmp_چوکھٹا->اونچائی = FFALIGN(dst->اونچائی, 16);
            ret = av_چوکھٹا_get_بفر(tmp_چوکھٹا, 0);
            اگر (ret < 0)
                واپس ret;
        }
    }

    dst_چوکھٹا = realigned ? tmp_چوکھٹا : dst;

    اگر (!s->session_download) {
        اگر (s->بچہ_چوکھٹے_ref)
            واپس qsv_transfer_ڈیٹا_بچہ(ctx, dst_چوکھٹا, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        واپس AVERROR(ENOSYS);
    }

    برآمد.Info = اندر->Info;
    map_چوکھٹا_مقصد_surface(dst_چوکھٹا, &برآمد);

    کرو {
        err = MFXVideo_VPP_تسلسل_چوکھٹا_VPPAsync(s->session_download, اندر, &برآمد, تہی, &sync);
        اگر (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } جب (err == MFX_WRN_DEVICE_BUSY);

    اگر (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        واپس AVERROR_UNKNOWN;
    }

    کرو {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } جب (err == MFX_WRN_اندر_EXECUTION);
    اگر (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        واپس AVERROR_UNKNOWN;
    }

    اگر (realigned) {
        tmp_چوکھٹا->چوڑائی  = dst->چوڑائی;
        tmp_چوکھٹا->اونچائی = dst->اونچائی;
        ret = av_چوکھٹا_copy(dst, tmp_چوکھٹا);
        tmp_چوکھٹا->چوڑائی  = FFALIGN(dst->linesize[0], 16);
        tmp_چوکھٹا->اونچائی = FFALIGN(dst->اونچائی, 16);
        اگر (ret < 0)
            واپس ret;
    }

    واپس 0;
}

ساکن صحیح qsv_transfer_ڈیٹا_مقصد(AVHWFramesContext *ctx, AVFrame *dst,
                                ثابت AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfx_چوکھٹا_Surface1   اندر = {{ 0 }};
    mfx_چوکھٹا_Surface1 *برآمد = (mfx_چوکھٹا_Surface1*)dst->ڈیٹا[3];
    mfx_چوکھٹا_Info tmp_info;

    mfx_Sync_نقطہ sync = تہی;
    mfx_حالت err;
    صحیح ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_چوکھٹا = &s->realigned_upload_چوکھٹا;
    ثابت AVFrame *src_چوکھٹا;
    صحیح realigned = 0;

    ret = qsv_اندرونی_session_check_init(ctx, 1);
    اگر (ret < 0)
        واپس ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    اگر (src->اونچائی & 15 || src->linesize[0] & 15) {
        realigned = 1;
        اگر (tmp_چوکھٹا->format != src->format ||
            tmp_چوکھٹا->چوڑائی  != FFALIGN(src->چوڑائی, 16) ||
            tmp_چوکھٹا->اونچائی != FFALIGN(src->اونچائی, 16)) {
            av_چوکھٹا_unref(tmp_چوکھٹا);

            tmp_چوکھٹا->format = src->format;
            tmp_چوکھٹا->چوڑائی  = FFALIGN(src->چوڑائی, 16);
            tmp_چوکھٹا->اونچائی = FFALIGN(src->اونچائی, 16);
            ret = av_چوکھٹا_get_بفر(tmp_چوکھٹا, 0);
            اگر (ret < 0)
                واپس ret;
        }
        ret = av_چوکھٹا_copy(tmp_چوکھٹا, src);
        اگر (ret < 0) {
            av_چوکھٹا_unref(tmp_چوکھٹا);
            واپس ret;
        }
        ret = qsv_fill_border(tmp_چوکھٹا, src);
        اگر (ret < 0) {
            av_چوکھٹا_unref(tmp_چوکھٹا);
            واپس ret;
        }

        tmp_info = برآمد->Info;
        برآمد->Info.CropW = FFMIN(برآمد->Info.چوڑائی_2,  tmp_چوکھٹا->چوڑائی);
        برآمد->Info.CropH = FFMIN(برآمد->Info.اونچائی_2, tmp_چوکھٹا->اونچائی);
    }

    src_چوکھٹا = realigned ? tmp_چوکھٹا : src;

    اگر (!s->session_upload) {
        اگر (s->بچہ_چوکھٹے_ref)
            واپس qsv_transfer_ڈیٹا_بچہ(ctx, dst, src_چوکھٹا);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        واپس AVERROR(ENOSYS);
    }

    اندر.Info = برآمد->Info;
    map_چوکھٹا_مقصد_surface(src_چوکھٹا, &اندر);

    کرو {
        err = MFXVideo_VPP_تسلسل_چوکھٹا_VPPAsync(s->session_upload, &اندر, برآمد, تہی, &sync);
        اگر (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } جب (err == MFX_WRN_DEVICE_BUSY);

    اگر (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        واپس AVERROR_UNKNOWN;
    }

    کرو {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } جب (err == MFX_WRN_اندر_EXECUTION);
    اگر (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        واپس AVERROR_UNKNOWN;
    }

    اگر (realigned) {
        برآمد->Info.CropW = tmp_info.CropW;
        برآمد->Info.CropH = tmp_info.CropH;
    }

    واپس 0;
}

ساکن صحیح qsv_dynamic_چوکھٹے_derive_مقصد(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, صحیح flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfx_چوکھٹا_Surface1 mfx_surf1;

    انتخاب (src_ctx->device_ctx->type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->چوکھٹا_type  = MFX_MEMTYPE_VIDEO_حافظہ_DECODER_ہدف;
        توڑو;
#اگر_ختم

#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        اگر (src_hwctx->BindFlags & D3_D11_BIND_RENDER_ہدف) {
            dst_hwctx->چوکھٹا_type |= MFX_MEMTYPE_VIDEO_حافظہ_PROCESSOR_ہدف;
        } ورنہ {
            dst_hwctx->چوکھٹا_type |= MFX_MEMTYPE_VIDEO_حافظہ_DECODER_ہدف;
        }
    }
    توڑو;
#اگر_ختم

    طےشدہ:
        واپس AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, حجم(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->چوکھٹا_info = mfx_surf1.Info;
    dst_hwctx->info = &s->چوکھٹا_info;
    dst_hwctx->nb_surfaces = 0;
    واپس 0;
}

ساکن صحیح qsv_fixed_چوکھٹے_derive_مقصد(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, صحیح flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    صحیح i;

    انتخاب (src_ctx->device_ctx->type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_جوڑے_اندرونی = av_calloc(src_ctx->initial_pool_سائز,
                                                 حجم(*s->handle_جوڑے_اندرونی));
            اگر (!s->handle_جوڑے_اندرونی)
                واپس AVERROR(ENOMEM);
            s->surfaces_اندرونی = av_calloc(src_hwctx->nb_surfaces,
                                             حجم(*s->surfaces_اندرونی));
            اگر (!s->surfaces_اندرونی)
                واپس AVERROR(ENOMEM);
            برائے (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_اندرونی[i]);
                s->handle_جوڑے_اندرونی[i].پہلا = src_hwctx->surface_ids + i;
                s->handle_جوڑے_اندرونی[i].دوسرا = (mfxMemId)MFX_INFINITE;
                s->surfaces_اندرونی[i].ڈیٹا_2.MemId = (mfxMemId)&s->handle_جوڑے_اندرونی[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->چوکھٹا_type  = MFX_MEMTYPE_VIDEO_حافظہ_DECODER_ہدف;
        }
        توڑو;
#اگر_ختم
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_جوڑے_اندرونی = av_calloc(src_ctx->initial_pool_سائز,
                                                 حجم(*s->handle_جوڑے_اندرونی));
            اگر (!s->handle_جوڑے_اندرونی)
                واپس AVERROR(ENOMEM);
            s->surfaces_اندرونی = av_calloc(src_ctx->initial_pool_سائز,
                                             حجم(*s->surfaces_اندرونی));
            اگر (!s->surfaces_اندرونی)
                واپس AVERROR(ENOMEM);
            برائے (i = 0; i < src_ctx->initial_pool_سائز; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_اندرونی[i]);
                s->handle_جوڑے_اندرونی[i].پہلا = (mfxMemId)src_hwctx->texture_infos[i].texture;
                اگر (src_hwctx->BindFlags & D3_D11_BIND_RENDER_ہدف) {
                    s->handle_جوڑے_اندرونی[i].دوسرا = (mfxMemId)MFX_INFINITE;
                } ورنہ {
                    s->handle_جوڑے_اندرونی[i].دوسرا = (mfxMemId)src_hwctx->texture_infos[i].اشاریہ;
                }
                s->surfaces_اندرونی[i].ڈیٹا_2.MemId = (mfxMemId)&s->handle_جوڑے_اندرونی[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_سائز;
            اگر (src_hwctx->BindFlags & D3_D11_BIND_RENDER_ہدف) {
                dst_hwctx->چوکھٹا_type |= MFX_MEMTYPE_VIDEO_حافظہ_PROCESSOR_ہدف;
            } ورنہ {
                dst_hwctx->چوکھٹا_type |= MFX_MEMTYPE_VIDEO_حافظہ_DECODER_ہدف;
            }
        }
        توڑو;
#اگر_ختم
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_چوکھٹے_Context *src_hwctx = src_ctx->hwctx;
            s->handle_جوڑے_اندرونی = av_calloc(src_ctx->initial_pool_سائز,
                                                 حجم(*s->handle_جوڑے_اندرونی));
            اگر (!s->handle_جوڑے_اندرونی)
                واپس AVERROR(ENOMEM);
            s->surfaces_اندرونی = av_calloc(src_hwctx->nb_surfaces,
                                             حجم(*s->surfaces_اندرونی));
            اگر (!s->surfaces_اندرونی)
                واپس AVERROR(ENOMEM);
            برائے (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_اندرونی[i]);
                s->handle_جوڑے_اندرونی[i].پہلا = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_جوڑے_اندرونی[i].دوسرا = (mfxMemId)MFX_INFINITE;
                s->surfaces_اندرونی[i].ڈیٹا_2.MemId = (mfxMemId)&s->handle_جوڑے_اندرونی[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            اگر (src_hwctx->surface_type == DXVA2_Video_Processor_Render_ہدف)
                dst_hwctx->چوکھٹا_type = MFX_MEMTYPE_VIDEO_حافظہ_PROCESSOR_ہدف;
            ورنہ
                dst_hwctx->چوکھٹا_type = MFX_MEMTYPE_VIDEO_حافظہ_DECODER_ہدف;
        }
        توڑو;
#اگر_ختم
    طےشدہ:
        واپس AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_اندرونی;

    واپس 0;
}

ساکن صحیح qsv_چوکھٹے_derive_مقصد(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, صحیح flags)
{
    اگر (src_ctx->initial_pool_سائز < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        واپس AVERROR(EINVAL);
    } ورنہ اگر (src_ctx->initial_pool_سائز == 0) {
        واپس qsv_dynamic_چوکھٹے_derive_مقصد(dst_ctx, src_ctx, flags);
    } ورنہ {
        واپس qsv_fixed_چوکھٹے_derive_مقصد(dst_ctx, src_ctx, flags);
    }
}

ساکن صحیح qsv_fixed_pool_map_مقصد(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    صحیح i, err, اشاریہ = -1;

    برائے (i = 0; i < hwctx->nb_surfaces && اشاریہ < 0; i++) {
        انتخاب(src->format) {
#اگر CONFIG_VAAPI
        حالت AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].ڈیٹا_2.MemId;
            اگر (*(VASurfaceID*)pair->پہلا == (VASurfaceID)(uintptr_t)src->ڈیٹا[3])
                اشاریہ = i;
            توڑو;
        }
#اگر_ختم
#اگر CONFIG_D3D11VA
        حالت AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].ڈیٹا_2.MemId;
            اگر (pair->پہلا == src->ڈیٹا[0]
                && (pair->دوسرا == src->ڈیٹا[1]
                    || (pair->دوسرا == (mfxMemId)MFX_INFINITE && src->ڈیٹا[1] == (uint8_t *)0)))
                اشاریہ = i;
            توڑو;
        }
#اگر_ختم
#اگر CONFIG_DXVA2
        حالت AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].ڈیٹا_2.MemId;
            اگر (pair->پہلا == src->ڈیٹا[3])
                اشاریہ = i;
            توڑو;
        }
#اگر_ختم
        }
    }
    اگر (اشاریہ < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        واپس AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx,
                                dst, src, تہی, تہی);
    اگر (err)
        واپس err;

    dst->چوڑائی   = src->چوڑائی;
    dst->اونچائی  = src->اونچائی;
    dst->ڈیٹا[3] = (uint8_t*)&hwctx->surfaces[اشاریہ];

    واپس 0;
}

ساکن خالی qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfx_چوکھٹا_Surface1 *surfaces_اندرونی = (mfx_چوکھٹا_Surface1 *)hwmap->priv;
    mfxHDLPair *handle_جوڑے_اندرونی = (mfxHDLPair *)surfaces_اندرونی->ڈیٹا_2.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->ماخذ_چوکھٹے->ڈیٹا;

    انتخاب (src_ctx->format) {
#اگر CONFIG_VAAPI
    حالت AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_جوڑے_اندرونی->پہلا);

        توڑو;
    }
#اگر_ختم

#اگر CONFIG_D3D11VA
    حالت AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        توڑو;
    }
#اگر_ختم
    طےشدہ:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        توڑو;
    }

    av_freep(&handle_جوڑے_اندرونی);
    av_freep(&surfaces_اندرونی);
}

ساکن صحیح qsv_dynamic_pool_map_مقصد(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    mfx_چوکھٹا_Surface1 *surfaces_اندرونی = تہی;
    mfxHDLPair *handle_جوڑے_اندرونی = تہی;
    صحیح ret = 0;

    surfaces_اندرونی = av_calloc(1, حجم(*surfaces_اندرونی));
    اگر (!surfaces_اندرونی) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }

    handle_جوڑے_اندرونی = av_calloc(1, حجم(*handle_جوڑے_اندرونی));
    اگر (!handle_جوڑے_اندرونی) {
        ret = AVERROR(ENOMEM);
        جاؤ fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_اندرونی);
    اگر (ret < 0)
        جاؤ fail;

    انتخاب (src->format) {
#اگر CONFIG_VAAPI
    حالت AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_اندرونی;

        surface_id_اندرونی = av_calloc(1, حجم(*surface_id_اندرونی));
        اگر (!surface_id_اندرونی) {
            ret =AVERROR(ENOMEM);
            جاؤ fail;
        }

        *surface_id_اندرونی = (VASurfaceID)(uintptr_t)src->ڈیٹا[3];
        handle_جوڑے_اندرونی->پہلا = (mfxHDL)surface_id_اندرونی;
        handle_جوڑے_اندرونی->دوسرا = (mfxMemId)MFX_INFINITE;

        توڑو;
    }
#اگر_ختم

#اگر CONFIG_D3D11VA
    حالت AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_چوکھٹے_ctx->ڈیٹا;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_جوڑے_اندرونی->پہلا = (mfxMemId)src->ڈیٹا[0];

        اگر (src_hwctx->BindFlags & D3_D11_BIND_RENDER_ہدف) {
            handle_جوڑے_اندرونی->دوسرا = (mfxMemId)MFX_INFINITE;
        } ورنہ {
            handle_جوڑے_اندرونی->دوسرا = (mfxMemId)src->ڈیٹا[1];
        }

        توڑو;
    }
#اگر_ختم
    طےشدہ:
        ret = AVERROR(ENOSYS);
        جاؤ fail;
    }

    surfaces_اندرونی->ڈیٹا_2.MemId = (mfxMemId)handle_جوڑے_اندرونی;

    ret = ff_hwframe_map_create(dst->hw_چوکھٹے_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_اندرونی);
    اگر (ret)
        جاؤ fail;

    dst->چوڑائی   = src->چوڑائی;
    dst->اونچائی  = src->اونچائی;
    dst->ڈیٹا[3] = (uint8_t*)surfaces_اندرونی;

    واپس 0;

fail:
    av_freep(&handle_جوڑے_اندرونی);
    av_freep(&surfaces_اندرونی);
    واپس ret;
}

ساکن صحیح qsv_map_مقصد(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    اگر (hwctx->nb_surfaces)
        واپس qsv_fixed_pool_map_مقصد(dst_ctx, dst, src, flags);
    ورنہ
        واپس qsv_dynamic_pool_map_مقصد(dst_ctx, dst, src, flags);
}

ساکن صحیح qsv_چوکھٹے_get_constraints(AVHWDeviceContext *ctx,
                                      ثابت خالی *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    صحیح i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    حجم(*constraints->valid_sw_formats));
    اگر (!constraints->valid_sw_formats)
        واپس AVERROR(ENOMEM);

    برائے (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, حجم(*constraints->valid_hw_formats));
    اگر (!constraints->valid_hw_formats)
        واپس AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    واپس 0;
}

ساکن خالی qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    اگر (hwctx->session)
        MFXClose(hwctx->session);

    اگر (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_بفر_unref(&priv->بچہ_device_ctx);
    av_freep(&priv);
}

ساکن mfxIMPL انتخاب_implementation(ثابت حرف *device, شمار AVHWDeviceType بچہ_device_type)
{
    ساکن ثابت ساخت {
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
    صحیح i;

    اگر (device) {
        برائے (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            اگر (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                توڑو;
            }
        اگر (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, تہی, 0);
    }

    اگر (impl != MFX_IMPL_SOFTWARE) {
        اگر (بچہ_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_بذریعہ_D3_D11;
        ورنہ اگر (بچہ_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_بذریعہ_D3_D9;
    }

    واپس impl;
}

ساکن صحیح qsv_device_derive_from_بچہ(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *بچہ_device_ctx,
                                        صحیح flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfx_نسخہ    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfx_حالت     err;
    صحیح ret;

    انتخاب (بچہ_device_ctx->type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *بچہ_device_hwctx = بچہ_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)بچہ_device_hwctx->display;
        }
        توڑو;
#اگر_ختم
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *بچہ_device_hwctx = بچہ_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)بچہ_device_hwctx->device;
        }
        توڑو;
#اگر_ختم
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *بچہ_device_hwctx = بچہ_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)بچہ_device_hwctx->devmgr;
        }
        توڑو;
#اگر_ختم
    طےشدہ:
        ret = AVERROR(ENOSYS);
        جاؤ fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    اگر (ret)
        جاؤ fail;

    err = MFXVideo_CORE_سیٹ_Handle(hwctx->session, handle_type, handle);
    اگر (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        جاؤ fail;
    }

    واپس 0;

fail:
    اگر (hwctx->session)
        MFXClose(hwctx->session);

    اگر (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = تہی;
    hwctx->loader = تہی;
    واپس ret;
}

ساکن صحیح qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *بچہ_device_ctx,
                             AVDictionary *opts, صحیح flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(حجم(*priv));
    اگر (!priv)
        واپس AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->آزاد = qsv_device_free;

    impl = انتخاب_implementation("hw_any", بچہ_device_ctx->type);
    واپس qsv_device_derive_from_بچہ(ctx, impl,
                                        بچہ_device_ctx, flags);
}

ساکن صحیح qsv_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                             AVDictionary *opts, صحیح flags)
{
    QSVDevicePriv *priv;
    شمار AVHWDeviceType بچہ_device_type;
    AVHWDeviceContext *بچہ_device;
    AVDictionary *بچہ_device_opts;
    AVDictionary_اندراج *e;

    mfxIMPL impl;
    صحیح ret;

    priv = av_mallocz(حجم(*priv));
    اگر (!priv)
        واپس AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->آزاد        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", تہی, 0);
    اگر (e) {
        بچہ_device_type = av_hwdevice_ڈھونڈو_type_by_name(e->قدر);
        اگر (بچہ_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->قدر);
            واپس AVERROR(EINVAL);
        }
#اگر QSV_ONEVPL
    } ورنہ اگر (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        بچہ_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } ورنہ اگر (CONFIG_DXVA2) {
        بچہ_device_type = AV_HWDEVICE_TYPE_DXVA2;
#ورنہ
    } ورنہ اگر (CONFIG_DXVA2) {
        av_log(تہی, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        بچہ_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } ورنہ اگر (CONFIG_D3D11VA) {
        بچہ_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#اگر_ختم
    } ورنہ اگر (CONFIG_VAAPI) {
        بچہ_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } ورنہ {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        واپس AVERROR(ENOSYS);
    }

#اگر CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    اگر (بچہ_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->قدر);
        واپس AVERROR(EINVAL);
    }
#اگر_ختم

    بچہ_device_opts = تہی;
    انتخاب (بچہ_device_type) {
#اگر CONFIG_VAAPI
    حالت AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_سیٹ(&بچہ_device_opts, "vendor_id", "0x8086", 0);
            av_dict_سیٹ(&بچہ_device_opts, "driver",    "iHD",    0);
        }
        توڑو;
#اگر_ختم
#اگر CONFIG_D3D11VA
    حالت AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_سیٹ(&بچہ_device_opts, "vendor_id",        "0x8086",  0);
        }
        توڑو;
#اگر_ختم
#اگر CONFIG_DXVA2
    حالت AV_HWDEVICE_TYPE_DXVA2:
#اگر QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#اگر_ختم
        توڑو;
#اگر_ختم
    طےشدہ:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            واپس AVERROR(ENOSYS);
        }
        توڑو;
    }

    e = av_dict_get(opts, "child_device", تہی, 0);
    ret = av_hwdevice_ctx_create(&priv->بچہ_device_ctx, بچہ_device_type,
                                 e ? e->قدر : تہی, بچہ_device_opts, 0);

    av_dict_free(&بچہ_device_opts);
    اگر (ret < 0)
        واپس ret;

    بچہ_device = (AVHWDeviceContext*)priv->بچہ_device_ctx->ڈیٹا;

    impl = انتخاب_implementation(device, بچہ_device_type);

    واپس qsv_device_derive_from_بچہ(ctx, impl, بچہ_device, 0);
}

ثابت HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_سائز      = حجم(QSVDeviceContext),
    .چوکھٹے_hwctx_سائز      = حجم(QSVFramesContext),

    .device_create          = qsv_device_create,
    .device_derive          = qsv_device_derive,
    .device_init            = qsv_device_init,
    .چوکھٹے_get_constraints = qsv_چوکھٹے_get_constraints,
    .چوکھٹے_init            = qsv_چوکھٹے_init,
    .چوکھٹے_uninit          = qsv_چوکھٹے_uninit,
    .چوکھٹے_get_بفر      = qsv_get_بفر,
    .transfer_get_formats   = qsv_transfer_get_formats,
    .transfer_ڈیٹا_مقصد       = qsv_transfer_ڈیٹا_مقصد,
    .transfer_ڈیٹا_from     = qsv_transfer_ڈیٹا_from,
    .map_مقصد                 = qsv_map_مقصد,
    .map_from               = qsv_map_from,
    .چوکھٹے_derive_مقصد       = qsv_چوکھٹے_derive_مقصد,
    .چوکھٹے_derive_from     = qsv_چوکھٹے_derive_from,

    .pix_fmts = (ثابت شمار AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
