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

#అన్తర్భావ <stdatomic.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ <mfxvideo.h>

#అన్తర్భావ "config.h"

#ఒకవేళ HAVE_PTHREADS
#అన్తర్భావ <pthread.h>
#అయితే_ముగింపు

#నిర్వచించు COBJMACROS
#ఒకవేళ CONFIG_VAAPI
#అన్తర్భావ "hwcontext_vaapi.h"
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
#అన్తర్భావ "hwcontext_d3d11va.h"
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
#అన్తర్భావ <initguid.h>
#అన్తర్భావ "hwcontext_dxva2.h"
#అయితే_ముగింపు

#అన్తర్భావ "buffer.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "hwcontext_qsv.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pixfmt.h"
#అన్తర్భావ "pixdesc.h"
#అన్తర్భావ "time.h"
#అన్తర్భావ "imgutils.h"
#అన్తర్భావ "avassert.h"

#నిర్వచించు QSV_సంస్కరణ_ATLEAST(MAJOR, MINOR)   \
    (MFX_సంస్కరణ_MAJOR > (MAJOR) ||         \
     MFX_సంస్కరణ_MAJOR == (MAJOR) && MFX_సంస్కరణ_MINOR >= (MINOR))

#నిర్వచించు QSV_RUNTIME_సంస్కరణ_ATLEAST(MFX_సంస్కరణ, MAJOR, MINOR)          \
    ((MFX_సంస్కరణ.Major > (MAJOR)) ||                                   \
     (MFX_సంస్కరణ.Major == (MAJOR) && MFX_సంస్కరణ.Minor >= (MINOR)))

#నిర్వచించు MFX_IMPL_ద్వారా_ముసుగు(impl) (0x0f00 & (impl))
#నిర్వచించు QSV_ONEVPL       QSV_సంస్కరణ_ATLEAST(2, 0)
#నిర్వచించు QSV_HAVE_OPAQUE  !QSV_ONEVPL

#ఒకవేళ QSV_ONEVPL
#అన్తర్భావ <mfxdispatcher.h>
#లేకపోతే
#నిర్వచించు MFXUnload(a) చేయి { } అయితే(0)
#అయితే_ముగింపు

రకనిర్వచనం నిర్మాణం QSVDevicePriv {
    AVBufferRef *బిడ్డ_device_ctx;
} QSVDevicePriv;

రకనిర్వచనం నిర్మాణం QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfx_సంస్కరణ          ver;
    mfxIMPL             impl;

    గణన AVHWDeviceType బిడ్డ_device_type;
    గణన AVPixelFormat  బిడ్డ_pix_fmt;
} QSVDeviceContext;

రకనిర్వచనం నిర్మాణం QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#ఒకవేళ HAVE_PTHREADS
    pthread_mutex_t session_తాళం;
#అయితే_ముగింపు

    AVBufferRef *బిడ్డ_చట్రాలు_ref;
    mfx_చట్రం_Surface1 *surfaces_అంతర్గత;
    mfxHDLPair *handle_జతలు_అంతర్గత;
    పూర్ణాంకం             nb_surfaces_వాడిన;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#ఒకవేళ QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfx_చట్రం_Surface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfx_Ext_బఫరు *ext_buffers[1];
#అయితే_ముగింపు
    AVFrame realigned_upload_చట్రం;
    AVFrame realigned_download_చట్రం;

    mfx_చట్రం_Info చట్రం_info;
} QSVFramesContext;

రకనిర్వచనం నిర్మాణం QSVSurface {
    mfx_చట్రం_Surface1 mfx_surface;
    AVFrame *బిడ్డ_చట్రం;
} QSVSurface;

స్థిర స్థిరరాశి నిర్మాణం {
    గణన AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_జరుపు;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#ఒకవేళ CONFIG_VAAPI
    { AV_PIX_FMT_UYVY422,
                       MFX_FOURCC_UYVY, 0 },
#అయితే_ముగింపు
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
#ఒకవేళ QSV_సంస్కరణ_ATLEAST(1, 31)
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
#అయితే_ముగింపు
};

బాహ్య పూర్ణాంకం ff_qsv_get_surface_పునాది_handle(mfx_చట్రం_Surface1 *surf,
                                          గణన AVHWDeviceType పునాది_dev_type,
                                          శూన్య **పునాది_handle);

స్థిర పూర్ణాంకం qsv_init_surface(AVHWFramesContext *ctx, mfx_చట్రం_Surface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
పూర్ణాంకం ff_qsv_get_surface_పునాది_handle(mfx_చట్రం_Surface1 *surf,
                                   గణన AVHWDeviceType పునాది_dev_type,
                                   శూన్య **పునాది_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->దత్తాంశం_2.MemId;
    ఎంపిక (పునాది_dev_type) {
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_HWDEVICE_TYPE_VAAPI:
        పునాది_handle[0] = handle_pair->మొదటి;
        తిరిగి 0;
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
    స్థితి AV_HWDEVICE_TYPE_D3D11VA:
        పునాది_handle[0] = handle_pair->మొదటి;
        పునాది_handle[1] = handle_pair->రెండవ;
        తిరిగి 0;
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
    స్థితి AV_HWDEVICE_TYPE_DXVA2:
        పునాది_handle[0] = handle_pair->మొదటి;
        తిరిగి 0;
#అయితే_ముగింపు
    }
    తిరిగి AVERROR(EINVAL);
}

స్థిర uint32_t qsv_fourcc_from_pix_fmt(గణన AVPixelFormat pix_fmt)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        ఒకవేళ (supported_pixel_formats[i].pix_fmt == pix_fmt)
            తిరిగి supported_pixel_formats[i].fourcc;
    }
    తిరిగి 0;
}

స్థిర uint16_t qsv_జరుపు_from_pix_fmt(గణన AVPixelFormat pix_fmt)
{
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        ఒకవేళ (supported_pixel_formats[i].pix_fmt == pix_fmt)
            తిరిగి supported_pixel_formats[i].mfx_జరుపు;
    }

    తిరిగి 0;
}

#ఒకవేళ CONFIG_D3D11VA
స్థిర uint32_t qsv_get_d3d11va_bind_flags(పూర్ణాంకం mem_type)
{
    uint32_t bind_flags = 0;

    ఒకవేళ ((mem_type & MFX_MEMTYPE_VIDEO_జ్ఞాపకం_ENCODER_లక్ష్యం) && (mem_type & MFX_MEMTYPE_అంతర్గత_చట్రం))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    లేకపోతే
        bind_flags = D3D11_BIND_DECODER;

    ఒకవేళ ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_జ్ఞాపకం_PROCESSOR_లక్ష్యం & mem_type))
        bind_flags = D3_D11_BIND_RENDER_లక్ష్యం;

    తిరిగి bind_flags;
}
#అయితే_ముగింపు

స్థిర పూర్ణాంకం qsv_fill_border(AVFrame *dst, స్థిరరాశి AVFrame *src)
{
    స్థిరరాశి AVPixFmtDescriptor *desc;
    పూర్ణాంకం i, planes_nb = 0;
    ఒకవేళ (dst->format != src->format)
        తిరిగి AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    కొరకు (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    కొరకు (i = 0; i < planes_nb; i++) {
        పూర్ణాంకం sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->వెడల్పు,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->వెడల్పు,
                                                 i);
        స్థిరరాశి AVComponentDescriptor comp = desc->comp[i];
        ఒకవేళ (swidth < 0 || dwidth < 0) {
            av_log(ఖాళీ, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            తిరిగి AVERROR(EINVAL);
        }
        sheight = src->ఎత్తు;
        dheight = dst->ఎత్తు;
        ఒకవేళ (i) {
            sheight = AV_CEIL_RSHIFT(src->ఎత్తు, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->ఎత్తు, desc->log2_chroma_h);
        }
        //fill right padding
        కొరకు (y = 0; y < sheight; y++) {
            శూన్య *పంక్తి_ptr = dst->దత్తాంశం[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(పంక్తి_ptr,
                           comp.లోతు > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        కొరకు (y = sheight; y < dheight; y++) {
            జ్ఞాపకం_నకలు(dst->దత్తాంశం[i]+y*dst->linesize[i],
                   dst->దత్తాంశం[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    తిరిగి 0;
}

స్థిర పూర్ణాంకం qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    పూర్ణాంకం   hw_handle_supported = 0;
    mfxHandleType handle_type;
    గణన AVHWDeviceType device_type;
    గణన AVPixelFormat  pix_fmt;
    mfx_స్థితి err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    ఒకవేళ (err == MFX_ERR_NONE)
        err = MFXQuery_సంస్కరణ(hwctx->session, &s->ver);
    ఒకవేళ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    ఒకవేళ (MFX_IMPL_ద్వారా_VAAPI == MFX_IMPL_ద్వారా_ముసుగు(s->impl)) {
#ఒకవేళ CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#అయితే_ముగింపు
    } లేకపోతే ఒకవేళ (MFX_IMPL_ద్వారా_D3_D11 == MFX_IMPL_ద్వారా_ముసుగు(s->impl)) {
#ఒకవేళ CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#అయితే_ముగింపు
    } లేకపోతే ఒకవేళ (MFX_IMPL_ద్వారా_D3_D9 == MFX_IMPL_ద్వారా_ముసుగు(s->impl)) {
#ఒకవేళ CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#అయితే_ముగింపు
    }

    ఒకవేళ (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        ఒకవేళ (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->బిడ్డ_device_type = device_type;
            s->బిడ్డ_pix_fmt     = pix_fmt;
        }
    }
    ఒకవేళ (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    తిరిగి 0;
}

స్థిర శూన్య qsv_చట్రాలు_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    ఒకవేళ (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = ఖాళీ;
    s->session_download_init = 0;

    ఒకవేళ (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = ఖాళీ;
    s->session_upload_init = 0;

#ఒకవేళ HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_తాళం);
#అయితే_ముగింపు

    av_freep(&s->mem_ids);
#ఒకవేళ QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#అయితే_ముగింపు
    av_freep(&s->surfaces_అంతర్గత);
    av_freep(&s->handle_జతలు_అంతర్గత);
    av_చట్రం_unref(&s->realigned_upload_చట్రం);
    av_చట్రం_unref(&s->realigned_download_చట్రం);
    av_బఫరు_unref(&s->బిడ్డ_చట్రాలు_ref);
}

స్థిర శూన్య qsv_pool_release_dummy(శూన్య *opaque, uint8_t *దత్తాంశం)
{
}

స్థిర శూన్య qsv_pool_release(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)దత్తాంశం;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.దత్తాంశం_2.MemId;
    AVHWFramesContext *బిడ్డ_చట్రాలు_ctx;

    ఒకవేళ (!s->బిడ్డ_చట్రాలు_ref)
        తిరిగి;

    బిడ్డ_చట్రాలు_ctx = (AVHWFramesContext*)s->బిడ్డ_చట్రాలు_ref->దత్తాంశం;
    ఒకవేళ (!బిడ్డ_చట్రాలు_ctx->device_ctx)
        తిరిగి;

#ఒకవేళ CONFIG_VAAPI
    ఒకవేళ (బిడ్డ_చట్రాలు_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->మొదటి);
#అయితే_ముగింపు

    av_freep(&hdl_pair);
    av_చట్రం_free(&qsv_surface->బిడ్డ_చట్రం);
    av_freep(&qsv_surface);
}

స్థిర AVBufferRef *qsv_fixed_pool_alloc(శూన్య *opaque, size_t కొలత)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    ఒకవేళ (s->nb_surfaces_వాడిన < hwctx->nb_surfaces) {
        s->nb_surfaces_వాడిన++;
        తిరిగి av_బఫరు_create((uint8_t*)(s->surfaces_అంతర్గత + s->nb_surfaces_వాడిన - 1),
                                పరిమాణం(*hwctx->surfaces), qsv_pool_release_dummy, ఖాళీ, 0);
    }

    తిరిగి ఖాళీ;
}

స్థిర AVBufferRef *qsv_dynamic_pool_alloc(శూన్య *opaque, size_t కొలత)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *బిడ్డ_చట్రాలు_ctx;
    QSVSurface *qsv_surface = ఖాళీ;
    mfxHDLPair *handle_జతలు_అంతర్గత = ఖాళీ;
    పూర్ణాంకం ret;

    ఒకవేళ (!s->బిడ్డ_చట్రాలు_ref)
        వెళ్ళు fail;

    బిడ్డ_చట్రాలు_ctx = (AVHWFramesContext*)s->బిడ్డ_చట్రాలు_ref->దత్తాంశం;
    ఒకవేళ (!బిడ్డ_చట్రాలు_ctx->device_ctx)
        వెళ్ళు fail;

#ఒకవేళ CONFIG_DXVA2
    ఒకవేళ (బిడ్డ_చట్రాలు_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        వెళ్ళు fail;
    }
#అయితే_ముగింపు

    qsv_surface = av_calloc(1, పరిమాణం(*qsv_surface));
    ఒకవేళ (!qsv_surface)
        వెళ్ళు fail;

    qsv_surface->బిడ్డ_చట్రం = av_చట్రం_alloc();
    ఒకవేళ (!qsv_surface->బిడ్డ_చట్రం)
        వెళ్ళు fail;

    ret = av_hwframe_get_బఫరు(s->బిడ్డ_చట్రాలు_ref, qsv_surface->బిడ్డ_చట్రం, 0);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    handle_జతలు_అంతర్గత = av_calloc(1, పరిమాణం(*handle_జతలు_అంతర్గత));
    ఒకవేళ (!handle_జతలు_అంతర్గత)
        వెళ్ళు fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

#ఒకవేళ CONFIG_VAAPI
    ఒకవేళ (బిడ్డ_చట్రాలు_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_అంతర్గత;

        surface_id_అంతర్గత = av_calloc(1, పరిమాణం(*surface_id_అంతర్గత));
        ఒకవేళ (!surface_id_అంతర్గత)
            వెళ్ళు fail;

        *surface_id_అంతర్గత = (VASurfaceID)(uintptr_t)qsv_surface->బిడ్డ_చట్రం->దత్తాంశం[3];
        handle_జతలు_అంతర్గత->మొదటి = (mfxHDL)surface_id_అంతర్గత;
        handle_జతలు_అంతర్గత->రెండవ = (mfxMemId)MFX_INFINITE;
    }
#అయితే_ముగింపు

#ఒకవేళ CONFIG_D3D11VA
    ఒకవేళ (బిడ్డ_చట్రాలు_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *బిడ్డ_చట్రాలు_hwctx = బిడ్డ_చట్రాలు_ctx->hwctx;
        handle_జతలు_అంతర్గత->మొదటి = (mfxMemId)qsv_surface->బిడ్డ_చట్రం->దత్తాంశం[0];

        ఒకవేళ (బిడ్డ_చట్రాలు_hwctx->BindFlags & D3_D11_BIND_RENDER_లక్ష్యం)
            handle_జతలు_అంతర్గత->రెండవ = (mfxMemId)MFX_INFINITE;
        లేకపోతే
            handle_జతలు_అంతర్గత->రెండవ = (mfxMemId)qsv_surface->బిడ్డ_చట్రం->దత్తాంశం[1];

    }
#అయితే_ముగింపు

    qsv_surface->mfx_surface.దత్తాంశం_2.MemId = (mfxMemId)handle_జతలు_అంతర్గత;
    తిరిగి av_బఫరు_create((uint8_t *)qsv_surface, పరిమాణం(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    ఒకవేళ (qsv_surface) {
        av_చట్రం_free(&qsv_surface->బిడ్డ_చట్రం);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_జతలు_అంతర్గత);

    తిరిగి ఖాళీ;
}

స్థిర AVBufferRef *qsv_pool_alloc(శూన్య *opaque, size_t కొలత)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    ఒకవేళ (hwctx->nb_surfaces == 0) {
        తిరిగి qsv_dynamic_pool_alloc(opaque, కొలత);
    } లేకపోతే {
        తిరిగి qsv_fixed_pool_alloc(opaque, కొలత);
    }
}

స్థిర పూర్ణాంకం qsv_init_బిడ్డ_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *బిడ్డ_device_ref = ఖాళీ;
    AVBufferRef *బిడ్డ_చట్రాలు_ref = ఖాళీ;

    AVHWDeviceContext *బిడ్డ_device_ctx;
    AVHWFramesContext *బిడ్డ_చట్రాలు_ctx;

    పూర్ణాంకం i, ret = 0;

    ఒకవేళ (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        తిరిగి AVERROR(EINVAL);
    }

    బిడ్డ_device_ref = av_hwdevice_ctx_alloc(device_priv->బిడ్డ_device_type);
    ఒకవేళ (!బిడ్డ_device_ref)
        తిరిగి AVERROR(ENOMEM);
    బిడ్డ_device_ctx   = (AVHWDeviceContext*)బిడ్డ_device_ref->దత్తాంశం;

#ఒకవేళ CONFIG_VAAPI
    ఒకవేళ (బిడ్డ_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *బిడ్డ_device_hwctx = బిడ్డ_device_ctx->hwctx;
        బిడ్డ_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
    ఒకవేళ (బిడ్డ_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *బిడ్డ_device_hwctx = బిడ్డ_device_ctx->hwctx;
        ID3_D11_Device_కూడు_Ref((ID3D11Device*)device_priv->handle);
        బిడ్డ_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
    ఒకవేళ (బిడ్డ_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *బిడ్డ_device_hwctx = బిడ్డ_device_ctx->hwctx;
        బిడ్డ_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#అయితే_ముగింపు

    ret = av_hwdevice_ctx_init(బిడ్డ_device_ref);
    ఒకవేళ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        వెళ్ళు fail;
    }

    బిడ్డ_చట్రాలు_ref = av_hwframe_ctx_alloc(బిడ్డ_device_ref);
    ఒకవేళ (!బిడ్డ_చట్రాలు_ref) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }
    బిడ్డ_చట్రాలు_ctx = (AVHWFramesContext*)బిడ్డ_చట్రాలు_ref->దత్తాంశం;

    బిడ్డ_చట్రాలు_ctx->format            = device_priv->బిడ్డ_pix_fmt;
    బిడ్డ_చట్రాలు_ctx->sw_format         = ctx->sw_format;
    బిడ్డ_చట్రాలు_ctx->initial_pool_కొలత = ctx->initial_pool_కొలత;
    బిడ్డ_చట్రాలు_ctx->వెడల్పు             = FFALIGN(ctx->వెడల్పు, 16);
    బిడ్డ_చట్రాలు_ctx->ఎత్తు            = FFALIGN(ctx->ఎత్తు, 16);

#ఒకవేళ CONFIG_D3D11VA
    ఒకవేళ (బిడ్డ_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *బిడ్డ_చట్రాలు_hwctx = బిడ్డ_చట్రాలు_ctx->hwctx;
        ఒకవేళ (hwctx->చట్రం_type == 0)
            hwctx->చట్రం_type = MFX_MEMTYPE_VIDEO_జ్ఞాపకం_PROCESSOR_లక్ష్యం;
        ఒకవేళ (hwctx->చట్రం_type & MFX_MEMTYPE_SHARED_RESOURCE)
            బిడ్డ_చట్రాలు_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        బిడ్డ_చట్రాలు_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->చట్రం_type);
    }
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
    ఒకవేళ (బిడ్డ_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_చట్రాలు_Context *బిడ్డ_చట్రాలు_hwctx = బిడ్డ_చట్రాలు_ctx->hwctx;
        ఒకవేళ (hwctx->చట్రం_type & MFX_MEMTYPE_VIDEO_జ్ఞాపకం_PROCESSOR_లక్ష్యం)
            బిడ్డ_చట్రాలు_hwctx->surface_type = DXVA2_Video_Processor_Render_లక్ష్యం;
        లేకపోతే
            బిడ్డ_చట్రాలు_hwctx->surface_type = DXVA2_Video_Decoder_Render_లక్ష్యం;
    }
#అయితే_ముగింపు

    ret = av_hwframe_ctx_init(బిడ్డ_చట్రాలు_ref);
    ఒకవేళ (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        వెళ్ళు fail;
    }

#ఒకవేళ CONFIG_VAAPI
    ఒకవేళ (బిడ్డ_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *బిడ్డ_చట్రాలు_hwctx = బిడ్డ_చట్రాలు_ctx->hwctx;
        కొరకు (i = 0; i < ctx->initial_pool_కొలత; i++) {
            s->handle_జతలు_అంతర్గత[i].మొదటి = బిడ్డ_చట్రాలు_hwctx->surface_ids + i;
            s->handle_జతలు_అంతర్గత[i].రెండవ = (mfxMemId)MFX_INFINITE;
            s->surfaces_అంతర్గత[i].దత్తాంశం_2.MemId = (mfxMemId)&s->handle_జతలు_అంతర్గత[i];
        }
        hwctx->చట్రం_type = MFX_MEMTYPE_VIDEO_జ్ఞాపకం_DECODER_లక్ష్యం;
    }
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
    ఒకవేళ (బిడ్డ_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *బిడ్డ_చట్రాలు_hwctx = బిడ్డ_చట్రాలు_ctx->hwctx;
        కొరకు (i = 0; i < ctx->initial_pool_కొలత; i++) {
            s->handle_జతలు_అంతర్గత[i].మొదటి = (mfxMemId)బిడ్డ_చట్రాలు_hwctx->texture_infos[i].texture;
            ఒకవేళ(బిడ్డ_చట్రాలు_hwctx->BindFlags & D3_D11_BIND_RENDER_లక్ష్యం) {
                s->handle_జతలు_అంతర్గత[i].రెండవ = (mfxMemId)MFX_INFINITE;
            } లేకపోతే {
                s->handle_జతలు_అంతర్గత[i].రెండవ = (mfxMemId)బిడ్డ_చట్రాలు_hwctx->texture_infos[i].సూచీ;
            }
            s->surfaces_అంతర్గత[i].దత్తాంశం_2.MemId = (mfxMemId)&s->handle_జతలు_అంతర్గత[i];
        }
        ఒకవేళ (బిడ్డ_చట్రాలు_hwctx->BindFlags & D3_D11_BIND_RENDER_లక్ష్యం) {
            hwctx->చట్రం_type |= MFX_MEMTYPE_VIDEO_జ్ఞాపకం_PROCESSOR_లక్ష్యం;
        } లేకపోతే {
            hwctx->చట్రం_type |= MFX_MEMTYPE_VIDEO_జ్ఞాపకం_DECODER_లక్ష్యం;
        }
    }
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
    ఒకవేళ (బిడ్డ_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_చట్రాలు_Context *బిడ్డ_చట్రాలు_hwctx = బిడ్డ_చట్రాలు_ctx->hwctx;
        కొరకు (i = 0; i < ctx->initial_pool_కొలత; i++) {
            s->handle_జతలు_అంతర్గత[i].మొదటి = (mfxMemId)బిడ్డ_చట్రాలు_hwctx->surfaces[i];
            s->handle_జతలు_అంతర్గత[i].రెండవ = (mfxMemId)MFX_INFINITE;
            s->surfaces_అంతర్గత[i].దత్తాంశం_2.MemId = (mfxMemId)&s->handle_జతలు_అంతర్గత[i];
        }
        ఒకవేళ (బిడ్డ_చట్రాలు_hwctx->surface_type == DXVA2_Video_Processor_Render_లక్ష్యం)
            hwctx->చట్రం_type = MFX_MEMTYPE_VIDEO_జ్ఞాపకం_PROCESSOR_లక్ష్యం;
        లేకపోతే
            hwctx->చట్రం_type = MFX_MEMTYPE_VIDEO_జ్ఞాపకం_DECODER_లక్ష్యం;
    }
#అయితే_ముగింపు

    s->బిడ్డ_చట్రాలు_ref       = బిడ్డ_చట్రాలు_ref;
    బిడ్డ_చట్రాలు_ref          = ఖాళీ;

fail:
    av_బఫరు_unref(&బిడ్డ_device_ref);
    av_బఫరు_unref(&బిడ్డ_చట్రాలు_ref);
    తిరిగి ret;
}

స్థిర పూర్ణాంకం qsv_init_surface(AVHWFramesContext *ctx, mfx_చట్రం_Surface1 *surf)
{
    స్థిరరాశి AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    ఒకవేళ (!desc)
        తిరిగి AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    ఒకవేళ (!fourcc)
        తిరిగి AVERROR(EINVAL);

    surf->Info.బిట్టు_లోతు_Luma   = desc->comp[0].లోతు;
    surf->Info.బిట్టు_లోతు_Chroma = desc->comp[0].లోతు;
    surf->Info.జరుపు_2          = qsv_జరుపు_from_pix_fmt(ctx->sw_format);

    ఒకవేళ (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    లేకపోతే ఒకవేళ (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    లేకపోతే
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.వెడల్పు_2          = FFALIGN(ctx->వెడల్పు, 16);
    surf->Info.CropW          = ctx->వెడల్పు;
    surf->Info.ఎత్తు_2         = FFALIGN(ctx->ఎత్తు, 16);
    surf->Info.CropH          = ctx->ఎత్తు;
    surf->Info.చట్రం_రేటు_Ext_N  = 25;
    surf->Info.చట్రం_రేటు_Ext_D  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *చట్రాలు_hwctx = &s->p;

    పూర్ణాంకం i, ret = 0;

    ఒకవేళ (ctx->initial_pool_కొలత < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        తిరిగి AVERROR(EINVAL);
    } లేకపోతే ఒకవేళ (ctx->initial_pool_కొలత == 0) {
        mfx_చట్రం_Surface1 mfx_surf1;

        ret = qsv_init_బిడ్డ_ctx(ctx);
        ఒకవేళ (ret < 0)
            తిరిగి ret;

        ffhwframesctx(ctx)->pool_అంతర్గత = av_బఫరు_pool_init2(పరిమాణం(mfx_చట్రం_Surface1),
                                                                 ctx, qsv_pool_alloc, ఖాళీ);
        ఒకవేళ (!ffhwframesctx(ctx)->pool_అంతర్గత)
            తిరిగి AVERROR(ENOMEM);

        memset(&mfx_surf1, 0, పరిమాణం(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->చట్రం_info = mfx_surf1.Info;
        చట్రాలు_hwctx->info = &s->చట్రం_info;
        చట్రాలు_hwctx->nb_surfaces = 0;

        తిరిగి 0;
    }

    s->handle_జతలు_అంతర్గత = av_calloc(ctx->initial_pool_కొలత,
                                         పరిమాణం(*s->handle_జతలు_అంతర్గత));
    ఒకవేళ (!s->handle_జతలు_అంతర్గత)
        తిరిగి AVERROR(ENOMEM);

    s->surfaces_అంతర్గత = av_calloc(ctx->initial_pool_కొలత,
                                     పరిమాణం(*s->surfaces_అంతర్గత));
    ఒకవేళ (!s->surfaces_అంతర్గత)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (i = 0; i < ctx->initial_pool_కొలత; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_అంతర్గత[i]);
        ఒకవేళ (ret < 0)
            తిరిగి ret;
    }

#ఒకవేళ QSV_HAVE_OPAQUE
    ఒకవేళ (!(చట్రాలు_hwctx->చట్రం_type & MFX_MEMTYPE_OPAQUE_చట్రం)) {
        ret = qsv_init_బిడ్డ_ctx(ctx);
        ఒకవేళ (ret < 0)
            తిరిగి ret;
    }
#లేకపోతే
    ret = qsv_init_బిడ్డ_ctx(ctx);
    ఒకవేళ (ret < 0)
        తిరిగి ret;
#అయితే_ముగింపు

    ffhwframesctx(ctx)->pool_అంతర్గత = av_బఫరు_pool_init2(పరిమాణం(mfx_చట్రం_Surface1),
                                                             ctx, qsv_pool_alloc, ఖాళీ);
    ఒకవేళ (!ffhwframesctx(ctx)->pool_అంతర్గత)
        తిరిగి AVERROR(ENOMEM);

    చట్రాలు_hwctx->surfaces    = s->surfaces_అంతర్గత;
    చట్రాలు_hwctx->nb_surfaces = ctx->initial_pool_కొలత;

    తిరిగి 0;
}

స్థిర mfx_స్థితి చట్రం_alloc(mfxHDL pthis, mfx_చట్రం_Alloc_Request *req,
                             mfx_చట్రం_Alloc_Response *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfx_చట్రం_Info *i  = &req->Info;
    mfx_చట్రం_Info *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    ఒకవేళ (!(req->Type & MFX_MEMTYPE_VIDEO_జ్ఞాపకం_PROCESSOR_లక్ష్యం) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_చట్రం))
        తిరిగి MFX_ERR_UNSUPPORTED;
    ఒకవేళ (i->వెడల్పు_2  > i1->వెడల్పు_2 || i->ఎత్తు_2 > i1->ఎత్తు_2 ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->వెడల్పు_2,  i->ఎత్తు_2,  i->FourCC,  i->ChromaFormat,
               i1->వెడల్పు_2, i1->ఎత్తు_2, i1->FourCC, i1->ChromaFormat);
        తిరిగి MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->అంకె_చట్రం_Actual = hwctx->nb_surfaces;

    తిరిగి MFX_ERR_NONE;
}

స్థిర mfx_స్థితి చట్రం_free(mfxHDL pthis, mfx_చట్రం_Alloc_Response *resp)
{
    తిరిగి MFX_ERR_NONE;
}

స్థిర mfx_స్థితి చట్రం_తాళం(mfxHDL pthis, mfxMemId mid, mfx_చట్రం_దత్తాంశం *ptr)
{
    తిరిగి MFX_ERR_UNSUPPORTED;
}

స్థిర mfx_స్థితి చట్రం_unlock(mfxHDL pthis, mfxMemId mid, mfx_చట్రం_దత్తాంశం *ptr)
{
    తిరిగి MFX_ERR_UNSUPPORTED;
}

స్థిర mfx_స్థితి చట్రం_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->మొదటి = pair_src->మొదటి;

    ఒకవేళ (pair_src->రెండవ != (mfxMemId)MFX_INFINITE)
        pair_dst->రెండవ = pair_src->రెండవ;
    తిరిగి MFX_ERR_NONE;
}

#ఒకవేళ QSV_ONEVPL

స్థిర పూర్ణాంకం qsv_d3d11_update_config(శూన్య *ctx, mfxHDL handle, mfxConfig cfg)
{
    పూర్ణాంకం ret = AVERROR_UNKNOWN;
#ఒకవేళ CONFIG_D3D11VA
    mfx_స్థితి sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = ఖాళీ;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_విలువ = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (శూన్య**)&pDXGIDevice);
    ఒకవేళ (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        ఒకవేళ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            తిరిగి ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        ఒకవేళ (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            వెళ్ళు fail;
        }
    } లేకపోతే {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        తిరిగి ret;
    }

    impl_విలువ.Type = MFX_VARIANT_TYPE_U16;
    impl_విలువ.దత్తాంశం_2.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (స్థిరరాశి mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_విలువ);
    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        వెళ్ళు fail;
    }

    impl_విలువ.Type = MFX_VARIANT_TYPE_PTR;
    impl_విలువ.దత్తాంశం_2.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (స్థిరరాశి mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_విలువ);
    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        వెళ్ళు fail;
    }

    impl_విలువ.Type = MFX_VARIANT_TYPE_U32;
    impl_విలువ.దత్తాంశం_2.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (స్థిరరాశి mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_విలువ);
    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        వెళ్ళు fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#అయితే_ముగింపు
    తిరిగి ret;
}

స్థిర పూర్ణాంకం qsv_d3d9_update_config(శూన్య *ctx, mfxHDL handle, mfxConfig cfg)
{
    పూర్ణాంకం ret = AVERROR_UNKNOWN;
#ఒకవేళ CONFIG_DXVA2
    mfx_స్థితి sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = ఖాళీ;
    IDirect3DDevice9Ex *device_ex = ఖాళీ;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = ఖాళీ;
    IDirect3D9 *d3d9 = ఖాళీ;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_విలువ = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        వెళ్ళు fail;
    }

    hr = IDirect3_DDevice_Manager9_తాళం_Device(devmgr, device_handle, &device, TRUE);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        వెళ్ళు fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (శూన్య **)&device_ex);
    IDirect3DDevice9_Release(device);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        వెళ్ళు unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        వెళ్ళు unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        వెళ్ళు unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (శూన్య **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        వెళ్ళు unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        వెళ్ళు release;
    }

    impl_విలువ.Type = MFX_VARIANT_TYPE_PTR;
    impl_విలువ.దత్తాంశం_2.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (స్థిరరాశి mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_విలువ);
    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        వెళ్ళు release;
    }

    ret = 0;

release:
    IDirect3D9Ex_Release(d3d9ex);
    IDirect3DDevice9Ex_Release(device_ex);

unlock:
    IDirect3DDeviceManager9_UnlockDevice(devmgr, device_handle, FALSE);
    IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
fail:
#అయితే_ముగింపు
    తిరిగి ret;
}

స్థిర పూర్ణాంకం qsv_va_update_config(శూన్య *ctx, mfxHDL handle, mfxConfig cfg)
{
#ఒకవేళ CONFIG_VAAPI
#ఒకవేళ VA_CHECK_సంస్కరణ(1, 15, 0)
    mfx_స్థితి sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_విలువ = {0};

    vas = va_Get_Display_లక్షణాలు(dpy, &attr, 1);
    ఒకవేళ (vas == VA_స్థితి_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_విలువ.Type = MFX_VARIANT_TYPE_U16;
        impl_విలువ.దత్తాంశం_2.U16 = (attr.విలువ & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (స్థిరరాశి mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_విలువ);
        ఒకవేళ (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            వెళ్ళు fail;
        }
    } లేకపోతే {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        వెళ్ళు fail;
    }

    తిరిగి 0;

fail:
#లేకపోతే
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#అయితే_ముగింపు
#అయితే_ముగింపు
    తిరిగి AVERROR_UNKNOWN;
}

స్థిర పూర్ణాంకం qsv_new_mfx_loader(శూన్య *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfx_సంస్కరణ *pver,
                              శూన్య **ploader)
{
    mfx_స్థితి sts;
    mfxLoader loader = ఖాళీ;
    mfxConfig cfg;
    mfxVariant impl_విలువ = {0};

    *ploader = ఖాళీ;
    loader = MFXLoad();
    ఒకవేళ (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        వెళ్ళు fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    ఒకవేళ (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        వెళ్ళు fail;
    }

    impl_విలువ.Type = MFX_VARIANT_TYPE_U32;
    impl_విలువ.దత్తాంశం_2.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (స్థిరరాశి mfxU8 *)"mfxImplDescription.Impl", impl_విలువ);
    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        వెళ్ళు fail;
    }

    impl_విలువ.Type = MFX_VARIANT_TYPE_U32;
    impl_విలువ.దత్తాంశం_2.U32 = pver->సంస్కరణ_2;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (స్థిరరాశి mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_విలువ);
    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        వెళ్ళు fail;
    }

    impl_విలువ.Type = MFX_VARIANT_TYPE_U32;
    impl_విలువ.దత్తాంశం_2.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (స్థిరరాశి mfxU8 *)"mfxImplDescription.VendorID", impl_విలువ);
    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        వెళ్ళు fail;
    }

    ఒకవేళ (MFX_HANDLE_VA_DISPLAY == handle_type) {
        ఒకవేళ (handle && qsv_va_update_config(ctx, handle, cfg))
            వెళ్ళు fail;

        impl_విలువ.దత్తాంశం_2.U32 = MFX_ACCEL_బహుళకం_ద్వారా_VAAPI;
    } లేకపోతే ఒకవేళ (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        ఒకవేళ (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            వెళ్ళు fail;

        impl_విలువ.దత్తాంశం_2.U32 = MFX_ACCEL_బహుళకం_ద్వారా_D3_D9;
    } లేకపోతే {
        ఒకవేళ (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            వెళ్ళు fail;

        impl_విలువ.దత్తాంశం_2.U32 = MFX_ACCEL_బహుళకం_ద్వారా_D3_D11;
    }

    impl_విలువ.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (స్థిరరాశి mfxU8 *)"mfxImplDescription.AccelerationMode", impl_విలువ);
    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        వెళ్ళు fail;
    }

    *ploader = loader;

    తిరిగి 0;

fail:
    ఒకవేళ (loader)
        MFXUnload(loader);

    తిరిగి AVERROR_UNKNOWN;
}

స్థిర పూర్ణాంకం qsv_create_mfx_session_from_loader(శూన్య *ctx, mfxLoader loader, mfxSession *psession)
{
    mfx_స్థితి sts;
    mfxSession session = ఖాళీ;
    uint32_t impl_idx = 0;
    mfx_సంస్కరణ ver;

    అయితే (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        ఒకవేళ (sts == MFX_ERR_NOT_దొరికింది)
            ఆపు;
        లేకపోతే ఒకవేళ (sts != MFX_ERR_NONE) {
            impl_idx++;
            కొనసాగు;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        ఒకవేళ (sts == MFX_ERR_NONE)
            ఆపు;

        impl_idx++;
    }

    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        వెళ్ళు fail;
    }

    sts = MFXQuery_సంస్కరణ(session, &ver);
    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        వెళ్ళు fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    తిరిగి 0;

fail:
    ఒకవేళ (session)
        MFXClose(session);

    తిరిగి AVERROR_UNKNOWN;
}

స్థిర పూర్ణాంకం qsv_create_mfx_session(శూన్య *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfx_సంస్కరణ *pver,
                                  mfxSession *psession,
                                  శూన్య **ploader)
{
    mfxLoader loader = ఖాళీ;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_సంస్కరణ_MAJOR, MFX_సంస్కరణ_MINOR, pver->Major, pver->Minor);

    ఒకవేళ (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        తిరిగి AVERROR(EXDEV);
    }

    *psession = ఖాళీ;

    ఒకవేళ (!*ploader) {
        ఒకవేళ (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (శూన్య **)&loader))
            వెళ్ళు fail;

        av_assert0(loader);
    } లేకపోతే
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    ఒకవేళ (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        వెళ్ళు fail;

    ఒకవేళ (!*ploader)
        *ploader = loader;

    తిరిగి 0;

fail:
    ఒకవేళ (!*ploader && loader)
        MFXUnload(loader);

    తిరిగి AVERROR_UNKNOWN;
}

#లేకపోతే

స్థిర పూర్ణాంకం qsv_create_mfx_session(శూన్య *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfx_సంస్కరణ *pver,
                                  mfxSession *psession,
                                  శూన్య **ploader)
{
    mfx_సంస్కరణ ver;
    mfx_స్థితి sts;
    mfxSession session = ఖాళీ;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_సంస్కరణ_MAJOR, MFX_సంస్కరణ_MINOR, pver->Major, pver->Minor);

    *ploader = ఖాళీ;
    *psession = ఖాళీ;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        వెళ్ళు fail;
    }

    sts = MFXQuery_సంస్కరణ(session, &ver);
    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        వెళ్ళు fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    ఒకవేళ (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        వెళ్ళు fail;
    }

    *psession = session;

    తిరిగి 0;

fail:
    ఒకవేళ (session)
        MFXClose(session);

    తిరిగి AVERROR_UNKNOWN;
}

#అయితే_ముగింపు

స్థిర పూర్ణాంకం qsv_init_అంతర్గత_session(AVHWFramesContext *ctx,
                                     mfxSession *session, పూర్ణాంకం upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *చట్రాలు_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    పూర్ణాంకం opaque = 0;

    mfx_చట్రం_Allocator చట్రం_allocator = {
        .pthis  = ctx,
        .Alloc  = చట్రం_alloc,
        .తాళం_3   = చట్రం_తాళం,
        .Unlock = చట్రం_unlock,
        .GetHDL = చట్రం_get_hdl,
        .Free   = చట్రం_free,
    };

    mfxVideoParam par;
    mfx_స్థితి err;
    పూర్ణాంకం                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    శూన్య             **loader = &hwctx->loader;
    mfxSession మాతృ_session = hwctx->session;
    mfxIMPL impl;
    mfx_సంస్కరణ ver;

    err = MFXQueryIMPL(మాతృ_session, &impl);
    ఒకవేళ (err == MFX_ERR_NONE)
        err = MFXQuery_సంస్కరణ(మాతృ_session, &ver);
    ఒకవేళ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        తిరిగి AVERROR_UNKNOWN;
    }

#ఒకవేళ QSV_HAVE_OPAQUE
    opaque = !!(చట్రాలు_hwctx->చట్రం_type & MFX_MEMTYPE_OPAQUE_చట్రం);
#అయితే_ముగింపు

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    ఒకవేళ (ret)
        వెళ్ళు fail;

    ఒకవేళ (device_priv->handle) {
        err = MFXVideo_CORE_సమితి_Handle(*session, device_priv->handle_type,
                                     device_priv->handle);
        ఒకవేళ (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            వెళ్ళు fail;
        }
    }

    ఒకవేళ (QSV_RUNTIME_సంస్కరణ_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(మాతృ_session, *session);
        ఒకవేళ (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            వెళ్ళు fail;
        }
    }

    ఒకవేళ (!opaque) {
        err = MFXVideo_CORE_సమితి_చట్రం_Allocator(*session, &చట్రం_allocator);
        ఒకవేళ (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            వెళ్ళు fail;
        }
    }

    memset(&par, 0, పరిమాణం(par));

    ఒకవేళ (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_బహిర్గతం_VIDEO_జ్ఞాపకం :
                                 MFX_IOPATTERN_లోపల_VIDEO_జ్ఞాపకం;
    }
#ఒకవేళ QSV_HAVE_OPAQUE
    లేకపోతే {
        par.ExtParam    = s->ext_buffers;
        par.అంకె_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
        par.IOPattern   = upload ? MFX_IOPATTERN_బహిర్గతం_OPAQUE_జ్ఞాపకం :
                                   MFX_IOPATTERN_లోపల_OPAQUE_జ్ఞాపకం;
    }
#అయితే_ముగింపు

    par.IOPattern |= upload ? MFX_IOPATTERN_లోపల_SYSTEM_జ్ఞాపకం :
                              MFX_IOPATTERN_బహిర్గతం_SYSTEM_జ్ఞాపకం;
    par.Async_లోతు = 1;

    par.vpp.లోపల_2 = చట్రాలు_hwctx->nb_surfaces ? చట్రాలు_hwctx->surfaces[0].Info : *చట్రాలు_hwctx->info;

    /* Apparently VPP requires the frame rate to be set to some value, otherwise
     * init will fail (probably for the framerate conversion filter). Since we
     * are only doing data upload/download here, we just invent an arbitrary
     * value */
    par.vpp.లోపల_2.చట్రం_రేటు_Ext_N = 25;
    par.vpp.లోపల_2.చట్రం_రేటు_Ext_D = 1;
    par.vpp.బహిర్గతం_2 = par.vpp.లోపల_2;

    err = MFXVideoVPP_Init(*session, &par);
    ఒకవేళ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        వెళ్ళు fail;
    }

    తిరిగి 0;

fail:
    ఒకవేళ (*session)
        MFXClose(*session);

    *session = ఖాళీ;

    తిరిగి ret;
}

స్థిర పూర్ణాంకం qsv_చట్రాలు_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *చట్రాలు_hwctx = &s->p;

    పూర్ణాంకం opaque = 0;

    uint32_t fourcc;
    పూర్ణాంకం i, ret;

#ఒకవేళ QSV_HAVE_OPAQUE
    opaque = !!(చట్రాలు_hwctx->చట్రం_type & MFX_MEMTYPE_OPAQUE_చట్రం);
#అయితే_ముగింపు

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    ఒకవేళ (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        తిరిగి AVERROR(ENOSYS);
    }

    ఒకవేళ (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        ఒకవేళ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            తిరిగి ret;
        }
    }

    ఒకవేళ (!opaque) {
        s->mem_ids = av_calloc(చట్రాలు_hwctx->nb_surfaces, పరిమాణం(*s->mem_ids));
        ఒకవేళ (!s->mem_ids)
            తిరిగి AVERROR(ENOMEM);

        కొరకు (i = 0; i < చట్రాలు_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = చట్రాలు_hwctx->surfaces[i].దత్తాంశం_2.MemId;
    }
#ఒకవేళ QSV_HAVE_OPAQUE
    లేకపోతే {
        s->surface_ptrs = av_calloc(చట్రాలు_hwctx->nb_surfaces,
                                    పరిమాణం(*s->surface_ptrs));
        ఒకవేళ (!s->surface_ptrs)
            తిరిగి AVERROR(ENOMEM);

        కొరకు (i = 0; i < చట్రాలు_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = చట్రాలు_hwctx->surfaces + i;

        s->opaque_alloc.లోపల_2.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.లోపల_2.అంకె_Surface = చట్రాలు_hwctx->nb_surfaces;
        s->opaque_alloc.లోపల_2.Type       = చట్రాలు_hwctx->చట్రం_type;

        s->opaque_alloc.బహిర్గతం_2 = s->opaque_alloc.లోపల_2;

        s->opaque_alloc.శీర్షిక_2.బఫరు_Id = MFX_EXTBUFF_OPAQUE_SURFACE_కేటాయింపు;
        s->opaque_alloc.శీర్షిక_2.బఫరు_Sz = పరిమాణం(s->opaque_alloc);

        s->ext_buffers[0] = (mfx_Ext_బఫరు*)&s->opaque_alloc;
    }
#అయితే_ముగింపు

    s->session_download = ఖాళీ;
    s->session_upload   = ఖాళీ;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#ఒకవేళ HAVE_PTHREADS
    pthread_mutex_init(&s->session_తాళం, ఖాళీ);
#అయితే_ముగింపు

    తిరిగి 0;
}

స్థిర పూర్ణాంకం qsv_get_బఫరు(AVHWFramesContext *ctx, AVFrame *చట్రం)
{
    చట్రం->buf[0] = av_బఫరు_pool_get(ctx->pool);
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి AVERROR(ENOMEM);

    చట్రం->దత్తాంశం[3] = చట్రం->buf[0]->దత్తాంశం;
    చట్రం->format  = AV_PIX_FMT_QSV;
    చట్రం->వెడల్పు   = ctx->వెడల్పు;
    చట్రం->ఎత్తు  = ctx->ఎత్తు;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    గణన AVHWFrameTransferDirection dir,
                                    గణన AVPixelFormat **formats)
{
    గణన AVPixelFormat *fmts;

    fmts = av_malloc_array(2, పరిమాణం(*fmts));
    ఒకవేళ (!fmts)
        తిరిగి AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం qsv_చట్రాలు_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, పూర్ణాంకం flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    పూర్ణాంకం i;

    ఎంపిక (dst_ctx->device_ctx->type) {
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               పరిమాణం(*dst_hwctx->surface_ids));
            ఒకవేళ (!dst_hwctx->surface_ids)
                తిరిగి AVERROR(ENOMEM);
            కొరకు (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].దత్తాంశం_2.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->మొదటి;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
    స్థితి AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_కొలత = src_ctx->initial_pool_కొలత;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 పరిమాణం(*dst_hwctx->texture_infos));
            ఒకవేళ (!dst_hwctx->texture_infos)
                తిరిగి AVERROR(ENOMEM);
            ఒకవేళ (src_hwctx->చట్రం_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            కొరకు (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].దత్తాంశం_2.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->మొదటి;
                dst_hwctx->texture_infos[i].సూచీ = pair->రెండవ == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->రెండవ;
            }
            ఒకవేళ (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } లేకపోతే
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->చట్రం_type);
        }
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
    స్థితి AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_చట్రాలు_Context *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            పరిమాణం(*dst_hwctx->surfaces));
            ఒకవేళ (!dst_hwctx->surfaces)
                తిరిగి AVERROR(ENOMEM);
            కొరకు (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].దత్తాంశం_2.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->మొదటి;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            ఒకవేళ (src_hwctx->చట్రం_type == MFX_MEMTYPE_VIDEO_జ్ఞాపకం_DECODER_లక్ష్యం)
                dst_hwctx->surface_type = DXVA2_Video_Decoder_Render_లక్ష్యం;
            లేకపోతే
                dst_hwctx->surface_type = DXVA2_Video_Processor_Render_లక్ష్యం;
        }
        ఆపు;
#అయితే_ముగింపు
    అప్రమేయ:
        తిరిగి AVERROR(ENOSYS);
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfx_చట్రం_Surface1 *surf = (mfx_చట్రం_Surface1*)src->దత్తాంశం[3];
    AVHWFramesContext *బిడ్డ_చట్రాలు_ctx;
    స్థిరరాశి AVPixFmtDescriptor *desc;
    uint8_t *బిడ్డ_దత్తాంశం;
    AVFrame *dummy;
    పూర్ణాంకం ret = 0;

    ఒకవేళ (!s->బిడ్డ_చట్రాలు_ref)
        తిరిగి AVERROR(ENOSYS);
    బిడ్డ_చట్రాలు_ctx = (AVHWFramesContext*)s->బిడ్డ_చట్రాలు_ref->దత్తాంశం;

    ఎంపిక (బిడ్డ_చట్రాలు_ctx->device_ctx->type) {
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->దత్తాంశం_2.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        బిడ్డ_దత్తాంశం = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->మొదటి;
        ఆపు;
    }
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
    స్థితి AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->దత్తాంశం_2.MemId;
        బిడ్డ_దత్తాంశం = pair->మొదటి;
        ఆపు;
    }
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
    స్థితి AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->దత్తాంశం_2.MemId;
        బిడ్డ_దత్తాంశం = pair->మొదటి;
        ఆపు;
    }
#అయితే_ముగింపు
    అప్రమేయ:
        తిరిగి AVERROR(ENOSYS);
    }

    ఒకవేళ (dst->format == బిడ్డ_చట్రాలు_ctx->format) {
        ret = ff_hwframe_map_create(s->బిడ్డ_చట్రాలు_ref,
                                    dst, src, ఖాళీ, ఖాళీ);
        ఒకవేళ (ret < 0)
            తిరిగి ret;

        dst->వెడల్పు   = src->వెడల్పు;
        dst->ఎత్తు  = src->ఎత్తు;

       ఒకవేళ (బిడ్డ_చట్రాలు_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->దత్తాంశం_2.MemId;
            dst->దత్తాంశం[0] = pair->మొదటి;
            dst->దత్తాంశం[1] = pair->రెండవ == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->రెండవ;
        } లేకపోతే {
            dst->దత్తాంశం[3] = బిడ్డ_దత్తాంశం;
        }

        తిరిగి 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    ఒకవేళ (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        తిరిగి AVERROR(ENOSYS);
    }

    dummy = av_చట్రం_alloc();
    ఒకవేళ (!dummy)
        తిరిగి AVERROR(ENOMEM);

    dummy->buf[0]        = av_బఫరు_ref(src->buf[0]);
    dummy->hw_చట్రాలు_ctx = av_బఫరు_ref(s->బిడ్డ_చట్రాలు_ref);
    ఒకవేళ (!dummy->buf[0] || !dummy->hw_చట్రాలు_ctx)
        వెళ్ళు fail;

    dummy->format        = బిడ్డ_చట్రాలు_ctx->format;
    dummy->వెడల్పు         = src->వెడల్పు;
    dummy->ఎత్తు        = src->ఎత్తు;

    ఒకవేళ (బిడ్డ_చట్రాలు_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->దత్తాంశం_2.MemId;
        dummy->దత్తాంశం[0] = pair->మొదటి;
        dummy->దత్తాంశం[1] = pair->రెండవ == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->రెండవ;
    } లేకపోతే {
        dummy->దత్తాంశం[3] = బిడ్డ_దత్తాంశం;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_చట్రం_free(&dummy);

    తిరిగి ret;
}

స్థిర పూర్ణాంకం qsv_transfer_దత్తాంశం_బిడ్డ(AVHWFramesContext *ctx, AVFrame *dst,
                                   స్థిరరాశి AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *బిడ్డ_చట్రాలు_ctx = (AVHWFramesContext*)s->బిడ్డ_చట్రాలు_ref->దత్తాంశం;
    పూర్ణాంకం download = !!src->hw_చట్రాలు_ctx;
    mfx_చట్రం_Surface1 *surf = (mfx_చట్రం_Surface1*)(download ? src->దత్తాంశం[3] : dst->దత్తాంశం[3]);

    AVFrame *dummy;
    పూర్ణాంకం ret;

    dummy = av_చట్రం_alloc();
    ఒకవేళ (!dummy)
        తిరిగి AVERROR(ENOMEM);

    dummy->format        = బిడ్డ_చట్రాలు_ctx->format;
    dummy->వెడల్పు         = src->వెడల్పు;
    dummy->ఎత్తు        = src->ఎత్తు;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->దత్తాంశం[3]       = surf->దత్తాంశం_2.MemId;
    dummy->hw_చట్రాలు_ctx = s->బిడ్డ_చట్రాలు_ref;

    ret = download ? av_hwframe_transfer_దత్తాంశం(dst, dummy, 0) :
                     av_hwframe_transfer_దత్తాంశం(dummy, src, 0);

    dummy->buf[0]        = ఖాళీ;
    dummy->దత్తాంశం[3]       = ఖాళీ;
    dummy->hw_చట్రాలు_ctx = ఖాళీ;

    av_చట్రం_free(&dummy);

    తిరిగి ret;
}

స్థిర పూర్ణాంకం map_చట్రం_గమ్యం_surface(స్థిరరాశి AVFrame *చట్రం, mfx_చట్రం_Surface1 *surface)
{
    ఎంపిక (చట్రం->format) {
    స్థితి AV_PIX_FMT_NV12:
    స్థితి AV_PIX_FMT_P010:
    స్థితి AV_PIX_FMT_P012:
        surface->దత్తాంశం_2.Y  = చట్రం->దత్తాంశం[0];
        surface->దత్తాంశం_2.UV = చట్రం->దత్తాంశం[1];
        ఆపు;

    స్థితి AV_PIX_FMT_YUV420P:
        surface->దత్తాంశం_2.Y = చట్రం->దత్తాంశం[0];
        surface->దత్తాంశం_2.U = చట్రం->దత్తాంశం[1];
        surface->దత్తాంశం_2.V = చట్రం->దత్తాంశం[2];
        ఆపు;

    స్థితి AV_PIX_FMT_BGRA:
        surface->దత్తాంశం_2.B = చట్రం->దత్తాంశం[0];
        surface->దత్తాంశం_2.G = చట్రం->దత్తాంశం[0] + 1;
        surface->దత్తాంశం_2.R = చట్రం->దత్తాంశం[0] + 2;
        surface->దత్తాంశం_2.A = చట్రం->దత్తాంశం[0] + 3;
        ఆపు;
    స్థితి AV_PIX_FMT_YUYV422:
        surface->దత్తాంశం_2.Y = చట్రం->దత్తాంశం[0];
        surface->దత్తాంశం_2.U = చట్రం->దత్తాంశం[0] + 1;
        surface->దత్తాంశం_2.V = చట్రం->దత్తాంశం[0] + 3;
        ఆపు;

    స్థితి AV_PIX_FMT_Y210:
    స్థితి AV_PIX_FMT_Y212:
        surface->దత్తాంశం_2.Y16 = (mfxU16 *)చట్రం->దత్తాంశం[0];
        surface->దత్తాంశం_2.U16 = (mfxU16 *)చట్రం->దత్తాంశం[0] + 1;
        surface->దత్తాంశం_2.V16 = (mfxU16 *)చట్రం->దత్తాంశం[0] + 3;
        ఆపు;
    స్థితి AV_PIX_FMT_VUYX:
        surface->దత్తాంశం_2.V = చట్రం->దత్తాంశం[0];
        surface->దత్తాంశం_2.U = చట్రం->దత్తాంశం[0] + 1;
        surface->దత్తాంశం_2.Y = చట్రం->దత్తాంశం[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->దత్తాంశం_2.A = చట్రం->దత్తాంశం[0] + 3;
        ఆపు;
    స్థితి AV_PIX_FMT_XV30:
        surface->దత్తాంశం_2.U = చట్రం->దత్తాంశం[0];
        ఆపు;
    స్థితి AV_PIX_FMT_XV36:
        surface->దత్తాంశం_2.U = చట్రం->దత్తాంశం[0];
        surface->దత్తాంశం_2.Y = చట్రం->దత్తాంశం[0] + 2;
        surface->దత్తాంశం_2.V = చట్రం->దత్తాంశం[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->దత్తాంశం_2.A = చట్రం->దత్తాంశం[0] + 6;
        ఆపు;
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_PIX_FMT_UYVY422:
        surface->దత్తాంశం_2.Y = చట్రం->దత్తాంశం[0] + 1;
        surface->దత్తాంశం_2.U = చట్రం->దత్తాంశం[0];
        surface->దత్తాంశం_2.V = చట్రం->దత్తాంశం[0] + 2;
        ఆపు;
#అయితే_ముగింపు
    అప్రమేయ:
        తిరిగి MFX_ERR_UNSUPPORTED;
    }
    surface->దత్తాంశం_2.Pitch     = చట్రం->linesize[0];
    surface->దత్తాంశం_2.సమయం_Stamp = చట్రం->pts;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం qsv_అంతర్గత_session_check_init(AVHWFramesContext *ctx, పూర్ణాంకం upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    పూర్ణాంకం ret = 0;

    ఒకవేళ (atomic_load(inited))
        తిరిగి 0;

#ఒకవేళ HAVE_PTHREADS
    pthread_mutex_తాళం(&s->session_తాళం);
#అయితే_ముగింపు

    ఒకవేళ (!atomic_load(inited)) {
        ret = qsv_init_అంతర్గత_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#ఒకవేళ HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_తాళం);
#అయితే_ముగింపు

    తిరిగి ret;
}

స్థిర పూర్ణాంకం qsv_transfer_దత్తాంశం_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  స్థిరరాశి AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfx_చట్రం_Surface1 బహిర్గతం = {{ 0 }};
    mfx_చట్రం_Surface1 *లోపల = (mfx_చట్రం_Surface1*)src->దత్తాంశం[3];

    mfx_Sync_బిందువు sync = ఖాళీ;
    mfx_స్థితి err;
    పూర్ణాంకం ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_చట్రం = &s->realigned_download_చట్రం;
    AVFrame *dst_చట్రం;
    పూర్ణాంకం realigned = 0;

    ret = qsv_అంతర్గత_session_check_init(ctx, 0);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    ఒకవేళ (dst->ఎత్తు & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        ఒకవేళ (tmp_చట్రం->format != dst->format ||
            tmp_చట్రం->వెడల్పు  != FFALIGN(dst->linesize[0], 16) ||
            tmp_చట్రం->ఎత్తు != FFALIGN(dst->ఎత్తు, 16)) {
            av_చట్రం_unref(tmp_చట్రం);

            tmp_చట్రం->format = dst->format;
            tmp_చట్రం->వెడల్పు  = FFALIGN(dst->linesize[0], 16);
            tmp_చట్రం->ఎత్తు = FFALIGN(dst->ఎత్తు, 16);
            ret = av_చట్రం_get_బఫరు(tmp_చట్రం, 0);
            ఒకవేళ (ret < 0)
                తిరిగి ret;
        }
    }

    dst_చట్రం = realigned ? tmp_చట్రం : dst;

    ఒకవేళ (!s->session_download) {
        ఒకవేళ (s->బిడ్డ_చట్రాలు_ref)
            తిరిగి qsv_transfer_దత్తాంశం_బిడ్డ(ctx, dst_చట్రం, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        తిరిగి AVERROR(ENOSYS);
    }

    బహిర్గతం.Info = లోపల->Info;
    map_చట్రం_గమ్యం_surface(dst_చట్రం, &బహిర్గతం);

    చేయి {
        err = MFXVideo_VPP_నిరంతరం_చట్రం_VPPAsync(s->session_download, లోపల, &బహిర్గతం, ఖాళీ, &sync);
        ఒకవేళ (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } అయితే (err == MFX_WRN_DEVICE_BUSY);

    ఒకవేళ (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    చేయి {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } అయితే (err == MFX_WRN_లోపల_EXECUTION);
    ఒకవేళ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        తిరిగి AVERROR_UNKNOWN;
    }

    ఒకవేళ (realigned) {
        tmp_చట్రం->వెడల్పు  = dst->వెడల్పు;
        tmp_చట్రం->ఎత్తు = dst->ఎత్తు;
        ret = av_చట్రం_copy(dst, tmp_చట్రం);
        tmp_చట్రం->వెడల్పు  = FFALIGN(dst->linesize[0], 16);
        tmp_చట్రం->ఎత్తు = FFALIGN(dst->ఎత్తు, 16);
        ఒకవేళ (ret < 0)
            తిరిగి ret;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం qsv_transfer_దత్తాంశం_గమ్యం(AVHWFramesContext *ctx, AVFrame *dst,
                                స్థిరరాశి AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfx_చట్రం_Surface1   లోపల = {{ 0 }};
    mfx_చట్రం_Surface1 *బహిర్గతం = (mfx_చట్రం_Surface1*)dst->దత్తాంశం[3];
    mfx_చట్రం_Info tmp_info;

    mfx_Sync_బిందువు sync = ఖాళీ;
    mfx_స్థితి err;
    పూర్ణాంకం ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_చట్రం = &s->realigned_upload_చట్రం;
    స్థిరరాశి AVFrame *src_చట్రం;
    పూర్ణాంకం realigned = 0;

    ret = qsv_అంతర్గత_session_check_init(ctx, 1);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    ఒకవేళ (src->ఎత్తు & 15 || src->linesize[0] & 15) {
        realigned = 1;
        ఒకవేళ (tmp_చట్రం->format != src->format ||
            tmp_చట్రం->వెడల్పు  != FFALIGN(src->వెడల్పు, 16) ||
            tmp_చట్రం->ఎత్తు != FFALIGN(src->ఎత్తు, 16)) {
            av_చట్రం_unref(tmp_చట్రం);

            tmp_చట్రం->format = src->format;
            tmp_చట్రం->వెడల్పు  = FFALIGN(src->వెడల్పు, 16);
            tmp_చట్రం->ఎత్తు = FFALIGN(src->ఎత్తు, 16);
            ret = av_చట్రం_get_బఫరు(tmp_చట్రం, 0);
            ఒకవేళ (ret < 0)
                తిరిగి ret;
        }
        ret = av_చట్రం_copy(tmp_చట్రం, src);
        ఒకవేళ (ret < 0) {
            av_చట్రం_unref(tmp_చట్రం);
            తిరిగి ret;
        }
        ret = qsv_fill_border(tmp_చట్రం, src);
        ఒకవేళ (ret < 0) {
            av_చట్రం_unref(tmp_చట్రం);
            తిరిగి ret;
        }

        tmp_info = బహిర్గతం->Info;
        బహిర్గతం->Info.CropW = FFMIN(బహిర్గతం->Info.వెడల్పు_2,  tmp_చట్రం->వెడల్పు);
        బహిర్గతం->Info.CropH = FFMIN(బహిర్గతం->Info.ఎత్తు_2, tmp_చట్రం->ఎత్తు);
    }

    src_చట్రం = realigned ? tmp_చట్రం : src;

    ఒకవేళ (!s->session_upload) {
        ఒకవేళ (s->బిడ్డ_చట్రాలు_ref)
            తిరిగి qsv_transfer_దత్తాంశం_బిడ్డ(ctx, dst, src_చట్రం);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        తిరిగి AVERROR(ENOSYS);
    }

    లోపల.Info = బహిర్గతం->Info;
    map_చట్రం_గమ్యం_surface(src_చట్రం, &లోపల);

    చేయి {
        err = MFXVideo_VPP_నిరంతరం_చట్రం_VPPAsync(s->session_upload, &లోపల, బహిర్గతం, ఖాళీ, &sync);
        ఒకవేళ (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } అయితే (err == MFX_WRN_DEVICE_BUSY);

    ఒకవేళ (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    చేయి {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } అయితే (err == MFX_WRN_లోపల_EXECUTION);
    ఒకవేళ (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    ఒకవేళ (realigned) {
        బహిర్గతం->Info.CropW = tmp_info.CropW;
        బహిర్గతం->Info.CropH = tmp_info.CropH;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం qsv_dynamic_చట్రాలు_derive_గమ్యం(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, పూర్ణాంకం flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfx_చట్రం_Surface1 mfx_surf1;

    ఎంపిక (src_ctx->device_ctx->type) {
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->చట్రం_type  = MFX_MEMTYPE_VIDEO_జ్ఞాపకం_DECODER_లక్ష్యం;
        ఆపు;
#అయితే_ముగింపు

#ఒకవేళ CONFIG_D3D11VA
    స్థితి AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        ఒకవేళ (src_hwctx->BindFlags & D3_D11_BIND_RENDER_లక్ష్యం) {
            dst_hwctx->చట్రం_type |= MFX_MEMTYPE_VIDEO_జ్ఞాపకం_PROCESSOR_లక్ష్యం;
        } లేకపోతే {
            dst_hwctx->చట్రం_type |= MFX_MEMTYPE_VIDEO_జ్ఞాపకం_DECODER_లక్ష్యం;
        }
    }
    ఆపు;
#అయితే_ముగింపు

    అప్రమేయ:
        తిరిగి AVERROR(ENOSYS);
    }

    memset(&mfx_surf1, 0, పరిమాణం(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->చట్రం_info = mfx_surf1.Info;
    dst_hwctx->info = &s->చట్రం_info;
    dst_hwctx->nb_surfaces = 0;
    తిరిగి 0;
}

స్థిర పూర్ణాంకం qsv_fixed_చట్రాలు_derive_గమ్యం(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, పూర్ణాంకం flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    పూర్ణాంకం i;

    ఎంపిక (src_ctx->device_ctx->type) {
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_జతలు_అంతర్గత = av_calloc(src_ctx->initial_pool_కొలత,
                                                 పరిమాణం(*s->handle_జతలు_అంతర్గత));
            ఒకవేళ (!s->handle_జతలు_అంతర్గత)
                తిరిగి AVERROR(ENOMEM);
            s->surfaces_అంతర్గత = av_calloc(src_hwctx->nb_surfaces,
                                             పరిమాణం(*s->surfaces_అంతర్గత));
            ఒకవేళ (!s->surfaces_అంతర్గత)
                తిరిగి AVERROR(ENOMEM);
            కొరకు (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_అంతర్గత[i]);
                s->handle_జతలు_అంతర్గత[i].మొదటి = src_hwctx->surface_ids + i;
                s->handle_జతలు_అంతర్గత[i].రెండవ = (mfxMemId)MFX_INFINITE;
                s->surfaces_అంతర్గత[i].దత్తాంశం_2.MemId = (mfxMemId)&s->handle_జతలు_అంతర్గత[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->చట్రం_type  = MFX_MEMTYPE_VIDEO_జ్ఞాపకం_DECODER_లక్ష్యం;
        }
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
    స్థితి AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_జతలు_అంతర్గత = av_calloc(src_ctx->initial_pool_కొలత,
                                                 పరిమాణం(*s->handle_జతలు_అంతర్గత));
            ఒకవేళ (!s->handle_జతలు_అంతర్గత)
                తిరిగి AVERROR(ENOMEM);
            s->surfaces_అంతర్గత = av_calloc(src_ctx->initial_pool_కొలత,
                                             పరిమాణం(*s->surfaces_అంతర్గత));
            ఒకవేళ (!s->surfaces_అంతర్గత)
                తిరిగి AVERROR(ENOMEM);
            కొరకు (i = 0; i < src_ctx->initial_pool_కొలత; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_అంతర్గత[i]);
                s->handle_జతలు_అంతర్గత[i].మొదటి = (mfxMemId)src_hwctx->texture_infos[i].texture;
                ఒకవేళ (src_hwctx->BindFlags & D3_D11_BIND_RENDER_లక్ష్యం) {
                    s->handle_జతలు_అంతర్గత[i].రెండవ = (mfxMemId)MFX_INFINITE;
                } లేకపోతే {
                    s->handle_జతలు_అంతర్గత[i].రెండవ = (mfxMemId)src_hwctx->texture_infos[i].సూచీ;
                }
                s->surfaces_అంతర్గత[i].దత్తాంశం_2.MemId = (mfxMemId)&s->handle_జతలు_అంతర్గత[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_కొలత;
            ఒకవేళ (src_hwctx->BindFlags & D3_D11_BIND_RENDER_లక్ష్యం) {
                dst_hwctx->చట్రం_type |= MFX_MEMTYPE_VIDEO_జ్ఞాపకం_PROCESSOR_లక్ష్యం;
            } లేకపోతే {
                dst_hwctx->చట్రం_type |= MFX_MEMTYPE_VIDEO_జ్ఞాపకం_DECODER_లక్ష్యం;
            }
        }
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
    స్థితి AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_చట్రాలు_Context *src_hwctx = src_ctx->hwctx;
            s->handle_జతలు_అంతర్గత = av_calloc(src_ctx->initial_pool_కొలత,
                                                 పరిమాణం(*s->handle_జతలు_అంతర్గత));
            ఒకవేళ (!s->handle_జతలు_అంతర్గత)
                తిరిగి AVERROR(ENOMEM);
            s->surfaces_అంతర్గత = av_calloc(src_hwctx->nb_surfaces,
                                             పరిమాణం(*s->surfaces_అంతర్గత));
            ఒకవేళ (!s->surfaces_అంతర్గత)
                తిరిగి AVERROR(ENOMEM);
            కొరకు (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_అంతర్గత[i]);
                s->handle_జతలు_అంతర్గత[i].మొదటి = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_జతలు_అంతర్గత[i].రెండవ = (mfxMemId)MFX_INFINITE;
                s->surfaces_అంతర్గత[i].దత్తాంశం_2.MemId = (mfxMemId)&s->handle_జతలు_అంతర్గత[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            ఒకవేళ (src_hwctx->surface_type == DXVA2_Video_Processor_Render_లక్ష్యం)
                dst_hwctx->చట్రం_type = MFX_MEMTYPE_VIDEO_జ్ఞాపకం_PROCESSOR_లక్ష్యం;
            లేకపోతే
                dst_hwctx->చట్రం_type = MFX_MEMTYPE_VIDEO_జ్ఞాపకం_DECODER_లక్ష్యం;
        }
        ఆపు;
#అయితే_ముగింపు
    అప్రమేయ:
        తిరిగి AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_అంతర్గత;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం qsv_చట్రాలు_derive_గమ్యం(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, పూర్ణాంకం flags)
{
    ఒకవేళ (src_ctx->initial_pool_కొలత < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        తిరిగి AVERROR(EINVAL);
    } లేకపోతే ఒకవేళ (src_ctx->initial_pool_కొలత == 0) {
        తిరిగి qsv_dynamic_చట్రాలు_derive_గమ్యం(dst_ctx, src_ctx, flags);
    } లేకపోతే {
        తిరిగి qsv_fixed_చట్రాలు_derive_గమ్యం(dst_ctx, src_ctx, flags);
    }
}

స్థిర పూర్ణాంకం qsv_fixed_pool_map_గమ్యం(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    పూర్ణాంకం i, err, సూచీ = -1;

    కొరకు (i = 0; i < hwctx->nb_surfaces && సూచీ < 0; i++) {
        ఎంపిక(src->format) {
#ఒకవేళ CONFIG_VAAPI
        స్థితి AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].దత్తాంశం_2.MemId;
            ఒకవేళ (*(VASurfaceID*)pair->మొదటి == (VASurfaceID)(uintptr_t)src->దత్తాంశం[3])
                సూచీ = i;
            ఆపు;
        }
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
        స్థితి AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].దత్తాంశం_2.MemId;
            ఒకవేళ (pair->మొదటి == src->దత్తాంశం[0]
                && (pair->రెండవ == src->దత్తాంశం[1]
                    || (pair->రెండవ == (mfxMemId)MFX_INFINITE && src->దత్తాంశం[1] == (uint8_t *)0)))
                సూచీ = i;
            ఆపు;
        }
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
        స్థితి AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].దత్తాంశం_2.MemId;
            ఒకవేళ (pair->మొదటి == src->దత్తాంశం[3])
                సూచీ = i;
            ఆపు;
        }
#అయితే_ముగింపు
        }
    }
    ఒకవేళ (సూచీ < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        తిరిగి AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_చట్రాలు_ctx,
                                dst, src, ఖాళీ, ఖాళీ);
    ఒకవేళ (err)
        తిరిగి err;

    dst->వెడల్పు   = src->వెడల్పు;
    dst->ఎత్తు  = src->ఎత్తు;
    dst->దత్తాంశం[3] = (uint8_t*)&hwctx->surfaces[సూచీ];

    తిరిగి 0;
}

స్థిర శూన్య qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfx_చట్రం_Surface1 *surfaces_అంతర్గత = (mfx_చట్రం_Surface1 *)hwmap->priv;
    mfxHDLPair *handle_జతలు_అంతర్గత = (mfxHDLPair *)surfaces_అంతర్గత->దత్తాంశం_2.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->ఆధారం_చట్రాలు->దత్తాంశం;

    ఎంపిక (src_ctx->format) {
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_జతలు_అంతర్గత->మొదటి);

        ఆపు;
    }
#అయితే_ముగింపు

#ఒకవేళ CONFIG_D3D11VA
    స్థితి AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        ఆపు;
    }
#అయితే_ముగింపు
    అప్రమేయ:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        ఆపు;
    }

    av_freep(&handle_జతలు_అంతర్గత);
    av_freep(&surfaces_అంతర్గత);
}

స్థిర పూర్ణాంకం qsv_dynamic_pool_map_గమ్యం(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    mfx_చట్రం_Surface1 *surfaces_అంతర్గత = ఖాళీ;
    mfxHDLPair *handle_జతలు_అంతర్గత = ఖాళీ;
    పూర్ణాంకం ret = 0;

    surfaces_అంతర్గత = av_calloc(1, పరిమాణం(*surfaces_అంతర్గత));
    ఒకవేళ (!surfaces_అంతర్గత) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    handle_జతలు_అంతర్గత = av_calloc(1, పరిమాణం(*handle_జతలు_అంతర్గత));
    ఒకవేళ (!handle_జతలు_అంతర్గత) {
        ret = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_అంతర్గత);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    ఎంపిక (src->format) {
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_అంతర్గత;

        surface_id_అంతర్గత = av_calloc(1, పరిమాణం(*surface_id_అంతర్గత));
        ఒకవేళ (!surface_id_అంతర్గత) {
            ret =AVERROR(ENOMEM);
            వెళ్ళు fail;
        }

        *surface_id_అంతర్గత = (VASurfaceID)(uintptr_t)src->దత్తాంశం[3];
        handle_జతలు_అంతర్గత->మొదటి = (mfxHDL)surface_id_అంతర్గత;
        handle_జతలు_అంతర్గత->రెండవ = (mfxMemId)MFX_INFINITE;

        ఆపు;
    }
#అయితే_ముగింపు

#ఒకవేళ CONFIG_D3D11VA
    స్థితి AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_చట్రాలు_ctx->దత్తాంశం;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_జతలు_అంతర్గత->మొదటి = (mfxMemId)src->దత్తాంశం[0];

        ఒకవేళ (src_hwctx->BindFlags & D3_D11_BIND_RENDER_లక్ష్యం) {
            handle_జతలు_అంతర్గత->రెండవ = (mfxMemId)MFX_INFINITE;
        } లేకపోతే {
            handle_జతలు_అంతర్గత->రెండవ = (mfxMemId)src->దత్తాంశం[1];
        }

        ఆపు;
    }
#అయితే_ముగింపు
    అప్రమేయ:
        ret = AVERROR(ENOSYS);
        వెళ్ళు fail;
    }

    surfaces_అంతర్గత->దత్తాంశం_2.MemId = (mfxMemId)handle_జతలు_అంతర్గత;

    ret = ff_hwframe_map_create(dst->hw_చట్రాలు_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_అంతర్గత);
    ఒకవేళ (ret)
        వెళ్ళు fail;

    dst->వెడల్పు   = src->వెడల్పు;
    dst->ఎత్తు  = src->ఎత్తు;
    dst->దత్తాంశం[3] = (uint8_t*)surfaces_అంతర్గత;

    తిరిగి 0;

fail:
    av_freep(&handle_జతలు_అంతర్గత);
    av_freep(&surfaces_అంతర్గత);
    తిరిగి ret;
}

స్థిర పూర్ణాంకం qsv_map_గమ్యం(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    ఒకవేళ (hwctx->nb_surfaces)
        తిరిగి qsv_fixed_pool_map_గమ్యం(dst_ctx, dst, src, flags);
    లేకపోతే
        తిరిగి qsv_dynamic_pool_map_గమ్యం(dst_ctx, dst, src, flags);
}

స్థిర పూర్ణాంకం qsv_చట్రాలు_get_constraints(AVHWDeviceContext *ctx,
                                      స్థిరరాశి శూన్య *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    పూర్ణాంకం i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    పరిమాణం(*constraints->valid_sw_formats));
    ఒకవేళ (!constraints->valid_sw_formats)
        తిరిగి AVERROR(ENOMEM);

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, పరిమాణం(*constraints->valid_hw_formats));
    ఒకవేళ (!constraints->valid_hw_formats)
        తిరిగి AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    తిరిగి 0;
}

స్థిర శూన్య qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    ఒకవేళ (hwctx->session)
        MFXClose(hwctx->session);

    ఒకవేళ (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_బఫరు_unref(&priv->బిడ్డ_device_ctx);
    av_freep(&priv);
}

స్థిర mfxIMPL ఎంచుకో_implementation(స్థిరరాశి అక్షరం *device, గణన AVHWDeviceType బిడ్డ_device_type)
{
    స్థిర స్థిరరాశి నిర్మాణం {
        స్థిరరాశి అక్షరం *name;
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
    పూర్ణాంకం i;

    ఒకవేళ (device) {
        కొరకు (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            ఒకవేళ (!strcmp(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                ఆపు;
            }
        ఒకవేళ (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, ఖాళీ, 0);
    }

    ఒకవేళ (impl != MFX_IMPL_SOFTWARE) {
        ఒకవేళ (బిడ్డ_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_ద్వారా_D3_D11;
        లేకపోతే ఒకవేళ (బిడ్డ_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_ద్వారా_D3_D9;
    }

    తిరిగి impl;
}

స్థిర పూర్ణాంకం qsv_device_derive_from_బిడ్డ(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *బిడ్డ_device_ctx,
                                        పూర్ణాంకం flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfx_సంస్కరణ    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfx_స్థితి     err;
    పూర్ణాంకం ret;

    ఎంపిక (బిడ్డ_device_ctx->type) {
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *బిడ్డ_device_hwctx = బిడ్డ_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)బిడ్డ_device_hwctx->display;
        }
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
    స్థితి AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *బిడ్డ_device_hwctx = బిడ్డ_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)బిడ్డ_device_hwctx->device;
        }
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
    స్థితి AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *బిడ్డ_device_hwctx = బిడ్డ_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)బిడ్డ_device_hwctx->devmgr;
        }
        ఆపు;
#అయితే_ముగింపు
    అప్రమేయ:
        ret = AVERROR(ENOSYS);
        వెళ్ళు fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    ఒకవేళ (ret)
        వెళ్ళు fail;

    err = MFXVideo_CORE_సమితి_Handle(hwctx->session, handle_type, handle);
    ఒకవేళ (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        వెళ్ళు fail;
    }

    తిరిగి 0;

fail:
    ఒకవేళ (hwctx->session)
        MFXClose(hwctx->session);

    ఒకవేళ (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = ఖాళీ;
    hwctx->loader = ఖాళీ;
    తిరిగి ret;
}

స్థిర పూర్ణాంకం qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *బిడ్డ_device_ctx,
                             AVDictionary *opts, పూర్ణాంకం flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(పరిమాణం(*priv));
    ఒకవేళ (!priv)
        తిరిగి AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->విడుదల = qsv_device_free;

    impl = ఎంచుకో_implementation("hw_any", బిడ్డ_device_ctx->type);
    తిరిగి qsv_device_derive_from_బిడ్డ(ctx, impl,
                                        బిడ్డ_device_ctx, flags);
}

స్థిర పూర్ణాంకం qsv_device_create(AVHWDeviceContext *ctx, స్థిరరాశి అక్షరం *device,
                             AVDictionary *opts, పూర్ణాంకం flags)
{
    QSVDevicePriv *priv;
    గణన AVHWDeviceType బిడ్డ_device_type;
    AVHWDeviceContext *బిడ్డ_device;
    AVDictionary *బిడ్డ_device_opts;
    AVDictionary_నమోదు *e;

    mfxIMPL impl;
    పూర్ణాంకం ret;

    priv = av_mallocz(పరిమాణం(*priv));
    ఒకవేళ (!priv)
        తిరిగి AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->విడుదల        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", ఖాళీ, 0);
    ఒకవేళ (e) {
        బిడ్డ_device_type = av_hwdevice_కనుగొను_type_by_name(e->విలువ);
        ఒకవేళ (బిడ్డ_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->విలువ);
            తిరిగి AVERROR(EINVAL);
        }
#ఒకవేళ QSV_ONEVPL
    } లేకపోతే ఒకవేళ (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        బిడ్డ_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } లేకపోతే ఒకవేళ (CONFIG_DXVA2) {
        బిడ్డ_device_type = AV_HWDEVICE_TYPE_DXVA2;
#లేకపోతే
    } లేకపోతే ఒకవేళ (CONFIG_DXVA2) {
        av_log(ఖాళీ, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        బిడ్డ_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } లేకపోతే ఒకవేళ (CONFIG_D3D11VA) {
        బిడ్డ_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#అయితే_ముగింపు
    } లేకపోతే ఒకవేళ (CONFIG_VAAPI) {
        బిడ్డ_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } లేకపోతే {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        తిరిగి AVERROR(ENOSYS);
    }

#ఒకవేళ CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    ఒకవేళ (బిడ్డ_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->విలువ);
        తిరిగి AVERROR(EINVAL);
    }
#అయితే_ముగింపు

    బిడ్డ_device_opts = ఖాళీ;
    ఎంపిక (బిడ్డ_device_type) {
#ఒకవేళ CONFIG_VAAPI
    స్థితి AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_సమితి(&బిడ్డ_device_opts, "vendor_id", "0x8086", 0);
            av_dict_సమితి(&బిడ్డ_device_opts, "driver",    "iHD",    0);
        }
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ CONFIG_D3D11VA
    స్థితి AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_సమితి(&బిడ్డ_device_opts, "vendor_id",        "0x8086",  0);
        }
        ఆపు;
#అయితే_ముగింపు
#ఒకవేళ CONFIG_DXVA2
    స్థితి AV_HWDEVICE_TYPE_DXVA2:
#ఒకవేళ QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#అయితే_ముగింపు
        ఆపు;
#అయితే_ముగింపు
    అప్రమేయ:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            తిరిగి AVERROR(ENOSYS);
        }
        ఆపు;
    }

    e = av_dict_get(opts, "child_device", ఖాళీ, 0);
    ret = av_hwdevice_ctx_create(&priv->బిడ్డ_device_ctx, బిడ్డ_device_type,
                                 e ? e->విలువ : ఖాళీ, బిడ్డ_device_opts, 0);

    av_dict_free(&బిడ్డ_device_opts);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    బిడ్డ_device = (AVHWDeviceContext*)priv->బిడ్డ_device_ctx->దత్తాంశం;

    impl = ఎంచుకో_implementation(device, బిడ్డ_device_type);

    తిరిగి qsv_device_derive_from_బిడ్డ(ctx, impl, బిడ్డ_device, 0);
}

స్థిరరాశి HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_కొలత      = పరిమాణం(QSVDeviceContext),
    .చట్రాలు_hwctx_కొలత      = పరిమాణం(QSVFramesContext),

    .device_create          = qsv_device_create,
    .device_derive          = qsv_device_derive,
    .device_init            = qsv_device_init,
    .చట్రాలు_get_constraints = qsv_చట్రాలు_get_constraints,
    .చట్రాలు_init            = qsv_చట్రాలు_init,
    .చట్రాలు_uninit          = qsv_చట్రాలు_uninit,
    .చట్రాలు_get_బఫరు      = qsv_get_బఫరు,
    .transfer_get_formats   = qsv_transfer_get_formats,
    .transfer_దత్తాంశం_గమ్యం       = qsv_transfer_దత్తాంశం_గమ్యం,
    .transfer_దత్తాంశం_from     = qsv_transfer_దత్తాంశం_from,
    .map_గమ్యం                 = qsv_map_గమ్యం,
    .map_from               = qsv_map_from,
    .చట్రాలు_derive_గమ్యం       = qsv_చట్రాలు_derive_గమ్యం,
    .చట్రాలు_derive_from     = qsv_చట్రాలు_derive_from,

    .pix_fmts = (స్థిరరాశి గణన AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
