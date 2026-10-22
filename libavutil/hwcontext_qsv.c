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

#अन्तर्भाव <stdatomic.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव <mfxvideo.h>

#अन्तर्भाव "config.h"

#यदि HAVE_PTHREADS
#अन्तर्भाव <pthread.h>
#यदि_अन्तः

#परिभाषय COBJMACROS
#यदि CONFIG_VAAPI
#अन्तर्भाव "hwcontext_vaapi.h"
#यदि_अन्तः
#यदि CONFIG_D3D11VA
#अन्तर्भाव "hwcontext_d3d11va.h"
#यदि_अन्तः
#यदि CONFIG_DXVA2
#अन्तर्भाव <initguid.h>
#अन्तर्भाव "hwcontext_dxva2.h"
#यदि_अन्तः

#अन्तर्भाव "buffer.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "hwcontext_qsv.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "time.h"
#अन्तर्भाव "imgutils.h"
#अन्तर्भाव "avassert.h"

#परिभाषय QSV_संस्करणम्_ATLEAST(MAJOR, MINOR)   \
    (MFX_संस्करणम्_MAJOR > (MAJOR) ||         \
     MFX_संस्करणम्_MAJOR == (MAJOR) && MFX_संस्करणम्_MINOR >= (MINOR))

#परिभाषय QSV_RUNTIME_संस्करणम्_ATLEAST(MFX_संस्करणम्, MAJOR, MINOR)          \
    ((MFX_संस्करणम्.Major > (MAJOR)) ||                                   \
     (MFX_संस्करणम्.Major == (MAJOR) && MFX_संस्करणम्.Minor >= (MINOR)))

#परिभाषय MFX_IMPL_द्वारा_आवरणम्(impl) (0x0f00 & (impl))
#परिभाषय QSV_ONEVPL       QSV_संस्करणम्_ATLEAST(2, 0)
#परिभाषय QSV_HAVE_OPAQUE  !QSV_ONEVPL

#यदि QSV_ONEVPL
#अन्तर्भाव <mfxdispatcher.h>
#अन्यथा
#परिभाषय MFXUnload(a) कुरु { } यावत्(0)
#यदि_अन्तः

प्रकारनिर्देश संरचना QSVDevicePriv {
    AVBufferRef *child_device_ctx;
} QSVDevicePriv;

प्रकारनिर्देश संरचना QSVDeviceContext {
    /**
     * The public AVQSVDeviceContext. See hwcontext_qsv.h for it.
     */
    AVQSVDeviceContext p;

    mfxHDL              handle;
    mfxHandleType       handle_type;
    mfx_संस्करणम्          ver;
    mfxIMPL             impl;

    गणना AVHWDeviceType child_device_type;
    गणना AVPixelFormat  child_pix_fmt;
} QSVDeviceContext;

प्रकारनिर्देश संरचना QSVFramesContext {
    /**
     * The public AVQSVFramesContext. See hwcontext_qsv.h for it.
     */
    AVQSVFramesContext p;

    mfxSession session_download;
    atomic_int session_download_init;
    mfxSession session_upload;
    atomic_int session_upload_init;
#यदि HAVE_PTHREADS
    pthread_mutex_t session_तालकम्;
#यदि_अन्तः

    AVBufferRef *child_चौकटाः_ref;
    mfxFrameSurface1 *surfaces_आन्तरिकम्;
    mfxHDLPair *handle_युग्मानि_आन्तरिकम्;
    पूर्णाङ्क             nb_surfaces_प्रयुक्तम्;

    // used in the frame allocator for non-opaque surfaces
    mfxMemId *mem_ids;
#यदि QSV_HAVE_OPAQUE
    // used in the opaque alloc request for opaque surfaces
    mfxFrameSurface1 **surface_ptrs;

    mfxExtOpaqueSurfaceAlloc opaque_alloc;
    mfx_Ext_बफर *ext_buffers[1];
#यदि_अन्तः
    AVFrame realigned_upload_frame;
    AVFrame realigned_download_frame;

    mfxFrameInfo frame_info;
} QSVFramesContext;

प्रकारनिर्देश संरचना QSVSurface {
    mfxFrameSurface1 mfx_surface;
    AVFrame *child_frame;
} QSVSurface;

स्थिर ध्रुव संरचना {
    गणना AVPixelFormat pix_fmt;
    uint32_t           fourcc;
    uint16_t           mfx_सरणम्;
} supported_pixel_formats[] = {
    { AV_PIX_FMT_NV12, MFX_FOURCC_NV12, 0 },
    { AV_PIX_FMT_BGRA, MFX_FOURCC_RGB4, 0 },
    { AV_PIX_FMT_P010, MFX_FOURCC_P010, 1 },
    { AV_PIX_FMT_PAL8, MFX_FOURCC_P8,   0 },
    { AV_PIX_FMT_YUYV422,
                       MFX_FOURCC_YUY2, 0 },
#यदि CONFIG_VAAPI
    { AV_PIX_FMT_UYVY422,
                       MFX_FOURCC_UYVY, 0 },
#यदि_अन्तः
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
#यदि QSV_संस्करणम्_ATLEAST(1, 31)
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
#यदि_अन्तः
};

बाह्य पूर्णाङ्क ff_qsv_get_surface_आधारः_handle(mfxFrameSurface1 *surf,
                                          गणना AVHWDeviceType आधारः_dev_type,
                                          शून्य **आधारः_handle);

स्थिर पूर्णाङ्क qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf);

/**
 * Caller needs to allocate enough space for base_handle pointer.
 **/
पूर्णाङ्क ff_qsv_get_surface_आधारः_handle(mfxFrameSurface1 *surf,
                                   गणना AVHWDeviceType आधारः_dev_type,
                                   शून्य **आधारः_handle)
{
    mfxHDLPair *handle_pair;
    handle_pair = surf->दत्त_2.MemId;
    विकल्प (आधारः_dev_type) {
#यदि CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        आधारः_handle[0] = handle_pair->first;
        प्रत्यागम 0;
#यदि_अन्तः
#यदि CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        आधारः_handle[0] = handle_pair->first;
        आधारः_handle[1] = handle_pair->second;
        प्रत्यागम 0;
#यदि_अन्तः
#यदि CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        आधारः_handle[0] = handle_pair->first;
        प्रत्यागम 0;
#यदि_अन्तः
    }
    प्रत्यागम AVERROR(EINVAL);
}

स्थिर uint32_t qsv_fourcc_from_pix_fmt(गणना AVPixelFormat pix_fmt)
{
    पूर्णाङ्क i;
    प्रति (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        यदि (supported_pixel_formats[i].pix_fmt == pix_fmt)
            प्रत्यागम supported_pixel_formats[i].fourcc;
    }
    प्रत्यागम 0;
}

स्थिर uint16_t qsv_सरणम्_from_pix_fmt(गणना AVPixelFormat pix_fmt)
{
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++) {
        यदि (supported_pixel_formats[i].pix_fmt == pix_fmt)
            प्रत्यागम supported_pixel_formats[i].mfx_सरणम्;
    }

    प्रत्यागम 0;
}

#यदि CONFIG_D3D11VA
स्थिर uint32_t qsv_get_d3d11va_bind_flags(पूर्णाङ्क mem_type)
{
    uint32_t bind_flags = 0;

    यदि ((mem_type & MFX_MEMTYPE_VIDEO_स्मृतिः_ENCODER_TARGET) && (mem_type & MFX_MEMTYPE_आन्तरिकम्_FRAME))
        bind_flags = D3D11_BIND_DECODER | D3D11_BIND_VIDEO_ENCODER;
    अन्यथा
        bind_flags = D3D11_BIND_DECODER;

    यदि ((MFX_MEMTYPE_FROM_VPPOUT & mem_type) || (MFX_MEMTYPE_VIDEO_स्मृतिः_PROCESSOR_TARGET & mem_type))
        bind_flags = D3D11_BIND_RENDER_TARGET;

    प्रत्यागम bind_flags;
}
#यदि_अन्तः

स्थिर पूर्णाङ्क qsv_fill_border(AVFrame *dst, ध्रुव AVFrame *src)
{
    ध्रुव AVPixFmtDescriptor *desc;
    पूर्णाङ्क i, planes_nb = 0;
    यदि (dst->format != src->format)
        प्रत्यागम AVERROR(EINVAL);

    desc = av_pix_fmt_desc_get(dst->format);

    प्रति (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    प्रति (i = 0; i < planes_nb; i++) {
        पूर्णाङ्क sheight, dheight, y;
        ptrdiff_t swidth = av_image_get_linesize(src->format,
                                                 src->विस्तारः,
                                                 i);
        ptrdiff_t dwidth = av_image_get_linesize(dst->format,
                                                 dst->विस्तारः,
                                                 i);
        ध्रुव AVComponentDescriptor comp = desc->comp[i];
        यदि (swidth < 0 || dwidth < 0) {
            av_log(रिक्त, AV_LOG_ERROR, "av_image_get_linesize failed\n");
            प्रत्यागम AVERROR(EINVAL);
        }
        sheight = src->height;
        dheight = dst->height;
        यदि (i) {
            sheight = AV_CEIL_RSHIFT(src->height, desc->log2_chroma_h);
            dheight = AV_CEIL_RSHIFT(dst->height, desc->log2_chroma_h);
        }
        //fill right padding
        प्रति (y = 0; y < sheight; y++) {
            शून्य *पङ्क्तिः_ptr = dst->दत्त[i] + y*dst->linesize[i] + swidth;
            av_memcpy_backptr(पङ्क्तिः_ptr,
                           comp.गभीरता > 8 ? 2 : 1,
                           dwidth - swidth);
        }
        //fill bottom padding
        प्रति (y = sheight; y < dheight; y++) {
            स्मृतिं_प्रतिलिख(dst->दत्त[i]+y*dst->linesize[i],
                   dst->दत्त[i]+(sheight-1)*dst->linesize[i],
                   dwidth);
        }
    }
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क qsv_device_init(AVHWDeviceContext *ctx)
{
    QSVDeviceContext       *s = ctx->hwctx;
    AVQSVDeviceContext *hwctx = &s->p;
    पूर्णाङ्क   hw_handle_supported = 0;
    mfxHandleType handle_type;
    गणना AVHWDeviceType device_type;
    गणना AVPixelFormat  pix_fmt;
    mfx_स्थितिः err;

    err = MFXQueryIMPL(hwctx->session, &s->impl);
    यदि (err == MFX_ERR_NONE)
        err = MFXQuery_संस्करणम्(hwctx->session, &s->ver);
    यदि (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    यदि (MFX_IMPL_द्वारा_VAAPI == MFX_IMPL_द्वारा_आवरणम्(s->impl)) {
#यदि CONFIG_VAAPI
        handle_type = MFX_HANDLE_VA_DISPLAY;
        device_type = AV_HWDEVICE_TYPE_VAAPI;
        pix_fmt = AV_PIX_FMT_VAAPI;
        hw_handle_supported = 1;
#यदि_अन्तः
    } अन्यथा यदि (MFX_IMPL_द्वारा_D3_D11 == MFX_IMPL_द्वारा_आवरणम्(s->impl)) {
#यदि CONFIG_D3D11VA
        handle_type = MFX_HANDLE_D3D11_DEVICE;
        device_type = AV_HWDEVICE_TYPE_D3D11VA;
        pix_fmt = AV_PIX_FMT_D3D11;
        hw_handle_supported = 1;
#यदि_अन्तः
    } अन्यथा यदि (MFX_IMPL_द्वारा_D3_D9 == MFX_IMPL_द्वारा_आवरणम्(s->impl)) {
#यदि CONFIG_DXVA2
        handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
        device_type = AV_HWDEVICE_TYPE_DXVA2;
        pix_fmt = AV_PIX_FMT_DXVA2_VLD;
        hw_handle_supported = 1;
#यदि_अन्तः
    }

    यदि (hw_handle_supported) {
        err = MFXVideoCORE_GetHandle(hwctx->session, handle_type, &s->handle);
        यदि (err == MFX_ERR_NONE) {
            s->handle_type       = handle_type;
            s->child_device_type = device_type;
            s->child_pix_fmt     = pix_fmt;
        }
    }
    यदि (!s->handle) {
        av_log(ctx, AV_LOG_VERBOSE, "No supported hw handle could be retrieved "
               "from the session\n");
    }
    प्रत्यागम 0;
}

स्थिर शून्य qsv_चौकटाः_uninit(AVHWFramesContext *ctx)
{
    QSVFramesContext *s = ctx->hwctx;

    यदि (s->session_download) {
        MFXVideoVPP_Close(s->session_download);
        MFXClose(s->session_download);
    }
    s->session_download = रिक्त;
    s->session_download_init = 0;

    यदि (s->session_upload) {
        MFXVideoVPP_Close(s->session_upload);
        MFXClose(s->session_upload);
    }
    s->session_upload = रिक्त;
    s->session_upload_init = 0;

#यदि HAVE_PTHREADS
    pthread_mutex_destroy(&s->session_तालकम्);
#यदि_अन्तः

    av_freep(&s->mem_ids);
#यदि QSV_HAVE_OPAQUE
    av_freep(&s->surface_ptrs);
#यदि_अन्तः
    av_freep(&s->surfaces_आन्तरिकम्);
    av_freep(&s->handle_युग्मानि_आन्तरिकम्);
    av_frame_unref(&s->realigned_upload_frame);
    av_frame_unref(&s->realigned_download_frame);
    av_बफर_unref(&s->child_चौकटाः_ref);
}

स्थिर शून्य qsv_pool_release_dummy(शून्य *opaque, uint8_t *दत्त)
{
}

स्थिर शून्य qsv_pool_release(शून्य *opaque, uint8_t *दत्त)
{
    AVHWFramesContext *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext *s = ctx->hwctx;
    QSVSurface *qsv_surface = (QSVSurface *)दत्त;
    mfxHDLPair *hdl_pair = (mfxHDLPair *)qsv_surface->mfx_surface.दत्त_2.MemId;
    AVHWFramesContext *child_चौकटाः_ctx;

    यदि (!s->child_चौकटाः_ref)
        प्रत्यागम;

    child_चौकटाः_ctx = (AVHWFramesContext*)s->child_चौकटाः_ref->दत्त;
    यदि (!child_चौकटाः_ctx->device_ctx)
        प्रत्यागम;

#यदि CONFIG_VAAPI
    यदि (child_चौकटाः_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI)
        av_freep(&hdl_pair->first);
#यदि_अन्तः

    av_freep(&hdl_pair);
    av_frame_free(&qsv_surface->child_frame);
    av_freep(&qsv_surface);
}

स्थिर AVBufferRef *qsv_fixed_pool_alloc(शून्य *opaque, size_t आकार)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;

    यदि (s->nb_surfaces_प्रयुक्तम् < hwctx->nb_surfaces) {
        s->nb_surfaces_प्रयुक्तम्++;
        प्रत्यागम av_बफर_create((uint8_t*)(s->surfaces_आन्तरिकम् + s->nb_surfaces_प्रयुक्तम् - 1),
                                परिमाण(*hwctx->surfaces), qsv_pool_release_dummy, रिक्त, 0);
    }

    प्रत्यागम रिक्त;
}

स्थिर AVBufferRef *qsv_dynamic_pool_alloc(शून्य *opaque, size_t आकार)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    QSVFramesContext       *s = ctx->hwctx;
    AVHWFramesContext *child_चौकटाः_ctx;
    QSVSurface *qsv_surface = रिक्त;
    mfxHDLPair *handle_युग्मानि_आन्तरिकम् = रिक्त;
    पूर्णाङ्क ret;

    यदि (!s->child_चौकटाः_ref)
        गच्छ fail;

    child_चौकटाः_ctx = (AVHWFramesContext*)s->child_चौकटाः_ref->दत्त;
    यदि (!child_चौकटाः_ctx->device_ctx)
        गच्छ fail;

#यदि CONFIG_DXVA2
    यदि (child_चौकटाः_ctx->device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        av_log(ctx, AV_LOG_ERROR,
               "QSV on dxva2 requires a fixed frame pool size\n");
        गच्छ fail;
    }
#यदि_अन्तः

    qsv_surface = av_calloc(1, परिमाण(*qsv_surface));
    यदि (!qsv_surface)
        गच्छ fail;

    qsv_surface->child_frame = av_frame_alloc();
    यदि (!qsv_surface->child_frame)
        गच्छ fail;

    ret = av_hwframe_get_बफर(s->child_चौकटाः_ref, qsv_surface->child_frame, 0);
    यदि (ret < 0)
        गच्छ fail;

    handle_युग्मानि_आन्तरिकम् = av_calloc(1, परिमाण(*handle_युग्मानि_आन्तरिकम्));
    यदि (!handle_युग्मानि_आन्तरिकम्)
        गच्छ fail;

    ret = qsv_init_surface(ctx, &qsv_surface->mfx_surface);
    यदि (ret < 0)
        गच्छ fail;

#यदि CONFIG_VAAPI
    यदि (child_चौकटाः_ctx->device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        VASurfaceID *surface_id_आन्तरिकम्;

        surface_id_आन्तरिकम् = av_calloc(1, परिमाण(*surface_id_आन्तरिकम्));
        यदि (!surface_id_आन्तरिकम्)
            गच्छ fail;

        *surface_id_आन्तरिकम् = (VASurfaceID)(uintptr_t)qsv_surface->child_frame->दत्त[3];
        handle_युग्मानि_आन्तरिकम्->first = (mfxHDL)surface_id_आन्तरिकम्;
        handle_युग्मानि_आन्तरिकम्->second = (mfxMemId)MFX_INFINITE;
    }
#यदि_अन्तः

#यदि CONFIG_D3D11VA
    यदि (child_चौकटाः_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_चौकटाः_hwctx = child_चौकटाः_ctx->hwctx;
        handle_युग्मानि_आन्तरिकम्->first = (mfxMemId)qsv_surface->child_frame->दत्त[0];

        यदि (child_चौकटाः_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET)
            handle_युग्मानि_आन्तरिकम्->second = (mfxMemId)MFX_INFINITE;
        अन्यथा
            handle_युग्मानि_आन्तरिकम्->second = (mfxMemId)qsv_surface->child_frame->दत्त[1];

    }
#यदि_अन्तः

    qsv_surface->mfx_surface.दत्त_2.MemId = (mfxMemId)handle_युग्मानि_आन्तरिकम्;
    प्रत्यागम av_बफर_create((uint8_t *)qsv_surface, परिमाण(*qsv_surface),
                            qsv_pool_release, ctx, 0);

fail:
    यदि (qsv_surface) {
        av_frame_free(&qsv_surface->child_frame);
    }

    av_freep(&qsv_surface);
    av_freep(&handle_युग्मानि_आन्तरिकम्);

    प्रत्यागम रिक्त;
}

स्थिर AVBufferRef *qsv_pool_alloc(शून्य *opaque, size_t आकार)
{
    AVHWFramesContext    *ctx = (AVHWFramesContext*)opaque;
    AVQSVFramesContext *hwctx = ctx->hwctx;

    यदि (hwctx->nb_surfaces == 0) {
        प्रत्यागम qsv_dynamic_pool_alloc(opaque, आकार);
    } अन्यथा {
        प्रत्यागम qsv_fixed_pool_alloc(opaque, आकार);
    }
}

स्थिर पूर्णाङ्क qsv_init_child_ctx(AVHWFramesContext *ctx)
{
    QSVDeviceContext *device_priv = ctx->device_ctx->hwctx;
    QSVFramesContext           *s = ctx->hwctx;
    AVQSVFramesContext     *hwctx = &s->p;

    AVBufferRef *child_device_ref = रिक्त;
    AVBufferRef *child_चौकटाः_ref = रिक्त;

    AVHWDeviceContext *child_device_ctx;
    AVHWFramesContext *child_चौकटाः_ctx;

    पूर्णाङ्क i, ret = 0;

    यदि (!device_priv->handle) {
        av_log(ctx, AV_LOG_ERROR,
               "Cannot create a non-opaque internal surface pool without "
               "a hardware handle\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    child_device_ref = av_hwdevice_ctx_alloc(device_priv->child_device_type);
    यदि (!child_device_ref)
        प्रत्यागम AVERROR(ENOMEM);
    child_device_ctx   = (AVHWDeviceContext*)child_device_ref->दत्त;

#यदि CONFIG_VAAPI
    यदि (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->display = (VADisplay)device_priv->handle;
    }
#यदि_अन्तः
#यदि CONFIG_D3D11VA
    यदि (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        ID3_D11_Device_सङ्कलय_Ref((ID3D11Device*)device_priv->handle);
        child_device_hwctx->device = (ID3D11Device*)device_priv->handle;
    }
#यदि_अन्तः
#यदि CONFIG_DXVA2
    यदि (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
        child_device_hwctx->devmgr = (IDirect3DDeviceManager9*)device_priv->handle;
    }
#यदि_अन्तः

    ret = av_hwdevice_ctx_init(child_device_ref);
    यदि (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child device context\n");
        गच्छ fail;
    }

    child_चौकटाः_ref = av_hwframe_ctx_alloc(child_device_ref);
    यदि (!child_चौकटाः_ref) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }
    child_चौकटाः_ctx = (AVHWFramesContext*)child_चौकटाः_ref->दत्त;

    child_चौकटाः_ctx->format            = device_priv->child_pix_fmt;
    child_चौकटाः_ctx->sw_format         = ctx->sw_format;
    child_चौकटाः_ctx->initial_pool_आकार = ctx->initial_pool_आकार;
    child_चौकटाः_ctx->विस्तारः             = FFALIGN(ctx->विस्तारः, 16);
    child_चौकटाः_ctx->height            = FFALIGN(ctx->height, 16);

#यदि CONFIG_D3D11VA
    यदि (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_चौकटाः_hwctx = child_चौकटाः_ctx->hwctx;
        यदि (hwctx->frame_type == 0)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_स्मृतिः_PROCESSOR_TARGET;
        यदि (hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
            child_चौकटाः_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
        child_चौकटाः_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(hwctx->frame_type);
    }
#यदि_अन्तः
#यदि CONFIG_DXVA2
    यदि (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_चौकटाः_Context *child_चौकटाः_hwctx = child_चौकटाः_ctx->hwctx;
        यदि (hwctx->frame_type & MFX_MEMTYPE_VIDEO_स्मृतिः_PROCESSOR_TARGET)
            child_चौकटाः_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        अन्यथा
            child_चौकटाः_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
    }
#यदि_अन्तः

    ret = av_hwframe_ctx_init(child_चौकटाः_ref);
    यदि (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing a child frames context\n");
        गच्छ fail;
    }

#यदि CONFIG_VAAPI
    यदि (child_device_ctx->type == AV_HWDEVICE_TYPE_VAAPI) {
        AVVAAPIFramesContext *child_चौकटाः_hwctx = child_चौकटाः_ctx->hwctx;
        प्रति (i = 0; i < ctx->initial_pool_आकार; i++) {
            s->handle_युग्मानि_आन्तरिकम्[i].first = child_चौकटाः_hwctx->surface_ids + i;
            s->handle_युग्मानि_आन्तरिकम्[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_आन्तरिकम्[i].दत्त_2.MemId = (mfxMemId)&s->handle_युग्मानि_आन्तरिकम्[i];
        }
        hwctx->frame_type = MFX_MEMTYPE_VIDEO_स्मृतिः_DECODER_TARGET;
    }
#यदि_अन्तः
#यदि CONFIG_D3D11VA
    यदि (child_device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        AVD3D11VAFramesContext *child_चौकटाः_hwctx = child_चौकटाः_ctx->hwctx;
        प्रति (i = 0; i < ctx->initial_pool_आकार; i++) {
            s->handle_युग्मानि_आन्तरिकम्[i].first = (mfxMemId)child_चौकटाः_hwctx->texture_infos[i].texture;
            यदि(child_चौकटाः_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                s->handle_युग्मानि_आन्तरिकम्[i].second = (mfxMemId)MFX_INFINITE;
            } अन्यथा {
                s->handle_युग्मानि_आन्तरिकम्[i].second = (mfxMemId)child_चौकटाः_hwctx->texture_infos[i].सूचकांक;
            }
            s->surfaces_आन्तरिकम्[i].दत्त_2.MemId = (mfxMemId)&s->handle_युग्मानि_आन्तरिकम्[i];
        }
        यदि (child_चौकटाः_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_स्मृतिः_PROCESSOR_TARGET;
        } अन्यथा {
            hwctx->frame_type |= MFX_MEMTYPE_VIDEO_स्मृतिः_DECODER_TARGET;
        }
    }
#यदि_अन्तः
#यदि CONFIG_DXVA2
    यदि (child_device_ctx->type == AV_HWDEVICE_TYPE_DXVA2) {
        AVDXVA2_चौकटाः_Context *child_चौकटाः_hwctx = child_चौकटाः_ctx->hwctx;
        प्रति (i = 0; i < ctx->initial_pool_आकार; i++) {
            s->handle_युग्मानि_आन्तरिकम्[i].first = (mfxMemId)child_चौकटाः_hwctx->surfaces[i];
            s->handle_युग्मानि_आन्तरिकम्[i].second = (mfxMemId)MFX_INFINITE;
            s->surfaces_आन्तरिकम्[i].दत्त_2.MemId = (mfxMemId)&s->handle_युग्मानि_आन्तरिकम्[i];
        }
        यदि (child_चौकटाः_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_स्मृतिः_PROCESSOR_TARGET;
        अन्यथा
            hwctx->frame_type = MFX_MEMTYPE_VIDEO_स्मृतिः_DECODER_TARGET;
    }
#यदि_अन्तः

    s->child_चौकटाः_ref       = child_चौकटाः_ref;
    child_चौकटाः_ref          = रिक्त;

fail:
    av_बफर_unref(&child_device_ref);
    av_बफर_unref(&child_चौकटाः_ref);
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    ध्रुव AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    यदि (!desc)
        प्रत्यागम AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    यदि (!fourcc)
        प्रत्यागम AVERROR(EINVAL);

    surf->Info.Bit_गभीरता_Luma   = desc->comp[0].गभीरता;
    surf->Info.Bit_गभीरता_Chroma = desc->comp[0].गभीरता;
    surf->Info.सरणम्_2          = qsv_सरणम्_from_pix_fmt(ctx->sw_format);

    यदि (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    अन्यथा यदि (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    अन्यथा
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.विस्तारः_2          = FFALIGN(ctx->विस्तारः, 16);
    surf->Info.CropW          = ctx->विस्तारः;
    surf->Info.Height         = FFALIGN(ctx->height, 16);
    surf->Info.CropH          = ctx->height;
    surf->Info.Frame_दरः_Ext_N  = 25;
    surf->Info.Frame_दरः_Ext_D  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क qsv_init_pool(AVHWFramesContext *ctx, uint32_t fourcc)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *चौकटाः_hwctx = &s->p;

    पूर्णाङ्क i, ret = 0;

    यदि (ctx->initial_pool_आकार < 0) {
        av_log(ctx, AV_LOG_ERROR, "Invalid frame pool size\n");
        प्रत्यागम AVERROR(EINVAL);
    } अन्यथा यदि (ctx->initial_pool_आकार == 0) {
        mfxFrameSurface1 mfx_surf1;

        ret = qsv_init_child_ctx(ctx);
        यदि (ret < 0)
            प्रत्यागम ret;

        ffhwframesctx(ctx)->pool_आन्तरिकम् = av_बफर_pool_init2(परिमाण(mfxFrameSurface1),
                                                                 ctx, qsv_pool_alloc, रिक्त);
        यदि (!ffhwframesctx(ctx)->pool_आन्तरिकम्)
            प्रत्यागम AVERROR(ENOMEM);

        स्मृतिं_पूरय(&mfx_surf1, 0, परिमाण(mfx_surf1));
        qsv_init_surface(ctx, &mfx_surf1);
        s->frame_info = mfx_surf1.Info;
        चौकटाः_hwctx->info = &s->frame_info;
        चौकटाः_hwctx->nb_surfaces = 0;

        प्रत्यागम 0;
    }

    s->handle_युग्मानि_आन्तरिकम् = av_calloc(ctx->initial_pool_आकार,
                                         परिमाण(*s->handle_युग्मानि_आन्तरिकम्));
    यदि (!s->handle_युग्मानि_आन्तरिकम्)
        प्रत्यागम AVERROR(ENOMEM);

    s->surfaces_आन्तरिकम् = av_calloc(ctx->initial_pool_आकार,
                                     परिमाण(*s->surfaces_आन्तरिकम्));
    यदि (!s->surfaces_आन्तरिकम्)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (i = 0; i < ctx->initial_pool_आकार; i++) {
        ret = qsv_init_surface(ctx, &s->surfaces_आन्तरिकम्[i]);
        यदि (ret < 0)
            प्रत्यागम ret;
    }

#यदि QSV_HAVE_OPAQUE
    यदि (!(चौकटाः_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME)) {
        ret = qsv_init_child_ctx(ctx);
        यदि (ret < 0)
            प्रत्यागम ret;
    }
#अन्यथा
    ret = qsv_init_child_ctx(ctx);
    यदि (ret < 0)
        प्रत्यागम ret;
#यदि_अन्तः

    ffhwframesctx(ctx)->pool_आन्तरिकम् = av_बफर_pool_init2(परिमाण(mfxFrameSurface1),
                                                             ctx, qsv_pool_alloc, रिक्त);
    यदि (!ffhwframesctx(ctx)->pool_आन्तरिकम्)
        प्रत्यागम AVERROR(ENOMEM);

    चौकटाः_hwctx->surfaces    = s->surfaces_आन्तरिकम्;
    चौकटाः_hwctx->nb_surfaces = ctx->initial_pool_आकार;

    प्रत्यागम 0;
}

स्थिर mfx_स्थितिः frame_alloc(mfxHDL pthis, mfxFrameAllocRequest *req,
                             mfxFrameAllocResponse *resp)
{
    AVHWFramesContext    *ctx = pthis;
    QSVFramesContext       *s = ctx->hwctx;
    AVQSVFramesContext *hwctx = &s->p;
    mfxFrameInfo *i  = &req->Info;
    mfxFrameInfo *i1 = hwctx->nb_surfaces ? &hwctx->surfaces[0].Info : hwctx->info;

    यदि (!(req->Type & MFX_MEMTYPE_VIDEO_स्मृतिः_PROCESSOR_TARGET) ||
        !(req->Type & (MFX_MEMTYPE_FROM_VPPIN | MFX_MEMTYPE_FROM_VPPOUT)) ||
        !(req->Type & MFX_MEMTYPE_EXTERNAL_FRAME))
        प्रत्यागम MFX_ERR_UNSUPPORTED;
    यदि (i->विस्तारः_2  > i1->विस्तारः_2 || i->Height > i1->Height ||
        i->FourCC != i1->FourCC || i->ChromaFormat != i1->ChromaFormat) {
        av_log(ctx, AV_LOG_ERROR, "Mismatching surface properties in an "
               "allocation request: %dx%d %d %d vs %dx%d %d %d\n",
               i->विस्तारः_2,  i->Height,  i->FourCC,  i->ChromaFormat,
               i1->विस्तारः_2, i1->Height, i1->FourCC, i1->ChromaFormat);
        प्रत्यागम MFX_ERR_UNSUPPORTED;
    }

    resp->mids           = s->mem_ids;
    resp->अङ्कः_Frame_Actual = hwctx->nb_surfaces;

    प्रत्यागम MFX_ERR_NONE;
}

स्थिर mfx_स्थितिः frame_free(mfxHDL pthis, mfxFrameAllocResponse *resp)
{
    प्रत्यागम MFX_ERR_NONE;
}

स्थिर mfx_स्थितिः frame_तालकम्(mfxHDL pthis, mfxMemId mid, mfx_Frame_दत्त *ptr)
{
    प्रत्यागम MFX_ERR_UNSUPPORTED;
}

स्थिर mfx_स्थितिः frame_unlock(mfxHDL pthis, mfxMemId mid, mfx_Frame_दत्त *ptr)
{
    प्रत्यागम MFX_ERR_UNSUPPORTED;
}

स्थिर mfx_स्थितिः frame_get_hdl(mfxHDL pthis, mfxMemId mid, mfxHDL *hdl)
{
    mfxHDLPair *pair_dst = (mfxHDLPair*)hdl;
    mfxHDLPair *pair_src = (mfxHDLPair*)mid;

    pair_dst->first = pair_src->first;

    यदि (pair_src->second != (mfxMemId)MFX_INFINITE)
        pair_dst->second = pair_src->second;
    प्रत्यागम MFX_ERR_NONE;
}

#यदि QSV_ONEVPL

स्थिर पूर्णाङ्क qsv_d3d11_update_config(शून्य *ctx, mfxHDL handle, mfxConfig cfg)
{
    पूर्णाङ्क ret = AVERROR_UNKNOWN;
#यदि CONFIG_D3D11VA
    mfx_स्थितिः sts;
    IDXGIAdapter *pDXGIAdapter;
    DXGI_ADAPTER_DESC adapterDesc;
    IDXGIDevice *pDXGIDevice = रिक्त;
    HRESULT hr;
    ID3D11Device *device = handle;
    mfxVariant impl_मानम् = {0};

    hr = ID3D11Device_QueryInterface(device, &IID_IDXGIDevice, (शून्य**)&pDXGIDevice);
    यदि (SUCCEEDED(hr)) {
        hr = IDXGIDevice_GetAdapter(pDXGIDevice, &pDXGIAdapter);
        यदि (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIDevice_GetAdapter %#lx\n", hr);
            IDXGIDevice_Release(pDXGIDevice);
            प्रत्यागम ret;
        }

        hr = IDXGIAdapter_GetDesc(pDXGIAdapter, &adapterDesc);
        यदि (FAILED(hr)) {
            av_log(ctx, AV_LOG_ERROR, "Error IDXGIAdapter_GetDesc %#lx\n", hr);
            गच्छ fail;
        }
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "Error ID3D11Device_QueryInterface %#lx\n", hr);
        प्रत्यागम ret;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_U16;
    impl_मानम्.दत्त_2.U16 = adapterDesc.DeviceId;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxExtendedDeviceId.DeviceID", impl_मानम्);
    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceID property: %d.\n", sts);
        गच्छ fail;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_PTR;
    impl_मानम्.दत्त_2.Ptr = &adapterDesc.AdapterLuid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_मानम्);
    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        गच्छ fail;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_U32;
    impl_मानम्.दत्त_2.U32 = 0x0001;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxExtendedDeviceId.LUIDDeviceNodeMask", impl_मानम्);
    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "LUIDDeviceNodeMask property: %d.\n", sts);
        गच्छ fail;
    }

    ret = 0;

fail:
    IDXGIAdapter_Release(pDXGIAdapter);
    IDXGIDevice_Release(pDXGIDevice);
#यदि_अन्तः
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क qsv_d3d9_update_config(शून्य *ctx, mfxHDL handle, mfxConfig cfg)
{
    पूर्णाङ्क ret = AVERROR_UNKNOWN;
#यदि CONFIG_DXVA2
    mfx_स्थितिः sts;
    IDirect3DDeviceManager9* devmgr = handle;
    IDirect3DDevice9 *device = रिक्त;
    IDirect3DDevice9Ex *device_ex = रिक्त;
    HANDLE device_handle = 0;
    IDirect3D9Ex *d3d9ex = रिक्त;
    IDirect3D9 *d3d9 = रिक्त;
    LUID luid;
    D3DDEVICE_CREATION_PARAMETERS params;
    HRESULT hr;
    mfxVariant impl_मानम् = {0};

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(devmgr, &device_handle);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error OpenDeviceHandle %#lx\n", hr);
        गच्छ fail;
    }

    hr = IDirect3_DDevice_Manager9_तालकम्_Device(devmgr, device_handle, &device, TRUE);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error LockDevice %#lx\n", hr);
        IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
        गच्छ fail;
    }
    hr = IDirect3DDevice9_QueryInterface(device, &IID_IDirect3DDevice9Ex, (शून्य **)&device_ex);
    IDirect3DDevice9_Release(device);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_QueryInterface %#lx\n", hr);
        गच्छ unlock;
    }

    hr = IDirect3DDevice9Ex_GetCreationParameters(device_ex, &params);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9_GetCreationParameters %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        गच्छ unlock;
    }

    hr = IDirect3DDevice9Ex_GetDirect3D(device_ex, &d3d9);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetDirect3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        गच्छ unlock;
    }
    hr = IDirect3D9_QueryInterface(d3d9, &IID_IDirect3D9Ex, (शून्य **)&d3d9ex);
    IDirect3D9_Release(d3d9);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3D9_QueryInterface3D %#lx\n", hr);
        IDirect3DDevice9Ex_Release(device_ex);
        गच्छ unlock;
    }

    hr = IDirect3D9Ex_GetAdapterLUID(d3d9ex, params.AdapterOrdinal, &luid);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error IDirect3DDevice9Ex_GetAdapterLUID %#lx\n", hr);
        गच्छ release;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_PTR;
    impl_मानम्.दत्त_2.Ptr = &luid;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxExtendedDeviceId.DeviceLUID", impl_मानम्);
    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "DeviceLUID property: %d.\n", sts);
        गच्छ release;
    }

    ret = 0;

release:
    IDirect3D9Ex_Release(d3d9ex);
    IDirect3DDevice9Ex_Release(device_ex);

unlock:
    IDirect3DDeviceManager9_UnlockDevice(devmgr, device_handle, FALSE);
    IDirect3DDeviceManager9_CloseDeviceHandle(devmgr, device_handle);
fail:
#यदि_अन्तः
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क qsv_va_update_config(शून्य *ctx, mfxHDL handle, mfxConfig cfg)
{
#यदि CONFIG_VAAPI
#यदि VA_CHECK_संस्करणम्(1, 15, 0)
    mfx_स्थितिः sts;
    VADisplay dpy = handle;
    VAStatus vas;
    VADisplayAttribute attr = {
        .type = VADisplayPCIID,
    };
    mfxVariant impl_मानम् = {0};

    vas = va_Get_Display_गुणाः(dpy, &attr, 1);
    यदि (vas == VA_स्थितिः_SUCCESS && attr.flags != VA_DISPLAY_ATTRIB_NOT_SUPPORTED) {
        impl_मानम्.Type = MFX_VARIANT_TYPE_U16;
        impl_मानम्.दत्त_2.U16 = (attr.मानम् & 0xFFFF);
        sts = MFXSetConfigFilterProperty(cfg,
                                         (ध्रुव mfxU8 *)"mfxImplDescription.mfxDeviceDescription.DeviceID", impl_मानम्);
        यदि (sts != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
                   "DeviceID property: %d.\n", sts);
            गच्छ fail;
        }
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "libva: Failed to get device id from the driver. Please "
               "consider to upgrade the driver to support VA-API 1.15.0\n");
        गच्छ fail;
    }

    प्रत्यागम 0;

fail:
#अन्यथा
    av_log(ctx, AV_LOG_ERROR, "libva: This version of libva doesn't support retrieving "
           "the device information from the driver. Please consider to upgrade libva to "
           "support VA-API 1.15.0\n");
#यदि_अन्तः
#यदि_अन्तः
    प्रत्यागम AVERROR_UNKNOWN;
}

स्थिर पूर्णाङ्क qsv_new_mfx_loader(शून्य *ctx,
                              mfxHDL handle,
                              mfxHandleType handle_type,
                              mfxIMPL implementation,
                              mfx_संस्करणम् *pver,
                              शून्य **ploader)
{
    mfx_स्थितिः sts;
    mfxLoader loader = रिक्त;
    mfxConfig cfg;
    mfxVariant impl_मानम् = {0};

    *ploader = रिक्त;
    loader = MFXLoad();
    यदि (!loader) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX loader\n");
        गच्छ fail;
    }

    /* Create configurations for implementation */
    cfg = MFXCreateConfig(loader);
    यदि (!cfg) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX configuration\n");
        गच्छ fail;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_U32;
    impl_मानम्.दत्त_2.U32 = (implementation == MFX_IMPL_SOFTWARE) ?
        MFX_IMPL_TYPE_SOFTWARE : MFX_IMPL_TYPE_HARDWARE;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxImplDescription.Impl", impl_मानम्);
    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        गच्छ fail;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_U32;
    impl_मानम्.दत्त_2.U32 = pver->संस्करणम्_2;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxImplDescription.ApiVersion.Version",
                                     impl_मानम्);
    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration "
               "property: %d.\n", sts);
        गच्छ fail;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_U32;
    impl_मानम्.दत्त_2.U32 = 0x8086; // Intel device only
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxImplDescription.VendorID", impl_मानम्);
    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "VendorID property: %d.\n", sts);
        गच्छ fail;
    }

    यदि (MFX_HANDLE_VA_DISPLAY == handle_type) {
        यदि (handle && qsv_va_update_config(ctx, handle, cfg))
            गच्छ fail;

        impl_मानम्.दत्त_2.U32 = MFX_ACCEL_बहुलकम्_द्वारा_VAAPI;
    } अन्यथा यदि (MFX_HANDLE_D3D9_DEVICE_MANAGER == handle_type) {
        यदि (handle && qsv_d3d9_update_config(ctx, handle, cfg))
            गच्छ fail;

        impl_मानम्.दत्त_2.U32 = MFX_ACCEL_बहुलकम्_द्वारा_D3_D9;
    } अन्यथा {
        यदि (handle && qsv_d3d11_update_config(ctx, handle, cfg))
            गच्छ fail;

        impl_मानम्.दत्त_2.U32 = MFX_ACCEL_बहुलकम्_द्वारा_D3_D11;
    }

    impl_मानम्.Type = MFX_VARIANT_TYPE_U32;
    sts = MFXSetConfigFilterProperty(cfg,
                                     (ध्रुव mfxU8 *)"mfxImplDescription.AccelerationMode", impl_मानम्);
    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error adding a MFX configuration"
               "AccelerationMode property: %d.\n", sts);
        गच्छ fail;
    }

    *ploader = loader;

    प्रत्यागम 0;

fail:
    यदि (loader)
        MFXUnload(loader);

    प्रत्यागम AVERROR_UNKNOWN;
}

स्थिर पूर्णाङ्क qsv_create_mfx_session_from_loader(शून्य *ctx, mfxLoader loader, mfxSession *psession)
{
    mfx_स्थितिः sts;
    mfxSession session = रिक्त;
    uint32_t impl_idx = 0;
    mfx_संस्करणम् ver;

    यावत् (1) {
        /* Enumerate all implementations */
        mfxImplDescription *impl_desc;

        sts = MFXEnumImplementations(loader, impl_idx,
                                     MFX_IMPLCAPS_IMPLDESCSTRUCTURE,
                                     (mfxHDL *)&impl_desc);
        /* Failed to find an available implementation */
        यदि (sts == MFX_ERR_NOT_प्राप्तम्)
            भङ्ग;
        अन्यथा यदि (sts != MFX_ERR_NONE) {
            impl_idx++;
            अनुवर्त;
        }

        sts = MFXCreateSession(loader, impl_idx, &session);
        MFXDispReleaseImplDescription(loader, impl_desc);
        यदि (sts == MFX_ERR_NONE)
            भङ्ग;

        impl_idx++;
    }

    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error creating a MFX session: %d.\n", sts);
        गच्छ fail;
    }

    sts = MFXQuery_संस्करणम्(session, &ver);
    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying a MFX session: %d.\n", sts);
        गच्छ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    *psession = session;

    प्रत्यागम 0;

fail:
    यदि (session)
        MFXClose(session);

    प्रत्यागम AVERROR_UNKNOWN;
}

स्थिर पूर्णाङ्क qsv_create_mfx_session(शून्य *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfx_संस्करणम् *pver,
                                  mfxSession *psession,
                                  शून्य **ploader)
{
    mfxLoader loader = रिक्त;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) oneVPL to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_संस्करणम्_MAJOR, MFX_संस्करणम्_MINOR, pver->Major, pver->Minor);

    यदि (handle_type != MFX_HANDLE_VA_DISPLAY &&
        handle_type != MFX_HANDLE_D3D9_DEVICE_MANAGER &&
        handle_type != MFX_HANDLE_D3D11_DEVICE) {
        av_log(ctx, AV_LOG_ERROR,
               "Invalid MFX device handle type\n");
        प्रत्यागम AVERROR(EXDEV);
    }

    *psession = रिक्त;

    यदि (!*ploader) {
        यदि (qsv_new_mfx_loader(ctx, handle, handle_type, implementation, pver, (शून्य **)&loader))
            गच्छ fail;

        av_assert0(loader);
    } अन्यथा
        loader = *ploader;      // Use the input mfxLoader to create mfx session

    यदि (qsv_create_mfx_session_from_loader(ctx, loader, psession))
        गच्छ fail;

    यदि (!*ploader)
        *ploader = loader;

    प्रत्यागम 0;

fail:
    यदि (!*ploader && loader)
        MFXUnload(loader);

    प्रत्यागम AVERROR_UNKNOWN;
}

#अन्यथा

स्थिर पूर्णाङ्क qsv_create_mfx_session(शून्य *ctx,
                                  mfxHDL handle,
                                  mfxHandleType handle_type,
                                  mfxIMPL implementation,
                                  mfx_संस्करणम् *pver,
                                  mfxSession *psession,
                                  शून्य **ploader)
{
    mfx_संस्करणम् ver;
    mfx_स्थितिः sts;
    mfxSession session = रिक्त;

    av_log(ctx, AV_LOG_VERBOSE,
           "Use Intel(R) Media SDK to create MFX session, API version is "
           "%d.%d, the required implementation version is %d.%d\n",
           MFX_संस्करणम्_MAJOR, MFX_संस्करणम्_MINOR, pver->Major, pver->Minor);

    *ploader = रिक्त;
    *psession = रिक्त;
    ver = *pver;
    sts = MFXInit(implementation, &ver, &session);
    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        गच्छ fail;
    }

    sts = MFXQuery_संस्करणम्(session, &ver);
    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying an MFX session: "
               "%d.\n", sts);
        गच्छ fail;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Initialize MFX session: implementation "
           "version is %d.%d\n", ver.Major, ver.Minor);

    MFXClose(session);

    sts = MFXInit(implementation, &ver, &session);
    यदि (sts != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error initializing an MFX session: "
               "%d.\n", sts);
        गच्छ fail;
    }

    *psession = session;

    प्रत्यागम 0;

fail:
    यदि (session)
        MFXClose(session);

    प्रत्यागम AVERROR_UNKNOWN;
}

#यदि_अन्तः

स्थिर पूर्णाङ्क qsv_init_आन्तरिकम्_session(AVHWFramesContext *ctx,
                                     mfxSession *session, पूर्णाङ्क upload)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *चौकटाः_hwctx = &s->p;
    QSVDeviceContext   *device_priv  = ctx->device_ctx->hwctx;
    AVQSVDeviceContext *hwctx        = &device_priv->p;
    पूर्णाङ्क opaque = 0;

    mfxFrameAllocator frame_allocator = {
        .pthis  = ctx,
        .Alloc  = frame_alloc,
        .तालकम्_2   = frame_तालकम्,
        .Unlock = frame_unlock,
        .GetHDL = frame_get_hdl,
        .Free   = frame_free,
    };

    mfxVideoParam par;
    mfx_स्थितिः err;
    पूर्णाङ्क                   ret = AVERROR_UNKNOWN;
    /* hwctx->loader is non-NULL for oneVPL user and NULL for non-oneVPL user */
    शून्य             **loader = &hwctx->loader;
    mfxSession parent_session = hwctx->session;
    mfxIMPL impl;
    mfx_संस्करणम् ver;

    err = MFXQueryIMPL(parent_session, &impl);
    यदि (err == MFX_ERR_NONE)
        err = MFXQuery_संस्करणम्(parent_session, &ver);
    यदि (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error querying the session attributes.\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

#यदि QSV_HAVE_OPAQUE
    opaque = !!(चौकटाः_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#यदि_अन्तः

    ret = qsv_create_mfx_session(ctx, device_priv->handle, device_priv->handle_type,
                                 device_priv->impl, &device_priv->ver, session, loader);
    यदि (ret)
        गच्छ fail;

    यदि (device_priv->handle) {
        err = MFXVideo_CORE_समुच्चयः_Handle(*session, device_priv->handle_type,
                                     device_priv->handle);
        यदि (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            गच्छ fail;
        }
    }

    यदि (QSV_RUNTIME_संस्करणम्_ATLEAST(ver, 1, 25)) {
        err = MFXJoinSession(parent_session, *session);
        यदि (err != MFX_ERR_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Error joining session.\n");
            ret = AVERROR_UNKNOWN;
            गच्छ fail;
        }
    }

    यदि (!opaque) {
        err = MFXVideo_CORE_समुच्चयः_Frame_Allocator(*session, &frame_allocator);
        यदि (err != MFX_ERR_NONE) {
            ret = AVERROR_UNKNOWN;
            गच्छ fail;
        }
    }

    स्मृतिं_पूरय(&par, 0, परिमाण(par));

    यदि (!opaque) {
        par.IOPattern = upload ? MFX_IOPATTERN_बहिर्गमनम्_VIDEO_स्मृतिः :
                                 MFX_IOPATTERN_अन्तर्_VIDEO_स्मृतिः;
    }
#यदि QSV_HAVE_OPAQUE
    अन्यथा {
        par.ExtParam    = s->ext_buffers;
        par.अङ्कः_Ext_Param = FF_ARRAY_ELEMS(s->ext_buffers);
        par.IOPattern   = upload ? MFX_IOPATTERN_बहिर्गमनम्_OPAQUE_स्मृतिः :
                                   MFX_IOPATTERN_अन्तर्_OPAQUE_स्मृतिः;
    }
#यदि_अन्तः

    par.IOPattern |= upload ? MFX_IOPATTERN_अन्तर्_SYSTEM_स्मृतिः :
                              MFX_IOPATTERN_बहिर्गमनम्_SYSTEM_स्मृतिः;
    par.Async_गभीरता = 1;

    par.vpp.अन्तर्_2 = चौकटाः_hwctx->nb_surfaces ? चौकटाः_hwctx->surfaces[0].Info : *चौकटाः_hwctx->info;

    /* Apparently VPP requires the frame rate to be set to some value, otherwise
     * init will fail (probably for the framerate conversion filter). Since we
     * are only doing data upload/download here, we just invent an arbitrary
     * value */
    par.vpp.अन्तर्_2.Frame_दरः_Ext_N = 25;
    par.vpp.अन्तर्_2.Frame_दरः_Ext_D = 1;
    par.vpp.बहिर्गमनम्_2 = par.vpp.अन्तर्_2;

    err = MFXVideoVPP_Init(*session, &par);
    यदि (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_VERBOSE, "Error opening the internal VPP session."
               "Surface upload/download will not be possible\n");

        ret = AVERROR_UNKNOWN;
        गच्छ fail;
    }

    प्रत्यागम 0;

fail:
    यदि (*session)
        MFXClose(*session);

    *session = रिक्त;

    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क qsv_चौकटाः_init(AVHWFramesContext *ctx)
{
    QSVFramesContext              *s = ctx->hwctx;
    AVQSVFramesContext *चौकटाः_hwctx = &s->p;

    पूर्णाङ्क opaque = 0;

    uint32_t fourcc;
    पूर्णाङ्क i, ret;

#यदि QSV_HAVE_OPAQUE
    opaque = !!(चौकटाः_hwctx->frame_type & MFX_MEMTYPE_OPAQUE_FRAME);
#यदि_अन्तः

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    यदि (!fourcc) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format\n");
        प्रत्यागम AVERROR(ENOSYS);
    }

    यदि (!ctx->pool) {
        ret = qsv_init_pool(ctx, fourcc);
        यदि (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            प्रत्यागम ret;
        }
    }

    यदि (!opaque) {
        s->mem_ids = av_calloc(चौकटाः_hwctx->nb_surfaces, परिमाण(*s->mem_ids));
        यदि (!s->mem_ids)
            प्रत्यागम AVERROR(ENOMEM);

        प्रति (i = 0; i < चौकटाः_hwctx->nb_surfaces; i++)
            s->mem_ids[i] = चौकटाः_hwctx->surfaces[i].दत्त_2.MemId;
    }
#यदि QSV_HAVE_OPAQUE
    अन्यथा {
        s->surface_ptrs = av_calloc(चौकटाः_hwctx->nb_surfaces,
                                    परिमाण(*s->surface_ptrs));
        यदि (!s->surface_ptrs)
            प्रत्यागम AVERROR(ENOMEM);

        प्रति (i = 0; i < चौकटाः_hwctx->nb_surfaces; i++)
            s->surface_ptrs[i] = चौकटाः_hwctx->surfaces + i;

        s->opaque_alloc.अन्तर्_2.Surfaces   = s->surface_ptrs;
        s->opaque_alloc.अन्तर्_2.अङ्कः_Surface = चौकटाः_hwctx->nb_surfaces;
        s->opaque_alloc.अन्तर्_2.Type       = चौकटाः_hwctx->frame_type;

        s->opaque_alloc.बहिर्गमनम्_2 = s->opaque_alloc.अन्तर्_2;

        s->opaque_alloc.शीर्षकम्_2.बफर_Id = MFX_EXTBUFF_OPAQUE_SURFACE_आवण्टनम्;
        s->opaque_alloc.शीर्षकम्_2.बफर_Sz = परिमाण(s->opaque_alloc);

        s->ext_buffers[0] = (mfx_Ext_बफर*)&s->opaque_alloc;
    }
#यदि_अन्तः

    s->session_download = रिक्त;
    s->session_upload   = रिक्त;

    s->session_download_init = 0;
    s->session_upload_init   = 0;

#यदि HAVE_PTHREADS
    pthread_mutex_init(&s->session_तालकम्, रिक्त);
#यदि_अन्तः

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क qsv_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    यदि (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    frame->दत्त[3] = frame->buf[0]->दत्त;
    frame->format  = AV_PIX_FMT_QSV;
    frame->विस्तारः   = ctx->विस्तारः;
    frame->height  = ctx->height;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क qsv_transfer_get_formats(AVHWFramesContext *ctx,
                                    गणना AVHWFrameTransferDirection dir,
                                    गणना AVPixelFormat **formats)
{
    गणना AVPixelFormat *fmts;

    fmts = av_malloc_array(2, परिमाण(*fmts));
    यदि (!fmts)
        प्रत्यागम AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    *formats = fmts;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क qsv_चौकटाः_derive_from(AVHWFramesContext *dst_ctx,
                                  AVHWFramesContext *src_ctx, पूर्णाङ्क flags)
{
    AVQSVFramesContext *src_hwctx = src_ctx->hwctx;
    पूर्णाङ्क i;

    विकल्प (dst_ctx->device_ctx->type) {
#यदि CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surface_ids = av_calloc(src_hwctx->nb_surfaces,
                                               परिमाण(*dst_hwctx->surface_ids));
            यदि (!dst_hwctx->surface_ids)
                प्रत्यागम AVERROR(ENOMEM);
            प्रति (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].दत्त_2.MemId;
                dst_hwctx->surface_ids[i] = *(VASurfaceID*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
        }
        भङ्ग;
#यदि_अन्तः
#यदि CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        {
            D3D11_TEXTURE2D_DESC texDesc;
            AVD3D11VAFramesContext *dst_hwctx;
            dst_ctx->initial_pool_आकार = src_ctx->initial_pool_आकार;
            dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->texture_infos = av_calloc(src_hwctx->nb_surfaces,
                                                 परिमाण(*dst_hwctx->texture_infos));
            यदि (!dst_hwctx->texture_infos)
                प्रत्यागम AVERROR(ENOMEM);
            यदि (src_hwctx->frame_type & MFX_MEMTYPE_SHARED_RESOURCE)
                dst_hwctx->MiscFlags = D3D11_RESOURCE_MISC_SHARED;
            प्रति (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].दत्त_2.MemId;
                dst_hwctx->texture_infos[i].texture = (ID3D11Texture2D*)pair->first;
                dst_hwctx->texture_infos[i].सूचकांक = pair->second == (mfxMemId)MFX_INFINITE ? (intptr_t)0 : (intptr_t)pair->second;
            }
            यदि (src_hwctx->nb_surfaces) {
                ID3D11Texture2D_GetDesc(dst_hwctx->texture_infos[0].texture, &texDesc);
                dst_hwctx->BindFlags = texDesc.BindFlags;
            } अन्यथा
                dst_hwctx->BindFlags = qsv_get_d3d11va_bind_flags(src_hwctx->frame_type);
        }
        भङ्ग;
#यदि_अन्तः
#यदि CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_चौकटाः_Context *dst_hwctx = dst_ctx->hwctx;
            dst_hwctx->surfaces = av_calloc(src_hwctx->nb_surfaces,
                                            परिमाण(*dst_hwctx->surfaces));
            यदि (!dst_hwctx->surfaces)
                प्रत्यागम AVERROR(ENOMEM);
            प्रति (i = 0; i < src_hwctx->nb_surfaces; i++) {
                mfxHDLPair *pair = (mfxHDLPair*)src_hwctx->surfaces[i].दत्त_2.MemId;
                dst_hwctx->surfaces[i] = (IDirect3DSurface9*)pair->first;
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            यदि (src_hwctx->frame_type == MFX_MEMTYPE_VIDEO_स्मृतिः_DECODER_TARGET)
                dst_hwctx->surface_type = DXVA2_VideoDecoderRenderTarget;
            अन्यथा
                dst_hwctx->surface_type = DXVA2_VideoProcessorRenderTarget;
        }
        भङ्ग;
#यदि_अन्तः
    स्वभाव:
        प्रत्यागम AVERROR(ENOSYS);
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क qsv_map_from(AVHWFramesContext *ctx,
                        AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    QSVFramesContext *s = ctx->hwctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)src->दत्त[3];
    AVHWFramesContext *child_चौकटाः_ctx;
    ध्रुव AVPixFmtDescriptor *desc;
    uint8_t *child_दत्त;
    AVFrame *dummy;
    पूर्णाङ्क ret = 0;

    यदि (!s->child_चौकटाः_ref)
        प्रत्यागम AVERROR(ENOSYS);
    child_चौकटाः_ctx = (AVHWFramesContext*)s->child_चौकटाः_ref->दत्त;

    विकल्प (child_चौकटाः_ctx->device_ctx->type) {
#यदि CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->दत्त_2.MemId;
        /* pair->first is *VASurfaceID while data[3] in vaapi frame is VASurfaceID, so
         * we need this casting for vaapi.
         * Add intptr_t to force cast from VASurfaceID(uint) type to pointer(long) type
         * to avoid compile warning */
        child_दत्त = (uint8_t*)(intptr_t)*(VASurfaceID*)pair->first;
        भङ्ग;
    }
#यदि_अन्तः
#यदि CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->दत्त_2.MemId;
        child_दत्त = pair->first;
        भङ्ग;
    }
#यदि_अन्तः
#यदि CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
    {
        mfxHDLPair *pair = (mfxHDLPair*)surf->दत्त_2.MemId;
        child_दत्त = pair->first;
        भङ्ग;
    }
#यदि_अन्तः
    स्वभाव:
        प्रत्यागम AVERROR(ENOSYS);
    }

    यदि (dst->format == child_चौकटाः_ctx->format) {
        ret = ff_hwframe_map_create(s->child_चौकटाः_ref,
                                    dst, src, रिक्त, रिक्त);
        यदि (ret < 0)
            प्रत्यागम ret;

        dst->विस्तारः   = src->विस्तारः;
        dst->height  = src->height;

       यदि (child_चौकटाः_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
            mfxHDLPair *pair = (mfxHDLPair*)surf->दत्त_2.MemId;
            dst->दत्त[0] = pair->first;
            dst->दत्त[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
        } अन्यथा {
            dst->दत्त[3] = child_दत्त;
        }

        प्रत्यागम 0;
    }

    desc = av_pix_fmt_desc_get(dst->format);
    यदि (desc && desc->flags & AV_PIX_FMT_FLAG_HWACCEL) {
        // This only supports mapping to software.
        प्रत्यागम AVERROR(ENOSYS);
    }

    dummy = av_frame_alloc();
    यदि (!dummy)
        प्रत्यागम AVERROR(ENOMEM);

    dummy->buf[0]        = av_बफर_ref(src->buf[0]);
    dummy->hw_चौकटाः_ctx = av_बफर_ref(s->child_चौकटाः_ref);
    यदि (!dummy->buf[0] || !dummy->hw_चौकटाः_ctx)
        गच्छ fail;

    dummy->format        = child_चौकटाः_ctx->format;
    dummy->विस्तारः         = src->विस्तारः;
    dummy->height        = src->height;

    यदि (child_चौकटाः_ctx->device_ctx->type == AV_HWDEVICE_TYPE_D3D11VA) {
        mfxHDLPair *pair = (mfxHDLPair*)surf->दत्त_2.MemId;
        dummy->दत्त[0] = pair->first;
        dummy->दत्त[1] = pair->second == (mfxMemId)MFX_INFINITE ? (uint8_t *)0 : pair->second;
    } अन्यथा {
        dummy->दत्त[3] = child_दत्त;
    }

    ret = av_hwframe_map(dst, dummy, flags);

fail:
    av_frame_free(&dummy);

    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क qsv_transfer_दत्त_child(AVHWFramesContext *ctx, AVFrame *dst,
                                   ध्रुव AVFrame *src)
{
    QSVFramesContext *s = ctx->hwctx;
    AVHWFramesContext *child_चौकटाः_ctx = (AVHWFramesContext*)s->child_चौकटाः_ref->दत्त;
    पूर्णाङ्क download = !!src->hw_चौकटाः_ctx;
    mfxFrameSurface1 *surf = (mfxFrameSurface1*)(download ? src->दत्त[3] : dst->दत्त[3]);

    AVFrame *dummy;
    पूर्णाङ्क ret;

    dummy = av_frame_alloc();
    यदि (!dummy)
        प्रत्यागम AVERROR(ENOMEM);

    dummy->format        = child_चौकटाः_ctx->format;
    dummy->विस्तारः         = src->विस्तारः;
    dummy->height        = src->height;
    dummy->buf[0]        = download ? src->buf[0] : dst->buf[0];
    dummy->दत्त[3]       = surf->दत्त_2.MemId;
    dummy->hw_चौकटाः_ctx = s->child_चौकटाः_ref;

    ret = download ? av_hwframe_transfer_दत्त(dst, dummy, 0) :
                     av_hwframe_transfer_दत्त(dummy, src, 0);

    dummy->buf[0]        = रिक्त;
    dummy->दत्त[3]       = रिक्त;
    dummy->hw_चौकटाः_ctx = रिक्त;

    av_frame_free(&dummy);

    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क map_frame_गन्तव्यम्_surface(ध्रुव AVFrame *frame, mfxFrameSurface1 *surface)
{
    विकल्प (frame->format) {
    पक्ष AV_PIX_FMT_NV12:
    पक्ष AV_PIX_FMT_P010:
    पक्ष AV_PIX_FMT_P012:
        surface->दत्त_2.Y  = frame->दत्त[0];
        surface->दत्त_2.UV = frame->दत्त[1];
        भङ्ग;

    पक्ष AV_PIX_FMT_YUV420P:
        surface->दत्त_2.Y = frame->दत्त[0];
        surface->दत्त_2.U = frame->दत्त[1];
        surface->दत्त_2.V = frame->दत्त[2];
        भङ्ग;

    पक्ष AV_PIX_FMT_BGRA:
        surface->दत्त_2.B = frame->दत्त[0];
        surface->दत्त_2.G = frame->दत्त[0] + 1;
        surface->दत्त_2.R = frame->दत्त[0] + 2;
        surface->दत्त_2.A = frame->दत्त[0] + 3;
        भङ्ग;
    पक्ष AV_PIX_FMT_YUYV422:
        surface->दत्त_2.Y = frame->दत्त[0];
        surface->दत्त_2.U = frame->दत्त[0] + 1;
        surface->दत्त_2.V = frame->दत्त[0] + 3;
        भङ्ग;

    पक्ष AV_PIX_FMT_Y210:
    पक्ष AV_PIX_FMT_Y212:
        surface->दत्त_2.Y16 = (mfxU16 *)frame->दत्त[0];
        surface->दत्त_2.U16 = (mfxU16 *)frame->दत्त[0] + 1;
        surface->दत्त_2.V16 = (mfxU16 *)frame->दत्त[0] + 3;
        भङ्ग;
    पक्ष AV_PIX_FMT_VUYX:
        surface->दत्त_2.V = frame->दत्त[0];
        surface->दत्त_2.U = frame->दत्त[0] + 1;
        surface->दत्त_2.Y = frame->दत्त[0] + 2;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->दत्त_2.A = frame->दत्त[0] + 3;
        भङ्ग;
    पक्ष AV_PIX_FMT_XV30:
        surface->दत्त_2.U = frame->दत्त[0];
        भङ्ग;
    पक्ष AV_PIX_FMT_XV36:
        surface->दत्त_2.U = frame->दत्त[0];
        surface->दत्त_2.Y = frame->दत्त[0] + 2;
        surface->दत्त_2.V = frame->दत्त[0] + 4;
        // Only set Data.A to a valid address, the SDK doesn't
        // use the value from the frame.
        surface->दत्त_2.A = frame->दत्त[0] + 6;
        भङ्ग;
#यदि CONFIG_VAAPI
    पक्ष AV_PIX_FMT_UYVY422:
        surface->दत्त_2.Y = frame->दत्त[0] + 1;
        surface->दत्त_2.U = frame->दत्त[0];
        surface->दत्त_2.V = frame->दत्त[0] + 2;
        भङ्ग;
#यदि_अन्तः
    स्वभाव:
        प्रत्यागम MFX_ERR_UNSUPPORTED;
    }
    surface->दत्त_2.Pitch     = frame->linesize[0];
    surface->दत्त_2.TimeStamp = frame->pts;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क qsv_आन्तरिकम्_session_check_init(AVHWFramesContext *ctx, पूर्णाङ्क upload)
{
    QSVFramesContext *s = ctx->hwctx;
    atomic_int *inited  = upload ? &s->session_upload_init : &s->session_download_init;
    mfxSession *session = upload ? &s->session_upload      : &s->session_download;
    पूर्णाङ्क ret = 0;

    यदि (atomic_load(inited))
        प्रत्यागम 0;

#यदि HAVE_PTHREADS
    pthread_mutex_तालकम्(&s->session_तालकम्);
#यदि_अन्तः

    यदि (!atomic_load(inited)) {
        ret = qsv_init_आन्तरिकम्_session(ctx, session, upload);
        atomic_store(inited, 1);
    }

#यदि HAVE_PTHREADS
    pthread_mutex_unlock(&s->session_तालकम्);
#यदि_अन्तः

    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क qsv_transfer_दत्त_from(AVHWFramesContext *ctx, AVFrame *dst,
                                  ध्रुव AVFrame *src)
{
    QSVFramesContext  *s = ctx->hwctx;
    mfxFrameSurface1 बहिर्गमनम् = {{ 0 }};
    mfxFrameSurface1 *अन्तर् = (mfxFrameSurface1*)src->दत्त[3];

    mfxSyncPoint sync = रिक्त;
    mfx_स्थितिः err;
    पूर्णाङ्क ret = 0;
    /* download to temp frame if the output is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_download_frame;
    AVFrame *dst_frame;
    पूर्णाङ्क realigned = 0;

    ret = qsv_आन्तरिकम्_session_check_init(ctx, 0);
    यदि (ret < 0)
        प्रत्यागम ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before downloading. */
    यदि (dst->height & 15 || dst->linesize[0] & 15) {
        realigned = 1;
        यदि (tmp_frame->format != dst->format ||
            tmp_frame->विस्तारः  != FFALIGN(dst->linesize[0], 16) ||
            tmp_frame->height != FFALIGN(dst->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = dst->format;
            tmp_frame->विस्तारः  = FFALIGN(dst->linesize[0], 16);
            tmp_frame->height = FFALIGN(dst->height, 16);
            ret = av_frame_get_बफर(tmp_frame, 0);
            यदि (ret < 0)
                प्रत्यागम ret;
        }
    }

    dst_frame = realigned ? tmp_frame : dst;

    यदि (!s->session_download) {
        यदि (s->child_चौकटाः_ref)
            प्रत्यागम qsv_transfer_दत्त_child(ctx, dst_frame, src);

        av_log(ctx, AV_LOG_ERROR, "Surface download not possible\n");
        प्रत्यागम AVERROR(ENOSYS);
    }

    बहिर्गमनम्.Info = अन्तर्->Info;
    map_frame_गन्तव्यम्_surface(dst_frame, &बहिर्गमनम्);

    कुरु {
        err = MFXVideo_VPP_सततम्_Frame_VPPAsync(s->session_download, अन्तर्, &बहिर्गमनम्, रिक्त, &sync);
        यदि (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } यावत् (err == MFX_WRN_DEVICE_BUSY);

    यदि (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error downloading the surface\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    कुरु {
        err = MFXVideoCORE_SyncOperation(s->session_download, sync, 1000);
    } यावत् (err == MFX_WRN_अन्तर्_EXECUTION);
    यदि (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation: %d\n", err);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    यदि (realigned) {
        tmp_frame->विस्तारः  = dst->विस्तारः;
        tmp_frame->height = dst->height;
        ret = av_frame_copy(dst, tmp_frame);
        tmp_frame->विस्तारः  = FFALIGN(dst->linesize[0], 16);
        tmp_frame->height = FFALIGN(dst->height, 16);
        यदि (ret < 0)
            प्रत्यागम ret;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क qsv_transfer_दत्त_गन्तव्यम्(AVHWFramesContext *ctx, AVFrame *dst,
                                ध्रुव AVFrame *src)
{
    QSVFramesContext   *s = ctx->hwctx;
    mfxFrameSurface1   अन्तर् = {{ 0 }};
    mfxFrameSurface1 *बहिर्गमनम् = (mfxFrameSurface1*)dst->दत्त[3];
    mfxFrameInfo tmp_info;

    mfxSyncPoint sync = रिक्त;
    mfx_स्थितिः err;
    पूर्णाङ्क ret = 0;
    /* make a copy if the input is not padded as libmfx requires */
    AVFrame *tmp_frame = &s->realigned_upload_frame;
    ध्रुव AVFrame *src_frame;
    पूर्णाङ्क realigned = 0;

    ret = qsv_आन्तरिकम्_session_check_init(ctx, 1);
    यदि (ret < 0)
        प्रत्यागम ret;

    /* According to MSDK spec for mfxframeinfo, "Width must be a multiple of 16.
     * Height must be a multiple of 16 for progressive frame sequence and a
     * multiple of 32 otherwise.", so align all frames to 16 before uploading. */
    यदि (src->height & 15 || src->linesize[0] & 15) {
        realigned = 1;
        यदि (tmp_frame->format != src->format ||
            tmp_frame->विस्तारः  != FFALIGN(src->विस्तारः, 16) ||
            tmp_frame->height != FFALIGN(src->height, 16)) {
            av_frame_unref(tmp_frame);

            tmp_frame->format = src->format;
            tmp_frame->विस्तारः  = FFALIGN(src->विस्तारः, 16);
            tmp_frame->height = FFALIGN(src->height, 16);
            ret = av_frame_get_बफर(tmp_frame, 0);
            यदि (ret < 0)
                प्रत्यागम ret;
        }
        ret = av_frame_copy(tmp_frame, src);
        यदि (ret < 0) {
            av_frame_unref(tmp_frame);
            प्रत्यागम ret;
        }
        ret = qsv_fill_border(tmp_frame, src);
        यदि (ret < 0) {
            av_frame_unref(tmp_frame);
            प्रत्यागम ret;
        }

        tmp_info = बहिर्गमनम्->Info;
        बहिर्गमनम्->Info.CropW = FFMIN(बहिर्गमनम्->Info.विस्तारः_2,  tmp_frame->विस्तारः);
        बहिर्गमनम्->Info.CropH = FFMIN(बहिर्गमनम्->Info.Height, tmp_frame->height);
    }

    src_frame = realigned ? tmp_frame : src;

    यदि (!s->session_upload) {
        यदि (s->child_चौकटाः_ref)
            प्रत्यागम qsv_transfer_दत्त_child(ctx, dst, src_frame);

        av_log(ctx, AV_LOG_ERROR, "Surface upload not possible\n");
        प्रत्यागम AVERROR(ENOSYS);
    }

    अन्तर्.Info = बहिर्गमनम्->Info;
    map_frame_गन्तव्यम्_surface(src_frame, &अन्तर्);

    कुरु {
        err = MFXVideo_VPP_सततम्_Frame_VPPAsync(s->session_upload, &अन्तर्, बहिर्गमनम्, रिक्त, &sync);
        यदि (err == MFX_WRN_DEVICE_BUSY)
            av_usleep(1);
    } यावत् (err == MFX_WRN_DEVICE_BUSY);

    यदि (err < 0 || !sync) {
        av_log(ctx, AV_LOG_ERROR, "Error uploading the surface\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    कुरु {
        err = MFXVideoCORE_SyncOperation(s->session_upload, sync, 1000);
    } यावत् (err == MFX_WRN_अन्तर्_EXECUTION);
    यदि (err < 0) {
        av_log(ctx, AV_LOG_ERROR, "Error synchronizing the operation\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    यदि (realigned) {
        बहिर्गमनम्->Info.CropW = tmp_info.CropW;
        बहिर्गमनम्->Info.CropH = tmp_info.CropH;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क qsv_dynamic_चौकटाः_derive_गन्तव्यम्(AVHWFramesContext *dst_ctx,
                                        AVHWFramesContext *src_ctx, पूर्णाङ्क flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    mfxFrameSurface1 mfx_surf1;

    विकल्प (src_ctx->device_ctx->type) {
#यदि CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_स्मृतिः_DECODER_TARGET;
        भङ्ग;
#यदि_अन्तः

#यदि CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
    {
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        यदि (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_स्मृतिः_PROCESSOR_TARGET;
        } अन्यथा {
            dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_स्मृतिः_DECODER_TARGET;
        }
    }
    भङ्ग;
#यदि_अन्तः

    स्वभाव:
        प्रत्यागम AVERROR(ENOSYS);
    }

    स्मृतिं_पूरय(&mfx_surf1, 0, परिमाण(mfx_surf1));
    qsv_init_surface(dst_ctx, &mfx_surf1);
    s->frame_info = mfx_surf1.Info;
    dst_hwctx->info = &s->frame_info;
    dst_hwctx->nb_surfaces = 0;
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क qsv_fixed_चौकटाः_derive_गन्तव्यम्(AVHWFramesContext *dst_ctx,
                                      AVHWFramesContext *src_ctx, पूर्णाङ्क flags)
{
    QSVFramesContext *s = dst_ctx->hwctx;
    AVQSVFramesContext *dst_hwctx = &s->p;
    पूर्णाङ्क i;

    विकल्प (src_ctx->device_ctx->type) {
#यदि CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_युग्मानि_आन्तरिकम् = av_calloc(src_ctx->initial_pool_आकार,
                                                 परिमाण(*s->handle_युग्मानि_आन्तरिकम्));
            यदि (!s->handle_युग्मानि_आन्तरिकम्)
                प्रत्यागम AVERROR(ENOMEM);
            s->surfaces_आन्तरिकम् = av_calloc(src_hwctx->nb_surfaces,
                                             परिमाण(*s->surfaces_आन्तरिकम्));
            यदि (!s->surfaces_आन्तरिकम्)
                प्रत्यागम AVERROR(ENOMEM);
            प्रति (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_आन्तरिकम्[i]);
                s->handle_युग्मानि_आन्तरिकम्[i].first = src_hwctx->surface_ids + i;
                s->handle_युग्मानि_आन्तरिकम्[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_आन्तरिकम्[i].दत्त_2.MemId = (mfxMemId)&s->handle_युग्मानि_आन्तरिकम्[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            dst_hwctx->frame_type  = MFX_MEMTYPE_VIDEO_स्मृतिः_DECODER_TARGET;
        }
        भङ्ग;
#यदि_अन्तः
#यदि CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;
            s->handle_युग्मानि_आन्तरिकम् = av_calloc(src_ctx->initial_pool_आकार,
                                                 परिमाण(*s->handle_युग्मानि_आन्तरिकम्));
            यदि (!s->handle_युग्मानि_आन्तरिकम्)
                प्रत्यागम AVERROR(ENOMEM);
            s->surfaces_आन्तरिकम् = av_calloc(src_ctx->initial_pool_आकार,
                                             परिमाण(*s->surfaces_आन्तरिकम्));
            यदि (!s->surfaces_आन्तरिकम्)
                प्रत्यागम AVERROR(ENOMEM);
            प्रति (i = 0; i < src_ctx->initial_pool_आकार; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_आन्तरिकम्[i]);
                s->handle_युग्मानि_आन्तरिकम्[i].first = (mfxMemId)src_hwctx->texture_infos[i].texture;
                यदि (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                    s->handle_युग्मानि_आन्तरिकम्[i].second = (mfxMemId)MFX_INFINITE;
                } अन्यथा {
                    s->handle_युग्मानि_आन्तरिकम्[i].second = (mfxMemId)src_hwctx->texture_infos[i].सूचकांक;
                }
                s->surfaces_आन्तरिकम्[i].दत्त_2.MemId = (mfxMemId)&s->handle_युग्मानि_आन्तरिकम्[i];
            }
            dst_hwctx->nb_surfaces = src_ctx->initial_pool_आकार;
            यदि (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_स्मृतिः_PROCESSOR_TARGET;
            } अन्यथा {
                dst_hwctx->frame_type |= MFX_MEMTYPE_VIDEO_स्मृतिः_DECODER_TARGET;
            }
        }
        भङ्ग;
#यदि_अन्तः
#यदि CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2_चौकटाः_Context *src_hwctx = src_ctx->hwctx;
            s->handle_युग्मानि_आन्तरिकम् = av_calloc(src_ctx->initial_pool_आकार,
                                                 परिमाण(*s->handle_युग्मानि_आन्तरिकम्));
            यदि (!s->handle_युग्मानि_आन्तरिकम्)
                प्रत्यागम AVERROR(ENOMEM);
            s->surfaces_आन्तरिकम् = av_calloc(src_hwctx->nb_surfaces,
                                             परिमाण(*s->surfaces_आन्तरिकम्));
            यदि (!s->surfaces_आन्तरिकम्)
                प्रत्यागम AVERROR(ENOMEM);
            प्रति (i = 0; i < src_hwctx->nb_surfaces; i++) {
                qsv_init_surface(dst_ctx, &s->surfaces_आन्तरिकम्[i]);
                s->handle_युग्मानि_आन्तरिकम्[i].first = (mfxMemId)src_hwctx->surfaces[i];
                s->handle_युग्मानि_आन्तरिकम्[i].second = (mfxMemId)MFX_INFINITE;
                s->surfaces_आन्तरिकम्[i].दत्त_2.MemId = (mfxMemId)&s->handle_युग्मानि_आन्तरिकम्[i];
            }
            dst_hwctx->nb_surfaces = src_hwctx->nb_surfaces;
            यदि (src_hwctx->surface_type == DXVA2_VideoProcessorRenderTarget)
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_स्मृतिः_PROCESSOR_TARGET;
            अन्यथा
                dst_hwctx->frame_type = MFX_MEMTYPE_VIDEO_स्मृतिः_DECODER_TARGET;
        }
        भङ्ग;
#यदि_अन्तः
    स्वभाव:
        प्रत्यागम AVERROR(ENOSYS);
    }

    dst_hwctx->surfaces = s->surfaces_आन्तरिकम्;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क qsv_चौकटाः_derive_गन्तव्यम्(AVHWFramesContext *dst_ctx,
                                AVHWFramesContext *src_ctx, पूर्णाङ्क flags)
{
    यदि (src_ctx->initial_pool_आकार < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Invalid src frame pool. \n");
        प्रत्यागम AVERROR(EINVAL);
    } अन्यथा यदि (src_ctx->initial_pool_आकार == 0) {
        प्रत्यागम qsv_dynamic_चौकटाः_derive_गन्तव्यम्(dst_ctx, src_ctx, flags);
    } अन्यथा {
        प्रत्यागम qsv_fixed_चौकटाः_derive_गन्तव्यम्(dst_ctx, src_ctx, flags);
    }
}

स्थिर पूर्णाङ्क qsv_fixed_pool_map_गन्तव्यम्(AVHWFramesContext *dst_ctx,
                                 AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;
    पूर्णाङ्क i, err, सूचकांक = -1;

    प्रति (i = 0; i < hwctx->nb_surfaces && सूचकांक < 0; i++) {
        विकल्प(src->format) {
#यदि CONFIG_VAAPI
        पक्ष AV_PIX_FMT_VAAPI:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].दत्त_2.MemId;
            यदि (*(VASurfaceID*)pair->first == (VASurfaceID)(uintptr_t)src->दत्त[3])
                सूचकांक = i;
            भङ्ग;
        }
#यदि_अन्तः
#यदि CONFIG_D3D11VA
        पक्ष AV_PIX_FMT_D3D11:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].दत्त_2.MemId;
            यदि (pair->first == src->दत्त[0]
                && (pair->second == src->दत्त[1]
                    || (pair->second == (mfxMemId)MFX_INFINITE && src->दत्त[1] == (uint8_t *)0)))
                सूचकांक = i;
            भङ्ग;
        }
#यदि_अन्तः
#यदि CONFIG_DXVA2
        पक्ष AV_PIX_FMT_DXVA2_VLD:
        {
            mfxHDLPair *pair = (mfxHDLPair*)hwctx->surfaces[i].दत्त_2.MemId;
            यदि (pair->first == src->दत्त[3])
                सूचकांक = i;
            भङ्ग;
        }
#यदि_अन्तः
        }
    }
    यदि (सूचकांक < 0) {
        av_log(dst_ctx, AV_LOG_ERROR, "Trying to map from a surface which "
               "is not in the mapped frames context.\n");
        प्रत्यागम AVERROR(EINVAL);
    }

    err = ff_hwframe_map_create(dst->hw_चौकटाः_ctx,
                                dst, src, रिक्त, रिक्त);
    यदि (err)
        प्रत्यागम err;

    dst->विस्तारः   = src->विस्तारः;
    dst->height  = src->height;
    dst->दत्त[3] = (uint8_t*)&hwctx->surfaces[सूचकांक];

    प्रत्यागम 0;
}

स्थिर शून्य qsv_dynamic_pool_unmap(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    mfxFrameSurface1 *surfaces_आन्तरिकम् = (mfxFrameSurface1 *)hwmap->priv;
    mfxHDLPair *handle_युग्मानि_आन्तरिकम् = (mfxHDLPair *)surfaces_आन्तरिकम्->दत्त_2.MemId;
    AVHWFramesContext *src_ctx = (AVHWFramesContext *)ffhwframesctx(ctx)->source_चौकटाः->दत्त;

    विकल्प (src_ctx->format) {
#यदि CONFIG_VAAPI
    पक्ष AV_PIX_FMT_VAAPI:
    {
        av_freep(&handle_युग्मानि_आन्तरिकम्->first);

        भङ्ग;
    }
#यदि_अन्तः

#यदि CONFIG_D3D11VA
    पक्ष AV_PIX_FMT_D3D11:
    {
        /* Do nothing */
        भङ्ग;
    }
#यदि_अन्तः
    स्वभाव:
        av_log(ctx, AV_LOG_ERROR, "Should not reach here. \n");
        भङ्ग;
    }

    av_freep(&handle_युग्मानि_आन्तरिकम्);
    av_freep(&surfaces_आन्तरिकम्);
}

स्थिर पूर्णाङ्क qsv_dynamic_pool_map_गन्तव्यम्(AVHWFramesContext *dst_ctx,
                                   AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    mfxFrameSurface1 *surfaces_आन्तरिकम् = रिक्त;
    mfxHDLPair *handle_युग्मानि_आन्तरिकम् = रिक्त;
    पूर्णाङ्क ret = 0;

    surfaces_आन्तरिकम् = av_calloc(1, परिमाण(*surfaces_आन्तरिकम्));
    यदि (!surfaces_आन्तरिकम्) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    handle_युग्मानि_आन्तरिकम् = av_calloc(1, परिमाण(*handle_युग्मानि_आन्तरिकम्));
    यदि (!handle_युग्मानि_आन्तरिकम्) {
        ret = AVERROR(ENOMEM);
        गच्छ fail;
    }

    ret = qsv_init_surface(dst_ctx, surfaces_आन्तरिकम्);
    यदि (ret < 0)
        गच्छ fail;

    विकल्प (src->format) {
#यदि CONFIG_VAAPI
    पक्ष AV_PIX_FMT_VAAPI:
    {
        VASurfaceID *surface_id_आन्तरिकम्;

        surface_id_आन्तरिकम् = av_calloc(1, परिमाण(*surface_id_आन्तरिकम्));
        यदि (!surface_id_आन्तरिकम्) {
            ret =AVERROR(ENOMEM);
            गच्छ fail;
        }

        *surface_id_आन्तरिकम् = (VASurfaceID)(uintptr_t)src->दत्त[3];
        handle_युग्मानि_आन्तरिकम्->first = (mfxHDL)surface_id_आन्तरिकम्;
        handle_युग्मानि_आन्तरिकम्->second = (mfxMemId)MFX_INFINITE;

        भङ्ग;
    }
#यदि_अन्तः

#यदि CONFIG_D3D11VA
    पक्ष AV_PIX_FMT_D3D11:
    {
        AVHWFramesContext *src_ctx = (AVHWFramesContext*)src->hw_चौकटाः_ctx->दत्त;
        AVD3D11VAFramesContext *src_hwctx = src_ctx->hwctx;

        handle_युग्मानि_आन्तरिकम्->first = (mfxMemId)src->दत्त[0];

        यदि (src_hwctx->BindFlags & D3D11_BIND_RENDER_TARGET) {
            handle_युग्मानि_आन्तरिकम्->second = (mfxMemId)MFX_INFINITE;
        } अन्यथा {
            handle_युग्मानि_आन्तरिकम्->second = (mfxMemId)src->दत्त[1];
        }

        भङ्ग;
    }
#यदि_अन्तः
    स्वभाव:
        ret = AVERROR(ENOSYS);
        गच्छ fail;
    }

    surfaces_आन्तरिकम्->दत्त_2.MemId = (mfxMemId)handle_युग्मानि_आन्तरिकम्;

    ret = ff_hwframe_map_create(dst->hw_चौकटाः_ctx,
                                dst, src, qsv_dynamic_pool_unmap, surfaces_आन्तरिकम्);
    यदि (ret)
        गच्छ fail;

    dst->विस्तारः   = src->विस्तारः;
    dst->height  = src->height;
    dst->दत्त[3] = (uint8_t*)surfaces_आन्तरिकम्;

    प्रत्यागम 0;

fail:
    av_freep(&handle_युग्मानि_आन्तरिकम्);
    av_freep(&surfaces_आन्तरिकम्);
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क qsv_map_गन्तव्यम्(AVHWFramesContext *dst_ctx,
                      AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    AVQSVFramesContext *hwctx = dst_ctx->hwctx;

    यदि (hwctx->nb_surfaces)
        प्रत्यागम qsv_fixed_pool_map_गन्तव्यम्(dst_ctx, dst, src, flags);
    अन्यथा
        प्रत्यागम qsv_dynamic_pool_map_गन्तव्यम्(dst_ctx, dst, src, flags);
}

स्थिर पूर्णाङ्क qsv_चौकटाः_get_constraints(AVHWDeviceContext *ctx,
                                      ध्रुव शून्य *hwconfig,
                                      AVHWFramesConstraints *constraints)
{
    पूर्णाङ्क i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(supported_pixel_formats) + 1,
                                                    परिमाण(*constraints->valid_sw_formats));
    यदि (!constraints->valid_sw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    प्रति (i = 0; i < FF_ARRAY_ELEMS(supported_pixel_formats); i++)
        constraints->valid_sw_formats[i] = supported_pixel_formats[i].pix_fmt;
    constraints->valid_sw_formats[FF_ARRAY_ELEMS(supported_pixel_formats)] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, परिमाण(*constraints->valid_hw_formats));
    यदि (!constraints->valid_hw_formats)
        प्रत्यागम AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_QSV;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    प्रत्यागम 0;
}

स्थिर शून्य qsv_device_free(AVHWDeviceContext *ctx)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;
    QSVDevicePriv       *priv = ctx->user_opaque;

    यदि (hwctx->session)
        MFXClose(hwctx->session);

    यदि (hwctx->loader)
        MFXUnload(hwctx->loader);
    av_बफर_unref(&priv->child_device_ctx);
    av_freep(&priv);
}

स्थिर mfxIMPL वृणु_implementation(ध्रुव वर्ण *device, गणना AVHWDeviceType child_device_type)
{
    स्थिर ध्रुव संरचना {
        ध्रुव वर्ण *name;
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
    पूर्णाङ्क i;

    यदि (device) {
        प्रति (i = 0; i < FF_ARRAY_ELEMS(impl_map); i++)
            यदि (!वाक्यं_तुलय(device, impl_map[i].name)) {
                impl = impl_map[i].impl;
                भङ्ग;
            }
        यदि (i == FF_ARRAY_ELEMS(impl_map))
            impl = strtol(device, रिक्त, 0);
    }

    यदि (impl != MFX_IMPL_SOFTWARE) {
        यदि (child_device_type == AV_HWDEVICE_TYPE_D3D11VA)
            impl |= MFX_IMPL_द्वारा_D3_D11;
        अन्यथा यदि (child_device_type == AV_HWDEVICE_TYPE_DXVA2)
            impl |= MFX_IMPL_द्वारा_D3_D9;
    }

    प्रत्यागम impl;
}

स्थिर पूर्णाङ्क qsv_device_derive_from_child(AVHWDeviceContext *ctx,
                                        mfxIMPL implementation,
                                        AVHWDeviceContext *child_device_ctx,
                                        पूर्णाङ्क flags)
{
    AVQSVDeviceContext *hwctx = ctx->hwctx;

    mfx_संस्करणम्    ver = { { 3, 1 } };
    mfxHDL        handle;
    mfxHandleType handle_type;
    mfx_स्थितिः     err;
    पूर्णाङ्क ret;

    विकल्प (child_device_ctx->type) {
#यदि CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        {
            AVVAAPIDeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_VA_DISPLAY;
            handle = (mfxHDL)child_device_hwctx->display;
        }
        भङ्ग;
#यदि_अन्तः
#यदि CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        {
            AVD3D11VADeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D11_DEVICE;
            handle = (mfxHDL)child_device_hwctx->device;
        }
        भङ्ग;
#यदि_अन्तः
#यदि CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
        {
            AVDXVA2DeviceContext *child_device_hwctx = child_device_ctx->hwctx;
            handle_type = MFX_HANDLE_D3D9_DEVICE_MANAGER;
            handle = (mfxHDL)child_device_hwctx->devmgr;
        }
        भङ्ग;
#यदि_अन्तः
    स्वभाव:
        ret = AVERROR(ENOSYS);
        गच्छ fail;
    }

    ret = qsv_create_mfx_session(ctx, handle, handle_type, implementation, &ver,
                                 &hwctx->session, &hwctx->loader);
    यदि (ret)
        गच्छ fail;

    err = MFXVideo_CORE_समुच्चयः_Handle(hwctx->session, handle_type, handle);
    यदि (err != MFX_ERR_NONE) {
        av_log(ctx, AV_LOG_ERROR, "Error setting child device handle: "
               "%d\n", err);
        ret = AVERROR_UNKNOWN;
        गच्छ fail;
    }

    प्रत्यागम 0;

fail:
    यदि (hwctx->session)
        MFXClose(hwctx->session);

    यदि (hwctx->loader)
        MFXUnload(hwctx->loader);

    hwctx->session = रिक्त;
    hwctx->loader = रिक्त;
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क qsv_device_derive(AVHWDeviceContext *ctx,
                             AVHWDeviceContext *child_device_ctx,
                             AVDictionary *opts, पूर्णाङ्क flags)
{
    mfxIMPL impl;
    QSVDevicePriv *priv;

    priv = av_mallocz(परिमाण(*priv));
    यदि (!priv)
        प्रत्यागम AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->मुक्त = qsv_device_free;

    impl = वृणु_implementation("hw_any", child_device_ctx->type);
    प्रत्यागम qsv_device_derive_from_child(ctx, impl,
                                        child_device_ctx, flags);
}

स्थिर पूर्णाङ्क qsv_device_create(AVHWDeviceContext *ctx, ध्रुव वर्ण *device,
                             AVDictionary *opts, पूर्णाङ्क flags)
{
    QSVDevicePriv *priv;
    गणना AVHWDeviceType child_device_type;
    AVHWDeviceContext *child_device;
    AVDictionary *child_device_opts;
    AVDictionary_प्रविष्टिः *e;

    mfxIMPL impl;
    पूर्णाङ्क ret;

    priv = av_mallocz(परिमाण(*priv));
    यदि (!priv)
        प्रत्यागम AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->मुक्त        = qsv_device_free;

    e = av_dict_get(opts, "child_device_type", रिक्त, 0);
    यदि (e) {
        child_device_type = av_hwdevice_find_type_by_name(e->मानम्);
        यदि (child_device_type == AV_HWDEVICE_TYPE_NONE) {
            av_log(ctx, AV_LOG_ERROR, "Unknown child device type "
                   "\"%s\".\n", e->मानम्);
            प्रत्यागम AVERROR(EINVAL);
        }
#यदि QSV_ONEVPL
    } अन्यथा यदि (CONFIG_D3D11VA) {  // Use D3D11 by default if d3d11va is enabled
        av_log(ctx, AV_LOG_VERBOSE,
               "Defaulting child_device_type to AV_HWDEVICE_TYPE_D3D11VA for oneVPL."
               "Please explicitly set child device type via \"-init_hw_device\" "
               "option if needed.\n");
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
    } अन्यथा यदि (CONFIG_DXVA2) {
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
#अन्यथा
    } अन्यथा यदि (CONFIG_DXVA2) {
        av_log(रिक्त, AV_LOG_WARNING,
                "WARNING: defaulting child_device_type to AV_HWDEVICE_TYPE_DXVA2 for compatibility "
                "with old commandlines. This behaviour will be removed "
                "in the future. Please explicitly set device type via \"-init_hw_device\" option.\n");
        child_device_type = AV_HWDEVICE_TYPE_DXVA2;
    } अन्यथा यदि (CONFIG_D3D11VA) {
        child_device_type = AV_HWDEVICE_TYPE_D3D11VA;
#यदि_अन्तः
    } अन्यथा यदि (CONFIG_VAAPI) {
        child_device_type = AV_HWDEVICE_TYPE_VAAPI;
    } अन्यथा {
        av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
        प्रत्यागम AVERROR(ENOSYS);
    }

#यदि CONFIG_VAAPI && defined(_WIN32)
    /* AV_HWDEVICE_TYPE_VAAPI on Windows/Libva-win32 not supported */
    /* Reject user specified child_device_type or CONFIG_VAAPI on Windows */
    यदि (child_device_type == AV_HWDEVICE_TYPE_VAAPI) {
        av_log(ctx, AV_LOG_ERROR, "VAAPI child device type not supported for oneVPL on Windows"
                "\"%s\".\n", e->मानम्);
        प्रत्यागम AVERROR(EINVAL);
    }
#यदि_अन्तः

    child_device_opts = रिक्त;
    विकल्प (child_device_type) {
#यदि CONFIG_VAAPI
    पक्ष AV_HWDEVICE_TYPE_VAAPI:
        {
            // libmfx does not actually implement VAAPI properly, rather it
            // depends on the specific behaviour of a matching iHD driver when
            // used on recent Intel hardware.  Set options to the VAAPI device
            // creation so that we should pick a usable setup by default if
            // possible, even when multiple devices and drivers are available.
            av_dict_समुच्चयः(&child_device_opts, "vendor_id", "0x8086", 0);
            av_dict_समुच्चयः(&child_device_opts, "driver",    "iHD",    0);
        }
        भङ्ग;
#यदि_अन्तः
#यदि CONFIG_D3D11VA
    पक्ष AV_HWDEVICE_TYPE_D3D11VA:
        {
            // Make sure the hardware vendor is Intel when multiple devices are
            // available, it will be ignored if user specifies the child device
            // explicitly
            av_dict_समुच्चयः(&child_device_opts, "vendor_id",        "0x8086",  0);
        }
        भङ्ग;
#यदि_अन्तः
#यदि CONFIG_DXVA2
    पक्ष AV_HWDEVICE_TYPE_DXVA2:
#यदि QSV_ONEVPL
        {
            av_log(ctx, AV_LOG_VERBOSE,
                   "d3d11va is not available or child device type is set to dxva2 "
                   "explicitly for oneVPL.\n");
        }
#यदि_अन्तः
        भङ्ग;
#यदि_अन्तः
    स्वभाव:
        {
            av_log(ctx, AV_LOG_ERROR, "No supported child device type is enabled\n");
            प्रत्यागम AVERROR(ENOSYS);
        }
        भङ्ग;
    }

    e = av_dict_get(opts, "child_device", रिक्त, 0);
    ret = av_hwdevice_ctx_create(&priv->child_device_ctx, child_device_type,
                                 e ? e->मानम् : रिक्त, child_device_opts, 0);

    av_dict_free(&child_device_opts);
    यदि (ret < 0)
        प्रत्यागम ret;

    child_device = (AVHWDeviceContext*)priv->child_device_ctx->दत्त;

    impl = वृणु_implementation(device, child_device_type);

    प्रत्यागम qsv_device_derive_from_child(ctx, impl, child_device, 0);
}

ध्रुव HWContextType ff_hwcontext_type_qsv = {
    .type                   = AV_HWDEVICE_TYPE_QSV,
    .name                   = "QSV",

    .device_hwctx_आकार      = परिमाण(QSVDeviceContext),
    .चौकटाः_hwctx_आकार      = परिमाण(QSVFramesContext),

    .device_create          = qsv_device_create,
    .device_derive          = qsv_device_derive,
    .device_init            = qsv_device_init,
    .चौकटाः_get_constraints = qsv_चौकटाः_get_constraints,
    .चौकटाः_init            = qsv_चौकटाः_init,
    .चौकटाः_uninit          = qsv_चौकटाः_uninit,
    .चौकटाः_get_बफर      = qsv_get_बफर,
    .transfer_get_formats   = qsv_transfer_get_formats,
    .transfer_दत्त_गन्तव्यम्       = qsv_transfer_दत्त_गन्तव्यम्,
    .transfer_दत्त_from     = qsv_transfer_दत्त_from,
    .map_गन्तव्यम्                 = qsv_map_गन्तव्यम्,
    .map_from               = qsv_map_from,
    .चौकटाः_derive_गन्तव्यम्       = qsv_चौकटाः_derive_गन्तव्यम्,
    .चौकटाः_derive_from     = qsv_चौकटाः_derive_from,

    .pix_fmts = (ध्रुव गणना AVPixelFormat[]){ AV_PIX_FMT_QSV, AV_PIX_FMT_NONE },
};
