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

#అన్తర్భావ <windows.h>

#నిర్వచించు DXVA2API_USE_BITFIELDS
#నిర్వచించు COBJMACROS

#అన్తర్భావ <d3d9.h>
#అన్తర్భావ <dxva2api.h>
#అన్తర్భావ <initguid.h>

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "hwcontext.h"
#అన్తర్భావ "hwcontext_dxva2.h"
#అన్తర్భావ "hwcontext_internal.h"
#అన్తర్భావ "imgutils.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "pixdesc.h"
#అన్తర్భావ "pixfmt.h"
#అన్తర్భావ "compat/w32dlfcn.h"

రకనిర్వచనం IDirect3D9* WINAPI pDirect3DCreate9(UINT);
రకనిర్వచనం HRESULT WINAPI pDirect3DCreate9Ex(UINT, IDirect3D9Ex **);
రకనిర్వచనం HRESULT WINAPI pCreateDeviceManager9(UINT *, IDirect3DDeviceManager9 **);

#నిర్వచించు FF_D3DCREATE_FLAGS (D3DCREATE_SOFTWARE_VERTEXPROCESSING | \
                            D3DCREATE_MULTITHREADED | \
                            D3DCREATE_FPU_PRESERVE)

స్థిర స్థిరరాశి D3DPRESENT_PARAMETERS dxva2_present_params = {
    .Windowed         = TRUE,
    .వెనుక_బఫరు_వెడల్పు  = 640,
    .వెనుక_బఫరు_ఎత్తు = 480,
    .వెనుక_బఫరు_లెక్క  = 0,
    .మార్పిడి_Effect       = D3DSWAPEFFECT_DISCARD,
    .Flags            = D3DPRESENTFLAG_VIDEO,
};

రకనిర్వచనం నిర్మాణం DXVA2Mapping {
    uint32_t palette_dummy[256];
} DXVA2Mapping;

రకనిర్వచనం నిర్మాణం DXVA2_చట్రాలు_Context {
    /**
     * The public AVDXVA2FramesContext. See hwcontext_dxva2.h for it.
     */
    AVDXVA2_చట్రాలు_Context p;

    IDirect3DSurface9 **surfaces_అంతర్గత;
    పూర్ణాంకం              nb_surfaces_వాడిన;

    HANDLE  device_handle;
    IDirectXVideoAccelerationService *service;

    D3DFORMAT format;
} DXVA2_చట్రాలు_Context;

రకనిర్వచనం నిర్మాణం DXVA2DevicePriv {
    HMODULE d3dlib;
    HMODULE dxva2lib;

    HANDLE device_handle;

    IDirect3D9       *d3d9;
    IDirect3DDevice9 *d3d9device;
} DXVA2DevicePriv;

స్థిర స్థిరరాశి నిర్మాణం {
    D3DFORMAT d3d_format;
    గణన AVPixelFormat pix_fmt;
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

స్థిర శూన్య dxva2_చట్రాలు_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2_చట్రాలు_Context              *s = ctx->hwctx;
    AVDXVA2_చట్రాలు_Context *చట్రాలు_hwctx = &s->p;
    పూర్ణాంకం i;

    ఒకవేళ (చట్రాలు_hwctx->decoder_గమ్యం_release)
        IDirectXVideoDecoder_Release(చట్రాలు_hwctx->decoder_గమ్యం_release);

    ఒకవేళ (s->surfaces_అంతర్గత) {
        కొరకు (i = 0; i < చట్రాలు_hwctx->nb_surfaces; i++) {
            ఒకవేళ (s->surfaces_అంతర్గత[i])
                IDirect3DSurface9_Release(s->surfaces_అంతర్గత[i]);
        }
    }
    av_freep(&s->surfaces_అంతర్గత);

    ఒకవేళ (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = ఖాళీ;
    }

    ఒకవేళ (s->device_handle != INVALID_HANDLE_విలువ) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_విలువ;
    }
}

స్థిర శూన్య dxva2_pool_release_dummy(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}

స్థిర AVBufferRef *dxva2_pool_alloc(శూన్య *opaque, size_t కొలత)
{
    AVHWFramesContext      *ctx = (AVHWFramesContext*)opaque;
    DXVA2_చట్రాలు_Context       *s = ctx->hwctx;
    AVDXVA2_చట్రాలు_Context *hwctx = &s->p;

    ఒకవేళ (s->nb_surfaces_వాడిన < hwctx->nb_surfaces) {
        s->nb_surfaces_వాడిన++;
        తిరిగి av_బఫరు_create((uint8_t*)s->surfaces_అంతర్గత[s->nb_surfaces_వాడిన - 1],
                                పరిమాణం(**hwctx->surfaces), dxva2_pool_release_dummy, 0, 0);
    }

    తిరిగి ఖాళీ;
}

స్థిర పూర్ణాంకం dxva2_init_pool(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2_చట్రాలు_Context              *s = ctx->hwctx;
    AVDXVA2_చట్రాలు_Context *చట్రాలు_hwctx = &s->p;
    పూర్ణాంకం decode = (చట్రాలు_hwctx->surface_type == DXVA2_Video_Decoder_Render_లక్ష్యం);

    పూర్ణాంకం i;
    HRESULT hr;

    ఒకవేళ (ctx->initial_pool_కొలత <= 0)
        తిరిగి 0;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(device_hwctx->devmgr, &s->device_handle);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(device_hwctx->devmgr,
                                                 s->device_handle,
                                                 decode ? &video_decoder_service : &video_processor_service,
                                                 (శూన్య **)&s->service);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create the video service\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        ఒకవేళ (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            ఆపు;
        }
    }
    ఒకవేళ (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        తిరిగి AVERROR(EINVAL);
    }

    s->surfaces_అంతర్గత = av_calloc(ctx->initial_pool_కొలత,
                                     పరిమాణం(*s->surfaces_అంతర్గత));
    ఒకవేళ (!s->surfaces_అంతర్గత)
        తిరిగి AVERROR(ENOMEM);

    hr = IDirectXVideoAccelerationService_CreateSurface(s->service,
                                                        ctx->వెడల్పు, ctx->ఎత్తు,
                                                        ctx->initial_pool_కొలత - 1,
                                                        s->format, D3DPOOL_DEFAULT, 0,
                                                        చట్రాలు_hwctx->surface_type,
                                                        s->surfaces_అంతర్గత, ఖాళీ);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the surfaces\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    ffhwframesctx(ctx)->pool_అంతర్గత =
        av_బఫరు_pool_init2(పరిమాణం(*s->surfaces_అంతర్గత),
                             ctx, dxva2_pool_alloc, ఖాళీ);
    ఒకవేళ (!ffhwframesctx(ctx)->pool_అంతర్గత)
        తిరిగి AVERROR(ENOMEM);

    చట్రాలు_hwctx->surfaces    = s->surfaces_అంతర్గత;
    చట్రాలు_hwctx->nb_surfaces = ctx->initial_pool_కొలత;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం dxva2_చట్రాలు_init(AVHWFramesContext *ctx)
{
    DXVA2_చట్రాలు_Context       *s = ctx->hwctx;
    AVDXVA2_చట్రాలు_Context *hwctx = &s->p;
    పూర్ణాంకం ret;

    ఒకవేళ (hwctx->surface_type != DXVA2_Video_Decoder_Render_లక్ష్యం &&
        hwctx->surface_type != DXVA2_Video_Processor_Render_లక్ష్యం) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        తిరిగి AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_విలువ;

    /* init the frame pool if the caller didn't provide one */
    ఒకవేళ (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        ఒకవేళ (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            తిరిగి ret;
        }
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం dxva2_get_బఫరు(AVHWFramesContext *ctx, AVFrame *చట్రం)
{
    చట్రం->buf[0] = av_బఫరు_pool_get(ctx->pool);
    ఒకవేళ (!చట్రం->buf[0])
        తిరిగి AVERROR(ENOMEM);

    చట్రం->దత్తాంశం[3] = చట్రం->buf[0]->దత్తాంశం;
    చట్రం->format  = AV_PIX_FMT_DXVA2_VLD;
    చట్రం->వెడల్పు   = ctx->వెడల్పు;
    చట్రం->ఎత్తు  = ctx->ఎత్తు;

    తిరిగి 0;
}

స్థిర పూర్ణాంకం dxva2_transfer_get_formats(AVHWFramesContext *ctx,
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

స్థిర శూన్య dxva2_unmap_చట్రం(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->ఆధారం->దత్తాంశం[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}

స్థిర పూర్ణాంకం dxva2_map_చట్రం(AVHWFramesContext *ctx, AVFrame *dst, స్థిరరాశి AVFrame *src,
                           పూర్ణాంకం flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->దత్తాంశం[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    పూర్ణాంకం i, err, nb_planes;
    పూర్ణాంకం తాళం_flags = 0;

    nb_planes = av_pix_fmt_లెక్క_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    ఒకవేళ (!(flags & AV_HWFRAME_MAP_WRITE))
        తాళం_flags |= D3DLOCK_READONLY;
    ఒకవేళ (flags & AV_HWFRAME_MAP_OVERWRITE)
        తాళం_flags |= D3DLOCK_DISCARD;

    hr = IDirect3_DSurface9_తాళం_Rect(surface, &LockedRect, ఖాళీ, తాళం_flags);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    map = av_mallocz(పరిమాణం(*map));
    ఒకవేళ (!map) {
        err = AVERROR(ENOMEM);
        వెళ్ళు fail;
    }

    err = ff_hwframe_map_create(src->hw_చట్రాలు_ctx, dst, src,
                                dxva2_unmap_చట్రం, map);
    ఒకవేళ (err < 0) {
        av_freep(&map);
        వెళ్ళు fail;
    }

    కొరకు (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_సూచికలు(dst->దత్తాంశం, dst->format, surfaceDesc.ఎత్తు_2,
                           (uint8_t*)LockedRect.p_బిట్లు, dst->linesize);

    ఒకవేళ (dst->format == AV_PIX_FMT_PAL8)
        dst->దత్తాంశం[1] = (uint8_t*)map->palette_dummy;

    తిరిగి 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    తిరిగి err;
}

స్థిర పూర్ణాంకం dxva2_transfer_దత్తాంశం_గమ్యం(AVHWFramesContext *ctx, AVFrame *dst,
                                  స్థిరరాశి AVFrame *src)
{
    AVFrame *map;
    పూర్ణాంకం ret;

    ఒకవేళ (src->format != ctx->sw_format)
        తిరిగి AVERROR(ENOSYS);

    map = av_చట్రం_alloc();
    ఒకవేళ (!map)
        తిరిగి AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_చట్రం(ctx, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    av_image_copy2(map->దత్తాంశం, map->linesize, src->దత్తాంశం, src->linesize,
                   ctx->sw_format, src->వెడల్పు, src->ఎత్తు);

fail:
    av_చట్రం_free(&map);
    తిరిగి ret;
}

స్థిర పూర్ణాంకం dxva2_transfer_దత్తాంశం_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    స్థిరరాశి AVFrame *src)
{
    AVFrame *map;
    ptrdiff_t src_linesize[4], dst_linesize[4];
    పూర్ణాంకం ret, i;

    ఒకవేళ (dst->format != ctx->sw_format)
        తిరిగి AVERROR(ENOSYS);

    map = av_చట్రం_alloc();
    ఒకవేళ (!map)
        తిరిగి AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_చట్రం(ctx, map, src, AV_HWFRAME_MAP_READ);
    ఒకవేళ (ret < 0)
        వెళ్ళు fail;

    కొరకు (i = 0; i < 4; i++) {
        dst_linesize[i] = dst->linesize[i];
        src_linesize[i] = map->linesize[i];
    }
    av_image_copy_uc_from(dst->దత్తాంశం, dst_linesize, (స్థిరరాశి uint8_t **)map->దత్తాంశం, src_linesize,
                          ctx->sw_format, src->వెడల్పు, src->ఎత్తు);
fail:
    av_చట్రం_free(&map);
    తిరిగి ret;
}

స్థిర పూర్ణాంకం dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, స్థిరరాశి AVFrame *src, పూర్ణాంకం flags)
{
    పూర్ణాంకం err;

    ఒకవేళ (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        తిరిగి AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_చట్రం(ctx, dst, src, flags);
    ఒకవేళ (err < 0)
        తిరిగి err;

    err = av_చట్రం_copy_props(dst, src);
    ఒకవేళ (err < 0)
        తిరిగి err;

    తిరిగి 0;
}

స్థిర శూన్య dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    ఒకవేళ (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_విలువ)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    ఒకవేళ (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    ఒకవేళ (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    ఒకవేళ (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    ఒకవేళ (priv->d3dlib)
        dlclose(priv->d3dlib);

    ఒకవేళ (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}

స్థిర పూర్ణాంకం dxva2_device_create9(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODE d3ddm;
    HRESULT hr;
    pDirect3DCreate9 *createD3D = (pDirect3DCreate9 *)dlsym(priv->d3dlib, "Direct3DCreate9");
    ఒకవేళ (!createD3D) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate Direct3DCreate9\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    priv->d3d9 = createD3D(D3_D_SDK_సంస్కరణ);
    ఒకవేళ (!priv->d3d9) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create IDirect3D object\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    IDirect3_D9_Get_Adapter_Display_బహుళకం(priv->d3d9, adapter, &d3ddm);

    d3dpp.వెనుక_బఫరు_Format = d3ddm.Format;

    hr = IDirect3D9_CreateDevice(priv->d3d9, adapter, D3DDEVTYPE_HAL, Get_Desktop_కిటికీ(),
                                 FF_D3DCREATE_FLAGS,
                                 &d3dpp, &priv->d3d9device);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    తిరిగి 0;
}

స్థిర పూర్ణాంకం dxva2_device_create9ex(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODEEX modeex = {0};
    IDirect3D9Ex *d3d9ex = ఖాళీ;
    IDirect3DDevice9Ex *exdev = ఖాళీ;
    HRESULT hr;
    pDirect3DCreate9Ex *createD3DEx = (pDirect3DCreate9Ex *)dlsym(priv->d3dlib, "Direct3DCreate9Ex");
    ఒకవేళ (!createD3DEx)
        తిరిగి AVERROR(ENOSYS);

    hr = createD3DEx(D3_D_SDK_సంస్కరణ, &d3d9ex);
    ఒకవేళ (FAILED(hr))
        తిరిగి AVERROR_UNKNOWN;

    modeex.కొలత_3 = పరిమాణం(D3DDISPLAYMODEEX);
    hr = IDirect3_D9_Ex_Get_Adapter_Display_బహుళకం_Ex(d3d9ex, adapter, &modeex, ఖాళీ);
    ఒకవేళ (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        తిరిగి AVERROR_UNKNOWN;
    }

    d3dpp.వెనుక_బఫరు_Format = modeex.Format;

    hr = IDirect3D9Ex_CreateDeviceEx(d3d9ex, adapter, D3DDEVTYPE_HAL, Get_Desktop_కిటికీ(),
                                     FF_D3DCREATE_FLAGS,
                                     &d3dpp, ఖాళీ, &exdev);
    ఒకవేళ (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        తిరిగి AVERROR_UNKNOWN;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Using D3D9Ex device.\n");
    priv->d3d9 = (IDirect3D9 *)d3d9ex;
    priv->d3d9device = (IDirect3DDevice9 *)exdev;
    తిరిగి 0;
}

స్థిర పూర్ణాంకం dxva2_device_create(AVHWDeviceContext *ctx, స్థిరరాశి అక్షరం *device,
                               AVDictionary *opts, పూర్ణాంకం flags)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv *priv;
    pCreateDeviceManager9 *createDeviceManager = ఖాళీ;
    గుర్తులేని resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;
    HRESULT hr;
    పూర్ణాంకం err;

    ఒకవేళ (device)
        adapter = atoi(device);

    priv = av_mallocz(పరిమాణం(*priv));
    ఒకవేళ (!priv)
        తిరిగి AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->విడుదల        = dxva2_device_free;

    priv->device_handle = INVALID_HANDLE_విలువ;

    priv->d3dlib = dlopen("d3d9.dll", 0);
    ఒకవేళ (!priv->d3dlib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D9 library\n");
        తిరిగి AVERROR_UNKNOWN;
    }
    priv->dxva2lib = dlopen("dxva2.dll", 0);
    ఒకవేళ (!priv->dxva2lib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load DXVA2 library\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    createDeviceManager = (pCreateDeviceManager9 *)dlsym(priv->dxva2lib,
                                                         "DXVA2CreateDirect3DDeviceManager9");
    ఒకవేళ (!createDeviceManager) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    ఒకవేళ (dxva2_device_create9ex(ctx, adapter) < 0) {
        // Retry with "classic" d3d9
        err = dxva2_device_create9(ctx, adapter);
        ఒకవేళ (err < 0)
            తిరిగి err;
    }

    hr = createDeviceManager(&resetToken, &hwctx->devmgr);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device manager\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(hwctx->devmgr, priv->d3d9device, resetToken);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind Direct3D device to device manager\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &priv->device_handle);
    ఒకవేళ (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        తిరిగి AVERROR_UNKNOWN;
    }

    తిరిగి 0;
}

స్థిరరాశి HWContextType ff_hwcontext_type_dxva2 = {
    .type                 = AV_HWDEVICE_TYPE_DXVA2,
    .name                 = "DXVA2",

    .device_hwctx_కొలత    = పరిమాణం(AVDXVA2DeviceContext),
    .చట్రాలు_hwctx_కొలత    = పరిమాణం(DXVA2_చట్రాలు_Context),

    .device_create        = dxva2_device_create,
    .చట్రాలు_init          = dxva2_చట్రాలు_init,
    .చట్రాలు_uninit        = dxva2_చట్రాలు_uninit,
    .చట్రాలు_get_బఫరు    = dxva2_get_బఫరు,
    .transfer_get_formats = dxva2_transfer_get_formats,
    .transfer_దత్తాంశం_గమ్యం     = dxva2_transfer_దత్తాంశం_గమ్యం,
    .transfer_దత్తాంశం_from   = dxva2_transfer_దత్తాంశం_from,
    .map_from             = dxva2_map_from,

    .pix_fmts             = (స్థిరరాశి గణన AVPixelFormat[]){ AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_NONE },
};
