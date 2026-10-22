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

#अन्तर्भाव <windows.h>

#परिभाषय DXVA2API_USE_BITFIELDS
#परिभाषय COBJMACROS

#अन्तर्भाव <d3d9.h>
#अन्तर्भाव <dxva2api.h>
#अन्तर्भाव <initguid.h>

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "hwcontext.h"
#अन्तर्भाव "hwcontext_dxva2.h"
#अन्तर्भाव "hwcontext_internal.h"
#अन्तर्भाव "imgutils.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "pixdesc.h"
#अन्तर्भाव "pixfmt.h"
#अन्तर्भाव "compat/w32dlfcn.h"

प्रकारनिर्देश IDirect3D9* WINAPI pDirect3DCreate9(UINT);
प्रकारनिर्देश HRESULT WINAPI pDirect3DCreate9Ex(UINT, IDirect3D9Ex **);
प्रकारनिर्देश HRESULT WINAPI pCreateDeviceManager9(UINT *, IDirect3DDeviceManager9 **);

#परिभाषय FF_D3DCREATE_FLAGS (D3DCREATE_SOFTWARE_VERTEXPROCESSING | \
                            D3DCREATE_MULTITHREADED | \
                            D3DCREATE_FPU_PRESERVE)

स्थिर ध्रुव D3DPRESENT_PARAMETERS dxva2_present_params = {
    .Windowed         = TRUE,
    .पृष्ठभागः_बफर_विस्तारः  = 640,
    .पृष्ठभागः_बफर_Height = 480,
    .पृष्ठभागः_बफर_गणनम्  = 0,
    .SwapEffect       = D3DSWAPEFFECT_DISCARD,
    .Flags            = D3DPRESENTFLAG_VIDEO,
};

प्रकारनिर्देश संरचना DXVA2Mapping {
    uint32_t palette_dummy[256];
} DXVA2Mapping;

प्रकारनिर्देश संरचना DXVA2_चौकटाः_Context {
    /**
     * The public AVDXVA2FramesContext. See hwcontext_dxva2.h for it.
     */
    AVDXVA2_चौकटाः_Context p;

    IDirect3DSurface9 **surfaces_आन्तरिकम्;
    पूर्णाङ्क              nb_surfaces_प्रयुक्तम्;

    HANDLE  device_handle;
    IDirectXVideoAccelerationService *service;

    D3DFORMAT format;
} DXVA2_चौकटाः_Context;

प्रकारनिर्देश संरचना DXVA2DevicePriv {
    HMODULE d3dlib;
    HMODULE dxva2lib;

    HANDLE device_handle;

    IDirect3D9       *d3d9;
    IDirect3DDevice9 *d3d9device;
} DXVA2DevicePriv;

स्थिर ध्रुव संरचना {
    D3DFORMAT d3d_format;
    गणना AVPixelFormat pix_fmt;
} supported_formats[] = {
    { MKTAG('N', 'V', '1', '2'), AV_PIX_FMT_NV12 },
    { MKTAG('P', '0', '1', '0'), AV_PIX_FMT_P010 },
    { MKTAG('A', 'Y', 'U', 'V'), AV_PIX_FMT_VUYX },
    { MKTAG('Y', 'U', 'Y', '2'), AV_PIX_FMT_YUYV422 },
    { MKTAG('Y', '2', '1', '0'), AV_PIX_FMT_Y210 },
    { MKTAG('Y', '4', '1', '0'), AV_PIX_FMT_XV30 },
    { MKTAG('P', '0', '1', '6'), AV_PIX_FMT_P012 },
    { MKTAG('Y', '2', '1', '6'), AV_PIX_FMT_Y216 },
    { MKTAG('Y', '4', '1', '6'), AV_PIX_FMT_XV48 },
    // There is no 12bit pixel format defined in D3DFMT*, use 16bit to compatible
    // with 12 bit AV_PIX_FMT* formats.
    { MKTAG('Y', '2', '1', '6'), AV_PIX_FMT_Y212 },
    { MKTAG('Y', '4', '1', '6'), AV_PIX_FMT_XV36 },
    { D3DFMT_P8,                 AV_PIX_FMT_PAL8 },
    { D3DFMT_A8R8G8B8,           AV_PIX_FMT_BGRA },
};

DEFINE_GUID(video_decoder_service,   0xfc51a551, 0xd5e7, 0x11d9, 0xaf, 0x55, 0x00, 0x05, 0x4e, 0x43, 0xff, 0x02);
DEFINE_GUID(video_processor_service, 0xfc51a552, 0xd5e7, 0x11d9, 0xaf, 0x55, 0x00, 0x05, 0x4e, 0x43, 0xff, 0x02);

स्थिर शून्य dxva2_चौकटाः_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2_चौकटाः_Context              *s = ctx->hwctx;
    AVDXVA2_चौकटाः_Context *चौकटाः_hwctx = &s->p;
    पूर्णाङ्क i;

    यदि (चौकटाः_hwctx->decoder_गन्तव्यम्_release)
        IDirectXVideoDecoder_Release(चौकटाः_hwctx->decoder_गन्तव्यम्_release);

    यदि (s->surfaces_आन्तरिकम्) {
        प्रति (i = 0; i < चौकटाः_hwctx->nb_surfaces; i++) {
            यदि (s->surfaces_आन्तरिकम्[i])
                IDirect3DSurface9_Release(s->surfaces_आन्तरिकम्[i]);
        }
    }
    av_freep(&s->surfaces_आन्तरिकम्);

    यदि (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = रिक्त;
    }

    यदि (s->device_handle != INVALID_HANDLE_मानम्) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_मानम्;
    }
}

स्थिर शून्य dxva2_pool_release_dummy(शून्य *opaque, uint8_t *दत्त)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}

स्थिर AVBufferRef *dxva2_pool_alloc(शून्य *opaque, size_t आकार)
{
    AVHWFramesContext      *ctx = (AVHWFramesContext*)opaque;
    DXVA2_चौकटाः_Context       *s = ctx->hwctx;
    AVDXVA2_चौकटाः_Context *hwctx = &s->p;

    यदि (s->nb_surfaces_प्रयुक्तम् < hwctx->nb_surfaces) {
        s->nb_surfaces_प्रयुक्तम्++;
        प्रत्यागम av_बफर_create((uint8_t*)s->surfaces_आन्तरिकम्[s->nb_surfaces_प्रयुक्तम् - 1],
                                परिमाण(**hwctx->surfaces), dxva2_pool_release_dummy, 0, 0);
    }

    प्रत्यागम रिक्त;
}

स्थिर पूर्णाङ्क dxva2_init_pool(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2_चौकटाः_Context              *s = ctx->hwctx;
    AVDXVA2_चौकटाः_Context *चौकटाः_hwctx = &s->p;
    पूर्णाङ्क decode = (चौकटाः_hwctx->surface_type == DXVA2_VideoDecoderRenderTarget);

    पूर्णाङ्क i;
    HRESULT hr;

    यदि (ctx->initial_pool_आकार <= 0)
        प्रत्यागम 0;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(device_hwctx->devmgr, &s->device_handle);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(device_hwctx->devmgr,
                                                 s->device_handle,
                                                 decode ? &video_decoder_service : &video_processor_service,
                                                 (शून्य **)&s->service);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create the video service\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रति (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        यदि (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            भङ्ग;
        }
    }
    यदि (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        प्रत्यागम AVERROR(EINVAL);
    }

    s->surfaces_आन्तरिकम् = av_calloc(ctx->initial_pool_आकार,
                                     परिमाण(*s->surfaces_आन्तरिकम्));
    यदि (!s->surfaces_आन्तरिकम्)
        प्रत्यागम AVERROR(ENOMEM);

    hr = IDirectXVideoAccelerationService_CreateSurface(s->service,
                                                        ctx->विस्तारः, ctx->height,
                                                        ctx->initial_pool_आकार - 1,
                                                        s->format, D3DPOOL_DEFAULT, 0,
                                                        चौकटाः_hwctx->surface_type,
                                                        s->surfaces_आन्तरिकम्, रिक्त);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the surfaces\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    ffhwframesctx(ctx)->pool_आन्तरिकम् =
        av_बफर_pool_init2(परिमाण(*s->surfaces_आन्तरिकम्),
                             ctx, dxva2_pool_alloc, रिक्त);
    यदि (!ffhwframesctx(ctx)->pool_आन्तरिकम्)
        प्रत्यागम AVERROR(ENOMEM);

    चौकटाः_hwctx->surfaces    = s->surfaces_आन्तरिकम्;
    चौकटाः_hwctx->nb_surfaces = ctx->initial_pool_आकार;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क dxva2_चौकटाः_init(AVHWFramesContext *ctx)
{
    DXVA2_चौकटाः_Context       *s = ctx->hwctx;
    AVDXVA2_चौकटाः_Context *hwctx = &s->p;
    पूर्णाङ्क ret;

    यदि (hwctx->surface_type != DXVA2_VideoDecoderRenderTarget &&
        hwctx->surface_type != DXVA2_VideoProcessorRenderTarget) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        प्रत्यागम AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_मानम्;

    /* init the frame pool if the caller didn't provide one */
    यदि (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        यदि (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            प्रत्यागम ret;
        }
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क dxva2_get_बफर(AVHWFramesContext *ctx, AVFrame *frame)
{
    frame->buf[0] = av_बफर_pool_get(ctx->pool);
    यदि (!frame->buf[0])
        प्रत्यागम AVERROR(ENOMEM);

    frame->दत्त[3] = frame->buf[0]->दत्त;
    frame->format  = AV_PIX_FMT_DXVA2_VLD;
    frame->विस्तारः   = ctx->विस्तारः;
    frame->height  = ctx->height;

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क dxva2_transfer_get_formats(AVHWFramesContext *ctx,
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

स्थिर शून्य dxva2_unmap_frame(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->source->दत्त[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}

स्थिर पूर्णाङ्क dxva2_map_frame(AVHWFramesContext *ctx, AVFrame *dst, ध्रुव AVFrame *src,
                           पूर्णाङ्क flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->दत्त[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    पूर्णाङ्क i, err, nb_planes;
    पूर्णाङ्क तालकम्_flags = 0;

    nb_planes = av_pix_fmt_गणनम्_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    यदि (!(flags & AV_HWFRAME_MAP_WRITE))
        तालकम्_flags |= D3DLOCK_READONLY;
    यदि (flags & AV_HWFRAME_MAP_OVERWRITE)
        तालकम्_flags |= D3DLOCK_DISCARD;

    hr = IDirect3_DSurface9_तालकम्_Rect(surface, &LockedRect, रिक्त, तालकम्_flags);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    map = av_mallocz(परिमाण(*map));
    यदि (!map) {
        err = AVERROR(ENOMEM);
        गच्छ fail;
    }

    err = ff_hwframe_map_create(src->hw_चौकटाः_ctx, dst, src,
                                dxva2_unmap_frame, map);
    यदि (err < 0) {
        av_freep(&map);
        गच्छ fail;
    }

    प्रति (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_सूचकाः(dst->दत्त, dst->format, surfaceDesc.Height,
                           (uint8_t*)LockedRect.p_द्वयङ्काः, dst->linesize);

    यदि (dst->format == AV_PIX_FMT_PAL8)
        dst->दत्त[1] = (uint8_t*)map->palette_dummy;

    प्रत्यागम 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    प्रत्यागम err;
}

स्थिर पूर्णाङ्क dxva2_transfer_दत्त_गन्तव्यम्(AVHWFramesContext *ctx, AVFrame *dst,
                                  ध्रुव AVFrame *src)
{
    AVFrame *map;
    पूर्णाङ्क ret;

    यदि (src->format != ctx->sw_format)
        प्रत्यागम AVERROR(ENOSYS);

    map = av_frame_alloc();
    यदि (!map)
        प्रत्यागम AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    यदि (ret < 0)
        गच्छ fail;

    av_image_copy2(map->दत्त, map->linesize, src->दत्त, src->linesize,
                   ctx->sw_format, src->विस्तारः, src->height);

fail:
    av_frame_free(&map);
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क dxva2_transfer_दत्त_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ध्रुव AVFrame *src)
{
    AVFrame *map;
    ptrdiff_t src_linesize[4], dst_linesize[4];
    पूर्णाङ्क ret, i;

    यदि (dst->format != ctx->sw_format)
        प्रत्यागम AVERROR(ENOSYS);

    map = av_frame_alloc();
    यदि (!map)
        प्रत्यागम AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_frame(ctx, map, src, AV_HWFRAME_MAP_READ);
    यदि (ret < 0)
        गच्छ fail;

    प्रति (i = 0; i < 4; i++) {
        dst_linesize[i] = dst->linesize[i];
        src_linesize[i] = map->linesize[i];
    }
    av_image_copy_uc_from(dst->दत्त, dst_linesize, (ध्रुव uint8_t **)map->दत्त, src_linesize,
                          ctx->sw_format, src->विस्तारः, src->height);
fail:
    av_frame_free(&map);
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, ध्रुव AVFrame *src, पूर्णाङ्क flags)
{
    पूर्णाङ्क err;

    यदि (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        प्रत्यागम AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_frame(ctx, dst, src, flags);
    यदि (err < 0)
        प्रत्यागम err;

    err = av_frame_copy_props(dst, src);
    यदि (err < 0)
        प्रत्यागम err;

    प्रत्यागम 0;
}

स्थिर शून्य dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    यदि (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_मानम्)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    यदि (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    यदि (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    यदि (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    यदि (priv->d3dlib)
        dlclose(priv->d3dlib);

    यदि (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}

स्थिर पूर्णाङ्क dxva2_device_create9(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODE d3ddm;
    HRESULT hr;
    pDirect3DCreate9 *createD3D = (pDirect3DCreate9 *)dlsym(priv->d3dlib, "Direct3DCreate9");
    यदि (!createD3D) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate Direct3DCreate9\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    priv->d3d9 = createD3D(D3_D_SDK_संस्करणम्);
    यदि (!priv->d3d9) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create IDirect3D object\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    IDirect3_D9_Get_Adapter_Display_बहुलकम्(priv->d3d9, adapter, &d3ddm);

    d3dpp.पृष्ठभागः_बफर_Format = d3ddm.Format;

    hr = IDirect3D9_CreateDevice(priv->d3d9, adapter, D3DDEVTYPE_HAL, Get_Desktop_गवाक्षः(),
                                 FF_D3DCREATE_FLAGS,
                                 &d3dpp, &priv->d3d9device);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क dxva2_device_create9ex(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODEEX modeex = {0};
    IDirect3D9Ex *d3d9ex = रिक्त;
    IDirect3DDevice9Ex *exdev = रिक्त;
    HRESULT hr;
    pDirect3DCreate9Ex *createD3DEx = (pDirect3DCreate9Ex *)dlsym(priv->d3dlib, "Direct3DCreate9Ex");
    यदि (!createD3DEx)
        प्रत्यागम AVERROR(ENOSYS);

    hr = createD3DEx(D3_D_SDK_संस्करणम्, &d3d9ex);
    यदि (FAILED(hr))
        प्रत्यागम AVERROR_UNKNOWN;

    modeex.आकार_3 = परिमाण(D3DDISPLAYMODEEX);
    hr = IDirect3_D9_Ex_Get_Adapter_Display_बहुलकम्_Ex(d3d9ex, adapter, &modeex, रिक्त);
    यदि (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    d3dpp.पृष्ठभागः_बफर_Format = modeex.Format;

    hr = IDirect3D9Ex_CreateDeviceEx(d3d9ex, adapter, D3DDEVTYPE_HAL, Get_Desktop_गवाक्षः(),
                                     FF_D3DCREATE_FLAGS,
                                     &d3dpp, रिक्त, &exdev);
    यदि (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        प्रत्यागम AVERROR_UNKNOWN;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Using D3D9Ex device.\n");
    priv->d3d9 = (IDirect3D9 *)d3d9ex;
    priv->d3d9device = (IDirect3DDevice9 *)exdev;
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क dxva2_device_create(AVHWDeviceContext *ctx, ध्रुव वर्ण *device,
                               AVDictionary *opts, पूर्णाङ्क flags)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv *priv;
    pCreateDeviceManager9 *createDeviceManager = रिक्त;
    अचिह्नित resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;
    HRESULT hr;
    पूर्णाङ्क err;

    यदि (device)
        adapter = atoi(device);

    priv = av_mallocz(परिमाण(*priv));
    यदि (!priv)
        प्रत्यागम AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->मुक्त        = dxva2_device_free;

    priv->device_handle = INVALID_HANDLE_मानम्;

    priv->d3dlib = dlopen("d3d9.dll", 0);
    यदि (!priv->d3dlib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D9 library\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }
    priv->dxva2lib = dlopen("dxva2.dll", 0);
    यदि (!priv->dxva2lib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load DXVA2 library\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    createDeviceManager = (pCreateDeviceManager9 *)dlsym(priv->dxva2lib,
                                                         "DXVA2CreateDirect3DDeviceManager9");
    यदि (!createDeviceManager) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    यदि (dxva2_device_create9ex(ctx, adapter) < 0) {
        // Retry with "classic" d3d9
        err = dxva2_device_create9(ctx, adapter);
        यदि (err < 0)
            प्रत्यागम err;
    }

    hr = createDeviceManager(&resetToken, &hwctx->devmgr);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device manager\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(hwctx->devmgr, priv->d3d9device, resetToken);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind Direct3D device to device manager\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &priv->device_handle);
    यदि (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        प्रत्यागम AVERROR_UNKNOWN;
    }

    प्रत्यागम 0;
}

ध्रुव HWContextType ff_hwcontext_type_dxva2 = {
    .type                 = AV_HWDEVICE_TYPE_DXVA2,
    .name                 = "DXVA2",

    .device_hwctx_आकार    = परिमाण(AVDXVA2DeviceContext),
    .चौकटाः_hwctx_आकार    = परिमाण(DXVA2_चौकटाः_Context),

    .device_create        = dxva2_device_create,
    .चौकटाः_init          = dxva2_चौकटाः_init,
    .चौकटाः_uninit        = dxva2_चौकटाः_uninit,
    .चौकटाः_get_बफर    = dxva2_get_बफर,
    .transfer_get_formats = dxva2_transfer_get_formats,
    .transfer_दत्त_गन्तव्यम्     = dxva2_transfer_दत्त_गन्तव्यम्,
    .transfer_दत्त_from   = dxva2_transfer_दत्त_from,
    .map_from             = dxva2_map_from,

    .pix_fmts             = (ध्रुव गणना AVPixelFormat[]){ AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_NONE },
};
