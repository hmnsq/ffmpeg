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

#شامل <windows.h>

#تعریف_کرو DXVA2API_USE_BITFIELDS
#تعریف_کرو COBJMACROS

#شامل <d3d9.h>
#شامل <dxva2api.h>
#شامل <initguid.h>

#شامل "avassert.h"
#شامل "common.h"
#شامل "hwcontext.h"
#شامل "hwcontext_dxva2.h"
#شامل "hwcontext_internal.h"
#شامل "imgutils.h"
#شامل "mem.h"
#شامل "pixdesc.h"
#شامل "pixfmt.h"
#شامل "compat/w32dlfcn.h"

قسمتعریف IDirect3D9* WINAPI pDirect3DCreate9(UINT);
قسمتعریف HRESULT WINAPI pDirect3DCreate9Ex(UINT, IDirect3D9Ex **);
قسمتعریف HRESULT WINAPI pCreateDeviceManager9(UINT *, IDirect3DDeviceManager9 **);

#تعریف_کرو FF_D3DCREATE_FLAGS (D3DCREATE_SOFTWARE_VERTEXPROCESSING | \
                            D3DCREATE_MULTITHREADED | \
                            D3DCREATE_FPU_PRESERVE)

ساکن ثابت D3DPRESENT_PARAMETERS dxva2_present_params = {
    .Windowed         = TRUE,
    .عقب_بفر_چوڑائی  = 640,
    .عقب_بفر_اونچائی = 480,
    .عقب_بفر_گنتی  = 0,
    .تبادلہ_Effect       = D3DSWAPEFFECT_DISCARD,
    .Flags            = D3DPRESENTFLAG_VIDEO,
};

قسمتعریف ساخت DXVA2Mapping {
    uint32_t palette_dummy[256];
} DXVA2Mapping;

قسمتعریف ساخت DXVA2_چوکھٹے_Context {
    /**
     * The public AVDXVA2FramesContext. See hwcontext_dxva2.h for it.
     */
    AVDXVA2_چوکھٹے_Context p;

    IDirect3DSurface9 **surfaces_اندرونی;
    صحیح              nb_surfaces_مستعمل;

    HANDLE  device_handle;
    IDirectXVideoAccelerationService *service;

    D3DFORMAT format;
} DXVA2_چوکھٹے_Context;

قسمتعریف ساخت DXVA2DevicePriv {
    HMODULE d3dlib;
    HMODULE dxva2lib;

    HANDLE device_handle;

    IDirect3D9       *d3d9;
    IDirect3DDevice9 *d3d9device;
} DXVA2DevicePriv;

ساکن ثابت ساخت {
    D3DFORMAT d3d_format;
    شمار AVPixelFormat pix_fmt;
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

ساکن خالی dxva2_چوکھٹے_uninit(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2_چوکھٹے_Context              *s = ctx->hwctx;
    AVDXVA2_چوکھٹے_Context *چوکھٹے_hwctx = &s->p;
    صحیح i;

    اگر (چوکھٹے_hwctx->decoder_مقصد_release)
        IDirectXVideoDecoder_Release(چوکھٹے_hwctx->decoder_مقصد_release);

    اگر (s->surfaces_اندرونی) {
        برائے (i = 0; i < چوکھٹے_hwctx->nb_surfaces; i++) {
            اگر (s->surfaces_اندرونی[i])
                IDirect3DSurface9_Release(s->surfaces_اندرونی[i]);
        }
    }
    av_freep(&s->surfaces_اندرونی);

    اگر (s->service) {
        IDirectXVideoAccelerationService_Release(s->service);
        s->service = تہی;
    }

    اگر (s->device_handle != INVALID_HANDLE_قدر) {
        IDirect3DDeviceManager9_CloseDeviceHandle(device_hwctx->devmgr, s->device_handle);
        s->device_handle = INVALID_HANDLE_قدر;
    }
}

ساکن خالی dxva2_pool_release_dummy(خالی *opaque, uint8_t *ڈیٹا)
{
    // important not to free anything here--data is a surface object
    // associated with the call to CreateSurface(), and these surfaces are
    // released in dxva2_frames_uninit()
}

ساکن AVBufferRef *dxva2_pool_alloc(خالی *opaque, size_t سائز)
{
    AVHWFramesContext      *ctx = (AVHWFramesContext*)opaque;
    DXVA2_چوکھٹے_Context       *s = ctx->hwctx;
    AVDXVA2_چوکھٹے_Context *hwctx = &s->p;

    اگر (s->nb_surfaces_مستعمل < hwctx->nb_surfaces) {
        s->nb_surfaces_مستعمل++;
        واپس av_بفر_create((uint8_t*)s->surfaces_اندرونی[s->nb_surfaces_مستعمل - 1],
                                حجم(**hwctx->surfaces), dxva2_pool_release_dummy, 0, 0);
    }

    واپس تہی;
}

ساکن صحیح dxva2_init_pool(AVHWFramesContext *ctx)
{
    AVDXVA2DeviceContext *device_hwctx = ctx->device_ctx->hwctx;
    DXVA2_چوکھٹے_Context              *s = ctx->hwctx;
    AVDXVA2_چوکھٹے_Context *چوکھٹے_hwctx = &s->p;
    صحیح decode = (چوکھٹے_hwctx->surface_type == DXVA2_Video_Decoder_Render_ہدف);

    صحیح i;
    HRESULT hr;

    اگر (ctx->initial_pool_سائز <= 0)
        واپس 0;

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(device_hwctx->devmgr, &s->device_handle);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        واپس AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_GetVideoService(device_hwctx->devmgr,
                                                 s->device_handle,
                                                 decode ? &video_decoder_service : &video_processor_service,
                                                 (خالی **)&s->service);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create the video service\n");
        واپس AVERROR_UNKNOWN;
    }

    برائے (i = 0; i < FF_ARRAY_ELEMS(supported_formats); i++) {
        اگر (ctx->sw_format == supported_formats[i].pix_fmt) {
            s->format = supported_formats[i].d3d_format;
            توڑو;
        }
    }
    اگر (i == FF_ARRAY_ELEMS(supported_formats)) {
        av_log(ctx, AV_LOG_ERROR, "Unsupported pixel format: %s\n",
               av_get_pix_fmt_name(ctx->sw_format));
        واپس AVERROR(EINVAL);
    }

    s->surfaces_اندرونی = av_calloc(ctx->initial_pool_سائز,
                                     حجم(*s->surfaces_اندرونی));
    اگر (!s->surfaces_اندرونی)
        واپس AVERROR(ENOMEM);

    hr = IDirectXVideoAccelerationService_CreateSurface(s->service,
                                                        ctx->چوڑائی, ctx->اونچائی,
                                                        ctx->initial_pool_سائز - 1,
                                                        s->format, D3DPOOL_DEFAULT, 0,
                                                        چوکھٹے_hwctx->surface_type,
                                                        s->surfaces_اندرونی, تہی);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Could not create the surfaces\n");
        واپس AVERROR_UNKNOWN;
    }

    ffhwframesctx(ctx)->pool_اندرونی =
        av_بفر_pool_init2(حجم(*s->surfaces_اندرونی),
                             ctx, dxva2_pool_alloc, تہی);
    اگر (!ffhwframesctx(ctx)->pool_اندرونی)
        واپس AVERROR(ENOMEM);

    چوکھٹے_hwctx->surfaces    = s->surfaces_اندرونی;
    چوکھٹے_hwctx->nb_surfaces = ctx->initial_pool_سائز;

    واپس 0;
}

ساکن صحیح dxva2_چوکھٹے_init(AVHWFramesContext *ctx)
{
    DXVA2_چوکھٹے_Context       *s = ctx->hwctx;
    AVDXVA2_چوکھٹے_Context *hwctx = &s->p;
    صحیح ret;

    اگر (hwctx->surface_type != DXVA2_Video_Decoder_Render_ہدف &&
        hwctx->surface_type != DXVA2_Video_Processor_Render_ہدف) {
        av_log(ctx, AV_LOG_ERROR, "Unknown surface type: %lu\n",
               hwctx->surface_type);
        واپس AVERROR(EINVAL);
    }

    s->device_handle = INVALID_HANDLE_قدر;

    /* init the frame pool if the caller didn't provide one */
    اگر (!ctx->pool) {
        ret = dxva2_init_pool(ctx);
        اگر (ret < 0) {
            av_log(ctx, AV_LOG_ERROR, "Error creating an internal frame pool\n");
            واپس ret;
        }
    }

    واپس 0;
}

ساکن صحیح dxva2_get_بفر(AVHWFramesContext *ctx, AVFrame *چوکھٹا)
{
    چوکھٹا->buf[0] = av_بفر_pool_get(ctx->pool);
    اگر (!چوکھٹا->buf[0])
        واپس AVERROR(ENOMEM);

    چوکھٹا->ڈیٹا[3] = چوکھٹا->buf[0]->ڈیٹا;
    چوکھٹا->format  = AV_PIX_FMT_DXVA2_VLD;
    چوکھٹا->چوڑائی   = ctx->چوڑائی;
    چوکھٹا->اونچائی  = ctx->اونچائی;

    واپس 0;
}

ساکن صحیح dxva2_transfer_get_formats(AVHWFramesContext *ctx,
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

ساکن خالی dxva2_unmap_چوکھٹا(AVHWFramesContext *ctx, HWMapDescriptor *hwmap)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)hwmap->ماخذ->ڈیٹا[3];
    IDirect3DSurface9_UnlockRect(surface);
    av_freep(&hwmap->priv);
}

ساکن صحیح dxva2_map_چوکھٹا(AVHWFramesContext *ctx, AVFrame *dst, ثابت AVFrame *src,
                           صحیح flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->ڈیٹا[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    صحیح i, err, nb_planes;
    صحیح تالا_flags = 0;

    nb_planes = av_pix_fmt_گنتی_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        واپس AVERROR_UNKNOWN;
    }

    اگر (!(flags & AV_HWFRAME_MAP_WRITE))
        تالا_flags |= D3DLOCK_READONLY;
    اگر (flags & AV_HWFRAME_MAP_OVERWRITE)
        تالا_flags |= D3DLOCK_DISCARD;

    hr = IDirect3_DSurface9_تالا_Rect(surface, &LockedRect, تہی, تالا_flags);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        واپس AVERROR_UNKNOWN;
    }

    map = av_mallocz(حجم(*map));
    اگر (!map) {
        err = AVERROR(ENOMEM);
        جاؤ fail;
    }

    err = ff_hwframe_map_create(src->hw_چوکھٹے_ctx, dst, src,
                                dxva2_unmap_چوکھٹا, map);
    اگر (err < 0) {
        av_freep(&map);
        جاؤ fail;
    }

    برائے (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_اشارے(dst->ڈیٹا, dst->format, surfaceDesc.اونچائی_2,
                           (uint8_t*)LockedRect.p_بٹ, dst->linesize);

    اگر (dst->format == AV_PIX_FMT_PAL8)
        dst->ڈیٹا[1] = (uint8_t*)map->palette_dummy;

    واپس 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    واپس err;
}

ساکن صحیح dxva2_transfer_ڈیٹا_مقصد(AVHWFramesContext *ctx, AVFrame *dst,
                                  ثابت AVFrame *src)
{
    AVFrame *map;
    صحیح ret;

    اگر (src->format != ctx->sw_format)
        واپس AVERROR(ENOSYS);

    map = av_چوکھٹا_alloc();
    اگر (!map)
        واپس AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_چوکھٹا(ctx, map, dst, AV_HWFRAME_MAP_WRITE | AV_HWFRAME_MAP_OVERWRITE);
    اگر (ret < 0)
        جاؤ fail;

    av_image_copy2(map->ڈیٹا, map->linesize, src->ڈیٹا, src->linesize,
                   ctx->sw_format, src->چوڑائی, src->اونچائی);

fail:
    av_چوکھٹا_free(&map);
    واپس ret;
}

ساکن صحیح dxva2_transfer_ڈیٹا_from(AVHWFramesContext *ctx, AVFrame *dst,
                                    ثابت AVFrame *src)
{
    AVFrame *map;
    ptrdiff_t src_linesize[4], dst_linesize[4];
    صحیح ret, i;

    اگر (dst->format != ctx->sw_format)
        واپس AVERROR(ENOSYS);

    map = av_چوکھٹا_alloc();
    اگر (!map)
        واپس AVERROR(ENOMEM);
    map->format = dst->format;

    ret = dxva2_map_چوکھٹا(ctx, map, src, AV_HWFRAME_MAP_READ);
    اگر (ret < 0)
        جاؤ fail;

    برائے (i = 0; i < 4; i++) {
        dst_linesize[i] = dst->linesize[i];
        src_linesize[i] = map->linesize[i];
    }
    av_image_copy_uc_from(dst->ڈیٹا, dst_linesize, (ثابت uint8_t **)map->ڈیٹا, src_linesize,
                          ctx->sw_format, src->چوڑائی, src->اونچائی);
fail:
    av_چوکھٹا_free(&map);
    واپس ret;
}

ساکن صحیح dxva2_map_from(AVHWFramesContext *ctx,
                          AVFrame *dst, ثابت AVFrame *src, صحیح flags)
{
    صحیح err;

    اگر (dst->format != AV_PIX_FMT_NONE && dst->format != ctx->sw_format)
        واپس AVERROR(ENOSYS);
    dst->format = ctx->sw_format;

    err = dxva2_map_چوکھٹا(ctx, dst, src, flags);
    اگر (err < 0)
        واپس err;

    err = av_چوکھٹا_copy_props(dst, src);
    اگر (err < 0)
        واپس err;

    واپس 0;
}

ساکن خالی dxva2_device_free(AVHWDeviceContext *ctx)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv       *priv = ctx->user_opaque;

    اگر (hwctx->devmgr && priv->device_handle != INVALID_HANDLE_قدر)
        IDirect3DDeviceManager9_CloseDeviceHandle(hwctx->devmgr, priv->device_handle);

    اگر (hwctx->devmgr)
        IDirect3DDeviceManager9_Release(hwctx->devmgr);

    اگر (priv->d3d9device)
        IDirect3DDevice9_Release(priv->d3d9device);

    اگر (priv->d3d9)
        IDirect3D9_Release(priv->d3d9);

    اگر (priv->d3dlib)
        dlclose(priv->d3dlib);

    اگر (priv->dxva2lib)
        dlclose(priv->dxva2lib);

    av_freep(&ctx->user_opaque);
}

ساکن صحیح dxva2_device_create9(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODE d3ddm;
    HRESULT hr;
    pDirect3DCreate9 *createD3D = (pDirect3DCreate9 *)dlsym(priv->d3dlib, "Direct3DCreate9");
    اگر (!createD3D) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate Direct3DCreate9\n");
        واپس AVERROR_UNKNOWN;
    }

    priv->d3d9 = createD3D(D3_D_SDK_نسخہ);
    اگر (!priv->d3d9) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create IDirect3D object\n");
        واپس AVERROR_UNKNOWN;
    }

    IDirect3_D9_Get_Adapter_Display_منوال(priv->d3d9, adapter, &d3ddm);

    d3dpp.عقب_بفر_Format = d3ddm.Format;

    hr = IDirect3D9_CreateDevice(priv->d3d9, adapter, D3DDEVTYPE_HAL, Get_Desktop_کھڑکی(),
                                 FF_D3DCREATE_FLAGS,
                                 &d3dpp, &priv->d3d9device);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device\n");
        واپس AVERROR_UNKNOWN;
    }

    واپس 0;
}

ساکن صحیح dxva2_device_create9ex(AVHWDeviceContext *ctx, UINT adapter)
{
    DXVA2DevicePriv *priv = ctx->user_opaque;
    D3DPRESENT_PARAMETERS d3dpp = dxva2_present_params;
    D3DDISPLAYMODEEX modeex = {0};
    IDirect3D9Ex *d3d9ex = تہی;
    IDirect3DDevice9Ex *exdev = تہی;
    HRESULT hr;
    pDirect3DCreate9Ex *createD3DEx = (pDirect3DCreate9Ex *)dlsym(priv->d3dlib, "Direct3DCreate9Ex");
    اگر (!createD3DEx)
        واپس AVERROR(ENOSYS);

    hr = createD3DEx(D3_D_SDK_نسخہ, &d3d9ex);
    اگر (FAILED(hr))
        واپس AVERROR_UNKNOWN;

    modeex.سائز_3 = حجم(D3DDISPLAYMODEEX);
    hr = IDirect3_D9_Ex_Get_Adapter_Display_منوال_Ex(d3d9ex, adapter, &modeex, تہی);
    اگر (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        واپس AVERROR_UNKNOWN;
    }

    d3dpp.عقب_بفر_Format = modeex.Format;

    hr = IDirect3D9Ex_CreateDeviceEx(d3d9ex, adapter, D3DDEVTYPE_HAL, Get_Desktop_کھڑکی(),
                                     FF_D3DCREATE_FLAGS,
                                     &d3dpp, تہی, &exdev);
    اگر (FAILED(hr)) {
        IDirect3D9Ex_Release(d3d9ex);
        واپس AVERROR_UNKNOWN;
    }

    av_log(ctx, AV_LOG_VERBOSE, "Using D3D9Ex device.\n");
    priv->d3d9 = (IDirect3D9 *)d3d9ex;
    priv->d3d9device = (IDirect3DDevice9 *)exdev;
    واپس 0;
}

ساکن صحیح dxva2_device_create(AVHWDeviceContext *ctx, ثابت حرف *device,
                               AVDictionary *opts, صحیح flags)
{
    AVDXVA2DeviceContext *hwctx = ctx->hwctx;
    DXVA2DevicePriv *priv;
    pCreateDeviceManager9 *createDeviceManager = تہی;
    غیرعلامتی resetToken = 0;
    UINT adapter = D3DADAPTER_DEFAULT;
    HRESULT hr;
    صحیح err;

    اگر (device)
        adapter = atoi(device);

    priv = av_mallocz(حجم(*priv));
    اگر (!priv)
        واپس AVERROR(ENOMEM);

    ctx->user_opaque = priv;
    ctx->آزاد        = dxva2_device_free;

    priv->device_handle = INVALID_HANDLE_قدر;

    priv->d3dlib = dlopen("d3d9.dll", 0);
    اگر (!priv->d3dlib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load D3D9 library\n");
        واپس AVERROR_UNKNOWN;
    }
    priv->dxva2lib = dlopen("dxva2.dll", 0);
    اگر (!priv->dxva2lib) {
        av_log(ctx, AV_LOG_ERROR, "Failed to load DXVA2 library\n");
        واپس AVERROR_UNKNOWN;
    }

    createDeviceManager = (pCreateDeviceManager9 *)dlsym(priv->dxva2lib,
                                                         "DXVA2CreateDirect3DDeviceManager9");
    اگر (!createDeviceManager) {
        av_log(ctx, AV_LOG_ERROR, "Failed to locate DXVA2CreateDirect3DDeviceManager9\n");
        واپس AVERROR_UNKNOWN;
    }

    اگر (dxva2_device_create9ex(ctx, adapter) < 0) {
        // Retry with "classic" d3d9
        err = dxva2_device_create9(ctx, adapter);
        اگر (err < 0)
            واپس err;
    }

    hr = createDeviceManager(&resetToken, &hwctx->devmgr);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to create Direct3D device manager\n");
        واپس AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_ResetDevice(hwctx->devmgr, priv->d3d9device, resetToken);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to bind Direct3D device to device manager\n");
        واپس AVERROR_UNKNOWN;
    }

    hr = IDirect3DDeviceManager9_OpenDeviceHandle(hwctx->devmgr, &priv->device_handle);
    اگر (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Failed to open device handle\n");
        واپس AVERROR_UNKNOWN;
    }

    واپس 0;
}

ثابت HWContextType ff_hwcontext_type_dxva2 = {
    .type                 = AV_HWDEVICE_TYPE_DXVA2,
    .name                 = "DXVA2",

    .device_hwctx_سائز    = حجم(AVDXVA2DeviceContext),
    .چوکھٹے_hwctx_سائز    = حجم(DXVA2_چوکھٹے_Context),

    .device_create        = dxva2_device_create,
    .چوکھٹے_init          = dxva2_چوکھٹے_init,
    .چوکھٹے_uninit        = dxva2_چوکھٹے_uninit,
    .چوکھٹے_get_بفر    = dxva2_get_بفر,
    .transfer_get_formats = dxva2_transfer_get_formats,
    .transfer_ڈیٹا_مقصد     = dxva2_transfer_ڈیٹا_مقصد,
    .transfer_ڈیٹا_from   = dxva2_transfer_ڈیٹا_from,
    .map_from             = dxva2_map_from,

    .pix_fmts             = (ثابت شمار AVPixelFormat[]){ AV_PIX_FMT_DXVA2_VLD, AV_PIX_FMT_NONE },
};
